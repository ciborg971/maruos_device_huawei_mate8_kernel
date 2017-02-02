
#ifndef __AFC_OM_DEF_H__
#define __AFC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "lte_nv_para_define.h"             /**/
/************************************************************
                               �궨��
************************************************************/

#define AFC_MAX_NCELL_PER_FREQ_NUM   (3)
#ifndef LPHY_MAX_RX_ANTENNA_NUM
#define LPHY_MAX_RX_ANTENNA_NUM      (2)
#endif
#define AFC_MAX_RS_WIN_LEN           (130)

#define AFC_DRX_PPM_WINDOW_LEN       (32)         /*DRX ������PPM�������*/
#define AFC_NON_CDRX_PPM_WINDOW_LEN  (64)         /*��DRX ������PPM�������*/


#define AFC_HST_MODE
#define AFC_PDM_WINDOW_LEN           (128)

#define TL_DCXO_POLY_COEF_NUM_SG     (4)          /*TL_DCXO_POLY_COEF_NUM*/

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
    LPHY_REQ_AFC_REPORT_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_AFC_PD_STATUS_ENA,
    LPHY_REQ_AFC_LOOP_STATE_ENA,
    LPHY_REQ_AFC_FIXED_PDM_ENA,
    LPHY_REQ_AFC_FILTER_STEP_SELECTION_ENA,
    LPHY_REQ_AFC_FIXED_FILTER_STEP_ENA,
    LPHY_REQ_NC_AFC_REPORT_ENA,
    LPHY_REQ_MBMS_STUB_ENA,
    LPHY_REQ_AFC_TEMP_COMP_ENA,
    LPHY_REQ_AFC_HST_ENA,
    LPHY_REQ_AFC_HST_OPEN_ENA,
    LPHY_DT_AFC_REPORT_REQ          = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_REQ, 0x100),
}LPHY_REQ_AFC_ENUM;

typedef enum
{
    AFC_OM_SWITCH_OFF = 0,
    AFC_OM_SWITCH_ON,
}AFC_OM_SWITCH_ENUM;
typedef UINT16 AFC_OM_SWITCH_ENUM_UINT16;

typedef struct
{
   AFC_OM_SWITCH_ENUM_UINT16    enNcAfcReportEn;
}LPHY_REQ_NC_AFC_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      usFixedPDMEn;    /*1 ʹ�̶ܹ�PDM*/
    UINT16      usFixedPDM;      /*1 �̶�PDMֵ*/
}LPHY_REQ_AFC_FIXED_PDM_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16   enAfcMbmsStubEn;
}LPHY_REQ_AFC_MBMS_STUB_ENA_STRU;
/*typedef union
{
    // Define the struct bits
    struct
    {
        UINT32    CpSel               : 1   ; // [0]
        UINT32    DtxcpSel            : 1   ; // [1]
        UINT32    PssSel              : 1   ; // [2]
        UINT32    ForceOL             : 1   ; // [3]
        UINT32    Reserved            : 28  ; //[31..4]
    } bits;

    // Define an unsigned member
    UINT32    ulOLPDSel;

} AFC_OLPD_SEL_UNION;
*/
// Define the struct bits
typedef struct
{
    UINT32    CpSel               : 1   ; // [0]
    UINT32    DtxcpSel            : 1   ; // [1]
    UINT32    PssSel              : 1   ; // [2]
    UINT32    ForceOL             : 1   ; // [3]
    UINT32    Reserved            : 28  ; //[31..4]
} AFC_OLPD_SEL_BITS_STRU;

typedef union
{
    AFC_OLPD_SEL_BITS_STRU  bits;

    // Define an unsigned member
    UINT32    ulOLPDSel;

} AFC_OLPD_SEL_UNION;


typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      enOLPDSelEn;    /*1 ʹ���⻷��Ƶģʽ*/
    AFC_OLPD_SEL_UNION      unOPLDFlag;      /*1 �⻷��Ƶģʽ*/
}LPHY_REQ_AFC_OLPD_SELECTION_ENA_STRU;

typedef enum
{
    AFC_KLOW_SELECTION  = 0,
	AFC_KHIGH_SELECTION = 1,
}AFC_FILTER_STEP_MODE_ENUM;
typedef UINT16 AFC_FILTER_STEP_MODE_ENUM_UINT16;
typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16             enFilterStepSelEn;    /*1 ʹ��ѡ���˲�����ģʽ*/
    AFC_FILTER_STEP_MODE_ENUM_UINT16      enFilterStepMode;      /*1 �˲�����ģʽ*/
}LPHY_REQ_AFC_FILTER_STEP_SELECTION_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      enFixedFilterStepEn;    /*1 ʹ�̶ܹ��˲�����*/
    UINT16                         usFixedFilterStep;      /*1 �̶��˲�����ֵ*/
}LPHY_REQ_AFC_FIXED_FILTER_STEP_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16 usRsv;
}LPHY_REQ_AFC_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16 usRsv;
}LPHY_REQ_AFC_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16 usRsv;
}LPHY_REQ_AFC_PPM_ENA_STRU;


typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16 usRsv;
}LPHY_REQ_AFC_UL_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16 usRsv;
}LPHY_REQ_AFC_HST_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM                  enDebugEn;    /*1 ʹ��AFC״̬�ϱ�*/
}LPHY_REQ_AFC_LOOP_STATE_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enPDStatusEn;
}LPHY_REQ_AFC_PD_STATUS_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enReportEn;    /*1 ʹ��AFC�²�����*/
}LPHY_REQ_AFC_TEMP_COMP_ENA_STRU;


typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enHstEn;       /* fixed to 1 for lab-test only, to get a better high speed(such as 250km/h) performance. */
    UINT16                              usAfcAccFoReadPeriod;
    INT32                               lHstVelThrsh;
    UINT16                              usTempDelta;
    UINT16                              usTestHstEn;
    INT32                               lFoVarThresh;
    UINT16                              usTempReadPeriod;
    UINT16                              usRev;
}LPHY_REQ_AFC_HST_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enHstOpenEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_HST_OPEN_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enMlOpenEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_ML_OPEN_ENA_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/

typedef enum
{
    AFC_RUN_STATE = 0,              /*AFC���ڼ�Ƶ����*/
    AFC_STOP_STATE,             /*AFC���ڼ�Ƶֹͣ*/
} AFC_STATE_ENUM;
typedef UINT16 AFC_STATE_ENUM_UINT16;

typedef enum
{
    AFC_IN_CYCLE_UNLOCK = 0,             /*AFC�ڻ�ʧ��*/
    AFC_IN_CYCLE_LOCK = 1,           /*AFC�ڻ�����*/
} AFC_LOOP_STATE_ENUM;
typedef UINT16 AFC_LOOP_STATE_ENUM_UINT16;

typedef enum
{
    AFC_OL_STOP = 0,              /*AFC�⻷��Ƶֹͣ*/
    AFC_TDPD_CP = 1,              /*AFC�⻷ CP��Ƶ*/
    AFC_TDPD_DTXCP  = 2,          /*AFC�⻷ DTXCP��Ƶ*/
    AFC_TDPD_PSS  = 3,            /*AFC�⻷ PSS��Ƶ*/
} AFC_OLPD_MODE_ENUM;
typedef UINT16 AFC_OLPD_MODE_ENUM_UINT16;

typedef enum
{
    AFC_RSPD = 0,
    AFC_OLPD_CP,
    AFC_OLPD_DTX,
    AFC_OLPD_PSS,
}AFC_PD_TYPE_ENUM;
typedef UINT16   AFC_PD_TYPE_ENUM_UINT16;

typedef enum
{
    AFC_NORMAL_TMPERATURE,
    AFC_NON_NORMAL_TMPERATURE
}AFC_TMPERATUR_RANGE_ENUM;
typedef UINT16 AFC_TMPERATUR_RANGE_ENUM_UINT16;

typedef enum
{
    AFC_HIGH_DRX_PERIOD,
    AFC_LOW_DRX_PERIOD
}AFC_DRX_PERIOD_ENUM;
typedef UINT16 AFC_DRX_PERIOD_ENUM_UINT16;

typedef enum
{
    PPM_DRX_NULL_STATE = 0,
    PPM_DRX_IDRX_STATE,
    PPM_DRX_CDRX_STATE,
    PPM_CON_NON_CDRX_STATE,
    PPM_DRX_STATE_BUTT
} PPM_DRX_STATE_DCXO;
typedef UINT16 PPM_DRX_STATE_DCXO_UINT16;


typedef enum
{
    DCXO_PPM_HTRAINMODE = 0,       /* ����ʶ��ģʽ*/
    DCXO_PPM_TEMPREATUREMODE,      /* �²�ˢ��ģʽ*/
    DCXO_PPM_MODE_BUTT
} DCXO_PPM_IDENTIFY_MODE;
typedef UINT16 DCXO_PPM_IDENTIFY_MODE_UINT16;

typedef enum
{
    DCXO_TC_AFCFREQPPM = 0,
    DCXO_TC_POLYCOEFF,
    DCXO_TC_DEFAULTCOEFF,
    DCXO_TC_BUTT
} DCXO_TC_OM_REPORT_MODE;
typedef UINT16 DCXO_TC_OM_REPORT_MODE_UINT16;

/*���ϵ������ָʾ����RS��CPʹ��*/
typedef struct
{
    UINT16    usCcInd;                   //���ϵ������ָʾ
    UINT16    usCCPassThrdCnt;          //ͨ������2�Ĵ���
}AFC_CC_STAT_STRU;

typedef struct
{
    INT32    lReal;//������ʵ��
    INT32    lImag;//�������鲿
}AFC_COMPLEX_STRU;

typedef struct
{
    UINT32    ulCoPower;//���ϵ�����Ӳ���
    UINT32    ulPower;//���ϵ����ĸ����
}AFC_CC_STRU;

/*RS���ϵ������ָʾ*/
typedef struct
{
    UINT16    usThrd1;     /*����1*/
    UINT16    usThrd2;     /*����2*/
    UINT16    usThrd3;     /*����3*/
    UINT16    usThrd4;     /*����3*/
    UINT16    usThrd5;     /*����3*/
    UINT16    usThrd6;     /*����3*/
    UINT16    usThrd7;     /*����3*/
    UINT16    usThrd8;     /*����3*/
}AFC_RSCC_THRE_STRU;

typedef struct
{
    UINT16                        usThreshold;
    UINT16                        usWinLen;
    UINT16                        usDataNum; /* �������м�Ƶ���ݸ���*/
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC��·״̬���ڻ�ʧ�����ڻ�����
}AFC_LOCK_STATE_STRU;


typedef struct
{
    AFC_LOCK_STATE_STRU           stIlUnlockState;

    UINT16                        usRemainFOWinLen;
    UINT16                        usRemainFreqNum; /* ����Ƶƫ���м�Ƶ���ݸ���*/
    UINT16                        usRemainFreqLevel;  //����Ƶƫ�ֵ�ָʾ
    UINT16                        usReserved;
}AFC_LOCK_PARA_STRU;
/************************************************************
                           3. Sg���ݽṹ����
************************************************************/

typedef enum
{
    LPHY_SG_AFC_REPORT_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_NC_AFC_REPORT_ENA,
    LPHY_SG_AFC_PCC_REPORT_ENA,
    LPHY_SG_AFC_SCC_REPORT_ENA,
    LPHY_SG_AFC_PPM_REPORT_ENA,
    LPHY_SG_AFC_UL_REPORT_ENA,
    LPHY_SG_AFC_ENA,
    LPHY_SG_AFC_PCC_ENA,
    LPHY_SG_AFC_SCC_ENA,
    LPHY_SG_AFC_HST_FO_ENA,
    LPHY_SG_AFC_HST_TEMP_ENA,
    LPHY_SG_AFC_DCXO_TC_ENA,
    LPHY_SG_AFC_DCXO_TC_INTERFACE_ENA,
}LPHY_SG_AFC_ENUM;

typedef struct
{
    UINT16    usCC;
    UINT16    usCCAlpha;
}AFC_ALPHA_FLT_STRU;

typedef struct
{
    AFC_ALPHA_FLT_STRU  stAlphaA;//���ϵ���������޷��Ľ��,�㷨ͼ��,A/C
    AFC_ALPHA_FLT_STRU  stAlphaB;//���ϵ������δ���޷��Ľ��,�㷨ͼ��,B/D
}AFC_ALPHA_STRU;

typedef struct
{
    UINT16                   usAlphaStateFlag;//Alpha�˲���ʼ����־
    UINT16                   usReserved;
    AFC_ALPHA_STRU           astAlpha[LPHY_MAX_RX_ANTENNA_NUM];                 /*����0��1��CP Alpha�˲����*/
}AFC_ALPHA_DATA_STRU;
typedef enum
{
    AFC_PD_UNDONE = 0,
    AFC_PD_INVALID = 1,
    AFC_PD_DONE,
}AFC_PD_DONE_ENUM;
typedef UINT16 AFC_PD_DONE_ENUM_UINT16;


typedef enum
{
    AFC_SAMPLE_RATE_7_68M = 0,
    AFC_SAMPLE_RATE_15_36M,
    AFC_SAMPLE_RATE_30_72M,
    AFC_SAMPLE_RATE_61_44M
}AFC_SAMPLE_RATE_ENUM;
typedef UINT16 AFC_SAMPLE_RATE_ENUM_UINT16;

/*CP���ϵ������ָʾ*/
typedef struct
{
    UINT16    usThrd1;     /*����1*/
    UINT16    usThrd2;     /*����2*/
    UINT16    usThrd3;     /*����3*/
    UINT16    usThrd4;     /*����4*/
    UINT16    usThrd5;     /*����5*/
    UINT16    usreserved;
}AFC_CPCC_THRE_STRU;

/**/
typedef struct
{
    AFC_CC_STAT_STRU      astRsCCind[LPHY_MAX_RX_ANTENNA_NUM];    /*����0��1��RS���ϵ������ָʾ*/
    AFC_RSCC_THRE_STRU    stRSCCThre;
    UINT16                ausCCFlag[LPHY_MAX_RX_ANTENNA_NUM];     /*����Ƶƫָʾ*/

    UINT16                usRSCCIndMax;           /*�������ڻ���CCInd�е����ֵ*/
    UINT16                usCCFlagMax;            /*������CCFlag�е����ֵ*/
}AFC_CC_IND_STRU;

typedef struct
{
    UINT16    usIndex;
    UINT16    usCounter;
    UINT16    usIndexLow;
    UINT16    usReserved;
}AFC_KLOWSNR_STRU;

typedef struct
{
    UINT16    usFOHighThreshold;
    UINT16    usFOLowThreshold;
    UINT16    usAdjustStpHigh;
    UINT16    usAdjustStpLow;
}AFC_KHIGHSNR_CFG_STRU;

typedef struct
{
    INT16                         sFilterInFOest;
    UINT16                        usFilterStep;
    UINT16                        usLoopAdjustStepLimit;
    UINT16                        usFilterInCCind;
    INT32                         lCurFOAdj;    //��ǰƵƫ������
    INT32                         lAccFO;       //Ƶƫ�������ۼ�ֵ
    INT32                         lAccFOReport;
    INT32                         lRemainFO;    //v8r1��Ӳ���Ƶƫ����  xuyoujiang
    INT16                         asRSLockWin[AFC_MAX_RS_WIN_LEN];   /* ����rs��Ƶ���� */
    //UINT16                        *pusRemainFOThresh;
    AFC_KLOWSNR_STRU              stKlowSNR;
    AFC_KHIGHSNR_CFG_STRU         stKHighSNR;
    /*��·״̬*/
    AFC_LOCK_PARA_STRU            stLockPara;

}AFC_LOOP_FILTER_STRU;
typedef struct
{
    UINT16                        usCurPDM;     //��·���Ƶƫ
    UINT16                        usInitPDM;

    UINT16                        usMultiModePdm;
    UINT16                        usPDMConfig;
    INT32                         lInitF0;      //��ʼƵƫ
    INT32                         lCsInitF0;      //��ʼƵƫ
    INT32                         lInitF0Compensation;      //��ʼƵƫ
    UINT32                        ulDeltFOCompensation;
    /* BEGIN: Added by yushujing, 2013/3/20   PN:v7r2_mod*/
    INT32                         lRFLoopFilterPCCIni;
    INT32                         lRFLoopFilterPCCCur;
    //INT32                         lSitaIni;
    /* END:   Added by yushujing, 2013/3/20 */

    INT32                         lDrxPDM;
	INT32                         lCsInitPDM;

	INT32                         lSccInitFO;
	UINT16                        usSccSampleRateValid;
	AFC_SAMPLE_RATE_ENUM_UINT16   usSccSampleRate;

	AFC_SAMPLE_RATE_ENUM_UINT16   usPccSampleRate;
	AFC_SAMPLE_RATE_ENUM_UINT16   usUlSampleRate;

	UINT16                        usHTrainFlag;
	UINT16                        usRev;
}AFC_PDM_CTRL_STRU;


typedef struct
{
    //AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC��·״̬���ڻ�ʧ�����⻷ʧ�����⻷����
    /*��·�˲�*/

    AFC_LOOP_FILTER_STRU          stLoopFilter;
    AFC_PDM_CTRL_STRU             stPdmCtrl;

}AFC_LOOP_CTRL_STRU;


/*��Ƶ������*/
typedef enum
{
     AFC_SDR_RUN = 1,
     AFC_SDR_STOP,
}AFC_PD_CONTROL_ENUM;
typedef UINT16 AFC_PD_CONTROL_ENUM_UINT16;
typedef enum
{
    AFC_EMBMS_HOLD = LPHY_TRUE,
    AFC_EMBMS_UNHOLD = LPHY_FALSE
}AFC_EMBMS_HOLD_CONFIG_ENUM;
typedef UINT16 AFC_EMBMS_HOLD_CONFIG_ENUM_UINT16;
typedef enum
{
    AFC_REFRESH_PDM_SUCCESS = 0,
    AFC_REFRESH_PDM_FAIL_UNLOCK,
    AFC_REFRESH_PDM_FAIL_CC,
    AFC_REFRESH_PDM_FAIL_PAR,
    AFC_REFRESH_PDM_FAIL_TEMP,
}AFC_REFRESH_PDM_CODE_ENUM;
typedef UINT16 AFC_REFRESH_PDM_CODE_ENUM_UINT16;

typedef struct
{

    /*�⻷BBP���:*/
    /*CP��Ƶ�����s19,���ϵ������u31��ĸu22*/
    /*DTXCP��Ƶ�����s19*/
    /*PSS��Ƶ�����s31*/
    /*�ڻ�BBP���*/
    /*RS��Ƶ�����s19,���ϵ������u31��ĸu22*/

    AFC_COMPLEX_STRU    astPwr[LPHY_MAX_RX_ANTENNA_NUM];         /*����0�⻷��Ƶ����ͽ������Ϊʵ�����鲿*/
    AFC_COMPLEX_STRU    stCordicIn;        /*�����߲���ͺϲ���CordicƵƫ����ģ������*/
    /*���ϵ��*/
    AFC_CC_STRU         astCC[LPHY_MAX_RX_ANTENNA_NUM];               /*����0��1�⻷���ϵ�����Ӻͷ�ĸ*/

    /*Alpha�˲�*/
    AFC_ALPHA_DATA_STRU      stAlphaData;                 /*����0��1��CP Alpha�˲����*/

    AFC_PD_DONE_ENUM_UINT16       enPDDoneFlag;
    AFC_PD_CONTROL_ENUM_UINT16    enPDCtrl;
    UINT16                        usFirstFrameFlag;
    UINT16                        usFrameCounter;

    AFC_EMBMS_HOLD_CONFIG_ENUM_UINT16 enPdHoldFlag;
    /*��Ƶ������*/
    INT16                         sPDFOEst;//Ƶƫ����
    UINT16                        usPeriod;//��Ƶ����
    UINT16                        usLHz;
    //UINT16    usCounter;//��Ƶ��������֡����
}AFC_PD_STATE_STRU;
typedef struct
{
    AFC_PD_STATE_STRU       stRSPDState;//AFC�ڻ���Ƶ״̬
    AFC_CC_IND_STRU         stAFCCCInd;
}AFC_PD_RESULT_STRU;
#define AFC_MAX_CCFLAG                     (5)
#define AFC_MAX_CCFLAG_LEVEL               (4)

typedef struct
{
    UINT16  ausPeriod[2];
    UINT16  ausCCFlagWindowslenth[6][5];
    UINT16  ausCCFlagThreNCP[4];
    UINT16  ausCCFlagThreECP[4];
    UINT16  ausRsThrd2Fdd[2][6];
    UINT16  ausRsThrd3Fdd[2][6];
    UINT16  ausRsThrd2TddCfg0[2][6];
    UINT16  ausRsThrd3TddCfg0[2][6];
    UINT16  ausRsThrd2TddNCfg0[2][6];
    UINT16  ausRsThrd3TddNCfg0[2][6];
    UINT16  ausRsThrd4[2];
    UINT16  ausRsThrd5[2];
    UINT16  usRsThrd6;
    UINT16  usRsThrd7;
    UINT16  usRsThrd8;
    UINT16  usRSCCIndThreHL;
}AFC_RS_PARA_CONFIG_STRU;
typedef struct
{
    AFC_PD_RESULT_STRU        stRsPdResult;
    AFC_RS_PARA_CONFIG_STRU   stRsConfig;
    AFC_LOOP_FILTER_STRU      stLoopFilter;
}AFC_PROC_STRU;
typedef struct
{
    INT32    lCrsInitAccFo;
    INT32    lEmbmaThetaInitial;
    INT32    lEmbmaPhaseStep;
    INT32    lEmbmsOutPhase;
    INT32    lEmbmaBaseBandFo;
}AFC_EMBMS_PHASE_STRU;
typedef struct
{
    UINT16   usCellId;
    UINT16   usFreqInfo;
    UINT16   usPDM;
    UINT16   usFilterStep;

    UINT16                        usRemainFreqLevel;  //����Ƶƫ�ֵ�ָʾ
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC��·״̬���ڻ�ʧ�����ڻ�����

    INT32    lAccFO;       //Ƶƫ�������ۼ�ֵ
    INT32    lInitF0;

	UINT16   usInitPDM;
	UINT16   usTcFlag;
	INT32    lDrxPDM;
	INT32    lCsInitPDM;
	INT16    sLastTemp;
	INT16    sCurrTemp;

}AFC_BACKUP_CELL_PARA_STRU;
typedef struct
{
    UINT16                    usCellID;
    UINT16                    usFreqInfo;
    AFC_PROC_STRU             stCrsProc;

}AFC_CARRIER_PARA_STRU;
/* BEGIN: Added by yushujing, 2013/4/22   PN:v7r2_mod*/
typedef struct
{
    INT32 lPhaseInitNext;
    INT32 lPhaseInit;
    INT32 lPhaseDelta;
    INT32 lPhaseDeltaUl;
    INT32 lPhaseDeltaUlConfig;
    INT32 lPhaseUpPts;
    UINT32 ulOffsetCalcFlag;
    INT32 lOffset0;
    INT32 lOffset1;
    INT32 lPccConverIni;
    INT32 lPccConverStep;
    INT32 lSccConverIni;
    INT32 lSccConverStep;
    INT32 lInitCurPcc;
    INT32 lPhaseStepPcc;
    INT32 lInitCurScc;
    INT32 lPhaseStepScc;
    INT32 lUlAccInitPhase;
    UINT16 usUlConfig;
    UINT16 usRev;
}AFC_TPA_PARA_STRU;

/* END:   Added by yushujing, 2013/4/22 */

typedef struct
{
    UINT32 ulFOAccAverage;
    INT32  lTcInitFo;
    INT32  lFreqRatio;
    INT16  sPastTmperature;      //��һ�β�ѯ�¶ȣ���λ0.1���϶�
    INT16  sCurrTmperature;      //��ǰ�¶�
    INT16  sTmperatureDiffCnt;   //�²�������޼���
    INT16  sFreqOutRangeCnt;
    INT16  sFreqLockErr;         //������ָʾ
    INT16  sRes;

}AFC_DCXO_TEMPERATURE_COMPENSATE;

typedef struct
{
    SINT32 aslAccFoSlidingWindow[AFC_PDM_WINDOW_LEN];
    SINT32 slAccFoSum;
    UINT16 usAccFoDataNum;
    UINT16 usPdPeriodNum;
    UINT16 usReadIdx;
    SINT16 sLastFoTemp;
    SINT16 sCurFoTemp;
    SINT16 sLastTemp;
    UINT16 usTempValid;
    UINT16 usTempReadNum;
    SINT32 slFoComp;
    INT64  lTotalFoVar;
    INT64  lFoVarThresh;
}AFC_HSTRAIN_RESULT_STRU;

typedef struct
{
    SINT32 aslAccFoSlidingWindow[AFC_PDM_WINDOW_LEN];
    SINT32 slAccFoSum;
    UINT16 usAccFoDataNum;
    UINT16 usPdPeriodNum;
    UINT16 usReadIdx;
    SINT16 sLastFoTemp;
    SINT16 sCurFoTemp;
    UINT16 usRev;
    SINT32 slFoComp;
    SINT32 lTotalFoVar;
    SINT32 lFoVarThresh;
}AFC_HST_FO_STRU;

typedef struct
{
    SINT16 sLastTemp;
    UINT16 usTempValid;
    UINT16 usTempReadNum;
    UINT16 usRev;
}AFC_HST_TEMP_STRU;

typedef struct
{
    AFC_HST_FO_STRU   stHstFo;
    AFC_HST_TEMP_STRU stHstTemp;
}AFC_HST_OM_STRU;


typedef struct
{
   INT32  lData;    /*  ������PPMֵ*/
   INT16  sTemp;    /*  �������¶�ֵ*/
   INT16  sReserved;
} PPM_SLIDWIN_STRU;

typedef struct
{
   PPM_SLIDWIN_STRU astPpmSlidingWindow[AFC_NON_CDRX_PPM_WINDOW_LEN]; /*������������64*/
   INT32  lPpmSum;                                           /*  ���������ݺ�*/
   UINT16 usPpmDataNum;                                      /*  ���������*/
   UINT16 usPpmUpdatePos;                                    /*  ���²��������λ��*/
   UINT16 usPastDrxState;                                    /*  �ϸ�������DRX״̬*/
   UINT16 usPastPointTimeFrm;                                /*  �ϸ����������ʱ��֡��*/
   UINT16 usPastPointTimeSubFrm;                             /*  �ϸ����������ʱ����֡��*/
   UINT16 usReserved;
} AFC_DCXO_PPM_POINT_STRU;

typedef struct
{
   UINT16 usHighTrainFlag;                                      /* ����ʶ���־��0�Ǹ�����1����*/
   UINT16 usTemperatureFlag;                                    /* �²�ˢ�±�־��0��ˢ�£�1ˢ��*/
} AFC_DCXO_PPM_CONTRL_STRU;

typedef NV_LTE_DCXO_PPM_UPDATE_THRESHOLD_STRU AFC_DCXO_PPMNVPARA_STRU;

typedef struct
{
    AFC_DCXO_PPM_POINT_STRU          astPpmPointResult[2];/*0�洢������������Ϣ��1���²���������Ϣ*/
    AFC_DCXO_PPM_CONTRL_STRU         stPpmContrlFlag;
    AFC_DCXO_PPMNVPARA_STRU          stPpmNvPara;
}AFC_DCXO_PPM_PARA_STRU;

typedef struct
{
    UINT16 usFratioSetFlag;
	UINT16 usReserved;
    INT32  lFratio;
    INT32  lLMasterInitFO;
    UINT16 usTcSetFlag;
    UINT16 usInitFOSetFlag;
}AFC_SWITCH_TO_L_MASTER;


typedef struct
{
    INT32  lAccFO;
    INT16  sLastTemperature;
    INT16  sCurrTemperature;
    UINT16 usConfigFlag;
	UINT16 usInitPDM;
	INT32  lCsInitPDM;
	INT32  lDrxPDM;

}AFC_BGS_CONFIG;

typedef struct
{
    INT16  sLastTemperature;
    INT16  sCurrTemperature;
	UINT16 usTCFlag;
	UINT16 usReserved;

}AFC_SWITCHBACK_TC;

typedef struct
{
	UINT8                     		usAfcContinuouseFrmFlag;
	UINT8                     		usRsv;
	AFC_STATE_ENUM_UINT16     		aenAFCState;
	AFC_CARRIER_PARA_STRU     		astCaAfc;
	AFC_TPA_PARA_STRU         		stAfcTpaPara;
}AFC_CC_PARA_STRU;
typedef struct
{
    UINT16                    		usSweepCounter;
    UINT16                    		usAfcMbmsContinuouseFrmFlag;
    AFC_STATE_ENUM_UINT16     		enAFCMbmsState;
    UINT16                          usSccFreqInfo;
    AFC_PROC_STRU             		stMrsProc;
    AFC_PDM_CTRL_STRU         		stPdmCtrl;
    AFC_EMBMS_PHASE_STRU      		stEmbmsPhase;
    AFC_BACKUP_CELL_PARA_STRU 		stHoBackupPara;
    AFC_BACKUP_CELL_PARA_STRU 		stBgsAnrBackupPara;
    AFC_DCXO_TEMPERATURE_COMPENSATE	stAfcTmperatureComp;
    AFC_SWITCH_TO_L_MASTER			stAfcSwitchToL;
    AFC_BGS_CONFIG            		stAfcBgsConfig;
    //AFC_HSTRAIN_RESULT_STRU         stHSTResult;
}AFC_NONCC_PARA_STRU;
typedef struct
{
    //UINT16                    usLastCellPDM;
    //UINT16                    usLastCellId;
	AFC_CC_PARA_STRU stAfcCc[LPHY_FEATURE_MAX_CARRIER_NUM];
	AFC_NONCC_PARA_STRU stAfcNonCc;
	#if 0
	AFC_CARRIER_PARA_STRU     astCaAfc[LPHY_FEATURE_MAX_CARRIER_NUM];

    UINT16                    usSweepCounter;
    AFC_STATE_ENUM_UINT16     aenAFCState[LPHY_FEATURE_MAX_CARRIER_NUM];//��һ��֡AFC��״̬��START/STOP/HOLD
    UINT8                     usAfcContinuouseFrmFlag[LPHY_FEATURE_MAX_CARRIER_NUM];

	AFC_STATE_ENUM_UINT16     enAFCMbmsState;
    UINT16                    usAfcMbmsContinuouseFrmFlag;
    //AFC_PROC_STRU             stCrsProc;
    AFC_PROC_STRU             stMrsProc;

    AFC_PDM_CTRL_STRU         stPdmCtrl;
    AFC_EMBMS_PHASE_STRU      stEmbmsPhase;
    AFC_BACKUP_CELL_PARA_STRU stHoBackupPara;
    AFC_BACKUP_CELL_PARA_STRU stBgsAnrBackupPara;
    /* BEGIN: Added by yushujing, 2013/4/22   PN:v7r2_mod*/
    AFC_TPA_PARA_STRU         stAfcTpaPara[LPHY_FEATURE_MAX_CARRIER_NUM];
    /* END:   Added by yushujing, 2013/4/22   PN:v7r2_mod*/
    AFC_DCXO_TEMPERATURE_COMPENSATE stAfcTmperatureComp;     //��ʼ��?
	AFC_SWITCH_TO_L_MASTER    stAfcSwitchToL;
    AFC_BGS_CONFIG            stAfcBgsConfig;
	#endif
   AFC_DCXO_PPM_PARA_STRU     stDcxoPpmPara;
}AFC_PARA_STRU;

typedef struct
{
    UINT16                    		usSweepCounter;
    UINT16                          usSccFreqInfo;
    UINT16                          usCurPDM;     //��·���Ƶƫ
    UINT16                          usInitPDM;
    INT32                           lInitF0;      //��ʼƵƫ
    INT32                           lCsInitF0;      //��ʼƵƫ
    INT32                           lInitF0Compensation;      //��ʼƵƫ
    INT32                           lRFLoopFilterPCCCur;
    INT32                           lSccInitFO;
	UINT16                          usSccSampleRateValid;
	AFC_SAMPLE_RATE_ENUM_UINT16     usSccSampleRate;
	AFC_SAMPLE_RATE_ENUM_UINT16     usPccSampleRate;
	AFC_SAMPLE_RATE_ENUM_UINT16     usUlSampleRate;
	UINT16                          usHTrainFlag;
	UINT16                          usRev;

    AFC_BACKUP_CELL_PARA_STRU 		stHoBackupPara;
    AFC_BACKUP_CELL_PARA_STRU 		stBgsAnrBackupPara;
    AFC_DCXO_TEMPERATURE_COMPENSATE	stAfcTmperatureComp;
    AFC_SWITCH_TO_L_MASTER			stAfcSwitchToL;
    AFC_BGS_CONFIG            		stAfcBgsConfig;
}AFC_COMMON_STRU;

typedef struct
{
    UINT16                          usCellID;
    UINT16                          usFreqInfo;
    UINT16                          usPeriod;//��Ƶ����
    AFC_STATE_ENUM_UINT16     		enAFCState;
    UINT16                          usCcInd[LPHY_MAX_RX_ANTENNA_NUM];

    INT16                           sFilterInFOest;
    UINT16                          usFilterInCCind;
    INT32                           lCurFOAdj;    //��ǰƵƫ������
    INT32                           lAccFOReport;
    INT32                           lRemainFO;    //v8r1��Ӳ���Ƶƫ����  xuyoujiang


    INT32                           lPhaseDelta;
    INT32                           lPhaseDeltaUlConfig;
    INT32                           lOffset0;
    INT32                           lOffset1;
    INT32                           lPccConverStep;
    INT32                           lSccConverStep;
    INT32                           lPhaseStepPcc;
    INT32                           lPhaseStepScc;

	UINT8                     		usAfcContinuouseFrmFlag;
	UINT8                     		usRsv[3];

}AFC_CACCRIER_STRU;

typedef struct
{
    AFC_COMMON_STRU     stAfcCommon;
    AFC_CACCRIER_STRU   astAfc[LPHY_FEATURE_MAX_CARRIER_NUM];
}AFC_OM_REPORT_STRU;

typedef struct
{
    UINT16      usCellId;      //С��ID
    INT16       sPDFOEst;      //Ƶƫ
    UINT16      usCurPDM;      //PDM
    UINT16      usRSCCIndMax;  //���ϵ������
    UINT16      usFilterStep;
    INT16       sFilterInFOest;
    UINT16      usReserved;
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;   //��·������־
    INT32       lInitF0;
    INT32       lAccFO;
}LPHY_NC_AFC_REPORT_STRU;

typedef struct
{
    UINT16                     usFreqInfo;
    LTE_BAND_WIDTH_ENUM_UINT16 enBandwidth;
    UINT16                     usMsrCellNum;
    UINT16                     usTxNum;
    LPHY_NC_AFC_REPORT_STRU    astNcAfcReport[AFC_MAX_NCELL_PER_FREQ_NUM];
}LPHY_SG_NC_AFC_REPORT_ENA_STRU;

typedef struct
{
    DCXO_TC_OM_REPORT_MODE_UINT16  enCalcMode;
    INT16                          sCurrTemp;
    INT32					       lAfcValue;
    INT32                          lDelta;
    UINT32					       aulMantissaDefault[TL_DCXO_POLY_COEF_NUM_SG];  /* ���δ��a0,a1,a2,a3��β�� */
	UINT16					       ausExponentDefault[TL_DCXO_POLY_COEF_NUM_SG];  /* ���δ��a0,a1,a2,a3��ָ�� */
}LPHY_SG_AFC_DCXO_TC_STRU;

typedef struct
{
    DCXO_TC_OM_REPORT_MODE_UINT16  enCalcMode;
    INT16                          sCurrTemp;
    INT32					       lAfcValue;
    INT32                          lDelta;
}LPHY_SG_AFC_DCXO_TC_INTERFACE_STRU;
/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_AFC_LOOP_STATE         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_AFC_OLPD_MODE,
    LPHY_TRACE_AFC_STATE,
    LPHY_TRACE_AFC_PARA_UPDATE,
}LPHY_TRACE_AFC_ENUM;

typedef struct
{
    UINT32      ulLineNum;
    AFC_LOOP_STATE_ENUM_UINT16      enNewLoopState;
    UINT16      usReserved;
}LPHY_TRACE_AFC_LOOP_STATE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    AFC_PD_TYPE_ENUM_UINT16      ulOlpdMode;
}LPHY_TRACE_AFC_OLPD_MODE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    AFC_STATE_ENUM      ulAfcState;
}LPHY_TRACE_AFC_STATE_STRU;
typedef enum
{
    AFC_SWITCH_CELL = 0,
    AFC_SWITCHBACK,
    AFC_INIT_START,
    AFC_UPDATE_DL_PARA,
    AFC_CAMPCELL,
    AFC_CONTIGOUS_CA,
    AFC_NONCONTIGOUS_CA,
    AFC_SCC_START,
    AFC_SCC_STOP,
    AFC_CONTIGOUS_CA_INACTIVE,
	AFC_NONBLIND_NONIRAT_HO,
	AFC_INTER_MEAS,
	AFC_RESUME_TPA,
	AFC_SCC_MEAS_TPA,
}AFC_UPDATE_CELL_CAUSE_ENUM;
typedef UINT16 AFC_UPDATE_CELL_CAUSE_ENUM_UINT16;

typedef struct
{
    AFC_UPDATE_CELL_CAUSE_ENUM_UINT16 enUpdateCause;
    AFC_SAMPLE_RATE_ENUM_UINT16       enSampleRate;
    UINT16                            usFreqInfo;
    UINT16                            usRev;
}LPHY_TRACE_AFC_PARA_UPDATE_STRU;
/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_ERROR_AFC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AFC_CASE,
    LPHY_ERROR_AFC_ZERO_DIV,
    LPHY_WARNING_AFC_RTT_SWITCH_OFF,
}LPHY_ERROR_AFC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_AFC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCurrentCase;
    UINT32      ulLastCase;
}LPHY_ERROR_AFC_CASE_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
}LPHY_ERROR_AFC_ZERO_DIV_STRU;

/************************************************************
                           7. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_IND_AFC_PD_STATUS_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_AFC_LOOP_STATE_ENA,
}LPHY_IND_AFC_ENUM;


typedef struct
{
    AFC_PD_TYPE_ENUM_UINT16       enPDType;
    UINT16                        usAlphaStateFlag;//Alpha�˲���ʼ����־
    INT16                         sPDFOEst;//Ƶƫ����
    UINT16                        usPeriod;//��Ƶ����
    UINT16                        ausCCFlag[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        ausDTXFlag[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        usCCAlphaA[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        usCCAlphaB[LPHY_MAX_RX_ANTENNA_NUM];
    AFC_CC_STAT_STRU              astCCind[LPHY_MAX_RX_ANTENNA_NUM];    /*����0��1��RS���ϵ������ָʾ*/
    AFC_COMPLEX_STRU              astPwr[LPHY_MAX_RX_ANTENNA_NUM];         /*����0�⻷��Ƶ����ͽ������Ϊʵ�����鲿*/
    AFC_CC_STRU                   astCC[LPHY_MAX_RX_ANTENNA_NUM];               /*����0��1�⻷���ϵ�����Ӻͷ�ĸ*/
    AFC_RSCC_THRE_STRU            stCCThre;
}LPHY_IND_AFC_PD_STATUS_ENA_STRU;

typedef struct
{
    /*��·�˲�*/
    AFC_LOOP_STATE_ENUM_UINT16      enAFCLoopCurState;//AFC��·״̬���ڻ�ʧ�����⻷ʧ�����⻷����
    UINT16      usLastCellPDM;
    UINT16      usFilterInCCind;
    INT16       sFilterInFOest;

    INT32       lCurFOAdj;    //��ǰƵƫ������
    INT32       lAccFO;       //Ƶƫ�������ۼ�ֵ
    INT32       lInitF0;      //��ʼƵƫ
    AFC_LOCK_PARA_STRU            stLockPara;
} LPHY_IND_AFC_LOOP_STATE_ENA_STRU;

typedef struct
{
    UINT16      usFOestUnderFlg;
    UINT16      usFixRawVelocityFlg;
}AFC_HS_DL_PARA_STRU;

typedef struct
{
    UINT32  ulFilterStateFlag;
    SINT32  slFilterIn;
    SINT32  slFilterCoef;
    SINT32  slACCFOReg;
    SINT16  sFOest;
    UINT16  usFOestPassCtl;
    SINT16  sLastTemp;
    SINT16  sCurTemp;
    SINT32  slFoComp;
}AFC_UL_ALPHA_FLT_STRU;
typedef struct
{
    UINT16      usULPDMConfig;
    UINT16      usDLFreqInfo;
    UINT16      usULFreqInfo;
    UINT16      usFrameType;
    UINT16      usAFCthres0;
    UINT16      usAFCthres1;
    SINT32      slULCurBBRotator;
    SINT32      slULLastBBRotator;
    SINT32      slULCurACCFO;
    SINT32      slDLCurACCFO;
    SINT32      slACCFOlongTerm;
    SINT16      slPhaseUL;
    SINT16      sRev;
    AFC_UL_ALPHA_FLT_STRU stULFilter;
}AFC_UL_PARA_STRU;

/************************************************************
                           8. DT·�����ݽṹ����
************************************************************/
/*typedef enum
{
    LPHY_DT_AFC_REPORT_REQ         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_DT, 0x1)

}LPHY_DT_AFC_REQ_ENUM;*/

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16    enAfcReportEn;
    UINT16   usReportPeriod;
}LPHY_DT_AFC_REPORT_REQ_STRU;

typedef enum
{
    LPHY_DT_AFC_REPORT_RESERVED         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_DT, 0x0),
    LPHY_DT_AFC_REPORT_IND,
    LPHY_DT_AFC_REPORT_CA_IND

}LPHY_DT_AFC_IND_ENUM;

typedef struct _LPHY_DT_AFC_REPORT_CA_IND_STRU__
{
    UINT8      ucCcValidFlg;
	UINT8      ucCcIdx;
	UINT16     usRsv;

    UINT16     usSFN;
    UINT16     usSubFn;
    UINT16     usPeriod;
    UINT16     usRsv0;
    INT32      lCurFOAdj;
}LPHY_DT_AFC_REPORT_CA_IND_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AFC_OM_DEF_H__ */

