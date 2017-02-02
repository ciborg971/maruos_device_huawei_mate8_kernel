

#ifndef __FRW_EVENT_MAIN_H__
#define __FRW_EVENT_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "frw_main.h"
#include "frw_event_sched.h"
#include "wlan_types.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_MAIN_H


/*****************************************************************************
  2 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名  : frw_event_deploy_enum_uint8
  协议表格:
  枚举说明: 事件部署类型
*****************************************************************************/
typedef enum
{
    FRW_EVENT_DEPLOY_NON_IPC  = 0,    /* 非核间通信 */
    FRW_EVENT_DEPLOY_IPC,             /* 核间通讯 */

    FRW_EVENT_DEPLOY_BUTT
}frw_event_deploy_enum;
typedef oal_uint8 frw_event_deploy_enum_uint8;

/*****************************************************************************
  8 宏定义
*****************************************************************************/
/* 事件表的最大个数 */
/* 一种类型的事件对应两个表项，所以事件表的大小为事件类型的2倍 */
#define FRW_EVENT_TABLE_MAX_ITEMS    (FRW_EVENT_TYPE_BUTT * 2)

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/
/*****************************************************************************
      结构名  : frw_event_mgmt_stru
      结构说明: 事件管理结构体
    *****************************************************************************/
    typedef struct
    {
        frw_event_queue_stru          st_event_queue[FRW_EVENT_MAX_NUM_QUEUES];    /* 事件队列 */
        frw_event_sched_queue_stru    st_sched_queue[FRW_SCHED_POLICY_BUTT];         /* 可调度队列 */
    }frw_event_mgmt_stru;
extern frw_event_table_item_stru g_ast_event_table[FRW_EVENT_TABLE_MAX_ITEMS];

extern frw_event_mgmt_stru g_ast_event_manager[WLAN_FRW_MAX_NUM_CORES];

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  frw_event_init(oal_void);
extern oal_uint32  frw_event_exit(oal_void);
extern oal_uint32  frw_event_queue_enqueue(frw_event_queue_stru *pst_event_queue, frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru *frw_event_queue_dequeue(frw_event_queue_stru *pst_event_queue);
extern oal_uint32  frw_event_post_event(frw_event_mem_stru *pst_event_mem, oal_uint32 ul_core_id);
extern oal_void  frw_event_deploy_register(oal_uint32 (*p_func)(frw_event_mem_stru *pst_event_mem, oal_uint8 *puc_deploy_result));
extern oal_void  frw_event_ipc_event_queue_full_register(oal_uint32 (*p_func)(oal_void));
extern oal_void  frw_event_ipc_event_queue_empty_register(oal_uint32 (*p_func)(oal_void));
extern frw_event_sched_queue_stru* frw_event_get_sched_queue(oal_uint32 ul_core_id, frw_sched_policy_enum_uint8 en_policy);
extern oal_void  frw_event_vap_pause_event(oal_uint8 uc_vap_id);
extern oal_void  frw_event_vap_resume_event(oal_uint8 uc_vap_id);
extern oal_uint32  frw_event_vap_flush_event(oal_uint8 uc_vap_id, frw_event_type_enum_uint8 en_event_type, oal_bool_enum_uint8 en_drop);
extern oal_uint32  frw_event_lookup_process_entry(frw_event_mem_stru *pst_event_mem, frw_event_hdr_stru *pst_event_hrd);


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


OAL_STATIC OAL_INLINE oal_uint32  frw_event_to_qid(frw_event_mem_stru *pst_event_mem, oal_uint16 *pus_qid)
{
    oal_uint16            us_qid;
    frw_event_hdr_stru   *pst_event_hrd;

    /* 获取事件头结构 */
    pst_event_hrd = (frw_event_hdr_stru *)pst_event_mem->puc_data;

    us_qid        = pst_event_hrd->uc_vap_id * FRW_EVENT_TYPE_BUTT + pst_event_hrd->en_type;

  /*
    us_qid = (pst_event_hrd->uc_chip_id * (WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE) +
              pst_event_hrd->uc_device_id * (WLAN_VAP_MAX_NUM_PER_DEVICE) + pst_event_hrd->uc_vap_id) *
              FRW_EVENT_TYPE_BUTT + pst_event_hrd->en_type;
  */

    /* 异常: 队列ID超过最大值 */
    if ((us_qid >= FRW_EVENT_MAX_NUM_QUEUES))
    {
        OAM_ERROR_LOG4(0, OAM_SF_FRW, "{frw_event_to_qid, array overflow! us_qid[%d], vap_id[%d], en_type[%d], sub_type[%d]}",
                                        us_qid, pst_event_hrd->uc_vap_id, pst_event_hrd->en_type, pst_event_hrd->uc_sub_type);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    *pus_qid = us_qid;

    return OAL_SUCC;
}
OAL_STATIC OAL_INLINE oal_void  frw_event_report(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru      *pst_event;
    oal_uint8            auc_event[OAM_EVENT_INFO_MAX_LEN] = {0};
#ifdef _PRE_DEBUG_MODE
    oal_uint8            auc_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 复制事件头 */
    oal_memcopy((oal_void *)auc_event, (const oal_void *)&pst_event->st_event_hdr, OAL_SIZEOF(frw_event_hdr_stru));

    FRW_EVENT_INTERNAL(auc_macaddr, 0, OAM_EVENT_INTERNAL, auc_event);
}
OAL_STATIC OAL_INLINE oal_uint32  frw_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_hdr_stru   *pst_event_hrd;
    oal_uint32            ul_core_id;

    /* 获取事件头结构 */
    pst_event_hrd  = (frw_event_hdr_stru *)pst_event_mem->puc_data;

    if (OAL_UNLIKELY(pst_event_hrd->en_pipeline >= FRW_EVENT_PIPELINE_STAGE_BUTT))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* 如果pipleline为0，则将事件入队。否则，
       根据事件类型，子类型以及分段号，执行相应的事件处理函数 */
    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hrd->en_pipeline)
    {
        ul_core_id = OAL_GET_CORE_ID();
        return frw_event_post_event(pst_event_mem, ul_core_id);
    }

    return frw_event_lookup_process_entry(pst_event_mem, pst_event_hrd);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_main.h */
