/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : lt_nv_common_interface.h
  �� �� ��   : ����
  ��    ��   : wangxu
  ��������   : 2014��3��13��
  ����޸�   :
  ��������   : TL ����NV����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��3��13��
    ��    ��   : wangxu
    �޸�����   : �����ļ�
--------------------------------------------------------------------------------


******************************************************************************/


#ifndef __LT_NV_COMMON_INTERFACE_H__
#define __LT_NV_COMMON_INTERFACE_H__
#include "TLPhyInterface.h"
#include "LNvCommon.h"/*alex nv write*/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/
#define TL_DCXO_POLY_COEF_NUM									(4)
#define TL_DCXO_TEMP_AFC_MAX_NUM          						(144)
#define TL_DCXO_UNITARY_TEMP									(250)
#define TL_DCXO_POLY_COEF_DEFAULT_A0_MANTISSA					(0)
#define TL_DCXO_POLY_COEF_DEFAULT_A0_EXP						(0)
#define TL_DCXO_POLY_COEF_DEFAULT_A1_MANTISSA					(1920998616)
#define TL_DCXO_POLY_COEF_DEFAULT_A1_EXP						(49154)
#define TL_DCXO_POLY_COEF_DEFAULT_A2_MANTISSA					(144403660)
#define TL_DCXO_POLY_COEF_DEFAULT_A2_EXP						(16379)
#define TL_DCXO_POLY_COEF_DEFAULT_A3_MANTISSA					(3271384601)
#define TL_DCXO_POLY_COEF_DEFAULT_A3_EXP						(16369)


/************************************************************
                               ö�ٶ���
************************************************************/


/************************************************************
                             ���ݽṹ����
************************************************************/
/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DCXO����ʽ�� 4��ϵ�����¶ȵ������Сֵ
*****************************************************************************/
typedef struct
{
	UINT32							aulMantissaDefault[TL_DCXO_POLY_COEF_NUM];  /* ���δ��a0,a1,a2,a3��β�� */
	UINT16							ausExponentDefault[TL_DCXO_POLY_COEF_NUM]; /* ���δ��a0,a1,a2,a3��ָ�� */
	INT16							sTmax;								/* �����¶����ֵ */
	INT16							sTmin;								/* �����¶���Сֵ */
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU;

enum TLCOMM_NV_32K_TYPE_ENUM
{
    TLCOMM_NV_32K_TYPE_32000            = 0,        /*32kʱ�Ӹ���32000*/
    TLCOMM_NV_32K_TYPE_32764            = 1,        /*32kʱ�Ӹ���32764*/
    TLCOMM_NV_32K_TYPE_32768            = 2     /*32kʱ�Ӹ���32768*/
};
typedef UINT16 TLCOMM_NV_32K_TYPE_ENUM_UINT16;

enum TLCOMM_NV_SINGLE_XO_TYPE_ENUM
{
    TLCOMM_NV_SINGLE_XO_TYPE_UNSUPPORT    = 0,                                    /* ��֧�ֵ�ʱ�� */                                                           /* ���н�����DPCH */
    TLCOMM_NV_SINGLE_XO_TYPE_TCXO         = 1,                                    /* ��TCXO */                                                           /* ���д���RACH */
    TLCOMM_NV_SINGLE_XO_TYPE_DCXO         = 2,                                    /* ��DCXO */
    TLCOMM_NV_SINGLE_XO_TYPE_BUTT
};
typedef UINT16 TLCOMM_NV_SINGLE_XO_TYPE_ENUM_UINT16;

typedef struct
{
    TLCOMM_NV_SINGLE_XO_TYPE_ENUM_UINT16 enSingleXoType;                    /*��ʱ������*/
    TLCOMM_NV_32K_TYPE_ENUM_UINT16       en32kType;                         /*32kʱ��Ƶ������*/
}TLCOMM_NV_SINGLE_XO_DEFINE_STRU;

/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���һ��DCXO���¶�-Ƶ��(ʵ��ΪAFC����ֵ)����
*****************************************************************************/
typedef struct
{
    INT16                           sTemp;                                /* �¶� */
    INT16                           sFreqPpm;                             /* �����¶��¶�Ӧ�����Ƶƫ */
}TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU;


/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO��ȡ�¶ȵ�����,����IDLE̬��DCH̬
*****************************************************************************/
typedef struct
{
    UINT16                          usIdlePeriod;                          /* IDLE̬�¶�ȡ���� */
    UINT16                          usConnPeriod;                          /* CONN̬�¶�ȡ���� */
}TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU;


/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO����ʽϵ����������
*****************************************************************************/
typedef struct
{
    UINT8   ucMinSampleNum;
    UINT8   ucMaxSampleNUm;
    UINT8   ucSampleInStep;
    UINT8   ucAgingThr;
    UINT16  usSampleInThr;
    INT16   sCoefVerifyTemp;
}TLCOMM_NV_DCXO_TEMP_CTRL_THR_ONE_AREA_STRU;
typedef struct
{
    INT16                                 sMinTemp;
    INT16                                 sMaxTemp;
    INT16                                 sLowestHighTempAreaThr;
    INT16                                 sHighestLowTempAreaThr;
	TLCOMM_NV_DCXO_TEMP_CTRL_THR_ONE_AREA_STRU astTempCtrlOneArea[3];
}TLCOMM_NV_DCXO_TEMP_CTRL_THR_STRU;
/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO����ʽϵ����������
*****************************************************************************/
typedef struct
{
    UINT32                          aulLowMantissa[TL_DCXO_POLY_COEF_NUM];
    UINT16                          ausLowExponent[TL_DCXO_POLY_COEF_NUM];
    UINT32                          aulHighMantissa[TL_DCXO_POLY_COEF_NUM];
    UINT16                          ausHighExponent[TL_DCXO_POLY_COEF_NUM];
    TLCOMM_NV_DCXO_TEMP_CTRL_THR_STRU stTempCtrlThr;
}TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���DCXO���¶�-Ƶ��(ʵ��ΪAFC����ֵ)��������
*****************************************************************************/
#if 0
typedef struct
{
    UINT32                          uwValidNum;                             /* ��������Ч���� */
    INT16                           shwTmax;                                /* �����¶����ֵ */
    INT16                           shwTmin;                                /* �����¶���Сֵ */
    TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU astAfcTempValue[TL_DCXO_TEMP_AFC_MAX_NUM]; /* �������� */
}TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;
#endif

#define TL_DCXO_TEMP_AFC_ONE_AREA_MAX_NUM                           (40)
typedef struct
{
    INT16                           sTemp;                                /* �¶� 0.1*/
    INT16                           sFreqPpm;                             /* �����¶��¶�Ӧ�����Ƶƫ */
}TLCOMM_NV_DCXO_T2F_SAMPLE_STRU;

typedef struct
{
    UINT8   ucValidNum;
    UINT8   ucWriteIdx;
    UINT8   ucMinSampleNum;
    UINT8   ucMaxSampleNUm;
    UINT8   ucSampleInStep;
    UINT8   ucRsv;
    UINT16  usSampleInThr;
    INT16   sCoefVerifyTemp;
    INT16   sRsv;
    TLCOMM_NV_DCXO_T2F_SAMPLE_STRU astSample[TL_DCXO_TEMP_AFC_ONE_AREA_MAX_NUM];
}TLCOMM_NV_DCXO_T2F_ONE_TEMP_AREA_STRU;


#define TLCOMM_NV_DCXO_T2F_LOW_TEMP_AREA_IDX     (0)                                    /* ������ */
#define TLCOMM_NV_DCXO_T2F_MID_TEMP_AREA_IDX     (1)                                    /* ������ */
#define TLCOMM_NV_DCXO_T2F_HIGH_TEMP_AREA_IDX    (2)                                   /* ������ */
#define TLCOMM_NV_DCXO_T2F_TEMP_AREA_IDX_BUTT    (3)

typedef struct
{
    INT16                                 sMinTemp;
    INT16                                 sMaxTemp;
    INT16                                 sLowestHighTempAreaThr;
    INT16                                 sHighestLowTempAreaThr;
    TLCOMM_NV_DCXO_T2F_ONE_TEMP_AREA_STRU astTempArea[TLCOMM_NV_DCXO_T2F_TEMP_AREA_IDX_BUTT];
}TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;
/*end*/

typedef struct
{
    UINT32                                      ulCoefValid;                /*�����У׼ϵ���Ƿ���Ч*/
    TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU     stCoef;                     /*��ֵ3�η�����ϵ��*/
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_STRU;

typedef struct
{
    TLCOMM_NV_DCXO_TEMP_COMP_POLY_STRU astcoef[TLCOMM_NV_DCXO_T2F_TEMP_AREA_IDX_BUTT];
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_ALL_STRU;

typedef struct
{
    INT16  sInitCfix;
    UINT16 usFreqErrThreshold;
    UINT16 usCfixLowerLimit;
    UINT16 usCfixUpperLimit;
}NV_DCXO_C_TRIM_DEFAULT;

typedef struct
{
    UINT16 usC2fixLowerLimit;
    UINT16 usC2fixUpperLimit;
    UINT16 usC2fixFactoryCal;
	UINT16 usRsv;
}NV_DCXO_C2_FIX_DEFAULT;

typedef struct
{
    INT16 sInitAfc;
	INT16 sInitTemperature;
}NV_XO_INIT_FREQUENCY;

typedef struct
{
    INT16  sCtrim;
	UINT16 usRsv;
}NV_DCXO_C_TRIM;

typedef struct
{
    INT16  sC2fix;
	UINT16 usRsv;
}NV_DCXO_C2_FIX;

typedef struct
{
	UINT32 ulTLCommNVSize;
}TL_COMM_NV_SIZE_PARA_STRU;

typedef struct
{
	UINT32 ulAgingValid;
    INT32 slAgingValue;
    UINT32 ulRsv;
}TLCOMM_NV_XO_AGING_STRU;

/*****************************************************************************
 �ṹ��    : TLCOMM_NV_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TL ����NV
*****************************************************************************/
typedef struct
{
	TL_COMM_NV_SIZE_PARA_STRU	  stNvSize;
	NV_DCXO_C_TRIM_DEFAULT        stDcxoCTrimdefault;
	NV_DCXO_C2_FIX_DEFAULT        stDcxoC2Fixdefault;
	NV_XO_INIT_FREQUENCY          stXoInitFrequency;
	NV_DCXO_C_TRIM                stDcxoCTrim;
	NV_DCXO_C2_FIX                stDcxoC2Fix;

	TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU stDcxoDefaultPlyCoef;/*DCXO �²�����ʽȱʡϵ��*/
	TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU stDcxoPlyCoefUpdateThr;/*DCXO�²�ϵ��ˢ������*/
	TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU  stDcxoFrqToTempBuffer;/*�¶�ppm����*/
	TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU	stDcxoTempSamplePeriod;/*�¶�Ƶƫ��������*/
	TLCOMM_NV_DCXO_TEMP_COMP_POLY_ALL_STRU  stDcxoCmpPlyCoef;/*DCXO �²�����ʽ����ϵ��*/
    TLCOMM_NV_XO_AGING_STRU                 stXoAgingInfo; /*XO�²��ϻ�NV*/

}TLCOMM_NV_PARA_STRU;

extern TLCOMM_NV_PARA_STRU *gpTLNvCommPara;

/*****************************************************************************
 ö����    : PS_NV_INDEX_ENUM
 ö��˵��  : ����������ͬband�µ���ͬ��NV��
*****************************************************************************/
#if (!defined(TL_PHY_ASIC_K3V5))
enum PS_NV_INDEX_ENUM
{
    NV_IDX_AGC_PARA                     = 0 ,

    NV_IDX_MODEM_LOSS,
    NV_IDX_TEMP_SENSOR,
    NV_IDX_RX_CAL_FREQ_LIST,
    NV_IDX_RX_CHAN0_FREQ_COMP,
    NV_IDX_RX_CHAN1_FREQ_COMP,
    NV_IDX_RX_CHAN2_FREQ_COMP,
    NV_IDX_RX_CHAN3_FREQ_COMP,
    NV_IDX_RX_TEMP_COMP,
    NV_IDX_RX_IP2_CAL_FREQ_LIST,
    NV_IDX_RX_IP2_CAL_THRESHOLD,
    /*NV_IDX_RX_IP2_CAL,*/
    NV_IDX_TX_APC_GAIN_THRESHOLD,
    /*NV_IDX_APC_ATT_TABLE_STRU,*/
    //NV_IDX_TX_CAL_FREQ_LIST,
    //NV_IDX_TX_PA_POWER,
    //NV_IDX_TX_CAL_HIGHGAIN_POWER,
    //NV_IDX_TX_CAL_MIDGAIN_POWER,
    //NV_IDX_TX_CAL_LOWGAIN_POWER,
    //NV_IDX_TX_APC_HIGHGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_MIDGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_LOWGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_TEMP_COMP,
    NV_IDX_TX_APT_PARA,
    NV_IDX_TX_APT_PDM_HIGH_TBL,
    NV_IDX_TX_APT_PDM_MID_TBL,
    NV_IDX_TX_APT_PDM_LOW_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_HIGH_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_MID_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_LOW_TBL,
    /* add by lishangfneg mpr begin */
    NV_IDX_TX_MPR,
    /* add by lishangfneg mpr end */
    NV_IDX_ANT_SAR,
    /*add by chenhongqiang begin*/
    NV_IDX_LTE_TX_ATTEN,
    /*add by chenhongqiang end*/

    NV_IDX_TX_AMPR,

    //NV_IDX_LTE_TX_DIVERSITY_LOSS_COMP,
    NV_IDX_LTE_OTHER_COMP,

    EN_NV_ID_LTE_TX_AMPR_NS05,
    EN_NV_ID_LTE_TX_AMPR_NS09,
    /*add for V9R1_6361 Begin*/
    NV_IDX_IIP2_CAL_TABLE,
    NV_IDX_RF_DCOC_CAL_ANT1,
    NV_IDX_RF_DCOC_CAL_ANT2,
    //NV_IDX_TX_APC_GAIN,
    //NV_IDX_RF_TXIQ_CAL,
    //NV_IDX_TX_RF_BB_ATT,
    //NV_IDX_TX_RF_BIAS,
    //NV_IDX_PA_POWER_DIFFERENCE,
    //NV_IDX_TX_RF_FREQ_COMP_STRU,
    //NV_IDX_TX_PA_TEMP_COMP,
    //NV_IDX_TX_ATTEN_TABLE,
    //NV_IDX_POWERDET_VOLTAGE,
    /*add for V9R1_6361 End*/
    NV_IDX_TX_ET_BAND_PARA,
    NV_IDX_LTE_CAL_PATH_ANT_NUM_PARA,
    NV_IDX_ET_LUT_TBL_LOWCH,
    NV_IDX_ET_LUT_TBL_MIDCH,
    NV_IDX_ET_LUT_TBL_HIGHCH,
    NV_IDX_ET_GAIN_COMP,
    NV_IDX_TX_ET_FINEDLY_PARA,
    NV_IDX_TX_ET_VOFFSET_GAIN,
    NV_IDX_TX_ET_EVDELY,
    NV_IDX_RF_CA_RCCODE_STRU,
    NV_IDX_LTE_TX_UL_ONE_RB_MPR,

    NV_IDX_LTE_TX_PD_PARA,
    NV_IDX_LTE_TX_PD_AUTO_CAL,
    NV_IDX_LTE_TX_PD_PWR_TABLE,
    NV_IDX_LTE_TX_PD_VOLT_TABLE,
    NV_IDX_LTE_TX_PD_TEMPCMP_TABLE,

    //NV_IDX_RX_NOBLK_AGC_SCC_FREQ_COMP_ANT1,
    //NV_IDX_RX_NOBLK_AGC_SCC_FREQ_COMP_ANT2,
    //NV_IDX_RX_BLK_AGC_SCC_FREQ_COMP_ANT1,
    //NV_IDX_RX_BLK_AGC_SCC_FREQ_COMP_ANT2,
    NV_IDX_DPDT_ANT_SAR,
    EN_IDX_NV_ID_FTM_CAND_CELL_LIST,
    NV_IDX_LTE_TX_CAL_LIST_STRU,
    NV_IDX_LTE_APC_TABLE_STRU,
    NV_IDX_LTE_TX_FILTER_CMP_STRU,
    NV_IDX_LTE_DEFAULT_POW_TABLE_STRU,
    NV_IDX_LTE_TX_CAL_RESULT_TABLE_STRU,
    NV_IDX_LTE_RF_TXIQ_CAL_STRU,
    NV_IDX_LTE_HD3_CAL_PARA_STRU,
    NV_IDX_LTE_HD3_CAL_RSULT_STRU,
    NV_IDX_TX_RF_FREQ_COMP_STRU,
    NV_IDX_TX_PA_TEMP_COMP,
    NV_IDX_LTE_TX_AMPR_NS03,
    NV_IDX_LTE_TX_AMPR_NS22,
    PS_NV_IDX_BUTT
};
#else
enum PS_NV_INDEX_ENUM
{
    NV_IDX_AGC_PARA                     = 0 ,

    NV_IDX_MODEM_LOSS,
    NV_IDX_TEMP_SENSOR,
    NV_IDX_RX_CAL_FREQ_LIST,
    NV_IDX_RX_NOBLK_AGC_FREQ_COMP_ANT1,
    NV_IDX_RX_NOBLK_AGC_FREQ_COMP_ANT2,
    NV_IDX_RX_BLK_AGC_FREQ_COMP_ANT1,
    NV_IDX_RX_BLK_AGC_FREQ_COMP_ANT2,
    NV_IDX_RX_TEMP_COMP,
    NV_IDX_RX_IP2_CAL_FREQ_LIST,
    NV_IDX_RX_IP2_CAL_THRESHOLD,
    /*NV_IDX_RX_IP2_CAL,*/
    NV_IDX_TX_APC_GAIN_THRESHOLD,
    /*NV_IDX_APC_ATT_TABLE_STRU,*/
    //NV_IDX_TX_CAL_FREQ_LIST,
    //NV_IDX_TX_PA_POWER,
    //NV_IDX_TX_CAL_HIGHGAIN_POWER,
    //NV_IDX_TX_CAL_MIDGAIN_POWER,
    //NV_IDX_TX_CAL_LOWGAIN_POWER,
    //NV_IDX_TX_APC_HIGHGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_MIDGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_LOWGAIN_FREQ_COMP,
    //NV_IDX_TX_APC_TEMP_COMP,
    NV_IDX_TX_APT_PARA,
    NV_IDX_TX_APT_PDM_HIGH_TBL,
    NV_IDX_TX_APT_PDM_MID_TBL,
    NV_IDX_TX_APT_PDM_LOW_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_HIGH_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_MID_TBL,
    NV_IDX_TX_APT_PDM_MC_COMP_LOW_TBL,
    /* add by lishangfneg mpr begin */
    NV_IDX_TX_MPR,
    /* add by lishangfneg mpr end */
    NV_IDX_ANT_SAR,
    /*add by chenhongqiang begin*/
    NV_IDX_LTE_TX_ATTEN,
    /*add by chenhongqiang end*/

    NV_IDX_TX_AMPR,

    //NV_IDX_LTE_TX_DIVERSITY_LOSS_COMP,
    NV_IDX_LTE_OTHER_COMP,

    EN_NV_ID_LTE_TX_AMPR_NS05,
    EN_NV_ID_LTE_TX_AMPR_NS09,
    /*add for V9R1_6361 Begin*/
    NV_IDX_IIP2_CAL_TABLE,
    NV_IDX_RF_DCOC_CAL_ANT1,
    NV_IDX_RF_DCOC_CAL_ANT2,
    //NV_IDX_TX_APC_GAIN,
    //NV_IDX_RF_TXIQ_CAL,
    //NV_IDX_TX_RF_BB_ATT,
    //NV_IDX_TX_RF_BIAS,
    //NV_IDX_PA_POWER_DIFFERENCE,
    //NV_IDX_TX_RF_FREQ_COMP_STRU,
    //NV_IDX_TX_PA_TEMP_COMP,
    //NV_IDX_TX_ATTEN_TABLE,
    //NV_IDX_POWERDET_VOLTAGE,
    /*add for V9R1_6361 End*/
    NV_IDX_TX_ET_BAND_PARA,
    NV_IDX_ET_LUT_TBL_LOWCH,
    NV_IDX_ET_LUT_TBL_MIDCH,
    NV_IDX_ET_LUT_TBL_HIGHCH,
    NV_IDX_ET_GAIN_COMP,
    NV_IDX_TX_ET_FINEDLY_PARA,
    NV_IDX_TX_ET_VOFFSET_GAIN,
    NV_IDX_TX_ET_EVDELY,
    NV_IDX_RF_CA_RCCODE_STRU,
    NV_IDX_LTE_TX_UL_ONE_RB_MPR,

    NV_IDX_LTE_TX_PD_PARA,
    NV_IDX_LTE_TX_PD_AUTO_CAL,
    NV_IDX_LTE_TX_PD_PWR_TABLE,
    NV_IDX_LTE_TX_PD_VOLT_TABLE,
    NV_IDX_LTE_TX_PD_TEMPCMP_TABLE,

    NV_IDX_RX_NOBLK_AGC_SCC_FREQ_COMP_ANT1,
    NV_IDX_RX_NOBLK_AGC_SCC_FREQ_COMP_ANT2,
    NV_IDX_RX_BLK_AGC_SCC_FREQ_COMP_ANT1,
    NV_IDX_RX_BLK_AGC_SCC_FREQ_COMP_ANT2,
    EN_IDX_NV_ID_FTM_CAND_CELL_LIST,
    EN_IDX_NV_ID_LTE_PA_TEMP_DET_CH,
    NV_IDX_LTE_TX_CAL_LIST_STRU,
    NV_IDX_LTE_APC_TABLE_STRU,
    NV_IDX_LTE_TX_FILTER_CMP_STRU,
    NV_IDX_LTE_DEFAULT_POW_TABLE_STRU,
    NV_IDX_LTE_TX_CAL_RESULT_TABLE_STRU,
    NV_IDX_LTE_RF_TXIQ_CAL_STRU,
    NV_IDX_LTE_HD3_CAL_PARA_STRU,
    NV_IDX_LTE_HD3_CAL_RSULT_STRU,
    NV_IDX_TX_RF_FREQ_COMP_STRU,
    NV_IDX_TX_PA_TEMP_COMP,

    NV_IDX_ETM_ET_APT_LAB,
    NV_IDX_ETM_ET_APT_FAC,
    NV_IDX_DPD_LAB,
    NV_IDX_DPD_FAC,
    NV_IDX_ETM_SEMI_STATIC_MIPI_LAB,
    NV_IDX_ETM_DYNAMIC_MIPI_LAB,
    NV_IDX_DPD_COMP_LAB,
    NV_IDX_DPDT_ANT_SAR,
    NV_IDX_DPD_COMP_FAC,

    PS_NV_IDX_BUTT
};

#endif

typedef VOS_UINT32 PS_NV_INDEX_ENUM_UINT32;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LT_NV_COMMON_INTERFACE_H__ */


