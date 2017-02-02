/*
 * synopsys_uart.h -- synopsys uart driver
 *
 * Copyright (C) 2014 Huawei Corporation
 *
 *
 */
#ifndef SYNOPSYS_UART_H
#define SYNOPSYS_UART_H

     /*-----------------------OFFSET OF REGISTER------------------------*/
#define	UART_REGOFF_RBR				0x00	/* UART data register (R/W) */
#define UART_REGOFF_DLL				0x00	/*UART Divisor Low bits */
#define UART_REGOFF_THR				0x00	/*UART Transmit Holding */
#define UART_REGOFF_DLH				0x04	/*UART Divisor High bits*/
#define UART_REGOFF_IER				0x04	/*Int Enable register */
#define UART_REGOFF_FCR				0x08	/*Fifo Control register(W)*/
#define UART_REGOFF_IIR				0x08	/*Int Status register(R)*/
#define UART_REGOFF_LCR				0x0C	/*UART Line Control register */
#define UART_REGOFF_MSR				0x18    /*Modem Status Register */
#define UART_REGOFF_USR				0x7C	/*UART Status register */
#define UART_REGOFF_LSR				0x14	/*UART Line Status Register*/
#define UART_FIFO_SIZE 				16  	/* FIFO SIZE*/
#define AMBA_ISR_PASS_LIMIT			128
#define UART_FIFO_MASK 				0x0F	

     /*-------------------LCR BITS FIELD-----------------------------*/
#define UART_LCR_DLS_MASK			0x03	/* ���ݳ�������*/
#define UART_LCR_DLS_5BITS			0x00	/* ���ݳ���ѡ��,5bits */
#define UART_LCR_DLS_6BITS			0x01	/* ���ݳ���ѡ��,6bits */
#define UART_LCR_DLS_7BITS			0x02	/* ���ݳ���ѡ��,7bits */
#define UART_LCR_DLS_8BITS			0x03	/* ���ݳ���ѡ��,8bits */
#define UART_LCR_STOP_2BITS			0x04	/* ֹͣλ����,2bits*/
#define UART_LCR_STOP_1BITS			0x00	/* ֹͣλ����,1bit */
#define UART_LCR_PEN_NONE	 		0x00	/* set no parity */
#define UART_LCR_PEN				0x08	/* ��żУ��ʹ��*/
#define UART_LCR_EPS				0x10	/* ��żУ��ѡ��*/
#define UART_LCR_BREAK				0x40	/* ��BREAK ���� */
#define UART_LCR_DLAB				0x80	/* ��DLL/DHL */
#define UART_LCR_DEFAULTVALUE		0x00	/* LCRĬ��ֵ*/
#define UART_LCR_BC_NORMAL			0x00	/* ��ͣ����λ ����*/
#define UART_LCR_BC_UNNORMAL		0x40	/* ��ͣ����λ ��ͣ*/
     
     /*-------------------IER BITS FIELD-----------------------------*/
#define UART_IER_IRQ_DISABLE		0x00	/* Disable both FIFOs */
#define UART_IER_LS_IRQ_ENABLE		0x04	/*Line Status Int Enable*/
#define UART_IER_TX_IRQ_ENABLE		0x02	/*Transmitter Int Enable*/
#define UART_IER_RX_IRQ_ENABLE		0x01	/*Receiver Int Enable*/
#define PTIME						(1<<7)
     
     /*-------------------LSR BITS FIELD-----------------------------*/
#define UART_LSR_DR					0x01	/* ����׼����*/
#define UART_LSR_OE					0x02	/* �����־*/
#define UART_LSR_PE					0x04	/* ��żУ������־*/
#define UART_LSR_FE					0x08	/* ֡�����־*/
#define UART_LSR_BI					0x10	/* �ж���ͣ��־*/
#define UART_LSR_THRE				0x20	/* THRΪ��*/
#define UART_LSR_TEMT				0x40	/* ���Ϳձ�־*/
#define UART_LSR_ERR_ANY (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI)
     
     /*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_REV_STA			0x06	/* ������״̬�ж�   */
#define UART_IIR_REV_VALID			0x04	/* ������������Ч */
#define UART_IIR_REV_TIMEOUT		0x0C	/* ���ճ�ʱ    */
#define UART_IIR_THR_EMPTY			0x02	/* transmit hold reg empty */
#define UART_IIR_NO_INTERRUPT		0x01	/* NO interrupt pending */
#define UART_IIR_MODEM_INTERRUPT	0x00	/* FOURTH modem int    */
     
     /*-------------------USR BITS FIELD-----------------------------*/
#define UART_USR_UART_BUSY			0x01	/* UARTæ��־   */
#define UART_USR_FIFO_NOT_FULL		0x02	/* ����FIFO������־   */
#define UART_USR_FIFO_EMP			0x04	/* ����FIFOΪ�ձ�־   */
#define UART_USR_FIFO_NOT_EMP		0x08	/* ����FIFO�ǿձ�־   */
#define UART_USR_FIFO_FULL			0x10	/* ����FIFO����־   */
     
     /*-------------------FCR BITS FIELD-----------------------------*/
#define UART_FCR_FIFO_ENABLE		0x01	/* Enable both FIFOs */
#define UART_FCR_FIFO_DISABLE		0x00	/* Disable both FIFOs */
#define UART_FCR_DEF_SET			0xB7	/* ʹ��FIFO,��λ�����뷢��FIFO�����շ���ˮ��ΪFIFO-2 */

#endif /* SYNOPSYS_UART_H */


