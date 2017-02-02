/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_mgmt_sta.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��6��7��
  ����޸�   :
  ��������   : sta�����֡����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��7��
    ��    ��   : zhangheng
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
#include "dmac_mgmt_sta.h"
#include "dmac_main.h"
#include "oal_net.h"
#include "dmac_chan_mgmt.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_STA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


oal_uint32 dmac_mgmt_wmm_update_edca_machw_sta(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_sta_asoc_set_edca_reg_stru *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_sta;
    wlan_wme_ac_type_enum_uint8         en_ac_type;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_sta_asoc_set_edca_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_device[idx=%d] null.}", pst_event_hdr->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_sta = mac_res_get_dmac_vap(pst_reg_params->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_sta)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_dmac_vap[idx=%d] null.}", pst_reg_params->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_WMM_SET_PARAM_TYPE_DEFAULT == pst_reg_params->en_set_param_type)
    {
        /*ȥʹ��EDCA*/
        hal_disable_machw_edca(pst_device->pst_device_stru);
        pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;

        /* ����VOĬ�ϲ��� */
        hal_vap_set_machw_aifsn_ac(pst_dmac_sta->pst_hal_vap, WLAN_WME_AC_VO, DMAC_WMM_VO_DEFAULT_DECA_AIFSN);
#if 0
        hal_vap_set_machw_cw_vo(pst_dmac_sta->pst_hal_vap,
                                (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                                (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin);
#endif
        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin,
                                  WLAN_WME_AC_VO);
        hal_vap_set_machw_prng_seed_val_all_ac(pst_dmac_sta->pst_hal_vap);
        return OAL_SUCC;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy((oal_uint8*)&pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac, (oal_uint8*)&pst_reg_params->ast_wlan_mib_qap_edac, (OAL_SIZEOF(wlan_mib_Dot11QAPEDCAEntry_stru) * WLAN_WME_AC_BUTT));
#endif

    hal_enable_machw_edca(pst_dmac_sta->pst_hal_device);

    /* ����edca�Ĵ������� */
    hal_vap_set_machw_aifsn_all_ac(pst_dmac_sta->pst_hal_vap,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN);

    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmin,
                                  en_ac_type);
    }
#if 0
    hal_vap_set_machw_cw_bk(pst_dmac_sta->pst_hal_vap,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_be(pst_dmac_sta->pst_hal_vap,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vi(pst_dmac_sta->pst_hal_vap,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vo(pst_dmac_sta->pst_hal_vap,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin);
#endif
    hal_vap_set_machw_txop_limit_bkbe(pst_dmac_sta->pst_hal_vap,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    hal_vap_set_machw_txop_limit_vivo(pst_dmac_sta->pst_hal_vap,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);

    /*DTS: 1102 beacon֡��EDCA������û��LIFETIMEֵ��STA���ݱ���mibֵ����(mibֵΪ0),
    ע�͵�������ã����ռĴ�����������Ч���� */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    hal_vap_set_machw_edca_bkbe_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableMSDULifetime);
    hal_vap_set_machw_edca_vivo_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableMSDULifetime);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_adjust_bandwidth_sta
 ��������  : ����AP��(STA)���������������׼��Ҫ�л����Ĵ���ģʽ
 �������  : pst_mac_vap  : MAC VAP�ṹ��ָ�룬ָ��STA
 �������  : pen_bandwidth: ���º�Ĵ���ģʽ
 �� �� ֵ  : ��+ ���ú���  :+ ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void  dmac_chan_adjust_bandwidth_sta(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 *pen_bandwidth)
{
    wlan_channel_bandwidth_enum_uint8   en_curr_bandwidth      = pst_mac_vap->st_channel.en_bandwidth;
    wlan_channel_bandwidth_enum_uint8   en_announced_bandwidth = pst_mac_vap->st_ch_switch_info.en_new_bandwidth;

    *pen_bandwidth = en_curr_bandwidth;

    /* �����ǰ����ģʽ���´���ģʽ��ͬ����ֱ�ӷ��� */
    if (en_announced_bandwidth == en_curr_bandwidth)
    {
        return;
    }

    if (WLAN_BAND_WIDTH_20M == en_announced_bandwidth)
    {
        *pen_bandwidth = WLAN_BAND_WIDTH_20M;
    }
    else   /* �´���ģʽ����20MHz����STA�����ģʽ��Ҫ����������������ƥ�� */
    {
        /* ʹ��40MHz */
        /* (1) �û�����"40MHz����"����(��STA�� dot11FortyMHzOperationImplementedΪtrue) */
        /* (2) AP��40MHz���� */
        if (OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
        {
            switch (en_announced_bandwidth)
            {
                case WLAN_BAND_WIDTH_40PLUS:
                case WLAN_BAND_WIDTH_80PLUSPLUS:
                case WLAN_BAND_WIDTH_80PLUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40PLUS;
                    break;

                case WLAN_BAND_WIDTH_40MINUS:
                case WLAN_BAND_WIDTH_80MINUSPLUS:
                case WLAN_BAND_WIDTH_80MINUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40MINUS;
                    break;

                default:
                    *pen_bandwidth = WLAN_BAND_WIDTH_20M;
                    break;
            }
        }

        /* ʹ��80MHz */
        /* (1) �û�֧��80MHz����(��STA�� dot11VHTChannelWidthOptionImplementedΪ0) */
        if (OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        {
            if (WLAN_MIB_VHT_SUPP_WIDTH_80 == mac_mib_get_VHTChannelWidthOptionImplemented(pst_mac_vap))
            {
                *pen_bandwidth = en_announced_bandwidth;
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_chan_multi_select_channel_mac
 ��������  : ����device������VAP������SW/MAC/PHY/RF�е��ŵ��ʹ���ʹVAP���������ŵ���
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ��Ҫ�����õ��ŵ���
             en_bandwidth: ��Ҫ�����õĴ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_vap;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
        "{hmac_chan_multi_select_channel_mac::pst_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_select_channel_mac::none vap.}");
        return;
    }

    OAL_IO_PRINT("[DFS]hmac_chan_multi_select_channel_mac, Switching channel to %d! BW %d mode.\n", uc_channel, en_bandwidth);

#ifdef _PRE_WLAN_FEATURE_DBAC
    if (mac_is_dbac_running(pst_device))
    {
        dmac_chan_select_channel_mac(pst_mac_vap, uc_channel, en_bandwidth);
        return;
    }
#endif

    /* ����device������vap */
    for (uc_vap_idx = 0; uc_vap_idx <pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
            "{hmac_chan_multi_select_channel_mac::pst_vap null,vap_id=%d.}", pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* �л������ŵ����� */
        dmac_chan_select_channel_mac(pst_mac_vap, uc_channel, en_bandwidth);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_chan_sta_switch_channel
 ��������  : STA�л��ŵ�
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_chan_sta_switch_channel(mac_vap_stru *pst_mac_vap)
{
    wlan_channel_bandwidth_enum_uint8   en_new_bandwidth = WLAN_BAND_WIDTH_20M;

    if (WLAN_BAND_WIDTH_BUTT != pst_mac_vap->st_ch_switch_info.en_new_bandwidth)
    {
        dmac_chan_adjust_bandwidth_sta(pst_mac_vap, &en_new_bandwidth);
    }

    /* ��ֹӲ��ȫ������ֱ��STA�ŵ��л���� */
    dmac_chan_disable_machw_tx(pst_mac_vap);
    /* �л��ŵ� */
    dmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_ch_switch_info.uc_new_channel, en_new_bandwidth);

    /* ���øñ���������STA���ŵ��л�ʱ����link loss */
    pst_mac_vap->st_ch_switch_info.en_waiting_for_ap           = OAL_TRUE;

    /* STA���л������ŵ��� */
    pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero     = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_new_bandwidth            = WLAN_BAND_WIDTH_BUTT;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
}

/*****************************************************************************
 �� �� ��  : dmac_handle_tbtt_chan_mgmt_sta
 ��������  : STA��TBTT�ж��н����ŵ�����
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_handle_tbtt_chan_mgmt_sta(dmac_vap_stru *pst_dmac_vap)
{
    mac_vap_stru *pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        return;
    }

    /* ���AP���͵�CSA IE�е�"�ŵ��л�����"Ϊ�㣬�������л��ŵ� */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero)
    {
        if (pst_dmac_vap->st_linkloss_info.us_link_loss > WLAN_LINKLOSS_OFFSET_11H)
        {
            dmac_chan_sta_switch_channel(pst_mac_vap);
            dmac_vap_linkloss_clean(pst_dmac_vap);
        }
    }
    /* �ŵ��л��Ѿ���ɡ��������ŵ��ϵȴ�����AP���͵�Beacon֡ */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_for_ap)
    {
        /* �ȴ�һ��ʱ��������ŵ��ϻָ�Ӳ������(������ʱAP�п��ܻ�û���л������ŵ�) */
        if (pst_dmac_vap->st_linkloss_info.us_link_loss > WLAN_LINKLOSS_OFFSET_11H)
        {
            pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = OAL_FALSE;
            dmac_chan_enable_machw_tx(pst_mac_vap);
            dmac_vap_linkloss_clean(pst_dmac_vap);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
        }
    }

    /* ���AP���͵�CSA IE�е�"�ŵ��л�����"��Ϊ�㣬��ÿһ��TBTT�ж��м�һ */
    if (pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt > 0)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt--;
        if (0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)
        {
            if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel)
            {
                dmac_chan_sta_switch_channel(pst_mac_vap);
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_is_active_htsta
 ��������  : �ж�sta�Ƿ�Ϊ��Ծsta
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint8  dmac_mgmt_is_active_htsta(mac_vap_stru *pst_mac_vap)
{
    //TODO Ŀǰ�ú���ʼ�շ���true, ���б�Ҫ�ڴ˴������ж�sta�Ƿ�Ϊ��Ծht sta�Ĵ���
    return OAL_TRUE;
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : dmac_mgmg_need_obss_scan
 ��������  : �ж��Ƿ���Ҫ����obss scan
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint8  dmac_mgmt_need_obss_scan(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru                     *pst_device;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "dmac_mgmt_need_obss_scan::null param");
        return OAL_FALSE;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN,
            "{dmac_mgmt_need_obss_scan::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    if (0 != pst_device->st_p2p_info.uc_p2p_goclient_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN,
            "{dmac_mgmt_need_obss_scan:: stop obss can since this is p2p scanrio}");
        return OAL_FALSE;
    }
#endif

    //l00311403 ��ǰvht������obssɨ��
    if ( (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) &&
         (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state) &&
         (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)&&
         (OAL_TRUE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)) &&
         (OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
         (OAL_TRUE == dmac_mgmt_is_active_htsta(pst_mac_vap))
          )
     {
        return OAL_TRUE;
     }

    return OAL_FALSE;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

