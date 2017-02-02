
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oal_net.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "oal_schedule.h"
#endif
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_regdomain.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "mac_ie.h"
#include "dmac_scan.h"
#include "dmac_main.h"
#include "dmac_acs.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_ext_if.h"
#include "dmac_device.h"
#include "dmac_mgmt_sta.h"
#if defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "dmac_scan_test.h"
#endif
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_dbac.h"
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#include "pm_extern.h"
#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_SCAN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ��̬�������� */

OAL_STATIC oal_uint32 dmac_scan_send_bcast_probe(mac_device_stru *pst_mac_device, oal_uint8 uc_band, oal_uint8  uc_index);

#if 0
#ifdef _PRE_WLAN_FEATURE_DBAC
OAL_STATIC oal_uint32  dmac_scan_register_scan_req_to_dbac(mac_device_stru *pst_mac_device);
#endif
#endif
OAL_STATIC oal_uint32  dmac_scan_report_channel_statistics_result(mac_device_stru *pst_mac_device, oal_uint8 uc_scan_idx);

OAL_STATIC oal_void    dmac_scan_switch_home_channel_work(mac_device_stru *pst_mac_device);

OAL_STATIC oal_uint32  dmac_scan_switch_home_channel_work_timeout(void *p_arg);

OAL_STATIC oal_uint32  dmac_scan_start_pno_sched_scan_timer(void *p_arg);


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if 0
OAL_STATIC oal_void dmac_scan_print_time_stamp()
{
    oal_uint32                  ul_timestamp;

    ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_print_time_stamp:: time_stamp:%d.}", ul_timestamp);

    return;
}
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST

oal_void dmac_detect_2040_te_a_b(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_frame_body, oal_uint16 us_frame_len, oal_uint16 us_offset,oal_uint8 uc_curr_chan)
{
    oal_uint8            chan_index     = 0;
    oal_bool_enum_uint8  ht_cap         = OAL_FALSE;
    oal_bool_enum_uint8  intolerant     = OAL_FALSE;
    oal_uint16           us_index       = us_offset;
    oal_uint8            uc_real_chan   = uc_curr_chan;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_detect_2040_te_a_b::mac_res_get_dev return null.}");
        return;
    }

    /* Ѱ��ht opern��ϢԪ�� */
    while(us_index < us_frame_len)
    {
        if(us_frame_len < (us_index + MAC_IE_HDR_LEN + puc_frame_body[us_index + 1]))
        {
            break;
        }

        if (MAC_EID_HT_CAP == puc_frame_body[us_index])
        {
            ht_cap = OAL_TRUE;

            /* Check for the Forty MHz Intolerant bit in HT-Capabilities */
            if((puc_frame_body[us_index + 3] & BIT6) != 0)
            {
                //OAM_INFO_LOG0(0, OAM_SF_SCAN, "dmac_detect_2040_te_a_b::40 intolerant in ht cap");
                intolerant = OAL_TRUE;
            }
        }
        else if (MAC_EID_2040_COEXT == puc_frame_body[us_index])
        {
            /* Check for the Forty MHz Intolerant bit in Coex-Mgmt IE */
            if((puc_frame_body[us_index + 2] & BIT1) != 0)
            {
                //OAM_INFO_LOG0(0, OAM_SF_SCAN, "dmac_detect_2040_te_a_b::40 intolerant in co");
                intolerant = OAL_TRUE;
            }
        }
        else if (MAC_EID_DSPARMS == puc_frame_body[us_index])
        {
            uc_real_chan = puc_frame_body[us_index + 2];
        }

        us_index += (MAC_IE_HDR_LEN + puc_frame_body[us_index + 1]);
    }

    mac_get_channel_idx_from_num((pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]).en_band,
                                    uc_real_chan, &chan_index);

    /* Detect Trigger Event - A */
    if(OAL_FALSE == ht_cap)
    {
        pst_dmac_vap->st_vap_base_info.st_ch_switch_info.ul_chan_report_for_te_a |= (1 << chan_index);
    }

    /* Register Trigger Event - B */
    if(OAL_TRUE == intolerant)
    {
        pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_te_b = OAL_TRUE;
    }

    return;
}
oal_void  dmac_scan_proc_obss_scan_complete_event(dmac_vap_stru *pst_dmac_vap)
{
    frw_event_mem_stru             *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru                 *pst_event;
    dmac_obss_te_a_b_stru          *pst_dmac_obss_te_a_b;

#if 0
    OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                 "{dmac_scan_proc_obss_scan_complete_event::te_a:%d,te_b:%d}",
                 pst_dmac_vap->st_vap_base_info.st_ch_switch_info.ul_chan_report_for_te_a,
                 pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_te_b);
#endif

    if(!pst_dmac_vap->st_vap_base_info.st_ch_switch_info.ul_chan_report_for_te_a
       && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_te_b))
    {
        return;
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_obss_te_a_b_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_obss_scan_complete_event::pst_event_mem null.}");

        return;
    }

    /* ����¼�ָ�� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP,
                       OAL_SIZEOF(dmac_obss_te_a_b_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    pst_dmac_obss_te_a_b = (dmac_obss_te_a_b_stru *)(pst_event->auc_event_data);

    pst_dmac_obss_te_a_b->ul_chan_report_for_te_a = pst_dmac_vap->st_vap_base_info.st_ch_switch_info.ul_chan_report_for_te_a;
    pst_dmac_obss_te_a_b->en_te_b = pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_te_b;


    /* �ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    pst_dmac_vap->st_vap_base_info.st_ch_switch_info.ul_chan_report_for_te_a = 0;
    pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_te_b = OAL_FALSE;

    return;
}
#endif
OAL_STATIC oal_void  dmac_scan_set_vap_mac_addr_by_scan_state(mac_device_stru  *pst_mac_device,
                                                                           oal_bool_enum_uint8 en_is_scan_start)
{
    dmac_vap_stru               *pst_dmac_vap;
    mac_vap_stru                *pst_mac_vap;
    mac_scan_req_stru           *pst_scan_params;
    OAL_STATIC oal_uint8         auc_original_mac_addr[6] = {0};

    /* ��ȡɨ����� */
    pst_scan_params = &(pst_mac_device->st_scan_params);

    /* �����mac addrɨ�裬ֱ�ӷ��أ���������֡���˼Ĵ��� */
    if (OAL_TRUE != pst_scan_params->en_is_random_mac_addr_scan)
    {
        //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: don't need modified mac addr.}");
        return;
    }

    /* p2pɨ�費֧�����mac addr */
    if (OAL_TRUE == pst_scan_params->bit_is_p2p0_scan)
    {
        //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: p2p scan, don't need modified mac addr.}");
        return;
    }

    /* ��ȡdmac vap */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_scan_params->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: pst_dmac_vap is null.}");
        return;
    }

    pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    /* ɨ�迪ʼʱ����������֡���˼Ĵ��� */
    if (OAL_TRUE == en_is_scan_start)
    {
        /* ����ԭ�ȵ�mac addr */
        oal_set_mac_addr(auc_original_mac_addr, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: save original mac addr, mac_addr[0-2]:%.2x:%.2x:%.2x.}",
                         auc_original_mac_addr[0], auc_original_mac_addr[1], auc_original_mac_addr[2]);
        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: mac_addr[3-5]:%.2x:%.2x:%.2x.}",
                         auc_original_mac_addr[3], auc_original_mac_addr[4], auc_original_mac_addr[5]);

        /* ����mib��Ӳ����macaddrΪ���mac addr */
        oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                         pst_scan_params->auc_sour_mac_addr);
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_scan_params->auc_sour_mac_addr);

        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: set random mac addr, mac_addr[0-2]:%.2x:%.2x:%.2x.}",
                         pst_scan_params->auc_sour_mac_addr[0],
                         pst_scan_params->auc_sour_mac_addr[1],
                         pst_scan_params->auc_sour_mac_addr[2]);
        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: mac_addr[3-5]:%.2x:%.2x:%.2x.}",
                         pst_scan_params->auc_sour_mac_addr[3],
                         pst_scan_params->auc_sour_mac_addr[4],
                         pst_scan_params->auc_sour_mac_addr[5]);
    }
    else
    {
        /* ɨ��������ָ�ԭ��mib��Ӳ���Ĵ�����mac addr */
        oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                         auc_original_mac_addr);
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, auc_original_mac_addr);

        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: resume original mac addr, mac_addr[0-2]:%.2x:%.2x:%.2x.}",
                         auc_original_mac_addr[0], auc_original_mac_addr[1], auc_original_mac_addr[2]);
        OAM_WARNING_LOG3(0, OAM_SF_SCAN, "{dmac_scan_set_vap_mac_addr_by_scan_state:: mac_addr[3-5]:%.2x:%.2x:%.2x.}",
                         auc_original_mac_addr[3], auc_original_mac_addr[4], auc_original_mac_addr[5]);
    }

    return;
}


OAL_STATIC oal_uint32  dmac_scan_report_scanned_bss(dmac_vap_stru *pst_dmac_vap, oal_void *p_param)
{
    frw_event_mem_stru                    *pst_event_mem;
    frw_event_stru                        *pst_event;
    mac_device_stru                       *pst_mac_device;
    dmac_tx_event_stru                    *pst_dtx_event;
    oal_netbuf_stru                       *pst_netbuf;
    dmac_rx_ctl_stru                      *pst_rx_ctrl;
    oal_uint8                             *puc_frame_body_tail;            /* ָ��֡���β�� */
    mac_scan_req_stru                     *pst_scan_params;
    mac_scanned_result_extend_info_stru   *pst_scanned_result_extend_info;
    oal_uint16                             us_frame_len;
	oal_uint16                             us_remain_netbuf_len;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_scan_report_scanned_bss::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_netbuf = (oal_netbuf_stru *)p_param;

    /* ��ȡ֡��Ϣ */
    us_frame_len = (oal_uint16)oal_netbuf_get_len(pst_netbuf);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    us_remain_netbuf_len = oal_netbuf_get_payload_len(pst_netbuf) - (us_frame_len - MAC_80211_FRAME_LEN);
#else
    us_remain_netbuf_len = (oal_uint16)oal_netbuf_tailroom(pst_netbuf);
#endif

    if(us_remain_netbuf_len < OAL_SIZEOF(mac_scanned_result_extend_info_stru))
    {
        /*to cut one netbuf mem.*/
        /*tailroom not enough*/
        OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_scan_report_scanned_bss::scan netbuf tailroom not enough,requet[%u],actual[%u] }",
                         us_remain_netbuf_len,
                         OAL_SIZEOF(mac_scanned_result_extend_info_stru));
        return OAL_FAIL;
    }

    /* ��ȡ��buffer�Ŀ�����Ϣ */
    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡɨ����� */
    pst_scan_params = &(pst_mac_device->st_scan_params);

    /* ÿ��ɨ��������ϱ�ɨ���������¼���HMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{dmac_scan_report_scanned_bss::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    /***********************************************************************************************/
    /*            netbuf data����ϱ���ɨ�������ֶεķֲ�                                        */
    /* ------------------------------------------------------------------------------------------  */
    /* beacon/probe rsp body  |     ֡����渽���ֶ�(mac_scanned_result_extend_info_stru)          */
    /* -----------------------------------------------------------------------------------------   */
    /* �յ���beacon/rsp��body | rssi(4�ֽ�) | channel num(1�ֽ�)| band(1�ֽ�)|bss_tye(1�ֽ�)|���  */
    /* ------------------------------------------------------------------------------------------  */
    /*                                                                                             */
    /***********************************************************************************************/

    /* ����չ��Ϣ������֡��ĺ��棬�ϱ���host�� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    puc_frame_body_tail = (oal_uint8 *)MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctrl->st_rx_info), pst_netbuf) + us_frame_len - MAC_80211_FRAME_LEN;
#else
    puc_frame_body_tail = (oal_uint8 *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info)) + us_frame_len;
#endif

    /* ָ��֡���β������netbuf������չ��Я��������Ҫ�ϱ�����Ϣ */
    pst_scanned_result_extend_info = (mac_scanned_result_extend_info_stru *)puc_frame_body_tail;

    /* ����ϱ�ɨ��������չ�ֶ���Ϣ�����и�ֵ */
    OAL_MEMZERO(pst_scanned_result_extend_info, OAL_SIZEOF(mac_scanned_result_extend_info_stru));
    pst_scanned_result_extend_info->l_rssi = (oal_int32)pst_rx_ctrl->st_rx_statistic.c_rssi_dbm;
    pst_scanned_result_extend_info->en_bss_type = pst_scan_params->en_bss_type;

    /* ����֡�ĳ���Ϊ������չ�ֶεĳ��� */
    us_frame_len += OAL_SIZEOF(mac_scanned_result_extend_info_stru);

    /* ҵ���¼���Ϣ */
    pst_dtx_event               = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dtx_event->pst_netbuf   = pst_netbuf;
    pst_dtx_event->us_frame_len = us_frame_len;

#if 0
    /* ����ά����Ϣ����ǰ�ŵ��š��ź�ǿ�ȡ��ϱ���netbuf���� */
    OAM_ERROR_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                   "{dmac_scan_report_scanned_bss::rssi[%d], cb_rssi[%d], channel_num[%d], buf_len[%d].}",
                   pst_scanned_result_extend_info->l_rssi,
                   pst_rx_ctrl->st_rx_statistic.c_rssi_dbm,
                   pst_rx_ctrl->st_rx_info.uc_channel_number,
                   us_frame_len);
#endif

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_scan_check_bss_in_pno_scan(oal_uint8         *puc_frame_body,
                                                                  oal_int32          l_frame_body_len,
                                                                  mac_pno_scan_stru *pst_pno_scan_info,
                                                                  oal_int32          l_rssi)
{
    oal_uint8       *puc_ssid;
    oal_int32        l_loop;
    oal_int8         ac_ssid[WLAN_SSID_MAX_LEN];
    oal_uint8        uc_ssid_len = 0;

    /* �����֡���ź�С��pnoɨ����ϱ�����ֵ���򷵻�ʧ�ܣ���֡���ϱ� */
    if (l_rssi < pst_pno_scan_info->l_rssi_thold)
    {
        return OAL_FAIL;
    }

    OAL_MEMZERO(ac_ssid, OAL_SIZEOF(ac_ssid));

    /* ��ȡ����֡�е�ssid IE��Ϣ */
    puc_ssid = mac_get_ssid(puc_frame_body, l_frame_body_len, &uc_ssid_len);
    if ((OAL_PTR_NULL != puc_ssid) && (0 != uc_ssid_len))
    {
        oal_memcopy(ac_ssid, puc_ssid, uc_ssid_len);
        ac_ssid[uc_ssid_len] = '\0';
    }

    /* ��pno�����в��ұ�ssid�Ƿ���ڣ�������ڣ�������ϱ� */
    for (l_loop = 0; l_loop < pst_pno_scan_info->l_ssid_count; l_loop++)
    {
        /* ���ssid��ͬ�����سɹ� */
        if (0 == oal_memcmp(ac_ssid, pst_pno_scan_info->ac_match_ssid_set[l_loop], (uc_ssid_len + 1)))
        {
            //OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_check_bss_in_pno_scan::ssid match success.}");
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_check_bss_type
 ��������  : ����յ���beacon/probe response�ǲ���Ҫɨ���bss
 �������  : puc_frame_body: beancon֡��
             pst_scan_params: ����ɨ�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_scan_check_bss_type(oal_uint8 *puc_frame_body, mac_scan_req_stru *pst_scan_params)
{
    mac_cap_info_stru         *pst_cap_info;

    /*************************************************************************/
    /*                       Beacon Frame - Frame Body                       */
    /* ----------------------------------------------------------------------*/
    /* |Timestamp|BcnInt|CapInfo|SSID|SupRates|DSParamSet|TIM  |CountryElem |*/
    /* ----------------------------------------------------------------------*/
    /* |8        |2     |2      |2-34|3-10    |3         |6-256|8-256       |*/
    /* ----------------------------------------------------------------------*/
    pst_cap_info = (mac_cap_info_stru *)(puc_frame_body + MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN);

    if ((WLAN_MIB_DESIRED_BSSTYPE_INFRA == pst_scan_params->en_bss_type) &&
        (1 != pst_cap_info->bit_ess))
    {
        //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_check_bss_type::expect infra bss, but it's not infra bss.}\r\n");
        return OAL_FAIL;
    }

    if ((WLAN_MIB_DESIRED_BSSTYPE_INDEPENDENT == pst_scan_params->en_bss_type) &&
        (1 != pst_cap_info->bit_ibss))
    {
        //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_check_bss_type::expect ibss, but it's not ibss.}\r\n");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_scan_mgmt_filter
 ��������  : device��ɨ��״̬�µĽ��չ���֡����
 �������  : dmac_vap_stru *pst_dmac_vap,
             oal_void *p_param,
             oal_uint8 *pen_report_bss,              �Ƿ��ϱ�bss�ɹ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_scan_mgmt_filter(dmac_vap_stru *pst_dmac_vap, oal_void *p_param, oal_bool_enum_uint8 *pen_report_bss)
{
    oal_netbuf_stru            *pst_netbuf;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint8                  *puc_frame_body;
    mac_device_stru            *pst_mac_device;
    mac_scan_req_stru          *pst_scan_params;
    oal_uint32                  ul_ret;
    oal_uint16                  us_frame_len;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    oal_uint16                  us_offset =  MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
#endif
#endif

    pst_mac_device  = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_mgmt_filter::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_scan_params = &(pst_mac_device->st_scan_params);

    pst_netbuf = (oal_netbuf_stru *)p_param;

    /* ��ȡ��buffer�Ŀ�����Ϣ */
    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡ֡��Ϣ */
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info));
    puc_frame_body = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctrl->st_rx_info), pst_netbuf);

    us_frame_len   = (oal_uint16)oal_netbuf_get_len(pst_netbuf);

    if ((WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type) ||
        (WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
    {
        /* ���ɨ�赽bss������ */
        ul_ret = dmac_scan_check_bss_type(puc_frame_body, pst_scan_params);
        if (OAL_SUCC != ul_ret)
        {
            //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_mgmt_filter::scanned bss isn't the desired one.}\r\n");
            return OAL_SUCC;
        }

        /* �����obssɨ�裬���ϱ�ɨ������ֻ�ڴ��ŵ���⵽��beacon֡����probe rsp֡�����¼���host����20/40�����߼����� */
        if (WLAN_SCAN_MODE_BACKGROUND_OBSS == pst_scan_params->en_scan_mode)
        {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
            dmac_detect_2040_te_a_b(pst_dmac_vap, puc_frame_body, us_frame_len, us_offset, pst_rx_ctrl->st_rx_info.uc_channel_number);
#endif
#endif
            return OAL_SUCC;
        }
        else
        {
            /* �����pno����ɨ�裬����Ҫ����rssi��ssid�Ĺ��� */
            if (WLAN_SCAN_MODE_BACKGROUND_PNO == pst_scan_params->en_scan_mode)
            {
                /* ��Ȿbss�Ƿ�����ϱ�����pnoɨ��ĳ����� */
                ul_ret = dmac_scan_check_bss_in_pno_scan(puc_frame_body,
                                                         (oal_int32)(us_frame_len - MAC_80211_FRAME_LEN),
                                                         &(pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params),
                                                         (oal_int32)pst_rx_ctrl->st_rx_statistic.c_rssi_dbm);
                if (OAL_SUCC != ul_ret)
                {
                    //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_mgmt_filter::this bss info can't report host.}");
                    return OAL_SUCC;
                }

                /* �����ɨ�赽�˵�һ��ƥ���ssid����ɨ�赽��ƥ���ssid���λΪ�� */
                if (OAL_TRUE != pst_mac_device->pst_pno_sched_scan_mgmt->en_is_found_match_ssid)
                {
                    pst_mac_device->pst_pno_sched_scan_mgmt->en_is_found_match_ssid = OAL_TRUE;

                    /* ֹͣpno����ɨ�趨ʱ�� */
                    dmac_scan_stop_pno_sched_scan_timer(pst_mac_device->pst_pno_sched_scan_mgmt);
                }
            }

            /* ����ģʽɨ�裬�ϱ�ɨ�赽��ɨ���� */
            ul_ret = dmac_scan_report_scanned_bss(pst_dmac_vap, p_param);
            if (OAL_SUCC != ul_ret)
            {
                *pen_report_bss = OAL_FALSE;
                OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_mgmt_filter::report scan result failed.}");
                return OAL_SUCC;
            }
            else
            {
                *pen_report_bss = OAL_TRUE;
            }
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_encap_probe_req_frame
 ��������  : ��װprobe request֡
 �������  : pst_dmac_vap: DMAC VAP
             puc_buffer: buffer��ʼ��ַ
             puc_bssid: bssid
             pc_ssid: ssid
 �������  : ��
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  dmac_scan_encap_probe_req_frame(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_mgmt_buf, oal_uint8 *puc_bssid, oal_int8 *pc_ssid)
{
    oal_uint8        auc_bcst_addr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* �㲥��ַ */
    oal_uint8        uc_ie_len;
    oal_uint8       *puc_mac_header          = oal_netbuf_header(pst_mgmt_buf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       *puc_payload_addr        = oal_netbuf_data(pst_mgmt_buf);
#else
    oal_uint8       *puc_payload_addr        = puc_mac_header + MAC_80211_FRAME_LEN;
#endif
    oal_uint8       *puc_payload_addr_origin = puc_payload_addr;
    mac_device_stru *pst_mac_device = OAL_PTR_NULL;
    oal_uint16       us_app_ie_len;
    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_mac_header, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_PROBE_REQ);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_mac_header, 0);

    /* ���õ�ַ1���㲥��ַ */
    oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR1_OFFSET, auc_bcst_addr);

    /* ���õ�ַ2��MAC��ַ(p2pɨ��Ϊp2p�ĵ�ַ������Ϊ������ַ��������mac addrɨ�迪������Ϊ�����ַ) */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, pst_mac_device->st_scan_params.auc_sour_mac_addr);

    /* ��ַ3���㲥��ַ */
    oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR3_OFFSET, puc_bssid);

    /*************************************************************************/
    /*                       Probe Request Frame - Frame Body                */
    /* --------------------------------------------------------------------- */
    /* |SSID |Supported Rates |Extended supp rates| HT cap|Extended cap      */
    /* --------------------------------------------------------------------- */
    /* |2-34 |   3-10         | 2-257             |  28   | 3-8              */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ����SSID */
    /***************************************************************************
                    ----------------------------
                    |Element ID | Length | SSID|
                    ----------------------------
           Octets:  |1          | 1      | 0~32|
                    ----------------------------
    ***************************************************************************/
    if ('\0' == pc_ssid[0])    /* ͨ��SSID */
    {
        puc_payload_addr[0] = MAC_EID_SSID;
        puc_payload_addr[1] = 0;
        puc_payload_addr   += MAC_IE_HDR_LEN;    /* ƫ��bufferָ����һ��ie */
    }
    else
    {
        puc_payload_addr[0] = MAC_EID_SSID;
        puc_payload_addr[1] = (oal_uint8)OAL_STRLEN(pc_ssid);
        oal_memcopy(&(puc_payload_addr[2]), pc_ssid, puc_payload_addr[1]);
        puc_payload_addr += MAC_IE_HDR_LEN + puc_payload_addr[1];  /* ƫ��bufferָ����һ��ie */
    }

    /* ����֧�ֵ����ʼ� */
    mac_set_supported_rates_ie(&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* ����extended supported rates��Ϣ */
    mac_set_exsup_rates_ie(&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* ���HT Capabilities��Ϣ */
    mac_set_ht_capabilities_ie(&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* ���Extended Capabilities��Ϣ */
    mac_set_ext_capabilities_ie(&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* ���vht capabilities��Ϣ */
    mac_set_vht_capabilities_ie(&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* ���WPS��Ϣ */
    mac_add_app_ie((oal_void *)&(pst_dmac_vap->st_vap_base_info), puc_payload_addr, &us_app_ie_len, OAL_APP_PROBE_REQ_IE);
    puc_payload_addr += us_app_ie_len;

    return (oal_uint16)(puc_payload_addr - puc_payload_addr_origin + MAC_80211_FRAME_LEN);
}

/*****************************************************************************
 �� �� ��  : dmac_scan_send_probe_req_frame
 ��������  : ����̽������֡
 �������  : pst_dmac_vap: DMAC VAP
             puc_bssid   : �˴�̽������֡�е�bssid
             pc_ssid     : �˴�̽������֡�е�ssid
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_scan_send_probe_req_frame(dmac_vap_stru *pst_dmac_vap,
                                            oal_uint8 *puc_bssid,
                                            oal_int8 *pc_ssid)
{
    oal_netbuf_stru        *pst_mgmt_buf;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret;
    oal_uint16              us_mgmt_len;
    oal_uint8              *puc_mac_header = OAL_PTR_NULL;
    oal_uint8              *puc_saddr;

    /* �������֡�ڴ� */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_TRUE);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_send_probe_req_frame::alloc netbuf failed.}");
        /* device netbuf ���벻��ά�⣬�Ժ�ɾ���� l00324381 20150902 */
        OAL_MEM_INFO_PRINT(OAL_MEM_POOL_ID_NETBUF);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf, OAL_PTR_NULL);

    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /* ��װprobe request֡ */
    us_mgmt_len = dmac_scan_encap_probe_req_frame(pst_dmac_vap, pst_mgmt_buf, puc_bssid, pc_ssid);

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    if (!ETHER_IS_MULTICAST(puc_bssid))
    {
        /* ���͵���̽��֡ */
        puc_mac_header = oal_netbuf_header(pst_mgmt_buf);
        puc_saddr = mac_vap_get_mac_addr(&(pst_dmac_vap->st_vap_base_info));
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR1_OFFSET, puc_bssid);
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, puc_saddr);
        MAC_GET_CB_IS_MCAST(pst_tx_ctl) = OAL_FALSE;
        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) =(oal_uint8)pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id;
    }
    else
    {
        /* �����㲥̽��֡ */
        MAC_GET_CB_IS_MCAST(pst_tx_ctl) = OAL_TRUE;
        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) =(oal_uint8)pst_dmac_vap->st_vap_base_info.us_multi_user_idx; /* probe request֡�ǹ㲥֡ */
    }

    /* ���÷��͹���֡�ӿ� */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, us_mgmt_len);
    if (OAL_SUCC != ul_ret)
    {

        oal_netbuf_free(pst_mgmt_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_proc_scan_complete_event
 ��������  : ɨ����ɺ���õĽӿ�
 �������  : dmac_vap_stru *pst_dmac_vap,
             mac_scan_status_enum_uint8 en_scan_rsp_status
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_scan_proc_scan_complete_event(dmac_vap_stru *pst_dmac_vap,
                                               mac_scan_status_enum_uint8 en_scan_rsp_status)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    mac_device_stru            *pst_mac_device;
    oal_uint8                   uc_vap_id;
    mac_scan_rsp_stru          *pst_scan_rsp_info;

    uc_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    //OAM_INFO_LOG0(uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_scan_complete_event:: start proc scan complete event.}");
    //dmac_scan_print_time_stamp();

    /* ��ȡdevice�ṹ�� */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_scan_complete_event::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ɨ�������¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_scan_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_scan_complete_event::alloc memory failed.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP,
                       OAL_SIZEOF(mac_scan_rsp_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    pst_scan_rsp_info = (mac_scan_rsp_stru *)(pst_event->auc_event_data);

    /* ����ɨ�����ʱ״̬���Ǳ��ܾ�������ִ�гɹ� */
    pst_scan_rsp_info->en_scan_rsp_status = en_scan_rsp_status;

    OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "dmac scan comp.status:%d, vap channel:%d",
                        en_scan_rsp_status,
                        pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number);

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 �� �� ��  : dmac_scan_is_too_busy
 ��������  : p2p�ѹ���ʱ ���ɨ���Ƿ�̫Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_scan_is_too_busy(mac_device_stru *pst_mac_device, mac_scan_req_stru *pst_scan_req_params)
{
    oal_uint32       ul_ret;
    oal_uint32       ul_timestamp;
    oal_uint32       ul_deltatime;

    ul_ret = mac_device_is_p2p_connected(pst_mac_device);
    if (OAL_SUCC == ul_ret)
    {
        ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        ul_deltatime = (ul_timestamp > pst_mac_device->ul_scan_timestamp)? \
                       (ul_timestamp - pst_mac_device->ul_scan_timestamp):(0xffffffff - pst_mac_device->ul_scan_timestamp + ul_timestamp);

        if (MAC_SCAN_FUNC_P2P_LISTEN != pst_scan_req_params->uc_scan_func)
        {
            if (ul_deltatime < DMAC_SCAN_DBAC_SCAN_DELTA_TIME)
            {
                OAM_WARNING_LOG2(0, OAM_SF_DBAC, "has connected p2p. scan deltatime:%d<%d, refused", ul_deltatime, DMAC_SCAN_DBAC_SCAN_DELTA_TIME);
                return OAL_TRUE;
            }
        }
        else
        {
            if (ul_deltatime > 500 || pst_scan_req_params->us_scan_time >= DMAC_SCAN_GO_MAX_SCAN_TIME)
            {
                OAM_WARNING_LOG2(0, OAM_SF_DBAC, "has connected p2p. p2p listen deltatime:%d, scan_time:%d, refused", ul_deltatime, pst_scan_req_params->us_scan_time);
                return OAL_TRUE;
            }
        }
    }

    return OAL_FALSE;
}
#endif


OAL_STATIC oal_uint32  dmac_scan_handle_scan_req_entry(mac_device_stru    *pst_mac_device,
                                                                 dmac_vap_stru      *pst_dmac_vap,
                                                                 mac_scan_req_stru  *pst_scan_req_params)
{

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* ֱ�ӷ���ɨ������������ɨ�裬����Ӱ�쳣�� */
    if((OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag) &&
       (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_scan_handle_scan_req_entry:: Because of always tx is running, cann't start scan.}");

        /* ������ϲ��·���ɨ������ֱ����ɨ������¼�; OBSSɨ���򷵻ؽ������ȴ���һ�ζ�ʱ����ʱ�ٷ���ɨ�� */
        if (pst_scan_req_params->en_scan_mode < WLAN_SCAN_MODE_BACKGROUND_OBSS)
        {
            return dmac_scan_proc_scan_complete_event(pst_dmac_vap, MAC_SCAN_REFUSED);
        }
        else
        {
            return OAL_SUCC;
        }
    }
#endif

    /* ��ȡ��ǰdeviceɨ��״̬���������ɨ��״̬����ֱ�ӷ��� */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_scan_handle_scan_req_entry:: device scan is running, scan_vap_id[%d], scan_func[0x%02x].}",
                         pst_mac_device->st_scan_params.uc_vap_id, pst_mac_device->st_scan_params.uc_scan_func);

        /* ������ϲ��·���ɨ������ֱ����ɨ������¼�; OBSSɨ���򷵻ؽ������ȴ���һ�ζ�ʱ����ʱ�ٷ���ɨ�� */
        if (pst_scan_req_params->en_scan_mode < WLAN_SCAN_MODE_BACKGROUND_OBSS)
        {
            /* ��ɨ������¼���ɨ�����󱻾ܾ� */
            return dmac_scan_proc_scan_complete_event(pst_dmac_vap, MAC_SCAN_REFUSED);
        }
        else
        {
            return OAL_FAIL;
        }
    }

    /* ����device��ǰɨ��״̬Ϊ����״̬ */
    pst_mac_device->en_curr_scan_state = MAC_SCAN_STATE_RUNNING;
    pst_mac_device->ul_scan_timestamp  = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ������ɨ��Ȩ�޺󣬽�ɨ�����������mac deivce�ṹ���£���ʱ������Ҳ��Ϊ�˷�ֹɨ�������������� */
    oal_memcopy(&(pst_mac_device->st_scan_params), pst_scan_req_params, OAL_SIZEOF(mac_scan_req_stru));

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P0 ɨ��ʱ��¼P2P listen channel */
    if (OAL_TRUE == pst_scan_req_params->bit_is_p2p0_scan)
    {
        pst_dmac_vap->st_vap_base_info.uc_p2p_listen_channel = pst_scan_req_params->uc_p2p0_listen_channel;
    }
#endif
    /* ��ʼ��ɨ���ŵ����� */
    pst_mac_device->uc_scan_chan_idx = 0;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* proxysta ֻɨ��һ���ŵ� */
        if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta) &&
            (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            pst_mac_device->uc_scan_chan_idx = pst_mac_device->uc_sta0_chan_idx;
        }
    }
#endif

    dmac_scan_switch_channel_off(pst_mac_device);

    /* ɨ�迪ʼʱ�������Ƿ������ɨ�裬��������vap��mac addr */
    dmac_scan_set_vap_mac_addr_by_scan_state(pst_mac_device, OAL_TRUE);

    /* ����ŵ�������� */
    OAL_MEMZERO(&(pst_mac_device->st_chan_result), OAL_SIZEOF(mac_scan_chan_stats_stru));

    dmac_scan_begin(pst_mac_device);

 /* ������ʼ��֪ͨBT */
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT9, 9);   // �������̿�ʼ
    hal_coex_sw_irq_set(BIT5);
#endif

    return OAL_SUCC;
}
OAL_STATIC oal_void dmac_scan_prepare_pno_scan_params(mac_scan_req_stru  *pst_scan_params,
                                                                  oal_uint8           uc_vap_id)
{
    oal_uint32      ul_ret;
    oal_uint8       auc_bcst_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    oal_uint8       uc_chan_idx;
    oal_uint8       uc_2g_chan_num = 0;
    oal_uint8       uc_5g_chan_num = 0;
    oal_uint8       uc_chan_number;

    /* ɨ������������� */
    OAL_MEMZERO(pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    /* ���÷���ɨ���vap id */
    pst_scan_params->uc_vap_id = uc_vap_id;

    /* ���ó�ʼɨ������Ĳ��� */
    pst_scan_params->en_bss_type    = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_scan_params->en_scan_type   = WLAN_SCAN_TYPE_ACTIVE;
    pst_scan_params->en_scan_mode   = WLAN_SCAN_MODE_BACKGROUND_PNO;
    pst_scan_params->us_scan_time   = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    pst_scan_params->uc_probe_delay = 0;
    pst_scan_params->uc_scan_func   = MAC_SCAN_FUNC_BSS;   /* Ĭ��ɨ��bss */
    pst_scan_params->uc_max_scan_count_per_channel = WLAN_DEFAULT_FG_SCAN_COUNT_PER_CHANNEL;   /* �ǹ����µ�ɨ�裬ÿ�ŵ�ɨ��2�� */
    pst_scan_params->uc_max_send_probe_req_count_per_channel = WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL;

    /* ����ɨ�������ssid��Ϣ */
    pst_scan_params->ac_ssid[0][0] = '\0';   /* ͨ��ssid */
    pst_scan_params->uc_ssid_num = 1;

    /* ����ɨ������ָֻ��1��bssid��Ϊ�㲥��ַ */
    oal_set_mac_addr(pst_scan_params->auc_bssid[0], auc_bcst_addr);
    pst_scan_params->uc_bssid_num = 1;

    /* 2G��ʼɨ���ŵ�, ȫ�ŵ�ɨ�� */
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
    {
        /* �ж��ŵ��ǲ����ڹ������� */
        ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_number);

            pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_chan_number = uc_chan_number;
            pst_scan_params->ast_channel_list[uc_2g_chan_num].en_band        = WLAN_BAND_2G;
            pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_idx         = uc_chan_idx;
            pst_scan_params->uc_channel_nums++;
            uc_2g_chan_num++;
        }
    }
    //OAM_INFO_LOG1(0, OAM_SF_SCAN, "{dmac_scan_prepare_pno_scan_params::after regdomain filter, the 2g total channel num is %d", uc_2g_chan_num);

    /* 5G��ʼɨ���ŵ�, ȫ�ŵ�ɨ�� */
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
    {
        /* �ж��ŵ��ǲ����ڹ������� */
        ul_ret = mac_is_channel_idx_valid(WLAN_BAND_5G, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_chan_idx, &uc_chan_number);

            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_chan_number = uc_chan_number;
            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].en_band        = WLAN_BAND_5G;
            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_idx         = uc_chan_idx;
            pst_scan_params->uc_channel_nums++;
            uc_5g_chan_num++;
        }
    }
    //OAM_INFO_LOG1(0, OAM_SF_SCAN, "{dmac_scan_prepare_pno_scan_params::after regdomain filter, the 5g total channel num is %d", uc_5g_chan_num);

    return;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*lint -e528*/
OAL_STATIC oal_void  dmac_scan_pno_scan_timeout_fn(void *p_ptr, void *p_arg)
{
    dmac_vap_stru                       *pst_dmac_vap;
    mac_device_stru                     *pst_mac_device;
    mac_scan_req_stru                    st_scan_req_params;

    OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_pno_scan_timeout_fn::pno scan timer time out.}");
    OAL_IO_PRINT("dmac_scan_pno_scan_timeout_fn::pno scan timer time out.\r\n");

    pst_dmac_vap = (dmac_vap_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_pno_scan_timeout_fn::pst_dmac_vap null.}");
        return;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{dmac_scan_pno_scan_timeout_fn::pst_mac_device null.}");
        return;
    }
#ifdef _PRE_WLAN_FEATURE_STA_PM
    //PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);
#endif

#if 0
    /* ����pno����ɨ��Ĵ��� */
    pst_mac_device->pst_pno_sched_scan_mgmt->uc_curr_pno_sched_scan_times++;

    /* pno����ɨ�赽������ظ�������ֹͣɨ�����͹��� */
    if (pst_mac_device->pst_pno_sched_scan_mgmt->uc_curr_pno_sched_scan_times >= pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.uc_pno_scan_repeat)
    {
        /* ֹͣPNOɨ�裬������͹��� */
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{dmac_scan_pno_scan_timeout_fn:: reached max pno scan repeat times, stop pno sched scan.}");

#ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_PNO_SCHED_SCAN_COMP, 0, OAL_PTR_NULL);
#endif
        /* �ͷ�PNO����ṹ���ڴ� */
        OAL_MEM_FREE(pst_mac_device->pst_pno_sched_scan_mgmt, OAL_TRUE);
        pst_mac_device->pst_pno_sched_scan_mgmt = OAL_PTR_NULL;
        return OAL_SUCC;
    }
#endif

    /* ��ʼ������Ϊ: δɨ�赽ƥ���bss */
    pst_mac_device->pst_pno_sched_scan_mgmt->en_is_found_match_ssid = OAL_FALSE;

    /* ׼��OBSSɨ�������׼������ɨ�� */
    dmac_scan_prepare_pno_scan_params(&st_scan_req_params, pst_dmac_vap->st_vap_base_info.uc_vap_id);

    /* ����֡���˼Ĵ��� */
    hal_set_rx_filter(pst_mac_device->pst_device_stru, 0x37B9CEEA);

    /* ���·���ɨ�� */
    dmac_scan_handle_scan_req_entry(pst_mac_device, pst_dmac_vap, &st_scan_req_params);

    /* ��������PNO����ɨ�趨ʱ�� */
    dmac_scan_start_pno_sched_scan_timer((void *)pst_dmac_vap);

    return;
}
#endif
OAL_STATIC oal_uint32  dmac_scan_start_pno_sched_scan_timer(void *p_arg)
{
#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_TEST_MODE != _PRE_TEST_MODE_UT))
    dmac_vap_stru                           *pst_dmac_vap = (dmac_vap_stru *)p_arg;
    mac_device_stru                         *pst_mac_device;
    mac_pno_sched_scan_mgmt_stru            *pst_pno_mgmt;
    oal_int32                                l_ret = OAL_SUCC;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN,
                       "{dmac_scan_start_pno_sched_scan_timer:: pst_mac_device is null.}");
        return OAL_FAIL;
    }

    /* ��ȡpno����ṹ�� */
    pst_pno_mgmt = pst_mac_device->pst_pno_sched_scan_mgmt;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* �ж�pno����ɨ���rtcʱ�Ӷ�ʱ���Ƿ��Ѿ����������δ�����������´���������ֱ���������� */
    if (OAL_PTR_NULL == pst_pno_mgmt->p_pno_sched_scan_timer)
    {
        pst_pno_mgmt->p_pno_sched_scan_timer = (oal_void *)oal_rtctimer_create(dmac_scan_pno_scan_timeout_fn, p_arg);
        if (OAL_PTR_NULL == pst_pno_mgmt->p_pno_sched_scan_timer)
        {
            OAM_WARNING_LOG0(0, OAM_SF_SCAN,
                           "{dmac_scan_start_pno_sched_scan_timer:: create pno timer faild.}");
            return OAL_FAIL;
        }
    }
#endif

    /* �����Ϸ��Լ�飬ʱ�������̣�pno����ִֻ��һ�� */
    if (0 == pst_pno_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval / 100)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN,
                         "{dmac_scan_start_pno_sched_scan_timer:: pno scan interval[%d] time too short.}",
                         pst_pno_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval);
        return OAL_FAIL;
    }

    /* ������ʱ�����ϲ��·���ɨ�����Ǻ��뼶�ģ�����ʱ����100���뼶�ģ������Ҫ����100 */
    l_ret = oal_rtctimer_start((STIMER_STRU *)pst_pno_mgmt->p_pno_sched_scan_timer, pst_pno_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval / 100);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN,
                         "{dmac_scan_start_pno_sched_scan_timer:: start pno timer faild.}");
        return OAL_FAIL;
    }

    OAM_WARNING_LOG1(0, OAM_SF_SCAN,
                     "{dmac_scan_start_pno_sched_scan_timer:: start pno timer succ, timeout[%d].}",
                     pst_pno_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval / 100);
#else
    /* 1151��֧�֣��Ҳ����ߵ��˴���do nothing����Ҫԭ��ƽ̨��δ��װ��ʱ����ؽӿ� */
#endif

    return OAL_SUCC;
}


oal_uint32  dmac_scan_stop_pno_sched_scan_timer(void *p_arg)
{
#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_TEST_MODE != _PRE_TEST_MODE_UT))
    mac_pno_sched_scan_mgmt_stru    *pst_pno_mgmt;
    oal_int32                        l_ret;

    pst_pno_mgmt = (mac_pno_sched_scan_mgmt_stru *)p_arg;

    /* �����ʱ�������ڣ�ֱ�ӷ��� */
    if (OAL_PTR_NULL == pst_pno_mgmt->p_pno_sched_scan_timer)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN,
                         "{dmac_scan_stop_pno_sched_scan_timer:: pno sched timer not create yet.}");
        return OAL_SUCC;
    }

    /* ֹͣ��ʱ�� */
    l_ret = oal_rtctimer_stop((STIMER_STRU *)pst_pno_mgmt->p_pno_sched_scan_timer);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN,
                         "{dmac_scan_stop_pno_sched_scan_timer:: stop pno sched timer failed.}");
    }

    /* ɾ����ʱ�� */
    oal_rtctimer_delete((STIMER_STRU *)pst_pno_mgmt->p_pno_sched_scan_timer);
    pst_pno_mgmt->p_pno_sched_scan_timer = OAL_PTR_NULL;
#else
    /* 1151��֧�֣��Ҳ����ߵ��˴���do nothing����Ҫԭ��ƽ̨��δ��װ��ʱ����ؽӿ� */
#endif

    return OAL_SUCC;
}


oal_uint32  dmac_scan_proc_sched_scan_req_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_vap_stru              *pst_dmac_vap;
    mac_device_stru            *pst_mac_device;
    mac_scan_req_stru           st_scan_req_params;

    OAL_IO_PRINT("dmac_scan_proc_sched_scan_req_event::enter here.\r\n");

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼���Ϣ */
    pst_event        = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_event_hdr    = &(pst_event->st_event_hdr);

    /* ��ȡdmac vap */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ׼��pnoɨ��������� */
    dmac_scan_prepare_pno_scan_params(&st_scan_req_params, pst_dmac_vap->st_vap_base_info.uc_vap_id);

    /* ����PNO����ɨ��Ĵ���Ϊ0 */
    pst_mac_device->pst_pno_sched_scan_mgmt->uc_curr_pno_sched_scan_times = 0;
    pst_mac_device->pst_pno_sched_scan_mgmt->en_is_found_match_ssid = OAL_FALSE;

    /* ����֡���˼Ĵ��� */
    hal_set_rx_filter(pst_mac_device->pst_device_stru, 0x37B9CEEA);

    /* ����ɨ����ڣ�ִ��ɨ�� */
    dmac_scan_handle_scan_req_entry(pst_mac_device, pst_dmac_vap, &st_scan_req_params);

    /* ����pno����ɨ���rtcʱ�Ӷ�ʱ�����ɻ�����˯��device */
    dmac_scan_start_pno_sched_scan_timer((void *)pst_dmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_proc_scan_req_event
 ��������  : �����ϲ��·���ɨ�������¼�������ɨ����ں�������ɨ��
 �������  : pst_event_mem: �¼��ڴ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_scan_proc_scan_req_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_vap_stru              *pst_dmac_vap;
    mac_device_stru            *pst_mac_device;
    mac_scan_req_stru          *pst_h2d_scan_req_params;

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_scan_req_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼���Ϣ */
    pst_event        = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_event_hdr    = &(pst_event->st_event_hdr);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_scan_req_event::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_scan_proc_scan_req_event::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ��ɨ��������� */
    pst_h2d_scan_req_params = (mac_scan_req_stru *)frw_get_event_payload(pst_event_mem);

    /* host�෢���ɨ������Ĵ��� */
    return dmac_scan_handle_scan_req_entry(pst_mac_device, pst_dmac_vap, pst_h2d_scan_req_params);
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
OAL_STATIC oal_uint32 dmac_scan_prepare_obss_scan_params(mac_scan_req_stru  *pst_scan_params,
                                                         dmac_vap_stru      *pst_dmac_vap)
{
    oal_uint32 ul_ret;
    oal_uint8  auc_bcst_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    oal_uint8  uc_2g_chan_num      = 0;
    oal_uint8  uc_channel_idx      = 0;
    oal_uint8  uc_low_channel_idx  = 0;
    oal_uint8  uc_high_channel_idx = 0;
    oal_uint8  uc_channel_num      = 0;
    oal_uint8  uc_curr_channel_num = pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number;
    oal_uint8  uc_curr_band        = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

    //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_update_obss_scan_params::update obss scan params.}");

    OAL_MEMZERO(pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    /* 1.���÷���ɨ���vap id */
    pst_scan_params->uc_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    /* 2.���ó�ʼɨ������Ĳ��� */
    pst_scan_params->en_bss_type         = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_scan_params->en_scan_type        = WLAN_SCAN_TYPE_ACTIVE;
    pst_scan_params->uc_probe_delay      = 0;
    pst_scan_params->uc_scan_func        = MAC_SCAN_FUNC_BSS;               /* Ĭ��ɨ��bss */
    pst_scan_params->uc_max_send_probe_req_count_per_channel = WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL;
    pst_scan_params->uc_max_scan_count_per_channel           = WLAN_DEFAULT_BG_SCAN_COUNT_PER_CHANNEL;

    /* ����ɨ�����ͣ�ȷ��ÿ�ŵ�ɨ��ʱ�� */
    if (WLAN_SCAN_TYPE_ACTIVE == pst_scan_params->en_scan_type)
    {
        pst_scan_params->us_scan_time = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    }
    else
    {
        pst_scan_params->us_scan_time = WLAN_DEFAULT_PASSIVE_SCAN_TIME;
    }

    /* OBSSɨ��ͨ��ssid */
    pst_scan_params->ac_ssid[0][0] = '\0';
    pst_scan_params->uc_ssid_num = 1;

    /* OBSSɨ��ɨ��ָֻ��1��bssid��Ϊ�㲥��ַ */
    oal_set_mac_addr(pst_scan_params->auc_bssid[0], auc_bcst_addr);
    pst_scan_params->uc_bssid_num = 1;

    /* ����ɨ��ģʽΪOBSSɨ�� */
    pst_scan_params->en_scan_mode = WLAN_SCAN_MODE_BACKGROUND_OBSS;

    /* ׼��OBSSɨ����ŵ� */
    if (WLAN_BAND_2G == uc_curr_band)
    {

        /* �ӵ�ǰ�ŵ�����ƫ��5���ŵ�������OBSSɨ���ŵ�
           1) ��ǰ�ŵ�idxС�ڵ���5�����0��ʼ����idx+5,
           2) ����5С��8��Ӧ�ô�idx-5��idx+5,
           3) ����8�����Ǵ�idx-5��13 */
        if (uc_curr_channel_num <= 5)
        {
            uc_low_channel_idx = 0;
            uc_high_channel_idx = uc_curr_channel_num + 5;
        }
        else if (5 < uc_curr_channel_num && uc_curr_channel_num <= 8)
        {
            uc_low_channel_idx  = uc_curr_channel_num - 5;
            uc_high_channel_idx = uc_curr_channel_num + 5;
        }
        else if (8 < uc_curr_channel_num && uc_curr_channel_num <= 13)
        {
            uc_low_channel_idx = uc_curr_channel_num - 5;
            uc_high_channel_idx = 13;
        }
        else
        {
            uc_low_channel_idx  = 0;
            uc_high_channel_idx = 0;
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_update_obss_scan_params::2040M,Current channel index is %d.}",
                           uc_curr_channel_num);
        }

        /* ׼��2.4G��OBSSɨ���ŵ� */
        for(uc_channel_idx = uc_low_channel_idx; uc_channel_idx <= uc_high_channel_idx; uc_channel_idx++)
        {
            /* �ж��ŵ��ǲ����ڹ������� */
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_channel_idx);
            if (OAL_SUCC == ul_ret)
            {
                mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_channel_idx, &uc_channel_num);

                pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_chan_number = uc_channel_num;
                pst_scan_params->ast_channel_list[uc_2g_chan_num].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_idx         = uc_channel_idx;
                pst_scan_params->uc_channel_nums++;
                uc_2g_chan_num++;
            }
        }

        /* ���±���ɨ����ŵ����� */
        pst_scan_params->uc_channel_nums = uc_2g_chan_num;
    }
#if 0
    else if (WLAN_BAND_5G == uc_curr_band)
    {
        /* ��ʱ������5G�µ�obssɨ�� */
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_update_obss_scan_params::5G don't do obss scan.}");
    }
    else
    {
        OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_update_obss_scan_params::error band[%d].}", uc_curr_band);
    }
#endif
    /* �����ǰɨ���ŵ�������Ϊ0�����ش��󣬲�ִ��ɨ������ */
    if (0 == pst_scan_params->uc_channel_nums)
    {
        OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_update_obss_scan_params::scan total channel num is 0, band[%d]!}", uc_curr_band);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : dmac_scan_after_p2pgo_send_noa
 ��������  : p2p go����ɨ�跢����NoA�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_scan_after_p2pgo_send_noa(void *p_arg)
{
    dmac_vap_stru       *pst_dmac_vap = (dmac_vap_stru *)p_arg;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "after go send noa, now switch channel");
    dmac_scan_switch_channel_off(pst_mac_device);
    /* ɨ�迪ʼʱ�������Ƿ������ɨ�裬��������vap��mac addr */
    dmac_scan_set_vap_mac_addr_by_scan_state(pst_mac_device, OAL_TRUE);
    /* ����ŵ�������� */
    OAL_MEMZERO(&(pst_mac_device->st_chan_result), OAL_SIZEOF(mac_scan_chan_stats_stru));
    dmac_scan_begin(pst_mac_device);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_scan_obss_timeout_fn(void *p_arg)
{
    dmac_vap_stru          *pst_dmac_vap;
    mac_device_stru        *pst_mac_device;
    mac_scan_req_stru       st_scan_req_params;
    oal_uint32              ul_ret;
    oal_uint8               uc_scan_now = OAL_FALSE;

    //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_obss_timeout_fn::obss timer time out.}");

    pst_dmac_vap = (dmac_vap_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_obss_timeout_fn::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{dmac_scan_obss_timeout_fn::pst_mac_device null.}");
        return OAL_FAIL;
    }

    /* �����obss scan timer�����ڼ䶯̬�޸���sta��������sta��֧��obssɨ�裬
     * ��ر�obss scan timer
     * �˴���Ψһ��ֹobssɨ��ĵط�!!!
     */
    if (OAL_FALSE == dmac_mgmt_need_obss_scan(&pst_dmac_vap->st_vap_base_info))
    {
        pst_dmac_vap->ul_obss_scan_timer_remain  = 0;
        pst_dmac_vap->uc_obss_scan_timer_started = OAL_FALSE;
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
        //            "{dmac_scan_obss_timeout_fn::stop obss scan timer}");
        return OAL_SUCC;
    }

    if (0 == pst_dmac_vap->ul_obss_scan_timer_remain)
    {
        uc_scan_now = OAL_TRUE;
    }

    dmac_scan_start_obss_timer(&pst_dmac_vap->st_vap_base_info);

    /* ����ɨ����ڣ�ִ��obssɨ�� */
    if (OAL_TRUE == uc_scan_now)
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
        //            "{dmac_scan_obss_timeout_fn:: start scan}");

        /* ׼��OBSSɨ�������׼������ɨ�� */
        ul_ret = dmac_scan_prepare_obss_scan_params(&st_scan_req_params, pst_dmac_vap);
        if (OAL_SUCC != ul_ret)
        {
            //OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{dmac_scan_obss_timeout_fn::update scan params error[%d].}", ul_ret);
            return ul_ret;
        }

        return dmac_scan_handle_scan_req_entry(pst_mac_device, pst_dmac_vap, &st_scan_req_params);
    }

    return OAL_SUCC;
}


oal_void dmac_scan_start_obss_timer(mac_vap_stru *pst_mac_vap)
{
    dmac_vap_stru                 *pst_dmac_vap;
    mac_device_stru               *pst_mac_device;
    oal_uint32                    ul_new_timer;

    /* ���ݷ���ɨ���vap id��ȡdmac vap */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_start_obss_timer:: pst_dmac_vap is NULL.}");
        return;
    }

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{dmac_scan_start_obss_timer::pst_mac_device null.}");
        return;
    }

    /* ����ɨ�趨ʱ�� */
    if (0 == pst_dmac_vap->ul_obss_scan_timer_remain)
    {
        pst_dmac_vap->ul_obss_scan_timer_remain = 1000*mac_mib_get_BSSWidthTriggerScanInterval(&pst_dmac_vap->st_vap_base_info);
    }

    ul_new_timer = pst_dmac_vap->ul_obss_scan_timer_remain > DMAC_SCAN_MAX_TIMER?
                        DMAC_SCAN_MAX_TIMER:pst_dmac_vap->ul_obss_scan_timer_remain;
    pst_dmac_vap->ul_obss_scan_timer_remain -= ul_new_timer;
    OAM_INFO_LOG2(0, OAM_SF_SCAN, "{dmac_scan_start_obss_timer::remain=%d new_timer=%d}",
                pst_dmac_vap->ul_obss_scan_timer_remain, ul_new_timer);

    FRW_TIMER_CREATE_TIMER(&(pst_mac_device->st_obss_scan_timer),
                           dmac_scan_obss_timeout_fn,
                           ul_new_timer,
                           (void *)pst_dmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);
    pst_dmac_vap->uc_obss_scan_timer_started = OAL_TRUE;

    return;
}
#endif
OAL_STATIC oal_void  dmac_scan_switch_channel_notify_alg(dmac_vap_stru     *pst_dmac_vap,
                                                                   mac_channel_stru  *pst_channel)
{
    mac_channel_stru                st_channel_tmp;

    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_channel))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{dmac_scan_switch_channel_notify_alg::pst_dmac_vap[%p], pst_channel[%p].}",
                       pst_dmac_vap, pst_channel);
        return;
    }

    /* ��¼��ǰvap�µ��ŵ���Ϣ */
    st_channel_tmp = pst_dmac_vap->st_vap_base_info.st_channel;

    /* ��¼Ҫ�л����ŵ���Ƶ�Σ��л��ŵ� */
    pst_dmac_vap->st_vap_base_info.st_channel.en_band        = pst_channel->en_band;
    pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number = pst_channel->uc_chan_number;
    pst_dmac_vap->st_vap_base_info.st_channel.uc_idx         = pst_channel->uc_idx;
    pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;

    /* ֪ͨ�㷨 */
    dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_SCAN);
    dmac_alg_cfg_bandwidth_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_SCAN);

    /* ֪ͨ�㷨�󣬻ָ�vapԭ���ŵ���Ϣ */
    pst_dmac_vap->st_vap_base_info.st_channel = st_channel_tmp;

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_switch_channel_off
 ��������  : ��VAP������֡�ķ�ʽ�����ŵ�
 �������  : pst_mac_device : mac device
             pst_mac_vap    : Ҫ������֡��VAP
             pst_dst_chl    : Ŀ���ŵ�
             us_protect_time: ���뱣��ʱ�䣬ms
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_switch_channel_off(
                mac_device_stru     *pst_mac_device,
                mac_vap_stru        *pst_mac_vap,
                mac_channel_stru    *pst_dst_chl,
                oal_uint16           us_protect_time)
{
    mac_fcs_mgr_stru               *pst_fcs_mgr;
    mac_fcs_cfg_stru               *pst_fcs_cfg;

    /* ��¼������ŵ�����ɨ������л� */
    pst_mac_device->st_home_channel = pst_mac_vap->st_channel;

    pst_fcs_mgr = dmac_fcs_get_mgr_stru(pst_mac_device);
    pst_fcs_cfg = &(pst_mac_device->st_fcs_cfg);

    OAL_MEMZERO(pst_fcs_cfg, OAL_SIZEOF(mac_fcs_cfg_stru));

    pst_fcs_cfg->st_src_chl = pst_mac_vap->st_channel;
    pst_fcs_cfg->st_dst_chl = *pst_dst_chl;

    mac_fcs_prepare_one_packet_cfg(pst_mac_vap, &(pst_fcs_cfg->st_one_packet_cfg), us_protect_time);

    /* ����FCS���ŵ��ӿ� ���浱ǰӲ�����е�֡��ɨ����ٶ��� */
    mac_fcs_start(pst_fcs_mgr, pst_fcs_cfg, 0, HAL_TX_FAKE_QUEUE_BGSCAN_ID);
    mac_fcs_release(pst_fcs_mgr);

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_DBAC, "{dmac_scan_switch_channel_off::switch src channel[%d] to dst channel[%d].}",
                  pst_mac_vap->st_channel.uc_chan_number, pst_fcs_cfg->st_dst_chl.uc_chan_number);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_switch_channel_off_enhanced
 ��������  : ��VAP����ɨ��ʱ ���빤���ŵ��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_switch_channel_off_enhanced(
                mac_device_stru     *pst_mac_device,
                mac_vap_stru        *pst_mac_vap1,
                mac_vap_stru        *pst_mac_vap2,
                mac_channel_stru    *pst_dst_chl,
                oal_uint16           us_protect_time)
{
    mac_fcs_mgr_stru               *pst_fcs_mgr;
    mac_fcs_cfg_stru               *pst_fcs_cfg;
    mac_vap_stru                   *pst_vap_sta;
#ifdef _PRE_WLAN_FEATURE_DBAC
    mac_vap_stru                   *pst_current_chan_vap;   /* ��ǰ�ŵ��ϵ�VAP */
    oal_uint8                       uc_fake_q_id = 0;
#endif

    /* ��¼����ʱ��������ŵ�����ͬƵ����ɨ������л� */
    if (pst_mac_vap1->st_channel.en_bandwidth >= pst_mac_vap2->st_channel.en_bandwidth)
    {
        pst_mac_device->st_home_channel = pst_mac_vap1->st_channel;
    }
    else
    {
        pst_mac_device->st_home_channel = pst_mac_vap2->st_channel;
    }

    /* ��ͣ����VAP�ķ��� */
    dmac_vap_pause_tx(pst_mac_vap1);
    dmac_vap_pause_tx(pst_mac_vap2);

    pst_fcs_mgr = dmac_fcs_get_mgr_stru(pst_mac_device);
    pst_fcs_cfg = &(pst_mac_device->st_fcs_cfg);
    OAL_MEMZERO(pst_fcs_cfg, OAL_SIZEOF(mac_fcs_cfg_stru));

    pst_fcs_cfg->st_dst_chl = *pst_dst_chl;

    OAM_INFO_LOG2(0, OAM_SF_DBAC, "{dmac_switch_channel_off_enhanced::curr hal chan[%d], dst channel[%d].}",
                  pst_mac_device->pst_device_stru->uc_current_chan_number,
                  pst_fcs_cfg->st_dst_chl.uc_chan_number);

#ifdef _PRE_WLAN_FEATURE_DBAC
    /* ��Ƶģʽֻ��Ҫ��һ��one packet */
    if (mac_is_dbac_running(pst_mac_device))
    {
        /* ��ͣDBAC���ŵ� */
        dmac_alg_dbac_pause(pst_mac_device);

        if (pst_mac_device->pst_device_stru->uc_current_chan_number == pst_mac_vap1->st_channel.uc_chan_number)
        {
            pst_current_chan_vap = pst_mac_vap1;
        }
        else
        {
            pst_current_chan_vap = pst_mac_vap2;
        }

        mac_fcs_get_fake_q_id(pst_current_chan_vap, &uc_fake_q_id);

        pst_fcs_cfg->st_src_chl = pst_current_chan_vap->st_channel;
        mac_fcs_prepare_one_packet_cfg(pst_current_chan_vap, &(pst_fcs_cfg->st_one_packet_cfg), us_protect_time);

        OAM_INFO_LOG2(pst_current_chan_vap->uc_vap_id, OAM_SF_DBAC, "switch chan off when dbac running. curr chan num:%d, fake_q_id:%d",
                        pst_current_chan_vap->st_channel.uc_chan_number, uc_fake_q_id);
        if (pst_mac_device->pst_device_stru->uc_current_chan_number != pst_current_chan_vap->st_channel.uc_chan_number)
        {
            OAM_WARNING_LOG2(0, OAM_SF_DBAC, "switch chan off when dbac running. hal chan num:%d, curr vap chan num:%d. not same,do not send protect frame",
                            pst_mac_device->pst_device_stru->uc_current_chan_number,
                            pst_current_chan_vap->st_channel.uc_chan_number);

            pst_fcs_cfg->st_one_packet_cfg.en_protect_type = HAL_FCS_PROTECT_TYPE_NONE;
        }

        mac_fcs_start(pst_fcs_mgr, pst_fcs_cfg, 0, uc_fake_q_id);
        mac_fcs_release(pst_fcs_mgr);
    }
    else
#endif
    {
        /* ͬƵ˫STAģʽ����Ҫ������one packet */
        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap1->en_vap_mode && WLAN_VAP_MODE_BSS_STA == pst_mac_vap2->en_vap_mode)
        {
            /* ׼��VAP1��fcs���� */
            pst_fcs_cfg->st_src_chl = pst_mac_vap1->st_channel;
            mac_fcs_prepare_one_packet_cfg(pst_mac_vap1, &(pst_fcs_cfg->st_one_packet_cfg), us_protect_time);

            /* ׼��VAP2��fcs���� */
            pst_fcs_cfg->st_src_chl2 = pst_mac_vap2->st_channel;
            mac_fcs_prepare_one_packet_cfg(pst_mac_vap2, &(pst_fcs_cfg->st_one_packet_cfg2), us_protect_time);
            pst_fcs_cfg->st_one_packet_cfg2.us_timeout = MAC_FCS_DEFAULT_PROTECT_TIME_OUT2;     /* ��С�ڶ���one packet�ı���ʱ�����Ӷ�������ʱ�� */

            OAM_INFO_LOG0(0, OAM_SF_DBAC, "switch chan off when dual sta.");
            mac_fcs_start_enhanced(pst_fcs_mgr, pst_fcs_cfg);
            mac_fcs_release(pst_fcs_mgr);
        }
        /* ͬƵSTA+GOģʽ��ֻ��ҪSTA��һ��one packet */
        else
        {
            if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap1->en_vap_mode)
            {
                pst_vap_sta = pst_mac_vap1;
            }
            else
            {
                pst_vap_sta = pst_mac_vap2;
            }

            pst_fcs_cfg->st_src_chl = pst_vap_sta->st_channel;
            mac_fcs_prepare_one_packet_cfg(pst_vap_sta, &(pst_fcs_cfg->st_one_packet_cfg), us_protect_time);

            OAM_INFO_LOG0(pst_vap_sta->uc_vap_id, OAM_SF_DBAC, "switch chan off when sta+go");
            /* ����FCS���ŵ��ӿ� ���浱ǰӲ�����е�֡��ɨ����ٶ��� */
            mac_fcs_start(pst_fcs_mgr, pst_fcs_cfg, 0, HAL_TX_FAKE_QUEUE_BGSCAN_ID);
            mac_fcs_release(pst_fcs_mgr);
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_scan_switch_channel_off
 ��������  : ɨ������home�ŵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_scan_switch_channel_off(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                   *pst_mac_vap;    /* Ҫ������֡��VAP */
    wlan_scan_mode_enum_uint8       en_scan_mode;
    dmac_vap_stru                  *pst_dmac_vap;   /* ����ɨ���VAP */
    oal_uint8                       uc_up_vap_num;
    oal_uint32                      ul_ret;
    mac_vap_stru                   *pst_mac_vap2;

    en_scan_mode = pst_mac_device->st_scan_params.en_scan_mode;

    if (en_scan_mode >= WLAN_SCAN_MODE_BUTT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_switch_channel_off::scan mode[%d] is invalid.}", en_scan_mode);
        return;
    }

    /* �����CCA�㷨�Ż������ɨ�裬�������ŵ� */
    if (WLAN_SCAN_MODE_BACKGROUND_CCA == en_scan_mode)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_switch_channel_off::CCA ALG scan, don't need switch channel.}");
        return;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->st_scan_params.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_switch_channel_off::pst_dmac_vap null.}");
        return;
    }

    /* ���ŵ�֮ǰ ֪ͨ�㷨 */
    dmac_scan_switch_channel_notify_alg(pst_dmac_vap, &(pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]));

    /* ǰ��ɨ�����PNO�����ɨ��(ע: PNOֻ���豸δ������״̬�²ŷ���ɨ��) ֱ�����ŵ� */
    if ((WLAN_SCAN_MODE_FOREGROUND == en_scan_mode) || (WLAN_SCAN_MODE_BACKGROUND_PNO == en_scan_mode))
    {
    #ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if ((OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta) && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* proxysta�����ŵ� */
            OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_switch_channel_off::proxysta DO NOT switch channnel.}");
            return;
        }
    #endif

        OAM_INFO_LOG1(0, OAM_SF_DBAC, "dmac_scan_switch_channel_off:: foreground scan, switch channel to %d",
                        pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx].uc_chan_number);
        dmac_mgmt_switch_channel(pst_mac_device, &pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]);
        return;
    }

    /****** ����ɨ�裬����FCS�ӿ����ŵ� ************/
    uc_up_vap_num = (oal_uint8)mac_device_calc_up_vap_num(pst_mac_device);

    if (1 == uc_up_vap_num)
    {
        ul_ret = mac_device_find_up_vap(pst_mac_device, &pst_mac_vap);
        if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_switch_channel_off::up vap is null ptr.}");
            return;
        }

        /* ��ͣ��VAP���� */
        dmac_vap_pause_tx(pst_mac_vap);

        /* �����ŵ� */
        dmac_switch_channel_off(pst_mac_device,
                                pst_mac_vap,
                                &(pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]),
                                pst_mac_device->st_scan_params.us_scan_time);
    }
    else if (2 == uc_up_vap_num)
    {
        ul_ret = mac_device_find_2up_vap(pst_mac_device, &pst_mac_vap, &pst_mac_vap2);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_SCAN, "mac_device_find_2up_vap return fail.");
            return;
        }

        dmac_switch_channel_off_enhanced(pst_mac_device,
                                         pst_mac_vap,
                                         pst_mac_vap2,
                                         &(pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]),
                                         pst_mac_device->st_scan_params.us_scan_time);
    }
    else
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "not support 3+ vap now");
    }
}

/*****************************************************************************
 �� �� ��  : dmac_scan_switch_channel_back
 ��������  : ����ɨ���л�home�ŵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_scan_switch_channel_back(mac_device_stru *pst_mac_device)
{
    /* ���Ӳ������ */
    dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);

    if (mac_is_dbac_running(pst_mac_device))
    {
        /* dbac����ֻ��ָ�dbac����dbac�����е������ŵ� */
        dmac_alg_dbac_resume(pst_mac_device);

        return;
    }

    /* �лع���VAP���ڵ��ŵ� */
    OAM_INFO_LOG3(0, OAM_SF_DBAC, "dmac_scan_switch_channel_back::switch home channel[%d], bw[%d], restore tx queue from %d.",
                  pst_mac_device->st_home_channel.uc_chan_number,
                  pst_mac_device->st_home_channel.en_bandwidth,
                  HAL_TX_FAKE_QUEUE_BGSCAN_ID);
    dmac_mgmt_switch_channel(pst_mac_device, &(pst_mac_device->st_home_channel));

    /* ��ɨ����ٶ������֡�ָ���Ӳ��������ȥ */
    dmac_tx_restore_tx_queue(pst_mac_device->pst_device_stru, HAL_TX_FAKE_QUEUE_BGSCAN_ID);

    /* �ָ�home�ŵ��ϱ���ͣ�ķ��� */
    dmac_vap_resume_tx_by_chl(pst_mac_device, &(pst_mac_device->st_home_channel));

}
OAL_STATIC oal_bool_enum_uint8  dmac_scan_need_switch_home_channel(mac_device_stru *pst_mac_device)
{
    /* ����ɨ����Ҫ�лع����ŵ����Ҽ��6���ŵ��л�һ�� */
    if ((OAL_TRUE == pst_mac_device->st_scan_params.en_need_switch_back_home_channel) &&
        (0 == pst_mac_device->uc_scan_chan_idx % DMAC_SCAN_CHANNEL_INTERVAL))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
OAL_STATIC oal_uint32  dmac_scan_curr_channel_scan_time_out(void *p_arg)
{
    mac_device_stru        *pst_mac_device = (mac_device_stru *)p_arg;
    mac_scan_req_stru      *pst_scan_params;
    mac_channel_stru       *pst_next_scan_channel = OAL_PTR_NULL;
    dmac_vap_stru          *pst_dmac_vap;
    oal_uint8               uc_do_meas;

    /* ��ȡɨ����� */
    pst_scan_params = &(pst_mac_device->st_scan_params);

    /* ���±����ŵ���ɨ����� */
    pst_scan_params->uc_curr_channel_scan_count++;

    /* ����ɨ��������ŵ�ɨ�����������ж��Ƿ��л��ŵ��� */
    if (pst_scan_params->uc_curr_channel_scan_count >= pst_scan_params->uc_max_scan_count_per_channel)
    {
        /* ���ŵ�ɨ�����������·���ɨ�������Ҫ�ϱ��ŵ�ͳ����Ϣ�����ϱ���Ĭ�Ϲر� */
        uc_do_meas = pst_mac_device->st_scan_params.uc_scan_func & (MAC_SCAN_FUNC_MEAS | MAC_SCAN_FUNC_STATS);
        if (uc_do_meas)
        {
            /* �����CCA�Ż��㷨�����ɨ�裬�����ϱ��ŵ�������� */
            if (WLAN_SCAN_MODE_BACKGROUND_CCA != pst_mac_device->st_scan_params.en_scan_mode)
            {
                /* �ϱ��ŵ�������� */
                dmac_scan_report_channel_statistics_result(pst_mac_device, pst_mac_device->uc_scan_chan_idx);

                /* ����ŵ����������׼����һ���ŵ�����ֵ��ͳ�� */
                OAL_MEMZERO(&(pst_mac_device->st_chan_result), OAL_SIZEOF(mac_scan_chan_stats_stru));
            }
        }

        pst_mac_device->uc_scan_chan_idx += 1;              /* �л��ŵ� */
        pst_scan_params->uc_curr_channel_scan_count = 0;    /* ���ŵ�ɨ��������� */
    }
    else
    {
        /* ���ŵ�ɨ�����δ��ɣ������л��ŵ���ֱ�ӷ���ɨ�� */
        dmac_scan_begin(pst_mac_device);
        return OAL_SUCC;
    }

    /* �˴�ɨ��������ɣ���һЩ��β���� */
    if (pst_mac_device->uc_scan_chan_idx >= pst_mac_device->st_scan_params.uc_channel_nums)
    {
        dmac_scan_end(pst_mac_device);
        return OAL_SUCC;
    }

    /* ��ȡ����ɨ���dmac vap�ṹ��Ϣ */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->st_scan_params.uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* proxysta ֻɨ��һ���ŵ� */
        if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            dmac_scan_end(pst_mac_device);
            return OAL_SUCC;
        }
    }
#endif

    if (WLAN_SCAN_MODE_FOREGROUND == pst_mac_device->st_scan_params.en_scan_mode)
    {
        /* ��ȡ��һ��Ҫɨ����ŵ���Ϣ */
        pst_next_scan_channel = &(pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]);

        /* ���ŵ�ǰ֪ͨ�㷨 */
        dmac_scan_switch_channel_notify_alg(pst_dmac_vap, pst_next_scan_channel);

        dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);

        /* ǰ��ɨ�� ֱ�����ŵ�����ɨ�� */
        dmac_mgmt_switch_channel(pst_mac_device, pst_next_scan_channel);
        dmac_scan_begin(pst_mac_device);
    }
    else
    {
        /* ����ɨ�裬�ж��Ƿ���Ҫ���ع����ŵ�����һ��ʱ�䣬����ǣ����лع����ŵ����� */
        if (OAL_TRUE == dmac_scan_need_switch_home_channel(pst_mac_device))
        {
            dmac_scan_switch_home_channel_work(pst_mac_device);
        }
        else
        {
            /* ��ȡ��һ��Ҫɨ����ŵ���Ϣ */
            pst_next_scan_channel = &(pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx]);

            /* ���ŵ�ǰ֪ͨ�㷨 */
            dmac_scan_switch_channel_notify_alg(pst_dmac_vap, pst_next_scan_channel);

            dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);

            /* ���ŵ�����ɨ�� */
            dmac_mgmt_switch_channel(pst_mac_device, pst_next_scan_channel);
            dmac_scan_begin(pst_mac_device);
        }
    }

    return OAL_SUCC;
}


oal_void dmac_scan_begin(mac_device_stru *pst_mac_device)
{
    mac_scan_req_stru               *pst_scan_params;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint32                       ul_ret;
    oal_uint8                        uc_band;
    oal_uint8                        uc_do_radar_det;
    oal_uint8                        uc_do_bss_scan;
    oal_uint8                        uc_do_meas;
    oal_uint8                        uc_loop;
    oal_uint8                        uc_do_p2p_listen = 0;

    /* ��ȡɨ����� */
    pst_scan_params = &(pst_mac_device->st_scan_params);

    uc_band          = pst_scan_params->ast_channel_list[pst_mac_device->uc_scan_chan_idx].en_band;
    uc_do_radar_det  = pst_scan_params->uc_scan_func & MAC_SCAN_FUNC_RADAR;
    uc_do_bss_scan   = pst_scan_params->uc_scan_func & MAC_SCAN_FUNC_BSS;
    uc_do_p2p_listen = pst_scan_params->uc_scan_func & MAC_SCAN_FUNC_P2P_LISTEN;

    /* �����ǰɨ��ģʽ��Ҫͳ���ŵ���Ϣ����ʹ�ܶ�Ӧ�Ĵ��� */
    uc_do_meas = pst_scan_params->uc_scan_func & (MAC_SCAN_FUNC_MEAS | MAC_SCAN_FUNC_STATS);
    if (uc_do_meas)
    {
        /* ʹ���ŵ������ж� */
        hal_set_ch_statics_period(pst_mac_device->pst_device_stru, DMAC_SCAN_CHANNEL_STATICS_PERIOD_US);
        hal_set_ch_measurement_period(pst_mac_device->pst_device_stru, DMAC_SCAN_CHANNEL_MEAS_PERIOD_MS);
        hal_enable_ch_statics(pst_mac_device->pst_device_stru, 1);
    }

    /* ����ɨ�趨ʱ�� */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_scan_timer,
                           dmac_scan_curr_channel_scan_time_out,
                           pst_scan_params->us_scan_time,
                           pst_mac_device,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);

    /* �����״��� */
    hal_enable_radar_det(pst_mac_device->pst_device_stru, ((WLAN_BAND_5G == uc_band) && uc_do_radar_det) ? 1 : 0);

    /* ACTIVE��ʽ�·��͹㲥RPOBE REQ֡ */
    if (uc_do_bss_scan && (WLAN_SCAN_TYPE_ACTIVE == pst_scan_params->en_scan_type))
    {
        /* ÿ���ŵ����͵�probe req֡�ĸ��� */
        for (uc_loop = 0; uc_loop < pst_scan_params->uc_max_send_probe_req_count_per_channel; uc_loop++)
        {
            ul_ret = dmac_scan_send_bcast_probe(pst_mac_device, uc_band, uc_loop);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{dmac_scan_begin::dmac_scan_send_bcast_probe failed[%d].}", ul_ret);
            }
        }
    }

    /* p2p���������߼� */
    /* p2p listenʱ��Ҫ����VAP���ŵ�����probe rsp֡(DSSS ie, ht ie)��Ҫ��listen������ָ� */
    if (uc_do_p2p_listen)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_scan_params->uc_vap_id);

        pst_mac_device->st_p2p_vap_channel = pst_dmac_vap->st_vap_base_info.st_channel;

        pst_dmac_vap->st_vap_base_info.st_channel = pst_scan_params->ast_channel_list[0];
    }

    return;
}
oal_void dmac_scan_end(mac_device_stru *pst_mac_device)
{
    dmac_vap_stru              *pst_dmac_vap;
    wlan_scan_mode_enum_uint8   en_scan_mode = WLAN_SCAN_MODE_BUTT;
    oal_uint8                   uc_do_p2p_listen;

    /* ��ȡdmac vap */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->st_scan_params.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_end::pst_dmac_vap is null.}");

        /* �ָ�deviceɨ��״̬Ϊ����״̬ */
        pst_mac_device->en_curr_scan_state = MAC_SCAN_STATE_IDLE;
        return;
    }

    /* listenʱ�޸�vap�ŵ�Ϊlisten�ŵ���listen��������Ҫ�ָ� */
    uc_do_p2p_listen = pst_mac_device->st_scan_params.uc_scan_func & MAC_SCAN_FUNC_P2P_LISTEN;
    if (uc_do_p2p_listen)
    {
        pst_dmac_vap->st_vap_base_info.st_channel = pst_mac_device->st_p2p_vap_channel;
    }

    hal_enable_radar_det(pst_mac_device->pst_device_stru, 0);

    /* ɨ�����ʱ�������Ƿ�Ϊ���mac addrɨ�裬�ָ�vapԭ�ȵ�mac addr */
    dmac_scan_set_vap_mac_addr_by_scan_state(pst_mac_device, OAL_FALSE);

    /* ��ȡɨ��ģʽ */
    en_scan_mode = pst_mac_device->st_scan_params.en_scan_mode;

    /* ����Ǳ���ɨ�裬�Ҳ���cca�����ɨ�裬�������лع����ŵ� */
    if ((en_scan_mode > WLAN_SCAN_MODE_FOREGROUND) && (en_scan_mode < WLAN_SCAN_MODE_BACKGROUND_CCA))
    {
        dmac_scan_switch_channel_back(pst_mac_device);
    }

    /* ����ɨ��ģʽ���ж�Ӧɨ�����Ĵ��� */
    switch (en_scan_mode)
    {
        case WLAN_SCAN_MODE_FOREGROUND:
        case WLAN_SCAN_MODE_BACKGROUND_STA:
        case WLAN_SCAN_MODE_BACKGROUND_AP:
        {
            /* �ϱ�ɨ������¼���ɨ��״̬Ϊ�ɹ� */
            (oal_void)dmac_scan_proc_scan_complete_event(pst_dmac_vap, MAC_SCAN_SUCCESS);
            break;
        }
        case WLAN_SCAN_MODE_BACKGROUND_OBSS:
        {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
            dmac_scan_proc_obss_scan_complete_event(pst_dmac_vap);
    #endif
#endif
            break;
        }
        case WLAN_SCAN_MODE_BACKGROUND_CCA:
        {
            /* CCA�㷨�Ż������ɨ�裬��device�෢��ֱ�ӵ��ö�Ӧ�ص��������д��� */
            if (OAL_PTR_NULL != pst_mac_device->st_scan_params.p_fn_cb)
            {
                pst_mac_device->st_scan_params.p_fn_cb(&(pst_mac_device->st_chan_result));
            }
            break;
        }
        case WLAN_SCAN_MODE_BACKGROUND_PNO:
        {
            /* �ָ�ԭ�ȵ�֡���˼Ĵ���ֵ */
            hal_set_rx_filter(pst_mac_device->pst_device_stru, 0x37B9EEFA);

            /* �Ƿ�ɨ�赽��ƥ���ssid������ǣ��ϱ�ɨ����; �������˯�� */
            if (OAL_TRUE == pst_mac_device->pst_pno_sched_scan_mgmt->en_is_found_match_ssid)
            {
                /* �ϱ�ɨ������¼���ɨ��״̬Ϊ�ɹ� */
                (oal_void)dmac_scan_proc_scan_complete_event(pst_dmac_vap, MAC_SCAN_SUCCESS);

                /* �ͷ�PNO����ṹ���ڴ� */
                OAL_MEM_FREE(pst_mac_device->pst_pno_sched_scan_mgmt, OAL_TRUE);
                pst_mac_device->pst_pno_sched_scan_mgmt = OAL_PTR_NULL;
            }
            else
            {
            #ifdef _PRE_WLAN_FEATURE_STA_PM
                hal_disable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_PNO_SCHED_SCAN_COMP, 0, OAL_PTR_NULL);
            #endif
            }
            break;
        }
        default:
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_end::scan_mode[%d] error.}", en_scan_mode);
            break;
        }
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX

    hal_set_btcoex_soc_gpreg0(OAL_FALSE, BIT9, 9);   // �������̽���
    hal_coex_sw_irq_set(BIT5);
#endif

    /* �ָ�deviceɨ��״̬Ϊ����״̬ */
    pst_mac_device->en_curr_scan_state = MAC_SCAN_STATE_IDLE;

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_abort
 ��������  : ����ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_scan_abort(mac_device_stru *pst_mac_device)
{
    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        return;
    }

    /* ɾ��ɨ�趨ʱ�� */
    if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
    }

    dmac_scan_end(pst_mac_device);
    OAM_WARNING_LOG0(0, OAM_SF_SCAN, "dmac_scan_abort: scan has been aborted");
}
OAL_STATIC oal_uint32 dmac_scan_get_ssid_ie_info(mac_device_stru *pst_mac_device, oal_int8 *pc_ssid, oal_uint8  uc_index)
{
    dmac_vap_stru     *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->st_scan_params.uc_vap_id);

    if (IS_LEGACY_VAP(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* ���������ţ�׼��probe req֡��ssid��Ϣ */
        oal_memcopy(pc_ssid, pst_mac_device->st_scan_params.ac_ssid[uc_index], WLAN_SSID_MAX_LEN);
    }
    else
    {
        /* P2P �豸ɨ�裬��Ҫ��ȡָ��ssid ��Ϣ����P2P �豸��ɨ��ʱֻɨ��һ��ָ��ssid */
        oal_memcopy(pc_ssid, pst_mac_device->st_scan_params.ac_ssid[0], WLAN_SSID_MAX_LEN);
    }

    return OAL_SUCC;
}



OAL_STATIC oal_uint32 dmac_scan_send_bcast_probe(mac_device_stru *pst_mac_device, oal_uint8 uc_band, oal_uint8  uc_index)
{
    oal_uint8          auc_bcst_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    oal_int8           ac_ssid[WLAN_SSID_MAX_LEN] = {'\0'};
    dmac_vap_stru     *pst_dmac_vap;
    oal_uint32         ul_ret;
    oal_uint8          uc_band_tmp;

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe::uc_vap_num=0.}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->st_scan_params.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    if(OAL_PTR_NULL == pst_dmac_vap->st_vap_base_info.pst_mib_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe::pst_dmac_vap->st_vap_base_info.pst_mib_info null.}");
        OAM_ERROR_LOG4(0, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe:: uc_vap_id[%d], p_fn_cb[%p], uc_scan_func[%d], uc_curr_channel_scan_count[%d].}",
                   pst_mac_device->st_scan_params.uc_vap_id,
                   pst_mac_device->st_scan_params.p_fn_cb,
                   pst_mac_device->st_scan_params.uc_scan_func,
                   pst_mac_device->st_scan_params.uc_curr_channel_scan_count);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��̽������ʱ����Ҫ��ʱ����vap��band��Ϣ����ֹ5G��11b */
    uc_band_tmp = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

    pst_dmac_vap->st_vap_base_info.st_channel.en_band = uc_band;

    /* ��ȡ����ɨ������֡����ҪЯ����ssid ie��Ϣ */
    ul_ret = dmac_scan_get_ssid_ie_info(pst_mac_device, ac_ssid, uc_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe::get ssid failed, error[%d].}", ul_ret);
        return ul_ret;
    }

    /* ����probe req֡ */
    ul_ret = dmac_scan_send_probe_req_frame(pst_dmac_vap, auc_bcst_addr, ac_ssid);

    pst_dmac_vap->st_vap_base_info.st_channel.en_band = uc_band_tmp;

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_scan_send_bcast_probe::dmac_mgmt_send_probe_request failed[%d].}", ul_ret);
    }

    return ul_ret;
}
OAL_STATIC oal_void  dmac_scan_switch_home_channel_work(mac_device_stru *pst_mac_device)
{
    hal_enable_radar_det(pst_mac_device->pst_device_stru, 0);

    /* �лع����ŵ�����ʱ�������Ƿ�Ϊ���mac addrɨ�裬�ָ�vapԭ�ȵ�mac addr */
    dmac_scan_set_vap_mac_addr_by_scan_state(pst_mac_device, OAL_FALSE);

    /* ����ɨ�� �лع����ŵ� */
    dmac_scan_switch_channel_back(pst_mac_device);

    /* ���������ʱ�����ڹ����ŵ�����һ��ʱ����л�ɨ���ŵ�����ɨ�� */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_scan_timer,
                           dmac_scan_switch_home_channel_work_timeout,
                           DMAC_SCAN_WORK_TIME_SWITCH_HOME_CHANNEL,
                           pst_mac_device,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);

    return;
}
OAL_STATIC oal_uint32  dmac_scan_switch_home_channel_work_timeout(void *p_arg)
{
    mac_device_stru         *pst_mac_device;

    pst_mac_device = (mac_device_stru *)p_arg;
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_switch_home_channel_work_timeout::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ж��Ƿ���Ҫ��������ɨ�裬�����ʱɨ��״̬Ϊ������״̬��˵��ɨ���Ѿ�ֹͣ�������ټ���ɨ�� */
    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        OAM_WARNING_LOG0(pst_mac_device->st_scan_params.uc_vap_id, OAM_SF_SCAN,
                         "{dmac_scan_switch_home_channel_work_timeout::scan has been aborted, no need to continue.}");
        return OAL_SUCC;
    }

    dmac_scan_switch_channel_off(pst_mac_device);

    /* ɨ���������ʱ�������Ƿ�Ϊ���ɨ�裬��������vap��mac addr */
    dmac_scan_set_vap_mac_addr_by_scan_state(pst_mac_device, OAL_TRUE);

    /* ����ŵ�������� */
    OAL_MEMZERO(&(pst_mac_device->st_chan_result), OAL_SIZEOF(mac_scan_chan_stats_stru));

    dmac_scan_begin(pst_mac_device);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_get_ch_statics_measurement_result
 ��������  : ��ȡӲ���ŵ�ͳ�� �������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_scan_get_ch_statics_measurement_result(
                mac_device_stru                 *pst_mac_device)
{
    hal_ch_statics_irq_event_stru    st_stats_result;
    oal_uint8                        uc_chan_idx;

    /* ��ȡ��� */
    OAL_MEMZERO(&st_stats_result, OAL_SIZEOF(st_stats_result));
    hal_get_ch_statics_result(pst_mac_device->pst_device_stru, &st_stats_result);
    hal_get_ch_measurement_result(pst_mac_device->pst_device_stru, &st_stats_result);

#if defined(_PRE_WLAN_CHIP_TEST) && defined(_PRE_SUPPORT_ACS) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    dmac_acs_channel_meas_comp_handler(pst_mac_device, &st_stats_result);
#endif

    uc_chan_idx  = pst_mac_device->uc_scan_chan_idx;

    /* �����ŵ�ͳ��/���������Ϣ */
    pst_mac_device->st_chan_result.uc_stats_valid = 1;
    pst_mac_device->st_chan_result.uc_channel_number = pst_mac_device->st_scan_params.ast_channel_list[uc_chan_idx].uc_chan_number;

    if (st_stats_result.c_pri20_idle_power < 0)
    {
        pst_mac_device->st_chan_result.s_free_power_stats_20M  += (oal_int8)st_stats_result.c_pri20_idle_power; /* ��20M�ŵ����й��� */
        pst_mac_device->st_chan_result.s_free_power_stats_40M  += (oal_int8)st_stats_result.c_pri40_idle_power; /* ��40M�ŵ����й��� */
        pst_mac_device->st_chan_result.s_free_power_stats_80M  += (oal_int8)st_stats_result.c_pri80_idle_power; /* ȫ��80M�ŵ����й��� */
        pst_mac_device->st_chan_result.uc_free_power_cnt += 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{dmac_scan_get_ch_statics_measurement_result::c_pri20_idle_power=%u}", (oal_uint8)st_stats_result.c_pri20_idle_power);
    }

    pst_mac_device->st_chan_result.ul_total_free_time_20M_us += st_stats_result.ul_pri20_free_time_us;
    pst_mac_device->st_chan_result.ul_total_free_time_40M_us += st_stats_result.ul_pri40_free_time_us;
    pst_mac_device->st_chan_result.ul_total_free_time_80M_us += st_stats_result.ul_pri80_free_time_us;
    pst_mac_device->st_chan_result.ul_total_recv_time_us     += st_stats_result.ul_ch_rx_time_us;
    pst_mac_device->st_chan_result.ul_total_send_time_us     += st_stats_result.ul_ch_tx_time_us;
    pst_mac_device->st_chan_result.ul_total_stats_time_us    += st_stats_result.ul_ch_stats_time_us;

}
oal_uint32 dmac_scan_channel_statistics_complete(frw_event_mem_stru *pst_event_mem)
{
    mac_device_stru                 *pst_mac_device;
    frw_event_stru                  *pst_event;
    oal_uint16                       us_total_scan_time_per_chan;
    oal_uint8                        uc_do_meas;        /* ����ɨ���Ƿ�Ҫ��ȡ�ŵ������Ľ�� */
    oal_uint8                        uc_chan_stats_cnt;

    //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_scan_channel_statistics_complete:: channel statistic complete.}");

    /* Ѱ�Ҷ�Ӧ��DEVICE�ṹ�Լ���Ӧ��ACS�ṹ */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_channel_statistics_complete::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡӲ��ͳ�� ������� */
    uc_do_meas = pst_mac_device->st_scan_params.uc_scan_func & (MAC_SCAN_FUNC_MEAS | MAC_SCAN_FUNC_STATS);
    if (uc_do_meas)
    {
        dmac_scan_get_ch_statics_measurement_result(pst_mac_device);
    }

    /* ���ŵ�Ӳ��ͳ�Ʋ����������� */
    pst_mac_device->st_chan_result.uc_stats_cnt++;

    /* ÿ��Ӳ������ʱ����10ms�����ݱ���ɨ��ʱ����ȷ��Ҫ�������ٴ�Ӳ������ */
    uc_chan_stats_cnt = pst_mac_device->st_chan_result.uc_stats_cnt;

    us_total_scan_time_per_chan = (oal_uint16)(pst_mac_device->st_scan_params.us_scan_time * pst_mac_device->st_scan_params.uc_max_scan_count_per_channel);
    if (uc_chan_stats_cnt * DMAC_SCAN_CHANNEL_MEAS_PERIOD_MS < us_total_scan_time_per_chan)
    {
        /* �ٴ�����һ�β��� */
        hal_set_ch_statics_period(pst_mac_device->pst_device_stru, DMAC_SCAN_CHANNEL_STATICS_PERIOD_US);
        hal_set_ch_measurement_period(pst_mac_device->pst_device_stru, DMAC_SCAN_CHANNEL_MEAS_PERIOD_MS);
        hal_enable_ch_statics(pst_mac_device->pst_device_stru, 1);
    }

    return OAL_SUCC;
}


oal_void dmac_scan_radar_detected(mac_device_stru *pst_mac_device, hal_radar_det_event_stru *pst_radar_det_info)
{
    pst_mac_device->st_chan_result.uc_radar_detected = 1;
    pst_mac_device->st_chan_result.uc_radar_bw       = 0;
}


/*****************************************************************************
 �� �� ��  : dmac_scan_report_channel_result
 ��������  : �ϱ���ǰ�ŵ����ŵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_scan_report_channel_statistics_result(mac_device_stru *pst_mac_device, oal_uint8 uc_scan_idx)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    dmac_crx_chan_result_stru  *pst_chan_result_param;

    /* ���ŵ�ɨ������HMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_crx_chan_result_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_scan_report_channel_statistics_result::alloc mem fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT,
                       OAL_SIZEOF(dmac_crx_chan_result_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_device->uc_chip_id,
                       pst_mac_device->uc_device_id,
                       0);

    pst_chan_result_param = (dmac_crx_chan_result_stru *)(pst_event->auc_event_data);

    pst_chan_result_param->uc_scan_idx    = uc_scan_idx;
    pst_chan_result_param->st_chan_result = pst_mac_device->st_chan_result;

    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}



oal_uint32 dmac_scan_init(mac_device_stru *pst_device)
{
    /* ��ʼ��deviceɨ��״̬Ϊ���� */
    pst_device->en_curr_scan_state = MAC_SCAN_STATE_IDLE;

    return OAL_SUCC;
}
oal_uint32 dmac_scan_exit(mac_device_stru *pst_device)
{
    return OAL_SUCC;
}


/*lint -e19 */

oal_module_symbol(dmac_scan_switch_channel_off);
oal_module_symbol(dmac_scan_begin);
oal_module_symbol(dmac_scan_abort);
oal_module_symbol(dmac_scan_switch_channel_back);
/*lint +e19 */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
