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
#ifndef __HI_AMON_H__
#define __HI_AMON_H__

#include <hi_base.h>
/*
 * Project: hi
 * Module : amon
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    amon �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_AMON_CNT_RESET_OFFSET                          (0x0) /* CNT_RESET��axi monitor���м���������λ�Ĵ����� */
#define    HI_AMON_CNT_CTRL_OFFSET                           (0x4) /* CNT_CTRL��axi monitor��ϵͳ���üĴ����� */
#define    HI_AMON_CNT_STATE_INT_OFFSET                      (0x8) /* CNT_STATE_INT��axi monitor��ϵͳ״̬�Ĵ����� */
#define    HI_AMON_WIN_COUNTER_OFFSET                        (0xC) /* WIN_COUNTER��axi monitor��ϵͳʱ�䴰�������� */
#define    HI_AMON_IDLE_COUNTER_OFFSET                       (0x14) /* IDLE_COUNTER��axi monitor��ϵͳidleͳ�Ƽ������� */
#define    HI_AMON_PORT_SEL_OFFSET                           (0x1C) /* CNT_PORT_SEL��axi_monitor�ļ��IDѡ���ĸ�AXI PORT */
#define    HI_AMON_INT_CLR_OFFSET                            (0x20) /* INT_CLR��axi_monitor���ж�����Ĵ��� */
#define    HI_AMON_ID_INT_SRC_OFFSET                         (0x24) /* ID����д����ж�ԭʼ�Ĵ��� */
#define    HI_AMON_ID_INT_MASK_OFFSET                        (0x28) /* ID����д����ж����γ��Ĵ��� */
#define    HI_AMON_ID_INT_STAT_OFFSET                        (0x2C) /* ID����д����ж�״̬�Ĵ��� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_0_OFFSET              (0x30) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_1_OFFSET              (0x40) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_2_OFFSET              (0x50) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_3_OFFSET              (0x60) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_4_OFFSET              (0x70) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_5_OFFSET              (0x80) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_6_OFFSET              (0x90) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_RD_WAIT_CYCLE_PORTS_7_OFFSET              (0xA0) /* RD_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_0_OFFSET              (0x38) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_1_OFFSET              (0x48) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_2_OFFSET              (0x58) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_3_OFFSET              (0x68) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_4_OFFSET              (0x78) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_5_OFFSET              (0x88) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_6_OFFSET              (0x98) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_WR_WAIT_CYCLE_PORTS_7_OFFSET              (0xA8) /* WR_WAIT_CYCLE_PORT�Ǽ��PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ����� */
#define    HI_AMON_CNT_TYPE_0_OFFSET                         (0xB0) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_1_OFFSET                         (0xB4) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_2_OFFSET                         (0xB8) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_3_OFFSET                         (0xBC) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_4_OFFSET                         (0xC0) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_5_OFFSET                         (0xC4) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_6_OFFSET                         (0xC8) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_TYPE_7_OFFSET                         (0xCC) /* CNT_TYPE�Ǽ��ID�ļ������������ѡ�� */
#define    HI_AMON_CNT_ID_0_OFFSET                           (0x100) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_1_OFFSET                           (0x200) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_2_OFFSET                           (0x300) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_3_OFFSET                           (0x400) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_4_OFFSET                           (0x500) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_5_OFFSET                           (0x600) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_6_OFFSET                           (0x700) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CNT_ID_7_OFFSET                           (0x800) /* CNT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_ID_ADDR_DES_0_OFFSET                      (0x104) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_1_OFFSET                      (0x204) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_2_OFFSET                      (0x304) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_3_OFFSET                      (0x404) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_4_OFFSET                      (0x504) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_5_OFFSET                      (0x604) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_6_OFFSET                      (0x704) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_7_OFFSET                      (0x804) /* ID_ADDR_DES��axi monitorϵͳϣ����صĵ�ַ��Ϣ�±߽� */
#define    HI_AMON_ID_ADDR_DES_M_0_OFFSET                    (0x108) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_1_OFFSET                    (0x208) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_2_OFFSET                    (0x308) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_3_OFFSET                    (0x408) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_4_OFFSET                    (0x508) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_5_OFFSET                    (0x608) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_6_OFFSET                    (0x708) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_ID_ADDR_DES_M_7_OFFSET                    (0x808) /* ID_ADDR_DES_M��axi monitorϵͳϣ����صĵ�ַ��Ϣ�ϱ߽� */
#define    HI_AMON_INCR1_ID_0_OFFSET                         (0x110) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_1_OFFSET                         (0x210) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_2_OFFSET                         (0x310) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_3_OFFSET                         (0x410) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_4_OFFSET                         (0x510) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_5_OFFSET                         (0x610) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_6_OFFSET                         (0x710) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR1_ID_7_OFFSET                         (0x810) /* INCR1_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR1������������ */
#define    HI_AMON_INCR2_ID_0_OFFSET                         (0x118) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_1_OFFSET                         (0x218) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_2_OFFSET                         (0x318) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_3_OFFSET                         (0x418) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_4_OFFSET                         (0x518) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_5_OFFSET                         (0x618) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_6_OFFSET                         (0x718) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR2_ID_7_OFFSET                         (0x818) /* INCR2_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR2������������ */
#define    HI_AMON_INCR4_ID_0_OFFSET                         (0x120) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_1_OFFSET                         (0x220) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_2_OFFSET                         (0x320) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_3_OFFSET                         (0x420) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_4_OFFSET                         (0x520) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_5_OFFSET                         (0x620) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_6_OFFSET                         (0x720) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR4_ID_7_OFFSET                         (0x820) /* INCR4_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR4������������ */
#define    HI_AMON_INCR8_ID_0_OFFSET                         (0x128) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_1_OFFSET                         (0x228) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_2_OFFSET                         (0x328) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_3_OFFSET                         (0x428) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_4_OFFSET                         (0x528) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_5_OFFSET                         (0x628) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_6_OFFSET                         (0x728) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR8_ID_7_OFFSET                         (0x828) /* INCR8_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR8������������ */
#define    HI_AMON_INCR16_ID_0_OFFSET                        (0x130) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_1_OFFSET                        (0x230) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_2_OFFSET                        (0x330) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_3_OFFSET                        (0x430) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_4_OFFSET                        (0x530) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_5_OFFSET                        (0x630) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_6_OFFSET                        (0x730) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_INCR16_ID_7_OFFSET                        (0x830) /* INCR16_ID��axi monitorͳ�Ƽ��ID�ŷ���INCR16������������ */
#define    HI_AMON_WRAP_ID_0_OFFSET                          (0x160) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_1_OFFSET                          (0x260) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_2_OFFSET                          (0x360) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_3_OFFSET                          (0x460) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_4_OFFSET                          (0x560) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_5_OFFSET                          (0x660) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_6_OFFSET                          (0x760) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_WRAP_ID_7_OFFSET                          (0x860) /* WRAP_ID��axi monitorͳ�Ƽ��ID�ŷ���WRAP������������ */
#define    HI_AMON_BURST_ID_0_OFFSET                         (0x190) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_1_OFFSET                         (0x290) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_2_OFFSET                         (0x390) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_3_OFFSET                         (0x490) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_4_OFFSET                         (0x590) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_5_OFFSET                         (0x690) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_6_OFFSET                         (0x790) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_BURST_ID_7_OFFSET                         (0x890) /* BURST_ID��axi monitorͳ�Ƽ��ID�ŷ���burst������������ */
#define    HI_AMON_FINISH_ID_0_OFFSET                        (0x1A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_1_OFFSET                        (0x2A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_2_OFFSET                        (0x3A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_3_OFFSET                        (0x4A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_4_OFFSET                        (0x5A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_5_OFFSET                        (0x6A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_6_OFFSET                        (0x7A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_FINISH_ID_7_OFFSET                        (0x8A0) /* FINISH_ID��axi monitorͳ�Ƽ��ID�����burst���������� */
#define    HI_AMON_READ_WAIT_ID_0_OFFSET                     (0x1B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_1_OFFSET                     (0x2B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_2_OFFSET                     (0x3B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_3_OFFSET                     (0x4B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_4_OFFSET                     (0x5B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_5_OFFSET                     (0x6B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_6_OFFSET                     (0x7B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_READ_WAIT_ID_7_OFFSET                     (0x8B8) /* READ_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ��ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_0_OFFSET                    (0x1C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_1_OFFSET                    (0x2C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_2_OFFSET                    (0x3C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_3_OFFSET                    (0x4C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_4_OFFSET                    (0x5C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_5_OFFSET                    (0x6C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_6_OFFSET                    (0x7C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_ID_7_OFFSET                    (0x8C0) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д���ݵȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET               (0x1D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_1_OFFSET               (0x2D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_2_OFFSET               (0x3D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_3_OFFSET               (0x4D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_4_OFFSET               (0x5D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_5_OFFSET               (0x6D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_6_OFFSET               (0x7D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_WRITE_WAIT_RESP_ID_7_OFFSET               (0x8D0) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ�ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_0_OFFSET                 (0x1D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_1_OFFSET                 (0x2D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_2_OFFSET                 (0x3D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_3_OFFSET                 (0x4D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_4_OFFSET                 (0x5D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_5_OFFSET                 (0x6D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_6_OFFSET                 (0x7D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_READ_MAX_WAIT_ID_7_OFFSET                 (0x8D8) /* READ_MAX_WAIT_ID��axi monitorͳ�Ƽ��ID�Ŷ����ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_0_OFFSET                (0x1DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_1_OFFSET                (0x2DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_2_OFFSET                (0x3DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_3_OFFSET                (0x4DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_4_OFFSET                (0x5DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_5_OFFSET                (0x6DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_6_OFFSET                (0x7DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_ID_7_OFFSET                (0x8DC) /* WRITE_WAIT_ID��axi monitorͳ�Ƽ��ID��д�������ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_0_OFFSET           (0x1E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_1_OFFSET           (0x2E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_2_OFFSET           (0x3E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_3_OFFSET           (0x4E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_4_OFFSET           (0x5E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_5_OFFSET           (0x6E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_6_OFFSET           (0x7E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_WRITE_MAX_WAIT_RESP_ID_7_OFFSET           (0x8E4) /* WRITE_WAIT_RESP_ID��axi monitorͳ�Ƽ��ID��д��Ӧ���ȴ����ڼ����� */
#define    HI_AMON_READ_BYTES_ID_0_OFFSET                    (0x1E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_1_OFFSET                    (0x2E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_2_OFFSET                    (0x3E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_3_OFFSET                    (0x4E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_4_OFFSET                    (0x5E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_5_OFFSET                    (0x6E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_6_OFFSET                    (0x7E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_READ_BYTES_ID_7_OFFSET                    (0x8E8) /* READ_BYTES_ID��axi monitorͳ�Ƽ��ID�����ж�����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_0_OFFSET                   (0x1F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_1_OFFSET                   (0x2F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_2_OFFSET                   (0x3F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_3_OFFSET                   (0x4F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_4_OFFSET                   (0x5F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_5_OFFSET                   (0x6F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_6_OFFSET                   (0x7F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_WRITE_BYTES_ID_7_OFFSET                   (0x8F0) /* WRITE_BYTES_ID��axi monitorͳ�Ƽ��ID������д����������byteΪ��λ */
#define    HI_AMON_CAPT_CTRL_OFFSET                          (0x900) /* CAPT_CTRL�������ݲɼ���ʼ�ͽ��� */
#define    HI_AMON_CAPT_ID_EN_OFFSET                         (0x904) /* CAPT_ID_EN��ID����ʹ�ܼĴ����� */
#define    HI_AMON_CAPT_CONFIG_OFFSET                        (0x908) /* CAPT_CONFIG�������ݲɼ�״̬ */
#define    HI_AMON_CAPT_ID_0_OFFSET                          (0x90C) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_1_OFFSET                          (0x910) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_2_OFFSET                          (0x914) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_3_OFFSET                          (0x918) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_4_OFFSET                          (0x91C) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_5_OFFSET                          (0x920) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_6_OFFSET                          (0x924) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_ID_7_OFFSET                          (0x928) /* CAPT_ID��axi monitor��ϵͳID��Ϣ�Ĵ����� */
#define    HI_AMON_CAPT_INT_SRC_OFFSET                       (0x92C) /* CAPT_INT_SRC�����ݲɼ������в������ж�����Ӧ��ԭʼ�жϼĴ��� */
#define    HI_AMON_CAPT_INT_MASK_OFFSET                      (0x930) /* CAPT_INT_MASK�����ݲɼ������в������ж�����Ӧ�����μĴ��� */
#define    HI_AMON_CAPT_INT_STATE_OFFSET                     (0x934) /* CAPT_INT_STAT�����ݲɼ������в������ж�����Ӧ��״̬�Ĵ��� */
#define    HI_AMON_CAPT_INT_CLR_OFFSET                       (0x938) /* CAPT_INT_CLR�����ݲɼ������в������ж�����Ӧ���ж�����Ĵ��� */
#define    HI_AMON_AXI_STATE_OFFSET                          (0x93C) /* AXI_STATE��д����ָʾ״̬�Ĵ��� */
#define    HI_AMON_CAPT_TRANS_WAIT_TIME_OFFSET               (0x940) /* CAPT_TANS_WAIT_TIM���ݰ��������ж��ϱ��ȴ�ʱ���Ĵ�������ֹƵ�����жϣ� */
#define    HI_AMON_TRANS_DATA_CNT_OFFSET                     (0x944) /* TANS_DATA_CNT���ݰ�����ͳ�� */
#define    HI_AMON_TRANS_DATA_CNT_HIGH_OFFSET                (0xD4) /* TANS_DATA_CNT���ݰ�����ͳ�� */
#define    HI_AMON_TRANS_DATA_LEVEL_OFFSET                   (0x948) /* TANS_DATA_LEVEL���ݰ���һ����������ֵ�����üĴ������ϱ��жϱ�־ */
#define    HI_AMON_CMD_PKG_SIZE_OFFSET                       (0x94C) /* CMD_PKG_SIZE����������İ����� */
#define    HI_AMON_DATA1_PKG_SIZE_OFFSET                     (0x950) /* DATA1_PKG_SIZE����������İ����� */
#define    HI_AMON_DATA2_PKG_SIZE_OFFSET                     (0x954) /* DATA2_PKG_SIZE����������İ����� */
#define    HI_AMON_DMA_REQ_EN_OFFSET                         (0x958) /* DMA_REQ_EN����dma��������ʹ�� */

#endif // __HI_AMON_H__

