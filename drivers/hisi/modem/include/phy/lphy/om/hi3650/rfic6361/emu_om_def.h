

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#ifndef __EMU_OM_DEF_H__
#define __EMU_OM_DEF_H__

#include "om_base_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                               �궨��
************************************************************/
#define EMU_FREQ_NUM                 5
#define EMU_CELL_NUM                 16

/************************************************************
                             ���ݽṹ����
************************************************************/


/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
	LPHY_REQ_EMU_EN_CLOSE = 0,
	LPHY_REQ_EMU_EN_OPEN
} LPHY_EMU_REQ_ENABLE_ENUM;

typedef  UINT16  LPHY_EMU_REQ_ENABLE_ENUM_UINT16;


typedef enum __LPHY_REQ_EMU__
{
    LPHY_REQ_EMU_SG_EN            = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_EMU_SG_SERVE_EN,
    LPHY_REQ_EMU_SDR_PRINT_EN,
    LPHY_REQ_EMU_LIST_PRINT_EN,
    LPHY_REQ_EMU_ALARM_STAT_EN
}LPHY_REQ_MSGID_EMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_EMU_ENUM_UINT16;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuSGEn;          /*1 ʹ���ϱ�, 0�ر��ϱ�*/
    UINT16                             usRsv;
    UINT16                             usFreqReportNum[EMU_FREQ_NUM];
} LPHY_REQ_EMU_SG_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuSGServeEn;     /*1 ʹ���ϱ�, 0�ر��ϱ�*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_SERVE_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usSdrPrintEn;     /*1 ʹ���ϱ�, 0�ر��ϱ�*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_SDR_PRINT_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usListPrintEn;     /*1 ʹ���ϱ�, 0�ر��ϱ�*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_LIST_PRINT_EN_STRU;

typedef  struct
{
	LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuStatEn;
	UINT16                             usRsv;
	UINT16                             usFreq;
	UINT16                             usCellNum;
	UINT16                             usCellList[8];
}LPHY_REQ_EMU_ALARM_STAT_EN_STRU;


/*old**/

// �㷨���ݽṹ
typedef struct _EMU_ALG_RESULT_REQ
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16   usReqType;          /*1 ʹ���ϱ�, 0�ر��ϱ�*/            
    UINT16                            rsv;                  
    UINT16                            usFreqReportNum[EMU_FREQ_NUM];  // Ƶ��С���ϱ�����
}EMU_ALG_RESULT_REQ_STRU;


/************************************************************
                           3. sg���ݽṹ����
************************************************************/




/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_EMU_CONN_INTRA_EVT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_EMU_CONN_INTER_EVT,
    LPHY_TRACE_EMU_CONN_GSM_EVT,
    LPHY_TRACE_EMU_CONN_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_INTRA_EVT,
    LPHY_TRACE_EMU_IDLE_INTER_EVT,
    LPHY_TRACE_EMU_IDLE_GSM_EVT,
    LPHY_TRACE_EMU_IDLE_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_TASK_UPDT_EVT,
    LPHY_TRACE_EMU_CS_ITO_UPDT_EVT,
    LPHY_TRACE_EMU_CS_FINISH_EVT,
    LPHY_TRACE_EMU_IDLE_SETUP_EVT,
    LPHY_TRACE_EMU_IDLE_RELEASE_EVT,
    LPHY_TRACE_EMU_CONN_SETUP_EVT,
    LPHY_TRACE_EMU_CONN_RELEASE_EVT,
	LPHY_TRACE_EMU_HOLD_EVT,
	LPHY_TRACE_EMU_UNHOLD_EVT,
	LPHY_TRACE_EMU_SLAVE_DONE_EVT,
	LPHY_TRACE_EMU_BSIC_REQ_EVT,
	LPHY_TRACE_EMU_ITAT_DONE_EVT,
	LPHY_TRACE_EMU_L_INTER_SHIFT_EVT,
	LPHY_TRACE_EMU_W_FREQ_SHIFT_EVT,
	LPHY_TRACE_EMU_TASK_STOP_EVT,
	LPHY_TRACE_EMU_SERV_LOST_EVT,
	LPHY_TRACE_EMU_PAR_LOW_EVT,
	LPHY_TRACE_EMU_NO_FREE_CELL_EVT,
	LPHY_TRACE_EMU_SCELL_ACTIVE_EVT,
	LPHY_TRACE_EMU_SCELL_INACTIVE_EVT,
    LPHY_TRACE_EMU_EVT_BUTT
}LPHY_TRACE_EMU_EVT_ENUM;

/*LPHY_TRACE_EMU_CONN_INTRA_EVT ~ ?*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_TRACE_EMU_EVT_STRU;


/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_WARN_EMU_LOSE_INT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_ERROR, 0x0),
    LPHY_WARN_EMU_TDD_CELL_POSITION,
    LPHY_WARN_EMU_TRACKER_LOW_PAR,
    LPHY_WARN_EMU_CS_LOSE_SERV,
    LPHY_WARN_EMU_EST_TOF_TOO_LARGE,
    LPHY_WARN_EMU_AFC_UNLOCK,
    LPHY_WARN_EMU_AFC_HOLD
}LPHY_ERROR_EMU_ENUM;

typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_ERROR_EMU_STRU;



/************************************************************
                           6. IND���ݽṹ����
************************************************************/

typedef enum
{
    LPHY_IND_EMU_ALL_FREQ_SG         = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_IND, 0x0),
	LPHY_IND_EMU_SERVE,	
    LPHY_IND_EMU_EMU_CFG_CHANNELS,
    LPHY_IND_EMU_EMU_INT,
    LPHY_IND_EMU_EMU_RESULT,
    LPHY_IND_EMU_EMU_STATE,
    LPHY_IND_EMU_ALARM_STAT
}LPHY_IND_EMU_ENUM;


// �����㷨���
typedef struct _EMU_RESULT_REPORT
{
    UINT16 usFreqInfo;                           // Ƶ��ֵ
    UINT16 usCellID;                             // С��ID
    INT16  sTimingDelta;                         // ��ʱ����ֵ
    UINT16 usReserved;
    INT32  ulRsrp_R0;                            // ��������0��RSRP
    INT32  ulRsrp_R1;                            // ��������1��RSRP
    INT32  ulRsrq_R0;                            // ��������0��RSRQ
    INT32  ulRsrq_R1;                            // ��������1��RSRQ
    INT32  ulRssi_R0;                            // ��������0��RSSI
    INT32  ulRssi_R1;                            // ��������1��RSSI
}EMU_RESULT_REPORT_STRU;

typedef struct _EMU_ALL_FREQ_SG
{
    UINT16 usCellNum;                            // ��ЧС����
    UINT16 usReserved;
    EMU_RESULT_REPORT_STRU  stCell[EMU_CELL_NUM];
}EMU_IND_ALL_FREQ_SG_STRU;

/*��С������Ϣ*/
typedef struct _EMU_RESULT_SERVE
{
    UINT16 usCellID;                            // С��ID
    UINT16 usReserved;
    INT32  lRsrp;                               // ��������0��RSRP
    INT32  lRsrp_R0;                            // ��������0��RSRP
    INT32  lRsrp_R1;                            // ��������1��RSRP
    INT32  lRssi_R0;                            // ��������0��RSSI
    INT32  lRssi_R1;                            // ��������1��RSSI
    INT32  lRsrq;                               // ��������0��RSRQ
    INT32  lSINR;
}EMU_IND_SERVE_SG_STRU;

typedef  struct
{
	UINT32  ulMsrReportNum;
	UINT32  ulFalseAlarmPerNum;
	UINT32  ulFalseAlarmNum;  
	UINT32  ulLeastRsrpNum;
	UINT32  ulLeastRealNum;
	
}EMU_IND_FALSE_ALARM_STRU;


typedef struct _EMU_ALG_CTRL
{
    UINT16 ebTimingLimitFlag;                    // ʱƫ����ģ�����޷�ģ���Ƿ��               ��TRUE-�򿪣�FALSE-�ر�
    UINT16 ebDrxAlphaFilterFlag;                 // DRX̬���ŵ��ܹ���/����Alpha�˲����㿪��      ��TRUE-�򿪣�FALSE-�ر�
    UINT16 eDbAlphaFilterFlag;                   // dB��alpha�˲����㿪��                      ��TRUE-�򿪣�FALSE-�ر�
    UINT16 usMeasSymbolNums;                     // ÿ���������ڲ����ķ�����
}EMU_ALG_CTRL_STRU;


// �㷨��־�ṹ
typedef struct _EMU_ALG_CTRL_REQ
{
    LPHY_REQ_MSGID_EMU_ENUM_UINT16   usReqType;  // ��������
    UINT16                           ulReaserve;
    EMU_ALG_CTRL_STRU                stAlg_Ctrl;
}EMU_ALG_CTRL_REQ_STRU;



/*LPHY_IND_EMU_EMU_CFG_GLOBAL*/
typedef struct
{
    UINT32 ulCell_Band;
    UINT32 ulInter_En;
    UINT32 ulTiming_En;
    UINT32 ulAngle_Th;
    UINT32 ulDelta_Coeff;
    UINT32 ulAagc_Pos;
    UINT32 ulAdj_En;
    UINT32 ulEmu_Ctrl;
}LPHY_IND_EMU_GLOBAL_CFG_STRU;

typedef struct
{
    UINT32 ulInf;
    UINT32 ulSync;
    UINT32 ulTiming_delta;
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
}LPHY_EMU_BBP_ONE_CH_CFG_STRU;

/*LPHY_IND_EMU_EMU_CFG_CHANNELS*/
typedef struct
{
    UINT32 ulEmuBwReg;
    UINT32 ulEmuInterEnReg;
    UINT32 ulEmuCtrlReg;
    UINT32 ulEmu_RptMode;
    UINT32 ulEmuFddTddSel;

    LPHY_EMU_BBP_ONE_CH_CFG_STRU stBbpChCfg[8];

    UINT32 ulSym_num0;
    UINT32 ulSym_num1;
    UINT32 ulTiming_kalman_idx0;
    UINT32 ulTiming_kalman_idx1;
    UINT32 ulRsrp_kalman_idx0;
    UINT32 ulRsrp_kalman_idx1;
    UINT32 ulRsrp_alpha;
    UINT32 ulRsrp_first_alpha;
    UINT32 ulEmu_en;
    UINT32 ulEmu_start;
    UINT32 ulEmu_stop;
    UINT32 ulEmu_Dma_en;
}LPHY_IND_EMU_CHANNELS_CFG_STRU;


/*LPHY_IND_EMU_EMU_INT*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];//usFreqInfo; BALONGV7_SMU_REG_SMU_SYM_CNT0_REG; BALONGV7_SMU_REG_SMU_SYM_CNT1_REG
}LPHY_IND_EMU_INT_STRU;

typedef struct
{
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
    UINT8  ucTiming_kalman_index;               //
    UINT8  ucRsrp_kalman_index;                 //
    UINT8  ucAlpha_Init;                       //
    UINT8  ucReserved;                          //
}EMU_OM_CELL_BBP_CTX_STRU;


typedef struct
{
    INT16                       sRssi_current0;
    INT16                       sRssi_current1;
    INT16                       sRsrp_current0;
    INT16                       sRsrp_current1;
    INT16                       sRsrq_current0;
    INT16                       sRsrq_current1;
    INT16                       sRsrp_rpt;
    INT16                       sRsrq_rpt;
}EMU_OM_CALC_RESULT_STRU;


typedef struct
{
    EMU_OM_CELL_BBP_CTX_STRU    stEmuBbpCellCtx;
    EMU_OM_CALC_RESULT_STRU     stResult;
    UINT16                      usCellId;
    UINT16                      usMeasSymb;
}LPHY_EMU_CELL_RESULT_STRU;


/*LPHY_IND_EMU_EMU_RESULT*/
typedef struct
{
	UINT16 usCellId;
	UINT16 enCellCPInd;
	UINT16 enBandWidth;
	UINT16 usTxNum;
	UINT32 ulCellPosition;
	UINT32 ulPnCnter;
	UINT32 ulTimeOffsetCnter;
	UINT32 ulDagc[2];
	INT16  sAagc[2];
	INT32  lTheta;
	UINT32 ulTxRxPh[4];
	UINT32 ulTxRxPn[4];
	UINT32 ulRsrpBef[2];
	UINT32 ulRsrpAft[2];
	INT16  sRsrpdB[2];	
	INT32  lRsv[2];

}EMU_SDR_PROC_RESULT;


/*LPHY_IND_EMU_EMU_STATE*/
typedef struct
{
    UINT32 ulCsInterStartCnt;
    UINT32 ulCsSlaveStartCnt;
    UINT32 ulEmuIntraCfgCnt;
    UINT32 ulEmuIntraIntCnt;
    UINT32 ulEmuInterCfgCnt;
    UINT32 ulEmuInterIntCnt;
    UINT32 ulEmuSlaveCfgCnt;
    UINT32 ulEmuSlaveIntCnt;
    UINT32 ulEmuRptIntraCnt;
    UINT32 ulEmuRptInterCnt;
    UINT32 ulEmuWOccasionCnt;
    UINT32 ulEmuGOccasionCnt;
    UINT32 ulEmuWFinishCnt;
    UINT32 ulEmuGFinishCnt;
}LPHY_IND_EMU_STATE_STRU;

typedef struct
{
    UINT16  ausCQI[2];
    UINT16  usRI;
    UINT8   aucRes[2];
}LPHY_IND_EMU_AT_RI_CQI_STRU;

typedef struct
{
    UINT16  usOpId;
    UINT16  usTa;
    INT32   lSINR;
    LPHY_IND_EMU_AT_RI_CQI_STRU stRiCqiPara;
}LPHY_IND_EMU_AT_MEAS_STRU;


/************************************************************
                             �ӿں�������
 ************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __EMU_OM_DEF_H__ */
