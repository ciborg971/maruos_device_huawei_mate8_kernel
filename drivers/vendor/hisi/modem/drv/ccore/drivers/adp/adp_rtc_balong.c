
#include <product_config.h>
#include "rtc_balong.h"

unsigned int mdrv_rtc_get_value (void)
{
#if defined(CONFIG_RTC_ON_PMU) || defined(CONFIG_RTC_ON_SOC)
    return balong_get_rtc_value();
#else
    return 0;
#endif
}

