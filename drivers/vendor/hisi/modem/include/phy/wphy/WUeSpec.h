/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : WUeSpec.h
  �� �� ��   : ����
  ��    ��   : Jinying
  ��������   : 2006��9��2��
  ����޸�   :
  ��������   : WUe�Ĳ�Ʒ�����ͷ�ļ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��9��2��
    ��    ��   : Jinying
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Hi_Config.h"
#include "product_config.h"



#ifndef __WUESPEC_H__
#define __WUESPEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PS_WUE_CIPHER_KEY_LEN                   (16)    /* ������Կ���� */

#define PS_WUE_MAX_FORBLA_NUM                   (32)    /* ��ֹע���������ĸ��� */

#define PS_WUE_MAX_HIGH_PLMN_NUM                (16)    /* ��������PLMN�������� */
#define PS_WUE_MAX_LOW_PLMN_NUM                 (16)    /* ��������PLMN�������� */

#define PS_WUE_MAX_NAS_GSM_MAP_NUM              (8)     /* Э��ֵ 8             */
#define PS_WUE_MAX_NAS_MSG_LEN                  (4095)  /* Э��ֵ 4095,NAS��Ϣ��󳤶�        */

#define PS_WUE_MAX_MULTI_PLMN_NUM               (5)     /* Э��ֵ 5,MultiplePLMN_List_r6*/
#define PS_WUE_MAX_PLMN_NUM                     (PS_WUE_MAX_MULTI_PLMN_NUM + 1)
                                                        /* MULTI PLMN����MIB��Я����PLMN */

#define PS_WUE_MAX_AC_NUM                       (16)    /* Э��ֵ maxAC 16  */
#define PS_WUE_MAX_ADD_MEAS_NUM                 (4)     /* Э��ֵ maxAdditionalMeas 4     */
#define PS_WUE_MAX_ASC_NUM                      (8)     /* Э��ֵ maxASC 8     */
#define PS_WUE_MAX_ASC_MAP_NUM                  (7)     /* Э��ֵ maxASCmap 7     */
#define PS_WUE_MAX_ASC_PERSIST_NUM              (6)     /* Э��ֵ maxASCpersist 6     */
#define PS_WUE_MAX_CCTRCH_NUM                   (1)     /* Э��ֵ maxCCTrCH 8     */  /* ����ֻ��ָR99��CCTRCH���� */
#define PS_WUE_MAX_SCCPCH_CCTRCH_NUM            (2)     /* ֧��cbs��pi���趨Ϊ2 */
#define PS_WUE_MAX_CELL_MEAS_NUM                (32)    /* Э��ֵ maxCellMeas 32    */
#define PS_WUE_MAX_CELL_MEAS1_NUM               (31)    /* Э��ֵ maxCellMeas_1 31    */
#define PS_WUE_MAX_CN_DOMAINS_NUM               (2)     /* Э��ֵ maxCNdomains 4     */  /* CS and PS */
#define PS_WUE_MAX_DPCH_DL_CHAN_NUM             (1)     /* Э��ֵ maxDPCH_DLchan 8     */  /* Asic spec */
#define PS_WUE_MAX_DPDCH_UL_NUM                 (1)     /* Э��ֵ maxDPDCH_UL 6     */
#define PS_WUE_MAX_DRAC_CLASSES_NUM             (8)     /* Э��ֵ maxDRACclasses 8     */
#define PS_WUE_MAC_E_DCH_MACD_FLOW_NUM          (8)     /* Э��ֵ maxE_DCHMACdFlow 8,E DCH���ĸ��� */
#define PS_WUE_MAX_E_DCH_MACD_FLOW1_NUM         (7)     /* Э��ֵ maxE_DCHMACdFlow_1 7     */
#define PS_WUE_MAX_E_DCH_RL_NUM                 (4)     /* Э��ֵ maxEDCHRL 4     */
#define PS_WUE_MAX_FACH_PCH_NUM                 (8)     /* Э��ֵ maxFACHPCH 8     */
#define PS_WUE_MAX_FREQ_NUM                     (8)     /* Э��ֵ maxFreq 8     */
#define PS_WUE_MAX_FREQ_BANDS_FDD_NUM           (2)     /* Э��ֵ maxFreqBandsFDD 8     */  /* 1900M and 2100M */
#define PS_WUE_MAX_FREQ_BANDS_FDD_EXT_NUM       (15)    /* Э��ֵ maxFreqBandsFDD_ext 15    */
#define PS_WUE_MAX_FREQ_BANDS_GSM_NUM           (3)     /* Э��ֵ maxFreqBandsGSM 16    */  /* 850M 900M 1800M */
#define PS_WUE_MAX_GERAN_SI_NUM                 (8)     /* Э��ֵ maxGERAN_SI 8     */
#define PS_WUE_MAX_GSM_TARGET_CELLS_NUM         (32)    /* Э��ֵ maxGSMTargetCells 32    */
#define PS_WUE_MAX_H_PROCESSES_NUM              (8)     /* Э��ֵ maxHProcesses 8     */
#define PS_WUE_MAX_HS_SCCHS_NUM                 (4)     /* Э��ֵ maxHSSCCHs 4     */
#define PS_WUE_MAX_INTER_SYS_MSGS_NUM           (2)     /* Э��ֵ maxInterSysMessages 4     */
#define PS_WUE_MAX_LOCH_PER_RLC_NUM             (2)     /* Э��ֵ maxLoCHperRLC 2,ÿ��RLC������ӳ����߼��ŵ����� */
#define PS_WUE_MAX_MAC_D_PDU_SIZES_NUM          (8)     /* Э��ֵ maxMAC_d_PDUsizes 8     */
#define PS_WUE_MAX_MEAS_EVT_NUM                 (8)     /* Э��ֵ maxMeasEvent 8     */
#define PS_WUE_MAX_MEAS_INTERVALS_NUM           (3)     /* Э��ֵ maxMeasIntervals 3     */
#if (FEATURE_ON == FEATURE_DC_UPA)
#define PS_WUE_MAX_MEAS_EVT_ON_SEC_UL_FREQ_NUM  (8)     /* Э��ֵ maxMeasEventOnSecULFreq 8     */
#endif
#define PS_WUE_MAX_MEAS_PAR_EV_NUM              (2)     /* Э��ֵ maxMeasParEvent 2 */
#define PS_WUE_MAX_NUM_GSM_FREQ_RANGES_NUM      (32)    /* Э��ֵ maxNumGSMFreqRanges 32    */
#define PS_WUE_MAX_NUM_FDD_FREQS_NUM            (8)     /* Э��ֵ maxNumFDDFreqs 8     */
#define PS_WUE_MAX_NO_OF_MEAS_NUM               (16)    /* Э��ֵ maxNoOfMeas 16    */
#define PS_WUE_MAX_OTHER_RAT_NUM                (1)     /* Э��ֵ maxOtherRAT 15    */   /* GSM */
#define PS_WUE_MAX_OTHER_RAT16_NUM              (1)     /* Э��ֵ maxOtherRAT_16 16    */   /* GSM */
#define PS_WUE_MAX_PAGE1_NUM                    (8)     /* Э��ֵ maxPage1 8     */
#define PS_WUE_MAX_PDCP_ALGO_TYPE_NUM           (2)     /* Э��ֵ maxPDCPAlgoType 8,PDCPͷѹ���㷨 */
#define PS_WUE_MAX_PRACH_NUM                    (16)    /* Э��ֵ maxPRACH 16������PRACHѡ��ÿ��ֻѡ��һ��PRACH������С���Ժ�����ѡ��    */
#define PS_WUE_MAX_QUEUE_NUM                    (8)     /* Э��ֵ maxQueueIDs 8 ��HSDPA���Ķ����� */

#define PS_WUE_MAX_CS_RAB_NUM                   (2)     /* 1��AMR��1��CSD */
#define PS_WUE_MAX_PS_RAB_NUM                   (5)     /* 5��PSҵ�� GCF7.1.5.2 5��PS RB��ӳ�䵽HSDPA*/
#define PS_WUE_MAX_RAB_NUM                      (PS_WUE_MAX_CS_RAB_NUM + PS_WUE_MAX_PS_RAB_NUM)
                                                        /* Э��ֵ maxRABsetup 16,���������RAB��        */
#define PS_WUE_MAX_SRB_NUM                      (4)     /* 4��SRB */
#define PS_WUE_MAX_AMR_RB_NUM                   (3)     /* AMR����Ӧ3��RB */
#define PS_WUE_MAX_CS_RB_NUM                    (PS_WUE_MAX_AMR_RB_NUM + 1)     /* 3��AMR/1��CSD */
#define PS_WUE_MAX_PS_RB_NUM                    (5)     /* 5��PS */

#define PS_WUE_MAX_RB_NUM                       (PS_WUE_MAX_SRB_NUM + PS_WUE_MAX_CS_RB_NUM + PS_WUE_MAX_PS_RB_NUM)     /* Э��ֵ maxRB 32 */
#define PS_WUE_MAX_RB_ALL_RABS_NUM              (PS_WUE_MAX_CS_RB_NUM + PS_WUE_MAX_PS_RB_NUM)
                                                        /* Э��ֵ maxRBallRABs 27    */  /* 4 CS + 2 PS */
#define PS_WUE_MAX_E_DCH_LOCH_NUM               (12)    /* 4������RB,5��PS��RB,3��CS,������1��AM RB��Ӧ2��LOCH�����,GCF14_7_7����4��SRB+3��PS RB��ӳ�䵽EDCH*/
#define PS_WUE_MAX_RB_MUX_OP_NUM                (4)     /* Э��ֵ maxRBMuxOptions 8     */
#define PS_WUE_MAX_RB_PER_RAB_NUM               (3)     /* Э��ֵ maxRBperRAB 8,ÿ��RAB���������RB��  */  /* AMR */
#define PS_WUE_MAX_RB_PER_TRCH_NUM              (4)     /* Э��ֵ maxRBperTrCh 16     */  /* SRB */
#define PS_WUE_MAX_RPT_GSM_CELLS_NUM            (8)     /* Э��ֵ maxReportedGSMCells 8     */
#define PS_WUE_MAX_RL_NUM                       (6)     /* Э��ֵ maxRL 8     */  /* ASIC spec */
#define PS_WUE_MAX_RL_MINUS1_NUM                (5)     /* Э��ֵ maxRL_1 7   */
#define PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH    (32)    /* Э��ֵ maxRLCPDUsizePerLogChan 32,ÿ���߼��ŵ����õ�RLC SIZE�¸��� */
#define PS_WUE_MAX_SAT_NUM                      (16)     /* Э��ֵ maxSat 16    */
#define PS_WUE_MAX_SVGLOBALHEALTH_NUM           (46)    /* Э��ֵ maxSvGlobalHealth 46    */
#define PS_WUE_MAX_SCCPCH_NUM                   (1)     /* Э��ֵ maxSCCPCH 16    */
#define PS_WUE_MAX_SIB_NUM                      (32)    /* Э��ֵ maxSIB 32    */
#define PS_WUE_MAX_SIB_FACH_NUM                 (8)     /* Э��ֵ maxSIB_FACH 8     */
#define PS_WUE_MAX_SIB_PER_MSG_NUM              (16)    /* Э��ֵ maxSIBperMsg 16    */
#define PS_WUE_MAX_SRB_SETUP_NUM                (5)     /* Э��ֵ maxSRBsetup 8     */
#define PS_WUE_MAX_SYS_CAPAB_NUM                (2)     /* Э��ֵ maxSystemCapability 16    */
#define PS_WUE_MAX_TF_NUM                       (32)    /* Э��ֵ maxTF 32,������ʽ */

#define PS_WUE_MAX_DL_TFC_NUM                   (128)   /* Э��ֵ maxTFC 1024  */
#define PS_WUE_MAX_UL_TFC_NUM                   (128)   /* Э��ֵ maxTFC 1024  */
#define PS_WUE_MAX_TFC_NUM                      (128)   /* Э��ֵ maxTFC 1024  */

#define PS_WUE_MAX_REF_E_TFCI_NUM               (8)     /* Э��ֵ 8 E_DPDCH_Reference_E_TFCIList */
#define PS_WUE_MAX_TFC_SUB_NUM                  (128)   /* Э��ֵ maxTFCsub 1024  */

#define PS_WUE_MAX_TGPS_NUM                     (6)     /* Э��ֵ maxTGPS 6     */
#define PS_WUE_MAX_TGPL                         (144)   /* Э��ֵ��144 */
#define PS_WUE_MAX_TGPRC                        (511)   /* Э��ֵ��511 */

#define PS_WUE_MAX_DCH_NUM                      (8)     /* 3CS AMR + 3PS + 1SIG */

#define PS_WUE_MAX_TRCH_NUM                     (PS_WUE_MAX_DCH_NUM + 1 + 1)
                                                        /* Э��ֵ maxTrCH 32����1HSDSCH,1E DCH,BBP��� */

#define PS_WUE_MAX_MEAS_TRCH_NUM                (PS_WUE_MAX_DCH_NUM)
                                                        /* Э��ֵ maxTrCH 32��������Ϊ6��DCH����1��RACH */

#define PS_WUE_MAX_URA_NUM                      (8)     /* Э��ֵ maxURA 8     */
#define PS_WUE_MAX_URNTI_GROUP_NUM              (8)     /* Э��ֵ maxURNTI_Group 8     */

#define PS_WUE_MAX_LOCH_NUM                     (15)    /* 2����AM SRB + 3��AMR + (2��PS RB + 3��AM SRB) * 2(LOCH PER RB) */
#define PS_WUE_MIN_LOCH_ID                      (1)
#define PS_WUE_MAX_LOCH_ID                      (15)    /* Э��ֵ 15,LogicalChannelList��explicitList�����ӳ��rb�� */
#define PS_WUE_CCCH_LOCH_ID_OVER_EDCH           (15)    /* CCCH�߼��ŵ�ID�̶���д15 */
#define PS_WUE_MIN_TRCH_ID                      (1)
#define PS_WUE_MAX_TRCH_ID                      (32)    /* Э��ֵ Integer(1..32)*/
#define PS_PROTOCOL_MAX_OTHER_RAT_NUM           (15)    /* Э��ֵ maxOtherRAT 15  UE������Ӧ:PS_WUE_MAX_OTHER_RAT_NUM:1  */

/*V3 R7_7C1 Start */
#define PS_WUE_INVALID_TRCH_ID                  (0xFFFF)
#define PS_WUE_MIN_HS_FLOW_ID                   (0)
#define PS_WUE_MAX_HS_FLOW_ID                   (7)
#define PS_WUE_MIN_HS_QUEUE_ID                  (0)
#define PS_WUE_MAX_HS_QUEUE_ID                  (7)
/* V3 R7_7C1 End */

/* E-RACH Add Begin */
#define PS_WUE_MAX_EDCHS                        (32)    /* Э��ֵ 32,maxEDCHs*/

/* E-RACH Add End */
#if (FEATURE_ON == FEATURE_DC_MIMO)
#define PS_WUE_MAX_HS_CATEGORY_NUM              (28)    /* UE ����HSDPA Category Num�� ������չ��cate */
#else
#define PS_WUE_MAX_HS_CATEGORY_NUM              (24)    /* UE ����HSDPA Category Num�� ������չ��cate */
#endif /* FEATURE_DC_MIMO */
#define PS_WUE_MAX_CRC_LEN                      (3)     /* ��λ:�ֽڣ�CRC bit����ȡֵΪ:0��8��12��16��24 */
#define PS_WUE_MAX_TB_CNT                       (32)    /* Э��ֵ���512,TB��Ŀ,HI4131 ������32*/
#define PS_WUE_MAX_COMM_HRNTI_NUM               (4)     /* maxCommonHRNTI,Э��ֵ 4 */
#define PS_WUE_MAX_COMM_QUEUE_ID_NUM            (2)     /* maxCommonQueueID ,Э��ֵ 2 */

#define PS_WUE_RSSI_THRESHOLD                   (-960)  /* �·����������RSSI�������ϱ����� */




/* ����ΪĿǰ��֧�ֵĹ�񣬰���TDD��MBMS */
#if 0
#define PS_WUE_HI_PDSCH_ID                      (1)     /* Э��ֵ 64    */
#define PS_WUE_HI_PUSCH_ID                      (1)     /* Э��ֵ 64    */
#define PS_WUE_MAX_CPCH_SETS                    (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_FREQ_BANDS_TDD               (1)     /* Э��ֵ 4     */
#define PS_WUE_MAX_HSDSCHTB_INDEX_TDD384        (1)     /* Э��ֵ 512   */   /* tdd not support */
#define PS_WUE_MAX_HSDSCHTB_INDEX               (1)     /* Э��ֵ maxHSDSCHTBIndex 64    */  /* not use */
#define PS_WUE_MAX_MBMS_COMM_CCTRCH             (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_MBMS_COMM_PHY_CH             (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_MBMS_COMM_RB                 (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_MBMS_COMM_TRCH               (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_MBMS_FREQ                    (1)     /* Э��ֵ 4     */
#define PS_WUE_MAX_MBMS_L1_CP                   (1)     /* Э��ֵ 4     */
#define PS_WUE_MAX_MBM_SSERV_CNT                (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_MBM_SSERV_MODIF              (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_MBM_SSERV_SCHED              (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_MBM_SSERV_UNMODIF            (1)     /* Э��ֵ 64    */
#define PS_WUE_MAX_MBMS_TRANSMIS                (1)     /* Э��ֵ 4     */
#define PS_WUE_MAX_NUM_CDMA2000_FREQS           (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_NUM_TDD_FREQS                (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_PCPCH_AP_SIG                 (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_PCPCH_AP_SUB_CH              (1)     /* Э��ֵ 12    */
#define PS_WUE_MAX_PCPCH_CD_SIG                 (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_PCPCH_CD_SUB_CH              (1)     /* Э��ֵ 12    */
#define PS_WUE_MAX_PCPCH_SF                     (1)     /* Э��ֵ 7     */
#define PS_WUE_MAX_PCPCHS                       (1)     /* Э��ֵ 64    */
#define PS_WUE_MAX_PDSCH                        (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_PDSCH_TFCI_GROUPS            (1)     /* Э��ֵ 256   */
#define PS_WUE_MAX_PRACH_FPACH                  (1)     /* Э��ֵ 8     */  /* TDD */
#define PS_WUE_MAX_PREDEF_CFG                   (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_PUSCH                        (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_RAT_NUM                      (2)     /* Э��ֵ maxRAT 16    */
#define PS_WUE_MAX_RB_PER_TRCH                  (1)     /* Э��ֵ 16     */ /* MBMS */
#define PS_WUE_MAX_RFC3095_CID                  (1)     /* Э��ֵ 16384 */
#define PS_WUE_MAX_ROHC_PACKET_SIZES_R4         (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_ROHC_PROFILE_R4              (1)     /* Э��ֵ 8     */
#define PS_WUE_MAX_TF_CPCH                      (1)     /* Э��ֵ 16    */
#define PS_WUE_MAX_TFCI2_COMBS                  (1)     /* Э��ֵ 512   */  /* dsch */
#define PS_WUE_MAX_TRCH_PRECONF                 (1)     /* Э��ֵ 32    */
#define PS_WUE_MAX_TS                           (1)     /* Э��ֵ 14    */
#define PS_WUE_MAX_TS1                          (1)     /* Э��ֵ 13    */
#define PS_WUE_MAX_TS2                          (1)     /* Э��ֵ 12    */
#define PS_WUE_MAX_TS_LCR                       (1)     /* Э��ֵ 6     */
#define PS_WUE_MAX_TS_LCR1                      (1)     /* Э��ֵ 5     */
#endif

/* RB_Identity ::=                        INTEGER (1..32) */
#define PS_WUE_MIN_RB_ID                        (1)     /* INTEGER (1..32) */
#define PS_WUE_MIN_T_RB_ID                      (5)     /* ��СTRAFFIC RB ID */
#define PS_WUE_MAX_RB_ID                        (32)    /* INTEGER (1..32) */

#define PS_WUE_MIN_RAB_ID                       (1)
#define PS_WUE_MAX_RAB_ID                       (16)

/* ѡ���DRX���ȣ�����CBS��Э����256 */
#define PS_WUE_MAX_DRXSEL_LEN                   (255)

/* UE������� */

/* ����������洢��NV���� */
#if 1
/* UE���������͹��� */
#define PS_WUE_MAX_TX_PWR                       (24)                            /* 25.101 6.2.1: Power Class 3              */

/*****************************************************************************
 �ṹ��    : PS_WUE_MULTI_RAT_GSM_SUPPT
             PS_WUE_MULTI_CARRIER_SUPPT
 ASN.1���� : supportOfGSM                        BOOLEAN,
             supportOfMulticarrier               BOOLEAN
 �ṹ˵��  : �Ƿ�֧����ϵͳ�Ͷ��ز�
*****************************************************************************/
#define PS_WUE_MULTI_RAT_GSM_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT: support GSM ,         PS_CAP_UNSUPPORT: not support GSM                       */
#define PS_WUE_MULTI_CARRIER_SUPPT              PS_CAP_UNSUPPORT                /* PS_CAP_SUPPORT: support multi carrier,PS_CAP_UNSUPPORT: not support multi carrier             */

/*****************************************************************************
 �ṹ��    :PS_WUE_MEAS_DL_COMPRS_TDD_SUPPT
            PS_WUE_MEAS_DL_COMPRS_FDD_SUPPT
            PS_WUE_MEAS_DL_COMPRS_GSM900_SUPPT
            PS_WUE_MEAS_DL_COMPRS_DCS1800_SUPPT
            PS_WUE_MEAS_DL_COMPRS_GSM1900_SUPPT
            PS_WUE_MEAS_DL_COMPRS_MULTI_CARRIER_SUPPT

            PS_WUE_MEAS_UL_COMPRS_TDD_SUPPT
            PS_WUE_MEAS_UL_COMPRS_FDD_SUPPT
            PS_WUE_MEAS_UL_COMPRS_GSM900_SUPPT
            PS_WUE_MEAS_UL_COMPRS_DCS1800_SUPPT
            PS_WUE_MEAS_UL_COMPRS_GSM1900_SUPPT
            PS_WUE_MEAS_UL_COMPRS_MULTI_CARRIER_SUPPT

 ASN.1���� :fdd_Measurements                    BOOLEAN,
            -- TABULAR: The IEs tdd_Measurements, gsm_Measurements and multiCarrierMeasurements
            -- are made optional since they are conditional based on another information element.
            -- Their absence corresponds to the case where the condition is not true.
            tdd_Measurements                    BOOLEAN                                OPTIONAL,
            gsm_Measurements                    GSM_Measurements                    OPTIONAL,
                GSM_Measurements ::=                SEQUENCE {
                    gsm900                                BOOLEAN,
                    dcs1800                                BOOLEAN,
                    gsm1900                                BOOLEAN
                }
            multiCarrierMeasurements            BOOLEAN                                OPTIONAL

 �ṹ˵��  : ֧�ֵ�ѹģ��������
*****************************************************************************/
#define PS_WUE_MEAS_DL_COMPRS_TDD_SUPPT                     PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_DL_COMPRS_FDD_SUPPT                     PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_DL_COMPRS_GSM900_SUPPT                  PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_DL_COMPRS_DCS1800_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_DL_COMPRS_GSM1900_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_DL_COMPRS_MULTI_CARRIER_SUPPT           PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */

#define PS_WUE_MEAS_UL_COMPRS_TDD_SUPPT                     PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_UL_COMPRS_FDD_SUPPT                     PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_UL_COMPRS_GSM900_SUPPT                  PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_UL_COMPRS_DCS1800_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_UL_COMPRS_GSM1900_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#define PS_WUE_MEAS_UL_COMPRS_MULTI_CARRIER_SUPPT           PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:֧��    PS_CAP_UNSUPPORT:��֧��                       */
#endif

/*==============================================================================
                        �洢�ڱ��ص�UE�����궨��=
==============================================================================*/
/* PDCP capability */
#define PS_WUE_CAP_LOSSLESS_SRNS_RELOC_SUPPT                PS_CAP_SUPPORT      /* PS_CAP_SUPPORT : SUPPORT                          */

#define PS_WUE_CAP_LOSSLESS_DL_RLC_PDU_SIZE_CHG_SUPPT       PS_CAP_SUPPORT      /* PS_CAP_SUPPORT : SUPPORT                          */
#define ASN1_LOSSLESS_DL_RLC_PDU_SIZE_CHG                   EN_ENC_PDCP_CAPAB_R5_EXT2_LOSSLESS_DLRLC_PDU_SIZE_CHG_TRUE

#define PS_WUE_CAP_RFC2507_SUPPT                            PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT : SUPPORT                          */

#define PS_WUE_CAP_RFC3095_SUPPT                            PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */

#define PS_WUE_CAP_MAX_ROHC_CTX_SESSION                     PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */
#define ASN1_MAX_ROHC_CTX_SESSION                           EN_ENC_MAX_ROHC_CONTEXT_SESSIONS_R4_BUTT/* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */

#define PS_WUE_CAP_REVERSE_DECOMPRS_DEP                     PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */

#define PS_WUE_CAP_RFC3095_CTX_RELOC                        PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */

#define PS_WUE_CAP_REVERSE_DECOMPRS_SUPPT                   PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT �˴���Ԥ�����ֲ�֧��  */

#define PS_WUE_CAP_MAX_HC_CONTEXT_SPACE                     8192                /* Э��ֵ : 512/1024/2048/4096/8192           */
#define ASN1_MAX_HC_CONTEXT_SPACE                           EN_ENC_MAX_HC_CONTEXT_SPACE_BY8192

/* RLC capability */
/*****************************************************************************
 �ṹ��    : PS_WUE_MAX_RLC_AM_ENTITY_CNT
 ASN.1���� : MaximumAM_EntityNumberRLC_Cap
             am4, am5, am6, am8, am16, am30
 �ṹ˵��  : 3��AMҵ��RB,���RB2-RB4 ��������RB,����6��AM RB
              25.306 R9Э��Table 5.1b������8��AM RB
*****************************************************************************/
#define PS_WUE_MAX_RLC_AM_ENTITY_CNT            (8)
#define ASN1_MAX_RLC_AM_ENTITY_CNT              EN_ENC_MAX_AM_ENTITY_NUM_RLC_CAP_AM8

/*****************************************************************************
 �ṹ��    : PS_WUE_MAX_RLC_AM_WIN_SIZE
 ASN.1���� : MaximumRLC_WindowSize ::=            ENUMERATED { mws2047, mws4095 }
 �ṹ˵��  :
*****************************************************************************/
#define PS_WUE_MAX_RLC_AM_WIN_SIZE              (2047)
#define ASN1_MAX_RLC_AM_WIN_SIZE                EN_ENC_MAX_RLC_WIN_SIZE_MWS2047

/*****************************************************************************
 �ṹ��    : PS_WUE_MAX_TOTAL_AM_RLC_BUFFER_SIZE
 ASN.1���� : TotalRLC_AM_BufferSize
             kb10, kb50, kb100, kb150, kb500, kb1000
 �ṹ˵��  : R3,R4��������Total receiving and transmitting RLC AM buffer
*****************************************************************************/
#define PS_WUE_MAX_TOTAL_AM_RLC_BUFFER_SIZE     (150)
#define ASN1_TOTAL_RLC_AM_BUF_SIZE              EN_ENC_TOTAL_RLC_AM_BUF_SIZE_KB150

/*****************************************************************************
 �ṹ��    : PS_WUE_MAX_TOTAL_AM_RLC_AND_MAC_HS_BUFFER_SIZE
 ASN.1���� : TotalRLC_AM_BufferSize_r5_ext
             kb200, kb300, kb400, kb750
 �ṹ˵��  : R5��������������MAC HS�Ļ���t
             Total receiving and transmitting RLC AM buffer and
             MAC-hs reordering buffer capability in kBytes.
             Note 1.
             The IE "Total RLC AM buffer size" values 200, 300, 400
             and 750 are not used in the INTER RAT HANDOVER INFO message.
*****************************************************************************/
#define PS_WUE_MAX_TOTAL_AM_RLC_AND_MAC_HS_BUFFER_SIZE      (750)
#define ASN1_TOTAL_RLC_AM_AND_MAC_HS_BUF_SIZE        EN_ENC_TOTAL_RLC_AM_BUF_SIZE_R5_EXT_KB750

/*****************************************************************************
 �ṹ��    : PS_WUE_TWO_LOGIC_CHL_SUPPT
 ASN.1���� : supportOfTwoLogicCh                        BOOLEAN,
 �ṹ˵��  : �Ƿ�֧�������߼��ŵ�
*****************************************************************************/
#define PS_WUE_TWO_LOGIC_CH_SUPPT               PS_CAP_UNSUPPORT                  /* PS_CAP_SUPPORT: support ,   PS_CAP_UNSUPPORT: not support   */

/* Transport channel capability */
#define PS_WUE_CAP_MAX_NO_BITS_RECV             (6400)                          /* Max no of bits received                    */
#define ASN1_MAX_NO_BITS_RECV                   EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_CONV_CODE_BITS_RECV      (640)                           /* Max convolutionally coded bits received    */
#define ASN1_MAX_CONV_CODE_BITS_RECV            EN_ENC_MAX_NO_BITS_B640

#define PS_WUE_CAP_TURBO_DEC_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT : Support turbo decoding    */

#define PS_WUE_CAP_MAX_TURB_CODE_BITS_RECV      (6400)                          /* Max turbo coded bits received              */
#define ASN1_MAX_TURB_CODE_BITS_RECV            EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_SIMU_TRANS_CH_DL         (8)                             /* Max Simultaneous TrChs DL                  */
#define ASN1_MAX_SIMU_TRANS_CH_DL               EN_ENC_MAX_SIMUL_TRANS_CHS_DL_E8

#define PS_WUE_CAP_MAX_SIMU_CCTRCH_CNT_DL       PS_WUE_MAX_CCTRCH_NUM           /* Max Simultaneous CCTRCH DL                 */

#define PS_WUE_CAP_MAX_TB_DL                    (PS_WUE_MAX_TB_CNT)             /* MaxTransportBlocksDL                       */
#define ASN1_MAX_TB_DL                          EN_ENC_MAX_TRANSP_BLOCK_DL_TB32

#define PS_WUE_CAP_MAX_TFC_DL                   (PS_WUE_MAX_DL_TFC_NUM)         /* MaxNumberOfTFC-InTFCS-DL                   */
#define ASN1_MAX_TFC_DL                         EN_ENC_MAX_NUM_OF_TFC_DL_TFC128

#define PS_WUE_CAP_MAX_TF_DL                    (64)                            /* MaxNumberOfTF                              */
#define ASN1_MAX_TF_DL                          EN_ENC_MAX_NUM_OF_TF_TF64

#define PS_WUE_CAP_MAX_NO_BITS_TRANS            (6400)
#define ASN1_MAX_NO_BITS_TRANS                  EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_CONV_CODE_BITS_TRANS     (640)                           /* Max conv coded bits transmitted            */
#define ASN1_MAX_CONV_CODE_BITS_TRANS           EN_ENC_MAX_NO_BITS_B640

#define PS_WUE_CAP_TURBO_ENC_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT : Support turbo encoding    */

#define PS_WUE_CAP_MAX_TURB_CODE_BITS_TRANS     (6400)                          /* Max turbo coded bits transmitted,          */
#define ASN1_MAX_TURB_CODE_BITS_TRANS           EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_SIMU_TRANS_CH_UL         (8)                             /* Max Simultaneous TrChs UL                  */
#define ASN1_MAX_SIMU_TRANS_CH_UL               EN_ENC_MAX_SIMUL_TRANS_CHS_UL_E8

#define PS_WUE_CAP_MAX_TB_UL                    (PS_WUE_MAX_TB_CNT)
#define ASN1_MAX_TB_UL                          EN_ENC_MAX_TRANSP_BLOCK_UL_TB32

#define PS_WUE_CAP_MAX_TFC_UL                   (PS_WUE_MAX_UL_TFC_NUM)
#define ASN1_MAX_TFC_UL                         EN_ENC_MAX_NUM_OF_TFC_UL_TFC128


#define PS_WUE_CAP_MAX_TF_UL                    (32)
#define ASN1_MAX_TF_UL                          EN_ENC_MAX_NUM_OF_TF_TF32

/* Security capability */
#define PS_WUE_CAP_SECURITY_NOT_SUPPORT_CIPH_ALG_CAP        (0x0001)            /* Ciphering algorithm capability, 0x0001:UEA0=1 */
#define PS_WUE_CAP_SECURITY_SUPPORT_CIPH_ALG_CAP            (0x0003)            /* Ciphering algorithm capability, 0x0003:UEA0=1&UEA1=1 */
#define PS_WUE_CAP_SECURITY_INTEG_PROT_ALG_CAP  (0x0002)                        /* Integrity protection algorithm capability 0x0001:UIA1=1 */

#define PS_WUE_CLASSMARK2_SIZE                  (5)                             /*Э��ֵ5,HI4131 ���4*/
#define PS_WUE_CLASSMARK3_MAX_SIZE              (34)                            /*Э��ֵ���22,HI4131 ������14*/
#define PS_WUE_GERAN_IU_RADIO_ACS_CAP_MAX_SIZE  (22)                            /*Э��ֵ���22,HI4131 ������22*/

#define PS_WUE_MAX_E_DCH_CCCH_BUF_BYTE_SIZE     (64)                            /* CCCH RB0����ռ䣬��Э��ֵ������ĿǰCELL UPDATE/RRC CONN REQ���ϢԤ���ռ� */
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/








#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of WUeSpec.h */
