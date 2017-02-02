/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TRrcGrrInterface.h
  Description     : TDS RRC��GRR֮��ӿ��ļ�
  History         :
      1.Xuruimei 49630       2011-10-08   Draft Enact

******************************************************************************/

#ifndef __TRRC_GRRINTERFACE_H__
#define __TRRC_GRRINTERFACE_H__

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
#include  "TRrcGrrCommInterface.h"

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

#define TRRC_GRR_MSG_HDR                (PS_MSG_ID_TRRC_TO_GRR_BASE)
#define GRR_TRRC_MSG_HDR                (PS_MSG_ID_GRR_TO_TRRC_BASE)


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
enum TRRC_GRR_MSG_TYPE_ENUM
{
    /* G -> T Cell Resel */
    ID_GRR_TRRC_CELL_RESEL_REQ                 = (GRR_TRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_REQ_STRU */
    ID_TRRC_GRR_CELL_RESEL_CNF                 = (TRRC_GRR_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_CNF_STRU */
    ID_GRR_TRRC_CELL_RESEL_STOP_REQ            = (GRR_TRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_STOP_REQ_STRU */
    ID_TRRC_GRR_CELL_RESEL_STOP_CNF            = (TRRC_GRR_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_STOP_CNF_STRU */

    /* G -> T Redirect */
    ID_GRR_TRRC_REDIRECTED_REQ                 = (GRR_TRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_REQ_STRU */
    ID_TRRC_GRR_REDIRECTED_CNF                 = (TRRC_GRR_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_CNF_STRU */
    ID_GRR_TRRC_REDIRECTED_STOP_REQ            = (GRR_TRRC_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_STOP_REQ_STRU */
    ID_TRRC_GRR_REDIRECTED_STOP_CNF            = (TRRC_GRR_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_STOP_CNF_STRU */

    /* G -> T CCO */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_REQ          = (GRR_TRRC_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_CNF          = (TRRC_GRR_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ     = (GRR_TRRC_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF     = (TRRC_GRR_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* G -> T ��ȡHO��Ϣ */
    ID_GRR_TRRC_IRAT_HANDOVER_INFO_REQ         = (GRR_TRRC_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU */
    ID_TRRC_GRR_IRAT_HANDOVER_INFO_CNF         = (TRRC_GRR_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU */

    /* G -> T HO */
    ID_GRR_TRRC_HANDOVER_REQ                   = (GRR_TRRC_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_REQ_STRU */
    ID_TRRC_GRR_HANDOVER_CNF                   = (TRRC_GRR_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_CNF_STRU */
    ID_GRR_TRRC_HANDOVER_STOP_REQ              = (GRR_TRRC_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_STOP_REQ_STRU */
    ID_TRRC_GRR_HANDOVER_STOP_CNF              = (TRRC_GRR_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_STOP_CNF_STRU */

    /* G -> T �͹��� */
    ID_GRR_TRRC_SET_DSP_POWER_REQ              = (GRR_TRRC_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice GRR_TRRC_SET_DSP_POWER_REQ_STRU */
    ID_TRRC_GRR_SET_DSP_POWER_CNF              = (TRRC_GRR_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice TRRC_GRR_SET_DSP_POWER_CNF_STRU */

    /* G -> T Meas */
    ID_GRR_TRRC_MEASURE_REQ                    = (GRR_TRRC_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_REQ_STRU */
    ID_TRRC_GRR_MEASURE_CNF                    = (TRRC_GRR_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_CNF_STRU */
    ID_TRRC_GRR_MEASURE_IND                    = (TRRC_GRR_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_IND_STRU */

    /* T -> G Cell Resel*/
    ID_TRRC_GRR_CELL_RESEL_REQ                 = (TRRC_GRR_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_REQ_STRU */
    ID_GRR_TRRC_CELL_RESEL_CNF                 = (GRR_TRRC_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_CNF_STRU */
    ID_TRRC_GRR_CELL_RESEL_STOP_REQ            = (TRRC_GRR_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_STOP_REQ_STRU */
    ID_GRR_TRRC_CELL_RESEL_STOP_CNF            = (GRR_TRRC_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_STOP_CNF_STRU */

    /* T -> G Redirect */
    ID_TRRC_GRR_REDIRECTED_REQ                 = (TRRC_GRR_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_REQ_STRU */
    ID_GRR_TRRC_REDIRECTED_CNF                 = (GRR_TRRC_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_CNF_STRU */
    ID_TRRC_GRR_REDIRECTED_STOP_REQ            = (TRRC_GRR_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_STOP_REQ_STRU */
    ID_GRR_TRRC_REDIRECTED_STOP_CNF            = (GRR_TRRC_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_STOP_CNF_STRU */

    /* T -> G CCO */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_REQ          = (TRRC_GRR_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_CNF          = (GRR_TRRC_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ     = (TRRC_GRR_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF     = (GRR_TRRC_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* T -> G HO */
    ID_TRRC_GRR_HANDOVER_REQ                   = (TRRC_GRR_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_REQ_STRU */
    ID_GRR_TRRC_HANDOVER_CNF                   = (GRR_TRRC_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_CNF_STRU */
    ID_TRRC_GRR_HANDOVER_STOP_REQ              = (TRRC_GRR_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_STOP_REQ_STRU */
    ID_GRR_TRRC_HANDOVER_STOP_CNF              = (GRR_TRRC_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_STOP_CNF_STRU */

    /* T -> G OOS PLMN SEARCH */
    ID_TRRC_GRR_PLMN_SEARCH_REQ                = (TRRC_GRR_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice TRRC_GRR_PLMN_SEARCH_REQ_STRU */
    ID_GRR_TRRC_PLMN_SEARCH_CNF                = (GRR_TRRC_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice GRR_TRRC_PLMN_SEARCH_CNF_STRU */
    ID_TRRC_GRR_PLMN_SEARCH_STOP_REQ           = (TRRC_GRR_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU */
    ID_GRR_TRRC_PLMN_SEARCH_STOP_CNF           = (GRR_TRRC_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU */

    /* T -> G �͹��� */
    ID_TRRC_GRR_SET_DSP_POWER_REQ              = (TRRC_GRR_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice TRRC_GRR_SET_DSP_POWER_REQ_STRU */
    ID_GRR_TRRC_SET_DSP_POWER_CNF              = (GRR_TRRC_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice GRR_TRRC_SET_DSP_POWER_CNF_STRU */

    /* T -> G Get Ue Capability Info */
    ID_TRRC_GRR_GETUECAPINFO_REQ               = (TRRC_GRR_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice TRRC_GRR_GETUECAPINFO_REQ_STRU */
    ID_GRR_TRRC_GETUECAPINFO_CNF               = (GRR_TRRC_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice GRR_TRRC_GETUECAPINFO_CNF_STRU */

    /* T -> G Meas */
    ID_TRRC_GRR_MEASURE_REQ                    = (TRRC_GRR_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_REQ_STRU */
    ID_GRR_TRRC_MEASURE_CNF                    = (GRR_TRRC_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_CNF_STRU */
    ID_GRR_TRRC_MEASURE_IND                    = (GRR_TRRC_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_IND_STRU */

    /* T -> G  Gsm Cell Bsic Verify  */
    ID_TRRC_GRR_BSIC_VERIFIED_REQ              = (TRRC_GRR_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice TRRC_GRR_BSIC_VERIFIED_REQ_STRU */
    ID_GRR_TRRC_BSIC_VERIFIED_CNF              = (GRR_TRRC_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice GRR_TRRC_BSIC_VERIFIED_CNF_STRU */
    ID_GRR_TRRC_BSIC_VERIFIED_IND              = (GRR_TRRC_MSG_HDR + 0x1b),     /* _H2ASN_MsgChoice GRR_TRRC_BSIC_VERIFIED_IND_STRU */

    /* T -> G RelAll */
    ID_TRRC_GRR_RELALL_REQ                     = (TRRC_GRR_MSG_HDR + 0x1c),     /* _H2ASN_MsgChoice TRRC_GRR_RELALL_REQ_STRU */
    ID_GRR_TRRC_RELALL_CNF                     = (GRR_TRRC_MSG_HDR + 0x1c),     /* _H2ASN_MsgChoice GRR_TRRC_RELALL_CNF_STRU */

    ID_TRRC_GRR_MSG_TYPE_BUTT

};
typedef VOS_UINT32  TRRC_GRR_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : GRR_TRRC_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RR���յ����緢�͵�С����ѡ������Ϣ��ͨ����ԭ��ָʾTRRC����С����ѡ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        stUtranTddCell;     /* ��ѡ�� TDSĿ��С���ṹ */
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;       /* TDS: ��ʹ�ô�IE */
    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCampType;        /* ��ҪĿ��С���ǰ���ANYCELL����SUITABLEפ��׼�����פ�� */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[2];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾС���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;
    VOS_UINT32                                              ulTBarLen;          /* ��λΪms������enCnfΪEN_CELL_RESEL_FAIL_REASON_CELL_BARʱ��Ч */
    /* ��GT��ѡ�޷�פ��ʱ����д��sQrxLevValue, �з��š��˱����ȡ�Ϊ����Э�������ʵ������ֵ */
    /* �˲���ֻ����TRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAILͬʱʹ�� */
    VOS_INT16                                               sQrxlevMin;
    /*Ԥ��λ*/
    VOS_INT16                                               sReserved;
}TRRC_GRR_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :GRR_TRRC_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :GRRָʾTRRCֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRR��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRC�����ض�������ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    /* ��REDIR INFO ָʾ������ʱ�� ��λ:����,Ŀǰ�̶�10000ms��
    �ڴ�ʱ����,TLRRCֻ����ָʾ��Ƶ���ڽ�����������ʱ�󣬿����������������TRRCĿǰ��ʹ�� */
    VOS_UINT16                                              usSearchTimer;

	VOS_UINT8												aucReserved1[1];
    VOS_UINT8                                               ucUtranTddCellCnt;  /* total valid cell number */
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        astUtranTddCell[RR_TRRC_MAX_UTRAN_TDD_CELL_NUM];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved2[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32                  enRslt;
}TRRC_GRR_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRCֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRR��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRC����CCO
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        stUtranTddCell;     /* CCO�� TDSĿ��С���ṹ */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR���CCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;

    /* ��usResult ԭ��ֵΪTRRC_GRR_CELL_RESEL_CCO_CELL_BARREDʱ��
       ulTimerVauleֵΪTRRCָʾ�ĳͷ�ʱ��,����ԭ��ֵ�����ô��ֶ� ,��λ :���� */
    VOS_UINT32                                              ulTimerValue; 
}TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  GRRָʾTRRCֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR��ֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*******************************************************************************
 �ṹ��    : GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR��TRR��ȡinter rat hand over info��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /* _H2ASN_Skip */
    PS_BOOL_ENUM_UINT8                                      enNeedCmprVer;      /* �Ƿ���Ҫѹ���汾����Ϣ */
    VOS_UINT8                                               aucReserved[3];     /* �����ֶ�,���ڽ�����չ */
}GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRR inter rat hand over info��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucData[RR_TRRC_INTER_RAT_HANDOVER_INFO_LEN];
}TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_HANDOVER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾ�����л�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;       /* �������ӵ����ͣ���ʹ�ø�IE */
    RRC_CIPHER_ACTIVE_ENUM_UINT32                           enCipherActiveFlg;  /* ָʾGSM�����Ƿ񼤻� */
    VOS_UINT16                                              usHandOverInfoLen;  /* �л�ʱ�տ���Ϣ�а�������Ϣ�ĳ��� */
    VOS_UINT8                                               aucHandOverInfo[2]; /* �л�ʱ�տ���Ϣ�а�������Ϣ�ĵ�ַ */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}GRR_TRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ�л����̽��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32                    enRslt;
}TRRC_GRR_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRCֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRR��ֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_TRRC_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  GRRָʾTRRC��DSP���µ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32                  enSetGDspPowerCmd;
}GRR_TRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_GRR_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR��DSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;             /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32               enRslt;
}TRRC_GRR_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_UTRAN_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UTRAN��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;

   /* ��usCellIdNum = 0ʱ����ʾ������Ƶ����Ϣ����С����Ϣ */
   VOS_UINT16                                               usCellIdNum;
   /* xrm ȷ�ϣ�ausUtranCellIdInfo��� */
   VOS_UINT16                                               ausUtranCellIdInfo[TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM];
}TRRC_UTRAN_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_UTRAN_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UTRAN��ϵͳ��Ϣ�б�
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
   TRRC_UTRAN_CELL_INFO_STRU                                astUtranCellInfo[TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}TRRC_UTRAN_CELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_UTRAN_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : UTRAN CELL �������
             1. ���MS����ȥ�������С������û�в⵽���С�������ϱ����ֵ-116 * 8��
             2. ���MS����ʱ��ԭ��û��ȥ�����С�������ϱ���ЧֵTRRC_GRR_INVALID_iNVALID_RSCP��
             3. ���MS����ȥ�������С�����Ҳ⵽�����С�����ϱ���С���Ĳ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usCellParamId;
    VOS_INT16                                               sRscp;              /* ����1/8 */
}TRRC_UTRAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : UTRAN ����Ƶ�� �������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_INT16                                               sRssi;              /* ����1/8��GTLĿǰ��ʹ�� */
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usCellNum;
    TRRC_UTRAN_CELL_MEAS_RESULT_STRU                        astUtranCellInfo[TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM];
}TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : UTRAN CELL ��������б�
            ע�⣺ 1. ���GAS�·��˵�Ƶ���������TRRC����ϱ���Ƶ���µ� 5 ��С�����������
                   2. ���GAS�·��Ĳ���������һ��Ƶ���µ�С������������ 5 ������TRRC����ϱ���Ƶ���µ� 5 ��С���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT8                                               aucReserved[2];
    TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU                 astUtranResult[TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾ��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_MEAS_CMD_ENUM_UINT16                           enMeasCmd;
    GRR_TRRC_MEAS_GAS_STATUS_ENUM_UINT8                     enGasStatus;
    VOS_UINT8                                               aucReserved[3];
    TRRC_UTRAN_CELL_INFO_LIST_STRU                          stUtranCellInfoList;
}GRR_TRRC_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ�������ý��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
    VOS_UINT8                                               aucReserved[1];
}TRRC_GRR_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU                     stMeasResult;
}TRRC_GRR_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_GERAN_CELL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GERAN��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                               usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                        enBandInd;
}TRRC_GRR_GERAN_CELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_GERAN_CELL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GERAN��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    TRRC_GRR_GERAN_CELL_STRU                                stGCellFreq;
    TRRC_GRR_BSIC_INFO_STRU                                 stBsic;
}TRRC_GRR_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :   TRRC_GRR_BSIC_VERIFIED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR����BSIC����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usGeranInfoNum;
    TRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16                  enVerifyTimeIndex;
    VOS_UINT8                                               aucReserved[2];
    TRRC_GRR_GERAN_CELL_INFO_STRU                           astGeranInfo[TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM];
}TRRC_GRR_BSIC_VERIFIED_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  GRR_TRRC_BSIC_VERIFIED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  GRRָʾTRRC����BSIC�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
}GRR_TRRC_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 �ṹ��    :   GRR_TRRC_BSIC_VERIFIED_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRC��BSIC��֤���
*****************************************************************************/
typedef struct
{
    TRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;
    VOS_UINT32                                              ulTimeAlignment;
    VOS_INT32                                               lFNOffset;
}GRR_TRRC_BSIC_VERIFIED_RESULT_STRU;

/*****************************************************************************
 �ṹ��    :   GRR_TRRC_BSIC_VERIFIED_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRC��BSIC��֤���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usArfcnNum;
    GRR_TRRC_BSIC_VERIFIED_RESULT_STRU                      astGeranBsicVerifedResult[TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM];
}GRR_TRRC_BSIC_VERIFIED_IND_STRU;

/*****************************************************************************
 �ṹ��    :   TRRC_SAVE_GCELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR������ѡЯ����GSMС����Ϣ
*****************************************************************************/
typedef struct
{
    TRRC_GRR_BSIC_INFO_STRU                                 stBsicInfo;         /* BSICֵ */
    VOS_UINT16                                              usBcchArcfn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
    VOS_INT32                                               lFNOffset;
    VOS_UINT32                                              ulTimeAlignmt;
    VOS_INT16                                               sRxlev;             /* GС���źŵ�ƽ����λ��dBm,û�в⵽�źŵ�ƽʱ��ֵΪRR_TRRC_INVALID_RXLEV */
    VOS_UINT8                                               aucReserved[2];
}TRRC_SAVE_GCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :   TRRC_GRR_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   TRRCָʾGRR������ѡ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_SAVE_GCELL_INFO_STRU                               stGsmCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;

    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCampType;

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[2];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾС����ѡ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;

    /* ��usResult ԭ��ֵΪ
       TRRC_GURRC_CELL_RESEL_CELL_BARREDʱ��ulTimerVauleֵΪ20min��20*60*1000��, TRRC_GURRC_CELL_RESEL_ACCESSʱ��
       ulTimerVauleΪ100s��100*1000��,��λ :����*/
    VOS_UINT32                                              ulTimerValue;
    /* ��usResult ԭ��ֵΪTRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAILʱ�� sC1Param������Ч
        ��ʾ��C1ֵ������صĲ�����TRRC���㹫ʽC1= sRxlev- sC1Param, RxlevΪһ����   */
    VOS_INT16                                               sC1Param;
    
    VOS_UINT8                                               aucReserved[2]; 
}GRR_TRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_CELL_RESEL_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRRֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   GRR_TRRC_CELL_RESEL_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRC��ֹͣС������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_REDIRECTED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ�ض�����������.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCellCampedType;
    VOS_UINT8                                               aucReserved1[3];

    /* ulGsmCellCnt =0��ʾȫƵ����������������ЩС�����Ѳ�����ȫƵ�� */
    VOS_UINT32                                              ulGsmCellCnt;
    RRC_SAVE_CELL_INFO_FOR_GAS_ST                           astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* ÿ��GSMС����Ϣ */

    VOS_UINT32                                              ulWaitTimeLen;                          /* wait timeʱ�䣬��λ��ms */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved2[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_REDIRECTED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_REDIRECTED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾ�ض�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32                  enRslt;
}GRR_TRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_REDIRECTED_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRRֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  GRR_TRRC_REDIRECTED_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  GRRָʾTRRC��ֹͣ�ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GSM_GREAN_SYS_INFO_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾCCO��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCnt;              /* ָʾ���鳤��1-23*//* ��ЧֵΪ1~23 */
    VOS_UINT8                                               aucGeranSysInfoBlock[TRRC_RR_MAX_GERAN_SI_LEN];
    VOS_UINT8                                               aucReserved[1];
}TRRC_GSM_GREAN_SYS_INFO_ST;

/*****************************************************************************
 �ṹ��    : TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾCCO��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucReserved[2];
    RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8                       enGeranInfoInd;     /* ucGeranSysInfoCntΪ0ʱ����ֵ��Ч */
    VOS_UINT8                                               ucGeranSysInfoCnt;  /* ��ЧֵΪ 0~ 8 */
    TRRC_GSM_GREAN_SYS_INFO_ST                              stGeranSysInfo[TRRC_RR_MAX_GERAN_SI_CNT];
}TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST;

/*****************************************************************************
 �ṹ��    : TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾCCO��Ϣ
*****************************************************************************/
typedef struct
{
    TRRC_GRR_BSIC_INFO_STRU                                 stBsicInfo;         /* BSICֵ */
    VOS_INT16                                               sRxlev;             /* GС���źŵ�ƽ����λ��dBm,û�в⵽�źŵ�ƽʱ��ֵΪRR_TRRC_INVALID_RXLEV */
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
    VOS_UINT16                                              usBcchArfcn;
    VOS_UINT8                                               ucNCmodeFlag;       /* NCMode���ڱ�־�� 0��ʾ�����ڣ�1��ʾ���� */
    VOS_UINT8                                               ucNCmode;           /* NCMode �������ģʽ�������Ƿ��ϱ��������档 ȷ��*/
    TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST             stGeranSysInfo;
}TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾCCO��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU                     stGsmCellInfo;      /* GSMС����Ϣ */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucReserved[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GRR����TRRCָʾCCO���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;
}GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRRֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRC��ֹͣCCO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_HANDOVER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾHO��������, Э��6.2.2
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_HANDOVER_GSM_GPRS_INFO_ST                           stGsmGprsCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;
    VOS_INT16                                               sTaValue;           /* ��Χ [-24,256],��λ 1/8 chip, 6400 chip = 5ms */
    VOS_UINT8                                               aucReserved[2];
    TRRC_GRR_FAST_RETURN_STRU                               stFastReturn;
}TRRC_GRR_HANDOVER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_HANDOVER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾHO���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32                    enRslt;
}GRR_TRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_HANDOVER_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRCָʾGRRֹͣHO����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_HANDOVER_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR��TRRC�ظ���ֹͣHO����ȷ�Ͻṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC������������GAS����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              ulGsmCellCnt;       /* �����GSM��������ֻ��Ҫ�ҵ���Щ������PLMN����,ȡֵ��Χ 0 ~ 32,0��ʾû����������ҪGAS��ȫƵ������ */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST                           astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];                 /* ÿ��GSMС����Ϣ */

    VOS_UINT32                                              ulAvailPlmnIdNum;   /* PLMN ID���� */
    TRRC_GRR_PLMN_ID_STRU                                   astAvailPlmnIdList[TRRC_GRR_MAX_AVAIL_PLMN_NUM];            /* PlMN��ʶ */
}TRRC_GRR_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_LOW_PLMN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR��TRRC�ظ��ĵ����ȼ�PLMN ID �ṹ
*****************************************************************************/
typedef struct
{
    TRRC_GRR_PLMN_ID_STRU                                   stPlmnId;           /* PLMN ID */
    VOS_INT32                                               lRscp;              /* RSCP����ֵ */
}TRRC_GRR_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRRָʾTRRC�ظ�PLMN�б�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulHighPlmnNum;      /* ������PLMN�ĸ��� */
    VOS_UINT32                                              ulLowPlmnNum;       /* ������PLMN�ĸ��� */
    TRRC_GRR_PLMN_ID_STRU                                   astHighPlmnList[TRRC_GRR_MAX_HIGH_PLMN_NUM];  /* ������PLMN�б�   */
    TRRC_GRR_LOW_PLMN_INFO_STRU                             astLowPlmnList[TRRC_GRR_MAX_LOW_PLMN_NUM];    /* ������PLMN�б�   */
}TRRC_GRR_PLMN_ID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR��TRRC�ظ��ĳ�����������ȷ�Ͻṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
    VOS_UINT8                                               aucReserved[3];

    /* enResultԭ��ֵΪTRRC_GRR_RESULT_SUCCʱ,����Ҫ�����Ƿ���PLMN�����û��PLMN������ΪҲ��ʧ�� */
    TRRC_GRR_PLMN_ID_LIST_STRU                              stPlmnIdList;       /* �ϱ���PLMN ID�б� */
}GRR_TRRC_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC֪ͨGRRֹͣ���������������̽ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR��TRRC�ظ�����ֹͣ����������������ȷ�Ͻṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    :    TRRC_GRR_SET_DSP_POWER_REQ_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  TRRCָʾGRR��DSPʡ��ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32                  enSetGDspPowerCmd;
}TRRC_GRR_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_TRRC_SET_DSP_POWER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRC��DSP�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32              enRslt;
}GRR_TRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TRRC_GRR_GETUECAPINFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  TRRCָʾGRR �ṩUE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :    GRR_TRRC_GETUECAPINFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRC��UE������ȡ���,GERAN UE CAP��дԭ�����

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
    TRRC_GRR_MSG_TYPE_ENUM_UINT32       enMsgId;                                /*_H2ASN_Skip*/
    TRRC_GRR_RESULT_ENUM_UINT8          enRslt;

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 ����,������TRRC��WRR��������IEI */
    VOS_UINT8                           aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 ���� */

    VOS_UINT8                           ucClassmark3Len;                        /* Classmark3 ����,������TRRC��WRR��������IEI */
    VOS_UINT8                           aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 ���� */

    VOS_UINT8                           aucReserved[1];                         /* 4�ֽڶ��룬���� */
}GRR_TRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_IRAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GERAN��ϵͳ��Ϣ�б�
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   Ƶ����Ϣ�и����ȼ�Ƶ�������IDLE̬����Ч������̬���ֶ�Ϊ������
   ���usArfcnNum =  usHighPriNum����ʾ����ֻ�и����ȼ�Ƶ�㣬
   astGeranCellInfo���˳��Ϊ:�����ȼ���Ϣ -> �����ȼ���Ϣ -> �����ȼ���Ϣ
   �����±�ΪGSMС����CELL ID
   ****************************************************************************/
   VOS_UINT16                                               usHighPrioNum;
   VOS_UINT16                                               usMgsmNum;          /* GSM��������������̬��Ч��IDLE̬���ֶα��� */
   VOS_UINT8                                                aucReserved[2];
   TRRC_GRR_GERAN_CELL_STRU                                 astGeranCellInfo[TRRC_GRR_GERAN_ARFCN_MAX_NUM];
}TRRC_GRR_IRAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC����GRRָʾ����IDLE����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_MEAS_CMD_ENUM_UINT16                           enMeasCmd;
    TRRC_GRR_MEAS_TAS_STATUS_ENUM_UINT8                     enTasStatus;
    VOS_UINT8                                               aucReserved[3];
    TRRC_GRR_IRAT_INFO_STRU                                 stInterRatInfo;
}TRRC_GRR_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾ�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[1];
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
}GRR_TRRC_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GERAN CELL �������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;          /* ����L->Wʱ����������Ϣ�е�Ƶ��ָʾһ�� */
    VOS_INT16                                               sRssi;              /* sRssi ȡֵ��Χ[-110 * 8,-48 * 8],��λ:dbm,����1/8 */
    VOS_UINT8                                               aucReserved[2];
}GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  : GERAN CELL ��������б�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT8                                               aucReserved[2];
    GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU                    astGeranCellResult[TRRC_GRR_GERAN_ARFCN_MAX_NUM];
}GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : GRR_TRRC_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GRR����TRRCָʾ�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU                     stMeasResult;
}GRR_TRRC_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    :  TRRC_GRR_RELALL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  TRRCָʾGRRִ��RelAll����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_RELALL_REASON_ENUM_UINT8                       enRelReason;
    VOS_UINT8                                               aucReserved[3];
}TRRC_GRR_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :   GRR_TRRC_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :   GRRָʾTRRCִ��RelAll�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRRC_GRR_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_MsgChoice_Export TRRC_GRR_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TRRC_GRR_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TRRC_GRR_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : TRrcGrrInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TRrcGrrInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TRRC_GRR_MSG_DATA                                       stMsgData;
}TRrcGrrInterface_MSG;


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

#endif /* end of TRrcGrrInterface.h */

