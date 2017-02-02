


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_rx_filter.h"
#include "dmac_vap.h"
#include "dmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RX_FILTER_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_set_rx_filter_value
 ��������  : dmac����RX Filterֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_set_rx_filter_value(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                         *pst_event;
    frw_event_hdr_stru                     *pst_event_hdr;
    mac_device_stru                        *pst_device;
    oal_uint32                             *pul_rx_filter_value;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pul_rx_filter_value     = (oal_uint32 *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_set_rx_filter_value::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_set_rx_filter(pst_device->pst_device_stru,*pul_rx_filter_value);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_calc_up_ap_num
 ��������  : 
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��16��
    ��    ��   : S00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_calc_up_ap_num(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;
    oal_uint8                      ul_up_ap_num = 0;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_calc_up_ap_num::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (MAC_VAP_STATE_INIT != pst_vap->en_vap_state)
        {
            ul_up_ap_num++;
        }
    }
    return ul_up_ap_num;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

