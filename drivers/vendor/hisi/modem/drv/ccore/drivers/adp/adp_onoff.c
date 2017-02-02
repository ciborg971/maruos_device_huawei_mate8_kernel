#include "osl_types.h"
#include "osl_wait.h"
//#include "drv_onoff.h"
#include "power_com.h"
#include "bsp_sram.h"
#include "bsp_icc.h"
#include "bsp_onoff.h"
#include <mdrv_sysboot.h>

#include <product_config.h>

#ifndef CONFIG_ONOFF

static stPowCtrl g_pwrctrl;


/*****************************************************************************
 �� �� ��  : power_on_c_status_set
 ��������  : ���C��״̬
 �������  : power_on_c_status_set
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_on_c_status_set(c_power_st_e val)
{
    power_info_s *pw_st = (power_info_s *)(SRAM_REBOOT_ADDR);

    pw_st->c_power_state = (u32)val;
}

/*****************************************************************************
 �� �� ��  : bsp_start_mode_get
 ��������  : ����C�˻�ȡ����ģʽ,ͨ���˼����, ������ʱ�������ȡ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
DRV_START_MODE_E mdrv_sysboot_get_bootmode( void )
{
    return 1;
}

/*****************************************************************************
 �� �� ��  : drv_shut_down
 ��������  : ����C�˽��йػ�����,ͨ���˼����
 �������  : �ػ�ԭ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void mdrv_sysboot_shutdown( DRV_SHUTDOWN_REASON_E enReason )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/*****************************************************************************
 �� �� ��  : drv_shut_down
 ��������  : ����C�˽��йػ�����,ͨ���˼����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void mdrv_sysboot_poweroff( void )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : Ӧ�õ�������ʱ���ã�at+cfun=6
********************************************************************************/
void bsp_drv_power_reboot( void )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/*****************************************************************************
 �� �� ��  : bsp_on_off_init
 ��������  : C�˿��ػ���ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_on_off_init( void )
{
    g_pwrctrl.is_init = 1;

    return BSP_OK;
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot_direct
*  Description:
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : ֱ������
********************************************************************************/
void bsp_drv_power_reboot_direct( void )
{
    return;
}

#endif

/* ����GPIO ���뿪���ж��Ƿ�����Э��ջ���� */
unsigned int mdrv_sysboot_check_startps(void)
{
	return ~DRV_NOT_START_UMTS;
}



