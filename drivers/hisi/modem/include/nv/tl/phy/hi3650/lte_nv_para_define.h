


#ifndef __LTE_NV_PARA_DEFINE_HI6921_H__
#define __LTE_NV_PARA_DEFINE_HI6921_H__
#include "TLPhyInterface.h"
#include "lt_nv_common_interface.h"
#include "LRrcLPhyInterface.h"
#include "PhyNvDefine.h"

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
#define    LPHY_NV_ALL_BAND         /*lte 22 Ƶ����*/
#define    LPHY_TERM_NV_DSP        /*�ն�NV �������*/
#define    LPHY_TX_DUAL_ANTENNA         2
#define    INTERP_COEF_ROW              9
#define    INTERP_COEF_COLUMN           3
#define    PB_TIME_DOMAIN_INTP_NUM     10
#define    PDU_TIME_DOMAIN_INTP_NUM    14
#define    IIR_ALPHA_NUMBER             6
#define    CHE_CPE_ROW                  8
#define    CHE_CPE_COLOUM               8
#define    LPHY_MAX_BANDWIDTH_NUM       6
#define    NUM_0                        0
#define    NUM_1                        1
#define    NUM_2                        2
#define    NUM_3                        3
#define    LPHY_NS14_BANDWIDTH_NUM      2
#define    FRE_845                   8450
#define    FRE_849                   8490

#define    AGC_INTF_DET_THR_BW_NUM     12

#define    RF_9361_HW_TYPE              10
#define    RF_6360_HW_TYPE              11
/* BEGIN: Added by luliwu,  2012/1/13  PN: DTS_V210_12345678 */
#define    UL_APT_VBIAS_NUM             16

/*ET�����漰�ĺ궨��*/
#define    UL_ET_MAX_ET_MIPICMD_NUM       10
#define    UL_ET_MAX_APT_MIPICMD_NUM      10
#define    UL_ET_MAX_BYPASS_MIPICMD_NUM   16
#define    UL_ET_MAX_GAIN_COMP_NUM        16
#define    UL_ET_LUT_TBL_MAX_NUM          256
#define    UL_ET_FINEDLY_PARA_NUM          10

#define    LHPA_LOAD_NV_ET_VENDOR_TI        0
#define    LHPA_LOAD_NV_ET_VENDOR_R2        1
#define    LHPA_LOAD_NV_ET_VENDOR_QU        2

#define    UL_ET_ETM_CURMODE_DEFAULT      0
#define    UL_ET_ETM_CURMODE_ET            1
#define    UL_ET_ETM_CURMODE_APT           2
#define    UL_ET_ETM_CURMODE_BYPASS        3
#define    AGC_MAX_GAIN_LEVEL    (8)


#define    AGC_MAX_INTERF_TYPE   2
#define    AGC_MAX_GAIN_TYPE     3

#define    NV_RFIC_BALONGV7_MULTIBAN_BAND7
/* #define NV_RFIC_BALONGV7_MULTIBAN_BAND38 */
/* BEGIN: Added by shijiahong, 2011/12/23   PN:DTS201112302952*/
#define    MAX_HI6360_INITIAL_REG_NUM       40
#define    MAX_DSP_CFG_REG_RESV_NUM         4

/*k3v3+ȫƵ������*/
#define MAX_PCC_BAND_NUM  		32
#define MAX_RX_LNA_NUM  		28
#define MAX_SCC_BAND_NUM        6
#define MAX_LSCANW_BAND_NUM     (5)

#define    MAX_RF_BAND_NUM      (MAX_PCC_BAND_NUM)

#define    RF_TX_FREQ_NUM (32)
#define    RF_RX_FREQ_NUM (32)
#define    RF_TX_GAIN_NUM (16)
#define    RF_TX_GAIN_6362_NUM (20)      /*K3V5 �޸�apc table num*/
#define    RF_BBGAIN_NUM_PER_RFGAIN (2)  /*k3v5_bzj ÿ��rf gainУ׼��bb gain�ĸ���*/
#define    RF_BAND_WIDTH_NUM         (8)  /*k3v5_bzj lte����ĸ���*/
#define    RF_PA_GAIN_NUM            (3)
#define    RF_HD3_CAL_NUM            (4)  /*ÿ��band֧�ֵ����У׼����*/
#define    RF_HD3_CAL_POWER_POINTNUM (4) /*ÿ����֧�ֵĹ��ʿ����ָ���*/
//#define    RF_HD3_POW_NUM   4
#define    RF_FILTER_MAX_COMP_AREA_NUM   (4) /*rf�˲�����󲹳��������*/
/* END:   Added by shijiahong, 2011/12/23   PN:DTS201112302952*/
/*PBCH  �����׻�*/

#define    PD_PWR_CUR_MAX_NUM         16   /*PD�������ߵ����*/
#define    PD_CAL_DAC_CFG_MAX_NUM     16   /*PD��У׼����DAC���ù���*/
#define    PD_CAL_VGA_CFG_MAX_NUM     8    /*PD��У׼����DAC���ù���*/
#define    PD_CAL_TX_REQ_NUM           16

#define    MAX_RFIC_PATH_NUM           2
#define    MAX_RX_ANT_NUM              2
#define    MAX_IIP2_CHAN_NUM           4
#define    PA_TEMP_NUM                 32


/*ET DPD*/
#define    ET_DPD_TAB_NUM               (512)
#define    ET_DPD_BANDWIDTH_NUM         (6)
#define    ET_DPD_VCC_MAX_NUM           (12)
#define    ET_DPD_DELAY_MAX_NUM         (10)
#define    ET_DPD_COMPLEX_GAIN_NUM      (128)
#define    ET_DPD_TEMP_COMP_NUM         (10)
#define    ET_DPD_FREQ_NUM              (16)
#define    ET_DPD_VGA_GAIN              (7)
#define    ET_DPD_MIPI_MAX_NUM          (20)
#define    ET_DPD_MIPI_TRIGER_MAX_NUM   (5)
#define    ET_DPD_VGA_MAX_NUM           (1)
#define    ET_POW_MAX_NUM               (20)
#define    APT_POW_MAX_NUM              (20)
#define    ET_GAIN_MAX_NUM              (20)
#define    EXTERNAL_LNA_MIPI_NUM        (2)

/************************************************************
                             ���ݽṹ����
************************************************************/
#if 0

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*�����׻�������1*/
    UINT8 WhitenRuuSize2;                                 /*�����׻�������2*/
    UINT8 WhitenThreMode;                                 /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
    UINT8 Threshold_A;                                    /*�����׻�����Ӧ��������Threshold_A*/
    UINT8 Threshold_B;                                    /*�����׻�����Ӧ��������Threshold_B*/
    UINT8 WhitenSwitchPBCH;                               /*PBCH�����׻�Ӳ����*/
    UINT8 Rsv0[2];
}NV_PB_IRC_STRU;

/*PDC  IRC*/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*�����׻�������1*/
    UINT8 WhitenRuuSize2;                                 /*�����׻�������2*/
    UINT8 PdcSInd;                                        /*��ʹ��PDS sym4: 0 ʹ��PDS sym4: 1 */
    UINT8 WhitenThreMode;                                 /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
    UINT8 Threshold_A;                                    /*�����׻�����Ӧ��������Threshold_A*/
    UINT8 Threshold_B;                                    /*�����׻�����Ӧ��������Threshold_B*/
    UINT8 Threshold_C;                                    /*�����׻�����Ӧ��������Threshold_C*/
    UINT8 WhitenSwitchPDCCH;                              /*PDCCH�����׻�Ӳ����*/
    UINT8 WhitenSwitchPCFICH;                             /*PCFICH�����׻�Ӳ����*/
    UINT8 WhitenSwitchPHICH;                              /*PHICH�����׻�Ӳ����*/
    UINT8 Rsv0[2];
    UINT16 PHICH_TH_NonWhiten;                            /*PHICH�����׻�Ӳ���عر�ʱ������*/
    UINT16 PHICH_TH_Whiten;                               /*PHICH�����׻�Ӳ���ؿ���ʱ������*/
} NV_PDC_IRC_STRU;

/*PDS  IRC*/
typedef struct
{
     UINT8 WhitenRuuSize1;                                /*�����׻�������1*/
     UINT8 WhitenRuuSize2;                                /*�����׻�������2*/
     UINT8 PdsSInd;                                       /*��һ��slot �������� ʹ��������0��1*/
     UINT8 WhitenThreMode;                                /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
     UINT8 Threshold_A;                                   /*�����׻�����Ӧ��������Threshold_A */
     UINT8 Threshold_B;                                   /*�����׻�����Ӧ��������Threshold_B */
     UINT8 Threshold_C;                                   /*�����׻�����Ӧ��������Threshold_C */
     UINT8 WhitenSwitchPDSCH;                             /*PDSCH�����׻�Ӳ����*/
     UINT8 BfWhitenRuuSize1;                              /*�����׻�������1*/
     UINT8 BfWhitenRuuSize2;                              /*�����׻�������2*/
     UINT8 BfPdsSInd;                                     /*��һ��slot �������� ʹ��������0��1*/
     UINT8 BfWhitenThreMode;                              /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
     UINT8 BfThreshold_A;                                 /*�����׻�����Ӧ��������Threshold_A */
     UINT8 BfThreshold_B;                                 /*�����׻�����Ӧ��������Threshold_B */
     UINT8 BfThreshold_C;                                 /*�����׻�����Ӧ��������Threshold_C */
     UINT8 BfWhitenSwitchPDSCH;                           /*PDSCH�����׻�Ӳ����*/
} NV_PDS_IRC_STRU;
#endif
typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*�����׻�������1*/
    UINT8 WhitenRuuSize2;                                 /*�����׻�������2*/
    UINT8 WhitenThreMode;                                 /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
    UINT8 Threshold_A;                                    /*�����׻�����Ӧ��������Threshold_A*/
    UINT8 Threshold_B;                                    /*�����׻�����Ӧ��������Threshold_B*/
    UINT8 WhitenSwitchPBCH;                               /*PBCH�����׻�Ӳ����*/
    UINT8 Rsv0[2];
}NV_PB_IRC_STRU;

#define NV_PB_IRC_STRU_DEFAULT						{\
														6,\
														3,\
														0,\
														0,\
														100,\
														1,\
														0\
													}


/*PB  IRC*/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*�����׻�������1:alex ��62   */
    UINT8 WhitenRuuSize2;                                 /*�����׻�������2             */
	UINT8 BalanceEst;									  /*����ƽ���ж�ʹ��che_irc_bl_est*/
    UINT8 WhitenThreMode;                                 /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
    UINT8 Threshold_A;                                    /*�����׻�����Ӧ��������Threshold_A*/
    UINT8 Threshold_B;                                    /*�����׻�����Ӧ��������Threshold_B*/
    UINT8 RuuTtiSwitch;									  /*Ruu_TTI_SWTICH*/
    UINT8 WhitenSwitchPDCCH;                              /*PDCCH�����׻�Ӳ����*/
    UINT8 IntraBalanceNum;								  /*RB �ڲ�ƽ�����*/
    UINT8 IntraBalanceThr;								  /*RB �ڲ�ƽ������*/
    UINT8 InterBalanceNum;								  /*RB �䲻ƽ�����*/
    UINT8 InterBalanceThr;								  /*RB �䲻ƽ������*/
    UINT8 RuuMode;										  /*RUU MODE*/
    UINT8 Rsv[3];

} NV_PDC_IRC_STRU;



#define NV_PDC_IRC_STRU_DEFAULT						{\
														6,				/*WhitenRuuSize1*/\
														2,				/*WhitenRuuSize2*/\
														1,				/*BalanceEst*/\
														0,				/*WhitenThreMode*/\
														20,				/*Threshold_A*/\
														200,			/*Threshold_B*/\
														1,				/*RuuTtiSwitch*/\
														1,				/*WhitenSwitchPDCCH*/\
														2,				/*IntraBalanceNum*/\
														4,				/*IntraBalanceThr*/\
														3,				/*InterBalanceNum*/\
														4,				/*InterBalanceThr*/\
														1,				/*RuuMode*/\
														{0,0,0}			/*Rsv*/\
													}

/*PDS  IRC*/

typedef struct
{
     UINT8 WhitenRuuSize1;                                /*�����׻�������1*/
     UINT8 WhitenRuuSize2;                                /*�����׻�������2*/
     UINT8 PdsSInd;                                       /*��һ��slot �������� ʹ��������0��1��0/1/2/3��1/3�������㷨ͬ����BBP��ͬ*/
     UINT8 Flag0th;										  /*����01�Ƿ�μ��ۼ�0/1/2*/
     UINT8 WhitenThreMode;                                /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
     UINT8 Threshold_A;                                   /*�����׻�����Ӧ��������Threshold_A */
     UINT8 Threshold_B;                                   /*�����׻�����Ӧ��������Threshold_B */
     UINT8 BfSDisIrcFlag;								  /*BF S SUBFRAME DISTRIBUTE IRC FLAG: 0, 1, 2  add che_irc_sd_set0 */
     UINT8 WhitenSwitchPDSCH;                             /*PDSCH�����׻�Ӳ����*/
     UINT8 BfWhitenRuuSize1;                              /*�����׻�������1*/
     UINT8 BfWhitenRuuSize2;                              /*�����׻�������2*/
     UINT8 AgcAdjDecideNosieProcFlag;					  /*�Ƿ�ʹ��agcadj flag��־*/
     UINT8 BfWhitenThreMode;                              /*0: ʹ��DSP �����������ֵ  1�� ʹ��NV�����õ�����ֵ*/
     UINT8 BfThreshold_A;                                 /*�����׻�����Ӧ��������Threshold_A */
     UINT8 BfThreshold_B;                                 /*�����׻�����Ӧ��������Threshold_B */
     UINT8 PdsRuuMode;									  /*RUU MODE*/
     UINT8 BfWhitenSwitchPDSCH;                           /*PDSCH�����׻�Ӳ����*/
     UINT8 JudgeSym0BalanceFlag;						  /* �жϷ���0�Ƿ�ƽ��ʹ��*/
     UINT8 JudgeSym0BalanceThr;						      /* �жϷ���0�Ƿ�ƽ������*/
     UINT8 ucRsv;
} NV_PDS_IRC_STRU;

#define NV_PDS_IRC_STRU_DEFAULT								{\
																6,		/*WhitenRuuSize1*/\
																3,		/*WhitenRuuSize2*/\
																3,		/*PdsSInd*/\
																2,		/*Flag0th*/\
																0,		/*WhitenThreMode*/\
																40,		/*Threshold_A*/\
																80,		/*Threshold_B*/\
																0,      /*TBD BfSDisIrcFlag*/\
																1,		/*WhitenSwitchPDSCH*/\
																6,      /*TBD BfWhitenRuuSize1*/\
																3,      /*TBD BfWhitenRuuSize2*/\
															 	1,		/*AgcAdjDecideNosieProcFlag*/\
															 	0,		/*BfWhitenThreMode*/\
															 	64,		/*BfThreshold_A*/\
															 	100,	/*BfThreshold_B*/\
															 	1,		/*PdsRuuMode*/\
															 	1,		/*BfWhitenSwitchPDSCH*/\
															 	1,		/*JudgeSym0BalanceFlag*/\
															 	16,		/*JudgeSym0BalanceThr*/\
															 	0,		/*ucRsv*/\
															 }

typedef struct
{
    NV_PB_IRC_STRU     stPbIrc;
    NV_PDC_IRC_STRU    stPdcIrc;
    NV_PDS_IRC_STRU    stPdsIrc;

} NV_IRC_STRU;

typedef struct
{
	NV_IRC_STRU stIrc[2];
}NV_IRC_PUB_STRU;
typedef struct
{
    UINT16                      ausRegionAVal[NUM_2];
    UINT16                      ausRegionBVal[NUM_2];
    UINT16                      ausRegionCVal[NUM_2];
}UL_AMPR_EXTEND_STRU;

typedef struct
{
    UINT16                      usRegionAVal;
    UINT16                      usRegionBVal;
    UINT16                      usRegionCVal;
    UINT16                      usReserved;
}UL_AMPR_STRU;

typedef struct
{
    UL_AMPR_STRU                astAmprValNS12[LPHY_MAX_BANDWIDTH_NUM];
    UINT16                      ausAmprNS12_1D4[NUM_3];
    UINT16                      usRev;
    UINT16                      ausAmprValNS13[NUM_2];
    UINT16                      ausAmprValNS14[LPHY_NS14_BANDWIDTH_NUM][NUM_2];
    UL_AMPR_EXTEND_STRU         astAmprValNS15[LPHY_MAX_BANDWIDTH_NUM];
}UL_AMPR_BAND26_STRU;
typedef struct
{
    UINT16                      ausAmprValNS18[NUM_2];
}UL_AMPR_BAND28_STRU;



typedef struct
{
   UINT8   RsIntpCoef[INTERP_COEF_ROW][INTERP_COEF_COLUMN];         /*����ϵ������*/
   UINT8   Rsv0;
   UINT16  PbchTimeIntCoef[PB_TIME_DOMAIN_INTP_NUM];                /*PBʱ���ֵϵ������*/
   UINT16  PduTimeIntCoef[PDU_TIME_DOMAIN_INTP_NUM];                /*PDUʱ���ֵϵ������*/
   UINT8   AlphaCoef[IIR_ALPHA_NUMBER];                             /*Alpha�˲�ϵ������*/
   UINT16  Rsv1;
   UINT32  ChanPhaseErrRx0[CHE_CPE_ROW][CHE_CPE_COLOUM];
   UINT32  ChanPhaseErrRx1[CHE_CPE_ROW][CHE_CPE_COLOUM];
} NV_CHE_INTP_STRU;

/*��ʱNV����*/
typedef struct{
    VOS_UINT16  T_ParTD[6];         /*default: [48 64 64  96 96 96]ʱ�����ʱ�ŵ�PDP����ȱ������ޣ���Ӧ1.4M��20M����                       */
    VOS_UINT16  T_ParFD[6];         /*default: [64 64 64  96 96 96]Ƶ�����ʱ�ŵ�PDP����ȱ������ޣ���Ӧ1.4M��20M����                       */
    VOS_UINT16  TrefShort[6];       /*default: [32 32 11 11 8 8]   DRXԤͬ�� or IDLE��Ѱ�������Ķ�ʱ��ǰ������0.5TsΪ��λ,��Ӧ1.4M��20M���� */
    VOS_UINT16  TrefCommon[6];      /*default: [16 16 11 11 8 8]   ���������Ķ�ʱ��ǰ������0.5TsΪ��λ,��Ӧ1.4M��20M����                    */
    VOS_UINT16  FPWLenShort[6];     /*default: [3 6 12 24 48]      DRXԤͬ�� or IDLE��Ѱ���������׾����������ȣ���Ӧ1.4M��20M����           */
    VOS_UINT16  FPWLenCommon[6];    /*default: [10 20 40 80 160]   �����������׾����������ȣ���Ӧ1.4M��20M����                              */
    VOS_UINT16  Tb;                 /*default: 384                 ��W1b��W2b����������                                                     */
    VOS_UINT16  EndValue;           /*default: 8                   �˲�ϵ����������ֵ                                                      */
    VOS_UINT16  W;                  /*default: 128                 �ྶ��������������                                                       */
    VOS_UINT16  FPWindow;           /*default: 20                  �ྶ���������ڷ�ֵ��ǰ�����׾��ķ�Χ                                     */
    VOS_UINT16  HoldThrsh;          /*default: 32                  �ྶ������������ȱ�������                                               */
    VOS_UINT16  Ncs;                /*default: 5                   ����̬DRX�����жϽ����ʱ��Ч�Ե�С����������                            */
    VOS_UINT16  ResetThrs;          /*default: 288                 �ྶ�������жϽ����ʱ��Ч�Ե�����(0.5Ts)                                */
    VOS_UINT16  Reserved;           /*default: 0                                                                                            */
}NV_TIMING_PARA_STRU;

typedef struct
{
    VOS_UINT8   N_6RB[4];           /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_15RB[4];          /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_Other;            /*default: {10}*/
    VOS_UINT8   Reserverd[3];       /*default: {0}*/
}NV_EMU_FAKECELL_PARA_STRU;
typedef struct
{
    UINT8       ucIdleInterFreqThrd;            /*default: 5 */
    UINT8       ucConnInterFreqThrd;            /*default: 5 */
    INT16       usReserved;
}NV_EMU_TASK_PERIOD_PARA_STRU;
typedef struct
{
    NV_EMU_TASK_PERIOD_PARA_STRU  stEmuTaskPeriodPara;
}NV_EMU_PARA_STRU;
typedef struct{
    VOS_UINT8   RuuAlpha;                       /*default:{{0},             Ruu���˲�����                                                  */
    VOS_UINT8   WhitenRBStep;                   /*default:{0},              �׻����ص�Ƶ���Ӵ���������                                      */
    VOS_UINT8   CSIWhitenFlag;                  /*default:{0},              CQI�����Ƿ�׻���Ӳ����                                          */
    VOS_UINT8   CSIWhitenSwitchMode;            /*default:{0},              CQI�����Ƿ���ȫ����ĸ��ž��������׻�����                        */
    VOS_UINT8   CSIWhitenKg[6];                 /*default:{1,1,1,1,1,1},    �׻����ص�Ƶ��RB��������                                         */
    VOS_INT8    ESINRRepairFactor1[24];         /*default:{1,1,1,0,0,1,-1,-1,-1,-1,-1,-1,1,1,1,0,0,1,-1,-1,-1,-1,-1,-1},  ��Ч����Ȳ���ֵ1            */
    VOS_INT8    ESINRRepairFactor2[24];         /*default:{-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0},  ��Ч����Ȳ���ֵ2            */
    VOS_INT8    ESINRRepairFactor3[24];         /*default:{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},  ��Ч����Ȳ���ֵ3            */
    VOS_INT8    ESINRRepairFactor4[24];         /*default:{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  ��Ч����Ȳ���ֵ4            */
    VOS_INT8    RuuZeroFlag;                    /*default: 1*/
    VOS_INT8    Reserved;                       /*default: 0*/
    VOS_UINT16  gausRIFactorTrms[2][3];    // [256,256,256,256,256,256]          �ֱ��ӦЧ�ʺ� RBIR�� 0,1,2
    VOS_UINT16  gausRIFactorCorr[2][3];    // [170,180,256,170,180,256]          �ֱ��ӦЧ�ʺ� RBIR�� 0,1,2
    VOS_UINT16  gausRIFactorTm[2][4];      // [256,300,256,256,256,300,256,256]  �ֱ��ӦЧ�ʺ� RBIR�� TM3,TM4,TM8,TM9
    VOS_UINT16  gausRIFactorDuplex[2][2];  // [256,256,256,256]                  �ֱ��ӦЧ�ʺ� RBIR�� FDD,TDD
    VOS_UINT16  gausRIFactorWhiten[2][2];  // [256,256,256,256]                  �ֱ��ӦЧ�ʺ� RBIR�� �ǰ׻� ,�׻�
    VOS_UINT16  gausRIFactorVelocity[2];   // [256,281]                          �ֱ��Ӧ���ٺ͵��ٵ�ȡֵ
}NV_CQI_PARA_STRU;

typedef struct _LTE_ASU_NV_SUB_STRU_{
    UINT32                     ulPrachFailNumThr;  //�������㷨�о�������ֵ����������ʧ�ܴﵽ���޴�����������
    UINT16                     usNGCThr;           //����̬�����о�ΪGOOD�����޴�������������
    UINT16                     usNPCThr;
    UINT16                     usNGIThr;
    UINT16                     usNPIThr;

    UINT16                     usNumHappyIdleThr;
    UINT16                     usNumUnhappyIdleThr;
    INT32                      lGoodRsrpThr;       //�ж�ΪGOOD��RSRP����ֵ ��������
    INT32                      lPoorRsrpThr;
    INT16                      sGoodSinrThr;
    INT16                      sPoorSinrThr;
}LTE_ASU_NV_SUB_STRU;

typedef struct{
	UINT32        NV_ID_LTE_AS_CTRL;		//Bit0����ʾ���߼�⹦���Ƿ�����Ĭ��ֵΪ1��
											//Bit1����ʾ�����л������Ƿ�����Ĭ��ֵΪ1��
											//Bit2��ָʾDPDTĬ��״̬��
											//Bit8~12��ָʾ����DPDT��GPIO��š�
											//����BitsΪԤ����
	UINT8         NV_ID_LTE_AS_ALG_PARA[8];	//Byte0��alpha �˲��������ӣ���������16������Ĭ��ֵΪ2��
											//Byte1��N1 Ĭ��ֵ 1
											//Byte2��N2 Ĭ��ֵ 5
											//Byte3��N3 Ĭ��ֵ 7
											//Byte4��SW_THR1 Ĭ��ֵ 9dB
											//Byte5��SW_THR2 Ĭ��ֵ 6dB
											//Byte6��SW_THR3 Ĭ��ֵ 3dB
											//Byte7��SW_HYST Ĭ��ֵ 2s
    //+TAS250 20140928 begin
    LTE_ASU_NV_SUB_STRU stAsuNvSubPara;

	UINT32         NV_ID_LTE_TAS250_ENA;// 0
	//+tas250 end
}NV_ASU_PARA_STRU;

/*****************************************************************************
 ���ݽṹ˵��  : LTE TASɨƵ�׶�Rssi����ֵ���Ͷ���
*****************************************************************************/
typedef struct
{
	INT16     ssLteTasBsRssiThdFdd;              /*FDD�µ�TASɨƵRssi����*/
	INT16     ssLteTasBsRssiThdTdd;			     /*TDD�µ�TASɨƵRssi����*/
}NV_LTE_TAS_BS_RSSI_THD_STRU;

typedef struct{
    VOS_UINT8   RuuAlpha;                        /*default:{{0},      Ruu���˲�����                                                  */
    VOS_INT8    RLMWhitenSwitch;                 /*default:{1},       RLM�����Ƿ�׻���Ӳ����                                         */
    VOS_INT8    RLMSwitchMode;                   /*default:{0},       �׻����ص������Ƿ���ȫ����                                      */
    VOS_INT8    RLMWhitenN[2];                   /*default:{10,1},    �׻����ص�����,[0]��Ӧ����1��[1]��Ӧ����2                       */
    VOS_INT8    RLM_WhitenThd_FDD[24];           /*default:{0,...,0}, FDD��RLM Whiten�о���������ֵ                                  */
    VOS_INT8    RLM_WhitenThd_TDD[24];           /*default:{0,...,0}, TDD��RLM Whiten�о���������ֵ   "                              */
    VOS_INT8    RuuZeroFlag;                     /*default: 1*/
    INT8        cN310OutComp[2];
    INT8        cN310InComp[2];
}NV_RLM_PARA_STRU;

typedef struct{
    VOS_INT8    Corr_Tlayer1IRC;                 /*default: 19,       1�������߻�1��������ʱ���ж������׻��������Ե�����ֵ         */
    VOS_INT8    Corr_Tlayer2IRC;                 /*default: 4},       2��2�ջ�4��2��ʱ���ж������׻��������Ե�����ֵ              */
    VOS_INT8    Reserved[2];                     /*Reseved: TBD*/
 }NV_ANTCORR_PARA_STRU;

/*VITERBI*/
typedef struct
{
    VOS_UINT16 DciTotalPwrThresh[2][4][4];      /*ȫ��CCE�������ֵ�о�����, [�����׻�����][RSSP����][DAGC����������]*/
    VOS_UINT16 DciSinglePwrThresh[2][4][4];     /*��CCE�������ֵ�о�����, [�����׻�����][RSSP����][DAGC����������]*/
    VOS_UINT16 DciBerThresh[2];                 /*BER�о�����, [�����׻�����]*/
    VOS_UINT32 CcDecTraceSelOrder;              /*�ӱ�ѡ���Ҵ�·��ѡ��ͻ���ʱ��ʼ״̬ѡ������ȼ�˳�򿪹�*/
}NV_VITERBI_PARA_STRU;

/*TURBO*/
typedef struct
{
    VOS_UINT32 TurboDecIterFactor;              /*���ε����ɿ�����, ȡֵ��Χ: 35-48, Ĭ��Ϊ45*/
}NV_TURBO_PARA_STRU;

typedef struct
{
    UINT16    ausRsThrd1Fdd[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddNCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
#if 0
    UINT16    ausOLHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausOLLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
#endif
    UINT16    ausILHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausILLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
}AFC_NV_RS_CONFIG_STRU;
typedef struct
{
    UINT16 usVctcxoThdHigh;             /* ��̬TCXO������ */
    UINT16 usVctcxoDynamic;             /* ��̬TCXOֵ, UE�ϵ�ʱ��HPA��ȡNV������DSP,
                                               UE�ϵ翪����������̬���DSP��ȡ��Чֵд��NV */
    UINT16 usVctcxoFlag;                /* ��̬TCXOȡֵ�Ƿ���Ч��ʶ, DSP�ɲ���,
                                               0: ��Ч��������Ч����ЧʱusDynamicTcxoֵ������ */
    UINT16 usVctcxoFuncSwitch;          /* ��̬TCXO�����Ƿ�ʹ�ÿ���, DSP�ɲ���,
                                               �޸ĺ�, ��Ҫ�µ����ϵ�Ż���Ч
                                               0: �ر�, �ر�ʱusVctcxoDynamicȡֵusVctcxoInit
                                               1: �� */
}LTE_TCXO_DYNAMIC_CONFIG_STRU;

typedef struct
{
    UINT16    usEnableFlag;
    UINT16    usHSTMode;
    AFC_NV_RS_CONFIG_STRU    stAfcNvCRsConfig;
/*#ifdef CHIP_BB_6920CS   */
    AFC_NV_RS_CONFIG_STRU    stAfcNvMRsConfig;
/* #endif */
    UINT16    usFreqAdjustLimit; /*usLoopAdjustLimit; */
    UINT16    usFOHSTCompensation;
    /* UINT16    usInitPDM; */
    /* UINT16    usDynamicPDM;*/
    UINT16    usVoltageFactor;
    UINT16    usMFreqAdjustLimit;

    UINT16    usPdmHighThreshold;
    UINT16    usFreqOffsetThreLow;
    UINT16    usFreqOffsetThreHigh;
    UINT16    usPdmCcThreshold;
    UINT16    ausPdmParThreshold[LPHY_MAX_BANDWIDTH_NUM];
	UINT16                                  usRsv;
    INT16 sTempDiffNum;                 //�²�����޴���
    INT16 sNormalTempLowLimt;           //���������������
    INT16 sNormalTempHighLimt;          //���������������
    INT16 sNormalCpThresh;              //����CP��ֵ
    INT16 sExtendCpThresh;              //��չCP��ֵ
    INT16 sCsDemodTimDiffNum;           //С������������ʱƫ�����
    INT16 sNormalTempDiff[4];           //���������²����ޣ���DRX���ڴӸߵ�������
    INT16 sNonNormalTempDiff[4];        //�ǳ��������²����ޣ���DRX���ڴӸߵ�������
}NV_AFC_PARA_STRU;

typedef struct {
    UINT8       ucVersion[16];                  /*�����汾������*/
    UINT32      ulVersionId;                    /*�����汾��ʶ*/
}NV_VERSION_STRU;

typedef struct
{
    INT16     sPreTargetPowerFdd;
    INT16     sPreTargetPowerTdd;
    INT16     sPostTargetPower;
    INT16     sLeastSNR;

/*    INT16     sPwrConst; */
/*	UINT16    usReserved; */

    UINT8     ucDAGCAdjBitForTM1To6;
    UINT8     ucDAGCAdjBitForTM7To8;
    INT8      cMinAntPwr;
    INT8      cMaxAntPwr;

    UINT8     ucACSFilterThreshold[AGC_INTF_DET_THR_BW_NUM];//ca changed
    INT8      cACSPowerThreshold0[AGC_INTF_DET_THR_BW_NUM];
    INT8      cACSPowerThreshold1[AGC_INTF_DET_THR_BW_NUM];
    UINT8     ucNBFilterThreshold[AGC_INTF_DET_THR_BW_NUM];
    INT8      cNBPowerThreshold0[AGC_INTF_DET_THR_BW_NUM];
    INT8      cNBPowerThreshold1[AGC_INTF_DET_THR_BW_NUM];
}NV_AGC_PARA_STRU;
/*UL NV */
typedef enum
{
    APC_GAIN_LEVEL_0 = 0,
    APC_GAIN_LEVEL_1 ,
    APC_GAIN_LEVEL_2 ,
    APC_GAIN_LEVEL_3,
    APC_GAIN_LEVEL_INVALID
}UL_APC_GAIN_LEVEL_ENUM;


typedef enum
{
    APC_GAIN_NONCROSS = 0,
    APC_GAIN_CROSS
}UL_APC_GAIN_CROSS_FLAG_ENUM;

typedef UINT16 UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16;
typedef UINT16 UL_APC_GAIN_LEVEL_ENUM_UINT16;

typedef struct
{
    INT16 sPwrLow;
    INT16 sPwrHigh;
    UL_APC_GAIN_LEVEL_ENUM_UINT16 enAPcGainLevel;
    UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16 enAgcGainCrossFlag;
}UL_APC_GAIN_CTRL_STRU;

typedef struct
{
    INT16  sPwr;
    UINT16 usVga;
}UL_APC_TABLE_ITEM_STRU;


#define APC_GAIN_AREA_NUM 3
#define APC_TABLE_NUM 2
#define APC_TABLE_LEN 64
/* #define APC_GAIN_LEVEL_NUM 4 */
typedef struct
{
    UINT16 usFreqFixSwitch;
    UINT16 usFreqSwitchStub;
    INT32  lIniPhase;
    INT32  lDeltaPhase;
}UL_FREQ_FIX_CTRl_STRU;

typedef struct
{
    UINT32 ulUlCfrSwitch;
    INT16  sSrsCfrThred;
    INT16  sPuschCfrThred;
}UL_CFR_CTRl_STRU;

typedef struct
{
    UL_CFR_CTRl_STRU stCfrCtrl;
    UL_APC_GAIN_CTRL_STRU astApcCtrl[APC_GAIN_AREA_NUM];
    //UL_APC_TABLE_ITEM_STRU astApcTable[APC_TABLE_NUM][APC_TABLE_LEN];
}NV_UL_PARA_STRU;

/* BEGIN: Added by shijiahong, 2011/12/23   PN:DTS201112302952*/

typedef struct
{
    UINT32 ulRegAddr;
    UINT32 ulValue;
}BBP_CFG_ITEM_STRU;

typedef struct
{
    UINT16 usRficRegAddr;
    UINT16 usRficRegValue;
}NV_LPHY_RFIC_CFG_STRU;


typedef struct
{
    UINT8 enSingleReceiverChnSel;
    INT8  cRsv[7];
}NV_PHY_FUNC_VERIFY_STUB_STRU;
/* END:   Added by luliwu,  2012/2/3  PN: DTS_TISTISTIS */
/*****************************************************************************
 �ṹ��    : DRX_CTRL_FLAG_BIT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DRX���ƿ���
*****************************************************************************/
typedef struct
{
    UINT32  bitIdleDrxFlag              :1;
    UINT32  bitDspPwCtrl                :1;
    UINT32  bitLowDspPwCtrl             :1;
    UINT32  bitBbpPwCtrl                :1;
    UINT32  bitRfPwCtrl                 :1;
    UINT32  bitRfDvtyPwCtrl             :1;
    UINT32  bitPaPwCtrl                 :1;
    UINT32  bitLteSlavePwCtrl           :1;
    UINT32  bitGUTSlavePwCtrl           :1;
    UINT32  bitDspDfsCtrl               :1;
    UINT32  bitFlag10                   :1;/*�Ѿ�ʹ��С�������Ż�����(bitFlag11<<1+bitFlag10),0��ʾ���Ż���n��ʾ�Ż�n+1��*/
    UINT32  bitFlag11                   :1;/*�Ѿ�ʹ��*/
    UINT32  bitFlag12                   :1;
    UINT32  bitFlag13                   :1;
    UINT32  bitFlag14                   :1;
    UINT32  bitFlag15                   :1;
    UINT32  bitTimeMeasIdx0             :1;
    UINT32  bitTimeMeasIdx1             :1;
    UINT32  bitTimeMeasIdx2             :1;
    UINT32  bitFlag19                   :1;
    UINT32  bitFlag20                   :1;
    UINT32  bitFlag21                   :1;
    UINT32  bitFlag22                   :1;
    UINT32  bitFlag23                   :1;
    UINT32  bitFlag24                   :1;
    UINT32  bitFlag25                   :1;
    UINT32  bitFlag26                   :1;
    UINT32  bitFlag27                   :1;
    UINT32  bitFlag28                   :1;
    UINT32  bitAllActCdrxFlag           :1;/*ʹ��CDRX��׮һֱ����*/
    UINT32  bitDisCdrxFlag              :1;/*ʹ��CDRX��׮ȥʹ��CDRX����*/
    UINT32  bitGcfCdrxStubFlag          :1;/*�Ѿ�����������ʹ�ã���Ҫ��ʹ��*/
}DRX_CTRL_FLAG_BIT_STRU;

/*****************************************************************************
 �ṹ����  : NV_LPHY_DSP_CONFIG
 Э����  :
 ASN.1���� :
 ö��˵��  : LPHY DSP������ʼ��������������NV�ṹ�嶨��
*****************************************************************************/
typedef struct{
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16  enAntennaPortsCount;                /*LPHY UE���������������������źŵ�������Ŀ*/
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteMode;                          /*LPHY ��ʼ��ʱĬ�ϵĸ���ģʽ*/
    UINT32                              aulNvLteAntennaSwitchBand[MAX_RF_BAND_NUM];       /*LTE��Band��Ӧ�����߿���ֵ, ����0:9��FDD���߿��ػ�TDD Rx���߿���ֵ;����16:25��TDD Tx���߿���ֵ*/
    UINT16                              usNvLteOccaPreTime;                 /*lte������ϵͳoccasionʱԤ�����ж���ǰ������λus*/
    UINT8                               ucPowerOnLoadFlag;                  /*LPHY DSP�ϵ��һ�μ��ر�ʶ: "1"�ϵ��һ�μ���;"0"���ϵ��һ�μ���*/
    UINT8                               ucNvLteInitialCfgRfabb;             /*LPHY ��ʼ��ʱ�Ƿ�����RF��ABB��ʶ��"1"����;"0"������*/
    UINT8                               ucHwVersion;                        /*BalongV7R1Ӳ���汾��*/
    UINT8                               ucNvLteBandNumber;                  /*LTE Band����,<8*/
    UINT8                               aucNvLteBandInd[MAX_RF_BAND_NUM];                  /*LTE Band�����飬ÿ��ֵ��ӦLTE Band��*/
    UINT8                               aucNvLtePaEnInd[MAX_RF_BAND_NUM];                  /*LTE��Band��Ӧ��PA En����λ,Bandָʾ��aucNvLteBandIndһ��*/
    UINT8                               ucNvLteDefaultBandIdx;              /*��ʼ��ʱȱʡBAND���*/
    UINT8                               ucUeCap;                            /*1��ʾue����1��2��ʶue����2��5��ʾue����5*/
    UINT8                               ucAntSelect;                    /*0:false,1:true */
    UINT8                               ucSupport64Qam;                    /*0:64qam��֧�֣�1:64qcam֧��*/
    #if 0
    /*UINT8                               aucDspCfgRsv[2];  */                  /*LPHY ��ʼ������Ԥ������*/
    UINT8                               ucIdleDrxControlFlag;/*IDLE DRX���Ʊ�־ */
    UINT8                               aucDspCfgRsv;                    /*LPHY ��ʼ������Ԥ������*/

    /*#else*/
    #endif
    UINT16                              usLteTxTrxSwitchCfg;                /*LTE��Tx_switch��TRx_switch��չ��־����ʾTx_switch�Ƿ�Ҫ��չΪ2��*/
    UINT16                              usLteAbbIfFormat;                   /*LTE ABB�ӿ�����*/
    UINT8                               ucLteC0C1Sel;                       /*˫��ʱlte����ͨ��c0����c1��*/
    UINT8                               ucLteSsiReadChSel;                  /*lte SSI�ض���ͨ��ѡ��*/
    UINT8                               ucLteRficAd9361Sel;                 /*lte �Ƿ�ѡ��AD9361*/
    UINT8                               ucLteAd9361TcvrOnFlag;              /*LTEʹ��AD9361֧�ֶ�ģ����ʱLTE��TCVR_ON�ܽ���ͨ��0�����״̬*/
    UINT8                               ucTxiqFeedbackPath;                /*Hi6361s ͨ·A/Bѡ��*/
    UINT8                               ucLteWakeSwitchTime;                /*Wake ���ѵ�ʱ���л���ʱ��*/
    DRX_CTRL_FLAG_BIT_STRU              stNvDrxControlBitFlag;              /*IDLE DRX���Ʊ�־ */
}NV_LPHY_DSP_CONFIG;



/*****************************************************************************
 �ṹ����  : NV_GULPHY_COMMON_PARA_CONFIG
 Э����  :
 ASN.1���� :
 ö��˵��  : GUL��ģ������������NV�ṹ�嶨��
*****************************************************************************/
typedef struct{
    UINT8                               ucNvSingleDualModeInd;              /*��˫��ָʾ��0��������1��˫��*/
    UINT8                               ucNvSingleDualRficInd;              /*��˫RFIC��0��˫RFIC��1����RFIC*/
    UINT8                               ucNvCtuTimingDelayCnt;              /*CTU��⵽timing_get_ind��̶��ӳ�nv_ctu_timing_delay_cnt��CTUʱ�����ں�����timing_valid�źš�*/
    UINT8                               ucNvPaMuxCtrl;                      /*GUL PA���ÿ��ƣ�3bit*/
}NV_GULPHY_COMMON_PARA_CONFIG;

typedef struct
{
              UINT16 usT1;                  /*T1Ĭ��ֵ����(������Ƶ���üĴ�����Ŀ����)*/
              UINT16 usT2;                  /*T2Ĭ��ֵ����(RFIC��Ƶʱ��)*/
              UINT16 usT3FDD;               /*T3_FDDĬ��ֵ����(��Ƶ����Ƶ֮��ı���ʱ��)*/
              UINT16 usT3TDD;               /*T3_TDDĬ��ֵ����(��Ƶ����Ƶ֮��ı���ʱ��)*/
              UINT16 usT4;                  /*T4Ĭ��ֵ����(FIR�˲�����ʱ)*/
              UINT16 usAGCCfgTime;          /*AGC������ǰ��(�߼�������Ƶ�������ǰ��)*/
              UINT16 usFDDADCOpenTime;      /*FDD ABB ADC����ǰ��*/
              UINT16 usTDDADCOpenTime;      /*TDD ABB ADC����ǰ��*/
              UINT16 usDACOpenTime;         /*ABB DAC����ǰ��*/
              UINT16 usT7UL;                /*UL_RFIC_T7(TDD����ģʽ�л�������ǰ��)*/
              UINT16 usT7DL;                /*RFIC_T7(TDD����ģʽ�л�������ǰ��)*/
              /* BEGIN: Added by yushujing, 2013/12/23   PN:t8ul_mod*/
              UINT16 usT8ULFDD[7];          /*UL_FDD_T8_COMPENSATE*/
              UINT16 usT8ULTDD[7];          /*UL_TDD_T8_COMPENSATE*/
              /* END:   Added by yushujing, 2013/12/23   PN:t8ul_mod*/
              UINT16 usT9;                  /*T9(TDD����ģʽ�л�������ǰ��)*/
              UINT32 ulT10VGASPICfgTime;    /*T10����VGA��SPI����ʱ��*/
              UINT16 usT15;                 /*T15*/
              /* BEGIN: Added by yushujing, 2013/12/23   PN:t8ul_mod*/
              UINT16 usTul[7];              /*����ͨ����ʱ*/
              /* END:   Added by yushujing, 2013/12/23   PN:t8ul_mod*/
              UINT16 usPaOpenTime;          /*PA��ʱ�䣬����PA����*/
              UINT16 usPaAttTime;           /*PA ATT��ʱ�䣬����PA����*/
              UINT16 usAntSelTime;          /*ANT��ʱ�䣬����ANT����*/
              UINT16 usReserve;             /*��������*/
}NV_DSP_CONFIG_TIME_STRU;
/*****************************************************************************
 �ṹ����  : NV_LPHY_AGC_BASE_TABLE_STRU
 Э����  :
 ASN.1���� :
 ö��˵��  : LPHY DSP AGC��׼��NV�ṹ�嶨��
*****************************************************************************/
typedef struct{
    UINT32 aulRx1AgcBaseTable[128];
    UINT32 aulRx2AgcBaseTable[128];
}NV_LPHY_AGC_BASE_TABLE_STRU;

typedef struct
{

     INT16 usFreqCmpInd;
     INT16 usTempCmpInd;
}NV_BT_CMP_SWITCH_STRU;

typedef struct
{
    UINT16 usDbbAtt;
	UINT16 usAbbAtt;
}NV_APC_ATT_TABLE_STRU;

typedef struct
{
    INT16 sHigh2MidThre;
	INT16 sMid2HighThre;
	INT16 sMid2LowThre;
	INT16 sLow2MidThre;
}NV_PA_LEVEL_THRE_STRU;

typedef struct
{
    INT16  ssPhyHkadcCh;
    INT16  ssRsv;
}NV_LTE_PA_TEMP_DET_CHANNEL_STRU;

typedef struct
{
    UINT32 ulDbbAttRegVal;
    UINT32 ulAbbAttRegVal;
    UINT32 ulAptPdmRegVal;
    UINT32 ulAptVoltRegVal;
    INT32  sUlPwr;
    UINT16 usBandwith;
    UINT16 usUlFreq;
    UINT16 usRbStart;
    UINT16 usRbNum;
    UINT16 usUlChType;
    UINT16 usRsv;
}UL_PWR_REG_STRU;
typedef struct
{
    UINT16 usOldAptType;    /*1:pdm apt  2:mipi apt*/
    UINT16 usUseETMAptFlg;    /*1:enable  0:disable*/
    UINT16 usOldAptEn;        /*old apt en*/
    UINT16 usETMEtEn;         /*etm ET en*/
    UINT16 usETMAptEn;
    UINT16 usETtoAptThres;
}UL_APT_PARA_STRU;
typedef struct
{
    INT16  sTxpower;
    UINT16 usVoltVal;
}UL_APT_TX_POWER_PDMVAL_STRU;
typedef struct
{
    UINT32 ulNum;
    UL_APT_TX_POWER_PDMVAL_STRU stPower2VoltVal[UL_APT_VBIAS_NUM];
}UL_APT_GAIN_VS_VBIAS_STRU;
typedef struct
{
    UINT16 usPdTotalFlg;         /*PD�����ܿ���*/
    UINT16 usDcOffsetThr;        /*DC offset���ޣ�0.001v����*/
    UINT16 usVgalowerGainThr;    /*VGA GAIN��������,0.001v����*/
    UINT16 usVgaUperGainThr;     /*VGA GAIN��������0.001v����*/
    UINT16 usHkAdcVCoeff;        /*HkAdc��ѹϴϵ����HKADC��ȡֵ���Ը�ֵ����1024Ϊ��ѹֵ(mv)*/
    UINT16 usPdCmpOffSwitch;     /*PD�������أ���Ϊ1��ֻ��ⲻ����*/
    UINT16 usPdValidTime;        /*PD���ʱЧʱ��*/
    UINT16 usPdCycNum;           /*PDѭ��������0��Ӧ1�Σ�1��Ӧ2*/
    UINT16 usPdMaxPwrCmp;        /*PD���Ĳ�������,Delta���ڴ�ֵ����ǰֵ����*/
    UINT16 usPdMinPwrCmp;        /*PD��С�Ĳ���,DeltaС�ڴ�ֵ���ٲ���*/
}NV_LPHY_PD_COMM_PARA;

typedef struct
{
    UINT16 usPdEnableFlg;          /*��ǰBAND�Ƿ�ʹ��PD*/
    INT16  sPwrStartThr;
    INT16  sPwrStopThr;
    UINT16 usPdAttenBx;            /*����Ĺ���˥��ֵ*/
    UINT16 usPdRmsRfEn;            /*�Ƿ�����˥��������*/
    UINT16 usPdRfaSel;             /*1Ϊ9db��0Ϊ5db*/
    UINT16 usPdOrigCalVgaCfg;      /*��ʼУ׼VGA����*/
    UINT16 usPdPowerIndexValidNum; /*Ԥ�����ѹ������Ч����*/
    UINT16 ausPdPowerIndex[PD_PWR_CUR_MAX_NUM];    /*Ԥ�����ѹ����*/
    UINT16 usPdDacCfgValidNum; /*Ԥ����DAC���ñ���Ч����*/
    UINT16 usHkAdcChanl;           /*��ǰBANDʹ�õ�HKADCͨ��*/
    UINT16 ausPdCalDacList[PD_CAL_DAC_CFG_MAX_NUM];    /*У׼����DAC���ñ�*/
    UINT16 usPdVagCfgValidNum;     /*VGA������Ч����*/
    UINT16 usRsv1;
    UINT16 aulPdCalVgaList[PD_CAL_VGA_CFG_MAX_NUM];       /*VGA���ñ�*/
    UINT16 usPdCalFreqValidNum;     /*VGA������Ч����*/
    UINT16 usRsv2;
    UINT16 aulFreqList[PD_CAL_TX_REQ_NUM];
}NV_UL_PD_TX_PARA;

typedef struct
{
    UINT16 usDcOffset;             /*У׼�õ���DC����*/
    UINT16 usVgaCfg;               /*VGA����*/
}NV_TX_PD_AUTO_CAL_PARA;

/**************************ET��أ������㷨���߼�Ҫ����Ҫ�Ĵ�������Ϊ������********/
typedef struct
{
    UINT16                          usEtTotalSwitch;        /*ET�ܿ���*/
    UINT16                          usHKADCRatio;           /*Vout����HKADC�ķ�ѹ��*/
    UINT16                          usCurEtmVendor;         /*��ǰETM Vendor 0:TI,1:R2,2:Q,*/
    UINT16                          usAptEtActModeTime;     /*APT_ET_MODE_TIME,T4*/
} NV_TX_ET_COMM_PARA_STRU;

typedef struct
{
    UINT32         ulBypassCfg;       /*ETģ��Bypass����*/
    UINT32         ulDataDely;        /*����ͨ����ʱ*/
    UINT16         usPowerOffset;     /*����ƫ��*/
    UINT16         usRsr;              /*����*/
}UL_TX_ET_BBP_MOD_CFG_STRU;

typedef struct
{
    UINT32         ulEvDely;    /*����ͨ����ʱ�ֵ�*/
} NV_TX_ET_EVDELY;

typedef struct
{
    UINT32         aulFineDlyPara[UL_ET_FINEDLY_PARA_NUM];    /*�����ӳټĴ���ֵ*/
    UINT16         usInitFineDly;        /*�����ӳٲ�ֵ����*/
    UINT16         usRsv;
}NV_TX_ET_FINEDLY_PARA;

typedef struct
{
    INT16  sTxpower;            /*���ʵ�*/
    UINT16 usGainComp;          /*����ֵ,��λ1/8db*/
}NV_LTE_ET_GAIN_COMP_PARA;

typedef struct
{
    UINT32         ulNum;     /*�������ʵ���*/
    NV_LTE_ET_GAIN_COMP_PARA   ulEtGainCmp[UL_ET_MAX_GAIN_COMP_NUM];    /*ETģʽ��pa���油��*/
}NV_LTE_ET_GAIN_COMP;

typedef struct
{
    UINT32                            ucValidflg:1;         /*��ǰָ���Ƿ���Ч*/
    UINT32                            ucExWFlg:1;           /*�Ƿ������չд���ͷ�ʽ,1��*/
    UINT32                            ucWatTime:8;          /*������ȴ�ʱ��*/
    UINT32                            ucSlaveid:4;          /*�豸USID*/
    UINT32                            ucMipiAddr:8;         /*��MIPI�豸�е�ƫ�Ƶ�ַ*/
    UINT32                            ucByteCnt:3;          /*�������չָ�ָ��CNT*/
	UINT32                            ucMipiPortSel:2;      /*Mipi channel, new add 2014.11.4*/
	UINT32                            ulRsv:5;
} NV_MIPI_CMD_CTRL_STRU;

typedef struct
{
    NV_MIPI_CMD_CTRL_STRU            stMipiCtrl;

    UINT8                            ucCmdByte0;
    UINT8                            ucCmdByte1;
    UINT8                            ucCmdByte2;
    UINT8                            ucCmdByte3;
}LPHY_MIPIDEV_CMD_STRU;

typedef struct
{
    UINT16                              usPavcc;              /*APT_PA_VCC*/
    UINT16                              usAptVoltOffset;     /*APT���õ�ѹ�Ĵ���ƫ��*/
    UL_TX_ET_BBP_MOD_CFG_STRU           stBbpEtCfg;           /*BBP�Ĵ�������*/
    UINT32                              ulETMipiCmdnum;      /*��ETM��ET�����MIPIָ�����*/
    UINT32                              ulAPTMipiCmdnum;     /*��ETM��APT�����MIPIָ�����*/
    UINT32                              ulBypassMipiCmdnum;  /*��ETM��Bypass�����MIPIָ�����*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmETCmdTriger;     /*����ET��MIPI����*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmAPTCmdTriger;    /*����APT��MIPI����*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmBypassCmdTriger; /*����Bypass��MIPI����*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmETInitCmd[UL_ET_MAX_ET_MIPICMD_NUM];        /*ETģʽ��MIPIָ��*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmAPTInitCmd[UL_ET_MAX_APT_MIPICMD_NUM];      /*APTģʽ��MIPI����*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmBypassInitCmd[UL_ET_MAX_BYPASS_MIPICMD_NUM];/*Bypassģʽ��Bypassָ��*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmAPTVoltCmd;   /*ETM��APTģʽ�����ѹ*/
} NV_TX_ETM_VENDOR_PARA;

typedef struct
{
    VOS_UINT16                   usEtSwitch;          /*Band��ET����*/
    INT16                        sEtThresh;           /*����ET �� ��������*/
    INT16                        sAPTThresh;          /*����APT �Ĺ�������*/
    INT16                        sCurMod;             /*��ǰģʽ:1-ET, 2-APT��3-Bypass*/
    INT16                        usHkAdcChanl;        /*��ǰBANDʹ�õ�HKADCͨ��*/
    UINT16                       usLowChanlFreq;      /*���ڴ�Ƶ��Ϊ��BNAD���ŵ�*/
    UINT16                       usHighChanlFreq;     /*���ڴ�Ƶ��Ϊ��BAND���ŵ�*/
    UINT16                       usRsv;
} NV_TX_ET_BAND_PARA;

typedef struct
{
    UINT32                       aulLutTbl[UL_ET_LUT_TBL_MAX_NUM];
} NV_TX_ET_CH_LUT_TBL_PARA;


typedef struct
{
    UINT16              usETPostOffset;          /*ET_Voffset*/
    UINT16              usETPostGain;             /*ET_Gain*/
}NV_LTE_ET_VOFFSET_GAIN;

#define PA_LEVEL_NUM  3
#define LNA_LEVEL_NUM 4
#define APC_ATT_MAX_NUM 88

typedef struct __NV_DEM_LIST_STRU__
{
    UINT8    ucInAdjBit;
    UINT8    ucInAdjBitBF;
    UINT8    ucPdschSfbcDemAlg;
    UINT8    ucPdschSdmaDemAlg;
    UINT16   usPHICHDemTHIrcOFF;
    UINT16   usPHICHDemTHIrcON;
}NV_DEM_LIST_STRU;

typedef struct
{
    INT16 usPaDiff[4];
}NV_PA_POWER_DIFFERENCE;

typedef struct
{
     UINT16 usAntCompDCI[16];
     UINT16 usAntCompDCQ[16];
}RF_DOCOC_ANT_ITEM_STRU;


typedef struct
{
    UINT16 usValidFlg;
    UINT16 usValidAntNum;
    RF_DOCOC_ANT_ITEM_STRU   astAntCal[MAX_RX_ANT_NUM];
}RF_DCOCS_DCCOMP_ITEM_STRU;

typedef struct
{
    RF_DCOCS_DCCOMP_ITEM_STRU  astDcocCalRst[MAX_RFIC_PATH_NUM];
}RF_DCOC_CAL_STRU;

typedef RF_DCOC_CAL_STRU NV_DCOC_CAL_TABLE_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usRsv;
	UINT16 usMain_I_DivOff[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_Q_DivOff[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_I_DivOn[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_Q_DivOn[MAX_IIP2_CHAN_NUM];
	UINT16 usDiv_I[MAX_IIP2_CHAN_NUM];
	UINT16 usDiv_Q[MAX_IIP2_CHAN_NUM];
}NV_IIP2_CAL_ITEM;

typedef struct
{
	UINT16 usChanNum;
	UINT16 usRsv;
    NV_IIP2_CAL_ITEM    astIp2CalRst[MAX_RFIC_PATH_NUM];
}NV_IIP2_CAL_TABLE;

typedef struct
{
    INT16  sAmplitude;
    INT16  sPhase;
    INT16  sDCI;
    INT16  sDCQ;
}NV_LTE_RF_TXIQ_CAL_STRU;

typedef struct
{
    INT16 sGainStatus[RF_TX_GAIN_NUM];
}NV_TX_APC_GAIN_ITEM_STRU;

typedef struct
{
    NV_TX_APC_GAIN_ITEM_STRU  astGainItem[3];  /*PA LEVEL,3��*/
}NV_TX_APC_GAIN_STRU;

typedef struct
{
    UINT16 usBias[RF_TX_GAIN_NUM];
}NV_TX_RF_BIAS_STRU;

typedef struct
{
    INT16 asBandWithCmp[4]; /*���5M,10M,15M,20M*/
}NV_TX_RF_BANDWITH_CMP;

typedef struct
{
    UINT8   aucBbAttGain[RF_TX_GAIN_NUM];
    UINT16  usRsv1;
    UINT16  usRsv2;
    NV_TX_RF_BANDWITH_CMP stBandWithCmp;
}NV_TX_RF_BB_ATT_STRU;

typedef struct
{
    INT16 sFreqComp[RF_TX_FREQ_NUM];
    //INT16 sEtFreqComp[RF_TX_FREQ_NUM];
}NV_TX_RF_FREQ_COMP_STRU;
typedef struct
{
    INT16 sPaTempComp[3][32];
}NV_TX_PA_TEMP_COMP;
typedef struct
{
    UINT16 usAttenTable[60];
}NV_TX_ATTEN_TABLE;
typedef struct
{
    UINT16 usPowerVoltage[3];
}NV_TX_POWERDET_VOLTAGE;

typedef struct
{
    UINT32 ulSwitchFlg;
    UINT32 ulResv;
}NV_LPHY_SWITCH_STRU;

typedef struct
{
	UINT32 	usRCcode;
	UINT32  usRsv;
}NV_RF_CA_RCCODE_STRU;

typedef struct
{
	INT16 ucLimitLeft;
    INT16 ucLimitRight;
    UINT16 ucInteration;
    UINT16 ucRsv;
}NV_RF_CA_RCCAL_CFG_STRU;

typedef NV_LPHY_SWITCH_STRU NV_LPHY_RF_BOARD_TYPE;

typedef struct
{
    /*band related*/

    UINT8     ucAGCAcsMinGainZ;
    UINT8     ucAGCNbMinGainY;
    UINT8     ucReserved;
    UINT8     ucDefaultGain0;

    UINT8     ucDefaultGain1;
    UINT8     ucDefaultGain2;
    UINT16    usReserved;

    /*RF/AGC�����*/
    UINT32     ulAGCGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCAcsGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCNbGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulRFIdxTable[2][AGC_MAX_GAIN_LEVEL];
    INT16      sRFErrorTable[2][AGC_MAX_GAIN_LEVEL];
}NV_AGC_BAND_GAIN_TABLE_STRU;
typedef struct
{
    UINT16      usFreqNum;
    UINT16      usRes;
    UINT16      usRxCalibrFreqList[RF_RX_FREQ_NUM];            /*RxƵ��У׼��*/
}NV_LTE_RX_CAL_LIST_STRU;
typedef struct
{
    NV_LTE_RX_CAL_LIST_STRU      stRxCalFreqListLab;            /*RxƵ��У׼��*/
    INT16   	asAgcNoBlkAnt1FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asAgcNoBlkAnt2FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asRxTempCmpVal[32];
    INT16     	asIP2CalChanList[MAX_IIP2_CHAN_NUM];
    NV_IIP2_CAL_TABLE stIP2CalResult;
    UINT16      usIp2CalApcCode;
    UINT16      usRsv2;
    NV_AGC_BAND_GAIN_TABLE_STRU           stAGCTable;        /*agc NV�� */
    RF_DCOC_CAL_STRU stDcocTbl;
    INT16   	asAgcCh1NoBlkAnt1FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asAgcCh1NoBlkAnt2FreqComp[8][RF_RX_FREQ_NUM];
}NV_BAND_RXPATH_PARA_STRU;



typedef struct{
    UINT8 ucRxBtLeverMapTable[16];
}NV_RX_BT_LEVEL_MAP_TABLE_STRU;



typedef struct
{
	INT16  sWireLessMaxPwr;                   /*����״̬�����*/
	INT16  sWiredMaxPwr;                      /*����״̬�����*/
	UINT16 usTestModeInd;                     /*��SAR����ģʽָʾ*/
	INT16  sReducedPwr[9];                    /*��SAR���˹���*/
}NV_ANT_SAR_STRU;
/*TAS2.0/2.5 SAR, max Power back NV*/

#define NORMSCEN_PWRBCK_LEVEL               6 /*һ�㳡�������˹��ʵ�λ��*/
#define ESPSCEN_PWRBCK_LEVEL                3 /*���ⳡ�������˹��ʵ�λ��*/
#define MAX_ESPSCEN_BANDS_NUM               8 /*֧�����ⳡ�������band��*/

typedef struct
{
    UINT16 usEspScenBand[MAX_ESPSCEN_BANDS_NUM];/*֧�����ⳡ����band�����б�*/
    UINT32 ulHLFreqThre;/*band�ߵ�Ƶ�о�����*/
}NV_LTE_COM_ANT_SAR_STRU; //��SAR��������

typedef enum
{
    SAR_PWR_BACK = 0,
    SAR_LF_BACK,
    SAR_HF_BACK,
    SAR_DPDTEX_PWR_BACK,
    SAR_DPDTEX_LF_BACK,
    SAR_DPDTEX_HF_BACK,
    SAR_INVALID
}NV_SCENE_SAR_ENUM;
typedef UINT32 NV_SCENE_SAR_ENUM_UINT32;

typedef struct
{
    INT16  sPwrBk                 ;/*DPDTֱ������modem����SAR���˹���*/
    INT16  sLFrqPwrBk             ;/*DPDTֱ����˫modem�Է���Ƶ����SAR���˹���*/
    INT16  sHFrqPwrBk             ;/*DPDTֱ����˫modem�Է���Ƶ����SAR���˹���*/
    INT16  sDpdtExPwrBk           ;/*DPDT���棬��modem����SAR���˹���*/
    INT16  sDpdtExLFrqPwrBk       ;/*DPDT���棬˫modem�Է���Ƶ����SAR���˹���*/
    INT16  sDpdtExHFrqPwrBk       ;/*DPDT���棬˫modem�Է���Ƶ����SAR���˹���*/
}NV_SCENE_SAR_STRU;/*һ�㳡��,��SAR���˹���*/

typedef struct
{
    INT16  sWireLessMaxPwr;         /*����״̬�����*/
    INT16  sWiredMaxPwr;            /*����״̬�����*/
    UINT16 usTestModeInd;           /*��SAR����ģʽָʾ*/
    UINT16 usPwrBckEnFlag;          /*��SARʹ�ܱ�־��1:��SAR, 0:����SAR*/
    NV_SCENE_SAR_STRU      astNSSar[NORMSCEN_PWRBCK_LEVEL]; /*һ�㳡��,��SAR���˹���*/
    NV_SCENE_SAR_STRU      astESSar[ESPSCEN_PWRBCK_LEVEL];  /*���ⳡ��,��SAR���˹���*/
}NV_LTE_DPDT_ANT_SAR_STRU;


#if 1
typedef struct
{
    UINT16 usValidFlag;    /*DBB������Ч���*/
    UINT16 usRbNum;
    UINT16 usRbStart;
    UINT16 usBw;
    UINT16 usPowThreshold; /*���ʴ��ڴ�����ʱ�Ž���DBB���ˣ���λ1/16*/
    UINT16 usDbbValue;     /*DBB ����ֵ�� ��λ1/16*/
    UINT16 usTargetPow;    /*���˺�Ŀ�깦�ʣ���λ1/16*/
    UINT16 usRsv;
}LTE_DBB_REDUCED_STRU;

#define MAX_DBB_REDUCED_NUM (4)

typedef struct
{
    UINT32 usDbbTotalValidFlag;
    LTE_DBB_REDUCED_STRU astDbbRed[MAX_DBB_REDUCED_NUM];
    UINT16 usRsv[2];
}LTE_OTHER_COMP_STRU;
#else
typedef struct
{
    INT16  sDivLossComp;
    UINT16 usRes;
}LTE_TX_DIVERSITY_LOSS_COMP;
#endif
typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidPwrNum;
    INT16  asPdPower[PD_CAL_TX_REQ_NUM][PD_PWR_CUR_MAX_NUM];
}NV_TX_PD_PWR_TABLE_STRU;

typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidVoltNum;
    UINT16 ausPdVolt[PD_CAL_TX_REQ_NUM][PD_PWR_CUR_MAX_NUM];
}NV_TX_PD_VOLT_TABLE_STRU;

typedef struct
{
    UINT16  usValidNum;
    UINT16  usRsv;
    INT16 asPdTempCmp[32];
}NV_TX_PD_TEMPCMP_TABLE_STRU;
#if 0
typedef struct
{
	INT16 sTx1RbAdjVal;                      /*1RB����ʱ����ֵ 1/8dbΪ��λ*/
	INT16 sRsv[15];
}NV_TX_CMP_RSV_STRU;
#endif
typedef struct
{
	UINT16    usStartRbArea;    /*�����������Ҫ��������ʼrb*/
	UINT16    usEndRbArea;      /*���������϶˶��ٸ�RB����Ҫ���� */
	UINT16    usRes;         /* ��RBλ�ò���ֵ */
	INT16     sCmpVal;      /* ��RBλ�ò���ֵ */
}NV_TX_RF_ABB_FILTER_CMP_STRU;
typedef struct
{
    NV_TX_RF_ABB_FILTER_CMP_STRU ast5MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*5M�˲�������ֵ*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast10MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*10M�˲�������ֵ*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast15MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*15M�˲�������ֵ*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast20MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*20M�˲�������ֵ*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast30MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*30M�˲�������ֵ*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast40MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*40M�˲�������ֵ*/
}NV_EQUIP_TX_FILTER_CMP_STRU;
typedef struct
{
    UINT16  ausGainNumsNeedCalEachPaLevel[RF_PA_GAIN_NUM];/*ÿ��pa��λ��ҪУ׼rfgain �ĸ���*/
    UINT16  sDbbValue;
    UINT16  ausLteApcTable[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}NV_LTE_APC_TABLE_STRU;
typedef struct
{
    INT16  asPaDiff[RF_PA_GAIN_NUM];/*pa�е͵�λ�͸ߵ�λ�Ĺ��ʲ��һ��ֵ��0  �� 0 -5 -10*/
    UINT16 usFreqCompCaliGainChoose;/*Ƶ��У׼gainѡ��*/
    INT16  asRfDefaultPower[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}NV_LTE_DEFAULT_POW_TABLE_STRU;
typedef struct
{
    UINT16 usFreqNum;
    UINT16 usRes;
    UINT16 ausTxCalFreqList[RF_TX_FREQ_NUM];           /*TXУ׼Ƶ�㣬�ɵ͵��߷���*/
    INT16  asTxCalCompListWired[RF_TX_FREQ_NUM];       /*TX����Ƶ�ʲ�����ʵ������д Ĭ��ȫ0��1/8db*/
    INT16  asTxCalCompListWireless[RF_TX_FREQ_NUM];    /*TX����Ƶ�ʲ�����ʵ������д Ĭ��ȫ0��1/8db*/
}NV_LTE_TX_CAL_LIST_STRU;
typedef struct
{
    INT16 sMaxPow;
    INT16 sMinPow;
}NV_LTE_TX_APC_GAIN_STATUS_POW;
typedef struct
{
    NV_LTE_TX_APC_GAIN_STATUS_POW astTxPaPower[RF_PA_GAIN_NUM][RF_TX_GAIN_6362_NUM];
    //NV_LTE_TX_APC_GAIN_STATUS_POW astEtTxPaPower[RF_PA_GAIN_NUM][RF_TX_GAIN_6362_NUM];
}NV_LTE_TX_CAL_RESULT_TABLE_STRU;
typedef struct
{
    INT16 sReal;
    INT16 sImg;
} LTE_CT_COMPLEX_STRU;
typedef struct
{
    UINT16 usRfCodeNum;
    UINT16 usRes;
    INT16 asRfCode[RF_HD3_CAL_POWER_POINTNUM];
    INT32 alBr[RF_HD3_CAL_POWER_POINTNUM];          /*У׼ֵʵ��*/
    INT32 alBi[RF_HD3_CAL_POWER_POINTNUM];          /*У׼ֵ�鲿*/
}NV_LTE_HD3_RESULT_PERPOINT_STRU;
typedef struct
{
    UINT16 usValFlg;    /*ָʾ��band�Ƿ���Ҫ���� 0 ����Ҫ 1 ��Ҫ*/
    UINT16 usRes;
    NV_LTE_HD3_RESULT_PERPOINT_STRU stHD3CalRst[RF_HD3_CAL_NUM];
} NV_LTE_HD3_CAL_RSULT_STRU;
typedef struct
{
    UINT16 usFreq;                          /*Ƶ��*/
	UINT16 usBW;        /*�������չ���ö�ٺ��嶨��*/
	UINT16 usRBPos;                         /*rbλ�� 0 high ��Ƶ��  1 low ��Ƶ��*/
	INT16  sPower;                          /*У׼ʱ�ķ��书�� 1db��λ*/
}NV_LTE_HD3_PERPOINT_PARA_STRU;


typedef struct
{
    UINT16 usValFlg;               /*ָʾ��band�Ƿ���ҪУ׼ 0 ����Ҫ 1 ��Ҫ*/
    UINT16 usCalPointNum;          /*HD3ÿ��band֧�ֵ����У׼����*/
    NV_LTE_HD3_PERPOINT_PARA_STRU astCalPara[RF_HD3_CAL_NUM];
} NV_LTE_HD3_CAL_PARA_STRU;
/**************************ET DPDУ׼NV START**********************/
/* ETʱ��У׼ʱʹ�ò��� */
typedef struct
{
    UINT16 usIntDelay;                   /* ʵ���Ҳⶨ������ʱ��ֵ */

    UINT16 usApcRealNum;
    UINT16 ausApcCode[ET_DPD_DELAY_MAX_NUM];
    INT16  asFracDelayCompValue[ET_DPD_BANDWIDTH_NUM][RF_TX_FREQ_NUM];
}NV_LTE_ET_DELAY_BAND_CAL_STRU;

/* ET LUT��У׼ʱʹ�õĲ��� */
typedef struct
{
    UINT16 usPout;                        /* LUTУ׼ʱ�ķ��书�� */
    INT16  sPinMin;                       /* PA���빦����С���� */
    UINT16 usPoutMin;                     /* PA���������С���� */

    UINT16 usHoldNumA;                    /* ����ƽ��ʹ�õķ��ȱ���Ԫ�� */
    UINT16 usSmoothLen;                   /* ƽ�������� */

    UINT16 usVccMin;                      /* LUT��VCC��С���� */
    UINT16 usVccMax;                      /* LUT��VCC������� */
    UINT16 usEtmGain;                     /* ETM���� */
    UINT16 usEtmOffset;                   /* ETMƫִ */

    UINT16 usVccTarget;                  /* Ŀ������(ʵ����ȷ��)VccTarger */
    UINT16 usNdb;                         /* NDBѹ����(ʵ����ȷ��) */

    UINT16 usLutSmoothLen;
    UINT16 usLutSmoothDB;

    UINT16 usVccRealNum;
    UINT16 ausVccSweep[ET_DPD_VCC_MAX_NUM];        /* ɨƵVCC 416*/
    UINT16 ausVccMipiValue[ET_DPD_VCC_MAX_NUM];    /* ɨƵVCC 416*/
}NV_LTE_ET_LUT_BAND_CAL_STRU;

/* ET LUT�� 8192*/
typedef struct
{
    UINT16 ausEtLutBand[ET_DPD_TAB_NUM];
}NV_LTE_ET_LUT_BAND_STRU;

/* ET����ʱ��У׼��� 224*/
typedef struct
{
    UINT16 ausIntDelay[ET_DPD_DELAY_MAX_NUM];
    UINT16 ausFracDelay[ET_DPD_DELAY_MAX_NUM];
}NV_LTE_ET_DELAY_BAND_FAC_STRU;

/* DPD LUT��У׼ʱʹ�ò��� 320 */
typedef struct
{
    UINT16 usAmpMax;                    /* �ֵ��������ֵ */
    UINT16 usGainCoeff;                 /* �����ϵ�� */
    UINT16 usGrIndex;                   /* �ο�����ȡֵ���� */
    UINT16 usGrLen;                     /* ����ο������ƽ������ */

    UINT16 usHoldNumA;                  /* ���ȱ���Ԫ���� */
    UINT16 usHoldNumP;                  /* ��λ����Ԫ���� */
    UINT16 usSmoothLen;                 /* ƽ�������� */
    UINT16 usStopIndex;                 /* ƽ��������ֹ���� */
    UINT16 usMaxIndex;                  /* ���Ƚ�ֹIndex */
    UINT16 usProtectP;                  /* ��λ��λ���� */

    UINT16 usGrShift;
    UINT16 usResv;
}NV_LTE_DPD_LUT_BAND_CAL_STRU;

/* ET DPD Pin���ʲ��� 4096*/
typedef struct
{
    INT16  asDbbPowTempComp[ET_DPD_TEMP_COMP_NUM][RF_TX_FREQ_NUM];   //FC4�²�
    INT16  asFracDelayTempComp[ET_DPD_TEMP_COMP_NUM][RF_TX_FREQ_NUM];//ʱ���²�
    INT16  asEtTxPowTempComp[ET_DPD_TEMP_COMP_NUM][RF_TX_FREQ_NUM];
}NV_LTE_ET_PIN_COMP_BAND_STRU;

/* ET DPD Pout���ʲ���У׼ 3584*/
typedef struct
{
    NV_LTE_TX_APC_GAIN_STATUS_POW astEtTxPaPower[RF_PA_GAIN_NUM][RF_TX_GAIN_6362_NUM];
    INT16 sEtFreqComp[RF_TX_FREQ_NUM];
}NV_LTE_ET_POUT_FREQ_COMP_STRU;

/* ������ */
typedef struct
{
    UINT16  usIData;                /* I·���� */
    UINT16  usQData;                /* Q·���� */
}LTE_DPD_ORTH_NUM_TYPE_STRU;


typedef struct
{
    UINT16 usApcCode;
    UINT16 usRegValue;
}LTE_ET_APT_POW_VALUE_TYPE_STRU;

/* DPD LUT�� 4096*/
typedef struct
{
    LTE_DPD_ORTH_NUM_TYPE_STRU astDpdLutBand[ET_DPD_COMPLEX_GAIN_NUM];
}NV_LTE_DPD_LUT_BAND_STRU;

typedef struct
{
    UINT16 usValidFlg;                    /* ��NV��MIPIָ��Ƿ���Ч */
    UINT16 usCmdNum;                      /* MIPI��Чָ���� */
    LPHY_MIPIDEV_CMD_STRU astMipiPara[ET_DPD_MIPI_MAX_NUM];/* MIPIָ� */
}NV_TX_ET_APT_MULT_PARA;

typedef struct
{
    UINT16 usValidFlg;                    /* ��NV��MIPIָ��Ƿ���Ч */
    UINT16 usCmdNum;                      /* MIPIָ���ָ���� */
    //LPHY_MIPIDEV_CMD_STRU stMipiTriger;   /* MIPI TRIGERָ�� */
    LPHY_MIPIDEV_CMD_STRU astMipiPara[ET_DPD_MIPI_TRIGER_MAX_NUM];/* MIPIָ� */
}NV_TX_ET_APT_TRIGER_PARA;

/****************************************************************/

/* ET/APT BAND�޹� */
typedef struct
{
    /* У׼ʹ�õĲ��� */
    UINT16 usLutType;               /* POUT_VCC/PIN_VCC/AMP_VCC*/
    UINT16 usDelayValue;            /* �̶�һ·ʱ�ӣ�������һ·ʱ��ģʽ�̶�TX */
    UINT16 usDelayTpye;

    /* ��������ʹ�õĲ��� */
    UINT16 usEtmSupportFlag;        /* �Ƿ�ʹ��ETM���� */
    UINT16 usCalModeSelect;
    UINT16 usResv;
}NV_ET_SELECT_WORK_MODE_LAB_STRU;

/* DPD BAND�޹� */
typedef struct
{
    /* ��������ʹ�õĲ��� */
    UINT16 usDpdOpenFlag;        /* DPD���� */
    UINT16 usPefOpenFlag;        /* PEF���� */
}NV_DPD_SELECT_WORK_MODE_LAB_STRU;

/* ET/APT BAND�޹�MIPIָ�� */
typedef struct
{
    NV_TX_ET_APT_MULT_PARA   stEtInitPara;    /* ��ʼ����ETָ�� */
    NV_TX_ET_APT_MULT_PARA   stEtIdlePara;
    NV_TX_ET_APT_MULT_PARA   stEtClosePara;
}NV_ET_APT_MIPI_CMD_LAB_STRU;

/* ET/APT BAND��� */
typedef struct
{
    /* У׼ʹ�õĲ��� */
    NV_LTE_ET_DELAY_BAND_CAL_STRU stEtCalDelayBandPara;  /* ����У׼ʱ����Ҫ�Ĳ��� */
    NV_LTE_ET_LUT_BAND_CAL_STRU   stEtCalLutPara;        /* ����У׼LUT����Ҫ�Ĳ��� */

    INT16 sCenterFreqDbbPow[ET_GAIN_MAX_NUM];            /*����Ƶ�㲻ͬ��λ��FC4����*/
    INT16 sFreqCompDbbPow[RF_TX_FREQ_NUM];               /*��ͬƵ����FC4�Ĳ���ֵ*/
    UINT16 ausDbbPowTempSensor[ET_DPD_TEMP_COMP_NUM];
    UINT16 ausTxPowTempSensor[ET_DPD_TEMP_COMP_NUM];
    UINT16 usTempMaxNum;

    UINT16                        usEtDebugFlag;

    UINT16                        usBandWidth;
    UINT16                        usFreq;
    UINT16                        usEtCalApcCode;
    UINT16                        usDbbCode;

    UINT16                        usMrxSelect;
    UINT16                        usMrxGain;
    UINT16                        usMrxVgaGain;

    UINT16                        usEtPaOffset;
    UINT16                        usEtPostGain;         /* �߼����䣬Ĭ��Ϊ0 */
    UINT16                        usEtPostOffset;       /* �߼����䣬Ĭ��Ϊ0 */

    UINT16                        usEtCalApcMaxNum;
    INT16                         sPowOffset;
    UINT16                        usFreqCalApcCodeIndex;
    UINT16                        usCtMaxNum;

    INT32                         lMrxIData;
    INT32                         lMrxQData;

    /* ��������ʹ�õĲ��� */
    INT16                         sEtToAptThreshold;
    INT16                         sAptToEtThreshold;
    INT16                         sEtLutRefPow;
    INT16                         sEtDelayRefPow;
}NV_LTE_ETM_ET_APT_BAND_LAB_STRU;

/* DPD BAND��� */
typedef struct
{
    /* У׼ʹ�õĲ��� */
    NV_LTE_DPD_LUT_BAND_CAL_STRU  stDpdCalLutPara;  /* ����У׼DPD LUT����Ҫ�Ĳ��� */

    /* ��������ʹ�õĲ��� */
    UINT16 usDpdOpenFlag;                            /* DPD�Ƿ�� */
    UINT16 usPefOpenFlag;                            /* PEF�Ƿ�� */
}NV_LTE_DPD_BAND_LAB_STRU;

/* ET/APT BAND��ذ뾲̬MIPIָ�� */
typedef struct
{
    UINT32 usResv;
}NV_LTE_ETM_SEMI_STATIC_MIPI_CMD_BAND_LAB_STRU;

/* ET/APT BAND��ض�̬MIPIָ�� */
typedef struct
{
    /* ET MODE MIPI CMD */
    NV_TX_ET_APT_TRIGER_PARA       astEtCalPara[ET_DPD_BANDWIDTH_NUM];

    NV_TX_ET_APT_TRIGER_PARA       astEtPara[ET_DPD_BANDWIDTH_NUM];
    LTE_ET_APT_POW_VALUE_TYPE_STRU astEtPowReg02Para[ET_POW_MAX_NUM];

    /* APT MODE MIPI CMD */
    NV_TX_ET_APT_TRIGER_PARA       stAptPAHighPara;  /*pa�ߵ���Ҫ���õİ뾲̬����*/
    NV_TX_ET_APT_TRIGER_PARA       stAptPAMidhPara;  /*pa�е���Ҫ���õİ뾲̬����*/
    NV_TX_ET_APT_TRIGER_PARA       stAptPALowhPara;  /*pa�͵���Ҫ���õİ뾲̬����*/
    LPHY_MIPIDEV_CMD_STRU          stAptPaHVoltPara; /*����pa H apt��ѹ������mipi*/
    LPHY_MIPIDEV_CMD_STRU          stAptPaMVoltPara;    /*����pa M apt��ѹ������mipi*/
    LPHY_MIPIDEV_CMD_STRU          stAptPaLVoltPara;    /*����pa L apt��ѹ������mipi*/

    UINT8                          aucPaHighAptPara[APT_POW_MAX_NUM];
    UINT8                          aucPaMidAptPara[APT_POW_MAX_NUM];
    UINT8                          aucPaLowAptPara[APT_POW_MAX_NUM];

    /* TRIGET MIPI CMD */
    LPHY_MIPIDEV_CMD_STRU          stMipiTriger;   /* MIPI TRIGERָ�� */
    UINT16                         usEtReg02Num;
    //UINT16                         usAptReg02Num;
    //UINT16                         usAptReg01Num;
    UINT16                         usResv;
}NV_LTE_ETM_DYNAMIC_MIPI_CMD_BAND_LAB_STRU;

/* ET DPDʵ���Ҳ��� */
typedef struct
{
    NV_LTE_ET_PIN_COMP_BAND_STRU stEtPinComp;
}NV_LTE_ET_DPD_COMP_BAND_LAB_STRU;

/* ET/APT BAND��� */
typedef struct
{
    /* ��������ʹ�õĲ��� */
    NV_LTE_ET_LUT_BAND_STRU       stEtLutBandFac;        /* ET LUT�� */
    NV_LTE_ET_DELAY_BAND_FAC_STRU stEtDelayBandFac;      /* ET����У׼�ķ���ʱ�� */
}NV_LTE_ETM_ET_APT_BAND_FAC_STRU;

/* DPD BAND��� */
typedef struct
{
    /* ��������ʹ�õĲ��� */
    UINT16                   usXmax;                               /* ������������ֵ */
    UINT16                   usRealNum;
    NV_LTE_DPD_LUT_BAND_STRU astDpdLutBandFac[ET_DPD_VGA_MAX_NUM];  /* DPD LUT�� */
}NV_LTE_DPD_BAND_FAC_STRU;

/* ET DPD����У׼���� */
typedef struct
{
    NV_LTE_ET_POUT_FREQ_COMP_STRU  stEtPoutFreqComp;
}NV_LTE_ET_DPD_COMP_BAND_FAC_STRU;


/**************************ET DPDУ׼NV END**********************/
typedef struct
{
    NV_PA_LEVEL_THRE_STRU stPaThre;          /*PA��λ����*/
	NV_LTE_PA_TEMP_DET_CHANNEL_STRU stPaTempDetCh;
    NV_LTE_TX_CAL_LIST_STRU         stTxCalFreqListLab;      /*TXУ׼Ƶ�㣬�ɵ͵��߷���*/
    NV_LTE_APC_TABLE_STRU           stApcTableLab;           /*k3v5_bzj apc teble pre band*/
    NV_EQUIP_TX_FILTER_CMP_STRU           stTxFilterCompLab;    /*k3v5_bzj ��ͬ����,rb�Ĺ��ʲ��� 1/8db��λ*/
    NV_LTE_DEFAULT_POW_TABLE_STRU   stTxDefaultPowLab;       /*k3v5_bzj rfĬ�Ϸ��书�ʣ���У׼�����ж�ʹ��*/
    NV_LTE_TX_CAL_RESULT_TABLE_STRU stTXCalResultFac;        /*k3v5_bzj ����У׼���*/
    NV_LTE_RF_TXIQ_CAL_STRU                stTxiqCal;
    NV_LTE_HD3_CAL_PARA_STRU        stHD3CalParaLab;          /*HD3У׼����*/
    NV_LTE_HD3_CAL_RSULT_STRU       stHD3CalResultFac;        /*HD3У׼���*/
    NV_TX_RF_FREQ_COMP_STRU         stFreq;                   /*k3v5_bzj*/
    NV_TX_PA_TEMP_COMP              stTxTempCompFac;
    //INT16   asLteTxTempCmpVal[RF_TX_GAIN_6362_NUM][32];  /*tx�²�*//*k3v5_bzj*/
    UL_APT_PARA_STRU                   stAptPara;        /*APT����ʹ�ܿ���*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaHighVoltTbl;   /*APT PDM�ߵ�λ������*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaMidVoltTbl;    /*APT PDM�п�����*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaLowVoltTbl;    /*APT PDM�Ϳ�����*/
    /*MPR begin*/
    UINT16 ausMprVal[4];
    /*MPR end*/
    UL_AMPR_STRU astAMprVal[LPHY_MAX_BANDWIDTH_NUM];
    /* END:   Added by xueqiuyan, 2012/5/17 */
    UINT32 ulAmprValNS05;
    UINT16 usAmprValNS09[2];
    /* END:   Added by xueqiuyan, 2012/10/10 */
    INT16  asAptPaHighCmp[UL_APT_VBIAS_NUM];             /*APT PA���油��*/
    INT16  asAptPaMidCmp[UL_APT_VBIAS_NUM];              /*APT PA���油��*/
    INT16  asAptPaLowCmp[UL_APT_VBIAS_NUM];              /*APT PA���油��*/
	/*NV_TX_CMP_RSV_STRU   stTxCmpRsv;*/
    NV_ANT_SAR_STRU   stAntSarPwr;

    NV_LTE_DPDT_ANT_SAR_STRU        stLteDpdtAntSarPwr;

#if 1
    LTE_OTHER_COMP_STRU     stOtherComp;
#else
    LTE_TX_DIVERSITY_LOSS_COMP stDivComp;
#endif

    NV_UL_PD_TX_PARA              stPdNv;
    NV_TX_PD_AUTO_CAL_PARA        stPdAutoCal;
    NV_TX_PD_PWR_TABLE_STRU       stPdPowerTbl;         /*PD���ʱ�*/
    NV_TX_PD_VOLT_TABLE_STRU      stPdVoltTbl;          /*PD��ѹ��*/
    NV_TX_PD_TEMPCMP_TABLE_STRU   stPdTempTbl;          /*PD�¶ȱ�*/

    /*ET�����漰NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtLowChLut;         /*���ŵ�LUT������NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtMiddleChLut;      /*���ŵ�LUT������NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtHighChLut;        /*���ŵ�LUT������NV*/
	NV_TX_ET_BAND_PARA            stEtBandPara;         /*ET BAND NV��������NV*/
	NV_LTE_ET_GAIN_COMP           stEtGainComp;         /*ET PA Gain ����*/
	NV_TX_ET_FINEDLY_PARA         stEtFineDlyPara;      /*ET ϸ�������ӳ�ϵ��������NV*/
	NV_LTE_ET_VOFFSET_GAIN        stEtVoffsetGain;      /*ETM Voffset��GainУ׼ֵ������NV*/
	NV_TX_ET_EVDELY               stEtEvDely;           /*ET ����ͨ����ʱ�ֵ�*/

	NV_RF_CA_RCCODE_STRU          stRfRCcode;           /*RFIC Code*/
	/* ETMʹ�õ�NV */
    NV_LTE_ETM_ET_APT_BAND_LAB_STRU   stEtmBandLabPara;
    NV_LTE_ETM_ET_APT_BAND_FAC_STRU   stEtmBandFacPara;

    /* DPDʹ�õ�NV */
    NV_LTE_DPD_BAND_LAB_STRU          stDpdBandLabPara;
    NV_LTE_DPD_BAND_FAC_STRU          stDpdBandFacPara;

    /* ETM��MIPIָ� */
    NV_LTE_ETM_SEMI_STATIC_MIPI_CMD_BAND_LAB_STRU    stEtmSemiStaticCmdBandPara;
    NV_LTE_ETM_DYNAMIC_MIPI_CMD_BAND_LAB_STRU        stEtmDynamicCmdBandPara;

    /* ET DPDƵ�ʹ��ʲ���NV */
    NV_LTE_ET_DPD_COMP_BAND_LAB_STRU  stEtDpdCompLabPara;
    NV_LTE_ET_DPD_COMP_BAND_FAC_STRU  stEtDpdCompFacPara;
}NV_BAND_TXPATH_PARA_STRU;

typedef struct
{
	UINT16 usModemLoss[2];	/*ʮ����֮һ��λ*/	
}NV_MODEM_LOSS_STRU;

typedef struct
{
    NV_MODEM_LOSS_STRU          stModemLoss;                           /*Modem���������߼�����*/
    UINT16                      ausTempSensor[PA_TEMP_NUM];            /*PA���������⵽��ƽ̨�¶�ת��ɵ�ѹ*/
}NV_BAND_COMMON_PARA_STRU;





#define MAX_6361_INIT_REG_NUM     (32)
//#define MAX_6362_INIT_REG_NUM     (256)
#define MAX_COMM_RSV            2
#define MAX_ABB_CH               2
#define MAX_BAND_RSV             2
#define RFIC_CTUNE_DEBUG        2
#define MAX_MIPI_INIT_NUM   16
#define MAX_CA_COUPLE           20
#define MAX_DEBUG_NUM           (12)
#define ANT_MIPI_NUM            (3)
#define PA_MIPI_NUM             (4)
#define APT_MIPI_NUM            (2)

typedef struct
{
    UINT16 usBand;
    UINT16 bitPathUsedNum : 4;
    UINT16 bitRsv     :12;
}NV_FE_BAND_RF_PATH_USED_STRU;

typedef struct
{
	//UINT32  		bitRfRxVCOCore            : 1; 	 	/*VCO Coreѡ��,��ʹ�ã�����д��*/
	UINT32  		bitRsv0     			: 1;
	//UINT32  		bitRfRxDiv		    	: 4; 	 	/*VCO����,��ʹ�ã�����д��*/
	UINT32  		bitRsv1    		    	: 4;
	UINT32  		bitRficGroupSel	    	: 1;  		/*RFIC LNA GROUP*/
	//UINT32  		bitRficRxLOSel			: 1;  		/*����ѡ��Ŀǰ��ͨ���󶨣���ʹ��*/
	UINT32  		bitRsv2     			: 1;
	UINT32  		bitRfRx0LNA		    	: 4;  		/*RFIC RXA LNA*/
	UINT32  		bitRfRx1LNA		    	: 4; 		/*RFIC RXB LNA*/
	UINT32  		bitRfChIdx      		: 1;  		/*bandʹ�õ�ABBͨ��˫��band��ʹ�ø�ͨ����*/
	//UINT32  		bitRfTxVCOCore	        : 1; 	 	/*VCO Coreѡ��,��ʹ�ã�����д��*/
	UINT32  		bitRsv3     		    : 1;
	//UINT32  		bitRfTxDiv		        : 4; 	 	/*VCO����,��ʹ�ã�����д��*/
	UINT32  		bitRsv4  		        : 4;
	UINT32  		bitRfTx0Port			: 4; 		/*RFIC TX0 Port ֻ��pcc ʹ��*/
    UINT32          bitRsv                  : 7;
}NV_RFIC_6362_STRU;

typedef struct
{
    NV_RFIC_6362_STRU                stRfic[MAX_RFIC_PATH_NUM];
    /*Mipi Gpio need?*/
}NV_RF_PATH_STRU;

typedef struct
{
    UINT32                           bitDualStandbyFlg      :1;                 /*��˫��ָʾ 1:˫�� 0:����*/
    UINT32                           bitRficNum             :2;                 /*��ǰƽ̨rfic��Ŀ*/
    UINT32                           bitCurrentAbbCH        :1;                 /*��rficʱ��ǰ��ʹ�õ�rf*/
    UINT32                           bitAbbChExchFlg        :1;                 /*6362��ABͨ����ABB0����1����*/
    UINT32                           bitAbbTxCh             :1;                 /**/
    UINT32                           bitPrint               :1;
    UINT32                           bitDeepPrint           :1;
    UINT32                           bitRsvAllEn            :8;
    UINT32                           bitPccBandNum          :16;                /*��ǰ����֧��band��Ŀ*/
    NV_FE_BAND_RF_PATH_USED_STRU     stFeBandRfPathUsed[MAX_PCC_BAND_NUM];
    NV_RF_PATH_STRU                  stBandRfPara[MAX_PCC_BAND_NUM];            /*6362����: RFͨ·NV����*/
}NV_FE_BASIC_INFO_STRU;

/*typedef struct
{
    UINT16 usRegAddr;
    UINT16 usRegCfg;
}NV_RFIC_REG_CONFIG_STRU;
*/
typedef struct
{
    UINT32 ulInitNum;
    UCOM_NV_RF_INIT_INFO_STRU stRfCfg[MAX_6361_INIT_REG_NUM];
}NV_FE_6361_INIT_STRU;
/*typedef struct
{
    UINT32 ulInitNum;
    NV_RFIC_REG_CONFIG_STRU stRfCfg[MAX_6362_INIT_REG_NUM];
}NV_FE_6362_INIT_STRU;
*/
typedef struct
{
    UINT8 ucDebugEn;
    UINT8 ucRegNum;
    UINT16 usProcCH;
    UINT8 ucRfRegList[MAX_DEBUG_NUM];
}NV_RF_REG_DEBUG_STRU;

typedef struct
{
    UINT32 ulRegAddr;
    UINT32 ulRegCfg;
}NV_BBP_REG_CFG_STRU;
typedef struct
{
    UINT32 bitValidFlg  : 1;
    UINT32 bitRfRegAddr : 8;
    UINT32 bitRfRegCfg  : 16;
    UINT32 bitRsv        : 7;
}NV_RF_CTUNING_DEBUG_STRU;
typedef struct
{
    UINT32 reserved0            : 1;
    UINT32 lte_rxb_iq_exchange  : 1;
    UINT32 lte_rxb_q_inv        : 1;
    UINT32 lte_rxb_i_inv        : 1;
    UINT32 lte_rxa_iq_exchange  : 1;
    UINT32 lte_rxa_q_inv        : 1;
    UINT32 lte_rxa_i_inv        : 1;
    UINT32 lte_tx_iq_exchange   : 1;
    UINT32 lte_tx_q_inv         : 1;
    UINT32 lte_tx_i_inv         : 1;
    UINT32 reserved1            : 22;
}NV_ABB_IF_FMT_STRU;
typedef struct
{
    UINT32               ulRfTcvrOn;
    UINT32               ulRfUnReset;        /*RF�⸴λ���� 1:�⸴λ*/
    UINT32               ulAgcStub;          /*ǰ��ǿ�ƴ�׮����16bitΪ��Ч��־����16bitΪ������*/
    UINT32               ulApcStub;          /*ǰ��ǿ�ƴ�׮����16bitΪ��Ч��־����16bitΪ������*/
    UINT32               ulTrxSwitchMap;
    UINT32               ulTxSwitchMap;
    NV_ABB_IF_FMT_STRU      stAbbIfFmt;          /*ABB IQ����*/
    NV_RF_REG_DEBUG_STRU stRfDebug;
}NV_FE_COMM_CONFIG_STRU;

#if defined(LPHY_FEATURE_TAS)
typedef struct
{
    UINT32 ulDpdt0Default;
    UINT32 ulDpdt0SwitchMap;
    UINT32 ulDpdtPreT1;
    UINT32 ulDpdtPostT2;
}NV_PBAND_TAS_CFG;
#else
typedef struct
{
    UINT32 ulDpdt0Default;
    UINT32 ulDpdt0SwitchMap;
    UINT32 ulDpdt1Default;
    UINT32 ulDpdt1SwitchMap;
}NV_PBAND_TAS_CFG;
#endif

/*k3v3+tas new nv for lte begin*/
typedef struct
{
    UINT32 ulTasDpdt0Default;
    UINT32 ulTasDpdt0SwitchMap;
}NV_GPIO_TAS_CFG;

typedef struct
{
    UINT32 ulTasDpdtPreT1;
    UINT32 ulTasDpdtPostT2;
}NV_TAS_DPDT_PROTECT_CFG;

typedef struct
{
    UINT32 ulTasClgModeGpio;
}NV_TAS_CLG_MODE_GPIO_CFG;

typedef struct
{
    INT16 slDpdtMeasStartThr;
    INT16 ulReserv;
}NV_TAS_BLIND_SW_THD_STRU;
typedef struct
{
    INT32 lHappyRsrpThr;
    INT32 lUnhappyRsrpThr;
}NV_TAS_HAPPY_UNHAPPY_THD_STRU;
/*k3v3+tas liyundong00196522 end*/

typedef struct
{
    UINT32 bitAbbCH                       :1;          /*Band����ABBͨ����0:CH0��1:CH1*/
    UINT32 bitRfIdx                       :1;          /*Band����RFIC��0:RFIC0��1:RFIC1*/
    UINT32 bitAfcPdmSrcSel               :1;          /*band afc pdm Դѡ��*/
    UINT32 bitAptPdmSrcSel               :1;          /*band apt pdm Դѡ��*/
    UINT32 bitPmuSsiSrcSel               :1;
    UINT32 bitRfABChanExchg              :1;          /*ABB ABͨ��������־ 1:���� 0:������*/
    UINT32 bitIntraBandNonCCABExchg      :1;          /*ͬ1band������CA ABͨ���������*/
    UINT32 bitBlindSwitchFlag            :1;        /*�Ƿ�֧��TASä��,0��֧�֣�����߶���*/
    UINT32 bitRsv                        :24;       /*32bit����*/
}NV_PBAND_CHAN_PARA_STRU;

typedef struct
{
    UINT32                  ulBandAntSelRx;      /*Band�������߿���*/
    UINT32                  ulTddBandAntSelTx0;  /*��������ѡ��ָʾΪ0ʱ��Band�������߿��أ���TDD����*/
    UINT32                  ulBandAntSelTx1;    /*��������ѡ��ָʾΪ1ʱ��Band�������߿���*/
    UINT32                  ulTxAntSel;
    UINT32                  ulPaEnMap;          /*��Band Paen map,SCC�޴˲���*/
    UINT32                  ulPaMode0Map;
    UINT32                  ulPaMode1Map;
    UINT16                  usPaModeCfg;        /*0x0~0x3����Ϊ�ͣ��У�NULL���ߵ�,0x30�Կ�*/
    UINT16                  usPaEnCfg;          /*0x3:ǿ�Ƹ� 0x1ǿ�Ƶͣ�0x30�Կ�*/
    UINT16                  usSrsPaOpenTime;
    UINT16                  usPchPaOpenTime;
    NV_PBAND_TAS_CFG        stTasConfig;       /*tas config*/
}NV_PBAND_CONFIG_PARA_STRU;
typedef struct
{
    UINT8  ucRx0Lna;
    UINT8  ucRx1Lna;
    UINT8  ucTxLna;
    UINT8  ucResv;
    NV_RF_CTUNING_DEBUG_STRU stRfCtuning;
}NV_PBAND_RFIC_PARA_STRU;
typedef struct
{
    UINT32 ulNum;
    LPHY_MIPIDEV_CMD_STRU astMipiCfg[MAX_MIPI_INIT_NUM];
}NV_MIPI_INIT_STRU;

typedef struct
{
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx[ANT_MIPI_NUM]; /*ANT0�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx[ANT_MIPI_NUM]; /*ANT1�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiTx[ANT_MIPI_NUM]; /*ANT0�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiTx[ANT_MIPI_NUM]; /*ANT1�������߿���*/
	LPHY_MIPIDEV_CMD_STRU      stAnt0Trig; /*ANT1�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1Trig; /*ANT1�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stPaOnMipi;          /*PAʹ������*/
    LPHY_MIPIDEV_CMD_STRU      stPaOffMipi;         /*PAʹ������*/
    LPHY_MIPIDEV_CMD_STRU      stPaHighMipi[PA_MIPI_NUM];    /*PA�ߵ�MIPI����*/
    LPHY_MIPIDEV_CMD_STRU      stPaMidMipi [PA_MIPI_NUM];     /*PA�е�MIPI����*/
    LPHY_MIPIDEV_CMD_STRU      stPaLowMipi [PA_MIPI_NUM];     /*PA�͵�MIPI����*/
	LPHY_MIPIDEV_CMD_STRU      stPaTrig; /*ANT1�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt0Mipi[2];    /*ANT0���ߵ�г*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt1Mipi[2];    /*ANT0���ߵ�г*/
    LPHY_MIPIDEV_CMD_STRU      stMipiRsv[2];           /*Ԥ��һ��MIPI*/
}NV_PBAND_MIPI_PARA_STRU;
typedef struct
{
    UINT16 usPccBand;
    UINT16 usSccBand;
    LPHY_MIPIDEV_CMD_STRU      stAnt0TunerMipi[2]; /*SCC ANT0�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1TunerMipi[2]; /*SCC ANT0�������߿���*/
}NV_FE_CA_TUNER_PARA_STRU;

typedef struct
{
    UINT32                     ulBandAntSelRx;      /*Band�������߿���*/
    UINT32                     ucSccRfABExchg;
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx[ANT_MIPI_NUM]; /*SCC ANT0�������߿���*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx[ANT_MIPI_NUM]; /*SCC ANT1�������߿���*/
    /*Tuner Mipi Cmd move here*/
    NV_FE_CA_TUNER_PARA_STRU   stCaTunerPara;
    LPHY_MIPIDEV_CMD_STRU      stAnt0Trig; /*ANT1�������߿���*/
	LPHY_MIPIDEV_CMD_STRU      stAnt1Trig; /*ANT1�������߿���*/
}NV_SBAND_LINE_STRU;



/*ͨ����������*/
typedef struct
{
    UINT32  bitRx0Lna           :4;
    UINT32  bitRx1Lna           :4;
    UINT32  bitRsv0              :24;
}NV_SBAND_RFIC_CONFIG_STRU;

    //NV_SBAND_CHAN_PARA_STRU         stSBandChanPara[MAX_SCC_BAND_NUM];

typedef struct
{
	//NV_RFIC_6362_STRU 			stRfic;
    UINT8                       ucSccRfPathIdx;
    UINT8                       ucRsv[3];
    NV_SBAND_RFIC_CONFIG_STRU   stRfCfg;
    NV_SBAND_LINE_STRU          stSBandInfo;
}NV_SBAND_CONFIG_STRU;

/*RFIC ��������*/
typedef struct
{
    UINT32                           usSBandNum;
    UINT32                           usSBandInd[MAX_SCC_BAND_NUM]; /*SCC * 5*/
    UINT16                           usRsv[2];


    NV_SBAND_CONFIG_STRU            stSBandPara[MAX_SCC_BAND_NUM];
}NV_SBAND_CONFIG_PARA_STRU;

typedef struct
{
    UINT16                          usBand;
    UINT16                          ucNvValidFlg;
    NV_PBAND_CHAN_PARA_STRU         stBandChanPara;
    NV_PBAND_CONFIG_PARA_STRU       stBandLinePara;
    NV_PBAND_RFIC_PARA_STRU         stBandRfPara;
    NV_PBAND_MIPI_PARA_STRU         stBandMipiPara;
    NV_SBAND_CONFIG_PARA_STRU       stBandSccPara;
}NV_BAND_FE_PARA_STRU;



typedef struct
{



	UINT32 	ulLPhyNvSize;
}NV_LPHY_NV_SIZE_STRU;

/*for notch only B39*/
#define NOTCH_MIPI_MAX  2
typedef struct
{
	UINT16 usNotchEnFlg;
	UINT16 usGpioCfgFlg;
	UINT32 ulGpioNotchCfg;
	LPHY_MIPIDEV_CMD_STRU  stNotchMipiCfg[NOTCH_MIPI_MAX];
}NV_FE_NOTCH_INFO_STRU;

/* Begin: Added by luzhejun, 2014-03-17 PN:LTE_WIFI*/
typedef struct
{
    UINT16 		 usLWCoexEnbale;
    UINT16       usTimerAheadTx;
    UINT16		 usTimerDelayTx;
    UINT16       usTimerAheadRx;
    UINT16		 usTimerDelayRx;
    UINT16		Reserved;
}NV_LPHY_LWCOEX_INIT_PARA_STRU;

/* END: Added by luzhejun, 2014-03-17 PN:LTE_WIFI*/

/*Tcxo����Ƶ�����ԣ�PPM��PDM֮���ת��ϵ������NV�Ǹ�����NV*/
typedef struct
{
    UINT8      ucConvertFactor;
    UINT8      ucReserved;
    UINT16     usReserved;
}NV_LPHY_CONVERT_FACTOR_PARA_STRU;

typedef struct
{
    UINT16      usVrmpFlag;
    UINT16      usBand39Vol;
}NV_LPHY_VRAMP_PARA_STRU;


#define MAX_MIPI_PA_ADDED_NUM    (2)
typedef struct
{
    LPHY_MIPIDEV_CMD_STRU   stPaLowCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaMidCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaHigCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaTrig;
}MIPI_PA_CONFIG_STRU;
typedef struct
{
    UINT32 ulPaTrigModeEn;
    MIPI_PA_CONFIG_STRU stBandPaMipi[MAX_PCC_BAND_NUM];
}NV_MIPI_PA_ADDED_CONFIG_STRU;

typedef struct
{
    LPHY_MIPIDEV_CMD_STRU stMipiAntRx0;
    LPHY_MIPIDEV_CMD_STRU stMipiAntRx1;
    LPHY_MIPIDEV_CMD_STRU stMipiAntTx;
}MIPI_ANT_CONFIG_STRU;

typedef struct
{
    MIPI_ANT_CONFIG_STRU stBandAddedAntMipi[MAX_PCC_BAND_NUM];
}NV_MIPI_ANT_ADDED_CONFIG_STRU;


/* Begin: Added by mabohao, 2015-04-13 PN:Terminal*/
typedef struct
{
	UINT32 ulT10VGASPICfgTime;
	UINT16 usPaOpenTime;
	UINT16 usPaAttTime;
	UINT16 usAntSelTime;
	UINT16 usRsv0;
	UINT16 usRsv1;
	UINT16 usRsv2;
}TERMINAL_DSP_CFGTIME_PARA;

typedef struct
{
	UINT32 ulTrxSwitchMap;
	UINT32 ulTxSwitchMap;
	UINT32 ulRsv;
}TERMINAL_FE_COMM_CONFIG_PARA;

typedef struct
{
	UINT8 ucAntSelect;
	UINT8 ucLteC0C1Sel;
	UINT16 usLteTxTrxSwitchCfg;
	UINT16 usRsv0;
	UINT16 usRsv1;
}TERMINAL_LPHY_DSP_CONFIG_PARA;

typedef struct
{
	UINT8 ucNvSingleDualModeInd;
	UINT8 ucNvSingleDualRficInd;
	UINT8 ucNvPaMuxCtrl;
	UINT8 ucRsv;
}TERMINAL_MULTIMODE_DSP_COMMON_CONFIG_PARA;

typedef struct
{
	UINT32                                                                          ulNvValidFlg;
	TERMINAL_DSP_CFGTIME_PARA                                      stTermDspCfgTime;
	TERMINAL_FE_COMM_CONFIG_PARA                               stTermFeComCfg;
	TERMINAL_LPHY_DSP_CONFIG_PARA                              stTermDspCfg;
	TERMINAL_MULTIMODE_DSP_COMMON_CONFIG_PARA    stTermMulTiModeCfg;
}NV_TERMINAL_TO_DSP_STRU;

/* End:   Added by mabohao, 2015-04-13 PN:Terminal*/

#if 0
typedef struct
{
	UINT16   uhwEnable;                         /*ȫ��ͨ���Կ���*/
	UINT16   uhwResvered;
}NV_GU_TRI_MODE_ENABLE_STRU;

typedef struct
{
	UINT32    uwProfileId;
	UINT32    auwResvered[3];
}NV_GU_TRI_MODE_FEM_PROFILE_ID_STRU;

typedef struct
{
	UINT16   uhwABBSwitch;
	UINT16   uhwRFSwitch;
	UINT16   uhwTCXOSwitch;
	UINT16   uhwResvered;
	UINT16   uhwReserved[4];
}NV_GU_MODE_BASIC_PARA_STRU;

typedef struct
{
	NV_GU_MODE_BASIC_PARA_STRU   stModeBasicPara[8];
	UINT32                        uwRfSwitch;
	UINT32						  uwGsmRficSel;
	UINT32						  uwGpioCtrl;
    UINT32                        uwCdmaRficSel;
	UINT32                        auwResvered[13];
}NV_GU_TRI_MODE_CHAN_PARA_STRU;

typedef struct
{
	NV_GU_TRI_MODE_CHAN_PARA_STRU stPara[8];
}NV_GU_TRI_MODE_CHAN_PARA_PROFILE_STRU;
#endif

typedef struct
{
	UINT16 										usBandExtLNAEnFlg;
    UINT16                                      usBandInd;
	UINT16 										usGpioCfgFlg;
	UINT16   									uResvered;
	UINT32 										ulGpioCfg;
    LPHY_MIPIDEV_CMD_STRU      					stAnt0LNAMipiRxEnable[EXTERNAL_LNA_MIPI_NUM]; /*ANT0????LNA????*/
    LPHY_MIPIDEV_CMD_STRU      					stAnt1LNAMipiRxEnable[EXTERNAL_LNA_MIPI_NUM]; /*ANT1????LNA????*/
}NV_RF_BAND_EXTERNAL_LNA_INFO_STRU;

typedef struct
{
	UINT16   							usNumBandLNA;                         /**/
	UINT16   							uResvered;
	NV_RF_BAND_EXTERNAL_LNA_INFO_STRU	stBandLNAInfo[MAX_RX_LNA_NUM];
}NV_RF_LTE_BAND_EXTERNAL_LNA_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NV_LTE_DCXO_PPM_UPDATE_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DCXO ͨ��PPM����������²�ˢ���б𼰸���ʶ�������ֵ
*****************************************************************************/

typedef struct
{
    INT32  lPpmVarThr;                  /*��������*/
    INT16  sTempThr;                   /*���β������¶Ȳ�����*/
	UINT16 usNotHighTrainThr;           /*����ģʽ���Ǹ���ģʽʱ������(֡��)*/
    UINT16 usPpmDrxReadPeriod;          /*��DRX PPM������ʱ������λms*/
    UINT16 usPpmNonDrxReadPeriod;       /*CDRX PPM���β�����������ʱ������λms*/
}NV_LTE_DCXO_PPM_UPDATE_THRESHOLD_STRU;
/****************************************************************************************/

/*****************************************band�޹ص�nv��*********************************/

typedef struct
{
	UINT16 usViaCSupportEn;
	UINT16 usViaCActiveIndGpio;
	UINT32 ulViaCLineCtrlMask;
	UINT32 ulViaCLineCtrl;
}NV_GU_VIA_C_CONFIG_STRU;
/*typedef struct
{
    UINT16 uswAntShareSwitchEn;
    UINT16 uwReserved;
	UINT32 ulB26AntShareDpdt;
	UINT32 ulB26TxDisableLineCtrl;
	UINT32 ulB26VoLteSupportLineCtrl;
}NV_GU_ANT_SHARE_SWITCH_STRU;
*/

typedef struct
{
    UINT16 ulAptValidFlag;
    UINT16 ulAptCfgAheadTime;
    UINT16 ulTrigAheadTime;
    UINT16 ulRsv;
    LPHY_MIPIDEV_CMD_STRU   stAptModeDisable[APT_MIPI_NUM];
    LPHY_MIPIDEV_CMD_STRU   stAptModeStandby[APT_MIPI_NUM];
    LPHY_MIPIDEV_CMD_STRU   stAptMode3G4G[APT_MIPI_NUM];
    LPHY_MIPIDEV_CMD_STRU   stAptData[APT_MIPI_NUM];
    LPHY_MIPIDEV_CMD_STRU   stAptOff[APT_MIPI_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaTrig;
}NV_LPHY_MIPI_APT_STRU;

typedef struct
{
    NV_LPHY_NV_SIZE_STRU        stLPhyNvSize;       /*NV��Size*/
    NV_TIMING_PARA_STRU         stTiming;           /*��ʱNV��*/
    NV_EMU_FAKECELL_PARA_STRU   stEmuFakeCell;      /*��������С����ʱʧЧ�о�*/
    NV_CQI_PARA_STRU            stCqi;              /*CQI NV��*/
	NV_ASU_PARA_STRU            stAsu;
    NV_ANTCORR_PARA_STRU        stCorr;             /*��� NV��*/
    NV_RLM_PARA_STRU            stRLM;              /*RLM�����*/
    NV_AFC_PARA_STRU            stAFC;              /*AFC NV��*/
    NV_IRC_PUB_STRU             stIrcPub;
    NV_CHE_INTP_STRU            stCheIntp;
    NV_VITERBI_PARA_STRU        stViterbi;
    NV_TURBO_PARA_STRU          stTurbo;
    NV_DEM_LIST_STRU            stDEM;
    NV_EMU_PARA_STRU            stEmu;                /*��������*/
    //NV_LPHY_AGC_BASE_TABLE_STRU stAgcBase;          /*AGC��׼��*/
    NV_UL_PARA_STRU             stUl;
    NV_AGC_PARA_STRU            stAGC;                         /*agc NV�� */
    NV_VERSION_STRU             stVersion;          /*NV �汾��Ϣ*/

    NV_LPHY_DSP_CONFIG          stDspCfg;           /*DSP������ʼ��������������NV*/
    NV_GULPHY_COMMON_PARA_CONFIG stGULCommParaCfg;  /*GUL��ģ������������NV�ṹ��*/

    LTE_TCXO_DYNAMIC_CONFIG_STRU    stVctcxoDynamicConfig;
    UINT16 	usVctcxoInit;	                        /*Vco��ֵ*/
    UINT16      usRsv1;

    NV_BT_CMP_SWITCH_STRU stBtCmpSwitch;

	NV_DSP_CONFIG_TIME_STRU      stRFECfgTime;      /*DSP�������ʱ������NV����*/

    NV_FE_NOTCH_INFO_STRU               stNotchInfo;   /*notch config*/
    NV_FE_BASIC_INFO_STRU               stFeBasicInfo;
    NV_FE_6361_INIT_STRU                stFeRfInitInfo;
    NV_FE_COMM_CONFIG_STRU              stFeCommCfg;



    NV_PHY_FUNC_VERIFY_STUB_STRU       stPhyFuncDebugPara;
    /* END:   Added by luliwu,  2012/2/3  PN: DTS_TISTISTIS */
    NV_RX_BT_LEVEL_MAP_TABLE_STRU stRxBtMapTable;

    VOS_UINT32                    ulSleepAddr;

    NV_TX_APC_GAIN_STRU           stDefaultTxGainStatus;
    NV_LPHY_PD_COMM_PARA          stPdComm;
    NV_MIPI_INIT_STRU             stMipiInitCfg;

    /*ET����ʹ��NV*/
    NV_TX_ET_COMM_PARA_STRU       stEtCommPara;                /*ET��������*/
    NV_TX_ETM_VENDOR_PARA         stEtEtmVendorPara;           /*ET Modulator���Ҳ���*/

    /*RFICУ׼ʹ��NV*/
    NV_RF_CA_RCCAL_CFG_STRU       stRfRCcalCfg;                /*RFIC CA У׼����*/
    /* Begin: Added by luzhejun, 2014-03-17 PN:LTE_WIFI*/
    NV_LPHY_LWCOEX_INIT_PARA_STRU  stLWCoexInitPara;
    /* END: Added by luzhejun, 2014-03-17 PN:LTE_WIFI*/

    NV_LPHY_VRAMP_PARA_STRU             stVrampPara;

    TLCOMM_NV_SINGLE_XO_DEFINE_STRU stSingleXoDefine;           /*��XO���ͼ�32k��Ƶ������*/

    NV_ET_SELECT_WORK_MODE_LAB_STRU   stEtSelect;
    NV_DPD_SELECT_WORK_MODE_LAB_STRU  stDpdSelect;
    NV_ET_APT_MIPI_CMD_LAB_STRU       stEtmCmdPara;
    NV_LPHY_CONVERT_FACTOR_PARA_STRU stConvertFactor;           /*PPM��PDM֮���ת��ϵ��*/

    UINT16 stTasEna;
	UINT16 usResv2;

	NV_GPIO_TAS_CFG stLteGpioTas;

    NV_TAS_DPDT_PROTECT_CFG stLteDpdtProtect;
	/*+tas gpio nv by lijiuyong 20141024 end*/
	NV_LTE_TAS_BS_RSSI_THD_STRU   stTasBSRssiThd;					/*LTE TASɨƵ�׶�Rssi����ֵ*/
	NV_TAS_BLIND_SW_THD_STRU stTasBlindSwThr;

    NV_TAS_CLG_MODE_GPIO_CFG stTasClgModeGpioMap;
	NV_TAS_HAPPY_UNHAPPY_THD_STRU stTasHappyThr;
	UCOM_NV_TRI_MODE_ENABLE_STRU  stGuTriEn;
	UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU  stGuProfileId;
	UCOM_NV_FEM_CHAN_PROFILE_STRU   stGuChanPara;
	UL_AMPR_BAND26_STRU astAmprValBand26;
    UL_AMPR_BAND28_STRU astAmprValBand28;

	UCOM_NV_VIA_C_CONFIG_STRU     stViaConfig;
	UCOM_NV_B26_ANT_SHARE_CONFIG_STRU stAntShareSwitch;
	NV_RF_LTE_BAND_EXTERNAL_LNA_CFG_STRU stRfLTEBandExtLNACfg;

	NV_LTE_DCXO_PPM_UPDATE_THRESHOLD_STRU stDcxoPpmUpdateThr;     /*DCXO LTE�²�������ʶ��PPM��������*/
	NV_LPHY_MIPI_APT_STRU       stMipiApt;
    NV_LTE_COM_ANT_SAR_STRU stComAntSar; //��SAR��������
}LTE_NV_PARA_STRU;
/**********************************************************************************************/
/*******************************band��ص�nv��*******************************************/
typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
    NV_BAND_TXPATH_PARA_STRU         stTxPath;
}LTE_BAND_NV_PARA_STRU;

typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
}LTE_BAND_NV_RX_PARA_STRU;
/**********************************************************************************************/
/*����ȫ�ֱ���,������ģ�����*/
extern LTE_NV_PARA_STRU  *gptrLteNvPara;

typedef struct
{
    UINT16                          usBand;
    UINT16                          usNvValidFlg;
    NV_PBAND_CHAN_PARA_STRU         stBandChanPara;
    NV_PBAND_CONFIG_PARA_STRU       stBandLinePara;
    NV_PBAND_RFIC_PARA_STRU         stBandRfPara;
    NV_PBAND_MIPI_PARA_STRU         stBandMipiPara;
    NV_SBAND_CONFIG_PARA_STRU       stBandSccPara;
}LPHY_RFD_INTRA_BAND_NV_STRU;
typedef struct
{
    UINT16                          usBand;
    UINT16                          usNvValidFlg;
    NV_PBAND_CHAN_PARA_STRU         stBandChanPara;
    NV_PBAND_CONFIG_PARA_STRU       stBandLinePara;
    NV_PBAND_RFIC_PARA_STRU         stBandRfPara;
    NV_PBAND_MIPI_PARA_STRU         stBandMipiPara;
}LPHY_RFD_INTER_BAND_NV_STRU;

typedef struct
{
    LPHY_RFD_INTRA_BAND_NV_STRU     stRfdIntraBandNv;
    NV_RFIC_6362_STRU               stRfic6362;
}LTE_NV_RFD_LSCANW_STRU;

typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
}LTE_NV_RX_PARA_LSCANW_STRU;

typedef struct
{
	UINT32  			            pNvAddr;           /*nv ddr��ַ*/
    UINT16                          usBand;
    UINT16                          usNvValidFlg;
	NV_PBAND_CHAN_PARA_STRU         stBandChanPara;
}LRRC_LPHY_DDR_BAND_STRU;

/*PS���ݸýṹ�����ز�NV��Ϣ���ص�DSP�ڴ�*/
typedef struct
{
    UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU    *pstRfInitNvAddr;
    LRRC_LPHY_DDR_BAND_STRU stNvDdrInfo[MAX_PCC_BAND_NUM];
}LRRC_LPHY_FENV_BAND_DDR_INFO_STRU;

typedef struct
{
    UINT16 usBand;
    UINT16 usValidFlg;
    UINT32 ulFeNvAdd;
    UINT32 ulRxParaNvAdd;
}LRRC_LPHY_LSCANW_DDR_ADDR_STRU;
typedef struct
{
    LRRC_LPHY_LSCANW_DDR_ADDR_STRU strDdrAddr[MAX_LSCANW_BAND_NUM];
}LRRC_LPHY_LSCANW_DDR_ADDR_LIST_STRU;

/*ddr�е�ַ��Ӧ��tcm�е��������ַ�����Э��ջʹ��*/
#define NV_BAND_FE_PARA_STRU_DDR_BASE (BAND_MAILBOX_NV_IDX_BASE_ADDR)
#define NV_BAND_FE_LSCANW_STRU_DDR_BASE (NV_BAND_FE_PARA_STRU_DDR_BASE + sizeof(LRRC_LPHY_FENV_BAND_DDR_INFO_STRU))

//xuping add for TAS, end, 20150317
/********************************************V7R5 FE NV********************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LTE_NV_PARA_H__ */
