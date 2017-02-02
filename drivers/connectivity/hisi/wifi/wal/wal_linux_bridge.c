


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_profiling.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_spec.h"

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
#include "hal_ext_if.h"
#endif

#include "hmac_vap.h"
#include "mac_vap.h"
#include "mac_resource.h"
#include "mac_data.h"
#include "hmac_ext_if.h"

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
#include "hmac_vap.h"
#endif

#include "wal_main.h"
#include "wal_linux_bridge.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_BRIDGE_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT

/*****************************************************************************
 �� �� ��  : wal_vap_start_xmit
 ��������  : �ҽӵ�VAP��Ӧnet_device�ṹ���µķ��ͺ���
 �������  : pst_buf: SKB�ṹ��,����dataָ��ָ����̫��ͷ
             pst_dev: net_device�ṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_net_dev_tx_enum  wal_vap_start_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{

    mac_vap_stru   *pst_vap;
    hmac_vap_stru  *pst_hmac_vap;
    oal_uint        ul_flags;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* ��ȡVAP�ṹ�� */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* ���VAP�ṹ�岻���ڣ��������� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_vap_start_xmit::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

     pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (pst_buf == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_data::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_vap->uc_vap_id);

    if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id])>=1000)
//    if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[0]) >= 1000)
    {
        oal_netbuf_free(pst_buf);
        if(g_tx_debug)
        {
            /* ����ά����Ϣ����tx_event_num��ֵ��ӡ�������û��������ϣ�����һֱping��ͨ����g_tx_debug���أ������ʱ��ֵ��Ϊ1���������쳣 */
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_vap_start_xmit::tx_event_num value is [%d].}", (oal_int32)oal_atomic_read(&(pst_hmac_vap->ul_tx_event_num)));
            OAL_IO_PRINT("wal_vap_start_xmit too fast\n");
        }
    }
    else
    {
        if(g_tx_debug)
            OAL_IO_PRINT("wal_vap_start_xmit enqueue and post event\n");

		oal_spin_lock_irq_save(&pst_hmac_vap->st_smp_lock, &ul_flags);
        OAL_NETBUF_QUEUE_TAIL(&(pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]),pst_buf);
//        OAL_NETBUF_QUEUE_TAIL(&(pst_hmac_vap->st_tx_queue_head[0]),pst_buf);
        oal_spin_unlock_irq_restore(&pst_hmac_vap->st_smp_lock, &ul_flags);

    }

    hmac_tx_post_event(pst_vap);

    return OAL_NETDEV_TX_OK;
}

#endif

/*****************************************************************************
 �� �� ��  : wal_bridge_vap_xmit
 ��������  : �ҽӵ�VAP��Ӧnet_device�ṹ���µķ��ͺ���
 �������  : pst_buf: SKB�ṹ��,����dataָ��ָ����̫��ͷ
             pst_dev: net_device�ṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_net_dev_tx_enum  wal_bridge_vap_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    mac_vap_stru                *pst_vap;
    hmac_vap_stru               *pst_hmac_vap;
    oal_uint32                   ul_ret;
    oal_uint8                    uc_data_type;
    oal_uint16                   us_len;

#if defined(_PRE_WLAN_FEATURE_PROXYSTA) ||  defined(_PRE_WLAN_FEATURE_ALWAYS_TX)
    mac_device_stru  *pst_mac_device;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_buf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* ��ȡVAP�ṹ�� */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* ���VAP�ṹ�岻���ڣ��������� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_add_vap::pst_hmac_vap null.}");
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::mac_res_get_dev is null!}");
        oal_netbuf_free(pst_buf);

        return OAL_NETDEV_TX_OK;
    }

    /*��������ģ�pst_device_struָ���л�δ״̬, ���������л�δ����״̬*/
    if ((OAL_SWITCH_ON == pst_vap->bit_al_tx_flag)
    || ((pst_mac_device->pst_device_stru != OAL_PTR_NULL) && (HAL_ALWAYS_TX_AMPDU_ENABLE == pst_mac_device->pst_device_stru->bit_al_tx_flag)))
    //|| (HAL_ALWAYS_RX_DISABLE != pst_mac_device->pst_device_stru->bit_al_rx_flag))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::the vap alway tx/rx!}\r\n");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (OAL_UNLIKELY(pst_buf == OAL_PTR_NULL))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    /* ����̫��������֡�ϱ�SDT */
    hmac_tx_report_eth_frame(pst_vap, pst_buf);

    if(OAL_GET_THRUPUT_BYPASS_ENABLE(OAL_TX_LINUX_BYPASS))
    {
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

    /* ά�⣬����ؼ�֡��ӡ */
    uc_data_type =  mac_get_eth_type((mac_ether_header_stru *)oal_netbuf_payload(pst_buf), &us_len);
    if((MAC_DATA_DHCP == uc_data_type) || (MAC_DATA_ARP == uc_data_type) ||(MAC_DATA_EAPOL == uc_data_type))
    {
        OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_WPA, "{wal_bridge_vap_xmit::send datatype==%u len==%u}[0:dhcp 1:arp 2:eapol]", uc_data_type, us_len);
    }
#if 0
#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_TRUE == pst_vap->st_vap_dft.ul_flg && OAL_PTR_NULL != pst_vap->st_vap_dft.pst_vap_dft_stats)
    {
        MAC_VAP_STATS_PKT_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_pkts, 1);
        MAC_VAP_STATS_BYTE_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_bytes,
                                OAL_NETBUF_LEN(pst_buf) - ETHER_HDR_LEN);
    }
#endif
#endif
    /* ����VAP״̬������滥�⣬��Ҫ�������� */
    oal_spin_lock_bh(&pst_hmac_vap->st_lock_state);

    /* �ж�VAP��״̬�����û��UP���������� */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state)))
    #ifdef _PRE_WLAN_FEATURE_ROAM
       && OAL_UNLIKELY(!(MAC_VAP_STATE_ROAMING == pst_vap->en_vap_state))
    #endif  //_PRE_WLAN_FEATURE_ROAM
        )
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
        oal_netbuf_free(pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);

        return OAL_NETDEV_TX_OK;
    }

    OAL_NETBUF_NEXT(pst_buf) = OAL_PTR_NULL;
    OAL_NETBUF_PREV(pst_buf) = OAL_PTR_NULL;

    OAL_MEMZERO(OAL_NETBUF_CB(pst_buf), OAL_NETBUF_CB_SIZE());

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::mac_res_get_dev is null!}");
        oal_netbuf_free(pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);

        return OAL_NETDEV_TX_OK;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* ARP��DHCP��ICMPv6�����ݰ��ĵ�ַת�� (ֻ��proxy STA�ķ��͵İ�����Ҫ��ַת��)*/
        if ((OAL_TRUE == pst_vap->st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            ul_ret = hmac_tx_proxysta_mat(pst_buf, pst_vap);

            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::hmac_tx_proxysta_mat fail.}");
                oal_netbuf_free(pst_buf);
                oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);

                return OAL_NETDEV_TX_OK;
            }
        }
    }

#endif

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT);
    ul_ret = hmac_tx_lan_to_wlan(pst_vap, pst_buf);

    /* ����ʧ�ܣ�Ҫ�ͷ��ں������netbuff�ڴ�� */
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        //hmac_free_netbuf_list(pst_buf);
        oal_netbuf_free(pst_buf);
    }

    oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);

    return OAL_NETDEV_TX_OK;
}

/*lint -e19*/
oal_module_symbol(wal_bridge_vap_xmit);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

