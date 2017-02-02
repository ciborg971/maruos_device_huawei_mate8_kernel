

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "om_base_def.h"
#include "LMspLPhyInterface.h"
/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __EQUIP_OM_DEF_H__
#define __EQUIP_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                    1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
    LPHY_REQ_EQUIP_BT_REQUEST           = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_REQ_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM usTxCmpOmSwitch;
    OM_REQ_ENABLE_ENUM usRxCmpOmSwitch;
}LPHY_OM_REQ_EQUIP_STRU;

/************************************************************
                    2. CNF���ݽṹ����
************************************************************/


/************************************************************
                    3. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LTE_CELL_SEARCH_SUCCESS,
    LTE_CELL_MAIN_CELL_CAMP_SUCCESS,
}NCIT_OM_REPORT_ENMU;
typedef UINT16 LTE_NCIT_OM_REPORT_UNIT16;

/*
**BT OM �ϱ�IND
*/
typedef enum
{
    LPHY_IND_EQUIP_BT_CMP_TX_REPORT = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_EQUIP_BT_CMP_RX_REPORT,
    LPHY_IND_EQUIP_ET_MRX_DDR_DATA,
    LPHY_IND_EQUIP_ET_LUT_REPORT,
}LPHY_EQUIP_BT_CMP_IND_ENUM;

/*
**BT OM �ϱ�TRACE
*/
typedef enum
{
    LPHY_IND_EQUIP_FREQ_COMP_REPORT = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_TRACE, 0x1),
    LPHY_IND_EQUIP_TX_COMP_REPORT,
}LPHY_EQUIP_BT_CMP_TRACE_ENUM;

typedef enum
{
	 LPHY_REQ_EQUIP_CT_REQUEST           = OM_CMD_ID(LPHY_CT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_CT_REQ_ENUM;

/*
**NCIT OM �ϱ�TRACE
*/
typedef enum
{
    LPHY_TRACE_EQUIP_NCIT_PRITASK_REPORT = OM_CMD_ID(TPHY_NCIT_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_EQUIP_NCIT_UP_START_REPORT,
    LPHY_TRACE_EQUIP_NCIT_UP_END_REPORT,
    LPHY_TRACE_EQUIP_NCIT_DOWN_START_REPORT,
    LPHY_TRACE_EQUIP_NCIT_DOWN_END_REPORT,
}LPHY_EQUIP_NCIT_CMP_TRACE_ENUM;


typedef struct
{
    UINT16 usCalMaxPwr;      /*����У׼�����������������*/
    INT16  sPwrCalc;         /*���㹦��*/
    UINT16 usPbVal;          /*AMPR��MPR����ֵ*/
    INT16  sSarMax;          /*��SAR���޶��������*/
    UINT16 usChType;         /*�ŵ�����*/
    INT16  sPowerIn;
    UINT16 usPdmVal;
    INT16  sAptCmp;
    INT16  sPwrAftPd;
    UINT16 usTxFreqCmpNum;   /*����õĲ���Ƶ�����*/
    UINT32 ulCentPoint;      /*��ǰ���������Ƶ��*/
    INT16  sFreqCmpVal;
    INT16  sTempIndex;
    INT16  sCurMaxPower;
    UINT16 usTempVal;
    UINT16 usPaLevel;        /*PA��λ*/
    UINT16 usDbbAttWord;
    UINT16 usAbbAttWord;
    UINT16 usRfCode;         /*RF������*/
    INT16  sFilterCmp;
    INT16  sBandWithCmp;
    UINT16 usPdDela;
    UINT16 usRsv2;
}BT_TX_CMP_OM_INFO_STRU;

typedef struct
{
    UINT16 usAgcLevel;
	UINT16 usBandWidth;
    UINT16 usHighFreq;
    UINT16 usLowFreq;
    INT16  usTempCompValResult;
    INT16  usFreqCalNum;
    UINT16 usFreqGetNum;
	UINT16 usGetFreqList[FREQ_MAX_NUM];
	UINT16 usGetFreqCompList[FREQ_MAX_NUM];
    UINT16 usFreq;
    UINT16 sCmpVal;
	UINT16 usFreqCmpValResult;

}BT_RX_CMP_OM_INFO_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulLowFreq;
    UINT32 ulHighFreq;
    UINT32 ulCenterFreq;
    UINT32 ulTemp;
    UINT32 sFilterCmp;
}OM_REPORT_FREQ_COMPENSATION_STRU;

/*
**BT OM �ϱ�TRACE
*/
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    INT16  sPowIn;
    UINT16 usPaLevel;
    UINT16 usFreq;
    UINT16 usBandWidth;

    INT16  sFreqComp;
    INT16  sTempComp;
    INT16  sGainstatusIndex;
    INT16  sBBAtt;
    INT16  sDbbAtt;
    UINT16 usRfCode;
    UINT16 usDbbCode;
    UINT16 usRes;
}OM_REPORT_BT_COMPENSATION_STRU;
/*
**NCIT OM �ϱ�TRACE�ṹ��
*/
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulSubFnCnt;
    UINT32 usSegmentCnt;
}OM_REPORT_NCIT_SEGMENT_CNT_STRU;

/*
**NCIT OM �ϱ�TRACE�ṹ��
*/
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulFnCnt;
}OM_REPORT_NCIT_FRAME_CNT_STRU;
/************************************************************
                    4. TRACE���ݽṹ����
************************************************************/

/************************************************************
                    5. ERROR���ݽṹ����
************************************************************/
typedef struct
{
    OM_REQ_ENABLE_ENUM usCtTxCalOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalSyncOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalSsiReportOmSwitch;
    OM_REQ_ENABLE_ENUM usCtTrigOmSwitch;
    OM_REQ_ENABLE_ENUM usCtApcGainCommReqOmSwitch;
}LPHY_OM_REQ_EQUIP_CT_STRU;
typedef struct LPHY_EQUIP_GET_TX_RF_CODE_REQ
{
    UINT16 usRfCodeNum;
    UINT16 ausRfCode[TX_POW_MAX_NUM]; /*Rf������*/
}LPHY_EQUIP_GET_TX_RF_CODE_REQ_STRU;
typedef struct LPHY_EQUIP_DBB_CODE_REQ
{
    UINT16 usDbbCodeNum;     /*DBB��������*/
    UINT16 usDbbCode;        /*DBB������*/
}LPHY_EQUIP_DBB_CODE_REQ_STRU;
typedef struct LPHY_EQUIP_CT_APC_GAIN_REQ_PARA
{
    UINT16 usWave;                                 /* CW����0�� LTE����1  */
    UINT16 usSegment;                              /* ���͵�һ����ʱ������λms  */
    UINT16 usRsv;
	UINT16 usFreqNum;
    UINT16 ausFreqList[FREQ_MAX_NUM];
    UINT32 ulTxRfCodeNum;                          /*����RF������*/
    UINT16 ausTxRfCode [TX_POW_MAX_NUM];           /*���书�ʿ����֣�����RF��IF������*/
    UINT16 usDbbNum;                               /**/
    UINT16 usDbbCode;                              /*DBB���ʿ�����*/
    UINT32 ulPaNum;
    UINT8  aucPaLevel[TX_POW_MAX_NUM];
    UINT32 ulPwrNum;
    INT16  sPowerTable[TX_POW_MAX_NUM];            /*����LIST*/
    UINT16 usAptEnbFlg;
    UINT16 usCalAptFlg;
    UINT32 ulPdEnbFlg;
    UINT16 usVgaCfg;
    UINT16 usDacCfg;
}LPHY_EQUIP_CT_APC_GAIN_REQ_STRU;
typedef struct LPHY_EQUIP_TRIG_INPUT_PARA
{
    UINT16 usSubFramNum;        /*��֡��*/
    UINT16 usSysFramNum;        /*ϵͳ֡��*/
    UINT16 usBandIndx;          /*Band����*/
    UINT16 usAbbChan;           /*ABBͨ��ѡ��*/
    UINT16 usTxRfCode;          /*Rf������*/
    UINT16 usFreqInfo;          /*Ƶ����Ϣ*/
    UINT8  ucPaLevel;           /*PA��λ��Ϣ*/
    UINT8  ucRsv;
    UINT16 usDBBIndex;
}LPHY_EQUIP_TRIG_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_SYNC_INPUT_PARA
{
    UINT16 usSubFramNum;         /*��֡����*/
    UINT16 usSysFramNum;         /*ϵͳ֡��*/
    UINT16 usFreqInfo;           /*Ƶ����Ϣ*/
    UINT16 usGainStateIndex;     /*���浵λ����*/
    UINT16 usTxRfCode;           /*Rf������*/
    UINT16 usTxDBBCode;          /*DBB������*/
    UINT8  ucPaLevel;            /*PA��λ��Ϣ*/
    UINT8  usResv;
    UINT16 usResv2;      /*ͳ��ϵͳ֡��*/
}LPHY_EQUIP_RX_SYNC_INPUT_STRU;

/*����У׼��Ϣ�ϱ��ṹ��*/
typedef struct LPHY_EQUIP_TX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*��֡��*/
    UINT16 usSysFramNum;        /*ϵͳ֡��*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqNum;           /*Ƶ�����*/
    UINT16 usFrequnceCnt;     /*Ƶ����������*/
    UINT16 usFreqInfo;          /*Ƶ����Ϣ*/
    UINT16 usGainStateNum;      /*У׼��λ��*/
    UINT16 usGainStateIndex;    /*���浵λ����*/
    UINT16 usTxRfCode;          /*Rf������*/
    UINT8  ucPaLevel;           /*PA��λ��Ϣ*/
    UINT16 usBandIndx;          /*Band����*/
    UINT16 usAbbChan;           /*ABBͨ��ѡ��*/
    UINT8  ucResv;
    UINT16 usResv;
}LPHY_EQUIP_TX_CAL_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*��֡��*/
    UINT16 usSysFramNum;        /*ϵͳ֡��*/
    UINT16 usCtSubFramCnt;
    UINT16 usRxFreqNum;
    UINT16 usRxFreqCnt;
    UINT16 usRxFreqInfo;        /*Ƶ����Ϣ*/
    UINT16 usRxGainNum;
    UINT16 usRxGainCnt;       /*���浵λ����*/
    UINT16 usRxRfCode;          /*Rf������*/
    UINT16 usRxGain;            /*��������*/
    UINT16 usBand;              /*Band��Ϣ*/
    UINT16 usResv;
}LPHY_EQUIP_RX_CAL_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_RSSI_PARA
{
    UINT16 usSubFramNum;        /*��֡��*/
    UINT16 usSysFramNum;        /*ϵͳ֡��*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqCnt;           /*Ƶ�ʼ���*/
    UINT16 usGainCnt;           /*���浵λ����*/
    UINT16 usRxSsiAnt1PowSum;    /*����1���չ���ͳ��*/
    UINT16 usRxSsiAnt2PowSum;    /*����2���չ���ͳ��*/
}LPHY_EQUIP_RX_RSSI_STRU;
typedef enum LTE_EQUIP_CT_OM_RPT_ID
{
    LPHY_EQUIP_CT_TX_CAL_REPORT = OM_LCMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x100),
    LPHY_EQUIP_CT_RX_CAL_REPORT,
    LPHY_EQUIP_CT_RX_CAL_ANTPOW_REPORT,
    LPHY_EQUIP_CT_RX_SYNC_REPORT ,
    LPHY_EQUIP_RFCODE_REQ_REPORT ,
    LPHY_EQUIP_DBBCODE_REQ_REPORT ,
    LPHY_EQUIP_CT_TRIG_REPORT,
    LPHY_EQUIP_CT_APC_GAIN_COMM_REQ_REPORT,
    LPHY_EQUIP_CT_TX_NV_INFO_REPORT,
	LPHY_EQUIP_CT_RX_NV_INFO_REPORT
}LTE_EQUIP_CT_OM_RPT_ID_ENUM;

typedef struct
{
    INT16 sHigh2MidThre;
	INT16 sMid2HighThre;
	INT16 sMid2LowThre;
	INT16 sLow2MidThre;
}OM_NV_PA_LEVEL_THRE_STRU;
typedef struct
{
    UINT16 usFreqNum;
    UINT16 usRes;
    UINT16 ausTxCalFreqList[RF_TX_FREQ_NUM];           /*TXУ׼Ƶ�㣬�ɵ͵��߷���*/
    INT16  asTxCalCompListWired[RF_TX_FREQ_NUM];       /*TX����Ƶ�ʲ�����ʵ������д Ĭ��ȫ0��1/8db*/
    INT16  asTxCalCompListWireless[RF_TX_FREQ_NUM];    /*TX����Ƶ�ʲ�����ʵ������д Ĭ��ȫ0��1/8db*/
}OM_NV_LTE_TX_CAL_LIST_STRU;
typedef struct
{
    UINT16  ausGainNumsNeedCalEachPaLevel[RF_PA_GAIN_NUM];/*ÿ��pa��λ��ҪУ׼rfgain �ĸ���*/
    UINT16  sDbbValue;
    UINT16  ausLteApcTable[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}OM_NV_LTE_APC_TABLE_STRU;
typedef struct
{
    INT16  asPaDiff[RF_PA_GAIN_NUM];/*pa�е͵�λ�͸ߵ�λ�Ĺ��ʲ��һ��ֵ��0  �� 0 -5 -10*/
    UINT16 usRes;
    INT16  asRfDefaultPower[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}OM_NV_LTE_DEFAULT_POW_TABLE_STRU;
typedef struct
{
    UINT16      usFreqNum;
    UINT16      usRes;
    UINT16      usRxCalibrFreqList[RF_RX_FREQ_NUM];            /*RxƵ��У׼��*/
}OM_NV_LTE_RX_CAL_LIST_STRU;
typedef struct
{
    UINT8     ucAGCAcsMinGainZ;
    UINT8     ucAGCNbMinGainY;
    UINT8     ucReserved;
    UINT8     ucDefaultGain0;
    UINT8     ucDefaultGain1;
    UINT8     ucDefaultGain2;
    UINT16    usReserved;
    UINT32     ulAGCGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCAcsGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCNbGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulRFIdxTable[2][AGC_MAX_GAIN_LEVEL];
    INT16      sRFErrorTable[2][AGC_MAX_GAIN_LEVEL];
}OM_NV_AGC_BAND_GAIN_TABLE_STRU;
typedef struct LPHY_EQUIP_CT_TX_PATH_NV_PARA
{
    UINT16                          usBand;
	OM_NV_PA_LEVEL_THRE_STRU           stPaThre;          /*PA��λ����*/
    OM_NV_LTE_TX_CAL_LIST_STRU         stTxCalFreqListLab;      /*TXУ׼Ƶ�㣬�ɵ͵��߷���*/
    OM_NV_LTE_APC_TABLE_STRU           stApcTableLab;           /*k3v5_bzj apc teble pre band*/
    OM_NV_LTE_DEFAULT_POW_TABLE_STRU   stTxDefaultPowLab;       /*k3v5_bzj rfĬ�Ϸ��书�ʣ���У׼�����ж�ʹ��*/
}LPHY_EQUIP_CT_TX_PATH_NV_INPUT_STRU;
typedef struct LPHY_EQUIP_CT_RX_PATH_NV_PARA
{
    UINT16                          usBand;
    OM_NV_LTE_RX_CAL_LIST_STRU         stRxCalFreqListLab;
    OM_NV_AGC_BAND_GAIN_TABLE_STRU         stRxAgcTableLab;
}LPHY_EQUIP_CT_RX_PATH_NV_INPUT_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif 

