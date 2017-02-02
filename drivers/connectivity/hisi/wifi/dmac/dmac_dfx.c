


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "frw_task.h"

#include "wlan_spec.h"

#include "hal_ext_if.h"

#include "mac_vap.h"
#include "mac_resource.h"
#include "dmac_vap.h"
#include "dmac_dfx.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DFX_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
dmac_dft_stru       g_st_dmac_dft_info;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
oal_int32    g_l_proxysta_feature = 0;
#endif
oal_uint16   g_us_wlan_assoc_user_max_num     = WLAN_ASSOC_USER_MAX_NUM_LIMIT;     /* �����û��������� Root APģʽ��Ϊ32��,Repeaterģʽ����15�� */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* ����WL_L2_DRAM��С���ƣ�Ŀǰ��ʱ����2��ҵ��vap�������񿪷Ŵ������Ż� TBD */
oal_uint32   g_ul_wlan_vap_max_num_per_device = 4 + 1;  /* 4��AP + 1������vap */
#else
oal_uint32   g_ul_wlan_vap_max_num_per_device = 4 + 1;  /* 4��AP + 1������vap */
#endif


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


oal_uint32  dmac_dft_init(oal_void)
{
    oal_uint32  ul_core_id;
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    /* ��һ������wifi�жϵĺ�*/
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if(frw_task_get_state(ul_core_id))
        {
            break;
        }
    }
#else
    ul_core_id = OAL_GET_CORE_ID();
#endif
    if(ul_core_id == WLAN_FRW_MAX_NUM_CORES)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "dmac_timestamp_init:dft timer init failed");
        return OAL_FAIL;
    }
    /* �����쳣ͳ���ϱ���ʱ�� */
    FRW_TIMER_CREATE_TIMER(&g_st_dmac_dft_info.st_excp_stat_info.st_timer,
                           oam_exception_stat_timeout,
                           OAM_EXCP_STATS_TIMEOUT,
                           OAL_PTR_NULL,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           ul_core_id);
    return OAL_SUCC;
}


oal_uint32  dmac_dft_exit(oal_void)
{
    /* ɾ���쳣ͳ���ϱ���ʱ�� */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&g_st_dmac_dft_info.st_excp_stat_info.st_timer);

    return OAL_SUCC;
}

/*
TBD��ע�ᵽ�¼��У����¼��������ͬ������
*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_uint32 dmac_custom_sync(mac_vap_stru * pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    hal_set_proxysta_enable(OAL_PTR_NULL, g_l_proxysta_feature);
#else
    hal_set_proxysta_enable(OAL_PTR_NULL, OAL_FALSE);
#endif
    return OAL_SUCC;
}
#endif
#if ((_PRE_PRODUCT_ID_HI1102_DEV ==_PRE_PRODUCT_ID) || (_PRE_PRODUCT_ID_HI1102_HOST ==_PRE_PRODUCT_ID))
/*****************************************************************************
 �� �� ��  : oam_spec_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��17��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_custom_init(oal_void)
{
    /* Ӳ������:3��STA; 2��AP */
    /* ������:
        1)AP ģʽ:  2��ap + 1������vap
        2)STA ģʽ: 3��sta + 1������vap
        3)STA+P2P����ģʽ:  1��sta + 1��P2P_dev + 1��P2P_GO/Client + 1������vap
        4)STA+Proxy STA����ģʽ:  1��sta + ?��proxy STA + 1������vap
    */
    g_us_wlan_assoc_user_max_num     = 8;
    // TBD �趨ΪWLAN_ASSOC_USER_MAX_NUM_LIMIT;
    g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;

    return OAL_SUCC;
}

#else

/*****************************************************************************
 �� �� ��  : oam_spec_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��17��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_custom_init(oal_void)
{

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (g_l_proxysta_feature)
    {
        g_us_wlan_assoc_user_max_num  = 15;
        g_ul_wlan_vap_max_num_per_device = WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;/* 1��AP, 1��sta��15��Proxy STA��1������vap */
    }
    else
#endif
    {
        g_us_wlan_assoc_user_max_num  = WLAN_ASSOC_USER_MAX_NUM_LIMIT;
        g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;
    }

    return OAL_SUCC;
}
#endif
oal_uint32 oam_exception_stat_timeout(oal_void *p_arg)
{
    oal_uint8                       uc_vap_idx;

    for (uc_vap_idx = 0; uc_vap_idx < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_idx++)
    {
        oam_exception_stat_handler(OM_WIFI, uc_vap_idx);
    }

    return OAL_SUCC;
}

oal_uint32 dmac_dfx_init(oal_void)
{
    dmac_custom_init();
    return dmac_dft_init();
}

oal_uint32 dmac_dfx_exit(oal_void)
{
    return dmac_dft_exit();
}

/*TBD�����޶�Ϊͬ�����Ͽ�*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#else
/*lint -e19*/
oal_module_symbol(dmac_custom_sync);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
oal_module_symbol(g_l_proxysta_feature);
#endif
oal_module_symbol(g_us_wlan_assoc_user_max_num);
oal_module_symbol(g_ul_wlan_vap_max_num_per_device);
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

