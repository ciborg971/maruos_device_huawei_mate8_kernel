/*****************************************************************************
  �� �� ��   : LmspLPhyInterface.h
  �� �� ��   : V1.0
  ��    ��   : DSP
  ��������   : 2013��
  ��������   : LMSP��LDSP֮��Ľӿ��ļ�����Ҫ��CT��BTʹ��
  �޸���ʷ   :
  1.��    �� : 2013��12��13��
    ��    �� : DSP
    �޸����� : �����ļ�

  2.��    �� : 2013��8��29��
    ��    �� : luzhejun
    �޸����� : ����LTE��WIFI����Ľӿ�


*****************************************************************************/
#ifndef _LMSP_LPHY_INTERFACE
#define _LMSP_LPHY_INTERFACE

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#ifdef MBX_RTT_CBT
#define CT_OM_MSG_HANDLING_DOWN         (0)
#define CT_OM_MSG_PARA_ERROR            (1)
#define CT_OM_TEST_MODE_REQ                (0x65)
#define CT_OM_BANDSW_SET_REQ               (0x66)
#define CT_OM_FCHAN_SET_REQ                (0x67)
#define CT_OM_AFC_C1_FIXSET_REQ            (0x12c)
#define CT_OM_AFC_C1_FIXREFRESH_REQ        (0x12d)
#define CT_OM_AFC_C2_FIXSET_REQ            (0x12e)
#define CT_OM_AFC_C2_FIXREFRESH_REQ        (0x12f)
#define CT_OM_DCXO_AFC_CALI_REQ            (0x130)
#define CT_OM_DCXO_HKADC_QUERY_REQ         (0x131)
#define CT_OM_CALIDCOC_SET_REQ             (0x132)
#define CT_OM_DCOC_RESULT_QUERY_REQ        (0x133)
#define CT_OM_CALIIP2_SET_REQ              (0x134)
#define CT_OM_IP2_RESULT_QUERY_REQ         (0x135)
#define CT_OM_CALITXIQ_SET_REQ             (0x136)
#define CT_OM_TXIQ_RESULT_QUERY_REQ        (0x137)
#define CT_OM_APC_CALI_PARASET_REQ         (0x138)
#define CT_OM_AGC_CALI_PARASET_REQ         (0x139)
#define CT_OM_APC_CALI_START_REQ           (0x13a)
#define CT_OM_TRIG_STARTUS_QUERY_REQ       (0x13b)
#define CT_OM_AGC_CALI_RESULT_QUERY_REQ    (0x13c)
#define CT_OM_TEMP_QUERY_REQ               (0x13d)
#define CT_OM_DCXO_TEMP_REFRESH_REQ        (0x13e)
#define CT_OM_LTXON_REQ                    (0x13f)
#define NCIT_OM_PARA_SET_REQ               (0x15e)
#define NCIT_OM_BW_SET_REQ                 (0x15f)
#define NCIT_OM_SYNC_SET_REQ               (0x160)
#define NCIT_OM_SYNC_STATUS_QUERY_REQ      (0x161)
#define NCIT_OM_SEGMENT_SET_REQ            (0x162)
#define NCIT_OM_TXMODU_SET_REQ             (0x163)
#define NCIT_OM_TXRBNUM_SET_REQ            (0x164)
#define NCIT_OM_TX_RBPOS_SET_REQ           (0x165)
#define NCIT_OM_TX_POW_SET_REQ             (0x166)
#define NCIT_OM_TX_CHTYPE_SET_REQ          (0x167)
#define NCIT_OM_SEGMENT_LEN_SET_REQ        (0x168)
#define NCIT_OM_RX_STAPERIOD_SET_REQ       (0x169)
#define NCIT_OM_RX_UPPARA_SET_REQ          (0x16a)
#define NCIT_OM_RX_BLER_QUERY_REQ          (0x16C)
#define NCIT_OM_TEST_START_REQ             (0x16d)
#define NCIT_OM_TEST_STOP_REQ              (0x16e)
#define NCIT_OM_TDD_SBFN_SET_REQ           (0x16f)
#define NCIT_OM_COMPARA_SET_REQ            (0x172)
#define NCIT_OM_TXPARA_SET_REQ             (0x173)
#endif
#define OM_PHY_CT_TEST_MODE_REQ		                 0X10000
#define PHY_OM_CT_TEST_MODE_CNF		                 0X10000
#define OM_PHY_CT_TXON_REQ	                         0X10020
#define PHY_OM_CT_TXON_CNF		                     0X10020
#define OM_PHY_CT_FREQ_SET_REQ	                     0X10040
#define PHY_OM_CT_FREQ_SET_CNF		                 0X10040
#define OM_PHY_CT_TXPOW_SET_REQ	                     0X10060
#define PHY_OM_CT_TXPOW_SET_CNF		                 0X10060
#define OM_PHY_CT_VCTCXO_SET_REQ	                 0X10080
#define PHY_OM_CT_VCTCXO_SET_CNF		             0X10080
#define OM_PHY_CT_RXON_REQ	                         0X100A0
#define PHY_OM_CT_RXON_CNF		                     0X100A0
#define OM_PHY_CT_RXANT_SET_REQ	                     0X100C0
#define PHY_OM_CT_RXANT_SET_CNF		                 0X100C0
#define OM_PHY_CT_AAGC_SET_REQ	                     0X100E0
#define PHY_OM_CT_AAGC_SET_CNF		                 0X100E0
#define OM_PHY_CT_MEAS_RSSI_REQ	                     0X10100
#define PHY_OM_CT_MEAS_RSSI_CNF		                 0X10100
#define PHY_OM_CT_RSSI_IND		                     0X10110

/* �¶Ȼ�ȡ�ӿ�*/
#define OM_PHY_CT_VOLTAGE_REQ		                 0X10111
#define PHY_OM_CT_VOLTAGE_CNF		                 0X10111

/* AT^FAGC*/
#define OM_PHY_FAGC_REQ		                         0X10112
#define PHY_OM_FAGC_CNF		                         0X10112

#define OM_PHY_CT_FPA_SET_REQ                        0x10113 /*AT^FPA*/
#define PHY_OM_CT_FPA_SET_CNF                        0x10113

#define OM_PHY_CT_FDAC_SET_REQ                       0x10114 /*AT^FDAC*/
#define PHY_OM_CT_FDAC_SET_CNF                       0x10114


#define OM_PHY_CT_TSELRF_SET_REQ                     0x10115 /*AT^TSELRF*/
#define PHY_OM_CT_TSELRF_SET_CNF                     0x10115

#define OM_PHY_CT_FWAVE_SET_REQ                      0x10116
#define PHY_OM_CT_FWAVE_SET_CNF                      0x10116

#define OM_PHY_CT_F_FREQ_SET_REQ                    (0x10120)
#define PHY_OM_CT_F_FREQ_SET_CNF                    (0x10120)

#define OM_PHY_CT_F_TXPOW_SET_REQ                   (0X10130)
#define PHY_OM_CT_F_TXPOW_SET_CNF        (0X10130)

#define OM_PHY_CT_F_AAGC_SET_REQ         (0X10140)
#define PHY_OM_CT_F_AAGC_SET_CNF         (0X10140)

#define PHY_OM_CT_F_MEAS_RSSI_IND        (0X10150)

#define PHY_OM_CT_F_MEAS_CMTMS_IND       (0X10160)

#define OM_PHY_CT_F_PA_SET_REQ           (0X10170)
#define PHY_OM_CT_F_PA_SET_CNF           (0X10170)

#define OM_PHY_CT_F_SEGMENT_SET_REQ      (0X10180)
#define PHY_OM_CT_F_SEGMENT_SET_CNF      (0X10180)

#define OM_PHY_CT_F_TXWAVE_SET_REQ       (0X10190)
#define PHY_OM_CT_F_TXWAVE_SET_CNF       (0X10190)

#define OM_PHY_CT_F_TRIGGER_SET_REQ      (0X101A0)
#define PHY_OM_CT_F_TRIGGER_SET_CNF      (0X101A0)

#define OM_PHY_CT_F_TRIGGER_RD_REQ       (0X101B0)
#define PHY_OM_CT_F_TRIGGER_RD_CNF       (0X101B0)


#define OM_PHY_CT_F_FBLK_SET_REQ         (0X101C0)
#define PHY_OM_CT_F_FBLK_SET_CNF         (0X101C0)

#define OM_PHY_CT_F_FIPSTART_SET_REQ     (0X101D0)
#define PHY_OM_CT_F_FIPSTART_SET_CNF     (0X101D0)
#define PHY_OM_CT_F_MEAS_IP2_IND          (0X101E0)

#define OM_PHY_CT_F_MAX_POWER_SET_REQ     (0X101f0)
#define PHY_OM_CT_F_MAX_POWER_SET_CNF     (0X101f0)

#define OM_PHY_CT_F_PA_POWER_SET_REQ      (0X101f4)
#define PHY_OM_CT_F_PA_POWER_SET_CNF       (0X101f4)

#define OM_PHY_LTESCINFO_RD_REQ          (0X101C2)
#define PHY_OM_LTESCINFO_RD_CNF          (0X101C2)

#define OM_PHY_CT_F_BANDSW_SET_REQ             (0X101F5)
#define PHY_OM_CT_F_BANDSW_SET_CNF             (0X101F5)


#define OM_PHY_BT_TEMP_DISPATCH_REQ        (0x10340)
#define PHY_OM_BT_TEMP_DISPATCH_CNF        (0x10340)

#define OM_PHY_CT_F_FPDMS_REQ              (0X101F6)
#define PHY_OM_CT_F_FPDMS_CNF              (0X101F6)

#define OM_PHY_CT_F_PD_AUTO_CAL_REQ             (0X101f7)
#define PHY_OM_CT_F_PD_AUTO_CAL_CNF             (0X101f7)
#define PHY_OM_CT_F_PD_AUTO_CAL_IND             (0X101f8)

#define OM_PHY_CT_F_PD_CAL_REQ                 (0X101f9)
#define PHY_OM_CT_F_PD_CAL_CNF                 (0X101f9)
#define PHY_OM_CT_F_PD_CAL_IND                 (0X101fA)
//^FCALIIP2S IDs
#define OM_PHY_CT_F_CALIIP2_SET_REQ (0x10220)
#define PHY_OM_CT_F_CALIIP2_SET_CNF (0x10220)
#define PHY_OM_CT_F_CALIIP2_IND     (0x10221)

//^FCALIDCOCS IDs
#define OM_PHY_CT_F_CALIDCOCS_SET_REQ (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_SET_CNF (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_IND (0x10231)

//^FCALITXIQ IDs
#define OM_PHY_CT_F_CALITXIQ_SET_REQ (0x10240)
#define PHY_OM_CT_F_CALITXIQ_SET_CNF (0x10240)
#define PHY_OM_CT_F_CALITXIQ_IND (0x10241)

//^FGAINSTATES IDs
#define OM_PHY_CT_F_GAINSTATE_SET_REQ (0x10250)
#define PHY_OM_CT_F_GAINSTATE_SET_CNF (0x10250)

//^FDBBATTS IDs
#define OM_PHY_CT_F_DBBATT_SET_REQ (0x10260)
#define PHY_OM_CT_F_DBBATT_SET_CNF (0x10260)

//^FBBATTS IDs
#define OM_PHY_CT_F_BBATT_SET_REQ  (0x10270)
#define PHY_OM_CT_F_BBATT_SET_CNF  (0x10270)

//^FCALIIP2SMRF IDS
#define OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ     (0X10280)
#define PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF     (0X10280)
#define PHY_OM_CT_F_CALIIP2_MUTIRF_IND         (0X10281)
#define OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ (0x10290)
#define PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF (0x10290)
#define PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND     (0x10291)

/**********************����Ϊ�������۲����Ϣ����******************************/
#define OM_PHY_SYN_SSYNC_SET_REQ             (0x10200)
#define PHY_OM_SYN_SSYNC_SET_CNF             (0x10200)

/* ^SSYNC �������۲��ѯ����ͬ��״̬*/
#define OM_PHY_SYN_SSYNC_RD_REQ              (0x10201)
#define PHY_OM_SYN_SSYNC_IND                 (0x10201)

/* ^STXBW �������۲����÷������*/
#define OM_PHY_SYN_STXBW_SET_REQ             (0x10202)
#define PHY_OM_SYN_STXBW_SET_CNF             (0x10202)

/* ^SSUBFRAME �������۲�������֡���*/
#define OM_PHY_SYN_SSUBFRAME_SET_REQ           (0x10204)
#define PHY_OM_SYN_SSUBFRAME_SET_CNF           (0x10204)

/* ^STXCHAN �������۲��������з����ŵ�*/
#define OM_PHY_SYN_STXCHAN_SET_REQ           (0x10205)
#define PHY_OM_SYN_STXCHAN_SET_CNF           (0x10205)

/*^SPARA*/
/*�������۲������ŵ�����*/
#define OM_PHY_SYN_SPARA_SET_REQ           (0x1020F)
#define PHY_OM_SYN_SPARA_SET_CNF           (0x1020F)

#define OM_PHY_SYN_SPARA_RD_REQ             (0x10210)
#define PHY_OM_SYN_SPARA_RD_CNF             (0x10210)

/*^SSEGNUM�������۲�����segment����*/
#define OM_PHY_SYN_SSEGNUM_SET_REQ           (0x10211)
#define PHY_OM_SYN_SSEGNUM_SET_CNF           (0x10211)

#define OM_PHY_SYN_SSEGNUM_RD_REQ            (0x10212)
#define PHY_OM_SYN_SSEGNUM_RD_CNF            (0x10212)

/* ^STXMODUS �������۲����õ��Ʒ�ʽ*/
#define OM_PHY_SYN_STXMODUS_SET_REQ          (0x10206)
#define PHY_OM_SYN_STXMODUS_SET_CNF          (0x10206)

/* ^STXRBNUMS �������۲�����RB����*/
#define OM_PHY_SYN_STXRBNUMS_SET_REQ         (0x10207)
#define PHY_OM_SYN_STXRBNUMS_SET_CNF         (0x10207)

/* ^STXRBPOSS �������۲�����RBλ��*/
#define OM_PHY_SYN_STXRBPOSS_SET_REQ         (0x10208)
#define PHY_OM_SYN_STXRBPOSS_SET_CNF         (0x10208)

/* ^STXPOWS �������۲����÷��书��*/
#define OM_PHY_SYN_STXPOWS_SET_REQ           (0x10209)
#define PHY_OM_SYN_STXPOWS_SET_CNF           (0x10209)

/* ^STXCHANTYPES �������۲������ŵ�����*/
#define OM_PHY_SYN_STXCHANTYPES_SET_REQ      (0x1020A)
#define PHY_OM_SYN_STXCHANTYPES_SET_CNF      (0x1020A)

/* ^SSEGLEN �������۲�����SEGMENT����*/
#define OM_PHY_SYN_SSEGLEN_SET_REQ          (0x1020B)
#define PHY_OM_SYN_SSEGLEN_SET_CNF          (0x1020B)

/*^SRXPOW�������۲���ղ��ԵĹ�������*/
#define OM_PHY_SYN_SRXPOW_SET_REQ          (0x10213)
#define PHY_OM_SYN_SRXPOW_SET_CNF          (0x10213)
#define OM_PHY_SYN_SRXPOW_RD_REQ           (0x10214)
#define PHY_OM_SYN_SRXPOW_RD_CNF           (0x10214)

/*^SRXSUBFRA�������۲���ղ��Ե���֡����*/
#define OM_PHY_SYN_SRXSUBFRA_SET_REQ          (0x10215)
#define PHY_OM_SYN_SRXSUBFRA_SET_CNF          (0x10215)
#define OM_PHY_SYN_SRXSUBFRA_RD_REQ           (0x10216)
#define PHY_OM_SYN_SRXSUBFRA_RD_CNF           (0x10216)

/*^SRXBLER�������۲���ղ��Բ�ѯ������*/
#define OM_PHY_SYN_SRXBLER_RD_REQ           (0x10217)
#define PHY_OM_SYN_SRXBLER_RD_CNF           (0x10217)

/* ^SSTART �������۲��������䲢״̬��ѯ*/
#define OM_PHY_SYN_SSTART_SET_REQ            (0x1020C)
#define PHY_OM_SYN_SSTART_SET_CNF            (0x1020C)

/* ^SSTART �������۲�״̬��ѯ*/
#define OM_PHY_SYN_SSTART_RD_REQ             (0x1020D)
#define PHY_OM_SYN_SSTART_RD_CNF             (0x1020D)

/* ^SSTOP �������۲�ֹͣ���з���*/
#define OM_PHY_SYN_SSTOP_SET_REQ             (0x1020E)
#define PHY_OM_SYN_SSTOP_SET_CNF             (0x1020E)

#define OM_PHY_SYN_SRXSET_SET_REQ            (0x10213)
#define PHY_OM_SYN_SRXSET_SET_CNF            (0x10213)

#define OM_PHY_BT_FPOW_SET_REQ                (0x10214)
#define PHY_OM_BT_FPOW_SET_CNF                (0x10214)

/*��ѯ TDS ���� BER ���*/
#define OM_PHY_SYN_SRXBER_RD_REQ           (0x10218)
#define PHY_OM_SYN_SRXBER_RD_CNF           (0x10218)

#define OM_PHY_COMM_CMD_SET_REQ            (0x102A0)
#define PHY_OM_COMM_CMD_SET_CNF            (0x102A0)
#define PHY_OM_COMM_CMD_IND                (0x102A1)

#define OM_PHY_FPLLSTATUS_RD_REQ           (0x102A2)
#define PHY_OM_FPLLSTATUS_RD_CNF           (0x102A2)

#define OM_PHY_NOISE_CFG_REQ                  (0x102A3)
#define PHY_OM_NOISE_RSSI_IND                  (0x102A4)

//IP2У׼֧�����Ƶ����
#define CT_IP2_CAL_FREQ_NUM 4

//DCOCУ׼��AGC��λ����
#define CT_F_CALIDCOCS_AGC_NUM 16

//GainState����������
#define CT_F_GAINSTATE_MAX_NUM  60

//DBB˥������������
#define CT_F_DBBATT_MAX_NUM CT_F_GAINSTATE_MAX_NUM

//BB˥������������
#define CT_F_BBATT_MAX_NUM_CT CT_F_GAINSTATE_MAX_NUM

/* Modify channel number from 16 to 32 by daizhicheng for V7R2/V9R1*/
#define CT_F_FREQ_UL_LIST_MAX_NUM 32
#define CT_F_FREQ_DL_LIST_MAX_NUM 32

#define POW_MAX_NUM             (30)
#define TX_POW_MAX_NUM          (20*2*3)
/* Modify channel number from 16 to 32 by daizhicheng for V7R2/V9R1*/
#define FREQ_MAX_NUM            (32)

#define NOISETOOL_MAX_PWR_NUM       (1)
#define NOISETOOL_SEGMENT_LEN         (5)
#define NOISETOOL_MEAS_OFFSET    (3)

#define CT_MAX_RFIC_PATH_NUM          2
#define CT_MAX_RX_ANT_NUM             4

#define CT_TDS_MODE             2

/* Begin: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */
/* LTE��WIFI��������MSP�·�����������Ĳ�������Ŀ */
#define    LMSP_LPHY_MAX_COEX_PARA_NUM                        6

#define LMSP_LPHY_MSG_HDR                (0x2000)
#define LPHY_LMSP_MSG_HDR                (0x2100)

#define LWCOEX_MSG_TYPE                (0x1)

#define LMSP_TDS_BAND39_INDEX            5         /*TDS_BANDF*/
#define LMSP_TDS_BAND34_INDEX            0         /*TDS_BANDA*/

#define LMSP_TDS_MAX_BAND_NUM            6
/* End: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */

/* Begin: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */
/*****************************************************************************
 ö����    : LMSP_LPHY_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LMSP -> LPHY �ӿ���ϢID
*****************************************************************************/
enum LMSP_LPHY_MSG_ID_ENUM
{
    /* MSP����������ԭ�� */
    ID_LMSP_LPHY_LTE_WIFI_COEX_SET_REQ       = LMSP_LPHY_MSG_HDR + LWCOEX_MSG_TYPE,
    ID_LMSP_LPHY_LTE_WIFI_COEX_SET_CNF       = LPHY_LMSP_MSG_HDR + LWCOEX_MSG_TYPE,
    ID_LMSP_LPHY_BUTT
};
typedef VOS_UINT32    LMSP_LPHY_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMSP_LPHY_COEX_BW_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMSP_LPHY_COEX_BW_TYPE_ENUM
{
    LMSP_LPHY_COEX_BAND_WIDTH_6RB              = 0,       /* ����Ϊ1.4M */
    LMSP_LPHY_COEX_BAND_WIDTH_15RB,                       /* ����Ϊ3M */
    LMSP_LPHY_COEX_BAND_WIDTH_25RB,                       /* ����Ϊ5M */
    LMSP_LPHY_COEX_BAND_WIDTH_50RB,                       /* ����Ϊ10M */
    LMSP_LPHY_COEX_BAND_WIDTH_75RB,                       /* ����Ϊ15M */
    LMSP_LPHY_COEX_BAND_WIDTH_100RB,                      /* ����Ϊ20M */
    LMSP_LPHY_COEX_BAND_WIDTH_BUTT
};
typedef UINT16    LMSP_LPHY_COEX_BW_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : LMSP_LPHY_COEX_ENABLE_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMSP_LPHY_COEX_ENABLE_IND_ENUM
{
    LMSP_LPHY_COEX_DISABLE     = 0, /*��ָ���Ĵ����Ϲرչ��淽��*/
    LMSP_LPHY_COEX_ENABLE ,         /*��ָ���Ĵ����ϴ򿪹��淽��*/
    LMSP_LPHY_COEX_BUTT
};
typedef UINT16    LMSP_LPHY_COEX_ENABLE_IND_ENUM_UINT16;


/*****************************************************************************
 ö����    : LMSP_LPHY_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMSP_LPHY_RESULT_ENUM
{
    LMSP_LPHY_RESULT_SUCC                 = 0,
    LMSP_LPHY_RESULT_FAIL ,
    LMSP_LPHY_RESULT_BUTT
};
typedef UINT16    LMSP_LPHY_RESULT_ENUM_UINT16;

/* End: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */




typedef struct
{
    UINT32 ulMsgId;
}PHY_MSP_CT_SINGLE_CNF_STRU;

#ifdef MBX_RTT_CBT
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usStatus;
    UINT16 usRsv;
} OM_MSG_CNF_STRU;
#endif
/*****************************************************************************
 ���� : MSP�յ�AT^TMODE������ж�Ϊ������ģʽʱ�·���ԭ���֪RTT��
        AT����������ģʽ���·���ԭ��
 ID   : OM_PHY_CT_TEST_MODE_REQ,PHY_OM_CT_TEST_MODE_CNF
 REQ  : OM_PHY_CT_TEST_MODE_REQ_STRU
 CNF  : PHY_OM_CT_TEST_MODE_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /*1: ��������ͨУ׼ģʽ*/
    /*6�����������У׼ģʽ*/
    UINT16 usTMode;     /* ģʽ����*/
    UINT16 usRsv;
} OM_PHY_CT_TEST_MODE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TEST_MODE_CNF_STRU;


/*****************************************************************************
 ���� : ָʾ����������ͨ����RTT�յ���ԭ������ͨ������һֱ�򿪣�ֱ��MSPͨ����ԭ��ر����С�
 ID   : OM_PHY_CT_TXON_REQ,PHY_OM_CT_TXON_CNF
 REQ  : OM_PHY_CT_TXON_REQ_STRU
 CNF  : PHY_OM_CT_TXON_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* 0:��ʾ�رշ����*/
	  /* 1:��ʾ�򿪷�����������������ƺ�RF����ͨ��*/
    /* 2:��ʾֻ��RFIC Transmitter��PA ��BB����ͨ�����򿪣�����VCTCXOУ׼*/
    UINT16 usTxType;                     /*Tx������*/
    UINT16 usRsv;
} OM_PHY_CT_TXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXON_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;
}OM_PHY_FPLLSTATUS_RD_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 tx_status;
    UINT16 rx_status;
}PHY_OM_FPLLSTATUS_RD_CNF_STRU;


/*****************************************************************************
 ���� : ����ǰ����ͨ���򿪣�Tx����Ϊ1��2������RTT��Ϊ��ԭ����������Ƶ�㣬������ͨ���رգ�
        ����Ϊ������Ƶ�㡣MSP�뽫AT^FCHAN�����е��ŵ��Ÿ���36.101Э��涨���תΪʵ��Ƶ��ֵ��
        ת�����̲ο���¼4��
 ID   : OM_PHY_CT_FREQ_SET_REQ,PHY_OM_CT_FREQ_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* Ƶ����Ϣ��*/
    /* Ƶդ���100Khz��������ֵ26200��ӦƵ��2.62GHz*/
    UINT16 usUlFreq;                   /*Ƶ����Ϣ*/
    UINT16 usDlFreq;                   /*Ƶ����Ϣ*/
    UINT16 usMode;    /*6,FDD;7,TDD */
    UINT16 usBandNum;
} OM_PHY_CT_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FREQ_SET_CNF_STRU;


/*****************************************************************************
 ���� : �������з��书�ʡ�RTT�յ���ԭ���Ӧ�����ı����з��书��
 ID   : OM_PHY_CT_TXPOW_SET_REQ,PHY_OM_CT_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* ��λ��dBm*/
    INT16  sTxPower;                     /*���з��书��*/
    UINT16 usRsv;
} OM_PHY_CT_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXPOW_SET_CNF_STRU;

/*****************************************************************************
 ���� : �������з��书�ʡ�RTT�յ���ԭ���Ӧ�����ı����з��书��
 ID   : OM_PHY_CT_VCTCXO_SET_REQ,PHY_OM_CT_VCTCXO_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* VCTCXO���Ƶ�ѹ		[0,65535]*/
    UINT16 usVctcxoCtrl;                 /*Vctcxo������*/
    UINT16 usRsv;
} OM_PHY_CT_VCTCXO_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_VCTCXO_SET_CNF_STRU;

/*****************************************************************************/

/*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
    UINT8  ucLevel;
    UINT8  ucPading[3];

} OM_PHY_CT_FPA_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FPA_SET_CNF_STRU;


/*****************************************************************************

*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
    UINT16  usApc;
    UINT16  usRsv;

} OM_PHY_CT_FDAC_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FDAC_SET_CNF_STRU;


/*****************************************************************************
 ���� : ָʾ���������ջ�������������ڽ��������ģʽ�Ѵ򿪽���˫ͨ����
        �˴��յ�ԭ��������մ���ֱ�ӷ���CNFԭ��
 ID   : OM_PHY_CT_RXON_REQ,PHY_OM_CT_RXON_CNF
 REQ  : OM_PHY_CT_RXON_REQ_STRU
 CNF  : PHY_OM_CT_RXON_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    UINT16 usRxType;                     /*Rx������*/
    UINT16 usRsv;
} OM_PHY_CT_RXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXON_CNF_STRU;

/*****************************************************************************
 ���� : ����RXͨ����RTT�յ���ԭ���ѡ����Ҫ����RSSI������ϱ��Ľ���ͨ����
      ע��RTT�ڷ�����ģʽ��Rx˫ͨ����һֱ�򿪡�����ԭ��ָʾ�ر�˫ͨ����
      RTT�����κδ���
 ID   : OM_PHY_CT_RXANT_SET_REQ,PHY_OM_CT_RXANT_SET_CNF
 REQ  : OM_PHY_CT_RXANT_SET_REQ_STRU
 CNF  : PHY_OM_CT_RXANT_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* 0:�ر�˫ͨ��*/
    /* 1:ֻ��ͨ��1*/
    /* 2:ֻ��ͨ��2*/
    /* 3:��˫ͨ��*/
    UINT16 usRxAntType;                  /* RXͨ��ѡ�� */
    UINT16 usRsv;
} OM_PHY_CT_RXANT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXANT_SET_CNF_STRU;

/*****************************************************************************
AT^TSELRF
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
    UINT8  ucPath;
    UINT8  ucGroup;
    UINT16 usRsv;
} OM_PHY_CT_TSELRF_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TSELRF_SET_CNF_STRU;


/*****************************************************************************
 ���� : ����RFIC��AAGC�����棬��������AGC���У׼����λΪdB��
      RTT�յ���ԭ���RFIC��������������Ϊԭ��ָʾ������ֵ��
 ID   : OM_PHY_CT_AAGC_SET_REQ,PHY_OM_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_AAGC_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* [0,127]	��λ:dB��*/
    UINT16 usAAGCValue;                  /* AAGC����ֵ */
    UINT16 usRsv;
} OM_PHY_CT_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_AAGC_SET_CNF_STRU;

/*****************************************************************************
 ���� :ָʾRTT���������RSSI��������������AGC���У׼��RTT�յ���ԭ�������RSSI
       ��������ɺ�ͨ��PHY_OM_CT_RSSI_INDԭ���ϱ���ӦRXͨ����RSSI�������
 ID   : OM_PHY_CT_MEAS_RSSI_REQ,PHY_OM_CT_MEAS_RSSI_CNF
 REQ  : OM_PHY_CT_MEAS_RSSI_REQ_STRU
 CNF  : PHY_OM_CT_MEAS_RSSI_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
} OM_PHY_CT_MEAS_RSSI_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_MEAS_RSSI_CNF_STRU;
/*****************************************************************************
 ���� :ָʾ������������������ѹ������
 ID   :
 REQ  : OM_PHY_CT_VOLTAGE_REQ_STRU
 CNF  : PHY_OM_CT_VOLTAGE_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
} OM_PHY_CT_VOLTAGE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulVoltage;
} PHY_OM_CT_VOLTAGE_CNF_STRU;

/*****************************************************************************
 ���� :ָʾRTT���������RSSI��������������AGC���У׼��RTT�յ���ԭ�������RSSI
       ��������ɺ�ͨ��PHY_OM_CT_RSSI_INDԭ���ϱ���ӦRXͨ����RSSI�������
 ID   : PHY_OM_CT_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_RSSI_IND_STRU
 ˵�� :
*****************************************************************************/

/* usRxANT1ValidFlag	Rxͨ��1��Ч��־		[0,1]	0:Rxͨ��1��Ч��sRxANT1RSSIֵ��Ч*/
/* 1:Rxͨ��1��Ч��sRxANT1RSSIֵ��Ч*/
/* sRxANT1RSSI	Rxͨ��1��RSSI		[-110*8,-20*8]	��λ:1/8dBm��ֻ��usRxANT1ValidFlag=1��Ч*/
/* usRxANT2ValidFlag	Rxͨ��2��Ч��־		[0,1]	0:Rxͨ��2��Ч��sRxANT2RSSIֵ��Ч*/
/* 1:Rxͨ��2��Ч��sRxANT2RSSIֵ��Ч*/
/* sRxANT2RSSI	Rxͨ��2��RSSI		[-110*8,-20*8]	��λ:1/8dBm��ֻ��usRxANT2ValidFlag=1��Ч*/
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usRxANT1ValidFlag;
    INT16  sRxANT1RSSI;
    UINT16 usRxANT2ValidFlag;
    INT16  sRxANT2RSSI;
    UINT16 usRxANT3ValidFlag;
    INT16  sRxANT3RSSI;
    UINT16 usRxANT4ValidFlag;
    INT16  sRxANT4RSSI;
} PHY_OM_CT_RSSI_IND_STRU;

/* OM_PHY_POWER_CONFIG_REQ*/
#if 0
typedef struct
{
    UINT32 ulMsgId;
    PHY_OM_UPLINK_PWR_CTRL_STRU stulPwrCtrlFlag;
    INT16  sPucchTxPower;
    INT16  sPuschTxPower;
    INT16  sSrsTxPower;
    INT16  sPrachTxPower;
}OM_PHY_POWER_CONFIG_REQ_STRU;
#endif
/*****************************************************************************
 ���� : AGC��ѯ
 ID   : OM_PHY_FAGC_REQ,PHY_OM_FAGC_CNF
 REQ  : OM_PHY_FAGC_REQ_STRU
 CNF  : PHY_OM_FAGC_CNF_STRU
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
} OM_PHY_FAGC_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    INT16 sRsrp;
    INT16 sRsv;
} PHY_OM_FAGC_CNF_STRU;

/****************************************************************************************************
����:   IP2У׼������^FCALIIP2S
ID:     OM_PHY_CT_F_CALIIP2_SET_REQ,      PHY_OM_CT_F_CALIIP2_SET_CNF,      PHY_OM_CT_F_CALIIP2_IND
�ṹ:   OM_PHY_CT_F_CALIIP2_SET_REQ_STRU, PHY_OM_CT_F_CALIIP2_SET_CNF_STRU, PHY_OM_CT_F_CALIIP2_IND_STU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usChan[CT_IP2_CAL_FREQ_NUM];
}OM_PHY_CT_F_CALIIP2_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIIP2_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usMain_I_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_I_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_I[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_Q[CT_IP2_CAL_FREQ_NUM];
}PHY_OM_CT_F_CALIIP2_IND_STRU;


/****************************************************************************************************
����:   IP2У׼������^FCALIIP2S
ID:     OM_PHY_CT_F_CALIIP2_SET_REQ,      PHY_OM_CT_F_CALIIP2_SET_CNF,      PHY_OM_CT_F_CALIIP2_IND
�ṹ:   OM_PHY_CT_F_CALIIP2_SET_REQ_STRU, PHY_OM_CT_F_CALIIP2_SET_CNF_STRU, PHY_OM_CT_F_CALIIP2_IND_STU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usBand;                            /*band ��  */
    UINT16 usFreqNum;                         /*Ƶ����Ŀ */
    UINT16 usRfid;                            /*RFͨ��   */
	UINT16 usRsv;
    UINT16 usFreq[CT_IP2_CAL_FREQ_NUM]; /*Ƶ���б� */
}OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usRsv;
	UINT16 usMain_I_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_I_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_I[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_Q[CT_IP2_CAL_FREQ_NUM];
}CT_RF_IIP2_CAL_ITEM;

typedef struct
{
	UINT32    ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usCalStatus;
#endif
	UINT16    usChanNum;
	UINT16    usRsv;
	CT_RF_IIP2_CAL_ITEM  astIp2CalRst[CT_MAX_RFIC_PATH_NUM];
}PHY_OM_CT_F_CALIIP2_MUTIRF_IND_STRU;


/****************************************************************************************************
����:   DCOCУ׼������^FCALIDCOCS
ID:     OM_PHY_CT_F_CALIDCOCS_SET_REQ,      PHY_OM_CT_F_CALIDCOCS_SET_CNF,      PHY_OM_CT_F_CALIDCOCS_IND
�ṹ:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChannel;
	UINT16 usRsv;
}OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usCalStatus;
#endif
	UINT16 usNOBLK_ANT1_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT1_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usBLK_ANT1_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT1_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usNOBLK_ANT2_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT2_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usBLK_ANT2_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT2_Q[CT_F_CALIDCOCS_AGC_NUM];
}PHY_OM_CT_F_CALIDCOCS_IND_STRU;

/****************************************************************************************************
����:   DCOCУ׼������^FCALIDCOCSMRF
ID:     OM_PHY_CT_F_CALIDCOCS_MULTIRF_SET_REQ,      PHY_OM_CT_F_CALIDCOCS_MULTIRF_SET_CNF,      PHY_OM_CT_F_CALIDCOCS_MULTIRF_IND
�ṹ:   OM_PHY_CT_F_CALIDCOCS_MULTIRF_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_MULTIRF_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_MULTIRF_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usFreq;  /*Ƶ��  */
    UINT16 usBand;  /*BAND��*/
    UINT16 usRfid;  /*RFͨ��*/
	UINT16 usRsv;
}OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF_STRU;

typedef struct
{
     UINT16 usAntCompDCI[CT_F_CALIDCOCS_AGC_NUM];
     UINT16 usAntCompDCQ[CT_F_CALIDCOCS_AGC_NUM];
}CT_RF_DOCOC_ANT_ITEM_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usValidAntNum;
    CT_RF_DOCOC_ANT_ITEM_STRU   astAntCal[CT_MAX_RX_ANT_NUM];
}CT_RF_DCOCS_DCCOMP_ITEM_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
	UINT16 usCalStatus;
#endif
    UINT16 usChanNum;
    UINT16 usRsv;
    CT_RF_DCOCS_DCCOMP_ITEM_STRU  astDcocCalRst[CT_MAX_RFIC_PATH_NUM];
}PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND_STRU;


/****************************************************************************************************
����:   TXIQУ׼������^FTXIQ
ID:     OM_PHY_CT_F_CALITXIQ_SET_REQ,       PHY_OM_CT_F_CALITXIQ_SET_CNF,       PHY_OM_CT_F_CALITXIQ_IND
�ṹ:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usFreq;      /*Ƶ��*/
    UINT16 usBand;      /*BAND��*/
    UINT16 usRfid;      /*RFͨ��*/
	UINT16 usRsv;
}OM_PHY_CT_F_TXIQ_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_TXIQ_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;/*0��ʾOK*/
    UINT16 usCalStatus;
#endif
	UINT16 usAmplitude;
	UINT16 usPhase;
	UINT16 usDCI;
	UINT16 usDCQ;
}PHY_OM_CT_F_TXIQ_IND_STRU;

/****************************************************************************************************
����:   ����GainState����������^FGAINSTATES
ID:     OM_PHY_CT_F_GAINSTATE_SET_REQ,       PHY_OM_CT_F_GAINSTATE_SET_CNF
�ṹ:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usGainStateNum;
	UINT16 usRsv;
	UINT16 ausGainState[TX_POW_MAX_NUM];
}OM_PHY_CT_F_GAINSTATE_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_GAINSTATE_SET_CNF_STRU;

/****************************************************************************************************
����:   ����DBB˥������������^FDBBATTS
ID:     OM_PHY_CT_F_DBBATT_SET_REQ,         PHY_OM_CT_F_DBBATT_SET_CNF
�ṹ:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usDbbCodeNum;
	UINT16 usDbbCode;
}OM_PHY_CT_F_DBBATT_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_DBBATT_SET_CNF_STRU;

/****************************************************************************************************
����:   ����BB˥������������^FBBATTS
ID:     OM_PHY_CT_F_BBATT_SET_REQ,      PHY_OM_CT_F_BBATT_SET_CNF
�ṹ:   OM_PHY_CT_F_BBATT_SET_REQ_STRU, PHY_OM_CT_F_BBATT_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usBbAttNum;
	UINT16 usRsv;
	UINT16 usBbAtt[CT_F_BBATT_MAX_NUM_CT];
}OM_PHY_CT_F_BBATT_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_BBATT_SET_CNF_STRU;

/*AT^FPDMS*/
typedef struct
{
   UINT32 ulMsgId;
   UINT32 ulIsEnable;
}OM_PHY_CT_F_FPDMS_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_FPDMS_SET_CNF_STRU;

/*TEMP*/
typedef struct
{
   UINT32 ulMsgId;
   UINT16 usTempVal;
   UINT16 usRsv;
}OM_PHY_BT_TEMP_DISPATCH_REQ_STRU;
/*****************************************************************************
AT^BANDSW
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usMode;
	UINT16 usBand;
	UINT16 usUlFreq;
	UINT16 usDLFreq;
	UINT16 usDlAbbChanIndex;
    UINT16 usUlAbbChanIndex;
	UINT16 usRsv;
}OM_PHY_CT_F_BANDSW_SET_REQ_STRU;
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_BANDSW_SET_CNF_STRU;



/*****************************************************************************
 ���� : ��ǰ����ͨ���򿪡�
        ����Ϊ������Ƶ�㡣MSP�뽫AT^FCHANS�����е��ŵ��Ÿ���36.101Э��涨���תΪʵ��Ƶ��ֵ��
        ת�����̲ο���¼4��
 ID   : OM_PHY_CT_F_FREQ_SET_REQ,PHY_OM_CT_F_FREQ_SET_CNF
 REQ  : OM_PHY_CT_F_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_FREQ_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ*/
    UINT32 ulMode;                       /* MODE TDD��7��FDD��6*/
    UINT16 usUlListNum; /* �������õĸ�������ӦausUlFreqInfo�����16��*/
    UINT16 usDlListNum; /* �������õĸ�������ӦausDlFreqInfo�����16��*/

    /* Ƶ����Ϣ��*/
    /* Ƶդ���100Khz��������ֵ26200��ӦƵ��2.62GHz*/
    UINT16 ausUlFreqInfo[CT_F_FREQ_UL_LIST_MAX_NUM];       /* ����Ƶ����Ϣ*/
    UINT16 ausDlFreqInfo[CT_F_FREQ_DL_LIST_MAX_NUM];       /* ����Ƶ����Ϣ*/
} OM_PHY_CT_F_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_FREQ_SET_CNF_STRU;


/*****************************************************************************
 ���� : �������з��书�ʡ�RTT�յ���ԭ���Ӧ�����ı����з��书��
 ID   : OM_PHY_CT_F_TXPOW_SET_REQ,PHY_OM_CT_F_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_F_TXPOW_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXPOW_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
#define CT_POWER_SET_MAX_NUM             (30)
typedef struct
{
    UINT32 ulMsgId;                          /* ��Ϣ��ʶ */

    /* ��λ��dBm*/
    UINT16 usTxPowerNum;                     /* ָ����asTxPower�ĸ���*/
    UINT16 usRsv;
    /* ���书���б��Կո�ָÿ��ֵ�ĳ���Ϊһ���� ����λΪdBm*/
    INT16  ausTxPower[CT_POWER_SET_MAX_NUM];  /*���з��书��*/
} OM_PHY_CT_F_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXPOW_SET_CNF_STRU;


/*****************************************************************************
 ���� : ����RFIC��AAGC�����棬��������AGC���У׼����λΪdB��
      RTT�յ���ԭ���RFIC��������������Ϊԭ��ָʾ������ֵ��
 ID   : OM_PHY_CT_F_AAGC_SET_REQ,PHY_OM_F_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_F_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_AAGC_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/

#define CT_F_AAGC_SET_MAX_NUM    (30)
typedef struct
{
    UINT32 ulMsgId;                               /* ��Ϣ��ʶ*/
    UINT16 usAagcNum;
    UINT16 usRsv;

    /*ȡֵ��Χ0��255������Hi6910�ķ�ΧΪ151-234��*/
    UINT8 aucAAGCValue[CT_F_AAGC_SET_MAX_NUM];    /* AAGC����ֵ*/
} OM_PHY_CT_F_AAGC_SET_REQ_STRU;

typedef struct
{


    UINT32 ulMsgId;         /* ��Ϣ��ʶ*/
    UINT16 usAagcNum;
    UINT16 usPaLevelNum;
    UINT16 usGainStateNum;
    UINT16 usULFreqNum;     /* ����Ƶ�����õĸ��������16��*/
    UINT16 usDLFreqNum;
    UINT16 usRsv;

    //UINT32 ulMode;          /* MODE TDD��7��FDD��6*/
    UINT16 usWave;          /*���в��� 0:���� 1:LTE����*/
    UINT16 usSegment;       /*segment����*/
    UINT16 usMeasOffset;    /* ��ʾ������ʼλ��ƫ�ƣ���λms��ȡֵ��Χ0~20����Ĭ��ֵ*/
	UINT16 usMeasLen;       /* ��ʾ�������ȣ���λms��ȡֵ��Χ0~20����Ĭ��ֵ */

    /* Ƶդ���100Khz��������ֵ26200��ӦƵ��2.62GHz*/
    UINT16 ausUlFreqInfo[CT_F_FREQ_UL_LIST_MAX_NUM];  /* ����Ƶ����Ϣ*/
    UINT16 ausDlFreqInfo[CT_F_FREQ_DL_LIST_MAX_NUM];  /* ����Ƶ����Ϣ*/
	UINT16 ausGainState[TX_POW_MAX_NUM];
	UINT32 aulAGCValue[CT_F_AAGC_SET_MAX_NUM];        /* AAGC����ֵ ǰ8ΪNO BLK����8ΪBLK*/
    UINT8  aucPaLevel[30];
    UINT16 usDbbCode;



} CT_AGC_CAL_SET_REQ_STRU;
typedef struct
{
    UINT32 ulMsgId;           /* ��Ϣ��ʶ*/
    UINT16 usAagcNum;
    UINT16 usRsv;
    UINT32 aulAGCValue[CT_F_AAGC_SET_MAX_NUM];  /* AAGC����ֵ ǰ8ΪNO BLK����8ΪBLK*/
} CT_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_AAGC_SET_CNF_STRU;

/*****************************************************************************
 ���� :
 ID   : PHY_OM_CT_F_MEAS_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_RSSI_IND_STRU
 ˵�� :
*****************************************************************************/
typedef struct
{
    /* ATָ�-װ������:*/
    /*  ��ֵ������ֵ��ʾ����ȷ��0.125dBm����ֵ��Ϣ��ȡֵ��ΧΪ160~880��*/
    /*  �����ǰ��RSSIֵΪ-85.125dBm����ΧֵΪ-85.125dbm*(-1)/0.125dbm = 681*/

    INT16  sRxANT1RSSI;
    INT16  sRxANT2RSSI;
	INT16  sRxANT3RSSI;
    INT16  sRxANT4RSSI;
} CT_F_ANT_RSSI_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 usFreqNum;
    UINT16 usPowNum;

    CT_F_ANT_RSSI_STRU  astRxANTRSSI[FREQ_MAX_NUM][POW_MAX_NUM];
} PHY_OM_CT_F_MEAS_RSSI_IND_STRU;

/*****************************************************************************
 ���� :
 ID   : PHY_OM_CT_F_MEAS_CMTMS_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_CMTMS_IND_STRU
 ˵�� :
*****************************************************************************/

typedef struct
{
    UINT32  ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16  usMsgStatus;
    UINT16  usCmtsReadStatus;
#endif
    UINT16  usCmtmsNum; 					     /* �¶�ֵ������ȡֵ��ΧΪ0��16*/
    UINT16  usType;

    UINT16  ausCmtms[FREQ_MAX_NUM]; /* �¶�ֵ�б�ȡֵ��ΧΪ0��256�����¶�ֵ����Ϊ0��û���¶�ֵ�б�*/

} PHY_OM_CT_F_MEAS_CMTMS_IND_STRU;


/*****************************************************************************
 ���� : ָʾRTT����PA
 ID   : OM_PHY_CT_F_PA_SET_REQ,PHY_OM_CT_F_PA_SET_CNF
 REQ  : OM_PHY_CT_F_PA_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
#define CT_F_PA_SET_MAX_NUM   (30)
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usLevelNum;
    UINT16 usRsv;
    UINT8 aucLvlList[CT_F_PA_SET_MAX_NUM];
} OM_PHY_CT_F_PA_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_PA_SET_CNF_STRU;

/*****************************************************************************
 ���� : ����ʹ��PD��־
 ID   : OM_PHY_CT_F_PD_REQ_STRU,OM_PHY_CT_F_PD_CNF_STRU
 REQ  : OM_PHY_CT_F_PD_REQ_STRU
 CNF  : OM_PHY_CT_F_PD_CNF_STRU
 IND  : PHY_OM_CT_F_PD_IND_STRU
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                          /* ��Ϣ��ʶ */
    UINT32 ulPdEnbFlg;                       /*ָʾPD�Ƿ�ʹ��*/
    UINT16 usDacCfg;
    UINT16 usVgaCfg;
} OM_PHY_CT_F_PD_REQ_STRU;

typedef PHY_MSP_CT_SINGLE_CNF_STRU PHY_OM_CT_F_PD_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*��Ϣ��ʶ  */
    UINT16 ausFreqVota[FREQ_MAX_NUM][POW_MAX_NUM];
} PHY_OM_CT_F_PD_IND_STRU;

/*****************************************************************************
 ���� : PD��У׼ʹ��
 ID   : OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU,OM_PHY_CT_F_AUTO_CAL_CNF_STRU
 REQ  : OM_PHY_CT_F_AUTO_CAL_REQ_STRU
 CNF  : PHY_OM_CT_F_PD_AUTO_IND_STRU
 IND  : NAN
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ   */
    UINT32 ulPdAutoFlg;                  /*ָʾPD�Ƿ�ʹ��*/
} OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU;

typedef PHY_MSP_CT_SINGLE_CNF_STRU PHY_OM_CT_F_PD_AUTOCAL_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*��Ϣ��ʶ  */
    UINT16 usDacCfg;                     /*��У׼��õ�DAC����*/
    UINT16 usVgaCfg;                     /*��У׼��õ�VGA����*/
    UINT16 usVgaErrorFlg;                /*VGAУ׼�쳣��־*/
    UINT16 usRsv;
} PHY_OM_CT_F_PD_AUTO_IND_STRU;

/*****************************************************************************
 ���� : ָʾRTT����SEGMENT
 ID   : OM_PHY_CT_F_SEGMENT_SET_REQ,PHY_OM_CT_F_SEGMENT_SET_CNF
 REQ  : OM_PHY_CT_F_SEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_SEGMENT_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
    UINT16 usSegment;                    /* 10,20���� */
    UINT16 measOffset;                   /* ��ʾ������ʼλ��ƫ�ƣ���λms��ȡֵ��Χ0~20����Ĭ��ֵ*/
	UINT16 measLen;                      /* ��ʾ�������ȣ���λms��ȡֵ��Χ0~20����Ĭ��ֵ */
    UINT16 usRsv;
} OM_PHY_CT_F_SEGMENT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_SEGMENT_SET_CNF_STRU;

/*****************************************************************************
 ���� : ָʾRTT���÷��䲨��
 ID   : OM_PHY_CT_F_TXWAVE_SET_REQ,PHY_OM_CT_F_TXWAVE_SET_CNF
 REQ  : OM_PHY_CT_F_TXWAVE_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXWAVE_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* < wave_type >  ���÷�����ķ��䲨��*/
    /*   0    CW���ͣ�DSPĬ������ΪCW���ͣ�*/
    /*   1    LTE����(1.4M)*/
    /*   2    LTE����(3M)*/
    /*   3    LTE����(5M)*/
    /*   4    LTE����(10M)*/
    /*   5    LTE����(15M)*/
    /*   6    LTE����(20M)*/
    /*   11  TDS����(1.6M)*/
    UINT16 usWaveType;

    INT16 usPower;
} OM_PHY_CT_F_TXWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXWAVE_SET_CNF_STRU;

/*****************************************************************************
 ���� : ��������У׼TRIGGER������У׼����
 ID   : OM_PHY_CT_F_TRIGGER_SET_REQ,PHY_OM_CT_F_TRIGGER_SET_CNF ����ID
        OM_PHY_CT_F_TRIGGER_RD_REQ,PHY_OM_CT_F_TRIGGER_RD_CNF   ��ѯID
 REQ  : OM_PHY_CT_F_TRIGGER_SET_REQ_STRU OM_PHY_CT_F_TRIGGER_RD_REQ_STRU
 CNF  : PHY_OM_CT_F_TRIGGER_SET_CNF_STRU PHY_OM_CT_F_TRIGGER_RD_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */

    /* 0    ����ͨ��У׼*/
    /* 1    ����ͨ��У׼������Ĭ��Ϊ˫ͨ����*/
    /* 2    ����/����ͨ��ͬʱУ׼������Ĭ��Ϊ˫ͨ����*/
    UINT8 ucType;

    UINT8 padding[3];
} OM_PHY_CT_F_TRIGGER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TRIGGER_SET_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
} OM_PHY_CT_F_TRIGGER_RD_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usRsv;
#endif
    /* 0    ����ͨ��У׼*/
    /* 1    ����ͨ��У׼������Ĭ��Ϊ˫ͨ����*/
    /* 2    ����/����ͨ��ͬʱУ׼������Ĭ��Ϊ˫ͨ����*/
    UINT8 ucType;

    /* ����У׼״̬*/
    /* 0    δ������ִ�����*/
    /* 1    ִ����*/
    UINT8 ucStatus;

    UINT8 ucRsv[2];
} PHY_OM_CT_F_TRIGGER_RD_CNF_STRU;

/*BLOCKING*/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usIsBLKMode;
	UINT16 usRsv;
}OM_PHY_CT_F_BLK_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_BLK_SET_CNF_STRU;

/*IP2*/
typedef struct
{
    UINT32 ulMsgId;       /*��Ϣ��ʶ*/
    UINT16 usBand;        /*IP2У׼bandֵ*/
    UINT16 usRsv;
} OM_PHY_CT_F_IP2START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;       /*��Ϣ��ʶ*/
} PHY_OM_CT_F_IP2START_CNF_STRU;


typedef struct
{
    UINT32 ulMsgId;       /*��Ϣ��ʶ*/
    INT16 ulIP2Value1;     /*IP2У׼���1*/
    INT16 ulIP2Value2;     /*IP2У׼���2*/
} PHY_OM_CT_F_MEAS_IP2_IND_STRU;
/*PHY_OM_CT_F_MEAS_IP2_IND_STRU*/

/*****************************************************************************
 ���� : MAXPOWERУ׼����
 ID   : OM_PHY_CT_F_MAX_POWER_REQ,PHY_OM_CT_F_MAX_POWER_CNF
 REQ  : OM_PHY_CT_F_MAX_POWER_REQ_STRU
 CNF  : PHY_OM_CT_F_MAX_POWER_CNF_STRU
 IND  : NAN
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ*/
    UINT16 usPaLevelNum;                 /*��ҪУ׼��PA ��λ��Ŀ0-4*/
    UINT16 usPaReduceGain;               /*����20111029��0-20*/
} OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*��Ϣ��ʶ*/
} PHY_OM_CT_F_MAX_POWER_SET_CNF_STRU;

/*****************************************************************************
 ���� : PAPOWER����
 ID   : OM_PHY_CT_F_PA_POWER_SET_REQ,PHY_OM_CT_F_PA_POWER_SET_CNF
 REQ  : OM_PHY_CT_F_PA_POWER_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_POWER_SET_CNF_STRU
 IND  : NAN
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ*/
    UINT16 usPaLevelNum;
    UINT16 usRsv;
    INT16 asMaxPwrList[4];              /*У׼���MAXPOWERֵ*/
} OM_PHY_CT_F_PA_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*��Ϣ��ʶ*/
} PHY_OM_CT_F_PA_POWER_SET_CNF_STRU;

/*****************************************************************************
 ���� : 8.6	����С����Ϣ��ѯ����^LTESCINFO
 ID   : OM_PHY_RD_LTESCINFO_REQ_STRU,OM_PHY_RD_LTESCINFO_CNF_STRU   ��ѯID
 REQ  : OM_PHY_RD_LTESCINFO_REQ_STRU
 CNF  : OM_PHY_RD_LTESCINFO_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
} OM_PHY_RD_LTESCINFO_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

    UINT16 usCid;     /* ����С��ID,ȡֵ��Χ��0 ~ 503 ��65535��ʾû�л�ȡ����ǰ����С��ID*/

    INT16  usDlSinr ; /* ������·�����,ȡֵ��Χ��-20 ~ 30*/
    UINT16 usDlBw ;   /* LTE downlink bandwidth*/

    UINT8  ucNumAnt;  /* ��ǰ���߸���,0~4*/
    UINT8  ucRsv;
} PHY_OM_RD_LTESCINFO_CNF_STRU;


/*****************************************************************************
 ���� : �������۲����õ���ͬ��״̬
 �ڵ���״̬�´���UE���۲��ǣ�MT8820C/CMW500����ͬ�����̣���ͬ���ɹ�ֱ�ӷ���OK�����򷵻�ERROR��
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ID   : OM_PHY_SYN_SSYNC_SET_REQ,PHY_OM_SYN_SSYNC_SET_CNFs
 REQ  : OM_PHY_SYN_SSYNC_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;     /* ��Ϣ��ʶ */
    UINT16 usMode;      /* MODE TDD��1��FDD��0*/
    UINT16 usBand;      /* LTEƵ����Ϣ��ȡֵ��Χ1��50����7����Band7*/
    UINT16 usUlchannel; /* ����ͬ���ŵ���ȡֵ��Χ0��65535*/
    UINT16 usDlchannel; /* ����ͬ���ŵ���ȡֵ��Χ0��65535*/
} OM_PHY_SYN_SSYNC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSYNC_SET_CNF_STRU;

/*****************************************************************************
 ���� : �������۲��ѯ����ͬ��״̬
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ID   : OM_PHY_SYN_SSYNC_RD_REQ,PHY_OM_SYN_SSYNC_RD_CNF
 REQ  : OM_PHY_SYN_SSYNC_RD_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_RD_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
/*DSP�����ϱ�*/
typedef struct
{
    UINT32 ulMsgId;

    /* UE���۲���ͬ��״̬ */
		/* 0	�Ѿ�ͬ���ɹ�*/
		/* 1	δͬ����ͬ��ʧ��*/
    UINT32 ulStatus;
} PHY_OM_SYN_SSYNC_RPT_IND_STRU;


/*****************************************************************************
 ���� : ^STXBW �������۲����÷������
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ��(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXBW_SET_REQ,PHY_OM_SYN_STXBW_SET_CNF
 REQ  : OM_PHY_SYN_STXBW_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXBW_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* ���۲�������з��������б�ȡֵ��Χ0~5��Ĭ��ֵΪ0*/
    /* 0	1.4M*/
    /* 1	3M*/
    /* 2	5M*/
    /* 3	10M*/
    /* 4	15M*/
    /* 5	20M*/
    UINT16 usBandwide;
    UINT16 usRsv;
} OM_PHY_SYN_STXBW_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXBW_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SCONFIG �������۲�������֡���
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ID   : OM_PHY_SYN_SCONFIG_SET_REQ,PHY_OM_SYN_SCONFIG_SET_CNF
 REQ  : OM_PHY_SYN_SCONFIG_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SCONFIG_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* RTTͨ��usFrameNumer/usFrameDeno,������֡���usFrameNumer=7��usFrameDeno=6��*/
    /* usFrameNumer/usFrameDeno=7/6*/
    UINT16 usSubFrameAssign;
    UINT16 usSubFramePattern;
} OM_PHY_SYN_SSUBFRAME_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSUBFRAME_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^STXCHAN �������۲�
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ��(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXCHAN_SET_REQ,PHY_OM_SYN_STXCHAN_SET_CNF
 REQ  : OM_PHY_SYN_STXCHAN_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHAN_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* ����ͬ���ŵ���ȡֵ��Χ0��65535*/
    UINT16 usUlchannel ;
    UINT16 usRsv;
} OM_PHY_SYN_STXCHAN_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHAN_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SPARA �������۲�������֡���
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 ˵�� :
*****************************************************************************/

typedef struct
{
	UINT32 ulMsgId;
	/*���ò������ͣ�ȡֵ��Χ0~32*/
	UINT16 usType;
	/*���ò���ֵ��ȡֵ��Χ0~65535*/
	UINT16 usValue;

} OM_PHY_SYN_SPARA_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SPARA_SET_CNF_STRU;
/*****************************************************************************
 ���� : ^SSEGNUM �������۲�����SEGMENT������
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSegNum;
	UINT16 usReserved;

} OM_PHY_SYN_SSEGNUM_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SSEGNUM_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^STXMODUS �������۲����õ��Ʒ�ʽ
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ��(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXMODUS_SET_REQ,PHY_OM_SYN_STXMODUS_SET_CNF
 REQ  : OM_PHY_SYN_STXMODUS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXMODUS_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* �����۲���Ե��Ʒ�ʽ��������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/
    UINT16 usModulution_num  ;
	UINT16 usRsv;

    /* �����۲���Ե��Է�ʽ�б�ȡֵ��Χ0~2��Ĭ��ֵΪ0*/
    /* ������0����QPSK��1����16QAM��2����64QAM��*/
    UINT16  usModulation_list [256];

} OM_PHY_SYN_STXMODUS_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXMODUS_SET_CNF_STRU;
/*****************************************************************************
 ���� : ^STXRBNUMS �������۲�����RB����
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* �����۲�������з���RB��������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/
    UINT16 usRb_num;
	UINT16 usRsv;
	/* �����۲�������з���RB���б�ȡֵ��Χ1~100��Ĭ��ֵ1*/
    UINT16 usrb_list[256];
} OM_PHY_SYN_STXRBNUMS_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBNUMS_SET_CNF_STRU;


/*****************************************************************************
 ���� : ^STXRBPOSS �������۲�����RBλ��
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����RB������^SRBNUMS����ִ�С�(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXRBPOSS_SET_REQ,PHY_OM_SYN_STXRBPOSS_SET_CNF
 REQ  : OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 usRbpos_num; /* �����۲�������з���RBλ�õ�������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/
	UINT16 usRsv;

	UINT16 usrbpos_list[256];  /* �����۲�������з���RBλ�õ��б�ȡֵ��Χ0~99��Ĭ��ֵΪ0*/
} OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^STXPOWS �������۲����÷��书��
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ�С�(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXPOWS_SET_REQ,PHY_OM_SYN_STXPOWS_SET_CNF
 REQ  : OM_PHY_SYN_STXPOWS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXPOWS_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 ulPow_num;   /* �����۲�������з���RBλ�õ�������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/
	UINT16 usRsv;

	INT16 slPow_list[256];  /* �����۲�������з���RBλ�õ��б�ȡֵ��Χ0~99��Ĭ��ֵΪ0*/
} OM_PHY_SYN_STXPOWS_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXPOWS_SET_CNF_STRU;


/*****************************************************************************
 ���� : ^STXCHANTYPES �������۲������ŵ�����
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ�С�(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_STXCHANTYPES_SET_REQ,PHY_OM_SYN_STXCHANTYPES_SET_CNF
 REQ  : OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 usType_num; /* �����۲�������з����ŵ���������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/
    UINT16 usRsv;
		/* 0	PUSCH*/
		/* 1	PUCCH*/
		/* 2	PRACH*/
    UINT16 usType_list[256];/*	�����۲�������з����ŵ����б�ȡֵ��Χ0~2*/
} OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SSEGLEN �������۲�����SEGMENT����
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ��������Ҫ�����÷������۲�ͬ����^SSYNC����ִ�С�(MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_SSEGMENT_SET_REQ,PHY_OM_SYN_SSEGMENT_SET_CNF
 REQ  : OM_PHY_SYN_SSEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSEGMENT_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* 10	10ms*/
    /* 20	20ms*/
	/* 50	50ms*/
	/* 100	100ms*/
    UINT16 usSegment_Len; /* �����۲�������з����ŵ���������ȡֵ��Χ0~50��Ĭ��ֵΪ0*/


    UINT16 usReserved;
} OM_PHY_SYN_SSEGLEN_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSEGLEN_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SRXPOW �������۲���ղ��ԵĹ�������
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣



 ID  :
 REQ :
 CNF :
 IND : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSwitch;
	INT16  sPower;
	UINT16 usMod;
	UINT16 usRBNum;
	UINT16 usRBPos;
	UINT16 usRsv;

}OM_PHY_SYN_SRXSET_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSET_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SRXSUBFRA �������۲���ղ��Ե���֡����
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣



 ID  :
 REQ :
 CNF :
 IND : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSubFrameNum;
	UINT16 usReserved;

}OM_PHY_SYN_SRXSUBFRA_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSUBFRA_SET_CNF_STRU;
/*****************************************************************************
 ���� : ^SRXBLER �������۲���ղ��Բ�ѯ������
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣



 ID  :
 REQ :
 CNF :
 IND : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBler[2];
	INT16  sSnr[2];
} PHY_OM_SYN_SRXMEAS_RPT_IND_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBersum;
	UINT32 ulBerErr;
	UINT32 usRsv;
} PHY_OM_SYN_SRXMEAS_TDS_RPT_IND_STRU;


typedef struct
{
    UINT32 ulMsgId;
	INT16  usPower;
	UINT16 usRsv;
} OM_PHY_SYN_FPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_FPOW_SET_CNF_STRU;
/*****************************************************************************
 ���� : ^SSTART �������۲��������䲢״̬��ѯ
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ����״̬������sequence��ʽ�ķ������۲⡣
 ��������Ҫ������AT^SSYNC��AT^SMODUS��AT^STXBWS��AT^SPOWS��AT^SCHANS��AT^SSEGMENT�����ִ�С�����ģʽ�·��ش����롣
 (MSP���ԼӼ��жϣ�����ʵ�ֿ����Ȳ�����)
 ID   : OM_PHY_SYN_SSTART_SET_REQ,PHY_OM_SYN_SSTART_SET_CNF
 REQ  : OM_PHY_SYN_SSTART_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTART_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTART_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTART_SET_CNF_STRU;

/*****************************************************************************
 ���� : ^SSTOP �������۲�ֹͣ���з���
 ^TMODE=7��ʹ�ã����ڷ�TMODE=7�������MSPֱ�ӷ��ش����롣
 ID   : OM_PHY_SYN_SSTOP_SET_REQ,PHY_OM_SYN_SSTOP_SET_CNF
 REQ  : OM_PHY_SYN_SSTOP_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTOP_SET_CNF_STRU
 IND  : NA
 ˵�� :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTOP_SET_REQ_STRU;

/* ��������Ϊ�ɹ�*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTOP_SET_CNF_STRU;


//*****************************************************************************
// ���� : �����빦������
// ID   : OM_PHY_CT_FWAVE_SET_REQ,PHY_OM_CT_FWAVE_SET_CNF
// REQ  : OM_PHY_CT_FWAVE_SET_REQ_STRU
// CNF  : PHY_OM_CT_FWAVE_SET_CNF_STRU
// ˵�� :
//*****************************************************************************
typedef struct
{
    UINT32 ulMsgId;                      /* ��Ϣ��ʶ */
    UINT16 usType;                       /*0:��ʾcontinues wave�ź�; 1:��ʾ1.4MHz LTE�ź�*/
    INT16 usPower;                       /*2300:23db*/
} OM_PHY_CT_FWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FWAVE_SET_CNF_STRU;



/* Begin: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */
/*****************************************************************************
 �ṹ��    : LMSP_LPHY_COEX_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_COEX_BW_TYPE_ENUM_UINT16         enCoexBWType;
    LMSP_LPHY_COEX_ENABLE_IND_ENUM_UINT16      enCoexEnableInd;
    UINT16                                     usTx_begin;
    UINT16                                     usTx_End;
    INT16                                      sTxPower;
    UINT16                                     usRx_begin;
    UINT16                                     usRx_End;
    UINT16                                     usReserved;
} LMSP_LPHY_COEX_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_MSG_ID_ENUM_UINT32               enMsgId;
    UINT16                                     usCoexParaNum;
    UINT16                                     usCoexParaSize;
    UINT8	                                   aucCoexPara[4];
} LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_MSG_ID_ENUM_UINT32               enMsgId;
    UINT16                                     usReserved;
    LMSP_LPHY_RESULT_ENUM_UINT16               enCoexParaConfigResult;
} LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU;

/* End: Added by luzhejun, 2013-08-29,PN:LTE_WIFI */
//*****************************************************************************
// ���� : ͨ��AT��������
// ID   : OM_PHY_COMM_CMD_SET_REQ,PHY_OM_COMM_CMD_SET_CNF,PHY_OM_COMM_CMD_IND
// REQ  : OM_PHY_COMM_CMD_SET_REQ_STRU
// CNF  : PHY_OM_COMM_CMD_SET_CNF_STRU
// ˵�� :
//*****************************************************************************
#define MAX_COMM_CMD_LEN 1152

typedef struct
{
    UINT32 ulMsgId;                  /* ��Ϣ��ʶ */
    UINT32 ulDataLen;                /* ���ݳ��� */
    INT8   cData[MAX_COMM_CMD_LEN];   /* ����     */
}OM_PHY_COMM_CMD_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                  /* ��Ϣ��ʶ */
    UINT32 ulDataLen;                /* ���ݳ��� */
    INT8   cData[MAX_COMM_CMD_LEN];   /* ����     */
}PHY_OM_COMM_CMD_SET_CNF_STRU;

typedef PHY_OM_COMM_CMD_SET_CNF_STRU PHY_OM_COMM_CMD_IND_STRU;


typedef struct
{
    UINT16 usWave;                                 /* CW����0�� LTE����1  */
    UINT16 usSegment;                              /* ���͵�һ����ʱ������λms  */

    UINT16 usRsv;
    UINT16 usFreqNum;
    UINT16 ausFreqList[FREQ_MAX_NUM];


    UINT32 ulTxRfCodeNum;                          /*����RF������*/
    UINT16 ausTxRfCode [TX_POW_MAX_NUM];           /*���书�ʿ����֣�����RF��IF������*/

    UINT16 usDbbNum;                               /**/
    UINT16 usDbbCode;                              /*DBB���ʿ�����*/

    UINT32 ulPaNum;
    UINT8  aucPaLevel[TX_POW_MAX_NUM];

    UINT32 ulPwrNum;
    INT16  sPowerTable[TX_POW_MAX_NUM];            /*����LIST*/

    UINT32 ulAptEnbFlg;

    UINT32 ulPdEnbFlg;
    UINT16 usVgaCfg;
    UINT16 usDacCfg;
}CT_F_TX_PARA_STRU;

typedef struct
{
    UINT32 ulCmdId;                      /*��Ϣ��ʶ*/
    CT_F_TX_PARA_STRU    stTxPara;
} CT_F_APCCAL_SET_REQ_STRU;

typedef struct
{
    UINT32 ulCmdId;                      /*��Ϣ��ʶ*/
    UINT8  ucType;
    UINT8  aucRsv[3];
} CT_F_APCCAL_START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;           /*��Ϣ��ʶ*/
    UINT16 usMode;            /*UE ģʽ*/
    UINT16 usBand;            /*Ƶ��*/
    UINT16 usDLStFreq;       /*����ɨƵ��ʼƵ��*/
    UINT16 usDLEdFreq;       /*����ɨƵ����Ƶ��*/
    UINT16 usFreqStep;       /*����ɨƵ����*/
    INT16   usTxPwr;            /*���з��书��*/
    UINT16 usBandWidth;
    UINT16 usRsv;
}OM_PHY_NOISE_CFG_REQ_STRU;

typedef struct
{
    UINT16 usDLFreq;       /*��ǰ����Ƶ��*/
    INT16   sDLPriRssi;   /*PHY�ϱ�����Ƶ���Ӧ��RSSI*/
    INT16   sDLDivRssi;   /*PHY�ϱ��ּ�Ƶ���Ӧ��RSSI*/
    UINT16 usRsv;
}PHY_NOISE_RESULT_STRU;
typedef struct
{
    UINT16 usDLRssiNum;
    UINT16 usRsv;
    PHY_NOISE_RESULT_STRU astDlRssiResult[32];
}LHPA_NOISE_RESULT_STRU;
typedef struct
{
    UINT32 ulMsgId;
    LHPA_NOISE_RESULT_STRU  stRssiInd;
}PHY_OM_NOISE_RSSI_IND_STRU;

/*ͨ��AT����CmdId*/
typedef enum
{
	COMM_AT_CMD_ID_RFTEST              = 0x0,
	COMM_AT_CMD_QUERY_BANDINFO,
	COMM_AT_CMD_QUERY_RX_POWER,
	COMM_AT_CMD_QUERY_HKADC,

    COMM_AT_CT_AAGCSET_CMDID           = 0x6,
    COMM_AT_CT_APCCAL_CMDID            = 0x7,
    COMM_AT_CT_APCSTART_CMDID          = 0x8,
    COMM_AT_CT_TXPARA_CMDID            = 0x9,
    COMM_AT_ET_SWITCH_CMDID            = 0xa,
    COMM_AT_ET_VOUT_CAL_REQ_CMDID,
    COMM_AT_ET_VOUT_REPORT_CMDID,
    COMM_AT_ET_LUT_SET_CMDID,
    COMM_AT_ET_FINEDLY_PARA_SET_CMDID,
    COMM_AT_ET_EVELY_SET_CMDID,
    COMM_AT_CT_CA_RF_RCCAL_Req,
    COMM_AT_CT_RFCAL_SETCODE_CMDID,
	COMM_AT_COM_NOTCH_SET              = 0x14,
	COMM_AT_CMD_XO_C2FIX               = 0x15,
	COMM_AT_CMD_XO_FRESH_C2FIX,
	COMM_AT_CMD_XO_C1FIX,
	COMM_AT_CMD_XO_FRESH_C1FIX,
	COMM_AT_CMD_XO_AFC_CAL,
	COMM_AT_CMD_XO_QUERY_HKADC,
	COMM_AT_CMD_XO_FRESH_AFC_TEMP,
	COMM_AT_CMD_RF_TOOL 
}NCIT_BTCT_COMM_AT_CMDID;



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#elif defined(MS_VC6_PLATFORM)
#pragma pack(pop)
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif //end of _DSP_CT_EX2_H

