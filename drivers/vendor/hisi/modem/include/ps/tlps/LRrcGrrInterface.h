

#ifndef __LRRC_GRRINTERFACE_H__
#define __LRRC_GRRINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPSCommon.h"
#include  "LRrcGuRrcCommInterface.h"
#include  "PsTypeDef.h"


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define LRRC_GRR_MSG_HDR                (PS_MSG_ID_LRRC_TO_GRR_BASE)
#define GRR_LRRC_MSG_HDR                (PS_MSG_ID_GRR_TO_LRRC_BASE)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    :
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LRRC_GRR_MSG_TYPE_ENUM
{
    /* G -> L Cell Resel */
    ID_GRR_LRRC_CELL_RESEL_REQ                 = (GRR_LRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_RESEL_REQ_STRU */
    ID_LRRC_GRR_CELL_RESEL_CNF                 = (LRRC_GRR_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_RESEL_CNF_STRU */
    ID_GRR_LRRC_CELL_RESEL_STOP_REQ            = (GRR_LRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_RESEL_STOP_REQ_STRU */
    ID_LRRC_GRR_CELL_RESEL_STOP_CNF            = (LRRC_GRR_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_RESEL_STOP_CNF_STRU */

    /* G -> L Redirect */
    ID_GRR_LRRC_REDIRECTED_REQ                 = (GRR_LRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice GRR_LRRC_REDIRECTED_REQ_STRU */
    ID_LRRC_GRR_REDIRECTED_CNF                 = (LRRC_GRR_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice LRRC_GRR_REDIRECTED_CNF_STRU */
    ID_GRR_LRRC_REDIRECTED_STOP_REQ            = (GRR_LRRC_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice GRR_LRRC_REDIRECTED_STOP_REQ_STRU */
    ID_LRRC_GRR_REDIRECTED_STOP_CNF            = (LRRC_GRR_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice LRRC_GRR_REDIRECTED_STOP_CNF_STRU */

    /* G -> L CCO */
    ID_GRR_LRRC_CELL_CHANGE_ORDER_REQ          = (GRR_LRRC_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_CHANGE_ORDER_REQ_STRU */
    ID_LRRC_GRR_CELL_CHANGE_ORDER_CNF          = (LRRC_GRR_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU */
    ID_GRR_LRRC_CELL_CHANGE_ORDER_STOP_REQ     = (GRR_LRRC_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_LRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF     = (LRRC_GRR_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* G-> L HO */
    ID_GRR_LRRC_HANDOVER_REQ                   = (GRR_LRRC_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice GRR_LRRC_HANDOVER_REQ_STRU */
    ID_LRRC_GRR_HANDOVER_CNF                   = (LRRC_GRR_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice LRRC_GRR_HANDOVER_CNF_STRU */
    ID_GRR_LRRC_HANDOVER_STOP_REQ              = (GRR_LRRC_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice GRR_LRRC_HANDOVER_STOP_REQ_STRU */
    ID_LRRC_GRR_HANDOVER_STOP_CNF              = (LRRC_GRR_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice LRRC_GRR_HANDOVER_STOP_CNF_STRU */

    /* G-> L �͹��� */
    ID_GRR_LRRC_SET_DSP_POWER_REQ              = (GRR_LRRC_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice GRR_LRRC_SET_DSP_POWER_REQ_STRU */
    ID_LRRC_GRR_SET_DSP_POWER_CNF              = (LRRC_GRR_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice LRRC_GRR_SET_DSP_POWER_CNF_STRU */

    /* G-> L Idle Meas */
    ID_GRR_LRRC_IDLE_MEASURE_REQ               = (GRR_LRRC_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice GRR_LRRC_IDLE_MEASURE_REQ_STRU */
    ID_LRRC_GRR_IDLE_MEASURE_CNF               = (LRRC_GRR_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice LRRC_GRR_IDLE_MEASURE_CNF_STRU */
    ID_LRRC_GRR_IDLE_MEASURE_IND               = (LRRC_GRR_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice LRRC_GRR_IDLE_MEASURE_IND_STRU */

    /* G-> L conn Meas */
    ID_GRR_LRRC_CONNECTED_MEASURE_REQ          = (GRR_LRRC_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice GRR_LRRC_CONNECTED_MEASURE_REQ_STRU */
    ID_LRRC_GRR_CONNECTED_MEASURE_CNF          = (LRRC_GRR_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice LRRC_GRR_CONNECTED_MEASURE_CNF_STRU */
    ID_LRRC_GRR_CONNECTED_MEASURE_IND          = (LRRC_GRR_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice LRRC_GRR_CONNECTED_MEASURE_IND_STRU */

    /* L -> G Cell Resel*/
    ID_LRRC_GRR_CELL_RESEL_REQ                 = (LRRC_GRR_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_RESEL_REQ_STRU */
    ID_GRR_LRRC_CELL_RESEL_CNF                 = (GRR_LRRC_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_RESEL_CNF_STRU */
    ID_LRRC_GRR_CELL_RESEL_STOP_REQ            = (LRRC_GRR_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_RESEL_STOP_REQ_STRU */
    ID_GRR_LRRC_CELL_RESEL_STOP_CNF            = (GRR_LRRC_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_RESEL_STOP_CNF_STRU */

    /* L-> G Redirect */
    ID_LRRC_GRR_REDIRECTED_REQ                 = (LRRC_GRR_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice LRRC_GRR_REDIRECTED_REQ_STRU */
    ID_GRR_LRRC_REDIRECTED_CNF                 = (GRR_LRRC_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice GRR_LRRC_REDIRECTED_CNF_STRU */
    ID_LRRC_GRR_REDIRECTED_STOP_REQ            = (LRRC_GRR_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice LRRC_GRR_REDIRECTED_STOP_REQ_STRU */
    ID_GRR_LRRC_REDIRECTED_STOP_CNF            = (GRR_LRRC_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice GRR_LRRC_REDIRECTED_STOP_CNF_STRU */

    /* L-> G CCO */
    ID_LRRC_GRR_CELL_CHANGE_ORDER_REQ          = (LRRC_GRR_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU */
    ID_GRR_LRRC_CELL_CHANGE_ORDER_CNF          = (GRR_LRRC_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_CHANGE_ORDER_CNF_STRU */
    ID_LRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ     = (LRRC_GRR_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice LRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_GRR_LRRC_CELL_CHANGE_ORDER_STOP_CNF     = (GRR_LRRC_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice GRR_LRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* L-> G HO */
    ID_LRRC_GRR_HANDOVER_REQ                   = (LRRC_GRR_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice LRRC_GRR_HANDOVER_REQ_STRU */
    ID_GRR_LRRC_HANDOVER_CNF                   = (GRR_LRRC_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice GRR_LRRC_HANDOVER_CNF_STRU */
    ID_LRRC_GRR_HANDOVER_STOP_REQ              = (LRRC_GRR_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice LRRC_GRR_HANDOVER_STOP_REQ_STRU */
    ID_GRR_LRRC_HANDOVER_STOP_CNF              = (GRR_LRRC_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice GRR_LRRC_HANDOVER_STOP_CNF_STRU */

    /* G-> L �͹��� */
    ID_LRRC_GRR_SET_DSP_POWER_REQ              = (LRRC_GRR_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice LRRC_GRR_SET_DSP_POWER_REQ_STRU */
    ID_GRR_LRRC_SET_DSP_POWER_CNF              = (GRR_LRRC_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice GRR_LRRC_SET_DSP_POWER_CNF_STRU */

    /* L-> G Get Ue Capability Info */
    ID_LRRC_GRR_GETUECAPINFO_REQ               = (LRRC_GRR_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice LRRC_GRR_GETUECAPINFO_REQ_STRU */
    ID_GRR_LRRC_GETUECAPINFO_CNF               = (GRR_LRRC_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice GRR_LRRC_GETUECAPINFO_CNF_STRU */

    /* L -> G Idle Meas */
    ID_LRRC_GRR_IDLE_MEASURE_REQ               = (LRRC_GRR_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice LRRC_GRR_IDLE_MEASURE_REQ_STRU */
    ID_GRR_LRRC_IDLE_MEASURE_CNF               = (GRR_LRRC_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice GRR_LRRC_IDLE_MEASURE_CNF_STRU */
    ID_GRR_LRRC_IDLE_MEASURE_IND               = (GRR_LRRC_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice GRR_LRRC_IDLE_MEASURE_IND_STRU */

    /* L -> G Conn Meas */
    ID_LRRC_GRR_CONNECTED_MEASURE_REQ          = (LRRC_GRR_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice LRRC_GRR_CONNECTED_MEASURE_REQ_STRU */
    ID_GRR_LRRC_CONNECTED_MEASURE_CNF          = (GRR_LRRC_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice GRR_LRRC_CONNECTED_MEASURE_CNF_STRU */
    ID_GRR_LRRC_CONNECTED_MEASURE_IND          = (GRR_LRRC_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice GRR_LRRC_CONNECTED_MEASURE_IND_STRU */

    /* L -> GU  Gsm Cell Bsic Verify  */
    ID_LRRC_GRR_BSIC_VERIFIED_REQ              = (LRRC_GRR_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice LRRC_GRR_BSIC_VERIFIED_REQ_STRU */
    ID_GRR_LRRC_BSIC_VERIFIED_CNF              = (GRR_LRRC_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice GRR_LRRC_BSIC_VERIFIED_CNF_STRU */
    ID_GRR_LRRC_BSIC_VERIFIED_IND              = (GRR_LRRC_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice GRR_LRRC_BSIC_VERIFIED_IND_STRU */

    /* L -> G RelAll */
    ID_LRRC_GRR_RELALL_REQ                     = (LRRC_GRR_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice LRRC_GRR_RELALL_REQ_STRU */
    ID_GRR_LRRC_RELALL_CNF                     = (GRR_LRRC_MSG_HDR + 0x1b),     /* _H2ASN_MsgChoice GRR_LRRC_RELALL_CNF_STRU */

    /* L -> G cell srch. L�ؽ�ʱ����GС�� */
    ID_LRRC_GRR_CELL_SRCH_REQ                  = (LRRC_GRR_MSG_HDR + 0x1c),       /* _H2ASN_MsgChoice LRRC_GRR_CELL_SRCH_REQ_STRU */
    ID_GRR_LRRC_CELL_SRCH_CNF                  = (GRR_LRRC_MSG_HDR + 0x1d),       /* _H2ASN_MsgChoice GRR_LRRC_CELL_SRCH_CNF_STRU */
    ID_LRRC_GRR_CELL_SRCH_STOP_REQ             = (LRRC_GRR_MSG_HDR + 0x1d),       /* _H2ASN_MsgChoice LRRC_GRR_CELL_SRCH_STOP_REQ_STRU */
    ID_GRR_LRRC_CELL_SRCH_STOP_CNF             = (GRR_LRRC_MSG_HDR + 0x1e),       /* _H2ASN_MsgChoice GRR_LRRC_CELL_SRCH_STOP_CNF_STRU */

    /* GTL�汾�У�L->G��ģ������ID�Ѿ�ʹ����
	LRRC_GRR_MSG_HDR + [ 0x17 - 0x1b]�� GRR_LRRC_MSG_HDR + [ 0x15 - 0x1c ]
    �˴�����Щ IDֵ���� */

    /* G-> L BackGroud Search */
    ID_GRR_LRRC_BG_PLMN_SEARCH_REQ         = (GRR_LRRC_MSG_HDR + 0x1f),         /* _H2ASN_MsgChoice GRR_LRRC_BG_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_GRR_BG_PLMN_SEARCH_CNF         = (LRRC_GRR_MSG_HDR + 0x1e),         /* _H2ASN_MsgChoice LRRC_GRR_BG_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_GRR_BG_PLMN_SEARCH_IND         = (LRRC_GRR_MSG_HDR + 0x1f),         /* _H2ASN_MsgChoice LRRC_GRR_BG_PLMN_SEARCH_IND_STRU */
    ID_GRR_LRRC_BG_SEARCH_STOP_REQ         = (GRR_LRRC_MSG_HDR + 0x20),         /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_STOP_REQ_STRU */
    ID_LRRC_GRR_BG_SEARCH_STOP_CNF         = (LRRC_GRR_MSG_HDR + 0x20),         /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_STOP_CNF_STRU */
    ID_GRR_LRRC_BG_SEARCH_SUSPEND_REQ      = (GRR_LRRC_MSG_HDR + 0x21),         /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_LRRC_GRR_BG_SEARCH_SUSPEND_CNF      = (LRRC_GRR_MSG_HDR + 0x21),         /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_LRRC_GRR_BG_SEARCH_RESUME_CNF       = (LRRC_GRR_MSG_HDR + 0x22),         /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_RESUME_CNF_STRU */
    ID_GRR_LRRC_BG_SEARCH_RESUME_REQ       = (GRR_LRRC_MSG_HDR + 0x22),         /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_RESUME_REQ_STRU */
    /* L -> G BackGroud Search */
    ID_LRRC_GRR_BG_PLMN_SEARCH_REQ             = (LRRC_GRR_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice LRRC_GRR_BG_PLMN_SEARCH_REQ_STRU */
    ID_GRR_LRRC_BG_PLMN_SEARCH_CNF             = (GRR_LRRC_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice GRR_LRRC_BG_PLMN_SEARCH_CNF_STRU */
    ID_GRR_LRRC_BG_PLMN_SEARCH_IND             = (GRR_LRRC_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice GRR_LRRC_BG_PLMN_SEARCH_IND_STRU */
    ID_LRRC_GRR_BG_SEARCH_STOP_REQ             = (LRRC_GRR_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_STOP_REQ_STRU */
    ID_GRR_LRRC_BG_SEARCH_STOP_CNF             = (GRR_LRRC_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_STOP_CNF_STRU */
    ID_LRRC_GRR_BG_SEARCH_SUSPEND_REQ          = (LRRC_GRR_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_GRR_LRRC_BG_SEARCH_SUSPEND_CNF          = (GRR_LRRC_MSG_HDR + 0x26),     /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_LRRC_GRR_BG_SEARCH_RESUME_REQ           = (LRRC_GRR_MSG_HDR + 0x26),     /* _H2ASN_MsgChoice LRRC_GRR_BG_SEARCH_RESUME_REQ_STRU */
    ID_GRR_LRRC_BG_SEARCH_RESUME_CNF           = (GRR_LRRC_MSG_HDR + 0x27),     /* _H2ASN_MsgChoice GRR_LRRC_BG_SEARCH_RESUME_CNF_STRU */

    /* L -> G ANR */
    ID_LRRC_GRR_GET_CGI_REQ                    = (LRRC_GRR_MSG_HDR + 0x27),     /* _H2ASN_MsgChoice LRRC_GRR_GET_CGI_REQ_STRU */
    ID_GRR_LRRC_GET_CGI_CNF                    = (GRR_LRRC_MSG_HDR + 0x28),     /* _H2ASN_MsgChoice GRR_LRRC_GET_CGI_CNF_STRU */
    ID_GRR_LRRC_GET_CGI_IND                    = (GRR_LRRC_MSG_HDR + 0x29),     /* _H2ASN_MsgChoice GRR_LRRC_GET_CGI_IND_STRU */
    ID_LRRC_GRR_GET_CGI_STOP_REQ               = (LRRC_GRR_MSG_HDR + 0x28),     /* _H2ASN_MsgChoice LRRC_GRR_GET_CGI_STOP_REQ_STRU */
    ID_GRR_LRRC_GET_CGI_STOP_CNF               = (GRR_LRRC_MSG_HDR + 0x2a),     /* _H2ASN_MsgChoice GRR_LRRC_GET_CGI_STOP_CNF_STRU */

    ID_LRRC_GRR_FR_INFO_CNF                    = (LRRC_GRR_MSG_HDR + 0x29),     /* _H2ASN_MsgChoice LRRC_GRR_FR_INFO_CNF_STRU */
    ID_GRR_LRRC_FR_INFO_REQ                    = (GRR_LRRC_MSG_HDR + 0x2b),     /* _H2ASN_MsgChoice GRR_LRRC_FR_INFO_REQ_STRU */

    ID_LRRC_GRR_MSG_TYPE_BUTT

};
typedef VOS_UINT32  LRRC_GRR_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    /* �տڲ����ڸ�����ʱ����дĬ��ֵ0 */
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;

    /* ��ѡ�ɹ���ͷ���ʱ������usPunishTimerValue��UE���ܴ�L������ѡ��GС����
       ��λ:���룬ĿǰĬ��Ϊ5000���� */
    VOS_UINT16                                              usPunishTimerValue;

    /* Gָʾפ����LTE С�������ͣ����G֧��CS������ֻ����ѡ��SUITABLEС�� */
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stLrrcGurrcDPriInfo;
}GRR_LRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��stPlmnIdInfo ��Ч��
     ������Ϊ��С����PLMN IDs */
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfo;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;

    VOS_INT16                                              sQrxLevMin;          /*RSRP��ͽ������ޣ���λ1/8dB*/
    VOS_INT16                                              sQqualMin;           /*RSRQ��ͽ������ޣ���λ1/8dB*/
    VOS_UINT32                                             ulReserved[4];
}LRRC_GRR_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GRRָʾLRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_REDIRECTED_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSMϵͳ���ض�λ��Ϣ
*****************************************************************************/
typedef struct
{

    VOS_UINT16                                              usArfcn;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT8                                               ucTargetCellPresent;
    VOS_UINT16                                              usCellId;

    /* �տڲ����ڸ�����ʱ����дĬ��ֵ0 */
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;

    /* LTE ϵͳ�еĺ�������Ϣ */
    VOS_UINT16                                              usBlackListCellNum;
    VOS_UINT16                                              ausBlackListCellId[LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM];
}GRR_LRRC_REDIRECTED_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾ�����ض���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              ulRedirInfoNum;
    GRR_LRRC_REDIRECTED_INFO_STRU                           astGrrRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_TYPE_ENUM_UINT8                        enRedirType;
    VOS_UINT8                                               aucReserved[3];
    /* CMCC-END */

    /* ��REDIR INFO ָʾ������ʱ�� ��λ:����,Ŀǰ�̶�10000ms��
    �ڴ�ʱ����,LRRCֻ����ָʾ��Ƶ���ڽ�����������ʱ�󣬿�������������� */
    VOS_UINT16                                              usSearchTimer;
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stLrrcGurrcDPriInfo;
}GRR_LRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}LRRC_GRR_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GRRָʾLRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_CELL_CHANGE_ORDER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GRRָʾLRRC����CCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;

    /* �տڲ����ڸ�����ʱ����дĬ��ֵ0 */
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;
    VOS_UINT8                                               aucReserved[1];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stLrrcGurrcDPriInfo;
}GRR_LRRC_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR���CCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CCO_RESULT_ENUM_UINT32                       enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��stPlmnIdInfo ��Ч��
     ������Ϊ��С����PLMN IDs */
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfo;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;
}LRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GRRָʾLRRCֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��ֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾ�����л�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    /* ������Ϊ������ RRC CONN RECFG ��Ϣ */
    VOS_UINT32                                              ulHoDataLen;
    VOS_UINT8                                               aucHoData[4];
}GRR_LRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}LRRC_GRR_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GRRָʾLRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  GRRָʾLRRC��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}GRR_LRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��EDSP����ʡ�����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}LRRC_GRR_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾ����IDLE����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stIdleEutranArfcnInfoList;
}GRR_LRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����GRRָʾIDLE�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_GRR_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾIDLE �������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    VOS_UINT8                                               aucReserved[2];

    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stIdleMeasResult;
}LRRC_GRR_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CONNECTED_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾ����CONNECTED����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stConnEutranArfcnInfoList;
}GRR_LRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CONNECTED_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾCONNECTED�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_GRR_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CONNECTED_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾCONNECTED �������
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpid;
    VOS_UINT8                                               aucReserved[2];

    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stConnMeasResult;
}LRRC_GRR_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;

    /* GС��������ƽֵ,������ʽ������޷���ȡ����ΪԼ������Чֵ��*/
    VOS_INT16                                               sGeranCellRxlev;
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stLrrcGurrcDPriInfo;
}LRRC_GRR_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��stPlmnIdInfo ��Ч
        ������Ϊ��С����PLMN ID  */
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfo;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;
    VOS_INT16                                               sC1Param;
    VOS_UINT8                                               aucReserved[2];

}GRR_LRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_SYSINFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTEϵͳ��Я�����ض���CCO���л���Ϣ�е�ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulSysInfoLen;
    VOS_UINT8                                               aucSysInfoData[LRRC_GURRC_GERAN_SYS_MAX_LEN];
}LRRC_GRR_SYSINFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_REDIRECTED_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTEϵͳ��Я�����ض�����Ϣ�е�ϵͳ��Ϣ
                  Э��6.2.2
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              bitulBsicInfoPresent : 1;
    VOS_UINT32                                              bitulSysInfoPresent  : 1;
    VOS_UINT32                                              bitSpare             : 30;

    VOS_UINT16                                              usArfCn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;
    LRRC_GRR_BSIC_INFO_STRU                                 stBsic;

    VOS_UINT32                                              ulSysInfoNum;
    LRRC_GRR_SYSINFO_STRU                                   astRedirSysInfo[LRRC_GURRC_GERAN_SYS_MAX_NUM];
}LRRC_GRR_REDIRECTED_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE ϵͳ��Я�����ض������б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GRR_REDIRECTED_INFO_STRU                           astLrrcGrrRedirInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_GRR_REDIRECTED_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾ�ض�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    LRRC_GRR_REDIRECTED_INFO_LIST_STRU                      stRedirGeranInfo;

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;
    /* CMCC-END */

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];


    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stLrrcGurrcDPriInfo;
}LRRC_GRR_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GRR����LRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}GRR_LRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾ�ض�����������
                  LTE CCO ��GSM���Ǵ�����̬��IDLE��ר��̬��Ϣ��Ч
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU                      stGeranSaveCellInfo;

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;
    /* CMCC-END */

    /* CSFB ��־,1:��ʾ��CSFB, 0: ��ʾ����CSFB */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enCsfbInd;

    /* enNCOPresent = 1: ��ʾ����NCO, 0: ��ʾ������NCO */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enNCOPresent;
    VOS_UINT8                                               ucNetworkControlOrder;

    /* enSysInfoChoice = 1: ��ʾЯ��ϵͳ��Ϣ, 0: ��ʾ��Я�� */
    LRRC_GRR_SYS_TYPE_ENUM_UINT8                            enSysInfoChoice;

    VOS_UINT32                                              ulSysInfoNum;
    LRRC_GRR_SYSINFO_STRU                                   astCcoSysInfo[LRRC_GURRC_GERAN_SYS_MAX_NUM];
}LRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_CHANGE_ORDER_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GRR����LRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CCO_RESULT_ENUM_UINT32                       enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��stPlmnIdInfo ��Ч��
     ������Ϊ��С����PLMN IDs */
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfo;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;
}GRR_LRRC_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_HANDOVER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾHO��������, Э��6.2.2
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    /* v7r2 lld begin */
    /*#ifdef V7R2*/
    /* Add by zhuochao for SRVCC 20131025 begin */
    /* Ŀ��GSMС��Ƶ��ָʾ */
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;

    /* ͬ���л�ʱЯ����L��TA����λΪ1TS��ȡֵ��Ч��Χ[0~20512]TS */
    VOS_UINT16                                              usTaValue;
    /* Add by zhuochao for SRVCC 20131025 end */
    /*#endif*/
    /* v7r2 lld end */

    /* CSFB ��־,1:��ʾ��CSFB, 0: ��ʾ����CSFB */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enCsfbInd;

    /* ucSysInfoChoice =0, ��ʾ��Я��ϵͳ��Ϣ */
    LRRC_GRR_SYS_TYPE_ENUM_UINT8                            enSysInfoChoice;

    VOS_UINT16                                              usSysInfoNum;
    LRRC_GRR_SYSINFO_STRU                                   astHoSysInfo[LRRC_GURRC_GERAN_SYS_MAX_NUM];

    /* ����̬�²���CELL ��Ϣ */
    LRRC_GRR_SAVE_GERAN_CELL_INFO_LIST_STRU                 stGeranCellInfoList;

    VOS_UINT8                                               aucPlmnId[3];
    VOS_UINT8                                               aucReserved[1];

    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;

    VOS_UINT32                                              ulHoDatalen;

    /* �����PS HANDOVER COMMAND ����HANDOVER COMMAND ���� */
    VOS_UINT8                                               aucHoData[4];
}LRRC_GRR_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GRR����LRRCָʾHO���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}GRR_LRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾGRR��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}LRRC_GRR_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��EDSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}GRR_LRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾGRR �ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucPlmnId[3];
    VOS_UINT8                                               aucReserved[1];
}LRRC_GRR_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��UE������ȡ���,GERAN UE CAP��дԭ�����

For GERAN CS: the octet string contains the concatenated string of the Mobile Station Classmark 2
and Mobile Station Classmark 3. The first 5 octets correspond to Mobile Station Classmark 2
and the following octets correspond to Mobile Station Classmark 3. The Mobile Station Classmark 2
is formatted as 'TLV' and is coded in the same way as the Mobile Station Classmark 2 information
element in TS 24.008 [49]. The first octet is the Mobile station classmark 2 IEI and its value shall
be set to 33H. The second octet is the Length of mobile station classmark 2 and its value shall be
set to 3. The octet 3 contains the first octet of the value part of the Mobile Station Classmark 2
information element, the octet 4 contains the second octet of the value part of the Mobile Station
Classmark 2 information element and so on. For each of these octets, the first/ leftmost/ most significant
bit of the octet contains b8 of the corresponding octet of the Mobile Station Classmark 2. The Mobile
Station Classmark 3 is formatted as 'V' and is coded in the same way as the value part in the Mobile
station classmark 3 information element in TS 24.008 [49]. The sixth octet of this octet string contains
octet 1 of the value part of Mobile station classmark 3, the seventh of octet of this octet string contains
octet 2 of the value part of Mobile station classmark 3 and so on. Note.


For GERAN PS: the encoding of UE capabilities is formatted as 'V' and is coded in the same way as the
value part in the MS Radio Access Capability information element in TS 24.008 [49].
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usGeranCsDataLen;
    VOS_UINT16                                              usGeranPsDataLen;
    VOS_UINT8                                               aucGeranCsInfoData[LRRC_GRR_UE_CAP_GEREN_CS_MAX_LEN];
    VOS_UINT8                                               aucGeranPsInfoData[LRRC_GRR_UE_CAP_GEREN_PS_MAX_LEN];
}GRR_LRRC_GETUECAPINFO_CNF_STRU;


typedef struct
{
   VOS_UINT16                                               usArfcn;
   LRRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
}LRRC_GRR_GERAN_CELL_STRU;


typedef struct
{
    VOS_UINT16                                              usArfcnNum;

    /****************************************************************************
    Ƶ����Ϣ�и����ȼ�Ƶ�������IDLE̬����Ч������̬���ֶ�Ϊ������
    ���usArfcnNum =  usHighPriNum����ʾ����ֻ�и����ȼ�Ƶ�㣬
    astGeranCellInfo���˳��Ϊ:�����ȼ���Ϣ -> �����ȼ���Ϣ -> �����ȼ���Ϣ
    �����±�ΪGSMС����CELL ID
    ****************************************************************************/
    VOS_UINT16                                              usHighPrioNum;
    VOS_UINT16                                              usMgsmNum;          /* GSM��������������̬��Ч��IDLE̬���ֶα��� */
    VOS_UINT8                                               aucReserved[2];
    LRRC_GRR_GERAN_CELL_STRU                                astGeranCellInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_GRR_GERAN_CELL_INFO_LIST_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;          /* ��������ָ�����setup��release */
    LRRC_GRR_GERAN_CELL_INFO_LIST_STRU                      stGsmCellInfoList;  /* ������GSMС���б� */
}LRRC_GRR_IDLE_MEASURE_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;             /* ����orֹͣ������� */
}GRR_LRRC_IDLE_MEASURE_CNF_STRU;
typedef struct
{
    VOS_UINT16                                              usArfcn;            /* Ƶ�� */
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;          /* Ƶ��ָʾ */
    VOS_INT16                                               sRssi;              /* sRssi ȡֵ��Χ[-110 * 8,-48 * 8],��λ:dbm,����1/8 */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
}GRR_LRRC_GERAN_CELL_MEAS_RESULT_STRU;


typedef struct
{
    VOS_UINT16                                              usArfcnNum;         /* Ƶ����� */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    GRR_LRRC_GERAN_CELL_MEAS_RESULT_STRU                    astGeranCellResult[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}GRR_LRRC_GERAN_MEAS_RESULT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    GRR_LRRC_GERAN_MEAS_RESULT_IND_STRU                     stGsmMeasResult;    /* �����ϱ���� */
}GRR_LRRC_IDLE_MEASURE_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;          /* ��������ָ�����setup��release */
    LRRC_GRR_GERAN_CELL_INFO_LIST_STRU                      stGsmCellInfoList;  /* ������GSMС���б� */
}LRRC_GRR_CONNECTED_MEASURE_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;             /* ����orֹͣ������� */
}GRR_LRRC_CONNECTED_MEASURE_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    GRR_LRRC_GERAN_MEAS_RESULT_IND_STRU                     stGsmMeasResult;    /* �����ϱ���� */
}GRR_LRRC_CONNECTED_MEASURE_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT16                                              usArfcnNum;         /* bsic��֤��GSMС������ */
    LRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16                  enVerifyTimeIndex;  /* GSM BSIC��ʼȷ�Ϻ���ȷ�ϵ�ʱ������ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
    LRRC_GRR_GERAN_CELL_STRU                                astGeranInfo[LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM];   /* gsmС���б� */
}LRRC_GRR_BSIC_VERIFIED_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
}GRR_LRRC_BSIC_VERIFIED_CNF_STRU;


typedef struct
{
    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;
    VOS_UINT32                                              usTimeAlignment;
    VOS_INT32                                               lFNOffset;
}GRR_LRRC_BSIC_VERIFIED_RESULT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;             /* ������ʶ */
    VOS_UINT16                                              usArfcnNum;         /* Ƶ����� */
    GRR_LRRC_BSIC_VERIFIED_RESULT_STRU                      astGeranBsicVerifedResult[LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM]; /* Ƶ��bsic��֤����б� */
}GRR_LRRC_BSIC_VERIFIED_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GRR_RELALL_REASON_ENUM_UINT8                       enRelReason;        /* LRRC�ͷ�ԭ�� */
    VOS_UINT8                                               aucReserved[3];
}LRRC_GRR_RELALL_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CELL_SRCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRRָʾС������, Я��GС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[1];
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT16                                              usArfcnNum;
    LRRC_GURRC_GERAN_CELL_STRU                              astGeranCellInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_GRR_CELL_SRCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_SRCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����LRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    /* �ҵ�ָ��פ��ģʽ��GС��ʱʹ��LRRC_GURRC_CELL_RESEL_SUCC��
       û���ҵ�ָ��פ��ģʽ��GС��ʱʹ��LRRC_GURRC_CELL_RESEL_UNSPECIFIC */
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ����ָ��פ��ģʽפ��������GС����Ϣ, BSIC��Ϣ��G�ṩ�� ���enRsltΪ�ɹ���
       L����BSIC��Ϣ�Ƿ���Ч������ѡ������ֱ��ʹ�� */

    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;

    /* GС��������ƽֵ,������ʽ������޷���ȡ����ΪԼ������Чֵ��*/
    VOS_INT16                                               sGeranCellRxlev;
    VOS_UINT8                                               aucReserved[2];

    /* stSuitablePlmnId��stPlmnIdList��Ϣֻ��פ��ģʽΪsuitableʱ�����壬
       ��פ��ģʽΪany cellʱ��ʱ���Բ��� */

    /* enRslt = LRRC_GURRC_CELL_RESEL_SUCC ����дG CELL��Я����PLMN*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stSuitablePlmnId;

    /* enRslt = LRRC_GURRC_CELL_RESEL_UNSPECIFIC ��Я���ڴ˹�����������
       �����е�PLMN ��Ϣ���Ըߵ��������򴫵ݸ�LRRC������׼��ͬ������
       PLMN LIST ���� */
    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}GRR_LRRC_CELL_SRCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_CELL_SRCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾGRRֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_CELL_SRCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_CELL_SRCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾLRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_CELL_SRCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :   LRRC_GRR_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾGRRִ�б�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stPlmnId;
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8                       enSearchType;       /* LRRC֪ͨGU���������ѻ���PLMN LIST�� */
    VOS_UINT8                                               aucReserved[1];     /* ����λ */

    VOS_UINT16                                              usForbLaNum;        /* ��ֹע�����ĸ��� */
    LRRC_GURRC_FORB_LA_STRU                                 astForbLaList[LRRC_GURRC_MAX_FORBLA_NUM];/* ��ֹע�����б� */
}LRRC_GRR_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRCִ�б����������õ�ȷ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;             /* ����orֹͣ��� */
    VOS_UINT8                                               aucReserved[2];     /* ����λ */
}GRR_LRRC_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_PLMN_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRCִ�б��������Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;             /* ������ʽ�����ɹ�ʧ�ܽ�� */
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8                       enSearchType;       /* LRRC֪ͨGU���������ѻ���PLMN LIST�� */
    VOS_UINT8                                               aucReserved[1];     /* ����λ */
    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;       /* ��������б� */
}GRR_LRRC_BG_PLMN_SEARCH_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];     /* ����λ */
}LRRC_GRR_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];     /* ����λ */
}GRR_LRRC_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_SEARCH_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾGRR���𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC�ѹ��𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_SEARCH_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾGRR�ָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC�ѻָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_BG_SEARCH_RESUME_CNF_STRU;

/*****************************************************************************
 �ṹ��    :   GRR_LRRC_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  GRRָʾLRRCִ�б�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32               enMsgId;                        /*_H2ASN_Skip*/

    LRRC_GURRC_PLMN_ID_INFO_STRU                stPlmnId;

    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8           enSearchType;                   /* ���������ѻ���PLMN LIST�� */

    VOS_UINT8                                   aucRsv1[3];
}GRR_LRRC_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRCִ�б���������ȷ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                enRslt;
    VOS_UINT8                                              aucRsv1[2];
}LRRC_GRR_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_PLMN_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRRִ�б��������Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;             /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8                       enSearchType;        /* ���������ѻ���PLMN LIST�� */
    VOS_UINT8                                               aucRsv1[1];

    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}LRRC_GRR_BG_PLMN_SEARCH_IND_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾLRRCֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}GRR_LRRC_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR��ֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}LRRC_GRR_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾLRRC���𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_BG_SEARCH_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR�ѹ��𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_BG_SEARCH_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾLRRC�ָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}GRR_LRRC_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   LRRC_GRR_BG_SEARCH_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾGRR�ѻָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];

}LRRC_GRR_BG_SEARCH_RESUME_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_GET_CGI_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾWRRC��ȡ��ӦGSMС����CGI��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;
}LRRC_GRR_GET_CGI_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CELL_GLOBAL_ID_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  GERAN CELL GLOBAL ID��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stPlmnId;
    VOS_UINT16                                              usLocAreaCode;
    VOS_UINT16                                              usCellId;
}LRRC_GRR_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_CGI_INFO_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  GERAN CGI��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_GRR_CELL_GLOBAL_ID_STRU                            stGsmCellGlobalId;
    VOS_INT16                                               sRssi;/* RSSI����ֵ ,ȡֵ��Χ[-110*8,-20*8], ��λ:dBm������ 1/8 */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enRacPresent;
    VOS_UINT8                                               ucRoutingAreaCode;
}LRRC_GRR_CGI_INFO_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    :  GRR_LRRC_GET_CGI_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  GRRָʾLRRC��ӦGSMС��CGI��Ϣ��ȡ���ý��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32                   enRslt;
}GRR_LRRC_GET_CGI_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_GET_CGI_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ӦGSMС��CGI��Ϣ��ȡ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32                   enRslt;

    LRRC_GRR_CGI_INFO_MEAS_RESULT_STRU                      stGsmCgiInfo;
}GRR_LRRC_GET_CGI_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GRR_GET_CGI_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾGRRֹͣANR����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_GRR_GET_CGI_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_LRRC_GET_CGI_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾLRRC��ֹͣANR����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_LRRC_GET_CGI_STOP_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LRRC_GRR_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_GRR_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    LRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_GRR_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_GRR_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_GRR_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : LRRCGRRInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCGRRInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_GRR_MSG_DATA                                       stMsgData;
}LRrcGrrInterface_MSG;

/*****************************************************************************
 �ṹ��    : GRR_LRRC_FR_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRCָʾLRRC��ȡLTE����FRƵ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32            enMsgId;            /*_H2ASN_Skip*/
}GRR_LRRC_FR_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_FR_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾGRRC��ȡLTE����FRƵ��Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_GRR_MSG_TYPE_ENUM_UINT32            enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU    stRedirEutraInfo;
}LRRC_GRR_FR_INFO_CNF_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern PS_BOOL_ENUM_UINT8  LRRC_CheckLteFreqSupported( VOS_UINT16 usArfcn );



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

#endif /* end of LRRC_GRRInterface.h */
