/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phytoolinterface.h
  �� �� ��   : ����
  ��    ��   : luoqingquan
  ��������   : 2012��8��14��
  ����޸�   :
  ��������   : phytoolinterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��14��
    ��    ��   : luoqingquan
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"



#ifndef __PHYTOOLINTERFACE_H__
#define __PHYTOOLINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  2.2 �궨��,W/G�궨��
*****************************************************************************/

/* ��ӡЯ���������� */
#define UPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )
#define UPHY_TOOL_INTER_REG_MAX_NUM             ( 300 )

/* ��ά�ɲ��func typeΪ4,intra msg������Ҫ��TOOLȷ�� */
#define UPHY_TOOL_MODEM2_FUNC_TYPE_OM_MSG       ( 0x84 )
#define UPHY_TOOL_MODEM2_FUNC_TYPE_INTRA_MSG    ( 0x94 )

#define UPHY_TOOL_MODEM1_FUNC_TYPE_OM_MSG       ( 0x44 )
#define UPHY_TOOL_MODEM1_FUNC_TYPE_INTRA_MSG    ( 0x54 )

#define UPHY_TOOL_MODEM0_FUNC_TYPE_OM_MSG       ( 0x04 )
#define UPHY_TOOL_MODEM0_FUNC_TYPE_INTRA_MSG    ( 0x1A )


/* ��С���뱣�ֺ�phyoaminterface.h��UPHY_OAM_SLEEP_INFO_NUMһ�� */
#define UPHY_TOOL_SLEEP_INFO_NUM                ( 16 )

/*****************************************************************************
  2.2 �궨��,GPHY�궨��
*****************************************************************************/

#if defined(INSTANCE_1)
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x48 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#elif defined (INSTANCE_2)
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x88 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#else
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x08 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#endif

#define CPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x12 )


/* PS����ʱ��������ʱ϶���� */
#define GPHY_PS_MAX_RX_TSN_NUM                  ( 5 )

/* PS����ʱ��������ʱ϶���� */
#define GPHY_PS_MAX_TX_TSN_NUM                  ( 4 )

/*****************************************************************************
 ԭ��GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU��ulFuncBitMaskÿ��bitλ�ĺ���;
 �����Ӧbitλ��1:���Ӧ����ʧЧ;
 �����Ӧbitλ��0:��ָ���Ӧ����;
*****************************************************************************/

#define GPHY_FUNC_DRX_USE_DISABLE_FLG           ( BIT0 )
#define GPHY_FUNC_DRX_SIMPLIFY_DISABLE_FLG      ( BIT1 )
#define GPHY_FUNC_BA_MEA_DISABLE_FLG            ( BIT2 )
#define GPHY_FUNC_INTERFERE_MEA_DISABLE_FLG     ( BIT3 )
#define GPHY_FUNC_C1_RESEL_DISABLE_FLG          ( BIT4 )
#define GPHY_FUNC_C2_RESEL_DISABLE_FLG          ( BIT5 )
#define GPHY_FUNC_NCELL_FBSB_DISABLE_FLG        ( BIT6 )
#define GPHY_FUNC_NCELL_SB_DISABLE_FLG          ( BIT7 )
#define GPHY_FUNC_NCELL_TASK_DISABLE_FLG        ( BIT8 )
#define GPHY_FUNC_RF_FRONT_DISPLAY_MNTN_FLG     ( BIT9 )



/* ��ά�ɲ����ݿ�����ϱ����� */
#define GPHY_TOOL_RPT_BLK_MAX_NUM               ( 10 )

/* ��ӡЯ���������� */
#define GPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )                           /* �����ϱ�ʱ���綨���ϱ��������� */


/*****************************************************************************
  2.3 �궨��,WPHY�궨��
*****************************************************************************/

#define WPHY_TOOL_PA_SWITCH_COMP_SLOT           ( 4 )                           /* W pa�л�����4��slot */
/* ��ӡЯ���������� */
#define WPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )                           /* �����ϱ�ʱ���綨���ϱ��������� */

/* ����С�������� */
#define WPHY_MNTN_MAX_ACT_CELL_NUM              ( 7 )                           /* ���С�������Ŀ */


/* ��ά�ɲ����ݿ�����ϱ����� */
#define WPHY_TOOL_RPT_BLK_MAX_NUM               ( 10 )

#define WPHY_MNTN_TRCH_NUM                      ( 8 )

#define WPHY_MNTN_SLAVE_REPORTFREQ_NUM          ( 3 )                           /* ��ģ��ν�ɲ��ϱ�Ƶ����� */
#define GPHY_TOOL_MA_FREQ_NUM                   ( 64 )                          /* ��Ƶ���еĸ��� */

#define GPHY_TOOL_BA_LIST_MAX_NUM               ( 32 )                          /* GSM BA LIST���ĸ��� */

#define GPHY_TOOL_AMR_MAX_ACS_NUM               ( 4 )                           /* ��󼤻���� */

#define GPHY_TOOL_RPT_MAX_LEN                   ( 100 )

#define GPHY_TOOL_AMR_CODEC_MAX_NUM             ( 8 )                           /* AMR��������� */

/* �����ÿ֡���ʱ϶���� */
#define GPHY_TOOL_TN_NUM_IN_FRAME               ( 8 )

#define GPHY_TOOL_MAX_UL_SLOT_NUM               ( 4 )                           /* Gsm��������ʱ϶���� */

#define GPHY_TOOL_MAX_IDLE_FRAME_NUM            ( 84 )                          /* ר��̬5S�ڿ���֡�������Ŀ */

#define GPHY_TOOL_MAX_SYNC_TASK_NUM             ( 5 )                           /* ר��̬����֡���������ͬ��������� */

#define GPHY_TOOL_MAX_NCELL_NUM                 ( 32 )                          /* �ϱ���������ϵͳ�����Ŀ */

#define GPHY_TOOL_NCELL_RPT_PREDICT_TASK_INFO_NUM  ( 5 )                        /* ר��̬��ӡ��Ԥ������ĸ��� */

#define WPHY_MNTN_HSUPA_SUB_FRM_NUM             ( 5 )                           /* HSUPA��֡�� */

#define WPHY_MNTN_HSUPA_OM_CARERIER_NUM         ( 2 )                           /* UPA ��ά�ɲ�ʹ�ã����������ز� */

#define WPHY_MNTN_HSUPA_RPT_VALUE_MAX_NUM       ( 100 )

#define WPHY_MNTN_RL_SCRAM_MAX_NUM              ( 7 )

#define WPHY_MNTN_DEMOD_FINGER_MAX_NUM          ( 13 )

#define WPHY_MNTN_EQ_FINGER_RPT_MAX_NUM         ( 2 )

#define WPHY_MNTN_BLER_RPT_MAX_NUM              ( 5 )

#define WPHY_MNTN_DPA_ERROR_CODE_RPT_MAX_NUM    ( 2 )

#define WPHY_MNTN_MP_WIN_MAX_NUM                ( 3 )

/* BCCH�������������� */
#define WPHY_MNTN_BCCH_QUEUE_LENGTH              ( 4 )

/* ademod�������������� */
#define WPHY_MNTN_ADMOD_QUEUE_LENGTH             ( 5 )

/* ���پ���ģ���֡�� */
#define WPHY_MNTN_CPC_DRX_PATTERN_FRAME_NUM      ( 5 )

/* CPC DRX������Ƶ������� */
#define WPHY_MNTN_CPC_DRX_EQUA_CTRL_TYPE_NUM     ( 2 )

/* CQI PATTERN���� */
#define WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM        ( 3 )

/* CPC DRX RF ���������� */
#define WPHY_MNTN_CPC_DRX_RF_CTRL_TYPE_NUM       ( 6 )

#define WPHY_MNTN_SLAVE_STEP23_CELL_NUM          ( 6 )

/* ���ICС������ */
#define WPHY_MNTN_IC_MAX_CELL_NUM                ( 2 )

/* DPA��Pֵ��Ŀ+1��ֱ��ʹ��Pֵ���±� */
#define WPHY_MNTN_P_VALUE_NUM                    ( 16 )

/* ����֡�ϱ�RAMƫ�� */
#define WPHY_MNTN_SUB_FRAME_ADDR_OFFSET          ( 0x30 )

/* ��֡�� */
#define WPHY_MNTN_SUB_FRAME_NUM                  ( 5 )

#define WPHY_MNTN_MAX_CNT                        ( 0xFFFFFFFF )

#define WPHY_MNTN_MAX_UINT16_VALUE               ( 0xFFFF )

#define WPHY_MNTN_MAX_CARRIER_NUM                ( 2 )

/* HSDSCH��������ͳ�ƣ�����10������ */
#define WPHY_MNTN_MAX_REGION_NUM                 ( 10 )

/*W Rx FAST CAL ������:SC/DC BLK/NBLK ���8����ÿ������2���������� */
#define WPHY_CAL_RX_FAST_CAL_MAX_VAILD_NUM       ( 64 )
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  3.1 ö�ٶ���,GPHYö�ٶ���
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 UPHY�ظ�CNFʱ,Я���Ĵ�����ö��
*****************************************************************************/
enum UPHY_TOOL_RTC_DEBUG_ENUM
{
    UPHY_MNTN_RTC_DEBUG_CLOSE                   = 0,
    UPHY_MNTN_RTC_DEBUG_OPEN                    = 1,

    UPHY_MNTN_RTC_DEBUG_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_RTC_DEBUG_ENUM_UINT16;



/*****************************************************************************
 UPHY<-->TOOLԭ���б�
*****************************************************************************/
enum UPHY_TOOL_MNTN_MSG_ID_ENUM
{
    ID_TOOL_UPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice  TOOL_UPHY_REQ_STRU */

    ID_TOOL_UPHY_QUERY_SHARE_ADDR_REQ           = 0xFE01,                       /* _H2ASN_MsgChoice  UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU */
    ID_UPHY_TOOL_QUERY_SHARE_ADDR_IND           = 0xFE02,                       /* _H2ASN_MsgChoice  UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU */

    ID_TOOL_UPHY_SDT_LINK_STATUS_REQ            = 0xFE03,                       /* _H2ASN_MsgChoice  UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU */
    ID_UPHY_TOOL_SDT_LINK_STATUS_CNF            = 0xFE04,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_ERROR_REPORT_REQ               = 0xFE05,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_REQ_STRU */
    ID_UPHY_TOOL_ERROR_REPORT_CNF               = 0xFE06,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_WPHY_BLER_RPT_REQ              = 0xFE07,
    ID_TOOL_UPHY_WPHY_INTRA_MSG_RPT_CTRL_REQ    = 0xFE08,
    ID_TOOL_UPHY_GPHY_INTRA_MSG_RPT_CTRL_REQ    = 0xFE09,


    ID_TOOL_UPHY_WPHY_INTER_GREG_REPORT_REQ     = 0xFE0A,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF     = 0xFE0B,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND     = 0xFE0C,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU */
    ID_TOOL_UPHY_WPHY_INTER_GREG_STOP_REQ       = 0xFE0D,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_STOP_CNF       = 0xFE0E,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_GPHY_INTER_WREG_REPORT_REQ     = 0xFE0F,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF     = 0xFE10,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND     = 0xFE11,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND_STRU */
    ID_TOOL_UPHY_GPHY_INTER_WREG_STOP_REQ       = 0xFE12,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_STOP_CNF       = 0xFE13,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_UPHY_TOOL_DRX_LATE_INFO_IND              = 0xFE14,                       /* _H2ASN_MsgChoice  UPHY_TOOL_DRX_LATE_INFO_IND_STRU */
    ID_UPHY_TOOL_KEY_INFORMATION_REPORT         = 0xFE15,                       /* _H2ASN_MsgChoice  UPHY_COM_KEY_INFORMATION_STRU */

    ID_UPHY_TOOL_UPHY_INIT_REPORT_IND           = 0xFE18,                       /* _H2ASN_MsgChoice  ** */

    ID_RCM_TOOL_MNTN_MSG_SCHDL_MAIN_INFO        = 0xFE19,                       /* _H2ASN_MsgChoice  RCM_SCHDL_MAIN_PARA_STRU */
    ID_RCM_TOOL_MNTN_MSG_MSGLIST_INFO           = 0xFE1A,                       /* _H2ASN_MsgChoice  RCM_PHY_MSG_LIST_STRU */
    ID_RCM_TOOL_MNTN_MSG_CHAINLIST_INFO         = 0xFE1B,                       /* _H2ASN_MsgChoice  RCM_TASK_NODE_STRU */

    /* diag �Ĵ����ṹ���ü���Ϣ�ϱ� */
    ID_TOOL_COM_DIAG_PHY_SAMPLE_CFG_REQ         = 0xFE1C,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_SAMPLE_CFG_STRU */
    ID_TOOL_COM_DIAG_PHY_SAMPLE_IND             = 0xFE1D,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_SAMPLE_REG_IND_STRU */
    ID_TOOL_COM_DIAG_SAMPLE_REG_IND             = 0xFE1E,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_REG_IND_STRU */

    ID_TOOL_UPHY_SOCP_VOTE_WAKE_CNF             = 0xFE20,                       /* _H2ASN_MsgChoice  UPHY_DRV_SOCP_VOTE_WAKE_CNF_STRU */

    ID_UPHY_TOOL_INFO_REPORT_IND                = 0xFEF7,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */
    ID_UPHY_TOOL_WARNING_REPORT_IND             = 0xFEF8,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */
    ID_UPHY_TOOL_ERROR_REPORT_IND               = 0xFEF9,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */

    ID_UPHY_TOOL_TAS_STATUS_REPORT_REQ          = 0xFEFA,                       /* _H2ASN_MsgChoice  UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU */
    ID_UPHY_TOOL_TAS_STATUS_REPORT_CNF          = 0xFEFB,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */
    ID_UPHY_TOOL_AGENTC_ESTIMATE_STATE_IND      = 0xFEFC,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU */
    ID_UPHY_TOOL_AGENTC_COMPARE_STATE_IND       = 0xFEFD,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_COMPARE_IND_STRU */
    ID_UPHY_TOOL_AGENTC_PROTECT_STATE_IND       = 0xFEFE,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_PROTECT_IND_STRU */
    ID_UPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 UPHY�ظ�CNFʱ,Я���Ĵ�����ö��
*****************************************************************************/
enum UPHY_TOOL_MNTN_RSLT_ENUM
{
    UPHY_MNTN_RSLT_SUCC                         = 0,
    UPHY_MNTN_RSLT_FAIL                         = 1,

    UPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_RSLT_ENUM_UINT16;



/*****************************************************************************
 ö����    : UPHY_TOOL_MNTN_RPT_LEVEL_ENUM
 Э����  :
 ö��˵��  : UPHY�����ϱ�����
*****************************************************************************/
enum UPHY_TOOL_MNTN_RPT_LEVEL_ENUM
{
    UPHY_MNTN_RPT_LEVEL_INFO                    = 1,
    UPHY_MNTN_RPT_LEVEL_WARNING                 = 2,
    UPHY_MNTN_RPT_LEVEL_ERROR                   = 3,

    UPHY_MNTN_RPT_LEVEL_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16;





/*****************************************************************************
 GPHY<-->TOOLԭ���б�
*****************************************************************************/
enum GPHY_TOOL_MNTN_MSG_ID_ENUM
{
    /* �·�REQ��Ϣ��Ϊ��VOS��Ϣ���ϱ���IND��CNF��Ϣ����VOS��Ϣͷ��Ӧ��REQ�������������ָʾΪ��ASN���ɷ��� */
    ID_TOOL_GPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice  TOOL_GPHY_REQ_STRU */

    ID_TOOL_GPHY_BLER_REPORT_REQ                = 0xE001,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLER_REPORT_REQ_STRU */
    ID_GPHY_TOOL_BLER_REPORT_CNF                = 0xE010,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_BLER_REPORT_IND                = 0xE011,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLER_REPORT_IND_STRU */

    ID_TOOL_GPHY_SNR_REPORT_REQ                 = 0xE002,                       /* _H2ASN_MsgChoice  GPHY_TOOL_SNR_REPORT_REQ_STRU */
    ID_GPHY_TOOL_SNR_REPORT_CNF                 = 0xE020,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_SNR_REPORT_IND                 = 0xE021,                       /* _H2ASN_MsgChoice  GPHY_TOOL_SNR_REPORT_IND_STRU */

    ID_TOOL_GPHY_AFC_REPORT_REQ                 = 0xE003,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AFC_REPORT_REQ_STRU */
    ID_GPHY_TOOL_AFC_REPORT_CNF                 = 0xE030,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_AFC_REPORT_IND                 = 0xE031,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AFC_REPORT_IND_STRU */

    ID_TOOL_GPHY_POWER_CTRL_REPORT_REQ          = 0xE004,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU */
    ID_GPHY_TOOL_POWER_CTRL_REPORT_CNF          = 0xE040,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_POWER_CTRL_REPORT_IND          = 0xE041,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_REPORT_IND_STRU */

    /* TAS״̬�ϱ�����*/
    ID_GPHY_TOOL_REQUEST_TAS_STATUS_IND         = 0xE043,                       /* _H2ASN_MsgChoice GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU*/

    ID_TOOL_GPHY_POWER_CTRL_SET_REQ             = 0xE005,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_SET_REQ_STRU */
    ID_GPHY_TOOL_POWER_CTRL_SET_CNF             = 0xE050,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_GPHY_TOOL_CHANNEL_QUALITY_IND            = 0xE080,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CHANNEL_QUALITY_IND_STRU */

    ID_TOOL_GPHY_FUNC_BIT_CONTROL_REQ           = 0xE00A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU */
    ID_GPHY_TOOL_FUNC_BIT_CONTROL_CNF           = 0xE0A0,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_PARA_CONTROL_REQ               = 0xE00B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PARA_CONTROL_REQ_STRU */
    ID_GPHY_TOOL_PARA_CONTROL_CNF               = 0xE0B0,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_RF_FRONT_STATIC_REQ            = 0xE052,                       /* _H2ASN_MsgChoice  GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU */
    ID_GPHY_TOOL_RF_FRONT_STATIC_IND            = 0xE053,                       /* _H2ASN_MsgChoice  GPHY_TOOL_RF_FRONT_STATIC_IND_STRU */

    ID_TOOL_GPHY_INTRA_MSG_RPT_CTRL_REQ         = 0xE054,                       /* _H2ASN_MsgChoice  GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU */
    ID_GPHY_TOOL_INTRA_MSG_RPT_CTRL_CNF         = 0xE055,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_AMR_REPORT_REQ                 = 0xE057,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_REPORT_REQ_STRU */
    ID_GPHY_TOOL_AMR_REPORT_CNF                 = 0xE058,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_AMR_REPORT_IND                 = 0xE059,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_REPORT_IND_STRU */

    ID_TOOL_GPHY_BLK_REPORT_LIST_REQ            = 0xE05A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU */
    ID_GPHY_TOOL_BLK_REPORT_LIST_CNF            = 0xE05B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_BLK_REPORT_LIST_IND            = 0xE05C,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLK_REPORT_LIST_IND_STRU */

    ID_GPHY_TOOL_GTC_TASK_INFO_IND              = 0xE061,                       /* _H2ASN_MsgChoice GPHY_GTC_CONTEXT_STRU */
    ID_GPHY_TOOL_RCV_SINGAL_INFO_IND            = 0xE062,                       /* _H2ASN_MsgChoice GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU */
    ID_GPHY_TOOL_CS_UL_INFO_IND                 = 0xE064,                       /* _H2ASN_MsgChoice GSM_CHN_UL_INFO_RPT_STRU */
    ID_GPHY_TOOL_CS_DL_INFO_IND                 = 0xE065,                       /* _H2ASN_MsgChoice COM_CS_DECODE_CTRL_INFO_STRU */

    ID_UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND        = 0xE066,                       /* _H2ASN_MsgChoice UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND_STRU */

    ID_GPHY_TOOL_RF_RESOURCE_ERR_IND            = 0xE067,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_RF_DSDS_WAKE_REPORT            = 0xE068,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_RF_DSDS_SLEEP_REPORT           = 0xE069,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_GRA_TASK_INFO_IND              = 0xE06A,                       /* _H2ASN_MsgChoice */

    /* GmeasW GBGW�ֹ���Ϣ�ϱ� */
    ID_GPHY_TOOL_GMEASW_SCHEDULE_INT7_IND       = 0xE06B,                       /* _H2ASN_MsgChoice GPHY_GMEASW_SCHEDULE_INFO_STRU */
    ID_GPHY_TOOL_GBGW_SCHEDULE_INT7_IND         = 0xE06C,                       /* _H2ASN_MsgChoice GPHY_BGW_SCHEDULE_INFO_STRU */

    ID_GPHY_TOOL_MASTER_WAKE_INFO_IND           = 0xE06D,                       /* _H2ASN_MsgChoice  UPHY_GDRX_MASTER_MNTN_STRU */
    ID_GPHY_TOOL_SLAVE_WAKE_INFO_IND            = 0xE06E,                       /* _H2ASN_MsgChoice  UPHY_GDRX_SLAVE_MNTN_STRU */
    ID_GPHY_TOOL_DCOFFSET_UPDATE_IND            = 0xE06F,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DC_OFFSET_REPORT_STRU */

    /* G��ģ������Ϣ��ӡ */
    ID_GPHY_TOOL_SLAVE_MEAS_INFO_IND            = 0xE073,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU *//* �ϱ�G��ģ������Ϣ */

    ID_GPHY_TOOL_DCH_OCCASION_USE_RPT_IND       = 0xE074,
    ID_GPHY_TOOL_NCELL_BSIC_SEARCH_STATE_IND    = 0xE075,
    ID_GPHY_TOOL_NCELL_BSIC_VERIFY_STATE_IND    = 0xE076,
    ID_GPHY_TOOL_NCELL_INTERRAT_RANK_IND        = 0xE077,
    ID_GPHY_TOOL_NCELL_PREDICT_TASK_IND         = 0xE078,
    ID_GPHY_TOOL_CHN_DUMMY_PCH_RPT_IND          = 0xE079,

    ID_GPHY_TOOL_REPORT_INFO_IND                = 0xE0F7,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */
    ID_GPHY_TOOL_REPORT_WARNING_IND             = 0xE0F8,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */
    ID_GPHY_TOOL_REPORT_ERROR_IND               = 0xE0F9,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */

    ID_TOOL_GPHY_BBP_RTC_REQ                    = 0xE0FA,                       /* _H2ASN_MsgChoice GPHY_TOOL_BBP_RTC_REQ_STRU  */
    ID_GPHY_TOOL_BBP_RTC_CNF                    = 0xE0FB,                       /* _H2ASN_MsgChoice GPHY_TOOL_COMMON_CNF_STRU  */

    /* DSP-PROBE */
    ID_TOOL_GPHY_GSM_CELL_SNR_REQ               = 0xE600,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GSM_CELL_SNR_REQ_STRU *//* ���������������ϱ�����С����6ǿ����������ȣ�����ֵ */
    ID_GPHY_TOOL_GSM_CELL_SNR_CNF               = 0xE601,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_GSM_CELL_SNR_IND               = 0xE602,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GSM_CELL_SNR_IND_STRU *//* �ϱ�����С����6ǿ����������ȣ�����ֵ */

    ID_TOOL_GPHY_BA_LIST_MEAS_REQ               = 0xE603,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BA_LIST_MEAS_REQ_STRU *//* ���������������ϱ���������32���������ź�ǿ�ȣ�bsicֵ */
    ID_GPHY_TOOL_BA_LIST_MEAS_CNF               = 0xE604,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_BA_LIST_MEAS_IND               = 0xE605,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BA_LIST_MEAS_IND_STRU *//* �ϱ���������32���������ź�ǿ�ȣ�bsicֵ */

    ID_TOOL_GPHY_AMR_SETTING_REQ                = 0xE606,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_SETTING_REQ_STRU *//* ���������������ϱ�AMR������Ϣ */
    ID_GPHY_TOOL_AMR_SETTING_CNF                = 0xE607,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_AMR_SETTING_IND                = 0xE608,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_SETTING_IND_STRU *//* �ϱ�AMR������Ϣ */

    ID_TOOL_GPHY_AMR_CODEC_USAGE_REQ            = 0XE609,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU *//* ���������������ϱ������ÿ���������ʵ�ʹ���� */
    ID_GPHY_TOOL_AMR_CODEC_USAGE_CNF            = 0XE60A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_AMR_CODEC_USAGE_IND            = 0XE60B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU *//* �ϱ������ÿ���������ʵ�ʹ������ */

    ID_TOOL_GPHY_AMR_CODEC_STAT_REQ             = 0xE60C,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU *//* ������������������������ʵ�ʹ���� */
    ID_GPHY_TOOL_AMR_CODEC_STAT_CNF             = 0xE60D,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_AMR_CODEC_STAT_IND             = 0xE60E,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_STAT_IND_STRU *//* �ϱ������������ʵ�ʹ���� */

    ID_TOOL_GPHY_CS_PS_TX_INFO_REQ              = 0xE60F,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_TX_INFO_REQ_STRU *//* ���������������ϱ�CS��������Ϣ */
    ID_GPHY_TOOL_CS_PS_TX_INFO_CNF              = 0xE610,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_CS_PS_TX_INFO_IND              = 0xE611,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_TX_INFO_IND_STRU *//* �ϱ�CS��������Ϣ */

    ID_TOOL_GPHY_CS_FER_REQ                     = 0xE612,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_FER_REQ_STRU *//* �����������ϱ�CS���FER */
    ID_GPHY_TOOL_CS_FER_CNF                     = 0xE613,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_CS_FER_IND                     = 0xE614,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_FER_IND_STRU *//* �ϱ�CS���FER */

    ID_TOOL_GPHY_GET_CURRENT_DSC_REQ            = 0xE615,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GET_CURRENT_DSC_REQ_STRU *//* �����������ϱ�DSC����ֵ */
    ID_GPHY_TOOL_GET_CURRENT_DSC_CNF            = 0xE616,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* �ظ�ȷ����Ϣ */
    ID_GPHY_TOOL_GET_CURRENT_DSC_IND            = 0xE617,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GET_CURRENT_DSC_IND_STRU *//* �ϱ�DSC����ֵ */

    ID_GPHY_TOOL_MASTER_WAKE_LTE_IND            = 0xE620,
    ID_GPHY_TOOL_MASTER_START_LTE_MEAS_IND      = 0xE621,
    ID_GPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND     = 0xE622,
    ID_GPHY_TOOL_MASTER_STOP_LTE_MEAS_IND       = 0xE623,
    ID_GPHY_TOOL_SET_LTE_MEAS_FLAG_IND          = 0xE624,
    ID_GPHY_TOOL_CLEAR_LTE_MEAS_FLAG_IND        = 0xE625,

    ID_GPHY_TOOL_MASTER_WAKE_TDS_IND            = 0xE630,
    ID_GPHY_TOOL_MASTER_START_TDS_MEAS_IND      = 0xE631,
    ID_GPHY_TOOL_MASTER_REPORT_TDS_MEAS_IND     = 0xE632,
    ID_GPHY_TOOL_MASTER_STOP_TDS_MEAS_IND       = 0xE633,
    ID_GPHY_TOOL_SET_TDS_MEAS_FLAG_IND          = 0xE634,
    ID_GPHY_TOOL_CLEAR_TDS_MEAS_FLAG_IND        = 0xE635,

    /* ˫�����о������Ϣ�ϱ� */
    ID_GPHY_TOOL_DUAL_ANT_ESTIMATE_IND          = 0xE640,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU *//* �ϱ����������������׶��о���Ϣ */
    ID_GPHY_TOOL_DUAL_ANT_COMPARE_IND           = 0xE641,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU *//* �ϱ��������������ȽϽ׶��о���Ϣ */
    ID_GPHY_TOOL_DUAL_ANT_DELAY_IND             = 0xE642,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU *//* �ϱ������л�������Ϣ */

    ID_GPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 GPHY�ظ�CNFʱ,Я���Ĵ�����ö��
*****************************************************************************/
enum GPHY_TOOL_MNTN_RSLT_ENUM
{
    GPHY_MNTN_RSLT_SUCC                         = 0,
    GPHY_MNTN_RSLT_FAIL                         = 1,

    GPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_MNTN_RSLT_ENUM_UINT16;



/*****************************************************************************
 TOOL�·��������ƣ���Ҫ�ǹ��ʿ��ƺ�BEP����
*****************************************************************************/
enum GPHY_TOOL_PARA_CTRL_ENUM
{
    GPHY_TOOL_PARA_PWC_CTRL                     = 0x01,                         /* �·����ƹ��ʲ��� */
    GPHY_TOOL_PARA_BEP_CTRL                     = 0x02,                         /* �·�����BEP���� */

    GPHY_TOOL_PARA_CTRL_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_PARA_CTRL_ENUM_UINT16;



/*****************************************************************************
 ö����    : GPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16
 Э����  :
 ö��˵��  : GPHY�����ϱ�����
*****************************************************************************/
enum GPHY_TOOL_ERROR_RPT_LEVEL_ENUM
{
    GPHY_TOOL_ERROR_LEVEL_INFO                  = 1,
    GPHY_TOOL_ERROR_LEVEL_WARNING               = 2,
    GPHY_TOOL_ERROR_LEVEL_ERROR                 = 3,

    GPHY_TOOL_ERROR_LEVEL_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_ERROR_RPT_LEVEL_ENUM_UINT16;






/*****************************************************************************
 GPHYģ�鶨��
*****************************************************************************/

enum GPHY_TOOL_MODULE_ENUM
{
    GPHY_MODULE_DRV                             = 0x5501,                       /* DRIVERģ������� */
    GPHY_MODULE_MEA                             = 0x5502,                       /* ����ģ������� */
    GPHY_MODULE_NCE_TSK                         = 0x5503,                       /* ��������ģ������� */
    GPHY_MODULE_NCE_RES                         = 0x5504,                       /* ������ѡģ������� */
    GPHY_MODULE_CHN_CCH                         = 0x5505,                       /* �����ŵ�ģ������� */
    GPHY_MODULE_CHN_CSDCH                       = 0x5506,                       /* CSר���ŵ�ģ������� */
    GPHY_MODULE_CHN_PSDCH                       = 0x5507,                       /* PSר���ŵ�ģ������� */
    GPHY_MODULE_CHN_AMRDTX                      = 0x5508,                       /* �ŵ�AMRDTXģ������� */
    GPHY_MODULE_COM                             = 0x5509,                       /* ����ģ������� */
    GPHY_MODULE_COM_MAIL                        = 0x550A,                       /* ��������ģ������� */
    GPHY_MODULE_COM_TOA                         = 0x550B,                       /* ����TOAģ������� */
    GPHY_MODULE_DRX                             = 0x550C,                       /* DRXģ������� */
    GPHY_MODULE_OM                              = 0x550D,                       /* OMģ������� */
    GPHY_MODULE_WMEAS                           = 0x550E,                       /* WMEASģ������� */
    GPHY_MODULE_CAL                             = 0x550F,                       /* CALģ������� */
    GPHY_MODULE_LMEAS                           = 0x5510,                       /* LTE����ģ������� */
    GPHY_MODULE_PD_INTERFACE                    = 0x5511,                       /* �µ粿�ִ���ӿں���ģ�� */
    GPHY_MODULE_TMEAS                           = 0x5512,                       /* TD����ģ������� */
    GPHY_MODULE_BUTT

};
typedef VOS_UINT16 GPHY_TOOL_MODULE_ENUM_UINT16;


/*****************************************************************************
  3.2 ö�ٶ���,WPHYö�ٶ���
*****************************************************************************/


/*****************************************************************************
 WPHY<-->TOOLԭ���б�
*****************************************************************************/

enum WPHY_TOOL_MNTN_MSG_ID_ENUM
{
    /* �·�REQ��Ϣ��Ϊ��VOS��Ϣ���ϱ���IND��CNF��Ϣ����VOS��Ϣͷ��Ӧ��REQ�������������ָʾΪ��ASN���ɷ��� */
    ID_TOOL_WPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice TOOL_WPHY_REQ_STRU */

    /* ����ģʽ��ʵʱ�޸�PA�����л��㲹��������ͻظ�ԭ�� */
    ID_TOOL_WPHY_RF_PA_GAIN_SWITCH_COMP_REQ     = 0xC801,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU */
    ID_WPHY_TOOL_RF_PA_GAIN_SWITCH_COMP_CNF     = 0xC802,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU */

    /* ����ģʽ��PDʹ�ܿ��� */
    ID_TOOL_WPHY_PD_ENABLE_REQ                  = 0xC803,                       /* _H2ASN_MsgChoice WPHY_TOOL_POW_DET_ENABLE_REQ_STRU */
    ID_WPHY_TOOL_PD_ENABLE_CNF                  = 0xC804,                       /* _H2ASN_MsgChoice WPHY_TOOL_POW_DET_ENABLE_CNF_STRU */

    /* ���С���ϱ�  */
    ID_TOOL_WPHY_ACT_CELL_REQ                   = 0xF001,                       /* _H2ASN_MsgChoice WPHY_TOOL_ACT_CELL_REQ_STRU */
    ID_WPHY_TOOL_ACT_CELL_CNF                   = 0xF002,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_ACT_CELL_IND                   = 0xF003,                       /* _H2ASN_MsgChoice WPHY_TOOL_ACT_CELL_INFO_IND_STRU */

    /* С�������б��ϱ� */
    ID_TOOL_WPHY_CELL_SEARCH_LIST_REQ           = 0xF004,                       /* _H2ASN_MsgChoice WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU  */
    ID_WPHY_TOOL_CELL_SEARCH_LIST_CNF           = 0xF005,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_CELL_SEARCH_LIST_IND           = 0xF006,                       /* _H2ASN_MsgChoice WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU */


    /* ���ؿ��ؿ��� */
    ID_TOOL_WPHY_PWR_SWITCH_CTRL_REQ            = 0xF00A,                       /* _H2ASN_MsgChoice WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU */
    ID_WPHY_TOOL_PWR_SWITCH_CTRL_CNF            = 0xF00B,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* ���ز������� */
    ID_TOOL_WPHY_PWR_PARA_SET_REQ               = 0xF010,                       /* _H2ASN_MsgChoice WPHY_TOOL_PWR_PARA_SET_REQ_STRU */
    ID_WPHY_TOOL_PWR_PARA_SET_CNF               = 0xF011,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */


    /* ������ϱ� */
    ID_TOOL_WPHY_BLER_REPORT_REQ                = 0xF020,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLER_REPORT_REQ_STRU */
    ID_WPHY_TOOL_BLER_REPORT_CNF                = 0xF021,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_BLER_REPORT_IND                = 0xF022,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLER_REPORT_IND_STRU */


    /* �¼��ϱ� */
    ID_TOOL_WPHY_EVENT_REPORT_REQ               = 0xF02A,                       /* _H2ASN_MsgChoice WPHY_TOOL_EVENT_REPORT_REQ_STRU */
    ID_WPHY_TOOL_EVENT_REPORT_CNF               = 0xF02B,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* �¼��ϱ�:ͬʧ���ϱ� */
    ID_WPHY_TOOL_SYNC_STATUS_IND                = 0xF02C,                       /* _H2ASN_MsgChoice WPHY_TOOL_SYNC_STATUS_IND_STRU */

    /* �¼��ϱ�:AFC״̬ */
    ID_WPHY_TOOL_VCTCXO_STATUS_IND              = 0xF02E,                       /* _H2ASN_MsgChoice WPHY_TOOL_AFC_STATUS_IND_STRU */

    /* �¼��ϱ�:�ж������쳣���� */
    ID_WPHY_TOOL_INTERRUPT_EXCEPTIION_IND       = 0xF030,                       /* _H2ASN_MsgChoice WPHY_TOOL_INTERRUPT_EXCEPTIION_IND_STRU */

    /* �¼��ϱ�:L1״̬�ϱ� */
    ID_WPHY_TOOL_WCDMA_L1_STATUS_IND            = 0xF031,                       /* _H2ASN_MsgChoice WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU */

    /* DRX���� */
    ID_TOOL_WPHY_DRX_SWITCH_REQ                 = 0xF032,                       /* _H2ASN_MsgChoice WPHY_TOOL_DRX_SWITCH_REQ_STRU */
    ID_WPHY_TOOL_DRX_SWITCH_CNF                 = 0xF033,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* �������� */
    ID_TOOL_WPHY_THRESHOLD_SET_REQ              = 0xF034,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_SET_REQ_STRU */
    ID_WPHY_TOOL_THRESHOLD_SET_CNF              = 0xF035,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* ���޲�ѯ */
    ID_TOOL_WPHY_THRESHOLD_QUERY_REQ            = 0xF036,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU */
    ID_WPHY_TOOL_THRESHOLD_QUERY_IND            = 0xF037,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_QUERY_IND_STRU */

    /* �����ϱ� */
    ID_TOOL_WPHY_ERROR_REPORT_REQ               = 0xF038,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_REQ_STRU */
    ID_WPHY_TOOL_ERROR_REPORT_CNF               = 0xF039,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_ERROR_REPORT_IND               = 0xF03A,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */
    ID_WPHY_TOOL_WARNING_REPORT_IND             = 0xF03B,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */
    ID_WPHY_TOOL_INFO_REPORT_IND                = 0xF03C,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */


    ID_TOOL_WPHY_RF_FRONT_END_PARA_REQ          = 0xF03D,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_END_PARA_CNF          = 0xF03E,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_RF_FRONT_END_PARA_IND          = 0xF03F,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU  */

    ID_WPHY_TOOL_PI_INT_RESULT_IND              = 0xF040,                       /* _H2ASN_MsgChoice WPHY_TOOL_PI_INT_RESULT_IND_STRU  */
    ID_WPHY_TOOL_AI_INT_RESULT_IND              = 0xF041,                       /* _H2ASN_MsgChoice WPHY_TOOL_AI_INT_RESULT_IND_STRU  */

    /* T313 ״̬�ϱ� */
    ID_WPHY_TOOL_T313_STATUS_IND                = 0xF042,                       /* _H2ASN_MsgChoice WPHY_TOOL_T313_STATUS_IND_STRU  */
    /* T312 ״̬�ϱ� */
    ID_WPHY_TOOL_T312_STATUS_IND                = 0xF043,                       /* _H2ASN_MsgChoice WPHY_TOOL_T312_STATUS_IND_STRU */

    /* PA״̬�ϱ� */
    ID_TOOL_WPHY_PA_STATUS_REPORT_REQ           = 0xF046,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_PA_STATUS_REPORT_CNF           = 0xF047,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_PA_STATUS_REPORT_IND           = 0xF048,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_STATUS_REPORT_IND_STRU */

    ID_TOOL_WPHY_INTRA_MSG_RPT_CTRL_REQ         = 0xF049,                       /* _H2ASN_MsgChoice WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU */
    ID_WPHY_TOOL_INTRA_MSG_RPT_CTRL_CNF         = 0xF04A,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* ǰ�˿�ά�ɲ� */
    ID_TOOL_WPHY_RF_FRONT_STATIC_REQUIRE_REQ    = 0xF070,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_STATIC_REQUIRE_IND    = 0xF071,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU  */

    ID_TOOL_WPHY_BBP_RTC_REQ                    = 0xF072,                       /* _H2ASN_MsgChoice WPHY_TOOL_BBP_RTC_REQ_STRU  */
    ID_WPHY_TOOL_BBP_RTC_CNF                    = 0xF073,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_TOOL_WPHY_RF_FRONT_DISPLAY_REQ           = 0xF075,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_DISPLAY_CNF           = 0xF077,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */


    ID_TOOL_WPHY_RAM_REPORT_REQ                 = 0xF078,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAM_REPORT_REQ_STRU  */
    ID_WPHY_TOOL_RAM_REPORT_CNF                 = 0xF079,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_RAM_REPORT_IND                 = 0xF07A,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAM_REPORT_IND_STRU  */

    ID_TOOL_WPHY_BLK_REPORT_LIST_REQ            = 0xF07B,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU  */
    ID_WPHY_TOOL_BLK_REPORT_LIST_CNF            = 0xF07C,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_BLK_REPORT_LIST_IND            = 0xF07D,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLK_REPORT_LIST_IND_STRU  */

    ID_TOOL_WPHY_RA_MNTN_CTRL_REQ               = 0xF07E,                       /* _H2ASN_MsgChoice WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU */
    ID_WPHY_TOOL_RA_MNTN_CTRL_CNF               = 0xF07F,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_TOOL_WPHY_ARM_0MS_MNTN_CTRL_REQ          = 0xF080,                       /* _H2ASN_MsgChoice WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU */
    ID_WPHY_TOOL_ARM_0MS_MNTN_CTRL_CNF          = 0xF081,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_WPHY_TOOL_SLAVE_CDRX_START_IND           = 0xF082,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_CDRX_START_IND_STRU  */
    ID_WPHY_TOOL_SLAVE_CDRX_STOP_IND            = 0xF083,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_CDRX_STOP_IND_STRU  */
    ID_WPHY_TOOL_SLAVE_W_FINISH_IND             = 0xF084,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_W_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_GRSSI_FINISH_IND         = 0xF085,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_GBSIC_FINISH_IND         = 0xF086,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND     = 0xF087,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU */
    ID_WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND      = 0xF088,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND_STRU */

    ID_WPHY_TOOL_MASTER_WAKE_LTE_IND            = 0xF090,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU */
    ID_WPHY_TOOL_MASTER_START_LTE_MEAS_IND      = 0xF091,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND     = 0xF092,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND       = 0xF093,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_SET_LTE_MEAS_FLAG_IND          = 0xF094,                       /* _H2ASN_MsgChoice WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU */
    ID_WPHY_TOOL_MASTER_RF_CONFIG_IND           = 0xF095,                       /* _H2ASN_MsgChoice WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU */
    ID_WPHY_TOOL_UPA_INFO_RPT_IND               = 0xF096,                       /* _H2ASN_MsgChoice WPHY_TOOL_UPA_RPT_INFO_STRU */

    ID_WPHY_TOOL_QPC_OPEN_UL_IND                = 0xF0A0,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_OPEN_UL_IND_STRU */
    ID_WPHY_TOOL_QPC_CLOSE_UL_IND               = 0xF0A1,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_CLOSE_UL_IND_STRU */
    ID_WPHY_TOOL_QPC_RRC_STATE_IND              = 0xF0A2,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_RRC_STATE_IND_STRU */
    ID_WPHY_TOOL_QPC_RB_TYPE_IND                = 0xF0A3,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_RB_TYPE_IND_STRU */


    ID_WPHY_TOOL_TAS_ESTIMATE_STATE_IND         = 0xF0B0,                       /* _H2ASN_MsgChoice WPHY_TOOL_TAS_ESTIMATE_STATE_IND_STRU */
    ID_WPHY_TOOL_TAS_COMPARE_STATE_IND          = 0xF0B1,                       /* _H2ASN_MsgChoice WPHY_TOOL_TAS_COMPARE_STATE_IND_STRU */
    ID_WPHY_TOOL_TAS_PROTECT_STATE_IND          = 0xF0B2,                       /* _H2ASN_MsgChoice WPHY_TOOL_TAS_PROTECT_STATE_IND_STRU */

    ID_WPHY_TOOL_IDLE_MNTN_RPT_IND              = 0xF0B3,                       /* _H2ASN_MsgChoice WPHY_TOOL_IDLE_MNTN_RPT_STRU */
    ID_WPHY_TOOL_FACH_MNTN_RPT_IND              = 0xF0B4,                       /* _H2ASN_MsgChoice WPHY_TOOL_FACH_MNTN_RPT_STRU */
    ID_WPHY_TOOL_DCH_MNTN_RPT_IND               = 0xF0B5,                       /* _H2ASN_MsgChoice WPHY_TOOL_DCH_MNTN_RPT_STRU */

    ID_WPHY_TOOL_TAS_STATUS_STATE_REPORT_IND    = 0xF0B6,                       /* _H2ASN_MsgChoice WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU */

    ID_WPHY_TOOL_PCCPCH_SCHEDULE_IND            = 0xF0B7,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU */
    ID_WPHY_TOOL_BCCH_QUEUE_IND                 = 0xF0B8,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU */
    ID_WPHY_TOOL_ADEMOD_QUEUE_IND               = 0xF0B9,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU */
    ID_WPHY_TOOL_CPC_MNTN_RPT_IND               = 0xF0BA,                       /* _H2ASN_MsgChoice WPHY_TOOL_CPC_MNTN_RPT_STRU */

    ID_WPHY_TOOL_IC_CELL_LIST_RPT_REQ           = 0xF0BB,                       /* _H2ASN_MsgChoice WPHY_TOOL_IC_CELL_REPORT_REQ_STRU */
    ID_WPHY_TOOL_IC_CELL_LIST_RPT_CNF           = 0xF0BC,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_IC_CELL_LIST_RPT_IND           = 0xF0BD,                       /* _H2ASN_MsgChoice WPHY_TOOL_IC_CELL_REPORT_IND_STRU */

    ID_WPHY_TOOL_RTT_STATUS_RPT_REQ             = 0xF0BE,                       /* _H2ASN_MsgChoice WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_RTT_STATUS_RPT_CNF             = 0xF0BF,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_RTT_STATUS_RPT_IND             = 0xF0C0,                       /* _H2ASN_MsgChoice WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU */

    ID_WPHY_TOOL_DPA_INFO_RPT_REQ               = 0xF0C1,                       /* _H2ASN_MsgChoice WPHY_TOOL_DPA_INFO_REQ_STRU */
    ID_WPHY_TOOL_DPA_INFO_RPT_CNF               = 0xF0C2,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_DPA_INFO_RPT_IND               = 0xF0C3,                       /* _H2ASN_MsgChoice WPHY_TOOL_DPA_INFO_IND_STRU */

    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_REQ       = 0xF0C4,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_CNF       = 0xF0C5,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_IND       = 0xF0C6,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU */

    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_REQ       = 0xF0C7,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_CNF       = 0xF0C8,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_IND       = 0xF0C9,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU */
    ID_WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_IND       = 0xF0CA,                       /* _H2ASN_MsgChoice WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU */
    ID_WPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ֻظ���Ϣ�Ľ��ֵ:�ɹ�����ʧ�ܵ�
*****************************************************************************/
enum WPHY_TOOL_MNTN_RSLT_ENUM
{
    WPHY_MNTN_RSLT_SUCC                         = 0,                            /* �ɹ� */
    WPHY_MNTN_RSLT_FAIL                         = 1,                            /* ʧ�� */
    WPHY_MNTN_RSLT_PERIOD_NOT_SUPPORT           = 2,                            /* �������ڲ�֧�� */
    WPHY_MNTN_RSLT_PARA_INVALID                 = 3,                            /* ���ò�����Ч */
    WPHY_MNTN_RSLT_PARA_TYPE_OVERFLOW           = 4,                            /* ���ò������Ͳ���ȷ */

    WPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RSLT_ENUM_UINT16;





/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ֲ��������ϱ�����
*****************************************************************************/
enum WPHY_TOOL_MNTN_REPORT_TYPE_ENUM
{
    WPHY_MNTN_REPORT_TYPE_NO_RPT                = 0,                            /* ���ϱ�: */
    WPHY_MNTN_REPORT_TYPE_ONE_TIME              = 1,                            /* �ϱ�1��: */
    WPHY_MNTN_REPORT_TYPE_PER_FRAME             = 2,                            /* ÿ֡�ϱ�: */
    WPHY_MNTN_REPORT_TYPE_ASSIGNED_PERIOD       = 3,                            /* ָ������:��֡Ϊ��λ�����ѡ�����������д��һ��������ָ�����ڡ� */
    WPHY_MNTN_REPORT_TYPE_EVENT_TRIGER          = 4,                            /* �¼�����: */

    WPHY_MNTN_REPORT_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM
{
    WPHY_MNTN_PWR_SWITCH_TYPE_UL_PC             = 0,                            /* ���й��ʿ���:�̶����з��䶫�� */
    WPHY_MNTN_PWR_SWITCH_TYPE_OLPC              = 1,                            /* �⻷���� */
    WPHY_MNTN_PWR_SWITCH_TYPE_WINUP             = 2,                            /* winup���� */
    WPHY_MNTN_PWR_SWITCH_TYPE_WINDOWN           = 3,                            /* windown���� */
    WPHY_MNTN_PWR_SWITCH_TYPE_FIX_DL_PWR        = 4,                            /* �̶����з��书�� */

    WPHY_MNTN_PWR_SWITCH_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM
{
    WPHY_MNTN_SWITCH_CTRL_CLOSE                 = 0,                            /* �ر� */
    WPHY_MNTN_SWITCH_CTRL_OPEN                  = 1,                            /* �� */

    WPHY_MNTN_SWITCH_CTRL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_SYNC_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_SYNC_STATUS_ENUM
{
    WPHY_MNTN_SYNC_STATUS_FIX                   = 0,                            /* ���� */
    WPHY_MNTN_SYNC_STATUS_LOST                  = 1,                            /* ʧ�� */

    WPHY_MNTN_SYNC_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_SYNC_STATUS_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_TCXO_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_TCXO_STATUS_ENUM
{
    WPHY_MNTN_TCXO_STATUS_FREEZE                = 0,                            /* ���� */
    WPHY_MNTN_TCXO_STATUS_UNFREEZE              = 1,                            /* ʧ�� */

    WPHY_MNTN_TCXO_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_TCXO_STATUS_ENUM_UINT16;



/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32
 Э����  :
 ö��˵��  : ���ʲ������ͣ���ѯ�����ù���
*****************************************************************************/
enum WPHY_TOOL_MNTN_PWR_PARA_ENUM
{
    WPHY_MNTN_PWR_PARA_SIR_TARGET               = 0x00000001,                   /* SirTarget */
    WPHY_MNTN_PWR_PARA_CURR_TRCH_ID_SELECTED    = 0x00000002,                   /* ��ǰѡ���TrchId */
    WPHY_MNTN_PWR_PARA_DL_TPC                   = 0x00000004,                   /* DL TPC */
    WPHY_MNTN_PWR_PARA_CURR_SIR                 = 0x00000008,                   /* ��ǰ��SIR */
    WPHY_MNTN_PWR_PARA_CURR_BLER                = 0x00000010,                   /* ��ǰ��BLER */
    WPHY_MNTN_PWR_PARA_UL_TPC                   = 0x00000020,                   /* UL TPC */
    WPHY_MNTN_PWR_PARA_BD                       = 0x00000040,                   /* Bd */
    WPHY_MNTN_PWR_PARA_BEC                      = 0x00000080,                   /* Bec */
    WPHY_MNTN_PWR_PARA_BED                      = 0x00000100,                   /* Bed */
    WPHY_MNTN_PWR_PARA_BHS_NACK                 = 0x00000200,                   /* BhsNack */
    WPHY_MNTN_PWR_PARA_BHS_ACK                  = 0x00000400,                   /* BhsAck */
    WPHY_MNTN_PWR_PARA_BHS_CQI                  = 0x00000800,                   /* BhsCQI */
    WPHY_MNTN_PWR_PARA_BHS_TFCI                 = 0x00001000,                   /* TFCI */
    WPHY_MNTN_PWR_PARA_SLOT_FORMAT              = 0x00002000,                   /* SlotFormat */
    WPHY_MNTN_PWR_PARA_MAX_PWR                  = 0x00004000,                   /* ����书�� */
    WPHY_MNTN_PWR_PARA_MIN_PWR                  = 0x00008000,                   /* ��С���书�� */
    WPHY_MNTN_PWR_PARA_INIT_PWR                 = 0x00010000,                   /* lint !e575 ��ʼ���书�� */
    WPHY_MNTN_PWR_PARA_LIST_MODE_SET_PWR        = 0x00020000,                   /* lint !e575 LIST MODE�¹ر��ڻ�����ֱ�����õķ��书�� */
    WPHY_MNTN_PWR_PARA_LIST_MODE_OPEN_ILPC      = 0x00040000,                   /* lint !e575 LIST MODE�����´��ڻ����� */

    WPHY_MNTN_PWR_PARA_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32;



/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32
 Э����  :
 ö��˵��  : �ϱ��¼�����
*****************************************************************************/
enum WPHY_TOOL_MNTN_EVENT_TYPE_ENUM
{
    WPHY_MNTN_EVENT_TYPE_AFC_STATUS             = 0x00000001,                   /* 6ms ����ʱ */
    WPHY_MNTN_EVENT_TYPE_SYNC_STATUS            = 0x00000002,                   /* 9ms ����ʱ */
    WPHY_MNTN_EVENT_TYPE_L1_STATUS              = 0x00000004,                   /* L1״̬ */
    WPHY_MNTN_EVENT_TYPE_INT_EXCEPT             = 0x00000008,                   /* �ж��쳣 */

    WPHY_MNTN_EVENT_TYPE_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32;




/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16
 Э����  :
 ö��˵��  : �ж��쳣����
*****************************************************************************/
enum WPHY_TOOL_MNTN_INT_EXCEPT_ENUM
{
    WPHY_MNTN_INT_EXCEPT_TYPE_6MS_TASK_EXPIRED  = 0,                            /* 6ms ����ʱ */
    WPHY_MNTN_INT_EXCEPT_TYPE_9MS_TASK_EXPIRED  = 1,                            /* 9ms ����ʱ */

    WPHY_MNTN_INT_EXCEPT_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16;



/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ϵͳ״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_SYS_STATUS_ENUM
{
    WPHY_MNTN_SYS_STATUS_FREE                   = 0,
    WPHY_MNTN_SYS_STATUS_CPICH                  = 1,
    WPHY_MNTN_SYS_STATUS_FACH                   = 2,
    WPHY_MNTN_SYS_STATUS_DPCH                   = 3,

    WPHY_MNTN_SYS_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16;



/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32
 Э����  :
 ö��˵��  : ��������������
*****************************************************************************/
enum WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM
{
    /* С���������� */
    WPHY_MNTN_THRESHOLD_TYPE_STEP1_NOISE                    = 0,
    WPHY_MNTN_THRESHOLD_TYPE_STEP2_NOISE                       ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NOISE_AFC_UNLOCK            ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NOISE_AFC_LOCK              ,
    WPHY_MNTN_THRESHOLD_TYPE_STEPB_NOISE                       ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP1_FAIL_FOR_SPEC_FREQ          ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP1_FAIL_FOR_BAND               ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP1_CORRELEN_FOR_INIT_CS        ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP2_RSDEC_LEN                   ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_CORRELEN_AFC_UNLOCK         ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_CORRELEN_AFC_LOCK           ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NCORRELEN_AFC_UNLOCK        ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NCORRELEN_AFC_LOCK          ,

    WPHY_MNTN_THRESHOLD_TYPE_STEPB_CORRELEN                    ,

    /*  �ྶ�������� */
    WPHY_MNTN_THRESHOLD_TYPE_CORRE_LENTH_LOCK                  ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_LENTH_LOCK                ,
    WPHY_MNTN_THRESHOLD_TYPE_CORRE_LENTH_UNLOCK                ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_LENTH_UNLOCK              ,

    /* �������� */
    WPHY_MNTN_THRESHOLD_TYPE_MEAS_AVERAGE_NOISE                ,
    WPHY_MNTN_THRESHOLD_TYPE_MP_RELATIVE_FACTOR                ,

    WPHY_MNTN_THRESHOLD_TYPE_MEAS_TIMING_ECNO_THRESHOLD        ,
    WPHY_MNTN_THRESHOLD_TYPE_MEAS_TIMING_RSCP_THRESHOLD        ,

    WPHY_MNTN_THRESHOLD_TYPE_MAX_TIMING_MEAS_FRAME_NUMBER      ,

    /* �������� */
    WPHY_MNTN_THRESHOLD_TYPE_SIR_THRESHOLD_PILOT1              ,
    WPHY_MNTN_THRESHOLD_TYPE_SIR_THRESHOLD_PILOT2              ,

    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI1OR2             ,
    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI4                ,
    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI8                ,

    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_CPU_QIN                   ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_CPU_QOUT                  ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_SS_THRESHOLD              ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_MRC_THRESHOLD             ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_INT_THRESHOLD             ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_ML_THRESHOLD              ,

    /* DRX�������� */
    WPHY_MNTN_THRESHOLD_TYPE_32K_CLOCK_MSR_WAIT_SFN_NUM        ,
    WPHY_MNTN_THRESHOLD_TYPE_SLEEP_LENTH                       ,
    WPHY_MNTN_THRESHOLD_TYPE_TIME_ADJUST                       ,

    WPHY_MNTN_THRESHOLD_TYPE_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_PA_STATUS_ENUM
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_MNTN_PA_STATUS_ENUM
{
    WPHY_MNTN_PA_STATUS_CLOSE                       = 0,                        /* �ر� */
    WPHY_MNTN_PA_STATUS_OPEN                        = 1,                        /* �� */

    WPHY_MNTN_PA_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_PA_STATUS_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_RPT_ADDR_ENUM_UINT16
 Э����  :
 ö��˵��  : WPHY��ά�ɲ�̶�ץȡ�ļ�������ö��
*****************************************************************************/
enum WPHY_TOOL_MNTN_RAM_RPT_ENUM
{
    WPHY_MNTN_RPT_HSUPA_SHARE_CTRL                  = 0,                        /* UPA���� */
    WPHY_MNTN_RPT_DSP_MODE                          = 1,                        /* DSPģʽ */
    WPHY_MNTN_RPT_HSUPA_RPT                         = 2,
    WPHY_MNTN_RPT_HSUPA_TTI                         = 3,
    WPHY_MNTN_RPT_CPC_DRX_RPT                       = 4,
    WPHY_MNTN_RPT_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16
 Э����  :
 ö��˵��  : WPHY�����ϱ�����
*****************************************************************************/
enum WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM
{
    WPHY_MNTN_ERROR_LEVEL_INFO                      = 1,
    WPHY_MNTN_ERROR_LEVEL_WARNING                   = 2,
    WPHY_MNTN_ERROR_LEVEL_ERROR                     = 3,

    WPHY_MNTN_ERROR_LEVEL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16;




/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_PA_STATUS_ENUM
 Э����  :
 ö��˵��  : ���ؿ��Ƶ�ö��ֵ
*****************************************************************************/
enum WPHY_TOOL_MNTN_RPT_STATUS_ENUM
{
    WPHY_MNTN_RPT_STATUS_CLOSE                      = 0,                        /* �ر� */
    WPHY_MNTN_RPT_STATUS_OPEN                       = 1,                        /* �� */

    WPHY_MNTN_RPT_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 Э����  :
 ö��˵��  : T313 Status
ASN.1���� :
 ö��˵��  : T313��ʱ�� ״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_T313_STATUS_ENUM
{
    WPHY_MNTN_T313_START                        = 0,
    WPHY_MNTN_T313_STOP                         = 1,
    WPHY_MNTN_T313_TIMEOUT                      = 2,

    WPHY_MNTN_T313_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_T313_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 Э����  :
 ö��˵��  : T312 Status
ASN.1���� :
 ö��˵��  : T312��ʱ�� ״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_T312_STATUS_ENUM
{
    WPHY_MNTN_T312_START                        = 0,
    WPHY_MNTN_T312_STOP                         = 1,
    WPHY_MNTN_T312_TIMEOUT                      = 2,

    WPHY_MNTN_T312_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_T312_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM
 Э����  :
 ö��˵��  : ǿͣLTEԭ��
ASN.1���� :
 ö��˵��  : ǿͣLTEԭ��

*****************************************************************************/
enum WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM
{
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BG               = 0,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_MEAS_TIMEOUT     = 1,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BG_TIMEOUT       = 2,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_HIGH_TASK        = 3,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_INIT             = 4,

    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ��ģ״̬
ASN.1���� :
 ö��˵��  : ��ģ״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM
{
    WPHY_MNTN_SLAVE_PRE                         = 0,
    WPHY_MNTN_SLAVE_ENTERGAP                    = 1,
    WPHY_MNTN_SLAVE_EXITRGAP                    = 2,
    WPHY_MNTN_SLAVE_FREQCHANGE                  = 3,
    WPHY_MNTN_SLAVE_MEAS_FINISH                 = 4,
    WPHY_MNTN_SLAVE_CS_FINISH                   = 5,
    WPHY_MNTN_SLAVE_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ��ǰ���⹤��״̬
ASN.1���� :
 ö��˵��  : ��ģ״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM
{
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_ALWAYS_OPEN    = 0,                                /* ���ⳤ��״̬ */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_DRX_OPEN,                                          /* �����״̬ */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_DRX_CLOSE,                                         /* ����ر�״̬ */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_BOOL_ENUM_UINT16
 Э����  :
 ö��˵��  : �����ö������
*****************************************************************************/
enum WPHY_TOOL_MNTN_BOOL_ENUM
{
    WPHY_MNTN_BOOL_FALSE                        = 0,
    WPHY_MNTN_BOOL_TRUE                         = 1,
    WPHY_MNTN_BOOL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_BOOL_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_CPC_DRX_CQI_PRIORITY_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CQI ���ȼ����Ͷ���
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM
{
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_0            = 0,                                /* CQI���ȼ�Ϊ0 */
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_1               ,                                /* CQI���ȼ�Ϊ1 */
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ۺ������ز���״̬��ĳ���cycle״̬����󼯺�
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM
{
    WPHY_MNTN_CPC_ULDPCCH_CYCLE1                = 0,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE2,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE1AND2,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :CPC DRX
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM
{
    WPHY_MNTN_CPC_DRX_RF_STATUS_ALWAYS_OPEN    = 0,                                  /* RFһֱ�� */
    WPHY_MNTN_CPC_DRX_RF_STATUS_DRX_OPEN,                                            /* RF����DRX�Ĵ�״̬ */
    WPHY_MNTN_CPC_DRX_RF_STATUS_DRX_CLOSE,                                           /* RF����DRX�Ĺر�״̬ */
    WPHY_MNTN_CPC_DRX_RF_STATUS_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16;

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
  6.0 STRUCT����,WG��������
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_TYPE_HEADER_STRU
 ö��˵��  : ���߽����ṹͷ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFuncType;                     /* ��ά�ɲ���0x4,�ڲ���Ϣץȡ��0x */
    VOS_UINT16                                  usLength;                       /* ֮��ĳ���,��λΪbyte */
    VOS_UINT32                                  ulSn;
    VOS_UINT32                                  ulTimeSlice;
}UPHY_TOOL_TYPE_HEADER_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_OM_MSG_HEADER_STRU
 ö��˵��  : ��Ϣͷ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usMsgId;
    VOS_UINT16                                  usReserved;
    VOS_UINT16                                  ausData[4];
}UPHY_TOOL_OM_MSG_HEADER_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_TOOL_INTRA_MSG_HEADER_STRU
 ö��˵��  : ��Ϣͷ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                  usMsgId;
    VOS_UINT16                                  usReserved;
}UPHY_TOOL_INTRA_MSG_HEADER_STRU;



/*****************************************************************************
  6.1 STRUCT����,UPHY����
*****************************************************************************/



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_SDT_LINK_STATUS_REQ
 �ṹ˵��  : TOOL����GPHY,SDT����״̬
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_COMMON_CNF_STRU
 �ṹ˵��  : GPHY��ά�ɲ⹫���ظ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip *//* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* ����ԭ��Ĵ�����ID */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}UPHY_TOOL_COMMON_CNF_STRU;


/*****************************************************************************
 �ṹ��    : UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU
 �ṹ˵��  : �����ַ��ѯ����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulParaValue;                    /* �Ƿ���Ƹò��� */
}UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU
 �ṹ˵��  : UPHY�����ַ��ѯ����ظ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulShareAddr;                    /* �����׵�ַ */

}UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU;


/*****************************************************************************
 �ṹ��    : UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU
 �ṹ˵��  : TOOL����UPHY,SDT����״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSdtStatus;
    VOS_UINT16                                  usRsv;
}UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_ERROR_REPORT_REQ_STRU
 �ṹ˵��  : �����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16        enErrorRptLevel;                /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRsv;
}UPHY_TOOL_ERROR_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_ERROR_REPORT_IND_STRU
 �ṹ˵��  : �����ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usFileNo;                       /* �ļ������� */
    VOS_UINT16                                  usLineNo;                       /* ������к� */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY�����ͳһ���LOG ID */
    VOS_UINT16                                  usReserved;                     /* �����ֶ� */
    VOS_UINT16                                  usVarCnt;                       /* �ϱ��������� */
    VOS_UINT32                                  aulVarValue[UPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* �ϱ�����ֵ */

}UPHY_TOOL_ERROR_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU
 �ṹ˵��  : WPHY����ϵͳG�Ĵ����б��·�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRsv;                         /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU
 �ṹ˵��  : WPHY����ϵͳG�Ĵ����յ��ظ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* ����ԭ��Ĵ�����ID */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU
 �ṹ˵��  : WPHY����ϵͳG�Ĵ���ֵ�ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRsv;                         /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegData[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU
 �ṹ˵��  : ֹͣWPHY����ϵͳG�Ĵ����ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulRsv;                          /* �����ϱ����󼶱� */
}UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU
 �ṹ˵��  : GPHY����ϵͳW�Ĵ����б��·�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRsv;                         /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU
 �ṹ˵��  : GPHY����ϵͳW�Ĵ����յ��ظ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* ����ԭ��Ĵ�����ID */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU
 �ṹ˵��  : GPHY����ϵͳW�Ĵ���ֵ�ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRsv;                         /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRegNum;                       /* �����ϱ����󼶱� */
    VOS_UINT32                                  aulRegData[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU
 �ṹ˵��  : ֹͣGPHY����ϵͳW�Ĵ����ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulRsv;                          /* �����ϱ����󼶱� */
}UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʱ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfn;                                 /* ϵͳ��ʱSFNֵ */
    VOS_UINT16                          uhwCfn;                                 /* ϵͳ��ʱCFNֵ */
    VOS_UINT16                          uhwSlot;                                /* ϵͳ��ʱSLOTֵ */
    VOS_UINT16                          uhwChip;                                /* ϵͳ��ʱCHIPֵ */
} WPHY_TOOL_TIMING_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU
 �ṹ˵��  : WPHY DRX��ά�ɲ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwForbidSleepReason;        /* ��ֹ˯��ԭ�� */
    VOS_UINT32                                      uwSndSleepReqCnt;           /* WPHY ����˯����Ϣ���� */
    VOS_UINT32                                      uwSndSleepReqSlice;         /* WPHY ����˯����Ϣslice */
    VOS_UINT32                                      uwDrxRcvSleepSlice;         /* DRX  �յ�˯����Ϣslice */
    VOS_UINT32                                      uwDrxSendSleepSlice;        /* DRX  ����˯����Ϣslice */
    VOS_UINT32                                      uwDrxNeedWakeSlice;         /* DRX  Ԥ�ڻ���slice */
    VOS_UINT32                                      uwDrxRcvWakeSlice;          /* DRX  �յ�������Ϣslice */
    VOS_UINT32                                      uwDrxSendWakeSlice;         /* DRX  ���ͻ�����Ϣslice */
    VOS_UINT32                                      uwRcvWakeMsgCnt;            /* WPHY ���յ�������Ϣ���� */
    VOS_UINT32                                      uwRcvWakeMsgSlice;          /* WPHY ���յ�������Ϣslice*/
    VOS_UINT32                                      uwDcStartSlice;             /* WPHY ����DC�ȶ���ʱ��ʱ��slice */
    VOS_UINT32                                      uwDcEndSlice;               /* WPHY DC�ȶ���ʱ����ʱslice */
    VOS_UINT32                                      uwMpStartSlice;             /* WPHY ��һ�ζྶ��������slice */
    VOS_UINT32                                      uwRcvMpSrchIntCnt;          /* WPHY ���յ��ྶ�����жϼ��� */
    VOS_UINT32                                      uwRcvMpSrchIntSlice;        /* WPHY ���յ��ྶ����slice */
    VOS_UINT32                                      uwOpenSlotIntCnt;           /* WPHY ��ʱ϶�жϼ��� */
    VOS_UINT32                                      uwOpenSlotIntSlice;         /* WPHY ��ʱ϶�ж�slice */
    VOS_UINT32                                      uwPichSetupSlice;           /* WPHY PICH����slice */
    VOS_UINT32                                      uwPiIntSlice;               /* WPHY PI�ж�slice */
    WPHY_TOOL_TIMING_INFO_STRU                      stPiRealTime;               /* WPHY PIλ��ʱ�� */
    WPHY_TOOL_TIMING_INFO_STRU                      stPichSetupTime;            /* WPHY PICH����ʱ�� */
}UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UPHY_TOOL_DRX_LATE_INFO_IND_STRU
 �ṹ˵��  : ������ʱ�Ĵ����Ϣ
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usRsv;                                          /* �����ֶ� */
    VOS_UINT32                                  ulAwakeTime;                                    /* ��Ҫ���ѵ�ʱ�䣬W��ΪSFN��G��ΪSlice */
    VOS_UINT32                                  ulCurTime;                                      /* ʵ�ʻ��ѵ�ʱ�䣬W��ΪSFN��G��ΪSlice */
    VOS_UINT32                                  aulAwakeHWInfo[UPHY_TOOL_SLEEP_INFO_NUM];       /* OAM��ά�ɲ���Ϣ */
    UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU           stWphyDrxMntn;                                  /* WPHY��ά�ɲ���Ϣ */
}UPHY_TOOL_DRX_LATE_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU
 �ṹ˵��  : ����ģ��ä�л������׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_INT16                                   sRxAGCValue;                    /* ���ģ�ϱ��˲���Ľ��,��λΪ1dbm */
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊֱͨ��1Ϊ���� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_AGENTC_COMPARE_IND_STRU
 �ṹ˵��  : ����ģ��ä�л��ȽϽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_INT16                                   sDeltaRxAGCValue;               /* ���ģ�ϱ��˲����ƽ����ֵ���,��λΪ1dB */
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usPhase;                        /* �ȽϽ׶ε�ǰ�׶� */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊֱͨ��1Ϊ���� */
}UPHY_TOOL_AGENTC_COMPARE_IND_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_AGENTC_PROTECT_IND_STRU
 �ṹ˵��  : ����ģ��ä�л����ͽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usFrozenTime;                   /* ����ʱ�䳤�ȣ�1ms */
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊֱͨ��1Ϊ���� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}UPHY_TOOL_AGENTC_PROTECT_IND_STRU;

/*****************************************************************************
  6.2 STRUCT����,GPHY����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_COMMON_CNF_STRU
 �ṹ˵��  : GPHY��ά�ɲ⹫���ظ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip *//* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    GPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* ����ԭ��Ĵ�����ID */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_COMMON_CNF_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BLER_REPORT_REQ_STRU
 �ṹ˵��  : GPHY GPRS�ŵ����������ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usBlerFlag;                     /* �Ƿ��ϱ�BLER */
    VOS_UINT16                                  usRptPeriod;                    /* BLER�ϱ�������,��λ:���� */
}GPHY_TOOL_BLER_REPORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BLER_REPROT_IND_STRU
 �ṹ˵��  : GPHY�ϱ�BLER�Ľṹ���ӽṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT32                                  ulBlkCnt;
    VOS_UINT32                                  ulErrBlkCnt;
}GPHY_BLER_PARA_STRU;

typedef struct
{
    VOS_UINT32                                  ulRcvBlkCnt;
    VOS_UINT32                                  ulDummyCnt;
    GPHY_BLER_PARA_STRU                         stBlerPara[GPHY_PS_MAX_RX_TSN_NUM];
}GPHY_GPRS_BLER_RECORD_STRU;



typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_GPRS_BLER_RECORD_STRU                  stGprsBlerRecord;
}GPHY_TOOL_BLER_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_SNR_REPORT_REQ_STRU
 �ṹ˵��  : GPHY GPRS�ŵ���SNR�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSNRFlag;                      /* �Ƿ��ϱ�SNR */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_SNR_REPORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_SNR_REPROT_IND_STRU
 �ṹ˵��  : GPHY�ϱ�SNR�Ľṹ���ӽṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usRptValidNum;
    VOS_UINT16                                  usRsv;
    VOS_INT16                                   sSNR[GPHY_PS_MAX_RX_TSN_NUM];
    VOS_UINT16                                  usRsv2;
}GPHY_GPRS_SNR_RECORD_STRU;

/* ��ά�ɲ�:SNR�ϱ��ṹ */
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_GPRS_SNR_RECORD_STRU                   stGprsSNRRecord;
}GPHY_TOOL_SNR_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AFC_REPORT_REQ_STRU
 �ṹ˵��  : GPHY AFC����ֵ��Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usAFCFlag;                      /* �Ƿ��ϱ�AFCֵ */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_AFC_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AFC_REPROT_IND_STRU
 �ṹ˵��  : GPHY�ϱ�AFC�Ľṹ
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    VOS_INT16                                   sAFCOffset;
    VOS_UINT16                                  usRsv;
}GPHY_TOOL_AFC_REPORT_IND_STRU;




/*****************************************************************************
 �ṹ��    : GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU
 �ṹ˵��  : GPHY �����¹�����Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usPwrCtrlFlag;                  /* �Ƿ��ϱ����ʿ��� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_GPRS_POWER_CTRL_REPROT_IND_STRU
 �ṹ˵��  : GPHY�ϱ����ʿ��Ʋ����Ľṹ���ӽṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usTxChannel;
    VOS_UINT16                                  usTxTn;
    VOS_INT16                                   sTxPwr;
    VOS_UINT16                                  usGammaTn;
    VOS_UINT16                                  usGammaBand;
    VOS_UINT16                                  usAlpha;
    VOS_UINT16                                  usPMax;
    VOS_UINT16                                  usRsv;
}GPHY_PWR_CTRL_PARA_STRU;

typedef struct
{
    VOS_UINT16                                  usTxCnt;
    VOS_UINT16                                  usRsv;
    GPHY_PWR_CTRL_PARA_STRU                     stPwrCtrlPara[GPHY_PS_MAX_TX_TSN_NUM];
}GPHY_POWER_CONTROL_RECORD_STRU;


typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_POWER_CONTROL_RECORD_STRU              stPwrCtrlRecord;
}GPHY_TOOL_POWER_CTRL_REPORT_IND_STRU;




/*****************************************************************************
 �ṹ��    : GPHY_TOOL_POWER_CTRL_SET_REQ_STRU
 �ṹ˵��  : GPHY ������ָ�����ʷ�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usPwrCtrlFlag;                  /* �Ƿ���ָ�����ʷ��� */
    VOS_UINT16                                  usTxPwr;                        /* ָ������,��λ:0.1dB */
}GPHY_TOOL_POWER_CTRL_SET_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_GPRS_POWER_CTRL_REPROT_IND_STRU
 �ṹ˵��  : GPHY�ϱ�EGPRS�ŵ������ϱ��ṹ
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usGmskMeanBep;                  /* 0-31,0xffΪ��Чֵ */
    VOS_UINT16                                  us8PSKMeanBep;                  /* 0-31,0xffΪ��Чֵ */
    VOS_UINT16                                  usGmskCvBep;                    /* 0-7,0xffΪ��Чֵ */
    VOS_UINT16                                  us8PSKCvBep;                    /* 0-7,0xffΪ��Чֵ */
}GPHY_TOOL_CHANNEL_QUALITY_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU
 �ṹ˵��  : GPHY ��ά�ɲ⹦�ܿ����·��Ľṹԭ��:�������ƹ�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulFuncBitMask;                  /* ��ӦBitλ��λ,����Ƹù�����Ч */
}GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_PARA_CONTROL_REQ_STRU
 �ṹ˵��  : GPHY��ά�ɲ���������·��Ľṹԭ��:�������Ʋ�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    GPHY_TOOL_PARA_CTRL_ENUM_UINT16             enParaId;                       /* ������ID,���Ʋ������б� */
    VOS_UINT16                                  usParaCtrlFlg;                  /* �Ƿ���Ƹò��� */
    VOS_UINT32                                  ulParaValue1;                   /* ���Ʋ�����ֵ */
    VOS_UINT32                                  ulParaValue2;                   /* Ŀǰ����,������չ */
}GPHY_TOOL_PARA_CONTROL_REQ_STRU;




/*****************************************************************************
 �ṹ��    : GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU
 �ṹ˵��  : GPHY �ϱ�ǰ�˶�̬��Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usMsgRptFlag;                   /* ָʾ��Ϣ��ص��ϱ������Ƿ��б�� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BBP_RTC_REQ_STRU
 �ṹ˵��  : RTC���ܴ򿪺͹ر�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_RTC_DEBUG_ENUM_UINT16             enRtcCtrl;                      /* RTC�򿪻��߹ر� */
    VOS_UINT16                                  usRsv;

}GPHY_TOOL_BBP_RTC_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_RF_FRONT_STATIC_IND_STRU
 �ṹ˵��  : GPHY�ϱ�ǰ�˶�̬��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */

    VOS_UINT16                                  usRfTrcvOnState;                /* RF�ܿ��أ�1Ϊ�򿪣�0Ϊ�ر� */
    VOS_UINT16                                  usRfRxOnOrOff;                  /* 04h[1:0] = 3Ϊ�� */
    VOS_UINT16                                  usRxPathselect;                 /* 04h[4:3] = 3Ϊ���ּ�������2������ */
    VOS_UINT16                                  usAbbRxConfig;                  /* 7Ϊ���ּ�������3������ */

    VOS_UINT16                                  usRfTxOnOrOff;                  /* 02h[1:0] = 3Ϊ�� */
    VOS_UINT16                                  usRfTxSHDN;                     /* RF���д򿪿��ƣ�0��BBP���� */

    VOS_UINT16                                  usGpioFuncOn;                   /* Ӳ��֧��GPIO */
    VOS_UINT16                                  usGpioPaMode;                   /* GPIO PA mode */

    VOS_UINT16                                  usMipiFuncOn;                   /* Ӳ��֧��MIPI */
    VOS_UINT16                                  usMipiPaMode;                   /* MIPI PA mode */

    VOS_UINT16                                  usAptFuncOn;                    /* Ӳ��֧��APT */
    VOS_UINT16                                  usAptPaMode;                    /* APT��ѹmode */
}GPHY_TOOL_RF_FRONT_STATIC_IND_STRU;





/*****************************************************************************
 �ṹ��    : GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU
 �ṹ˵��  : PHY �ڲ���Ϣ�ϱ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usMsgRptFlag;                   /* ָʾ�ڲ���Ϣ�Ƿ��ϱ� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU;




/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_REPORT_REQ_STRU
 �ṹ˵��  : GPHY ������AMR�ŵ������������ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usAmrRptFlag;                   /* �Ƿ��ϱ�AMR��Ϣ */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}GPHY_TOOL_AMR_REPORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_REPORT_IND_STRU
 �ṹ˵��  : GPHY�ϱ�AMR��Ϣ����
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usCrcErrFlg;                    /* ������0-��ȷ;1-���� */
    VOS_UINT16                                  usDecodeMode;                   /* ���б��뷽ʽ */
    VOS_UINT16                                  usDecodeRate;                   /* ���б������� */
    VOS_UINT16                                  usEncodeMode;                   /* ���б��뷽ʽ */
    VOS_UINT16                                  usEncodeRate;                   /* ���б������� */
    VOS_UINT16                                  usRsv;
}GPHY_TOOL_AMR_REPORT_IND_STRU;




/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU
 �ṹ˵��  : GPHYץȡ�ǹ̶���ַ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulBlkAddr;                      /* ץȡ���ݿ���׵�ַ */
    VOS_UINT32                                  ulBlkLen;                       /* ץȡ���ݿ�ĳ���,��λ:32bit */
}GPHY_TOOL_BLK_REPORT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRptFlag;
    VOS_UINT16                                  usRsv;
    GPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[GPHY_TOOL_RPT_BLK_MAX_NUM];
}GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BLK_REPORT_LIST_IND_STRU
 �ṹ˵��  : GPHYץȡ�ǹ̶���ַ������
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    GPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[GPHY_TOOL_RPT_BLK_MAX_NUM];
    VOS_UINT32                                  aulData[2];
}GPHY_TOOL_BLK_REPORT_LIST_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_RCV_BURST_INFO_STRU
 �ṹ˵��  : ��ʱ϶������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMeaFn;                            /* �ϱ������ж�ʱ��֡�� */
    VOS_UINT16                              usMeaArfcn;                         /* �ϱ�������Ƶ�� */
    VOS_UINT16                              usTsMeasType;                       /* �������� */
    VOS_UINT16                              usNextAgcGain;                      /* AGC��λ */
    VOS_INT16                               sAgcRssi;                           /* ����ֵ:0.125dB */
    VOS_UINT32                              ulDrssi;                            /* DRSSI���������ǰ��ֵ�ϱ� */
    VOS_UINT32                              ulFastDrssi;                        /* ���ٲ�����һ���Լ��ڶ���RSSI�ϱ� */
    VOS_UINT32                              ulLsDcValue;
    /*VOS_UINT32                            ulDemoduFn;*/                       /* �ϱ������ж�ʱ��֡�� */
    VOS_UINT16                              usReserve;                          /* ����λ */
    VOS_UINT16                              usNbPos;
    VOS_UINT32                              ulGrossCarrierEn;
    VOS_UINT32                              ulGrossInterfereEn;
    VOS_UINT32                              ulValppCarrierEn;
    VOS_UINT32                              ulValppInterfereEn;
    VOS_UINT32                              ulDemTypeToa;
}GPHY_TOOL_RCV_BURST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU
 �ṹ˵��  : ��֡������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulCurFn;
    VOS_UINT16                                  usAfcValue;
    VOS_INT16                                   sAfcTempComp;
    VOS_UINT32                                  ulReserved[2];
    GPHY_TOOL_RCV_BURST_INFO_STRU               astBurstInfo[GPHY_TOOL_TN_NUM_IN_FRAME];
    VOS_UINT32                                  ulBBPCOMMC0TxPriModeAddr;         /* ��Ӧ�Ĵ���BBPCOMM_C0_PRIMARY_MODE_IND_ADDR��ֵ  */
    VOS_UINT32                                  ulBBPCOMMC0RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC1TxPriModeAddr;         /* ��Ӧ�Ĵ���BBPCOMM_C0_PRIMARY_MODE_IND_ADDR��ֵ  */
    VOS_UINT32                                  ulBBPCOMMC1RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC2TxPriModeAddr;         /* ��Ӧ�Ĵ���BBPCOMM_C0_PRIMARY_MODE_IND_ADDR��ֵ  */
    VOS_UINT32                                  ulBBPCOMMC2RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC3TxPriModeAddr;         /* ��Ӧ�Ĵ���BBPCOMM_C0_PRIMARY_MODE_IND_ADDR��ֵ  */
    VOS_UINT32                                  ulBBPCOMMC3RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMGsChSwAddr;            /* BBPCOMM_GS_CH_SW_ADDR  */
    VOS_UINT32                                  ulBBPCOMMPmuChSel0Addr;         /* BBPCOMM_PMU_CH_SEL0_ADDR */
    VOS_UINT32                                  ulBBPCOMMDbgReg20CpuAddr;       /* BBPCOMM_DBG_REG20_CPU_ADDR */
    VOS_UINT16                                  usReserved1;                    /* �����ֶ� */
    VOS_UINT16                                  usReserved2;                    /* �����ֶ� */
}GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_REPORT_ERROR_IND_STRU
 �ṹ˵��  : GPHY��Ϣ,�澯,error�ϱ��ṹ
*****************************************************************************/

typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usFileNo;                       /* �ļ������� */
    VOS_UINT16                                  usLineNo;                       /* ������к� */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY�����ͳһ���LOG ID */
    VOS_UINT16                                  usReserved;                     /* �����ֶ� */
    VOS_UINT16                                  usVarCnt;                       /* �ϱ��������� */
    VOS_UINT32                                  aulVarValue[GPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* �ϱ�����ֵ */
}GPHY_TOOL_REPORT_ERROR_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU
 �ṹ˵��  : ��֡������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_INT16                                   shwCurrTemp;                    /* ��ǰ�¶� */
    VOS_INT16                                   shwXoInitTemp;                  /* У׼�¶� */
    VOS_INT32                                   swTempCompValue;                /* ���μ�����¶Ȳ������ */
    VOS_UINT32                                  auwMantissa[4];  /* DCXO����ʽϵ�� */
    VOS_UINT16                                  auhwExponent[4]; /* DCXO����ʽϵ�� */
}UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU
 �ṹ˵��  : ����֡������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwTaskFn;
    VOS_UINT16                                  enTaskType;
    VOS_UINT16                                  uhwFreqNum;                     /* ר��̬IDLE֡�����������Ƶ����Ŀ */
    VOS_UINT16                                  enOccasionUseMode;              /* ��ǰ���ĸ�ģʽ��ʹ�� */
    VOS_UINT16                                  auhwFreqInfo[GPHY_TOOL_MAX_SYNC_TASK_NUM]; /* ר��̬IDLE֡��������5��BSIC��֤ */
}GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulCurFn;
    VOS_UINT16                                  uhwTimeOutCnt;
    VOS_UINT16                                  uhwOccasionNum;
    GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU        astOccasionUseInfo[ GPHY_TOOL_MAX_IDLE_FRAME_NUM ];
}GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BSIC_SEARCH_INFO_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  enBsicSrchState;
    VOS_UINT16                                  uhwFreq;
    VOS_UINT16                                  uhwRank;
    VOS_UINT16                                  enNStrongIndex;
    VOS_INT16                                   shwRxlev;
    VOS_UINT16                                  uhwReserved;
}GPHY_TOOL_BSIC_SEARCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BSIC_VERIFY_INFO_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  uwCurFn;
    VOS_UINT16                                  enBsicVerifyState;
    VOS_UINT16                                  uhwFreq;
    VOS_UINT16                                  uhwRank;
    VOS_UINT16                                  enNStrongIndex;
    VOS_INT16                                   shwRxlev;
    VOS_INT16                                   shwDCOffsetI;
    VOS_INT16                                   shwDCOffsetQ;
    VOS_UINT16                                  uhwAgcGain;
    VOS_UINT32                                  uwSNR;
    VOS_UINT16                                  uhwBsic;
    VOS_UINT16                                  uhwNCC;
    VOS_UINT16                                  uhwBCC;
    VOS_UINT16                                  uhwReserved;
}GPHY_TOOL_BSIC_VERIFY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_NCELL_RANK_INFO_STRU
 �ṹ˵��  : GSM �������ȼ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usBaListIndex;
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usRank;
    VOS_INT16                                   sRxlev;
    VOS_UINT16                                  usNStrongIndex;
    VOS_UINT16                                  usBsicKnownFlag;
    VOS_UINT16                                  usBsic;
    VOS_UINT16                                  usNCC;
    VOS_UINT16                                  usBCC;
    VOS_UINT16                                  usInMRFlag;
}GPHY_TOOL_NCELL_RANK_INFO_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_INTERRAT_RANK_INFO_STRU
 �ṹ˵��  : ��ϵͳ���ȼ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRank;
    VOS_UINT16                                  usMaxGapNum;                    /* ���ɷ���Ĺ�����Ŀ */
    VOS_UINT16                                  usAssignedGapNum;               /* �ѷ���Ĺ�����Ŀ */
    VOS_UINT16                                  usResv;
}GPHY_TOOL_INTERRAT_RANK_INFO_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_NCELL_INTERRAT_RANK_RPT_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    GPHY_TOOL_NCELL_RANK_INFO_STRU              astNcellRankInfo[GPHY_TOOL_MAX_NCELL_NUM];
    GPHY_TOOL_INTERRAT_RANK_INFO_STRU           stInterratRankInfo;
}GPHY_TOOL_NCELL_INTERRAT_RANK_RPT_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCurFn;
    VOS_UINT16                          uhwCurFnT2;
    VOS_UINT16                          uhwPredictTask;
}GPHY_TOOL_NCELL_RECORD_PREDICT_TASK_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  uhwNcellBcchOccupy;             /* �Ƿ�������ϵͳ�㲥��Ϣռ�� */
    VOS_UINT16                                  uhwSrchRank;                    /* ����Ƶ���������ȼ�*/
    VOS_UINT16                                  uhwInterRatRank;                /* ��ϵͳƵ���������ȼ�*/
    VOS_UINT16                                  uhwVerifyRank;                  /* ��֤Ƶ���������ȼ� */
    GPHY_TOOL_NCELL_RECORD_PREDICT_TASK_STRU    astRecordPredictTask[ GPHY_TOOL_NCELL_RPT_PREDICT_TASK_INFO_NUM ];
}GPHY_TOOL_NCELL_PREDICT_TASK_RPT_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CHN_DUMMY_BURST_RPT_IND
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  uhwDummyPchFlag;                /* ��֡��Ѱ���ļ���� */
    VOS_UINT16                                  uhwAverageValue;                /* ���ݾ���ֵ��ͺ��ֵȡƽ��(�����㷨��·������16��) */
    VOS_UINT32                                  uwFN;                           /* ��ǰ֡�� */
    VOS_INT32                                   swJudgeDataC;                   /* ��������м�ֵ */
    VOS_INT32                                   swJudgeDataD;                   /* ��������м�ֵ */
    VOS_INT32                                   swJudgeDataE;                   /* ��������м�ֵ */
    VOS_INT32                                   swJudgeDataF;                   /* ��������м�ֵ */
}GPHY_TOOL_CHN_DUMMY_PCH_RPT_STRU;


/*****************************************************************************
  6.2 STRUCT����,WPHY����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU
 Э����  :
 �ṹ˵��  : W TX PA�����л�ʱ���ʲ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2MComp;                             /* PA����Ӹ��е��е����޲���,��λ0.1db */
    VOS_INT16                           shwM2HComp;                             /* PA��������е��ߵ����޲���,��λ0.1db */
    VOS_INT16                           shwM2LComp;                             /* PA��������е��͵����޲���,��λ0.1db */
    VOS_INT16                           shwL2MComp;                             /* PA����ӵ��е��е����޲���,��λ0.1db */
}WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_MNTN_TX_PA_GAIN_SWITCH_COMP_STRU
 Э����  :
 �ṹ˵��  : W TX 4��ʱ϶��PA�����л�ʱ���ʲ���ֵ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU  astSlotComp[WPHY_TOOL_PA_SWITCH_COMP_SLOT];
}WPHY_TOOL_TX_PA_GAIN_SWITCH_COMP_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU
 �ṹ˵��  : PA���л�����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                              uhwMsgID;                           /* Msg ID */
    VOS_UINT16                              uhwRsv1;                            /* ���� */

    WPHY_TOOL_TX_PA_GAIN_SWITCH_COMP_STRU   stPaGainSwitchComp;

}WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU
 �ṹ˵��  : PA���л�����ԭ��Ľ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2M;                                 /* �ߵ������油�� */
    VOS_INT16                           shwM2H;                                 /* �е������油�� */
    VOS_INT16                           shwM2L;                                 /* �е������油�� */
    VOS_INT16                           shwL2M;                                 /* �͵������油�� */
}WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU
 �ṹ˵��  : PA���л�����ԭ��Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwTransId;                              /* ԭ��ID,�̶�ֵ:0x5001 */
    VOS_UINT16                          uhwReserved1;                            /* �����ֶ� */
    VOS_UINT16                          uhwFuncType;                            /* �̶�ֵ:0x04 */
    VOS_UINT16                          uhwLength;                              /* ��uwSn����β�ĳ��� */
    VOS_UINT32                          uwSn;                                   /* �̶�ֵ:0 */
    VOS_UINT32                          uwTimeStamp;                            /* �ϱ�CNF����SFN */
    VOS_UINT16                          uhwPrimId;                              /* WDSP_MNTN_MSG_ID_ENUM_UINT16,��ϢID  */
    VOS_UINT16                          uhwReserved2;                           /* */
    VOS_UINT32                          uwResult;                               /* ��Ϣ������ʼ��ַ */
    WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU    stRfPaGainSwitchCompInd;       /* ��ǰ���油���ϱ�*/
}WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_POW_DET_ENABLE_REQ_STRU
 �ṹ˵��  : �����ǲ���ͨ��SDTʵʱ�򿪹ر�PD�ĺ���������ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgID;                               /* Msg ID */
    VOS_UINT16                          uhwRsv1;                                /* ���� */
    VOS_UINT32                          uwPdEnFlg;                              /* PDʹ�ܱ�ǣ�0:ȥʹ�ܣ�1:ʹ��*/
}WPHY_TOOL_POW_DET_ENABLE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_POW_DET_ENABLE_CNF_STRU
 �ṹ˵��  : �����ǲ���ͨ��LMTʵʱ�򿪹ر�PD�ĺ����Ļظ�ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwTransId;                              /* ԭ��ID,�̶�ֵ:0x5001 */
    VOS_UINT16                          uhwReserved1;                            /* �����ֶ� */
    VOS_UINT16                          uhwFuncType;                            /* �̶�ֵ:0x04 */
    VOS_UINT16                          uhwLength;                              /* ��ulSn����β�ĳ��� */
    VOS_UINT32                          uwSn;                                   /* �̶�ֵ:0 */
    VOS_UINT32                          uwTimeStamp;                            /* �ϱ�CNF����SFN */
    VOS_UINT16                          uhwPrimId;                              /* WDSP_MNTN_MSG_ID_ENUM_UINT16����ϢID  */
    VOS_UINT16                          uhwReserved2;                           /* */
    VOS_UINT32                          uwErrCode;                              /* ��� */
}WPHY_TOOL_POW_DET_ENABLE_CNF_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_COMMON_CNF_STRU
 �ṹ˵��  : WPHY��ά�ɲ⹫���ظ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* ����ԭ��Ĵ�����ID */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}WPHY_TOOL_COMMON_CNF_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ACT_CELL_REQ_STRU
 �ṹ˵��  : ���С����Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                                  usReportPeriod;                /* Ĭ��0����ʶ��Ч�����ϱ�����Ϊָ������ʱ����IE��Ч��*/
}WPHY_MNTN_REPORT_TYPE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* Ĭ��ÿ֡�ϱ�  */
}WPHY_TOOL_ACT_CELL_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ACT_CELL_INFO_IND_STRU
 �ṹ˵��  : ���С����Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  ausScramble[WPHY_MNTN_MAX_ACT_CELL_NUM]; /* ���С�������� */
    VOS_UINT16                                  usServingCellScramble;                   /* ��С������ */
}WPHY_TOOL_ACT_CELL_INFO_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU
 �ṹ˵��  : С�������б���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* Ĭ���¼������ϱ���ÿ��С�������ϱ�  */
}WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU
 �ṹ˵��  : С�������б���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usScramble;
    VOS_UINT16                                  usEnergy;
    VOS_UINT32                                  ulPhase;                        /* ��Ҫת��ΪChip���� */
    VOS_UINT16                                  usLifeCycle;                    /* �������� */
    VOS_UINT16                                  usRsv;
}WPHY_MNTN_CS_LIST_CELL_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usCnt;
    WPHY_MNTN_CS_LIST_CELL_INFO_STRU            astCellInfo[32];

}WPHY_MNTN_CS_LIST_INFO_STRU;


typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  usFreqCnt;
    VOS_UINT16                                  usRsv;
    WPHY_MNTN_CS_LIST_INFO_STRU                 astCsList[3];
}WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU
 �ṹ˵��  : ���ع��ܿ��ƣ�ָ���򿪻�ر����µĹ��ع���:
               1.���й��ؿ���(����˿��عرգ����ʶ���еĹ��ع���ȫ��ʧЧ,
                  �����ڻ����أ��⻷���أ�Winup,Windown�ȣ�
                  ��ʱ������ͨ���������ò�������������TPC,SirTarget�ȡ�)
               2.�⻷����(����˹��ܹرգ�����ʶ�⻷���ܹرգ���ʱ����ͨ��
                  ���ʲ������ù���������SirTarget��)
               3.Windown
               4.Winup
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16  enPCType;
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enStatus;

}WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PWR_PARA_SET_REQ_STRU
 �ṹ˵��  : ���ʲ������ã���Mask��ʶ��Ч���
               1.SirTarget
               2.��ʼ���书��
               3.Hold���з��书��(���������С���书��)
               4.����ָ�����͵�����TPC.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32         enPwrParaMask;
    VOS_UINT32                                  ulSirTarget;                    /* SirTarget */
    VOS_INT16                                   sInitTxPwr;                     /* ��ʼ���� */
    VOS_INT16                                   sUlTpc;                         /* ����TPC */
    VOS_INT16                                   sMaxTxPwr;                      /* ����书�� */
    VOS_INT16                                   sMinTxPwr;                      /* ��С���书�� */

}WPHY_TOOL_PWR_PARA_SET_REQ_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MNTN_BLER_REQ_STRU
 �ṹ˵��  : ������ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* Ĭ��ÿ֡�ϱ�  */

}WPHY_TOOL_BLER_REPORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_MNTN_TRCH_BLER_STRU
 �ṹ˵��  : ������ϱ�����
             ����� = ulErrorBlocks/ulTotalBlocks
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTrchId;
    VOS_UINT16                                  usTti;                          /* ÿ�������ŵ���TTI */
    VOS_UINT32                                  ulErrorBlocks;                  /* �����  */
    VOS_UINT32                                  ulTotalBlocks;                  /* �ܿ��� */

}WPHY_MNTN_TRCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MNTN_BLER_IND_STRU
 �ṹ˵��  : ������ϱ�����
             ÿ���ϱ��Ĵ����ŵ��������̶����������ٸ���CNTȷ����
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  usCnt;
    VOS_UINT16                                  usRsv;
    WPHY_MNTN_TRCH_BLER_STRU                    astTrchBler[WPHY_MNTN_TRCH_NUM];

}WPHY_TOOL_BLER_REPORT_IND_STRU;







/*****************************************************************************
 �ṹ��    : WPHY_MNTN_EVENT_REPORT_REQ_STRU
 �ṹ˵��  : �¼��ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32       enEventTypeMask;

}WPHY_TOOL_EVENT_REPORT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SYNC_STATUS_IND_STRU
 �ṹ˵��  : W��ͬ��ʧ��״̬�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_SYNC_STATUS_ENUM_UINT16           enSyncStatus;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SYNC_STATUS_IND_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_AFC_STATUS_IND_STRU
 �ṹ˵��  : AFC����
   EVENT_VCTCXO_FREEZE ,EVENT_VCTCXO_UNFREEZE
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_TCXO_STATUS_ENUM_UINT16           enTcxoStatus;
    VOS_UINT16                                  usRsv;
    VOS_UINT32                                  ulAfcStatusValue;

}WPHY_TOOL_AFC_STATUS_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MNTN_INTERRUPT_EXCEPTIION_IND_STRU
 �ṹ˵��  : �ж��쳣�¼��ϱ���
               1.��6ms�������ʱ����ȡ9ms�����Ѿ����
               2.��9ms�������ʱ����ȡSFN�жϸ������Ƿ��Ѿ���֡��
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;

    WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16       enIntExceptType;                /* �ж��쳣���� */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_INTERRUPT_EXCEPTIION_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU
 �ṹ˵��  : �ϱ�L1״̬
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;

    VOS_UINT32                                  ulChannelStatus;                /* �ŵ�״̬ */
    WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16       enSysStatus;                    /* ϵͳ״̬ */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DRX_SWITCH_REQ_STRU
 �ṹ˵��  : DRX���ܴ򿪺͹ر�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enDrxCtrl;
    VOS_UINT16                                  usRsv;

}WPHY_TOOL_DRX_SWITCH_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_THRESHOLD_SET_REQ_STRU
 �ṹ˵��  : ��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;
    VOS_INT32                                   lValue;

}WPHY_TOOL_THRESHOLD_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU
 �ṹ˵��  : ��ѯ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;

}WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_THRESHOLD_QUERY_CNF_STRU
 �ṹ˵��  : ��ѯ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;
    VOS_INT32                                   lValue;

}WPHY_TOOL_THRESHOLD_QUERY_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ERROR_REPORT_REQ_STRU
 �ṹ˵��  : �����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16  enErrorRptLevel;                /* �����ϱ����󼶱� */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_ERROR_REPORT_REQ_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ERROR_REPORT_IND_STRU
 �ṹ˵��  : �����ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usFileNo;                       /* �ļ������� */
    VOS_UINT16                                  usLineNo;                       /* ������к� */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY�����ͳһ���LOG ID */
    VOS_UINT16                                  usReserved;                     /* �����ֶ� */
    VOS_UINT16                                  usVarCnt;                       /* �ϱ��������� */
    VOS_UINT32                                  aulVarValue[WPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* �ϱ�����ֵ */

}WPHY_TOOL_ERROR_REPORT_IND_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU
 �ṹ˵��  : RFǰ�˲����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */

    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* Ĭ��ÿ֡�ϱ�  */

}WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU
 �ṹ˵��  : �ϱ�TX Temp Comp,Freq Comp,AFC,LNA,HDET
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_INT16                                   sPaHighTempComp;                /* PA������ʱ�¶Ȳ��� */
    VOS_INT16                                   sPaMidTempComp;                 /* PA������ʱ�¶Ȳ��� */
    VOS_INT16                                   sPaLowTempComp;                 /* PA������ʱ�¶Ȳ��� */

    VOS_INT16                                   sPaHighFreqComp;                /* PA������ʱƵ�ʲ��� */
    VOS_INT16                                   sPaMidFreqComp;                 /* PA������ʱƵ�ʲ��� */
    VOS_INT16                                   sPaLowFreqComp;                 /* PA������ʱƵ�ʲ��� */

    VOS_UINT16                                  usAfcStatus;                    /* AFCֵ */
    VOS_UINT16                                  usAnt1AgcStatus;                /* ����1��AGC����״̬ */
    VOS_UINT16                                  usAnt2AgcStatus;                /* ����2��AGC����״̬ */
    VOS_UINT16                                  usHdet;                         /* HDETֵ */
    VOS_UINT16                                  usPaStatus;                     /* PA״̬:�ϱ�����PA��ģʽ������ */
    VOS_UINT16                                  usDbbAtten;                     /* DBB˥�� */
    VOS_UINT16                                  usRfAtten;                      /* RF˥�� */
    VOS_UINT16                                  usReserved;

}WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PI_INT_RESULT_IND_STRU
 �ṹ˵��  : WPHY��PI�жϽ���ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_INT16                                   sPiResult;
    VOS_UINT16                                  usPiSoftValue;
    UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU           stWphyDrxMntn;                  /* DRX��ά�ɲ���Ϣ */
}WPHY_TOOL_PI_INT_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_AI_INT_RESULT_IND_STRU
 �ṹ˵��  : WPHY��AI�жϽ���ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_INT16                                   sAiResult;                      /* AI���,+1��-1��0 */
    VOS_UINT16                                  usReTranNum;                    /* �ش����� */
    VOS_INT16                                   sInitPower;                     /* ��ʼ����,��λ 0.1dBm */
    VOS_INT16                                   sCurrentPower;                  /* ��ǰ����,��λ 0.1dBm */
    VOS_UINT32                                  uwMaxTxPower;                   /* ����书��,��λ0.1dBm */
}WPHY_TOOL_AI_INT_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : T313 Timer Status
 �ṹ˵��  : T313��ʱ��״̬�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_T313_STATUS_ENUM_UINT16      enT313Status;                   /* T313״̬*/
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_T313_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : T312 Timer Status
 �ṹ˵��  : T312��ʱ��״̬�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_T312_STATUS_ENUM_UINT16      enT312Status;                   /* T313״̬*/
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_T312_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : ��ģCDRX��������
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
}WPHY_TOOL_SLAVE_CDRX_START_IND_STRU;

/*****************************************************************************
 �ṹ��    : ��ģCDRX����ֹͣ
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
}WPHY_TOOL_SLAVE_CDRX_STOP_IND_STRU;


/*****************************************************************************
 �ṹ��    :WPHY_TOOL_AMP_PATH_INFO_STRU
 Э����  :
 �ṹ˵��  :�ྶ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPathEnergy;                          /* ������ */
    VOS_UINT16                          uhwPathPos;                             /* ����λ */
} WPHY_TOOL_AMP_PATH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WSLAVE_MEAS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W SLAVE MEAS��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                uwUnitBitMap;                     /* CS status */
    WPHY_TOOL_AMP_PATH_INFO_STRU              stUnitFirstFingerInfo;            /* Strongest finger info */
} WPHY_TOOL_WSLAVE_MEAS_INFO_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSlotEnergy;                          /* bit[14:0]��С������ */
    VOS_UINT16                          uhwSlotPhase;                           /* bit[28:16]��ʱ϶��λ */
} WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_STPEAB_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY_TOOL_STPEAB_INFO_STRU��Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwStepABSucFlag;
    VOS_UINT16                          uhwReserve;
    WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU    stStep1Info;
    WPHY_TOOL_TIMING_INFO_STRU          stStepAbStartTime;
    WPHY_TOOL_TIMING_INFO_STRU          stStepAbEndTime;
} WPHY_TOOL_STPEAB_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ACS_CELL_INFO_STRU
 Э����  :
 �ṹ˵��  :  ÿ��С����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCellEnergy;                          /* bit[15:0] ��Step3/setpB�����õ���С������ */
    VOS_UINT16                          uhwScramble;                            /* bit[24:16]��Step3/setpB�����õ�������� */
    VOS_UINT16                          uhwSlotNo;                              /* bit[35:32]��ʱ϶��*/
    VOS_UINT16                          uhwSlotPhase;                           /* bit[60:48]��ʱ϶��λ*/
} WPHY_TOOL_ACS_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_STPE23_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY_TOOL_STPE23_INFO_STRU��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwStep23SucFlag;
    VOS_UINT16                          uhwCS3RsltNum;
    WPHY_TOOL_TIMING_INFO_STRU          stStep23StartTime;
    WPHY_TOOL_TIMING_INFO_STRU          stStep23EndTime;
    WPHY_TOOL_ACS_CELL_INFO_STRU        stCS3SucInfo[WPHY_MNTN_SLAVE_STEP23_CELL_NUM];
} WPHY_TOOL_STPE23_INFO_STRU;


/*****************************************************************************
 ö����    : WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16
 Э����  :
 ö��˵��  : ��ģCS״̬
ASN.1���� :
 ö��˵��  : ��ģCS״̬
*****************************************************************************/
enum WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM
{
    WPHY_MNTN_SLAVE_CS_STATUS_INVALID               = 0x0,
    WPHY_MNTN_SLAVE_CS_STATUS_STEPAB_RUNNING        = 0x1,                      /* ��ģ���������б�� */
    WPHY_MNTN_SLAVE_CS_STATUS_STEP23_RUNNING        = 0x2,                      /* ��ģstep23���б�� */
    WPHY_MNTN_SLAVE_CS_STATUS_FINISH                = 0x4,                      /* ��ģС��������ɱ�� */
    WPHY_MNTN_SLAVE_CS_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WSLAVE_CS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W SLAVE CS��Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16    enCsStatus;                   /* CS status */
    VOS_UINT16                          uhwReserve;                             /* Reserve */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwIntraStepAbEn;                       /* IntraStepAbEn */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwIntraStep23En;                       /* IntraStep23En */
    WPHY_TOOL_STPEAB_INFO_STRU          stStepAbInfo;                           /* only save one slot info */
    WPHY_TOOL_STPE23_INFO_STRU          stStep23Info;                           /* if success, save scram code, energy etc. */
} WPHY_TOOL_WSLAVE_CS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_AFC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʱ���µ�ǰppm��scpll����ֵ���¶�ֵ��AFCֵ
*****************************************************************************/
typedef struct
{
    VOS_INT32                           swPpmValue;                             /* ppm */
    VOS_UINT32                          uwPllFracValue;                         /* Scpll С�����ֵ���ֵ */
    VOS_UINT32                          uwPllInterValue;                        /* Scpll �������ֵ���ֵ */
    VOS_UINT32                          uwAfcValue4518;                         /* AFC 4518 */
    VOS_UINT32                          uwAfcValue452C;                         /* AFC 452C */
    VOS_UINT32                          uwAfcValue4500;                         /* AFC 4500 */
    VOS_UINT32                          uwAfcValue450C;                         /* AFC 450C */
    VOS_INT16                           shwTemperatureValue;                    /* �¶� */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_AFC_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WSLAVE_FE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W SLAVE ǰ����Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_AFC_INFO_STRU             stAfcInfo;                              /* ��ʱ���µ�ǰppm��scpll����ֵ���¶�ֵ��AFCֵ */
    VOS_UINT32                          uwFeRssi;                               /* RSSI 1414 */
    VOS_UINT32                          uwFeRssiDiv;                            /* RSSI 1418 */
    VOS_UINT32                          uwDcOffset[8];                          /* DC OFFSET */
    VOS_UINT32                          uwTcvrOnRx[4];                          /* TRANSVER ON */
    VOS_UINT32                          uwTcvrOnTx[2];                          /* TRANSVER ON */
    VOS_UINT32                          uwChnMasterModeRx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnMasterModeTx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnSlaveMode[4];                      /* Channel slave mode */
    VOS_UINT32                          uwSsiEn[2];                             /* SSI EN */
    VOS_UINT32                          uwRfPllStatus;                          /* rfic������ʧ��״̬ */
    VOS_UINT16                          uhwTasAntStatusInfo;                    /* TasAntStatus */
    VOS_UINT16                          uhwReserve;
} WPHY_TOOL_WSLAVE_FE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WBBP_GAP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W SLAVE BBP enter exit gap ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uw3F34To3F40[4];                        /* enter exit gap, measure status */
    VOS_UINT32                          uwMaterMeasWen;                         /*  10E8 */
    VOS_UINT32                          uwMipiSsiBusy;                          /*  F80A34 */
} WPHY_TOOL_WBBP_GAP_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_WSLAVE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W slave mode mntn info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_TIMING_INFO_STRU                  stWslaveTimingInfo;             /* ��ʱ�ϱ���Ϣ(����Я��SFN CFN SLOT SLICE��Ϣ) */
    VOS_UINT16                                  uhwCurrFreq;                    /* CurrFreq */
    VOS_UINT16                                  uhwCurrBand;                    /* CurrBand */
    WPHY_TOOL_WSLAVE_CS_INFO_STRU               stWslaveCSInfo;                 /* WslaveCSInfo */
    WPHY_TOOL_WSLAVE_MEAS_INFO_STRU             stWslaveMeasInfo;               /* WslaveMeasInfo */
    WPHY_TOOL_WSLAVE_FE_INFO_STRU               stWslaveFeInfo;                 /* ǰ����Ϣ */
    WPHY_TOOL_WBBP_GAP_INFO_STRU                stWbbpEnterExitGapInfo;         /* EnterExitGapInfo */
}WPHY_TOOL_WSLAVE_MNTN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : ��ģSTATUS
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16                   enMsgId;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                          uhwToolId;              /* tools id */
    WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16     enCurrentStatus;
    VOS_UINT16                                          usCurrentFreqIndex;
    VOS_UINT16                                          ausMeasStatus[WPHY_MNTN_SLAVE_REPORTFREQ_NUM];
    VOS_UINT16                                          ausCSStatus[WPHY_MNTN_SLAVE_REPORTFREQ_NUM];
    VOS_UINT16                                          usMeasCellNumb;
    VOS_UINT16                                          usMeasCellIndex;
    WPHY_TOOL_WSLAVE_MNTN_INFO_STRU                     stWslaveInfo;
}WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU
 �ṹ˵��  : PA״̬�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */

    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* Ĭ��ÿ֡�ϱ�  */

}WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU
 �ṹ˵��  : ����LTE��ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulWakeReason;                   /* ����Ŀ�� */
}WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU
 �ṹ˵��  : ����LTE������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulStartReason;                  /* ����ԭ�� */
    VOS_UINT32                                  ulMeasTime;                     /* ����ʱ�� us */
    VOS_UINT32                                  ulInt0Int1Time;                 /* int0 int1��� us */
    VOS_UINT32                                  ulAfcLockFlag;
    VOS_INT32                                   slAfcValue;
}WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU
 �ṹ˵��  : ����LTE������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* �ϱ�ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* �ϱ�ʱ�̵�slot */
}WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU
 �ṹ˵��  : ǿͣLTE������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16                   enMsgId;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                          usToolsId;              /* �����ֶ� */
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM_UINT16  enReason;               /* ǿͣԭ�� */
    VOS_UINT16                                          usSfn;                  /* ǿͣʱ�̵�sfn */
    VOS_UINT16                                          usSlot;                 /* ǿͣʱ�̵�slot */
    VOS_UINT16                                          usRsv;
}WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU
 �ṹ˵��  : ����LTE������ǵ�ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usValue;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CFG_TIME_INFO_STRU
 �ṹ˵��  : ���õ�ʱ��
*****************************************************************************/
typedef struct
{

    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usCfn;                          /* ����ʱ�̵�cfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT16                                  usChip;                         /* ����ʱ�̵�chip */
}WPHY_TOOL_CFG_TIME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CFG_TIME_INFO_STRU
 �ṹ˵��  : ���õ�ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRfCfgOpSc;                    /* RF���õ�Ŀ�� */
    VOS_UINT16                                  usAntMode;                      /* RF����ģʽ */
    VOS_UINT16                                  usIntraBand;                    /* ��ƵBAND */
    VOS_UINT16                                  usIntraFreq;                    /* ��ƵƵ�� */
    VOS_UINT16                                  usAdjFreq;                      /* ��ƵƵ�� */
    VOS_UINT16                                  usInterBand;                    /* ��ƵBAND */
    VOS_UINT16                                  usInterFreq;                    /* ��ƵƵ�� */
    VOS_UINT16                                  usRxRficMode;                   /* RX RFICģʽ */
    VOS_UINT16                                  usTxRficMode;                   /* TX RFICģʽ */
    VOS_UINT16                                  usReserve;
}WPHY_TOOL_RF_CFG_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MASTER_RF_CONFIG_IND_STRU
 �ṹ˵��  : ����LTE������ǵ�ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* RF����ʱ�� */
    WPHY_TOOL_RF_CFG_INFO_STRU                  stCfgInfo;                      /* RF������Ϣ */
}WPHY_TOOL_MASTER_RF_CONFIG_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_QPC_OPEN_UL_IND_STRU
 �ṹ˵��  : QPC��������·��ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulOpenReason;                   /* ��ԭ�� */
}WPHY_TOOL_QPC_OPEN_UL_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_QPC_CLOSE_UL_IND_STRU
 �ṹ˵��  : QPC�ر�������·��ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulCloseReason;                  /* �ر�ԭ�� */
}WPHY_TOOL_QPC_CLOSE_UL_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_QPC_RRC_STATE_IND_STRU
 �ṹ˵��  : QPC��ǰRRC״̬��ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulRrcState;                     /* RRC״̬ */
}WPHY_TOOL_QPC_RRC_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_QPC_RB_TYPE_IND_STRU
 �ṹ˵��  : QPC��ǰҵ�����͵�ָʾ CS/PS
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;                          /* ����ʱ�̵�sfn */
    VOS_UINT16                                  usSlot;                         /* ����ʱ�̵�slot */
    VOS_UINT32                                  ulRbType;                       /* RB TYPE */
}WPHY_TOOL_QPC_RB_TYPE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU
 �ṹ˵��  : TAS���л������׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_INT16                                   sRssi;                          /* �����ߵ�RSSI,�˲���Ľ��,��λΪ0.125dbm */
    VOS_INT16                                   sRscp;                          /* �����ߵ�RSCP,�˲���Ľ��,��λΪ0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊ������1Ϊ�ּ� */
}WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU
 �ṹ˵��  : TASä�л������׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* ��һ״̬ */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_INT16                                   sDeltaRscp;                     /* T1ʱ�����źŴ����м�ֵǰ�������� */
    VOS_INT16                                   sRscpAveCurr;                   /* ��ǰT1ʱ�䵥�����С������,��λΪ0.125dbm */
    VOS_INT16                                   sRscpAvePre;                    /* ǰһ��T1ʱ�䵥�����С������,��λΪ0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊ������1Ϊ�ּ� */
}WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TAS_ESTIMATE_STATE_IND_STRU
 �ṹ˵��  : TAS�����׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU  stNonBlindInfo;                 /* ���л�����״̬��Ϣ */
    WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU     stBlindInfo;                    /* ä�л�����״̬��Ϣ */
}WPHY_TOOL_TAS_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU
 �ṹ˵��  : TAS���л��ȽϽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usPhase;                        /* �ȽϽ׶���һ�׶� */
    VOS_INT16                                   sDeltaRscp;                     /* ���ּ������˲����RSCP��ֵ,��λΪ0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊ������1Ϊ�ּ� */
}WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU
 �ṹ˵��  : TASä�л��ȽϽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usRsv;
    VOS_UINT16                                  usPhase;                        /* �ȽϽ׶���һ�׶� */
    VOS_INT16                                   sRscpAveCurr;                   /* ���ּ������˲����RSCP��ֵ,��λΪ0.125dbm */
    VOS_INT16                                   sRscpAvePre;                    /* ���ּ������˲����RSCP��ֵ,��λΪ0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊ������1Ϊ�ּ� */
}WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TAS_COMPARE_STATE_IND_STRU
 �ṹ˵��  : TAS�ȽϽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU   stNonBlindInfo;                    /* ��һ˫����״̬ */
    WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU      stBlindInfo;                        /* �ȽϽ׶���һ�׶� */
}WPHY_TOOL_TAS_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TAS_PROTECT_STATE_IND_STRU
 �ṹ˵��  : TAS���ͽ׶ο�ά�ɲ��ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usNextState;                    /* ��һ˫����״̬ */
    VOS_UINT16                                  usAntStatus;                    /* ��ǰ����״̬,0Ϊ������1Ϊ�ּ� */
}WPHY_TOOL_TAS_PROTECT_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SLAVE_W_FINISH_IND_STRU
 �ṹ˵��  : ��ģW�������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_W_FINISH_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU
 �ṹ˵��  : ��ģW�������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU
 �ṹ˵��  : ��ģG BSIC�������ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU
 �ṹ˵��  : ��ģ���ȳ�ʱָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usStartChip;
    VOS_UINT16                                  usStartSlot;
    VOS_UINT16                                  usEndChip;
    VOS_UINT16                                  usEndSlot;
    VOS_UINT16                                  usScheduleTime;                 /* ����ʱ�䣬��λus */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU;
/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PA_STATUS_REPORT_IND_STRU
 �ṹ˵��  : PA״̬�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_PA_STATUS_ENUM_UINT16        enPaStatus;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_PA_STATUS_REPORT_IND_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU
 �ṹ˵��  : PHY �ڲ���Ϣ�ϱ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usMsgRptFlag;                   /* ָʾ�ڲ���Ϣ�Ƿ��ϱ� */
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
}WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU
 �ṹ˵��  : ��̬��ѯǰ��״̬����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
}WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU
 �ṹ˵��  : ��̬��ѯǰ��״̬�ظ�ԭ��
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usRfTrcvOnState;                /* RF�ܿ��أ�1Ϊ�򿪣�0Ϊ�ر� */
    VOS_UINT16                                  usRfRxOnOrOff;                  /* 04h[1:0] = 3Ϊ�� */
    VOS_UINT16                                  usRxPathselect;                 /* 04h[4:3] = 3Ϊ���ּ�������2������ */
    VOS_UINT16                                  usWagcSwitch;                   /* WBBP ���ּ����� */

    VOS_UINT16                                  usAbbRxConfig;                  /* 3Ϊ���ּ�������1������ */
    VOS_UINT16                                  usAbbTxCh01LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:Gģ 2:Wģ 3:LTEģ 4:TDSģ 5:ETģʽ 6:APTģʽ 7:CAģʽ */
    VOS_UINT16                                  usAbbTxCh23LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:Gģ 2:Wģ 3:LTEģ 4:TDSģ 5:ETģʽ 6:APTģʽ 7:CAģʽ */
    VOS_UINT16                                  usAbbRxCh01LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:Gģ 2:Wģ 3:LTEģ 4:TDSģ 5:ETģʽ 6:APTģʽ 7:CAģʽ */
    VOS_UINT16                                  usAbbRxCh23LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:Gģ 2:Wģ 3:LTEģ 4:TDSģ 5:ETģʽ 6:APTģʽ 7:CAģʽ */
    VOS_UINT16                                  usAbbRxCh01Mode;                /* CH1:[15:8],CH0:[7:0] = 0:2G 1:3G_SC 2:4G 3: 3G_DC 4:TDS */
    VOS_UINT16                                  usAbbRxCh23Mode;                /* CH1:[15:8],CH0:[7:0] = 0:2G 1:3G_SC 2:4G 3: 3G_DC 4:TDS */
    VOS_UINT16                                  usAbbCh01VoiceData;             /* CH1:[15:8],CH0:[7:0] = 1:voice mode 2: data mode */
    VOS_UINT16                                  usAbbCh23VoiceData;             /* CH1:[15:8],CH0:[7:0] = 1:voice mode 2: data mode */

    VOS_UINT16                                  usRfTxOnOrOff;                  /* 02h[1:0] = 3Ϊ�� */
    VOS_UINT16                                  usRfTxSHDN;                     /* RF���д򿪿��ƣ�0��BBP���� */
    VOS_UINT16                                  usTxPathselect;                 /* RFIC TX Patch */
    VOS_UINT16                                  usRfTxAgc;                      /* RFIC TXAGC */

    VOS_UINT16                                  usCpcDrxFuncOn;                 /* ��ǰ������CPC DRX�ı�־ */
    VOS_UINT16                                  usCpcDrxStartCfn;               /* CPC DRX��ʼ������CFN */
    VOS_UINT16                                  usCpcSleepBitMap;               /* ��16bit��1Ϊ����ʱ϶��0Ϊ˯��ʱ϶ */

    VOS_UINT16                                  usGpioFuncOn;                   /* Ӳ��֧��GPIO */
    VOS_UINT16                                  usGpioPaMode;                   /* GPIO PA mode */

    VOS_UINT16                                  usMipiFuncOn;                   /* Ӳ��֧��MIPI */
    VOS_UINT16                                  usMipiPaMode;                   /* MIPI PA mode */

    VOS_UINT16                                  usAptFuncOn;                    /* Ӳ��֧��APT */
    VOS_UINT16                                  usAptPaMode;                    /* APT��ѹmode */
    VOS_UINT16                                  uhwAptVcc;                          /* ���� */
}WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU
 �ṹ˵��  : �Ƿ�ʵʱ���ǰ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enDisplayCtrl;
    VOS_UINT16                                  usReserved;
}WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_BBP_RTC_REQ_STRU
 �ṹ˵��  : RTC���ܴ򿪺͹ر�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    UPHY_TOOL_RTC_DEBUG_ENUM_UINT16             enRtcCtrl;                      /* RTC�򿪻��߹ر� */
    VOS_UINT16                                  usRsv;

}WPHY_TOOL_BBP_RTC_REQ_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAM_REPORT_REQ_STRU
 �ṹ˵��  : WPHYץȡ�̶��黭ͼ��RAM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16          enRptRam;
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptStatus;
}WPHY_TOOL_RAM_REPORT_REQ_STRU;





/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAM_REPORT_IND_STRU
 �ṹ˵��  : WPHYץȡ�̶��黭ͼ��RAM
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16          enRptRam;
    VOS_UINT16                                  usRsv;
    VOS_UINT32                                  aulData[2];
}WPHY_TOOL_RAM_REPORT_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU
 �ṹ˵��  : WPHYץȡ�ǹ̶���ַ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulBlkAddr;                      /* ץȡ���ݿ���׵�ַ */
    VOS_UINT32                                  ulBlkLen;                       /* ץȡ���ݿ�ĳ���,��λ:32bit */
}WPHY_TOOL_BLK_REPORT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRsv;
    WPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[WPHY_TOOL_RPT_BLK_MAX_NUM];
}WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU;




/*****************************************************************************
 �ṹ��    : WPHY_TOOL_BLK_REPORT_LIST_IND_STRU
 �ṹ˵��  : WPHYץȡ�ǹ̶���ַ������
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[WPHY_TOOL_RPT_BLK_MAX_NUM];
    VOS_UINT32                                  aulData[2];
}WPHY_TOOL_BLK_REPORT_LIST_IND_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU
 �ṹ˵��  : ��������ά�ɲ��ϱ�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enRaMntnCtrl;                   /* ��������ά�ɲ�򿪻�ر� */
    VOS_UINT16                                  usReserve;                      /* �����ֶ� */
}WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU
 �ṹ˵��  : ARM 0MS��ά�ɲ��ϱ�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enArm0msMntnCtrl;               /* ARM 0MS�򿪻�ر� */
    VOS_UINT16                                  usReserve;                      /* �����ֶ� */
}WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU
 �ṹ˵��  : UPA��֡��ά�ɲ���Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRptValue[WPHY_MNTN_HSUPA_RPT_VALUE_MAX_NUM][WPHY_MNTN_HSUPA_OM_CARERIER_NUM];
}WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_UPA_RPT_INFO_STRU
 �ṹ˵��  : UPA��ά�ɲ���Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU        astRptValue[WPHY_MNTN_HSUPA_SUB_FRM_NUM];
}WPHY_TOOL_UPA_RPT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_GSM_CELL_SNR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������������ϱ�����С���������������,����ֵ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                              uhwMsgId;                           /* _H2ASN_Skip */    /* ԭ��ID */
    VOS_UINT16                              uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                              uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                              uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_GSM_CELL_SNR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_GSM_CELL_SNR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��С���������,����ֵ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFreqInfo;                            /* Ƶ����Ϣ�ϱ�����12bit��ʾƵ�Σ�0:850,1:900,2:1800,3:1900����12bit��ʾƵ��ţ�0-1023��*/
    VOS_INT16                           shwRxLev;                               /* �ź�ǿ��ֵ��[-110,-15],��λΪdbm */
    VOS_UINT16                          uhwCellSnr;                             /* ����ȣ�[0,99],��λΪdb */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_GSM_CELL_SNR_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_GSM_CELL_SNR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�����С���������������,����ֵ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCellNum;                             /* Ƶ���� */
    GPHY_TOOL_GSM_CELL_SNR_STRU         astCellInfo[GPHY_TOOL_MA_FREQ_NUM];       /* С����Ϣ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_GSM_CELL_SNR_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BA_LIST_MEAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�BA LIST���ź�ǿ�ȣ�bsic��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_BA_LIST_MEAS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CELL_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��С������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFreqInfo;                            /* Ƶ����Ϣ�ϱ�����12bit��ʾƵ�Σ�0:850,1:900,2:1800,3:1900����12bit��ʾƵ��ţ�0-1023��*/
    VOS_INT16                           shwRxLev;                               /* �ź�ǿ��ֵ��[-110,-15],��λΪdbm */
    VOS_UINT16                          uhwBsic;                                /* ��վ��ʶ�룬0-77����Ч0xffff */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_CELL_MEAS_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_BA_LIST_MEAS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�BA LIST���ź�ǿ�ȣ�bsic��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwScellFreqInfo;                       /* Ƶ����Ϣ�ϱ�����12bit��ʾƵ�Σ�0:850,1:900,2:1800,3:1900����12bit��ʾƵ��ţ�0-1023��*/
    VOS_INT16                           shwScellRxLev;                          /* �ź�ǿ��ֵ��[-110,-15],��λΪdbm */
    VOS_UINT16                          uhwHoppingInd;                          /* ��Ƶָʾ,1:��ʾ��Ƶ,0��ʾ����Ƶ */
    VOS_UINT16                          uhwResvered1;                           /* �����ֶ� */
    VOS_UINT16                          uhwCellNum;                             /* �����ĸ��� */
    VOS_UINT16                          uhwResvered2;                           /* �����ֶ� */
    GPHY_TOOL_CELL_MEAS_STRU            astNeighbourCell[GPHY_TOOL_BA_LIST_MAX_NUM]; /* �����Ĳ�����Ϣ */
}GPHY_TOOL_BA_LIST_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_SETTING_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�AMR������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_AMR_SETTING_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_SETTING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�AMR������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwAcsNum;                              /* �������,��ΧΪ0-4 */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
    VOS_UINT16                          auhwAcs[GPHY_TOOL_AMR_MAX_ACS_NUM];       /* ������ϣ���Χ0-7 */
    VOS_UINT16                          auhwHyst[GPHY_TOOL_AMR_MAX_ACS_NUM-1];    /* �л����ʹ�С����Χ0-15����λΪ0.5db */
    VOS_UINT16                          auhwThd[GPHY_TOOL_AMR_MAX_ACS_NUM-1];     /* �л����޴�С����ΧΪ0-63����λΪ0.5db */
}GPHY_TOOL_AMR_SETTING_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ������ÿ���������ʵ�ʹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ������ÿ���������ʵ�ʹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwAcsNum;                              /* �������,��ΧΪ0-4 */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
    VOS_UINT16                          auhwAcs[GPHY_TOOL_AMR_MAX_ACS_NUM];       /* ������ϣ���Χ0-7 */
    VOS_UINT32                          auwUplink[GPHY_TOOL_AMR_MAX_ACS_NUM];     /* ������·�����ÿ�����ʵĿ�������Χ0-2^32-1����λΪ�� */
    VOS_UINT32                          auwDownlink[GPHY_TOOL_AMR_MAX_ACS_NUM];   /* ������·�����ÿ�����ʵĿ�������Χ0-2^32-1����λΪ�� */
}GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������������ʵ�ʹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_AMR_CODEC_AVG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ���������ʵ�ʹ����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          auhwUplink[GPHY_TOOL_AMR_CODEC_MAX_NUM];  /* ������·�����ÿ�����ʵĿ�������Χ0-2^32-1����λΪ�� */
    VOS_UINT32                          auhwDownlink[GPHY_TOOL_AMR_CODEC_MAX_NUM];/* ������·�����ÿ�����ʵĿ�������Χ0-2^32-1����λΪ�� */
}GPHY_AMR_CODEC_AVG_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_AMR_CODEC_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С�������е�ͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    GPHY_AMR_CODEC_AVG_STRU             stCell;                                 /* С����ͳ����Ϣ */
    GPHY_AMR_CODEC_AVG_STRU             stCall;                                 /* ÿ�����е�ͳ����Ϣ */
}GPHY_TOOL_AMR_CODEC_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CS_PS_TX_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�CS/PS��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_CS_PS_TX_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CS_PS_TX_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�CS/PS��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwTa;                                  /* ʱ����ǰ������ΧΪ0-63����λΪ���� */
    VOS_UINT16                          uhwSlotNumber;                          /* ʱ϶���� */
    VOS_UINT16                          uhwTxPower[4];                          /* ���з��书�ʣ���ΧΪ0-99����λΪdbm */
    VOS_UINT16                          uhwPcl;                                 /* ��վָ���Ĺ��ʵȼ�����ΧΪ0-31 */
    VOS_UINT16                          uhwResvered;
}GPHY_TOOL_CS_PS_TX_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CS_FER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�CS FER��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_CS_FER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CS_FER_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�CS FER��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT32                          uwErrorFrameFull;                       /* full��Ĵ���֡�� */
    VOS_UINT32                          uwTotalFrameFull;                       /* full��֡�� */
    VOS_UINT32                          uwErrorFrameSub;                        /* sub��Ĵ���֡�� */
    VOS_UINT32                          uwTotalFrameSub;                        /* sub��֡�� */
}GPHY_TOOL_CS_FER_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_CS_GET_CURRENT_DSC_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�������·����ֵ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwCommand;                             /* ���0:ֹͣ��1������ */
    VOS_UINT16                          uhwResvered;                            /* �����ֶ� */
}GPHY_TOOL_GET_CURRENT_DSC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_GET_CURRENT_DSC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�������·����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* ԭ��ID */
    VOS_UINT16                          uhwToolId;                              /* �����ֶ� */
    VOS_UINT16                          uhwDsc;                                 /* ������·����ֵ */
    VOS_UINT16                          uhwResvered;
}GPHY_TOOL_GET_CURRENT_DSC_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������������׶��о�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                               /* _H2ASN_Skip */ /* ԭ��ID */
    VOS_UINT16                          uhwToolId;                                  /* tools id */
    VOS_UINT16                          uhwDualAntCurId;                        /* ����id */
    VOS_UINT16                          uhwDualAntNextState;                    /* ��һ����ת�׶� */
    VOS_UINT16                          uhwRxlevAvgSub;                         /* ������ƽ��ÿ��ͳ������SUB�������ֵ */
    VOS_UINT16                          uhwReserved;                                /* reserved  */
}GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������������ȽϽ׶��о�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMsgID;                                   /* _H2ASN_Skip */ /* ԭ��ID */
    VOS_UINT16                      uhwToolId;                                  /* tools id */
    VOS_UINT16                      uhwDualAntCurId;                            /* �л�ǰ������id */
    VOS_UINT16                      uhwDualAntNextId;                           /* �л��������id */
    VOS_UINT16                      uhwDualAntNextState;                        /* ��һ����ת�׶� */
    VOS_UINT16                      uhwAntCmpNextSubState;                      /* ��һ����ת��״̬ */
    VOS_INT16                       shwRxlevFilterPriAnt;                       /* ������ƽ��ÿ��ͳ�����ڵ������˲�ֵ */
    VOS_INT16                       shwRxlevFilterSecAnt;                       /* ������ƽ��ÿ��ͳ�����ڵ������˲�ֵ */
    VOS_INT16                       shwDeltaRxlev;                              /* ��������������ƽ��ÿ��ͳ�����ڵ������˲���ֵ */
    VOS_UINT16                      uhwReserved;                                /* reserved  */
}GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU;


/*****************************************************************************
 �ṹ��    : GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����л�ͣ�ͽ׶��о�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMsgID;                                   /* _H2ASN_Skip */ /* ԭ��ID */
    VOS_UINT16                      uhwToolId;                                  /* tools id */
    VOS_UINT16                      uhwDualAntCurId;                            /* ����id */
    VOS_UINT16                      uhwDualAntNextState;                        /* ��һ����ת�׶� */
    VOS_UINT16                      uhwHandAntEn;                               /* ͣ�ͽ׶������������־ */
    VOS_UINT16                      uhwReserved;                                /* reserved  */
}GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU;


/*****************************************************************************
 DCά������ö��
*****************************************************************************/
enum UPHY_TOOL_DCOFFSET_ENUM
{
    UPHY_TOOL_DCOFFSET_UPDATE_INIT      = 0,
    UPHY_TOOL_DCOFFSET_UPDATE_REMAIN    = 1,

    UPHY_TOOL_DCOFFSET_UPDATE_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_DCOFFSET_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DC_OFFSET_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM DC Offset Report
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                                   /* _H2ASN_Skip */ /* ԭ��ID */
    VOS_UINT16                          uhwToolId;                                  /* tools id */
    VOS_UINT16                          uhwReserved;                                /* reserved  */
    UPHY_TOOL_DCOFFSET_ENUM_UINT16      enUpdateType;
    VOS_UINT16                          uhwFreqInfo;
    VOS_UINT16                          uhwGain;
    VOS_INT16                           shwRemainI;
    VOS_INT16                           shwRemainQ;

    VOS_INT16                           shwInitDcoci;                           /* ��ʼֵ,RFIC����ֵΪ0x80��Ӧ��I·DCֵ */
    VOS_INT16                           shwInitDcocq;                           /* ��ʼֵ,RFIC����ֵΪ0x80��Ӧ��Q·DCֵ */
    VOS_INT16                           shwRfDci;                               /* У׼��,RFIC I·DC����ֵ */
    VOS_INT16                           shwRfDcq;                               /* У׼��,RFIC Q·DC����ֵ */
    VOS_INT16                           shwRemainDcoci;                         /* У׼��,I·����DCֵ */
    VOS_INT16                           shwRemainDcocq;                         /* У׼��,Q·����DCֵ */
}GPHY_TOOL_DC_OFFSET_REPORT_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SINGLE_XO_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʱ���µ�ǰppm��scpll����ֵ���¶�ֵ��AFCֵ
*****************************************************************************/
typedef struct
{
    VOS_INT32                           swPpmValue;                             /* ppm */
    VOS_UINT32                          uwPllFracValue;                         /* Scpll С�����ֵ���ֵ */
    VOS_UINT32                          uwPllInterValue;                        /* Scpll �������ֵ���ֵ */
    VOS_UINT32                          uwAfcValue;                             /* AFC */
    VOS_INT16                           shwTemperatureValue;                    /* �¶� */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_SINGLE_XO_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_FE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǰ����Ϣ
*****************************************************************************/
typedef struct
{

    /* SSI_EN����/RSSI/AGC��λ/DCOFFSET/AFC/BLOCK��NOBLOCK״̬���߿���/ABB�߿�/TRCV_ON״̬/��˫����״̬  */
    WPHY_TOOL_SINGLE_XO_INFO_STRU       stSingleXoInfo;                         /* ��ʱ���µ�ǰppm��scpll����ֵ���¶�ֵ��AFCֵ */
    VOS_UINT32                          uwFeRssi;                               /* RSSI 1414 */
    VOS_UINT32                          uwWagcSwitch;                           /* WAGC_SWITCH 1400 */
    VOS_UINT32                          uwIntrasys_valid;                       /* BBPCOMM_W_INTRASYS_VALID_ADDR */
    VOS_UINT32                          uwIntMaskLteRcvW;                       /* BBPCOMM_INT_MASK_LTE_RCV_W_ADDR */
    VOS_UINT32                          uwRfPllStatus;                          /* rfic������ʧ��״̬ */
    VOS_UINT32                          uwTcvrOnRx[4];                          /* TRANSVER ON */
    VOS_UINT32                          uwTcvrOnTx[2];                          /* TRANSVER ON */
    VOS_UINT32                          uwChnMasterModeRx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnMasterModeTx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnSlaveMode[4];                      /* Channel slave mode */
} WPHY_TOOL_FE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_LOWPOWER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �͹��������Ϣ
*****************************************************************************/
typedef struct
{
    /* RF/PA/BBP/ABB���µ�״̬����˯ԭ��  */
    VOS_UINT16                          uhwGuBbpTopMemOffFlg;                   /* GuBbp MEM�Ƿ��µ��ж� */
    VOS_UINT16                          uhwGuBbpTopMemStatus;                   /* �洢��ǰ���ϵ�״̬ */
    VOS_UINT32                          uwGuBbpLPPurposeBitmap;                 /* TOP1B2B���µ����Ŀ��,����ΪTURBO����DPA */
    VOS_UINT16                          uhwBbpMasterOffFlg;                     /* BBP MASTER�Ƿ��µ��ж� */
    VOS_UINT16                          uhwBbpMasterStatus;                     /* �洢��ǰBBP MASTER���ϵ�״̬ */
    VOS_INT16                           shwAnt2CtrlFlag;                        /* �ּ����� */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_LOWPOWER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ྶ������Ԫ1�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwEn;                                   /* ��Ԫ1ʹ����Ϣ 0xFD902020 */
    VOS_UINT32                          uwMode;                                 /* ��Ԫ1ģʽ 0xFD902024 */
    VOS_UINT32                          uwScram;                                /* ���� 0xFD902028 */
    VOS_UINT32                          uwCpichSync;                            /* ֡ͷ��Ϣ 0xFD90202C */
    VOS_UINT32                          uwWinOffset;                            /* ��λ�� 0xFD902030 */
} WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_FINGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ྶ���������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFingerEnergy;                           /* ������ */
    VOS_UINT32                          uwFingerPos;                              /* ����λ */
} WPHY_TOOL_FINGER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_FINGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ԫ0 1 2�� F0��ǿ����Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astFingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
} WPHY_TOOL_MP_FINGER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TWO_ANT_MP_FINGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫���� ��Ԫ0 1 2�� F0��ǿ����Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astAnt1FingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
    WPHY_TOOL_FINGER_INFO_STRU          astAnt2FingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
} WPHY_TOOL_TWO_ANT_MP_FINGER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DEMOD_FINGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astDemodFingerInfo[WPHY_MNTN_DEMOD_FINGER_MAX_NUM];
} WPHY_TOOL_DEMOD_FINGER_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PRI_WIN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С����ͷβ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwPriWinTop;                            /* ��ͷ��Ϣ 0xFD9040C0 */
    VOS_UINT32                          uwPriWinEnd;                            /* ��β��Ϣ 0xFD9040C4 */
} WPHY_TOOL_PRI_WIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SOFT_WIN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ͷβ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSoftWinTop;                           /* ��ͷ��Ϣ 0xFD9040C8 */
    VOS_UINT32                          uwSoftWinEnd;                           /* ��β��Ϣ 0xFD9040CC */
} WPHY_TOOL_SOFT_WIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RL_SCRAM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��·�������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRlScram[WPHY_MNTN_RL_SCRAM_MAX_NUM];
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_RL_SCRAM_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_MEASURE_CTRL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������״̬
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIntraMeasureStatus;                           /*��Ƶ����״̬*/
    VOS_UINT16                          uhwInterMeasureStatus;                           /*��Ƶ����״̬  */
    VOS_UINT16                          uhwInterRATMeasureStatus;                        /*��ϵͳ����״̬*/
    VOS_UINT16                          uhwInterRATBSICStatus;                           /*��ϵͳBSIC��֤״̬*/
    #if FEATURE_LTE                                                                      /* _H2ASN_Skip */
    VOS_UINT16                          uhwInterRATLteMeasureStatus;                     /*��ϵͳLTE����״̬*/
    #endif /* FEATURE_LTE */                                                             /* _H2ASN_Skip */
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_MEASURE_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CS_CTRL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С����������״̬
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIntraStatusFlg;                      /* ���ڱ�Ƶ����״̬��־��Ϊ�˷�ֹ��������STEP1, ����ֹ����ģ�齫Ƶ���е����Ƶ��  */
    VOS_UINT16                          uhwInterStatusFlg;                      /* ������Ƶ����״̬��־, Ϊ�˷�ֹ��������STEP1, ����ֹ����ģ�齫Ƶ���е����Ƶ��  */
}WPHY_TOOL_CS_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_SYS_TIME_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ϵͳ��ʱ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSysTime;                              /* ϵͳ��ʱ */
    VOS_UINT32                          uwCpichPathPos;                         /* ����С��CPICH���羶�ھ���ʱ���ϵ�λ�� */
    VOS_UINT32                          uwDpchPathPos;                          /* ����С��SCCPCH/DPCH���羶�ھ���ʱ���ϵ�λ�� */
}WPHY_TOOL_SYS_TIME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_ERROR_CODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwErrorBlocks;                          /* �����  */
    VOS_UINT32                          uwTotalBlocks;                          /* �ܿ��� */
}WPHY_TOOL_ERROR_CODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_R99_BLER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : R99�����ŵ�����ͳ��
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_ERROR_CODE_INFO_STRU      astBlerInfo[WPHY_MNTN_BLER_RPT_MAX_NUM];
}WPHY_TOOL_R99_BLER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA��������ͳ��
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_ERROR_CODE_INFO_STRU      astErrorCode[WPHY_MNTN_DPA_ERROR_CODE_RPT_MAX_NUM];
}WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA ����������Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astEqFingerInfo[WPHY_MNTN_EQ_FINGER_RPT_MAX_NUM];
}WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RA_STATUS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������״̬��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAccessStatus;
    VOS_UINT16                          uhwAccessProcess;                       /*��������ϱ�״̬*/
}WPHY_TOOL_RA_STATUS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_PI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PI��ά�ɲ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfn;                                 /* PI SFNֵ */
    VOS_UINT16                          uhwSlot;                                /* PI SLOTֵ */
    VOS_UINT16                          uhwChip;                                /* PI CHIPֵ */
    VOS_UINT16                          uhwPiAckNum;                            /* �⵽PIΪACK�ĸ��� */
    VOS_UINT16                          uhwPiTotalNum;                          /* �⵽PI�ܸ��� */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_PI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TX_POW_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���з��书����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxAvrgPwr;
    VOS_INT16                           shwTxMaxPwr;
    VOS_INT16                           shwTxMinPwr;
    VOS_INT16                           shwFilterDpcchPwr;
    VOS_INT16                           shwAllowUlMaxPower;
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_TX_POW_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TPC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ǰ֡TPCͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDlTpcS0To7;
    VOS_UINT32                          uwDlTpcS8To15;
    VOS_UINT32                          uwUlTpc;
}WPHY_TOOL_TPC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_GAIN_FACTOR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ŵ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBc;
    VOS_UINT16                          uhwBd;
    VOS_UINT16                          uhwBhs;
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_GAIN_FACTOR_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDlGapPara;
    VOS_UINT32                          uwUlGapPara;
}WPHY_TOOL_CM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TIME_MEA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ�������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfncfnMeasFlag;
    VOS_INT16                           shwScramCodeNum;
}WPHY_TOOL_TIME_MEA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_COMM_BUSINESS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY��״̬������ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_TIMING_INFO_STRU          stTimingInfo;                           /* ��ʱ�ϱ���Ϣ(����Я��SFN CFN SLOT SLICE��Ϣ) */
    VOS_UINT16                          uhwCurrentFreq;                         /* ��ǰ��С��Ƶ�� */
    VOS_UINT16                          uhwSysSramcode;                         /* ��ǰ��С������ */
    WPHY_TOOL_RL_SCRAM_INFO_STRU        stRlScramInfo;                          /* ��·0��6������� */
    WPHY_TOOL_DEMOD_FINGER_INFO_STRU    stDemodFingerInfo;                      /* ������Ч�����������λ�� */
    WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU stUnit1Info;                            /* �ྶ������Ԫ1�����Ϣ */
    WPHY_TOOL_MP_FINGER_INFO_STRU       stMpFingerInfo;                         /* ��Ԫ0,1,2 f0�ྶ��������λ��ͨ���ྶ�жϻ�ȡ��������� */
    WPHY_TOOL_PRI_WIN_INFO_STRU         stPriWinInfo;                           /* ��С����ͷβ */
    WPHY_TOOL_MEASURE_CTRL_INFO_STRU    stMeasureCtrlInfo;                      /* �����������״̬ */
    WPHY_TOOL_CS_CTRL_INFO_STRU         stCsCtrlInfo;                           /* С����������״̬ */
    WPHY_TOOL_R99_BLER_INFO_STRU        stR99BlerInfo;                          /* �����ŵ�����ͳ�� */
    VOS_UINT32                          uwDemEn;                                /* 0-15bitΪ����ŵ�ʹ�ܣ�16bitΪ�����ŵ�ʹ�� */
}WPHY_TOOL_COMM_BUSINESS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_IDLE_MNTN_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IDLE̬��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usToolsId;                              /* �����ֶ� */

    WPHY_TOOL_FE_INFO_STRU              stFeInfo;                               /* ǰ����Ϣ */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU   stCommBusinessInfo;                     /* ����ҵ����Ϣ */
    WPHY_TOOL_LOWPOWER_INFO_STRU        stLowPowerInfo;                         /* �͹������ */
    WPHY_TOOL_PI_INFO_STRU              stPiInfo;
}WPHY_TOOL_IDLE_MNTN_RPT_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_FACH_MNTN_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FACH̬��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usToolsId;                              /* �����ֶ� */

    WPHY_TOOL_FE_INFO_STRU              stFeInfo;                               /* ǰ����Ϣ */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU   stCommBusinessInfo;                     /* ����ҵ����Ϣ */
    WPHY_TOOL_RA_STATUS_INFO_STRU       stRaStatus;
    WPHY_TOOL_SYS_TIME_INFO_STRU        stSysTimeInfo;                          /* ϵͳ��ʱ�����羶��Ϣ */
    VOS_UINT32                          uwMaxAndMinTxPow;                       /* �����С����ֵ 0xFD90C0A4*/
    VOS_UINT32                          uwDpchSccpchDataPow;                    /* DPCH/SCCPCH�ŵ���������ֵ */
    VOS_UINT32                          uwPaStatus;                             /* PA���µ�״̬ */
}WPHY_TOOL_FACH_MNTN_RPT_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DCH_MNTN_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCH̬��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16       enMsgId;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usToolsId;                          /* �����ֶ� */

    WPHY_TOOL_FE_INFO_STRU                  stFeInfo;                           /* ǰ����Ϣ */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU       stCommBusinessInfo;                 /* ����ҵ����Ϣ */
    WPHY_TOOL_SOFT_WIN_INFO_STRU            stSoftWinInfo;
    WPHY_TOOL_TX_POW_INFO_STRU              stTxPow;                            /* ���з��书�� */
    WPHY_TOOL_TPC_INFO_STRU                 stTpcInfo;                          /* ��ǰ֡TPCͳ��ֵ */
    WPHY_TOOL_TWO_ANT_MP_FINGER_INFO_STRU   stTwoAntMpFingerInfo;
    WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU      stDpaErrorCode;                     /* DPA��������ͳ�� */
    WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU       stDpaEqFinger;                      /* ����������Ϣ */
    WPHY_TOOL_GAIN_FACTOR_STRU              stGainFactor;                       /* ���ŵ��������� */
    WPHY_TOOL_SYS_TIME_INFO_STRU            stSysTimeInfo;                      /* ϵͳ��ʱ�����羶��Ϣ */
    WPHY_TOOL_CM_INFO_STRU                  stCmInfo;                           /* ѹģ��� */
    WPHY_TOOL_TIME_MEA_INFO_STRU            stTimeMeaInfo;                      /* ʱ�������� */
    VOS_UINT32                              uwSyncInd;                          /* ��ǰ֡ͬʧ��״̬ */
    VOS_INT16                               shwSirTarget;                       /* �⻷����ֵ */
    VOS_UINT16                              uhwOlpcCtrlMode;                    /* �⻷���ؿ���ģʽBLER����BER */
    VOS_UINT32                              uwDpchSccpchDataPow;                /* DPCH/SCCPCH�ŵ���������ֵ */
    VOS_UINT32                              uwBerError;                         /* BER����ͳ�� */
    VOS_UINT32                              uwMaxAndMinTxPow;                   /* �����С����ֵ 0xFD90C0A4*/
    VOS_UINT32                              uwPcUlChanEn;                       /* bit�ɵ͵��߷ֱ��ʾ����E-DCH��DCH��RACH��HSUPA������ʹ����Ϣ */
    VOS_UINT32                              uwPaStatus;                         /* PA���µ�״̬ */
}WPHY_TOOL_DCH_MNTN_RPT_STRU;

/*****************************************************************************
 �ṹ��    : UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU
 �ṹ˵��  : TAS_STATUS report���ܴ򿪺͹ر�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT32                                  uwTasCtrl0;                     /* ������ */
    VOS_UINT32                                  uwTasCtrl1;
    VOS_UINT32                                  uwTasCtrl2;
    VOS_UINT32                                  uwTasCtrl3;
}UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU
 �ṹ˵��  : TAS_STATUS report �ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  uhwToolId;                      /* �����ֶ� */
    VOS_UINT16                                  uhwRatMode;                     /* MODEM MODE */
    VOS_UINT16                                  uhwDpdtState;                   /* dpdt״̬ */
    VOS_INT16                                   shwAntValueMain;                /* �������� */
    VOS_INT16                                   shwSwitchDelta;                 /* �����Ĳ� */
    VOS_UINT16                                  uhwCdmaCtrlFlag;                /* cdma��ұ�־ */
    VOS_UINT16                                  uhwReserve;
}WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU
 �ṹ˵��  : TAS_STATUS report �ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    VOS_UINT16                                  uhwRatMode;                     /* MODEM MODE */
    VOS_UINT16                                  uhwDpdtState;                   /* dpdt״̬ */
    VOS_INT16                                   shwAntValueMain;                /* �������� */
    VOS_INT16                                   shwSwitchDelta;                 /* �����Ĳ� */
    VOS_UINT16                                  uhwCdmaCtrlFlag;                /* cdma��ұ�־ */
    VOS_UINT16                                  uhwReserve;
}GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU;
/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_PCCPCH_SCHL_INFO_STRU
 �ṹ˵��  : ���õ�ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCurrentQueueType;             /* ��ǰ�����Ƿ�Ϊ�㲥������,1:�������ѡ��㲥����;0:�������ѡ��A������� */
    VOS_UINT16                                  uhwCurrentTaskFreqIndex;         /* ��ǰ���������ز� */
    VOS_UINT16                                  uhwQueueIndex;                   /* ��ǰ�����Ӧ������е�����*/
    VOS_UINT16                                  uhwBand;                        /* Ƶ�� */
    VOS_UINT16                                  uhwFreq;                        /* Ƶ�� */
    VOS_UINT16                                  uhwScramCode;                   /* ���� */
    VOS_UINT16                                  uhwTDIndicator;                  /* �㲥����ķּ����� */
    VOS_UINT16                                  uhwPccpchTaskType;               /* �㲥�������� */
    VOS_UINT16                                  uhwPccpchTaskStatus;             /* �㲥����״̬ */
    VOS_UINT16                                  uhwSchdlPriority;                /* �������ȼ� */
}WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU
 �ṹ˵��  : ����LTE������ǵ�ָʾ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* Pcpch����ʱ�� */
    WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU        stCfgInfo;                      /* Pcccpch������Ϣ */
}WPHY_TOOL_RAKE_PCCPCH_SCHDL_IND_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU
 �ṹ˵��  : ���õ�ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                   uhwBand;                       /* Ƶ�� */
    VOS_UINT16                                   uhwFreq;                       /* Ƶ�� */
    VOS_UINT16                                   uhwScramCode;                  /* ���� */
    VOS_UINT16                                   uhwTDIndicator;                 /* �㲥����ķּ����� */
    VOS_UINT16                                   uhwPccpchTaskType;              /* �㲥�������� */
    VOS_UINT16                                   uhwPccpchTaskStatus;            /* �㲥����״̬ */
    VOS_UINT16                                   uhwSchdlPriority;               /* �������ȼ� */
    VOS_UINT16                                   uhwRsv;
}WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_BCCH_QUEUE_IND_STRU
 �ṹ˵��  : BCH�㲥������Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* Pcpch����ʱ�� */
    WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU         astQueueInfo[WPHY_MNTN_BCCH_QUEUE_LENGTH];                      /* BCCH������Ϣ */
}WPHY_TOOL_RAKE_BCCH_QUEUE_IND_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU
 �ṹ˵��  : ���õ�ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                   uhwBand;                       /* Ƶ�� */
    VOS_UINT16                                   uhwFreq;                       /* Ƶ�� */
    VOS_UINT16                                   uhwScramCode;                  /* ���� */
    VOS_UINT16                                   uhwTDIndicator;                /* �㲥����ķּ����� */
    VOS_UINT16                                   uhwPccpchTaskType;             /* �㲥�������� */
    VOS_UINT16                                   uhwPccpchTaskStatus;           /* �㲥����״̬ */
    VOS_UINT16                                   uhwSchdlPriority;              /* �������ȼ� */
    VOS_UINT16                                   uhwRsv;
}WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU
 �ṹ˵��  : ADEMOD������Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* ADEMOD����ʱ�� */
    WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU       astQueueInfo[WPHY_MNTN_ADMOD_QUEUE_LENGTH];                      /* BCCH������Ϣ */
}WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU;
/*****************************************************************************
  7 UNION����
*****************************************************************************/
/*****************************************************************************
 ��������   : WPHY_TOOL_MNTN_RPT_UNION
 Э����   :
 ASN.1����  :
 ������˵�� : WPHY��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef union
{
    WPHY_TOOL_IDLE_MNTN_RPT_STRU        stIdleMntnRpt;                          /* IDLE̬��ά�ɲ���Ϣ�ϱ� */
    WPHY_TOOL_FACH_MNTN_RPT_STRU        stFachMntnRpt;                          /* FACH̬��ά�ɲ���Ϣ�ϱ� */
    WPHY_TOOL_DCH_MNTN_RPT_STRU         stDchMntnRpt;                           /* DCH̬��ά�ɲ���Ϣ�ϱ� */
}WPHY_TOOL_MNTN_RPT_UNION;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU
 �ṹ˵��  : �ϲ���ľ���ģ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwStartCfn;
    VOS_UINT16                          auhwPattBitMap[WPHY_MNTN_CPC_DRX_PATTERN_FRAME_NUM];        /* �ӵ͵��߹�15λ��Ч��ÿ��BIT��ʾ��Ӧʱ϶�Ĳ����Ǵ�(ֵΪ1)���ǹر�(ֵΪ0) */

}WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-DPCCH�ŵ�CQI�ϱ�DRX���ƾ�̬������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwNpre[WPHY_MNTN_HSUPA_OM_CARERIER_NUM];          /* ��ǰ�жϵ���֡�� */

} WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DTX_E_DCH_TTI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : edch dtx����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usUeDtxCyc1;                                  /*  Units of subframes*/
    VOS_UINT16                  usUeDtxCyc2;                                  /*  Units of subframes*/
    VOS_UINT16                  usMacDtxCyc;                                  /*  Units of subframes*/
    VOS_UINT16                  usReserved;
} WPHY_TOOL_DTX_E_DCH_TTI_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-SCCH��HS_PDSCH�ŵ����տ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwHsscchSchedSlot;                 /* HS-SCCH��HS_PDSCH�ŵ���������ʱ϶ */
    VOS_UINT16                                      uhwHsscchEquaRfSlotNum;             /* ����򿪺�RF�򿪵ĳ���ʱ�䣬��ʱ϶Ϊ��λ*/
    VOS_UINT16                                      uhwHsscchInactiveEquaRfSlotCnt;     /* ����������Чʱ������Inactivity_Threshold_for_UE_DRX_cycle�ļ�����*/
    VOS_UINT16                                      uhwHsscchInactiveEquaRfSlotNum;     /* ����������Чʱ������Inactivity_Threshold_for_UE_DRX_cycle������*/
} WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-SCCH��HS_PDSCH�ŵ�ACK���Ϳ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPost;                                /* ����ACKʱ,������Ҫ����POST*/
    VOS_UINT16                          uhwRfSlotNum;                           /* HSPDSCH��ѯ������ʱ����ACK����֮�䣬RF�򿪵ĳ���ʱ�䣬��ʱ϶Ϊ��λ */
} WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-DPCCH�ŵ�CQI�ϱ�DRX������Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enCqiSchedFlag;                     /* TRUE:��ҪCQI DRX���Ƶ���,������Ҫ */
    WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM_UINT16      enCqiDtxPri;                        /* �ۺϿ���BBP�����ά���ó���CQI���ȼ� */
    WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU          stCqiStaticNpreInfo;                /* HS-DPCCH�ŵ�CQI�ϱ�DRX���ƾ�̬������Ϣ��ǰ�жϵ���֡�� */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCqiEquaPattInfo[WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM];           /* CQI DRX���ȿ��Ƶľ���PATTERN��Ϣ */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCqiRfPattern[WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM];         /* RF PATTERN */
} WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC DRX info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16  enCpcEquaWorkState;                 /* ��ǰ���⹤��״̬ */
    VOS_UINT16                                      uhwReserve;
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stCpcEquaCombPatt;                  /* �ϲ���ľ���ģ�� */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCpcEquaPattInfo[WPHY_MNTN_CPC_DRX_EQUA_CTRL_TYPE_NUM];       /* ����PATTERN��Ϣ */
} WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_DRX_RF_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC DRX info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16    enRfWorkState;                /* ��ǰRF����״̬ */
    VOS_UINT16                                      uhwReserve;
    VOS_UINT32                                      uwPhySubTaskStaBitMap;              /* Ӱ��RF��������״̬bitmap */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astRfPattInfo[WPHY_MNTN_CPC_DRX_RF_CTRL_TYPE_NUM];                     /* RF PATTERN��Ϣ */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stCombRfPatt;                 /* �ϲ����RFģ�� */
} WPHY_TOOL_CPC_DRX_RF_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DCH_MNTN_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCH̬��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                          /* �����ֶ� */
    WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM_UINT16  enUlDpcchPattCycleState;        /* �ۺ������ز���״̬��ĳ���cycle״̬����󼯺� */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enAgchRgchSchedFlag;                /* �Ƿ����AGCH/RGCH���ȱ�־, TRUE:Ҫ, FALSE:��Ҫ */
    WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU                stEquaCtrl;                         /* ����ģ�� */
    WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU                 stCqiDrxCtrl;                       /* CQI DRX���ȿ��� */
    WPHY_TOOL_CPC_DRX_RF_CTRL_STRU                  stRfCtrl;                           /* RFģ�� */
    WPHY_TOOL_DTX_E_DCH_TTI_STRU                    stDtxEdchTti;                       /* edch dtx���� */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stUlDpcchC1RfPatt;                  /* UL Dpcch cycle1 RF PATTERN */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stUlDpcchC2RfPatt;                  /* UL Dpcch cycle2 RF PATTERN */
    WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU          stHsscchDrxCtrl;                    /* HsscchDrx���ƽṹ*/
    WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU         stHsdpcchAckCtrl;                   /* HsscchAck���ƽṹ*/
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astDrxEdchCtrlRfPatt[WPHY_MNTN_HSUPA_OM_CARERIER_NUM];  /* EDCH���� һ���ز��ϵ� RF PATTERN�������ز���pattern�ֱ�ˢ�� */

}WPHY_TOOL_CPC_MNTN_RPT_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_IC_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С����Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwScramCodeNum;            /* ���� */
    VOS_UINT16                                      uhwFreqInfo;                /* Ƶ�� */
}WPHY_TOOL_IC_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_IC_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ز���ICС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwCellNum;                                     /* С������ */
    VOS_UINT16                                      uhwReserved;                                    /* ����λ */
    WPHY_TOOL_IC_CELL_INFO_STRU                     astIcCellInfo[WPHY_MNTN_IC_MAX_CELL_NUM];       /* ԭ������ */
}WPHY_TOOL_IC_CELL_LIST_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_IC_CELL_REPORT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ICС����Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                  /* �����ֶ� */
    WPHY_TOOL_IC_CELL_LIST_STRU                     astIcCellList[WPHY_MNTN_MAX_CARRIER_NUM];    /* ԭ������ */
}WPHY_TOOL_IC_CELL_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_IC_CELL_REPORT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ز���ICС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRptPeriod;
}WPHY_TOOL_IC_CELL_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_UL_DTX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTX��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwUlDtxStatus;             /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwMainCarrierEnable;       /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwSecondCarrierEnable;     /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwMainCarrierActive;       /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierActive;     /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierPattern;      /* ԭ������ */
    VOS_UINT16                                      uhwSecondCarrierPattern;    /* ԭ������ */
    VOS_UINT16                                      uhwCQIDtxPriority;          /* ԭ������,0--low 1--high */
    VOS_UINT16                                      uhwMainCarrierMacDtx;       /* ԭ������,0--continue 1--MAC DTX */
    VOS_UINT16                                      uhwSecondCarrierMacDtx;     /* ԭ������,0--continue 1--MAC DTX */
}WPHY_TOOL_UL_DTX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DL_DRX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DRX��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwDrxActiveStatus;         /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwReserved;                /* ����Ϊ */
}WPHY_TOOL_DL_DRX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CPC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwEnableStatus;            /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwActiveStatus;            /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* ԭ������,0--Inactive 1--active */
}WPHY_TOOL_CPC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RTT״̬�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                  /* �����ֶ� */
    WPHY_TOOL_UL_DTX_INFO_STRU                      stUlDtxInfo;                /* ԭ������ */
    WPHY_TOOL_DL_DRX_INFO_STRU                      stDlDRxInfo;                /* ԭ������ */
    WPHY_TOOL_CPC_INFO_STRU                         stHsScchLessInfo;           /* ԭ������ */
}WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ز���ICС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRptPeriod;
}WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DPA_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA��Ϣ
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                  /* �����ֶ� */
    VOS_UINT16                                      uhwEnableStatus;            /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwActiveStatus;            /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* ԭ������,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* ԭ������,0--Inactive 1--active */
}WPHY_TOOL_DPA_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_DPA_INFO_REPORT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA �ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
}WPHY_TOOL_DPA_INFO_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_P_VALUE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Pֵ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      auwPValueTotalCnt[WPHY_MNTN_P_VALUE_NUM];   /* ԭ������,0--disable 1--enable */
}WPHY_TOOL_P_VALUE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSSCCH_DECODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-SCCH������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwSubFrameNum;              /* ԭ������,0--disable 1--enable */
    VOS_UINT32                                      uwHsScchAttempt;            /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwHsScchSucc;               /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwHsScchSuccRate;           /* ԭ������,0--Inactive 1--active */
    WPHY_TOOL_P_VALUE_INFO_STRU                     stPValueInfo;
}WPHY_TOOL_HSSCCH_DECODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-SCCH������Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_HSSCCH_DECODE_INFO_STRU               astHsScchDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM];    /* ԭ������ */
}WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSSCCH�����ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
}WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSDSCH_TBS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-DSCH������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwQpskNum;                  /* ԭ������,0--disable 1--enable */
    VOS_UINT32                                      uw16QamNum;                 /* ԭ������,0--disable 1--enable */
    VOS_UINT32                                      uw64QamNum;                 /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwSupport64QamFlag;         /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwSBSub;                    /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwSBPlus;                   /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwFirstSuccNum;             /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwSecondSuccNum;            /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwThirdSuccNum;             /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwFourthSuccNum;            /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwFifthSuccNum;             /* ԭ������,0--Inactive 1--active */
    VOS_UINT32                                      uwSixthSuccNum;             /* ԭ������,0--Inactive 1--active */
}WPHY_TOOL_HSDSCH_TBS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-DSCH������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwTbsLowThredhold;         /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwTbsHighThredhold;        /* ԭ������,0--disable 1--enable */
}WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSDSCH_DECODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS-DSCH������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwRegionNum;                                   /* ԭ������,0--disable 1--enable */
    VOS_UINT16                                      uhwReserved;                                    /* ԭ������,0--disable 1--enable */
    WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU              astTbsThredholdInfo[WPHY_MNTN_MAX_REGION_NUM];  /* ԭ������,0--Inactive 1--active */
    WPHY_TOOL_HSDSCH_TBS_INFO_STRU                  astTbsInfo[WPHY_MNTN_MAX_REGION_NUM];           /* ԭ������,0--Inactive 1--active */
}WPHY_TOOL_HSDSCH_DECODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDSCH�����ϱ�����
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                                      /* �����ֶ� */
    WPHY_TOOL_HSDSCH_DECODE_INFO_STRU               astHsDschDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM]; /* ԭ������ */
}WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDSCH�����ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usToolsId;                      /* �����ֶ� */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
    VOS_UINT16                                  uhwReserved;
    VOS_UINT16                                  uhwRegionNum;                    /* ����Ϊ0-9��������ausThredhold�е���Ŀƥ�� */
    VOS_UINT16                                  auhwThredhold[WPHY_MNTN_MAX_REGION_NUM];
}WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU;
/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU
 �ṹ˵��  : W RXУ׼�켣��ӡ, һ����������Ϊһ����ӡ��Ԫ
*****************************************************************************/
typedef struct
{
    /* ���� */
    VOS_UINT16                          uhwRxConfigTimeSfn;
    VOS_UINT16                          uhwRxConfigTimeSlot;
    VOS_UINT16                          uhwRxConfigTimeChip;
    VOS_UINT16                          uhwBand;
    VOS_UINT16                          uhwFreq;
    VOS_UINT16                          uhwAgcCfg;

    /* ��� */
    VOS_UINT16                          uhwRSSIStartTimeSfn;
    VOS_UINT16                          uhwRSSIStartTimeSlot;
    VOS_UINT16                          uhwRSSIStartTimeChip;
    VOS_UINT16                          uhwRSSIRsltTimeSfn;
    VOS_UINT16                          uhwRSSIRsltTimeSlot;
    VOS_UINT16                          uhwRSSIRsltTimeChip;
    VOS_INT32                           swRssiAnt1Rslt;
    VOS_INT32                           swRssiAnt2Rslt;
    VOS_INT16                           shwRSSIAnt1FirstRslt;
    VOS_INT16                           shwRSSIAnt2FirstRslt;
    VOS_INT16                           shwRSSIAnt1EndRslt;
    VOS_INT16                           shwRSSIAnt2EndRslt;
}WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU;
/*****************************************************************************
 �ṹ��    : WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU
 �ṹ˵��  : W RXУ׼�켣��ӡ, һ����������Ϊһ����ӡ��Ԫ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxValidNum;                          /* ��¼����Ч���� */
    VOS_UINT16                          uhwReserved;                            /* ���� */
    WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU     astWphyRxFastCalMntn[WPHY_CAL_RX_FAST_CAL_MAX_VAILD_NUM];
}WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU;

/*****************************************************************************
 �ṹ��    : WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Rx Fast Cal��ά�ɲ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                      usToolsId;                          /* �����ֶ� */
    WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU            stWphyToolRxFastCal;
}WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU;

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
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

#endif /* end of phytoolinterface.h */
