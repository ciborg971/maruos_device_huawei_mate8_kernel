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

#ifndef __HI_WDT_H__
#define __HI_WDT_H__

/*
 * Project: hi
 * Module : wdt
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    wdt �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_WDG_LOAD_OFFSET                                (0x0) /* ������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ�� */
#define    HI_WDG_VALUE_OFFSET                               (0x4) /* ��������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ�� */
#define    HI_WDG_CONTROL_OFFSET                             (0x8) /* ���ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ� */
#define    HI_WDG_INTCLR_OFFSET                              (0xC) /* �ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ�� */
#define    HI_WDG_RIS_OFFSET                                 (0x10) /* ԭʼ�жϼĴ����� */
#define    HI_WDG_MIS_OFFSET                                 (0x14) /* ���κ��жϼĴ����� */
#define    HI_WDG_LOCK_OFFSET                                (0xC00) /* LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ� */
#define		HI_WDG_SYSCTRL_ENABLE_OFFSET				(0x33C)/*��ȡϵͳ���ƼĴ���33c bit[0] ,0�򿪿��Ź���1�رտ��Ź�*/
/********************************************************************************/
/*    wdt �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    wdg_load                   : 32; /* [31..0] Watchdog�ڲ��ݼ��������ĳ�ʼֵ����ֵһ����ˢ�£��������������������� */
    } bits;
    unsigned int    u32;
}HI_WDG_LOAD_T;    /* ������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ�� */

typedef union
{
    struct
    {
        unsigned int    wdogvalue                  : 32; /* [31..0] ���ڵݼ������ļ�������ǰֵ�� */
    } bits;
    unsigned int    u32;
}HI_WDG_VALUE_T;    /* ��������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ�� */

typedef union
{
    struct
    {
        unsigned int    inten                      : 1; /* [0..0] WatchDog�ж��ź����ʹ�ܡ�0��������ֹͣ����������ֵ���ֵ�ǰֵ���䣬WatchDog���رգ�1����������������ʹ���жϣ�WatchDog�����������ж���ǰ����ֹ�����ж��ٴα�ʹ��ʱ���������ӼĴ���WdogLoad�������ֵ�����¿�ʼ������ */
        unsigned int    resen                      : 1; /* [1..1] WatchDog��λ�ź����ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_CONTROL_T;    /* ���ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ� */

typedef union
{
    struct
    {
        unsigned int    wdg_intclr                 : 32; /* [31..0] �ԸüĴ���д������ֵ�����WatchDog���жϣ���ʹWatchDog�ӼĴ���WDG_LOAD�����������ֵ���¼����� */
    } bits;
    unsigned int    u32;
}HI_WDG_INTCLR_T;    /* �ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ�� */

typedef union
{
    struct
    {
        unsigned int    wdogris                    : 1; /* [0..0] WatchDogԭʼ�ж�״̬�����������ļ���ֵ�ݼ���0ʱ����λ��1��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_RIS_T;    /* ԭʼ�жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    wdogmis                    : 1; /* [0..0] WatchDog�����κ��ж�״̬��0��δ�����жϻ����жϱ����Σ�1���Ѳ����жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_MIS_T;    /* ���κ��жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    wdg_lock                   : 32; /* [31..0] ��üĴ���д��0x1ACC_E551���ɴ����мĴ�����дȨ�ޣ���üĴ���д������ֵ��ر�дȨ�ޡ����üĴ������ؼ�����״̬������д��üĴ�����ֵ��0x0000_0000������д���ʣ�δ��������0x0000_0001����ֹд���ʣ��Ѽ������� */
    } bits;
    unsigned int    u32;
}HI_WDG_LOCK_T;    /* LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ� */


/********************************************************************************/
/*    wdt ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_wdg_load_wdg_load,wdg_load,HI_WDG_LOAD_T,HI_WDT_BASE_ADDR, HI_WDG_LOAD_OFFSET)
HI_SET_GET(hi_wdg_value_wdogvalue,wdogvalue,HI_WDG_VALUE_T,HI_WDT_BASE_ADDR, HI_WDG_VALUE_OFFSET)
HI_SET_GET(hi_wdg_control_inten,inten,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_resen,resen,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_reserved,reserved,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_intclr_wdg_intclr,wdg_intclr,HI_WDG_INTCLR_T,HI_WDT_BASE_ADDR, HI_WDG_INTCLR_OFFSET)
HI_SET_GET(hi_wdg_ris_wdogris,wdogris,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_ris_reserved,reserved,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_mis_wdogmis,wdogmis,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_mis_reserved,reserved,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_lock_wdg_lock,wdg_lock,HI_WDG_LOCK_T,HI_WDT_BASE_ADDR, HI_WDG_LOCK_OFFSET)

#endif // __HI_WDT_H__

