
/*lint -save -e537*/
#include <osl_bio.h>
#include <osl_wait.h>
#include <osl_types.h>
#include <osl_thread.h>
#include <drv_comm.h>
#include <hi_rtc.h>
#include "of.h"
#include <bsp_pmu.h>

#include <bsp_memmap.h>
#include <bsp_icc.h>
#include "rtc_balong.h"

#define LEAPS_THRU_END_OF(y)    (((y)/4 - (y)/100) + (y)/400)

struct rtc_control g_rtc_ctrl=
{
    0,
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    0
};

static s32 is_leap_year(u32 year)
{
    return (!(year % 4) && (year % 100)) || !(year % 400);
}

/*
 * The number of days in the month.
 */
static s32 rtc_month_days(u32 month, u32  year)
{
    return g_rtc_ctrl.rtc_days_in_month[month] + (s32)(is_leap_year(year) && (month == 1));
}

/*
 * Convert seconds since 01-01-1970 00:00:00 to Gregorian date.
 */
static void rtc_time_to_tm(u32 time, struct rtc_time *tm)
{
    unsigned int month, year;
    int days;

    days = (int)(time / 86400);
    time -= (unsigned int) days * 86400;

    /* day of the week, 1970-01-01 was a Thursday */
    tm->tm_wday = (days + 4) % 7;

    year = (unsigned int)(1970 + days / 365);
    days -= (s32)((year - 1970) * 365
                  + LEAPS_THRU_END_OF(year - 1)
                  - LEAPS_THRU_END_OF(1970 - 1));
    if (days < 0)
    {
        year -= 1;
        days += 365 + is_leap_year(year);
    }
    tm->tm_year = (int)(year - 1900);
    tm->tm_yday = days + 1;

    for (month = 0; month < 11; month++)
    {
        int newdays;

        newdays = days - rtc_month_days(month, year);
        if (newdays < 0)
            break;
        days = newdays;
    }
    tm->tm_mon = (int)(month);
    tm->tm_mday = days + 1;

    tm->tm_hour = (int)(time / 3600);
    time -= (u32)(tm->tm_hour * 3600);
    tm->tm_min = (int)(time / 60);
    tm->tm_sec = (int)((int)time - tm->tm_min * 60);

    tm->tm_isdst = 0;
}
/*lint -save -e438 -e830*/
s32 balong_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
    u32 value = 0;
    dev = dev;

    value = balong_get_rtc_value();

    rtc_time_to_tm(value, tm);
    rtc_dbg( "%4d-%02d-%02d %02d:%02d:%02d\n",
             tm->tm_year, tm->tm_mon, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);

    return BSP_OK;
}
/*lint -restore*/

u32 balong_get_rtc_value (void)
{
    u32 value = 0;

#if defined(CONFIG_RTC_ON_PMU)
    value = bsp_pmu_get_rtc_value();
#elif defined(CONFIG_RTC_ON_SOC)
    if (g_rtc_ctrl.mapped ==0)
    {
        struct device_node *np;

        np = of_find_compatible_node(NULL, NULL, "arm,pl031");
        if (!np)
        {
            bsp_trace(4,BSP_MODU_RTC,"[%s]fail to find node\n",__FUNCTION__);
            return -1;/*lint !e570*/
        }
        g_rtc_ctrl.rtc_base_addr = (u32)of_iomap(np, 0);
        if (g_rtc_ctrl.rtc_base_addr == 0)
        {
            bsp_trace(4,BSP_MODU_RTC,"[%s]fail to of_iomap\n",__FUNCTION__);
            return -1;/*lint !e570*/
        }
        g_rtc_ctrl.mapped = 1;
    }
    value = readl(g_rtc_ctrl.rtc_base_addr + HI_RTC_DR_OFFSET);
#endif

    return value;
}

/*lint -restore*/

