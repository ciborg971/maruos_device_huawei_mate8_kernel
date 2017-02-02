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

#ifndef __HI_PWRCTRL_INTER_H__
#define __HI_PWRCTRL_INTER_H__

#include "hi_base.h"
#include "hi_pwrctrl.h"

#if 0
/*irm ǯλ��ʹ��*/
static __inline__ void set_hi_pwr_ctrl5_irm_iso_dis(unsigned int v)
{
	return set_hi_pwr_ctrl5_irmbbp_iso_ctrl_dis(v);
}

/*irm ǯλʹ��*/
static __inline__ void set_hi_pwr_ctrl4_irm_iso_en(unsigned int v)
{
	set_hi_pwr_ctrl4_irmbbp_iso_ctrl_en(v);
}

/*irm�ϵ�*/
static __inline__ void set_hi_pwr_ctrl6_irm_mtcmos_en(unsigned int v)
{
	set_hi_pwr_ctrl6_irmbbp_mtcmos_ctrl_en(v);
}

/*irm �µ�*/
static __inline__ void set_hi_pwr_ctrl7_irm_mtcmos_dis(unsigned int v)
{
	set_hi_pwr_ctrl7_irmbbp_mtcmos_ctrl_dis(v);
}

/*irm ״̬��ѯ*/
static __inline__ unsigned int get_hi_pwr_stat1_irm_mtcmos_rdy(void)
{
	return get_hi_pwr_stat1_irmbbp_mtcmos_rdy_stat();
}
#endif

/* for pm */
static __inline__ unsigned int  hi_pwrctrl_get_pwr_ctrl2_abb_ch1_tcxo_en(void){return 0;}
static __inline__ unsigned int  hi_pwrctrl_get_pwr_ctrl2_pmu_ch1_tcxo_en(void){return 0;}

static __inline__ void hi_pwrctrl_set_pwr_ctrl2_abb_ch1_tcxo_en(unsigned int val){};
static __inline__ void hi_pwrctrl_set_pwr_ctrl2_pmu_ch1_tcxo_en(unsigned int val){};

#if 0
static __inline__ unsigned int get_hi_pwr_stat1(void)
{
#if defined(__KERNEL__)
	return readl((const volatile void *)(HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#else
	return readl((HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#endif
}
/* for pm --end */
#endif
#if 0
/******** dsp start ********/
static __inline__ void dsp_bbe_power_on(void)
{
    /* power on BBE16 */
    set_hi_pwr_ctrl6_bbe16_mtcmos_ctrl_en(1);
    while (!get_hi_pwr_stat1_bbe16_mtcmos_rdy_stat()) ;
}

static __inline__ void dsp_iso_clamp_dis(void)
{
    /* disable ISO clamp */
    set_hi_pwr_ctrl5_bbe16_iso_ctrl_dis(1);
}

static __inline__ void dsp_bbe_power_off(void)
{
    /* power down DSP0 */
    set_hi_pwr_ctrl7_bbe16_mtcmos_ctrl_dis(1);
}

static __inline__ void dsp_iso_clamp_en(void)
{
    /* enable ISO clamp */
    set_hi_pwr_ctrl4_bbe16_iso_ctrl_en(1);
}

/******** dsp end *********/
#endif
#endif
