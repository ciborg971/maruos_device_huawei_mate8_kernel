/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : adp_pmu_hi6561.c */
/* Version       : 2.0 */
/* Created       : 2013-05-8*/
/* Last Modified : */
/* Description   :  The C union definition file for the module LTE_PMU*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

/*lint --e{537}*/
#include "string.h"
#include "product_config.h"
#include <osl_spinlock.h>
#include "mdrv_pmu.h"
#include "mdrv_pm.h"
#include "drv_nv_def.h"
#include "bsp_mipi.h"
#include "bsp_dpm.h"
#include "bsp_pa_rf.h"
#include "bsp_hardtimer.h"
#include "bsp_regulator.h"
#include "bsp_pmu_hi6561.h"
#include "pmu_hi6561.h"
#include "bsp_gpio.h"

#ifdef CONFIG_PASTAR

/*surport for v9r1 interface*/
//extern char *err_list[];

/*lock for pa pwerctrl */
spinlock_t    pctrl_pa_lock[HI6561_BUTT];
/*lock for rf pwerctrl */
spinlock_t    pctrl_rf_lock[HI6561_BUTT];


extern NV_RFPOWER_UNIT_STRU rf_power_unit;
extern NV_PAPOWER_UNIT_STRU pa_power_unit;

/*天线开关不下电特性nv*/
extern unsigned int   sw_unpd_en;
extern int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux);

static HI6561_POWER_ID bsp_adpter_hi6561_powerid(EM_MODEM_CONSUMER_ID_E consumer_id)
{
	switch(consumer_id)
	{
		case MODEM_PA0:
		case MODEM_PA1:
			return PMU_HI6561_BUCK_PA;
		case MODEM_RFIC0_ANALOG0:
		case MODEM_RFIC1_ANALOG0:
			return PMU_HI6561_BUCK1;
		case MODEM_RFIC0_ANALOG1:
		case MODEM_RFIC1_ANALOG1:
			return PMU_HI6561_BUCK2;
		case MODEM_FEM0:
		case MODEM_FEM1:
			return PMU_HI6561_LDO1;
		case MODEM_PA_VBIAS0:
		case MODEM_PA_VBIAS1:
			return PMU_HI6561_LDO2;
		default:
			return PMU_HI6561_POWER_ID_BUTT;
	}
}

static HI6561_ID_ENUM bsp_adpter_hi6561_chipid(EM_MODEM_CONSUMER_ID_E consumer_id)
{
	switch(consumer_id)
	{
		case MODEM_PA0:
		case MODEM_RFIC0_ANALOG0:
		case MODEM_RFIC0_ANALOG1:
		case MODEM_FEM0:
		case MODEM_PA_VBIAS0:
			return HI6561_0;

		case MODEM_PA1:
		case MODEM_RFIC1_ANALOG0:
		case MODEM_RFIC1_ANALOG1:
		case MODEM_FEM1:
		case MODEM_PA_VBIAS1:
			return HI6561_1;
		default:
			return HI6561_BUTT;
	}
}


static int pmu_hi6561_config_mode(PWC_COMM_MODE_E mode_id,HI6561_ID_ENUM chip_id)
{
	int ret=MIPI_OK;
	switch(mode_id){
		case PWC_COMM_MODE_LTE :
    	case PWC_COMM_MODE_TDS :
		case PWC_COMM_MODE_WCDMA :
			/*配置buck pa的电压为3.3v*/
			ret|= pmu_hi6561_voltage_set(PMU_HI6561_BUCK_PA,3300,chip_id);

			/*关闭APT*/
			ret |= pmu_hi6561_apt_disable(chip_id);
			break;
		case PWC_COMM_MODE_GSM:

			/*BU0=3.7v*/
			ret|= pmu_hi6561_voltage_set(PMU_HI6561_BUCK_PA,3700,chip_id);

			/*关闭APT*/
			ret |= pmu_hi6561_apt_disable(chip_id);
			break;

		default:
			;

	}

	return ret;
}

/*****************************************************************************
 函 数 名  : drv_pmu_hi6561_exc_check
 功能描述  : 通信模块检查PASTAR是否有异常接口
 输入参数  : modem_id       卡号
 输出参数  : 无
 返 回 值  : BSP_OK          没有异常
             BSP_ERROR       存在异常
*****************************************************************************/
s32 drv_pmu_hi6561_exc_check(PWC_COMM_MODEM_E modem_id)
{
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

    /* 副卡PA/RF不用PAStar供电时，不去check modem1。 */
    if((pa_power_unit.papower_m1 != PA_POWER_FROM_HI6561) && 
       (rf_power_unit.rfpower_m1 != RF_POWER_FROM_HI6561) && 
       (PWC_COMM_MODEM_1 == modem_id))
    {
        return MIPI_OK;
    }
    
	if(strcmp("UNKOWN",pmu_hi6561_exc_isr((HI6561_ID_ENUM)modem_id))){
		return (BSP_S32)MIPI_ERROR;/*pmu 存在异常*/
	}

	return (BSP_S32)MIPI_OK;
}

/*****************************************************************************
 函 数 名  : drv_pmu_hi6561_voltage_set
 功能描述  : 通信模块设置电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      设置的电压值毫伏
 输出参数  : 无
 返 回 值  : BSP_OK          设置成功
             BSP_ERROR       设置失败
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_set(EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
	HI6561_POWER_ID power_id;
	HI6561_ID_ENUM chip_id;
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

	/*获取chip id / power id*/
    /* coverity[assignment] */
	chip_id = bsp_adpter_hi6561_chipid(consumer_id);
	power_id=bsp_adpter_hi6561_powerid(consumer_id);

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }

    /* coverity[overrun-call] */
    return pmu_hi6561_voltage_set(power_id, (u16)voltage_mv,chip_id);
}

/*****************************************************************************
 函 数 名  : drv_pmu_hi6561_voltage_get
 功能描述  : 通信模块获取电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      获得的电压值毫伏
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_get(EM_MODEM_CONSUMER_ID_E consumer_id, u32 *voltage_mv )
{
	HI6561_POWER_ID power_id;
	HI6561_ID_ENUM chip_id;
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;
    
	/*获取chip id / power id*/
    /* coverity[assignment] */
	chip_id = bsp_adpter_hi6561_chipid(consumer_id);
	power_id= bsp_adpter_hi6561_powerid(consumer_id);

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }    

    /* coverity[overrun-call] */
	return pmu_hi6561_voltage_get(power_id,voltage_mv,chip_id);
}

/*****************************************************************************
 函 数 名  : drv_pmu_hi6561_voltage_list
 功能描述  : 通信模块获取电压设置范围接口
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_list(EM_MODEM_CONSUMER_ID_E consumer_id, u16 **list, u32 *size)
{
	HI6561_POWER_ID power_id;
	HI6561_ID_ENUM chip_id;
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

	power_id= bsp_adpter_hi6561_powerid(consumer_id);
	chip_id = bsp_adpter_hi6561_chipid(consumer_id);

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }  

	return pmu_hi6561_voltage_list_get(power_id, list, size);
}

/*****************************************************************************
 函数	: drv_pmu_hi6561_apt_enable
 功能	: 通信模块使能APT状态接口
 输入	: modem_id       卡号
 输出	: 无
 返回	: 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_hi6561_apt_enable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    }  
    
    return pmu_hi6561_apt_enable((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 函数	: drv_pmu_hi6561_apt_disable
 功能	: 通信模块去使能APT状态接口
 输入	: modem_id       卡号
 输出	: 无
 返回	: 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_hi6561_apt_disable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    }  
    
    return pmu_hi6561_apt_disable((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 函数	: drv_pmu_hi6561_apt_status_get
 功能	: 通信模块获取当前APT状态接口
 输入	: modem_id       卡号
 输出	: 无
 返回	: 1  APT使能/   0    APT未使能/  -1    获取失败
*****************************************************************************/
s32 drv_pmu_hi6561_apt_status_get(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    } 

	return pmu_hi6561_apt_status_get((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 函数 	: drv_pmu_hi6561_mode_config
 功能	: 通信模块配置G模或W模接口
 输入	: modem_id       卡号
 输出	: 无
 返回  : BSP_OK         配置成功/  BSP_ERROR      配置失败
*****************************************************************************/
s32 drv_pmu_hi6561_mode_config(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)    
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* 副卡不使用PAStar供电，则直接返回 */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    } 
    
	return pmu_hi6561_config_mode(mode_id,(HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 函数 	: bsp_pmu_hi6561_pa_poweron
 功能	:PA 上电
 输入	: 无

 输出	: 无
 返回	: pa电源开关状态
*****************************************************************************/
int bsp_pmu_hi6561_pa_poweron(PWC_COMM_MODEM_E modem_id)
{
	int ret = MIPI_OK;
	HI6561_POWER_ID power_id1;
	HI6561_POWER_ID power_id2;
	unsigned long flags;
	u32 papower_local[PWC_COMM_MODEM_BUTT];

	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	papower_local[PWC_COMM_MODEM_0]=pa_power_unit.papower_m0;
	papower_local[PWC_COMM_MODEM_1]=pa_power_unit.papower_m1;

    if(PA_POWER_FROM_HI6561 != papower_local[modem_id])
    {
		return MIPI_OK;
    }

	power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);


	/*若电源已打开，无需重新开*/
	if(PWRCTRL_COMM_ON == bsp_pmu_hi6561_get_pa_powerstatus(modem_id)){
		ret = MIPI_OK;
		return ret;
	}

	/*加锁保护*/
	spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

	/*打开MODEM_PA*/
	ret=pmu_hi6561_power_on(power_id1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_on failed! power id=%d\n",power_id1);
		ret = MIPI_ERROR;
		goto out;
	}

	/*打开MODEM_PA_VBIAS*/
	ret=pmu_hi6561_power_on(power_id2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_on failed! power id=%d\n",power_id2);
		ret = MIPI_ERROR;
		goto out;
	}

out:
	spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
	return ret;
}

/*****************************************************************************
 函数 	: bsp_pmu_hi6561_pa_poweron
 功能	: PA 上电
 输入	: 无

 输出	: 无
 返回	: pa电源开关状态
*****************************************************************************/
int bsp_pmu_hi6561_pa_poweroff(PWC_COMM_MODEM_E modem_id)
{
	int ret = 0;
	HI6561_POWER_ID power_id1;
	HI6561_POWER_ID power_id2;
    unsigned long flags;
	u32 papower_local[PWC_COMM_MODEM_BUTT];
    
	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	papower_local[PWC_COMM_MODEM_0]=pa_power_unit.papower_m0;
	papower_local[PWC_COMM_MODEM_1]=pa_power_unit.papower_m1;

    if(PA_POWER_FROM_HI6561 != papower_local[modem_id])
    {
		return MIPI_OK;
    }

	/*电源ID转换*/
	power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);


	/*若电源已关闭，不可重复关闭*/
	if(PWRCTRL_COMM_OFF == bsp_pmu_hi6561_get_pa_powerstatus(modem_id)){
		ret = MIPI_OK;
		return ret;
	}

	/*加锁保护*/
	spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

	ret=pmu_hi6561_power_off(power_id1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_off failed! power id=%d\n",power_id1);
		ret = MIPI_ERROR;
		goto out;
	}

	ret=pmu_hi6561_power_off(power_id2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_off failed! power id=%d\n",power_id2);
		ret = MIPI_ERROR;
		goto out;
	}

out:
	spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
	return ret;

}
static int pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
	int ret = MIPI_OK;
	HI6561_POWER_ID power_id1;
	HI6561_POWER_ID power_id2;
	HI6561_POWER_ID power_id3;
	unsigned long flags;

	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}
	power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);
	power_id3=bsp_adpter_hi6561_powerid(MODEM_FEM0);

	/*若电源已打开，无需重新开*/
	if(PWRCTRL_COMM_ON == bsp_pmu_hi6561_get_rf_powerstatus(modem_id)){
		return MIPI_OK;
	}

	/*上电过程需要加锁，以免中间有关闭电源请求*/
	spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);

    /* 清除buck1/2的误报过流 */
	ret = pmu_hi6561_buck1_2_phony_exception_clear((HI6561_ID_ENUM)modem_id);
	if(MIPI_OK != ret)
    {
		mipi_print_error("Error:clear buck1/2 phony over current status failed! modem id:%d\n", modem_id);
	}
    
	/*打开MODEM_RFIC_ANALOG0*/
	ret=pmu_hi6561_power_on(power_id1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id1);
		goto out;
	}

	/*打开MODEM_RFIC_ANALOG1*/
	ret=pmu_hi6561_power_on(power_id2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id2);
		goto out;
	}

	/*打开FEM*/
	ret=pmu_hi6561_power_on(power_id3,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id3);
		goto out;
	}

	/*将天线管脚切换为功能管脚*/	
    if(sw_unpd_en && (0==modem_id)){
		/*将主分集天线开关配置为antn 功能*/
		ret = bsp_antn_sw_unpd_config(MASTER_0 , 1);
		if(ret){
			mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
		}

		ret = bsp_antn_sw_unpd_config(MASTER_1 , 1);		
		if(ret){
			mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 1,mux 0\n");
		}
	}
	
out:

	spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
	return ret;

}

static int pmu_ldo_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    unsigned long flags = 0;

	if(PWC_COMM_MODEM_1 == modem_id){
		spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);
		/*todo: 调用GPIO 123\124拉高*/
        rf_gpio_set_high();
		
		/*将天线管脚切换为功能管脚*/	
		if(sw_unpd_en){
			/*将副modem天线开关配置为antn 功能*/
			if(bsp_antn_sw_unpd_config(NAGTIVE , 1)){
				mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
			}
		
		}
		spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);

		return MIPI_OK;
	}
	else{
		mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
		return MIPI_ERROR;
	}
}
int bsp_pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

	if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*需要pastar供电*/
		return pmu_hi6561_rf_poweron(modem_id);
	}
	else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*需要ldo供电*/
		return pmu_ldo_rf_poweron(modem_id);
	}
	else{/*不需要pastar或LDO供电*/
		mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
		return MIPI_ERROR;
	}

}
static int pmu_ldo_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    unsigned long flags = 0;
	if(PWC_COMM_MODEM_1 == modem_id){
		spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);
		/*todo: 调用GPIO拉低*/
        rf_gpio_set_low();
		
		if(sw_unpd_en && (PWC_COMM_MODEM_1 == modem_id)){
			/*将副modem天线开关配置为GPIO默认态*/
			if(bsp_antn_sw_unpd_config(NAGTIVE , 0)){/*枚举*/
				mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
			}
			/*副modem天线开关不下电在gpio中实现*/
		}
		spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
		return MIPI_OK;
	}
	else{
		mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
		return MIPI_ERROR;
	}
}


static int pmu_hi6561_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
	int ret = MIPI_OK;
	HI6561_POWER_ID power_id1;
	HI6561_POWER_ID power_id2;
	HI6561_POWER_ID power_id3;
    unsigned long flags;

	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return MIPI_ERROR;
	}

	power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);
	power_id3=bsp_adpter_hi6561_powerid(MODEM_FEM0);

	/*若电源已关闭，无需重新开*/
	if(PWRCTRL_COMM_OFF == bsp_pmu_hi6561_get_rf_powerstatus(modem_id)){
		return MIPI_OK;
	}

	/*加锁保护*/
	spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);

	/*关闭RFIC_ANALOG0*/
	ret=pmu_hi6561_power_off(power_id1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id1);
		ret = MIPI_ERROR;
		goto out;
	}

	/*关闭RFIC_ANALOG1*/
	ret=pmu_hi6561_power_off(power_id2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id2);
		ret = MIPI_ERROR;
		goto out;
	}

    /* 清除buck1/2的过流标记 */
	ret = pmu_hi6561_buck1_2_real_exception_clear((HI6561_ID_ENUM)modem_id);
	if(MIPI_OK != ret)
    {
		mipi_print_error("Error:clear buck1/2 real over current status failed! modem id:%d\n", modem_id);
	}
    if(sw_unpd_en && (PWC_COMM_MODEM_0 == modem_id)){
		/*将主分集天线开关配置为GPIO默认态*/
		ret = bsp_antn_sw_unpd_config(MASTER_0 , 0);
		if(ret){
			mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
		}

		ret = bsp_antn_sw_unpd_config(MASTER_1 , 0);		
		if(ret){
			mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 1,mux 0\n");
		}
	}
	else{
		/*关闭FEM*/
		ret = pmu_hi6561_power_off(power_id3,(HI6561_ID_ENUM)modem_id);
		if(ret){
			mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id3);
			ret = MIPI_ERROR;
			goto out;
		}
	}

out:
	spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
	return ret;
}
int bsp_pmu_hi6561_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

	if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*需要pastar供电*/
		return pmu_hi6561_rf_poweroff(modem_id);
	}
	else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*需要ldo供电*/
		return pmu_ldo_rf_poweroff(modem_id);
	}
	else{/*不需要pastar或LDO供电*/
		mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
		return MIPI_ERROR;
	}

}

static PWC_COMM_STATUS_E pmu_hi6561_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{

	int ret = 0;
	HI6561_POWER_ID power_id1 = PMU_HI6561_POWER_ID_BUTT;
	HI6561_POWER_ID power_id2 = PMU_HI6561_POWER_ID_BUTT;
	HI6561_POWER_ID power_id3 = PMU_HI6561_POWER_ID_BUTT;
	PWC_COMM_STATUS_E result = PWC_COMM_STATUS_BUTT;
	unsigned long flags;
	u8 status1 = 0;
	u8 status2 = 0;
	u8 status3 = 0;

	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return PWC_COMM_STATUS_BUTT;
	}

	power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);
	power_id3=bsp_adpter_hi6561_powerid(MODEM_FEM0);

	/*加锁保护*/
	spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);
    
	ret=pmu_hi6561_power_status(power_id1,&status1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("get rf power status failed!power id is %d\n",power_id1);
		result = PWC_COMM_STATUS_BUTT;
		goto out;
	}

	ret=pmu_hi6561_power_status(power_id2,&status2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("get rf power status failed!power id is %d\n",power_id2);
		result = PWC_COMM_STATUS_BUTT;
		goto out;
	}

	ret=pmu_hi6561_power_status(power_id3,&status3,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("get rf power status failed!power id is %d\n",power_id3);
		result = PWC_COMM_STATUS_BUTT;
		goto out;
	}

	if(status1&&status2&&status3){
		result = PWRCTRL_COMM_ON;
	}
	else if(0 == (status1 | status2 | status3)){
		result = PWRCTRL_COMM_OFF;
	}
	else{
		result = PWC_COMM_STATUS_BUTT;
	}
    
out:
	spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
	return result;
}
static PWC_COMM_STATUS_E pmu_ldo_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
	/*todo:获取GPIO接口*/
	int gpio123 = ldo_gpio123_get_value();
	int gpio124 = ldo_gpio124_get_value();

	if(1==gpio123&&1==gpio124){
		return PWRCTRL_COMM_ON;
	}
	else if(0==gpio123&&0==gpio124){
		return PWRCTRL_COMM_OFF;
	}

	return PWC_COMM_STATUS_BUTT;
}
/*****************************************************************************
 函 数 名     : bsp_pmu_hi6561_get_rf_powerstatus
 功能描述  :RF 电源状态查询
 输入参数  : 无

 输出参数  :
 				PWC_COMM_STATUS_BUTT :error

 				0x10:power on
 				0x20:power off
 返 回 值  : rf电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
	u32 rfpower_local[PWC_COMM_MODEM_BUTT];

	rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
	rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

	if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*需要pastar供电*/
		return pmu_hi6561_get_rf_powerstatus(modem_id);
	}
	else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*需要ldo供电*/
		return pmu_ldo_get_rf_powerstatus(modem_id);
	}
	else{/*不需要pastar或LDO供电*/
		mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
		return PWC_COMM_STATUS_BUTT;
	}

}

/*****************************************************************************
 函 数 名     : bsp_pmu_hi6561_get_rf_powerstatus
 功能描述  :RF 电源状态查询
 输入参数  : 无

 输出参数  :
 				PWC_COMM_STATUS_BUTT :error
 				-1:error

 				0x10:power on
 				0x20:power off
 返 回 值  : pa电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id)
{
	int ret = 0;
	unsigned long flags;
	PWC_COMM_STATUS_E result=PWC_COMM_STATUS_BUTT;
	HI6561_POWER_ID power_id1 = PMU_HI6561_POWER_ID_BUTT;
	HI6561_POWER_ID power_id2 = PMU_HI6561_POWER_ID_BUTT;
	u32 papower_local[PWC_COMM_MODEM_BUTT];
	u8 status1 = 0;
	u8 status2 = 0;

	if(PWC_COMM_MODEM_BUTT<=modem_id){
		mipi_print_error("invalid param with modem id %d\n",modem_id);
		return PWC_COMM_STATUS_BUTT;
	}

	papower_local[PWC_COMM_MODEM_0]=pa_power_unit.papower_m0;
	papower_local[PWC_COMM_MODEM_1]=pa_power_unit.papower_m1;

    if(PA_POWER_FROM_HI6561 != papower_local[modem_id])
    {
		return PWC_COMM_STATUS_BUTT;
    }

	power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
	power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);
    
	/*加锁保护*/
	spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

	ret=pmu_hi6561_power_status(power_id1,&status1,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("get pa power status failed!power id is %d\n",power_id1);
		result = PWC_COMM_STATUS_BUTT;
		goto out;
	}

	ret=pmu_hi6561_power_status(power_id2,&status2,(HI6561_ID_ENUM)modem_id);
	if(ret){
		mipi_print_error("get pa power status failed!power id is %d\n",power_id2);
		result = PWC_COMM_STATUS_BUTT;
		goto out;
	}

	if(status1&&status2){
		result = PWRCTRL_COMM_ON;
	}
	else if(0 == (status1 | status2)){
		result = PWRCTRL_COMM_OFF;
	}
	else{
		result = PWC_COMM_STATUS_BUTT;
	}

out :
	spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
	return result;
}

int adp_pmu_hi6561_initial(HI6561_ID_ENUM chip_id)
{
	/*init lock*/
	spin_lock_init(&pctrl_pa_lock[chip_id]);

	spin_lock_init(&pctrl_rf_lock[chip_id]);

	/*for k3V3回片，打开副卡RF 电源*/
	//pmu_ldo_rf_poweron(PWC_COMM_MODEM_1);
	return 0;
}

/*************************************************************
 * 以下是pastar dpm相关 
 *************************************************************/
/* 记录各个模的投票信息 */
struct pastar_vote_map_stru{
     const char    *name;                   
     int            status;                 /*记录当前状态*/
     unsigned int   vote;                   /*记录投票情况*/
     unsigned int   times_count;            /*记录读时间戳次数*/
     unsigned int   enable_real;            /*记录真实开的次数*/
     unsigned int   disable_real;           /*记录真实关的次数*/
     spinlock_t     spinlock;
};

/*pastar dpm info*/
struct pastar_dpm_info_stru{
	u32 *suspend_mask;
	u32 *en_timestamp;
};
extern struct pa_rf_vote_map_stru pa_rf_vote_map[];

struct pastar_vote_map_stru pastar_vote_map = {
    .name = "pastar_pd",
    .status = 0,
    .vote = 0,
    .times_count = 0,
    .enable_real = 0,
    .disable_real = 0,
    .spinlock = {0},
};

struct regulator *pastar_regulator = NULL;
static struct pastar_dpm_info_stru pastar_dpm_info; 

#define PASTAR_WAIT_TIME     (66)   /*等待2ms*/

/*此函数用于等待pastar 来自smart star LVS5使能信号到来，2ms*/
static void check_pastar_stable_timestamp(void)
{
	unsigned int newslice = 0;

	/*判断pastar是否关闭过smart star LVS5*/
	if(*pastar_dpm_info.suspend_mask & 0x1){
		newslice = bsp_get_slice_value();
		if(get_timer_slice_delta(*(pastar_dpm_info.en_timestamp), newslice) < PASTAR_WAIT_TIME){
			do{
				newslice = bsp_get_slice_value();

				/*记录等稳定时间未到2ms后需要再读取时间戳的次数*/
				pastar_vote_map.times_count ++;
			}while(get_timer_slice_delta(*(pastar_dpm_info.en_timestamp), newslice) < PASTAR_WAIT_TIME);
		}
	}
	return;
}

/*此函数用于清除suspend中的标记和配置pastar*/
static void clear_pastar_suspend_mark_and_config(void)
{
    u32 temp = 0;
    
	/*清suspend 标记*/
	if(*(pastar_dpm_info.suspend_mask) & 0x1){
        temp = *(pastar_dpm_info.suspend_mask);
        temp &= ~(0x1);
        writel(temp, (unsigned)(pastar_dpm_info.suspend_mask));
		pmu_hi6561_reg_resume();    
	}
	return;
}

/*此函数用于关闭pastar 来自smart star LVS5 --[18]*/
static s32 pastar_suspend(struct dpm_device *dev)
{
	int ret = 0;
    u32 temp = 0;

    /* 所有供电器件都同意下电，才可以下电 */
	if(!(pa_rf_vote_map[PA0].vote || pa_rf_vote_map[PA1].vote || 
         pa_rf_vote_map[RFIC0].vote || pa_rf_vote_map[RFIC1].vote))
         {
			ret = (int)pmu_hi6561_reg_save();
			if(ret)
            {                
				return MIPI_ERROR;
            }
			check_pastar_stable_timestamp();
			clear_pastar_suspend_mark_and_config();     

			ret = regulator_disable(pastar_regulator);
			if(ret){
                temp = *(pastar_dpm_info.suspend_mask);
                temp |= (0x1 << 1);
                writel(temp, (unsigned)(pastar_dpm_info.suspend_mask));
				return MIPI_ERROR;
			}
			pastar_vote_map.disable_real ++;

			/*清读时间戳的次数*/
			pastar_vote_map.times_count = 0;
            temp = *(pastar_dpm_info.suspend_mask);
            temp |= 0x1;
            writel(temp, (unsigned)(pastar_dpm_info.suspend_mask));
	}
	return 0;
}

/*此函数用于使能pastar 来自smart star LVS5 */
static s32 pastar_resume_early(struct dpm_device *dev)
{
    u32 temp = 0;
    
	/*判断pastar是否关闭过smart star LVS5*/
	if(*(pastar_dpm_info.suspend_mask) & 0x1){
		if(0 != regulator_enable(pastar_regulator))
		{
		    /* 写共享内存最好调用writel */
		    temp = *(pastar_dpm_info.suspend_mask);
            temp |= (0x1 << 2);
            writel(temp, (unsigned)(pastar_dpm_info.suspend_mask));

			return MIPI_ERROR;
		}
		pastar_vote_map.enable_real ++;

		/*记录smart star LVS5使能的时刻点*/
        writel(bsp_get_slice_value(), (unsigned)(pastar_dpm_info.en_timestamp));
	}
	return 0;
}


static struct dpm_device pastar_dpm =
{
	.device_name = "pastar dpm",
	.suspend_late = pastar_suspend,
	.resume_early  = pastar_resume_early,
};

void  bsp_pastar_dpm_debug_init(void)   
{
	s32 ret = 0;
	int i = 0;

	/*初始化spinlock*/
	while( NULL != pastar_vote_map.name)
    {
		spin_lock_init(&pastar_vote_map.spinlock);
		i++;
	}

	pastar_regulator = regulator_get(NULL, "PA_STAR_VDD-vcc");
	if(NULL == pastar_regulator)
	{
	    mipi_print_error("pastar regulator_get is fail!\n");
	}else{
    	ret = bsp_device_pm_add(&pastar_dpm);
    	if(ret)
    	{
    		mipi_print_error("pastar dpm callback function register fail!\n");
    	}
    }

    /* 写共享内存不能直接赋值，最好调用writel。如果直接赋值，需要cache_sync */
    writel(0, (unsigned)(pastar_dpm_info.suspend_mask));
    writel(0, (unsigned)(pastar_dpm_info.en_timestamp));

	pastar_dpm_info.suspend_mask = (u32 *)(SRAM_PASTAR_DPM_INFO+PASTAR_DPM_SUSPEND_MASK_OFFSET);
	pastar_dpm_info.en_timestamp = (u32 *)(SRAM_PASTAR_DPM_INFO+PASTAR_DPM_EN_TIMESTAMP_OFFSET);

	return;
}

void debug_pastar_dpm(void)
{
	mipi_print_error("pastar suspend count: %d\n",pastar_vote_map.disable_real);
	mipi_print_error("pastar resume count : %d\n",pastar_vote_map.enable_real);
	mipi_print_error("read timestamp count: %d\n",pastar_vote_map.times_count);
	if(*(pastar_dpm_info.suspend_mask) & (0x1 << 1)){
		mipi_print_error("regulator_disable pastar failure!\n");
	}
	if(*(pastar_dpm_info.suspend_mask) & (0x1 << 2)){
		mipi_print_error("regulator_enable pastar failure!\n");
	}
	return;
}


#else


int pmu_hi6561_init_config(void)
{
	return 0;
}
int adp_pmu_hi6561_initial(HI6561_ID_ENUM chip_id)
{
	mipi_print_error("pmu hi6561 didn't build all function!\n");
	return 0;
}

int pmu_hi6561_init(void)
{
	return 0;
}

unsigned int pmu_hi6561_reg_save(void)
{
    return 0;
}

int pmu_hi6561_init_phase2(void)
{
	return MIPI_OK;
}

int pmu_hi6561_init_phase1(void)
{
	return MIPI_OK;
}

unsigned int pmu_hi6561_reg_resume(void)
{
    return 0;
}

#endif

