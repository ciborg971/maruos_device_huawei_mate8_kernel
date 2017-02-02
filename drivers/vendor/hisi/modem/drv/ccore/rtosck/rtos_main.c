/*****************************************************************************
*RTOSCKСϵͳ������ڣ����ļ��������������
*owner:xujingcui
*****************************************************************************/
#include "sre_task.h"
#include "sre_typedef.h"
#include <bsp_gic_pm.h>
#include <of.h>
#include <bsp_sysctrl.h>
#include <bsp_s_memory.h>
#include <bsp_hardtimer.h>
#include <bsp_uart.h>
#include <bsp_l2cache.h>
#include "bsp_dump.h"
#include "bsp_coresight.h"
/*Сϵͳ��Ҫ�ĺ���,��systimer��������Ҫ����*/
extern void rtosckClkStart(void);
extern void drv_entry (void);
#ifdef CONFIG_SMART_SYSTEM_MODEM
void gic_init(void)
{}
#endif


/*****************************************************************************
 �� �� ��  : SRE_HardBootInit
 ��������  : ����ϵͳ����ʱ���ã���ʼ������������Ҫ��ʹ�ܵ�Ӳ��ģ��;
             ����Ҫ���ʴ�׮
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

*****************************************************************************/
#ifdef BSP_CONFIG_HI3650
extern u32 g_reset_flag;
#endif

#ifdef DRV_BUILD_GCOV
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

void __libc_init_array (void)
{
    unsigned int i     = 0;
    unsigned int count = __init_array_end - __init_array_start;

    for (i = 0; i < count; i++)
        __init_array_start[i]();
}
#endif

VOID SRE_HardBootInit()
{
#ifdef DRV_BUILD_GCOV
    __libc_init_array();
#endif

#ifdef BSP_CONFIG_HI3650
    g_reset_flag = 0;
    SRE_ExcRegHook(dump_exc_hook_earlier);
#endif

	(void)bsp_dts_init();



    l2cache_HardBootInit();


	return;
}

/*****************************************************************************
 �� �� ��  : SRE_HardDrvInit
 ��������  : ����ϵͳ����ʱ���ã���ʼ����Ҫ������Ҫʹ�ܵ�ģ�飬��UART,timer
 �������  : ��
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

*****************************************************************************/
UINT32 SRE_HardDrvInit(VOID)
{

    /*ӳ��gic�ռ�*/
    gic_init();
    /*��ʼ��serial*/
    bsp_serial_init();
    return SRE_OK;
}

/*****************************************************************************
 �� �� ��  : SRE_AppInit
 ��������  : ����ϵͳ���ڵ��ã���������һ��������ȼ������񣬳�ʼ����ģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

*****************************************************************************/

UINT32 SRE_AppInit()
{
    TSK_HANDLE_T       uwTaskUsrInitId;
    TSK_INIT_PARAM_S stTaskUsrInit={0};
    UINT32 uwRet;
    stTaskUsrInit.pfnTaskEntry = (TSK_ENTRY_FUNC)drv_entry;
    stTaskUsrInit.uwStackSize  = 0x4000;
    stTaskUsrInit.usTaskPrio    = 0;
    stTaskUsrInit.pcName        = "drv_entry";
    stTaskUsrInit.usQNum        = 0;
    stTaskUsrInit.uwStackAddr  = 0;
    dt_sysctrl_init();
	bsp_shared_mem_init();
	bsp_timer_iomap_and_clk_cfg();
    /*��ʼ��timer*/
    rtosckClkStart();

    uwRet = SRE_TaskCreate(&uwTaskUsrInitId, &stTaskUsrInit);
    if (SRE_OK != uwRet)
    {
        return uwRet;
    }
    return SRE_OK;
}

