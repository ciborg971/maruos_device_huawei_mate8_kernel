


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "mac_frame.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_rx_data.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_blockack.h"
#include "dmac_psm_ap.h"
#include "dmac_mgmt_ap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_scan.h"
#include "dmac_alg_if.h"
#include "mac_vap.h"
#include "dmac_11w.h"
#include "dmac_dft.h"
#include "dmac_mgmt_sta.h"
#include "dmac_p2p.h"
#include "oal_net.h"
#include "dmac_beacon.h"
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "dmac_mgmt_sta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif


#ifdef _PRE_WLAN_RF_110X_CALI_DPD
#include "hal_ext_if.h"
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_device.h"
#include "dmac_resource.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#define OCCUPIED_TIMES 		3
#define OCCUPIED_INTERVAL 	80
#define OCCUPIED_PERIOD 	60000
oal_uint32  g_occupied_times = OCCUPIED_TIMES;
#endif


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_rx_process_control
 ��������  : ����֡����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_control(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8 *pen_go_on)
{
    dmac_rx_ctl_stru                 *pst_rx_ctl;
    mac_ieee80211_frame_stru         *pst_frame_hdr;
    mac_ieee80211_pspoll_frame_stru  *pst_pspoll_frame_hdr;
    oal_uint8                        *puc_payload;
    dmac_tid_stru                    *pst_tid;
    dmac_user_stru                   *pst_ta_user;
    oal_uint8                        *puc_sa_addr;
    oal_uint16                        us_user_idx = 0xFFFF;
    oal_uint8                         uc_tidno;
    oal_uint32                        ul_rslt;

    *pen_go_on = OAL_FALSE;//Ĭ�ϲ��ϱ�control֡

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    /* ����ACK֡ */
    if (WLAN_ACK == pst_frame_hdr->st_frame_control.bit_sub_type)
    {
#if(_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    /*****************************************************************************/
        /*��Ϣ�ϱ���ʱʹ�ã��㷨�ṩ��ɾ���ò���*/
        /* ��ȡԴ��ַ */
        puc_sa_addr = pst_frame_hdr->auc_address2;

        /*  ��ȡ�û�ָ�� */
        ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
        /*
            �����û�ʧ��: �����쳣�����أ�����Χ�ͷſռ�
            û���ҵ���Ӧ���û�: �������ִ��
        */
        if (OAL_SUCC != ul_rslt)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

            return ul_rslt;
        }

        /* ת��Ϊdmac user */
        pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
        if (OAL_PTR_NULL != pst_ta_user)
        {
            pst_ta_user->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        /*pst_ta_user->st_query_stats.ul_signal = smooth_signal_rssi(pst_ta_user->st_query_stats.ul_signal,pst_rx_ctl->st_rx_statistic.c_rssi_dbm);*/
        }
    /*****************************************************************************/
#endif
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::ack frame.}\r\n");
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_ack_dropped, 1);
        return OAL_SUCC;
    }

    /* ��ȡԴ��ַ */
    puc_sa_addr = pst_frame_hdr->auc_address2;

    /*  ��ȡ�û�ָ�� */
    ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
    /*
        �����û�ʧ��: �����쳣�����أ�����Χ�ͷſռ�
        û���ҵ���Ӧ���û�: �������ִ��
    */
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

        return ul_rslt;
    }

    /* ת��Ϊdmac user */
    pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_ta_user)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ta_user null, us_user_idx=%d.}", us_user_idx);

        mac_rx_report_80211_frame((oal_uint8 *)&(pst_dmac_vap->st_vap_base_info),
                                  (oal_uint8 *)&(pst_rx_ctl->st_rx_info),
                                  pst_netbuf,
                                  OAM_OTA_TYPE_RX_DMAC_CB);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ҵ��û�: ����ʱ��� */
    pst_ta_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    if (WLAN_BLOCKACK_REQ == (pst_frame_hdr->st_frame_control.bit_sub_type))    /* BAR 1000 */
    {
        /* ��ȡ֡ͷ��payloadָ��*/
        puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);

        /*************************************************************************/
        /*                     BlockAck Request Frame Format                     */
        /* --------------------------------------------------------------------  */
        /* |Frame Control|Duration|DA|SA|BAR Control|BlockAck Starting    |FCS|  */
        /* |             |        |  |  |           |Sequence number      |   |  */
        /* --------------------------------------------------------------------  */
        /* | 2           |2       |6 |6 |2          |2                    |4  |  */
        /* --------------------------------------------------------------------  */
        /*                                                                       */
        /*************************************************************************/

        uc_tidno        = (puc_payload[1] & 0xF0) >> 4;
        //us_start_seqnum = mac_get_bar_start_seq_num(puc_payload);

        pst_tid = &(pst_ta_user->ast_tx_tid_queue[uc_tidno]);
        if (OAL_PTR_NULL == pst_tid->pst_ba_rx_hdl)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ba_rx_hdl null.}");
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_bar_process_dropped, 1);
            dmac_mgmt_delba(pst_dmac_vap, pst_ta_user, uc_tidno, MAC_RECIPIENT_DELBA, MAC_QSTA_SETUP_NOT_DONE);
            return OAL_ERR_CODE_PTR_NULL;
        }
        /*Bar֡�ϴ���Hmac����*/
        //dmac_reorder_ba_rx_buffer_bar(pst_tid->pst_ba_rx_hdl, us_start_seqnum, &(pst_dmac_vap->st_vap_base_info));
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::receive bar.}");
        *pen_go_on = OAL_TRUE;
        return OAL_SUCC;

    }

    if (WLAN_PS_POLL == (pst_frame_hdr->st_frame_control.bit_sub_type))         /* PS_POLL 1010 */
    {
        /* �����ps-poll����Ӧ�ð�֡ͷת��Ϊps-poll��֡ͷ��ʽ */
        pst_pspoll_frame_hdr = (mac_ieee80211_pspoll_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

        /* AP��Ҫ�ж�PS_POLL�����AID��AP������û�AID�Ƿ�һ��,��һ�µĻ�ֱ�Ӻ��� */
        if (pst_pspoll_frame_hdr->bit_aid_value != pst_ta_user->st_user_base_info.us_assoc_id)
        {
            OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                           "{dmac_rx_process_control::AID in pspoll and AID in user_stru mismatch, bit_aid_value=%d us_assoc_id=%d.}",
                           pst_pspoll_frame_hdr->bit_aid_value, pst_ta_user->st_user_base_info.us_assoc_id);

            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return OAL_FAIL;
        }

        /* ֱ�ӵ���PS_POLL, ����ʹ��֡���ͼ��� */
        ul_rslt = dmac_psm_resv_ps_poll(pst_dmac_vap, pst_ta_user);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return ul_rslt;
        }
    }

    return OAL_SUCC;
}
#define RELATIVE_VALUE_POS_H 10
#define RELATIVE_VALUE_POS_M 6
#define RELATIVE_VALUE_POS_L 2
#define RELATIVE_VALUE_NEG_H -10
#define RELATIVE_VALUE_NEG_M -6
#define RELATIVE_VALUE_NEG_L -2
#define FACTOR_H 5
#define FACTOR_M 3
#define FACTOR_L 2
#define ABS(a,b)  ((a) >= 0 ? (b) : (-(b)))

oal_int32 smooth_signal_rssi(oal_int32 pre_rssi, oal_int32 rssi)
{
    oal_int32 factor;
    oal_int32 delta;
    /*���оƬbug����ʱdevice���ϱ�0ֵ���˴���0ֵ����*/
    if( 0 == rssi)
    {
        return pre_rssi;
    }
    /*ȡ��ǰֵ����ʷֵ�Ĳ�ֵ����ֵ��-10~10��Χ�⣬ȡ-10��10*/
    delta = rssi - pre_rssi;
    if( delta > RELATIVE_VALUE_POS_H)
    {
        delta = RELATIVE_VALUE_POS_H;
    }
    else if( delta < RELATIVE_VALUE_NEG_H)
    {
        delta = RELATIVE_VALUE_NEG_H;
    }
    /*��ȡ��ֵ�������ӣ�1/5,1/3��1/2*/
    if( delta > RELATIVE_VALUE_POS_M || delta < RELATIVE_VALUE_NEG_M )
    {
        factor = FACTOR_H;
    }
    else if( delta > RELATIVE_VALUE_NEG_L && delta < RELATIVE_VALUE_POS_L)
    {
        factor = FACTOR_L;
    }
    else
    {
        factor = FACTOR_M;
    }
    /*����ƽ�����rssi*/
    pre_rssi = pre_rssi + (delta*2 + ABS(delta,factor))/(factor*2);
    return pre_rssi;

}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC oal_uint32 dmac_btcoex_wlan_occupied_timeout_callback(oal_void *p_arg)
{
    dmac_device_stru *pst_dmac_device = (dmac_device_stru *)p_arg;
    mac_device_stru *pst_mac_device = pst_dmac_device->pst_device_base_info;
 	if (OAL_PTR_NULL == pst_mac_device)
	{
		OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_wlan_occupied_timeout_callback::pst_dmac_device null.}");
		return OAL_FAIL;
	}

	if (g_occupied_times > 0)
	{
		OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_wlan_occupied_timeout_callback::g_occupied_times = %d}" , g_occupied_times);
		g_occupied_times--;
		hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);

        /* ����occupied��ʱ�� */
        FRW_TIMER_CREATE_TIMER(&pst_dmac_device->bt_coex_occupied_timer,
                               dmac_btcoex_wlan_occupied_timeout_callback,
                               OCCUPIED_INTERVAL,
                               (oal_void *)pst_dmac_device,
                               OAL_FALSE,
                               OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);
		return OAL_SUCC;
	}

	g_occupied_times = OCCUPIED_TIMES;
	return OAL_SUCC;
}
#endif
OAL_STATIC oal_void dmac_rx_mgmt_update_tsf(dmac_vap_stru *pst_dmac_vap,
                                            mac_ieee80211_frame_stru *pst_frame_hdr,
                                            mac_scan_state_enum_uint8 en_scan_state)
{
    /* ɨ��״̬��STA UP/PAUSE״̬���յ�Beacon��probe rsp֡����TSF */
    if ((MAC_SCAN_STATE_RUNNING == en_scan_state) ||
        ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
          && ((MAC_VAP_STATE_PAUSE  == pst_dmac_vap->st_vap_base_info.en_vap_state)
          || (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state))))
    {
        if ((WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
             || (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            if (!OAL_MEMCMP(pst_frame_hdr->auc_address2, pst_dmac_vap->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN))
            {
                hal_sta_tsf_save(pst_dmac_vap->pst_hal_vap);
            }
            else
            {
                hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : dmac_rx_filter_mgmt
 ��������  : dmac_rx_filter_mgmt
 �������  : pst_dmac_vap
             pst_netbuf
             pst_event_mem
             &en_go_on
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
#define MAX_SMOOTH_RSSI_COUNT   (3)  /*�յ�3��beacon֡����һ��ƽ��*/
oal_uint32  dmac_rx_filter_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, frw_event_mem_stru *pst_event_mem, oal_uint8 *pen_go_on)
{
    mac_device_stru            *pst_mac_device;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_wps_ie      = OAL_PTR_NULL;
    oal_uint8                  *puc_payload     = OAL_PTR_NULL;
    oal_uint8                   auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta������ap mac��ַ */
    oal_uint16                  us_msg_len;         /* ��Ϣ�ܳ���,������FCS */
    oal_uint32                  ul_ret;
    oal_bool_enum_uint8         en_report_bss = OAL_FALSE;      /* �Ƿ��ϱ���bss */
    //static oal_uint8 smooth_count = 0;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::pst_mac_device is NULL.}");
        return OAL_FAIL;
    }

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    *pen_go_on = OAL_TRUE;  /* �������غ��Ƿ񷢵�HMAC����ʼΪtrue */

    /* ���TSF�������� */
    dmac_rx_mgmt_update_tsf(pst_dmac_vap, pst_frame_hdr, pst_mac_device->en_curr_scan_state);

    /* �����ǰdevice����ɨ��״̬�������յ��Ĺ���֡ */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
/* kaiyong��������ת�Ƶ�ɨ��ģ�鴦��ʱ��ִ�����´��� */
#ifdef _PRE_WLAN_FEATURE_P2P
        if (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func)
        {
            /* P2P �豸���յ�����֡ */
            if (!IS_LEGACY_VAP((&pst_dmac_vap->st_vap_base_info)))
            {
                dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf, pen_go_on);
            }
        }
        else
#endif
        {
            /* ���ɨ�趯������bss��Ϣ����ô����ɨ�����֡���ˣ����ж�Ӧ�Ĵ�����������do nothing  */
            if (pst_mac_device->st_scan_params.uc_scan_func & MAC_SCAN_FUNC_BSS)
            {
                *pen_go_on = OAL_FALSE;

                /* ɨ��״̬��֡���˴��� */
                dmac_scan_mgmt_filter(pst_dmac_vap, pst_netbuf, &en_report_bss);
            }
        }
    }

    if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state && WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on      = OAL_FALSE;
            pst_rx_info     = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));
            puc_payload     = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info, pst_netbuf);
            us_msg_len      = pst_rx_info->us_frame_len;                          /* ��Ϣ�ܳ���,������FCS */
            //puc_wps_ie      = mac_get_wps_ie(puc_payload, us_msg_len, 0);
            puc_wps_ie      = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_WLAN_OUI_TYPE_MICROSOFT_WPS, puc_payload, us_msg_len);
            if (OAL_PTR_NULL != puc_wps_ie)
            {
                *pen_go_on = OAL_TRUE;
            }
            dmac_ap_up_rx_probe_req(pst_dmac_vap, pst_netbuf);
        }
        else if (WLAN_AUTH == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on = OAL_FALSE;
            ul_ret = dmac_ap_up_rx_generate_chtxt(pst_dmac_vap, pst_netbuf, pst_event_mem);
            if (OAL_SUCC != ul_ret)
            {
                /* ��netbuf�黹�ڴ�� */
                oal_netbuf_free(pst_netbuf);
            }

            return ul_ret;
        }
#ifdef _PRE_WLAN_FEATURE_P2P
        else if(WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            if (IS_P2P_GO((&pst_dmac_vap->st_vap_base_info)))
            {
                dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf, pen_go_on);
            }
        }
#endif
    }

    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) && (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
        if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            /* ��ȡBeacon֡�е�mac��ַ����AP��mac��ַ */
            mac_get_bssid((oal_uint8 *)pst_frame_hdr, auc_bssid);
            if(0 == oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
            {
                //pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
                pst_dmac_vap->st_query_stats.ul_signal = smooth_signal_rssi( pst_dmac_vap->st_query_stats.ul_signal,pst_rx_ctl->st_rx_statistic.c_rssi_dbm);


#if (!defined(HI1102_EDA))
#ifdef _PRE_WLAN_FEATURE_P2P
                if (IS_P2P_CL((&pst_dmac_vap->st_vap_base_info)))
                {
                    /* ��ȡGO Beacon֡�е�NoA��Ѷ */
                    dmac_process_p2p_noa(pst_dmac_vap, pst_netbuf);
                }

                if ((IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))&&
                    (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
                {
                    dmac_p2p_oppps_ctwindow_start_event(pst_dmac_vap);
                }
#endif  /* #ifdef _PRE_WLAN_FEATURE_P2P */
#endif  /* #if (!defined(HI1102_EDA)) */

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    dmac_sync_tsf_by_bcn(pst_dmac_vap, pst_netbuf);
#endif
#if (!defined(HI1102_EDA))
#ifdef _PRE_WLAN_FEATURE_STA_PM
#ifdef _PRE_PSM_DEBUG_MODE
                //WRITEW(0x50002174,READW(0x50002174)|(BIT4));
#endif
                dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
#ifdef _PRE_PSM_DEBUG_MODE
                //WRITEW(0x50002174,READW(0x50002174)&(~BIT4));
#endif
#endif
#endif
            }
#if (defined(HI1102_EDA))
#ifdef _PRE_WLAN_FEATURE_STA_PM
            dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
#endif
#endif
            dmac_sta_up_rx_beacon(pst_dmac_vap, pst_netbuf, pen_go_on);
        }
    }
    else
    {
        if ((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
            || (WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        }
    }

    if(OAL_TRUE == en_report_bss)
    {
        /*�����ɨ�����Ѿ��ϱ����˴���Ӧ�����ϱ���netbuf,���Ҳ����ͷ�netbuf*/
        *pen_go_on = OAL_FALSE;
        return OAL_SUCC;
    }

    if (OAL_FALSE == *pen_go_on)
    {
        /* ��netbuf�黹�ڴ�� */
        oal_netbuf_free(pst_netbuf);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_mgmt_classify
 ��������  : DMACģ�飬�������̹���֡������ڣ���Ҫ����֡��DMAC����HMAC�ķַ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_mgmt_classify(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                mac_vap_stru                   *pst_vap,
                oal_netbuf_stru                *pst_netbuf)
{
    frw_event_stru                    *pst_event;
    dmac_wlan_crx_event_stru          *pst_crx_event;
    dmac_vap_stru                     *pst_dmac_vap;
    dmac_rx_ctl_stru                  *pst_rx_ctl;
    mac_ieee80211_frame_stru          *pst_frame_hdr;
    oal_bool_enum_uint8                en_go_on          = OAL_TRUE;           /* �Ƿ������hmac���� */
    mac_user_stru                     *pst_user;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    oal_uint32                         ul_relt           = OAL_SUCC;
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
	mac_device_stru					  *pst_mac_device;
    dmac_device_stru                  *pst_dmac_device;
#endif

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* �����¼�ͷ�е�VAP ID */
    pst_event_hdr->uc_vap_id = pst_vap->uc_vap_id;

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    /* ת��ΪDMAC VAP */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_mgmt_classify::pst_dmac_vap null.}");

        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (mac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctl->st_rx_info)));

    /* ����֡����Ŀǰû���ϱ���HMAC��ֱ��return */
    if (WLAN_CONTROL == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL != pst_user)
            dmac_alg_txbf_rx_cntl_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);

        dmac_rx_process_control(pst_dmac_vap, pst_netbuf, &en_go_on);
        if (OAL_FALSE == en_go_on)
        {
            oal_netbuf_free(pst_netbuf);
            return OAL_SUCC;
        }
    }

    /* DMAC����֡���� */
    if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type)
    {
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_PTR_NULL == pst_dmac_device)
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_mgmt_classify::pst_dmac_device null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_mac_device = pst_dmac_device->pst_device_base_info;
        if (OAL_PTR_NULL == pst_mac_device)
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_mgmt_classify::pst_mac_device null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

    	if(pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_ble_status.st_ble_status.bit_ble_scan)
    	{
            if ((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
                ||(WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
            {
    		    hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);

                /* ����occupied��ʱ�� */
                FRW_TIMER_CREATE_TIMER(&pst_dmac_device->bt_coex_occupied_timer,
                                       dmac_btcoex_wlan_occupied_timeout_callback,
                                       OCCUPIED_INTERVAL,
                                       (oal_void *)pst_dmac_device,
                                       OAL_FALSE,
                                       OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);
        	}
    	}
#endif
        if (OAL_PTR_NULL != pst_user)
        {
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)


            ul_relt = dmac_11w_rx_filter(pst_dmac_vap, pst_netbuf);
            if (OAL_SUCC != ul_relt)
            {
                /* �鲥����ʧ�ܣ����ϱ�����֡ */
                OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_RX,
                               "{dmac_rx_mgmt_classify::dmac_11w_rx_filter failed[%d].}", ul_relt);

                return ul_relt;
            }
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */
            dmac_alg_rx_mgmt_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);

        }

        dmac_rx_filter_mgmt(pst_dmac_vap, pst_netbuf, pst_event_mem, &en_go_on);
    }

    if (OAL_TRUE == en_go_on)
    {
        /* ��������֡ͳһ�ϱ���HMAC���� */
        /* �̳��¼��������޸��¼�ͷ����ʱδ����STA��APģʽ */
        FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX);

        pst_crx_event = (dmac_wlan_crx_event_stru *)(pst_event->auc_event_data);
        pst_crx_event->pst_netbuf = pst_netbuf;

        /* ��ǰcb�ֶ����ŵ���Ϣ�Ѿ��ڽ����жϵ��°벿�����˸�ֵ���˴��������¸�ֵ */
#if 0
        pst_rx_ctl->st_rx_info.uc_channel_number = pst_dmac_vap->pst_hal_device->uc_current_chan_number;
#endif

        /* �ַ� */
        return frw_event_dispatch_event(pst_event_mem);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_multi_mgmt_frame
 ��������  : ������������BSS�Ĺ㲥����֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_multi_mgmt_frame(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                oal_netbuf_stru                *pst_netbuf)
{
    mac_device_stru    *pst_device;
    mac_vap_stru       *pst_mac_vap;
    oal_netbuf_stru    *pst_netbuf_copy;
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint8           uc_vap_idx;
    oal_uint32          ul_rslt;

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX,
                       "{dmac_rx_multi_mgmt_frame::pst_device null, uc_device_id=%d.}", pst_event_hdr->uc_device_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��device�µ��豸��Ϊ0ʱ��ֱ���ͷŽ��յ��İ� */
    if (0 == pst_device->uc_vap_num)
    {
        //OAM_INFO_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::the device have none vap.}\r\n");

        oal_netbuf_free(pst_netbuf);
    }

    /* ��������BSS�Ĺ㲥����֡��ת����ÿһ��VAPһ�� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* ���һ��VAPֱ�ӷ���ԭ����netbuf */
        if (uc_vap_idx == pst_device->uc_vap_num - 1)
        {
            pst_netbuf_copy = pst_netbuf;
        }
        else
        {
            pst_netbuf_copy = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_TRUE);
            if (OAL_PTR_NULL == pst_netbuf_copy)
            {
                OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_netbuf_copy null.}");
                continue;
            }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            OAL_MEM_NETBUF_TRACE(pst_netbuf_copy, OAL_TRUE);
#endif

            pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf_copy);
            /* ��Ϣ���� */
            oal_memcopy(oal_netbuf_cb(pst_netbuf_copy), oal_netbuf_cb(pst_netbuf), OAL_SIZEOF(dmac_rx_ctl_stru));

#if (_PRE_PRODUCT_ID !=_PRE_PRODUCT_ID_HI1102_DEV)
            oal_memcopy(pst_netbuf_copy->head, pst_netbuf->head, (oal_uint32)(pst_netbuf->end - pst_netbuf->head));
#else
            oal_memcopy(oal_netbuf_header(pst_netbuf_copy), oal_netbuf_header(pst_netbuf), (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len));
            oal_memcopy(oal_netbuf_payload(pst_netbuf_copy), oal_netbuf_payload(pst_netbuf),
                       ((oal_uint32)(pst_rx_ctrl->st_rx_info.us_frame_len) - (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len)));
#endif

            /* ����netbuf���ȡ�TAILָ�� */
            oal_netbuf_set_len(pst_netbuf_copy, oal_netbuf_get_len(pst_netbuf));
            oal_set_netbuf_tail(pst_netbuf_copy, oal_netbuf_data(pst_netbuf_copy) + oal_netbuf_get_len(pst_netbuf_copy));

            /* ����MAC֡ͷ��ָ��(copy�󣬶�Ӧ��mac header��ͷ�Ѿ������仯) */
            mac_set_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info), (oal_uint32 *)oal_netbuf_header(pst_netbuf_copy));
        }

        /* ���ô������֡�ӿ� */
        ul_rslt = dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_mac_vap, pst_netbuf_copy);
        if (ul_rslt != OAL_SUCC)
        {
//            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].", ul_rslt);
            OAL_IO_PRINT("\r\n dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].\r\n", ul_rslt);

            oal_netbuf_free(pst_netbuf_copy);
        }
    }


    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_rx_process_mgmt
 ��������  : ����֡�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_mgmt(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                hal_to_dmac_device_stru        *pst_hal_device,
                oal_netbuf_stru                *pst_netbuf)
{
    hal_to_dmac_vap_stru   *pst_hal_vap = OAL_PTR_NULL;
    dmac_rx_ctl_stru       *pst_cb_ctrl;
    oal_uint8               uc_vap_id;
    mac_vap_stru           *pst_vap;
    mac_device_stru        *pst_mac_device;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_ieee80211_frame_stru *pst_mac_ieee80211_frame;
#endif

    pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_DFT_STAT
    /* ����֡����ͳ�� */
    dmac_dft_mgmt_stat_incr(pst_mac_device, oal_netbuf_header(pst_netbuf), MAC_DEV_MGMT_STAT_TYPE_RX);
#endif

    /* ��ȡ��֡��Ӧ��VAP ID */
    uc_vap_id = pst_cb_ctrl->st_rx_info.bit_vap_id;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((uc_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_vap_id <= WLAN_PROXY_STA_END_ID)))        /* ���Ա�device�µ�ĳһBSS��֡ */
        {
            hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::hal vap failed!}");
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::mac vap is null!}");

                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            /* ����Ƿ��͸�sta0�Ĺ㲥/�鲥����֡����device�µ�ÿ��vap(����Proxy STA)������һ�� */
            pst_mac_ieee80211_frame = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);

            if ((WLAN_STA0_HAL_VAP_ID == uc_vap_id) && (ETHER_IS_MULTICAST(pst_mac_ieee80211_frame->auc_address1)))
            {
               return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
            }

            return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
        }
        else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* ��������bss�Ĺ㲥����֡ */
        {
            return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
        }
        else                                                /* �쳣֡ */
        {
            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
    else
    {
        if (uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)        /* ���Ա�device�µ�ĳһBSS��֡ */
        //if (HAL_VAP_ID_IS_VALID(uc_vap_id))  /* TODO proxy sta�򿪺�HAL VAP ID��һ�� */
        {
            /* ��ȡ��Ӧ��hal vap */
            hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::hal vap failed!}", uc_vap_id);
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::mac vap is null!}", pst_hal_vap->uc_mac_vap_id);
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
        }
        else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* ��������bss�Ĺ㲥����֡ */
        {
            return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
        }
        else                                                /* �쳣֡ */
        {
            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
#else
    //if (uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)        /* ���Ա�device�µ�ĳһBSS��֡ */
    if (HAL_VAP_ID_IS_VALID(uc_vap_id))
    {
        /* ��ȡ��Ӧ��hal vap */
        hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
        if (OAL_PTR_NULL == pst_hal_vap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_hal_vap null.}");

            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_vap null.}");

            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }

        return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
    }
    else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* ��������bss�Ĺ㲥����֡ */
    {
        return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
    }
    else                                                /* �쳣֡ */
    {
        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
#endif
}

/*****************************************************************************
 �� �� ��  : dmac_tx_process_action_event
 ��������  : DMACģ�飬ACTION���ʹ���ӿڣ���Ҫ�ǽ�����Ϣͬ���͵��ù���֡���ͽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��10��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tx_process_action_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_ctx_action_event;
    dmac_tx_event_stru         *pst_tx_event;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    oal_uint32                  ul_action_info_offset;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_process_action_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_tx_event            = (dmac_tx_event_stru *)pst_event->auc_event_data;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru) - MAC_80211_FRAME_LEN;
#else
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif
    pst_ctx_action_event    = (dmac_ctx_action_event_stru *)(oal_netbuf_data(pst_tx_event->pst_netbuf) + ul_action_info_offset);

    /* ��ȡȫ��board������Ϣ */

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /*��λ״̬��ͣ����*/
    if(OAL_PTR_NULL != pst_device && OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX,
                       "{dmac_tx_process_action_event::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_SUCC;
    }

    OAM_INFO_LOG2(0, OAM_SF_TX, "{dmac_tx_process_action_event::category %d, action %d.}",
                  pst_ctx_action_event->en_action_category, pst_ctx_action_event->uc_action);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_ctx_action_event->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_ctx_action_event->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_REQ:

                    dmac_mgmt_tx_addba_req(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:

                    dmac_mgmt_tx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_DELBA:

                    dmac_mgmt_tx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action type.}");
                    break;
            }

            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action category.}");
            break;
    }


    return OAL_SUCC;
}
oal_uint32  dmac_mgmt_tx_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    dmac_tx_event_stru      *pst_ctx_event;
    dmac_vap_stru           *pst_dmac_vap;
    oal_netbuf_stru         *pst_mgmt_frame;
    mac_tx_ctl_stru         *pst_tx_ctl;
    oal_uint32               ul_ret;
    oal_uint8                uc_mgmt_frm_type;
    mac_user_stru           *pst_mac_user;
    mac_device_stru         *pst_mac_device;

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);

    pst_ctx_event   = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_mgmt_frame  = pst_ctx_event->pst_netbuf;
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_frame);

    oal_set_netbuf_next(pst_mgmt_frame, OAL_PTR_NULL);
    oal_set_netbuf_prev(pst_mgmt_frame, OAL_PTR_NULL);
    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)        = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_mgmt_frame));
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* ����״̬ʱ��ǿ�Ʒ��͸ù���֡ */
    if (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        ul_ret = dmac_tx_force(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len, 1);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::dmac_tx_force [roam] len[%d] fail[%ld]}",
                           pst_ctx_event->us_frame_len, ul_ret);
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
        }
        return ul_ret;
    }
#endif //_PRE_WLAN_FEATURE_ROAM
    uc_mgmt_frm_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_cb_frame_hdr(pst_tx_ctl));
    if (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_AUTH)
    {
        pst_mac_user = mac_res_get_mac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
        pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_PTR_NULL == pst_mac_device)
        {
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_mac_device is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        if (OAL_PTR_NULL != pst_mac_user)
        {
            dmac_tid_clear(pst_mac_user, pst_mac_device);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        #ifdef _PRE_WLAN_DFT_STAT
            dmac_dft_tid_stat_init(pst_mac_user);
        #endif
#endif
        #ifdef _PRE_DEBUG_MODE
            dmac_dft_ampdu_stat_init(pst_mac_user);
        #endif
        }

    }

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_ctx_event->pst_netbuf);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_process_sync_event
 ��������  : �յ�wlan��Delba��addba rsp���ڵ�dmac��ͬ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_sync_event(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_crx_action_sync;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_sync_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_action_sync    = (dmac_ctx_action_event_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    OAM_INFO_LOG2(0, OAM_SF_RX, "{dmac_rx_process_sync_event::category %d, action %d.}",
                  pst_crx_action_sync->en_action_category, pst_crx_action_sync->uc_action);
    switch (pst_crx_action_sync->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_crx_action_sync->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_RSP:

                    dmac_mgmt_rx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                case MAC_BA_ACTION_DELBA:

                    dmac_mgmt_rx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action type.}");

                    break;
            }

            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action category.}");
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_process_priv_req_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_priv_req_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    mac_priv_req_args_stru     *pst_crx_priv_req_args;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_priv_req_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_priv_req_args   = (mac_priv_req_args_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_crx_priv_req_args->uc_type)
    {
        case MAC_A_MPDU_START:

            dmac_mgmt_rx_ampdu_start(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        case MAC_A_MPDU_END:
            dmac_mgmt_rx_ampdu_end(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_priv_req_event::invalid priv action type.}");
            break;
    }

    return OAL_SUCC;
}
oal_uint32  dmac_tx_complete_mgmt_notify(
                hal_to_dmac_device_stru *pst_hal_device,
                dmac_user_stru         *pst_dmac_user,
                hal_tx_dscr_stru       *pst_dscr,
                oal_netbuf_stru        *pst_buf)
{
    mac_tx_ctl_stru                *pst_tx_ctl;
    oal_uint8                       uc_tid;

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);

    if (OAL_TRUE == mac_is_delba_frame(pst_buf, &uc_tid))
    {
        pst_dmac_user->ast_tx_tid_queue[uc_tid].en_is_delba_ing = OAL_FALSE;
        return OAL_SUCC;
    }

    if (OAL_TRUE == mac_get_cb_is_bar(pst_tx_ctl))
    {
        dmac_tid_resume(pst_hal_device, &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctl)], DMAC_TID_PAUSE_RESUME_TYPE_BA);
        return OAL_SUCC;
    }

    return OAL_SUCC;
}
#if 0

oal_uint32  dmac_tx_complete_security_ap(
                dmac_user_stru     *pst_dmac_user,
                hal_tx_dscr_stru   *pst_dscr,
                oal_netbuf_stru    *pst_buf)
{

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_mgmt_connect_set_channel
 ��������  : STA�������ŵ�����AP�����ŵ��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_mgmt_connect_set_channel(
                mac_device_stru    *pst_mac_device,
                mac_vap_stru       *pst_up_vap,
                mac_channel_stru   *pst_channel)
{
    /* ��ǰû�д��ڹ���״̬��VAP������ֱ�����ŵ� */
    if (OAL_PTR_NULL == pst_up_vap)
    {
        dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);
        dmac_mgmt_switch_channel(pst_mac_device, pst_channel);

        return;
    }

    OAM_WARNING_LOG4(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: has up vap. up_vap_chan:%d bw:%d, new_chan:%d bw:%d",
                         pst_up_vap->st_channel.uc_chan_number,
                         pst_up_vap->st_channel.en_bandwidth,
                         pst_channel->uc_chan_number,
                         pst_channel->en_bandwidth);

    if (pst_channel->uc_chan_number != pst_up_vap->st_channel.uc_chan_number)
    {
        /* ��ͣ�����ŵ���VAP���� */
        dmac_vap_pause_tx_by_chl(pst_mac_device, &(pst_up_vap->st_channel));

        OAM_WARNING_LOG1(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: diff chan_num. switch off to chan %d.",
                            pst_channel->uc_chan_number);

        /* ������֡���ŵ����� */
        dmac_switch_channel_off(pst_mac_device, pst_up_vap, pst_channel, 20);
    }
    else
    {
        if (pst_channel->en_bandwidth > pst_up_vap->st_channel.en_bandwidth)
        {
            OAM_WARNING_LOG2(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel:  same chan_num[%d], switch to bw[%d].",
                            pst_channel->uc_chan_number,
                            pst_channel->en_bandwidth);

            dmac_mgmt_switch_channel(pst_mac_device, pst_channel);
        }
    }

}
oal_uint32 dmac_join_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                 *pst_event;
    frw_event_hdr_stru             *pst_event_hdr;
    dmac_ctx_join_req_set_reg_stru *pst_reg_params;
    mac_device_stru                *pst_device;
    dmac_vap_stru                  *pst_dmac_vap;
    mac_vap_stru                   *pst_vap_up;     /* ����UP״̬��VAP */
#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_sta_pm_handler_stru        *pst_mac_sta_pm_handle; /* STA����״̬�½ṹ�� */
#endif

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_join_req_set_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ͬ��dmac vap���ŵ���Ϣ */
    pst_dmac_vap->st_vap_base_info.st_channel = pst_reg_params->st_current_channel;

    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* дSTA BSSID�Ĵ���*/
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap, pst_reg_params->auc_bssid);

    /* ͬ��beacon period */
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = pst_reg_params->us_beacon_period;
    if (0 != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::beacon period[%d]}",
                         pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
        /* ��beacon������д��Ĵ��� */
        hal_vap_set_psm_beacon_period(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
    }
    /* ����tbtt offset��λus */
    hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, DMAC_DEFAULT_STA_INTER_TBTT_OFFSET);

    /* ����sta tbtt��ʱ�� */
    hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);

    /* ���ý���beacon��ʱ�жϵ�ʱ�� */
    hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, DMAC_DEFAULT_STA_BEACON_WAIT_TIME);

    /* ֪ͨ�㷨 */
    dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);
    dmac_alg_cfg_bandwidth_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);

    /* ����д���UP״̬��VAP���˴��������ŵ���Ҫ������֡ */
    mac_device_find_up_vap(pst_device, &pst_vap_up);
    dmac_mgmt_connect_set_channel(pst_device, pst_vap_up, &(pst_reg_params->st_current_channel));

/* �����02ģʽ�£���Ҫ���ŵ���Ϣͬ����dmac vap�ṹ���� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy(&(pst_dmac_vap->st_vap_base_info.st_channel), &(pst_reg_params->st_current_channel), OAL_SIZEOF(mac_channel_stru));
    OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::chan_num[%d], band[%d], bandwidth[%d].}",
                  pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                  pst_dmac_vap->st_vap_base_info.st_channel.en_band,
                  pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth);
#endif

    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    /* ��ʼ��Ĭ�Ͻ���beacon֡ */
    /* ��ֹ�����������޸ļĴ�������д�Ĵ�������beacon֡ */
    if(OAL_FALSE == pst_reg_params->ul_beacon_filter)
    {
        /* �ر�beacon֡����  */
        hal_disable_beacon_filter(pst_device->pst_device_stru);
    }

    /* ��ʼ��Ĭ�ϲ�����non_direct_frame֡*/
    /* Ϊ��ֹ�����������޸ļĴ�����д�Ĵ���������non_direct_frame֡ */
    if(OAL_TRUE == pst_reg_params->ul_non_frame_filter)
    {
        /* ��non frame֡���� */
        hal_enable_non_frame_filter(pst_device->pst_device_stru);
    }

    /* �����Ż�����ͬƵ���µ�������һ�� */
    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
    }

    /* ����ssid */
    oal_memcopy(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID, pst_reg_params->auc_ssid, WLAN_SSID_MAX_LEN);
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID[WLAN_SSID_MAX_LEN - 1] = '\0';

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* ����Beacon interval�޸Ķ�Ӧ��STA������keepalive��DTIM interval */
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_mac_sta_pm_handle null}");
    }
    else
    {
        if (0 != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)
        {
            pst_mac_sta_pm_handle->ul_ps_keepalive_max_num = (200 * 100) /
                        (pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
        }
    }
#endif

#if 0
OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{call DPD Calibration Start function}");

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
      dmac_start_dpd_calibration(pst_vap_up);
    }
#endif
#endif
    return OAL_SUCC;
}
oal_uint32 dmac_join_set_dtim_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_set_dtim_tsf_reg_stru      *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_set_dtim_tsf_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* дbssid �Ĵ��� */
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap,pst_reg_params->auc_bssid);

    /* */
    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* дtsf �Ĵ��� */
    if(OAL_TRUE == (oal_uint32)pst_reg_params->us_tsf_bit0)
    {
       /* enable tbtt */
       hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : dmac_set_smps_process
 ��������  : DMAC����SMPSģʽ������(����MAC�Ĵ�����ʹ��SMPS)
 �������  : pst_event_mem--�¼�ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��17��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_set_smps_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                         *pst_event;
    frw_event_hdr_stru                     *pst_event_hdr;
    mac_cfg_smps_mode_stru                 *pst_smps_mode;
    hal_smps_mode_enum_uint8                en_smps_mode;
    mac_device_stru                        *pst_device;
    mac_vap_stru                           *pst_mac_vap;
    mac_user_stru                          *pst_mac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SMPS, "{dmac_set_smps_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_smps_mode           = (mac_cfg_smps_mode_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device   = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = mac_res_get_mac_user(pst_smps_mode->us_user_idx);

    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_alg_cfg_smps_notify(pst_mac_vap, pst_mac_user);

    pst_device->uc_dev_smps_mode = pst_smps_mode->uc_smps_mode;

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == pst_smps_mode->uc_smps_mode)
    {
        pst_device->en_smps = OAL_FALSE;
        en_smps_mode = HAL_SMPS_MODE_DISABLE;
    }
    else
    {
        pst_device->en_smps = OAL_TRUE;
        en_smps_mode = (hal_smps_mode_enum_uint8)(pst_smps_mode->uc_smps_mode);
    }

    /* дSMPS���ƼĴ��� */
    hal_set_smps_mode(pst_device->pst_device_stru, en_smps_mode);

    return OAL_SUCC;
}
#endif
oal_uint32  dmac_asoc_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_asoc_set_reg_stru       *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_user_stru                      *pst_dmac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{dmac_asoc_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_asoc_set_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_dmac_user = mac_res_get_dmac_user(pst_reg_params->uc_user_index);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ֧��QOS �����Ĵ���*/
    hal_machw_seq_num_index_update_per_tid(pst_device->pst_device_stru, pst_dmac_user->uc_lut_index, OAL_TRUE);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_conn_result_event
 ��������  : ����hmac�����Ĺ�������¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_mgmt_conn_result_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    oal_uint32                           ul_result;
    oal_uint32                           ul_ret;
    mac_device_stru                     *pst_device;
    mac_vap_stru                        *pst_vap_up;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "pst_event_mem null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    ul_result               = *((oal_uint32 *)pst_event->auc_event_data);

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_SUCC != ul_result)
    {
        /* �����vap up����ָ����Ǹ�vap���ڵ��ŵ� */
        ul_ret = mac_device_find_up_vap(pst_device, &pst_vap_up);
        if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
        {
            if (MAC_VAP_STATE_PAUSE == pst_vap_up->en_vap_state)
            {
                pst_device->st_home_channel = pst_vap_up->st_channel;
                dmac_scan_switch_channel_back(pst_device);

                OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_DBAC, "dmac_mgmt_conn_result_event: conn fail, switch to up vap. channel num:%d",
                                pst_device->st_home_channel.uc_chan_number);
            }
        }
    }

    dmac_tx_fake_queue_empty_assert(pst_device->pst_device_stru, HAL_TX_FAKE_QUEUE_BGSCAN_ID, THIS_FILE_ID);

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

