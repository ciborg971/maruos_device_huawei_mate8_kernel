

#ifndef __DMAC_BTCOEX_H__
#define __DMAC_BTCOEX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif





/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "hal_ext_if.h"
#include "hal_hi1102_coex_reg.h"
#include "dmac_alg_if.h"
#include "dmac_rx_data.h"
#include "mac_resource.h"
#include "mac_board.h"
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BTCOEX_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*�������淶��������*/
typedef enum
{
    WIFIAWAKE = 0,
    WIFISLEEP = 1,
    COEX_ALL_STATUS
}COEX_STATUS;

typedef enum
{
    BTCOEX_NONE = 0,
    BTCOEX_PRIORITY = 1,
    BTCOEX_OCCUPIED = 2
} btcoex_sco_state_enum;


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
typedef struct mac_ieee80211_qoscoex_frame
{
    mac_header_frame_control_stru   st_frame_control;
    oal_uint16                      bit_duration_value      : 15,           /* duration/id */
                                    bit_duration_flag       : 1;
    oal_uint8                       auc_address1[WLAN_MAC_ADDR_LEN];
    oal_uint8                       auc_address2[WLAN_MAC_ADDR_LEN];
    oal_uint8                       auc_address3[WLAN_MAC_ADDR_LEN];
    oal_uint16                      bit_sc_frag_num     : 4,                /* sequence control */
                                    bit_sc_seq_num      : 12;
    oal_uint8                       bit_qc_tid          : 4,
                                    bit_qc_eosp         : 1,
                                    bit_qc_ack_polocy   : 2,
                                    bit_qc_amsdu        : 1;

}dmac_btcoex_qosnull_frame_stru;


typedef struct dmac_btcoex_param
{
    oal_uint32 ul_self_cts_duration;
    oal_uint32 ul_abort_null_duration;
}dmac_btcoex_param_stru;


typedef struct dmac_btcoex
{
    oal_uint8 auc_null_qosnull_frame[BTCOEX_MAC_HDR];
    dmac_btcoex_param_stru st_dmac_btcoex_param;
    oal_uint32 ul_occupied_times;
}dmac_btcoex_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint32 dmac_btcoex_init(oal_void);
extern oal_uint32 dmac_btcoex_exit(oal_void);
extern oal_void dmac_btcoex_init_preempt(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, coex_preempt_frame_enum_uint8 en_preempt_type);
extern oal_void dmac_btcoex_wlan_priority_set(oal_uint8 uc_value);
extern oal_uint32 dmac_btcoex_wlan_priority_timeout_callback(oal_void *p_arg);
extern oal_void dmac_btcoex_change_state_syn(oal_uint8 uc_state);
extern oal_void dmac_btcoex_vap_up_handle(mac_vap_stru *pst_mac_vap);
extern oal_void dmac_btcoex_vap_down_handle(mac_vap_stru *pst_mac_vap);
extern oal_uint32 dmac_btcoex_get_rate(mac_vap_stru *pst_vap,hal_to_dmac_device_stru *pst_hal_device,dmac_rx_ctl_stru *pst_cb_ctrl);
extern oal_void dmac_btcoex_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_on,oal_uint8 uc_ba_size);
extern oal_void dmac_btcoex_rx_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_on);


#endif /* #ifdef _PRE_WLAN_FEATURE_COEXIST_BT */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_data_acq.h */
