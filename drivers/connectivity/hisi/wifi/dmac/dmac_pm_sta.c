


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_hcc_slave_if.h"
#include "hal_hi1102_reset.h"
#include "wlan_spec.h"
#include "wlan_mib.h"
#include "hal_device.h"
#include "hal_hi1102_soc.h"
#include "hal_hi1102_mac_reg.h"
#include "hal_hi1102_soc_reg.h"
#include "hal_hi1102_phy_reg.h"
#include "oal_mem.h"
#include "mac_resource.h"
#include "stack_cr4.h"
#include "DMA.h"
#include "dmac_pm_sta.h"
#include "dmac_rx_data.h"
#include "frw_timer.h"
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PM_STA_C

#if (defined(HI1102_ASIC))
#define PM_DMA_SAVE_TCM_SIZE    (0x3F00)
#define PM_DMA_RECOVER_TCM_SIZE (0x3F00)
#else
#define PM_DMA_SAVE_TCM_SIZE    (2048)
#define PM_DMA_RECOVER_TCM_SIZE (4096 + 4096)
#endif
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    oal_uint8  *g_puc_ps_tcm_ptr = (oal_uint8*)(WL_PKT_DRAM_PS_BASEADDR);
#else
    oal_uint8  *g_puc_ps_tcm_ptr = (oal_uint8*)(OAL_PTR_NULL);
#endif

extern oal_uint8  dmac_psm_is_hw_queues_empty(mac_device_stru  *pst_device);
extern oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap);

extern volatile oal_netbuf_stru*    g_pstnetbuff;
oal_uint32  g_ul_wait_log = 0;
oal_uint32  g_ul_wait_hw = 0;
oal_uint32  g_ul_wait_tid = 0;
oal_uint32  g_ul_wait_rx_irq = 0;
oal_uint32  g_ul_coex_cnt  = 0;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

oal_uint8 dmac_psm_check_txrx_state(oal_void)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;
    oal_dlist_head_stru        *pst_current_rx_isr_list;
    dmac_vap_stru                  *pst_dmac_vap;
    oal_uint8                       uc_vap_idx;

    pst_device      = mac_res_get_dev(0);
    pst_hal_device  = pst_device->pst_device_stru;

    pst_current_rx_isr_list = &(pst_hal_device->ast_rx_isr_info_list[0]);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        g_ul_coex_cnt++;
    }
#endif

    /*检查log是否发送完*/
    if(OAL_PTR_NULL != g_pstnetbuff)
    {
        //OAL_IO_PRINT("oam netbuf not empty!\r\n");
        g_ul_wait_log++;
        return OAL_FALSE;
    }

    /*检查接收硬件发送队列和TID队列是否空*/
    if(OAL_FALSE == dmac_psm_is_hw_queues_empty(pst_device))
    {
        //OAL_IO_PRINT("pm check:tx hw queues not empty\r\n");
        g_ul_wait_hw++;
        return OAL_FALSE;
    }


    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);

        if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {

            if(OAL_FALSE == dmac_psm_is_tid_queues_empty(pst_dmac_vap))
            {
                //OAL_IO_PRINT("pm check:tx tid queues not empty\r\n");
                g_ul_wait_tid++;
                 return OAL_FALSE;
            }
        }
    }


    /*检查接收中断是否有残留*/
    if (!oal_dlist_is_empty(pst_current_rx_isr_list))
    {
        //OAL_IO_PRINT("ast_rx_isr_info_list[0] IS NOT EMPTY\r\n");
        g_ul_wait_rx_irq++;
        return OAL_FALSE;

    }

    pst_current_rx_isr_list = &(pst_hal_device->ast_rx_isr_info_list[1]);


    if (!oal_dlist_is_empty(pst_current_rx_isr_list))
    {
        //OAL_IO_PRINT("ast_rx_isr_info_list[1] IS NOT EMPTY\r\n");
        g_ul_wait_rx_irq++;
         return OAL_FALSE;
    }

    return OAL_TRUE;

}
oal_void  dmac_psm_save_mac_hw_reg(hal_to_dmac_device_stru  *pst_hal_device)
{
    hal_reset_reg_save(pst_hal_device, HAL_RESET_HW_TYPE_MAC);
}


oal_void  dmac_psm_save_phy_hw_reg(hal_to_dmac_device_stru  *pst_hal_device)
{
    hal_reset_reg_save(pst_hal_device, HAL_RESET_HW_TYPE_PHY);
}

oal_void dmac_psm_save_tcm (oal_uint8* puc_ch0)
{
    oal_uint8   *puc_netbuf_tcm_addr = g_puc_ps_tcm_ptr;

    /* 保存TCM内存段,BTCM 用DMA搬移,一次最大16KB-4 */
     //MEMCPY(puc_netbuf_tcm_addr, (oal_uint8*)WL_BTCM_BASEADDR, (oal_uint32)WL_BTCM_LEN);
     //puc_netbuf_tcm_addr += WL_BTCM_LEN;

    *puc_ch0 =(oal_uint8)DMAMemoryToMemory((oal_uint32)WL_BTCM_BASEADDR, (oal_uint32)puc_netbuf_tcm_addr, (PM_DMA_SAVE_TCM_SIZE/4),OAL_PTR_NULL);
    puc_netbuf_tcm_addr += PM_DMA_SAVE_TCM_SIZE;

    MEMCPY(puc_netbuf_tcm_addr,(oal_uint8*)(WL_BTCM_BASEADDR + PM_DMA_SAVE_TCM_SIZE),(WL_BTCM_LEN - PM_DMA_SAVE_TCM_SIZE));
    puc_netbuf_tcm_addr += (WL_BTCM_LEN - PM_DMA_SAVE_TCM_SIZE);

    /* 保存ATCM的内容 */
    MEMCPY(puc_netbuf_tcm_addr, (oal_uint8*)WL_ATCM_BASEADDR, (oal_uint32)WL_ATCM_LEN);

    return;

}



oal_uint8 dmac_psm_save_ps_state (oal_void)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;
    oal_uint8                    uc_dmach0;
    //oal_int8                    uc_dmach1;
    //oal_int8                    uc_dmach2;
    //oal_int8                    uc_dmach3;



    pst_device      = mac_res_get_dev(0);

    pst_hal_device  = pst_device->pst_device_stru;

    frw_timer_stop();

    dmac_psm_save_tcm((oal_uint8* )&uc_dmach0);

    /* 保存PHY逻辑与寄存器 */
    dmac_psm_save_phy_hw_reg(pst_hal_device);

   /* 保存MAC逻辑与寄存器 */
    dmac_psm_save_mac_hw_reg(pst_hal_device);

    DMAWaitChannelDone(uc_dmach0);
    //DMAWaitChannelDone(uc_dmach1);
    //DMAWaitChannelDone(uc_dmach2);
    //DMAWaitChannelDone(uc_dmach3);

    return OAL_TRUE;


}


oal_void dmac_psm_init_netbuf_pool(oal_void)
{
    oal_mem_create_netbuf_pool(OAL_MEM_POOL_ID_NETBUF);
}


oal_void  dmac_psm_recover_phy_reg(hal_to_dmac_device_stru  *pst_hal_device)
{
    hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_PHY);
}


oal_void  dmac_psm_recover_mac_reg(hal_to_dmac_device_stru  *pst_hal_device)
{
    hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_MAC);
}


oal_void dmac_psm_recover_tcm (oal_void)
{
    oal_uint8                   *puc_netbuf_tcm_addr = g_puc_ps_tcm_ptr + PM_DMA_RECOVER_TCM_SIZE;

    /* 恢复BTCM的内容 */
   // MEMCPY((oal_uint8*)WL_BTCM_BASEADDR, puc_netbuf_tcm_addr, (oal_uint32)WL_BTCM_LEN);
    //puc_netbuf_tcm_addr += WL_BTCM_LEN;
    MEMCPY((oal_uint8*)(WL_BTCM_BASEADDR + PM_DMA_RECOVER_TCM_SIZE),puc_netbuf_tcm_addr,(WL_BTCM_LEN - PM_DMA_RECOVER_TCM_SIZE));
    puc_netbuf_tcm_addr += (WL_BTCM_LEN - PM_DMA_RECOVER_TCM_SIZE);

    /* 恢复ATCM的内容 */
    MEMCPY((oal_uint8*)WL_ATCM_BASEADDR, puc_netbuf_tcm_addr, (oal_uint32)WL_ATCM_LEN);
    puc_netbuf_tcm_addr += WL_ATCM_LEN;

}


oal_uint8  dmac_psm_recover_ps_phy_state(oal_void)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    mac_device_stru                *pst_device;
    oal_uint                        ul_irq_flag;

    //OAL_IO_PRINT("dmac_psm_recover_ps_phy_state!\r\n");

    pst_device      = mac_res_get_dev(0);
    pst_hal_device  = pst_device->pst_device_stru;

    /* 关中断，在挂起硬件发送之后 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    dmac_psm_recover_phy_reg(pst_hal_device);

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

    return  OAL_TRUE;
}

oal_void dmac_psm_recover_primary_channel(mac_device_stru *pst_device)
{
    hal_to_dmac_device_stru         *pst_h2d_device;
    hal_wifi_channel_status_stru    *pst_wifi_channel_status;

    pst_h2d_device = pst_device->pst_device_stru;

    pst_wifi_channel_status = &(pst_h2d_device->st_wifi_channel_status);

    /* 设置带宽 */
    hal_set_bandwidth_mode(pst_device->pst_device_stru, pst_wifi_channel_status->uc_bandwidth);

    hal_set_primary_channel(pst_device->pst_device_stru,
                   pst_wifi_channel_status->uc_chan_number,
                   pst_wifi_channel_status->uc_band,
                   pst_wifi_channel_status->uc_idx,
                   pst_wifi_channel_status->uc_bandwidth);

}
oal_uint8  dmac_psm_recover_powerdown(oal_uint8 uc_dmach0)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    mac_device_stru                *pst_device;
    oal_uint32                      ul_ret  = OAL_SUCC;
    hal_error_state_stru            st_error_state;

    pst_device      = mac_res_get_dev(0);//和平台沟通，目前先写死是device id，后面有需求再传入参
    pst_hal_device  = pst_device->pst_device_stru;


    /* 内存相关操作 */
    dmac_psm_recover_tcm();

    dmac_psm_recover_phy_reg(pst_hal_device);

    dmac_psm_recover_mac_reg(pst_hal_device);

    frw_timer_restart();

    /* g_st_netbuf_pool不下电, 重新初始化内存池时需清零 */
    OAL_MEMZERO(&g_st_netbuf_pool, OAL_SIZEOF(g_st_netbuf_pool));

	/*rx描述符恢复将操作TCM，必须等待DMA搬移完成*/
    DMAWaitChannelDone(uc_dmach0);

    dmac_psm_init_netbuf_pool();

    /*避免复位过程中接收描述符队列异常，重新初始化接收描述符队列*/
    //hal_rx_destroy_dscr_queue(pst_hal_device,OAL_FALSE);

    //hal_rx_init_dscr_queue(pst_hal_device);

    /* rx dscr挂接netbuf */
#if 1
    hal_rx_dscr_add_netbuf(pst_hal_device,&ul_ret);
    if(ul_ret != OAL_SUCC)
    {
        return (oal_uint8)ul_ret;
    }
#endif

    /* 清中断状态 */
    st_error_state.ul_error1_val = 0xFFFFFFFF;
    st_error_state.ul_error2_val = 0xFFFFFFFF;
    hal_clear_mac_error_int_status(pst_hal_device, &st_error_state);
    hal_clear_mac_int_status(pst_hal_device, 0xffffffff);

    /* SDIO 重新初始化 */
    hcc_slave_reinit();

    //dmac_psm_recover_primary_channel(pst_device);

    /* 在恢复前端时使能pa */
    //hal_enable_machw_phy_and_pa(pst_hal_device);

    return OAL_TRUE;

}



oal_void  dmac_psm_recover_ps_start_dma(oal_uint8 *puc_ch0)
{
    //OAL_IO_PRINT("dmac_psm_recover_ps_start_dma!\r\n");
    oal_uint8                   *puc_netbuf_tcm_addr = g_puc_ps_tcm_ptr;

    /* 恢复BTCM的内容 */
     *puc_ch0 = (oal_uint8)DMAMemoryToMemory((oal_uint32)puc_netbuf_tcm_addr,(oal_uint32)WL_BTCM_BASEADDR, (PM_DMA_RECOVER_TCM_SIZE/4),OAL_PTR_NULL);
}
oal_uint8 dmac_psm_recover_no_powerdown (oal_void)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    mac_device_stru                *pst_device;
    hal_error_state_stru            st_error_state;
    oal_uint32                      ul_ret;

    pst_device      = mac_res_get_dev(0);//和平台沟通，目前先写死是device id，后面有需求再传入参
    pst_hal_device  = pst_device->pst_device_stru;

    frw_timer_restart();

    /* g_st_netbuf_pool不下电, 重新初始化内存池时需清零 */
    OAL_MEMZERO(&g_st_netbuf_pool, OAL_SIZEOF(g_st_netbuf_pool));

    dmac_psm_init_netbuf_pool();

    /*避免复位过程中接收描述符队列异常，重新初始化接收描述符队列*/
    //hal_rx_destroy_dscr_queue(pst_hal_device,OAL_FALSE);
    //hal_rx_init_dscr_queue(pst_hal_device);

    /* rx dscr挂接netbuf */
    hal_rx_dscr_add_netbuf(pst_hal_device, &ul_ret);
    if(ul_ret != OAL_SUCC)
    {
        return (oal_uint8)ul_ret;
    }

     /* 清中断状态 */
    st_error_state.ul_error1_val = 0xFFFFFFFF;
    st_error_state.ul_error2_val = 0xFFFFFFFF;
    hal_clear_mac_error_int_status(pst_hal_device, &st_error_state);
    hal_clear_mac_int_status(pst_hal_device, 0xffffffff);

    /* SDIO 重新初始化 */
    hcc_slave_reinit();

    //dmac_psm_recover_primary_channel(pst_device);

    /* 在恢复前端时使能pa */
    //hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 恢复硬件发送 */
    //hal_set_machw_tx_resume(pst_hal_device);

    return OAL_TRUE;

}
oal_uint8 dmac_psm_cbb_stopwork (oal_void)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;

    pst_device      = mac_res_get_dev(0);

    pst_hal_device  = pst_device->pst_device_stru;

    /* 挂起硬件发送 */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* 关闭pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    return OAL_TRUE;
}


oal_uint8 dmac_psm_lightsleep_stop (oal_void)
{
#if 0
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;

    pst_device      = mac_res_get_dev(0);

    pst_hal_device  = pst_device->pst_device_stru;

    //dmac_psm_recover_primary_channel(pst_device);

    /* 使能pa */
    //hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 恢复硬件发送 */
    //hal_set_machw_tx_resume(pst_hal_device);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    /* 通知bt wifi开始睡眠 */
    hal_set_btcoex_soc_gpreg1(WIFIAWAKE, BIT0 | BIT1, 0);
#endif
#endif
    return OAL_TRUE;
}
oal_void dmac_psm_rf_sleep(oal_uint8 uc_restore_reg)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;

    pst_device      = mac_res_get_dev(0);

    pst_hal_device  = pst_device->pst_device_stru;

    hal_psm_rf_sleep(pst_hal_device, uc_restore_reg);

    return;
}

oal_void dmac_psm_rf_awake (oal_uint8 uc_restore_reg)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    mac_device_stru             *pst_device;

    pst_device      = mac_res_get_dev(0);

    pst_hal_device  = pst_device->pst_device_stru;
    if (OAL_TRUE == uc_restore_reg)
    {
        hal_psm_rf_awake(pst_hal_device,uc_restore_reg);
    }
    dmac_psm_recover_primary_channel(pst_device);

    return;
}




#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

