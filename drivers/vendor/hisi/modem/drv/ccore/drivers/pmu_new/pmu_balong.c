#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include "pmu_balong.h"
#include "pmu_pmic.h"
#include "pmu_fpga.h"

/*****************************************************************************
 函 数 名  : dummy_pmu_init
 功能描述  : 初始化默认打桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : LED模块
*****************************************************************************/
void dummy_pmu_init(void)
{
    pmu_print_error("no pmic macro defined,use dummy!\n");
}
/*****************************************************************************
 函 数 名  : dummy_info_get_handler
 功能描述  : 查询PMU版本号的打桩函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
u32 dummy_info_get_handler(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return  0;
}
char* dummy_version_get(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return NULL;
}
int dummy_sim_upres_disable(u32 para)
{
    pmu_print_info("no pmic macro defined,use dummy!\n",para);
    return  0;
}
void dummy_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    pmu_print_info("no pmic macro defined,use dummy,para is %d,%d!\n",dcxoId,value);
}
void dummy_rfclk_onoff(u32 para)
{
    pmu_print_info("no pmic macro defined,use dummy,para is %d!\n",para);
}
u32 dummy_get_rtc_value(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}
int dummy_ocp_register(int volt_id,PMU_OCP_FUNCPTR func)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}

struct pmu_adp_ops g_pmu_adpops = {
    .version_get = dummy_version_get,
    .sim_upres_disable = dummy_sim_upres_disable,
    .dcxo_compensate = dummy_dcxo_compensate,
    .rfclk_enable = dummy_rfclk_onoff,
    .rfclk_disable = dummy_rfclk_onoff,
    .get_rtc_value = dummy_get_rtc_value,
    .ocp_register = dummy_ocp_register,
};

int pmu_adpops_register(struct pmu_adp_ops *pmic_ops)
{
    if (NULL == pmic_ops)
    {
        pmu_print_error("argc is NULL check it\n");
        return BSP_ERROR;
    }
    g_pmu_adpops = *pmic_ops;

    return BSP_OK;
}

/*以下函数只在Ccore\Mcore和FASTBOOT中提供*/
/*****************************************************************************
 函 数 名  : bsp_pmu_init
 功能描述  :系统启动初始化pmu相关信号量
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :ccore系统初始化函数
*****************************************************************************/
void bsp_pmu_init(void)
{
#if defined(CONFIG_PMIC_FPGA)
    pmu_fpga_init();
#endif

#ifdef CONFIG_PMU_NEW
    pmu_pmic_init();
    pmu_dcdc_init();
#endif
}

int bsp_sim_upres_disable(u32 sim_id)
{
    return  g_pmu_adpops.sim_upres_disable(sim_id);
}
unsigned int bsp_pmu_get_rtc_value(void)
{
    return g_pmu_adpops.get_rtc_value();
}

/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取pmu版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : 集成hso，msp调用
*****************************************************************************/
char* bsp_pmu_version_get(void)
{
    return g_pmu_adpops.version_get();
}
/*****************************************************************************
*  函 数 名  : mdrv_pmu_dcxo_fre_compensate
*  功能描述  : 为dcxo设置频率补偿
*  输入参数  : value:需要设置的值
*
*  输出参数  : 无
*  返 回 值  : null
*
******************************************************************************/
void bsp_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
#ifdef CONFIG_PMIC_FPGA
    pmic_dcxo_compensate(dcxoId,value);
#else
    g_pmu_adpops.dcxo_compensate(dcxoId,value);
#endif
}
void bsp_pmu_rfclk_enable(u32 rf_id)
{
    g_pmu_adpops.rfclk_enable(rf_id);
}
void bsp_pmu_rfclk_disable(u32 rf_id)
{
    g_pmu_adpops.rfclk_disable(rf_id);
}
int bsp_pmu_ocp_register(int volt_id,PMU_OCP_FUNCPTR func)
{
    return g_pmu_adpops.ocp_register(volt_id,func);
}
#ifdef CONFIG_AVOID_RFIC6362_LDO27_LEAK
int mdrv_pmu_set_ldo27_ao(int ao)
{
	return pmic_set_ldo27_ao(ao);
}
#endif
