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

#ifndef HI6930_UART_H
#define HI6930_UART_H

/*
 * bsp_uart.h -- balong uart driver header for both linux and vxworks
 *
 * Copyright (C) 2012 Huawei Corporation
 * 
 *
*/
#include "soc_memmap.h"
#include "soc_interrupts.h"

#define ARM_UART_PERIPHERAL_ID      0x00041011
#define SYNOPSYS_UART_PERIPHERAL_ID 0x000c21c0

#define MINI_SYSTEM_UART_ADDR		HI_UART1_REGBASE_ADDR

#define UART0_BASE_ADDR             HI_UART0_REGBASE_ADDR
#define UART1_BASE_ADDR             HI_UART1_REGBASE_ADDR
#define UART2_BASE_ADDR             HI_UART2_REGBASE_ADDR
#define UART3_BASE_ADDR             HI_UART_MDM_REGBASE_ADDR
#define UART0_INT_LVL               INT_LVL_UART0
#define UART1_INT_LVL               INT_LVL_UART1
#define UART2_INT_LVL               INT_LVL_UART2
#define UART3_INT_LVL               INT_LVL_UART_MDM
#define UART0_M3_INT                M3_UART0_INT
#define UART1_M3_INT                M3_UART1_INT
#define UART2_M3_INT                M3_UART2_INT
#define UART3_M3_INT                0

#define CCORE_SYS_UART_BASE         0xE0203000
#define CCORE_SYS_UART_INTID        50

#define UART_USE_FLAG               0x112233
#define AT_UART_USE_FLAG            0x116119

#define PRT_FLAG_EN_MAGIC_M         0x24680136  /* M���İ����궨��*/
#define PRT_FLAG_EN_MAGIC_A         0x24680137  /* A���İ����궨��*/

#define UART_BALONG_ID              ARM_UART_PERIPHERAL_ID  /* uart id */
#define UART_ID_ARM                 0x00041011
#define UART_BALONG_ID_MASK         0x000fffff 
#define UART_PRIMCELL_CLOCK         19200000
#define UART_BAUDRATE               115200

/*-----------------------OFFSET OF REGISTER------------------------*/
#define UART_REGOFFSET_RBR			0x00	/*�������ݼĴ���*/
#define UART_REGOFFSET_THR			0x00	/*�������ݼĴ���*/
#define UART_REGOFFSET_RSR_ECR		0x04	/*����״̬�Ĵ���/��������Ĵ���*/
#define UART_REGOFFSET_FR			0x18	/*��ǩ�Ĵ���*/
#define UART_REGOFFSET_IBRD			0x24	/*�����ʼĴ���*/
#define UART_REGOFFSET_FBRD			0x28
#define UART_REGOFFSET_LCR_H		0x2C	/*�߿ؼĴ���*/
#define UART_REGOFFSET_CR			0x30	/*���ƼĴ���*/
#define UART_REGOFFSET_IFLS			0x34	/*�ж�fifo levelѡ��Ĵ���*/
#define UART_REGOFFSET_IMSC			0x38	/*�ж����ε�����/���ѡ��Ĵ���*/
#define UART_REGOFFSET_MIS			0x40	/*���κ���ж�״̬�Ĵ���*/
#define UART_REGOFFSET_ICR			0x44	/*�ж�����Ĵ���*/
#define UART_REGOFFSET_DMACR		0x48	/*DMA���ƼĴ���*/

#define UART_FIFO_SIZE              32      /* FIFO SIZE*/
#define UART_FIFO_MASK              0xF0

#define PTIME       (1<<7)

#define UART_LCR_BC_NORMAL          0x00 /* ��ͣ����λ ����*/
#define UART_LCR_BC_UNNORMAL        0x01 /* ��ͣ����λ ��ͣ*/
/*-------------------IFLS BITS FIELD-----------------------------*/

#define UART_IFLS_DEF_SET           0x12 	/* ����ˮλ1/2full ����ˮ��Ϊ3/4full*/
/*-------------------IER BITS FIELD-----------------------------*/
#define UART_DISABLE	        	0x00 	/* uart���� */
#define UART_ENABLE					0x01 	/* uartʹ�� */
#define UART_TX_ENABLE      		0x100 	/*����ʹ��*/
#define UART_RX_ENABLE      		0x200 	/*����ʹ��*/
#define UART_IER_IRQ_CLR			0xFFFF 	/*��������ж�*/
/*-------------------LCR BITS FIELD-----------------------------*/
#define UART_LCR_DLS_MASK           0x03 	/* ���ݳ�������*/
#define UART_LCR_DLS_5BITS          0x00 	/* ���ݳ���ѡ��,5bits */
#define UART_LCR_DLS_6BITS          0x20 	/* ���ݳ���ѡ��,6bits */
#define UART_LCR_DLS_7BITS          0x40 	/* ���ݳ���ѡ��,7bits */
#define UART_LCR_DLS_8BITS          0x60 	/* ���ݳ���ѡ��,8bits */

#define UART_LCR_STOP_2BITS         0x08 	/* ֹͣλ����,2bits*/
#define UART_LCR_STOP_1BITS         0x00 	/* ֹͣλ����,1bit */
#define UART_LCR_PEN_NONE	        0x00 	/* set no parity */

#define UART_LCR_ODD                0x02 	/* ��У��ʹ��*/
#define UART_LCR_EPS                0x06 	/* żУ��ʹ��*/

#define UART_LCR_DEFAULTVALUE       0x00 	/* LCRĬ��ֵ*/
#define UART_LCR_FIFO_ENABLE	    0x10 	/* Enable both FIFOs */
#define UART_LCR_FIFO_DISABLE	    0x00 	/* Disable both FIFOs */
/*-------------------FR BITS FIELD-----------------------------*/
#define UART_FR_UART_BUSY          	0x08 	/* UARTæ��־   */
#define UART_FR_RX_FIFO_EMP			0x10 	/* ����FIFIOΪ�� */
#define UART_FR_TX_FIFO_FULL        0x20 	/* ����FIFOΪ����־   */
#define UART_FR_RX_FIFO_FULL      	0x40 	/* ����FIFO����־   */
#define UART_FR_TX_FIFO_EMP       	0x80 	/* ����FIFO�ձ�־   */

/*-------------------IMSC BITS FIELD-----------------------------*/
#define UART_RX_IRQ_ENABLE      	0x10 	/*�����ж�ʹ��*/
#define UART_TX_IRQ_ENABLE			0x20 	/*�����ж�ʹ�� */
#define UART_TIMEOUT_IRQ_ENABLE		0x40 	/*���ճ�ʱ�ж�ʹ�� */
#define UART_ALL_IRQ_DISABLE		0x00
/*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_REV_VALID          0x10 	/* ������������Ч */
#define UART_IIR_THR_INTERRUPT      0x20 	/* �����ж�	*/
#define UART_IIR_REV_TIMEOUT        0x40	/* ���ճ�ʱ    */


/******************* uart print macro definition ********************/
#ifndef __ASSEMBLY__
struct uart_info{
	unsigned int uart_base_addr;
	unsigned int uart_intid;
};

extern struct uart_info g_uart_info;

static inline void print_info(const char *buffer)
{
    int loop;
    volatile unsigned int status = 0;
    while (*buffer != '\0')
    {
        /* wait for the tx fifo is empty and the uart is idle */
        loop = 0x10000;
        while ((status != 0x10) && loop--)
        {
            status = *(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_FR) & 0x18;
        }
		*(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR) = (unsigned int)(*buffer);
        buffer++;
    }
}
#endif
static inline void modem_uart_gpio_config(void)
{
	/*����GPIO 20 ����uart6Ϊmodem ʹ��--K3V5 SFT*/
	*(volatile unsigned *)(0xE8A1F400) = (unsigned int)(0xFF);
	*(volatile unsigned *)(0xE8A1F3FC) = (unsigned int)(0x20);
}
#define print_uart_m3boot(value)\
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =value;\
	ldr r3, =UART_REGOFFSET_THR;\
	str r2, [r1,r3]
            
#define uart_init_m3boot \
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =0xE0;\
	ldr r3, =UART_REGOFFSET_RSR_ECR;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFFSET_IMSC;\
	str r2, [r1, r3];\
	ldr r2, =0xFFFF;\
	ldr r3, =UART_REGOFFSET_ICR;\
	str r2, [r1, r3];\
	ldr r2, =0x1A;\
	ldr r3, =UART_REGOFFSET_IBRD;\
	str r2, [r1, r3];\
	ldr r2, =0x3;\
	ldr r3, =UART_REGOFFSET_FBRD;\
	str r2, [r1, r3];\
	ldr r2, =0x70;\
	ldr r3, =UART_REGOFFSET_LCR_H;\
	str r2, [r1, r3];\
	ldr r2, =0x164;\
	ldr r3, =UART_REGOFFSET_IFLS;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFFSET_DMACR;\
	str r2, [r1, r3];\
	ldr r2, =0x301;\
	ldr r3, =UART_REGOFFSET_CR;\
	str r2, [r1, r3];\
	bx lr

#endif /* BSP_UART_H */

