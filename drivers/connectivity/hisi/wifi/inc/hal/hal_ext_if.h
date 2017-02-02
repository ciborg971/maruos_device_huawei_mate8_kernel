/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hal_ext_if.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��20��
  ����޸�   :
  ��������   : hal���⹫���ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��20��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HAL_EXT_IF_H__
#define __HAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_types.h"
#include "hal_spec.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "hal_lpm_test.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HAL_EXT_IF_H

extern oal_int32 g_l_rf_channel_num;
extern oal_int32 g_l_rf_single_tran;
extern oal_int32 g_l_rf_fem_switch;

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/* ˫оƬ����£�5G��2G��Ӧ��CHIP ID�궨��; ��ͬ��Ƭ��̬��5G��2G��Ӧ��CHIP ID��ͬ */
#ifdef _PRE_WLAN_5G_ON_PCIE0_2G_ON_PCIE1
#define HAL_DOUBLE_CHIP_5G_ID      0
#define HAL_DOUBLE_CHIP_2G_ID      1
#else
#define HAL_DOUBLE_CHIP_5G_ID      1
#define HAL_DOUBLE_CHIP_2G_ID      0
#endif
#endif
/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/* HALģ���DMACģ�鹲�õ�WLAN RX�ṹ�� */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf����һ��Ԫ�� */
    oal_uint16              us_netbuf_num;      /* netbuf����ĸ��� */
    oal_uint8               auc_resv[2];        /* �ֽڶ��� */
}hal_cali_hal2hmac_event_stru;

typedef struct
{
    oal_uint32 ul_packet_idx;

    oal_uint8 auc_payoald[4];
}hal_cali_hal2hmac_payload_stru;


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_int32 hal_main_init(oal_void);
extern oal_void  hal_main_exit(oal_void);
#ifdef _PRE_WLAN_FEATURE_HUT
extern oal_void  hal_to_hut_irq_isr_register(hal_oper_mode_enum_uint8 en_oper_mode, oal_void (*p_func)(oal_void));
extern oal_void  hal_to_hut_irq_isr_unregister(oal_void);
#endif
extern oal_void  hal_get_hal_to_dmac_device(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_hal_device);

/*****************************************************************************
  10.1 оƬ������
*****************************************************************************/
extern oal_uint32 hal_chip_get_chip(oal_uint8 uc_chip_id,  hal_to_dmac_chip_stru **ppst_chip_stru);
extern oal_uint32 hal_chip_get_device_num(oal_uint8 uc_chip_id, oal_uint8 * puc_device_nums);
extern oal_uint32 hal_chip_get_device(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_device_stru);
/*****************************************************************************
  10.2 ���Ⱪ¶�����ýӿ�
*****************************************************************************/


/*****************************************************************************
  10.3 ��Ӧһ��Ӳ��MAC��PHY�ľ�̬��������
*****************************************************************************/
#define HAL_CHIP_LEVEL_FUNC
/*****************************************************************************
  10.3.1 CHIP����   ��һ���������Ϊ hal_to_dmac_chip_stru
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_chip_version(hal_to_dmac_chip_stru * pst_hal_chip, oal_uint32 *pul_chip_ver)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_chip_version, pst_hal_chip, pul_chip_ver);
}

#define HAL_DEVICE_LEVEL_FUNC
/*****************************************************************************
  10.3.2 DEVICE����   ��һ���������Ϊ hal_to_dmac_device_stru
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_rx_init_dscr_queue, pst_device);
}
OAL_STATIC OAL_INLINE oal_void hal_rx_dscr_add_netbuf(hal_to_dmac_device_stru *pst_device, oal_uint32  *pul_ret)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_dscr_add_netbuf, pst_device, pul_ret);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_destroy_netbuf)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_destroy_dscr_queue, pst_device,uc_destroy_netbuf);
}

OAL_STATIC OAL_INLINE oal_void hal_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_al_rx_destroy_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_al_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_al_rx_init_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_init_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_destroy_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_init_hw_rx_isr_list, pst_device);
}
OAL_STATIC OAL_INLINE oal_void hal_free_rx_isr_list(hal_to_dmac_device_stru *pst_device, oal_dlist_head_stru  *pst_rx_isr_list)
{
    HAL_PUBLIC_HOOK_FUNC1(_free_rx_isr_list, pst_rx_isr_list);
}

OAL_STATIC OAL_INLINE oal_void hal_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_destroy_hw_rx_isr_list, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_free_rx_isr_info(hal_to_dmac_device_stru *pst_device, hal_hw_rx_dscr_info_stru *pst_rx_isr_info)
{
    oal_irq_disable();
    oal_dlist_add_tail(&(pst_rx_isr_info->st_dlist_head), &(pst_device->st_rx_isr_info_res_list));
    oal_irq_enable();
}

/*****************************************************************************
 �� �� ��  : hal_get_tx_dscr_queue_total_ppdu_num
 ��������  : ��ȡ5�����Ͷ���(4��EDCA���� + 1�������ȼ�����)�д����͵�PPDU����
 �������  : pst_hal_device: HAL to DEVICE�ṹ��ָ��
 �������  : pus_ppdu_cnt  : ���Ͷ�����PPDU�ĸ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_tx_dscr_queue_total_ppdu_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 *pus_ppdu_cnt)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_tx_dscr_queue_total_ppdu_num, pst_hal_device, pus_ppdu_cnt);
}


/*����������Ļ�����Ϣ������֡���ȡ�mac���ȡ���ȫ��Ϣ*/
OAL_STATIC OAL_INLINE oal_void hal_tx_fill_basic_ctrl_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_fill_basic_ctrl_dscr, p_tx_dscr, pst_mpdu);
}

/* ������������������ */
OAL_STATIC OAL_INLINE oal_void  hal_tx_ctrl_dscr_link(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_ctrl_dscr_link, pst_tx_dscr_prev, pst_tx_dscr);
}

/* ����������next��ȡ��һ����������ַ */
OAL_STATIC OAL_INLINE oal_void  hal_get_tx_dscr_next(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_tx_dscr_next, pst_tx_dscr, ppst_tx_dscr_next);
}

OAL_STATIC OAL_INLINE oal_void  hal_tx_ctrl_dscr_unlink(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_ctrl_dscr_unlink, pst_tx_dscr);
}

/* ���ó�������Ϣ������������������ֶ� */
OAL_STATIC OAL_INLINE oal_void hal_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature)
{
    HAL_PUBLIC_HOOK_FUNC5(_tx_ucast_data_set_dscr, pst_hal_device, pst_tx_dscr, pst_txop_feature, pst_txop_alg, pst_ppdu_feature);
}

/* ���ù���֡���鲥 �㲥����֡��������Ϣ������������������ֶ� */
OAL_STATIC OAL_INLINE oal_void hal_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature)
{
    HAL_PUBLIC_HOOK_FUNC5(_tx_non_ucast_data_set_dscr, pst_hal_device, pst_tx_dscr, pst_txop_feature, pst_txop_alg, pst_ppdu_feature);
}
OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_modify_mac_header_length(hal_to_dmac_device_stru *pst_hal_device,hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_modify_mac_header_length, pst_tx_dscr, uc_mac_header_length);
}

/*****************************************************************************
 �� �� ��  : hal_tx_set_seqno_sw_generate
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_seqno_sw_generate(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_seqno_sw_generate, pst_tx_dscr, uc_sw_seqno_generate);
}

/*���amsdu�����������msdu���������ط������������׶γ��ȣ��Լ��ڶ��γ��� */
OAL_STATIC OAL_INLINE oal_void hal_tx_get_size_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_size_dscr, us_msdu_num, pul_dscr_one_size, pul_dscr_two_size);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_get_vap_id(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id, oal_int32 is_proxysta_feature)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_vap_id, pst_tx_dscr, puc_vap_id,is_proxysta_feature);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_get_dscr_ctrl_one_param(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ctrl_one_param, pst_tx_dscr, pst_tx_dscr_one_param);
}

/*****************************************************************************
 �� �� ��  : hal_tx_get_dscr_tx_cnt
 ��������  : ��ȡMAC�����ķ��ʹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_tx_cnt(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_tx_cnt, pst_tx_dscr, puc_tx_count);
}

/*****************************************************************************
 �� �� ��  : hal_tx_get_dscr_seq_num
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_seq_num(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_seq_num, pst_tx_dscr, pus_seq_num);
}

/*****************************************************************************
 �� �� ��  : hal_tx_get_dscr_seq_num
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_mpdu_num(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_mpdu_num)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_mpdu_num, pst_tx_dscr, puc_mpdu_num);
}



OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_status(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_status, pst_tx_dscr, uc_status);
}

OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_dscr_chiper_type, pst_tx_dscr, puc_chiper_type, puc_chiper_key_id);
}



OAL_STATIC OAL_INLINE oal_void  hal_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_enable_peer_sta_ps_ctrl, pst_hal_device, uc_lut_index);
}

OAL_STATIC OAL_INLINE oal_void  hal_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_disable_peer_sta_ps_ctrl, pst_hal_device, uc_lut_index);
}



/*****************************************************************************
 �� �� ��  : hal_tx_get_dscr_status
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_status(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_status, pst_tx_dscr, puc_status);
}

/*****************************************************************************
 �� �� ��  : hal_tx_get_bar_dscr_ba_ssn
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��12��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_ba_ssn(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ba_ssn, pst_tx_dscr, pus_ba_ssn);
}

/*****************************************************************************
 �� �� ��  : hal_tx_get_bar_dscr_ba_ssn
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��12��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_ba_bitmap(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ba_bitmap, pst_tx_dscr, pul_ba_bitmap);
}

/*****************************************************************************
 �� �� ��  : hal_tx_put_dscr
 ��������  : ���ݶ������ͣ���һ��������������׵�ַ����֪ӲMAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_put_dscr, pst_hal_device, en_tx_queue_type, past_tx_dscr);
}

/*****************************************************************************
 �� �� ��  : hal_get_tx_q_status
 ��������  : ��ȡ���Ͷ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��20��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_tx_q_status, pst_hal_device, pul_status, uc_qnum);
}


OAL_STATIC OAL_INLINE oal_void  hal_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_ampdu_len, pst_hal_device, pst_dscr, pul_ampdu_len);
}

#ifdef _PRE_DEBUG_MODE_USER_TRACK

OAL_STATIC OAL_INLINE oal_void  hal_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_protocol_mode, pst_hal_device, pst_dscr, puc_protocol_mode);
}
#endif

/*��ȡ������������С*/
OAL_STATIC OAL_INLINE oal_void hal_rx_get_size_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_dscr_size)
{
    //HAL_PUBLIC_HOOK_FUNC1(_rx_get_size_dscr, pul_dscr_size);
    *pul_dscr_size = WLAN_RX_DSCR_SIZE;

    /*��������������Ĵ�С����oal��������������ڴ���С����ӡ������Ϣ*/
    if(OAL_UNLIKELY(*pul_dscr_size > WLAN_MEM_SHARED_RX_DSCR_SIZE))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "Rx dscr size: %d is larger than WLAN_MEM_SHARED_RX_DSCR_SIZE(%d)", *pul_dscr_size, WLAN_MEM_SHARED_RX_DSCR_SIZE);
    }
}

/*��ȡ��������Ϣ*/
OAL_STATIC OAL_INLINE oal_void hal_rx_get_info_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics)
{
    HAL_PUBLIC_HOOK_FUNC4(_rx_get_info_dscr, pul_rx_dscr, pst_rx_ctl, pst_rx_status, pst_rx_statistics);
}

OAL_STATIC OAL_INLINE oal_void hal_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_hal_vap, pst_hal_device, uc_vap_id, ppst_hal_vap);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_get_netbuffer_addr_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_get_netbuffer_addr_dscr, pul_rx_dscr, ppul_mac_hdr_addr);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_get_mac_hdr_addr_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr, oal_uint32 ** ppul_mac_hdr_address_dscr)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_get_mac_hdr_addr_dscr, pul_rx_dscr, ppul_mac_hdr_address_dscr);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_show_dscr_queue_info, pst_hal_device, en_rx_dscr_type);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_sync_invalid_dscr, pst_hal_device, pul_dscr, en_queue_num);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_free_dscr_list, pst_hal_device, en_queue_num, pul_rx_dscr);
}


OAL_STATIC OAL_INLINE oal_void hal_dump_rx_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC1(_dump_rx_dscr, pul_rx_dscr);
}

OAL_STATIC OAL_INLINE oal_void hal_dump_tx_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC1(_dump_tx_dscr, pul_tx_dscr);
}

/*****************************************************************************
 �� �� ��  : hal_reg_write
 ��������  : дSoC��MAC, PHY�Ĵ�����ֵ, �����ڵ���
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
OAL_STATIC OAL_INLINE oal_void  hal_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_reg_write, pst_hal_device, ul_addr, ul_val);
}

/*****************************************************************************
 �� �� ��  : hal_set_counter_clear
 ��������  : ͳ�Ƽ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��12��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_counter_clear, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_reg_write16
 ��������  : дSoC��MAC, PHY�Ĵ�����ֵ, �����ڵ���
 �������  : pst_hal_device:51��Ҫͨ��pst_hal_device��������Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reg_write16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 us_val)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    HAL_PUBLIC_HOOK_FUNC3(_reg_write16, pst_hal_device, ul_addr, us_val);
#endif
}

/*****************************************************************************
 �� �� ��  : hal_set_machw_rx_buff_addr
 ��������  : ����Ӳ�����������������׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_machw_rx_buff_addr, pst_hal_device, ul_rx_dscr, en_queue_num);
}


OAL_STATIC OAL_INLINE oal_uint32  hal_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num)
{
    return HAL_PUBLIC_HOOK_FUNC3(_set_machw_rx_buff_addr_sync, pst_hal_device, ul_rx_dscr, en_queue_num);
}


OAL_STATIC OAL_INLINE oal_void hal_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_dscr_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_add_dscr, pst_hal_device, en_queue_num, us_rx_dscr_num);
}

/*****************************************************************************
 �� �� ��  : hal_set_machw_tx_suspend
 ��������  : ����Ӳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_machw_tx_suspend, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_set_machw_tx_resume
 ��������  : �ָ�Ӳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_machw_tx_resume, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_reset_phy_machw
 ��������  : ��λMAC �� PHY
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                                        oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg)
{
    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_HW_BEGIN);

    HAL_PUBLIC_HOOK_FUNC5(_reset_phy_machw, pst_hal_device,en_type,sub_mod,uc_reset_phy_reg,uc_reset_mac_reg);

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_HW_END);

}

/*****************************************************************************
  hal��ʼ��/�˳�/��λ��ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_disable_machw_phy_and_pa
 ��������  : ֹͣPA��PHY�Ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_phy_and_pa, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_enable_machw_phy_and_pa
 ��������  : ʹ��PA��PHY�Ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device)
{
    /* ����λ�Ĵ�����������������Ϊ0���ڶ�������ΪALL */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
   hal_reset_phy_machw(pst_hal_device, HAL_RESET_HW_TYPE_MAC, 0, 0, 0);
#endif
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_phy_and_pa, pst_hal_device);
}


/*****************************************************************************
  hal MAC hardware��ʼ���ӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_initialize_machw
 ��������  : MAC hardware��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_machw(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_machw, pst_hal_device);
}

/*****************************************************************************
  Ƶ�Ρ������ŵ�����ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_set_freq_band
 ��������  : ���ù���Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_freq_band, pst_hal_device, en_band);
}

/*****************************************************************************
 �� �� ��  : hal_set_bandwidth_mode
 ��������  : ���ô���
 �������  : en_bandwidth: ����ö��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_bandwidth_mode, pst_hal_device, en_bandwidth);
}
/*****************************************************************************
 �� �� ��  : hal_set_primary_channel
 ��������  : ������20�ŵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_primary_channel, pst_hal_device, uc_channel_num, uc_band, uc_channel_idx, en_bandwidth);
}

#ifdef _PRE_WLAN_HW_TEST
/*****************************************************************************
 �� �� ��  : hal_set_phy_tx_scale
 ��������  : ����phy��tx scale
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��25��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_tx_scale, pst_hal_device, en_2g_11ac);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : hal_freq_adjust
 ��������  : ����Ƶƫ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��29��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_freq_adjust(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_pll_int, oal_uint16 us_pll_frac)
{
    HAL_PUBLIC_HOOK_FUNC3(_freq_adjust, pst_hal_device, us_pll_int, us_pll_frac);
}
#endif
/*****************************************************************************
 �� �� ��  : hal_set_rx_multi_ant
 ��������  : ���ý���ͨ��
 �������  : uc_rx_chain: ����ͨ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_multi_ant, pst_hal_device, uc_rx_chain);
}

/*****************************************************************************
 �� �� ��  : hal_add_machw_ba_lut_entry
 ��������  : ���һ�����BA LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size)
{
    HAL_PUBLIC_HOOK_FUNC6(_add_machw_ba_lut_entry, pst_hal_device,
                    uc_lut_index, puc_dst_addr, uc_tid, uc_seq_no, uc_win_size);
}

/*****************************************************************************
 �� �� ��  : hal_remove_machw_ba_lut_entry
 ��������  : ��BA LUT����ɾ��һ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_remove_machw_ba_lut_entry, pst_hal_device, uc_lut_index);
}

/*****************************************************************************
 �� �� ��  : hal_get_machw_ba_params
 ��������  : ��ȡBA LUT������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
														oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para)
{
    HAL_PUBLIC_HOOK_FUNC5(_get_machw_ba_params, pst_hal_device, uc_index,pst_addr_h,pst_addr_l,pst_ba_para);
}

/*****************************************************************************
 �� �� ��  : hal_restore_machw_ba_params
 ��������  : �ָ�BA LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                                oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para)
{
    HAL_PUBLIC_HOOK_FUNC5(_restore_machw_ba_params, pst_hal_device, uc_index,ul_addr_h,ul_addr_l,ul_ba_para);
}

/*****************************************************************************
          RA LUT������ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_machw_seq_num_index_update_per_tid
 ��������  : ����RA LUT index��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag)
{
    HAL_PUBLIC_HOOK_FUNC3(_machw_seq_num_index_update_per_tid, pst_hal_device, uc_lut_index, uc_qos_flag);
}

/*****************************************************************************
 �� �� ��  : hal_set_tx_sequence_num
 ��������  : ����TX SEQUENCE NUM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_tx_sequence_num, pst_hal_device,uc_lut_index,uc_tid,uc_qos_flag, ul_val_write);
}

/*****************************************************************************
 �� �� ��  : hal_get_tx_sequence_num
 ��������  : ����TX SEQUENCE NUM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read )
{
    HAL_PUBLIC_HOOK_FUNC5(_get_tx_sequence_num, pst_hal_device, uc_lut_index,uc_tid,uc_qos_flag,pst_val_read);
}

/*****************************************************************************
 �� �� ��  : hal_reset_init
 ��������  : ��λ��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_init(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_reset_init, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_reset_destroy
 ��������  : ��λ��Դ�ͷŽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_destroy(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_reset_destroy, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_reset_reg_restore
 ��������  : ��λ�Ĵ����ָ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_reset_reg_restore, pst_hal_device,en_type);
}

OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_reset_reg_save, pst_hal_device,en_type);
}


/*****************************************************************************
 �� �� ��  : hal_disable_machw_ack_trans
 ��������  : ����Ӳ�����յ�����֡ʱ����ACK
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_ack_trans, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_disable_machw_ack_trans
 ��������  : ����Ӳ�����յ�����֡ʱ��ACK
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_ack_trans, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_disable_machw_cts_trans
 ��������  : ����Ӳ�����յ�RTSʱ����CTS
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
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_cts_trans, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_enable_machw_cts_trans
 ��������  : ����Ӳ�����յ�RTSʱ��CTS
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
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_cts_trans, pst_hal_device);
}


/*****************************************************************************
  PHY��ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_initialize_phy
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_phy(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_phy, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_radar_config_reg
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain)
{
    HAL_PUBLIC_HOOK_FUNC2(_radar_config_reg, pst_hal_device, en_dfs_domain);
}

/*****************************************************************************
  RF��ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_initialize_rf_sys
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��10��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_rf_sys, pst_hal_device);
}

OAL_STATIC OAL_INLINE oal_void  hal_psm_rf_sleep(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg)
{
    HAL_PUBLIC_HOOK_FUNC2(_psm_rf_sleep, pst_hal_device, uc_restore_reg);
}

OAL_STATIC OAL_INLINE oal_void  hal_psm_rf_awake(hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg)
{
    HAL_PUBLIC_HOOK_FUNC2(_psm_rf_awake, pst_hal_device,uc_restore_reg);
}




#ifdef _PRE_WLAN_REALTIME_CALI

OAL_STATIC OAL_INLINE oal_void hal_rf_cali_realtime(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_freq,
                                                           oal_uint8 uc_chn_idx, oal_uint8 uc_bandwidth, oal_uint8 uc_protocol)
{
     HAL_PUBLIC_HOOK_FUNC5(_rf_cali_realtime, pst_hal_device, uc_freq, uc_chn_idx, uc_bandwidth, uc_protocol);
}
#endif

/*****************************************************************************
  SoC��ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_initialize_soc
 ��������  : SoC�ϵ��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_soc(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_soc, pst_hal_device);
}

/*****************************************************************************
  �ж���ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_get_mac_int_status
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_mac_int_status, pst_hal_device, pul_status);
}

/*****************************************************************************
 �� �� ��  : hal_clear_mac_int_status
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_clear_mac_int_status, pst_hal_device, ul_status);
}

/*****************************************************************************
 �� �� ��  : hal_get_mac_error_int_status
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_mac_error_int_status, pst_hal_device, pst_state);
}

/*****************************************************************************
 �� �� ��  : hal_clear_mac_error_int_status
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_clear_mac_error_int_status, pst_hal_device, pst_status);
}


/* ERROR IRQ�жϼĴ�����ز��� */
OAL_STATIC OAL_INLINE oal_void  hal_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_mac_error_init_status, pst_hal_device, pst_status);
}

/* mac�жϼĴ�����ز��� */
OAL_STATIC OAL_INLINE oal_void  hal_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_mac_init_status, pst_hal_device, ul_status);
}

OAL_STATIC OAL_INLINE oal_void  hal_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_show_irq_info, pst_hal_device, uc_param);
}

OAL_STATIC OAL_INLINE oal_void  hal_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dump_all_rx_dscr, pst_hal_device);
}

OAL_STATIC OAL_INLINE oal_void  hal_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_clear_irq_stat, pst_hal_device);
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
typedef enum
{
  HAL_DPD_CALI_START        = 0,
  HAL_DPD_CALI_STATUS       = 1,
  HAL_DPD_CALI_DATA_READ   = 2,
  HAL_DPD_CALI_DATA_WRITE  = 3,

}hal_dpd_cali_enum;


#define HI1102_DMAC_DPD_CALI_LUT_LENGTH 128
/*
 * DPD Calibration function
 */
OAL_STATIC OAL_INLINE oal_void hal_dpd_cali_func(oal_uint8 en_functype, oal_uint32* pstatus, oal_uint32* pdpd_cal_data_read, oal_uint32* pdpd_cal_data_write)
{
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
  HAL_PUBLIC_HOOK_FUNC4(_dpd_cali_func, en_functype, pstatus, pdpd_cal_data_read, pdpd_cal_data_write);
#endif
}
#endif


OAL_STATIC OAL_INLINE oal_void hal_cali_send_func(oal_uint8* puc_cal_data_write)
{
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
  HAL_PUBLIC_HOOK_FUNC1(_cali_send_func, puc_cal_data_write);
#endif
}


/*
����halά����vap id����ȡhal vap
*/
OAL_STATIC OAL_INLINE oal_void hal_get_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC4(_get_vap, pst_hal_device, vap_mode, vap_id, ppst_hal_vap);
}

/*
����vapģʽ��hal����vap�ṹ�������vap id
*/
OAL_STATIC OAL_INLINE oal_void hal_add_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC4(_add_vap, pst_hal_device, vap_mode, uc_mac_vap_id, ppst_hal_vap);
}

/*
����vapģʽ��halɾ��vap�ṹ�������vap id
*/
OAL_STATIC OAL_INLINE oal_void hal_del_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id)
{
    HAL_PUBLIC_HOOK_FUNC3(_del_vap, pst_hal_device, vap_mode, vap_id);
}

OAL_STATIC OAL_INLINE oal_void hal_set_proxysta_enable(hal_to_dmac_device_stru * pst_hal_device, oal_int32 l_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_proxysta_enable, pst_hal_device, l_enable);
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
OAL_STATIC OAL_INLINE oal_void hal_set_proxysta_vap_addr(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 vap_id, oal_uint8 *puc_mac_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_proxysta_vap_addr, pst_hal_device, vap_id, puc_mac_addr);
}
#endif

OAL_STATIC OAL_INLINE oal_void  hal_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol)
{
    HAL_PUBLIC_HOOK_FUNC2(_config_eifs_time, pst_hal_device, en_protocol);
}

/*****************************************************************************
 �� �� ��  : hal_register_alg_isr_hook
 ��������  : ע���㷨�ж��ϰ벿���Ӻ���
 �������  : hal_to_dmac_device_stru    *pst_hal_device
             hal_isr_type_enum_uint8     en_isr_type
             hal_alg_noify_enum_uint8    en_alg_notify
             _alg_isr_func          p_func
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_register_alg_isr_hook(hal_to_dmac_device_stru    *pst_hal_device,
                                                          hal_isr_type_enum_uint8     en_isr_type,
                                                          hal_alg_noify_enum_uint8    en_alg_notify,
                                                          p_hal_alg_isr_func          p_func)

{
    HAL_PUBLIC_HOOK_FUNC4(_register_alg_isr_hook, pst_hal_device, en_isr_type, en_alg_notify, p_func);
}
/*****************************************************************************
 �� �� ��  : hal_unregister_alg_isr_hook
 ��������  : ע���㷨�ж��ϰ벿���Ӻ���
 �������  : hal_to_dmac_device_stru    *pst_hal_device
             hal_isr_type_enum_uint8     en_isr_type
             hal_alg_noify_enum_uint8    en_alg_notify
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_unregister_alg_isr_hook(hal_to_dmac_device_stru    *pst_hal_device,
                                                            hal_isr_type_enum_uint8     en_isr_type,
                                                            hal_alg_noify_enum_uint8    en_alg_notify)
{
    HAL_PUBLIC_HOOK_FUNC3(_unregister_alg_isr_hook,pst_hal_device, en_isr_type, en_alg_notify);
}

/*****************************************************************************
 �� �� ��  : hal_one_packet_start
 ��������  : ����FCS
 �������  : struct tag_hal_to_dmac_device_stru *pst_hal_device
             hal_one_packet_cfg_stru *pst_cfg
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_one_packet_start, pst_hal_device, pst_cfg);
}
/*****************************************************************************
 �� �� ��  : hal_one_packet_stop
 ��������  : ֹͣFCS
 �������  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_one_packet_stop, pst_hal_device);
}
/*****************************************************************************
 �� �� ��  : hal_one_packet_get_status
 ��������  : ��ȡFCS״̬
 �������  : struct tag_hal_to_dmac_device_stru *pst_hal_device
             hal_one_packet_status_stru *pst_status
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_one_packet_get_status, pst_hal_device, pst_status);
}

/*****************************************************************************
 �� �� ��  : hal_reset_nav_timer
 ��������  : ����NAV������
 �������  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_reset_nav_timer, pst_hal_device);
}


/*****************************************************************************
 �� �� ��  : hal_clear_hw_fifo
 ��������  : ���Ӳ�����ͻ�����
 �������  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_clear_hw_fifo, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_mask_interrupt
 ��������  : ����ָ���ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_mask_interrupt, pst_hal_device, ul_offset);
}
/*****************************************************************************
 �� �� ��  : hal_unmask_interrupt
 ��������  : �ָ�ָ���ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_interrupt, pst_hal_device, ul_offset);
}

/*****************************************************************************
  �Ĵ�������ӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_reg_info
 ��������  : ��ȡSoC, MAC, PHY�Ĵ�����ֵ, �����ڵ���
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
OAL_STATIC OAL_INLINE oal_void  hal_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_reg_info, pst_hal_device, ul_addr, pul_val);
}

OAL_STATIC OAL_INLINE oal_void  hal_reg_info16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 *pus_val)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    HAL_PUBLIC_HOOK_FUNC3(_reg_info16, pst_hal_device, ul_addr, pus_val);
#endif
}
OAL_STATIC OAL_INLINE oal_void hal_get_all_tx_q_status(hal_to_dmac_device_stru *pst_hal_device,oal_uint32 *pul_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_all_tx_q_status, pst_hal_device, pul_val);
}

/*****************************************************************************
 �� �� ��  : hal_get_ampdu_bytes
 ��������  : ��ȡMAC�Ĵ��� ampdu���ͽ����ֽ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��12��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_ampdu_bytes(hal_to_dmac_device_stru *pst_hal_device,oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_ampdu_bytes, pst_hal_device, pul_tx_bytes, pul_rx_bytes);
}
/*****************************************************************************
 �� �� ��  : hal_get_ampdu_bytes
 ��������  : ��ȡMAC�Ĵ��� �������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��12��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_rx_err_count(hal_to_dmac_device_stru *pst_hal_device,
                                                          oal_uint32 *pul_cnt1,
                                                          oal_uint32 *pul_cnt2,
                                                          oal_uint32 *pul_cnt3,
                                                          oal_uint32 *pul_cnt4,
                                                          oal_uint32 *pul_cnt5,
                                                          oal_uint32 *pul_cnt6)
{
    HAL_PUBLIC_HOOK_FUNC7(_get_rx_err_count, pst_hal_device, pul_cnt1, pul_cnt2, pul_cnt3, pul_cnt4, pul_cnt5, pul_cnt6);
}

/*****************************************************************************
 �� �� ��  : hal_show_fsm_info
 ��������  : ���ڵ�������ʾfsm״̬��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��31��
    ��    ��   : caohb
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_show_fsm_info, pst_hal_device);
}


/*****************************************************************************
 �� �� ��  : hal_mac_error_msg_report
 ��������  : mac�����ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_mac_error_msg_report, pst_hal_device, en_error_type);
}

/*****************************************************************************
 �� �� ��  : hal_show_fsm_info
 ��������  : ���ڵ�������ʾfsm״̬��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��31��
    ��    ��   : caohb
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_en_soc_intr, pst_hal_device);
}

OAL_STATIC  OAL_INLINE oal_void hal_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_beacon_filter, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device)
{
   HAL_PUBLIC_HOOK_FUNC1(_disable_beacon_filter, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_non_frame_filter, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_disable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_non_frame_filter, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_monitor_mode, pst_hal_device);
}

OAL_STATIC  OAL_INLINE oal_void hal_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_monitor_mode, pst_hal_device);
}
#if (_PRE_WLAN_FEATURE_PMF  != _PRE_PMF_NOT_SUPPORT)


OAL_STATIC  OAL_INLINE oal_void  hal_set_pmf_crypto(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_crypto)
{
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    HAL_PUBLIC_HOOK_FUNC2(_set_pmf_crypto, pst_hal_vap, en_crypto);
#else
    return;
#endif
}
#endif /* #if(_PRE_WLAN_FEATURE_PMF  != _PRE_PMF_NOT_SUPPORT)  */
/*****************************************************************************
 �� �� ��  : hal_ce_add_key
 ��������  : ����Կд��Ӳ���Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��24��
    ��    ��   : louyueyun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_ce_add_key, pst_hal_device,pst_security_key,puc_addr);
}


OAL_STATIC  OAL_INLINE oal_void  hal_disable_ce(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_ce, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_ce_del_key
 ��������  : ����Կд��Ӳ���Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��29��
    ��    ��   : louyueyun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key)
{
    HAL_PUBLIC_HOOK_FUNC2(_ce_del_key, pst_hal_device,pst_security_key);
}


OAL_STATIC  OAL_INLINE oal_void hal_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_ce_add_peer_macaddr, pst_hal_device,uc_lut_idx,puc_addr);
}

OAL_STATIC  OAL_INLINE oal_void hal_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx)
{
    HAL_PUBLIC_HOOK_FUNC2(_ce_del_peer_macaddr, pst_hal_device,uc_lut_idx);
}

/*****************************************************************************
 �� �� ��  : hal_set_rx_pn
 ��������  : ��pn noд�����RX PN LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 �� �� ��  : hal_get_rx_pn
 ��������  : ��RX pn LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 �� �� ��  : hal_set_tx_pn
 ��������  : ��pn noд�����Tx PN LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_tx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 �� �� ��  : hal_get_rx_pn
 ��������  : ��tx pn LUT��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_tx_pn, pst_hal_device, pst_pn_lut_cfg);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_rate_80211g_table(hal_to_dmac_device_stru *pst_hal_device, oal_void **pst_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_rate_80211g_table, pst_rate);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_rate_80211g_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pst_data_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_rate_80211g_num, pst_data_num);
}

/*****************************************************************************
 �� �� ��  : hal_get_hw_addr
 ��������  : ��ȡӲ��mac��ַ������eeprom��flash
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_hw_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_hw_addr, puc_addr);
}

/*****************************************************************************
 �� �� ��  : hal_enable_ch_statics
 ��������  : ����MAC���ŵ�ͳ��ʹ�ܼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��14��
    ��    ��   : wangshanbo
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_ch_statics, pst_hal_device, uc_enable);
}


/*****************************************************************************
 �� �� ��  : hal_set_ch_statics_period
 ��������  : ����MAC���ŵ�ͳ��ʱ�䳤�ȼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��14��
    ��    ��   : wangshanbo
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ch_statics_period, pst_hal_device, ul_period);
}

/*****************************************************************************
 �� �� ��  : hal_set_ch_measurement_period
 ��������  : ����MAC���ŵ�ͳ��ʱ�䳤�ȼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��14��
    ��    ��   : wangshanbo
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ch_measurement_period, pst_hal_device, uc_period);
}


OAL_STATIC OAL_INLINE oal_void hal_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_ch_statics_result, pst_hal_device, pst_ch_statics);
}


OAL_STATIC OAL_INLINE oal_void hal_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_ch_measurement_result, pst_hal_device, pst_ch_statics);
}


OAL_STATIC OAL_INLINE oal_void hal_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_radar_det, pst_hal_device, uc_enable);
}


OAL_STATIC OAL_INLINE oal_void hal_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_radar_det_result, pst_hal_device, pst_radar_info);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rts_rate_params, pst_hal_device, pst_hal_rts_tx_param);
}

/*****************************************************************************
 �� �� ��  : hal_set_rts_rate_selection_mode
 ��������  : ����rts����ѡ��ģʽ
             0: RTS���� = PROT_DATARATE������
             1: RTS���� = Ӳ������TX�������������ֵ
             2: RTS���� = min(PROT_DATARATE,Ӳ������TX�������������ֵ)
             3: RTS���� = max(PROT_DATARATE,Ӳ������TX�������������ֵ)
 �������  : pst_hal_device, uc_rts_rate_select_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode)

{
    HAL_PUBLIC_HOOK_FUNC2(_set_rts_rate_selection_mode, pst_hal_device, uc_rts_rate_select_mode);
}

#ifdef _PRE_WLAN_FEATURE_TPC

//OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num)
//{
    //HAL_PUBLIC_HOOK_FUNC3(_set_bcn_phy_tx_mode, pst_hal_device, uc_band, uc_channel_num);
//}


OAL_STATIC  OAL_INLINE oal_void  hal_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rf_temp, pst_hal_device, puc_cur_temp);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_tpc_init_rate_dac_lpf_table, pauc_rate_pow_table_2G, pauc_rate_pow_table_5G,
                            pauc_mode_len);
}


OAL_STATIC  OAL_INLINE oal_void  hal_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code,
        oal_int8   *pac_tpc_level_table, oal_uint8 uc_tpc_level_num,
        oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table,oal_int16 *pas_other_gain_table)
{
    HAL_PUBLIC_HOOK_FUNC6(_set_dac_lpc_pa_upc_level, uc_dac_lpf_code, pac_tpc_level_table,
                        uc_tpc_level_num, pauc_dac_lpf_pa_code_table,pas_upc_gain_table,pas_other_gain_table);
}
#ifdef _PRE_WLAN_REALTIME_CALI

OAL_STATIC  OAL_INLINE oal_void  hal_get_tpc_cali_upc_gain_in_rf_list(oal_int8* pac_upc_gain_in_rf_list)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_tpc_cali_upc_gain_in_rf_list, pac_upc_gain_in_rf_list);
}
#endif


OAL_STATIC  OAL_INLINE oal_void  hal_get_bcn_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint8 *puc_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_bcn_rate, pst_hal_device, uc_vap_id, puc_data_rate);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_bcn_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_tpc_code, oal_uint8 uc_vap_id)

{
    HAL_PUBLIC_HOOK_FUNC3(_set_bcn_phy_tx_mode, pst_hal_device, uc_tpc_code, uc_vap_id);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_spec_frm_rate, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_band, oal_uint8 uc_subband_idx)

{
    HAL_PUBLIC_HOOK_FUNC3(_set_spec_frm_phy_tx_mode, pst_hal_device, uc_band, uc_subband_idx);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param)

{
    HAL_PUBLIC_HOOK_FUNC2(_set_tpc_ctrl_reg_param, pst_hal_device, ul_tpc_ctrl_param);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2)

{
    HAL_PUBLIC_HOOK_FUNC5(_set_tpc_delay_reg_param, pst_hal_device, ul_phy_tx_up_down_time_reg,
                        ul_phy_rx_up_down_time_reg, ul_rf_reg_wr_delay1, ul_rf_reg_wr_delay2);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2)

{
    HAL_PUBLIC_HOOK_FUNC5(_get_tpc_delay_reg_param, pst_hal_device, pul_phy_tx_up_down_time_reg,
                        pul_phy_rx_up_down_time_reg, pul_rf_reg_wr_delay1, pul_rf_reg_wr_delay2);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
  oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
  oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx)

{
    HAL_PUBLIC_HOOK_FUNC7(_get_tpc_rf_reg_param, pst_hal_device, pus_dac_val, pus_pa_val,pus_lpf_val,paus_2g_upc_val
        ,paus_5g_upc_val, uc_chain_idx);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
  oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
  oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx)

{
    HAL_PUBLIC_HOOK_FUNC7(_set_tpc_rf_reg_param, pst_hal_device, us_dac_val, us_pa_val,us_lpf_val,paus_2g_upc_val
        ,paus_5g_upc_val, uc_chain_idx);
}


OAL_STATIC  OAL_INLINE oal_void  hal_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_tpc_phy_reg_param, pst_hal_device);
}

/*****************************************************************************
 �� �� ��  : hal_get_2g_subband_index
 ��������  : ��ȡ2g�ŵ���Ӧ��subband
 �������  : uc_channel_num
 �������  : puc_subband_idx
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : lm
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_subband_index, en_band, uc_channel_num, puc_subband_idx);
}

/*****************************************************************************
 �� �� ��  : hal_set_dpd_by_power
 ��������  : �������ã���Բ�ͬ�����ʡ���ͬ�Ĺ��ʽ���dpd����
 �������  : pst_pow_params
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : t00300755
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate, oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx)
{

    HAL_PUBLIC_HOOK_FUNC4(_set_dpd_by_power, pst_rate, uc_power_level, ul_dpd_configure, ul_rate_idx);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx)
{

    HAL_PUBLIC_HOOK_FUNC3(_set_upc_data, pst_hal_device, uc_band, uc_subband_idx);
}

#endif

/*****************************************************************************
 �� �� ��  : hal_irq_affinity_init
 ��������  : �жϺͺ˰󶨳�ʼ��
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��6��
    ��    ��   : zhoukaichun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_irq_affinity_init(hal_to_dmac_device_stru * pst_device, oal_uint32 ul_core_id)
{
    HAL_PUBLIC_HOOK_FUNC2(_irq_affinity_init, pst_device, ul_core_id);
}

#ifdef _PRE_WLAN_FEATURE_TXBF

OAL_STATIC  OAL_INLINE oal_void hal_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_legacy_matrix_buf_pointer, pst_hal_device, ul_matrix);
}

OAL_STATIC  OAL_INLINE oal_void hal_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_legacy_matrix_buf_pointer, pst_hal_device, pul_matrix);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_membership_status_63_32, pst_hal_device, ul_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_membership_status_31_0, pst_hal_device, ul_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_63_48, pst_hal_device, ul_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_47_32, pst_hal_device, ul_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_31_16, pst_hal_device, ul_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_15_0, pst_hal_device, ul_value);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_vht_report_rate, pst_hal_device, ul_rate);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_vht_report_phy_mode, pst_hal_device, ul_phy_mode);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_rate, pst_hal_device, ul_rate);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_phy_mode, pst_hal_device, ul_phy_mode);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_max_time, pst_hal_device, uc_ndp_time);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndpa_duration, pst_hal_device, ul_ndpa_duration);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_group_id)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_group_id, pst_hal_device, ul_group_id);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_partial_aid, pst_hal_device, us_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_legacy_bf_en, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_txbf_legacy_en, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_pilot_bf_en, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_num, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_step, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_pointer, pst_hal_device, ul_reg_value);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_h_matrix_timeout, pst_hal_device, ul_reg_value);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_mu_aid_matrix_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint16 us_aid, oal_uint8  *p_matrix)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_mu_aid_matrix_info, pst_hal_device, uc_vap_id, us_aid, p_matrix);
}


OAL_STATIC  OAL_INLINE oal_void hal_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_delete_txbf_lut_info, pst_hal_device, uc_lut_index);
}


OAL_STATIC OAL_INLINE oal_void hal_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 auc_mac_addr[], oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_peer_lut_info, pst_hal_device, auc_mac_addr, uc_lut_index);
}

OAL_STATIC  OAL_INLINE oal_void hal_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_txbf_lut_info, pst_hal_device, uc_lut_index, ul_reg_value);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_txbf_lut_info, pst_hal_device, uc_lut_index, pst_reg_value);
}
#endif

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF

OAL_STATIC  OAL_INLINE oal_void hal_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_weak_intf_rssi_th, pst_hal_device, l_reg_val);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_agc_unlock_min_th, pst_hal_device, l_tx_reg_val, l_rx_reg_val);
}

/*****************************************************************************
 �� �� ��  : hal_set_nav_max_duration
 ��������  : ������nav�������ý���duration���ֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint16 us_obss_dur)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_nav_max_duration, pst_hal_device, us_bss_dur, us_obss_dur);
}
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT

OAL_STATIC  OAL_INLINE oal_void hal_set_counter1_clear(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_counter1_clear, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_txrx_frame_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_txrx_frame_time, pst_hal_device, ul_reg_val);
}

/*****************************************************************************
�� �� ��  : hal_set_mac_clken
��������  : ����mac_tx/rx_clken�ſ�ģʽ
�������  : pst_hal_device:  deviceָ��;
            en_wctrl_enable: mac tx/rxʱ���ſ�ģʽ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ     :
1.��    ��   : 2015��8��17��
  ��    ��   : wanran
  �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_mac_clken, pst_hal_device, en_wctrl_enable);
}
#endif

/*****************************************************************************
 �� �� ��  : hal_set_soc_lpm
 ��������  : ����SOC���ܿ����͹ر�
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_soc_lpm, pst_hal_device,en_type, uc_on_off,uc_pcie_idle);
}

/*****************************************************************************
 �� �� ��  : hal_set_psm_status
 ��������  : ����PSM�Ĵ����н���״̬λ
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_status, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 �� �� ��  : hal_set_psm_wakeup_mode
 ��������  : ����PSM�Ĵ����л��ѷ�ʽ
 �������  : uc_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_psm_dtim_period, pst_hal_vap, uc_dtim_period, uc_listen_intvl_to_dtim_times, en_receive_dtim);
}


/*****************************************************************************
 �� �� ��  : hal_set_psm_wakeup_mode
 ��������  : ����PSM�Ĵ����л��ѷ�ʽ
 �������  : uc_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_wakeup_mode, pst_hal_device, uc_mode);
}

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
/*****************************************************************************
 �� �� ��  : hal_set_smps_mode
 ��������  : ����SMPS��ģʽ 0:disable,1:static,2:dynamic
 �������  : uc_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_smps_mode, pst_hal_device, uc_mode);
}

/*****************************************************************************
 �� �� ��  : hal_get_smps_mode
 ��������  : ����SMPS��ģʽ 0:disable,1:static,2:dynamic
 �������  : uc_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_smps_mode, pst_hal_device, pst_reg_value);
}

#endif

#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
/*****************************************************************************
 �� �� ��  : hal_set_txop_ps_enable
 ��������  : ����TXOP PS�Ĵ�����ʹ��λ
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_enable, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 �� �� ��  : hal_set_txop_ps_condition1
 ��������  : ����PSM�Ĵ�����condition1״̬λ
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_condition1, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 �� �� ��  : hal_set_txop_ps_condition2
 ��������  : ����PSM�Ĵ�����condition2״̬λ
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_condition2, pst_hal_device, uc_on_off);
}


OAL_STATIC  OAL_INLINE oal_void  hal_set_txop_ps_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_partial_aid)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_partial_aid, pst_hal_device, us_partial_aid);
}

#endif
/*****************************************************************************
 �� �� ��  : hal_set_wow_en_para
 ��������  : ����wow
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_wow_en, pst_hal_device, ul_set_bitmap, pst_para);
}

/*****************************************************************************
 �� �� ��  : hal_set_wow_en_para
 ��������  : ����wow
 �������  : uc_on_off
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_lpm_state, pst_hal_device,uc_state_from,uc_state_to, pst_para);
}


OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_edca, pst_hal_device);
}


OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_edca, pst_hal_device);
}



OAL_STATIC  OAL_INLINE oal_void hal_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_tx_abort_en, pst_hal_device, uc_abort_en);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_coex_ctrl, pst_hal_device, ul_mac_ctrl, ul_rf_ctrl);
}


OAL_STATIC  OAL_INLINE oal_void hal_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num)
{
    HAL_PUBLIC_HOOK_FUNC4(_get_hw_version, pst_hal_device, pul_hw_vsn, pul_hw_vsn_data, pul_hw_vsn_num);
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : hal_get_all_reg_value
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��1��
    ��    ��   : wowoo
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_all_reg_value, pst_hal_device);
}
#endif


OAL_STATIC  OAL_INLINE oal_void hal_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_tx_dscr_field, pst_hal_device, ul_data, en_sect);
}


OAL_STATIC  OAL_INLINE oal_void hal_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_rf_test_disable_al_tx, pst_hal_device);
}


OAL_STATIC  OAL_INLINE oal_void hal_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC2(_rf_test_enable_al_tx, pst_hal_device, pst_tx_dscr);
}

#ifdef _PRE_WLAN_PHY_PLL_DIV


OAL_STATIC  OAL_INLINE oal_void hal_rf_set_freq_skew(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[])
{
    HAL_PUBLIC_HOOK_FUNC3(_rf_set_freq_skew, us_idx, us_chn, as_corr_data);
}
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : hal_rf_adjust_ppm
 ��������  : ����ppm
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : pengdunmeng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_rf_adjust_ppm(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_ppm, wlan_channel_bandwidth_enum_uint8  en_bandwidth, oal_uint8 uc_clock)
{
    HAL_PUBLIC_HOOK_FUNC4(_rf_adjust_ppm, pst_hal_device, c_ppm, en_bandwidth, uc_clock);
}
#endif

/*****************************************************************************
 �� �� ��  : hal_set_daq_mac_reg
 ��������  : �������ݲɼ�ʱ��MAC�Ĵ���
 �������  : pst_hal_device--deviceָ��, pul_addr --��ַ, us_unit_len--��Ԫ����, us_unit_num--��Ԫ����, us_depth--���ݱ������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_daq_mac_reg, pst_hal_device, pul_addr, us_unit_len, us_unit_num, us_depth);
}

/*****************************************************************************
 �� �� ��  : hal_set_daq_phy_reg
 ��������  : �������ݲɼ�ʱ��PHY�Ĵ���
 �������  : pst_hal_device--deviceָ��, ul_reg_value --����ֵ,
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_daq_phy_reg, pst_hal_device, ul_reg_value);
}

/*****************************************************************************
 �� �� ��  : hal_set_daq_en
 ��������  : ʹ�ܻ�ȥʹ�����ݲɼ�
 �������  : pst_hal_device--deviceָ��, uc_reg_value --����ֵ,
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_daq_en, pst_hal_device, uc_reg_value);
}

/*****************************************************************************
 �� �� ��  : hal_get_daq_status
 ��������  : ʹ�ܻ�ȥʹ�����ݲɼ�
 �������  : pst_hal_device--deviceָ��, pul_reg_value --�ض���״ֵ̬,
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_daq_status, pst_hal_device, pul_reg_value);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_beacon_timeout_val, pst_hal_device, us_value);
}

#ifdef _PRE_WLAN_HW_TEST

OAL_STATIC OAL_INLINE oal_void hal_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                                 oal_uint8 en_band,
                                                 oal_uint8 en_bandwidth,
                                                 oal_uint8 en_protocol_mode,
                                                 oal_uint8 en_rate)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_dac_lpf_gain, pst_hal_device, en_band, en_bandwidth, en_protocol_mode, en_rate);
}
#endif

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)

OAL_STATIC OAL_INLINE oal_void hal_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                                 oal_uint8 en_band,
                                                 oal_uint8 en_bandwidth,
                                                 oal_uint8 en_protocol_mode,
                                                 oal_uint8 en_rate)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_dac_lpf_gain, pst_hal_device, en_band, en_bandwidth, en_protocol_mode, en_rate);
}
#endif
/*****************************************************************************
 �� �� ��  : hal_set_rx_filter
 ��������  : ����SMPS��ģʽ 0:disable,1:static,2:dynamic
 �������  : uc_mode
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_filter, pst_hal_device, ul_rx_filter_val);
}

/*****************************************************************************
 �� �� ��  : hal_get_rx_filter
 ��������  : ��ȡ֡���˼Ĵ���ֵ
 �������  : hal_to_dmac_device_stru *pst_hal_device

 �������  : oal_uint32* pst_reg_value
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rx_filter, pst_hal_device, pst_reg_value);
}

#define HAL_VAP_LEVEL_FUNC
/*****************************************************************************
 �� �� ��  : hal_vap_tsf_get_32bit
 ��������  : ��ȡtsf��32λֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��25��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_tsf_get_32bit, pst_hal_vap, pul_tsf_lo);
}
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_tsf_set_32bit, pst_hal_vap, ul_tsf_lo);
}

/*****************************************************************************
 �� �� ��  : hal_vap_tsf_get_64bit
 ��������  : ��ȡ����tsf 64λֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��25��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_tsf_get_64bit, pst_hal_vap, pul_tsf_hi, pul_tsf_lo);
}
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_tsf_set_64bit, pst_hal_vap, ul_tsf_hi, ul_tsf_lo);
}

/*****************************************************************************
 �� �� ��  : hal_vap_send_beacon_pkt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_send_beacon_pkt(hal_to_dmac_vap_stru        *pst_hal_vap,
                                                        hal_beacon_tx_params_stru   *pst_params)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_send_beacon_pkt, pst_hal_vap, pst_params);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_beacon_rate
 ��������  : ����beacon��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_beacon_rate(hal_to_dmac_vap_stru        *pst_hal_vap,
                                                                 oal_uint32 ul_beacon_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_beacon_rate, pst_hal_vap, ul_beacon_rate);
}

/*****************************************************************************
 �� �� ��  : hal_vap_beacon_suspend
 ��������  : ����beacon֡����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_beacon_suspend, pst_hal_vap);
}

/*****************************************************************************
 �� �� ��  : hal_vap_beacon_resume
 ��������  : �ָ�beacon֡����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_beacon_resume, pst_hal_vap);
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : hal_get_beacon_miss_status
 ��������  : beaconmissʱ��ӡ��ؼĴ�����ά��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : daihu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_beacon_miss_status(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_beacon_miss_status, pst_hal_device);
}
#endif

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_prot_params
 ��������  : ����RTS phy tx mode��data rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��8��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_prot_params, pst_hal_vap, pst_phy_tx_mode, pst_data_rate);
}



/*****************************************************************************
  10.2 ��Ӧһ��Ӳ��MAC VAP�ľ�̬��������
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_macaddr, pst_hal_vap, puc_mac_addr);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_opmode
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_opmode, pst_hal_vap, en_vap_mode);
}




/*****************************************************************************
 �� �� ��  : hal_vap_clr_opmode
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_clr_opmode, pst_hal_vap, en_vap_mode);
}


/*****************************************************************************
  hal vap EDCA����������ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_aifsn_all_ac
 ��������  : ��������AC���ٲ�֡���(arbitration inter-frame space, AIFS)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo)
{
    HAL_PUBLIC_HOOK_FUNC5(_vap_set_machw_aifsn_all_ac, pst_hal_vap, uc_bk, uc_be, uc_vi, uc_vo);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_aifsn_ac
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                                           wlan_wme_ac_type_enum_uint8   en_ac,
                                                           oal_uint8                     uc_aifs)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_aifsn_ac, pst_hal_vap, en_ac, uc_aifs);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_edca_machw_cw
 ��������  : ����BE��BK��VI��VO�������ڵ�������(CWmin, CWmax)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ec_type)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_set_edca_machw_cw, pst_hal_vap, uc_cwmax, uc_cwmin, uc_ec_type);
}
/*****************************************************************************
 �� �� ��  : hal_vap_get_edca_machw_cw
 ��������  : ��ȡBE��BK��VI��VO�������ڵ�������(CWmin, CWmax)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ec_type)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_get_edca_machw_cw, pst_hal_vap, puc_cwmax, puc_cwmin, uc_ec_type);
}

#if 0
/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_cw_bk
 ��������  : ����BK�������ڵ�������(CWmin[BK], CWmax[BK])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_bk, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_cw_bk
 ��������  : ��ȡBK�������ڵ�������(CWmin[BK], CWmax[BK])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_bk, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_cw_be
 ��������  : ����BE�������ڵ�������(CWmin[BE], CWmax[BE])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_be, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_cw_be
 ��������  : ��ȡBE�������ڵ�������(CWmin[BE], CWmax[BE])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_be, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_cw_vi
 ��������  : ����VI�������ڵ�������(CWmin[VI], CWmax[VI])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_vi, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_cw_vi
 ��������  : ��ȡVI�������ڵ�������(CWmin[VI], CWmax[VI])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_vi, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_cw_vo
 ��������  : ����VO�������ڵ�������(CWmin[VO], CWmax[VO])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_vo, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_cw_vo
 ��������  : ��ȡVO�������ڵ�������(CWmin[VO], CWmax[VO])
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_vo, pst_hal_vap, puc_cwmax, puc_cwmin);
}
#endif

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_txop_limit_bkbe
 ��������  : ����BK��BE��TXOP����(��λ: ΢��)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_txop_limit_bkbe, pst_hal_vap, us_be, us_bk);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_txop_limit_bkbe
 ��������  : ��ȡBK��BE��TXOP����(��λ: ΢��)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_txop_limit_bkbe, pst_hal_vap, pus_be, pus_bk);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_txop_limit_vivo
 ��������  : ����VI��VO��TXOP����(��λ: ΢��)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_txop_limit_vivo, pst_hal_vap, us_vo, us_vi);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_txop_limit_vivo
 ��������  : ��ȡVI��VO��TXOP����(��λ: ΢��)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_txop_limit_vivo, pst_hal_vap, pus_vo, pus_vi);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_edca_bkbe_lifetime
 ��������  : ����BK��BE������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_edca_bkbe_lifetime, pst_hal_vap, us_be, us_bk);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_edca_bkbe_lifetime
 ��������  : ��ȡBK��BE������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_edca_bkbe_lifetime, pst_hal_vap, pus_be, pus_bk);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_edca_vivo_lifetime
 ��������  : ����VI��VO������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_edca_vivo_lifetime, pst_hal_vap, us_vo, us_vi);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_machw_edca_vivo_lifetime
 ��������  : ��ȡVI��VO������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_edca_vivo_lifetime, pst_hal_vap, pus_vo, pus_vi);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_prng_seed_val_all_ac
 ��������  : Ϊÿһ��AC�ֱ�����̽������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_set_machw_prng_seed_val_all_ac, pst_hal_vap);
}


/*****************************************************************************
  hal vap TSF����������ؽӿ�
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hal_vap_start_tsf
 ��������  : ʹ��TBTT
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_start_tsf, pst_hal_vap, en_dbac_enable);
}

/*****************************************************************************
 �� �� ��  : hal_vap_read_tbtt_timer
 ��������  : ��ȡTBTT������
 �������  : hal_to_dmac_vap_stru *pst_hal_vap
             oal_uint32 *pul_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_read_tbtt_timer, pst_hal_vap, pul_value);
}
/*****************************************************************************
 �� �� ��  : hal_vap_write_tbtt_timer
 ��������  : д��TBTT������
 �������  : hal_to_dmac_vap_stru *pst_hal_vap
             oal_uint32 ul_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_write_tbtt_timer, pst_hal_vap, ul_value);
}


/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_tsf_disable
 ��������  : ����vap������TBTT�ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_set_machw_tsf_disable, pst_hal_vap);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_machw_beacon_period
 ��������  : ����vap��Beacon Period
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_machw_beacon_period, pst_hal_vap, us_beacon_period);
}

/*****************************************************************************
 �� �� ��  : hal_vap_update_beacon_period
 ��������  : ��hal_vap_set_machw_beacon_period��������ֻ����Beacon���ڼĴ�����������tsf
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_update_beacon_period, pst_hal_vap, us_beacon_period);
}

/*****************************************************************************
 �� �� ��  : hal_set_psm_listen_interval
 ��������  : ����PSM�Ĵ�����listen_interval��ֵ
 �������  : us_interval
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_listen_interval, pst_hal_vap, us_interval);
}
/*****************************************************************************
 �� �� ��  : hal_set_psm_listen_interval_count
 ��������  : ����PSM�Ĵ�����listen_interval_count��ֵ
 �������  : us_interval
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_listen_interval_count, pst_hal_vap, us_interval_count);
}

/*****************************************************************************
 �� �� ��  : hal_set_psm_listen_interval
 ��������  : ����PSM�Ĵ�����listen_interval��ֵ
 �������  : us_offset
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_tbtt_offset, pst_hal_vap, us_offset);
}

/*****************************************************************************
 �� �� ��  : hal_set_psm_listen_interval
 ��������  : ����PSM�Ĵ�����listen_interval��ֵ
 �������  : us_offset
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_ext_tbtt_offset, pst_hal_vap, us_offset);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_beacon_period
 ��������  : ��ȡbeacon���ڼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_beacon_period, pst_hal_vap, ul_beacon_period);
}
/*****************************************************************************
 �� �� ��  : hal_vap_get_beacon_period
 ��������  : ��ȡbeacon���ڼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��11��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_tsf_ctrl, pst_hal_vap, ul_tsf_ctrl_val);
}

/*****************************************************************************
 �� �� ��  : hal_vap_get_beacon_period
 ��������  : ��ȡbeacon���ڼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_get_beacon_period, pst_hal_vap, pul_beacon_period);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_noa
 ��������  : ����NoA�Ĵ���
 �������  : pst_hal_vap: hal vap
             ul_start_tsf: start tsf
             ul_duration : absentʱ��, ��λus
             ul_interval : noa����, ��λus
             uc_count    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count)
{
    HAL_PUBLIC_HOOK_FUNC5(_vap_set_noa, pst_hal_vap, ul_start_tsf, ul_duration, ul_interval, uc_count);
}

/*****************************************************************************
 �� �� ��  : hal_sta_tsf_save
 ��������  : ����������ӦVAP������TSF
 �������  : pst_hal_vap: hal vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_sta_tsf_save(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_sta_tsf_save, pst_hal_vap);
}

/*****************************************************************************
 �� �� ��  : hal_sta_tsf_restore
 ��������  : ����ֹͣ��ӦVAP������TSF
 �������  : pst_hal_vap: hal vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_sta_tsf_restore(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_sta_tsf_restore, pst_hal_vap);
}

#ifdef _PRE_WLAN_FEATURE_P2P

OAL_STATIC OAL_INLINE oal_void  hal_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_ops, pst_hal_vap, en_ops_ctrl, uc_ct_window);
}

/*****************************************************************************
 �� �� ��  : hal_vap_set_p2p_absent_suspend
 ��������  : ����NoA�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��19��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_bool_enum_uint8     en_suspend_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_enable_p2p_absent_suspend, pst_hal_vap, en_suspend_enable);
}

#endif
/* beacon hal��ؽӿ� ԭ������ */
OAL_STATIC OAL_INLINE oal_void hal_tx_complete_update_rate(hal_tx_dscr_ctrl_one_param *pst_tx_dscr_param)
{
    oal_uint8       uc_retry;

    uc_retry = pst_tx_dscr_param->uc_long_retry + pst_tx_dscr_param->uc_short_retry;

    if (uc_retry <= pst_tx_dscr_param->ast_per_rate[0].rate_bit_stru.bit_tx_count) /* ����ʹ�õ�1������ */
    {
        pst_tx_dscr_param->uc_last_rate_rank = 0;
    }
    else
    {
        uc_retry -= pst_tx_dscr_param->ast_per_rate[0].rate_bit_stru.bit_tx_count;
        if(uc_retry <= pst_tx_dscr_param->ast_per_rate[1].rate_bit_stru.bit_tx_count) /* ����ʹ�õ�2������ */
        {
            pst_tx_dscr_param->uc_last_rate_rank = 1;
        }
        else
        {
            uc_retry -= pst_tx_dscr_param->ast_per_rate[1].rate_bit_stru.bit_tx_count;
            if(uc_retry <= pst_tx_dscr_param->ast_per_rate[2].rate_bit_stru.bit_tx_count)
            {
                pst_tx_dscr_param->uc_last_rate_rank = 2;
            }
            else
            {
                uc_retry -= pst_tx_dscr_param->ast_per_rate[2].rate_bit_stru.bit_tx_count;
                pst_tx_dscr_param->uc_last_rate_rank = 3;
            }
        }
    }

    pst_tx_dscr_param->ast_per_rate[pst_tx_dscr_param->uc_last_rate_rank].rate_bit_stru.bit_tx_count = uc_retry;

}
OAL_STATIC OAL_INLINE oal_void  hal_get_random_byte(oal_uint8 *puc_byte)
{
    /* wep���� */
    *puc_byte = oal_get_random();
}
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_bssid, pst_hal_vap, puc_byte);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_dtim_period, pst_hal_vap, ul_dtim_period);
}

OAL_STATIC  OAL_INLINE oal_void hal_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_sta_dtim_period, pst_hal_vap, pul_dtim_period);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_dtim_count, pst_hal_vap, ul_dtim_count);
}

OAL_STATIC  OAL_INLINE oal_void hal_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_dtim_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_psm_dtim_count, pst_hal_vap, puc_dtim_count);
}


OAL_STATIC  OAL_INLINE oal_void hal_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_dtim_count, pst_hal_vap, uc_dtim_count);
}


OAL_STATIC  OAL_INLINE oal_void hal_pm_wlan_servid_register(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_ret)
{
    HAL_PUBLIC_HOOK_FUNC2(_pm_wlan_servid_register, pst_hal_vap, pul_ret);
}

OAL_STATIC  OAL_INLINE oal_void hal_pm_wlan_servid_unregister(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_pm_wlan_servid_unregister, pst_hal_vap);
}


OAL_STATIC  OAL_INLINE oal_void hal_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_sta_tsf_tbtt, pst_hal_vap);
}


OAL_STATIC  OAL_INLINE oal_void hal_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_sta_tsf_tbtt, pst_hal_vap);
}


OAL_STATIC OAL_INLINE oal_void hal_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_cfg_slottime_type, pst_hal_device, ul_slottime_type);
}

/*****************************************************************************
  10.4 SDT��д�Ĵ�������
*****************************************************************************/

/*****************************************************************************
    оƬ�������ͺ�Э��������ͻ���ת��
*****************************************************************************/


OAL_STATIC  OAL_INLINE hal_cipher_protocol_type_enum_uint8 hal_cipher_suite_to_ctype(wlan_ciper_protocol_type_enum_uint8 en_cipher_suite)
{
    /********************************************************************
    *  ���ܷ�ʽ      ������ܷ�ʽ��Ӧ����ֵ        Ӳ��������������Ӧ��ֵ
    *  User Grp                 0
    *   WEP-40                  1                           0
    *   TKIP                    2                           1
    *   RES                     3
    *   CCMP                    4                           2
    *   WEP-104                 5                           4
    *   BIP                     6                           5
    *   ��Ӧ�����ܣ�����Ӳ������������bit3~0 Ϊ             3
    ********************************************************************/

    hal_cipher_protocol_type_enum_uint8 en_ciper_type = HAL_NO_ENCRYP;

    switch(en_cipher_suite)
    {
        case WLAN_80211_CIPHER_SUITE_WEP_40:
            en_ciper_type = HAL_WEP40;
            break;
        case WLAN_80211_CIPHER_SUITE_TKIP:
            en_ciper_type = HAL_TKIP;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            en_ciper_type = HAL_CCMP;
            break;
        case WLAN_80211_CIPHER_SUITE_WEP_104:
            en_ciper_type = HAL_WEP104;
            break;
        case WLAN_80211_CIPHER_SUITE_BIP:
            en_ciper_type = HAL_BIP;
            break;
        default:
            en_ciper_type = HAL_NO_ENCRYP;
            break;
    }
    return en_ciper_type;
}


OAL_STATIC  OAL_INLINE  wlan_ciper_protocol_type_enum_uint8 hal_ctype_to_cipher_suite(hal_cipher_protocol_type_enum_uint8 en_cipher_type)
{
    /********************************************************************
    *  ���ܷ�ʽ      ������ܷ�ʽ��Ӧ����ֵ        Ӳ��������������Ӧ��ֵ
    *  User Grp                 0
    *   WEP-40                  1                           0
    *   TKIP                    2                           1
    *   RES                     3
    *   CCMP                    4                           2
    *   WEP-104                 5                           4
    *   BIP                     6                           5
    *   ��Ӧ�����ܣ�����Ӳ������������bit3~0 Ϊ             3
    ********************************************************************/

    wlan_ciper_protocol_type_enum_uint8 en_ciper_suite = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    switch(en_cipher_type)
    {
        case HAL_WEP40:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_WEP_40;
            break;
        case HAL_TKIP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_TKIP;
            break;
        case HAL_CCMP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_CCMP;
            break;
        case HAL_WEP104:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_WEP_104;
            break;
        case HAL_BIP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_BIP;
            break;
        default:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
            break;
    }
    return en_ciper_suite;
}

/*****************************************************************************
 �� �� ��  : hal_mwo_det_enable_mac_counter
 ��������  : ��⵽΢��¯����ʹ��MAC����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : heyinjun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_mwo_det_enable_mac_counter, pst_hal_device, l_enable_reg_val);
}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC OAL_INLINE oal_void hal_coex_sw_irq_set(oal_uint8 uc_irq_en)
{
    HAL_PUBLIC_HOOK_FUNC1(_coex_sw_irq_set, uc_irq_en);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_cf_end_data_rate(oal_uint32 *ul_cfend_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_cf_end_data_rate, ul_cfend_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_cf_end_phy_mode(oal_uint32 *ul_cfend_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_cf_end_phy_mode, ul_cfend_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_done_cnt(oal_uint32 *ul_abort_done_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_done_cnt, ul_abort_done_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_end_cnt(oal_uint32 *ul_abort_end_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_end_cnt, ul_abort_end_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_null_data_rate(oal_uint32 *ul_null_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_null_data_rate, ul_null_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_null_phy_mode(oal_uint32 *ul_null_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_null_phy_mode, ul_null_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_qos_null_seq_num(oal_uint32 *ul_qosnull_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_qos_null_seq_num, ul_qosnull_seq_num);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_selfcts_data_rate(oal_uint32 *ul_selfcts_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_selfcts_data_rate, ul_selfcts_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_selfcts_phy_mode(oal_uint32 *ul_selfcts_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_selfcts_phy_mode, ul_selfcts_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_start_cnt(oal_uint32 *ul_abort_start_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_start_cnt, ul_abort_start_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_all_abort_preempt_type(oal_uint8 *uc_preempt_type)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_all_abort_preempt_type, uc_preempt_type);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_occupied_period(oal_uint16 *ul_occupied_period)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_occupied_period, ul_occupied_period);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_pa_status(oal_uint32 *ul_pa_status)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_pa_status, ul_pa_status);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_phy_tx_rx_status(oal_uint32 *ul_phy_tx_rx_status)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_phy_tx_rx_status, ul_phy_tx_rx_status);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_post_preempt_cnt(oal_uint32 *ul_post_preempt_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_post_preempt_cnt, ul_post_preempt_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_post_preempt_fail_cnt(oal_uint32 *ul_post_preempt_fail_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_post_preempt_fail_cnt, ul_post_preempt_fail_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_preempt_cnt(oal_uint32 *ul_preempt_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_preempt_cnt, ul_preempt_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_soc_bt_gpreg(oal_uint16 *pus_bt_status)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_soc_bt_gpreg, pus_bt_status);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_soc_ble_gpreg(oal_uint16 *pus_ble_status)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_soc_ble_gpreg, pus_ble_status);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_cf_end_data_rate(oal_uint32 ul_cfend_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_cf_end_data_rate, ul_cfend_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_cf_end_phy_mode(oal_uint32 ul_cfend_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_cf_end_phy_mode, ul_cfend_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_cnt_clear(oal_void)
{
    HAL_PUBLIC_HOOK_FUNC(_set_btcoex_abort_cnt_clear);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_null_buff_addr(oal_uint32 ul_abort_null_buff_addr)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_null_buff_addr, ul_abort_null_buff_addr);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_null_data_rate(oal_uint32 ul_null_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_null_data_rate, ul_null_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_null_phy_mode(oal_uint32 ul_null_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_null_phy_mode, ul_null_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_qos_null_seq_num(oal_uint32 ul_qosnull_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_qos_null_seq_num, ul_qosnull_seq_num);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_selfcts_data_rate(oal_uint32 ul_selfcts_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_selfcts_data_rate, ul_selfcts_data_rate);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_selfcts_duration(oal_uint32 ul_selfcts_duration)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_selfcts_duration, ul_selfcts_duration);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_selfcts_phy_mode(oal_uint32 ul_selfcts_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_selfcts_phy_mode, ul_selfcts_phy_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_timeout_val(oal_uint16 us_bt_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_timeout_val, us_bt_time);
}
OAL_STATIC OAL_INLINE oal_void hal_set_blecoex_abort_timeout_val(oal_uint16 us_ble_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_blecoex_abort_timeout_val, us_ble_time);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_all_abort_preempt_type(coex_preempt_frame_enum_uint8 en_preempt_type)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_all_abort_preempt_type, en_preempt_type);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_hw_rx_priority_dis(oal_uint8 uc_hw_rx_prio_dis)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_hw_rx_priority_dis, uc_hw_rx_prio_dis);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_hw_priority_en(oal_uint8 uc_hw_prio_en)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_hw_priority_en, uc_hw_prio_en);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_max_cnt(oal_uint32 ul_abort_max_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_max_cnt, ul_abort_max_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_occupied_period(oal_uint16 ul_occupied_period)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_occupied_period, ul_occupied_period);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_post_preempt_timeout_val(oal_uint32 ul_post_preempt_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_post_preempt_timeout_val, ul_post_preempt_time);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_post_preempt_tx_cnt(oal_uint8 uc_post_preempt_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_post_preempt_tx_cnt, uc_post_preempt_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_rf_stable_time(oal_uint32 ul_rf_stable_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_rf_stable_time, ul_rf_stable_time);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_sw_all_abort_ctrl(oal_uint8 uc_sw_abort_ctrl)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_sw_all_abort_ctrl, uc_sw_abort_ctrl);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_sw_all_abort_mode(oal_uint8 uc_sw_abort_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_sw_all_abort_mode, uc_sw_abort_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_sw_priority_flag(oal_uint8 uc_sw_prio_flag)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_sw_priority_flag, uc_sw_prio_flag);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_soc_gpreg0(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_btcoex_soc_gpreg0, uc_val, us_mask, uc_offset);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_soc_gpreg1(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_btcoex_soc_gpreg1, uc_val, us_mask, uc_offset);
}
OAL_STATIC OAL_INLINE oal_void hal_update_btcoex_btble_status(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_update_btcoex_btble_status, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_init(oal_void *p_arg)
{
    HAL_PUBLIC_HOOK_FUNC1(_btcoex_init, p_arg);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_statistic(oal_void)
{
    HAL_PUBLIC_HOOK_FUNC(_get_btcoex_statistic);
}
OAL_STATIC OAL_INLINE oal_void hal_mpw_soc_write_reg(oal_uint32 ulQuryRegAddrTemp, oal_uint16 usQuryRegValueTemp)
{
    HAL_PUBLIC_HOOK_FUNC2(_mpw_soc_write_reg, ulQuryRegAddrTemp, usQuryRegValueTemp);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_update_ap_beacon_count(oal_uint32 *pul_beacon_count)
{
    HAL_PUBLIC_HOOK_FUNC1(_btcoex_update_ap_beacon_count, pul_beacon_count);
}
#ifdef _PRE_WLAN_FEATURE_LTECOEX
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_enable(oal_uint8 ltecoex_enable)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_enable, ltecoex_enable);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_lte_pol_ctl(oal_uint8 uc_lte_inactive)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_lte_pol_ctl, uc_lte_inactive);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_lte_pol_ctl_get(oal_uint8 *uc_lte_inactive)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_lte_pol_ctl_get, uc_lte_inactive);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_lte_pol_ctl_set(oal_uint8 uc_lte_inactive)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_lte_pol_ctl_set, uc_lte_inactive);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_lte_tx_delay_cnt_get(oal_uint8 *uc_tx_delay_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_lte_tx_delay_cnt_get, uc_tx_delay_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_lte_tx_delay_cnt_set(oal_uint8 uc_tx_delay_cnt)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_lte_tx_delay_cnt_set, uc_tx_delay_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_rx_abort_timeout(oal_uint32 uc_pri_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_rx_abort_timeout, uc_pri_time);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_sw_hw_mode(oal_uint8 uc_sw_hd_mode)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_sw_hw_mode, uc_sw_hd_mode);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_wlan_priority_set(oal_uint8 uc_man_set)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_wlan_priority_set, uc_man_set);
}
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_wlan_priority_time(oal_uint32 uc_pri_time)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_wlan_priority_time, uc_pri_time);
}
#endif

#endif
OAL_STATIC OAL_INLINE oal_void hal_tx_get_dscr_iv_ls_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ls_val, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_key_id)
{
    HAL_PUBLIC_HOOK_FUNC4(_tx_get_dscr_iv_ls_word, pst_dscr, pul_iv_ls_val, uc_chiper_type, uc_chiper_key_id);
}
OAL_STATIC  OAL_INLINE oal_void hal_get_fem_pa_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_fem_pa_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_fem_pa_status, pst_hal_device, ul_cali_check_fem_pa_status);
}

#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC OAL_INLINE oal_void hal_dft_clear_machw_stat_info(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_clear_machw_stat_info, pst_hal_device);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_get_machw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_machw_stat,oal_uint8 us_bank_select)
{
    HAL_PUBLIC_HOOK_FUNC3(_dft_get_machw_stat_info, pst_hal_device, pst_machw_stat,us_bank_select);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_set_phy_stat_node(hal_to_dmac_device_stru *pst_hal_device,oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    HAL_PUBLIC_HOOK_FUNC2(_dft_set_phy_stat_node, pst_hal_device, pst_phy_node_idx);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_get_phyhw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_phyhw_stat,oal_uint8 us_bank_select)
{
    HAL_PUBLIC_HOOK_FUNC3(_dft_get_phyhw_stat_info, pst_hal_device, pst_phyhw_stat,us_bank_select);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_get_rfhw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_rfhw_stat)
{
    HAL_PUBLIC_HOOK_FUNC2(_dft_get_rfhw_stat_info, pst_hal_device, pst_rfhw_stat);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_print_machw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_machw_stat, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_print_phyhw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_phyhw_stat, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_print_rfhw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_rfhw_stat, pst_hal_device);
}
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hal_ext_if.h */
