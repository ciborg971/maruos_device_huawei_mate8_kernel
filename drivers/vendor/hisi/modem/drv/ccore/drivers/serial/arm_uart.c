
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include "serial_core.h"
#include "arm_uart.h"
#include <bsp_om.h>

static struct uart_port *uap;

/*****************************************************************************
* �� �� ��  :  arm_uart_stop_tx
*
* ��������  :  ֹͣ����
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_stop_tx(struct uart_port *port)
{
    unsigned int imsc;

    imsc = readl(port->base_addr + UART_REGOFF_IMSC);
    imsc &= ~UART_IMSC_TXIM;
    writel(imsc, port->base_addr + UART_REGOFF_IMSC);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_start_tx
*
* ��������  :  ��ʼ���ʹ�������
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_start_tx(struct uart_port *port)
{
    unsigned int imsc;

    imsc = readl(port->base_addr + UART_REGOFF_IMSC);
    imsc |= UART_IMSC_TXIM;
    writel(imsc, port->base_addr + UART_REGOFF_IMSC);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_stop_rx
*
* ��������  :  ֹͣ���մ�������
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_stop_rx(struct uart_port *port)
{
    unsigned int imsc;

    imsc = readl(port->base_addr + UART_REGOFF_IMSC);
    imsc &= ~(UART_IMSC_RXIM|UART_IMSC_RTIM|UART_IMSC_FEIM|
            UART_IMSC_PEIM|UART_IMSC_BEIM|UART_IMSC_OEIM);
    writel(imsc, port->base_addr + UART_REGOFF_IMSC);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_get_char
*
* ��������  :  ���մ�������
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ����data
*
* �޸ļ�¼  :
*****************************************************************************/
static int arm_uart_get_char(struct uart_port *port)
{	
    unsigned int status;

    status = readl(port->base_addr + UART_REGOFF_FR);
    if ((status & UART_FR_RX_FIFO_EMP) == UART_FR_RX_FIFO_EMP)
        return -1;

    /* if there is not emp in the FIFO */
    return (int)readl(port->base_addr + UART_REGOFF_DR);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_put_char
*
* ��������  :  ���ʹ�������
*
* �������  :  uart_port��char

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_put_char(struct uart_port *port, unsigned char ch)
{
    /* Wait until there is space in the FIFO */
    while ((readl(port->base_addr + UART_REGOFF_FR) & UART_FR_TX_FIFO_FULL) == UART_FR_TX_FIFO_FULL){}

    /* Send the character */
    writel(ch, port->base_addr + UART_REGOFF_DR);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_tx_int_proc
*
* ��������  :  ���ڷ����жϴ�����
*
* �������  :  uart_port  :��Ӧͨ��
* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_tx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;

    do {
        /* there is space in the FIFO */
        if (UART_FR_TX_FIFO_FULL != (readl(port->base_addr + UART_REGOFF_FR) & UART_FR_TX_FIFO_FULL))
        {
            if (*port->ldisc->tx_chars && ((*port->ldisc->tx_chars)(&ch) != 0))
                writel((unsigned char)ch, port->base_addr + UART_REGOFF_DR);
            else {/* disable transmit interrupt */
                arm_uart_stop_tx(port);
                break;
            }
        }
        else
        {
            break;
        }
    }while(--pass_counter > 0);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_rx_int_proc
*
* ��������  :  ���ڽ����жϴ�����
*
* �������  :  uart_port  :��Ӧͨ��
* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_rx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;  

    do {
        /* if there is not emp in the FIFO */
        if (UART_FR_RX_FIFO_EMP != (readl(port->base_addr + UART_REGOFF_FR) & UART_FR_RX_FIFO_EMP)) {
            ch = (char)readl(port->base_addr + UART_REGOFF_DR);
            if (*port->ldisc->rx_chars)
                (void)(*port->ldisc->rx_chars)(&ch);
            }
        else
            break;
    }while(--pass_counter > 0);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_int_handle
*
* ��������  :  �����ж���Ӧ����
*
* �������  :  irq :�жϺ� dev_id:�豸ID

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static irqreturn_t arm_uart_int_handle(void *arg)
{
    unsigned long interrupt_flg;
    unsigned int status, pass_counter = AMBA_ISR_PASS_LIMIT;
    irqreturn_t handled = IRQ_NONE;

    local_irq_save(interrupt_flg);
    status = readl(uap->base_addr + UART_REGOFF_MIS);
    if (status & (UART_MIS_TXIS|UART_MIS_RTIS|UART_MIS_RXIS)) {
        do {
            writel(status & ~(UART_MIS_TXIS|UART_MIS_RTIS|UART_MIS_RXIS),
                   uap->base_addr + UART_REGOFF_ICR);

            /* receive interrupt */
            if (status & (UART_MIS_RTIS|UART_MIS_RXIS))
                arm_uart_rx_int_proc(uap);

            /* transmit interrupt */
            if (status & UART_MIS_TXIS)
                arm_uart_tx_int_proc(uap);

            if (pass_counter-- == 0)
                break;

            status = readl(uap->base_addr + UART_REGOFF_MIS);
        } while ((status & (UART_MIS_TXIS|UART_MIS_RTIS|UART_MIS_RXIS)) != 0);
        handled = IRQ_HANDLED;
    }

    local_irq_restore(interrupt_flg);

    return handled;
}

/*****************************************************************************
* �� �� ��  :  arm_uart_set_termios
*
* ��������  :  ���ô��ڲ���
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_set_termios(struct uart_port *port)
{
    unsigned int ibrd,fbrd;

    while(UART_FR_UART_BUSY & readl(port->base_addr + UART_REGOFF_FR))
        DWB();

    /* set baudrate*/
    ibrd = port->uartclk / (16 * port->baudrate);
    writel(ibrd, port->base_addr + UART_REGOFF_IBRD);

    /*
    *fbrd:(clk % (16 * baud)) / (16 * baud) * 64 + 0.5
    */
    fbrd = port->uartclk % (16 * port->baudrate);
    fbrd *= (1UL << 6);
    fbrd *= 2;
    fbrd += 16 * port->baudrate;
    fbrd /= (u32)(2 * 16 * port->baudrate);
    writel(fbrd, port->base_addr + UART_REGOFF_FBRD);

    /* disable fifo */
    writel(UART_LCRH_DLS_8BITS, port->base_addr + UART_REGOFF_LCRH);

    writel(0, port->base_addr + UART_REGOFF_DR);
 	while(UART_FR_UART_BUSY & readl(port->base_addr + UART_REGOFF_FR))
		DWB();
    /* �������ݳ���Ϊ8bit,1ֹͣλ,��У��λ,ʹ��FIFO*/
    writel((UART_LCRH_PEN_NONE | UART_LCRH_STP1 | UART_LCRH_DLS_8BITS | UART_LCRH_FIFO_ENABLE), port->base_addr + UART_REGOFF_LCRH);

}

/*****************************************************************************
* �� �� ��  :  arm_uart_get_mctrl
*
* ��������  :  get modem control
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��ǰ״̬
*
* �޸ļ�¼  :
*****************************************************************************/
static unsigned int arm_uart_get_mctrl(struct uart_port *port)
{
    unsigned int result = 0;
    unsigned int status = readl(port->base_addr + UART_REGOFF_FR);

#define TIOCMBIT(uartbit, tiocmbit)	\
    if (status & uartbit)		\
    	result |= tiocmbit

    TIOCMBIT(UART_FR_DCD, TIOCM_CAR);
    TIOCMBIT(UART_FR_DSR, TIOCM_DSR);
    TIOCMBIT(UART_FR_CTS, TIOCM_CTS);
    TIOCMBIT(UART_FR_RI, TIOCM_RNG);
#undef TIOCMBIT
    return result;
}

/*****************************************************************************
* �� �� ��  :  arm_uart_set_mctrl
*
* ��������  :  set modem control
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
    unsigned int cr;

    cr = readl(port->base_addr + UART_REGOFF_CR);

#define	TIOCMBIT(tiocmbit, uartbit)		\
    if (mctrl & tiocmbit)		\
    	cr |= uartbit;		\
    else				\
    	cr &= ~uartbit

    TIOCMBIT(TIOCM_RTS, UART_CR_RTS);
    TIOCMBIT(TIOCM_DTR, UART_CR_DTR);
    TIOCMBIT(TIOCM_OUT1, UART_CR_OUT1);
    TIOCMBIT(TIOCM_OUT2, UART_CR_OUT2);
    TIOCMBIT(TIOCM_LOOP, UART_CR_LBE);

    /* We need to disable auto-RTS if we want to turn RTS off */
    TIOCMBIT(TIOCM_RTS, UART_CR_RTSEN);
    TIOCMBIT(TIOCM_CTS, UART_CR_CTSEN);
#undef TIOCMBIT

    writel(cr, port->base_addr + UART_REGOFF_CR);
}

/*****************************************************************************
* �� �� ��  :  arm_uart_startup
*
* ��������  :  �������ڶ˿ڣ��ڴ򿪸��豸�ǻ���ã������жϵȹ���
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int arm_uart_startup(struct uart_port *port)
{
    static int flag = 0;
    int retval;
    unsigned long interrupt_flg; 

    local_irq_save(interrupt_flg);

    /* disable uart */
    writel(UART_CR_UARTDIS, port->base_addr + UART_REGOFF_CR);

    /*clear register UARTRSR_UARTECR: clear all error flags*/
    writel(0xE0 , port->base_addr + UART_REGOFF_RSR);
    
    /* Clear all interrupts */
    writel(0, port->base_addr + UART_REGOFF_IMSC);

    /* Clear pending error and receive interrupts */
    writel(UART_ICR_OEIS | UART_ICR_BEIS | UART_ICR_PEIS | UART_ICR_FEIS |
        UART_ICR_RTIS | UART_ICR_RXIS, port->base_addr + UART_REGOFF_ICR);

    /*set FIFO line*/
    writel(UART_IFLS_DEF_SET, port->base_addr + UART_REGOFF_IFLS);

    writel(UART_CR_UARTEN | UART_CR_TXE | UART_CR_LBE, port->base_addr + UART_REGOFF_CR);

    arm_uart_set_termios(port);

    /*
     * Allocate the IRQ
     */
    if (((*port->ldisc->rx_chars) || (*port->ldisc->tx_chars)) && (flag == 0)) { /*lint !e830 */
        uap = port;
        retval = request_irq(port->irq, arm_uart_int_handle, 0, "arm-uart", port);
        if (retval) {
            local_irq_restore(interrupt_flg);
            return retval;
        }
        else
            flag = 1;
    }

    /* Clear out any spuriously appearing RX interrupts */
    writel(UART_ICR_RTIS | UART_ICR_RXIS, port->base_addr + UART_REGOFF_ICR);

    /*Receiver Int Enable*/
    if (*port->ldisc->rx_chars) { /*lint !e539 */
        writel(UART_IMSC_RTIM | UART_IMSC_RXIM, port->base_addr + UART_REGOFF_IMSC);
        writel(UART_CR_TXE|UART_CR_RXE|UART_CR_UARTEN, port->base_addr + UART_REGOFF_CR);
    }

    local_irq_restore(interrupt_flg);

    return 0;

}

/*****************************************************************************
* �� �� ��  :  arm_uart_shutdown
*
* ��������  :  �رմ��ڣ��ڹرո��豸ʱ���ã��ͷ��жϵ�
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void arm_uart_shutdown(struct uart_port *port)
{
    unsigned long val;
    unsigned long interrupt_flg;

    local_irq_save(interrupt_flg);

    /*
     * disable/clear all interrupts
    */
    writel(0, port->base_addr + UART_REGOFF_IMSC);
    writel(0xffff, port->base_addr + UART_REGOFF_ICR);

    local_irq_restore(interrupt_flg);

    /*
     * Free the interrupt
     */
    free_irq(port->irq, port);

    /* Disable RX and TX */
    while(UART_FR_UART_BUSY & readl(port->base_addr + UART_REGOFF_FR))
        DWB();
    
    /*
     * disable break condition and fifos
     */
    val = readl(port->base_addr + UART_REGOFF_LCRH);
    val &= ~(UART_LCRH_BRK | UART_LCRH_FIFO_ENABLE);
    writel(val, port->base_addr + UART_REGOFF_LCRH);

    /* disable uart*/
    writel(UART_CR_UARTDIS, port->base_addr + UART_REGOFF_CR);

}

/*****************************************************************************
* �� �� ��  :  arm_uart_suspend
*
* ��������  :  ���ڹ���
*
* �������  :  ��

* �������  :  ��
*
* �� �� ֵ  :  0 : OK
*              1 : ERR
*
* �޸ļ�¼  :
*****************************************************************************/
static int arm_uart_suspend(struct uart_port *port)
{
    /* disable interrupt */
    (void)disable_irq(port->irq);

    return 0;
}

/*****************************************************************************
* �� �� ��  :  arm_uart_resume
*
* ��������  :  ���ڻָ�
*
* �������  :  ��

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int arm_uart_resume(struct uart_port *port)
{
    int ret;

    ret = arm_uart_startup(port);
    if (ret)
        return ret;

    (void)enable_irq(port->irq);

    return 0;
}

static struct uart_ops arm_uart_pops = {
    .set_mctrl      = arm_uart_set_mctrl,    /* set modem control    */
    .get_mctrl      = arm_uart_get_mctrl,    /* get modem control    */
    .stop_tx	    = arm_uart_stop_tx,      /* stop transmit           */
    .start_tx	    = arm_uart_start_tx,     /* start transmit           */
    .stop_rx	    = arm_uart_stop_rx,      /* stop  receive            */
    .startup	    = arm_uart_startup,      /* start uart receive/transmit    */
    .shutdown	    = arm_uart_shutdown,     /* shut down uart           */
    .set_termios	= arm_uart_set_termios,  /* set termios            */
    .get_char       = arm_uart_get_char,
    .put_char       = arm_uart_put_char,
    .suspend        = arm_uart_suspend,
    .resume         = arm_uart_resume,
};

static struct uart_driver arm_driver = {
    .ops = &arm_uart_pops,
    .periphid = 0x00041011,
    .driver_name = "arm_uart", 
};

int arm_uart_drv_init(void)
{
    int ret = 0;

    ret = uart_register_driver(&arm_driver);

    return ret;
}

