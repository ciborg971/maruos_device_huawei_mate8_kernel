/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_vap.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
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
#include "oal_net.h"
#include "oam_ext_if.h"

#include "wlan_spec.h"

#include "mac_ie.h"

#include "hmac_vap.h"
#include "hmac_resource.h"
#include "hmac_tx_amsdu.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_fsm.h"
#include "hmac_ext_if.h"
#include "hmac_chan_mgmt.h"

#include "hmac_edca_opt.h"
#ifdef _PRE_WLAN_FEATURE_MCAST
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif
#include "hmac_blockack.h"
#include "hmac_p2p.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt.h"
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_VAP_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define HMAC_NETDEVICE_WDT_TIMEOUT      (5*OAL_TIME_HZ)

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    OAL_STATIC oal_net_device_ops_stru gst_vap_net_dev_cfg_vap_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /* TBD */
#else
        .ndo_get_stats          = oal_net_device_get_stats,
        .ndo_open               = oal_net_device_open,
        .ndo_stop               = oal_net_device_close,
        .ndo_start_xmit         = OAL_PTR_NULL,
        .ndo_set_multicast_list = OAL_PTR_NULL,
        .ndo_do_ioctl           = oal_net_device_ioctl,
        .ndo_change_mtu         = oal_net_device_change_mtu,
        .ndo_init               = oal_net_device_init,
        .ndo_set_mac_address    = oal_net_device_set_macaddr
#endif
    };
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    OAL_STATIC oal_net_device_ops_stru gst_vap_net_dev_cfg_vap_ops = {
         oal_net_device_init,
         oal_net_device_open,
         oal_net_device_close,
         OAL_PTR_NULL,
         OAL_PTR_NULL,
         oal_net_device_get_stats,
         oal_net_device_ioctl,
         oal_net_device_change_mtu,
         oal_net_device_set_macaddr};
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void hmac_del_virtual_inf_worker(oal_work_stru *pst_del_virtual_inf_work);
#endif


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_vap_init
 ��������  : ��ʼ��Ҫ��ӵ�hmac vap��һЩ������Ϣ
 �������  : ָ��Ҫ��ӵ�vap��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_vap_init(
                hmac_vap_stru              *pst_hmac_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                wlan_vap_mode_enum_uint8    en_vap_mode)
{
    oal_uint32      ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_init::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_vap_init(&pst_hmac_vap->st_vap_base_info,
                          uc_chip_id,
                          uc_device_id,
                          uc_vap_id,
                          en_vap_mode);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANY, "{hmac_vap_init::mac_vap_init failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ��ʼ��Ԥ����� */
    pst_hmac_vap->st_preset_para.en_protocol   = pst_hmac_vap->st_vap_base_info.en_protocol;
    pst_hmac_vap->st_preset_para.en_bandwidth  = pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth;
    pst_hmac_vap->st_preset_para.en_band       = pst_hmac_vap->st_vap_base_info.st_channel.en_band;
    /* ��ʼ������˽�нṹ�� */
    //����P2P CL �����ٳ�ʼ������
    pst_hmac_vap->st_cfg_priv.dog_tag = OAL_DOG_TAG;
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_vap->st_cfg_priv.st_wait_queue));
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_vap->st_cfg_priv.st_wait_queue_for_sdt_reg));
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_vap->st_mgmt_tx.st_wait_queue));

    /* Ĭ������Ϊ�Զ�����BA�ػ��Ľ��� */
    pst_hmac_vap->en_addba_mode = HMAC_ADDBA_MODE_AUTO;

    /* 1151Ĭ�ϲ�amsdu ampdu ���ϾۺϹ��ܲ����� 1102����С���Ż�
     * ��tplink/syslink���г�����������⣬�ȹر�02��ampdu+amsdu
     */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_hmac_vap->en_amsdu_ampdu_active = OAL_FALSE;
#else
    pst_hmac_vap->en_amsdu_ampdu_active = OAL_FALSE;
#endif

    /* ��ʼ��MIC faile ״̬ */
    pst_hmac_vap->en_mic_faile_in_progress = OAL_FALSE;

    /* ��ʼ����֤����ΪOPEN */
    pst_hmac_vap->en_auth_mode                 = WLAN_WITP_AUTH_OPEN_SYSTEM;
    pst_hmac_vap->uc_80211i_mode               = OAL_FALSE;
    pst_hmac_vap->en_psm_active                = WLAN_FEATURE_PSM_IS_OPEN;
    pst_hmac_vap->en_wme_active                = WLAN_FEATURE_WME_IS_OPEN;
    pst_hmac_vap->en_msdu_defrag_active        = WLAN_FEATURE_MSDU_DEFRAG_IS_OPEN;
    /* 2040�����ŵ��л����س�ʼ�� */
    pst_hmac_vap->en_2040_switch_prohibited    = OAL_TRUE;
    pst_hmac_vap->en_wps_active                = OAL_FALSE;

    /*����vap����û���*/
    pst_hmac_vap->us_user_nums_max = WLAN_ASSOC_USER_MAX_NUM_SPEC;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_hmac_vap->uc_rx_ba_session_num = 0;
    pst_hmac_vap->uc_tx_ba_session_num = 0;
#endif
    /* ״̬����ʼ�� */
    oal_spin_lock_init(&pst_hmac_vap->st_lock_state);

#ifdef _PRE_WLAN_FEATURE_11D
    pst_hmac_vap->en_updata_rd_by_ie_switch = OAL_FALSE;
#endif
    OAL_WAIT_QUEUE_INIT_HEAD(&pst_hmac_vap->query_wait_q);
    /* ��������VAP������Ӧ�����ҽ���ҵ��VAP������AP��STA��WDSģʽ */
    switch(en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            /* ִ�����Գ�ʼ��vap�ĺ��� */
        #ifdef _PRE_WLAN_FEATURE_AMSDU
            pst_hmac_vap->en_amsdu_active = OAL_FALSE;
        #endif
         /* �鲥ת������ʼ������ */
        #ifdef _PRE_WLAN_FEATURE_MCAST
            hmac_m2u_attach(pst_hmac_vap);
        #endif

        #ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_vap->ul_edca_opt_time_ms       = HMAC_EDCA_OPT_TIME_MS;
            FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_edca_opt_timer), hmac_edca_opt_timeout_fn, pst_hmac_vap->ul_edca_opt_time_ms, pst_hmac_vap, OAL_TRUE, OAM_MODULE_ID_ALG_SCHEDULE, pst_hmac_vap->st_vap_base_info.ul_core_id);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151) //open for 1151 om 6-29
            pst_hmac_vap->uc_edca_opt_flag_ap       = 1;
            FRW_TIMER_RESTART_TIMER(&(pst_hmac_vap->st_edca_opt_timer), pst_hmac_vap->ul_edca_opt_time_ms, OAL_TRUE);
#else
            pst_hmac_vap->uc_edca_opt_flag_ap       = 0;
            FRW_TIMER_STOP_TIMER(&(pst_hmac_vap->st_edca_opt_timer));
#endif
        #endif
            break;

        case WLAN_VAP_MODE_BSS_STA:
             /* �鲥ת������ʼ������ */
        #ifdef _PRE_WLAN_FEATURE_MCAST
            hmac_m2u_attach(pst_hmac_vap);
        #endif

        #ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_vap->uc_edca_opt_flag_sta = 0;
            pst_hmac_vap->uc_edca_opt_weight_sta    = WLAN_EDCA_OPT_WEIGHT_STA;
        #endif

        #ifdef _PRE_WLAN_FEATURE_DFS
            mac_mib_set_SpectrumManagementImplemented(&pst_hmac_vap->st_vap_base_info, OAL_TRUE);
        #endif
            pst_hmac_vap->bit_sta_protocol_cfg = OAL_SWITCH_OFF;

            break;

        case WLAN_VAP_MODE_WDS:
            break;

        case WLAN_VAP_MODE_CONFIG:
            pst_hmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_INIT;
            /* ����VAPֱ�ӷ��� */
            return OAL_SUCC;

        default:
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_init::unsupported mod=%d.}", en_vap_mode);
            return OAL_ERR_CODE_INVALID_CONFIG;
    }

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    OAL_NETBUF_QUEUE_HEAD_INIT(&(pst_hmac_vap->st_tx_queue_head[0]));
    OAL_NETBUF_QUEUE_HEAD_INIT(&(pst_hmac_vap->st_tx_queue_head[1]));
    pst_hmac_vap->uc_in_queue_id  = 0;
    pst_hmac_vap->uc_out_queue_id = 1;
    oal_atomic_set(&pst_hmac_vap->ul_tx_event_num,1);  /* ul_tx_event_num��ʼֵ�޸�Ϊ1����ֹhmac_tx_post_event�������������������¼� */
    pst_hmac_vap->ul_tx_quata = 256;
    oal_spin_lock_init(&pst_hmac_vap->st_smp_lock);
#endif

    /* ����vapʱ ��ʼ״̬Ϊinit */
    pst_hmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_INIT;

    /* ��ʼ��������ʱʱ�� */
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_BK] = HMAC_BA_RX_BK_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_BE] = HMAC_BA_RX_BE_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_VI] = HMAC_BA_RX_VI_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_VO] = HMAC_BA_RX_VO_TIMEOUT;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* ��ʼ��ɾ����������ӿڹ������� */
    OAL_INIT_WORK(&(pst_hmac_vap->st_del_virtual_inf_worker), hmac_del_virtual_inf_worker);
    pst_hmac_vap->pst_del_net_device    = OAL_PTR_NULL;
    pst_hmac_vap->pst_p2p0_net_device   = OAL_PTR_NULL;
#endif
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].filter_info.ul_ack_limit = DEFAULT_TX_TCP_ACK_THRESHOLD;
    pst_hmac_vap->st_hamc_tcp_ack[HCC_RX].filter_info.ul_ack_limit = DEFAULT_RX_TCP_ACK_THRESHOLD;
    hmac_tcp_opt_init_filter_tcp_ack_pool(pst_hmac_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    hmac_roam_init(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_vap_get_priv_cfg
 ��������  : ��ȡhmac_vap�ṹ���е�˽��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_vap_get_priv_cfg(mac_vap_stru *pst_mac_vap, hmac_vap_cfg_priv_stru **ppst_cfg_priv)
{
    hmac_vap_stru   *pst_hmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_get_priv_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    *ppst_cfg_priv = &pst_hmac_vap->st_cfg_priv;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_vap_get_desired_country
 ��������  : ��ȡ�����Ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int8*  hmac_vap_get_desired_country(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{hmac_vap_get_desired_country::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    return pst_hmac_vap->ac_desired_country;
}
#ifdef _PRE_WLAN_FEATURE_11D
/*****************************************************************************
 �� �� ��  : hmac_vap_get_updata_rd_by_ie_switch
 ��������  : ��ȡ�Ƿ���ݹ���ap���¹�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��17��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_vap_get_updata_rd_by_ie_switch(oal_uint8 uc_vap_id,oal_bool_enum_uint8 *us_updata_rd_by_ie_switch)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(0);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_get_updata_rd_by_ie_switch::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    *us_updata_rd_by_ie_switch = pst_hmac_vap->en_updata_rd_by_ie_switch;
    return OAL_SUCC;
}
#endif

oal_net_device_stru  *hmac_vap_get_net_device(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{hmac_vap_get_net_device::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    return (pst_hmac_vap->pst_net_device);
}



oal_uint32  hmac_vap_set_asoc_req_ie_ptr_null(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);


    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ASSOC, "{hmac_vap_set_asoc_req_ie_ptr_null::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_vap_creat_netdev
 ��������  : ��ȡhmac_vap�ṹ���е�˽��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_vap_creat_netdev(hmac_vap_stru *pst_hmac_vap, oal_int8 *puc_netdev_name, oal_int8 *puc_mac_addr)

{
    oal_net_device_stru *pst_net_device;
    oal_uint32           ul_return;
    mac_vap_stru        *pst_vap;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_netdev_name)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_vap_creat_netdev::param null %d %d.}", pst_hmac_vap, puc_netdev_name);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap = &pst_hmac_vap->st_vap_base_info;

    pst_net_device = oal_net_alloc_netdev(0, puc_netdev_name, oal_ether_setup);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_device))
    {
        MAC_WARNING_LOG(pst_vap->uc_vap_id, "mac_device_init:p_vap_netdev_alloc return fail.");
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_vap_creat_netdev::pst_net_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���¶�netdevice�ĸ�ֵ��ʱ�����²��� */
    OAL_NETDEVICE_OPS(pst_net_device)             = &gst_vap_net_dev_cfg_vap_ops;
    OAL_NETDEVICE_DESTRUCTOR(pst_net_device)      = oal_net_free_netdev;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /* TBD  need to check the net device diff*/
#else
    OAL_NETDEVICE_MASTER(pst_net_device)          = OAL_PTR_NULL;
#endif

    OAL_NETDEVICE_IFALIAS(pst_net_device)         = OAL_PTR_NULL;
    OAL_NETDEVICE_WATCHDOG_TIMEO(pst_net_device)  = HMAC_NETDEVICE_WDT_TIMEOUT;
    oal_memcopy(OAL_NETDEVICE_MAC_ADDR(pst_net_device), puc_mac_addr, WLAN_MAC_ADDR_LEN);
    OAL_NET_DEV_PRIV(pst_net_device) = pst_vap;
    OAL_NETDEVICE_QDISC(pst_net_device, OAL_PTR_NULL);

    ul_return = (oal_uint32)oal_net_register_netdev(pst_net_device);
    if (OAL_UNLIKELY(OAL_SUCC != ul_return))
    {
        MAC_WARNING_LOG(pst_vap->uc_vap_id, "mac_device_init:oal_net_register_netdev return fail.");
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_vap_creat_netdev::oal_net_register_netdev failed.}");

        return ul_return;
    }

    pst_hmac_vap->pst_net_device = pst_net_device;
    /* ����'\0' */
    oal_memcopy(pst_hmac_vap->auc_name,pst_net_device->name,OAL_IF_NAME_SIZE);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_vap_destroy
 ��������  : ����hmac vap�Ĵ�����
 �������  : ָ��Ҫ���ٵ�vapָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_vap_destroy(hmac_vap_stru *pst_hmac_vap)
{
    mac_cfg_down_vap_param_stru   st_down_vap;
    oal_uint32                    ul_ret;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_vap_destroy::func enter.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_destroy::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_hmac_vap->uc_edca_opt_flag_ap   = 0;
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_vap->st_edca_opt_timer));
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_hmac_vap->uc_edca_opt_flag_sta = 0;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    hmac_roam_exit(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    /* ��down vap */
    st_down_vap.pst_net_dev = pst_hmac_vap->pst_net_device;
    ul_ret = hmac_config_down_vap(&pst_hmac_vap->st_vap_base_info,
                                  OAL_SIZEOF(mac_cfg_down_vap_param_stru),
                                  (oal_uint8 *)&st_down_vap);
    if (ul_ret != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_destroy::hmac_config_down_vap failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* Ȼ����delete vap */
    ul_ret = hmac_config_del_vap(&pst_hmac_vap->st_vap_base_info,
                        OAL_SIZEOF(mac_cfg_down_vap_param_stru),
                        (oal_uint8 *)&st_down_vap);
    if (ul_ret != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_destroy::hmac_config_del_vap failed[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_vap_destroy::func out.}");
    return OAL_SUCC;
}


oal_uint16 hmac_vap_check_ht_capabilities_ap(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                   *pst_hmac_user_sta)
{
    oal_uint16              us_index        = us_info_elem_offset;
    oal_bool_enum           en_prev_asoc_ht = OAL_FALSE;
    oal_bool_enum           en_prev_asoc_non_ht = OAL_FALSE;
    mac_user_ht_hdl_stru   *pst_ht_hdl      = &(pst_hmac_user_sta->st_user_base_info.st_ht_hdl);
    hmac_amsdu_stru        *pst_amsdu;
    oal_uint32              ul_amsdu_idx;
    mac_protection_stru    *pst_protection;
    oal_uint8               uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8               uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(&pst_hmac_vap->st_vap_base_info))
    {
        return MAC_SUCCESSFUL_STATUSCODE;
    }
    /* ���STA�Ƿ�����Ϊһ��HT capable STA��AP���� */
    if ((MAC_USER_STATE_ASSOC == pst_hmac_user_sta->st_user_base_info.en_user_asoc_state) && (OAL_TRUE == pst_ht_hdl->en_ht_capable))
    {
        mac_user_set_ht_capable(&(pst_hmac_user_sta->st_user_base_info), OAL_FALSE);
        en_prev_asoc_ht = OAL_TRUE;
    }

    /* ���STA�Ƿ�����Ϊһ��non HT capable STA��AP���� */
    else if (MAC_USER_STATE_ASSOC == pst_hmac_user_sta->st_user_base_info.en_user_asoc_state)
    {
        en_prev_asoc_non_ht = OAL_TRUE;
    }
    else
    {

    }

    /* �ڹ�������֡������ HT Capabilities Element */
    while (us_index < (ul_msg_len - WLAN_HDR_FCS_LENGTH))
    {
        if (puc_payload[us_index] == MAC_EID_HT_CAP)
        {
            /* ������HT STA ʹ�� TKIP/WEP ���� */
            if (mac_is_wep_enabled(&pst_hmac_vap->st_vap_base_info))
            {
                OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_ht_capabilities_ap::Rejecting a HT STA because of its Pairwise Cipher[%d].}",
                                 pst_hmac_user_sta->st_user_base_info.st_key_info.en_cipher_type);
                return MAC_MISMATCH_HTCAP;
            }
            uc_pcip_policy = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested;
            uc_grp_policy  = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested;

            if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pcip_policy)
            {
                OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_ht_capabilities_ap::HT STA with TKIP Pairwise Cipher,uc_pcip_policy=%d uc_grp_policy=%d.}",
                                 uc_pcip_policy, uc_grp_policy);
                break;
            }

            /* ���� HT Capabilities Element */
            hmac_search_ht_cap_ie_ap(pst_hmac_vap, pst_hmac_user_sta, puc_payload, us_index, en_prev_asoc_ht);

            break;
        }
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        else if (puc_payload[us_index] == MAC_EID_EXT_CAPS)
        {
            mac_ie_proc_ext_cap_ie(&(pst_hmac_user_sta->st_user_base_info), &puc_payload[us_index]);
        }
#endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

        /* ͨ��IE������������ֵ */
        us_index += puc_payload[us_index + 1] + MAC_IE_HDR_LEN;
    }

    /*�ߵ����˵��sta�Ѿ���ͳ�Ƶ�ht��ص�ͳ������*/
    pst_hmac_user_sta->st_user_stats_flag.bit_no_ht_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_gf_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_20M_only_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_lsig_txop_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_40dsss_stats_flag = OAL_TRUE;

    pst_protection = &(pst_hmac_vap->st_vap_base_info.st_protection);
    if (OAL_FALSE == pst_ht_hdl->en_ht_capable) /*STA��֧��HT*/
    {
        /*  ���STA֮ǰû����AP����*/
        if (MAC_USER_STATE_ASSOC != pst_hmac_user_sta->st_user_base_info.en_user_asoc_state)
        {
            pst_protection->uc_sta_non_ht_num++;
        }
        /*���STA֮ǰ�Ѿ���ΪHTվ����AP����*/
        else if (OAL_TRUE == en_prev_asoc_ht)
        {
            pst_protection->uc_sta_non_ht_num++;

            if ((OAL_FALSE == pst_ht_hdl->bit_supported_channel_width) && (0 != pst_protection->uc_sta_20M_only_num))
            {
                pst_protection->uc_sta_20M_only_num--;
            }

            if ((OAL_FALSE == pst_ht_hdl->bit_ht_green_field) && (0 != pst_protection->uc_sta_non_gf_num))
            {
                pst_protection->uc_sta_non_gf_num--;
            }

            if ((OAL_FALSE == pst_ht_hdl->bit_lsig_txop_protection) && (0 != pst_protection->uc_sta_no_lsig_txop_num))
            {
                pst_protection->uc_sta_no_lsig_txop_num--;
            }
        }
        else /*STA ֮ǰ�Ѿ���Ϊ��HTվ����AP����*/
        {
        }
    }
    else  /*STA֧��HT*/
    {
        for (ul_amsdu_idx = 0; ul_amsdu_idx < WLAN_WME_MAX_TID_NUM; ul_amsdu_idx++)
        {
            pst_amsdu = &(pst_hmac_user_sta->ast_hmac_amsdu[ul_amsdu_idx]);
            hmac_amsdu_set_maxsize(pst_amsdu, pst_hmac_user_sta, 7936);
            hmac_amsdu_set_maxnum(pst_amsdu, WLAN_AMSDU_MAX_NUM);
        }

        /* ����amsdu�� */
        pst_hmac_user_sta->uc_amsdu_supported = 255;

        /*  ���STA֮ǰ�Ѿ���non-HTվ����AP����, ��uc_sta_non_ht_num��1*/
        if ((OAL_TRUE == en_prev_asoc_non_ht) && (0 != pst_protection->uc_sta_non_ht_num))
        {
            pst_protection->uc_sta_non_ht_num--;
        }
    }

    return MAC_SUCCESSFUL_STATUSCODE;
}
oal_uint16 hmac_vap_check_vht_capabilities_ap(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                  *pst_hmac_user_sta)
{
    oal_uint8              *puc_vht_cap_ie;
    mac_vap_stru           *pst_mac_vap;
    mac_user_stru          *pst_mac_user;
    oal_uint8               uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8               uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    if (OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == puc_payload || OAL_PTR_NULL == pst_hmac_user_sta)
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::param null,%d %d %d.}",
                                 pst_hmac_vap, puc_payload, pst_hmac_user_sta);
        return MAC_UNSPEC_FAIL;

    }
    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user_sta->st_user_base_info);

    //puc_vht_cap_ie  = mac_get_vht_cap_ie(puc_payload, (oal_uint16)ul_msg_len, us_info_elem_offset);
    puc_vht_cap_ie = mac_find_ie(MAC_EID_VHT_CAP, puc_payload + us_info_elem_offset, (oal_int32)(ul_msg_len - us_info_elem_offset));
    if (OAL_PTR_NULL != puc_vht_cap_ie)
    {
        /* ������VHT STA ʹ�� TKIP/WEP ���� */
        if (mac_is_wep_enabled(pst_mac_vap))
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::Rejecting a VHT STA because of its Pairwise Cipher[%]d.}",
                                 pst_mac_user->st_key_info.en_cipher_type);
            return MAC_MISMATCH_HTCAP;
        }
        uc_pcip_policy = pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested;
        uc_grp_policy  = pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested;

        if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pcip_policy)
        {
            OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::VHT STA with TKIP Pairwise Cipher,uc_pcip_policy=%d uc_grp_policy=%d.}",
                                 uc_pcip_policy, uc_grp_policy);
            return MAC_SUCCESSFUL_STATUSCODE;
        }

        hmac_proc_vht_cap_ie(pst_mac_vap, pst_hmac_user_sta, puc_vht_cap_ie);
        hmac_amsdu_init_user(pst_hmac_user_sta);
    }
    else
    {
        /* ������֧��11ac STA����11aconly ģʽ��AP*/
        if(WLAN_VHT_ONLY_MODE == pst_mac_vap->en_protocol)
        {
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,"{hmac_vap_check_vht_capabilities_ap:AP 11ac only, but STA not support 11ac}");
            return MAC_MISMATCH_VHTCAP;
        }
    }

    return MAC_SUCCESSFUL_STATUSCODE;
}


oal_void  hmac_search_txbf_cap_ie_ap(mac_user_ht_hdl_stru *pst_ht_hdl,
								     oal_uint32            ul_info_elem)
{
	oal_uint32  ul_tmp_txbf_elem = ul_info_elem;

    pst_ht_hdl->bit_imbf_receive_cap				= (ul_tmp_txbf_elem & BIT0);
    pst_ht_hdl->bit_receive_staggered_sounding_cap  = ((ul_tmp_txbf_elem & BIT1) >> 1);
    pst_ht_hdl->bit_transmit_staggered_sounding_cap = ((ul_tmp_txbf_elem & BIT2) >> 2);
    pst_ht_hdl->bit_receive_ndp_cap					= ((ul_tmp_txbf_elem & BIT3) >> 3);
    pst_ht_hdl->bit_transmit_ndp_cap				= ((ul_tmp_txbf_elem & BIT4) >> 4);
    pst_ht_hdl->bit_imbf_cap						= ((ul_tmp_txbf_elem & BIT5) >> 5);
    pst_ht_hdl->bit_calibration						= ((ul_tmp_txbf_elem & 0x000000C0) >> 6);
    pst_ht_hdl->bit_exp_csi_txbf_cap				= ((ul_tmp_txbf_elem & BIT8) >> 8);
    pst_ht_hdl->bit_exp_noncomp_txbf_cap			= ((ul_tmp_txbf_elem & BIT9) >> 9);
    pst_ht_hdl->bit_exp_comp_txbf_cap				= ((ul_tmp_txbf_elem & BIT10) >> 10);
    pst_ht_hdl->bit_exp_csi_feedback				= ((ul_tmp_txbf_elem & 0x00001800) >> 11);
    pst_ht_hdl->bit_exp_noncomp_feedback			= ((ul_tmp_txbf_elem & 0x00006000) >> 13);

    pst_ht_hdl->bit_exp_comp_feedback				= ((ul_tmp_txbf_elem & 0x0001C000) >> 15);
    pst_ht_hdl->bit_min_grouping					= ((ul_tmp_txbf_elem & 0x00060000) >> 17);
    pst_ht_hdl->bit_csi_bfer_ant_number				= ((ul_tmp_txbf_elem & 0x001C0000) >> 19);
    pst_ht_hdl->bit_noncomp_bfer_ant_number			= ((ul_tmp_txbf_elem & 0x00600000) >> 21);
    pst_ht_hdl->bit_comp_bfer_ant_number			= ((ul_tmp_txbf_elem & 0x01C00000) >> 23);
    pst_ht_hdl->bit_csi_bfee_max_rows				= ((ul_tmp_txbf_elem & 0x06000000) >> 25);
    pst_ht_hdl->bit_channel_est_cap					= ((ul_tmp_txbf_elem & 0x18000000) >> 27);
}



oal_uint32  hmac_search_ht_cap_ie_ap(
                hmac_vap_stru               *pst_hmac_vap,
                hmac_user_stru              *pst_hmac_user_sta,
                oal_uint8                   *puc_payload,
                oal_uint16                   us_current_offset,
                oal_bool_enum                en_prev_asoc_ht)
{
    oal_uint8                   uc_smps;
    oal_uint8                   uc_supported_channel_width;
    oal_uint8                   uc_ht_green_field;
    oal_uint8                   uc_lsig_txop_protection_support;
    oal_uint8                   uc_mcs_bmp_index;
    oal_uint8				   *puc_tmp_payload;
    oal_uint16					us_tmp_info_elem = 0;
	oal_uint16					us_tmp_txbf_low = 0;
	oal_uint32					ul_tmp_txbf_elem = 0;

    mac_user_ht_hdl_stru        *pst_ht_hdl;
    mac_user_ht_hdl_stru         st_ht_hdl;
    mac_vap_stru                *pst_mac_vap;
    mac_user_stru               *pst_mac_user;
    mac_device_stru             *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_search_ht_cap_ie_ap::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���� ��� */
    puc_tmp_payload =  puc_payload;

    pst_ht_hdl    = &st_ht_hdl;
    mac_user_get_ht_hdl(&(pst_hmac_user_sta->st_user_base_info), pst_ht_hdl);
    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user_sta->st_user_base_info);

    /* ���� HT Capability Element �� STA����ʾ������HT capable. */
    pst_ht_hdl->en_ht_capable = 1;
    us_current_offset += MAC_IE_HDR_LEN;

    /***************************************************************************
                    ���� HT Capabilities Info Field
    ***************************************************************************/

    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);

    /* ���STA��֧�ֵ�LDPC�������� B0��0:��֧�֣�1:֧�� */
    pst_ht_hdl->bit_ldpc_coding_cap = (us_tmp_info_elem & BIT0);

    /* ���STA��֧�ֵ��ŵ���� B1��0:��20M���У�1:20M��40M���� */
    uc_supported_channel_width = (us_tmp_info_elem & BIT1) >> 1;
    pst_ht_hdl->bit_supported_channel_width = mac_ie_proc_ht_supported_channel_width(pst_mac_user, pst_mac_vap, uc_supported_channel_width, en_prev_asoc_ht);

    /* ���ռ临�ý���ģʽ B2~B3 */
    uc_smps = ((us_tmp_info_elem & (BIT2 | BIT3)) >> 2);
    pst_ht_hdl->bit_sm_power_save = mac_ie_proc_sm_power_save_field(pst_mac_user, uc_smps);

    /* ���Greenfield ֧����� B4�� 0:��֧�֣�1:֧��*/
    uc_ht_green_field = (us_tmp_info_elem & BIT4) >> 4;
    pst_ht_hdl->bit_ht_green_field = mac_ie_proc_ht_green_field(pst_mac_user, pst_mac_vap, uc_ht_green_field, en_prev_asoc_ht);

    /* ���20MHz Short-GI B5,  0:��֧�֣�1:֧�֣�֮����APȡ����  */
    pst_ht_hdl->bit_short_gi_20mhz = ((us_tmp_info_elem & BIT5) >> 5);
    pst_ht_hdl->bit_short_gi_20mhz &= pst_hmac_vap->st_vap_base_info.pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented;

    /* ���40MHz Short-GI B6,  0:��֧�֣�1:֧�֣�֮����APȡ���� */
    pst_ht_hdl->bit_short_gi_40mhz = ((us_tmp_info_elem & BIT6) >> 6);
    pst_ht_hdl->bit_short_gi_40mhz &= pst_hmac_vap->st_vap_base_info.pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented;

    /* ���֧�ֽ���STBC PPDU B8,  0:��֧�֣�1:֧�� */
    pst_ht_hdl->bit_rx_stbc = ((us_tmp_info_elem & 0x0300) >> 8);

    /* ������A-MSDU���� B11��0:3839�ֽ�, 1:7935�ֽ� */
    pst_hmac_user_sta->us_amsdu_maxsize = (0 == (us_tmp_info_elem & BIT11)) ? WLAN_MIB_MAX_AMSDU_LENGTH_SHORT : WLAN_MIB_MAX_AMSDU_LENGTH_LONG;

    /* �����40M��DSSS/CCK��֧����� B12 */
    /* �ڷ�Beacon֡��probe rsp֡��ʱ */
    /* 0: STA��40MHz�ϲ�ʹ��DSSS/CCK, 1: STA��40MHz��ʹ��DSSS/CCK */
    pst_ht_hdl->bit_dsss_cck_mode_40mhz = ((us_tmp_info_elem & BIT12) >> 12);

    if ((0 == pst_ht_hdl->bit_dsss_cck_mode_40mhz)
     && (1 == pst_ht_hdl->bit_supported_channel_width))
    {
        pst_hmac_vap->st_vap_base_info.st_protection.uc_sta_no_40dsss_cck_num++;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* ���Forty MHz Intolerant */
    pst_ht_hdl->bit_forty_mhz_intolerant = ((us_tmp_info_elem & BIT14) >> 14);

    hmac_chan_update_40M_intol_user(pst_mac_vap, pst_mac_user, (oal_bool_enum_uint8)pst_ht_hdl->bit_forty_mhz_intolerant);

    /* ���Forty MHz Intolerant������0��������AP��40MHz���� */
    if (0 != pst_ht_hdl->bit_forty_mhz_intolerant)
    {
        hmac_chan_start_40M_recovery_timer(pst_mac_vap);
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                      "{hmac_search_ht_cap_ie_ap::40MHz Intolerant STA joining.}");
        if (pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M)
        {
            /* AP׼���л���20MHz���� */
            hmac_chan_multi_switch_to_20MHz_ap(pst_hmac_vap);
        }
        else
        {
            pst_mac_device->en_40MHz_intol_bit_recd = OAL_TRUE;
        }
    }

#endif
    /*  ����L-SIG TXOP ������֧����� B15, 0:��֧�֣�1:֧�� */
    uc_lsig_txop_protection_support = (us_tmp_info_elem & BIT15) >> 15;
    pst_ht_hdl->bit_lsig_txop_protection = mac_ie_proc_lsig_txop_protection_support(pst_mac_user, pst_mac_vap, uc_lsig_txop_protection_support, en_prev_asoc_ht);

    us_current_offset += MAC_HT_CAPINFO_LEN;

    /***************************************************************************
                        ���� A-MPDU Parameters Field
    ***************************************************************************/

    /* ��ȡ Maximum Rx A-MPDU factor (B1 - B0) */
    pst_ht_hdl->uc_max_rx_ampdu_factor = (puc_tmp_payload[us_current_offset] & 0x03);

    /* ��ȡ the Minimum MPDU Start Spacing (B2 - B4) */
    pst_ht_hdl->uc_min_mpdu_start_spacing = (puc_tmp_payload[us_current_offset] >> 2)  & 0x07;

    us_current_offset += MAC_HT_AMPDU_PARAMS_LEN;

    /***************************************************************************
                        ���� Supported MCS Set Field
    ***************************************************************************/
    for (uc_mcs_bmp_index = 0; uc_mcs_bmp_index < WLAN_HT_MCS_BITMASK_LEN; uc_mcs_bmp_index++)
    {
        pst_ht_hdl->uc_rx_mcs_bitmask[uc_mcs_bmp_index] =
                (pst_hmac_vap->st_vap_base_info.pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[uc_mcs_bmp_index])
              & (*(oal_uint8 *)(puc_tmp_payload + us_current_offset + uc_mcs_bmp_index));
    }

    pst_ht_hdl->uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN - 1] &= 0x1F;

    us_current_offset += MAC_HT_SUP_MCS_SET_LEN;

    /***************************************************************************
                        ���� HT Extended Capabilities Info Field
    ***************************************************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);

    /* ��ȡ HTC support Information */
    if (0 != (us_tmp_info_elem & BIT10))
    {
        pst_ht_hdl->uc_htc_support = 1;
    }

    us_current_offset += MAC_HT_EXT_CAP_LEN;

    /***************************************************************************
                        ���� Tx Beamforming Field
    ***************************************************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);
    us_tmp_txbf_low	 = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset + 2], puc_tmp_payload[us_current_offset + 3]);
    ul_tmp_txbf_elem = OAL_MAKE_WORD32(us_tmp_info_elem, us_tmp_txbf_low);
    hmac_search_txbf_cap_ie_ap(pst_ht_hdl, ul_tmp_txbf_elem);
    us_current_offset += MAC_HT_TXBF_CAP_LEN;

    /***************************************************************************
                        ���� ASEL Field(����ѡ������)
    ***************************************************************************/
    us_current_offset += MAC_HT_ASEL_LEN;

    /* ������Ϣ�������� */
    //us_current_offset = us_saved_offset + puc_tmp_payload[us_saved_offset + 1] + MAC_IE_HDR_LEN;

    mac_user_set_ht_hdl(&(pst_hmac_user_sta->st_user_base_info), pst_ht_hdl);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_vap_addba_check
 ��������  : �жϸ��û���Ӧ��TID�Ƿ��Ѿ�����BA�Ự
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_TRUE������Խ���BA�Ự��OAL_FALSE��ʾ�����Խ���BA�Ự
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_vap_addba_check(
                hmac_vap_stru    *pst_hmac_vap,
                hmac_user_stru   *pst_hmac_user,
                oal_uint8         uc_tidno)
{
    mac_device_stru   *pst_mac_device;
    hmac_tid_stru     *pst_hmac_tid_info;

    /* �ж�HMAC VAP���Ƿ�֧�־ۺ� */
    if (!((pst_hmac_vap->en_tx_aggr_on) || (pst_hmac_vap->st_vap_base_info.st_cap_flag.bit_rifs_tx_on)))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_tx_aggr_on of vap is off");
        return OAL_FALSE;
    }

    pst_hmac_tid_info = &(pst_hmac_user->ast_tid_info[uc_tidno]);
    if (OAL_TRUE != pst_hmac_tid_info->st_ba_tx_info.en_ba_switch)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_tx_aggr_on of tid[%d] is off", uc_tidno);
        return OAL_FALSE;
    }

    if (DMAC_BA_COMPLETE == pst_hmac_tid_info->st_ba_tx_info.en_ba_status)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_ba_status of tid[%d] is COMPLETE", uc_tidno);
        return OAL_FALSE;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::pst_mac_dev null");
        return OAL_FALSE;
    }
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    if (pst_hmac_vap->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::uc_tx_ba_session_num[%d] exceed spec", pst_hmac_vap->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#else
    if (pst_mac_device->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::uc_tx_ba_session_num[%d] exceed spec", pst_mac_device->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#endif
    /* ��Ҫ�ȷ���5������֡���ٽ���BA�Ự�Ľ��� */
    if ((OAL_TRUE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos) &&
        (pst_hmac_user->auc_ba_flag[uc_tidno] < DMAC_UCAST_FRAME_TX_COMP_TIMES))
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                      "{hmac_vap_addba_check::auc_ba_flag[%d]}", pst_hmac_user->auc_ba_flag[uc_tidno]);
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
        return OAL_FALSE;
    }

    if ((pst_hmac_tid_info->st_ba_tx_info.en_ba_status != DMAC_BA_INPROGRESS)
     && (pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps < HMAC_ADDBA_EXCHANGE_ATTEMPTS))
    {
        pst_hmac_tid_info->st_ba_tx_info.en_ba_status = DMAC_BA_INPROGRESS;
        pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps++;

        return OAL_TRUE;
    }
    else
    {
        OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                     "{hmac_vap_addba_check::addba_attemps[%d] of tid[%d] is COMPLETE}", pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps, uc_tidno);
    }

    return OAL_FALSE;
}


oal_void hmac_vap_net_stopall(oal_void)
{
    oal_uint8 uc_vap_id;
    oal_net_device_stru  *pst_net_device = NULL;
    hmac_vap_stru    *pst_hmac_vap = NULL;
    for (uc_vap_id = 0; uc_vap_id < WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if(NULL == pst_hmac_vap)
            break;

        pst_net_device = pst_hmac_vap->pst_net_device;

        if(NULL == pst_net_device)
            break;

        oal_net_tx_stop_all_queues(pst_net_device);
        //OAL_IO_PRINT("stop net device:%p\n", pst_net_device);
    }
}

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL

oal_bool_enum_uint8 hmac_flowctl_check_device_is_sta_mode(oal_void)
{
    mac_device_stru         *pst_dev;
    mac_vap_stru            *pst_vap;
    oal_uint8                uc_vap_index;
    oal_bool_enum_uint8      en_device_is_sta = OAL_FALSE;

    /* check ��VAP״̬��ֻҪ��VAP������STAģʽ(����BSS_STA����P2P client)������Ϊ��device������staģʽ */
    pst_dev = mac_res_get_dev(0);

    if (pst_dev->uc_vap_num >= 1)
    {
        for(uc_vap_index = 0; uc_vap_index < pst_dev->uc_vap_num; uc_vap_index++)
        {
            pst_vap = mac_res_get_mac_vap(pst_dev->auc_vap_id[uc_vap_index]);

            if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
            {
                en_device_is_sta = OAL_TRUE;
                break;
            }
        }
    }

    OAM_INFO_LOG2(0, OAM_SF_TX, "{hmac_flowctl_check_device_is_sta_mode:: vap_num = %d, is_sta mode = %d}", pst_dev->uc_vap_num, en_device_is_sta);

    return en_device_is_sta;
}
OAL_STATIC oal_void hmac_vap_wake_subq(oal_uint8 uc_vap_id, oal_uint16 us_queue_idx)
{
    oal_net_device_stru    *pst_net_device = NULL;
    hmac_vap_stru          *pst_hmac_vap = NULL;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if(NULL == pst_hmac_vap)
    {
        return;
    }

    if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        return;
    }

    pst_net_device = pst_hmac_vap->pst_net_device;
    if(NULL == pst_net_device)
    {
        return;
    }

    oal_net_wake_subqueue(pst_net_device, us_queue_idx);
}


oal_void hmac_vap_net_start_subqueue(oal_uint16 us_queue_idx)
{
    oal_uint8               uc_vap_id;
    OAL_STATIC oal_uint8    g_uc_start_subq_flag = 0;

    if (0 == g_uc_start_subq_flag)
    {
        g_uc_start_subq_flag = 1;

        /* vap id�ӵ͵��߻ָ� */
        for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
        {
            hmac_vap_wake_subq(uc_vap_id, us_queue_idx);
        }
    }
    else
    {
        g_uc_start_subq_flag = 0;

        /* vap id�Ӹߵ��ͻָ� */
        for (uc_vap_id = WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id > 0; uc_vap_id--)
        {
            hmac_vap_wake_subq(uc_vap_id - 1, us_queue_idx);
        }
    }
}

/*****************************************************************************
 �� �� ��  : hmac_vap_stop_subq
 ��������  : ֹͣĳ��VAP���е�ĳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_vap_stop_subq(oal_uint8 uc_vap_id, oal_uint16 us_queue_idx)
{
    oal_net_device_stru    *pst_net_device = NULL;
    hmac_vap_stru          *pst_hmac_vap = NULL;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if(NULL == pst_hmac_vap)
    {
        return;
    }

    if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        return;
    }

    pst_net_device = pst_hmac_vap->pst_net_device;
    if(NULL == pst_net_device)
    {
        return;
    }

    oal_net_stop_subqueue(pst_net_device, us_queue_idx);
}



oal_void hmac_vap_net_stop_subqueue(oal_uint16 us_queue_idx)
{
    oal_uint8               uc_vap_id;
    OAL_STATIC oal_uint8    g_uc_stop_subq_flag = 0;

    /* �ɰ���VAP ID˳��ֹͣsubq����Ϊ������VAP ID˳�� */
    if (0 == g_uc_stop_subq_flag)
    {
        g_uc_stop_subq_flag = 1;

        for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
        {
            hmac_vap_stop_subq(uc_vap_id, us_queue_idx);
        }
    }
    else
    {
        g_uc_stop_subq_flag = 0;

        for (uc_vap_id = WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id > 0; uc_vap_id--)
        {
            hmac_vap_stop_subq(uc_vap_id - 1, us_queue_idx);
        }
    }
}
#endif
oal_void hmac_vap_net_startall(oal_void)
{
    oal_uint8 uc_vap_id;
    oal_net_device_stru  *pst_net_device = NULL;
    hmac_vap_stru    *pst_hmac_vap = NULL;
    for (uc_vap_id = 0; uc_vap_id < WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if(NULL == pst_hmac_vap)
            break;

        pst_net_device = pst_hmac_vap->pst_net_device;

        if(NULL == pst_net_device)
            break;

        oal_net_tx_wake_all_queues(pst_net_device);
        //OAL_IO_PRINT("start net device:%p\n", pst_net_device);
    }
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY

oal_uint32 hmac_check_opmode_notify(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_mac_hdr,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                   *pst_hmac_user)
{
    oal_uint8              *puc_opmode_notify_ie;
    mac_vap_stru           *pst_mac_vap;
    mac_user_stru          *pst_mac_user;
    mac_opmode_notify_stru *pst_opmode_notify = OAL_PTR_NULL;
    oal_uint8               uc_mgmt_frm_type;
    oal_uint32              ul_relt;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_mac_hdr))
    {
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{hmac_check_opmode_notify::pst_hmac_vap = [%x], puc_payload = [%x], pst_hmac_user = [%x],puc_mac_hdr = [%x]!}\r\n",
                        pst_hmac_vap, puc_payload, pst_hmac_user, puc_mac_hdr);
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{hmac_check_opmode_notify::param null, %d %d %d %d.}",
                       pst_hmac_vap, puc_payload, pst_hmac_user, puc_mac_hdr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user->st_user_base_info);

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        return OAL_SUCC;
    }

    //puc_opmode_notify_ie = mac_get_opmode_notify_ie(puc_payload, (oal_uint16)ul_msg_len, us_info_elem_offset);
    puc_opmode_notify_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_payload + us_info_elem_offset, (oal_int32)(ul_msg_len - us_info_elem_offset));
    if (OAL_PTR_NULL != puc_opmode_notify_ie)
    {
        uc_mgmt_frm_type  = mac_get_frame_sub_type(puc_mac_hdr);
        pst_opmode_notify = (mac_opmode_notify_stru *)(puc_opmode_notify_ie + MAC_IE_HDR_LEN);
        ul_relt = hmac_ie_proc_opmode_field(pst_mac_vap, pst_mac_user, pst_opmode_notify, uc_mgmt_frm_type);
        if (OAL_UNLIKELY(OAL_SUCC != ul_relt))
        {
            OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_check_opmode_notify::hmac_config_send_event failed[%d].}", ul_relt);
            return ul_relt;
        }
        /* opmodeϢͬ��dmac */
        ul_relt = hmac_config_update_opmode_event(pst_mac_vap, pst_mac_user, uc_mgmt_frm_type);
        if (OAL_UNLIKELY(OAL_SUCC != ul_relt))
        {
            OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_check_opmode_notify::hmac_config_send_event failed[%d].}", ul_relt);

			return ul_relt;
        }
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
oal_void hmac_del_virtual_inf_worker(oal_work_stru *pst_del_virtual_inf_work)
{
    oal_net_device_stru         *pst_net_dev;
    hmac_vap_stru               *pst_hmac_vap;
    oal_wireless_dev_stru       *pst_wireless_dev;
    hmac_device_stru            *pst_hmac_device;

    pst_hmac_vap     = OAL_CONTAINER_OF(pst_del_virtual_inf_work, hmac_vap_stru, st_del_virtual_inf_worker);
    pst_net_dev      = pst_hmac_vap->pst_del_net_device;
    pst_wireless_dev = OAL_NETDEVICE_WDEV(pst_net_dev);

    oal_net_unregister_netdev(pst_net_dev);

	/* ���ͷ�net_device ���ͷ�wireless_device �ڴ� */
    OAL_MEM_FREE(pst_wireless_dev, OAL_TRUE);

    pst_hmac_vap->pst_del_net_device = OAL_PTR_NULL;

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (pst_hmac_device == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                    "{hmac_del_virtual_inf_worker::pst_hmac_device is null !device_id[%d]}",
                    pst_hmac_vap->st_vap_base_info.uc_device_id);
        return;
    }

    hmac_clr_p2p_status(&pst_hmac_device->ul_p2p_intf_status, P2P_STATUS_IF_DELETING);

    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                    "{hmac_del_virtual_inf_worker::end !pst_hmac_device->ul_p2p_intf_status[%x]}",
                    pst_hmac_device->ul_p2p_intf_status);
    OAL_SMP_MB();
    OAL_WAIT_QUEUE_WAKE_UP(&pst_hmac_device->st_netif_change_event);

}
#endif	/* _PRE_WLAN_FEATURE_P2P */

/*lint -e19*/
oal_module_symbol(hmac_vap_get_priv_cfg);
oal_module_symbol(hmac_vap_get_net_device);
oal_module_symbol(hmac_vap_set_asoc_req_ie_ptr_null);
oal_module_symbol(hmac_vap_get_desired_country);
#ifdef _PRE_WLAN_FEATURE_11D
oal_module_symbol(hmac_vap_get_updata_rd_by_ie_switch);
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
oal_module_symbol(hmac_del_virtual_inf_worker);
#endif /* _PRE_WLAN_FEATURE_P2P */
/*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

