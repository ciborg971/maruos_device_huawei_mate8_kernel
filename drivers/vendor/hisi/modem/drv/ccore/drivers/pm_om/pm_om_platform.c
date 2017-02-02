
#include <securec.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"

struct pm_om_platform g_pmom_platform;

/*
 * pm_om_fwrite_trigger - trigger file write from log buffer
 */
int pm_om_fwrite_trigger(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	u32 timestamp = 0;

	/* 确认是否需要唤醒acore */
	if (ctrl->log.app_is_alive)
	{
		timestamp = bsp_get_slice_value();
		if ((timestamp - g_pmom_platform.timestamp) > g_pmom_platform.wakeup_interval)
		{
			bsp_ipc_int_send((IPC_INT_CORE_E)IPC_CORE_ACORE, (IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_PM_OM);
		}

		g_pmom_platform.timestamp = bsp_get_slice_value();
	}
	return PM_OM_OK;
}

s32 pm_om_icc_handler(u32 channel_id , u32 len, void *context)
{
	pm_om_icc_data_type data = 0;
	s32 ret = PM_OM_OK;

	ret = bsp_icc_read(channel_id, (u8 *)&data, sizeof(data));
	if(sizeof(data) != (u32)ret)
	{
		pmom_pr_err("icc read fail: 0x%x\n", ret);
		return ret;
	}

	if (data)
	{
		g_pmom_platform.ctrl->log.init_flag = PM_OM_INIT_MAGIC;
	}
	else
	{
		g_pmom_platform.ctrl->log.init_flag = 0;
	}

	return PM_OM_OK;
}

int pm_om_platform_init(void)
{
	u32 channel_id = 0;
	struct pm_om_ctrl *ctrl  = pm_om_ctrl_get();

	(void)memset_s((void *)&g_pmom_platform, sizeof(g_pmom_platform), 0, sizeof(g_pmom_platform));
	g_pmom_platform.timestamp       = bsp_get_slice_value();
	g_pmom_platform.wakeup_interval = PM_OM_WAKEUP_INTERVAL;

	channel_id = PM_OM_ICC_CHN_ID;
	if (ICC_OK != bsp_icc_event_register(channel_id, pm_om_icc_handler, NULL, NULL, NULL))
	{
		return PM_OM_ERR;
	}

	g_pmom_platform.ctrl = ctrl;
	ctrl->platform = (void *)&g_pmom_platform;
	return PM_OM_OK;
}