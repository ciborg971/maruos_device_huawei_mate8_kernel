

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


/*BEGIN: Added by humin, 20150504*/
#define     MAX_CELL_NUM_DL                    LPHY_FEATURE_MAX_CARRIER_NUM// 4
#if 0
#if    (MAX_CELL_NUM_DL !=  LPHY_FEATURE_MAX_CARRIER_NUM)
    #error "(MAX_CELL_NUM_DL !=  LPHY_FEATURE_MAX_CARRIER_NUM)"
#endif
#endif
/*END: Added by humin, 20150504*/
/*�궨��*/
//#define UL_MAX_CELL_NUM 2
#define DL_MAX_CELL_NUM 4
#define MAX_DL_CHAN_NUM 3
#define MAX_RX_NUM      4
#define UL_MAX_CELL_NUM LPHY_MAX_UL_CARRIER_NUM
#define UL_MAX_TB_NUM 2

#define OM_UL_MAX_CELL_NUM 2



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
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA,
    LPHY_DT_VITERBI_RPT_CFI_INFO_REQ               = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_REQ, 0x100),
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ,
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
    //LPHY_IND_VITERBI_RPT_CFI_SCELL,
    /* END:   Added by yushujing, 2013/8/29   PN:chan_om*/
    LPHY_IND_VITERBI_RPT_PDCCH_SINR       = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_IND, 0x3),
    LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_UL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_PWR_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT,
    LPHY_IND_VITERBI_RPT_PDCCH_CCE_INFO,
    LPHY_IND_VITERBI_RPT_PDCCH_BLER
}LPHY_IND_VITERBI_ENUM;

/*�ϱ�CFIֵ*/

typedef struct __LPHY_VITERBI_CFI_INFO_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 ulCfi;
}LPHY_VITERBI_CFI_INFO_STRU;

typedef struct __LPHY_VITERBI_RPT_CFI_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    //UINT16 usCfi;
    //UINT16 usCcFlag;
    LPHY_VITERBI_CFI_INFO_STRU astCfiInfo[DL_MAX_CELL_NUM];
}LPHY_IND_VITERBI_RPT_CFI_STRU;




/*�ϱ�CFIͳ��*/
typedef struct __LPHY_VITERBI_RPT_CFI_STAT_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulCfi1Num[DL_MAX_CELL_NUM];
    UINT32 ulCfi2Num[DL_MAX_CELL_NUM];
    UINT32 ulCfi3Num[DL_MAX_CELL_NUM];
    UINT32 ulCfiTotalNum[DL_MAX_CELL_NUM];
}LPHY_IND_VITERBI_RPT_CFI_STAT_STRU;

/*�ϱ�PDCCH SINR*/
typedef struct
{
    UINT32 ulDlDciPower[DL_MAX_CELL_NUM][MAX_DL_CHAN_NUM];    /*[CC��][�ŵ���]����DCI�������ֵ*/
    UINT32 ulUlDciPower[OM_UL_MAX_CELL_NUM];       /*����DCI�������ֵ*/
    UINT32 ulRsNoisePower[DL_MAX_CELL_NUM][MAX_RX_NUM];  /*[CC��][������]����0\1\2\3��ƽ�������������*/
    INT32  lDlDciSINR[DL_MAX_CELL_NUM];         /*[CC��]����DCI�Ÿ����*/
    INT32  lUlDciSINR[OM_UL_MAX_CELL_NUM];                          /*����DCI�Ÿ����*/
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
    OM_DCI_2C,
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


/*typedef enum
{
    MCS_QPSK = 0,
    MCS_16QAM,
    MCS_64QAM,
    MCS_QM_INVALID
}MCS_QM_ENUM;
typedef UINT16 DL_MCS_QM_ENUM_UINT16;
*/

typedef enum __PDSCH_TRANS_SCHEME_OM_ENUM__
{
    OM_PORT0 = 0,
    OM_PORT5,
    OM_PORT7,
    OM_PORT8,
    OM_PORT78,
    OM_PORT789,
    OM_PORT78910,
    OM_SFBC,
    OM_OPEN_LOOP_SM,
    OM_CLOSE_LOOP_SM,
    OM_MU_MIMO,
    OM_PMCH_SIMO,
    OM_UNKNOWN_TRANS_SCHEME
}PDSCH_TRANS_SCHEME_OM_ENUM;
typedef UINT16 PDSCH_TRANS_SCHEME_OM_ENUM_UINT16;

typedef struct
{
    UINT8  ucMcs;
    UINT8  ucNdi;
    UINT8  ucNewReTrans;       /*·�����Ǳ�����*/
    UINT8  ucRv;
    PDSCH_TRANS_SCHEME_OM_ENUM_UINT16  usTransScheme;          /*����ÿ���ִ��䷽ʽ�����д˲�����Ч*/
    MCS_QM_ENUM_UINT16  enModSched;
    UINT32 ulTbSize;
}DCI_TB_PARA;
/*
typedef struct
{
    UINT16 usCcIdx;
    UINT16 usSysFn;
    UINT8  ucSubFn;
    UINT8  ucRbStart;
    UINT8  ucRbNum;
    UINT8  ucHarqId;
    DCI_TB_PARA astTbPara[2];
}DCI_PARA;  */              /*·���������������װΪ�ӽṹ*/

typedef struct __LPHY_VITERBI_RPT_PDCCH_DL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8 enDciType;

    UINT16 usCcIdx;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucHarqId;

    UINT32 ulDciMsb;
    UINT32 ulDciLsb;

    UINT8  ucRbNum;
    UINT8  ucRbStart;
    UINT8  ucTpc;
    UINT8  ucDai;

    UINT8  ucSwapFlag;
    UINT8  ucPrecodeInfo;
    UINT8  ucAggLevel;          /*·�����Ǳ�����*/
    UINT8  ucRsv;

    DCI_TB_PARA astTbPara[2];
    //UINT8  ucMcs1;
    //UINT8  ucNdi1;
    //UINT8  ucRV1;
    //UINT8  ucNewReTrans1;       /*·�����Ǳ�����*/
    //UINT32 ulTbSize1;
    //UINT8  ucMcs2;
    //UINT8  ucNdi2;
    //UINT8  ucRV2;
    //UINT8  ucNewReTrans2;       /*·�����Ǳ�����*/
    //UINT32 ulTbSize2;
}LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT_STRU;

/*�ϱ�������Ȩ*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_UL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    UINT8  ucRsv0;

    UINT16 usCcIdx;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;     /*·�����Ǳ�����*/
    UINT8  ucHarqId;

    UINT32 ulDciMsb;
    UINT32 ulDciLsb;

    UINT16 usAggLevel;                          /*SG����*/
    UINT8  ucHoppingFlag;
    UINT8  ucRbStart;

    UINT8  ucRbNum;
    UINT8  ucTpc;
    UINT8  ucDMRS;
    UINT8  ucUlIndex;

    UINT8  ucDai;
    UINT8  ucCqiReq;
    UINT16  usRsv1;

    DCI_TB_PARA astTbPara[2];
    //UINT32 ulTbSize;
   // UINT8  ucNewReTrans;
    //UINT8  ucRsd0;
    //UINT16 usRsd1;
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

#define     CFI_TYPE_NUM       3
#define     CCE_TYPE_NUM       4
typedef struct
{
    UINT16 ausCfiNum[CFI_TYPE_NUM];
    UINT16 usRsd1;
    UINT16 usUlGrantNum;
    UINT16 usDlGrantNum;
    UINT16 usCceNum[CCE_TYPE_NUM];
    UINT16 usDci0Num;
    UINT16 usDci1Num;
    UINT16 usDci1ANum;
    UINT16 usDci1BNum;
    UINT16 usDci1CNum;
    UINT16 usDci1DNum;
    UINT16 usDci2Num;
    UINT16 usDci2ANum;
    UINT16 usDci2BNum;
    UINT16 usDci2CNum;
    UINT16 usDci3Num;
    UINT16 usDci3ANum;

    /*�ۻ�ֵ�������ڲ�����0*/
    UINT32 aulAccuCfiNum[CFI_TYPE_NUM];
    UINT32 ulAccuUlGrantNum;
    UINT32 ulAccuDlGrantNum;
    UINT32 ulAccuCceNum[CCE_TYPE_NUM];
    UINT32 ulAccuDci0Num;
    UINT32 ulAccuDci1Num;
    UINT32 ulAccuDci1ANum;
    UINT32 ulAccuDci1BNum;
    UINT32 ulAccuDci1CNum;
    UINT32 ulAccuDci1DNum;
    UINT32 ulAccuDci2Num;
    UINT32 ulAccuDci2ANum;
    UINT32 ulAccuDci2BNum;
    UINT32 ulAccuDci2CNum;
    UINT32 ulAccuDci3Num;
    UINT32 ulAccuDci3ANum;
}PDCCH_GRANT_STAT_PARA_STRU;

typedef struct __LPHY_VITERBI_RPT_PDCCH_GRANT_STAT_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_GRANT_STAT_PARA_STRU astPdcPara[DL_MAX_CELL_NUM];
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
    UINT32 ulPdcchErrorNum[DL_MAX_CELL_NUM];         /*����Ϊ���κ���Ч��DCI(����������)����һ�� -> �㷨����, �����������, ��DSP�Լ�����*/
    UINT32 ulPdcchTotalNum[DL_MAX_CELL_NUM];         /*����ΪֻҪVDL�����ж���������һ��, ע�����DTX�������Ҫ�ۼ�, �����������ۼ�*/
    UINT32 ulPdcchAccuErrorNum[DL_MAX_CELL_NUM];     /*�ۻ���*/
    UINT32 ulPdcchAccuTotalNum[DL_MAX_CELL_NUM];     /*�ۻ���*/
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
    UINT16 usCcStoreIdx;
    UINT16 usDlBbpNum;
    UINT16 usDlDataGrantValid;
    UINT16 usDlGrantNum;
    UINT16 usDci0BbpNum;
    UINT16 usDci0CRntiSelNum;
    UINT16 usDci0TcRntiSelNum;
    UINT16 usDci0SpsRntiSelNum;
    UINT16 usDci0Num;
    UINT16 usDci0MacHarqNum;
    UINT16 ausDci0HarqInfo[OM_UL_MAX_CELL_NUM];
}LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_STRU;
typedef struct __LPHY_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCcStoreIdx;
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
    /* BEGIN: Added by xueqiuyan, 2014/9/16   PN:v7r5_modify*/
    UL_DCI_STRU            stUlGrantInfo;
    /* END:   Added by xueqiuyan, 2014/9/16 */
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
    UINT32 ulCcIdx;
    UINT16 usPhichOrgNum;
    UINT16 usPhichNum;
    UINT16 usPhichIdx;
    UINT8  aucPhichResult[OM_UL_MAX_CELL_NUM];
}LPHY_TRACE_VITERBI_PHICH_RESULT_STRU;
typedef struct __LPHY_VITERBI_TRACE_REPORT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 usData[DL_MAX_CELL_NUM];
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
#define     OM_VITERBI_MAX_RPT_PCELL_REG_IMG_LEN       ((0x37c - 0x200) / 4 + 1)
#define     OM_VITERBI_MAX_RPT_SCELL_REG_IMG_LEN       ((0x488 - 0x380) / 4 + 1)
//#define     OM_VITERBI_CFG_REG_IMG_LEN                 ((0xbc - 0x5c) / 4 + 1)
#define     OM_VITERBI_CFG_REG_IMG_LEN                 ((0x010B8 - 0x01000) / 4 + 1)

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
    UINT16 usCcStoreIdx;
    UINT16 usIntAlarm;
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

/*BEGIN: by humin, 2015/05/07*/
#if 1
/************************************************************
                             ���ݽṹ����
************************************************************/
typedef struct
{
    LPHY_REQ_VITERBI_STUB_DCI_ENA_STRU      stReqStubDciEna;
}LPHY_REQ_VITERBI_CFG_ENA_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA_STRU  stReqRptCfiStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_CFI_STAT_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA_STRU stReqRptPdcchGrantStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA_STRU stReqRptPdcBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_PDCCH_BLER_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_CFI_ENA_STRU               stReqRptCfiEna;
    LPHY_REQ_VITERBI_RPT_CFI_STAT_STRU              stReqRptCfiStat;
    LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA_STRU        stReqRptPdcchSinrEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA_STRU    stReqRptPdcchDlGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA_STRU    stReqRptPdcchUlGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA_STRU   stReqRptPdcchPwrGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_STRU      stReqRptPdcchGrantStat;
    LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA_STRU    stReqRptPdcchCceInfo;
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_STRU            stReqRptPdcchBler;
}LPHY_REQ_VITERBI_RPT_ENA_STRU;

typedef struct
{
    LPHY_IND_VITERBI_RPT_CFI_STRU               stRptCfiVal;
    LPHY_IND_VITERBI_RPT_CFI_STAT_STRU          stRptCfiStat;
    LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT_STRU  stRptPdcGrantStat;
    LPHY_IND_VITERBI_RPT_PDCCH_BLER_STRU        stRptPdcBlerStat;
}LPHY_IND_VITERBI_RPT_STRU;


/* BEGIN: Added by yangruina, 2014/3/19   PN:CMCC_DT*/
/************************************************************
                           7.DT����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef UINT16 PDCCH_GRANT_DCI_ENUM_UINT16;

/*DT�ϱ�CFI ����*/
typedef struct
{
   OM_REQ_ENABLE_ENUM_UINT16 enRptCfiEna;
   UINT16 usRsv;
}LPHY_DT_VITERBI_RPT_CFI_INFO_REQ_STRU;

/*DT�ϱ� ��Ȩͳ�� ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16  enRptPdcchGrantStatEna;
    UINT16 ulRptPdcchGrantStatPeriod;
}LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_STRU;

/*DT�ϱ� ������Ȩ ����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptPdcchDlGrantEna;
    UINT16 usRsv;
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ_STRU;

/*DT�ϱ� PDCCH BLER����*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptPdcBlerEna;
    UINT16 ulRptPdcchBlerPeriod;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_STRU;
//begin: by humin, 2015/05/26
/*
typedef enum __LPHY_DT_REQ_VITERBI__
{
    LPHY_DT_VITERBI_RPT_CFI_INFO_REQ                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ,
}LPHY_DT_REQ_VITERBI;
//*/
//end: by humin, 2015/05/26
typedef enum __LPHY_DT_IND_VITERBI__
{
    LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DT, 0x9001),
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_CA_STAT_IND,
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_CA_INFO_IND,
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND,
}LPHY_DT_IND_VITERBI;

typedef struct __LPHY_DT_VITERBI_CFI_INFO_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 ulCfi;
}LPHY_DT_VITERBI_CFI_INFO_STRU;

/*DT�ϱ�CFIֵ*/
typedef struct __LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_DT_VITERBI_CFI_INFO_STRU stDtCfiInfo[MAX_CELL_NUM_DL];
}LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU;

/*DT�ϱ���Ȩͳ����Ϣ*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT32 ulAccuUlGrantNum;
    UINT32 ulAccuDlGrantNum;
    UINT32 ulAccuCce1Num;
    UINT32 ulAccuCce2Num;
    UINT32 ulAccuCce4Num;
    UINT32 ulAccuCce8Num;
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
} LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU;


/*DT�ϱ�������Ȩ��Ϣ*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT16 usRbNum;
    UINT16 usRbStart;
    UINT16 usHarqId;
    //UINT16 usRsv;
    PDCCH_GRANT_DCI_ENUM_UINT16 enDciType;
    /* END:   Added by xueqiuyan, 2013/2/28 */
    UINT8  ucCW0Mcs;
    UINT8  ucCW1Mcs;
    UINT8  ucDlCW0ModSched;
    UINT8  ucDlCW1ModSched;
    UINT16 usCW0RvIndex;
    UINT16 usCW1RvIndex;
    UINT32 ulCW0TbSize;
    UINT32 ulCW1TbSize;
    UINT16 ulTransScheme;
    UINT16 usRsv2;
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU;

typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU stDtPdcchGrantInfo[MAX_CELL_NUM_DL];
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU;


/*DT�ϱ�PDCCH_BLER��Ϣ*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT32 ulPdcchAccuErrorNum;
    UINT32 ulPdcchAccuTotalNum;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_STRU  stRptPdcchGrantStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_STRU stRptPdcBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_CFI_INFO_REQ_STRU              stDtReqRptCfiInfo;
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_CNT_STRU  stDtReqRptPdcchGrantStat;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ_STRU   stDtReqRptPdcchDlGrantInfo;
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_CNT_STRU        stDtReqRptPdcchBler;
}LPHY_DT_REQ_VITERBI_RPT_ENA_STRU;


typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU      stDtIndRptPdcchGrantStat[MAX_CELL_NUM_DL];
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU            stDtIndRptPdcBlerStat[MAX_CELL_NUM_DL];
    LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU stDtIndRptCfiVal;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU stDtIndRptPdcchGrantInfo;
}LPHY_DT_IND_VITERBI_RPT_STRU;

/* END:   Added by yanruina, 2014/3/21 */
#endif
/*END: by humin, 2015/05/07*/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __VITERBI_OM_DEF_H__ */


