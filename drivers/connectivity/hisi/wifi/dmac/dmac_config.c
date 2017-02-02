/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_config.c
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2013��1��8��
  ����޸�   :
  ��������   : ��������صĲ����ӿں���ʵ�ֵ�Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��1��8��
    ��    ��   : zourong
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
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "mac_data.h"
#include "mac_device.h"
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_psm_ap.h"
#include "dmac_rx_data.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_mgmt_sta.h"
#include "dmac_tx_complete.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_uapsd.h"
#include "dmac_blockack.h"
#include "dmac_beacon.h"
#include "dmac_user.h"
#include "dmac_11i.h"
#include "dmac_wep.h"
#include "dmac_uapsd.h"
#include "dmac_acs.h"
#include "dmac_reset.h"
#include "dmac_config.h"
#include "dmac_stat.h"
#include "dmac_data_acq.h"
#include "dmac_user_track.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_txopps.h"
#include "dmac_dft.h"
#include "dmac_ap_pm.h"
#include "dmac_beacon.h"
#include "dmac_scan.h"

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
#include "cali_data.h"
#include "pm_extern.h"
#endif
#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_frame_filter_test.h"
#include "dmac_wmm_test.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "hal_witp_phy_reg.h"
#include "hal_witp_pa_reg.h"

#include "hal_hi1102_phy_reg.h"
#include "hal_hi1102_mac_reg.h"
#endif

#ifdef _PRE_WIFI_DMT
#include "hal_witp_dmt_if.h"
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "pm_extern.h"
#include "dmac_sta_pm.h"
#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

#include "dmac_11w.h"
#endif
#include "dmac_chan_mgmt.h"

#include "dmac_reset.h"
#include "oal_net.h"
#include "dmac_config.h"
#include "dmac_main.h"
#include "dmac_rx_filter.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#include "core_cr4.h"
#endif
#include "oal_profiling.h"

#ifdef _PRE_SUPPORT_ACS
#include "dmac_acs.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "mac_board.h"
#endif

#include "dmac_arp_offload.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_CONFIG_C

mac_rssi_debug_switch_stru  g_st_rssi_debug_switch_info = {0};

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
extern oal_uint16 g_usUsedMemForStop;
extern oal_uint16 g_usUsedMemForstart;
#endif


/*****************************************************************************
  3 ��̬��������
*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_fbm(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_pgl(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_mtpgl(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ta(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ra(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_cc(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data0(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data1(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data2(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data3(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_power(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_shortgi(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_preamble_mode(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_rtscts(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_lsigtxop(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_smooth(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_snding(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_txbf(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
OAL_STATIC oal_void  dmac_config_set_dscr_stbc(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
#endif
OAL_STATIC oal_void  dmac_config_get_dscr_ess(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ch_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_uint32  dmac_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32   dmac_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

#ifdef _PRE_DEBUG_MODE
OAL_STATIC oal_uint32  dmac_config_get_all_reg_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#if !((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
extern oal_uint32  dmac_config_set_meta(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param);
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
extern void OML_LOG_SetLevel(oal_uint8 ucModuleID, oal_uint8 ucLevel);
#endif

#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_config_report_vap_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#define DMAC_SET_NETBUF_CB(  evt_type, \
                            tx_usr_idx,  \
                            ismcast, \
                            is_bar,  \
                            tid)  do{\
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);\
    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());\
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)               = evt_type;    \
        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)             = tx_usr_idx;   \
        MAC_GET_CB_IS_MCAST(pst_tx_ctl)             = ismcast; \
        mac_set_cb_is_bar(pst_tx_ctl, is_bar);               \
        mac_set_cb_tid(pst_tx_ctl, tid);                        \
        mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);}while(0)




OAL_STATIC dmac_set_dscr_func  g_dmac_config_set_dscr_param[] =
{
    dmac_config_set_dscr_fbm,       /* fbm, ��Ӧ����������13�е�freq bandwidth mode */
    dmac_config_set_dscr_pgl,       /* �ѷ��� */
    dmac_config_set_dscr_mtpgl,     /* �ѷ��� */
    OAL_PTR_NULL,                   /* �ѷ��� */
    dmac_config_set_dscr_ta,        /* ta��tx antena����Ӧ����������15�е�TXRTS Antenna */
    dmac_config_set_dscr_ra,        /* ra: rx antena, ��Ӧ����������15�е�RXCTRL Antenna */
    dmac_config_set_dscr_cc,        /* cc: channel code, ��Ӧ����������13�е�channel code */
    dmac_config_set_dscr_data0,     /* data0����Ӧ����������14�У�32bit 10����ֵ */
    dmac_config_set_dscr_data1,     /* data1����Ӧ����������19�У� */
    dmac_config_set_dscr_data2,     /* data2����Ӧ����������20�У� */
    dmac_config_set_dscr_data3,     /* data3����Ӧ����������21�У� */
    dmac_config_set_dscr_power,     /* tx power: ��Ӧ����������22�� */
    dmac_config_set_dscr_shortgi,         /* ����short GI��long GI*/
    dmac_config_set_dscr_preamble_mode,   /* ����preamble mode*/
    dmac_config_set_dscr_rtscts,         /* ����rts/cts�Ƿ�ʹ��*/
    dmac_config_set_dscr_lsigtxop,       /* ����lsig txop�Ƿ�ʹ��*/
    dmac_config_set_dscr_smooth,        /* ���ý��ն��Ƿ���ŵ�������ƽ�� */
    dmac_config_set_dscr_snding,        /* ����Soundingģʽ */
    dmac_config_set_dscr_txbf,          /* ����txbfģʽ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    dmac_config_set_dscr_stbc,          /* ����stbcģʽ */
#endif
    dmac_config_get_dscr_ess,           /* ��ȡ��չ�ռ��� */
    dmac_config_set_dscr_dyn_bw,        /* ����DYN_BANDWIDTH_IN_NON_HT */
    dmac_config_set_dscr_dyn_bw_exist,  /* ����DYN_BANDWIDTH_IN_NON_HT exist */
    dmac_config_set_dscr_ch_bw_exist,   /* ����CH_BANDWIDTH_IN_NON_HT exist*/
};

oal_uint32 g_ul_first_timestamp = 0;    /*��¼����ͳ�Ƶ�һ��ʱ���*/
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_send_sys_event
 ��������  : ���¼���HMAC��, ͬ��HMAC����
 �������  : pst_mac_vap  : VAP
             en_cfg_id: ����id
             us_len: ��Ϣ����
             puc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param)
{
    oal_uint32                  ul_ret;
    frw_event_mem_stru         *pst_event_mem;
    dmac_to_hmac_cfg_msg_stru  *pst_syn_msg;
    frw_event_stru             *pst_event;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_cfg_msg_stru) - 4 + us_len);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_send_sys_event::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ����¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_SDT_REG,
                        DMAC_TO_HMAC_SYN_CFG,
                        OAL_SIZEOF(dmac_to_hmac_cfg_msg_stru) - 4 + us_len,
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    pst_syn_msg = (dmac_to_hmac_cfg_msg_stru *)pst_event->auc_event_data;

    DMAC_INIT_SYN_MSG_HDR(pst_syn_msg, en_cfg_id, us_len);

    /* ��д����ͬ����Ϣ���� */
    oal_memcopy(pst_syn_msg->auc_msg_body, puc_param, us_len);

    /* �׳��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_send_sys_event::frw_event_dispatch_event failed[%d].}",ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_send_sys_event::vap mode[%d],vap state[%d],cfgid[%d]}",
                                      pst_mac_vap->en_vap_mode,
                                      pst_mac_vap->en_vap_state,
                                      en_cfg_id);

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
OAL_STATIC oal_void  dmac_config_set_dscr_fbm(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_rate.uc_channel_bandwidth = (oal_uint8)l_value;
    (WLAN_BAND_ASSEMBLE_AUTO == pst_dmac_vap->st_tx_alg.st_rate.uc_channel_bandwidth)?(pst_dmac_vap->bit_bw_cmd = 0):(pst_dmac_vap->bit_bw_cmd = 1);
}


OAL_STATIC oal_void  dmac_config_set_dscr_pgl(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_tx_power.bit_pa_gain_level3 = (oal_uint8)l_value;
}


OAL_STATIC oal_void  dmac_config_set_dscr_mtpgl(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_tx_power.bit_pa_gain_level0 = (oal_uint8)l_value;
}


OAL_STATIC oal_void  dmac_config_set_dscr_ta(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_antenna_params.uc_tx_rts_antenna = (oal_uint8)l_value;
}


OAL_STATIC oal_void  dmac_config_set_dscr_ra(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_antenna_params.uc_rx_ctrl_antenna = (oal_uint8)l_value;
}


OAL_STATIC oal_void  dmac_config_set_dscr_cc(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    hal_to_dmac_device_stru         *pst_hal_device_base;
    wlan_phy_protocol_enum_uint8    en_curr_prot;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
       OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                             "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
       return;
    }

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::invalid frame type[%02x].}", uc_type);
            return;
    }

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
       hal_set_tx_dscr_field(pst_hal_device_base, (oal_uint8)l_value, HAL_RF_TEST_CHAN_CODE);
    }

    /* ����ֵ���� */
    if ((1 == l_value) && (WLAN_11B_PHY_PROTOCOL_MODE == en_curr_prot || WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE == en_curr_prot))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_config_set_dscr_cc::can not set channel code to 1 in non-HT mode.}");
    }
    else if ((1 == l_value) || (0 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::channel code=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::invalid channel code=%d", l_value);
    }
}
OAL_STATIC oal_void  dmac_config_set_dscr_data0(oal_int32 l_value, oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;

    }
}


OAL_STATIC oal_void  dmac_config_set_dscr_data1(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}


OAL_STATIC oal_void dmac_config_set_dscr_data2(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}


OAL_STATIC oal_void  dmac_config_set_dscr_data3(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}


OAL_STATIC oal_void  dmac_config_set_dscr_power(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32 *pul_txpower;

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_data_mcast.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_data_bcast.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_vht.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_ht.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_11ag.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_11b.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_shortgi
 ��������  : ����gi���
 �������  :  l_value  : 0 long GI, 1: short GI
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_shortgi(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_vap_stru *pst_mac_vap = (mac_vap_stru *)pst_dmac_vap;
#endif
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
       OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                             "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
       return;
    }
#endif

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::uc_type=%d", uc_type);
            return;
    }

#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
       hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    if ((0 == l_value) || (1 == l_value))
    {
        pst_dmac_vap->uc_short_gi = (oal_uint8)l_value;
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::short gi enable l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::invalid short gi enable l_value=%d", l_value);
    }
#endif
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_preamble_mode
 ��������  : ����preamble_mode
 �������  :
             Protocol mode��11b
               0: 11b Short Preamble
               1: 11b Long Preamble
             Protocol mode��legacy OFDM
               0: legacy OFDM tx format
               1: reserved
             Protocol mode��HT
               0: HT Mixed Mode Frame
               1: HT Green Field Frame
             Protocol mode��VHT
               0: VHT Preamble
               1: reserved
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_preamble_mode(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
        hal_to_dmac_device_stru         *pst_hal_device_base;

        pst_hal_device_base = pst_dmac_vap->pst_hal_device;
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
        {
           OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                                 "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
           return;
        }
#endif

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::invalid frame type=%d", uc_type);
            return;
    }

#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
	/* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
       hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::invalid l_value=%d", l_value);
    }
#endif
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_rtscts
 ��������  : ����rts cts enable
 �������  :  l_value  : 0 long GI, 1: short GI
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_rtscts(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_lsigtxop
 ��������  : ����lsig txop
 �������  :  l_value  : 0 lsig txop diable, 1: lsig txop enable
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_lsigtxop(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_smooth
 ��������  : ����smoothing
 �������  :  l_value  : 0 smoothing is not recommended,
                         1 smoothing is recommended
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_smooth(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_snding
 ��������  : ����soundingģʽ
 �������  :  l_value  : 0: no sounding             1: NDP sounding
                         2: staggered sounding      3: legacy sounding
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_snding(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::invalid frame type=%d", uc_type);
            return;
    }

    /* ��ӡTX������ */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_txbf
 ��������  : ����TXBF
 �������  :  l_value  : 0: Non TXBF                1: Explicit TXBF
                         2: �û��޸�֪TXBF          3: Reserved
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_txbf(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::invalid frame type=%d", uc_type);
            return;
    }

    /* ��ӡTX������ */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::invalid l_value=%d", l_value);
    }
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_stbc
 ��������  : ����STBC
 �������  :  l_value  : 0: ������STBC              1: Nsts - Nss = 1
                         2: Nsts - Nss = 2          3: Reserved
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_stbc(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::invalid frame type=%d", uc_type);
            return;
    }

    /* ��ӡTX������ */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::l_valuee=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::invalid l_value=%d", l_value);
    }
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_config_get_dscr_ess
 ��������  : ��ȡTX����������չ�ռ���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_get_dscr_ess(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8   uc_ess_num;

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_data_mcast.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_data_bcast.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.uc_extend_spatial_streams;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_vht.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_ht.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_11ag.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_11b.st_rate.uc_extend_spatial_streams;
            break;
    #endif

        default:
            uc_ess_num = 0;
            break;
    }

    /* ��ӡTX������ */
    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_get_dscr_ess::uc_ess_num=%d", uc_ess_num);
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_dyn_bw
 ��������  : ����STBC
 �������  :  l_value  : 0: not present
                         1: present
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.dyn_bandwidth_in_non_ht  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_dyn_bw_exist
 ��������  : ����STBC
 �������  :  l_value  : 0: no existance
                         1: existance
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.dyn_bandwidth_in_non_ht_exist  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_dscr_ch_bw_exist
 ��������  : ����STBC
 �������  :  l_value  : 0: no existance
                         1: existance
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : ���ɭ
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_ch_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.ch_bandwidth_in_non_ht_exist  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::invalid l_valueype=%d", l_value);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_get_cmd_one_arg
 ��������  : ��ȡ�ַ�����һ������ �Կո�Ϊ�������ֱ�ʶ
 �������  : pc_cmd         : ������ַ���
 �������  : pc_arg         : ��һ������
             pul_cmd_offset : ��һ�������ĳ���
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_get_cmd_one_arg(oal_int8 *pc_cmd, oal_int8 *pc_arg, oal_uint32 *pul_cmd_offset)
{
    oal_int8   *pc_cmd_copy;
    oal_uint32  ul_pos = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pc_cmd) || (OAL_PTR_NULL == pc_arg) || (OAL_PTR_NULL == pul_cmd_offset)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_CFG,
                       "{dmac_get_cmd_one_arg::param null, pc_cmd=%d pc_arg=%d pul_cmd_offset=%d.}",
                       pc_cmd, pc_arg, pul_cmd_offset);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pc_cmd_copy = pc_cmd;

    /* ȥ���ַ�����ʼ�Ŀո� */
    while (' ' == *pc_cmd_copy)
    {
        ++pc_cmd_copy;
    }

    while ((' ' != *pc_cmd_copy) && ('\0' != *pc_cmd_copy))
    {
        pc_arg[ul_pos] = *pc_cmd_copy;
        ++ul_pos;
        ++pc_cmd_copy;

        if (OAL_UNLIKELY(ul_pos >= DMAC_HIPRIV_CMD_NAME_MAX_LEN))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_get_cmd_one_arg::ul_pos=%d", ul_pos);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }

    pc_arg[ul_pos]  = '\0';

    /* �ַ�������β�����ش����� */
    if (0 == ul_pos)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_get_cmd_one_arg::ul_pos=0.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pul_cmd_offset = (oal_uint32)(pc_cmd_copy - pc_cmd);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_reg_display_test
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_display_test(mac_vap_stru *pst_mac_vap, oal_uint32 ul_start_addr, oal_uint32 ul_end_addr)
{
    mac_device_stru      *pst_device;
    oal_uint32            ul_addr;
    oal_uint32            ul_val = 0;

    if (ul_start_addr % 4 != 0 || ul_end_addr % 4 != 0)
    {
        return;
    }

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    for (ul_addr = ul_start_addr; ul_addr <= ul_end_addr; ul_addr += 4)
    {
        hal_reg_info(pst_device->pst_device_stru, ul_addr, &ul_val);
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x", ul_addr, ul_val);
        OAL_IO_PRINT("dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x\r\n", ul_addr, ul_val);
    }
}



/*****************************************************************************
 �� �� ��  : dmac_config_reg_display_test16
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_display_test16(mac_vap_stru *pst_mac_vap, oal_uint32 ul_start_addr, oal_uint32 ul_end_addr)
{
    mac_device_stru      *pst_device;
    oal_uint32            ul_addr;
    oal_uint16            us_val = 0;

    if (ul_start_addr % 2 != 0 || ul_end_addr % 2 != 0)
    {
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test16::not mod 2, start[%08x], end[%08x].", ul_start_addr, ul_end_addr);
        return;
    }

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_reg_display_test16::pst_device null.");
        return;
    }

    for (ul_addr = ul_start_addr; ul_addr <= ul_end_addr; ul_addr += 2)
    {
        hal_reg_info16(pst_device->pst_device_stru, ul_addr, &us_val);
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x", ul_addr, us_val);
        OAL_IO_PRINT("dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x\r\n", ul_addr, us_val);
    }
}



/*****************************************************************************
 �� �� ��  : dmac_config_reg_write_test
 ��������  : д�Ĵ���������PHY,SOC,MAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_write_test(mac_vap_stru *pst_mac_vap, oal_uint32 ul_addr, oal_uint32 ul_val)
{
    mac_device_stru      *pst_device;
    oal_int8              ac_buf[64] = {0};

    if (ul_addr % 4 != 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reg_write_test::ul_addr=%d", ul_addr);
        return;
    }

    OAL_SPRINTF((char*)ac_buf, OAL_SIZEOF(ac_buf), "reg_write:addr=0x%08x, val=0x%08x.\n", ul_addr, ul_val);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_write_test::reg_write:addr=0x%08x, val=0x%08x.", ul_addr, ul_val);
    oam_print(ac_buf);

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    hal_reg_write(pst_device->pst_device_stru, ul_addr, ul_val);
}

/*****************************************************************************
 �� �� ��  : dmac_config_reg_write_test16
 ��������  : д�Ĵ���������PHY,SOC,MAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_write_test16(mac_vap_stru *pst_mac_vap, oal_uint32 ul_addr, oal_uint16 us_val)
{
    mac_device_stru      *pst_device;
    oal_int8              ac_buf[64] = {0};

    if (ul_addr % 2 != 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reg_write_test::ul_addr=%d", ul_addr);
        return;
    }

    OAL_SPRINTF((char*)ac_buf, OAL_SIZEOF(ac_buf), "reg_write:addr=0x%08x, val=0x%04x.\n", ul_addr, us_val);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_write_test::reg_write:addr=0x%08x, val=0x%04x.", ul_addr, us_val);
    oam_print(ac_buf);

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    hal_reg_write16(pst_device->pst_device_stru, ul_addr, us_val);
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_bss_type
 ��������  : ����bss type
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* ����mibֵ */
    return mac_mib_set_bss_type(pst_mac_vap, uc_len, puc_param);
}
oal_uint32  dmac_config_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_mode_param_stru     *pst_prot_param;
    dmac_vap_stru               *pst_dmac_vap;
    mac_device_stru             *pst_mac_device;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_mode::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mode::pst_mac_device null.}");
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* ��ȡdmac vap�ṹ�� */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TXBF, "{dmac_config_set_mode::pst_dmac_vap null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    #if 0 // gaolin��ACS����֮�󣬻����ò�ͬ���ŵ���DMAC������·��������ϵband��channel��λ
    /* �Ѿ����ù�ʱ������Ҫ������*/
    if (WLAN_BAND_WIDTH_BUTT != pst_mac_device->en_max_bandwidth)
    {
        return OAL_SUCC;
    }
    #endif

    pst_prot_param = (mac_cfg_mode_param_stru *)puc_param;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ��¼Э��ģʽ, band, bandwidth��mac_vap�� */
    pst_mac_vap->en_protocol                              = pst_prot_param->en_protocol;
    pst_mac_vap->st_channel.en_band                       = pst_prot_param->en_band;
    pst_mac_vap->st_channel.en_bandwidth                  = pst_prot_param->en_bandwidth;
    pst_mac_vap->st_ch_switch_info.en_user_pref_bandwidth = pst_prot_param->en_bandwidth;

#ifdef _PRE_WLAN_FEATURE_11AC2G
    if ((WLAN_VHT_MODE == pst_mac_vap->en_protocol)
        && (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band))
    {
        mac_vap_set_11ac2g(pst_mac_vap, OAL_TRUE);
    }
    else
    {
        mac_vap_set_11ac2g(pst_mac_vap, OAL_FALSE);
    }
#endif

    /* ����Э�����vap���� */
    mac_vap_init_by_protocol(pst_mac_vap, pst_prot_param->en_protocol);

    /* ���ݴ�����Ϣ����Mib */
    mac_vap_change_mib_by_bandwidth(pst_mac_vap, pst_prot_param->en_bandwidth);

    /* ����device��Ƶ�μ���������Ϣ */
    pst_mac_device->en_max_bandwidth = pst_prot_param->en_bandwidth;
    pst_mac_device->en_max_band      = pst_prot_param->en_band;

    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                  "{dmac_config_set_mode::protocol=%d, band=%d, bandwidth=%d.}",
                  pst_mac_vap->en_protocol, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth);
#endif
    if (pst_mac_vap->en_protocol < WLAN_HT_MODE)
    {
        pst_dmac_vap->en_bfee_actived       = OAL_FALSE;
        pst_dmac_vap->en_bfer_actived       = WLAN_BFER_ACTIVED;
        pst_dmac_vap->en_mu_bfee_actived    = OAL_FALSE;
        pst_dmac_vap->en_txstbc_actived     = OAL_FALSE;
    }
    else
    {
        pst_dmac_vap->en_bfee_actived       = OAL_TRUE;
        pst_dmac_vap->en_bfer_actived       = WLAN_BFER_ACTIVED;
        pst_dmac_vap->en_mu_bfee_actived    = OAL_TRUE;
        pst_dmac_vap->en_txstbc_actived     = WLAN_TXSTBC_ACTIVED;
#ifdef _PRE_WLAN_FEATURE_TXOPPS
        if (pst_mac_vap->en_protocol == WLAN_VHT_MODE ||
             pst_mac_vap->en_protocol == WLAN_VHT_ONLY_MODE)
        {
            pst_dmac_vap->en_mu_bfee_actived   = WLAN_MU_BFEE_ACTIVED;
        }
#endif
    }

    hal_disable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

    /* ��hal�ӿ�����Ƶ�� */
    hal_set_freq_band(pst_mac_device->pst_device_stru, pst_prot_param->en_band);
#if 0
#ifdef _PRE_WLAN_FEATURE_DFS
    /* mayuan DFS begin */
    /* �ر��״��⣬��ʱ����ʱ���ڴ� */
    if (WLAN_BAND_5G == pst_prot_param->en_band)
    {
        if (0 != pst_mac_device->us_dfs_timeout)
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
    }
    /* mayuan DFS end */
#endif
#endif
    /* ��hal�ӿ����ô��� */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /*dummy*/
#else
    if (pst_prot_param->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_mode:: fpga is not support 80M.}\r\n");
        pst_prot_param->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif
    hal_set_bandwidth_mode(pst_mac_device->pst_device_stru, pst_prot_param->en_bandwidth);

    hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

    /* ֪ͨ�㷨 */
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_mac_addr
 ��������  : dmac����mac��ַ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mac_addr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru  *pst_param;
    dmac_vap_stru                 *pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru               *pst_mac_device;
    hal_to_dmac_device_stru       *pst_hal_device;
#endif

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P ����MAC ��ַmib ֵ��Ҫ����P2P DEV ��P2P_CL/P2P_GO,P2P_DEV MAC ��ַ���õ�p2p0 MIB �� */
    if (pst_param->en_p2p_mode == WLAN_P2P_DEV_MODE)
    {
        /* �����p2p0 device��������MAC ��ַ��auc_p2p0_dot11StationID ��Ա�� */
        oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID,
                        pst_param->auc_station_id);
    }
    else
#endif
    {
        /* ����mibֵ, Station_ID */
        mac_mib_set_station_id(pst_mac_vap, OAL_SIZEOF(mac_cfg_staion_id_param_stru), puc_param);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_config_set_mac_addr::mac_res_get_dev pst_mac_device null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* ����mibֵ, Station_ID */
            mac_mib_set_station_id(pst_mac_vap, OAL_SIZEOF(mac_cfg_staion_id_param_stru), puc_param);

            /* ��Proxy STA��mac ��ַд�뵽peer addr �Ĵ�����,����hal_vap_id��Proxy STA��mac_addr�����Ӧ�� */
            hal_set_proxysta_vap_addr(pst_hal_device, pst_dmac_vap->pst_hal_vap->uc_vap_id, mac_mib_get_StationID(pst_mac_vap));
        }
        else if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* ��main proxysta(sta0)�ĵ�ַд�� mac_device_stru�� */
            oal_set_mac_addr(pst_mac_device->st_device_proxysta.auc_mac_addr, pst_param->auc_station_id);

            /* hal����mac��ַ */
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set main proxysta mac addr succ!}");
        }
        else
        {
            /* hal����mac��ַ */
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set mac addr succ!}");

        }
    }
    else
    {
        /* hal����mac��ַ */
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set mac addr succ!}");
    }
#else
    /* hal����mac��ַ */
#ifdef _PRE_WLAN_FEATURE_P2P
    if (pst_param->en_p2p_mode == WLAN_P2P_DEV_MODE)
    {
        /* ����p2p0 �����ַ����Ҫ���õ�p2p0_hal_vap �У���������MAC ��ַ���õ�hal_vap �� */
        hal_vap_set_macaddr(pst_dmac_vap->pst_p2p0_hal_vap, pst_param->auc_station_id);
    }
    else
#endif
    {
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
    }
    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"{dmac_config_set_mac_addr::set mac addr succ!}");
#endif


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_freq
 ��������  : �����ŵ�
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_freq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32               l_value;
    mac_device_stru        *pst_mac_device;
    oal_uint8               uc_channel_idx;
    oal_uint32              ul_ret;
#ifdef _PRE_WLAN_HW_TEST
    mac_cfg_mode_param_stru     st_prot_param;
    oal_uint8                   uc_msg_len = 0;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_cfg_channel_param_stru l_channel_param;
#endif

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);



#ifdef _PRE_WIFI_DMT
    if (l_value >= 36)
    {
        g_ul_dmt_scan_flag = 1;   /* DMT����ɨ������ŵ�����ɨ�裬��������ȫ�ŵ�ɨ��   */
    }
#endif

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, (oal_uint8)l_value, &uc_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                       "{dmac_config_set_freq::mac_get_channel_idx_from_num failed[%d], band[%d], channel num[%d].}", ul_ret, pst_mac_vap->st_channel.en_band, (oal_uint8)l_value);
        return ul_ret;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_vap->st_channel.uc_chan_number = (oal_uint8)l_value;
    pst_mac_vap->st_channel.uc_idx         = uc_channel_idx;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#if 0
    pst_mac_device->uc_max_channel = (oal_uint8)l_value;    /* hi1102-cb allways set at both side */
#else
    mac_device_get_channel(pst_mac_device, &l_channel_param);
    l_channel_param.uc_channel = (oal_uint8)l_value;
    mac_device_set_channel(pst_mac_device, &l_channel_param);
#endif

#endif

    /* ֪ͨ�㷨 */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /* ����hal�ӿ������ŵ��� */
    hal_set_primary_channel(pst_mac_device->pst_device_stru,
                           (oal_uint8)l_value,
                            pst_mac_vap->st_channel.en_band,
                            uc_channel_idx,
                            pst_mac_vap->st_channel.en_bandwidth);
#else
    if (pst_mac_vap->st_channel.en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_freq:: fpga is not support 80M.}\r\n");
        /* ����hal�ӿ������ŵ��� */
        hal_set_primary_channel(pst_mac_device->pst_device_stru,
                                (oal_uint8)l_value,
                                pst_mac_vap->st_channel.en_band,
                                uc_channel_idx,
                                WLAN_BAND_WIDTH_20M);
    }
    else
    {
        /* ����hal�ӿ������ŵ��� */
        hal_set_primary_channel(pst_mac_device->pst_device_stru,
                                (oal_uint8)l_value,
                                pst_mac_vap->st_channel.en_band,
                                uc_channel_idx,
                                pst_mac_vap->st_channel.en_bandwidth);
    }
#endif


#ifdef _PRE_WLAN_DFT_EVENT
    oam_event_chan_report((oal_uint8)l_value);
#endif

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        if (WLAN_BAND_2G == (pst_mac_vap->st_channel.en_band) && (WLAN_VHT_MODE == pst_mac_vap->en_protocol))
        {
            hal_set_phy_tx_scale(pst_mac_device->pst_device_stru, OAL_TRUE);

            st_prot_param.en_band       = pst_mac_vap->st_channel.en_band;
            st_prot_param.en_bandwidth  = pst_mac_vap->st_channel.en_bandwidth;
            st_prot_param.en_protocol   = pst_mac_vap->en_protocol;

            dmac_config_set_mode(pst_mac_vap, uc_msg_len, (oal_uint8 *)&st_prot_param);
        }
        else
        {
            hal_set_phy_tx_scale(pst_mac_device->pst_device_stru, OAL_FALSE);
        }
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_concurrent
 ��������  : dmac �����豸�����û���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_concurrent(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32  l_value;

    l_value = *((oal_int32 *)puc_param);

    mac_res_set_max_asoc_user((oal_uint16)l_value);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_concurrent::l_value=%d.}", l_value);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_ssid
 ��������  : ����ssid
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* ����mibֵ */
    return mac_mib_set_ssid(pst_mac_vap, uc_len, puc_param);
}
oal_uint32  dmac_config_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                         *pst_mac_device;
    mac_pno_sched_scan_mgmt_stru            *pst_pno_scan_mgmt;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::pst_mac_device is null.}");
        return OAL_FAIL;
    }

    /* �ж�pno�Ƿ��Ѿ�ֹͣ�����ֹͣ����pnoɨ��Ĺ���ṹ��ָ��Ϊnull */
    if (OAL_PTR_NULL == pst_mac_device->pst_pno_sched_scan_mgmt)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::pno sched scan already stop.}");
        return OAL_SUCC;
    }

    /* ��ȡpnoɨ�����ṹ�� */
    pst_pno_scan_mgmt = pst_mac_device->pst_pno_sched_scan_mgmt;

    /* ɾ��PNO����ɨ�趨ʱ�� */
    dmac_scan_stop_pno_sched_scan_timer((void *)pst_pno_scan_mgmt);

    /* ֹͣ����PNO����ɨ��ʱ */
    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (WLAN_SCAN_MODE_BACKGROUND_PNO == pst_mac_device->st_scan_params.en_scan_mode))
    {
        /* ɾ��ɨ�趨ʱ�� */
        if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        }

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::stop pno scan.}");

        /* ����ɨ��״̬Ϊ���� */
        pst_mac_device->en_curr_scan_state = MAC_SCAN_STATE_IDLE;
    }

    /* �ͷ�PNO����ṹ���ڴ� */
    OAL_MEM_FREE(pst_mac_device->pst_pno_sched_scan_mgmt, OAL_TRUE);
    pst_mac_device->pst_pno_sched_scan_mgmt = OAL_PTR_NULL;

    //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::go last.}");

    return OAL_SUCC;
}


oal_uint32  dmac_config_scan_abort(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru     *pst_mac_device;

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                     "{dmac_config_scan_abort::vap_id[%d] scan abort.}", pst_mac_vap->uc_vap_id);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_scan_abort::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��Ҫ��ֹɨ���vap������ɨ���vap��ͬһ��vap����ֹͣɨ�� */
    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (pst_mac_vap->uc_vap_id == pst_mac_device->st_scan_params.uc_vap_id))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_scan_abort::stop scan.}");
        dmac_scan_abort(pst_mac_device);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#ifdef _PRE_WLAN_FEATURE_BTCOEX
oal_uint32 dmac_config_btcoex_assoc_state_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    oal_uint8   uc_chan_idx;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    coex_preempt_frame_enum_uint8 en_preempt_type;

    pst_mac_device = mac_res_get_dev((oal_uint32)pst_mac_vap->uc_device_id);

    pst_hal_device = pst_mac_device->pst_device_stru;

    en_preempt_type = BTCOEX_NOFRAME;

    pst_hal_device->st_btcoex_wifi_status.en_all_abort_preempt_type = en_preempt_type;

    dmac_btcoex_init_preempt(pst_mac_vap, pst_mac_user, en_preempt_type);

    /* ״̬�ϱ�BT  */
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            "{dmac_config_btcoex_assoc_state_syn::channel state: band->%d, channel->%d, bandwidth->%d.",
            pst_mac_vap->st_channel.en_band,
            pst_mac_vap->st_channel.uc_chan_number,
            pst_mac_vap->st_channel.en_bandwidth);
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);    // Ƶ��
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);    // �ŵ�
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6); // ����
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_coex_sw_irq_set(BIT5);

    return OAL_SUCC;
}
#endif
oal_uint32  dmac_config_set_shortgi(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    shortgi_cfg_stru    *shortgi_cfg;

    shortgi_cfg = (shortgi_cfg_stru *)puc_param;

    switch(shortgi_cfg->uc_shortgi_type)
    {
        case SHORTGI_20_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = OAL_FALSE;
            }
            break;

        case SHORTGI_40_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented = OAL_FALSE;
            }
            break;

        case SHORTGI_80_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = OAL_FALSE;
            }
            break;
        default:
            break;

    }
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_vap_state_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
//#if defined(_PRE_WLAN_FEATURE_STA_PM) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    dmac_vap_stru *pst_dmac_vap;
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
//#endif

    //OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_vap_state_syn::uc_len = %d, en state = %d.}", uc_len, *puc_param);

    /* ͬ��vap״̬ */
    //if (!(IS_P2P_CL(pst_mac_vap) && (pst_mac_vap->us_user_nums > 0)))
    {
        pst_mac_vap->en_vap_state = (mac_vap_state_enum_uint8)(*puc_param);
    }

    /* STA ģʽ��ֻ��UP״̬�ſ���keepalive��ʱ�� */
    if ((MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state)
        && (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA))
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_KEEPALIVE, 0, OAL_PTR_NULL);
#endif
    }
    /* STA ģʽ��ֻ��UP״̬�ſ���keepalive��ʱ�� */
    if ((MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    && (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA))
    {
        /* ��ʱ�ر�keepalive */
        pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive   =  OAL_FALSE;

    }

    /* 20/40�����߼�����ʱ���ж��Ƿ�����obssɨ�趨ʱ�� */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* STAģʽ������Ҫobssɨ�趨ʱ��������ʱ�� */
    if ((OAL_TRUE == dmac_mgmt_need_obss_scan(pst_mac_vap)) &&
         (OAL_FALSE == pst_dmac_vap->uc_obss_scan_timer_started) )
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_config_vap_state_syn:: start obss scan}");
        dmac_scan_start_obss_timer(pst_mac_vap);
    }
    //else if (OAL_TRUE == pst_dmac_vap->uc_obss_scan_timer_started)
    //{
    //    OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_config_vap_state_syn:: obss scan timer already started}");
    //}
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_change_state_syn(pst_mac_vap->en_vap_state);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_set_stbc_cap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    oal_bool_enum_uint8   uc_value;

    uc_value = (oal_bool_enum_uint8)*puc_param;

    if (uc_value > 1)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_stbc_cap::stbc_value is limit! value = [%d].}", uc_value);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11RxSTBCOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated                  = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTTxSTBCOptionImplemented   = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTRxSTBCOptionImplemented   = uc_value;

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_set_ldpc_cap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_bool_enum_uint8   uc_value;

    uc_value = (oal_bool_enum_uint8)(*puc_param);

    if (uc_value > 1)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ldpc_cap::ldpc_value is limit! value = [%d].}\r\n", uc_value);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated                  = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTLDPCCodingOptionImplemented   = uc_value;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_STA_PM
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD

OAL_STATIC oal_uint32 dmac_config_set_uapsd_para(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_uapsd_sta_stru   *pst_uapsd_info = (mac_cfg_uapsd_sta_stru *)puc_param;

    /* uc_max_sp_len */
    if (pst_uapsd_info->uc_max_sp_len > 6)
    {
       OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_uapsd_para::uc_max_sp_len[%d] > 6!}\r\n", pst_uapsd_info->uc_max_sp_len);
       return OAL_FAIL;
    }

    mac_vap_set_uapsd_para(pst_mac_vap, pst_uapsd_info);

    return OAL_SUCC;
}
#endif
#endif
#endif  /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC */


OAL_STATIC oal_uint32  dmac_config_user_asoc_state_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_user_asoc_state_stru *pst_user_asoc_info;
    mac_user_stru                *pst_mac_user;

    pst_user_asoc_info = (mac_h2d_user_asoc_state_stru *)puc_param;

    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_user_asoc_state_syn::us_user_idx = %d, user state = %d.}",
                  pst_user_asoc_info->us_user_idx, pst_user_asoc_info->en_asoc_state);

    /* ��ȡDMACģ���û��ṹ�� */
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_asoc_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_asoc_state_syn::pst_mac_user null.user idx [%d]}", pst_user_asoc_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ͬ��user����״̬ */
    mac_user_set_asoc_state(pst_mac_user, pst_user_asoc_info->en_asoc_state);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_config_btcoex_assoc_state_syn(pst_mac_vap, pst_mac_user);
#endif
#endif
    return OAL_SUCC;
}



oal_uint32 dmac_config_user_cap_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_stru              *pst_mac_user;
    mac_h2d_usr_cap_stru       *pst_mac_h2d_usr_cap;

    pst_mac_h2d_usr_cap = (mac_h2d_usr_cap_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_h2d_usr_cap->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_cap_syn::pst_mac_user null.user idx [%d]}", pst_mac_h2d_usr_cap->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    dmac_11w_update_users_status((dmac_vap_stru *)pst_mac_vap, pst_mac_user, pst_mac_h2d_usr_cap->st_user_cap_info.bit_pmf_active);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    oal_memcopy(&pst_mac_user->st_cap_info, &pst_mac_h2d_usr_cap->st_user_cap_info, OAL_SIZEOF(mac_h2d_usr_cap_stru));
#endif /* (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) */
    return OAL_SUCC;
}



OAL_STATIC oal_uint32  dmac_config_user_rate_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_usr_rate_info_stru        *pst_usr_info;
    dmac_user_stru                    *pst_dmac_user;

    if (OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_user_rate_info_syn::the input is null pointer.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_usr_info = (mac_h2d_usr_rate_info_stru *)puc_param;


    /* ��ȡDMACģ���û��ṹ�� */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_usr_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_rate_info_syn::pst_dmac_user null.user idx [%d]}", pst_usr_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_protocol_mode(&(pst_dmac_user->st_user_base_info), pst_usr_info->en_protocol_mode);

    /* ͬ��legacy���ʼ���Ϣ */
    mac_user_set_avail_op_rates(&pst_dmac_user->st_user_base_info, pst_usr_info->uc_avail_rs_nrates, pst_usr_info->auc_avail_rs_rates);

    /* ͬ��ht���ʼ���Ϣ */
    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &pst_usr_info->st_ht_hdl);

    /* ͬ��vht���ʼ���Ϣ */
    mac_user_set_vht_hdl(&pst_dmac_user->st_user_base_info, &pst_usr_info->st_vht_hdl);

    /* ��Ϣͬ���������� */
    if (pst_dmac_user->st_user_base_info.st_vht_hdl.bit_vht_txop_ps)
    {
        pst_mac_vap->st_cap_flag.bit_txop_ps = OAL_TRUE;
    }
#endif
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_sta_usr_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_h2d_usr_info_stru   *pst_usr_info;
    mac_user_stru           *pst_mac_user;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_ht_hdl_stru     st_ht_hdl;
#endif
    pst_usr_info = (mac_h2d_usr_info_stru *)puc_param;

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_usr_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_sta_usr_info_syn::pst_mac_user null.user idx [%d]}", pst_usr_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ����mac��ַ������ʱmac����� */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        oal_set_mac_addr(pst_mac_user->auc_user_mac_addr, pst_mac_vap->auc_bssid);
    }

    /* ͬ��USR���� */
    mac_user_set_bandwidth_cap(pst_mac_user, pst_usr_info->en_bandwidth_cap);
    mac_user_set_bandwidth_info(pst_mac_user, pst_usr_info->en_avail_bandwidth, pst_usr_info->en_cur_bandwidth);

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);
    st_ht_hdl.uc_max_rx_ampdu_factor    = pst_usr_info->uc_arg1;
    st_ht_hdl.uc_min_mpdu_start_spacing = pst_usr_info->uc_arg2;
    mac_user_set_ht_hdl(pst_mac_user, &st_ht_hdl);
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_sta_usr_info_syn::user idx:%d,en_avail_bandwidth:%d,en_cur_bandwidth:%d}",
                        pst_usr_info->us_user_idx,
                        pst_mac_user->en_avail_bandwidth,
                        pst_mac_user->en_cur_bandwidth);

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    /* ͬ��user pmf������ */
    dmac_11w_update_users_status((dmac_vap_stru *)pst_mac_vap, pst_mac_user, pst_usr_info->en_user_pmf);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    /* ͬ��Э��ģʽ */
    mac_user_set_avail_protocol_mode(pst_mac_user, pst_usr_info->en_avail_protocol_mode);
    mac_user_set_cur_protocol_mode(pst_mac_user, pst_usr_info->en_avail_protocol_mode);
    mac_user_set_protocol_mode(pst_mac_user, pst_usr_info->en_protocol_mode);
    mac_user_set_asoc_state(pst_mac_user, pst_usr_info->en_user_asoc_state);

    /* ��ʼ��slottime */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        dmac_user_init_slottime(pst_mac_vap, pst_mac_user);
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_config_btcoex_assoc_state_syn(pst_mac_vap, pst_mac_user);
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

    /* �����㷨�ı����֪ͨ�� */
    dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_vap_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_vap_info_stru   *pst_vap_info;

    pst_vap_info = (mac_h2d_vap_info_stru *)puc_param;

    /* ͬ��vap��Ϣ */
    pst_mac_vap->us_sta_aid = pst_vap_info->us_sta_aid;
    mac_vap_set_uapsd_cap(pst_mac_vap, pst_vap_info->uc_uapsd_cap);
#endif
    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
OAL_STATIC oal_void  dmac_config_get_tx_rate_info(hal_tx_txop_alg_stru     *pst_tx_alg,
                                                        mac_data_rate_stru       *pst_mac_rates_11g,
                                                        oal_rate_info_stru       *pst_rate_info)
{
    oal_uint32                          ul_loop = 0;
    oal_uint8                           uc_tx_dscr_protocol_type = 0;
    wlan_legacy_rate_value_enum_uint8   en_legacy_rate = 0;

    /* ��ʼ������ */
    OAL_MEMZERO(pst_rate_info, OAL_SIZEOF(oal_rate_info_stru));

    /* ��ȡ��protocol typeȡֵ��ΧΪ0-3,����0Ϊ11b type, 1Ϊlegacy OFDM type��2ΪHT type��3ΪVHT type */
    uc_tx_dscr_protocol_type = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    switch(uc_tx_dscr_protocol_type)
    {
        /* 11b or legacy OFDM type */
        case 0:
        case 1:
            en_legacy_rate = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;

            for (ul_loop = 0; ul_loop < MAC_DATARATES_PHY_80211G_NUM; ul_loop++)
            {
                if (en_legacy_rate == pst_mac_rates_11g[ul_loop].uc_phy_rate)
                {
                    pst_rate_info->legacy = pst_mac_rates_11g[ul_loop].uc_mbps;
                    break;
                }
            }

            /* δ���ҵ���Ӧ��legacy���ʣ�������������ô��� */
            if (ul_loop >= MAC_DATARATES_PHY_80211G_NUM)
            {
                OAM_ERROR_LOG2(0, OAM_SF_ANY,
                               "{dmac_config_get_tx_rate_info::protocol_type[%d], legacy_rate[%d] is invalid, may be software config error.}",
                               uc_tx_dscr_protocol_type, en_legacy_rate);
            }
            break;

        /* HT type */
        case 2:
            pst_rate_info->flags |= RATE_INFO_FLAGS_MCS;
            pst_rate_info->mcs = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs;
            if (pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable)
            {
                pst_rate_info->flags |= RATE_INFO_FLAGS_SHORT_GI;
            }
            break;

        /* VHT type */
        case 3:
            pst_rate_info->flags |= RATE_INFO_FLAGS_VHT_MCS;
            pst_rate_info->mcs = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs;
            if (pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable)
            {
                pst_rate_info->flags |= RATE_INFO_FLAGS_SHORT_GI;
            }

            /* ����nss mode */
            pst_rate_info->nss = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode + 1;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_RSSI,
                           "{dmac_config_get_tx_rate_info:: protocol type[%d] invalid, software config error.}",
                           uc_tx_dscr_protocol_type);
            break;
    }

    /* �����ŵ���ȣ��ö�Ӧ�ı��λ */
    switch (pst_tx_alg->st_rate.uc_channel_bandwidth)
    {
        case WLAN_BAND_ASSEMBLE_40M:
        case WLAN_BAND_ASSEMBLE_40M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_80M:
        case WLAN_BAND_ASSEMBLE_80M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_80_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_160M:
        case WLAN_BAND_ASSEMBLE_160M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_160_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_80M_80M:
            pst_rate_info->flags |= RATE_INFO_FLAGS_80P80_MHZ_WIDTH;
            break;

        default:
            /* do nothing */
            break;
    }

    OAM_WARNING_LOG4(0, OAM_SF_ANY,
                     "{dmac_config_get_tx_rate_info::protocol_type[%d],legacy_rate[%d],short_gi[%d],bandwidth[%d].}",
                     uc_tx_dscr_protocol_type, en_legacy_rate,
                     pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable,
                     pst_tx_alg->st_rate.uc_channel_bandwidth);

    OAM_WARNING_LOG4(0, OAM_SF_ANY,
                     "{dmac_config_get_tx_rate_info::legacy[%d]:mcs[%d]:flags[%d]:nss[%d].}",
                     pst_rate_info->legacy, pst_rate_info->mcs, pst_rate_info->flags, pst_rate_info->nss);

    return;
}
OAL_STATIC oal_uint32  dmac_config_proc_query_sta_info_event(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                         *pst_mac_device;
    dmac_vap_stru                           *pst_dmac_vap;
    dmac_user_stru                          *pst_dmac_user;
    dmac_query_request_event                *pst_query_requset_event;
    dmac_query_station_info_response_event   st_query_station_info;
    oal_uint16                               us_user_idx;
    oal_uint32                               ul_ret;

    pst_query_requset_event     = (dmac_query_request_event *)puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                         "{dmac_config_proc_query_sta_info_event::pst_mac_device is null, device_id[%d].}",
                         pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    if (OAL_QUERY_STATION_INFO_EVENT == pst_query_requset_event->query_event)
    {
        pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_proc_query_sta_info_event::pst_dmac_vap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            /* sta��ѯ��Ϣ��ֵ */
            st_query_station_info.query_event        = pst_query_requset_event->query_event;
            /*���㷨����ȡRSSI*/
            st_query_station_info.ul_signal          = pst_dmac_vap->st_query_stats.ul_signal;
            /*���ݰ�ͳ�ƣ���ά�ⲻ�ܷ���ͬһ��Ԥ���������*/
            st_query_station_info.ul_rx_packets      = pst_dmac_vap->st_query_stats.ul_drv_rx_pkts;
            st_query_station_info.ul_tx_packets      = pst_dmac_vap->st_query_stats.ul_hw_tx_pkts;
            st_query_station_info.ul_rx_bytes        = pst_dmac_vap->st_query_stats.ul_drv_rx_bytes;
            st_query_station_info.ul_tx_bytes        = pst_dmac_vap->st_query_stats.ul_hw_tx_bytes;
            st_query_station_info.ul_tx_failed       = pst_dmac_vap->st_query_stats.ul_tx_failed;
            st_query_station_info.ul_tx_retries      = pst_dmac_vap->st_query_stats.ul_tx_retries;
            st_query_station_info.ul_rx_dropped_misc = pst_dmac_vap->st_query_stats.ul_rx_dropped_misc;
        }
        else if(WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_query_requset_event->auc_query_sta_addr, &us_user_idx);

            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_proc_query_sta_info_event::no user.}");
                return ul_ret;
            }

            /* ��ȡDMACģ���û��ṹ�� */
            pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
            if (OAL_PTR_NULL == pst_dmac_user)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_proc_query_sta_info_event::pst_dmac_user null.}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            /* sta��ѯ��Ϣ��ֵ */
            st_query_station_info.query_event        = pst_query_requset_event->query_event;
            /*���㷨����ȡRSSI*/
            st_query_station_info.ul_signal          = pst_dmac_user->st_query_stats.ul_signal;
            /*���ݰ�ͳ�ƣ���ά�ⲻ�ܷ���ͬһ��Ԥ���������*/
            st_query_station_info.ul_rx_packets      = pst_dmac_user->st_query_stats.ul_drv_rx_pkts;
            st_query_station_info.ul_tx_packets      = pst_dmac_user->st_query_stats.ul_hw_tx_pkts;
            st_query_station_info.ul_rx_bytes        = pst_dmac_user->st_query_stats.ul_drv_rx_bytes;
            st_query_station_info.ul_tx_bytes        = pst_dmac_user->st_query_stats.ul_hw_tx_bytes;
            st_query_station_info.ul_tx_failed       = pst_dmac_user->st_query_stats.ul_tx_failed;
            st_query_station_info.ul_tx_retries      = pst_dmac_user->st_query_stats.ul_tx_retries;
            st_query_station_info.ul_rx_dropped_misc = pst_dmac_user->st_query_stats.ul_rx_dropped_misc;
        }
        else
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RSSI,
                             "{dmac_config_proc_query_sta_info_event::vap_mode[%d] don't support query statistics info.}",
                             pst_mac_vap->en_vap_mode);
            return OAL_FAIL;
        }

        /* ��ȡ�������� */
        dmac_config_get_tx_rate_info(&(pst_dmac_vap->st_tx_alg), &(pst_mac_device->st_mac_rates_11g[0]), &(st_query_station_info.st_txrate));

        dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_QUERY_STATION_STATS, OAL_SIZEOF(dmac_query_station_info_response_event), (oal_uint8 *)&st_query_station_info);

    }

    return OAL_SUCC;
}
#endif   /* end of (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV) */
#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 �� �� ��  : dmac_config_dfs_radartool
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��16��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dfs_radartool(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS
    mac_device_stru       *pst_mac_device;
    oal_int8              *pc_token;
    oal_int8              *pc_end;
    oal_int8              *pc_ctx;
    oal_int8              *pc_sep = " ";
    oal_bool_enum_uint8    en_val;
    oal_uint32             ul_val;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�������� */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == oal_strcmp(pc_token, "dfsenable"))
    {
        /* ��ȡDFSʹ�ܿ���*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_dfs_enable(pst_mac_device, en_val);
    }
    else if (0 == oal_strcmp(pc_token, "cacenable"))
    {
        /* ��ȡCAC���ʹ�ܿ���*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_cac_enable(pst_mac_device, en_val);
    }
    else if (0 == oal_strcmp(pc_token, "dfsdebug"))
    {
        /* ��ȡdebug level */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

        mac_dfs_set_debug_level(pst_mac_device, (oal_uint8)ul_val);
    }
    else if(0 == oal_strcmp(pc_token, "offchannum"))
    {
        /* ��ȡOFF-CHAN CAC����ŵ�*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_offchan_number(pst_mac_device, ul_val);
    }
    else if(0 == oal_strcmp(pc_token, "ctsdura"))
    {
        /* ��ȡcts duration */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->st_dfs.st_dfs_info.uc_cts_duration = (oal_uint8)ul_val;
    }
    else if(0 == oal_strcmp(pc_token, "radarfilter"))
    {
        /* ��ȡ�״���� chirp_enable */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.en_chirp_enable = (oal_bool_enum_uint8)ul_val;

        /* ��ȡ�״���� chirp_cnt */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_chirp_cnt_threshold = ul_val;

        /* ��ȡ�״���� chirp threshold */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_chirp_time_threshold = ul_val;

        /* ��ȡ�״���� threshold */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_time_threshold = ul_val;

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_last_burst_timestamp = 0;
        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_last_burst_timestamp_for_chirp = 0;
    }
    else if(0 == oal_strcmp(pc_token, "enabletimer"))
    {
        /* ��ȡ�����󱨶�ʱ��ʱ�� */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);
        pst_mac_device->us_dfs_timeout = (oal_uint16)ul_val;
        //OAM_INFO_LOG1(0, OAM_SF_DFS, "[DFS]enable timer: %d. ", pst_mac_device->us_dfs_timeout);
    }
    else if(0 == oal_strcmp(pc_token, "offchanenable"))
    {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        /* 1102 DBAC todo Ĭ�Ͽ���DBACʱ����GO������beacon֡*/
        hal_vap_start_tsf(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, OAL_FALSE);
#endif
    }
    else
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }
#endif
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_config_set_shpreamble
 ��������  : ����dmac AMPDU����λ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* ����mibֵ */
    mac_mib_set_shpreamble(pst_mac_vap, uc_len, puc_param);
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_MONITOR
/*****************************************************************************
 �� �� ��  : dmac_config_set_addr_filter
 ��������  : ����dmac ��ַ��������λ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8        uc_value;
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_get_cmd_one_arg::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_value = (*((oal_int32 *)puc_param) == 0) ? 0 : 1;

    if (0 != uc_value)
    {
        /* ����monitorģʽ��������֡���͹��� */
        hal_enable_monitor_mode(pst_mac_device->pst_device_stru);
    }
    else
    {
        /* �ر�monitorģʽ������֡���͹��� */
        hal_disable_monitor_mode(pst_mac_device->pst_device_stru);
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_config_set_prot_mode
 ��������  : ����dmac ����ģʽ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32 l_value;

    l_value = *((oal_int32 *)puc_param);

    pst_mac_vap->st_protection.en_protection_mode = (oal_uint8)l_value;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_pause_tid
 ��������  : ��������ȥ����1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pause_tid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    oal_uint16                      us_user_idx;
    oal_uint32                      ul_ret;
    dmac_user_stru                 *pst_dmac_user;
    oal_uint8                       uc_tid;
    mac_device_stru                *pst_mac_device;

    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)puc_param;
    uc_tid = pst_pause_tid_param->uc_tid;

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_pause_tid_param->auc_mac_addr, &us_user_idx);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pause_tid::no user.}");
        return ul_ret;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pause_tid::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pause_tid::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if  (OAL_TRUE == pst_pause_tid_param->uc_is_paused)
    {
        dmac_tid_pause(&(pst_dmac_user->ast_tx_tid_queue[uc_tid]), DMAC_TID_PAUSE_RESUME_TYPE_BA);
    }
    else
    {
        dmac_tid_resume(pst_mac_device->pst_device_stru, &(pst_dmac_user->ast_tx_tid_queue[uc_tid]), DMAC_TID_PAUSE_RESUME_TYPE_BA);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_config_dump_timer
 ��������  : �������timer��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_timer(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    frw_timer_dump_timer(pst_mac_vap->ul_core_id);
#if 0
    oal_dlist_head_stru *pst_entry;
    oal_dlist_head_stru *pst_user_list_head;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;

    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

    /* ����VAP������û���dump�û�last active timestamp  */
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

        /* ָ��˫��������һ���ڵ� */
        pst_entry = pst_entry->pst_next;

        if (OAL_PTR_NULL == pst_dmac_user_tmp)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "dmac_config_dump_timer::user is null. us_assoc_id is %d", pst_user_tmp->us_assoc_id);
            continue;
        }

        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "dmac_config_dump_timer::us_assoc_id is %d, last_active_timestamp[%u]",
                         pst_user_tmp->us_assoc_id, pst_dmac_user_tmp->ul_last_active_timestamp);

    }
#endif
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_config_set_user_vip
 ��������  : �����û���vip flag
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��22��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_user_vip(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_user_vip_param_stru    *pst_user_vip_param;
    oal_uint16                      us_user_idx;
    oal_uint32                      ul_ret;
    dmac_user_stru                 *pst_dmac_user;

    pst_user_vip_param = (mac_cfg_user_vip_param_stru *)puc_param;

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_user_vip_param->auc_mac_addr, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_user_vip::no user.}");
        return ul_ret;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_user_vip::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_vip_flag = pst_user_vip_param->uc_vip_flag;

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_user_vip, vip_flag = %d}", pst_dmac_user->en_vip_flag);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_vap_host
 ��������  : ����vapΪhost vap;
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��22��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_vap_host(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_vap_host::param null.}");
         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->en_is_host_vap = *puc_param;

    OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_vap_host, host_flag = %d}", pst_dmac_vap->en_is_host_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_send_bar
 ��������  : ��������ȥ����1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_send_bar(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    oal_uint16                      us_user_idx;
    oal_uint32                      ul_ret;
    dmac_user_stru                 *pst_dmac_user;
    oal_uint8                       uc_tid;
    dmac_tid_stru                  *pst_tid;

    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)puc_param;
    uc_tid = pst_pause_tid_param->uc_tid;

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_pause_tid_param->auc_mac_addr, &us_user_idx);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_bar::no user.}");
        return ul_ret;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_bar::pst_dmac_user null, user idx[%d]}", us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid];

    if (OAL_PTR_NULL == pst_tid->pst_ba_tx_hdl || DMAC_BA_COMPLETE != pst_tid->pst_ba_tx_hdl->en_ba_conn_status)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_bar::ba not established.}");
        return OAL_FAIL;
    }

    return dmac_ba_send_bar(pst_tid->pst_ba_tx_hdl, pst_dmac_user, pst_tid);
}



/*****************************************************************************
 �� �� ��  : dmac_config_set_bintval
 ��������  : ����beacon interval
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_bintval(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru  *pst_dmac_vap;
    oal_int32       l_value;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_mac_device;
    oal_uint8                    uc_vap_idx;
    mac_vap_stru*               pst_vap;
#endif

    l_value = *((oal_int32 *)puc_param);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_device              = mac_res_get_dev(pst_mac_vap->uc_device_id);

    mac_device_set_beacon_interval(pst_mac_device, *((oal_uint32 *)puc_param));

    /* ����device������vap */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_config_set_bintval::pst_mac_vap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* ֻ��AP VAP��Ҫbeacon interval */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
             /* ����mibֵ */
            mac_mib_set_beacon_period(pst_vap, (oal_uint8)uc_len, puc_param);
        }
    }
#endif

    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)l_value);
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_config_alg
 ��������  : �㷨��������
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_alg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32        ul_ret = OAL_FAIL;
    oal_uint8         uc_idx;
    p_alg_config_func p_func;

    oal_int8         *pac_argv[DMAC_ALG_CONFIG_MAX_ARG + 1];

    mac_ioctl_alg_config_stru *pst_alg_config = (mac_ioctl_alg_config_stru *)puc_param;

    for (uc_idx = OAL_SIZEOF(mac_ioctl_alg_config_stru); uc_idx < uc_len; uc_idx++)
    {
        if(puc_param[uc_idx] == ' ')
        {
            puc_param[uc_idx] = 0;
        }
    }

    for(uc_idx = 0; uc_idx < pst_alg_config->uc_argc; uc_idx++)
    {
        pac_argv[uc_idx] = (oal_int8 *)puc_param + OAL_SIZEOF(mac_ioctl_alg_config_stru) + pst_alg_config->auc_argv_offset[uc_idx];
    }

    pac_argv[uc_idx] = NULL;

    for(uc_idx = 0; uc_idx < DMAC_ALG_CONFIG_ID_BUTT; uc_idx++)
    {
        if(0 == oal_strcmp(pac_argv[0], g_ast_dmac_alg_config_table[uc_idx].puc_alg_name))
        {
            break;
        }
    }

    if (uc_idx == DMAC_ALG_CONFIG_ID_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_alg: uc_idx error: %d}", uc_idx);

        return OAL_FAIL;
    }

    p_func = gst_alg_main.pa_alg_config_notify_func[uc_idx];

    if(p_func)
    {
        ul_ret = p_func(pst_mac_vap, pst_alg_config->uc_argc - 1, pac_argv + 1);
    }
    else
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_alg::p_func null.}");
    }

    return ul_ret;
}

oal_uint32  dmac_config_set_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ����mibֵ */
    mac_mib_set_dtim_period(pst_mac_vap, uc_len, puc_param);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_nobeacon
 ��������  : ����dmac no beacon����λ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8            uc_value;
    dmac_vap_stru       *pst_dmac_vap;

    uc_value      = (*((oal_int32 *)puc_param) == 0) ? 0 : 1;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_nobeacon::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 != uc_value)
    {
        hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);
    }
    else
    {
        hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);
    }

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_nobeacon succ!");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_txchain
 ��������  : ����dmac ����ͨ��
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txchain(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32           l_value;
    mac_device_stru    *pst_mac_device;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_txchain::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);

#if 0
    pst_mac_device->uc_tx_chain = (oal_uint8)l_value;
#else
    mac_device_set_txchain(pst_mac_device, (oal_uint8)l_value);
#endif

    /* ����ͨ��û�мĴ����������������� */
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_rxchain
 ��������  : ����dmac ����ͨ��
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_rxchain(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32           l_value;
    mac_device_stru    *pst_mac_device;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rxchain::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);

#if 0
    pst_mac_device->uc_rx_chain = (oal_uint8)l_value;
#else
    mac_device_set_rxchain(pst_mac_device, (oal_uint8)l_value);
#endif
    /* ����HAL�ӿ� */
    hal_set_rx_multi_ant(pst_mac_device->pst_device_stru, pst_mac_device->uc_rx_chain);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_txpower
 ��������  : ����dmac ���͹���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txpower(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32 l_value;

    l_value = *((oal_int32 *)puc_param);

    mac_vap_set_tx_power(pst_mac_vap, (oal_uint8)l_value);

    /* �������������й����ֶ� */
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_cwmin
 ��������  : ����cwmin����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmin;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmin  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_cwmin::invalid param, ul_ac=%d uc_cwmin=%d.", ul_ac, uc_cwmin);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableCWmin = uc_cwmin;
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_cwmax
 ��������  : ����cwmax����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_cwmax(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmax  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_cwmax::invalid param, ul_ac=%d uc_cwmax=%d.", ul_ac, uc_cwmax);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableCWmax = (oal_uint32)uc_cwmax;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_aifsn
 ��������  : ����aifsn����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_aifsn::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableAIFSN = ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_aifsn
 ��������  : ����txop_limit����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txop_limit(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_txop_limit::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableTXOPLimit = ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_msdu_lifetime
 ��������  : ����msdu_lifetime����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_msdu_lifetime(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_msdu_lifetime::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableMSDULifetime = ul_value;

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : dmac_config_set_edca_mandatory
 ��������  : ����edca_mandatory����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_edca_mandatory(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_edca_mandatory::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].en_dot11EDCATableMandatory = (oal_uint8)ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_cwmin
 ��������  : ����AP��cwmin��������Ҫ�����Ĵ���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_qap_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax = 0;
    oal_uint8   uc_cwmin = 0;
    oal_uint8   uc_cwmin_pre = 0;

    hal_to_dmac_vap_stru        *pst_hal_vap;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmin  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmin::invalid param, ul_ac=%d uc_cwmin=%d.", ul_ac, uc_cwmin);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableCWmin = uc_cwmin;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;

    hal_vap_get_edca_machw_cw(pst_hal_vap, &uc_cwmax, &uc_cwmin_pre, (oal_uint8)ul_ac);
    hal_vap_set_edca_machw_cw(pst_hal_vap, uc_cwmax, uc_cwmin, (oal_uint8)ul_ac);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_cwmax
 ��������  : ����AP��cwmax��������Ҫ�����Ĵ���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_qap_cwmax(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax = 0;
    oal_uint8   uc_cwmin = 0;
    oal_uint8   uc_cwmax_pre = 0;

    hal_to_dmac_vap_stru        *pst_hal_vap;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmax  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmax::invalid param, ul_ac=%d uc_cwmax=%d.", ul_ac, uc_cwmax);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableCWmax = uc_cwmax;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;

    hal_vap_get_edca_machw_cw(pst_hal_vap, &uc_cwmax_pre, &uc_cwmin, (oal_uint8)ul_ac);
    hal_vap_set_edca_machw_cw(pst_hal_vap, uc_cwmax, uc_cwmin, (oal_uint8)ul_ac);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_aifsn
 ��������  : ����AP��aifsn��������Ҫ�����Ĵ���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_qap_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_aifsn::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableAIFSN = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;

    hal_vap_set_machw_aifsn_ac(pst_hal_vap, (wlan_wme_ac_type_enum_uint8)ul_ac, (oal_uint8)ul_value);

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_aifsn
 ��������  : ����AP��txop_limit��������Ҫ�����Ĵ���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_qap_txop_limit(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;
    oal_uint16  us_txop_bk = 0;
    oal_uint16  us_txop_be = 0;
    oal_uint16  us_txop_vi = 0;
    oal_uint16  us_txop_vo = 0;
    oal_uint16  us_pre_value = 0;

    hal_to_dmac_vap_stru        *pst_hal_vap;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_txop_limit::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableTXOPLimit = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;

    switch (ul_ac)
    {
        case WLAN_WME_AC_BK:
            hal_vap_get_machw_txop_limit_bkbe(pst_hal_vap, &us_txop_be, &us_pre_value);
            hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap, us_txop_be, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_BE:
            hal_vap_get_machw_txop_limit_bkbe(pst_hal_vap, &us_pre_value, &us_txop_bk);
            hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap, (oal_uint16)ul_value, us_txop_bk);
            break;

        case WLAN_WME_AC_VI:
            hal_vap_get_machw_txop_limit_vivo(pst_hal_vap, &us_txop_vo, &us_pre_value);
            hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, us_txop_vo, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_VO:
            hal_vap_get_machw_txop_limit_vivo(pst_hal_vap, &us_pre_value, &us_txop_vi);
            hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, (oal_uint16)ul_value, us_txop_vi);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_msdu_lifetime
 ��������  : ����AP��msdu_lifetime��������Ҫ�����Ĵ���
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_set_qap_msdu_lifetime(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    oal_uint16  us_lifetime_bk = 0;
    oal_uint16  us_lifetime_be = 0;
    oal_uint16  us_lifetime_vi = 0;
    oal_uint16  us_lifetime_vo = 0;
    oal_uint16  us_pre_value = 0;

    hal_to_dmac_vap_stru        *pst_hal_vap;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_msdu_lifetime::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableMSDULifetime = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;

    switch (ul_ac)
    {
        case WLAN_WME_AC_BK:
            hal_vap_get_machw_edca_bkbe_lifetime(pst_hal_vap, &us_lifetime_be, &us_pre_value);
            hal_vap_set_machw_edca_bkbe_lifetime(pst_hal_vap, us_lifetime_be, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_BE:
            hal_vap_get_machw_edca_bkbe_lifetime(pst_hal_vap, &us_pre_value, &us_lifetime_bk);
            hal_vap_set_machw_edca_bkbe_lifetime(pst_hal_vap, (oal_uint16)ul_value, us_lifetime_bk);
            break;

        case WLAN_WME_AC_VI:
            hal_vap_get_machw_edca_vivo_lifetime(pst_hal_vap, &us_lifetime_vo, &us_pre_value);
            hal_vap_set_machw_edca_vivo_lifetime(pst_hal_vap, us_lifetime_vo, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_VO:
            hal_vap_get_machw_edca_vivo_lifetime(pst_hal_vap, &us_pre_value, &us_lifetime_vi);
            hal_vap_set_machw_edca_vivo_lifetime(pst_hal_vap, (oal_uint16)ul_value, us_lifetime_vi);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : dmac_config_set_qap_edca_mandatory
 ��������  : ����AP��edca_mandatory����
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_qap_edca_mandatory(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_edca_mandatory::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].en_dot11QAPEDCATableMandatory = (oal_uint8)ul_value;

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_channel_param_stru      *pst_channel_param;
    mac_device_stru                 *pst_mac_device;
    oal_uint8                        uc_channel_idx = 0;
    oal_uint32                       ul_beacon_rate;
    mac_vap_stru                    *pst_vap_up;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_channel::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_channel_param = (mac_cfg_channel_param_stru *)puc_param;

    mac_get_channel_idx_from_num(pst_channel_param->en_band, pst_channel_param->uc_channel, &uc_channel_idx);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_vap->st_channel.uc_chan_number  = pst_channel_param->uc_channel;
    pst_mac_vap->st_channel.en_band         = pst_channel_param->en_band;
    pst_mac_vap->st_channel.en_bandwidth    = pst_channel_param->en_bandwidth;

    pst_mac_vap->st_channel.uc_idx = uc_channel_idx;

    if(MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    {
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_AP_WAIT_START;
    }

    //OAM_INFO_LOG3(0, OAM_SF_2040, "dmac_config_set_channel::chan=%d band=%d bandwidth=%d\r\n", pst_channel_param->uc_channel, pst_channel_param->en_band,
      //                                            pst_channel_param->en_bandwidth);
    /* ���ݴ�����Ϣ����Mib */
    mac_vap_change_mib_by_bandwidth(pst_mac_vap, pst_channel_param->en_bandwidth);

    mac_device_set_channel(pst_mac_device, pst_channel_param);
#endif

    /* ����beacon�ķ��Ͳ��� */
    if ((WLAN_BAND_2G == pst_channel_param->en_band) || (WLAN_BAND_5G == pst_channel_param->en_band))
    {
        ul_beacon_rate = ((dmac_vap_stru *)pst_mac_vap)->ast_tx_mgmt_ucast[pst_channel_param->en_band].ast_per_rate[0].ul_value;
        hal_vap_set_beacon_rate(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, ul_beacon_rate);
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_set_channel::en_band=%d", pst_channel_param->en_band);
    }

    /* disable TSF */
    hal_vap_set_machw_tsf_disable(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap);

#ifdef _PRE_WLAN_FEATURE_DFS
    /* ʹ��ȥʹ���״��� */
    if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)&&(OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device)))
    {
        oal_bool_enum_uint8      en_enable_dfs;

        en_enable_dfs = mac_is_ch_in_radar_band(pst_mac_device->en_max_band, pst_mac_vap->st_channel.uc_idx);
        hal_enable_radar_det(pst_mac_device->pst_device_stru, en_enable_dfs);
    }
#endif

    /* ��hal�ӿ����ô��� */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /*dummy*/
#else
    if (pst_channel_param->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_channel:: fpga is not support 80M.}\r\n");
        pst_channel_param->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif

    /* ֪ͨ�㷨 */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    mac_device_find_up_sta(pst_mac_device, &pst_vap_up);

    dmac_mgmt_connect_set_channel(pst_mac_device, pst_vap_up, &(pst_mac_vap->st_channel));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_WLAN_FEATURE_DBAC
    if(mac_is_dbac_enabled(pst_mac_device))
    {

    }
    else
#endif
    {
        hal_vap_start_tsf(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, OAL_FALSE);
    }
#endif

    return OAL_SUCC;
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : dmac_config_set_beacon_debug
 ��������  : DMAC add beacon ��Ϣ�������
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : zwx287476
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_config_set_beacon_debug(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_beacon_param_stru           *pst_beacon_param;
    oal_uint32                       ul_loop;
    oal_uint8                        uc_vap_id;

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    uc_vap_id = pst_mac_vap->uc_vap_id;

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug::crypto_mode=%d.}", pst_beacon_param->uc_crypto_mode);
    OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:gourp %d, group_size %d, auth %d.} bit_wpa %d, bit_wpa2 %d \r\n",
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected);

    OAM_INFO_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:bit_wpa %d, bit_wpa2 %d.}",
        pst_mac_vap->st_cap_flag.bit_wpa,
        pst_mac_vap->st_cap_flag.bit_wpa2);

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:[%d] %d, %d}",
            (ul_loop + 1),
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:[%d] %d, %d}",
            ul_loop + 1,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:rsn_capability %02x}", pst_beacon_param->us_rsn_capability);
}


OAL_STATIC oal_void dmac_config_add_beacon_debug(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_beacon_param_stru           *pst_beacon_param;
    oal_uint32                       ul_loop;
    oal_uint8                        uc_vap_id;

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    uc_vap_id = pst_mac_vap->uc_vap_id;

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug::crypto_mode=%d.}", pst_beacon_param->uc_crypto_mode);
    OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:gourp %d, group_size %d, auth %d.} bit_wpa %d, bit_wpa2 %d \r\n",
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected);

    OAM_INFO_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:bit_wpa %d, bit_wpa2 %d.}",
        pst_mac_vap->st_cap_flag.bit_wpa,
        pst_mac_vap->st_cap_flag.bit_wpa2);

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:[%d] %d, %d}",
            (ul_loop + 1),
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:[%d] %d, %d}",
            ul_loop + 1,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:rsn_capability %02x}", pst_beacon_param->us_rsn_capability);
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_config_set_beacon
 ��������  : HOSTAPD ����AP ����������beacon interval��dtim_period, WPA/WPA2
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : zwx287476
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_beacon(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    mac_beacon_param_stru           *pst_beacon_param;
    dmac_vap_stru                   *pst_dmac_vap;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    pst_beacon_param = pst_beacon_param;/* ���pclint�澯��pst_beacon_paramδ���� */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 1102�������ں�start ap��change beacon�ӿڸ��ô˽ӿڣ���ͬ����change beaconʱ����������beacon����
       ��dtim���ڣ���ˣ�change beaconʱ��interval��dtim period����Ϊȫ�㣬��ʱ��Ӧ�ñ����õ�mib�� */
    if ((0 != pst_beacon_param->l_dtim_period) || (0 != pst_beacon_param->l_interval))
    {
        /* ����mib */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod   = (oal_uint32)pst_beacon_param->l_dtim_period;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)pst_beacon_param->l_interval;
    }

    /* �����·��Ĳ���������vap����ssid������λ��Ϣ */
    mac_vap_set_hide_ssid(pst_mac_vap, pst_beacon_param->uc_hidden_ssid);

    if (MAC_ADD_BEACON == pst_beacon_param->en_operation_type)
    {
        mac_vap_add_beacon(pst_mac_vap, pst_beacon_param);
    }
    else
	{
        mac_vap_set_beacon(pst_mac_vap, pst_beacon_param);
	}

    /* ����short gi */
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = pst_beacon_param->en_shortgi_20;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented  = pst_beacon_param->en_shortgi_40;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = pst_beacon_param->en_shortgi_80;

    mac_vap_init_by_protocol(pst_mac_vap, pst_beacon_param->en_protocol);
    mac_vap_init_rates(pst_mac_vap);
#endif

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_DEBUG_MODE
    if (MAC_ADD_BEACON == pst_beacon_param->en_operation_type)
    {
        dmac_config_add_beacon_debug(pst_mac_vap, puc_param);
    }
    else
	{
        dmac_config_set_beacon_debug(pst_mac_vap, puc_param);
	}
#endif
    dmac_vap_init_tx_frame_params(pst_dmac_vap, OAL_TRUE);
    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_add_user
 ��������  : DMAC�û�����û�ͬ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint16                      us_user_idx;
    mac_cfg_add_user_param_stru    *pst_add_user;
    dmac_user_stru                 *pst_dmac_user;
    mac_device_stru                *pst_device;
    oal_uint32                      ul_tid_idx;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_ht_hdl_stru            st_ht_hdl;
#endif
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_user::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_add_user = (mac_cfg_add_user_param_stru *)puc_param;

    us_user_idx = pst_add_user->us_user_idx;

    /* ��ȡdmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* TBD hmac_config_add_user�˽ӿ�ɾ������Ӧ������Ҫ���ģ�duankaiyong&guyanjie */

    /* ����qos�򣬺���������Ҫ����ͨ����������������� */
    mac_user_set_qos(&pst_dmac_user->st_user_base_info, OAL_TRUE);

    /* ����HT�� */
    mac_user_get_ht_hdl(&pst_dmac_user->st_user_base_info, &st_ht_hdl);
    st_ht_hdl.en_ht_capable = pst_add_user->en_ht_cap;

    if (OAL_TRUE == pst_add_user->en_ht_cap)
    {
        pst_dmac_user->st_user_base_info.en_cur_protocol_mode                = WLAN_HT_MODE;
        pst_dmac_user->st_user_base_info.en_avail_protocol_mode              = WLAN_HT_MODE;
    }

    /* ����HT��ص���Ϣ:Ӧ���ڹ�����ʱ��ֵ ���ֵ���õĺ������д����� 2012->page:786 */
    st_ht_hdl.uc_min_mpdu_start_spacing = 6;
    st_ht_hdl.uc_max_rx_ampdu_factor    = 3;
    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &st_ht_hdl);

    mac_user_set_asoc_state(&pst_dmac_user->st_user_base_info, MAC_USER_STATE_ASSOC);
#endif

    pst_dmac_user->ul_probe_req_ts    = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��ʼ��dmac_ht_handle_stru�ṹ���е�uc_ampdu_max_sizeֵ */
    for (ul_tid_idx = 0; ul_tid_idx < WLAN_TID_MAX_NUM; ul_tid_idx++)
    {
        pst_dmac_user->ast_tx_tid_queue[ul_tid_idx].st_ht_tx_hdl.us_ampdu_max_size = 65535;
    }

    /* lut idx���ڴ���ʱ���룬�˴�д��Ӳ����ȥ */
    hal_machw_seq_num_index_update_per_tid(pst_device->pst_device_stru,
                                           pst_dmac_user->uc_lut_index,
                                           OAL_TRUE);

    /* ��������ģ������û�����ɺ�STA VAP��ΪUP״̬ */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)&&
        (IS_LEGACY_VAP(pst_mac_vap)))
    {
        /*��vap״̬�ı���Ϣ�ϱ�*/
        mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_UP);

        pst_mac_vap->en_vap_state = MAC_VAP_STATE_UP;
#ifdef _PRE_WLAN_FEATURE_ROAM
        dmac_sta_roam_trigger_init((dmac_vap_stru *)pst_mac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_del_user
 ��������  : ɾ���û��ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint16                      us_user_idx;
    mac_cfg_del_user_param_stru    *pst_del_user;
    dmac_user_stru                 *pst_dmac_user;
    mac_device_stru                *pst_mac_device;

    pst_del_user = (mac_cfg_del_user_param_stru *)puc_param;

    us_user_idx = pst_del_user->us_user_idx;

    /* ��ȡdmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_del_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �黹RA LUT IDX */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* do nothing, ����Ҫ�Ƴ�user����ΪProxy STA��uc_lut_index��ΧΪ16~31���õ���vap�ģ�����user�� */
        }
        else
        {
            mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
        }
    }
    else
    {
        mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
    }
#else
    mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
#endif
    /* ��������ģ��ɾ���û�����ɺ�STA VAP��ΪFAKE_UP״̬ */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)&&
        (IS_LEGACY_VAP(pst_mac_vap)))

    {
        /*��vap״̬�ı���Ϣ�ϱ�*/
        mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_STA_FAKE_UP);

        pst_mac_vap->en_vap_state = MAC_VAP_STATE_STA_FAKE_UP;
    }

    dmac_alg_del_assoc_user_notify((dmac_vap_stru *)pst_mac_vap, pst_dmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_dump_ba_bitmap
 ��������  : ��ʾ�����жϸ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_ba_bitmap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_DEBUG_MODE
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
#if 0
        hal_to_dmac_device_stru          *pst_hal_device;
        dmac_vap_stru                    *pst_dmac_vap;
	 dmac_user_stru			 *pst_dmac_user;
        oal_uint16                        us_track_index;
        oal_uint16                        us_seq_index;
        oal_uint8                         uc_num = 0;
        oal_uint8                         uc_lut_idx;
        dmac_tx_ba_track_stru            *pst_tx_ba_track;
        mac_cfg_mpdu_ampdu_tx_param_stru *pst_aggr_tx_on_param;
        oal_file                         *pst_fs = OAL_PTR_NULL;
        oal_mm_segment_t                  old_fs;
        dmac_seq_track_stru               *pst_seq_track = OAL_PTR_NULL;

        pst_aggr_tx_on_param = (mac_cfg_mpdu_ampdu_tx_param_stru *)puc_param;

        pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
        pst_hal_device  = pst_dmac_vap->pst_hal_device;
        pst_dmac_user = (dmac_user_stru *)mac_vap_get_user_by_addr(pst_mac_vap, pst_aggr_tx_on_param->auc_ra_mac);

	 if (OAL_PTR_NULL == pst_dmac_user)
	 {
	     OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::dmac_user_null!\n.}");
	     return OAL_FAIL;
	 }

	 if ( (pst_aggr_tx_on_param->uc_tid >= WLAN_TIDNO_BUTT) || (pst_aggr_tx_on_param->uc_tid < WLAN_TIDNO_BEST_EFFORT) )
	 {
	     OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_config_dump_ba_bitmap::invalid input tid number[%d]\n.}", pst_aggr_tx_on_param->uc_tid);
	     return OAL_FAIL;
	 }

	 if ( OAL_PTR_NULL == (pst_dmac_user->ast_tx_tid_queue[pst_aggr_tx_on_param->uc_tid].pst_ba_tx_hdl) )
	 {
	     OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::pst_tx_ba_handle null\n.}");
	     return OAL_FAIL;
	 }

	 uc_lut_idx = pst_dmac_user->ast_tx_tid_queue[pst_aggr_tx_on_param->uc_tid].pst_ba_tx_hdl->uc_tx_ba_lut;

	 if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
	 {
	     OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::invalid uc_lut_idx[%d].}", uc_lut_idx);
	     return OAL_FAIL;
	 }

        pst_tx_ba_track = &g_ast_tx_ba_track[pst_mac_vap->uc_device_id][uc_lut_idx];
        us_track_index  = pst_tx_ba_track->us_track_head;

        pst_fs = oal_kernel_file_open(DMAC_DUMP_BA_BITMAP_PATH, OAL_O_RDWR|OAL_O_CREAT|OAL_O_APPEND);
        if(!pst_fs)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "witp_reset_dump_mac_reg,fail to open file!\n");
            return OAL_FAIL;
        }

        old_fs = oal_get_fs();
        oal_set_fs(OAL_KERNEL_DS);                  //��չ�ں˿ռ䵽�û��ռ�

        if (pst_tx_ba_track->us_track_head > OAM_SEQ_TRACK_NUM - 1 || pst_tx_ba_track->us_track_tail > OAM_SEQ_TRACK_NUM - 1)
        {
            oal_kernel_file_print(pst_fs, "head: %d  tail:%d \n", pst_tx_ba_track->us_track_head, pst_tx_ba_track->us_track_tail);
            return OAL_FAIL;
        }
        oal_kernel_file_print(pst_fs, "tid %d \n", pst_tx_ba_track->ast_seq_bitmap_log[us_track_index].uc_tid);

        while (pst_tx_ba_track->us_track_tail != us_track_index)
        {
            pst_seq_track = &(pst_tx_ba_track->ast_seq_bitmap_log[us_track_index]);
            oal_kernel_file_print(pst_fs, "********************************************************************\n");
            oal_kernel_file_print(pst_fs, "No.%d \n", uc_num);
            uc_num++;

            /*������ɣ� �ϱ�����������ӡ*/
            if (pst_seq_track->en_is_before_tx_track == OAL_FALSE)
            {
                oal_kernel_file_print(pst_fs, "ba track AFTER tx \n");
                oal_kernel_file_print(pst_fs, "tx status =  %d, report_dscr_num = %d \n", pst_seq_track->un_mix_dscr.st_report.uc_tx_status, pst_seq_track->un_mix_dscr.st_report.uc_report_mpdu_num);
                oal_kernel_file_print(pst_fs, "report seqnum by hw : ");

                for (us_seq_index = 0; us_seq_index < pst_seq_track->un_mix_dscr.st_report.uc_report_mpdu_num; us_seq_index++)
                {
                    oal_kernel_file_print(pst_fs, "%d ", pst_seq_track->un_mix_dscr.st_report.aus_report_seqnum[us_seq_index]);
                }

                oal_kernel_file_print(pst_fs, "\n");
            }
            else /*����ǰ�� ��������������ӡ*/
            {
                oal_kernel_file_print(pst_fs, "ba track BEFORE tx \n");
                oal_kernel_file_print(pst_fs, "schedule_mpdu_num = %d \n", pst_seq_track->un_mix_dscr.st_schedule.uc_schedule_mpdu_num);
                oal_kernel_file_print(pst_fs, "schedule seqnum : ");
                for (us_seq_index = 0; us_seq_index < pst_seq_track->un_mix_dscr.st_schedule.uc_schedule_mpdu_num; us_seq_index++)
                {
                     oal_kernel_file_print(pst_fs, "%d ", pst_seq_track->un_mix_dscr.st_schedule.aus_schedule_seqnum[us_seq_index]);
                }

                oal_kernel_file_print(pst_fs, "\n");
            }

            /*tid ������Ϣ��ӡ*/
            oal_kernel_file_print(pst_fs, "tid_total_mpdu_num = %d, tid_retry_mpdu_num = %d)\n", pst_seq_track->us_tid_total_mpdu_num, pst_seq_track->uc_tid_retry_mpdu_num);
            oal_kernel_file_print(pst_fs, "tid_queue_seqnum : ");
            for (us_seq_index = 0; us_seq_index < pst_seq_track->uc_tid_record_mpdu_num; us_seq_index++)
            {
                oal_kernel_file_print(pst_fs, "%d ", pst_tx_ba_track->ast_seq_bitmap_log[us_track_index].aus_tid_seqnum[us_seq_index]);
            }
            oal_kernel_file_print(pst_fs, "\n");

            /*ba handle��Ϣ��ӡ*/
            oal_kernel_file_print(pst_fs, "ba bitmap : %08x %08x %08x %08x \n",
                         pst_seq_track->aul_bitmap[0],
                         pst_seq_track->aul_bitmap[1],
                         pst_seq_track->aul_bitmap[2],
                         pst_seq_track->aul_bitmap[3]);

            oal_kernel_file_print(pst_fs, "baw_start: %d , baw_lsn: %d, baw_head: %d, baw_tail: %d \n",
                         pst_seq_track->us_seq_start,
                         pst_seq_track->us_lsn,
                         pst_seq_track->us_baw_head,
                         pst_seq_track->us_baw_tail);

            us_track_index = (us_track_index + 1) & (OAM_SEQ_TRACK_NUM - 1);
        }
//#endif
#endif
#endif
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_get_mpdu_num(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32          ul_ret;
    oal_uint16          us_user_idx = 0;
    mac_cfg_get_mpdu_num_stru   *pst_param;
    mac_device_stru             *pst_mac_dev;
    dmac_user_stru              *pst_dmac_user;
    oam_report_mpdu_num_stru     st_mpdu_num;

    pst_param = (mac_cfg_get_mpdu_num_stru *)puc_param;

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_param->auc_user_macaddr, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_get_mpdu_num::find user return no succ! ul_ret=%d}\r\n", ul_ret);
        return ul_ret;
    }

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_get_mpdu_num:: pst_mac_dev is Null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_get_mpdu_num:: pst_dmac_user is Null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_mpdu_num.us_total_mpdu_num_in_device = pst_mac_dev->us_total_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid0         = pst_dmac_user->ast_tx_tid_queue[0].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid1         = pst_dmac_user->ast_tx_tid_queue[1].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid2         = pst_dmac_user->ast_tx_tid_queue[2].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid3         = pst_dmac_user->ast_tx_tid_queue[3].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid4         = pst_dmac_user->ast_tx_tid_queue[4].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid5         = pst_dmac_user->ast_tx_tid_queue[5].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid6         = pst_dmac_user->ast_tx_tid_queue[6].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid7         = pst_dmac_user->ast_tx_tid_queue[7].us_mpdu_num;

    return oam_report_mpdu_num(pst_dmac_user->st_user_base_info.auc_user_mac_addr, &st_mpdu_num);
}
#if 0
/*****************************************************************************
 �� �� ��  : dmac_config_ota_switch
 ��������  : OTA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ota_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wal_specific_event_type_param_stru      *pst_specific_event_param;
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;

    pst_specific_event_param = (wal_specific_event_type_param_stru *)puc_param;

    OAL_IO_PRINT("dmac_config_ota_switch: en_ota_type:%d  en_switch_type:%d \n", pst_specific_event_param->l_event_type, pst_specific_event_param->l_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
        ul_ret = oam_ota_set_switch(uc_vap_id_loop,
                                    (oal_switch_enum_uint8)pst_specific_event_param->l_param,
                                    (oam_ota_type_enum_uint8)pst_specific_event_param->l_event_type);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_ANY, "{dmac_config_ota_switch::ota switch set failed!}\r\n");
            return ul_ret;
        }
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

#define DPD_CALI_LUT_LENGTH 128
oal_uint32  dmac_dpd_data_processed_recv(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    oal_netbuf_stru            *pst_dpd_data_netbuf;
    dpd_cali_data_stru         *pst_dpd_cali_data_processed;
    dmac_tx_event_stru         *pst_dtx_event;

    OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv function called.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv::pst_event_mem null.}");
      return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dtx_event       = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dpd_data_netbuf = pst_dtx_event->pst_netbuf;

    pst_dpd_cali_data_processed = (dpd_cali_data_stru *)OAL_NETBUF_DATA(pst_dpd_data_netbuf);

    // write dpd data back to register
    hal_dpd_cali_func(HAL_DPD_CALI_DATA_WRITE, 0, 0, pst_dpd_cali_data_processed->us_dpd_data);
    oal_netbuf_free(pst_dpd_data_netbuf);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_dpd_cali_data_send(mac_vap_stru *pst_mac_vap, oal_void *p_param)
{
    frw_event_mem_stru      *pst_event_mem;
    frw_event_stru          *pst_event;
    dmac_tx_event_stru      *pst_dpd_event;
    oal_netbuf_stru         *pst_netbuf_dpd_data;
    dpd_cali_data_stru      *pst_dpd_cali_data;


    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CALIBRATE,
                       "{dmac_send_dpd_calibrated_data::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_netbuf_dpd_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, OAL_SIZEOF(dpd_cali_data_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf_dpd_data)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_cali_data_send::pst_netbuf_scan_result null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf_dpd_data), OAL_TX_CB_LEN);

    pst_dpd_cali_data = (dpd_cali_data_stru *)(OAL_NETBUF_DATA(pst_netbuf_dpd_data));
    oal_memcopy(pst_dpd_cali_data, p_param, OAL_SIZEOF(dpd_cali_data_stru));

    pst_dpd_event              = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dpd_event->pst_netbuf  = pst_netbuf_dpd_data;
    pst_dpd_event->us_frame_len = OAL_SIZEOF(dpd_cali_data_stru);

    frw_event_dispatch_event(pst_event_mem);

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

oal_void dmac_start_dpd_calibration(mac_vap_stru *pst_mac_vap)
{
   oal_uint32 ul_status = OAL_FAIL;
    oal_uint8 index = 0;

   dpd_cali_data_stru dpd_cali_data_read;
   //dpd_cali_data_stru dpd_cali_data_calc;

   if(OAL_PTR_NULL == pst_mac_vap)
   {
     OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "dmac_start_dpd_calibration fail PTR_NULL\n\r");
     return;
   }

   OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "DPD Calibration Start\n\r");

   hal_dpd_cali_func(HAL_DPD_CALI_START, 0, 0, 0);
   hal_dpd_cali_func(HAL_DPD_CALI_STATUS, &ul_status, 0, 0);

   if (OAL_SUCC == ul_status)
   {
     hal_dpd_cali_func(HAL_DPD_CALI_DATA_READ, 0, dpd_cali_data_read.us_dpd_data, 0);
     dpd_cali_data_read.us_data_len = HI1102_DMAC_DPD_CALI_LUT_LENGTH;
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAL_IO_PRINT("gain = 0x%6x\n\r", dpd_cali_data_read.us_dpd_data[index]);
            //dpd_cali_data_calc.us_dpd_data[index] = 0;
        }
#if 0
        hi1102_rf_cali_dpd_corr_calc(dpd_cali_data_read.us_dpd_data, dpd_cali_data_calc.us_dpd_data);
        OAL_IO_PRINT("show dpd results.\n\r", dpd_cali_data_calc.us_dpd_data[index]);
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAL_IO_PRINT("out = 0x%6x\n\r", dpd_cali_data_calc.us_dpd_data[index]);
        }
        hal_dpd_cali_func(HAL_DPD_CALI_DATA_WRITE, 0, 0, dpd_cali_data_calc.us_dpd_data);
        hal_dpd_cali_func(HAL_DPD_CALI_DATA_READ, 0, dpd_cali_data_read.us_dpd_data, 0);
        dpd_cali_data_read.us_data_len = HI1102_DMAC_DPD_CALI_LUT_LENGTH;
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAL_IO_PRINT("read lut = 0x%6x\n\r", dpd_cali_data_read.us_dpd_data[index]);
            dpd_cali_data_calc.us_dpd_data[index] = 0;
        }
#else
     dmac_dpd_cali_data_send(pst_mac_vap, (oal_void*)(&dpd_cali_data_read));
#endif
   }
}

//
//
//
OAL_STATIC oal_uint32 dmac_config_start_dpd(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

 dmac_start_dpd_calibration(pst_mac_vap);


   return OAL_SUCC;
}

#endif/*_PRE_WLAN_RF_110X_CALI_DPD end*/


oal_uint32  dmac_cali_hmac2dmac_recv(frw_event_mem_stru *pst_event_mem)
{
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    frw_event_stru             *pst_event;
    oal_netbuf_stru            *pst_cali_data_netbuf;
    oal_uint8                  *puc_cali_data;
    dmac_tx_event_stru         *pst_dtx_event;
   //oal_uint8                  *puc_content;
   //oal_uint32                  ul_byte;

   //OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv function called.}");
   //OAL_IO_PRINT("dmac_cali_hmac2dmac_recv: start\r\n");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dtx_event       = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_cali_data_netbuf = pst_dtx_event->pst_netbuf;

    puc_cali_data = (oal_uint8 *)OAL_NETBUF_DATA(pst_cali_data_netbuf);
#if 0
    puc_content = (oal_uint8 *)puc_cali_data;

    for (ul_byte = 0; ul_byte < OAL_SIZEOF(oal_cali_param_stru); ul_byte+=4)
    {
        OAL_IO_PRINT("%02X %02X %02X %02X\r\n", puc_content[ul_byte], puc_content[ul_byte+1],
                      puc_content[ul_byte+2], puc_content[ul_byte+3]);
    }

    for(idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++)
    {
      OAM_ERROR_LOG1(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv  received: 0x%X}", pst_dpd_cali_data_processed->us_dpd_data[idx]);
    }
#endif
    // write dpd data back to register


    hal_cali_send_func(puc_cali_data);

    oal_netbuf_free(pst_cali_data_netbuf);
#endif
    return OAL_SUCC;
}


#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 �� �� ��  : dmac_config_beacon_offload_test
 ��������  : OTA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_sta_beacon_offload_test(pst_mac_vap, puc_param);
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_config_ota_beacon_switch
 ��������  : beacon֡��OTA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ota_beacon_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;
    oal_int32                                l_value;

    l_value = *((oal_int32 *)puc_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
        ul_ret = oam_ota_set_beacon_switch(uc_vap_id_loop,
                                          (oam_sdt_print_beacon_rxdscr_type_enum_uint8)l_value);

        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_CFG, "{dmac_config_ota_beacon_switch::ota beacon switch set failed!}\r\n");
            return ul_ret;
        }
    }
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_ota_rx_dscr_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;
    oal_int32                                l_value;

    l_value = *((oal_int32 *)puc_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
          ul_ret = oam_ota_set_rx_dscr_switch(uc_vap_id_loop,
                                             (oal_switch_enum_uint8)l_value);

        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_CFG, "{dmac_config_ota_rx_dscr_switch::ota rx_dscr switch set failed!}\r\n");
            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_all_ota
 ��������  : ����OAMģ������λ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_all_ota(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_switch_enum_uint8      en_switch;

    en_switch = *((oal_switch_enum_uint8 *)puc_param);
    return oam_report_set_all_switch(en_switch);
}

/*****************************************************************************
 �� �� ��  : dmac_config_oam_output
 ��������  : ���������û�֡�ϱ������п��أ������1�����ϱ���������֡��֡���ݣ�
             cb�ֶΣ��������������0����ʲô�����ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_oam_output(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32                   l_value;
    oal_uint32                  ul_ret;

    l_value = *((oal_int32 *)puc_param);

    /* ����OAM logģ��Ŀ��� */
    ul_ret = oam_set_output_type((oam_output_type_enum_uint8)l_value);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_oam_output::oam_set_output_type failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_probe_switch
 ��������  : ����probe request��probe response�ϱ��Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_probe_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    mac_cfg_probe_switch_stru       *pst_probe_switch;
    oal_uint32                       ul_ret = 0;

    pst_probe_switch = (mac_cfg_probe_switch_stru *)puc_param;

    ul_ret = oam_report_80211_probe_set_switch(pst_probe_switch->en_frame_direction,
                                               pst_probe_switch->en_frame_switch,
                                               pst_probe_switch->en_cb_switch,
                                               pst_probe_switch->en_dscr_switch);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_probe_switch::oam_report_80211_probe_set_switch failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}

OAL_STATIC oal_uint32 dmac_config_80211_mcast_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_80211_mcast_switch_stru *pst_80211_switch_param;
    oal_uint32                       ul_ret = 0;

    pst_80211_switch_param = (mac_cfg_80211_mcast_switch_stru *)puc_param;

    ul_ret = oam_report_80211_mcast_set_switch(pst_80211_switch_param->en_frame_direction,
                                               pst_80211_switch_param->en_frame_type,
                                               pst_80211_switch_param->en_frame_switch,
                                               pst_80211_switch_param->en_cb_switch,
                                               pst_80211_switch_param->en_dscr_switch);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_mcast_switch::oam_report_80211_mcast_set_switch failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_rssi_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_rssi_debug_switch_stru      *pst_rssi_switch;

    pst_rssi_switch = (mac_rssi_debug_switch_stru *)puc_param;

    /* ����rssi������Ϣ */
    oal_memcopy(&g_st_rssi_debug_switch_info, pst_rssi_switch, OAL_SIZEOF(mac_rssi_debug_switch_stru));

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 dmac_config_report_vap_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint32               ul_flags_value;

    /* �����Ϸ����ж� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_report_vap_info::input params is invalid, %p, %p.}",
                         pst_mac_vap, puc_param);
        return OAL_FAIL;
    }

    ul_flags_value = *(oal_uint32 *)puc_param;

    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_report_vap_info::vap_id[%d], flags_value[0x%08x].}",
                     pst_mac_vap->uc_vap_id, ul_flags_value);

    /* �ϱ�Ӳ����Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_HARDWARE_INFO)
    {
        dmac_dft_report_mac_hardware_info(pst_mac_vap);
    }

    /* �ϱ�������Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_QUEUE_INFO)
    {
        dmac_dft_report_dmac_queue_info(pst_mac_vap);
    }

    /* �ϱ��ڴ���Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_MEMORY_INFO)
    {
        dmac_dft_report_dmac_memory_info(pst_mac_vap);
    }

    /* �ϱ��¼���Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_EVENT_INFO)
    {
        dmac_dft_report_dmac_event_info(pst_mac_vap);
    }

    /* �ϱ�vap��Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_VAP_INFO)
    {
        dmac_dft_report_dmac_vap_info(pst_mac_vap);
    }

    /* �ϱ��û���Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_USER_INFO)
    {
        dmac_dft_report_dmac_user_info(pst_mac_vap);
    }

    /* �ϱ��շ���ͳ����Ϣ */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_TXRX_PACKET_STATISTICS)
    {
        dmac_config_report_vap_stat(pst_mac_vap, uc_len, puc_param);
    }
#else
    OAM_WARNING_LOG0(0, OAM_SF_ANY,
                     "{dmac_config_report_vap_info::DFT macro switch is not open, do nothing.}");
#endif

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

OAL_STATIC oal_uint32  dmac_config_80211_ucast_switch(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
    mac_cfg_80211_ucast_switch_stru *pst_80211_switch_param;
    oal_uint16                       us_user_idx = 0;
    oal_uint32                       ul_ret;

    pst_80211_switch_param = (mac_cfg_80211_ucast_switch_stru *)puc_param;

    /* �㲥��ַ�����������û��ĵ���֡���� */
    if (ETHER_IS_BROADCAST(pst_80211_switch_param->auc_user_macaddr))
    {
        for (us_user_idx = 0; us_user_idx < WLAN_ACTIVE_USER_MAX_NUM + WLAN_MAX_MULTI_USER_NUM_SPEC; us_user_idx++)
        {
            oam_report_80211_ucast_set_switch(pst_80211_switch_param->en_frame_direction,
                                              pst_80211_switch_param->en_frame_type,
                                              pst_80211_switch_param->en_frame_switch,
                                              pst_80211_switch_param->en_cb_switch,
                                              pst_80211_switch_param->en_dscr_switch,
                                              us_user_idx);
        }
        return OAL_SUCC;
    }

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap,
                                          pst_80211_switch_param->auc_user_macaddr,
                                          &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_ucast_switch::mac_vap_find_user_by_macaddr[%02X:XX:XX:%02X:%02X:%02X]failed !!}",
                        pst_80211_switch_param->auc_user_macaddr[0],
                        pst_80211_switch_param->auc_user_macaddr[3],
                        pst_80211_switch_param->auc_user_macaddr[4],
                        pst_80211_switch_param->auc_user_macaddr[5]);
        return ul_ret;
    }

    ul_ret = oam_report_80211_ucast_set_switch(pst_80211_switch_param->en_frame_direction,
                                               pst_80211_switch_param->en_frame_type,
                                               pst_80211_switch_param->en_frame_switch,
                                               pst_80211_switch_param->en_cb_switch,
                                               pst_80211_switch_param->en_dscr_switch,
                                               us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_ucast_switch::Set switch of report_ucast failed[%d]!!frame_switch[%d], cb_switch[%d], dscr_switch[%d].}",
                ul_ret,
                pst_80211_switch_param->en_frame_switch,
                pst_80211_switch_param->en_cb_switch,
                pst_80211_switch_param->en_dscr_switch);
        return ul_ret;
    }
    return OAL_SUCC;
}
#endif /* DMAC_OFFLOAD */


OAL_STATIC oal_uint32  dmac_config_dump_all_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_dump_all_rx_dscr(pst_device->pst_device_stru);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_reset_hw
 ��������  : ��λӲ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��8��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reset_hw(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    mac_device_stru    *pst_device;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];
    dmac_reset_para_stru            st_reset_param;

    /* ��λӲ��phy&mac: hipriv "Hisilicon0 reset_hw 0|1|2|3(all|phy|mac|debug) 0|1(reset phy reg) 0|1(reset mac reg)"*/
    /* �������debug��ʾlut��ͼĴ���:hipriv "Hisilicon0 reset_hw 3(debug) 0|1|2(all|mac reg|phy reg|lut) "*/

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* ��������������� */
    if(OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reset_hw::pst_device is null,id=%d}", pst_mac_vap->uc_device_id);

        return OAL_FAIL;
    }

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);
    /* ��ȡ��λ����*/
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
    st_reset_param.uc_reset_type = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    puc_param = puc_param + ul_off_set;

    //if (st_reset_param.uc_reset_type <= HAL_RESET_HW_TYPE_MAC_PHY)
    if (st_reset_param.uc_reset_type < HAL_RESET_HW_TYPE_DUMP_MAC)
    {
        /* ��ȡ�Ƿ�λphy reg */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_reset_phy_reg = (oal_uint8)oal_atoi(ac_name);
        /* ƫ�ƣ�ȡ��һ������ */
        puc_param = puc_param + ul_off_set;

        /* ��ȡ�Ƿ�λmac reg */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_reset_mac_reg = (oal_uint8)oal_atoi(ac_name);
        /* ƫ�ƣ�ȡ��һ������ */
        puc_param = puc_param + ul_off_set;

        st_reset_param.uc_reset_mac_mod = HAL_RESET_MAC_ALL;    /* HAL_RESET_MAC_ALL*/
        st_reset_param.uc_reason = 1;           /*DMAC_RESET_REASON_CONFIG*/
        dmac_reset_hw(pst_device,(oal_uint8*)&st_reset_param);
    }
    else
    {

        /* ��ȡdebug����:0|1|2(all|mac reg|phy reg|lut) */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_debug_type= (oal_uint8)oal_atoi(ac_name);
        /* ƫ�ƣ�ȡ��һ������ */
        puc_param = puc_param + ul_off_set;

        dmac_reset_debug_all(pst_device,&st_reset_param);
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_dump_rx_dscr
 ��������  : dump rx ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��2��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    hal_rx_dscr_queue_header_stru   *pst_rx_dscr_queue;
    mac_device_stru                 *pst_mac_device;
    hal_to_dmac_device_stru         *pst_hal_device;
    oal_uint32                      *pul_curr_dscr;
    hal_rx_dscr_stru                *pst_hal_to_dmac_dscr;
    oal_uint32                       ul_value;
    oal_uint32                       ul_rx_dscr_len = 0;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#ifdef _PRE_DEBUG_MODE
    oal_uint32                       ul_loop;
    oal_uint32                      *pul_original_dscr;
    oal_uint32                       ul_dscr_num;
#endif

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_dump_rx_dscr::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    ul_value = *((oal_uint32 *)puc_param);

    if (ul_value >= HAL_RX_DSCR_QUEUE_ID_BUTT)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_config_dump_rx_dscr::invalid rx dscr queue[%d].}", ul_value);
        return OAL_FAIL;
    }

    hal_rx_get_size_dscr(pst_hal_device, &ul_rx_dscr_len);

#ifdef _PRE_DEBUG_MODE
    /* ��������ԭʼ��ַ����� */
    OAM_INFO_LOG0(0, OAM_SF_CFG, "the origin dscr phy addr and virtual addr:\n");

    if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == ul_value)
    {
        pul_original_dscr = pst_hal_device->aul_nor_rx_dscr;
        ul_dscr_num       = HAL_NORMAL_RX_MAX_BUFFS;
    }
    else
    {
        pul_original_dscr = pst_hal_device->aul_hi_rx_dscr;
        ul_dscr_num       = HAL_HIGH_RX_MAX_BUFFS;
    }

    for (ul_loop = 0; ul_loop < ul_dscr_num; ul_loop++)
    {
        pul_curr_dscr = OAL_PHY_TO_VIRT_ADDR(pul_original_dscr[ul_loop]);
        OAM_INFO_LOG3(0, OAM_SF_CFG, "%2d 0x%08x, 0x%08x\n",
                     ul_loop,
                     pul_original_dscr[ul_loop],
                     (oal_uint32)pul_curr_dscr);

        oam_report_dscr(auc_user_macaddr, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
    }

    OAM_INFO_LOG1(0, OAM_SF_CFG, "dscr exception free cnt is %d\n", pst_hal_device->ul_exception_free);
#endif

    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[ul_value]);

    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

    //OAM_INFO_LOG1(0, OAM_SF_CFG, "the current dscr cnt is: %d\n", pst_rx_dscr_queue->us_element_cnt);
    //OAM_INFO_LOG1(0, OAM_SF_CFG, "head ptr virtual addr is: 0x%08x\n", (oal_uint32)pst_rx_dscr_queue->pul_element_head);
    //OAM_INFO_LOG1(0, OAM_SF_CFG, "tail ptr virtual addr is: 0x%08x\n", (oal_uint32)pst_rx_dscr_queue->pul_element_tail);

    OAM_INFO_LOG0(0, OAM_SF_CFG, "the current dscr addr and dscr's content:\n");
    while(OAL_PTR_NULL != pul_curr_dscr)
    {
        OAM_INFO_LOG2(0, OAM_SF_CFG, "virtual addr:0x%08x, phy addr:0x%08x\n", (oal_uint32)pul_curr_dscr, (oal_uint32)OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)));
        oam_report_dscr(auc_user_macaddr, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);

        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
        pul_curr_dscr        = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));
    }

    hal_rx_show_dscr_queue_info(pst_hal_device, (oal_uint8)ul_value);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_dump_tx_dscr
 ��������  : dump tx ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��2��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_tx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    hal_to_dmac_device_stru         *pst_hal_device;
    oal_uint32                       ul_value;
    hal_tx_dscr_stru                *pst_dscr;
    oal_dlist_head_stru             *pst_pos;
    oal_netbuf_stru                 *pst_netbuf;
    mac_tx_ctl_stru                 *pst_tx_cb;
    oal_uint32                       ul_dscr_one_size = 0;
    oal_uint32                       ul_dscr_two_size = 0;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_tx_dscr::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_hal_device = pst_mac_device->pst_device_stru;

    ul_value = *((oal_uint32 *)puc_param);

    if (ul_value >= HAL_TX_QUEUE_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_dump_rx_dscr::invalid tx dscr queue[%d].}", ul_value);
        return OAL_FAIL;
    }

    OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_hal_device->ast_tx_dscr_queue[ul_value].st_header))
    {
        pst_dscr   = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;
        pst_tx_cb  = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);

        hal_tx_get_size_dscr(pst_hal_device, MAC_GET_CB_NETBUF_NUM(pst_tx_cb), &ul_dscr_one_size, &ul_dscr_two_size);
        oam_report_dscr(auc_user_macaddr,
                        (oal_uint8 *)pst_dscr,
                        (oal_uint16)(ul_dscr_one_size + ul_dscr_two_size),
                        OAM_OTA_TYPE_TX_DSCR);
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_connect(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32                                   ul_ret;
    mac_cfg80211_connect_security_stru          *pst_conn;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_connect::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_conn = (mac_cfg80211_connect_security_stru *)puc_param;

    ul_ret = mac_vap_init_privacy(pst_mac_vap, pst_conn);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_connect::mac_11i_init_privacy fail [%d].}", ul_ret);
        return ul_ret;
    }
#ifdef _PRE_WLAN_FEATURE_11R
    ul_ret = mac_mib_init_ft_cfg(pst_mac_vap, pst_conn->auc_mde);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_connect::mac_mib_init_ft_cfg fail[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
#endif //_PRE_WLAN_FEATURE_11R

#endif

    return OAL_SUCC;
}

#ifdef _PRE_DEBUG_MODE_USER_TRACK

OAL_STATIC oal_uint32  dmac_config_report_thrput_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_usr_thrput_stru             *pst_usr_thrput_param;
    oal_uint16                           us_usr_idx = 0;
    oal_uint32                           ul_ret;
    dmac_user_stru                      *pst_dmac_user;

    pst_usr_thrput_param = (mac_cfg_usr_thrput_stru *)puc_param;

    /* ��ȡ�û� */
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_usr_thrput_param->auc_user_macaddr, &us_usr_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_report_thrput_stat::find usr fail.}");
        return ul_ret;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_usr_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_report_thrput_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_usr_thrput_param->uc_param)
    {
        /* ֹͣ�ϱ� */
        return dmac_user_track_clear_usr_thrput_stat(&pst_dmac_user->st_user_base_info);
    }
    else
    {
        return dmac_user_track_report_usr_thrput_stat(&pst_dmac_user->st_user_base_info);
    }
}

#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 �� �� ��  : dmac_config_print_btcoex_status
 ��������  : ��ӡ����ά����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_print_btcoex_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_get_btcoex_statistic();
    return OAL_SUCC;
}

#endif
#ifdef _PRE_WLAN_DFT_STAT

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)


OAL_STATIC oal_uint32  dmac_config_phy_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if 0
    oam_stats_phy_stat_stru         st_phy_stat;
    mac_device_stru                *pst_macdev;
    oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_macdev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_phy_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_phy_stat, OAL_SIZEOF(oam_stats_phy_stat_stru));

    hal_dft_get_phyhw_stat_info(pst_macdev->pst_device_stru,&st_phy_stat);

    /* ����ȡ����ͳ��ֵ�ϱ� */
    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_phy_stat,(oal_uint16)OAL_SIZEOF(oam_stats_phy_stat_stru), OAM_OTA_TYPE_PHY_STAT);
#endif
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_machw_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if 0
    mac_device_stru                 *pst_mac_dev;
#if 0
    oal_uint8                        uc_loop;
    oal_uint32                       ul_reg_addr;
    oal_uint32                       ul_reg_val = 0;
#endif
    oam_stats_machw_stat_stru        st_machw_stat;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_machw_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* ����macͳ��,macͳ������Ĵ�����bit2~bit22,bit4�Ƿ���beacon֡��Ŀ��bit9�Ǹ����ȼ����з�����Ŀ�������㣬
           ������ͳ��ֵ���ڹ���֡ͳ�ƹ��ܿ���
        */
        hal_dft_clear_machw_stat_info(pst_mac_dev->pst_device_stru);
        return OAL_SUCC;
    }
    else
    {
        OAL_MEMZERO(&st_machw_stat, OAL_SIZEOF(oam_stats_machw_stat_stru));

        /* ��MAC�Ĵ�����ȡͳ��ֵ */
        dmac_dft_get_machw_stat_info(pst_mac_dev->pst_device_stru, &st_machw_stat);
    #if 0
        /* ��ȡmac rxͳ����Ϣ��ֱ�Ӷ�mac�Ĵ��� */
        for (ul_reg_addr = (oal_uint32)WITP_PA_RX_AMPDU_COUNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_RX_FILTERED_CNT_REG && uc_loop < OAM_MACHW_STAT_RX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_rx_cnt[uc_loop] = ul_reg_val;
        }

        /* ��ȡmac txͳ����Ϣ��ֱ�Ӷ�mac�Ĵ��� */
        for (ul_reg_addr = (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_HI_PRI_RETRY_CNT_REG && uc_loop < OAM_MACHW_STAT_TX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_tx_cnt[uc_loop] = ul_reg_val;
        }
    #endif
        return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_machw_stat,(oal_uint16)OAL_SIZEOF(oam_stats_machw_stat_stru), OAM_OTA_TYPE_MACHW_STAT);
    }
#endif
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_report_mgmt_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
    oam_stats_mgmt_stat_stru         st_mgmt_stat;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_report_mgmt_stat::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* ����macͳ�Ƶķ���beacon֡��Ŀ�������ȼ����з�����Ŀ:MACͳ�ƼĴ�����bit4��bit9 */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, 0x210);

        /* �������ͳ�ƵĹ���֡�շ���Ŀ */
        OAL_MEMZERO(&pst_mac_dev->st_mgmt_stat, OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        return OAL_SUCC;
    }
    else
    {
        /* ��ȡmacͳ�Ƶķ���beacon֡��Ŀ�͸����ȼ����з�����Ŀ */
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_BCN_COUNT_REG, &st_mgmt_stat.ul_machw_stat_tx_bcn_cnt);
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_HI_PRI_MPDU_CNT_REG, &st_mgmt_stat.ul_machw_stat_tx_hi_cnt);

        /* ��ȡ����Ĺ���֡�շ�ͳ�� */
        oal_memcopy(st_mgmt_stat.aul_sw_rx_mgmt_cnt,
                    &pst_mac_dev->st_mgmt_stat,
                    OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        /* ��ͳ��ֵ�ϱ� */
        return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_mgmt_stat, (oal_uint16)OAL_SIZEOF(oam_stats_mgmt_stat_stru),OAM_OTA_TYPE_MGMT_STAT);
    }
}


#else
OAL_STATIC oal_uint32  dmac_config_phy_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oam_stats_phy_stat_stru         st_phy_stat;
    mac_device_stru                *pst_macdev;
    oal_uint8                       uc_loop;
    oal_uint32                      ul_reg_addr;
    oal_uint32                      ul_reg_val = 0;
    oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_macdev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_phy_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_phy_stat, OAL_SIZEOF(oam_stats_phy_stat_stru));

    /* ��ȡ�û�ָ��ͳ�Ƶ�4��phyͳ��ֵ */
    for (ul_reg_addr = (oal_uint32)WITP_PHY_PHY_STA0_RPT_REG, uc_loop = 0;
         ul_reg_addr <= (oal_uint32)WITP_PHY_PHY_STA3_RPT_REG && uc_loop < OAM_PHY_STAT_NODE_ENABLED_MAX_NUM;
         ul_reg_addr += 4, uc_loop++)
    {
        hal_reg_info(pst_macdev->pst_device_stru, ul_reg_addr, &ul_reg_val);
        st_phy_stat.aul_user_requested_stat_cnt[uc_loop] = ul_reg_val;
    }

    /* ��ȡphy����Э��ģʽͳ�ƵĽ�����ȷ�ʹ���֡���� */
    for (ul_reg_addr = (oal_uint32)WITP_PHY_DOTB_OK_FRM_NUM_REG, uc_loop = 0;
         ul_reg_addr <= (oal_uint32)WITP_PHY_LEGA_ERR_FRM_NUM_REG && uc_loop < OAM_PHY_STAT_RX_PPDU_CNT;
         ul_reg_addr += 4, uc_loop++)
    {
        hal_reg_info(pst_macdev->pst_device_stru, ul_reg_addr, &ul_reg_val);
        st_phy_stat.aul_phy_stat_rx_ppdu_cnt[uc_loop] = ul_reg_val;
    }

    /* ����ȡ����ͳ��ֵ�ϱ� */
    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_phy_stat,(oal_uint16)OAL_SIZEOF(oam_stats_phy_stat_stru), OAM_OTA_TYPE_PHY_STAT);
}
OAL_STATIC oal_uint32  dmac_config_machw_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
#if 0
    oal_uint8                        uc_loop;
    oal_uint32                       ul_reg_addr;
    oal_uint32                       ul_reg_val = 0;
#endif
    oam_stats_machw_stat_stru        st_machw_stat;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_machw_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* ����macͳ��,macͳ������Ĵ�����bit2~bit22,bit4�Ƿ���beacon֡��Ŀ��bit9�Ǹ����ȼ����з�����Ŀ�������㣬
           ������ͳ��ֵ���ڹ���֡ͳ�ƹ��ܿ���
        */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, 0x7FFDEC);

        return OAL_SUCC;
    }
    else
    {
        OAL_MEMZERO(&st_machw_stat, OAL_SIZEOF(oam_stats_machw_stat_stru));

        /* ��MAC�Ĵ�����ȡͳ��ֵ */
        dmac_dft_get_machw_stat_info(pst_mac_dev->pst_device_stru, &st_machw_stat);
    #if 0
        /* ��ȡmac rxͳ����Ϣ��ֱ�Ӷ�mac�Ĵ��� */
        for (ul_reg_addr = (oal_uint32)WITP_PA_RX_AMPDU_COUNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_RX_FILTERED_CNT_REG && uc_loop < OAM_MACHW_STAT_RX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_rx_cnt[uc_loop] = ul_reg_val;
        }

        /* ��ȡmac txͳ����Ϣ��ֱ�Ӷ�mac�Ĵ��� */
        for (ul_reg_addr = (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_HI_PRI_RETRY_CNT_REG && uc_loop < OAM_MACHW_STAT_TX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_tx_cnt[uc_loop] = ul_reg_val;
        }
    #endif
        return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_machw_stat,(oal_uint16)OAL_SIZEOF(oam_stats_machw_stat_stru), OAM_OTA_TYPE_MACHW_STAT);
    }
}
OAL_STATIC oal_uint32  dmac_config_report_mgmt_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
    oam_stats_mgmt_stat_stru         st_mgmt_stat;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_report_mgmt_stat::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* ����macͳ�Ƶķ���beacon֡��Ŀ�������ȼ����з�����Ŀ:MACͳ�ƼĴ�����bit4��bit9 */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, 0x210);

        /* �������ͳ�ƵĹ���֡�շ���Ŀ */
        OAL_MEMZERO(&pst_mac_dev->st_mgmt_stat, OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        return OAL_SUCC;
    }
    else
    {
        /* ��ȡmacͳ�Ƶķ���beacon֡��Ŀ�͸����ȼ����з�����Ŀ */
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_TX_BCN_COUNT_REG, &st_mgmt_stat.ul_machw_stat_tx_bcn_cnt);
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, &st_mgmt_stat.ul_machw_stat_tx_hi_cnt);

        /* ��ȡ����Ĺ���֡�շ�ͳ�� */
        oal_memcopy(st_mgmt_stat.aul_sw_rx_mgmt_cnt,
                    &pst_mac_dev->st_mgmt_stat,
                    OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        /* ��ͳ��ֵ�ϱ� */
        return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_mgmt_stat,(oal_uint16)OAL_SIZEOF(oam_stats_mgmt_stat_stru), OAM_OTA_TYPE_MGMT_STAT);
    }
}
OAL_STATIC oal_uint32  dmac_config_usr_queue_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_usr_queue_param_stru        *pst_usr_queue_param;
    oal_uint16                           us_usr_idx = 0;
    oal_uint32                           ul_ret;
    dmac_user_stru                      *pst_dmac_user;

    pst_usr_queue_param = (mac_cfg_usr_queue_param_stru *)puc_param;

    /* ��ȡ�û� */
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_usr_queue_param->auc_user_macaddr, &us_usr_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_usr_queue_stat::find usr fail.}");
        return ul_ret;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_usr_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_usr_queue_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_usr_queue_param->uc_param)
    {
        /* ����û�����ͳ����Ϣ */
        return dmac_dft_clear_usr_queue_stat(pst_dmac_user);
    }
    else
    {
        return dmac_dft_report_usr_queue_stat(pst_dmac_user);
    }
}

#endif

OAL_STATIC oal_uint32  dmac_config_report_vap_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    dmac_vap_query_stats_stru    st_vap_dft_stats;
    oal_uint8                    auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#if (_PRE_OS_VERSION == _PRE_OS_VERSION_RAW)
    oal_uint8                    uc_vap_id;
#endif
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_config_report_vap_stat::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#if (_PRE_OS_VERSION == _PRE_OS_VERSION_RAW)
    uc_vap_id = pst_mac_vap->uc_vap_id;
#endif
    OAL_MEMZERO(&st_vap_dft_stats, OAL_SIZEOF(oam_stats_vap_stat_stru));
#if (_PRE_OS_VERSION == _PRE_OS_VERSION_RAW)
    OAM_WARNING_LOG_ALTER(uc_vap_id, OAM_SF_RX, "{dmac_config_report_vap_stat::drv_tx_pkts[%lu], hw_tx_pkts_succ[%lu], tx_fail[%lu], rx_mpdus[%lu], rx_drops[%lu], rx_null[%lu], rx_mgmt[%lu]}", 7,
                        pst_dmac_vap->st_query_stats.ul_drv_tx_pkts, pst_dmac_vap->st_query_stats.ul_hw_tx_pkts, pst_dmac_vap->st_query_stats.ul_tx_failed,
                        pst_dmac_vap->st_query_stats.ul_rx_mpdu_total_num,
                        (pst_dmac_vap->st_query_stats.ul_rx_dropped_misc + pst_dmac_vap->st_query_stats.ul_rx_alg_process_dropped + pst_dmac_vap->st_query_stats.ul_rx_security_check_fail_dropped),
                        pst_dmac_vap->st_query_stats.ul_rx_null_frame_dropped,
                        pst_dmac_vap->st_query_stats.ul_rx_mgmt_mpdu_num_cnt);
#endif
    oal_memcopy(&st_vap_dft_stats,
                &(pst_dmac_vap->st_query_stats),
                OAL_SIZEOF(dmac_vap_query_stats_stru));

    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_vap_dft_stats,(oal_uint16)OAL_SIZEOF(dmac_vap_query_stats_stru),OAM_OTA_TYPE_VAP_STAT);


}


OAL_STATIC oal_uint32  dmac_config_set_phy_stat_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oam_stats_phy_node_idx_stru     *pst_phy_node_idx;
    mac_device_stru                 *pst_mac_dev;

    pst_phy_node_idx = (oam_stats_phy_node_idx_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_phy_stat_en::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return dmac_dft_set_phy_stat_node(pst_mac_dev, pst_phy_node_idx);
}


OAL_STATIC oal_uint32  dmac_config_dbb_env_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    if (OAL_FALSE == *puc_param)
    {
        /* ֹͣ�ϱ����������Դ */
        return dmac_dft_stop_report_dbb_env(pst_mac_vap);
    }
    else
    {
        /* ��ʼ����(20ms)�ɼ�,����(2s)�ϱ� */
        return dmac_dft_start_report_dbb_env(pst_mac_vap);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_config_report_irq_info
 ��������  : ��ʾ�����жϸ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_irq_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_show_irq_info::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_show_irq_info(pst_device->pst_device_stru, *puc_param);
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_report_all_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token_type;
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint8             uc_val;

    /* ��ȡҪ��ȡ�ļĴ������� */
    pc_token_type = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token_type)
    {
        return OAL_FAIL;
    }
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    uc_val = (oal_uint8)oal_strtol(pc_token, &pc_end, 16);

    if (0 == oal_strcmp(pc_token, "soc"))
    {
        if (OAL_TRUE == uc_val)
        {
            dmac_config_phy_stat_info(pst_mac_vap, uc_len, &uc_val);
        }
    }
    else if (0 == oal_strcmp(pc_token, "machw"))
    {
        dmac_config_machw_stat_info(pst_mac_vap, uc_len, &uc_val);
    }
    else if (0 == oal_strcmp(pc_token, "mgmt"))
    {
        dmac_config_report_mgmt_stat(pst_mac_vap, uc_len, &uc_val);
    }
    else if (0 == oal_strcmp(pc_token, "irq"))
    {
        dmac_config_report_irq_info(pst_mac_vap, uc_len, &uc_val);
    }
    else
    {
        dmac_config_report_irq_info(pst_mac_vap, uc_len, &uc_val);
        dmac_config_report_mgmt_stat(pst_mac_vap, uc_len, &uc_val);
        dmac_config_machw_stat_info(pst_mac_vap, uc_len, &uc_val);
        if (OAL_TRUE == uc_val)
        {
            dmac_config_phy_stat_info(pst_mac_vap, uc_len, &uc_val);
        }
    }

    return OAL_SUCC;
}
#endif
OAL_STATIC oal_uint32  dmac_config_user_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* mips????????,??????? */
#ifndef _PRE_WLAN_PROFLING_MIPS
    dmac_user_stru                  *pst_dmac_user;
    mac_cfg_user_info_param_stru    *pst_dmac_event;
    oam_output_type_enum_uint8      en_output_type  = OAM_OUTPUT_TYPE_BUTT;
    oal_uint8                       uc_tid_index;
    //oal_uint32                      ul_tid_mpdu_num    = 0;

    /* ��ȡdmac user */
    pst_dmac_event = (mac_cfg_user_info_param_stru *)puc_param;
    pst_dmac_user  = (dmac_user_stru *)mac_res_get_dmac_user(pst_dmac_event->us_user_idx);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_user_info::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "dmac_config_user_info::us_assoc_id is %d, last_active_timestamp[%u]",
                     pst_dmac_user->st_user_base_info.us_assoc_id, pst_dmac_user->ul_last_active_timestamp);
#if 0
    for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index ++)
    {
        ul_tid_mpdu_num += pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num;
        if(pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num)
        {
            OAL_IO_PRINT("TID[%d],mpdu_num[%d],retry[%d],paused[%d]\r\n",
                   uc_tid_index,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].c_is_paused);
        }
    }
    OAL_IO_PRINT("dmac_config_user_info:totoal tid_mpdu_num %d\r\n", ul_tid_mpdu_num);
#endif
    oam_get_output_type(&en_output_type);
    if (OAM_OUTPUT_TYPE_SDT != en_output_type)
    {
#if 0
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_lut_index :        %d \n", pst_dmac_user->uc_lut_index);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "bit_ps :              %d \n", pst_dmac_user->bit_ps_mode);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_vip_flag :         %d \n", pst_dmac_user->en_vip_flag);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_smartant_training :%d \n", pst_dmac_user->en_smartant_training);
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");

        for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index ++)
        {
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "tid               %d \n", uc_tid_index);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_is_paused : %d \n", (oal_uint8)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].c_is_paused);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_dq : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_dq);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_retry_num : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "us_mpdu_num : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "ul_mpdu_avg_len : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].ul_mpdu_avg_len);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_tx_ba : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_tx_ba);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_rx_ba : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_rx_ba);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pst_ba_tx_hdl : %u \n", (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_tx_hdl);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pst_ba_rx_hdl : %u \n\n", (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_rx_hdl);
        }

        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "power save related user_info:\n");
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "mpdu num in ps_queue-->%d\n", oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num));
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "user ps mode is -->%d\n", pst_dmac_user->bit_ps_mode);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pspoll process state is -->%d\n", pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing);
#endif

        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_lut_index[%d]; bit_ps[%d];en_vip_flag[%d];en_smartant_training[%d]\n",
                      pst_dmac_user->uc_lut_index, pst_dmac_user->bit_ps_mode, pst_dmac_user->en_vip_flag, pst_dmac_user->en_smartant_training);

        for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index++)
        {
            OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "tid[%d]; uc_is_paused[%d]\n",
                          uc_tid_index, (oal_uint8)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_is_paused);

            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_dq[%d]; uc_retry_num[%d]; us_mpdu_num[%d]; ul_mpdu_avg_len[%d]\n",
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_dq,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].ul_mpdu_avg_len);

            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_tx_ba[%d]; uc_num_rx_ba[%d]; pst_ba_tx_hdl[%u]; pst_ba_rx_hdl[%u]\n",
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_tx_ba,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_rx_ba,
                          (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_tx_hdl,
                          (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_rx_hdl);
        }

        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "power save related user_info:mpdu num in ps_queue[%d]; user ps mode[%d]; pspoll process state[%d]\n",
                      oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num),
                      pst_dmac_user->bit_ps_mode,
                      pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing);
    }
    else
    {
        oam_ota_report((oal_uint8 *)&pst_dmac_user->uc_lut_index,
                       (oal_uint16)(OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru)),
                       0, 0, OAM_OTA_TYPE_DMAC_USER);
    }
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_dscr_param_stru     *pst_event_set_dscr;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_event_set_dscr = (mac_cfg_set_dscr_param_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    /* ������Ĭ�ϵ�set_ucast_data����, ����������ض�Э�������valid��־��0 */
    if (pst_event_set_dscr->en_type == MAC_VAP_CONFIG_UCAST_DATA)
    {
        pst_dmac_vap->un_mode_valid.uc_mode_param_valid = 0;
    }
    /* ����, ����������µ�set_mode_ucast_data����, �򽫶�ӦЭ�������valid��־��1 */
    else if (pst_event_set_dscr->en_type >= MAC_VAP_CONFIG_MODE_UCAST_DATA)
    {
        switch (pst_event_set_dscr->en_type)
        {
            case MAC_VAP_CONFIG_VHT_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_vht_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_HT_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_ht_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_11AG_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11ag_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_11B_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11b_param_vaild = 1;
                break;
            default:
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr::pst_event_set_dscr->en_type = %u, invalid}", pst_event_set_dscr->en_type);
                return OAL_FAIL;
        }
    }
#endif

    g_dmac_config_set_dscr_param[pst_event_set_dscr->uc_function_index](pst_event_set_dscr->l_value,
                                                                        pst_event_set_dscr->en_type,
                                                                        pst_dmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_log_level
 ��������  : ������־����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��21��
    ��    ��   : jwx222439
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_log_level(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // ����device log level��ҵ����Ӵ����߼�
    return oam_log_set_vap_level(pst_mac_vap->uc_vap_id, *puc_param);
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_feature_log
 ��������  : ������־����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��21��
    ��    ��   : jwx222439
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_feature_log(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // ����device log level��ҵ����Ӵ����߼�
    oal_uint16      us_param = *(oal_uint16 *)puc_param;
    return oam_log_set_feature_level(pst_mac_vap->uc_vap_id, (oal_uint8)(us_param>>8), (oal_uint8)us_param) ;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_country
 ��������  : ���ù�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��7��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_country(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_regdomain_info_stru *pst_mac_regdom;
    mac_regdomain_info_stru *pst_regdomain_info;
    oal_uint8                uc_rc_num;
    oal_uint32               ul_size;

    pst_mac_regdom = (mac_regdomain_info_stru *)puc_param;

    /* ��ȡ������ĸ��� */
    uc_rc_num = pst_mac_regdom->uc_regclass_num;

    /* ������������ */
    ul_size = OAL_SIZEOF(mac_regclass_info_stru) * uc_rc_num + MAC_RD_INFO_LEN;
    /*��ȡ������ȫ�ֱ���*/
    mac_get_regdomain_info(&pst_regdomain_info);

    /* ���¹�������Ϣ */
    oal_memcopy(pst_regdomain_info, pst_mac_regdom, ul_size);

    /* �����ŵ��Ĺ�������Ϣ */
    mac_init_channel_list();

#ifdef _PRE_SUPPORT_ACS
    dmac_acs_report_support_chan(pst_mac_vap);
#endif
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 �� �� ��  : dmac_config_set_country_for_dfs
 ��������  : ���ù�������dfs��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_country_for_dfs(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_dfs_domain_enum_uint8       en_dfs_domain;
    hal_to_dmac_device_stru        *pst_hal_device;
    mac_device_stru                *pst_mac_device;

    en_dfs_domain = *puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    pst_hal_device = pst_mac_device->pst_device_stru;

    if(OAL_PTR_NULL == pst_mac_device||OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "dmac_config_set_country_for_dfs::pointer null.");
        return OAL_FAIL;
    }

    hal_radar_config_reg(pst_hal_device, en_dfs_domain);

    pst_hal_device->st_dfs_radar_filter.ul_last_burst_timestamp           = 0;
    pst_hal_device->st_dfs_radar_filter.ul_last_burst_timestamp_for_chirp = 0;
    pst_hal_device->st_dfs_radar_filter.en_chirp_enable                   = 1;
    pst_hal_device->st_dfs_radar_filter.ul_time_threshold                 = 100;
    switch(en_dfs_domain)
    {
        case MAC_DFS_DOMAIN_ETSI:
            pst_hal_device->st_dfs_radar_filter.ul_chirp_cnt_threshold  = 3;
            pst_hal_device->st_dfs_radar_filter.ul_chirp_time_threshold = 100;
            break;
        case MAC_DFS_DOMAIN_FCC:
            pst_hal_device->st_dfs_radar_filter.ul_chirp_cnt_threshold  = 4;
            pst_hal_device->st_dfs_radar_filter.ul_chirp_time_threshold = 12000;
            break;
        default :
            break;
    }

    OAM_WARNING_LOG0(0, OAM_SF_DFS, "{dmac_config_set_country_for_dfs::set radar filter params.}");

    return OAL_SUCC;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : dmac_config_list_channel
 ��������  : �ϱ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_list_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_regdomain_info_stru *pst_regdomain_info                     = OAL_PTR_NULL;
    oal_uint8                uc_chan_num;
    oal_uint8                uc_chan_idx;
    oal_uint32               ul_ret                                 = OAL_FAIL;
    oal_int8                 ac_string[OAM_PRINT_FORMAT_LENGTH];
    oal_int8                *pc_str_offset;
    mac_regclass_info_stru  *pst_rc_info;

    mac_get_regdomain_info(&pst_regdomain_info);

    OAL_SPRINTF(ac_string, sizeof(ac_string), "Country is: %s %s\n",
                pst_regdomain_info->ac_country,
                "2G(chan_num reg_tx_pwr max_tx_pwr):\n");
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_2, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_2, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_2G, uc_chan_idx);
            OAL_IO_PRINT("%d,%d,%d\r\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
            OAL_SPRINTF(pc_str_offset, 10, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }

    oam_print(ac_string);

    OAL_SPRINTF(ac_string, sizeof(ac_string), "%s", "5G(chan_num reg_tx_pwr max_tx_pwr):\n");
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT/2; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_5, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_5G, uc_chan_idx);
            OAL_SPRINTF(pc_str_offset, 12, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }
    oam_print(ac_string);

    ac_string[0] = '\0';
    for (uc_chan_idx = MAC_CHANNEL_FREQ_5_BUTT/2; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_5, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_5G, uc_chan_idx);
            OAL_SPRINTF(pc_str_offset, 12, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }
    oam_print(ac_string);
    return OAL_SUCC;
}
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_config_set_regdomain_pwr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��16��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32   dmac_config_set_regdomain_pwr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_regdomain_max_pwr_stru *pst_cfg;

    pst_cfg = (mac_cfg_regdomain_max_pwr_stru *)puc_param;

    mac_regdomain_set_max_power(pst_cfg->uc_pwr, pst_cfg->en_exceed_reg);

    return OAL_SUCC;

}
#endif


#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
OAL_STATIC oal_uint32  dmac_config_set_rate(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_non_ht_rate_stru        *pst_event_set_rate;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rate::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rate::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������� */
    pst_event_set_rate = (mac_cfg_non_ht_rate_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate = pst_event_set_rate->en_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_rate->en_protocol_mode;

    /* ʹ�ó�ǰ���룬����1Mbps */
    if (WLAN_LEGACY_11b_RESERVED1 == pst_event_set_rate->en_rate)
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = 1;
    }

    /* ����Э������ */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_rate->en_protocol_mode << 6) | pst_event_set_rate->en_rate);

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* ����ģʽ��Ƶ�㡢��������������DAC��LPF���� */
    hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_rate->en_protocol_mode, pst_event_set_rate->en_rate);
#else
#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_TX_RF == pst_hal_device_base->bit_al_tx_flag)
    {
        hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_rate->en_protocol_mode, pst_event_set_rate->en_rate);
    }
#endif
#endif

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
       hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rate::en_rate=%d,protocol=%d.",
                    pst_event_set_rate->en_rate, pst_event_set_rate->en_protocol_mode);
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_mcs(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_mcs;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;


    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_set_mcs = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = pst_event_set_mcs->uc_param;

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* ����ģʽ��Ƶ�㡢��������������DAC��LPF���� */
    hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcs->en_protocol_mode, pst_event_set_mcs->uc_param);
#else
#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_TX_RF == pst_hal_device_base->bit_al_tx_flag)
    {
        hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcs->en_protocol_mode, pst_event_set_mcs->uc_param);
    }
#endif
#endif

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_mcs->en_protocol_mode;

    /* �������ʼ�Э��ģʽ */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_mcs->en_protocol_mode << 6) | pst_event_set_mcs->uc_param);

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
        hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr mcs=%d.", pst_event_set_mcs->uc_param);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_mcsac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_mcsac;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcsac::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcsac::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������� */
    pst_event_set_mcsac = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs = pst_event_set_mcsac->uc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_mcsac->en_protocol_mode;

    /* ����Э������ */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_mcsac->en_protocol_mode << 6) | pst_event_set_mcsac->uc_param);
#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* ����ģʽ��Ƶ�㡢��������������DAC��LPF���� */
    hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcsac->en_protocol_mode, pst_event_set_mcsac->uc_param);
#else
#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_TX_RF == pst_hal_device_base->bit_al_tx_flag)
    {
        hal_set_dac_lpf_gain(pst_hal_device_base, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcsac->en_protocol_mode, pst_event_set_mcsac->uc_param);
    }
#endif
#endif

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
        hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr mcsac=%d.", pst_event_set_mcsac->uc_param);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_nss;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_nss::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_nss::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������� */
    pst_event_set_nss = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode = pst_event_set_nss->uc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_nss->en_protocol_mode;

    /* ����Э������ */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_nss->en_protocol_mode << 6) | pst_event_set_nss->uc_param);

    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr nss=%d.", pst_event_set_nss->uc_param);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_rfch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_rfch;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rfch::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rfch::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������� */
    pst_event_set_rfch = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_event_set_rfch->uc_param;

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
        hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr tx chain selection=%d.", pst_event_set_rfch->uc_param);
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_bw(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_bw;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_bw::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_bw::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

     /* �������� */
    pst_event_set_bw = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.st_rate.uc_channel_bandwidth = pst_event_set_bw->uc_param;

    pst_dmac_vap->uc_bw_flag = pst_event_set_bw->uc_param;

    /* ����ģʽ���������� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)/* Hi1102 ��������bit ��־λ��mac vap �ṹ���� */
#else
    if (OAL_SWITCH_ON == pst_hal_device_base->ul_al_tx_flag)
#endif
    {
        hal_set_tx_dscr_field(pst_hal_device_base, pst_event_set_bw->uc_param, HAL_RF_TEST_BAND_WIDTH);
    }

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_always_tx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_al_tx;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_event_set_al_tx = (mac_cfg_tx_comp_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ó���ģʽ��־ */
    mac_vap_set_al_tx_flag(pst_mac_vap, pst_event_set_al_tx->uc_param);
    mac_vap_set_al_tx_payload_flag(pst_mac_vap, pst_event_set_al_tx->en_payload_flag);
    pst_hal_device_base->ul_al_tx_flag = pst_event_set_al_tx->uc_param;
    pst_hal_device_base->bit_al_tx_flag = pst_event_set_al_tx->uc_param;

    if (OAL_SWITCH_OFF == pst_hal_device_base->ul_al_tx_flag)
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
        hal_rf_test_disable_al_tx(pst_hal_device_base);
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
OAL_STATIC oal_uint32 dmac_config_al_tx_set_addresses(
                mac_vap_stru                           *pst_vap,
                mac_ieee80211_frame_stru  *pst_hdr)
{
    oal_uint8       auc_bcst[6] = {0xff,0xff,0xff,0xff,0xff,0xff};

    /* From DS��ʶλ���� */
    mac_hdr_set_from_ds((oal_uint8 *)pst_hdr, 0);

    /* to DS��ʶλ���� */
    mac_hdr_set_to_ds((oal_uint8 *)pst_hdr, 1);

    /* Set Address1 field in the WLAN Header with BSSID */
    oal_set_mac_addr(pst_hdr->auc_address1, auc_bcst);


    /* Set Address2 field in the WLAN Header with the source address */
    oal_set_mac_addr(pst_hdr->auc_address2, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* Set Address3 field in the WLAN Header with the destination address */
    oal_set_mac_addr(pst_hdr->auc_address3, auc_bcst);

	return OAL_SUCC;
}
OAL_STATIC oal_uint32 dmac_config_al_tx_set_frame_ctrl(
                                                      mac_tx_ctl_stru                         *pst_tx_ctl,
                                                      mac_ieee80211_frame_stru  *pst_hdr)
{
    /* ����֡�����ֶ� */
    mac_hdr_set_frame_control((oal_uint8 *)pst_hdr, WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_DATA);

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = MAC_80211_FRAME_LEN;

	return OAL_SUCC;
}
OAL_STATIC oal_uint32 dmac_config_al_tx_packet_send(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    frw_event_mem_stru    *pst_event_mem;
    //oal_uint32             ul_ret = HMAC_TX_PASS;
    frw_event_stru        *pst_event;
    dmac_tx_event_stru    *pst_dtx_stru;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::FRW_EVENT_ALLOC failed.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        pst_vap->st_vap_stats.ul_tx_dropped_packets++;
#endif
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_DRX,
                        DMAC_TX_HOST_DRX,
                        OAL_SIZEOF(dmac_tx_event_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_vap->uc_chip_id,
                        pst_vap->uc_device_id,
                        pst_vap->uc_vap_id);

    pst_dtx_stru             = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dtx_stru->pst_netbuf = pst_buf;

    dmac_tx_process_data_event(pst_event_mem);

     /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;

}

OAL_STATIC oal_uint32 dmac_config_al_tx_packet(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf, oal_uint32 ul_len)
{
    mac_tx_ctl_stru                     *pst_tx_ctl;       /* SKB CB */
    mac_ieee80211_qos_htc_frame_stru    *pst_hdr;

    /* ��ʼ��CB tx rx�ֶ� , CB�ֶ���ǰ���Ѿ������㣬 �����ﲻ��Ҫ�ظ���ĳЩ�ֶθ���ֵ*/

    /* netbuff��Ҫ�����ڴ�  */
    pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)                  = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl)                       = 1;
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl)             = WLAN_DATA_BASICTYPE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctl)          = DMAC_USER_ALG_NON_PROBE;
    //MAC_GET_CB_EN_ACK_POLICY(pst_tx_ctl)             = WLAN_TX_NORMAL_ACK;
    mac_set_cb_ack_policy(pst_tx_ctl, WLAN_TX_NO_ACK);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl)           = pst_vap->uc_vap_id;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_VO);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)             = FRW_EVENT_TYPE_WLAN_DTX;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)           = (oal_uint8)pst_vap->us_multi_user_idx;
    mac_set_cb_80211_mac_head_type(pst_tx_ctl, 0); /*ָʾmacͷ������skb�У������˶����ڴ��ŵ�*/
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)    = MAC_80211_FRAME_LEN;
    MAC_GET_CB_IS_MCAST(pst_tx_ctl) = OAL_TRUE;

    pst_hdr = (mac_ieee80211_qos_htc_frame_stru *)OAL_NETBUF_HEADER(pst_buf);
    pst_hdr->bit_qc_amsdu = OAL_FALSE;

    /* �ҽ�802.11ͷ,��data_tx��Ὣ802.11ͷȫ����0 */
    dmac_config_al_tx_set_frame_ctrl(pst_tx_ctl,(mac_ieee80211_frame_stru *)pst_hdr);
    dmac_config_al_tx_set_addresses(pst_vap, (mac_ieee80211_frame_stru *)pst_hdr);
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)pst_hdr);

    /* ����frame���� */
    MAC_GET_CB_MPDU_BYTES(pst_tx_ctl) = (oal_uint16)ul_len;
    //MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = (oal_uint16)ul_len;
    return OAL_SUCC;
}

OAL_STATIC oal_netbuf_stru*  dmac_config_create_al_tx_packet(oal_uint32 ul_size,
                                                    mac_rf_payload_enum_uint8        en_payload_flag)
{
    oal_netbuf_stru         *pst_buf;
    oal_uint32               ul_loop = 0;
    oal_uint8                       *puc_data;

    //pst_buf = OAL_MEM_NETBUF_ALLOC((oal_uint16)ul_size, OAL_TRUE);/* ��Ҫ�����������ṩ��ר�Žӿ� */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(WLAN_LARGE_NETBUF_SIZE >= ul_size)
    {
        pst_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_TRUE);
    }
    else
    {
        pst_buf = OAL_MEM_MULTI_NETBUF_ALLOC((oal_uint16)ul_size);
    }
#else
    pst_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_TRUE);
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "dmac_config_create_al_tx_packet::alloc Fail");
        return OAL_PTR_NULL;
    }

    //oal_netbuf_put(pst_buf, ul_size);
    puc_data = OAL_NETBUF_DATA(pst_buf);
    switch (en_payload_flag)
    {
        case RF_PAYLOAD_ALL_ZERO:
            OAL_MEMZERO(puc_data, ul_size);
            break;
        case RF_PAYLOAD_ALL_ONE:
            oal_memset(puc_data, 0xFF, ul_size);
            break;
        case RF_PAYLOAD_RAND:
            puc_data[0] = oal_gen_random(18, 1);
            for (ul_loop = 1; ul_loop < ul_size; ul_loop++)
            {
                puc_data[ul_loop] = oal_gen_random(18, 0);
            }
            break;
        default:
        	break;
    }

    pst_buf->next = OAL_PTR_NULL;
    //pst_buf->prev = OAL_PTR_NULL;

    OAL_MEMZERO(oal_netbuf_cb(pst_buf), OAL_TX_CB_LEN);

    return pst_buf;
}
OAL_STATIC oal_uint32  dmac_config_al_tx_bcast_pkt(mac_vap_stru *pst_mac_vap, oal_uint32 ul_len)
{
    oal_netbuf_stru                *pst_netbuf;
    oal_uint32                      ul_ret;

    /* ��� */
    pst_netbuf = dmac_config_create_al_tx_packet(ul_len, (oal_uint8)pst_mac_vap->bit_payload_flag);

    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_bcast_pkt::return null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��дcb��macͷ */
    ul_ret = dmac_config_al_tx_packet(pst_mac_vap, pst_netbuf, ul_len);

    /* �������� */
    ul_ret |= dmac_config_al_tx_packet_send(pst_mac_vap, pst_netbuf);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_bcast_pkt::hmac_tx_lan_to_wlan return error %d!}\r\n", ul_ret);
    }

    return ul_ret;
}
OAL_STATIC oal_uint32  dmac_config_set_always_tx_1102(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_al_tx;
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_event_set_al_tx = (mac_cfg_tx_comp_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ó���ģʽ��־ */

    mac_vap_set_al_tx_flag(pst_mac_vap, pst_event_set_al_tx->uc_param);
    mac_vap_set_al_tx_payload_flag(pst_mac_vap, pst_event_set_al_tx->en_payload_flag);

    /* �ȹرռĴ��� */
    pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
    //hal_rf_test_disable_al_tx(pst_hal_device_base);

    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_FALSE;
        /* hal_rf_test_enable_al_tx�Ĵ�������������dmac_tx_data�����  */
        /* �˴�Ϊ�˼���51�Ŀ��أ��˴����Կ���is_not_first_run */
        if (OAL_TRUE == pst_mac_vap->bit_first_run)
        {
            return OAL_SUCC;
        }
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_TRUE);

        return dmac_config_al_tx_bcast_pkt(pst_mac_vap, pst_event_set_al_tx->ul_payload_len);

    }
    else
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
        hal_rf_test_disable_al_tx(pst_hal_device_base);
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_WLAN_FEATURE_ALWAYS_TX */

oal_uint32 g_ul_al_ampdu_num               = WLAN_AMPDU_TX_MAX_NUM; /*ampdu �����ۺϳ���*/
oal_uint32 g_ul_al_mpdu_len                = 1510; /*ָʾ����mpdu���ȣ� �ɸ���ʵ������޸�*/
//oal_uint32 g_ul_first_timestamp = 0;    /*��¼����ͳ�Ƶ�һ��ʱ���*/

/*****************************************************************************
 �� �� ��  : dmac_config_always_rx_set_hal
 ��������  : ���ó���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_always_rx_set_hal(hal_to_dmac_device_stru *pst_hal_device_base, oal_uint8 uc_switch)
{
    /* ֹͣmac phy���� */
    hal_disable_machw_phy_and_pa(pst_hal_device_base);

    if(uc_switch)
    {
        /* �ͷ������������������� */
        hal_rx_destroy_dscr_queue(pst_hal_device_base,OAL_TRUE);

        /* ��ʼ�����ս������������� */
        hal_al_rx_init_dscr_queue(pst_hal_device_base);
    }
    else
    {
        /* �ͷ����г��ս������������� */
        hal_al_rx_destroy_dscr_queue(pst_hal_device_base);

        /* ��ʼ���������������� */
        hal_rx_init_dscr_queue(pst_hal_device_base);
    }

    /* �ָ� mac phy����*/
    hal_enable_machw_phy_and_pa(pst_hal_device_base);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_always_rx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                   *pst_dmac_vap;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_rx::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_rx::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ۺ�֡�������£���ʹ����ָ������������ͬҲҪ���£���ʹ������Ч */
    pst_hal_device_base->bit_al_txrx_ampdu_num = g_ul_al_ampdu_num;

    /* ������·��������״̬û�䣬��ֱ�ӷ��� */
    if(*(oal_bool_enum_uint8 *)puc_param == pst_hal_device_base->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }

    /* ���ó���ģʽ��־ */
    pst_hal_device_base->bit_al_rx_flag = *(oal_bool_enum_uint8 *)puc_param;

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_RESERVED == pst_hal_device_base->bit_al_rx_flag)
    {
        hal_reg_write(pst_hal_device_base, WITP_PA_RX_FRAMEFILT_REG, 0x0);
    }
#endif

    /* ��RF����ʹ�ã�AMPDU���ղ���Ҫ���߼� */
    if (HAL_ALWAYS_RX_RESERVED == pst_hal_device_base->bit_al_rx_flag)
    {
        dmac_config_always_rx_set_hal(pst_hal_device_base, pst_hal_device_base->bit_al_rx_flag);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_get_thruput
 ��������  : ��ȡоƬ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_thruput(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint32                       ul_rx_octects_in_ampdu;
    oal_uint32                       ul_tx_octects_in_ampdu;
    oal_uint32                       ul_rx_normal_mdpu_succ_num;
    oal_uint32                       ul_rx_ampdu_succ_num;
    oal_uint32                       ul_tx_ppdu_succ_num;
    oal_uint32                       ul_rx_ppdu_fail_num;
    oal_uint32                       ul_tx_ppdu_fail_num;
    oal_uint32                       ul_rx_ampdu_fcs_num;
    oal_uint32                       ul_rx_delimiter_fail_num;
    oal_uint32                       ul_rx_mpdu_fcs_num;
    oal_uint32                       ul_rx_phy_err_mac_passed_num;
    oal_uint32                       ul_rx_phy_longer_err_num;
    oal_uint32                       ul_rx_phy_shorter_err_num;
    oal_uint32                       ul_timestamp;
    oal_uint8                        uc_stage;       /*0Ϊ��ʼͳ�ƽ׶Σ� 1Ϊ����ͳ�ƽ׶�*/
    oal_uint32                       ul_rx_rate;     /*��λmpbs*/
    oal_uint32                       ul_tx_rate;     /*��λmpbs*/
    oal_uint32                       ul_time_offest; /*ͳ��ʱ���, ��λms*/
    hal_to_dmac_device_stru         *pst_hal_device_base;
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_cpu_usage_stat_stru          st_cpu_stat;
    oal_uint64                       ull_alltime;
#endif
    mac_device_stru                 *pst_mac_device;
    oal_uint32                       ul_cycles = 0;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event_up;
    dmac_thruput_info_sync_stru     *pst_thruput_info_sync;
#endif

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_thruput::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_thruput::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_thruput::pst_hal_device_base null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_stage = *(oal_bool_enum_uint8 *)puc_param;

    if(0 == uc_stage)
    {
        pst_mac_device->ul_first_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    #if (!defined(_PRE_PC_LINT) && !defined(WIN32))
        enable_cycle_counter();
    #endif
    #endif

        /*����*/
        hal_set_counter_clear(pst_hal_device_base);
        pst_hal_device_base->ul_rx_normal_mdpu_succ_num = 0;
        pst_hal_device_base->ul_rx_ampdu_succ_num = 0;
        pst_hal_device_base->ul_tx_ppdu_succ_num = 0;
        pst_hal_device_base->ul_rx_ppdu_fail_num = 0;
        pst_hal_device_base->ul_tx_ppdu_fail_num = 0;
    }
    else
    {
        ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        ul_time_offest = ul_timestamp - pst_mac_device->ul_first_timestamp;

        #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        #if (!defined(_PRE_PC_LINT) && !defined(WIN32))
            disable_cycle_counter();

            ul_cycles = get_cycle_count();
        #endif
        #endif

        ul_rx_normal_mdpu_succ_num = pst_hal_device_base->ul_rx_normal_mdpu_succ_num;
        ul_rx_ampdu_succ_num = pst_hal_device_base->ul_rx_ampdu_succ_num;
        ul_tx_ppdu_succ_num = pst_hal_device_base->ul_tx_ppdu_succ_num;
        ul_rx_ppdu_fail_num = pst_hal_device_base->ul_rx_ppdu_fail_num;
        ul_tx_ppdu_fail_num = pst_hal_device_base->ul_tx_ppdu_fail_num;

        if (HAL_ALWAYS_TX_MPDU == pst_hal_device_base->bit_al_tx_flag)
        {
            ul_tx_rate = ((ul_tx_ppdu_succ_num + ul_tx_ppdu_fail_num)*g_ul_al_mpdu_len/(ul_time_offest))*8;
            ul_rx_rate = ((ul_rx_normal_mdpu_succ_num + ul_rx_ppdu_fail_num)*g_ul_al_mpdu_len/(ul_time_offest))*8;
        }
        else
        {
            hal_get_ampdu_bytes(pst_hal_device_base, &ul_tx_octects_in_ampdu, &ul_rx_octects_in_ampdu);

            ul_rx_rate = (ul_rx_octects_in_ampdu/(ul_time_offest))*8;
            ul_tx_rate = (ul_tx_octects_in_ampdu/(ul_time_offest))*8;

            OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::tx octects=%u, rx octects=%u, cycles=%u.}",
                           ul_tx_octects_in_ampdu, ul_rx_octects_in_ampdu, ul_cycles);

        }

        /*������*/
        hal_get_rx_err_count(pst_hal_device_base,
                        &ul_rx_ampdu_fcs_num,
                        &ul_rx_delimiter_fail_num,
                        &ul_rx_mpdu_fcs_num,
                        &ul_rx_phy_err_mac_passed_num,
                        &ul_rx_phy_longer_err_num,
                        &ul_rx_phy_shorter_err_num);

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{tx succ num: %u, tx fail num: %u}", ul_tx_ppdu_succ_num, ul_tx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx normal succ num: %u, rx ampdu succ num: %u, rx fail num: %u}", ul_rx_normal_mdpu_succ_num, ul_rx_ampdu_succ_num, ul_rx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{tx rate(Mbps): %u, rx rate(Mbps): %u, ul_cycles: %u,}", ul_tx_rate, ul_rx_rate, ul_cycles);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx ampdu fcs num: %u, rx delimiter fail num: %u,}", ul_rx_ampdu_fcs_num, ul_rx_delimiter_fail_num);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx mpdu fcs num: %u, rx phy err mac passed num: %u,}", ul_rx_mpdu_fcs_num, ul_rx_phy_err_mac_passed_num);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx phy longer err num: %u, rx phy shorter err num: %u,}", ul_rx_phy_longer_err_num, ul_rx_phy_shorter_err_num);

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        oal_get_cpu_stat(&st_cpu_stat);
        ull_alltime = st_cpu_stat.ull_user + st_cpu_stat.ull_nice + st_cpu_stat.ull_system + st_cpu_stat.ull_idle + st_cpu_stat.ull_iowait +
                      st_cpu_stat.ull_irq + st_cpu_stat.ull_softirq + st_cpu_stat.ull_steal + st_cpu_stat.ull_guest;
	    OAL_IO_PRINT("user=%llu, nice=%llu, system=%llu, idle=%llu, iowait=%llu, irq=%llu, softirq=%llu, steal=%llu, guest=%llu, alltime=%llu\r\n",
	                 st_cpu_stat.ull_user, st_cpu_stat.ull_nice, st_cpu_stat.ull_system, st_cpu_stat.ull_idle, st_cpu_stat.ull_iowait,
	                 st_cpu_stat.ull_irq,  st_cpu_stat.ull_softirq, st_cpu_stat.ull_steal, st_cpu_stat.ull_guest, ull_alltime);
#endif

        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::TX succ num=%d,fail num=%d;RX succ num=%d, fail num=%d}",
                       ul_tx_ppdu_succ_num, ul_tx_ppdu_fail_num, ul_rx_normal_mdpu_succ_num, ul_rx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::tx rate(Mbps)=%d, rx rate(Mbps)=%d, ul_cycles=%d}",
                       ul_tx_rate, ul_rx_rate, ul_cycles);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* ����Ҫͬ�����������¼�ͬ����hmac */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_thruput_info_sync_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_query_event_response::pst_event_memory null.}");

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
        pst_thruput_info_sync = (dmac_thruput_info_sync_stru *)pst_event_up->auc_event_data;
        pst_thruput_info_sync->ul_cycles        = ul_cycles;
        pst_thruput_info_sync->ul_sw_tx_succ_num = ul_tx_ppdu_succ_num;
        pst_thruput_info_sync->ul_sw_tx_fail_num = ul_tx_ppdu_fail_num;
        pst_thruput_info_sync->ul_sw_rx_ampdu_succ_num = ul_rx_ampdu_succ_num;
        pst_thruput_info_sync->ul_sw_rx_ppdu_fail_num = ul_rx_ppdu_fail_num;
        pst_thruput_info_sync->ul_sw_rx_mpdu_succ_num  = ul_rx_normal_mdpu_succ_num;
        pst_thruput_info_sync->ul_hw_rx_ampdu_fcs_fail_num = ul_rx_ampdu_fcs_num;
        pst_thruput_info_sync->ul_hw_rx_mpdu_fcs_fail_num = ul_rx_mpdu_fcs_num;
        dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_THRUPUT_INFO, OAL_SIZEOF(dmac_thruput_info_sync_stru), (oal_uint8 *)pst_thruput_info_sync);
        FRW_EVENT_FREE(pst_event_mem);
#endif
    }

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_freq_skew(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_PHY_PLL_DIV
    mac_cfg_freq_skew_stru *pst_freq_skew;
    mac_device_stru      *pst_device;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ж� */
    pst_freq_skew = (mac_cfg_freq_skew_stru*)puc_param;
    if (pst_freq_skew->us_idx >= WITP_RF_SUPP_NUMS)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq_skew::us_idx=%d.", pst_freq_skew->us_idx);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_hal_device_base = pst_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq_skew::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_rf_set_freq_skew(pst_device->pst_device_stru, pst_freq_skew->us_idx, pst_freq_skew->us_chn, pst_freq_skew->as_corr_data);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_adjust_ppm
 ��������  : ����PPMУ׼
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : pengdunmeng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_adjust_ppm(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_cfg_adjust_ppm_stru         *pst_adjust_ppm;
    mac_device_stru                 *pst_device;

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ж� */
    pst_adjust_ppm = (mac_cfg_adjust_ppm_stru*)puc_param;

    hal_rf_adjust_ppm(pst_device->pst_device_stru, pst_adjust_ppm->c_ppm_val, pst_mac_vap->st_channel.en_bandwidth, pst_adjust_ppm->uc_clock_freq);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_reg_info
 ��������  : ��ȡmac�Ĵ���

 �������  : puc_param:"16|32 regtype(soc/mac/phy) startaddr endaddr"
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reg_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_bool_enum_uint8   en_reg_info32 = OAL_TRUE;

    struct dmac_reg_info_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_start_addr;
        oal_uint32    ul_end_addr;

    }st_dmac_reg_info = {0};

    /* ѡ���ȡ��λ(32/16) */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /*lint -e960*/
    /* ����ԭ��"regtype(soc/mac/phy) startaddr endaddr"�����ʽ��Ĭ��32λ��ȡ�Ĵ��� */
    if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
    {
        if (0 == oal_strcmp(pc_token, "16"))
        {
            en_reg_info32 = OAL_FALSE;
        }

        /* ��ȡҪ��ȡ�ļĴ������� */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (NULL == pc_token)
        {
            return OAL_FAIL;
        }
        /* ������� */
        if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
        {
            return OAL_FAIL;
        }

    }
    /*lint +e960*/

    st_dmac_reg_info.pc_reg_type = pc_token;

    /* ��ȡ��ʼ��ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_info.ul_start_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡ��ֹ��ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_info.ul_end_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    if (OAL_TRUE == en_reg_info32)
    {
        /*lint -e960*/
        dmac_config_reg_display_test(pst_mac_vap, st_dmac_reg_info.ul_start_addr, st_dmac_reg_info.ul_end_addr);
        /*lint +e960*/
        return OAL_SUCC;
    }
    /*lint -e960*/
    dmac_config_reg_display_test16(pst_mac_vap, st_dmac_reg_info.ul_start_addr, st_dmac_reg_info.ul_end_addr);
    /*lint +e960*/
    return OAL_SUCC;
}

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))

/*****************************************************************************
 �� �� ��  : dmac_config_sdio_flowctrl
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_sdio_flowctrl(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint16            us_UsedMemForStop;
    oal_uint16            us_UsedMemForstart;

    /* ��ȡҪ��ȡ�ļĴ������� */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    us_UsedMemForStop = (oal_uint16)oal_strtol(pc_token, &pc_end, 10);

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    us_UsedMemForstart = (oal_uint16)oal_strtol(pc_token, &pc_end, 10);

    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_sdio_flowctrl::UsedMemForStop=%d, UsedMemForstart=%d.", us_UsedMemForStop, us_UsedMemForstart);

    g_usUsedMemForStop  = us_UsedMemForStop;
    g_usUsedMemForstart = us_UsedMemForstart;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_reg_write
 ��������  : д�Ĵ����ӿ�
 �������  : puc_param:"32/16(51û��16λд�Ĵ�������) regtype(soc/mac/phy) addr val"
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reg_write(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_bool_enum_uint8   en_reg_info32 = OAL_TRUE;
    struct dmac_reg_write_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_addr;
        oal_uint32    ul_val;    /* д32λ�Ĵ��� */
    }st_dmac_reg_write = {0};

    /* ѡ��д������λ(32/16) */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /*lint -e960*/
    /* ����ԭ��" regtype(soc/mac/phy) addr val"�����ʽ��Ĭ��32λ��ȡ�Ĵ��� */
    if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
    {
        if (0 == oal_strcmp(pc_token, "16"))
        {
            en_reg_info32 = OAL_FALSE;
        }

        /* ��ȡҪ��ȡ�ļĴ������� */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (NULL == pc_token)
        {
            return OAL_FAIL;
        }
        /* ������� */
        if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
        {
            return OAL_FAIL;
        }

    }
    /*lint +e960*/
    st_dmac_reg_write.pc_reg_type = pc_token;

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_write.ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡ��Ҫд���ֵ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    if (OAL_TRUE == en_reg_info32)
    {
        st_dmac_reg_write.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);
        /*lint -e960*/
        dmac_config_reg_write_test(pst_mac_vap, st_dmac_reg_write.ul_addr, st_dmac_reg_write.ul_val);
        /*lint +e960*/
        return OAL_SUCC;
    }

    st_dmac_reg_write.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /*lint -e960*/
    dmac_config_reg_write_test16(pst_mac_vap, st_dmac_reg_write.ul_addr, (oal_uint16)(st_dmac_reg_write.ul_val));
    /*lint +e960*/

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_vap_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_vap_info::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //print protection info
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_protection_mode=%d. uc_obss_non_erp_aging_cnt=%d. uc_obss_non_ht_aging_cnt=%d. bit_auto_protection=%d",
                                                                                                                pst_mac_vap->st_protection.en_protection_mode,
                                                                                                                pst_mac_vap->st_protection.uc_obss_non_erp_aging_cnt,
                                                                                                                pst_mac_vap->st_protection.uc_obss_non_ht_aging_cnt,
                                                                                                                pst_mac_vap->st_protection.bit_auto_protection);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "bit_obss_non_erp_present=%d. bit_obss_non_ht_present=%d. bit_rts_cts_protect_mode=%d. bit_lsig_txop_protect_mode=%d.",
                                                                                                                pst_mac_vap->st_protection.bit_obss_non_erp_present,
                                                                                                                pst_mac_vap->st_protection.bit_obss_non_ht_present,
                                                                                                                pst_mac_vap->st_protection.bit_rts_cts_protect_mode,
                                                                                                                pst_mac_vap->st_protection.bit_lsig_txop_protect_mode);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_sta_no_short_slot_num=%d. uc_sta_no_short_preamble_num=%d. uc_sta_non_erp_num=%d. uc_sta_non_ht_num=%d.",
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_short_slot_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_short_preamble_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_erp_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_ht_num);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_sta_non_gf_num=%d. uc_sta_20M_only_num=%d. uc_sta_no_40dsss_cck_num=%d. uc_sta_no_lsig_txop_num=%d. ",
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_gf_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_20M_only_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_40dsss_cck_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_lsig_txop_num);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_machw_wmm
 ��������  : ����Ӳ��wmm����
 �������  : pst_hal_vap: hal vap
             pst_mac_vap: mac vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_machw_wmm(hal_to_dmac_vap_stru *pst_hal_vap, mac_vap_stru *pst_mac_vap)
{
    wlan_wme_ac_type_enum_uint8     en_ac_type;
    /* ����AIFSN */
    hal_vap_set_machw_aifsn_all_ac(pst_hal_vap,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN);

    /* cwmin cwmax */
    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_hal_vap,
                                 (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmin,
                                  en_ac_type);
    }

#if 0
    hal_vap_set_machw_cw_bk(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_be(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vi(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vo(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin);
#endif
    /* txop */
    hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);


}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : dmac_add_p2p_cl_vap
 ��������  : ���p2p cl vap���¼����Ⱥ���
 �������  : pst_mac_vap : ҵ��vap������������VAP
             puc_param   : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��25��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : zhongwen
    �޸�����   : ��Ӻ�������

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_add_p2p_cl_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_device;
    mac_cfg_add_vap_param_stru     *pst_param;
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_device_stru        *pst_hal_device;
    hal_to_dmac_vap_stru           *pst_hal_vap = OAL_PTR_NULL;
    oal_uint8                       uc_vap_idx;
    mac_vap_stru                   *pst_mac_cfg_vap;

    pst_param = (mac_cfg_add_vap_param_stru *)puc_param;

    /* ��ȡdevice */
    pst_mac_cfg_vap = (mac_vap_stru*)mac_res_get_mac_vap(pst_param->uc_cfg_vap_indx);
    if (OAL_PTR_NULL == pst_mac_cfg_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_cfg_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_cfg_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����P2P CL ��P2P DEV ����VAP����P2P CL ����Ҫ�����ڴ棬Ҳ����Ҫ��ʼ��dmac vap �ṹ */
    uc_vap_idx     = pst_device->st_p2p_info.uc_p2p0_vap_idx;/* uc_p2p0_vap_idx�ڴ���p2p0 ʱ��ʼ�� */
    pst_dmac_vap   = (dmac_vap_stru *)mac_res_get_dmac_vap(uc_vap_idx);

    /* ���hmac��dmac����vap idx�Ƿ�һ�� */
    if (uc_vap_idx != pst_param->uc_vap_id)
    {
        OAM_ERROR_LOG2(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::HMAC and DMAC vap indx not same!.saved_vap_id[%d], new_vap_id[%d]}",
                        uc_vap_idx, pst_param->uc_vap_id);
        return OAL_ERR_CODE_ADD_VAP_INDX_UNSYNC;
    }


    /* ����hal_add_vap */
    pst_hal_device = pst_device->pst_device_stru;

#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* �����Proxy STA������hal ����ΪProxy STAģʽ�����ģʽֻ��hal��ʹ�� */
            hal_add_vap(pst_hal_device, WLAN_VAP_MODE_PROXYSTA, uc_vap_idx, &pst_hal_vap);
        }
        else
        {
            hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
        }
    }
    else
    {
        hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* ͬһ��vap ���ܹ��ҽӶ��hal_vap */
    /* ����MAC Ӳ������P2P ��ؼĴ��������ơ�
    *  GO ֻ�ܴ�����hal_vap_id = 1,
    *  CL ֻ�ܴ�����hal_vap_id = 5,
    *  ��Ҫ��P2P ģʽ����hal_add_vap ������  */
    /*
    *  |7      4|3      0|
    *  |p2p_mode|vap_mode|
    */
    OAM_INFO_LOG2(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "dmac_add_p2p_cl_vap:vap_mode %02x, p2p_mode %02x\r\n",
                  pst_param->en_vap_mode,
                  pst_param->en_p2p_mode);

    hal_add_vap(pst_hal_device, ((pst_param->en_vap_mode) | ((oal_uint8)(pst_param->en_p2p_mode << 4))),
                uc_vap_idx, &pst_hal_vap);
#else
    /* ͬһ��vap ���ܹ��ҽӶ��hal_vap */
    hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
#endif

    if (OAL_PTR_NULL == pst_hal_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_hal_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->pst_hal_vap = pst_hal_vap;

    /* ���浽dmac vap�ṹ���У������ȡ */
    pst_dmac_vap->pst_hal_device = pst_hal_device;

    //pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_hal_vap->uc_vap_id;


    /* ����RTS���Ͳ��� */
    //hal_vap_set_machw_prot_params(pst_dmac_vap->pst_hal_vap, &(pst_dmac_vap->st_tx_alg.st_rate), &(pst_dmac_vap->st_tx_alg.ast_per_rate[0]));


    /* P2P ����MAC ��ַ */
    hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);


    /* ����Ӳ��WMM���� */
    dmac_config_set_machw_wmm(pst_dmac_vap->pst_hal_vap, pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* device��sta������1 */
    if (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (1 == pst_device->st_cap_flag.bit_proxysta)
        {
            if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta) &&
                (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
            {
                pst_device->uc_proxysta_num++;
            }
        }
#endif
        /* ��ʼ��uc_assoc_vap_idΪ���ֵ����apδ���� */
        mac_vap_set_assoc_id(pst_mac_vap, 0xff);
    }
    mac_vap_set_p2p_mode(&pst_dmac_vap->st_vap_base_info, pst_param->en_p2p_mode);
    mac_inc_p2p_num(&pst_dmac_vap->st_vap_base_info);


#endif
    /* ��ʼ��ҵ��VAP������AP��STA��WDSģʽ */
    dmac_alg_create_vap_notify(pst_dmac_vap);

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* ��ʼ��P2P CLIENT ����״̬�� */
    dmac_pm_sta_attach(pst_dmac_vap);
#endif
    /* ���hmac��dmac����muti user idx�Ƿ�һ�� */
    if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::HMAC and DMAC muti user indx not same!.}");
        return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
    }
#if 0
    /* ��dmac ��mac_vap ��uc_p2p0_hal_vap_id/uc_p2p_gocl_hal_vap_id ͬ����hmac ��mac_vap �ṹ�� */
    /* ����Ҫͬ�����������¼�ͬ����hmac */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_add_vap_sync_data_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_event_memory null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_add_vap_sync_data = (mac_add_vap_sync_data_stru *)pst_event_up->auc_event_data;
    //pst_mac_add_vap_sync_data->uc_p2p0_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    //pst_mac_add_vap_sync_data->uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id;
    //dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_ADD_VAP, OAL_SIZEOF(mac_add_vap_sync_data_stru), (oal_uint8 *)pst_mac_add_vap_sync_data);
    FRW_EVENT_FREE(pst_event_mem);
#endif
    /*��ʼ��p2p���ܲ���*/
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_add_p2p_cl_vap::add vap [%d] sucess.}", uc_vap_idx);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_del_p2p_cl_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_device_stru        *pst_hal_device;
    pst_dmac_vap   = (dmac_vap_stru *)pst_mac_vap;
    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* ֹͣP2P ���ܼĴ��� */
    hal_vap_set_noa(pst_dmac_vap->pst_hal_vap, 0, 0, 0, 0);
    hal_vap_set_ops(pst_dmac_vap->pst_hal_vap, 0, 0);
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* ����״̬��ɾ��*/
    dmac_pm_sta_detach(pst_dmac_vap);
#endif
    /* �����p2p0,ɾ��p2p0_hal_vap */

    hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_hal_vap->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_P2P
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_dec_p2p_num(pst_mac_vap);
#endif
#endif

    /* ɾ��p2p cl ����Ҫ��dmac vap �ṹ��hal_vap ָ��ָ��p2p0_hal_vap,�Ա�p2p0 �������� */
    pst_dmac_vap->pst_hal_vap    = pst_dmac_vap->pst_p2p0_hal_vap;
    mac_vap_set_p2p_mode(&pst_dmac_vap->st_vap_base_info, WLAN_P2P_DEV_MODE);
	//pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    oal_memcopy(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    /* ɾ�����㷨��صĽӿ� */
    dmac_alg_delete_vap_notify(pst_dmac_vap);


    if (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_del_p2p_cl_vap::config vap should not be here.}");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

#endif
/*****************************************************************************
 �� �� ��  : dmac_config_add_vap
 ��������  : ���vap���¼����Ⱥ���
 �������  : pst_mac_vap : ҵ��vap������������VAP
             puc_param   : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��25��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : zhangheng
    �޸�����   : ��Ӻ�������

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_add_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_device;
    mac_cfg_add_vap_param_stru     *pst_param;
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_device_stru        *pst_hal_device;
    hal_to_dmac_vap_stru           *pst_hal_vap = OAL_PTR_NULL;
    oal_uint32                      ul_ret;
    oal_uint8                       uc_vap_idx;
    mac_vap_stru                   *pst_mac_cfg_vap;

    pst_param = (mac_cfg_add_vap_param_stru *)puc_param;

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_CL_MODE == pst_param->en_p2p_mode)
    {
        return dmac_add_p2p_cl_vap(pst_mac_vap, uc_len, puc_param);
    }
#endif
    /* ��ȡdevice */
    pst_mac_cfg_vap = (mac_vap_stru*)mac_res_get_mac_vap(pst_param->uc_cfg_vap_indx);
    if (OAL_PTR_NULL == pst_mac_cfg_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_cfg_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_cfg_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_vap_idx = pst_param->uc_vap_id;
    /* ����dmac vap�ڴ�ռ� */
    ul_ret = mac_res_alloc_dmac_vap(uc_vap_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::mac_res_alloc_dmac_vap error.}");
        return ul_ret;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(uc_vap_idx);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = dmac_vap_init(pst_dmac_vap,
                           pst_device->uc_chip_id,
                           pst_device->uc_device_id,
                           uc_vap_idx,
                           pst_param->en_vap_mode);
    if (OAL_SUCC != ul_ret)
    {
        if (OAL_PTR_NULL != pst_dmac_vap->st_vap_base_info.pst_mib_info)
        {
            OAL_MEM_FREE(pst_dmac_vap->st_vap_base_info.pst_mib_info, OAL_TRUE);
            pst_dmac_vap->st_vap_base_info.pst_mib_info = OAL_PTR_NULL;
        }
        /* �ͷ���Դ�� */
        mac_res_free_mac_vap(uc_vap_idx);
        return ul_ret;
    }

    /* ����hal_add_vap */
    pst_hal_device = pst_device->pst_device_stru;

#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_config_add_vap::mac_res_get_dev fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* �����Proxy STA������hal ����ΪProxy STAģʽ�����ģʽֻ��hal��ʹ�� */
            hal_add_vap(pst_hal_device, WLAN_VAP_MODE_PROXYSTA, uc_vap_idx, &pst_hal_vap);
        }
        else
        {
            hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
        }
    }
    else
    {
        hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* ͬһ��vap ���ܹ��ҽӶ��hal_vap */
    /* ����MAC Ӳ������P2P ��ؼĴ��������ơ�
    *  GO ֻ�ܴ�����hal_vap_id = 1,
    *  CL ֻ�ܴ�����hal_vap_id = 5,
    *  ��Ҫ��P2P ģʽ����hal_add_vap ������  */
    /*
    *  |7      4|3      0|
    *  |p2p_mode|vap_mode|
    */
    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap:vap_mode %02x, p2p_mode %02x\r\n}",
                    pst_param->en_vap_mode,
                    pst_param->en_p2p_mode);

    /* ͬһ��vap ���ܹ��ҽӶ��hal_vap */
    hal_add_vap(pst_hal_device, (pst_param->en_vap_mode) | (oal_uint8)(pst_param->en_p2p_mode << 4) ,
                uc_vap_idx, &pst_hal_vap);
#else
    /* ͬһ��vap ���ܹ��ҽӶ��hal_vap */
    hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
#endif

    if (OAL_PTR_NULL == pst_hal_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_event_add_vap::add hal_vap failed. pst_hal_vap null.}");

        if (OAL_PTR_NULL != pst_dmac_vap->st_vap_base_info.pst_mib_info)
        {
            OAL_MEM_FREE(pst_dmac_vap->st_vap_base_info.pst_mib_info, OAL_TRUE);
            pst_dmac_vap->st_vap_base_info.pst_mib_info = OAL_PTR_NULL;
        }

        /* �ͷ���Դ�� */
        mac_res_free_mac_vap(uc_vap_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* �ֱ��ʼ��P2P CL ��P2P DEV */
    if (WLAN_P2P_DEV_MODE == pst_param->en_p2p_mode)
    {
        pst_dmac_vap->pst_p2p0_hal_vap = pst_hal_vap;
        pst_device->st_p2p_info.uc_p2p0_vap_idx = pst_mac_vap->uc_vap_id;
    }
#endif /* _PRE_WLAN_FEATURE_P2P */
    pst_dmac_vap->pst_hal_vap = pst_hal_vap;

    /* ���浽dmac vap�ṹ���У������ȡ */
    pst_dmac_vap->pst_hal_device = pst_hal_device;
#if 0
#ifdef _PRE_WLAN_FEATURE_P2P
    /* ����mac vap �ṹ���� uc_p2p0_hal_vap_id �� uc_p2p_gocl_hal_vap_id ��Ӧӳ���ϵ */
    /* ��dmac ��mac_vap ��uc_p2p0_hal_vap_id/uc_p2p_gocl_hal_vap_id ͬ����hmac ��mac_vap �ṹ�� */
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
        /*  */
        pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id = pst_hal_vap->uc_vap_id;
    }
    pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_hal_vap->uc_vap_id;
#endif
#endif
    /* ����RTS���Ͳ��� */
    //hal_vap_set_machw_prot_params(pst_dmac_vap->pst_hal_vap, &(pst_dmac_vap->st_tx_alg.st_rate), &(pst_dmac_vap->st_tx_alg.ast_per_rate[0]));

#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta) && (OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta))
        {
            /* ��hal vap id(16~31) ��ֵ������Ϊ user id */
            pst_mac_vap->st_vap_proxysta.uc_lut_idx = pst_hal_vap->uc_vap_id;
        }
        else
        {
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, mac_mib_get_StationID(pst_mac_vap));
        }
    }
    else
    {
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* P2P ����MAC ��ַ */
    if ((WLAN_P2P_DEV_MODE == pst_param->en_p2p_mode) && (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode))
    {
        /* ����p2p0 MAC ��ַ */
        hal_vap_set_macaddr(pst_dmac_vap->pst_p2p0_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
    }
    else
    {
        /* ��������vap ��mac ��ַ */
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }
#else
    /* ����MAC��ַ */
    hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
#endif

    /* ����Ӳ��WMM���� */
    dmac_config_set_machw_wmm(pst_dmac_vap->pst_hal_vap, pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_set_vap_id(pst_device, &(pst_dmac_vap->st_vap_base_info),uc_vap_idx, pst_param->en_vap_mode, pst_param->en_p2p_mode, OAL_TRUE);

    /* ��ʼ��STA AID Ϊ 0 */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        mac_vap_set_aid(pst_mac_vap, 0);
    }
#endif

    /* ��ʼ��linkloss��⹤�� */
    dmac_vap_linkloss_init(pst_dmac_vap);

#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ��offload����£��ò�����HMAC�Ѿ������� */
    pst_device->auc_vap_id[pst_device->uc_vap_num++] = uc_vap_idx;

    /* device��sta������1 */
    if (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode)
    {
        pst_device->uc_sta_num++;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (1 == pst_device->st_cap_flag.bit_proxysta)
        {
            if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta) &&
                (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
            {
                pst_device->uc_proxysta_num++;
            }
        }
#endif
        /* ��ʼ��uc_assoc_vap_idΪ���ֵ����apδ���� */
        mac_vap_set_assoc_id(pst_mac_vap, 0xff);
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    mac_vap_set_p2p_mode(&pst_dmac_vap->st_vap_base_info, pst_param->en_p2p_mode);
    mac_inc_p2p_num(&pst_dmac_vap->st_vap_base_info);

    if (IS_P2P_GO(&(pst_dmac_vap->st_vap_base_info)))
    {
        for (uc_vap_tmp_idx = 0; uc_vap_tmp_idx < pst_device->uc_vap_num; uc_vap_tmp_idx++)
        {
            pst_tmp_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_tmp_idx]);
            if (OAL_PTR_NULL == pst_tmp_vap)
            {
                OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_config_add_vap::pst_mac_vap null,vap_idx=%d.}",
                               pst_device->auc_vap_id[uc_vap_tmp_idx]);
                continue;
            }

            if ((MAC_VAP_STATE_UP == pst_tmp_vap->en_vap_state) && (pst_tmp_vap != pst_mac_vap))
            {
                pst_dmac_vap->st_vap_base_info.st_channel.en_band        = pst_tmp_vap->st_channel.en_band;
                pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth   = pst_tmp_vap->st_channel.en_bandwidth;
                pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number = pst_tmp_vap->st_channel.uc_chan_number;
                pst_dmac_vap->st_vap_base_info.st_channel.uc_idx         = pst_tmp_vap->st_channel.uc_idx;
                break;
            }
        }
    }
#endif
#endif

#endif//����mac�ṹ

    /* ��ʼ��ҵ��VAP������AP��STA��WDSģʽ */
    switch(pst_param->en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            /* ִ�����Գ�ʼ��vap�ĺ��� */
            /* ִ���㷨���VAP��ʼ���ӿ� */
            dmac_alg_create_vap_notify(pst_dmac_vap);
        #ifdef _PRE_WLAN_FEATURE_UAPSD
            pst_dmac_vap->uc_uapsd_max_depth = DMAC_UAPSD_QDEPTH_DEFAULT;
            mac_vap_set_uapsd_en(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
        #endif

        #ifdef  _PRE_WLAN_FEATURE_PM
            if(OAL_TRUE == pst_device->en_pm_enable)
            {
                dmac_pm_ap_attach(pst_dmac_vap);
            }
        #endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            //DKY ���1102 AP ע�ᵽƽ̨
            if (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))
            {
                hal_pm_wlan_servid_register(pst_dmac_vap->pst_hal_vap, &ul_ret);

                if (OAL_SUCC != ul_ret)
                {
                    OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                           "{dmac_pm_sta_attach:hal_pm_wlan_servid_register hal vap:[%d]fail",pst_dmac_vap->pst_hal_vap->uc_vap_id);

                }
                //PM_WLAN_SwitchToState(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_AP_WORK_STS);
                PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);
            }
#endif
            break;

        case WLAN_VAP_MODE_BSS_STA:
            /* ִ�����Գ�ʼ��vap�ĺ��� */
            /* ִ���㷨���VAP��ʼ���ӿ� */
            if(IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info))
            {
                dmac_alg_create_vap_notify(pst_dmac_vap);
#ifdef  _PRE_WLAN_FEATURE_STA_PM    //�Ƿ���Ҫ���������ap(liuzhengqi)
                /* P2P DEVICE �� P2P client ����vap �ṹ�����P2P DEVICE ��ע�����״̬�� */
                dmac_pm_sta_attach(pst_dmac_vap);
#endif
            }
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

            // p2p device ע��
            if (IS_P2P_DEV(&pst_dmac_vap->st_vap_base_info))
            {
                hal_pm_wlan_servid_register(pst_dmac_vap->pst_p2p0_hal_vap, &ul_ret);

                if (OAL_SUCC != ul_ret)
                {
                    OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                           "{dmac_pm_sta_attach:hal_pm_wlan_servid_register hal vap:[%d]fail",pst_dmac_vap->pst_p2p0_hal_vap->uc_vap_id);

                }

                /* OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                        "{dmac_config_add_vap:hal_vap_id[%d], service_id[%d]",
                        pst_dmac_vap->pst_p2p0_hal_vap->uc_vap_id, pst_dmac_vap->pst_p2p0_hal_vap->uc_service_id); */


            }
#endif
#endif
            break;

        case WLAN_VAP_MODE_WDS:

            break;

        default:

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_vap_init::invalid vap mode[%d].", pst_param->en_vap_mode);
            return OAL_ERR_CODE_INVALID_CONFIG;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
            && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* Proxysta �������鲥�û�*/
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap:: proxysta don't add multicast user.}");
        }
        else
        {
            /* ���봴��dmac�鲥�û� */
            dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
            mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

            /* ���hmac��dmac����muti user idx�Ƿ�һ�� */
            if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
            {
                OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
                return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
            }
        }
    }
    else
    {
        /* ���봴��dmac�鲥�û� */
        dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
        mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

        /* ���hmac��dmac����muti user idx�Ƿ�һ�� */
        if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
        {
            OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
            return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
        }
    }
#else
    /* ���봴��dmac�鲥�û� */
    dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
    mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

    /* ���hmac��dmac����muti user idx�Ƿ�һ�� */
    if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
        return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
    }
#endif

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

    pst_dmac_vap->ul_user_pmf_status = 0;
#endif /* #if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP) */
#if 0
#ifdef _PRE_WLAN_FEATURE_P2P
    /* ����Ǵ���P2P_DEV,��Ҫ����device ��mac_device �ṹ����p2p0_vap_id ��Ա����ֵ */
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
		/* ��ʼ��p2p0 ʱ����Ҫ���´���p2p0_vap ��vap_id ��ֵ��device�ж�Ӧ��Ա */
        pst_device->st_p2p_info.uc_p2p0_vap_idx = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    }

    /* ��dmac ��mac_vap ��uc_p2p0_hal_vap_id/uc_p2p_gocl_hal_vap_id ͬ����hmac ��mac_vap �ṹ�� */
    /* ����Ҫͬ�����������¼�ͬ����hmac */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_add_vap_sync_data_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_query_event_response::pst_event_memory null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_add_vap_sync_data = (mac_add_vap_sync_data_stru *)pst_event_up->auc_event_data;
    pst_mac_add_vap_sync_data->uc_p2p0_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    pst_mac_add_vap_sync_data->uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id;
    dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_ADD_VAP, OAL_SIZEOF(mac_add_vap_sync_data_stru), (oal_uint8 *)pst_mac_add_vap_sync_data);
    FRW_EVENT_FREE(pst_event_mem);

    /*GO ��ʼ��p2p���ܲ���*/
    if (WLAN_P2P_GO_MODE == en_p2p_mode)
    {
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }

#endif
#endif

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap succ. mode[%d] state[%d].}",
                             pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_beacon_chain_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8         uc_value;
    dmac_vap_stru    *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_beacon_chain_switch::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_value = *((oal_uint8 *)puc_param);

    /* ����beacon֡�ر�/����˫·�������ͣ�1Ϊ����,0Ϊ�ر� */
    pst_dmac_vap->en_beacon_chain_active = uc_value;

    return OAL_SUCC;
}
#if 0
OAL_STATIC oal_uint32  dmac_config_tdls_prohibited(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);

    /* ����tdls prohibited,1Ϊ������ֹ,0Ϊ�رս�ֹ */
    mac_vap_set_tdls_prohibited(pst_mac_vap, uc_value);
#endif
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_tdls_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);

    mac_vap_set_tdls_channel_switch_prohibited(pst_mac_vap, uc_value);

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_tdls_channel_switch_prohibited succ!");
#endif
    return OAL_SUCC;
}
#endif

OAL_STATIC oal_uint32  dmac_config_hide_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);
    mac_vap_set_hide_ssid(pst_mac_vap, uc_value);
    OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_config_hide_ssid::mac_vap_set_hide_ssid [%d].}", uc_value);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "dmac_config_hide_ssid[%d] succ!", uc_value);
#endif
    return OAL_SUCC;
}


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)


OAL_STATIC oal_uint32 dmac_config_offload_start_vap(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_cfg_start_vap_param_stru *pst_start_vap_param;

    pst_start_vap_param = (mac_cfg_start_vap_param_stru *)puc_param;

    pst_mac_vap->st_channel.en_band = pst_start_vap_param->uc_band;
    pst_mac_vap->st_channel.en_bandwidth = pst_start_vap_param->uc_bandwidth;
    mac_vap_init_by_protocol(pst_mac_vap, pst_start_vap_param->uc_protocol);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* ����bssid */
        mac_vap_set_bssid(pst_mac_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /*��vap״̬�ı���Ϣ�ϱ�*/
        mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_UP);

        pst_mac_vap->en_vap_state = MAC_VAP_STATE_UP;
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {

#ifdef _PRE_WLAN_FEATURE_P2P
        /* P2P0 ��P2P-P2P0 ��VAP �ṹ��P2P CL UPʱ�򣬲���Ҫ����vap ״̬ */
        if (WLAN_P2P_CL_MODE != pst_start_vap_param->en_p2p_mode)
#endif
        {
        #ifdef _PRE_WLAN_FEATURE_ROAM
            if (MAC_VAP_STATE_ROAMING != pst_mac_vap->en_vap_state)
        #endif //_PRE_WLAN_FEATURE_ROAM
            {
                mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_STA_FAKE_UP);
                pst_mac_vap->en_vap_state = MAC_VAP_STATE_STA_FAKE_UP;
            }
        }
    }

    /* ��ʼ�����ʼ� */
    mac_vap_init_rates(pst_mac_vap);
    return OAL_SUCC;
}

#endif


OAL_STATIC oal_uint32  dmac_config_del_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap = OAL_PTR_NULL;
    hal_to_dmac_device_stru        *pst_hal_device;
    oal_uint8                       uc_vap_id;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_cfg_del_vap_param_stru     *pst_del_vap_param;
    wlan_p2p_mode_enum_uint8        en_p2p_mode = WLAN_LEGACY_VAP_MODE;
#endif

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap::del vap. mode[%d] state[%d].}",
                      pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    pst_dmac_vap   = (dmac_vap_stru *)pst_mac_vap;
    pst_hal_device = pst_dmac_vap->pst_hal_device;
    uc_vap_id      = pst_dmac_vap->st_vap_base_info.uc_vap_id;

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    pst_dmac_vap->ul_user_pmf_status = 0;
#endif /* #if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP) */

#ifdef _PRE_WLAN_FEATURE_P2P
    /* ��ƽ̨ȥע����� */
    if (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                            "{dmac_config_del_vap:hal_vap_id[%d], service_id[%d]",
                            pst_dmac_vap->pst_hal_vap->uc_vap_id, pst_dmac_vap->pst_hal_vap->uc_service_id);

        /* service id ȥע�� */
        hal_pm_wlan_servid_unregister(pst_dmac_vap->pst_hal_vap);
    }

    pst_del_vap_param = (mac_cfg_del_vap_param_stru *)puc_param;
    en_p2p_mode       = pst_del_vap_param->en_p2p_mode;
    if (WLAN_P2P_CL_MODE == en_p2p_mode)
    {
        return dmac_del_p2p_cl_vap(pst_mac_vap, uc_len, puc_param);
    }
    if (WLAN_P2P_GO_MODE == en_p2p_mode)
    {
        /* ֹͣP2P ���ܼĴ��� */
        hal_vap_set_noa(pst_dmac_vap->pst_hal_vap, 0, 0, 0, 0);
        hal_vap_set_ops(pst_dmac_vap->pst_hal_vap, 0, 0);
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }
    /* �����p2p0,ɾ��p2p0_hal_vap */
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
        hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_p2p0_hal_vap->uc_vap_id);
        pst_dmac_vap->pst_p2p0_hal_vap    = OAL_PTR_NULL;
    }
    else
#endif
    {
        /* STA����״̬��ɾ��*/
#ifdef _PRE_WLAN_FEATURE_STA_PM
        if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            dmac_pm_sta_detach(pst_dmac_vap);
        }
#endif
        /* ֱ�ӵ���hal_del_vap */
        hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_hal_vap->uc_vap_id);
		/* ɾ�����㷨��صĽӿ� */
        dmac_alg_delete_vap_notify(pst_dmac_vap);
    }
    pst_dmac_vap->pst_hal_device = OAL_PTR_NULL;
    pst_dmac_vap->pst_hal_vap    = OAL_PTR_NULL;

    /* ����״̬��ɾ��*/
    #ifdef _PRE_WLAN_FEATURE_PM
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_pm_ap_deattach(pst_dmac_vap);
    }
    #endif

    if (WLAN_VAP_MODE_CONFIG != pst_mac_vap->en_vap_mode)
    {
        /* ɾ��DMAC�鲥�û� */
        dmac_user_del_multi_user(pst_mac_vap, pst_mac_vap->us_multi_user_idx);
    }
    else
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap::config vap should not be here.}");
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    if (OAL_PTR_NULL != pst_dmac_vap->pst_ip_addr_info)
    {
        OAL_MEM_FREE(pst_dmac_vap->pst_ip_addr_info, OAL_TRUE);
        pst_dmac_vap->pst_ip_addr_info = OAL_PTR_NULL;
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_vap_exit(pst_mac_vap);
#endif

    /* �ͷ�tim_bitmap */
    if (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap)
    {
        OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
        pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_dmac_vap)
    {
        mac_res_free_mac_vap(uc_vap_id);
        OAM_WARNING_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap:: del vap[%d] success, multe user idx[%d].}", uc_vap_id, pst_mac_vap->us_multi_user_idx);
    }

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_start_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    oal_uint32                    ul_ret;
    wlan_protocol_enum_uint8      en_protocol;
    hal_to_dmac_device_stru      *pst_hal_device;
    mac_cfg_start_vap_param_stru *pst_start_vap_param;

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::start vap. mode[%d] state[%d].}",
                             pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    pst_start_vap_param = (mac_cfg_start_vap_param_stru *)puc_param;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_ret = dmac_config_offload_start_vap(pst_mac_vap, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::dmac_config_offload_start_vap failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif
    en_protocol    = pst_mac_vap->en_protocol;
    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* ����MAC EIFS_TIME �Ĵ��� */
    hal_config_eifs_time(pst_hal_device, en_protocol);

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P0 ��P2P-P2P0 ��VAP �ṹ��P2P CL UPʱ�򣬲���Ҫ����vap ״̬ */
    if (WLAN_P2P_DEV_MODE == pst_start_vap_param->en_p2p_mode)
    {
        /* ʹ��PA_CONTROL��vap_controlλ: bit0~3��ӦAP0~3 bit4��Ӧsta */
        hal_vap_set_opmode(pst_dmac_vap->pst_p2p0_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }
    else
#endif
    {
        /* ʹ��PA_CONTROL��vap_controlλ: bit0~3��ӦAP0~3 bit4��Ӧsta */
        hal_vap_set_opmode(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }

    /* ��ʼ������������֡��������֡�ķ��Ͳ��� */
    dmac_vap_init_tx_frame_params(pst_dmac_vap, pst_start_vap_param->en_mgmt_rate_init_flag);

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    /* ��ʼ��Ĭ�ϲ���������ض�Э��Ĺ̶��������� */
    pst_dmac_vap->un_mode_valid.uc_mode_param_valid = 0;
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_vht, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_ht, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_11ag, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_11b, OAL_SIZEOF(hal_tx_txop_alg_stru));
#endif

    /* ��ʼ����������֡�ķ��Ͳ��� */
    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* ����beacon֡ */

        /* �����Ż�����ͬƵ���µ�������һ�� */
        if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
        {
            mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
            mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_FALSE);
        }
        else
        {
            mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
            mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_TRUE);
        }

        ul_ret = dmac_beacon_alloc(pst_dmac_vap);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::dmac_beacon_alloc failed[%d].}", ul_ret);
            return ul_ret;
        }
        dmac_alg_vap_up_notify(pst_mac_vap);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_TXOPPS
        /* ��Ϊsta����Ҫ����txop ps������ʼ��mac txop psʹ�ܼĴ��� */
        dmac_txopps_init_machw_sta(pst_dmac_vap);
    #endif
    }
    else
    {

    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_vap_up_handle(pst_mac_vap);
#endif

    /* ״̬�ϱ�BT: �ŵ�������Ƶ�ʵ�*/
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                     "{dmac_config_start_vap::start vap success.channel state: band->%d, channel->%d, bandwidth->%d, p2p mode[%d]",
                     pst_mac_vap->st_channel.en_band,
                     pst_mac_vap->st_channel.uc_chan_number,
                     pst_mac_vap->st_channel.en_bandwidth,
                     pst_mac_vap->en_p2p_mode);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_down_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /* ���PA_CONTROL��vap_controlλ: bit0~3��ӦAP0~3 bit4��Ӧsta */
    hal_vap_clr_opmode(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* �ͷ�beacon֡ */
        dmac_beacon_free(pst_dmac_vap);
#ifdef _PRE_WLAN_FEATURE_DBAC
        dmac_alg_vap_down_notify(pst_mac_vap);
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
        hal_enable_radar_det(pst_dmac_vap->pst_hal_device, 0);
#endif
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        /* �ر�sta tsf��ʱ�� */
        hal_disable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
    }
    else
    {

    }

    /* ֪ͨɨ������ */
    dmac_mgmt_scan_vap_down(pst_mac_vap);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_CL_MODE == mac_get_p2p_mode(pst_mac_vap))
    {
    	mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_STA_SCAN_COMP;

    }
    else
#endif
    {
    	mac_vap_state_change_to_sdt(pst_mac_vap, MAC_VAP_STATE_INIT);
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_INIT;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_vap_down_handle(pst_mac_vap);
#endif

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::down vap succ.vap mode[%d] state[%d].}",
                      pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    return OAL_SUCC;
}


#ifdef _PRE_WLAN_FEATURE_PM
OAL_STATIC oal_uint32  dmac_config_wifi_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    oal_int32                    l_value;
    dmac_vap_stru               *pst_dmac_vap;
    oal_uint16                   us_type;
    mac_device_stru             *pst_mac_dev;
    oal_uint8                    uc_state_to;

    l_value = *((oal_int32 *)puc_param);
    if(1 == l_value)
    {
        us_type = AP_PWR_EVENT_WIFI_ENABLE;
    }
    else
    {
        us_type = AP_PWR_EVENT_WIFI_DISABLE;
    }

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if(pst_mac_dev->uc_cfg_vap_id == pst_mac_vap->uc_vap_id)
    {
        /*cfg vap,ֱ������device*/
        if (AP_PWR_EVENT_WIFI_ENABLE == us_type)
        {
            uc_state_to = DEV_PWR_STATE_WORK;
        }
        else
        {
            uc_state_to = DEV_PWR_STATE_DEEP_SLEEP;
        }
        mac_pm_set_hal_state(pst_mac_dev,uc_state_to);
    }
    else
    {
        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
        /*ҵ��VAP����PM�����¼�*/
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

            dmac_pm_post_event(pst_dmac_vap,us_type,0,OAL_PTR_NULL);
        }
    }
    return OAL_SUCC;

}



OAL_STATIC oal_uint32  dmac_config_pm_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;
    mac_pm_arbiter_stru         *pst_pm_arbiter;
    mac_pm_handler_stru         *pst_pm_handler;
    mac_fsm_stru                *pst_pm_fsm;
    oal_uint32                   ul_loop;
    oal_uint8                    uc_vap_idx;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_info::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*device��arbiter����Ϣ*/
    pst_pm_arbiter = pst_device->pst_pm_arbiter;
    if(OAL_PTR_NULL == pst_pm_arbiter)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "--------------------------Device %d PM info begin------------------------\n",pst_device->uc_device_id);
    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "Requestor num = %d,id_bitmap = 0x%x\n",pst_pm_arbiter->uc_requestor_num,pst_pm_arbiter->ul_id_bitmap);
    for(ul_loop=0;ul_loop<pst_pm_arbiter->uc_requestor_num;ul_loop++)
    {
        if(0 == ul_loop%4)
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");
        }
        OAL_IO_PRINT("Requestor id %d:%s ,",ul_loop,pst_pm_arbiter->requestor[ul_loop].auc_id_name);

    }
    /*state bitmap*/
    for(ul_loop=0;ul_loop<DEV_PWR_STATE_BUTT;ul_loop++)
    {
        if(0 == ul_loop%4)
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");
        }
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "state %d bitmap:0x%x ,",
                        ul_loop,pst_pm_arbiter->ul_state_bitmap[ul_loop]);
    }

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n Curr State:(%d), Prev State:(%d)\n",
                  pst_pm_arbiter->uc_cur_state, pst_pm_arbiter->uc_prev_state);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "--------------------------Device %d PM info end------------------------\n\n",pst_device->uc_device_id);
   /*ÿVAP״̬��FSM*/
   /* ����device������vap */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
      pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
      if (OAL_PTR_NULL == pst_dmac_vap)
      {
          OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_CFG, "{hmac_config_wifi_enable::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
          return OAL_ERR_CODE_PTR_NULL;
      }
      pst_pm_handler = pst_dmac_vap->pst_pm_handler;
      if(!pst_pm_handler)
      {
        return OAL_ERR_CODE_PTR_NULL;
      }
      pst_pm_fsm = pst_pm_handler->p_mac_fsm;
      if(!pst_pm_fsm)
      {
        return OAL_ERR_CODE_PTR_NULL;
      }
      OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"--------------------------PM FSM info------------------------\n");
      OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"Arbiter id = %d,max_inactive_time = %d\n",
                    pst_pm_handler->ul_pwr_arbiter_id,pst_pm_handler->ul_max_inactive_time);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"inactive_time = %d,user_check_count = %d,user_num = %d\n",
                    pst_pm_handler->ul_inactive_time,pst_pm_handler->ul_user_check_count,pst_dmac_vap->st_vap_base_info.us_user_nums);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"auto_sleep_en = %d, wow_en = %d, siso_en = %d\n",
                    pst_pm_handler->bit_pwr_sleep_en,pst_pm_handler->bit_pwr_wow_en,
                    pst_pm_handler->bit_pwr_siso_en);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"Cur State:(%d), Prev state:(%d), Last event:(%d)\n",
                    pst_pm_fsm->uc_cur_state, pst_pm_fsm->uc_prev_state, pst_pm_fsm->us_last_event);

    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_pm_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;
    mac_pm_arbiter_stru         *pst_pm_arbiter;
    oal_uint8                    uc_vap_idx;
    oal_int32                    l_value;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*device��arbiter����Ϣ*/
    pst_pm_arbiter = pst_device->pst_pm_arbiter;
    if(OAL_PTR_NULL == pst_pm_arbiter)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_pm_arbiter null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    l_value = *((oal_int32 *)puc_param);
    pst_device->en_pm_enable = (1==l_value)?OAL_TRUE:OAL_FALSE;


    /*ʹ��,Ϊÿ��VAP attach pm handler*/
    /*ȥʹ��,Ϊÿ��VAP deattach pm handler*/
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
      pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
      if (OAL_PTR_NULL == pst_dmac_vap)
      {
          OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
          return OAL_ERR_CODE_PTR_NULL;
      }

      /*STAģʽ������*/
      if(WLAN_VAP_MODE_BSS_STA ==  pst_dmac_vap->st_vap_base_info.en_vap_mode)
      {
        continue;
      }

      if(OAL_TRUE == pst_device->en_pm_enable)
      {
        dmac_pm_ap_attach(pst_dmac_vap);
      }
      else
      {
        dmac_pm_ap_deattach(pst_dmac_vap);
      }
    }
    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_PERFORM_STAT
/*****************************************************************************
 �� �� ��  : dmac_config_pfm_stat
 ��������  : ��ʼ����ͳ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pfm_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_stat_param_stru        *pst_stat_param  = OAL_PTR_NULL;
    mac_user_stru                  *pst_user        = OAL_PTR_NULL;
    dmac_tid_stru                  *pst_tid         = OAL_PTR_NULL;
    oal_void                       *p_void          = OAL_PTR_NULL;
    oal_uint16                      us_user_idx     = 0;
    oal_uint32                      ul_ret          = OAL_SUCC;

    pst_stat_param = (mac_cfg_stat_param_stru *)puc_param;

    switch (pst_stat_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_DELAY:
        case MAC_STAT_TYPE_TID_PER:
        case MAC_STAT_TYPE_TID_THRPT:
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_stat_param->auc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
                return ul_ret;
            }

            pst_user = mac_res_get_mac_user(us_user_idx);

            ul_ret = dmac_user_get_tid_by_num(pst_user, pst_stat_param->uc_tidno, &pst_tid);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::dmac_user_get_tid_by_num failed[%d].}", ul_ret);
                return ul_ret;
            }

            p_void = (oal_void *)pst_tid;

            break;

        case MAC_STAT_TYPE_USER_THRPT:
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_stat_param->auc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
                return ul_ret;
            }

            pst_user = mac_res_get_mac_user(us_user_idx);

            p_void = (oal_void *)pst_user;

            break;

        case MAC_STAT_TYPE_VAP_THRPT:
            p_void = (oal_void *)pst_mac_vap;

            break;

        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
            return OAL_FAIL;
    }

    /* ע��ͳ�ƽڵ� */
    ul_ret = dmac_stat_register(OAM_MODULE_ID_PERFORM_STAT, pst_stat_param->en_stat_type, p_void, OAL_PTR_NULL, OAL_PTR_NULL,pst_mac_vap->ul_core_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::invalid en_stat_type[%d].}", pst_stat_param->en_stat_type);
        return ul_ret;
    }

    /* ͬʱ��ʼ����ͳ�� */
    ul_ret = dmac_stat_start(OAM_MODULE_ID_PERFORM_STAT,
                             pst_stat_param->en_stat_type,
                             pst_stat_param->us_stat_period,
                             pst_stat_param->us_stat_num,
                             p_void);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::dmac_stat_start failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_pfm_display
 ��������  : ��ʾ������־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pfm_display(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_display_param_stru     *pst_display_param  = OAL_PTR_NULL;
    mac_user_stru                  *pst_user            = OAL_PTR_NULL;
    dmac_tid_stru                  *pst_tid             = OAL_PTR_NULL;
    oal_void                       *p_void              = OAL_PTR_NULL;
    oal_uint16                      us_user_idx         = 0;
    oal_uint32                      ul_ret              = OAL_SUCC;

    pst_display_param = (mac_cfg_display_param_stru *)puc_param;

    switch (pst_display_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_DELAY:
        case MAC_STAT_TYPE_TID_PER:
        case MAC_STAT_TYPE_TID_THRPT:
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_display_param->auc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
                return ul_ret;
            }

            pst_user = mac_res_get_mac_user(us_user_idx);

            ul_ret = dmac_user_get_tid_by_num(pst_user, pst_display_param->uc_tidno, &pst_tid);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_user_get_tid_by_num failed[%d].}", ul_ret);
                return ul_ret;
            }

            p_void = (oal_void *)pst_tid;

            break;

        case MAC_STAT_TYPE_USER_THRPT:
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_display_param->auc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
                return ul_ret;
            }

            pst_user = mac_res_get_mac_user(us_user_idx);

            p_void = (oal_void *)pst_user;

            break;

        case MAC_STAT_TYPE_VAP_THRPT:
            p_void = (oal_void *)pst_mac_vap;

            break;

        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::invalid en_stat_type[%d].}", pst_display_param->en_stat_type);
            return OAL_FAIL;
    }

    /* ��ʾͳ����Ϣ */
    ul_ret = dmac_stat_display(OAM_MODULE_ID_PERFORM_STAT, pst_display_param->en_stat_type, p_void);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_stat_display failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ע��ͳ�ƽڵ� */
    ul_ret = dmac_stat_unregister(OAM_MODULE_ID_PERFORM_STAT, pst_display_param->en_stat_type, p_void);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_stat_unregister failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 �� �� ��  : dmac_config_set_pm_chip_state
 ��������  : ����оƬ˯�߻���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_chip_state(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru             *pst_device;
    hal_lpm_state_param_stru     st_para;
    mac_cfg_lpm_sleep_para_stru  *pst_set_para;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_lpm_chip_state::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_set_para = (mac_cfg_lpm_sleep_para_stru*)puc_param;
    if (MAC_LPM_STATE_SOFT_SLEEP == pst_set_para->uc_pm_switch)
    {

        st_para.bit_soft_sleep_en = 1;
        st_para.ul_sleep_time     = 1000*(pst_set_para->us_sleep_ms);   /*15ms*/

        //dmac_test_lpm_create_sleep_timer(pst_device,st_para.us_sleep_time);

        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_NORMAL_WORK,HAL_LPM_STATE_DEEP_SLEEP,&st_para);

    }

    if (MAC_LPM_STATE_GPIO_SLEEP == pst_set_para->uc_pm_switch)
    {
        st_para.bit_gpio_sleep_en = 1;
        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_NORMAL_WORK,HAL_LPM_STATE_DEEP_SLEEP,&st_para);

    }

    if (MAC_LPM_STATE_WORK == pst_set_para->uc_pm_switch)
    {
        /*����*/
        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_DEEP_SLEEP,HAL_LPM_STATE_NORMAL_WORK,OAL_PTR_NULL);

    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_soc_mode
 ��������  : ����SOC�͹��Ľ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_soc_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                  *pst_device;
    mac_cfg_lpm_soc_set_stru         *pst_soc_para;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL ;
    }
    pst_soc_para = (mac_cfg_lpm_soc_set_stru*)puc_param;

    switch(pst_soc_para->en_mode)
    {
        case MAC_LPM_SOC_BUS_GATING:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_BUS_GATING,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_RD_BYPASS:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_RD_BYPASS,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_MEM_PRECHARGE:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_MEM_PRECHARGE,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_L0_S:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_L0,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_L1_0:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_L1_PM,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        default:
            break;
    }

    return OAL_SUCC ;

}

/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_psm_param
 ��������  : ����оƬPSM�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_psm_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                  *pst_device;
    mac_cfg_lpm_psm_param_stru       *pst_psm_para;
    dmac_vap_stru                    *pst_dmac_vap;
    hal_to_dmac_vap_stru             *pst_hal_vap;

    /* ת��ΪDMAC VAP */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap = pst_dmac_vap->pst_hal_vap;

	pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_psm_para = (mac_cfg_lpm_psm_param_stru*)puc_param;
    if(0 == pst_psm_para->uc_psm_on||1 == pst_psm_para->uc_psm_on)
    {
        hal_set_psm_listen_interval(pst_hal_vap, pst_psm_para->us_psm_listen_interval);
        hal_set_psm_tbtt_offset(pst_hal_vap, pst_psm_para->us_psm_tbtt_offset);
        hal_set_psm_wakeup_mode(pst_device->pst_device_stru, pst_psm_para->uc_psm_wakeup_mode);
        hal_set_psm_status(pst_device->pst_device_stru, pst_psm_para->uc_psm_on);

        hal_test_lpm_set_psm_en(pst_psm_para->uc_psm_on);
    }
    else
    {
        /*debug��ʾ���*/
        hal_test_lpm_psm_dump_record();
    }

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_smps_mode
 ��������  : ����оƬ˯�߻���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru    *pst_device;
    oal_uint8           uc_mode;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_lpm_smps_mode::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_mode = *puc_param;
    hal_set_smps_mode(pst_device->pst_device_stru,uc_mode);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_smps_stub
 ��������  : smps ap�෢����׮��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_smps_stub(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru						 *pst_device;
    mac_cfg_lpm_smps_stub_stru           *pst_smps_stub;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }

    pst_smps_stub = (mac_cfg_lpm_smps_stub_stru*)puc_param;
    g_st_dmac_test_mng.st_lpm_smps_stub.uc_stub_type= pst_smps_stub->uc_stub_type;
    g_st_dmac_test_mng.st_lpm_smps_stub.uc_rts_en = pst_smps_stub->uc_rts_en;

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_txop_ps
 ��������  : ����оƬtxop ps�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_txop_ps(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_device;
    mac_cfg_lpm_txopps_set_stru* pst_txopps_set;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_txopps_set = (mac_cfg_lpm_txopps_set_stru*)puc_param;
    if((0 == pst_txopps_set->uc_txop_ps_on)||(1 == pst_txopps_set->uc_txop_ps_on))
    {
        hal_set_txop_ps_condition1(pst_device->pst_device_stru, pst_txopps_set->uc_conditon1);
        hal_set_txop_ps_condition2(pst_device->pst_device_stru, pst_txopps_set->uc_conditon2);
        hal_set_txop_ps_enable(pst_device->pst_device_stru,     pst_txopps_set->uc_txop_ps_on);

        dmac_test_lpm_txopps_en(pst_txopps_set->uc_txop_ps_on);
    }
    else
    {
        dmac_test_lpm_txopps_debug();
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_txop_ps_tx_stub
 ��������  : ����оƬtxop ps�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_txop_ps_tx_stub(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru						 *pst_device;
    mac_cfg_lpm_txopps_tx_stub_stru      *pst_txopps_tx_stub;
    dmac_lpm_txopps_tx_stub_stru         *pst_txop_stub;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_txopps_tx_stub = (mac_cfg_lpm_txopps_tx_stub_stru*)puc_param;
    pst_txop_stub = &g_st_dmac_test_mng.st_lpm_txop_stub;
    pst_txop_stub->uc_stub_on = pst_txopps_tx_stub->uc_stub_on;
    pst_txop_stub->us_begin_num = pst_txopps_tx_stub->us_begin_num;
    pst_txop_stub->us_curr_num = 0;
    pst_txop_stub->us_partial_aid_real = 0;

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_config_set_lpm_wow_en
 ��������  : ����оƬtxop ps�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_wow_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_mac_device;
    mac_cfg_lpm_wow_en_stru         *pst_wow_en;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                       uc_vap_idx;
    oal_uint32                      ul_wow_set_bitmap = 0;
    hal_wow_param_stru              st_wow_para;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FAIL;
    }
    pst_wow_en = (mac_cfg_lpm_wow_en_stru*)puc_param;
    OAL_MEMZERO(&st_wow_para, OAL_SIZEOF(hal_wow_param_stru));
    dmac_test_lpm_set_wow_en(pst_wow_en->uc_en);

    /*hipriv "Hisilicon0 lpm_wow_en 0|1|2(0��ʹ��|1ʹ��|2������Ϣ) 0|1(Null data�Ƿ���)"*/
    if(pst_wow_en->uc_en==1||pst_wow_en->uc_en==0)
    {
        if(pst_wow_en->uc_en)
        {
            ul_wow_set_bitmap|= HAL_WOW_PARA_EN;
            for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_CFG, "{dmac_config_set_lpm_wow_en::pst_dmac_vap null.");
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_prepare_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_prepare_null_data(pst_dmac_vap);
                if(0 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                  if(!pst_dmac_vap->pst_wow_probe_resp)
                   {
                        continue;
                   }
                  st_wow_para.ul_ap0_probe_resp_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_probe_resp));
                  st_wow_para.ul_ap0_probe_resp_len = pst_dmac_vap->us_wow_probe_resp_len;
                  st_wow_para.uc_ap0_probe_resp_phy = 0;    /*11b*/
                  st_wow_para.uc_ap0_probe_resp_rate = 0;   /*1M*/
                  ul_wow_set_bitmap |= HAL_WOW_PARA_AP0_PROBE_RESP;
                }
                else if(1 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                  if(!pst_dmac_vap->pst_wow_probe_resp)
                   {
                        continue;
                   }
                  st_wow_para.ul_ap1_probe_resp_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_probe_resp));
                  st_wow_para.ul_ap1_probe_resp_len = pst_dmac_vap->us_wow_probe_resp_len;
                  st_wow_para.uc_ap1_probe_resp_phy = 0;    /*11b*/
                  st_wow_para.uc_ap1_probe_resp_rate = 0;   /*1M*/
                  ul_wow_set_bitmap |= HAL_WOW_PARA_AP1_PROBE_RESP;
                }
                else if(4 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                   if(!pst_dmac_vap->pst_wow_null_data)
                   {
                        continue;
                   }
                   st_wow_para.ul_nulldata_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_null_data));
                   st_wow_para.uc_nulldata_rate = 0;
                   st_wow_para.uc_nulldata_phy_mode = 0;
                   ul_wow_set_bitmap |= HAL_WOW_PARA_NULLDATA;

                   st_wow_para.ul_nulldata_interval = 1000; /*1s*/
                }
            }
            st_wow_para.uc_nulldata_awake = pst_wow_en->uc_null_wake;
            ul_wow_set_bitmap |= HAL_WOW_PARA_NULLDATA_AWAKE;

            hal_set_wow_en(pst_mac_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            OAL_IO_PRINT("call dmac_test_lpm_create_sleep_timer \n");
            dmac_test_lpm_create_sleep_timer(pst_mac_device,30);

        }
        else
        {
            ul_wow_set_bitmap = 0;
            for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_CFG, "{dmac_config_set_lpm_wow_en::pst_dmac_vap null.");
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_release_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_release_null_data(pst_dmac_vap);
            }

            hal_set_wow_en(pst_mac_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(g_st_dmac_test_mng.st_sleep_timer));
        }

    }
    else
    {
#if(_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

        /*��ʾ�жϴ���*/
        //dmac_test_lpm_wow_debug();
        oal_uint32          ul_val = 0x0;

        /*GPIO 47*/
        /*1.���ó����ģʽ*/
        ul_val = oal_readl((oal_uint32)(g_pst_5610_mode + 0x1a4));
        ul_val |= BIT15;
        oal_writel(ul_val, (oal_uint32)(g_pst_5610_mode + 0x1a4));

        /*2.�������ݷ���in*/
        ul_val =  oal_readl((oal_uint32)(g_pst_5610_gpio + 0x4));
        ul_val &= ~BIT15;
        oal_writel(ul_val, (oal_uint32)(g_pst_5610_gpio + 0x4));

        /*�����ݼĴ���*/
        ul_val =  oal_readl((oal_uint32)(g_pst_5610_gpio + 0x50));

        OAL_IO_PRINT("GPIO 47 0x10107000 = 0x%x \n",ul_val);
#endif
#endif
    }
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_lpm_tx_probe_request
 ��������  : ����оƬtxop ps�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_lpm_tx_probe_request(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device ;
    dmac_vap_stru                   *pst_dmac_vap ;
    mac_cfg_lpm_tx_data_stru        *pst_lpm_tx_data ;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FAIL ;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
       OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_lpm_tx_probe_request::can't find existed vap to send probe_req.}");
       return OAL_FAIL ;
    }

   pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[0]);
   if (OAL_PTR_NULL == pst_dmac_vap)
   {
       OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_lpm_tx_probe_request::pst_dmac_vap null.}");

       return OAL_ERR_CODE_PTR_NULL;
   }

   pst_lpm_tx_data = (mac_cfg_lpm_tx_data_stru*)puc_param;

   dmac_test_lpm_send_probe_requst(pst_dmac_vap,pst_lpm_tx_data->uc_positive,pst_lpm_tx_data->auc_da);

   return OAL_SUCC ;
}

/*****************************************************************************
 �� �� ��  : dmac_config_remove_user_lut
 ��������  : ɾ��/�ָ��û�LUT
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_remove_user_lut(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_remove_lut_stru *pst_param;    /* ����ɾ���û��ṹ�� */
    dmac_user_stru          *pst_dmac_user;


    pst_param = (mac_cfg_remove_lut_stru *)puc_param;

    pst_dmac_user = mac_res_get_dmac_user(pst_param->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_remove_user_lut::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (1 == pst_param->uc_is_remove)
    {
        /* remove lut */
        dmac_user_inactive(pst_dmac_user);


    }
    else
    {
        /* resume lut */
        dmac_user_active(pst_dmac_user);
    }

    return OAL_SUCC;
}
OAL_STATIC oal_uint32 dmac_config_send_frame(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_user_stru                  *pst_dmac_user;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_netbuf_stru                 *pst_netbuf;
    oal_uint32                       ul_frame_len = 0;
    mac_tx_ctl_stru                 *pst_tx_ctl;
    oal_uint32                       ul_ret;
    mac_cfg_send_frame_param_stru   *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    dmac_test_encap_frame            pst_test_encap_frame_fun;
    oal_uint16                       us_user_idx = 0;


    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_param->auc_mac_ra, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                "{dmac_config_send_frame::mac_vap_find_user_by_macaddr failed, mac_ra=%02X:XX:XX:%02X:%02X:%02X.}",
                pst_param->auc_mac_ra[0],pst_param->auc_mac_ra[3],pst_param->auc_mac_ra[4],pst_param->auc_mac_ra[5]);
        return OAL_PTR_NULL;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                       "{dmac_config_send_frame::cannot find user by idx[%d]!.}",
                       us_user_idx);
        return OAL_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::cannot find vap by user[user_id is %d]!}",us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����֡�ڴ� */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::cannot alloc netbuff in size[%d].}", WLAN_LARGE_NETBUF_SIZE);

        return OAL_ERR_CODE_PTR_NULL;
    }
     /* ��ʼ��ǰ��ָ��ΪNULL */
    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);


    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    DMAC_SET_NETBUF_CB(FRW_EVENT_TYPE_HOST_CRX, pst_dmac_user->st_user_base_info.us_assoc_id,
                        OAL_FALSE, OAL_FALSE, 0);
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CONTROL;

    /* ��֡ */
    pst_test_encap_frame_fun = dmac_test_get_encap_func(pst_param->en_frame_type);
    if(OAL_PTR_NULL == pst_test_encap_frame_fun)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::pst_test_encap_frame_fun null.}");

        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_frame_len = pst_test_encap_frame_fun(&(pst_dmac_vap->st_vap_base_info),
                                            (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf),
                                            puc_param, uc_len);

    if (0 == ul_frame_len)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::ul_frame_len=0.}");


        oal_netbuf_free(pst_netbuf);

        return OAL_FAIL;
    }

    /* ���÷��͹���֡�ӿ� */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_netbuf, (oal_uint16)ul_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf);
        return ul_ret;
    }
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_rx_pn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_device;
    mac_cfg_set_rx_pn_stru          *pst_rx_pn;
    dmac_user_stru                  *pst_dmac_usr;
    hal_pn_lut_cfg_stru             st_pn_lut_cfg;

    pst_rx_pn = (mac_cfg_set_rx_pn_stru *)puc_param;

    pst_dmac_usr = mac_res_get_dmac_user(pst_rx_pn->us_user_idx);
    if(OAL_PTR_NULL == pst_dmac_usr)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rx_pn::pst_dmac_usr null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rx_pn::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    st_pn_lut_cfg.uc_pn_key_type = 1;
    st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_usr->uc_lut_index;
    st_pn_lut_cfg.uc_pn_tid      = 0;
    st_pn_lut_cfg.ul_pn_msb      = 0;
    st_pn_lut_cfg.ul_pn_lsb      = pst_rx_pn->us_rx_pn;
    hal_set_rx_pn(pst_device->pst_device_stru,&st_pn_lut_cfg);
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_soft_retry(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_set_software_retry(puc_param);
	return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_open_addr4(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_open_addr4(puc_param);
	return OAL_SUCC;
}

OAL_STATIC oal_uint32  dmac_config_open_wmm_test(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_open_wmm_test(pst_mac_vap, *((oal_uint8 *)puc_param));
	return OAL_SUCC;
}



OAL_STATIC oal_uint32  dmac_config_chip_test_open(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_set_chip_test(*(oal_uint8*)puc_param);
	return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_coex(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_device;
    mac_cfg_coex_ctrl_param_stru    *pst_coex_ctrl;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_coex_ctrl = (mac_cfg_coex_ctrl_param_stru *)puc_param;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_coex::ul_mac_ctrl=%d ul_rf_ctrl=%d.}",
                  pst_coex_ctrl->ul_mac_ctrl, pst_coex_ctrl->ul_rf_ctrl);

    hal_set_coex_ctrl(pst_device->pst_device_stru, pst_coex_ctrl->ul_mac_ctrl, pst_coex_ctrl->ul_rf_ctrl);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_set_dfx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = *((oal_int32 *)puc_param);

    g_st_dmac_test_mng.en_cfg_tx_cnt = (oal_switch_enum_uint8)l_value;

    return OAL_SUCC;
}


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

OAL_STATIC oal_uint32 dmac_config_enable_pmf(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_bool_enum_uint8        en_pmf_active;
    wlan_pmf_cap_status_uint8 *puc_pmf_cap;
    oal_dlist_head_stru       *pst_entry;
    oal_dlist_head_stru       *pst_user_list_head;
    mac_user_stru             *pst_user_tmp;
    dmac_vap_stru             *pst_dmac_vap;
    mac_device_stru           *pst_device;

    puc_pmf_cap = (wlan_pmf_cap_status_uint8 *)puc_param;
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF, "{dmac_config_enable_pmf:: pointer is null,pst_mac_vap[%d], puc_param[%d] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{dmac_config_enable_pmf::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    switch(*puc_pmf_cap)
    {
        case MAC_PMF_DISABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_FALSE);
            en_pmf_active = OAL_FALSE;

             /* ����pmf�ļӽ����ܿ��� */
            hal_set_pmf_crypto(pst_dmac_vap->pst_hal_vap, OAL_FALSE);
        }
        break;
        /* enable״̬�����ı�����user��Ӳ���� */
        case MAC_PMF_ENABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_TRUE);
            return OAL_SUCC;
        }
        case MAC_PME_REQUIRED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_TRUE);
            en_pmf_active = OAL_TRUE;

             /* ����pmf�ļӽ����ܿ��� */
            hal_set_pmf_crypto(pst_dmac_vap->pst_hal_vap, OAL_TRUE);

        }
        break;
        default:
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{dmac_config_enable_pmf: commend error!}");
            return OAL_FALSE;
        }
    }

    if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state)
    {
        pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

        for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);

            /* ָ��˫��������һ���ڵ� */
            pst_entry = pst_entry->pst_next;
            if (OAL_PTR_NULL == pst_user_tmp)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PMF, "dmac_config_enable_pmf:: pst_user_tmp is null");
                return OAL_ERR_CODE_PTR_NULL;
            }
            mac_user_set_pmf_active(pst_user_tmp, en_pmf_active);

        }

    }

    return OAL_SUCC;
}
#endif


OAL_STATIC oal_uint32  dmac_config_send_pspoll(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru         *pst_netbuf;
    oal_uint8               *puc_data;
    mac_tx_ctl_stru         *pst_tx_cb;
    oal_uint32               ul_ret;

    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_PTR_NULL;
    }

    oal_netbuf_put(pst_netbuf, 16);

    puc_data = OAL_NETBUF_HEADER(pst_netbuf);

    /* frame control,����DS��ps-poll */
    puc_data[0] = 0xA4;
    puc_data[1] = 0x01;

    /* AID */
    puc_data[2] = (oal_uint8)pst_mac_vap->us_sta_aid;
    puc_data[3] = 0xC0;

    /* BSSID */
    oal_set_mac_addr(&puc_data[4], pst_mac_vap->auc_bssid);

    /* Transmitter address */
    oal_set_mac_addr(&puc_data[10], pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);

    pst_tx_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(pst_tx_cb, OAL_NETBUF_CB_SIZE());
    MAC_GET_CB_TX_USER_IDX(pst_tx_cb)   = pst_mac_vap->uc_assoc_vap_id;
    MAC_GET_CB_IS_MCAST(pst_tx_cb)   = OAL_FALSE;
    mac_set_cb_ac(pst_tx_cb, WLAN_WME_AC_MGMT);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_cb)          = OAL_TRUE;
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_cb)           = pst_mac_vap->uc_vap_id;
    MAC_GET_CB_FRAME_TYPE(pst_tx_cb)          = WLAN_CONTROL;
    MAC_GET_CB_IS_MCAST(pst_tx_cb)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_cb, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_cb)   = OAL_TRUE;
    mac_set_cb_frame_hdr(pst_tx_cb, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_cb)    = 16;
    MAC_GET_CB_MPDU_NUM(pst_tx_cb)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_cb)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_cb)               = 0;

    ul_ret = dmac_tx_mgmt((dmac_vap_stru *)pst_mac_vap, pst_netbuf, 16);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_pspoll::dmac_tx_mgmt failed[%d].", ul_ret);
        oal_netbuf_free(pst_netbuf);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_config_send_nulldata(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    oal_uint16                       us_frame_ctl_second_byte = 0;
    mac_user_stru                   *pst_user;
    oal_uint8                       *puc_frame;
    mac_ieee80211_qos_frame_stru    *pst_qos_header;
    mac_cfg_tx_nulldata_stru        *pst_tx_nulldata;

    /* ����net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_TRUE);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::pst_net_buf null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_tx_nulldata = (mac_cfg_tx_nulldata_stru *)puc_param;

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    if (pst_tx_nulldata->l_is_qos)
    {
        oal_netbuf_put(pst_net_buf, OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    }
    else
    {
        oal_netbuf_put(pst_net_buf, 24);
    }

    puc_frame = OAL_NETBUF_HEADER(pst_net_buf);

    if (0 == pst_tx_nulldata->l_is_psm)
    {
        us_frame_ctl_second_byte = 0x0100;
    }
    else
    {
        us_frame_ctl_second_byte = 0x1100;
    }

    pst_user = mac_res_get_mac_user((oal_uint16)pst_mac_vap->uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::pst_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д֡ͷ,����from dsΪ1��to dsΪ0�����frame control�ĵڶ����ֽ�Ϊ02 */
    if (pst_tx_nulldata->l_is_qos)
    {
        mac_hdr_set_frame_control(puc_frame, (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL) | us_frame_ctl_second_byte);
    }
    else
    {
        mac_hdr_set_frame_control(puc_frame, (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | us_frame_ctl_second_byte);
    }

    if (pst_tx_nulldata->l_is_qos)
    {
        pst_qos_header = (mac_ieee80211_qos_frame_stru *)puc_frame;
        pst_qos_header->bit_qc_tid = (oal_uint8)pst_tx_nulldata->l_tidno;
        pst_qos_header->bit_qc_eosp = 1;
        pst_qos_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;
    }

    /* BSSID */
    oal_set_mac_addr(&puc_frame[4], pst_user->auc_user_mac_addr);

    /* SA */
    oal_set_mac_addr(&puc_frame[10], pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* DA */
    oal_set_mac_addr(&puc_frame[16], pst_user->auc_user_mac_addr);

    /* ��дcb�ֶ� */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* ��дtx���� */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)            = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);

    if (pst_tx_nulldata->l_is_qos)
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_TID_TO_AC(pst_tx_nulldata->l_tidno));
    }
    else
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_BE);
    }
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)        = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)          = 0;
    if (pst_tx_nulldata->l_is_qos)
    {
        mac_set_cb_tid(pst_tx_ctrl, (oal_uint8)pst_tx_nulldata->l_tidno);
    }
    else
    {
        mac_set_cb_tid(pst_tx_ctrl, WLAN_TID_FOR_DATA);
    }

    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)          = pst_mac_vap->uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)           = pst_mac_vap->uc_assoc_vap_id;

    /* ��дtx rx�������� */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)               = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)                 = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)         = OAL_TRUE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    if (pst_tx_nulldata->l_is_qos)
    {
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)     = OAL_SIZEOF(mac_ieee80211_qos_frame_stru);
    }
    else
    {
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)     = OAL_SIZEOF(mac_ieee80211_frame_stru);
    }

    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)                = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)              = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)                = 0;

    ul_ret = dmac_tx_process_data(((dmac_vap_stru *)pst_mac_vap)->pst_hal_device, (dmac_vap_stru *)pst_mac_vap, pst_net_buf);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::dmac_tx_process_data failed[%d].}", ul_ret);

        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_clear_all_stat
 ��������  : ���ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_clear_all_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_clear_all_stat::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* ����ж�ͳ����Ϣ */
    hal_clear_irq_stat(pst_device->pst_device_stru);

    return OAL_SUCC;
}

#endif /* CHIP_TEST */

/*****************************************************************************
 �� �� ��  : dmac_config_get_fem_pa_status
 ��������  : ��ȡfem��pa�Ƿ��ջ�״̬
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_fem_pa_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                       *pst_device;
    dmac_atcmdsrv_fem_pa_response_event    st_atcmdsrv_fem_pa_info;
    oal_uint32                             ul_cali_check_fem_pa_status = 0;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_fem_pa_status::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    st_atcmdsrv_fem_pa_info.uc_fem_pa_event = OAL_ATCMDSRV_FEM_PA_INFO_EVENT;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hal_get_fem_pa_status(pst_device->pst_device_stru,&ul_cali_check_fem_pa_status);
#endif
    st_atcmdsrv_fem_pa_info.ul_fem_pa_status = ul_cali_check_fem_pa_status;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_CHECK_FEM_PA, OAL_SIZEOF(dmac_atcmdsrv_fem_pa_response_event), (oal_uint8 *)&st_atcmdsrv_fem_pa_info);
    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_config_set_mib
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mib(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    return mac_config_set_mib(pst_mac_vap, uc_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_obss_mib
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_obss_mib(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wlan_mib_Dot11OperationEntry_stru *pst_new_mib;
    wlan_mib_Dot11OperationEntry_stru *pst_mib;

    pst_new_mib = (wlan_mib_Dot11OperationEntry_stru*)puc_param;
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_new_mib))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_obss_mib::null param}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mib = &pst_mac_vap->pst_mib_info->st_wlan_mib_operation;
    pst_mib->ul_dot11BSSWidthTriggerScanInterval = pst_new_mib->ul_dot11BSSWidthTriggerScanInterval;
    pst_mib->ul_dot11BSSWidthChannelTransitionDelayFactor = pst_new_mib->ul_dot11BSSWidthChannelTransitionDelayFactor;
    pst_mib->ul_dot11OBSSScanPassiveDwell = pst_new_mib->ul_dot11OBSSScanPassiveDwell;
    pst_mib->ul_dot11OBSSScanActiveDwell = pst_new_mib->ul_dot11OBSSScanActiveDwell;
    pst_mib->ul_dot11OBSSScanPassiveTotalPerChannel = pst_new_mib->ul_dot11OBSSScanPassiveTotalPerChannel;
    pst_mib->ul_dot11OBSSScanActiveTotalPerChannel = pst_new_mib->ul_dot11OBSSScanActiveTotalPerChannel;
    pst_mib->ul_dot11OBSSScanActivityThreshold = pst_new_mib->ul_dot11OBSSScanActivityThreshold;

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : dmac_config_set_thruput_bypass
 ��������  : ����thruput_bypassά���
 �������  :
 �������  :
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_thruput_bypass(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_thruput_bypass_stru *pst_set_thruput_bypass = (mac_cfg_set_thruput_bypass_stru *)puc_param;

    OAL_SET_THRUPUT_BYPASS_ENABLE(pst_set_thruput_bypass->uc_bypass_type, pst_set_thruput_bypass->uc_value);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_config_set_performance_log_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_performance_log_switch_stru *pst_set_performance_log_switch = (mac_cfg_set_performance_log_switch_stru *)puc_param;
    oal_uint8                    uc_loop_index;
    dmac_vap_stru *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if(pst_set_performance_log_switch->uc_performance_log_switch_type >= DFX_PERFORMANCE_LOG_BUTT)
    {
        for(uc_loop_index = 0;uc_loop_index < DFX_PERFORMANCE_LOG_BUTT;uc_loop_index++)
        {
            DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(uc_loop_index,pst_set_performance_log_switch->uc_value);
        }
    }
    else if(pst_set_performance_log_switch->uc_performance_log_switch_type == DFX_PERFORMANCE_DUMP)
    {
        if(0 == pst_set_performance_log_switch->uc_value )
        {
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{ampdu length (1-14)%d  (15-17)%d  (18-30)%d  (31-32)%d\n.}",
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_0],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_1],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_2],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_3]
            );
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_hardretry_count = %d,ul_tx_cts_fail = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_retries,
                pst_dmac_vap->st_query_stats.ul_tx_cts_fail);
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_mpdu_succ_num = %d, ul_tx_mpdu_fail_num = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_succ_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_fail_num);
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_ampdu_succ_num = %d, ul_tx_mpdu_in_ampdu = %d,ul_tx_ampdu_fail_num = %d, ul_tx_mpdu_fail_in_ampdu = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_ampdu_succ_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_in_ampdu,
                pst_dmac_vap->st_query_stats.ul_tx_ampdu_fail_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_fail_in_ampdu);
        }
        else
        {
            for(uc_loop_index = 0;uc_loop_index < DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT;uc_loop_index++)
            {
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[uc_loop_index] = 0;
            }
        }
    }
    else
    {
        DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(pst_set_performance_log_switch->uc_performance_log_switch_type,pst_set_performance_log_switch->uc_value);
    }

    return OAL_SUCC;
}
#endif

oal_void  dmac_config_set_wmm_open_cfg(hal_to_dmac_vap_stru *pst_hal_vap, mac_wme_param_stru  *pst_wmm)
{
    wlan_wme_ac_type_enum_uint8     en_ac_type;

    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_wmm)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_wmm_open_cfg::param null.}");

        return;
    }
    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_hal_vap,
                                 (oal_uint8)(pst_wmm[en_ac_type].ul_logcwmax),
                                 (oal_uint8)(pst_wmm[en_ac_type].ul_logcwmin),
                                  en_ac_type);

        hal_vap_set_machw_aifsn_ac(pst_hal_vap, en_ac_type, (oal_uint8)pst_wmm[en_ac_type].ul_aifsn);
    }

#if 0
    hal_vap_set_machw_cw_bk(pst_hal_vap, (oal_uint8)(pst_wmm[WLAN_WME_AC_BK].ul_logcwmax), (oal_uint8)(pst_wmm[WLAN_WME_AC_BK].ul_logcwmin));
    hal_vap_set_machw_cw_be(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin);
    hal_vap_set_machw_cw_vi(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_logcwmin);
    hal_vap_set_machw_cw_vo(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_logcwmin);

    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_BK, (oal_uint8)pst_wmm[WLAN_WME_AC_BK].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_BE, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VI, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VO, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_aifsn);
#endif

    hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_BE].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_BK].ul_txop_limit);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_VO].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_VI].ul_txop_limit);

}


oal_void  dmac_config_set_wmm_close_cfg(hal_to_dmac_vap_stru *pst_hal_vap, mac_wme_param_stru  *pst_wmm)
{
    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_wmm)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_wmm_close_cfg::param null.}");

        return;
    }
   // hal_vap_set_machw_cw_vo(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin);
    hal_vap_set_edca_machw_cw(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin, WLAN_WME_AC_VO);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VO, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_aifsn);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_BE].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_VI].ul_txop_limit);
}


oal_void dmac_config_set_wmm_register(mac_vap_stru *pst_mac_vap,  oal_bool_enum_uint8 en_wmm)
{
    hal_to_dmac_device_stru *pst_hal_device;
    mac_device_stru         *pst_mac_device;
    hal_to_dmac_vap_stru    *pst_hal_vap;
    dmac_vap_stru           *pst_dmac_vap;
    mac_wme_param_stru      *pst_wmm;
    oal_uint                 ul_irq_flag;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_device = pst_mac_device->pst_device_stru;
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    pst_wmm = mac_get_wmm_cfg(pst_mac_vap->en_vap_mode);

    /* ���жϣ�����Ӳ��������Ҫ���ж� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DCSWR);

    /* ����Ӳ������ */
    /* hal_set_machw_tx_suspend(pst_hal_device); */

    /* ��ȡʱ��� */
    /* hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf); */

     /* ����Ӳ��abort */
    /* hal_set_tx_abort_en(pst_hal_device, 1); */
    /* �ر�wmm */
    if(!en_wmm)
    {
        /* ������������ */
        dmac_flush_txq_to_tid_of_vo(pst_hal_device);
        /* �ر�WMM */
        hal_disable_machw_edca(pst_hal_device);
        /* ��������WMM���� */
        dmac_config_set_wmm_close_cfg(pst_hal_vap, pst_wmm);

        /* ��WMM��mib��Ϣλ�е�Qosλ��0 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;
    }
    else
    {
        /* ��WMM */
        hal_enable_machw_edca(pst_hal_device);
        /* ��������WMM���� */
        dmac_config_set_wmm_open_cfg(pst_hal_vap, pst_wmm);

        /* ��WMM��mib��Ϣλ�е�Qosλ��1 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_TRUE;
    }

    /* �˳�abort */
    /* hal_set_tx_abort_en(pst_hal_device, 0); */

    /* ��������Ӳ������ */
    /* hal_set_machw_tx_resume(pst_hal_device); */

    /* �ٴλ�ȡʱ��� */
    /* hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf_passed); */

    /* ���ж� */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DCSWR);
}


OAL_STATIC oal_uint32  dmac_config_wmm_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru         *pst_mac_device;
    oal_bool_enum_uint8            en_wmm = OAL_FALSE;
    en_wmm = *(oal_bool_enum_uint8 *)puc_param;
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ����״̬û�б仯�����ٽ��к������� */
    if(en_wmm == pst_mac_device->en_wmm)
    {
        return OAL_SUCC;
    }
    /* ����dev�е�wmm_en��ʹ�ܻ��߹ر�4ͨ�� */
    pst_mac_device->en_wmm = en_wmm;

    dmac_config_set_wmm_register(pst_mac_vap, en_wmm);
    return OAL_SUCC;
}



OAL_STATIC oal_uint32  dmac_config_set_rts_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru            *pst_device           = OAL_PTR_NULL;
    mac_cfg_rts_tx_param_stru  *pst_mac_rts_tx_param = OAL_PTR_NULL;
    hal_cfg_rts_tx_param_stru   st_hal_rts_tx_param;

    pst_mac_rts_tx_param = (mac_cfg_rts_tx_param_stru *)puc_param;

    /*mac������ֵ��hal����*/
    oal_memcopy(&st_hal_rts_tx_param, pst_mac_rts_tx_param, OAL_SIZEOF(st_hal_rts_tx_param));

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rts_param::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_set_rts_rate_params(pst_device->pst_device_stru, &st_hal_rts_tx_param);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_update_protection_tx_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::can't find existed vap.}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_tx_update_protection_all_txop_alg(pst_dmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_set_protection
 ��������  : ͬ������ģʽ��صĲ���
 �������  : mac_vap_stru *pst_mac_vap
             uc_len ���ݳ���
             puc_param ����
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_protection(mac_vap_stru *pst_mac_vap,
            oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wlan_mib_Dot11OperationEntry_stru *pst_mib;
    mac_h2d_protection_stru     *pst_h2d_prot;
    dmac_user_stru              *pst_dmac_user;
    oal_uint32                  ul_ret;

    DMAC_CHECK_NULL(puc_param);

    pst_h2d_prot = (mac_h2d_protection_stru *)puc_param;

    //mac_dump_protection(pst_mac_vap, puc_param);

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_BARK_PREAMBLE)
    {
        pst_dmac_user = mac_res_get_dmac_user(pst_h2d_prot->us_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
        {
            OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_protection:: user is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        mac_user_set_barker_preamble_mode(&pst_dmac_user->st_user_base_info, pst_h2d_prot->st_user_cap_info.bit_barker_preamble_mode);

    }

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_MIB)
    {
        pst_mib = &pst_mac_vap->pst_mib_info->st_wlan_mib_operation;
        pst_mib->en_dot11HTProtection = pst_h2d_prot->en_dot11HTProtection;
        pst_mib->en_dot11RIFSMode = pst_h2d_prot->en_dot11RIFSMode;
        pst_mib->en_dot11LSIGTXOPFullProtectionActivated =
            pst_h2d_prot->en_dot11LSIGTXOPFullProtectionActivated;
        pst_mib->en_dot11NonGFEntitiesPresent = pst_h2d_prot->en_dot11NonGFEntitiesPresent;
    }

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_PROT)
    {
        oal_memcopy((oal_uint8*)&pst_mac_vap->st_protection, (oal_uint8*)&pst_h2d_prot->st_protection,
                    OAL_SIZEOF(mac_protection_stru));
    }

    ul_ret = dmac_config_update_protection_tx_param(pst_mac_vap, uc_len, puc_param);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_config_get_version
 ��������  : ��ȡ�汾��Ϣ
 �������  : pst_mac_vap: ָ��VAP��ָ��
             uc_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��28��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;
    oal_uint32                   ul_hw_version = 0;
    oal_uint32                   ul_hw_version_data = 0;
    oal_uint32                   ul_hw_version_num = 0;
    oal_uint8                    auc_sw_version[] = "Hi1151 V100R001C01B361_20150919";
    oal_int8                     ac_tmp_buff[200];

        dmac_atcmdsrv_dbb_num_response_event    st_atcmdsrv_dbb_num_info;


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_version::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡFPGA�汾 */
    hal_get_hw_version(pst_device->pst_device_stru, &ul_hw_version, &ul_hw_version_data, &ul_hw_version_num);

    OAL_SPRINTF((char*)ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "Software Version: %s. \nFPGA Version: %04x-%04x-%02x.\n", auc_sw_version, ul_hw_version, ul_hw_version_data, ul_hw_version_num);
    oam_print(ac_tmp_buff);

        st_atcmdsrv_dbb_num_info.uc_dbb_num_event = OAL_ATCMDSRV_DBB_NUM_INFO_EVENT;
        st_atcmdsrv_dbb_num_info.ul_dbb_num = ul_hw_version;
        dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_GET_VERSION, OAL_SIZEOF(dmac_atcmdsrv_dbb_num_response_event), (oal_uint8 *)&st_atcmdsrv_dbb_num_info);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32   dmac_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;

    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "dmac_config_rx_fcs_info:packets info, succ[0x%x], fail[0x%x]\n", pst_hal_device->ul_rx_normal_mdpu_succ_num, pst_hal_device->ul_rx_ppdu_fail_num);

    /* �������� */
    pst_hal_device->ul_rx_normal_mdpu_succ_num = 0;
    pst_hal_device->ul_rx_ppdu_fail_num = 0;
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_vap_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
	oal_uint8            uc_value;

	uc_value = *puc_param;

	mac_vap_init_rx_nss_by_protocol(pst_mac_vap);
	mac_vap_set_rx_nss(pst_mac_vap, OAL_MIN(pst_mac_vap->en_vap_rx_nss, (uc_value - 1)));

	return OAL_SUCC;
}


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

OAL_STATIC oal_uint32   dmac_config_resume_rx_intr_fifo(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_resume_rx_intr_fifo_stru   *pst_param;
    mac_device_stru              *pst_mac_dev;

    pst_param = (mac_cfg_resume_rx_intr_fifo_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_resume_rx_intr_fifo::pst_mac_dev null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_dev->pst_device_stru->en_rx_intr_fifo_resume_flag = pst_param->uc_is_on;

    return OAL_SUCC;
}
#endif

#ifdef  _PRE_DEBUG_MODE

OAL_STATIC oal_uint32  dmac_config_get_all_reg_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_all_reg_value:pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�Ĵ�����ֵ */
    hal_get_all_reg_value(pst_device->pst_device_stru);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_report_ampdu_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ampdu_stat_stru     *pst_ampdu_stat;
    oal_uint32                   ul_ret;
    dmac_user_stru              *pst_dmac_user;
    oal_uint16                   us_user_idx = 0;
    dmac_tid_stru               *pst_tid;

    pst_ampdu_stat = (mac_cfg_ampdu_stat_stru *)puc_param;

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_ampdu_stat->auc_user_macaddr, &us_user_idx);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_report_ampdu_stat::vap find user fail. ul_ret = [%d], \
                         us_user_idx = [%d]}", ul_ret, us_user_idx);
        return OAL_FAIL;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_report_ampdu_stat:: user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡtid�����tid_noΪ8�����������tid���в��� */
    if (pst_ampdu_stat->uc_tid_no > WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_report_ampdu_stat::tid_no invalid, tid_no = [%d]}", pst_ampdu_stat->uc_tid_no);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_TID_MAX_NUM == pst_ampdu_stat->uc_tid_no)
    {
        return dmac_dft_report_all_ampdu_stat(pst_dmac_user, pst_ampdu_stat->uc_param);
    }
    else
    {
        pst_tid = &pst_dmac_user->ast_tx_tid_queue[pst_ampdu_stat->uc_tid_no];

        return dmac_dft_report_ampdu_stat(pst_tid, pst_ampdu_stat->auc_user_macaddr, pst_ampdu_stat->uc_param);
    }
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_config_set_ampdu_aggr_num
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_ampdu_aggr_num(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_aggr_num_stru   *pst_aggr_num_ctrl;

    pst_aggr_num_ctrl = (mac_cfg_aggr_num_stru *)puc_param;

    g_uc_aggr_num_switch = pst_aggr_num_ctrl->uc_aggr_num_switch;

    if (0 != pst_aggr_num_ctrl->uc_aggr_num_switch)
    {
        g_uc_max_aggr_num = pst_aggr_num_ctrl->uc_aggr_num;

        //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ampdu_aggr_num::aggr num start, num is [%d].}", g_uc_max_aggr_num);
    }
    else
    {
        g_uc_max_aggr_num = 0;

        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ampdu_aggr_num::aggr num stop.}");
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

OAL_STATIC oal_uint32  dmac_config_freq_adjust(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_freq_adjust_stru    *pst_freq_adjust;
    mac_device_stru             *pst_mac_device;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_freq_adjust::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_freq_adjust = (mac_cfg_freq_adjust_stru *)puc_param;

    hal_freq_adjust(pst_mac_device->pst_device_stru, pst_freq_adjust->us_pll_int, pst_freq_adjust->us_pll_frac);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
oal_uint32  dmac_config_set_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_smps_mode_stru                 *pst_smps_mode;
    mac_device_stru                        *pst_mac_device;
    mac_vap_stru                           *pst_mac_vap_tmp;
    wlan_mib_mimo_power_save_enum_uint8     en_mib_smps_mode;
    oal_uint8                               uc_vap_idx;

    pst_smps_mode           = (mac_cfg_smps_mode_stru *)puc_param;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_mac_device   = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{dmac_config_set_smps_mode::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_mib_smps_mode = (wlan_mib_mimo_power_save_enum_uint8)(pst_smps_mode->uc_smps_mode);
    if (en_mib_smps_mode >= WLAN_MIB_MIMO_POWER_SAVE_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{dmac_config_set_smps_mode::unexpect mode[%d].}", en_mib_smps_mode);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����device������vap������vap�µ��ŵ��� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap_tmp = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap_tmp)
        {
            continue;
        }

        if (OAL_TRUE != pst_mac_vap_tmp->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
        {
            continue;
        }
        /* �ŵ�����ֻ���APģʽ����APģʽ������ */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap_tmp->en_vap_mode)
        {
            /* STA��ʱ������ */
            /* ����STA��SMPS������������SM Power Save Frame֡ */
            continue;
        }

        /* ����mib�� */
        pst_mac_vap_tmp->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave = en_mib_smps_mode;
        mac_vap_set_smps(pst_mac_vap_tmp, en_mib_smps_mode);

        /* VAP��userͷָ�벻Ӧ��Ϊ�� */
        if (OAL_FALSE == oal_dlist_is_empty(&pst_mac_vap->st_mac_user_list_head))
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_smps_mode::st_mac_user_list_head is not empty.}");
        }
    }

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == en_mib_smps_mode)
    {
        pst_mac_device->en_smps = OAL_FALSE;
        pst_mac_device->uc_dev_smps_mode = HAL_SMPS_MODE_DISABLE;
    }
    else
    {
        pst_mac_device->en_smps = OAL_TRUE;
        pst_mac_device->uc_dev_smps_mode = en_mib_smps_mode;
    }

    /* дSMPS���ƼĴ��� */
    hal_set_smps_mode(pst_mac_device->pst_device_stru, pst_mac_device->uc_dev_smps_mode);

    return OAL_SUCC;
}

#endif


oal_uint32 dmac_config_set_app_ie_to_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_app_ie_stru         *pst_app_ie;

    if ((OAL_PTR_NULL == puc_param) || (OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_app_ie_to_vap::param is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_app_ie = (oal_app_ie_stru *)puc_param;

    mac_vap_save_app_ie(pst_mac_vap, pst_app_ie, pst_app_ie->en_app_ie_type);
    return OAL_SUCC;
}

oal_uint32 dmac_config_show_device_memleak(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_pool_id_stru          *pst_pool_id_param;
    oal_uint8                         uc_pool_id;

    pst_pool_id_param = (mac_device_pool_id_stru *)puc_param;
    uc_pool_id  = pst_pool_id_param->uc_pool_id;

    if (uc_pool_id >=  OAL_MEM_POOL_ID_BUTT)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_show_device_memleak::uc_pool_id %d >= OAL_MEM_POOL_ID_BUTT.}", uc_pool_id);
        return OAL_FAIL;
    }

    if (uc_pool_id < OAL_MEM_POOL_ID_NETBUF)
    {
        oal_mem_leak(uc_pool_id);
    }
    else if (OAL_MEM_POOL_ID_NETBUF == uc_pool_id)
    {
        oal_mem_netbuf_leak();
    }
#endif
    return OAL_SUCC;
}


oal_uint32 dmac_config_cancel_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_scan_req_stru       *pst_scan_req_params;
    mac_device_stru         *pst_mac_device;

    /* ��ȡmac dev */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* 1.�жϵ�ǰ�Ƿ�����ɨ�裬���������ɨ�裬ֱ�ӷ��� */
    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_cancel_remain_on_channel::scan is not running.}");
        return OAL_SUCC;
    }

    pst_scan_req_params = &(pst_mac_device->st_scan_params);

    /* 2.�жϵ�ǰɨ���vap�ǲ���p2p�ģ�������ǣ�ֱ�ӷ��أ�����ǣ��ж��Ƿ��ڼ���������ֱ�ӷ��� */
    if ((pst_mac_vap->uc_vap_id != pst_scan_req_params->uc_vap_id) ||
        (MAC_SCAN_FUNC_P2P_LISTEN != pst_scan_req_params->uc_scan_func))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                        "{dmac_config_cancel_remain_on_channel::other vap is scanning, scan_func[%d].}",
                        pst_scan_req_params->uc_scan_func);
        return OAL_SUCC;
    }

    /* 3.ɾ����ʱ�������ҵ���ɨ����� */
    if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_cancel_remain_on_channel::stop scan.}");

        dmac_scan_end(pst_mac_device);
    }
    else
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "shouldn't go here");
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_P2P

oal_uint32  dmac_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    mac_cfg_p2p_ops_param_stru  *pst_p2p_ops;


    pst_p2p_ops = (mac_cfg_p2p_ops_param_stru *)puc_param;
    /* ��ȡhal_vap �ṹ�� */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    /*  sanity check, CTwindow 7bit*/
    if(pst_p2p_ops->uc_ct_window < 127)
    {
        /*wpa_supplicantֻ����ctwindow size,����dmac,��д�Ĵ���*/
        pst_dmac_vap->st_p2p_ops_param.uc_ct_window= pst_p2p_ops->uc_ct_window;
        return OAL_SUCC;
    }
    /*  sanity check, opps ctrl 1bit*/
    if(pst_p2p_ops->en_ops_ctrl <  2)
    {
        if((pst_p2p_ops->en_ops_ctrl ==  0)&& IS_P2P_OPPPS_ENABLED(pst_dmac_vap))
        {
            /* �ָ����� */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        }
        pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl = pst_p2p_ops->en_ops_ctrl;
    }
    else
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_ops:invalid ops ctrl value[%d]\r\n",
                           pst_p2p_ops->en_ops_ctrl);
        return OAL_FAIL;
    }
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_ops:ctrl[%d] ct_window[%d] vap state[%d]\r\n",
                pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl,
                pst_dmac_vap->st_p2p_ops_param.uc_ct_window,
                pst_mac_vap->en_vap_state);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    /* ����P2P ops �Ĵ��� */
    hal_vap_set_ops(pst_hal_vap, pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl, pst_dmac_vap->st_p2p_ops_param.uc_ct_window);
    return OAL_SUCC;
}


oal_uint32  dmac_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    mac_cfg_p2p_noa_param_stru  *pst_p2p_noa;
    oal_uint32                   ul_current_tsf_lo;
    mac_device_stru             *pst_mac_device;

    pst_p2p_noa = (mac_cfg_p2p_noa_param_stru *)puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(IS_P2P_GO(pst_mac_vap))
    {
#ifdef _PRE_WLAN_FEATURE_DBAC
        if (mac_is_dbac_running(pst_mac_device))
        {
            /* dbac������ go��noa��dbac�ӹ� */
            return OAL_SUCC;
        }
#endif

        /*�����GO, interval��Ϊbeacon interval*/
        pst_p2p_noa->ul_interval = pst_mac_device->ul_beacon_interval * 1024;
    }

    /* ��ȡdmac_vap �ṹ�� */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
	/* ��ȡhal_vap �ṹ�� */
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    /* �����������encap probe rsp,beacon*/
    if (pst_p2p_noa->uc_count != 0)
	{
        pst_dmac_vap->st_p2p_noa_param.uc_count = pst_p2p_noa->uc_count;
        pst_dmac_vap->st_p2p_noa_param.ul_duration = pst_p2p_noa->ul_duration;
        pst_dmac_vap->st_p2p_noa_param.ul_interval = pst_p2p_noa->ul_interval;
        hal_vap_tsf_get_32bit(pst_hal_vap, &ul_current_tsf_lo);
        pst_p2p_noa->ul_start_time += ul_current_tsf_lo;
        pst_dmac_vap->st_p2p_noa_param.ul_start_time = pst_p2p_noa->ul_start_time;
    }
    else
    {
    	if(IS_P2P_NOA_ENABLED(pst_dmac_vap))
        {
            /* �ָ����� */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        }

        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_noa:start_time:%d, duration:%d, interval:%d, count:%d\r\n",
                    pst_dmac_vap->st_p2p_noa_param.ul_start_time,
                    pst_dmac_vap->st_p2p_noa_param.ul_duration,
                    pst_dmac_vap->st_p2p_noa_param.ul_interval,
                    pst_dmac_vap->st_p2p_noa_param.uc_count);
    /* ����P2P noa �Ĵ��� */
    hal_vap_set_noa(pst_hal_vap,
                    pst_dmac_vap->st_p2p_noa_param.ul_start_time,
                    pst_dmac_vap->st_p2p_noa_param.ul_duration,
                    pst_dmac_vap->st_p2p_noa_param.ul_interval,
                    pst_dmac_vap->st_p2p_noa_param.uc_count);
    return OAL_SUCC;
}
OAL_STATIC oal_uint32  dmac_config_set_p2p_ps_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_p2p_stat_param_stru *pst_p2p_stat;
    hal_to_dmac_device_stru     *pst_hal_device;
    pst_p2p_stat = (mac_cfg_p2p_stat_param_stru *)puc_param;
    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_stat::ctrl:%d\r\n",
    //                pst_p2p_stat->uc_p2p_statistics_ctrl);
    /* ��ȡhal_device �ṹ�� */
    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    if (pst_p2p_stat->uc_p2p_statistics_ctrl == 0)
    {
        /* ���ͳ��ֵ */
        hal_clear_irq_stat(pst_hal_device);
    }
    else if (pst_p2p_stat->uc_p2p_statistics_ctrl == 1)
    {
        /* ��ӡͳ��ֵ */
        hal_show_irq_info(pst_hal_device, 0);
    }
    else
    {
        /* ����������� */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_stat:: wrong p2p ps ctrl vale \r\n");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM

extern oal_uint8 g_uc_sdt_enabled;
oal_uint32 dmac_config_set_ps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    //oal_uint32                      ul_dtim_period;
    mac_cfg_ps_mode_param_stru      *pst_ps_param;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                       uc_vap_ps_mode;
    oal_uint8                       uc_hw_ps_enabled;
    oal_uint8                       uc_sdt_enabled;
    oal_uint8                       uc_cfg_pm_mode_manual;
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        return OAL_SUCC;
    }

    pst_ps_param        = (mac_cfg_ps_mode_param_stru *)puc_param;
    uc_vap_ps_mode      = pst_ps_param->uc_vap_ps_mode;
    uc_hw_ps_enabled    = pst_ps_param->uc_hw_ps_enabled;
    uc_sdt_enabled      = pst_ps_param->uc_sdt_enabled;
    uc_cfg_pm_mode_manual  = pst_ps_param->uc_cfg_pm_mode_manual;

    /* SDT���� */
    if((1 == uc_sdt_enabled) || (0 == uc_sdt_enabled))
    {
        g_uc_sdt_enabled = uc_sdt_enabled ? 1 : 0;
    }

    /* device ƽ̨�͹��Ŀ��� */
    if ((1 == uc_hw_ps_enabled) || (0 == uc_hw_ps_enabled))
    {
        g_pm_switch = uc_hw_ps_enabled ? 1 : 0;
    }

    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_config_set_ps_mode::pst_sta_pm_handle null}");
        return OAL_SUCC;
    }

    /* STA PM ��״̬���� */
    dmac_sta_initialize_psm_globals(pst_sta_pm_handle);

    /* host�·��ֶ�������ģʽʱ��¼ */
    if ((1 == uc_cfg_pm_mode_manual) || (0 == uc_cfg_pm_mode_manual))
    {
        pst_dmac_vap->uc_cfg_pm_mode_manual = uc_cfg_pm_mode_manual;
        pst_dmac_vap->uc_cfg_manual_pm_mode = uc_vap_ps_mode;
    }

    /* �����ǰ�͹���ģʽ�������õ�ģʽһ����Э���ϲ����ظ����õ͹��� */
    if ((uc_vap_ps_mode == pst_sta_pm_handle->uc_vap_ps_mode) && (uc_hw_ps_enabled == pst_sta_pm_handle->en_hw_ps_enable))
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac_config_set_ps_mode:the same ps mode:[%d],hw_ps:[%d]}", pst_sta_pm_handle->uc_vap_ps_mode, pst_sta_pm_handle->en_hw_ps_enable);
        return  OAL_SUCC;
    }

    if (uc_vap_ps_mode < NUM_PS_MODE)
    {
        pst_sta_pm_handle->uc_vap_ps_mode   = uc_vap_ps_mode;
    }

    if ((1 == uc_hw_ps_enabled) || (0 == uc_hw_ps_enabled))
    {
        pst_sta_pm_handle->en_hw_ps_enable  = uc_hw_ps_enabled;
    }

    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac_config_set_ps_mode:ps mode:[%d],hw_ps:[%d]}", uc_vap_ps_mode, uc_hw_ps_enabled);

    hal_vap_set_psm_tsf_ctrl(pst_dmac_vap->pst_hal_vap, 0x3);

    //ul_dtim_period = mac_mib_get_dot11dtimperiod(&(pst_dmac_vap->st_vap_base_info));

    /* ��������DTIM�Ĵ�����ֵ */
    /*hal_set_psm_dtim_period(pst_dmac_vap->pst_hal_vap, ul_dtim_period, pst_sta_pm_handle->uc_listen_intervl_to_dtim_times,
                                pst_sta_pm_handle->en_receive_dtim); */

    /* �����ϵ�ʱ�������activity��ʱ�� */
    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
    }
    else
    {
		OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"sta_pm vap state:[%d],assoc aid is:[%d]",pst_dmac_vap->st_vap_base_info.en_vap_state,pst_dmac_vap->st_vap_base_info.us_sta_aid);
    }
    return OAL_SUCC;
}
#ifdef _PRE_PSM_DEBUG_MODE
#if 0
oal_void dmac_pm_info(dmac_vap_stru *pst_dmac_vap)
{
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;
    oal_uint8                        uc_doze_trans_flag;

    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_show_ps_info::pst_sta_pm_handle null}");
        return;
    }
    /* ��doze������ */
    uc_doze_trans_flag = (pst_sta_pm_handle->en_beacon_frame_wait) | (pst_sta_pm_handle->st_null_wait.en_doze_null_wait << 1) | (pst_sta_pm_handle->en_more_data_expected << 2)
                 | (pst_sta_pm_handle->st_null_wait.en_active_null_wait << 3) | (pst_sta_pm_handle->en_send_active_null_frame_to_ap << 4);

    OAL_IO_PRINT("beacon timout:[%d], tbtt:[%d],now state:[%d],  doze_trans_flag:[%d]\r\n",
                    pst_sta_pm_handle->st_psm_stat_info.ul_sta_beacon_timeout,
                    pst_sta_pm_handle->st_psm_stat_info.ul_sta_tbtt_times,
                    STA_GET_PM_STATE(pst_sta_pm_handle),
                    uc_doze_trans_flag);

    /* beacon timeout & tbtt �������� */
    pst_sta_pm_handle->st_psm_stat_info.ul_sta_beacon_timeout   =  0;
    pst_sta_pm_handle->st_psm_stat_info.ul_sta_tbtt_times       =  0;

}
#endif
extern  oal_uint8 g_pm_wlan_debug;
oal_uint32 dmac_show_ps_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ps_info_stru            *pst_ps_info;
    dmac_vap_stru                   *pst_dmac_vap;
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;
    oal_uint8                        uc_psm_info_enable;  //����psm��ά�����
    oal_uint8                        uc_psm_debug_mode;
    oal_uint8                        uc_doze_trans_flag;
    oal_uint32                       uiCnt;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_show_ps_info::pst_sta_pm_handle null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ps_info = (mac_cfg_ps_info_stru *)puc_param;
    uc_psm_info_enable = pst_ps_info->uc_psm_info_enable;
    uc_psm_debug_mode  = pst_ps_info->uc_psm_debug_mode;


    /* ��doze������ */
    uc_doze_trans_flag = (pst_sta_pm_handle->en_beacon_frame_wait) | (pst_sta_pm_handle->st_null_wait.en_doze_null_wait << 1) | (pst_sta_pm_handle->en_more_data_expected << 2)
                 | (pst_sta_pm_handle->st_null_wait.en_active_null_wait << 3) | (pst_sta_pm_handle->en_send_active_null_frame_to_ap << 4);

    if (OAL_TRUE == uc_psm_info_enable)
    {
        for(uiCnt= 0; uiCnt < PM_MSG_COUNT; uiCnt++)
        {
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{pm debug msg[%d] [%d]}",uiCnt,pst_sta_pm_handle->aul_pmDebugCount[uiCnt]);
        }

        OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"now pm state:[%d],ps mode:[%d],don't doze reason[0x%x],fe deepsleep enabled:[%d],lightsleep enabled:{%d]",5,
                             STA_GET_PM_STATE(pst_sta_pm_handle),pst_sta_pm_handle->uc_vap_ps_mode,uc_doze_trans_flag,g_deepsleep_fe_awake_cnt,g_lightsleep_fe_awake_cnt);

    }
    else
    {
        OAL_MEMZERO(&(pst_sta_pm_handle->aul_pmDebugCount), PM_MSG_COUNT  * OAL_SIZEOF(oal_uint32));
        g_deepsleep_fe_awake_cnt   = 0;
        g_lightsleep_fe_awake_cnt  = 0;
    }

    if (OAL_TRUE == uc_psm_debug_mode)
    {
        g_pm_wlan_debug = 1;
    }
    else
    {
        g_pm_wlan_debug = 0;
    }

    return OAL_SUCC;
}
#endif
oal_uint32 dmac_set_psm_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ps_param_stru           *pst_ps_param;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint16                       us_listen_interval;
    oal_uint16                       us_tbtt_offset;
    oal_uint16                       us_ext_tbtt_offset;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    pst_ps_param = (mac_cfg_ps_param_stru *)puc_param;
    us_listen_interval = pst_ps_param->us_listen_interval;
    us_tbtt_offset = pst_ps_param->us_tbtt_offset;
    us_ext_tbtt_offset = pst_ps_param->us_ext_tbtt_offset;

    /* listen interval */
    if (us_listen_interval != 0)
    {
        hal_set_psm_listen_interval(pst_dmac_vap->pst_hal_vap, us_listen_interval);
        hal_set_psm_listen_interval_count(pst_dmac_vap->pst_hal_vap, us_listen_interval);
    }

    /* INTER TBTT OFFSET */
    if (us_tbtt_offset != 0)
    {
        hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, us_tbtt_offset);
    }

    /* EXT TBTT OFFSET*/
    if (us_ext_tbtt_offset != 0)
    {
        hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, us_ext_tbtt_offset);
    }
    return OAL_SUCC;
}




oal_uint32 dmac_set_psm_vote(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ps_vote_stru            *pst_ps_vote;
    oal_uint8                       uc_sta0_vote;
    oal_uint8                       uc_sta1_vote;
    oal_uint8                       uc_sta2_vote;
    oal_uint8                       uc_ap_vote;
    oal_uint8                       uc_service_id;
    oal_uint8                       uc_vote = 0;

    pst_ps_vote = (mac_cfg_ps_vote_stru *)puc_param;
    uc_sta0_vote = pst_ps_vote->uc_sta0_vote;
    uc_sta1_vote = pst_ps_vote->uc_sta1_vote;
    uc_sta2_vote = pst_ps_vote->uc_sta2_vote;
    uc_ap_vote   = pst_ps_vote->uc_ap_vote;

    for (uc_service_id = WLAN_STA0_ID; uc_service_id < WLAN_PF_ID; uc_service_id++)
    {
        switch (uc_service_id)
        {
            case WLAN_STA0_ID:
                uc_vote = uc_sta0_vote;
            break;

            case WLAN_STA1_ID:
                uc_vote = uc_sta1_vote;
            break;

            case WLAN_STA2_ID:
                uc_vote = uc_sta2_vote;
            break;

            case WLAN_AP_ID:
                uc_vote = uc_ap_vote;
            break;

            default:
            break;

        }
        /* p2p DEVICE����ҪͶƱ */
        if (WLAN_STA2_ID == uc_service_id)
        {
            continue;
        }

        if (uc_vote < PM_WLAN_STS_NUM)
        {
            if ((PM_WLAN_DEEPSLEEP_PROCESS == uc_vote) || (PM_WLAN_LIGHTSLEEP_PROCESS == uc_vote))
            {
                /* ��˯ǳ˯�ŵ��ô˽ӿ� */
                PM_WLAN_PsmHandle(uc_service_id, uc_vote);
            }
            else if (PM_WLAN_SHUTDOWN_PROCESS == uc_vote)
            {
                PM_WLAN_PsmHandle(uc_service_id, PM_WLAN_DEEPSLEEP_PROCESS);

                /* ��ƽ̨ȥע���service id */
                //PM_WLAN_ServID_UnRegister(uc_service_id, pst_dmac_vap->pst_hal_vap->uc_mac_vap_id);
                //pst_hal_vap->uc_service_id  =  WLAN_ID_NUM;
            }
            else
            {
                PM_WLAN_PsmHandle(uc_service_id, uc_vote);
            }

            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "service id:[%d]vote:[%d]:%d\r\n", uc_service_id, uc_vote);
        }

    }

    return OAL_SUCC;
}
 oal_uint32 dmac_set_sta_pm_open(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
 {
    mac_cfg_ps_open_stru            *pst_ps_open_param;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                        uc_sta_pm_open;
    mac_device_stru                 *pst_device;
    oal_uint8                        uc_final_open_sta_pm;
    mac_cfg_ps_mode_param_stru       st_ps_param;

    pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    pst_device      = mac_res_get_dev(pst_mac_vap->uc_device_id);

    pst_ps_open_param = (mac_cfg_ps_open_stru *)puc_param;
    uc_sta_pm_open = pst_ps_open_param->uc_sta_pm_open;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"vap mode is:[%d] not sta",pst_mac_vap->en_vap_mode);
        return OAL_SUCC;
    }

    /* ��¼��dbac�л��ĵ͹���״̬ */
    if (uc_sta_pm_open  < MAC_STA_DBAC_OFF_PM)
    {
        pst_dmac_vap->uc_sta_pm_on = uc_sta_pm_open;
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"sta_pm [%d] want open/close pm",uc_sta_pm_open);

    /* DBAC running�²������͹��� dbac�رպ���ٿ� */
    if((OAL_TRUE == mac_is_dbac_running(pst_device)) && (OAL_TRUE == uc_sta_pm_open))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"sta_pm set pm on but dbac is running");
        return OAL_SUCC;
    }

    st_ps_param.uc_cfg_pm_mode_manual = 0xFF;    //openʱ�������ֶ���

    /* open ���������� */
    if (uc_sta_pm_open >= MAC_STA_PM_OPEN_BUTT)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"sta_pm set pm on open param [%d]wrong",uc_sta_pm_open);
        return OAL_SUCC;
    }

    /* �����λ 0�� 1�� */
    uc_final_open_sta_pm = uc_sta_pm_open & (pst_dmac_vap->uc_sta_pm_on);

     /* ���͹��� Ĭ��fastģʽ */
    if (uc_final_open_sta_pm)
    {
        /*�ֶ��������˽���ģʽ��ʹ��֮ǰ�����ģʽ */
        st_ps_param.uc_vap_ps_mode = (pst_dmac_vap->uc_cfg_pm_mode_manual) ? pst_dmac_vap->uc_cfg_manual_pm_mode : 1;

        st_ps_param.uc_hw_ps_enabled   = 1;
        st_ps_param.uc_sdt_enabled     = 1;

        if(WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            /* ֻ��staģʽ����Ҫ����ϵͳ�͹�����������tsf��tbtt offset */
            hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, DMAC_DEFAULT_EXT_TBTT_OFFSET);
        }

        mac_mib_set_powermanagementmode(pst_mac_vap, WLAN_MIB_PWR_MGMT_MODE_PWRSAVE);

        dmac_config_set_ps_mode(pst_mac_vap, OAL_SIZEOF(mac_cfg_ps_mode_param_stru), (oal_uint8 *)&st_ps_param);

    }

    /* ֻ�ر�Э��͹���,ƽ̨��device�͹���Ĭ�Ͽ� */
    else
    {
        st_ps_param.uc_vap_ps_mode     = 0;
        st_ps_param.uc_hw_ps_enabled   = 1;
        st_ps_param.uc_sdt_enabled     = 1;

        mac_mib_set_powermanagementmode(pst_mac_vap, WLAN_MIB_PWR_MGMT_MODE_ACTIVE);

        dmac_config_set_ps_mode(pst_mac_vap, OAL_SIZEOF(mac_cfg_ps_mode_param_stru), (oal_uint8 *)&st_ps_param);
    }

    return OAL_SUCC;
 }


#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
/*****************************************************************************
 �� �� ��  : dmac_config_set_mips
 ��������  :
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_mips(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_mips_type_param_stru      *pst_mips_type_param;

    pst_mips_type_param = (oal_mips_type_param_stru *)puc_param;

    switch (pst_mips_type_param->l_mips_type)
    {
        case OAL_MIPS_TX:
        {
            if (OAL_SWITCH_ON == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_OFF == g_mips_tx_statistic.en_switch)
                {
                    oal_profiling_mips_tx_init();
                    oal_profiling_enable_cycles();

                    g_mips_tx_statistic.en_switch = OAL_SWITCH_ON;
                    g_mips_tx_statistic.uc_flag |= BIT0;
                }
            }
            else if (OAL_SWITCH_OFF == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_ON == g_mips_tx_statistic.en_switch)
                {
                    oal_profiling_disable_cycles();

                    g_mips_tx_statistic.en_switch = OAL_SWITCH_OFF;
                }
            }
        }
        break;

        case OAL_MIPS_RX:
        {
            if (OAL_SWITCH_ON == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_OFF == g_mips_rx_statistic.en_switch)
                {
                    oal_profiling_mips_rx_init();
                    oal_profiling_enable_cycles();

                    g_mips_rx_statistic.en_switch = OAL_SWITCH_ON;
                }
            }
            else if (OAL_SWITCH_OFF == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_ON == g_mips_rx_statistic.en_switch)
                {
                    oal_profiling_disable_cycles();

                    g_mips_rx_statistic.en_switch = OAL_SWITCH_OFF;
                }
            }
        }
        break;

        default:
        {
            OAL_IO_PRINT("dmac_config_set_mips: mips type is wrong!\r\n");
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_show_mips
 ��������  :
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_show_mips(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32 l_mips_type;

    l_mips_type = *((oal_int32 *)puc_param);

    switch (l_mips_type)
    {
        case OAL_MIPS_TX:
        {
            oal_profiling_tx_mips_show();
        }
        break;

        case OAL_MIPS_RX:
        {
            oal_profiling_rx_mips_show();
        }
        break;

        default:
        {
            OAL_IO_PRINT("dmac_config_show_mips: mips type is wrong!\r\n");
        }
    }

    return OAL_SUCC;
}
#endif


OAL_STATIC oal_uint32 dmac_config_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_nss_stru  *pst_user_nss;
    mac_user_stru      *pst_mac_user;

    pst_user_nss = (mac_user_nss_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_nss->us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_spatial_stream::mac user(idx=%d) is null!", pst_user_nss->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_num_spatial_stream(pst_mac_user, pst_user_nss->uc_num_spatial_stream);
    mac_user_set_avail_num_spatial_stream(pst_mac_user, pst_user_nss->uc_avail_num_spatial_stream);
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_config_opmode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY

    mac_user_opmode_stru  *pst_user_opmode;
    mac_user_stru         *pst_mac_user;

    pst_user_opmode = (mac_user_opmode_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_opmode->us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_opmode::mac user(idx=%d) is null!", pst_user_opmode->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_avail_bf_num_spatial_stream(pst_mac_user, pst_user_opmode->uc_avail_bf_num_spatial_stream);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* �����㷨���Ӻ��� */
        dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    mac_user_set_avail_num_spatial_stream(pst_mac_user, pst_user_opmode->uc_avail_num_spatial_stream);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* �����㷨���Ӻ��� */;
        dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    mac_user_set_bandwidth_info(pst_mac_user, pst_user_opmode->en_avail_bandwidth, pst_user_opmode->en_cur_bandwidth);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* �����㷨���Ӻ��� */;
        dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);
    }
#endif
    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/*****************************************************************************
 �� �� ��  : dmac_config_enable_arp_offload
 ��������  : ����ARP offload��Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_enable_arp_offload(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru *pst_dmac_vap  = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap->en_arp_offload_switch = *(oal_switch_enum_uint8 *)puc_param;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_ip_add
 ��������  : ����IP��ַ
 �������  : mac_vap_stru *pst_mac_vap
             dmac_ip_addr_config_stru *pst_ip_addr_info
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ip_add(dmac_vap_stru *pst_dmac_vap, dmac_ip_addr_config_stru *pst_ip_addr_info)
{
    mac_vap_stru              *pst_mac_vap       = &pst_dmac_vap->st_vap_base_info;
    oal_uint32                 ul_loop;
    oal_bool_enum_uint8        en_comp           = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap->pst_ip_addr_info))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::IP record array memory is not alloced.}");
        return OAL_FAIL;
    }

    if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == *(oal_uint32 *)(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr)))
            {
                en_comp = OAL_TRUE; /* ������� */
                oal_memcopy(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE);
            }
            else if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE))
            {
                if (OAL_TRUE == en_comp)
                {
                    oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, 0, OAL_IPV4_ADDR_SIZE);
                }
                else
                {
                    en_comp = OAL_TRUE;
                }
            }
        }
    }
    else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && OAL_IPV6_IS_UNSPECIFIED_ADDR(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))
            {
                en_comp = OAL_TRUE; /* ������� */
                oal_memcopy(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE);
            }
            else if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE))
            {
                if (OAL_TRUE == en_comp)
                {
                    oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, 0, OAL_IPV6_ADDR_SIZE);
                }
                else
                {
                    en_comp = OAL_TRUE;
                }
            }
        }
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::IP type[%d] is wrong.}", pst_ip_addr_info->en_type);
        return OAL_FAIL;
    }

    if (OAL_FALSE == en_comp)
    {
        if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
        {
            OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::Add IPv4 address[%d.X.X.%d] failed, there is no empty array.}",
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[0],
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[3]);
        }
        else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
        {
            OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::Add IPv6 address[%04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x] failed, there is no empty array.}",
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[0]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[1]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[6]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[7]));
        }
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_ip_del
 ��������  : ɾ��IP��ַ
 �������  : mac_vap_stru *pst_mac_vap
             dmac_ip_addr_config_stru *pst_ip_addr_info
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ip_del(dmac_vap_stru *pst_dmac_vap, dmac_ip_addr_config_stru *pst_ip_addr_info)
{
    mac_vap_stru              *pst_mac_vap       = &pst_dmac_vap->st_vap_base_info;
    oal_uint32                 ul_loop;
    oal_bool_enum_uint8        en_comp           = OAL_FALSE;

    if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE)))
            {
                en_comp = OAL_TRUE; /* ɾ����� */
                oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, 0, OAL_IPV4_ADDR_SIZE);
                break;
            }
        }
    }
    else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE)))
            {
                en_comp = OAL_TRUE; /* ɾ����� */
                oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, 0, OAL_IPV6_ADDR_SIZE);
                break;
            }
        }
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::IP type[%d] is wrong.}", pst_ip_addr_info->en_type);
        return OAL_FAIL;
    }

    if (OAL_FALSE == en_comp)
    {
        if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::Delete IPv4 address[%d.X.X.%d] failed, there is not the IP address.}",
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[0],
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[3]);
        }
        else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
        {
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::Delete IPv6 address[%04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x] failed, there is not the IP address.}",
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[0]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[1]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[6]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[7]));
        }
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_ip_addr
 ��������  : ����IP��ַ��Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_set_ip_addr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru             *pst_dmac_vap      = (dmac_vap_stru *)pst_mac_vap;
    dmac_ip_addr_config_stru  *pst_ip_addr_info  = (dmac_ip_addr_config_stru *)puc_param;

    switch (pst_ip_addr_info->en_oper)
    {
        case DMAC_IP_ADDR_ADD:
        {
            return dmac_config_ip_add(pst_dmac_vap, pst_ip_addr_info);
        }

        case DMAC_IP_ADDR_DEL:
        {
            return dmac_config_ip_del(pst_dmac_vap, pst_ip_addr_info);
        }

        default:
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_ip_addr::IP operation[%d] is wrong.}", pst_ip_addr_info->en_oper);
            break;
        }
    }
    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : dmac_config_show_arpoffload_info
 ��������  : �鿴Device��ARPOFFLOADά����Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_show_arpoffload_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_arpoffload_info_stru    *pst_ps_info;
    mac_device_stru                 *pst_mac_dev;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                        uc_show_ip_addr;
    oal_uint8                        uc_show_arpoffload_info;
    oal_uint32                       ul_loop;

    pst_mac_dev  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    pst_ps_info                 = (mac_cfg_arpoffload_info_stru *)puc_param;
    uc_show_ip_addr             = pst_ps_info->uc_show_ip_addr;
    uc_show_arpoffload_info     = pst_ps_info->uc_show_arpoffload_info;
    if ((OAL_PTR_NULL == pst_mac_dev) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_ps_info))
    {
        OAM_ERROR_LOG3(0, OAM_SF_CFG, "{dmac_config_show_arpoffload_info:: pointer is null,pst_mac_de[0x%x],vpst_mac_vap[0x%x],puc_param[0x%x]",pst_mac_dev,pst_dmac_vap,pst_ps_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (1 == uc_show_ip_addr)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_show_ip_addr::IPv4 index[%d]: %d.X.X.%d.}",
                             ul_loop,
                             pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr[0],
                             pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr[3]);
        }

        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            OAM_WARNING_LOG_ALTER(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_show_ip_addr::IPv6 index[%d]: %04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x.}",
                                  5,
                                  ul_loop,
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[0]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[1]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[6]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[7]));
        }
    }

    if (1 == uc_show_arpoffload_info)
    {
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"suspend state:[%d],arpofflad drop frame:[%d],send arp rsp:[%d]",pst_mac_dev->uc_in_suspend,g_ul_arpoffload_drop_frame,g_ul_arpoffload_send_arprsp);
    }
    /* ͳ������ */
    else if (0 == uc_show_arpoffload_info)
    {
        g_ul_arpoffload_drop_frame  = 0;
        g_ul_arpoffload_send_arprsp = 0;
    }
    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
oal_uint32  dmac_config_roam_enable(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                       uc_roaming_mode;
    mac_device_stru                *pst_mac_device;
    mac_user_stru                  *pst_mac_user;


    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_roam_enable::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_roaming_mode  = (oal_uint8)*puc_param;
    if ((uc_roaming_mode == 1) && (pst_mac_vap->en_vap_state == MAC_VAP_STATE_UP))
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        /* ֪ͨԭap�������״̬ */
        dmac_send_null_frame_to_ap((dmac_vap_stru *)pst_mac_vap, 1, OAL_FALSE);
#endif
        pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);


        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY,
                           "{dmac_config_roam_enable::pst_mac_user[%d] null.}", pst_mac_vap->uc_assoc_vap_id);
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* ɾ��tid�����е�������Ϣ */
        dmac_tid_clear(pst_mac_user, pst_mac_device);
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable:: [MAC_VAP_STATE_UP]->[MAC_VAP_STATE_ROAMING]}");
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_ROAMING;
    }
    else if ((uc_roaming_mode == 0) && (pst_mac_vap->en_vap_state == MAC_VAP_STATE_ROAMING))
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        /* ֪ͨԭap�˳�����״̬ */
        dmac_send_null_frame_to_ap((dmac_vap_stru *)pst_mac_vap, 0, OAL_FALSE);
#endif
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable:: [MAC_VAP_STATE_ROAMING]->[MAC_VAP_STATE_UP]}");
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_UP;
    }
    else
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable::unexpect state[%d] or mode[%d]}",
                       pst_mac_vap->en_vap_state, uc_roaming_mode);
    }
    return OAL_SUCC;
}
oal_uint32  dmac_config_set_roam_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8          uc_roam_trigger_type;
    dmac_vap_stru     *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{dmac_config_set_roam_trigger::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_roam_trigger_type  = (oal_uint8)*puc_param;
    pst_dmac_vap          = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap->st_roam_trigger.ul_rssi_ignore = (oal_uint32)uc_roam_trigger_type;

    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                    "{dmac_config_set_roam_trigger, ul_rssi_ignore = %d}", (oal_uint32)uc_roam_trigger_type);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_roam_hmac_sync_dmac
 ��������  : ����ģʽ�¸��� hmac info �� dmac
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��25��
    ��    ��   : l00350000
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_roam_hmac_sync_dmac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_user_stru                   *pst_mac_user;
    mac_h2d_roam_sync_stru          *pst_sync_param = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_roam_hmac_sync_dmac::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,
                       "{dmac_config_roam_hmac_sync_dmac::pst_mac_user[%d] null.}", pst_mac_vap->uc_assoc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_sync_param = (mac_h2d_roam_sync_stru *)puc_param;

    /* �ָ�ԭ��bss�����Ϣ */
    pst_mac_vap->us_sta_aid = pst_sync_param->us_sta_aid;
    oal_memcopy(&(pst_mac_vap->st_channel), &pst_sync_param->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&(pst_mac_user->st_cap_info), &pst_sync_param->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy(&(pst_mac_user->st_key_info), &pst_sync_param->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));
    oal_memcopy(&(pst_mac_user->st_user_tx_info),&pst_sync_param->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));

    /* �����û�8021x�˿ںϷ��Ե�״̬Ϊ�Ϸ� */
    mac_user_set_port(pst_mac_user, OAL_TRUE);

    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_hmac_sync_dmac:: Sync Done!!}");

    return OAL_SUCC;
}

#endif  //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST

OAL_STATIC oal_uint32 dmac_config_enable_2040bss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru           *pst_mac_device;
    oal_bool_enum_uint8        en_2040bss_switch;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_enable_2040bss:: pointer is null,pst_mac_vap[%d], puc_param[%d] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_enable_2040bss::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_2040bss_switch = (*puc_param == 0) ? OAL_FALSE : OAL_TRUE;
    mac_set_2040bss_switch(pst_mac_device, en_2040bss_switch);

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_enable_2040bss::set 2040bss switch[%d].}", en_2040bss_switch);

    return OAL_SUCC;
}
#endif /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32 dmac_config_suspend_action_sync(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru           *pst_mac_device;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_suspend_action_sync:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_suspend_action_sync::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device->uc_in_suspend = *puc_param;
    return OAL_SUCC;
}
#endif
/*****************************************************************************
    HMAC��DMAC����ͬ���¼�����������
*****************************************************************************/
OAL_STATIC OAL_CONST dmac_config_syn_stru g_ast_dmac_config_syn[] =
{
    /* ͬ��ID                    ����2���ֽ�            �������� */
    {WLAN_CFGID_BSS_TYPE,           {0, 0},         dmac_config_set_bss_type},
    {WLAN_CFGID_ADD_VAP,            {0, 0},         dmac_config_add_vap},
    {WLAN_CFGID_START_VAP,          {0, 0},         dmac_config_start_vap},
    {WLAN_CFGID_DEL_VAP,            {0, 0},         dmac_config_del_vap},
    {WLAN_CFGID_DOWN_VAP,           {0, 0},         dmac_config_down_vap},
    {WLAN_CFGID_MODE,               {0, 0},         dmac_config_set_mode},
    {WLAN_CFGID_CURRENT_CHANEL,     {0, 0},         dmac_config_set_freq},
    {WLAN_CFGID_STATION_ID,         {0, 0},         dmac_config_set_mac_addr},
    {WLAN_CFGID_CONCURRENT,         {0, 0},         dmac_config_set_concurrent},
    {WLAN_CFGID_SSID,               {0, 0},         dmac_config_set_ssid},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SHORTGI,            {0, 0},         dmac_config_set_shortgi},   /* hi1102-cb add sync */
    {WLAN_CFGID_VAP_STATE_SYN,      {0, 0},         dmac_config_vap_state_syn},
    {WLAN_CFGID_REGDOMAIN_PWR,      {0, 0},         dmac_config_set_regdomain_pwr},
    {WLAN_CFGID_SET_STBC_CAP,       {0, 0},         dmac_config_set_stbc_cap},
    {WLAN_CFGID_SET_LDPC_CAP,       {0, 0},         dmac_config_set_ldpc_cap},
#endif
    {WLAN_CFGID_SCAN_ABORT,         {0, 0},         dmac_config_scan_abort},
    {WLAN_CFGID_STOP_SCHED_SCAN,    {0, 0},         dmac_config_stop_sched_scan},
    {WLAN_CFGID_USER_ASOC_STATE_SYN,{0, 0},         dmac_config_user_asoc_state_syn},
    {WLAN_CFGID_USER_RATE_SYN,      {0, 0},         dmac_config_user_rate_info_syn},
    {WLAN_CFGID_USR_INFO_SYN,       {0, 0},         dmac_config_sta_usr_info_syn},
    {WLAN_CFGID_STA_VAP_INFO_SYN,   {0, 0},         dmac_config_vap_info_syn},

#ifdef _PRE_WLAN_FEATURE_TXOPPS
    {WLAN_CFGID_STA_TXOP_AID,         {0, 0},      dmac_txopps_set_machw_partialaid_sta},
#endif

    {WLAN_CFGID_SHORT_PREAMBLE,     {0, 0},         dmac_config_set_shpreamble},
#ifdef _PRE_WLAN_FEATURE_MONITOR
    {WLAN_CFGID_ADDR_FILTER,        {0, 0},         dmac_config_set_addr_filter},
#endif
    {WLAN_CFGID_PROT_MODE,          {0, 0},         dmac_config_set_prot_mode},
    {WLAN_CFGID_BEACON_INTERVAL,    {0, 0},         dmac_config_set_bintval},
    {WLAN_CFGID_NO_BEACON,          {0, 0},         dmac_config_set_nobeacon},
    {WLAN_CFGID_TX_CHAIN,           {0, 0},         dmac_config_set_txchain},
    {WLAN_CFGID_RX_CHAIN,           {0, 0},         dmac_config_set_rxchain},
    {WLAN_CFGID_TX_POWER,           {0, 0},         dmac_config_set_txpower},
    {WLAN_CFGID_DTIM_PERIOD,        {0, 0},         dmac_config_set_dtimperiod},
    {WLAN_CFGID_GET_MPDU_NUM,       {0, 0},         dmac_config_get_mpdu_num},
#if 0
    {WLAN_CFGID_OTA_SWITCH,         {0, 0},         dmac_config_ota_switch},
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    {WLAN_CFGID_START_DPD,         {0, 0},          dmac_config_start_dpd},
#endif
#ifdef _PRE_WLAN_CHIP_TEST
    {WLAN_CFGID_SET_BEACON_OFFLOAD_TEST, {0, 0},    dmac_config_beacon_offload_test},
#endif
    {WLAN_CFGID_OTA_BEACON_SWITCH,  {0, 0},         dmac_config_ota_beacon_switch},
    {WLAN_CFGID_OTA_RX_DSCR_SWITCH, {0, 0},         dmac_config_ota_rx_dscr_switch},
    {WLAN_CFGID_SET_ALL_OTA,        {0, 0},         dmac_config_set_all_ota},
    {WLAN_CFGID_OAM_OUTPUT_TYPE,    {0, 0},         dmac_config_oam_output},
    {WLAN_CFGID_PROBE_SWITCH,       {0, 0},         dmac_config_probe_switch},
    {WLAN_CFGID_80211_MCAST_SWITCH, {0, 0},         dmac_config_80211_mcast_switch},
    {WLAN_CFGID_RSSI_SWITCH,        {0, 0},         dmac_config_rssi_switch},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
	{WLAN_CFGID_REPORT_VAP_INFO,         {0, 0},    dmac_config_report_vap_info},
    {WLAN_CFGID_80211_UCAST_SWITCH, {0, 0},         dmac_config_80211_ucast_switch},
#endif /* DMAC_OFFLOAD */


#ifdef _PRE_WLAN_FEATURE_UAPSD
    {WLAN_CFGID_UAPSD_EN,           {0, 0},         dmac_config_set_uapsden},
    {WLAN_CFGID_UAPSD_DEBUG,        {0, 0},         dmac_config_uapsd_debug},
    {WLAN_CFGID_UAPSD_UPDATE,       {0, 0},         dmac_config_set_uapsd_update},
#endif
    {WLAN_CFGID_EDCA_TABLE_CWMIN,           {0, 0},         dmac_config_set_cwmin},
    {WLAN_CFGID_EDCA_TABLE_CWMAX,           {0, 0},         dmac_config_set_cwmax},
    {WLAN_CFGID_EDCA_TABLE_AIFSN,           {0, 0},         dmac_config_set_aifsn},
    {WLAN_CFGID_EDCA_TABLE_TXOP_LIMIT,      {0, 0},         dmac_config_set_txop_limit},
    {WLAN_CFGID_EDCA_TABLE_MSDU_LIFETIME,   {0, 0},         dmac_config_set_msdu_lifetime},
    {WLAN_CFGID_EDCA_TABLE_MANDATORY,       {0, 0},         dmac_config_set_edca_mandatory},
    {WLAN_CFGID_QEDCA_TABLE_CWMIN,          {0, 0},         dmac_config_set_qap_cwmin},
    {WLAN_CFGID_QEDCA_TABLE_CWMAX,          {0, 0},         dmac_config_set_qap_cwmax},
    {WLAN_CFGID_QEDCA_TABLE_AIFSN,          {0, 0},         dmac_config_set_qap_aifsn},
    {WLAN_CFGID_QEDCA_TABLE_TXOP_LIMIT,     {0, 0},         dmac_config_set_qap_txop_limit},
    {WLAN_CFGID_QEDCA_TABLE_MSDU_LIFETIME,  {0, 0},         dmac_config_set_qap_msdu_lifetime},
    {WLAN_CFGID_QEDCA_TABLE_MANDATORY,      {0, 0},         dmac_config_set_qap_edca_mandatory},

    {WLAN_CFGID_VAP_INFO,                   {0, 0},         dmac_config_vap_info},
    {WLAN_CFGID_ADD_USER,                   {0, 0},         dmac_config_add_user},
    {WLAN_CFGID_DEL_USER,                   {0, 0},         dmac_config_del_user},
    {WLAN_CFGID_PAUSE_TID,                  {0, 0},         dmac_config_pause_tid},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_DUMP_TIEMR,                 {0, 0},         dmac_config_dump_timer},
#endif
    {WLAN_CFGID_SET_USER_VIP,               {0, 0},         dmac_config_set_user_vip},
    {WLAN_CFGID_SET_VAP_HOST,               {0, 0},         dmac_config_set_vap_host},
    {WLAN_CFGID_SEND_BAR,                   {0, 0},         dmac_config_send_bar},
    {WLAN_CFGID_RESET_HW,                   {0, 0},         dmac_config_reset_hw},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_RESET_HW_OPERATE,           {0, 0},         dmac_reset_sys_event},
#endif
    {WLAN_CFGID_DUMP_RX_DSCR,               {0, 0},         dmac_config_dump_rx_dscr},
    {WLAN_CFGID_DUMP_TX_DSCR,               {0, 0},         dmac_config_dump_tx_dscr},
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    {WLAN_CFGID_USR_THRPUT_STAT,            {0, 0},         dmac_config_report_thrput_stat},
#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    {WLAN_CFGID_TXOP_PS_MACHW,              {0, 0},         dmac_config_set_txop_ps_machw},
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    {WLAN_CFGID_BTCOEX_STATUS_PRINT,        {0, 0},         dmac_config_print_btcoex_status},
#endif
#ifdef _PRE_WLAN_DFT_STAT
    {WLAN_CFGID_PHY_STAT_EN,                {0, 0},         dmac_config_set_phy_stat_en},
    {WLAN_CFGID_DBB_ENV_PARAM,              {0, 0},         dmac_config_dbb_env_param},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    {WLAN_CFGID_USR_QUEUE_STAT,             {0, 0},         dmac_config_usr_queue_stat},
#endif
    {WLAN_CFGID_VAP_STAT,                   {0, 0},         dmac_config_report_vap_stat},
    {WLAN_CFGID_ALL_STAT,                   {0, 0},         dmac_config_report_all_stat},
#endif

    {WLAN_CFGID_SET_LOG_LEVEL,              {0, 0},         dmac_config_set_log_level},
    {WLAN_CFGID_SET_FEATURE_LOG,            {0, 0},         dmac_config_set_feature_log},

    /*wpa-wpa2*/
    {WLAN_CFGID_ADD_KEY,           {0, 0},              dmac_config_11i_add_key},
	//{WLAN_CFGID_ADD_KEY_KEY,       {0, 0},              dmac_config_11i_add_key},
    //{WLAN_CFGID_ADD_KEY_SEQ,       {0, 0},              dmac_config_11i_add_key_seq},
    {WLAN_CFGID_REMOVE_KEY,        {0, 0},              dmac_config_11i_remove_key},
    {WLAN_CFGID_DEFAULT_KEY,       {0, 0},              dmac_config_11i_set_default_key},
    //{WLAN_CFGID_ADD_WEP_KEY,       {0, 0},              dmac_config_wep_add_key},
    {WLAN_CFGID_ADD_WEP_ENTRY,     {0, 0},              dmac_config_wep_add_entry},
    {WLAN_CFGID_REMOVE_WEP_KEY,    {0, 0},              dmac_config_wep_remove_key},
	{WLAN_CFGID_CONNECT_REQ,        {0, 0},             dmac_config_connect},

#ifdef _PRE_WLAN_FEATURE_WAPI
    {WLAN_CFGID_ADD_WAPI_KEY,       {0, 0},             dmac_config_wapi_add_key},
#endif

    {WLAN_CFGID_INIT_SECURTIY_PORT, {0, 0},             dmac_config_11i_init_port},
    {WLAN_CFGID_ALG,               {0, 0},              dmac_config_alg},
    {WLAN_CFGID_DUMP_BA_BITMAP,    {0, 0},              dmac_config_dump_ba_bitmap},
    {WLAN_CFGID_DUMP_ALL_RX_DSCR,  {0, 0},              dmac_config_dump_all_rx_dscr},
    {WLAN_CFGID_USER_INFO,         {0, 0},              dmac_config_user_info},
    {WLAN_CFGID_SET_DSCR,          {0, 0},              dmac_config_set_dscr},
    {WLAN_CFGID_COUNTRY,           {0, 0},              dmac_config_set_country},
#ifdef _PRE_WLAN_FEATURE_DFS
    {WLAN_CFGID_COUNTRY_FOR_DFS,   {0, 0},              dmac_config_set_country_for_dfs},
#endif
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    {WLAN_CFGID_SET_RATE,          {0, 0},              dmac_config_set_rate},
    {WLAN_CFGID_SET_MCS,           {0, 0},              dmac_config_set_mcs},
    {WLAN_CFGID_SET_MCSAC,         {0, 0},              dmac_config_set_mcsac},
    {WLAN_CFGID_SET_NSS,           {0, 0},              dmac_config_set_nss},
    {WLAN_CFGID_SET_RFCH,          {0, 0},              dmac_config_set_rfch},
    {WLAN_CFGID_SET_BW,            {0, 0},              dmac_config_set_bw},
    {WLAN_CFGID_SET_ALWAYS_TX,     {0, 0},              dmac_config_set_always_tx},
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    {WLAN_CFGID_SET_ALWAYS_TX_1102,{0, 0},              dmac_config_set_always_tx_1102},
#endif
    {WLAN_CFGID_SET_ALWAYS_RX,     {0, 0},              dmac_config_set_always_rx},
    {WLAN_CFGID_GET_THRUPUT,       {0, 0},              dmac_config_get_thruput},
    {WLAN_CFGID_SET_FREQ_SKEW,     {0, 0},              dmac_config_set_freq_skew},
    {WLAN_CFGID_ADJUST_PPM,        {0, 0},              dmac_config_adjust_ppm},
    {WLAN_CFGID_REG_INFO,          {0, 0},              dmac_config_reg_info},
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
    {WLAN_CFGID_SDIO_FLOWCTRL,     {0, 0},              dmac_config_sdio_flowctrl},
#endif
    {WLAN_CFGID_REG_WRITE,         {0, 0},              dmac_config_reg_write},
    {WLAN_CFGID_CFG80211_SET_CHANNEL,      {0, 0},      dmac_config_set_channel},

    {WLAN_CFGID_CFG80211_CONFIG_BEACON,    {0, 0},      dmac_config_set_beacon},

    {WLAN_CFGID_BEACON_CHAIN_SWITCH,       {0, 0},      dmac_config_beacon_chain_switch},
#if 0
    {WLAN_CFGID_TDLS_PROHI,                {0, 0},      dmac_config_tdls_prohibited},
    {WLAN_CFGID_TDLS_CHASWI_PROHI,         {0, 0},      dmac_config_tdls_channel_switch_prohibited},
#endif
    {WLAN_CFGID_HIDE_SSID,                 {0, 0},      dmac_config_hide_ssid},
    {WLAN_CFGID_WMM_SWITCH,                {0, 0},      dmac_config_wmm_switch},

#ifdef _PRE_WLAN_PERFORM_STAT
    {WLAN_CFGID_PFM_STAT,                  {0, 0},      dmac_config_pfm_stat},
    {WLAN_CFGID_PFM_DISPLAY,               {0, 0},      dmac_config_pfm_display},
#endif

#ifdef _PRE_WLAN_CHIP_TEST

    {WLAN_CFGID_LPM_TX_PROBE_REQUEST,     {0, 0},       dmac_config_lpm_tx_probe_request},
    {WLAN_CFGID_LPM_CHIP_STATE,     {0, 0},             dmac_config_set_lpm_chip_state},
    {WLAN_CFGID_LPM_SOC_MODE,      {0, 0},              dmac_config_set_lpm_soc_mode},
    {WLAN_CFGID_LPM_PSM_PARAM,      {0, 0},             dmac_config_set_lpm_psm_param},
    {WLAN_CFGID_LPM_SMPS_MODE,      {0, 0},             dmac_config_set_lpm_smps_mode},
    {WLAN_CFGID_LPM_SMPS_STUB,      {0, 0},             dmac_config_set_lpm_smps_stub},
    {WLAN_CFGID_LPM_TXOP_PS_SET,    {0, 0},             dmac_config_set_lpm_txop_ps},
    {WLAN_CFGID_LPM_TXOP_TX_STUB,   {0, 0},             dmac_config_set_lpm_txop_ps_tx_stub},
    {WLAN_CFGID_LPM_WOW_EN,         {0, 0},             dmac_config_set_lpm_wow_en},
    {WLAN_CFGID_SEND_FRAME,         {0, 0},             dmac_config_send_frame},
    {WLAN_CFGID_SET_RX_PN_REG,      {0, 0},             dmac_config_set_rx_pn},
    {WLAN_CFGID_SET_SOFT_RETRY,     {0, 0},             dmac_config_set_soft_retry},
    {WLAN_CFGID_OPEN_ADDR4,         {0, 0},             dmac_config_open_addr4},
    {WLAN_CFGID_OPEN_WMM_TEST,      {0, 0},             dmac_config_open_wmm_test},
    {WLAN_CFGID_CHIP_TEST_OPEN,     {0, 0},             dmac_config_chip_test_open},
    {WLAN_CFGID_SET_COEX,           {0, 0},             dmac_config_set_coex},
    {WLAN_CFGID_DFX_SWITCH,         {0, 0},             dmac_config_set_dfx},
    {WLAN_CFGID_REMOVE_LUT,         {0, 0},             dmac_config_remove_user_lut},
    {WLAN_CFGID_SEND_PSPOLL,        {0, 0},             dmac_config_send_pspoll},
    {WLAN_CFGID_SEND_NULLDATA,      {0, 0},             dmac_config_send_nulldata},
    {WLAN_CFGID_CLEAR_ALL_STAT,    {0, 0},              dmac_config_clear_all_stat},

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    {WLAN_CFGID_PMF_ENABLE,         {0, 0},             dmac_config_enable_pmf},
#endif
#endif
    {WLAN_CFGID_CHECK_FEM_PA,        {0, 0},            dmac_config_get_fem_pa_status},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SET_MIB,            {0, 0},             dmac_config_set_mib},
    {WLAN_CFGID_SET_OBSS_MIB,       {0, 0},             dmac_config_set_obss_mib},
#endif


#ifdef _PRE_SUPPORT_ACS
    {WLAN_CFGID_ACS_PARAM,          {0, 0},             dmac_acs_recv_msg},
    {WLAN_CFGID_ACS_CONFIG,         {0, 0},             dmac_config_acs},
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
    {WLAN_CFGID_RADARTOOL,          {0, 0},             dmac_config_dfs_radartool},
#endif

    {WLAN_CFGID_SET_RTS_PARAM,      {0, 0},             dmac_config_set_rts_param},

    {WLAN_CFGID_UPDTAE_PROT_TX_PARAM,{0, 0},            dmac_config_update_protection_tx_param},
    {WLAN_CFGID_SET_PROTECTION,      {0, 0},            dmac_config_set_protection},

    {WLAN_CFGID_GET_VERSION,         {0, 0},            dmac_config_get_version},
    {WLAN_CFGID_RX_FCS_INFO,         {0, 0},            dmac_config_rx_fcs_info},
    {WLAN_CFGID_SET_THRUPUT_BYPASS,  {0, 0},            dmac_config_set_thruput_bypass},
#ifdef _PRE_WLAN_DFT_STAT
    {WLAN_CFGID_SET_PERFORMANCE_LOG_SWITCH,  {0, 0},            dmac_config_set_performance_log_switch},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_RESUME_RX_INTR_FIFO, {0, 0},            dmac_config_resume_rx_intr_fifo},
#endif

#ifdef _PRE_DEBUG_MODE
    {WLAN_CFGID_GET_ALL_REG_VALUE,   {0, 0},            dmac_config_get_all_reg_value},
    {WLAN_CFGID_REPORT_AMPDU_STAT,   {0, 0},            dmac_config_report_ampdu_stat},
#endif
    {WLAN_CFGID_SET_VAP_NSS,         {0, 0},            dmac_config_set_vap_nss},
    {WLAN_CFGID_SET_AGGR_NUM,        {0, 0},            dmac_config_set_ampdu_aggr_num},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_FREQ_ADJUST,         {0, 0},            dmac_config_freq_adjust},
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
    {WLAN_CFGID_DATA_ACQ,            {0, 0},            dmac_config_data_acq},
#endif
#ifdef _PRE_WLAN_FEATURE_SMPS
    {WLAN_CFGID_SET_SMPS,            {0, 0},            dmac_config_set_smps_mode},
#endif

#ifdef _PRE_WLAN_FEATURE_PM
    {WLAN_CFGID_WIFI_EN,          {0, 0},               dmac_config_wifi_en},
    {WLAN_CFGID_PM_INFO,          {0, 0},               dmac_config_pm_info},
    {WLAN_CFGID_PM_EN,          {0, 0},                 dmac_config_pm_en},
#endif
    {WLAN_CFGID_SET_WPS_P2P_IE,    {0, 0},              dmac_config_set_app_ie_to_vap},
    {WLAN_CFGID_DEVICE_MEM_LEAK,   {0, 0},              dmac_config_show_device_memleak},
    {WLAN_CFGID_CFG80211_CANCEL_REMAIN_ON_CHANNEL,  {0, 0},  dmac_config_cancel_remain_on_channel},
#ifdef _PRE_WLAN_FEATURE_STA_PM
    {WLAN_CFGID_SET_PS_MODE,         {0, 0},                 dmac_config_set_ps_mode},  /* hi1102 pspoll�������� */
#ifdef _PRE_PSM_DEBUG_MODE
    {WLAN_CFGID_SHOW_PS_INFO,        {0, 0},                 dmac_show_ps_info},/* sta psm ά��ͳ����Ϣ */
#endif
    {WLAN_CFGID_SET_PSM_PARAM,       {0, 0},                 dmac_set_psm_param},/* sta psm tbtt offset/listen interval ���� */
    {WLAN_CFGID_SET_PSM_VOTE,        {0, 0},                 dmac_set_psm_vote},/* sta psm tbtt offset/listen interval ���� */
    {WLAN_CFGID_SET_PSM_OPEN,        {0, 0},                 dmac_set_sta_pm_open},/* sta psm tbtt offset/listen interval ���� */

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    {WLAN_CFGID_SET_UAPSD_PARA,        {0, 0},              dmac_config_set_uapsd_para},
#endif
#endif

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    {WLAN_CFGID_QUERY_STATION_STATS, {0, 0},                dmac_config_proc_query_sta_info_event},
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    {WLAN_CFGID_SET_P2P_PS_OPS,     {0, 0},                 dmac_config_set_p2p_ps_ops},
    {WLAN_CFGID_SET_P2P_PS_NOA,     {0, 0},                 dmac_config_set_p2p_ps_noa},
    {WLAN_CFGID_SET_P2P_PS_STAT,    {0, 0},                 dmac_config_set_p2p_ps_stat},
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
    {WLAN_CFGID_SET_MIPS,           {0, 0},             dmac_config_set_mips},
    {WLAN_CFGID_SHOW_MIPS,          {0, 0},             dmac_config_show_mips},
#endif
    {WLAN_CFGID_NSS,                {0, 0},             dmac_config_nss},
    {WLAN_CFGID_UPDATE_OPMODE,      {0, 0},             dmac_config_opmode},
    {WLAN_CFGID_USER_CAP_SYN,       {0, 0},             dmac_config_user_cap_syn},

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    {WLAN_CFGID_ENABLE_ARP_OFFLOAD,         {0, 0},     dmac_config_enable_arp_offload},
    {WLAN_CFGID_SET_IP_ADDR,                {0, 0},     dmac_config_set_ip_addr},
    {WLAN_CFGID_SHOW_ARPOFFLOAD_INFO,       {0, 0},     dmac_config_show_arpoffload_info},
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
    {WLAN_CFGID_SET_ROAMING_MODE,       {0, 0},         dmac_config_roam_enable},
    {WLAN_CFGID_SET_ROAM_TRIGGER,       {0, 0},         dmac_config_set_roam_trigger},
    {WLAN_CFGID_ROAM_HMAC_SYNC_DMAC,    {0, 0},         dmac_config_roam_hmac_sync_dmac},
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    {WLAN_CFGID_2040BSS_ENABLE,     {0, 0},             dmac_config_enable_2040bss},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SUSPEND_ACTION_SYN,        {0, 0},      dmac_config_suspend_action_sync},
#endif
    {WLAN_CFGID_BUTT,               {0, 0},             OAL_PTR_NULL},
};


oal_uint32 dmac_cali_to_hmac(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;

    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);

    //OAL_IO_PRINT("dmac_cali_to_hmac start\r\n");
    FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_MISC_SUB_TYPE_CALI_TO_HMAC);
    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_event_config_syn
 ��������  : dmac����ͬ���¼��������
 �������  : pst_event_mem: �¼��ڴ�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_event_config_syn(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    hmac_to_dmac_cfg_msg_stru  *pst_hmac2dmac_msg;
    mac_vap_stru               *pst_mac_vap;
    mac_device_stru            *pst_mac_device;
    oal_uint32                  ul_ret;
    oal_uint16                  us_cfgid;


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_event_config_syn::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼� */
    pst_event         = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr     = &(pst_event->st_event_hdr);
    pst_hmac2dmac_msg = (hmac_to_dmac_cfg_msg_stru *)pst_event->auc_event_data;

    //OAM_INFO_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::a dmac config syn event occur, cfg_id=%d.}", pst_hmac2dmac_msg->en_syn_id);
    /* ��ȡdmac vap */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac device */
    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_FAIL;
    }

    /* ���cfg id��Ӧ�Ĳ������� */
    for (us_cfgid = 0; WLAN_CFGID_BUTT != g_ast_dmac_config_syn[us_cfgid].en_cfgid; us_cfgid++)
    {
        if (g_ast_dmac_config_syn[us_cfgid].en_cfgid == pst_hmac2dmac_msg->en_syn_id)
        {
            break;
        }
    }

    /* �쳣�����cfgid��g_ast_dmac_config_syn�в����� */
    if (WLAN_CFGID_BUTT == g_ast_dmac_config_syn[us_cfgid].en_cfgid)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::invalid en_cfgid[%d].", pst_hmac2dmac_msg->en_syn_id);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* ִ�в������� */
    ul_ret = g_ast_dmac_config_syn[us_cfgid].p_set_func(pst_mac_vap, (oal_uint8)(pst_hmac2dmac_msg->us_len), (oal_uint8 *)pst_hmac2dmac_msg->auc_msg_body);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_CFG,
                         "{dmac_event_config_syn::p_set_func failed, ul_ret=%d en_syn_id=%d.", ul_ret, pst_hmac2dmac_msg->en_syn_id);
        return ul_ret;
    }

    return OAL_SUCC;
}
/*lint -e578*//*lint -e19*/

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_module_symbol(dmac_config_set_qap_cwmin);
    oal_module_symbol(dmac_config_set_qap_cwmax);
#endif
/*lint +e578*//*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

