/*
 * Copyright (C) 2012-2015 HUAWEI
 * Author: L J H
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LINUX_HI6521_CHARGER_H
#define _LINUX_HI6521_CHARGER_H

#include <soc_scharger_interface.h>
/*#include <dev_scharger_v200.h>*/
#include <huawei_platform/log/hw_log.h>

#define HI6521_EVENT_UNKOWN                   (0x00)
#define HI6521_NO_CHARGER_SOURCE              (0x00)
#define HI6521_VBUS_STAT_UNKNOWM              (0x00)
#define HI6521_NOT_CHARGING                   (0x10)
#define HI6521_START_CHARGING                 (0x20)
#define HI6521_START_AC_CHARGING              (0x30)
#define HI6521_START_USB_CHARGING             (0x40)
#define HI6521_CHARGE_DONE                    (0x50)
#define HI6521_STOP_CHARGING                  (0x60)
#define POWER_SUPPLY_STATE_FAULT              (0x70)
#define POWER_SUPPLY_OVERVOLTAGE              (0x80)
#define POWER_SUPPLY_WEAKSOURCE               (0x90)
#define HI6521_RESET_TIMER                    (0x38)
#define HI6521_VBUS_OVP_BITMASK                   (0xF7)

#define HI6521_LCD_LDO_OCP_EVENT		(0x10)

#define HI6521_NO_CLR_LDO_OCP                   ~(1 << 2)
#define HI6521_OPEN_LDO_TO_OCP_TIME             500
#define HI6521_LCD_LDO_OCP_LIMIT_NUM            10
#define HI6521_LCD_LDO_OCP_CLEAR_BIT            (1 << 2)
#define SCHG_BOOST1_ID 0
#define SCHG_BOOST2_ID 1
#define SCHG_BOOST3_ID 2
#define SCHG_SOURCE1_ID 3
#define SCHG_SOURCE2_ID 4
#define SCHG_BOOST4_ID 5
#define SCHG_LDO3_ID 6
#define SCHG_CPN1_ID 7
#define SCHG_LDO1_ID 8
#define SCHG_LDO2_ID 9

/*for backup battery parameters*/
#define BACKUP_EXIST_MIN_MV                    (1700)
#define BACKUP_EXIST_MAX_MV                    (1900)
#define HKADC9                                 (9)


/*status reg0*/
#define CHG_STATUS0                     	(SOC_SCHARGER_STATUS0_ADDR(0))
#define CHG_STATUS0_OTG_ON              	(1 << SOC_SCHARGER_STATUS0_otg_on_START)
#define CHG_STATUS0_STAT_NOT_CHARGING   	(0 << SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_STATUS0_STAT_PRE_CHARGING   	(1 << SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_STATUS0_STAT_FAST_CHARGING  	(2 << SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_STATUS0_STAT_CHAEGE_DONE    	(3 << SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_STATUS0_STAT_MASK_BIT       	(3 << SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_STATUS0_WDT_TIMER_OUT       	(0 << SOC_SCHARGER_STATUS0_wdt_time_out_n_START)
#define CHG_STATUS0_WDT_TIMER_OUT_MASK_BIT  (1 << SOC_SCHARGER_STATUS0_wdt_time_out_n_START)
#define CHG_STATUS0_BUCK_VSYS_STAT          (1 << SOC_SCHARGER_STATUS0_buck_vsys_stat_2d_START)

/*status reg1*/
#define CHG_STATUS1                     	(SOC_SCHARGER_STATUS1_ADDR(0))
#define CHG_STATUS1_OTMP_150                (1 << SOC_SCHARGER_STATUS1_otmp_150_r_START)
#define CHG_STATUS1_OTMP_JREG               (1 << SOC_SCHARGER_STATUS1_otmp_jreg_r_START)
#define CHG_STATUS1_VBUS_OVP_6P5V       	(1 << SOC_SCHARGER_STATUS1_vbus_ovp_6p5v_r_START)

/*status reg4*/
#define CHG_STATUS4                 		(SOC_SCHARGER_STATUS4_ADDR(0))

/*status reg5*/
#define CHG_STATUS5                     	(SOC_SCHARGER_STATUS5_ADDR(0))
#define CHG_STATUS5_VBAT_OVP            	(1 << SOC_SCHARGER_STATUS5_vbat_ovp_r_START)
#define CHG_STATUS5_OTG_OVP_5P3V            (1 << SOC_SCHARGER_STATUS5_otg_ovp_5p3v_r_START)
/*buck_reg4*/
#define INPUT_SOURCE_REG           	 		(SOC_SCHARGER_BUCK_REG4_ADDR(0))
#define HI6521_VINDPM_SHIFT          		(SOC_SCHARGER_BUCK_REG4_buck_dpm_sel_START)
#define VINDPM_MIN_3880              		(3880)
#define VINDPM_3960                  		(3960)
#define VINDPM_4040                  		(4040)
#define VINDPM_4120                  		(4120)
#define VINDPM_4200                  		(4200)
#define VINDPM_4280                  		(4280)
#define VINDPM_4360                  		(4360)
#define VINDPM_4440                  		(4440)
#define VINDPM_4520                  		(4520)
#define VINDPM_4600                  		(4600)
#define VINDPM_4680                  		(4680)
#define VINDPM_4760                  		(4760)
#define VINDPM_4840                  		(4840)
#define VINDPM_4920                  		(4920)
#define VINDPM_5000                  		(5000)
#define VINDPM_MAX_5080              		(5080)
#define VINDPM_STEP_80               		(80)

#define IINLIM_100                    		(100)
#define IINLIM_150                    		(150)
#define IINLIM_500                    		(500)
#define IINLIM_900                    		(900)
#define IINLIM_1000                  		(1000)
#define IINLIM_1200                  		(1200)
#define IINLIM_1500                  		(1500)
#define IINLIM_1600                  		(1600)
#define IINLIM_1800                  		(1800)
#define IINLIM_2000                  		(2000)
#define IINLIM_2200                  		(2200)
#define IINLIM_2500                  		(2500)

/*BUCK_REG3 config vsys min*/
#define VSYS_MIN_CONFIG_REG        			(SOC_SCHARGER_BUCK_REG3_ADDR(0))
#define SYS_MIN_MIN_3550             		(3550)
#define SYS_MIN_3650                 		(3650)
#define SYS_MIN_3750                 		(3750)
#define SYS_MIN_MAX_3850             		(3850)
#define SYS_MIN_STEP_100             		(100)
#define HI6521_SYS_MIN_SHIFT         		(SOC_SCHARGER_BUCK_REG3_buck_sysmin_sel_START)
#define BUCK_DMD_OFFSET              		(4)

/*onff reg config power on*/
#define POWER_ON_CONFIG_REG00        		(SOC_SCHARGER_ONFF0_ADDR(0))
#define POWER_ON_CONFIG_REG01       		(SOC_SCHARGER_ONFF1_ADDR(0))
#define CHG_POWER_EN                 		(1)
#define CHG_POWER_DIS                		(0)

/*fast current Control Register CHG_REG1 (default 0x13-2000mA,step 100mA,range 100mA-2000mA)  */
#define CHG_FAST_CURRENT_REG    			(SOC_SCHARGER_CHG_REG1_ADDR(0))
#define CHG_FAST_ICHG_SHIFT     			(SOC_SCHARGER_CHG_REG1_chg_fast_ichg_START)
#define CHG_FAST_ICHG_MIN       			(100)
#define CHG_FAST_ICHG_MAX       			(2000)
#define CHG_FAST_ICHG_VALUE(x)  			(x)
#define CHG_FAST_ICHG_STEP_100  			(100)

/*fast voltage threhold and term current threhold  Register CHG_REG2*/
#define CHG_FAST_VOL_TERM_CUR_REG        	(SOC_SCHARGER_CHG_REG2_ADDR(0))
#define CHG_FAST_VCHG_MIN       			(3800)
#define CHG_FAST_VCHG_MAX       			(4550)
#define CHG_FAST_VCHG_VALUE(x)  			(x)
#define CHG_FAST_VCHG_STEP_50   			(50)

#define CHG_TERM_ICHG_MIN       			(50)
#define CHG_TERM_ICHG_100MA     			(100)
#define CHG_TERM_ICHG_150MA     			(150)
#define CHG_TERM_ICHG_MAX       			(200)
#define CHG_TERM_ICHG_STEP_50   			(50)


/*pre voltage and current and batfet control Register CHG_REG0*/
#define CHG_PRE_VOL_CURRENT_BATFET_REG  	(SOC_SCHARGER_CHG_REG0_ADDR(0))
#define CHG_PRE_VCHG_MIN           			(2800)
#define CHG_PRE_VCHG_3000MV        			(3000)
#define CHG_PRE_VCHG_3100MV        			(3100)
#define CHG_PRE_VCHG_MAX           			(3200)

#define CHG_PRG_ICHG_MIN           			(100)
#define CHG_PRG_ICHG_200MA         			(200)
#define CHG_PRG_ICHG_300MA         			(300)
#define CHG_PRG_ICHG_MAX           			(400)
#define CHG_PRG_ICHG_STEP_100      			(100)

#define CHG_BATFET_EN              			(1)
#define CHG_BATFET_DIS             			(0)

/*pre timer and recharge voltage/timer*/
#define CHG_PRE_TIMER_RECHG_VOL_TIMER_REG 	(SOC_SCHARGER_CHG_REG3_ADDR(0))
#define CHG_PRE_TIMER_MIN          			(30)
#define CHG_PRE_TIMER_45MIN        			(45)
#define CHG_PRE_TIMER_60MIN        			(60)
#define CHG_PRE_TIMER_MAX          			(75)
#define CHG_PRE_TIMER_STEP_15MIN   			(15)

#define CHG_RECHG_TIMER_MIN        			(100)
#define CHG_RECHG_TIMER_1000MS     			(1000)
#define CHG_RECHG_TIMER_2000MS     			(2000)
#define CHG_RECHG_TIMER_MAX        			(4000)

#define CHG_RECHG_VOL_HYS_MIN         		(50)
#define CHG_RECHG_VOL_HYS_VALUE_MV(x) 		(x)
#define CHG_RECHG_VOL_HYS_MAX         		(400)
#define CHG_RECHG_VOL_STEP_50MV       		(50)

/*fast safe timer and charge termination ctrl and irvbat adj*/
#define CHG_FAST_SAFE_TIMER_TERM_CTRL_REG 	(SOC_SCHARGER_CHG_REG4_ADDR(0))
#define CHG_FAST_SAFE_TIMER_MIN    			(5)
#define CHG_FAST_SAFE_TIMER_8H     			(8)
#define CHG_FAST_SAFE_TIMER_12H    			(12)
#define CHG_FAST_SAFE_TIMER_MAX    			(20)

#define CHG_VBATIR_ADJ_MIN         			(10)
#define CHG_VBATIR_ADJ_VALUE_MV(x)  		(x)
#define CHG_VBATIR_ADJ_MAX         			(160)
#define CHG_VBATIR_ADJ_STEP_10MV   			(10)

#define CHG_TERMINATION_EN         			(1)
#define CHG_TERMINATION_DIS        			(0)

/*irq status register*/
#define CHG_IRQ_REG0             			(SOC_SCHARGER_IRQ0_ADDR(0))
#define CHG_IRQ0_VBUS_OVP_6P5V_R 			(1 << SOC_SCHARGER_IRQ0_vbus_ovp_6p5v_r_START)
#define CHG_IRQ0_VBUS_FAST_CHG_FAULT 	    (1 << SOC_SCHARGER_IRQ0_fast_chg_fault_r_START)
#define CHG_IRQ0_VBUS_PRE_CHG_FAULT 	    (1 << SOC_SCHARGER_IRQ0_pre_chg_fault_r_START)
#define CHG_IRQ0_VBUS_TRICKLE_CHG_FAULT 	(1 << SOC_SCHARGER_IRQ0_trickle_chg_fault_r_START)

#define CHG_IRQ_REG1           	  			(SOC_SCHARGER_IRQ1_ADDR(0))
#define CHG_IRQ1_WLED_OVP_38V     			(1 << SOC_SCHARGER_IRQ1_wled_ovp_38v_r_START)
#define CHG_IRQ1_WLED_OVP_4P5V    			(1 << SOC_SCHARGER_IRQ1_wled_ovp_4p5v_r_START)
#define CHG_IRQ1_WLED_UVP         			(1 << SOC_SCHARGER_IRQ1_wled_uvp_r_START)
#define CHG_IRQ1_WLED_SCP         			(1 << SOC_SCHARGER_IRQ1_wled_scp_r_START)
#define CHG_IRQ1_BUCK_SCP                   (1 << SOC_SCHARGER_IRQ1_buck_scp_r_START)

#define CHG_IRQ_REG2           				(SOC_SCHARGER_IRQ2_ADDR(0))
#define CHG_IRQ2_FLASH_BST_UVP  			(1 << SOC_SCHARGER_IRQ2_flash_bst_uvp_r_START)
#define CHG_IRQ2_FLASH_BST_OVP  			(1 << SOC_SCHARGER_IRQ2_flash_bst_ovp_r_START)
#define CHG_IRQ2_FLASH_BST_SCP  			(1 << SOC_SCHARGER_IRQ2_flash_bst_scp_r_START)
#define CHG_IRQ2_FLASH_LED_SHORT  		    (1 << SOC_SCHARGER_IRQ2_flash_led_short_r_START)
#define CHG_IRQ2_FLASH_LED_OPEN 			(1 << SOC_SCHARGER_IRQ2_flash_led_open_r_START)

#define CHG_IRQ_REG3           				(SOC_SCHARGER_IRQ3_ADDR(0))
#define CHG_IRQ3_LCD_NCP_SCP  				(1 << SOC_SCHARGER_IRQ3_lcd_ncp_scp_r_START)
#define CHG_IRQ3_LCD_BST_UVP  				(1 << SOC_SCHARGER_IRQ3_lcd_bst_uvp_r_START)
#define CHG_IRQ3_LCD_BST_OVP  				(1 << SOC_SCHARGER_IRQ3_lcd_bst_ovp_r_START)
#define CHG_IRQ3_LCD_BST_SCP  				(1 << SOC_SCHARGER_IRQ3_lcd_bst_scp_r_START)
#define CHG_IRQ3_LCD_LDO_OCP  				(1 << SOC_SCHARGER_IRQ3_lcd_ldo_ocp_r_START)
#define CHG_IRQ3_LDO1_200MA_OCP  			(1 << SOC_SCHARGER_IRQ3_ldo1_200ma_ocp_r_START)
#define CHG_IRQ3_LDO2_200MA_OCP  			(1 << SOC_SCHARGER_IRQ3_ldo2_200ma_ocp_r_START)

#define CHG_IRQ_REG4           				(SOC_SCHARGER_IRQ4_ADDR(0))
#define CHG_IRQ4_OTG_OVP_5P3V   			(1 << SOC_SCHARGER_IRQ4_otg_ovp_5p3v_r_START)
#define CHG_IRQ4_OTG_SCP        			(1 << SOC_SCHARGER_IRQ4_otg_scp_r_START)
#define CHG_IRQ4_OTG_UVP        			(1 << SOC_SCHARGER_IRQ4_otg_uvp_r_START)

/*irq mask register */
#define CHG_IRQ_MASK_REG0     				(SOC_SCHARGER_IRQM0_ADDR(0))
#define CHG_IRQ_MASK_REG1     				(SOC_SCHARGER_IRQM1_ADDR(0))
#define CHG_IRQ_MASK_REG2     				(SOC_SCHARGER_IRQM2_ADDR(0))
#define CHG_IRQ_MASK_REG3     				(SOC_SCHARGER_IRQM3_ADDR(0))
#define CHG_IRQ_MASK_REG4     				(SOC_SCHARGER_IRQM4_ADDR(0))
#define CHG_IRQ_EN            				(0)
#define CHG_IRQ_DIS           				(1)

/*ref reg*/
#define CHG_REF_REG           				(SOC_SCHARGER_REF_REG_ADDR(0))
#define CHG_THSD_TREG_SET_MIN  				(60)
#define CHG_THSD_TREG_SET_80C  				(80)
#define CHG_THSD_TREG_SET_100C 				(100)
#define CHG_THSD_TREG_SET_MAX  				(120)
#define CHG_THSD_TREG_STEP_20  				(20)

#define CHG_THSD_TSTP_SET_120C 				(120)
#define CHG_THSD_TSTP_SET_140C 				(140)

/*chg reg6*/
#define CHG_REG6                            (SOC_SCHARGER_CHG_REG6_ADDR(0))
#define CHG_BUCK_OK                         (1 << SOC_SCHARGER_CHG_REG6_buck_ok_START)

/*chg v210 version*/
#define CHG_V210_VERSION                    (SOC_SCHARGER_CHG_REG8_ADDR(0))
#define CHG_V222                             2
#define CHG_V210                             1
#define CHG_V200                             0
#define CHG_V210_CMBOX                      (SOC_SCHARGER_CHG_REG9_ADDR(0))
/*chg reg10*/
#define CHG_REG10             				(SOC_SCHARGER_CHG_REG10_ADDR(0))
#define CHG_BATTRY_NOT_PRESENT 				(0) /* no battery is useless, do not config this mode */
#define CHG_BATTRY_PRESENT     				(0)

/*otg reg0*/
#define CHG_OTG_REG0          				(SOC_SCHARGER_OTG_REG0_ADDR(0))
#define CHG_OTG_FORCE_EN      				(1)
#define CHG_OTG_FORCE_DIS     				(0)

/*ctrl reg*/
#define CHG_WDT_RST_REG	    				(SOC_SCHARGER_CTRL_REG_ADDR(0))
#define CHG_WDT_RST          				(1)
#define CHG_WDT_NO_RST       				(0)
#define CHG_FLASH_LED_RST    				(1)
#define CHG_FLASH_LED_NO_RST 				(0)
#define CHG_SOFT_RST         				(1)
#define CHG_SOFT_NO_RST      				(0)

/*sys_set_reg*/
#define CHG_WDT_TIMER_REG       			(SOC_SCHARGER_SYS_SET_REG_ADDR(0))
#define CHG_WDT_TIMER_DIS       			(0)
#define CHG_WDT_TIMER_10S       			(1)
#define CHG_WDT_TIMER_20S       			(2)
#define CHG_WDT_TIMER_40S       			(3)

/*flash_led_current_reg*/
#define FLASH_LED_CURRENT_REG       		(SOC_SCHARGER_FLASH_LED_REG4_ADDR(0))
#define FLASH_LED_CURRENT_FLASH_125	        (0)
#define FLASH_LED_CURRENT_FLASH_250	        (1)
#define FLASH_LED_CURRENT_FLASH_375	        (2)
#define FLASH_LED_CURRENT_FLASH_500	        (3)
#define FLASH_LED_CURRENT_FLASH_625	        (4)
#define FLASH_LED_CURRENT_FLASH_750	        (5)
#define FLASH_LED_CURRENT_FLASH_875	        (6)
#define FLASH_LED_CURRENT_FLASH_1000    	(7)
#define FLASH_LED_CURRENT_FLASH_1125    	(8)
#define FLASH_LED_CURRENT_FLASH_1250	    (9)
#define FLASH_LED_CURRENT_FLASH_1375    	(10)
#define FLASH_LED_CURRENT_FLASH_1500	    (11)
/* 12~15 is 1500 */

#define FLASH_LED_CURRENT_FLASH_MAX FLASH_LED_CURRENT_FLASH_1500

#define FLASH_LED_CURRENT_TORCH_50      	(0)
#define FLASH_LED_CURRENT_TORCH_100     	(1)
#define FLASH_LED_CURRENT_TORCH_150     	(2)
#define FLASH_LED_CURRENT_TORCH_200	        (3)
#define FLASH_LED_CURRENT_TORCH_250	        (4)
#define FLASH_LED_CURRENT_TORCH_300	        (5)
#define FLASH_LED_CURRENT_TORCH_350	        (6)
#define FLASH_LED_CURRENT_TORCH_400	        (7)

#define FLASH_LED_CURRENT_TORCH_MAX FLASH_LED_CURRENT_TORCH_400

/*flash_led_timeout_reg*/
#define FLASH_LED_REG6_REG       		    (SOC_SCHARGER_FLASH_LED_REG6_ADDR(0))
#define FLASH_LED_TIMEOUT_400      			(400)
#define FLASH_LED_TIMEOUT_600     			(600)
#define FLASH_LED_TIMEOUT_800     			(800)
#define FLASH_LED_TIMEOUT_1000	        	(1000)

#define CHG_FLASH_TORCH_TIMOUT_MIN       	(0)
#define CHG_FLASH_TORCH_TIMOUT_MAX       	(30)
#define CHG_FLASH_TORCH_TIMOUT_VALUE(x)  	(x)
#define CHG_FLASH_TORCH_TIMOUT_STEP_2  		(2)

/*flash_led_timeout_en_reg*/
#define FLASH_LED_REG7_REG       		    (SOC_SCHARGER_FLASH_LED_REG7_ADDR(0))

/*flash_bst_voltage_reg*/
#define BUCK_REG5_REG       		    (SOC_SCHARGER_BUCK_REG5_ADDR(0))
/*two stage charger*/
#define TWO_STAGE_CHARGE_FIRST_STAGE        (0x00)
#define TWO_STAGE_CHARGE_SECOND_STAGE       (0x01)

/*charger task period*/
#define CHG_TASK_PERIOD_30S     			(30000)

#define SCHARGER_VERSION_HI6521_VALUE       (0x20)

/*(-10 ) battery temperature is -10 degree*/
#define HI6521_COLD_BATTERY_THRESHOLD     	(-10)
 /*(0 ) battery temperature is 0 degree*/
#define HI6521_COOL_BATTERY_THRESHOLD      	(0)
 /*( 5 ) battery temperature is 5 degree*/
#define HI6521_BATTERY_THRESHOLD_5       	(5)
 /*( 10 ) battery temperature is 10 degree*/
#define HI6521_BATTERY_THRESHOLD_10       	(10)
 /*( 45 ) battery temperature is 45 degree*/
#define HI6521_WARM_BATTERY_THRESHOLD     	(45)
 /*( 50 ) battery temperature is 50 degree*/
#define HI6521_HOT_BATTERY_THRESHOLD      	(50)
 /*( 3 ) battery temperature offset is 3 degree*/
#define HI6521_TEMPERATURE_OFFSET          	(3)

 /* default battery capacity for error that can't get Capacity */
#define HI6521_DEFAULT_CAPACITY            	(2000)
 /* default charge parameter when low temperature for error that can't get the parameter  */
#define DEFAULT_CHARGE_PARAM_LOW_TEMP       (3)

 /*(3.0V) battery preconditioning voltage is 3.0V*/

 /*low temperature charge termination voltage*/
#define HI6521_LOW_TEMP_TERM_VOLTAGE    	(4000)
#define HI6521_LOW_TEMP_NOT_CHARGING_VOLTAGE (4100)
#define HI6521_NORNAL_ICHRG_VOLTAGE     	(3400)
#define CAPACITY_LEVEL_HIGH_THRESHOLD    	(90)

#define HI6521_HIGH_TEMP_RECHARGE_VOLTAGE    (4000)
#define HI6521_HIGH_TEMP_STOP_CHARGE_VOLTAGE    (4100)

/*int HI6521_register_notifier(struct notifier_block *nb,
                unsigned int events);
int HI6521_unregister_notifier(struct notifier_block *nb,
                unsigned int events);*/
extern int hi6521_get_factory_flag(void);
extern int scharger_flash_bst_voltage_config(int volt);
extern int hi6521_set_charge_state(int state);
extern int hi6521_mhl_set_iin(int flag);
extern int scharger_register_notifier(struct notifier_block *nb);
extern int scharger_unregister_notifier(struct notifier_block *nb);
extern int hi6521_get_max_voltagemV(void);
extern int hi6521_get_vrechg_hys(void);
extern int scharger_write_regs(u8 value, u8 reg);
extern int scharger_read_regs(u8 *value, u8 reg);
#endif

