

#ifndef _TDS_CHE_OM_DEF_H_
#define _TDS_CHE_OM_DEF_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "balong_lte_dsp.h"


/************************************************************
                               �궨��
************************************************************/

typedef struct TPHY_REQ_JD_REPORT_SWITCH
{
	UINT16 usTsBitMap;
	OM_REQ_ENABLE_ENUM_UINT16 enCheCfgRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enRxSignRpt;
    UINT16 enInitCheRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enActWinRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enAlphaRpt;
    UINT16 enLlrRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enCheJdIFRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enJdCdIFRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enJdTimeRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enNoiseRpt;
}TPHY_REQ_JD_REPORT_SWITCH_STRU;

typedef struct TPHY_REQ_CHE_NVPARA_SWITCH
{
    UINT16 usThSaleIc;                    /*�����޷�����*/
    UINT16 usNoiseLimit;                  /*������Сֵ*/
    UINT16 usRev0;
    UINT16 usRev1;
}TPHY_REQ_CHE_NVPARA_SWITCH_STRU;


typedef enum __TDS_CHE_CODE_TYPE__
{
	 SCCH = 1,
	 PCCPCH,
	 AGCH,
	 HICH,
	 FPACH,
	 PICH,
	 NSHICH,
	 SCCPCH,
	 DPCH,
	 DSCH
}TDS_CHE_CODE_TYPE_ENUM;

typedef UINT16  TDS_CHE_CODE_TYPE_ENUM_UINT16;
/************************************************************
                             ���ݽṹ����
************************************************************/






/************************************************************
                             ��������
************************************************************/
typedef enum TDS_JD_OM_RPT_IND
{
    TPHY_REQ_JD_SWITCH                         = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_JD_CHE_CFG_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_JD_RX_SIGN_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_INIT_CHE_IND                      = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x3),
    TPHY_REQ_JD_LLR_IND                        = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x4),
    TPHY_REQ_CHE_JD_INTERFACE_IND              = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x5),
    TPHY_REQ_JD_CD_INTERFACE_IND               = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x6),
    TPHY_REQ_CHE_ALPHAFILTER_IND               = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x7),
    TPHY_REQ_CHE_ACTWIN_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x8),
    TPHY_REQ_CHE_TIME_IND                      = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x9),
    TPHY_REQ_CHE_PARA                          = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0xa),
    TPHY_REQ_CHE_NOISE_RPT                     = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0xb)
}TPHY_OM_REQ_JD_STRU;

/************************************************************
                     ERROR���ݽṹ����
************************************************************/
typedef enum
{
    TPHY_ERROR_CHE_MORE_FIR_ERROR              = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x1),
    TPHY_ERROR_CHE_NO_CONFIG_ERROR             = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x2),
    TPHY_ERROR_CHE_DIV_ZREO                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x3),
    TPHY_ERROR_CHE_MOD_ZREO                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x4),

}TPHY_CHE_ERROR_ENUM;

typedef struct
{
    UINT16      usSysSfn;        /*ϵͳ��֡��*/
    UINT16      usSysTs;         /*ϵͳʱ϶��*/
    UINT16      usChipNum[4];
}TPHY_OM_TRACE_CHE_TIME_STRU;


typedef struct
{
    UINT16 usSfnId;                            /*��֡��*/
    UINT16 usTsId;                             /*ʱ϶��*/
    UINT16 usMidId;                            /*С��ID*/
    UINT16 usKLocal;                           /*��С��Kֵ*/
    UINT16 usLocCellPos;                       /*����*/
    UINT16 usCellNum;                          /*С����*/
    UINT8 usCodeNum;                           /*����������*/
    UINT8 usSf;                                /*��Ƶ����*/
    UINT8 usMidMode;                           /*Midamble���䷽ʽ��0:default;1:common;2: Specific;*/
    UINT8 usMidShift;                          /*MIDAMBLE ƫ�ƣ���uMidModeΪ2ʱ��Ч*/

    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code0Type;    /*�ŵ�����*/
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code1Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code2Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code3Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code4Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code5Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code6Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code7Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code8Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code9Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code10Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code11Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code12Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code13Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code14Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code15Type;

    UINT16 ausDmuMode[16];                     /*���Ʒ�ʽ*/
} TPHY_OM_REQ_CHE_CFG_PARA_STRU;

typedef struct
{
    INT16  asRxData[864 * 2];
} TPHY_OM_REQ_RX_SIGN_STRU;

typedef struct
{
    INT16  asInitChe[128 * 2];
} TPHY_OM_REQ_INIT_CHE_STRU;

typedef struct
{
    INT8  acSoftData[176];
} TPHY_OM_REQ_JD_SOFT_DATA_STRU;

typedef  struct
{
    UINT32  pulChEst;                   /* �ŵ����ƽ��,[128*2*3]128chip*3С��*4byte */
    UINT32  pulRxData;                  /*���������ź�*/
    UINT32  pulSrMidamble;              /*Midamble�����ع��ź�*/
    UINT32  ulNoise;                    /*��������*/
    UINT16  usTotalWin;                 /*���������0~16*/
    UINT16  usSF;                       /*��Ƶ���ӣ�1��16*/
	UINT16  usK;                 /*�������������0~16*/
    UINT16  usTotalVRU;                 /*�������������0~16*/
    UINT32  ulLocalVRU;                 /*���û��������������0~16*/
    UINT16  ausChanID[16];              /*ÿ�����������ţ�0~15*/
    UINT16  ausModuType[16];            /*ÿ������ĵ��Ʒ�ʽ��QPSK/16QAM*/
    UINT16  ausWinID[16];               /*ÿ�����Ĵ��ţ�0~(3*WinLen-1)*/
    UINT16  ausWinVRU[16];              /*ÿ�������������������1~16*/
    UINT16  ausVRUScramID[16];          /*ÿ�������Ӧ��С��ID��0~127*/
} TPHY_OM_REQ_CHE_JD_INTERFACE_STRU;

typedef struct
{
    UINT16     usRxSfn;               /*������֡��*/
    UINT16     usRxTsId;              /*����ʱ϶��*/
	UINT8      ucRuActiveFlag[16];    /*��������־*/
    UINT8      ucCctrchType[16];      /*�ŵ�����*/
    UINT16     usModulationType[16];  /*��Ӧ�����������*/
    INT32      psJdCdData[16];        /*JdCdData��ַ*/
    
    UINT16     usDpchTsNum;           /*һ����֡��Dpch�����ʱ϶������Χ0~5*/
    UINT16     usDschTsNum;           /*һ����֡��Dsch�����ʱ϶������Χ0~5*/
    UINT16     usScchNum;             /*һ����֡����Ҫ�����Scch�ĸ�������Χ0~4*/
    UINT16     usAgchNum;             /*һ����֡����Ҫ�����Agch�ĸ�������Χ0~4*/
    UINT16     usScchTsId[4];             /*����ʱ϶����Χ0~6*/
    UINT8      ucScchFirstCode[4];        /*��һ�����λ�ã���Χ0~15*/
    UINT8      ucScchSecondCode[4];       /*�ڶ������λ�ã���Χ0~15*/
    UINT16     usAgchTsId[4];             /*����ʱ϶����Χ0~6*/
    UINT8      ucAgchFirstCode[4];        /*��һ�����λ�ã���Χ0~15*/
    UINT8      ucAgchSecondCode[4];       /*�ڶ������λ�ã���Χ0~15*/
     
} TPHY_OM_REQ_JDCD_INTERFACE_NEW_STRU;

typedef  struct
{
    UINT32 ulPathPwrLast[96];       /*����֡������*/
    INT8   ucCodeType[16];          /*����֡�ŵ�����*/
    INT8   ucActWinFlag[16];        /*���״̬*/
    INT16  sShiftCurrent;           /*��ǰ��λֵ*/
    INT16  sShiftLast;              /*����֡��λֵ*/
	INT16  sAgcGainLast;            /*����֡Agc����*/
	INT16  sAgcGainCur;             /*��ǰ��֡Agc����*/
    INT32  lNoiseLast;              /*����֡����*/
    INT32  lNoiseCurrent;           /*��ǰ��֡����*/
    INT16  sFirstTsFlag;            /*��һ��ʱ϶��־*/
	INT16  sTimingOffsetFlag;       /*��ʱ������־*/
	INT16  sAgcRatio;
	INT16  sReserved[5];
} TDS_OM_CHE_ALPHAFILTER_STRU;


typedef  struct
{
    UINT32 Cell0WinPwr[16];
    INT8   Cell0ActWinFlag[16];
    INT32  Cell0NoisePwr;
    UINT16 Cell0Id;
    UINT16 Cell0MaxPathPos;
    UINT32 Cell0SrPtr;
    UINT32 Cell0CirPtr;

    UINT32 Cell1WinPwr[16];
    INT8   Cell1ActWinFlag[16];
    INT32  Cell1NoisePwr;
    UINT16 Cell1Id;
    UINT16 Cell1MaxPathPos;
    UINT32 Cell1SrPtr;
    UINT32 Cell1CirPtr;

    UINT32 Cell2WinPwr[16];
    INT8   Cell2ActWinFlag[16];
    INT32  Cell2NoisePwr;
    UINT16 Cell2Id;
    UINT16 Cell2MaxPathPos;
    UINT32 Cell2SrPtr;
    UINT32 Cell2CirPtr;
} TDS_CHE_COMMON_DATA_STRU;

typedef  struct
{
    INT32 lNoise1;
    INT32 lNoise2;
	INT32 lNoiseThFlag;
	INT32 lRev;
} TDS_CHE_NOISE_RPT_STRU;


extern TPHY_REQ_JD_REPORT_SWITCH_STRU gstJdReportSwitch;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TDS_CHE_OM_DEF_H__ */

