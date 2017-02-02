#include <product_config.h>
#include <bsp_vic.h>

#ifndef CONFIG_MODULE_VIC
s32 bsp_vic_init(void)
{
	return 0;
}
#endif