/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_user.c
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
#include "oam_ext_if.h"
#include "dmac_user.h"
#include "dmac_11i.h"
#include "dmac_wep.h"
#include "dmac_alg.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_tx_complete.h"
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

#include "dmac_11w.h"
#endif
#include "oam_ext_if.h"
#include "dmac_beacon.h"
#include "dmac_psm_sta.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_USER_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE_USER_TRACK

OAL_STATIC oal_uint32  dmac_user_track_init(dmac_user_stru  *pst_dmac_user)
{
    pst_dmac_user->st_txrx_protocol.en_rx_flg = OAL_TRUE;
    pst_dmac_user->st_txrx_protocol.en_tx_flg = OAL_TRUE;

    OAL_MEMZERO(&pst_dmac_user->st_user_track_ctx, OAL_SIZEOF(mac_user_track_ctx_stru));

    return OAL_SUCC;
}


oal_uint32  dmac_user_check_txrx_protocol_change(
                                  dmac_user_stru *pst_dmac_user,
                                  oal_uint8      uc_present_mode,
                                  oam_user_info_change_type_enum_uint8  en_type)
{
    mac_user_stru *pst_mac_user = (mac_user_stru *)pst_dmac_user;
    if (OAL_PTR_NULL == pst_mac_user)
    {
        MAC_ERR_LOG(0, "pst_mac_user is null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch (en_type)
    {
        case OAM_USER_INFO_CHANGE_TYPE_TX_PROTOCOL:
            /* ����ǵ�һ�μ�¼����ֱ�Ӹ�ֵ�����ñȽ��ϱ� */
            if (OAL_TRUE == pst_dmac_user->st_txrx_protocol.en_tx_flg)
            {
                pst_dmac_user->st_txrx_protocol.uc_tx_protocol = uc_present_mode;
                pst_dmac_user->st_txrx_protocol.en_tx_flg = OAL_FALSE;
            }
            else if (uc_present_mode == pst_dmac_user->st_txrx_protocol.uc_tx_protocol)
            {
                ;
            }
            else
            {
                mac_user_change_info_event(pst_mac_user->auc_user_mac_addr,
                                           pst_mac_user->uc_vap_id,
                                           (oal_uint32)pst_dmac_user->st_txrx_protocol.uc_tx_protocol,
                                           (oal_uint32)uc_present_mode,
                                           OAM_MODULE_ID_DMAC,
                                           en_type);
                pst_dmac_user->st_txrx_protocol.uc_tx_protocol = uc_present_mode;
            }
        break;

        case OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL:
            if (OAL_TRUE == pst_dmac_user->st_txrx_protocol.en_rx_flg)
            {
                pst_dmac_user->st_txrx_protocol.uc_rx_protocol = uc_present_mode;
                pst_dmac_user->st_txrx_protocol.en_rx_flg = OAL_FALSE;
            }
            else if (uc_present_mode == pst_dmac_user->st_txrx_protocol.uc_rx_protocol)
            {
                ;
            }
            else
            {
                mac_user_change_info_event(pst_mac_user->auc_user_mac_addr,
                                           pst_mac_user->uc_vap_id,
                                           (oal_uint32)pst_dmac_user->st_txrx_protocol.uc_rx_protocol,
                                           (oal_uint32)uc_present_mode,
                                           OAM_MODULE_ID_DMAC,
                                           en_type);
                pst_dmac_user->st_txrx_protocol.uc_rx_protocol = uc_present_mode;
            }
        break;

        default:
        break;
    }

    return OAL_SUCC;
}


#endif

/*****************************************************************************
 �� �� ��  : dmac_user_init
 ��������  : ��ʼ��DMAC �û�
 �������  : ָ���û���ָ��
 �������  : ʧ��ԭ���ɹ�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : ������53369
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_init(dmac_user_stru *pst_dmac_user)
{
    mac_vap_stru            *pst_mac_vap;

    /* ���dmac user�ṹ�� */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_user) + OAL_SIZEOF(mac_user_stru), OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru));

    /* ����dmac user�Ľ���ģʽ */
    pst_dmac_user->bit_ps_mode     = OAL_FALSE;
    pst_dmac_user->ul_probe_req_ts = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* RSSIͳ������ʼ�� */
    pst_dmac_user->c_rx_rssi = WLAN_RSSI_DUMMY_MARKER;
    pst_dmac_user->uc_max_key_index = 0;

    /* ��ʼ��ʱ��� */
    pst_dmac_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��ʼ��seq num���� */
    OAL_MEMZERO(pst_dmac_user->aus_txseqs, WLAN_TID_MAX_NUM * OAL_SIZEOF(pst_dmac_user->aus_txseqs[0]));
    OAL_MEMZERO(pst_dmac_user->aus_txseqs_frag, WLAN_TID_MAX_NUM * OAL_SIZEOF(pst_dmac_user->aus_txseqs_frag[0]));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    /* ��ʼ����QOS֡��seq_num 12λȫΪ1 */
    pst_dmac_user->us_non_qos_seq_frag_num = 65535;
#endif
    /* DMAC USER TID ��ʼ�� */
    dmac_tid_tx_queue_init(pst_dmac_user->ast_tx_tid_queue, &(pst_dmac_user->st_user_base_info));

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL  == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX, "{dmac_user_init::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����mac_user_stru�е�gruopid��partial aid������Ա����,beaforming��txop ps���õ� */
    dmac_user_set_groupid_partial_aid(pst_mac_vap,pst_dmac_user);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* ���usrͳ����Ϣ */
    oam_stats_clear_user_stat_info(pst_dmac_user->st_user_base_info.us_assoc_id);
#endif
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    /* ��ʼ��ά���õ���Ϣ */
    dmac_user_track_init(pst_dmac_user);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_add_multi_user
 ��������  : dmac�����鲥�û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_multi_user_idx)
{
    dmac_user_stru  *pst_dmac_multi_user;
    oal_uint16       us_user_idx;
    dmac_vap_stru   *pst_dmac_vap;
    oal_uint32       ul_ret;

    us_user_idx = us_multi_user_idx;
    mac_res_alloc_dmac_user(us_user_idx);

    pst_dmac_multi_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_multi_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_init(&pst_dmac_multi_user->st_user_base_info, us_user_idx, OAL_PTR_NULL, pst_mac_vap->uc_chip_id,  pst_mac_vap->uc_device_id, pst_mac_vap->uc_vap_id);
#endif

    dmac_user_init(pst_dmac_multi_user);

    /* �鲥�û����ǻ�Ծ�� */
    pst_dmac_multi_user->bit_active_user = OAL_TRUE;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    dmac_alg_add_assoc_user_notify(pst_dmac_vap, pst_dmac_multi_user);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        ul_ret = dmac_psm_user_ps_structure_init(pst_dmac_multi_user);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;
}
oal_uint32  dmac_user_del_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx)
{
    mac_device_stru                *pst_mac_device;
    dmac_user_stru                 *pst_dmac_user;
    dmac_vap_stru                  *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* dmac user��ز���ȥע�� */
    dmac_alg_del_assoc_user_notify(pst_dmac_vap, pst_dmac_user);

    /* ɾ��tid�����е�������Ϣ */
    dmac_tid_clear(&(pst_dmac_user->st_user_base_info), pst_mac_device);

    /* ɾ���û����ܽṹ */
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_psm_user_ps_structure_destroy(pst_dmac_user);
    }

    /* ����user */
    OAL_MEMZERO((oal_uint8 *)pst_dmac_user + OAL_SIZEOF(mac_user_stru), OAL_SIZEOF(dmac_user_stru)- OAL_SIZEOF(mac_user_stru));

    mac_res_free_mac_user(us_user_idx);

    return OAL_SUCC;
}


oal_uint32  dmac_user_get_tid_by_num(mac_user_stru *pst_mac_user, oal_uint8 uc_tid_num, dmac_tid_stru **ppst_tid_queue)
{
    dmac_user_stru     *pst_dmac_user;

    if ((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == ppst_tid_queue))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_user_get_tid_by_num::param null, pst_mac_user=%d, ppst_tid_queue=%d.}",
                       pst_mac_user, ppst_tid_queue);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_tid_by_num::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_num]);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_is_user_in_smartant_training
 ��������  : ��ȡ��ǰ�û��Ƿ�����������ѵ��״̬
 �������  : pst_user: ָ��user��ָ��
 �������  : pen_is_training: ����״̬
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_user_get_smartant_training_state(
                mac_user_stru                          *pst_user,
                dmac_user_smartant_training_enum_uint8 *pen_training_state)
{
    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_training_state::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_training_state = pst_dmac_user->en_smartant_training;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 �� �� ��  : dmac_set_user_in_smartant_training
 ��������  : ���õ�ǰ����������ѵ��״̬
 �������  : pst_user      : ָ���û���ָ��
             en)is_training: Ҫ���õ�״̬
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_set_smartant_training_state(
                mac_user_stru                              *pst_user,
                dmac_user_smartant_training_enum_uint8      en_training_state)
{
    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_training_state::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_smartant_training = en_training_state;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_user_get_smartant_normal_rate_stats
 ��������  : ��ȡ�û��ĵ�ǰ����ͳ����Ϣ
 �������  : pst_mac_user        : ָ���û���ָ��
 �������  : ppst_rate_stats_info: ָ������ͳ����Ϣ
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_get_smartant_normal_rate_stats(
                mac_user_stru                      *pst_mac_user,
                dmac_tx_normal_rate_stats_stru    **ppst_rate_stats_info)
{

    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_rate_stats_info = &(pst_dmac_user->st_smartant_rate_stats);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 �� �� ��  : dmac_user_set_smartant_normal_rate_stats
 ��������  : �����û��ĵ�ǰ����ͳ����Ϣ
 �������  : pst_mac_user: ָ���û���ָ��
 �������  : pst_rate_stats_info: ����ͳ����Ϣ
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_set_smartant_normal_rate_stats(
                mac_user_stru                  *pst_mac_user,
                dmac_tx_normal_rate_stats_stru *pst_rate_stats_info)
{

    dmac_tx_normal_rate_stats_stru *pst_rate_stats;
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_set_smartant_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rate_stats = &(pst_dmac_user->st_smartant_rate_stats);

    pst_rate_stats->ul_best_rate_goodput_kbps = pst_rate_stats_info->ul_best_rate_goodput_kbps;

    pst_rate_stats->ul_rate_kbps        = pst_rate_stats_info->ul_rate_kbps;
    pst_rate_stats->uc_aggr_subfrm_size = pst_rate_stats_info->uc_aggr_subfrm_size;
    pst_rate_stats->uc_per              = pst_rate_stats_info->uc_per;

    return OAL_SUCC;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : dmac_user_get_txchain_mask
 ��������  : ��ȡ��ͬ�ռ����µ�TX CHAIN MASK
 �������  : pst_user: ָ���û���ָ��
             en_nss: �ռ���ö��
 �������  : puc_chainmask: tx chain mask
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_get_txchain_mask(
                mac_user_stru          *pst_user,
                wlan_nss_enum_uint8     en_nss,
                oal_uint8              *puc_chainmask)
{
    dmac_user_stru                 *pst_dmac_user;

    if (en_nss >= WLAN_NSS_BUTT)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_get_txchain_mask::invalid en_nss[%d].", en_nss);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_get_txchain_mask::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_chainmask = pst_dmac_user->auc_txchain_mask[en_nss];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_set_txchain_mask
 ��������  : ��ȡ��ͬ�ռ����µ�TX CHAIN MASK
 �������  : pst_user: ָ���û���ָ��
             en_nss: �ռ���ö��
 �������  : puc_chainmask: tx chain mask
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_set_txchain_mask(
                mac_user_stru          *pst_user,
                wlan_nss_enum_uint8     en_nss,
                oal_uint8               uc_chainmask)
{
    dmac_user_stru                 *pst_dmac_user;

    if (en_nss >= WLAN_NSS_BUTT)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_set_txchain_mask::invalid en_nss[%d].", en_nss);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_set_txchain_mask::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->auc_txchain_mask[en_nss] = uc_chainmask;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_user_get_vip_flag
 ��������  : ��ȡ�û���VIP����
 �������  : pst_user      : ָ��user�û���ָ��
 �������  :
 �� �� ֵ  : true - vip; false - ��vip
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  dmac_user_get_vip_flag(mac_user_stru  *pst_user)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_get_vip_flag::pst_dmac_user null.}");

        return OAL_FALSE;
    }

    return pst_dmac_user->en_vip_flag;
}


/*****************************************************************************
 �� �� ��  : dmac_user_get_ps_mode
 ��������  : ��ȡ�û���ps_mode
 �������  : pst_user      : ָ��user�û���ָ��
 �������  :
 �� �� ֵ  : true - ����ps_mode;
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  dmac_user_get_ps_mode(mac_user_stru  *pst_user)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_get_ps_mode::pst_dmac_user null.}");

        return OAL_FALSE;
    }

    return pst_dmac_user->bit_ps_mode;
}

/*****************************************************************************
 �� �� ��  : dmac_user_get_vip_flag
 ��������  : ��ȡ�û���VIP����
 �������  : pst_user      : ָ��user�û���ָ��
 �������  : pen_vip_flag
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_set_vip_flag(
                mac_user_stru               *pst_user,
                oal_bool_enum_uint8          en_vip_flag)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_set_vip_flag::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_vip_flag = en_vip_flag;

    return OAL_SUCC;
}


oal_void dmac_user_init_slottime(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    hal_to_dmac_device_stru    *pst_hal_device;

    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_user_init_slottime::hal dev null, fail to update slot time.}");
        return;
    }

    if (WLAN_LEGACY_11B_MODE == pst_mac_user->en_cur_protocol_mode)
    {
        hal_cfg_slottime_type(pst_hal_device, 1);
    }
    else
    {
        hal_cfg_slottime_type(pst_hal_device, 0);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_user_inactive
 ��������  : �����û�Ϊ�ǻ�Ծ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_inactive(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_mac_vap;
#ifdef  _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_stru       *pst_mac_vap_proxysta;
#endif
    oal_uint32          ul_ret;

    /* �Ѿ��Ƿǻ�Ծ�û���ֱ�ӷ��� */
    if (OAL_FALSE == pst_dmac_user->bit_active_user)
    {
        return OAL_SUCC;
    }

    //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_inactive::one user will be set inactive, user aid=%d.}",
    //              pst_dmac_user->st_user_base_info.us_assoc_id);

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_inactive::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �黹lut index */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    /* ɾ����Կ */
    pst_mac_vap_proxysta = mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_main_proxysta))
        {
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

    pst_dmac_user->bit_active_user = OAL_FALSE;

#if 0
    if (pst_mac_device->uc_active_user_cnt)
    {
        pst_mac_device->uc_active_user_cnt--;
    }
#else
    mac_device_dec_active_user(pst_mac_device);
#endif

    /* ɾ����Կ */
    pst_mac_vap = mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "dmac_user_del::pst_mac_vap==NULL\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = dmac_11i_remove_key_from_user(pst_mac_vap, pst_dmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "dmac_user_del::dmac_11i_remove_key_from_user=%u\r\n",ul_ret);
        return ul_ret;
    }

    /* ��gtk��ƹ��ָʾλ��0 ע��:��λap�����ã�staʹ��*/
    dmac_reset_gtk_token(pst_mac_vap);

    OAM_INFO_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_WPA, "dmac_user_del::lutidx %u, usridx %u\r\n", pst_dmac_user->uc_lut_index, pst_dmac_user->st_user_base_info.us_assoc_id);

    ul_ret = dmac_11i_del_peer_macaddr(pst_mac_vap,pst_dmac_user->uc_lut_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_WPA, "dmac_user_del::dmac_11i_del_peer_macaddr=%u\r\n",ul_ret);
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_active_timer
 ��������  : ��Ծ��ʱ�����ڴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_active_timer(void *p_arg)
{
    mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;
    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint32           ul_runtime;
    oal_uint32           ul_present_time;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_active_timer::p_arg null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ����device�������û����Գ�����Ծʱ����û����ǻ�Ծ���� */
    /* ҵ��vap��1��ʼ */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_active_timer::pst_mac_vap null.");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* ��Ծ�û�����ֻ���APģʽ����APģʽ������ */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
            if (OAL_PTR_NULL == pst_dmac_user_tmp)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_user_active_timer::pst_dmac_user_tmp null.");
                return OAL_ERR_CODE_PTR_NULL;
            }

            ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_user_tmp->ul_last_active_timestamp, ul_present_time);

            if (ul_runtime > WLAN_USER_ACTIVE_TO_INACTIVE_TIME)
            {
                dmac_user_inactive(pst_dmac_user_tmp);
            }
        }
    }

    /* �����Ծ�û�С�ڹ��-1���ر�ת�ǻ�Ծ��ʱ�� */
    if (pst_mac_device->uc_active_user_cnt < WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->st_active_user_timer));
        OAM_INFO_LOG0(0, OAM_SF_CFG, "{dmac_user_active_timer::destroy active user timer.}\r\n");
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_active
 ��������  : �����û�Ϊ��Ծ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_active(dmac_user_stru *pst_dmac_user)
{
    oal_uint8           uc_lut_idx;
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_stru       *pst_mac_vap_proxysta;
#endif
    mac_user_stru      *pst_mac_user;

    pst_mac_user = &(pst_dmac_user->st_user_base_info);

    /* �Ѿ��ǻ�Ծ�û���ֱ�ӷ��� */
    if (OAL_TRUE == pst_dmac_user->bit_active_user)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_user->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM.}");
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_vap_proxysta = mac_res_get_mac_vap(pst_mac_user->uc_vap_id);

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_main_proxysta))
        {
            uc_lut_idx = pst_mac_vap_proxysta->st_vap_proxysta.uc_lut_idx;
        }
        else
        {
            uc_lut_idx = mac_user_get_ra_lut_index_proxysta(pst_mac_device->auc_ra_lut_index_table);
        }
    }
    else
    {
    /* ����lut index */
    uc_lut_idx = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
    }
#else
    /* ����lut index */
    uc_lut_idx = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
#endif
    if (uc_lut_idx >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::uc_lut_idx >= WLAN_ACTIVE_USER_MAX_NUM.}");
        return OAL_FAIL;
    }
    pst_dmac_user->uc_lut_index = uc_lut_idx;
    pst_dmac_user->bit_active_user   = OAL_TRUE;

#if 0
    pst_mac_device->uc_active_user_cnt++;
#else
    mac_device_inc_active_user(pst_mac_device);
#endif

    /* ����hal lut index */
    hal_machw_seq_num_index_update_per_tid(pst_mac_device->pst_device_stru, uc_lut_idx, OAL_TRUE);

    /* �����Ծ�û��ﵽ���-1������ת�ǻ�Ծ���� */
    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        if (OAL_FALSE == pst_mac_device->st_active_user_timer.en_is_registerd)
        {
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_active_user_timer,
                                   dmac_user_active_timer,
                                   WLAN_USER_ACTIVE_TRIGGER_TIME,               /* 1000ms����һ�� */
                                   pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }

    /* ������Կ */
    pst_mac_vap = mac_res_get_mac_vap(pst_mac_user->uc_vap_id);
    return dmac_11i_add_key_from_user(pst_mac_vap, pst_dmac_user);

}
oal_uint32  dmac_send_null_frame_to_sta(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    dmac_vap_stru             *pst_dmac_vap;
    dmac_user_stru            *pst_dmac_user;
#ifdef _PRE_WLAN_FEATURE_UAPSD
    oal_uint8                  uc_ac          =  WLAN_WME_AC_VO;
    oal_uint8                  uc_uapsd_flag  =  OAL_FALSE;
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
	oal_int8                   c_i;
#endif

    /* ��ȡvap�ṹ��Ϣ */
    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta::pst_dmac_vap null.}");
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    /* ��ȡuser�ṹ��Ϣ */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta::pst_dmac_user null. user idx = [%d]}",
                               pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_AP ==  pst_mac_vap->en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_UAPSD
        /* AP�����user����״̬��ѡ��null֡����Qos null֡ */
        uc_uapsd_flag = pst_dmac_user->uc_uapsd_flag;

        if (OAL_FALSE != (uc_uapsd_flag & MAC_USR_UAPSD_EN))
        {
            for(c_i = MAC_AC_PARAM_LEN - 1; c_i >= 0; c_i--)
            {
                if (OAL_TRUE == pst_dmac_user->st_uapsd_status.uc_ac_trigger_ena[c_i])
                {
                    uc_ac = (oal_uint8)c_i;
                    break;
                }
            }
            return dmac_send_qosnull(pst_dmac_vap, pst_dmac_user, uc_ac, OAL_FALSE);
        }
    #endif
        /* �û����ڷǽ���״̬ */
        return dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta:: vap mode %d is wrong.}", pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }

    return OAL_FAIL;

}


oal_uint32  dmac_user_keepalive_timer(void *p_arg)
{
    mac_device_stru     *pst_mac_device;
    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    oal_dlist_head_stru *pst_user_list_head;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint32           ul_runtime;
    oal_uint32           ul_present_time;
    oal_uint32           ul_list_count = 0;
    oal_uint32           ul_aging_time;
    oal_uint32           ul_send_null_frame_time;

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = (mac_device_stru *)p_arg;

    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();


    /* ����device�µ������û����������ϻ���ɾ���� */
    /* ҵ��vap��1��ʼ */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::pst_mac_vap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* �û��ϻ�ֻ���APģʽ����APģʽ������ ��û��keepalive���������� */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        /* ���keepalive �����ѹ�, ��ʱ��ʱ�����ǿ����Ļ��͹رն�ʱ�� */
        if (OAL_FALSE ==  pst_mac_vap->st_cap_flag.bit_keepalive)
        {
            if (OAL_TRUE == pst_mac_device->st_keepalive_timer.en_is_registerd)
            {
               FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->st_keepalive_timer));
            }
            continue;
        }


        ul_aging_time           = WLAN_USER_AGING_TIME;
        ul_send_null_frame_time = WLAN_USER_KEEPALIVE_SEND_NULL;

#ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_GO(pst_mac_vap))
        {
            ul_aging_time           = WLAN_P2PGO_USER_AGING_TIME;
            ul_send_null_frame_time = WLAN_GO_USER_KEEPALIVE_SEND_NULL;
        }
#endif

        pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

        for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

            /* ָ��˫��������һ���ڵ� */
            pst_entry = pst_entry->pst_next;

            if (OAL_PTR_NULL == pst_dmac_user_tmp)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "pst_dmac_user_tmp is null. us_assoc_id is %d", pst_user_tmp->us_assoc_id);
                return OAL_ERR_CODE_PTR_NULL;
            }

            ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_user_tmp->ul_last_active_timestamp, ul_present_time);

            if (ul_runtime > ul_aging_time)
            {
                dmac_send_disasoc_misc_event(pst_mac_vap,pst_user_tmp->us_assoc_id, DMAC_DISASOC_MISC_KEEPALIVE);
            }
            else if(ul_runtime > ul_send_null_frame_time)
            {
                dmac_send_null_frame_to_sta(pst_mac_vap, pst_user_tmp);
                OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::send null frame to %02X:XX:XX:%02X:%02X:%02X.}",
                        pst_user_tmp->auc_user_mac_addr[0],
                        pst_user_tmp->auc_user_mac_addr[3],
                        pst_user_tmp->auc_user_mac_addr[4],
                        pst_user_tmp->auc_user_mac_addr[5]);

            }

            if(ul_list_count++ > WLAN_ACTIVE_USER_MAX_NUM)
            {
#ifdef _PRE_WLAN_DFT_STAT
                OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer:st_mac_user_list_head ul_hash_cnt = %d ul_dlist_cnt = %d.}",pst_mac_vap->ul_hash_cnt,pst_mac_vap->ul_dlist_cnt);
#endif
                break;
            }
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_add
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
oal_uint32  dmac_user_add(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16                      us_user_idx;
    dmac_user_stru                 *pst_dmac_user;
    frw_event_stru                 *pst_event;
    dmac_ctx_add_user_stru         *pst_add_user_payload;
    oal_uint32                      ul_ret;
    oal_uint8                       uc_lut_index;
    mac_device_stru                *pst_mac_device;
    oal_uint16                      us_max_asoc_user;
    mac_vap_stru                    *pst_mac_vap;
    dmac_vap_stru                   *pst_dmac_vap;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_event_mem)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_add::pst_event_mem null.}");
        return OAL_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    us_user_idx          = pst_add_user_payload->us_user_idx;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG4(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::us_user_idx:%d,user mac[0-2]:%.2x:%.2x:%.2x}",
                     us_user_idx,
                     pst_add_user_payload->auc_user_mac_addr[0],
                     pst_add_user_payload->auc_user_mac_addr[1],
                     pst_add_user_payload->auc_user_mac_addr[2]);
    OAM_WARNING_LOG3(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::user mac[3-5]:%.2x:%.2x:%.2x}",
                     pst_add_user_payload->auc_user_mac_addr[3],
                     pst_add_user_payload->auc_user_mac_addr[4],
                     pst_add_user_payload->auc_user_mac_addr[5]);

    /* ����dmac user */
    ul_ret = mac_res_alloc_dmac_user(us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::mac_res_alloc_dmac_user failed[%d].", ul_ret);

        return ul_ret;
    }

    /* ��ȡdmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::pst_dmac_user null.}");

        mac_res_free_mac_user(us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_add::get mac_vap_stru fail.}");

        mac_res_free_mac_user(us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* mac user��ʼ�� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ��ʼ��0 */
    OAL_MEMZERO(&(pst_dmac_user->st_user_base_info), OAL_SIZEOF(mac_user_stru));
    mac_user_init(&(pst_dmac_user->st_user_base_info), us_user_idx, pst_add_user_payload->auc_user_mac_addr,
                  pst_event->st_event_hdr.uc_chip_id,
                  pst_event->st_event_hdr.uc_device_id,
                  pst_event->st_event_hdr.uc_vap_id);

    ul_ret = mac_vap_add_assoc_user(pst_mac_vap, us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        mac_res_free_mac_user(us_user_idx);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_add::mac_vap_add_assoc_user fail.}");
        return OAL_FAIL;
    }

    pst_mac_device->uc_asoc_user_cnt++;

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_mac_vap, (oal_uint8)us_user_idx);
    }

    /* ���¹����û���ʱ������ƹ��λ */
    dmac_reset_gtk_token(pst_mac_vap);
#endif

    /* dmac user��ʼ�� */
    dmac_user_init(pst_dmac_user);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        ul_ret = dmac_psm_user_ps_structure_init(pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_add::psm user fail.}");
            mac_res_free_mac_user(us_user_idx);
            return ul_ret;
        }
    }
    /* ��ʼ��linkloss��״̬ */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    dmac_vap_linkloss_clean(pst_dmac_vap);

    /* ����keepalive��ʱ��, ����ʱ���ѿ���, �����ٿ��� */
    if ((OAL_FALSE == pst_mac_device->st_keepalive_timer.en_is_registerd) &&
        (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_keepalive))
    {
        FRW_TIMER_CREATE_TIMER(&(pst_mac_device->st_keepalive_timer),
                               dmac_user_keepalive_timer,
                               WLAN_USER_KEEPALIVE_TRIGGER_TIME,                /* 30s����һ��(1101��60s����һ��) TBD:�������� */
                               pst_mac_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,
                               pst_mac_device->ul_core_id);
    }

#ifdef _PRE_WLAN_FEATURE_UAPSD
    ul_ret = dmac_uapsd_user_init(pst_dmac_user);
    if(OAL_SUCC!= ul_ret)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::dmac_uapsd_user_init failed.}");
        mac_res_free_mac_user(us_user_idx);
        return ul_ret;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PM
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        dmac_pm_post_event(pst_dmac_vap,AP_PWR_EVENT_USR_ASSOC,0,OAL_PTR_NULL);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* ����lut index,�������Proxy STA����Ϊap0��userΪ0~15,proxystaΪ16~31,��������ã�user��Ϊ0~31 */
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            uc_lut_index = pst_mac_vap->st_vap_proxysta.uc_lut_idx;
        }
        else
        {
            uc_lut_index = mac_user_get_ra_lut_index_proxysta(pst_mac_device->auc_ra_lut_index_table);
        }
    }
    else
    {
        /* ����lut index */
        uc_lut_index = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
    }
#else
    /* ����lut index */
    uc_lut_index = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
#endif
    if (uc_lut_index >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::add failed,uc_lut_index=%d,us_user_idx=%d.}",
                            uc_lut_index, us_user_idx);

        /* �쳣�ͷ��ڴ� */
        mac_res_free_mac_user(us_user_idx);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::uc_lut_index=%d.}", uc_lut_index);

    /* ��Ծ�û���+1 */
    pst_mac_device->uc_active_user_cnt++;
    pst_dmac_user->bit_active_user = OAL_TRUE;
    pst_dmac_user->uc_lut_index    = uc_lut_index;


    /* ����оƬά�������к� */
    hal_set_tx_sequence_num(pst_mac_device->pst_device_stru, uc_lut_index, 0, 0, 0);

    /* �����Ծ�û��ﵽ���-1������ת�ǻ�Ծ���� */
    us_max_asoc_user = mac_res_get_max_asoc_user();
    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        if (us_max_asoc_user <= WLAN_ACTIVE_USER_MAX_NUM)
        {
            /* �������û�С��32��������ת�ǻ�Ծ */
            /* do nothing */
        }
        else if (OAL_FALSE == pst_mac_device->st_active_user_timer.en_is_registerd)
        {
            /* �����ʱ��û��ʹ�ܣ�˵����ʱ��û��������������ʱ�� */

            //OAM_INFO_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::start active user timer.}\r\n");

            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_active_user_timer,
                                   dmac_user_active_timer,
                                   WLAN_USER_ACTIVE_TRIGGER_TIME,               /* 1000ms����һ�� */
                                   pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }

#ifdef _PRE_WLAN_FEATURE_ROAM
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        dmac_sta_roam_trigger_init((dmac_vap_stru *)pst_mac_vap);
    }
#endif //_PRE_WLAN_FEATURE_ROAM

    OAM_WARNING_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::add succ,us_user_idx=%d.}", us_user_idx);


    return OAL_SUCC;
}



oal_uint32  dmac_user_add_notify_alg(frw_event_mem_stru *pst_event_mem)
{
    oal_uint32               ul_ret;
    dmac_vap_stru           *pst_dmac_vap;
    frw_event_stru          *pst_event;
    dmac_user_stru          *pst_dmac_user;
    dmac_ctx_add_user_stru  *pst_add_user_payload;

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ֪ͨ�㷨 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    //oal_memcmp(pst_dmac_vap->st_vap_base_info.auc_bssid, pst_add_user_payload->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_add_user_payload->us_user_idx);
    mac_vap_set_aid(&pst_dmac_vap->st_vap_base_info, pst_add_user_payload->us_sta_aid);
    mac_user_set_assoc_id(&pst_dmac_user->st_user_base_info, pst_add_user_payload->us_user_idx);

    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &pst_add_user_payload->st_ht_hdl);
    mac_user_set_vht_hdl(&pst_dmac_user->st_user_base_info, &pst_add_user_payload->st_vht_hdl);
    if (pst_dmac_user->st_user_base_info.st_vht_hdl.bit_vht_txop_ps)
    {
        pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_txop_ps = OAL_TRUE;
    }

    ul_ret = dmac_alg_add_assoc_user_notify(pst_dmac_vap, pst_dmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_add_notify_alg::dmac_alg_add_assoc_user_notify failed[%d].", ul_ret);
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_alg_vap_up_notify(&(pst_dmac_vap->st_vap_base_info));
    }

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32  dmac_user_del_offload(mac_vap_stru* pst_vap, oal_uint16 us_user_idx)
{
    mac_device_stru   *pst_mac_device;
    oal_uint32         ul_ret;

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_user_del_offload::mac_vap_del_user usridx[%d]}", us_user_idx);

    /* ��vap��ɾ���û� */
    ul_ret = mac_vap_del_user(pst_vap, us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_del::vap del failed.}");
    }

    /* �ͷ��û��ڴ� */
    mac_res_free_mac_user(us_user_idx);

    /* device���ѹ���user����-- */
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_user_del_offload::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device->uc_asoc_user_cnt--;

    /* STAģʽ�½�������VAP��id��Ϊ�Ƿ�ֵ */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_vap, 0xff);
    }

    return OAL_SUCC;
}

#endif

oal_uint32  dmac_user_del(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16                      us_user_idx;
    dmac_user_stru                 *pst_dmac_user;
    dmac_vap_stru                  *pst_dmac_vap;
    frw_event_stru                 *pst_event;
    dmac_ctx_del_user_stru         *pst_del_user_payload;
    mac_device_stru                *pst_mac_device;
    oal_uint32                      ul_rslt = OAL_FAIL;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_event_mem)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_del::pst_event_mem null.}");
        return OAL_FAIL;
    }
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_del_user_payload = (dmac_ctx_del_user_stru *)pst_event->auc_event_data;
    us_user_idx          = pst_del_user_payload->us_user_idx;

    OAM_WARNING_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_del::useridx==%u}", us_user_idx);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG, "{dmac_user_del::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap   = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG, "{dmac_user_del::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �·���Чuser idx����mac��ַ����user */
    if (MAC_INVALID_USER_ID == us_user_idx)
    {
        ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), pst_del_user_payload->auc_user_mac_addr, &us_user_idx);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_ERROR_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,"{dmac_user_del::Cannot find user by idx[%d],and mac_addr[%02x XX XX XX %02x %02x]!.}",
                        us_user_idx,
                        pst_del_user_payload->auc_user_mac_addr[0],
                        pst_del_user_payload->auc_user_mac_addr[4],
                        pst_del_user_payload->auc_user_mac_addr[5]);
            return OAL_ERR_CODE_PTR_NULL;
        }
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_del::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    /* AP ��Ӳ��PMF���ƿ�����д */
    dmac_11w_update_users_status(pst_dmac_vap, &pst_dmac_user->st_user_base_info, OAL_FALSE);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    /* dmac user��ز���ȥע�� */
    dmac_alg_del_assoc_user_notify(pst_dmac_vap, pst_dmac_user);

    /* �����STAɾ���û�����ʾ��STAȥ�����ˣ�����vap down֪ͨ�� */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_alg_vap_down_notify(&(pst_dmac_vap->st_vap_base_info));

#ifdef _PRE_WLAN_FEATURE_STA_PM
        mac_vap_set_aid(&(pst_dmac_vap->st_vap_base_info), 0);
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_DEASSOCIATE, 0, OAL_PTR_NULL);
#endif

    }

    /* ɾ��tid�����е�������Ϣ */
    dmac_tid_clear(&(pst_dmac_user->st_user_base_info), pst_mac_device);

    #ifdef _PRE_WLAN_FEATURE_UAPSD
      dmac_uapsd_user_destroy(pst_dmac_user);
    #endif

    /* ɾ���û����ܽṹ,���vap����ĸ��û���tim_bitmap��Ϣ */
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_psm_user_ps_structure_destroy(pst_dmac_user);
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);

        if (OAL_TRUE == pst_dmac_user->bit_ps_mode)
        {
            pst_dmac_vap->uc_ps_user_num--;
        }
    }

    dmac_user_inactive(pst_dmac_user);

    /* ���VAPģʽ��STA������Ҫ�ָ�STA�Ĵ�������ʼ״̬ */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
        {
            if (OAL_TRUE ==pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta)
            {
                dmac_vap_sta_reset(pst_dmac_vap);
            }
            else
            {
                /* do nothing����ɾ��user */
            }
        }
        else
        {
            dmac_vap_sta_reset(pst_dmac_vap);
            OAM_INFO_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_PROXYSTA, "{dmac_user_del::reset station register.}");
        }
#else
        dmac_vap_sta_reset(pst_dmac_vap);

#endif
    }

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    /* ���û�����ɾ����ʱ�� */
    if (OAL_TRUE == pst_dmac_user->st_user_track_ctx.st_txrx_param_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_dmac_user->st_user_track_ctx.st_txrx_param_timer);
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_SMPS
    /* ɾ���û�������SMPS���� */
    mac_user_set_sm_power_save(&pst_dmac_user->st_user_base_info, 0);
#endif

    dmac_psm_disable_user_to_psm_back(pst_mac_device,pst_dmac_user);
    dmac_user_del_offload(&pst_dmac_vap->st_vap_base_info, us_user_idx);
#else
    mac_res_free_mac_user(us_user_idx);
#endif

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_user_del::OK.}");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_user_key_search_fail_handler
 ��������  : ����֡key search fail����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_user_key_search_fail_handler(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;

    /* ����û������ڣ�ʲô������ */
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_key_search_fail_handler::pst_dmac_user null.}");
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_key_search_fail_handler::pst_mac_device null.}");
        return;
    }

    /* �����Ծ�û���û��������򽫴��û�תΪ��Ծ�û� */
    if (pst_mac_device->uc_active_user_cnt < WLAN_ACTIVE_USER_MAX_NUM)
    {
        dmac_user_active(pst_dmac_user);
        return;
    }
}


/*****************************************************************************
 �� �� ��  : dmac_user_tx_inactive_user_handler
 ��������  : �������̷ǻ�Ծ�û�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_tx_inactive_user_handler(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_tx_inactive_user_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_tx_inactive_user_handler::active user >= WLAN_ACTIVE_USER_MAX_NUMl.}");
        return OAL_FAIL;
    }

    return dmac_user_active(pst_dmac_user);

}

#ifdef _PRE_WLAN_DFT_EVENT

OAL_STATIC OAL_INLINE oal_void  dmac_user_status_change_to_sdt(
                                       dmac_user_stru       *pst_dmac_user,
                                       oal_bool_enum_uint8   en_is_user_paused )
{
    oal_uint8       auc_event[50] = {0};
    auc_event[0] = en_is_user_paused;

    DMAC_EVENT_PAUSE_OR_RESUME_USER(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                    pst_dmac_user->st_user_base_info.uc_vap_id,
                                    OAM_EVENT_PAUSE_OR_RESUME_USER,
                                    auc_event);
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_user_pause
 ��������  : ��ͣ�û�����TID
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
oal_uint32  dmac_user_pause(dmac_user_stru *pst_dmac_user)
{
    oal_uint8       uc_tid_idx;
    dmac_tid_stru  *pst_tid;
    oal_uint32      ul_ret;

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_pause::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    if (MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_DFT_EVENT
    dmac_user_status_change_to_sdt(pst_dmac_user, OAL_TRUE);
#endif

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx++)
    {
        pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_idx]);

        ul_ret = dmac_tid_pause(pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_PS);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_user_resume
 ��������  : �ָ��û�����TID
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
oal_uint32  dmac_user_resume(dmac_user_stru *pst_dmac_user)
{
    oal_uint8       uc_tid_idx;
    dmac_tid_stru  *pst_tid;
    oal_uint32      ul_ret;
    mac_device_stru *pst_mac_device = OAL_PTR_NULL;


    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_resume::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_resume::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_DFT_EVENT
    dmac_user_status_change_to_sdt(pst_dmac_user, OAL_FALSE);
#endif

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx++)
    {
        pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_idx]);

        ul_ret = dmac_tid_resume(pst_mac_device->pst_device_stru, pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_PS);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;

}



oal_uint32  dmac_user_set_groupid_partial_aid(mac_vap_stru  *pst_mac_vap,
                                                      dmac_user_stru *pst_dmac_user)
{
    oal_uint16     us_temp_partial_aid;
    oal_uint16     us_temp_aid;
    oal_uint8      uc_temp_bssid;


    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_dmac_user->uc_groupid     = 0;

        /* ȡBSSID[39:47] */
        us_temp_partial_aid = OAL_MAKE_WORD16(pst_mac_vap->auc_bssid[4], pst_mac_vap->auc_bssid[5]);

        /* ��bssid��48��bit�ĸ�9bit��Ӧ��10����ֵ��Ϊpaid */
        pst_dmac_user->us_partial_aid = (us_temp_partial_aid & 0xFF80) >> 7;

    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        pst_dmac_user->uc_groupid     = 63;

        us_temp_aid   = pst_dmac_user->st_user_base_info.us_assoc_id & 0x1FF;
        uc_temp_bssid = (pst_mac_vap->auc_bssid[5] & 0x0F) ^ ((pst_mac_vap->auc_bssid[5] & 0xF0) >> 4);
        pst_dmac_user->us_partial_aid = (us_temp_aid + (uc_temp_bssid << 5) ) & ((1 << 9) -1);
    }
    else
    {
        pst_dmac_user->uc_groupid     = 63;
        pst_dmac_user->us_partial_aid = 0;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMPS

oal_uint8 dmac_user_get_smps_mode(mac_vap_stru  *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    wlan_mib_mimo_power_save_enum_uint8 en_vap_smps;
    wlan_mib_mimo_power_save_enum_uint8 en_user_smps;

    if (OAL_TRUE != pst_mac_user->st_ht_hdl.en_ht_capable)
    {
       return WLAN_MIB_MIMO_POWER_SAVE_MIMO;
    }

    en_vap_smps  = pst_mac_vap->st_cap_flag.bit_smps;
    en_user_smps = (wlan_mib_mimo_power_save_enum_uint8)pst_mac_user->st_ht_hdl.bit_sm_power_save;

    return (oal_uint8)((en_vap_smps >= en_user_smps)? en_user_smps : en_vap_smps);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

oal_void dmac_ap_pause_all_user(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru                  *pst_entry;
    oal_dlist_head_stru                  *pst_user_list_head;
    mac_user_stru                        *pst_user_tmp;
    dmac_user_stru                       *pst_dmac_user_tmp;
    mac_device_stru                      *pst_mac_device;

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_ap_pause_all_user}");
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    /* ����vap�������û�,pause tid ���� */
    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

        /* ָ��˫��������һ�� */
        pst_entry = pst_entry->pst_next;

        /* pause tid */
        dmac_user_pause(pst_dmac_user_tmp);

        /* ��ͣ��vap�µ������û���Ӳ�����еķ���, Ӳ���ϱ�psm_back,����ٻ��� */
        hal_tx_enable_peer_sta_ps_ctrl(pst_mac_device->pst_device_stru, pst_dmac_user_tmp->uc_lut_index);
    }
}

oal_void dmac_ap_resume_all_user(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru                  *pst_entry;
    oal_dlist_head_stru                  *pst_user_list_head;
    mac_user_stru                        *pst_user_tmp;
    dmac_user_stru                       *pst_dmac_user_tmp;
    mac_device_stru                      *pst_mac_device;
    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_ap_resume_all_user}");
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    /* ����vap�������û�,pause tid ���� */
    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

        /* ָ��˫��������һ�� */
        pst_entry = pst_entry->pst_next;

        /* pause tid */
        dmac_user_resume(pst_dmac_user_tmp);

        /* �ָ���vap�µ������û���Ӳ�����еķ��� */
        hal_tx_disable_peer_sta_ps_ctrl(pst_mac_device->pst_device_stru, pst_dmac_user_tmp->uc_lut_index);
    }
}
#endif

/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_user_get_tid_by_num);
oal_module_symbol(dmac_user_get_smartant_training_state);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_user_set_smartant_training_state);
#endif
oal_module_symbol(dmac_user_get_smartant_normal_rate_stats);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_user_set_smartant_normal_rate_stats);
#endif
oal_module_symbol(dmac_user_get_vip_flag);
oal_module_symbol(dmac_user_set_vip_flag);
oal_module_symbol(dmac_user_get_ps_mode);


#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(dmac_user_get_smps_mode);
#endif
/*lint +e578*//*lint +e19*/







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

