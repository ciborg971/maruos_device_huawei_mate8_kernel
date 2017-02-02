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
#ifndef __BSP_SHARED_DDR_H__
#define __BSP_SHARED_DDR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_memmap.h"
#include "bsp_s_memory.h"
#include "product_config.h"

/*****************************************************************************************************************************
*�����ڴ����ַ
******************************************************************************************************************************/
#if !defined(__KERNEL__) && !defined(__OS_VXWORKS__) && !defined(__OS_RTOSCK__)
#define SHM_BASE_ADDR                  (HI_SHARED_DDR_BASE_ADDR)
#else
#define SHM_BASE_ADDR                  (g_mem_ctrl.sddr_virt_addr)
#define SHD_DDR_V2P(addr)              (void *)((unsigned long)(addr) - (unsigned long)g_mem_ctrl.sddr_virt_addr + (unsigned long)g_mem_ctrl.sddr_phy_addr)
#define SHD_DDR_P2V(addr)              (void *)((unsigned long)(addr) - (unsigned long)g_mem_ctrl.sddr_phy_addr + (unsigned long)g_mem_ctrl.sddr_virt_addr)
#endif
/*****************************************************************************************************************************
*��ģ�鶨���ƫ�ƺʹ�С,ƫ�ƶ���:SHM_OFFSET_XXX  ��С����:SHM_SIZE_XXXX������������KB������� SHM_OFFSET_SLICE_MEM ���
******************************************************************************************************************************/
#define SHM_SIZE_HIFI_MBX   			(DDR_HIFI_MBX_SIZE)
#define SHM_OFFSET_HIFI_MBX		    	(0x0)

#define SHM_SIZE_HIFI   				(10*1024)
#define SHM_OFFSET_HIFI		    		(SHM_OFFSET_HIFI_MBX + SHM_SIZE_HIFI_MBX)

#define SHM_SIZE_TLPHY                  (12*1024)
#define SHM_OFFSET_TLPHY                (SHM_OFFSET_HIFI + SHM_SIZE_HIFI)

#define SHM_SIZE_TEMPERATURE	     	(3*1024)
#define SHM_OFFSET_TEMPERATURE	    	(SHM_OFFSET_TLPHY + SHM_SIZE_TLPHY)

#define SHM_SIZE_DDM_LOAD				(1*1024)
#define SHM_OFFSET_DDM_LOAD				(SHM_OFFSET_TEMPERATURE + SHM_SIZE_TEMPERATURE)

/* v7r2 a9_boot_addr ���뷽ʽ�����ã���Ҫ64/32/16KB/8KB���� */
#define SHM_SIZE_MEM_APPA9_PM_BOOT      (0x10000)    /* 64Kȫռ�� */
#define SHM_OFFSET_APPA9_PM_BOOT        (SHM_OFFSET_DDM_LOAD + SHM_SIZE_DDM_LOAD)

#define SHM_SIZE_MEM_MDMA9_PM_BOOT      (0x2000)
#define SHM_OFFSET_MDMA9_PM_BOOT        (SHM_OFFSET_APPA9_PM_BOOT + SHM_SIZE_MEM_APPA9_PM_BOOT)

/*CT BT*/
#define SHM_SIZE_TENCILICA_MULT_BAND    (0x8000)
#define SHM_OFFSET_TENCILICA_MULT_BAND  (SHM_OFFSET_MDMA9_PM_BOOT + SHM_SIZE_MEM_MDMA9_PM_BOOT)

/* �ܴ�СΪ236KB, ����, GUͨ��192KB, Lͨ��40KB, icc���ƽṹ��Ϊҳ����ȡΪ4KB */
#define SHM_SIZE_ICC                    (0x61800)
#define SHM_OFFSET_ICC                  (SHM_OFFSET_TENCILICA_MULT_BAND + SHM_SIZE_TENCILICA_MULT_BAND)

/* �ܴ�СΪ64KB, ����, ���ڴ�AXI(SRAM)�ƹ�����IPF��������IPF�͹��ĵļĴ�������ָ�, �׵�ַҪ��8�ֽڶ��� */
#define SHM_SIZE_IPF                    (0x10000)
#define SHM_OFFSET_IPF             	    (SHM_OFFSET_ICC + SHM_SIZE_ICC)

#define SHM_SIZE_WAN                    (0x8000)
#define SHM_OFFSET_WAN             	    (SHM_OFFSET_IPF + SHM_SIZE_IPF)

#define SHM_SIZE_NV  				    (NV_DDR_SIZE)
#define SHM_OFFSET_NV				    (SHM_OFFSET_WAN + SHM_SIZE_WAN)

#define SHM_SIZE_M3_MNTN     			(0x20000)
#define SHM_OFFSET_M3_MNTN		    	(SHM_OFFSET_NV + SHM_SIZE_NV)

#define SHM_SIZE_TIMESTAMP				(1*1024)
#define SHM_OFFSET_TIMESTAMP			(SHM_OFFSET_M3_MNTN + SHM_SIZE_M3_MNTN)

#define SHM_SIZE_IOS     		        (6*1024)
#define SHM_OFFSET_IOS		            (SHM_OFFSET_TIMESTAMP + SHM_SIZE_TIMESTAMP)

#define SHM_SIZE_RESTORE_AXI            (96*1024)
#define SHM_OFFSET_RESTORE_AXI          (SHM_OFFSET_IOS + SHM_SIZE_IOS)

/* ��ѹԴ���Կ��Ʊ���С��Ԥ����ʵ��ʹ��Ϊ0x85c */
#define SHM_SIZE_PMU                    (3*1024)
#define SHM_OFFSET_PMU                  (SHM_OFFSET_RESTORE_AXI + SHM_SIZE_RESTORE_AXI)

/* ������ */
#define SHM_SIZE_PTABLE                 (2*1024)
#define SHM_OFFSET_PTABLE               (SHM_OFFSET_PMU + SHM_SIZE_PMU)

/* modem ������λ��� */
#define SHM_SIZE_CCORE_RESET            (0x400)
#define SHM_OFFSET_CCORE_RESET          (SHM_OFFSET_PTABLE + SHM_SIZE_PTABLE)

/* pm om log�� */
#define SHM_SIZE_PM_OM                  (256*1024)
#define SHM_OFFSET_PM_OM                (SHM_OFFSET_CCORE_RESET + SHM_SIZE_CCORE_RESET)

#define SHM_SIZE_M3PM               (0x1000)
#define SHM_OFFSET_M3PM            (SHM_OFFSET_PM_OM + SHM_SIZE_PM_OM)

/*���ڷ��䲻����KB����ķ���*/
#define SHM_SIZE_SLICE_MEM              (0x1000)
#define SHM_OFFSET_SLICE_MEM            (SHM_OFFSET_M3PM + SHM_SIZE_M3PM)

#define SHM_SIZE_OSA_LOG              (1024)
#define SHM_OFFSET_OSA_LOG            (SHM_OFFSET_SLICE_MEM + SHM_SIZE_SLICE_MEM)

#define SHM_SIZE_WAS_LOG              (1024)
#define SHM_OFFSET_WAS_LOG            (SHM_OFFSET_OSA_LOG + SHM_SIZE_OSA_LOG)

/* sram needs store/restore since hi6950 because of sram powerdown */
#define SHM_SIZE_SRAM_BAK               (HI_SRAM_MEM_SIZE)
#define SHM_OFFSET_SRAM_BAK             (SHM_OFFSET_WAS_LOG + SHM_SIZE_WAS_LOG)  

#ifdef CONFIG_SRAM_SECURE
/* for sec, move sram to ddr */
#define SHM_SIZE_SRAM_TO_DDR            (HI_SRAM_MEM_SIZE)
#else
#define SHM_SIZE_SRAM_TO_DDR            (0)
#endif
#define SHM_OFFSET_SRAM_TO_DDR          (SHM_OFFSET_SRAM_BAK + SHM_SIZE_SRAM_BAK)

/*�����ڴ�ʣ�ಿ��ƫ�ƺʹ�С*/
#define SHM_OFFSET_MEMMGR               (SHM_SIZE_SRAM_TO_DDR + SHM_OFFSET_SRAM_TO_DDR)
#define SHM_SIZE_MEMMGR                 (DDR_SHARED_MEM_SIZE - SHM_OFFSET_MEMMGR)

/**************************************���ڷ��䲻����Kb����ķ���*******************************************************
*����С�ڴ�ķ��䶼����SHM_OFFSET_SLICE_MEM �ڷ��䣬ĿǰSHM_OFFSET_SLICE_MEM��С0x1000,����ע�ⲻҪ����
************************************************************************************************************************/
#define SHM_SIZE_MEMMGR_FLAG            (0x180)
#define SHM_OFFSET_MEMMGR_FLAG          (SHM_OFFSET_SLICE_MEM)

#define SHM_SIZE_SYNC                   (0x60)
#define SHM_OFFSET_SYNC             	(SHM_OFFSET_MEMMGR_FLAG + SHM_SIZE_MEMMGR_FLAG)

#define SHM_SIZE_AT_FLAG                (0x4)
#define SHM_OFFSET_AT_FLAG              (SHM_OFFSET_SYNC + SHM_SIZE_SYNC)

#define SHM_SIZE_CSHELL_FLAG            (0x4)
#define SHM_OFFSET_CHSELL_FLAG          (SHM_OFFSET_AT_FLAG + SHM_SIZE_AT_FLAG)

#define SHM_SIZE_DSP_FLAG               (0x4)
#define SHM_OFFSET_DSP_FLAG             (SHM_OFFSET_CHSELL_FLAG + SHM_SIZE_CSHELL_FLAG)

#define SHM_SIZE_CDSP_FLAG               (0x4)
#define SHM_OFFSET_CDSP_FLAG             (SHM_OFFSET_DSP_FLAG + SHM_SIZE_DSP_FLAG)

/*pastar dpm flag*/
#define SHM_SIZE_PASTAR_DPM_INFO        (0xc)
#define SHM_OFFSET_PASTAR_DPM_INFO      (SHM_OFFSET_CDSP_FLAG + SHM_SIZE_CDSP_FLAG)

/* L2CACHE���ر�� */
#define SHM_SIZE_CCORE_L2CACHE          (0x4)
#define SHM_OFFSET_CCORE_L2CACHE        (SHM_OFFSET_PASTAR_DPM_INFO + SHM_SIZE_PASTAR_DPM_INFO)

/* modem ������ */
#define SHM_SIZE_LOADM                  (0x0C)
#define SHM_OFFSET_LOADM                (SHM_OFFSET_CCORE_L2CACHE + SHM_SIZE_CCORE_L2CACHE)

/*bbp power flag*/
#define SHM_SIZE_MEMREPAIR              (0x20)
#define SHM_OFFSET_MEMREPAIR            (SHM_OFFSET_LOADM + SHM_SIZE_LOADM)
/* nand spec info */
#define SHM_SIZE_NAND_SPEC              (24)
#define SHM_OFFSET_NAND_SPEC            (SHM_OFFSET_MEMREPAIR + SHM_SIZE_MEMREPAIR)

#define SHM_SIZE_VERSION                (0x20)
#define SHM_OFFSET_VERSION              (SHM_OFFSET_NAND_SPEC + SHM_SIZE_NAND_SPEC)

#define SHM_SIZE_UART_FLAG              (0xC)
#define SHM_OFFSET_UART_FLAG            (SHM_OFFSET_VERSION + SHM_SIZE_VERSION)

/* m3pm om */
#define SHM_SIZE_M3PM_LOG               (0x80)
#define SHM_OFFSET_M3PM_LOG             (SHM_OFFSET_UART_FLAG + SHM_SIZE_UART_FLAG)


/* autotest pan_rpc */
#define SHM_SIZE_PAN_RPC                (0x4)
#define SHM_OFFSET_PAN_RPC              (SHM_OFFSET_M3PM_LOG + SHM_SIZE_M3PM_LOG)
#define SHM_SIZE_MODEM_SR_STAMP         (0x170)
#define SHM_OFFSET_MODEM_SR_STAMP       (SHM_OFFSET_PAN_RPC + SHM_SIZE_PAN_RPC)


#ifndef CONFIG_MODULE_BUSSTRESS
#define SHM_SIZE_BUSSTRESS_TEST         (70*1024)
#else
#define SHM_SIZE_BUSSTRESS_TEST         (0)
#endif

#define SHM_OFFSET_BUSSTRESS_TEST       (SHM_OFFSET_MODEM_SR_STAMP + SHM_SIZE_MODEM_SR_STAMP)


#ifdef __cplusplus
}
#endif

#endif    /* __BSP_SHARED_DDR_H__ */



