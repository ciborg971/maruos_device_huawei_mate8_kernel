


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_schedule.h"

#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
}


oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer)
{

    return 0;
}


oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer)
{

    return 0;
}


oal_void  oal_timer_add(oal_timer_list_stru *pst_timer)
{
}


oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_expires)
{

#ifdef  _PRE_WIFI_DMT
	DmtStub_StartTimer(MGMT_TIMER, ui_expires);  /*15ms 的定时任务，触发frw_timer_timeout_proc_event */
#endif

    return OAL_SUCC;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

