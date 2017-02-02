
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include "serial_core.h"
#include "synopsys_uart.h"

static struct uart_port *uap;

/*****************************************************************************
* �� �� ��  :  synopsys_uart_stop_tx
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
static void synopsys_uart_stop_tx(struct uart_port *port)
{
    unsigned int ier;

    ier = readl(port->base_addr + UART_REGOFF_IER);
    ier &= ~(PTIME | UART_IER_TX_IRQ_ENABLE);
    writel(ier, port->base_addr + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_start_tx
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
static void synopsys_uart_start_tx(struct uart_port *port)
{
    unsigned int ier;

    ier = readl(port->base_addr + UART_REGOFF_IER);
    ier |= UART_IER_TX_IRQ_ENABLE;
    writel(ier, port->base_addr + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_stop_rx
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
static void synopsys_uart_stop_rx(struct uart_port *port)
{
    unsigned int ier;

    ier = readl(port->base_addr + UART_REGOFF_IER);
    ier &= ~(UART_IER_LS_IRQ_ENABLE | UART_IER_RX_IRQ_ENABLE);
    writel(ier, port->base_addr + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_get_char
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
static int synopsys_uart_get_char(struct uart_port *port)
{	
    if (!(readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_EMP))
        return -1;

    /* if there is not emp in the FIFO */
    return (int)readl(port->base_addr + UART_REGOFF_RBR);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_put_char
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
static void synopsys_uart_put_char(struct uart_port *port, unsigned char ch)
{
    /* Wait until there is space in the FIFO */
    while (0 == (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_FULL)){}

    /* Send the character */
    writel(ch, port->base_addr + UART_REGOFF_RBR);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_wait_idle
*
* ��������  :  �ȴ����ڴ������
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ  :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static inline void synopsys_uart_wait_idle(struct uart_port *port)
{
    while(readl(port->base_addr + UART_REGOFF_USR) & UART_USR_UART_BUSY) {
        if(readl(port->base_addr + UART_REGOFF_LSR) & UART_LSR_DR)
            (void)readl(port->base_addr + UART_REGOFF_RBR);
    }
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_tx_int_proc
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
static void synopsys_uart_tx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;

    do {
        /* there is space in the FIFO */
        if (UART_USR_FIFO_NOT_FULL == (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_FULL))
        {
            if (*port->ldisc->tx_chars && ((*port->ldisc->tx_chars)(&ch) != 0))
                writel((unsigned char)ch, port->base_addr + UART_REGOFF_RBR);
            else {/* disable transmit interrupt */
                synopsys_uart_stop_tx(port);
                break;
            }
        }
        else
        {
            break;
        }
    }while(--pass_counter > 0);

    /* clear trans interrupt */
    (void)readl(port->base_addr + UART_REGOFF_IIR);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_rx_int_proc
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
static void synopsys_uart_rx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;

    do {
        /* if there is not emp in the FIFO */
        if (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_EMP) {
            ch = (char)readl(port->base_addr + UART_REGOFF_RBR);
            if (*port->ldisc->rx_chars)
                (void)(*port->ldisc->rx_chars)(&ch);
            }
        else
            break;
    }while(--pass_counter > 0);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_int_handle
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
static irqreturn_t synopsys_uart_int_handle(void *arg)
{
    unsigned long interrupt_flg;
    unsigned int status;
    irqreturn_t handled = IRQ_NONE;

    local_irq_save(interrupt_flg);
    status = readl(uap->base_addr + UART_REGOFF_IIR) & 0x0f;

    /*if is "no interrupt pending" dap*/
    if (status != UART_IIR_NO_INTERRUPT) {
        /* receive interrupt */
        if ((status == UART_IIR_REV_VALID)||(status == UART_IIR_REV_TIMEOUT))
            synopsys_uart_rx_int_proc(uap);

        /* transmit interrupt */
        else if (status == UART_IIR_THR_EMPTY)
            synopsys_uart_tx_int_proc(uap);

        /* clear other interrupt status. */
        else {
            (void)readl(uap->base_addr + UART_REGOFF_LSR);
            (void)readl(uap->base_addr + UART_REGOFF_USR);
            (void)readl(uap->base_addr + UART_REGOFF_MSR);
        }
        handled = IRQ_HANDLED;
    }

    local_irq_restore(interrupt_flg);

    return handled;
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_set_termios
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
static void synopsys_uart_set_termios(struct uart_port *port)
{
    unsigned int quot;
    unsigned int ul_divisor_high, ul_divisor_low;

    quot = port->uartclk / (16 * port->baudrate);
    ul_divisor_high = (quot & 0xFF00) >> 8;
    ul_divisor_low = quot & 0xFF;

    /*config baudrate: uart must be idle */
    /*config baudrate: enable access DLL and DLH */
    do {
        (void)readl(port->base_addr + UART_REGOFF_USR);
        writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);
        writel(UART_LCR_DLAB,port->base_addr + UART_REGOFF_LCR);
    }while(!(UART_LCR_DLAB & readl(port->base_addr + UART_REGOFF_LCR)));

    /* Set baud rate */
    writel(ul_divisor_high, port->base_addr + UART_REGOFF_DLH);
    writel(ul_divisor_low, port->base_addr + UART_REGOFF_DLL);

    do {
        (void)readl(port->base_addr + UART_REGOFF_USR);
        writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);
        writel(UART_LCR_DEFAULTVALUE,port->base_addr + UART_REGOFF_LCR);
    }while(UART_LCR_DLAB & readl(port->base_addr + UART_REGOFF_LCR));

    /* ������Χ���ͺͽ������ݵ���ĿΪ8bit,1ֹͣλ,��У��λ,disable DLL&DLH */
    writel((UART_LCR_PEN_NONE | UART_LCR_STOP_1BITS | UART_LCR_DLS_8BITS), port->base_addr + UART_REGOFF_LCR);
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_startup
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
static int synopsys_uart_startup(struct uart_port *port)
{
    static int flag = 0;
    int retval;
    unsigned long interrupt_flg; 

    local_irq_save(interrupt_flg);

    /* disable FIFO and interrupt */
    writel(UART_IER_IRQ_DISABLE, port->base_addr + UART_REGOFF_IER);
    writel(UART_FCR_FIFO_DISABLE, port->base_addr + UART_REGOFF_FCR);

    /*
     * Allocate the IRQ
     */
    if (((*port->ldisc->rx_chars) || (*port->ldisc->tx_chars)) && (flag == 0)) {
        uap = port;
        retval = request_irq(port->irq, synopsys_uart_int_handle, 0, "synopsys-uart", port);
        if (retval) {
            local_irq_restore(interrupt_flg);
            return retval;
        }
        else
            flag = 1;
    }

    /* enable FIFO */
    writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);

    /* clear interrupt status */
    (void)readl(port->base_addr + UART_REGOFF_LSR);
    (void)readl(port->base_addr + UART_REGOFF_IIR);
    (void)readl(port->base_addr + UART_REGOFF_USR);
    (void)readl(port->base_addr + UART_REGOFF_RBR);

    synopsys_uart_set_termios(port);

    /*Receiver Int Enable*/
    if (*port->ldisc->rx_chars)
        writel(UART_IER_RX_IRQ_ENABLE, port->base_addr + UART_REGOFF_IER);

    local_irq_restore(interrupt_flg);

    return 0;

}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_shutdown
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
static void synopsys_uart_shutdown(struct uart_port *port)
{
    unsigned long val;
    unsigned long interrupt_flg;

    local_irq_save(interrupt_flg);

    /*
     * disable/clear all interrupts
    */
    writel(UART_IER_IRQ_DISABLE, port->base_addr + UART_REGOFF_IER);
    (void)readl(port->base_addr + UART_REGOFF_LSR);

    local_irq_restore(interrupt_flg);

    /*
     * Free the interrupt
     */
    free_irq(port->irq, port);

    synopsys_uart_wait_idle(port);
    val = readl(port->base_addr + UART_REGOFF_LCR);
    val &= ~(UART_LCR_BREAK);/* [false alarm]:�� */
    writel(val, port->base_addr + UART_REGOFF_LCR);

    /* disable fifo*/
    writel(UART_FCR_FIFO_DISABLE, port->base_addr + UART_REGOFF_FCR);

}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_suspend
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
static int synopsys_uart_suspend(struct uart_port *port)
{  
    /* disable FIFO */
    writel(UART_FCR_DEF_SET & ~0x1, port->base_addr + UART_REGOFF_FCR);

    /* disable interrupt */
    (void)disable_irq(port->irq);

    return 0;
}

/*****************************************************************************
* �� �� ��  :  synopsys_uart_resume
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
static int synopsys_uart_resume(struct uart_port *port)
{
    int ret;

    ret = synopsys_uart_startup(port);
    if (ret)
        return ret;

    (void)enable_irq(port->irq);

    return 0;
}

static struct uart_ops synopsys_uart_pops = {
    .stop_tx	    = synopsys_uart_stop_tx,      /* stop transmit           */
    .start_tx	    = synopsys_uart_start_tx,     /* start transmit           */
    .stop_rx	    = synopsys_uart_stop_rx,      /* stop  receive            */
    .startup	    = synopsys_uart_startup,      /* start uart receive/transmit    */
    .shutdown	    = synopsys_uart_shutdown,     /* shut down uart           */
    .set_termios	= synopsys_uart_set_termios,  /* set termios            */
    .get_char       = synopsys_uart_get_char,
    .put_char       = synopsys_uart_put_char,
    .suspend        = synopsys_uart_suspend,
    .resume         = synopsys_uart_resume,
};

static struct uart_driver synopsys_driver = {
    .ops = &synopsys_uart_pops,
    .periphid = 0x000c21c0,
    .driver_name = "synopsys_uart", 
};

int synopsys_uart_drv_init(void)
{
    int ret = 0;

    ret = uart_register_driver(&synopsys_driver);

    return ret;
}

