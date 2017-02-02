
/*lint --e{438,525,539,550,570,628,701,713,718,732,734,737,746,813} */
#include <of.h>
#include "securec.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_thread.h"
#include "bsp_sysctrl.h"
#include "bsp_gpio.h"
#include "bsp_dump.h"
#include "bsp_hardtimer.h"
#include "mdrv_dual_modem.h"
#include "dual_modem.h"
#ifdef CONFIG_CCORE_PM
#include "bsp_dpm.h"
#endif

struct dual_modem_control g_dual_modem_ctrl={{0},{0},{0},{0},0};
struct dm_dump_info	*g_dm_dump_info = NULL;

/*****************************************************************************
 �� �� ��  : recv_lpm3_msg_icc_cb
 ��������  : ��lpm3��ת���Ļ�����Ϣ or ����v3 modemʱ�õ���ȷ����Ϣ 
 �������  : UART_HW_DESC* uart_hw_desc
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
#ifdef LPM3_VIA_GPIO
static int recv_lpm3_msg_icc_cb(u32 chan_id, u32 len, void* context)
{
	u8 flag = 0;
	s32 read_size = 0;
	
 	read_size = bsp_icc_read((ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART, &flag, len); 
	if ((read_size > (s32)len) && (read_size <= 0))
	{
		return ERROR;
	}

	if(g_dual_modem_ctrl.init_flag != DUAl_MODEM_ENABLE)
	{
		dm_print_err("dual modem not init\n");
		return OK;
	}
	
	if(flag == VIA_WAKEUP_BALONG)
	{
		wake_lock(&g_dual_modem_ctrl.wakelock);	
		dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
		cpcp_msg_count_record(&g_dm_dump_info->via_wakeup_balong_cnt, "WakeupBalongcnt");
	}
	if(flag == UART_INIT_ENABLE)
	{
		dm_print_err("lpm3 revc uart init icc\n");
	}
	return OK;
}
#else
static irqreturn_t wakeup_gpio_int(int irq,void *dev)
{
	if(g_dual_modem_ctrl.init_flag != DUAl_MODEM_ENABLE)
	{
		dm_print_err("dual modem not init\n");
		return IRQ_HANDLED;
	}

	wake_lock(&g_dual_modem_ctrl.wakelock);	
	dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
	cpcp_msg_count_record(&g_dm_dump_info->via_wakeup_balong_cnt,"WakeupBalongcnt_mdm");
	return IRQ_HANDLED;
}
#endif
/*****************************************************************************
 �� �� ��  : uart_port_hw_init
 ��������  : ���ò�����
 �������  : UART_HW_DESC* uart_hw_desc
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
void dual_modem_uart_channel_init(UART_PORT *uart_hw_desc)
{
	unsigned long  lock_flag = 0;
	u32  ul_divisor;
	unsigned int fbrd = 0;
	
    if(NULL == uart_hw_desc)
    {
        dm_print_err("uart_hw_desc is null\n");
        return;
    }
    spin_lock_irqsave(&g_dual_modem_ctrl.lock, lock_flag);
    writel(UART_DISABLE, (u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_CR);	
    writel(UART_IFLS_RX_DEF_ONETWO, (u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_IFLS);
    writel(UART_IRQ_CLR,(u32)(uart_hw_desc)->base_addr+ UART_REGOFFSET_ICR);
    ul_divisor = uart_hw_desc->clk/(u32)(16 * uart_hw_desc->baudrate);		/* [false alarm]:�� */
    writel(ul_divisor, (u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_IBRD);
	/*
    *fbrd:(clk % (16 * baud)) / (16 * baud) * 64 + 0.5
     */
    fbrd = uart_hw_desc->clk % (16 * uart_hw_desc->baudrate);
    fbrd *= (1UL << 6);
    fbrd *= 2;
    fbrd += 16 * uart_hw_desc->baudrate;
    fbrd /= (u32)(2 * 16 * uart_hw_desc->baudrate);
    writel(fbrd, (u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_FBRD);
   
    writel((UART_LCR_PEN_NONE | UART_LCR_STOP_1BITS | UART_ARM_LCR_DLS_8BITS | UART_LCR_FIFO_ENABLE),(u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_LCR_H);
	writel(UART_RX_IRQ_ENABLE | UART_TIMEOUT_IRQ_ENABLE, (u32)(uart_hw_desc)->base_addr+ UART_REGOFFSET_IMSC);	
	writel(UART_TX_ENABLE |UART_RX_ENABLE |UART_ENABLE | uart_hw_desc->rts_mask, (u32)(uart_hw_desc)->base_addr + UART_REGOFFSET_CR);

    spin_unlock_irqrestore(&g_dual_modem_ctrl.lock, lock_flag);
}
/*****************************************************************************
 �� �� ��  : uart_core_recv_handler_register
 ��������  : �û��������ݻص�ע��ӿ�
 �������  : UART_CONSUMER_PORT uPortNo
             pUARTRecv pCallback
 �������  : ��
 �� �� ֵ  : int
*****************************************************************************/
int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback)
{
	UART_PORT * cur_port = &g_dual_modem_ctrl.uart_port;
	if(NULL == pCallback)
    {
        dm_print_err("register null\n",uPortNo); /* [false alarm]:�� */
        return ERROR;
    }
    if(CBP_UART_PORT_ID != uPortNo)
    {
        dm_print_err("uart port err\n",uPortNo); /* [false alarm]:�� */
        return ERROR;
    }
    cur_port->recv_callback = pCallback;
    g_dm_dump_info->recv_register_cnt++;
	
    return OK;
}

/*****************************************************************************
 �� �� ��  : uart_send
 ��������  : uart send
 �������  : UART_HW_PORT* uart_port
             BSP_U8 *pbuf
             BSP_U32 size
 �������  : ��
 �� �� ֵ  : BSP_S32
*****************************************************************************/
int dual_modem_send_bytes(UART_PORT* uart_port,u8* pbuf,u32 size)
{
	u8 * pu8Buffer = NULL;
	u32  regval = 0;
	
    pu8Buffer = pbuf;
 
    osl_sem_down(&uart_port->send_mutex);	
	
	g_dm_dump_info->send_mutex_cnt++;
	g_dm_dump_info->tx_cur_size = size;
	g_dm_dump_info->tx_total_size += size;

	g_dm_dump_info->send_time_stamp = bsp_get_slice_value();
	if(g_dm_dump_info->tx_cur_offset + 4 > DUAL_DUMP_TX_BUFF_SIZE)
	{
		g_dm_dump_info->tx_cur_offset = 0;
	}
	*(g_dm_dump_info->tx_dump_addr + g_dm_dump_info->tx_cur_offset) = g_dm_dump_info->send_time_stamp;
	g_dm_dump_info->tx_cur_offset += 4;

	if(g_dual_modem_ctrl.log_flag == 1)
	{	
		dm_debug_print("TxCurSize %d,TxTotalSize %d\n",g_dm_dump_info->tx_cur_size,g_dm_dump_info->tx_total_size);
		(void)dm_print_info(pu8Buffer ,size);	/* lint !e532 */
	}	
	while(size)
	{
		regval = readl(uart_port->base_addr+ UART_REGOFFSET_FR);
		if(0 == (regval & UART_FR_TX_FIFO_FULL))
    	{
			writel(*pu8Buffer, uart_port->base_addr + UART_REGOFFSET_THR);
			*(g_dm_dump_info->tx_dump_addr + g_dm_dump_info->tx_cur_offset) = *pu8Buffer;
			g_dm_dump_info->tx_cur_offset++;
			if(g_dm_dump_info->tx_cur_offset > DUAL_DUMP_TX_BUFF_SIZE)
			{
				g_dm_dump_info->tx_cur_offset = 0;
			}
			pu8Buffer++;
			size--;
      	}
	}
	
	osl_sem_up(&uart_port->send_mutex);
	return OK;
}

/*****************************************************************************
 �� �� ��  : uart_core_send
 ��������  : ��������
 �������  : UART_CONSUMER_PORT uPortNo
             unsigned char * pDataBuffer
             unsigned int uslength
 �������  : ��
 �� �� ֵ  : int
*****************************************************************************/
int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int uslength)
{
	UART_PORT* cur_port = &g_dual_modem_ctrl.uart_port;
	
	if(DUAl_MODEM_ENABLE != g_dual_modem_ctrl.init_flag)
	{
		dm_print_err("dual modem not init\n");
		return ERROR;
	}
	
	cpcp_msg_count_record(&g_dm_dump_info->cbpa_send_cnt, "CbpaSendCnt");
	if(NULL == pDataBuffer)
    {
        dm_print_err("pDataBuffer is null\n");
        return ERROR;
    }
	
	wake_lock(&g_dual_modem_ctrl.wakelock);
	bsp_softtimer_delete(&g_dual_modem_ctrl.sleep_timer);
	if(g_dual_modem_ctrl.wakeup_3rdmodem_flag == DO_WAKEUP_3RD)
	{
		if(OK != wakeup_via_modem())
		{
            dm_print_err("wakeup err\n");
			dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
		    return ERROR;
		}
		(void)osl_sem_downtimeout(&g_dual_modem_ctrl.wait_reply_mutex ,CBP_WAKEUP_DELAY_TIME_MS);
	}
    bsp_softtimer_delete(&g_dual_modem_ctrl.hold_wake_timer);

	cur_port->ops->send(cur_port ,pDataBuffer ,uslength);

	dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
	g_dual_modem_ctrl.wakeup_3rdmodem_flag = NOT_WAKEUP_V3;
	dual_modem_restart_timer(&g_dual_modem_ctrl.hold_wake_timer);

	return OK;
}
/*****************************************************************************
 �� �� ��  : DualModem_InQue
 ��������  : ���ٴ��ڽ��ջ�������Ӻ���
 �������  : pstQue ����������ָ��
             sucData ���յ����ַ�
 �������  : ��
 �� �� ֵ  : 
*****************************************************************************/
static int rx_chars(UART_PORT *uap)
{
	unsigned char ch = 0;
	unsigned int status = 0;
    unsigned int ulTail = 0;
	unsigned int max_count = UART_RECV_BUF_SIZE;
	
	while(0 != max_count--)
	{
		status = readl(uap->base_addr + UART_REGOFFSET_FR);
		if (status & UART_FR_RX_FIFO_EMP)
				break;
		ch = readl(uap->base_addr + UART_REGOFFSET_RBR);

        /* coverity[result_independent_of_operands] */
		if(ch & UART_DR_ERROR)
		{
			dm_print_err("uart frame err\n");
			g_dm_dump_info->frame_err_cnt++;
			return ERROR;
		}
		
		ulTail = uap->circ_buf.ulWrite;
		
	    uap->circ_buf.ucData[ulTail] = ch;
	    ulTail = ((ulTail+1) ==  UART_RECV_BUF_SIZE) ? 0 : (ulTail+1);
	    uap->circ_buf.ulWrite = ulTail;

		if(uap->circ_buf.ulWrite == uap->circ_buf.ulRead)
		{
			dm_print_err("circ buf covered\n");
			g_dm_dump_info->circ_buff_err_cnt++;
			return ERROR;
		}
	}
	
	if(max_count == 0)
	{
		dm_print_err("circ buffer full\n");
		g_dm_dump_info->circ_buff_err_cnt++;

		return ERROR;
	}
	return OK;
}
/*****************************************************************************
 �� �� ��  : dual_modem_uart_irq_handler
 ��������  : uart�жϴ�����
 �������  : u32 uart_port_addr
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
static irqreturn_t dual_modem_uart_irq_handler(void *uart_port_addr)
{
    u32 status = 0;
	u32 ret = ERROR;
	UART_PORT *uart_port = NULL;

	uart_port = (UART_PORT *)uart_port_addr;

	g_dm_dump_info->recv_time_stamp = bsp_get_slice_value();

	cpcp_msg_count_record(&g_dm_dump_info->irq_cnt, "IrqCnt");

	status = readl(uart_port->base_addr + UART_REGOFFSET_MIS);
	if(status)
	{
		do{
			writel(status & ~(UART_ARMIP_REV_VALID | UART_ARMIP_REV_TIMEOUT), 
				uart_port->base_addr + UART_REGOFFSET_ICR);
			if(status & (UART_ARMIP_REV_VALID | UART_ARMIP_REV_TIMEOUT))
			{
				ret = rx_chars(uart_port);
			}
			
			status = readl(uart_port->base_addr + UART_REGOFFSET_MIS);
		}while(status != 0);
		
	}
	if(ret == OK)
	{
		g_dual_modem_ctrl.stop_timer_flag = CPCP_TRUE;
		wake_lock(&g_dual_modem_ctrl.wakelock);
		osl_sem_up(&g_dual_modem_ctrl.recv_mutex);
		
		cpcp_msg_count_record(&g_dm_dump_info->irq_SemGive_cnt, "IrqSemGiveCnt");
	}

	return IRQ_HANDLED;
}
	
/*****************************************************************************
 �� �� ��  : dual_modem_uart_recv_task
 ��������  : ���ûص����������ϲ㷢������
 �������  : UART_PORT * uart_port_add �˿ڵ�ַ
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
void dual_modem_uart_recv_task(UART_PORT *uart_port_addr)
{
	s32 ret = 0;
	volatile u32 ulwrite = 0;
	volatile u32 this_size = 0;
    UART_PORT *uart_port = NULL;
	RECV_STR *recvStr = NULL;

	recvStr = &g_dual_modem_ctrl.uart_port.circ_buf;

    if(NULL == uart_port_addr)
    {
        dm_print_err("uart_port_addr is null\n");
        return ;
    }
    uart_port = uart_port_addr;

   	while(1)
    {
		osl_sem_down(&g_dual_modem_ctrl.recv_mutex);
		cpcp_msg_count_record(&g_dm_dump_info->rtask_SemTake_cnt, "RtaskSemTakecnt");

		ulwrite = recvStr->ulWrite;
		bsp_softtimer_delete(&g_dual_modem_ctrl.sleep_timer);
		dual_modem_restart_timer(&g_dual_modem_ctrl.hold_wake_timer);
		g_dual_modem_ctrl.wakeup_3rdmodem_flag = NOT_WAKEUP_V3;
        if(NULL != uart_port->recv_callback)
		{
			if(recvStr->ulRead  == ulwrite)
        	{
             	dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
                continue;
        	}
			if(recvStr->ulRead < ulwrite)
			{
				this_size = ulwrite - recvStr->ulRead;
        		ret = uart_port->recv_callback(CBP_UART_PORT_ID,(recvStr->ucData + recvStr->ulRead),this_size);	/* [false alarm]:�� */		
				if((g_dm_dump_info->rx_cur_offset + this_size + 4) > DUAL_DUMP_RX_BUFF_SIZE)
				{
					g_dm_dump_info->rx_cur_offset = 0;
				}

				*(g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset) = g_dm_dump_info->recv_time_stamp;
				g_dm_dump_info->rx_cur_offset += 4;

				memcpy_s((g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset) ,this_size,(recvStr->ucData + recvStr->ulRead), this_size);
				g_dm_dump_info->rx_cur_offset += this_size;
				
				g_dm_dump_info->rx_cur_size = this_size;
				g_dm_dump_info->rx_total_size += this_size;
				if(g_dual_modem_ctrl.log_flag == 1)
				{
					dm_debug_print("RecvCurSize %d\n",this_size);				
					dm_print_info((recvStr->ucData + recvStr->ulRead),this_size);
				}
			}
			else 
			{
				this_size = UART_RECV_BUF_SIZE - recvStr->ulRead;
				ret = uart_port->recv_callback(CBP_UART_PORT_ID,(recvStr->ucData + recvStr->ulRead),this_size);		/* [false alarm]:�� */	

				if((g_dm_dump_info->rx_cur_offset + this_size + 4) > DUAL_DUMP_RX_BUFF_SIZE)
				{
					g_dm_dump_info->rx_cur_offset = 0;
				}

				*(g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset) = g_dm_dump_info->recv_time_stamp;
				g_dm_dump_info->rx_cur_offset += 4;

				memcpy_s((g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset) ,this_size,(recvStr->ucData + recvStr->ulRead), this_size);
				g_dm_dump_info->rx_cur_offset += this_size;
				
				g_dm_dump_info->rx_cur_size = this_size + ulwrite;
				g_dm_dump_info->rx_total_size += this_size;	

				if(g_dual_modem_ctrl.log_flag == 1)
				{
					dm_debug_print("RecvCurSize %d\n",g_dm_dump_info->rx_cur_size);
					dm_print_info((recvStr->ucData + recvStr->ulRead),this_size);
				}
				if(ulwrite)
				{
					this_size = ulwrite;
					ret = uart_port->recv_callback(CBP_UART_PORT_ID,recvStr->ucData,this_size);	   /* [false alarm]:�� */

					if((g_dm_dump_info->rx_cur_offset + this_size + 4) > DUAL_DUMP_RX_BUFF_SIZE)
					{
						g_dm_dump_info->rx_cur_offset = 0;
					}

					*(g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset) = g_dm_dump_info->recv_time_stamp;
					g_dm_dump_info->rx_cur_offset += 4;
					
					memcpy_s((g_dm_dump_info->rx_dump_addr + g_dm_dump_info->rx_cur_offset),this_size ,recvStr->ucData , this_size);
					g_dm_dump_info->rx_cur_offset += this_size;
					
					g_dm_dump_info->rx_total_size += this_size;

					if(g_dual_modem_ctrl.log_flag == 1)
					{
						dm_print_info(recvStr->ucData,this_size);
					}
				}
			}
			recvStr->ulRead = ulwrite;
			if(OK != ret)
			{
				dm_print_err("recv error!!\n");

			}
		}
		else 
		{
			dm_print_err("callback is null\n");
			g_dm_dump_info->callback_fail_cnt++;
			recvStr->ulRead = ulwrite;
		}
		dual_modem_restart_timer(&g_dual_modem_ctrl.sleep_timer);
    }
}
/*****************************************************************************
* �� �� ��  :  wakeup_via_modem
* ��������  :  gpio��ʼ��
* �������  :  ��
* �������  :  ��
* �� �� ֵ  :  0
* �޸ļ�¼  :  
*****************************************************************************/
int wakeup_via_modem(void)
{
	s32 ret = ERROR;
	u32 i = 0;
	u8 cbp_wakeup_string[] = {0x00,0x7e,0x7e,0x7e};//����CPB�����ַ���0x7e7e7e
	for(i = 0;i < 3;i++)
	{
		ret = dual_modem_send_bytes(&g_dual_modem_ctrl.uart_port,cbp_wakeup_string,sizeof(cbp_wakeup_string));
    	if(ERROR == ret)
    	{
        	dm_print_err("send wakeup string fail\n");
        	return ERROR;
    	}
	    (void)osl_sem_downtimeout(&g_dual_modem_ctrl.wait_reply_mutex, CBP_WAKEUP_DELAY_TIME_MS);

		cpcp_msg_count_record(&g_dm_dump_info->balong_wakeup_via_cnt, "WakeupViaCnt");
    }
	return OK;
}

/*****************************************************************************
 �� �� ��  : modem_wakeup_delay_overhandler
 ��������  : 300ms��ʱ��Ͷ˯��Ʊ
 �������  : BSP_U32 uart_port_addr
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
void dual_modem_restart_timer(struct softtimer_list * softtimer)
{
	g_dual_modem_ctrl.stop_timer_flag = CPCP_FLASE;
	bsp_softtimer_delete(softtimer);
	bsp_softtimer_add(softtimer);
}

/*****************************************************************************
 �� �� ��  : modem_sleeptimer_overhandler
 ��������  : 300ms��ʱ��Ͷ˯��Ʊ
 �������  : BSP_U32 uart_port_addr
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
void modem_sleeptimer_int(u32 temp)
{
	temp = temp;		/* [false alarm]:�� */
	g_dm_dump_info->modem_sleeptimer_cnt++;
	g_dual_modem_ctrl.wakeup_3rdmodem_flag = DO_WAKEUP_3RD;
	bsp_softtimer_delete(&g_dual_modem_ctrl.hold_wake_timer);
	g_dual_modem_ctrl.stop_timer_flag = CPCP_FLASE;
		wake_unlock(&g_dual_modem_ctrl.wakelock);
}
/*****************************************************************************
 �� �� ��  : modem_awaketimer_overhandler
 ��������  : ����240ms��˫modemͨ��ǰҪ���ѶԷ�
 �������  : u32 temp
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
void modem_awaketimer_int(u32 temp)
{
	temp = temp;		/* [false alarm]:�� */
	g_dual_modem_ctrl.wakeup_3rdmodem_flag = DO_WAKEUP_3RD;
}
/*lint -save -e801*/
/*****************************************************************************
 �� �� �� : dual_modem_wakeup_init
 �������� : ��ʼ��˯��ͶƱ����ʼ����ʱ����ע��iccͨ��
 ������� : ��
 ������� : 0:�ɹ���-1:ʧ��
 �� �� ֵ : int
*****************************************************************************/
int dual_modem_wakeup_init(DRV_DUAL_MODEM_STR DualModemNv)
{
	struct softtimer_list *T1_timer =&g_dual_modem_ctrl.hold_wake_timer;
	struct softtimer_list *T2_timer =&g_dual_modem_ctrl.sleep_timer;
	T1_timer->func = modem_awaketimer_int;
	T1_timer->para = 0;	
	T1_timer->timeout = DualModemNv.AwakeTmer;
	T1_timer->wake_type = SOFTTIMER_NOWAKE;
	
	T2_timer->func = modem_sleeptimer_int;
	T2_timer->para = 0;	
	T2_timer->timeout= DualModemNv.DoSleepTimer;
	T2_timer->wake_type = SOFTTIMER_NOWAKE;

	wake_lock_init(&g_dual_modem_ctrl.wakelock ,PWRCTRL_SLEEP_UART0 ,"PWRCTRL_SLEEP_UART0");

 	g_dual_modem_ctrl.wakeup_3rdmodem_flag = DO_WAKEUP_3RD;
	if(OK !=bsp_softtimer_create(T1_timer))
	{
		dm_print_err("T1_timer create fail!\n");
		goto T1timerfail;
	}
	if(OK !=bsp_softtimer_create(T2_timer))
	{
		dm_print_err("T2_timer create fail!\n");
		goto T2timerfail;
	}
	return OK;
	
T2timerfail:
	bsp_softtimer_free(T1_timer);
T1timerfail:
	return ERROR;	
}

/*****************************************************************************
 �� �� �� : dual_modem_dump_hook
 �������� : ϵͳ��λǰ���ú�����������Ϣ
 ������� : ��
 ������� : 
 �� �� ֵ : 
*****************************************************************************/
void dual_modem_dump_hook(void)
{
	if(NULL != g_dm_dump_info && g_dual_modem_ctrl.init_flag == DUAl_MODEM_ENABLE)
	{
		g_dm_dump_info->uart_reg_val[0] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_FR);
		g_dm_dump_info->uart_reg_val[1] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_IBRD);
		g_dm_dump_info->uart_reg_val[2] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_LCR_H);
		g_dm_dump_info->uart_reg_val[3] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_CR);
		g_dm_dump_info->uart_reg_val[4] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_IFLS);
		g_dm_dump_info->uart_reg_val[5] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_IMSC);
		g_dm_dump_info->uart_reg_val[6] = readl(g_dual_modem_ctrl.uart_port.base_addr + UART_REGOFFSET_MIS);
	}
	return;
}

/*****************************************************************************
 �� �� �� : dual_modem_dump_init
 �������� : dump ��ʼ��
 ������� : ��
 ������� : 
 �� �� ֵ : 
*****************************************************************************/
s32 dual_modem_dump_init(void)
{
	u8 *dump_addr = NULL;

	if(-1 == bsp_dump_register_hook("dual_modem" , (dump_hook)dual_modem_dump_hook))
	{
		dm_print_err("dump hook fail");
		return ERROR;
	}
	
	dump_addr = bsp_dump_register_field((u32)DUMP_SAVE_MOD_DUAL_MODEM ,"dual_modem" ,0,0, DUMP_EXT_DUAL_MODEM_SIZE,0);
	if(dump_addr == NULL)
	{
		dm_print_err("dump no buffer\n");
		return ERROR;
	}
	dm_print_err("dump addr 0x%x\n",(u32)dump_addr);
    memset_s(dump_addr ,DUMP_EXT_DUAL_MODEM_SIZE ,0 ,DUMP_EXT_DUAL_MODEM_SIZE);
	g_dm_dump_info = (struct dm_dump_info *)dump_addr;
	g_dm_dump_info->rx_dump_addr = (u8 *)(dump_addr + DUAL_DUMP_COUNT_SIZE);
	g_dm_dump_info->tx_dump_addr = (u8 *)(g_dm_dump_info->rx_dump_addr + DUAL_DUMP_RX_BUFF_SIZE);
	return OK;
}
/*****************************************************************************
* �� �� ��  :  dual_uart_suspend
* ��������  :  ����5����
* �������  :  ��
* �������  :  ��
* �� �� ֵ  :  0
* �޸ļ�¼  :  
*****************************************************************************/
int dual_uart_suspend(struct dpm_device *dev)
{
	u32 regval = 0;
	regval = readl(g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uart_perclken);
	if((regval & g_dual_modem_ctrl.ap_uart.bit_shift) == 0)
	{
		writel(g_dual_modem_ctrl.ap_uart.bit_shift,
				g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uart_perdis);
		writel(0x8000000, g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uarth_clkdiv);
	}
	if(NULL != g_dm_dump_info)
		g_dm_dump_info->suspend_cnt++;
	return 0;
}

/*****************************************************************************
* �� �� ��  :  dual_uart_resume
* ��������  :  ����5�ָ�
* �������  :  ��
* �������  :  ��
* �� �� ֵ  :  0 : �ɹ�[״̬��־λȡ��
*              1 : ʧ��[״̬��־λȡ��
* �޸ļ�¼  :
*****************************************************************************/
int dual_uart_resume(struct dpm_device *dev)
{	
	writel(0x8000000 | g_dual_modem_ctrl.ap_uart.bit_shift, 
			g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uarth_clkdiv);
	writel(g_dual_modem_ctrl.ap_uart.bit_shift, 
			g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uart_peren);

	dual_modem_uart_channel_init(&g_dual_modem_ctrl.uart_port);
	if(NULL != g_dm_dump_info)
		g_dm_dump_info->resume_cnt++;
	return 0;
}

struct UART_OPS send_ops =
{
	.send = dual_modem_send_bytes,
};

#ifdef CONFIG_CCORE_PM
struct dpm_device dual_modem_device =
{
	.device_name = "dual modem driver",
	.suspend = dual_uart_suspend,
	.resume = dual_uart_resume,
	.prepare = NULL,
	.suspend_late = NULL,
	.complete = NULL,
	.resume_early = NULL,
};
#endif

int get_info_from_dts(void)
{
	int ret = OK;
	u32 data[4] = {0};
	u32 shift = 0;
	struct device_node *node = NULL;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,cpcp_uart");
	if(!node){
		dm_print_err("get cpcp node fail\n");
		return ERROR;
	}
	ret = of_property_read_u32(node, "clock", &g_dual_modem_ctrl.uart_port.clk);

	ret |= of_property_read_u32(node, "band", &g_dual_modem_ctrl.uart_port.baudrate);

	g_dual_modem_ctrl.uart_port.irq_num = (u32)irq_of_parse_and_map(node, 0);
	if(g_dual_modem_ctrl.uart_port.irq_num == 0){
		dm_print_err("get irq fail\n");
		return ERROR;
	}
	g_dual_modem_ctrl.uart_port.base_addr =	(u32)of_iomap(node, 0);
	if(g_dual_modem_ctrl.uart_port.base_addr == 0){
		dm_print_err("get base addr fail\n");
		return ERROR;
	}

	ret |= of_property_read_u32_array(node, "crg_offset", &data[0], 4);

	g_dual_modem_ctrl.ap_uart.clk_uart_peren = data[0];
	g_dual_modem_ctrl.ap_uart.clk_uart_perdis = data[1];
	g_dual_modem_ctrl.ap_uart.clk_uart_perclken = data[2];
	g_dual_modem_ctrl.ap_uart.clk_uarth_clkdiv = data[3];

	ret |= of_property_read_u32(node, "shift", &shift);
	
	g_dual_modem_ctrl.ap_uart.bit_shift = (1 << shift);

	ret |= of_property_read_u32(node, "wakeup_gpio", &g_dual_modem_ctrl.wakeup_gpio);

	g_dual_modem_ctrl.ap_uart.crg_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);
	if(g_dual_modem_ctrl.uart_port.base_addr == 0)
	{
		dm_print_err("get crg base addr fail\n");
		return ERROR;
	}

	return ret;
}

/*****************************************************************************
 �� �� ��  : bsp_dual_modem_init
 ��������  : K3 modem uart��س�ʼ��
 �������  : void
 �������  : -1:ʧ�ܣ�0:�ɹ�
 �� �� ֵ  : int
****************************************************************************/
int bsp_dual_modem_drv_init(void)
{
	int ret = ERROR;
	RECV_STR *recvStr = NULL;
#ifdef LPM3_VIA_GPIO
	struct dual_modem_icc_msg_str dm_msg = {0};
#endif

	recvStr = &g_dual_modem_ctrl.uart_port.circ_buf;

	if(DUAl_MODEM_ENABLE == g_dual_modem_ctrl.nv_flag
		&& DUAl_MODEM_DISABLE == g_dual_modem_ctrl.init_flag)
    {
		wake_lock(&g_dual_modem_ctrl.wakelock);
		memset_s((void*)&g_dual_modem_ctrl.uart_port.circ_buf, sizeof(g_dual_modem_ctrl.uart_port.circ_buf), 0, sizeof(g_dual_modem_ctrl.uart_port.circ_buf)); 
		osl_sem_init(0, &g_dual_modem_ctrl.wait_reply_mutex);
		osl_sem_init(0, &g_dual_modem_ctrl.recv_mutex);
    	osl_sem_mcreate(&g_dual_modem_ctrl.uart_port.send_mutex, OSL_SEM_Q_PRIORITY | OSL_SEM_DELETE_SAFE);
		spin_lock_init(&g_dual_modem_ctrl.lock);
			
		g_dual_modem_ctrl.uart_port.ops = &send_ops;
		
		if(OK != get_info_from_dts())
		{
			dm_print_err("get dts err %d\n",ret);
			goto init_fail;
		}
		writel(0x8000000 | g_dual_modem_ctrl.ap_uart.bit_shift, 
			   g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uarth_clkdiv);
		writel(g_dual_modem_ctrl.ap_uart.bit_shift, 
			   g_dual_modem_ctrl.ap_uart.crg_addr + g_dual_modem_ctrl.ap_uart.clk_uart_peren);

		dual_modem_uart_channel_init(&g_dual_modem_ctrl.uart_port);

#ifdef CONFIG_CCORE_PM
	   if(bsp_device_pm_add(&dual_modem_device))
	   {
			dm_print_err("device add err\n");
			goto init_fail;
	   }
#endif
		if(OK != osl_task_init("utlrecv", DUAL_MODEM_TASK_PRO, DUAL_MODEM_TASK_STK,
		     (OSL_TASK_FUNC)dual_modem_uart_recv_task, (UART_PORT *)&g_dual_modem_ctrl.uart_port, &recvStr->recv_task_id))
    	{
			dm_print_err("utlrecv task err\n");
			goto init_fail;
    	}
		

		ret = request_irq(g_dual_modem_ctrl.uart_port.irq_num, 
			(irq_handler_t)dual_modem_uart_irq_handler, 0, "dual modem irq", &g_dual_modem_ctrl.uart_port);
		if(ret){
			dm_print_err("request irq err\n");
			goto init_fail;
		}

#ifdef LPM3_VIA_GPIO
		dm_msg.dual_modem_init_flag = UART_INIT_ENABLE;
		dm_msg.icc_msgs_flag = LPm3_UART5_IQR_DISABLE;

		/* ֪ͨlpm3	*/
		bsp_icc_send((u32)ICC_CPU_MCU,(ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART,(u8 *)&dm_msg,sizeof(dm_msg));
#else
		bsp_gpio_direction_input(g_dual_modem_ctrl.wakeup_gpio);
		bsp_gpio_irq_unmask(g_dual_modem_ctrl.wakeup_gpio);
		ret = bsp_gpio_request_irq(g_dual_modem_ctrl.wakeup_gpio, (irq_handler_t)wakeup_gpio_int, IRQ_TYPE_EDGE_FALLING, "cpcp gpio");
		if(ret)
		{
			dm_print_err("gpio irq request err\n");
			goto init_fail;
		}
#endif
		g_dual_modem_ctrl.init_flag = DUAl_MODEM_ENABLE;
		wake_unlock(&g_dual_modem_ctrl.wakelock);
    }
    return OK;
init_fail:
	bsp_gpio_irq_mask(g_dual_modem_ctrl.wakeup_gpio);
	wake_unlock(&g_dual_modem_ctrl.wakelock);
	return ERROR;
}

int bsp_dual_modem_init(void)
{
	int ret = ERROR;
	DRV_DUAL_MODEM_STR dual_modem_nv;
	DRV_DM_UART5_STR uart_cfg_nv;
	
	memset_s((void*)&g_dual_modem_ctrl.uart_port, sizeof(g_dual_modem_ctrl.uart_port), 0, sizeof(g_dual_modem_ctrl.uart_port)); 	/*lint !e545*/		//��ʼ����������
	memset_s((void*)&dual_modem_nv, sizeof(DRV_DUAL_MODEM_STR), 0, sizeof(DRV_DUAL_MODEM_STR));
	memset_s((void*)&uart_cfg_nv, sizeof(DRV_DM_UART5_STR), 0, sizeof(DRV_DM_UART5_STR));

	ret = bsp_nvm_read(NV_ID_DRV_DUAL_MODEM ,(u8 *)&dual_modem_nv ,sizeof(DRV_DUAL_MODEM_STR));
    if (ret != OK)
    {
        dm_print_err("read dual modem nv fail: %d\n", NV_ID_DRV_DUAL_MODEM);
        dual_modem_nv.enUartEnableCfg = DUAl_MODEM_DISABLE;
    }
	
	if(DUAl_MODEM_ENABLE == dual_modem_nv.enUartEnableCfg)
    {		
		ret = bsp_nvm_read(NV_ID_DRV_DM_UART5_CFG ,(u8 *)&uart_cfg_nv ,sizeof(DRV_DM_UART5_STR));
    	if (ret != OK)
    	{
        	dm_print_err("read dual modem nv fail: %d\n", NV_ID_DRV_DM_UART5_CFG);
       	    uart_cfg_nv.ex1_param = 0;
    	}
	    g_dual_modem_ctrl.uart_port.rts_mask = (uart_cfg_nv.ex1_param << 14);

		if(DUAl_MODEM_ENABLE == dual_modem_nv.enUartlogEnableCfg)
		{
			g_dual_modem_ctrl.log_flag = 1;	
			bsp_mod_level_set(BSP_MODU_DUAL_MODEM ,BSP_LOG_LEVEL_DEBUG);
		}
		
		ret = dual_modem_wakeup_init(dual_modem_nv);
		if(ret !=OK)
		{
			dm_print_err("dual modem wakeup init failed!\n");
			return ERROR;
		}
		if(OK != dual_modem_dump_init())
		{
			dm_print_err("dual_modem_dump_init fail!\n");
			return ERROR;
    	}
#ifdef LPM3_GPIO
		/* ע��ICC��д�ص� */
		if(OK != bsp_icc_event_register((ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART,
			     recv_lpm3_msg_icc_cb , NULL, NULL, NULL))
    	{
			dm_print_err("register icc callback fail\n");
			return ERROR;
    	}
#endif		
		g_dual_modem_ctrl.nv_flag = DUAl_MODEM_ENABLE;
		dm_print_err("dual modem init\n");
    }
    return OK;
}
/*****************************************************************************
* �� �� ��  : uart_driver_info
* ��������  : UART ��ά�ɲ�ӿ�
* �������  : NA
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void uart_driver_info(void)
{	
	if(	g_dual_modem_ctrl.init_flag == DUAl_MODEM_ENABLE)
	{
		dm_trace("*****************dm recv info*************\n");
		dm_trace("[register cnt]..........................%d\n",g_dm_dump_info->recv_register_cnt);
		dm_trace("[register fail cnt].....................%d\n",g_dm_dump_info->callback_fail_cnt);
		dm_trace("[irq cnt]...............................%d\n",g_dm_dump_info->irq_cnt);
		dm_trace("[irq SemGive cnt].......................%d\n",g_dm_dump_info->irq_SemGive_cnt);
	    dm_trace("[task SemTake cnt]......................%d\n",g_dm_dump_info->rtask_SemTake_cnt);
		dm_trace("[recv total size].......................%d\n",g_dm_dump_info->rx_total_size);
		dm_trace("[circ buff errcnt]......................%d\n",g_dm_dump_info->circ_buff_err_cnt);
		dm_trace("*****************dm send info*************\n");
		dm_trace("[cbpa send cnt].........................%d\n",g_dm_dump_info->cbpa_send_cnt);
		dm_trace("[cur size]..............................%d\n",g_dm_dump_info->tx_cur_size);
		dm_trace("[total size]............................%d\n",g_dm_dump_info->tx_total_size);
		dm_trace("[send mutex]............................%d\n",g_dm_dump_info->send_mutex_cnt);
		dm_trace("*****************dm lowpower info*********\n");
		dm_trace("[suspend cnt]...........................%d\n",g_dm_dump_info->suspend_cnt);
	    dm_trace("[resume cnt]............................%d\n",g_dm_dump_info->resume_cnt);	
		dm_trace("[wakeup balong cnt].....................%d\n",g_dm_dump_info->via_wakeup_balong_cnt);
		dm_trace("[wakeup via cnt]........................%d\n",g_dm_dump_info->balong_wakeup_via_cnt);
		dm_trace("[sleeptimer cnt]........................%d\n",g_dm_dump_info->modem_sleeptimer_cnt);
		dm_trace("*****************dm recv info*************\n");
		dm_trace("[FR].................................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x18));
		dm_trace("[IBRD]...............................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x24));
		dm_trace("[LCR_H]..............................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x2c));
		dm_trace("[CR].................................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x30));
		dm_trace("[IFLS]...............................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x34));
		dm_trace("[IMSC]...............................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x38));
		dm_trace("[MIC]................................0x%3x\n", readl(g_dual_modem_ctrl.uart_port.base_addr + 0x40));
		dm_trace("[frame err cnt].........................%d\n",g_dm_dump_info->frame_err_cnt);
	}
	else 
	{
		dm_trace("dual modem not init\n");
	}
}

void cpcp_msg_count_record(unsigned int *cnt, char *name)
{
	unsigned int *count = cnt;
	(*count)++;
	if(g_dual_modem_ctrl.log_flag == 1)
	{
		dm_debug_print("%s %d\n", name,*count);
	}
}

int dm_print_info(unsigned char *pData, unsigned int ulLength)
{
	char dm_debug_buff[256];
	char *p_buff = dm_debug_buff;
	u8 *pdatabuff = pData;
	s32 ret = 0;
	u32 i = 0;
	u32 datalen = ulLength;
	dm_debug_buff[0] = 0;
	for(i = 0;i < ulLength; i++)
    {
		/*lint -save -e628*/
		ret = snprintf(p_buff, sizeof(dm_debug_buff)-(p_buff - dm_debug_buff + 1), "%x ", *pdatabuff); /*lint !e737 */ 
		if (ret <= 0)
		{
			dm_debug_print("dm_print_info error, code:%d \n",ret);
			return ERROR;
		}
		p_buff += ret;
		pdatabuff++;
		datalen--;
	    if(((sizeof(dm_debug_buff)-(p_buff - dm_debug_buff + 1)) < 3) || (datalen == 0))
		{
			*(p_buff) = '\0';
			dm_debug_print("%s\n" ,dm_debug_buff);
			p_buff = dm_debug_buff;
		}
	}
    return OK;
}

