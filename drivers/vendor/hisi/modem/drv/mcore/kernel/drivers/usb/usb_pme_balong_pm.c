#ifdef __cplusplus
extern "C" {
#endif

#include <libfdt.h>
#include <osl_common.h>

#ifdef ACORE_HAVE_NO_PME_INTERRUPT
#include <irq.h>
#include <soc_interrupts_m3.h>
#include <bsp_ipc.h>
#include <bsp_usb.h>

#if 0
struct device_node *usb_syscrg_np = NULL;

static void usb3_sysctrl_set(const char *propname, int value)
{
	u32 para_value[3];
	u32 bitnum;
	u32 base;
	u32 reg = 0;
	int ret;
	
	ret = of_property_read_u32_array(usb_syscrg_np, propname, para_value, 3);
	if(ret){
		printk("skip find of [%s]\n", propname);
		return ;
	}

	bitnum = para_value[2] - para_value[1] + 1;
	base = para_value[0];
	reg = readl(base);
	reg &= ~(((1<<bitnum)-1)<<para_value[1]);
	reg |= (value << para_value[1]);
	writel(reg, base);
}


static void syscrg_usb_set_pmu_state(int value)
{
		usb3_sysctrl_set("usb_controller_ctrl0_usb3_pm_power_state_requset", value);

}
#endif
static irqreturn_t usb_pme_int_handler(void)
{
	disable_irq(M3_USB3_PME_INT);
	bsp_ipc_int_send(IPC_CORE_ACORE, IPC_ACPU_INT_SRC_MCPU_USB_PME);
	return IRQ_HANDLED;
}
static void dwc3_pme_en(u32 param)
{
	enable_irq(M3_USB3_PME_INT);
}

void bsp_usb_pme_init(void)
{
	int ret = 0;
#if 0
	unsigned int irq;
	struct device_node *np = NULL;

	const char *name = "hisilicon,usb_pme_lpm3";
	//const char *usb_syscrg_name = "hisilicon,usb_syscrg_lpm3";
	//usb_syscrg_np = of_find_compatible_node(NULL, NULL, usb_syscrg_name);
	//if(!usb_syscrg_np){
		//printk("usb syscrg device node not found\n");
	//}
	
	np = of_find_compatible_node(NULL, NULL, name);
	if(!np){
		printk("usb pme device node not found\n");
	}

    irq = irq_of_parse_and_map(np, 0);
	if(0 == irq){
		printk("acquire irq number fail.\n");
	}
#endif
	ret = bsp_ipc_int_connect(IPC_MCPU_INT_SRC_ACPU_USB_PME_EN,  dwc3_pme_en, 0);
	if(ret){
		return;    
	}
	ret = bsp_ipc_int_enable (IPC_MCPU_INT_SRC_ACPU_USB_PME_EN);
	if(ret){
		return;    
	}

	ret = request_irq(M3_USB3_PME_INT, (irq_handler_t)usb_pme_int_handler, 0, (const char*)0, (void*)0);	
	if(ret){
 		return;    
	}
	//printk("pme init succ \n");
}
#else
void bsp_usb_pme_init(void)
{

}

#endif

 
#ifdef __cplusplus
}
#endif
