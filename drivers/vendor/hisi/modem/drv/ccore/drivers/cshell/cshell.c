/*
 * cshell.c -- balong cshell driver
 *
 * Copyright (C) 2012 Huawei Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <sre_io_intf.h>
#include <string.h>
#include "securec.h"
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <hi_uart.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_shared_ddr.h>
#include "cshell.h"

//cprint_hook g_cprint_hook = NULL;
struct cshell_debug g_cshell_dbg = {0};
static struct cshell_ctl cshell_ctl_info =
{
	.send_permit.uint_path = 0
};
static print_hook g_print_hook = NULL;

void cshell_register_hook(print_hook hook)
{
    g_print_hook = hook;
}

static int cshell_fifo_empty(struct ring_fifo_ctl * fifo)
{
	if(fifo->r_idx == fifo->w_idx)
		return 1;
	return 0;
}

static int cshell_fifo_full(struct ring_fifo_ctl * fifo)
{
	if((fifo->w_idx + 1) % fifo->size == fifo->r_idx)
		return 1;
	return 0;
}

static int cshell_fifo_get_data_sz(struct ring_fifo_ctl * fifo)
{
	return ((int)fifo->w_idx - (int)fifo->r_idx + (int)fifo->size) % (int)fifo->size;
}

static int cshell_fifo_get_read_addr(struct ring_fifo_ctl * fifo, void ** addr, int len)
{
	int data_sz = 0;

	*addr = (void*)((unsigned long)fifo->base + fifo->r_idx);
	if(fifo->r_idx <= fifo->w_idx)
		data_sz = (int)(fifo->w_idx - fifo->r_idx);
	else
		data_sz = (int)(fifo->size - fifo->r_idx);
	return data_sz <= len ? data_sz : len;
}

static void cshell_fifo_move_widx(struct ring_fifo_ctl * fifo, unsigned int offset)
{
	fifo->w_idx += offset;
	fifo->w_idx %= fifo->size;
}

static void cshell_fifo_move_ridx(struct ring_fifo_ctl * fifo, unsigned int line_pos)
{
	fifo->r_idx = fifo->r_idx < line_pos ? line_pos : fifo->r_idx;
	fifo->r_idx = fifo->r_idx % fifo->size;
}

static int cshell_ctl_cb(unsigned int chan_id, unsigned int len, void * context)
{
	int          recv_sz = 0;
	unsigned int flag    = 0;

	recv_sz = bsp_icc_read((ICC_CHN_IFC << 16) | IFC_RECV_FUNC_CSHELL, (unsigned char*)&flag, len);
	if ((recv_sz > (int)len) && (recv_sz < 0))
        return MDRV_ERROR;

	cshell_ctl_info.send_permit.uint_path = (unsigned int)flag;
	return MDRV_OK;
}

static int cshell_cmd_cb(unsigned int channel_id , unsigned int len, void * context)
{
	int i       = 0;
	int recv_sz = 0;
	unsigned char * recv_buf = (unsigned char *)cshell_ctl_info.recv_buf->base + cshell_ctl_info.recv_buf->w_idx;
	unsigned int icc_chn_id = cshell_ctl_info.icc_chn_id;

	if(!len)
	{
		cshell_print_error("C:cshell_read_cb fail for zero length data\n");
		return MDRV_ERROR;
	}

	if(len > (cshell_ctl_info.recv_buf->size - cshell_ctl_info.recv_buf->w_idx))
	{
		memset_s(recv_buf, cshell_ctl_info.recv_buf->size - cshell_ctl_info.recv_buf->w_idx, 0,
			cshell_ctl_info.recv_buf->size - cshell_ctl_info.recv_buf->w_idx);
		recv_buf = cshell_ctl_info.recv_buf->base;
	}

	recv_sz = (int)bsp_icc_read(icc_chn_id, recv_buf, len);
	if ((recv_sz > (int)len) || (recv_sz < 0))
	{
		cshell_print_error("C:cshell_read_cb fail [0x%x]\n", recv_sz);
		return MDRV_ERROR;
	}
	cshell_ctl_info.recv_buf->w_idx = ((unsigned int)(recv_buf - (unsigned char *)(cshell_ctl_info.recv_buf->base)) + (unsigned int)recv_sz) % cshell_ctl_info.recv_buf->size;
	cshell_ctl_info.recv_buf->r_idx = cshell_ctl_info.recv_buf->w_idx;

	g_cshell_dbg.recv_data_cnt++;

	for(i = 0; i < recv_sz; i++)
		(void)SRE_SendChrToShell(*((unsigned char*)recv_buf + i));

	return MDRV_OK;
}

int cshell_sys_recv_fun(char ch)
{
	unsigned char * wr_addr = NULL;
	unsigned long spinlock_flag = 0;

	if('\0' == ch)
		return MDRV_OK;

	if(g_print_hook)
		(void)g_print_hook(&ch);

	if(cshell_fifo_full(cshell_ctl_info.send_buf))
	{
		g_cshell_dbg.obuf_full_cnt++;
		spin_lock_irqsave(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
		cshell_fifo_move_ridx(cshell_ctl_info.send_buf, cshell_ctl_info.send_buf->r_idx + 1);
		spin_unlock_irqrestore(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
	}
	wr_addr = (unsigned char *)cshell_ctl_info.send_buf->base + cshell_ctl_info.send_buf->w_idx;
	*wr_addr = (unsigned char)ch;
	cshell_fifo_move_widx(cshell_ctl_info.send_buf, 1);
	osl_sem_up(&cshell_ctl_info.sem_send_tsk);

	return MDRV_OK;
}

void cshell_send_tsk(void * tsk_para)
{
	struct ring_fifo_ctl * send_fifo = cshell_ctl_info.send_buf;
	void * data_addr = NULL;
	int    data_size = 0;
	unsigned long spinlock_flag = 0;
	long sem_wait_tick = -1L;//WAIT_FOREVER;
	int wr_len = 0;


	/* coverity[no_escape] */
	for(;;)
	{
		if(MDRV_OK != osl_sem_downtimeout(&cshell_ctl_info.sem_send_tsk, sem_wait_tick))
			continue;

		if(cshell_fifo_empty(send_fifo) || !cshell_ctl_info.send_permit.uint_path)
			continue;

		while(!cshell_fifo_empty(send_fifo))
		{
			data_size = cshell_fifo_get_data_sz(send_fifo);
			data_size = cshell_fifo_get_read_addr(send_fifo, &data_addr, data_size <= CSHELL_ICC_FIFO_DEPTH ? data_size : CSHELL_ICC_FIFO_DEPTH);
			wr_len = bsp_icc_send(ICC_CPU_APP, cshell_ctl_info.icc_chn_id, data_addr, (unsigned int)data_size);
			if(wr_len < 0)
			{
				++g_cshell_dbg.send_fail_cnt;
				sem_wait_tick = 1;
				break;
			}
			else if(wr_len < data_size)
			{
				++g_cshell_dbg.send_busy_cnt;
				spin_lock_irqsave(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
				cshell_fifo_move_ridx(send_fifo, (unsigned int)data_addr - (unsigned int)cshell_ctl_info.send_buf->base + (unsigned int)wr_len);
				spin_unlock_irqrestore(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
				sem_wait_tick = 1;
				break;
			}
			else if(wr_len == data_size)
			{
				++g_cshell_dbg.send_succ_cnt;
				spin_lock_irqsave(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
				cshell_fifo_move_ridx(send_fifo, (unsigned int)data_addr - (unsigned int)cshell_ctl_info.send_buf->base + (unsigned int)wr_len);
				spin_unlock_irqrestore(&cshell_ctl_info.ridx_sync_lock, spinlock_flag);
				sem_wait_tick = -1L;//WAIT_FOREVER;
			}
		}/* while(!(*send_fifo->fifo_empty)(send_fifo)) */
	}/* for(;;) */
}

extern void uart_poll_send(unsigned char ch);
int cshell_direction(enum cshell_mode_tpye mode)
{
	unsigned long irq_flag = 0;

	if(cshell_ctl_info.shell_mode == mode)
	{
		cshell_print_error("C:no need to redirect cshell!\n");
		return MDRV_OK;
	}

	local_irq_save(irq_flag);
	osl_task_lock();

	if(CSHELL_MODE_USB == mode)
		(void)SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)cshell_sys_recv_fun);
	else
		(void)SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)uart_poll_send);
	cshell_ctl_info.shell_mode = mode;

	osl_task_unlock();
	local_irq_restore(irq_flag);

    return MDRV_OK;
}

static int cshell_buf_init(struct ring_fifo_ctl ** fifo_ctl, unsigned int sz)
{
	struct ring_fifo_ctl * buf_ctl = NULL;

	*fifo_ctl = (struct ring_fifo_ctl *)osl_malloc(sizeof(struct ring_fifo_ctl));
	if(NULL == *fifo_ctl)
	{
		cshell_print_error("send buf malloc fail!\n");
		return MDRV_ERROR;
	}
	buf_ctl = *fifo_ctl;
	buf_ctl->r_idx = 0;
	buf_ctl->w_idx = 0;
	buf_ctl->size  = 0;
	osl_sem_init(SEM_FULL, &buf_ctl->mutex);
	buf_ctl->base = osl_malloc(sz);
	if (NULL == buf_ctl->base)
	{
		cshell_print_error("buf_ctl->base malloc fail!\n");
		osl_free(*fifo_ctl);
		return MDRV_ERROR;
	}
	buf_ctl->size = sz;
    return MDRV_OK;
}

int cshell_init(void)
{
	int retval = 0;
	DRV_UART_SHELL_FLAG uartcshell_nv = {.extendedbits = 0};

	retval = (int)bsp_nvm_read(NV_ID_DRV_UART_SHELL_FLAG, (unsigned char *)&uartcshell_nv, sizeof(DRV_UART_SHELL_FLAG));
	if(retval)
		cshell_print_error("bsp_nvm_read fails uartcshell_nv.cshell_to_auart:%d\n", uartcshell_nv.extendedbits);
	if(uartcshell_nv.extendedbits & 0x1U)
		cshell_ctl_info.send_permit.bit_path.uart_path = 1;

	osl_sem_init(SEM_EMPTY, &cshell_ctl_info.sem_send_tsk);
	spin_lock_init(&cshell_ctl_info.ridx_sync_lock);

	retval  = cshell_buf_init(&cshell_ctl_info.send_buf, IO_BUFFER_MAX * 2);
	retval += cshell_buf_init(&cshell_ctl_info.recv_buf, IO_BUFFER_MAX);
	if (retval)
	{
		cshell_print_error("buffer init fail!\n");
		return MDRV_ERROR;
	}

	cshell_ctl_info.icc_chn_id     = (ICC_CHN_CSHELL << 16) | 0;
	cshell_ctl_info.icc_chn_id_ctl = (ICC_CHN_IFC    << 16) | IFC_RECV_FUNC_CSHELL;
	retval  = bsp_icc_event_register(cshell_ctl_info.icc_chn_id    , (read_cb_func)cshell_cmd_cb, NULL, NULL, NULL);
	retval += bsp_icc_event_register(cshell_ctl_info.icc_chn_id_ctl, (read_cb_func)cshell_ctl_cb, NULL, NULL, NULL);
	if(retval)
	{
		cshell_print_error("register icc callback fail!\n");
		return MDRV_ERROR;
	}

	if(readl(SHM_OFFSET_CHSELL_FLAG + (unsigned long)SHM_BASE_ADDR) == PRT_FLAG_EN_MAGIC_M)
		(void)cshell_direction(CSHELL_MODE_USB);
	else
		(void)cshell_direction(CSHELL_MODE_UART);

	(void)memset_s((void *)&g_cshell_dbg, sizeof(g_cshell_dbg), 0, sizeof(g_cshell_dbg));
	retval = osl_task_init("cshell_send_tsk", CSHELL_TASK_PRI, CSHELL_TASK_STACK_SIZE,
		(OSL_TASK_FUNC)cshell_send_tsk, NULL, &cshell_ctl_info.send_tsk_id);
	if(retval)
	{
		cshell_print_error("cshell_send_tsk init fials\n");
		return MDRV_ERROR;
	}

	g_cshell_dbg.state = 1;
   	cshell_print_error("cshell_init ok\n");
    return MDRV_OK;
}

int cshell_debug_show(void)
{
	cshell_print_error("*****************************************************\n");
	cshell_print_error("g_cshell_dbg.state        : 0x%08x\n", g_cshell_dbg.state);
	cshell_print_error("g_cshell_dbg.obuf_full_cnt: 0x%08x\n", g_cshell_dbg.obuf_full_cnt);
	cshell_print_error("g_cshell_dbg.lost_data_cnt: 0x%08x\n", g_cshell_dbg.lost_data_cnt);
	cshell_print_error("g_cshell_dbg.recv_data_cnt: 0x%08x\n", g_cshell_dbg.recv_data_cnt);
	cshell_print_error("g_cshell_dbg.send_succ_cnt: 0x%08x\n", g_cshell_dbg.send_succ_cnt);
	cshell_print_error("g_cshell_dbg.send_busy_cnt: 0x%08x\n", g_cshell_dbg.send_busy_cnt);
	cshell_print_error("g_cshell_dbg.send_fail_cnt: 0x%08x\n", g_cshell_dbg.send_fail_cnt);

	return MDRV_OK;
}
