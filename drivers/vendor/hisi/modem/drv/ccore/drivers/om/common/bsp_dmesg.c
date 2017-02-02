
/*lint -save -e537 -e830 -e525 -e64*/
#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <semLib.h>
#include <taskLib.h>
#include <stdio.h>
#endif
#ifdef __OS_RTOSCK__
#include <osl_sem.h>
#include <osl_thread.h>
#include <sre_libc.h>
#include <sre_shell.h>
#include <sre_io_intf.h>
#endif
#include "securec.h" 

#include <string.h>
#include "osl_common.h"
#include "osl_irq.h"
#include "mdrv.h"
#include "bsp_dump_drv.h"
#include "bsp_memmap.h"
#include "bsp_om.h"
#include "bsp_ipc.h"
/*lint -restore*/

typedef void (* funcvoid)(void);

extern  void cshell_register_hook(print_hook hook);

#ifdef __OS_VXWORKS__
extern void cshell_send_data(char* data, int length);
void dmesg_cshell_hook(void);
#endif
int  dmesg_get_char(char *out_char);
int dmesg_charter_send_hook(char* charter);


#define __LOG_BUF_LEN	        (DUMP_DMESG_SIZE)
#define DUMP_PRINT_MAGIC        (0x32324554)
#define LOG_BUF_MASK            (__LOG_BUF_LEN -1)
#define LOG_BUF(idx)            (g_dmesg_buff->log_buf[(idx) & LOG_BUF_MASK])

typedef struct
{
    u32     magic;          /* magic number for print section */
    u32     log_read;       /* read pointer, update by acore */
    u32     log_write;      /* write pointer, update by dmesg_write */
    u32     logged_chars;   /* number of chars in log buffer */
    u32     log_buf_len;    /* buffer length */
    u32     w_mark;         /* water mark, if logged chars exceed w_mark, send IPC to acore */
    u32     full_flag;      /* set this flag when ccore send IPC, acore clear this flag after data consumption */
    u32     reserved;       /* reserved for 32-byte align */
    s8 *    log_buf;        /* data area */
}log_mem_stru;

typedef struct
{
    s8 *    buffer1;
    s8 *    buffer2;
    u32     size1;
    u32     size2;
    u32     poff1;
    u32     poff2;
}dmesg_print;

log_mem_stru *  g_dmesg_buff = NULL;
BSP_BOOL        dmesg_enable = BSP_FALSE;
dmesg_print     g_dmesg_print;
extern u32  g_dump_product_type;


char * dmesg_buf = NULL;

void dmesg_clear_pbuff(int ix)
{
    if(1 == ix)
    {
        g_dmesg_print.buffer1 = NULL;
        g_dmesg_print.size1 = 0;
        g_dmesg_print.poff1 = 0;
    }
    else if(2 == ix)
    {
        g_dmesg_print.buffer2 = NULL;
        g_dmesg_print.size2 = 0;
        g_dmesg_print.poff2 = 0;
    }
}
/*lint -save -e830 -e525*/
static void emit_log_char(char c)
{
	LOG_BUF(g_dmesg_buff->log_write) = c;
	g_dmesg_buff->log_write++;

	if (g_dmesg_buff->log_write >= g_dmesg_buff->log_buf_len)
	{
    	//LOG_BUF(g_dmesg_buff->log_end -1) = 0;
		g_dmesg_buff->log_write = 0;
    }
	if (g_dmesg_buff->logged_chars < g_dmesg_buff->log_buf_len)
		g_dmesg_buff->logged_chars++;
}
/*lint -restore*/
static void dmesg_notify_acore(void)
{
    if(g_dump_product_type == DUMP_MBB)
    {
        (void)bsp_ipc_int_send(IPC_CORE_ACORE, IPC_ACPU_INT_SRC_CCPU_LOG);
    }
}

/*lint -save -e18*/
int dmesg_write(const char* buffer, const unsigned len)
{
	char* buff  = (char*)buffer;
    u32 read_p;
    u32 write_p;

    if(dmesg_enable != BSP_TRUE)
    {
        return 0;
    }

    read_p  = g_dmesg_buff->log_read;
    write_p = g_dmesg_buff->log_write;

    if(!g_dmesg_buff->full_flag)
    {
        if(read_p <= write_p)
        {
            if(write_p - read_p + len > g_dmesg_buff->w_mark)
            {
                g_dmesg_buff->full_flag = 1;
                dmesg_notify_acore();
            }
        }
        else
        {
            if(write_p + g_dmesg_buff->log_buf_len - read_p + len > g_dmesg_buff->w_mark)
            {
                g_dmesg_buff->full_flag = 1;
                dmesg_notify_acore();
            }
        }
    }
    /*lint -save -e539*/

	while(buff < buffer + len)
	{
		(void)emit_log_char(*buff);
		buff++;
	}
    /*lint -restore +e539*/
	return buff - buffer;
}
/*lint -restore +e18*/

__inline__ void dmesg_start()
{
	dmesg_enable = BSP_TRUE;
    return;
}

__inline__ void dmesg_stop()
{
	dmesg_enable = BSP_FALSE;
    return;
}

/*lint -save -e64*/
void dmesg_init(void)
{
    dmesg_buf = (char *)(DUMP_DMESG_ADDR);

    (void)memset_s(dmesg_buf, DUMP_DMESG_SIZE,0, DUMP_DMESG_SIZE);

	g_dmesg_buff = (log_mem_stru *)dmesg_buf;
	g_dmesg_buff->magic = DUMP_PRINT_MAGIC;
	g_dmesg_buff->log_read = 0;
	g_dmesg_buff->log_write = 0;
	g_dmesg_buff->logged_chars = 0;
	g_dmesg_buff->log_buf_len = __LOG_BUF_LEN - sizeof(log_mem_stru);
        
    /* coverity[suspicious_pointer_arithmetic] */
	g_dmesg_buff->log_buf = (s8 *)(g_dmesg_buff + sizeof(log_mem_stru));
    g_dmesg_buff->w_mark = g_dmesg_buff->log_buf_len - (g_dmesg_buff->log_buf_len)/4;

    dmesg_clear_pbuff(1);
    dmesg_clear_pbuff(2);
#ifdef __OS_VXWORKS__
    balongv7r2_uart_register_hook(dmesg_get_char);
    cshell_register_hook(dmesg_cshell_hook);
#else
    /*×¢²áÊä³ö×Ö·û¹³×Óº¯Êý*/
    //SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)dmesg_hshell_hook);
    uart_register_hook(dmesg_charter_send_hook);
    cshell_register_hook(dmesg_charter_send_hook);


#endif
	dmesg_start();
}
/*lint -restore*/


int dmesg_save(const char* buffer, const unsigned length)
{
    u32 end = 0;
    u32 len = 0, chars = 0;
    s8 *s1, *s2;
    u32 l1, l2;

	end = g_dmesg_buff->log_write;
	chars = g_dmesg_buff->logged_chars;
    len = g_dmesg_buff->log_buf_len;
    /*lint -save -e830 -e525 -e64*/
	if (chars >= len) {
		s1 = (s8*)(g_dmesg_buff->log_buf + end);
		l1 = len - end;

		s2 = (s8*)g_dmesg_buff->log_buf;
		l2 = end; /* [false alarm]:ÆÁ±ÎFority´íÎó */
	}
    else {
		s1 = NULL;
		l1 = 0;

		s2 = (s8*)g_dmesg_buff->log_buf;
		l2 = chars; /* [false alarm]:ÆÁ±ÎFority´íÎó */
	}
    /*lint -restore +e830 +e525 +e64*/

    if((s1 != NULL) && (l1 != 0))
    {
        (void)memcpy_s((void *)buffer, (u32)l1,(void *)s1, (u32)l1);
    }
    (void)memcpy_s((void *)(buffer+l1), (u32)l2,(void *)s2, (u32)l2);

    return 0;
}

void dmesg(void)
{
    u32 end, chars, len;
    unsigned long lock_key;

    local_irq_save(lock_key);

    if(g_dmesg_buff)
    {
    	end = g_dmesg_buff->log_write;
    	chars = g_dmesg_buff->logged_chars;
        len = g_dmesg_buff->log_buf_len;
        /*lint -save -e64*/
    	if (chars >= len) {
            g_dmesg_print.poff1 = 0;
    		g_dmesg_print.buffer1 = (s8*)(g_dmesg_buff->log_buf + end);
    		g_dmesg_print.size1 = (u32)(len - end);
            g_dmesg_print.poff2 = 0;
    		g_dmesg_print.buffer2 = (g_dmesg_buff->log_buf);
    		g_dmesg_print.size2 = (u32)end;
    	}
        else if(chars > 0)
        {
            dmesg_clear_pbuff(1);
            g_dmesg_print.poff2 = 0;
    		g_dmesg_print.buffer2 = g_dmesg_buff->log_buf;
    		g_dmesg_print.size2 = (u32)chars;
    	}
        else
        {
            dmesg_clear_pbuff(1);
            dmesg_clear_pbuff(2);
        }
        /*lint -restore +e64*/
    }
    else
    {
        dmesg_clear_pbuff(1);
        dmesg_clear_pbuff(2);
    }

    local_irq_restore(lock_key);

    return;
}

int dmesg_get_char(char *out_char)
{
    if(g_dmesg_print.buffer1 && g_dmesg_print.size1)
    {
        if(g_dmesg_print.poff1 < g_dmesg_print.size1)
        {
            *out_char = (char)(g_dmesg_print.buffer1[g_dmesg_print.poff1++]);
            return BSP_OK;
        }
        else
        {
            dmesg_clear_pbuff(1);
        }
    }

    if(g_dmesg_print.buffer2 && g_dmesg_print.size2)
    {
        if(g_dmesg_print.poff2 < g_dmesg_print.size2)
        {
            *out_char = (char)(g_dmesg_print.buffer2[g_dmesg_print.poff2++]);
            return BSP_OK;
        }
        else
        {
            dmesg_clear_pbuff(2);
        }
    }

    return BSP_ERROR;
}
#ifdef __OS_VXWORKS__
void dmesg_cshell_hook(void)
{
    if(g_dmesg_print.buffer1 && g_dmesg_print.size1)
    {
        cshell_send_data((char *)g_dmesg_print.buffer1, (int)g_dmesg_print.size1);
        dmesg_clear_pbuff(1);
    }

    if(g_dmesg_print.buffer2 && g_dmesg_print.size2)
    {
        cshell_send_data((char *)g_dmesg_print.buffer2, (int)g_dmesg_print.size2);
        dmesg_clear_pbuff(2);
    }
}

#else
int dmesg_charter_send_hook(char* charter)
{

    emit_log_char((char)(*charter));
 
   return MDRV_OK;
}

#endif


