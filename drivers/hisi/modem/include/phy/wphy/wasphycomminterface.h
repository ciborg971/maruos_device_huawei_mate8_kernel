#ifndef __WASPHYCOMMINTERFACE_H__
#define __WASPHYCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "Hi_Config.h"
#include "vos.h"

#pragma pack(4)

#define MULTIBAND_SUPPORT_SWITCH                (1)                /*����Ϊ1��ʾ֧�ֶ�Ƶ��,Ϊ0��ʾ��֧��*/

#define RRC_PHY_MAX_FREQ_NUM                   (20)   /*Ƶ���б�������Ƶ����*/

#define RRC_PHY_MAX_PSCH_FREQ_NUM              (25)    /*�·���WDSP��PSCH��һ��Ƶ���������*/

#define RRC_PHY_MAX_SAMPLE_FREQ_NUM_PER_BAND   (25)    /*һ��band�ڲ��������Ƶ�����*/


#define RRC_PHY_MAX_W_BG_SEARCH_FREQ_NUM        (32)

#define RRC_PHY_MAX_G_BG_SEARCH_FREQ_NUM        (60)

/**************��ȷ������صĺ�***********************/
#define RRC_PHY_MAX_SEG_POS_INFO_NUM           (10)

/*Start of Add by W50455*/
#define PHY_RRC_MAX_REPORT_CANDIDATE_CELL_NUM  (32) /*Cell Search �ϱ�ʱЯ�������С������*/


#define RRC_PHY_MAX_CANDIDATE_CELL_NUM         (64)    /*��С�������·������С������ */

#define  RRC_PHY_BCCH_DATA_SIZE                 (32)


/*****************************************************************************
 ö����    : PHYITF_RSLT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��е���Ч�Ա�ʶ
*****************************************************************************/

enum    PHYITF_RSLT_ENUM
{
    PHYITF_SUCC                         = 0,                                    /* �ɹ� */
    PHYITF_FAIL                         = 1,                                    /* ʧ�� */
    PHYITF_DRX_NOT_SUPPORT              = 2,                                    /* DRX̫�� */

    PHYITF_RSLT_BUTT
};
typedef VOS_UINT16  PHYITF_RSLT_ENUM_UINT16;

enum PHYITF_BG_RESULT_TYPE_ENUM
{
    PHYITF_BG_SUCC              = 0,
    PHYITF_BG_FAIL              = 1,

    PHYITF_BG_BUTT
};
typedef  VOS_UINT16 PHYITF_BG_RESULT_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_ANT_CHANGE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RSSI����ʱ�����Ƿ����л�
*****************************************************************************/

enum    PHYITF_ANT_CHANGE_ENUM
{
    PHYITF_ANT_NOT_CHANGE     = 0,            /* ����û�з����л� */
    PHYITF_ANT_CHANGE         = 1,            /* ���߷����л� */
    PHYITF_ANT_BUTT
};
typedef VOS_UINT32 PHYITF_ANT_CHANGE_ENUM_UINT32;


/*****************************************************************************
 ö����    : RRC_PHY_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC -> PHY �ӿ���ϢID
*****************************************************************************/

enum    RRC_PHY_MSG_ID_ENUM
{
    ID_RRC_PHY_RL_SETUP_REQ                                 = 0x1001,   /* _H2ASN_MsgChoice RRC_PHY_RL_SETUP_REQ_STRU */
    ID_RRC_PHY_RL_MODIFY_REQ                                = 0x1002,   /* _H2ASN_MsgChoice RRC_PHY_RL_MODIFY_REQ_STRU */
    ID_RRC_PHY_RL_RELEASE_REQ                               = 0x1003,   /* _H2ASN_MsgChoice RRC_PHY_RL_RELEASE_REQ_STRU */
    ID_RRC_PHY_POWER_CONTROL_REQ                            = 0x1004,   /* _H2ASN_MsgChoice RRC_PHY_POWER_CONTROL_REQ_STRU */
    ID_RRC_PHY_TRCH_CONFIG_REQ                              = 0x1005,   /* _H2ASN_MsgChoice RRC_PHY_TRCH_CONFIG_REQ_STRU */
    ID_RRC_PHY_TRCH_RELEASE_REQ                             = 0x1006,   /* _H2ASN_MsgChoice RRC_PHY_TRCH_RELEASE_REQ_STRU */

    ID_RRC_PHY_UPLINK_MAXTXPWR_REQ                          = 0x1008,   /* _H2ASN_MsgChoice RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU */
    ID_RRC_PHY_RELALL_PHYCH_REQ                             = 0x1009,   /* _H2ASN_MsgChoice RRC_PHY_RELALL_REQ_STRU */
    ID_RRC_PHY_CAMPED_MAINCELL_REQ                          = 0x100A,   /* _H2ASN_MsgChoice RRC_PHY_CAMPED_MAINCELL_REQ_STRU */

    ID_RRC_PHY_PCCPCH_SETUP_REQ                             = 0x100D,   /* _H2ASN_MsgChoice RRC_PHY_PCCPCH_SETUP_REQ_STRU */
    ID_RRC_PHY_PCCPCH_RELEASE_REQ                           = 0x100E,   /* _H2ASN_MsgChoice RRC_PHY_PCCPCH_RELEASE_REQ_STRU */
    ID_RRC_PHY_CELL_SEARCHING_REQ                           = 0x100F,   /* _H2ASN_MsgChoice RRC_PHY_CELL_SEARCH_REQ_STRU */
    ID_RRC_PHY_MEASUREMENT_IN_IDLE_REQ                      = 0x1010,   /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    ID_RRC_PHY_QUALITY_MEASUREMENT_REQ                      = 0x1011,   /* _H2ASN_MsgChoice RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU */
    ID_RRC_PHY_MEASUREMENT_IN_CONNECTED_REQ                 = 0x1012,   /* _H2ASN_MsgChoice RRC_PHYITF_CONNECT_MEASURE_REQ_STRU */
    ID_RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ       = 0x1013,   /* _H2ASN_MsgChoice RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU */
    ID_RRC_PHY_MACE_CONFIG_REQ                              = 0x1014,   /* _H2ASN_MsgChoice RRC_PHY_MACE_CONFIG_REQ_STRU */


    ID_RRC_PHY_FREQ_MEASURE_REQ                             = 0x1015,   /* _H2ASN_MsgChoice RRC_PHY_FREQ_MEASURE_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_STOP_REQ                           = 0x1017,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_STOP_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_SUSPEND_REQ                        = 0x1018,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_RESUME_REQ                         = 0x1019,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_RESUME_REQ_STRU */
    ID_RRC_PHY_SYSINFO_POS_NOTIFY_REQ                       = 0x101A,   /* _H2ASN_MsgChoice RRC_PHY_SYSINFO_POS_NOTIFY_REQ_STRU */
    ID_RRC_PHY_BSIC_VERIFIED_REQ                            = 0x1020,   /* _H2ASN_MsgChoice RRC_PHY_BSIC_VERIFIED_REQ_STRU */
    ID_RRC_PHY_POSITION_MEASUREMENT_REQ                     = 0x1021,   /* _H2ASN_MsgChoice RRC_PHY_POSITION_MEASUREMENT_REQ_STRU */
    ID_RRC_PHY_MACE_RELEASE_REQ                             = 0x1022,   /* _H2ASN_MsgChoice RRC_PHY_MACE_RELEASE_REQ_STRU */
    ID_RRC_PHY_MAC_E_I_RESET_REQ                            = 0x1023,   /* _H2ASN_MsgChoice RRC_PHY_MAC_E_I_RESET_REQ_STRU */
    ID_RRC_PHY_MACHS_RESET_REQ                              = 0x1024,   /* _H2ASN_MsgChoice RRC_PHY_MACHS_RESET_REQ_STRU*/
    ID_RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ                = 0x1025,   /* _H2ASN_MsgChoice RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU */
    ID_RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ                = 0x1026,   /* _H2ASN_MsgChoice RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU */

    ID_RRC_PHY_CBS_CONFIG_REQ                               = 0x1027,   /* _H2ASN_MsgChoice RRC_PHY_CBS_CONFIG_REQ_STRU */
    ID_RRC_PHY_CPC_CONFIG_REQ                               = 0X1028,   /* _H2ASN_MsgChoice RRC_PHY_CPC_CONFIG_REQ_STRU*/
    ID_RRC_PHY_CPC_DISABLE_REQ                              = 0X1029,   /* _H2ASN_MsgChoice RRC_PHY_CPC_DISABLE_REQ_STRU*/
    ID_RRC_PHY_SCND_RL_SETUP_REQ                            = 0x102A,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_SETUP_REQ_STRU */
    ID_RRC_PHY_SCND_RL_MODIFY_REQ                           = 0x102B,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_MODIFY_REQ_STRU */
    ID_RRC_PHY_SCND_RL_REL_REQ                              = 0x102C,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_REL_REQ_STRU */
    ID_RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ                    = 0x102D,   /* _H2ASN_MsgChoice RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU */

    /* ADD UL_E_L2 */
    ID_RRC_PHY_MACI_CONFIG_REQ                              = 0x102E,   /* _H2ASN_MsgChoice RRC_PHY_MACI_CONFIG_REQ_STRU */
    ID_RRC_PHY_MACI_RELEASE_REQ                             = 0x102F,   /* _H2ASN_MsgChoice RRC_PHY_MACI_RELEASE_REQ_STRU */
    /* END UL_E_L2 */
    ID_RRC_PHY_SET_WORK_MODE_REQ                            = 0x1032,    /* _H2ASN_MsgChoice RRC_PHY_SET_WORK_MODE_REQ_STRU */
    ID_RRC_PHY_SET_RAT_PRI_REQ                              = 0x1033,    /* _H2ASN_MsgChoice RRC_PHY_SET_RAT_PRI_REQ_STRU */

    /* ���ڽ���SIB7�����ӿ�------ start */
    ID_RRC_PHY_PRACH_INIT_TX_POWER_IND                      = 0x1034,   /* _H2ASN_MsgChoice RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU */
    /* ���ڽ���SIB7�����ӿ�------ end */

    ID_RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ                    = 0x1035,   /* _H2ASN_MsgChoice RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU */
    ID_RRC_PHY_CS_PS_IND                                    = 0x1036,   /* _H2ASN_MsgChoice RRC_PHY_CS_PS_IND_STRU */
    ID_RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND                 = 0x1037,   /* _H2ASN_MsgChoice RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU */
    ID_RRC_PHY_SLAVE_MEASURE_REQ                            = 0x1038,   /* _H2ASN_MsgChoice RRC_PHY_SLAVE_MEASURE_REQ_STRU */
    ID_RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND                    = 0x1039,   /* _H2ASN_MsgChoice RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND_STRU */
    ID_RRC_PHY_RTT_TEST_CFG_REQ                             = 0xE001,   /* _H2ASN_MsgChoice RRC_PHY_RTT_TEST_REG_CFG_REQ_STRU */

    ID_PHY_RRC_MEASUREMENT_IN_CONNECTED_CNF                 = 0x0001,   /* _H2ASN_MsgChoice PHY_RRC_CONNECT_MEASURE_CNF_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_CONNECTED_IND                 = 0x0002,   /* _H2ASN_MsgChoice PHY_RRC_CONNECT_MEASURE_IND_STRU */
    ID_PHY_RRC_BSIC_VERIFIED_CNF                            = 0x0003,   /* _H2ASN_MsgChoice PHY_RRC_BSIC_VERIFIED_CNF_STRU */
    ID_PHY_RRC_RL_SETUP_CNF                                 = 0x3201,   /* _H2ASN_MsgChoice PHY_RRC_RL_SETUP_CNF_STRU */
    ID_PHY_RRC_RL_MODIFY_CNF                                = 0x3202,   /* _H2ASN_MsgChoice PHY_RRC_RL_MODIFY_CNF_STRU */
    ID_PHY_RRC_RL_RELEASE_CNF                               = 0x3203,   /* _H2ASN_MsgChoice PHY_RRC_RL_RELEASE_CNF_STRU */
    ID_PHY_RRC_ACTIVATE_IND                                 = 0x3204,   /* _H2ASN_MsgChoice PHY_RRC_ACTIVATE_IND_STRU */
    ID_PHY_RRC_POWER_CONTROL_CNF                            = 0x3205,   /* _H2ASN_MsgChoice PHY_RRC_POWER_CONTROL_CNF_STRU */
    ID_PHY_RRC_TRCH_CONFIG_CNF                              = 0x3206,   /* _H2ASN_MsgChoice PHY_RRC_TRCH_CONFIG_CNF_STRU */
    ID_PHY_RRC_TRCH_RELEASE_CNF                             = 0x3207,   /* _H2ASN_MsgChoice PHY_RRC_TRCH_RELEASE_CNF_STRU */
    ID_PHY_RRC_ERROR_IND                                    = 0x3208,   /* _H2ASN_MsgChoice PHY_RRC_ERROR_IND_STRU */
    ID_PHY_RRC_SYNC_IND                                     = 0x3209,   /* _H2ASN_MsgChoice PHY_RRC_SYNC_IND_STRU */
    ID_PHY_RRC_OUT_OF_SYNC_IND                              = 0x320A,   /* _H2ASN_MsgChoice PHY_RRC_OUT_OF_SYNC_IND_STRU */
    ID_PHY_RRC_RL_FAIL_IND                                  = 0x320B,   /* _H2ASN_MsgChoice PHY_RRC_RL_FAIL_IND_STRU */
    ID_PHY_RRC_RELALL_PHYCH_CNF                             = 0x320C,   /* _H2ASN_MsgChoice PHY_RRC_RELALL_CNF_STRU */
    ID_PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND              = 0x320D,   /* _H2ASN_MsgChoice PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU */
    ID_PHY_RRC_CAMPED_MAINCELL_CNF                          = 0x320E,   /* _H2ASN_MsgChoice PHY_RRC_CAMPED_MAINCELL_CNF_STRU */

    ID_PHY_RRC_MACE_CONFIG_CNF                              = 0x320F,   /* _H2ASN_MsgChoice PHY_RRC_MACE_CONFIG_CNF_STRU */

/*V3 R7_7C1 Start */
    ID_PHY_RRC_MAC_ACTIVATE_IND                             = 0x3210,   /* _H2ASN_MsgChoice PHY_RRC_MAC_ACTIVATE_IND_STRU */
/* V3 R7_7C1 End */

    ID_PHY_RRC_MACE_RELEASE_CNF                             = 0x3211,   /* _H2ASN_MsgChoice PHY_RRC_MACE_RELEASE_CNF_STRU */
    ID_PHY_RRC_MAC_E_I_RESET_CNF                            = 0x3212,   /* _H2ASN_MsgChoice PHY_RRC_MAC_E_I_RESET_CNF_STRU */
    ID_PHY_RRC_UPLINK_MAXTXPWR_CNF                          = 0x3213,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU */
    ID_PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND                 = 0x3214,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU */
    ID_PHY_RRC_MACHS_RESET_CNF                              = 0x3215,   /* _H2ASN_MsgChoice PHY_RRC_MACHS_RESET_CNF_STRU*/
    ID_PHY_RRC_RELALL_PHYCH_ACTIVATE_IND                    = 0x3216,   /* _H2ASN_MsgChoice PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU*/
    ID_PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF                = 0x3217,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU */
    ID_PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF                = 0x3218,   /* _H2ASN_MsgChoice PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU */
    ID_PHY_RRC_CBS_CONFIG_CNF                               = 0x3219,   /* _H2ASN_MsgChoice PHY_RRC_CBS_CONFIG_CNF_STRU */
    ID_PHY_RRC_CPC_CONFIG_CNF                               = 0x321A,   /* _H2ASN_MsgChoice PHY_RRC_CPC_CONFIG_CNF_STRU */
    ID_PHY_RRC_CPC_DISABLE_CNF                              = 0x321B,   /* _H2ASN_MsgChoice PHY_RRC_CPC_DISABLE_CNF_STRU */
    ID_PHY_RRC_SCND_RL_SETUP_CNF                            = 0x321C,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_SETUP_CNF_STRU */
    ID_PHY_RRC_SCND_RL_MODIFY_CNF                           = 0x321D,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_MODIFY_CNF_STRU */
    ID_PHY_RRC_SCND_RL_REL_CNF                              = 0x321E,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_REL_CNF_STRU */
    ID_PHY_RRC_SET_WORK_MODE_CNF                            = 0x321F,   /* _H2ASN_MsgChoice PHY_RRC_SET_WORK_MODE_CNF_STRU */
    ID_PHY_RRC_SET_RAT_PRI_CNF                              = 0x3220,   /* _H2ASN_MsgChoice PHY_RRC_SET_RAT_PRI_CNF_STRU */

    /* ADD UL_E_L2 */
    ID_PHY_RRC_MACI_CONFIG_CNF                              = 0x3221,   /* _H2ASN_MsgChoice PHY_RRC_MACI_CONFIG_CNF_STRU */
    ID_PHY_RRC_MACI_RELEASE_CNF                             = 0x3222,   /* _H2ASN_MsgChoice PHY_RRC_MACI_RELEASE_CNF_STRU */
    /* END UL_E_L2 */
    ID_PHY_RRC_DISABLE_ULDCCH_IND                           = 0x3223,   /* _H2ASN_MsgChoice PHY_RRC_DISABLE_ULDCCH_IND_STRU */
    ID_PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF                    = 0x3224,   /* _H2ASN_MsgChoice PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU */
    ID_PHY_RRC_CELL_SEARCH_IND                              = 0x3301,   /* _H2ASN_MsgChoice PHY_RRC_CELL_SEARCH_IND_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_IDLE_CNF                      = 0x3302,   /* _H2ASN_MsgChoice PHY_RRC_IDLE_MEASURE_CNF_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_IDLE_IND                      = 0x3303,   /* _H2ASN_MsgChoice PHY_RRC_IDLE_MEASURE_IND_STRU */
    ID_PHY_RRC_BG_SEARCH_STOP_CNF                           = 0x3306,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_STOP_CNF_STRU */
    ID_PHY_RRC_BG_SEARCH_SUSPEND_CNF                        = 0x3307,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_PHY_RRC_BG_SEARCH_RESUME_CNF                         = 0x3308,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_RESUME_CNF_STRU */
    ID_PHY_RRC_FREQ_MEASURE_IND                             = 0x3309,   /* _H2ASN_MsgChoice PHY_RRC_FREQ_MEASURE_IND_STRU */
    ID_PHY_RRC_PCCPCH_SETUP_CNF                             = 0x3401,   /* _H2ASN_MsgChoice PHY_RRC_PCCPCH_SETUP_CNF_STRU */
    ID_PHY_RRC_PCCPCH_RELEASE_CNF                           = 0x3402,   /* _H2ASN_MsgChoice PHY_RRC_PCCPCH_RELEASE_CNF_STRU */
    ID_PHY_RRC_BCCHDATA_IND                                 = 0x3403,   /* _H2ASN_MsgChoice PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU */
    ID_PHY_RRC_SYSINFO_POS_NOTIFY_CNF                       = 0x3404,   /* _H2ASN_MsgChoice PHY_RRC_SYSINFO_POS_NOTIFY_CNF_STRU */
    ID_PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF       = 0x3501,   /* _H2ASN_MsgChoice PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU */
    ID_PHY_RRC_QUALITY_MEASUREMENT_CNF                      = 0x3502,   /* _H2ASN_MsgChoice PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU */
    ID_PHY_RRC_QUALITY_MEASUREMENT_IND                      = 0x3503,   /* _H2ASN_MsgChoice PHY_RRC_QUALITY_MEASUREMENT_IND_STRU */
    ID_PHY_RRC_POSITION_MEASUREMENT_CNF                     = 0x3504,   /* _H2ASN_MsgChoice PHY_RRC_POSITION_MEASUREMENT_CNF_STRU*/
    ID_PHY_RRC_POSITION_MEASUREMENT_IND                     = 0x3505,   /* _H2ASN_MsgChoice PHY_RRC_POSITION_MEASUREMENT_IND_STRU*/
    ID_PHY_RRC_UE_INTERNAL_MEASUREMENT_IND                  = 0x3506,   /* _H2ASN_MsgChoice PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU */
    ID_PHY_RRC_BCCH_FAIL_IND                                = 0x3507,   /* _H2ASN_MsgChoice PHY_RRC_BCCH_FAIL_IND_STRU */
    ID_PHY_RRC_WCDMA_CELL_TIMING_IND                        = 0x3509,   /* _H2ASN_MsgChoice PHY_RRC_WCDMA_CELL_TIMING_IND_STRU */
    ID_PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF                    = 0x350A,   /* _H2ASN_MsgChoice PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU */
    ID_PHY_RRC_WCDMA_TIMING_ERROR_IND                       = 0x350B,   /* _H2ASN_MsgChoice PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU */
    ID_PHY_RRC_SLAVE_MEASURE_CNF                            = 0x350C,   /* _H2ASN_MsgChoice PHY_RRC_SLAVE_MEASURE_CNF_STRU */
    ID_PHY_RRC_SLAVE_MEASURE_IND                            = 0x350D,   /* _H2ASN_MsgChoice PHY_RRC_SLAVE_MEASURE_IND_STRU */
    ID_PHY_RRC_AFC_LOCK_INFO_IND                            = 0x350E,   /* _H2ASN_MsgChoice PHY_RRC_AFC_LOCK_IND_STRU */
    ID_PHY_RRC_RADIO_RESOURCE_IND                           = 0x350F,   /* _H2ASN_MsgChoice PHY_RRC_RADIO_RESOURCE_IND_STRU */
    ID_PHY_RRC_RTT_TEST_REG_IND                             = 0xF001,   /* _H2ASN_MsgChoice PHY_RRC_RTT_TEST_REG_IND_STRU */
    ID_RRC_PHY_MSG_BUTT

};
typedef VOS_UINT16 RRC_PHY_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_TX_DIVER_IND_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ּ�ָʾ����
*****************************************************************************/

enum    PHYITF_TX_DIVER_IND_ENUM
{
    PHYITF_TX_DIVER_NO_DIVER                 = 0,       /* û�з��ּ� */
    PHYITF_TX_DIVER_STTD                     = 1,       /* STTD */
    PHYITF_TX_DIVER_CLOSELOOP_TIM_ADJ_SLOT1  = 2,       /* TX Diversity Mode = closed loop mode1, Closed loop timing adjustment mode = 1 */
    PHYITF_TX_DIVER_CLOSELOOP_TIM_ADJ_SLOT2  = 3,       /* TX Diversity Mode = closed loop mode1, Closed loop timing adjustment mode = 2 */
    PHYITF_TX_DIVER_UNKNOWN                  = 0xFF,    /*RRC ��֪�����ּ���ģʽ*/

    PHYITF_TX_DIVER_BUTT

};
typedef VOS_UINT16 PHYITF_TX_DIVER_IND_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ֪ͨDSP ��Ƶ���������ķ�ʽ
*****************************************************************************/

enum    PHYITF_FREQ_SEARCH_TYPE_ENUM
{
    PHYITF_FREQ_SEARCH_TYPE_RSSI               = 0,            /*֪ͨDSP����RSSIֵ����Ƶ���������*/
    PHYITF_FREQ_SEARCH_TYPE_PSCH               = 1,            /*֪ͨDSP����PSCHֵ����Ƶ���������*/
    PHYITF_FREQ_SEARCH_TYPE_FFT                = 2,            /*֪ͨDSP����FFT�㷨����Ƶ���������*/
    PHYITF_FREQ_SEARCH_TYPE_HISTORY_CAND_RSSI  = 3,            /*֪ͨDSP����HISTORY_CANDƵ�㳡��RSSI����Ƶ���������*/
    PHYITF_FREQ_SEARCH_TYPE_HISTORY_CAND_PSCH  = 4,            /*֪ͨDSP����HISTORY_CANDƵ�㳡��PSCH����Ƶ���������*/
    PHYITF_FREQ_SEARCH_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : CSEL ʹ�õ�С��Search����
*****************************************************************************/

enum    PHYITF_CELL_SEARCH_TYPE_ENUM
{
    PHYITF_CELL_SEARCH_NO_CAND_CELL     = 0,            /*������С������*/
    PHYITF_CELL_SEARCH_WITH_CAND_CELL   = 1,            /*������ĺ�ѡС������*/
    PHYITF_CELL_SEARCH_FREQ_BAND        = 2,            /*Ƶ������,ָ��Ҫ������Ƶ�Σ�PHY�Լ���Ƶ����ѡ��Ƶ������*/
    PHYITF_CELL_SEARCH_FREQ_LIST        = 3,            /*��ɢƵ���б�����,ָ��Ҫ��������ɢƵ��,PHY�Լ������б��ڵ�Ƶ������*/

    PHYITF_CELL_SEARCH_TPPE_BUTT

};
typedef VOS_UINT16 PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16;

/* �ӿ��е�BOOLֵ���� */
/*****************************************************************************
 ö����    : PHYITF_BOOL_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��е���Ч�Ա�ʶ
*****************************************************************************/

enum    PHYITF_BOOL_ENUM
{
    PHYITF_INVALID                      = 0,    /*���ڶԽӿ��е�valid��־��λ������Ч��ʹ��1*/
    PHYITF_VALID                        = 1,    /*���ڶԽӿ��е�valid��־��λ������Ч��ʹ��0*/

    PHYITF_BUTT

};
typedef VOS_UINT16  PHYITF_BOOL_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_PCCPCH_PURPOSE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����㲥�ŵ���Ŀ��
*****************************************************************************/

enum    PHYITF_PCCPCH_PURPOSE_ENUM
{
    PHYITF_PCCPCH_PURPOSE_RCV_SIB7      = 0,                                    /* ��SIB7 */
    PHYITF_PCCPCH_PURPOSE_OTHER         = 1,                                    /* ����ԭ�� */

    PHYITF_PCCPCH_PURPOSE_BUTT

};
typedef VOS_UINT16  PHYITF_PCCPCH_PURPOSE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : BCCH FAIL ʧ��ԭ������
*****************************************************************************/

enum    PHYITF_PCCPCH_FAIL_TYPE_ENUM
{
    PHYITF_PCCPCH_FAIL_CRC_ERROR              = 0,                                    /* �㲥���ݴ��� */
    PHYITF_PCCPCH_FAIL_PRIMITIVE_ERROR        = 1,                                    /* �㲥ԭ���쳣 */

    PHYITF_PCCPCH_FAIL_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16;



/*****************************************************************************
 �ṹ��    : PHYITF_FREQ_MEASURE_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ����Ϣ��ָ�����Ƶ�ε�
             ���Ƶ��,���Ƶ�ʣ��շ�Ƶ���Ƶ�κ�
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usLowFreq;                          /* Ƶ�ε����Ƶ�� */
    VOS_UINT16                              usHighFreq;                         /* Ƶ�ε����Ƶ�� */
    VOS_UINT16                              usFreqBandNo;                       /* Ƶ�κ� */
    VOS_UINT16                              usTxRxFreqSeparation;               /* �շ�Ƶ�� */
}PHYITF_FREQ_MEASURE_BAND_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usFreqBandNo;           /*Ƶ�κ�,ȡֵ:1,2,3,4,5,6��8*/
    VOS_UINT16                                  usTxRxFreqSeparation;   /*Ƶ��*/
    VOS_UINT16                                  usDLFreqInfo;
    VOS_UINT16                                  usReserve1;
}PHYITF_FREQ_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_FREQ_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϸɨʱ��ҪЯ����Ƶ���б�
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFreqNum;              /* ��ԭ��ֵΪPSCHʱ����ҪЯ��Ƶ����� */
    VOS_UINT16                                  usReserve1;             /*��ԭ��ֵΪPSCHʱ����ҪЯ��Ƶ���б� */
    PHYITF_FREQ_INFO_STRU                       astFreqList[RRC_PHY_MAX_PSCH_FREQ_NUM];/* Ƶ���б��о����Ƶ����Ϣ*/
}PHYITF_FREQ_LIST_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_FREQ_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�����������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* ������ʶ */
    PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16         enSearchType;           /* ָʾDSP��ͨ��RSSI,PSCH����FFT��Ƶ��������� */
    VOS_UINT16                                  usStepLength;           /* ֪ͨDSP����ȡƵ��Ĳ��������ԭ��ֵ��FFT,�򲽳�Ϊ5M,��Я��Ƶ�����Ϊ25��;���ԭ��ֵΪrssi,�򲽳�Ϊ3M����Я��Ƶ�����Ϊ15��*/
    PHYITF_FREQ_MEASURE_BAND_INFO_STRU          stFreqBandInfo;         /* ��ԭ��ֵΪRSSI����FFTʱ����ҪЯ��band��Ϣ�Լ��������� */
    PHYITF_FREQ_LIST_STRU                       stFreqList;             /* ��ԭ��ֵΪPSCH,HISTORY_CAND_RSSI,HISTORY_CAND_PSCHʱ����ҪЯ����Ҫ��ϸɨ��Ƶ�� */
}RRC_PHY_FREQ_MEASURE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_FREQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�ϱ���Ƶ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usFreq;
    VOS_UINT16                                          usFreqQuality;          /* Ƶ���RSSIֵ����PSCHֵ������RSSI�Ǹ��ģ�DSP�ϱ���RSSIֵ��ƫ��65535�õ��� */
    VOS_UINT16                                          usFreqBandNo;           /*Ƶ�κ�,ȡֵ:1,2,3,4,5,6��8*/
    VOS_UINT16                                          usReserve1;
} PHY_RRC_FREQ_INFO_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_RANKED_FREQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�ϱ����ź����Ƶ���б�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usFreqNum;              /* Ƶ����Ŀ */
    VOS_UINT16                                          usReserve1;
    PHY_RRC_FREQ_INFO_STRU                              astFreqInfo[RRC_PHY_MAX_SAMPLE_FREQ_NUM_PER_BAND];
} PHY_RRC_MEAS_FREQ_INFO_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_FREQ_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�����ָʾ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* ������ʶ */
    PHYITF_ANT_CHANGE_ENUM_UINT32               enAntChgFlg;            /* �����Ƿ������л���RSSI����ʱ��Ч */
    PHYITF_RSLT_ENUM_UINT16                     enResult;               /* ��PI��С������������DSP�Ÿ�ֵ��Ĭ����PHYITF_SUCC */
    PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16         enSearchType;           /* ָʾDSP��ͨ��RSSI,PSCH����FFT��Ƶ��������� */
    PHY_RRC_MEAS_FREQ_INFO_STRU                 stMeasFreqInfo;
}PHY_RRC_FREQ_MEASURE_IND_STRU;




/**************************С��������ص�����**************************************************/
/*****************************************************************************
 �ṹ��    : PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С�������к�С����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;    /* ����С�������� */
    VOS_UINT16                          usReferenceTime;       /* ����С����ʱ����Ϣ */

}PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С������Ƶ����Ϣ��ָ�����Ƶ�ε�
             ���Ƶ�ʺ����Ƶ��
 *****************************************************************************/
typedef struct
{
    VOS_UINT16  usLowFreq;       /* Ƶ�ε����Ƶ�� */
    VOS_UINT16  usHighFreq;      /* Ƶ�ε����Ƶ�� */

}PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU;


typedef struct
{
    VOS_UINT16                              usFreqCnt;                       /* Ƶ���б���Ƶ�����Ŀ,Ϊ0���ʾû�� */
    VOS_UINT16                              usReserve1;
    PHYITF_FREQ_INFO_STRU                   astFreqList[RRC_PHY_MAX_FREQ_NUM];/* Ƶ���б��о����Ƶ����Ϣ*/

}PHYITF_FREQ_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_CELL_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С������������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* ������ʶ */
    PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16         enCellSearchType;       /*ö��ֵ��ȡ��PHYITF_SEARCH_FLAG_ENUM*/  /* ��ʼС���������� */
    VOS_UINT16                                  usFreqInfo;             /* ��ʼС��������Ƶ��,��enCellSearchType = PHYITF_CELL_SEARCH_NO_CAND_CELL��PHYITF_CELL_SEARCH_WITH_CAND_CELLʱ��Ч*/
    VOS_INT16                                   sRSCPThreshold;         /* С������������Ҫ���RSCP������� */
    VOS_UINT16                                  usCandidateCellNum;     /* ����С������Ŀ,��enCellSearchType = PHYITF_CELL_SEARCH_WITH_CAND_CELLʱ��Ч*/
    PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU astCandidateCellInfo[RRC_PHY_MAX_CANDIDATE_CELL_NUM];
    PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU      stFreqBand;             /*��enCellSearchType = PHYITF_CELL_SEARCH_FREQ_BANDʱ��Ч*/
    PHYITF_FREQ_INFO_LIST_STRU                  stFreqList;             /*��enCellSearchType = PHYITF_CELL_SEARCH_FREQ_LISTʱ��Ч*/
    VOS_UINT16                                  usTxRxFreqSeparation;   /*Ϊʵ��Ƶ��ֵFreq��5�Ľ��*/
    VOS_UINT16                                  usFreqBandNo;           /*Ƶ�κ�,ȡֵ:1,2,3,4,5,6*/
    VOS_UINT16                                  usReportCellNumInd;    /*�ϱ�С����Ŀָʾ,1:ֻ�ϱ�һ��С������������.2:Ҫ�ϱ����С���������*/
    PHYITF_BOOL_ENUM_UINT16                     enHoFlg;                /* �л�Ŀ�ĵ�С������ָʾ */
    PHYITF_BOOL_ENUM_UINT16                     enCsDetectFlg;          /* ָ��С������ʱ���Ƿ��������С�� */
    VOS_UINT16                                  usDetectCellNum;        /* �������С���ĸ��� */
}RRC_PHY_CELL_SEARCH_REQ_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_EACH_CELL_SEARCH_RESULT
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С������������ÿ��С��������������ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;         /*С��������*/
    VOS_INT16                           sCpichRscp;                 /* CPICH RSCP����ֵ */
    VOS_INT16                           sCpichEcN0;                 /* CPICH EcN0����ֵ */
    VOS_INT16                           sUtraCarrierRSSI;           /* UtraCarrierRSSI����ֵ */

}PHY_RRC_EACH_CELL_SEARCH_RESULT;


/*****************************************************************************
 �ṹ��    : PHY_RRC_CELL_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С������ָʾ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                              usOPID;                 /* ������ʶ */
    VOS_UINT16                              usFreqInfo;             /* ��ʼС����Ƶ�� */
    VOS_UINT16                              usSerchedCellNum;       /*���ڸ�Ƶ��һ��С�����Ѳ�������usSerchedCellNum = 0*/
    PHY_RRC_EACH_CELL_SEARCH_RESULT         astCellSerchResult[PHY_RRC_MAX_REPORT_CANDIDATE_CELL_NUM]; /* С���������� */
    PHYITF_RSLT_ENUM_UINT16                 enResult;               /* С�������������PI��С������������DSP�Ÿ�ֵ��Ĭ����PHYITF_SUCC */
    VOS_UINT16                              ausReserve1[1];
}PHY_RRC_CELL_SEARCH_IND_STRU;



/*****************************************************************************
 �ṹ��    : RRC_PHY_PCCPCH_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCCPCH �ŵ��ͷ�������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    PHYITF_BOOL_ENUM_UINT16             enBgSearchFlg;          /* �Ƿ񱳾��ѱ�־�������DSP��Ҫ����ȷ���գ�
                                                                    PHYITF_VALID ��ʾ��Ҫ����ȷ��㲥��
                                                                    PHYITF_INVALID����ʾ����Ҫ��ȷ��㲥 */
    VOS_UINT16                          usReserve1;
}RRC_PHY_PCCPCH_RELEASE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_PCCPCH_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCCPCH �ŵ��ͷ�֤ʵ��Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

}PHY_RRC_PCCPCH_RELEASE_CNF_STRU;



/*****************************************************************************
 �ṹ��    : RRC_PHY_PCCPCH_SETUP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCCPCH �ŵ�����������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usFreqInfo;             /* Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/

    VOS_UINT16                          usPriScramCode;         /* С���������� */

    /*Pccpch�ķּ���ʽ: 0�������÷ּ���ʽ��1������STTD�ּ���ʽ,
     0xFF:��һ�ν���Pccpch��RRC��֪��Pccpch�Ƿ�����˷ּ���ʽ,��������Լ����ж�.
     Ϊ�˼���6511�汾,��ֵֻ��ʹ��0,1.
     ����6720�汾����ֵ����ʹ��0,1,0xFF*/
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    PHYITF_BOOL_ENUM_UINT16             enBgSearchFlg;          /* �Ƿ񱳾��ѱ�־�������DSP��Ҫ����ȷ���գ�
                                                                    PHYITF_VALID ��ʾ��Ҫ����ȷ��㲥��
                                                                    PHYITF_INVALID����ʾ����Ҫ��ȷ��㲥 */
    PHYITF_PCCPCH_PURPOSE_ENUM_UINT16   enPccpchPurpose;        /* ���ν�㲥�ǲ���ֻ��SIB7��Ϣ */
    VOS_UINT16                          usReserve1;

}RRC_PHY_PCCPCH_SETUP_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_PCCPCH_SETUP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCCPCH �ŵ�����֤ʵ��Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

}PHY_RRC_PCCPCH_SETUP_CNF_STRU;


typedef struct
{
    VOS_UINT16                      usPos;
    VOS_UINT16                      usRepeat;
} SYSINFO_POS_REPEAT_STRU;

/* CPHY_SYSINFO_POS_NOTIFY_REQԭ������ṹ */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16  enMsgID;                                        /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                  usOpID;
    PHYITF_BOOL_ENUM_UINT16     enRcvAllFlg;                                    /* �Ƿ�ȫ��㲥�ı�� */
    VOS_UINT16                  ausReserve1[2];
    VOS_UINT16                  usSegNum;
    SYSINFO_POS_REPEAT_STRU     astSegList[RRC_PHY_MAX_SEG_POS_INFO_NUM];                                  /*����λ������*/
} RRC_PHY_SYSINFO_POS_NOTIFY_REQ_STRU;

/* CPHY_SYSINFO_POS_NOTIFY_CNFԭ������ṹ */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                      enMsgID;                    /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                                      usOPID;
    PHYITF_RSLT_ENUM_UINT16                         enResult;                   /* �ɹ�����ʧ�ܵı�־ */
    VOS_UINT16                                      usReserve1[1];
} PHY_RRC_SYSINFO_POS_NOTIFY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_BCCH_FAIL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ھ�ȷ��㲥�����У�WDSP��WAS�ϱ��޷����о�ȷ��㲥��
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������ *//*_H2ASN_Skip*/
    PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16 enFailType;         /* �㲥ʧ��ԭ�� */
} PHY_RRC_BCCH_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_BG_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W������W��ʱ��WAS֪ͨWPHYֹͣ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* ������ʶ */
}RRC_PHY_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W������W��ʱ��WAS֪ͨWPHY��ͣ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* ������ʶ */
}RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_BG_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY��RRC_PHY_BG_SEARCH_STOP_REQ��Ϣ����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* ������ʶ */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* ������� */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY��RRC_PHY_BG_SEARCH_SUSPEND_REQ��Ϣ����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* ������ʶ */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* ������� */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_BG_SEARCH_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W������W��ʱ��WAS֪ͨWPHY��ұ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* ������ʶ */
}RRC_PHY_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_BG_SEARCH_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY��RRC_PHY_BG_SEARCH_RESUME_REQ��Ϣ����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* ������ʶ */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* ������� */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_RESUME_CNF_STRU;

/****************PCCPCH ����BCCH�ϵ�����**********************************/
/*****************************************************************************
 �ṹ��    : PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BCCH DATA ָʾ��Ϣ���ݽṹ
             ��PCCPCH ����ϵͳ��Ϣʹ�ô�
             ��Ϣ����

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������ *//*_H2ASN_Skip*/
    VOS_INT16                           sCRCFlg;            /* CRC��� */
    VOS_UINT16                          usServSfn;          /* ��С����sfnֵ*/
    VOS_UINT16                          usReserve;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucBcchData[RRC_PHY_BCCH_DATA_SIZE]; /* һ��TB��BCCH���� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausBcchData[RRC_PHY_BCCH_DATA_SIZE/2]; /* _H2ASN_Skip  һ��TB��BCCH���� */
#endif

} PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU;


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

#endif /* end of RrcPhyInterface.h */

