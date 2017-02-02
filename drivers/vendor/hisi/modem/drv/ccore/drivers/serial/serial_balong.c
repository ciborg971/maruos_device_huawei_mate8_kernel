
#include <sre_typedef.h>
#include <sre_shell.h>
#include <sre_hwi.h>
#include <sre_io_intf.h>
#include <of.h>
#include <bsp_om.h>
#include <bsp_uart.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <soc_clk.h>
#include <hi_uart.h>
#include <serial_core.h>

#define BUFFER_SIZE 0x4000
static struct {
    unsigned int  in;	/* data is added at offset (in % size) */
    unsigned int  out;	/* data is extracted from off. (out % size) */
    unsigned char buffer[BUFFER_SIZE];	/* the buffer holding the data */
}s_ring_buff;

unsigned int console_rx_char(char *ch);
unsigned int console_tx_char(char *ch);

print_hook g_print_hook = NULL;

struct uart_ldisc console_ldisc = {
    .tx_chars = console_tx_char,
    .rx_chars = console_rx_char,
    .id       = 2,
};

void uart_register_hook(print_hook hook)
{
    g_print_hook = hook;
}

void uart_poll_send(unsigned char ch)
{    
    if('\0' != ch)
    {
        s_ring_buff.buffer[s_ring_buff.in] = ch;
        s_ring_buff.in++;
        s_ring_buff.in &= (BUFFER_SIZE - 1);
    }
    else
        uart_start_tx(console_ldisc.port);

    if(g_print_hook)
    {
        (void)g_print_hook((char *)&ch);
    }
}

unsigned int console_tx_char(char *ch)
{
    if (s_ring_buff.out != s_ring_buff.in) {
        if (ch) 
            *ch = (char)s_ring_buff.buffer[s_ring_buff.out];
        s_ring_buff.out++;
        s_ring_buff.out &= (BUFFER_SIZE - 1);
        return 1;
    }
    return 0;
}

unsigned int console_rx_char(char *ch)
{
    return SRE_SendChrToShell((unsigned char)*ch);
}

#define UART_NR			4
extern int synopsys_uart_drv_init(void);
extern int arm_uart_drv_init(void);
extern VIRT_PHYS_MEM_S sysPhysMemDesc [];
static struct uart_port uart_device[UART_NR];
static const char *propname[UART_NR] = {"hisilicon,uart0_mdm","hisilicon,uart1_mdm","hisilicon,uart2_mdm","hisilicon,uart3_mdm"};

void *bsp_get_uart_base_addr(void)
{
    return (void*)uart_device[console_ldisc.id].base_addr;
}

static int uart_device_init(void)
{
    struct device_node *node = NULL;
    u64 start = 0, size = 0;
    int ret = 0;
    unsigned int n;

    node = of_find_compatible_node(NULL, NULL, propname[0]);
    if (!node)
       return -1;

    console_ldisc.id = readl((unsigned long)HI_SHARED_DDR_BASE_ADDR + SHM_OFFSET_UART_FLAG + 4);
    n = console_ldisc.id;

    node = of_find_compatible_node(NULL, NULL, propname[n]);
    if (!node)
       return -1;

    (void)of_reg_info_get(node, 0, &start, &size);
    sysPhysMemDesc[MMU_MAP_UART].uwVirtualAddr      = (unsigned int)start;
    sysPhysMemDesc[MMU_MAP_UART].uwPhysicalAddr     = (unsigned int)start;
    sysPhysMemDesc[MMU_MAP_UART].uwLen              = (unsigned int)size;
    sysPhysMemDesc[MMU_MAP_UART].uwInitialStateMask = MMU_STATEMASK_ALL;
    sysPhysMemDesc[MMU_MAP_UART].uwInitialState     = MMU_STATE_RWX | OS_MMU_STATE_STRONGLY_ORDERED;
    uart_device[n].base_addr = sysPhysMemDesc[MMU_MAP_UART].uwVirtualAddr;
    uart_device[n].irq = (unsigned int)irq_of_parse_and_map(node, 0);
    uart_device[n].id = n;

    ret += of_property_read_u32_array(node, "baudrate", &uart_device[n].baudrate, 1);
    ret += of_property_read_u32_array(node, "uartclk", &uart_device[n].uartclk, 1);
    ret += of_property_read_u32_array(node, "periphid", &uart_device[n].periphid, 1);
    if(ret)
       return ret;

    ret = uart_register_device(&uart_device[n]);

    return ret;
}

void bsp_serial_init(void)
{
    (void)synopsys_uart_drv_init();

    (void)arm_uart_drv_init();

#ifndef CONFIG_SMART_SYSTEM_MODEM
    (void)uart_device_init();
#else
    uart_device[0].base_addr = CCORE_SYS_UART_BASE;
    uart_device[0].irq = CCORE_SYS_UART_INTID;
    uart_device[0].id = 2;
    uart_device[0].baudrate = UART_BAUDRATE;
    uart_device[0].uartclk = UART_PRIMCELL_CLOCK;
    uart_device[0].periphid = UART_BALONG_ID;
    (void)uart_register_device(&uart_device[0]);
#endif

    (void)uart_register_ldisc(&console_ldisc);

    s_ring_buff.in = 0;
    s_ring_buff.out = 0;
    
    /*register output hook*/
    (void)SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)uart_poll_send);
}

