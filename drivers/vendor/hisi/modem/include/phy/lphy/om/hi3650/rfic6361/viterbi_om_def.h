

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __VITERBI_OM_DEF_H__
#define __VITERBI_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
enum __LPHY_REQ_VITERBI__
{
    LPHY_REQ_VITERBI_STUB_DCI_ENA                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_VITERBI_RPT_CFI_ENA,
    LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA
};

/*�ϱ�����, �����ο�*/
typedef enum __LPHY_REQ_DECODE_PERIOD_RPT___
{
    PERIOD_1        = 0,
    PERIOD_2,
    PERIOD_4,
    PERIOD_8,
    PERIOD_16,
    PERIOD_32,
    PERIOD_64,
    PERIOD_128,
    PERIOD_256,
    PERIOD_512,
    PERIOD_1024,
    PERIOD_2048,
}LPHY_REQ_DECODE_PERIOD_RPT_ENUM;
typedef UINT16 LPHY_REQ_DECODE_PERIOD_RPT_ENUM_UINT16;

/*��׮DCI����*/
typedef enum
{
    OM_STUB_DCI1A    = 0,
    OM_STUB_DCIX,
}PDCCH_STUB_DCI_ENUM;
typedef UINT16 PDCCH_STUB_DCI_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM enStubDciEna;
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    PDCCH_STUB_DCI_ENUM_UINT16 enStubDciType;
    UINT16 usReserved;
}LPHY_REQ_VITERBI_STUB_DCI_ENA_STRU;

/*�ϱ�CFIֵ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptCfiEna;
}LPHY_REQ_VITERBI_RPT_CFI_ENA_STRU;

/*�ϱ�CFIͳ�ƿ���*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptCfiStatEna;
    UINT32 ulRptCfiStatPeriod;
}LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA_STRU;

/*�ϱ�PDCCH SINR����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchSinrEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA_STRU;

/*�ϱ�������Ȩ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchDlGrantEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA_STRU;

/*�ϱ�������Ȩ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchUlGrantEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA_STRU;

/*�ϱ�������Ȩ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchPwrGrantInfoEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA_STRU;

/*�ϱ���Ȩͳ�ƿ���*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchGrantStatEna;
    UINT32 ulRptPdcchGrantStatPeriod;
}LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA_STRU;

/*�ϱ�CCE��Ϣ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchCCEInfoEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA_STRU;

/*�ϱ�PDCCH BLER����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcBlerEna;
    UINT32 ulRptPdcchBlerPeriod;
}LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA_STRU;


/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_VITERBI_OM_CNF__
{
    LPHY_CNF_VITERBI_STUB_DCI_ENA                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_CNF, 0x1),
    LPHY_CNF_VITERBI_RPT_CFI_ENA,
    LPHY_CNF_VITERBI_RPT_CFI_STAT_ENA,
    LPHY_CNF_VITERBI_RPT_SINR_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_DL_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_UL_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_PWR_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_GRANT_STAT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_CCE_INFO_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_BLER_ENA
}LPHY_CNF_VITERBI_ENUM;


/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_VITERBI__
{
    LPHY_IND_VITERBI_RPT_CFI                = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_IND, 0x1),
    /* BEGIN: Added by yushujing, 2013/8/29   PN:chan_om*/
    LPHY_IND_VITERBI_RPT_CFI_SCELL,
    /* END:   Added by yushujing, 2013/8/29   PN:chan_om*/
    LPHY_IND_VITERBI_RPT_PDCCH_SINR,
    LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_UL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_PWR_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT,
    LPHY_IND_VITERBI_RPT_PDCCH_CCE_INFO,
    LPHY_IND_VITERBI_RPT_PDCCH_BLER
}LPHY_IND_VITERBI_ENUM;

/*�ϱ�CFIֵ*/
typedef struct __LPHY_VITERBI_RPT_CFI_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfi;
    UINT16 usCcFlag;
}LPHY_IND_VITERBI_RPT_CFI_STRU;

/*�ϱ�CFIͳ��*/
typedef struct __LPHY_VITERBI_RPT_CFI_STAT_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulCfi1Num;
    UINT32 ulCfi2Num;
    UINT32 ulCfi3Num;
    UINT32 ulCfiTotalNum;
}LPHY_IND_VITERBI_RPT_CFI_STAT_STRU;

/*�ϱ�PDCCH SINR*/
typedef struct
{
    UINT32 ulDlDciPower[2][3];    /*����DCI�������ֵ*/
    UINT32 ulUlDciPower;                        /*����DCI�������ֵ*/
    UINT32 ulRsNoisePower[2][2];     /*����0��1��ƽ�������������*/
    INT32  lDlDciSINR[2];         /*����DCI�Ÿ����*/
    INT32  lUlDciSINR;                          /*����DCI�Ÿ����*/
}PDCCH_SINR_INFO_STRU;

typedef struct __LPHY_VITERBI_RPT_PDCCH_SINR_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_SINR_INFO_STRU stPdcSinrInfo;
}LPHY_IND_VITERBI_RPT_PDCCH_SINR_STRU;

/*�ϱ�������Ȩ*/
typedef enum
{
    OM_DCI_0    = 0,
    OM_DCI_1,
    OM_DCI_1A,
    OM_DCI_1B,
    OM_DCI_1C,
    OM_DCI_1D,
    OM_DCI_2,
    OM_DCI_2A,
    OM_DCI_2B,
    OM_DCI_3,
    OM_DCI_3A
}PDCCH_GRANT_DCI_ENUM;
typedef UINT8 PDCCH_GRANT_DCI_ENUM_UINT8;

typedef enum
{
    OM_RA_RNTI    = 0,
    OM_P_RNTI,
    OM_SI_RNTI,
    OM_C_RNTI,
    OM_SPS_RNTI,
    OM_TC_RNTI,
    OM_TPC_PUCCH_RNTI,
    OM_TPC_PUSCH_RNTI
}PDCCH_GRANT_RNTI_ENUM;
typedef UINT8 PDCCH_GRANT_RNTI_ENUM_UINT8;

typedef struct __LPHY_VITERBI_RPT_PDCCH_DL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8 enDciType;
    UINT16 usCcFlag;
    UINT16 usRsv;
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucRbNum;
    UINT8  ucTpc;
    UINT8  ucDai;
    UINT8  ucHarqNum;
    UINT8  ucSwapFlag;
    UINT8  ucPrecodeInfo;
    UINT8  ucAggLevel;          /*·�����Ǳ�����*/
    UINT8  ucMcs1;
    UINT8  ucNdi1;
    UINT8  ucRV1;
    UINT8  ucNewReTrans1;       /*·�����Ǳ�����*/
    UINT32 ulTbSize1;
    UINT8  ucMcs2;
    UINT8  ucNdi2;
    UINT8  ucRV2;
    UINT8  ucNewReTrans2;       /*·�����Ǳ�����*/
    UINT32 ulTbSize2;
}LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT_STRU;

/*�ϱ�������Ȩ*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_UL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;     /*·�����Ǳ�����*/
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    UINT16 usAggLevel;                          /*SG����*/
    UINT8  ucHoppingFlag;
    UINT8  ucRbStart;
    UINT8  ucRbNum;
    UINT8  ucMcs;
    UINT8  ucNdi;
    UINT8  ucTpc;
    UINT8  ucDMRS;
    UINT8  ucUlIndex;
    UINT8  ucDai;
    UINT8  ucCqiReq;
    UINT32 ulTbSize;
    UINT8  ucNewReTrans;
    UINT8  ucRsd0;
    UINT16 usRsd1;
    /* END:   Added by yushujing, 2012/3/21 */
}LPHY_IND_VITERBI_RPT_PDCCH_UL_GRANT_STRU;

/*�ϱ�������Ȩ*/
typedef enum
{
    OM_PWR_GRANT_DCI_3    = 0,
    OM_PWR_GRANT_DCI_3A,
}PDCCH_PWR_GRANT_DCI_ENUM;
typedef UINT8 PDCCH_PWR_GRANT_DCI_ENUM_UINT8;

typedef enum
{
    OM_PWR_GRANT_TPC_PUCCH_RNTI    = 0,
    OM_PWR_GRANT_TPC_PUSCH_RNTI,
}PDCCH_PWR_GRANT_RNTI_ENUM;
typedef UINT8 PDCCH_PWR_GRANT_RNTI_ENUM_UINT8;

typedef struct __LPHY_VITERBI_RPT_PDCCH_PWR_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_PWR_GRANT_DCI_ENUM_UINT8  enDciType;
    UINT32 ulDciMsb;
    PDCCH_PWR_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucCceStart;       /*·�����Ǳ�����*/
    UINT16 usAggLevel;       /*·�����Ǳ�����*/
}LPHY_IND_VITERBI_RPT_PDCCH_PWR_GRANT_STRU;

/*�ϱ���Ȩͳ��*/
#define     OM_VITERBI_PDCCH_GRANT_STAT_LEN       44       /*Viterbi��Ȩͳ������������ݳ���, Bytes, ע����Ҫ��ӿ�ͬ��*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_GRANT_STAT_OM_IND__
{
    //UINT16 usCfi1Num;
    //UINT16 usCfi2Num;
    //UINT16 usCfi3Num;
    UINT16 ausCfiNum[3];
    UINT16 usRsd1;
    UINT16 usUlGrantNum;
    UINT16 usDlGrantNum;
    //UINT16 usCce1Num;
    //UINT16 usCce2Num;
    //UINT16 usCce4Num;
    //UINT16 usCce8Num;
    UINT16 usCceNum[4];
    UINT16 usDci0Num;
    UINT16 usDci1Num;
    UINT16 usDci1ANum;
    UINT16 usDci1BNum;
    UINT16 usDci1CNum;
    UINT16 usDci1DNum;
    UINT16 usDci2Num;
    UINT16 usDci2ANum;
    UINT16 usDci2BNum;
    UINT16 usDci3Num;
    UINT16 usDci3ANum;
    UINT16 usRsd2;
    //UINT32 ulAccuCfi1Num;
    //UINT32 ulAccuCfi2Num;
    //UINT32 ulAccuCfi3Num;
    UINT32 aulAccuCfiNum[3];
    UINT32 ulAccuUlGrantNum;
    UINT32 ulAccuDlGrantNum;
    //UINT32 ulAccuCce1Num;
    //UINT32 ulAccuCce2Num;
    //UINT32 ulAccuCce4Num;
    //UINT32 ulAccuCce8Num;
    UINT32 ulAccuCceNum[4];
    UINT32 ulAccuDci0Num;
    UINT32 ulAccuDci1Num;
    UINT32 ulAccuDci1ANum;
    UINT32 ulAccuDci1BNum;
    UINT32 ulAccuDci1CNum;
    UINT32 ulAccuDci1DNum;
    UINT32 ulAccuDci2Num;
    UINT32 ulAccuDci2ANum;
    UINT32 ulAccuDci2BNum;
    UINT32 ulAccuDci3Num;
    UINT32 ulAccuDci3ANum;
}LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT_STRU;

/*�ϱ�CCE��Ϣ*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_CCE_INFO_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucCceStart;
    UINT8  ucAggLevel;
    UINT8  ucRsd;
}LPHY_IND_VITERBI_RPT_PDCCH_CCE_INFO_STRU;

/*�ϱ�PDCCH BLER*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_BLER_OM_IND__
{
    UINT32 ulPdcchErrorNum[2];         /*����Ϊ���κ���Ч��DCI(����������)����һ�� -> �㷨����, �����������, ��DSP�Լ�����*/
    UINT32 ulPdcchTotalNum[2];         /*����ΪֻҪVDL�����ж���������һ��, ע�����DTX�������Ҫ�ۼ�, �����������ۼ�*/
    UINT32 ulPdcchAccuErrorNum[2];     /*�ۻ���*/
    UINT32 ulPdcchAccuTotalNum[2];     /*�ۻ���*/
}LPHY_IND_VITERBI_RPT_PDCCH_BLER_STRU;


/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_VITERBI_ENUM__
{
    /*PBCH, ID 1 - 31*/
    LPHY_TRACE_VITERBI_PBCH_DECODE_START                = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_VITERBI_PBCH_DECODE_FAIL,
    LPHY_TRACE_VITERBI_PBCH_DECODE_SUCCESS,

    /*PDCCH ID 32 - 4095*/
    LPHY_TRACE_VITERBI_CFI_FLOAT_INT_TRIGGERED          = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_VITERBI_PDCCH_DECODE_START,
    LPHY_TRACE_VITERBI_PDCCH_FLOAT_INT_TRIGGERED,
    LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS,
    LPHY_TRACE_VITERBI_PDCCH_RAR_TIMEOUT,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_ACTIVATE,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_ACTIVATE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_PDCCH_DTX,
    LPHY_TRACE_VITERBI_PDCCH_MULTI_RNTI_COEXIST,
    LPHY_TRACE_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST,
    LPHY_TRACE_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_RA_RNTI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PARA_UPDATE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PARA_UPDATE,
    LPHY_TRACE_VITERBI_LMAC_UL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_MCCH_CHANGE_NOTIFY,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPEC_CFG,
    LPHY_TRACE_VITERBI_PHICH_RESULT,
    LPHY_TRACE_VITERBI_CRC_OK_RETRAN,
    LPHY_TRACE_VITERBI_SWAP_VALID,
    LPHY_TRACE_VITERBI_MSG3_ACK_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_DL_DCI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_DCI0_RECEIVED,
    LPHY_TRACE_VITERBI_TC_RNTI_INVALID,
    /* END:   Added by yushujing, 2012/3/21 */
    LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL,
}LPHY_TRACE_VITERBI_ENUM;
typedef UINT16 LPHY_TRACE_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_DECODE_START_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulPbchCombineFlag;
    UINT32 ulPbchDecodeCnt;
    UINT32 ulPbchCfgPara;
}LPHY_TRACE_ERROR_VITERBI_PBCH_DECODE_STRU;

typedef struct __LPHY_VITERBI_PBCH_DECODE_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usTxAnteNum;
    UINT16 usSfn;
    UINT32 ulPbchData;
}LPHY_TRACE_VITERBI_PBCH_DECODE_SUCCESS_STRU;

/*PDCCH*/
typedef struct __LPHY_VITERBI_CFI_FLOAT_INT_TRIGGERED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfiValue;
    UINT16 usBandWidth;
}LPHY_TRACE_VITERBI_CFI_FLOAT_INT_TRIGGERED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DCI_PARSE_FINISHED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usDlBbpNum;
    UINT16 usDlDataGrantValid;
    UINT16 usDlGrantNum;
    UINT16 usDci0BbpNum;
    UINT16 usDci0CRntiSelNum;
    UINT16 usDci0TcRntiSelNum;
    UINT16 usDci0SpsRntiSelNum;
    UINT16 usDci0Num;
    UINT16 usDci0MacHarqNum;
    UINT16 ausDci0HarqInfo[2];
}LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_STRU;
typedef struct __LPHY_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usDlBbpNum;
    UINT16 usDlDataGrantValid;
    UINT16 usDlGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL_STRU;

typedef struct __LPHY_VITERBI_PDCCH_ORDER_TRIGGER_RA_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPreambleIdx;
    UINT16 usPrachMaskIdx;
    UINT32 ulDci1AMsb;
    UINT32 ulGrpValidNum;
}LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_STRU;

typedef struct __LPHY_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RAR_TIMEOUT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_RAR_TIMEOUT_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_ACTIVATE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_ACTIVATE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_RELEASE_STRU;

typedef struct
{
    UINT16                 usInitSysFn;                     /*�ó�ʼ��Ȩ����֡��*/
    UINT16                 usInitSubFn;                     /*�ó�ʼ��Ȩ������֡��*/
    UINT16                 usRecvSysFn;                     /*��ǰ����֡��*/
    UINT16                 usRecvSubFn;                     /*��ǰ������֡��*/
    UINT16                 usTranSysFn;                     /*��ǰ��Ч֡��*/
    UINT16                 usTranSubFn;                     /*��ǰ��Ч��֡��*/
    UINT16                 usOddEvenFlag;                   /*��żλ�ñ�־, 0: żλ��, 1: ��λ��*/
    INT16                  sSubFnOffset;                    /*��֡ƫ��, �������������1��4����²�Ϊ0*/
    UINT32                 ulNextPeriodPos;                 /*�´���Ч����λ��*/
    UINT32                 ulActualPeriodNum;               /*ʵ��������Ч����*/
    UINT32                 ulTotalPeriodNum;                /*������Ч����*/
    DCI0_STRU              stUlGrantInfo;
}OM_UL_SPS_INIT_GRANT_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_ACTIVATE_OM_TRACE__
{
    UINT32 ulHarqIndex;
    OM_UL_SPS_INIT_GRANT_STRU stUlSpsInitGrant;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_ACTIVATE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_RELEASE_STRU;

typedef enum
{
    PDCCH_RESPOND_DTX_TDD_SPEC    = 0,
    PDCCH_RESPOND_DTX_BF_SPEC,
    PDCCH_RESPOND_DTX_NO_GRANT
}PDCCH_RESPOND_DTX_ENUM;
typedef UINT16 PDCCH_RESPOND_DTX_TYPE_ENUM_UINT16;
typedef struct __LPHY_VITERBI_PDCCH_DTX_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_RESPOND_DTX_TYPE_ENUM_UINT16 enDtxRespType;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_DTX_STRU;

typedef struct __LPHY_VITERBI_PDCCH_MULTI_RNTI_COEXIST_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usRaRntiFlag;
    UINT16 usSpsRntiFlag;
    UINT16 usCTcRntiFlag;
    UINT16 usSiRntiFlag;
    UINT16 usPRntiFlag;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_MULTI_RNTI_COEXIST_STRU;

//typedef struct __LPHY_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST_OM_TRACE__
//{
//    UINT16 usSysFn;
//    UINT16 usSubFn;
//    UINT16 usRaRntiFlag;
//    UINT16 usSpsRntiFlag;
//    UINT16 usCTcRntiFlag;
//    UINT16 usSiRntiFlag;
//    UINT16 usPRntiFlag;
//    UINT16 usRsd;
//}LPHY_TRACE_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT16 usRntiValue;
}LPHY_TRACE_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RA_RNTI_RECEIVED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT16 usRntiValue;
    UINT16 usRarGrantCnt;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_RA_RNTI_RECEIVED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG_OM_TRACE__
{
    UINT16 usCurrSysFn;
    UINT16 usCurrSubFn;
    UINT16 usInitSysFn;
    UINT16 usInitSubFn;
    UINT32 ulNextPeriodPos;
    UINT32 ulActualPeriodNum;
    UINT32 ulTotalPeriodNum;
    UINT16 usSemiSchedInteval;
    UINT16 usGrantStatus;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG_OM_TRACE__
{
    OM_UL_SPS_INIT_GRANT_STRU stUlSpsInitGrant;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG_STRU;

/*�����а뾲̬�������ݽṹ*/
typedef struct
{
    UINT16 enSpsConfigEnabled;
    UINT16 enPersistSchedInterval;
    UINT16 usNumOfSpsProcess;
    UINT16 enTwoIntervalsCfgValidFlg;
}OM_SEMI_SCHED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_SPS_PARA_UPDATE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usSpsRntiValidFlg;
    UINT16 usSpsRntiValue;
    OM_SEMI_SCHED_STRU stDlSemiSched;
    OM_SEMI_SCHED_STRU stUlSemiSched;
}LPHY_TRACE_VITERBI_PDCCH_SPS_PARA_UPDATE_STRU;

/*����MACָʾ�뾲̬�ͷ����ݽṹ*/
typedef struct __LPHY_VITERBI_LMAC_UL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_LMAC_UL_SPS_RELEASE_STRU;

/*MCCH���֪ͨ���ݽṹ*/
typedef struct __LPHY_VITERBI_MCCH_CHANGE_NOTIFY_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usMbSfnFlag;
    UINT16 usMRntiValidFlag;
    UINT16 usMRntiValue;
    UINT16 ausDciValidFlag[2];
    UINT8  aucMcchNotifyData[2];
    UINT16 ausDciPower[2];
    UINT16 ausDciBlindTimes[2];
}LPHY_TRACE_VITERBI_MCCH_CHANGE_NOTIFY_STRU;

#define     MAX_TDD_UL_HARQ_NUM			(0x7)        	/*TDD�������HARQ������*/
#define 	MAX_TDD_UD_CFG_NUM     		(0x7)			/*TDD�����������ȸ���*/

typedef struct
{
	UINT16 usValidFlag;		/*�Ƿ���Ч��־*/
	UINT16 usInitFlag;
	UINT16 usCurrSendPos;
  	UINT16 usNextSendPos; 	/*��һ�η���λ��*/
	UINT16 usDci0RecvFlag;
	UINT16 usReserved;
}PDCCH_TDD_UL_SPEC_HARQ_STRU;

typedef struct
{
  	PDCCH_TDD_UL_SPEC_HARQ_STRU astTddUlSpecHarq[MAX_TDD_UL_HARQ_NUM];
}PDCCH_TDD_UL_SPEC_CFG_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPEC_CFG_OM_TRACE__
{
    UINT16 usCurrSysFn;
    UINT16 usCurrSubFn;
    UINT16 usTranSysFn;
    UINT16 usTranSubFn;
	UINT16 usHarqNum;
    UINT16 usTddUDConfig;
    PDCCH_TDD_UL_SPEC_CFG_STRU astTddUlSpecCfg[MAX_TDD_UD_CFG_NUM];
}LPHY_TRACE_VITERBI_PDCCH_UL_SPEC_CFG_STRU;

typedef struct __LPHY_VITERBI_PHICH_RESULT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPhichOrgNum;
    UINT16 usPhichNum;
	UINT16 usPhichIdx;
	UINT8  aucPhichResult[2];
}LPHY_TRACE_VITERBI_PHICH_RESULT_STRU;
typedef struct __LPHY_VITERBI_TRACE_REPORT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 usData[4];
}LPHY_TRACE_VITERBI_TRACE_REPORT_STRU;
/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum __LPHY_ERROR_VITERBI_ENUM__
{
    /*PBCH, ERROR ID 1 - 15*/
    LPHY_ERROR_VITERBI_PBCH_CELL_PARA_FAIL              = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_VITERBI_PBCH_DET_MODE_FAIL,
    LPHY_ERROR_VITERBI_PBCH_DECODE_UNFINISHED,

    /*PBCH, WARNING ID 16 - 31*/
    LPHY_WARNING_VITERBI_PBCH_RESERVED                  = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x10),

    /*PDCCH, ERROR ID 32 - 63*/
    LPHY_ERROR_VITERBI_PDCCH_NO_RNTI                    = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x20),
    LPHY_ERROR_VITERBI_PDCCH_INVALID_CFI,
    LPHY_ERROR_VITERBI_PDCCH_DEC_UNFINISHED,
    LPHY_ERROR_VITERBI_PHICH_NUM_OVERFLOW,
    LPHY_ERROR_VITERBI_PDCCH_TDD_UL_HARQ_OVERFLOW,

    /*PDCCH, WARNING ID 64 - 4095*/
    LPHY_WARNING_VITERBI_PDCCH_CHN_NUM_OVERFLOW         = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x40),
    LPHY_WARNING_VITERBI_PDCCH_NOISE_PWR_ZERO,
    LPHY_WARNING_VITERBI_SPS_PARA_MISMATCH,
}LPHY_ERROR_VITERBI_ENUM;
typedef UINT16 LPHY_ERROR_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_DET_MODE_FAIL_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulPbchDetMode;
}LPHY_ERROR_VITERBI_PBCH_DET_MODE_FAIL_STRU;

/*PDCCH*/
typedef struct __LPHY_VITERBI_PDCCH_NO_RNTI_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPdcChnValid;
    UINT16 usRntiValid;
}LPHY_ERROR_VITERBI_PDCCH_NO_RNTI_STRU;

typedef struct __LPHY_VITERBI_PDCCH_INVALID_CFI_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfiValue;
    UINT16 usBandWidth;
}LPHY_ERROR_VITERBI_PDCCH_INVALID_CFI_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DEC_UNFINISHED_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    /* BEGIN: Added by yushujing, 2013/1/4   PN:v7r2_mod*/
    UINT16 usPdcDecFinish;
    UINT16 usCfiValid;
    /* END:   Added by yushujing, 2013/1/4   PN:v7r2_mod*/
}LPHY_ERROR_VITERBI_PDCCH_DEC_UNFINISHED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_CHN_NUM_OVERFLOW_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulChanNum;
}LPHY_ERROR_VITERBI_PDCCH_CHN_NUM_OVERFLOW_STRU;

typedef struct __LPHY_VITERBI_PDCCH_NOISE_PWR_ZERO_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulNoisePwr;
    UINT32 ulSignalPwr;
}LPHY_ERROR_VITERBI_PDCCH_NOISE_PWR_ZERO_STRU;


/************************************************************
                           6. DEBUG���ݽṹ����
************************************************************/
/*Viterbi�ϱ������ݳ���, DW, ע����Ҫ��Ӳ���ӿ�ͬ��, ����ĿǰHSO��֧�������귽ʽ����, �˴������ϴ�ֵ, MPW: 0x204, Pilot: 0x230*/
#define     OM_VITERBI_MAX_RPT_PCELL_REG_IMG_LEN       ((0x378 - 0x200) / 4 + 1)
#define     OM_VITERBI_MAX_RPT_SCELL_REG_IMG_LEN       ((0x484 - 0x37c) / 4 + 1)
/* BEGIN: Added by yushujing, 2013/1/28   PN:v7r2_mod*/
#define     OM_VITERBI_CFG_REG_IMG_LEN                 ((0xbc - 0x5c) / 4 + 1)
/* END:   Added by yushujing, 2013/1/28 */

typedef enum __LPHY_DEBUG_VITERBI_ENUM__
{
    /*PBCH, INFO ID  1 - 63*/
    LPHY_DEBUG_VITERBI_PBCH_GAP                          = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DEBUG, 0x1),

    /*PDCCH, INFO ID 64 - 4095*/
    LPHY_DEBUG_VITERBI_PDCCH_DCI_LEN                     = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DEBUG, 0x40),
    LPHY_DEBUG_VITERBI_PDCCH_SEARCH_SPACE,
    LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE,
    LPHY_DEBUG_VITERBI_PDCCH_CDRX_HARQ_RTT,
    LPHY_DEBUG_VITERBI_PDCCH_CFG_REGS_IMAGE,
    LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL,
}LPHY_DEBUG_VITERBI_ENUM;
typedef UINT16 LPHY_DEBUG_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_GAP_OM_DEBUG__
{
    UINT16 usPrevSfn;
    UINT16 usCurrSfn;
}LPHY_DEBUG_VITERBI_PBCH_GAP_STRU;

/*PDCCH*/
typedef enum
{
    RNTI_INVALID = 0,
    RNTI_EXIST,
    RNTI_VALID,
    RNTI_BUTT
}OM_RNTI_STATUS_ENUM;
typedef UINT16 OM_RNTI_STATUS_ENUM_UINT16;

typedef struct
{
    OM_RNTI_STATUS_ENUM_UINT16 enRntiStatus;
    UINT16 usRntiValue;
}OM_RNTI_STRU;

typedef struct
{
    UINT32       ulRntiValidFlag;  /*����RNTI��־*/
    OM_RNTI_STRU stRaRnti;         /*RA-RNTI*/
    OM_RNTI_STRU stPRnti;          /*P-RNTI*/
    OM_RNTI_STRU stSiRnti;         /*SI-RNTI*/
    OM_RNTI_STRU stCRnti;          /*C-RNTI*/
    OM_RNTI_STRU stSpsRnti;        /*SPS-RNTI*/
    OM_RNTI_STRU stTcRnti;         /*TC-RNTI*/
    OM_RNTI_STRU stPucchTpcRnti;   /*PUCCH-TPC-RNTI*/
    OM_RNTI_STRU stPuschTpcRnti;   /*PUSCH-TPC-RNTI*/
    OM_RNTI_STRU stMRnti;          /*M-RNTI*/
}OM_RNTI_LIST_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DCI_LEN_OM_DEBUG__
{
    UINT16            usDci1CLen;
	/* BEGIN: Added by yushujing, 2013/1/28   PN:v7r2_mod*/

    UINT16            usDci01ACommLen;
    UINT16            ausDci01AUeLen[2];
    UINT16            ausDciXLen[2];
    //UINT16            ausTranMode[2];
	/* END:   Added by yushujing, 2013/1/28 */

    OM_RNTI_LIST_STRU stRntiList;
}LPHY_DEBUG_VITERBI_PDCCH_DCI_LEN_STRU;

typedef struct __LPHY_VITERBI_PDCCH_SEARCH_SPACE_OM_DEBUG__
{
    UINT16 usMiBlindDetFlag;
    UINT16 usStartLocUeL1;
    UINT16 usStartLocUeL2;
    UINT16 usStartLocUeL4;
    UINT16 usStartLocUeL8;
    UINT16 usSrchTimesUeL1;
    UINT16 usSrchTimesUeL2;
    UINT16 usSrchTimesUeL4;
    UINT16 usSrchTimesUeL8;
    UINT16 usSrchTimesBdMiZero;
    UINT16 usSrchTimesBdMiOne;
    UINT16 usSrchTimesBdMiTwo;
    UINT16 usNcceNum;
    UINT16 usRsd;
}LPHY_DEBUG_VITERBI_PDCCH_SEARCH_SPACE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RPT_REGS_IMAGE_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulIntAlarm;
    UINT32 aulRegImg[OM_VITERBI_MAX_RPT_PCELL_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 aulRegImg[OM_VITERBI_MAX_RPT_SCELL_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL_STRU;
/*HARQ RTT Timer��־*/
typedef enum
{
    HARQ_RTT_DL = 0,
    HARQ_RTT_UL_DCI0,
    HARQ_RTT_UL_PHICH,
}HARQ_RTT_TIMER_TYPE_ENUM;
typedef UINT16 HARQ_RTT_TIMER_TYPE_ENUM_UINT16;

typedef struct
{
    UINT16 usHarqRttTimerValidFlag;
    HARQ_RTT_TIMER_TYPE_ENUM_UINT16 enHarqRttTimerType;
    UINT16 usHarqNum;
    UINT16 usHarqRttTimer;
    UINT16 usNewTranFlag;
    UINT16 usSemiGrantFlag;
}LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU stDlHarqRtt;
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU astUlHarqRttDci0[2];
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU astUlHarqRttPhich[2];
}LPHY_PDCCH_CDRX_HARQ_RTT_STRU;
/* BEGIN: Added by yushujing, 2013/1/28   PN:v7r2_mod*/
typedef struct __LPHY_VITERBI_PDCCH_CFG_REGS_IMAGE_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulCaPara;
    UINT32 aulRegImg[OM_VITERBI_CFG_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_CFG_REGS_IMAGE_STRU;

/* END:   Added by yushujing, 2013/1/28 */



#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __VITERBI_OM_DEF_H__ */


