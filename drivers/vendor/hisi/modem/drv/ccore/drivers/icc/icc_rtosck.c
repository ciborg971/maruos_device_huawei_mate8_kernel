

#include <bsp_dump.h>
#include <bsp_dpm.h>

#include <icc_core.h>
#include <bsp_icc.h>

extern struct icc_control g_icc_ctrl;

void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo)
{
	if (bsp_reset_ccore_is_reboot())
	{
		if(ICC_CHN_MAGIC_UNSIGN == channel_fifo->magic) /* [false alarm]:fortify */ /* MBB���߲������ֻ������ߵ� */
		{
			channel_fifo->magic = ICC_CHN_MAGIC_SIGN;
		}
	}
	return;
}

s32 icc_channel_has_data(void)
{
	/*lint --e{53, 58, 56 } */
	s32 i = 0;
	u32 read  = 0;
	u32 write = 0;
	struct icc_channel_fifo *fifo = NULL;
	struct icc_channel_packet packet = {0};

	for(i = 0; i < (int)ICC_CHN_ID_MAX; i++)
	{
		
		if(NULL == g_icc_ctrl.channels[i])
		{
			continue;
		}
		fifo = g_icc_ctrl.channels[i]->fifo_recv;
		read  = fifo->read;
		write = fifo->write;
		if(read != write) /* has data to be handled */
		{
			icc_print_error("%s[channel-%d] stop suspend flow\n", g_icc_ctrl.channels[i]->name, i);
			if (ICC_CHN_IFC == i || ICC_CHN_MCORE_ACORE == i || ICC_CHN_MCORE_CCORE ==i)
			{
				while(read < write)
				{
					if(fifo_get(fifo, (u8 *)&packet, sizeof(packet), &read) != sizeof(packet))
					{
						break;
					}
					icc_sleep_flag_set();
					if (icc_channel_packet_dump(&packet) != ICC_OK)
					{
						break;
					}
					read = (read + packet.len);
					read = (read >= fifo->size)? (read - fifo->size): (read);
				}
			}
			icc_wake_lock(&g_icc_ctrl.wake_lock);
			osl_sem_up(&g_icc_ctrl.shared_task_sem);
			return ICC_BUSY;
		}
	}

	return ICC_OK;
}

s32 bsp_icc_prepare(struct dpm_device *dev);

struct dpm_device icc_dpm_device =
{
	.device_name = "balong icc dpm driver",
	.prepare = bsp_icc_prepare,
};

s32 bsp_icc_prepare(struct dpm_device *dev)
{
	return icc_channel_has_data();
}

static s32 icc_device_pm_add(void)
{
	if(bsp_device_pm_add(&icc_dpm_device))
	{
		return ICC_REGISTER_DPM_FAIL;
	}

	return ICC_OK;
}

void icc_sem_init(void)
{
    osl_sem_init(ICC_SEM_FULL, &g_icc_ctrl.shared_task_sem);
}

int icc_shared_task_init(void)
{
	return osl_task_init("icc_shared", ICC_TASK_SHARED_PRI, ICC_TASK_STK_SIZE ,(void *)icc_task_shared_func, NULL,
			&g_icc_ctrl.shared_task_id);

}

void icc_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    system_error(mod_id, arg1, arg2, data, length);
}

void bsp_icc_channel_uninit(u32 real_channel_id)
{
	struct icc_channel *channel = NULL;

	channel = g_icc_ctrl.channels[real_channel_id];


#ifdef ICC_HAS_INDEPENDENT_CHN_FEATURE
	if(!channel->mode.union_stru.task_shared)
	{

		kthread_stop(channel->private_task_id);
		(void)osl_sema_delete(&channel->private_task_sem);
	}

	if(!channel->mode.union_stru.ipc_shared)
	{
		bsp_ipc_int_disconnect(((IPC_INT_LEV_E))channel->ipc_recv_irq_id, (voidfuncptr)icc_ipc_isr, channel->id);
	}
#endif

	icc_safe_free(channel->vector);
	(void)memset_s(channel->fifo_send, sizeof(struct icc_channel_fifo) + channel->fifo_send->size, 
		0, sizeof(struct icc_channel_fifo) + channel->fifo_send->size); /*lint !e665 */
	icc_safe_free(channel);

}

void icc_wakeup_flag_set(void)
{
	g_icc_ctrl.wake_up_flag = 1;
}

void icc_sleep_flag_set(void)
{
	g_icc_ctrl.sleep_flag = 1;
}

u32 bsp_icc_channel_status_get(u32 real_channel_id, u32 *channel_stat)
{
	struct icc_channel* channel = g_icc_ctrl.channels[real_channel_id];

	if(NULL == channel)
	{
		*channel_stat = ICC_CHN_CLOSED;
		return *channel_stat;
	}

	*channel_stat = channel->state;
	return *channel_stat;

}

int icc_pm_init(void)
{
	(void)icc_device_pm_add();
	return ICC_OK;
}

