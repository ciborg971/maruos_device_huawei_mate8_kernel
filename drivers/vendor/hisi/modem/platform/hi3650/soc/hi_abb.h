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
#ifndef __HI_ABB_H__
#define __HI_ABB_H__

#include <osl_bio.h>
#include <bsp_memmap.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ABB_K3V5
#define ABB_TWO_CHN
#define ABB_VERSION_ADDR (0x40)

static __inline__ void hi_abb_control_enable(int id)
{
    unsigned int hi_value = 0;

    if (1 == id)
    {
        hi_value = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

        hi_value |= (1UL << 7);

        writel(hi_value, HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);
    }
}

static __inline__ void hi_abb_control_disable(int id)
{
    unsigned int hi_value = 0;

    if (1 == id)
    {
        hi_value = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

        hi_value &= ~(1UL << 7);

        writel(hi_value, HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);
    }
}

static __inline__ int hi_abb_control_status(int id)
{
    unsigned int hi_value = 0;

    hi_value = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

    hi_value = (hi_value >> 7) & 0x01;

    return (int)hi_value;
}

static __inline__ int hi_abb_get_buffer_status(int id)
{
    unsigned int hi_value = 0;

    hi_value = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x1C);
    hi_value = (hi_value >> 11) & 0x01;

    return (int)hi_value;
}

static __inline__ int hi_abb_get_finish_status(int id)
{
    unsigned int hi_value = 0;

    hi_value = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x1C);
    hi_value = (hi_value >> 13) & 0x01;

    return (int)hi_value;
}


#ifdef __cplusplus
}
#endif

#endif
