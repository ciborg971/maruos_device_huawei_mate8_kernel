
/*lint --e{530, 801,830,539}*/

#include <securec.h>
#include <bsp_dpm.h>
#include <bsp_hardtimer.h>
#include <bsp_dump_drv.h>
#include <bsp_pm_om.h>
#include "dpm_balong.h"

u32 dpm_dump_drx_c_addr = 0;

#define DPM_DUMP_START      (dpm_dump_drx_c_addr+CDRX_DUMP_DPM_OFFSET)
#define DPM_DUMP_SIZE       (CDRX_DUMP_DPM_SIZE)
#define DPM_CNT_RECORD_ADDR (DPM_DUMP_START)
#define DPM_STAMP_START     (DPM_CNT_RECORD_ADDR+0x10)


/* ASCII define  */
enum dpm_ascii{
    /**/
    dpm_asc_dpm = 0x006D7064,/*  ASCII = "dpm " */
    dpm_asc_cnt = 0x00746E63,/*  ASCII = "cnt " */

    /* asc for dpm steps*/
    dpm_asc_sus_prepare  = 0x56727053,/*  ASCII = "Spre" */
    dpm_asc_sus_early    = 0x72616553,/*  ASCII = "Sear" */
    dpm_asc_sus_suspend  = 0x73757353,/*  ASCII = "Ssus" */
    dpm_asc_sus_late     = 0x74616C53,/*  ASCII = "Slat" */
    dpm_asc_res_early    = 0x72616552,/*  ASCII = "Rear" */
    dpm_asc_res_resume   = 0x76657252,/*  ASCII = "Sres" */
    dpm_asc_res_late     = 0x74616C52,/*  ASCII = "Slat" */
    dpm_asc_res_complete = 0x6D6F6352,/*  ASCII = "Scom" */
    
    dpm_asc_in           = 0x5F6E695F,/*  ASCII = "_in_" */
    dpm_asc_out          = 0x5F74756F,/*  ASCII = "out_" */
    dpm_asc_fail         = 0x6C696166,/*  ASCII = "fail" */
};

void bsp_dpm_suspend_cnt(u32 cnt)
{
    writel( dpm_asc_dpm, DPM_CNT_RECORD_ADDR);
    writel( dpm_asc_cnt, DPM_CNT_RECORD_ADDR+0x4);
    writel( cnt, DPM_CNT_RECORD_ADDR+0x8);
}
void bsp_dpm_resume_cnt(u32 cnt)
{    writel( cnt, DPM_CNT_RECORD_ADDR+0xC);}



u32 g_dpm_index = 0;
void dpm_stamp_reset(void)
{
    if(dpm_dump_drx_c_addr)
    {
        g_dpm_index = 0;
    }
}

void dpm_stamp_step_head(u32 step)
{
    if(dpm_dump_drx_c_addr)
    {
        g_dpm_index++;
        /*  ASCII = step+"_in_out_fail" */ 
        writel( step, DPM_STAMP_START+g_dpm_index*0x10);
        writel( dpm_asc_in, DPM_STAMP_START+g_dpm_index*0x10+0x4);
        writel( dpm_asc_out, DPM_STAMP_START+g_dpm_index*0x10+0x8);
        writel( dpm_asc_fail, DPM_STAMP_START+g_dpm_index*0x10+0xc);
    }
}


void dpm_stamp_in(u32 ops_addr)
{
    if(dpm_dump_drx_c_addr)
    {
        g_dpm_index++;
        writel(ops_addr, DPM_STAMP_START+g_dpm_index*0x10);
        writel( bsp_get_slice_value(), DPM_STAMP_START+g_dpm_index*0x10+4);
    }
}
void dpm_stamp_out(u32 fail_cnt)
{
    if(dpm_dump_drx_c_addr)
    {
        writel( bsp_get_slice_value(), DPM_STAMP_START+g_dpm_index*0x10+0x8);
        writel( fail_cnt, DPM_STAMP_START+g_dpm_index*0x10+0xC);
    }
}
void dpm_stamp_fail_cnt(u32 fail_cnt)
{
    if(dpm_dump_drx_c_addr)
    {
        writel( fail_cnt, DPM_STAMP_START+g_dpm_index*0x10+0xC);
        (void)bsp_pm_log(PM_OM_DPM, 0x10, (void*)(DPM_STAMP_START+g_dpm_index*0x10));
    }
}

/*lint --e{826, 525 } */
/*记录可维可测回调级别*/
enum dpm_stat_enum{
	PREPARE,
	SUS_EARLY,
	SUSPEND,
	LATE,
	EARLY,
	RESUME,
	RES_LATE,
	COMPLETE
};
struct dpm_control dpm_ctrl;
s32 bsp_device_pm_add(struct dpm_device *dev)
{
	 /*lint -save -e516*/
	 int i = 0;
	 unsigned long flags = 0;
	 spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);
	if(NULL!=dev)
	{
		INIT_LIST_HEAD(&dev->entry);
		for(i = 0;i<DPM_CALLBACK_NUM;i++)
			dev->debug_count[i] = 0;
		list_add_tail(&dev->entry,&(dpm_ctrl.dpm_list));
	} 
	else
	{
		dpm_print("the dev to add is NULL\n");
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);
		return ERROR;
	}
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
}

s32 bsp_device_pm_remove(struct dpm_device *dev)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	if((NULL!=dev)&&(!list_empty(&dev->entry)))
	{
		list_del_init(&dev->entry);
	}
	else
	{
		dpm_print("the dev to remove is NULL or is already removed\n");
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return ERROR;
	}
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
}

void update_max_duration(struct dpm_device *dev, enum dpm_stat_enum step)
{
    u32 duration = 0;
    duration = get_timer_slice_delta(dev->debug_time[step][0], dev->debug_time[step][1]);
    if(duration > dev->max_duration[step])
    {
        dev->max_duration[step] = duration;
    }
}
static void dpm_resume_early()
{
	unsigned long flags = 0;
	struct dpm_device *dev,*next;
	s32 ret=0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_res_early);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_late_early_list),entry)
	{
		if(dev->resume_early)
		{
			dpm_ctrl.current_callback = dev->resume_early;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[EARLY][0] = bsp_get_slice_value();
            DWB(); 
            dpm_stamp_in((u32)dev->resume_early);
			ret = dev->resume_early(dev);
            dpm_stamp_out(dev->debug_count[EARLY]);
			dev->debug_time[EARLY][1] = bsp_get_slice_value();
            update_max_duration(dev, EARLY);
			dpm_ctrl.flag = 0;
            DWB();
			if(OK!=ret)
			{
				/*如果resume_early失败，则打印，并跳过此设备继续resume下一个设备*/
				dev->debug_count[EARLY]++;
                dpm_stamp_fail_cnt(dev->debug_count[EARLY]);
				continue;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_suspend_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
}
static void dpm_resume()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_res_resume);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_suspend_list),entry)
	{
		if(dev->resume)
		{
			dpm_ctrl.current_callback = dev->resume;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[RESUME][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->resume);
			ret = dev->resume(dev);
            dpm_stamp_out(dev->debug_count[RESUME]);
			dev->debug_time[RESUME][1] = bsp_get_slice_value();
            update_max_duration(dev, RESUME);
			dpm_ctrl.flag = 0;
           DWB();
			if(OK!=ret)
			{
				/*如果resume失败，则打印，并跳过此设备继续resume下一个设备*/
				dev->debug_count[RESUME]++;
                dpm_stamp_fail_cnt(dev->debug_count[RESUME]);
				continue;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_sus_early_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
}

static void dpm_resume_late()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_res_late);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_sus_early_list),entry)
	{
		if(dev->resume_late)
		{
			dpm_ctrl.current_callback = dev->resume_late;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[RES_LATE][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->resume_late);
			ret = dev->resume_late(dev);
            dpm_stamp_out(dev->debug_count[RES_LATE]);
			dev->debug_time[RES_LATE][1] = bsp_get_slice_value();
            update_max_duration(dev, RES_LATE);
			dpm_ctrl.flag = 0;
            DWB();
			if(OK!=ret)
			{
				/*如果resume失败，则打印，并跳过此设备继续resume下一个设备*/
				dev->debug_count[RES_LATE]++;
                dpm_stamp_fail_cnt(dev->debug_count[RES_LATE]);
				continue;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_prepared_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
}


static void dpm_complete()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_res_complete);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_prepared_list),entry)
	{
		if(dev->complete)
		{
			dpm_ctrl.current_callback = dev->complete;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[COMPLETE][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->complete);
			ret = dev->complete(dev);
            dpm_stamp_out(dev->debug_count[COMPLETE]);
			dev->debug_time[COMPLETE][1] = bsp_get_slice_value();
            update_max_duration(dev, COMPLETE);
			dpm_ctrl.flag = 0;
            DWB();
			if(OK!=ret)
			{
				/*如果complete失败，则打印，并跳过此设备继续complete下一个设备*/
				dev->debug_count[COMPLETE]++;
                dpm_stamp_fail_cnt(dev->debug_count[COMPLETE]);
				continue;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
}
void bsp_dpm_resume()
{  
	dpm_resume_early();
	dpm_resume();
	dpm_resume_late();
	dpm_complete();
	dpm_ctrl.dpm_count[DPM_CNT_R_TOTAL]++;/*resume times*/
    bsp_dpm_resume_cnt(dpm_ctrl.dpm_count[DPM_CNT_R_TOTAL]);
}
static s32 dpm_prepare()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_sus_prepare);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_list),entry)
	{
		if(dev->prepare)
		{
			dpm_ctrl.current_callback = dev->prepare;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[PREPARE][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->prepare);
			ret = dev->prepare(dev);
            dpm_stamp_out(dev->debug_count[PREPARE]);
			dev->debug_time[PREPARE][1] = bsp_get_slice_value();
            update_max_duration(dev, PREPARE);
			dpm_ctrl.flag = 0;
           DWB();
			if(OK!=ret)
			{
				dev->debug_count[PREPARE]++;
                dpm_stamp_fail_cnt(dev->debug_count[PREPARE]);
				spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
				goto complete;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_prepared_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
	
	complete:
		bsp_dpm_resume();
		return ERROR;	
}

static s32 dpm_suspend_early()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_sus_early);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_prepared_list),entry)
	{
		if(dev->suspend_early)
		{
			dpm_ctrl.current_callback = dev->suspend_early;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[SUS_EARLY][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->suspend_early);
			ret = dev->suspend_early(dev);
            dpm_stamp_out(dev->debug_count[SUS_EARLY]);
			dev->debug_time[SUS_EARLY][1] = bsp_get_slice_value();
            update_max_duration(dev, SUS_EARLY);
			dpm_ctrl.flag = 0;
            DWB();
			if(OK!=ret)
			{
				dev->debug_count[SUS_EARLY]++;
                dpm_stamp_fail_cnt(dev->debug_count[SUS_EARLY]);
				spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
				goto resume;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_sus_early_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
	
	resume:
		bsp_dpm_resume();/*suspend阶段出错，需要回退执行已经suspend的各设备的resume和complete回调*/
		return ERROR;
	
}

static s32 dpm_suspend()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_sus_suspend);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_sus_early_list),entry)
	{
		if(dev->suspend)
		{
			dpm_ctrl.current_callback = dev->suspend;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[SUSPEND][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->suspend);
			ret = dev->suspend(dev);
            dpm_stamp_out(dev->debug_count[SUSPEND]);
			dev->debug_time[SUSPEND][1] = bsp_get_slice_value();
            update_max_duration(dev, SUSPEND);
			dpm_ctrl.flag = 0;
            DWB();
			if(OK!=ret)
			{
				dev->debug_count[SUSPEND]++;
                dpm_stamp_fail_cnt(dev->debug_count[SUSPEND]);
				spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
				goto resume;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_suspend_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
	
	resume:
		bsp_dpm_resume();/*suspend阶段出错，需要回退执行已经suspend的各设备的resume和complete回调*/
		return ERROR;
	
}
static s32 dpm_suspend_late()
{
	struct dpm_device *dev,*next;
	s32 ret=0;
	unsigned long flags = 0;
	spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
    dpm_stamp_step_head(dpm_asc_sus_late);
	list_for_each_entry_safe(dev,next,&(dpm_ctrl.dpm_suspend_list),entry)
	{
		if(dev->suspend_late)
		{
			dpm_ctrl.current_callback = dev->suspend_late;
			dpm_ctrl.device_name = dev->device_name;
			dpm_ctrl.flag = 1;
			dev->debug_time[LATE][0] = bsp_get_slice_value();
            DWB();
            dpm_stamp_in((u32)dev->suspend_late);
			ret = dev->suspend_late(dev);
            dpm_stamp_out(dev->debug_count[LATE]);
			dev->debug_time[LATE][1] = bsp_get_slice_value();
            update_max_duration(dev, LATE);
			dpm_ctrl.flag = 0;
           DWB();
			if(OK!=ret)
			{
				dev->debug_count[LATE]++;
                dpm_stamp_fail_cnt(dev->debug_count[LATE]);
				spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
				goto resume;
			}
		}
		list_move_tail(&dev->entry,&(dpm_ctrl.dpm_late_early_list));
	} 
	spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
	return OK;
	
	resume:
		bsp_dpm_resume();
		return ERROR;
	
}

s32 bsp_dpm_suspend()
{
	s32 ret = 0;
    dpm_stamp_reset();
	dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL]++;/*total suspend times*/
    bsp_dpm_suspend_cnt(dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL]);
	ret = dpm_prepare();
	if(OK!=ret)
	{
		dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_PREPARE]++;/*prepare error times*/
		return ERROR;
	}
	ret = dpm_suspend_early();
	if(OK!=ret)
	{
		dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_EARLY]++;/*suspend error times*/
		return ERROR;
	}
	ret = dpm_suspend();
	if(OK!=ret)
	{
		dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_SUSPEND]++;/*suspend late error times*/
		return ERROR;
	}
	ret = dpm_suspend_late();/*suspend realy late error times*/
	if(OK!=ret)
	{
		dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_LATE]++;
		return ERROR;
	}
	return OK;
}

/*在串口调试使用*/
s32 bsp_dpm_suspend_single(char *dev_name)
{
	s32 ret = 0;
	struct dpm_device *cur;
	unsigned long flags = 0;
	if(NULL == dev_name)
	{
		dpm_print("null para\n");
		return ERROR;
	}
	else
	{
		spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		list_for_each_entry(cur,&(dpm_ctrl.dpm_list),entry)
		{
			ret = strcmp(cur->device_name,dev_name);
			if(0==ret)
			{
				dpm_ctrl.device_name = dev_name;
				break;
			}
		}
		/*如果未查到匹配项返回错误*/
		if(&cur->entry == &(dpm_ctrl.dpm_list))
		{
			dpm_print("dev not in list\n");
			goto failed;
		}
		if(cur->prepare)
		{
			dpm_ctrl.current_callback = cur->prepare;
			dpm_ctrl.flag = 1;
			cur->debug_time[PREPARE][0]=bsp_get_slice_value();
			ret = cur->prepare(cur);
			cur->debug_time[PREPARE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[PREPARE]++;
				goto failed;
			}
		}
		/*prepare成功执行后，移入prepared链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_prepared_list));
		if(cur->suspend_early)
		{
			dpm_ctrl.current_callback = cur->suspend_early;
			dpm_ctrl.flag = 1;
			cur->debug_time[SUS_EARLY][0]=bsp_get_slice_value();
			ret = cur->suspend_early(cur);
			cur->debug_time[SUS_EARLY][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[SUS_EARLY]++;
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->suspend;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
				}
				goto failed;
			}
		}
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_sus_early_list));
		if(cur->suspend)
		{
			dpm_ctrl.current_callback = cur->suspend;
			dpm_ctrl.flag = 1;
			cur->debug_time[SUSPEND][0]=bsp_get_slice_value();
			ret = cur->suspend(cur);
			cur->debug_time[SUSPEND][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[SUSPEND]++;
				if(cur->resume_late)
				{
					dpm_ctrl.current_callback = cur->resume_late;
					dpm_ctrl.flag = 1;
					cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
					ret = cur->resume_late(cur);
					cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RES_LATE]++;
					}
					goto failed;
				}
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->suspend;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					/* coverity[copy_paste_error] */
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
					goto failed;
				}				
			}
		}
		/*suspend成功执行后，移入suspend链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_suspend_list));
		if(cur->suspend_late)
		{
			dpm_ctrl.current_callback = cur->suspend_late;
			dpm_ctrl.flag = 1;
			cur->debug_time[LATE][0]=bsp_get_slice_value();
			ret = cur->suspend_late(cur);
			cur->debug_time[LATE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[LATE]++;
				if(cur->resume)
				{
					dpm_ctrl.current_callback = cur->resume;
					dpm_ctrl.flag = 1;
					cur->debug_time[RESUME][0]=bsp_get_slice_value();
					ret = cur->resume(cur);
					cur->debug_time[RESUME][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RESUME]++;
					}
					goto failed;
				}
				if(cur->resume_late)
				{
					dpm_ctrl.current_callback = cur->resume_late;
					dpm_ctrl.flag = 1;
					cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
					ret = cur->resume_late(cur);
					cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RES_LATE]++;
					}
					goto failed;
				}
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->complete;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					/* coverity[original] */
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
					goto failed;
				}		
			}
		}
		/*suspend late成功执行后，移入late early链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_late_early_list));
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return OK;
	}
	failed:
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return ERROR;
}
/*在串口调试使用*/
s32 bsp_dpm_resume_single(char *dev_name)
{
	s32 ret = 0;
	struct dpm_device *cur;
	unsigned long flags = 0;
	if(NULL == dev_name)
	{
		dpm_print("[%s]:null para\n");
		return ERROR;
	}
	else
	{
		spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		list_for_each_entry(cur,&(dpm_ctrl.dpm_late_early_list),entry)
		{
			ret = strcmp(cur->device_name,dev_name);
			if(0==ret)
			{
				dpm_ctrl.device_name = dev_name;
				break;
			}
		}
		/*如果未查到匹配项返回错误*/
		if(&cur->entry == &(dpm_ctrl.dpm_late_early_list))
		{
			dpm_print("dev not in list\n");
			goto failed;
		}
		if(cur->resume_early)
		{
			dpm_ctrl.current_callback = cur->resume_early;
			dpm_ctrl.flag = 1;
			cur->debug_time[EARLY][0]=bsp_get_slice_value();
			ret = cur->resume_early(cur);
			cur->debug_time[EARLY][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[EARLY]++;
				goto failed;
			}
		}
		/*resume early 成功执行后，移入到suspend链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_suspend_list));
		if(cur->resume)
		{
			dpm_ctrl.current_callback = cur->resume;
			dpm_ctrl.flag = 1;
			cur->debug_time[RESUME][0]=bsp_get_slice_value();
			ret = cur->resume(cur);
			cur->debug_time[RESUME][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[RESUME]++;
				goto failed;
			}
		}
		/*resume成功执行后，移入到prepared链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_sus_early_list));
		if(cur->resume_late)
		{
			dpm_ctrl.current_callback = cur->resume_late;
			dpm_ctrl.flag = 1;
			cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
			ret = cur->resume_late(cur);
			cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[RES_LATE]++;
				goto failed;
			}
		}
		/*resume成功执行后，移入到prepared链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_prepared_list));
		if(cur->complete)
		{
			dpm_ctrl.current_callback = cur->complete;
			dpm_ctrl.flag = 1;
			cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
			ret = cur->complete(cur);
			cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[COMPLETE]++;
				goto failed;
			}
		}
		/*complete成功执行后，移入到dpm_list链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_list));
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return OK;
	}
	failed:
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return ERROR;
}

void bsp_dpm_help()
{
    
    dpm_print("dpm cnt 0x%x\n",dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL]);
    dpm_print("dpm dump addr 0x%x\n",DPM_DUMP_START);
    dpm_print("for more info try: %s\n",__FUNCTION__);
}

void bsp_dpm_show()
{
	struct dpm_device *dev;/*lint !e830*/
	dpm_print("devnode_name=%s,current_callback = 0x%x,  flag = %d\n",dpm_ctrl.device_name,dpm_ctrl.current_callback,dpm_ctrl.flag);
	dpm_print("[dpm count] suspend:%d  resume:%d\n",\
            dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL],dpm_ctrl.dpm_count[DPM_CNT_R_TOTAL]);
	dpm_print("[dpm count] pre_err:%d  sus_early_err:%d  sus_err:%d late_err:%d  \n",\
            dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_PREPARE],dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_EARLY],\
            dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_SUSPEND],dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_LATE]);
	dpm_print("-------------------dpm list info:  dev_info:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_list),entry)
	{
		dpm_print("[%s]:\n",dev->device_name);
        if(dev->prepare)
            dpm_print("prepare   begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[PREPARE][0], dev->debug_time[PREPARE][1],\
                dev->max_duration[PREPARE] , dev->debug_count[PREPARE]);
        if(dev->suspend_early)
            dpm_print("sus early begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[SUS_EARLY][0], dev->debug_time[SUS_EARLY][1],\
                dev->max_duration[SUS_EARLY] , dev->debug_count[SUS_EARLY]);
        if(dev->suspend)
            dpm_print("suspend   begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[SUSPEND][0], dev->debug_time[SUSPEND][1],\
                dev->max_duration[SUSPEND] , dev->debug_count[SUSPEND]);
        if(dev->suspend_late)
            dpm_print("sus late  begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[LATE][0], dev->debug_time[LATE][1],\
                dev->max_duration[LATE] ,dev->debug_count[LATE]);
        if(dev->resume_early)
            dpm_print("res early begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[EARLY][0], dev->debug_time[EARLY][1], dev->max_duration[EARLY]);
        if(dev->resume)
            dpm_print("resume    begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[RESUME][0], dev->debug_time[RESUME][1], dev->max_duration[RESUME]);
        if(dev->resume_late)
            dpm_print("res  late begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[RES_LATE][0], dev->debug_time[RES_LATE][1], dev->max_duration[RES_LATE]);
        if(dev->complete)
            dpm_print("complete  begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[COMPLETE][0] ,dev->debug_time[COMPLETE][1], dev->max_duration[COMPLETE]);
	}
    dpm_print("\n");
    dpm_print("-------------------dpm list info:  dev_name:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("-------------------dpm prepared  list info:  dev_name:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_prepared_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm sus early list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_sus_early_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm suspend list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_suspend_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm late early list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_late_early_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
}

void bsp_dpm_init(void)
{
	int i = 0;
	INIT_LIST_HEAD(&(dpm_ctrl.dpm_list));
	INIT_LIST_HEAD(&(dpm_ctrl.dpm_prepared_list));
	INIT_LIST_HEAD(&(dpm_ctrl.dpm_sus_early_list));
	INIT_LIST_HEAD(&(dpm_ctrl.dpm_suspend_list));
	INIT_LIST_HEAD(&(dpm_ctrl.dpm_late_early_list));
	spin_lock_init(&dpm_ctrl.dpm_list_mtx);
	for(i = 0;i<DPM_CALLBACK_NUM;i++)
		dpm_ctrl.dpm_count[i]=0;
	dpm_ctrl.current_callback = NULL;
	dpm_ctrl.flag = 0;
    
    dpm_dump_drx_c_addr = (u32)bsp_dump_register_field(DUMP_CP_DRX, "DRX_CCORE", NULL, NULL, PM_DUMP_CCORE_DRX_SIZE, 0);
    if(0!=dpm_dump_drx_c_addr)
    {
        if(memset_s((void*)(DPM_DUMP_START),DPM_DUMP_SIZE,0,DPM_DUMP_SIZE))
            dpm_print("memset_s DPM_DUMP_START err \n");
    }
    else
    {
        dpm_print("bsp_dump_register_field:DRX_CCORE failed \n");
    }
    dpm_print("c core dpm init success\n");
	return;
}
/*lint -restore +e516*/


