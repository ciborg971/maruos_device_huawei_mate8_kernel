/* drv_entry.c - ccore initialization routine
ά��ģ��: sysboot
�޸����ģ�鸺����review
DESCRIPTION
Initialize user application code.
*/
/*lint --e{534,752} */
#include <product_config.h>
#include <osl_thread.h>
#include <osl_bio.h>
#include <mem_balong.h>
#include <bsp_sysctrl.h>
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_hardtimer.h>
#include <bsp_clk.h>
#include <bsp_dpm.h>
#include <bsp_softtimer.h>
#include <bsp_regulator.h>
#include <bsp_cpufreq.h>
#include <bsp_wdt.h>
#include <bsp_edma.h>
#include <bsp_bbp.h>
#include <bsp_abb.h>

#include <bsp_dsp.h>
#include <bsp_dspload.h>
#include <bsp_hkadc.h>
#include <bsp_hw_spinlock.h>
#include <bsp_i2c.h>
#include <bsp_leds.h>
#include <bsp_onoff.h>
#include <bsp_spi.h>
#include <bsp_version.h>
#include <ddm_phase.h>
#include <efuse_balong.h>
#include <bsp_gpio.h>
#include <power_com.h>
#include <bsp_rfile.h>
#include <bsp_socp.h>
#include <bsp_dump.h>
#include <bsp_nvim.h>
#include <bsp_sci.h>
#include <bsp_om.h>
#include <hi_uart.h>
#include <bsp_sram.h>
#include <bsp_ipf.h>
#include <bsp_psam.h>
#include <board_fpga.h>
#include <bsp_amon.h>
#include <bsp_reset.h>
#include <bsp_dual_modem.h>
#include <bsp_pmu.h>
#include <bsp_s_memory.h>
#include <bsp_memmap.h>
#include <bsp_sysctrl.h>
#include <bsp_dump_mem.h>
#include <bsp_vic.h>
#include <bsp_dual_modem.h>
#include <cpuidle_balong.h>
#include <bsp_misc.h>
#include <bsp_mipi.h>
#include <bsp_pmu_hi6561.h>
#include <bsp_pa_rf.h>
#include <bsp_cshell.h>
#include <bsp_cipher.h>
#include <bsp_udi.h>
#include <tcxo_balong.h>
#include <bsp_hwadp.h>
#include <bsp_pm.h>
#include <bsp_wakelock.h>
#include <bsp_pinctrl.h>
#include <cpuidle_balong.h>
#include <bsp_pm_om.h>
#include <bsp_rf_balong.h>
#ifdef CONFIG_DYNAMIC_LOAD
#include <dynamic_load.h>
#endif
#include <bsp_coresight.h>
#include <board_fpga.h>
#include <bsp_cross_mipi.h>
#include <bsp_wp.h>
#include <bsp_pdlock.h>
#include <bsp_xmailbox.h>
#include <c_sys_bus_core.h>

/* ��������Ų�� */
#ifdef FEATURE_TLPHY_MAILBOX
extern void bsp_mailbox_init(void);
#endif

extern void bsp_dump_mem_debug_init(void);

#ifdef __OS_RTOSCK__
/*****************************************************************************
 �� �� ��  : text_segment_protection_enable
 ��������  : ���ڴ���α�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

*****************************************************************************/
void text_segment_protection_enable(void)
{
extern unsigned int __text_start;
extern unsigned int __text_end;
extern unsigned int __data_start;
extern unsigned int __PT_START;
    u32 uwRet;
    u32 text_start = (u32)(&__text_start);
    u32 text_end = (u32)(&__text_end);
    u32 data_start = (u32)(&__data_start);
    u32 data_end = (u32)(&__PT_START);
    OS_MEM_PT_STATE os_mem_info;
    

    /*����������Ϣ*/
    SRE_Printf("============================================================\n");
    SRE_Printf("==.text start:0x%x, end:0x%x, len=%d\n", text_start, text_end, (text_end - text_start));

    /*������ݶ���Ϣ*/
    SRE_Printf("==.data start:0x%x, end:0x%x, len=%d\n", data_start, data_end, (data_end - data_start));

    /*�����ڴ�ش�С*/
    SRE_Printf("== RealMemPool start:0x%x, end:0x%x, len=%d\n", data_end, (DDR_MCORE_ADDR + DDR_MCORE_SIZE), ((DDR_MCORE_ADDR + DDR_MCORE_SIZE) - data_end));

    /*�����ڴ�*/
    if(SRE_OK == SRE_MemPtStateGet(0, &os_mem_info))
    {
        SRE_Printf("== OsMemFreeSize:%d, OsTotalMemSize:%d\n", os_mem_info.uwFreeSize, os_mem_info.uwPtSize);
    }

    /*���ô����ֻ����ִ������*/
    uwRet = SRE_MmuStateSet(text_start, (text_end - text_start), 0, MMU_STATE_ROX | OS_MMU_STATE_CACHE_WBWA);
    if(uwRet){
        SRE_Printf("==.text segment protection set fail,ret = 0x%x .\n",uwRet);
        return;
    }
    SRE_Printf("==.text segment protection is enabled.\n");

    SRE_Printf("=============================================================\n");
}

#endif

extern signed int mailbox_init();

/*�˺����ڵ���Сϵͳ*/
#ifdef CONFIG_SMART_SYSTEM_MODEM
void drv_entry (void)
{
    SRE_Printf("8-8-8-8-smart-system-run-ok-8-8-8-8\n");
}
#else

void bsp_drivers_init()
{
/***********************����ģ���ʼ��***************************/


	/* pm_omģ��dump��ʼ��, ����dump mem��ʼ�� */
	(void)bsp_pm_om_dump_init();

    bsp_clk_init();

	bsp_wakelock_init();
	bsp_dpm_init();

    (void)bsp_wp_init();
	bsp_timer_init();

    (void)bsp_udi_init();
	(void)bsp_vic_init();

    bsp_ipc_init();

    (void)bsp_dump_init_phase2();

	(void)bsp_icc_init();


#ifdef CONFIG_K3V3_CLK_CRG /*CONFIG_K3V3_CLK_CRG*/
    gps_refclk_icc_read_cb_init();
#endif
	/* Cshell init if magic number is set to PRT_FLAG_EN_MAGIC_M */
	if(cshell_init())
		bsp_trace(0,0,"cshell_init fail\n");

#ifdef CONFIG_NVIM
     if(0 != bsp_nvm_init())
        bsp_trace(0,0,"nv init fail\n",0,0,0,0,0,0);
#endif

    /* axi monitor��س�ʼ�� */
    (void)bsp_amon_init();

	/*�˳�ʼ�����������MSP/OAM/PS��ʼ��֮ǰ���벻Ҫ����Ķ�˳��*/
    (void)tcxo_init_configure();

    if(0 != bsp_rfile_init())
       bsp_trace(0,0,"rfile init fail\n",0,0,0,0,0,0);

	/* version inits */
    bsp_productinfo_init();

    hwspinlock_init();

    bsp_hkadc_init();

    bsp_version_init();

	hwadp_init();

	(void)bsp_softtimer_init();

#ifdef CONFIG_BALONG_EDMA
    if(0 != bsp_edma_init())
    {
       //logMsg("edma init fail \n",0,0,0,0,0,0);
     }
#endif

    /*C core init ipc module*/
    (void)socp_init();

	(void)bsp_dual_modem_init();

/***********************����ģ���ʼ��***************************/
    bsp_dsp_init();

#ifdef CONFIG_CBBE
    dsp_load_init();
#endif

    bsp_bbp_init();/*�˴���Ҫ����dsp��ʼ��֮�󣬷���pastar/abb֮ǰ*/

    board_fpga_init();

    (void)bsp_gpio_init();

    bsp_pmu_init();
	regulator_init();
#ifdef CONFIG_PA_RF
    (void)bsp_pa_rf_init();   /* ������regulator_init */
#endif
#ifdef CONFIG_MIPI
    bsp_mipi_init();
#endif

    bsp_cross_mipi_init();

#ifdef CONFIG_MODEM_PINTRL
	modem_pinctrl_init();
#endif

    bsp_rffe_init();    /* ������regulator ��mipi*/
#ifdef CONFIG_PASTAR
	/*�˺�����λ�ò���������ƶ���Ϊpastar�ϵ���ṩ�㹻���ȶ�ʱ��*/
    pmu_hi6561_init_phase1();
#endif

    (void)bsp_watchdog_init();

#ifdef CONFIG_CCORE_I2C
	(void)bsp_i2c_initial();
#endif

#ifdef CONFIG_EFUSE
	(void)efuse_init();
#endif

#ifdef CONFIG_LEDS_CCORE
    (void)bsp_led_init();
#endif

/***********************ͨ��֧��ģ���ʼ��***************************/
	(void)cipher_init();

#ifdef CONFIG_IPF
    if(0 != ipf_init())
        bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IPF, "ipf init fail\n");
#endif

#ifdef CONFIG_PSAM
    if(0 != psam_init())
        bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IPF, "psam ccore init fail\n");
#endif

#ifdef CONFIG_MODULE_BUSSTRESS
	 ipf_ul_stress_test_start(10);
#endif

#ifdef FEATURE_TLPHY_MAILBOX
    bsp_mailbox_init();
#endif

    bsp_xmailbox_init();

#ifdef CONFIG_HIFI_MAILBOX

    mailbox_init();
#endif

#ifdef CONFIG_ANTEN
    (void)bsp_anten_init();
#endif
#ifdef CONFIG_MEM
	bsp_mem_init();
#endif
	bsp_sci_cfg_init();

    bsp_abb_init();

    /* Զ��ʱ��:����A��IPʹ�ã�Դͷ��C�˿��� */
	bsp_remote_clk_init();

    bsp_on_off_init();

	(void)cpufreq_init();

#ifdef CONFIG_CCORE_BALONG_PM
    balong_pm_init();
#endif

#ifdef CONFIG_BALONG_MODEM_RESET
	bsp_reset_init();
#endif

#ifdef CONFIG_PASTAR
	/*��!�˴���Ҫ�����ڸú������ȷ��pastar�ϵ���ȶ��󣬽��г�ʼ������*/
	pmu_hi6561_init_phase2();
#endif

	/* yangzhi for sc file 2014-10-11 */
    bsp_sc_init();

	/* pm_omģ��log��ʼ��, ����ipc��nv */
	(void)bsp_pm_om_log_init();

    sys_bus_core_init();

#ifdef __OS_RTOSCK__
	text_segment_protection_enable();
#endif

#ifdef CONFIG_DYNAMIC_LOAD
    bsp_dload_init( );
#endif
	SRE_Printf("+-+-+-+-bsp_drivers_init finish+-+-+-+-\n");
}

/******************************************************************************
*
* drv_entry - initialize the users application
*/

void drv_entry (void)
{
/* !!!!ע��: C�˸�ģ���������ʼ��ͳһ�ŵ�bsp_drivers_init�У���Ҫ�ŵ����� */
    ddm_phase_boot_score("start bsp_om_init",__LINE__);
    (void)bsp_dump_mem_init();
	dmesg_init();
    bsp_coresight_init();
    (void)bsp_pdlock_init();
    (void)bsp_dump_init();
    ddm_phase_boot_score("end bsp_om_init",__LINE__);

	power_on_c_status_set(POWER_OS_OK);

    //board_fpga_init();

    ddm_phase_boot_score("start bsp_drivers_init",__LINE__);
    bsp_drivers_init();
	power_on_c_status_set(POWER_BSP_OK);
    ddm_phase_boot_score("end bsp_drivers_init",__LINE__);

#ifndef DRV_BUILD_SEPARATE
extern void root(void);
    ddm_phase_boot_score("start root",__LINE__);
    bsp_dump_mem_debug_init();
    root();
	power_on_c_status_set(POWER_MSP_OK);   /* ���ݷ���ֵ���� */
    ddm_phase_boot_score("end root",__LINE__);
#endif

	/*ԭ��taskdelay(2)������porting��������ʱ����BSP_PromptSet��û���˳���������ʱ�޸�Ϊ20*/
    osl_task_delay(20);

    SRE_IdleHookAdd(cpu_idle);

    bsp_dump_init_task_name();

    SRE_Printf("+-+-+-+-sysbootinit finish+-+-+-+-\n");
}
#endif

