#include <product_config.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <drv_nv_def.h>
#include <hi_anten.h>
#include <gpio_balong.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <bsp_version.h>
#include <bsp_rf_balong.h>


/*****************************************************************************
 �� �� ��  : drv_anten_lock_status_get
 ��������  : ��ȡ���������ߵ�����״̬
 �������  : none
 �������  : 0 - ��������
             1 - ��������
 �� �� ֵ  : 0 - �ɹ�
             ����Ϊʧ��

*****************************************************************************/
int mdrv_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
	return bsp_anten_get_lockstate(modem_id,status);
}


/*****************************************************************************
 �� �� ��  : drv_anten_int_install
 ��������  : �ж�ע�ắ����������õ�ǰ������״̬
 �������  : routine   - �жϴ�����
             para      - �����ֶ�
 �������  : none
 �� �� ֵ  : void

*****************************************************************************/
void mdrv_anten_register_intr_cb(PWC_COMM_MODEM_E modem_id, void* routine, int para)
{
    bsp_anten_int_install(modem_id, routine, para);
}

int mdrv_anten_set_outer_rfswitch(unsigned int status)
{   
    return bsp_anten_set_outer_rfswitch(status);
}

int mdrv_anten_get_outer_rfswitch(unsigned int *status)
{
    return bsp_anten_get_outer_rfswitch(status);
}

int mdrv_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    return bsp_anten_set_mode(mode);
}


int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return bsp_fem_ioctrl(ctrl_type,para1,para2,para3);
}

