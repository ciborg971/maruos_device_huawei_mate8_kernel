/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _BSP_PMU_H_
#define _BSP_PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
#include "mdrv_pmu.h"
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

#define PMU_INNER_INT_INVALID 99

/*PMU申请的总大小是3*1024*/
#define SHM_PMU_VOLTTABLE_SIZE 0x900
#define SHM_PMU_OCP_INFO_SIZE 0x10
#define SHM_PMU_NPREG_SIZE 0x10
#define SHM_PMU_VOLTTABLE_ADDR ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_PMU)
#define SHM_PMU_OCP_INFO_ADDR (SHM_PMU_VOLTTABLE_ADDR + SHM_PMU_VOLTTABLE_SIZE)
#define SHM_MEM_PMU_NPREG_ADDR (SHM_PMU_OCP_INFO_ADDR + SHM_PMU_OCP_INFO_SIZE)
#define SHM_MEM_PMU_OM_ADDR (SHM_MEM_PMU_NPREG_ADDR + SHM_PMU_NPREG_SIZE)

/*PMU VOLT MODE */
typedef enum  _pmu_mode_e
{
    PMU_MODE_NORMAL = 0,        /* 普通模式 */
    PMU_MODE_ECO = 1,           /* HI6451中电源的eco模式 */
    PMU_MODE_ECO_FORCE = 2,     /* HI6551/HI6559中电源的eco模式:强制进入eco模式 */
    PMU_MODE_ECO_FOLLOW = 3,    /* HI6551/HI6559中电源的eco模式:跟随pmu进入eco模式 */
    PMU_MODE_NONE = 4,          /* HI6551/HI6559中电源的模式:该路没有eco模式 */
    PMU_MODE_BUTTOM
}pmu_mode_e;

/*pmu状态宏定义，给om调用*/
#define PMU_STATE_OK    0
#define PMU_STATE_UNDER_VOL 1 << 0
#define PMU_STATE_OVER_VOL  1 << 1
#define PMU_STATE_OVER_CUR  1 << 2
#define PMU_STATE_OVER_TEMP 1 << 3

/*fastboot中提供给lcd模块开关电源*/
#ifdef __FASTBOOT__




#endif

#ifdef __KERNEL__

/*PMU 32K CLK 枚举类型 */
typedef enum  _pmu_clk_e
{
    PMU_32K_CLK_A = 0,   /*SOC睡眠时钟，其他模块不能使用*/
    PMU_32K_CLK_B,       /**/
#if defined(CONFIG_PMIC_HI6551)
    PMU_32K_CLK_C,       /*只有hi6551中有该路时钟*/
#endif
    PMU_32K_CLK_MAX
}pmu_clk_e;

/*给使用pmu中断的模块调用*/
typedef void (*pmufuncptr)(void *);
#ifdef CONFIG_PMU_NEW
typedef enum  _pmu_int_mod_e
{
    PMU_INT_POWER_KEY_1SS_PRESS    = 5,
    PMU_INT_POWER_KEY_20MS_RELEASE = 6,
    PMU_INT_POWER_KEY_20MS_PRESS   = 7,
    PMU_INT_USB_OUT                = 2,
    PMU_INT_USB_IN                 = 1 ,
    PMU_INT_SIM0_RAISE          = 24 ,
    PMU_INT_SIM0_FALL           = 25 ,
    PMU_INT_SIM0_HIGH           = 26 ,
    PMU_INT_SIM0_LOW            = 27 ,
    PMU_INT_SIM1_RAISE          = 28 ,
    PMU_INT_SIM1_FALL           = 29 ,
    PMU_INT_SIM1_HIGH           = 30 ,
    PMU_INT_SIM1_LOW            = 31 ,

    PMU_INT_BUTTOM
}pmu_int_mod_e;
#else

typedef enum  _pmu_int_mod_e
{
	PMU_INT_OTMP                   = 0,
	PMU_INT_VSYS_UNDER_DIE         = 1, /* 欠压2.5V */
	PMU_INT_VSYS_UNDER_WARNING     = 2, /* 欠压告警，6551上是2.7V，6559上是2.85V */
	PMU_INT_VSYS_OVER_6P0          = 3,
    PMU_INT_POWER_KEY_1SS_PRESS    = 4,
    PMU_INT_POWER_KEY_20MS_RELEASE = 5,
    PMU_INT_POWER_KEY_20MS_PRESS   = 6,
    PMU_INT_IRQ_OCP_SCP            = 7,
    PMU_INT_VBUS_DET_1P375_90US    = 8,
    PMU_INT_USB_OUT                = 9,
    PMU_INT_USB_IN                 = 10 ,
    PMU_INT_ALARM_A                = 11 ,
    PMU_INT_ALARM_B                = 12 ,
    PMU_INT_ALARM_C                = 13 ,
    PMU_INT_ALARM_D                = 14 ,
    PMU_INT_ALARM_E                = 15 ,
    PMU_INT_ALARM_F                = 16 ,
    PMU_INT_SIM0_IN_FALL           = 17 ,
    PMU_INT_SIM0_IN_RAISE          = 18 ,
    PMU_INT_SIM0_OUT_FALL          = 19 ,
    PMU_INT_SIM0_OUT_RAISE         = 20 ,

#ifdef CONFIG_PMIC_HI6551
    /* 21-30号中断在6551上存在，在6559上不存在 */
    PMU_INT_SIM1_IN_FALL           = 21 ,
    PMU_INT_SIM1_IN_RAISE          = 22 ,
    PMU_INT_SIM1_OUT_FALL          = 23 ,
    PMU_INT_SIM1_OUT_RAISE         = 24 ,
    PMU_INT_COUL_INT               = 25 ,   /*cl_out>cl_int时上报中断*/
    PMU_INT_COUL_OUT               = 26 ,   /*cl_out计数到81.25%上报中断*/
    PMU_INT_COUL_IN                = 27 ,   /*cl_in计数到81.25%上报中断*/
    PMU_INT_CHG_TIMER              = 28 ,   /*chg_timer计数到81.25%上报中断*/
    PMU_INT_LOAD_TIMER             = 29 ,   /*load_timer计数到81.25%上报中断*/
    PMU_INT_VBAT_INT               = 30 ,   /*vbat电压<设定的vbat_int值*/
#endif

    PMU_INT_BUTTOM
}pmu_int_mod_e;
#endif
#endif

/*DR模块，给led调用*/
#if defined(__FASTBOOT__) || defined(__KERNEL__)
/*DR相关*/
typedef enum  _dr_id_e
{
    PMU_DR01 = 1,
    PMU_DR02 ,
    PMU_DR03 ,
    PMU_DR04 ,
    PMU_DR05 ,
    DR_ID_BUTTOM
}dr_id_e;
#define PMU_DR_MIN  PMU_DR01
#define PMU_DR_MAX  PMU_DR05
typedef enum  _dr_mode_e
{
    PMU_DRS_MODE_FLA_FLASH = 0,    /*闪烁闪动模式(DR1/2/3/4/5)*/
    PMU_DRS_MODE_FLA_LIGHT ,       /*闪烁长亮模式(DR1/2/3/4/5)*/
    PMU_DRS_MODE_BRE ,       /*呼吸模式(DR3/4/5)*/
    PMU_DRS_MODE_BRE_FLASH , /*呼吸闪烁模式，高精度闪烁(DR1/2)*/
    PMU_DRS_MODE_BRE_LIGHT , /*呼吸长亮模式(DR1/2)*/
    PMU_DRS_MODE_BUTTOM
}dr_mode_e;

typedef enum  _dr_bre_time_e
{
    PMU_DRS_BRE_ON_MS = 0,    /*呼吸长亮时间(DR1/2/3/4/5)*/
    PMU_DRS_BRE_OFF_MS ,       /*呼吸长暗时间(DR1/2/3/4/5)*/
    PMU_DRS_BRE_RISE_MS ,       /*呼吸渐亮时间(DR1/2/3/4/5))*/
    PMU_DRS_BRE_FALL_MS ,       /*呼吸渐灭时间(DR1/2/3/4/5))*/
    PMU_DRS_BRE_TIME_BUTTOM
}dr_bre_time_e;

typedef struct
{
    /*unsigned int fla_feriod_us;闪烁周期时间*/
    unsigned int fla_on_us;/*闪烁点亮时间*/
    unsigned int fla_off_us;/*闪烁点亮时间*/
}DR_FLA_TIME;

typedef struct
{
    unsigned int bre_on_ms;
    unsigned int bre_off_ms;
    unsigned int bre_rise_ms;
    unsigned int bre_fall_ms;
}DR_BRE_TIME;

#define ALWAYS_ON_OFF_TIME_DR12     5000/*长亮或者长暗寄存器配置值*/
#define ALWAYS_ON_OFF_TIME_DR345    50000/*长亮或者长暗寄存器配置值*/
#define BRE_TIME_NOT_SURE    0xfffffe/*长亮或者长暗寄存器配置值*/
#define DR_VALUE_INVALIED   0xffffffff
#define DR345_START_DELAY_STEP  256
#define DR_CUR_NUMS 8   /*电流源档位都为8*/

/*error code*/
#define BSP_DR_OK              0
#define BSP_DR_ERROR          (-1)
#endif

#ifdef __KERNEL__
/*函数声明*/
/*****************************************************************************
 函 数 名  : bsp_pmu_get_boot_state
 功能描述  :系统启动时检查pmu寄存器状态，
                确认是否是由pmu引起的重启
 输入参数  : void
 输出参数  : reset.log
 返 回 值  : pmu问题或ok
 调用函数  :
 被调函数  :系统可维可测
*****************************************************************************/
int bsp_pmu_get_boot_state(void);

/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_enable
 功能描述  : 开启pmu中32k时钟
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 开启成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_enable(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_disable
 功能描述  : 关闭pmu中32k时钟
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 关闭成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_disable(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_is_enabled
 功能描述  : 查询pmu中32k时钟是否开启
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 开启或关闭
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_is_enabled(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_enable
 功能描述  : 开启pmu中xo时钟
 输入参数  : 
 输出参数  : 无
 返 回 值  : 开启成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_enable(int clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_disable
 功能描述  : 关闭pmu中xo时钟
 输入参数  : 
 输出参数  : 无
 返 回 值  : 关闭成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_disable(int clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_is_enabled
 功能描述  : 查询pmu中xo时钟是否开启
 输入参数  :
 输出参数  : 无
 返 回 值  : 开启或关闭
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_is_enabled(int clk_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取usb是否插拔状态
 输入参数  : void
 输出参数  : 无
 返 回 值  : usb插入或拔出:1:插入;0:拔出
 调用函数  :
 被调函数  : 开关机模块
*****************************************************************************/
bool bsp_pmu_usb_state_get(void);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
void bsp_pmu_irq_mask(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
void bsp_pmu_irq_unmask(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
int bsp_pmu_irq_is_masked(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_key_state_get
 功能描述  : 获取按键是否按下状态
 输入参数  : void
 输出参数  : 无
 返 回 值  : 按键是否按下:1:按下；0:未按下
 调用函数  :
 被调函数  : 开关机模块
*****************************************************************************/
bool bsp_pmu_key_state_get(void);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
int bsp_pmu_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data);
/*****************************************************************************
* 函 数 名  : bsp_dr_list_current
* 功能描述  :查询某路电流源指定档位电流。
* 输入参数  :dr_id:电流源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电流源指定档位的电流值（单位：uA）
*
*****************************************************************************/
int bsp_dr_list_current(int dr_id, unsigned selector);
/*****************************************************************************
* 函 数 名  : bsp_pmu_dr_set_mode
* 功能描述  :设置某路电流源模式。
* 输入参数  :dr_id:电流源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_dr_set_mode(int dr_id, dr_mode_e mode);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_get_mode
* 功能描述  :获取某路电流源模式。
* 输入参数  :dr_id:电流源id号；
* 输出参数  :无
* 返回值：   电流源当前模式
*
*****************************************************************************/
dr_mode_e bsp_dr_get_mode(int dr_id);
/*****************************************************************************
 函 数 名  : bsp_dr_fla_time_set
 功能描述  : 设置dr的闪烁周期时间和点亮时间
 输入参数  : dr_fla_time_st:闪烁时间参数结构体;单位:us
 输出参数  : 无
 返 回 值  : 设置成功或者失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁
             闪烁周期:reg_value*31.25ms;点亮时间:reg_value*7.8125ms
*****************************************************************************/
int bsp_dr_fla_time_set(int dr_id, DR_FLA_TIME *dr_fla_time_st);
int bsp_dr_fla_time_get(int dr_id, DR_FLA_TIME *dr_fla_time_st);

/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_set
 功能描述  : 设置dr的呼吸时间(包括长亮，长暗、渐亮、渐暗时间)
 输入参数  : dr_id:要设置的电流源编号;dr_bre_time_st:呼吸时间参数结构体;
            没有找到设置的时间，就设置为长亮
 输出参数  : 无
 返 回 值  : 设置成功或者失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁
*****************************************************************************/
int bsp_dr_bre_time_set(int dr_id, DR_BRE_TIME *dr_bre_time_st);
int bsp_dr_bre_time_get(int dr_id, DR_BRE_TIME *dr_bre_time_st);
/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_list
 功能描述  : 陈列dr的呼吸时间(包括长亮，长暗、渐亮、渐暗时间)各档位的时间值
 输入参数  : dr_id:要查询的电流源编号;bre_time_enum:所要查询的时间类型;
             selector，时间档位
 输出参数  : 无
 返 回 值  : 档位时间
 调用函数  :
 备注说明  :
*****************************************************************************/
unsigned bsp_dr_bre_time_list(int dr_id, dr_bre_time_e bre_time_enum ,unsigned selector);
/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_selectors_get
 功能描述  : 获取dr 呼吸时间总共档位值
 输入参数  : dr_id:要设置的电流源编号;bre_time_enum:所要查询的时间类型;
 输出参数  : 无
 返 回 值  : 档位时间
 调用函数  :
 备注说明  :
*****************************************************************************/
unsigned bsp_dr_bre_time_selectors_get(int dr_id, dr_bre_time_e bre_time_enum);
/*****************************************************************************
 函 数 名  : bsp_dr_start_delay_set
 功能描述  : 设置dr的启动延时时间
 输入参数  : dr_id:要设置的电流源编号;delay_ms:启动延时的时间，单位:ms
             设置范围:[0 , 32768]ms
 输出参数  : 无
 返 回 值  : 设置成功或失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁，只有DR3/4/5有此功能
*****************************************************************************/
int bsp_dr_start_delay_set(int dr_id, unsigned delay_ms);
/*****************************************************************************
 函 数 名  : bsp_pmu_sim_debtime_set
 功能描述  : 设置SIM卡中断去抖时间，单位是us。
 输入参数  : uctime:设置的去抖时间(范围是(120,600),step:30;)
 输出参数  : 设置成功或失败
 返 回 值  : 无
 调用函数  :
 被调函数  : sim卡模块
*****************************************************************************/
int bsp_pmu_sim_debtime_set(u32 uctime);
void bsp_pmu_ldo22_res_enable(void);
void bsp_pmu_ldo22_res_disable(void);
unsigned int bsp_pmu_irq_inner_id_get(pmu_int_mod_e mod);
void bsp_pmu_usbphy_ldo_set(void);

#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__) || defined(__CMSIS_RTOS)
/*****************************************************************************
 函 数 名  : bsp_pmu_init
 功能描述  : 系统启动初始化pmu相关信号量
 输入参数  : void 输出参数  : 无
 返 回 值  : 无
 调用函数  :被调函数  :ccore和mcore系统初始化相关函数
*****************************************************************************/
void bsp_pmu_init(void);
int bsp_sim_upres_disable(u32 sim_id);
#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
s32 bsp_pmu_apt_enable(void);
s32 bsp_pmu_apt_disable(void);
s32 bsp_pmu_apt_status_get(void);
s32 bsp_pmu_parf_exc_check(void);
void bsp_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
#endif

/*fastboot、a、c、mcore都提供*/
/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取pmu版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : 集成hso，msp调用
*****************************************************************************/
char* bsp_pmu_version_get(void);

#ifdef CONFIG_PMIC_HI6451

#define PMIC_HI6451_BUCK1  1
#define PMIC_HI6451_BUCK2  2
#define PMIC_HI6451_BUCK3  3
#define PMIC_HI6451_BUCK4  4
#define PMIC_HI6451_BUCK5  5
#define PMIC_HI6451_BUCK6  6
#define PMIC_HI6451_LDO1   7
#define PMIC_HI6451_LDO2   8
#define PMIC_HI6451_LDO3   9
#define PMIC_HI6451_LDO4   10
#define PMIC_HI6451_LDO5   11
#define PMIC_HI6451_LDO6   12
#define PMIC_HI6451_LDO7   13
#define PMIC_HI6451_LDO8   14
#define PMIC_HI6451_LDO9   15
#define PMIC_HI6451_LDO10  16
#define PMIC_HI6451_LDO11  17
#define PMIC_HI6451_LDO12  18
#define PMIC_HI6451_LDO13  19
#define PMIC_HI6451_LDO14  20
#define PMIC_HI6451_LDO15  21
#define PMIC_HI6451_DR1    22
#define PMIC_HI6451_DR2    23
#define PMIC_HI6451_DR3    24


#define PMIC_HI6451_REGULATOR_MIN   PMIC_HI6451_BUCK1
#define PMIC_HI6451_REGULATOR_MAX   PMIC_HI6451_DR3/*APT功能注销*/
#define PMIC_HI6451_VOLT_ECO_MIN    PMIC_HI6451_BUCK1
#define PMIC_HI6451_VOLT_ECO_MAX    PMIC_HI6451_LDO15
#define PMIC_HI6451_VOLT_MIN    PMIC_HI6451_BUCK1
#define PMIC_HI6451_VOLT_MAX    PMIC_HI6451_DR3
/*delete later*/
#define PMIC_MAX_VECO_NUM 22

/*波特率*/
#define SPI_BAUT_RATE 2000000
/*PMIC传输协议地址偏移*/
#define ADDR_BIT_OFFSET 9
/*PMIC传输协议命令偏移*/
#define CMD_BIT_OFFSET 8
#define HI6451_32K_CLK_A 1
#define HI6451_32K_CLK_B 2

typedef struct{
u8 onoff_reg_addr;
u8 onoff_bit_offset;
u8 voltage_reg_addr;
u8 voltage_bit_mask;
u8 voltage_bit_offset;
u8 voltage_nums;
u8 eco_reg_addr;
u8 eco_bit_offset;
int *voltage_list;
}PMIC_HI6451_VLTGS_ATTR;

/*函数声明*/
/*****************************************************************************
* 函 数 名  : bsp_hi6451_reg_write
* 功能描述  :写hi6451寄存器。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
int bsp_hi6451_reg_write( u8 addr, u8 value);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_reg_read
* 功能描述  :读hi6451寄存器。
* 输入参数  :addr:要操作的寄存器地址；pValue:读出的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
int bsp_hi6451_reg_read( u8 addr, u8 *pValue);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_reg_show
* 功能描述  :显示hi6451寄存器内容。
* 输入参数  :addr:要操作的寄存器地址;
* 输出参数  :读出的值
* 返回值：   无
*
*****************************************************************************/
int  bsp_hi6451_reg_show( u8 addr);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_reg_write_mask
* 功能描述  :操作寄存器的某几bit。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值;
*               mask:
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
int bsp_hi6451_reg_write_mask(u8 addr, u8 value, u8 mask);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_is_enabled
* 功能描述  :查询某路电压源是否开启。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   正数：开启；0：关闭；负数:失败
*
*****************************************************************************/
int bsp_hi6451_volt_is_enabled(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_enable
* 功能描述  :打开某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6451_volt_enable(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_disable
* 功能描述  :关闭某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6451_volt_disable(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_get_voltage
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6451_volt_get_voltage(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_set_voltage
* 功能描述  :设置某路电压源电压。
* 输入参数  :volt_id:电压源id号；min_uV：设置的最小电压；max_uV：最大电压；
* 输出参数  :selector：所设置的电压是第几档
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6451_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_set_mode
* 功能描述  :设置某路电压源模式。
* 输入参数  :volt_id:电压源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6451_volt_set_mode(int volt_id, pmu_mode_e mode);
/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_get_mode
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
pmu_mode_e bsp_hi6451_volt_get_mode(int volt_id);

/*****************************************************************************
* 函 数 名  : bsp_hi6451_volt_list_voltage
* 功能描述  :查询某路电压源指定档位电压。
* 输入参数  :volt_id:电压源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电压源指定档位的电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6451_volt_list_voltage(int volt_id, unsigned selector);

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
int bsp_pmu_hi6451_init(void);
#endif

#endif

#ifdef CONFIG_PMIC_HI6551
 #define PMIC_HI6551_BUCK0  0
 #define PMIC_HI6551_BUCK1  1
 #define PMIC_HI6551_BUCK2  2
 #define PMIC_HI6551_BUCK3  3
 #define PMIC_HI6551_BUCK4  4
 #define PMIC_HI6551_BUCK5  5
 #define PMIC_HI6551_BUCK6  6
 #define PMIC_HI6551_BOOST  7
 #define PMIC_HI6551_LDO01  8
 #define PMIC_HI6551_LDO02  9
 #define PMIC_HI6551_LDO03  10
 #define PMIC_HI6551_LDO04  11
 #define PMIC_HI6551_LDO05  12
 #define PMIC_HI6551_LDO06  13
 #define PMIC_HI6551_LDO07  14
 #define PMIC_HI6551_LDO08  15
 #define PMIC_HI6551_LDO09  16
 #define PMIC_HI6551_LDO10  17
 #define PMIC_HI6551_LDO11  18
 #define PMIC_HI6551_LDO12  19
 #define PMIC_HI6551_LDO13  20
 #define PMIC_HI6551_LDO14  21
 #define PMIC_HI6551_LDO15  22
 #define PMIC_HI6551_LDO16  23
 #define PMIC_HI6551_LDO17  24
 #define PMIC_HI6551_LDO18  25
 #define PMIC_HI6551_LDO19  26
 #define PMIC_HI6551_LDO20  27
 #define PMIC_HI6551_LDO21  28
 #define PMIC_HI6551_LDO22  29
 #define PMIC_HI6551_LDO23  30
 #define PMIC_HI6551_LDO24  31
 #define PMIC_HI6551_LVS02  32
 #define PMIC_HI6551_LVS03  33
 #define PMIC_HI6551_LVS04  34
 #define PMIC_HI6551_LVS05  35
 #define PMIC_HI6551_LVS06  36
 #define PMIC_HI6551_LVS07  37
 #define PMIC_HI6551_LVS08  38
 #define PMIC_HI6551_LVS09  39
 #define PMIC_HI6551_LVS10  40

#define PMIC_HI6551_VOLT_MIN        PMIC_HI6551_BUCK2/*buck 0/1 不能让用户操作*/
#define PMIC_HI6551_VOLT_MAX        PMIC_HI6551_LVS10
#define PMIC_HI6551_BUCK_MAX        PMIC_HI6551_BUCK6
#define PMIC_HI6551_LDO_MIN         PMIC_HI6551_LDO01
#define PMIC_HI6551_LDO_MAX         PMIC_HI6551_LDO24
#define PMIC_HI6551_LVS_MIN         PMIC_HI6551_LVS02
#define PMIC_HI6551_LVS_MAX         PMIC_HI6551_LVS10
#define PMIC_HI6551_VOLT_NUM        (PMIC_HI6551_LVS10 - PMIC_HI6551_BUCK0 + 1)

/*DR相关*/
#define PMIC_HI6551_DR01     1
#define PMIC_HI6551_DR02     2
#define PMIC_HI6551_DR03     3
#define PMIC_HI6551_DR04     4
#define PMIC_HI6551_DR05     5

typedef struct
{
    u16 enable_reg_addr;
    u16 disable_reg_addr;

    u16 is_enabled_reg_addr;
    u16 voltage_reg_addr;

    u16 eco_follow_reg_addr;
    u16 eco_force_reg_addr;

    u8 enable_bit_offset;
    u8 disable_bit_offset;
    u8 is_enabled_bit_offset;
    u8 voltage_bit_mask;

    u8 voltage_bit_offset;
    u8 voltage_nums;
    u8 eco_follow_bit_offset;
    u8 eco_force_bit_offset;

    int voltage_list[8];
}PMIC_HI6551_VLTGS_ATTR;

typedef struct
{
    unsigned long   magic_start;
    PMIC_HI6551_VLTGS_ATTR    hi6551_volt_attr[PMIC_HI6551_VOLT_MAX+1];
    unsigned long   magic_end;
} PMIC_HI6551_VLTGS_TABLE;

/*函数声明*/
/*****************************************************************************
* 函 数 名  : bsp_hi6551_reg_write
* 功能描述  :写hi6551寄存器。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void bsp_hi6551_reg_write( u16 addr, u8 value);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_reg_read
* 功能描述  :读hi6551寄存器。
* 输入参数  :addr:要操作的寄存器地址；pValue:读出的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void  bsp_hi6551_reg_read( u16 addr, u8 *pValue);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_reg_show
* 功能描述  :显示hi6551寄存器内容。
* 输入参数  :addr:要操作的寄存器地址;
* 输出参数  :读出的值
* 返回值：   无
*
*****************************************************************************/
int  bsp_hi6551_reg_show( u16 addr);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_reg_write_mask
* 功能描述  :操作寄存器的某几bit。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值;
*               mask:
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void bsp_hi6551_reg_write_mask(u16 addr, u8 value, u8 mask);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_is_enabled
* 功能描述  :查询某路电压源是否开启。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   非0：开启；0：关闭
*
*****************************************************************************/
int bsp_hi6551_volt_is_enabled(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_enable
* 功能描述  :打开某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_volt_enable(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_disable
* 功能描述  :关闭某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_volt_disable(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_get_voltage
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6551_volt_get_voltage(int volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_set_voltage
* 功能描述  :设置某路电压源电压。
* 输入参数  :volt_id:电压源id号；min_uV：设置的最小电压；max_uV：最大电压；
* 输出参数  :selector：所设置的电压是第几档
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_list_voltage
* 功能描述  :查询某路电压源指定档位电压。
* 输入参数  :volt_id:电压源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电压源指定档位的电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6551_volt_list_voltage(int volt_id, unsigned selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_set_mode
* 功能描述  :设置某路电压源模式。
* 输入参数  :volt_id:电压源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_volt_set_mode(int volt_id, pmu_mode_e mode);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_volt_get_mode
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
pmu_mode_e bsp_hi6551_volt_get_mode(int volt_id);

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
int bsp_pmu_hi6551_init(void);
#endif
/*dr相关接口，只在Acore使用*/
#if defined(__KERNEL__) || defined(__FASTBOOT__)
/*****************************************************************************
 函 数 名  : bsp_hi6551_dr_is_enabled
 功能描述  : 查询某路电流源是否开启。
 输入参数  : dr_id:电流源id号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 备注说明  : 只在Acore提供该函数实现，
*****************************************************************************/
int bsp_hi6551_dr_is_enabled(int dr_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_enable
* 功能描述  : 打开某路电流源。
* 输入参数  : dr_id:电流源id号
* 输出参数  : 无
* 返回值：    成功或失败
*
*****************************************************************************/
int bsp_hi6551_dr_enable(int dr_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_disable
* 功能描述  :关闭某路电流源　
* 输入参数  :dr_id:电流源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_dr_disable(int dr_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_get_current
* 功能描述  :获取某路电流源电流。
* 输入参数  :dr_id:电流源id号
* 输出参数  :无
* 返回值：   电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6551_dr_get_current(int dr_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_set_current
* 功能描述  :设置某路电流源电流。
* 输入参数  :dr_id:电流源id号；min_uA：设置的最小电流；max_uA：最大电流；
* 输出参数  :selector：所设置的电压是第几档
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_dr_set_current(int dr_id, int min_uA, int max_uA, unsigned *selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_list_current
* 功能描述  :查询某路电流源指定档位电流。
* 输入参数  :dr_id:电流源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电流源指定档位的电流值（单位：uA）
*
*****************************************************************************/
int bsp_hi6551_dr_list_current(int dr_id, unsigned selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_set_mode
* 功能描述  :设置某路电流源模式。
* 输入参数  :dr_id:电流源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6551_dr_set_mode(int dr_id, dr_mode_e mode);
/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_get_mode
* 功能描述  :获取某路电流源模式。
* 输入参数  :dr_id:电流源id号；
* 输出参数  :无
* 返回值：   电流源当前模式
*
*****************************************************************************/
dr_mode_e bsp_hi6551_dr_get_mode(int dr_id);

#endif
#endif

#ifdef CONFIG_PMIC_HI6559

/* 所有输出电源 */
#define PMIC_HI6559_BUCK0  0
#define PMIC_HI6559_BUCK3  1
#define PMIC_HI6559_BUCK4  2
#define PMIC_HI6559_BUCK5  3
#define PMIC_HI6559_BUCK6  4
#define PMIC_HI6559_LDO01  5
#define PMIC_HI6559_LDO03  6
#define PMIC_HI6559_LDO06  7
#define PMIC_HI6559_LDO07  8
#define PMIC_HI6559_LDO08  9
#define PMIC_HI6559_LDO09  10
#define PMIC_HI6559_LDO10  11
#define PMIC_HI6559_LDO11  12
#define PMIC_HI6559_LDO12  13
#define PMIC_HI6559_LDO13  14
#define PMIC_HI6559_LDO14  15
#define PMIC_HI6559_LDO22  16
#define PMIC_HI6559_LDO23  17
#define PMIC_HI6559_LDO24  18
#define PMIC_HI6559_LVS07  19
#define PMIC_HI6559_LVS09  20

/* 用于参数合法性检查 */
#define PMIC_HI6559_VOLT_MIN        PMIC_HI6559_BUCK0
#define PMIC_HI6559_VOLT_MAX        PMIC_HI6559_LVS09
#define PMIC_HI6559_BUCK_MAX        PMIC_HI6559_BUCK6
#define PMIC_HI6559_LDO_MIN         PMIC_HI6559_LDO01
#define PMIC_HI6559_LDO_MAX         PMIC_HI6559_LDO24
#define PMIC_HI6559_LVS_MIN         PMIC_HI6559_LVS07
#define PMIC_HI6559_LVS_MAX         PMIC_HI6559_LVS09
#define PMIC_HI6559_VOLT_NUM        (PMIC_HI6559_VOLT_MAX - PMIC_HI6559_VOLT_MIN + 1)

/*DR相关*/
#define PMIC_HI6559_DR01     1
#define PMIC_HI6559_DR02     2
#define PMIC_HI6559_DR03     3
#define PMIC_HI6559_DR04     4
#define PMIC_HI6559_DR05     5

/* 电压源的电压值档位数量 */
#define HI6559_VOLT_LIST_NUM 16

typedef struct
{
    u16 enable_reg_addr;
    u16 disable_reg_addr;

    u16 is_enabled_reg_addr;
    u16 voltage_reg_addr;

    u16 eco_follow_reg_addr;
    u16 eco_force_reg_addr;

    u8 enable_bit_offset;
    u8 disable_bit_offset;
    u8 is_enabled_bit_offset;
    u8 voltage_bit_mask;

    u8 voltage_bit_offset;
    u8 voltage_nums;
    u8 eco_follow_bit_offset;
    u8 eco_force_bit_offset;

    int voltage_list[HI6559_VOLT_LIST_NUM];
}PMIC_HI6559_VLTGS_ATTR;

typedef struct
{
    unsigned long   magic_start;
    PMIC_HI6559_VLTGS_ATTR    hi6559_volt_attr[PMIC_HI6559_VOLT_MAX + 1];
    unsigned long   magic_end;
}PMIC_HI6559_VLTGS_TABLE;

/*函数声明*/
/*****************************************************************************
* 函 数 名  :bsp_hi6559_reg_write
* 功能描述  :写hi6559寄存器。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void bsp_hi6559_reg_write( u16 addr, u8 value);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_reg_read
* 功能描述  :读hi6559寄存器。
* 输入参数  :addr:要操作的寄存器地址；pValue:读出的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void  bsp_hi6559_reg_read( u16 addr, u8 *pValue);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_reg_show
* 功能描述  :显示hi6559寄存器内容。
* 输入参数  :addr:要操作的寄存器地址;
* 输出参数  :读出的值
* 返回值：   无
*
*****************************************************************************/
s32  bsp_hi6559_reg_show( u16 addr);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_reg_write_mask
* 功能描述  :操作寄存器的某几bit。
* 输入参数  :addr:要操作的寄存器地址；value:要写入的值;
*               mask:
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void bsp_hi6559_reg_write_mask(u16 addr, u8 value, u8 mask);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_is_enabled
* 功能描述  :查询某路电压源是否开启。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   非0：开启；0：关闭
*
*****************************************************************************/
s32 bsp_hi6559_volt_is_enabled(s32 volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_enable
* 功能描述  :打开某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
s32 bsp_hi6559_volt_enable(s32 volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_disable
* 功能描述  :关闭某路电压源。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
s32 bsp_hi6559_volt_disable(s32 volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_get_voltage
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号
* 输出参数  :无
* 返回值：   电压值（单位：uV）
*
*****************************************************************************/
s32 bsp_hi6559_volt_get_voltage(s32 volt_id);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_set_voltage
* 功能描述  :设置某路电压源电压。
* 输入参数  :volt_id:电压源id号；min_uV：设置的最小电压；max_uV：最大电压；
* 输出参数  :selector：所设置的电压是第几档
* 返回值：   成功或失败
*
*****************************************************************************/
s32 bsp_hi6559_volt_set_voltage(s32 volt_id, s32 min_uV, s32 max_uV, unsigned *selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_list_voltage
* 功能描述  :查询某路电压源指定档位电压。
* 输入参数  :volt_id:电压源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电压源指定档位的电压值（单位：uV）
*
*****************************************************************************/
s32 bsp_hi6559_volt_list_voltage(s32 volt_id, unsigned selector);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_set_mode
* 功能描述  :设置某路电压源模式。
* 输入参数  :volt_id:电压源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
s32 bsp_hi6559_volt_set_mode(s32 volt_id, pmu_mode_e mode);
/*****************************************************************************
* 函 数 名  : bsp_hi6559_volt_get_mode
* 功能描述  :获取某路电压源电压。
* 输入参数  :volt_id:电压源id号；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
pmu_mode_e bsp_hi6559_volt_get_mode(s32 volt_id);

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
s32 bsp_pmu_hi6559_init(void);
s32 bsp_pmu_hi6559_apt_enable(void);
s32 bsp_pmu_hi6559_apt_disable(void);
s32 bsp_pmu_hi6559_apt_status_get(void);
s32 bsp_pmu_hi6559_parf_exc_check(void);
#endif
/*dr相关接口，只在Acore使用*/
#if defined(__KERNEL__) || defined(__FASTBOOT__)
/*****************************************************************************
 函 数 名  : bsp_hi6559_dr_is_enabled
 功能描述  : 查询某路电流源是否开启。
 输入参数  : dr_id:电流源id号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 备注说明  : 只在Acore提供该函数实现，
*****************************************************************************/
int bsp_hi6559_dr_is_enabled(int dr_id);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_enable
* 功能描述  : 打开某路电流源。
* 输入参数  : dr_id:电流源id号
* 输出参数  : 无
* 返回值：    成功或失败
*
*****************************************************************************/
int bsp_hi6559_dr_enable(int dr_id);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_disable
* 功能描述  :关闭某路电流源　
* 输入参数  :dr_id:电流源id号
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6559_dr_disable(int dr_id);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_get_current
* 功能描述  :获取某路电流源电流。
* 输入参数  :dr_id:电流源id号
* 输出参数  :无
* 返回值：   电压值（单位：uV）
*
*****************************************************************************/
int bsp_hi6559_dr_get_current(int dr_id);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_set_current
* 功能描述  :设置某路电流源电流。
* 输入参数  :dr_id:电流源id号；min_uA：设置的最小电流；max_uA：最大电流；
* 输出参数  :selector：所设置的电压是第几档
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6559_dr_set_current(int dr_id, int min_uA, int max_uA, unsigned *selector);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_list_current
* 功能描述  :查询某路电流源指定档位电流。
* 输入参数  :dr_id:电流源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电流源指定档位的电流值（单位：uA）
*
*****************************************************************************/
int bsp_hi6559_dr_list_current(int dr_id, unsigned selector);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_set_mode
* 功能描述  :设置某路电流源模式。
* 输入参数  :dr_id:电流源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_hi6559_dr_set_mode(int dr_id, dr_mode_e mode);

/*****************************************************************************
* 函 数 名  : bsp_hi6559_dr_get_mode
* 功能描述  :获取某路电流源模式。
* 输入参数  :dr_id:电流源id号；
* 输出参数  :无
* 返回值：   电流源当前模式
*
*****************************************************************************/
dr_mode_e bsp_hi6559_dr_get_mode(int dr_id);
#endif /* #if defined(__KERNEL__) || defined(__FASTBOOT__)  */
#endif /* #ifdef CONFIG_PMIC_HI6559 */

/*PMU版本号宏*/
#ifdef CONFIG_PMIC_HI6559
#define BSP_PMU_V100 0x10
#else
#define BSP_PMU_V210 0x21
#define BSP_PMU_V220 0x22
#define BSP_PMU_V230 0x23
#define BSP_PMU_V240 0x24
#endif

/*判断ddr是否被改写的魔幻数*/
#define SHM_PMU_VOLTTABLE_MAGIC_START_DATA   0xc7c7c7c7
#define SHM_PMU_VOLTTABLE_MAGIC_END_DATA     0xa6a6a6a6


/*错误码定义*/
#define BSP_PMU_ERROR   -1
#define BSP_PMU_OK      0
#define BSP_PMU_NO_PMIC      0x2001/*系统没有PMU芯片*/
#define BSP_PMU_PARA_ERROR      0x2002/*无效参数值*/
#define BSP_PMU_VOLTTABLE_ERROR      0x2003/*DDR被改写，table表被破坏*/

#define PMU_INVAILD_ADDR 0/*地址等无效值*/
#define PMU_INVAILD_DATA 0/*数据等无效值*/
#define PMU_INVAILD_OFFSET 0/*偏移等无效值*/


typedef enum  _pmic_id_e
{
#ifdef CONFIG_PMIC_HI6451
    PMIC_HI6451 ,
#endif
#ifdef CONFIG_PMIC_HI6551
    PMIC_HI6551 ,/*HI6551中电源的eco模式:强制进入eco模式*/
#endif
#ifdef CONFIG_PMIC_HI6559
    PMIC_HI6559 ,/*HI6559中电源的eco模式:强制进入eco模式*/
#endif

#ifdef CONFIG_PASTAR
	PMIC_HI6561 ,
#endif
    PMIC_BUTTOM
}pmic_id_e;


/*om log*/
/*PMU om log 枚举类型 */
typedef enum  _pmu_om_log_e
{
    PMU_OM_LOG_START = 0,   /*PMU om log*/
    PMU_OM_LOG_RESET,
    PMU_OM_LOG_EXC,       /*wifi clk */
    PMU_OM_LOG_END
}pmu_om_log_e;
#define PMU_OM_LOG            "/modem_log/log/pmu_om.log"
/*debug*/


/*函数声明*/
#if defined(__CMSIS_RTOS)
int bsp_pmu_suspend(void);
int bsp_pmu_resume(void);
int bsp_pmu_sdio_suspend(void);
int bsp_pmu_sdio_resume(void);
void bsp_pmu_volt_state_save(void);
#endif

void bsp_pmu_rfclk_enable(u32 rf_id);
void bsp_pmu_rfclk_disable(u32 rf_id);
unsigned int bsp_pmu_get_rtc_value(void);

typedef void (*PMU_OCP_FUNCPTR)(int);
int bsp_pmu_ocp_register(int volt_id,PMU_OCP_FUNCPTR func);


#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_PMU_H_*/
