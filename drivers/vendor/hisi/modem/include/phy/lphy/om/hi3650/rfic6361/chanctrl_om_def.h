

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

#ifndef __CHANCTRL_OM_DEF_H__
#define __CHANCTRL_OM_DEF_H__


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
    LPHY_REQ_CHANCTRL_TM_REQUEST           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_CHANCTRL_CP_REQUEST,
    /* BEGIN: Added by yushujing, 2013/8/28   PN:chan_om*/
    LPHY_REQ_CHANCTRL_CELL_STAT_REQUEST,
    /* END:   Added by yushujing, 2013/8/28 */

    LPHY_REQ_TAS_STAT_REQUEST,
    LPHY_REQ_DPDT_STAT_REQUEST,

}LPHY_CHANCTRL_REQ_ENUM;

typedef UINT16 LPHY_CHANCTRL_REQ_ENUM_UINT16;


typedef struct
{
    OM_REQ_ENABLE_ENUM enOmTmSwitch;
    OM_REQ_ENABLE_ENUM enOmCpSwitch;
}LPHY_OM_REQ_CHANCTRL_STRU;
/* BEGIN: Added by yushujing, 2013/8/28   PN:chan_om*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32 ulRptChanPeriod;
}LPHY_OM_REQ_CHANCTRL_STAT_ENA_STRU;
typedef struct
{
    LPHY_OM_REQ_CHANCTRL_STAT_ENA_STRU stRptChanEna;
    UINT32 ulRptPeriodCnt;
}LPHY_OM_REQ_CHANCTRL_STAT_STRU;
/* END:   Added by yushujing, 2013/8/28 */

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32             ulRptTasPeriod;
}LPHY_OM_REQ_TASCTRL_STAT_ENA_STRU;
typedef struct
{
    LPHY_OM_REQ_TASCTRL_STAT_ENA_STRU stRptTasEna;
    UINT32                            ulRptTasPeriodCnt;
}LPHY_OM_REQ_TAS_STAT_ENA_STRU;
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDpdtEna;
    UINT16             usRev;
}LPHY_OM_REQ_DPDT_STAT_ENA_STRU;

/************************************************************
                    2. CNF���ݽṹ����
************************************************************/


/************************************************************
                    3. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_IND_CHANCTRL_TM_REPORT           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_CHANCTRL_CP_REPORT,
    /* BEGIN: Added by yushujing, 2013/8/28   PN:chan_om*/
    LPHY_IND_CHANCTRL_CELL_STAT,
    /* END:   Added by yushujing, 2013/8/28   PN:chan_om*/

	LPHY_IND_TAS_ASU_STAT,
	LPHY_IND_TAS_DPDT_SWITCH_STAT,
	LPHY_IND_TAS_STATE_CHANGE_STAT,
	LPHY_IND_TAS_GIVE_STAT,
	LPHY_IND_TAS_GIVE_DCH,
	LPHY_IND_TAS_GIVE_IDLE,
	LPHY_IND_TAS_BS_RSSI_STAT,
	LPHY_IND_DPDT_STAT,
	LPHY_IND_TAS_ESTIMATE_N1_STAT,  //N1
    LPHY_IND_TAS_ESTIMATE_N2_STAT,  //N2
    LPHY_IND_TAS_ESTIMATE_N3_STAT,  //N3
    LPHY_IND_TAS_PROTECT_STAT,      //�벻Ҫ��������ĸ��궨�壬N1��N2��N3��PROTECT
}LPHY_CHANCTRL_IND_ENUM;

typedef UINT16 LPHY_CHANCTRL_IND_ENUM_UINT16;

typedef struct
{
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_IND_CHANCTRL_STRU;
/* BEGIN: Added by yushujing, 2013/8/28   PN:chan_om*/
enum LPHY_CHANCTRL_BAND_WIDTH_ENUM
{
    LPHY_BAND_WIDTH_6RB              = 0,                /* ����Ϊ6RB */
    LPHY_BAND_WIDTH_15RB,                                /* ����Ϊ15RB */
    LPHY_BAND_WIDTH_25RB,                                /* ����Ϊ25RB */
    LPHY_BAND_WIDTH_50RB,                                /* ����Ϊ50RB */
    LPHY_BAND_WIDTH_75RB,                                /* ����Ϊ75RB */
    LPHY_BAND_WIDTH_100RB,                               /* ����Ϊ100RB */
    LPHY_BAND_WIDTH_BUTT
};
typedef UINT8 LPHY_CHANCTRL_BAND_WIDTH_ENUM_UINT8;

enum LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM
{
    LPHY_LTE_MODE_TYPE_FDD                = 0,                             /* LTE FDD ��ʽ */
    LPHY_LTE_MODE_TYPE_TDD                = 1,                             /* LTE TDD ��ʽ */
    LPHY_LTE_MODE_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM_UINT8;

enum LPHY_CHANCTRL_CONTINUOUS_CA_ENUM
{
    LPHY_NON_CONTINUOUS_CA                = 0,                             /* LTE FDD ��ʽ */
    LPHY_CONTINUOUS_CA                    = 1,                             /* LTE TDD ��ʽ */
    LPHY_CA_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_CONTINUOUS_CA_ENUM_UINT8;

enum LPHY_CHANCTRL_CROSS_CA_ENUM
{
    LPHY_NON_CROSS_CA                = 0,                             /* LTE FDD ��ʽ */
    LPHY_CROSS_CA                    = 1,                             /* LTE TDD ��ʽ */
    LPHY_CROSS_CA_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_CROSS_CA_ENUM_UINT8;

typedef struct
{
    UINT16 ucCellId;
    UINT16 usFreqInfo;

    UINT8 ucBandInd;
    LPHY_CHANCTRL_BAND_WIDTH_ENUM_UINT8 ucBandWidth;
    LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM_UINT8 ucLteModeType;
    UINT8 ucTmMode;

    UINT8 ucCellIndex;
    UINT8 ucRsv;
    UINT16 usRsv;
}LPHY_OM_CHANCTRL_CELL_STAT_STRU;

typedef struct
{
    LPHY_CHANCTRL_CROSS_CA_ENUM_UINT8 ucCrossCa;
    UINT8 ucScellCifPresent;
    UINT8 ucPdschStart;
    LPHY_CHANCTRL_CONTINUOUS_CA_ENUM_UINT8 ucContiCa;
}LPHY_OM_CHANCTRL_CELL_CA_STAT_STRU;

typedef struct
{
    LPHY_OM_CHANCTRL_CELL_STAT_STRU astCellStat[2];
    LPHY_OM_CHANCTRL_CELL_CA_STAT_STRU stCaStat;
}LPHY_OM_IND_CHANCTRL_STAT_STRU;
/* END:   Added by yushujing, 2013/8/28   PN:chan_om*/
/************************************************************
                    4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_CHACNTRL_PBCH_SETUP           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_CHACNTRL_PDSCH_BCCH_SETUP,
    LPHY_TRACE_CHACNTRL_PDSCH_PCH_SETUP,
    LPHY_TRACE_CHANCTRL_PDSCH_RACH_SETUP,
    LPHY_TRACE_CHANCTRL_PDSCH_DSCH_SETUP,
    LPHY_TRACE_CHANCTRL_SCELL_PDSCH_DSCH_SETUP,
    LPHY_TRACE_CHANCTRL_PBCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_BCCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_PCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_RACH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_DSCH_RELEASE,
    LPHY_TRACE_CHANCTRL_SCELL_PDSCH_DSCH_RELEASE,
    LPHY_TRACE_CHACNTRL_CAMPED_ON_MAIN_CELL,
    LPHY_TRACE_CHANCTRL_HANDOVER,
    LPHY_TRACE_CHANCTRL_SI_CONFIG,
    LPHY_TRACE_CHANCTRL_C_RNTI_CONFIG,
    LPHY_TRACE_CHANCTRL_TC_RNTI_CONFIG,
    LPHY_TRACE_CHANCTRL_TC_RNTI_TO_C_RNTI,
    LPHY_TRACE_CHANCTRL_PCH_STOP_BY_NC_BCH,
    /* BEGIN: Added by yushujing, 2012/1/5   PN:ANR_MOD*/
    LPHY_TRACE_CHANCTRL_ANR_READY,
    LPHY_TRACE_CHANCTRL_ANR_START,
    LPHY_TRACE_CHANCTRL_ANR_HOLD,
    LPHY_TRACE_CHANCTRL_ANR_TIME_OK,
    /* END:   Added by yushujing, 2012/1/5 */
    LPHY_TRACE_CHANCTRL_BLIND_HANDOVER,
    LPHY_TRACE_CHANCTRL_RELEASE_ALL,
    LPHY_TRACE_CHANCTRL_CHANNEL_RECONFIG,
    LPHY_TRACE_CHANCTRL_INITIAL_CELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_NEIGHBOUR_CELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_MAINCELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_INITIAL_CELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_NEIGHBOUR_CELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_MAINCELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_TRANSMISSION_MODE_UPDATA,
    LPHY_TRACE_CHANCTRL_CALLING_RFE_CHANGE,
    /* END:   Added by sunyanjie, 2012/3/20 */
    /* BEGIN: Added by yushujing, 2013/8/29   PN:chan_om*/
    LPHY_TRACE_CHANCTRL_SCELL_ACT,
    LPHY_TRACE_CHANCTRL_SCELL_INACT,
    /* END:   Added by yushujing, 2013/8/29   PN:chan_om*/

}LPHY_CHANCTRL_TRACE_ENUM;

typedef UINT16 LPHY_CHANCTRL_TRACE_ENUM_UINT16;

typedef struct
{
    UINT16      usSysFrmNum;    /*ϵͳ֡��*/
    UINT16      usSubFrmNum;    /*��֡��*/
    UINT16      usSymbNum;      /*��ǰ������*/
    UINT16      usReserved;
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_TRACE_CHANCTRL_STRU;

/************************************************************
                    5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_ERROR_CHACNTRL_UL_MAILBOX_FEEDBACK_FAIL         = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_CHACNTRL_SEARCH_CELL_FROM_CSLIST_FAIL,
    LPHY_ERROR_CHACNTRL_SERVE_CELL_STATE_ERROR,
    LPHY_ERROR_CHANCTRL_SETUP_TOO_MANY_CHANNELS,
    LPHY_ERROR_CHANCTRL_CANNOT_FIND_THE_SPECIAL_CHANNEL,
    LPHY_ERROR_CHANCTRL_TPC_RNTI_TYPE_ERROR,
    LPHY_ERROR_CHANCTRL_PRIMITIVE_PARA_ERROR,
    LPHY_ERROR_CHANCTRL_TIMING_START_ERROR,
    LPHY_ERROR_CHANCTRL_TIMING_STOP_ERROR,
    LPHY_ERROR_CHANCTRL_GET_TIMING_CELL_ERROR,
    LPHY_ERROR_CHANCTRL_GET_TIMING_NOTREADY_ERROR,
    LPHY_ERROR_CHANCTRL_BGS_PDS_BCH_CHANNEL_SETUP,
    LPHY_ERROR_CHANCTRL_BGS_PBCH_CHANNEL_SETUP,
    LPHY_ERROR_CHANCTRL_BGS_PCH_CHANNEL_SETUP,
#ifdef TLPHY_FEATURE_DSDS
    LPHY_ERROR_CHACNTRL_NO_RF_FAIL,
#endif
}LPHY_CHANCTRL_ERROR_ENUM;

typedef UINT32 LPHY_CHANCTRL_ERROR_ENUM_UINT32;

typedef struct
{
    UINT16      usSysFrmNum;    /*ϵͳ֡��*/
    UINT16      usSubFrmNum;    /*��֡��*/
    UINT16      usSymbNum;      /*��ǰ������*/
    UINT16      usReserved;
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_ERROR_CHANCTRL_STRU;

typedef UINT8 TAS_NEW_STATE_ENUM_UINT8;

/*���������л�ʱ��������������ֵ OM*/
typedef struct _ASU_DPDT_SWITCH_STRU_{
    INT32        lGiveConnRsrp0;
    INT32        lGiveConnRsrp1;

    INT32        lGiveIdleRsrp0;
    INT32        lGiveIdleRsrp1;
}ASU_DPDT_SWITCH_STRU;

/*����֡Ƶ���ϱ���TAS TRACE����Ҫ�ϱ���ǰ״̬�����о���ʵʱ״̬*/
typedef struct _TAS_ASU_STATE_OM_STRU_{
    UINT32                     ulRsv3;
    TAS_NEW_STATE_ENUM_UINT8   enTasNewState;      //��ǰLTE ASU����״̬
    TAS_NEW_STATE_ENUM_UINT8   enIdleLastHappyState;
    UINT16                     usCurrNGI_Sinr;     //idle̬�о�Ϊgood��sinr���ޣ���ͬ

    UINT16                     usCurrNPI_Sinr;
    UINT16                     usCurrNGI_Rsrp;

    UINT16                     usCurrNPI_Rsrp;
    TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //LTE ASUZ״̬ת��ǰ�ľ�״̬
    UINT8                      ucInitPrachState;

    UINT16                     usPrachFailNum;     //��ǰ��������ʧ�ܵĴ���
    UINT16                     usCurrNGC;          //��ǰ�����о�ΪGOOD�Ĵ���

    UINT16                     usCurrNPC;          //��ǰ�����о�ΪPOOR�Ĵ���
    UINT16                     usRsv2;

    ASU_DPDT_SWITCH_STRU       stIdleConnSubPara;
}TAS_ASU_STATE_OM_STRU;

typedef struct _TAS_ASU_DATA_OM_STRU_{
	TAS_ASU_STATE_OM_STRU stTasState;
	UINT32                ulDpdtCurrState;
	UINT32                ulRsv;
}TAS_ASU_DATA_OM_STRU;

typedef struct _TAS_DPDT_SWITCH_STRU_{
	ASU_DPDT_SWITCH_STRU stTasDpdtStru;

    UINT32               ulDpdtCurrState;
    UINT32               ulBlankType;
    UINT32               ulRsv;
}TAS_DPDT_SWITCH_STRU;

typedef struct
{
    UINT16  usMsgID;//����PHY���Բ�һ��
	UINT16	usRatMode;//�μ�ԭ�и���ģʽ�Ķ���
	UINT16	usDpdtState;//0ֱͨ,1����
	INT16	ssAntValueMain;// �л����������߽����ź�����ֵ,����RSSI/RSCP/RSRP
	INT16	ssSwitchDelta;// �л�����ʱ���ּ�����Delta
	UINT16	usCdmaCtrlFlag;// ����CDMA�����л���� 1: ��ҿ�, 0: ����ҿ�
}LTE_OM_DPDT_STATE_IND_STRU;
/*����IDLE GOOD/POOR CONN GOOD/POOR״̬��״̬����ʱ���ϱ��¾�״̬��dpdt״̬*/
typedef struct _ASU_STATE_STRU_{
    UINT32       ulTasNewState;
	UINT32       ulTasOldState;
	UINT32       ulDpdtCurrState;
	UINT32       ulRsv0;
	UINT32       ulRsv1;
}ASU_STATE_STRU;

/*�ϱ�LTEɨƵ�׶�����RSSI*/
typedef struct _TAS_BS_RSSI_OM_STRU_{
    SINT16       ssMaxRssi;
	UINT16       usRsv;
}TAS_BS_RSSI_OM_STRU;

/*TAS200 ����̬�յ��Ĳ���ģ���������������ֵ���������������߼����źŽϺõ�����*/
typedef struct _ASU_GIVE_RSRP_STRU_{
    INT32       slTasAnt0;
	INT32       slTasAnt1;
    UINT32      ulDpdtCurrState;	//��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    INT32       slTasAnt0Filter;
	INT32       slTasAnt1Filter;
	INT32       slTasAntDelta;
    UINT32      ulCnt;
    UINT32      ulRsv;
}ASU_GIVE_RSRP_STRU;

//����̬�ϱ�����PROTECT״̬ʱ������״̬
typedef struct _ASU_TAS_HYST_STRU_{
    UINT32      ulDpdtCurrState; //��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32      ulRsv;
}ASU_TAS_HYST_STRU;

/*idle̬ASU�յ����������������ϱ���OM*/
typedef struct _ASU_GIVE_IDLE_STRU_{
    UINT32                     ulRsv3;

    TAS_NEW_STATE_ENUM_UINT8   enTasNewState;
    UINT8                      ucRsv;
    UINT16                     usCurrNGI_Sinr;

    UINT16                     usCurrNPI_Sinr;
    UINT16                     usCurrNGI_Rsrp;

    UINT16                     usCurrNPI_Rsrp;
    TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //LTE ASUZ״̬ת��ǰ�ľ�״̬
    UINT8                      ucInitPrachState;
}ASU_GIVE_IDLE_STRU;

typedef struct _ASU_GIVE_IDLE_OM_STRU_{
    ASU_GIVE_IDLE_STRU stGiveIdle;
    INT32              lRsrpAnt0;
    INT32              lRsrpAnt1;
    INT32              lRsrpUse;
    INT32              lSinrUse;

    UINT32             ulDpdtCurrState;
    UINT32             ulRsv;
}ASU_GIVE_IDLE_OM_STRU;

/*DCH̬ASU�յ����������������ϱ���OM*/
typedef struct _ASU_GIVE_DCH_OM_STRU_{
    INT32         slDchNewState;
    INT32         slDchOldState;

    UINT16        usCurrNGC;
    UINT16        usCurrNPC;
    UINT8         ucDrxValidFlag;
    UINT8         ucRsv0;
    UINT16        usRsv1;
    INT32         lRsrpAnt0;
    INT32         lRsrpAnt1;
    INT32         lRsrpUse;
    INT32         lSinrUse;

    UINT32        ulDpdtCurrState;
    UINT32        ulRsv;
}ASU_GIVE_DCH_OM_STRU;
/*TAS OM REPORT end k3v3+tas*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHANCTRL_OM_DEF_H__ */

