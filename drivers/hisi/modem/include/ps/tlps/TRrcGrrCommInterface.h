/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TRrcGrrCommInterface.h
  Description     : TD&G RRCģ�鹫����Ϣͷ�ļ�
  History         :
      1.xuruimei       2011-10-10   Draft Enact

******************************************************************************/

#ifndef __TRRC_GRRCOMMINTERFACE_H__
#define __TRRC_GRRCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "GUCommInterface.h"

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

/* TDS����GSMС��������� */
#define TRRC_GRR_GERAN_ARFCN_MAX_NUM                        (32)

/* GSM����TDS�ز��ĵ�һ�ز������С���� */
#define TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM                (32)

/* GAS���� TDS����С���б���Ƶ����������ʵ����GAS����·�3������Ƶ�㣬��TD���
��9��Ƶ�㣬������ֵ������ 9 */
#define TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM              (9)

/* TDS ֧������BSIC VERFIED С������*/
#define TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM                (8)

/* TDS��GSM CCO��Ϣ��Я����ϵͳ��Ϣ������ */
#define TRRC_RR_MAX_GERAN_SI_CNT                            (8)

/* TDS��GSM CCO��Ϣ��Я����ϵͳ��Ϣ����ֽ��� */
#define TRRC_RR_MAX_GERAN_SI_LEN                            (23)

/* GERAN CS UE �����������󳤶� */
#define TRRC_GRR_UE_CAP_GEREN_CS_MAX_LEN                    (128)

/* GERAN PS UE �����������󳤶� */
#define TRRC_GRR_UE_CAP_GEREN_PS_MAX_LEN                    (128)

/* TD->G ��������������������PLMN�б� */
#define TRRC_GRR_MAX_AVAIL_PLMN_NUM                         (18)

/* TD->G ��������������G�ظ������PLMN�б� */
#define TRRC_GRR_MAX_HIGH_PLMN_NUM                          (16)                /* ��������PLMN�������� */
#define TRRC_GRR_MAX_LOW_PLMN_NUM                           (16)                /* ��������PLMN�������� */

/* channel release GAS���Я��96��С�� */
#define RR_TRRC_MAX_UTRAN_TDD_CELL_NUM                      (96)

/* INTER_RAT_HANDOVER_INFO ����, �250�ֽ� */
#define RR_TRRC_INTER_RAT_HANDOVER_INFO_LEN                 (250)

/* TD->G cell resel����cell change orderЯ����С����Ϣ���ź�ǿ����Чֵ */
#define RR_TRRC_INVALID_RXLEV                               (0X00FF)

/* G��Ϊ��ģ����Td-scmdaС����TRRC�ϱ��Ĳ��������Чֵ */
#define TRRC_GRR_INVALID_RSCP                               (-131 * 8)

#define TRRC_GRR_INVALID_RSSI                               (-102 * 8)
#define TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM              (9)
#define TRRC_GRR_MAX_FR_FREQ_NUM                            (9)
#define TRRC_GRR_LOWEST_FR_RSCP_THRES                       (-116)
#define TRRC_GRR_HIGHEST_FR_RSCP_THRES                      (-26)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM
 Э����  :
     44060-8.4.2
     Access is denied in the new cell (i.e., the mobile station receives an
     IMMEDIATE ASSIGNMENT REJECT, a PACKET ASSIGNMENT REJECT or, in a UTRAN
     cell, an RRC CONNECTION REJECT message or fails to establish an RRC
     connection in an E-UTRAN cell as specified in 3GPP TS 36.331).
     Cause: "Immediate Assign Reject or Packet Access Reject on target cell";
 ASN.1���� :
 ö��˵��  : GU��TDS֮��CELL RESEL, CCO���
*****************************************************************************/
enum TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM
{
    TRRC_GRR_CELL_RESEL_CCO_SUCC                              = 0,
    TRRC_GRR_CELL_RESEL_CCO_CELL_BARRED                      ,                  /* CELL BARRED */
    TRRC_GRR_CELL_RESEL_CCO_CELL_FORBID                      ,                  /* CELL �� FORBID*/
    TRRC_GRR_CELL_RESEL_CCO_NOT_EPLMNS                       ,                  /* CELLЯ����PLMN��Ϣû������RPLMN��EPLMNS */
    TRRC_GRR_CELL_RESEL_CCO_ACCESS_NOT_PERMIT                ,                  /* CELL ACCESS ���� */
    TRRC_GRR_CELL_RESEL_CCO_CONNECTION_REJECT                ,                  /* ����ָ�ɱ��ܻ����ӱ��ܣ���ԭ��ֵֻ����CCO���� */
    TRRC_GRR_CELL_RESEL_CCO_UNSPECIFIC                       ,                  /* ����δ����Ĵ��� */
    TRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAIL                   ,                  /*��ѡƹ��*/

    TRRC_GRR_CELL_RESEL_CCO_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : TRRC_GRR_REDIRECTED_SUCC
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS��TDS֮��REDIRECTED���
*****************************************************************************/
enum TRRC_GRR_REDIRECTED_RESULT_ENUM
{
    TRRC_GRR_REDIRECTED_SUCC                              = 0,
    TRRC_GRR_REDIRECTED_FAIL                                 ,

    TRRC_GRR_REDIRECTED_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : TRRC_GURRC_HANDOVER_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS��TDS֮��HANDOVER ���
*****************************************************************************/
enum TRRC_GRR_HANDOVER_RESULT_ENUM
{
    TRRC_GRR_HANDOVER_RESULT_SUCC                         = 0,

    /* ����ԭ��ֵ����TDS��GAS�ظ�Handoverʧ��ԭ�� */
    TRRC_GRR_HANDOVER_RESULT_FREQ_NOT_IMPLEMENTED            ,                  /* HO��Ϣ�����˲�֧�ֵ����� */
    TRRC_GRR_HANDOVER_RESULT_CONFIG_UNKNOWN                  ,                  /* HO��Ϣ�������޷��ҵ� */
    TRRC_GRR_HANDOVER_RESULT_INVALID_CONFIG                  ,                  /* HO��Ϣ����Ч������ */
    TRRC_GRR_HANDOVER_RESULT_RRC_CONNECT_FAILURE             ,                  /* HO��ͬ��ʧ�� */

    /* ����ԭ��ֵ����GAS��TDS�ظ�handoverʧ��ԭ�� */
    TRRC_GRR_HANDOVER_RESULT_PROTOCOL_ERROR                  ,                  /* Handover command������쳣 */
    TRRC_GRR_HANDOVER_RESULT_UNSUPORTED_CONFIGURATION        ,                  /* ��֧�ָ�Ƶ��/�Ƿ����� */
    TRRC_GRR_HANDOVER_RESULT_PHY_CHANNEL_FAIL                ,                  /* �����ŵ�����ʧ��  */
    TRRC_GRR_HANDOVER_RESULT_MESSAGE_INVALID                 ,                  /* �л�����Ϣ��Ч */

    TRRC_GRR_HANDOVER_RESULT_UNSPECIFIC,

    TRRC_GRR_HANDOVER_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : TRRC_GRR_VERIFY_TIME_INDEX_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TRR֪ͨGRR��GSM BSIC��ʼȷ�Ϻ���ȷ�ϵ�ʱ������

 ����̬����ȡֵ����:

     index    Tidentify,gsm  Treconfirm,gsm
                  (ms)            (ms)
    ------------------------------------------
      0          5000           5000

����̬����ȡֵ����:

    index  DRX cycle length  Tidentify,gsm
                 (s)              (ms)
   ------------------------------------------
     0           0.08             360
     1           0.16             360
     2           0.32             360
     3           0.64             360
     4           1.28             180
     5           2.56             180
     6           5.12             180

*****************************************************************************/
enum TRRC_GRR_VERIFY_TIME_INDEX_ENUM
{
    TRRC_GRR_VERIFY_TIME_INDEX_0                            = 0,
    TRRC_GRR_VERIFY_TIME_INDEX_1                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_2                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_3                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_4                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_5                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_6                             ,

    TRRC_GRR_VERIFY_TIME_INDEX_BUTT
};
typedef VOS_UINT16 TRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16;

/*****************************************************************************
 ö����    : TRRC_GRR_RESULT_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ͨ�ûظ������־
*****************************************************************************/
enum TRRC_GRR_RESULT_ENUM
{
    TRRC_GRR_RESULT_SUCC                                    = 0,
    TRRC_GRR_RESULT_FAIL                                    ,

    TRRC_GRR_RESULT_BUTT
};
typedef VOS_UINT8    TRRC_GRR_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_GRR_SET_DSP_POWER_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU��LTE֮������DSPʡ��ģʽ����
*****************************************************************************/
enum TRRC_GRR_SET_DSP_POWER_CMD_ENUM
{
    TRRC_GRR_SET_DSP_POWER_OPEN                             = 0,
    TRRC_GRR_SET_DSP_POWER_CLOSE                             ,

    TRRC_GRR_SET_DSP_POWER_TYPE_BUTT
};

typedef VOS_UINT32 TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32;

/*****************************************************************************
 ö����    : TRRC_GRR_SET_DSP_POWER_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : G��TD֮������DSPʡ��ģʽ���
*****************************************************************************/
enum TRRC_GRR_SET_DSP_POWER_RESULT_ENUM
{
    TRRC_GRR_SET_DSP_POWER_SUCC                             = 0,
    TRRC_GRR_SET_DSP_POWER_FAIL                              ,

    TRRC_GRR_SET_DSP_POWER_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : TRRC_GRR_MEAS_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ö��(��������)
*****************************************************************************/
enum TRRC_GRR_MEAS_BAND_WIDTH_ENUM
{
    TRRC_GRR_MEAS_BAND_WIDTH_3840MCPS                       = 0,                /* ����Ϊ3.84 Mcps */
    TRRC_GRR_MEAS_BAND_WIDTH_1280MCPS                       = 1,                /* ����Ϊ1.28 Mcps */

    TRRC_GRR_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 TRRC_GRR_MEAS_BAND_WIDTH_ENUM_UINT8;

/*****************************************************************************
 ö����    : GRR_TRRC_MEAS_GAS_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS��ģ����ʱ��GASĿǰ��״̬����TRRC; �ͷŲ���ʱ, TRRC ����GAS״̬��
*****************************************************************************/
enum GRR_TRRC_MEAS_GAS_STATUS_ENUM
{
    GRR_TRRC_MEAS_GAS_STATUS_IDLE                           = 0,                /* IDLE̬ */
    GRR_TRRC_MEAS_GAS_STATUS_CONNECT                         ,                  /* CONNECT̬ */

    GRR_TRRC_MEAS_GAS_STATUS_BUTT
};
typedef VOS_UINT8 GRR_TRRC_MEAS_GAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_GRR_MEAS_TAS_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TDS��ģ����ʱ��TDSĿǰ��״̬����TRRC
*****************************************************************************/
enum TRRC_GRR_MEAS_TAS_STATUS_ENUM
{
    TRRC_GRR_MEAS_TAS_STATUS_IDLE                           = 0,                /* IDLE̬ */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_PCH                          ,                /* CELL_PCH̬ */
    TRRC_GRR_MEAS_TAS_STATUS_URA_PCH                           ,                /* URA_PCH̬ */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_FACH                         ,                /* CELL_FACH̬ */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_DCH                          ,                /* CELL_DCH̬ */

    TRRC_GRR_MEAS_TAS_STATUS_BUTT
};
typedef VOS_UINT8 TRRC_GRR_MEAS_TAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С��פ����ʽ
*****************************************************************************/
enum TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM
{
    TRRC_GRR_CELL_CAMPEDON_SUITABLE                         = 0,                /* С��פ���ڷ�ʽΪsuitable   */
    TRRC_GRR_CELL_CAMPEDON_ANY_CELL                            ,                /* С��פ���ڷ�ʽΪacceptable */

    TRRC_GRR_CELL_CAMPEDON_TYPE_BUTT
};

typedef VOS_UINT8 TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_GURRC_MEAS_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ָ��
*****************************************************************************/
enum TRRC_GRR_MEAS_CMD_ENUM
{
    TRRC_GRR_MEAS_CMD_ENUM_RELEASE                          = 0,
    TRRC_GRR_MEAS_CMD_ENUM_SETUP                             ,

    TRRC_GRR_MEAS_CMD_ENUM_BUTT
};

typedef VOS_UINT16 TRRC_GRR_MEAS_CMD_ENUM_UINT16;


/*****************************************************************************
 ö����    : TRRC_GRR_RELALL_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TRRC��GRR���͵��ͷ�ԭ��
*****************************************************************************/
enum TRRC_GRR_RELALL_REASON_ENUM
{
    TRRC_GRR_REL_REASON_OTHER                               = 0,
    TRRC_GRR_REL_REASON_TO_GSM                                 ,

    TRRC_GRR_REL_REASON_BUTT
};
typedef VOS_UINT8 TRRC_GRR_RELALL_REASON_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :TRRC_GRR_PLMN_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PLMN ID�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                                              ulMnc;              /* MNC,2 or 3 bytes */
}TRRC_GRR_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    :TRRC_GRR_BSIC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :CELL BSIC Info��Э��36331 6.3.4
            ucNcc(GSM Network Colour Code)  ������Χ:(0..7), 8 ��ʾ��Чֵ
            ucBcc(GSM Base Station Colour Code)  ������Χ:(0..7) , 8 ��ʾ��Чֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNcc;
    VOS_UINT8                                               ucBcc;
    VOS_UINT8                                               aucReserved[2];
}TRRC_GRR_BSIC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CELL_SEL_UTRAN_TDD_CELL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDDС������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* Ƶ�� */
    VOS_UINT16                              usCellParamId;                      /* ���������Чʹ��0xFFFFֵ */
    VOS_UINT8                               ucDiversity;                        /* �ּ�ָʾ TDS: SCTD applied��Ŀǰ��ʹ�ã���GAS����д */
    TRRC_GRR_MEAS_BAND_WIDTH_ENUM_UINT8     enBandWidth;                        /* TDС���ŵ�����,��2��ֵ��Ч��Ĭ��ֵΪTRRC_GRR_MEAS_BAND_WIDTH_3840TCPS */
    VOS_UINT8                               ucSyncCaseTstd;                     /* 3.84 Mcps: Sync case; 1.28 Mcps: TSTD applied��Ŀǰ��ʹ�ã���GAS����д  */
    VOS_UINT8                               aucReserved[1];                     /* 4�ֽڶ��룬���� */
}RRC_CELL_SEL_UTRAN_TDD_CELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_GRR_FAST_RETURN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDD����GSM���ٷ���TDD�Ľṹ
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFRValid;      /* �����ֵΪfalse���ͱ�ʾ��֧��fast return�����ô����������Ϣ */
    VOS_UINT8                           ucFreqNum;

    /* band1:ÿ��Arfcn�ķ�Χ[9400,9499]; band2:ÿ��Arfcn�ķ�Χ[9500,9599]; band3:ÿ��Arfcn�ķ�Χ[10050,10125]; */
    VOS_UINT16                          ausArfcn[TRRC_GRR_MAX_FR_FREQ_NUM];
    VOS_INT16                           sRscpThres;     /* ��Ӧʵ��RSCP�ķ�Χ[-116 ~ -26] */
    VOS_UINT8                           aucReserve[2];
}TRRC_GRR_FAST_RETURN_STRU;
/*׼FR����end*/
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

#endif

