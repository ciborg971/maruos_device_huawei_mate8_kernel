

#ifndef __LRRC_GURRCCOMMINTERFACE_H__
#define __LRRC_GURRCCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

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
/* 3GPP Э���Ϲ涨���EUTRANƵ���� */
#define LRRC_GURRC_LTE_ARFCN_MAX_NUM                        8

/* UE֧�ֵ�EUTRANƵ�����������Ŀ */
/* begin: add for feature v700r500 */

/* Begin: add inter meas ferq num */
/* UE֧�ֵ�EUTRANƵ�����������Ŀ */
#define LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM          8
/* End: add inter meas ferq num */

/* begin: end for feature v700r500 */

/* EUTRAN ����Ƶ��֧��С�������Ŀ */
#define LRRC_GURRC_MAX_LTE_CELL_PER_FREQ_NUM                32

/* EUTRAN ����Ƶ����֧�ֵĺ�����С����Ŀ*/
#define LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM                  16

/* 3GPP Э���Ϲ涨���UTRANƵ���� */
#define LRRC_GURRC_UTRAN_ARFCN_MAX_NUM                      16

/* UE֧�ֵ�UTRANƵ�����������Ŀ */
#define LRRC_GURRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM        3

/* begin: for modify TDD max Meas Num  */
/* UE֧�ֵ�UTRANƵ�����������Ŀ */
#define LRRC_TRRC_PHY_MAX_SUPPORT_CARRIER_NUM               9
/* end: for modify TDD max Meas Num  */

/* UTRAN ����Ƶ��֧��С�������Ŀ */
#define LRRC_GURRC_MAX_UTRAN_CELL_PER_FREQ_NUM              32

/* 3GPP Э���Ϲ涨���GERANƵ���� */
#define LRRC_GURRC_GERAN_ARFCN_MAX_NUM                      32

/* LUE ֧������BSIC VERFIED С������*/
#define LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM              8

/* EUTRAN ֧�ֵ� GERAN ϵͳ��Ϣ����*/
#define LRRC_GURRC_GERAN_SYS_MAX_NUM                        10

/* EUTRAN ֧�ֵ� GERAN ϵͳ��Ϣ��󳤶� */
#define LRRC_GURRC_GERAN_SYS_MAX_LEN                        24

/* PLMN ����ʱ��������PLMN ������ */
#define LRRC_GURRC_MAX_HIGH_PLMN_NUM                        16

/* PLMN ����ʱ��������PLMN ������ */
#define LRRC_GURRC_MAX_LOW_PLMN_NUM                         16

/* EUTRAN�е���С�����������PLMN ����*/
#define LRRC_GURRC_PLMN_ID_MAX_NUM                          6

/* UTRAN UE �����������󳤶�*/
#define LRRC_WRRC_UE_CAP_UTRAN_MAX_LEN                      256

/* EUTRAN UE �����������󳤶�*/
#define LRRC_WRRC_UE_CAP_EUTRAN_MAX_LEN                     1024

/* GERAN CS UE �����������󳤶�*/
#define LRRC_GRR_UE_CAP_GEREN_CS_MAX_LEN                    128

/* GERAN PS UE �����������󳤶�*/
#define LRRC_GRR_UE_CAP_GEREN_PS_MAX_LEN                    128

/* L�ض���ʱ��������UTRAN CELL ������ */
#define LRRC_WRRC_REDIR_CELL_MAX_MUN                        16
/* v7r2 code begin */
/* L�ض���ʱ��������UTRAN FREQ ������ */
#define LRRC_TRRC_REDIR_FREQ_MAX_MUN                        6
/* v7r2 code end */

/* L�ض���ʱ��������UTRAN CELL ��ϵͳ��Ϣ��󳤶� */
#define LRRC_WRRC_UTRAN_BCCH_CONTAINER_MAX_BYTE_LEN         640


/* L CellResel����CCO��Gʱ�����Ŀ��GС��û�в���ֵ���ӿ������õ���Чֵ */
#define LRRC_GRR_INVALID_CELL_RXLEV_VALUE                   0x00FF

#define LRRC_WRRC_MAX_NUM_OF_PLMN_ID_LIST_2                 5

#define LRRC_GURRC_MAX_FORBLA_NUM                           (16)

/* bgs begin */
/* FORBID TA ������ */
#define LRRC_GURRC_MAX_FORBTA_NUM                           (64)
/* bgs end */

/* EUTRAN ר�����ȼ������� */
#define LRRC_GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM             (64)

/* UTRAN ר�����ȼ������� */
#define LRRC_GURRC_UTRAN_DEDICATED_PRI_MAX_NUM              (64)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : LRRC_GURRC_MEAS_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ö��(��������)
*****************************************************************************/
enum LRRC_GURRC_MEAS_BAND_WIDTH_ENUM
{
    LRRC_GURRC_MEAS_BAND_WIDTH_6RB                          = 0,                /* ����Ϊ6RB   */
    LRRC_GURRC_MEAS_BAND_WIDTH_15RB                            ,                /* ����Ϊ15RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_25RB                            ,                /* ����Ϊ25RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_50RB                            ,                /* ����Ϊ50RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_75RB                            ,                /* ����Ϊ75RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_100RB                           ,                /* ����Ϊ100RB */

    LRRC_GURRC_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
 ö����     :LRRC_GRR_BANDINDICATOR_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : 2GС��Ƶ��ָʾ
*****************************************************************************/
enum LRRC_GRR_BANDINDICATOR_ENUM
{
    LRRC_GRR_BANDINDICATOR_DCS1800                          = 0,
    LRRC_GRR_BANDINDICATOR_PCS1900                             ,

    LRRC_GRR_BANDINDICATOR_BUTT
};
typedef VOS_UINT16    LRRC_GRR_BANDINDICATOR_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM
 Э����  :
 ASN.1����   :
 ö��˵��  : С��פ����ʽ
*****************************************************************************/
enum LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM
{
    LRRC_GURRC_CELL_CAMPEDON_SUITABLE                       = 0,                /* С��פ���ڷ�ʽΪsuitable   */
    LRRC_GURRC_CELL_CAMPEDON_ANY_CELL                          ,                /* С��פ���ڷ�ʽΪacceptable */

    LRRC_GURRC_CELL_CAMPEDON_TYPE_BUTT
};

typedef VOS_UINT8 LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_GRR_RELALL_REASON_ENUM_UINT8
 Э����  :
 ASN.1����   :
 ö��˵��  : LRRC�ͷ�ԭ��
*****************************************************************************/
enum LRRC_GRR_RELALL_REASON_ENUM
{
    LRRC_GRR_REL_REASON_OTHER                             = 0,
    LRRC_GRR_REL_REASON_TO_GSM                               ,                  /* LTE�ͷŵ�ԭ��ΪLTE�л�����CCO��GSM */

    LRRC_GRR_REL_REASON_BUTT
};
typedef VOS_UINT8 LRRC_GRR_RELALL_REASON_ENUM_UINT8;


/*****************************************************************************
 ö����     :LRRC_GURRC_VALID_FLAG_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ͨ���Ƿ���ڱ�־
*****************************************************************************/
enum LRRC_GURRC_VALID_FLAG_ENUM
{
    LRRC_GURRC_FLAG_INVALID                                 = 0,
    LRRC_GURRC_FLAG_VALID                                      ,

    LRRC_GURRC_FLAG_BUTT
};
typedef VOS_UINT8    LRRC_GURRC_VALID_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_GURRC_CELL_RESEL_RESULT_ENUM
 Э����  :
	 44060-8.4.2
	 Access is denied in the new cell (i.e., the mobile station receives an
	 IMMEDIATE ASSIGNMENT REJECT, a PACKET ASSIGNMENT REJECT or, in a UTRAN
	 cell, an RRC CONNECTION REJECT message or fails to establish an RRC
	 connection in an E-UTRAN cell as specified in 3GPP TS 36.331).
	 Cause: "Immediate Assign Reject or Packet Access Reject on target cell";
 ASN.1���� :
 ö��˵��  : GU��LTE֮��CELL RESEL���
*****************************************************************************/
enum LRRC_GURRC_CELL_RESEL_RESULT_ENUM
{
    LRRC_GURRC_CELL_RESEL_SUCC                              = 0,
    LRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL                         ,                /* ϵͳ��Ϣ����ʧ�� */
    LRRC_GURRC_CELL_RESEL_CELL_BARRED                          ,                /* CELL BARRED */
    LRRC_GURRC_CELL_RESEL_CELL_FORBID                          ,                /* CELL �� FORBID*/
    LRRC_GURRC_CELL_RESEL_NOT_EPLMNS                           ,                /* CELLЯ����PLMN��Ϣû������RPLMN��EPLMNS */
    LRRC_GURRC_CELL_RESEL_ACCESS                               ,                /* CELL ACCESS ���� */
    LRRC_GURRC_CELL_RESEL_UNSPECIFIC                           ,                /* ����δ����Ĵ��� */
    LRRC_GURRC_CELL_RESEL_CONNECTION_REJECT                    ,                /* ����ָ�ɱ��ܻ����ӱ��ܣ���ԭ��ֵֻ����CCO���� */

    LRRC_GURRC_CELL_RESEL_S_OR_C1_CHECK_FAIL                   ,
    /* add for MFBI begin */
    LRRC_GURRC_CELL_RESEL_ARFCN_NOT_SUPPORT                    ,
    /* add for MFBI end */

    LRRC_GURRC_CELL_RESEL_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32;

/* CCOʧ��ԭ��ͬ CEL RESEL ���� */
typedef VOS_UINT32 LRRC_GURRC_CCO_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_HANDOVER_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��HANDOVER ���
*****************************************************************************/
enum LRRC_GURRC_HANDOVER_RESULT_ENUM
{
    LRRC_GURRC_HANDOVER_RESULT_SUCC                         = 0,
    LRRC_GURRC_HANDOVER_RESULT_CONF_UNACCEPTABLE               ,                /* �л����ò�֧�� */
    LRRC_GURRC_HANDOVER_RESULT_PHY_CHANNEL_FAIL                ,                /* physical channel failure  */
    LRRC_GURRC_HANDOVER_RESULT_IRAT_PROTOCOL_ERR               ,                /* inter-RAT protocol error */
    LRRC_GURRC_HANDOVER_RESULT_UNSPECIFIC,

    /* add for MFBI begin */
    LRRC_GURRC_HANDOVER_RESULT_ARFCN_NOT_SUPPORT               ,
    /* add for MFBI end */

    LRRC_GURRC_HANDOVER_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_CELL_RESEL_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��REDIRECTED���
*****************************************************************************/
enum LRRC_GURRC_REDIRECTED_RESULT_ENUM
{
    LRRC_GURRC_REDIRECTED_SUCC                              = 0,
    LRRC_GURRC_REDIRECTED_FAIL                                 ,

    /* add for MFBI begin */
    LRRC_GURRC_REDIRECTED_ARFCN_NOT_SUPPORT                    ,
    /* add for MFBI end */

    LRRC_GURRC_REDIRECTED_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GRR_SYS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CCO�������У�ָʾ�Ƿ����GERANϵͳ��Ϣ
*****************************************************************************/
enum LRRC_GRR_SYS_TYPE_ENUM
{
    LRRC_GRR_SYS_TYPE_NOT_EXIST                             = 0,
    LRRC_GRR_SYS_TYPE_SI                                       ,
    LRRC_GRR_SYS_TYPE_PSI                                      ,

    LRRC_GRR_SYS_TYPE_BUTT
};

typedef VOS_UINT8   LRRC_GRR_SYS_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_GURRC_SET_DSP_POWER_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮������DSPʡ��ģʽ����
*****************************************************************************/
enum LRRC_GURRC_SET_DSP_POWER_CMD_ENUM
{
    LRRC_GURRC_SET_DSP_POWER_OPEN                           = 0,
    LRRC_GURRC_SET_DSP_POWER_CLOSE                             ,

    LRRC_GURRC_SET_DSP_POWER_TYPE_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮������DSPʡ��ģʽ���
*****************************************************************************/
enum LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM
{
    LRRC_GURRC_SET_DSP_POWER_SUCC                           = 0,
    LRRC_GURRC_SET_DSP_POWER_FAIL                              ,

    LRRC_GURRC_SET_DSP_POWER_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE PLMN�������
*****************************************************************************/
enum LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM
{
    LRRC_WRRC_PLMN_SEARCH_SUCC                              = 0,
    LRRC_WRRC_PLMN_SEARCH_FAIL                                 ,

    LRRC_WRRC_PLMN_SEARCH_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_MEAS_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��MEAS ����
*****************************************************************************/
enum LRRC_GURRC_MEAS_CMD_ENUM
{
    LRRC_GURRC_MEAS_CMD_RELEASE                             = 0,
    LRRC_GURRC_MEAS_CMD_SETUP                                  ,

    LRRC_GURRC_MEAS_CMD_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_MEAS_CMD_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_MEAS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��MEAS CMD ���
*****************************************************************************/
enum LRRC_GURRC_MEAS_RESULT_ENUM
{
    LRRC_GURRC_MEAS_RESULT_SUCC                             = 0,
    LRRC_GURRC_MEAS_RESULT_FAIL                                ,

    /* add for MFBI begin */
    LRRC_GURRC_MEAS_RESULT_ARFCN_NOT_SUPPORT                   ,
    /* add for MFBI end */

    LRRC_GURRC_MEAS_RESULT_BUTT
};

typedef VOS_UINT32  LRRC_GURRC_MEAS_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_GET_UECAP_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��UE CAP��ȡ���
*****************************************************************************/
enum LRRC_GURRC_GET_UECAP_RESULT_ENUM
{
    LRRC_GURRC_GET_UECAP_SUCC                               = 0,
    LRRC_GURRC_GET_UECAP_FAIL                                  ,

    LRRC_GURRC_GET_UECAP_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_MEAS_IRAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��IRAT����
*****************************************************************************/
enum LRRC_GURRC_MEAS_IRAT_TYPE_ENUM
{
    LRRC_GURRC_MEAS_IRAT_TYPE_GERAN                         = 0,
    LRRC_GURRC_MEAS_IRAT_TYPE_UTRAN                            ,

    LRRC_GURRC_MEAS_IRAT_TYPE_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_MEAS_IRAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_WRRC_STATE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : WRRC��ǰ��״̬���ͣ�������������̬������������
                            CELL_PCH/URA_PCH: WRRCָʾERRC ����IDLE̬����
                            CELL_FACH/CELL_DCH: WRRCָʾERRC ��������̬����
*****************************************************************************/
enum LRRC_WRRC_STATE_TYPE_ENUM
{
    LRRC_WRRC_STATE_TYPE_CELL_PCH                           = 0,
    LRRC_WRRC_STATE_TYPE_URA_PCH                               ,
    LRRC_WRRC_STATE_TYPE_CELL_FACH                             ,
    LRRC_WRRC_STATE_TYPE_CELL_DCH                              ,

    LRRC_WRRC_STATE_TYPE_BUTT
};

typedef VOS_UINT16 LRRC_WRRC_STATE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_VERIFY_TIME_INDEX_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LRRC֪ͨGURRC��GSM BSIC��ʼȷ�Ϻ���ȷ�ϵ�ʱ������

 ����̬����ȡֵ����:

    index  Number of carriers  Tidentify,gsm  Treconfirm,gsm  Gap configuration
            other than GSM         (ms)            (ms)
   -----------------------------------------------------------------------------
     0            0               2160           1920
     1            1               5280           5040
     2            2               5280           5040            40ms (ID 0)
     3            3               19440          13320
     4            4               31680          29280
     5            5               31680          29280
   -----------------------------------------------------------------------------
     6            0               5280           5040
     7            1               21760          17280           80ms (ID 1)
     8            2               31680          29280

����̬����ȡֵ����:

    index  DRX cycle length  Tidentify,gsm
                 (s)              (ms)
   ------------------------------------------
     0           0.32             360
     1           0.64             360
     2           1.28             180
     3           2.56             180

*****************************************************************************/

enum LRRC_GRR_VERIFY_TIME_INDEX_ENUM
{
    LRRC_GRR_VERIFY_TIME_INDEX_0                          = 0,
    LRRC_GRR_VERIFY_TIME_INDEX_1                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_2                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_3                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_4                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_5                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_6                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_7                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_8                             ,

    LRRC_GRR_VERIFY_TIME_INDEX_BUTT
};

typedef VOS_UINT16 LRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_GURRC_LOAD_DSP_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE����WDSP���
*****************************************************************************/
enum LRRC_GURRC_LOAD_DSP_RESULT_ENUM
{
    LRRC_GURRC_LOAD_DSP_RESULT_SUCC                         = 0,
    LRRC_GURRC_LOAD_DSP_RESULT_FAIL                            ,

    LRRC_GURRC_LOAD_DSP_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_LOAD_DSP_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_GET_CGI_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��CGI��ȡ���
*****************************************************************************/
enum LRRC_GURRC_GET_CGI_RESULT_ENUM
{
    LRRC_GURRC_GET_CGI_RESULT_SUCC                          = 0,
    LRRC_GURRC_GET_CGI_RESULT_FAIL                             ,

    LRRC_GURRC_GET_CGI_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_GURRC_BG_SEARCH_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮��BG�������
*****************************************************************************/
enum LRRC_GURRC_BG_SEARCH_RESULT_ENUM
{
    LRRC_GURRC_BG_SEARCH_RESULT_SUCC                        = 0,
    LRRC_GURRC_BG_SEARCH_RESULT_FAIL                           ,
    LRRC_GURRC_BG_SEARCH_RESULT_ABNORMAL                       ,

    LRRC_GURRC_BG_SEARCH_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_SEARCH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ָʾ�������ͣ���BG����PLMN LIST
*****************************************************************************/
enum LRRC_GURRC_SEARCH_TYPE_ENUM
{
    LRRC_GURRC_SEARCH_TYPE_BG                 = 0,                                    /* ֪ͨ�������� */
    LRRC_GURRC_SEARCH_TYPE_PLMN_LIST             ,                                    /* ֪ͨ��PLMN LIST��  */
    LRRC_GURRC_SEARCH_TYPE_BG_HIGH_RAT           ,
    LRRC_GURRC_SEARCH_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8;

/* CMCC-BEGIN */
/*****************************************************************************
 ö����    : LRRC_GURRC_REDIR_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ض������ͣ�����������Ƶġ�UE����ִ�е�
*****************************************************************************/
enum LRRC_GURRC_REDIR_TYPE_ENUM
{
    LRRC_GURRC_REDIR_TYPE_UE_AUTO                         = 0,
    LRRC_GURRC_REDIR_TYPE_NET_CTL                            ,
    LRRC_GURRC_REDIR_TYPE_BUTT
};

typedef VOS_UINT8 LRRC_GURRC_REDIR_TYPE_ENUM_UINT8;
/* CMCC-END */


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :LRRC_GRR_BSIC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :CELL BAIC Info��Э��36331 6.3.4
            usNcc(GSM Network Colour Code)  ������Χ:(0..7), 8 ��ʾ��Чֵ
            usBcc(GSM Base Station Colour Code)  ������Χ:(0..7) , 8 ��ʾ��Чֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNcc;
    VOS_UINT16                                              usBcc;
}LRRC_GRR_BSIC_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_LTE_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LTE���ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* ȡֵ��Χ0~9,0��ʾ���ȼ���ͣ�9��ʾ���ȼ���ߣ�����1~8��ӦЭ���ϵ�0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}LRRC_GURRC_LTE_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LTEר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_LTE_PRI_INFO_STRU                            astLteDPriInfo[LRRC_GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM];
}LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_UTRAN_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :UTRAN���ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* ȡֵ��Χ0~9,0��ʾ���ȼ���ͣ�9��ʾ���ȼ���ߣ�����1~8��ӦЭ���ϵ�0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}LRRC_GURRC_UTRAN_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :UTRANר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_UTRAN_PRI_INFO_STRU                          astUtranDPriInfo[LRRC_GURRC_UTRAN_DEDICATED_PRI_MAX_NUM];
}LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_GERAN_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :2G���ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;

    /* ȡֵ��Χ0~9,0��ʾ���ȼ���ͣ�9��ʾ���ȼ���ߣ�����1~8��ӦЭ���ϵ�0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[3];
}LRRC_GURRC_GERAN_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :2Gר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_GERAN_PRI_INFO_STRU                          astGeranDPriInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :ר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    /**************************************************************************
     bitLteDPriInfoPresent: ��ʾstLteDPriInfo�Ƿ���Ч��1��ʾ��Ч��0��ʾ��Ч
     bitUtranDPriInfoPresent: ��ʾstUtranDPriInfo�Ƿ���Ч��1��ʾ��Ч��0��ʾ��Ч
     bitGeranDPriInfoPresent: ��ʾstGeranDPriInfo�Ƿ���Ч��1��ʾ��Ч��0��ʾ��Ч
     bitDPriTimerPresent: ��ʾulTimerValue�Ƿ���Ч��1��ʾ��Ч��0��ʾ��Ч
    **************************************************************************/

    VOS_UINT32                                              bitLteDPriInfoPresent  : 1;
    VOS_UINT32                                              bitUtranDPriInfoPresent: 1;
    VOS_UINT32                                              bitGeranDPriInfoPresent: 1;
    VOS_UINT32                                              bitDPriTimerPresent    : 1;  /* bitΪ0ʱ��ʾ����ʱ�� */
    VOS_UINT32                                              bitSpare               : 28;

    /* EUTRAN Ƶ�����ȼ���Ϣ */
    LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU                  stLteDPriInfo;

    /* URTAN Ƶ�����ȼ���Ϣ */
    LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU                stUtranDPriInfo;

    /* GSM Ƶ�����ȼ���Ϣ */
    LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU                stGeranDPriInfo;

    /* T3230,T322 ,T320��ʱ��ʵ��ʣ��ʱ������λ������,
            ���T3230,T322 ,T320��ʱ�������ڣ���ʾ���������޴� */
    VOS_UINT32                                              ulTimerValue;
}LRRC_GURRC_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_PLMN_ID_INFO_STRU
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
}LRRC_GURRC_PLMN_ID_INFO_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_PLMN_ID_INFO_LIST_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :ϵͳ��Ϣ��Я����PLMN��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnIdNum;
    LRRC_GURRC_PLMN_ID_INFO_STRU                            astPlmnIdInfo[LRRC_GURRC_PLMN_ID_MAX_NUM];
}LRRC_GURRC_PLMN_ID_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GRR_GERAN_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :2GС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;
    LRRC_GRR_BSIC_INFO_STRU                                 stBsic;
}LRRC_GRR_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRR����̬�²�����GERAN CELL �����Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;

    /* GĿ��С��������ƽֵ,������ʽ������޷���ȡ����ΪԼ������Чֵ��HOʱ��ʹ�á�*/
    VOS_INT16                                               sGeranCellRxlev;

    VOS_UINT8                                               aucReserved[1];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enFNOffsetTAPresent; /* GС����ʱ��Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    VOS_INT32                                               lFNOffset;
    VOS_UINT32                                              ulTimeAlignmt;
}LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GRR_SAVE_GERAN_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����GRR����̬�²�����GERAN CELL �����Ϣ�б�ֻЯ���Ѿ���֤
             �ɹ���GС�������Ϣ
*****************************************************************************/
typedef struct
{
    /* GSMС������ */
    VOS_UINT32                                              ulGsmCellNum;
    LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU                      astRrcSaveCellInfoForGas[LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM];
}LRRC_GRR_SAVE_GERAN_CELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_LRRC_EUTRAN_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :EUTRAN Ƶ����Ϣ
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;
   LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                   enMeasband;         /*  �տڲ�Я��,��дĬ��ֵ 0 */

   VOS_UINT8                                                aucReserved[3];

   /* �տ���Ϣ��Я����ÿ��Ƶ���Ӧ�ĺ�������Ϣ*/
   VOS_UINT8                                                ucBlackListCnt;
   VOS_UINT16                                               ausBlackCellidList[LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM];
}GURRC_LRRC_EUTRAN_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_LRRC_EUTRAN_INFO_LIST_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :EUTRAN Ƶ����Ϣ�б�
*****************************************************************************/
typedef struct
{
   /* ��Ҫ������Ƶ����� */
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   Ƶ����Ϣ�и����ȼ�Ƶ����������usArfcnNum =  usHighPriNum��
   ��ʾ����ֻ�и����ȼ�Ƶ�㣬��ǰ״̬���������ȼ�
   astEutranInfo���˳��Ϊ:�����ȼ���Ϣ -> �����ȼ���Ϣ -> �����ȼ���Ϣ
   ****************************************************************************/
   VOS_UINT16                                               usHighPriNum;
   GURRC_LRRC_EUTRAN_INFO_STRU                              astEutranInfo[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}GURRC_LRRC_EUTRAN_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usCellId;
    VOS_INT16                                               sRsrp;              /* RSRP����ֵ,ȡֵ��Χ[-141*8,-44*8]�� ��λ:dBm������ 1/8  */
    VOS_INT16                                               sRsrq;              /* RSRQ����ֵ ,ȡֵ��Χ[-40*4��-6*4]�� ��λ:dB�� ���� 1/8  */
    VOS_INT16                                               sRssi;              /* RSSI����ֵ ,ȡֵ��Χ[-110*8,-20*8], ��λ:dBm������ 1/8  */
}LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LTE Ƶ��С���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usArfcnCellNum;
    LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU                 astInterFreqMeasResult[LRRC_GURRC_MAX_LTE_CELL_PER_FREQ_NUM];
}LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :EUTRAN ������Ϣ
*****************************************************************************/
typedef struct
{
   /* �Ѿ����������ݵ�Ƶ������ */
   VOS_UINT16                                               usArfcnNum;
   VOS_UINT8                                                aucReserved[2];

   LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU           astEutranMeasResultInfo[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GURRC_CELL_GLOBAL_ID_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :  UTRAN/EUTRAN CELL GLOBAL ID��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stPlmnId;
    VOS_UINT32                                              ulCellId;
}LRRC_GURRC_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_FORB_LA_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :

*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                 PlmnId;                        /* PlMN��ʶ       */
    VOS_UINT32                                   ulForbLac;                     /* ��ֹע������Ϣ */
}LRRC_GURRC_FORB_LA_STRU;

/*****************************************************************************
 �ṹ��     :LRRC_GURRC_UTRAN_CELL_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GERAN��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;
   LRRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
}LRRC_GURRC_GERAN_CELL_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GURRC_LOW_PLMN_ID_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  �����ȼ�plmn���ݽṹ������plmn��Ϣ��RSRP����ֵ
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stLowPlmnId;
    VOS_INT32                                               lRsrp;
}LRRC_GURRC_LOW_PLMN_ID_INFO_STRU;

/*****************************************************************************
 �ṹ��    :    LRRC_GURRC_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  suitable Plmn ����ʧ�ܣ�LRRC����WRRC PLMN SEARCH ���
*****************************************************************************/
typedef struct
{
    /* ������PLMN�ĸ��� */
    VOS_UINT32                                              ulHighPlmnNum;
    LRRC_GURRC_PLMN_ID_INFO_STRU                            astHighPlmnList[LRRC_GURRC_MAX_HIGH_PLMN_NUM];

    /* ������PLMN�ĸ��� */
    VOS_UINT32                                              ulLowPlmnNum;
    LRRC_GURRC_LOW_PLMN_ID_INFO_STRU                        astLowPlmnList[LRRC_GURRC_MAX_LOW_PLMN_NUM];
}LRRC_GURRC_PLMN_ID_LIST_STRU;

/* CMCC-BEGIN */
/*****************************************************************************
 �ṹ��    : LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE���ر������ʷƵ���б���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    VOS_UINT16                                              ausArfcn[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU;
/* CMCC-END */

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

#endif /* end of LRRC_GURRCCommInterface.h */
