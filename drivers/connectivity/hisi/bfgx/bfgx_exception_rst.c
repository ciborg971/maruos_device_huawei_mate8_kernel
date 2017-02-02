

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/delay.h>
#include <linux/rtc.h>
#include <linux/tty.h>

#include "plat_type.h"
#include "plat_debug.h"
#include "hw_bfg_ps.h"
#include "plat_pm.h"
#include "bfgx_exception_rst.h"
#include "plat_firmware.h"
#include "plat_uart.h"

#include "oal_sdio_host_if.h"

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
struct st_exception_info *g_pst_exception_info = NULL;
extern struct oal_sdio* oal_alloc_sdio_stru(oal_void);

/*****************************************************************************
  2 函数实现
*****************************************************************************/
void  bfgx_beat_timer_expire(uint64 data);
void  wifi_rf_overheat_expire(uint64 data);
void  bfgx_rf_overheat_expire(uint64 data);
int32 get_exception_info_reference(struct st_exception_info **exception_data);
int32 plat_exception_handler(uint32 subsys_type, uint32 thread_type, uint32 exception_type);
void  plat_exception_reset_work(struct work_struct *work);
int32 wifi_exception_handler(void);
int32 wifi_subsystem_reset(void);
int32 wifi_system_reset(void);
int32 wifi_rf_overheat_handle(void);
int32 wifi_status_recovery(void);
int32 wifi_exception_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count);
int32 bfgx_exception_handler(void);
int32 bfgx_subthread_reset(void);
int32 bfgx_subsystem_reset(void);
int32 bfgx_system_reset(void);
int32 bfgx_recv_dev_mem(uint8 *buf_ptr, uint16 count);
int32 bfgx_store_stack_mem_to_file(void);
void  bfgx_dump_stack(void);
int32 bfgx_rf_overheat_handle(void);
int32 bfgx_status_recovery(void);
int32 hi110x_system_power_reset(void);
int32 plat_bfgx_exception_rst_register(struct ps_plat_s *data);
int32 plat_exception_reset_init(void);
int32 plat_exception_reset_exit(void);

/*****************************************************************************
 * Prototype    : mod_beat_timer
 * Description  :
 * input        : uint8
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/05/09
 *     Author       : wx145522
 *     Modification : Created function
*****************************************************************************/
int32 mod_beat_timer(uint8 on)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (on)
    {
        PS_PRINT_INFO("exception: reset beat timer\n");
        atomic_set(&pst_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);
        mod_timer(&pst_exception_data->bfgx_beat_timer, jiffies + BFGX_BEAT_TIME * HZ);
    }
    else
    {
        PS_PRINT_INFO("exception: delete beat timer\n");
        del_timer_sync(&pst_exception_data->bfgx_beat_timer);
    }

    return 0;
}


//FIXME: remove then, just for test
extern uint32 ul_disallow_flag;
//FIXME end

void bfgx_beat_timer_expire(uint64 data)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;
    struct tty_buffer *thead;
    struct tty_bufhead *buf = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    /*bfgx睡眠时，没有心跳消息上报*/
    if (BFGX_SLEEP == ps_core_d->ps_pm->bfgx_dev_state_get())
    {
        PS_PRINT_INFO("bfgx has sleep!\n");
        return;
    }

    if (BFGX_NOT_RECV_BEAT_INFO == atomic_read(&pst_exception_data->bfgx_beat_flag))
    {
        PS_PRINT_ERR("host can not recvive bfgx beat info!\n");
        //FIXME: remove then, just for test
        if (1 == ul_disallow_flag)
        {
            PS_PRINT_ERR("###########we have not recv data from dev after last disallow msg@@@@@@@@@@@@@@!\n");
            if (tty_chars_in_buffer(ps_core_d->tty))
            {
                PS_PRINT_INFO("uart tx buf is not empty\n");
            }

            if(NULL == ps_core_d->tty->port)
            {
                PS_PRINT_ERR("tty->port is null, bfgx download patch maybe failed!\n");
                return;
            }
            buf = &(ps_core_d->tty->port->buf);
            thead = buf->head;
            while (thead != NULL)
            {
                PS_PRINT_INFO("thead is not null, size= 0x%x\n", thead->size);
                if (thead->used)
                {
                    PS_PRINT_INFO("tty buf is not free\n");
                }
                thead = thead->next;
            }
            /*
            if (0 != host_wkup_dev())
            {
                PS_PRINT_ERR("###########bfgx_beat_timer_expire wkup failed@@@@@@@@@@@@@@!\n");
            }
            msleep(200);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DISALLOW_SLP);
            */
        }
        //FIXME end
        if (true == pst_exception_data->exception_reset_enable)
        {
            PS_PRINT_ERR("bfgx beat timer bring to reset work!");
            del_timer_sync(&ps_core_d->ps_pm->pm_priv_data->bfg_timer);
            plat_exception_handler(SUBSYS_BFGX, BFGX_THREAD_BOTTOM, BEAT_HEART_TIMEOUT);
            return;
        }
    }

    atomic_set(&pst_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);

    PS_PRINT_INFO("exception:reset beat timer\n");
    mod_timer(&pst_exception_data->bfgx_beat_timer, jiffies + BFGX_BEAT_TIME * HZ);

    return;
}


void bfgx_rf_overheat_expire(uint64 data)
{
    struct st_exception_info *pst_exception_data = NULL;
    struct ps_core_s *ps_core_d = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    if (RF_TEMERATURE_NORMAL == atomic_read(&pst_exception_data->bfgx_rf_temperature_status))
    {
        PS_PRINT_SUC("bfgx rf temperature is normal!\n");
        /*通知业务BFGX，rf温度已经恢复正常*/
        pst_exception_data->reset_device_msg = RESET_MSG_BFGX_RF_NORMAL;
        sysfs_notify(g_sysfs_bfgx_exception, NULL, "bfgx_rf_temp\n");
        mdelay(10);
        pst_exception_data->reset_device_msg = RESET_MSG_NONE;
    }
    else
    {
        /*发送平台命令，查询rf温度*/
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_QUERY_RF_TEMP);
        mod_timer(&pst_exception_data->bfgx_rf_overheat_timer, jiffies + BFGX_RF_QUERY_TIME * HZ);
    }

    return;
}


void wifi_rf_overheat_expire(uint64 data)
{
    struct st_exception_info *pst_exception_data = NULL;
    struct oal_sdio     *hi_sdio;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    if (RF_TEMERATURE_NORMAL == atomic_read(&pst_exception_data->wifi_rf_temperature_status))
    {
        PS_PRINT_SUC("wifi rf temperature is normal!\n");
        /*通知业务WIFI，rf温度恢复正常*/
        pst_exception_data->reset_device_msg = RESET_MSG_WIFI_RF_NORMAL;
        sysfs_notify(g_sysfs_bfgx_exception, NULL, "wifi_rf_temp\n");
    }
    else
    {
        /*sdio MSG,查询rf温度*/
        hi_sdio = oal_alloc_sdio_stru();
        oal_sdio_send_msg(hi_sdio, H2D_MSG_QUERY_RF_TEMP);
        mod_timer(&pst_exception_data->wifi_rf_overheat_timer, jiffies + WIFI_RF_QUERY_TIME * HZ);
    }

    return;
}


int32 get_exception_info_reference(struct st_exception_info **exception_data)
{
    if (NULL == exception_data)
    {
        PS_PRINT_ERR("%s parm exception_data is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    if (NULL == g_pst_exception_info)
    {
        *exception_data = NULL;
        PS_PRINT_ERR("%s g_pst_exception_info is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    *exception_data = g_pst_exception_info;

    return EXCEPTION_SUCCESS;
}


int32 plat_exception_handler(uint32 subsys_type, uint32 thread_type, uint32 exception_type)
{
    struct st_exception_info *pst_exception_data = NULL;
    uint64 flag;

    if (subsys_type >= SUBSYS_BOTTOM)
    {
        PS_PRINT_ERR("para subsys_type %u is error!\n", subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (((subsys_type == SUBSYS_WIFI) && (thread_type > WIFI_THREAD_BOTTOM))
     || ((subsys_type == SUBSYS_BFGX) && (thread_type > BFGX_THREAD_BOTTOM)))
    {
        PS_PRINT_ERR("para thread_type %u is error! subsys_type is %u\n", thread_type, subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (exception_type >= EXCEPTION_TYPE_BOTTOM)
    {
        PS_PRINT_ERR("para exception_type %u is error!\n", exception_type);
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (true != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_INFO("palt exception reset not enable!");
        return EXCEPTION_SUCCESS;
    }

    /*这里只能用spin lock，因为该函数会被心跳超时函数调用，心跳超时函数属于软中断，不允许睡眠*/
    spin_lock_irqsave(&pst_exception_data->exception_spin_lock, flag);
    if (PLAT_EXCEPTION_RESET_IDLE == atomic_read(&pst_exception_data->is_reseting_device))
    {
        pst_exception_data->subsys_type   = subsys_type;
        pst_exception_data->thread_type   = thread_type;
        pst_exception_data->excetion_type = exception_type;

        /*当前异常没有处理完成之前，不允许处理新的异常*/
        atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_BUSY);
    }
    else
    {
        PS_PRINT_INFO("plat is processing exception! subsys=%d, exception type=%d\n",
                               pst_exception_data->subsys_type, pst_exception_data->excetion_type);
        spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);
        return EXCEPTION_SUCCESS;
    }
    spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);

    /*触发异常处理worker*/
    queue_work(pst_exception_data->plat_exception_rst_workqueue, &pst_exception_data->plat_exception_rst_work);

    return EXCEPTION_SUCCESS;
}
void plat_exception_reset_work(struct work_struct *work)
{
	int32  ret = -EXCEPTION_FAIL;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    mutex_lock(&pst_exception_data->exception_reset_mutex);

	if (SUBSYS_WIFI == pst_exception_data->subsys_type)
	{
	    pst_exception_data->wifi_exception_cnt += 1;
		ret = wifi_exception_handler();
	}
	else
	{
	    pst_exception_data->bfgx_exception_cnt += 1;
		ret = bfgx_exception_handler();
	}

	if (ret != EXCEPTION_SUCCESS)
	{
		PS_PRINT_ERR("plat execption recovery fail! subsys_type = [%u], exception_type = [%u]\n",
		                               pst_exception_data->subsys_type, pst_exception_data->excetion_type);
	}
	else
	{
        PS_PRINT_SUC("plat execption recovery success!\n");
	}

    atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_IDLE);

	mutex_unlock(&pst_exception_data->exception_reset_mutex);

	return;
}


int32 wifi_exception_handler(void)
{
	int32 ret = -EXCEPTION_FAIL;
	uint32 exception_type;
	struct ps_core_s *ps_core_d = NULL;
	struct st_exception_info *pst_exception_data = NULL;
	struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

	exception_type = pst_exception_data->excetion_type;

    if (exception_type == RF_OVERHEAT_EXCEPTION)
    {
        /*RF过热异常处理*/
        ret = wifi_rf_overheat_handle();
        if (EXCEPTION_SUCCESS != ret)
        {
            PS_PRINT_ERR("wifi rf overheat handle failed!");
            return ret;
        }

        return EXCEPTION_SUCCESS;
    }

    /*bfg mutex, 防止wifi异常处理期间bfgx关闭，因为要用到uart*/
    mutex_lock(&pm_data->host_mutex);

	/*如果bfgx已经打开，执行wifi子系统复位流程，否则执行wifi全系统复位流程*/
	if (!check_dev_is_shutdown(BT_GNSS_FM_NFC_IR_STATE_FLAG))
	{
	    PS_PRINT_INFO("bfgx is opened, start wifi subsystem reset!\n");
		ret = wifi_subsystem_reset();
		if (EXCEPTION_SUCCESS != ret)
		{
            PS_PRINT_ERR("wifi subsystem reset failed, start wifi system reset!\n");
            ret = wifi_system_reset();
		}
	}
	else
	{
	    PS_PRINT_INFO("bfgx is not opened, start wifi system reset!\n");
		ret = wifi_system_reset();
	}

	if (ret != EXCEPTION_SUCCESS)
	{
		PS_PRINT_ERR("wifi execption recovery fail!\n");
		mutex_unlock(&pm_data->host_mutex);
		return ret;
	}

	mutex_unlock(&pm_data->host_mutex);

	return EXCEPTION_SUCCESS;
}
int32 wifi_subsystem_reset(void)
{
    int32 ret = -EXCEPTION_FAIL;
    struct ps_core_s *ps_core_d = NULL;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    /*通过uart复位WCPU*/
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_WIFI);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_WIFI);

    /*加载wifi firmware*/
    ret = firmware_download_function(WIFI_CFG);
    if (EXCEPTION_SUCCESS != ret)
    {
        PS_PRINT_ERR("wifi firmware download failed\n");
        return -EXCEPTION_FAIL;
    }

    /*恢复业务状态*/
    ret = wifi_status_recovery();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("wifi status revocery failed!\n");
        return -EXCEPTION_FAIL;
    }

	return EXCEPTION_SUCCESS;
}
int32 wifi_system_reset(void)
{
    int32 ret = -EXCEPTION_FAIL;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (!check_dev_is_shutdown(BT_GNSS_FM_NFC_IR_STATE_FLAG))
    {
        /*通知bfgx*/
        pst_exception_data->reset_device_msg = RESET_MSG_POWER_RESET;
        sysfs_notify(g_sysfs_bfgx_exception, NULL, "power_reset\n");
        msleep(50);
        pst_exception_data->reset_device_msg = RESET_MSG_NONE;
    }

    /*重新上电，firmware重新加载*/
    ret = hi110x_system_power_reset();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("hi110x system power reset failed!\n");
        return -EXCEPTION_FAIL;
    }

    if (!check_dev_is_shutdown(BT_GNSS_FM_NFC_IR_STATE_FLAG))
    {
        /*恢复bfgx业务状态*/
        ret = bfgx_status_recovery();
        if (ret != EXCEPTION_SUCCESS)
        {
            PS_PRINT_ERR("bfgx status revocery failed!\n");
            return -EXCEPTION_FAIL;
        }
    }

    ret = wifi_status_recovery();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("wifi status revocery failed!\n");
        return -EXCEPTION_FAIL;
    }

    return EXCEPTION_SUCCESS;
}
int32 wifi_rf_overheat_handle(void)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    PS_PRINT_ERR("wifi device rf overheat!\n");
    atomic_set(&pst_exception_data->wifi_rf_temperature_status, RF_TEMERATURE_OVERHEAT);

    /*通知业务rf过热异常*/
    pst_exception_data->reset_device_msg = RESET_MSG_WIFI_RF_OVERHEAT;
    sysfs_notify(g_sysfs_bfgx_exception, NULL, "wifi_rf_temp\n");

    /*起定时器，定时查询rf温度，如果温度恢复正常，通知业务*/
    mod_timer(&pst_exception_data->wifi_rf_overheat_timer, jiffies + WIFI_RF_QUERY_TIME * HZ);

    return EXCEPTION_SUCCESS;
}


int32 wifi_status_recovery(void)
{
    struct ps_plat_s *ps_plat_d = NULL;
    struct ps_core_s *ps_core_d = NULL;

    ps_get_plat_reference(&ps_plat_d);
    if (unlikely(NULL == ps_plat_d))
    {
        PS_PRINT_ERR("ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;
    }
    ps_core_d = ps_plat_d->core_data;

    if (check_dev_is_shutdown(WLAN_STATE_FLAG))
    {
        /*uart关闭WCPU*/
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_WIFI);
    }

	return EXCEPTION_SUCCESS;
}
int32 wifi_exception_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count)
{
    return sdio_device_mem_dump(pst_mem_dump_info, count);
}

EXPORT_SYMBOL(wifi_exception_mem_dump);


int32 prepare_to_recv_bfgx_stack(uint32 len)
{
    struct st_exception_info *pst_exception_data = NULL;
    struct st_exception_mem_info *pst_mem_info = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }
    pst_mem_info = &pst_exception_data->dump_mem[SUBSYS_BFGX];

    if (DUMP_MEM_IDLE == pst_mem_info->mem_status)
    {
        pst_mem_info->exception_mem_addr = (uint8 *)OS_KMALLOC_GFP(len);
        if (NULL == pst_mem_info->exception_mem_addr)
        {
            PS_PRINT_ERR("prepare mem to recv bfgx stack failed\n");
            return -EXCEPTION_FAIL;
        }
        else
        {
            pst_mem_info->mem_status  = DUMP_MEM_BUSY;
            pst_mem_info->recved_size = 0;
            pst_mem_info->total_size  = len;
            PS_PRINT_INFO("prepare mem [%d] to recv bfgx stack\n", len);
        }
    }

    return EXCEPTION_SUCCESS;
}


int32 bfgx_exception_handler(void)
{
	int32  ret = -EXCEPTION_FAIL;
	uint32 exception_type;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

	exception_type = pst_exception_data->excetion_type;

	/*ioctl下来的异常执行线程复位流程*/
	if (exception_type == TIMER_TIMEOUT || exception_type == ARP_TIMEOUT)
	{
		ret = bfgx_subthread_reset();
	}
	else if (exception_type == RF_OVERHEAT_EXCEPTION)
	{
        /*rf过热处理*/
        ret = bfgx_rf_overheat_handle();
	}
	else
	{
		ret = bfgx_subsystem_reset();
	}

	if (EXCEPTION_SUCCESS != ret)
	{
		PS_PRINT_ERR("bfgx exception recovery fail!, exception_type = [%u]\n", exception_type);
		return ret;
	}

	return EXCEPTION_SUCCESS;
}


int32 bfgx_subthread_reset(void)
{
	int32  ret = -EXCEPTION_FAIL;
	uint32 subsys, subthread;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    subsys    = pst_exception_data->subsys_type;
    subthread = pst_exception_data->thread_type;

	/*uart 发送复位子业务命令*/

	/*等待子业务复位成功ACK*/

	if (EXCEPTION_SUCCESS != ret)
	{
		PS_PRINT_INFO("bfgx subthread reset fail! start subsystem reset!\n");
		ret = bfgx_subsystem_reset();

		if (EXCEPTION_SUCCESS != ret)
		{
			PS_PRINT_ERR("bfgx subsystem reset fail!\n");
			return -EXCEPTION_FAIL;
		}
	}

	return EXCEPTION_SUCCESS;
}


int32 __bfgx_subsystem_reset(void)
{
    int32  ret = -EXCEPTION_FAIL;
    struct oal_sdio  *hi_sdio;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    PS_PRINT_INFO("info to bfgx, plat start exception reset!\n");
    pst_exception_data->reset_device_msg = RESET_MSG_BFGX_RESET;
    sysfs_notify(g_sysfs_bfgx_exception, NULL, "bfgx_reset\n");
    msleep(50);
    pst_exception_data->reset_device_msg = RESET_MSG_NONE;

    if (false == ps_chk_bfg_active(ps_core_d))
    {
        PS_PRINT_ERR("no proto func is opened\n");
        return EXCEPTION_SUCCESS;
    }

    /*关闭打开uart*/
    ret = release_tty_drv(ps_core_d->pm_data);
    if (ret != 0)
    {
        PS_PRINT_ERR("close tty is err!\n");
        return -EXCEPTION_FAIL;
    }

    ret = open_tty_drv(ps_core_d->pm_data);
    if (ret != 0)
    {
        PS_PRINT_ERR("open tty is err!\n");
        return -EXCEPTION_FAIL;
    }

    /*sdio复位解复位BCPU*/
    PS_PRINT_INFO("exception: reset BCPU\n");
    hi_sdio = oal_alloc_sdio_stru();
    oal_sdio_send_msg(hi_sdio, H2D_MSG_RESET_BCPU);

    /*等待device软件初始化完成，这里最好使用完成量*/
    mdelay(100);

    /*恢复bfgx*/
    ret = bfgx_status_recovery();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("bfgx recovery status failed\n");
        return -EXCEPTION_FAIL;
    }

    return EXCEPTION_SUCCESS;
}


int32 bfgx_subsystem_reset(void)
{
	int32  ret = -EXCEPTION_FAIL;
	struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    /*bfgx互斥锁，防止异常处理期间业务的开关*/
    mutex_lock(&pm_data->host_mutex);

	/*如果是心跳超时，尝试用平台命令读栈，不能保证一定成功，因为此时uart可能不通*/
	bfgx_dump_stack();

	/*如果wifi已经打开，执行bfgx子系统复位流程，否则执行bfgx全系统复位流程*/
	if (!check_dev_is_shutdown(WLAN_STATE_FLAG))
	{
	    PS_PRINT_INFO("wifi is opened, start bfgx subsystem reset!\n");
        ret = __bfgx_subsystem_reset();
        if (ret != EXCEPTION_SUCCESS)
        {
            PS_PRINT_ERR("bfgx subsystem reset failed, start bfgx system reset!\n");
            ret = bfgx_system_reset();
        }
	}
	else
	{
	    PS_PRINT_INFO("wifi is not opened, start bfgx system reset!\n");
		ret = bfgx_system_reset();
	}

    mutex_unlock(&pm_data->host_mutex);

	return ret;
}
int32 bfgx_system_reset(void)
{
    int32 ret = -EXCEPTION_FAIL;
    struct ps_core_s *ps_core_d = NULL;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    /*上电互斥锁，用于和wifi同步*/
    ps_core_d->ps_pm->bfg_mutex_lock(1);

    /*通知bfgx*/
    pst_exception_data->reset_device_msg = RESET_MSG_POWER_RESET;
    sysfs_notify(g_sysfs_bfgx_exception, NULL, "power_reset\n");
    msleep(50);
    pst_exception_data->reset_device_msg = RESET_MSG_NONE;

    if (!check_dev_is_shutdown(WLAN_STATE_FLAG))
    {
        /*通知wifi*/
        /*调用wifi注册的回调函数*/
    }

    /*重新上电，firmware重新加载*/
    ret = hi110x_system_power_reset();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("hi110x system power reset failed!\n");
        ps_core_d->ps_pm->bfg_mutex_lock(0);
        return -EXCEPTION_FAIL;
    }

    /*恢复业务状态*/
    ret = wifi_status_recovery();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("wifi status revocery failed!\n");
        ps_core_d->ps_pm->bfg_mutex_lock(0);
        return -EXCEPTION_FAIL;
    }

    ret = bfgx_status_recovery();
    if (ret != EXCEPTION_SUCCESS)
    {
        PS_PRINT_ERR("bfgx status revocery failed!\n");
        ps_core_d->ps_pm->bfg_mutex_lock(0);
        return -EXCEPTION_FAIL;
    }

    ps_core_d->ps_pm->bfg_mutex_lock(0);

    return EXCEPTION_SUCCESS;
}


int32 bfgx_recv_dev_mem(uint8 *buf_ptr, uint16 count)
{
    struct st_exception_info *pst_exception_data = NULL;
    struct st_exception_mem_info *pst_mem_info = NULL;
    uint32 offset = 0;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }
    pst_mem_info = &pst_exception_data->dump_mem[SUBSYS_BFGX];

    if (NULL == buf_ptr)
    {
        PS_PRINT_ERR("buf_ptr is NULL\n");
        return -EFAIL;
    }

    if (pst_mem_info->mem_status == DUMP_MEM_IDLE)
    {
        PS_PRINT_ERR("mem status is error\n");
        return -EXCEPTION_FAIL;
    }

    offset = pst_mem_info->recved_size;
    if (offset + count > pst_mem_info->total_size)
    {
        PS_PRINT_ERR("outof buf total size, recved size is [%d], curr recved size is [%d], total size is [%d]\n", offset, count, pst_mem_info->total_size);
        return -EXCEPTION_FAIL;
    }
    else
    {
        PS_PRINT_INFO("cpy stack size [%d] to exception mem\n", count);
        OS_MEM_CPY(pst_mem_info->exception_mem_addr + offset, buf_ptr, count);
        pst_mem_info->recved_size += count;
    }

    if (pst_mem_info->recved_size == pst_mem_info->total_size)
    {
        complete(&pst_exception_data->wait_read_bfgx_stack);
    }

    return EXCEPTION_SUCCESS;
}


int32 bfgx_store_stack_mem_to_file(void)
{
    OS_KERNEL_FILE_STRU *fp;
    char filename[100] = {0};
    struct timeval tv;
    struct rtc_time tm;
    int32 l_ret;
    mm_segment_t fs;
    struct st_exception_info *pst_exception_data = NULL;
    struct st_exception_mem_info *pst_mem_info = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }
    pst_mem_info = &pst_exception_data->dump_mem[SUBSYS_BFGX];

    if (pst_mem_info->mem_status == DUMP_MEM_IDLE)
    {
        PS_PRINT_ERR("mem status is error\n");
        return -EXCEPTION_FAIL;
    }

    do_gettimeofday(&tv);
    rtc_time_to_tm(tv.tv_sec, &tm);
    PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
               tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    OS_MEM_SET(filename, 0, sizeof(filename));
    snprintf(filename, sizeof(filename),"/data/memdump/%04d%02d%02d%02d%02d%02d_bfgx.bin",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    /*打开文件，准备保存接收到的内存*/
    fp = filp_open(filename, O_RDWR | O_CREAT, 0777);
    if (IS_ERR(fp))
    {
        PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
        OS_MEM_KFREE(pst_mem_info->exception_mem_addr);
        pst_mem_info->exception_mem_addr = NULL;
        pst_mem_info->mem_status = DUMP_MEM_IDLE;
        return -EXCEPTION_FAIL;
    }

    /*将接收到的内存写入到文件中*/
    fs = get_fs();
    set_fs(KERNEL_DS);
    l_ret = vfs_llseek(fp, 0, SEEK_END);
    PS_PRINT_INFO("pos = %d\n", (int)fp->f_pos);
    vfs_write(fp, pst_mem_info->exception_mem_addr, pst_mem_info->recved_size, &fp->f_pos);
    set_fs(fs);

    filp_close(fp, NULL);

    OS_MEM_KFREE(pst_mem_info->exception_mem_addr);
    pst_mem_info->exception_mem_addr = NULL;
    pst_mem_info->mem_status = DUMP_MEM_IDLE;

    return EXCEPTION_SUCCESS;
}


void bfgx_dump_stack(void)
{
    uint64 timeleft;
    uint32 exception_type;
    struct ps_core_s *ps_core_d = NULL;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    exception_type = pst_exception_data->excetion_type;

    if ((exception_type != BEAT_HEART_TIMEOUT) && (exception_type != LAST_WORD))
	{
	    return;
	}

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    INIT_COMPLETION(pst_exception_data->wait_read_bfgx_stack);

    /*心跳超时需要host主动发命令去读内存，临终遗言只需要等待device将内存上报上来*/
    if (exception_type == BEAT_HEART_TIMEOUT)
    {
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_READ_STACK);
    }

    /*等待读栈操作完成*/
    timeleft = wait_for_completion_timeout(&pst_exception_data->wait_read_bfgx_stack, msecs_to_jiffies(WAIT_BFGX_READ_STACK_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("read bfgx stack failed!\n");
    }
    else
    {
        bfgx_store_stack_mem_to_file();
        PS_PRINT_INFO("read bfgx stack success!\n");
    }

    return;
}


int32 bfgx_rf_overheat_handle(void)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (RF_TEMERATURE_NORMAL != atomic_read(&pst_exception_data->bfgx_rf_temperature_status))
    {
        PS_PRINT_INFO("bfgx_rf_overheat_timer have been started! ignored\n");
        return EXCEPTION_SUCCESS;
    }

    PS_PRINT_ERR("bfgx device rf overheat!\n");
    atomic_set(&pst_exception_data->bfgx_rf_temperature_status, RF_TEMERATURE_OVERHEAT);

    /*通知BFGX rf过热异常*/
    pst_exception_data->reset_device_msg = RESET_MSG_BFGX_RF_OVERHEAT;
    sysfs_notify(g_sysfs_bfgx_exception, NULL, "bfgx_rf_temp\n");
    msleep(50);
    pst_exception_data->reset_device_msg = RESET_MSG_NONE;

    /*起定时器，定时查询rf温度，如果温度恢复正常，通知业务*/
    mod_timer(&pst_exception_data->bfgx_rf_overheat_timer, jiffies + BFGX_RF_QUERY_TIME * HZ);

    return EXCEPTION_SUCCESS;
}


int32 bfgx_status_recovery(void)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return -EXCEPTION_FAIL;;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /*仅调试使用*/
    PS_PRINT_INFO("exception: set debug beat flag to 1\n");
    pst_exception_data->debug_beat_flag = 1;

    return EXCEPTION_SUCCESS;
}
int32 hi110x_system_power_reset(void)
{
    int32 ret = -EXCEPTION_FAIL;

    /*重新上电*/
    PS_PRINT_INFO("exception:reset power on gpio, pull down and then pull up\n");
    board_power_on();

    /*加载firmware*/
    ret = firmware_download_function(BFGX_AND_WIFI_CFG);
    if (0 != ret)
    {
        PS_PRINT_ERR("exception firmware download failed\n");
        return -EXCEPTION_FAIL;
    }

	return EXCEPTION_SUCCESS;
}


int32 is_bfgx_exception(void)
{
    struct st_exception_info *pst_exception_data = NULL;
    int32 is_exception = 0;
    uint64 flag;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    spin_lock_irqsave(&pst_exception_data->exception_spin_lock, flag);
    if ((SUBSYS_BFGX == pst_exception_data->subsys_type)
     && (PLAT_EXCEPTION_RESET_BUSY == atomic_read(&pst_exception_data->is_reseting_device)))
    {
        is_exception = 1;
    }
    spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);

    return is_exception;
}


int32 plat_bfgx_exception_rst_register(struct ps_plat_s *data)
{
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (NULL == data)
    {
        PS_PRINT_ERR("para data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    pst_exception_data->ps_plat_d = data;

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_bfgx_exception_rst_register);


int32 plat_wifi_exception_rst_register(void *data)
{
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    /*wifi异常回调函数注册*/
    pst_exception_data->wifi_callback = data;

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_wifi_exception_rst_register);
int32 plat_exception_reset_init(void)
{
    struct st_exception_info *p_exception_data = NULL;

    p_exception_data = (struct st_exception_info *)kzalloc(sizeof(struct st_exception_info), GFP_ATOMIC);
    if (NULL == p_exception_data)
    {
        PS_PRINT_ERR("kzalloc p_exception_data is failed!\n");
        return -EXCEPTION_FAIL;
    }

    p_exception_data->subsys_type   = SUBSYS_BOTTOM;
    p_exception_data->thread_type   = BFGX_THREAD_BOTTOM;
    p_exception_data->excetion_type = EXCEPTION_TYPE_BOTTOM;
    p_exception_data->dump_mem[SUBSYS_WIFI].mem_status = DUMP_MEM_IDLE;
    p_exception_data->dump_mem[SUBSYS_WIFI].total_size= 0;
    p_exception_data->dump_mem[SUBSYS_WIFI].recved_size= 0;
    p_exception_data->dump_mem[SUBSYS_WIFI].exception_mem_addr = NULL;
    p_exception_data->dump_mem[SUBSYS_BFGX].mem_status = DUMP_MEM_IDLE;
    p_exception_data->dump_mem[SUBSYS_BFGX].total_size= 0;
    p_exception_data->dump_mem[SUBSYS_BFGX].recved_size= 0;
    p_exception_data->dump_mem[SUBSYS_BFGX].exception_mem_addr = NULL;

    p_exception_data->exception_reset_enable   = false;
    p_exception_data->wifi_exception_cnt       = 0;
    p_exception_data->bfgx_exception_cnt       = 0;
    p_exception_data->reset_device_msg         = RESET_MSG_NONE;
    p_exception_data->ps_plat_d                = NULL;
    p_exception_data->wifi_callback            = NULL;

    atomic_set(&p_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);
    atomic_set(&p_exception_data->bfgx_rf_temperature_status, RF_TEMERATURE_NORMAL);
    atomic_set(&p_exception_data->wifi_rf_temperature_status, RF_TEMERATURE_NORMAL);
    atomic_set(&p_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_IDLE);

    /*初始化异常处理workqueue和work*/
    p_exception_data->plat_exception_rst_workqueue = create_singlethread_workqueue("plat_exception_reset_queue");
    INIT_WORK(&p_exception_data->plat_exception_rst_work, plat_exception_reset_work);

    /*初始化心跳timer*/
    init_timer(&p_exception_data->bfgx_beat_timer);
    p_exception_data->bfgx_beat_timer.function = bfgx_beat_timer_expire;
    p_exception_data->bfgx_beat_timer.expires  = jiffies + BFGX_BEAT_TIME*HZ;
    p_exception_data->bfgx_beat_timer.data     = 0;

    /*初始化bfgx rf温度查询timer*/
    init_timer(&p_exception_data->bfgx_rf_overheat_timer);
    p_exception_data->bfgx_rf_overheat_timer.function = bfgx_rf_overheat_expire;
    p_exception_data->bfgx_rf_overheat_timer.expires  = jiffies + BFGX_RF_QUERY_TIME*HZ;
    p_exception_data->bfgx_rf_overheat_timer.data     = 0;

    /*初始化wifi rf温度查询timer*/
    init_timer(&p_exception_data->wifi_rf_overheat_timer);
    p_exception_data->wifi_rf_overheat_timer.function = wifi_rf_overheat_expire;
    p_exception_data->wifi_rf_overheat_timer.expires  = jiffies + WIFI_RF_QUERY_TIME*HZ;
    p_exception_data->wifi_rf_overheat_timer.data     = 0;

    /*初始化异常处理互斥锁*/
    mutex_init(&p_exception_data->exception_reset_mutex);

    /*初始化异常处理自旋锁*/
    spin_lock_init(&p_exception_data->exception_spin_lock);

    /*初始化bfgx读栈完成量*/
    init_completion(&p_exception_data->wait_read_bfgx_stack);

    /*调试使用的变量初始化*/
    p_exception_data->debug_beat_flag          = 1;

    g_pst_exception_info = p_exception_data;

    PS_PRINT_SUC("plat exception reset init success\n");

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_init);


int32 plat_exception_reset_exit(void)
{
    struct st_exception_info *p_exception_data = NULL;

    p_exception_data = g_pst_exception_info;
    if (p_exception_data == NULL)
    {
        PS_PRINT_ERR("g_pst_exception_info is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    destroy_workqueue(p_exception_data->plat_exception_rst_workqueue);
    del_timer_sync(&p_exception_data->bfgx_rf_overheat_timer);
    del_timer_sync(&p_exception_data->wifi_rf_overheat_timer);
    del_timer_sync(&p_exception_data->bfgx_beat_timer);

    kfree(p_exception_data->dump_mem[SUBSYS_WIFI].exception_mem_addr);
    kfree(p_exception_data->dump_mem[SUBSYS_BFGX].exception_mem_addr);
    kfree(p_exception_data);
    g_pst_exception_info = NULL;

    PS_PRINT_SUC("plat exception reset exit success\n");

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_exit);


