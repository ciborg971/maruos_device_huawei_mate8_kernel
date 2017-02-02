
#ifndef TDSUL_OM_DEF_H_
#define TDSUL_OM_DEF_H_


#include "om_base_def.h"
#include "tds_datapath_interface.h"
#include "tds_ul_interface.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define TDS_UL_MAX_TS_NUM             (0x6)
#define MAX_TRCH_CNT                  (6)          //������ŵ���
#define MAX_TRCH                      (6)

//OM ���Ͷ���
typedef enum
{
    TPHY_REQ_UL_REPORT_ENA         = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_UL_PWR_SET,
    TPHY_REQ_UL_SS_SET,
    TPHY_REQ_UL_UPPCH_LOOP,
    TPHY_REQ_UL_DATA_SAMPLE,
    TPHY_REQ_UL_ZERO_PADDING,
    TPHY_REQ_UL_SPEED_REPORT,

    TPHY_REQ_TAS_REPORT,  //+TAS OM 20141014 ����TDS UL��OM�ṹ
    TPHY_REQ_DPDT_REPORT, //songwenning

    TPHY_REQ_UL_REQ_BUTT,
}TPHY_REQ_UL_ENUM;

typedef enum
{
    TPHY_TRACE_UL_PRACH_SEND_EVT              = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_TRACE, 0x0),
    TPHY_TRACE_UL_DPCH_CONFIG_EVT,
    TPHY_TRACE_UL_DPCH_SEND_EVT,
    TPHY_TRACE_UL_HO_SYNC_EVT,
    TPHY_TRACE_UL_EPUCH_CONFIG_EVT,
    TPHY_TRACE_UL_EPUCH_SEND_EVT,
    TPHY_TRACE_UL_LOOP_TEST_EVT,
    TPHY_TRACE_UL_DRIVER_EVT,
    TPHY_TRACE_UL_FPACH_RCV_EVT,
    TPHY_TRACE_UL_PRACH_CC_EVT,
    TPHY_TRACE_UL_DPCH_CC_EVT,
    TPHY_TRACE_UL_EPUCH_CC_EVT,
    TPHY_TRACE_UL_UPPCH_BC_EVT,
    TPHY_TRACE_UL_CHAN_BC_EVT,
    TPHY_TRACE_UL_DPCH_TPC_FILL_EVT,
    TPHY_TRACE_UL_SS_ADJUST_EVT,
    TPHY_TRACE_UL_FIR_INT_EVT,
    TPHY_TRACE_UL_CC_BBPREG_HEAD_EVT,        //�ϱ�BBP����
    TPHY_TRACE_UL_CC_BBPREG_TRCH_EVT,
    TPHY_TRACE_UL_CC_BBPREG_TS_EVT,
    TPHY_TRACE_UL_CC_PARA_EVT,          //�ϱ�CC�������
    TPHY_TRACE_UL_BC_PARA_EVT,           //�ϱ�BC���Ʋ���
    TPHY_TRACE_UL_EDCH_BBPREG_EVT,      //�ϱ�EDCH�ŵ�����Ĵ�������
    TPHY_TRACE_UL_HSPDSCH_CONFIG_EVT,
    TPHY_TRACE_UL_SWITCH_CHANGE_EVT,

    TPHY_TRACE_TAS_ASU_EVT,
    TPHY_TRACE_TAS_DPDT_SWITCH_EVT,
    TPHY_TRACE_TAS_STATE_CHANGE_EVT,
    TPHY_TRACE_TAS_GIVE_RSCP_EVT,
    TPHY_TRACE_TAS_GIVE_IDLE_EVT,
    TPHY_TRACE_TAS_GIVE_DCH_EVT,
    TPHY_TRACE_TAS_SEARCH_EVT,
    TPHY_TRACE_DPDT_REPORT_EVT,
	
    TPHY_TRACE_UL_HSSICH_PARA_EVT,
    TPHY_TRACE_TAS_ESTIMATE_N1_EVT,  //N1
    TPHY_TRACE_TAS_ESTIMATE_N2_EVT,  //N2
    TPHY_TRACE_TAS_ESTIMATE_N3_EVT,  //N3
    TPHY_TRACE_TAS_PROTECT_EVT,      //�벻Ҫ��������ĸ��궨�壬N1��N2��N3��PROTECT
    TPHY_TRACE_UL_EVT_BUTT
}TPHY_TRACE_EMU_EVT_ENUM;

typedef enum
{
    TPHY_ERROR_UL_CC_TFOVERFLOW                = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_ERROR, 0x0),
    TPHY_ERROR_UL_CC_TFCOVERFLOW,
    TPHY_ERROR_UL_CC_ZEROPARA,
    TPHY_ERROR_UL_CC_INVTRCHID,
    TPHY_ERROR_UL_CC_INVSTATUS,
    TPHY_ERROR_UL_BC_PARAERR,
    TPHY_ERROR_UL_ZEROPADDING_LEN_OVERFLOW,
    TPHY_ERROR_UL_DMA_PARAERR,
    TPHY_ERROR_UL_PRIM_PARAERROR,
    TPHY_ERROR_UL_EDCH_CCPARAERR,
    TPHY_ERROR_UL_EUCCH_INVNUM,
    TPHY_ERROR_UL_SICH_INVSTATE,
    TPHY_ERROR_UL_EPUCH_CHNINVALID,
    TPHY_ERROR_UL_EPUCH_CCLOST,
    TPHY_ERROR_UL_CC_DELAY,
    TPHY_ERROR_UL_DPCH_CCLOST,
    TPHY_ERROR_UL_ERR_BUTT
} TPHY_ERROR_UL_ENUM;

typedef enum
{
    TPHY_TRACE_UL_PRACH_CC_OUT_DATA_IND              = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_IND, 0x0),
    TPHY_TRACE_UL_DPCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_EPUCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_EUCCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_BC_SLOT_DATA_IND,
    TPHY_TRACE_UL_PRACH_SRC_DATA_IND,
    TPHY_TRACE_UL_DPCH_SRC_DATA_IND,
    TPHY_TRACE_UL_EPUCH_SRC_DATA_IND,
    TPHY_TRACE_UL_FIR_DATA_IND,
    TPHY_TRACE_UL_IND_BUTT,
}TPHY_TRACE_EMU_IND_ENUM;

typedef enum
{
    TPHY_UL_OM_SWITCH_OFF = 0,
    TPHY_UL_OM_SWITCH_ON,
}TPHY_UL_OM_SWITCH_ENUM;

//REQ
typedef struct
{
    TPHY_UL_OM_SWITCH_ENUM    enTphyUlReportEn;
    TPHY_UL_OM_SWITCH_ENUM    enTphyUlSgReportEn;
}TPHY_REQ_UL_REPORT_ENA_STRU;

typedef struct
{
    UINT16 usTti;
    UINT16 usTbNum;
    UINT16 usTbSize;
} CC_TFC_STRU;

typedef struct
{
    UINT16 usChnCodeType;
    UINT16 usRmAttr;
    UINT16 usCrcCode;
} CC_SMTFINF_STRU;

typedef struct
{
    UINT16 usTbNum;
    UINT16 usTbSize;
} CC_DATADESC_STRU;

typedef struct
{
    UINT16  usCcTrchNum;
    UINT16  ausCcRuSF1[5];
    UINT16  ausCcRuSF2[5];
    UINT16  usCcTsNum;
    UINT16  ausCcServiceType[6];
    UINT16  usCcPuncturingLimit;
    UINT16  ausCcModulateMode[5];
    UINT16  usCcDynamicSF;
    UINT16  usCcInter2Mode;
    UINT16  usCcAllowedTfcNum;
    UINT16  ausCtfciCode[5];
    UINT16  ausCcSsTpcSymbols[5];
    UINT16  ausTfNum[6];
    UINT16  usPsOffset;                              //added for double PS
    UINT16  usTbnum1Ind;
    UINT16  *pausCcAllowedTfci;                      //128
    UINT16  *pausCtfc;                               //128
    //UINT16  *pausCcSemistaticTfInfo;                 //18

    CC_TFC_STRU         *pastTfList;            //432
    CC_SMTFINF_STRU     *pastSemStaticTfInfo;   //18
    CC_DATADESC_STRU    astDataDesc[MAX_TRCH_CNT];          //12
} DCH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  usAccChannelCodingType;
    UINT16  usAccCcCdCrcSize;
    UINT16  usAccCcCdTbNum;
    UINT16  usAccCcCdTbSize;
    //UINT16  ausPrimChannelCode[4];
    UINT16  ausSf[4];
    UINT16  ausChannelCode[4];
    UINT16  usAccCcCdTti;
    UINT16  usResv;
} PRACH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  usCcCdChannelCodeType;
    UINT16  ausCcRuSF1[5];
    UINT16  usCcTsNum;
    UINT16  usCcCdCrcSize;
    UINT16  usCcModulateMode;
    UINT16  usCcHsupaRsn;
    UINT16  usCcRvIndex;
    UINT16  usEucchSymbolNum;
    CC_TFC_STRU  stCcTransportFormat;
    UINT16  usReserved;
} EDCH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  *pausBcCcPingBuf;                       //1320
    INT16   sGainFactor;
    UINT16  ausCcRuSF1[5];
    UINT16  ausCcRuSF2[5];
    UINT16  usCcTsNum;
    UINT16  ausCcRuNum[5];
    UINT16  ausCcRuNumPrach[5];
    UINT16  ausEveryTsOffset[10];
    UINT16  ausEveryTsOffsetPrach[10];
    UINT16  ausFirstTpcOffset[5];
    UINT16  ausSecondTpcOffset[5];
} CC_OUT_INFO_STRU;

typedef struct
{
    UINT16  usTrchId;
    UINT16  ausCcTrchCnt[MAX_TRCH];
    UINT16  ausCcTrchCntPrach[MAX_TRCH];

    UINT16  *pausCcCsData;                          //160  added for cs
    UINT16  *pausCcCsSubA;                          //27
    UINT16  *pausCcCsSubB;                          //27
    UINT16  *pausCcCsSubC;                          //27
    UINT16  *pausCcPsData;                          //528
    UINT16  *pausCcDcchData;                        //12

    UINT16  *pausCcPrachData;

    UINT16  *pausEdchData;                          //698

    DCH_PRIM_INFO_STRU *pstDchPrimInfo;
    PRACH_PRIM_INFO_STRU *pstPrachPrimInfo;
    EDCH_PRIM_INFO_STRU *pstEDchPrimInfo;
    CC_OUT_INFO_STRU *pstCcOutInfo;
} CC_PARA_STRU;

//STATISTICS
typedef struct
{
    UINT32    ulTphyUlInitNum;
    UINT32    ulTphyUlSetupNum;
    UINT32    ulTphyUlRelNum;
    UINT32    ulTphyUlPrachSendReqNum;
    UINT32    ulTphyUlDpchConfigReqNum;
    UINT32    ulTphyUlDpchSendReqNum;
    UINT32    ulTphyUlHspdschConfigReqNum;
    UINT32    ulTphyUlEpuchConfigReqNum;
    UINT32    ulTphyUlEpuchSendReqNum;
    UINT32    ulTphyUlHoSyncReqNum;
    UINT32    ulTphyUlPrachCcTrigNum;
    UINT32    ulTphyUlPrachCcProcNum;
    UINT32    ulTphyUlBcProcNum;
    UINT32    ulTphyUlDriverTrigNum;
    UINT32    ulTphyUlDriverProcNum;
    UINT32    ulTphyUlDpchCcTrigNum;
    UINT32    ulTphyUlDpchCcProcNum;
    UINT32    ulTphyUlEpuchCcTrigNum;
    UINT32    ulTphyUlEpuchCcProcNum;
    UINT32    ulTphyUlSubFrmIntNum;
    UINT32    ulTphyUlFirIntNum;
    UINT32    ulTphyUlFpachRcvNum;
    UINT32    ulTphyUlFpachFailNum;
}TPHY_UL_CHANCTRL_STAT_STRU;

//TRACE
typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
}TPHY_TRACE_UL_COMM_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSwitch;
}TPHY_TRACE_UL_SWITCH_CHANGE_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usAn;
    UINT16 usCqi;
    UINT16 usTbs;
    UINT16 usRmf;
    UINT16 usRes;
}TPHY_TRACE_UL_HSSICH_PARA_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  usCcTbLen[MAX_TRCH];
    UINT32  usDestDataAddr[MAX_TRCH];
    UINT32  usSrcDataAddr[MAX_TRCH];
}TPHY_TRACE_UL_DPCH_SEND_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT32  ulDpchBitSpeed;
    UINT32  ulDpchKBitSpeed;
    UINT32  ulEdchBitSpeed;
    UINT32  ulEdchKBitSpeed;
    UINT16  usTxTsId[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsPwr[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsFreq[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsChnNum[TDS_UL_MAX_TS_NUM];
    TDS_DATA_PATH_LOG_IN_STRU astUlTxDriverPara[TDS_UL_MAX_TS_NUM];
}TPHY_TRACE_UL_DRIVER_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    TDS_UL_FPACH_BURST_INFO_STRU  stFpachBurstInfo;
}TPHY_TRACE_UL_FPACH_RCV_STRU;

/*typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    CC_PARA_STRU  stCcPara;
}TPHY_TRACE_UL_CC_STRU;
*/

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    PRACH_PRIM_INFO_STRU  stPrachCcPara;
}TPHY_TRACE_UL_PRACH_CC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    //DCH_PRIM_INFO_STRU  stDpchCcPara;
}TPHY_TRACE_UL_DPCH_CC_STRU;



typedef struct
{
    UINT16   usEucchTbsizeIndex;
    UINT16   usEucchRsn;
    UINT16   usEucchHarqProcessId;
    UINT16   usEucchNum;
    UINT16   usEucchTsNum;
    UINT16   ausEucchTpc[2];
    UINT16   ausEucchNumTs[5];
    UINT16   *pusEucchResultTs;
}TDS_UL_EUCCH_PARA;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    EDCH_PRIM_INFO_STRU  stEdchCcPara;
    TDS_UL_EUCCH_PARA stEucchPara;
}TPHY_TRACE_UL_EPUCH_CC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  ausAccSyncUlCode[8];
    UINT32  aulUpPchBcData[128];
}TPHY_TRACE_UL_UPPCH_BC_STRU;

typedef struct
{
    //DPCH or PRACH
    UINT16  usMidId;            //BC input,the Midamble ID
    UINT16  usChannelFlag;      //BC input, the flag of channel type
    UINT16  usTxPower;          //BC input, the send power of the timeslot
    //DPCH 
    UINT16  usModulateMode;     //BC input,modulation mode, 0:QPSK; 1:8PSK; 2:16QAM
    UINT16  usMidambleAllocMode;//BC input,consided the Up Link ,only 2 cases ,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usResverd1;
    UINT16  ausChannelCode[2];   //BC input,MaxRuNum=2,first word is first RU's SF and usCode Number ,second word is second RU's SF and usCode Number                  
    UINT16  usCcRuNum;    //BC input,RU's number,don't consided the HsSich
    UINT16  usCcSf1;      //BC input,first RU's SF, !!!!!!ע�⣬usCcSf1��usCcSf2����ǰ������
    UINT16  usCcSf2;      //BC input,second RU's SF
    UINT16  usGainFactor; //BC input,beta factor
    UINT16  *pusBcCcBuf;   //BC input,the adress of bit data of DPCH or PRACH in this timeslot, Data length [176]
    UINT16  usDpchPower;  //BC input, the power of dpch
    
    //HSDPA HsSich          
    UINT16  usHsSichChannelCode;       //BC input,HsSich RU's SF and usCode Number
    UINT16  usHsSichMidambleAllocMode; //BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsSichMidambleShift;//BC input,only in SpecificMidamble, use it  
    UINT16  usHsSichK;            //BC input,the max user number,the value = 1/2 fact value
    UINT16  usNackAckPoweroffset; //BC input,use to calculate Adjust factor
    UINT16  usNackAckFlag;        //BC input,Nack error flag
    UINT16  usResverd2;
    UINT16  *pusHsSichBuffer;      //BC input,bit data of HsSich, Data length [6] 
    //UINT16  ChannelPowChange;   //BC input, change the channel power
    UINT16  usHsSichPower;        //BC input, the power of Sich
   
    //HSUPA E-PUCH or E-RUCCH                   
    UINT16  usHsupaChannelCode;      //BC input,Epch or Erucch RU's SF and usCode Number         
    UINT16  usHsupaModulateMode;     //BC input,modulation mode, 0:QPSK; 2:16QAM ,ERUCCH is QPSK 
    UINT16  usHsupaMidambleAllocMode;//BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsupaMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usHsupaK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usEucchNumber;           //Bc input, Eucchnumber=tpcnumber 
    INT16   sHsupaGainFactor;       //BC input, E-PUCH's gainfactor,Erucch no gainfactor  
    UINT16  *pusHsupaBuffer;          //BC input,bit data of Edch or Erucch                  
    UINT16  *pusEucchBuffer;          //BC input,bit data of Eucch  
    UINT16  usHsupaPower;            //BC input, the power of Epuch or Erucch      
           
    //BC out               
    INT16   sPowersetting; //BC output,db format send to DSP1 for every time slot
    INT16  *psTxData;      //BC output,the transfers burst, Data length [1728]       
    UINT16  usSysRfPoint;   //BC input, for 1db power step adjust 
    UINT16  usPowContrFlag; //BC input, for Channel usCode power control index
} T_BC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  usBcTotalTsNum;
    UINT16  usDmaTsCnt;
    UINT16  ausUlTsInfo[TDS_UL_MAX_TS_NUM];
    T_BC_STRU stBcInputPara;
}TPHY_TRACE_UL_BC_STRU;

typedef struct
{
    UINT16    ausTpcSs16SFSymbol[5];        //Tpc symbol number
    UINT16    ausfirstTPCoffset[5];         //start fill position if even frame
    UINT16    aussecondTPCoffset[5];        //start fill position if odd frame
    UINT16    ausModulateMode[5];           //Modulation mode
} TDS_UL_CC_FILLTPC;

typedef struct 
{         
    UINT16              usRxTsNum;
    UINT16              usPowerSysFrameCnt;           //system frame counter,and use to get relativeframe         
    UINT16              ausDlTpc[4];                  //CalTpc's result
    TDS_UL_CC_FILLTPC   stFillTpcPara;                //Cc parameter, length 9 word
    INT16 *             psBcCcBuf;                      //CC out data, fill Tpc in it. Length 132*3*2 word   
}TDS_UL_FILL_TPC;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    TDS_UL_FILL_TPC stFillDpchTpcPara;
}TPHY_TRACE_UL_DPCH_TPC_FILL_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    INT16   sLastTxSumSs;
    INT16   sCurrentTxSumSs;
    INT16   sSsAdjust;
    UINT16  usTxAdvPluseCnt;
    UINT16  usTxAdvNegCnt;
    UINT16  usTxDtxPos;
}TPHY_TRACE_UL_SS_ADJUST_STRU;


typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT32  ulTfpTxIntFlag;
    UINT16  usDmaTsCnt;
    UINT16  usBcTotalTsNum;
    UINT16  usUlSyncDmaFlag;
    UINT16  usDmaLen;
    UINT32  ulDmaSourceAddr;
    UINT32  ulDmaDestAddr;
}TPHY_TRACE_UL_FIR_INT_STRU;

//STUB
typedef struct
{
    UINT16 usUpPchSwitch;       /*UpPch���书�ʴ�׮����*/
    UINT16 usRachSwitch;        /*Rach���书�ʴ�׮����*/
    UINT16 usDpchSwitch;        /*Dpch���书�ʴ�׮����*/
    UINT16 usEpuchSwitch;       /*Epuch���书�ʴ�׮����*/
    UINT16 usSichSwitch;        /*Sich���书�ʴ�׮����*/
    UINT16 usUpPchPower;        /*UpPch���书��*/
    UINT16 usRachPower;         /*Rach���书��*/
    UINT16 usDpchPower;         /*Dpch���书��*/
    UINT16 usEpuchPower;        /*Epuch���书��*/
    UINT16 usSichPower;         /*Sich���书��*/
}TDS_UL_TX_POWER_SET_STRU;

typedef struct
{
    UINT16 usSsFixSwitch;       /*��ʱ������׮����*/
    INT16  sSsValue;            /*��ʱ����ֵ*/
}TDS_UL_TX_SS_SET_STRU;

typedef struct
{
    UINT16 usUpPchLoopwitch;    /*UpPchѭ�����Ϳ���*/
    UINT16 usRsv;               
}TDS_UL_TX_PRACH_SET_STRU;

typedef struct
{
    UINT16 usDataSampleSwitch;    /*���������ϱ�����*/
    UINT16 usRsv;               
}TDS_UL_TX_DATA_SAMPLE_SET_STRU;

typedef struct
{
    UINT16 usZeroPaddingBefore;
    UINT16 usZeroPaddingAfter;               
}TDS_UL_TX_ZERO_PADDIND_STRU;

typedef struct
{
    UINT16 usSpeedCapSfnNum;    /* ÿ��ͳ�Ƶ���֡����(200�ı���,200����֡Ϊ1s) */
    UINT16 usSpeedReportEna;    /* �����ϱ�ʹ�� */
}TDS_UL_SPEED_REPORT_STRU;


typedef struct
{
    UINT16 usSichStubSwitch;
    UINT16 usTbsizeIndex;
    UINT16 usModType;
    UINT16 usRes;
} TDS_UL_HSSICH_STUB_STRU;

//STAT
//Cc&Bcͳ����
typedef struct
{
    UINT32 ulTphyUlCcMainNum;               //����CcMain��ں����Ĵ���
    UINT32 ulTphyUlCcMainInvStatusNum;      //����CcMain����ʱ����״̬����Ĵ���
    UINT32 ulTphyUlCcMainInvTrchIdNum;      //����CcMain����ʱ�ŵ����ʹ���Ĵ���
    UINT32 ulTphyUlEdchCcMainNum;           //����EdchCcMain��ں����Ĵ���
    UINT32 ulTphyUlCcSubTaskTrigNum;        //����CcSubTask�����Ĵ���
    UINT32 ulTphyUlCcSubTaskCallNum;        //���ñ���������Ĵ���
    UINT32 ulTphyUlCcWaitTaskExcNum;        //����ͣ��״̬������ʵ��ִ�еĴ���
    UINT32 ulTphyUlCcFinishTaskExcNum;      //�������״̬������ʵ��ִ�д��� 
    UINT32 ulTphyUlCcSwaitIsrNum;           //����ͣ���жϴ������Ĵ���
    UINT32 ulTphyUlCcFinishIsrNum;          //��������жϴ������Ĵ���
    UINT32 ulTphyUlEdchFinishIsrNum;        //����EDCH��������жϴ������Ĵ���
    UINT32 ulTphyUlCcSetRegDataDmaIsrNum;   //�������üĴ�������DMA�жϴ������Ĵ���
    UINT32 ulTphyUlCcGetInt1DataDmaIsrNum;  //���û�ȡ1�ν�֯����DMA�жϴ������Ĵ���
    UINT32 ulTphyUlCcGetMapDataDmaIsrNum;   //���û�ȡ�����ŵ�ӳ������DMA�жϴ������Ĵ���
    UINT32 ulTphyUlCcSbNum;                 //�������SB�����Ĵ���
    UINT32 ulTphyUlBcMainNum;               //����BcMain��ں����Ĵ���
} TPHY_UL_CCBC_STAT_STRU;

//STUB
//CC���߼���������(�Ĵ�������)
#define TDS_UL_MAXTRCH  6
#define TDS_UL_MAXTS    5
typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usChnTypeIdx;
    
    UINT32 ulInt2RegData;
    UINT32 ulSubSegRegData;
}TDS_UL_BBP_REG_HEAD_STRU;

typedef struct
{
    UINT32 ulTrchNum;
    UINT32 ulCrcRegData;
    UINT32 ulEncRegData;
    UINT32 ulInt1RegData;
    UINT32 ulRmCommRegData;
    UINT32 ulCheckBit1RegData;
    UINT32 ulCheckBit2RegData;
}TDS_UL_BBP_REG_TRCH_STRU;

typedef struct
{
    UINT32 ulTsNum;
    UINT32 ulPhCfgRegData;
    UINT32 ulPhBsRegData;
}TDS_UL_BBP_REG_TS_STRU;

typedef struct
{
    UINT16 usChnCodeType;
    UINT16 usRmAttr;
    UINT16 usCrcCode;
} TDS_UL_CCSMTFINF_STRU;

typedef struct
{
    UINT16  usTrchNum;                                      //�����ŵ���
    UINT16  usTsNum;                                        //ʱ϶��
    UINT16  usCcDynamicSF;
    UINT16  ausServiceType[TDS_UL_MAXTRCH];                   //01
    UINT16  ausCcModulateMode[TDS_UL_MAXTS];
    UINT16  ausSsTpcSymbols[TDS_UL_MAXTS];
    UINT16  ausCcRuSF1[TDS_UL_MAXTS];
    UINT16  ausCcRuSF2[TDS_UL_MAXTS];
    UINT16  ausTti[TDS_UL_MAXTRCH];
    UINT16  ausFi[TDS_UL_MAXTRCH];
    UINT16  ausTfciLen[TDS_UL_MAXTS];
    TDS_UL_CCSMTFINF_STRU astSmtfInf[TDS_UL_MAXTRCH];
    
    UINT16 usSubFrameNum;
    UINT16 usChnTypeIdx;
    UINT16 ausRuNum[TDS_UL_MAXTS];
    UINT16 usResv;
}TDS_UL_CCPARA_STRU;

typedef struct
{
    //DPCH or PRACH
    UINT16  usMidId;            //BC input,the Midamble ID
    UINT16  usChannelFlag;      //BC input, the flag of channel type
    UINT16  usTxPower;          //BC input, the send power of the timeslot
    //DPCH 
    UINT16  usModulateMode;     //BC input,modulation mode, 0:QPSK; 1:8PSK; 2:16QAM
    UINT16  usMidambleAllocMode;//BC input,consided the Up Link ,only 2 cases ,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  ausChannelCode[2];   //BC input,MaxRuNum=2,first word is first RU's SF and usCode Number ,second word is second RU's SF and usCode Number                  
    UINT16  usCcRuNum;    //BC input,RU's number,don't consided the HsSich
    UINT16  usCcSf1;      //BC input,first RU's SF
    UINT16  usCcSf2;      //BC input,second RU's SF
    UINT16  usGainFactor; //BC input,beta factor
    
    //HSDPA HsSich          
    UINT16  usHsSichChannelCode;       //BC input,HsSich RU's SF and usCode Number
    UINT16  usHsSichMidambleAllocMode; //BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsSichMidambleShift;//BC input,only in SpecificMidamble, use it  
    UINT16  usHsSichK;            //BC input,the max user number,the value = 1/2 fact value
    UINT16  usNackAckPoweroffset; //BC input,use to calculate Adjust factor
    UINT16  usNackAckFlag;        //BC input,Nack error flag
   
    //HSUPA E-PUCH or E-RUCCH                   
    UINT16  usHsupaChannelCode;      //BC input,Epch or Erucch RU's SF and usCode Number         
    UINT16  usHsupaModulateMode;     //BC input,modulation mode, 0:QPSK; 2:16QAM ,ERUCCH is QPSK 
    UINT16  usHsupaMidambleAllocMode;//BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsupaMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usHsupaK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usEucchNumber;           //Bc input, Eucchnumber=tpcnumber 
    INT16   sHsupaGainFactor;       //BC input, E-PUCH's gainfactor,Erucch no gainfactor     
           
    //BC out                    
    UINT16  usPowContrFlag; //BC input, for Channel usCode power control index
    UINT16  usSubFrameNum;
}TDS_UL_BCPARA_STRU;
typedef struct
{
    UINT16 usSfn;
    UINT16 usSwitch;
} TDS_UL_SWITCH_CHANGE_STRU;

typedef struct
{
    UINT32 ulTrchNum;
    UINT16 usTfIdx;
    UINT16 usTfNum;
}TDS_UL_TFOVERFLOW_ERR_STRU;

typedef struct
{
    UINT16 usTfcIdx;
    UINT16 usAllowedTfcNum;
}TDS_UL_TFCOVERFLOW_ERR_STRU;

typedef struct
{
    UINT16 usTrchNum;
    UINT16 usTbNum;
    UINT32 ulSumRmN;
}TDS_UL_ZEROPARA_ERR_STRU;

typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usTrchId;
}TDS_UL_INVTRCHID_ERR_STRU;


typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usCurState;
    UINT16 usIsRunning;
    UINT16 usEntry;         //0->CcMain, 1->CcSubMain
}TDS_UL_INVSTATUS_ERR_STRU;

typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usErrType;
    UINT16 usErrPara[4];
    UINT16 usBcExcTrace;
    UINT16 usResv;
}TDS_UL_BCPARA_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usEucchTsNum;
    UINT16 usEucchNum;
    UINT16 usRes;
} TDS_UL_EUCCH_NUM_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usScchIdIndex;
    UINT16 usAirSfn;
    UINT16 usCrc;
} TDS_UL_SICH_INVSTATE_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usTsNum;
    UINT16 usSendSfn;
    UINT16 usChnFlag;
} TDS_UL_EPUCH_CHNINVALID_ERR_STRU;


typedef struct
{
    UINT16 usZeroPaddingBefore;
    UINT16 usZeroPaddingAfter;
    UINT16 usZeroPaddingAll;
    UINT16 usZeroPaddingLim;
}TDS_UL_ZEROPADDING_LEN_OVERFLOW_STRU;

typedef struct
{
    UINT32 ulTfpTxIntFlag;
}TDS_UL_DMA_PARAERR_STRU;

typedef struct
{
    UINT32 ulPara[4];
}TDS_UL_PRIM_PARAERR_STRU;



typedef struct
{
    UINT32 ulTbSize;           //HSUPA������С
    UINT32 ulCrcPara;          //CRC����
    UINT32 ulEncPara;          //�������
    UINT32 ulInt1Para;         //һ�ν�֯����
    UINT32 ulRmNumPara;        //����ƥ��������
    UINT32 ulSysBitPara;       //ϵͳλУ�����
    UINT32 ulP1BitPara;        //��һУ��λ����
    UINT32 ulP2BitPara;        //�ڶ�У��λ����
    UINT32 ulNcNrPara;         //����ϵͳ������ռ��������������
    UINT32 ulAddrIniPara;      //����ƥ���У�������ʼ��ַ
    UINT32 ulInt2Para;         //���ν�֯���������Ų���
    UINT32 ulCtrlBits;         //HSUPA�Ĵ�������λ
    UINT32 ulIntEnable;        //�ж�ʹ�ܼĴ���
    UINT32 ulIntFlag;          //�ж�״̬�Ĵ���
} TDS_UL_EDCH_REG_BBP_PARA;;


typedef struct
{
    UINT32 ulErrId;
} TDS_UL_EDCH_PARA_ERR_STRU;


typedef struct
{
    UINT32 ulTdsUlErrBitMap;
    UINT32 ulCcErrBitMap;
    UINT32 ulBcErrBitMap;
    UINT32 ulChCtrlErrBitMap;
    UINT32 ulDriverBitMap;
} TDS_UL_ERROR_STAT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usResverd;
} TDS_UL_ERROR_EPUCH_CCLOST_STRU;

typedef struct
{
    UINT16 usLastCcSfn;
    UINT16 usCurCcSfn;
} TDS_UL_ERROR_DPCH_CCLOST_STRU;


typedef struct
{
    UINT16 usChnType;
    UINT16 usExpCcTs;
    UINT16 usCurTs;
    UINT16 usRes;
} TDS_UL_CC_DELAY_ERR_STRU;

typedef UINT8 TDS_TAS_NEW_STATE_ENUM_UINT8;



//���߷����л�ʱ�ϱ���OM�ṹ��
typedef struct _TDS_ASU_SWITCH_OM_STRU_{
    //����̬TAS200�յ��Ĳ���ֵ
    INT32        slGiveConnAnt0;
    INT32        slGiveConnAnt1;

    //idle��dch̬�յ��Ĳ��� �����ж�TAS250״̬
    INT32        slGiveConnRsrp;
    INT32        slGiveConnScale;
    INT32        slGiveIdleRsrp;
    INT32        slGiveIdleScale;
}TDS_ASU_SWITCH_OM_STRU;

typedef struct _TDS_ASU_DPDT_SWITCH_STRU_{
    TDS_ASU_SWITCH_OM_STRU      stSwitchOm;
    UINT32                      ulDpdtCurrState;//��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32                      ulBlankType;
    UINT32                      ulRsv;
}TDS_ASU_DPDT_SWITCH_STRU;

//����OM�ϱ���ASU�ṹ�壬����ͬTDS_ASU_DATA_STRU
typedef struct _TDS_ASU_OM_REPORT_STRU_{
    UINT32                         ulRsv3;
    UINT8                          ucInitPrachState;   //�Ƿ��ǳ�ʼ�������̬
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasNewState;      //��ǰTASҪת����״̬
    UINT16                         usCurrNGI_Scale;    //IDLE̬SCALE���� NOT GOOD�����Ĵ���

    UINT16                         usCurrNPI_Scale;    //IDLE̬SCALE���� NOT POOR�����Ĵ���
    UINT16                         usCurrNGI_Rsrp;     //IDLE̬RSCP���� NOT GOOD�����Ĵ���

    UINT16                         usCurrNPI_Rsrp;     //IDLE̬RSCP���� NOT POOR�����Ĵ���
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //��ǰTASת��ǰ��״̬
    UINT8                          ucRsv;

    UINT16                         usPrachFailNum;     //rach����ʧ�ܵ���������
    UINT16                         usCurrNGC;          //scale/rscp ͬʱnot good����������

    UINT16                         usCurrNPC;          //scale/rscp ͬʱnot poor����������
    UINT16                         usRsv2;
    TDS_ASU_SWITCH_OM_STRU         stGiveSubPara;
}TDS_ASU_OM_REPORT_STRU;

//TAS trace�ϱ����������ϱ���Ƶ��
typedef struct _TPHY_TAS_DPDT_SWITCH_STRU_{
    TDS_ASU_OM_REPORT_STRU     stTasOm;
    UINT32                     ulDpdtCurrState;  //��ǰ��dpdt״̬ 1-����  0-ֱͨ
    UINT32                     ulRsv;
}TPHY_TAS_DPDT_SWITCH_STRU;

typedef struct
{
    UINT16  usMsgID;//����PHY���Բ�һ��
	UINT16	usRatMode;//�μ�ԭ�и���ģʽ�Ķ���
	UINT16	usDpdtState;//0ֱͨ,1����
	INT16	ssAntValueMain;// �л����������߽����ź�����ֵ,����RSSI/RSCP/RSRP
	INT16	ssSwitchDelta;// �л�����ʱ���ּ�����Delta
	UINT16	usCdmaCtrlFlag;// ����CDMA�����л���� 1: ��ҿ�, 0: ����ҿ�
}TDS_OM_DPDT_STATE_IND_STRU;
//����״̬�仯ʱ�ϱ���OM
typedef struct _TDS_ASU_STATE_STRU_{
    UINT32       ulTasNewState;   //ת�����״̬
    UINT32       ulTasOldState;   //ת��ǰ��״̬
    UINT32       ulDpdtCurrState; //��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32       ulRsv0;
    UINT32       ulRsv1;
}TDS_ASU_STATE_STRU;

//����̬�ϱ����������߲���ֵOM
typedef struct _TDS_ASU_GIVE_RSCP_STRU_{

    //TAS200����̬�����ϱ���TASģ�������������л��ж�
    INT32       slGiveRscpAnt0;
    INT32       slGiveRscpAnt1;

    //��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32      ulDpdtCurrState;
    INT32       slGiveRscpAnt0Filter;
    INT32       slGiveRscpAnt1Filter;

    INT32       slGiveRscpDelta;
    UINT32      ulCnt;
    UINT32      ulRsv;
}TDS_ASU_GIVE_RSCP_STRU;

//����̬�ϱ�����PROTECT״̬ʱ������״̬
typedef struct _TDS_ASU_TAS_HYST_STRU_{
    UINT32      ulDpdtCurrState; //��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32      ulRsv;
}TDS_ASU_TAS_HYST_STRU;


//idle̬�ϱ�������������ֵOM
typedef struct _TDS_ASU_IDLE_STRU_{
    UINT32       ulRsv3;
    UINT8        ucInitPrachState;   //�Ƿ��ǳ�ʼ�������̬
    UINT8        ucTasNewState;
    UINT16       usCurrNGI_Rsrp;

    UINT16       usCurrNPI_Rsrp;
    UINT16       usCurrNGI_Scale;

    UINT16       usCurrNPI_Scale;
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //��ǰTASת��ǰ��״̬
    UINT8                          ucRsv;
}TDS_ASU_IDLE_STRU;

typedef struct _TDS_ASU_IDLE_RSCP_STRU_{
    INT16             slGiveRscp;
    INT16             slRsv1;
    UINT32            ulGiveScale;


    TDS_ASU_IDLE_STRU stTdsIdleGive;
    UINT16            usDpdtCurrState;
    UINT16            usRsv2;
}TDS_ASU_IDLE_RSCP_STRU;

//����̬�ϱ��������߲���ֵOM
typedef struct _TDS_ASU_DCH_RSCP_STRU_{
    UINT32        ulDchNewState;
    UINT32        ulDchOldState;
    UINT16        usCurrNGC;
    UINT16        usCurrNPC;
    INT16         slGiveRscp;
    UINT16        usDpdtCurrState;
    UINT32        ulGiveScale;
    UINT32        ulRsv;
}TDS_ASU_DCH_RSCP_STRU;

//searching�������ϱ���ʵʱ״̬OM
typedef struct _TDS_TAS_SEARCH_STATE_STRU_{
    UINT32      ulMidPwr;              /*�м䴰����*/
    UINT32      ulSfmCnt;              /*��������֡��*/
    UINT8       ucRcmRsped;            /*�Ƿ��յ���RCM��Ӧ*/
    UINT8       ucTasDominate;         /*�Ƿ���TAS����Ȩ*/

    UINT8       ucSearchDpdtValid;     /*���������о��Ƿ���Ҫ������*/
    UINT8       ucDpdtDone;            /*�Ƿ��Ѿ��й�����̬*/

    UINT8       ucTasSearch;           /*�Ƿ�TAS��*/
    UINT8       ucDpdtOld;             /*�ɵ�dpdt״̬*/

    UINT8       ucOmSource;            /*��ʶ��OM��Ƶ���ѻ���Ƶ�����ϱ���*/
    UINT8       ucRsv2;                /*����*/
    INT32       slRsv3;                /*����*/
}TDS_TAS_SEARCH_STATE_STRU;

//����TDS TAS��OM���ؿ���
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32             ulRptTasPeriod;
}TPHY_OM_REQ_TASCTRL_STAT_ENA_STRU;
typedef struct
{
    TPHY_OM_REQ_TASCTRL_STAT_ENA_STRU stRptTasEna;
    UINT32                            ulRptTasPeriodCnt;
}TPHY_OM_REQ_TAS_STAT_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDpdtEna;
    UINT16             usRev;
}TPHY_OM_REQ_DPDT_STAT_ENA_STRU;
/*TAS OM end*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


