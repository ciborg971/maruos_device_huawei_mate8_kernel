/*----------------------------------------------------------------------------
 *      balongv7r5 m3 cpufreq
 *----------------------------------------------------------------------------
 *      Name:    cpufreq_api.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r5 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_irq.h"
#include "osl_bio.h"

#include "bsp_shared_ddr.h"
#include "soc_interrupts_m3.h"

#include "m3_pm.h"
#include "bsp_softtimer.h"
#include "drv_edma_enum.h"
#include "edma_balong.h"
#include "dpm_balong.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "ios_pd.h"
#include "wdt_balong.h"
#include "m3_cpufreq.h"
#include "bsp_dsp.h"
#include "bsp_hardtimer.h"
#include "bsp_dfs_training.h"
#include "m3_cpufreq.h"
#include "cpufreq_api.h"



/**************************dfs**************************/

extern T_CPUFREQ_ST g_cpufreq;
void dfs_config_reg(u32 cur, u32 new);
TCM_DFS_TRAINING *cpufreq_ddr_train = NULL;


T_CPUFREQ_PROFILE gCpufrqProfile[CPUFREQ_MAX_PROFILE+1] =
{
	{1, 0x40007777, DDR_FREQ_133},//133
	{1, 0x40003733, DDR_FREQ_266},//266
	{1, 0x40003313, DDR_FREQ_266},//266.533
	{0, 0x40001301, DDR_FREQ_333},//333.667
	{1, 0x40001311, DDR_FREQ_533},//533ddr553
	{1, 0x40001301, DDR_FREQ_533},//533.1066
	{1, 0x40001300, DDR_FREQ_533}//1066
 };

 /* only support 1067M and 667M */
 T_CPUFREQ_PLL_CONFIG gCpufrqPll[CPUFREQ_MAX_PLL + 1] =
 {
	{0x6d5555, 0x2101045},
	{0x855555, 0x1101037}
 };

 extern u32 g_set_profile;
 void set_pm_dfs_profile(u32 new_profile)
 {
	 if (new_profile > CPUFREQ_MAX_PROFILE)
	 {
		 printk("argc err:%d\n", new_profile);
	 }
	 g_set_profile = new_profile;
 }

/* dfs */
void pm_dfs_bak(void)
{
	u32 cur = M3_CUR_CPUFREQ_PROFILE;
	u32 max = g_set_profile;
	u32 min_limit = M3_MIN_CPUFREQ_PROFILE;

	if(max < min_limit)
	{
		max = min_limit;
	}
	if(cur < max)
	{
		dfs_config_reg(cur, max);
		g_cpufreq.curprof = max;
		M3_CUR_CPUFREQ_PROFILE = max;
	}
}

void dfs_set_profile(u32 profile)
{
	dfs_config_reg(g_cpufreq.curprof, profile);
}
u32 get_pro_int = 0;
u32 dfs_get_profile(void)
{
	u32 profile = CPUFREQ_INVALID_PROFILE;
	T_CPUFREQ_PLL_CONFIG curconf;
	u32 invalid = 0xFFFFFFFF;
	u32 curpll = invalid;
	u32 curclkdiv = 0;
	u32 i = 0;
    if (!get_pro_int)
    {
        get_pro_int = 1;
        return CPUFREQ_MAX_PROFILE;
    }
    return M3_CUR_CPUFREQ_PROFILE;
	/* find right pll */
	curconf.dfs1ctrl1 = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL1);
	curconf.dfs1ctrl2 = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL2);

	for(i = 0;i <= CPUFREQ_MAX_PLL;i++)
	{
		if(curconf.dfs1ctrl1 == gCpufrqPll[i].dfs1ctrl1)
		{
			if(curconf.dfs1ctrl2 == gCpufrqPll[i].dfs1ctrl2)
			{
				curpll = i;
				break;
			}
		}
	}
	if(curpll == invalid)
	{
		printk("get pll err\n");
		return CPUFREQ_INVALID_PROFILE;
	}
	/* find right profile */
	curclkdiv = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKDIV2);

	for(i = 0;i <= CPUFREQ_MAX_PROFILE;i++)
	{
		if(curpll == gCpufrqProfile[i].pll)
		{
			if(curclkdiv == gCpufrqProfile[i].clkdiv)
			{
				profile = i;
				break;
			}
		}
	}

	return profile;
}

static u32 dfs_get_pro_mode(u32 pro)
{
    u32 curfbus = 0;
	u32 curpll = 0;
	
	curpll = gCpufrqProfile[pro].pll;
	curfbus = (gCpufrqProfile[pro].clkdiv >> 12) & 0xf;
	return (curpll && (curfbus < 3)) ? mission_mode : bypass_mode;
}
s32 dfs_get_cur_mode(u32 *cur_ddr)
{
    u32 tmp = 0;
    tmp = dfs_get_profile();
	if(tmp == CPUFREQ_INVALID_PROFILE)
	{
		//M3CPUFREQ_PRINT("cut profile invalid\n");
		tmp = CPUFREQ_MAX_PROFILE;
	}
	*cur_ddr = gCpufrqProfile[tmp].ddrvalue;
	return (s32)dfs_get_pro_mode(tmp);
}


void dfs_get_ddrc2_timing(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMING* ptiming)
{
	/* 667M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0x654A180F;
				ptiming->nxttiming1 = 0x1372A047;
				ptiming->nxttiming2 = 0x6401504F;
				ptiming->nxttiming3 = 0xAF4A8046;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x2081008;
				ptiming->nxttiming6 = 0x44;
				break;
#if 0
			case 3:
				ptiming->nxttiming0 = 0x63290D08;
				ptiming->nxttiming1 = 0xA62A024;
				ptiming->nxttiming2 = 0x4300B027;
				ptiming->nxttiming3 = 0xAF454035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080808;
				ptiming->nxttiming6 = 0x44;
				break;
			case 5:
				ptiming->nxttiming0 = 0x6318C906;
				ptiming->nxttiming1 = 0x762A019;
				ptiming->nxttiming2 = 0x4300901A;
				ptiming->nxttiming3 = 0xAF438035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080608;
				ptiming->nxttiming6 = 0x44;
				break;
			case 7:
				ptiming->nxttiming0 = 0x6318C805;
				ptiming->nxttiming1 = 0x562A013;
				ptiming->nxttiming2 = 0x43009013;
				ptiming->nxttiming3 = 0xAF42A035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080608;
				ptiming->nxttiming6 = 0x44;
				break;
#endif
			default:
				break;
		}
	}
	else if(1 == pll)/* 1066M */
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0x677B6718;
				ptiming->nxttiming1 = 0x1E82A071;
				ptiming->nxttiming2 = 0x9502107E;
				ptiming->nxttiming3 = 0xAF50C057;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x3181908;
				ptiming->nxttiming6 = 0x44;
				break;
			case 3:
				ptiming->nxttiming0 = 0x6441D50D;
				ptiming->nxttiming1 = 0xF72A039;
				ptiming->nxttiming2 = 0x5301103F;
				ptiming->nxttiming3 = 0xAF486035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x2080D08;
				ptiming->nxttiming6 = 0x44;
				break;
#if 0
			case 5:
				ptiming->nxttiming0 = 0x63294E09;
				ptiming->nxttiming1 = 0xA62A027;
				ptiming->nxttiming2 = 0x4300C02A;
				ptiming->nxttiming3 = 0xAF45A035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080908;
				ptiming->nxttiming6 = 0x44;
				break;
#endif
			case 7:
				ptiming->nxttiming0 = 0x63210B07;
				ptiming->nxttiming1 = 0x862A01D;
				ptiming->nxttiming2 = 0x4300901F;
				ptiming->nxttiming3 = 0xAF444035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080708;
				ptiming->nxttiming6 = 0x44;
				break;
#if 0
			case 15:
				ptiming->nxttiming0 = 0x6318C704;
				ptiming->nxttiming1 = 0x462A00F;
				ptiming->nxttiming2 = 0x4300900F;
				ptiming->nxttiming3 = 0xAF422035;
				ptiming->nxttiming4 = 0x600000;
				ptiming->nxttiming5 = 0x1080608;
				ptiming->nxttiming6 = 0x44;
				break;
#endif
			default:
				break;
		}
	}
	else
	{
		printk("dfs get_timing err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING0), 0, 31, ptiming->nxttiming0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING1), 0, 31, ptiming->nxttiming1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING2), 0, 31, ptiming->nxttiming2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING3), 0, 31, ptiming->nxttiming3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING4), 0, 31, ptiming->nxttiming4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING5), 0, 31, ptiming->nxttiming5);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING6), 0, 31, ptiming->nxttiming6);
}


void dfs_get_ddrc2_timer(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMER* ptimer)
{
	/* 667M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x354F4542;
				ptimer->dramtimer1 = 0x8472A36;
				ptimer->dramtimer2 = 0x2006104B;
				ptimer->dramtimer3 = 0x80340D4E;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 3:
				ptimer->dramtimer0 = 0x1CC82332;
				ptimer->dramtimer1 = 0x6241636;
				ptimer->dramtimer2 = 0x20040C26;
				ptimer->dramtimer3 = 0x8019F4A7;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 5:
				ptimer->dramtimer0 = 0x14C62232;
				ptimer->dramtimer1 = 0x6191236;
				ptimer->dramtimer2 = 0x20040C1A;
				ptimer->dramtimer3 = 0x80115C70;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 7:
				ptimer->dramtimer0 = 0x10C52232;
				ptimer->dramtimer1 = 0x6131236;
				ptimer->dramtimer2 = 0x20040C14;
				ptimer->dramtimer3 = 0x800CFC54;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			default:
				break;
		}
	}
	else if(1 == pll)/* 1066M */
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x51D87852;
				ptimer->dramtimer1 = 0xA714236;
				ptimer->dramtimer2 = 0x20091477;
				ptimer->dramtimer3 = 0x80534E16;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440705;
				ptimer->dmsel      = 0x24704A00;
				ptimer->ioctl3     = 0xC000;
				break;
			case 3:
				ptimer->dramtimer0 = 0x290D4432;
				ptimer->dramtimer1 = 0x8392236;
				ptimer->dramtimer2 = 0x20050C3C;
				ptimer->dramtimer3 = 0x8029950B;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 5:
				ptimer->dramtimer0 = 0x1CC93332;
				ptimer->dramtimer1 = 0x6271836;
				ptimer->dramtimer2 = 0x20040C28;
				ptimer->dramtimer3 = 0x801BACB2;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			case 7:
				ptimer->dramtimer0 = 0x18C72232;
				ptimer->dramtimer1 = 0x61D1236;
				ptimer->dramtimer2 = 0x20040C1F;
				ptimer->dramtimer3 = 0x8014CC86;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 15:
				ptimer->dramtimer0 = 0x10C42232;
				ptimer->dramtimer1 = 0x60F1236;
				ptimer->dramtimer2 = 0x20040C10;
				ptimer->dramtimer3 = 0x800A5443;
				ptimer->dramtimer4 = 0x0;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			default:
				break;
		}
	}
	else
	{
		printk("dfs_get_timer err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER0), 0, 31, ptimer->dramtimer0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER1), 0, 31, ptimer->dramtimer1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER2), 0, 31, ptimer->dramtimer2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER3), 0, 31, ptimer->dramtimer3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER4), 0, 31, ptimer->dramtimer4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER5), 0, 31, ptimer->dramtimer5);
}


#if 0
void dfs_get_ddrc3_timing(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMING* ptiming)
{
	/* 667M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0xB54A180F;
				ptiming->nxttiming1 = 0xC72A02D;
				ptiming->nxttiming2 = 0x6501204F;
				ptiming->nxttiming3 = 0xAF4A8245;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x12081008;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 3:
				ptiming->nxttiming0 = 0xB3290D08;
				ptiming->nxttiming1 = 0x662A017;
				ptiming->nxttiming2 = 0x4500A027;
				ptiming->nxttiming3 = 0xAF454145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080808;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 5:
				ptiming->nxttiming0 = 0xB318C906;
				ptiming->nxttiming1 = 0x462A010;
				ptiming->nxttiming2 = 0x4500901A;
				ptiming->nxttiming3 = 0xAF438145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 7:
				ptiming->nxttiming0 = 0xB318C805;
				ptiming->nxttiming1 = 0x362A00C;
				ptiming->nxttiming2 = 0x45009013;
				ptiming->nxttiming3 = 0xAF42A145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			default:
				break;
		}
	}
	else if(1 == pll)/* 1066M */
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0xB77B6718;
				ptiming->nxttiming1 = 0x1282A047;
				ptiming->nxttiming2 = 0x9501C07E;
				ptiming->nxttiming3 = 0xAF50C255;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x13181908;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 3:
				ptiming->nxttiming0 = 0xB441D50D;
				ptiming->nxttiming1 = 0x972A024;
				ptiming->nxttiming2 = 0x5500F03F;
				ptiming->nxttiming3 = 0xAF486145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x12080D08;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 5:
				ptiming->nxttiming0 = 0xB3294E09;
				ptiming->nxttiming1 = 0x762A019;
				ptiming->nxttiming2 = 0x4500A02A;
				ptiming->nxttiming3 = 0xAF45A145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080908;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 7:
				ptiming->nxttiming0 = 0xB3210B07;
				ptiming->nxttiming1 = 0x562A013;
				ptiming->nxttiming2 = 0x4500901F;
				ptiming->nxttiming3 = 0xAF444145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080708;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 15:
				ptiming->nxttiming0 = 0xB318C704;
				ptiming->nxttiming1 = 0x362A00A;
				ptiming->nxttiming2 = 0x4500900F;
				ptiming->nxttiming3 = 0xAF422145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			default:
				break;
		}
	}
	else
	{
		printk("dfs_get_ddrc_timing err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING0), 0, 31, ptiming->nxttiming0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING1), 0, 31, ptiming->nxttiming1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING2), 0, 31, ptiming->nxttiming2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING3), 0, 31, ptiming->nxttiming3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING4), 0, 31, ptiming->nxttiming4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING5), 0, 31, ptiming->nxttiming5);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING6), 0, 31, ptiming->nxttiming6);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING7), 0, 31, ptiming->nxttiming7);
}


void dfs_get_ddrc3_timer(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMER* ptimer)
{
	/* 400M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x354F4552;
				ptimer->dramtimer1 = 0x847246B;
				ptimer->dramtimer2 = 0x2006104B;
				ptimer->dramtimer3 = 0x80340D4E;
				ptimer->dramtimer4 = 0x300860F;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 3:
				ptimer->dramtimer0 = 0x1CC82352;
				ptimer->dramtimer1 = 0x624146B;
				ptimer->dramtimer2 = 0x20041026;
				ptimer->dramtimer3 = 0x8019F4A7;
				ptimer->dramtimer4 = 0x3008488;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 5:
				ptimer->dramtimer0 = 0x14C62252;
				ptimer->dramtimer1 = 0x619126B;
				ptimer->dramtimer2 = 0x2004101A;
				ptimer->dramtimer3 = 0x80115C70;
				ptimer->dramtimer4 = 0x3008406;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 7:
				ptimer->dramtimer0 = 0x10C52252;
				ptimer->dramtimer1 = 0x613126B;
				ptimer->dramtimer2 = 0x20041014;
				ptimer->dramtimer3 = 0x800CFC54;
				ptimer->dramtimer4 = 0x3008385;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			default:
				break;
		}
	}
	else if(1 == pll)/* 666M */
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x51D87852;
				ptimer->dramtimer1 = 0xA71386B;
				ptimer->dramtimer2 = 0x20091477;
				ptimer->dramtimer3 = 0x80534E16;
				ptimer->dramtimer4 = 0x3008817;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440705;
				ptimer->dmsel      = 0x24704A00;
				ptimer->ioctl3     = 0xC000;
				break;
			case 3:
				ptimer->dramtimer0 = 0x290D4452;
				ptimer->dramtimer1 = 0x8391E6B;
				ptimer->dramtimer2 = 0x2005103C;
				ptimer->dramtimer3 = 0x8029950B;
				ptimer->dramtimer4 = 0x300858C;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 5:
				ptimer->dramtimer0 = 0x1CC93352;
				ptimer->dramtimer1 = 0x627146B;
				ptimer->dramtimer2 = 0x20041028;
				ptimer->dramtimer3 = 0x801BACB2;
				ptimer->dramtimer4 = 0x3008489;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 7:
				ptimer->dramtimer0 = 0x18C72252;
				ptimer->dramtimer1 = 0x61D126B;
				ptimer->dramtimer2 = 0x2004101F;
				ptimer->dramtimer3 = 0x8014CC86;
				ptimer->dramtimer4 = 0x3008407;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 15:
				ptimer->dramtimer0 = 0x10C42252;
				ptimer->dramtimer1 = 0x60F126B;
				ptimer->dramtimer2 = 0x20041010;
				ptimer->dramtimer3 = 0x800A5443;
				ptimer->dramtimer4 = 0x3008384;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			default:
				break;
		}
	}
	else
	{
		printk("dfs_get_ddrc_timer err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER0), 0, 31, ptimer->dramtimer0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER1), 0, 31, ptimer->dramtimer1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER2), 0, 31, ptimer->dramtimer2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER3), 0, 31, ptimer->dramtimer3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER4), 0, 31, ptimer->dramtimer4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER5), 0, 31, ptimer->dramtimer5);
}
#endif

void dfs_ddrc_config(u32 newpro)
{
	u32 n = 0;
	u32 m = 0;
	s32 ddrvalue = 0;
	ddrvalue = gCpufrqProfile[newpro].ddrvalue;
	if (dfs_get_pro_mode(newpro))
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL0), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL1), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL1);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL2), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL2);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL3), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL3);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL4), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL4);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ADDRPHBOUND), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ADDRPHBOUND);
		for (n = 0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL0 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL0[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL1 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL1[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL2 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL2[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL0 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQNBDL0[0][n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL1 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQNBDL1[0][n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNOEBDL	+ n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNOEBDL[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQSDLY  + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQSDLY[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQDLY   + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQDLY[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWLSL	 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWLSL[n]);
		}
	}
	else
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL0), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL1), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL2), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL3), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL4), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ADDRPHBOUND), 0, 31, 0xC0000);
		for (n = 0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL0 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL1 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL2 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL0 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL1 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNOEBDL	+ n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQSDLY  + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQDLY   + n * 0x80), 0, 31, 0xC00);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWLSL	 + n * 0x80), 0, 31, 0x10000);
		}
	}
	for (n = 0; n < 4; n++)
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSDLY + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSDLY[n]);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNGDS	 + n * 0x80), 0, 31, 
							cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNGDS[n]);
		for (m = 0; m < 2; m++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 0, 6, 
								(cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7F));
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 9, 14, 
								((cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7E00) >> 9));
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 16, 22, 
								((cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7F0000) >> 16));
		}
	}
}
#define CM3_LP_PWRCTRL0      (0xE0044020)
#define CM3_DDRC_BASE_ADDR    0xE0046000

static void pm_ddr_porting_in_sref(void)
{
    u32 tmp = 0;
    volatile u32 times = 20;
	/* 1 */
	tmp = readl(CM3_LP_PWRCTRL0);
	tmp |= 0x10000;
	writel(tmp, CM3_LP_PWRCTRL0);

	/* 5 */
	writel(0x1, CM3_DDRC_BASE_ADDR + 0x4);
	do{
		tmp = readl(CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(!tmp);
    
    while(times)
    {
        times--;
    }
}

static void pm_ddr_porting_out_sref(void)
{
    u32 tmp = 0;
    volatile u32 times = 20;

    writel(0x0, CM3_DDRC_BASE_ADDR + 0x4);
	do{
		tmp = readl(CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(tmp);
    
    while(times)
    {
        times--;
    }
    
	tmp = readl(CM3_LP_PWRCTRL0);
	tmp &= ~0x10000;
	writel(tmp, CM3_LP_PWRCTRL0);
}

void dfs_config_reg(u32 cur, u32 new)
{
    volatile u32 times = 60;
    pm_ddr_porting_in_sref();
    while(times)
    {
        times--;
    }
    pm_ddr_porting_out_sref();
}

void dfs_ddrc_calc(void)
{
	cpufreq_ddr_train = (TCM_DFS_TRAINING *)DFS_DDR_TRAINING_DATA_ADDR;
}