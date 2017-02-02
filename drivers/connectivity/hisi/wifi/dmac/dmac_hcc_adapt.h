

#ifndef __DMAC_HCC_ADAPT_H__
#define __DMAC_HCC_ADAPT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_HCC_ADAPT_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*Rx适配部分*/
extern frw_event_mem_stru* dmac_tx_process_data_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_user_add_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_user_del_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_event_config_syn_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_event_config_syn_alg_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_mgmt_wmm_update_edca_machw_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_mgmt_tx_event_process_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_scan_proc_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern  frw_event_mem_stru* dmac_dpd_data_processed_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif
extern frw_event_mem_stru*   dmac_cali_hmac2dmac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

extern frw_event_mem_stru* dmac_scan_proc_sched_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

extern frw_event_mem_stru* dmac_asoc_set_reg_event_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_join_set_dtim_reg_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_mgmt_conn_result_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_join_set_reg_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_set_rx_filter_value_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern frw_event_mem_stru* dmac_psm_opmode_notify_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif
extern frw_event_mem_stru* dmac_user_add_notify_alg_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_init_event_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_init_event_create_cfg_vap_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_tx_process_action_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_rx_process_sync_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru *dmac_chan_select_channel_mac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru *dmac_chan_initiate_switch_to_new_channel_rx_adapt(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru *dmac_chan_restart_network_after_switch_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru *dmac_chan_disable_machw_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_psm_reset_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern frw_event_mem_stru* dmac_edca_opt_stat_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif
extern frw_event_mem_stru* dmac_hcc_test_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

/*Tx适配部分*/
extern oal_uint32 dmac_proc_wlan_drx_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_tkip_mic_fail_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_tbtt_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_dfs_radar_detect_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_crx_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_scan_report_scanned_bss_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32 dmac_dpd_data_cali_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32 dmac_scan_proc_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_chan_result_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_init_event_process_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_proc_event_del_ba_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_event_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_alg_ct_result_tx_adapt(frw_event_mem_stru *pst_event_mem);
//extern oal_uint32 dmac_proc_event_log_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_mgmt_rx_delba_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_send_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_switch_to_new_chan_complete_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_dbac_status_notify_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_disasoc_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_cali2hmac_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 dmac_proc_roam_trigger_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_ROAM

extern oal_uint32  dmac_hcc_test_event_rxsub_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_alg_syn_info_adapt(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern oal_uint32 dmac_scan_proc_obss_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
extern oal_uint32  dmac_alg_flow_tx_adapt_tx_adapt(frw_event_mem_stru * pst_event_mem);
#endif

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_main */


