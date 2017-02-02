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

#ifndef __HI_EMI_H__
#define __HI_EMI_H__

/*
 * Project: hi
 * Module : emi
 */

#ifndef HI_SET_GET

#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif



/********************************************************************************/
/*    emi �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_EMI_SMBIDCYR0_OFFSET                           (0x0) /* Bank0��תʱ��Ĵ����� */
#define    HI_EMI_SMBWST1R0_OFFSET                           (0x4) /* Bank0�����ʵȴ�ʱ��Ĵ����� */
#define    HI_EMI_SMBWST2R0_OFFSET                           (0x8) /* Bank0д���ʵȴ�ʱ��Ĵ����� */
#define    HI_EMI_SMBWSTOENR0_OFFSET                         (0xC) /* Bank0��ʹ���ӳ�ʱ��Ĵ����� */
#define    HI_EMI_SMBWSTWENR0_OFFSET                         (0x10) /* Bank0дʹ���ӳ�ʱ��Ĵ����� */
#define    HI_EMI_SMBCR0_OFFSET                              (0x14) /* Bank0���ƼĴ����� */
#define    HI_EMI_SMBSR0_OFFSET                              (0x18) /* Bank0״̬�Ĵ����� */

/********************************************************************************/
/*    emi �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    idcy                       : 4; /* [3..0] ����ֶο��������߶����ʺ�д����֮�����ĵȴ�������Ŀ������ĵȴ�����ʱ��Ϊ(idcy+1)*Thclk�� */
        unsigned int    updlyr_l                   : 7; /* [10..4] ���ƶ�״̬PREB�ź�0���1���CS���ӳ٣��ӳ�ʱ��Ϊ(updlyr)*Thclk����7bitΪupdlyr�ĵ�λ���ء� */
        unsigned int    dwndlyr_l                  : 7; /* [17..11] ���ƶ�״̬PREB�ź�1���0���CS���ӳ٣��ӳ�ʱ��Ϊ(dwndlyr+1)*Thclk����7bitΪdwndlyr�ĵ�λ���ء� */
        unsigned int    updlyw_l                   : 7; /* [24..18] ����д״̬PREB�ź�0���1���CS���ӳ٣��ӳ�ʱ��Ϊ(updlyw)*Thclk����7bitΪupdlyw�ĵ�λ���ء� */
        unsigned int    dwndlyw_l                  : 7; /* [31..25] ����д״̬PREB�ź�1���0���CS���ӳ٣��ӳ�ʱ��Ϊ(dwndlyw+1)*Thclk����7bitΪdwndlyw�ĵ�λ���ء� */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBIDCYR0_T;    /* Bank0��תʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    wst1                       : 10; /* [9..0] Wait State 1���ֶο��������߶����ʵȴ�״̬����Ŀ��Wait state time=wst1*Thclk�� */
        unsigned int    updlyr_h                   : 3; /* [12..10] ���ƶ�״̬PREB�ź�0���1���CS���ӳ٣��ӳ�ʱ��Ϊ(updlyr)*Thclk����3bitΪupdlyr�ĸ�λ���ء� */
        unsigned int    dwndlyr_h                  : 3; /* [15..13] ���ƶ�״̬PREB�ź�1���0���CS���ӳ٣��ӳ�ʱ��Ϊ(dwndlyr+1)*Thclk����3bitΪdwndlyr�ĸ�λ���ء� */
        unsigned int    updlyw_h                   : 3; /* [18..16] ����д״̬PREB�ź�0���1���CS���ӳ٣��ӳ�ʱ��Ϊ(updlyw)*Thclk����3bitΪupdlyw�ĸ�λ���ء� */
        unsigned int    dwndlyw_h                  : 3; /* [21..19] ����д״̬PREB�ź�1���0���CS���ӳ٣��ӳ�ʱ��Ϊ(dwndlyw+1)*Thclk����3bitΪdwndlyw�ĸ�λ���ء� */
        unsigned int    reserved                   : 10; /* [31..22] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWST1R0_T;    /* Bank0�����ʵȴ�ʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    wst2                       : 10; /* [9..0] Wait State 2���ֶο���������д���ʵȴ�״̬����Ŀ��Wait state time=wst2*Thclk�� */
        unsigned int    reserved_1                 : 6; /* [15..10] ������ */
        unsigned int    wst3                       : 8; /* [23..16] Wait State 3���ֶο��������ζ����ʼ��������д���ʼ����ĵȴ���������Wait state time=wst3*Thclk�� */
        unsigned int    reserved_0                 : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWST2R0_T;    /* Bank0д���ʵȴ�ʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    wstoen                     : 4; /* [3..0] ��ʹ����Ч�����Ƭѡ��Ч���ӳ����ڿ��ơ�Output Enable Delay time=wstoen*Thclk�� */
        unsigned int    oendisable                 : 1; /* [4..4] Ϊ1��ʱ�򣬶�ʹ���ź�ʼ��Ϊ�ߣ�Ϊ0��ʱ���ʹ���ź���Ч������WSTOEN���ñ仯�� */
        unsigned int    oendly                     : 2; /* [6..5] ��ʹ����Ч�źŵ�Ƭѡ��Ч�źŵ��ӳ٣�oendly*Thclk�� */
        unsigned int    reserved                   : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWSTOENR0_T;    /* Bank0��ʹ���ӳ�ʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    wstwen                     : 4; /* [3..0] дʹ����Ч�����Ƭѡ��Ч���ӳ����ڿ��ơ�Write Enable Delay time=wstwen*Thclk�� */
        unsigned int    wendly                     : 2; /* [5..4] дʹ����Ч�����Ƭѡ��Ч���ӳ����ڿ��ơ�Write Enable Delay time=wendly*Thclk�� */
        unsigned int    wenclocksel                : 1; /* [6..6] д�����ź��������ʱ�ӱ���ѡ��0���½��أ�1�������ء�<B>˵����Hi6755��ֻ������Ϊ�����Ӳ�������������</B> */
        unsigned int    ebictrl                    : 1; /* [7..7] Ϊ1ʱ��ģ��EBI�ӿڣ���GRANT�ź���REQ�ź��У��ޣ�Чһ��ʱ�����ں��У��ޣ�Ч�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWSTWENR0_T;    /* Bank0дʹ���ӳ�ʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rble                       : 1; /* [0..0] Read bye lane enable��0��nSMBL[1:0]�ڶ�����ȫ��������ȫ��Ϊ�ߡ���������������8bit��������һ��bank��bye lane enable�źű����ӵ�Memory������дʹ�ܣ������ڶ�������ʱ�����Ϊ�ߣ�1��nSMBL[1:0]�ڶ�����ȫ��������ȫ��Ϊ�͡���������������16bit��������һ��bank���ֿ���дʹ�ܣ�nSMWEN����ʹ�ã�bye lane enable�ź��ڶ��Ĺ����б��뱻hold�������ڶ�������ʱ�����Ϊ�ߡ����ϵͳ���ϵ�󣬴�Bank1 boot��remapΪ1����RBLE��������pin SMRBLECS1������ */
        unsigned int    cspol                      : 1; /* [1..1] Ƭѡ�źż���ѡ���źš�0��Ƭѡ�źŵ���Ч��1��Ƭѡ�źŸ���Ч��������������ʹ����Ƭѡ�ź�������һ��Ҫȷ����λ����ȷ���á��������ȷ�ļ��Ա����ã�������������������������� */
        unsigned int    wp                         : 1; /* [2..2] ����д����ʹ�ܡ�0��û��д������1��������д������ */
        unsigned int    mw                         : 2; /* [4..3] ���Memory��ȡ�00��8bit��01��16bit��10��������11�������� */
        unsigned int    addr_cnt                   : 1; /* [5..5] ������Ϊ1ʱ�������16bit��bank��bit[0]������ֵ�ַ��16bit����������Ϊ0��ʱ�������16bit��bank��bit[1]������ֵ�ַ��16bit���� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBCR0_T;    /* Bank0���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hsizeerr                   : 1; /* [0..0] Bus transfer size����״̬��־���Ӹ�λ����0��No error��1��Bus transfer size�������λд��0����Ч��1����д����״̬��־�� */
        unsigned int    writeproerr                : 1; /* [1..1] д��������״̬��־���Ӹ�λ����0��No error��1��д�����������λд��0����Ч��1����д����״̬��־�� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBSR0_T;    /* Bank0״̬�Ĵ����� */


/********************************************************************************/
/*    emi ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_emi_smbidcyr0_idcy,idcy,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyr_l,updlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyr_l,dwndlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyw_l,updlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyw_l,dwndlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_wst1,wst1,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyr_h,updlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyr_h,dwndlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyw_h,updlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyw_h,dwndlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_reserved,reserved,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst2,wst2,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_1,reserved_1,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst3,wst3,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_0,reserved_0,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_wstoen,wstoen,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendisable,oendisable,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendly,oendly,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_reserved,reserved,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wstwen,wstwen,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wendly,wendly,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wenclocksel,wenclocksel,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_ebictrl,ebictrl,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_reserved,reserved,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_rble,rble,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_cspol,cspol,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_wp,wp,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_mw,mw,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_addr_cnt,addr_cnt,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_reserved,reserved,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_hsizeerr,hsizeerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_writeproerr,writeproerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_reserved,reserved,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)

#endif // __HI_EMI_H__

