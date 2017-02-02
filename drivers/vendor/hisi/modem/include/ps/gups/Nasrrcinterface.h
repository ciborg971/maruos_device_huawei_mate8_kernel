

#ifndef __NASRRCINTERFACE_H__
#define __NASRRCINTERFACE_H__



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "WUe.h"
#include "PsTypeDef.h"


#include "ComInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
#define RRC_MAX_FORBLA_NUM              (32)                /* ��ֹע���������ĸ��� */
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
#define RRC_MAX_HIGH_PLMN_NUM           (48)                /* ��������PLMN�������� */
#define RRC_MAX_LOW_PLMN_NUM            (48)                /* ��������PLMN�������� */
#define RRC_MAX_EQUPLMN_NUM             (16)                /* ��ЧPLMN��������     */
#define RRC_MAX_PLMN_NUM                (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM)
                                                            /* PLMN�������� */
#define RRC_NAS_MAX_RAB_SETUP           (16)                /* ���������RAB��        */
#define RRC_NAS_MAX_RB_PER_RAB          (8)                 /* ÿ��RAB���������RB��  */
#define RRC_NAS_MAX_CN_DOMAIN           (2)                 /* ���CN����Ŀ           */
#define RRC_NAS_MAX_SIZE_NAS_GSM_MAP    (8)                 /* Э��ֵ : 8             */
#define RRC_NAS_MAX_SIZE_NAS_MSG        (256)               /* NAS��Ϣ��󳤶�        */
#define RRC_NAS_CIPHER_KEY_LEN          (16)                /* ������Կ���� */
#define RRC_NAS_INTEGRITY_KEY_LEN       (16)                /* �����Ա�����Կ���� */
#define RR_NAS_KC_LEN                   (8)                 /* RR������Կ���� */
#define RRC_NAS_TMSI_LEN                (4)                 /* TMSI���� */
#define RRC_NAS_PTMSI_LEN               (4)                 /* PTMSI���� */
#define RRC_NAS_IMSI_MAX_LEN            (8)                 /* IMSI��󳤶� */
#define RRC_NAS_AT_CELL_MAX_NUM         (8)                 /* С��ID�ṹ�� */
#define RRC_NAS_AT_MAX_TRCH             (8)                 /* �ŵ�����ṹ�� */
#define RRC_CELL_INFO_MAX_NUM           (8)
#define RRMM_UE_RFPOWER_INVALID         (0x1fff)            /* ��Чֵ */
#define RRC_NAS_MAX_AMR_RATE_NUM        (10)                /* AMR���������� */
#define NAS_RRC_MAX_RE_TX_MSG_LENTH     (320)               /* RRMM_EST_REQ_STRU����RRMM_DATA_REQ_STRU����󳤶� */
#define NAS_RRC_MAX_RE_TX_MSG_NUM       (2)                 /* ����ط���DT��Ϣ���� */
#define RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN                (250)  /* INTER_RAT_HANDOVER_INFO ����,�250�ֽ� */

#define MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE                (6)    /* RAC��Ϣ��С���� */
#define MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE                (52)   /* RAC��Ϣ��󳤶� */

#define NAS_RRC_MAX_BG_SRCH_PLMN_NUM    (16)                /* BG����ʧ�ܺ��ϱ�������PLMN���� */
#define NAS_RRC_MAX_AVAILPLMN_NUM       (18)                /* RRMM_PLMN_QUERY_CNF����п���������Ϣ��������:HPLMN+EPLMN */
#define RRC_NAS_MEASURE_INVALID_VALUE   (0x5A5A)            /* ͨ��AT��ѯ����ֵ���޷���ȡ����ֵʱ�ϱ���Чֵ */

#define NAS_RRC_MAX_EHPLMN_NUM          (32)                /* ֧�ֵ����EHPLMN���� */

#define NAS_RRC_MAX_RAT_NUM                             (3)                     /* ��ǰ֧�ֵĽ��뼼������ */

#define RRC_NAS_NET_SCAN_MAX_FREQ_NUM   (20)

#define MS_CLASSMARK2_MAX_LEN                              (4)                  /* R6Э����Classmark2��󳤶� */
#define MS_CLASSMARK3_MAX_LEN                              (32)                 /* R8Э����Classmark3��󳤶� */

#define RRC_NAS_NET_SCAN_MAX_FREQ_NUM   (20)

#define RRC_NAS_TDS_ARFCN_MAX_NUM           (9)                                 /* TDSƵ���б������� */

#define  RRMM_TDS_ARFCN_MAX_NUM                          (9)                    /* TDSƵ���б�������������GAS���������ṹ��MTC�ϱ�Ƶ����Ϣ */
#define  RRMM_LTE_ARFCN_MAX_NUM                          (8)                    /* LTEƵ���б�������������GAS���������ṹ��MTC�ϱ�Ƶ����Ϣ */
#define  RRMM_GSM_MAX_USING_ARFCN_NUM                    (7)                    /* GSMƵ���б������� */
#define  RRMM_GSM_MA_ARFCN_MAX_NUM                       (64)                   /* GSM��ƵƵ���б������� */
#define  RRMM_WCDMA_MAX_USING_ARFCN_NUM                  (4)                    /* WCDMAƵ���б������� */
/* Added by h00313353 for SMS Filter Prj, 2015-9-19, begin */
#define  NAS_SMS_PD                                      (0x09)
#define  NAS_PD_MASK                                     (0x0F)
/* Added by h00313353 for SMS Filter Prj, 2015-9-19, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_RRC_MSG_TYPE_ENUM
 �ṹ˵��  : ԭ���ulMsgName
*****************************************************************************/
enum NAS_RRC_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/  /* ��ע */
/* MM����AS��ԭ�� */
    RRMM_PLMN_SEARCH_REQ                = 0x0000,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_REQ_STRU */
    RRMM_EQU_PLMN_NOTIFY_REQ            = 0x0002,   /* _H2ASN_MsgChoice RRMM_EQU_PLMN_NOTIFY_REQ_STRU */
    RRMM_START_REQ                      = 0x0004,   /* _H2ASN_MsgChoice RRMM_START_REQ_STRU */
    RRMM_CELL_SELECTION_CTRL_REQ        = 0x0006,   /* _H2ASN_MsgChoice RRMM_CELL_SELECTION_CTRL_REQ_STRU */
    RRMM_EST_REQ                        = 0x0008,   /* _H2ASN_MsgChoice RRMM_EST_REQ_STRU */
    RRMM_DATA_REQ                       = 0x000A,   /* _H2ASN_MsgChoice RRMM_DATA_REQ_STRU */
    RRMM_REL_REQ                        = 0x000C,   /* _H2ASN_MsgChoice RRMM_REL_REQ_STRU */
    RRMM_NAS_INFO_CHANGE_REQ            = 0x0010,   /* _H2ASN_MsgChoice RRMM_NAS_INFO_CHANGE_REQ_STRU */
    RRRABM_RAB_RSP                      = 0x0012,   /* _H2ASN_MsgChoice RRRABM_RAB_RSP_STRU */
    RRRABM_QOS_UPDATE_REQ               = 0x0014,   /* _H2ASN_MsgChoice RRRABM_QOS_UPDATE_REQ_STRU */
    RRMM_POWER_OFF_REQ                  = 0x0016,   /* _H2ASN_MsgChoice RRMM_POWER_OFF_REQ_STRU */
    RRMM_PLMN_SEARCH_STOP_REQ           = 0x0018,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_STOP_REQ_ST */
    RRMM_SUSPEND_RSP                    = 0x002A,   /* _H2ASN_MsgChoice RRMM_SUSPEND_RSP_ST */
    RRMM_RESUME_RSP                     = 0x002C,   /* _H2ASN_MsgChoice RRMM_RESUME_RSP_ST */
    GRRMM_NAS_INFO_CHANGE_REQ           = 0x002E,   /* _H2ASN_MsgChoice GRRMM_NAS_INFO_CHANGE_REQ_STRU */
    GRRGMM_ASSIGN_REQ                   = 0x0030,   /* _H2ASN_MsgChoice GRRGMM_ASSIGN_REQ_ST */
    RRMM_SUSPEND_REQ                    = 0x0032,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REQ_ST */
    RRMM_NAS_PARAMS_REQ                 = 0x0034,   /* _H2ASN_MsgChoice RRMM_NAS_PARAMS_REQ_ST */
    RRMM_AT_MSG_REQ                     = 0x0036,   /* _H2ASN_MsgChoice RRMM_AT_MSG_REQ_ST */
    GRRMM_EST_SAPI3_REQ                 = 0x0038,   /* _H2ASN_MsgChoice GRRMM_EST_SAPI3_REQ_ST */
    GRRMM_AT_MSG_REQ                    = 0x003A,   /* _H2ASN_MsgChoice GRRMM_AT_MSG_REQ_ST */

    RRRABM_HANDOVER_RAB_RSP             = 0x003C,   /* _H2ASN_MsgChoice RRRABM_HANDOVER_RAB_RSP_STRU */
    RRMM_UICC_STATUS_CHANGE_IND         = 0x003e,   /* _H2ASN_MsgChoice RRMM_UICC_STATUS_CHANGE_IND_ST */
    RRMM_SET_WCDMA_BAND_REQ             = 0x0042,   /* _H2ASN_MsgChoice RRMM_SET_WCDMA_BAND_REQ_ST */
    RRMM_SET_GSM_BAND_REQ               = 0x0044,   /* _H2ASN_MsgChoice RRMM_SET_GSM_BAND_REQ_ST */

    RRRABM_REL_ALL_REQ                  = 0x0046,   /* _H2ASN_MsgChoice RRRABM_REL_ALL_REQ_STRU */

    RRMM_SUSPEND_REL_REQ                = 0x0048,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REL_REQ_STRU */

    RRMM_NAS_COMM_INFO_CHANGE_REQ       = 0x004A,   /* _H2ASN_MsgChoice RRMM_NAS_COMM_INFO_REQ_STRU */
    RRMM_SYS_CFG_REQ                    = 0x004C,   /* _H2ASN_MsgChoice RRMM_SYS_CFG_REQ_STRU */
    RRMM_PLMN_QUERY_CNF                 = 0x004E,   /* _H2ASN_MsgChoice RRMM_PLMN_QUERY_CNF_STRU */

    RRMM_BG_PLMN_SEARCH_REQ             = 0x0050,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_REQ_ST */
    RRMM_BG_PLMN_STOP_REQ               = 0x0052,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_STOP_REQ_ST */

    RRMM_INTER_RAT_HANDOVER_INFO_REQ    = 0x0064,   /* _H2ASN_MsgChoice RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU */
    RRMM_EPLMN_QUERY_REQ                = 0x0066,   /* _H2ASN_MsgChoice RRMM_EPLMN_QUERY_REQ_STRU */
    RRRABM_FASTDORM_START_REQ           = 0x0068,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_START_REQ_STRU */
    RRRABM_FASTDORM_STOP_REQ            = 0x006A,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_STOP_REQ_STRU */
    RRMM_AUTH_FAIL_NOTIFY_REQ           = 0x006C,   /* _H2ASN_MsgChoice RRMM_AUTH_FAIL_NOTIFY_REQ_STRU */
    RRMM_TRANSACTION_INFO_ENQ           = 0x006E,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_INFO_ENQ_STRU */
    RRMM_UTRAN_MODE_REQ                 = 0x0070,   /* _H2ASN_MsgChoice RRMM_UTRAN_MODE_REQ_STRU */

    RRMM_NET_SCAN_REQ                   = 0x0072,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_REQ_STRU */
    RRMM_NET_SCAN_STOP_REQ              = 0x0074,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_STOP_REQ_STRU */

    RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND  = 0x0076,   /* _H2ASN_MsgChoice RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND_STRU */
    RRMM_REL_CS_PS_ALL_CONN_REQ         = 0x0078,   /* _H2ASN_MsgChoice RRMM_REL_CS_PS_ALL_CONN_REQ_STRU */

    RRMM_BEGIN_SESSION_NOTIFY           = 0x007E,   /* _H2ASN_MsgChoice RRMM_BEGIN_SESSION_NOTIFY_STRU */
    RRMM_END_SESSION_NOTIFY             = 0x0082,   /* _H2ASN_MsgChoice RRMM_END_SESSION_NOTIFY_STRU */

    RRMM_SERVICE_ABORT_NOTIFY        = 0x0080,  /* _H2ASN_MsgChoice RRMM_SERVICE_ABORT_NOTIFY_STRU */

    RRMM_GMM_PROC_NOTIFY               = 0x007A,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_NOTIFY_STRU */
    RRMM_GMM_PROC_ANS                  = 0X007C,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_ANS_STRU */

    RRRABM_VOICEPREFER_START_REQ       = 0x0084,   /* _H2ASN_MsgChoice RRRABM_VOICEPREFER_START_REQ_STRU */
    RRRABM_VOICEPREFER_STOP_REQ        = 0x0086,   /* _H2ASN_MsgChoice RRRABM_VOICEPREFER_STOP_REQ_STRU */

    RRMM_TRANSACTION_STATUS_NOTIFY     = 0x0088,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_STATUS_NOTIFY_STRU */

    /* AS����MM��ԭ�� */
    RRMM_PLMN_SEARCH_CNF                = 0x0001,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_CNF_STRU */
    RRMM_PLMN_LIST_IND                  = 0x0003,   /* _H2ASN_MsgChoice RRMM_PLMN_LIST_IND_STRU */
    RRMM_AREA_LOST_IND                  = 0x0005,   /* _H2ASN_MsgChoice RRMM_AREA_LOST_IND_STRU */
    RRMM_SYS_INFO_IND                   = 0x0007,   /* _H2ASN_MsgChoice RRMM_SYS_INFO_IND_STRU  */
    RRMM_PAGING_IND                     = 0x0009,   /* _H2ASN_MsgChoice RRMM_PAGING_IND_STRU    */
    RRMM_EST_CNF                        = 0x000B,   /* _H2ASN_MsgChoice RRMM_EST_CNF_STRU       */
    RRMM_DATA_IND                       = 0x000D,   /* _H2ASN_MsgChoice RRMM_DATA_IND_STRU      */
    RRMM_REL_IND                        = 0x000F,   /* _H2ASN_MsgChoice RRMM_REL_IND_STRU */
    RRMM_SECURITY_IND                   = 0x0011,   /* _H2ASN_MsgChoice RRMM_SECURITY_IND_STRU  */
    RRRABM_RAB_IND                      = 0x0013,   /* _H2ASN_MsgChoice RRRABM_RAB_IND_STRU     */
    RRMM_SYNC_IND                       = 0x0015,   /* _H2ASN_MsgChoice RRMM_SYNC_IND_STRU      */
    RRRABM_STATUS_IND                   = 0x0017,   /* _H2ASN_MsgChoice RRRABM_STATUS_IND_STRU  */
    RRMM_POWER_OFF_CNF                  = 0x0019,   /* _H2ASN_MsgChoice RRMM_POWER_OFF_CNF_STRU */
    RRMM_START_CNF                      = 0x001B,   /* _H2ASN_MsgChoice RRMM_START_CNF_STRU */
    RRMM_AC_INFO_CHANGE_IND             = 0x001D,   /* _H2ASN_MsgChoice RRMM_AC_INFO_CHANGE_IND_STRU   */
    RRMM_PLMN_SEARCH_STOP_CNF           = 0x001F,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_STOP_CNF_ST */
    GRRMM_SYS_INFO_IND                  = 0x0021,   /* _H2ASN_MsgChoice GRRMM_SYS_INFO_IND_ST */
    GRRMM_PAGING_IND                    = 0x0023,   /* _H2ASN_MsgChoice GRRMM_PAGING_IND_ST   */
    GAS_RR_SYNC_IND                     = 0x0025,   /* _H2ASN_MsgChoice GAS_RR_SYNC_IND_ST    */
    RRMM_SUSPEND_IND                    = 0x0027,   /* _H2ASN_MsgChoice RRMM_SUSPEND_IND_ST   */
    RRMM_RESUME_IND                     = 0x0029,   /* _H2ASN_MsgChoice RRMM_RESUME_IND_ST    */
    RRMM_SUSPEND_CNF                    = 0x003B,   /* _H2ASN_MsgChoice RRMM_SUSPEND_CNF_ST   */
    RRMM_GPRS_SUSPENSION_IND            = 0x003D,   /* _H2ASN_MsgChoice RRMM_GPRS_SUSPEND_IND_ST */
    GRRMM_SCELL_MEAS_IND                = 0x003F,   /* _H2ASN_MsgChoice GRRMM_SCELL_MEAS_IND_ST  */
    GRRMM_EST_SAPI3_CNF                 = 0x0041,   /* _H2ASN_MsgChoice GRRMM_EST_SAPI3_CNF_ST   */
    RRMM_GPRS_RESUME_IND                = 0x0047,   /* _H2ASN_MsgChoice RRMM_GPRS_RESUME_IND_ST  */
    RRMM_AT_MSG_IND                     = 0x0049,   /* _H2ASN_MsgChoice RRMM_AT_MSG_IND_ST       */
    RRMM_AT_MSG_CNF                     = 0x004B,   /* _H2ASN_MsgChoice RRMM_AT_MSG_CNF_ST       */

    RRRABM_HANDOVER_RAB_IND             = 0x004D,   /* _H2ASN_MsgChoice RRRABM_HANDOVER_RAB_IND_STRU */
    RRMM_UICC_STATUS_CHANGE_RSP         = 0x004F,   /* _H2ASN_MsgChoice RRMM_UICC_STATUS_CHANGE_RSP_ST */
    RRMM_SET_WCDMA_BAND_CNF             = 0x0051,   /* _H2ASN_MsgChoice RRMM_SET_WCDMA_BAND_CNF_ST */
    RRMM_SET_GSM_BAND_CNF               = 0x0053,   /* _H2ASN_MsgChoice RRMM_SET_GSM_BAND_CNF_ST */
    WRRMM_SCELL_RXLEV_IND               = 0x0055,   /* _H2ASN_MsgChoice WRRMM_SCELL_RXLEV_IND_ST */

    RRMM_SYS_CFG_CNF                    = 0x0057,   /* _H2ASN_MsgChoice RRMM_SYS_CFG_CNF_STRU */
    GAS_RR_CHAN_IND                     = 0x0059,   /* _H2ASN_MsgChoice GAS_RR_CHAN_MOD_IND_ST */
    RRMM_SUSPEND_REL_CNF                = 0x005B,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REL_CNF_STRU */
    RRMM_PLMN_QUERY_REQ                 = 0x005D,   /* _H2ASN_MsgChoice RRMM_PLMN_QUERY_REQ_STRU */
    RRMM_CELL_RESELECT_IND              = 0X005F,   /* _H2ASN_MsgChoice RRMM_CELL_RESELECT_IND_ST */
    RRMM_LIMIT_SERVICE_CAMP_IND         = 0X0061,   /* _H2ASN_MsgChoice RRMM_LIMIT_SERVICE_CAMP_IND_STRU */
    GRRGMM_TBF_REL_IND                  = 0X0063,   /* _H2ASN_MsgChoice GRRGMM_TBF_REL_IND_ST */

    RRMM_BG_PLMN_SEARCH_STATUS_IND      = 0X0065,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_STATUS_IND_ST */
    RRMM_BG_PLMN_SEARCH_CNF             = 0X0067,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_CNF_ST */
    RRMM_BG_PLMN_STOP_CNF               = 0X0069,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_STOP_CNF_ST */

    RRMM_INTER_RAT_HANDOVER_INFO_CNF    = 0x006B,   /* _H2ASN_MsgChoice RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU */

    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND  = 0x006D,   /* _H2ASN_MsgChoice GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU */
    RRMM_NOT_CAMP_ON_IND                = 0x006F,   /* _H2ASN_MsgChoice RRMM_NOT_CAMP_ON_IND_STRU */

    RRMM_EPLMN_QUERY_CNF                = 0x0071,   /* _H2ASN_MsgChoice RRMM_EPLMN_QUERY_CNF_STRU */
    WRRMM_TBAR_EXPIRED_IND              = 0x0073,   /* _H2ASN_MsgChoice WRRMM_TBAR_EXPIRED_IND_STRU */
    GRRGMM_GPRS_ACCESS_RESULT_IND       = 0x0075,   /* _H2ASN_MsgChoice GRRGMM_GPRS_ACCESS_RESULT_IND_STRU */
    RRRABM_FASTDORM_INFO_IND            = 0x0077,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_INFO_IND_STRU */
    RRRABM_FASTDORM_START_CNF           = 0x0079,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_START_CNF_STRU */
    RRRABM_FASTDORM_STOP_CNF            = 0x007B,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_STOP_CNF_STRU */
    RRMM_CIPHER_INFO_IND                = 0x007D,   /* _H2ASN_MsgChoice RRMM_CIPHER_INFO_IND_STRU */

    RRMM_W_AC_INFO_CHANGE_IND           = 0x007F,   /* _H2ASN_MsgChoice RRMM_W_AC_INFO_CHANGE_IND_STRU   */
    RRMM_TRANSACTION_INFO_ANS           = 0x0081,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_INFO_ANS_STRU */
    RRMM_UE_OOC_STATUS_NOTIFY_IND       = 0x0083,   /* _H2ASN_MsgChoice RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU */

    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND = 0x0085,/* _H2ASN_MsgChoice GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU */

    RRMM_UTRAN_MODE_CNF                 = 0x0087,   /* _H2ASN_MsgChoice RRMM_UTRAN_MODE_CNF_STRU */

    RRMM_NACK_DATA_IND                  = 0x0089,   /* _H2ASN_MsgChoice RRMM_NACK_DATA_IND_STRU */

    RRMM_HANDOVER_INFO_IND              = 0x008B,   /* _H2ASN_MsgChoice RRMM_HANDOVER_INFO_IND_STRU */
    RRMM_CLASSMARK_CHANGE_IND           = 0x008D,   /* _H2ASN_MsgChoice RRMM_CLASSMARK_CHANGE_IND_STRU */

    RRMM_NET_SCAN_CNF                   = 0x0091,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_CNF_STRU */
    RRMM_NET_SCAN_STOP_CNF              = 0x0093,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_STOP_CNF_STRU */

    RRMM_NCELL_MONITOR_IND              = 0x0095,   /* _H2ASN_MsgChoice RRC_NAS_NCELL_MONITOR_IND_STRU */
    RRMM_GMM_PROC_ENQ                   = 0x0097,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_ENQ_STRU */

    RRMM_SEARCHED_PLMN_INFO_IND         = 0x0099  , /* _H2ASN_MsgChoice RRMM_SEARCHED_PLMN_INFO_IND_STRU */
                                                    /*����������������PLMN����Ϣ�ϱ�*/

    RRMM_USING_FREQ_IND                 = 0x009B,   /* _H2ASN_MsgChoice RRMM_USING_FREQ_IND_STRU */

    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, begin */
    RRMM_CONNECTED_LOCATION_INFO_IND    = 0x009D,   /* _H2ASN_MsgChoice RRMM_CONNECTED_LOCATION_INFO_IND_STRU */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, end */

    NAS_RRC_MSG_TYPE_BUTT               = 0xFFFF
};
typedef VOS_UINT16 NAS_RRC_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRMM_CELL_RESEL_PROC_ENUM
 �ṹ˵��  : ԭ���ucCellReselProcȡֵ��С����ѡ���̺궨��
*****************************************************************************/
enum RRMM_CELL_RESEL_PROC_ENUM
{
    RRMM_CELL_RESEL_START           = 0,
    RRMM_CELL_RESEL_FINISH          = 1,
    RRMM_CELL_RESEL_BUTT
};
typedef VOS_UINT8 RRMM_CELL_RESEL_PROC_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_CN_DOMAIN_TYPE_ENUM
 �ṹ˵��  : ԭ���enCnDomainIdȡֵ,CN���ʶ
*****************************************************************************/
enum RRC_NAS_CN_DOMAIN_TYPE_ENUM
{
    RRC_NAS_CS_DOMAIN                   = 0,
    RRC_NAS_PS_DOMAIN                   = 1,
    RRC_NAS_INVALID_DOMAIN              = 3,
    RRC_NAS_CN_DOMAIN_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_PPP_VALID_ENUM
 �ṹ˵��  : RRRABM_RAB_INFO_STRU,PPP�Ƿ�Ϸ���
*****************************************************************************/
enum RRC_NAS_PPP_VALID_ENUM
{
    RRC_NAS_PPP_VALID                   = 0,
    RRC_NAS_PPP_INVALID                 = 1
};
typedef VOS_UINT32 RRC_NAS_PPP_VALID_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_PLMN_SEARCH_TYPE_ENUM
 �ṹ˵��  : RRMM_PLMN_SEARCH_REQ_STRU��Ϣ�е�enSearchType
*****************************************************************************/
enum RRC_PLMN_SEARCH_TYPE_ENUM
{
    RRC_PLMN_SEARCH_SPEC                = 0,                /* ָ����PLMN������ */
    RRC_PLMN_SEARCH_LIST                = 1,                /* PLMN�б������   */
    RRC_PLMN_SEARCH_SPEC_FAST           = 2,                /* ָ����PLMN�����������е�BAND */

    RRC_PLMN_SEARCH_NCELL_SPEC          = 3,                /* SVLTE���Կ���ʱ����modem1 g�ϱ���TDS����Ƶ����Ϣ�������� */

    RRC_PLMN_SEARCH_HISTORY             = 4,                /*��ʷ��Ϣ����*/
    RRC_PLMN_SEARCH_GET_GEO             = 5,                /*��ȡ������Ϣ */

    RRC_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 RRC_PLMN_SEARCH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_PLMN_SEARCH_RLT_ENUM
 �ṹ˵��  : RRMM_PLMN_SEARCH_CNF_STRU��Ϣ�е�enSearchRlt
*****************************************************************************/
enum RRC_PLMN_SEARCH_RLT_ENUM
{
    RRC_PLMN_SEARCH_RLT_SPEC            = 0,                /* ָ����PLMN ID �����ɹ� */
    RRC_PLMN_SEARCH_RLT_LIST            = 1,                /* PLMN List�����ɹ�      */
    RRC_PLMN_SEARCH_RLT_SPEC_FAIL       = 2,                /* ָ��PLMN ID����ʧ��    */
    RRC_PLMN_SEARCH_RLT_LIST_REJ        = 3,
    RRC_PLMN_SEARCH_RLT_LIST_FAIL       = 4,                /* ����D̬��F̬����plmn list�ѻص�ԭ��ֵ */

    RRC_PLMN_SEARCH_RLT_SPEC_NO_RF      = 5,                /* ָ������Դ����ʧ�� */
    RRC_PLMN_SEARCH_RLT_LIST_NO_RF      = 6,                /* list����Դ����ʧ�� */
    RRC_PLMN_SEARCH_RLT_HISTORY_SUCC    = 7,
    RRC_PLMN_SEARCH_RLT_HISTORY_FAIL    = 8,
    RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF   = 9,
    RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC    = 10,
    RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL    = 11,
    RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF   = 12,

    RRC_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT32  RRC_PLMN_SEARCH_RLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_AREA_LOST_ENUM
 �ṹ˵��  : RRMM_AREA_LOST_IND_STRU��Ϣ�е�enRptMode
*****************************************************************************/
enum RRC_NAS_AREA_LOST_ENUM
{
    RRC_NAS_SERVICE_AREA_LOST           = 0,                /* ��������ʧ */
    RRC_NAS_COVERAGE_AREA_LOST          = 1,                /* ��������ʧ */
    RRC_NAS_NO_RF_AREA_LOST    = 2,                /* ����NO RF���µĵ��� */
    RRC_NAS_AREA_LOST_BUTT
};
typedef VOS_UINT32  RRC_NAS_AREA_LOST_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_SIM_STATUS_ENUM
 �ṹ˵��  : RRMM_START_REQ_STRU��Ϣ�е�enSimStatus
             RRMM_UICC_STATUS_CHANGE_IND_ST
*****************************************************************************/
enum RRC_NAS_SIM_STATUS_ENUM
{
    RRC_NAS_UICC_ABSENT                 = 0,                /* �������� */
    RRC_NAS_USIM_PRESENT                = 1,                /* ������,������Ϊ USIM �� */
    RRC_NAS_SIM_PRESENT                 = 2,                /* ������,������Ϊ SIM ��  */
    RRC_NAS_SIM_STATUS_BUTT
};
typedef VOS_UINT32  RRC_NAS_SIM_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_SIM_STATUS_ENUM
 �ṹ˵��  : RRMM_START_REQ_STRU��Ϣ�е�enRat
*****************************************************************************/
enum RRC_NAS_RAT_TYPE_ENUM
{
    RRC_NAS_RAT_WCDMA_FDD               = 0,                /* only WCDMA    */
    RRC_NAS_RAT_WCDMA_GSM               = 1,                /* WCDMA and GSM */
    RRC_NAS_RAT_GSM                     = 2,                /* only GSM      */
    RRC_NAS_RAT_LTE                     = 3,
    /* NetScan Add Begin */
    RRC_NAS_RAT_TD_SCDMA                = 4,                /* only TD-SCDMA */
    /* NetScan Add End */
    RRC_NAS_RAT_TYPE_BUTT
};
typedef VOS_UINT32  RRC_NAS_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM
 �ṹ˵��  : RRMM_PLMN_SEARCH_CNF_STRU��Ϣ�е�LIST����������
*****************************************************************************/
enum RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM
{
    RRC_NAS_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST����δ����        */
    RRC_NAS_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST����������,������� */
    RRC_NAS_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST�������          */
    RRC_NAS_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT32  RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRMM_SYS_CFG_RESULT_ENUM
 �ṹ˵��  : RRMM_SYS_CFG_CNF��Ϣ�е�ulResult;
*****************************************************************************/
enum RRMM_SYS_CFG_RESULT_ENUM
{
    RRMM_SYS_CFG_RESULT_SUCCESS         = 0,
    RRMM_SYS_CFG_RESULT_FAILURE         = 1,
    RRMM_SYS_CFG_RESULT_BUTT
};
typedef VOS_UINT32  RRMM_SYS_CFG_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_START_RESULT_ENUM
 �ṹ˵��  : RRMM_START_CNF_STRU��Ϣ�е�enResult
*****************************************************************************/
enum MMC_START_RESULT_ENUM
{
    MMC_START_SUCCESS                   = 0,
    MMC_START_FAILURE                   = 1,
    MMC_START_BUTT
};
typedef VOS_UINT32 MMC_START_RESULT_ENUM_UINT32;


enum RRC_NAS_RESEL_TYPE_ENUM
{
    RRC_NAS_CELL_SELECTION              = 0,
    RRC_NAS_RESEL_SUITABLE              = 1,
    RRC_NAS_FORBLA_CHANGE               = 2,
    RRC_NAS_RESEL_BUTT
};
typedef VOS_UINT32  RRC_NAS_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_CALL_TYPE_ENUM
 �ṹ˵��  : RRMM_EST_REQ_STRU enEstCause
*****************************************************************************/
enum RRC_NAS_CALL_TYPE_ENUM
{
    RRC_NAS_CALL_TYPE_SPEECH            = 0,
    RRC_NAS_CALL_TYPE_VIDEO             = 1,
    RRC_NAS_CALL_TYPE_OTHER             = 2,
    RRC_NAS_CALL_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_EST_CAUSE_ENUM
 �ṹ˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause
*****************************************************************************/
enum RRC_NAS_EST_CAUSE_ENUM
{
    RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL             = 0,
    RRC_EST_CAUSE_ORIGIN_STREAM_CALL                = 1,
    RRC_EST_CAUSE_ORIGIN_INTERACT_CALL              = 2,
    RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL            = 3,
    RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL      = 4,
    RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL           = 5,
    RRC_EST_CAUSE_TERMINAT_STREAM_CALL              = 6,
    RRC_EST_CAUSE_TERMINAT_INTERACT_CALL            = 7,
    RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL          = 8,
    RRC_EST_CAUSE_EMERGENCY_CALL                    = 9,
    RRC_EST_CAUSE_INTER_RAT_CELL_RESELECT           = 10,
    RRC_EST_CAUSE_INTER_RAT_CELL_CHANGE_ORDER       = 11,
    RRC_EST_CAUSE_REGISTRATION                      = 12,
    RRC_EST_CAUSE_DETACH                            = 13,
    RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL       = 14,
    RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL        = 15,
    RRC_EST_CAUSE_CALL_RE_ESTABLISH                 = 16,
    RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL     = 17,
    RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL      = 18,
    RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN            = 19,
	RRC_EST_CAUSE_EMERGENCY_CALL_RE_ESTABLISH       = 20,
    RRC_EST_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_NAS_EST_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_IDNNS_TYPE_ENUM
 �ṹ˵��  : RRMM_EST_REQ_STRU enIdnns ȡֵ
*****************************************************************************/
enum RRC_NAS_IDNNS_TYPE_ENUM
{
    RRC_IDNNS_LOCAL_TMSI                = 0,
    RRC_IDNNS_TMSI_DIFFER_LA            = 1,
    RRC_IDNNS_TMSI_DIFFER_PLMN          = 2,
    RRC_IDNNS_IMSI_PAGE_RSP             = 3,
    RRC_IDNNS_IMSI_UE_INIT              = 4,
    RRC_IDNNS_IMEI                      = 5,

    RRC_IDNNS_CSFB_LOCAL_TMSI           = 6,        /* mt csfb��Gʱʹ�ã�paging request��Ϣ��ָʾmobile identity typeΪs-tmsi����
                                                       cs service notification��Ϣ��ָʾmobile identity typeΪtmsi */
    RRC_IDNNS_CSFB_LOCAL_IMSI           = 7,        /* mt csfb��Gʱʹ�ã�paging request��Ϣ��cs service notification��Ϣ��ָʾmobile identity typeΪimsi*/

	RRC_NAS_IDNNS_BUTT
};
typedef VOS_UINT32 RRC_NAS_IDNNS_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_RRC_SPLMN_SAME_RPLMN_ENUM
 �ṹ˵��  : RRMM_EST_REQ_STRU enSplmnSameRplmn ȡֵ
*****************************************************************************/
enum NAS_RRC_SPLMN_SAME_RPLMN_ENUM
{
    NAS_RRC_SPLMN_SAME_RPLMN                       = 0,     /* ѡ���PLMN��RPLMNһ�� */
    NAS_RRC_SPLMN_DIFF_RPLMN                       = 1,     /* ѡ���PLMN��RPLMN��һ�� */
    NAS_RRC_SPLMN_RPLMN_BUTT
};
typedef VOS_UINT32 NAS_RRC_SPLMN_SAME_RPLMN_ENUM_UINT32;


/*****************************************************************************
 ö����    : RRC_NAS_EST_RESULT_ENUM
 �ṹ˵��  : RRMM_EST_CNF_STRU enResultȡֵ
*****************************************************************************/
enum RRC_NAS_EST_RESULT_ENUM
{
    RRC_EST_SUCCESS                     = 0,                /* �������ӽ����ɹ�                     */
    RRC_EST_PRESENT                     = 1,                /* �����������Ѿ�����                   */
    RRC_EST_ESTING                      = 2,                /* �������������ڽ���                   */
    RRC_EST_DELING                      = 3,                /* ���������������ͷ�                   */
    RRC_EST_RJ_CONGEST                  = 4,                /* RRC Connection Reject: Congestion    */
    RRC_EST_RJ_UNSPEC                   = 5,                /* RRC Connection Reject: Unspecified   */
    RRC_EST_ACCESS_BARRED               = 6,                /* access barred because of AC control  */
    RRC_EST_EST_CONN_FAIL               = 7,                /* RR connection establish failure      */
    RRC_EST_RJ_INTER_RAT                = 8,                /* RR connection Reject: ָʾ������ϵͳ */
    RRC_EST_IMMEDIATE_ASSIGN_REJECT     = 9,                /* �����Ľ�����̣�����RA������յ�����ָ�ɾܾ���Ϣ��
                                                               û���յ�����ָ����Ϣ�����µĽ���ʧ�� */
    RRC_EST_RANDOM_ACCESS_REJECT        = 10,               /* �����Ľ�����̣�����RA�����û���յ�����������ָ�ɣ�
                                                               Ҳû���յ�����ָ�ɾܾ�������ʧ�� */
    RRC_EST_PAGING_ACCESS_BARRED        = 11,               /*Paging Restriction(PPAC����)*/
    RRC_EST_REGISTER_ACCESS_BARRED      = 12,                /*Location/Registration Restriction(PPAC����)*/
    RRC_EST_OTHER_ACCESS_BARRED         = 13,

    RRC_EST_RJ_T3122_RUNNING            = 14,               /* G������ָ�ɱ�������T3122����T3122�����ڼ�ظ��������� */

    RRC_EST_RJ_NO_RF                       = 15,               /* ����RF�����õ��µ�RRC����ʧ�� */

    RRC_EST_RJ_SNW                       = 16,               /* AS����״̬RRC�ظ�����ʧ�� */

    RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO        = 17,   /* ��G��ʹ�ã�δͬ��������� */

    RRC_EST_RJ_RA_FAIL                      = 18,           /* GAS����RA�ﵽ��������GPHYһֱû�лظ����ͳɹ�, */
    RRC_EST_RJ_NOT_ALLOW                    = 19,           /* MM�㷢��Ľ���������������,�����յ�����ָ�ɣ�������ʱ���ڼ䲻�����ٴη������ */
    RRC_EST_RJ_TIME_OUT                     = 20,           /* ����CS���ӹ����е�ģ���ı�����ʱ����ʱ,GAS,TDRRC����ʹ�� */
    RRC_EST_RJ_RA_RESOURCE_FAIL             = 21,           /* �������������Դʧ��; */
    RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID     = 22,           /* �յ�������ָ�ɷǷ� */
    RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL = 23,           /* �ŵ�ָ�ɹ����м��������ŵ�ʧ��*/
    RRC_EST_RJ_AIRMSG_DECODE_ERR            = 24,           /* �տ���Ϣ������� */
    RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT    = 25,           /* ��ǰδפ�� */
    RRC_EST_RJ_INVALID_UE_STATE             = 26,           /* �����UE״̬  */
    RRC_EST_RJ_CELL_BAR                     = 27,           /* С����bar */
    RRC_EST_RJ_FASTRETURN_LTE               = 28,           /* FASTRETURN_LTE */
    RRC_EST_RJ_RA_FAIL_NO_VALID_INFO        = 29,           /* ��G��ʹ��,GAS����RA�ﵽ��������GPHYһֱû�лظ����ͳɹ�,δͬ��������� */

    RRC_NAS_EST_RESULT_BUTT
};
typedef VOS_UINT32 RRC_NAS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_EST_RESULT_ENUM
 �ṹ˵��  : RRMM_DATA_REQ_STRU enPriorityIndȡֵ
*****************************************************************************/
enum RRC_NAS_MSG_PRIORTY_ENUM
{
    RRC_NAS_MSG_PRIORTY_LOW             = 0,                /* ��Ϣ���ȼ���Low  */
    RRC_NAS_MSG_PRIORTY_HIGH            = 1,                /* ��Ϣ���ȼ���High */
    RRC_NAS_MSG_PRIORTY_BUTT
};
typedef VOS_UINT32 RRC_NAS_MSG_PRIORTY_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_CELL_BAR_ENUM
 �ṹ˵��  : RRMM_ABORT_REQ_STRU enBarValidFlgȡֵ
*****************************************************************************/
enum RRC_CELL_BAR_ENUM
{
    RRC_CELL_BARRED                     = 0,                /* ԭ����WUEPS_TRUE */
    RRC_CELL_UNBARRED                   = 1,                /* ԭ����WUEPS_FALSE */
    RRC_CELL_BAR_BUTT
};
typedef VOS_UINT32 RRC_CELL_BAR_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_EST_RESULT_ENUM
 �ṹ˵��  : RRMM_REL_IND_STRU enRrcConnStatusȡֵ
*****************************************************************************/
enum RRC_RRC_CONN_STATUS_ENUM
{
    RRC_RRC_CONN_STATUS_PRESENT         = 0,                /* ԭ�Ƚӿ�WUEPS_TRUE��RRC Connection����    */
    RRC_RRC_CONN_STATUS_ABSENT          = 1,                /* ԭ�Ƚӿ�WUEPS_FALSE��RRC Connection������ */
    RRC_RRC_CONN_STATUS_BUTT
};
typedef VOS_UINT32 RRC_RRC_CONN_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_LIMIT_CAMP_ACTION_ENUM
 �ṹ˵��  : RRMM_LIMIT_SERVICE_CAMP_IND_STRU enLimitCampAction��ȡֵ
*****************************************************************************/
enum RRC_LIMIT_CAMP_ACTION_ENUM
{
    RRC_LIMIT_CAMP_ACTION_START         = 0,                /* ���Ʒ���ʼ */
    RRC_LIMIT_CAMP_ACTION_END           = 1,                /* ���Ʒ������ */
    RRC_LIMIT_CAMP_ACTION_BUTT
};
typedef VOS_UINT32 RRC_LIMIT_CAMP_ACTION_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_EST_RESULT_ENUM
 �ṹ˵��  : RRMM_REL_IND_STRU enRelCauseȡֵ
*****************************************************************************/
enum RRC_REL_CAUSE_ENUM
{
    /* RRC Connection Release��Ϣ�е�ԭ�� */
    RRC_REL_CAUSE_RR_NORM_EVENT                 = 0,        /* Normal event                             */
    RRC_REL_CAUSE_RR_UNSPEC                     = 1,        /* Unspecified                              */
    RRC_REL_CAUSE_RR_PRE_EMPT_REL               = 2,        /* Pre-emptive release                      */
    RRC_REL_CAUSE_RR_CONGEST                    = 3,        /* Congedtion                               */
    RRC_REL_CAUSE_RR_RE_EST_REJ                 = 4,        /* Re-establishment reject                  */
    RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST       = 5,        /* Directed signal conn re-establish        */
    RRC_REL_CAUSE_RR_USER_INACT                 = 6,        /* User inactive                            */
    RRC_REL_CAUSE_UTRAN_RELEASE                 = 7,        /* Signaling Connection Release,RRC�յ�Signaling Connection Release��Ϣ */
    /* NASָʾ�ͷ� */
    RRC_REL_CAUSE_NAS_REL_SUCCESS               = 8,        /* NAS Release Connection��Successful       */
    RRC_REL_CAUSE_NAS_REL_ABSENT                = 9,        /* NAS Release Connection: Absent           */
    RRC_REL_CAUSE_NAS_ABORT                     = 10,       /* NAS : Abort                              */
    RRC_REL_CAUSE_NAS_STOP_SETUP                = 11,       /* NAS Stop connection setup                */
    /* ���� */
    RRC_REL_CAUSE_CONN_FAIL                     = 12,       /* RR Connection Failure                    */
    RRC_REL_CAUSE_NAS_DATA_ABSENT               = 13,       /* NAS Data Request: Connection Absent      */
    RRC_REL_CAUSE_RRC_ERROR                     = 14,       /* RRC�����쳣: RRC ERROR                   */
    RRC_REL_CAUSE_RL_FAILURE                    = 15,       /* Radio Link Failure                       */
    RRC_REL_CAUSE_GAS_TIMEOUT                   = 16,       /* GAS ��������ʱ���� RR �����ͷ�           */
    RRC_REL_CAUSE_OTHER_REASON                  = 17,       /* ����ԭ��                                 */
    RRC_REL_CAUSE_NO_RF                         = 18,       /* û����Ƶ��Դ,DSDS���� */

    RRC_REL_CAUSE_RLC_ERROR                     = 19,       /* RLC���ɻָ����� */
    RRC_REL_CAUSE_CELL_UPDATE_FAIL              = 20,       /* CELL Updateʧ��,TDʹ�� */
    RRC_REL_CAUSE_T314_EXPIRED                  = 21,       /* CS����·���ڣ�����̬��ʧ������ʧ�ܣ�T314��ʱ */
    RRC_REL_CAUSE_T315_EXPIRED                  = 22,       /* PS����·���ڣ�����̬��ʧ������ʧ�ܣ�T315��ʱ */
    RRC_REL_CAUSE_W_RL_FAIL                     = 23,       /* ��W��ʹ�ã�Radio linkʧ�ܣ������������ؽ� */

    RRC_REL_CAUSE_G_RL_FAIL                     = 24,       /* ��G��ʹ�ã�Radio linkʧ�ܣ������������ؽ� */


    RRC_REL_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_AC_TYPE_ENUM
 �ṹ˵��  : RRMM_AC_INFO_CHANGE_IND_STRU enAcChangeIndȡֵ
*****************************************************************************/
enum RRC_NAS_AC_TYPE_ENUM
{
    RRC_NAS_AC_NOT_BAR                  = 0,                /* ����һ��AC���ڲ����� */
    RRC_NAS_T3122_EXPIRE                = 1,
    RRC_NAS_AC_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_AC_TYPE_ENUM_UINT32;
enum MMC_SUSPEND_CAUSE_ENUM
{
    MMC_SUSPEND_CAUSE_HANDOVER              = 0x00,
    MMC_SUSPEND_CAUSE_CELLRESELECT          = 0x01,
    MMC_SUSPEND_CAUSE_CELLCHANGE            = 0x02,
    MMC_SUSPEND_CAUSE_PLMNSEARCH            = 0x03,  /* ����ԭ��ֵ����WAS��ҪGAS����PLMN����ʱ������NAS��ԭ��ԭ��ֵ */
    MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK   = 0x04,  /* ����ԭ��ֵ��������ϵͳCCO����ʧ�ܻ�����NASָʾ�Ĺ�������    */
    MMC_SUSPEND_CAUSE_REDIRECTION           = 0x05,  /* ����ԭ��ֵ, ������ϵͳ�ض���ʱ,GU��������NASָʾ�Ĺ������� */
    MMC_SUSPEND_CAUSE_BUTT
};

typedef VOS_UINT8 MMC_SUSPEND_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_AC_TYPE_ENUM
 �ṹ˵��  : RRMM_SUSPEND_IND_ST enSuspendOrigen
*****************************************************************************/
enum MMC_SUSPEND_ORIGEN_ENUM
{
    MMC_SUSPEND_ORIGEN_GSM              = 0x00,
    MMC_SUSPEND_ORIGEN_WCDMA            = 0x01,
    MMC_SUSPEND_ORIGEN_LTE              = 0x02,
    MMC_SUSPEND_ORIGEN_BUTT
};
typedef VOS_UINT8 MMC_SUSPEND_ORIGEN_UINT8;


/*****************************************************************************
 ö����    : MMC_SUSPEND_DESTINATION_UINT8
 �ṹ˵��  : MMC_SUSPEND_DESTINATION_UINT8 enSuspendDest
*****************************************************************************/
enum MMC_SUSPEND_DESTINATION
{
    MMC_SUSPEND_DESTINATION_GSM              = 0x00,
    MMC_SUSPEND_DESTINATION_WCDMA            = 0x01,
    MMC_SUSPEND_DESTINATION_LTE              = 0x02,
    MMC_SUSPEND_DESTINATION_HRPD             = 0x03,
    MMC_SUSPEND_DESTINATION_BUTT
};
typedef VOS_UINT8 MMC_SUSPEND_DESTINATION_UINT8;

/*****************************************************************************
 ö����    : MMC_RE_TRANS_MSG_TYPE_ENUM
 �ṹ˵��  : �����л�������£�L3֪ͨNAS��Ҫ�ط���ֱ����Ϣ������
*****************************************************************************/
enum NAS_RRC_RE_TX_MSGTYPE_ENUM
{
    NAS_RRC_NULL_RE_TX_MSG              = 0,                /* û����Ϣ��Ҫ�ش� */
    NAS_RRC_RE_TX_EST_REQ_MSG           = 1,                /* EST_REQ��Ϣ */
    NAS_RRC_RE_TX_DATA_REQ_MSG          = 2,                /* DATA_REQ��Ϣ */
    NAS_RRC_RE_TX_MSGTYPE_BUTT
};
typedef VOS_UINT32 NAS_RRC_RE_TX_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_AC_TYPE_ENUM
 �ṹ˵��  : RRMM_SUSPEND_RSP_ST enResult ȡֵ
*****************************************************************************/
enum RRC_NAS_SUSPEND_RESULT_ENUM
{
    RRC_NAS_SUSPEND_SUCCESS             = 0x00,
    RRC_NAS_SUSPEND_FAILURE             = 0x01
};
typedef VOS_UINT8 RRC_NAS_SUSPEND_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_RESUME_RESULT_ENUM
 �ṹ˵��  : RRMM_RESUME_IND_ST enResult ȡֵ
*****************************************************************************/
enum MMC_RESUME_RESULT_ENUM
{
    MMC_RESUME_RESULT_SUCCESS           = 0x00,
    MMC_RESUME_RESULT_FAILURE           = 0x01,
    MMC_RESUME_GPRS_SUSPENSION          = 0x02,
    MMC_RESUME_RESULT_BUTT
};
typedef VOS_UINT8 MMC_RESUME_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_RESUME_RESULT_ENUM
 �ṹ˵��  : RRMM_RESUME_IND_ST  enCsResumeResult,enPsResumeResult
*****************************************************************************/
enum MMC_RESUME_ORIGEN_ENUM
{
    MMC_RESUME_ORIGEN_GSM               = 0x00,
    MMC_RESUME_ORIGEN_WCDMA             = 0x01,
    MMC_RESUME_ORIGEN_LTE               = 0x02,

    MMC_RESUME_ORIGEN_HRPD              = 0x03,

    MMC_RESUME_ORIGEN_BUTT
};
typedef VOS_UINT8 MMC_RESUME_ORIGEN_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_AS_SUSPEND_STOP_ENUM
 �ṹ˵��  : ����ֹͣ��ʽ����ֵ
             RRMM_SUSPEND_REQ_ST enStopCause
*****************************************************************************/
enum MMC_AS_SUSPEND_STOP_ENUM
{
    MMC_AS_SUSPEND_STOP                 = 0x00,             /* ����ֹͣ��ǰ����㣬�����Ƴ�DSP */
    MMC_AS_SUSPEND_STOP_DSP             = 0x01,             /* ����ֹͣ��ǰ����㣬�Ƴ�DSP */
    MMC_AS_SUSPEND_STOP_BUTT
};
typedef VOS_UINT8 MMC_AS_SUSPEND_STOP_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_AS_SUSPEND_STOP_ENUM
 �ṹ˵��  : ��������������ֵ
             RRMM_SUSPEND_CNF_ST enResult
*****************************************************************************/
enum MMC_AS_SUSPEND_RESULT_ENUM
{
    MMC_AS_SUSPEND_SUCCESS              = 0x00,             /* ��ǰ��������ɹ�������㹦�ܽ�ת���µĽ���㴦�� */
    MMC_AS_SUSPEND_FAILURE              = 0x01,             /* ��ǰ��������ʧ�ܣ���ǰ��������ṩ����㹦�� */
    MMC_AS_SUSPEND_RESULT_BUTT
};
typedef VOS_UINT8 MMC_AS_SUSPEND_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : AS_UICC_STATUS_IND_RESULT_ENUM
 �ṹ˵��  : ��������������ֵ
             RRMM_UICC_STATUS_CHANGE_RSP_ST enResult
*****************************************************************************/
enum AS_UICC_STATUS_IND_RESULT_ENUM
{
    AS_UICC_STATUS_IND_SUCCESS          = 0,
    AS_UICC_STATUS_IND_FAIL             = 1,
    AS_UICC_STATUS_IND_BUTT
};
typedef VOS_UINT32 AS_UICC_STATUS_IND_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_SECURITY_RPT_MODE_ENUM
 �ṹ˵��  : RRMM_SECURITY_IND_STRU enRptModeȡֵ
*****************************************************************************/
enum RRC_SECURITY_RPT_MODE_ENUM
{
    RRC_SECURITY_CS_SMC_CMPL            = 0,                /* һ��CS SMC���̽���                       */
    RRC_SECURITY_DEL_CS_KEY             = 1,                /* USIM��CS��CK��IK��ɾ��                   */
    RRC_SECURITY_DEL_PS_KEY             = 2,                /* USIM��PS��CK��IK��ɾ��                   */
    RRC_SECURITY_DEL_CS_PS_KEY          = 3,                /* USIM��CS+PS��CK��IK��ɾ��                */
    RRC_SECURITY_CS_SMC_RCV             = 4,                /* �յ���Ч��CS SMC��Ϣ                     */
    RRC_SECURITY_PS_SMC_RCV             = 5,                /* �յ���Ч��PS SMC��Ϣ                     */
    RRC_SECURITY_PS_SMC_CMPL            = 6,                /* һ��PS SMC���̽���                       */
    RRC_SECURITY_RB_CTRL_MSG            = 7,                /* �յ�������Ϣ�޸ļ����㷨                 */
    RRC_SECURITY_MOBI_MSG               = 8,                /* �յ�CELL/URA UPDATE CNF��Ϣ�޸ļ����㷨  */
    RRC_SECURITY_RPT_MODE_BUTT
};
typedef VOS_UINT32 RRC_SECURITY_RPT_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_PDCP_EXIST_FLAG_ENUM
 �ṹ˵��  : RAB_INFO_STRU ��Ϣ�� enPdcpFlg
             ��ʶ��Ӧ��RAB PDCP�Ƿ����
*****************************************************************************/
enum RRC_NAS_PDCP_EXIST_FLAG_ENUM
{
    RRC_NAS_PDCP_NOT_EXIST              = 0,
    RRC_NAS_PDCP_EXIST                  = 1,
    RRC_NAS_PDCP_EXIST_FLAG_BUTT
};
typedef VOS_UINT32 RRC_NAS_PDCP_EXIST_FLAG_ENUM_UINT32;



/*****************************************************************************
 ö����    : RRC_NAS_PAGING_TYPE_ENUM
 �ṹ˵��  : RRMM_PAGING_IND_STRU enPagingTypeȡֵ
*****************************************************************************/
enum RRC_NAS_PAGING_TYPE_ENUM
{
    RRC_NAS_PAGING_TYPE1                = 0,                /* Paging Type 1 */
    RRC_NAS_PAGING_TYPE2                = 1,                /* Paging Type 2 */
    RRC_NAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_PAGING_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_PAGE_CAUSE_ENUM
 �ṹ˵��  : RRMM_PAGING_IND_STRU enPagingCauseȡֵ
*****************************************************************************/
enum RRC_PAGE_CAUSE_ENUM
{
    RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL          = 0,
    RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL             = 1,
    RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL           = 2,
    RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL         = 3,
    RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL    = 4,
    RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL     = 5,
    RRC_PAGE_CAUSE_TERMINAT_CAUSE_UNKNOWN           = 6,
    RRC_PAGE_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_PAGE_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_PAGE_UE_ID_ENUM
 �ṹ˵��  : RRMM_PAGING_IND_STRU enPagingUeIdȡֵ
*****************************************************************************/
enum RRC_PAGE_UE_ID_ENUM
{
    RRC_IMSI_GSM_MAP                    = 0,                /* used for Paging Type 1/2 */
    RRC_TMSI_GSM_MAP_P_TMSI             = 1,                /* used for Paging Type 1   */
    RRC_IMSI_DS41                       = 2,                /* used for Paging Type 1/2 */
    RRC_TMSI_DS41                       = 3,                /* used for Paging Type 1/2 */
    RRC_P_TMSI_GSM_MAP                  = 4,                /* used for Paging Type 1   */
    RRC_PAGE_UE_ID_BUTT
};
typedef VOS_UINT32 RRC_PAGE_UE_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_PAGE_UE_ID_ENUM
 �ṹ˵��  : RRRABM_RAB_IND_STRU enRabChangeTypeȡֵ
             RRRABM_HANDOVER_RAB_IND_STRU
*****************************************************************************/
enum NAS_RRC_RAB_CHANGE_ENUM
{
    NAS_RRC_RAB_SETUP_REQUEST           = 0,                /* �������µ�RAB   */
    NAS_RRC_RAB_SETUP_SUCCESS           = 1,                /* �ɹ������µ�RAB   */
    NAS_RRC_RAB_SETUP_FAILURE           = 2,                /* �����µ�RABʧ��   */
    NAS_RRC_RAB_RECONFIG                = 3,                /* �����Ѿ�������RAB */
    NAS_RRC_RAB_RELEASE                 = 4,                /* �ͷ��Ѿ�������RAB */
    NAS_RRC_RAB_CHANGE_BUTT
};
typedef VOS_UINT32 NAS_RRC_RAB_CHANGE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_RAB_STATUS_ENUM
 �ṹ˵��  : RRRABM_STATUS_IND_STRU enStatusȡֵ
*****************************************************************************/
enum RRC_RAB_STATUS_ENUM
{
    RRC_RAB_STATUS_STOP                 = 0,                /* ֹͣ���ݴ��� */
    RRC_RAB_STATUS_CONTINUE             = 1,                /* �ָ����ݴ��� */
    RRC_RAB_STATUS_BUTT
};
typedef VOS_UINT32 RRC_RAB_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_ATTACH_STATUS_ENUM
 �ṹ˵��  : NAS_INFO_STRU enAttachȡֵ
*****************************************************************************/
enum RRC_NAS_ATTACH_STATUS_ENUM
{
    RRC_NAS_ATTACH                      = 0,
    RRC_NAS_NOT_ATTACH                  = 1,
    RRC_NAS_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_USIM_STATUS_ENUM
 �ṹ˵��  : NAS_INFO_STRU enUsimValidȡֵ
*****************************************************************************/
enum RRC_NAS_USIM_STATUS_ENUM
{
    RRC_NAS_USIM_VALID                  = 0,
    RRC_NAS_USIM_INVALID                = 1,
    RRC_NAS_USIM_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_USIM_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_AT_ACTION_ENUM
 �ṹ˵��  : RRMM_AT_MSG_REQ_ST enActionType��ȡֵ
*****************************************************************************/
enum RRC_NAS_AT_ACTION_ENUM
{
    RRC_NAS_AT_START_FOREVER            = 0,                /* ָʾWRRC�������� */
    RRC_NAS_AT_START_ONCE               = 1,                /* ָʾWRRC��������һ�� */
    RRC_NAS_AT_STOP                     = 2,                /* ָʾWRRCֹͣ */
    RRC_NAS_AT_ACTION_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_ACTION_ENUM_UINT8;
enum RRC_NAS_AT_MSG_TYPE_ENUM
{
    RRC_NAS_AT_CELL_SIGN                = 1,                /* ��ʾ��ȡС����Ϣǿ�� */
    RRC_NAS_AT_CELL_ID                  = 2,                /* ��ʾ��ȡС��ID */
    RRC_NAS_AT_CELL_BLER                = 4,                /* ��ʾ��ȡ�ŵ������� */
    RRC_NAS_AT_CELL_SUBMODE             = 8,
    RRC_NAS_AT_MSG_TYPE_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_TYPE_ENUM_UINT8;
enum RRC_NAS_AT_MSG_SUBMODE_ENUM
{
   RRC_NAS_AT_R99_ONLY                 ,             /* ��ʾֻ��R99�������  */
   RRC_NAS_AT_HSDPA_ONLY               ,             /* ��ʾ��HSDPA�������� */
   RRC_NAS_AT_HSUPA_ONLY               ,             /* ��ʾ��HSUPA�������� */
   RRC_NAS_AT_HSDPA_AND_HSUPA          ,              /* ��ʾͬʱ����HSDPA��HSUPA*/
   RRC_NAS_AT_HSPA_PLUS                ,              /* ��ʾ����HSPA+*/
   RRC_NAS_AT_DC_HSPA_PLUS             ,              /* ��ʾ����DC+HSPA+*/
   RRC_NAS_AT_DC_MIMO                  ,              /* ��ʾ����DC+MIMO*/
   RRC_NAS_AT_MSG_RAT_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_SUBMODE_ENUM_UINT8;



/*****************************************************************************
 ö����    : RRC_NAS_AT_MSG_FLAG_ENUM
 �ṹ˵��  : RRMM_AT_MSG_CNF_ST enMsgFlg��ȡֵ
*****************************************************************************/
enum RRC_NAS_AT_MSG_FLAG_ENUM
{
    RRC_NAS_AT_VALID                    = 0,
    RRC_NAS_AT_INVALID                  = 1,
    RRC_NAS_AT_MSG_FLAG_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_WCDMA_BAND_TYPE_ENUM
 �ṹ˵��  : RRMM_SET_WCDMA_BAND_REQ_ST enWasDlFreqInfo
*****************************************************************************/
enum NAS_WCDMA_BAND_TYPE_ENUM
{
    NAS_WCDMA_BAND_TYPE_NULL            = 0x0,
    NAS_WCDMA_BAND_TYPE_800             = 0x0001,
    NAS_WCDMA_BAND_TYPE_850             = 0x0002,
    NAS_WCDMA_BAND_TYPE_900             = 0x0004,
    NAS_WCDMA_BAND_TYPE_1800            = 0x0010,
    NAS_WCDMA_BAND_TYPE_1900            = 0x0020,
    NAS_WCDMA_BAND_TYPE_2100            = 0x0100,
    NAS_WCDMA_BAND_TYPE_ANY             = 0x01ff,
    NAS_WCDMA_BAND_TYPE_BUTT
};
typedef VOS_UINT32 NAS_WCDMA_BAND_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : WAS_CHANGE_BAND_RESULT_ENUM
 �ṹ˵��  : RRMM_SET_WCDMA_BAND_CNF_ST enResult
*****************************************************************************/
enum WAS_CHANGE_BAND_RESULT_ENUM
{
    WAS_CHANGE_BAND_SUCCESS             = 0,
    WAS_CHANGE_BAND_FAIL                = 1,
    WAS_CHANGE_BAND_RESULT_BUTT
};
typedef VOS_UINT32 WAS_CHANGE_BAND_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : GRRMM_MSG_REL_VER_ENUM
 �ṹ˵��  : GRRMM_SYS_INFO_IND_ST enMsrRelease
*****************************************************************************/
enum GRRMM_MSG_REL_VER_ENUM
{
    GRRMM_MSC_RELEASE98_OR_OLDER        = 0,
    GRRMM_MSC_RELEASE99_ONWARDS         = 1,
    GRRMM_MSG_REL_VER_BUTT
};
typedef VOS_UINT8   GRRMM_MSG_REL_VER_ENUM_UINT8;


enum RRC_NAS_RESTRICTION_ENUM
{
    RRC_NAS_ACCESS_NO_RESTRICTION                                   = 0,     /* ������ҵ�� */
    RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE                       = 1,     /* ��������ҵ�� */
    RRC_NAS_ACCESS_RESTRICTION_EMERGENCY_SERVICE                    = 2,     /* ��������ҵ�� */
    RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE                          = 3,     /* ��������ҵ��ͽ���ҵ�� */
    RRC_NAS_ACCESS_BUTT
};
typedef VOS_UINT8 RRC_NAS_RESTRICTION_ENUM_UINT8;


typedef struct
{
    VOS_UINT8                          ucRestrictNormalService          :1;         /* ��������ҵ�� */
    VOS_UINT8                          ucRestrictEmergencyService       :1;         /* ��������ҵ�� */
    VOS_UINT8                          ucRestrictSpare6                 :6;
}RRC_NAS_RESTRICTION_STRU;


typedef union
{
    VOS_UINT8                           ucRestrictType;

    RRC_NAS_RESTRICTION_STRU            stBitRestrictType;
}RRC_NAS_RESTRICTION_UN;



/*****************************************************************************
 ö����    : NAS_GAS_BAND_INDICATOR_ENUM
 �ṹ˵��  : GRRMM_SYS_INFO_IND_ST ucBandIndicator
*****************************************************************************/
enum GRRMM_BAND_INDICATOR_ENUM
{
    GRRMM_BAND_INDICATOR_1800             = 0,
    GRRMM_BAND_INDICATOR_1900             = 1,
    GRRMM_BAND_INDICATOR_BUTT
};
typedef VOS_UINT8 GRRMM_BAND_INDICATOR_ENUM_UINT8;


/*****************************************************************************
 ö����    : GRRMM_SGSN_REL_VER_ENUM
 �ṹ˵��  : GRRMM_SYS_INFO_IND_ST ucSgsnRelease
*****************************************************************************/
enum GRRMM_SGSN_REL_VER_ENUM
{
    GRRMM_SGSN_RELEASE98_OR_OLDER        = 0,
    GRRMM_SGSN_RELEASE99_ONWARDS         = 1,
    GRRMM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   GRRMM_SGSN_REL_VER_ENUM_UINT8;

/*****************************************************************************
 ö����    : GRRMM_NW_OP_MODE_ENUM
 �ṹ˵��  : GRRMM_SYS_INFO_IND_ST enNetworkOperationMode
*****************************************************************************/
enum GRRMM_NW_OP_MODE_ENUM
{
    GRRMM_NW_OP_MODE_INVALID            = 0,
    GRRMM_NW_OP_MODE_I                  = 1,
    GRRMM_NW_OP_MODE_II                 = 2,
    GRRMM_NW_OP_MODE_III                = 3,
    GRRMM_NW_OP_MODE_BUTT
};
typedef VOS_UINT8   GRRMM_NW_OP_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_MS_IE_TYPE_ENUM
 �ṹ˵��  : GRRMM_PAGING_IND_ST enMSIDTypeȡֵ
*****************************************************************************/
enum GAS_MS_IE_TYPE_ENUM
{
    GAS_IMSI                            = 0,                /* IMSI     */
    GAS_TMSI                            = 1,                /* TMSI     */
    GAS_PTMSI                           = 2,                /* PTMSI    */
    GAS_MS_ID_TYPE_BUTT
};
typedef VOS_UINT8   GAS_MS_IE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_PAGING_TYPE_ENUM
 �ṹ˵��  : GRRMM_PAGING_IND_ST enPagingTypeȡֵ
*****************************************************************************/
enum GAS_PAGING_TYPE_ENUM
{
    GAS_PAGING_CS                       = 0,                /* CS       */
    GAS_PAGING_PS                       = 1,                /* PS       */
    GAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT8   GAS_PAGING_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GRR_GMM_GPRS_RESUME_RESULT_ENUM
 �ṹ˵��  : RRMM_GPRS_RESUME_IND_ST enResult ȡֵ
*****************************************************************************/
enum GRR_GMM_GPRS_RESUME_RESULT_ENUM
{
    GRR_GMM_GPRS_RESUME_SUCCESS         = 0,
    GRR_GMM_GPRS_RESUME_FAILURE         = 1,
    GRR_GMM_GPRS_RESUME_RESULT_BUTT
};
typedef VOS_UINT8 GRR_GMM_GPRS_RESUME_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_GSM_MASK_ENUM
 �ṹ˵��  : GAS_NAS_INFO_ST enMaskȡֵ
*****************************************************************************/
enum NAS_GSM_MASK_ENUM
{
    NAS_GSM_MASK_ATTACH                 = 0x0001,
    NAS_GSM_MASK_USIM_INVALID           = 0x0002,
    NAS_GSM_MASK_SECURITY_KEY           = 0x0004,
    NAS_GSM_MASK_DRX                    = 0x0008,
    NAS_GSM_MASK_TMSI_LAI               = 0x0010,
    NAS_GSM_MASK_PTMSI_RAI              = 0x0020,
    NAS_GSM_MASK_DEL_KC                 = 0x0040,           /* ָʾGASɾ��ָ�����KC       */
    NAS_GSM_MASK_GSM_GMM_STATE          = 0x0080,           /* GSM������GMM״̬��Ϣ��Ч��־ */
    NAS_GSM_MASK_READY_TIMER            = 0x0100,           /* READY TIMERֵ��Ч��־        */
    NAS_GSM_MASK_MS_GPRS_MODE           = 0x0200,           /* MS GPRSģʽֵ��Ч��־ */
    NAS_GSM_MASK_MAPPED_SECURITY_KEY    = 0x0400,           /* LTE��ӳ������İ�ȫ��������Ч��־ */
    NAS_GSM_MASK_BUTT
};
typedef VOS_UINT32 NAS_GSM_MASK_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_GSM_ATTACH_TYPE_ENUM
 �ṹ˵��  : NAS_INFO_STRU enAttachȡֵ
*****************************************************************************/
enum NAS_GSM_ATTACH_TYPE_ENUM
{
    NAS_GSM_ATTACH                      = 0,
    NAS_GSM_NOT_ATTACH                  = 1,
    NAS_GSM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GSM_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_GSM_USIM_ENUM
 �ṹ˵��  : NAS_INFO_STRU enUsimValidȡֵ
*****************************************************************************/
enum NAS_GSM_USIM_ENUM
{
    NAS_GSM_USIM_VALID                  = 0,
    NAS_GSM_USIM_INVALID                = 1,
    NAS_GSM_USIM_BUTT
};
typedef VOS_UINT32 NAS_GSM_USIM_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_GMM_STATE_ENUM
 �ṹ˵��  : NAS_INFO_STRU enGsmGmmStateȡֵ
*****************************************************************************/
enum NAS_GMM_STATE_ENUM
{
    NAS_GMM_STATE_IDLE                  = 0,                /* GMM״̬:idle */
    NAS_GMM_STATE_STANDYBY              = 1,                /* GMM״̬:standby */
    NAS_GMM_STATE_READY                 = 2,                /* GMM״̬:ready */
    NAS_GMM_STATE_BUTT
};
typedef VOS_UINT8 NAS_GMM_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_GSM_GPRS_MODE_ENUM
 �ṹ˵��  : NAS_INFO_STRU enMsGprsModeȡֵ
*****************************************************************************/
enum NAS_GSM_GPRS_MODE_ENUM
{
    NAS_GSM_GPRS_MODE_A                 = 0,                /* MS GPRSģʽA:����ͬʱ����GSM��GPRSҵ�� */
    NAS_GSM_GPRS_MODE_B                 = 1,                /* MS GPRSģʽB:������GSM��GPRSҵ��,�����߲���ͬʱ���� */
    NAS_GSM_GPRS_MODE_C_GSM             = 2,                /* MS GPRSģʽC:���Թ���GSMģʽ */
    NAS_GSM_GPRS_MODE_C_GPRS            = 3,                /* MS GPRSģʽC:���Թ���GPRSģʽ */
    NAS_GSM_GPRS_MODE_BUTT
};
typedef VOS_UINT8 NAS_GSM_GPRS_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GMM_GRR_TLLI_CAUSE_ENUM
 �ṹ˵��  : GRRGMM_ASSIGN_REQ_ST enTlliCauseȡֵ
*****************************************************************************/
enum GMM_GRR_TLLI_CAUSE_ENUM
{
    GMM_GRR_NEW_TLLI                    = 1,                /* �����µ�TLLI,֪ͨGRR���� */
    GMM_GRR_OLD_TLLI                    = 2,                /* ���е�TLLI��Ч��֪ͨGRR�ͷ� */
    GMM_GRR_TLLI_CAUSE_BUTT
};
typedef VOS_UINT32 GMM_GRR_TLLI_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_CM_BAND_ENUM
 �ṹ˵��  : RRMM_NAS_PARAMS_REQ_ST ulBand ȡֵ
*****************************************************************************/
enum MMC_CM_BAND_ENUM
{
    MMC_CM_BAND_PREF_GSM_DCS_1800       = 0x00000080,
    MMC_CM_BAND_PREF_GSM_EGSM_900       = 0x00000100,
    MMC_CM_BAND_PREF_GSM_PGSM_900       = 0x00000200,
    MMC_CM_BAND_PREF_GSM_450            = 0x00010000,
    MMC_CM_BAND_PREF_GSM_480            = 0x00020000,
    MMC_CM_BAND_PREF_GSM_750            = 0x00040000,
    MMC_CM_BAND_PREF_GSM_850            = 0x00080000,
    MMC_CM_BAND_PREF_GSM_RGSM_900       = 0x00100000,
    MMC_CM_BAND_PREF_GSM_PCS_1900       = 0x00200000,
    MMC_CM_BAND_PREF_WCDMA_I_IMT_2000   = 0x00400000,
    MMC_CM_BAND_PREF_WCDMA_II_PCS_1900  = 0x00800000,
    MMC_CM_BAND_PREF_WCDMA_III_1700     = 0x01000000,
    MMC_CM_BAND_PREF_ANY                = 0x3FFFFFFF,
    MMC_CM_BAND_PREF_NO_CHANGE          = 0x40000000,
    MMC_CM_BAND_BUTT
};
typedef VOS_UINT32 MMC_CM_BAND_ENUM_UINT32;

/*****************************************************************************
 ö����    : MM_EST_RESULT_ENUM
 �ṹ˵��  : GRRMM_EST_SAPI3_CNF_ST enResult ȡֵ
*****************************************************************************/
enum MM_EST_RESULT_ENUM
{
    MM_EST_SAPI3_SUCCESS                = 0,
    MM_EST_SAPI3_FAILURE                = 1,
    MM_EST_RESULT_BUTT
};
typedef VOS_UINT8 MM_EST_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_NAS_AT_ACTION_TYPE_ENUM
 �ṹ˵��  : GRRMM_AT_MSG_REQ_ST enActionType��ȡֵ
*****************************************************************************/
enum GAS_NAS_AT_ACTION_TYPE_ENUM
{
    GAS_NAS_AT_START_FOREVER            = 0,                /* ָʾGAS�������� */
    GAS_NAS_AT_START_ONCE               = 1,                /* ָʾGAS�ϱ�һ�� */
    GAS_NAS_AT_STOP                     = 2,                /* ָʾGASֹͣ */

    GAS_NAS_AT_ACTION_TYPE_BUTT
};
typedef VOS_UINT8 GAS_NAS_AT_ACTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_GSM_BAND_TYPE_ENUM
 �ṹ˵��  : RRMM_SET_GSM_BAND_REQ_ST enGsmBandInfo
*****************************************************************************/
enum NAS_GSM_BAND_TYPE_ENUM
{
    NAS_GSM_BAND_TYPE_NULL              = 0x0000,
    NAS_GSM_BAND_TYPE_450               = 0x0001,           /* ARFCN�������Ƶ��:GSM 450 */
    NAS_GSM_BAND_TYPE_480               = 0x0002,           /* ARFCN�������Ƶ��:GSM 480 */
    NAS_GSM_BAND_TYPE_850               = 0x0004,           /* ARFCN�������Ƶ��:GSM 850 */
    NAS_GSM_BAND_TYPE_P900              = 0x0008,           /* ARFCN�������Ƶ��:P-GSM 900 */
    NAS_GSM_BAND_TYPE_R900              = 0x0010,           /* ARFCN�������Ƶ��:R-GSM 900 */
    NAS_GSM_BAND_TYPE_E900              = 0x0020,           /* ARFCN�������Ƶ��:E-GSM 900 */
    NAS_GSM_BAND_TYPE_1800              = 0x0040,           /* ARFCN�������Ƶ��:DCS 1800 */
    NAS_GSM_BAND_TYPE_1900              = 0x0080,           /* ARFCN�������Ƶ��:PCS 1900 */
    NAS_GSM_BAND_TYPE_700               = 0x0100,           /* ARFCN�������Ƶ��:GSM 700 */
    NAS_GSM_BAND_TYPE_ANY               = 0x01ff,           /*����Ƶ��*/
    NAS_GSM_BAND_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GSM_BAND_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : GAS_CHANGE_BAND_RESULT_ENUM
 �ṹ˵��  : RRMM_SET_GSM_BAND_CNF_ST enResult
*****************************************************************************/
enum GAS_CHANGE_BAND_RESULT_ENUM
{
    GAS_CHANGE_BAND_SUCCESS             = 0,
    GAS_CHANGE_BAND_FAIL                = 1,
    GAS_CHANGE_BAND_RESULT_BUTT
};
typedef VOS_UINT32 GAS_CHANGE_BAND_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : GAS_CHANGE_BAND_RESULT_ENUM
 �ṹ˵��  : RRMM_SET_GSM_BAND_CNF_ST enResult
*****************************************************************************/
enum RRC_WORK_MODE_ENUM
{
    RRC_WORK_NULL          = 0,     /*NULL״̬��������δ�յ���NAS��START_REQ��Ϣʱ��״̬*/
    RRC_WORK_STANDBY       = 1,     /*����״̬���յ�PLMN_SEARCH_REQ��������һ�����л������������Ͻ��빤��״̬*/
    RRC_WORK_READY         = 2,     /*����״̬����ǰ�������л����� */
    RRC_WORK_HANDOVER_OUT  = 3,     /*����״̬��ͬʱ�������г�״̬ */
    RRC_WORK_HANDOVER_IN   = 4      /*����״̬��ͬʱ����������״̬ */
};
typedef VOS_UINT8 RRC_WORK_MODE_ENUM_UINT8;


/*****************************************************************************
 ö����    : MM_SECURITY_MASK_ENUM
 �ṹ˵��  : MM_CSPS_INFO_ST enInfoMask
*****************************************************************************/
enum MM_SECURITY_MASK_ENUM
{
    MM_SECURITY_CK_MASK                 = 0x01,             /* CK ��Ч��־ */
    MM_SECURITY_IK_MASK                 = 0x02,             /* IK ��Ч��־ */
    MM_SECURITY_KC_MASK                 = 0x04,             /* Kc ��Ч��־ */
    MM_SECURITY_IMSI_MASK               = 0x08,             /* IMSI ��Ч��־ */
    MM_SECURITY_CKSN_MASK               = 0x10,             /* CKSN ��Ч��־ */
    MM_SECURITY_P_TMSI_MASK             = 0x20,             /* P/TMSI ��Ч��־ */
    MM_SECURITY_MASK_BUTT
};
typedef VOS_UINT8 MM_SECURITY_MASK_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_AMR_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : AMRģʽ
*****************************************************************************/
enum RRC_NAS_AMR_MODE_ENUM
{
    RRC_NAS_AMR_SILENCE_FRAME_NO_EXIT   = 0,
    RRC_NAS_AMR_SILENCE_FRAME_EXIT      = 1,
    RRC_NAS_AMR_SILENCE_FRAME_INDEX     = 8,
    RRC_NAS_AMR_NODATA_INDEX            = 9,
    RRC_NAS_AMR_MODE_BUTT
};
typedef VOS_UINT8 RRC_NAS_AMR_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_AMR_RATE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : AMR����
*****************************************************************************/
enum RRC_NAS_AMR_RATE_TYPE_ENUM
{
    RRC_NAS_AMR_RATE_NULL               = 0x00,             /* ����ASN.1���룬���벻ʹ�� */
    RRC_NAS_AMR_RATE_4P75               = 0x01,             /* 4.75k */
    RRC_NAS_AMR_RATE_5P15               = 0x02,             /* 5.15k */
    RRC_NAS_AMR_RATE_5P9                = 0x04,             /* 5.90k */
    RRC_NAS_AMR_RATE_6P7                = 0x08,             /* 6.70k */
    RRC_NAS_AMR_RATE_7P4                = 0x10,             /* 7.40k */
    RRC_NAS_AMR_RATE_7P95               = 0x20,             /* 7.95k */
    RRC_NAS_AMR_RATE_10P2               = 0x40,             /* 10.2k */
    RRC_NAS_AMR_RATE_12P2               = 0x80,             /* 12.2k */
    RRC_NAS_AMR_RATE_BUTT

};
typedef VOS_UINT8 RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_AMR_MODE_CFG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : AMRģʽ����
*****************************************************************************/
enum RRC_NAS_AMR_MODE_CFG_ENUM
{
    RRC_NAS_AMR_MODE_SETUP              = 0,                /* ҵ����ʱ���� */
    RRC_NAS_AMR_MODE_MODIFY             = 1,                /* AMRģʽ�޸�ʱ */
    RRC_NAS_AMR_MODE_RESOURCE_IND       = 2,                /*SYSHO*/
    RRC_NAS_AMR_MODE_NO_CHANGE          = 3,                /* AMRģʽδ�仯 */
    RRC_NAS_AMR_MODE_CFG_BUTT
};
typedef VOS_UINT8   RRC_NAS_AMR_MODE_CFG_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_RR_CHANNEL_MODE
 Э����  :
 ASN.1���� :
 ö��˵��  : AMR�ŵ�ģʽ
*****************************************************************************/
enum GAS_RR_CHANNEL_MODE
{
    RR_CHAN_MOD_SINGAL_ONLY,    /* ������ģʽ*/
    RR_CHAN_MOD_FR,             /* Full Rate */
    RR_CHAN_MOD_EFR,            /* Enhanced Full Rate  */
    RR_CHAN_MOD_AFS,            /* Enhanced Full Rate  */
    RR_CHAN_MOD_CSD_2400,
    RR_CHAN_MOD_CSD_4800,
    RR_CHAN_MOD_CSD_9600,
    RR_NAS_DATA_CSD_14400,
    RR_CHAN_MOD_HR,             /* half Rate */
    RR_CHAN_MOD_AHR,             /* half Rate */
    RR_CHAN_MOD_H24,            /* Adaptive Multi-Rate */
    RR_CHAN_MOD_H48,            /* Adaptive Multi-Rate */
    RR_CHAN_MOD_WFS,            /* Adaptive Multi-Rate,WFSҵ�� */
    RR_CHAN_MOD_BUF
};
typedef VOS_UINT8  NAS_RR_CHANNEL_MODE_ENUM_U8;

/*****************************************************************************
 ö����    : RRMM_GMM_PROC_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GMM������������
*****************************************************************************/
enum RRMM_GMM_PROC_TYPE_ENUM
{
    RRMM_GMM_PROC_TYPE_ATTACH        = 0, /*ע��, ��������PSע������ע��*/
    RRMM_GMM_PROC_TYPE_NORMAL_RAU    = 1, /*����·��������,��������PS·�������º����·��������*/
    RRMM_GMM_PROC_TYPE_PERIOD_RAU    = 2, /*������·��������,��������PS·�������º����·��������*/
    RRMM_GMM_PROC_TYPE_INVALID       = 3  /*��Ч������*/
};

typedef VOS_UINT16 RRMM_GMM_PROC_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRMM_GMM_PROC_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GMM������������
*****************************************************************************/
enum RRMM_GMM_PROC_FLAG_ENUM
{
    RRMM_GMM_PROC_FLAG_START       = 0, /*ע��, ��������PSע������ע��*/
    RRMM_GMM_PROC_FLAG_FINISH      = 1, /*����·��������,��������PS·�������º����·��������*/
    RRMM_GMM_PROC_FLAG_INVALID     = 2  /*��Чֵ*/
};
typedef VOS_UINT16 RRMM_GMM_PROC_FLAG_ENUM_UINT16;
enum RRMM_GMM_PROC_CONN_TYPE_ENUM
{
    RRMM_GMM_PROC_CONN_TYPE_NO_CONN               = 0, /* no conn */
    RRMM_GMM_PROC_CONN_TYPE_ATTACH_SIG_CONN       = 1, /* attach sig conn */
    RRMM_GMM_PROC_CONN_TYPE_RAU_SIG_CONN          = 2, /* rau sig conn */
    RRMM_GMM_PROC_CONN_TYPE_PS_SERVICE_CONN       = 3, /* ps service conn */
    RRMM_GMM_PROC_CONN_TYPE_BUTT                  = 4  /*��Чֵ*/
};
typedef VOS_UINT16 RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16;




/*****************************************************************************
 ö����    : GRR_NAS_SYNC_CHANNAL_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GSM�ŵ�ģʽ����
*****************************************************************************/
enum GRR_NAS_SYNC_CHANNAL_MODE_ENUM
{
    RR_NAS_SIGNALLING_ONLY,
    RR_NAS_SPEECH_V1,
    RR_NAS_SPEECH_V2,
    RR_NAS_SPEECH_V3,
    RR_NAS_DATA_9600,
    RR_NAS_DATA_4800,
    RR_NAS_DATA_2400,
    RR_NAS_DATA_14400
};
typedef VOS_UINT8 GRR_NAS_SYNC_CHANNAL_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GRR_NAS_SYNC_TCH_RATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GSM�ŵ���������
*****************************************************************************/
enum GRR_NAS_SYNC_TCH_RATE_ENUM
{
    RR_NAS_TCH_FULL_RATE,
    RR_NAS_TCH_HALF_RATE
};
typedef VOS_UINT8 GRR_NAS_SYNC_TCH_RATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RR_NAS_SYNC_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ŵ��仯ԭ��
*****************************************************************************/
enum RR_NAS_SYNC_REASON_ENUM
{
    /*  reasons mapped from rr_sync_ind */
    RR_NAS_GSM_RES_ASSIGNED,
    RR_NAS_GSM_CHANNEL_MODE_MODIFIED,
    RR_NAS_GSM_GSM_HANDOVER,
    RR_NAS_WCDMA_GSM_HANDOVER,

    /*  reasons mapped from rrc_sync_ind */
    RR_NAS_WCDMA_RAB_ESTABLISHED,
    RR_NAS_WCDMA_RAB_RELEASED,
    RR_NAS_WCDMA_RAB_RECONFIGURED,
    RR_NAS_GSM_WCDMA_HANDOVER
};
typedef VOS_UINT8 RR_NAS_SYNC_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_BG_PLMN_SEARCH_RLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : BG�������
*****************************************************************************/
enum RRC_BG_PLMN_SEARCH_RLT_ENUM
{
    RRC_BG_PLMN_SEARCH_RLT_SUCCESS            = 0,                /* ָ����PLMN�����ɹ� */
    RRC_BG_PLMN_SEARCH_RLT_FAIL               = 1,                /* �����ʵ�ʸ�DSP��������������������ʧ�� */
    RRC_BG_PLMN_SEARCH_RLT_ABORT              = 2,                /* PLMNû�и�DSP������������Ϊ����㵱ǰ״̬��������������ֹ */
    RRC_BG_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT8  RRC_BG_PLMN_SEARCH_RLT_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_SYS_SUBMODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : פ������Ľ��뼼��ö��
*****************************************************************************/
/* ��WAS��ֳ���ȷ��,��ģʽ�����仯ʱ,�ض���ͨ��AT_MSG_IND��Ϣ�ϱ� */
enum RRC_NAS_SYS_SUBMODE_ENUM
{
    RRC_NAS_SYS_SUBMODE_NULL                  = 0,                /* �޷��� */
    RRC_NAS_SYS_SUBMODE_GSM                   = 1,                /* GSMģʽ */
    RRC_NAS_SYS_SUBMODE_GPRS                  = 2,                /* GPRSģʽ */
    RRC_NAS_SYS_SUBMODE_EDGE                  = 3,                /* EDGEģʽ */
    RRC_NAS_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMAģʽ */
    RRC_NAS_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPAģʽ */
    RRC_NAS_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPAģʽ */
    RRC_NAS_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPAģʽ */
    RRC_NAS_SYS_SUBMODE_LTE                   = 8,                /* LTEģʽ */
    RRC_NAS_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  RRC_NAS_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_SYS_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : sys info ������
*****************************************************************************/
enum RRC_NAS_SYS_INFO_TYPE_ENUM
{
    RRC_NAS_SYS_INFO_TYPE_OTA                 = 0,                /* ��ǰ��ota */
    RRC_NAS_SYS_INFO_TYPE_SYS                 = 1,                /* ��ǰ��ϵͳ��Ϣ */
    RRC_NAS_SYS_INFO_TYPE_BUTT
};
typedef VOS_UINT8  RRC_NAS_SYS_INFO_TYPE_ENUM_UINT8;


enum RRC_NAS_LTE_CAPABILITY_STATUS_ENUM
{
    RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE                   = 0,                        /* LTE���Բ�����,����L������ע�ᱻ��#7 */
    RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE                  = 1,                        /* LTE���Իָ����� */
    RRC_NAS_LTE_CAPABILITY_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_LTE_CAPABILITY_STATUS_ENUM_UINT32;


enum RRC_NAS_RAT_CAPABILITY_STATUS_ENUM
{
    RRC_NAS_RAT_CAPABILITY_STATUS_DISABLE                   = 0,                        /* RAT���Բ����� */
    RRC_NAS_RAT_CAPABILITY_STATUS_REENABLE                  = 1,                        /* RAT���Իָ����� */
    RRC_NAS_RAT_CAPABILITY_STATUS_BUTT
};
typedef VOS_UINT8 RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8;


enum RRC_NAS_CS_TRANSACTION_ENUM
{
    RRC_NAS_CS_TRANSACTION_NO_EXIST                   = 0,                         /* ������CSFB ���� */
    RRC_NAS_CS_TRANSACTION_MO_NORMAL_EXIST            = 1,                         /* ����CSFB ����ҵ��(CC/SS)���� */
    RRC_NAS_CS_TRANSACTION_EMERGENCY_EXIST            = 2,                         /* ����CSFB ������������ */
    RRC_NAS_CS_TRANSACTION_MT_EXIST                   = 3,                         /* ����CSFB �������� */
    RRC_NAS_CS_TRANSACTION_BUTT
};
typedef VOS_UINT8 RRC_NAS_CS_TRANSACTION_ENUM_UINT8;


enum RRC_NAS_UTRAN_MODE_ENUM
{
    RRC_NAS_UTRAN_MODE_FDD          = 0,     /* ��ǰ����ģʽΪWCDMA */
    RRC_NAS_UTRAN_MODE_TDD          = 1,     /* ��ǰ����ģʽΪTDSCDMA */
    RRC_NAS_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  RRC_NAS_UTRAN_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_COVERAGE_TYPE_ENUM
 �ṹ˵��  : RRMM_PLMN_SEARCH_CNF_STRU��Ϣ�е�enCoverageType
*****************************************************************************/
enum RRC_NAS_COVERAGE_TYPE_ENUM
{
    RRC_NAS_COVERAGE_TYPE_NONE              = 0,                                /* �����縲�� */
    RRC_NAS_COVERAGE_TYPE_LOW               = 1,                                /* �е��������縲��*/
    RRC_NAS_COVERAGE_TYPE_HIGH              = 2,                                /* �и��������縲�� */
    RRC_NAS_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  RRC_NAS_COVERAGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_NAS_NET_SCAN_RESULT_ENUM
 �ṹ˵��  : RRC_NAS_NET_SCAN_CNF��Ϣ�е�enResult;
*****************************************************************************/
enum RRC_NAS_NET_SCAN_RESULT_ENUM
{
    RRC_NAS_NET_SCAN_RESULT_SUCCESS        = 0,
    RRC_NAS_NET_SCAN_RESULT_FAILURE        = 1,
    RRC_NAS_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  RRC_NAS_NET_SCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_NET_SCAN_CAUSE_ENUM
 �ṹ˵��  : �����ظ�NASɨ��ʧ��ԭ�������ǰû���κ�ģʽפ����NASֱ�ӻظ�ATʧ��
 1.��    ��   : 2013��8��24��
   ��    ��   : sunxibo
   �޸�����   : �½��ṹ��
*****************************************************************************/
enum RRC_NAS_NET_SCAN_CAUSE_ENUM
{
    RRC_NAS_NET_SCAN_CAUSE_SIGNAL_EXIST = 0,                /* �����������ӣ�NAS�ظ�AT�Ժ��ٳ��� */
    RRC_NAS_NET_SCAN_CAUSE_STATE_NOT_ALLOWED,               /* ��ǰ״̬������NAS�ظ�AT�Ժ��ٳ��� */
    RRC_NAS_NET_SCAN_CAUSE_FREQ_LOCK,                       /* ��ǰ��Ƶ״̬��NAS�ظ�ATʧ�� */
    RRC_NAS_NET_SCAN_CAUSE_PARA_ERROR,                      /* �������󣬰������뼼����֧�֣�Ƶ�β�֧�֣�Ƶ������������޴���NAS�ظ�ATʧ�� */

    RRC_NAS_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 RRC_NAS_NET_SCAN_CAUSE_ENUM_UINT8;


enum RRC_NAS_NCELL_STATE_ENUM
{
    RRC_NAS_NCELL_STATE_NULL    = 0x00,                                         /* ��û��TD��������Ҳû��4G���� */
    RRC_NAS_NCELL_STATE_3G      = 0x01,                                         /* ֻ��TD������ */
    RRC_NAS_NCELL_STATE_4G      = 0x02,                                         /* ֻ��4G������ */
    RRC_NAS_NCELL_STATE_3G4G    = 0x03,                                         /* ����TD��������Ҳ��4G���� */
    RRC_NAS_NCELL_STATE_BUTT

};
typedef VOS_UINT8 RRC_NAS_NCELL_STATE_ENUM_UINT8;


enum NAS_GAS_MS_CAP_TYPE_ENUM
{
    NAS_GAS_MS_CAP_TYPE_UTRAN_FDD_RAC = 0x00,           /* UTRAN FDD�»�ȡMS GģRAC */
    NAS_GAS_MS_CAP_TYPE_UTRAN_TDD_RAC,                  /* UTRAN TDD�»�ȡMS GģRAC */
    NAS_GAS_MS_CAP_TYPE_CLASSMARK,                      /* ��ȡMS CLASSMARK */
    NAS_GAS_MS_CAP_TYPE_BUTT
};
typedef VOS_UINT8 NAS_GAS_MS_CAP_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: RRMM_FFT_SCAN_TYPE_ENUM_UINT8
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum RRMM_FFT_SCAN_TYPE_ENUM
{
    RRMM_FFT_SCAN_TYPE_NONE     = 0,                 /* �����縲�� */
    RRMM_FFT_SCAN_TYPE_LOW      = 1,                 /* ���������縲��   */
    RRMM_FFT_SCAN_TYPE_HIGH     = 2,                 /* �и��������縲�� */
    RRMM_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  RRMM_FFT_SCAN_TYPE_ENUM_UINT8;
enum NAS_LAU_TYPE_ENUM
{
    NAS_LAU_TYPE_NORMAL_LAU             = 0,
    NAS_LAU_TYPE_PERIOD_LAU,
    NAS_LAU_TYPE_IMSI_ATTACH,

    NAS_LAU_TYPE_BUTT

};
typedef VOS_UINT8 NAS_LAU_TYPE_ENUM_UINT8;


enum NAS_ADDITION_UPDATE_PARA_ENUM
{
    NAS_ADDITION_UPDATE_PARA_NONE       = 0,
    NAS_ADDITION_UPDATE_PARA_MO,
    NAS_ADDITION_UPDATE_PARA_MT,
    NAS_ADDITION_UPDATE_PARA_MO_MT,

    NAS_ADDITION_UPDATE_PARA_BUTT

};
typedef VOS_UINT8 NAS_ADDITION_UPDATE_PARA_ENUM_UINT8;


enum RRMM_TRANSACTION_STATUS_ENUM
{
    RRMM_TRANSACTION_CONNECTION_EST_SUCC       = 0,
    RRMM_TRANSACTION_FAIL,

    RRMM_TRANSACTION_BUTT

};
typedef VOS_UINT8 RRMM_TRANSACTION_STATUS_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* 7.1.1 ��Ϣ RRMM_PLMN_SEARCH_REQ �Ľṹ�� */
typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}RRC_PLMN_ID_STRU;

typedef struct
{
    RRC_PLMN_ID_STRU                    PlmnId;             /* PlMN��ʶ       */
    VOS_UINT32                          ulForbLac;          /* ��ֹע������Ϣ */
}RRC_FORB_LA_STRU;
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0��ʾTDDƵ�㲻���� */
    VOS_UINT8                           ucEplmnIdNum;                           /* PLMN ID���� */

    VOS_UINT16                          ausTdsArfcnList[RRC_NAS_TDS_ARFCN_MAX_NUM];
    RRC_PLMN_ID_STRU                    astEplmnIdList[RRC_MAX_EQUPLMN_NUM];    /* ������ص�ЧPlMN��ʶ */
}RRMM_NCELL_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ    */     /*_H2ASN_Skip*/
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    ulSearchType;       /* ��������  */

    VOS_UINT32                          ulPlmnIdNum;        /* PLMN ID���� */
    RRC_PLMN_ID_STRU                    aPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* PlMN��ʶ */
    VOS_UINT32                          ulForbLaNum;        /* ��ֹע�����ĸ��� */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];        /* ��ֹע�����б�                           */

    RRMM_NCELL_INFO_STRU                stNcellInfo;
    PS_BOOL_ENUM_UINT8                  enCsfbFlg;          /* �������������Ƿ�CSFB����� */
    RRMM_FFT_SCAN_TYPE_ENUM_UINT8       enFftScanType;      /* FFT��������,Ŀǰ����spec�����ͻ�ȡ������Ϣ������ */
    PS_BOOL_ENUM_UINT8                  enPlmnInfoCampFlg;  /* ֻ���ϱ�plmn�Ƿ���Ҫ����פ��׼��,Ŀǰ���ڻ�ȡ������Ϣ�п��ܻ���дPS_FALSE,Ĭ����PS_TRUE */

    VOS_UINT8                           aucReserve[1];

}RRMM_PLMN_SEARCH_REQ_STRU;

/* 7.1.2 ��Ϣ RRMM_PLMN_SEARCH_CNF �Ľṹ�� */
typedef struct
{
    RRC_PLMN_ID_STRU                stPlmnId;
    RRC_NAS_RAT_TYPE_ENUM_UINT32    ulRat;    /* ֧�ֵĽ��뼼�� */
}RRMM_PLMN_WITH_RAT_STRU;

/* ulSearchRltȡֵ */
typedef struct
{
    RRMM_PLMN_WITH_RAT_STRU             PlmnId;             /* PLMN ID    */
    VOS_INT32                           lRscp;              /* RSCP����ֵ */
}RRC_LOW_PLMN_INFO_STRU;

typedef struct
{
    RRC_NAS_RAT_TYPE_ENUM_UINT32             enRat;                            /* �����Ľ��뼼�� */
    RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM_UINT32 enListSearchRlt;                  /* ���뼼��LIST������ɽ�� */
}RRC_LIST_SEARCH_RAT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* ������PLMN�ĸ��� */
    RRMM_PLMN_WITH_RAT_STRU             aHighPlmnList[RRC_MAX_HIGH_PLMN_NUM];   /* ������PLMN�б�   */
    VOS_UINT32                          ulLowPlmnNum;                           /* ������PLMN�ĸ��� */
    RRC_LOW_PLMN_INFO_STRU              aLowPlmnList[RRC_MAX_LOW_PLMN_NUM];     /* ������PLMN�б�   */
}RRC_PLMN_ID_LIST_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ   */      /*_H2ASN_Skip*/
    RRC_PLMN_SEARCH_RLT_ENUM_UINT32     ulSearchRlt;        /* ������� */
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;     /* RRC�ڵ�ǰ���뼼���µ����縲������ */
    RRC_LIST_SEARCH_RAT_INFO_STRU       astSearchRatInfo[NAS_RRC_MAX_RAT_NUM];     /* ��¼����㱾���Ѿ������Ľ��뼼����Ϣ�������б�����ʱ��Ч */
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* �ϱ���PLMN ID�б� */
}RRMM_PLMN_SEARCH_CNF_STRU;

/* 7.1.3 ��Ϣ RRMM_PLMN_LIST_IND �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ        */ /*_H2ASN_Skip*/
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* �ϱ���PLMN ID�б� */
}RRMM_PLMN_LIST_IND_STRU;

/* 7.1.4 ��Ϣ RRMM_EQU_PLMN_NOTIFY_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ         */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulEquPlmnNum;                           /* ��Ч��PLMN�ĸ��� */
    RRC_PLMN_ID_STRU                    aEquPlmnIdList[RRC_MAX_EQUPLMN_NUM];    /* ��Ч��PLMNID�б� */
} RRMM_EQU_PLMN_NOTIFY_REQ_STRU;

/* 7.1.5 ��Ϣ RRMM_AREA_LOST_IND �Ľṹ��,NAS���κ�����¶�����Ӧ��������ָʾ */
/* ulRptModeȡֵ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ   */      /*_H2ASN_Skip*/
    RRC_NAS_AREA_LOST_ENUM_UINT32       ulRptMode;          /* ����ģʽ */
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* �ϱ���PLMN ID�б� */ /* ����������PLMN ��Ϣʱ����Ҫ��Gȥ������û������ǰ�����̴��� */
}RRMM_AREA_LOST_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ         */      /*_H2ASN_Skip*/
    RRC_LIMIT_CAMP_ACTION_ENUM_UINT32   enLimitCampAction;  /* ���Ʒ���Ĺ���:��ʼ���߽���  */
    VOS_UINT32                          ulServiceAvailFlag; /* ��ǰ�Ƿ������� VOS_TRUE ������� VOS_FALSE ���񲻿���   */
    RRC_RRC_CONN_STATUS_ENUM_UINT32     enRrcConnStatus;    /* RRC_RRC_CONN_STATUS_PRESENT:����̬;RRC_RRC_CONN_STATUS_ABSENT:������̬ */
    RRC_PLMN_ID_LIST_STRU               stPlmnIdList;    /* �ϱ���W/G/L PLMN ID�б� */
}RRMM_LIMIT_SERVICE_CAMP_IND_STRU;


/***********************�����ӿ�MMC��>AS**************************/
/* 7.1.6 ��ϢRRMM_PLMN_SEARCH_STOP_REQ�Ľṹ�� */
/******************************************************************************
    ˵����AS���յ�����Ϣ��,������ڽ���PLMN����,��ֹͣ����PLMN����,
    ����MMC����ֹͣȷ����Ϣ,���û�н���,ֱ����MMC����ֹͣȷ����Ϣ��
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ����   */
}RRMM_PLMN_SEARCH_STOP_REQ_ST;

/***********************�����ӿ�AS��>MMC**************************/
/* 7.1.7 ��Ϣ RRMM_PLMN_SEARCH_STOP_CNF�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ���� */
}RRMM_PLMN_SEARCH_STOP_CNF_ST;

/***********************�޸Ľӿ�MMC��>AS**************************/
/* 7.1.8 ��Ϣ RRMM_START_REQ �Ľṹ�� */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ     */    /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM��״̬              */
    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* ��ģ�����ȼ� */
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* ��ǰUTRAN�Ĺ���ģʽ:0---FDD 1---TDD */

    VOS_UINT8                           aucReserve1[2];     /* ���� */
}RRMM_START_REQ_STRU;

/* 7.1.9 ��Ϣ RRMM_START_CNF �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ   */      /*_H2ASN_Skip*/
    MMC_START_RESULT_ENUM_UINT32        ulResult;           /* ������� */
}RRMM_START_CNF_STRU;

/* 7.1.10 ��Ϣ RRMM_CELL_SELECTION_CTRL_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ       */  /*_H2ASN_Skip*/
    RRC_NAS_RESEL_TYPE_ENUM_UINT32      ulReselectInd;      /* ��ѡ����ָʾ */
    VOS_UINT32                          ulForbLaNum;        /* ��ֹע�����ĸ��� */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];        /* ��ֹע�����б� */
}RRMM_CELL_SELECTION_CTRL_REQ_STRU;

typedef struct
{
    VOS_UINT32                          ulNasMsgSize;       /* [1,RRC_NAS_MAX_SIZE_NAS_MSG],Byte */
    VOS_UINT8                           aucNasMsg[4];       /*_H2ASN_Replace   L3Message aucNasMsg; */
}NAS_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                           ulOpId;             /* ������ʶ                                 */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32   ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_EST_CAUSE_ENUM_UINT32        ulEstCause;         /* RRC Connection Reqԭ��ȡֵ��ö�ٶ��� */
    RRC_NAS_CALL_TYPE_ENUM_UINT32        enCallType;         /* RRC Connection Req ҵ������ */
    RRC_NAS_IDNNS_TYPE_ENUM_UINT32       ulIdnnsType;        /* Intra domain nas node selector���ͣ�ȡֵ��ö�ٶ��� */
    NAS_RRC_SPLMN_SAME_RPLMN_ENUM_UINT32 enSplmnSameRplmn;   /* NASָʾ�����ѡ���plmn��Rplmn�Ƿ���ͬ   */
    RRC_PLMN_ID_STRU                     stPlmnId;           /* ��С��PLMN ID              */
    NAS_MSG_STRU                         FisrtNasMsg;        /* ��CN Domain�ĵ�һ��NAS��Ϣ               */
}RRMM_EST_REQ_STRU;

/* 7.1.12 ��Ϣ RRMM_EST_CNF �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ   */      /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;             /* ������ʶ */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult;           /* ���������ӽ��������ȡֵ��ö�ٶ��� */
}RRMM_EST_CNF_STRU;

/* 7.1.13 ��Ϣ RRMM_DATA_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_MSG_PRIORTY_ENUM_UINT32     ulPriorityInd;      /* ��Ϣ���ȼ�ָʾ��ȡֵ��ö�ٶ��� */
    NAS_MSG_STRU                        SendNasMsg;         /* ������Ҫ���͵�NAS��Ϣ          */
}RRMM_DATA_REQ_STRU;

/* 7.1.14 ��Ϣ RRMM_DATA_IND �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    NAS_MSG_STRU                        RcvNasMsg;
}RRMM_DATA_IND_STRU;

/* 7.1.15 ��Ϣ RRMM_REL_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_CELL_BAR_ENUM_UINT32            enBarValidFlg;      /* ��ǰС���򼤻С���Ƿ�������ȡֵ��ö�ٶ��� */
}RRMM_REL_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_REL_CS_PS_ALL_CONN_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_SERVICE_ABORT_NOTIFY_STRU;




/* 7.1.16 ��Ϣ RRMM_REL_IND �Ľṹ��,NAS���κ�����¶�����Ӧ�����ͷ�ָʾ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus;    /* �ͷ��������Ӻ�RRC�����Ƿ���ڣ�ȡֵ��ö�ٶ��� */
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;         /* �����ͷ�ԭ��ȡֵ��ö�ٶ���                  */
}RRMM_REL_IND_STRU;

/* 7.1.17 ��Ϣ RRMM_ABORT_REQ �Ľṹ�壬ɾ����RRMM_REL_REQ_STRU�ϲ� */

/* 7.1.18��Ϣ RRMM_POWER_OFF_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ���� */
}RRMM_POWER_OFF_REQ_STRU;

/* 7.1.19��Ϣ RRMM_POWER_OFF_CNF �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ���� */
}RRMM_POWER_OFF_CNF_STRU;

/* 7.1.20��Ϣ RRMM_AC_INFO_CHANGE_IND �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_AC_TYPE_ENUM_UINT32         ulAcChangeInd;      /* AC����״̬�����ı� */
} RRMM_AC_INFO_CHANGE_IND_STRU;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.21 ��Ϣ RRMM_SUSPEND_IND �ṹ�� */

typedef struct
{
    PS_BOOL_ENUM_UINT8                 enRestrictPagingRsp;          /* �Ƿ�������ӦѰ�� */
    PS_BOOL_ENUM_UINT8                 enRestrictRegister;           /* �Ƿ�����ע�� */
    PS_BOOL_ENUM_UINT8                 enRestrictNormalService;      /* �Ƿ���������ҵ�� */
    PS_BOOL_ENUM_UINT8                 enRestrictEmergencyService;   /* �Ƿ����ƽ���ҵ�� */
}RRC_NAS_RESTRICTION_TYPE_STRU;

/* 7.1.20_1 ��Ϣ RRMM_W_AC_INFO_CHANGE_IND_STRU �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_NAS_RESTRICTION_TYPE_STRU       stCsRestriction;    /* CS������Ƿ����� */
    RRC_NAS_RESTRICTION_TYPE_STRU       stPsRestriction;    /* PS������Ƿ����� */
} RRMM_W_AC_INFO_CHANGE_IND_STRU;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.21 ��Ϣ RRMM_SUSPEND_IND �ṹ�� */
typedef struct
{
    NAS_RRC_RE_TX_MSGTYPE_ENUM_UINT32   enReTxMsgType;
    VOS_UINT8                           aucNasReTxMsg[NAS_RRC_MAX_RE_TX_MSG_LENTH];
}NAS_RRC_RE_TX_MSG_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_SUSPEND_CAUSE_ENUM_UINT8        ucSuspendCause;     /* ����ԭ�� */
    MMC_SUSPEND_ORIGEN_UINT8            ucSuspendOrigen;    /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;/* �����Ŀ�ķ� */
    VOS_UINT8                           aucReserve1[1];     /* ���� */
    NAS_RRC_RE_TX_MSG_STRU              astReTxMsg[NAS_RRC_MAX_RE_TX_MSG_NUM];
}RRMM_SUSPEND_IND_ST;

/***********************�����ӿ�MMC��>AS***************************/
/* 7.1.22 ��Ϣ RRMM_SUSPEND_RSP �ṹ�� */
/* ˵�������NAS����ʧ�ܣ���NAS�ص���������״̬��*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   ucResult;           /*WRRC/RR��Ҫ�������ʧ�ܵ������NAS����Щ����¹����ʧ��*/
    VOS_UINT8                           aucReserve1[3];     /* ���� */
} RRMM_SUSPEND_RSP_ST;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.23 ��Ϣ RRMM_RESUME_IND �ṹ�� */
/******************************************************************************
 1����AS��Ҫ��:��ϵͳ���л���ɺ�����:(ϵͳ1->ϵͳ2)����(ϵͳ1->ϵͳ2->ϵͳ1)�����������л������Σ�
 AS��������MM�Ӳ㷢�ͻָ���Ϣ��Ȼ���������Ϊ���л�״̬ʱ���������̴��������ûָ���Ϣ�������Ӧ�÷���
 ��Ϣ��������NAS��AS״̬��һ�£��ָ���Ϣ�ĺ�������Ǳ����л����̽�����

 2����NAS������:NAS������л��������ͬ�������������ȡֵ˵��

 ucCsResumeResult:
   ����Cs��ҵ��ʱ:
   MMC_RESUME_RESULT_SUCCESS--NAS��ΪCS��RR����״̬�������ܷ���NAS CSֱ����Ϣ
   MMC_RESUME_RESULT_FAILURE--NAS��ΪCS��RR����ʧ�ܣ����ܷ���NAS CSֱ����Ϣ����ջ����ֱ����Ϣ��
   ������Cs��ҵ��ʱ:
   MMC_RESUME_RESULT_SUCCESS--NAS��Ϊ�����פ��С���ɹ�
   MMC_RESUME_RESULT_FAILURE--NAS��Ϊ�����û���ҵ�С��פ����

 ucPsResumeResult:
   MMC_RESUME_RESULT_SUCCESS--2G->3Gʱ����ʾWRRCפ���ɹ�����ǰû��RR���ӣ�GMM�����Ҫ����ֱ����Ϣ��
                                        ʹ��RRMM_EST_REQ���Ƚ���WRRC PS��������
                              3G->2G->3Gʱ����ʾWRRCפ���ɹ���GMM���Է���ֱ����Ϣ

                              3G->2Gʱ����ʾGRRפ��GPRSС���ɹ���GMM�����Ҫ����ֱ����Ϣ��
                                        TLLI��������Ϣ�ȴ��ݸ�GRR��LLC������RA����ֱ����Ϣ
                              2G->3G->2Gʱ����ʾGRRפ��GPRSС���ɹ���GMM����ͨ��LLC����GMMֱ����Ϣ��
                                        TLLI��������Ϣ�����贫�ݸ�GRR��LLC����ΪGRR��LLC����Щ��Ϣ

   MMC_RESUME_RESULT_FAILURE--פ��ʧ�ܣ�GMM����״̬�ָ�����ջ������Ϣ

   MMC_RESUME_GPRS_SUSPENSION-����������ϵͳ�ı䵽2G,��ʾGPRS���ҡ�
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_RESUME_RESULT_ENUM_UINT8        ucCsResumeResult;   /* CS���л���� */
    MMC_RESUME_RESULT_ENUM_UINT8        ucPsResumeResult;   /* PS���л���� */
    MMC_RESUME_ORIGEN_ENUM_UINT8        ucResumeOrigen;     /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8                           aucReserve1[1];     /* ���� */
}RRMM_RESUME_IND_ST;


/***********************�����ӿ�MMC��>AS***************************/
/* 7.1.24 ��Ϣ RRMM_RESUME_RSP �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ���� */
}RRMM_RESUME_RSP_ST;

/***********************�����ӿ�MMC��>AS***************************/
/* 7.1.25 ��ϢRRMM_SUSPEND_REQ �ṹ�� */
/******************************************************************************
˵��������Ϣ������MMC�������AS(GAS��WAS)��Ĳ�������
   1����˭������Ϣ����ʾ�����ĸ������ʵ�壻
   2������������ܹ�������󣬽���㲻�ܴ��ں���״̬��������ֹ���������
      �Ĺ��̣�ת��������ʼ���󣬵ȴ�PLMN���������״̬�����ݹ���
      ���ͣ������Ƿ񽫵�ǰ������Ƴ�DSP��Ŀ���Ǳ�֤��ͬ����ģʽ��
      ת����ɡ�ĿǰMMCֻʹ���˹���ʱ�Ƴ�DSP�����
   3�������ǰ�����ܾ���������MMC�����ֵ�ǰ�Ľ���㣬�л�����ͬ�����
      �Ĳ���ʧ�ܣ���ǰMMC״̬���ı䣬�ɼ�������������̡�
   4���ӽ�������״̬�ָ���ʹ��RRMM_PLMN_SEARCH_REQ��Ϣ����ʼ�����Ĺ��ܡ�
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    MMC_AS_SUSPEND_STOP_ENUM_UINT8      ucStopCause;        /* ����ֹͣ��ʽ         */
    VOS_UINT8                           aucReserve1[3];     /* ���� */
}RRMM_SUSPEND_REQ_ST;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.26 ��Ϣ RRMM_SUSPEND_CNF �ṹ�� */
/******************************************************************************
˵��������Ϣ�ǽ���㣨GAS��WAS����RRMM_SUSPEND_REQ�Ļ�Ӧȷ�ϡ�
   1�������ǰ��������NAS�Ĺ�������ulResultֵ����MMC_AS_SUSPEND_SUCCESS��
      ����㽫��ֹ��ǰ�����й��̣��ص�������ʼ״̬���ȴ�NAS�㻽�ѡ�
   2�������ǰ�����ܾ�NAS�Ĺ�������ulResultֵ����MMC_AS_SUSPEND_FAILURE��
      ����㱣������״̬��������������NAS���������
   3��NAS���ڷ���RRMM_SUSPEND_REQ���ǵȴ�������RRMM_SUSPEND_CNF��Ϣ�ġ�
      ����ղ���������ȷ����Ϣ��NAS��MMCʵ�彫һֱ�ȴ���
******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    MMC_AS_SUSPEND_RESULT_ENUM_UINT8    ucResult;           /* ���������� */
    VOS_UINT8                           aucReserve1[3];     /* ���� */
}RRMM_SUSPEND_CNF_ST;

/***********************�����ӿ�MMC��>AS***************************/
/* 7.1.27 ��Ϣ RRMM_UICC_STATUS_CHANGE_IND �ṹ�� */
/******************************************************************************
˵��������Ϣ��NAS��֪ͨAS�㣨GAS��WAS��UICC״̬��AS����ݸ�״̬
      ����AS����UICC��ص���Ϣ��ulSimStatusȡֵ��7.1.8 ��Ϣ RRMM_START_REQ
      ��SIM��״̬��ö��ֵ��ͬ
******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM��״̬   */
}RRMM_UICC_STATUS_CHANGE_IND_ST;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.28 ��Ϣ RRMM_UICC_STATUS_CHANGE_RSP �ṹ�� */
/* ˵��������Ϣ��AS��֪ͨNAS���Ѿ��յ�sim��״ָ̬ʾ*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    AS_UICC_STATUS_IND_RESULT_ENUM_UINT32   ulResult;       /* �յ�SIM��״̬������   */
}RRMM_UICC_STATUS_CHANGE_RSP_ST;


/* 7.2 WASר����Ϣ */
/* 7.2.1 ��Ϣ RRMM_SYS_INFO_IND �Ľṹ�� */


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpCsDrx      : 1;
    VOS_UINT32                          bitOpPsDrx      : 1;
    VOS_UINT32                          bitOpCellId     : 1;
    VOS_UINT32                          bitSpare        : 28;

    RRC_NAS_SYS_INFO_TYPE_ENUM_UINT8    enSysInfoType;
    VOS_UINT8                           aucReserve[3];

    RRC_PLMN_ID_STRU                    PlmnId;             /* ��С��PLMN ID              */

    VOS_UINT32                          ulCsDrxLength;      /* CS��DRX����ϵ�� */
    VOS_UINT32                          ulPsDrxLength;      /* PS��DRX����ϵ�� */
    VOS_UINT32                          ulCellId;           /* ��ǰפ��С��ID  */
    WCDMA_BAND_SET_UN                   unWcdmaBand;        /*_H2ASN_Replace WCDMA_BAND_STRU                     stWcdmaBitBand; */
    VOS_UINT8                           ucCnCommonSize;     /* CN Common��Ϣ���ֽڳ���    */
    VOS_UINT8                           aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucCsInfoSize;       /* CS�������Ϣ���ֽڳ���     */
    VOS_UINT8                           aucCsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];

    VOS_UINT8                           ucPsInfoSize;       /* PS�������Ϣ���ֽڳ���     */
    VOS_UINT8                           aucPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    RRC_NAS_RESTRICTION_TYPE_STRU       stCsRestriction;    /* ��ӦPLMN ID CS������Ƿ����� */
    RRC_NAS_RESTRICTION_TYPE_STRU       stPsRestriction;    /* ��ӦPLMN ID PS������Ƿ����� */
    RRC_NAS_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;       /* ��ǰС����ϵͳ��ģʽ */
}RRMM_SYS_INFO_IND_STRU;


/* 7.2.2 ��Ϣ RRMM_PAGING_IND �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_PAGING_TYPE_ENUM_UINT32     ulPagingType;       /* Ѱ����Ϣ���ͣ�               */
    RRC_PAGE_CAUSE_ENUM_UINT32          ulPagingCause;      /* Paging Cause��               */
    RRC_PAGE_UE_ID_ENUM_UINT32          ulPagingUeId;       /* Paging Recorder Id��         */
}RRMM_PAGING_IND_STRU;

/* 7.2.3 ��Ϣ RRMM_SECURITY_IND �Ľṹ�� */
typedef struct
{
     MSG_HEADER_STRU                    MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
     RRC_SECURITY_RPT_MODE_ENUM_UINT32  ulRptMode;          /* ����ģʽ                                 */
}RRMM_SECURITY_IND_STRU;

/* 7.2.4 ��Ϣ RRRABM_RAB_IND �Ľṹ�� */
typedef struct
{
    VOS_UINT32                          ulRabId;            /* RAB ID             */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_PDCP_EXIST_FLAG_ENUM_UINT32 enPdcpFlg;          /* ��RAB�Ƿ����PDCP */
    VOS_UINT32                          ulRbNum;            /* ��RAB����RB����    */
    VOS_UINT32                          aulRbId[RRC_NAS_MAX_RB_PER_RAB];        /* ��RAB����RB ID                           */
    WUE_RLC_MODE_ENUM_UINT8             aenUlRlcMode[RRC_NAS_MAX_RB_PER_RAB];    /* RB��Ӧ��RLC��ULģʽ������RABM����ʱ����WTTF��������ʱ�ж� */
}RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    NAS_RRC_RAB_CHANGE_ENUM_UINT32      ulRabChangeType;    /* RAB�Ĳ������� */
    VOS_UINT32                          ulRabCnt;           /* ����RAB���������� */
    RAB_INFO_STRU                       aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_RAB_IND_STRU;

typedef RRRABM_RAB_IND_STRU             RRRABM_HANDOVER_RAB_IND_STRU;

/* 7.2.5 ��Ϣ RRRABM_RAB_RSP �Ľṹ�� */
typedef struct
{
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  enCnDomainId;       /* CN Domain ID                             */
    VOS_UINT32                          ulRabId;            /* RAB ID          */
    RRC_NAS_PPP_VALID_ENUM_UINT32       ulPppValid;         /* �Ƿ����PPPЭ�� */
    VOS_UINT32                          ulDeliveryErrSdu;
}RRRABM_RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;             /* �뽨��RAB��INDԭ����ͬ                   */
    VOS_UINT32                          ulRabCnt;           /* ����RAB����                              */
    RRRABM_RAB_INFO_STRU                aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_RAB_RSP_STRU;

typedef RRRABM_RAB_RSP_STRU             RRRABM_HANDOVER_RAB_RSP_STRU;

/* 7.2.6 ��Ϣ RRMM_SYNC_IND �Ľṹ�� */
/*****************************************************************************
 �ṹ��    : RRC_NAS_AMR_MODE_IND_STRU
 �ṹ˵��  : AMR���������ã��������޸�ʱ���ø�NAS��
             ����ͨ��enAmrModeCfgType֪ͨNAS��
             AMR������AMR�޸ģ�AMR���ʲ��䡣
*****************************************************************************/
typedef struct
{
    RRC_NAS_AMR_MODE_ENUM_UINT8         enUlAmrMode;
    RRC_NAS_AMR_MODE_ENUM_UINT8         enDlAmrMode;
    VOS_UINT8                           ucUlAmrRateCnt;
    RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8    aenUlAmrRate[RRC_NAS_MAX_AMR_RATE_NUM];
    VOS_UINT8                           ucDlAmrRateCnt;
    RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8    aenDlAmrRate[RRC_NAS_MAX_AMR_RATE_NUM];
}RRC_NAS_AMR_MODE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_SYNC_INFO_STRU
 �ṹ˵��  : NASͬ��ָʾ��RRC�ڿտ�Я����SYNC��Ԫʱ����NAS��
             ����տ�û��Я����������NAS��
             ulRabCnt = 0��ʾû��Я����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRabId;            /* RAB ID          */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    VOS_UINT8                           ucRabSyncInfo;      /* ��RAB��ͬ��ָʾ */

    VOS_UINT8                           aucReserve1[3];     /* ���� */
}RRMM_SYNC_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/

    VOS_UINT32                          ulRabCnt;           /* ��Ҫͬ��RAB������0��ʾ������ */
    RRMM_SYNC_INFO_STRU                 NasSyncInfo[RRC_NAS_MAX_RAB_SETUP];

    VOS_UINT8                           aucReserve1[3];     /* ���� */
    RRC_NAS_AMR_MODE_CFG_ENUM_UINT8     enAmrModeCfgType;   /* AMRģʽ�������� */
    RRC_NAS_AMR_MODE_IND_STRU           stAmrModeInd;
}RRMM_SYNC_IND_STRU;

/* 7.2.7 ��Ϣ RRRABM_STATUS_IND �Ľṹ�� */
typedef struct
{
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  enCnDomainId;       /* CN Domain ID    */
    VOS_UINT32                          ulRabId;            /* RAB ID        */
}RRRABM_STATUS_RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulRabCnt;           /* RAB���� */
    RRRABM_STATUS_RAB_INFO_STRU         aRab[RRC_NAS_MAX_RAB_SETUP];
    RRC_RAB_STATUS_ENUM_UINT32          ulStatus;           /* RAB��Ӧ�������� */
}RRRABM_STATUS_IND_STRU;


/* 7.2.8 ��Ϣ RRRABM_QOS_UPDATE_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulRabCnt;           /* RAB����                                  */
    RRRABM_RAB_INFO_STRU                aRab[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_QOS_UPDATE_REQ_STRU;

/* 7.2.9 ��Ϣ RRMM_NAS_INFO_CHANGE_REQ �Ľṹ�� */
typedef struct
{
    VOS_UINT8                           aucCk[RRC_NAS_CIPHER_KEY_LEN];          /* Cipher Key,�洢��ʽ�μ�31.102            */
    VOS_UINT8                           aucIk[RRC_NAS_INTEGRITY_KEY_LEN];       /* Integrity Key,�洢��ʽ�μ�31.102         */
}SECURITY_KEY_STRU;

typedef struct
{
    VOS_UINT8                           aucTmsi[RRC_NAS_TMSI_LEN];              /* �洢˳��μ�24.008 10.5.1.4�еĹ涨      */
    RRC_PLMN_ID_STRU                    stPlmnId;                               /* �洢˳��μ�24.008 10.5.1.3�еĹ涨��ǰ3
                                                                                   ���ֽ���Ч                               */
    VOS_UINT16                          usLac;                                  /* �洢˳��μ�24.008 10.5.1.3�еĹ涨��ǰ2
                                                                                   ���ֽ���Ч                               */
    VOS_UINT8                           aucReserve1[2];     /* ���� */
}NAS_INFO_TMSI_LAI_STRU;

typedef struct
{
    VOS_UINT8                           aucPtmsi[RRC_NAS_PTMSI_LEN];            /* �洢˳��μ�24.008 10.5.1.4�еĹ涨      */
    RRC_PLMN_ID_STRU                    stPlmnId;                               /* �洢˳��μ�24.008 10.5.5.15�еĹ涨��ǰ
                                                                                   3���ֽ���Ч                              */
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;

    VOS_UINT8                           aucReserve1[1];     /* ���� */
}NAS_INFO_PTMSI_RAI_STRU;

typedef struct
{
    VOS_UINT8                           ucEHPlmnNum;
    VOS_UINT8                           aucReserve[3];
    RRC_PLMN_ID_STRU                    astEHPlmnList[NAS_RRC_MAX_EHPLMN_NUM];
}NAS_INFO_EHPLMN_STRU;

typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    VOS_UINT32                          bitOpTmsiLai    : 1;
    VOS_UINT32                          bitOpPTmsiRai   : 1;
    VOS_UINT32                          bitDelKey       : 1;
    VOS_UINT32                          bitOpIdleMappedLSecurity    : 1;
    VOS_UINT32                          bitSpare        : 25;

    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    RRC_NAS_ATTACH_STATUS_ENUM_UINT32   ulAttach;           /* Attach��Deattach��־ */
    SECURITY_KEY_STRU                   SecurityKey;
    VOS_UINT32                          ulDrxLength;        /* PS��Э�̺��DRX����  */
    NAS_INFO_TMSI_LAI_STRU              TmsiLai;
    NAS_INFO_PTMSI_RAI_STRU             PTmsiRai;
}NAS_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulCnDomainCnt;      /* CN Domain���� */
    NAS_INFO_STRU                       aNasInfo[RRC_NAS_MAX_CN_DOMAIN];
}RRMM_NAS_INFO_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_CSFB_SERVICE_ABORT_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS֪ͨAS��ǰCSFB�ж�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ         */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];      /* ����   */
} RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND_STRU;

/***********************WAS�����ӿ�WAS��>MMC***********************************/
/*****************************************************************************
 Structure      : WRRMM_SCELL_RXLEV_IND_ST
 Description    : ֪ͨNAS����С���ź�ǿ�ȡ�
                  MsgHeader ������Ϣͷ
                  WRR-->NAS��MMCʵ��
*****************************************************************************/
/* 7.2.10 ��Ϣ WRRMM_SCELL_RXLEV_IND_ST �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_INT16                           sRxlev;             /* ����С���ź�ǿ���ϱ�RSCP����Χ-111~-24DB */
    VOS_UINT8                           aucReserve1[2];     /* ����   */
}WRRMM_SCELL_RXLEV_IND_ST;

/***********************WAS�����ӿ�WAS��>MMC********************************/
/* 7.2.11 ��Ϣ WRRMM_CHANNEL_QUAL_IND �Ľṹ�� */
/*****************************************************************************
Structure      : WRRMM_CHANNEL_QUAL_IND_ST
Description    : ��ר��ģʽ�£������Ե���NAS�ϱ�����С���ź�����
                 WRR-->NAS
                 MsgHeader ������Ϣͷ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           ucChannelQual;      /* �����ʼ���,0xFF��ʾû��,��0~6��7���ȼ� */
    VOS_UINT8                           aucReserve1[3];     /* ����   */
}WRRMM_CHANNEL_QUAL_IND_ST;

/***********************WAS�����ӿ�MMC��>WAS********************************/
/* 7.2.12 ��Ϣ RRMM_AT_MSG_REQ �Ľṹ�� */
/*****************************************************************************
Structure      : RRMM_AT_MSG_REQ_ST
Description    : MMC����WAS AT�����Ϣ�ϱ���Ϣ
                 NAS-->WRR
                 MsgHeader ������Ϣͷ
*****************************************************************************/
/* ��ϢRRMM_AT_MSG_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_AT_ACTION_ENUM_UINT8        ucActionType;
    VOS_UINT8                           ucMsgType;          /* �����ϱ����ͻ� */
    VOS_UINT8                           ucSignThreshold;    /* �źű仯����,��RSCP�仯������ֵ��
                                                               �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                           ucMinRptTimerInterval;     /* ����ϱ���ʱ��(0-20)S   */
}RRMM_AT_MSG_REQ_ST;

/***********************WAS�����ӿ�WAS��>MMC********************************/
/* 7.2.13 ��Ϣ RRMM_AT_MSG_CNF �Ľṹ�� */
/*****************************************************************************
Structure      : RRMM_AT_MSG_CNF_ST
Description    : WAS ��MMC�ϱ�REQ��ѯ�Ľ��
                 WRR-->NAS
                 MsgHeader ������Ϣͷ
*****************************************************************************/
/* ��ϢRRMM_AT_MSG_CNF�Ľṹ�� */
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* ����   */
    RRC_NAS_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;       /* aulCellId[0]С������ */
    VOS_UINT8                           ucIDNum;            /* С��ID�� */
    VOS_UINT32                          aulCellId[RRC_NAS_AT_CELL_MAX_NUM];
}RRC_NAS_CELL_ID_ST;

/* С���ź�ǿ�Ƚṹ�� */
typedef struct
{
    VOS_UINT32                          ulCellId;
    VOS_INT16                           sCellRSCP;
    VOS_INT16                           sRSSI;     /* RSSI  */
}RRC_NAS_CELL_RSCP_ST;

/* С���ź�ǿ�Ƚṹ�б� */
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* ����   */
    VOS_UINT16                          usCellNum;          /* С������ */
    RRC_NAS_CELL_RSCP_ST                stCellRscp[RRC_NAS_AT_CELL_MAX_NUM];
    VOS_UINT16                          usCellDlFreq;       /*С��Ƶ��(����)*/
    VOS_UINT16                          usCellUlFreq;       /*��ǰƵ��(����)*/
    VOS_INT16                           sUeRfPower;         /*���书��*/
    PS_BOOL_ENUM_UINT8                  enCritSValid;       /* S׼���־�Ƿ���Ч��PS_TRUE��ʾenNotFullfilCritS��Ч,D̬��F̬�²��������־ */
    PS_BOOL_ENUM_UINT8                  enNotFullfilCritS;  /* �Ƿ�����S׼��,PS_TRUE��ʾ������ */
}RRC_NAS_CELL_RSCP_STRU_LIST;


typedef struct
{
    VOS_UINT8                           ucDlTrChBler;       /* BLER */
    VOS_UINT8                           ucTrChId;           /* �����ŵ�ID */
    VOS_UINT8                           aucReserve1[2];     /* ����   */
}RRC_NAS_CELL_TRCH_BLER_ST;

/* �ŵ�����ṹ���б� */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* ����   */
    VOS_UINT8                           ucTrchNum;          /* �����ŵ����� */
    RRC_NAS_CELL_TRCH_BLER_ST           stTrchBlerInfo[RRC_NAS_AT_MAX_TRCH];
}RRC_NAS_CELL_TRCH_BLER_STRU_LIST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_AT_ACTION_ENUM_UINT8        ucActionType;
    VOS_UINT8                           ucMsgType;          /* ���ֽ������Ӧ��Ϣ */
    RRC_NAS_AT_MSG_FLAG_ENUM_UINT8      ucMsgFlg;           /* ���͵�CNF�е���Ϣ�Ƿ���Ч;���AS��ǰû�д���Ϣ�����ݣ���д��Ч������������ʽ����������ʱ��ͨ��IND��ʽ���ϱ� */
    VOS_UINT8                           ucDataLen;          /* ���ݳ��� */
    VOS_UINT8                           aucData[4];         /* �������� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

}RRMM_AT_MSG_CNF_ST;

/***********************WAS�����ӿ�WAS��>MMC********************************/
/* 7.2.14 ��ϢRRMM_AT_MSG_IND�Ľṹ�� */
/*****************************************************************************
Structure      : RRMM_AT_MSG_IND_ST
Description    : WAS ��MMC�����ϱ�REQ��ѯ�Ľ��
                 WRR-->NAS
                 MsgHeader ������Ϣͷ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[2];     /* ����   */
    RRC_NAS_AT_MSG_TYPE_ENUM_UINT8      ucMsgType;
    VOS_UINT8                           ucDataLen;          /* ���ݳ��� */
    VOS_UINT8                           aucData[4];         /* �������� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

}RRMM_AT_MSG_IND_ST;

/* 7.2.15 OM��WAS��Ϣ�ṹ���壬��Ϣ���궨�岻�ڱ��ļ���                    */
/***********************************BEGIN***********************************/
#define   OM_RRCF_CELLPARA_REQ                0x3201        /*OM��RRCF������С��������ѯ�����MsgID*/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
}RRCF_CELLPARA_REQ_ST;

#define   RRCF_OM_CELLPARA_CNF                0x3202        /*RRCF�ظ�С��������MsgID*/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
    VOS_UINT32                          ulDataLen;          /* ���ݳ���  */
    VOS_UINT8                           aucData[4];         /* �������� */
} RRCF_CELLPARA_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
}RRC_GET_CELL_INFO_REQ_ST;

typedef struct
{
    RRC_PLMN_ID_STRU                    PlmnId;
    VOS_UINT32                          ulPrimCode;         /* С�������� */
    VOS_UINT32                          ulFreq;             /* С��Ƶ�� */
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcN0;
    VOS_UINT8                           ucCellID;           /* С��ID */
    VOS_UINT8                           ucPlmnFlag;         /* PLMN �Ƿ���Ч������ʾ��Ч������ʾ��Ч */
    VOS_UINT8                           ucRscpFlg;          /* ����ʾ��Ч������ʾRSCP��Ч */
    VOS_UINT8                           ucEcN0Flg;          /* ����ʾ��Ч������ʾEcN0��Ч */
}WAS_OM_CELL_INFO_ST;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* ����   */
    VOS_UINT8                           ucCellNum;          /* �ϱ�С���� */
    WAS_OM_CELL_INFO_ST                 stCellInfo[RRC_CELL_INFO_MAX_NUM];
} WAS_CELL_INFO_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulDataLen;          /* ���ݳ���  */
    VOS_UINT8                           aucData[4];         /* �������� ,��������ΪWAS_CELL_INFO_CNF_ST */
}RRC_GET_CELL_INFO_CNF_ST;

#if 0

/* ����WasMntnģ�� */

#define CONSOLE_WAS_TRANSPORT_REQ         0x5000
#define WAS_CONSOLE_TRANSPORT_CNF         0x5001
#define PSTAS_RRCF_SERVICECELLINFO_REQ    0x5200
#define PSTAS_RRCF_SERVICECELLINFO_CNF    0x5201

typedef struct
{
    VOS_MSG_HEADER                             /* ������Ϣ��Ϣͷ�������len��usMsgType��ʼ���� */
    VOS_UINT16 usMsgType;                      /* ������Ϣ����0x5001��0x5FFF����ģ�黮�ֹ������ */
    VOS_UINT16 usTransId;                      /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��� */
    VOS_UINT8  astMsg[4];                      /* ��Ϣ�ṹָ�룬ָ������Я������Ϣ���� */
}WAS_DEBUG_MSG_ST;

typedef struct
{
    VOS_MSG_HEADER                             /* ͸��ͨ����Ϣͷ�������len��usMsgID��ʼ���� */
    VOS_UINT16      usMsgID;                   /* ͸��ͨ����Ϣ���ͣ��̶�Ϊ0x5000 */
    VOS_UINT16      usSubId;                   /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣��̶�Ϊ0 */
    WAS_DEBUG_MSG_ST    stDebug;               /* ������Ϣ��Ϣ*/
}WAS_TRANS_COMM_MSG_ST;

#endif



/* BEGIN: Added by liuyang id:48197, 2006/6/5   PN:A32D04222*/
/***********************�����ӿ�MMC��>WAS***************************/
/* 7.2.16 ��Ϣ RRMM_SET_WCDMA_BAND_REQ �ṹ�� */
/* ˵��������Ϣ��MMC����WAS������Ƶ��ԭ�*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_WCDMA_BAND_TYPE_ENUM_UINT32     ulWasDlFreqInfo;    /* WAS����Ƶ��  */
}RRMM_SET_WCDMA_BAND_REQ_ST;

/***********************�����ӿ�WAS��>MMC***************************/
/* 7.2.17 ��Ϣ RRMM_SET_WCDMA_BAND_CNF �ṹ�� */
/*******************************************************************************
˵��������Ϣ��AS��֪ͨNAS���Ѿ��յ�����Ƶ�����󲢿���������Ӧ��AS
      �����µ�Ƶ���Ϸ���С���������ɹ����ϱ�ϵͳ��Ϣ�������ɹ������ϱ�����
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    WAS_CHANGE_BAND_RESULT_ENUM_UINT32  ulResult;           /* �յ�WCDMAƵ�����ý��  */
}RRMM_SET_WCDMA_BAND_CNF_ST;


/* END:   Added by liuyang id:48197, 2006/6/5   PN:A32D04222*/
/***********************************END************************************/


/* 7.3 GASר����Ϣ */
/***********************GAS�����ӿ�GAS��>MMC***************************/
/* 7.3.1 ��Ϣ GRRMM_SYS_INFO_IND �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU                    PlmnId;             /* ��С��PLMN ID */
    GSM_BAND_SET_UN                     unGsmBand;          /*_H2ASN_Replace GSM_BAND_STRU                       stGsmBitBand; */
    VOS_UINT16                          usCellId;           /* ��С�� ID  */
    VOS_UINT16                          usLac;              /* [0x0001��0xFFFE] λ������  */
    VOS_UINT8                           ucAttachDetach;     /* [0-1] ����֪ͨMS���ڱ�С�����Ƿ���Ҫ����IMSI��Ϻͷ����������:
                                                               0��ʾ����Ҫ�ֻ�����IMSI���źͷ�����̣�
                                                               1���ʾ�ֻ������������źͷ�����̣�message origin:SI3,PSI2 */
    VOS_UINT8                           ucLRTimerT3212;     /* [0-255] ����λ�ø��¶�ʱ��,ȷ�����ֻ���������λ�ø��µ�Ƶ��,
                                                               ÿ1����λ��ʾ6���ӵ�ʱ�䣬Ϊ0���ʾ������λ�ø��£�message origin:SI3,PSI2 */
    VOS_UINT8                           ucGprsSupportInd;   /* [0-1] GPRS֧��ָʾ:0-��֧��;1-֧��*/
    VOS_UINT8                           ucRac;              /* ·��������*/
    GRRMM_NW_OP_MODE_ENUM_UINT8         ucNetworkOperationMode;       /*   ��������ģʽ */
    VOS_UINT8                           ucDrxTimerMax;      /* [0,1,2,4,8,16,32,64]s   */
    GRRMM_MSG_REL_VER_ENUM_UINT8        ucMsrRelease;       /* [0-1] 0 MSC is Release '98 or older
                                                               1 MSC is Release '99 onwards */
    GRRMM_SGSN_REL_VER_ENUM_UINT8       ucSgsnRelease;       /* [0-1] 0 SGSN is Release '98 or older
                                                               1 SGSN is Release '99 onwards */
    RRC_NAS_RESTRICTION_UN              unAcInfo;	     /*_H2ASN_Replace RRC_NAS_RESTRICTION_ENUM_UINT8            unAcInfo; */
    GRRMM_BAND_INDICATOR_ENUM_UINT8     ucBandIndicator;     /* ��ǰ������ָʾ:1800��1900  0��ʾ1800��1��ʾ1900*/
    VOS_UINT8                           aucReserve[2];
}GRRMM_SYS_INFO_IND_ST;


/***********************GAS�����ӿ�GAS��>MM/GMM*************************/
/* 7.3.2 ��Ϣ GRRMM_PAGING_IND �Ľṹ�� */
/* ��RR��GRR���������յ�Ѱ����Ϣ��RR��GRRӦ�ü��MS identity������MS�����ƥ�䣬
   ������RR���ӳɹ��󣬷���GRRMM_PAGING _INDԭ��ָʾNAS */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    GAS_MS_IE_TYPE_ENUM_UINT8           ucMSIDType;         /* TMSI or IMSI or PTMSI */
    GAS_PAGING_TYPE_ENUM_UINT8          ucPagingType;       /* CS or PS */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}GRRMM_PAGING_IND_ST;

/***********************GAS�����ӿ�GAS��>GMM*************************/
/* ��UL&UL TBF�ͷ�ʱ��GAS֪ͨGMM,GMM�յ��������Ҫ����ATTACH�����̷���ATTACH���� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];      /* 4�ֽڶ��룬���� */
}GRRGMM_TBF_REL_IND_ST;

/***********************GAS�����ӿ�GAS��>MM***************************/
/*********************************************************************
 Structure      : GAS_RR_SYNC_IND_ST
 Description    : ����ṹ������MO��MT����RR���Ӻ�ͬ�������ݽӿڣ�
                  MsgHeader ������Ϣͷ
                  RR-->NAS
                  RR_SYNC_IND
                  ʹ������ṹ �μ�  24.007
***********************************************************************/
/* 7.3.3 ��Ϣ GAS_RR_SYNC_IND �Ľṹ�� */
/* uiSynCauseȡֵ */
#define   RR_SYN_CIPH                   0   /*��������*/
#define   RR_SYN_TCH                    1   /*�ŵ�ָ�����*/
#define   RR_SYN_TCH_MODIFY             2   /*�ŵ�ģʽ�޸�*/
#define   RR_SYN_GSM_GSM_HANDOVER       3
#define   RR_SYN_WCDMA_GSM_HANDOVER     4

/* uiSynCauseȡֵΪRR_SYN_CIPHʱucSynValue��ȡֵ */
#define   RR_CIPHER_ALGORITHM_A51       0   /* �����㷨A5/1,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A52       1   /* �����㷨A5/2,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A53       2   /* �����㷨A5/3,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A54       3   /* �����㷨A5/4,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A55       4   /* �����㷨A5/5,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A56       5   /* �����㷨A5/6,��Э��R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A57       6   /* �����㷨A5/7,��Э��R4,44018,10.5.2.9 */
#define   RR_NO_CIPHER                  8   /* ����ֹͣ */

/* uiSynCauseȡֵΪRR_SYN_TCH��RR_SYN_TCH_MODIFYʱucSynValue��ȡֵ */
#if 0
#define   RR_CHAN_MOD_SINGAL_ONLY       0   /* ������ģʽ*/
#define   RR_CHAN_MOD_FR                1   /* Full Rate */
#define   RR_CHAN_MOD_EFR               2   /* Enhanced Full Rate  */
#endif

#define   RR_CHAN_MOD_AMR               3   /* Adaptive Multi-Rate */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           ucSynCause;
    VOS_UINT8                           ucSynValue;
    GRR_NAS_SYNC_TCH_RATE_ENUM_UINT8    ucTchRate;
    VOS_UINT8                           aucReserve1[1];     /* ����   */
}GAS_RR_SYNC_IND_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_RR_CHANNEL_MODE_ENUM_U8         enChanMod;          /* �ŵ�ģʽ   */
    VOS_UINT8                           aucReserve1[3];     /* ����   */
}GAS_RR_CHAN_MOD_IND_ST;

/***********************GAS�����ӿ�GAS��>GMM***********************************/
/*****************************************************************************
 Structure      : RRMM_GPRS_SUSPEND_IND_ST
 Description    : ֪ͨNAS����GPRS��
                  MsgHeader ������Ϣͷ
                  RR-->NAS��GMMʵ��
                  RRMM_GPRS_SUSPEND_IND
                  ʹ������ṹ �μ�  24.007
*****************************************************************************/
/* 7.3.4 ��Ϣ RRMM_GPRS_SUSPENSION_IND_ST �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
}RRMM_GPRS_SUSPEND_IND_ST;

/***********************GAS�����ӿ�GAS��>GMM***********************************/
/*****************************************************************************
 Structure      : RRMM_GPRS_RESUME_IND_ST
 Description    : ֪ͨNAS�ָ�GPRS��
                  MsgHeader ������Ϣͷ
                  RR-->NAS��GMMʵ��
                  RRMM_GPRS_RESUME_IND
                  ʹ������ṹ �μ�  24.007
*****************************************************************************/
/* 7.3.4 ��Ϣ RRMM_GPRS_RESUME_IND_ST �Ľṹ�� */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    GRR_GMM_GPRS_RESUME_RESULT_ENUM_UINT8   ucResult;
    VOS_UINT8                           aucReserve1[3];     /* ����   */
}RRMM_GPRS_RESUME_IND_ST;

/***********************GAS�����ӿ�GAS��>MMC***********************************/

#define GRRMM_SCELL_MEAS_TYPE_NONE                              0x00               /* AT��ѯ�ϱ�  */
#define GRRMM_SCELL_MEAS_TYPE_RXLEV                             0x01               /* RXLEV�仯�������ϱ� */
#define GRRMM_SCELL_MEAS_TYPE_RXQUALITY                         0x02               /* RXQUALITY�仯�������ϱ� */
#define GRRMM_SCELL_MEAS_TYPE_CELLID                            0x04               /* CELL ID�仯�������ϱ� */



typedef struct
{
    VOS_UINT8                          ucMeasRxlevType          :1;             /* Rxlev�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                          ucMeasRxqualityType      :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                          ucMeasCellIdType         :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                          ucMeasTypeSpare5         :5;
}GRRMM_SCELL_MEAS_TYPE_STRU;
typedef union
{
    VOS_UINT8                             ucMeasReportType;

    GRRMM_SCELL_MEAS_TYPE_STRU            stMeasReportType;
}GRRMM_SCELL_MEAS_REPORT_TYPE_UN;
/*****************************************************************************
Structure      : GRRMM_SCELL_MEAS_IND_ST
Description    : GCOM�����Ե���NAS�ϱ�����С���ź�ǿ��
                  RR-->NAS
                  MsgHeader ������Ϣͷ

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_INT16                           sRxlev;             /* ����С���ź�ǿ�� */
    VOS_UINT8                           ucChannelQual;      /*�����ʼ���,99��ʶû�� */

    GRRMM_SCELL_MEAS_REPORT_TYPE_UN     unMeasReportType;   /* �����ϱ�������   */ /*_H2ASN_Replace GRRMM_SCELL_MEAS_TYPE_STRU            stMeasReportType; */

    VOS_UINT16                          usCellId;
    VOS_UINT16                          usCellDlFreq;       /*С��Ƶ��(����)*/
    VOS_UINT16                          usCellUlFreq;       /*��ǰƵ��(����)*/
    VOS_INT16                           sUeRfPower;         /*���书��,RRMM_UE_RFPOWER_INVALID��Чֵ*/
}GRRMM_SCELL_MEAS_IND_ST ;

/***********************GAS�����ӿ�MM/GMM��>GAS********************************/
/*****************************************************************************
 Structure      : GRRMM_NAS_INFO_CHANGE_REQ_STRU
 Description    : ��GSM������NAS��Ϣ�ı�֪ͨ�����
*****************************************************************************/
/* 7.3.6 ��Ϣ GRRMM_NAS_INFO_CHANGE_REQ �Ľṹ�� */
typedef struct
{
    VOS_UINT8                           aucKc[RR_NAS_KC_LEN];                   /* GPRS Ciphering key,�洢��ʽ�μ�TS31.102-4.4.3.2*/
}GAS_SECURITY_KEY_ST;

typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    VOS_UINT32                          bitOpTmsiLai    : 1;
    VOS_UINT32                          bitOpPTmsiRai   : 1;
    VOS_UINT32                          bitOpDelKey     : 1;
    VOS_UINT32                          bitOpGmmState   : 1;
    VOS_UINT32                          bitOpReadyTime  : 1;
    VOS_UINT32                          bitOpGprsMode   : 1;
    VOS_UINT32                          bitOpIdleMappedLSecurity   : 1;
    VOS_UINT32                          bitSpare        : 22;
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    NAS_GSM_ATTACH_TYPE_ENUM_UINT32     ulAttach;           /* Attach��Deattach��־��   */
    GAS_SECURITY_KEY_ST                 stSecurityKey;
    VOS_UINT32                          ulDrxLength;        /* PS��Э�̺��DRX����      */
    VOS_UINT32                          ulSplitPgCycle;     /* DRX������Split PG Cycle��ֵ */
    NAS_INFO_TMSI_LAI_STRU              stTmsiLai;
    NAS_INFO_PTMSI_RAI_STRU             stPtmsiRai;
    VOS_UINT32                          ulReadyTimerValue;  /* READY TIMER ��ǰ��С */
    NAS_GMM_STATE_ENUM_UINT8            ucGsmGmmState;      /* GMM״̬  */
    NAS_GSM_GPRS_MODE_ENUM_UINT8        ucMsGprsMode;       /* MS GPRS ģʽ */
    VOS_UINT8                           aucReserve1[2];     /* ����   */
}GAS_NAS_INFO_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    GAS_NAS_INFO_ST                     stNasInfo;
}GRRMM_NAS_INFO_CHANGE_REQ_STRU;

/***********************GAS�����ӿ�GMM��>GRR***************************/
/* 7.3.7 ��Ϣ GRRGMM_ASSIGN_REQ �Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulTlli;             /* ��ǰ��Ч��TLLIֵ */
    VOS_UINT32                          ulOldTlli;          /* ׼��ȥָ���TLLIֵ */
    GMM_GRR_TLLI_CAUSE_ENUM_UINT32      ulTlliCause;        /* ����TLLI��ԭ��ֵ */
}GRRGMM_ASSIGN_REQ_ST;

/***********************GAS�����ӿ�MMC��>GAS********************************/
/* 7.3.8 ��Ϣ RRMM_NAS_PARAMS_REQ �Ľṹ�� */
/*Description   : MMC��RR�����û�ѡ���Ƶ����Ϣ
                  NAS��MMC�� GGCOM
                  MsgHeader ������Ϣͷ

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    MMC_CM_BAND_ENUM_UINT32             ulBand;             /* �û�ѡ���Ƶ�� */
}RRMM_NAS_PARAMS_REQ_ST;

/***********************GAS�����ӿ�MM��>GAS********************************/
/* 7.3.9 ��Ϣ GRRMM_EST_SAPI3_REQ �Ľṹ�� */
/*Description   : MM����GAS����SAPI3
                  NAS��MM��GGCOM
                  MsgHeader ������Ϣͷ

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
}GRRMM_EST_SAPI3_REQ_ST;

/***********************GAS�����ӿ�GAS��>MM********************************/
/* 7.3.10 ��Ϣ GRRMM_EST_SAPI3_CNF �Ľṹ�� */
/*Description   : GAS��MM������SAPI3�Ļ�Ӧ
                  GGCOM NAS��MM)
                  MsgHeader ������Ϣͷ

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    MM_EST_RESULT_ENUM_UINT8            ucResult;           /* �������  */
    VOS_UINT8                           aucReserve1[3];     /* ����   */
}GRRMM_EST_SAPI3_CNF_ST;

/***********************GAS�����ӿ�MM��>GAS********************************/
/* 7.3.11 ��Ϣ GRRMM_AT_MSG_REQ �Ľṹ�� */
/*Description   : MM��GAS�������������ϱ�����Ϣ�ṹ
                  GGCOM NAS��MM)
                  MsgHeader ������Ϣͷ

*****************************************************************************/
/* ��ϢRRMM_AT_MSG_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    GAS_NAS_AT_ACTION_TYPE_ENUM_UINT8   ucActionType;       /* ֻ����RSSI��BER */
    VOS_UINT8                           ucSignThreshold;    /* �źű仯����,��RSSI�仯������ֵ��
                                                               �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                           ucMinRptTimerInterval;     /* ����ϱ���ʱ��(0-20)S   */
    VOS_UINT8                           aucReserve1[1];     /* ����   */
}GRRMM_AT_MSG_REQ_ST;

/***********************AS�ӿ�GMM��>GAS********************************/
/* 7.3.12 ��Ϣ RRMM_GMM_PROC_NOTIFY_STRU �Ľṹ�� */
/*Description   : GMMָʾGMM ATTACH��RAU�������
                  NAS��GMM��
                  MsgHeader ������Ϣͷ

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      usGmmProcType;        /* GMM�������� */
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      usGmmProcFlag;        /* GMM���̱�־ */
}RRMM_GMM_PROC_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_GMM_PROC_ENQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16                     enGmmConnType;
    VOS_UINT8                                               aucReserve[2];
}RRMM_GMM_PROC_ANS_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulT3302TimerLen;    /* Timerʱ��(��λ������) */
}RRMM_AUTH_FAIL_NOTIFY_REQ_STRU;
enum NAS_GPRS_ACCESS_RESULT_ENUM
{
    NAS_GPRS_ACCESS_SUCCESS             = 0,                                    /* GPRS����ɹ� */
    NAS_GPRS_ACCESS_FAIL                = 1                                  /* GPRS����ʧ�� */
};
typedef VOS_UINT32 NAS_GPRS_ACCESS_RESULT_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */ /*_H2ASN_Skip*/
    NAS_GPRS_ACCESS_RESULT_ENUM_UINT32  enResult;                               /* GPRS������ */
}GRRGMM_GPRS_ACCESS_RESULT_IND_STRU;

/***********************�����ӿ�MMC��>GAS***************************/
/* 7.3.12 ��Ϣ RRMM_SET_GSM_BAND_REQ �ṹ�� */
/* ˵��������Ϣ��MMC����AS������Ƶ��ԭ�*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_GSM_BAND_TYPE_ENUM_UINT32       ulGsmBandInfo;      /* GSMƵ����Ϣ  */
}RRMM_SET_GSM_BAND_REQ_ST;

/***********************�����ӿ�AS��>MMC***************************/
/* 7.1.29 ��Ϣ RRMM_SET_GSM_BAND_CNF �ṹ�� */
/* ˵��������Ϣ��GAS��֪ͨNAS���Ѿ��յ�����Ƶ�����󲢿���������Ӧ��GAS
�����µ�Ƶ���Ϸ���С���������ɹ����ϱ�ϵͳ��Ϣ�������ɹ������ϱ�����
*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    GAS_CHANGE_BAND_RESULT_ENUM_UINT32  ulResult;           /* �յ�GSMƵ�����ý��  */
}RRMM_SET_GSM_BAND_CNF_ST;

/***********************�����ӿ�GAS��>MMC***************************/
/* 7.3.30 ��Ϣ GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND �ṹ�� */
/* ˵��������Ϣ��GAS����NAS�ϱ�MS RADIO ACCESS CAPABILITIES*/
typedef struct
{
    MSG_HEADER_STRU    MsgHeader;                                       /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT8          aucData[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];    /* RAC��Ϣ�������� */
}GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU;

/* 9.2 AS ��ȡ MM/GMM ��ȫ��Ϣ�ӿ� �������ӿڣ� */
typedef struct
{
    MM_SECURITY_MASK_ENUM_UINT8         ucInfoMask;         /* ��Ϣ������Ч��־ */
    VOS_UINT8                           aucCk[RRC_NAS_CIPHER_KEY_LEN];          /* Cipher Key        */
    VOS_UINT8                           aucIk[RRC_NAS_INTEGRITY_KEY_LEN];       /* Integrity Key     */
    VOS_UINT8                           aucKc[RR_NAS_KC_LEN];                   /* GSM cipher key Kc */
    VOS_UINT8                           aucImsi[RRC_NAS_IMSI_MAX_LEN];          /* 15 digits */
    VOS_UINT8                           ucCksn;             /* Ciphering Key Sequence Number */
    VOS_UINT8                           aucPTMSI[RRC_NAS_PTMSI_LEN];            /* P/TMSI */
    VOS_UINT8                           aucReserve1[2];     /* ����   */

}MM_CSPS_INFO_ST;

/* 9.3 NAS ��ȡ BAND ��Ϣ�ӿ� �������ӿڣ� */
#define AS_NAS_BAND_INVALID_FLAG    0xFFFFFFFF      /* BAND��Ϣ��Чָʾ����RR���ʹ˽ṹʱ����Ҫ��WRRƵ����Ϣ��Ϊ��Ч*/
typedef struct
{

    VOS_UINT32                          ulRrBandInfo;       /* (32bit) RR��ǰ����С��band��Ϣ */
    VOS_UINT32                          ulWrrBandInfo;      /* (32bit) WRR��ǰ����С��band��Ϣ */

}AS_NAS_SCELL_BAND_INFO_ST;

/* 9.4 AS ��ȡ ͨ�����ô˽ӿ�����ȡNAS�������Ϣ������˵PLMN����Ϣ�ȡ��������ӿڣ� */

typedef struct
{
    VOS_UINT32                          bitOpCurPlmn: 1;                        /* ָʾstCurCampedPlmnId�ֶ��Ƿ���Ч���ֶ�����ģʽ��
                                                                                �����ǰפ�����粻���û�ָ��plmn���ֵΪ0����ǰפ��������Ч */
    VOS_UINT32                          bitSpare     : 31;
    RRC_PLMN_ID_STRU                    stCurCampedPlmnId;

    VOS_UINT32                          ulPlmnIdNum;                            /* ��Чplmn���� */
    RRC_PLMN_ID_STRU                    aPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* ��Чplmn��Ϣ*/
}RRC_EPLMN_INFO_STRU;


typedef struct
{
    RRC_EPLMN_INFO_STRU                 stEplmnInfo;

    VOS_UINT32                          ulForbLaNum;        /* ��ֹע�����ĸ��� */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];
}PLMN_INFO_LIST_ST;

typedef struct
{
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;
}MM_SIM_INFO_ST;

typedef struct
{
    PLMN_INFO_LIST_ST                   stPlmnInfo;
    MM_SIM_INFO_ST                      stSimInfo;
    /*add,sunxibo,2007-06-12,for GCF 20.7 begin*/
    RRC_PLMN_ID_STRU                    stCurPlmnId;
    VOS_UINT16                          usCurLac;
    VOS_UINT8                           ucCurRac;
    VOS_UINT8                           ucUeOperMode;
    /*add,sunxibo,2007-06-12,for GCF 20.7 end*/
}MM_INFO_ST;


/*  9.5 WASͨ������ԭ��֪ͨRABM�ͷ�������Դ������Ϣ��״̬�޹أ�
    RABM���κ�ʱ��Ӧ����ȷ��Ӧ����ԭ�ʹ�����쳣ʱ��RABM������ȫ�ͷ� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* �ֽڶ��� */
}RRRABM_REL_ALL_REQ_STRU;

/********************************************************************************
  9.6 ��ϵͳ�л�������ѡ������NAS������ʱ����ʱ����GAS����WAS�����ͷ�����
********************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* �ֽڶ��� */
}RRMM_SUSPEND_REL_REQ_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* �ֽڶ��� */
}RRMM_SUSPEND_REL_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enQueryWPlmn;       /* PS_TRUE ��ʾ��ѯW �µ�PLMN,NAS�ϱ�HPLMN��RPLMN,PS_FALSE ��ѯG��PLMN*/
    VOS_UINT8                           aucReserve1[3];     /* �ֽڶ��� */
}RRMM_PLMN_QUERY_REQ_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_EPLMN_QUERY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ѯ��ЧPLMN��Ϣ�Ľӿ�
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/

    VOS_UINT8                           aucReserve1[4];     /* �ֽڶ��� */
}RRMM_EPLMN_QUERY_REQ_STRU;


/*******************************************************************************
 �ṹ��    : RRMM_EPLMN_QUERY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS�ظ������RRMM_EPLMN_QUERY_REQ��ѯ��Ϣ�Ľӿ�
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpCurPlmn: 1;                        /* ָʾstCurCampedPlmnId�ֶ��Ƿ���Ч���ֶ�����ģʽ��
                                                                                   �����ǰפ�����粻���û�ָ��plmn���ֵΪ0����ǰפ��������Ч */
    VOS_UINT32                          bitSpare     : 31;
    RRC_PLMN_ID_STRU                    stCurCampedPlmnId;

    VOS_UINT32                          ulEPlmnIdNum;        /* PLMN ID���� */
    RRC_PLMN_ID_STRU                    astEPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* PlMN��ʶ */
}RRMM_EPLMN_QUERY_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* �ֽڶ��� */
}WRRMM_TBAR_EXPIRED_IND_STRU;
/********************************************************************************
  9.7 TC��RRCF����TC_RRCF_TEST_CONTROL��Ϣ������TC����ʱ���BBP��������
********************************************************************************/
/*ԭ��ID*/
#define     TC_RRCF_TEST_CONTROL            0x100
/*ģʽ��Ϣ*/
#define     TC_RRCF_ACT_TEST_MODE           0         /*�������ز���ģʽ*/
#define     TC_RRCF_DEACT_TEST_MODE         1         /*ֹͣ���ز���ģʽ*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32      ulMsgName;
    VOS_UINT32      ulMode;
}TC_RRCF_TEST_CONTROL_MSG;



typedef struct
{
    VOS_UINT32                          bitOpUsimValid      :1;
    VOS_UINT32                          bitOpLTECapability  :1;                   /* LTE�����Ƿ����ı��OP��,����enLCapabilityStatus�Ƿ���Ч */
    VOS_UINT32                          bitOpUTRANCapability : 1;
    VOS_UINT32                          bitOpGSMCapability  : 1;

    VOS_UINT32                          bitOpHPlmn          : 1;
    VOS_UINT32                          bitOpEHPlmn         : 1;
    VOS_UINT32                          bitSpare            : 26;

    RRC_NAS_USIM_STATUS_ENUM_UINT32                         enUsimStatus;       /* ��־USIM����״̬ */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enLCapabilityStatus;/* ��־LTE����ʹ�ܵ�״̬ */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enUCapabilityStatus;/* ��־UTRAN����ʹ�ܵ�״̬ */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enGCapabilityStatus;/* ��־GSM����ʹ�ܵ�״̬ */
    VOS_UINT8                                               aucReserve[1];

    RRC_PLMN_ID_STRU                    stHPlmn;
    NAS_INFO_EHPLMN_STRU                stEHPlmn;

} NAS_COMM_INFO_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_NAS_COMM_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_NAS_COMM_INFO_CHANGE_REQ �Ľṹ
             ����ϢΪWAS��GASͬNAS������Ϣ����MMC������
             ��Ҫ���������·������޹صĲ���:��USIM��״̬�ȡ�
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_COMM_INFO_STRU                  stNasCommInfo;
} RRMM_NAS_COMM_INFO_REQ_STRU;



/*******************************************************************************
 �ṹ��    : USER_SET_FREQ_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�ζ���
*******************************************************************************/
typedef struct
{
    WCDMA_BAND_SET_UN                   unWcdmaBand;        /*_H2ASN_Replace WCDMA_BAND_STRU                     stWcdmaBitBand; */
    GSM_BAND_SET_UN                     unGsmBand;          /*_H2ASN_Replace GSM_BAND_STRU                       stGsmBitBand; */
}USER_SET_FREQ_BAND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM��״̬ */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;
    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* Ƶ�� */

    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* ��ģ�����ȼ� */
    VOS_UINT8                           aucReserved[3];
}RRMM_SYS_CFG_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/

    VOS_UINT32                          ulAvailPlmnIdNum;        /* PLMN ID���� */
    RRC_PLMN_ID_STRU                    astAvailPlmnIdList[NAS_RRC_MAX_AVAILPLMN_NUM];      /* PlMN��ʶ */
}RRMM_PLMN_QUERY_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_SYS_CFG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_SYS_CFG_CNF�Ľṹ
             ����ϢΪWAS��GAS������RRMM_SYS_CFG_REQ��Ϣ��Ļظ�ȷ����Ϣ
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRMM_SYS_CFG_RESULT_ENUM_UINT32     ulResult;
}RRMM_SYS_CFG_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_CELL_RESELECT_IND_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_CELL_RESELECT_IND�Ľṹ
             ����Ϣ����֪ͨNAS��ʼ�����С����ѡ����
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRMM_CELL_RESEL_PROC_ENUM_UINT8     ucCellReselProc;
    VOS_UINT8                           aucReserve1[3];     /* ����   */
}RRMM_CELL_RESELECT_IND_ST;

/*******************************************************************************
 �ṹ��    : RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_INTER_RAT_HANDOVER_INFO_REQ �Ľṹ
             ����Ϣ�����������ȡinter rat hand over info��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* �����ֶ�,���ڽ�����չ */
}RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_INTER_RAT_HANDOVER_INFO_CNF �Ľṹ
             ����Ϣ������NAS�ظ� inter rat hand over info��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* ��Ϣͷ */         /*_H2ASN_Skip*/
    VOS_UINT16                         usDataLen;
    VOS_UINT8                          aucData[RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN];
}RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ����   */
}RRMM_NOT_CAMP_ON_IND_STRU;

/*******************************************************************************
 �ṹ��    : RRMM_BG_PLMN_SEARCH_STATUS_IND_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_BG_PLMN_SEARCH_STATUS_IND�Ľṹ
             ����Ϣ����֪ͨNAS�Ƿ�������BG����
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ����   */
}RRMM_BG_PLMN_SEARCH_STATUS_IND_ST;

/*******************************************************************************
 �ṹ��    : RRMM_BG_PLMN_SEARCH_REQ_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_BG_PLMN_SEARCH_REQ�Ľṹ
             ����Ϣ����֪ͨ����㷢��BG����
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRMM_PLMN_WITH_RAT_STRU             stPlmnId;           /* PlMN��ʶ */

    VOS_UINT32                          ulForbLaNum;        /* ��ֹע�����ĸ��� */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];   /* ��ֹLAI��Ϣ */

}RRMM_BG_PLMN_SEARCH_REQ_ST;

/*******************************************************************************
 �ṹ��    : RRMM_BG_PLMN_SEARCH_CNF_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_BG_PLMN_SEARCH_CNF�Ľṹ
             ����Ϣ����֪ͨNAS BG�������
*******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_BG_PLMN_SEARCH_RLT_ENUM_UINT8   enSearchRlt;        /* ������� */
    VOS_UINT8                           aucReserve[2];      /* ����   */
    VOS_UINT8                           ucPlmnNum ;
    RRMM_PLMN_WITH_RAT_STRU             astPlmnId[NAS_RRC_MAX_BG_SRCH_PLMN_NUM];           /* PlMN��ʶ */
}RRMM_BG_PLMN_SEARCH_CNF_ST;

/*******************************************************************************
 �ṹ��    : RRMM_BG_PLMN_STOP_REQ_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_BG_PLMN_STOP_REQ�Ľṹ
             ����Ϣ����֪ͨNAS BG�������
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ����   */
}RRMM_BG_PLMN_STOP_REQ_ST;

/*******************************************************************************
 �ṹ��    : RRMM_BG_PLMN_STOP_CNF_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRMM_BG_PLMN_STOP_CNF�Ľṹ
             ����Ϣ����֪ͨNAS BG�������
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* ����   */
}RRMM_BG_PLMN_STOP_CNF_ST;

/*****************************************************************************
 ö����    : RRC_FASTDORM_START_TYPE_ENUM_UINT32
 �ṹ˵��  : FASTDORM������������?
*****************************************************************************/
enum RRC_FASTDORM_START_TYPE_ENUM
{
    RRC_FASTDORM_START_TYPE_FD                 = 0,        /* ������FD */
    RRC_FASTDORM_START_TYPE_ASCR               = 1,        /* ������ASCR��Ԥ�� */
    RRC_FASTDORM_START_TYPE_FD_ASCR            = 2,        /* ����FD��ASCR */
    RRC_FASTDORM_START_TYPE_BUTT
};
typedef VOS_UINT32 RRC_FASTDORM_START_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : RRRABM_FASTDORM_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����AS����FASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    RRC_FASTDORM_START_TYPE_ENUM_UINT32   enStartType;    /* FD�������� */
}RRRABM_FASTDORM_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRRABM_FASTDORM_START_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AS�յ�����FASTDORM����Ļظ�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* ���� */
}RRRABM_FASTDORM_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRRABM_FASTDORM_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����ASֹͣFASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* ���� */
}RRRABM_FASTDORM_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_TRANSACTION_INFO_ENQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��NAS��ѯ��ǰҵ����Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
}RRMM_TRANSACTION_INFO_ENQ_STRU;

/*****************************************************************************
 �ṹ��    : RRRABM_FASTDORM_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AS�յ�ֹͣFASTDORM����Ļظ�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* ���� */
}RRRABM_FASTDORM_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NAS_CS_TRANSACTION_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSҵ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8     enCsTransactionType;
    /* Added by n00355355 for �����ؽ�, 2015-9-17, begin */
    VOS_UINT8                             ucIsCallActive;
    /* Added by n00355355 for �����ؽ�, 2015-9-17, end */
    VOS_UINT8                             aucReserve1[2]; /* ���� */
}RRC_NAS_CS_TRANSACTION_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NAS_PS_TRANSACTION_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PSҵ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             aucReserve1[4]; /* ���� */
}RRC_NAS_PS_TRANSACTION_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_TRANSACTION_INFO_ANS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ѯ��ǰҵ����Ϣ�Ļظ�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;        /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    RRC_NAS_CS_TRANSACTION_INFO_STRU      stCsTransactInfo; /* CSҵ����Ϣ */
    RRC_NAS_PS_TRANSACTION_INFO_STRU      stPsTransactInfo; /* PSҵ����Ϣ */
}RRMM_TRANSACTION_INFO_ANS_STRU;
/*****************************************************************************
 ö����    : RRRABM_FASTDORM_INFO_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : FASTDORM�������
*****************************************************************************/
enum RRRABM_FASTDORM_INFO_ENUM
{
    RRRABM_FASTDORM_INFO_NEED_RETRY       = 0,      /* AS��ҪNAS����FD */
    RRRABM_FASTDORM_INFO_EXEC_SUCC        = 1,      /* ASִ������FD����ɹ� */
    RRRABM_FASTDORM_INFO_EXEC_FAIL        = 2,      /* �����쳣������ʧ�ܡ����֧�ֵ� */
    RRRABM_FASTDORM_INFO_RRC_IDLE         = 3,      /* ��ǰ����Э��Idle״̬ */
    RRRABM_FASTDORM_INFO_PCH_MAX          = 4,      /* ��P���ѳ�������ʹ��� */
    RRRABM_FASTDORM_INFO_BUTT
};
typedef VOS_UINT32  RRRABM_FASTDORM_INFO_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : RRRABM_FASTDORM_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :AS�����ϱ�NAS��������ֹFASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    RRRABM_FASTDORM_INFO_ENUM_UINT32     enInfoType;     /* �����ϱ�����Ϣ���� */
}RRRABM_FASTDORM_INFO_IND_STRU;

/*****************************************************************************
 ö����    : RRC_NAS_CIPHER_ALGOR_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ǰW�¼����㷨ö��
*****************************************************************************/
enum RRC_NAS_CIPHER_ALGOR_ENUM
{
    RRC_NAS_CIPHER_ALGOR_UEA0                 = 0,                /* ����δ�� */
    RRC_NAS_CIPHER_ALGOR_UEA1                 = 1,
    RRC_NAS_CIPHER_ALGOR_UEA2                 = 2,
    RRC_NAS_CIPHER_ALGOR_BUTT
};
typedef VOS_UINT8  RRC_NAS_CIPHER_ALGOR_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RRMM_CIPHER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AS�����ϱ�NAS�������㷨����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    RRC_NAS_CIPHER_ALGOR_ENUM_UINT8      enCipherAlgorForCSDomain;  /* CS������㷨  0:uea0; 1:uea1; 2:uea2 */
    RRC_NAS_CIPHER_ALGOR_ENUM_UINT8      enCipherAlgorForPSDomain;  /* PS������㷨  0:uea0; 1:uea1; 2:uea2 */
    VOS_UINT8                            aucReserved[2];            /* Ԥ��λ */
}RRMM_CIPHER_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS֪ͨAS��ǰ�Ѿ���������������̡�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ         */ /*_H2ASN_Skip*/
} RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ            */ /*_H2ASN_Skip*/
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enUtranMode;        /* UTRAN�Ĺ���ģʽ*/
    VOS_UINT8                           aucReserved[3];     /* Ԥ��λ */
}RRMM_UTRAN_MODE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;        /* ��Ϣͷ          */ /*_H2ASN_Skip*/
}RRMM_UTRAN_MODE_CNF_STRU;
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usC1;
    VOS_UINT16                          usC2;
    VOS_UINT16                          usLac;
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usBsic;
    VOS_INT16                           sRxlev;             /* TD-SCDMA:��дrscp, ��ֵ */
    VOS_INT16                           sRssi;              /* TD-SCDMA:������д�������GSM����д */
    VOS_UINT16                          usPSC;              /* WCDMA:��ֵ��������; TD-SCDMA:��ֵ��4 * syncId(���е�Ƶ��) + basicMidamble��
                                                               ��ΪTD-SCDMA�н����ʹ�ø�ֵ + Ƶ������һ��С�� */
    VOS_UINT32                          ulCellId;
    VOS_UINT32                          ulPhyId;            /* L��Ҫʹ��physical cell id��Ƶ����ȷ��һ��С����NetScan����Ƶ/��С������ʹ�ã�TDS����Ϊȫ1 */
    VOS_UINT32                          aulBand[2];         /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β��� */
}RRMM_NET_SCAN_INFO_STRU;



enum RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM
{
    RRC_NAS_NETSCAN_TDD_SEARCH_NONE     = 0,                /* TDSCDMA����NETSCAN���̺󣬲������������� */
    RRC_NAS_NETSCAN_TDD_SEARCH_REQ,                         /* TDSCDMA����NETSCAN���̺󣬽����������� */
    RRC_NAS_NETSCAN_TDD_SEARCH_BUTT
};
typedef VOS_UINT8 RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RRMM_NET_SCAN_REQ_STRU
 �ṹ˵��  : MMC���������������ɨ����Ϣ�ṹ��
 1.��    ��   : 2013��8��24��
   ��    ��   : sunxibo
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;    /* ��Ϣͷ    */         /*_H2ASN_Skip*/
    RRC_NAS_RAT_TYPE_ENUM_UINT32        enRat;
    VOS_UINT16                          usFreqNum;
    VOS_INT16                           sPower;
    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;        /* ����enRatȡֵȷ�������ĸ����뼼���µ�Ƶ�Σ�����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β��� */
    RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM_UINT8 usSearchReq;
    VOS_UINT8                           aucReserve[3];
}RRMM_NET_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_NET_SCAN_CNF_STRU
 �ṹ˵��  : �����ɨ�����ظ���Ϣ�ṹ��
 1.��    ��   : 2013��8��24��
   ��    ��   : sunxibo
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    RRC_NAS_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    RRC_NAS_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[1];
    RRMM_NET_SCAN_INFO_STRU             astNetScanInfo[RRC_NAS_NET_SCAN_MAX_FREQ_NUM];
}RRMM_NET_SCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_NET_SCAN_STOP_REQ_STRU
 �ṹ˵��  : MMC��������ֹͣ��������ɨ����Ϣ�ṹ��
 1.��    ��   : 2013��8��24��
   ��    ��   : sunxibo
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_NET_SCAN_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_NET_SCAN_STOP_CNF_STRU
 �ṹ˵��  : �����ֹͣɨ�����ظ���Ϣ�ṹ��
 1.��    ��   : 2013��8��24��
   ��    ��   : sunxibo
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[3];
    RRMM_NET_SCAN_INFO_STRU             astNetScanInfo[RRC_NAS_NET_SCAN_MAX_FREQ_NUM];
}RRMM_NET_SCAN_STOP_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    RRC_NAS_NCELL_STATE_ENUM_UINT8      enNcellState;
    VOS_UINT8                           aucReserved[3];
} RRC_NAS_NCELL_MONITOR_IND_STRU;

typedef struct
{
    RRC_PLMN_ID_STRU                stPlmnId;
    RRC_NAS_RAT_TYPE_ENUM_UINT32    ulRat;    /* ֧�ֵĽ��뼼�� */
    VOS_UINT16                      usLac;    /* λ������Ϣ,���û��λ����Ϣ����0xffff*/
    VOS_UINT16                      usReserved;
}RRMM_PLMN_RAT_WITH_LAC_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT32                          ulAvailPlmnNum;       /* �ϱ�PLMN���� */

    /* �ϱ�plmn ���뼼����λ������Ϣ */
    RRMM_PLMN_RAT_WITH_LAC_STRU         astPlmnWithLacList[NAS_RRC_MAX_AVAILPLMN_NUM];
}RRMM_SEARCHED_PLMN_INFO_IND_STRU;



/*****************************************************************************
 �ṹ��    : RRRABM_VOICEPREFER_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :ָʾVOICEPREFER����
*****************************************************************************/


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4]; /* ���� */
}RRRABM_VOICEPREFER_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRRABM_VOICEPREFER_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :ָʾVOICEPREFERȥ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;      /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4]; /* ���� */
}RRRABM_VOICEPREFER_STOP_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ  */    /*_H2ASN_Skip*/
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransActionStatus;
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}RRMM_TRANSACTION_STATUS_NOTIFY_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/* 9.2 AS ��ȡ MM/GMM ��ȫ��Ϣ�ӿ� �������ӿڣ� */
/*****************************************************************************
 Prototype      : MM_GetSecurityInfo
 Description    : AS ͨ���˽ӿں�����ȡ CS ��ȫ��Ϣ�� IMSI

 Input          : pCsInfo AS ���ṩ����Ϣ�ṹָ��
 Output         : pCsInfo MM ���ṹ�и���Ա,������ȫ��Ϣ�� IMSI
 Return Value   : ---
 Calls          : ---
 Called By      : WAS/GAS

 History        : ---
  1.Date        : 2005-09-09
    Author      : sxbo
    Modification: Creation
*****************************************************************************/
extern VOS_VOID MM_GetSecurityInfo(MM_CSPS_INFO_ST *pCsInfo);

/*****************************************************************************
 Prototype      :  GMM_GetSecurityInfo
 Description    :  ��ѯGMM�İ�ȫ��������Ϣ����
 Input          :
 Output         : ---
 Return Value   : 1     ���سɹ�
                  0     ����ʧ��
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---
*****************************************************************************/
extern VOS_VOID GMM_GetSecurityInfo(MM_CSPS_INFO_ST *pPsInfo);

/*****************************************************************************
 Prototype      :  GMM_GetTlliInfo
 Description    :  ��ȡ��ǰ��TLLI
 Input          :
 Output         : ---
 Return Value   : void
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---
*****************************************************************************/
extern VOS_VOID GMM_GetTlliInfo(VOS_UINT32 *pulNewTlli, VOS_UINT32 *pulOldTlli);

/* 9.3 NAS ��ȡ BAND ��Ϣ�ӿ� �������ӿڣ� */
/*****************************************************************************
 Prototype      : GAS_SCELL_BAND_INFO
 Description    : NAS ͨ���˽ӿں�����ȡ GAS BAND ��Ϣ

 Input          : pstBandInfo NAS ���ṩ�� BAND ��Ϣ�ṹָ��
 Output         : pstBandInfo AS ���ṹ�ж�Ӧ��Ա
 Return Value   : ---
 Calls          : ---
 Called By      : NAS

 History        : ---
  1.Date        :  GAS_GetSCellBandInfo
    Author      :
    Modification: Creation
*****************************************************************************/
extern VOS_VOID GAS_SCELL_BAND_INFO( AS_NAS_SCELL_BAND_INFO_ST *pstBandInfo );
extern VOS_VOID GAS_GetSCellBandInfo( AS_NAS_SCELL_BAND_INFO_ST *pstBandInfo );

extern VOS_UINT32 MMC_ComJudgeLai(RRC_PLMN_ID_STRU stPlmn,
                                    VOS_UINT16 usLac,PS_BOOL_ENUM_UINT8 *penLaiValidFlg);


/* 9.4 AS ��ȡ ͨ�����ô˽ӿ�����ȡNAS�������Ϣ������˵PLMN����Ϣ�ȡ��������ӿڣ� */
/*****************************************************************************
 Prototype      : MM_GetSecurityInfo
 Description    : AS ��ȡ ͨ�����ô˽ӿ�����ȡNAS�������Ϣ������˵PLMN����Ϣ�ȡ�
                  pMmInfo AS ���ṩ����Ϣ�ṹָ��, ����ucType�Ĳ�ͬ����ȡ��ͬ��
                  ���ݽṹ��
 Input          : ucType -- 0��    ��ʾ��ȡPLMN��Ϣ�뿨״̬��Ϣ��
 Output         : pMmInfo -- MM�����ṹ�и���Ա,����PLMN����Ϣ
 Return Value   : ---
 Calls          : ---
 Called By      : WAS/GAS

 History        : ---
  1.Date        : 2005-09-09
    Author      : sxbo
    Modification: Creation
*****************************************************************************/
extern VOS_VOID MM_GetNasInfo(MM_INFO_ST *pstMmInfo);


extern VOS_UINT32 NAS_MMC_GetEHPlmn(RRC_PLMN_ID_STRU *pstEHPlmn, VOS_UINT8 *pucEHPlmnNum);


extern VOS_UINT32 NAS_GetTransactionInfo(RRC_NAS_CS_TRANSACTION_INFO_STRU *pstCsTransactInfo,
                                         RRC_NAS_PS_TRANSACTION_INFO_STRU *pstPsTransactInfo);

enum CSPS_REG_STATE_ENUM
{
    NAS_RRC_CSPS_ATTACH,
    NAS_RRC_CS_DETACH,
    NAS_RRC_PS_DETACH,
    NAS_RRC_CSPS_DETACH
};
typedef VOS_UINT32 CSPS_REG_STATE_ENUM_UINT32;
/*****************************************************************************
 AS��ѯCS,PS��ע��״̬API�ӿ�
*****************************************************************************/
extern VOS_VOID NVIM_Read_DrxFlag (VOS_VOID);



enum PPP_DIAL_RATE_DISPLAY_ENUM
{
    PPP_DIAL_RATE_DISPLAY_GSM = 0,
    PPP_DIAL_RATE_DISPLAY_GPRS,
    PPP_DIAL_RATE_DISPLAY_EDGE,

    PPP_DIAL_RATE_DISPLAY_R99,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_6,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_8,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_9,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_10,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_12,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_14,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_18,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_24,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_26,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_28,

    PPP_DIAL_RATE_DISPLAY_BUTT
};

typedef VOS_UINT32 PPP_DIAL_RATE_DISPLAY_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    NAS_MSG_STRU                        stNackMsg;
}RRMM_NACK_DATA_IND_STRU;


enum RRC_NAS_SESSION_TYPE_ENUM
{
    RRC_NAS_SESSION_TYPE_NONE                           = 0,

    RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL,
    RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    RRC_NAS_SESSION_TYPE_CS_MO_SS,
    RRC_NAS_SESSION_TYPE_CS_MO_SMS,
    RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL,
    RRC_NAS_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK,      /* ������eCall�Ļغ����� */
    RRC_NAS_SESSION_TYPE_CS_MT_SS,
    RRC_NAS_SESSION_TYPE_CS_MT_SMS,
    RRC_NAS_SESSION_TYPE_CS_LAU,
    RRC_NAS_SESSION_TYPE_CS_DETACH,
    RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB,
    RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB,
    RRC_NAS_SESSION_TYPE_CS_MT_CSFB,
    RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL,
    RRC_NAS_SESSION_TYPE_PS_STREAM_CALL,
    RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL,
    RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL,
    RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    RRC_NAS_SESSION_TYPE_PS_MO_SMS,
    RRC_NAS_SESSION_TYPE_PS_MT_SMS,
    RRC_NAS_SESSION_TYPE_PS_ATTACH,
    RRC_NAS_SESSION_TYPE_PS_RAU,
    RRC_NAS_SESSION_TYPE_PS_DETACH,

    RRC_NAS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 RRC_NAS_SESSION_TYPE_ENUM_UINT8;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}RRMM_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enCsRelAll;
    PS_BOOL_ENUM_UINT8                  enPsRelAll;
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulDelayTime;
}RRMM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
 ö����     :RRC_NAS_SIGNAL_INFO_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ��ϵͳ������ʱЯ������������
*****************************************************************************/
typedef enum
{
    RRC_NAS_NO_SIG_INF0                              = 0,                            /* ���������� */
    RRC_NAS_SIG_CS,                                                                  /* ֻ����CS���� */
    RRC_NAS_SIG_PS,                                                                  /* ֻ����PS���� */
    RRC_NAS_SIG_CSANDPS,                                                             /* ͬʱ����CS��PS���� */
    RRC_NAS_SIG_BUTT
}RRC_NAS_SIGNAL_INFO_ENUM;
typedef VOS_UINT8  RRC_NAS_SIGNAL_INFO_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RRMM_HANDOVER_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AS֪ͨNAS��MMCģ�鵱ǰ�л���Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ         */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSrvccFlag;                            /* ��ǰ�Ƿ�ΪSRVCC���� */
    RRC_NAS_SIGNAL_INFO_ENUM_UINT8      enSignalInfo;                           /* �������ӵ����� */
    VOS_UINT8                           aucRsv[2];
} RRMM_HANDOVER_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRMM_CLASSMARK_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GAS�ϱ�CLASSMARK����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 ���ȣ��ó���Ϊ0����CLASSMARK2��Ч */
    VOS_UINT8                           aucClassmark2[MS_CLASSMARK2_MAX_LEN];   /* Classmark2 ���� */

    VOS_UINT8                           ucClassmark3FddLen;                     /* Fdd Classmark3 ���ȣ��ó���Ϊ0����Fdd CLASSMARK3��Ч */
    VOS_UINT8                           aucClassmark3Fdd[MS_CLASSMARK3_MAX_LEN];/* Fdd Classmark3 ���� */

    VOS_UINT8                           ucClassmark3TddLen;                     /* Tdd Classmark3 ���ȣ��ó���Ϊ0����Tdd CLASSMARK3��Ч */
    VOS_UINT8                           aucClassmark3Tdd[MS_CLASSMARK3_MAX_LEN];/* Tdd Classmark3 ���� */

    VOS_UINT8                           aucReserved[1];                         /* 4�ֽڶ��룬���� */
} RRMM_CLASSMARK_CHANGE_IND_STRU;


typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                              /* TDSƵ�������0��ʾTDSƵ�㲻���� */
    VOS_UINT8                           aucRsv[1];                                  /* ����λ*/
    VOS_UINT16                          ausTdsArfcnList[RRMM_TDS_ARFCN_MAX_NUM]; /* Ƶ���б� */
}RRMM_TDS_NCELL_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                              /* LTEƵ�������0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucRsv[3];                                  /* ����λ*/
    VOS_UINT32                          aulLteArfcnList[RRMM_LTE_ARFCN_MAX_NUM]; /* Ƶ���б� */
}RRMM_LTE_NCELL_INFO_STRU;

/*****************************************************************************
 ö����     :RRMM_GSM_BANDINDICATOR_ENUM
 Э����   :
 ASN.1����  :
 ö��˵��   :2GС��Ƶ��ָʾ
*****************************************************************************/
enum RRMM_GSM_BANDINDICATOR_ENUM
{
    RRMM_GSM_BANDINDICATOR_DCS1800                          = 0,
    RRMM_GSM_BANDINDICATOR_PCS1900                             ,

    RRMM_GSM_BANDINDICATOR_BUTT
};
typedef VOS_UINT16  RRMM_GSM_BANDINDICATOR_ENUM_UINT16;


typedef struct
{
    VOS_UINT16                          usGsmArfcn;     /* ����Ƶ��� */
    RRMM_GSM_BANDINDICATOR_ENUM_UINT16  enBandInd;      /* Bandָʾ, ָʾ��ǰƵ���� 1800 ϵͳ �� 1900 ϵͳ */
}RRMM_GSM_FREQ_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucGsmArfcnNum;                                      /* GSMƵ�������0��ʾGSMƵ�㲻���� */
    VOS_UINT8                           ucGsmMaArfcnNum;                                    /* ҵ��Ƶ�����, �統ǰ����G��ģ,��Ϊ0 */
    VOS_UINT8                           aucRsv[2];
    RRMM_GSM_FREQ_INFO_STRU             astGsmArfcnList[RRMM_GSM_MAX_USING_ARFCN_NUM];   /* ����С��������Ƶ���б�, ����С��Ƶ���ڵ�һλ */
    RRMM_GSM_FREQ_INFO_STRU             astGsmMaArfcnList[RRMM_GSM_MA_ARFCN_MAX_NUM];    /* ҵ��Ƶ����Ϣ������Ϣֻ��G��ģ����Ч */
}RRMM_GSM_FREQ_INFO_LIST_STRU;


typedef struct
{
    VOS_UINT8                           ucWcdmaArfcnNum;                                        /* WƵ�������0��ʾWCDMAƵ�㲻���� */
    VOS_UINT8                           aucRsv[3];                                              /* ����λ*/
    VOS_UINT16                          ausWcdmaArfcnList[RRMM_WCDMA_MAX_USING_ARFCN_NUM];   /* Ƶ���б� */
}RRMM_WCDMA_FREQ_INFO_LIST_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                       /*_H2ASN_Skip*/

    RRMM_GSM_FREQ_INFO_LIST_STRU        stGsmFreqInfo;                     /* GSMƵ���б���Ϣ */

    RRMM_WCDMA_FREQ_INFO_LIST_STRU      stWcdmaFreqInfo;                   /* WCDMAƵ���б���Ϣ */

    RRMM_TDS_NCELL_INFO_STRU            stTdsFreqInfo;                     /* TDSƵ���б���Ϣ */

    RRMM_LTE_NCELL_INFO_STRU            stLteFreqInfo;                     /* LTEƵ���б���Ϣ */

    PS_BOOL_ENUM_UINT8                  enCsExistFlag;                     /* PS_FALSE ��ʾ������CS���� */
    PS_BOOL_ENUM_UINT8                  enPsExistFlag;                     /* PS_FALSE ��ʾ������PS���� */
    VOS_UINT8                           aucRsv[2];
}RRMM_USING_FREQ_IND_STRU;

/* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, begin */
/*****************************************************************************
 �ṹ��    : RRMM_CONNECTED_LOCATION_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��NAS�ϱ�λ����Ϣ�ṹԭ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU                    PlmnId;             /* ��С��PLMN ID  */
    VOS_UINT32                          ulCellId;           /* ��ǰפ��С��ID */
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserve1;     /* ���� */
}RRMM_CONNECTED_LOCATION_INFO_IND_STRU;
/* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, end */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    NAS_RRC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_RRC_MSG_TYPE_ENUM_UINT32*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��NAS_RRC_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_RRC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_RRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_RRC_MSG_DATA                    stMsgData;
}NasRrcInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*
extern VOS_BOOL  RRC_GET_DrxFlag (VOS_VOID);
*/

extern VOS_UINT32 GASGCOM_GetDisplayRate(PPP_DIAL_RATE_DISPLAY_ENUM_UINT32 *penRateDisplay);

extern VOS_VOID GASGCOM_UpdateCustomizeNv(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
/* APIԼ��1: ��ֹLTE FDD NV������Ǵ򿪵ģ�
   APIԼ��2: �����Gģ��������
   APIԼ��3: Gģ�Ǵ�ģ
   ���������е��κ�һ����������������Ч����
*/
extern VOS_UINT32 GASGCOM_GetMsCapability(RRC_PLMN_ID_STRU *pstPlmn,
                                               NAS_GAS_MS_CAP_TYPE_ENUM_UINT8 enCapType,
                                               VOS_UINT16 usSize,
                                               VOS_UINT8 *pucData);
#endif

extern VOS_UINT32  TAF_IsNormalSrvStatus(VOS_VOID);


extern VOS_UINT32 NAS_MM_GetLauRequestInfo(
    NAS_MSG_STRU                           *pstLauReqMsg,
    NAS_LAU_TYPE_ENUM_UINT8                *penLauType,
    VOS_UINT8                              *pucFollowOnFlg,
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8    *penAdditionUpdatePara
);

/* Added by h00313353 for SMS Filter Prj, 2015-9-17, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_GetL3ReqMsgPd
 ��������  : �ṩ��������ȡReq��Ϣ�е�PD��Ϣ
 �������  : pstSendMsg: Data Req��Ϣ���� RRMM_DATA_REQ_STRU�ṹ
 �������  : ucPd:VOS_UINT8����

 �� �� ֵ  : VOS_OK:��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetL3ReqMsgPd(
    RRMM_DATA_REQ_STRU                     *pstSendMsg,
    VOS_UINT8                              *pucPd
);

/*****************************************************************************
 �� �� ��  : NAS_MM_GetL3RcvMsgPd
 ��������  : �ṩ��������ȡInd��Ϣ�е�PD��Ϣ
 �������  : pstSendMsg: Data Ind��Ϣ���� RRMM_DATA_IND_STRU�ṹ
 �������  : ucPd:VOS_UINT8����

 �� �� ֵ  : VOS_OK:��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetL3RcvMsgPd(
    RRMM_DATA_IND_STRU                     *pstRcvMsg,
    VOS_UINT8                              *pucPd
);

/*****************************************************************************
 �� �� ��  : NAS_MM_GetSmsFilterFlg
 ��������  : �ṩ��������ȡ���˹����Ƿ�򿪵�Nv
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ���й���
             VOS_FALSE:����Ҫ���й���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetSmsFilterFlg( VOS_VOID );
/* Added by h00313353 for SMS Filter Prj, 2015-9-17, end */
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

#endif /* end of NasRrcInterface.h */
