

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PHYRFCALINTERFACE_HI6360_H__
#define __PHYRFCALINTERFACE_HI6360_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define MASK_SELF_CAL_TX_IQ_MISMATCH_HI6360        ( 0x0001 )
#define MASK_SELF_CAL_W_RX_DCR_HI6360              ( 0x0002 )
#define MASK_SELF_CAL_W_RX_IP2_HI6360              ( 0x0004 )

#define SELF_CAL_BAND_ID_MAX_COUNT_HI6360          ( 10 )

#define W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360         ( 8 )
#define W_RX_BLOCK_AGC_GAIN_COUNT_HI6360           ( 5 )

/* Mask code Used for RF_CAL_W_CFG_REQ_STRU */
#define MASK_CAL_RF_W_TX_AFC_HI6360                ( 0x0001 )
#define MASK_CAL_RF_W_TX_ARFCN_HI6360              ( 0x0002 )
#define MASK_CAL_RF_W_TX_TXONOFF_HI6360            ( 0x0004 )
#define MASK_CAL_RF_W_TX_PAMODE_HI6360             ( 0x0008 )
#define MASK_CAL_RF_W_TX_DBB_RF_ATTEN_HI6360       ( 0x0010 )
#define MASK_CAL_RF_W_TX_POWER_HI6360              ( 0x0020 )
#define MASK_CAL_RF_W_RX_RXONOFF_HI6360            ( 0x0040 )
#define MASK_CAL_RF_W_RX_ARFCN_HI6360              ( 0x0080 )
#define MASK_CAL_RF_W_RX_ANTSEL_HI6360             ( 0x0100 )
#define MASK_CAL_RF_W_RX_CARRMODE_HI6360           ( 0x0200 )
#define MASK_CAL_RF_W_TX_PWR_ATTEN_HI6360          ( 0x0400 )
#define MASK_CAL_RF_W_PD_ONOFF_HI6360              ( 0x0800 )
#define MASK_CAL_RF_W_RX_AGC_GAIN_HI6360           ( 0x1000 )
#define MASK_CAL_RF_W_TX_PA_VBIAS_HI6360           ( 0x2000 )
#define MASK_CAL_RF_W_TX_CFIX_HI6360               ( 0x4000 )
#define MASK_CAL_RF_W_TX_UPA_HI6360                ( 0x8000 )

/* Mask code Used for PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360 */
#define MASK_CAL_RF_W_TX_FAST_PDM_HI6360           ( 0x0001 )
#define MASK_CAL_RF_W_TX_FAST_PWR_HI6360           ( 0x0002 )
#define MASK_CAL_RF_W_TX_FAST_ATTEN_HI6360         ( 0x0004 )
#define MASK_CAL_RF_W_TX_FAST_PAVBIAS_HI6360       ( 0x0008 )
#define MASK_CAL_RF_W_TX_FAST_PDVGA_HI6360         ( 0x0010 )
#define MASK_CAL_RF_W_TX_FAST_PDDISTUNE_HI6360     ( 0x0020 )

/* W Rx �ز�ģʽ */
#define W_RX_CARRIER_MODE_SC_HI6360                ( 0 )
#define W_RX_CARRIER_MODE_DC_HI6360                ( 1 )

#define W_TRX_MAX_STEP_CNT_HI6360                  ( 16 )
#define W_TRX_MAX_SWEEP_FRAME_CNT_HI6360           ( 50 )

/* StepData Bit */
#define W_TX_PWR_ATTEN_BIT_HI6360                  ( 0x000003FF )
#define W_RX_AGC_MODE_BIT_HI6360                   ( 0x00003C00 )
#define W_TX_PA_MODE_BIT_HI6360                    ( 0x0000C000 )
#define W_TX_PA_VBIAS_BIT_HI6360                   ( 0x007F0000 )
#define W_TX_PD_VGA_BIT_HI6360                     ( 0x07800000 )
#define W_TX_PD_DISTUNE_BIT_HI6360                 ( 0x78000000 )

/* WģУ׼�ϱ�ʱ�ɹ�ʧ�ܱ�ʶ */
#define WPHY_TOOL_CAL_RESULT_RPT_SUCCESS_HI6360    ( 0 )
/*  G TRX CFG MARCO
*/
//////////////////////////////////////////////////////////////////////////
/* Mask code Used for RF_CAL_G_TX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_TX_AFC_HI6360         ( 0x0001 )  /* �·�����Ƶ�ʿ���ֵ */
#define MASK_CAL_RF_G_TX_ARFCN_HI6360       ( 0x0002 )  /* �·�����Ƶ�� */
#define MASK_CAL_RF_G_TX_TXEN_HI6360        ( 0x0004 )  /* �·��������λ */

/* Mask code Used for RF_CAL_G_RX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_RX_ARFCN_HI6360       ( 0x0001 )  /* �·�Ƶ�� */
#define MASK_CAL_RF_G_RX_MODE_HI6360        ( 0x0002 )  /* �·�����ģʽ */
#define MASK_CAL_RF_G_RX_AGCMODE_HI6360     ( 0x0004 )  /* �·�����ģʽ */
#define MASK_CAL_RF_G_RX_AGCGAIN_HI6360     ( 0x0008 )  /* �·�AGC��λ */

#define G_TX_PARA_MAX_SLOT_CNT_PER_FRAME_HI6360  ( 4 )

/* Mask code Used for PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */
#define MASK_RF_CAL_G_TX_FAST_POWER         ( 0x0001 )  /* �·�����(0.125dBm) */
#define MASK_RF_CAL_G_TX_FAST_AGC           ( 0x0002 )  /* �·�AGC */
#define MASK_RF_CAL_G_TX_FAST_POWER_ATTEN   ( 0x0004 )  /* �·�8PSK Power Atten */
#define MASK_RF_CAL_G_TX_FAST_PCL           ( 0x0008 )  /* �·�8PSK PCL */
#define MASK_RF_CAL_G_TX_FAST_PAVBIAS       ( 0x0010 )  /* �·�8PSK PaVbias */

#define G_TX_MAX_STEP_CNT_HI6360            ( 7 )       /* ��ǰֻ֧��4ʱ϶*/
#define G_TX_MAX_SWEEP_FRAME_CNT_HI6360     ( 120 )
#define G_RX_MAX_STEP_CNT_HI6360            ( 7 )
#define G_RX_MAX_SWEEP_FRAME_CNT_HI6360     ( 100 )
#define G_RX_MAX_RSSI_CNT_HI6360            ( G_RX_MAX_SWEEP_FRAME_CNT_HI6360 * G_RX_MAX_STEP_CNT_HI6360)
#define W_GAUGE_RESULT_SIZE_HI6360          ( 13 )      /* 32KУ׼�ϱ����ݸ��� */
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    :PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360
 Э����  :
 ASN.1���� :
 ö��˵��  :RF CAL MSG ID ENUM
*****************************************************************************/
enum PHY_TOOL_MSG_ID_ENUM_HI6360
{
    /* WCDMA RF����У׼�ӿ�ԭ���б� */
    ID_TOOL_WPHY_CAL_TRX_PARA_CFG_REQ_HI6360       = 0x1230,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360 */

    ID_TOOL_WPHY_CAL_RX_RSSI_MEAS_REQ_HI6360       = 0x1231,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_RX_RSSI_MEAS_IND_HI6360       = 0x21EA,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360 */

    /* WCDMA RF��У׼�ӿ�ԭ���б� */
    ID_TOOL_WPHY_CAL_SELF_CAL_REQ_HI6360           = 0x1229,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_SELF_CAL_IND_HI6360           = 0x21E8,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360 */

    /* WCDMA RF����У׼�ӿ�ԭ���б� */
    ID_TOOL_WPHY_CAL_TRX_FAST_CAL_REQ_HI6360       = 0x1227,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_TRX_FAST_CAL_IND_HI6360       = 0x21E6,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360 */

    /* W RFͨ��CNF */
    ID_WPHY_TOOL_CAL_RF_MSG_CNF_HI6360             = 0x21E0,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360 */

    ID_WPHY_TOOL_CAL_TX_POWER_DETECT_IND_HI6360    = 0x21E4,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360 */

    ID_WPHY_TOOL_GAUGE_REQ_HI6360                  = 0x1232,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_REQ_STRU */
    ID_WPHY_TOOL_GAUGE_CNF_HI6360                  = 0x21E5,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_CNF_STRU_HI6360 */
    ID_WPHY_TOOL_GAUGE_IND_HI6360                  = 0x21E6,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_IND_STRU_HI6360 */

    /* GSM RF����У׼�ӿ�ԭ���б� */
    ID_TOOL_GPHY_CAL_TX_PARA_CFG_REQ_HI6360 = 0x1732,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU */
    ID_TOOL_GPHY_CAL_RX_PARA_CFG_REQ_HI6360 = 0x1733,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU */

    ID_TOOL_GPHY_CAL_RX_RSSI_MEAS_REQ_HI6360= 0x1734,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_RSSI_MEAS_IND_HI6360= 0x7118,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU */

    /* GSM RF��У׼�ӿ�ԭ���б� */
    ID_TOOL_GPHY_CAL_SELF_CAL_REQ_HI6360           = 0x1731,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360 */
    ID_GPHY_TOOL_CAL_SELF_CAL_IND_HI6360           = 0x7116,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360 */

    /* GSM RF����У׼�ӿ�ԭ���б� */
    ID_TOOL_GPHY_CAL_TX_FAST_CAL_REQ_HI6360 = 0x1721,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */

    /* G RFͨ��CNF */
    ID_GPHY_TOOL_CAL_RF_MSG_CNF_HI6360      = 0x7112,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RF_MSG_CNF_STRU */

    ID_TOOL_GPHY_CAL_RX_FAST_CAL_REQ_HI6360 = 0x1720,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_FAST_CAL_IND_HI6360 = 0x7113,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU */

    ID_TOOL_GPHY_CAL_RX_IP2_CAL_REQ         = 0x1728,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_IP2_CAL_IND         = 0x7117,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU */

    ID_TOOL_GPHY_CAL_RX_DCR_START_REQ       = 0x1725,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_START_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_DCR_RPT_IND         = 0x7114,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU */
    ID_GPHY_TOOL_CAL_RX_DCR_STOP_CNF        = 0x7115,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU */

};
typedef UINT16 PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360;


/*****************************************************************************
 ö����    :RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16_HI6360
 Э����  :
 ASN.1���� :
 ö��˵��  :RF CAL W/G Self Cal Fail Code ENUM
*****************************************************************************/
enum RF_CAL_SELF_CAL_ERR_CODE_ENUM_HI6360
{
    RF_CAL_SELF_CAL_SUCCESS_HI6360                 = 0,
    RF_CAL_SELF_CAL_IQ_MISMATCH_FAIL_HI6360,
    RF_CAL_SELF_CAL_W_RX_DCOFFSET_FAIL_HI6360,
    RF_CAL_SELF_CAL_W_RX_IP2_FAIL_HI6360,
    RF_CAL_SELF_CAL_BUTT_HI6360,
};
typedef UINT16 RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16_HI6360;



/*****************************************************************************
 ö����    :W_FAST_TX_STEP_TYPE_ENUM_UINT16_HI6360
 Э����  :
 ASN.1���� :
 ö��˵��  :RF CAL W TRX FAST ENUM
*****************************************************************************/
enum W_FAST_TX_STEP_TYPE_ENUM_HI6360
{
    TX_STEP_TYPE_PDM_HI6360                        = 0,
    TX_STEP_TYPE_PWR_HI6360,
    TX_STEP_TYPE_ATTEN_HI6360,
    TX_STEP_TYPE_BUTT_HI6360
};
typedef UINT16 W_FAST_TX_STEP_TYPE_ENUM_UINT16_HI6360;


/*****************************************************************************
 ö����    :W_FAST_STEP_WIDTH_ENUM_UINT16_HI6360
 Э����  :
 ASN.1���� :
 ö��˵��  :RF CAL W TRX FAST ENUM
*****************************************************************************/

enum W_FAST_STEP_WIDTH_ENUM_HI6360
{
    WIDTH_10MS_HI6360                              = 10,
    WIDTH_20MS_HI6360                              = 20,
    WIDTH_30MS_HI6360                              = 30,
    WIDTH_40MS_HI6360                              = 40,
    WIDTH_BUTT_HI6360
};
typedef UINT16 W_FAST_STEP_WIDTH_ENUM_UINT16_HI6360;

/*****************************************************************************
 ö����    :G_MODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum G_MODE_TYPE_ENUM_HI6360
{
    MODE_GMSK_HI6360                               = 0,
    MODE_8PSK_HI6360                               = 1,
    MODE_BUTT_HI6360
};
typedef UINT16 G_MODE_TYPE_ENUM_UINT16_HI6360;


/*****************************************************************************
 ö����    :G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum G_SINGLE_SLOT_CTRL_MODE_ENUM_HI6360
{
    CTRL_GMSK_VPA_HI6360                           = 0,
    CTRL_POWER_HI6360                              = 1,
    CTRL_8PSK_PAVBIAS_DBB_RF_ATTEN_HI6360          = 2,
    CTRL_BUTT
};
typedef UINT16 G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16_HI6360;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360
 Э����  :
 �ṹ˵��  : WCDMA RF����У׼�ӿ� -- UPA���� ( ��ʱ�������� )
*****************************************************************************/
typedef struct
{
    /* ����Ĳ����Ƿ���UPA��Ҫʹ�õ� */
    UINT16                              usBec;
    UINT16                              usBed1;
    UINT16                              usBed2;
    UINT16                              usBc;
    UINT16                              usBd;
    UINT16                              usTxSlotFormat;     /* ����ģʽ:�������ʱ϶��ʽ */
    UINT16                              usTxChanNum;        /* ������� */
}PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  : WCDMA RF����У׼�ӿ�
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360      usMsgID;                                /* ԭ������ */
    UINT16                                  usRsv;                                  /* ����λ   */

    UINT16                                  usCfix;                                 /* DCXO Cfix �Ŀ����� */

    /* Tx Para Cfg */
    UINT16                                  usMask;                                 /* Reference MASK_CAL_RF_W_* */
    UINT16                                  usTxAfcInit;                            /* AFC��ֵ */
    UINT16                                  usTxBand;                               /* WģBAND:1��ʾBAND1,2��ʾBAND2,�������� */
    UINT16                                  usTxFreqNum;                            /* WģTXƵ���,��BAND1��9750 */
    UINT16                                  usTxEnable;                             /* 0:��ʹ��,1:ʹ�� */
    UINT16                                  usTxPaMode;                             /* 0:�Զ�����;1:������;2:������;3:������ */
    INT16                                   sTxPower;                               /* 0.1dBm */
    INT16                                   sDbbAtten;                              /* DBB���ź�˥���Ŀ����� */
    UINT16                                  usRfAtten;                              /* RF���ź�˥���Ŀ����� */
    INT16                                   sTxPwrAtten;                            /* ���źŵ�˥��,��λ0.1dBm */
    UINT16                                  usPaVbias;                              /* W PA Vbias �Ŀ����� */

    /* Rx Para Cfg */
    UINT16                                  usRxEnable;                             /* 0:��ʹ��,1:ʹ�� */
    UINT16                                  usRxBand;                               /* WģBAND:1��ʾBAND1,2��ʾBAND2,�������� */
    UINT16                                  usRxFreqNum;                            /* WģRXƵ���,��BAND1��10700 */
    UINT16                                  usRxAntSel;                             /* 1:��������;2:�ּ����� */
    UINT16                                  usRxAgcGain;                            /* BIT[15] : 1:5��, 0:8��;
                                                                                   BIT[3]  : 1:�Զ� 0:DSPǿ��5/8���е�ĳһ��
                                                                                   BIT[2:0]: 0:5/8���ĵ�һ��(������ߵ�),�������� */
    UINT16                                  usRxCarrMode;                           /* 0:���ز�;1:˫�ز� */

    /* ����Ĳ����Ƿ���UPA��Ҫʹ�õ�--Ϊ�˲�Ӱ�����е�AT����,���ڸýṹ�����������ر��� */
    UINT16                                  usUpaEnable;                            /* LMT����UPA�źŴ򿪹ر�.0:�ر�;1:�� */
    UINT16                                  usTxCarrMode;                           /* TX�ز�ģʽ.0:���ز�;1:˫�ز� */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360    stPrimCarr;                             /* ���ز���صĲ��� */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360    stSecondCarr;                           /* ���ز���صĲ��� */

}PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360
 Э����  :
 �ṹ˵��  : W TRX ������У׼ͨ��CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usRecMsgID;                             /* ��Ӧ���·�Msg ID */
    UINT16                              usFlag;
}PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    INT16                               sPdHkadc;
    UINT16                              usRsv2;
}PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usMeasNum;
    UINT16                              usInterval;
}PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    INT16                               sRSSI;
    UINT16                              usAgcState;
}PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  : WCDMA RF Self Cal�ӿ�
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usSelfCalMask;                          /* reference to MASK_SELF_CAL_* */
    UINT16                              usRfBandCount;                          /* ���DSPƵ�θ��� */
    UINT16                              ausBandId[SELF_CAL_BAND_ID_MAX_COUNT_HI6360];
}PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  : WCDMA RF Self Cal�ӿ�
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360 PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360;



/*****************************************************************************
 �ṹ��    : TX_IQ_MISMATCH_DCR_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    INT16                               sAmp;
    INT16                               sPhase;
    INT16                               sDci;
    INT16                               sDcq;
}TX_IQ_MISMATCH_DCR_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : RX_IQ_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    INT16                               sI;
    INT16                               sQ;
}RX_IQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : W_RX_DCOFFSET_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                          astScNoBlockAt1[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScBlockAt1[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcNoBlockAt1[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcBlockAt1[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScNoBlockAt2[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScBlockAt2[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcNoBlockAt2[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcBlockAt2[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
}W_RX_DCOFFSET_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : W_RX_IP2_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                          stHChanDivOn;
    RX_IQ_STRU_HI6360                          stHChanDivOff;
    RX_IQ_STRU_HI6360                          stMChanDivOn;
    RX_IQ_STRU_HI6360                          stMChanDivOff;
    RX_IQ_STRU_HI6360                          stLChanDivOn;
    RX_IQ_STRU_HI6360                          stLChanDivOff;
}W_RX_IP2_ANT1_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : W_RX_IP2_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                        stCalChanIQ[3];    // 0:���ŵ���1:���ŵ���2:���ŵ�
}W_RX_IP2_ANT2_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : W_SELF_CAL_RESULT_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UINT16                              usBandId;
    UINT16                              usRsv;
    TX_IQ_MISMATCH_DCR_STRU_HI6360      stTxIqMismatchDcr;
    W_RX_DCOFFSET_STRU_HI6360           stRxDcOffset;
    W_RX_IP2_ANT1_STRU_HI6360           stRxIp2Ant1;
}W_SELF_CAL_RESULT_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usErrCode;                              /* Reference to RF_CAL_SELF_CAL_* */
    UINT16                              usErrBand;                              /*���У׼ʧ�ܵ�Ƶ��*/
    UINT16                              usSelfCalMask;                          /*���DSP��У׼��*/
    UINT16                              usRfBandCount;                          /*���DSPƵ�θ���*/
    W_SELF_CAL_RESULT_STRU_HI6360       astSelfCalRlt[SELF_CAL_BAND_ID_MAX_COUNT_HI6360];
}PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : W_TRX_FAST_FRAME_STRU_HI6360
 Э����  :
 �ṹ˵��  : WCDMA RF����У׼�ӿ�
*****************************************************************************/
typedef struct
{
    UINT16                              usBand;
    UINT16                              usStepCnt;                              /* [1, 16] */
    UINT16                              usTxArfcn;
    UINT16                              usRxArfcn;
    UINT16                              usTxStepPattern;
    UINT16                              usRxStepPattern;
    UINT16                              usRxAgcModePattern;                     /* Bit -- set 1:Block; set 0:NoBlock */
    UINT16                              usRxCarrModePattern;                    /* Bit -- set 1:Double; set 0:Single */
    UINT32                              aulStepData[W_TRX_MAX_STEP_CNT_HI6360];        /* Bit[30:27]: PD Distune;
                                                                                   Bit[26:23]: PD VGA;
                                                                                   Bit[22:16]: TX PA VBIAS;
                                                                                   Bit[15:14]: Pa Mode;
                                                                                   Bit[13:10]: Rx Agc;
                                                                                   Bit[9:0]:   Tx PWR/ATTEN(0.1dBm)
                                                                                */
}W_TRX_FAST_FRAME_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usTxStepType;                           /* Reference to W_FAST_TX_STEP_TYPE_ENUM_HI6360 */
    UINT16                              usStepWidth;                            /* Reference to W_FAST_STEP_WIDTH_ENUM_HI6360 */
    UINT16                              usPowerDetect;                          /*1 - report detected volt; 0 - no report*/
    UINT16                              usTxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT_HI6360] */
    UINT16                              usRxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT_HI6360] */
    W_TRX_FAST_FRAME_STRU_HI6360        astSweepFrame[W_TRX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360;



/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usRssiCnt;                              /* 0:PDM, 1:Power */
    UINT16                              usPowerDetectorCnt;
    INT16                               asReportData[900];                      /*Rssi At1(0.125dBm)+Rssi At2(0.125dBm)+PD������� */
}PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360;



/*****************************************************************************
 �ṹ��    : G_RF_SINGLE_SLOT_CFG_STRU
 Э����  :
 �ṹ˵��  : G TX GSM RF����У׼�ӿ�
*****************************************************************************/
typedef struct
{
    UINT16                                     usTxMode;                               /* 0�� burst */
    G_MODE_TYPE_ENUM_UINT16_HI6360             usModType;                              /* ������Ʒ�ʽ:0��ʾGMSK����;1��ʾ8PSK����*/
    G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16_HI6360 usCtrlMode;                             /* ������Ʒ�ʽ��
                                                                                    0��GMSK��ѹ����,�˷�ʽ��usTxVpaҪ���ã�
                                                                                    1�����ʿ���,�˷�ʽ��usTxPowerҪ���ã�
                                                                                    2��8PSK PaVbias��ѹ&DBB Atten&RF Atten���ƣ�
                                                                                    usPAVbias��usRfAtten,sDbbAtten����������Ҫ���ã�*/
    UINT16                              usRfAtten;
    UINT16                              usTxPower;                              /* Ŀ�귢�书��,��λΪ0.1dBm,GSM��EDGE���� */
    UINT16                              usTxVpa;                                /* GSM PA���书�ʿ��Ƶ�ѹ */
    INT16                               sDbbAtten;
    UINT16                              usPAVbias;                              /* EDGE PA ���Ƶ�ѹ*/
}G_RF_SINGLE_SLOT_CFG_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usMask;                                 /* Reference to MASK_CAL_RF_G_TX_* */
    UINT16                              usAFC;
    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usTxEnable;                             /* ����ʹ�ܿ���:0x5555-ʹ�ܷ���;0xAAAA-ֹͣ����;TSC 0; */
    UINT16                              usDataPattern;                          /* 0��All 0��1��All 1��2��Random */
    UINT16                              usSlotCnt;                              /* ����ʱ϶��������Χ1~4��8,����ָ������ʹ����Щʱ϶��DSP�Զ�����1~4ʱ϶���� */
    G_RF_SINGLE_SLOT_CFG_STRU_HI6360    astSlotCfg[G_TX_PARA_MAX_SLOT_CNT_PER_FRAME_HI6360]; /* ÿ��ʱ϶��������� */
}PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU
 Э����  :
 �ṹ˵��  : G Rx
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    UINT16                              usMask;                                 /* Reference to MASK_CAL_RF_G_RX_* */
    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usRxMode;                               /* 0:burst����; 1:��������;Ŀǰֻ֧��burst���շ�ʽ */
    UINT16                              usAGCMode;                              /* Fast AGC,Slow AGC */
    UINT16                              usAGCGain;                              /* AGC��λ���Զ������嵵��ȡֵΪ�Զ���--0���嵵--1~5 */
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    UINT16                              usMeasNum;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    INT16                               sRSSI;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU_HI6360;



/*****************************************************************************
 �ṹ��    : G_SELF_CAL_RESULT_STRU
 Э����  :
 �ṹ˵��  : GSM RF��У׼�ӿ�
             ����Gģ��У׼��Req�ӿ���Wģ��ͬ
*****************************************************************************/
typedef W_SELF_CAL_RESULT_STRU_HI6360 G_SELF_CAL_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360 PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : G_RF_TX_STEP_STRU
 Э����  :
 �ṹ˵��  : GSM RF����У׼֡�ṹ
*****************************************************************************/
typedef struct
{
    INT16                               sPwrPara;                               /* Tx Power/Tx Agc/Power Atten(0.1dBm)/PCL according to usTxModeMask */
    UINT16                              usExternPara;                           /* PaVbias according to usTxModeMask, if no PaVbias_Mask DSP Use Max PaVbias */
}G_RF_TX_STEP_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : G_RF_TX_SEQUENCE_STRU
 Э����  :
 �ṹ˵��  : GSM RF����У׼�ӿ�
             G Tx
*****************************************************************************/
typedef struct
{
    G_RF_TX_STEP_STRU_HI6360                   astStepValue[G_TX_MAX_STEP_CNT_HI6360];        /*��ǰ���ֻ֧����ʱ϶*/
}G_RF_TX_SEQUENCE_HI6360_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usTxPattern;                            /* ��8Bit��Ч */
    G_MODE_TYPE_ENUM_UINT16_HI6360      usModType;                              /* 0:GMSK; 1:8PSK */
    UINT16                              usTxModeMask;                           /* Reference to MASK_RF_CAL_G_TX_FAST_ */
    UINT16                              usFrameCnt;
    UINT16                              usRsv;
    UINT16                              ausChannel[G_TX_MAX_SWEEP_FRAME_CNT_HI6360];   /*ausChannel��astTxSequenceһһ��Ӧ*/
    G_RF_TX_SEQUENCE_HI6360_STRU        astTxSequence[G_TX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RF_MSG_CNF_STRU
 Э����  :
 �ṹ˵��  : G TRX ������У׼ͨ��CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usRecMsgID;                             /* ���յ�����ϢID����ǰ��Ӧ����ϢID�� */
    UINT16                              usFlag;                                 /* 0:Correct��1:Error */
}PHY_RF_CAL_G_RF_MSG_CNF_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : G_RF_RX_SEQUENCE_STRU
 Э����  :
 �ṹ˵��  : G Rx
*****************************************************************************/
typedef struct
{
    UINT16                              usChannel;
    UINT16                              ausAgcGain[G_RX_MAX_STEP_CNT_HI6360];          /* ÿ֡������7��������λ */
}G_RF_RX_SEQUENCE_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    UINT16                              usChannelCnt;                           /* ����֡�� */
    UINT16                              usRsv2;
    G_RF_RX_SEQUENCE_STRU_HI6360        astRxSequence[G_RX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    UINT16                              usRssiNum;                              /* �������������ΪG_RX_MAX_RSSI_CNT��,������ͬ��֡ */
    UINT16                              usRsv2;
    INT16                               asRssiValue[G_RX_MAX_RSSI_CNT_HI6360];         /* ÿ֡�ϱ�7���㣬���G_RX_MAX_RSSI_CNT�� */
}PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_DCR_START_REQ_STRU
 Э����  :
 �ṹ˵��  : G Rx DCR
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usBandMask;                             /* Bit0:GSM850; Bit1:GSM900; Bit2:DCS; Bit3:PCS; */
    UINT16                              usFramesCnt;                            /* ͳ��֡�� */
}PHY_RF_CAL_G_RX_DCR_START_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv1;
    UINT16                              usFreq;                                 /* ������Ƶ�κź�Ƶ��ţ�band��12 | channel��*/
    UINT16                              usFreqIndex;                            /* Ƶ�������� */
    UINT16                              usGain;                                 /* ����ʹ�õĵ�λ����Χ0��1��2��3 */
    UINT16                              usRsv2;
    INT16                               sIDCOffset;
    INT16                               sQDCOffset;
}PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU_HI6360;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;                                  /* ����λ */
}PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU
 Э����  :
 �ṹ˵��  : G Rx IP2
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT16                              usFreqNum;                              /* (Band<<12)|Channel */
    UINT16                              usAGCGain;                              /* У׼ʱҪ���AGC״̬ */
}PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    INT16                               sIData;                                 /* I·����ֵ */
    INT16                               sQData;                                 /* Q·����ֵ */
}PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_GAUGE_REQ_STRU_HI6360
 Э����  :
 �ṹ˵��  : ����32K���������������ֹͣ
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-����32K����;0-ֹͣ32K���� */
}WPHY_TOOL_GAUGE_REQ_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_GAUGE_CNF_STRU_HI6360
 Э����  :
 �ṹ˵��  : ����32K���������������ֹͣ��ԭ��ظ�
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-����32K����;0-ֹͣ32K���� */
}WPHY_TOOL_GAUGE_CNF_STRU_HI6360;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_GAUGE_IND_STRU_HI6360
 Э����  :
 �ṹ˵��  : ����32K����������ϱ�
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* ԭ������ */
    UINT16                              usRsv;
    UINT32                              aulData[W_GAUGE_RESULT_SIZE_HI6360];
}WPHY_TOOL_GAUGE_IND_STRU_HI6360;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PhyRfCalInterface_hi6360.h */

