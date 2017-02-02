#include <hi_syssc_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 �� �� ��  : power_off_reboot_operation
 ��������  : pmu rst ϵͳ����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void power_off_reboot_operation( void )
{
/* p531 FPGA��λ��Ҫͬʱ��λF1/BBP/RF */
#ifdef BSP_CONFIG_P531_FPGA
extern void p531_fpga_reset(void);
	p531_fpga_reset();
#endif

	hi_syssc_pmu_reboot();

    /* coverity[no_escape] */
    while(1);
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
    power_off_reboot_operation();
}

#ifdef __cplusplus
}
#endif