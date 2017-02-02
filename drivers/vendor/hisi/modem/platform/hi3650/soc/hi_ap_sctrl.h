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

#ifndef __HI_AP_SCTRL_H__
#define __HI_AP_SCTRL_H__

/*
 * Project: hi
 * Module : AP_SCTRL
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    AP_SCTRL �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_AP_SCTRL_SCCTRL_OFFSET                         (0x0) /* ϵͳ�������Ĵ��� */
#define    HI_AP_SCTRL_SCSYSSTAT_OFFSET                      (0x4) /* ϵͳ״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCITMCTRL_OFFSET                      (0x8) /* �ж�ģʽ���ƼĴ��� */
#define    HI_AP_SCTRL_SCIMSTAT_OFFSET                       (0xC) /* �ж�ģʽ״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCXTALCTRL_OFFSET                     (0x10) /* ������ƼĴ��� */
#define    HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET                 (0x14) /* �����ȶ�ʱ�����üĴ���0 */
#define    HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET                 (0x18) /* �����ȶ�ʱ�����üĴ���1 */
#define    HI_AP_SCTRL_SCXTALSTAT_OFFSET                     (0x1C) /* �������״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCPPLLCTRL0_OFFSET                    (0x20) /* PPLL0���ƼĴ���0 */
#define    HI_AP_SCTRL_SCPPLLCTRL1_OFFSET                    (0x24) /* PPLL0���ƼĴ���1 */
#define    HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET                  (0x28) /* PPLL0 SSC���ƼĴ��� */
#define    HI_AP_SCTRL_SCPPLLSTAT_OFFSET                     (0x2C) /* PPLL0״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCPEREN0_OFFSET                       (0x30) /* ����ʱ��ʹ�ܼĴ���0 */
#define    HI_AP_SCTRL_SCPERDIS0_OFFSET                      (0x34) /* ����ʱ�ӽ�ֹ�Ĵ���0 */
#define    HI_AP_SCTRL_SCPERCLKEN0_OFFSET                    (0x38) /* ����ʱ��ʹ��״̬�Ĵ���0 */
#define    HI_AP_SCTRL_SCPERSTAT0_OFFSET                     (0x3C) /* ����ʱ������״̬�Ĵ���0 */
#define    HI_AP_SCTRL_SCPEREN1_OFFSET                       (0x40) /* ����ʱ��ʹ�ܼĴ���1 */
#define    HI_AP_SCTRL_SCPERDIS1_OFFSET                      (0x44) /* ����ʱ�ӽ�ֹ�Ĵ���1 */
#define    HI_AP_SCTRL_SCPERCLKEN1_OFFSET                    (0x48) /* ����ʱ��ʹ��״̬�Ĵ���1 */
#define    HI_AP_SCTRL_SCPERSTAT1_OFFSET                     (0x4C) /* ����ʱ������״̬�Ĵ���1 */
#define    HI_AP_SCTRL_SCPEREN2_OFFSET                       (0x50) /* ����ʱ��ʹ�ܼĴ���2 */
#define    HI_AP_SCTRL_SCPERDIS2_OFFSET                      (0x54) /* ����ʱ�ӽ�ֹ�Ĵ���2 */
#define    HI_AP_SCTRL_SCPERCLKEN2_OFFSET                    (0x58) /* ����ʱ��ʹ��״̬�Ĵ���2 */
#define    HI_AP_SCTRL_SCPERSTAT2_OFFSET                     (0x5C) /* ����ʱ������״̬�Ĵ���2 */
#define    HI_AP_SCTRL_SCPERRSTEN0_OFFSET                    (0x80) /* ������λʹ�ܼĴ���0 */
#define    HI_AP_SCTRL_SCPERRSTDIS0_OFFSET                   (0x84) /* ������λ����Ĵ���0 */
#define    HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET                  (0x88) /* ������λ״̬�Ĵ���0 */
#define    HI_AP_SCTRL_SCPERRSTEN1_OFFSET                    (0x8C) /* ������λʹ�ܼĴ���1 */
#define    HI_AP_SCTRL_SCPERRSTDIS1_OFFSET                   (0x90) /* ������λ����Ĵ���1 */
#define    HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET                  (0x94) /* ������λ״̬�Ĵ���1 */
#define    HI_AP_SCTRL_SCPERRSTEN2_OFFSET                    (0x98) /* ������λʹ�ܼĴ���2 */
#define    HI_AP_SCTRL_SCPERRSTDIS2_OFFSET                   (0x9C) /* ������λ����Ĵ���2 */
#define    HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET                  (0xA0) /* ������λ״̬�Ĵ���2 */
#define    HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET                  (0xA4) /* IP�����߹������ƼĴ��� */
#define    HI_AP_SCTRL_SCISOEN_OFFSET                        (0xC0) /* ������ϵͳISOʹ�ܼĴ��� */
#define    HI_AP_SCTRL_SCISODIS_OFFSET                       (0xC4) /* ������ϵͳISOʹ�ܳ����Ĵ��� */
#define    HI_AP_SCTRL_SCISOSTAT_OFFSET                      (0xC8) /* ������ϵͳISOʹ��״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCPWREN_OFFSET                        (0xD0) /* ������ϵͳ��Դʹ�ܼĴ��� */
#define    HI_AP_SCTRL_SCPWRDIS_OFFSET                       (0xD4) /* ������ϵͳ��Դʹ�ܳ����Ĵ��� */
#define    HI_AP_SCTRL_SCPWRSTAT_OFFSET                      (0xD8) /* ������ϵͳ��Դʹ��״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCPWRACK_OFFSET                       (0xDC) /* ������ϵͳ���յ�Դ״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET               (0xE0) /* ����������ʱ�����üĴ��� */
#define    HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET                 (0xE4) /* �������ϵ�ʱ�����üĴ��� */
#define    HI_AP_SCTRL_SCCLKDIV0_OFFSET                      (0x100) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���0 */
#define    HI_AP_SCTRL_SCCLKDIV1_OFFSET                      (0x104) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���1 */
#define    HI_AP_SCTRL_SCCLKDIV2_OFFSET                      (0x108) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���2 */
#define    HI_AP_SCTRL_SCCLKDIV3_OFFSET                      (0x10C) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���3 */
#define    HI_AP_SCTRL_SCCLKDIV4_OFFSET                      (0x110) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���4 */
#define    HI_AP_SCTRL_SCCLKDIV5_OFFSET                      (0x114) /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���5 */
#define    HI_AP_SCTRL_SCPERCTRL0_OFFSET                     (0x200) /* ������ƼĴ���0 */
#define    HI_AP_SCTRL_SCPERCTRL1_OFFSET                     (0x204) /* ������ƼĴ���1 */
#define    HI_AP_SCTRL_SCPERCTRL2_OFFSET                     (0x208) /* ������ƼĴ���2 */
#define    HI_AP_SCTRL_SCPERCTRL3_OFFSET                     (0x20C) /* ������ƼĴ���3 */
#define    HI_AP_SCTRL_SCPERCTRL4_OFFSET                     (0x210) /* ������ƼĴ���4 */
#define    HI_AP_SCTRL_SCPERCTRL5_OFFSET                     (0x214) /* ������ƼĴ���5 */
#define    HI_AP_SCTRL_SCPERCTRL6_OFFSET                     (0x218) /* ������ƼĴ���6 */
#define    HI_AP_SCTRL_SCPERSTATUS0_OFFSET                   (0x21C) /* ����״̬�Ĵ���0 */
#define    HI_AP_SCTRL_SCPERSTATUS1_OFFSET                   (0x220) /* ����״̬�Ĵ���1 */
#define    HI_AP_SCTRL_SCPERSTATUS2_OFFSET                   (0x224) /* ����״̬�Ĵ���2 */
#define    HI_AP_SCTRL_SCPERSTATUS3_OFFSET                   (0x228) /* ����״̬�Ĵ���3 */
#define    HI_AP_SCTRL_SCPERSTATUS4_OFFSET                   (0x22C) /* ����״̬�Ĵ���4 */
#define    HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET                  (0x300) /* ����ָʾϵͳ������������˯�ߵ�״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET                  (0x304) /* MRB EFUSE BUSY״ָ̬ʾ�Ĵ��� */
#define    HI_AP_SCTRL_SCSWADDR_OFFSET                       (0x308) /* ���ڱ��������ڵ�ַ�ļĴ��� */
#define    HI_AP_SCTRL_SCDDRADDR_OFFSET                      (0x30C) /* ���ڱ���DDRѵ�����ݵĵ�ַ�ļĴ��� */
#define    HI_AP_SCTRL_SCDDRDATA_OFFSET                      (0x310) /* ���ڱ���DDRѵ�����ݵļĴ��� */
#define    HI_AP_SCTRL_SCBAKDATA0_OFFSET                     (0x314) /* �������ʹ�õĴ洢���ݼĴ���0 */
#define    HI_AP_SCTRL_SCBAKDATA1_OFFSET                     (0x318) /* �������ʹ�õĴ洢���ݼĴ���1 */
#define    HI_AP_SCTRL_SCBAKDATA2_OFFSET                     (0x31C) /* �������ʹ�õĴ洢���ݼĴ���2 */
#define    HI_AP_SCTRL_SCBAKDATA3_OFFSET                     (0x320) /* �������ʹ�õĴ洢���ݼĴ���3 */
#define    HI_AP_SCTRL_SCBAKDATA4_OFFSET                     (0x324) /* �������ʹ�õĴ洢���ݼĴ���4 */
#define    HI_AP_SCTRL_SCBAKDATA5_OFFSET                     (0x328) /* �������ʹ�õĴ洢���ݼĴ���5 */
#define    HI_AP_SCTRL_SCBAKDATA6_OFFSET                     (0x32C) /* �������ʹ�õĴ洢���ݼĴ���6 */
#define    HI_AP_SCTRL_SCBAKDATA7_OFFSET                     (0x330) /* �������ʹ�õĴ洢���ݼĴ���7 */
#define    HI_AP_SCTRL_SCBAKDATA8_OFFSET                     (0x334) /* �������ʹ�õĴ洢���ݼĴ���8 */
#define    HI_AP_SCTRL_SCBAKDATA9_OFFSET                     (0x338) /* �������ʹ�õĴ洢���ݼĴ���9 */
#define    HI_AP_SCTRL_SCBAKDATA10_OFFSET                    (0x33C) /* �������ʹ�õĴ洢���ݼĴ���10 */
#define    HI_AP_SCTRL_SCBAKDATA11_OFFSET                    (0x340) /* �������ʹ�õĴ洢���ݼĴ���11 */
#define    HI_AP_SCTRL_SCBAKDATA12_OFFSET                    (0x344) /* �������ʹ�õĴ洢���ݼĴ���12 */
#define    HI_AP_SCTRL_SCBAKDATA13_OFFSET                    (0x348) /* �������ʹ�õĴ洢���ݼĴ���13 */
#define    HI_AP_SCTRL_SCBAKDATA14_OFFSET                    (0x34C) /* �������ʹ�õĴ洢���ݼĴ���14 */
#define    HI_AP_SCTRL_SCBAKDATA15_OFFSET                    (0x350) /* �������ʹ�õĴ洢���ݼĴ���15 */
#define    HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET              (0x450) /* �ۺϺ���ж�״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCINT_MASK_OFFSET                     (0x454) /* �ж��������üĴ��� */
#define    HI_AP_SCTRL_SCINT_STAT_OFFSET                     (0x458) /* ԭʼ�ж�״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET                  (0x45C) /* DRX�жϷ������üĴ��� */
#define    HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET              (0x460) /* LPM3 WFI�ж�����Ĵ��� */
#define    HI_AP_SCTRL_SCMALIBYPCFG_OFFSET                   (0x48C) /* MALI DBGACK BYPASS���üĴ��� */
#define    HI_AP_SCTRL_SCLPM3CLKEN_OFFSET                    (0x500) /* LPM3��ϵͳʱ��ʹ�ܼĴ��� */
#define    HI_AP_SCTRL_SCLPM3RSTEN_OFFSET                    (0x504) /* LPM3��ϵͳ��λʹ�ܼĴ��� */
#define    HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET                   (0x508) /* LPM3��ϵͳ��λ����Ĵ��� */
#define    HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET                  (0x50C) /* LPM3��ϵͳ��λʹ��״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCLPM3CTRL_OFFSET                     (0x510) /* LPM3��ϵͳ�������üĴ��� */
#define    HI_AP_SCTRL_SCLPM3STAT_OFFSET                     (0x514) /* LPM3��ϵͳ״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET                  (0x518) /* LPM3 RAM ���ƼĴ��� */
#define    HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET                  (0x530) /* BBPDRX��ϵͳ״̬�Ĵ���0 */
#define    HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET                  (0x534) /* BBPDRX��ϵͳ״̬�Ĵ���1 */
#define    HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET                  (0x538) /* BBPDRX��ϵͳ״̬�Ĵ���2 */
#define    HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET                (0x550) /* A7 EVENT���μĴ��� */
#define    HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET               (0x554) /* A15 EVENT���μĴ��� */
#define    HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET              (0x558) /* IOM3 EVENT���μĴ��� */
#define    HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET              (0x55C) /* LPM3 EVENT���μĴ��� */
#define    HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET              (0x560) /* MCPU EVENT���μĴ��� */
#define    HI_AP_SCTRL_SCEVENT_STAT_OFFSET                   (0x564) /* EVENT״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCJTAG_SEL_OFFSET                     (0x800) /* JTAGѡ����ƼĴ��� */
#define    HI_AP_SCTRL_SCMODEM_KEY0_OFFSET                   (0x804) /* MODEM_KEY0 */
#define    HI_AP_SCTRL_SCMODEM_KEY1_OFFSET                   (0x808) /* MODEM_KEY1 */
#define    HI_AP_SCTRL_SCMODEM_KEY2_OFFSET                   (0x80C) /* MODEM_KEY2 */
#define    HI_AP_SCTRL_SCMODEM_KEY3_OFFSET                   (0x810) /* MODEM_KEY3 */
#define    HI_AP_SCTRL_SCCFG_DJTAG_OFFSET                    (0x814) /* DJTAG���ƼĴ��� */
#define    HI_AP_SCTRL_SCCP15_DISABLE_OFFSET                 (0x818) /* CP15DISABLE���ƼĴ��� */
#define    HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET                   (0x81C) /* ʱ�Ӽ���״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCCLKCNTCFG_OFFSET                    (0x820) /* ʱ�Ӽ������üĴ��� */
#define    HI_AP_SCTRL_SCCLKMONCTRL_OFFSET                   (0x824) /* ʱ�Ӽ�ؿ��ƼĴ��� */
#define    HI_AP_SCTRL_SCCLKMONINT_OFFSET                    (0x828) /* ʱ�Ӽ���ж�״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET                (0x82C) /* ARM debug en���üĴ��� */
#define    HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET                 (0x830) /* ARM debug key0���üĴ��� */
#define    HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET                 (0x834) /* ARM debug key1���üĴ��� */
#define    HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET               (0x838) /* ARM debug en״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCEFUSECTRL_OFFSET                    (0x83C) /* EFUSE PAD��д���ƼĴ��� */
#define    HI_AP_SCTRL_SCEFUSESEL_OFFSET                     (0x840) /* AOCC/SECSʱ���ſؼĴ��� */
#define    HI_AP_SCTRL_SCSECURITYSTAT_OFFSET                 (0x844) /* EFUSE SECURITY״̬�Ĵ��� */
#define    HI_AP_SCTRL_SCCHIP_ID0_OFFSET                     (0x848) /* EFUSE CHIP_ID0�Ĵ��� */
#define    HI_AP_SCTRL_SCCHIP_ID1_OFFSET                     (0x84C) /* EFUSE CHIP_ID1�Ĵ��� */
#define    HI_AP_SCTRL_SCSOCID0_OFFSET                       (0xE00) /* SOCID�Ĵ���0 */

/********************************************************************************/
/*    AP_SCTRL �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    modectrl                   : 3; /* [2..0] ϵͳģʽ���ơ����ﶨ����ϵͳ�����Ĺ���ģʽ��000��SLEEP��001��DOZE��01X�� SLOW��1XX:��NORMAL�� */
        unsigned int    modestatus                 : 4; /* [6..3] ָʾϵͳ������ϵͳ״̬����ǰ����ģʽ��0000��SLEEP��0001��DOZE��0011��XTAL CTL��1000��XTAL_OFF��1011��SW to XTAL��1001��SW from XTAL��0010��SLOW��0110��PLL CTL��1110��SW to PLL��1010��SW from PLL��0100��NORMAL��Others�������� */
        unsigned int    reserved_1                 : 1; /* [7..7] ������ */
        unsigned int    timeforcehigh              : 1; /* [8..8] Timer01��Timer23��Timer45��Timer67ʹ�ܶ�ǿ�����ߵ�Ӳ��ʹ�����á�0��Ӳ���������Զ�������1����ϵͳʱ����32Kʱ��Ӳ���Զ�ǿ������Timer01��Timer23��Timer45��Timer67��ʹ�ܡ� */
        unsigned int    timeren0sel                : 1; /* [9..9] Time0ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren0ov                 : 1; /* [10..10] Timer0ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren0sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren1sel                : 1; /* [11..11] Time1ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren1ov                 : 1; /* [12..12] Timer1ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren1sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren2sel                : 1; /* [13..13] Time2ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren2ov                 : 1; /* [14..14] Timer2ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren2sel]ָ����1��ʹ���źű�ǿ�����ߡ�ע����TIMER�а�ȫ�������󣬿�ͨ�����ð�ȫ����timer_secu_enλ��ǿ��ѡ��32KHZʱ�� */
        unsigned int    timeren3sel                : 1; /* [15..15] Time3ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren3ov                 : 1; /* [16..16] Timer3ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren3sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren4sel                : 1; /* [17..17] Time4ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren4ov                 : 1; /* [18..18] Timer4ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren4sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren5sel                : 1; /* [19..19] Time5ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren5ov                 : 1; /* [20..20] Timer5ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren5sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren6sel                : 1; /* [21..21] Time6ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren6ov                 : 1; /* [22..22] Timer6ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren6sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    timeren7sel                : 1; /* [23..23] Time7ʱ��ʹ�ܲο�ʱ��ѡ��0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int    timeren7ov                 : 1; /* [24..24] Timer7ʱ��ʹ�ܿ��ơ�0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren7sel]ָ����1��ʹ���źű�ǿ�����ߡ� */
        unsigned int    deepsleepen                : 1; /* [25..25] ����DEEP SLEEPģʽʹ�ܼĴ��������ø�bit����״̬������������̣���NORMALģʽ�����ã����modectrl�����ã�0����ʾ��ʹ�ܣ�1����ʾʹ�ܡ� */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCTRL_T;    /* ϵͳ�������Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reset_source               : 11; /* [10..0] ��λԴָʾ��[10]:modem_wd_rst_req[9]:asp_subsys_wd_req[8]:iom3_rst_req[7]:modem_tsensor_rst_req[6]:lpm3_rst_req[5]:wd1_rst_req[4]:wd0_rst_req[3]:soft_rst_req[2]:g3d_tsensor_rst_req[1]:a7_tsensor_rst_req[0]:a15_tsensor_rst_req */
        unsigned int    reserved                   : 21; /* [31..11] д�����üĴ���д������ֵ�ᴥ��ϵͳ��λ���������üĴ���������λԴ�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSYSSTAT_T;    /* ϵͳ״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    itmden                     : 1; /* [0..0] �ж�ģʽʹ�ܡ�0���ж�ģʽ����ֹ��1�������жϷ���ʱ�������ж�ģʽ�� */
        unsigned int    itmdctrl                   : 3; /* [3..1] �����ж�ģʽ��ϵͳ��͵Ĺ���ģʽ���üĴ�����ֵ��SCCTRL�Ĵ���ModeCtrl��ֵ������Ϊ�жϷ�����ϵͳ�����Ĺ���ģʽ�� */
        unsigned int    reserved_1                 : 3; /* [6..4] ������ */
        unsigned int    inmdtype                   : 1; /* [7..7] ���ô���ϵͳ�����ж�ģʽ���ж����͡�0��FIQ��1��FIQ����IRQ�� */
        unsigned int    reserved_0                 : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCITMCTRL_T;    /* �ж�ģʽ���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    itmdstat                   : 1; /* [0..0] �ж�ģʽ״̬����λ���������������ֱ�ӽ����ж�ģʽ�����üĴ���ʱ��0����ǰδ�����ж�ģʽ��1����ǰ�����ж�ģʽ��д�üĴ���ʱ��A����ǰ���ڷ��ж���Ӧģʽ�£�0����������ƽ����ж�ģʽ��1���������жϴ���ֱ�ӽ����ж�ģʽ��B����ǰ�Ѿ������ж���Ӧģʽ��0������ж���Ӧģʽ1��������ж���Ӧģʽ������B�������£�ϵͳ�����ж���Ӧģʽ���Ҵ���SLOWģʽ�£���ʱҪ������Ĳ�������Ϊ��1������Ŀ��ģʽΪNORMALģʽ��2����NORMALģʽ�����FIQ��IRQ�жϣ�3�����itmdstat���أ����Ըñ���д0�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIMSTAT_T;    /* �ж�ģʽ״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    tcxopresel_apb             : 1; /* [0..0] ����ѡ��Ԥ���ã��´λ���ʱ�л���ѡ������ֻ��tcxosoft_apbΪ0����tcxohardcon_bypassΪ1ʱ�ù��ܲ���Ч�� */
        unsigned int    tcxohardcon_bypass         : 1; /* [1..1] ����ѡ��Ӳ���л����Σ�1��ѡ��Ԥ���ù���0��ѡ��Ӳ���Զ��л� */
        unsigned int    tcxosel_apb                : 1; /* [2..2] �������л�ѡ��1��ѡ��TCXO10��ѡ��TCXO0 */
        unsigned int    tcxosoft_apb               : 1; /* [3..3] �������л�ѡ��1��ѡ��tcxosel_apb0��ѡ��Ԥ�л�����Ӳ���Զ��л� */
        unsigned int    defau_tcxo                 : 1; /* [4..4] ��DRX�жϵ���Ĭ��ѡ��TCXO1��ѡ����10��ѡ����0 */
        unsigned int    tcxofast_ctrl0             : 1; /* [5..5] ����0������������1����������0���������� */
        unsigned int    tcxofast_ctrl1             : 1; /* [6..6] ����1������������1����������0���������� */
        unsigned int    ctrlen1_apb                : 1; /* [7..7] ����1���ʹ�ܿ��ƣ�1������ʹ��0������ȥʹ�� */
        unsigned int    ctrlsel1_apb               : 1; /* [8..8] ����1�������ѡ��1��ѡ��ctrlen1_apb0��ѡ��Ӳ���Զ����� */
        unsigned int    ctrlen0_apb                : 1; /* [9..9] ����0���ʹ�ܿ��ƣ�1������ʹ��0������ȥʹ�� */
        unsigned int    ctrlsel0_apb               : 1; /* [10..10] ����0�������ѡ��1��ѡ��ctrlen0_apb0��ѡ��Ӳ���Զ����� */
        unsigned int    timeout_bypass0            : 1; /* [11..11] ״̬����⾧��0��ʱBYPASS����1��BYPASSʹ��0��BYPASSȥʹ�� */
        unsigned int    timeout_bypass1            : 1; /* [12..12] ״̬����⾧��1��ʱBYPASS����1��BYPASSʹ��0��BYPASSȥʹ�� */
        unsigned int    tcxoseq_bypass             : 1; /* [13..13] ״̬����⾧��ر����BYPASS����1��BYPASSʹ��0��BYPASSȥʹ�� */
        unsigned int    tcxoseq0_time              : 5; /* [18..14] �ؾ���0���ABB BUF��ʱ��������32KHZΪʱ������ */
        unsigned int    tcxoseq1_time              : 5; /* [23..19] �ؾ���1���ABB BUF��ʱ��������32KHZΪʱ������ */
        unsigned int    reserved                   : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALCTRL_T;    /* ������ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    timeoutcnt0_apb            : 32; /* [31..0] 32KHZʱ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALTIMEOUT0_T;    /* �����ȶ�ʱ�����üĴ���0 */

typedef union
{
    struct
    {
        unsigned int    timeoutcnt1_apb            : 32; /* [31..0] 32KHZʱ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALTIMEOUT1_T;    /* �����ȶ�ʱ�����üĴ���1 */

typedef union
{
    struct
    {
        unsigned int    tcxo_en0                   : 1; /* [0..0] ����0�����ж�״̬ */
        unsigned int    tcxo_en1                   : 1; /* [1..1] ����1�����ж�״̬ */
        unsigned int    tcxo_timeout1              : 1; /* [2..2] ����1��ʱ״̬ */
        unsigned int    tcxo_timeout0              : 1; /* [3..3] ����0��ʱ״̬ */
        unsigned int    sysclk_en1                 : 1; /* [4..4] ����1ʹ��״̬ */
        unsigned int    sysclk_en0                 : 1; /* [5..5] ����0ʹ��״̬ */
        unsigned int    sysclk_sel                 : 1; /* [6..6] ����ѡ��״̬ */
        unsigned int    clkgt_ctrl0                : 1; /* [7..7] ����0���������clk gate�ź� */
        unsigned int    clkgt_ctrl1                : 1; /* [8..8] ����1���������clk gate�ź� */
        unsigned int    clkgt_ctrl                 : 1; /* [9..9] ���������CRG��clk gate�ź� */
        unsigned int    abbbuf_en0                 : 1; /* [10..10] ABB BUF0��ʹ��״̬ */
        unsigned int    abbbuf_en1                 : 1; /* [11..11] ABB BUF1��ʹ��״̬ */
        unsigned int    tcxoseq_finish0            : 1; /* [12..12] ����0�ر����ָʾ״̬ */
        unsigned int    tcxoseq_finish1            : 1; /* [13..13] ����1�ر����ָʾ״̬ */
        unsigned int    reserved                   : 18; /* [31..14] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALSTAT_T;    /* �������״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ppll0_en                   : 1; /* [0..0] PPLL0ʹ�ܿ��ƣ���AUDIO��ϵͳ������PPLLʹ�ܿ��������߼���0��ȥʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    ppll0_bp                   : 1; /* [1..1] PPLL0 Bypass���ơ�0������������1��Bypass�� */
        unsigned int    ppll0_refdiv               : 6; /* [7..2] PPLL0����ʱ�ӷ�Ƶ���� */
        unsigned int    ppll0_fbdiv                : 12; /* [19..8] PPLL0����ʱ��������Ƶ���� */
        unsigned int    ppll0_postdiv1             : 3; /* [22..20] PPLL0���ʱ�ӷ�Ƶ��1�� */
        unsigned int    ppll0_postdiv2             : 3; /* [25..23] PPLL0���ʱ�ӷ�Ƶ��2�� */
        unsigned int    reserved                   : 6; /* [31..26] ���� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLCTRL0_T;    /* PPLL0���ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    ppll0_fracdiv              : 24; /* [23..0] PPLL0����ʱ�ӷ�����Ƶ���� */
        unsigned int    ppll0_int_mod              : 1; /* [24..24] PPLL0������Ƶģʽ��0��������Ƶģʽ��1��������Ƶģʽ��ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int    ppll0_cfg_vld              : 1; /* [25..25] PPLL0������Ч��־��0��������Ч��1��������Ч�� */
        unsigned int    gt_clk_ppll0               : 1; /* [26..26] PPLL0�ſ��źš�0��PPLL0���ʱ���ſأ�1��PPLL0���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int    reserved                   : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLCTRL1_T;    /* PPLL0���ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    ppll0_ssc_reset            : 1; /* [0..0] ��λ�źţ�����Ч��0����λȡ��1����λ��Чע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int    ppll0_ssc_disable          : 1; /* [1..1] Bypass the modulator������Ч��0����������1��bypass */
        unsigned int    ppll0_ssc_downspread       : 1; /* [2..2] ѡ��center spread��down spread0��Center Spread1��Down Spread */
        unsigned int    ppll0_ssc_spread           : 3; /* [5..3] ���õ������(spread%)3'b000 = 03'b001 = 0.049%3'b010 = 0.098%3'b011 = 0.195%3'b100 = 0.391%3'b101 = 0.781%3'b110 = 1.563%3'b111 = 3.125% */
        unsigned int    ppll0_ssc_divval           : 4; /* [9..6] ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int    reserved                   : 22; /* [31..10] ���� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLSSCCTRL_T;    /* PPLL0 SSC���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    pllstat                    : 1; /* [0..0] PPLL0״ָ̬ʾ��0��δ�ȶ���1�����ȶ��� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLSTAT_T;    /* PPLL0״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] ����ʱ��ʹ�ܿ��ƣ�0��д0��Ч����1��ʹ��IPʱ�ӡ� */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN0_T;    /* ����ʱ��ʹ�ܼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] ����ʱ�ӽ�ֹ���ƣ�0��д0��Ч����1����ֹIPʱ�ӡ� */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS0_T;    /* ����ʱ�ӽ�ֹ�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] ����ʱ��ʹ��״̬��0��IPʱ��ʹ�ܳ���״̬��1��IPʱ��ʹ��״̬�� */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN0_T;    /* ����ʱ��ʹ��״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_ao_cc               : 1; /* [0..0] ����ʱ������״̬��0��IPʱ�ӽ�ֹ״̬��1��IPʱ��ʹ��״̬�� */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31] �����Ĵ����ĸ�λֵ��SCTRL�������ź�peri_clk_stat0[31:0]�ĸ�λֵ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT0_T;    /* ����ʱ������״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] ����ʱ��ʹ�ܿ��ƣ�0��д0��Ч��1��д1ʹ��IPʱ�ӡ� */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4]  */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN1_T;    /* ����ʱ��ʹ�ܼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] ����ʱ�ӽ�ֹ���ƣ�0��д0��Ч��1��д1��ֹIPʱ�ӡ� */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4]  */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS1_T;    /* ����ʱ�ӽ�ֹ�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] ����ʱ��ʹ��״̬��0��IPʱ�ӽ�ֹ״̬��1��IPʱ��ʹ��״̬�� */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4] modem��ϵͳ�͸�bbpdrx��ʱ�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN1_T;    /* ����ʱ��ʹ��״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] ����ʱ������״̬��0��IPʱ�ӽ�ֹ״̬��1��IPʱ��ʹ��״̬�� */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4] modem��ϵͳ�͸�bbpdrx��ʱ�� */
        unsigned int    reserved                   : 22; /* [26..5] ������ */
        unsigned int    swdone_clk_asp_subsys_div  : 1; /* [27..27] clk_asp_subsysDIV��Ƶ���л��Ƿ����ָʾ�źţ�0��δ��ɣ�1����ɣ� */
        unsigned int    swdone_clk_sci_div         : 1; /* [28..28] clk_sci DIV��Ƶ���л��Ƿ����ָʾ�źţ�0��δ��ɣ�1����ɣ� */
        unsigned int    swdone_clk_aobus_div       : 1; /* [29..29] clk_aobus DIV��Ƶ���л��Ƿ����ָʾ�źţ�0��δ��ɣ�1����ɣ� */
        unsigned int    aobusclksw2sys             : 1; /* [30..30] aobus clk�л�������ʱ��ָʾ������Ч�� */
        unsigned int    aobusclksw2pll             : 1; /* [31..31] aobus clk�л���PLLʱ��ָʾ������Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT1_T;    /* ����ʱ������״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN2_T;    /* ����ʱ��ʹ�ܼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS2_T;    /* ����ʱ�ӽ�ֹ�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN2_T;    /* ����ʱ��ʹ��״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] �����Ĵ����ĸ�λֵ��SCTRL�������ź�peri_clk_stat2[31:0]�ĸ�λֵ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT2_T;    /* ����ʱ������״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] IP��λʹ�ܣ�0��IP��λʹ��״̬���䣻1��IP��λʹ�ܡ� */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] ������ */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] ������ */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] ������ */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] ������ */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] ��λԴ��Ϣ������ƣ�0��д0��Ч����1����λԴ��Ϣ��������رո�λԴ��¼���ܣ� */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU��λ������ƣ�0��д0��Ч����1��PMU��λ���������ر�PMU��λ���ܣ� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN0_T;    /* ������λʹ�ܼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] IP��λ���룺0��IP��λʹ��״̬���䣻1��IP��λ���롣 */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] ������ */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] ������ */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] ������ */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] ������ */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] ��λԴ����źſ��ƣ�0��д0��Ч����1����λԴ�������������λԴ��¼�������ã� */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU��λ���ܿ��ƣ�0��д0��Ч����1��PMU��λ�������ã� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS0_T;    /* ������λ����Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] ������λʹ��״̬��0��IP��λʹ�ܳ�����1��IP��λʹ�ܣ� */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] ������ */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] ������ */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] ������ */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] ������ */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] ��λԴ�������״̬��0�����ø�λԴ��¼���ܣ�1��������λԴ��¼���ܣ� */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU��λ���ܿ���״̬��0������PMU��λ���ܣ�1������PMU��λ���ܣ� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT0_T;    /* ������λ״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN1_T;    /* ������λʹ�ܼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS1_T;    /* ������λ����Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT1_T;    /* ������λ״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN2_T;    /* ������λʹ�ܼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS2_T;    /* ������λ����Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT2_T;    /* ������λ״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    rst_gt_rtc_bypass          : 1; /* [0..0] 1:BYPASS��λ&ʱ���ſط����߹�������0:ʹ�ܸ�λ&ʱ���ſط����߹������� */
        unsigned int    rst_gt_rtc1_bypass         : 1; /* [1..1]  */
        unsigned int    rst_gt_timer0_bypass       : 1; /* [2..2]  */
        unsigned int    rst_gt_timer1_bypass       : 1; /* [3..3]  */
        unsigned int    rst_gt_timer2_bypass       : 1; /* [4..4]  */
        unsigned int    rst_gt_timer3_bypass       : 1; /* [5..5]  */
        unsigned int    rst_gt_gpio0_bypass        : 1; /* [6..6]  */
        unsigned int    rst_gt_gpio1_bypass        : 1; /* [7..7]  */
        unsigned int    rst_gt_gpio2_bypass        : 1; /* [8..8]  */
        unsigned int    rst_gt_gpio3_bypass        : 1; /* [9..9]  */
        unsigned int    rst_gt_gpio4_bypass        : 1; /* [10..10]  */
        unsigned int    rst_gt_gpio5_bypass        : 1; /* [11..11]  */
        unsigned int    rst_gt_ioc_bypass          : 1; /* [12..12]  */
        unsigned int    rst_gt_syscnt_bypass       : 1; /* [13..13]  */
        unsigned int    rst_gt_sci0_bypass         : 1; /* [14..14]  */
        unsigned int    rst_gt_sci1_bypass         : 1; /* [15..15]  */
        unsigned int    rst_gt_bbpdrx_bypass       : 1; /* [16..16]  */
        unsigned int    rst_gt_efusec_bypass       : 1; /* [17..17]  */
        unsigned int    reserved                   : 14; /* [31..18] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIPCLKRSTBUS_T;    /* IP�����߹������ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISOEN_T;    /* ������ϵͳISOʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISO���������� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISODIS_T;    /* ������ϵͳISOʹ�ܳ����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�1--ISOʹ�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISOSTAT_T;    /* ������ϵͳISOʹ��״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    audiopwren                 : 1; /* [0..0] AUDIO��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWREN_T;    /* ������ϵͳ��Դʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    audiopwren                 : 1; /* [0..0] AUDIO��ϵͳ��Դʹ�ܳ������ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRDIS_T;    /* ������ϵͳ��Դʹ�ܳ����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    audiopwrstat               : 1; /* [0..0] AUDIO��ϵͳ��Դʹ��״̬��0��AUDIO��ϵͳ��Դʹ�ܳ�����1��AUDIO��ϵͳ��Դʹ�ܡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRSTAT_T;    /* ������ϵͳ��Դʹ��״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    audiopwrack                : 1; /* [0..0] AUDIO��ϵͳ��Դ״̬��0��AUDIO��ϵͳ��Դ�ж�״̬��1��AUDIO��ϵͳ��Դ����״̬�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRACK_T;    /* ������ϵͳ���յ�Դ״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    peri_pwr_down_time         : 25; /* [24..0] ָʾPMU�����������������ʱ�䡣�ȶ�ʱ����㹫ʽ����33554432-peri_pwr_down_time+3��������ʱ��Ϊ32K��(�µ����ʱ���ԼΪ600us,Ĭ��Ϊ����20��32Kʱ������) */
        unsigned int    reserved                   : 7; /* [31..25] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERPWRDOWNTIME_T;    /* ����������ʱ�����üĴ��� */

typedef union
{
    struct
    {
        unsigned int    peri_pwr_up_time           : 25; /* [24..0] ָʾPMU���������ϵ������ʱ�䡣�ȶ�ʱ����㹫ʽ����33554432-peri_pwr_up_time+3��������ʱ��Ϊ32K��(�ϵ絽��������ɴ�ԼΪ1.26msĬ��Ϊ����42��32Kʱ������) */
        unsigned int    reserved                   : 7; /* [31..25] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERPWRUPTIME_T;    /* �������ϵ�ʱ�����üĴ��� */

typedef union
{
    struct
    {
        unsigned int    sc_div_asp_subsys          : 3; /* [2..0] ASP SUBSYSʱ�ӷ�Ƶ�ȡ���Դʱ��ΪPPLL0��3'h0:1��3'h1:2��3'h2:3��3'h3:4������3'h7:8�� */
        unsigned int    sc_div_hifidsp             : 6; /* [8..3] HIFIDSPʱ�ӷ�Ƶ�ȡ�6'h0:1��6'h1:2��6'h2:3��6'h3:4����6'h1F:64�� */
        unsigned int    sc_div_sci                 : 2; /* [10..9] SCIʱ�ӷ�Ƶ�ȡ�(Դʱ��Ϊclk_aobus 60MHzʱ�ӣ���Ƶ��������)2'h0:1��2'h1:2��2'h2:3��2'h3:4�� */
        unsigned int    reserved                   : 4; /* [14..11] ������ */
        unsigned int    extclk_en                  : 1; /* [15..15] ����ʱ��ʹ�ܣ�����Ч�� */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV0_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    sc_div_aobus               : 6; /* [5..0] AOBUSʱ�ӷ�Ƶ��ѡ��(Դʱ��ΪPPLL0ʱ�ӣ���Ƶ�ȵ�������)6'h0:1��6'h1:2��6'h2:3����6'h3E:63��6'h3F:64�� */
        unsigned int    div_clkout0_tcxo           : 3; /* [8..6] clkout0 tcxoʱ�ӷ�Ƶ��ѡ�񣺣�Դʱ��Ϊ19.2MHz�ľ���ʱ�ӣ�3'h0:1��3'h1:2��3'h2:3����3'h6:7��3'h7:8�� */
        unsigned int    div_clkout1_tcxo           : 3; /* [11..9] clkout1 tcxoʱ�ӷ�Ƶ��ѡ�񣺣�Դʱ��Ϊ19.2MHz�ľ���ʱ�ӣ�3'h0:1��3'h1:2��3'h2:3����3'h6:7��3'h7:8�� */
        unsigned int    sel_clkout0                : 2; /* [13..12] clkout0 ʱ��Դѡ��0��32KHz��1��19.2MHzʱ�ӷ�Ƶ��2/3��PPLL3ʱ�ӷ�Ƶ�� */
        unsigned int    sel_clkout1                : 2; /* [15..14] clkout1 ʱ��Դѡ��0��32KHz��1��19.2MHzʱ�ӷ�Ƶ��2/3��PPLL3ʱ�ӷ�Ƶ�� */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV1_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_subsys          : 1; /* [0..0] ʱ���ſ����ã�0��ʱ�ӹرգ�1��ʱ�ӿ����� */
        unsigned int    gt_hifidsp_clk_div         : 1; /* [1..1]  */
        unsigned int    gt_clk_sci                 : 1; /* [2..2]  */
        unsigned int    gt_clk_aobus               : 1; /* [3..3]  */
        unsigned int    gt_asp_hclk_div            : 1; /* [4..4]  */
        unsigned int    reserved_1                 : 3; /* [7..5] ������ */
        unsigned int    sc_div_asp_hclk            : 2; /* [9..8] asp hclk��Ƶ�ȣ�2'b0:1��2'b1:2������ */
        unsigned int    reserved_0                 : 6; /* [15..10] ������ */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV2_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] ������ */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV3_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] ������ */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV4_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���4 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] ������ */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV5_T;    /* ʱ�ӷ�Ƶ�ȿ��ƼĴ���5 */

typedef union
{
    struct
    {
        unsigned int    efusec_mem_ctrl            : 16; /* [15..0] efusec��MEMORY���� */
        unsigned int    efuse_remap                : 1; /* [16..16] �͸�EFUSEC��REMAP���� */
        unsigned int    reserved                   : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL0_T;    /* ������ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL1_T;    /* ������ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    repair_disable             : 20; /* [19..0] ����ָʾ����IP�Ƿ���Ҫ��mem repair:bit[19]:MRB19-VENCbit[18]:MRB18-VDECbit[17]:MRB17-MDDRC/MCUbit[16]:MRB16-LTE_BBP_WRAPbit[15]:MRB15-LTE_BBPbit[14]:MRB14-BBP_COMMbit[13]:MRB13-BBE16_WRAPbit[12]:MRB12-MODEM_PERI_WRAPbit[11]:MRB11-ISPbit[10]:MRB10-MALI_SHADERCORE3bit[9]:MRB9-MALI_SHADERCORE2bit[8]:MRB8-MALI_SHADERCORE1bit[7]:MRB7-MALI_SHADERCORE0bit[6]:MRB6-MALI_TOPbit[5]:MRB5-DSS_SDPbit[4]:MRB4-DSS_SUBSYSbit[3]:MRB3-ASP_SUBSYSbit[2]:MRB2-AO_M3_MEMbit[1]:MRB1-A7_CLUSTERbit[0]:MRB0-A15_CLUSTER0�����޸���1�����޸� */
        unsigned int    reserved_1                 : 4; /* [23..20] reserved */
        unsigned int    jtaq_to_sdcard             : 1; /* [24..24] �͸�JTAG MUX�Ŀ����ź� */
        unsigned int    reserved_0                 : 7; /* [31..25] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL2_T;    /* ������ƼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 1; /* [0..0] reserved */
        unsigned int    reset_memrep_msk           : 1; /* [1..1] reset_memrep_msk */
        unsigned int    repair_iddq                : 1; /* [2..2] 1'b0:��IDDQģʽ1'b1:BISR����EFUSE����IDDQģʽ */
        unsigned int    repair_frm_sram            : 1; /* [3..3] ָʾ�޸�������ԴSRAM��1'b0:1'b1:�޸�������ԴSRAM */
        unsigned int    repair_frm_efu             : 1; /* [4..4] ָʾ�޸�������ԴEFUSE��1'b0:1'b1:�޸�������ԴEFUSE���ź����CRG�����reset_memrep�������߼��������BISR */
        unsigned int    dram_pwr_ctl               : 3; /* [7..5] �����ڲ�˫�˿�RAM POWER */
        unsigned int    efusec_timeout_bypass      : 1; /* [8..8] efusec timeout bypass */
        unsigned int    bbdrx_timeout_bypass       : 1; /* [9..9] bbdrx timeout bypass */
        unsigned int    sleep_mode_cfgbus_bypass   : 1; /* [10..10] 1'b0:sleepmode��Чʱ��ʱ��1'b1:sleepmode��Чʱ����ʱ�� */
        unsigned int    sleep_mode_lpmcu_bypass    : 1; /* [11..11] 1'b0:sleepmode��Чʱ��ʱ��1'b1:sleepmode��Чʱ����ʱ�� */
        unsigned int    sleep_mode_iomcu_bypass    : 1; /* [12..12] 1'b0:sleepmode��Чʱ��ʱ��1'b1:sleepmode��Чʱ����ʱ�� */
        unsigned int    sleep_mode_aobus_bypass    : 1; /* [13..13] 1'b0:sleepmode��Чʱ��ʱ��1'b1:sleepmode��Чʱ����ʱ�� */
        unsigned int    bbp_clk_en                 : 1; /* [14..14] �͸�BBPDRX��ʱ��ʹ���źţ�1'b0:��ʱ��1'b1:��ʱ�� */
        unsigned int    reserved_0                 : 17; /* [31..15] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL3_T;    /* ������ƼĴ���3 */

typedef union
{
    struct
    {
        unsigned int    ddr_ret_en                 : 2; /* [1..0] ����DDRPHY����Retentionģʽ�Ŀ����źţ�д2'b11��Ч�� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL4_T;    /* ������ƼĴ���4 */

typedef union
{
    struct
    {
        unsigned int    usim0_io_sel18             : 1; /* [0..0] USIM��0��ODIO��ѹ�л������ź� */
        unsigned int    usim1_io_sel18             : 1; /* [1..1] USIM��1��ODIO��ѹ�л������ź� */
        unsigned int    sdcard_io_sel18            : 1; /* [2..2] SDCARD��ODIO��ѹ�л��ź� */
        unsigned int    tp_sel                     : 3; /* [5..3] �����źŷ���ѡ����ϸ���������ο���������ĵ� */
        unsigned int    tcxo_mode                  : 1; /* [6..6] �͸�MODEM�ľ������ */
        unsigned int    reserved                   : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL5_T;    /* ������ƼĴ���5 */

typedef union
{
    struct
    {
        unsigned int    peri_io_ret                : 1; /* [0..0] ���������������IO Retetion��0��Retetion������1��Retetionʹ�ܣ� */
        unsigned int    reserved_1                 : 3; /* [3..1] ������ */
        unsigned int    peri_bootio_ret            : 1; /* [4..4] �������������IO Retetion��0��Retetion������1��Retetionʹ�ܣ� */
        unsigned int    peri_bootio_ret_mode       : 1; /* [5..5] �������������IO Retetion����ģʽ��0���ɱ���4������ֵ���ƣ�1����Ӳ���Զ����ƣ� */
        unsigned int    reserved_0                 : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL6_T;    /* ������ƼĴ���6 */

typedef union
{
    struct
    {
        unsigned int    asp_dwaxi_dlock_wr         : 1; /* [0..0] asp��dlock wr״̬ */
        unsigned int    asp_dwaxi_dlock_id         : 4; /* [4..1] asp��dlock id״̬ */
        unsigned int    asp_dwaxi_dlock_slv        : 3; /* [7..5] asp��slave dlock״̬ */
        unsigned int    asp_dwaxi_dlock_mst        : 2; /* [9..8] asp��master dlock״̬ */
        unsigned int    sys_pw_stat                : 4; /* [13..10] ϵͳ����״̬��״̬ */
        unsigned int    tcxoseq_stat0              : 3; /* [16..14] ����0�����߼�״̬��״̬ */
        unsigned int    tcxoseq_stat1              : 3; /* [19..17] ����1�����߼�״̬��״̬ */
        unsigned int    tp_a3_grp                  : 9; /* [28..20] bit[28]:lpram2 ret2n outbit[27]:lpram2 ret1n outbit[26]:lpram2 pgen outbit[25]:lpram1 ret2n outbit[24]:lpram1 ret1n outbit[23]:lpram1 pgen outbit[22]:lpram0 ret2n outbit[21]:lpram0 ret1n outbit[20]:lpram0 pgen out */
        unsigned int    tp_a4_grp0                 : 2; /* [30..29] bit[30]:lpram3 ret2n outbit[29]:lpram3 ret1n out */
        unsigned int    tp_a4_grp1                 : 1; /* [31..31] bit[31]:memrep pgen out */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS0_T;    /* ����״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    err_flag                   : 32; /* [31..0] memory repairģ��errָʾ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS1_T;    /* ����״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    peri_stat2                 : 10; /* [9..0] bit[9]:sclkbit[8]:por_int_nbit[7]:xtal_sw_ackbit[6]:xtal_sw_reqbit[5]:ppll0_enbit[4]:ppll0_lockbit[3]:reset_memrep_nbit[2]:preset_efusec_nbit[1]:pll_sw_reqbit[0]:pll_sw_ack */
        unsigned int    reserved                   : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS2_T;    /* ����״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    efusec_timeout_dbg_info    : 32; /* [31..0] efusec timeout dbg info */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS3_T;    /* ����״̬�Ĵ���3 */

typedef union
{
    struct
    {
        unsigned int    bbdrx_timeout_dbg_info     : 32; /* [31..0] bbdrx_timeout_dbg_info */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS4_T;    /* ����״̬�Ĵ���4 */

typedef union
{
    struct
    {
        unsigned int    deepsleeped                : 1; /* [0..0] ϵͳ�Ƿ��������������״̬����DEEP SLEEPģʽָʾλ��0��ϵͳû�н����DEEP SLEEP״̬��1��ϵͳ���������DEEP SLEEP״̬��û�б����塣���Ըñ���λд1�����λ��״̬����λֵ�� */
        unsigned int    reserved_1                 : 3; /* [3..1] ������ */
        unsigned int    sleeped                    : 1; /* [4..4] ϵͳ�Ƿ����������ϵͳ״̬���� SLEEPģʽָʾλ��0��ϵͳû�н����SLEEP״̬��1��ϵͳ���������SLEEP״̬��û�б����塣���Ըñ���λд1�����λ��״̬����λֵ�� */
        unsigned int    reserved_0                 : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDEEPSLEEPED_T;    /* ����ָʾϵͳ������������˯�ߵ�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    mrb_efuse_busy             : 20; /* [19..0] ����ָʾ����IP�Ƿ����mem repair:bit[19]:MRB19-VENCbit[18]:MRB18-VDECbit[17]:MRB17-MDDRC/MCUbit[16]:MRB16-LTE_BBP_WRAPbit[15]:MRB15-LTE_BBPbit[14]:MRB14-BBP_COMMbit[13]:MRB13-BBE16_WRAPbit[12]:MRB12-MODEM_PERI_WRAPbit[11]:MRB11-ISPbit[10]:MRB10-MALI_SHADERCORE3bit[9]:MRB9-MALI_SHADERCORE2bit[8]:MRB8-MALI_SHADERCORE1bit[7]:MRB7-MALI_SHADERCORE0bit[6]:MRB6-MALI_TOPbit[5]:MRB5-DSS_SDPbit[4]:MRB4-DSS_SUBSYSbit[3]:MRB3-ASP_SUBSYSbit[2]:MRB2-AO_M3_MEMbit[1]:MRB1-A7_CLUSTERbit[0]:MRB0-A15_CLUSTER0������ɣ�1����δ��� */
        unsigned int    reserved                   : 12; /* [31..20] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMRBBUSYSTAT_T;    /* MRB EFUSE BUSY״ָ̬ʾ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    swaddr                     : 32; /* [31..0] �����������ڵ�ַ�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSWADDR_T;    /* ���ڱ��������ڵ�ַ�ļĴ��� */

typedef union
{
    struct
    {
        unsigned int    ddrtrainaddr               : 32; /* [31..0] ����DDRѵ�����ݵĵ�ַ�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDDRADDR_T;    /* ���ڱ���DDRѵ�����ݵĵ�ַ�ļĴ��� */

typedef union
{
    struct
    {
        unsigned int    ddrtraindata               : 32; /* [31..0] ����DDR��ѵ�����ݡ� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDDRDATA_T;    /* ���ڱ���DDRѵ�����ݵļĴ��� */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���0��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA0_T;    /* �������ʹ�õĴ洢���ݼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���1��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA1_T;    /* �������ʹ�õĴ洢���ݼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���2��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA2_T;    /* �������ʹ�õĴ洢���ݼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���3��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA3_T;    /* �������ʹ�õĴ洢���ݼĴ���3 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���4��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA4_T;    /* �������ʹ�õĴ洢���ݼĴ���4 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���5��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA5_T;    /* �������ʹ�õĴ洢���ݼĴ���5 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���6��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA6_T;    /* �������ʹ�õĴ洢���ݼĴ���6 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���7��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA7_T;    /* �������ʹ�õĴ洢���ݼĴ���7 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���8��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA8_T;    /* �������ʹ�õĴ洢���ݼĴ���8 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���9��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA9_T;    /* �������ʹ�õĴ洢���ݼĴ���9 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���10��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA10_T;    /* �������ʹ�õĴ洢���ݼĴ���10 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���11��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA11_T;    /* �������ʹ�õĴ洢���ݼĴ���11 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���12��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA12_T;    /* �������ʹ�õĴ洢���ݼĴ���12 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���13��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA13_T;    /* �������ʹ�õĴ洢���ݼĴ���13 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���14��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA14_T;    /* �������ʹ�õĴ洢���ݼĴ���14 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] �����Ԥ�������ݼĴ���15��������ʱ���ݵĻ��档 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA15_T;    /* �������ʹ�õĴ洢���ݼĴ���15 */

typedef union
{
    struct
    {
        unsigned int    int_wakeup_sys             : 1; /* [0..0] 1���ж���Ч��0���ж���Ч��ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int    drx0_int                   : 1; /* [1..1] 1���ж���Ч��0���ж���Ч��ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int    drx1_int                   : 1; /* [2..2] 1���ж���Ч��0���ж���Ч��ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int    notdrx_int                 : 1; /* [3..3] 1���ж���Ч��0���ж���Ч��ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_GATHER_STAT_T;    /* �ۺϺ���ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    gpio_22_int                : 1; /* [0..0] �ж����μĴ�����0��������Ч��1��������Ч�� */
        unsigned int    gpio_23_int                : 1; /* [1..1]  */
        unsigned int    gpio_24_int                : 1; /* [2..2]  */
        unsigned int    gpio_25_int                : 1; /* [3..3]  */
        unsigned int    gpio_26_int                : 1; /* [4..4]  */
        unsigned int    rtc_int                    : 1; /* [5..5]  */
        unsigned int    rtc1_int                   : 1; /* [6..6]  */
        unsigned int    timer0_int                 : 1; /* [7..7]  */
        unsigned int    timer1_int                 : 1; /* [8..8]  */
        unsigned int    timer2_int                 : 1; /* [9..9]  */
        unsigned int    timer3_int                 : 1; /* [10..10]  */
        unsigned int    timer4_int                 : 1; /* [11..11]  */
        unsigned int    timer5_int                 : 1; /* [12..12]  */
        unsigned int    timer6_int                 : 1; /* [13..13]  */
        unsigned int    timer7_int                 : 1; /* [14..14]  */
        unsigned int    gic_irq_int0               : 1; /* [15..15]  */
        unsigned int    gic_irq_int1               : 1; /* [16..16]  */
        unsigned int    gic_fiq_int2               : 1; /* [17..17]  */
        unsigned int    gic_fiq_int3               : 1; /* [18..18]  */
        unsigned int    lpm3_int                   : 1; /* [19..19]  */
        unsigned int    iom3_int                   : 1; /* [20..20]  */
        unsigned int    asp_ipc_arm_int            : 1; /* [21..21]  */
        unsigned int    drx0_int                   : 1; /* [22..22]  */
        unsigned int    drx1_int                   : 1; /* [23..23]  */
        unsigned int    drx2_int                   : 1; /* [24..24]  */
        unsigned int    drx3_int                   : 1; /* [25..25]  */
        unsigned int    drx4_int                   : 1; /* [26..26]  */
        unsigned int    gpio_27_int                : 1; /* [27..27]  */
        unsigned int    gpio_asp_int               : 1; /* [28..28]  */
        unsigned int    gpio_asp_int_sc            : 1; /* [29..29]  */
        unsigned int    intr_asp_watchdog          : 1; /* [30..30]  */
        unsigned int    lpm3_wfi_int               : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_MASK_T;    /* �ж��������üĴ��� */

typedef union
{
    struct
    {
        unsigned int    gpio_22_int                : 1; /* [0..0] �ж�״̬�Ĵ�����0���ж���Ч��1���ж���Ч�� */
        unsigned int    gpio_23_int                : 1; /* [1..1]  */
        unsigned int    gpio_24_int                : 1; /* [2..2]  */
        unsigned int    gpio_25_int                : 1; /* [3..3]  */
        unsigned int    gpio_26_int                : 1; /* [4..4]  */
        unsigned int    rtc_int                    : 1; /* [5..5]  */
        unsigned int    rtc1_int                   : 1; /* [6..6]  */
        unsigned int    timer0_int                 : 1; /* [7..7]  */
        unsigned int    timer1_int                 : 1; /* [8..8]  */
        unsigned int    timer2_int                 : 1; /* [9..9]  */
        unsigned int    timer3_int                 : 1; /* [10..10]  */
        unsigned int    timer4_int                 : 1; /* [11..11]  */
        unsigned int    timer5_int                 : 1; /* [12..12]  */
        unsigned int    timer6_int                 : 1; /* [13..13]  */
        unsigned int    timer7_int                 : 1; /* [14..14]  */
        unsigned int    gic_int0                   : 1; /* [15..15]  */
        unsigned int    gic_int1                   : 1; /* [16..16]  */
        unsigned int    gic_int2                   : 1; /* [17..17]  */
        unsigned int    gic_int3                   : 1; /* [18..18]  */
        unsigned int    lpm3_int                   : 1; /* [19..19]  */
        unsigned int    iom3_int                   : 1; /* [20..20]  */
        unsigned int    asp_ipc_arm_int            : 1; /* [21..21]  */
        unsigned int    drx0_int                   : 1; /* [22..22]  */
        unsigned int    drx1_int                   : 1; /* [23..23]  */
        unsigned int    drx2_int                   : 1; /* [24..24]  */
        unsigned int    drx3_int                   : 1; /* [25..25]  */
        unsigned int    drx4_int                   : 1; /* [26..26]  */
        unsigned int    gpio_27_int                : 1; /* [27..27]  */
        unsigned int    intr_asp_watchdog          : 1; /* [28..28]  */
        unsigned int    gpio_asp_int               : 1; /* [29..29]  */
        unsigned int    reserved                   : 2; /* [31..30]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_STAT_T;    /* ԭʼ�ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    drx0_int                   : 1; /* [0..0] �ж����üĴ�����0������DRX0���жϣ�1������DRX1���жϣ� */
        unsigned int    drx1_int                   : 1; /* [1..1]  */
        unsigned int    drx2_int                   : 1; /* [2..2]  */
        unsigned int    drx3_int                   : 1; /* [3..3]  */
        unsigned int    drx4_int                   : 1; /* [4..4]  */
        unsigned int    gpio_asp_int               : 1; /* [5..5]  */
        unsigned int    reserved                   : 26; /* [31..6]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDRX_INT_CFG_T;    /* DRX�жϷ������üĴ��� */

typedef union
{
    struct
    {
        unsigned int    lpm3_wfi_int_clr           : 1; /* [0..0] д�������lpm3_wfi_int�жϣ�����������lpm3_wfi_int�ж�״̬ */
        unsigned int    reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T;    /* LPM3 WFI�ж�����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    mali_dbgack_byp            : 1; /* [0..0] 0��bypass��Ч��1��bypass��Ч�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMALIBYPCFG_T;    /* MALI DBGACK BYPASS���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    dapclkoff_sys_n            : 1; /* [0..0] M3 DAPCLKʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    reserved_1                 : 1; /* [1..1] reserved */
        unsigned int    rom_clk_clkoff_sys_n       : 1; /* [2..2] BOOTROM��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    ram_clk_clkoff_sys_n       : 1; /* [3..3] LP_RAM��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    reserved_0                 : 1; /* [4..4] reserved */
        unsigned int    ddrc_clk_clkoff_sys_n      : 1; /* [5..5] DDRC���ýӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    tsen_clk_clkoff_sys_n      : 1; /* [6..6] TSENSORC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    pmc_clk_clkoff_sys_n       : 1; /* [7..7] PMC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    uart_clk_clkoff_sys_n      : 1; /* [8..8] UART��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    i2c_clk_clkoff_sys_n       : 1; /* [9..9] PMU_I2C��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    ssi_clk_clkoff_sys_n       : 1; /* [10..10] PMU_SSI��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    pcrg_clk_clkoff_sys_n      : 1; /* [11..11] ����CRG���ýӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    nandc_clk_clkoff_sys_n     : 1; /* [12..12] NANDC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    wdog_clk_clkoff_sys_n      : 1; /* [13..13] LP_WDG��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    tim_clk_clkoff_sys_n       : 1; /* [14..14] LP_TIMER��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    cssys_clk_clkoff_sys_n     : 1; /* [15..15] CSSYS���ʽӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�� */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdivÿ������λ��ʹ��λ��ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3CLKEN_T;    /* LPM3��ϵͳʱ��ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core��λ������Чʱ���ḴλM3 Core�������߼� */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight ϵͳ�����λ���󣬸�λ���е�coresight��� */
        unsigned int    reserved_2                 : 1; /* [2..2] reserved */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM�ĸ�λ������Чʱ���ḴλBOOTROM�ӿ��߼��� */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM�ĸ�λ������Чʱ���ḴλLP_RAM�ӿ��߼��� */
        unsigned int    reserved_1                 : 1; /* [5..5] reserved */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC���ýӿڵĸ�λ������Чʱ���ḴλDDRC�����ýӿ��߼��� */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC�ĸ�λ������Чʱ���ḴλTSENSORC�����߼��� */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC�ĸ�λ������Чʱ���ḴλPMC�������߼��� */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART�ĸ�λ������Чʱ���ḴλUART�����߼��� */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C�ĸ�λ������Чʱ���ḴλPMU_I2C�����߼��� */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI�ĸ�λ������Чʱ���ḴλPMU_SSI�����߼��� */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] ����CRG���ýӿڵĸ�λ������Чʱ���Ḵλ����CRG�����ýӿ��߼��� */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC�ĸ�λ������Чʱ���ḴλNANDC�����߼��� */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG�ĸ�λ������Чʱ���Ḵλwatchdog�����߼��� */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER�ĸ�λ������Чʱ���Ḵλtimer�����߼��� */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����CSSYS�Ľӿ��߼��� */
        unsigned int    reserved_0                 : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTEN_T;    /* LPM3��ϵͳ��λʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core��λ������Чʱ���ḴλM3 Core�������߼� */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight ϵͳ�����λ���󣬸�λ���е�coresight��� */
        unsigned int    bus_soft_rst_req           : 1; /* [2..2] M3�ڲ����߸�λ������Чʱ���ḴλM3��ϵͳ�ڲ�AHB���߼�APB���ߣ�����Ӧ�豸�� */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM�ĸ�λ������Чʱ���ḴλBOOTROM�ӿ��߼��� */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM�ĸ�λ������Чʱ���ḴλLP_RAM�ӿ��߼��� */
        unsigned int    aon_soft_rst_req           : 1; /* [5..5] AON_SUBSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����AON_SUBSYS�Ľӿ��߼��� */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC���ýӿڵĸ�λ������Чʱ���ḴλDDRC�����ýӿ��߼��� */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC�ĸ�λ������Чʱ���ḴλTSENSORC�����߼��� */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC�ĸ�λ������Чʱ���ḴλPMC�������߼��� */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART�ĸ�λ������Чʱ���ḴλUART�����߼��� */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C�ĸ�λ������Чʱ���ḴλPMU_I2C�����߼��� */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI�ĸ�λ������Чʱ���ḴλPMU_SSI�����߼��� */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] ����CRG���ýӿڵĸ�λ������Чʱ���Ḵλ����CRG�����ýӿ��߼��� */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC�ĸ�λ������Чʱ���ḴλNANDC�����߼��� */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG�ĸ�λ������Чʱ���Ḵλwatchdog�����߼��� */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER�ĸ�λ������Чʱ���Ḵλtimer�����߼��� */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����CSSYS�Ľӿ��߼��� */
        unsigned int    reserved                   : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTDIS_T;    /* LPM3��ϵͳ��λ����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core��λ������Чʱ���ḴλM3 Core�������߼� */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight ϵͳ�����λ���󣬸�λ���е�coresight��� */
        unsigned int    bus_soft_rst_req           : 1; /* [2..2] M3�ڲ����߸�λ������Чʱ���ḴλM3��ϵͳ�ڲ�AHB���߼�APB���ߣ�����Ӧ�豸�� */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM�ĸ�λ������Чʱ���ḴλBOOTROM�ӿ��߼��� */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM�ĸ�λ������Чʱ���ḴλLP_RAM�ӿ��߼��� */
        unsigned int    aon_soft_rst_req           : 1; /* [5..5] AON_SUBSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����AON_SUBSYS�Ľӿ��߼��� */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC���ýӿڵĸ�λ������Чʱ���ḴλDDRC�����ýӿ��߼��� */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC�ĸ�λ������Чʱ���ḴλTSENSORC�����߼��� */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC�ĸ�λ������Чʱ���ḴλPMC�������߼��� */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART�ĸ�λ������Чʱ���ḴλUART�����߼��� */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C�ĸ�λ������Чʱ���ḴλPMU_I2C�����߼��� */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI�ĸ�λ������Чʱ���ḴλPMU_SSI�����߼��� */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] ����CRG���ýӿڵĸ�λ������Чʱ���Ḵλ����CRG�����ýӿ��߼��� */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC�ĸ�λ������Чʱ���ḴλNANDC�����߼��� */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG�ĸ�λ������Чʱ���Ḵλwatchdog�����߼��� */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER�ĸ�λ������Чʱ���Ḵλtimer�����߼��� */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����CSSYS�Ľӿ��߼��� */
        unsigned int    reserved                   : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTSTAT_T;    /* LPM3��ϵͳ��λʹ��״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    boot_remap_en              : 1; /* [0..0] M3����ģʽѡ��0���ӱ���BOOTROM������1����ϵͳNAND���� */
        unsigned int    mpudisable                 : 1; /* [1..1] M3�ڴ汣����Ԫ�����ź� */
        unsigned int    nmi_in                     : 1; /* [2..2] �ⲿ���������ж����� */
        unsigned int    bus_div_clk_sel            : 2; /* [4..3] bus_div_clk��Ƶ��ѡ���ź�00��bus_clk��1��Ƶ01��bus_clk��2��Ƶ10��bus_clk��3��Ƶ11��bus_clk��4��Ƶ */
        unsigned int    sysresetreq_en             : 1; /* [5..5] M3 SYSRESETREQʹ�ܿ��ơ�0��M3�����ϵͳ��λ���󲻻ᱻM3 CRG��Ӧ��1��M3�����ϵͳ��λ����ɱ�M3 CRG��Ӧ�� */
        unsigned int    mem_ctrl_ema_lpram         : 5; /* [10..6] tcm��cache ram��memory�ٶȵ����źš�Bit[4:3]��EMAW��memoryд���ʿ��ơ�Ĭ��ֵ2'b01Bit[2:0]��EMA��memory�����ʿ��ơ�Ĭ��ֵ3'b011 */
        unsigned int    lpm3idle_bypass            : 1; /* [11..11] ϵͳ״̬��LPM3 IDLE�ж�BYPASS���ƣ�1'b1��bypass��Ч1'b0��bypass��Ч */
        unsigned int    reserved_1                 : 12; /* [23..12] ������ */
        unsigned int    reserved_0                 : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3CTRL_T;    /* LPM3��ϵͳ�������üĴ��� */

typedef union
{
    struct
    {
        unsigned int    sysresetreq_sign_out_stat  : 1; /* [0..0] M3 SYSRESETREQ��λ�¼���־������� */
        unsigned int    sleeping                   : 1; /* [1..1] M3 ����״ָ̬ʾ�ź� */
        unsigned int    lockup                     : 1; /* [2..2] M3 core����ָʾ�ź� */
        unsigned int    halted                     : 1; /* [3..3] M3 coreͣ��ָʾ�źţ�debug״̬�� */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3STAT_T;    /* LPM3��ϵͳ״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    lpramctrl_sel              : 1; /* [0..0] lpm3 ram�͹���ģʽ����ѡ��1���������0��״̬������ */
        unsigned int    lpram0_mod                 : 2; /* [2..1] lpm3 ram0�͹���ģʽ���ã�״̬�����ƣ�00/10:retention201:retention111:power-down */
        unsigned int    lpram1_mod                 : 2; /* [4..3] lpm3 ram1�͹���ģʽ���ã�״̬�����ƣ�00/10:retention201:retention111:power-down */
        unsigned int    lpram2_mod                 : 2; /* [6..5] lpm3 ram2�͹���ģʽ���ã�״̬�����ƣ�00/10:retention201:retention111:power-down */
        unsigned int    lpram3_mod                 : 2; /* [8..7] lpm3 ram3�͹���ģʽ���ã�״̬�����ƣ�00/10:retention201:retention111:power-down */
        unsigned int    lpram0ctrl_soft            : 3; /* [11..9] lpm0 ram�͹��Ŀ����ź�������ã�bit9:pgenbit10:ret1nbit11:ret2n */
        unsigned int    lpram1ctrl_soft            : 3; /* [14..12] lpm1 ram�͹��Ŀ����ź�������ã�bit12:pgenbit13:ret1nbit14:ret2n */
        unsigned int    lpram2ctrl_soft            : 3; /* [17..15] lpm2 ram�͹��Ŀ����ź�������ã�bit15:pgenbit16:ret1nbit17:ret2n */
        unsigned int    lpram3ctrl_soft            : 3; /* [20..18] lpm3 ram�͹��Ŀ����ź�������ã�bit18:pgenbit19:ret1nbit20:ret2n */
        unsigned int    memrep_ram_mod             : 2; /* [22..21] memrep ram�͹���ģʽ���ã�״̬�����ƣ�00/10:retention201:retention111:power-down */
        unsigned int    memrep_ramctrl_soft        : 3; /* [25..23] memrep ram�͹��Ŀ����ź�������ã�bit23:pgenbit24:ret1nbit25:ret2n */
        unsigned int    reserved                   : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RAMCTRL_T;    /* LPM3 RAM ���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    g2_gdrx_depsleep_flag      : 1; /* [0..0] ״ָ̬ʾ�źţ�����Ч */
        unsigned int    g1_gdrx_depsleep_flag      : 1; /* [1..1] ״ָ̬ʾ�źţ�����Ч */
        unsigned int    wdrx_deepsleep_flag        : 1; /* [2..2] ״ָ̬ʾ�źţ�����Ч */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT0_T;    /* BBPDRX��ϵͳ״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer         : 32; /* [31..0] ldrx2dbg_abs_timer�ĵ�32bit��(32KHzʱ����ļ���) */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT1_T;    /* BBPDRX��ϵͳ״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer         : 32; /* [31..0] ldrx2dbg_abs_timer�ĸ�32bit��(32KHzʱ����ļ���) */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT2_T;    /* BBPDRX��ϵͳ״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1��������Ч��0��������Ч�� */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1��������Ч��0��������Ч�� */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1��������Ч��0��������Ч�� */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1��������Ч��0��������Ч�� */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1��������Ч��0��������Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCA7_EVENT_MASK_T;    /* A7 EVENT���μĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1��������Ч��0��������Ч�� */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1��������Ч��0��������Ч�� */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1��������Ч��0��������Ч�� */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1��������Ч��0��������Ч�� */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1��������Ч��0��������Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCA15_EVENT_MASK_T;    /* A15 EVENT���μĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1��������Ч��0��������Ч�� */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1��������Ч��0��������Ч�� */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1��������Ч��0��������Ч�� */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1��������Ч��0��������Ч�� */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1��������Ч��0��������Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIOM3_EVENT_MASK_T;    /* IOM3 EVENT���μĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1��������Ч��0��������Ч�� */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1��������Ч��0��������Ч�� */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1��������Ч��0��������Ч�� */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1��������Ч��0��������Ч�� */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1��������Ч��0��������Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3_EVENT_MASK_T;    /* LPM3 EVENT���μĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1��������Ч��0��������Ч�� */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1��������Ч��0��������Ч�� */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1��������Ч��0��������Ч�� */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1��������Ч��0��������Ч�� */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1��������Ч��0��������Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMCPU_EVENT_MASK_T;    /* MCPU EVENT���μĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7_event                   : 1; /* [0..0] 1��event��Ч��0��event��Ч�� */
        unsigned int    a15_event                  : 1; /* [1..1] 1��event��Ч��0��event��Ч�� */
        unsigned int    iom3_event                 : 1; /* [2..2] 1��event��Ч��0��event��Ч�� */
        unsigned int    lpm3_event                 : 1; /* [3..3] 1��event��Ч��0��event��Ч�� */
        unsigned int    mcpu_event                 : 1; /* [4..4] 1��event��Ч��0��event��Ч�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEVENT_STAT_T;    /* EVENT״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    processor_jtag_sel         : 1; /* [0..0] 1��DSP jtag,function pins useless0��coresight jtag ,DSP on function pins */
        unsigned int    dsp_jtag_sel               : 2; /* [2..1] 10��hifi dsp��JTAG01��bbp dsp��JTAG00��jtag����������hifi dsp->bbp dsp */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCJTAG_SEL_T;    /* JTAGѡ����ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    modem_key0                 : 32; /* [31..0] modem_key0 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY0_T;    /* MODEM_KEY0 */

typedef union
{
    struct
    {
        unsigned int    modem_key1                 : 32; /* [31..0] modem_key1 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY1_T;    /* MODEM_KEY1 */

typedef union
{
    struct
    {
        unsigned int    modem_key2                 : 32; /* [31..0] modem_key2 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY2_T;    /* MODEM_KEY2 */

typedef union
{
    struct
    {
        unsigned int    modem_key3                 : 32; /* [31..0] modem_key3 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY3_T;    /* MODEM_KEY3 */

typedef union
{
    struct
    {
        unsigned int    cfg_djtag                  : 1; /* [0..0] 1��djtag disable0��normalдһ��������������֤ͨ�������ݲ���д�벢��ֻ�е�efuse_djtag_ctrlΪ2'b01ʱ��cfg_djtag�������djtag_disable */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCFG_DJTAG_T;    /* DJTAG���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    a7cp15disable0             : 1; /* [0..0] A7 CPU0�Ŀ���bit��д1������CPU0��λ�����ؽ��� */
        unsigned int    a7cp15disable1             : 1; /* [1..1] A7 CPU1�Ŀ���bit��д1������CPU1��λ�����ؽ��� */
        unsigned int    a7cp15disable2             : 1; /* [2..2] A7 CPU2�Ŀ���bit��д1������CPU2��λ�����ؽ��� */
        unsigned int    a7cp15disable3             : 1; /* [3..3] A7 CPU3�Ŀ���bit��д1������CPU3��λ�����ؽ��� */
        unsigned int    a15cp15disable0            : 1; /* [4..4] A15 CPU0�Ŀ���bit��д1������CPU0��λ�����ؽ��� */
        unsigned int    a15cp15disable1            : 1; /* [5..5] A15 CPU1�Ŀ���bit��д1������CPU1��λ�����ؽ��� */
        unsigned int    a15cp15disable2            : 1; /* [6..6] A15 CPU2�Ŀ���bit��д1������CPU2��λ�����ؽ��� */
        unsigned int    a15cp15disable3            : 1; /* [7..7] A15 CPU3�Ŀ���bit��д1������CPU3��λ�����ؽ��� */
        unsigned int    a9cp15disable              : 1; /* [8..8] A9 CPU�Ŀ���bit��д1������CPU��λ�����ؽ��� */
        unsigned int    gicdisable                 : 1; /* [9..9] GIC�Ŀ���bit��д1������GIC��λ�����ؽ��� */
        unsigned int    reserved                   : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCP15_DISABLE_T;    /* CP15DISABLE���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    cnt_stat                   : 16; /* [15..0] clk_monitorģ��ʱ�Ӽ���״̬�Ĵ�������clk_cnt_en = 1'b1����32KHz˯��ʱ���������½���ʱ���£��������ά�ֲ��䡣 */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKCNTSTAT_T;    /* ʱ�Ӽ���״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cnt_cfg                    : 16; /* [15..0] clk_monitorģ��ʱ�Ӽ������üĴ����� */
        unsigned int    timer_secu_en              : 1; /* [16..16] AO��TIMER2��ȫ���ƣ�ʹ��ʱtimer2��ʱ����Ч����λ���룬timer_clk_en2Ϊ32KHZʱ��0����ȫ���Ʋ�ʹ��1����ȫ����ʹ�� */
        unsigned int    reserved                   : 13; /* [29..17] ������ */
        unsigned int    clk_cnt_en                 : 1; /* [30..30] clk_cntʹ�����á�0����ʹ��1��ʹ�� */
        unsigned int    clk_monitor_en             : 1; /* [31..31] clk_monitorģ��ʹ�����á�0����ʹ��1��ʹ��ע��Ҫ������cnt_cfg[15:0]��������clk_monitor_en�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKCNTCFG_T;    /* ʱ�Ӽ������üĴ��� */

typedef union
{
    struct
    {
        unsigned int    intr_clr                   : 1; /* [0..0] �ж����0�������ж�1�����ж�ע��д1֮��Ҫ��д0�������һֱ�������жϵ�״̬�� */
        unsigned int    intr_mask                  : 1; /* [1..1] �ж�����0���������ж�1�������ж� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKMONCTRL_T;    /* ʱ�Ӽ�ؿ��ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    raw_intr                   : 1; /* [0..0] �ж�ָʾ0�����ж�1�����ж� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKMONINT_T;    /* ʱ�Ӽ���ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cfg_arm_dbgen              : 4; /* [3..0] ARM debugen���á�����ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��дһ�Ρ��� */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCFG_ARM_DBGEN_T;    /* ARM debug en���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    arm_dbg_key0               : 32; /* [31..0] arm_dbg_key�ĵ�32λ������ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��д3�Ρ��� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBG_KEY0_T;    /* ARM debug key0���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    arm_dbg_key1               : 32; /* [31..0] arm_dbg_key�ĸ�32λ������ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��д3�Ρ��� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBG_KEY1_T;    /* ARM debug key1���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    arm_dbgen_wr               : 1; /* [0..0] ARM debugen wr״̬�Ĵ�����0����ǰ����дcfg_arm_dbgen�Ĵ�����1����ǰ��дcfg_arm_dbgen�Ĵ����� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBGEN_STAT_T;    /* ARM debug en״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    sys_efuse_pad_sel          : 1; /* [0..0] 0��PAD��д��1�������д�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEFUSECTRL_T;    /* EFUSE PAD��д���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    gt_clk_ao_cc_secs          : 1; /* [0..0] aocc/secsʱ���ſؿ��ƣ�0��IPʱ�ӽ�ֹ��1��IPʱ��ʹ�ܡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEFUSESEL_T;    /* AOCC/SECSʱ���ſؼĴ��� */

typedef union
{
    struct
    {
        unsigned int    security_n                 : 1; /* [0..0] ����оƬ��ȫ�ȼ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSECURITYSTAT_T;    /* EFUSE SECURITY״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    chip_id0                   : 32; /* [31..0] CHIP_ID��32bit */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCHIP_ID0_T;    /* EFUSE CHIP_ID0�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    chip_id1                   : 32; /* [31..0] CHIP_ID��32bit */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCHIP_ID1_T;    /* EFUSE CHIP_ID1�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    version_code               : 16; /* [15..0] 0x0100��оƬ�İ汾�š� */
        unsigned int    chip_code                  : 16; /* [31..16] 0x3630��оƬ�ı�� */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSOCID0_T;    /* SOCID�Ĵ���0 */


/********************************************************************************/
/*    AP_SCTRL ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_ap_sctrl_scctrl_modectrl,modectrl,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_modestatus,modestatus,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeforcehigh,timeforcehigh,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0sel,timeren0sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0ov,timeren0ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1sel,timeren1sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1ov,timeren1ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2sel,timeren2sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2ov,timeren2ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3sel,timeren3sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3ov,timeren3ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4sel,timeren4sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4ov,timeren4ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5sel,timeren5sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5ov,timeren5ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6sel,timeren6sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6ov,timeren6ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7sel,timeren7sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7ov,timeren7ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_deepsleepen,deepsleepen,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reset_source,reset_source,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reserved,reserved,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmden,itmden,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmdctrl,itmdctrl,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_inmdtype,inmdtype,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_itmdstat,itmdstat,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_reserved,reserved,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxopresel_apb,tcxopresel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxohardcon_bypass,tcxohardcon_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosel_apb,tcxosel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosoft_apb,tcxosoft_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_defau_tcxo,defau_tcxo,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl0,tcxofast_ctrl0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl1,tcxofast_ctrl1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen1_apb,ctrlen1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel1_apb,ctrlsel1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen0_apb,ctrlen0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel0_apb,ctrlsel0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass0,timeout_bypass0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass1,timeout_bypass1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq_bypass,tcxoseq_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq0_time,tcxoseq0_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq1_time,tcxoseq1_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_reserved,reserved,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout0_timeoutcnt0_apb,timeoutcnt0_apb,HI_AP_SCTRL_SCXTALTIMEOUT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout1_timeoutcnt1_apb,timeoutcnt1_apb,HI_AP_SCTRL_SCXTALTIMEOUT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en0,tcxo_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en1,tcxo_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout1,tcxo_timeout1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout0,tcxo_timeout0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en1,sysclk_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en0,sysclk_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_sel,sysclk_sel,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl0,clkgt_ctrl0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl1,clkgt_ctrl1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl,clkgt_ctrl,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en0,abbbuf_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en1,abbbuf_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish0,tcxoseq_finish0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish1,tcxoseq_finish1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_reserved,reserved,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_en,ppll0_en,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_bp,ppll0_bp,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_refdiv,ppll0_refdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_fbdiv,ppll0_fbdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv1,ppll0_postdiv1,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv2,ppll0_postdiv2,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_fracdiv,ppll0_fracdiv,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_int_mod,ppll0_int_mod,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_cfg_vld,ppll0_cfg_vld,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_gt_clk_ppll0,gt_clk_ppll0,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_reset,ppll0_ssc_reset,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_disable,ppll0_ssc_disable,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_downspread,ppll0_ssc_downspread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_spread,ppll0_ssc_spread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_divval,ppll0_ssc_divval,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_reserved,reserved,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_pllstat,pllstat,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_reserved,reserved,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_reserved,reserved,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_reserved,reserved,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ao_cc,gt_clk_ao_cc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_reserved,reserved,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_reserved,reserved,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_reserved,reserved,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_asp_subsys_div,swdone_clk_asp_subsys_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_sci_div,swdone_clk_sci_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_aobus_div,swdone_clk_aobus_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2sys,aobusclksw2sys,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2pll,aobusclksw2pll,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen2_reserved,reserved,HI_AP_SCTRL_SCPEREN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis2_reserved,reserved,HI_AP_SCTRL_SCPERDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken2_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat2_reserved,reserved,HI_AP_SCTRL_SCPERSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten1_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis1_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat1_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten2_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis2_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat2_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc_bypass,rst_gt_rtc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc1_bypass,rst_gt_rtc1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer0_bypass,rst_gt_timer0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer1_bypass,rst_gt_timer1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer2_bypass,rst_gt_timer2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer3_bypass,rst_gt_timer3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio0_bypass,rst_gt_gpio0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio1_bypass,rst_gt_gpio1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio2_bypass,rst_gt_gpio2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio3_bypass,rst_gt_gpio3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio4_bypass,rst_gt_gpio4_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio5_bypass,rst_gt_gpio5_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_ioc_bypass,rst_gt_ioc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_syscnt_bypass,rst_gt_syscnt_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci0_bypass,rst_gt_sci0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci1_bypass,rst_gt_sci1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_bbpdrx_bypass,rst_gt_bbpdrx_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_efusec_bypass,rst_gt_efusec_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_reserved,reserved,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_audioisoen,audioisoen,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_reserved,reserved,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_audioisoen,audioisoen,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_reserved,reserved,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_audioisoen,audioisoen,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_reserved,reserved,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_audiopwren,audiopwren,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_reserved,reserved,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_audiopwren,audiopwren,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_reserved,reserved,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_audiopwrstat,audiopwrstat,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_reserved,reserved,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_audiopwrack,audiopwrack,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_reserved,reserved,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_peri_pwr_down_time,peri_pwr_down_time,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_reserved,reserved,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_peri_pwr_up_time,peri_pwr_up_time,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_reserved,reserved,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_asp_subsys,sc_div_asp_subsys,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_hifidsp,sc_div_hifidsp,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_sci,sc_div_sci,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_reserved,reserved,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_extclk_en,extclk_en,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sc_div_aobus,sc_div_aobus,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout0_tcxo,div_clkout0_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout1_tcxo,div_clkout1_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout0,sel_clkout0,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout1,sel_clkout1,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_hifidsp_clk_div,gt_hifidsp_clk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_sci,gt_clk_sci,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_asp_hclk_div,gt_asp_hclk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_1,reserved_1,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_sc_div_asp_hclk,sc_div_asp_hclk,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_0,reserved_0,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_reserved,reserved,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_reserved,reserved,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_reserved,reserved,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efusec_mem_ctrl,efusec_mem_ctrl,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efuse_remap,efuse_remap,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_reserved,reserved,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl1_reserved,reserved,HI_AP_SCTRL_SCPERCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_repair_disable,repair_disable,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_jtaq_to_sdcard,jtaq_to_sdcard,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reset_memrep_msk,reset_memrep_msk,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_iddq,repair_iddq,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_sram,repair_frm_sram,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_efu,repair_frm_efu,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_dram_pwr_ctl,dram_pwr_ctl,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_efusec_timeout_bypass,efusec_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbdrx_timeout_bypass,bbdrx_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_cfgbus_bypass,sleep_mode_cfgbus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_lpmcu_bypass,sleep_mode_lpmcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_iomcu_bypass,sleep_mode_iomcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_aobus_bypass,sleep_mode_aobus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbp_clk_en,bbp_clk_en,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_ddr_ret_en,ddr_ret_en,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_reserved,reserved,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim0_io_sel18,usim0_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim1_io_sel18,usim1_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_sdcard_io_sel18,sdcard_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tp_sel,tp_sel,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tcxo_mode,tcxo_mode,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_reserved,reserved,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_io_ret,peri_io_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret,peri_bootio_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret_mode,peri_bootio_ret_mode,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_wr,asp_dwaxi_dlock_wr,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_id,asp_dwaxi_dlock_id,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_slv,asp_dwaxi_dlock_slv,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_mst,asp_dwaxi_dlock_mst,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_sys_pw_stat,sys_pw_stat,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat0,tcxoseq_stat0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat1,tcxoseq_stat1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a3_grp,tp_a3_grp,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp0,tp_a4_grp0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp1,tp_a4_grp1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus1_err_flag,err_flag,HI_AP_SCTRL_SCPERSTATUS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_peri_stat2,peri_stat2,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_reserved,reserved,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus3_efusec_timeout_dbg_info,efusec_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus4_bbdrx_timeout_dbg_info,bbdrx_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_deepsleeped,deepsleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_1,reserved_1,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_sleeped,sleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_0,reserved_0,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_mrb_efuse_busy,mrb_efuse_busy,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_reserved,reserved,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scswaddr_swaddr,swaddr,HI_AP_SCTRL_SCSWADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSWADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddraddr_ddrtrainaddr,ddrtrainaddr,HI_AP_SCTRL_SCDDRADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddrdata_ddrtraindata,ddrtraindata,HI_AP_SCTRL_SCDDRDATA_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRDATA_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata0_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata1_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata2_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata3_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata4_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata5_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata6_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata7_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA7_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA7_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata8_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA8_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA8_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata9_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA9_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA9_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata10_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA10_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA10_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata11_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA11_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA11_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata12_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA12_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA12_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata13_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA13_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA13_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata14_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA14_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA14_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata15_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA15_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA15_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_int_wakeup_sys,int_wakeup_sys,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_notdrx_int,notdrx_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_reserved,reserved,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int0,gic_irq_int0,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int1,gic_irq_int1,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int2,gic_fiq_int2,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int3,gic_fiq_int3,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int_sc,gpio_asp_int_sc,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_wfi_int,lpm3_wfi_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int0,gic_int0,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int1,gic_int1,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int2,gic_int2,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int3,gic_int3,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_reserved,reserved,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx0_int,drx0_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx1_int,drx1_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx2_int,drx2_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx3_int,drx3_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx4_int,drx4_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_reserved,reserved,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_lpm3_wfi_int_clr,lpm3_wfi_int_clr,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_reserved,reserved,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_mali_dbgack_byp,mali_dbgack_byp,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_reserved,reserved,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_dapclkoff_sys_n,dapclkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_rom_clk_clkoff_sys_n,rom_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ram_clk_clkoff_sys_n,ram_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ddrc_clk_clkoff_sys_n,ddrc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tsen_clk_clkoff_sys_n,tsen_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pmc_clk_clkoff_sys_n,pmc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_uart_clk_clkoff_sys_n,uart_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_i2c_clk_clkoff_sys_n,i2c_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ssi_clk_clkoff_sys_n,ssi_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pcrg_clk_clkoff_sys_n,pcrg_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_nandc_clk_clkoff_sys_n,nandc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_wdog_clk_clkoff_sys_n,wdog_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tim_clk_clkoff_sys_n,tim_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_cssys_clk_clkoff_sys_n,cssys_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_2,reserved_2,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_boot_remap_en,boot_remap_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mpudisable,mpudisable,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_nmi_in,nmi_in,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_bus_div_clk_sel,bus_div_clk_sel,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_sysresetreq_en,sysresetreq_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mem_ctrl_ema_lpram,mem_ctrl_ema_lpram,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_lpm3idle_bypass,lpm3idle_bypass,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sysresetreq_sign_out_stat,sysresetreq_sign_out_stat,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sleeping,sleeping,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_lockup,lockup,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_halted,halted,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_reserved,reserved,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpramctrl_sel,lpramctrl_sel,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0_mod,lpram0_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1_mod,lpram1_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2_mod,lpram2_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3_mod,lpram3_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0ctrl_soft,lpram0ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1ctrl_soft,lpram1ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2ctrl_soft,lpram2ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3ctrl_soft,lpram3ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ram_mod,memrep_ram_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ramctrl_soft,memrep_ramctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_reserved,reserved,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g2_gdrx_depsleep_flag,g2_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g1_gdrx_depsleep_flag,g1_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_wdrx_deepsleep_flag,wdrx_deepsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_reserved,reserved,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat1_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat2_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_reserved,reserved,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_reserved,reserved,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_reserved,reserved,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_reserved,reserved,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_reserved,reserved,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a7_event,a7_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a15_event,a15_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_iom3_event,iom3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_lpm3_event,lpm3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_mcpu_event,mcpu_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_reserved,reserved,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_processor_jtag_sel,processor_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_dsp_jtag_sel,dsp_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_reserved,reserved,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key0_modem_key0,modem_key0,HI_AP_SCTRL_SCMODEM_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key1_modem_key1,modem_key1,HI_AP_SCTRL_SCMODEM_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key2_modem_key2,modem_key2,HI_AP_SCTRL_SCMODEM_KEY2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key3_modem_key3,modem_key3,HI_AP_SCTRL_SCMODEM_KEY3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY3_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_cfg_djtag,cfg_djtag,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_reserved,reserved,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable0,a7cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable1,a7cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable2,a7cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable3,a7cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable0,a15cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable1,a15cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable2,a15cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable3,a15cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a9cp15disable,a9cp15disable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_gicdisable,gicdisable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_reserved,reserved,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_cnt_stat,cnt_stat,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_reserved,reserved,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_cnt_cfg,cnt_cfg,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_timer_secu_en,timer_secu_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_reserved,reserved,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_cnt_en,clk_cnt_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_monitor_en,clk_monitor_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_clr,intr_clr,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_mask,intr_mask,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_reserved,reserved,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_raw_intr,raw_intr,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_reserved,reserved,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_cfg_arm_dbgen,cfg_arm_dbgen,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_reserved,reserved,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key0_arm_dbg_key0,arm_dbg_key0,HI_AP_SCTRL_SCARM_DBG_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key1_arm_dbg_key1,arm_dbg_key1,HI_AP_SCTRL_SCARM_DBG_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_arm_dbgen_wr,arm_dbgen_wr,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_reserved,reserved,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_sys_efuse_pad_sel,sys_efuse_pad_sel,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_reserved,reserved,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_gt_clk_ao_cc_secs,gt_clk_ao_cc_secs,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_reserved,reserved,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_security_n,security_n,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_reserved,reserved,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id0_chip_id0,chip_id0,HI_AP_SCTRL_SCCHIP_ID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id1_chip_id1,chip_id1,HI_AP_SCTRL_SCCHIP_ID1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_version_code,version_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_chip_code,chip_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)

#endif // __HI_AP_SCTRL_H__

