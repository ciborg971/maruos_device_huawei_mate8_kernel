#include <linux/init.h>
//#include <linux/platform_device.h>
//#include <linux/io.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/kernel.h>
//#include <asm/setup.h>
//#include <mach/system.h>
//#include <mach/platform.h>
//#include <mach/irqs.h>
//#include <mach/io.h>
//#include <mach/boardid.h>
//#include <mach/gpio.h>

#define HEX_STRING_MAX    (10)
#define TRANSFER_BASE     (16)
#define HWLOG_TAG pd_charge
HWLOG_REGIST();

static unsigned int pd_charge_flag;
/**
 * parse powerdown charge cmdline which is passed from fastoot. *
 * Format : pd_charge=0 or 1             *
 */
static int __init early_parse_pdcharge_cmdline(char * p)
{
    if(p)
    {
        if(!strcmp(p,"charger"))
        {
            pd_charge_flag = 1;
        }
        else
        {
            pd_charge_flag = 0;
        }

        hwlog_info("power down charge p:%s, pd_charge_flag :%u\n", p, pd_charge_flag);
    }

    return 0;
}
early_param("androidboot.mode", early_parse_pdcharge_cmdline);


unsigned int get_pd_charge_flag(void)
{
	return pd_charge_flag;
}
EXPORT_SYMBOL(get_pd_charge_flag);



