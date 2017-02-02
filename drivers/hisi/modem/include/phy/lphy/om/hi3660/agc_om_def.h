


#ifndef __AGC_OM_DEF_H__
#define __AGC_OM_DEF_H__


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
#ifndef LPHY_MAX_RX_ANTENNA_NUM
#define LPHY_MAX_RX_ANTENNA_NUM     (4)
#endif

#ifndef AGC_MAX_CC_NUM
#define AGC_MAX_CC_NUM           LPHY_FEATURE_MAX_CARRIER_NUM
#endif

#ifndef AGC_MAX_SERV_FREQ_NUM
#define AGC_MAX_SERV_FREQ_NUM					(LPHY_FEATURE_MAX_CARRIER_NUM+2)
#endif

#ifndef AGC_EMBMS_MAX_CH
#define AGC_EMBMS_MAX_CH    (2)
#endif

#define AGC_BANDSCAN_COMB_NUM	 (16)
/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
    LPHY_REQ_AGC_REPORT_ENA                         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA,
    LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA,
    LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA,
    LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA,
    LPHY_REQ_DAGCF_DEM_FIXED_GAIN_CONFIG_ENA,
    LPHY_REQ_DAGCF_MSR_FIXED_GAIN_CONFIG_ENA,
    LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA,
    LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA,
    LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA,
    LPHY_REQ_TRIGGER_RFIN_SAMPLING_ENA,
    LPHY_REQ_MAGC_REPORT_ENA,
    LPHY_REQ_AGC_BAND_SCAN_PWR_RPT_ENA,
    LPHY_REQ_AGC_FREQ_BUF_RPT_ENA,
    LPHY_REQ_AGC_COM_RPT_ENA,
    LPHY_REQ_AGC_FREQ_CFG_RPT_ENA,
    LPHY_REQ_AGC_MODE_CFG_FREQ_PROC_RPT_ENA,
    LPHY_REQ_AGC_NV_BUF_INFO_RPT_ENA,
    LPHY_REQ_AGC_CALC_DIRECT_CONN_ENA,
    LPHY_REQ_AGC_CHANCTRL_FREQ_CFG_RPT_ENA
}LPHY_REQ_AGC_ENUM;

typedef enum
{
    AGC_OM_SWITCH_OFF = 0,
    AGC_OM_SWITCH_ON,
}AGC_OM_SWITCH_ENUM;

typedef UINT16 AGC_OM_SWITCH_ENUM_UINT16;
typedef UINT32 AGC_OM_SWITCH_ENUM_UINT32;


typedef enum
{
    DEBUG_RFIN_NO_TRIGGER = 0,
    DEBUG_RFIN_SAMPLING_ENABLE,
    DEBUG_RFIN_PBCH_FAILURE,
    DEBUG_RFIN_GAP_INTER_FREQ_START,
    DEBUG_RFIN_IDLE_INTER_FREQ_START,
    DEBUG_RFIN_INTER_FREQ_FINISH,
    DEBUG_RFIN_PRE_DEFINED_SUBFRAME,
    DEBUG_RFIN_DLSCH_CRC,
    DEBUG_RFIN_BCCH_CRC,
    DEBUG_RFIN_PCH_CRC,
    DEBUG_RFIN_TIMING_ERROR,
    DEBUG_EMU_ABNORMAL_RPT,
    DEBUG_CMU_ABNORMAL_RPT
}LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM;
typedef UINT16 LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM_UINT16;

typedef enum
{
    AGC_BANDSCAN_STAGE_NULL 			= 0,
    AGC_BANDSCAN_STAGE_1,
	AGC_BANDSCAN_STAGE_2,
    AGC_BANDSCAN_STAGE_DONE
} AGC_BANDSCAN_STAGE_ENUM;
typedef UINT16 AGC_BANDSCAN_STAGE_ENUM_UINT16;

typedef struct
{
	AGC_BANDSCAN_STAGE_ENUM_UINT16 enStage;
	UINT16 usCounter;
	INT32 alBandScanDbm[LPHY_MAX_RX_ANTENNA_NUM][AGC_BANDSCAN_COMB_NUM];
}AGC_BANDSCAN_CTRL_STRU;


typedef struct
{
    LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM  enRfinSamplingTrigger;
    UINT32                              ulCounter;
    UINT16                              usFreqInfo;
    UINT16                              usCellId;
    INT16                               sUpThreshold;
    INT16                               sLowThreshold;
    UINT16                              usEmuMode;
    UINT16                              enCcIndex;
}LPHY_DEBUG_RFIN_SAMPLING_CTRL_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;    /*1 ʹ��AGC״̬�ϱ�*/
}LPHY_REQ_AGC_REPORT_ENA_STRU;


typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_BANDSCAN_PWR_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_FREQ_BUF_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_MAGC_REPORT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_COMPENSATION_REPORT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_FREQ_CFG_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_MODE_CFG_FREQ_PROC_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_NV_BUF_INFO_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_CHANCTRL_FREQ_CFG_ENA_STRU;

typedef enum
{
    AGC_INDEPENDENT_ANTENNA,
    AGC_COMBINED_ANTENNA,
    AGC_NOISE_SAME,
    AGC_ON_AIR
}AGC_ANT_CONFIG_ENUM;
typedef UINT16  AGC_ANT_CONFIG_ENUM_UINT16;

typedef enum
{
    AGC_ADJMODE_INDEPENDENT = 0,
    AGC_ADJMODE_NOISESAME,
	AGC_ADJMODE_UNITY
}AGC_ADJMODE_ENUM;
typedef UINT8 AGC_ADJMODE_ENUM_UINT8;


typedef enum
{
    AGC_NO_INTERFERENCE =0,
    AGC_ACS_INTERF_VAR,
    AGC_ACS_INTERF_CONST,
    AGC_NB_INTERF_VAR,
    AGC_NB_INTERF_CONST,
    AGC_INTERF_BUTT,
}AGC_INTERFERENCE_TYPE_ENUM;
typedef INT16  AGC_INTERFERENCE_TYPE_ENUM_INT16;

typedef enum
{
    AGC_DEM_PERIOD_1MS = 0,
    AGC_DEM_PERIOD_5MS,
    AGC_DEM_PERIOD_10MS,
    AGC_DEM_PERIOD_20MS,
    AGC_DEM_PERIOD_BUTT,
}AGC_DEM_MODE_SEL_ENUM;
typedef UINT16  AGC_DEM_MODE_SEL_ENUM_UINT16;

typedef enum
{
    AGC_RF_IDX0 = 0,
    AGC_RF_IDX1,
    AGC_RF_IDX2,
    AGC_RF_IDX3,
    AGC_RF_IDX4,
    AGC_RF_IDX5,
    AGC_RF_IDX6,
    AGC_RF_IDX7,
    AGC_RF_IDX8,
    AGC_RF_IDX9,
    AGC_RF_IDX10,
    AGC_RF_IDX11,
    AGC_RF_IDX12,
    AGC_RF_IDX13,
    AGC_RF_IDX14,
    AGC_RF_IDX15,
}AGC_RF_IDX_ENUM;
typedef UINT16  AGC_RF_IDX_ENUM_UINT16;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    AGC_RF_IDX_ENUM_UINT16       aenFixedRfIdx[4][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT16     asFixedPreDagcGain[4][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT16     asFixedPostDagcGain[4][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_ANT_CONFIG_ENUM_UINT16   enAntennaConfig; // default AGC_ON_AIR
}LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_INTERFERENCE_TYPE_ENUM_INT16      enInterfConfig;
}LPHY_AGC_OM_INTERF_CONFIG_STRU;

typedef struct
{
	LPHY_AGC_OM_INTERF_CONFIG_STRU astInterfConfig[4];//om for ca
}LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_DEM_MODE_SEL_ENUM_UINT16 enDemPeriodSel;
}LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lPreTarPower;
}LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lPostTarPower;
}LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lTddBlockPowerThresh;
}LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lTddBlockGainStep;
}LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32 enEnable;
    UINT32    aulDemFixedDagcFGain[4];//om for ca
}LPHY_REQ_DAGCF_DEM_FIXED_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    aulMsrFixedDagcFGain[4];//om for ca
}LPHY_REQ_DAGCF_MSR_FIXED_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulAdjBit;
}LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulExtraPA;
}LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulDemBitShift;
    UINT32    ulMsrBitShift;
}LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA_STRU;


/************************************************************
                           3. Sg���ݽṹ����
************************************************************/

typedef enum
{
    AGC_DIRECT_NONE_CONN 			= 0,
    AGC_DIRECT_CONN,
} AGC_DIRECT_CONN_ENUM;
typedef UINT16 AGC_DIRECT_CONN_ENUM_UINT16;

typedef enum
{
    AGC_CC_DEACTIVE = 0,
    AGC_CC_ENACTIVE,    
    AGC_CC_CHANGE_CHAN          /*����״̬����ֻ��ͨ�������ı䣬AGC��Ҫhold һ����֡*/
}AGC_CC_STATUS_ENUM;
typedef UINT16 AGC_CC_STATUS_ENUM_UINT16;

typedef enum
{
    LPHY_SG_AAGC_REPORT_ENA                     = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_DAGC_REPORT_ENA                     = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x1),
    LPHY_SG_MDAGCF_REPORT_ENA                   = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x2),
    LPHY_SG_MAAGC_MAIN_AREA_REPORT_ENA          = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x3),
    LPHY_SG_MAAGC_NON_MAIN_AREA_REPORT_ENA      = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x4),
}LPHY_SG_AGC_ENUM;

typedef struct
{
    INT16     sPreTargetPower;
    INT16     sPostTargetPower;
}AGC_TARGET_POWER_STRU;


typedef struct
{
	INT32   alPreRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//pre-rssi dB �����ۺ�
	INT32	alPostRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//post-rssi dB �����ۺ�
	INT32	alInbandSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];				//inband dB �����ۺ�
	INT32	alCRSSubframeAcc[LPHY_MAX_RX_ANTENNA_NUM];				//ÿ��֡ƽ��CRS dB��֡���ۺ�
	INT32	alCRSAccTmp0[LPHY_MAX_RX_ANTENNA_NUM];			//ÿ��֡CRS����0 4 7 11 dB�ۺ�
	INT32	alCRSAccTmp1[LPHY_MAX_RX_ANTENNA_NUM];			//ÿ��֡CRS����1 8 dB�ۺ�
	UINT8	aucSymbolNum[4];
	UINT8	aucSubframeNum[4];
	UINT8   aucEmbmsReNum[4];
}AGC_ACC_INFO_STRU;

typedef struct
{
	AGC_ACC_INFO_STRU stAccInfo;									//ͳ�������ۺ�
	AGC_DIRECT_CONN_ENUM_UINT16      enDirectConnIndicate[LPHY_MAX_RX_ANTENNA_NUM];         //4��ֱ��ָʾ
    INT16     asPreRssidB[LPHY_MAX_RX_ANTENNA_NUM];                 //��������0/1/2/3���˲�ǰʱ��DAGC��RSSI ƽ��ֵ
    INT16     asPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];         		//��������0/1/2/3���˲�ǰʱ��DAGC����
    INT16     asPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];           	//�˲�ǰ��������0/1/2/3���߿ڹ���,dBm
    INT16     asPostRssidB[LPHY_MAX_RX_ANTENNA_NUM];                //�˲����������0/1/2/3��ʱ��DAGC��RSSI ƽ��ֵ
    INT16     asPostDAGCTgain[2][LPHY_MAX_RX_ANTENNA_NUM];       	//�˲����������0/1/2/3��ʱ��DAGC����, none-ABS��ABS
    INT16     asPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];          	//�˲����������0/1/2/3���߿ڹ���,dBm
    INT16     asAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];             		//��������0/1/2/3��AAGC����
    UINT16    ausLNAGain[LPHY_MAX_RX_ANTENNA_NUM];             		//��ǰ��������0/1/2/3��LNA��λ
    UINT16    ausRFGain[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16    ausRFIdex[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_RF_IDX_ENUM_UINT16    aenFinalIdx[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_INTERFERENCE_TYPE_ENUM_INT16    aenAAGCIdxSel[LPHY_MAX_RX_ANTENNA_NUM];          //��������0/1/2/3����ѡ���ź�
    /*last Value*/
    UINT16    ausLastRfGain[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1/2/3��AAGC����
    INT16     asLastCrsAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1/2/3��AAGC����
    INT16     asLastPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1/2/3��AAGC����
    INT16     asLastPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1/2/3��AAGC����

    INT16     asLastAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1/2/3��AAGC����
    INT16     asLastPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];  //�˲����������0/1/2/3��ʱ��DAGC����
    INT16     asLastPostDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM]; //��������0/1/2/3��AAGC����alex tbd abs

    /*��ģ��������*/
    UINT8    ucFixAgcFlag;                                /*��Ƶ��̶�AGC��ʶ*/
    UINT8    ucReserved;                                     /*����ʱ��*/
    UINT8    ucLastFixAgcFlag;
    //UINT8    ucReserved2;
    UINT8    ucInterAutoGainConuter;
    /*END*/
    INT16     asInBanddB[LPHY_MAX_RX_ANTENNA_NUM];                	//ƽ����InBand����ͳ��δ�۵����߿ڣ�����CA�����������Ƶ��ΪSum_InBand
    INT16     asInBandAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];         	//asInBanddB ���㵽���߿�
    INT16     asCRSdB[LPHY_MAX_RX_ANTENNA_NUM];                		//ƽ����CRS����ͳ��δ�۵����߿ڣ�����CA�����������Ƶ��ΪSum_CRS
    INT16     asCRSAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];              //asCRSdB ���㵽���߿�
	AGC_INTERFERENCE_TYPE_ENUM_INT16 enInterfInd;
    AGC_DIRECT_CONN_ENUM_UINT16 enDirectConnInd;
}AAGC_PARA_STRU;

typedef struct
{
    UINT32    aulRx0Sym0Pwr[4];  
    UINT32    aulRx1Sym0Pwr[4];  
    UINT16    ausSym0PwrInv[4];  
	UINT32	  aulCSIDAGCFGain[4];
    UINT32    aulDAGCFGain[4];   
    UINT16    ausPaValue[4];
    UINT32    aulPcValue[4];

    INT16     asAGCNoiseFactor[4][LPHY_MAX_RX_ANTENNA_NUM];         //��������//cc0 cc1 cc2 cc3
    UINT16    ausDAGCFTar[4];              //����ADJBit�õ�,����DAGCFĿ�깦��,�ڷ���2�ж��и���
    UINT8     ucCounter1;
    UINT8     ucCounter3;
    UINT8	  aucRsv[2];
}DAGCF_PARA_STRU;

typedef struct LPHY_AGC_OM_AAGC_CC_STATE
{
    LPHY_CA_CC_ENUM_UINT16    enCCIdx;
    AGC_CC_STATUS_ENUM_UINT16 enCCState;
    UINT32 ulShowIdx;
}LPHY_AGC_OM_AAGC_CC_STATE_STRU;

typedef struct
{
    AGC_ADJMODE_ENUM_UINT8     enIndepAGCFlag;
    UINT8     ucFreqIndex;
    UINT16    usFreqInfo;
    UINT32    ulContCaFlag;
    UINT16    usCaMemberFreqInfo[2];
    AAGC_PARA_STRU    stAAGCPara;
}LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU;

typedef struct
{
    LPHY_AGC_OM_AAGC_CC_STATE_STRU      astOmAagcCCState[6];
	LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU astAAgcPara[6];//om for ca
} LPHY_SG_AAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT8     aucAgcPaIndex[4];                //PA ����cc0 cc1
    UINT8     aucExtraPa[4];                   //Extra PA   cc0 cc1
    UINT8     ucMflag;
    UINT8     ucReserved;
    UINT16    usSubFrameNum;// = SCHED_GetSubFrmNum();
    DAGCF_PARA_STRU   stDAGCFPara;             //��ǰ��֡DAGCF�Ĳ���
} LPHY_SG_DAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT16    usMs1DagcfGain;
    UINT16    usReserved;
    UINT16    usMDagcfGain[AGC_EMBMS_MAX_CH];

    UINT16    usDagcfGainDiff[AGC_EMBMS_MAX_CH];
    UINT16    usDagcfGainCoef[AGC_EMBMS_MAX_CH];

    INT16     sOutDiffPowdBm[AGC_EMBMS_MAX_CH];//PMCH��֡��֮ǰ���ڵĵ�����֡�˲������߿ڹ���֮��

} LPHY_SG_MDAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT16 usMagcStrartFlag;
    UINT16 usEmbmsHold;

    UINT16 usEmbmsflag;
    UINT16 usFirstFrameFlag;

    UINT16 usMagcCalcFlag;
    UINT16 usCurMrsValid;

    UINT16 usNextMrsValid;
    UINT16 usCfgValid;

    UINT16 usMainAreaFlg;
    UINT16 usPeriod;

    UINT16 usSfnCounter;
    UINT16 usSubFrmNum;
} LPHY_TRACE_MDAGC_STATE_STRU;



typedef struct
{
    AAGC_PARA_STRU    astMAGCPara[2];
} LPHY_SG_MAAGC_REPORT_ENA_STRU;


/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_AGC_STATE         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_AGC_TDD_BLOCK_EVENT,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_1,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_3,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_4,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_6,
    LPHY_TRACE_AGC_FREQ_INFO,
    LPHY_TRACE_AGC_EMBMS_FRAME,
    LPHY_TRACE_MDAGC_STATE,
    LPHY_TRACE_AGC_EMBMS_MUTE,
	LPHY_TRACE_AGC_BANDSCAN_PWR_INFO,
	LPHY_TRACE_AGC_COMPENSATION_INFO,
	LPHY_TRACE_AGC_FREQ_CFG,
	LPHY_TRACE_AGC_MODE_CFG_FREQ_PROC,
	LPHY_TRACE_AGC_MODE_REQ_GAIN_CFG,
	LPHY_TRACE_AGC_MODE_CFG,
	LPHY_TRACE_AGC_DRX_GAIN_CFG,
	LPHY_TRACE_AGC_NV_BUF_INFO,
	LPHY_TRACE_AGC_CHANCTRL_FREQ_CFG
}LPHY_TRACE_AGC_ENUM;


typedef enum
{
    AGC_BAND_SCAN = 0,                                /*ɨƵģʽ*/
    AGC_INIT_CELL_SEARCH,                             /*��ʼС������ģʽ��RSSIͳ��ʱ��5ms��ʹ��ȫ����������*/
    AGC_DEMOD,                                        /*���ģʽ��RSSIͳ��ʹ�õ�Ƶ����*/
    AGC_GAP,                                          /*GAP��Ƶģʽ*/
    AGC_DRX,                                          /*DRX��Ƶģʽ*/
    AGC_FIXED_GAIN0,                                  /*�̶�����*/
    AGC_FIXED_GAIN1,
    AGC_NULL
} AGC_WORKING_MODE_ENUM;

typedef UINT16 AGC_WORKING_MODE_ENUM_UINT16;


typedef struct
{
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCRFBW;     /*RF�˲�������*/
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCBBBW;     /*�����˲�������*/
} AGC_BW_CHANGE_STRU ;

typedef struct
{
    UINT16                             usAGCFreqInfo; 							/*AGCƵ����Ϣ*/
    UINT16                             usBand;
    LPHY_CA_CC_ENUM_UINT16             enCcIdx;
    UINT16                             usRsv;
    AGC_BW_CHANGE_STRU                 stAGCBWChange; 							/*AGC����仯*/
}AGC_FREQUENCY_INFO_STRU;


typedef struct
{
    AGC_CC_STATUS_ENUM              enCCStatus;         /*�ز�״̬*/
    CHANCTRL_CA_IND_ENUM_UINT16     enCAType;
    LPHY_CA_CC_ENUM_UINT16          enCaMemberCC;
    UINT16                          usFreqInfo; 							/*AGCƵ����Ϣ*/
    UINT16                          usBand;
}CHANCTRL_CC_INFO_STRU;

typedef struct
{
    AGC_FREQUENCY_INFO_STRU         stCcFreqInfo;                           /*��ǰ�����ز���Ƶ����Ϣ*/
    AGC_CC_STATUS_ENUM_UINT16       enCcStatus;                             /*�ز�״̬ active inactive*/
    CHANCTRL_CA_IND_ENUM_UINT16     enCaType;                               /*����CA��־*/
    AGC_FREQUENCY_INFO_STRU         stCaMemberFreqInfo;                     /*CA��Ա��Ƶ����Ϣ*/
    AGC_FREQUENCY_INFO_STRU         stContCaCenterFreqInfo;                 /*����CA������Ƶ����Ϣ*/
    UINT8                           ucValidFlg;                             /*�ӿ���Ч��־*/
    UINT8                           ucReserved;                             
	LTE_FRAME_TYPE_ENUM_UINT16      enFrametype;
}AGC_MODE_CFG_CC_INFO_STRU;

typedef struct
{
    AGC_MODE_CFG_CC_INFO_STRU           astCcInfo[AGC_MAX_CC_NUM];	            /*ÿ���ز���Ϣ*/
    AGC_WORKING_MODE_ENUM_UINT16       	enAAGCMode;    							/*��ǰ��֡AAGC����ģʽ*/
    UINT32                             	ulBaseCellPos;
    UINT16                              usBandScanFreq;                         /*��������ʱ 10.8M������Ƶ��*/
    UINT16                              usDualPssFlag;
} AGC_MODE_CFG_REQ_STRU;

typedef struct
{
    AGC_MODE_CFG_CC_INFO_STRU           astCcInfo[4];	            /*ÿ���ز���Ϣ*/
}AGC_MODE_CFG_FREQ_PROC_RPT_STRU;

typedef struct
{
    AGC_WORKING_MODE_ENUM_UINT16       	enAAGCMode;    							/*��ǰ��֡AAGC����ģʽ*/
    UINT16                              usBandScanFreq;                         /*��������ʱ 10.8M������Ƶ��*/
    UINT16                              usDualPssFlag;
    UINT16                              usReserved;
}AGC_MODE_CFG_RPT_STRU;


typedef struct
{
    UINT32      ulSubframe;
}LPHY_TRACE_AGC_EMBMS_FRAME_STRU;


typedef struct
{
    UINT16      usMute;
    UINT16      usFirstFrameFlg;
}LPHY_TRACE_AGC_EMBMS_MUTE_STRU;


typedef enum
{
    AGC_ENTER_TDD_BLOCK_STATE = 0,
    AGC_TDD_BLOCK_INC_PWR,
    AGC_TDD_BLOCK_REACH_MAX_GAIN,
}AGC_TDD_BLK_EVENT_TRACE_ENUM;

typedef struct
{
    INT16     sCounter;
    UINT16    usState;
}AGC_SPECIAL_SENARION_TRACE_STRU;
typedef struct
{
    AGC_TDD_BLK_EVENT_TRACE_ENUM    enEvent;
}LPHY_TRACE_TDD_BLK_STRU;


typedef enum
{
    AGC_CONFIG_SCELL_FREQ_INFO = 0,                     						/*����AGC������Ƶ����Ϣ(����CA��Ϣ�仯)*/
    AGC_CONFIG_NCELL_FREQ_INFO,                         						/*����AGC��ƵƵ����Ϣ*/
    AGC_SWITCH_SCELL_FREQ_INFO,                        	 						/*�л�AGC������Ƶ��*/
} AGC_FREQ_CMD_ENUM;
typedef UINT16 AGC_FREQ_CMD_ENUM_UINT16;

typedef enum
{
    AGC_CHANCTR_FREQ_DISCFG = 0,
    AGC_CHANCTR_FREQ_CFG,
    AGC_CHANCTR_FREQ_BUTT,
}AGC_CHANCTR_FREQ_CFG_ENUM;
typedef UINT16 AGC_CHANCTR_FREQ_CFG_ENUM_UINT8;

#define AGC_MAX_SERV_FREQ_NUM					(LPHY_FEATURE_MAX_CARRIER_NUM+2)
#define AGC_MASTER_MODE_PCC_SCC_CA_BGS_FREQ_NUM (AGC_MAX_SERV_FREQ_NUM+1)  //cc + max ca number + bgs number
#define AGC_MAX_FREQ_NUM						(LPHY_FEATURE_MAX_INTER_EMU_NUM + AGC_MASTER_MODE_PCC_SCC_CA_BGS_FREQ_NUM)
#define AGC_FREQUENCY_NEAR_SPARE_IDX			(AGC_MAX_FREQ_NUM - 1)	/*STATIC FREQ IDX FOR BGS FREQ*/
#define AGC_INVALID_FREQ_INDEX					(AGC_MAX_FREQ_NUM)
#define AGC_MAX_NEAR_FREQ_NUM					(AGC_MAX_FREQ_NUM - 1)
#define AGC_NEAR_FREQ_NUM_DCOC                  (LPHY_FEATURE_MAX_INTER_EMU_NUM)

#define AGC_MAX_CONT_CA_NUM                     (2)

#define AGC_FREQ_CONFIG_NUM_MAX         (LPHY_FEATURE_MAX_INTER_EMU_NUM)
typedef struct
{
    AGC_FREQ_CMD_ENUM_UINT16            enAGCFreqCmd;							/*Ƶ����������*/
    UINT16                              usAGCNumOfFreq;							/*Ƶ�����ø���*/
    
    UINT16                              usAGCFreqInfo[AGC_FREQ_CONFIG_NUM_MAX];	/*��Ϊ���û��л���������Ƶ�����PCC SCC CONT_CC*/
    UINT16								ausBand[AGC_FREQ_CONFIG_NUM_MAX];		/*��Ϊ���û��л���������BAND�ŷ���PCC SCC CONT_CC*/
    
    AGC_CHANCTR_FREQ_CFG_ENUM_UINT8     aenFreqCfgInd[AGC_FREQ_CONFIG_NUM_MAX];
    UINT16                              usCcIdx[AGC_MAX_SERV_FREQ_NUM];
    UINT16                              usDualPssFlag;
    UINT16                              usRsv;
} AGC_FREQ_INFO_STRU;

typedef struct
{
    UINT16                              usAGCNumOfFreq;     /*������Ƶ�����������CAΪ2������Ϊ1*/
    UINT16                              usRsv1;
    UINT16                              usAGCFreqInfo[2];	/*����/ȥ����CCʱ idx0��ǰ�����ز�����caʱ����idx1 ��CA member*/
    UINT16								ausBand[2];			/*ͬ��*/
    AGC_CHANCTR_FREQ_CFG_ENUM_UINT8     aenFreqCfgInd[2];   /*ͬ��*/
    UINT16                              usRsv2;
    UINT16                              usCcIdx[2];
}AGC_CHANCTRL_CA_INFO_STRU;


typedef struct
{
    AGC_FREQ_INFO_STRU      stFreqInfo;
}LPHY_TRACE_FREQ_INFO_STRU;

/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_ERROR_AGC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AGC_CASE,
    LPHY_ERROR_AGC_UNKONW_FREQ
}LPHY_ERROR_AGC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_AGC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCurrentCase;
    UINT32      ulLastCase;
}LPHY_ERROR_AGC_CASE_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulFreqInfo;
}LPHY_ERROR_AGC_FREQ_INFO_STRU;


typedef union
{
    LPHY_TRACE_TDD_BLK_STRU           stAgcTddBlockEvent;
    LPHY_TRACE_AGC_EMBMS_FRAME_STRU   stAgcEmbmsTrace;
    AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario;
    LPHY_ERROR_AGC_CASE_STRU          stAgcCaseError;
    LPHY_ERROR_AGC_FREQ_INFO_STRU     stAgcFreqInfoError;
}AGC_OM_REPORT_UNION;

typedef enum
{
    AGC_SERV_FREQ = 0,  //������Ƶ��
    AGC_NEAR_FREQ,      //����Ƶ��
} AGC_FREQ_TYPE_ENUM;
typedef UINT16 AGC_FREQ_TYPE_ENUM_UINT16;

typedef struct
{
    UINT16                          usFreqInfo;
    UINT16                          usBand;
    AGC_FREQ_TYPE_ENUM_UINT16       usFreqType;
    UINT16                          usBufIdx;
}AGC_ONE_FREQ_RPT_STRU;

typedef struct
{
    AGC_ONE_FREQ_RPT_STRU astFreqInfo[16]; //��16��Ƶ�㣬HIDS �ϱ�ʶ��������⣬������������
}AGC_FREQ_RPT_STRU;


typedef enum
{
    AGC_NV_BAND_INVALID 			= 0,
    AGC_NV_BAND_SERV,
    AGC_NV_BAND_NEAR,
} AGC_NV_BAND_TYPE_ENUM;
typedef UINT16 AGC_NV_BAND_TYPE_ENUM_UINT16;


typedef struct
{
	AGC_NV_BAND_TYPE_ENUM_UINT16		enNvBandType;
	UINT16								usBandNum;
    UINT32                              ulCurrReqFlg;
    UINT32                              ulNvTableAddr;
    UINT32                              ulAGCGainTable[8];  //AGC_MAX_GAIN_LEVEL = 8, HIDS �ϱ�ʶ��������⣬������������
    UINT32                              ulRFIdxTable[8];    //AGC_MAX_GAIN_LEVEL = 8, HIDS �ϱ�ʶ��������⣬������������
}AGC_ONE_NV_RPT_STRU;


typedef struct
{
    AGC_ONE_NV_RPT_STRU astNvBufInfo[4]; //��4��NV buf�� HIDS �ϱ�ʶ��������⣬������������

}AGC_NV_BUF_RPT_STRU;


typedef struct
{
    UINT16 usFreqInfo;
    UINT16 usBandWidth;
    
    UINT16 usAntIndex;
    UINT16 usRfIndex;
    
    UINT16 usModemLoss;
    UINT16 usCurTemp;
    
    SINT16 sFreqCmpVal;
    SINT16 sTempCmpVal;

    UINT16 usErrorTable;
    SINT16 sTotalCmpVal;
}AGC_AAGC_COMPENSATION_RPT_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32 enCalcDirectConnEn;    /*1 ʹ��AGC״̬�ϱ�*/
}LPHY_REQ_AGC_CALC_DIRECT_CONN_ENA_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AGC_OM_DEF_H__ */

