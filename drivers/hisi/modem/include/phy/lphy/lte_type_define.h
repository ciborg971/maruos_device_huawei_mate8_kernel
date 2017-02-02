

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

#ifndef __LTE_PARA_H__
#define __LTE_PARA_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
    LTEЭ���г���������: 1.4M, 3M, 5M, 10M ,15M ,20M
*/
typedef enum __LTE_BAND_WIDTH_E__
{
    LTE_BAND_WIDTH_1D4M = 0,
    LTE_BAND_WIDTH_3M,
    LTE_BAND_WIDTH_5M,
    LTE_BAND_WIDTH_10M,
    LTE_BAND_WIDTH_15M,
    LTE_BAND_WIDTH_20M,
	LTE_BAND_WIDTH_BUTT
 }LTE_BAND_WIDTH_E;
typedef UINT16 LTE_BAND_WIDTH_ENUM_UINT16;


/*
    LTEЭ���еĶ���ѭ��ǰ׺����: normal or extened.
*/
typedef enum __LTE_CP_TYPE_E__
{
    LTE_CP_TYPE_NORMAL = 0,
    LTE_CP_TYPE_EXTENDED
}LTE_CP_TYPE_E;
typedef UINT16 LTE_CP_TYPE_ENUM_UINT16;


/*
    LTEЭ���ж����֡�ṹ����: fdd or tdd
*/
typedef enum __LTE_FRAME_TYPE_E__
{
    LTE_FRAME_TYPE_FDD = 0,
    LTE_FRAME_TYPE_TDD
}LTE_FRAME_TYPE_E;
typedef UINT16 LTE_FRAME_TYPE_ENUM_UINT16;

typedef enum
{
    RX_PLL_QUERY = 0,
    TX_PLL_QUERY,
    PLL_QUERY_BUTT
}PLL_QUERY_TYPE;
typedef UINT16 PLL_QUERY_TYPE_U16;

typedef enum
{
    PLL_UNLOCK = 0,
    PLL_LOCK,
    PLL_QUERY_FAIL,
    PLL_BUTT
}PLL_STATUS_ENUM;
typedef UINT16 PLL_STATUS_ENUM_U16;


/*
    LTEЭ���й涨��TDD��Ӧ����֡����,�μ�Э��211��4.2��: uplink,special,downlink.
*/
typedef enum __LTE_TDD_SUBFRAME_TYPE_E__
{
    LTE_TDD_SUBFRAME_TYPE_DOWNLINK = 0,
    LTE_TDD_SUBFRAME_TYPE_SPECIAL,
    LTE_TDD_SUBFRAME_TYPE_UPLINK,
    LTE_TDD_SUBFRAME_TYPE_MRS,
    LTE_TDD_SUBFRAME_TYPE_MBSFN,
    LTE_TDD_SUBFRAME_TYPE_BUTT
}LTE_TDD_SUBFRAME_TYPE_E;
typedef UINT16 LTE_TDD_SUBFRAME_TYPE_ENUM_UINT16;


/*
    LTEЭ���й涨��TDD��Ӧ����������֡��ȣ��μ�Э��211 4.2��.
*/
typedef enum __LTE_TDD_UD_CFG_E__
{
    LTE_TDD_UD_CFG_0 = 0,           /* DSUUU DSUUU*/
    LTE_TDD_UD_CFG_1,               /* DSUUD DSUUD*/
    LTE_TDD_UD_CFG_2,               /* DSUDD DSUDD*/
    LTE_TDD_UD_CFG_3,               /* DSUUU DDDDD*/
    LTE_TDD_UD_CFG_4,               /* DSUUD DDDDD*/
    LTE_TDD_UD_CFG_5,               /* DSUDD DDDDD*/
    LTE_TDD_UD_CFG_6                /* DSUUU DSUUD*/
}LTE_TDD_UD_CFG_E;
typedef UINT16 LTE_TDD_UD_CFG_ENUM_UINT16;


/*
    LTEЭ���й涨��TDD��Ӧ��������֡����, ��Э��211 4.2��.
*/
typedef enum __LTE_TDD_SPEC_SUBFRM_CFG_E__
{
    LTE_TDD_SPEC_SUBFRM_CFG_0 = 0,
    LTE_TDD_SPEC_SUBFRM_CFG_1,
    LTE_TDD_SPEC_SUBFRM_CFG_2,
    LTE_TDD_SPEC_SUBFRM_CFG_3,
    LTE_TDD_SPEC_SUBFRM_CFG_4,
    LTE_TDD_SPEC_SUBFRM_CFG_5,
    LTE_TDD_SPEC_SUBFRM_CFG_6,
    LTE_TDD_SPEC_SUBFRM_CFG_7,
    LTE_TDD_SPEC_SUBFRM_CFG_8,
    LTE_TDD_SPEC_SUBFRM_CFG_9
}LTE_TDD_SPEC_SUBFRM_CFG_E;
typedef UINT16 LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16;


/*
    LTEЭ���й涨�ĵ��Ʒ�ʽ: bpsk,qpsk, qam16, qam64
*/
typedef enum __LTE_MODULATION_SCHEME_E__
{
    LTE_MODULATION_SCHEME_BPSK =1,
    LTE_MODULATION_SCHEME_QPSK =2,
    LTE_MODULATION_SCHEME_QAM16=4,
    LTE_MODULATION_SCHEME_QAM64=6,
    LTE_MODULATION_SCHEME_BUTT
}LTE_MODULATION_SCHEME_E;
typedef UINT16 LTE_MODULATION_SCHEME_ENUM_UINT16;

typedef enum __LTE_PHY_CH_TYPE_E__
{
    LTE_PHY_CH_TYPE_PBCH,
    LTE_PHY_CH_TYPE_PCFICH,
    LTE_PHY_CH_TYPE_PDCCH,
    LTE_PHY_CH_TYPE_PHICH,
    LTE_PHY_CH_TYPE_PDSCH,
    LTE_PHY_CH_TYPE_PUCCH,
    LTE_PHY_CH_TYPE_PUSCH,
    LTE_PHY_CH_TYPE_PMCH
}LTE_PHY_CH_TYPE_E;
typedef UINT16 LTE_PHY_CH_TYPE_ENUM_UINT16;

/*
    LTEЭ���й涨��pdsch�ŵ��Ĵ��䷽ʽ����8��: �μ�Э��213 7.1��
*/
typedef enum __LTE_PDSCH_TRANS_SCHEME_E__
{
    LTE_PDSCH_TRANS_SCHEME_PORT0 = 0,           /*1,���Ͷ�ֻ��һ���������ߣ����ø�ģʽ*/
    LTE_PDSCH_TRANS_SCHEME_SFBC,                /*2,���Ͷ���2����4����������ʱ���Բ��ø��ִ���ģʽ*/
    LTE_PDSCH_TRANS_SCHEME_OPEN_LOOP_SM,        /*3,�����ռ临��ģʽ*/
    LTE_PDSCH_TRANS_SCHEME_CLOSE_LOOP_SM,       /*4,�ջ��ռ临��ģʽ*/
    LTE_PDSCH_TRANS_SCHEME_MU_MIMO,             /*5,���û�MIMO*/
    LTE_PDSCH_TRANS_SCHEME_CLOSE_LOOP_RI_1,     /*6,�ջ� Rank=1 Ԥ����ģʽ*/
    LTE_PDSCH_TRANS_SCHEME_PORT5,               /*7,�����߿ڴ���ģʽ��port5*/
    LTE_PDSCH_TRANS_SCHEME_PORT78,              /*8,�����߿ڴ���ģʽ��port7,port8*/
    LTE_PDSCH_TRANS_SCHEME_PORT7,               /*undefined*/
    LTE_PDSCH_TRANS_SCHEME_PORT8                /*undefined*/
}LTE_PDSCH_TRANS_SCHEME_E;
typedef UINT16 LTE_PDSCH_TRANS_SCHEME_ENUM_UINT16;


/*
    LTE�涨������״̬,�μ�Э��133����
*/
typedef enum __LTE_RRC_STATE_E__
{
    LTE_RRC_STATE_NULL = 0,
    LTE_RRC_STATE_IDLE,
    LTE_RRC_STATE_CONNECTED,
    LTE_RRC_STATE_BUTT
}LTE_RRC_STATE_E;
typedef UINT16 LTE_RRC_STATE_ENUM_UINT16;


/*
    LTE�涨��drx״̬,�μ�Э��321����331
*/
typedef enum __LTE_DRX_STATE_E__
{
    LTE_DRX_STATE_NO,
    LTE_DRX_STATE_YES,
}LTE_DRX_STATE_E;
typedef UINT16 LTE_DRX_STATE_ENUM_UINT16;

typedef enum __LTE_DRX_TIMING_STATE_E__
{
    LTE_DRX_STATE_NO_PRESYNC,
    LTE_DRX_STATE_YES_PRESYNC
}LTE_DRX_TIMING_STATE_E;
typedef UINT16 LTE_DRX_TIMING_STATE_ENUM_UINT16;

typedef enum __LTE_DRX_PERIOD_E__
{
    LTE_DRX_PERIOD_320MS=0,
    LTE_DRX_PERIOD_640MS,
    LTE_DRX_PERIOD_1280MS,
    LTE_DRX_PERIOD_2560MS,
}LTE_DRX_PERIOD_E;
typedef UINT16 LTE_DRX_PERIOD_ENUM_UINT16;



/*
    GAP��ص�״̬����:
        �Ǽ���:     �ϵ����ǷǼ���״̬��������ԭ��֪ͨgap�ͷž��ǷǼ���״̬;
        ����:       �յ�gap����֪ͨ���ڲ����Ǽ���״̬;
        INVALID:    δ�յ�����ԭ�����ԭ��֪ͨ����gap���ҵ�ǰ��֡��������gap�����ڼ�;
        VALID:      ԭ��֪ͨ����gap�󣬲��ҵ�ǰ��֡����gap�����ڼ�
*/
typedef enum __LTE_GAP_ACTIVE_STATE_E__
{
    LTE_GAP_ACTIVE_STATE_NO,                          /*GAP�Ǽ���״̬*/
    LTE_GAP_ACTIVE_STATE_YES                          /*GAP����״̬*/
}LTE_GAP_ACTIVE_STATE_E;
typedef UINT16 LTE_GAP_ACTIVE_STATE_ENUM_UINT16;

typedef enum __LTE_GAP_STATE_E__
{
    LTE_GAP_STATE_INVALID,                              /*GAPδ���������GAP���������Ч(��gap��֡)*/
    LTE_GAP_STATE_VALID                                /*GAP����������Ч*/
}LTE_GAP_STATE_E;
typedef UINT16 LTE_GAP_STATE_ENUM_UINT16;

/*
    MBSFN��ص�״̬����:
        �Ǽ���:     �ϵ����ǷǼ���״̬��������ԭ��֪ͨMBSFN�ͷž��ǷǼ���״̬;
        ����:       �յ�MBSFN����ԭ����ڲ����Ǽ���״̬;
        INVALID:    δ�յ�����ԭ�����ԭ��֪ͨ����MBSFN���ҵ�ǰ��֡��������MBSFN�����ڼ�;
        VALID:      ԭ��֪ͨ����MBSFN�󣬲��ҵ�ǰ��֡����MBSFN�����ڼ�
*/
typedef enum __LTE_MBSFN_ACTIVE_STATE_E__
{
    LTE_MBSFN_ACTIVE_STATE_NO,                          /*MBSFN�Ǽ���״̬*/
    LTE_MBSFN_ACTIVE_STATE_YES                          /*MBSFNԭ�Ｄ����*/
}LTE_MBSFN_ACTIVE_STATE_E;
typedef UINT16 LTE_MBSFN_ACTIVE_STATE_ENUM_UINT16;

typedef enum __LTE_MBSFN_STATE_E__
{
    LTE_MBSFN_STATE_INVALID,                            /*MBSFN���������Ч(��MBSFN��֡)*/
    LTE_MBSFN_STATE_VALID                              /*MBSFN����������Ч*/
}LTE_MBSFN_STATE_E;
typedef UINT16 LTE_MBSFN_STATE_ENUM_UINT16;


/*
    LTE�涨��ϵͳ֡�š���֡�š����ű�ʶ���μ�Э��211��
*/
#define LTE_TIMING_MAX_MFN                                      1223
typedef struct __LTE_TIMING_INFO_STRU__
{
    UINT16                                  usSysFrmNum;        /*ϵͳ֡��: 0~1023*/
    UINT16                                  usSubFrmNum;        /*��֡��: 0~9 */
    UINT16                                  usSymNum;           /*����: 0~13 or 0~11*/
    UINT16                                  usAfn;              /*AFN: 0~1023*/
    UINT16                                  usMfn;              /*MFN: 0~1223*/
    UINT16                                  usReserved;
}LTE_TIMING_INFO_STRU;


/*
    �㷨�涨���ŵ��ռ������:
*/
typedef enum __LTE_CHAN_SPACE_CORR__
{
    LTE_CHAN_SPACE_CORR_HIGH = 0,
    LTE_CHAN_SPACE_CORR_MID,
    LTE_CHAN_SPACE_CORR_LOW
} LTE_CHAN_SPACE_CORR_ENUM;
typedef UINT8 LTE_CHAN_SPACE_CORR_ENUM_UINT8;


/*
    С����Ϣ�ṹ�嶨��
*/

typedef enum __CC_STATE_ENUM__
{
	CC_INVALID,
	CC_EXIST,
	CC_VALID,
	CC_STATE_BUTT
}CC_STATE_ENUM;

typedef UINT16	CC_STATE_ENUM_UINT16;

typedef struct __LTE_CELL_INFO_STRU__
{
	CC_STATE_ENUM_UINT16                    enCcState;          /*�ز�״̬*/
    UINT16                                  usCellId;           /*С��id = 3*nid2 + nid1*/
    UINT16                                  usFreqInfo;         /*С��Ƶ��*/
    UINT16									usBandNum;
    UINT8                                   ucTransAntNum;      /*����������*/
    UINT8                                   ucRecvAntNum;       /*����������*/
    LTE_CP_TYPE_ENUM_UINT16                 enCpType;           /*cp����*/
    LTE_BAND_WIDTH_ENUM_UINT16              enDlBandWidth;      /*eNodeB���д���*/
    LTE_FRAME_TYPE_ENUM_UINT16              enFrameType;        /*֡����:FDD or TDD*/
    LTE_TDD_UD_CFG_ENUM_UINT16              enUDCfg;            /*TDD֡���ͣ���������֡���*/
    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16     enSpecSubframeCfg;  /*TDD֡���ͣ�������֡��ʽ*/
    UINT16                                  usBSFreqForAgc;
    UINT16                                  usRsv;
}LTE_CELL_INFO_STRU;

typedef struct __LTE_DUAL_PSS_SCAN_INFO_STRU__
{
    INT32                                   ssOffSet0;           /*Ƶ����1*/
    INT32                                   ssOffSet1;           /*Ƶ����2*/
    UINT16                                  usFreqInfo0;
    UINT16                                  usFreqInfo1;
    UINT16                                  usDualPssFlag;       /*����ɨƵ��־λ*/
    UINT16                                  usBSFreqForAgc;
}LTE_DUAL_PSS_SCAN_INFO_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LTE_PARA_H__ */
