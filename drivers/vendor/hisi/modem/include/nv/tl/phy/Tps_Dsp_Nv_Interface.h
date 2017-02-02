
#ifndef   __TPS_DSP_NV_INTERFACE_H__
#define   __TPS_DSP_NV_INTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#endif


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/************************************************************
                               �궨��
************************************************************/



/*  NV����ڴ�ZSP ƫ�ڵ�ַ  */

#define TDPHY_NV_ZSP_BASE_ADDR        		 (VOS_UINT32)(0x00027020UL)


/*bzj nv test begin*/
#define RF_INITIAL_REGS_NUM_MAX          28   /*��Ƶ��ʼ���Ĵ������ĸ���
 */
#define RF_SUPPORT_BAND_NUM  	  			     4

#define RF_AGC_TBL_NUM                   10   /*AGC_Table ����
 */
#define RF_APC_TBL_HIGH_NUM              19   /*APC_Table High ����
 */
#define RF_APC_TBL_LOW_NUM               80   /*APC_Table Low ����
 */


#define TDS_BAND_NUM_MAX                 6    /*TDSƵ������
 */
#define TDS_TX_LEVEL_NUM_MAX             3    /*TDS TX��λ����
 */
#define TDS_RX_LEVEL_NUM_MAX             16   /*TDS RX��λ����
 */
#define TDS_TX_CAL_POWERNUM_MAX          80   /*TDS TXУ׼���ʸ���
 */
#define TDS_TX_CAL_FREQNUM_MAX           16   /*TDS TXУ׼Ƶ�����
 */
#define TDS_RX_CAL_FREQNUM_MAX           16   /*TDS RXУ׼Ƶ�����
 */
#define TDS_TEMP_NUM_MAX                 32   /*TDS �¶Ȳ��������
 */


/*begin: add by liuhuashan for DSP NV <2012-06-06>*/
#define TDS_HL1_DSPNV_SUCC   (0)
#define TDS_HL1_DSPNV_FAIL   (1)

extern VOS_UINT8 g_DspNvTest[5000];
#ifndef TDS_RRC_PC_PRJ
#define TDS_DSP_NV_ADDR             (0x1300E040)
#else
#define TDS_DSP_NV_ADDR             (g_DspNvTest)
#endif

#define ADDR_DSP2RF_CFG               (TDS_DSP_NV_ADDR)
#define ADDR_RF_ADVANCE_TIME          (ADDR_DSP2RF_CFG + sizeof(NV_DSP2RF_CFG_STRU))
#define ADDR_RF_AGC_PARA_CODE         (ADDR_RF_ADVANCE_TIME + sizeof(RF_ADVANCE_TIME_STU))
#define ADDR_RF_AGC_PARA_UPTHRGAIN    (ADDR_RF_AGC_PARA_CODE + sizeof(NV_RF_AGC_PARA_STRU))
#define ADDR_RF_AGC_PARA_DOWNTHRGAIN  (ADDR_RF_AGC_PARA_UPTHRGAIN + sizeof(NV_RF_AGC_PARA_STRU))
#define ADDR_RF_AGC_PARA_TOTALGAIN    (ADDR_RF_AGC_PARA_DOWNTHRGAIN + sizeof(NV_RF_AGC_PARA_STRU))
#define ADDR_ACS_PARA                 (ADDR_RF_AGC_PARA_TOTALGAIN + sizeof(NV_RF_AGC_PARA_STRU))
#define ADDR_AGC_CAL_PARA             (ADDR_ACS_PARA + sizeof(NV_RF_ACS_PARA_STRU))
#define ADDR_APC_PARA                 (ADDR_AGC_CAL_PARA + sizeof(NV_RF_AGC_CAL_PARA_STRU))
#define ADDR_MAXPOWER                 (ADDR_APC_PARA + sizeof(NV_RF_APC_PARA_STRU))
#define ADDR_TX_APCOFF_REDUCE         (ADDR_MAXPOWER + sizeof(TDS_NV_MAXPOWER_STRU))
#define ADDR_TX_CAL_FREQ_LIST_0       (ADDR_TX_APCOFF_REDUCE + sizeof(TDS_NV_TX_APCOFF_REDUCE_STRU))
#define ADDR_TX_CAL_FREQ_LIST_1       (ADDR_TX_CAL_FREQ_LIST_0 + sizeof(TDS_NV_TX_CAL_FREQ_LIST_STRU))
#define ADDR_TX_CAL_FREQ_LIST_2       (ADDR_TX_CAL_FREQ_LIST_1 + sizeof(TDS_NV_TX_CAL_FREQ_LIST_STRU))
#define ADDR_RX_CAL_FREQ_LIST_0       (ADDR_TX_CAL_FREQ_LIST_2 + sizeof(TDS_NV_TX_CAL_FREQ_LIST_STRU))
#define ADDR_RX_CAL_FREQ_LIST_1       (ADDR_RX_CAL_FREQ_LIST_0 + sizeof(TDS_NV_RX_CAL_FREQ_LIST_STRU))
#define ADDR_RX_CAL_FREQ_LIST_2       (ADDR_RX_CAL_FREQ_LIST_1 + sizeof(TDS_NV_RX_CAL_FREQ_LIST_STRU))
#define ADDR_TEMP_SEMSOR_0            (ADDR_RX_CAL_FREQ_LIST_2 + sizeof(TDS_NV_RX_CAL_FREQ_LIST_STRU))
#define ADDR_TEMP_SEMSOR_1            (ADDR_TEMP_SEMSOR_0 + sizeof(TDS_NV_TEMP_SEMSOR_STRU))
#define ADDR_TEMP_SEMSOR_2            (ADDR_TEMP_SEMSOR_1 + sizeof(TDS_NV_TEMP_SEMSOR_STRU))
#define ADDR_TX_TEMP_COMP_0           (ADDR_TEMP_SEMSOR_2 + sizeof(TDS_NV_TEMP_SEMSOR_STRU))
#define ADDR_TX_TEMP_COMP_1           (ADDR_TX_TEMP_COMP_0 + sizeof(TDS_NV_TX_TEMP_COMP_STRU))
#define ADDR_TX_TEMP_COMP_2           (ADDR_TX_TEMP_COMP_1 + sizeof(TDS_NV_TX_TEMP_COMP_STRU))
#define ADDR_RX_TEMP_COMP_0           (ADDR_TX_TEMP_COMP_2 + sizeof(TDS_NV_TX_TEMP_COMP_STRU))
#define ADDR_RX_TEMP_COMP_1           (ADDR_RX_TEMP_COMP_0 + sizeof(TDS_NV_RX_TEMP_COMP_STRU))
#define ADDR_RX_TEMP_COMP_2           (ADDR_RX_TEMP_COMP_1 + sizeof(TDS_NV_RX_TEMP_COMP_STRU))
#define ADDR_PA_POWER_0               (ADDR_RX_TEMP_COMP_2 + sizeof(TDS_NV_RX_TEMP_COMP_STRU))
#if 0
#define ADDR_PA_POWER_1               (ADDR_PA_POWER_0 + sizeof(TDS_NV_PA_POWER_STRU))
#define ADDR_PA_POWER_2               (ADDR_PA_POWER_1 + sizeof(TDS_NV_PA_POWER_STRU))
#define ADDR_TX_APC_COMP_0            (ADDR_PA_POWER_2 + sizeof(TDS_NV_PA_POWER_STRU))
#endif
#define ADDR_TX_APC_COMP_1            (ADDR_TX_APC_COMP_0 + sizeof(TDS_NV_TX_APC_COMP_STRU))
#define ADDR_TX_APC_COMP_2            (ADDR_TX_APC_COMP_1 + sizeof(TDS_NV_TX_APC_COMP_STRU))
#define ADDR_TX_APC_FREQ_COMP_0       (ADDR_TX_APC_COMP_2 + sizeof(TDS_NV_TX_APC_COMP_STRU))
#define ADDR_TX_APC_FREQ_COMP_1       (ADDR_TX_APC_FREQ_COMP_0 + sizeof(TDS_NV_TX_APC_FREQ_COMP_STRU))
#define ADDR_TX_APC_FREQ_COMP_2       (ADDR_TX_APC_FREQ_COMP_1 + sizeof(TDS_NV_TX_APC_FREQ_COMP_STRU))
#define ADDR_RX_AGC_COMP_0            (ADDR_TX_APC_FREQ_COMP_2 + sizeof(TDS_NV_TX_APC_FREQ_COMP_STRU))
#define ADDR_RX_AGC_COMP_1            (ADDR_RX_AGC_COMP_0 + sizeof(TDS_NV_RX_AGC_COMP_STRU))
#define ADDR_RX_AGC_COMP_2            (ADDR_RX_AGC_COMP_1 + sizeof(TDS_NV_RX_AGC_COMP_STRU))
#define ADDR_RX_AGC_FREQ_COMP_0       (ADDR_RX_AGC_COMP_2 + sizeof(TDS_NV_RX_AGC_COMP_STRU))
#define ADDR_RX_AGC_FREQ_COMP_1       (ADDR_RX_AGC_FREQ_COMP_0 + sizeof(TDS_NV_RX_AGC_FREQ_COMP_STRU))
#define ADDR_RX_AGC_FREQ_COMP_2       (ADDR_RX_AGC_FREQ_COMP_1 + sizeof(TDS_NV_RX_AGC_FREQ_COMP_STRU))
#define ADDR_TX_PA_LEVEL_THRE       (ADDR_RX_AGC_FREQ_COMP_2 + sizeof(TDS_NV_RX_AGC_FREQ_COMP_STRU))
#define ADDR_DRX_PARA           (ADDR_TX_PA_LEVEL_THRE + sizeof(TDS_NV_RX_PA_LEVEL_THRE_STRU))
#define ADDR_US_TCXO_INIT           (ADDR_DRX_PARA + sizeof(TDS_NV_DRX_PARA_STRU))

/*end*/



/************************************************************
                             ���ݽṹ����
************************************************************/
typedef struct
{
    VOS_UINT16 usRfstdby2TxCfgTimeT1;
    VOS_UINT16 usRfstdby2TxCalmTimeT2;
    VOS_UINT16 usRfstdby2RxCfgTimeT3;
    VOS_UINT16 usSpeedOffAdvanceTimeT4;
    VOS_UINT16 usRfRxOnAdvanceTime;
    VOS_UINT16 usRfTxOnAdvanceTime;
    VOS_UINT16 usFirRxEnAdvanceTimeT5;
    VOS_UINT16 usFirTxEnAdvanceTimeT6;
    VOS_UINT16 usABBAdOnAdvanceTimeT7;
    VOS_UINT16 usABBDaOnAdvanceTimeT8;
    VOS_UINT16 usPaEnAdvanceTimeT9;
    VOS_UINT16 usTxVGAAdvanceTimeT10;
    VOS_UINT16 usRxVGAorDCAdvanceTimeT11;
    VOS_UINT16 usFreqSWAdvanceTimeT12;
    VOS_UINT16 usAgcCfgAdvanceTime;
    VOS_UINT16 usTimerT0;
}RF_ADVANCE_TIME_STU;
typedef struct
{
    VOS_UINT32 ulTxEnBitMap;                 /*TXEN��Ӧ��bitλѡ��
 */
    VOS_UINT32 ulResetEnBitMap;
    VOS_UINT32 ulABBADEnBitMap;
    VOS_UINT32 ulABBDAEnBitMap;
    VOS_UINT32 ulFirADEnBitMap;
    VOS_UINT32 ulFirDAEnBitMap;
    VOS_UINT32 ulPaAttBitMap;
    VOS_UINT32 ulPaAttModeCfg;
    VOS_UINT32 ulBitMapResv;
}RF_COMM_CONFIG_STRU;
typedef struct
{
    VOS_UINT32 ulPaEnBitMap;
    VOS_UINT32 ulAntSelRxOnBitMap;
    VOS_UINT32 ulAntSelTxOnBitMap;
    VOS_UINT32 ulBitMapResv;
}RF_PRIVATE_CONFIG_STRU;
typedef struct
{
    VOS_UINT16 ucRxMainLnaSel; /*��Ƶ��ͨ��LNAѡ��
 */
    VOS_UINT16 ucRxDvtyLnaSel;
    VOS_UINT16 ucTxLnaSel;
    VOS_UINT16 ucResv;
}RF_PRIVATE_CHANNEL_CFG_STRU;
typedef struct
{
    VOS_UINT16 ucRxCoreSel;    /*����ͨ��Coreѡ��
 */
    VOS_UINT16 ucRxDivider;    /*����ͨ����Ƶѡ��
 */
    VOS_UINT16 ucTxCoreSel;
    VOS_UINT16 ucTxDivider;
}RF_PRIVATE_CORE_DIV_CFG_STRU;
typedef struct
{
    VOS_UINT32 ulRfInitRegNum; /*��ʼ���Ĵ�������
 */
    VOS_UINT32 ulRfCfgTab[RF_INITIAL_REGS_NUM_MAX]; /*�Ĵ�����ַ������ֵ�б�
 */
}RF_INITIAL_STRU;
typedef struct
{
    VOS_UINT32 ulRegAddr; /*���üĴ�����ַ
 */
    VOS_UINT32 ulCfgValue;  /*�Ĵ�����Ӧ����ֵ
 */
}RF_REG_ADDR_CFG_STRU;
typedef struct
{
    VOS_UINT32 ulBoardType;    /*������̬ ����
 */
    VOS_UINT16 ulBandNumSupt;  /*֧��band��Ŀ
 */
    VOS_UINT16 usReserved;             /* ���ֽڶ���*/
    VOS_UINT16 ulBandList[RF_SUPPORT_BAND_NUM];     /*֧��band�б�
 */
    RF_INITIAL_STRU stRfInitTbl;
    RF_COMM_CONFIG_STRU stRfCommCfg; /*RF���ͨ������
 */
    RF_PRIVATE_CONFIG_STRU stRfPrivateCfg[RF_SUPPORT_BAND_NUM]; /* ��band��ص�RF����
 */
    RF_PRIVATE_CHANNEL_CFG_STRU stRfChannelCfg[RF_SUPPORT_BAND_NUM];/*��Ƶͨ������
 */
    RF_PRIVATE_CORE_DIV_CFG_STRU stRfCoreAndDivSel[RF_SUPPORT_BAND_NUM];
	VOS_UINT32 aulCtuPaMaxConfig[8];
}NV_DSP2RF_CFG_STRU;
typedef struct
{
    /*VOS_UINT16 ulAgcTblNoBlock[RF_AGC_TBL_NUM];
 */
    /*VOS_UINT16 ulAgcTblBlock[RF_AGC_TBL_NUM];
 */
    VOS_UINT16 ulAgcTblNoBlock[TDS_RX_LEVEL_NUM_MAX];
    VOS_UINT16 ulAgcTblBlock[TDS_RX_LEVEL_NUM_MAX];
}NV_RF_AGC_PARA_STRU;
typedef struct
{
    VOS_UINT16 usAapcCode;
    VOS_UINT16 usDapcCode;
}NV_RF_APC_CODE_STRU;
typedef struct
{
    /*NV_RF_APC_CODE_STRU stNvApcHighTbl[RF_APC_TBL_HIGH_NUM];
 */
    NV_RF_APC_CODE_STRU stNvApcLowTbl[RF_APC_TBL_LOW_NUM];
}NV_RF_APC_PARA_STRU;

#if 0
typedef struct
{
    VOS_UINT16 usCurrFreq;
    VOS_UINT16 usCfgFlag;
    VOS_UINT16 usCfgIndex;
    VOS_UINT16 usTransdentFlg;/*������Ϣ���
 */
}RF_DCOC_CFG_STU;
#endif
/*bzj nv test end*/



typedef struct
{
    VOS_INT16 asTxMaxPower[TDS_BAND_NUM_MAX];
}TDS_NV_MAXPOWER_STRU;

typedef struct
{
    VOS_INT16 asTxPower[TDS_TX_CAL_POWERNUM_MAX];
}TDS_NV_TX_POWER_LIST_STRU;

typedef struct
{
    VOS_UINT16 ausCalFreq[TDS_TX_CAL_FREQNUM_MAX];
}TDS_NV_TX_CAL_FREQ_LIST_STRU;

typedef struct
{
    VOS_UINT16 ausCalFreq[TDS_RX_CAL_FREQNUM_MAX];
}TDS_NV_RX_CAL_FREQ_LIST_STRU;
/*
typedef struct
{
    VOS_INT16 asTxMaxPower[TDS_TX_LEVEL_NUM_MAX];
    VOS_INT16 asReserve;
}TDS_NV_PA_POWER_STRU;*/

typedef struct
{
    VOS_INT16 asTxPowerComp[TDS_TX_CAL_POWERNUM_MAX];
}TDS_NV_TX_APC_COMP_STRU;

typedef struct
{
    VOS_INT16 asTxFreqComp[TDS_TX_LEVEL_NUM_MAX][TDS_TX_CAL_FREQNUM_MAX];
}TDS_NV_TX_APC_FREQ_COMP_STRU;

typedef struct
{
    VOS_INT16 asRxAgcComp[TDS_RX_LEVEL_NUM_MAX];
}TDS_NV_RX_AGC_COMP_STRU;

typedef struct
{
    VOS_INT16 asRxFreqComp[TDS_RX_CAL_FREQNUM_MAX];
}TDS_NV_RX_AGC_FREQ_COMP_STRU;

typedef struct
{
    VOS_UINT16 ausTempSensor[TDS_TEMP_NUM_MAX];
}TDS_NV_TEMP_SEMSOR_STRU;

typedef struct
{
    VOS_INT16 asTxTempComp[TDS_TX_LEVEL_NUM_MAX][TDS_TEMP_NUM_MAX];
}TDS_NV_TX_TEMP_COMP_STRU;

typedef struct
{
    VOS_INT16 asRxTempComp[TDS_TEMP_NUM_MAX];
}TDS_NV_RX_TEMP_COMP_STRU;

typedef struct
{
    VOS_UINT16 ausRxAgcCalPowerNum;
    VOS_INT16 asRxAgcCalPower[TDS_RX_LEVEL_NUM_MAX];
}TDS_NV_RX_AGC_CAL_POWER_STRU;

/* BEGIN: Added by xueqiuyan, 2012/6/29   PN:tds_apc*/
typedef struct
{
    VOS_INT16 sHigh2MidThre;
    VOS_INT16 sMid2HighThre;
    VOS_INT16 sMid2LowThre;
    VOS_INT16 sLow2MidThre;
}TDS_NV_RX_PA_LEVEL_THRE_STRU;

/* END:   Added by xueqiuyan, 2012/6/29 */


typedef struct
{
    /*VOS_UINT16 ausTxApcOffReduce;
 */
    VOS_UINT32 ausTxApcOffReduce;
}TDS_NV_TX_APCOFF_REDUCE_STRU;

typedef struct
{
    VOS_INT16 sAcsDifferThreshold;                       /*(6)*/
    VOS_INT16 sAcsPowerThreshold0;                       /*(-49)1*/
    VOS_INT16 sAcsPowerThreshold1;                        /*(-30)1*/
    VOS_INT16 sRev;

}NV_RF_ACS_PARA_STRU;

typedef struct
{
    VOS_INT16 sPowerCalConst; /*(-3791)
 */
    VOS_INT16 sPreDiffer; /*(-305)
 */
    VOS_INT16 sPowerFactor;/*(-1120)
 */
    VOS_INT16 sRssiShiftFactor;/*1152
 */
    VOS_INT16 sPreRssiFactor;/*24
 */
    VOS_UINT16 usNoneBlockingTarget;/*3/
 */
    VOS_UINT16 usBlockingTarget;/*3/
 */
    VOS_UINT16 usAcsZ;/*0
 */
    VOS_INT16 sRfMinPowDbm;/*(-110)
 */
    VOS_INT16 sRfMaxPowDbm;/*(-20)
 */
    VOS_INT16 sPowerConst; /*(2688)
 */
    VOS_INT16 sRev;
}NV_RF_AGC_CAL_PARA_STRU;

#if 0
typedef struct
{
    VOS_UINT16    ucTDSMasterDrxControlFlag;
    VOS_UINT16    ucTDSSlaveDrxControlFlag;
    VOS_UINT32    ucRsvd[8];
}TDS_NV_DRX_PARA_STRU;
#endif

typedef struct
{
    NV_DSP2RF_CFG_STRU stDsp2RfCfg;/*��ID��0xE400��
 */
    RF_ADVANCE_TIME_STU stRfAdvanceTime;/*��ID��0xE401��
 */
    #if 0
    NV_RF_AGC_PARA_STRU stRfAgcPara;
    NV_RF_APC_PARA_STRU stRfApcPara;
    #else
    NV_RF_AGC_PARA_STRU stRfAgcCodePara;/*��ID��0xE402��AGC������*/
    NV_RF_AGC_PARA_STRU stRfAgcUpThrGain;/*��ID��0xE403��AGC��������*/
    NV_RF_AGC_PARA_STRU stRfAgcDownThrGain;/*��ID��0xE404�AGC��������*/

    NV_RF_AGC_PARA_STRU stRfAgcTotalGain;/*��ID��0xE405�AGC������*/
    NV_RF_ACS_PARA_STRU stRfAcsPara;/*��ID��0xE406��*/
    NV_RF_AGC_CAL_PARA_STRU stRfAgcCalPara;/*��ID��0xE407��*/
    NV_RF_APC_PARA_STRU stRfApcPara;/*��ID��0xE408��
 */
    #endif

    TDS_NV_MAXPOWER_STRU stMaxPower;/*��ID��0xE4e0��
 */
    TDS_NV_TX_APCOFF_REDUCE_STRU stTxApcoffReduce;/*��ID��0xE4e1��
 */

    TDS_NV_TX_CAL_FREQ_LIST_STRU stTxCalFreq[3];/*��ID��0xE4e3  0xE4e9  0xE4ef��
 */
    TDS_NV_RX_CAL_FREQ_LIST_STRU stRxCalFreq[3];/*��ID��0xE4e4  0xE4ea  0xE4f0��
 */
    TDS_NV_TEMP_SEMSOR_STRU stTempSensor[3];/*��ID��0xE4e5  0xE4eb  0xE4f1��
 */
    TDS_NV_TX_TEMP_COMP_STRU stTxTempComp[3];/*��ID��0xE4e6  0xE4ec  0xE4f2��
 */
    TDS_NV_RX_TEMP_COMP_STRU stRxTempComp[3];/*��ID��0xE4e7  0xE4ed  0xE4f3��
 */

    /*TDS_NV_PA_POWER_STRU stTxPaMaxPower[3];*//*��ID��0xF8f0  0xF8f5  0xF8fa��
 */
    TDS_NV_TX_APC_COMP_STRU stTxPowerComp[3];/*��ID��0xF8f1  0xF8f6  0xF8fb��
 */
    TDS_NV_TX_APC_FREQ_COMP_STRU stTxFreqComp[3];/*��ID��0xF8f2  0xF8f7  0xF8fc��
 */
    TDS_NV_RX_AGC_COMP_STRU stRxAgcComp[3];/*��ID��0xF8f3  0xF8f8  0xF8fd��
 */
    TDS_NV_RX_AGC_FREQ_COMP_STRU stRxFreqComp[3];/*��ID��0xF8f4  0xF8f9  0xF8fe��
 */

    TDS_NV_RX_PA_LEVEL_THRE_STRU stTxPaLevelThre;/*��ID��0xE409��
 */
    /*TDS_NV_DRX_PARA_STRU stTdsNvDrxPara;*/ /*��ID��0xE40a��
 */
	VOS_UINT16 usTcxoInit;/*��ID��0xE900��TCXO ��ֵ
 */
}TDS_NV_PARA_STRU;


/* ���ڱ�ʶNV�Ƿ�����Band, 0:������,ֱ��ʹ����ʵnv id.  1:����,ʹ������������ӦBand��nv id */
#define TDS_DSPNV_ID_FLG		(0)
#define TDS_DSPNV_IDX_FLG		(1)

#define TDS_GET_MEMBER_OFFSET_IN_STRUCT(stType, ulMember)   \
          ((VOS_UINT32) &(((stType *) 0)->ulMember))


/*****************************************************************************
 ö����    : TDS_BAND_ENUM
 ö��˵��  : ����������ͬband��NV�б�
*****************************************************************************/
enum TDS_BAND_ENUM
{
	TDS_BAND_34,
	TDS_BAND_39,
	TDS_BAND_40,
	TDS_BAND_RESERVED,

	TDS_BAND_BUTT
};
typedef VOS_UINT8 TDS_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : TDS_NV_INDEX_ENUM
 ö��˵��  : ����������ͬband�µ���ͬ��NV��
*****************************************************************************/
enum TDS_NV_INDEX_ENUM
{
	NV_IDX_TDS_TEMPERATURE_SENSOR = 0,
	NV_IDX_TDS_TX_CAL_FREQ,
	NV_IDX_TDS_TX_TEMP_COMP,
	NV_IDX_TDS_TX_RF_BIAS,
	NV_IDX_TDS_TX_RF_BB_ATT,
	NV_IDX_TDS_PA_LEVEL_THRE,
	NV_IDX_TDS_RX_CAL_FREQ,
	NV_IDX_TDS_AGC_BAND_PARA,
	NV_IDX_TDS_AGC_TEMP_COMP,
	NV_IDX_TDS_TX_FREQ_COMP,
	NV_IDX_TDS_PA_POWER_DIFFERENCE,
	NV_IDX_TDS_TX_APC_GAIN,
	NV_IDX_TDS_AGC_FREQ_COMP,
	NV_IDX_TDS_DCOC_CAL,
	NV_IDX_TDS_RF_TXIQ_CAL,

    TDS_NV_IDX_BUTT
};
typedef VOS_UINT32 TDS_NV_INDEX_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : TDS_DSPNV_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
	VOS_UINT32          ulNvIdFlag;
	VOS_UINT32          ulNvId;
	VOS_UINT32          ulNvLength;
	VOS_UINT32          pNvItemAddr;
}TDS_DSPNV_CFG_STRU;


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


