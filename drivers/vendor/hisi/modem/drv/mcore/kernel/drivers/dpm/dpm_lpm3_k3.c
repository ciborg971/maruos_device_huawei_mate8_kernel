/*lint --e{537,551}*/
#include "dpm_balong.h"
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_ipf.h>
#include <bsp_hardtimer.h>
#include <temperature.h>
#include <bsp_pmu_hi6561.h>
static u32 pm_suspend_flag ;
static u32 pm_resume_flag ;

/*��ά����������¼��ά�ɲ���Ϣ:
  *0 suspendʧ�ܴ�����
  *1 resumeʧ�ܴ�����
  *�������һ�����ڼ�¼�ֱ����suspend��resume�ܴ���
  */
__ao_data static u32 dpm_debug[DPM_BUTTON+1][2]={{0,0},{0,0},{0,0},{0,0},{0,0}};
/*lint --e{732}*/

/*��ģ����дʱ��ע��suspend˳����resume˳���෴*/
static s32 enter_suspend_and_resume(u32 pm_msg)
{
	u32 ret = 0;
	pm_suspend_flag = 0;
	pm_resume_flag = 0;
	if(PMSG_SUSPEND==pm_msg){
		/*��ά�ɲ⣬��¼����suspend�ܴ���*/
		dpm_debug[DPM_BUTTON][0]++;
		/*����֧�ص����豸��suspend�ص�������˳�����¼�*/

		ret = bsp_icc_suspend();
		if(ret != 0)
		{
			pm_suspend_flag = 1;
		    goto end;
		}
		ret=tem_protect_suspend();
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_TEM][0] +=1;
			goto end;
		}
		ret = ipf_drx_bak_reg();
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_IPF][0] +=1;
			goto tem_resume;
		}
		bsp_ipc_suspend();
    }
	else if(PMSG_RESUME==pm_msg){
		dpm_debug[DPM_BUTTON][1]++;/*��ά�ɲ⣬��¼����resume�ܴ���*/
		/*����֧�ص����豸��resume�ص�����,˳�����ϼ�*/
		bsp_ipc_resume();
		ipf_drx_restore_reg();
tem_resume:
		tem_protect_resume();


	}
end:
	if(PMSG_SUSPEND==pm_msg)
	{
		if(0==pm_suspend_flag)
			return DPM_OK;
		else
			return DPM_ERROR;
	}
	if(PMSG_RESUME==pm_msg)
	{
        if(0==pm_resume_flag)
			return DPM_OK;
		else
			return DPM_ERROR;
	}
	return DPM_OK;
}

s32 dpm_suspend(void)
{
	s32 ret = 0;
	ret = enter_suspend_and_resume(PMSG_SUSPEND);
	return ret;
}
s32 dpm_resume(void)
{
	s32 ret = 0;
	ret = enter_suspend_and_resume(PMSG_RESUME);
	return ret;
}
#if 0
void bsp_dpm_show(void)
{
	int i = 0;
	printk("id\tsuspend_failed_times\tresume_failed_times\n");
	for(i=0;i<DPM_BUTTON;i++){
		printk("%d\t%d\t\t%d\n",i,dpm_debug[i][0],dpm_debug[i][1]);
	}
	printk("total suspend:%d\n total resume:%d\n",dpm_debug[DPM_BUTTON][0],dpm_debug[DPM_BUTTON][1]);
}
#endif
