/* cshell.h -  balong cshell driver header file */

/* Copyright (C) 2012 Huawei Corporation */

#ifndef __CSHELL__
#define __CSHELL__

#ifdef __cplusplus
extern "C" {
#endif


#include <osl_types.h>
#include <osl_malloc.h>
#include <osl_sem.h>
#include <bsp_om.h>

#define SIO_IRDA_MODE               0x1040
#define UART_DMA_MODE               0x1041
#define IO_BUFFER_MAX               8192
#define IO_BUFFER_LEVEL             2048
#define TTY_BUFFER_MAX              2048
#define CSHELL_ICC_FIFO_DEPTH       3072
#define CSHELL_ICC_CHANNEL_ID       31
#define CSHELL_TASK_PRI             (20)
#define CSHELL_TASK_STACK_SIZE      (0x400)
#define CSHELL_OK                   0
#define CSHELL_ERROR                (-1)

#ifndef min
#define min(__x,__y)                ((__x)<(__y)?(__x):(__y))
#endif


#define cshell_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CSHELL, "[cshell]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define cshell_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO,  BSP_MODU_CSHELL, "[cshell]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define cshell_print_debug(fmt, ...)            \
do {                                            \
        cshell_print_error(fmt, ##__VA_ARGS__); \
} while (0)

enum cshell_mode_tpye
{
	CSHELL_MODE_UART,
	CSHELL_MODE_USB
};

struct ring_fifo_ctl
{
	void *       base; /* buffer base                            */
	unsigned int size; /* buffer size in byte                    */
	unsigned int w_idx;/* the byte index to be writen, from zero */
	unsigned int r_idx;/* the byte index to be read, from zero   */
	osl_sem_id   mutex;/* mutex for serial operation             */
	char pad[2];
};

struct cshell_ctl
{
	struct ring_fifo_ctl * send_buf;       /* buffer to recieve data from systerm */
	struct ring_fifo_ctl * recv_buf;       /* buffer to recieve data from acore   */  
	unsigned int           icc_chn_id;     /* icc channel for cshell of ccore     */
	unsigned int           icc_chn_id_ctl; /* icc channel to be used to send cmd  */
	union
	{
		unsigned int uint_path;
		struct
		{
			unsigned int usb_path   : 1;
			unsigned int uart_path  : 1;
			unsigned int fnode_path : 1;
			unsigned int reserve    : 29;
		}bit_path;
	}send_permit;                          /* permisson flag to identify which path of accore admits to send log */
	enum cshell_mode_tpye  shell_mode;     /* identify that log is sent to c-uart or c-cshell                    */
	OSL_TASK_ID            send_tsk_id;    /* task id that sends log to acore through icc                        */
	osl_sem_id             sem_send_tsk;   /* sem that block send task when no log to send                       */
	spinlock_t             ridx_sync_lock; /* sem that block recieve sys cb function when buffer full            */
};

struct cshell_debug
{
    unsigned int state;
	unsigned int obuf_full_cnt;
	unsigned int lost_data_cnt;
	unsigned int recv_data_cnt;
	unsigned int send_fail_cnt;
	unsigned int send_succ_cnt;
	unsigned int send_busy_cnt;
};

typedef void (*cprint_hook)(void);


#ifdef __cplusplus
}
#endif

#endif
