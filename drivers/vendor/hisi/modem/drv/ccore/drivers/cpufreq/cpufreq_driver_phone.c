
#include <product_config.h>
#include <securec.h>

#include <osl_malloc.h>
#include <osl_irq.h>
#include <of.h>
#include <bsp_dpm.h>
#include <bsp_sysctrl.h>
#include "cpufreq_balong.h"
/*lint --e{525, 539, 830}*/
void cpufreq_config_reg(u32 cur, u32 new);

u32 cpufreq_sysctrl_base_addr = 0xE0200000;

u32 cpufreq_clkdiv2_offset = 0x104;

u32 cpufreq_a9pll_cfg0_offset = 0x200;

u32 cpufreq_a9pll_cfg1_offset = 0x204;

u32 cpufreq_max_pll = 2;

u32 cpufreq_dpm_get_curpro = 1;


T_CPUFREQ_ST g_cpufreq;

T_CPUFREQ_PROFILE *gCpufrqProfile = NULL;

/* pll only support 666M and 400M */
T_CPUFREQ_PLL_CONFIG *gCpufrqPll = NULL;



/* dfs */
void cpufreq_pm_dfs_bak(u32 profile)
{
    u32 cur = CPUFREQ_CUR_PROFILE;
    u32 max_pro = CPUFREQ_MAX_PROFILE_LIMIT;

    if(cur < max_pro)
    {
        cpufreq_config_reg(cur, profile);
        g_cpufreq.curprof = profile;
        CPUFREQ_CUR_PROFILE = profile;
    }
}

static void cpufreq_set_profile(u32 profile)
{
	cpufreq_config_reg(g_cpufreq.curprof, profile);
}

static u32 cpufreq_reg_get_profile(void)
{
	u32 profile = CPUFREQ_INVALID_PROFILE;
	T_CPUFREQ_PLL_CONFIG curconf;
	u32 invalid = 0xFFFFFFFF;
	u32 curpll = invalid;
	u32 curclkdiv = 0;
	u32 i = 0;

	/* find right pll */
	curconf.a9pllcfg0 = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
	curconf.a9pllcfg1 = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);

	for(i = 0;i <= cpufreq_max_pll;i++)
	{
		if((curconf.a9pllcfg0&0x3FFFFFC) == gCpufrqPll[i].a9pllcfg0)
		{
			if((curconf.a9pllcfg1&0xFFFFFF) == gCpufrqPll[i].a9pllcfg1)
			{
				curpll = i;
				break;
			}
		}
	}
	if(curpll == invalid)
	{
		cpufreq_err("dfs_get_profile pll error\n");
		return CPUFREQ_INVALID_PROFILE;
	}

	/* find right profile */
	curclkdiv = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);

	for(i = 0;i <= (u32)BALONG_FREQ_MAX;i++)
	{
		if(curpll == gCpufrqProfile[i].pll)
		{
			if((curclkdiv&0xFFF0) == gCpufrqProfile[i].clkdiv)
			{
				profile = i;
				break;
			}
		}
	}

	return profile;
}
void cpufreq_config_reg(u32 cur, u32 new)
{
	u32 tmp = 0;
	u32 curpll = 0;
	u32 newpll = 0;
    u32 flag = 0;

    curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;
    /*lint --e{801 }*/
    if(curpll == newpll)
    {
        flag = 1;
        goto step11;
    }

	/* 1 */
	tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	tmp &= ~(0x7<<16);
    tmp |= 0x4<<16;
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);

	/* 2 */
	tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);
	tmp &= ~(0x1<<26);
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);

	/* 3 */

	/* 4 */
	tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
	tmp &= ~(0x3);
    tmp |= 0x2;
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);

	/* 5 */
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
    tmp &= 0xFC000003;/* bit[25:2] = 0 */
    tmp |= gCpufrqPll[newpll].a9pllcfg0;
    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);

    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);
    tmp &= 0xFF000000;/* bit[23:0] = 0 */
    tmp |= gCpufrqPll[newpll].a9pllcfg1;
    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);

	/* 6 */
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
	tmp &= ~(0x3);
    tmp |= 0x1;
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);

	/* 7 */

	/* 8 */
	do
	{
		tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
		tmp = (tmp >> 26) & 0x1;
	}while(!tmp);

	/* 9 */
	tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);
	tmp |= (0x1<<26);
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);

	/* 10 */

	/* 11 */
	/*
		如果mcpu_div的分频系数变小，
		先配置slow_div fast_div，然后再配置mcpu_div； 
		否则先配置mcpu_div再配置slow_div fast_div
	*/
step11:
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
    if ((gCpufrqProfile[new].clkdiv & 0xF0) < (gCpufrqProfile[cur].clkdiv & 0xF0))
    {
    	tmp &= 0xFFFF00FF;/* bit[15:12  11:8] = 0 */
	    tmp |= (gCpufrqProfile[new].clkdiv & 0xFF00);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	    tmp &= 0xFFFFFF0F;
	    tmp |= (gCpufrqProfile[new].clkdiv & 0xF0);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	}
	else
	{
		tmp &= 0xFFFFFF0F;
	    tmp |= (gCpufrqProfile[new].clkdiv & 0xF0);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	    
    	tmp &= 0xFFFF00FF;/* bit[15:12  11:8] = 0 */
	    tmp |= (gCpufrqProfile[new].clkdiv & 0xFF00);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	}
    if(flag == 1)
    {
        return;
    }

	/* 12 */
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
    tmp &= ~(0x7<<16);
    tmp |= 0x1<<16;
    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
}

u32 cpufreq_get_cur_profile(void)
{
    unsigned long irqlock = 0;
	s32 tmp = 0;
    if (cpufreq_dpm_get_curpro)
    {
    	tmp = (s32)cpufreq_reg_get_profile();
    	if(tmp == CPUFREQ_INVALID_PROFILE)
    	{
    		cpufreq_err("cur profile invalid\n");
    		tmp = BALONG_FREQ_MAX;
    	}
    	/*lint --e{63}*/
    	local_irq_save(irqlock);
        cpufreq_dpm_get_curpro = 0;
        g_cpufreq.curprof = (u32)tmp;
        CPUFREQ_CUR_PROFILE = (u32)tmp;
        local_irq_restore(irqlock);
    }
    else
    {
        tmp = (s32)CPUFREQ_CUR_PROFILE;
    	if ((tmp < BALONG_FREQ_MIN) || (tmp > BALONG_FREQ_MAX))
    	{
    		tmp = BALONG_FREQ_MAX;
    		cpufreq_info("cpufreq return right cur_profile value? %d\n", tmp);
    	}
    }
	return (u32)tmp;
}

u32 cpufreq_find_profile(u32 action, u32 profile)
{
	u32 curprof = CPUFREQ_INVALID_PROFILE;
	u32 dstprof = CPUFREQ_INVALID_PROFILE;
    /*lint --e{616} */
	curprof = cpufreq_get_cur_profile();
	switch(action)
	{
		case 0://升
            profile = curprof + 1;
		case 1://升目标
			if((curprof < profile) && (profile <= g_cpufreq.maxprof))
			{
				dstprof = profile;
			}
			else
			{
				cpufreq_info("cpufreq up  dst: %d, cur:%d, max: %d\n", profile, curprof, g_cpufreq.maxprof);
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid or not change*/
			}
			break;
		case 2://降
            profile = (curprof > 0)?(curprof - 1) : 0;
		case 3://降目标
			if((profile < curprof) && (profile >= g_cpufreq.minprof))
			{
				dstprof = profile;
			}
			else
			{
				cpufreq_info("cpufreq down  dst:%d, cur:%d, min:%d\n", profile, curprof, g_cpufreq.minprof);
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid or not change*/
			}
			break;
		case 4://设置最小profile
			if(profile > g_cpufreq.maxprof)
			{
                cpufreq_err("1 profile not in the range\n");
			}
            else if(profile == g_cpufreq.minprof)
            {
                cpufreq_info("minprof is the same\n");
            }
			else
			{
				g_cpufreq.minprof = profile;
                //CPUFREQ_MIN_PROFILE_LIMIT
                ((SRAM_SMALL_SECTIONS * )((unsigned long)SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE = profile;
				if(curprof < profile)
				{
					dstprof = profile;
				}
				else
				{
					dstprof = CPUFREQ_INVALID_PROFILE;
				}
			}
			break;
		case 5://设置最大profile
			if((profile > (u32)BALONG_FREQ_MAX)||(profile < g_cpufreq.minprof))
			{
                cpufreq_err("2 profile not in the range\n");
			}
            else if(profile == g_cpufreq.maxprof)
            {
                cpufreq_info("maxprof is the same\n");
            }
			else
			{
				g_cpufreq.maxprof = profile;
                CPUFREQ_MAX_PROFILE_LIMIT = profile;
				if(curprof > profile)
				{
					dstprof = profile;
				}
				else
				{
					dstprof = CPUFREQ_INVALID_PROFILE;
				}
			}
			break;
		default :
			break;
	}
	return dstprof;
}

static void cpufreq_set_ccorelockflag(u32 action)
{
    unsigned long irqlock = 0;

    local_irq_save(irqlock);
    switch(action)
	{
        case 0:
            g_cpufreq.ccorelockflag = 1;
            break;
        case 1:
            g_cpufreq.ccorelockflag = 0;
            break;
        default:
            break;
    }
    local_irq_restore(irqlock);
}

void cpufreq_recv_msg(struct cpufreq_msg *rmsg)
{
	unsigned long irqlock = 0;
	u32 dstprof = 0;

	if(rmsg == NULL)
	{
		cpufreq_err("recv_msg input err\n");
		return;
	}

    if(rmsg->source != CPUFREQ_CCORE)
    {
        cpufreq_err("rmail->coretype err=%d\n", rmsg->source);
        return;
    }

    cpufreq_info(" msgtype:%d action:%d profile=%d\n", rmsg->msg_type, rmsg->content, rmsg->profile);
	switch(rmsg->msg_type)
	{
		case CPUFREQ_ADJUST_FREQ:
			local_irq_save(irqlock);
			if(!g_cpufreq.ccorelockflag)
			{
				dstprof = cpufreq_find_profile(rmsg->content, rmsg->profile);
				if(dstprof != CPUFREQ_INVALID_PROFILE)
				{
					cpufreq_set_profile(dstprof);
					g_cpufreq.curprof = dstprof;
                    CPUFREQ_CUR_PROFILE = dstprof;
				}
			}
            else
            {
                cpufreq_err("cpufreq lock\n");
            }
			local_irq_restore(irqlock);
			break;
        case CPUFREQ_LOCK_MCORE_ACTION:
            cpufreq_set_ccorelockflag(rmsg->content);
            break;
		default:
			cpufreq_err("msgtype err\n");
			break;
	}
}

static int cpufreq_drv_phone_resume(struct dpm_device *cpufreq_resume)
{
    cpufreq_dpm_get_curpro = 1;
    return BSP_OK;
}


int cpufreq_reg_init(void)
{
	unsigned int i = 0;
	unsigned int len = 0;
	unsigned int reg_addr = 0;
	unsigned int *cpufreq_reg_pll = NULL;
	unsigned int *cpufreq_reg_clkdiv = NULL;
	unsigned int *cpufreq_reg_pll_cfg0 = NULL;
	unsigned int *cpufreq_reg_pll_cfg1 = NULL;

	struct device_node *cpufreq_reg_node = NULL;
	cpufreq_reg_node = of_find_compatible_node(NULL, NULL, "cpufreq_balong_ccore");
	if (!cpufreq_reg_node)
	{
		cpufreq_err("cpufreq read reg dts node not found!  %s\n");
		return ERROR;
	}
	len = sizeof(unsigned int) * ((unsigned int)DC_RESV + 1);
	cpufreq_reg_pll = (unsigned int *)osl_malloc(len);
	if (NULL == cpufreq_reg_pll)
	{
		cpufreq_err("malloc pll failed\n");
		return ERROR;
	}
	(void)memset_s(cpufreq_reg_pll, len, 0, len);

	cpufreq_reg_clkdiv = (unsigned int *)osl_malloc(len);
	if (NULL == cpufreq_reg_clkdiv)
	{
		osl_free(cpufreq_reg_pll);
		cpufreq_err("malloc clkdiv failed\n");
		return ERROR;
	}
	(void)memset_s(cpufreq_reg_pll, len, 0, len);
	
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_reg_pll_count", &cpufreq_max_pll, 1);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_reg_pll", cpufreq_reg_pll, DC_RESV);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_reg_clkdiv", cpufreq_reg_clkdiv, DC_RESV);

	cpufreq_reg_pll_cfg0 = (unsigned int *)osl_malloc(sizeof(unsigned int) * cpufreq_max_pll);
	if (NULL == cpufreq_reg_pll_cfg0)
	{
		osl_free(cpufreq_reg_pll);
		osl_free(cpufreq_reg_clkdiv);
		cpufreq_err("malloc pll_cfg0 failed\n");
		return ERROR;
	}
	
	cpufreq_reg_pll_cfg1 = (unsigned int *)osl_malloc(sizeof(unsigned int) * cpufreq_max_pll);
	if (NULL == cpufreq_reg_pll_cfg1)
	{
		osl_free(cpufreq_reg_pll);
		osl_free(cpufreq_reg_clkdiv);
		osl_free(cpufreq_reg_pll_cfg0);
		cpufreq_err("malloc pll_cfg1 failed\n");
		return ERROR;
	}
	
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_reg_pll_cfg0", cpufreq_reg_pll_cfg0, cpufreq_max_pll);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_reg_pll_cfg1", cpufreq_reg_pll_cfg1, cpufreq_max_pll);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_sys_addr", &reg_addr, 1);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_clkdiv2_offset", &cpufreq_clkdiv2_offset, 1);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_a9pll_cfg0_offset", &cpufreq_a9pll_cfg0_offset, 1);
	(void)of_property_read_u32_array(cpufreq_reg_node, "cpufreq_a9pll_cfg1_offset", &cpufreq_a9pll_cfg1_offset, 1);
	
	cpufreq_sysctrl_base_addr = (unsigned int)bsp_sysctrl_addr_get((void *)reg_addr);
	
	gCpufrqProfile = (T_CPUFREQ_PROFILE *)osl_malloc(sizeof(T_CPUFREQ_PROFILE) * ((unsigned int)DC_RESV + 1));
	if (NULL == gCpufrqProfile)
	{
		osl_free(cpufreq_reg_pll);
		osl_free(cpufreq_reg_clkdiv);
		osl_free(cpufreq_reg_pll_cfg0);
		osl_free(cpufreq_reg_pll_cfg1);
		cpufreq_err("malloc gCpufrqProfile failed\n");
		return ERROR;
	}
	gCpufrqPll = (T_CPUFREQ_PLL_CONFIG *)osl_malloc(sizeof(T_CPUFREQ_PLL_CONFIG) * cpufreq_max_pll);
	if (NULL == gCpufrqPll)
	{
		osl_free(cpufreq_reg_pll);
		osl_free(cpufreq_reg_clkdiv);
		osl_free(cpufreq_reg_pll_cfg0);
		osl_free(cpufreq_reg_pll_cfg1);
		osl_free(gCpufrqProfile);
		cpufreq_err("malloc gCpufrqPll failed\n");
		return ERROR;
	}
	for(i = 0; i < (unsigned int)DC_RESV; i++)
	{
		gCpufrqProfile[i].pll = cpufreq_reg_pll[i];
		gCpufrqProfile[i].clkdiv = cpufreq_reg_clkdiv[i];
	}
	for(i = 0; i < cpufreq_max_pll; i++)
	{
		gCpufrqPll[i].a9pllcfg0 = cpufreq_reg_pll_cfg0[i];
		gCpufrqPll[i].a9pllcfg1 = cpufreq_reg_pll_cfg1[i];
	}

	osl_free(cpufreq_reg_pll);
	osl_free(cpufreq_reg_clkdiv);
	osl_free(cpufreq_reg_pll_cfg0);
	osl_free(cpufreq_reg_pll_cfg1);
	
	g_cpufreq.maxprof = BALONG_FREQ_MAX;
	g_cpufreq.minprof = BALONG_FREQ_MIN;
	g_cpufreq.curprof = cpufreq_get_cur_profile();
    g_cpufreq.ccorelockflag = 0;
    
    CPUFREQ_CUR_PROFILE = g_cpufreq.curprof;
    CPUFREQ_MAX_PROFILE_LIMIT = g_cpufreq.maxprof;
    CPUFREQ_MIN_PROFILE_LIMIT = g_cpufreq.minprof;
    return OK;
}

int cpufreq_driver_phone_release(void)
{
	return OK;	
}

int cpufreq_driver_phone_target(struct cpufreq_msg *msg)
{
	if (NULL == msg)
	{
		return ERROR;
	}
	
	if (CPUFREQ_SET_DDR_LIMIT != msg->msg_type)
	{
		cpufreq_recv_msg(msg);
	}
	else
	{
		(void)cpufreq_icc_send(msg);
	}
	return OK;
}

int cpufreq_get_phone_cur_pro(void)
{
	return (s32)cpufreq_get_cur_profile();
}
struct cpufreq_driver_s cpufreq_driver_phone = {
	.drv_name = "drv_phone",
	.drv_id = 2,
	.drv_ops = {
		.driver_init = cpufreq_reg_init,
		.driver_release = cpufreq_driver_phone_release,
		.driver_target = cpufreq_driver_phone_target,
		.driver_resume = cpufreq_drv_phone_resume,
		.get_current_profile = cpufreq_get_phone_cur_pro,
	},
};

