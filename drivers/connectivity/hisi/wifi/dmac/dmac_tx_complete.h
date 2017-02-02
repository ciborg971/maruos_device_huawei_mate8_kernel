

#ifndef __DMAC_TX_COMPLETE_H__
#define __DMAC_TX_COMPLETE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "mac_device.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_user.h"
#include "dmac_vap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_stat.h"
#include "dmac_main.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_COMPLETE_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint8 g_uc_aggr_num_switch;     /* 设置最大AMPDU聚合个数开关 */
extern oal_uint8 g_uc_max_aggr_num;     /* 设置最大AMPDU聚合个数 */


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_tx_complete_event_handler(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_tx_reset_flush(hal_to_dmac_device_stru *pst_device);
extern oal_uint32  dmac_tx_complete_schedule(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ac_num);
#if 0
extern oal_void  dmac_tx_delete_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_delete_dscr);
#endif
extern oal_uint32  dmac_tx_complete_buff(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_dscr);
extern oal_uint32  dmac_mgmt_tx_complete(mac_vap_stru *pst_mac_vap, oal_uint8 mgmt_frame_id, oal_uint32 uc_dscr_status, oal_uint8 uc_user_idx);
extern oal_void  dmac_tx_complete_free_dscr(hal_tx_dscr_stru *pst_dscr);
extern oal_void  dmac_tx_complete_free_dscr_list(hal_tx_dscr_stru *pst_dscr, oal_uint8 uc_dscr_num);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_tx_complete.h */
