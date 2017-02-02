/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <linux/rtc.h>
#include <linux/delay.h>
#include "rtc_hi6551.h"
#include "osl_types.h"
#include "osl_bio.h"
#include <linux/platform_device.h>

#define RTC_TEST_OK 0
#define RTC_TEST_ERROR 1

extern struct platform_device hi6551_rtc_device[HI6551_RTC_DEVICE_NUM];
extern struct rtc_control g_hi6551_rtc_ctrl;
s32 hi6551_readtime_test(void)
{
    struct rtc_time tm;

    hi6551_rtc_readtime( NULL, &tm );

    hi6551_rtc_print_dbg(" %4d-%02d-%02d %02d:%02d:%02d\n",
            RTC_BASE_YEAR + tm.tm_year, tm.tm_mon, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    return RTC_TEST_OK;
}

static int hi6551_rtc_test_settime(int y,int mon,int d,int h,int minute,int s)
{
    struct rtc_time time;
    u32 temp = 0;
    u32 temp1 = 0;

    time.tm_year = y;
    time.tm_mon = mon;
    time.tm_mday = d;
    time.tm_hour = h;
    time.tm_min = minute;
    time.tm_sec = s;
    temp = hi6551_rtc_read_reg(HI6551_RTCCR_A0_OFFSET);

    hi6551_rtc_settime(NULL,&time);
	msleep(2);
    temp = hi6551_rtc_read_reg(HI6551_RTCCR_A0_OFFSET);
    rtc_tm_to_time( &time, (unsigned long*)&temp1);
    if((((temp - temp1) < 3)&&((temp - temp1)>= 0)) || (((temp1 - temp)<3) && ((temp - temp1)>= 0)))
        return RTC_TEST_OK;
    else
        return RTC_TEST_ERROR;
}

s32 hi6551_settime_test_case0(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(98, 7, 1, 13, 1, 25);
    if(RTC_TEST_OK == ret)
    {
        return RTC_TEST_OK;
    }
    else
    {
        printk("hi6551_rtc_test_settime(98, 7, 1, 13, 1, 25)\r\n");
        return RTC_TEST_ERROR;
    }
}
s32 hi6551_settime_test_case1(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(98, 12, 1, 13, 1, 25);
    if(RTC_TEST_ERROR == ret)
    {
        return RTC_TEST_OK;
    }
    else
    {
        printk("hi6551_rtc_test_settime(98, 12, 1, 13, 1, 25)\r\n");
        return RTC_TEST_ERROR;
    }
}
s32 hi6551_settime_test_case2(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(20, 12, 1, 13, 1, 25);
    if(RTC_TEST_ERROR == ret)
    {
        return RTC_TEST_OK;
    }
    else
    {
        printk("hi6551_rtc_test_settime(20, 12, 1, 13, 1, 25)\r\n");
        return RTC_TEST_ERROR;
    }
}
static int hi6551_rtc_test_setalarm(struct platform_device rtc, int y,int mon,int d,int h,int minute,int s,char enable)
{
    struct rtc_wkalrm alarm;
    u32 alarmtime_reg = 0;
    u32 alarmtime_from = 0;

    alarm.time.tm_year = y;
    alarm.time.tm_mon = mon;
    alarm.time.tm_mday = d;
    alarm.time.tm_hour = h;
    alarm.time.tm_min = minute;
    alarm.time.tm_sec = s;
    alarm.enabled = enable;

    hi6551_rtc_setalarm(&rtc.dev, &alarm);

    udelay(3);

    alarmtime_reg = hi6551_rtc_read_reg(g_hi6551_rtc_ctrl.alarm_base_addr[rtc.id]);

	rtc_tm_to_time( &(alarm.time), (unsigned long*)&alarmtime_from);


    if( (alarmtime_from == alarmtime_reg)&&(enable == alarm.enabled))
        return RTC_TEST_OK;
    else
        return RTC_TEST_ERROR;
}


s32 hi6551_setalarm_test_case0(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(98, 7, 1, 13, 1, 25);
    ret += hi6551_rtc_test_setalarm(hi6551_rtc_device[0],98, 7, 1, 13, 3, 0 ,ALARM_ENABLE);
    if(RTC_TEST_OK == ret)
        return RTC_TEST_OK;
    else
    {
        printk("Fail:RTC time:98, 7, 1, 13, 1, 25 Alarm is:98, 7, 1, 13, 3, 0 ,1\r\n");
        return RTC_TEST_ERROR;
    }
}

s32 hi6551_setalarm_test_case1(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(98, 7, 1, 13, 1, 25);
    ret += hi6551_rtc_test_setalarm(hi6551_rtc_device[1],98, 7, 1, 24, 0, 0 ,ALARM_ENABLE);
    if(RTC_TEST_OK != ret)
        return RTC_TEST_OK;
    else
    {
        printk("Fail:RTC time:98, 7, 1, 13, 1, 25 Alarm is:98, 7, 1, 24, 0, 0 ,1\r\n");
        return RTC_TEST_ERROR;
    }
}

s32 hi6551_setalarm_test_case2(void)
{
    s32 ret = 0;
    ret = hi6551_rtc_test_settime(98, 7, 1, 13, 1, 25);
    ret += hi6551_rtc_test_setalarm(hi6551_rtc_device[2],90, 7, 1, 24, 0, 0 ,ALARM_ENABLE);
    if(0 != ret)
        return RTC_TEST_OK;
    else
    {
        printk("Fail:RTC time:98, 7, 1, 13, 1, 25 Alarm is:98, 7, 1, 24, 0, 0 ,1\r\n");
        return RTC_TEST_ERROR;
    }
}

s32 hi6551_readalarm_test(void)
{
    struct rtc_wkalrm alarm;
    hi6551_rtc_readalarm(&hi6551_rtc_device[0].dev, &alarm);

    hi6551_rtc_print_dbg("alarm time is %d.%d.%d-%d:%d:%d", alarm.time.tm_year, alarm.time.tm_mon, alarm.time.tm_mday, alarm.time.tm_hour, alarm.time.tm_min, alarm.time.tm_sec);
    hi6551_rtc_print_dbg("alarm enable is %d ", alarm.enabled);
    hi6551_rtc_print_dbg("alarm pending is %d ", alarm.pending);
    return RTC_TEST_OK;
}

s32 hi6551_alarmenable_test_case0(void)
{
    struct rtc_wkalrm alarm;

    hi6551_alarm_irq_enable(&hi6551_rtc_device[0].dev, ALARM_ENABLE);
    hi6551_rtc_readalarm(&hi6551_rtc_device[0].dev, &alarm);
    if(ALARM_ENABLE == alarm.enabled)
    {
        return RTC_TEST_OK;
    }
    else
    {
        printk("Fail:alarm enable\r\n");
        return RTC_TEST_ERROR;
    }
}
s32 hi6551_alarmenable_test_case1(void)
{
    struct rtc_wkalrm alarm;

    hi6551_alarm_irq_enable(&hi6551_rtc_device[1].dev, ALARM_DISABLED);
    hi6551_rtc_readalarm(&hi6551_rtc_device[1].dev, &alarm);
    if(ALARM_DISABLED == alarm.enabled)
    {
        return RTC_TEST_OK;
    }
    else
    {
        printk("Fail:alarm disable\r\n");
        return RTC_TEST_ERROR;
    }
}
/********************test end**********************/
