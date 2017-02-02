

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "om_base_def.h"

/************************************************************
                               �궨��
************************************************************/
#define CMU_SB_MAX                 25

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __CMU_OM_DEF_H__
#define __CMU_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define CMU_RX_MAX_NUM NUM_OF_RX_ANT 
#define   CMU_TX_MAX_NUM                NUM_OF_TX_ANT
#define NUM_FRAME_TYPE         4
#define NUM_OF_INTERP_CRS_RB    4
#define NUM_OF_CRS_RB    2
#define NUM_OF_TX_ANT    2
#define NUM_OF_RX_ANT    2
#define NUM_OF_IQPATH    2
	
#define NUM_OF_RS_SYMB   4
#define NUM_OF_RB        100
#define NUM_OF_RB_20M        100
#define NUM_OF_RB_15M        75
#define NUM_OF_RB_10M        50
#define NUM_OF_RB_5M         25
#define NUM_OF_RB_3M         15
#define NUM_OF_RB_1P4M       6


/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_CMU__
{
    LPHY_REQ_CMU_REPORT_ENA            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_REQ, 0x0),
}LPHY_REQ_MSGID_CMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_CMU_ENUM_UINT16;
typedef enum
{
    CMU_OM_SWITCH_OFF = 0,
    CMU_OM_SWITCH_ON,
}CMU_OM_SWITCH_ENUM;
typedef UINT16 CMU_OM_SWITCH_ENUM_UINT16;
typedef struct
{
   CMU_OM_SWITCH_ENUM    enCmuSgReportEn;
   
}LPHY_REQ_CMU_SG_REPORT_ENA_STRU;

#if 0
/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_CMU__
{
    LPHY_CNF_CMU_RESERVED            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_CNF, 0x0),
    LPHY_CNF_CMU_ENA_ALG,              /*ʹ�ܹ�����������ϱ�*/
    LPHY_CNF_CMU_ENA_CFG,              /*���ù����������㷨����*/
}LPHY_CNF_MSGID_CMU_ENUM;
typedef UINT16 LPHY_CNF_MSGID_CMU_ENUM_UINT16;

// REQʱ���ص�CNF�ṹ
typedef struct _CMU_CNF_REQ
{
    LPHY_CNF_MSGID_CMU_ENUM_UINT16   usCnfType;  // ��������
    UINT16                           ulReaserve;
}CMU_CNF_STRU;

#endif
/************************************************************
                           3. Sg���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_SG_CMU_PCC_REPORT_ENA         = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_CMU_SCC_REPORT_ENA
}LPHY_SG_CMU_ENUM;

typedef enum CMU_STATE
{
	CMU_IDLE = 0,
	CMU_DRX,
	CMU_HOLD,
	CMU_WAIT,
	CMU_WORKING
}CMU_STATE_ENUM;
typedef UINT16 CMU_STATE_ENUM_UINT16;


typedef struct
{
    /*Do not change the order and the size of this structrue must be 160bit times*/
    UINT32           aulCmuServCrsRsrp[CMU_RX_MAX_NUM];
    UINT32           aulCmuServNoisePower[CMU_RX_MAX_NUM];                               
    UINT32           aulCmuFinalNoisePower[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];                               
	
    UINT32           aulCmuSdrPhRx[CMU_RX_MAX_NUM];// kalman input
    UINT32           aulCmuSdrPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];// kalman input                        

	UINT32           aulCmuFilteredPhRx[CMU_RX_MAX_NUM];
    UINT32           aulCmuFilteredPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];                                  

	UINT32           aulChPowerTxRx[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];                    
    UINT32           aulNoisePowerTxRx[NUM_FRAME_TYPE][CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];                        
	UINT32           aulCmuRsrpConInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];//Filtered
	UINT32           aulCmuPnConInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];//Filtered
	
    UINT32           ulPhPnKalmanIndex;                                                    
    UINT32           ulRsrpKalmanIndex;                                                    
    UINT32           ulNoiseKalmanIndex[NUM_FRAME_TYPE];                                                    
    UINT32           ulConIndKalmanIndex;                                                    
	INT16            asCmuSnr[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];                                        
	INT16            asCmuServSnr[CMU_RX_MAX_NUM];                                        
	UINT16           ausConnectionInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	UINT32           aulAgcNoisePower[NUM_FRAME_TYPE][CMU_RX_MAX_NUM]; 
	UINT8            aucAgcNoiseSel[NUM_FRAME_TYPE][CMU_RX_MAX_NUM]; //TBD

}CMU_CALC_PARA_STRU;
typedef struct
{
	CMPX_64_STRU	astCmuTruErrKalmanFormerData[NUM_OF_RX_ANT];
	UINT32 ulCmuTruErrKalmanIndex;
	INT16 sThetaBefore;
	INT16 sThetaLastSubFrm;

}CMU_KALMAN_PARA_STRU;
typedef struct
{
	CMU_KALMAN_PARA_STRU  stTruKalmanPara;
	CMU_CALC_PARA_STRU    stCmuCalcPara;                             
	UINT32                ulTsPos;
	INT32                 lTsNum;
	UINT32 			      aulKalmanAgcRatio[NUM_OF_RX_ANT];
	UINT32 			      aulCompAgcRatio[NUM_OF_RX_ANT];
	UINT8                 ucResultValid;
	UINT8                 ucNoiseAvailableFlag;
	CMU_STATE_ENUM_UINT16        enCmuState;
}CMU_PARA_STRU;

/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_CMU_
{
    LPHY_TRACE_CMU_RESERVED              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_TRACE, 0x0),
	LPHY_TRACE_CMU_STATE,                        // ����CMU��״̬
	LPHY_TRACE_CMU_CFG,                          // ����CMU�����ù���
	LPHY_TRACE_CMU_RESULT,                       // ����CMU�ļ������
	LPHY_TRACE_CMU_CELL,                         // ����CMU��С��״��
	LPHY_TRACE_CMU_SFNUM,                        // ����CMU����֡��
}LPHY_TRACE_CMU_ENUM;
typedef UINT16 LPHY_TRACE_CMU_ENUM_UINT16;


typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuState;
}LPHY_TRACE_CMU_STATE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuCell;
}LPHY_TRACE_CMU_CELL_STRU;
typedef enum
{
    CMU_CFG_IDLE = 0,
    CMU_CFG_WAIT,
    CMU_CFG_UPLINK,
    CMU_CFG_MAXTAU,
    CMU_CFG_ALL,
    CMU_CFG_SERVCELL,
    CMU_CFG_ONLYTAU,
}CMU_CONFIG_ENUM;

typedef struct
{
    CMU_CONFIG_ENUM      enCmuCfg;
}LPHY_TRACE_CMU_CFG_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuResult;
}LPHY_TRACE_CMU_RESULT_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuSFNum;
}LPHY_TRACE_CMU_SFNUM_STRU;


/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum __LPHY_ERROR_CMU_ENUM__
{
    /*PBCH, ERROR ID 1 - 15*/
    LPHY_ERROR_CMU_LOG_ERROR              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_CMU_EXP_ERROR,
    LPHY_ERROR_CMU_DMA_ERROR
}LPHY_ERROR_CMU_ENUM;
typedef UINT16 LPHY_ERROR_CMU_ENUM_UINT16;

typedef struct
{
    UINT32      ulErrorType;
    INT32       lErrorValue;
}LPHY_TRACE_CMU_ERROR_STRU;



/************************************************************
                           6. DEBUG���ݽṹ����
************************************************************/
typedef enum __LPHY_DEBUG_CMU_ENUM__
{
    LPHY_DEBUG_CMU_RESERVED                         = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_DEBUG, 0x0),
    LPHY_DEBUG_CMU_LOGIC_REG,
    LPHY_DEBUG_CMU_BUFFER_VALUE,
    LPHY_DEBUG_CMU_CURRCAL_VALUE,
}LPHY_DEBUG_CMU_ENUM;
typedef UINT16 LPHY_DEBUG_CMU_ENUM_UINT16;

typedef struct
{
    UINT8 ccValidFlag;
    UINT8 ccIdx;
    UINT16 rsv;
    LTE_CP_TYPE_ENUM_UINT16 enCpType;
    INT16  sCRS_SinrR0;
    INT16  sCRS_SinrR1;
    INT16 sCRS_AvgSinr;
    //INT16  sDRS_AvgSinr;
    /* END: Added by wujing, 2013/02/04  */
    INT32  lCRS_Rsrq;
    INT32  lCRS_RsrpR0;
    INT32  lCRS_RsrpR1;
    INT32  lDRS_RsrpR0;
    INT32  lDRS_RsrpR1;
    INT32  lCRS_RssiR0;
    INT32  lCRS_RssiR1;
    /* BEGIN: Added by xueqiuyan, 2013/8/13   PN:DRS_SNR*/
    INT16  sDRS_SnrP5P7Rx0;
    INT16  sDRS_SnrP5P7Rx1;
    INT16  sDRS_SnrP8Rx0;
    INT16  sDRS_SnrP8Rx1;
    /* END:   Added by xueqiuyan, 2013/8/13 */
} LPHY_DT_MEAS_INFO_IND_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CMU_OM_DEF_H__ */
