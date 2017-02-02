
#include <mdrv_pm.h>
#include <bsp_cpufreq.h>
#include <drv_comm.h>
#ifdef __cplusplus
extern "C"
{
#endif

int g_cpufreq_max_profile = 5;
int g_cpufreq_ddr_max_profile = 6;
int  cpufreq_init(void)
{
    return 0;
}
/*�ṩpm���̵��ã��������Ƶ��CPU/DDR*/
void cpufreq_set_max_freq(void)
{
	
}
void cpufreq_debug_set_target(unsigned int msg_type, unsigned int source, unsigned int content, unsigned int profile)
{
}
void cpufreq_debug_stop(int flag, int enable)
{
}
/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_GetCcpuLoadCB
 ��������  : arm �ṩ��TTF�Ļص�����
 �������  : pFunc:TTF����ָ��
 �������  : ��
 �� �� ֵ  : ����ռ�ĵ�ַ ��
*****************************************************************************/
 void cpufreq_ttf_get_cpuload_cb(PWRCTRLFUNCPTR pFunc )
 {
	(void)(*pFunc)(1);
 }

/*
 * ��ȡ��ǰprofile
 */
int cpufreq_dfs_get_profile()
{
	return 0;
}
/*
 * ����profile
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_profile(int profile)
{
	return MDRV_OK;
}

/*
 * ����profile����
 * success: return BSP_OK	
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_baseprofile(int baseprofile)
{
	return MDRV_OK;
}

/*
 * ������Ƶ lock=0����;lock=1����
 */
void cpufreq_dfs_lock(u32 lock)
{
	
}

/*
 * ���Խӿڣ�����Ƶ�� BSP_ERROR ����ʧ��;BSP_OK ���óɹ�
 *
 */
int cpufreq_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return MDRV_OK;
}

int cpufreq_dfs_current(int *a9freq, int *ddrfreq, int *slowfreq)
{
	return MDRV_OK;
}

void cpufreq_update_frequency(void)
{
	
}
void cpufreq_checkload_in_sysint(void)
{

}
/*for v9r1*/
BSP_S32 cpufreq_qos_request(BSP_S32 qos_id, BSP_U32 req_value, BSP_S32 *req_id)
{
	return MDRV_OK;
}
BSP_S32 cpufreq_qos_release(BSP_S32 qos_id, BSP_S32 *req_id)
{
	return MDRV_OK;
}
BSP_S32 cpufreq_qos_update(BSP_S32 qos_id, BSP_S32 req_id, BSP_U32 req_value)
{
	return MDRV_OK;
}


/********************************new interface start ***********************************/
void mdrv_pm_register_ccpuload_cb(PWRCTRLFUNCPTR pFunc )
{
	cpufreq_ttf_get_cpuload_cb(pFunc);
}
int mdrv_pm_get_ccpuload(unsigned int *ptrCCpuLoad)
{
	return MDRV_OK;
}

 /*
 * ��ȡ��ǰprofile ��Χ
 */
 int mdrv_pm_get_dfs_profile_limit(struct mdrv_pm_profile *profile_limit)
{
	if (NULL == profile_limit)
	{
		return MDRV_ERROR;
	}
	profile_limit->max_profile = 4;
	profile_limit->min_profile = 0;
	return MDRV_OK;
}
int mdrv_pm_dfs_qos_get(int qos_id, unsigned int req_value, int* req_id)
{
	return cpufreq_qos_request(qos_id, req_value, req_id);
}

int mdrv_pm_dfs_qos_put(int qos_id, int* req_id)
{
	return cpufreq_qos_release(qos_id, req_id);
}

int mdrv_pm_dfs_qos_update(int qos_id, int req_id, unsigned int req_value)
{
	return cpufreq_qos_update(qos_id, req_id, req_value);
}

int mdrv_pm_get_dfs_profile(void)
{
	return cpufreq_dfs_get_profile();
}

int mdrv_pm_set_dfs_profile(int profile)
{
	return cpufreq_dfs_set_profile(profile);
}

int mdrv_pm_set_dfs_baseprofile(int profile)
{
	return cpufreq_dfs_set_baseprofile(profile);
}

void mdrv_pm_lock_dfs(unsigned int lock)
{
	cpufreq_dfs_lock(lock);
}

int mdrv_pm_set_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return	cpufreq_dfs_target(a9freq, ddrfreq, slowfreq);
}
/********************************new interface end ***********************************/

#ifdef __cplusplus
}
#endif

