

#ifndef __LRRCTRRCINTERFACE_H__
#define __LRRCTRRCINTERFACE_H__

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
#include  "LRrcWRrcInterface.h"

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

#define LRRC_TRRC_MSG_HDR                (PS_MSG_ID_LRRC_TO_TRRC_BASE)
#define TRRC_LRRC_MSG_HDR                (PS_MSG_ID_TRRC_TO_LRRC_BASE)

/* UTRAN TDD UE �����������󳤶�*/
#define LRRC_TRRC_UE_CAP_UTRAN_MAX_LEN                      256


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
enum LRRC_TRRC_MSG_TYPE_ENUM
{
    /* T -> L Cell Resel */
    ID_TRRC_LRRC_CELL_RESEL_REQ             = (TRRC_LRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_CNF             = (LRRC_TRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_STOP_REQ        = (TRRC_LRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_STOP_CNF        = (LRRC_TRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Redirect */
    ID_TRRC_LRRC_REDIRECTED_REQ             = (TRRC_LRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_CNF             = (LRRC_TRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_STOP_REQ        = (TRRC_LRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_STOP_CNF        = (LRRC_TRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L HO */
    ID_TRRC_LRRC_HANDOVER_REQ               = (TRRC_LRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_REQ_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_CNF               = (LRRC_TRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_CNF_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_STOP_REQ          = (TRRC_LRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_STOP_CNF          = (LRRC_TRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L �͹��� */
    ID_TRRC_LRRC_SET_DSP_POWER_REQ          = (TRRC_LRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice TRRC_LRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_SET_DSP_POWER_CNF          = (LRRC_TRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LRRC_TRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Get Ue Capability Info */
    ID_TRRC_LRRC_GETUECAPINFO_REQ           = (TRRC_LRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice TRRC_LRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_GETUECAPINFO_CNF           = (LRRC_TRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LRRC_TRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L PLMN SEARCH */
    ID_TRRC_LRRC_PLMN_SEARCH_REQ            = (TRRC_LRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice TRRC_LRRC_PLMN_SEARCH_REQ_STRU */       /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_PLMN_SEARCH_CNF            = (LRRC_TRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LRRC_TRRC_PLMN_SEARCH_CNF_STRU */       /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_PLMN_SEARCH_STOP_REQ       = (TRRC_LRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU */  /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_PLMN_SEARCH_STOP_CNF       = (LRRC_TRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU */  /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Idle Meas */
    ID_TRRC_LRRC_IDLE_MEASURE_REQ           = (TRRC_LRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_REQ_STRU */      /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_TRRC_IDLE_MEASURE_CNF           = (LRRC_TRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_CNF_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_TRRC_IDLE_MEASURE_IND           = (LRRC_TRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_IND_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* T -> L Conn Meas */
    ID_TRRC_LRRC_CONNECTED_MEASURE_REQ      = (TRRC_LRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU */ /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_TRRC_CONNECTED_MEASURE_CNF      = (LRRC_TRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_TRRC_CONNECTED_MEASURE_IND      = (LRRC_TRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_IND_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* T -> L RelAll */
    ID_TRRC_LRRC_RELALL_REQ                 = (TRRC_LRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice TRRC_LRRC_RELALL_REQ_STRU */            /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_RELALL_CNF                 = (LRRC_TRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice LRRC_TRRC_RELALL_CNF_STRU */            /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* L -> T Cell Resel*/
    ID_LRRC_TRRC_CELL_RESEL_REQ             = (LRRC_TRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_CNF             = (TRRC_LRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_STOP_REQ        = (LRRC_TRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_STOP_CNF        = (TRRC_LRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T Redirect */
    ID_LRRC_TRRC_REDIRECTED_REQ             = (LRRC_TRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_CNF             = (TRRC_LRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_STOP_REQ        = (LRRC_TRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_STOP_CNF        = (TRRC_LRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T HO */
    ID_LRRC_TRRC_HANDOVER_REQ               = (LRRC_TRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_REQ_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_CNF               = (TRRC_LRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_CNF_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_STOP_REQ          = (LRRC_TRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_STOP_CNF          = (TRRC_LRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> T �͹��� */
    ID_LRRC_TRRC_SET_DSP_POWER_REQ          = (LRRC_TRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice LRRC_TRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_SET_DSP_POWER_CNF          = (TRRC_LRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice TRRC_LRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T Get Ue Capability Info */
    ID_LRRC_TRRC_GETUECAPINFO_REQ           = (LRRC_TRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice LRRC_TRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_GETUECAPINFO_CNF           = (TRRC_LRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice TRRC_LRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> T Idle Meas */
    ID_LRRC_TRRC_IDLE_MEASURE_REQ           = (LRRC_TRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_REQ_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_IDLE_MEASURE_CNF           = (TRRC_LRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_TRRC_LRRC_IDLE_MEASURE_IND           = (TRRC_LRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_IND_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> T Conn Meas */
    ID_LRRC_TRRC_CONNECTED_MEASURE_REQ      = (LRRC_TRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_REQ_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CONNECTED_MEASURE_CNF      = (TRRC_LRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU */ /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_TRRC_LRRC_CONNECTED_MEASURE_IND      = (TRRC_LRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_IND_STRU */ /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> T RelAll */
    ID_LRRC_TRRC_RELALL_REQ                = (LRRC_TRRC_MSG_HDR + 0x19),        /* _H2ASN_MsgChoice LRRC_TRRC_RELALL_REQ_STRU */             /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_RELALL_CNF                = (TRRC_LRRC_MSG_HDR + 0x19),        /* _H2ASN_MsgChoice TRRC_LRRC_RELALL_CNF_STRU */             /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    ID_LRRC_TRRC_FR_INFO_CNF               = (LRRC_TRRC_MSG_HDR + 0x1a),        /* _H2ASN_MsgChoice LRRC_TRRC_FR_INFO_CNF_STRU */
    ID_TRRC_LRRC_FR_INFO_REQ               = (TRRC_LRRC_MSG_HDR + 0x1a),        /* _H2ASN_MsgChoice TRRC_LRRC_FR_INFO_REQ_STRU */

    ID_LRRC_TRRC_MSG_TYPE_BUTT = PS_MSG_ID_TRRC_TO_LRRC_BASE + 0x9f             /*!!!������ϢIDֻ�����ӵ�0x9f*/
};

typedef VOS_UINT32 LRRC_TRRC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}TRRC_LRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
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
}LRRC_TRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾ�ض�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                                               aucReserve1[2];

    /* T->L�ض�����Ϣ */
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];


    /* �ͷ�ʱ��ָ����RRC CON REJ ��Я����ʱ��ʣ��ʱ����λ:���� */
    VOS_UINT16                                              usPunishTimerValue;

    /* ��REDIR INFO ָʾ������ʱ�� ��λ:����,Ŀǰ�̶�10000ms��
       �ڴ�ʱ��������ָ��С����ֱ�ӽ���������С������������Ҫ�ȵ��˶�ʱ����ʱ������������SUITABELEС��
    ***************************************************************************/
    VOS_UINT16                                              usSearchTimer;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;   /* �̶�ΪSUITABLE */
    VOS_UINT8                                               aucReserve2[2];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}TRRC_LRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}LRRC_TRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_TRRC_PLMN_ID_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :PLMN��Ϣ
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucPlmnId[3];
    VOS_UINT8                                               aucReserved[1];
}LRRC_TRRC_PLMN_ID_INFO_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GURRC_CELL_GLOBAL_ID_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  UTRAN/EUTRAN CELL GLOBAL ID��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_TRRC_PLMN_ID_INFO_STRU                            stPlmnId;
    VOS_UINT32                                              ulCellId;
}LRRC_TRRC_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRC����HO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              bitOpCellGlobalId : 1;
    VOS_UINT32                                              bitSpare          : 31;
    /* L֪ͨT��ǰפ���Ĺ����� */
    VOS_UINT8                                               aucMcc[3];
    VOS_UINT8                                               aucReserved[1];
    VOS_UINT16                                              usPrimaryScramCode; /* ��ǰ��С��������*/
    VOS_UINT16                                              usDlUarfcn;         /* ����Ƶ�� */
    LRRC_TRRC_CELL_GLOBAL_ID_STRU                          stCellGlobalId;
    VOS_UINT32                                              ulHoDataLen;
    /* ������Ϊ������RRC CONN RECFG */
    VOS_UINT8                                               aucHoData[4];
}TRRC_LRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  LRRC����TRRCָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}LRRC_TRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  TRRCָʾLRRC��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}TRRC_LRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��EDSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}LRRC_TRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  TRRCָʾLRRC���ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usMcc;
    VOS_UINT8                                               aucReserved[2];
}TRRC_LRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��UE������ȡ���
 For EUTRA: the encoding of UE capabilities is defined in IE UE-EUTRA-Capability.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucEutranCapInfoData[LRRC_WRRC_UE_CAP_EUTRAN_MAX_LEN];
}LRRC_TRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRC����PLMN SEARCH����
                 �������UTRAN UE������̬�³��������������̣�
                 LRRC��Ҫ�������������жϸ�С���Ƿ�����SUITABLE׼��
                 ��������ָ����PLMN��������һ�������ǲ�פ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astArfcnInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];
}TRRC_LRRC_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  LRRC����TRRC PLMN SEARCH ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
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
}LRRC_TRRC_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :TRRCָʾLRRCֹͣPLMN SEARCH����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRC��ֹͣPLMN SEARCH ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾ����IDLE����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stIdleEutranArfcnInfoList;
}TRRC_LRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����TRRCָʾIDLE�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_TRRC_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾIDLE�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stMeasRslt;
}LRRC_TRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾ����CONNECTED����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;

    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_WRRC_STATE_TYPE_ENUM_UINT16                        enTRrcStateType;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stConnEutranArfcnInfoList;
}TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾCONNECTED�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_CONNECTED_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾCONNECTED �������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stMeasRslt;
}LRRC_TRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_RELALL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  TRRCָʾLRRCִ��RelAll����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   LRRCָʾTRRCִ��RelAll�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����TRRCָʾС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usPrimaryCode;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}LRRC_TRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_NOT_EPLMNSʱ��
    stPlmnIdInfo ��Ч,������ΪС����PLMN IDs ��Ϣ*/
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfoList;

    /* ��usResult ԭ��ֵΪLRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVaule��Ч,��λ :����*/
    VOS_UINT32                                              ulTimerValue;

    /* ��LT��ѡ�޷�פ��ʱ����д��lQrxLevValue, �з��š��˱����ȡ�Ϊ����Э�������ʵ������ֵ */
    /* �˲���ֻ����LRRC_GURRC_CELL_RESEL_PATH_LOSS_CHECK_FAILͬʱʹ�� */
    VOS_INT16                                               sQrxlevMin;
    VOS_INT16                                               sQqualMin;
    /* Ԥ��λ */
    VOS_UINT32                                              aulReserved[4];

}TRRC_LRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾTRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU;

/* v7r2 code begin */

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_REDIR_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : �ض�����Я����С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT16                                              usArfcn;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usSysInfoLen;
    VOS_UINT8                                               aucData[LRRC_WRRC_UTRAN_BCCH_CONTAINER_MAX_BYTE_LEN];
}LRRC_TRRC_REDIR_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_REDIR_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC�ض�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT16                                              usCellInfoNum;
    VOS_UINT16                                              ausArfcn[LRRC_TRRC_REDIR_FREQ_MAX_MUN];
    LRRC_TRRC_REDIR_CELL_INFO_STRU                          astCellInfo[LRRC_WRRC_REDIR_CELL_MAX_MUN];
}LRRC_TRRC_REDIR_INFO_LIST_STRU;
/* v7r2 code end */

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : LRRC����TRRCָʾ�ض�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    /* v7r2 code begin */
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;      /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    LRRC_TRRC_REDIR_INFO_LIST_STRU                          stRedirInfoList;    /* С����Ϣ */
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;             /* ר�����ȼ���Ϣ */
    /* v7r2 code end */
}LRRC_TRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}TRRC_LRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾTRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  LRRC_TRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾTRRC����HO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* CSFB ��־,1:��ʾ��CSFB, 0: ��ʾ����CSFB */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enCsfbInd;
    VOS_UINT8                                               aucReserved[1];

    VOS_UINT16                                              usHoDatalen;
    VOS_UINT8                                               aucHoData[4];       /*  ������HANDOVER TO UTRAN COMMAND ����*/
}LRRC_TRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  TRRC����LRRCָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}TRRC_LRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LRRCָʾTRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾTRRC��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}LRRC_TRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC��EDSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}TRRC_LRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾTRRC���ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usMcc;
    VOS_UINT8                                               aucReserved[2];
}LRRC_TRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRC��UE������ȡ���
 For UTRA: the octet string contains the INTER RAT HANDOVER INFO message defined in TS 25.331 [19].
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucUtranCapInfoData[LRRC_TRRC_UE_CAP_UTRAN_MAX_LEN];
}TRRC_LRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾ��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_TRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : TRRC����LRRCָʾIDLE�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}TRRC_LRRC_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾIDLE�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}TRRC_LRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����LRRCָʾ����CONNECTED����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_TRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾCONNECTED�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_CONNECTED_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����TRRCָʾCONNECTED �������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}TRRC_LRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_TRRC_RELALL_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  LRRCָʾTRRCִ��RelAll����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_LRRC_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾLRRCִ��RelAll�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_RELALL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_TRRC_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_TRRC_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_MsgChoice_Export LRRC_TRRC_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_TRRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_TRRC_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : LRRC_TRRCInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_TRRCInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_TRRC_MSG_DATA                                      stMsgData;
}LRrcTRrcInterface_MSG;

/*****************************************************************************
 �ṹ��    : TRRC_LRRC_FR_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾLRRC��ȡLTE����FRƵ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
}TRRC_LRRC_FR_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_TRRC_FR_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRCָʾTRRC��ȡLTE����FRƵ��Ľ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU    stRedirEutraInfo;
}LRRC_TRRC_FR_INFO_CNF_STRU;

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

#endif /* end of LRRC_TRRCInterface.h */


