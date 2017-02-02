/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_beacon.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��3��28��
  ����޸�   :
  ��������   : Beacon֡��֡ ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��28��
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
#include "wlan_spec.h"
#include "wlan_types.h"

#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "oam_main.h"

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#include "pm_extern.h"
#endif

#include "hal_ext_if.h"
#include "mac_frame.h"
#include "mac_ie.h"
#include "mac_vap.h"
#include "mac_frame.h"


#include "dmac_main.h"
#include "dmac_device.h"
#include "dmac_beacon.h"
#include "dmac_chan_mgmt.h"
#include "dmac_psm_ap.h"
#include "dmac_mgmt_sta.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_device.h"
#include "dmac_scan.h"
#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "mac_device.h"
#include "dmac_dft.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "dmac_sta_pm.h"
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BEACON_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_CHIP_TEST
static dmac_beacon_test_stru g_beacon_offload_test; /*�����ڲ���*/
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#define COEX_LINKLOSS_OCCUP_TIMES 				(15)
#define COEX_LINKLOSS_OCCUP_PERIOD				(20000) /*us*/
#endif
#define RX_DATA_RATE                            (50000) /* 50M */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_set_tim_ie
 ��������  : vap����ʱ�Լ�ÿ��tbtt�жϣ�ap�ѱ��ص�tim_bitmap������beacon֡���
             TIM��ϢԪ�ؿռ�
 �������  : pst_vap: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_tim_ie(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    dmac_vap_stru  *pst_dmac_vap;
    oal_uint8       uc_tim_offset = 0;
    oal_uint8       uc_PVBitmap_len;

    /***************************************************************************
     ---------------------------------------------------------------------------
     |EID |Len |DTIM Count |DTIM Period |Bitmap Control |Partial Virtual Bitmap|
     ---------------------------------------------------------------------------
     |1   |1   |1          |1           |1              |1~251                 |
     ---------------------------------------------------------------------------
    ***************************************************************************/

    pst_dmac_vap = (dmac_vap_stru *)pst_vap;

    uc_PVBitmap_len  = pst_dmac_vap->puc_tim_bitmap[0];
    uc_tim_offset    = 2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0));
    if (uc_PVBitmap_len + uc_tim_offset > pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_WIFI_BEACON, "{dmac_set_tim_ie::puc_tim_bitmap[0x%x] = 0x%x bitmap_len[%d] .}",
                       pst_dmac_vap->puc_tim_bitmap, OAL_NTOH_32(*(oal_uint32 *)(pst_dmac_vap->puc_tim_bitmap)), pst_dmac_vap->uc_tim_bitmap_len);
        uc_PVBitmap_len = 1;
    }
    /* ��vap�б����dtim_countֵ����DTIM Count�ֶΣ�ÿ�ζ����1��������[0,DTIM_period]��ѭ�� */
    if (0 == pst_dmac_vap->uc_dtim_count)
    {
        pst_dmac_vap->uc_dtim_count = (oal_uint8)(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod - 1);
    }
    else
    {
        pst_dmac_vap->uc_dtim_count--;
    }
    puc_buffer[0] = MAC_EID_TIM;
    puc_buffer[1] = uc_PVBitmap_len + MAC_TIM_LEN_EXCEPT_PVB;
    puc_buffer[2] = pst_dmac_vap->uc_dtim_count;
    puc_buffer[3] = (oal_uint8)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;
    puc_buffer[4] = pst_dmac_vap->puc_tim_bitmap[1];

    /* ����Beacon֡��DTIM Control bit0��ֵ�������´�TBTT�жϵ���ʱ���ж��Ƿ���Ҫ���ͻ���㲥���鲥֡ */
    pst_dmac_vap->en_dtim_ctrl_bit0 = (oal_bool_enum_uint8)(pst_dmac_vap->puc_tim_bitmap[1] & BIT0);

    /* ��vap���ص�bitmap��Ϊ0�Ĳ��ָ��Ƶ�beacon֡��Ӧ�ռ䣬��ΪPartial Virtual Bitmap */
    oal_memcopy(&puc_buffer[5], pst_dmac_vap->puc_tim_bitmap + uc_tim_offset, uc_PVBitmap_len);


    *puc_ie_len = MAC_IE_HDR_LEN + MAC_TIM_LEN_EXCEPT_PVB + uc_PVBitmap_len;
}

/*****************************************************************************
 �� �� ��  : dmac_encap_beacon
 ��������  : beacon֡��֡
 �������  : pst_dmac_vap  : ָ��vap�Ľṹ��
             puc_beacon_buf: ָ��beacon buffer
 �������  : puc_beacon_len: beacon֡�ĳ���
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_encap_beacon(
                dmac_vap_stru               *pst_dmac_vap,
                oal_uint8                   *puc_beacon_buf,
                oal_uint16                  *pus_beacon_len)
{

    oal_uint8        uc_ie_len;
    oal_uint8        auc_bcst_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* �㲥��ַ */
    oal_uint8       *puc_bf_origin = puc_beacon_buf;
    mac_device_stru *pst_mac_device;
    mac_vap_stru    *pst_mac_vap;
    oal_uint16       us_app_ie_len;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_encap_beacon::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/
    /* ����Frame Control�ֶ� */
    mac_hdr_set_frame_control(puc_beacon_buf, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_BEACON);

    /* ����durationΪ0����Ӳ���� */
    mac_hdr_set_duration(puc_beacon_buf, 0);

    /* ����address1, DA��һ���㲥��ַ */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR1_OFFSET, auc_bcst_addr, WLAN_MAC_ADDR_LEN);

    /* ����address2��SA��mac��ַ */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR2_OFFSET,
                pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    /* ����address3, BSSID */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR3_OFFSET,
                pst_dmac_vap->st_vap_base_info.auc_bssid,
                WLAN_MAC_ADDR_LEN);

    /* ���÷�Ƭ���Ϊ0��beacon֡û��sequence number */
    mac_hdr_set_fragment_number(puc_beacon_buf, 0);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                       Beacon Frame - Frame Body                       */
    /* ----------------------------------------------------------------------*/
    /* |Timestamp|BcnInt|CapInfo|SSID|SupRates|DSParamSet|TIM  |CountryElem |*/
    /* ----------------------------------------------------------------------*/
    /* |8        |2     |2      |2-34|3-10    |3         |6-256|8-256       |*/
    /* ----------------------------------------------------------------------*/
    /* |PowerConstraint |Quiet|TPC Report|ERP |RSN  |WMM |Extended Sup Rates|*/
    /* ----------------------------------------------------------------------*/
    /* |3               |8    |4         |3   |4-255|26  | 3-257            |*/
    /* ----------------------------------------------------------------------*/
    /* |BSS Load |HT Capabilities |HT Operation |Overlapping BSS Scan       |*/
    /* ----------------------------------------------------------------------*/
    /* |7        |28              |24           |16                         |*/
    /* ----------------------------------------------------------------------*/
    /* |Extended Capabilities |                                              */
    /* ----------------------------------------------------------------------*/
    /* |3-8                   |                                              */
    /*************************************************************************/
    /* timestamp��Ӳ������ */
    puc_beacon_buf += MAC_80211_FRAME_LEN;
    OAL_MEMZERO(puc_beacon_buf, 8);

    /* Initialize index */
    puc_beacon_buf += MAC_TIME_STAMP_LEN;

    /* ����beacon interval */
    mac_set_beacon_interval_field(pst_mac_vap, puc_beacon_buf);
    puc_beacon_buf += MAC_BEACON_INTERVAL_LEN;

    /* ����capability information */
    mac_set_cap_info_ap(pst_mac_vap, puc_beacon_buf);
    puc_beacon_buf += MAC_CAP_INFO_LEN;

    /* ����ssid element,���������ssid���صĻ�������ssid */
    mac_set_ssid_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len, WLAN_FC0_SUBTYPE_BEACON);
    puc_beacon_buf += uc_ie_len;

    /* ����֧�ֵ����ʼ� */
    mac_set_supported_rates_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ����dsss������ */
    mac_set_dsss_params(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;
    /* ����TIM��ϢԪ����beacon֡�е�ƫ�� */
    pst_dmac_vap->uc_tim_offset_in_beacon = (oal_uint8)(puc_beacon_buf - puc_bf_origin);

    /* ���tim��Ϣ */
    dmac_set_tim_ie(pst_dmac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11D
    /* ���country��Ϣ */
    mac_set_country_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_11AC2G
    mac_set_vendor_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#endif

    /* ���power constraint��Ϣ */
    mac_set_pwrconstraint_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���quiet��Ϣ */
    mac_set_quiet_ie(pst_mac_vap, puc_beacon_buf, MAC_QUIET_COUNT, MAC_QUIET_PERIOD,
                      MAC_QUIET_DURATION, MAC_QUIET_OFFSET, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���TPC Report��Ϣ */
    mac_set_tpc_report_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���erp��Ϣ */
    mac_set_erp_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#if defined(_PRE_WLAN_FEATURE_WPA2)
    /* ���WPA2 ��ȫ�����Ϣ */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_beacon_buf, &uc_ie_len, DMAC_RSNA_802_11I);
    puc_beacon_buf += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA2) */

#if defined (_PRE_WLAN_FEATURE_WPA)
    /* ���WPA ��ȫ�����Ϣ */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_beacon_buf, &uc_ie_len, DMAC_WPA_802_11I);
    puc_beacon_buf += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA) */

    /* ���wmm��Ϣ */
    //mac_set_wmm_params_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    mac_set_wmm_params_ie(pst_mac_vap, puc_beacon_buf, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���extended supported rates��Ϣ */
    mac_set_exsup_rates_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���bss load��Ϣ */
    mac_set_bssload_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���HT Capabilities��Ϣ */
    mac_set_ht_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���HT Operation��Ϣ */
    mac_set_ht_opern_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���Overlapping BSS Scan��Ϣ */
    mac_set_obss_scan_params(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���Extended Capabilities��Ϣ */
    mac_set_ext_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���vht cap��Ϣ */
    mac_set_vht_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���vht opern��Ϣ */
    mac_set_vht_opern_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* ���CSA IE */

    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn)
    {
        mac_set_csa_ie(pst_mac_vap->st_ch_switch_info.uc_announced_channel,
                   pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt,
                   puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }

#ifdef _PRE_WLAN_CHIP_TEST
    if (1 == g_beacon_offload_test.uc_csa_in_beacon)
    {
        mac_set_csa_ie(g_beacon_offload_test.uc_announced_channel,
                   g_beacon_offload_test.uc_switch_cnt,
                   puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    if (1 == g_beacon_offload_test.uc_opmode_in_beacon)
    {
        puc_beacon_buf[0] = MAC_EID_OPMODE_NOTIFY;
        puc_beacon_buf[1] = MAC_OPMODE_NOTIFY_LEN;
        puc_beacon_buf[2] = g_beacon_offload_test.uc_opmode;
        puc_beacon_buf += (MAC_IE_HDR_LEN + MAC_OPMODE_NOTIFY_LEN);
    }
#endif
#endif

    /* ���WPS��Ϣ */
    mac_add_app_ie((oal_void *)pst_mac_vap, puc_beacon_buf, &us_app_ie_len, OAL_APP_BEACON_IE);
    puc_beacon_buf += us_app_ie_len;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* ���p2p noa Attribute*/
    if((IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_NOA_ENABLED(pst_dmac_vap) || IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        mac_set_p2p_noa(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }
#endif
    *pus_beacon_len = (oal_uint16)(puc_beacon_buf - puc_bf_origin);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_beacon_alloc
 ��������  : ����beacon֡�ڴ�
 �������  : pst_dmac_vap: ָ��vap�ṹ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_beacon_alloc(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                  *pauc_beacon_buf[DMAC_VAP_BEACON_BUFFER_BUTT];
    oal_uint16                  us_beacon_len = 0;
    hal_beacon_tx_params_stru   st_beacon_tx_params;
    hal_tx_txop_alg_stru       *pst_tx_param;
    wlan_channel_band_enum_uint8 en_band;

    /* Ŀǰacs���up��vap��һ��wait��up�����ʱ��beacon֡�ڵ�һ��up��ʱ���ڴ��Ѿ����룬�����ٴν���ʱֱ�ӷ��ؼ��� */
    if((OAL_PTR_NULL != pst_dmac_vap->pauc_beacon_buffer[0]) && (OAL_PTR_NULL != pst_dmac_vap->pauc_beacon_buffer[1]))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::vap beacon buf has been alloc.}\r\n");
        return OAL_SUCC;
    }

    /* �����һ��beacon֡�ڴ� */
    pauc_beacon_buf[0] = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_MGMT_PKT, WLAN_MEM_SHARED_MGMT_PKT_SIZE1, OAL_TRUE);
    if (OAL_PTR_NULL == pauc_beacon_buf[0])
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::pauc_beacon_buf[0] null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ����ڶ���beacon֡�ڴ� */
    pauc_beacon_buf[1] = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_MGMT_PKT, WLAN_MEM_SHARED_MGMT_PKT_SIZE1, OAL_TRUE);
    if (OAL_PTR_NULL == pauc_beacon_buf[1])
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::pauc_beacon_buf[1] null.}");

        /* �ͷ���������ڴ� */
        OAL_MEM_FREE(pauc_beacon_buf[0], OAL_TRUE);
        pauc_beacon_buf[0] = OAL_PTR_NULL;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ʼbeacon��֡ */
    dmac_encap_beacon(pst_dmac_vap, pauc_beacon_buf[0], &us_beacon_len);

    oal_memcopy(pauc_beacon_buf[1], pauc_beacon_buf[0], us_beacon_len);

    /* ��beacon֡�ҵ�vap�� */
    pst_dmac_vap->pauc_beacon_buffer[0] = pauc_beacon_buf[0];
    pst_dmac_vap->pauc_beacon_buffer[1] = pauc_beacon_buf[1];

    pst_dmac_vap->uc_beacon_idx = 0;    /* ��ʼ������Ӳ����beacon֡���� */
    pst_dmac_vap->us_beacon_len = us_beacon_len;

    /* ��д����Beacon֡���� */
    en_band  = pst_dmac_vap->st_vap_base_info.st_channel.en_band;
    pst_tx_param = &pst_dmac_vap->ast_tx_mgmt_bmcast[en_band];
    pst_tx_param->ast_per_rate[0].rate_bit_stru.bit_reserve = 0;

    st_beacon_tx_params.ul_pkt_ptr   = (oal_uint32)((pauc_beacon_buf[0]));
    st_beacon_tx_params.us_pkt_len   = us_beacon_len;
    st_beacon_tx_params.pst_tx_param = pst_tx_param;

    /* ����beacon period */
    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

    /* �ж��Ƿ�����˫·�������� */
    if(1 == pst_dmac_vap->en_beacon_chain_active)
    {
        /* ��һ��beacon֡��ͨ��0���ͣ��ڶ���beacon֡��ͨ��1���� */
        if(pst_dmac_vap->uc_beacon_idx == DMAC_VAP_BEACON_BUFFER1)
        {
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
        }
        pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 2;
    }

    /* HAL����Beacon֡�ӿ� */
    hal_vap_send_beacon_pkt(pst_dmac_vap->pst_hal_vap, &st_beacon_tx_params);

    /* DBACʹ�ܺ���DBAC��������TSF */
#ifdef _PRE_WLAN_FEATURE_DBAC
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
     /* 1102 DBAC todo DBACδ������ʱ��ͨ��enable��Ϣ�жϣ�����GO���ᷢ��Beacon֡*/
    {
        mac_device_stru *pst_device = mac_res_get_dev((oal_uint32)pst_dmac_vap->st_vap_base_info.uc_device_id);

        if(pst_device->en_dbac_enabled)
        {
			/* force PAUSE when DBAC enabled */
            pst_dmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_PAUSE;
            OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "{dmac_beacon_alloc::dbac enabled, tsf not started.}\r\n");
            return OAL_SUCC;
        }
    }
#endif
#endif

    /* ����tsf */
    hal_vap_start_tsf(pst_dmac_vap->pst_hal_vap, OAL_FALSE);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_beacon_free
 ��������  : �ͷ�beacon֡�ڴ�
 �������  : pst_dmac_vap: ָ��dmac vap
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_beacon_free(dmac_vap_stru *pst_dmac_vap)
{
    OAL_MEM_FREE(pst_dmac_vap->pauc_beacon_buffer[0], OAL_TRUE);
    OAL_MEM_FREE(pst_dmac_vap->pauc_beacon_buffer[1], OAL_TRUE);

    pst_dmac_vap->pauc_beacon_buffer[0] = OAL_PTR_NULL;
    pst_dmac_vap->pauc_beacon_buffer[1] = OAL_PTR_NULL;

    /* �ر�tsf */
    hal_vap_set_machw_tsf_disable(pst_dmac_vap->pst_hal_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tbtt_exception_handler
 ��������  : ͳ��MAC�����жϼ���
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_exception_handler(dmac_vap_stru *pst_dmac_vap)
{
    hal_to_dmac_device_stru         *pst_hal_device = pst_dmac_vap->pst_hal_device;
    hal_dfr_err_opern_stru          *pst_dfr_err;
    hal_mac_error_type_enum_uint8    en_error_id;

    /* �������д������� */
    for (en_error_id = 0; en_error_id < HAL_MAC_ERROR_TYPE_BUTT; en_error_id++)
    {
        pst_dfr_err = &(pst_hal_device->st_dfr_err_opern[en_error_id]);

        pst_dfr_err->us_tbtt_cnt++;

        if (pst_dfr_err->us_tbtt_cnt >= 10)
        {
            pst_dfr_err->us_tbtt_cnt = 0;

            /* ÿ10��TBTT�жϣ����˼������� */
            pst_dfr_err->us_err_cnt = 0;
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_handle_tbtt_chan_mgmt_ap
 ��������  : AP��TBTT�ж��н����ŵ�����
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ�룬ָ��AP
 �������  : pst_dmac_vap: DMAC VAP�ṹ��ָ�룬ָ��ap
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_handle_tbtt_chan_mgmt_ap(dmac_vap_stru *pst_dmac_vap)
{
    mac_vap_stru              *pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);
    mac_ch_switch_info_stru   *pst_csi = &(pst_mac_vap->st_ch_switch_info);

    /* AP׼�������ŵ��л� */
    if (WLAN_CH_SWITCH_STATUS_1 == pst_csi->en_ch_switch_status)
    {
        if (0 == pst_csi->uc_ch_switch_cnt)
        {
            oal_uint8   auc_null_addr[6] = {0};

            /* �ڵ�ǰ�ŵ�����beacon֡���� */
            hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);

            /* ��Beacon֡���Ƴ�Channel Switch Announcement IE */
            pst_csi->en_csa_present_in_bcn = OAL_FALSE;

            mac_vap_set_bssid(pst_mac_vap, auc_null_addr);
            dmac_chan_attempt_new_chan(pst_dmac_vap, pst_csi->uc_announced_channel, pst_csi->en_announced_bandwidth);
        }
        else
        {
            pst_csi->uc_ch_switch_cnt--;
        }
    }
    else if (0 == pst_dmac_vap->uc_dtim_count)
    {
        if (WLAN_BW_SWITCH_40_TO_20 == pst_csi->en_bw_switch_status || WLAN_BW_SWITCH_20_TO_40 == pst_csi->en_bw_switch_status)
        {
            OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "dmac_handle_tbtt_chan_mgmt_ap, Switched to 20MHz at DTIM 0, [channel = %d, bandwidth = %d].",
                          pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);

            pst_csi->en_bw_switch_status = WLAN_BW_SWITCH_DONE;

            /* ����VAP�µ�"����ģʽ"Ӧ��Ϊ WLAN_BAND_WIDTH_20MHz */
            dmac_chan_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
        }
    }
}


oal_uint32  dmac_send_disasoc_misc_event(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx, oal_uint16 us_disasoc_reason)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;
    dmac_disasoc_misc_stru    st_disasoc_misc;

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_disasoc_misc_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                "{dmac_send_disasoc_misc_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_DMAC_MISC,
                            DMAC_MISC_SUB_TYPE_DISASOC,
                            WLAN_MEM_EVENT_SIZE1,
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_mac_vap->uc_chip_id,
                            pst_mac_vap->uc_device_id,
                            pst_mac_vap->uc_vap_id);

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_send_disasoc_misc_event::user_id=%d reason=%d}",
                    us_user_idx, us_disasoc_reason);

    st_disasoc_misc.en_disasoc_reason = us_disasoc_reason;
    st_disasoc_misc.us_user_idx       = us_user_idx;
    oal_memcopy(pst_event->auc_event_data, &st_disasoc_misc, OAL_SIZEOF(dmac_disasoc_misc_stru));

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_send_disasoc_misc_event::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_ROAM

#define ROAM_TRIGGER_COUNT_THRESHOLD           (5)
#define ROAM_TRIGGER_RSSI_NE80_DB              (-80)
#define ROAM_TRIGGER_RSSI_NE75_DB              (-75)
#define ROAM_TRIGGER_RSSI_NE70_DB              (-70)
#define ROAM_TRIGGER_INTERVAL_10S              (10 * 1000)
#define ROAM_TRIGGER_INTERVAL_15S              (15 * 1000)
#define ROAM_TRIGGER_INTERVAL_20S              (20 * 1000)

oal_uint32 dmac_sta_roam_trigger_init(dmac_vap_stru *pst_dmac_vap)
{
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap->st_roam_trigger.ul_cnt         = 0;
    pst_dmac_vap->st_roam_trigger.ul_rssi_ignore = 0;
    pst_dmac_vap->st_roam_trigger.ul_time_stamp  = 0;

    OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{dmac_sta_roam_trigger_init}");
    return OAL_SUCC;
}


oal_uint32 dmac_sta_roam_trigger_check(dmac_vap_stru *pst_dmac_vap)
{
    mac_device_stru          *pst_mac_device;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_to_dmac_device_stru  *pst_hal_device;
#endif
    frw_event_mem_stru       *pst_event_mem     = OAL_PTR_NULL;
    frw_event_stru           *pst_event         = OAL_PTR_NULL;
    oal_uint32                ul_ret            = OAL_SUCC;
    oal_uint32                ul_delta_time     = 0;
    oal_bool_enum             en_trigger_enable = OAL_FALSE;
    oal_int8                  c_trigger_rssi    = 0;
    oal_int8                  c_rssi_offset     = 0;
    oal_uint8                 uc_vap_id;
    oal_uint16                us_linkloss_threshold = 0;       /*  LinkLoss����  */

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 5G���Ƿ�Ҫ�������� */
    if (WLAN_BAND_5G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
        c_rssi_offset = 0;  //10
    }

    if ((pst_dmac_vap->st_roam_trigger.ul_rssi_ignore) ||
        (pst_dmac_vap->st_query_stats.ul_signal >= (ROAM_TRIGGER_RSSI_NE70_DB + c_rssi_offset)))
    {
        pst_dmac_vap->st_roam_trigger.ul_cnt = 0;
    }
    else
    {
        /* �������ɴ�rssiС������ʱ����һ������  */
        if ((pst_dmac_vap->st_roam_trigger.ul_cnt++ >= ROAM_TRIGGER_COUNT_THRESHOLD) &&
            (0== pst_dmac_vap->st_roam_trigger.ul_rssi_ignore))
        {
            pst_dmac_vap->st_roam_trigger.ul_cnt = 0;
            /* ���δ����¼���Ҫ�����ϱ���С��� *//*lint -e666*/
            ul_delta_time  = OAL_TIME_GET_RUNTIME(pst_dmac_vap->st_roam_trigger.ul_time_stamp, (oal_uint32)OAL_TIME_GET_STAMP_MS());/*lint +e666*/
            c_trigger_rssi = (oal_int8)pst_dmac_vap->st_query_stats.ul_signal;

            if ((c_trigger_rssi <= (ROAM_TRIGGER_RSSI_NE80_DB + c_rssi_offset)) &&
                (ul_delta_time >= ROAM_TRIGGER_INTERVAL_10S))
            {
                /* ��ǰAP���ź�ǿ��С�ڵ���-80������ɨ����10s */
                en_trigger_enable  = OAL_TRUE;
            }
            else if ((c_trigger_rssi <= (ROAM_TRIGGER_RSSI_NE75_DB + c_rssi_offset)) &&
                     (ul_delta_time >= ROAM_TRIGGER_INTERVAL_15S))
            {
                /* ��ǰAP���ź�ǿ��С�ڵ���-75������ɨ����15s */
                en_trigger_enable  = OAL_TRUE;
            }
            else if ((c_trigger_rssi <= (ROAM_TRIGGER_RSSI_NE70_DB + c_rssi_offset)) &&
                     (ul_delta_time >= ROAM_TRIGGER_INTERVAL_20S))
            {
                /* ��ǰAP���ź�ǿ��С�ڵ���-70������ɨ����20s */
                en_trigger_enable  = OAL_TRUE;
            }
        }
    }

    /* LINK LOSS��������1/2��3/4������ʱ����һ�����Σ�rssiΪ0��ʾǿ������  */
    us_linkloss_threshold = pst_dmac_vap->st_linkloss_info.us_linkloss_threshold;
    if ((pst_dmac_vap->st_linkloss_info.us_link_loss == (us_linkloss_threshold >> 1)) ||
        (pst_dmac_vap->st_linkloss_info.us_link_loss == (us_linkloss_threshold >> 1) + (us_linkloss_threshold >> 2)))
    {
        c_trigger_rssi     = 0;
        en_trigger_enable  = OAL_TRUE;
    }

    if (en_trigger_enable == OAL_FALSE)
    {
        return OAL_FAIL;
    }

    pst_mac_device  = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::pst_mac_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
     /* dbac������,ֱ��return */
    if ((OAL_TRUE == mac_is_dbac_running(pst_mac_device)))
    {
        OAM_WARNING_LOG1(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::ignor rssi[%d] for dbac is running.}", c_trigger_rssi);
        return OAL_FAIL;
    }
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::pst_hal_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* bt��ҵ���ʱ��ֱ��return */
    if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        /* Ŀǰֻ�����ֵ绰������ҵ������ҵ���ݲ������� */
        if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_a2dp ||
            pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_sco)
        {
            OAM_WARNING_LOG1(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::ignor rssi[%d] for bt is running.}", c_trigger_rssi);
            return OAL_FAIL;
        }
    }
#endif
    uc_vap_id      = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_disasoc_misc_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::pst_event_mem fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_DMAC_MISC,
                            DMAC_MISC_SUB_TYPE_ROAM_TRIGGER,
                            WLAN_MEM_EVENT_SIZE1,
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_dmac_vap->st_vap_base_info.uc_chip_id,
                            pst_dmac_vap->st_vap_base_info.uc_device_id,
                            uc_vap_id);

    oal_memcopy(pst_event->auc_event_data, &c_trigger_rssi, OAL_SIZEOF(oal_uint8));

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);

    pst_dmac_vap->st_roam_trigger.ul_time_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    OAM_INFO_LOG3(uc_vap_id, OAM_SF_ROAM, "{dmac_sta_roam_trigger_check::ROAM TRIGGER OCCURED, c_trigger_rssi = %d, ul_delta_time = %d, link_loss = %d.}", c_trigger_rssi, ul_delta_time, pst_dmac_vap->st_linkloss_info.us_link_loss);

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 �� �� ��  : dmac_LinkLoss_send_probe_req
 ��������  :  �Ǳ���ɨ��׶Σ�LinkLoss����������һ�룬׼����ʼ���͵���̽��֡�ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : zhongwen
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_linkloss_send_probe_req(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    mac_vap_stru       *pst_mac_vap;

    pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    /* ɨ�衢�״2040���ŵ�ʱ��linkloss������������,���Բ����ⷢ�͵���̽��֡ */
    if ((0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
        /* ���������ţ�׼��probe req֡��ssid��Ϣ */
        dmac_scan_send_probe_req_frame(pst_dmac_vap,
                                       pst_mac_vap->auc_bssid,
                                       (oal_int8 *)(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID));
    }
}
/*****************************************************************************
 �� �� ��  : dmac_vap_linkloss_incr
 ��������  : ��linkloss��������1
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : zhongwen
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_vap_linkloss_incr(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    /* ɨ�衢�״2040���ŵ�ʱ��linkloss������������ */
    if ((0 == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
        pst_dmac_vap->st_linkloss_info.us_link_loss++;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_vap_update_linkloss_threshold
 ��������  :  ����linkloss����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : zhongwen
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_vap_update_linkloss_threshold(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    oal_uint32                         ul_dot11BeaconPeriod;
    dmac_vap_linkloss_stru            *pst_linkloss_info;
    oal_uint16                         us_linkloss_threshold;
    oal_bool_enum_uint8                en_bt_on = OAL_FALSE;
    oal_bool_enum_uint8                en_dbac_running = OAL_FALSE;
    oal_bool_enum_uint8                en_far_distance = OAL_FALSE;
    oal_bool_enum_uint8                en_threshold_change_flag = OAL_FALSE;

    ul_dot11BeaconPeriod = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

    /* ��Чbeacon���(Ϊ0)��ǿ�а���beacon���Ϊ100ms����linkloss���� */
    if (0 == ul_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                "{dmac_vap_update_linkloss_threshold::pst_mib.ul_dot11BeaconPeriod[%d] is Abnormal, when STAUT_mode and UP_status!}", ul_dot11BeaconPeriod);
        ul_dot11BeaconPeriod = WLAN_BEACON_INTVAL_DEFAULT;
    }

    pst_linkloss_info = &(pst_dmac_vap->st_linkloss_info);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    en_bt_on = pst_dmac_vap->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on;
    /* ���bt���ظı� */
    if (pst_linkloss_info->en_old_bt_on != en_bt_on)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::bt change to [%d]!}",en_bt_on);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_bt_on = en_bt_on;
    }
#endif
    en_dbac_running = mac_is_dbac_running(pst_mac_device);
    if (pst_linkloss_info->en_old_dbac_runing != en_dbac_running)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::dbac_runing change to [%d]!}",en_dbac_running);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_dbac_runing = en_dbac_running;
    }

    en_far_distance = (pst_dmac_vap->st_query_stats.ul_signal < WLAN_FAR_DISTANCE_RSSI);
    if(pst_linkloss_info->en_old_far_distance != en_far_distance)
    {
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_far_distance = en_far_distance;
    }

    /* ���beacon���ڸı� */
    if (ul_dot11BeaconPeriod != pst_linkloss_info->ul_old_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::old_BeaconPeriod[%d], new_BeaconPeriod[%d]!}",
            pst_linkloss_info->ul_old_dot11BeaconPeriod,
            ul_dot11BeaconPeriod);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->ul_old_dot11BeaconPeriod = ul_dot11BeaconPeriod;
    }

    /* ״̬�޸ı䣬��������ˢ������ */
    if (OAL_TRUE != en_threshold_change_flag)
    {
        return;
    }

    /* �������޻�������beacon����ΪĬ������ʱ���Ż�Ϊ��λ�Ʒ�ʽ(Լ���� time*10>>8) */
    if (IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info))
    {
        /* ���� */
        if (WLAN_FAR_DISTANCE_RSSI <= pst_dmac_vap->st_query_stats.ul_signal)
        {
            us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(40)  : (oal_uint16)(4000 / ul_dot11BeaconPeriod); /* 4s in normal BeaconPeriod*/
        }
        else
        {
            us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(100)  :  (oal_uint16)(10000 / ul_dot11BeaconPeriod); /* 10s in normal BeaconPeriod*/
        }

    }
    else
    {
        us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(20)  :  (oal_uint16)(2000 / ul_dot11BeaconPeriod); /* 2s in normal BeaconPeriod*/
    }


    /* ���ݾ��������������ֵ */
    if (OAL_TRUE == en_dbac_running)
    {
        us_linkloss_threshold = (oal_uint16)(us_linkloss_threshold << 1); /* DBACģʽ�����޷�2�� */
    }

    if (OAL_TRUE == en_bt_on)
    {
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        us_linkloss_threshold = (oal_uint16)((us_linkloss_threshold << 1) + (us_linkloss_threshold >> 1)); /* ����ģʽ�����޷�2.5�� */
#endif
    }

    /* �쳣����:��linkloss���޹��ͣ������Ļ����¼����׳���linkloss���˴������������ֵ */
    if (WLAN_LINKLOSS_MIN_THRESHOLD > us_linkloss_threshold)
    {
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::The linkloss_threshold[%d]is too little that we have to change it to[%d],and now BeaconPeriod is[%d]!}",
            us_linkloss_threshold,
            WLAN_LINKLOSS_MIN_THRESHOLD,
            ul_dot11BeaconPeriod);
        us_linkloss_threshold = WLAN_LINKLOSS_MIN_THRESHOLD;
    }

    pst_linkloss_info->us_linkloss_threshold = us_linkloss_threshold;
}

OAL_STATIC void dmac_sta_tbtt_prior_linkloss_handler(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint16           us_linkloss_period;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {

        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                        "{dmac_sta_up_misc::Cannot find mac_dev,by vap.device_id[%d]} ",
                        pst_dmac_vap->st_vap_base_info.uc_device_id);
        return ;
    }

    dmac_vap_update_linkloss_threshold(pst_dmac_vap, pst_mac_device);
    dmac_vap_linkloss_incr(pst_dmac_vap, pst_mac_device);

#define LINKLOSS_DFT_PERIOD  10
    us_linkloss_period = (pst_dmac_vap->st_linkloss_info.us_link_loss % LINKLOSS_DFT_PERIOD);

    /* linkloss��������һ��,"��ÿ��16��tbtt����" or "linklos���޼���ֵС��16"��׼�����͵���̽��֡ */
    if ((pst_dmac_vap->st_linkloss_info.us_link_loss >= (pst_dmac_vap->st_linkloss_info.us_linkloss_threshold >> 1))&&
        ((0 == us_linkloss_period) || (pst_dmac_vap->st_linkloss_info.us_linkloss_threshold < LINKLOSS_DFT_PERIOD )))
    {
        dmac_linkloss_send_probe_req(pst_dmac_vap, pst_mac_device);
    }

    /*linklossÿͳ�ƴﵽ10�Σ��ϱ�һ��ά����Ϣ��ɨ������ŵ�ʱ�̲���ӡ*/
    if ((0 == us_linkloss_period) && (0 == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_para(pst_dmac_vap,OAL_FALSE);
#endif
    }
}
 OAL_STATIC void dmac_sta_up_misc(dmac_vap_stru *pst_dmac_vap)
 {

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    pst_dmac_vap->uc_beacon_miss_cnt++;
#endif

    dmac_sta_tbtt_prior_linkloss_handler(pst_dmac_vap);

#ifdef _PRE_WLAN_FEATURE_ROAM
    dmac_sta_roam_trigger_check(pst_dmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    dmac_handle_tbtt_chan_mgmt_sta(pst_dmac_vap);

    /* sta��ap��ʧ���ӳ������޴��� */
    if (DMAC_IS_LINKLOSS(pst_dmac_vap))
    {
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                        "{dmac_sta_up_misc::Oh no,LinkLoss!! BSSID[%02X:XX:XX:%02X:%02X:%02X]} ",
                        pst_dmac_vap->st_vap_base_info.auc_bssid[0],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[3],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[4],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[5]);
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_para(pst_dmac_vap,OAL_TRUE);
#endif
        dmac_vap_linkloss_clean(pst_dmac_vap);
        dmac_send_disasoc_misc_event(&(pst_dmac_vap->st_vap_base_info),pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id, DMAC_DISASOC_MISC_LINKLOSS);
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : dmac_tbtt_event_sta
 ��������  : sta tbtt�жϴ���, �׵�hmacȥ����
 �������  : pst_dmac_vap: DMAC VAP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_event_sta(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru  *pst_event;
    dmac_vap_stru   *pst_dmac_vap;

#ifdef _PRE_WLAN_CHIP_TEST
    if (1 == dmac_test_lpm_get_wow_en())
    {
         return;
    }
#endif

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dmac_vap = mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "dmac_tbtt_event_sta, pst_dmac_vap is null, vap id [%d].", pst_event->st_event_hdr.uc_vap_id);
        return;
    }

    if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        dmac_sta_up_misc(pst_dmac_vap);
    }
    else
    {
        FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(&(pst_event->st_event_hdr), DMAC_TBTT_EVENT_SUB_TYPE);

        /* �ַ��¼� */
        frw_event_dispatch_event(pst_event_mem);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_tbtt_event_ap
 ��������  : ap tbtt�жϴ���
 �������  : pst_dmac_vap: DMAC VAP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_event_ap(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                    uc_bcn_idx_for_soft;   /* �������beacon֡��� */
    oal_uint8                   *puc_bcn_buf;
    hal_beacon_tx_params_stru    st_beacon_tx_params;
    hal_tx_txop_alg_stru        *pst_tx_param;
    dmac_user_stru              *pst_dmac_multi_user;
    oal_uint32                   ul_ret;
    mac_device_stru             *pst_macdev;
    wlan_channel_band_enum_uint8 en_band;
    oal_uint8                    uc_bcn_chain_switch;
    oal_uint32                   ul_bcn_interval_temp;
#ifdef  _PRE_WLAN_FEATURE_PM
    hal_tx_txop_tx_power_stru    st_tx_power_temp;
    mac_pm_handler_stru          *pst_mac_pm_handle;
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
    oal_uint32                   ul_start_tsf;
    oal_uint32                   ul_scan_time;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_wifi_status_stru    *pst_hal_btcoex_wifi_status;
    oal_uint32 ul_beacon_count_new;
#endif
    if ((MAC_VAP_STATE_UP != pst_dmac_vap->st_vap_base_info.en_vap_state) &&
        (MAC_VAP_STATE_PAUSE != pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        //OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::vap state=%d.}", pst_dmac_vap->st_vap_base_info.en_vap_state);
        return;
    }

    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON,
                       "{dmac_tbtt_event_ap::dev is null!}");
        return;
    }
    /* �����������beacon֡��� */
    uc_bcn_idx_for_soft = (DMAC_VAP_BEACON_BUFFER_BUTT == (pst_dmac_vap->uc_beacon_idx + 1)) ? DMAC_VAP_BEACON_BUFFER1 : DMAC_VAP_BEACON_BUFFER2;

    /* ���Ҫ���µ�beacon֡ */
    puc_bcn_buf = pst_dmac_vap->pauc_beacon_buffer[uc_bcn_idx_for_soft];

    if(puc_bcn_buf == NULL)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::beacon buf = NULL. uc_bcn_idx_for_soft=%d.}\r\n", uc_bcn_idx_for_soft);
        return;
    }
    /* ����˴�tbtt�ж϶�Ӧ����DTIM���ڣ�����Ҫ�����鲥/�㲥���ܶ����еĻ���֡ */
//    if (0 == pst_dmac_vap->uc_dtim_count)
    if ((0 == pst_dmac_vap->uc_dtim_count) && (OAL_TRUE == pst_dmac_vap->en_dtim_ctrl_bit0))
    {
        pst_dmac_multi_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
        if (OAL_PTR_NULL == pst_dmac_multi_user)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::get multi user[%d] fail.}", pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
            return;
        }
		/* �����ǰPSMδ����ʱ����Ľ��ܶ���ˢ������ */
        dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_multi_user);
    }

    if((WITP_TX_CHAIN_DOUBLE == pst_macdev->uc_tx_chain)&&
        (OAL_TRUE == pst_dmac_vap->en_beacon_chain_active))
    {
        uc_bcn_chain_switch = 1;
    }
    else
    {
        uc_bcn_chain_switch = 0;
    }

    /* �ŵ����� */
    dmac_handle_tbtt_chan_mgmt_ap(pst_dmac_vap);

    en_band = pst_dmac_vap->st_vap_base_info.st_channel.en_band;
    pst_tx_param =&(pst_dmac_vap->ast_tx_mgmt_bmcast[en_band]);
    pst_tx_param->ast_per_rate[0].rate_bit_stru.bit_reserve = 0;

    ul_bcn_interval_temp = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

#ifdef  _PRE_WLAN_FEATURE_PM
    /*��������ֵ,������������ָ�*/
    st_tx_power_temp     = pst_tx_param->st_tx_power;
    pst_mac_pm_handle    = (mac_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if(PWR_SAVE_STATE_IDLE == dmac_pm_vap_current_state((oal_void *)pst_dmac_vap))
    {
        if(WITP_TX_CHAIN_DOUBLE == pst_macdev->uc_tx_chain)
        {
            uc_bcn_chain_switch  = 1;
        }

        #ifdef _PRE_WLAN_FEATURE_DBAC
        if (!mac_is_dbac_enabled(mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id)))
        {
            // DBACʹ��ʱ,beacon��������
            pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = WLAN_BEACON_INTVAL_IDLE;
        }
        #endif

        oal_memcopy((oal_void*)&(pst_tx_param->st_tx_power),(oal_void*)&(pst_mac_pm_handle->ul_idle_beacon_txpower),4);

    }

#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    if (1 == pst_dmac_vap->uc_p2pgo_scan_beacon_cnt)
    {
        pst_dmac_vap->uc_p2pgo_scan_beacon_cnt = 0;

        dmac_beacon_set_p2p_noa(&pst_dmac_vap->st_vap_base_info,0,0,0,0);

        /* ��һ����ʱ������ʱ�����ں�ʼ���ŵ�ɨ�� */
         FRW_TIMER_CREATE_TIMER(&pst_macdev->st_go_scan_timer,
                                   dmac_scan_after_p2pgo_send_noa,
                                   DMAC_SCAN_P2PGO_SEND_BEACON_TIME,
                                   pst_dmac_vap,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_macdev->ul_core_id);
        OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "start after_p2pgo_send_noa timer");
    }
    else if (2 == pst_dmac_vap->uc_p2pgo_scan_beacon_cnt)
    {
        pst_dmac_vap->uc_p2pgo_scan_beacon_cnt--;

        /* GO�ı���ɨ�裬����Beacon�е�NoA���� */
        hal_vap_tsf_get_32bit(pst_dmac_vap->pst_hal_vap, &ul_start_tsf);

        ul_start_tsf += ul_bcn_interval_temp<<10;   /* �˴θ��µ�Beacon֡����һ��TBTT���� */

        ul_scan_time = (pst_dmac_vap->us_p2pgo_scan_time)<<10;
        dmac_beacon_set_p2p_noa(&pst_dmac_vap->st_vap_base_info,
                                ul_start_tsf,
                                ul_scan_time,
                                ul_scan_time, 1);
        OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "GO has bg-scan, set noa. start_tsf:%d, scan_time:%d",
                                ul_start_tsf, ul_scan_time);
    }
#endif

    /* ����beacon֡ */
    dmac_encap_beacon(pst_dmac_vap, puc_bcn_buf, &(pst_dmac_vap->us_beacon_len));

    /* �����µ�beacon֡д��Ӳ��beacon֡�Ĵ��� */
    /* ��д����Beacon֡���� */
    st_beacon_tx_params.pst_tx_param = pst_tx_param;
    st_beacon_tx_params.ul_pkt_ptr   = (oal_uint32)puc_bcn_buf;
    st_beacon_tx_params.us_pkt_len   = pst_dmac_vap->us_beacon_len;

    /* �ж��Ƿ�����˫·�������� */
    if(1 == uc_bcn_chain_switch)
    {
        /* ��һ��beacon֡��ͨ��0���ͣ��ڶ���beacon֡��ͨ��1���� */
        if(pst_dmac_vap->uc_beacon_idx == DMAC_VAP_BEACON_BUFFER1)
        {
            //pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
            st_beacon_tx_params.ul_tx_chain_mask= 0x1;
        }
        //pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 2;
        st_beacon_tx_params.ul_tx_chain_mask = 0x2;
    }
    else
    {
        if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
        {
            st_beacon_tx_params.ul_tx_chain_mask   = 0x1;
        }
        else
        {
            st_beacon_tx_params.ul_tx_chain_mask   = pst_dmac_vap->uc_vap_tx_chain;
        }
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if (pst_macdev->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_page)
    {
        hal_btcoex_update_ap_beacon_count(&ul_beacon_count_new);
        pst_hal_btcoex_wifi_status = &(pst_macdev->pst_device_stru->st_btcoex_wifi_status);

        /* ÿ5��beacon����ʧ���ϱ�һ��BEACON MISS�жϣ������ڷ�����5��beacon�󣬼�����1 */
        if (ul_beacon_count_new - pst_hal_btcoex_wifi_status->ul_ap_beacon_count == 5)
        {
            pst_hal_btcoex_wifi_status->ul_ap_beacon_count = ul_beacon_count_new;
            pst_hal_btcoex_wifi_status->uc_ap_beacon_miss = OAL_SUB(pst_hal_btcoex_wifi_status->uc_ap_beacon_miss, 1);
        }

        /* �ﵽ30��beacon miss������occupied */
        if (pst_hal_btcoex_wifi_status->uc_ap_beacon_miss > 5)
        {
            hal_set_btcoex_occupied_period(10000);  // 10ms
        }
    }

#endif

    /* HAL����Beacon֡�ӿ� */
    hal_vap_send_beacon_pkt(pst_dmac_vap->pst_hal_vap, &st_beacon_tx_params);

    ul_ret = oam_report_beacon(puc_bcn_buf, MAC_80211_FRAME_LEN,
                               puc_bcn_buf + MAC_80211_FRAME_LEN,
                               pst_dmac_vap->us_beacon_len,  OAM_OTA_FRAME_DIRECTION_TYPE_TX);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::oam_report_beacon return err: 0x%x.}\r\n", ul_ret);
    }

#ifdef _PRE_WLAN_DFT_STAT
    /* ����beacon֡��Ŀͳ�� */
    DMAC_DFT_MGMT_STAT_INCR(pst_macdev->st_mgmt_stat.aul_tx_mgmt_soft[WLAN_BEACON]);
#endif
    /* ��������beacon֡ */
    pst_dmac_vap->uc_beacon_idx = uc_bcn_idx_for_soft;

#ifdef  _PRE_WLAN_FEATURE_PM
/*�ָ�����ֵ*/
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = ul_bcn_interval_temp;
    pst_tx_param->st_tx_power = st_tx_power_temp;
#endif

}


#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_linkloss_occupied_process(dmac_vap_stru *pst_dmac_vap)
{
	if (pst_dmac_vap->st_linkloss_info.us_link_loss > COEX_LINKLOSS_OCCUP_TIMES)
	{
        hal_set_btcoex_occupied_period(COEX_LINKLOSS_OCCUP_PERIOD);
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_COEX,
                        "{dmac_tbtt_event_handler::occupied time == [%d], linkloss == [%d].}",
                        COEX_LINKLOSS_OCCUP_PERIOD, pst_dmac_vap->st_linkloss_info.us_link_loss);
	}
}
#endif


/*****************************************************************************
 �� �� ��  : dmac_tbtt_event_handler
 ��������  : TBTT�ж��¼�������
 �������  : pst_event_mem: ָ���¼��ڴ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tbtt_event_handler(frw_event_mem_stru *pst_event_mem)
{
    dmac_vap_stru               *pst_dmac_vap;
    frw_event_stru              *pst_event;
    mac_device_stru             *pst_mac_device;
	hal_error_state_stru         st_err_state;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_tbtt_exception_handler(pst_dmac_vap);

	pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_P2P
        if ((IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
            (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
        {
            dmac_p2p_oppps_ctwindow_start_event(pst_dmac_vap);
        }
#endif
        dmac_tbtt_event_ap(pst_dmac_vap);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* STA��pspoll�͹��Ĵ��� */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_psm_process_tbtt_sta(pst_dmac_vap, pst_mac_device);
#endif
#if (!defined(HI1102_EDA))
        dmac_tbtt_event_sta(pst_event_mem);
#endif

    }
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_linkloss_occupied_process(pst_dmac_vap);
#endif
    /* ���mac�������������֤ÿһ��tbtt��϶�У���ദ��Ĵ����� */
    /* ����vapʱ���������ݲ��������*/
    dmac_mac_error_cnt_clr(pst_mac_device);
    st_err_state.ul_error1_val = 0xffffffff;
    st_err_state.ul_error2_val = 0xffffffdf;
    hal_unmask_mac_error_init_status(pst_dmac_vap->pst_hal_device, &st_err_state);

#if 0
    /* 1102оƬ���ԣ���ӡ����tsf��״̬ */
    if (pst_dmac_vap->pst_hal_vap->uc_vap_id == 4)
    {
        oal_uint8             i;
        hal_to_dmac_vap_stru *pst_hal_vap;
        oal_uint32            ul_tsf;

        uc_cnt++;

        if (uc_cnt > 10)
        {
            uc_cnt = 0;

            for (i = 0; i < 2; i++)
            {
                hal_get_hal_vap(pst_dmac_vap->pst_hal_device, i, &pst_hal_vap);
                hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);

                OAM_INFO_LOG2(0, OAM_SF_DBAC, "hal_vap_id:%d, tsf:%d", i, ul_tsf);
            }

            for (i = 4; i < 7; i++)
            {
                hal_get_hal_vap(pst_dmac_vap->pst_hal_device, i, &pst_hal_vap);
                hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);

                OAM_INFO_LOG2(0, OAM_SF_DBAC, "hal_vap_id:%d, tsf:%d", i, ul_tsf);
            }
        }
    }
#endif

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : dmac_beacon_set_p2p_noa
 ��������  : ����beacon֡�е�p2p ie noa����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_beacon_set_p2p_noa(
                mac_vap_stru           *pst_mac_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count)
{
    dmac_vap_stru              *pst_dmac_vap;
    /*������ܲ���������encap beacon,probe response*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_dmac_vap->st_p2p_noa_param.uc_count = uc_count;
    pst_dmac_vap->st_p2p_noa_param.ul_duration = ul_duration;
    pst_dmac_vap->st_p2p_noa_param.ul_interval = ul_interval;
    pst_dmac_vap->st_p2p_noa_param.ul_start_time = ul_start_tsf;
    return OAL_SUCC;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_beacon_set_p2p_noa);
/*lint +e578*//*lint +e19*/

#endif
#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 �� �� ��  : dmac_sta_test_info_dump
 ��������  : �����ڲ��ԣ�ģ��host sleep����
 �������  : uc_host_sleep
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��3��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
void dmac_sta_test_info_dump(mac_vap_stru *pst_mac_vap)
{
    mac_opmode_notify_stru *pst_opmode;

    OAL_IO_PRINT("uc_test_flag=%d\r\n", g_beacon_offload_test.uc_test_flag);
    OAL_IO_PRINT("uc_host_sleep=%d\r\n", g_beacon_offload_test.uc_host_sleep);
    OAL_IO_PRINT("uc_opmode_in_beacon=%d\r\n", g_beacon_offload_test.uc_opmode_in_beacon);
    OAL_IO_PRINT("uc_opmode=%d\r\n", g_beacon_offload_test.uc_opmode);

    pst_opmode = (mac_opmode_notify_stru*)&g_beacon_offload_test.uc_opmode;
    OAL_IO_PRINT("bit_channel_width=%d bit_rx_nss=%d bit_rx_nss_type=%d\r\n",
            pst_opmode->bit_channel_width, pst_opmode->bit_rx_nss, pst_opmode->bit_rx_nss_type);
    OAL_IO_PRINT("uc_csa_in_beacon=%d\r\n", g_beacon_offload_test.uc_csa_in_beacon);
    OAL_IO_PRINT("uc_announced_channel=%d\r\n", g_beacon_offload_test.uc_announced_channel);
    OAL_IO_PRINT("uc_switch_cnt=%d\r\n", g_beacon_offload_test.uc_switch_cnt);
    OAL_IO_PRINT("wmm in beacon=%d\r\n", pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented);
    OAL_IO_PRINT("wmm cnt=%d\r\n", pst_mac_vap->uc_wmm_params_update_count);
}


/*****************************************************************************
 �� �� ��  : dmac_sta_host_force_sleep
 ��������  : �����ڲ��ԣ�ģ��host sleep����
 �������  : uc_host_sleep
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��3��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
void dmac_sta_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint8 *uc_param)
{
    if (!uc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRAME_FILTER, "dmac_sta_beacon_offload_test::uc_param null");
        return;
    }

    OAL_IO_PRINT("param[0]=%d param[1]=%d param[2]=%d param[3]=%d\r\n",
                uc_param[0], uc_param[1], uc_param[2], uc_param[3]);
    switch (uc_param[0])
    {
    case 0: //�򿪣��رղ���
        g_beacon_offload_test.uc_test_flag = uc_param[1];
        if (1 == uc_param[1])
        {
            oal_memset(&g_beacon_offload_test, 0, OAL_SIZEOF(g_beacon_offload_test));
            g_beacon_offload_test.uc_test_flag = uc_param[1];
            g_beacon_offload_test.uc_host_sleep = 0;
            g_beacon_offload_test.uc_opmode_in_beacon = 0;
            g_beacon_offload_test.uc_opmode = 0;
            g_beacon_offload_test.uc_csa_in_beacon = pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn;
            g_beacon_offload_test.uc_announced_channel = pst_mac_vap->st_ch_switch_info.uc_announced_channel;
            g_beacon_offload_test.uc_switch_cnt = pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt;
        }
        break;

    case 1: //�ֶ�ģ��host sleep
        g_beacon_offload_test.uc_host_sleep = uc_param[1];
        break;

    case 2: //����opmode ie
        g_beacon_offload_test.uc_opmode_in_beacon = uc_param[1];
        g_beacon_offload_test.uc_opmode = uc_param[2];
        break;

    case 3: //����csa ie
        g_beacon_offload_test.uc_csa_in_beacon = uc_param[1];
        g_beacon_offload_test.uc_announced_channel = uc_param[2];
        g_beacon_offload_test.uc_switch_cnt = uc_param[3];
        break;

    case 4:
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = uc_param[1];
        pst_mac_vap->uc_wmm_params_update_count = uc_param[2];
        break;

    default:
        OAL_IO_PRINT("wrong type\r\n");
        break;
    }

    dmac_sta_test_info_dump(pst_mac_vap);
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_sta_opmode_is_changed
 ��������  : �ж�beacon֡��opmode ie�������һ��beacon֡�Ƿ����ı�
 �������  : pst_mac_vap
             puc_frame_body
             us_frame_len
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_bool_enum_uint8 dmac_sta_host_is_sleep(void)
{
#ifdef _PRE_WLAN_CHIP_TEST
    if (g_beacon_offload_test.uc_test_flag && g_beacon_offload_test.uc_host_sleep)
    {
        return OAL_TRUE;
    }
#endif
    //l00311403 ����zourong�Ľӿ�
    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_sta_opmode_is_changed
 ��������  : �ж�beacon֡��opmode ie�������һ��beacon֡�Ƿ����ı�
 �������  : pst_mac_vap
             puc_frame_body
             us_frame_len
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_opmode_is_changed(
                mac_vap_stru  *pst_mac_vap,
                mac_user_stru *pst_mac_user,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8              uc_modify_flag = OAL_FALSE;
#if defined _PRE_WLAN_FEATURE_OPMODE_NOTIFY || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
    mac_opmode_notify_stru *pst_opmode_notify;
    const oal_uint8        *puc_opmode_ie;

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        return OAL_FALSE;
    }

    puc_opmode_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL == puc_opmode_ie)
    {
        return OAL_FALSE;
    }

    pst_opmode_notify = (mac_opmode_notify_stru *)(puc_opmode_ie + MAC_IE_HDR_LEN);

    if ( (1 == pst_opmode_notify->bit_rx_nss_type) &&
         (pst_opmode_notify->bit_rx_nss != pst_mac_user->uc_avail_bf_num_spatial_stream) )
    {
        mac_user_avail_bf_num_spatial_stream(pst_mac_user, pst_opmode_notify->bit_rx_nss);
        uc_modify_flag = OAL_TRUE;
    }

    if (pst_opmode_notify->bit_channel_width != pst_mac_user->en_avail_bandwidth)
    {
        mac_user_set_bandwidth_info(pst_mac_user, pst_opmode_notify->bit_channel_width, pst_mac_user->en_cur_bandwidth);
        uc_modify_flag = OAL_TRUE;
    }

    if ( pst_mac_user->uc_avail_num_spatial_stream !=
         OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_opmode_notify->bit_rx_nss))
    {
        mac_user_set_avail_num_spatial_stream(pst_mac_user, OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_opmode_notify->bit_rx_nss));
        uc_modify_flag = OAL_TRUE;
    }

    if (OAL_TRUE == uc_modify_flag)
    {
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                "{dmac_sta_opmode_is_changed::opmode changed=%d bit_channel_width=%d bit_rx_nss=%d bit_rx_nss_type=%d}\r\n",
                uc_modify_flag, pst_opmode_notify->bit_channel_width, pst_opmode_notify->bit_rx_nss,
                pst_opmode_notify->bit_rx_nss_type);
    }
#endif

    return uc_modify_flag;
}

/*****************************************************************************
 �� �� ��  : dmac_sta_csa_is_changed
 ��������  : �ж�beacon֡��Channel Switch Annoucement ie�������һ��beacon֡��
             �����ı�
 �������  : pst_mac_vap
             puc_frame_body
             us_frame_len
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_csa_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    const oal_uint8   *puc_csa_ie;
    oal_uint8         uc_new_chan = 0xff; /*��CSA IE������ʱ*/
    oal_uint8         uc_old_chan;
    oal_uint8         uc_modify_flag = OAL_FALSE;

    puc_csa_ie = mac_find_ie(MAC_EID_CHANSWITCHANN, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL != puc_csa_ie)
    {
        uc_new_chan   = puc_csa_ie[MAC_IE_HDR_LEN + 1];
    }
    else
    {
        puc_csa_ie = mac_find_ie(MAC_EID_EXTCHANSWITCHANN, puc_frame_body, us_frame_len);
        if (OAL_PTR_NULL != puc_csa_ie)
        {
            uc_new_chan   = puc_csa_ie[MAC_IE_HDR_LEN + 2];
        }
        else
        {
            return OAL_FALSE;
        }
    }

    uc_old_chan = pst_mac_vap->st_ch_switch_info.uc_new_channel;
    if (uc_old_chan != uc_new_chan)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_channel = uc_new_chan;
        uc_modify_flag = OAL_TRUE;
    }

    if (uc_modify_flag)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                        "dmac_sta_csa_is_changed::csa changed=%d", uc_modify_flag);
    }

    return uc_modify_flag;
}


/*****************************************************************************
 �� �� ��  : dmac_sta_edca_is_changed
 ��������  : �ж�beacon֡��EDCA ie�������һ��beacon֡�Ƿ����ı�
 �������  : pst_mac_vap
             puc_frame_body
             us_frame_len
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��26��
    ��    ��   : wanran
    �޸�����   : ֻ�ڶ���¸���dmac��count
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_edca_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8         uc_param_set_cnt;
    oal_uint8         uc_modify_flag = OAL_FALSE;
    const oal_uint8   *puc_edca_ie;

    puc_edca_ie = mac_find_ie(MAC_EID_WMM, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL == puc_edca_ie)
    {
        return OAL_FALSE;
    }

    if (OAL_TRUE == mac_is_wmm_ie((oal_uint8*)puc_edca_ie))
    {
        uc_param_set_cnt = puc_edca_ie[DMAC_WMM_QOS_PARAMS_HDR_LEN] & 0x0F;

        if (uc_param_set_cnt != pst_mac_vap->uc_wmm_params_update_count)
        {
            OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                    "dmac_sta_edca_is_changed::edca is changed=%d, old_cnt=%d new_cnt=%d\r\n",
                    uc_modify_flag, pst_mac_vap->uc_wmm_params_update_count, uc_param_set_cnt);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            mac_vap_set_wmm_params_update_count(pst_mac_vap, uc_param_set_cnt);
#endif
            uc_modify_flag = OAL_TRUE;
        }
    }

    return uc_modify_flag;
}


OAL_STATIC oal_bool_enum_uint8 dmac_sta_channel_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8        uc_channel;
    oal_uint8        uc_modify_flag;
    oal_uint8       *puc_dsss_ie;

    //puc_dsss_ie = mac_get_dsss_param_ie(puc_frame_body, us_frame_len, 0);
    puc_dsss_ie = mac_find_ie(MAC_EID_DSPARMS, puc_frame_body, us_frame_len);
    if (OAL_PTR_NULL == puc_dsss_ie)
    {
        return OAL_FALSE;
    }

    uc_channel = puc_dsss_ie[MAC_IE_HDR_LEN];

    if (uc_channel != pst_mac_vap->st_channel.uc_chan_number)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                "dmac_sta_channel_is_changed::AP channel is changed, old_channel=%d new_channel=%d\r\n",
                pst_mac_vap->st_channel.uc_chan_number, uc_channel);
        uc_modify_flag = OAL_TRUE;
    }
    else
    {
        uc_modify_flag = OAL_FALSE;
    }

    return uc_modify_flag;
}


oal_void dmac_sta_update_slottime(mac_vap_stru* pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_payload, oal_uint16 us_msg_len)
{
    dmac_user_stru             *pst_dmac_user;
    mac_erp_params_stru        *pst_erp_ie;
    const oal_uint8            *puc_erp_ie;
    hal_to_dmac_device_stru    *pst_hal_device;

    pst_dmac_user = (dmac_user_stru *)pst_mac_user;

    /* ����non_erp��Ϣ,staģʽ�£�����BSS���Ƿ���erpվ�����Ϣ */
    puc_erp_ie = mac_find_ie(MAC_EID_ERP, puc_payload, us_msg_len);
    if (OAL_PTR_NULL == puc_erp_ie)
    {
        return;
    }

    /* NON_ERPվ�����ʱ����slottime���� */
    pst_erp_ie = (mac_erp_params_stru*)&(puc_erp_ie[MAC_IE_HDR_LEN]);
    if (pst_dmac_user->bit_non_erp_exist != pst_erp_ie->bit_non_erp)
    {
        pst_dmac_user->bit_non_erp_exist = pst_erp_ie->bit_non_erp;

        hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
        if (OAL_PTR_NULL == pst_hal_device)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_sta_update_slottime::hal dev null, fail to update slot time.}");
            return;
        }

        /* ��NON_ERPվ��ʱ��ʹ��short slottime�����ݣ�����ʹ��long slottime */
        hal_cfg_slottime_type(pst_hal_device, pst_erp_ie->bit_non_erp);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_sta_up_rx_beacon
 ��������  : �ж�beacon֡�Ƿ���Ҫ�ϱ�HMAC
 �������  : pst_dmac_vap
             pst_netbuf
 �������  : pen_go_on
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_sta_up_rx_beacon(
                dmac_vap_stru   *pst_dmac_vap,
                oal_netbuf_stru *pst_netbuf,
                oal_uint8       *pen_go_on)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    mac_vap_stru               *pst_mac_vap;
    mac_user_stru              *pst_mac_user;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_payload;
    oal_uint16                  us_ie_offset;
    oal_uint16                  us_msg_len;
    oal_uint32                  ul_ret;

    *pen_go_on = OAL_FALSE;

    pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    pst_rx_ctl     = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    pst_rx_info    = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));
    puc_payload    = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info, pst_netbuf);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    us_msg_len     = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /*֡�峤��*/
#else
    us_msg_len     = pst_rx_info->us_frame_len - pst_rx_info->uc_mac_header_len; /*֡�峤��*/
#endif
    /* ��������bss��Beacon�������� */
    ul_ret = oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_frame_hdr->auc_address3);
    if(0 != ul_ret)
    {
        return OAL_SUCC;
    }

    dmac_vap_linkloss_clean(pst_dmac_vap);

    /* �ɹ����յ�beacon, beacon timeout��ʱ�ļ������� */
    pst_dmac_vap->bit_beacon_timeout_times = 0;

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    pst_dmac_vap->uc_beacon_miss_cnt = 0;
#endif

    /* ���host�಻�Ǵ�����˯״̬��beaconֱ���ϱ�HMAC */
#ifdef _PRE_WIFI_DMT
    *pen_go_on = OAL_TRUE;
    return OAL_SUCC;
#else

    us_ie_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    puc_payload += us_ie_offset;
    us_msg_len  -= us_ie_offset;
    if (OAL_TRUE == dmac_sta_channel_is_changed(pst_mac_vap, puc_payload, us_msg_len))
    {
        ul_ret = dmac_send_disasoc_misc_event(pst_mac_vap, pst_mac_vap->uc_assoc_vap_id, DMAC_DISASOC_MISC_CHANNEL_MISMATCH);
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctl->st_rx_info)));
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                       "{dmac_sta_up_rx_beacon::pst_mac_user null}");
        return OAL_FALSE;
    }

    /* ��non_erpվ��ʱʹ��long slottime */
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        dmac_sta_update_slottime(pst_mac_vap, pst_mac_user, puc_payload, us_msg_len);
    }

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE)/*OAL_FALSE == PM_WLAN_IsHostSleep()*/)
    {
        *pen_go_on = OAL_TRUE;
        return OAL_SUCC;
    }
#endif
#endif

    if ( (OAL_TRUE == dmac_sta_opmode_is_changed(pst_mac_vap, pst_mac_user, puc_payload, us_msg_len)) ||
          (OAL_TRUE == dmac_sta_csa_is_changed(pst_mac_vap, puc_payload, us_msg_len)) ||
          (OAL_TRUE == dmac_sta_edca_is_changed(pst_mac_vap, puc_payload, us_msg_len)))
    {
        *pen_go_on = OAL_TRUE;
    }

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
    //                "dmac_sta_up_rx_beacon::pen_go_on=%d", *pen_go_on);

    return OAL_SUCC;
}
oal_uint32  dmac_beacon_timeout_event_hander(frw_event_mem_stru *pst_event_mem)
{
#ifdef _PRE_WLAN_FEATURE_STA_PM
    dmac_vap_stru               *pst_dmac_vap;
    frw_event_stru              *pst_event;
    mac_device_stru             *pst_mac_device;
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_beacon_timeout_event_hander:event is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_beacon_timeout_event_hander:vap is null }");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_device || OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_ERROR_LOG2(0, OAM_SF_WIFI_BEACON, "{beacon timeout has null point: mac_device:%p sta_pm_handle:%p.}",pst_mac_device,pst_mac_sta_pm_handle);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����beacon��ʱ���� */
    pst_dmac_vap->bit_beacon_timeout_times++;

    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        /* ����beacon��ʱ���� */
        pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BEACON_TIMEOUT_CNT]++;
    }

    if(pst_mac_sta_pm_handle->ul_psm_pkt_cnt || pst_mac_device->ul_rx_rate > RX_DATA_RATE)
    {
        return OAL_SUCC;
    }

    /* �͹���ģʽ�²Ż���beacon timeout ˯�� */
    if (WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == (mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))))
    {
        /* ����beacon��ʱ������ͶƱ˯�ļ��� */
        pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BCN_TOUT_SLEEP]++;
        pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_BEACON_TIMEOUT, 0, OAL_PTR_NULL);
    }
#endif

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_TSF_SYNC

oal_void dmac_sync_tsf_by_bcn(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint16                          us_beacon_interval         = 0;
    oal_uint32                          ul_beacon_timestamp_low    = 0;
    oal_uint64                          ul_beacon_timestamp_high   = 0;
    oal_uint64                          ul_beacon_timestamp        = 0;
    oal_uint8                           *puc_payload			   = OAL_PTR_NULL;

    if (pst_dmac_vap->uc_beacon_miss_cnt != 0)
    {
        pst_dmac_vap->uc_beacon_miss_cnt--;  /* dec after the beacon has been received */
    }

    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    /*get the timestamp and beacon interval*/
    ul_beacon_timestamp_low  = puc_payload[0];
    ul_beacon_timestamp_low |= (puc_payload[1] << 8);
    ul_beacon_timestamp_low |= (puc_payload[2] << 16);
    ul_beacon_timestamp_low |= (puc_payload[3] << 24);

    ul_beacon_timestamp_high  =  puc_payload[4];
    ul_beacon_timestamp_high |= (puc_payload[5] << 8);
    ul_beacon_timestamp_high |= (puc_payload[6] << 16);
    /*lint -e647*/
    ul_beacon_timestamp_high |= (puc_payload[7] << 24);
    /*lint +e647*/

    /* ����keep alive��ʱ֮�� */
    //g_stKeepAliveTime.ulLow  = beacon_timestamp_low;
    //g_stKeepAliveTime.ulHigh = beacon_timestamp_high;

    ul_beacon_timestamp  = ul_beacon_timestamp_low;

    /*lint -e647*/
    ul_beacon_timestamp |= (ul_beacon_timestamp_high << 32);
    /*lint +e647*/

    us_beacon_interval   = puc_payload[MAC_TIME_STAMP_LEN];
    us_beacon_interval  |= (puc_payload[MAC_TIME_STAMP_LEN + 1] << 8);


    if (0 != pst_dmac_vap->uc_beacon_miss_cnt)
    {

        //OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_sync_tsf_by_bcn::beacon miss cnt:[%d]",pst_dmac_vap->uc_beacon_miss_cnt);
        /*if beacon is missed,then clear saved*/
        pst_dmac_vap->ul_old_beacon_timestamp = 0;
        pst_dmac_vap->uc_beacon_miss_cnt = 0;
    }
    else if ((0 == pst_dmac_vap->uc_beacon_miss_cnt) && (0 == pst_dmac_vap->ul_old_beacon_timestamp))
    {
        /*saved the first timestamp*/
        pst_dmac_vap->ul_old_beacon_timestamp = ul_beacon_timestamp;
    }
    else if ((0 == pst_dmac_vap->uc_beacon_miss_cnt) && (0 != pst_dmac_vap->ul_old_beacon_timestamp))
    {
        /* cal the SyncTsfValue after receive the second beacon beacon֡���ж�������Ҫ����5ms���� */
        if (((oal_uint64)((ul_beacon_timestamp >> 10) - (pst_dmac_vap->ul_old_beacon_timestamp >> 10))) < (oal_uint64)(us_beacon_interval - 5))
        {
            pst_dmac_vap->us_sync_tsf_value = us_beacon_interval - (oal_uint16)((oal_uint64)((ul_beacon_timestamp >> 10) - ((pst_dmac_vap->ul_old_beacon_timestamp) >> 10))) + 70;
            OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_sync_tsf_by_bcn::sync value:[%d],beacon interval:[%d],\
                                         new time:[%lu],old time:[%lu]}",pst_dmac_vap->us_sync_tsf_value,us_beacon_interval,(ul_beacon_timestamp),((pst_dmac_vap->ul_old_beacon_timestamp)));

        }
        else
        {
            pst_dmac_vap->us_sync_tsf_value = 0;
        }

        OAM_INFO_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_sync_tsf_by_bcn::beacon interval:[%d],\
                                     new time:[%lu],old time:[%lu]}",us_beacon_interval,ul_beacon_timestamp,pst_dmac_vap->ul_old_beacon_timestamp);

        /*clear after fix once*/
        pst_dmac_vap->ul_old_beacon_timestamp  = ul_beacon_timestamp;
    }
}
#endif /* TSF_SYNC_OPT */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

