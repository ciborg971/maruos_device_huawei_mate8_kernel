/******************************************************************************

				  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��	 : drv_mailbox.c
  �� �� ��	 : ����
  ��	��	 : ��ׯ�� 59026
  ��������	 : 2012��12��15��
  ����޸�	 :
  ��������	 : mailbox�ӿ�
  �����б�	 :

  �޸���ʷ	 :
  1.��	  ��   : 2012��12��15��
	��	  ��   : ��ׯ�� 59026
	�޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "hifi_drv_mailbox_cfg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
unsigned int mailbox_send_msg(
                unsigned int            mailcode,
                void                    *data,
                unsigned int            length);

unsigned int mailbox_reg_msg_cb(
                unsigned int             mailcode,
                mb_msg_cb                 func,
                void                     *data);

unsigned int mailbox_read_msg_data(
                void                   *mail_handle,
                 char                  *buff,
                unsigned int          *size);
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length)
{
	return mailbox_send_msg(MailCode, pData, Length);
}


unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle)
{
	return mailbox_reg_msg_cb(MailCode, pFun, UserHandle);
}


unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize)
{
	return mailbox_read_msg_data(MailHandle, (char *)pData, pSize);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

