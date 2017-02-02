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

#ifndef __HI_SOCP_H__
#define __HI_SOCP_H__

#define HI_SOCP_GLOBAL_SRST_CTRL_OFFSET              (0x0)            /* SOCPȫ����λ���ƼĴ��� */
#define HI_SOCP_ENC_SRST_CTRL_OFFSET                 (0x4)            /* ����ͨ����λ���ƼĴ��� */
#define HI_SOCP_DEC_SRST_CTRL_OFFSET                 (0x8)            /* ����ͨ����λ���ƼĴ��� */
#define HI_SOCP_ENC_CH_STATUS_OFFSET                 (0xC)            /* ����ͨ��״̬�Ĵ��� */
#define HI_SOCP_DEC_CH_STATUS_OFFSET                 (0x10)           /* ����ͨ��״̬�Ĵ��� */
#define HI_SOCP_CLK_CTRL_OFFSET                      (0x14)           /* �Զ�ʱ���ſؿ��ƼĴ��� */
#define HI_SOCP_PRIOR_CFG_OFFSET                     (0x18)           /* ���ȼ����üĴ��� */
#define HI_SOCP_DEC_INT_TIMEOUT_OFFSET               (0x20)           /* �����жϳ�ʱ���üĴ��� */
#define HI_SOCP_INT_TIMEOUT_OFFSET                   (0x24)           /* ������жϳ�ʱ���üĴ��� */
#define HI_SOCP_BUFFER_TIMEOUT_OFFSET                (0x28)           /* BUFFER�����ʱ���üĴ��� */
#define HI_SOCP_DEC_PKT_LEN_CFG_OFFSET               (0x2C)           /* ����ͨ·���������üĴ��� */
#define HI_SOCP_ENC_SRCCH_SECCTRL_OFFSET             (0x30)           /* ����Դͨ����ȫ���ƼĴ��� */
#define HI_SOCP_ENC_DSTCH_SECCTRL_OFFSET             (0x34)           /* ����Ŀ��ͨ����ȫ���ƼĴ��� */
#define HI_SOCP_DEC_SRCCH_SECCTRL_OFFSET             (0x38)           /* ����Դͨ����ȫ���ƼĴ��� */
#define HI_SOCP_DEC_DSTCH_SECCTRL_OFFSET             (0x3C)           /* ����Ŀ��ͨ����ȫ���ƼĴ��� */
#define HI_SOCP_GLB_OFFSET_SECCTRL_OFFSET            (0x40)           /* ȫ�ּĴ�����ȫ���ƼĴ��� */
#define HI_SOCP_GLOBAL_INT_STATUS_OFFSET             (0x50)           /* ȫ���ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_MASK0_OFFSET               (0x54)           /* CORE0���봫���ж����μĴ��� */
#define HI_SOCP_ENC_CORE0_RAWINT0_OFFSET             (0x58)           /* CORE0���봫���ж�ԭʼ״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_INT0_OFFSET                (0x5C)           /* CORE0���봫���ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_MASK1_OFFSET               (0x60)           /* CORE0����ͷ��־���ж����μĴ��� */
#define HI_SOCP_ENC_CORE1_MASK1_OFFSET               (0x64)           /* CORE1����ͷ��־���ж����μĴ��� */
#define HI_SOCP_ENC_RAWINT1_OFFSET                   (0x68)           /* ����ͨ��ͷ��־���ж�ԭʼ״̬�Ĵ���1 */
#define HI_SOCP_ENC_CORE0_INT1_OFFSET                (0x6C)           /* CORE0����ͨ��ͷ��־���ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE1_INT1_OFFSET                (0x70)           /* CORE1����ͨ��ͷ��־���ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_MASK2_OFFSET               (0x74)           /* CORE0����Ŀ��buffer�����ж����μĴ��� */
#define HI_SOCP_ENC_CORE0_RAWINT2_OFFSET             (0x78)           /* ����Ŀ��buffer����ԭʼ�ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_INT2_OFFSET                (0x7C)           /* CORE0����Ŀ��buffer�����ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_MASK3_OFFSET               (0x80)           /* CORE0����RD�ж����μĴ��� */
#define HI_SOCP_ENC_CORE1_MASK3_OFFSET               (0x84)           /* CORE1����RD�ж����μĴ��� */
#define HI_SOCP_ENC_RAWINT3_OFFSET                   (0x88)           /* ����ͨ��RDԭʼ�ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE0_INT3_OFFSET                (0x8C)           /* CORE0����RD�ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE1_INT3_OFFSET                (0x90)           /* CORE1����RD�ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE0_MASK0_OFFSET               (0xA8)           /* CORE0����ͨ�������ж����μĴ��� */
#define HI_SOCP_DEC_CORE1_MASK0_OFFSET               (0xAC)           /* CORE1����ͨ�������ж����μĴ��� */
#define HI_SOCP_DEC_RAWINT0_OFFSET                   (0xB0)           /* ����ͨ���ж�ԭʼ״̬�Ĵ���0 */
#define HI_SOCP_DEC_CORE0_INT0_OFFSET                (0xB4)           /* CORE0����ͨ�������ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE1_INT0_OFFSET                (0xB8)           /* CORE1����ͨ�������ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE0_MASK1_OFFSET               (0xBC)           /* CORE0����ͨ���쳣�ж����μĴ��� */
#define HI_SOCP_DEC_CORE0_RAWINT1_OFFSET             (0xC0)           /* ����ͨ���쳣�ж�ԭʼ״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE0_INT1_OFFSET                (0xC4)           /* CORE0����ͨ���쳣�ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE0_MASK2_OFFSET               (0xC8)           /* CORE0����ͨ��Ŀ��buffer����ж����μĴ��� */
#define HI_SOCP_DEC_CORE1NOTE_MASK2_OFFSET           (0xCC)           /* CORE1����ͨ��Ŀ��buffer����ж����μĴ��� */
#define HI_SOCP_DEC_RAWINT2_OFFSET                   (0xD0)           /* ����ͨ��Ŀ��buffer����ж�ԭʼ״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE0NOTE_NT2_OFFSET             (0xD4)           /* CORE0����ͨ��Ŀ��buffer����ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE1NOTE_INT2_OFFSET            (0xD8)           /* CORE1����ͨ��Ŀ��buffer����ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE1_MASK0_OFFSET               (0xDC)           /* CORE1���봫���ж����μĴ��� */
#define HI_SOCP_ENC_CORE1_INT0_OFFSET                (0xE0)           /* CORE1���봫���ж�״̬�Ĵ��� */
#define HI_SOCP_ENC_CORE1_MASK2_OFFSET               (0xE4)           /* CORE1����Ŀ��buffer�����ж����μĴ��� */
#define HI_SOCP_ENC_CORE1_INT2_OFFSET                (0xE8)           /* CORE1����Ŀ��buffer�����ж�״̬�Ĵ��� */
#define HI_SOCP_DEC_CORE1_MASK1_OFFSET               (0xEC)           /* CORE1����ͨ���쳣�ж����μĴ��� */
#define HI_SOCP_DEC_CORE1_INT1_OFFSET                (0xF0)           /* CORE1����ͨ���쳣�ж�״̬�Ĵ��� */
#define HI_SOCP_BUS_ERROR_MASK_OFFSET                (0xF4)           /* �����쳣�ж����μĴ��� */
#define HI_SOCP_BUS_ERROR_RAWINT_OFFSET              (0xF8)           /* �����쳣ԭʼ�ж�״̬�Ĵ��� */
#define HI_SOCP_BUS_ERROR_INT_OFFSET                 (0xFC)           /* �����쳣���κ��жϼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_0_OFFSET           (0x100)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_1_OFFSET           (0x140)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_2_OFFSET           (0x180)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_3_OFFSET           (0x1C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_4_OFFSET           (0x200)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_5_OFFSET           (0x240)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_6_OFFSET           (0x280)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_7_OFFSET           (0x2C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_8_OFFSET           (0x300)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_9_OFFSET           (0x340)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_10_OFFSET          (0x380)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_11_OFFSET          (0x3C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_12_OFFSET          (0x400)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_13_OFFSET          (0x440)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_14_OFFSET          (0x480)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_15_OFFSET          (0x4C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_16_OFFSET          (0x500)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_17_OFFSET          (0x540)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_18_OFFSET          (0x580)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_19_OFFSET          (0x5C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_20_OFFSET          (0x600)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_21_OFFSET          (0x640)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_22_OFFSET          (0x680)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_23_OFFSET          (0x6C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_24_OFFSET          (0x700)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_25_OFFSET          (0x740)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_26_OFFSET          (0x780)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_27_OFFSET          (0x7C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_28_OFFSET          (0x800)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_29_OFFSET          (0x840)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_30_OFFSET          (0x880)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_WPTR_31_OFFSET          (0x8C0)          /* ����ͨ·Դbuffermдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_0_OFFSET           (0x104)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_1_OFFSET           (0x144)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_2_OFFSET           (0x184)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_3_OFFSET           (0x1C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_4_OFFSET           (0x204)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_5_OFFSET           (0x244)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_6_OFFSET           (0x284)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_7_OFFSET           (0x2C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_8_OFFSET           (0x304)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_9_OFFSET           (0x344)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_10_OFFSET          (0x384)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_11_OFFSET          (0x3C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_12_OFFSET          (0x404)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_13_OFFSET          (0x444)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_14_OFFSET          (0x484)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_15_OFFSET          (0x4C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_16_OFFSET          (0x504)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_17_OFFSET          (0x544)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_18_OFFSET          (0x584)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_19_OFFSET          (0x5C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_20_OFFSET          (0x604)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_21_OFFSET          (0x644)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_22_OFFSET          (0x684)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_23_OFFSET          (0x6C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_24_OFFSET          (0x704)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_25_OFFSET          (0x744)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_26_OFFSET          (0x784)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_27_OFFSET          (0x7C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_28_OFFSET          (0x804)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_29_OFFSET          (0x844)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_30_OFFSET          (0x884)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_RPTR_31_OFFSET          (0x8C4)          /* ����ͨ·Դbufferm��ָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_0_OFFSET           (0x108)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_1_OFFSET           (0x148)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_2_OFFSET           (0x188)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_3_OFFSET           (0x1C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_4_OFFSET           (0x208)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_5_OFFSET           (0x248)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_6_OFFSET           (0x288)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_7_OFFSET           (0x2C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_8_OFFSET           (0x308)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_9_OFFSET           (0x348)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_10_OFFSET          (0x388)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_11_OFFSET          (0x3C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_12_OFFSET          (0x408)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_13_OFFSET          (0x448)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_14_OFFSET          (0x488)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_15_OFFSET          (0x4C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_16_OFFSET          (0x508)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_17_OFFSET          (0x548)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_18_OFFSET          (0x588)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_19_OFFSET          (0x5C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_20_OFFSET          (0x608)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_21_OFFSET          (0x648)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_22_OFFSET          (0x688)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_23_OFFSET          (0x6C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_24_OFFSET          (0x708)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_25_OFFSET          (0x748)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_26_OFFSET          (0x788)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_27_OFFSET          (0x7C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_28_OFFSET          (0x808)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_29_OFFSET          (0x848)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_30_OFFSET          (0x888)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_ADDR_31_OFFSET          (0x8C8)          /* ����ͨ·Դbufferm��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_0_OFFSET          (0x10C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_1_OFFSET          (0x14C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_2_OFFSET          (0x18C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_3_OFFSET          (0x1CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_4_OFFSET          (0x20C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_5_OFFSET          (0x24C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_6_OFFSET          (0x28C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_7_OFFSET          (0x2CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_8_OFFSET          (0x30C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_9_OFFSET          (0x34C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_10_OFFSET         (0x38C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_11_OFFSET         (0x3CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_12_OFFSET         (0x40C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_13_OFFSET         (0x44C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_14_OFFSET         (0x48C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_15_OFFSET         (0x4CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_16_OFFSET         (0x50C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_17_OFFSET         (0x54C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_18_OFFSET         (0x58C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_19_OFFSET         (0x5CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_20_OFFSET         (0x60C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_21_OFFSET         (0x64C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_22_OFFSET         (0x68C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_23_OFFSET         (0x6CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_24_OFFSET         (0x70C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_25_OFFSET         (0x74C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_26_OFFSET         (0x78C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_27_OFFSET         (0x7CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_28_OFFSET         (0x80C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_29_OFFSET         (0x84C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_30_OFFSET         (0x88C)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_DEPTH_31_OFFSET         (0x8CC)          /* ����ͨ·Դbufferm��ȼĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_0_OFFSET            (0x110)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_1_OFFSET            (0x150)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_2_OFFSET            (0x190)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_3_OFFSET            (0x1D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_4_OFFSET            (0x210)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_5_OFFSET            (0x250)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_6_OFFSET            (0x290)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_7_OFFSET            (0x2D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_8_OFFSET            (0x310)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_9_OFFSET            (0x350)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_10_OFFSET           (0x390)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_11_OFFSET           (0x3D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_12_OFFSET           (0x410)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_13_OFFSET           (0x450)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_14_OFFSET           (0x490)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_15_OFFSET           (0x4D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_16_OFFSET           (0x510)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_17_OFFSET           (0x550)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_18_OFFSET           (0x590)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_19_OFFSET           (0x5D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_20_OFFSET           (0x610)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_21_OFFSET           (0x650)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_22_OFFSET           (0x690)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_23_OFFSET           (0x6D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_24_OFFSET           (0x710)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_25_OFFSET           (0x750)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_26_OFFSET           (0x790)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_27_OFFSET           (0x7D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_28_OFFSET           (0x810)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_29_OFFSET           (0x850)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_30_OFFSET           (0x890)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_BUFM_CFG_31_OFFSET           (0x8D0)          /* ����ͨ·Դbufferm���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_0_OFFSET            (0x114)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_1_OFFSET            (0x154)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_2_OFFSET            (0x194)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_3_OFFSET            (0x1D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_4_OFFSET            (0x214)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_5_OFFSET            (0x254)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_6_OFFSET            (0x294)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_7_OFFSET            (0x2D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_8_OFFSET            (0x314)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_9_OFFSET            (0x354)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_10_OFFSET           (0x394)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_11_OFFSET           (0x3D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_12_OFFSET           (0x414)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_13_OFFSET           (0x454)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_14_OFFSET           (0x494)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_15_OFFSET           (0x4D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_16_OFFSET           (0x514)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_17_OFFSET           (0x554)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_18_OFFSET           (0x594)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_19_OFFSET           (0x5D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_20_OFFSET           (0x614)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_21_OFFSET           (0x654)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_22_OFFSET           (0x694)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_23_OFFSET           (0x6D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_24_OFFSET           (0x714)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_25_OFFSET           (0x754)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_26_OFFSET           (0x794)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_27_OFFSET           (0x7D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_28_OFFSET           (0x814)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_29_OFFSET           (0x854)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_30_OFFSET           (0x894)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_WPTR_31_OFFSET           (0x8D4)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_0_OFFSET            (0x118)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_1_OFFSET            (0x158)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_2_OFFSET            (0x198)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_3_OFFSET            (0x1D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_4_OFFSET            (0x218)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_5_OFFSET            (0x258)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_6_OFFSET            (0x298)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_7_OFFSET            (0x2D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_8_OFFSET            (0x318)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_9_OFFSET            (0x358)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_10_OFFSET           (0x398)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_11_OFFSET           (0x3D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_12_OFFSET           (0x418)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_13_OFFSET           (0x458)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_14_OFFSET           (0x498)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_15_OFFSET           (0x4D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_16_OFFSET           (0x518)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_17_OFFSET           (0x558)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_18_OFFSET           (0x598)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_19_OFFSET           (0x5D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_20_OFFSET           (0x618)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_21_OFFSET           (0x658)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_22_OFFSET           (0x698)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_23_OFFSET           (0x6D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_24_OFFSET           (0x718)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_25_OFFSET           (0x758)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_26_OFFSET           (0x798)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_27_OFFSET           (0x7D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_28_OFFSET           (0x818)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_29_OFFSET           (0x858)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_30_OFFSET           (0x898)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_RPTR_31_OFFSET           (0x8D8)          /* ����ͨ·RD����bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_0_OFFSET           (0x11C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_1_OFFSET           (0x15C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_2_OFFSET           (0x19C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_3_OFFSET           (0x1DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_4_OFFSET           (0x21C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_5_OFFSET           (0x25C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_6_OFFSET           (0x29C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_7_OFFSET           (0x2DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_8_OFFSET           (0x31C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_9_OFFSET           (0x35C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_10_OFFSET          (0x39C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_11_OFFSET          (0x3DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_12_OFFSET          (0x41C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_13_OFFSET          (0x45C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_14_OFFSET          (0x49C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_15_OFFSET          (0x4DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_16_OFFSET          (0x51C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_17_OFFSET          (0x55C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_18_OFFSET          (0x59C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_19_OFFSET          (0x5DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_20_OFFSET          (0x61C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_21_OFFSET          (0x65C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_22_OFFSET          (0x69C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_23_OFFSET          (0x6DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_24_OFFSET          (0x71C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_25_OFFSET          (0x75C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_26_OFFSET          (0x79C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_27_OFFSET          (0x7DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_28_OFFSET          (0x81C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_29_OFFSET          (0x85C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_30_OFFSET          (0x89C)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_BADDR_31_OFFSET          (0x8DC)          /* ����ͨ·RD����buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_0_OFFSET             (0x120)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_1_OFFSET             (0x160)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_2_OFFSET             (0x1A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_3_OFFSET             (0x1E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_4_OFFSET             (0x220)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_5_OFFSET             (0x260)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_6_OFFSET             (0x2A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_7_OFFSET             (0x2E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_8_OFFSET             (0x320)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_9_OFFSET             (0x360)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_10_OFFSET            (0x3A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_11_OFFSET            (0x3E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_12_OFFSET            (0x420)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_13_OFFSET            (0x460)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_14_OFFSET            (0x4A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_15_OFFSET            (0x4E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_16_OFFSET            (0x520)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_17_OFFSET            (0x560)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_18_OFFSET            (0x5A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_19_OFFSET            (0x5E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_20_OFFSET            (0x620)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_21_OFFSET            (0x660)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_22_OFFSET            (0x6A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_23_OFFSET            (0x6E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_24_OFFSET            (0x720)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_25_OFFSET            (0x760)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_26_OFFSET            (0x7A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_27_OFFSET            (0x7E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_28_OFFSET            (0x820)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_29_OFFSET            (0x860)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_30_OFFSET            (0x8A0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_SRC_RDQ_CFG_31_OFFSET            (0x8E0)          /* ����ͨ·RD����buffer���üĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_0_OFFSET          (0x900)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_1_OFFSET          (0x920)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_2_OFFSET          (0x940)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_3_OFFSET          (0x960)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_4_OFFSET          (0x980)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_5_OFFSET          (0x9A0)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_WPTR_6_OFFSET          (0x9C0)          /* ����ͨ·Ŀ��bufferдָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_0_OFFSET          (0x904)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_1_OFFSET          (0x924)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_2_OFFSET          (0x944)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_3_OFFSET          (0x964)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_4_OFFSET          (0x984)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_5_OFFSET          (0x9A4)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_RPTR_6_OFFSET          (0x9C4)          /* ����ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_0_OFFSET          (0x908)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_1_OFFSET          (0x928)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_2_OFFSET          (0x948)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_3_OFFSET          (0x968)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_4_OFFSET          (0x988)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_5_OFFSET          (0x9A8)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_ADDR_6_OFFSET          (0x9C8)          /* ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_0_OFFSET         (0x90C)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_1_OFFSET         (0x92C)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_2_OFFSET         (0x94C)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_3_OFFSET         (0x96C)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_4_OFFSET         (0x98C)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_5_OFFSET         (0x9AC)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_DEPTH_6_OFFSET         (0x9CC)          /* ����ͨ·Ŀ��buffer��ȼĴ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_0_OFFSET          (0x910)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_1_OFFSET          (0x930)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_2_OFFSET          (0x950)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_3_OFFSET          (0x970)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_4_OFFSET          (0x990)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_5_OFFSET          (0x9B0)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_DEST_BUFN_THRH_6_OFFSET          (0x9D0)          /* ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_0_OFFSET           (0x914)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_1_OFFSET           (0x934)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_2_OFFSET           (0x954)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_3_OFFSET           (0x974)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_4_OFFSET           (0x994)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_5_OFFSET           (0x9B4)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_ENC_INT_THRESHOLD_6_OFFSET           (0x9D4)          /* ����ͨ·�����ж���ֵ�Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_WPTR_0_OFFSET           (0xA00)          /* ����ͨ·Դbufferxдָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_WPTR_1_OFFSET           (0xA40)          /* ����ͨ·Դbufferxдָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_WPTR_2_OFFSET           (0xA80)          /* ����ͨ·Դbufferxдָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_WPTR_3_OFFSET           (0xAC0)          /* ����ͨ·Դbufferxдָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_RPTR_0_OFFSET           (0xA04)          /* ����ͨ·Դbufferx��ָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_RPTR_1_OFFSET           (0xA44)          /* ����ͨ·Դbufferx��ָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_RPTR_2_OFFSET           (0xA84)          /* ����ͨ·Դbufferx��ָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_RPTR_3_OFFSET           (0xAC4)          /* ����ͨ·Դbufferx��ָ��Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_ADDR_0_OFFSET           (0xA08)          /* ����ͨ·Դbufferx��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_ADDR_1_OFFSET           (0xA48)          /* ����ͨ·Դbufferx��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_ADDR_2_OFFSET           (0xA88)          /* ����ͨ·Դbufferx��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_ADDR_3_OFFSET           (0xAC8)          /* ����ͨ·Դbufferx��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_SRC_BUFX_CFG0_0_OFFSET           (0xA0C)          /* ����ͨ·Դbufferx���üĴ��� */
#define HI_SOCP_DEC_SRC_BUFX_CFG0_1_OFFSET           (0xA4C)          /* ����ͨ·Դbufferx���üĴ��� */
#define HI_SOCP_DEC_SRC_BUFX_CFG0_2_OFFSET           (0xA8C)          /* ����ͨ·Դbufferx���üĴ��� */
#define HI_SOCP_DEC_SRC_BUFX_CFG0_3_OFFSET           (0xACC)          /* ����ͨ·Դbufferx���üĴ��� */
#define HI_SOCP_DEC_BUFX_STATUS0_0_OFFSET            (0xA20)          /* ����ͨ·״̬�Ĵ���0 */
#define HI_SOCP_DEC_BUFX_STATUS0_1_OFFSET            (0xA60)          /* ����ͨ·״̬�Ĵ���0 */
#define HI_SOCP_DEC_BUFX_STATUS0_2_OFFSET            (0xAA0)          /* ����ͨ·״̬�Ĵ���0 */
#define HI_SOCP_DEC_BUFX_STATUS0_3_OFFSET            (0xAE0)          /* ����ͨ·״̬�Ĵ���0 */
#define HI_SOCP_DEC_BUFX_STATUS1_0_OFFSET            (0xA24)          /* ����ͨ·״̬�Ĵ���1 */
#define HI_SOCP_DEC_BUFX_STATUS1_1_OFFSET            (0xA64)          /* ����ͨ·״̬�Ĵ���1 */
#define HI_SOCP_DEC_BUFX_STATUS1_2_OFFSET            (0xAA4)          /* ����ͨ·״̬�Ĵ���1 */
#define HI_SOCP_DEC_BUFX_STATUS1_3_OFFSET            (0xAE4)          /* ����ͨ·״̬�Ĵ���1 */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET          (0xC00)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_1_OFFSET          (0xC10)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_2_OFFSET          (0xC20)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_3_OFFSET          (0xC30)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_4_OFFSET          (0xC40)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_5_OFFSET          (0xC50)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_6_OFFSET          (0xC60)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_7_OFFSET          (0xC70)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_8_OFFSET          (0xC80)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_9_OFFSET          (0xC90)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_10_OFFSET         (0xCA0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_11_OFFSET         (0xCB0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_12_OFFSET         (0xCC0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_13_OFFSET         (0xCD0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_14_OFFSET         (0xCE0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_WPTR_15_OFFSET         (0xCF0)          /* ����ͨ·Ŀ��bufferyдָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET          (0xC04)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_1_OFFSET          (0xC14)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_2_OFFSET          (0xC24)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_3_OFFSET          (0xC34)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_4_OFFSET          (0xC44)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_5_OFFSET          (0xC54)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_6_OFFSET          (0xC64)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_7_OFFSET          (0xC74)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_8_OFFSET          (0xC84)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_9_OFFSET          (0xC94)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_10_OFFSET         (0xCA4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_11_OFFSET         (0xCB4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_12_OFFSET         (0xCC4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_13_OFFSET         (0xCD4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_14_OFFSET         (0xCE4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_RPTR_15_OFFSET         (0xCF4)          /* ����ͨ·Ŀ��buffery��ָ��Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_0_OFFSET          (0xC08)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_1_OFFSET          (0xC18)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_2_OFFSET          (0xC28)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_3_OFFSET          (0xC38)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_4_OFFSET          (0xC48)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_5_OFFSET          (0xC58)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_6_OFFSET          (0xC68)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_7_OFFSET          (0xC78)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_8_OFFSET          (0xC88)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_9_OFFSET          (0xC98)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_10_OFFSET         (0xCA8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_11_OFFSET         (0xCB8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_12_OFFSET         (0xCC8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_13_OFFSET         (0xCD8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_14_OFFSET         (0xCE8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_ADDR_15_OFFSET         (0xCF8)          /* ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET          (0xC0C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_1_OFFSET          (0xC1C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_2_OFFSET          (0xC2C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_3_OFFSET          (0xC3C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_4_OFFSET          (0xC4C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_5_OFFSET          (0xC5C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_6_OFFSET          (0xC6C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_7_OFFSET          (0xC7C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_8_OFFSET          (0xC8C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_9_OFFSET          (0xC9C)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_10_OFFSET         (0xCAC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_11_OFFSET         (0xCBC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_12_OFFSET         (0xCCC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_13_OFFSET         (0xCDC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_14_OFFSET         (0xCEC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_DEC_DEST_BUFY_CFG0_15_OFFSET         (0xCFC)          /* ����ͨ·Ŀ��buffery���üĴ��� */
#define HI_SOCP_ENC_CD_DBG0_OFFSET                   (0xE00)          /* ����CD debug�Ĵ���0 */
#define HI_SOCP_ENC_CD_DBG1_OFFSET                   (0xE04)          /* ����CD debug�Ĵ���1 */
#define HI_SOCP_ENC_IBUF_DBG0_OFFSET                 (0xE08)          /* ����Դ��debug�Ĵ���0 */
#define HI_SOCP_ENC_IBUF_DBG1_OFFSET                 (0xE0C)          /* ����Դ��debug�Ĵ���1 */
#define HI_SOCP_ENC_IBUF_DBG2_OFFSET                 (0xE10)          /* ����Դ��debug�Ĵ���2 */
#define HI_SOCP_ENC_IBUF_DBG3_OFFSET                 (0xE14)          /* ����Դ��debug�Ĵ���3 */
#define HI_SOCP_ENC_OBUF_DBG0_OFFSET                 (0xE18)          /* ����Ŀ�Ķ�debug�Ĵ���0 */
#define HI_SOCP_ENC_OBUF_DBG1_OFFSET                 (0xE1C)          /* ����Ŀ�Ķ�debug�Ĵ���1 */
#define HI_SOCP_ENC_OBUF_DBG2_OFFSET                 (0xE20)          /* ����Ŀ�Ķ�debug�Ĵ���2 */
#define HI_SOCP_ENC_OBUF_DBG3_OFFSET                 (0xE24)          /* ����Ŀ�Ķ�debug�Ĵ���3 */
#define HI_SOCP_DEC_IBUF_DBG0_OFFSET                 (0xE28)          /* ����Դ��debug�Ĵ���0 */
#define HI_SOCP_DEC_IBUF_DBG1_OFFSET                 (0xE2C)          /* ����Դ��debug�Ĵ���1 */
#define HI_SOCP_DEC_IBUF_DBG2_OFFSET                 (0xE30)          /* ����Դ��debug�Ĵ���2 */
#define HI_SOCP_DEC_IBUF_DBG3_OFFSET                 (0xE34)          /* ����Դ��debug�Ĵ���3 */
#define HI_SOCP_DEC_OBUF_DBG0_OFFSET                 (0xE38)          /* ����Ŀ�Ķ�debug�Ĵ���0 */
#define HI_SOCP_DEC_OBUF_DBG1_OFFSET                 (0xE3C)          /* ����Ŀ�Ķ�debug�Ĵ���1 */
#define HI_SOCP_DEC_OBUF_DBG2_OFFSET                 (0xE40)          /* ����Ŀ�Ķ�debug�Ĵ���2 */
#define HI_SOCP_DEC_OBUF_DBG3_OFFSET                 (0xE44)          /* ����Ŀ�Ķ�debug�Ĵ���3 */
#define HI_SOCP_SOCP_VERSION_OFFSET                  (0xFFC)          /* �汾ָʾ�Ĵ��� */


#define HI_SOCP_ENC_SRC_BUFM_CFG0_0_OFFSET            (HI_SOCP_ENC_SRC_BUFM_DEPTH_0_OFFSET)
#define HI_SOCP_ENC_SRC_BUFM_CFG1_0_OFFSET			  (HI_SOCP_ENC_SRC_BUFM_CFG_0_OFFSET)
#define HI_SOCP_ENC_DEST_BUFN_CFG_0_OFFSET			  (HI_SOCP_ENC_DEST_BUFN_DEPTH_0_OFFSET)

#endif
