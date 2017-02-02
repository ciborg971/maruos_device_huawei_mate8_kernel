/*lint --e{537}*/
#include <bsp_dpm.h>
#include <dpm_balong.h>
#include <bsp_om.h>
#include <osl_list.h>

static s32 my_prepare_ok(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s prepare func ok\n",dev->device_name);
	return OK;
}
static s32 my_prepare_error(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s prepare func error\n",dev->device_name);
	return ERROR;
}
static s32 my_suspend_ok(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s suspend func ok\n",dev->device_name);
	return OK;
}
static s32 my_suspend_error(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s suspend func error\n",dev->device_name);
	return ERROR;
}
static s32 my_resume_ok(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s resume func ok\n",dev->device_name);
	return OK;
}
static s32 my_resume_error(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s resume func error\n",dev->device_name);
	return ERROR;
}
static s32 my_complete_ok(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s complete func ok\n",dev->device_name);
	return OK;
}
static s32 my_complete_error(struct dpm_device *dev)
{
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DPM,"%s complete func error\n",dev->device_name);
	return ERROR;
}

struct dpm_device dev0,dev1,dev2,dev3,dev4,dev5,dev6;

/*case01:�������һ����ɾ���豸*/
s32 dpm_test_case01()
{
	s32 ret = 0;
	dev0.device_name = "dev0";
	dev0.complete   = my_complete_ok;
	dev0.prepare   = my_prepare_ok;
	dev0.resume   = my_resume_ok;
	dev0.suspend = my_suspend_ok;
	ret = bsp_device_pm_add(&dev0);
	if(OK != ret)
	{
		return ERROR;
	}
	ret = bsp_device_pm_remove(&dev0);
	if(OK != ret)
	{
		return ERROR;
	}
	return OK;
}


/*case02:����ɾ��һ����ɾ�����豸*/
s32 dpm_test_case02()
{
	s32 ret = 0;
	ret = bsp_device_pm_remove(&dev0);
	if(ERROR == ret)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}


/*case03:���Զ���豸������ʼ����ע�ᵽdpm��������*/
s32 dpm_test_case03()
{
	s32 ret = 0;
	dev1.device_name = "dev1";
	dev1.complete = my_complete_ok;
	dev1.prepare   = my_prepare_ok;
	dev1.resume   = my_resume_ok;
	dev1.suspend = my_suspend_ok;
	dev2.device_name = "dev2";
	dev2.complete = my_complete_ok;
	dev2.prepare   = my_prepare_ok;
	dev2.resume   = my_resume_ok;
	dev2.suspend = my_suspend_ok;
	dev3.device_name = "dev3";
	dev3.complete = my_complete_ok;
	dev3.prepare   = my_prepare_ok;
	dev3.resume   = my_resume_ok;
	dev3.suspend = my_suspend_ok;
	dev4.device_name = "dev4";
	dev4.complete = my_complete_ok;
	dev4.prepare   = my_prepare_ok;
	dev4.resume   = my_resume_ok;
	dev4.suspend = my_suspend_ok;
	dev5.device_name = "dev5";
	dev5.complete = my_complete_ok;
	dev5.prepare   = my_prepare_ok;
	dev5.resume   = my_resume_ok;
	dev5.suspend = my_suspend_ok;
	ret = bsp_device_pm_add(&dev1);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	ret = bsp_device_pm_add(&dev2);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	ret = bsp_device_pm_add(&dev3);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	ret = bsp_device_pm_add(&dev4);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	ret = bsp_device_pm_add(&dev5);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	return OK;
}

/*case04:�����豸�����лص��������ܷ���OK,
    ����suspend�����ܷ�������豸����ת�Ƶ�suspend����*/
s32 dpm_test_case04()
{
	s32 ret = 0;
	ret = bsp_dpm_suspend();
	if(ret ==ERROR)
	{
		return ERROR;
	}
	bsp_dpm_resume();
	return OK;
}

/*case5:���豸5���Ϸ��ش���ֵ��prepare������
              ���Թ۲�suspend����;ʱ�Ƿ��ָ��Ѿ�suspend���豸*/
s32 dpm_test_case05()
{
	s32 ret = 0;
	ret=bsp_device_pm_remove(&dev5);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	dev5.prepare = my_prepare_error;
	ret = bsp_device_pm_add(&dev5);
	 if(ret ==ERROR)
	 {
		 return ERROR;
	 }
	 ret = bsp_dpm_suspend();
	 if(ret ==ERROR)
	 {
		return OK;
	 }
	 else
	 	return ERROR;
}
/*case06:���豸5���Ϸ��ش���ֵ��suspend������
              ���Թ۲�suspend����;ʱ�Ƿ��ָ��Ѿ�suspend���豸*/
s32 dpm_test_case06()
{
	s32 ret = 0;
	ret=bsp_device_pm_remove(&dev5);
	if(ret ==ERROR)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"remove error\n");
		return ERROR;
	}
	dev5.prepare= my_prepare_ok;
	dev5.suspend = my_suspend_error;
	ret = bsp_device_pm_add(&dev5);
	 if(ret ==ERROR)
	 {
	 	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"add error\n");
		 return ERROR;
	 }
	 ret = bsp_dpm_suspend();
	 if(ret ==ERROR)
	 {
		return OK;
	 }
	 else
	 	return ERROR;
}
/*case7:���豸5���Ϸ��ش���ֵ��complete�ص�������
              ���Թ۲�resume�Ƿ�᷵�ش��󲢴�ӡ��ش���log*/
s32 dpm_test_case07()
{
	s32 ret = 0;
	ret=bsp_device_pm_remove(&dev5);
	if(ret ==ERROR)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"remove error\n");
		return ERROR;
	}
	dev5.suspend = my_suspend_ok;
	dev5.complete = my_complete_error;
	ret = bsp_device_pm_add(&dev5);
	 if(ret ==ERROR)
	 {
	 	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"add error\n");
		 return ERROR;
	 }
	 
	 ret = bsp_dpm_suspend();
	 if(ret ==ERROR)
	 	return ERROR;
	 bsp_dpm_resume();
	 return OK;
}
/*case8:���豸4���Ϸ��ش���ֵ��resume�ص�������
              ���Թ۲�resume�Ƿ�᷵�ش��󲢴�ӡ��ش���log*/
s32 dpm_test_case08()
{
	s32 ret = 0;
	ret=bsp_device_pm_remove(&dev4);
	if(ret ==ERROR)
	{
		return ERROR;
	}
	dev4.resume = my_resume_error;
	dev4.complete = my_complete_ok;
	ret = bsp_device_pm_add(&dev4);
	 if(ret ==ERROR)
	 {
		 return ERROR;
	 }
	 
	 ret = bsp_dpm_suspend();
	 if(ret ==ERROR)
	 	return ERROR;
	 bsp_dpm_resume();	
	 /*DPMģ����Խ���,������*/
	 list_del_init(&dev1.entry);
	 list_del_init(&dev2.entry);
	 list_del_init(&dev3.entry);
	 list_del_init(&dev4.entry);
	 list_del_init(&dev5.entry);
	 return OK;
}

s32 dpm_test()
{
	s32 ret = 0;
	ret = dpm_test_case01();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case01 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case01 fail\n");
	}
	ret = dpm_test_case02();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case02 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case02 fail\n");
	}
	ret = dpm_test_case03();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case03 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case03 fail\n");
	}
	ret = dpm_test_case04();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case04 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case04 fail\n");
	}
	ret = dpm_test_case05();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case05 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case05 fail\n");
	}
	ret = dpm_test_case06();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case06 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case06 fail\n");
	}
	ret = dpm_test_case07();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case07 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case07 fail\n");
	}
	ret = dpm_test_case08();
	if(OK == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case08 pass\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_DPM,"dpm_test_case08 fail\n");
	}
	return 0;
}
