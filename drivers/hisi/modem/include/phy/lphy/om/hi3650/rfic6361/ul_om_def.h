

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

#ifndef __UL_OM_DEF_H__
#define __UL_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*����TDD ģʽ���յ����������֡��Ŀ*/
#define UL_TDD_MAX_DL_SUBFRAME_NUM 9
/* BEGIN: Added by yushujing, 2012/8/14   PN:V7R2_MODIFY*/
#define UL_MAX_SUBFRAME_NUM 10
/* END:   Added by yushujing, 2012/8/14   PN:V7R2_MODIFY*/
#define UL_Pusch_Code_Rate     930
#define UL_MAX_PWR (INT16)23
#define UL_MIN_PWR (INT16)(-40)

#define PWR_VALID(sPwr) ((sPwr >= UL_MIN_PWR)&&(sPwr <= UL_MAX_PWR))

#define UL_OM_RPT_PERIOD 1000

/* BEGIN: Added by xueqiuyan, 2012/6/5   PN:POWER_OM*/

#define POWER_INVALID_VALUE 0x7f

/* END:   Added by xueqiuyan, 2012/6/5 */

/* BEGIN: Added by xueqiuyan, 2012/9/7   PN:CMCC_DT*/

#define DT_INVALID_VALUE 0x7f
#define UL_OM_DT_RPT_PERIOD 200

/* END:   Added by xueqiuyan, 2012/9/7 */

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_UL__
{
    LPHY_REQ_UL_BASIC_INFO              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_UL_RANDOM_ACCESS_INFO      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x2),
    LPHY_REQ_UL_CTRL_INFO               =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x3),
    LPHY_REQ_UL_ACK_INFO                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x4),
    LPHY_REQ_UL_STAT_INFO               =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x5),
    LPHY_REQ_UL_CAPTURE_INFO            =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x6),
    LPHY_REQ_UL_UCI_TEST                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x7),
    LPHY_REQ_UL_POWER_CONFIG            =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x8),
    LPHY_REQ_UL_PHR_INFO                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x9),

    LPHY_REQ_UL_SCHEDUL_STATIC_INFO     =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xa),
    LPHY_REQ_UL_HARQBLER_INFO           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xb),
    LPHY_REQ_UL_PD_INFO                 =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xd)
}LPHY_REQ_MSGID_UL_ENUM;

/*****************************************************************************
 ö����    : UL_OM_ACTIVE_FLG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����OM�����־
*****************************************************************************/
enum UL_OM_ACTIVE_FLG_ENUM
{
    UL_OM_DEACTIVE = 0,
    UL_OM_ACTIVE
};
typedef UINT16 UL_OM_ACTIVE_FLG_ENUM_UINT16;

typedef struct __LPHY_REQ_UL_BASIC_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usReportPeriod;
}LPHY_REQ_UL_BASIC_INFO_STRU;

typedef struct __LPHY_REQ_UL_RANDOM_ACCESS_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_REQ_UL_RANDOM_ACCESS_INFO_STRU;

typedef struct __LPHY_REQ_UL_CTRL_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usUciBitMap;
}LPHY_REQ_UL_CTRL_INFO_STRU;

typedef struct __LPHY_REQ_UL_ACK_INFO_STRU_
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsvd;
}LPHY_REQ_UL_ACK_INFO_STRU;

typedef struct __LPHY_REQ_UL_STAT_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usBitMap;
    UINT32 ulStaRptTyp;
}LPHY_REQ_UL_STAT_INFO_STRU;

typedef struct __LPHY_REQ_UL_CAPTURE_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usBitMap;
}LPHY_REQ_UL_CAPTURE_INFO_STRU;


/*ACK����ָʾö�ٽṹ*/
enum UL_CODE_IND_ENUM
{
    SINGLE_WORD = 0,
    DOUBLE_WORD,
    INVALID_WORD
};
typedef UINT16 UL_CODE_IND_ENUM_UINT16;

/*ACK��������ö�ٽṹ*/
enum UL_SCHED_TYPE_ENUM
{
    NON_PERSISTENT = 0,                    /*��̬*/
    PERSISTENT,
    INVALID_SCHED                          /*�뾲̬*/
};
typedef UINT16 UL_SCHED_TYPE_ENUM_UINT16;

/*���н��TPC����ö�ٽṹ*/
enum UL_TPC_TYPE_ENUM
{
    DCI3_3A = 0,                           /*DCI3/3A����TPC*/
    DCIX,                                  /*��������TPC*/
    DCI_TPC_N,                            /*����ȷ��n1��Դ������TPC*/
    INVALID_DCI
};
typedef UINT16 UL_TPC_TYPE_ENUM_UINT16;

/*TPC��ֵö�ٽṹ*/
enum UL_TPC_ENUM
{
    TPC_0 = 0,
    TPC_1,
    TPC_2,
    TPC_3,
    INVALID_TPC
};
typedef UINT16 UL_TPC_ENUM_UINT16;

/*ACK����ö�ٽṹ*/
enum UL_ACK_ENUM
{
    NACK = 0,
    ACK,
    DTX,
    INVALID_ACK
};
typedef UINT16 UL_ACK_ENUM_UINT16;

/*Beging :dongning add For V7R2*/
enum UL_CHANNEL_SELECT_ENUM
{
    UL_CHANNEL_PUSCH = 0,
    UL_CHANNEL_PUCCH,
    UL_CHANNEL_INVALID
};
typedef UINT16 UL_CHANNEL_SELECT_ENUM_UINT16;
/*End :dongning add For V7R2*/

typedef struct
{
    UL_TPC_ENUM_UINT16         enTPC;
    UL_TPC_TYPE_ENUM_UINT16    enTPCType;
    UL_SCHED_TYPE_ENUM_UINT16  enSchedType;
    UL_CODE_IND_ENUM_UINT16    enCodeInd;
    UL_ACK_ENUM_UINT16         enAckCode1;
    UL_ACK_ENUM_UINT16         enAckCode2;
    UINT16                     usNcce;
    UINT16                     usDAI;
    UINT16                     usRecFrame;
    UINT16                     usRecSubFrame;
}UL_OM_ACK_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_CQI_REPORT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMCQI�ϱ���Ϣ�ṹ
*****************************************************************************/
#if 0
typedef struct
{
    UINT16  usPeriodORAperiodInd;   /*-1:��Ч���;0:����CQI����;1:������CQI����*/
    UINT16  usSFN;                  /*CQI�����͵�֡��*/
    UINT16  usSubFrame;             /*CQI�����͵���֡��*/
    UINT8   ucRIinfo;               /*RI��Ϣ0 ��Ч��1 ��ʾRI Ϊ1��2��ʾRIΪ2������ֵ����*/
    UINT8   ucPMILength;            /*����PMI���泤��,��λbit, for dem*/
    UINT8   ucPMINum;               /*����PMI����,dor dem*/
    UINT8   ucCQILength;            /*CQI���泤��,��λbit,for ul*/
    UINT16  usRev;
    UINT32  aulPMIReport[2];        /*����PMI����,for dem*/
    UINT32  aulCQIReport[4];        /*CQI����*/
}UL_OM_CQI_REPORT_INFO_STRU;
#endif

typedef struct
{
    /*�����Ӧ��֡����֡��*/
    UINT16  usSFN;                  /*CQI�����͵�֡��*/
    UINT16  usSubFrame;             /*CQI�����͵���֡��*/

    /*������ģ��ķ��ͱ���*/
    UINT16  usPeriodORAperiodInd;   /*0:��Ч���;1:����CQI����;2:������CQI����*/
    UINT8   ucRIinfo;               /*RI��Ϣ0 ��Ч��1 ��ʾRI Ϊ1��2��ʾRIΪ2������ֵ����*/
    UINT8   ucCQILength;            /*CQI���泤��,��λbit,for ul*/
    UINT32  aulCQIReport[4];        /*CQI����*/

    /*�����ģ��ı���*/
    UINT8   ucPmiValid;             /*PMI�Ƿ���Ч���*/
    UINT8   ucSubbandNum;           /*�Ӵ�����*/
    UINT8   ucSubbandWidth;         /*�Ӵ���С*/
    UINT8   ucPMIValue[25];         /*PMIֵ*/

}UL_OM_CQI_REPORT_INFO_STRU;


typedef struct __LPHY_REQ_UL_UCI_TEST_STRU__
{
    UINT16 usSubFrame;     /*�ڴ�����һ��֡����*/
    UINT16 usBitMap;       /*bit0:   0:��С��ACK��Ϣ��Ч;1:��С��ACK��Ϣ��Ч
                             bit1:   0:CQI��Ϣ��Ч;1:CQI��Ϣ��Ч
                             bit2:   0:SR��Ϣ��Ч; 1:SR��Ϣ��Ч
                             bit3:   0:PUSCH��Ч; 1:PUSCH��Ч
                             bit4:   0:��С��ACK��Ϣ��Ч;1:��С��ACK��Ϣ��Ч
                             */

    UINT16 usAckInfoNum;   /*ACK��Ϣ����*/
    UINT16 usCqiPucchResIdx;  /*CQI��Դ����*/
    UINT16 usAnAndCqiValidFlg;
    UINT16 usSpsAckCount;
    UINT16 usAckNoDTX;
    UINT16 usAckLastRecIdx;
    UL_OM_ACK_INFO_STRU astAckInfo[4];
    UL_OM_CQI_REPORT_INFO_STRU stCqiInfoStru;
}LPHY_REQ_UL_UCI_TEST_STRU;

typedef enum
{
    PWRCTRL_OFF_AND_CLOSEDLOOP_OFF = 0,
    PWRCTRL_ON_AND_CLOSEDLOOP_OFF,
    PWR_STUB_SET,
    PWRCTRL_ON_AND_CLOSEDLOOP_ON
}OM_PWRCTRL_SWITCH_ENUM;

typedef UINT32 OM_PWRCTRL_SWITCH_ENUM_32;

typedef enum
{
    COMPENSATE_OFF = 0,
    COMPENSATE_ON
}OM_COMPENSATE_SWITCH_ENUM;

typedef UINT32 OM_COMPENSATE_SWITCH_ENUM_32;

typedef struct
{
    OM_PWRCTRL_SWITCH_ENUM_32    ulPuschPwrCtrlSwitch            :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulPucchPwrCtrlSwitch            :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulSrsPwrCtrlSwitch              :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulPrachPwrCtrlSwitch            :2;
    OM_COMPENSATE_SWITCH_ENUM_32 ulFreqCmpnstSwitch              :1;
    OM_COMPENSATE_SWITCH_ENUM_32 ulTempCmpnstSwitch              :1;
    UINT32 ulSpare                         :22;
}PHY_OM_UPLINK_PWR_CTRL_STRU;

typedef struct __LPHY_REQ_UL_POWER_CONFIG_STRU__
{
    PHY_OM_UPLINK_PWR_CTRL_STRU stulPwrCtrlSwitch;
    INT16  sPucchTxPower;
    INT16  sPuschTxPower;
    INT16  sSrsTxPower;
    INT16  sPrachTxPower;
}LPHY_REQ_UL_POWER_CONFIG_STRU;

typedef struct __LPHY_REQ_UL_PHR_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_PHR_INFO_STRU;

typedef struct __LPHY_REQ_UL_SCHEDUl_STATIC_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_SCHEDUl_STATIC_INFO_STRU;

typedef struct __LPHY_REQ_UL_HARQBLER_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_HARQBLER_INFO_STRU;


/*SRS���ò����ṹ*/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsCommInfoValidFlg;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedInfoValidFlg;
    LRRC_LPHY_SRS_COMM_INFO_STRU          stSrsCommInfo;
    LRRC_LPHY_SRS_DEDICATED_INFO_STRU     stSrsDedicatedInfo;

    /*���ӷ�����SRSר�в��ֲ���*/
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedAperiodicInfoValidFlg;  /* R10 ������ר��SRS�����Ƿ���Ч */
    LRRC_LPHY_SRS_DEDI_APERIOD_INFO_STRU  stSrsDedicatedAperiodicInfo;          /* R10 ������ר��SRS���� */

    /*����RRC��������������õ���SRS�������ں�ƫ����*/
    UINT16                              usSrsPeriod;
    UINT16                              ausSrsOffset[2];

    UINT16                              usApSrsPeriod;
    UINT16                              ausApSrsOffset[2];
}UL_SRS_CFG_PARA_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/



/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_UL__
{
    LPHY_IND_UL_BASIC_INFO             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_UL_RANDOM_ACCESS_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x2),
    LPHY_IND_UL_CTRL_INFO              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x3),
    LPHY_IND_UL_ACK_INFO               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x4),
    LPHY_IND_UL_PUSCH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x5),
    LPHY_IND_UL_PUCCH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x6),
    LPHY_IND_UL_PRACH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x7),
    LPHY_IND_UL_SRS_STAT_INFO          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x8),
    LPHY_IND_UL_PUCCH_CAPTURE_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x9),
    LPHY_IND_UL_PUSCH_CAPTURE_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xa),
    LPHY_IND_UL_SRS_CAPTURE_INFO       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xb),
    LPHY_IND_UL_PHR_INFO               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xc),
    LPHY_IND_UL_SCHEUL_STATIC_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xd),
    LPHY_IND_UL_HARQBLER_INFO          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xe),
    LPHY_IND_UL_PD_INFO                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xf),
    /* BEGIN: Added by yushujing, 2012/8/6   PN:V7R2_MODIFY*/
    //LPHY_IND_UL_PUSCH_33A_INFO         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xf),
    //LPHY_IND_UL_PUCCH_33A_INFO         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x10)
    /* END:   Added by yushujing, 2012/8/6 */

}LPHY_IND_MSGID_UL_ENUM;
/* BEGIN: Added by yushujing, 2012/8/1   PN:V7R2_MODIFY*/
typedef struct
{
    UINT16 usDci3ValidFlag;                  /*PUSCH DCI3��3a���ڱ�־*/
    UINT16 usDci3Tpc;
    UINT16 usSendSfn;
    UINT16 usRsv;
}UL_PUSCH_33A_TPC_PARA_STRU;
typedef struct
{
    UINT16 usDci3CalcFlag;                  /*��ǰ�Ƿ������33a�ļ��� 0:δ���� 1:�н���*/
    UINT16 usRsv;
    UL_PUSCH_33A_TPC_PARA_STRU astPusch33aTpcPara[UL_MAX_SUBFRAME_NUM];
}UL_PUSCH_33A_TPC_CTRL_INFO_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_PUSCH_33A_TPC_CTRL_INFO_STRU stPusch33aTpcInfo;
}UL_OM_PUSCH_33A_TPC_IND_STRU;

typedef struct
{
    UINT16 usDci3ValidFlag;/*PUCCH DCI3��3a���ڱ�־*/
    UINT16 usDci3Tpc;
    UINT16 usSendSfn;
    UINT16 usRsv;
}UL_PUCCH_33A_TPC_PARA_STRU;
typedef struct
{
    UL_PUCCH_33A_TPC_PARA_STRU astPucch33aTpcPara[UL_MAX_SUBFRAME_NUM][UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_PUCCH_33A_TPC_PARA_STRU stPucch33aTemp;  //���ڱ��� ���5 ��֡9 �ı�����Ϣ

    UINT16 usCnt[UL_MAX_SUBFRAME_NUM];
    UINT16 usDci3CalcFlag;
    UINT16 usRevd;
}UL_PUCCH_33A_TPC_CTRL_INFO_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    //UL_PUCCH_33A_TPC_CTRL_INFO_STRU stPucch33aTpcInfo;
    UL_PUCCH_33A_TPC_PARA_STRU astPucch33aTpcPara[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_PUCCH_33A_TPC_PARA_STRU stPucch33aTemp;  //���ڱ��� ���5 ��֡9 �ı�����Ϣ
}UL_OM_PUCCH_33A_TPC_IND_STRU;

/* END:   Added by yushujing, 2012/8/1 */
enum UL_SRS_SYMBOL_IND_ENUM
{
    NON_SYMBOL = 0,
    LAST_FIRST_SYMBOL,
    LAST_SECOND_SYMBOL,
    LAST_ALL_SYMBOL
};
typedef UINT16 UL_SRS_SYMBOL_IND_ENUM_UINT16;


enum UL_SRS_TYPE_ENUM
{
    PERIOD_SRS = 0,
    APERIOD_SRS
};
typedef UINT16 UL_SRS_TYPE_ENUM_UINT16;


typedef enum
{
    UL_DCI0_GRANT = 0,
    UL_SEMI_PESIST_GRANT,
    UL_RAR_GRANT,
    UL_GRANT_INVALID
}UL_GRANT_TYPE_ENUM;

typedef struct
{
    /*��Ȩ����*/
    UL_GRANT_TYPE_ENUM  enUlGrantType;           /*RAR��Ȩָʾ�����ڼ���RAR���͹����е�f(i)*/
    UINT16              usHarqProcNum;           /*������ȡ��ʼ��Ȩ�Ĵ���*/

    /*TPC���*/
    UINT16              usTpcExistFlg;           /*TPC���ڱ�־*/
    UINT16              usTpcType;               /*tpc���� 0:DCI0; 1:DCI3; 2:3A; 3:RAR*/
    UINT16              usTpcIdx;                /*TPC����*/
    INT16               sTpc;
    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usCurMPusch;
    UINT16              usRBNum;
    UINT16              usPl;
    UINT16              usAlf;                   /* ����10bit��������1024*/
    INT16               sDeltaF;
    /*�ۻ���fi����*/
    INT16               sfi;                     /*�ۻ�����������ÿ��ʹ�ö�����*/
    INT16               sfiTmp;                  /* f(i)�м���� */
    INT16               sCalTransPwr;            /*���㹦�ʱ���*/
    INT16               sTransPwr;               /*���͹��ʱ���*/
    INT16               sPhr;

    INT16               sPucPusTotalPwr;
    //UINT16              usRevd;
    INT16              sPhr2;                   /*Type2PHR*/
    INT16              sPmax;
    UINT16             usPbValue;               /*MAC�ϱ�MPR*/
} UL_CUR_PUSCH_PWR_PARA_STRU;

/*��ǰPUCCH���ز����ṹ,����PUCCH ���ز�������*/
typedef struct
{
    UINT16              usPucchFormat;
    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usPl;
    UINT16              usHCqiAck;
    UINT16              usHarqBit;
    UINT16              usCqiBit;
    INT16               sDeltaF_PUCCH;
    INT16               sGiValue;                /*g(i)ֵ*/
    INT16               sTpcValue;               /*TPC����ֵ*/
    INT16               sCalTransPwr;
    /*���͹��ʱ���*/
    INT16               sTransPwr;               /*��¼��ǰ�ն˷��书�ʣ����ں��ն�����͹���*/
    UINT16              ausTpc[9];
    /* BEGIN: Added by yushujing, 2012/8/11   PN:V7R2_MODIFY*/
    INT16               s33aTpcValue;
    //UINT16              usRsv;
    /* END:   Added by yushujing, 2012/8/11 */

    /* BEGIN: Added by dongning, 2013/1/11   PN:V7R2_MODIFY*/
    INT16               sPmax;
    /* END:   Added by dongning, 2013/1/11 */
}UL_CUR_PUCCH_PWR_CTRL_PARA_STRU;

typedef struct
{
    /*��������*/
    INT16               sSrsOffset;
    UINT16              usSrsRBNum;
    UINT16              usMSrs;

    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usPl;
    UINT16              usAlf;                   /* ����10bit��������1024*/
    /*�ۻ���fi����*/
    INT16               sfi;                     /*�ۻ�����������ÿ��ʹ�ö�����*/
    INT16               sCalTransPwr;            /*���㹦�ʱ���*/
    INT16               sTransPwr;               /*���͹��ʱ���*/
    UINT16              usRsvd;
} UL_CUR_SRS_PWR_PARA_STRU;

typedef struct __LPHY_IND_UL_BASIC_INFO_STRU__
{
    UINT16 usSFN;                              /*С��SFN��*/
    UINT16 usSubFrameFn;                       /*С����֡��*/
    UINT16 usUpChannelType;                    /*���з��������ŵ�����.Bit0:����PUCCH;Bit1:����PUSCH;Bit2:����SRS;Bit3:����PRACH;*/
    UL_SRS_SYMBOL_IND_ENUM_UINT16 enSRSSymbInd;/*ָʾSRS���Ǹ����ŷ���*/
    UINT16 usUCIInd;                           /*ָʾUCI������:Bit0:��ʾ����CQI����;Bit1:��ʾ����ACK;Bit2:��ʾ����SR*/
    UINT16 usPuccdFormat;                      /*PUCCH��ʽ*/
    UINT16 usPuschMcs;                         /*PUSCH���Ʒ�ʽ��0:BPSK;1:QPSK;2:16QAM;3:64QAM*/
    UINT16 usPuschTB;                          /*UL-SCH��TB�鳤��*/
    INT16  sPucchPuschTxPower;                 /*PUCCH��PUSCH����PRACH�ķ��书�ʣ���λdBm*/
    INT16  sSRSTxPower;
    UL_CUR_PUSCH_PWR_PARA_STRU      stPuschPwrPara;
    UL_CUR_PUCCH_PWR_CTRL_PARA_STRU stPucchPwrPara;
    UL_CUR_SRS_PWR_PARA_STRU        stSrsPwrPara;
}LPHY_IND_UL_BASIC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM���������Ϣָʾ�ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFrameFn;

    UINT16 usPreambleIndex;

    UINT16 usPreambleRecSfn;
    UINT16 usPreambleRecSbfn;
    UINT16 usPreambleTranSfn;
    UINT16 usPreambleTranSbfn;

    UINT16 usWindowLen;
    UINT16 usPrachCfgIndex;
    UINT16 usPrachFormat;

    INT16  sTransPwr;
    INT16  sPreambleTxPower;
    UINT16 usPathLoss;

    UINT16 usK0;
    UINT16 usU;
    UINT16 usCv;

}LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU;


/*����ģ��ʹ��*/
enum UL_ENABLE_ENUM
{
    DISABLE = 0,
    ENABLE
};
typedef UINT16 UL_ENABLE_ENUM_UINT16;

/*����ģ����Ч��ʶ*/
enum UL_VALID_ENUM
{
    UL_INVALID = 0,
    UL_VALID
};
typedef UINT16 UL_VALID_ENUM_UINT16;

/*����ģ��״̬��*/
enum UL_STATE_ENUM
{
    IDLE_STATE = 0,
    PREAMBLE_SEND_STATE,
    UL_DEDICATED_STATE
};
typedef UINT16 UL_STATE_ENUM_UINT16;


/*����ģ���ŵ�������Ϣ�ṹ*/
typedef struct
{
    UL_ENABLE_ENUM_UINT16 enPucchEn;
    UL_ENABLE_ENUM_UINT16 enPuschEn;
    UL_ENABLE_ENUM_UINT16 enPrachEn;
    UL_ENABLE_ENUM_UINT16 enSrsEn;
    UL_ENABLE_ENUM_UINT16 enAckTranEn;
    UL_STATE_ENUM_UINT16  enUlCurState;
    UL_VALID_ENUM_UINT16  enSrsSchedValid; /*SRS���ڵ�����Ч��ʶ*/
    UL_VALID_ENUM_UINT16  enSrsApSchedValid; /*SRS�����ڵ�����Ч��ʶ*/


    UL_VALID_ENUM_UINT16  enSrSchedValid;  /*SR������Ч��ʶ*/
    UINT16 usCurSfn;
    UINT16 usCurSbfn;
    UINT16                usRevd;
}UL_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_CUR_UCI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM���е�ǰUCI�ṹ
*****************************************************************************/
typedef enum
{
    INVALID_CQI_REPORT = 0,
    PERIOD_CQI_REPORT,
    APERIOD_CQI_REPORT
}UL_CQI_RPT_TYPE_ENUM;

typedef UINT16 UL_CQI_RPT_TYPE_ENUM_UINT16;

/*��ǰUCI��Ϣ�ṹ*/
typedef   struct
{
    UINT8   ucPmiValid;             /*PMI�Ƿ���Ч���*/
    UINT8   ucSubbandNum;           /*�Ӵ�����*/
    UINT8   ucSubbandWidth;         /*�Ӵ���С*/
    UINT8   ucPMIValue[25];         /*PMIֵ*/

    UINT32  ulRiData;

}UL_CUR_UCI_PMI_STRU;

/*��ǰUCI��Ϣ�ṹ*/
typedef   struct
{
    UL_ENABLE_ENUM_UINT16  enCqiEn ;
    UL_ENABLE_ENUM_UINT16  enSrEn;
    UL_ENABLE_ENUM_UINT16  enRiEn ;
    UL_ENABLE_ENUM_UINT16  enAckEn;
    UL_CQI_RPT_TYPE_ENUM_UINT16 enCqiRptType;
    UINT16                 usRev;
    UINT32          aulCqiData[4];
    UINT32          ulCqiLen ;
    UINT32          ulRiData;
    UINT32          ulRiLen ;
    UINT32          ulAckData;
    UINT32          ulAckLen;
    UINT16          usCqiTranSfn;   /*��CQIģ��ȷ��*/
    UINT16          usCqiTranSbfn;

//    UINT8   ucPmiValid;             /*PMI�Ƿ���Ч���*/
//    UINT8   ucSubbandNum;           /*�Ӵ�����*/
//    UINT8   ucSubbandWidth;         /*�Ӵ���С*/
//    UINT8   ucPMIValue[25];         /*PMIֵ*/
    UL_CUR_UCI_PMI_STRU     astUciCsiStr[2];


    UINT16  usAckChSel;
    UINT16  usRiChSel;
    UINT16  usCqiChSel;
    //UINT16  usRevd;
    LPHY_CA_CC_ENUM_UINT16  enCCIndx;

}UL_CUR_UCI_STRU;

typedef struct __LPHY_IND_UL_CTRL_INFO_STRU__
{
    UL_CTRL_INFO_STRU stUlCtrlInfo;     /*���п��������Ϣ*/
    UL_CUR_UCI_STRU stCurUciInfo ;      /*UCI��Ϣ�ṹ*/
    UINT16 ausRsvd[32];
}LPHY_IND_UL_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UL_TDD_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDDģʽACK��Ϣ�ṹ
*****************************************************************************/
/*TDDģʽ����HARQ ACK��Ϣ�洢�ṹ*/

/*����뾲̬״̬*/
typedef enum
{
    /*ע��: ��Ҫ�������ö��˳��, ���а뾲̬�ᰴö��ֵȡ���Խ�ʡ����ռ��MIPS*/
    SPS_INVALID      = 0,
    SPS_RELEASE,            /*��ʾ����ȨΪ�ͷ���Ȩ*/
    SPS_ACTIVE,             /*��ʾ����ȨΪ������Ȩ*/
    SPS_RETRAN,             /*��ʾ����ȨΪ�ش���Ȩ*/
    SPS_CONFIG_GRANT        /*��ʾ����ȨΪ������Ȩ*/
}SPS_STATUS_ENUM;
typedef UINT16 SPS_STATUS_ENUM_UINT16;

typedef struct
{
    UL_SCHED_TYPE_ENUM_UINT16 aenAckSchedType[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_CODE_IND_ENUM_UINT16   aenAckCodeInd[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_ACK_ENUM_UINT16        aenAckCode1[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_ACK_ENUM_UINT16        aenAckCode2[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_TPC_TYPE_ENUM_UINT16   aenAckTpcType[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_TPC_ENUM_UINT16        aenAckTpc[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    ausAckDAI[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    ausAckNcce[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    usAckTotal;
    UINT16                    usAckNoDTX;
    UINT16                    usSpsAckCount;             /*�뾲̬ACK��Ŀ*/
    UINT16                    usAckLastRecIdx;
    UINT16                    usDbWordCnt;
    //UINT16                    usRev;
    //SPS_STATUS_ENUM       enSpsGrantStatus; /*ָʾ��ǰ�뾲̬��Ȩ״̬*/
    SPS_STATUS_ENUM_UINT16  aenSpsGrantStatus[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_VALID_ENUM_UINT16      aenAckCodeChange[UL_TDD_MAX_DL_SUBFRAME_NUM];/*0��ʾ�����ֽ�����1��ʾ�����ֽ���*/
    UINT16                    usSpecialNum;
    UINT16                    ausCcsDciInd[UL_TDD_MAX_DL_SUBFRAME_NUM];/*�������PDSCH��ӦDCI������С�����Ǹ�С����0:��С����1:��С��*/
    UINT16                    usRev;
}UL_TDD_ACK_STRU;

/*****************************************************************************
 ö����    : UL_TRAN_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ACK����ָʾ
*****************************************************************************/
/*ACK����ָʾö�ٽṹ*/
enum UL_TRAN_IND_ENUM
{
    INIT_TRAN = 0,
    RE_TRAN,
    INVALID_TRAN_IND
};
typedef UINT16 UL_TRAN_IND_ENUM_UINT16;

/*****************************************************************************
 ö����    : UL_PUC1bCS_ACK_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ACK����ָʾ
*****************************************************************************/
/*ACK����ָʾö�ٽṹ*/
enum UL_PUC1bCS_ACK_TYPE_ENUM
{
    PUCCH_1bCS_ACK_TYPE_FDD = 0,
    PUCCH_1bCS_ACK_TYPE_M1 = 1,/*M1*/
    PUCCH_1bCS_ACK_TYPE_M2,/*M1*/
    PUCCH_1bCS_ACK_TYPE_M34,/*M3��M4*/
    PUCCH_1bCS_ACK_TYPE_F3,/*Format 3��Ϊ1bCs*/
    PUCCH_1bCS_ACK_TYPE_BUTT

};
typedef UINT16 UL_PUC1bCS_ACK_TYPE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : UL_CUR_TDD_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDDģʽ��ǰ��֡ACK��Ϣ�ṹ
*****************************************************************************/
/*TDDģʽ��ǰ����HARQ ACK��Ϣ�洢�ṹ*/
typedef struct
{
    UL_TDD_ACK_STRU                 stCurTddAck;
    UINT16                          usAckIdxforPucch1;
    UINT16                          usNbundleIdx;
    UL_TRAN_IND_ENUM_UINT16         enTranInd;
    UINT16                          usRevd;
    UINT16                          usAckPucchResIdx;
    UINT16                          enAckPucchType;/*PUCCH����ACK��Ӧ������*/

    UL_PUC1bCS_ACK_TYPE_ENUM_UINT16 enPucch1bCsAckType;
    UINT16                          usRevd2;

}UL_CUR_TDD_ACK_STRU;

/*****************************************************************************
 �ṹ��    : UL_FDD_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FDDģʽACK��Ϣ�ṹ
*****************************************************************************/
/*FDDģʽ����HARQ ACK�洢�ṹ*/
typedef struct
{
    UL_SCHED_TYPE_ENUM_UINT16 enAckSchedType;
    UL_CODE_IND_ENUM_UINT16   enAckCodeInd;        /*��ǰ������Ŀ*/
    UL_ACK_ENUM_UINT16        enAckCode1;
    UL_ACK_ENUM_UINT16        enAckCode2;
    UL_TPC_TYPE_ENUM_UINT16   enAckTpcType;
    UL_TPC_ENUM_UINT16        enAckTpc;
    UINT16                    usAckNcce;
    SPS_STATUS_ENUM_UINT16    enSpsGrantStatus; /*ָʾ��ǰ�뾲̬��Ȩ״̬*/
    UL_VALID_ENUM_UINT16      enAckCodeChange;
    UINT16                    usCcsDciInd;
}UL_FDD_ACK_STRU;

/*****************************************************************************
 �ṹ��    : UL_CUR_FDD_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FDDģʽ��ǰ��֡ACK��Ϣ�ṹ
*****************************************************************************/
/*FDDģʽ��ǰ����HARQ ACK��Ϣ�洢�ṹ*/
typedef struct
{
    UL_FDD_ACK_STRU                 stCurFddAck;
    UL_TRAN_IND_ENUM_UINT16         enTranInd;
    UINT16                          usRsv;
    UINT16                          usAckPucchResIdx;
    UINT16                          enAckPucchType;/*PUCCH����ACK��Ӧ������*/
}UL_CUR_FDD_ACK_STRU;

/*****************************************************************************
 �ṹ��    : UL_ACK_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ACK�������
*****************************************************************************/
/*ACK�������*/
typedef struct
{
    UL_VALID_ENUM_UINT16  enACKValid;
    UINT16                usRevd;
    UINT32                ulAckData;
    UINT32                ulAckLen;
}UL_ACK_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_ACK_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ACK����ָʾ�ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_ACK_INFO_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFrameFn;
    UINT16 enTDDFeedbackMode;
    UINT16 usRsvd;
    union
    {
        UL_CUR_TDD_ACK_STRU stUlCurTddAck[2];
        UL_CUR_FDD_ACK_STRU stUlCurFddAck[2];
    }unCurAck;
    UL_ACK_RESULT_STRU stUlAckResult;
}LPHY_IND_UL_ACK_INFO_STRU;


 /*****************************************************************************
 �ṹ��    : UL_OM_PRACH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPrachͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulPRACHSetupReqCount;/*PRACH�ŵ������������*/
    UINT32 ulPRACHSetupReqErrCount; /*PRACH�ŵ�����ʧ�ܴ���*/
    UINT32 ulAccessReqCount;/*MAC�·��Ľ����������*/
    UINT32 ulPrachSchdErrCount; /*PRACH���ȴ������*/
    UINT32 ulPrachParaCalCount; /*PRACH�����������ͳ��*/
    UINT32 ulPrachBppCfgCount;  /*PRACH�Ĵ������ü���*/
}UL_OM_PRACH_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_PUSCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUSCHͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulPUSCHSetupReqCount;    /*PUSCH�ŵ������������*/
    UINT32 ulPUSCHHoReqCount;       /*PUSCH�ŵ��л��������ͳ��*/
    UINT32 ulPuschSetupProcNumCount;/*PUSCH�ŵ�������ȷ����ͳ��*/
    UINT32 ulPuschHoProcNumCount; /*PUSCH�ŵ��л��������´���*/
    UINT32 ulRARReqCount;           /*RAR�������*/
    UINT32 ulRARSchedCount;         /*RAR���ȼ���*/
    UINT32 ulDCISchedCount;         /*DCI���ȴ�������*/
    UINT32 ulTtiBundlingProcCount;  /*TTI�ش������������*/
    UINT32 ulUlDCI0SchedErrCount;
    UINT32 ulCodParaCalCount;       /*��������������*/
    UINT32 ulCodParaCalErrCount;    /*�����������������*/
    UINT32 ulCodParaCfgCount;       /*�������BPP���ü���*/
    UINT32 ulModParaCalCount;       /*���Ʋ����������*/
    UINT32 ulModParaCfgCount;       /*���Ʋ���BPP���ü���*/
    UINT32 ulPwrCalCount;           /*���ʼ��㴦�����*/
}UL_OM_PUSCH_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_PUCCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUCCHͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulPucchSetupReqCount;        /*PUCCH�ŵ������������*/
    UINT32 ulPucchHoReqCount;           /*PUCCH�ŵ��л��������*/
    UINT32 ulPucchRecfgCount;           /*PUCCH�ŵ������ü���*/
    UINT32 ulPucchTranCtrlCount;        /*PUCCH������Ƽ���*/
    UINT32 ulSrCfgCount;                /*SR�������ü���*/
    UINT32 ulSrReqCount;                /*SR�������*/
    UINT32 ulSrTranCtrlCount;            /*SR������Ƽ���*/
    UINT32 ulSrSchedCount;              /*SR���ȼ���*/
    UINT32 ulSrProcInPUCCHCount;        /*SR��PUCCH�ŵ����ͼ���*/
    UINT32 ulSrProcSimuPUSCHCount;      /*SR����ʱ������Ȩ*/
    UINT32 ulAckListUpdateCount;        /*ACK�ӿڵ��ü���*/
    UINT32 ulAckStoreCount;             /*ACK�������*/
    UINT32 ulAckSchedCount;             /*ACK������Ч����*/
    UINT32 ulAckDataProcErrCount;       /*ACK���ݴ���������*/
    UINT32 ulAckProcInPUCCHCount;       /*ACK��PUCCH�ŵ�ʵ�ʷ��͵Ĵ���*/
    UINT32 ulAckProcInPUSCHCount;       /*ACK��PUSCH�ŵ�ʵ�ʷ��͵Ĵ���*/
    UINT32 ulCqiUpdateCount;            /*CQI�ӿڵ��ü���*/
    UINT32 ulCqiSchedValidCount;        /*CQI������Ч����*/
    UINT32 ulCqiProcInPUCCHCount;       /*CQI��PUCCH�ŵ����ͼ���*/
    UINT32 ulCqiProcInPUSCHCount;       /*CQI��PUSCH�ŵ����ͼ���*/
    UINT32 ulRiPcellSchedValidCount;    /*��С��RI������Ч����*/
    UINT32 ulRiScellSchedValidCount;    /*��С��RI������Ч����*/
    UINT32 ulRiPScellSchedValidCount;   /*����С��RI������Ч����*/
    UINT32 ulRiProcInPUCCHCount;        /*RI��PUCCH�ŵ����ͼ���*/
    UINT32 ulRiProcInPUSCHCount;        /*RI��PUSCH�ŵ����ͼ���*/
    UINT32 ulPucchModParaCalCount;      /*PUCCH���Ʋ����������*/
    UINT32 ulPucchModParaCalErrCount;   /*PUSCH���Ʋ�������������*/
    UINT32 ulPUCCH1ModParaCfgCount;     /*PUCCH Format 1/1a/1b���Ʋ���BPP���ü���*/
    UINT32 ulPUCCH2ModParaCfgCount;     /*PUCCH Format 2/2a/2b���Ʋ���BPP���ü���*/
    UINT32 ulPucchPwrCalCount;          /*PUCCH���ʼ��㴦�����*/
}UL_OM_PUCCH_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_PWR_CTRL_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM����ͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UINT32 usPuschTPCCfgInvalidErrCount;
    UINT32 usTpcCalErrCount;
    UINT32 usPwrCommParaInvalidCount;
    UINT32 usPwrDedicatedParaInvalidCount;
}UL_OM_PWR_CTRL_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_SRS_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMSRSͳ����Ϣ�ṹ
*****************************************************************************/
/*SRS���ͳ��*/
typedef struct
{
    UINT32 ulSrsCfgReqCount;             /*SRS�����������*/
    UINT32 ulSrsSchedCount;              /*SRS������Ч����*/
    UINT32 ulApSrsSchedCount;
    UINT32 ulSrsModParaCalCount;         /*SRS���Ʋ���������� */
    UINT32 ulSrsModParaCalErrCount;      /*SRS���Ʋ������������� */
    UINT32 ulSrsBbpParaCfgCount;         /*SRSBBP���ü���*/
    UINT32 ulSrsPwrCalCount;             /*SRS���ʼ������*/
    UINT32 ulSrsEnableCount;             /*SRS��Ч��������*/
}UL_OM_SRS_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UL_OM_OTHER_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM����ͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulTARecCount;
    UINT32 ulMaxPwrReqCount;
}UL_OM_OTHER_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UL_PUCCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/

typedef struct
{
    /*ԭ���������*/
    UINT32 ulSrCfgErrCount;                            /*SR�������ô������*/
    UINT32 ulSrSchedErrCount;                          /*SR���ȴ������*/
    UINT32 ulPucchTpcCfgErrCount;                      /*TPC���ô������*/
    UINT32 ulDAIErrCount;                              /*DAI�������*/
    UINT32 ulAckUpdateErrCount;                        /*ACK�ӿڸ��´������*/
    UINT32 ulAckInvalidErrCount;                       /*ACK������Ч�������*/
    UINT32 ulFddAckStoreTimeErrCount;                  /*LTE_FRAME_TYPE_FDD ACK����ʱ��������*/
    UINT32 ulFddAckStoreErrCount;                      /*LTE_FRAME_TYPE_FDD ACK����������*/
    UINT32 ulFddAckSchedErrCount;                      /*LTE_FRAME_TYPE_FDD ACK���ȴ������*/
    UINT32 ulTddAckStoreTimeErrCount;                  /*LTE_FRAME_TYPE_TDD ACK����ʱ��������*/
    UINT32 ulTddAckRecSbfnErrCount;                    /*LTE_FRAME_TYPE_TDD ACK������֡�������*/
    UINT32 ulTddAckSchedErrCount;                      /*LTE_FRAME_TYPE_TDD ACK���ȴ������*/
    UINT32 ulTddAckNumErrCount;                        /*LTE_FRAME_TYPE_TDD ACK���մ����������*/
    UINT32 ulTddBundAckProcForPuschErrCount;           /*LTE_FRAME_TYPE_TDD PUSCH Bund ACK����������*/
    UINT32 ulTddMultiAckProcForPuschErrCount;          /*LTE_FRAME_TYPE_TDD PUCCH Multi ACK����������*/
    UINT32 ulTddBundAckProcForPucchErrCount;           /*LTE_FRAME_TYPE_TDD PUCCH Bund ACK����������*/
    UINT32 ulTddMultiAckProcForPucchErrCount;          /*LTE_FRAME_TYPE_TDD PUCCH Multi ACK����������*/
    UINT32 ulTddAckDataLossErrCount;                   /*LTE_FRAME_TYPE_TDD ACK���ݶ�ʧ�������*/
    UINT32 ulTddAckResIdxErrCount;                     /*LTE_FRAME_TYPE_TDD ACK��Դ�������������*/
    UINT32 ulTddMultiAddressErrCount;                  /*LTE_FRAME_TYPE_TDD ACK Multi���ַ�������*/
    UINT32 ulPucchFormatErrcount;                      /*PUCCH��ʽ�������*/
    UINT32 ulPucch1ResIdxGetErrCount;                  /*PUCCH Format1/1a/1b��Դ�����������*/
    UINT32 ulCqiLenErrCount;                           /*CQI���ȴ������*/
    UINT32 ulAckLenErrCount;                           /*ACK���ȴ������*/
    UINT32 ulCqiTranTimeErrCount;                      /*CQI����ʱ��������*/
    UINT32 ulSimuCqiAndSrErrCount;                     /*CQI/SRͬ���������*/
    UINT32 ulSimuAckAndCqiErrCount;                    /*CQI/ACKͬ���������*/
    UINT32 ulSimuAckAndCqiCfgDropCount;                /*CQI/ACKͬ�����ò�֧�ֶ�������*/
    UINT32 ulSimuAckAndCqiScellDropCount;              /*CQI/ACKͬ����С������ACK��������*/
    UINT32 ulSimuAckAndCqiTTiBundDropCount;            /*CQI/ACKͬ��Tti Bundling��������*/
    UINT32 ulNcceErrCount;                             /*Ncce�������*/
    UINT32 ulPucchDeltaShiftErrCount;                  /*Deltashift�������*/

    UINT32 ulPhrCfgErrCount;                           /*PHR���ô������*/
    UINT32 ulMacHeadValidErrCount;                     /* MAC PHY Headͷ��Ч��־�������*/
    UINT32 ulPucch1bCsAckResIdxErrCount;               /*PUCCH 1bCs ACK��Դ�������������*/
    UINT32 ulPucch1bCsAckTableErrCount;                /*PUCCH 1bCs ACK��Դ���ѯ�������*/
    UINT32 ulPucch1bCsResIdxGetErrCount;               /*PUCCH Format1b  Cs��Դ�����������*/
    UINT32 ulPucch3ResIdxGetErrCount;                  /*PUCCH Format3��Դ�����������*/
    UINT32 ulPucch2ResIdxGetErrCount;                  /*PUCCH Format2��Դ�����������*/

    UINT32 ulPucch1bCsPwtErrCount;                     /*PUCCH Format1bCs�����������������*/
    UINT32 ulPucch3PwtErrCount;                        /*PUCCH Format3�����������������*/
    UINT32 ulPucchnHarqErrCount;                       /*PUCCH FormatnHarq�������*/

    UINT32 ulPucch1bCsM1M2ErrCount;                    /*PUCCH Format M1M2�������*/
    UINT32 ulPucch1bCsM3M4ErrCount;                    /*PUCCH Format M3M4�������*/

    UINT32 ulAckDummyErrorCount;                       /*��֧�쳣����*/

}UL_PUCCH_STAT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : UL_PUSCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct
{
    /*ԭ���������*/
    UINT32 ulMsgChanTypeErrCount;
    UINT32 ulMsgHopModErrCount;

    UINT32 ulParaInvalidErrCount;
    UINT32 ulSpsParaInvalidErrCount;

    UINT32 ulBandWithCfgErrCount;
    UINT32 ulDCINumErrCount;
    UINT32 ulTPC0ErrCount;

    /*�������㲿�ִ���*/
    UINT32 ulImcsErrCount;
    UINT32 ulRBSumErrCount;
    UINT32 ulCqiReqFlgErrCount;
    UINT32 ulCqiDataNotReadyErrCount;
    UINT32 ulCalKposErrCount;
    UINT32 ulResAlloType1EvenErrCount;
    UINT32 ulResAlloType1OddErrCount;
    UINT32 ulHoppingInfoErrCount;
    UINT32 ulAckQCalParaInvalidErrCount;
    UINT32 ulDmrsCs1IndexErrCount;
    UINT32 ulDmrsCs2IndexErrCount;
    UINT32 ulAckCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulCqiCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulRiCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulHoppingOffsetErrCount;
    UINT32 ulType2ResourceAssinErr;
    UINT32 ulDeltaSSErrCount;
    UINT32 ulNsbErrCount;
    UINT32 ulRBNumInvalidErrCount;

    UINT32 ulDci0TpcIdxErrCount;
    UINT32 ulPuschTpcCfgInvalidErrCount;
    UINT32 ulPuschPwrAccuCalErrCount;
    UINT32 ulHarqProcNumCalErrCount;
    /*��������*/
    UINT32 ulModParaCalErrCount;
    UINT32 ulCodParaCfgCountErrCount;                   /*Deltashift�������*/
    UINT32 ulMacPduUnequalDspErrCount;                  /*DSP��MAC��һ�´������*/
    UINT32 ulOnlyUciPuschDisabErrCount;                 /*Deltashift�������*/
    UINT32 ulMacInValidErrCnt;                          /*Deltashift�������*/
    UINT32 ulTtiBundlNprbErrCnt;
    /* END:   Added by sunyanjie, 2011/11/24 */
}UL_PUSCH_STAT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : UL_PRACH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulPRACHHoReqCount;
    UINT32 ulPreambleFormatErrCount;

    UINT32 ulMsgChanTypeErrCount;
    UINT32 ulMsgRootSeqErrCount;
    UINT32 ulMsgNcsIndErrCount;
    UINT32 ulMsgPrachCfgIndErrCount;
    UINT32 ulRaReqMaskCodeIndexErrCount;
    UINT32 ulMsgPreambleIndErrCount;

    UINT32 ulRARSchedErrCount;
    UINT32 ulParaInvalidErrCount;

    UINT32 ulRARGrantUlDelayErrCount;
    UINT32 ulRARSchedError;             /*RAR����˷���ʱ϶����*/
    UINT32 ulPrachResouceIndCount;
    UINT32 ulTddFrmStruErrCount;        /*FDDģʽ�£�֡�ṹ���ʹ��󣬼�����0~6��Χ��*/

    UINT32 ulRootuAndCvCalErrCont;
    UINT32 ulFddCalPrbIndexErrCount;
    UINT32 ulRBStartPosErrCount;

    /*bpp������ؼ���*/
    UINT16 usBppCfgErrCount;
    UINT16 usRsv;
}UL_PRACH_STAT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : UL_SRS_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulSrsCfgErrCount;               /*SRS���ô������*/
    UINT32 ulSrsNraErrCount;               /*SRS Nra�������*/
    UINT32 ulSrsBandErrCount;              /*SRS�������ô������*/
    UINT32 ulSrsMsrsMaxCalErrCount;        /*SRS Msrsmax����������*/
    UINT32 ulMsrsCalErrCount;              /*SRS Msrs����������*/
    UINT32 ulUpptsK0PieCalErrCount;        /*SRS Uppts k0pie����������*/

}UL_SRS_STAT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_PRACH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_PRACH_STAT_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usRsvd;
    UL_OM_PRACH_STAT_INFO_STRU stOmPrachStatInfo;
    UL_PRACH_STAT_INFO_STRU stUlPrachStatInfo;
}LPHY_IND_UL_PRACH_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_PUSCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_PUSCH_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_PUSCH_STAT_INFO_STRU stOmPuschStatInfo;
    UL_PUSCH_STAT_INFO_STRU stUlPuschStatInfo;
}LPHY_IND_UL_PUSCH_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_PUCCH_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_PUCCH_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_PUCCH_STAT_INFO_STRU stOmPucchStatInfo;
    UL_PUCCH_STAT_INFO_STRU stUlPucchStatInfo;
}LPHY_IND_UL_PUCCH_STAT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LPHY_IND_UL_SRS_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMUCI��������ṹ
*****************************************************************************/
typedef struct __LPHY_IND_UL_SRS_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_SRS_STAT_INFO_STRU stOmSrsStatInfo;
    UL_SRS_STAT_INFO_STRU stUlSrsStatInfo;
}LPHY_IND_UL_SRS_STAT_INFO_STRU;




/*****************************************************************************
 ö����    : UL_TRAN_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ACK����ָʾ
*****************************************************************************/
/*PUCCH��ʽö�ٽṹ*/
enum UL_PUCCH_FORMAT_ENUM
{
    PUCCH_FORMAT_1 = 0,
    PUCCH_FORMAT_1a,
    PUCCH_FORMAT_1b,
    PUCCH_FORMAT_1b_CS,
    PUCCH_FORMAT_2,
    PUCCH_FORMAT_2a,
    PUCCH_FORMAT_2b,
    PUCCH_FORMAT_3,
    PUCCH_FORMAT_INVALID
};
typedef UINT16 UL_PUCCH_FORMAT_ENUM_UINT16;

/*****************************************************************************
 ö����    : UL_HIGHSPEED_FLG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ߵ��ٱ�־
*****************************************************************************/
/*PRACH �ߵ��ٱ�־������preamble���������Ӧunrestricted set��restricted set*/
enum UL_HIGHSPEED_FLG_ENUM
{
    HIGH_SPEED_FLAG_FALSE = 0, /*��Ӧunrestricted set*/
    HIGH_SPEED_FLAG_TURE       /*��Ӧrestricted set*/
};
typedef UINT16 UL_HIGHSPEED_FLG_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : UL_OM_BBP_PARA_CAPTURE_FLG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMBBP���������־�ṹ
*****************************************************************************/
typedef struct
{
    UINT16 usBbpParaActFlg;
    UINT16 usBitmap;
}UL_OM_BBP_PARA_CAPTURE_FLG_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_STAT_INFO_CAPTURE_FLG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMͳ����Ϣ�����־�ṹ
*****************************************************************************/
typedef struct
{
    UINT16 usStatInfoActFlg;
    UINT16 usBitmap;
    UINT32 ulStaRptTyp;
}UL_OM_STAT_INFO_CAPTURE_FLG_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_STAT_INFO_CAPTURE_FLG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMͳ����Ϣ��־�ṹ
*****************************************************************************/
typedef struct
{
    UL_OM_ACTIVE_FLG_ENUM_UINT16  enInfoActflag;
    UINT16  usPeriod;
    UINT16  usPeriodCount;
    UINT16  usRsv;
}UL_OM_CTRL_INFO_STRU;
/* END:   Added by yushujing, 2010/9/2 */

/*****************************************************************************
 �ṹ��    : UL_OM_DATA_CAPTURE_FLG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM���ݲ����־�ṹ
*****************************************************************************/
typedef struct
{
    UINT16 usBasicInfoActFlg;
    UINT16 usRandomAccessActFlg;
    UINT16 usCtrlInfoActFlg;
    UINT16 usAckInfoActFlg;
    UINT32 ulUciBitMap;
    UL_OM_STAT_INFO_CAPTURE_FLG_STRU stStatInfoCapFlg;
    UL_OM_BBP_PARA_CAPTURE_FLG_STRU stBbpParaCapFlg;
    UL_OM_CTRL_INFO_STRU stBasicInfoActFlg;
    UL_OM_CTRL_INFO_STRU stPhrCtrlInfo;
}UL_OM_DATA_CAPTURE_FLG_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_PWR_SET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM�������ýṹ
*****************************************************************************/
typedef struct
{
   UINT16 usPuschPwrCtrlSwitch;
   UINT16 usPuschClosedLoopSwitch;
   UINT16 usPucchPwrCtrlSwitch;
   UINT16 usPucchClosedLoopSwitch;
   UINT16 usSrsPwrCtrlSwitch;
   UINT16 usPrachPwrCtrlSwitch;
   INT16  sPuschTxPower;
   INT16  sPucchTxPower;
   INT16  sSrsTxPower;
   INT16  sPrachTxPower;
}UL_OM_PWR_SET_STRU;



/*****************************************************************************
 �ṹ��    : UL_PUSCH_BPP_CODING_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUSCHBBP�������ò����ṹ
*****************************************************************************/

/*PUSCH BPP����������üĴ����������ִ������˼������Ӳ���ӿ�,��13���Ĵ���*/

/*PUSCH BPP����������üĴ����������ִ������˼������Ӳ���ӿ�,��11���Ĵ���*/

typedef struct
{
    /*PUSCH_SBFN_REG*/
    UINT32 ulPROCESS_NUM    :4;
    UINT32 ulSUBFRAME_NUM   :4;
    UINT32 ulFRAME_NUM      :10;
    UINT32                  :14;
    /*ULSCH_TB_REG*/
    UINT32 ulQM_PUSCH       :3;
    UINT32                  :1;
    UINT32 ulTB_SIZE        :17;
    UINT32                  :11;
    /*SEG_NEG_CB_REG*/
    UINT32 ulC1_UL_SCH      :4;  /*C-*/
    UINT32 ulK1_UL_SCH      :13; /*K-*/
    UINT32                  :15;
    /*SEG_POS_CB_FILL_REG*/
    UINT32 ulC2_UL_SCH      :4;  /*C+*/
    UINT32 ulK2_UL_SCH      :13; /*K+*/
    UINT32                  :3;
    UINT32 ulN_TB_NULL      :6;
    UINT32                  :6;
    /*TURBO_PARA_KNEG_REG*/
    UINT32 ulF1_C1_UL_SCH   :9;  /*f1 for C-*/
    UINT32                  :3;
    UINT32 ulF2_C1_UL_SCH   :10; /*f2 for C-*/
    UINT32                  :10;
    /*TURBO_PARA_KPOS_REG*/
    UINT32 ulF1_C2_UL_SCH   :9;  /*f1 for C+*/
    UINT32                  :3;
    UINT32 ulF2_C2_UL_SCH   :10; /*f2 for C+*/
    UINT32                  :10;
    /*TURBO_RM_EDW_REG*/
    UINT32 ulC1_E_UL_SCH    :17; /*E for C-*/
    UINT32                  :3;
    UINT32 ulRvinx          :2;  /*����汾��*/
    UINT32                  :10;
    /*TURBO_RM_EUP_REG*/
    UINT32 ulC2_E_UL_SCH    :17; /*E for C+*/
    UINT32                  :3;
    UINT32 ulGama           :4;
    UINT32                  :8;
    /*PUSCH_INTERLEAVER_REG*/
    UINT32 ulRbNum          :7;  /*RbNum��Ŀ,BBP�Լ������ŵ���֯����*/
    UINT32                  :1;
    UINT32 ulSCH_SYMB_NUM   :4;  /*ָʾ���һ�������Ƿ���SRS,0:�����ͣ�1:����*/
    UINT32                  :20;
    /*PUSCH_Q_RI_CQI_REG*/
    UINT32 ulQ_CQI_PUSCH    :14; /*Q'cqi*/
    UINT32                  :2;
    UINT32 ulQ_RI_PUSCH     :13; /*Q'ri*/
    UINT32                  :3;
    /*PUSCH_ACK_REG*/
    UINT32 ulAckScrEn       :1;
    UINT32                  :3;
    UINT32 ulNbundleIdx     :2;
    UINT32                  :10;
    UINT32 ulQ_ACK_PUSCH    :13; /*Q'ack*/
    UINT32                  :3;
}UL_PUSCH_BPP_CODING_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UL_PUSCH_BBP_MOD_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUSCHBBP�������ò����ṹ
*****************************************************************************/
/*�������½ӿڵ��������ݽṹ��20090429*/
typedef struct
{
    UINT32 aulModReg[9];
    #if 0
    /*PUSCH_SCRAMBL_REG*/
    UINT32 ulScr_X2_Init            :31;
    UINT32                          :1;
    /*PUSCH_EVEN_REG*/
    UINT32 ulU_PUSCH_EVEN           :5;
    UINT32                          :3;
    UINT32 ulQ_PUSCH_EVEN           :11;
    UINT32                          :1;
    UINT32 ulN_DMRS_EVEN_PUSCH      :4;
    //UINT32 ulRB_START_EVEN          :7;
    //UINT32                          :1;
    UINT32 ulPUS_EVEN_NPRB_STYLE    :1;
    UINT32                          :7;
    /*PUSCH_ODD_REG*/
    UINT32 ulU_PUSCH_ODD            :5;
    UINT32                          :3;
    UINT32 ulQ_PUSCH_ODD            :11;
    UINT32                          :1;
    UINT32 ulN_DMRS_ODD_PUSCH       :4;
    //UINT32 ulRB_START_ODD           :7;
    //UINT32                          :1;
    UINT32 ulPUS_ODD_NPRB_STYLE       :1;
    UINT32                            :7;

    /*PUSCH_EVEN_RB_POS*/
    UINT32 ulPUS_EVEN0_NPRB           :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN0_RBLEN          :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN1_NPRB           :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN1_RBLEN          :7;
    UINT32                            :1;

    /*PUSCH_ODD_RB_POS*/
    UINT32 ulPUS_ODD0_NPRB            :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD0_RBLEN           :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD1_NPRB            :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD1_RBLEN           :7;
    UINT32                            :1;

    /*PUSCH_DMRS_REG*/
    UINT32 ulw_0                      :1;
    UINT32 ulw_1                      :1;
    UINT32                           :30;

    /*PUSCH_AMP_REG*/
    UINT32 ulpus_amp_b                :17;
    UINT32                            :15;
    #endif
}UL_PUSCH_BBP_MOD_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UL_OM_DCI0_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMDCI0�ṹ
*****************************************************************************/
typedef struct
{
    UINT16 usSemiStaticFlag; /*��̬/�뾲̬����ָʾ*/
    UINT16 usInitGrantFlag;  /*��ʼ��Ȩ��־*/
    UINT16 usDci0ExistFlag;      /*DCI0���ڱ�־*/
    UINT16 usHoppingFlag;    /*Hopping flag*/
    UINT16 usTbSize;         /*TB size */
    UINT16 usRIV;             /*����汾��*/
    UINT16 usImcs;              /*���ƽ���*/
    UINT16 usNewIndex;        /*������ָʾ*/
    UINT16 usPuschTpc;       /*TPC command for scheduled PUSCH*/
    UINT16 usCyclicDmrs;     /*Cyclic shift for DM RS*/
    UINT16 usUlIndex;        /*UL index*/
    UINT16 usCqiRequest;     /*CQI request*/
    UINT16 usRbStart;        /*RB��ʼλ��*/
    UINT16 usRbNum;          /*RB��Ŀ*/
    UINT16 usHopInfo;        /*��Ƶ��Ϣ*/
    UINT16 usDaiInfo;        /*DAI��Ϣ��*/
}UL_OM_DCI0_STRU;

enum UL_RB_ALLOC_TYPE_ENUM
{
    UL_RB_ALLOC_TYPE0 = 0,
    UL_RB_ALLOC_TYPE1 = 1,
    UL_RB_ALLOC_INVALID
};
typedef UINT16 UL_RB_ALLOC_TYPE_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : DCI0_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    UINT16 usSemiStaticFlag; /*��̬/�뾲̬����ָʾ,0-��̬,1-��̬*/
    UINT16 usInitGrantFlag;  /*��ʼ��Ȩ��־,1-��ʼ,0-�ش�*/
    UINT16 usDci0ExistFlag;      /*DCI0���ڱ�־,1-����,0-������*/
    UINT16 usNewTransFlag;    /*ָʾ�Ƿ�Ϊ��һ���յ�����Ȩ,0xffff-û����Ȩ��1-�Ѿ��յ���Ȩ*/
    SPS_STATUS_ENUM enSemiGrantType;    /*ָʾ��ǰ��Ȩ�ǰ뾲̬����/�ͷ���Ȩ����������Ȩ1-������ͷ���Ȩ��0-������Ȩ*/
    UINT16 usAntPort;
    UINT16 usHoppingFlag;    /*Hopping flag*/
    UINT16 usTbSize;         /*TB size */
    UINT16 usRIV;             /*����汾��*/
    UINT16 usImcs;              /*���ƽ���*/
    UINT16 usNewIndex;        /*������ָʾ*/
    UINT16 usPuschTpc;       /*TPC command for scheduled PUSCH*/
    UINT16 usCyclicDmrs;     /*Cyclic shift for DM RS*/
    UINT16 usUlIndex;        /*UL index*/
    UINT16 usCqiRequest;     /*CQI request*/
    //UINT16 usRbStart;        /*RB��ʼλ��*/
    UINT16 usRbNum;          /*RB��Ŀ*/
    UINT16 usHopInfo;        /*��Ƶ��Ϣ*/
    UINT16 usDaiInfo;        /*DAI��Ϣ��*/
    UINT16 usOnlyUciInfoFlg;
    UINT16 usRnti;
    UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT32 ulRbAssign;
    UINT16 usRbNum0;
    UINT16 usRbNum1;
    UINT16 usRbStart0;
    UINT16 usRbStart1;
}DCI0_STRU;

/*****************************************************************************
 �ṹ��    : UL_OM_PUSCH_CAPTURE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUSCH��������ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulProcessID;
    DCI0_STRU stDci0;
    UL_PUSCH_BPP_CODING_PARA_STRU stPUSCHBbpCodingPara;
    UL_PUSCH_BBP_MOD_PARA_STRU stPuschBbpModPara;
}UL_OM_PUSCH_CAPTURE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UL_MOD_PUCCH1_BBP_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PUCCH��ʽ1/1a/1b BBP���ò����ṹ
*****************************************************************************/


typedef struct
{
    /*PUCCH_FORMAT_REG*/
    UINT32 ulPUCCH_FORMAT     :3;
    UINT32                    :29;

    /*PUCCH_COMMON_REG*/
    UINT32 ulU_EVEN           :5;                      /*żʱ϶���������u*/
    UINT32                    :3;
    UINT32 ulEVEN_PRB_INDEX   :7;                      /*żʱ϶PRBλ��*/
    UINT32                    :1;
    UINT32 ulU_ODD            :5;                      /*��ʱ϶���������u*/
    UINT32                    :3;
    UINT32 ulODD_PRB_INDEX    :7;                      /*��ʱ϶PRBλ��*/
    UINT32                    :1;

    /*PUCCH1_PARA_REG*/
    UINT32 ulEVEN_OC_INDEX    :2;                      /*żʱ϶������������*/
    UINT32                    :2;
    UINT32 ulODD_OC_INDEX     :2;                      /*żʱ϶������������*/
    UINT32                    :2;
    UINT32 ulEVEN_S_NS        :1;                       /*żʱ϶����ϵ��*/
    UINT32                    :3;
    UINT32 ulODD_S_NS         :1;                       /*żʱ϶����ϵ��*/
    UINT32                    :3;
    UINT32 ulODD_N_SF_PUCCH   :3;                       /*��ʱ϶PUCCH��ʽָʾ*/
    UINT32                    :13;

    /*PUCCH23_SCRAMBL_REG*/
    UINT32 ulPUCCH2_SCRAMBL   :31;                       /*PUCCH��ʽ23�������*/
    UINT32                    :1;

    /*PUCCH123_EVEN_NCS_REG*/
    UINT32 ulEVEN_NCS         :28;                      /*żʱ϶ѭ����λ*/
    UINT32                    :4;

    /*PUCCH123_ODD_NCS_REG*/
    UINT32 ulODD_NCS          :28;                      /*��ʱ϶ѭ����λ*/
    UINT32                    :4;

    /*PUCCH3_PARA_REG*/
    UINT32 ulPUC3_NOC_EVEN    :3;                      /*żʱ϶������������*/
    UINT32                    :1;
    UINT32 ulPUC3_NOC_ODD     :3;                      /*��ʱ϶������������*/
    UINT32                    :1;
    UINT32 ulPUC3_NSF_ODD     :3;                      /*��ʱ϶���Ÿ�ʽ*/
    UINT32                    :21;

    /*PUCCH_AMP_REG*/
    UINT32 ulPUC_AMP_B        :17;
    UINT32                    :15;

    /*PUCCH_ANTENNA_REG*/
    UINT32 ulAntennaSel       :1;
    UINT32                    :31;

}UL_PUCCH_BBP_MOD_PARA_STRU;



/*****************************************************************************
 �ṹ��    : UL_OM_PUCCH_CAPTURE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMPUCCH��������ṹ
*****************************************************************************/
typedef struct
{
    UL_PUCCH_FORMAT_ENUM_UINT16 enPUCCH_Format;
    union
    {
        UINT16 usnPUCCH1;
        UINT16 usnPUCCH2;
        UINT16 usnPUCCH3;
    }unPucchResoureIdx;

    UL_PUCCH_BBP_MOD_PARA_STRU stPucchBbpPara;
}UL_OM_PUCCH_CAPTURE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UL_MOD_SRS_BBP_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OMSRSBBP���Ʋ����ṹ
*****************************************************************************/
/*SRS BBP���ò����ṹ*/

typedef struct
{
   /*SRS_POS_REG*/
   UINT32 ulK0_LAST1    :11;
   UINT32               :1;
   UINT32 ulK0_LAST2    :11;
   UINT32               :1;
   UINT32 ulSymInd      :2;
   UINT32               :6;

   /*SRS_BASE_REG*/
   UINT32 ulSRS_Q       :11;
   UINT32               :1;
   UINT32 ulSRS_U       :5;
   UINT32               :3;
   UINT32 ulN_SRS       :3;
   UINT32               :9;

   /*SRS_LEN_REG*/
   UINT32 ulSRS_N_ZC_RS :11;
   UINT32               :1;
   UINT32 ulM_SC_B      :11;
   UINT32               :9;

   /*SRS_AMP_REG*/
   UINT32 ulSRS_AMP_B   :17;
   UINT32               :15;
   /*SRS_ANTENNA_REG*/
   UINT32 ulSRS_ANTENNA;

}UL_MOD_SRS_BBP_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHY_OM_UPLINK_CAPTURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM���в���ָʾ�ṹ
*****************************************************************************/
typedef struct
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usRev;
    union
    {
        UL_OM_PUCCH_CAPTURE_PARA_STRU stPucchCaptruePara;
        UL_OM_PUSCH_CAPTURE_PARA_STRU stPuschCaptruePara;
        UL_MOD_SRS_BBP_PARA_STRU stSrsBbpPara;
    }unCaptrueInfo;
}PHY_OM_UPLINK_CAPTURE_IND_STRU;

typedef struct __LPHY_IND_UL_PUSCH_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usPuschRate;
    UINT32 ulMacDataInvalid;
    INT16 sPuschTransPwr;
    UINT16 usRev;
    UL_OM_PUSCH_CAPTURE_PARA_STRU stPuschCaptruePara;

}LPHY_IND_UL_PUSCH_CAPTURE_INFO_STRU;

typedef struct __LPHY_IND_UL_PUCCH_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    /* UINT16 usRev; */
    INT16 sPucchTransPwr;
    UL_OM_PUCCH_CAPTURE_PARA_STRU stPucchCaptruePara;
}LPHY_IND_UL_PUCCH_CAPTURE_INFO_STRU;

typedef struct __LPHY_IND_UL_SRS_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    /* UINT16 usRev; */
    INT16 sSrsTransPwr;
    UL_SRS_CFG_PARA_STRU stSrsCfg;
    UL_MOD_SRS_BBP_PARA_STRU stSrsBbpPara;
}LPHY_IND_UL_SRS_CAPTURE_INFO_STRU;

typedef struct
{
    UINT32 ulMcsCnt;
    UINT32 ulRBTotal;
}UL_MCS_RB_STRU;

typedef struct __LPHY_IND_UL_SCHEUL_STATIC_INFO_STRU__
{
    UL_MCS_RB_STRU astMcsRb[32];
    UINT32 aulSlot0RbCnt[100];
    UINT32 aulSlot1RbCnt[100];
    UINT32 ulRbTotal;
    UINT32 ulPeriodCnt;
}LPHY_IND_UL_SCHEUL_STATIC_INFO_STRU;

typedef struct
{
    UINT32 ulTotal;
    UINT32 ulIniBler;
    UINT32 ulReBler;
}UL_HARQBLER_STRU;


typedef struct __LPHY_IND_UL_HARQBLER_INFO_STRU__
{
    UL_HARQBLER_STRU stPeriod;
    UL_HARQBLER_STRU stAccumTotal;
    UINT32 ulPeriodCnt;
}LPHY_IND_UL_HARQBLER_INFO_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usRsv;
}LPHY_REQ_UL_PD_INFO_STRU;


typedef struct
{
    INT16                       sulPwr;        /*��ǰ��֡���͹���*/
    INT16                       sDeltap;       /*��ǰ��֡�����õ���DelatP����*/
    UINT16                      usPdval;       /*PD�ض�ֵ*/
    UINT16                      usIfEnablePd;  /*��ǰ��֡�Ƿ�ʹ���¸���֡��PD*/
    UINT16                      usIfReadPd;    /*��ǰ��֡�Ƿ�ʹ����֡��PD*/
    UINT32                      ulCenterUlPonit; /*����Ƶ��*/
    UINT16                      usPdRbSum;        /*RF�����ԭ�򣬵�RB����PD�ض���׼ȷ*/
    UINT16                      usRsv;
}UL_PD_SBSFN_INFO_STRU;
typedef struct
{
    UINT16                      usIfValidDelta;
    INT16                       usPdDelta;
    UINT16                      usCenFreq;
    INT16                       sPwrByPd1;
    INT16                       sPwrByPd2;
    UINT16                      usPdSfn;
    UINT16                      usPdSbfn;
    UINT16                      usPdPwrVlidNum;
    INT16                       sPdPwrDeltSum;
	UINT16                      usRsv;
    UL_PD_SBSFN_INFO_STRU       ausSbsfnPdinfo[UL_MAX_SUBFRAME_NUM];
}UL_PD_STATE_STRU;

typedef struct
{
    UINT16                      usNoContinuStat;
    UINT16                      usNoEnable;
    UINT16                      usLongThan10msStat;
    UINT16                      usInvalidPwr;
    UINT16                      usPdReadFail;
    UINT16                      usPdRangeOut;
}UL_PD_STAT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usNoContinuStat;
    UL_PD_STAT_STRU             stPdStatInfo;
    UL_PD_STATE_STRU            stPdState;
}LPHY_IND_UL_PD_INFO_STRU;

enum
{
    DCI_INVALID = 0,
    UL_DCI_VALID,
    DL_DCI_VALID
};
typedef UINT16 RAR_DCI_VALID_ENUM_UINT16;
enum
{
    UL_ACCESS_INVALID = 0,
    UL_ACCESS_START,
    UL_ACCESS_FINISH
};
typedef UINT16 UL_ACCESS_STATUS_ENUM_UINT16;

enum
{
    UL_MSG3_INVALID = 0,
    UL_MSG3_START,
    UL_MSG3_ACK_RECEIVE
};
typedef UINT16 UL_MSG3_STATUS_ENUM_UINT16;

/* END:   Added by sunyanjie, 2011/11/14 */
typedef struct
{
    //UINT16 usMsg3SndFlg;
    UL_MSG3_STATUS_ENUM_UINT16 enMsg3SndFlg;
    /* END:   Added by sunyanjie, 2011/11/14 */
    UINT16 usAccessMode;
    UINT16 usTcRnti;
    UINT16 usPdcchOrderFlg;
    UINT16 usRarAck;
    UINT16 usRarHarqNum;
    UL_ACCESS_STATUS_ENUM_UINT16 enAccessStatus;
    RAR_DCI_VALID_ENUM_UINT16 enDciReceived;
    /* END:   Added by sunyanjie, 2011/11/14 */
}UL_RAR_PROCESS_STRU;


typedef struct
{
    UINT32 ulMsgId;
    UINT16 usSfn;
    UINT16 usSbSfn;
    UINT32 aulTraceInfo[4];
}OM_DSP_TRACE_INFO;

typedef enum
{
    DCI0_INVALID = 0,
    DCI0_VALID,
    DCI0_USED
}DCI_VALID_ENUM;

typedef UINT16 DCI_VALID_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : UL_GRANT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    DCI_VALID_ENUM_UINT16 usDci0ValidFlag;
    UINT16 usUlTpcValidFlag;     /*3/3A��Ч��־*/
    UINT16 usFrameNum;       /*��Ч֡��*/
    UINT16 usSubFrameNum;    /*��Ч��֡��*/
    UINT16 usUlTpc;          /*PUSCH��3/3A��TPC*/
    UINT16 usUeAntMode;
    DCI0_STRU stDci0;
}UL_GRANT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;

    UINT16 usPucchPuschSimul;
    INT16 sPhr;
    INT16 sPhr2;
    INT16 sPmax;

    UINT8 ucPhrType;
    UINT8 aucPhrValue[5];
    UINT8 aucRev[2];
}PHY_OM_PHR_INFO_IND_STRU;

enum __MCS_QM_ENUM__
{
    MCS_QPSK_MOD = 0,
    MCS_16QAM_MOD,
    MCS_64QAM_MOD,
    MCS_QM_INVALID
};
typedef UINT16 MCS_QM_ENUM_UINT16;

/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_UL_ENUM__
{
    LPHY_TRACE_UL_LOG_STATE_REQ_ERR           = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_UL_LOG_SRS_CFG_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2),
    LPHY_TRACE_UL_LOG_ACKTPC_INVALID_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x3),
    LPHY_TRACE_UL_LOG_FDD_ACK_STORE_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x4),
    LPHY_TRACE_UL_LOG_TDD_ACK_REC_SUBFRM_ERR  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x5),
    LPHY_TRACE_UL_LOG_TDD_ACK_STORE_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x6),
    LPHY_TRACE_UL_LOG_TDD_ACK_NUM_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x7),
    LPHY_TRACE_UL_LOG_MULTI_ADDRESS_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x8),
    LPHY_TRACE_UL_LOG_NCCE_ERR                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x9),
    LPHY_TRACE_UL_LOG_PUCCH_FORMAT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xA),
    LPHY_TRACE_UL_LOG_PRACH_CFG_IDX_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xB),
    LPHY_TRACE_UL_LOG_TPC_IDX_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xC),
    LPHY_TRACE_UL_LOG_RAR_SLOT_ERR            = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xD),
    LPHY_TRACE_UL_LOG_SRS_CELL_CFG_IDX_ERR    = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xE),
    LPHY_TRACE_UL_LOG_PRACH_FORMAT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xF),
    LPHY_TRACE_UL_LOG_PREAMBLE_IDX_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x10),
    LPHY_TRACE_UL_LOG_NCS_IDX_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x11),
    LPHY_TRACE_UL_LOG_ROOTSEQ_IDX_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x12),
    LPHY_TRACE_UL_LOG_RA_PRB_ERR              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x13),
    LPHY_TRACE_UL_LOG_HALF_SEARCH_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x14),
    LPHY_TRACE_UL_LOG_IMCS_ERR                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x15),
    LPHY_TRACE_UL_LOG_RBSUM_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x16),
    LPHY_TRACE_UL_LOG_CQIREQ_ERR              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x17),
    LPHY_TRACE_UL_LOG_HOPPINGINFO_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x18),
    LPHY_TRACE_UL_LOG_RIV_ERR                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x19),
    LPHY_TRACE_UL_LOG_DMRS1_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1A),
    LPHY_TRACE_UL_LOG_DMRS2_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1B),
    LPHY_TRACE_UL_LOG_RBNUM_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1C),
    LPHY_TRACE_UL_LOG_BANDWIDTH_INDEX_ERR     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1D),
    LPHY_TRACE_UL_LOG_MASKCODE_INDEX_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1E),
    LPHY_TRACE_UL_LOG_CQI_TRANS_TIME_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1F),
    LPHY_TRACE_UL_LOG_FDD_ACK_SCHED_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_UL_LOG_TDD_ACK_SCHED_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x21),
    LPHY_TRACE_UL_LOG_CODERATE_EX_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x22),
    LPHY_TRACE_UL_LOG_MBX_ERR                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x23),
    LPHY_TRACE_UL_LOG_TTI_BUNDL_STATE_CHANGE  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x24),
    /* END:   Added by sunyanjie, 2011/11/24 */
    LPHY_TRACE_UL_TA_TIMER_TIMEOUT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x25),
    LPHY_TRACE_UL_CHANNEL_RELEASE             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x26),
    LPHY_TRACE_UL_SRS_CONFIG                  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x27),
    LPHY_TRACE_UL_SRS_RELEASE                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x28),
    LPHY_TRACE_UL_HARQ_MAX_NUM_ERR            = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x29),
    LPHY_TRACE_UL_UCI_ONLY_CONFIG             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2A),
    LPHY_TRACE_UL_PREAMBLE_TRANS_REQUEST      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2B),
    LPHY_TRACE_UL_PREAMBLE_TRANSMIT           = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2C),
    LPHY_TRACE_UL_NONCONTENT_RAR_CONFIG       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2D),
    LPHY_TRACE_UL_CONTENT_RAR_CONFIG          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2E),
    LPHY_TRACE_UL_MSG3_TRANSMIT               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2F),
}LPHY_TRACE_UL_ENUM;

#define UL_TRACE_ERR_LEN   16

typedef struct __LPHY_TRACE_UL_CODERATE_EX_ERR_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT32 usTBSize;
    UINT32 usCalRateG;
    UINT32 usPuschRate;
}LPHY_TRACE_UL_CODERATE_EX_ERR_INFO_STRU;

typedef struct __LPHY_TRACE_UL_FRAME_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 ulData[4];
}LPHY_TRACE_UL_FRAME_INFO_STRU;


typedef struct __LPHY_TRACE_UL_SRS_CONFIG_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usUlSrsConfigPeriod;
    UINT16 usReserved;
}LPHY_TRACE_UL_SRS_CONFIG_STRU;

typedef struct __LPHY_TRACE_UL_RAR_CONFIG_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 enRaAccessType;
    UINT16 usTaVal;
}LPHY_TRACE_UL_RAR_CONFIG_STRU;



/* BEGIN: Added by xueqiuyan, 2012/9/7   PN:CMCC_DT*/

/************************************************************
                           5. DT·�����ݽṹ����
************************************************************/

/*****************************************************************************
�ṹ��    : UL_OM_DATA_CAPTURE_FLG_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/



typedef enum __LPHY_DT_REQ_MSGID_UL__
{
    LPHY_DT_UL_POWER_INFO_REQ              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_UL_PUSCH_INFO_REQ              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x2),
    LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x3),
    LPHY_DT_HARQ_INFO_REQ                  =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x4),
    LPHY_DT_UL_ACCESS_INFO_REQ             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x5),
    LPHY_DT_TA_INFO_REQ                    =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x6),
    LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x7)

}LPHY_DT_REQ_MSGID_UL_ENUM;


typedef struct __LPHY_DT_UL_POWER_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_DT_UL_POWER_INFO_REQ_STRU;
typedef struct __LPHY_DT_UL_PUSCH_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_DT_UL_PUSCH_INFO_REQ_STRU;

typedef struct __LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU;

typedef struct __LPHY_DT_HARQ_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRptHarqInfoPeriod;
} LPHY_DT_HARQ_INFO_REQ_STRU;

typedef struct __LPHY_DT_UL_ACCESS_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_DT_UL_ACCESS_INFO_REQ_STRU;

typedef struct __LPHY_DT_TA_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_DT_TA_INFO_REQ_STRU;
typedef struct __LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usTransSuccRptPeriod;
}LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU;




typedef enum __LPHY_DT_IND_MSGID_UL__
{
    LPHY_DT_UL_POWER_INFO_IND              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1001),
    LPHY_DT_UL_PUSCH_INFO_IND              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1002),
    LPHY_DT_UL_PUSCH_INFO_CA_IND           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x9002),   
    LPHY_DT_UL_SCHEDULE_STAT_INFO_IND      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1003),
    LPHY_DT_HARQ_INFO_IND                  =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1004),
    LPHY_DT_HARQ_INFO_CA_IND               =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x9004),    
    LPHY_DT_UL_ACCESS_INFO_IND             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1005),
    LPHY_DT_TA_INFO_IND                    =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1006),
    LPHY_DT_PUSCH_HARQ_BLER_STAT_IND      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1007)

}LPHY_DT_IND_MSGID_UL_ENUM;


typedef struct __LPHY_DT_UL_POWER_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    INT16   sPuschTransPwr;
    INT16   sP0;
    UINT16  usPl;
    UINT16  usAlf;
    INT16   sFi;
    INT16   sPucchTransPwr;
    INT16   sGiValue;
    INT16   sSrsTransPwr;
    UINT16  usSrsRBNum;
    UINT16  usRsv;
}LPHY_DT_UL_POWER_INFO_IND_STRU;


typedef struct __LPHY_DT_UL_PUSCH_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
	UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT16  usPuschRb0Num;
    UINT16  usPuschRb0Start;
    UINT16  usPuschRb1Num;
    UINT16  usPuschRb1Start;	
    UINT16  usRvIndex;
    UINT16  usUlMcs;
    MCS_QM_ENUM_UINT16  enUlModSched;
    UINT16  usTbSize;
    UINT16  usHarqId;
} LPHY_DT_UL_PUSCH_INFO_IND_STRU;



typedef struct __LPHY_DT_UL_SCHEDULE_STAT_INFO_IND_STRU__
{
    UINT32 aulMcsCnt[32];
    UINT32 ulQPSKTotalNum;
    UINT32 ul16QAMTotalNum;
    UINT32 ul64QAMTotalNum;
    UINT32 ulThroughput;
}LPHY_DT_UL_SCHEDULE_STAT_INFO_IND_STRU;

typedef struct __LPHY_DT_HARQ_INFO_CA_IND_STRU__
{
    UINT8  ucCcValidFlg;
	UINT8  ucCcIdx;
	UINT16 usRsv;

    UINT16 usPuschMaxTransNum;
    UINT16 usUlHarqProcessNum;
    UINT16 usDlHarqProcessNum;
    UINT16 usRsv0;
}LPHY_DT_HARQ_INFO_CA_IND_STRU;

typedef struct __LPHY_DT_UL_ACCESS_INFO_IND_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFn;
    INT16  sPrachTransPower;
    UINT16 usRaRntiValue;
}LPHY_DT_UL_ACCESS_INFO_IND_STRU;

typedef struct __LPHY_DT_TA_INFO_IND_STRU__
{
    UINT16   usSFN;
    UINT16   usSubFn;
    UINT16   usTaValue;
    UINT16   usRsv;
    UINT8    ucCcValidFlag;
    UINT8    ucCcIdx;
    INT16    sTimeDeviation;
}LPHY_DT_TA_INFO_IND_STRU;

typedef struct
{
    UINT32 ulTransSuccNum[5];
    UINT32 ulReTransFailNum;
}LPHY_DT_PUSCH_HARQ_BLER_STAT_IND_STRU;


typedef struct
{
    UINT16 usPowerInfoActFlg;
    UINT16 usPuschInfoActFlg;
    LPHY_DT_HARQ_INFO_REQ_STRU stHarqInfoActPara;
    UINT16 usUlAccessInfoActFlg;
    UINT16 usTaInfoActFlg;
    LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU stUlSchedStatActPara;
    LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU stUlPuschHarqBlerStatPara;

}UL_DT_OM_DATA_REQUEST_FLG_STRU;


/* BEGIN: Added by xueqiuyan, 2012/9/13   PN:CMCC_DT*/
typedef struct
{
    UINT32 ulSchedStatCnt;
    UINT32 ulHarqRptCnt;
    UINT32 ulHarqBlerStatCnt;
}UL_DT_OM_DATA_REPORT_COUNT_STRU;
/* END:   Added by xueqiuyan, 2012/9/13 */


/* END:   Added by xueqiuyan, 2012/9/7 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UL_OM_DEF_H__ */

