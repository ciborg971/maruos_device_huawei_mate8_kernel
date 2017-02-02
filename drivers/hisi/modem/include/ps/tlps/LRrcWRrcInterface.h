

#ifndef __LRRCWRRCINTERFACE_H__
#define __LRRCWRRCINTERFACE_H__

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

#define LRRC_WRRC_MSG_HDR                (PS_MSG_ID_LRRC_TO_WRRC_BASE)
#define WRRC_LRRC_MSG_HDR                (PS_MSG_ID_WRRC_TO_LRRC_BASE)

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
enum LRRC_WRRC_MSG_TYPE_ENUM
{
    /* W -> L Cell Resel */
    ID_WRRC_LRRC_CELL_RESEL_REQ             = (WRRC_LRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_RESEL_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_CELL_RESEL_CNF             = (LRRC_WRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_RESEL_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CELL_RESEL_STOP_REQ        = (WRRC_LRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_CELL_RESEL_STOP_CNF        = (LRRC_WRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L Redirect */
    ID_WRRC_LRRC_REDIRECTED_REQ             = (WRRC_LRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice WRRC_LRRC_REDIRECTED_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_REDIRECTED_CNF             = (LRRC_WRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LRRC_WRRC_REDIRECTED_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_REDIRECTED_STOP_REQ        = (WRRC_LRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice WRRC_LRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_REDIRECTED_STOP_CNF        = (LRRC_WRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LRRC_WRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L HO */
    ID_WRRC_LRRC_HANDOVER_REQ               = (WRRC_LRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice WRRC_LRRC_HANDOVER_REQ_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_HANDOVER_CNF               = (LRRC_WRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LRRC_WRRC_HANDOVER_CNF_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_HANDOVER_STOP_REQ          = (WRRC_LRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice WRRC_LRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_HANDOVER_STOP_CNF          = (LRRC_WRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LRRC_WRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L �͹��� */
    ID_WRRC_LRRC_SET_DSP_POWER_REQ          = (WRRC_LRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice WRRC_LRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_SET_DSP_POWER_CNF          = (LRRC_WRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LRRC_WRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L Get Ue Capability Info */
    ID_WRRC_LRRC_GETUECAPINFO_REQ           = (WRRC_LRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice WRRC_LRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_GETUECAPINFO_CNF           = (LRRC_WRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LRRC_WRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L PLMN SEARCH */
    ID_WRRC_LRRC_PLMN_SEARCH_REQ            = (WRRC_LRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice WRRC_LRRC_PLMN_SEARCH_REQ_STRU */       /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_PLMN_SEARCH_CNF            = (LRRC_WRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LRRC_WRRC_PLMN_SEARCH_CNF_STRU */       /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_PLMN_SEARCH_STOP_REQ       = (WRRC_LRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice WRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU */  /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_PLMN_SEARCH_STOP_CNF       = (LRRC_WRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LRRC_WRRC_PLMN_SEARCH_STOP_CNF_STRU */  /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* W -> L Idle Meas */
    ID_WRRC_LRRC_IDLE_MEASURE_REQ           = (WRRC_LRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice WRRC_LRRC_IDLE_MEASURE_REQ_STRU */      /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_WRRC_IDLE_MEASURE_CNF           = (LRRC_WRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LRRC_WRRC_IDLE_MEASURE_CNF_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_WRRC_IDLE_MEASURE_IND           = (LRRC_WRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice LRRC_WRRC_IDLE_MEASURE_IND_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* W -> L Conn Meas */
    ID_WRRC_LRRC_CONNECTED_MEASURE_REQ      = (WRRC_LRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice WRRC_LRRC_CONNECTED_MEASURE_REQ_STRU */ /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_WRRC_CONNECTED_MEASURE_CNF      = (LRRC_WRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice LRRC_WRRC_CONNECTED_MEASURE_CNF_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_WRRC_CONNECTED_MEASURE_IND      = (LRRC_WRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice LRRC_WRRC_CONNECTED_MEASURE_IND_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* W -> L RelAll */
    ID_WRRC_LRRC_RELALL_REQ                 = (WRRC_LRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice WRRC_LRRC_RELALL_REQ_STRU */            /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_RELALL_CNF                 = (LRRC_WRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice LRRC_WRRC_RELALL_CNF_STRU */            /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* L -> W Cell Resel*/
    ID_LRRC_WRRC_CELL_RESEL_REQ             = (LRRC_WRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_RESEL_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CELL_RESEL_CNF             = (WRRC_LRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_RESEL_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_CELL_RESEL_STOP_REQ        = (LRRC_WRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CELL_RESEL_STOP_CNF        = (WRRC_LRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> W Redirect */
    ID_LRRC_WRRC_REDIRECTED_REQ             = (LRRC_WRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice LRRC_WRRC_REDIRECTED_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_REDIRECTED_CNF             = (WRRC_LRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice WRRC_LRRC_REDIRECTED_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_REDIRECTED_STOP_REQ        = (LRRC_WRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice LRRC_WRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_REDIRECTED_STOP_CNF        = (WRRC_LRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice WRRC_LRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> W HO */
    ID_LRRC_WRRC_HANDOVER_REQ               = (LRRC_WRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice LRRC_WRRC_HANDOVER_REQ_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_HANDOVER_CNF               = (WRRC_LRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice WRRC_LRRC_HANDOVER_CNF_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_HANDOVER_STOP_REQ          = (LRRC_WRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice LRRC_WRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_HANDOVER_STOP_CNF          = (WRRC_LRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice WRRC_LRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> W �͹��� */
    ID_LRRC_WRRC_SET_DSP_POWER_REQ          = (LRRC_WRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice LRRC_WRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_SET_DSP_POWER_CNF          = (WRRC_LRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice WRRC_LRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> W Get Ue Capability Info */
    ID_LRRC_WRRC_GETUECAPINFO_REQ           = (LRRC_WRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice LRRC_WRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_GETUECAPINFO_CNF           = (WRRC_LRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice WRRC_LRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

   /* L -> W Idle Meas */
    ID_LRRC_WRRC_IDLE_MEASURE_REQ          = (LRRC_WRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice LRRC_WRRC_IDLE_MEASURE_REQ_STRU */     /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_IDLE_MEASURE_CNF          = (WRRC_LRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice WRRC_LRRC_IDLE_MEASURE_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_WRRC_LRRC_IDLE_MEASURE_IND          = (WRRC_LRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice WRRC_LRRC_IDLE_MEASURE_IND_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> W Conn Meas */
    ID_LRRC_WRRC_CONNECTED_MEASURE_REQ     = (LRRC_WRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice LRRC_WRRC_CONNECTED_MEASURE_REQ_STRU */    /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CONNECTED_MEASURE_CNF     = (WRRC_LRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice WRRC_LRRC_CONNECTED_MEASURE_CNF_STRU */    /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_WRRC_LRRC_CONNECTED_MEASURE_IND     = (WRRC_LRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice WRRC_LRRC_CONNECTED_MEASURE_IND_STRU */    /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> W RelAll */
    ID_LRRC_WRRC_RELALL_REQ                = (LRRC_WRRC_MSG_HDR + 0x1b),       /* _H2ASN_MsgChoice LRRC_WRRC_RELALL_REQ_STRU */           /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_RELALL_CNF                = (WRRC_LRRC_MSG_HDR + 0x1c),       /* _H2ASN_MsgChoice WRRC_LRRC_RELALL_CNF_STRU */           /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> W cell srch. L�ؽ�ʱ����UTRAС�� */
    ID_LRRC_WRRC_CELL_SRCH_REQ              = (LRRC_WRRC_MSG_HDR + 0x1c),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_SRCH_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CELL_SRCH_CNF              = (WRRC_LRRC_MSG_HDR + 0x1d),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_SRCH_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_CELL_SRCH_STOP_REQ         = (LRRC_WRRC_MSG_HDR + 0x1d),       /* _H2ASN_MsgChoice LRRC_WRRC_CELL_SRCH_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_CELL_SRCH_STOP_CNF         = (WRRC_LRRC_MSG_HDR + 0x1e),       /* _H2ASN_MsgChoice WRRC_LRRC_CELL_SRCH_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

   /* L -> W BackGroud Search */
    ID_LRRC_WRRC_BG_PLMN_SEARCH_REQ        = (LRRC_WRRC_MSG_HDR + 0x1e),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_PLMN_SEARCH_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_BG_PLMN_SEARCH_CNF        = (WRRC_LRRC_MSG_HDR + 0x1f),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_PLMN_SEARCH_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_WRRC_LRRC_BG_PLMN_SEARCH_IND        = (WRRC_LRRC_MSG_HDR + 0x20),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_PLMN_SEARCH_IND_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_BG_SEARCH_STOP_REQ        = (LRRC_WRRC_MSG_HDR + 0x1f),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_STOP_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_BG_SEARCH_STOP_CNF        = (WRRC_LRRC_MSG_HDR + 0x21),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_STOP_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_BG_SEARCH_SUSPEND_REQ     = (LRRC_WRRC_MSG_HDR + 0x20),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_SUSPEND_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_BG_SEARCH_SUSPEND_CNF     = (WRRC_LRRC_MSG_HDR + 0x22),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_SUSPEND_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_WRRC_BG_SEARCH_RESUME_REQ      = (LRRC_WRRC_MSG_HDR + 0x21),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_RESUME_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_BG_SEARCH_RESUME_CNF      = (WRRC_LRRC_MSG_HDR + 0x23),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_RESUME_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* W-> L BackGroud Search */
    ID_WRRC_LRRC_BG_PLMN_SEARCH_REQ         = (WRRC_LRRC_MSG_HDR + 0x24),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_WRRC_BG_PLMN_SEARCH_CNF         = (LRRC_WRRC_MSG_HDR + 0x22),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_WRRC_BG_PLMN_SEARCH_IND         = (LRRC_WRRC_MSG_HDR + 0x23),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_PLMN_SEARCH_IND_STRU */
    ID_WRRC_LRRC_BG_SEARCH_STOP_REQ         = (WRRC_LRRC_MSG_HDR + 0x25),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_STOP_REQ_STRU */
    ID_LRRC_WRRC_BG_SEARCH_STOP_CNF         = (LRRC_WRRC_MSG_HDR + 0x24),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_STOP_CNF_STRU */
    ID_WRRC_LRRC_BG_SEARCH_SUSPEND_REQ      = (WRRC_LRRC_MSG_HDR + 0x26),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_LRRC_WRRC_BG_SEARCH_SUSPEND_CNF      = (LRRC_WRRC_MSG_HDR + 0x25),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_WRRC_LRRC_BG_SEARCH_RESUME_REQ       = (WRRC_LRRC_MSG_HDR + 0x27),       /* _H2ASN_MsgChoice WRRC_LRRC_BG_SEARCH_RESUME_REQ_STRU */
    ID_LRRC_WRRC_BG_SEARCH_RESUME_CNF       = (LRRC_WRRC_MSG_HDR + 0x26),       /* _H2ASN_MsgChoice LRRC_WRRC_BG_SEARCH_RESUME_CNF_STRU */

    /* L -> W ANR */
    ID_LRRC_WRRC_GET_W_CGI_REQ              = (LRRC_WRRC_MSG_HDR + 0x27),       /* _H2ASN_MsgChoice LRRC_WRRC_GET_W_CGI_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_WRRC_LRRC_GET_W_CGI_CNF              = (WRRC_LRRC_MSG_HDR + 0x28),       /* _H2ASN_MsgChoice WRRC_LRRC_GET_W_CGI_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_WRRC_LRRC_GET_W_CGI_IND              = (WRRC_LRRC_MSG_HDR + 0x29),       /* _H2ASN_MsgChoice WRRC_LRRC_GET_W_CGI_IND_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

   /* L -> W ANR STOP */
    ID_LRRC_WRRC_GET_CGI_STOP_REQ          = (LRRC_WRRC_MSG_HDR + 0x29),       /* _H2ASN_MsgChoice LRRC_WRRC_GET_CGI_STOP_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* L פ��������֪ͨ WAS */
    ID_LRRC_WRRC_CAMP_PLMN_INFO_NTF        = (LRRC_WRRC_MSG_HDR + 0x30),       /* _H2ASN_MsgChoice LRRC_WRRC_CAMP_PLMN_INFO_NTF_STRU */

    /* L ����֪ͨ WAS */
    ID_LRRC_WRRC_AREA_LOST_NTF             = (LRRC_WRRC_MSG_HDR + 0x31),       /* _H2ASN_MsgChoice LRRC_WRRC_AREA_LOST_NTF_STRU */

    ID_WRRC_LRRC_GET_CGI_STOP_CNF          = (WRRC_LRRC_MSG_HDR + 0x32),       /* _H2ASN_MsgChoice WRRC_LRRC_GET_CGI_STOP_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */


    /* W -> L ��ȡ����FR LTEƵ��*/
    ID_WRRC_LRRC_FR_INFO_REQ               = (WRRC_LRRC_MSG_HDR + 0x33),        /* _H2ASN_MsgChoice WRRC_LRRC_FR_INFO_REQ_STRU */
    ID_LRRC_WRRC_FR_INFO_CNF               = (LRRC_WRRC_MSG_HDR + 0x32),        /* _H2ASN_MsgChoice LRRC_WRRC_FR_INFO_CNF_STRU */

    ID_LRRC_WRRC_MSG_TYPE_BUTT = PS_MSG_ID_WRRC_TO_LRRC_BASE + 0x3f              /* !!! ������ϢIDֻ�����ӵ�0x3f*/
};

typedef VOS_UINT32 LRRC_WRRC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}WRRC_LRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��stPlmnIdInfo ��Ч*/
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfoList;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;

    VOS_INT16                                              sQrxLevMin;          /*RSRP��ͽ������ޣ���λ1/8dB*/
    VOS_INT16                                              sQqualMin;           /*RSRQ��ͽ������ޣ���λ1/8dB*/
    VOS_UINT32                                             ulReserved[4];
}LRRC_WRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_ARFCN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRRC�ض�������̬������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usBlackListNum;
    VOS_UINT16                                              ausBlackListCellId[LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM];
}WRRC_LRRC_ARFCN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾ�ض�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                                               aucReserve1[2];

    /* W->L�ض�����Ϣ */
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];


    /* �ͷ�ʱ��ָ����RRC CON REJ ��Я����ʱ��ʣ��ʱ����λ:���� */
    VOS_UINT16                                              usPunishTimerValue;

    /* ��REDIR INFO ָʾ������ʱ�� ��λ:����,Ŀǰ�̶�10000ms��
       �ڴ�ʱ��������ָ��С����ֱ�ӽ���������С������������Ҫ�ȵ��˶�ʱ����ʱ������������SUITABELEС��
    ***************************************************************************/
    VOS_UINT16                                              usSearchTimer;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;   /* �̶�ΪSUITABLE */

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_TYPE_ENUM_UINT8                        enRedirType;
    VOS_UINT8                                               aucReserved2[1];
    /* CMCC-END */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}WRRC_LRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}LRRC_WRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRC����HO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              bitOpCellGlobalId : 1;
    VOS_UINT32                                              bitSpare          : 31;    
    VOS_UINT8                                               aucMcc[3];          /* W֪ͨL��ǰ��������� */ 
    VOS_UINT8                                               aucReserved[1];   
    VOS_UINT16                                              usPrimaryScramCode; /* ��ǰ��С��������*/
    VOS_UINT16                                              usDlUarfcn;         /* ����Ƶ�� */
    LRRC_GURRC_CELL_GLOBAL_ID_STRU                          stCellGlobalId;    
    VOS_UINT32                                              ulHoDataLen;
    /* ������Ϊ������RRC CONN RECFG */
    VOS_UINT8                                               aucHoData[4];
}WRRC_LRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  LRRC����WRRCָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}LRRC_WRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  WRRCָʾLRRC��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}WRRC_LRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��EDSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}LRRC_WRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  WRRCָʾLRRC���ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    /* gaojishan-SYSCFG-SAVENV-Begin */
    VOS_UINT8                                               aucMcc[3];
    VOS_UINT8                                               aucReserved[1];
    /* gaojishan-SYSCFG-SAVENV-End */
}WRRC_LRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��UE������ȡ���
 For EUTRA: the encoding of UE capabilities is defined in IE UE-EUTRA-Capability.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucEutranCapInfoData[LRRC_WRRC_UE_CAP_EUTRAN_MAX_LEN];
}LRRC_WRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRC����PLMN SEARCH����
                 �������UTRAN UE������̬�³��������������̣�
                 LRRC��Ҫ�������������жϸ�С���Ƿ�����SUITABLE׼��
                 ��������ָ����PLMN��������һ�������ǲ�פ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astArfcnInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];
}WRRC_LRRC_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  LRRC����WRRC PLMN SEARCH ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM_UINT16                enPLmnSearchRslt;
    VOS_UINT8                                               aucReserved[2];

    /* usPLmnSearchResult =  LRRC_WRRC_PLMN_SEARCH_SUCC ����дԭ������
       LTE CELL��Я����PLMN LIST�У���RPLMN����дRPLMN������ѡ������
       һ��PLMN ��Ϣ*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stSuitablePlmnId;

    /* usPLmnSearchResult =  LRRC_WRRC_PLMN_SEARCH_FAIL ��Я���ٴι�����������
           ���е�PLMN ��Ϣ���Ըߵ��������򴫵ݸ�WRRC������׼��ͬ������
          PLMN LIST ����*/
    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}LRRC_WRRC_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :WRRCָʾLRRCֹͣPLMN SEARCH����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_PLMN_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��ֹͣPLMN SEARCH ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾ����IDLE����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stIdleEutranArfcnInfoList;
}WRRC_LRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����WRRCָʾIDLE�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_WRRC_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾIDLE�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stIdleMeasRslt;
}LRRC_WRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CONNECTED_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾ����CONNECTED����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;

    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_WRRC_STATE_TYPE_ENUM_UINT16                        enWRrcStateType;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stConnEutranArfcnInfoList;
}WRRC_LRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CONNECTED_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾCONNECTED�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_WRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CONNECTED_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾCONNECTED �������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stConnMeasRslt;
}LRRC_WRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_RELALL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  WRRCָʾLRRCִ��RelAll����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRCִ��RelAll�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����WRRCָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usPrimaryCode;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    PS_BOOL_ENUM_UINT8                                      enLteReestInd;
    VOS_UINT8                                               aucReserved[1];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}LRRC_WRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��
    stPlmnIdInfo ��Ч,������ΪС����PLMN IDs ��Ϣ*/
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfoList;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;
    VOS_INT16                                               sQrxlevMin;         /* */
    VOS_INT16                                               sQqualMin;
    VOS_UINT32                                              aulReserved[4];
}WRRC_LRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_REDIR_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : �ض�����Я����С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT16                                              usSysInfoLen;
    VOS_UINT8                                               aucData[LRRC_WRRC_UTRAN_BCCH_CONTAINER_MAX_BYTE_LEN];
}LRRC_GURRC_REDIR_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_REDIR_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : �ض�����Я����С����Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCellNum;
    LRRC_GURRC_REDIR_CELL_INFO_STRU                         astCellInfo[LRRC_WRRC_REDIR_CELL_MAX_MUN];
}LRRC_GURRC_REDIR_CELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����WRRCָʾ�ض�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    VOS_UINT8                                               aucReserved[3];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enRedirCellInfoPresent; /* �ض���С����Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;      /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_REDIR_CELL_INFO_LIST_STRU                    stRedirCellInfoList;    /* С����Ϣ */
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;             /* ר�����ȼ���Ϣ */

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;
    /* CMCC-END */
}LRRC_WRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}WRRC_LRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  LRRC_WRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRC����HO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* CMCC-BEGIN */
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;
    /* CMCC-END */

    /* CSFB ��־,1:��ʾ��CSFB, 0: ��ʾ����CSFB */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enCsfbInd;

    /* L֪ͨW��ǰפ���Ĺ����� */
    VOS_UINT8                                               aucMcc[3];
    VOS_UINT8                                               aucReserved[2];

    VOS_UINT16                                              usHoDatalen;
    VOS_UINT8                                               aucHoData[4];       /*  ������HANDOVER TO UTRAN COMMAND ����*/
}LRRC_WRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  WRRC����LRRCָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}WRRC_LRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾWRRC��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}LRRC_WRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��EDSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}WRRC_LRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾWRRC���ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    /* gaojishan-SYSCFG-SAVENV-Begin */
    VOS_UINT8                                               aucMcc[3];
    VOS_UINT8                                               aucReserved[1];
    /* gaojishan-SYSCFG-SAVENV-End */
}LRRC_WRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��UE������ȡ���
 For UTRA: the octet string contains the INTER RAT HANDOVER INFO message defined in TS 25.331 [19].
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucUtranCapInfoData[LRRC_WRRC_UE_CAP_UTRAN_MAX_LEN];
}WRRC_LRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_UTRAN_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :UTRAN��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
   LRRC_GURRC_VALID_FLAG_ENUM_UINT8                         enDetectedCellMeasInd; /* �Ƿ���Ҫ����DetectedС�� */
   VOS_UINT8                                                aucReserved[3];

   VOS_UINT16                                               usArfcn;

   /* ��usCellIdNum = 0ʱ����ʾ������Ƶ����Ϣ����������Ϣ */
   VOS_UINT16                                               usCellIdNum;
   VOS_UINT16                                               ausUtranCellIdInfo[LRRC_GURRC_MAX_UTRAN_CELL_PER_FREQ_NUM];
}LRRC_GURRC_UTRAN_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :UTRAN��ϵͳ��Ϣ�б�
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   Ƶ����Ϣ�и����ȼ�Ƶ���������ΪIDLE̬����Ч, ����̬�¸��ֶ�Ϊ������
   ���usArfcnNum =  usHighPriNum����ʾ����ֻ�и����ȼ�Ƶ�㣬
   astUtranCellInfo���˳��Ϊ:�����ȼ���Ϣ -> �����ȼ���Ϣ -> �����ȼ���Ϣ
   ****************************************************************************/
   VOS_UINT16                                               usHighPrioNum;
   /* begin: for modify TDD max Meas Num  */
   LRRC_GURRC_UTRAN_CELL_INFO_STRU                          astUtranCellInfo[LRRC_TRRC_PHY_MAX_SUPPORT_CARRIER_NUM];
   /* end: for modify TDD max Meas Num  */
}LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾ����IDLE����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_WRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : WRRC����LRRCָʾIDLE�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}WRRC_LRRC_IDLE_MEASURE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : GURRC_LRRC_UTRAN_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GERAN CELL �������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT8                                               aucReserved[2];
    VOS_INT16                                               sRscp;              /* ����1/8 */
    VOS_INT16                                               sEcN0;              /* ����1/8 */
}GURRC_LRRC_UTRAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GURRC_LRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : UTRAN ����Ƶ�� �������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_INT16                                               sRssi;              /* ����1/8 */
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usCellNum;
    GURRC_LRRC_UTRAN_CELL_MEAS_RESULT_STRU                  astUtranCellInfo[LRRC_GURRC_MAX_UTRAN_CELL_PER_FREQ_NUM];
}GURRC_LRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : UTRAN CELL ��������б�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT8                                               aucReserved[2];
    /* begin: for modify TDD max Meas Num  */
    GURRC_LRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU           astUtranResult[LRRC_TRRC_PHY_MAX_SUPPORT_CARRIER_NUM];
    /* end: for modify TDD max Meas Num  */
}GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾIDLE�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}WRRC_LRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CONNECTED_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾ����CONNECTED����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_WRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CONNECTED_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾCONNECTED�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}WRRC_LRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CONNECTED_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾCONNECTED �������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}WRRC_LRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_RELALL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾWRRCִ��RelAll����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRCִ��RelAll�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CELL_SRCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����WRRCָʾС��������Я��С���б�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[1];
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT16                                              usArfcnNum;
    LRRC_GURRC_UTRAN_CELL_INFO_STRU                         astUtranCellInfo[LRRC_GURRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_WRRC_CELL_SRCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_LRRC_CELL_SRCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRC����LRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* �ҵ�ָ��פ��ģʽ��UTRAС��ʱʹ��LRRC_GURRC_CELL_RESEL_SUCC��
       û���ҵ�ָ��פ��ģʽ��UTRAС��ʱʹ��LRRC_GURRC_CELL_RESEL_UNSPECIFIC */
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ����ָ��פ��ģʽפ��������UTRAС����Ϣ */
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usPrimaryCode;

    /* stSuitablePlmnId��stPlmnIdList��Ϣֻ��פ��ģʽΪsuitableʱ�����壬
       ��פ��ģʽΪany cellʱ��ʱ���Բ��� */

    /* enRslt = LRRC_GURRC_CELL_RESEL_SUCC ����дԭ������
       UTRA CELL��Я����PLMN LIST�У���RPLMN����дRPLMN������ѡ������
       һ��PLMN ��Ϣ*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stSuitablePlmnId;

    /* enRslt = LRRC_GURRC_CELL_RESEL_UNSPECIFIC ��Я���ڴ˹�����������
       �����е�PLMN ��Ϣ���Ըߵ��������򴫵ݸ�LRRC������׼��ͬ������
       PLMN LIST ���� */
    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}WRRC_LRRC_CELL_SRCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CELL_SRCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_CELL_SRCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_CELL_SRCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_CELL_SRCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :   LRRC_WRRC_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾW RRCִ�б�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32              enMsgId;                        /*_H2ASN_Skip*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                stPlmnId;
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8           enSearchType;                   /* LRRC֪ͨGU���������ѻ���PLMN LIST�� */
    VOS_UINT8                                   aucReserved[1];

    VOS_UINT16                                  usForbLaNum;                    /* ��ֹע�����ĸ��� */
    LRRC_GURRC_FORB_LA_STRU                     astForbLaList[LRRC_GURRC_MAX_FORBLA_NUM];
                                                                                /* ��ֹע�����б� */
}LRRC_WRRC_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRCִ�б����������õ�ȷ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT8                                               aucReserved[2];
}WRRC_LRRC_BG_PLMN_SEARCH_CNF_STRU;


/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_PLMN_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRCִ�б��������Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8                       enSearchType;       /* LRRC֪ͨGU���������ѻ���PLMN LIST�� */
    VOS_UINT8                                               aucReserved[1];

    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}WRRC_LRRC_BG_PLMN_SEARCH_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRCֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_SEARCH_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRC���𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC�ѹ��𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_SEARCH_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRC�ָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC�ѻָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_BG_SEARCH_RESUME_CNF_STRU;

/*****************************************************************************
 �ṹ��    :   WRRC_LRRC_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  WRRCָʾLRRCִ�б�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32              enMsgId;                        /*_H2ASN_Skip*/

    LRRC_GURRC_PLMN_ID_INFO_STRU                stPlmnId;

    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8           enSearchType;                   /* ���������ѻ���PLMN LIST�� */

    VOS_UINT8                                   aucRsv1[3];
}WRRC_LRRC_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRCִ�б���������ȷ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT8                                               aucRsv1[2];
}LRRC_WRRC_BG_PLMN_SEARCH_CNF_STRU;


/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_PLMN_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRCִ�б��������Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16                 enRslt;
    LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8                       enSearchType;       /* ���������ѻ���PLMN LIST�� */
    VOS_UINT8                                               aucRsv1[1];

    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}LRRC_WRRC_BG_PLMN_SEARCH_IND_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRCָʾLRRCֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_SEARCH_REL_STOP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC��ֹͣ������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                         enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}LRRC_WRRC_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRCָʾLRRC���𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_BG_SEARCH_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC�ѹ��𱳾���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_BG_SEARCH_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRCָʾLRRC�ָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                         enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}WRRC_LRRC_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   LRRC_WRRC_BG_SEARCH_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾWRRC�ѻָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                         enMsgId;             /*_H2ASN_Skip*/
    VOS_UINT8                                              aucReserved[4];
}LRRC_WRRC_BG_SEARCH_RESUME_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_GET_W_CGI_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾWRRC��ȡ��ӦС����CGI��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_GET_W_CGI_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_CGI_INFO_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  UTRAN CGI��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT16                                               sRscp;              /* ����1/8 */
    VOS_INT16                                               sEcN0;              /* ����1/8 */
    LRRC_GURRC_CELL_GLOBAL_ID_STRU                          stCellGlobalId;
    VOS_UINT16                                              usPlmnCnt;
    VOS_UINT8                                               aucReserved1[2];
    LRRC_GURRC_PLMN_ID_INFO_STRU                            astPlmnIdList[LRRC_WRRC_MAX_NUM_OF_PLMN_ID_LIST_2];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enLacPresent;
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enRacPresent;
    VOS_UINT16                                              usLocAreaCode;
    VOS_UINT8                                               ucRoutingAreaCode;
    VOS_UINT8                                               aucReserved[3];
}LRRC_WRRC_CGI_INFO_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_GET_W_CGI_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ӦС��CGI��Ϣ��ȡ���ý��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32                   enRslt;
}WRRC_LRRC_GET_W_CGI_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_GET_W_CGI_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ӦС��CGI��Ϣ��ȡ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32                   enRslt;

    LRRC_WRRC_CGI_INFO_MEAS_RESULT_STRU                     stCgiInfo;
}WRRC_LRRC_GET_W_CGI_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_WRRC_GET_CGI_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾWRRCֹͣANR����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_WRRC_GET_CGI_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    WRRC_LRRC_GET_CGI_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   WRRCָʾLRRC��ֹͣANR����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}WRRC_LRRC_GET_CGI_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_WRRC_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_MsgChoice_Export LRRC_WRRC_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_WRRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_WRRC_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : LRRCWRRCInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCWRRCInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_WRRC_MSG_DATA                                      stMsgData;
}LRrcWRrcInterface_MSG;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_CAMP_PLMN_INFO_NFT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRC��ǰפ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32        enMsgId;                /*_H2ASN_Skip*/
    LRRC_GURRC_PLMN_ID_INFO_STRU          stPlmnIdInfo;
}LRRC_WRRC_CAMP_PLMN_INFO_NTF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_AREA_LOST_NFT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRC��ǰLRRC����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32        enMsgId;           /*_H2ASN_Skip*/
    VOS_UINT8                             aucResrved[4];
}LRRC_WRRC_AREA_LOST_NTF_STRU;


/*****************************************************************************
 �ṹ��    : WRRC_LRRC_FR_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WRRCָʾLRRC��ȡLTE����FRƵ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
}WRRC_LRRC_FR_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_WRRC_FR_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾWRRC��ȡLTE����FRƵ��Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_WRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU    stRedirEutraInfo;
}LRRC_WRRC_FR_INFO_CNF_STRU;

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

#endif /* end of LRRC_WRRCInterface.h */

