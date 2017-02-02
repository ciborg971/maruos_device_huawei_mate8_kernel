


#ifndef __RFE_OM_DEF_H__
#define __RFE_OM_DEF_H__


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
#define RFE_OM_READREG_NUM  12

#define  RFIN_Rx_Downlink                        (1 << 0)            /* */
#define  RFIN_Rx_DUMMY                           (1 << 1)            /* */
#define  RFIN_Rx_S                               (1 << 2)            /* */
#define  RFIN_Rx_S_DUMMY                         (1 << 3)            /* */
#define  RFIN_Tx_PUXCH                           (1 << 4)            /*PUSCH/PUCCH/PUSCH&PUCCH Long*/
#define  RFIN_Tx_PRACH                           (1 << 14)           /*PRACH 1~3 Long */
#define  RFIN_Tx_DUMMY                           (1 << 5)            /*no send*/
#define  RFIN_Tx_PUXCH_SHORTEN                   (1 << 6)            /*PUSCH/PUCCH/PUSCH&PUCCH Short*/
#define  RFIN_Tx_PRACH_SHORTEN                   (1 << 15)           /*PRACH 1~3 Short */
#define  RFIN_Tx_SRS_ONLY                        (1 << 7)            /*SRS On U Sfrm*/
#define  RFIN_Tx_PUXCH_SRS                       (1 << 8)            /* PUSCH&SRS/PUCCH&SRS/PUSCH&PUCCH&SRS*/
#define  RFIN_S_SRS_BOTH                         (1 << 9)            /* 2 SRS On S Sfrm*/
#define  RFIN_S_SRS_LAST                         (1 << 10)            /*2nd SRS On S Sfrm*/
#define  RFIN_S_SRS_SecondLAST                   (1 << 11)            /*1ST */
#define  RFIN_S_PRACH4                           (1 << 12)            /* */
#define  RFIN_S_PRACH4_DUMMY                     (1 << 13)            /* */
#define  RFIC_IDLE (0)
#define  RFIC_STANDBY (1)
#define  RFIC_RXON  (2)
#define  RFIC_TXON (3)


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
    LPHY_REQ_RFE_MBX_REPORT_ENA        = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RFE_NV_REPORT_ENA,
    LPHY_REQ_RFIN_DRV_REPORT_ENA,
    LPHY_REQ_RFE_REG_READ_ENA,
    LPHY_REQ_RFE_FIX_UL_POWER_ENA,
    LPHY_REQ_RFE_PCC_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_SCC_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FORCE_CELL_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_DLCH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_ULCH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FORCE_CH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FPU_CELL_CONFIG_REPORT_ENA,
    LPHY_REQ_RFE_DELAY_TIME_REPORT_ENA,
    LPHY_REQ_RFE_DL_CA_CONFIG_REPORT_ENA,
    LPHY_REQ_RFE_CC2CH_IDX_REPORT_ENA,
    LPHY_REQ_RFE_INFO_REPORT_ID,
}LPHY_REQ_RFE_INFO_ENUM;

typedef enum
{
    RFE_OM_SWITCH_OFF = LPHY_FALSE,
    RFE_OM_SWITCH_ON = LPHY_TRUE
}RFE_OM_SWITCH_ENUM;
typedef UINT16 RFE_OM_SWITCH_ENUM_UINT16;
typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16   enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16                      usReserved;
}LPHY_REQ_RFE_REPORT_ENA_STRU;

typedef enum
{
    RFE_OM_INFO_TYPE_L1C_ITF                     = 0,
    RFE_OM_INFO_TYPE_SLAVE_TIME_RECOVER,
    RFE_OM_INFO_TYPE_RFIN_DL_CH_GROUP_INFO,
    RFE_OM_INFO_TYPE_RFIN_DL_EVENT
}RFE_OM_INFO_TYPE_ENUM;
typedef UINT16 RFE_OM_INFO_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_CCA_CC_INVALID = 0,
    RFE_CCA_CC_PRIMARY ,
    RFE_CCA_CC_SECOND
}RFE_CCA_CC_TYPE_ENUM;

typedef UINT16 RFE_CCA_CC_TYPE_ENUM_UINT16;

typedef enum
{
    LPHY_RFE_PCC = 0,
    LPHY_RFE_SCC1,
    LPHY_RFE_SCC2,
    LPHY_RFE_SCC3,
    LPHY_RFE_INVALID_CC
}LPHY_RFE_CC_ENUM;

typedef UINT16 LPHY_RFE_CC_ENUM_UINT16;
typedef enum
{
    PA_LOW_LEVEL = 0,
    PA_MID_LEVEL,
    PA_HIGH_LEVEL,
    PA_LEVEL_BUTT
}PA_LEVEL_INDEX_ENUM;

typedef UINT16 PA_LEVEL_INDEX_ENUM_UINT16;
typedef UINT08 PA_LEVEL_INDEX_ENUM_UINT08;

typedef enum
{
    RFE_UL_PATH0 = 0,
    RFE_UL_PATH1 = 1
}RFE_UL_PATH_ENUM;
typedef UINT16 RFE_UL_PATH_ENUM_UINT16;

typedef enum
{
    RFE_SET_RX_3072_DELAY_TIME = 0,
    RFE_SET_RX_6144_DELAY_TIME,
    RFE_SET_TX_3072_DELAY_TIME,
    RFE_SET_TX_6144_DELAY_TIME,
    RFE_SET_BOTH_3072_DELAY_TIME,
    RFE_SET_BOTH_6144_DELAY_TIME,
}RFE_DELAYTIME_TYPE_ENUM;
typedef UINT16 RFE_DELAYTIME_TYPE_ENUM_UINT16;

enum RFE_SAMPLE_RATE_ENUM
{
    RFE_SAMPLE_RATE_7_68M = 0,
    RFE_SAMPLE_RATE_15_36M,
    RFE_SAMPLE_RATE_30_72M,
    RFE_SAMPLE_RATE_61_44M
};
typedef UINT16 RFE_SAMPLE_RATE_ENUM_UINT16;

typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16   enEnable;
    LPHY_CA_CC_ENUM_UINT16      enCcIndex;
    RFE_UL_PATH_ENUM_UINT16     enTxPath;
    PA_LEVEL_INDEX_ENUM_UINT08  enPaLevel;
    UINT08                      ucApcCodeLessThan20;
}LPHY_REQ_REF_FIX_UL_POWER_STRU;

/*LPHY_REQ_RFE_INFO_REPORT_ID*/
typedef struct
{
    RFE_OM_INFO_TYPE_ENUM_UINT16    enRfeInfoType;
    RFE_OM_SWITCH_ENUM_UINT16       enRfeOmSwitch;
}LPHY_REQ_RFE_INFO_ENA_STRU;
typedef struct
{
    UINT32                            ucValidflg:1;         /*��ǰָ���Ƿ���Ч*/
    UINT32                            ucExWFlg:1;           /*�Ƿ������չд���ͷ�ʽ,1��*/
    UINT32                            ucWatTime:8;          /*������ȴ�ʱ��*/
    UINT32                            ucSlaveid:4;          /*�豸USID*/
    UINT32                            ucMipiAddr:8;         /*��MIPI�豸�е�ƫ�Ƶ�ַ*/
    UINT32                            ucByteCnt:3;          /*�������չָ�ָ��CNT*/
    UINT32                            ucBbpMipiPin:3;
    UINT32                            ulRsv:4;
} NV_MIPI_CMD_CTRL_OM_STRU;/*Ҫ��NV�ж���Ľṹ��NV_MIPI_CMD_CTRL_STRU����һ��*/
typedef struct
{
    NV_MIPI_CMD_CTRL_OM_STRU            stMipiCtrl;

    UINT8                            ucCmdByte0;
    UINT8                            ucCmdByte1;
    UINT8                            ucCmdByte2;
    UINT8                            ucCmdByte3;
}LPHY_MIPIDEV_CMD_OM_STRU;/*Ҫ��NV�ж���Ľṹ��LPHY_MIPIDEV_CMD_STRU����һ��*/
typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16    enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
    UINT16   usReserved;
    /*Reg*/
    UINT8    ucBbpRegNum;
    UINT8    ucSsiRegNum;
    UINT8    ucMipiRegNum;
    UINT8    ucCtuIdx;
    UINT32   aulBbpAddr[RFE_OM_READREG_NUM];
    UINT32   aulSsiAddr[RFE_OM_READREG_NUM];
    NV_MIPI_CMD_CTRL_OM_STRU   astMipiCtrlInfo[RFE_OM_READREG_NUM];
}LPHY_REQ_RFE_REG_READ_ENA_STRU;
#if 0
/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_CNF_AFC_FIX_PDM_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_CNF, 0x1),

}LPHY_CNF_AFC_ENUM;

typedef struct
{
    UINT32                  ulMsgId;    /*1 CNF��ϢID*/
}LPHY_CNF_AFC_FIX_PDM_ENA_STRU;

#endif
/************************************************************
                           3. Sg���ݽṹ����
************************************************************/

/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_RFE_MBX                      = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_RFE_REG_READ,
    LPHY_TRACE_RFE_SCC_MBX,
    LPHY_TRACE_RFE_PCC_STATUS,
    LPHY_TRACE_RFE_SCC_STATUS,
    LPHY_TRACE_RFE_DLCH_STATUS,
    LPHY_TRACE_RFE_ULCH_STATUS,
    LPHY_TRACE_RFE_APC_PARA,

    LPHY_TRACE_RFE_UL_PARA,
    LPHY_TRACE_RFE_DELAY_TIME,
    LPHY_TRACE_RFE_IRAT_STATUS,
    LPHY_TRACE_RFE_CC2CH_IDX,
    LPHY_TRACE_RFE_NV,
    LPHY_TRACE_RFE_DL_CELLINFO,
    LPHY_TRACE_RFE_UL_CELLINFO,

    LPHY_TRACE_RFIN_EVT_RX_ON_CH0_RPT      = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_RFIN_EVT_RX_ON_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_OFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_AGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTRAFLAGON_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFLAGON_RPT,

    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_EX0_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_EX0_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_EX1_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_EX1_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_OFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_OFF_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_OFF_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_OFF_EX_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SHUTDOWN_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SHUTDOWN_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_EX0_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_EX0_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_EX1_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_EX1_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQON_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH1_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH2_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH3_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH2_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH3_RPT,
    LPHY_TRACE_RFIN_EVT_RX_IIP2_RPT,
    LPHY_TRACE_RFIN_EVT_MRX_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHB_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHCD_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHBCD_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHB_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHCD_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHBCD_RPT

}LPHY_TRACE_RFE_CTU_EVENT_ENUM;
typedef enum
{
    LPHY_TRACE_RFE_HI6360_BEFORE_CHANGEFRQ_EVT        = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x40),
    LPHY_TRACE_RFE_HI6360_AFTER_CHANGEFRQ_EVT

}LPHY_TRACE_RFE_HI6360_EVENT_ENUM;

/*L1C->L1B����ͨ����������*/
enum RFE_REQ_TYPE_ENUM
{
    LTE_RFE_REQ_INVALID = 0,                        /*RFE ������Ч*/
    LTE_RFE_BAND_SCAN_REQ,                          /*С������Ƶ��Ԥ����Ƶ���������֮һ������Ƶ��ʹ���20M/1.4M���󷵻�rssi*/
    LTE_RFE_INIT_CS_REQ,                            /*��ʼƵ��������Ƶǰ���л�*/
    LTE_RFE_INIT_PBCH_NCELL_BCCH_START_REQ,         /*��ʼ��㲥��������㲥 ��ʼ��MIB SIB��Ƶǰ���л�������AFC ��ʱ����*/
    LTE_RFE_NCELL_BCCH_RELEASE_REQ,                 /*��ʼ��㲥��������㲥�ͷţ��ڶ����������ͨ�������*/
    LTE_RFE_DL_PARA_CHANGE_REQ,                     /*����ͨ����ǰС��ϵͳ����������󣬽��漰����������������TDD UL/DL��� ������֡��ʽ�仯*/
    LTE_RFE_CAMP_REQ,                               /*פ������*/
//    LTE_RFE_NCELL_PBCH_PDSCH_REQ,                   /*����MIB�������*/
//    LTE_RFE_NCELL_2_MAIN_CELL_REQ,                  /*����SIB�������*/
    LTE_RFE_IDLE_2_CONN_REQ,                        /*��������̬����,ԭ��������ר��PDSCH�ŵ�ʱ����*/
//    LTE_RFE_TX_OPEN_REQ,                            /*��������̬����,ԭ�����н���PUSCH�ŵ�ʱ����*/
    LTE_RFE_INTER_MEAS_NO_GAP_REQ,                  /*IDLE̬��Ƶ��������*/
    LTE_RFE_INTER_MEAS_RELEAS_REQ,                  /*��Ƶ�����ͷź�GU occasion�ͷ�*/
    LTE_RFE_INTER_MEAS_GAP_REQ,                     /*����̬��Ƶ��������*/
    LTE_RFE_GU_OCCASION_REQ,                        /*GU occasion����*/
    LTE_RFE_HO_REQ                                 /*�л�����*/
};
typedef UINT16 RFE_REQ_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_NCBAND_0BAND = 0,
    RFE_NCBAND_1BAND,
    RFE_NCBAND_NBAND
}RFE_NCBAND_TYPE_ENUM;

typedef UINT16 RFE_NCBAND_TYPE_ENUM_UINT16;

typedef enum
{
    RFD_RX_ON_EVT = 0,
    RFD_RX_OFF_EVT,
    RFD_RX_SHUTDOWN_EVT,
    RFD_RX_FREQ_EVT,
    RFD_RX_AGC_EVT,
    RFD_TX_ON_EVT,
    RFD_TX_OFF_EVT,
    RFD_TX_SHUTDOWN_EVT,
    RFD_TX_APC_EVT,
    RFD_TX_FREQ_EVT,
    RFD_INTRA_FLAGON,
    RFD_INTER_FLAGON,
    RFD_DRV_EVT_BUTT
}RFD_DRV_EVT_ENUM;
typedef UINT16 RFD_DRV_EVT_ENUM_UINT16;
typedef enum
{
    SSI_RX_ON_EVT = 0,
    SSI_RX_OFF_EVT,
    SSI_RX_SHUTDOWN_EVT,
    SSI_RX_FREQ_EVT,
    SSI_RX_AGC_EVT,

    SSI_TX_ON_EVT,
    SSI_TX_OFF_EVT,
    SSI_TX_FREQ_EVT,
    SSI_TX_SWITCH_ON_EVT,
    SSI_TX_SHUTDOWN_EVT,
    SSI_TX_APC_EVT,

    SSI_EVT_BUTT
}RFD_SSI_EVT_ENUM;
typedef UINT16 RFD_SSI_EVT_ENUM_UINT16;
typedef enum
{
    MIPI_RX_ON_EVT = 0,

    MIPI_TX_ON_EVT,
    MIPI_TX_OFF_EVT,
    MIPI_TX_APC_EVT,

    MIPI_EVT_BUTT
}RFD_MIPI_EVT_ENUM;
typedef UINT16 RFD_MIPI_EVT_ENUM_UINT16;
typedef enum
{
    FPU_CC_TYPE_PCC = 0,
    FPU_CC_TYPE_CC1 ,
    FPU_CC_TYPE_CC2 ,
    FPU_CC_TYPE_CC3
}FPU_CC_TYPE_ENUM;

typedef  UINT16   RFE_FPU_CC_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_INVALID_CA = 0,
    RFE_INTER_BAND_CA ,
    RFE_INTRA_BAND_CONTIGOUS_CA ,
    RFE_INTRA_BAND_NONCONTIGOUS_CA
}RFE_CA_TYPE_ENUM;
typedef UINT16 RFE_CA_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_DL_SCELL_REQ = 0,
    RFE_UL_SCELL_REQ,
}RFE_SCELL_REQ_DLUL_ENUM;
typedef UINT8 RFE_SCELL_REQ_DLUL_ENUM_UINT08;

typedef enum
{
    RFE_CC_INVALID = 0,
    RFE_SINGLE_CC_ACT,
    RFE_CONTIGOUS_CA_ACT,
}RFE_ACT_CC_TYPE_ENUM;
typedef UINT16 RFE_ACT_CC_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_CC_NO_PROC = 0,
    RFE_1TO2_HOLD,
    RFE_2TO1_HOLD,
    RFE_1TO1_NO_PROC,
    RFE_2TO2_NO_PROC,
    RFE_ACT1_TO1_START,
    RFE_ACT1_TO2_START,
    RFE_ACT2_TO2_START,
    RFE_DEACT_STOP,
    RFE_ONLY_CHCHANGE,
}RFE_CC_PROC_TYPE_ENUM;
typedef UINT16 RFE_CC_PROC_TYPE_ENUM_UINT16;

typedef enum
{
    SCELL_OFF                  = 0,
    SCELL_CFG_INACTIVE,
    WAIT_SCELL_FRAME_HEAD_EXIST,
    SCELL_ACTIVE_ON,
    SCELL_MEAS_ON,
    SCELL_BOTH_ON
} RFE_SCELL_STATE_ENUM;
typedef  UINT16   RFE_SCELL_STATE_ENUM_UINT16;

typedef enum
{
    RFE_SCC_STATE_MOVE_NULL            = 0,
    RFE_SCC_OFF_TO_CFGINACTIVE,

    RFE_SCC_CFGINACTIVE_TO_OFF,
    RFE_SCC_CFGINACTIVE_TO_WAITFRMHEADEXIT,
    RFE_SCC_CFGINACTIVE_TO_MACACTIVEON,
    RFE_SCC_CFGINACTIVE_TO_MEASACTIVEON,
    RFE_SCC_CFGINACTIVE_TO_BOTHON,

    RFE_SCC_WAITFRMHEADEXIT_TO_OFF,
    RFE_SCC_WAITFRMHEADEXIT_TO_CFGINACTIVE,
    RFE_SCC_WAITFRMHEADEXIT_TO_MACACTIVEON,
    RFE_SCC_WAITFRMHEADEXIT_TO_MEASACTIVEON,
    RFE_SCC_WAITFRMHEADEXIT_TO_BOTHON,

    RFE_SCC_MACACTIVEON_TO_OFF,
    RFE_SCC_MACACTIVEON_TO_CFGINACTIVE,
    RFE_SCC_MACACTIVEON_TO_MEASACTIVEON,
    RFE_SCC_MACACTIVEON_TO_BOTHON,

    RFE_SCC_MEASACTIVEON_TO_OFF,
    RFE_SCC_MEASACTIVEON_TO_CFGINACTIVE,
    RFE_SCC_MEASACTIVEON_TO_MACACTIVEON,
    RFE_SCC_MEASACTIVEON_TO_BOTHON,

    RFE_SCC_BOTHON_TO_OFF,
    RFE_SCC_BOTHON_TO_CFGINACTIVE,
    RFE_SCC_BOTHON_TO_MACACTIVEON,
    RFE_SCC_BOTHON_TO_MEASACTIVEON,

}RFE_SCC_STATE_MOVE_ENUM;
typedef  UINT16  RFE_SCC_STATE_MOVE_ENUM_UINT16;

typedef enum
{
    RFE_SCC_FPU_FULL_CONFIG = 5,
    RFE_SCC_FPU_ONLY_TIMING_CONFIG
}RFE_SCC_FPU_CONFIG_ENUM;
typedef  UINT16  RFE_SCC_FPU_CONFIG_ENUM_UINT16;

typedef enum
{
	RFE_TIMING_SWITCH_INVALID = 0,
	RFE_TIMING_SWITCH_FROME_DEM,
	RFE_TIMING_SWITCH_FROME_CSU
}RFE_TIMING_SWITCH_ENUM;
typedef  UINT16  RFE_TIMING_SWITCH_ENUM_UINT16;

typedef enum
{
    RFE_OM_EMCS_REQ_BAND_SCAN               = 0,
    RFE_OM_EMCS_REQ_FREE_CELL_SEARCH ,
    RFE_OM_EMCS_REQ_INTER_MEAS,
    RFE_OM_EMCS_REQ_INTER_MEAS_FINISH,
    RFE_OM_EMCS_REQ_INTER_SRCH_FINISH,
    RFE_OM_EMCS_REQ_INTER_MEAS_RELEASE,
    RFE_OM_EMCS_REQ_GAP_INTER_MODE,
    RFE_OM_EMCS_REQ_W_OCCASION,
    RFE_OM_EMCS_REQ_G_RSSI_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_VERIFY_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_CONFIRM_OCCASION,
    RFE_OM_EMCS_REQ_OCCASION_RELEASE,
    RFE_OM_EMCS_REQ_SLAVE_OCCASION_REQ,
//#ifdef BALONGV7_FEATURE_LCS
    RFE_OM_EMCS_REQ_LCS_OCCASION_REQ
//#endif
}RFE_OM_EMCS_REQ_TYPE_ENUM;
typedef UINT16 RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_NORMAL_MODE = 0, /*����ҵ��ģʽ*/
    RFE_EQUIP_MODE,    /*װ��ģʽ*/
    RFE_EQUIP_CAL_MODE /*װ��У׼ģʽ*/
}RFE_WORK_MODE_ENUM;
typedef UINT16 RFE_WORK_MODE_ENUM_UINT16;

typedef enum
{
    RF_BAND_WIDTH_1D4M = 0,
    RF_BAND_WIDTH_3M,
    RF_BAND_WIDTH_5M,
    RF_BAND_WIDTH_10M,
    RF_BAND_WIDTH_15M,
    RF_BAND_WIDTH_20M,
    RF_BAND_WIDTH_30M,
    RF_BAND_WIDTH_40M,
    RF_BAND_WIDTH_BUTT
}RFE_RF_BAND_WIDTH_ENUM;

typedef  UINT16  RFE_RF_BAND_WIDTH_ENUM_UINT16;

typedef enum
{
    RFIN_SAMPLE_RATE_30_72M  =  0,
    RFIN_SAMPLE_RATE_15_36M,
    RFIN_SAMPLE_RATE_7_68M,
    RFIN_SAMPLE_RATE_61_44M
}RFIN_SAMPLE_RATE_ENUM;
typedef UINT16 LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16;

typedef enum
{
    BAND_NV_INTRA = 0,
    BAND_NV_INTER,
    BAND_NV_BUTT
}FE_BAND_NV_ENUM;
typedef UINT16  FE_BAND_NV_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_CFG = 0,
    RFIN_CH_CFGED,
    RFIN_CH_CFG_BUTT
}RFIN_CH_CFG_STAT_ENUM;
typedef UINT16 RFIN_CH_CFG_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_ACT,
    RFIN_CH_ACTED,
    RFIN_CH_ACT_BUTT
}RFIN_CH_ACT_STAT_ENUM;
typedef UINT16 RFIN_CH_ACT_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_COMB = 0,
    RFIN_CH_COMBED,
    RFIN_CH_COMB_BUTT
}RFIN_CH_COMB_STAT_ENUM;
typedef UINT16 RFIN_CH_COMB_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NOT_BAK = 0,
    RFIN_CH_BAKED,
    RFIN_CH_BAK_BUTT
}RFIN_CH_BAK_STAT_ENUM;
typedef UINT16 RFIN_CH_BAK_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_DL_INTRA_EVT = 0,
    RFIN_DL_INTER_EVT
}RFIN_DL_EVT_TYPE_ENUM;
typedef UINT16 RFIN_DL_EVT_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_1BAND_NV,
    RFE_NBAND_NV
}RFE_NV_TYPE_ENUM;
typedef UINT16 RFE_NV_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_TX_CLEAR_INVALID = 0,
    RFIN_TX_CLEAR_1CH,
    RFIN_TX_CLEAR_2CH
}RFIN_TX_CLEAR_IND_ENUM;
typedef UINT16 RFIN_TX_CLEAR_IND_ENUM_UINT16;

typedef enum
{
    RFIN_Rx_Downlink_SFM            = RFIN_Rx_Downlink,
    RFIN_Rx_DUMMY_SFM               = RFIN_Rx_DUMMY,
    RFIN_Rx_S_SFM                   = RFIN_Rx_S,
    RFIN_Rx_S_DUMMY_SFM             = RFIN_Rx_S_DUMMY,
    RFIN_Tx_PUXCH_SFM               = RFIN_Tx_PUXCH,           /*PUSCH/PUCCH/PUSCH&PUCCH Long*/
    RFIN_Tx_PRACH_SFM               = RFIN_Tx_PRACH,           /*PRACH 1~3 Long */
    RFIN_Tx_DUMMY_SFM               = RFIN_Tx_DUMMY,            /*no send*/
    RFIN_Tx_PUXCH_SHORTEN_SFM       = RFIN_Tx_PUXCH_SHORTEN,     /*PUSCH/PUCCH/PUSCH&PUCCH Short*/
    RFIN_Tx_PRACH_SHORTEN_SFM       = RFIN_Tx_PRACH_SHORTEN,           /*PRACH 1~3 Short */
    RFIN_Tx_SRS_ONLY_SFM            = RFIN_Tx_SRS_ONLY,            /*SRS On U Sfrm*/
    RFIN_Tx_PUXCH_SRS_SFM           = RFIN_Tx_PUXCH_SRS,            /* PUSCH&SRS/PUCCH&SRS/PUSCH&PUCCH&SRS*/
    RFIN_S_SRS_BOTH_SFM             = RFIN_S_SRS_BOTH,            /* 2 SRS On S Sfrm*/
    RFIN_S_SRS_LAST_SFM             = RFIN_S_SRS_LAST,            /*2nd SRS On S Sfrm*/
    RFIN_S_SRS_SecondLAST_SFM       = RFIN_S_SRS_SecondLAST,            /*1ST */
    RFIN_S_PRACH4_SFM               = RFIN_S_PRACH4,
    RFIN_S_PRACH4_DUMMY_SFM         = RFIN_S_PRACH4_DUMMY
}RFE_SFM_TYPE_ENUM;
typedef UINT32 RFE_SFM_TYPE_ENUM_UINT32;

typedef enum
{
    RFIC_IDLE_TYPE     = RFIC_IDLE,
    RFIC_STANDBY_TYPE  = RFIC_STANDBY,
    RFIC_RXON_TYPE     = RFIC_RXON,
    RFIC_TXON_TYPE     = RFIC_TXON,
    RFIC_STATE_BUTT
}RFIC_STATE_TYPE_ENUM;
typedef UINT16 RFIC_STATE_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_IDLE_TO_STANDBY = ((RFIC_IDLE << 8)    | RFIC_STANDBY),
    RFIN_STANDBY_TO_IDLE = ((RFIC_STANDBY << 8) | RFIC_IDLE),
    RFIN_IDLE_TO_RXON    = ((RFIC_IDLE << 8)    | RFIC_RXON),
    RFIN_STANDBY_TO_RXON = ((RFIC_STANDBY << 8) | RFIC_RXON),
    RFIN_RXON_TO_IDLE    = ((RFIC_RXON << 8)    | RFIC_IDLE),
    RFIN_RXON_TO_STANDBY = ((RFIC_RXON << 8)    | RFIC_STANDBY),
    RFIN_RXON_TO_TXON    = ((RFIC_RXON << 8)    | RFIC_TXON),
    RFIN_IDLE_TO_TXON    = ((RFIC_IDLE << 8)    | RFIC_TXON),
    RFIN_STANDBY_TO_TXON = ((RFIC_STANDBY << 8) | RFIC_TXON),
    RFIN_TXON_TO_IDLE    = ((RFIC_TXON << 8)    | RFIC_IDLE),
    RFIN_TXON_TO_STANDBY = ((RFIC_TXON << 8)    | RFIC_STANDBY),
    RFIN_TXON_TO_RXON    = ((RFIC_TXON << 8)    | RFIC_RXON),
    RFIN_RX_AGC_TO_AGC,
    RFIN_TX_APC_TO_APC_PRACH,
    RFIN_TX_APC_TO_APC_PUSCH_PUCCH,
    RFIN_TX_APC_TO_APC_SRS,
    RFIN_NO_CHANGE       =  0xFFFF
}RFIN_STATE_MOVE_TYPE_ENUM;
typedef UINT16 RFIN_STATE_MOVE_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_UL_PRACH_CH    = 0,
    RFIN_UL_PUSCH_PUCCH_CH,
    RFIN_UL_SRS_CH,
    RFIN_UL_CH_BUTT
}RFIN_UL_CH_TYPE_ENUM;

typedef UINT16 RFIN_UL_CH_TYPE_ENUM_UINT16;

typedef struct
{
    UINT8 ucUlRfChIdx;       //puschʹ�ܱ�־
    UINT8 ucRsv;
    UINT16 usApcCode;
    UINT16 usPaLevel;
    UINT16 usAptPdmVal;
    UINT16 enUlCcIdx;
    RFIN_UL_CH_TYPE_ENUM_UINT16  enUlChType;
} LTE_RFIN_UL_APC_INFO_STRU;

/*LPHY_TRACE_RFE_CTU_LTE_INT0_EVT ~ LPHY_TRACE_RFE_CTU_GSM_INT6_EVT*/
typedef struct
{
    UINT32  ulCtuInfo[6];
}LPHY_TRACE_RFE_CTU_EVENT_STRU;
typedef struct
{
    UINT32  ulHi6360Info[6];
}LPHY_TRACE_RFE_HI6360_EVENT_STRU;

typedef struct
{
    UINT16                              usGUOccasionLen;      /*GU occasion����*/
    UINT8                               ucGUOccasionType;     /*GU occasion����*/
    UINT8                               ucWDchSwfreqFlag;     /*W����̬Ƶ�����ָʾ*/
}LTE_RFE_IRAT_CONFIG_STRU;
typedef struct
{
    UINT16                              usUlFreqInfo;         /*����Ƶ��*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth;            /*������ϵͳ����*/
    UINT16                              usUlBandNum;          /*����BAND*/
    UINT8                               ucUlConfigValidFlg;   /*����������Ч��ʶ*/
    UINT8                               ucRsv;
}LTE_RFE_UL_CELLINFO_STRU;
/*L1C->L1B����ͨ������ṹ�����Ͷ���*/
typedef struct{
    LTE_CELL_INFO_STRU                  stCellDlInfo;         /*С�����в���*/
    LTE_DUAL_PSS_SCAN_INFO_STRU         stDualPssScanInfo;     /*����ɨƵ����*/
    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;         /*��Ƶǰ����������*/
    UINT16                              usUlFrequency;        /*����Ƶ��*/
    LTE_BAND_WIDTH_ENUM_UINT16          enUlBw;               /*������ϵͳ����*/
    RFE_CCA_CC_TYPE_ENUM_UINT16         enCcaCcType;
    LPHY_RFE_CC_ENUM_UINT16             en2ndCcIdx;
    UINT16                              usPdm;                /*AFC PDMֵ����ʼС������,��ѡ���л�ʱ��ֵ��*/
    UINT32                              ulFramePosition;      /*С��֡��ʱ*/
    UINT16                              usUlBandNum;          /*����BAND*/
    UINT16                              usGUOccasionLen;      /*GU occasion����*/
    UINT8                               ucUlConfigValidFlg;   /*����������Ч��ʶ*/
    UINT8                               ucGUOccasionType;     /*GU occasion����*/
    UINT8                               ucWDchSwfreqFlag;     /*W����̬Ƶ�����ָʾ*/
    UINT8                               ucRsv;
} LTE_RFE_REQ_STRU;
typedef struct
{
    UINT32   ulAddr;
    UINT32   ulData;
}RFE_REG_STRU;
typedef struct
{
    UINT8    ucBbpRegNum;
    UINT8    ucSsiRegNum;
    UINT8    ucMipiRegNum;
    UINT8    ucReserved;
    UINT32   aulSsiReg[RFE_OM_READREG_NUM];
    LPHY_MIPIDEV_CMD_OM_STRU    astMipiReg[RFE_OM_READREG_NUM];
    RFE_REG_STRU                astBbpReg[RFE_OM_READREG_NUM];
}LPHY_TRACE_RFE_REG_READ_STRU;

typedef struct{
    UINT32                          *pBandNvDestBuf;    /*NV TCM addr*/
    UINT32                          *pBandNvSrcBuf;     /*NV DDR addr*/
    FE_BAND_NV_ENUM_UINT16          usBandType;         /*NV Load type*/
    UINT16                          usBand;
    UINT16                          usValidFlag;
    UINT16                          usReserved;
} LTE_RFE_NV_TRACE_STRU;
typedef struct
{
    RFE_FPU_CC_TYPE_ENUM_UINT16 enFpuCcIdx;
    UINT16  usReserved;
    UINT8   ucRecvAntNumFpu;
    UINT8   ucTransAntNumFpu;
    UINT8   ucDwptsLen;
    UINT8   ucSampingRate;
}RFE_FPU_CELL_CONFIG_STRU;
/*L1C->L1B����ͨ������ṹ�����Ͷ���*/

typedef struct{
    UINT16                          usSingleIntraNvBand;
    UINT16                          usSingleInterNvBand;
} RFE_SINGLE_BAND_NV_INFO_STRU;

typedef struct
{
    LTE_CELL_INFO_STRU                  stCellDlInfo;         /*С�����в���*/
    UINT16                               usULInfoCfgFlg;
    UINT16                              usUlFreqInfo;       /*����Ƶ��*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth ;     /*���д������*/
    UINT16                              usUlBandNum;        /*����BAND*/
    RFE_CA_TYPE_ENUM_UINT16             enCaType;
    LPHY_RFE_CC_ENUM_UINT16             enUl2ndCcIdx;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enUlCcaCcType;

    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;         /*��Ƶǰ����������*/

    LPHY_RFE_CC_ENUM_UINT16             enCcIdx;
    UINT8                               ucTxAntNumforAgc;     /*�͸�AGC����������Ŀ��0��ʾä��*/
    RFE_SCELL_REQ_DLUL_ENUM_UINT08      enDlUlFlag;
    UINT32                              ulFramePosition;      /*С��֡��ʱ*/
} LTE_RFE_SCC_REQ_STRU;

/*RFIN EVT report*/
/*RFIN EVT report*/
typedef struct
{
    UINT32 ulEventTimeRef        : 3;
    UINT32 ulRsv0                : 13;
    UINT32 ulEventTime           : 16;
}RFE_RFIN_EVENT_TIME_CFG_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU stRfinEvtTime;
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16 enRfinStatMoveType;    //��8bit��ʾRFIC��ʷ״̬����8bit��ʾRFICĿ��״̬
    UINT16 usRsv;
}RFE_RFIN_EVENT_CFG_INFO_STRU;

typedef struct
{
    UINT32 ulSsiCfgFlag           : 1;
    UINT32 ulRsv0                 : 15;
    UINT32 ulSsiCfgTimeOffset     : 16;

    UINT32 ulSsiNum               : 8;
    UINT32 ulRsv2                 : 8;
    UINT32 ulSsiBufferBase        : 8;
    UINT32 ulRsv1                 : 8;

}RFE_RFIN_SSI_CFG_STRU;

typedef struct
{
    UINT32 ulMipiCfgFlag           : 1;
    UINT32 ulRsv0                  : 15;
    UINT32 ulMipiCfgTimeOffset     : 16;

    UINT32 ulMipiNum               : 9;
    UINT32 ulRsv2                 : 7;
    UINT32 ulMipiBufferBase        : 9;
    UINT32 ulRsv1                 : 7;

}RFE_RFIN_MIPI_CFG_STRU;

typedef struct
{
    UINT32 ulFpuDataEn          : 2;
    UINT32 ulRsv4               : 2;
    UINT32 ulAdiuEn             : 2;
    UINT32 ulRsv3               : 2;
    UINT32 ulAbbRxbEn           : 2;
    UINT32 ulRsv2               : 2;
    UINT32 ulAbbRxaEn           : 2;
    UINT32 ulRsv1               : 2;
    UINT32 ulRsv0               : 16;
}RFE_RFIN_RX_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulLnaEnSel            : 1;
    UINT32 ulRsv1                : 3;
    UINT32 ulLnaEnIdx            : 2;
    UINT32 ulRsv0                : 26;
}RFE_RFIN_LNA_EN_CFG_STRU;

typedef struct
{
    UINT32 ulAntSelFlag            : 1;
    UINT32 ulRsv1                  : 3;
    UINT32 ulAntIdx                : 4;
    UINT32 ulRsv0                  : 8;
    UINT32 ulAntCfgTimeOffset      : 16;
}RFE_RFIN_ANT_EN_CFG_STRU;

typedef struct
{
    UINT32 ulEventEnFlag           : 1;
    UINT32 ulRsv0                  : 31;
}RFE_RFIN_EVENT_EN_CFG_STRU;

typedef struct
{
    UINT32 ulLnaModeSel           : 1;
    UINT32 ulRsv1                 : 15;
    UINT32 ulLnaModeIdx           : 2;
    UINT32 ulRsv0                 : 14;
}RFE_RFIN_LNA_MODE_CFG_STRU;

typedef struct
{
    UINT32 ulAbbCfgVld          : 2;
    UINT32 ulRsv0               : 30;
}RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulFpuGapEn            : 2;
    UINT32 ulRsv5                : 2;
    UINT32 ulFpuInterIntra       : 2;
    UINT32 ulRsv4                : 2;
    UINT32 ulIntersysIngapPreInd : 2;
    UINT32 ulRsv3                : 2;
    UINT32 ulIntrasysValid       : 2;
    UINT32 ulRsv2                : 2;
    UINT32 ulIntrasysValidDelay  : 2;
    UINT32 ulRsv1                : 2;
    UINT32 ulInterFlagEn         : 2;
    UINT32 ulRsv0                : 10;
}RFE_RFIN_INTER_FLAG_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulValidFlag             : 1;
    UINT32 ulResv1                 : 3;
    UINT32 ulDbbRate               : 2;
    UINT32 ulResv0                 : 10;
    UINT32 ulDbbRateTimeOffset     : 16;
}RFE_RFIN_DBB_RATE_CFG_STRU;

typedef struct
{
    UINT32 ulAbbTxEn            : 2;
    UINT32 ulRsv4               : 2;
    UINT32 ulETActEn            : 2;
    UINT32 ulRsv3               : 2;
    UINT32 ulRsv2               : 4;
    UINT32 ulAPTPdmEn           : 2;
    UINT32 ulRsv1               : 2;
    UINT32 ulRsv0               : 16;
}RFE_RFIN_TX_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulPaModeSel            : 1;
    UINT32 ulRsv1                 : 15;
    UINT32 ulPaModeIdx            : 2;
    UINT32 ulRsv0                 : 14;
}RFE_RFIN_PA_MODE_CFG_STRU;

typedef struct
{
    UINT32 ulPaEnSel              : 1;
    UINT32 ulRsv1                 : 3;
    UINT32 ulPaEnIdx              : 2;
    UINT32 ulRsv0                 : 26;
}RFE_RFIN_PA_EN_CFG_STRU;

typedef struct
{
    UINT32 ulPdmModuSel           :1;
    UINT32 ulRsv0                 :15;
    UINT32 ulPdmModu              :16;
}RFE_RFIN_PDM_MODU_CFG_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_SWITCH_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU         dtLnaModeCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_DVTY_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU         dtLnaModeCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_SHUTDOWN_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_DBB_RATE_CFG_STRU          stDbbRateCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTRA_FREQ_STRU;

/*inter event*/
typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_DBB_RATE_CFG_STRU          stDbbRateCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTER_FREQ_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_INTER_FLAG_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTER_FLAG_ON_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_INTER_FLAG_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTAR_FLAG_ON_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU          stLnaModCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_RX_AGC_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    UINT32                             usRsv;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_SWITCH_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_CLEAR_TX_SWITCH_STRU;
typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PDM_MODU_CFG_STRU         stPdmModuCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_AGC_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
	UINT32                             usRsv;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_SHUTDOWN_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_RX_IIP2_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    UINT32                              aulRsv[5];
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_MRX_STRU;
typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
       UINT32                             ulRsv;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PDM_MODU_CFG_STRU         stPdmModuCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_APC_STRU;

typedef struct
{
    LTE_CELL_INFO_STRU                  stCellDlInfo;
    UINT16                              usULInfoCfgFlg;     /*����������Ϣ��Ч��־*/
    UINT16                              usUlFreqInfo;       /*����Ƶ��*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth ;     /*���д������*/
    UINT16                              usUlBandNum;        /*����BAND*/


    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;       /*��Ƶǰ����������*/
    UINT8                               ucTxAntNumforAgc;   /*��ʹ�ã�ʹ��PCC��*/
    UINT8                               ucUlTransAntNum;    /*UE ���з���������Ŀ*/
    UINT32                              ulSccFramePos;      /*Scell С��֡��ʱ,����ʹ�õ� 0.25 ts*/
    UINT32                              ulSccFramePosOld;   /*scell frame head isn't exist, use pcell as old  0.25 ts*/

    RFE_FPU_CC_TYPE_ENUM_UINT16         en1stFpuCcIdx;
    RFE_FPU_CC_TYPE_ENUM_UINT16         en2ndFpuCcIdx;

    RFE_CA_TYPE_ENUM_UINT16             enCaType;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enCcaCcType;
    LPHY_RFE_CC_ENUM_UINT16             en2ndCcIdx;

    RFE_ACT_CC_TYPE_ENUM_UINT16         enActCcType;

    RFE_CC_PROC_TYPE_ENUM_UINT16        enCcProType;
    UINT8                               ucOldFreqSwitchInd;
    UINT8                               ucNewFreqSwitchInd;

    RFE_CA_TYPE_ENUM_UINT16             enUlCaType;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enUlCcaCcType;

    LPHY_RFE_CC_ENUM_UINT16             enUl2ndCcIdx;

    UINT8                               ucRxClearRfChIdx;  //rx clear
    UINT8                               ucTxClearRfChIdx[2]; //tx clear
    UINT8                               ucCaWithPccFlag;
    UINT16                              usCcCenterFreq;      /*cc center  freq*/

    RFE_RF_BAND_WIDTH_ENUM_UINT16       enCcBw;
    RFE_SCELL_STATE_ENUM_UINT16         enScellState;

    RFE_SCC_STATE_MOVE_ENUM_UINT16      enScellMoveState;

    UINT16                              usDlIntraBandIdx;

    UINT16                              usUlIntraBandIdx;
    UINT8                               ucCfgInActiveReq;
    UINT8                               ucDeCfgInActiveReq;

    UINT8                               ucMacActiveReq;
    UINT8                               ucMacInActiveReq;
    UINT8                               ucMeasActiveReq;
    UINT8                               ucMeasInActiveReq;

    UINT8                               ucOtdoaActiveReq;
    UINT8                               ucOtdoaInActiveReq;

    UINT8                               ucMeasValidFlag;
    UINT8                               ucOtdoaValidFlag;

    /*align*/
    UINT8                               ucFpuActFlag;        /*for fpu sym10 config  */
    UINT8                               ucFpuInActFlag;      /*for fpu sym10 config  */
	UINT8                               ucReSyncFlag;
    UINT8                               ucRfChIdx;

    UINT8                               ucDlNewCfgInd;
    UINT8                               ucUlNewCfgInd;

    UINT16                              usDlRfPathIndex;
    UINT08                              ucRficIdx;
    UINT08                              ucUlRficIdx;
    UINT16                              usUlRfPathIndex;
    UINT08                              ucRfRxSel;         /*rfic abcdѡ��*/
    UINT08                              ucRsv[3];
    //UINT8                               ucNonCcInActDelay;   /*for scc fpu delay next subfrm sym6 to deactivate*/
    UINT8                               ucScellActive;       /*dem  active deactive, С�������ѵ�֡ͷΪtrue*/
    /*align*/
    UINT8                               ucFrmHeadExist;      /*frame head exist or not*/
    UINT8                               ucMacTriWaitFlag;
    UINT8                               ucMeasTriWaitFlag;
    RFE_SCC_FPU_CONFIG_ENUM_UINT16      enSccFpuCfgMode;

    LTE_TDD_SUBFRAME_TYPE_ENUM_UINT16   usFpuNextSfrmType;

	INT32                               lUlTpaDlt;
	RFE_TIMING_SWITCH_ENUM_UINT16       enTimeSwitchType;
	LPHY_RFE_CC_ENUM_UINT16             enCcIdx;
}RFE_STATUS_SCC_STRU;
typedef struct
{
    UINT16 usTxActInd                   : 1;
    UINT16 usTxEx0ActInd                : 1;
    UINT16 usTxEx1ActInd                : 1;
    UINT16 usTxDeActInd                 : 1;
    UINT16 usTxExDeActInd               : 1;
    UINT16 usCfgInd                     : 1;
    UINT16 usDeCfgInd                   : 1;
    UINT16 usRxClearInd                 : 1;
    UINT16 usFreqSwtichInd              : 1;
    UINT16 usTxApcInd                   : 1;
    UINT16 usTxApcEx0Ind                : 1;
    UINT16 usTxApcEx1Ind                : 1;
    UINT16 usRsv                        : 4;
	UINT16 usReserved;
}RFE_RFIN_UL_CH_ACTION_IND_STRU;

typedef struct
{
    UINT16 usActInd                 : 1;
    UINT16 usDeActInd               : 1;
    UINT16 usDeActExInd             : 1;
    UINT16 usCfgInd                 : 1;
    UINT16 usDeCfgInd               : 1;
    UINT16 usCombInd                : 1;
    UINT16 usDeCombInd              : 1;
    UINT16 usFlagOnInd              : 1;
    UINT16 usFreqSwtichInd          : 1;
    UINT16 usCtuUncloseInd          : 1;  //0��ʾҪ�ر�
    UINT16 usSlaveModeInd           : 1;  // LTE slave mode, enter into occasion
    UINT16 usGuFlagOnInd            : 1;
	UINT16 usRficClearInd			: 1;  //�峡��־
    UINT16 usRsv                    : 3;
	UINT16 usReserved;
}RFE_RFIN_DL_CH_ACTION_IND_STRU;

typedef struct
{
    UINT8                                     ucRfChIdx;      /* ͨ��ID */
    UINT8                                     ucRficIdx;      /* ͨ��rfic */
    UINT8                                     ucClearDlChIdx;  /* RxClearOff ��Ϊ��Ӧ��DL CH */
    UINT8                                     ucRfRxSel;      /* ��Ӧ��rx */
    UINT16                                    usUlRfChIndex;    /* ͨ��Band��Ӧ��RF CH*/
    UINT16                                    usRsv;

    RFIN_CH_CFG_STAT_ENUM_UINT16              enRfCfgStat;    /* ͨ������״̬ */
    RFIN_CH_ACT_STAT_ENUM_UINT16              enRfActStat;    /* ͨ������״̬ */

    RFE_WORK_MODE_ENUM_UINT16                 usWorkMode;    /*��������ģʽ������װ��ģʽ*/
    UINT8                                     ucCtuChIdx;      /*��Ӧ�����е�ChIdx*/
    UINT8                                     ucCAInd;         /*ͨ����Ӧ��CA�Ƿ��Ǽ���״̬*/

    LPHY_RFE_CC_ENUM_UINT16                   en1stCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   en2ndCcIdx;

    RFE_SCC_STATE_MOVE_ENUM_UINT16            en1stCcMoveState;
    RFE_SCC_STATE_MOVE_ENUM_UINT16            en2stCcMoveState;

    UINT16                                    usFreqInfo;               /*Ƶ��*/
    UINT16                                    usBandNum;                /*Band*/

    RFE_RF_BAND_WIDTH_ENUM_UINT16             enUlBandWidth;            /*����*/ //senUlBandWidth
    LTE_FRAME_TYPE_ENUM_UINT16                enDuplexMode;             /*֡����:FDD or TDD*/

    LTE_CP_TYPE_ENUM_UINT16                   enCpType;                 /*cp����*/
    UINT8                                     ucTransAntNum;            /* ����������Ŀ */
    UINT8                                     ucPaOnFlag;        /* 1--immediate en, 0--buffer time */

    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16       enSpecSubframeCfg;        /* ������֡��� */
    RFE_NV_TYPE_ENUM_UINT16                   enNvType;                 /* NV���ͣ�ΪRFE_1BAND_NV ����RFE_NBAND_NV */

    //NV_SINGLE_BAND_FE_PARA_STRU               *pstNvParaPoint;          /* RFE_1BAND_NV */
    //NV_BAND_FE_UL_PARA_STRU                   *pstUlChPara;
    UINT32                                    *pstUlChPara;
    //NV_NCCA_UL_BAND_PARA_STRU                 *pstNcCaUlBandNvPoint;    /* RFE_NBAND_NV */
    UINT32                                    *pstNcCaUlBandNvPoint;    /* RFE_NBAND_NV */
    //NV_NCCA_UL_COMM_PARA_STRU                 *pstNcCaUlCommNvPoint;
    UINT32                                    *pstNcCaUlCommNvPoint;
    //NV_NCCA_DL_BAND_PARA_STRU                 *pstNcCaDlBandNvPoint;
    UINT32                                    *pstNcCaDlBandNvPoint;
    RFE_SFM_TYPE_ENUM_UINT32                  ulNext2SfrmType;          /* �ٶ���ǰ��֡ΪN��֡��N+2��֡���� */
    RFE_SFM_TYPE_ENUM_UINT32                  ulNext1SfrmType;          /* �ٶ���ǰ��֡ΪN��֡��N+1��֡���� */
    //RFE_RFIN_EVENT_TIME_CFG_STRU              stChActEvtTime; /*�¼���Ч����*/
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16          enRfinStatMoveType;
	UINT16                                    usReserved;
    RFE_RFIN_UL_CH_ACTION_IND_STRU            stChActionInd;   /* ����ͨ����Ϊָʾ */
}RFE_UL_RFIN_CHAN_INFO_STRU;
typedef struct
{

    UINT8                                     ucRfChIdx;       /* ͨ��ID */
    UINT8                                     ucCombRfChIdx;   /* ��ͨ��ID */
    UINT16                                    usDlRfChIndex;    /* ͨ��Band��Ӧ��RF CH*/
    UINT08                                    ucRficIdx;
    UINT08                                    ucRfRxSel;         /*rfic abcdѡ��*/
    UINT16                                    usRsv;
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16          enRfinStatMoveType;
    UINT16                                    usReserved;

    RFIN_CH_COMB_STAT_ENUM_UINT16             enRfCombStat;    /* ͨ����״̬ */
    RFIN_CH_CFG_STAT_ENUM_UINT16              enRfCfgStat;     /* ͨ������״̬ */
    RFIN_CH_ACT_STAT_ENUM_UINT16              enRfActStat;     /* ͨ������״̬ */
    RFIN_CH_BAK_STAT_ENUM_UINT16              enChBakStat;     /* ͨ������״̬ */
    RFIN_DL_EVT_TYPE_ENUM_UINT16              enRfinEvtType;   /*INter��Intra��Ƶ�¼�*/
    RFIN_TX_CLEAR_IND_ENUM_UINT16             enTxClearInd;             /* TxClearOff ��Ϊָʾ */

    /* TxClearOff ��Ϊ��Ӧ��Ul CH, ���������MIMO�����Ӧ��2��Ul CH��2��RFIC �ϣ���Ҫ��Ӧ2��UL CH */
    UINT8                                     ucClearUlChIdx[2];
    UINT8                                     ucOnlyCloseLineCtrlFlag;  /* ��Ƶ�����������ؽ����߿�*/
    UINT8                                     ucCAInd;                 /*ͨ����Ӧ��CA�Ƿ��Ǽ���״̬*/

    UINT8                                     ucPrimaryChFlag;         /*���ز�����ͨ����Ч��־λ*/
    UINT8                                     ucFddForcedFlag;
    RFE_WORK_MODE_ENUM_UINT16                 usWorkMode;

    LPHY_RFE_CC_ENUM_UINT16                   en1stCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   en2ndCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   enDeAct1stCcIdx;    /* ��ǰ��֡��һ��ȥ������ز����� */
    LPHY_RFE_CC_ENUM_UINT16                   enDeAct2ndCcIdx;  /* ��ǰ��֡�ڶ���ȥ������ز����� */

    RFE_SCC_STATE_MOVE_ENUM_UINT16            en1stCcMoveState;
    RFE_SCC_STATE_MOVE_ENUM_UINT16            en2stCcMoveState;
    UINT16                                    usFreqInfo;               /*Ƶ��*/
    UINT16                                    usBandNum;                /*Band*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16             enDlBandWidth;            /*����*/
    LTE_FRAME_TYPE_ENUM_UINT16                enDuplexMode;             /*֡����:FDD or TDD*/

    LTE_CP_TYPE_ENUM_UINT16                   enCpType;                 /*cp����*/
    UINT8                                     ucRecvAntNum;             /* ����������Ŀ */
    UINT8                                     ucActRecvAntNum;

    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16       enSpecSubframeCfg;        /* ������֡��� */
    RFE_NV_TYPE_ENUM_UINT16                   enNvType;                 /* NV���ͣ�ΪRFE_1BAND_NV ����RFE_NBAND_NV */

    UINT32                                    *pstDlChPara;
    //NV_BAND_FE_DL_PARA_STRU                   *pstDlChPara;
    UINT32                                    *pstNcCaDlBandNvPoint;        /* RFE_NBAND_NV */
    //NV_NCCA_DL_BAND_PARA_STRU                 *pstNcCaDlBandNvPoint;        /* RFE_NBAND_NV */
    UINT32                                    *pstNcCaDlCommNvPoint;         /*NCCA DL Band ��������*/
    //NV_NCCA_DL_COMM_PARA_STRU                 *pstNcCaDlCommNvPoint;         /*NCCA DL Band ��������*/
    UINT32                                    *pstNcCaUlBandNvPoint;        /*NCCA UL ��Band  ˽�в���*/
    //NV_NCCA_UL_BAND_PARA_STRU                 *pstNcCaUlBandNvPoint;        /*NCCA UL ��Band  ˽�в���*/
    RFE_SFM_TYPE_ENUM_UINT32                  ulNextSfrmType;           /* �ٶ���ǰ��֡ΪN��֡��N+1��֡���� */
    RFE_SFM_TYPE_ENUM_UINT32                  ulCurrSfrmType;           /* ��ǰ��֡���ͣ�N��֡���� */

    RFE_RFIN_DL_CH_ACTION_IND_STRU            stChActionInd;            /* ����ͨ����Ϊָʾ */

}RFE_RFIN_CHAN_INFO_STRU;

typedef struct
{
    UINT16  usCcIndex;
    RFE_DELAYTIME_TYPE_ENUM_UINT16  enType;
	UINT16  usRxChDlyTime;                  /*����ͨ���ӳٲ���,T8,�տڵ�������Ӳ�������ӳ�*/
	UINT16  usTxChDlyTime;                  /*����ͨ���ӳٲ���,tul*/
}RFE_CH_DELAY_TIMER_STRU;
/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
/************************************************************
                           7. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_IND_RFE_L1C_DEM_CMD_ID               = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_IND, 0x0),
    LPHY_IND_RFE_L1C_EMCS_CMD_ID,
    LPHY_IND_RFE_TIME_RCVR_IND_ID,

    LPHY_IND_RFE_RFIN_DL_CH_GROUP0_IND_ID,
    LPHY_IND_RFE_RFIN_DL_CH_GROUP1_IND_ID,
    LPHY_IND_RFE_RFIN_DL_CH_GROUP2_IND_ID,

    LPHY_IND_RFE_RFIN_EVNET_RX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_ON_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_OFF_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_AGC_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_CLEAR_TX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_SHUTDOWN_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTRA_FREQ_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_EX0_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_EX1_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_OFF_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_EX0_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_EX1_ID,
    LPHY_IND_RFE_RFIN_EVNET_CLEAR_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_SHUTDOWN_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_RX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FLAG_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FLAG_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FREQ_ID
}LPHY_IND_RFE_L1C_CMD_ENUM;

typedef UINT16 LPHY_IND_RFE_L1C_CMD_ENUM_UINT16;


enum RFE_OM_DEM_REQ_TYPE_ENUM
{
    RFE_OM_DEM_REQ_CAMP_MAINCELL           =0,
    RFE_OM_DEM_REQ_NCELL_BCCH_START,
    RFE_OM_DEM_REQ_NCELL_BCCH_FINISH,
    RFE_OM_DEM_REQ_SERV_BCCH_START,
    RFE_OM_DEM_REQ_SERV_BCCH_FINISH,
    RFE_OM_DEM_REQ_DL_SYSPARA_CHANGE,
    RFE_OM_DEM_REQ_HANDOVER_BLIND,
    RFE_OM_DEM_REQ_HANDOVER_NON_BLIND
};
typedef UINT16 RFE_OM_DEM_REQ_TYPE_ENUM_UINT16;


typedef struct
{
    UINT16                              usFreqInfo;
    UINT16                              usCellID;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    LTE_CP_TYPE_ENUM_UINT16             enCPType;
    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16 enSpecSFCfg;
    LTE_TDD_UD_CFG_ENUM_UINT16          enULDLCfg;
    UINT32                              ulFramePosition;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    UINT8                               ucTxAntennaNum;
}RFE_OM_DL_CFG_PARA_STRU;

/*LPHY_IND_RFE_L1C_DEM_CMD_ID*/
typedef struct
{
    RFE_OM_DEM_REQ_TYPE_ENUM_UINT16         enFreqSwitchType;
    UINT8                                   ucIratHoFlag;      /*IRAT -> LTE�л���ʶ��1��Ч*/
    UINT8                                   ucRsvd;
    RFE_OM_DL_CFG_PARA_STRU                 stDLCfgPara;
}RFE_OM_DEM_REQ_STRU;

/*LPHY_IND_RFE_L1C_EMCS_CMD_ID*/
typedef struct
{
    UINT16                              usInterFreq;
    UINT16                              usRsvd;
    RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16    enFreqSwitchType;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    UINT16                              usOccasionInms;
    UINT8                               ucWFrequencySwitchFlag;
}RFE_OM_EMCS_REQ_STRU;


typedef struct{
    union {
        struct{
            UINT32      gFnLow      :   11;//[0,10]  0-1325
            UINT32      gFnHigh     :   11;//[11,21] 0-2047
        } u;
        UINT32 bits;
    } gfn;

    UINT16 usGsmQb;         /*0-4999*/
    UINT8  aucRsv[2];
}RFE_OM_GSM_TIMING_STRU;

typedef union{
    struct{
        UINT32      clockInChip             :   4;//[0,3] 0-15
        UINT32      chip                    :   12;//[4,15] 0-2559
        UINT32      slot                    :   4;//[16,19] 0-14
        UINT32      sfn                     :   12;//[20,31] 0-4095
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_TIMING_UINION;

typedef union{
    struct{
        UINT32      chip                    :   12;//[0,11] 0-2559
        UINT32      slot                    :   4;//[12,15] 0-14
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_SYSABS_UINION;


typedef union{
    struct{
        UINT32      ts                      :   15;//[0,14]  0-30719
        UINT32      sbfn                    :   4;//[15,18]  0-9
        UINT32      sfn                     :   10;//[19,28] 0-1023
    } u;
    UINT32 bits;
}RFE_OM_LTE_TIMING_UINION;

typedef union{
    struct{
        UINT32      cycle                   :   3; //[0,2]
        UINT32      rsv1                    :   1; //[3]
        UINT32      ts                      :   15;//[4,18]  0-30719
        UINT32      rsv2                    :   1; //[19]
        UINT32      sbfn                    :   4; //[20,23] 0-9
    } u;
    UINT32 bits;
}RFE_OM_LTE_ABS_TIMING_UINION;

typedef struct
{
    UINT32 ulSfn;     //��֡��
    UINT32 ulChip;    //1/32chip Ϊ��λ
}RFE_OM_TDS_TIMING_STRU;


typedef struct{
    RFE_OM_LTE_ABS_TIMING_UINION   uLteTiming;
    RFE_OM_WCDMA_TIMING_UINION     uWcdmaTiming;
    RFE_OM_WCDMA_SYSABS_UINION     uWcdmaSysAbsOffs;
    RFE_OM_GSM_TIMING_STRU         stGsmTiming;
    RFE_OM_TDS_TIMING_STRU         stTdsTiming;
    UINT32                         ulCtuDsp;
    UINT8                          ucValidFlg;
    UINT8                          aucRsv[3];
}RFE_OM_IRAT_TIMING_STRU;

/*LPHY_IND_RFE_TIME_RCVR_IND_ID*/
typedef struct{
    RFE_OM_IRAT_TIMING_STRU         stOldTime;
    RFE_OM_IRAT_TIMING_STRU         stNewTime;
    RFE_OM_LTE_ABS_TIMING_UINION    stRecoveredLteTime;
    UINT32                          ulDeltaT;
}RFE_OM_SLAVE_TIME_RECOVER_IND_STRU;
typedef struct
{
    //RFIN_CH0_RAGC_TIME_UNION  stEvtTimeCfg;
	UINT16 usRxABGain;
	UINT16 usRxCDGain;
	UINT16 usRxADcoc;
	UINT16 usRxBDcoc;
	UINT16 usRxCDcoc;
	UINT16 usRxDDcoc;
    UINT16 usRfAIIP2;
    UINT16 usRfBIIP2;
    UINT16 usRfCIIP2;
    UINT16 usRfDIIP2;
    RFE_WORK_MODE_ENUM_UINT16 usWorkMode;
    UINT16 usAgcDcocMode;//added liliuwei00279357,0:agc dcoc�����ã�1: ����agc 2:����dcoc  ����ֵ���Ƿ�  20150306
    //UINT16 usRsv;
} LTE_RFD_RX_AGC_CFG_STRU;

typedef struct
{
    //RFIN_CH0_RON_TIME_UNION             stEvtTimeCfg;           /*��Чʱ��ʹ���ʱ��*/
    UINT16                              usDlRfChIndex;          /*��bandʹ�õ�RFͨ����*/
    UINT16                              usFreqInfo;             /*Ƶ��*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16       enBandWidth;            /*����*/
    //LTE_FRAME_TYPE_ENUM_UINT16          enDuplexMode;           /*FDD/TDD*/
    LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16   enSampleRate;           /*������*/
}LTE_RFD_RX_CH_CFG_STRU;
typedef struct
{
    UINT08                              ucReserved;                 /*CTUͨ����*/
    UINT08                              ucUlRfChIndex;          /*��bandʹ�õ�RFͨ����*/
    UINT16                              usFreqInfo;             /*Ƶ��*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16       enBandWidth;            /*����*/
    //LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16   enSampleRate;           /*������*/
    UINT16 usApcCode;
    UINT16 usAptPdmVal;
    UINT16 usRsv;
}LTE_RFD_TX_CFG_STRU;

typedef struct
{
    RFD_MIPI_EVT_ENUM_UINT16            enMipiEvt;
    UINT16                              usMipiAddrOffSet;           /*MIPI Bufferƫ�Ƶ�ַ*/

    NV_BAND_UL_MIPI_CTRL_STRU    	    *pstUlMipiConfig; 		 /*����ͨ��MIPI  ��ز���*/
	NV_BAND_DL_MIPI_CTRL_STRU    	    *pstDlMipiConfig;     /*����ͨ��MIPI  ��ز���*/

    //RFE_NV_TYPE_ENUM_UINT16             enNvType;               /* NV���ͣ�ΪRFE_1BAND_NV ����RFE_NBAND_NV */
    PA_LEVEL_INDEX_ENUM_UINT16          enPaLevel;
    UINT16                              usPaTime;
    UINT16                              usMipiTime;
    UINT16                              usReserved;
}RFD_MIPI_CFG;
typedef struct
{
 	UINT08                              ucActRecvAntNum;            /*����������*/
    UINT08                              ucRficClearInd;                 /*CTUͨ����*/
    UINT16                              usReserved;
    LTE_RFD_RX_AGC_CFG_STRU             stRxAgcCfg;                 /*AGC���RFD�¼�����*/
    LTE_RFD_RX_CH_CFG_STRU              stRxChCfg;                  /*ͨ�����RFD�¼�����*/
}LTE_RFD_RX_CFG_STRU;
typedef struct
{
    UINT32                              ulBbpBufAddr;               /*RFIN���¼����üĴ�����ַ*/
    UINT32                              ulSsiTime;                /*SSI �����ӳ�ʱ��*/
    UINT32                              ulAntTime;                /*���߿����ӳ�ʱ��*/
    UINT32                              ulOmMsgId;                  /*RFIN�¼���ν�ɲ�ID*/
    UINT32                              ulEvtTimeCfg;           /*��Чʱ��ʹ���ʱ��*/

    UINT16                              usBandNum;                  /*band ��*/
    RFD_DRV_EVT_ENUM_UINT16             enDrvEvt;                    /*RFD�¼�*/

    RFD_SSI_EVT_ENUM_UINT16             enSsiEvt;
    UINT16                              usSsiBufOffset;             /*SSI Bufferƫ�Ƶ�ַ*/

    LTE_FRAME_TYPE_ENUM_UINT16          enDuplexMode;               /*FDD/TDD*/
    RFE_WORK_MODE_ENUM_UINT16           enWorkMode;

    RFIN_STATE_MOVE_TYPE_ENUM_UINT16    enRfinStatMoveType;
    UINT08                              ucFddForcedFlag;
    UINT08                              ucReserved;

    UINT08                              ucPrimaryChFlag;
    UINT08                              ucMipiCfgEn;                /*�Ƿ�����MIPI*/
    UINT08                              ucCtuChIdx;
    UINT08                              ucFreqSwtichInd;
    UINT08                              ucRficIdx;
    UINT08                              ucRfRxSel;
    UINT08                              ucRsv[2];
    LTE_RFD_RX_CFG_STRU                 stRxCfg;
    LTE_RFD_TX_CFG_STRU                 stTxCfg;                  /*ͨ�����RFD�¼�����*/
    RFD_MIPI_CFG                        stMipiCfg;
}RFD_EVT_PARA_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RFE_OM_DEF_H__ */


