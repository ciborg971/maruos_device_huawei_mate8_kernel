

#ifndef __GUCOMMINTERFACE_H__
#define __GUCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/
#include "PsTypeDef.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨�� 
*****************************************************************************/
/* 3GPP Э���Ϲ涨���EUTRANƵ���� */
#define GURRC_LTE_ARFCN_MAX_NUM                             (8)
    
/* 3GPP Э���Ϲ涨���UTRANƵ���� */
#define GURRC_UTRAN_ARFCN_MAX_NUM                           (16)
    
/* 3GPP Э���Ϲ涨���GERANƵ���� */
#define GURRC_GERAN_ARFCN_MAX_NUM                           (32)

#define RRC_MAX_INTER_GSM_CELL_NUM                          (64)                /* UTRAN��GSM������������ */

#define RRC_MAX_INTER_GSM_MESSAGE_MAXLEN                    (512)               /* �л�ʱ������GSM��Ϣ����󳤶� */
#define RRC_MAX_INTER_GSM_MESSAGE_NUM                       (4)                 /* �л�ʱ������GSM��Ϣ�������Ŀ */
#define GSM_CARRIER_MAXNUM                                  (8)                 /* TRRC/WRRC�����GSMС���������ֵ */

#define GSM_CLASSMARK2_MAX_LEN                              (4)                 /* R6Э����Classmark2��󳤶�,������TRRC��WRR��������IEI */
#define GSM_CLASSMARK3_MAX_LEN                              (32)                /* R8Э����Classmark3��󳤶�,������TRRC��WRR��������IEI */

/* EUTRAN ר�����ȼ������� */
#define GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM                  (64)

/* UTRAN ר�����ȼ������� */
#define GURRC_UTRAN_DEDICATED_PRI_MAX_NUM                   (64)

/*****************************************************************************
  3 ö�ٶ��� 
*****************************************************************************/
/*****************************************************************************
 ö����     :RRC_GRR_BANDINDICATOR_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : 2GС��Ƶ��ָʾ
*****************************************************************************/
enum RRC_GRR_BANDINDICATOR_ENUM
{
    RRC_GRR_BANDINDICATOR_DCS1800       = 0,
    RRC_GRR_BANDINDICATOR_PCS1900       ,

    RRC_GRR_BANDINDICATOR_BUTT
};
typedef VOS_UINT16    RRC_GRR_BANDINDICATOR_ENUM_UINT16;

/*****************************************************************************
 ö����     :GURRC_VALID_FLAG_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ͨ���Ƿ���ڱ�־
*****************************************************************************/
enum GURRC_VALID_FLAG_ENUM
{
    GURRC_FLAG_INVALID                  = 0,
    GURRC_FLAG_VALID                    ,

    GURRC_FLAG_BUTT
};
typedef VOS_UINT8    GURRC_VALID_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����     :RRC_GSM_GERAN_SYS_INFO_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : GSMС��ϵͳ��Ϣ����ö��
*****************************************************************************/
typedef enum
{
    GERAN_SYS_INFO_TYPE_SI              = 0,
    GERAN_SYS_INFO_TYPE_PSI             = 1,
    GERAN_SYS_INFO_TYPE_BUTT
}RRC_GSM_GERAN_SYS_INFO_ENUM;
typedef VOS_UINT8 RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8;

/*****************************************************************************
 ö����     :RRC_GSM_BAND_INDICATOR_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : GSMС��Ƶ��ָʾö��
*****************************************************************************/
typedef enum
{
    EN_DSC_1800_USED                    = 0,
    EN_PDS_1900_USED
}RRC_GSM_BAND_INDICATOR_ENUM;
typedef VOS_UINT32  RRC_GSM_BAND_INDICATOR_ENUM_UINT32;

/*****************************************************************************
 ö����     :RRC_SINGAL_INFO_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ��ϵͳ������ʱЯ������������
*****************************************************************************/
typedef enum
{
    EN_NO_SIG_INF0                              = 0,                            /* ���������� */
    EN_SIG_CS,                                                                  /* ֻ����CS���� */
    EN_SIG_PS,                                                                  /* ֻ����PS���� */
    EN_SIG_CSANDPS                                                              /* ͬʱ����CS��PS���� */
}RRC_SINGAL_INFO_ENUM;
typedef VOS_UINT32  RRC_SINGAL_INFO_ENUM_UINT32;

/*****************************************************************************
 ö����     :RRC_SINGAL_INFO_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : ��ϵͳ������ʱָʾGSM�Ƿ񼤻��˼���
*****************************************************************************/
enum RRC_CIPHER_ACTIVE_ENUM
{
    EN_RRC_CIPHER_INACTIVE              = 0,
    EN_RRC_CIPHER_ACTIVE                = 1,
    EN_RRC_CIPHER_ACTIVE_BUTT
};
typedef VOS_UINT32  RRC_CIPHER_ACTIVE_ENUM_UINT32;

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
/*****************************************************************************
 �ṹ��     :GURRC_LTE_PRI_INFO_STRU
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
}GURRC_LTE_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_LTE_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :LTEר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_LTE_PRI_INFO_STRU                                 astLteDPriInfo[GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM];
}GURRC_LTE_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_UTRAN_PRI_INFO_STRU
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
}GURRC_UTRAN_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_UTRAN_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :UTRANר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_UTRAN_PRI_INFO_STRU                               astUtranDPriInfo[GURRC_UTRAN_DEDICATED_PRI_MAX_NUM];
}GURRC_UTRAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_GERAN_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :2G���ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;

    /* ȡֵ��Χ0~9,0��ʾ���ȼ���ͣ�9��ʾ���ȼ���ߣ�����1~8��ӦЭ���ϵ�0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved2[3];
}GURRC_GERAN_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_GERAN_DEDICATED_PRI_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :2Gר�����ȼ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_GERAN_PRI_INFO_STRU                               astGeranDPriInfo[GURRC_GERAN_ARFCN_MAX_NUM];
}GURRC_GERAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :GURRC_DEDICATED_PRI_INFO_STRU
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
    VOS_UINT32                                              bitDPriTimerPresent    : 1;
    VOS_UINT32                                              bitSpare               : 28;

    /* EUTRAN Ƶ�����ȼ���Ϣ */
    GURRC_LTE_DEDICATED_PRI_INFO_STRU                       stLteDPriInfo;

    /* URTAN Ƶ�����ȼ���Ϣ */
    GURRC_UTRAN_DEDICATED_PRI_INFO_STRU                     stUtranDPriInfo;

    /* GSM Ƶ�����ȼ���Ϣ */
    GURRC_GERAN_DEDICATED_PRI_INFO_STRU                     stGeranDPriInfo;

    /* T3230,T322 ,T320��ʱ��ʵ��ʣ��ʱ������λ������,
            ���T3230,T322 ,T320��ʱ�������ڣ���ʾ���������޴� */
    VOS_UINT32                                              ulTimerValue;
}GURRC_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��     :RRC_SAVE_CELL_INFO_FOR_GAS_ST
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GSMС������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNCC;
    VOS_UINT32                          ulBCC;
    VOS_UINT32                          ulBcchArcfn;
    VOS_UINT32                          ulFreqBandInd;
    VOS_UINT32                          ulFlag;                                 /* �ñ������ָʾlFNOffset��ulTimeAlignmt�Ƿ������ݣ�0:��ʾ������ 1: ��ʾ������*/
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;

    VOS_INT16                           sRxlev;                                 /* GС���źŵ�ƽ����λ��dBm,û�в⵽�źŵ�ƽʱ��ֵΪRRWRR_INVALID_RXLEV */
    VOS_UINT8                           aucReserve1[2];                         /* 4�ֽڶ��룬���� */

}RRC_SAVE_CELL_INFO_FOR_GAS_ST;

/*****************************************************************************
 �ṹ��     :RRC_SAVEINFO_FOR_GAS_ST
 Э����  :
 ASN.1����   :
 �ṹ˵��  :��ϵͳ״̬�±����GSMС���ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGsmCellNum;                           /* GSMС������ */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       RrcSaveCellInfoForGas[GSM_CARRIER_MAXNUM];
}RRC_SAVEINFO_FOR_GAS_ST;

/*****************************************************************************
 �ṹ��     :RRC_GSM_MESSAGE_ST
 Э����  :
 ASN.1����   :
 �ṹ˵��  :�л���GSMС��Я����GSMС����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
     VOS_UINT16                         usBitLength;                            /* �տ���Ϣ��GSM��Ϣ�ĳ���*/
     VOS_UINT8                          aucReserve[2];                         /* 4�ֽڶ��룬���� */
     VOS_UINT8                          aucData[RRC_MAX_INTER_GSM_MESSAGE_MAXLEN];/* �տ���Ϣ��GSM��Ϣ������ */
}RRC_GSM_MESSAGE_ST;

/*****************************************************************************
 �ṹ��     :RRC_HANDOVER_GSM_GPRS_INFO_ST
 Э����  :
 ASN.1����   :
 �ṹ˵��  :�л���GSMС��GPRS��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    RRC_SAVEINFO_FOR_GAS_ST             stRrcSaveInfoForGas;
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enBandIndictor;
    VOS_UINT16                          usMessageNUM;                           /* �տ���Ϣ��GSM��Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve1[2];                         /* 4�ֽڶ��룬���� */
    RRC_GSM_MESSAGE_ST                  stGsmGprsMsg[RRC_MAX_INTER_GSM_MESSAGE_NUM];    
}RRC_HANDOVER_GSM_GPRS_INFO_ST;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/








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

#endif /* end of GUCommInterface.h */
