/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : __DRV_UART_H__
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : __DRV_UART_H__ ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _E_UART_CONSUMER_ID_
{
    CBP_UART_PORT_ID = 1,
    UART_CONSUMER_BUTT
}UART_CONSUMER_ID;

/*****************************************************************************
 �� �� ��  : DRV_UART_SEND
 ��������  : UART�ڷ�������
             ������ֻ֧������������ͬ�����������ݷ���
 �������  : uPortNo
             pDataBuffer
             uslength
 �������  : ��
 �� �� ֵ  :  0  ���ͳɹ�;  1  ����ʧ��;
 ���ú���  :
 ��������  :
*****************************************************************************/
extern int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int ulLength);
#define mdrv_dualmodem_send(uPortNo,pDataBuffer,ulLength) \
        uart_core_send(uPortNo,pDataBuffer,ulLength)
     
/*****************************************************************************
 �� �� ��  : DRV_UART_RCV_CALLBACK_REGI
 ��������  : UART�����ݽ����ϲ�Ӧ�ûص�����ע��ӿ�
 �������  : uPortNo
             pCallback

 �������  : ��
 �� �� ֵ  :  0 :ע��ɹ�;  -1 ��ע��ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
*****************************************************************************/
typedef int (*pUARTRecv)(UART_CONSUMER_ID uPortNo,unsigned char * pData, unsigned int ulLength);
extern int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback);
#define mdrv_dualmodem_register_rcvhook(uPortNo,pCallback)\
        uart_core_recv_handler_register(uPortNo,pCallback)

extern int bsp_dual_modem_drv_init(void);

#define mdrv_dual_modem_init(void)\
		bsp_dual_modem_drv_init(void)

#ifdef __cplusplus
    }
#endif

#endif

