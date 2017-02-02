#ifndef HI_ARMIP_UART_H
#define HI_ARMIP_UART_H

/*
 * bsp_uart.h -- balong uart driver header for both linux and vxworks
 *
 * Copyright (C) 2012 Huawei Corporation
 * 
 *
*/
/*-----------------------OFFSET OF REGISTER------------------------*/
#define UART_REGOFFSET_RBR			0x00	/*�������ݼĴ���*/
#define UART_REGOFFSET_THR			0x00	/*�������ݼĴ���*/
#define UART_REGOFFSET_FR			0x18	/*��ǩ�Ĵ���*/
#define UART_REGOFFSET_IBRD			0x24	/*�����ʼĴ���*/
#define UART_REGOFFSET_FBRD			0x28
#define UART_REGOFFSET_CR			0x30	/*���ƼĴ���*/
#define UART_REGOFFSET_IFLS			0x34    /*�ж�fifo levelѡ��Ĵ���*/
#define UART_REGOFFSET_ICR			0x44	/*�ж�����Ĵ���*/
#define UART_REGOFFSET_LCR_H		0x2C	/*�߿ؼĴ���*/
#define UART_REGOFFSET_IMSC			0x38	/*�ж���������/���ѡ��Ĵ���*/
#define UART_REGOFFSET_MIS			0x40	/*���κ���ж�״̬�Ĵ���*/

#define UART_DR_OE					(1 << 11)
#define UART_DR_BE					(1 << 10)
#define UART_DR_PE					(1 << 9)
#define UART_DR_FE					(1 << 8)
#define UART_DR_ERROR		(UART_DR_OE|UART_DR_BE|UART_DR_PE|UART_DR_FE)

/*-------------------IFLS BITS FIELD-----------------------------*/

#define UART_IFLS_RX_DEF_ONETWO		0x10	/* ���շ���ˮ��ΪFIFO-1/2 */
#define UART_ARM_LCR_DLS_8BITS      0x60 	/* ���ݳ���ѡ��,8bits */
/*-------------------IER BITS FIELD-----------------------------*/
#define UART_DISABLE	        	0x00 	/* uart���� */
#define UART_ENABLE					0x01 	/* uartʹ�� */
#define UART_TX_ENABLE      		0x100 	/*����ʹ��*/
#define UART_RX_ENABLE      		0x200 	/*����ʹ��*/
#define UART_IRQ_CLR			0xFF 	/*��������ж�*/

#define UART_LCR_ODD                0x02 	/* ��У��ʹ��*/
#define UART_LCR_PEN_NONE	 		0x00	/* set no parity */
#define UART_LCR_STOP_1BITS			0x00	/* ֹͣλ����,1bit */

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

#define UART_RX_IRQ_CLEAR      		0x10 	/*�����ж�*/
#define UART_TIMEOUT_IRQ_CLEAR 		0x40 	/*���ճ�ʱ�ж� */

/*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_THR_INTERRUPT      0x20 	/* �����ж�	*/
#define UART_ARMIP_REV_VALID        0x10 	/* ������������Ч */
#define UART_ARMIP_REV_TIMEOUT      0x40 	/* ���ճ�ʱ    */
#define UART_IRQ_MARK				0xf0	/*�ж�����*/
#endif /* BSP_UART_H */
