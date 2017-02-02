
#include <mdrv_pm.h>
#include <bsp_pm_om.h>

#ifndef CONFIG_PM_OM
int bsp_pm_log(u32 magic, u32 data_len , void *data)
{
	return -1;
}

int bsp_pm_log_type(u32 magic, u32 type, u32 data_len , void *data)
{
	return -1;
}

void* bsp_pm_log_addr_get(void)
{
	return NULL;
}

void* bsp_pm_dump_get(u32 magic, u32 len)
{
	return NULL;
}

int bsp_pm_om_dump_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}

int bsp_pm_om_log_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}

void pm_om_wakeup_stat(void){;}
void pm_om_wakeup_log(void){;}

#endif /* CONFIG_PM_OM */

int mdrv_pm_log(int mod_id,  unsigned int data_len , void *data)
{
	if (PM_MOD_AP_OSA == mod_id)
		mod_id = PM_OM_AOSA;
	else if (PM_MOD_CP_OSA == mod_id)
		mod_id = PM_OM_COSA;
	else if (PM_MOD_CP_MSP == mod_id)
		mod_id = PM_OM_CMSP;
	else
		pmom_pr_err("err: invalid mod_id\n");
	return bsp_pm_log((u32)mod_id, data_len, data);
}