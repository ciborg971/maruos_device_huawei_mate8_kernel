


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_net.h"
#include "oal_cfg80211.h"
#include "wlan_spec.h"
#include "wal_linux_event.h"
#include "wal_linux_scan.h"
#include "wal_linux_cfg80211.h"
#include "wal_main.h"
#include "wal_linux_rx_rsp.h"
#include "hmac_vap.h"
#include "hmac_device.h"
#include "hmac_resource.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <net/cfg80211.h>
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

#endif

#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    /* UTģʽ�µ���frw_event_process_all_event */
    extern oal_void  frw_event_process_all_event(oal_uint ui_data);
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_SCAN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


OAL_STATIC oal_void  wal_inform_bss_frame(wal_scanned_bss_info_stru *pst_scanned_bss_info, oal_void *p_data)
{
    oal_cfg80211_bss_stru        *pst_cfg80211_bss;
    oal_wiphy_stru               *pst_wiphy;
    oal_ieee80211_channel_stru   *pst_ieee80211_channel;

    if ((OAL_PTR_NULL == pst_scanned_bss_info) || (OAL_PTR_NULL == p_data))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{wal_inform_bss_frame::input param pointer is null, pst_scanned_bss_info[%p], p_data[%p]!}",
                       pst_scanned_bss_info, p_data);
        return;
    }

    pst_wiphy = (oal_wiphy_stru *)p_data;

    pst_ieee80211_channel = oal_ieee80211_get_channel(pst_wiphy, (oal_int32)pst_scanned_bss_info->s_freq);

    OAM_INFO_LOG1(0, OAM_SF_SCAN, "{wal_inform_bss_frame::freq = [%u]!}", (oal_uint16)pst_scanned_bss_info->s_freq);

    pst_scanned_bss_info->l_signal = pst_scanned_bss_info->l_signal * 100;

    /* ����ϱ��ں�bss ��Ϣ */
    pst_cfg80211_bss = oal_cfg80211_inform_bss_frame(pst_wiphy, pst_ieee80211_channel, pst_scanned_bss_info->pst_mgmt, pst_scanned_bss_info->ul_mgmt_len, pst_scanned_bss_info->l_signal, GFP_ATOMIC);
    if (pst_cfg80211_bss != NULL)
    {
        oal_cfg80211_put_bss(pst_cfg80211_bss);
    }

    return;
}
oal_void  wal_inform_all_bss(oal_wiphy_stru  *pst_wiphy, hmac_bss_mgmt_stru  *pst_bss_mgmt, oal_uint8   uc_vap_id)
{
    mac_bss_dscr_stru              *pst_bss_dscr;
    hmac_scanned_bss_info          *pst_scanned_bss;
    oal_dlist_head_stru            *pst_entry;
    mac_ieee80211_frame_stru       *pst_frame_hdr;
    wal_scanned_bss_info_stru       st_scanned_bss_info;
    oal_uint32                      ul_ret;
    oal_uint32                      ul_bss_num_not_in_regdomain = 0;
    oal_uint8                       uc_chan_number;
    enum ieee80211_band             en_band;

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ����ɨ�赽��bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if ((OAL_PTR_NULL == pst_bss_dscr) || (OAL_PTR_NULL == pst_bss_dscr->auc_mgmt_buff))
        {
            continue;
        }

        uc_chan_number = pst_bss_dscr->st_channel.uc_chan_number;
        en_band        = (enum ieee80211_band)pst_bss_dscr->st_channel.en_band;

        /* �ж��ŵ��ǲ����ڹ������ڣ�������ڣ����ϱ��ں� */
        ul_ret = mac_is_channel_num_valid(en_band, uc_chan_number);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(uc_vap_id, OAM_SF_SCAN,
                             "{wal_inform_all_bss::curr channel[%d] and band[%d] is not in regdomain.}",
                             uc_chan_number, en_band);
            ul_bss_num_not_in_regdomain++;
            continue;
        }

        /* ��ʼ�� */
        oal_memset(&st_scanned_bss_info, 0, OAL_SIZEOF(wal_scanned_bss_info_stru));

        st_scanned_bss_info.l_signal    = pst_bss_dscr->c_rssi;

        /*��bss�����ŵ�������Ƶ��*/
        st_scanned_bss_info.s_freq      = (oal_int16)oal_ieee80211_channel_to_frequency(uc_chan_number, en_band);
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_SCAN, "{wal_inform_all_bss::scan_comp freq[%u] chan[%d] band[%d] !}",
                      (oal_uint16)st_scanned_bss_info.s_freq, uc_chan_number, en_band);

        /* �����ָ֡��ͳ��� */
        st_scanned_bss_info.pst_mgmt    = (oal_ieee80211_mgmt_stru *)(pst_bss_dscr->auc_mgmt_buff);
        st_scanned_bss_info.ul_mgmt_len = pst_bss_dscr->ul_mgmt_len;

        /* ��ȡ�ϱ���ɨ�����Ĺ���֡��֡ͷ */
        pst_frame_hdr  = (mac_ieee80211_frame_stru *)pst_bss_dscr->auc_mgmt_buff;

        /* ���ɨ��������յ���֡������beacon���ͣ�ͳһ�޸�Ϊprobe rsp�����ϱ���
           Ϊ�˽���ϱ��ں˵�ɨ����beacon֡�������е����⣬�����⣬��01���ֹ� */
    	if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
    	{
    	    /* �޸�beacon֡����Ϊprobe rsp */
    		pst_frame_hdr->st_frame_control.bit_sub_type = WLAN_PROBE_RSP;
    	}

        /* �ϱ�ɨ�������ں� */
        wal_inform_bss_frame(&st_scanned_bss_info, pst_wiphy);
    }

    /* ����� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    OAM_WARNING_LOG2(uc_vap_id, OAM_SF_SCAN,
                     "{wal_inform_all_bss::there are %d bss not in regdomain, so inform kernal bss num is [%d]!}",
                     ul_bss_num_not_in_regdomain, (pst_bss_mgmt->ul_bss_num - ul_bss_num_not_in_regdomain));

    return;
}
OAL_STATIC oal_void  wal_set_scan_channel(
                    oal_cfg80211_scan_request_stru    *pst_request,
					oal_uint32                        *pul_channels_2g,
					oal_uint32                        *pul_num_channels_2g,
					oal_uint32                        *pul_channels_5g,
					oal_uint32                        *pul_num_channels_5g)

{
    oal_uint32  ul_loop;
    oal_uint32  ul_num_chan_2G;
    oal_uint32  ul_num_chan_5G;
    oal_uint16  us_center_freq;
    oal_int32   l_chan;

    if ((OAL_PTR_NULL == pst_request) || (OAL_PTR_NULL == pul_channels_2g))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_set_scan_channel::scan failed, null ptr, pst_request[%p], pul_channels_2g[%p].}\r\n",
          pst_request, pul_channels_2g);

        return ;
    }

    if ((OAL_PTR_NULL == pul_num_channels_2g) || (OAL_PTR_NULL == pul_channels_5g)|| (OAL_PTR_NULL == pul_num_channels_5g))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{wal_set_scan_channel::scan failed, null ptr, pul_num_channels_2g[%p], pul_channels_5g[%p], pul_num_channels_5g[%p].}\r\n",
          pul_num_channels_2g, pul_channels_5g, pul_num_channels_5g);

        return ;
    }

    ul_num_chan_2G = 0;
    ul_num_chan_5G = 0;

    for (ul_loop = 0; ul_loop < pst_request->n_channels; ul_loop++)
    {
        us_center_freq = pst_request->channels[ul_loop]->center_freq;

        /* ��������Ƶ�ʣ������ŵ��� */
        l_chan = (oal_int32)oal_ieee80211_frequency_to_channel((oal_int32)us_center_freq);

        if (us_center_freq <= WAL_MAX_FREQ_2G)
        {
            pul_channels_2g[ul_num_chan_2G++] = (oal_uint32)l_chan;
        }
        else
        {
            pul_channels_5g[ul_num_chan_5G++] = (oal_uint32)l_chan;
        }
    }

    *pul_num_channels_2g = ul_num_chan_2G;
    *pul_num_channels_5g = ul_num_chan_5G;
}
OAL_STATIC oal_void wal_set_scan_ssid(oal_cfg80211_scan_request_stru *pst_request, mac_cfg80211_scan_param_stru *pst_scan_param)
{
    oal_int32   l_loop;
    oal_int32   l_ssid_num;

    if ((OAL_PTR_NULL == pst_request) || (OAL_PTR_NULL == pst_scan_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_set_scan_ssid::scan failed, null ptr, pst_request[%p], pst_scan_param[%p].}",
          pst_request, pst_scan_param);

        return;
    }

    pst_scan_param->en_scan_type = OAL_ACTIVE_SCAN; /* active scan */
    pst_scan_param->l_ssid_num   = 0;

    /* ȡ�ں��·���ssid�ĸ��� */
    l_ssid_num = pst_request->n_ssids;
    if (l_ssid_num > WLAN_SCAN_REQ_MAX_SSID)
    {
        /* ����û��·���ָ��ssid�ĸ�����������֧�ֵ�����������ȡ����֧�ֵ�ָ��ssid�������� */
        l_ssid_num = WLAN_SCAN_REQ_MAX_SSID;
    }

    /* ���û��·���ssid��Ϣ��������Ӧ�Ľṹ���� */
    if ((l_ssid_num > 0) && (OAL_PTR_NULL != pst_request->ssids))
    {
        pst_scan_param->l_ssid_num = l_ssid_num;

        for (l_loop = 0; l_loop < l_ssid_num; l_loop++)
        {
            pst_scan_param->st_ssids[l_loop].uc_ssid_len = pst_request->ssids[l_loop].ssid_len;
            if (pst_scan_param->st_ssids[l_loop].uc_ssid_len > OAL_IEEE80211_MAX_SSID_LEN)
            {
                OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_set_scan_ssid::ssid scan set failed, ssid_len[%d] is exceed, max[%d].}",
                  pst_scan_param->st_ssids[l_loop].uc_ssid_len, OAL_IEEE80211_MAX_SSID_LEN);

                pst_scan_param->st_ssids[l_loop].uc_ssid_len = OAL_IEEE80211_MAX_SSID_LEN;
            }

            oal_memcopy(pst_scan_param->st_ssids[l_loop].auc_ssid, pst_request->ssids[l_loop].ssid,
              pst_scan_param->st_ssids[l_loop].uc_ssid_len);
        }
	}
}


OAL_STATIC oal_uint32  wal_wait_for_scan_timeout_fn(void *p_arg)
{
    hmac_vap_stru                  *pst_hmac_vap = (hmac_vap_stru *)p_arg;
    mac_vap_stru                   *pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
    hmac_device_stru               *pst_hmac_device;
    mac_device_stru                *pst_mac_device;
    hmac_bss_mgmt_stru             *pst_bss_mgmt;
    oal_wiphy_mgmt_stru            *pst_wiphy_mgmt;
    oal_wiphy_stru                 *pst_wiphy;

    OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_wait_for_scan_complete_time_out::scan timeout proc.}");

    /* ���ݵ�ǰɨ������ͺ͵�ǰvap��״̬�������л�vap��״̬��ɨ���쳣�����У��ϱ��ں�ɨ��״̬Ϊɨ����� */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) &&
        (MAC_VAP_STATE_STA_WAIT_SCAN == pst_mac_vap->en_vap_state))
    {
        /* �ı�vap״̬��SCAN_COMP */
        mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_STA_SCAN_COMP;
    }

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_wait_for_scan_complete_time_out::pst_hmac_device is null.}");
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        wlan_pm_enable();
#endif
        return OAL_FAIL;
    }

    /* ��ȡmac device */
    pst_mac_device = pst_hmac_device->pst_device_base_info;

    pst_wiphy_mgmt = &(pst_mac_device->st_wiphy_mgmt);
    pst_wiphy      = pst_mac_device->pst_wiphy;

    /* ��ȡɨ�����Ĺ���ṹ��ַ */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    if (OAL_PTR_NULL != pst_wiphy_mgmt->pst_request)
    {
        /* �ϱ�ɨ�赽�����е�bss */
        wal_inform_all_bss(pst_wiphy, pst_bss_mgmt, pst_mac_vap->uc_vap_id);

        /* ֪ͨ kernel scan �Ѿ����� */
        oal_cfg80211_scan_done(pst_wiphy_mgmt->pst_request, 0);

        pst_wiphy_mgmt->pst_request = OAL_PTR_NULL;
        pst_wiphy_mgmt->en_complete = OAL_TRUE;

        /* �ñ������Ż�ʱ��֤OAL_WAIT_QUEUE_WAKE_UP�����ִ�� */
        OAL_SMP_MB();
        OAL_WAIT_QUEUE_WAKE_UP(&pst_wiphy_mgmt->st_wait_queue);
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    wlan_pm_enable();
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_void  wal_start_timer_for_scan_timeout(oal_uint8   uc_vap_id)
{
    hmac_vap_stru               *pst_hmac_vap = OAL_PTR_NULL;
    mac_device_stru             *pst_mac_device = OAL_PTR_NULL;
    oal_uint32                   ul_timeout;

    /* ��ʱʱ��Ϊ5�� */
    ul_timeout = WAL_MAX_SCAN_TIME_PER_SCAN_REQ;

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{wal_start_timer_for_scan_timeout::pst_hmac_vap is null!}");
        return;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{wal_start_timer_for_scan_timeout::pst_mac_device is null!}");
        return;
    }

    /* ����ɨ�豣����ʱ������ָ��ʱ��û���ϱ�ɨ�����������ϱ�ɨ����� */
    FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_scan_timeout),
                           wal_wait_for_scan_timeout_fn,
                           ul_timeout,
                           pst_hmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_WAL,
                           pst_mac_device->ul_core_id);

    OAM_WARNING_LOG1(uc_vap_id, OAM_SF_SCAN,
                     "{wal_start_timer_for_scan_timeout::start a timer, wait time[%d] for scan timeout proc.}", ul_timeout);

    return;
}


oal_void wal_scan_work_func(oal_wiphy_mgmt_stru                   *pst_wiphy_mgmt,
                                  oal_net_device_stru                   *pst_netdev,
                                  oal_cfg80211_scan_request_stru        *pst_request)
{
    mac_cfg80211_scan_param_stru st_scan_param;
    oal_uint32                  *pul_channels_2G = OAL_PTR_NULL;
    oal_uint32                  *pul_channels_5G = OAL_PTR_NULL;
    oal_uint32                   ul_num_channels_2G = 0;
    oal_uint32                   ul_num_channels_5G = 0;
    oal_uint32                   ul_channel_num = 0;
    oal_uint32                   ul_ret;
    mac_vap_stru                *pst_mac_vap = OAL_NET_DEV_PRIV(pst_netdev);
    oal_uint8                    uc_vap_id = pst_mac_vap->uc_vap_id;

    oal_memset(&st_scan_param, 0, sizeof(mac_cfg80211_scan_param_stru));

    /* ��¼�ں��·����ŵ������� */
    ul_channel_num = pst_request->n_channels;

    pul_channels_2G = oal_memalloc(ul_channel_num * OAL_SIZEOF(oal_uint32));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pul_channels_2G))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_CFG, "{wal_scan_work_func::2.4G channel alloc mem return null ptr!}");
        return;
    }

    pul_channels_5G = oal_memalloc(ul_channel_num * OAL_SIZEOF(oal_uint32));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pul_channels_5G))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_CFG, "{wal_scan_work_func::5G channel alloc mem return null ptr!}");
        oal_free(pul_channels_2G);
        return;
    }

    /* �����ں��·���ɨ���ŵ��б� */
    wal_set_scan_channel(pst_request, pul_channels_2G, &ul_num_channels_2G, pul_channels_5G, &ul_num_channels_5G);

    OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{wal_scan_work_func::channel num is %d, 2.4G: %d, 5G: %d!}",
      ul_channel_num, ul_num_channels_2G, ul_num_channels_5G);

    if (ul_num_channels_2G > 0)
    {
        st_scan_param.uc_num_channels_2G = (oal_uint8)ul_num_channels_2G;
        st_scan_param.pul_channels_2G    = pul_channels_2G;
    }

    if (ul_num_channels_5G > 0)
    {
        st_scan_param.uc_num_channels_5G = (oal_uint8)ul_num_channels_5G;
        st_scan_param.pul_channels_5G    = pul_channels_5G;
    }

    /* �����ں��·���ssid */
    wal_set_scan_ssid(pst_request, &st_scan_param);

    /* �����ں��·���ie */
    st_scan_param.puc_ie    = pst_request->ie;
    st_scan_param.ul_ie_len = pst_request->ie_len;

    /* P2P WLAN/P2P ��������£�����ɨ���ssid �ж��Ƿ�Ϊp2p device �����ɨ�裬
        ssid Ϊ"DIRECT-"����Ϊ��p2p device �����ɨ�� */
    /* �����·�ɨ���device �Ƿ�Ϊp2p device(p2p0) */
    st_scan_param.bit_is_p2p0_scan      = OAL_FALSE;

    if ((pst_request->n_ssids > 0) && (NULL != pst_request->ssids)
        && (pst_request->ssids[0].ssid_len == OAL_STRLEN("DIRECT-"))
        && (0 == oal_memcmp(pst_request->ssids[0].ssid, "DIRECT-", OAL_STRLEN("DIRECT-"))))
    {
        st_scan_param.bit_is_p2p0_scan = OAL_TRUE;
    }

    /* ���¼�ǰ��ֹ�첽�������ɨ���,����ͬ������ */
    pst_wiphy_mgmt->en_complete = OAL_FALSE;

    /* ���¼���֪ͨ��������ɨ�� */
    ul_ret = wal_cfg80211_start_scan(pst_netdev, &st_scan_param);
    if( OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_scan_work_func::wal_cfg80211_start_scan proc failed, err_code[%d]!}", ul_ret);

        oal_free(pul_channels_2G);
        oal_free(pul_channels_5G);
        return;
    }

    /* win32 UTģʽ������һ���¼����� */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    frw_event_process_all_event(0);
#endif

    /* ������ʱ��������ɨ�賬ʱ���� */
    wal_start_timer_for_scan_timeout(uc_vap_id);

    return;
}
oal_int32 wal_send_scan_abort_msg(oal_net_device_stru   *pst_net_dev)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_pedding_data = 0;       /* ������ݣ���ʹ�ã�ֻ��Ϊ�˸��ýӿ� */
    oal_int32                       l_ret = 0;

    /* ���¼�֪ͨdevice����ֹɨ�� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SCAN_ABORT, OAL_SIZEOF(ul_pedding_data));

    oal_memcopy(st_write_msg.auc_value, (oal_int8 *)&ul_pedding_data, OAL_SIZEOF(ul_pedding_data));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(ul_pedding_data),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_send_scan_abort_msg::fail to stop scan, error[%d]}", l_ret);
    }

    return l_ret;
}


oal_int32 wal_force_scan_complete(oal_net_device_stru   *pst_net_dev,
                                         oal_bool_enum          en_is_aborted)
{
    mac_vap_stru            *pst_mac_vap;
    hmac_vap_stru           *pst_hmac_vap;
    hmac_device_stru        *pst_hmac_device;
    mac_device_stru         *pst_mac_device;
    oal_wiphy_mgmt_stru     *pst_wiphy_mgmt;

    pst_mac_vap  = OAL_NET_DEV_PRIV(pst_net_dev);

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_cfg80211_notify_scan_complete::pst_hmac_device is null, dev_id[%d]!}",
                         pst_mac_vap->uc_device_id);
        return -OAL_EINVAL;
    }

    pst_mac_device = pst_hmac_device->pst_device_base_info;
    pst_wiphy_mgmt = &(pst_mac_device->st_wiphy_mgmt);

    /* �ж�ɨ�����������ϲ�����ڲ� */
    if (OAL_PTR_NULL == pst_wiphy_mgmt->pst_request)
    {
        /* �ж��Ƿ�����ڲ�ɨ�裬������ڣ�Ҳ��Ҫֹͣ */
        if ((OAL_TRUE == pst_hmac_device->st_scan_mgmt.en_is_scanning) &&
            (pst_mac_vap->uc_vap_id == pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id))
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{wal_cfg80211_notify_scan_complete::may be internal scan, stop scan!}");
            /* ��ֹɨ�� */
            wal_send_scan_abort_msg(pst_net_dev);
        }

        return OAL_SUCC;
    }

    /* stop��vap������ɨ���vap����ͬ��ֱ�ӷ��� */
    if (pst_mac_vap->uc_vap_id != pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_cfg80211_notify_scan_complete::stop_vap[%d] is different scan_vap[%d]!}",
                         pst_mac_vap->uc_vap_id,
                         pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id);
        return OAL_SUCC;
    }

    /* ��ȡhmac vap */
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_cfg80211_notify_scan_complete::hmac_vap is null, vap_id[%d]!}", pst_mac_vap->uc_vap_id);
        return -OAL_EINVAL;
    }

    /* ɾ���ȴ�ɨ�賬ʱ��ʱ�� */
    if (OAL_TRUE == pst_hmac_vap->st_scan_timeout.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_vap->st_scan_timeout));
    }

    /* ������ϲ��·���ɨ��������֪ͨ�ں�ɨ��������ڲ�ɨ�費��֪ͨ */
    if (OAL_PTR_NULL != pst_wiphy_mgmt->pst_request)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_cfg80211_notify_scan_complete::vap_id[%d] notify kernel scan abort!}",
                         pst_mac_vap->uc_vap_id);

        /* ��ֹɨ�� */
        wal_send_scan_abort_msg(pst_net_dev);

        /* �ϱ��ں�ɨ���� */
        wal_inform_all_bss(pst_hmac_device->pst_device_base_info->pst_wiphy,
                           &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt),
                           pst_mac_vap->uc_vap_id);

        /* ֪ͨ�ں�ɨ����ֹ */
        oal_cfg80211_scan_done(pst_wiphy_mgmt->pst_request, en_is_aborted);
        pst_wiphy_mgmt->pst_request = OAL_PTR_NULL;
        pst_wiphy_mgmt->en_complete = OAL_TRUE;

        /* �ñ������Ż�ʱ��֤OAL_WAIT_QUEUE_WAKE_UP�����ִ�� */
        OAL_SMP_MB();
        OAL_WAIT_QUEUE_WAKE_UP(&pst_wiphy_mgmt->st_wait_queue);
    }

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

