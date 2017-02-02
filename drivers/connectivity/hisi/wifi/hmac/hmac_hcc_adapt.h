

#ifndef __HMAC_HCC_ADAPT_H__
#define __HMAC_HCC_ADAPT_H__


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
#include "hmac_ext_if.h"
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_HCC_ADAPT_H

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

/*Hcc 事件处理*/
extern oal_uint32 hmac_hcc_rx_event_comm_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_hcc_test_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);


/*Rx适配部分*/
extern frw_event_mem_stru * hmac_rx_process_data_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_rx_process_tkip_mic_fail_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru *  hmac_mgmt_tbtt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru *hmac_dfs_radar_detect_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru *  hmac_rx_process_mgmt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru* hmac_scan_proc_scan_comp_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* hmac_chan_result_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

extern frw_event_mem_stru* hmac_scan_proc_scanned_bss_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern frw_event_mem_stru *hmac_dpd_data_cali_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif
extern frw_event_mem_stru * hmac_init_event_process_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_proc_event_del_ba_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru *hmac_proc_event_config_syn_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* hmac_mgmt_send_disasoc_deauth_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru* hmac_alg_ct_result_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* hmac_mgmt_rx_delba_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* hmac_switch_to_new_chan_complete_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru* hmac_dbac_status_notify_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru *hmac_proc_event_log_syn_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

/*Tx适配部分*/

extern oal_uint32 hmac_proc_add_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_del_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_host_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_test_hcc_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_mgmt_ctx_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_set_edca_param_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_process_action_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32   hmac_dpd_data_processed_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32   hmac_send_cali_data_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_sched_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_update_user_qos_table_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_join_set_dtim_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_send_connect_result_to_dmac_sta_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_join_set_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32 hmac_psm_opmode_notify_process_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32 hmac_proc_set_rx_filter_value_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_user_add_notify_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_init_event_process_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_cfg_vap_send_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_proc_rx_process_sync_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_select_channel_mac_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_initiate_switch_to_new_channel_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_restart_network_after_switch_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_disable_machw_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru* hmac_proc_disasoc_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

#ifdef _PRE_WLAN_FEATURE_ROAM
extern frw_event_mem_stru* hmac_proc_roam_trigger_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
#endif //_PRE_WLAN_FEATURE_ROAM
extern frw_event_mem_stru * hmac_cali2hmac_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern oal_uint32 hmac_psm_reset_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru* hmac_proc_event_syn_info_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern frw_event_mem_stru* hmac_scan_proc_obss_scan_comp_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif

#ifdef _PRE_WLAN_FEATRUE_FLOWCTL
extern frw_event_mem_stru* hmac_alg_flowctl_backp_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32 hmac_edca_opt_stat_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_main */

