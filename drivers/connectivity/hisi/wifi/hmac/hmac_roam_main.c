


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_roam_main.h"
#include "hmac_roam_connect.h"
#include "hmac_roam_alg.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_MAIN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

OAL_STATIC hmac_roam_fsm_func g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_BUTT][ROAM_MAIN_FSM_EVENT_TYPE_BUTT];
OAL_STATIC oal_uint32  hmac_roam_main_null_fn(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_scan_init(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_scan_channel(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_check_scan_reslut(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_connect_to_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_to_old_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_to_new_bss_fail(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_to_new_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_stop(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_stop_roam_trigger(hmac_vap_stru *pst_hmac_vap);
OAL_STATIC oal_uint32  hmac_roam_main_del_timer(hmac_roam_info_stru *pst_roam_info);
/*****************************************************************************
  3 函数实现
*****************************************************************************/


OAL_STATIC oal_void hmac_roam_fsm_init(oal_void)
{
    oal_uint32  ul_state;
    oal_uint32  ul_event;

    for (ul_state = 0; ul_state < ROAM_MAIN_STATE_BUTT; ul_state++)
    {
        for (ul_event = 0; ul_event < ROAM_MAIN_FSM_EVENT_TYPE_BUTT; ul_event++)
        {
            g_hmac_roam_main_fsm_func[ul_state][ul_event] = hmac_roam_main_null_fn;
        }
    }
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_INIT][ROAM_MAIN_FSM_EVENT_START]                = hmac_roam_scan_init;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_SCANING][ROAM_MAIN_FSM_EVENT_START]             = hmac_roam_scan_channel;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_SCANING][ROAM_MAIN_FSM_EVENT_SCAN_RESULT]       = hmac_roam_check_scan_reslut;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_SCANING][ROAM_MAIN_FSM_EVENT_TIMEOUT]           = hmac_roam_stop;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_SCANING][ROAM_MAIN_FSM_EVENT_START_CONNECT]     = hmac_roam_connect_to_bss;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_CONNECTING][ROAM_MAIN_FSM_EVENT_TIMEOUT]        = hmac_roam_to_old_bss;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_CONNECTING][ROAM_MAIN_FSM_EVENT_CONNECT_FAIL]   = hmac_roam_to_new_bss_fail;
    g_hmac_roam_main_fsm_func[ROAM_MAIN_STATE_CONNECTING][ROAM_MAIN_FSM_EVENT_CONNECT_SUCC]   = hmac_roam_to_new_bss;
}


oal_uint32  hmac_roam_main_fsm_action(hmac_roam_info_stru *pst_roam_info, roam_main_fsm_event_type_enum en_event, oal_void *p_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_roam_info))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_roam_info->en_main_state >= ROAM_MAIN_STATE_BUTT)
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    if (en_event >= ROAM_MAIN_FSM_EVENT_TYPE_BUTT)
    {
        return OAL_ERR_CODE_ROAM_EVENT_UXEXPECT;
    }

    return g_hmac_roam_main_fsm_func[pst_roam_info->en_main_state][en_event](pst_roam_info, p_param);
}


OAL_STATIC oal_void  hmac_roam_main_change_state(hmac_roam_info_stru *pst_roam_info, roam_main_state_enum_uint8 en_state)
{
    if (pst_roam_info)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ROAM,
                      "{hmac_roam_main_change_state::[%d]->[%d]}", pst_roam_info->en_main_state, en_state);
        pst_roam_info->en_main_state = en_state;
    }
}


OAL_STATIC oal_uint32 hmac_roam_main_timeout(oal_void *p_arg)
{
    hmac_roam_info_stru *pst_roam_info;

    pst_roam_info = (hmac_roam_info_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_roam_info))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_main_timeout::OCCURR.}");
    
    return hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_TIMEOUT, OAL_PTR_NULL);
}


oal_uint32 hmac_roam_init(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru    *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_hmac_vap->pul_roam_info)
    {
        /* 漫游主结构体内存申请 */
        pst_hmac_vap->pul_roam_info = (oal_uint32 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_roam_info_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_hmac_vap->pul_roam_info)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_init::OAL_MEM_ALLOC fail.}");
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;

    /* TBD 参数初始化 */
    oal_memset(pst_hmac_vap->pul_roam_info, 0, OAL_SIZEOF(hmac_roam_info_stru));

    pst_roam_info->uc_enable             = 1;
    pst_roam_info->en_main_state         = ROAM_MAIN_STATE_INIT;
    pst_roam_info->pst_hmac_vap          = pst_hmac_vap;
    pst_roam_info->pst_hmac_user         = OAL_PTR_NULL;
    pst_roam_info->pst_old_bss           = OAL_PTR_NULL;

    pst_roam_info->st_config.uc_scan_band                 = (ROAM_BAND_2G_BIT|ROAM_BAND_5G_BIT);
    pst_roam_info->st_config.uc_scan_orthogonal           = ROAM_SCAN_CHANNEL_ORG_BUTT;
    pst_roam_info->st_config.ul_trigger_rssi_threshold    = -70;
    pst_roam_info->st_config.ul_blacklist_expire_sec      = 100;
    pst_roam_info->st_config.ul_buffer_max                = 100;

    pst_roam_info->st_alg.st_history.us_count_limit       = 1;
    pst_roam_info->st_alg.st_history.us_timeout           = 20000;
    pst_roam_info->st_alg.st_blacklist.us_count_limit     = 2;
    pst_roam_info->st_alg.st_blacklist.us_timeout         = 50000;

    hmac_roam_fsm_init();
    hmac_roam_connect_fsm_init();

    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_init::SUCC.}");
    return OAL_SUCC;
}

oal_uint32 hmac_roam_exit(hmac_vap_stru *pst_hmac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_hmac_vap->pul_roam_info)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(((hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info)->st_connect.st_timer));
        hmac_roam_main_del_timer((hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info);
        OAL_MEM_FREE(pst_hmac_vap->pul_roam_info, OAL_TRUE);
        pst_hmac_vap->pul_roam_info = OAL_PTR_NULL;
    }

    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_exit::SUCC.}");

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alloc_buf
 功能描述  : 申请 roam 切换相关 buff，用于备份 old bss 信息、同步 hmac/dmac 信息
 输入参数  : pst_roam_info
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月02日
    作    者   : l00350000
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_roam_alloc_buf(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru           *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;

    /* 指针检查为空 */
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_alloc_buf:: pst_roam_info is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 指针检查非空 */
    if(OAL_PTR_NULL != pst_roam_info->pst_old_bss)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_alloc_buf::pst_old_bss is not NULL!}");
        return OAL_FAIL;
    }
    
    /* 保存现有bss的相关信息，以便失败的时候回退 */
    pst_roam_info->pst_old_bss = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_roam_old_bss_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_roam_info->pst_old_bss)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_alloc_buf::no buff to save old bss!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_free_buf
 功能描述  : 释放 roam 切换相关 buff，用于备份 old bss 信息、同步 hmac/dmac 信息
 输入参数  : pst_roam_info
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月02日
    作    者   : l00350000
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_roam_free_buf(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru           *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;

    /* 指针检查为空 */
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_free_buf:: pst_roam_info is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 释放旧bss的数据 */
    if(OAL_PTR_NULL != pst_roam_info->pst_old_bss)
    {
        OAL_MEM_FREE(pst_roam_info->pst_old_bss, OAL_TRUE);
        pst_roam_info->pst_old_bss = OAL_PTR_NULL;
    }    
    return OAL_SUCC;
}


oal_uint32 hmac_roam_show_info(hmac_vap_stru *pst_hmac_vap)
{
    oal_int8               *pc_print_buff;
    hmac_roam_info_stru    *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_hmac_vap->pul_roam_info)
    {
        return OAL_SUCC;
    }

    pc_print_buff = (oal_int8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAM_REPORT_MAX_STRING_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == pc_print_buff)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{hmac_config_vap_info::pc_print_buff null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);
    OAL_SPRINTF(pc_print_buff, OAM_REPORT_MAX_STRING_LEN,
                    "ROAM_EN[%d] MAIN_STATE[%d]\n"
                    "ROAM_SCAN_BAND[%d] ROAM_SCAN_ORTH[%d]\n",
                    pst_roam_info->uc_enable, pst_roam_info->en_main_state,
                    pst_roam_info->st_config.uc_scan_band, pst_roam_info->st_config.uc_scan_orthogonal);

    oam_print(pc_print_buff);

    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

    return OAL_SUCC;
}


OAL_STATIC oal_void hmac_roam_main_start_timer(hmac_roam_info_stru *pst_roam_info, oal_uint32 ul_timeout)
{
    frw_timeout_stru            *pst_timer = &(pst_roam_info->st_timer);

    OAM_INFO_LOG1(0, OAM_SF_ROAM, "{hmac_roam_main_start_timer [%d].}", ul_timeout);

    /* 启动认证超时定时器 */
    FRW_TIMER_CREATE_TIMER(pst_timer,
                           hmac_roam_main_timeout,
                           ul_timeout,
                           pst_roam_info,
                           OAL_TRUE,
                           OAM_MODULE_ID_HMAC,
                           pst_roam_info->pst_hmac_vap->st_vap_base_info.ul_core_id);
}
OAL_STATIC oal_uint32  hmac_roam_main_del_timer(hmac_roam_info_stru *pst_roam_info)
{
    OAM_INFO_LOG0(0, OAM_SF_ROAM, "{hmac_roam_main_del_timer.}");
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_roam_info->st_timer));
    return OAL_SUCC;
}


oal_uint32 hmac_roam_enable(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_enable)
{
    hmac_roam_info_stru   *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_enable::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_enable::pst_roam_info null .}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    if (uc_enable == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_enable::SET[%d] fail .}", uc_enable);
        return OAL_FAIL;
    }

    /* 设置漫游开关 */
    pst_roam_info->uc_enable             = uc_enable;
    pst_roam_info->en_main_state         = ROAM_MAIN_STATE_INIT;
    OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_enable::SET[%d] OK!}", uc_enable);

    return OAL_SUCC;
}
oal_uint32 hmac_roam_org(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_scan_orthogonal)
{
    hmac_roam_info_stru   *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_org::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_org::pst_roam_info null .}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 设置漫游正交 */
    pst_roam_info->st_config.uc_scan_orthogonal = uc_scan_orthogonal;
    OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_org::SET[%d] OK!}", uc_scan_orthogonal);

    return OAL_SUCC;
}
oal_uint32 hmac_roam_band(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_scan_band)
{
    hmac_roam_info_stru   *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_band::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_band::pst_roam_info null .}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 设置漫游频段 */
    pst_roam_info->st_config.uc_scan_band = uc_scan_band;
    OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_band::SET[%d] OK!}", uc_scan_band);

    return OAL_SUCC;
}
oal_uint32 hmac_roam_start(hmac_vap_stru *pst_hmac_vap)
{
    oal_uint32             ul_ret;
    hmac_roam_info_stru   *pst_roam_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_start::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    hmac_roam_alg_init(pst_roam_info, ROAM_RSSI_CMD_TYPE);

    ul_ret = hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_START, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_start::START fail[%d].}", ul_ret);
        return ul_ret;
    }
    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_start::START succ.}");
    return OAL_SUCC;
}


oal_uint32 hmac_roam_show(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru             *pst_roam_info;
    hmac_roam_static_stru           *pst_static;
    oal_uint8                        uc_vap_id;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_show::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_show::pst_roam_info null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_static = &pst_roam_info->st_static;

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;
    OAM_ERROR_LOG2(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_show::trigger_rssi_cnt[0x%x] trigger_linkloss_cnt[0x%x] .}",
                   pst_static->ul_trigger_rssi_cnt, pst_static->ul_trigger_linkloss_cnt);
    OAM_ERROR_LOG2(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_show::scan_cnt[0x%x] scan_result_cnt[0x%x].}",
                   pst_static->ul_scan_cnt, pst_static->ul_scan_result_cnt);
    OAM_ERROR_LOG3(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_show::connect_cnt[0x%x] roam_new_cnt[0x%x] roam_old_cnt[0x%x].}",
                   pst_static->ul_connect_cnt, pst_static->ul_roam_new_cnt, pst_static->ul_roam_old_cnt);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  hmac_roam_main_null_fn(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    /* 什么都不做 */

    return OAL_SUCC;
}
OAL_STATIC oal_void  hmac_roam_scan_comp_cb(void  *p_scan_record)
{
    hmac_scan_record_stru           *pst_scan_record = (hmac_scan_record_stru *)p_scan_record;
    hmac_vap_stru                   *pst_hmac_vap = OAL_PTR_NULL;
    hmac_roam_info_stru             *pst_roam_info;
    hmac_device_stru                *pst_hmac_device;
    hmac_bss_mgmt_stru              *pst_scan_bss_mgmt;

    /* 获取hmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_scan_record->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_roam_scan_comp_cb::pst_hmac_vap is null.");
        return;
    }

    /* 获取hmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_complete::device null!}");
        return;
    }

    pst_scan_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        return;
    }

    /* 漫游开关没有开时，不处理扫描结果 */
    if (pst_roam_info->uc_enable == 0)
    {
        return;
    }

    OAM_INFO_LOG0(pst_scan_record->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_scan_complete::handling scan result!}");
    hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_SCAN_RESULT, (void *)pst_scan_bss_mgmt);

    return;
}
OAL_STATIC oal_uint32  hmac_roam_scan_init(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32              ul_ret;
    mac_scan_req_stru      *pst_scan_params;
    hmac_vap_stru          *pst_hmac_vap;
    oal_uint8              *puc_cur_ssid;

    /* 漫游开关没有开时，不发起扫描 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_init::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_INIT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_scan_init::scan disabled in state[%d]!}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_init::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (pst_hmac_vap->st_vap_base_info.en_vap_state != MAC_VAP_STATE_UP)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_scan_init::vap state[%d] is not up.}", pst_hmac_vap->st_vap_base_info.en_vap_state);
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info->pst_hmac_user = mac_res_get_hmac_user((oal_uint16)pst_hmac_vap->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_roam_info->pst_hmac_user)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_scan_init::assoc_vap_id[%d] can't found.}", pst_hmac_vap->st_vap_base_info.uc_assoc_vap_id);
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (mac_is_wep_enabled(&pst_hmac_vap->st_vap_base_info))
    {
        hmac_roam_stop_roam_trigger(pst_hmac_vap);
        return OAL_SUCC;
    }

    pst_scan_params = &pst_roam_info->st_scan_params;
    puc_cur_ssid = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;

    /* 扫描参数初始化 */
    pst_scan_params->en_bss_type         = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_scan_params->en_scan_type        = WLAN_SCAN_TYPE_ACTIVE;
    pst_scan_params->us_scan_time        = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    pst_scan_params->uc_probe_delay      = 0;
    pst_scan_params->uc_scan_func        = MAC_SCAN_FUNC_BSS;               /* 默认扫描bss */
    pst_scan_params->p_fn_cb             = hmac_roam_scan_comp_cb;
    pst_scan_params->uc_max_send_probe_req_count_per_channel = WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL;

    oal_memcopy(pst_scan_params->ac_ssid[0], puc_cur_ssid, WLAN_SSID_MAX_LEN);
    pst_scan_params->uc_ssid_num                             = 1;

    /* 初始扫描请求只指定1个bssid，为广播地址 */
    oal_memset(pst_scan_params->auc_bssid, 0xff, WLAN_MAC_ADDR_LEN);
    pst_scan_params->uc_bssid_num                            = 1;

    ul_ret = hmac_roam_alg_scan_channel_init(pst_roam_info, pst_scan_params);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_scan_init::hmac_roam_alg_scan_channel_init fail[%d]}", ul_ret);
        return ul_ret;
    }
    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_SCANING);
    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_scan_init::start scanning!}");

    return hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_START, (oal_void *)pst_roam_info);
}

OAL_STATIC oal_uint32  hmac_roam_scan_channel(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32              ul_ret;
    hmac_vap_stru          *pst_hmac_vap;

    /* 漫游开关没有开时，不发起扫描 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_channel::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 只允许在scaning状态下发起扫描 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_SCANING)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_scan_channel::scan disabled in state[%d]!}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_channel::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (pst_hmac_vap->st_vap_base_info.en_vap_state != MAC_VAP_STATE_UP)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_scan_channel::vap state[%d] is not up.}", pst_hmac_vap->st_vap_base_info.en_vap_state);
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info->st_static.ul_scan_cnt++;

    /* 发起背景扫描 */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_SCAN_REQ, (oal_void *)(&pst_roam_info->st_scan_params));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_scan_channel::start scan failed!}");
        return ul_ret;
    }

    /* 启动扫描超时定时器 */
    hmac_roam_main_start_timer(pst_roam_info, ROAM_SCAN_TIME_MAX);

    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_scan_channel::now scanning!}");
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  hmac_roam_check_scan_reslut(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32               ul_ret;
    hmac_bss_mgmt_stru      *pst_bss_mgmt;
    hmac_vap_stru           *pst_hmac_vap;
    oal_dlist_head_stru     *pst_entry;
    hmac_scanned_bss_info   *pst_scanned_bss;
    hmac_scan_rsp_stru       st_scan_rsp;
    mac_bss_dscr_stru       *pst_bss_dscr = OAL_PTR_NULL;

    /* 漫游开关没有开时，不处理扫描;不需要打印失败，防止正常扫描时打印过多 */
    if (0 == pst_roam_info->uc_enable)
    {
        return OAL_SUCC;
    }

    /* SCANING状态下才处理扫描结果 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_SCANING)
    {
        return OAL_SUCC;
    }

    pst_hmac_vap    = pst_roam_info->pst_hmac_vap;
    pst_bss_mgmt    = (hmac_bss_mgmt_stru *)p_param;
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_bss_mgmt))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_check_scan_reslut::vap invalid!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info->st_static.ul_scan_result_cnt++;

    /* 如果扫描到的bss个数为0，退出 */
    if (0 == pst_bss_mgmt->ul_bss_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_check_scan_reslut::no bss scanned}");
        return OAL_ERR_CODE_ROAM_NO_VALID_BSS;
    }

    /* 获取锁 */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* 遍历扫描到的bss信息，查找可以漫游的bss */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);

        ul_ret = hmac_roam_alg_bss_check(pst_roam_info, pst_bss_dscr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_check_scan_reslut::hmac_roam_alg_bss_check fail[%d]}", ul_ret);
        }

        pst_bss_dscr = OAL_PTR_NULL;
    }

    /* 解除锁 */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    if (OAL_TRUE == hmac_roam_alg_need_to_stop_roam_trigger(pst_roam_info))
    {
        return hmac_roam_stop_roam_trigger(pst_hmac_vap);
    }

    pst_bss_dscr = hmac_roam_alg_select_bss(pst_roam_info);
    if (OAL_PTR_NULL == pst_bss_dscr)
    {
        /* 没有扫描到可用的bss，等待定时器超时即可 */
        OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_check_scan_reslut::no bss valid}");
        return OAL_SUCC;
    }

    ul_ret = hmac_check_capability_mac_phy_supplicant(&(pst_hmac_vap->st_vap_base_info), pst_bss_dscr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{hmac_roam_check_scan_reslut::check mac and phy capability fail[%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* 扫描结果发给sme */
    OAL_MEMZERO(&st_scan_rsp, OAL_SIZEOF(st_scan_rsp));
    hmac_send_rsp_to_sme_sta(pst_hmac_vap, HMAC_SME_SCAN_RSP, (oal_uint8 *)&st_scan_rsp);

    /* 扫描到可用的bss，开始connect */
    return hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_START_CONNECT, (oal_void *)pst_bss_dscr);
}
OAL_STATIC oal_uint32  hmac_roam_connect_to_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru           *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;
    hmac_user_stru          *pst_hmac_user = pst_roam_info->pst_hmac_user;
    mac_bss_dscr_stru       *pst_bss_dscr  = (mac_bss_dscr_stru *)p_param;
    hmac_roam_old_bss_stru  *pst_old_bss;
    oal_uint32               ul_ret;
    oal_uint32               ul_need_to_stop_user = 1;
#ifdef _PRE_WLAN_FEATURE_11R
    wlan_mib_Dot11FastBSSTransitionConfigEntry_stru *pst_wlan_mib_ft_cfg;
#endif //_PRE_WLAN_FEATURE_11R

    /* 漫游开关没有开时，不发起connect */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 只有在scaning状态才发起connect */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_SCANING)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::unexpected state[%d]!}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    if ((pst_hmac_vap == OAL_PTR_NULL) || (pst_hmac_user == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }


#ifdef _PRE_WLAN_FEATURE_11R
    pst_wlan_mib_ft_cfg = &pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg;
    if ((OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FastBSSTransitionActivated) &&
        (OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FTOverDSActivated))
    {
        ul_need_to_stop_user = 0;
    }
#endif //_PRE_WLAN_FEATURE_11R

    if (0 != ul_need_to_stop_user)
    {
        /* 切换vap的状态为ROAMING，将用户节能，暂停发送 */
        ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_ROAMING_START, (oal_void *)pst_bss_dscr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::hmac_fsm_call_func_sta fail[%ld]!}", ul_ret);
            return ul_ret;
        }
    }
    /* 申请漫游数据 buff */
    hmac_roam_alloc_buf(pst_roam_info);

    /* 原bss信息保存，以便回退 */
    pst_old_bss = pst_roam_info->pst_old_bss;
    pst_old_bss->us_sta_aid = pst_hmac_vap->st_vap_base_info.us_sta_aid;
    oal_memcopy(&pst_old_bss->st_cap_info, &(pst_hmac_user->st_user_base_info.st_cap_info), OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy(&pst_old_bss->st_key_info, &(pst_hmac_user->st_user_base_info.st_key_info), OAL_SIZEOF(mac_key_mgmt_stru));
    oal_memcopy(&pst_old_bss->st_user_tx_info, &(pst_hmac_user->st_user_base_info.st_user_tx_info), OAL_SIZEOF(mac_user_tx_param_stru));
    oal_memcopy(&pst_old_bss->st_mib_info, pst_hmac_vap->st_vap_base_info.pst_mib_info, OAL_SIZEOF(wlan_mib_ieee802dot11_stru));
    oal_memcopy(&pst_old_bss->st_op_rates, &(pst_hmac_user->st_op_rates), OAL_SIZEOF(mac_rate_stru));
    oal_memcopy(&pst_old_bss->st_ht_hdl, &(pst_hmac_user->st_user_base_info.st_ht_hdl), OAL_SIZEOF(mac_user_ht_hdl_stru));
    oal_memcopy(&pst_old_bss->st_vht_hdl, &(pst_hmac_user->st_user_base_info.st_vht_hdl), OAL_SIZEOF(mac_vht_hdl_stru));
    pst_old_bss->en_avail_bandwidth = pst_hmac_user->st_user_base_info.en_avail_bandwidth;
    pst_old_bss->en_cur_bandwidth = pst_hmac_user->st_user_base_info.en_cur_bandwidth;
    oal_memcopy(&pst_old_bss->st_channel, &(pst_hmac_vap->st_vap_base_info.st_channel), OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&pst_old_bss->auc_bssid, &(pst_hmac_vap->st_vap_base_info.auc_bssid), WLAN_MAC_ADDR_LEN);
    pst_old_bss->us_cap_info = pst_hmac_vap->st_vap_base_info.us_assoc_user_cap_info;

    /* 切换状态至connecting */
    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_CONNECTING);

    pst_roam_info->st_static.ul_connect_cnt++;

    /* 设置漫游到的bss能力位，重关联请求使用 */
    pst_hmac_vap->st_vap_base_info.us_assoc_user_cap_info = pst_bss_dscr->us_cap_info;

    /* 启动connect状态机 */
    ul_ret = hmac_roam_connect_start(pst_hmac_vap, pst_bss_dscr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::hmac_roam_connect_start fail[%ld]!}", ul_ret);
        return ul_ret;
    }

    /* 启动connect超时定时器 */
    hmac_roam_main_start_timer(pst_roam_info, ROAM_CONNECT_TIME_MAX);

    OAM_INFO_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                   "{hmac_roam_connect_to_bss::connecting to [%02X:XX:XX:XX:%02X:%02X] PAIRWISE[%d]}",
                   pst_bss_dscr->auc_bssid[0],pst_bss_dscr->auc_bssid[4],pst_bss_dscr->auc_bssid[5], 
                   pst_bss_dscr->st_bss_sec_info.uc_pairwise_policy_match);

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                   "{hmac_roam_connect_to_bss::backup st_key_info.en_cipher_type = %d, uc_default_index = %d}",
                   pst_old_bss->st_key_info.en_cipher_type,pst_old_bss->st_key_info.uc_default_index);

    OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                   "{hmac_roam_connect_to_bss::backup st_user_tx_info, en_cipher_key_type = %d, en_cipher_protocol_type = %d, uc_cipher_key_id = %d}",
                   pst_old_bss->st_user_tx_info.st_security.en_cipher_key_type,pst_old_bss->st_user_tx_info.st_security.en_cipher_protocol_type,pst_old_bss->st_user_tx_info.st_security.uc_cipher_key_id);

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  hmac_roam_to_old_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32                  ul_ret          = OAL_SUCC;
    hmac_vap_stru               *pst_hmac_vap   = pst_roam_info->pst_hmac_vap;
    hmac_user_stru              *pst_hmac_user  = pst_roam_info->pst_hmac_user;
    hmac_roam_old_bss_stru      *pst_old_bss    = pst_roam_info->pst_old_bss;
    mac_h2d_roam_sync_stru      *pst_h2d_sync   = OAL_PTR_NULL;
    
    if (OAL_PTR_NULL == pst_old_bss)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_back_to_old_bss::pst_old_bss null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 只有在connecting状态才发起back to old bss */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_back_to_old_bss::unexpect state[%d]}", pst_roam_info->en_main_state);
        hmac_roam_free_buf(pst_roam_info);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    if ((pst_hmac_vap == OAL_PTR_NULL) || (pst_hmac_user == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_back_to_old_bss::vap null!}");
        hmac_roam_free_buf(pst_roam_info);
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info->st_static.ul_roam_old_cnt++;

    /* 添加黑名单*/
    hmac_roam_alg_add_blacklist(pst_roam_info, pst_hmac_vap->st_vap_base_info.auc_bssid);

    /* 恢复原来bss相关信息 */
    pst_hmac_vap->st_vap_base_info.us_sta_aid = pst_old_bss->us_sta_aid;
    oal_memcopy(&(pst_hmac_user->st_user_base_info.st_cap_info), &pst_old_bss->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy(&(pst_hmac_user->st_user_base_info.st_key_info), &pst_old_bss->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));
    oal_memcopy(&(pst_hmac_user->st_user_base_info.st_user_tx_info),&pst_old_bss->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));
    oal_memcopy(pst_hmac_vap->st_vap_base_info.pst_mib_info, &pst_old_bss->st_mib_info, OAL_SIZEOF(wlan_mib_ieee802dot11_stru));
    oal_memcopy(&(pst_hmac_user->st_op_rates), &pst_old_bss->st_op_rates, OAL_SIZEOF(mac_rate_stru));
    oal_memcopy(&(pst_hmac_user->st_user_base_info.st_ht_hdl), &pst_old_bss->st_ht_hdl, OAL_SIZEOF(mac_user_ht_hdl_stru));
    oal_memcopy(&(pst_hmac_user->st_user_base_info.st_vht_hdl), &pst_old_bss->st_vht_hdl, OAL_SIZEOF(mac_vht_hdl_stru));
    pst_hmac_user->st_user_base_info.en_avail_bandwidth = pst_old_bss->en_avail_bandwidth;
    pst_hmac_user->st_user_base_info.en_cur_bandwidth   = pst_old_bss->en_cur_bandwidth;
    oal_memcopy(&(pst_hmac_vap->st_vap_base_info.st_channel), &pst_old_bss->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(pst_hmac_vap->st_vap_base_info.auc_bssid, pst_old_bss->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_hmac_vap->st_vap_base_info.us_assoc_user_cap_info = pst_old_bss->us_cap_info;

    /* 设置用户8021x端口合法性的状态为合法 */
    mac_user_set_port(&pst_hmac_user->st_user_base_info, OAL_TRUE);

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                   "{hmac_roam_to_old_bss::backup st_key_info.en_cipher_type = %d, uc_default_index = %d}",
                   pst_old_bss->st_key_info.en_cipher_type,pst_old_bss->st_key_info.uc_default_index);

    OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                   "{hmac_roam_to_old_bss::backup st_user_tx_info, en_cipher_key_type = %d, en_cipher_protocol_type = %d, uc_cipher_key_id = %d}",
                   pst_old_bss->st_user_tx_info.st_security.en_cipher_key_type,pst_old_bss->st_user_tx_info.st_security.en_cipher_protocol_type,pst_old_bss->st_user_tx_info.st_security.uc_cipher_key_id);
        
    /* 相关参数需要配置到dmac */
    hmac_roam_connect_set_join_reg(&pst_hmac_vap->st_vap_base_info);

    hmac_roam_connect_set_dtim_param(&pst_hmac_vap->st_vap_base_info, 0, pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod, BIT0);

    /* 更新用户的mac地址，漫游时mac会更新 */
    oal_set_mac_addr(pst_hmac_user->st_user_base_info.auc_user_mac_addr, pst_hmac_vap->st_vap_base_info.auc_bssid);

    ul_ret = hmac_config_user_info_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_back_to_old_bss::hmac_syn_vap_state failed[%d].}", ul_ret);
    }

    /* 回退 bss 时，hmac 2 dmac 同步的相关信息，以便失败的时候回退 */
    pst_h2d_sync = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_h2d_roam_sync_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_h2d_sync)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_to_bss::no buff to alloc sync info!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    //填充同步信息
    pst_h2d_sync->us_sta_aid = pst_old_bss->us_sta_aid;
    oal_memcopy(&(pst_h2d_sync->st_channel), &pst_old_bss->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&(pst_h2d_sync->st_cap_info), &pst_old_bss->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy(&(pst_h2d_sync->st_key_info), &pst_old_bss->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));
    oal_memcopy(&(pst_h2d_sync->st_user_tx_info),&pst_old_bss->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));

    //发送同步信息
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info, WLAN_CFGID_ROAM_HMAC_SYNC_DMAC, OAL_SIZEOF(mac_h2d_roam_sync_stru), (oal_uint8 *)pst_h2d_sync);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_back_to_old_bss::send event[WLAN_CFGID_ROAM_HMAC_SYNC_DMAC] failed[%d].}", ul_ret);
    }

    /* 释放同步数据 */
    if(OAL_PTR_NULL != pst_h2d_sync)
    {
        OAL_MEM_FREE(pst_h2d_sync, OAL_TRUE);
        pst_h2d_sync = OAL_PTR_NULL;
    }

    /* user已经关联上，抛事件给DMAC，在DMAC层挂用户算法钩子 */
    hmac_user_add_notify_alg(&pst_hmac_vap->st_vap_base_info, pst_hmac_user->st_user_base_info.us_assoc_id);

    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_FAIL);

    /* 切换vap的状态为UP，恢复用户节能，恢复发送 */
    hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_ROAMING_STOP, OAL_PTR_NULL);

    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                  "{hmac_roam_back_to_old_bss::now resuming to [%02X:XX:XX:%02X:%02X:%02X]}", 
                  pst_old_bss->auc_bssid[0],pst_old_bss->auc_bssid[3],pst_old_bss->auc_bssid[4],pst_old_bss->auc_bssid[5]);


    /* 释放漫游数据 buff */
    hmac_roam_free_buf(pst_roam_info);

    return ul_ret;
}
OAL_STATIC oal_uint32  hmac_roam_to_new_bss_fail(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    /* 漫游失败先关闭漫游主定时器 */
    hmac_roam_main_del_timer(pst_roam_info);

    return hmac_roam_to_old_bss(pst_roam_info, p_param);
}
OAL_STATIC oal_uint32  hmac_roam_to_new_bss(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru           *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;

    /* 释放旧bss的数据 */
    hmac_roam_free_buf(pst_roam_info);

    /* 漫游开关没有开时，停止漫游 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_trans_to_new_bss::roam disabled, now stopping}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 只有在connecting状态才发起trans to new bss */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_trans_to_new_bss::unexpected state[%d]!}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_trans_to_new_bss::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info->st_static.ul_roam_new_cnt++;
    hmac_roam_alg_add_history(pst_roam_info, pst_hmac_vap->st_vap_base_info.auc_bssid);
    hmac_roam_alg_add_history(pst_roam_info, pst_hmac_vap->st_vap_base_info.auc_bssid);

    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_UP);

    /* 切换vap的状态为UP，恢复用户节能，恢复发送 */
    hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_ROAMING_STOP, OAL_PTR_NULL);

    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                  "{hmac_roam_trans_to_new_bss::roam to [%02X:XX:XX:%02X:%02X:%02X] succ}", 
                  pst_hmac_vap->st_vap_base_info.auc_bssid[0],pst_hmac_vap->st_vap_base_info.auc_bssid[3],
                  pst_hmac_vap->st_vap_base_info.auc_bssid[4],pst_hmac_vap->st_vap_base_info.auc_bssid[5]);

    return OAL_SUCC;

}


OAL_STATIC oal_uint32  hmac_roam_stop(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru           *pst_hmac_vap   = pst_roam_info->pst_hmac_vap;
    oal_uint32               ul_reason_code = 0;
    oal_uint32               ul_ret;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_stop::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }
    if (p_param)
    {
        ul_reason_code = *(oal_uint32 *)p_param;
    }

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                  "{hmac_roam_stop::current state[%d] reacon code[%d]}", pst_roam_info->en_main_state, ul_reason_code);

    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_FAIL);

    /* 切换vap的状态为UP，恢复用户节能，恢复发送 */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_ROAMING_STOP, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_stop::hmac_fsm_call_func_sta fail[%d]!} reason code[%d]", ul_ret, ul_reason_code);
        return ul_ret;
    }

    return OAL_SUCC;
}
#if 0
OAL_STATIC oal_uint32  hmac_roam_flush_buf(struct work_struct *pst_work)
{
    hmac_roam_buf_stru                *pst_roam_buf;
    hmac_roam_info_stru               *pst_roam_info;
    oal_netbuf_stru                   *pst_skb;
    oal_uint32                         ul_ret;
    hmac_vap_stru                     *pst_hmac_vap;

    pst_roam_buf  = container_of(pst_work, struct hmac_roam_buf_stru, st_work);
    pst_roam_info = container_of(pst_roam_buf, struct hmac_roam_info_stru, st_buf);

    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_flush_buf::roam_info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (OAL_PTR_NULL == pst_roam_buf->pst_wq)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_flush_buf::pst_wq null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_flush_buf::hmac_vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    while(!skb_queue_empty(&pst_roam_buf->st_data_queue))
    {
        pst_skb = skb_dequeue(&pst_roam_buf->st_data_queue);

        ul_ret  = hmac_tx_lan_to_wlan(&(pst_hmac_vap->st_vap_base_info), pst_skb);
        if (SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_flush_buf::hmac_tx_lan_to_wlan fail[%d]!}", ul_ret);
            oal_netbuf_free(pst_skb);
        }
    }
}


oal_uint32  hmac_roam_pause_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_roam_info_stru     *pst_roam_info;
    oal_uint8                uc_vap_id;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_pause_user::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不暂停用户 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    if (OAL_PTR_NULL != pst_roam_info->st_buf.pst_wq)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::buf exist!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 初始化缓存队列 */
    skb_queue_head_init(&(pst_roam_info->st_buf.st_data_queue));
    INIT_WORK(&(pst_roam_info->st_buf.st_work), hmac_roam_flush_buf);
    pst_roam_info->st_buf.pst_wq = create_singlethread_workqueue("hi110x_roam");
    return OAL_SUCC;
}


oal_uint32  hmac_roam_resume_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_roam_info_stru     *pst_roam_info;
    oal_uint8                uc_vap_id;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_pause_user::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (OAL_PTR_NULL == pst_roam_info->st_buf.pst_wq)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::buf exist!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 清空缓存队列 */
    skb_queue_purge(&(pst_roam_info->st_buf.st_data_queue));
    destroy_workqueue(pst_roam_info->st_buf.pst_wq);
    pst_roam_info->st_buf.pst_wq = OAL_PTR_NULL;
    return OAL_SUCC;
}
#endif
OAL_STATIC oal_uint32  hmac_roam_stop_roam_trigger(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_uint32                        ul_ret;
    oal_uint8                         uc_vap_id;
    oal_uint8                         uc_roam_trigger_type;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_stop_roam_trigger::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_stop_roam_trigger::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_roam_trigger_type = 1;
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info, WLAN_CFGID_SET_ROAM_TRIGGER, OAL_SIZEOF(oal_uint8), (oal_uint8 *)&uc_roam_trigger_type);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_CFG, "{hmac_roam_stop_roam_trigger::send event[WLAN_CFGID_SET_ROAM_TRIGGER] failed[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_stop_roam_trigger::OK!}");
    return OAL_SUCC;
}


oal_uint32  hmac_roam_pause_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_net_device_stru              *pst_net_device;
    oal_uint32                        ul_ret;
    oal_uint8                         uc_vap_id;
    oal_uint8                         uc_roaming_mode;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_pause_user::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不暂停用户 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    pst_net_device = pst_hmac_vap->pst_net_device;
    if (OAL_PTR_NULL == pst_net_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::net_device null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 必须保证vap的状态是UP */
    if (MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_pause_user::vap state[%d] unexpected!}", pst_hmac_vap->st_vap_base_info.en_vap_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* 暂停所有协议层数据，这样就不需要再hmac搞一个缓存队列了 */
    //oal_net_stop_subqueue(pst_net_device, 0);
    oal_net_tx_stop_all_queues(pst_net_device);
    oal_net_wake_subqueue(pst_net_device, WLAN_HI_QUEUE);

    /* 清空 HMAC层TID信息 */
    hmac_tid_clear(&pst_hmac_vap->st_vap_base_info, pst_roam_info->pst_hmac_user);

#ifdef _PRE_WLAN_FEATURE_STA_PM
    ul_ret = hmac_config_sta_pm_off_syn(&pst_hmac_vap->st_vap_base_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_CFG, "{hmac_roam_pause_user::hmac_config_sta_pm_off_syn failed[%d].}", ul_ret);
        oal_net_tx_wake_all_queues(pst_net_device);
        return ul_ret;
    }
#endif

    uc_roaming_mode = 1;
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info, WLAN_CFGID_SET_ROAMING_MODE, OAL_SIZEOF(oal_uint8), (oal_uint8 *)&uc_roaming_mode);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_CFG, "{hmac_roam_pause_user::send event[WLAN_CFGID_SET_ROAMING_MODE] failed[%d].}", ul_ret);
        oal_net_tx_wake_all_queues(pst_net_device);
        return ul_ret;
    }

    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_ROAMING);

    OAM_INFO_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_pause_user::queues stopped!}");
    return OAL_SUCC;
}


oal_uint32  hmac_roam_resume_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_net_device_stru              *pst_net_device;
    oal_uint32                        ul_ret;
    oal_uint8                         uc_vap_id;
    oal_uint8                         uc_roaming_mode;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_resume_user::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_resume_user::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_net_device = pst_hmac_vap->pst_net_device;
    if (OAL_PTR_NULL == pst_net_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_resume_user::net_device null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 必须保证vap的状态是roaming */
    if (MAC_VAP_STATE_ROAMING != pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
        oal_net_tx_wake_all_queues(pst_net_device);
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_resume_user::vap state[%d] unexpected!}", pst_hmac_vap->st_vap_base_info.en_vap_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    uc_roaming_mode = 0;
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info, WLAN_CFGID_SET_ROAMING_MODE, OAL_SIZEOF(oal_uint8), (oal_uint8 *)&uc_roaming_mode);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_CFG, "{hmac_roam_resume_user::send event[WLAN_CFGID_SET_ROAMING_MODE] failed[%d].}", ul_ret);
    }

    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_UP);

    hmac_roam_main_change_state(pst_roam_info, ROAM_MAIN_STATE_INIT);

    hmac_roam_connect_stop(pst_hmac_vap);

#ifdef _PRE_WLAN_FEATURE_STA_PM
    ul_ret = hmac_set_ipaddr_timeout(&pst_hmac_vap->st_vap_base_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_CFG, "{hmac_roam_resume_user::hmac_set_ipaddr_timeout failed[%d].}", ul_ret);
    }
#endif
    oal_net_tx_wake_all_queues(pst_net_device);

    OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_resume_user::all_queues awake!}");

    return OAL_SUCC;
}
oal_uint32 hmac_roam_scan_complete(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;
    hmac_device_stru                 *pst_hmac_device;
    oal_uint8                         uc_vap_id;
    hmac_bss_mgmt_stru               *pst_scan_bss_mgmt;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_complete::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理扫描结果 */
    if (0 == pst_roam_info->uc_enable)
    {
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 获取hmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_complete::device null!}");
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    pst_scan_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    OAM_INFO_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_scan_complete::handling scan result!}");
    return hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_SCAN_RESULT, (void *)pst_scan_bss_mgmt);
}


oal_void  hmac_roam_tbtt_handle(hmac_vap_stru *pst_hmac_vap)
{
    //hmac_roam_connect_rx_tbtt(pst_hmac_vap);
}


oal_uint32 hmac_roam_trigger_handle(hmac_vap_stru *pst_hmac_vap, oal_int8 c_rssi)
{
    hmac_roam_info_stru     *pst_roam_info;
    oal_uint32               ul_ret;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_trigger_handle::pst_hmac_vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_trigger_handle::pst_roam_info null!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 漫游开关没有开时，不处理扫描结果 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_trigger_handle::ROAM_DISABLED!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    if (ROAM_MAIN_STATE_INIT != pst_roam_info->en_main_state)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{hmac_roam_trigger_handle::ROAMING NOW! STATE[%d]!}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    hmac_roam_alg_init(pst_roam_info, c_rssi);

    ul_ret = hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_START, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_trigger_handle::START fail[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_trigger_handle::RSSI[%d].}", c_rssi);
    return OAL_SUCC;
}
oal_uint32  hmac_sta_roam_rx_mgmt(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    dmac_wlan_crx_event_stru *pst_crx_event;

    pst_crx_event = (dmac_wlan_crx_event_stru *)p_param;

    hmac_roam_connect_rx_mgmt(pst_hmac_vap, pst_crx_event);
    return OAL_SUCC;
}

oal_void  hmac_roam_add_key_done(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_connect_key_done(pst_hmac_vap);
}
#ifdef _PRE_WLAN_FEATURE_11R

oal_uint32 hmac_roam_reassoc(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_uint32                        ul_ret;
    oal_uint8                         uc_vap_id;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_reassoc::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_reassoc::roam info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    ul_ret = hmac_roam_connect_ft_reassoc(pst_hmac_vap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_reassoc::hmac_roam_connect_process_ft FAIL[%d]!}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

oal_uint32 hmac_roam_rx_ft_action(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_wlan_crx_event_stru st_crx_event;

    OAL_MEMZERO(&st_crx_event, OAL_SIZEOF(dmac_wlan_crx_event_stru));
    st_crx_event.pst_netbuf = pst_netbuf;

    hmac_roam_connect_rx_mgmt(pst_hmac_vap, &st_crx_event);
    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_11R

oal_void hmac_roam_connect_complete(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_reslut)
{
    hmac_roam_info_stru     *pst_roam_info;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::vap null!}");
        return;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::pst_roam_info null!}");
        return;
    }

    /* 漫游开关没有开时，不处理扫描结果 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::roam disabled!}");
        return;
    }

    if (ul_reslut == OAL_SUCC)
    {
        hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_CONNECT_SUCC, OAL_PTR_NULL);
    }
    else
    {
        hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_CONNECT_FAIL, OAL_PTR_NULL);
    }
}

#if 0
oal_void hmac_roam_rx_complete(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_reslut)
{
    hmac_roam_info_stru     *pst_roam_info;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::vap null!}");
        return;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::pst_roam_info null!}");
        return;
    }

    /* 漫游开关没有开时，不处理扫描结果 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_complete::roam disabled!}");
        return;
    }

    if (ul_reslut == OAL_SUCC)
    {
        hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_CONNECT_SUCC, OAL_PTR_NULL);
    }
    else
    {
        hmac_roam_main_fsm_action(pst_roam_info, ROAM_MAIN_FSM_EVENT_CONNECT_FAIL, OAL_PTR_NULL);
    }
}

#endif
oal_void hmac_roam_timeout_test(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_connect_timeout(pst_hmac_vap->pul_roam_info);
}

#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

