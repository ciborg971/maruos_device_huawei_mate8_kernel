
#ifdef __cplusplus
extern "C"
{
#endif
#include <product_config.h>

#ifdef CONFIG_PA_RF
#include <of.h>
#include <mdrv_pm.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_shared_ddr.h>
#include <bsp_pa_rf.h>
#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include <bsp_pmu_hi6561.h>
#include <bsp_nvim.h>
#include "pa_rf_balong.h"
#include <tcxo_balong.h>

#define PA_RF_VOLT_NUM  MODEM_PA1

u32 g_channel_max_num = 0;  /* 最大channel数量 */
int s_is_gpa_usepmu = 1;    /* GPA是否使用PMU供电，还是电池供电；默认使用pmu，可根据NV定制 */

struct pmu_parf_ops pmu_parf_ops;

#ifndef CONFIG_PASTAR

#define NV_PARF_SWITCH_DEFAULT_VAL  ((1<<MODEM_PA0)|(1<<MODEM_RFIC0_ANALOG0)\
                                    |(1<<MODEM_RFIC0_ANALOG1)|(1<<MODEM_FEM0)|(1<<MODEM_PA_VBIAS0))


struct parf_power_ctrl_s parf_power_ctrl[PA_RF_VOLT_NUM]={
    [MODEM_PA0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_PA_VCC,
        },
    [MODEM_RFIC0_ANALOG0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RFIC_FRONT_VCC,
        },
    [MODEM_RFIC0_ANALOG1] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RFIC_VCC,
        },
    [MODEM_FEM0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RF_FEM_VCC,
        },
    [MODEM_PA_VBIAS0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_PA_VBIA2_VCC,
        },
};

/*
 * 以下是针对PMU芯片的适配
 */

s32 pmu_power_on(EM_MODEM_CONSUMER_ID_E power_id)
{
    s32 ret = 0;

    if(parf_power_ctrl[power_id].is_exist)
    {
        ret = regulator_enable(parf_power_ctrl[power_id].regulator);
    }
    else
    {
        parf_power_ctrl[power_id].status_stub = 1;
    }

    return ret;
}
s32 pmu_power_off(EM_MODEM_CONSUMER_ID_E power_id)
{
    s32 ret = 0;

    if(parf_power_ctrl[power_id].is_exist)
    {
        ret = regulator_disable(parf_power_ctrl[power_id].regulator);
    }
    else
    {
        parf_power_ctrl[power_id].status_stub = 0;
    }

    return ret;
}

s32 pmu_is_poweron(EM_MODEM_CONSUMER_ID_E power_id)
{
    return parf_power_ctrl[power_id].is_exist \
              ? regulator_is_enabled(parf_power_ctrl[power_id].regulator) \
              : parf_power_ctrl[power_id].status_stub;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_get_pa_powerstatus
 功能描述  : 获取pa上下电状态
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    s32 status1, status2;
    PWC_COMM_STATUS_E result = PWC_COMM_STATUS_BUTT;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    status1 = pmu_is_poweron(MODEM_PA0);
    status2 = pmu_is_poweron(MODEM_PA_VBIAS0);

    if(status1 && status2)
    {
        result = PWRCTRL_COMM_ON;
    }
    else if(0 == (status1 | status2))
    {
        result = PWRCTRL_COMM_OFF;
    }
    else
    {
        result = PWC_COMM_STATUS_BUTT;
    }

    return result;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_pa_poweron
 功能描述  : 给pa上电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_pa_poweron(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = PARF_OK;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PARF_ERROR;
    }

    ret = pmu_power_on(MODEM_PA0) | pmu_power_on(MODEM_PA_VBIAS0);
    if(ret)
    {
        parf_print_error("ERROR: enable pa failed, ret %d \n", ret);
        return ret;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_pa_poweroff
 功能描述  : 给pa下电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_pa_poweroff(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = PARF_OK;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PARF_ERROR;
    }

    /* 711 LDO12与USB共用，此处不能关掉，需要考虑兼容方案? */
    ret = pmu_power_off(MODEM_PA0);/* | pmu_power_off(MODEM_PA_VBIAS0);*/
    if(ret)
    {
        parf_print_error("ERROR: disable pa failed, ret %d \n", ret);
        return ret;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_get_rf_powerstatus
 功能描述  : 获取rf上下电状态
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    s32 status1, status2, status3;
    s32 result = 0;

    /* bbstar只支持modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    status1 = pmu_is_poweron(MODEM_RFIC0_ANALOG0);

    status2 = pmu_is_poweron(MODEM_RFIC0_ANALOG1);

    status3 = pmu_is_poweron(MODEM_FEM0);

    if(status1 && status2 && status3)
    {
        result = PWRCTRL_COMM_ON;
    }
    else if(0 == (status1 | status2 | status3))
    {
        result = PWRCTRL_COMM_OFF;
    }
    else
    {
        result = PWC_COMM_STATUS_BUTT;
    }

    return (PWC_COMM_STATUS_E)result;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_rf_poweron
 功能描述  : 给rf上电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = OK;

    /* bbstar只支持modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return BSP_PMU_ERROR;
    }

    ret = pmu_power_on(MODEM_RFIC0_ANALOG0)\
        | pmu_power_on(MODEM_RFIC0_ANALOG1)\
        | pmu_power_on(MODEM_FEM0);

    if(ret)
    {
        parf_print_error("ERROR: rf power on failed, ret %d \n", ret);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : bsp_pmu_rf_poweroff
 功能描述  : 给rf下电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = OK;

    /* bbstar只支持modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return BSP_PMU_ERROR;
    }

    ret = pmu_power_off(MODEM_RFIC0_ANALOG0)\
        | pmu_power_off(MODEM_RFIC0_ANALOG1)\
        | pmu_power_off(MODEM_FEM0);

    if(ret)
    {
        parf_print_error("ERROR: rf power off failed, ret %d \n", ret);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : drv_pmu_parf_exc_check
 功能描述  : 通信模块检查pa/rf供电是否有异常
 输入参数  : modem_id       卡号
 输出参数  : 无
 返 回 值  : 0          没有异常
             1          存在异常
             -1         参数错误
*****************************************************************************/
s32 drv_pmu_parf_exc_check(PWC_COMM_MODEM_E modem_id)
{
    /* 参数检查 */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    return bsp_pmu_parf_exc_check();
}

/*****************************************************************************
 函 数 名  : drv_pmu_modem_voltage_set
 功能描述  : 通信模块设置电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      设置的电压值毫伏
 输出参数  : 无
 返 回 值  : 0          设置成功
             else       设置失败
*****************************************************************************/
s32 drv_pmu_modem_voltage_set(EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
    s32 ret = 0;

    /* 参数检查 */
    if(consumer_id >= PA_RF_VOLT_NUM)
    {
        parf_print_error("ERROR: invalid consumer_id %d\n", consumer_id);
        return ERROR;
    }

    if(parf_power_ctrl[consumer_id].is_exist)
    {
        ret = regulator_set_voltage(parf_power_ctrl[consumer_id].regulator, (s32)voltage_mv * 1000, (s32)voltage_mv * 1000);
    }
    else
    {
        parf_print_error("ERROR: regulator %s is not exist\n", parf_power_ctrl[consumer_id].name);
        ret = -1;
    }

    if(ret)
    {
        parf_print_error("ERROR: regulator_set_voltage failed, ret = %d\n", ret);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : drv_pmu_modem_voltage_get
 功能描述  : 通信模块获取电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      获得的电压值毫伏
 输出参数  : 无
 返 回 值  : 0          获取成功
             else       获取失败
*****************************************************************************/
s32 drv_pmu_modem_voltage_get( EM_MODEM_CONSUMER_ID_E consumer_id, u32 *voltage_mv )
{
    s32 ret = OK;

    /* 参数检查 */
    if(consumer_id >= PA_RF_VOLT_NUM)
    {
        parf_print_error("ERROR: invalid consumer_id %d\n", consumer_id);
        return ERROR;
    }

    if(!voltage_mv)
    {
        parf_print_error("ERROR: null pointer of vlotage_mv\n");
        return ERROR;
    }

    /* 获取电压值，并转换为mv */
    if(parf_power_ctrl[consumer_id].is_exist)
    {
        *voltage_mv = (u32)regulator_get_voltage(parf_power_ctrl[consumer_id].regulator) / 1000;
    }
    else
    {
        parf_print_error("ERROR: regulator %s is not exist\n", parf_power_ctrl[consumer_id].name);
        *voltage_mv = 0;
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : drv_pmu_modem_voltage_list
 功能描述  : 通信模块获取电压设置范围接口
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : 0          获取成功
             else       获取失败
*****************************************************************************/
s32 drv_pmu_modem_voltage_list(EM_MODEM_CONSUMER_ID_E consumer_id,u16 **list, u32 *size)
{
    /* 上层没有调用，此处直接返回ERROR */
    return PARF_OK;
}

/*****************************************************************************
 函数    : drv_pmu_modem_apt_enable
 功能    : 通信模块使能APT状态接口
 输入    : modem_id       卡号
          mode_id        模式
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_modem_apt_enable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* 参数检查 */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_enable();
}

/*****************************************************************************
 函数    : drv_pmu_modem_apt_disable
 功能    : 通信模块去使能APT状态接口
 输入    : modem_id       卡号
          mode_id        模式
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_modem_apt_disable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* 参数检查 */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_disable();
}

/*****************************************************************************
 函数    : drv_pmu_modem_apt_status_get
 功能    : 通信模块获取当前APT状态接口
 输入    : modem_id       卡号
          mode_id        模式
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_modem_apt_status_get(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* 参数检查 */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_status_get();
}

/*****************************************************************************
 函数     : drv_pmu_modem_mode_config
 功能    : 通信模块配置G模或W模接口
 输入    : modem_id       卡号
          mode_id        模式
 输出    : 无
 返回  : 0         配置成功/  else      配置失败
*****************************************************************************/
s32 drv_pmu_modem_mode_config(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    s32 ret = OK;

    /* 参数检查 */
    if(modem_id > PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return ERROR;
    }

    switch(mode_id){
        case PWC_COMM_MODE_LTE :
        case PWC_COMM_MODE_TDS :
        case PWC_COMM_MODE_WCDMA :
            if(parf_power_ctrl[MODEM_PA0].is_exist)
            {
                /* 配置buck pa的电压为3.3v */
                ret|= regulator_set_voltage(parf_power_ctrl[MODEM_PA0].regulator,3300000,3300000);
            }
            /* 关闭APT */
            ret |= bsp_pmu_apt_disable();

			/* set RFIC0_ANALOG0 1.8V */
            if(parf_power_ctrl[MODEM_RFIC0_ANALOG0].is_exist)
            {
                ret |= regulator_set_voltage(parf_power_ctrl[MODEM_RFIC0_ANALOG0].regulator,1800000,1800000);
            }
            break;

        case PWC_COMM_MODE_GSM:
            if(parf_power_ctrl[MODEM_PA0].is_exist)
            {
                /* 配置buck pa的电压为3.7v */
                ret|= regulator_set_voltage(parf_power_ctrl[MODEM_PA0].regulator,3700000,3700000);
            }
            /* 关闭APT */
            ret |= bsp_pmu_apt_disable();

			/* set RFIC0_ANALOG0 2.2V */
            if(parf_power_ctrl[MODEM_RFIC0_ANALOG0].is_exist)
            {
                ret |= regulator_set_voltage(parf_power_ctrl[MODEM_RFIC0_ANALOG0].regulator,2200000,2200000);
            }
            break;

        default:
            ;
    }

    return ret;
}

s32 parf_regulator_register(NV_DRV_PARF_SWITCH_STRU switchs)
{
	u32 ret = PARF_OK;
	u32 i = 0;

	/* 根据NV配置，获取regulator */
	for(i=0; i<PA_RF_VOLT_NUM; i++)
	{
		parf_power_ctrl[i].is_exist = 1 & (switchs.cont.u32>>i);
		if(parf_power_ctrl[i].is_exist)
		{
			parf_power_ctrl[i].regulator = regulator_get(NULL, parf_power_ctrl[i].name);
			if(NULL == parf_power_ctrl[i].regulator)
			{
				parf_print_error("ERROR: regulator_pmu%d get regulator failed %d\n", i);
				ret |= (1U << i);
			}
		}
	}

	if(ret != PARF_OK)
	{
		return (s32)ret;
	}

	return PARF_OK;
}

#endif

/*
 * 以下是对外提供的接口，包括DRV接口和dpm流程接口
 */

/*****************************************************************************
 函 数 名  : DRV_PASTAR_EXC_CHECK
 功能描述  : 通信模块检查PASTAR是否有异常接口
 输入参数  : modem_id       卡号
 输出参数  : 无
 返 回 值  : 0          没有异常
             else       存在异常
*****************************************************************************/
int mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id)
{
    return pmu_parf_ops.drv_pastar_exc_check(modem_id);
}

/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_SET
 功能描述  : 通信模块设置电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      设置的电压值毫伏
 输出参数  : 无
 返 回 值  : 0          设置成功
             else       设置失败
*****************************************************************************/
int mdrv_pmu_set_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned int voltage_mv)
{
    return pmu_parf_ops.drv_modem_voltage_set(consumer_id,voltage_mv);
}

/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_GET
 功能描述  : 通信模块获取电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      获得的电压值毫伏
 输出参数  : 无
 返 回 值  : 0          获取成功
             else       获取失败
*****************************************************************************/
int mdrv_pmu_get_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned int *voltage_mv)
{
    return pmu_parf_ops.drv_modem_voltage_get(consumer_id, voltage_mv);
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_list_voltage
 功能描述  : 通信模块获取电压设置范围接口
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : 0          获取成功
             else       获取失败
*****************************************************************************/
int mdrv_pmu_list_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned short **list, unsigned int *size)
{
    return pmu_parf_ops.drv_modem_voltage_list(consumer_id, list, size);
}

/*****************************************************************************
 函数    : mdrv_pmu_enable_apt
 功能    : 通信模块使能APT状态接口
 输入    : modem_id       卡号
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
int mdrv_pmu_enable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_enable(modem_id, mode_id);
}

/*****************************************************************************
 函数    : mdrv_pmu_disable_apt
 功能    : 通信模块去使能APT状态接口
 输入    : modem_id       卡号
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
int mdrv_pmu_disable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_disable(modem_id, mode_id);
}

/*****************************************************************************
 函数    : mdrv_pmu_get_aptstatus
 功能    : 通信模块获取当前APT状态接口
 输入    : modem_id       卡号
 输出    : 无
 返回    : 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
int mdrv_pmu_get_aptstatus(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_status_get(modem_id, mode_id);
}

/*****************************************************************************
 函数     : mdrv_pmu_set_modem_mode
 功能    : 通信模块配置G模或W模接口
 输入    : modem_id       卡号
 输出    : 无
 返回  : 0         配置成功/  else      配置失败
*****************************************************************************/
int mdrv_pmu_set_modem_mode(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_mode_config(modem_id, mode_id);
}

/*****************************************************************************
 函 数 名  : bsp_pa_poweron
 功能描述  : 给pa上电
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pa_poweron(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_on(modem_id);
}

/*****************************************************************************
 函 数 名  : bsp_pa_poweroff
 功能描述  : 给pa下电
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pa_poweroff(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_off(modem_id);
}

/*****************************************************************************
 函 数 名  : bsp_get_pa_powerstatus
 功能描述  : 获取pa上下电状态
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_status(modem_id);
}

/*****************************************************************************
 函 数 名  : bsp_rf_poweron
 功能描述  : 给rf上电
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_on(modem_id);
}

/*****************************************************************************
 函 数 名  : bsp_rf_poweroff
 功能描述  : 给rf下电
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_off(modem_id);
}

/*****************************************************************************
 函 数 名  : bsp_get_rf_powerstatus
 功能描述  : 获取rf上下电状态
 输入参数  : @modem_id - 0:主卡 1:副卡
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_status(modem_id);
}

/*
 * 给dpm提供的接口
 */
struct pa_rf_vote_map_stru pa_rf_vote_map[PA_RF_ID_MAX] = {
    {"PA0_pd", 0, 0,{0},{0},0,0,{0}},
    {"PA1_pd", 0, 0,{0},{0},0,0,{0}},
    {"RFIC0_pd", 0, 0,{0},{0},0,0,{0}},
    {"RFIC1_pd", 0, 0,{0},{0},0,0,{0}}
};

ST_PWC_SWITCH_STRU g_nv_pwc_switch_data = {0};

s32 parf_get_dts_info(u32 *channel_max_num)
{
    struct device_node *node = NULL;
    s32 ret = PARF_OK;

    if(!channel_max_num)
    {
        parf_print_error("ERROR: null pointer!\n");
        return PARF_ERROR;
    }

    /* 读取DTS节点 */
    node = of_find_compatible_node(NULL, NULL, "hisilicon,pa_rf");/*[false alarm]:这行代码不是dead code*/
    if (!node)
    {
        parf_print_error("ERROR: pa_rf dts node not found!\n");
        return PARF_ERROR;
    }

    /* 获取channel数量 */
    ret = of_property_read_u32(node, "channel_max_num", channel_max_num);
    if(ret)
    {
        parf_print_error("ERROR: read channel_max_num from dts failed, ret = %d!\n", ret);
        return ret;
    }

    return PARF_OK;
}

void parf_ops_register(void)
{
#ifdef CONFIG_PASTAR
    pmu_parf_ops.pmu_pa_power_on = bsp_pmu_hi6561_pa_poweron;
    pmu_parf_ops.pmu_pa_power_off = bsp_pmu_hi6561_pa_poweroff;
    pmu_parf_ops.pmu_pa_power_status = bsp_pmu_hi6561_get_pa_powerstatus;
    pmu_parf_ops.pmu_rf_power_on = bsp_pmu_hi6561_rf_poweron;
    pmu_parf_ops.pmu_rf_power_off = bsp_pmu_hi6561_rf_poweroff;
    pmu_parf_ops.pmu_rf_power_status = bsp_pmu_hi6561_get_rf_powerstatus;
    pmu_parf_ops.drv_pastar_exc_check = drv_pmu_hi6561_exc_check;
    pmu_parf_ops.drv_modem_voltage_set = drv_pmu_hi6561_voltage_set;
    pmu_parf_ops.drv_modem_voltage_get = drv_pmu_hi6561_voltage_get;
    pmu_parf_ops.drv_modem_voltage_list = drv_pmu_hi6561_voltage_list;
    pmu_parf_ops.drv_modem_apt_enable = drv_pmu_hi6561_apt_enable;
    pmu_parf_ops.drv_modem_apt_disable = drv_pmu_hi6561_apt_disable;
    pmu_parf_ops.drv_modem_apt_status_get = drv_pmu_hi6561_apt_status_get;
    pmu_parf_ops.drv_modem_mode_config = drv_pmu_hi6561_mode_config;
#else
    pmu_parf_ops.pmu_pa_power_on = bsp_pmu_pa_poweron;
    pmu_parf_ops.pmu_pa_power_off = bsp_pmu_pa_poweroff;
    pmu_parf_ops.pmu_pa_power_status = bsp_pmu_get_pa_powerstatus;
    pmu_parf_ops.pmu_rf_power_on = bsp_pmu_rf_poweron;
    pmu_parf_ops.pmu_rf_power_off = bsp_pmu_rf_poweroff;
    pmu_parf_ops.pmu_rf_power_status = bsp_pmu_get_rf_powerstatus;
    pmu_parf_ops.drv_pastar_exc_check = drv_pmu_parf_exc_check;
    pmu_parf_ops.drv_modem_voltage_set = drv_pmu_modem_voltage_set;
    pmu_parf_ops.drv_modem_voltage_get = drv_pmu_modem_voltage_get;
    pmu_parf_ops.drv_modem_voltage_list = drv_pmu_modem_voltage_list;
    pmu_parf_ops.drv_modem_apt_enable = drv_pmu_modem_apt_enable;
    pmu_parf_ops.drv_modem_apt_disable = drv_pmu_modem_apt_disable;
    pmu_parf_ops.drv_modem_apt_status_get = drv_pmu_modem_apt_status_get;
    pmu_parf_ops.drv_modem_mode_config = drv_pmu_modem_mode_config;
#endif
    return;
}

int bsp_pa_rf_dpm_init(void)
{
    s32 i = 0;
    u32 ret = PARF_OK;

    /*初始化spinlock*/
    for(i = 0; i < PA_RF_ID_MAX; i++)
    {
        spin_lock_init(&pa_rf_vote_map[i].spinlock);
    }

    ret = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&g_nv_pwc_switch_data), sizeof(ST_PWC_SWITCH_STRU));
    if(ret != NV_OK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, "ERROR: bsp_nvm_read failed, ret = %d\n", ret);
        return (int)ret;
    }

    return PARF_OK;
}

/*****************************************************************************
 函 数 名  : bsp_pa_rf_init
 功能描述  : 获取regulator
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:成功；else - 失败。失败时返回值的bit0~bit4对应获取失败的regulator_pmu id
*****************************************************************************/
s32 bsp_pa_rf_init(void)
{
    s32 ret = PARF_OK;

#ifdef CONFIG_PASTAR
#else
    NV_DRV_PARF_SWITCH_STRU switchs;
    ret = (s32)bsp_nvm_read(NV_ID_DRV_PA_RF_SWITCH, (u8*)&switchs, sizeof(NV_DRV_PARF_SWITCH_STRU));
    if(ret)
    {
        switchs.cont.u32= NV_PARF_SWITCH_DEFAULT_VAL;
        parf_print_error("ERROR: bsp_nvm_read failed %d,set to default %#x\n", ret, switchs.cont.u32);
    }
    s_is_gpa_usepmu = switchs.cont.bits.gpa;
    /* regulator注册 */
    ret = parf_regulator_register(switchs);
    if(ret != PARF_OK)
    {
        parf_print_error("parf_regulator_register failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }
#endif

    /* 获取支持的最大通道数 */
    ret = parf_get_dts_info(&g_channel_max_num);
    if(ret != PARF_OK)
    {
        parf_print_error("parf_get_dts_info failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }

    /* dpm功能初始化 */
    ret = bsp_pa_rf_dpm_init();
    if(ret != PARF_OK)
    {
        parf_print_error("bsp_pa_rf_dpm_init failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }

    /* ops注册 */
    parf_ops_register();

    /* 初始化ok */
    parf_print_always("pa_rf init ok\n");

    return PARF_OK;
}

/*底层软件实现PA的上电PA0--[0]PA1--[1]*/
int bsp_pa_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    int ret = PARF_OK;

    /* GPA使用电池供电，不操作PMU */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return 0;
    }
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? PA0 : PA1;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].enable_count[enCommMode] ++;
    pa_rf_vote_map[sub_scripts].enable_real ++;

    ret = bsp_pa_poweron(enModemId);
    if(!(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode)))   /* 投上电票 */
    {
        pa_rf_vote_map[sub_scripts].vote |= ((unsigned int)1 << enCommMode);
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

int bsp_pa_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    unsigned int drx_pa_pd;
    int ret = PARF_OK;

    /* GPA使用电池供电，不操作PMU */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return 0;
    }

    /* 区分主卡副卡 */
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? PA0 : PA1;
    drx_pa_pd = (enModemId == PWC_COMM_MODEM_0) ? g_nv_pwc_switch_data.drx_pa0_pd : g_nv_pwc_switch_data.drx_pa1_pd;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].disable_count[enCommMode] ++;   /* 调用接口的次数累加 */

    if(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode))  /* 去掉上电票，同意下电 */
    {
        pa_rf_vote_map[sub_scripts].vote &= ~((unsigned int)1 << enCommMode);
    }

    if(!pa_rf_vote_map[sub_scripts].vote)   /* 各个模都同意下电，才可以下电 */
    {
        /*根据NV来决定最终是否关闭*/
        if (drx_pa_pd == 0)
        {
            pa_rf_vote_map[sub_scripts].disable_real ++;    /* 实际下电的次数累加 */
            ret = bsp_pa_poweroff(enModemId);
        }
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    /* GPA使用电池供电，直接返回上电状态 */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return PWRCTRL_COMM_ON;
    }
    return bsp_get_pa_powerstatus(enModemId);
}

/*底层软件实现RFIC的上电RFIC0--[2] RFIC1--[3]*/
int bsp_rfic_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    int ret = PARF_OK;

    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? RFIC0 : RFIC1;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].enable_count[enCommMode] ++;
    pa_rf_vote_map[sub_scripts].enable_real ++;

    if(RFIC1 == sub_scripts)    /* 对于副卡rf的特殊处理 */
    {
        bsp_pmu_tcxo1_en_enable(RFIC1_ID_0);
    }

    ret = bsp_rf_poweron(enModemId);
    if(!(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode)))
    {
        pa_rf_vote_map[sub_scripts].vote |= ((unsigned int)1 << enCommMode);
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}
int bsp_rfic_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    unsigned int drx_pa_pd;
    int ret = PARF_OK;

    /* 区分主副卡 */
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? RFIC0 : RFIC1;
    drx_pa_pd = (enModemId == PWC_COMM_MODEM_0) ? g_nv_pwc_switch_data.drx_rfic0_pd : g_nv_pwc_switch_data.drx_rfic1_pd;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].disable_count[enCommMode] ++;   /* 调用接口的次数累加 */

    if(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode))  /* 去掉上电票，同意下电 */
    {
        pa_rf_vote_map[sub_scripts].vote &= ~((unsigned int)1 << enCommMode);
    }

    if(!pa_rf_vote_map[sub_scripts].vote)   /* 各个模都同意下电，才可以下电 */
    {
        /* 根据NV来决定最终是否关闭 */
        if (drx_pa_pd == 0)
        {
            pa_rf_vote_map[sub_scripts].disable_real ++;        /* 实际下电的次数累加 */
            ret = bsp_rf_poweroff(enModemId);
            if(RFIC1 == sub_scripts)
            {
                bsp_pmu_tcxo1_en_disable(RFIC1_ID_0);
            }
        }
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return bsp_get_rf_powerstatus(enModemId);
}

/*****************************************************************************
* 函 数    : bsp_fem_power_down
* 功 能    : fem 下电打桩
* 输 入    : 无
* 输 出    :
* 返 回    : rf电源开关状态
* 说 明    :
*****************************************************************************/
int bsp_fem_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
/*****************************************************************************
 函数    : bsp_fem_power_up
 功能    : RF 上电打桩
 输入    : 无
 输出    : 无
 返回    : rf电源开关状态
*****************************************************************************/
int bsp_fem_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
/*****************************************************************************
 函 数 名  :bsp_pa_power_status
 功能描述  :RF电源状态查询打桩
 输入参数  :
 输出参数  :
 返 回 值  : pa电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return PWRCTRL_COMM_ON;
}

int bsp_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

int bsp_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
#else
#include <osl_types.h>
#include <mdrv_pmu.h>
#include <mdrv_pm.h>
#include "pa_rf_balong.h"
u32 g_channel_max_num = 0;  /* 最大channel数量 */

/*
 * 以下是打桩接口，只有当PASTAR和PMU都不编译时，才会用到这些接口
 */

s32 bsp_pa_rf_init(void)
{
    parf_print_error("NOTICE: pa_rf_init stub!\n");
    return (s32)PARF_OK;
}

#endif

#ifdef __cplusplus
}
#endif
