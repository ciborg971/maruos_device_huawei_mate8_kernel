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

#ifndef __HI_TIMER_H__
#define __HI_TIMER_H__


/*
 * Project: hi
 * Module : timer
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    timer �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
/*c coreʹ��*/
#define    HI_TIMER_LOADCOUNT_OFFSET                         (0x0) /* ��ʱ��n�ĵ�32λ��ʼֵ�Ĵ����� */
#define    HI_TIMER_LOADCOUNT_H_OFFSET                       (0xB0) /* ��ʱ��n�ĸ�32λ��ʼֵ�Ĵ����� */
#define    HI_TIMER_CURRENTVALUE_OFFSET                      (0x4) /* ��ʱ��n�ĵ�32λ��ǰֵ�Ĵ����� */
#define    HI_TIMER_CURRENTVALUE_H_OFFSET                    (0xB4) /* ��ʱ��n�ĸ�32λ��ǰֵ�Ĵ����� */
#define    HI_TIMER_CONTROLREG_OFFSET                        (0x8) /* ��ʱ��n�Ŀ��ƼĴ����� */
#define    HI_TIMER_EOI_OFFSET                               (0xC) /* ��ʱ��n�����жϼĴ����� */
#define    HI_TIMER_INTSTATUS_OFFSET                         (0x10) /* ��ʱ��n���ж�״̬�Ĵ����� */
#define    HI_TIMERS_INTSTATUS_OFFSET                        (0xA0) /* ��ʱ���ж�״̬�Ĵ����� */
#define    HI_TIMERS_EOI_OFFSET                              (0xA4) /* ��ʱ�����жϼĴ����� */
#define    HI_TIMERS_RAWINTSTATUS_OFFSET                     (0xA8) /* ԭʼ�ж�״̬�Ĵ����� */



#ifndef __ASSEMBLY__

/********************************************************************************/
/*    timer �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    timern_loadcount_l         : 32; /* [31..0] ��ʱ��n��ʼֵ��32λ��ע������timer���õ�λ���λ��ȡֵΪ0�� */
    } bits;
    unsigned int    u32;
}HI_TIMER_LOADCOUNT_T;    /* ��ʱ��n�ĵ�32λ��ʼֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    timern_loadcount_h         : 32; /* [31..0] ��ʱ��n��ʼֵ��32λ��ע������timer���õ�λ���λ��ȡֵΪ0�� */
    } bits;
    unsigned int    u32;
}HI_TIMER_LOADCOUNT_H_T;    /* ��ʱ��n�ĸ�32λ��ʼֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    timern_currentvalue_l      : 32; /* [31..0] ��ʱ��n��ǰֵ��32λ�� */
    } bits;
    unsigned int    u32;
}HI_TIMER_CURRENTVALUE_T;    /* ��ʱ��n�ĵ�32λ��ǰֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    timern_currentvalue_h      : 32; /* [31..0] ��ʱ��n��ǰֵ��32λ�� */
    } bits;
    unsigned int    u32;
}HI_TIMER_CURRENTVALUE_H_T;    /* ��ʱ��n�ĸ�32λ��ǰֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    timern_en                  : 1; /* [0..0] ��ʱ��n��ʹ��λ��0���رն�ʱ��1��1���򿪶�ʱ��1�� */
        unsigned int    timern_mode                : 1; /* [1..1] ��ʱ��nģʽ����λ��0������ģʽ��1������ģʽ�� */
        unsigned int    timern_int_mask            : 1; /* [2..2] ��ʱ��n�ж�����λ��0���������жϣ�1�������жϡ� */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    timern_en_ack              : 1; /* [4..4] timernʹ�����÷�����־��0����ʱʹ������δ��Ч��1����ʱʹ��������Ч��ע����bit�ڸ�λ���������pclk���ں��Զ���Ϊ1�� */
        unsigned int    reserved_0                 : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_TIMER_CONTROLREG_T;    /* ��ʱ��n�Ŀ��ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    timern_eoi                 : 1; /* [0..0] ���üĴ��������ʱ��n���жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ���� */
    } bits;
    unsigned int    u32;
}HI_TIMER_EOI_T;    /* ��ʱ��n�����жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    timern_int_status          : 1; /* [0..0] ��ʱ��n���ж�״̬�Ĵ�����0���ж���Ч��1���ж���Ч�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_TIMER_INTSTATUS_T;    /* ��ʱ��n���ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    timer1_int_status          : 1; /* [0..0] ��ʱ��1��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer2_int_status          : 1; /* [1..1] ��ʱ��2��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer3_int_status          : 1; /* [2..2] ��ʱ��3��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer4_int_status          : 1; /* [3..3] ��ʱ��4��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer5_int_status          : 1; /* [4..4] ��ʱ��5��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer6_int_status          : 1; /* [5..5] ��ʱ��6��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer7_int_status          : 1; /* [6..6] ��ʱ��7��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer8_int_status          : 1; /* [7..7] ��ʱ��8��������֮����ж�״̬λ��0���ж���Ч��1���ж���Ч�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_TIMERS_INTSTATUS_T;    /* ��ʱ���ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���üĴ����������8����ʱ�����жϡ� */
    } bits;
    unsigned int    u32;
}HI_TIMERS_EOI_T;    /* ��ʱ�����жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    timer1_raw_int_status      : 1; /* [0..0] ��ʱ��1δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer2_raw_int_status      : 1; /* [1..1] ��ʱ��2δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer3_raw_int_status      : 1; /* [2..2] ��ʱ��3δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer4_raw_int_status      : 1; /* [3..3] ��ʱ��4δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer5_raw_int_status      : 1; /* [4..4] ��ʱ��5δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer6_raw_int_status      : 1; /* [5..5] ��ʱ��6δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer7_raw_int_status      : 1; /* [6..6] ��ʱ��7δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    timer8_raw_int_status      : 1; /* [7..7] ��ʱ��8δ�����ε��ж�״̬��0���ж���Ч��1���ж���Ч�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_TIMERS_RAWINTSTATUS_T;    /* ԭʼ�ж�״̬�Ĵ����� */


/********************************************************************************/
/*    timer ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
#if 0
HI_SET_GET(hi_timer_loadcount_timern_loadcount_l,timern_loadcount_l,HI_TIMER_LOADCOUNT_T,HI_TIMER_BASE_ADDR, HI_TIMER_LOADCOUNT_OFFSET)
HI_SET_GET(hi_timer_loadcount_h_timern_loadcount_h,timern_loadcount_h,HI_TIMER_LOADCOUNT_H_T,HI_TIMER_BASE_ADDR, HI_TIMER_LOADCOUNT_H_OFFSET)
HI_SET_GET(hi_timer_currentvalue_timern_currentvalue_l,timern_currentvalue_l,HI_TIMER_CURRENTVALUE_T,HI_TIMER_BASE_ADDR, HI_TIMER_CURRENTVALUE_OFFSET)
HI_SET_GET(hi_timer_currentvalue_h_timern_currentvalue_h,timern_currentvalue_h,HI_TIMER_CURRENTVALUE_H_T,HI_TIMER_BASE_ADDR, HI_TIMER_CURRENTVALUE_H_OFFSET)
HI_SET_GET(hi_timer_controlreg_timern_en,timern_en,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_controlreg_timern_mode,timern_mode,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_controlreg_timern_int_mask,timern_int_mask,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_controlreg_reserved_1,reserved_1,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_controlreg_timern_en_ack,timern_en_ack,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_controlreg_reserved_0,reserved_0,HI_TIMER_CONTROLREG_T,HI_TIMER_BASE_ADDR, HI_TIMER_CONTROLREG_OFFSET)
HI_SET_GET(hi_timer_eoi_timern_eoi,timern_eoi,HI_TIMER_EOI_T,HI_TIMER_BASE_ADDR, HI_TIMER_EOI_OFFSET)
HI_SET_GET(hi_timer_eoi_reserved,reserved,HI_TIMER_EOI_T,HI_TIMER_BASE_ADDR, HI_TIMER_EOI_OFFSET)
HI_SET_GET(hi_timer_intstatus_timern_int_status,timern_int_status,HI_TIMER_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMER_INTSTATUS_OFFSET)
HI_SET_GET(hi_timer_intstatus_reserved,reserved,HI_TIMER_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMER_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer1_int_status,timer1_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer2_int_status,timer2_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer3_int_status,timer3_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer4_int_status,timer4_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer5_int_status,timer5_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer6_int_status,timer6_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer7_int_status,timer7_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_timer8_int_status,timer8_int_status,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_intstatus_reserved,reserved,HI_TIMERS_INTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_INTSTATUS_OFFSET)
HI_SET_GET(hi_timers_eoi_reserved,reserved,HI_TIMERS_EOI_T,HI_TIMER_BASE_ADDR, HI_TIMERS_EOI_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer1_raw_int_status,timer1_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer2_raw_int_status,timer2_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer3_raw_int_status,timer3_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer4_raw_int_status,timer4_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer5_raw_int_status,timer5_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer6_raw_int_status,timer6_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer7_raw_int_status,timer7_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_timer8_raw_int_status,timer8_raw_int_status,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
HI_SET_GET(hi_timers_rawintstatus_reserved,reserved,HI_TIMERS_RAWINTSTATUS_T,HI_TIMER_BASE_ADDR, HI_TIMERS_RAWINTSTATUS_OFFSET)
#endif
#endif
#endif // __HI_TIMER_H__

