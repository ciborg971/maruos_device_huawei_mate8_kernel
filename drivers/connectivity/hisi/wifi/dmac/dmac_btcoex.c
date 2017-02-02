


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "dmac_btcoex.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BTCOEX_C

#define WLAN_TIDNO_COEX_QOSNULL     WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   /* ����qos null�����������߸����ȼ�ѵ��֡ */

#define WLAN_BTCOEX_SCO_20M_RX_BA_LUT_WSIZE  4
#define WLAN_BTCOEX_SCO_40M_RX_BA_LUT_WSIZE  32
#define WLAN_BTCOEX_ADP_DOWN_RX_BA_LUT_WSIZE  4
#define WLAN_BTCOEX_ADP_UP_RX_BA_LUT_WSIZE    8
#define WLAN_BTCOEX_ADP_40M_RX_BA_LUT_WSIZE   32





/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
dmac_btcoex_stru gst_dmac_btcoex = {0};

extern oal_uint32  dmac_send_sys_event(mac_vap_stru *pst_mac_vap,
                                                wlan_cfgid_enum_uint16 en_cfg_id,
                                                oal_uint16 us_len,
                                                oal_uint8 *puc_param);
oal_void dmac_btcoex_rx_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_on);
oal_uint32 gul_rx_window = BTCOEX_RX_WINDOW_SIZE;



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


OAL_STATIC oal_void dmac_btcoex_encap_preempt_sta(oal_uint8 *puc_frame,
                                                               oal_uint8 *puc_da,
                                                               oal_uint8 *puc_sa,
                                                               coex_preempt_frame_enum_uint8 en_preempt_type)
{
    oal_uint32 ul_qosnull_seq_num = 0;
    /* ��д֡ͷ,����from dsΪ1��to dsΪ0��ps=1 ���frame control�ĵڶ����ֽ�Ϊ12 */
    if (BTCOEX_NULLDATA == en_preempt_type)
    {
        mac_ieee80211_frame_stru *pst_mac_header = (mac_ieee80211_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA | 0x1100,
                            puc_da,
                            puc_sa);
        /* �趨seq num��frag */
        puc_frame[22] = 0;
        puc_frame[23] = 0;
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
    }
    else if (BTCOEX_QOSNULL == en_preempt_type)
    {
        dmac_btcoex_qosnull_frame_stru *pst_mac_header = (dmac_btcoex_qosnull_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL | 0x1100,
                            puc_da,
                            puc_sa);
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
        pst_mac_header->bit_qc_tid = WLAN_TIDNO_COEX_QOSNULL;
        pst_mac_header->bit_qc_eosp = 0;

        /* ����seq�����к� */
        hal_get_btcoex_abort_qos_null_seq_num(&ul_qosnull_seq_num);
        pst_mac_header->bit_sc_seq_num = (ul_qosnull_seq_num + 1);
        hal_set_btcoex_abort_qos_null_seq_num(pst_mac_header->bit_sc_seq_num);

        /*Э��涨������QOS NULL DATAֻ����normal ack ��������Ҫ����0�ǶԷ����ack */
        pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;

    }
    else
    {
    }

}


oal_void dmac_btcoex_init_preempt(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, coex_preempt_frame_enum_uint8 en_preempt_type)
{
    /* ��д֡ͷ*/
    dmac_btcoex_encap_preempt_sta(gst_dmac_btcoex.auc_null_qosnull_frame,
                                  pst_mac_user->auc_user_mac_addr,
                                  pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                                  en_preempt_type);

    hal_set_btcoex_abort_null_buff_addr((oal_uint32)gst_dmac_btcoex.auc_null_qosnull_frame);

    return;
}
oal_void dmac_btcoex_set_null_params(oal_void)
{
    oal_uint32         ul_null_phy_val = 0;
    oal_uint32         ul_null_rate_val = 0;

    hal_get_btcoex_abort_null_phy_mode(&ul_null_phy_val);

    hal_get_btcoex_abort_null_data_rate(&ul_null_rate_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_null_phy_mode(ul_null_phy_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_null_data_rate(ul_null_rate_val);

    hal_set_btcoex_post_preempt_timeout_val(BT_POSTPREEMPT_TIMEOUT_US);

    hal_set_btcoex_post_preempt_tx_cnt(15);
}


oal_void dmac_btcoex_set_cf_end_cts_params(oal_void)
{
    oal_uint32         ul_cf_phy_val = 0;
    oal_uint32         ul_cf_daterate_val = 0;
    oal_uint32         ul_cts_phy_val = 0;
    oal_uint32         ul_cts_date_val = 0;

    hal_get_btcoex_abort_cf_end_phy_mode(&ul_cf_phy_val);

    hal_get_btcoex_abort_cf_end_data_rate(&ul_cf_daterate_val);

    hal_get_btcoex_abort_selfcts_phy_mode(&ul_cts_phy_val);

    hal_get_btcoex_abort_selfcts_data_rate(&ul_cts_date_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_cf_end_phy_mode(ul_cf_phy_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_cf_end_data_rate(ul_cf_daterate_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_selfcts_phy_mode(ul_cts_phy_val);

    /* ����ʹ��Ĭ��ֵ������Ҫ����ʱ����Ĳ��� */
    hal_set_btcoex_abort_selfcts_data_rate(ul_cts_date_val);

    hal_set_btcoex_abort_selfcts_duration(BTCOEX_BT_DEFAULT_DURATION);

}
#if 0
/*****************************************************************************
 �� �� ��  : dmac_btcoex_rx_delba_event_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_rx_delba_event_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    hal_btcoex_btble_status_stru *pst_hal_bt_status;
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;
    oal_uint8 uc_vap_idx;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    pst_hal_bt_status = (hal_btcoex_btble_status_stru *)pst_event->auc_event_data;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++) {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_rx_delba_event_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
            (MAC_VAP_STATE_P2P_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
        {
            if (OAL_TRUE == pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_sco) {
                dmac_btcoex_rx_delba_trigger(pst_mac_vap, OAL_TRUE);
            } else {
                dmac_btcoex_rx_delba_trigger(pst_mac_vap, OAL_FALSE);
            }

        }
    }
    return OAL_SUCC;
}
#endif


OAL_STATIC oal_uint32 dmac_a2dp_abort_count_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device = (mac_device_stru *)p_arg;
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    hal_to_dmac_device_stru *pst_hal_device;
    wlan_bw_cap_enum_uint8          en_bwcap;

    pst_hal_device = pst_mac_device->pst_device_stru;

    if ((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG2(0, OAM_SF_COEX, "{dmac_btcoex_vap_up_handle:mac devcie:0x%p hal device:0x%p}",pst_mac_device,pst_hal_device);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����ʶ����ǰ������ֻ����������֣��������ֲ��ԾۺϽ��д���ֱ�ӷ��� */
    if (!pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_a2dp)
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_abort_count_callback: don't need changed aggr num, just press keys");
    	return OAL_SUCC;
    }

    /* �����ֵ����ۺϸ����ĳ����£�ÿ��1s����Ҫ���һ�������Ƿ񽵵ͣ��Ƿ�Ҫ���ۺϸ��� */
    FRW_TIMER_RESTART_TIMER(&pst_mac_device->bt_coex_abort_timer, 1000, OAL_TRUE);

    /* �������ֳ����£��ԾۺϽ��д��� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_rx_delba_event_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);
        if(WLAN_BW_CAP_40M < en_bwcap)
        {
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
            (MAC_VAP_STATE_P2P_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
        {
            if(WLAN_BW_CAP_20M == en_bwcap)
            {
                if((pst_mac_device->ul_rx_rate < BTCOEX_RATE_THRESHOLD3) && (pst_mac_device->ul_bar_size > WLAN_BTCOEX_ADP_DOWN_RX_BA_LUT_WSIZE))
                {
                    pst_mac_device->ul_bar_size = WLAN_BTCOEX_ADP_DOWN_RX_BA_LUT_WSIZE;
                    OAM_WARNING_LOG2(0, OAM_SF_COEX, "{rx rate decline:%d M bar_size become:%d}", pst_mac_device->ul_rx_rate/1000,pst_mac_device->ul_bar_size);
                    dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
                }
                else if((pst_mac_device->ul_rx_rate > BTCOEX_RATE_THRESHOLD0) && (pst_mac_device->ul_bar_size < WLAN_BTCOEX_ADP_UP_RX_BA_LUT_WSIZE))
                {

                    pst_mac_device->ul_bar_size = WLAN_BTCOEX_ADP_UP_RX_BA_LUT_WSIZE;
                    OAM_WARNING_LOG2(0, OAM_SF_COEX, "{rx rate increase:%d M bar_size become:%d}", pst_mac_device->ul_rx_rate/1000,pst_mac_device->ul_bar_size);
                    dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
                }

            }
            else
            {
                pst_mac_device->ul_bar_size = WLAN_BTCOEX_ADP_40M_RX_BA_LUT_WSIZE;
                OAM_WARNING_LOG2(0, OAM_SF_COEX, "{ a2dp 40M rx rate increase:%d M bar_size become:%d}", pst_mac_device->ul_rx_rate/1000,pst_mac_device->ul_bar_size);
                dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
            }

        }
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint32 dmac_sco_abort_count_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device = (mac_device_stru *)p_arg;
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    hal_to_dmac_device_stru *pst_hal_device;
    wlan_bw_cap_enum_uint8          en_bwcap;

    pst_hal_device = pst_mac_device->pst_device_stru;

    if ((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG2(0, OAM_SF_COEX, "{dmac_btcoex_vap_up_handle:mac devcie:0x%p hal device:0x%p}",pst_mac_device,pst_hal_device);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����ʶ����ǰ������ֻ����������֣��������ֲ��ԾۺϽ��д���ֱ�ӷ��� */
    if (!pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_sco)
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_abort_count_callback: don't need changed aggr num, just tel above 10s");
    	return OAL_SUCC;
    }

    /* ����Ƶ����绰�Ϳ��ص绰 */
    FRW_TIMER_RESTART_TIMER(&pst_mac_device->bt_coex_abort_timer, 1000, OAL_TRUE);

    /* �����绰�����£��ԾۺϽ��д��� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_rx_delba_event_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);
        if(WLAN_BW_CAP_40M < en_bwcap)
        {
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
            (MAC_VAP_STATE_P2P_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
        {

            if(WLAN_BW_CAP_20M == en_bwcap)
            {
               pst_mac_device->ul_bar_size = WLAN_BTCOEX_SCO_20M_RX_BA_LUT_WSIZE;
               OAM_WARNING_LOG2(0, OAM_SF_COEX, "{ sco 20M rx rate decline:%d M bar_size become:%d}", pst_mac_device->ul_rx_rate/1000,pst_mac_device->ul_bar_size);
               dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
            }
            else
            {
                pst_mac_device->ul_bar_size = WLAN_BTCOEX_SCO_40M_RX_BA_LUT_WSIZE;
                OAM_WARNING_LOG2(0, OAM_SF_COEX, "{sco 40M rx rate increase:%d M bar_size become:%d}", pst_mac_device->ul_rx_rate/1000,pst_mac_device->ul_bar_size);
                dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
            }
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_btcoex_sco_aggr_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_sco_aggr_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    hal_btcoex_btble_status_stru *pst_hal_bt_status;
    mac_device_stru *pst_mac_device;
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    wlan_bw_cap_enum_uint8          en_bwcap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_aggr_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    pst_hal_bt_status = (hal_btcoex_btble_status_stru *)pst_event->auc_event_data;

    OAM_WARNING_LOG1(0, OAM_SF_COEX, "{bt sco status changed:%d}", pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_sco);


    if(pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_sco)
    {
        /* ����occupied��ʱ�� */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_abort_timer,
                               dmac_sco_abort_count_callback,
                               10000,
                               (oal_void *)pst_mac_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);

    }
    else
    {

        if (OAL_TRUE == pst_mac_device->bt_coex_abort_timer.en_is_registerd)
        {
            FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->bt_coex_abort_timer));
        }

        if(WLAN_AMPDU_RX_BA_LUT_WSIZE == pst_mac_device->ul_bar_size)
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "bt sco status aggr size is :%d",pst_mac_device->ul_bar_size);
            return OAL_SUCC;
        }

        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
             pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
             if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
             {
                 OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_sco_aggr_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
                 continue;
             }

             mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);
             if(WLAN_BW_CAP_40M < en_bwcap)
             {
                 continue;
             }

             if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
                 (MAC_VAP_STATE_P2P_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
             {
                 pst_mac_device->ul_bar_size = WLAN_AMPDU_RX_BA_LUT_WSIZE;
                 dmac_btcoex_delba_trigger(pst_mac_vap, OAL_FALSE, (oal_uint8)pst_mac_device->ul_bar_size);
                 OAM_WARNING_LOG0(0, OAM_SF_COEX, "bt sco closed aggr size become 32");
             }
        }

    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_btcoex_sco_aggr_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_ad2q_event_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    hal_btcoex_btble_status_stru *pst_hal_bt_status;
    mac_device_stru *pst_mac_device;
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    wlan_bw_cap_enum_uint8          en_bwcap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_ad2q_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    pst_hal_bt_status = (hal_btcoex_btble_status_stru *)pst_event->auc_event_data;

    OAM_WARNING_LOG1(0, OAM_SF_COEX, "{bt a2dp status changed:%d}", pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_a2dp);


    if(pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_a2dp)
    {
        /* ����occupied��ʱ�� */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_abort_timer,
                               dmac_a2dp_abort_count_callback,
                               3000,
                               (oal_void *)pst_mac_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);

    }
    else
    {

        if (OAL_TRUE == pst_mac_device->bt_coex_abort_timer.en_is_registerd)
        {
            FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->bt_coex_abort_timer));
        }

        if(WLAN_AMPDU_RX_BA_LUT_WSIZE == pst_mac_device->ul_bar_size)
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "bt a2dp status aggr size is :%d",pst_mac_device->ul_bar_size);
            return OAL_SUCC;
        }

        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
         pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
         if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
         {
             OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_ad2q_event_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
             continue;
         }

         mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);
         if(WLAN_BW_CAP_40M < en_bwcap)
         {
             continue;
         }

         if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
             (MAC_VAP_STATE_P2P_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
         {
             pst_mac_device->ul_bar_size = WLAN_AMPDU_RX_BA_LUT_WSIZE;
             dmac_btcoex_delba_trigger(pst_mac_vap, OAL_FALSE, (oal_uint8)(pst_mac_device->ul_bar_size));
             OAM_WARNING_LOG0(0, OAM_SF_COEX, "bt a2dp closed  aggr size become 32");
         }
        }

    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_status_event_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/

OAL_STATIC oal_uint32 dmac_btcoex_status_event_handler(frw_event_mem_stru *pst_event_mem)
{
     frw_event_stru *pst_event;
     hal_btcoex_btble_status_stru *pst_hal_bt_status;

     if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
     {
         OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::pst_event_mem null.}");
         return OAL_ERR_CODE_PTR_NULL;
     }

     pst_event = (frw_event_stru *)pst_event_mem->puc_data;
     pst_hal_bt_status = (hal_btcoex_btble_status_stru *)pst_event->auc_event_data;

     OAM_WARNING_LOG1(0, OAM_SF_COEX, "{bt status changed:%d}", pst_hal_bt_status->un_bt_status.st_bt_status.bit_bt_on);


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_register_dmac_misc_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 dmac_btcoex_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT || NULL == p_func)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_register_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_unregister_dmac_misc_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_btcoex_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_unregister_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}


oal_uint32 dmac_btcoex_init(oal_void)
{
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_MISC_BTCOEX, dmac_btcoex_status_event_handler)) {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event fail!}");
        return OAL_FAIL;
    }

    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_SCO_BTCOEX, dmac_btcoex_sco_aggr_handler)) {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register DMAC_SCO_BTCOEX_event fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_MISC_BTCOEX);
        return OAL_FAIL;
    }

    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_AD2P_BTCOEX, dmac_btcoex_ad2q_event_handler)) {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_DMAC_AD2P_BTCOEX_event fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_MISC_BTCOEX);
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_SCO_BTCOEX);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}


oal_uint32 dmac_btcoex_exit(oal_void)
{
    /* init coexit wifi bt param */
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_MISC_BTCOEX);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_MISC_BTCOEX);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_SCO_BTCOEX);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_wlan_priority_set()
 ��������  : ����趨�����ȼ�����
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_wlan_priority_set(oal_uint8 uc_value)
{
    /* uc_value == 1, ������ø����ȼ���uc_value == 0, ���ظ�Ӳ������ */
    hal_set_btcoex_hw_rx_priority_dis((oal_uint8)(!uc_value));

    /* ��������������ȼ� */
    hal_set_btcoex_hw_priority_en((oal_uint8)(!uc_value));

    /* ����������ȼ� */
    hal_set_btcoex_sw_priority_flag(uc_value);

}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_wlan_priority_timeout_callback()
 ��������  : ����趨�����ȼ�������ʱ����
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_btcoex_wlan_priority_timeout_callback(oal_void *p_arg)
{
    //mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;

    dmac_btcoex_wlan_priority_set(0);
    return OAL_SUCC;
}


oal_uint32 dmac_btcoex_get_rate(mac_vap_stru *pst_vap,hal_to_dmac_device_stru *pst_hal_device,dmac_rx_ctl_stru *pst_cb_ctrl)
{
    dmac_user_stru *pst_dmac_user;
    mac_device_stru *pst_mac_device;
    oal_uint32 ul_mac_tx_rate;  // û��ʵ����;��ֻ��Ϊ�˴���

    pst_mac_device      = mac_res_get_dev(0);
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&pst_cb_ctrl->st_rx_info));

    dmac_start_stat_rate(pst_dmac_user);

    if (pst_dmac_user->st_user_rate_info.st_dmac_rate_stat_info.us_rx_rate_stat_count < gul_rx_window)
    {
        return OAL_FALSE;
    }
    else
    {
        dmac_get_stat_rate(pst_dmac_user, &ul_mac_tx_rate, &pst_mac_device->ul_rx_rate);
        return OAL_TRUE;
    }

}
/*****************************************************************************
 �� �� ��  : dmac_btcoex_change_state_syn
 ��������  : ����״̬����hw_rx_prio
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��25��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_change_state_syn(oal_uint8 uc_state)
{

    switch (uc_state)
    {
    case MAC_VAP_STATE_STA_WAIT_SCAN:
    case MAC_VAP_STATE_STA_WAIT_JOIN:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4:
    case MAC_VAP_STATE_STA_AUTH_COMP:
    case MAC_VAP_STATE_STA_WAIT_ASOC:
    case MAC_VAP_STATE_STA_OBSS_SCAN:
    case MAC_VAP_STATE_STA_BG_SCAN:
        hal_set_btcoex_hw_rx_priority_dis(0);
        break;
    default:
        hal_set_btcoex_hw_rx_priority_dis(1);
    }

}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_rx_delba_trigger
 ��������  : Change ba size
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_rx_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_sco)
{
    dmac_to_hmac_btcoex_rx_delba_trigger_event_stru st_dmac_to_hmac_btcoex_rx_delba;

    st_dmac_to_hmac_btcoex_rx_delba.uc_bt_sco = uc_bt_sco;
    st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size = 4;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_BTCOEX_RX_DELBA_TRIGGER, OAL_SIZEOF(dmac_to_hmac_btcoex_rx_delba_trigger_event_stru), (oal_uint8 *)&st_dmac_to_hmac_btcoex_rx_delba);
}


oal_void dmac_btcoex_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_on,oal_uint8 uc_ba_size)
{
    dmac_to_hmac_btcoex_rx_delba_trigger_event_stru st_dmac_to_hmac_btcoex_rx_delba;

    st_dmac_to_hmac_btcoex_rx_delba.uc_bt_on = uc_bt_on;
    st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size = uc_ba_size;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_BTCOEX_RX_DELBA_TRIGGER, OAL_SIZEOF(dmac_to_hmac_btcoex_rx_delba_trigger_event_stru), (oal_uint8 *)&st_dmac_to_hmac_btcoex_rx_delba);
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_vap_up_handle
 ��������  : ����vap_up����BT�����ж�
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_vap_up_handle(mac_vap_stru *pst_mac_vap)
{
    oal_uint8 uc_chan_idx;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    wlan_bw_cap_enum_uint8 en_bwcap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_up_handle::pst_mac_device null.}");
        return;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_vap_up_handle::pst_hal_device null.}");
        return;
    }

    /* ״̬�ϱ�BT */
    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_up_handle::VAP state->TRUE.}");

    /* ״̬�ϱ�BT: �ŵ�������Ƶ�ʵ�*/
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                 "{dmac_btcoex_vap_up_handle::channel state: band->%d, channel->%d, bandwidth->%d.",
                 pst_mac_vap->st_channel.en_band,
                 pst_mac_vap->st_channel.uc_chan_number,
                 pst_mac_vap->st_channel.en_bandwidth);
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);   // Ƶ��
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);   // �ŵ�
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6);   // ����
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_coex_sw_irq_set(BIT5);

    hal_update_btcoex_btble_status(pst_hal_device);

    if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_set_btcoex_sw_all_abort_ctrl(1);

        mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);

        if (en_bwcap > WLAN_BW_CAP_40M)
        {
            return;
        }

        if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_sco)
        {
            pst_mac_device->ul_bar_size = (WLAN_BW_CAP_20M == en_bwcap) ?
                                WLAN_BTCOEX_SCO_20M_RX_BA_LUT_WSIZE : WLAN_BTCOEX_SCO_40M_RX_BA_LUT_WSIZE;
            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
        }
        else if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_a2dp)
        {
            pst_mac_device->ul_bar_size = (WLAN_BW_CAP_20M == en_bwcap) ?
                                    WLAN_BTCOEX_ADP_UP_RX_BA_LUT_WSIZE : WLAN_BTCOEX_ADP_40M_RX_BA_LUT_WSIZE;
            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, (oal_uint8)(pst_mac_device->ul_bar_size));
        }
    }

}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_vap_down_handle
 ��������  : ����vap_down����BT�����ж�
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_vap_down_handle(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::pst_mac_device null.}");

        return;
    }

    if (0 == mac_device_calc_up_vap_num(pst_mac_device))
    {
#if ((_PRE_WLAN_CHIP_FPGA_HI1101RF == _PRE_WLAN_CHIP_VERSION) || (_PRE_WLAN_CHIP_FPGA_HI1151RF == _PRE_WLAN_CHIP_VERSION))
        /* set channel 0 to mpw0, for coex, add by huangtao 20150121 */
        hal_mpw_soc_write_reg((oal_uint32)0x80001010, (oal_uint16)0x0);
#endif
        hal_set_btcoex_sw_all_abort_ctrl(0);
        hal_set_btcoex_hw_rx_priority_dis(1);

        /* ״̬�ϱ�BT */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::VAP state->FALSE.}");
        hal_set_btcoex_soc_gpreg0(0x0, 0xffff, 0);
        hal_coex_sw_irq_set(BIT5);
    }
}

#endif /* end of _PRE_WLAN_FEATURE_COEXIST_BT */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

