#ifndef __MDRV_CCORE_ANTEN_H__
#define __MDRV_CCORE_ANTEN_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_pm_common.h>

/*����������ģʽ���á�*/
typedef enum tagGPIO_ANT_MODESET_E
{
    ANT_LTE = 0,
    ANT_GSM = 1,
    ANT_MAX
} GPIO_ANT_MODESET_E;

/*fem io ctrl type�궨��*/
typedef enum{
	CFG_RFFE_GROUP_GPIO_MIPI = 1,/*������Ƶ18002 ����fem �ܽ�*/
	CFG_RFFE_SET_PIN_NO_NV,      /*�ϲ�ܽ����ã�������nv*/
	CFG_RFFE_SET_PIN_WITH_RESUEM,
	FEMIO_CTRL_TYPE_BUTT
}FEMIO_CTRL_TYPE;

/*****************************************************************************
	 *  �� �� ��  : mdrv_anten_get_lockstate
	 *  ��������  :  ��ȡ���������ߵ�����״̬��
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_anten_get_lockstate (PWC_COMM_MODEM_E modem_id,unsigned int *status);

/*****************************************************************************
	 *  �� �� ��  : mdrv_anten_register_intr_cb
	 *  ��������  :  ���ûص����������ڻ�ȡ����״̬��
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
void mdrv_anten_register_intr_cb (PWC_COMM_MODEM_E modem_id,void* routine, int para);

/*****************************************************************************
	 *  �� �� ��  : mdrv_anten_set_outer_rfswitch
	 *  ��������  :  ���Modem������ѡ����ƽӿڡ�NASר�á�
	 *  �������  : status: 1�����Modem���߹��ܣ�
        *                                       0������Modem���߹��ܡ�
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_anten_set_outer_rfswitch (unsigned int status);

/*****************************************************************************
	 *  �� �� ��  : mdrv_anten_get_outer_rfswitch
	 *  ��������  :  ���Modem������ѡ���ѯ�ӿڡ�NASר�á�
	 *  �������  :
	 *
	 *  �������  : status: 1�����Modem���߹��ܣ�
        *                                       0������Modem���߹��ܡ�
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_anten_get_outer_rfswitch (unsigned int *status);

/*****************************************************************************
	 *  �� �� ��  : �������������������ýӿڡ�����LTE���������ߣ������ͷּ���
	 *                         �ּ����߿�����GSM���á�Gģ���Ե�������ӿ����÷ּ����߸�GSMʹ�á�
	 *                         GUDSPר�á�
	 *  ��������  :  mdrv_anten_set_mode
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_anten_set_mode (GPIO_ANT_MODESET_E status);

/*****************************************************************************
	 *  �� �� ��  : mdrv_rf_set_pin_highz
	 *  ��������  :  ������Ƶ��صĹܽ�����ֵ���ܡ�GUDSPר�á�
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_rf_set_pin_highz (unsigned char mask, unsigned char is_hz, unsigned char value);

/*****************************************************************************
	 *  �� �� ��  : mdrv_rf_enable_rse
	 *  ��������  : ���������߿��ش��ڸ��ŵ���RSE���������������ӿڣ�RSE���ܴ򿪣�GUDSPר�á�
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_rf_enable_rse (void);

/*****************************************************************************
	 *  �� �� ��  : mdrv_rf_disable_rse
	 *  ��������  :  ���������߿��ش��ڸ��ŵ���RSE���������������ӿڣ�RSE���ܹرգ�GUDSPר�á�
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_rf_disable_rse (void);



#if defined(CHIP_BB_HI6210)
static inline int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return 0;
}

#else
int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3);
#endif

#ifdef __cplusplus
}
#endif
#endif

