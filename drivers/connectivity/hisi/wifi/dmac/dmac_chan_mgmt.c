/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_chan_mgmt.c
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2014��2��22��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��2��22��
    ��    ��   : mayuan
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "hal_ext_if.h"
#include "dmac_main.h"
#include "dmac_alg.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_chan_mgmt.h"
#include "dmac_scan.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_CHAN_MGMT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
oal_uint32 dmac_dump_chan(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param)
{
    dmac_set_chan_stru *pst_chan;
    oal_uint8 uc_vap_id;

    if ( (OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param) )
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_vap_id = pst_mac_vap->uc_vap_id;
    pst_chan = (dmac_set_chan_stru*)puc_param;
    OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "uc_chan_number=%d en_band=%d en_bandwidth=%d uc_idx=%d\r\n",
                pst_chan->st_channel.uc_chan_number, pst_chan->st_channel.en_band,
                pst_chan->st_channel.en_bandwidth, pst_chan->st_channel.uc_idx);

    OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "uc_announced_channel=%d en_announced_bandwidth=%d uc_ch_switch_cnt=%d en_ch_switch_status=%d\r\n",
                pst_chan->st_ch_switch_info.uc_announced_channel, pst_chan->st_ch_switch_info.en_announced_bandwidth,
                pst_chan->st_ch_switch_info.uc_ch_switch_cnt, pst_chan->st_ch_switch_info.en_ch_switch_status);

    OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "en_bw_switch_status=%d en_csa_present_in_bcn=%d uc_start_chan_idx=%d uc_end_chan_idx=%d\r\n",
                pst_chan->st_ch_switch_info.en_bw_switch_status, pst_chan->st_ch_switch_info.en_csa_present_in_bcn,
                pst_chan->st_ch_switch_info.uc_start_chan_idx, pst_chan->st_ch_switch_info.uc_end_chan_idx);

   OAM_INFO_LOG3(uc_vap_id, OAM_SF_2040,
               "en_user_pref_bandwidth=%d uc_new_channel=%d en_new_bandwidth=%d\r\n",
               pst_chan->st_ch_switch_info.en_user_pref_bandwidth,
               pst_chan->st_ch_switch_info.uc_new_channel, pst_chan->st_ch_switch_info.en_new_bandwidth);

   /* OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "en_user_pref_bandwidth=%d en_bw_change=%d uc_new_channel=%d en_new_bandwidth=%d\r\n",
                pst_chan->st_ch_switch_info.en_user_pref_bandwidth, pst_chan->st_ch_switch_info.en_bw_change,
                pst_chan->st_ch_switch_info.uc_new_channel, pst_chan->st_ch_switch_info.en_new_bandwidth);*/

    OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "uc_new_ch_swt_cnt=%d en_waiting_to_shift_channel=%d en_waiting_for_ap=%d en_channel_swt_cnt_zero=%d\r\n",
                pst_chan->st_ch_switch_info.uc_new_ch_swt_cnt, pst_chan->st_ch_switch_info.en_waiting_to_shift_channel,
                pst_chan->st_ch_switch_info.en_waiting_for_ap, pst_chan->st_ch_switch_info.en_channel_swt_cnt_zero);

    OAM_INFO_LOG4(uc_vap_id, OAM_SF_2040,
                "en_te_b=%d ul_chan_report_for_te_a=%d en_switch_immediately=%d en_check_cac=%d\r\n",
                pst_chan->st_ch_switch_info.en_te_b, pst_chan->st_ch_switch_info.ul_chan_report_for_te_a,
                pst_chan->en_switch_immediately, pst_chan->en_check_cac);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_initiate_switch_to_new_channel
 ��������  : ����Channel Switch Announcement֡��׼���л������ŵ�����
 �������  : pst_event_mem: �¼��ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_chan_initiate_switch_to_new_channel(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    frw_event_hdr_stru              *pst_event_hdr;
    dmac_vap_stru                   *pst_dmac_vap;
    mac_vap_stru                    *pst_mac_vap;
    dmac_set_ch_switch_info_stru    *pst_ch_switch_info;
    mac_device_stru                 *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_chan_initiate_switch_to_new_channel::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event          = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr      = &(pst_event->st_event_hdr);
    pst_ch_switch_info = (dmac_set_ch_switch_info_stru *)pst_event->auc_event_data;

    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    pst_mac_vap   = &(pst_dmac_vap->st_vap_base_info);

    /* ͬ��channel switch info */
    pst_mac_vap->st_ch_switch_info.en_ch_switch_status    = pst_ch_switch_info->en_ch_switch_status;
    pst_mac_vap->st_ch_switch_info.uc_announced_channel   = pst_ch_switch_info->uc_announced_channel;
    pst_mac_vap->st_ch_switch_info.en_announced_bandwidth = pst_ch_switch_info->en_announced_bandwidth;
    pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt       = pst_ch_switch_info->uc_ch_switch_cnt;
    pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn  = pst_ch_switch_info->en_csa_present_in_bcn;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    pst_mac_device->uc_csa_vap_cnt = pst_ch_switch_info->uc_csa_vap_cnt;

    /* ���� Channel Switch Announcement ֡ */
    return dmac_mgmt_send_csa_action(pst_dmac_vap, pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_announced_channel,
                                     pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_ch_switch_cnt,
                                     pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_announced_bandwidth);
}

/*****************************************************************************
 �� �� ��  : dmac_chan_update_user_bandwidth
 ��������  : ����ap������user�Ĵ���
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ�룬ָ��AP
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ�룬ָ��ap
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_update_user_bandwidth(mac_vap_stru *pst_mac_vap)
{
    wlan_bw_cap_enum_uint8    en_bwcap_ap;
    wlan_bw_cap_enum_uint8    en_bandwidth_cap;
    oal_uint16                us_max_user_id;
    oal_uint16                us_user_id;
    mac_user_stru            *pst_mac_user;
    wlan_bw_cap_enum_uint8    en_bwcap_min;

    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_ap);
    us_max_user_id = mac_res_get_max_user_id();
    for (us_user_id = 0; us_user_id<us_max_user_id; us_user_id++)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_id);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "dmac_chan_update_user_bandwidth::null user");
            return;
        }

        if ( (pst_mac_user->uc_chip_id == pst_mac_vap->uc_chip_id) &&
             (pst_mac_user->uc_device_id == pst_mac_vap->uc_device_id) &&
             (pst_mac_user->uc_vap_id == pst_mac_vap->uc_vap_id) )
         {
            mac_user_get_sta_cap_bandwidth(pst_mac_user, &en_bandwidth_cap);
            en_bwcap_min = OAL_MIN(en_bwcap_ap, en_bandwidth_cap);
            mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_min, en_bwcap_min);

            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "dmac_chan_update_user_bandwidth::update us_user_id=%d cap=%d avail=%d cur=%d",
                us_user_id, en_bandwidth_cap, pst_mac_user->en_avail_bandwidth,
                pst_mac_user->en_cur_bandwidth);
         }

    }
}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_scan_dfs_timeout
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_mgmt_scan_dfs_timeout(void *p_arg)
{
    mac_device_stru            *pst_mac_device;

    pst_mac_device = (mac_device_stru *)p_arg;

    /* ʹ���״��� */
    hal_enable_radar_det(pst_mac_device->pst_device_stru, 1);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_chan_select_channel_mac
 ��������  : ����SW/MAC/PHY/RF�е��ŵ��ʹ���ʹVAP���������ŵ���
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ��Ҫ�����õ��ŵ�
             en_bandwidth: ��Ҫ�����õĴ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_select_channel_mac(mac_vap_stru                        *pst_mac_vap,
                                       oal_uint8                            uc_channel,
                                       wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_device_stru   *pst_mac_device;
    oal_uint8          uc_idx;
    oal_uint32         ul_ret;
#ifdef _PRE_WLAN_FEATURE_DFS
    oal_bool_enum_uint8      en_enable_dfs;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_chan_select_channel_mac::pst_mac_vap null.}");

        return;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_chan_select_channel_mac::pst_mac_device null.}");

        return;
    }

    /* ����VAP�µ���20MHz�ŵ��š�����ģʽ���ŵ����� */
    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_chan_select_channel_mac::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_vap->st_channel.uc_chan_number = uc_channel;
    pst_mac_vap->st_channel.en_bandwidth   = en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;

#ifdef _PRE_WLAN_FEATURE_DBAC
    if (mac_is_dbac_running(pst_mac_device))
    {
        mac_fcs_update_dbac_config(pst_mac_vap);
        return;
    }
#endif

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        dmac_chan_update_user_bandwidth(pst_mac_vap);
    }
#ifdef _PRE_WLAN_FEATURE_DFS
    /* ʹ��ȥʹ���״��� */
    if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)&&(OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device)))
    {
        en_enable_dfs = mac_is_ch_in_radar_band(pst_mac_device->en_max_band, uc_idx);
        if (0 != pst_mac_device->us_dfs_timeout && OAL_TRUE ==en_enable_dfs)
        {
            hal_enable_radar_det(pst_mac_device->pst_device_stru, 0);
            /* ������ʱ�� */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_radar_timer,
                                   dmac_mgmt_scan_dfs_timeout,
                                   pst_mac_device->us_dfs_timeout,
                                   pst_mac_device,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
        else
        {
            hal_enable_radar_det(pst_mac_device->pst_device_stru, en_enable_dfs);
        }
    }
#endif

    /* ֪ͨ�㷨�ŵ��ı� */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    /* ֪ͨ�㷨����ı� */
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    /* �л��ŵ� */
    dmac_mgmt_switch_channel(pst_mac_device, &pst_mac_vap->st_channel);
}

/*****************************************************************************
 �� �� ��  : dmac_chan_select_chan_event_process
 ��������  : �����HMACģ��������ŵ����������¼�
 �������  : pst_event_mem: �¼��ṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_chan_sync(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru           *pst_event;
    frw_event_hdr_stru       *pst_event_hdr;
    dmac_set_chan_stru       *pst_set_chan;
    mac_vap_stru             *pst_mac_vap;
    oal_uint32                ul_tea;
    oal_bool_enum_uint8       en_teb;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_chan_sync::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);
    pst_set_chan  = (dmac_set_chan_stru *)pst_event->auc_event_data;

    pst_mac_vap   = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);
    ul_tea = pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a;
    en_teb = pst_mac_vap->st_ch_switch_info.en_te_b;
    oal_memcopy(&pst_mac_vap->st_channel, &pst_set_chan->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&pst_mac_vap->st_ch_switch_info, &pst_set_chan->st_ch_switch_info,
                    OAL_SIZEOF(mac_ch_switch_info_stru));
    pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a = ul_tea;
    pst_mac_vap->st_ch_switch_info.en_te_b = en_teb;

    //OAM_INFO_LOG0(0, OAM_SF_2040, "\r\n\r\ndmac_chan_sync\r\n");
    dmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);

    if (OAL_TRUE == pst_set_chan->en_switch_immediately)
    {
        dmac_chan_select_channel_mac(pst_mac_vap, pst_set_chan->st_channel.uc_chan_number, pst_set_chan->st_channel.en_bandwidth);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_restart_network_after_switch
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_restart_network_after_switch(mac_device_stru *pst_mac_device, dmac_vap_stru *pst_dmac_vap)
{
    /* �����ŵ��ϻָ�Beacon֡�ķ��� */
    hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);

    /* �����ŵ��ϻָ�Ӳ���ķ��� */
    hal_set_machw_tx_resume(pst_dmac_vap->pst_hal_device);

   // OAM_INFO_LOG0(0, OAM_SF_ANY, "Transmitter is enabled!");
}

/*****************************************************************************
 �� �� ��  : dmac_chan_restart_network_after_switch
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_chan_restart_network_after_switch_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru       *pst_event;
    frw_event_hdr_stru   *pst_event_hdr;
    mac_device_stru      *pst_mac_device;
    dmac_vap_stru        *pst_dmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_chan_restart_network_after_switch_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    /* ��ȡdmac vap�ṹ����Ϣ */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_chan_restart_network_after_switch_event::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡdevice�ṹ����Ϣ */
    pst_mac_device   = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_chan_restart_network_after_switch_event::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_chan_restart_network_after_switch(pst_mac_device, pst_dmac_vap);

    /* mayuan TBD ���￴Ҫ��Ҫ���ô˺��� */
    //dmac_vap_resume_tx_by_chl(pst_mac_device, &(pst_dmac_vap->st_vap_base_info.st_channel));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_switch_complete_notify
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_switch_complete_notify(mac_vap_stru *pst_mac_vap,
                                                    oal_bool_enum_uint8 en_check_cac)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_ret;
    dmac_set_chan_stru   *pst_set_chan;

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(0)
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{dmac_switch_complete_notify::pst_event_mem null.}");

        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CRX,
                    DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE,
                    OAL_SIZEOF(dmac_set_chan_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    pst_set_chan = (dmac_set_chan_stru *)pst_event->auc_event_data;
    oal_memcopy(&pst_set_chan->st_channel, &pst_mac_vap->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&pst_set_chan->st_ch_switch_info, &pst_mac_vap->st_ch_switch_info,
                OAL_SIZEOF(mac_ch_switch_info_stru));
    pst_set_chan->en_check_cac = en_check_cac;

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{dmac_switch_complete_notify}");
    dmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{dmac_switch_complete_notify::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);

        return;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);
}

#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
/*****************************************************************************
 �� �� ��  : dmac_dfs_switch_to_offchan
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��2��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dfs_switch_to_offchan_event_process(frw_event_mem_stru* pst_event_mem)
{
    frw_event_stru           *pst_event;
    frw_event_hdr_stru       *pst_event_hdr;
    mac_vap_stru             *pst_mac_vap;
    mac_device_stru          *pst_mac_device;
    mac_channel_stru          st_off_chan;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{dmac_chan_select_chan_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    pst_mac_vap   = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);
    pst_mac_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    st_off_chan.uc_chan_number = pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num;
    st_off_chan.en_band        = pst_mac_vap->st_channel.en_band;
    st_off_chan.en_bandwidth   = pst_mac_vap->st_channel.en_bandwidth;
    st_off_chan.uc_idx         = 0;
    mac_get_channel_idx_from_num(st_off_chan.en_band, st_off_chan.uc_chan_number, &st_off_chan.uc_idx);

    //hal_set_machw_tx_suspend(pst_mac_device->pst_device_stru);

    //hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);
    //hal_set_machw_tx_suspend(pst_mac_device->pst_device_stru);

    dmac_vap_pause_tx_by_chl(pst_mac_device, &(pst_mac_vap->st_channel));

    /* �л���offchan���� */
    dmac_switch_channel_off(pst_mac_device, pst_mac_vap, &st_off_chan, pst_mac_device->st_dfs.st_dfs_info.uc_cts_duration);
    //dmac_mgmt_switch_channel(pst_mac_device, &st_off_chan);

    pst_mac_device->st_dfs.st_dfs_info.uc_dmac_channel_flag = 1;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dfs_switch_back_event_process
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��2��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dfs_switch_back_event_process(frw_event_mem_stru* pst_event_mem)
{
    frw_event_stru           *pst_event;
    frw_event_hdr_stru       *pst_event_hdr;
    mac_vap_stru             *pst_mac_vap;
    mac_device_stru          *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{dmac_chan_select_chan_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    pst_mac_vap   = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);
    pst_mac_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* �л���home channel���� */
    dmac_scan_switch_channel_back(pst_mac_device);

    pst_mac_device->st_dfs.st_dfs_info.uc_dmac_channel_flag = 0;

    if (WLAN_CH_SWITCH_STATUS_1 != pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        //hal_set_machw_tx_resume(pst_mac_device->pst_device_stru);
        //hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);
    }

    return OAL_SUCC;
}
#endif

oal_uint32  dmac_dfs_test(frw_event_mem_stru* pst_dmac_event_mem)
{
    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event_desc;
    hal_radar_det_event_stru        *pst_radar_det_info;
    oal_uint8 uc_chip_id;
    oal_uint8 uc_device_id;
    oal_uint8 uc_vap_id;

    pst_event_desc = (frw_event_stru *)pst_dmac_event_mem->puc_data;
    uc_chip_id   = pst_event_desc->st_event_hdr.uc_chip_id;
    uc_device_id = pst_event_desc->st_event_hdr.uc_device_id;
    uc_vap_id    = pst_event_desc->st_event_hdr.uc_vap_id;

    /* ע��: �״��¼��ľ����������ж��°벿��ȡ */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hal_radar_irq_reg_list_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
       // HAL_ERR_LOG(0, "hi1102_irq_radar_isr: alloc pst_event_mem failed!");
        OAM_ERROR_LOG0(0, OAM_SF_IRQ, "{dmac_dfs_test::alloc pst_event_mem failed.}\r\n");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event_desc = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event_desc->st_event_hdr),
                       FRW_EVENT_TYPE_DMAC_MISC,
                       HAL_EVENT_DMAC_MISC_RADAR_DETECTED,
                       OAL_SIZEOF(hal_radar_irq_reg_list_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id );


    /* ��ȡ�״���ƼĴ��� */
    pst_radar_det_info = (hal_radar_det_event_stru *)(pst_event_desc->auc_event_data);
    pst_radar_det_info->uc_radar_type = 1;

    /* �¼��ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_chan_attempt_new_chan
 ��������  : ����VAPת�������ŵ�����
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ��
             uc_channel  : ���ŵ���
             en_bandwidth: �´���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFS
oal_void  dmac_chan_attempt_new_chan(dmac_vap_stru                       *pst_dmac_vap,
                                     oal_uint8                            uc_channel,
                                     wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_device_stru   *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DFS, "{dmac_chan_attempt_new_chan::pst_mac_device null.}");

        return;
    }

    /* ѡ��20/40/80MHz�ŵ� */
    //l00311403 TODO ��Ҫ����dbac��������Ĵ���
    dmac_chan_select_channel_mac(&(pst_dmac_vap->st_vap_base_info), uc_channel, en_bandwidth);

    OAM_INFO_LOG2(0, OAM_SF_DFS,"[DFS]dmac_chan_attempt_new_chan, Switching channel to %d! BW %d mode.\n",
                 uc_channel, en_bandwidth);

    /* �����ŵ��л�״̬Ϊ WLAN_CH_SWITCH_DONE(���) */
    pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_ch_switch_status = WLAN_CH_SWITCH_DONE;

    mac_vap_set_bssid(&(pst_dmac_vap->st_vap_base_info), mac_mib_get_StationID(&(pst_dmac_vap->st_vap_base_info)));


    /* �ϱ��ŵ��л�����¼� hmac�ж��Ƿ���ҪCAC��� */
    dmac_switch_complete_notify(&(pst_dmac_vap->st_vap_base_info), OAL_TRUE);

    if (mac_dfs_get_debug_level(pst_mac_device) & 0x1)
    {
        //OAM_INFO_LOG1(0, OAM_SF_DFS, "{dmac_chan_attempt_new_chan::chan switch time(ms): %d.}", ul_delta_time_for_chan_switch);
    }

}

#else

oal_void  dmac_chan_attempt_new_chan(dmac_vap_stru                       *pst_dmac_vap,
                                     oal_uint8                            uc_channel,
                                     wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_device_stru   *pst_mac_device;

    /* ѡ��20/40/80MHz�ŵ� */
    //l00311403 TODO ��Ҫ����dbac��������Ĵ���
    dmac_chan_select_channel_mac(&(pst_dmac_vap->st_vap_base_info), uc_channel, en_bandwidth);

    /* DFS �Ƿ���Ҫ����ɨ���ŵ� */

    /* �����ŵ��л�״̬Ϊ WLAN_CH_SWITCH_DONE(���) */
    //l00311403 Ҫͬ��״̬
    pst_dmac_vap->st_vap_base_info.st_ch_switch_info.en_ch_switch_status = WLAN_CH_SWITCH_DONE;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DFS, "{dmac_chan_attempt_new_chan::pst_mac_device null.}");

        return;
    }

    /* CSA�������� */
    pst_mac_device->uc_csa_cnt = 0;

    mac_vap_set_bssid(&(pst_dmac_vap->st_vap_base_info), mac_mib_get_StationID(&(pst_dmac_vap->st_vap_base_info)));

    /* �����ŵ��ϻָ�Beacon֡�ķ��� */
    hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);

    /* �����ŵ��ϻָ�Ӳ���ķ��� */
    hal_set_machw_tx_resume(pst_dmac_vap->pst_hal_device);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_switch_complete_notify(&(pst_dmac_vap->st_vap_base_info), OAL_FALSE);
#endif
}

#endif   /* end of _PRE_WLAN_FEATURE_DFS */

/*****************************************************************************
 �� �� ��  : dmac_chan_disable_machw_tx
 ��������  : ��ֹӲ������(����֡��ACK��RTS)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_disable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru   *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_chan_disable_machw_tx::pst_mac_device null.}");

        return;
    }

    /* ��ֹӲ������ */
    hal_set_machw_tx_suspend(pst_mac_device->pst_device_stru);

    /* ��ֹӲ����ack */
    hal_disable_machw_ack_trans(pst_mac_device->pst_device_stru);

    /* ��ֹӲ����cts */
    hal_disable_machw_cts_trans(pst_mac_device->pst_device_stru);
}

/*****************************************************************************
 �� �� ��  : dmac_chan_enable_machw_tx
 ��������  : �ָ�Ӳ������(����֡��ACK��RTS)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_enable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru   *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_chan_enable_machw_tx::pst_mac_device null.}");

        return;
    }

    /* �ָ�Ӳ������ */
    hal_set_machw_tx_resume(pst_mac_device->pst_device_stru);

    /* �ָ�Ӳ����ack */
    hal_enable_machw_ack_trans(pst_mac_device->pst_device_stru);

    /* �ָ�Ӳ����cts */
    hal_enable_machw_cts_trans(pst_mac_device->pst_device_stru);
}

/*****************************************************************************
 �� �� ��  : dmac_chan_disable_machw_tx_event_process
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_chan_disable_machw_tx_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru           *pst_event;
    frw_event_hdr_stru       *pst_event_hdr;
    mac_vap_stru             *pst_mac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_chan_disable_machw_tx_event_process::pst_event_mem null.}");


        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    pst_mac_vap  = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_chan_disable_machw_tx_event_process::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ֹӲ����ȫ������ */
    dmac_chan_disable_machw_tx(pst_mac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_enable_machw_tx_event_process
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_chan_enable_machw_tx_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru           *pst_event;
    frw_event_hdr_stru       *pst_event_hdr;
    mac_vap_stru             *pst_mac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_chan_enable_machw_tx_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    pst_mac_vap   = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    /* �ָ�Ӳ������ */
    dmac_chan_enable_machw_tx(pst_mac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_tx_complete_2040_coexist
 ��������  : 20/40���淢������жϴ�����Ҫ��AP������CSA frame����Ҫ��ֹӲ������
 �������  : pst_mac_device: device�ṹ��ָ��
             pst_hal_device: hal��device�ṹ��ָ��
             pst_netbuf    : ����CSA frame��netbufָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_tx_complete_2040_coexist(mac_device_stru *pst_mac_device, hal_to_dmac_device_stru *pst_hal_device, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8       *puc_payload;

    /* ��Channel Switch Announcement֡���ͺ���Ҫ��ֹӲ������ */
    if (mac_ieeee80211_is_action(oal_netbuf_header(pst_netbuf)))
    {
    #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        puc_payload = (oal_uint8 *)oal_netbuf_data(pst_netbuf);
    #else
        puc_payload = (oal_uint8 *)oal_netbuf_header(pst_netbuf) + MAC_80211_FRAME_LEN;
    #endif

        if ((MAC_ACTION_CATEGORY_SPECMGMT == puc_payload[0]) && (MAC_SPEC_CH_SWITCH_ANNOUNCE == puc_payload[1]))
        {
            pst_mac_device->uc_csa_cnt++;

            /* ��device������AP��CSA֡��������ɺ󣬹���Ӳ������ */
            if (pst_mac_device->uc_csa_cnt == (pst_mac_device->uc_vap_num - pst_mac_device->uc_sta_num))
            {
                //OAM_INFO_LOG0(0, OAM_SF_2040, "{dmac_chan_tx_complete_2040_coexist::machw tx suspend.}\r\n");

                /* ����Ӳ������ */
                hal_set_machw_tx_suspend(pst_hal_device);
            }
        }
    }
}

#ifdef _PRE_WLAN_FEATURE_DFS
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_chan_tx_complete_suspend_tx
 ��������  : CSA֡��������жϴ�����Ҫ��AP������CSA frame����Ҫ��ֹӲ������
 �������  : pst_mac_device: device�ṹ��ָ��
             pst_hal_device: hal��device�ṹ��ָ��
             pst_netbuf    : ����CSA frame��netbufָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_tx_complete_suspend_tx(mac_device_stru           *pst_mac_device,
                                           mac_vap_stru              *pst_mac_vap,
                                           hal_to_dmac_device_stru   *pst_hal_device,
                                           oal_netbuf_stru           *pst_netbuf)
{
    oal_uint8     *puc_payload;

    /* ��Channel Switch Announcement֡���ͺ���Ҫ��ֹӲ������ */
    if (mac_ieeee80211_is_action(oal_netbuf_header(pst_netbuf)))
    {
        puc_payload = (oal_uint8 *)oal_netbuf_data(pst_netbuf);

        if ((MAC_ACTION_CATEGORY_SPECMGMT == puc_payload[0]) && (MAC_SPEC_CH_SWITCH_ANNOUNCE == puc_payload[1]))
        {
            pst_mac_device->uc_csa_vap_cnt--;

            /* ��device������running AP��CSA֡��������ɺ󣬹���Ӳ������ */
            if (0 == pst_mac_device->uc_csa_vap_cnt)
            {
                //OAM_INFO_LOG0(0, OAM_SF_DFS, "{dmac_chan_tx_complete_suspend_tx::machw tx suspend.}\r\n");

                /* ����Ӳ������ */
                hal_set_machw_tx_suspend(pst_hal_device);

                if (mac_dfs_get_debug_level(pst_mac_device) & 0x1)
                {

                    //OAM_INFO_LOG1(0, OAM_SF_DFS, "{dmac_chan_tx_complete_suspend_tx::chan shutdown time(ms): %d.}", ul_delta_time_for_chan_shutdown);
                }
            }
        }
    }
}
#else
/*****************************************************************************
 �� �� ��  : dmac_chan_tx_complete_suspend_tx
 ��������  : CSA֡��������жϴ�����Ҫ��AP������CSA frame����Ҫ��ֹӲ������
 �������  : pst_mac_device: device�ṹ��ָ��
             pst_hal_device: hal��device�ṹ��ָ��
             pst_netbuf    : ����CSA frame��netbufָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_chan_tx_complete_suspend_tx(mac_device_stru           *pst_mac_device,
                                           mac_vap_stru              *pst_mac_vap,
                                           hal_to_dmac_device_stru   *pst_hal_device,
                                           oal_netbuf_stru           *pst_netbuf)
{
    oal_uint8     *puc_payload;
    oal_uint32     ul_chan_shutdown_time;
    oal_uint32     ul_delta_time_for_chan_shutdown;

    /* ��Channel Switch Announcement֡���ͺ���Ҫ��ֹӲ������ */
    if (mac_ieeee80211_is_action(oal_netbuf_data(pst_netbuf)))
    {
        puc_payload = (oal_uint8 *)oal_netbuf_data(pst_netbuf) + MAC_80211_FRAME_LEN;

        if ((MAC_ACTION_CATEGORY_SPECMGMT == puc_payload[0]) && (MAC_SPEC_CH_SWITCH_ANNOUNCE == puc_payload[1]))
        {
            pst_mac_device->uc_csa_vap_cnt--;

            /* ��device������running AP��CSA֡��������ɺ󣬹���Ӳ������ */
            if (0 == pst_mac_device->uc_csa_vap_cnt)
            {
                //OAM_INFO_LOG0(0, OAM_SF_DFS, "{dmac_chan_tx_complete_suspend_tx::machw tx suspend.}\r\n");

                /* ����Ӳ������ */
                hal_set_machw_tx_suspend(pst_hal_device);

                if (mac_dfs_get_debug_level(pst_mac_device) & 0x1)
                {
                    ul_chan_shutdown_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();
                    ul_delta_time_for_chan_shutdown = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_mac_device->st_dfs.st_dfs_info.ul_radar_detected_timestamp, ul_chan_shutdown_time);

                    //OAM_INFO_LOG1(0, OAM_SF_DFS, "{dmac_chan_tx_complete_suspend_tx::chan shutdown time(ms): %d.}", ul_delta_time_for_chan_shutdown);
                }
            }
        }
    }
}
#endif
OAL_STATIC oal_void dmac_dfs_radar_detect_log(mac_device_stru *pst_mac_device, oal_uint8 uc_radar_type, oal_uint8 uc_vap_id)
{
    OAL_STATIC oal_uint32       ul_dfs_cnt = 0;

    OAM_WARNING_LOG2(uc_vap_id, OAM_SF_DFS, "{dmac_dfs_radar_detect_event::[DFS]radar detected %u, radar type = %d!",
                       ul_dfs_cnt, uc_radar_type);
    ul_dfs_cnt++;
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dfs_radar_detect_event
 ��������  : DMAC �״��жϴ�����ں���
 �������  : pst_event_mem: �¼��ڴ�ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :
             mayuan TBD�����¼�����ʲô������Ҫȷ�ϣ�vap id, etc...
 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_dfs_radar_detect_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    mac_device_stru            *pst_mac_device;
    mac_vap_stru               *pst_mac_vap = OAL_PTR_NULL;
    hal_radar_det_event_stru   *pst_radar_det_info;
    oal_uint8                   uc_vap_idx;
    oal_bool_enum_uint8         en_found_running_ap  = OAL_FALSE;
    oal_bool_enum_uint8         en_found_starting_ap = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{dmac_dfs_radar_detect_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{dmac_dfs_radar_detect_event::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_radar_det_info = (hal_radar_det_event_stru *)pst_event->auc_event_data;
    /* ����״���ûʹ�ܣ���ֱ�ӷ��� */
    if (OAL_FALSE == mac_dfs_get_dfs_enable(pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{dmac_dfs_radar_detect_event::[DFS]dfs is disabled.");
        return OAL_SUCC;
    }

    if (mac_dfs_get_debug_level(pst_mac_device) & 0x1)
    {
        dmac_dfs_radar_detect_log(pst_mac_device, pst_radar_det_info->uc_radar_type, pst_event->st_event_hdr.uc_vap_id);
        /* ��¼�״���ʱ��� */
        pst_mac_device->st_dfs.st_dfs_info.ul_radar_detected_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    }

    if (mac_dfs_get_debug_level(pst_mac_device) & 0x2)
    {
        dmac_dfs_radar_detect_log(pst_mac_device, pst_radar_det_info->uc_radar_type, pst_event->st_event_hdr.uc_vap_id);
        return OAL_SUCC;
    }

    /* ��һ��running AP */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if ((OAL_PTR_NULL != pst_mac_vap)                      &&
            (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state))
        {
            en_found_running_ap = OAL_TRUE;
            break;
        }
    }

    /* û�ҵ� running AP��Ѱ���Ƿ������� start ��AP */
    if (OAL_FALSE == en_found_running_ap)
    {
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if ((OAL_PTR_NULL != pst_mac_vap)                      &&
                (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) &&
                (MAC_VAP_STATE_AP_WAIT_START == pst_mac_vap->en_vap_state))
            {
                en_found_starting_ap = OAL_TRUE;
                break;
            }
        }
    }

    /* ��û������ running �� AP��Ҳû������ start �� AP�����������״��ŵ�������Ӧ */
    if (((OAL_FALSE == en_found_running_ap) && (OAL_FALSE == en_found_starting_ap)) ||
        (OAL_PTR_NULL == pst_mac_vap))
    {
        return OAL_SUCC;
    }

    /* �ر�Ӳ���״��� */
    hal_enable_radar_det(pst_mac_device->pst_device_stru, OAL_FALSE);

    /* �����¼�ͷ�е�VAP ID */
    pst_event->st_event_hdr.uc_vap_id = pst_mac_vap->uc_vap_id;

    FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(&(pst_event->st_event_hdr), DMAC_MISC_SUB_TYPE_RADAR_DETECT);

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);

    return OAL_SUCC;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

