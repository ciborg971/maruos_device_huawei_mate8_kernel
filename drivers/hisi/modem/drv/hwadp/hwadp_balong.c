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

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <product_config.h>
#include <osl_types.h>
#include <mdrv_memory.h>
#include <drv_mailbox_cfg.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <bsp_om.h>
#include <bsp_sysctrl.h>
#include <bsp_dump_mem.h>
#include <bsp_dump_drv.h>
#include <bsp_hwadp.h>

#define hwadp_printf(fmt, ...) printk(fmt , ##__VA_ARGS__)

struct ul_base_addr_info {
    BSP_IP_TYPE_E enIPType;
    void *ul_base_addr;
};

struct ul_int_info {
    BSP_INT_TYPE_E enIPType;
    unsigned int   irq_num;
};

struct gu_ctrl {
    void *addr_virt;
    void *addr_phy;
    unsigned int mem_size;
};

//static struct ul_base_addr_info g_base_addrs[BSP_IP_TYPE_BUTTOM];
/*lint --e{551}*/
static struct ul_int_info  g_irq_nums[BSP_INT_TYPE_BUTTOM];
BSP_DDR_SECT_INFO_S        g_ddr_info[BSP_DDR_SECT_TYPE_BUTTOM];
static struct gu_ctrl      g_gu_ctrl;

void *DRV_DDR_VIRT_TO_PHY(void *ulVAddr);
void *DRV_DDR_PHY_TO_VIRT(void *ulPAddr);
void *DRV_AXI_VIRT_TO_PHY(void *ulVAddr);
void *DRV_AXI_PHY_TO_VIRT(void *ulPAddr);

#ifndef HI_BBP_CDMA_BASE_ADDR
#define HI_BBP_CDMA_BASE_ADDR 0
#endif

#ifndef HI_BBP_CDMA_ON_BASE_ADDR
#define HI_BBP_CDMA_ON_BASE_ADDR 0
#endif

#ifndef HI_BBP_GLB_ON_BASE_ADDR
#define HI_BBP_GLB_ON_BASE_ADDR 0
#endif

#ifndef HI_BBP_GSDR_BASE_ADDR
#define HI_BBP_GSDR_BASE_ADDR 0
#endif

/* BBP相关移走后删除 */
static struct ul_base_addr_info g_base_addrs[BSP_IP_TYPE_BUTTOM] = {
	[BSP_IP_TYPE_GBBP]      ={BSP_IP_TYPE_GBBP,        (void*)HI_GBBP_REG_BASE_ADDR},
	[BSP_IP_TYPE_GBBP_DRX]  ={BSP_IP_TYPE_GBBP_DRX,    (void*)HI_GBBP_DRX_REG_BASE_ADDR},
	[BSP_IP_TYPE_GBBP1]     ={BSP_IP_TYPE_GBBP1,       (void*)HI_GBBP1_REG_BASE_ADDR},
	[BSP_IP_TYPE_GBBP1_DRX] ={BSP_IP_TYPE_GBBP1_DRX,   (void*)HI_GBBP1_DRX_REG_BASE_ADDR},
	[BSP_IP_TYPE_WBBP]      ={BSP_IP_TYPE_WBBP,        (void*)HI_WBBP_REG_BASE_ADDR},
	[BSP_IP_TYPE_WBBP_DRX]  ={BSP_IP_TYPE_WBBP_DRX,    (void*)HI_WBBP_DRX_REG_BASE_ADDR},
	[BSP_IP_TYPE_TDSSYS]     ={BSP_IP_TYPE_TDSSYS,     (void*)HI_BBP_TSTU_BASE_ADDR},
	[BSP_IP_TYPE_BBPMASTER]  ={BSP_IP_TYPE_BBPMASTER,  (void*)HI_BBPMASTER_REG_BASE_ADDR},
	[BSP_IP_TYPE_CTU]        ={BSP_IP_TYPE_CTU,        (void*)HI_CTU_BASE_ADDR}, /* 这个地址保证多模平台可正常工作，现由BSP_CONFIG_V7R2_ASIC宏控制 */
};

/****************************对上层提供的接口*********************************************/

/*****************************************************************************
* 函 数 名  :  mdrv_misc_get_ip_baseaddr
*
* 功能描述  :  IP地址查询
*
* 输入参数  :  enSectType: 需要查询的IP类型
*
* 返 回 值  :  IP基地址/NULL
*
* 修改记录  :
*****************************************************************************/
void* mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_E enIPType)
{
    int i;

    if(enIPType >= BSP_IP_TYPE_BUTTOM)
        return NULL;

    for(i = 0; i < BSP_IP_TYPE_BUTTOM; i++) {
        if(enIPType == g_base_addrs[i].enIPType)
            return g_base_addrs[i].ul_base_addr;
    }

    return NULL;
}

/*****************************************************************************
* 函 数 名  :  mdrv_get_fix_ddr_addr
*
* 功能描述  :  DDR内存段查询接口
*
* 输入参数  :  pstSectQuery: 需要查询的内存段类型、属性
*
* 输出参数  :  pstSectInfo:  查询到的内存段信息
*
* 返 回 值  :  MDRV_OK/MDRV_ERROR
*
* 修改记录  :
*****************************************************************************/
int mdrv_get_fix_ddr_addr(BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo)
{
    if((BSP_NULL == pstSectQuery) || (BSP_NULL == pstSectInfo) || (BSP_NULL == g_ddr_info[pstSectQuery->enSectType].pSectPhysAddr))
    {
        return MDRV_ERROR;
    }

    (void)memcpy((void *)pstSectInfo, (const void *)(&g_ddr_info[pstSectQuery->enSectType]), sizeof(BSP_DDR_SECT_INFO_S));

    return MDRV_OK;
}

/*****************************************************************************
* 函 数 名  :  mdrv_virt_to_phy
*
* 功能描述  :  虚地址转换实地址
*
* 输入参数  :  虚地址
*
* 返 回 值  :  实地址
*
* 修改记录  :
*****************************************************************************/
void*  mdrv_virt_to_phy (MEM_MODE_TYPE_E mode, void* lPAddr)
{
    switch(mode)
    {
        case MEM_DDR_MODE:
            return (void *)DRV_DDR_VIRT_TO_PHY(lPAddr);
            break;
        case MEM_AXI_MODE:
            return (void *)DRV_AXI_VIRT_TO_PHY(lPAddr);
            break;
        default:
            return NULL;
            break;
    }
}

/*****************************************************************************
* 函 数 名  :  mdrv_phy_to_virt
*
* 功能描述  :  实地址转换虚地址
*
* 输入参数  :  实地址
*
* 返 回 值  :  虚地址
*
* 修改记录  :
*****************************************************************************/
void*  mdrv_phy_to_virt (MEM_MODE_TYPE_E mode, void* pMem)
{
    switch(mode)
    {
        case MEM_DDR_MODE:
            return (void *)DRV_DDR_PHY_TO_VIRT(pMem);
            break;
        case MEM_AXI_MODE:
            return (void *)DRV_AXI_PHY_TO_VIRT(pMem);
            break;
        default:
            return NULL;
            break;
    }
}

EXPORT_SYMBOL_GPL(mdrv_misc_get_ip_baseaddr);
EXPORT_SYMBOL_GPL(mdrv_get_fix_ddr_addr);
EXPORT_SYMBOL_GPL(mdrv_virt_to_phy);
EXPORT_SYMBOL_GPL(mdrv_phy_to_virt);

/*************************底软注册到hwadp模块接口*********************************/

/*****************************************************************************
* 函 数 名  :  bsp_hwadp_register_base_addr
*
* 功能描述  :  底软注册到hwadp模块供上层使用的base addr
*
* 输入参数  :  type:需提供base addr信息对应的枚举类型。
*              *base_addr:需提供的IP物理地址(已在底软做过映射)
*
* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int bsp_hwadp_register_base_addr(BSP_IP_TYPE_E type, void *base_addr)
{
    if(type >= BSP_IP_TYPE_BUTTOM)
        return BSP_ERROR;

    g_base_addrs[type].enIPType= type;
    g_base_addrs[type].ul_base_addr = base_addr;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  :  bsp_hwadp_register_irq_num
*
* 功能描述  :  底软注册到hwadp模块供上层使用的int信息
*
* 输入参数  :  type:   需提供int信息对应的枚举类型；
*              irq_num:需提供的IP中断号。
*
* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int bsp_hwadp_register_irq_num(BSP_INT_TYPE_E type, unsigned int irq_num)
{
    if(type >= BSP_INT_TYPE_BUTTOM)
        return BSP_ERROR;

    g_irq_nums[type].enIPType= type;
    g_irq_nums[type].irq_num = irq_num;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  :  bsp_hwadp_register_ddr
*
* 功能描述  :  底软注册到hwadp模块供上层使用的ddr信息
*
* 输入参数  :  type: 需提供ddr信息对应的枚举类型；
*              attr: 映射的内存属性；
*              *ddr_virt:需提供的ddr的虚拟地址；
*              *ddr_phy:需提供的ddr的物理地址；
*              size: 需提供的ddr的大小；
*
* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_E type, BSP_DDR_SECT_ATTR_E attr, void *ddr_virt, void *ddr_phy, unsigned int size)
{
    if(type >= BSP_DDR_SECT_TYPE_BUTTOM)
        return BSP_ERROR;

    g_ddr_info[type].enSectType= type;
    g_ddr_info[type].enSectAttr = attr;
    g_ddr_info[type].pSectVirtAddr = ddr_virt;
    g_ddr_info[type].pSectPhysAddr = ddr_phy;
    g_ddr_info[type].ulSectSize = size;

    return BSP_OK;
}


/*************************hwadp 模块内部封装接口*********************************/

/*****************************************************************************
* 函 数 名  :  DRV_DDR_VIRT_TO_PHY
*
* 功能描述  :  DDR内存虚地址往实地址转换
*
* 输入参数  :  ulVAddr；虚地址
*
* 返 回 值  :  实地址
*
* 修改记录  :
*****************************************************************************/
void *DRV_DDR_VIRT_TO_PHY(void *ulVAddr)
{
    if((ulVAddr >= (void *)SHM_BASE_ADDR)
    && (ulVAddr < (void *)((unsigned long)SHM_BASE_ADDR + DDR_SHARED_MEM_SIZE)))
    {
        return SHD_DDR_V2P((unsigned long)ulVAddr);
    }

    if((ulVAddr >= (void *)g_gu_ctrl.addr_virt)
        && (ulVAddr <= (void *)((unsigned long)g_gu_ctrl.addr_virt + g_gu_ctrl.mem_size)))
    {
        return (void *)((unsigned long)ulVAddr - (unsigned long)g_gu_ctrl.addr_virt + (unsigned long)g_gu_ctrl.addr_phy);
    }

    hwadp_printf("DRV_DDR_VIRT_TO_PHY: ulVAddr(0x%p) is invalid!\n", ulVAddr);

    return NULL;
}

/*****************************************************************************
 函 数 名  : DRV_DDR_PHY_TO_VIRT
 功能描述  : DDR内存虚地址往实地址转换
 输入参数  : ulPAddr；实地址
 输出参数  : 无
 返回值    ：虚地址
*****************************************************************************/
void *DRV_DDR_PHY_TO_VIRT(void *ulPAddr)
{
    if((ulPAddr >= (void *)g_mem_ctrl.sddr_phy_addr)
        && (ulPAddr < (void *)((unsigned long)g_mem_ctrl.sddr_phy_addr + g_mem_ctrl.sddr_mem_size)))
    {
        return SHD_DDR_P2V((unsigned long)ulPAddr);
    }

    if((ulPAddr >= (void *)g_gu_ctrl.addr_phy)
    && (ulPAddr < (void *)((unsigned long)g_gu_ctrl.addr_phy + g_gu_ctrl.mem_size)))
    {
        return (void *)((unsigned long)ulPAddr - (unsigned long)g_gu_ctrl.addr_phy + (unsigned long)g_gu_ctrl.addr_virt);
    }

    hwadp_printf("DRV_DDR_PHY_TO_VIRT: ulVAddr(0x%p) is invalid!\n",ulPAddr);
    return NULL;
}

/*****************************************************************************
 函 数 名  : DRV_AXI_VIRT_TO_PHY
 功能描述  : AXI内虚地址往实地址转换
 输入参数  : ulVAddr；虚地址
 输出参数  : 无
 返回值    ：虚地址
*****************************************************************************/
void *DRV_AXI_VIRT_TO_PHY(void *ulVAddr)
{
    return (void *)((unsigned long)ulVAddr - (unsigned long)g_mem_ctrl.sram_virt_addr + (unsigned long)g_mem_ctrl.sram_phy_addr);
}

/*****************************************************************************
 函 数 名  : DRV_AXI_PHY_TO_VIRT
 功能描述  : AXI内实地址往虚地址转换
 输入参数  : ulVAddr；实地址
 输出参数  : 无
 返回值    ：虚地址
*****************************************************************************/
void *DRV_AXI_PHY_TO_VIRT(void *ulPAddr)
{
    return (void *)((unsigned long)ulPAddr - (unsigned long)g_mem_ctrl.sram_phy_addr + (unsigned long)g_mem_ctrl.sram_virt_addr);
}

/*****************************************************************************
* 函 数 名  :  hwadp_dts_register_base_addr
*
* 功能描述  :  通过dts动态注册
*
* 输入参数  :  无

* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void hwadp_dts_register_base_addr(void)
{
    struct device_node *node, *np;
    const __be32 *prop = NULL;
    int na = 0, ns = 0, len = 0;
    void *base_addr = NULL;
    unsigned int ip_type = 0xFFFF, int_type = 0xFFFF, irq_num = 0xFFFF;

    node = of_find_compatible_node(NULL, NULL, "hisilicon,hardware_adapt");
    if (!node) {
        hwadp_printf("dts node not found!\n");
        return;
    }

    for_each_available_child_of_node(node, np) {
        na = of_n_addr_cells(np);
        ns = of_n_size_cells(np);

        prop = of_get_property(np, "reg", &len);
        if (!prop || len < (na + ns) * (int)sizeof(*prop)) {
            hwadp_printf("hwadp:read reg from dts is failed!\n");
            continue;
        }

        if(of_property_read_u32(np, "ip_type", &ip_type)) {
            hwadp_printf("hwadp:read ip_type from dts is failed!\n");
            continue;
        }

        if(of_property_read_u32(np, "int_type", &int_type)) {
            hwadp_printf("hwadp:read int_type from dts is failed!\n");
            continue;
        }

        irq_num = irq_of_parse_and_map(np, 0);

        base_addr = (void*)(unsigned long)of_read_number(prop, na);
        (void)of_iomap(np, 0);

        if((ip_type != 0xFFFF) && (base_addr != NULL)) {
            if(bsp_hwadp_register_base_addr(ip_type, base_addr) != BSP_OK){
                hwadp_printf("hwadp:register base addr is failed!\n");
                continue;
            }
        }

        if((int_type != 0xFFFF) && (irq_num != 0xFFFF)) {
            if(bsp_hwadp_register_irq_num(int_type, irq_num) != BSP_OK){
                hwadp_printf("hwadp:register base addr is failed!\n");
                continue;
            }
        }
    }
}

/*********************************初始化**********************************************/
#define SRAM_USB_ASHELL_ADDR             (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_USB_ASHELL))
#define SRAM_UART_INFO_ADDR              (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->UART_INFORMATION)
#define MEMORY_AXI_DICC_ADDR             (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DICC))
#define SRAM_DSP_DRV_ADDR                (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_DRV))
#define SRAM_PCIE_INFO_ADDR              (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PCIE_INFO)
#define SRAM_SEC_ROOTCA_ADDR             (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_SEC_ROOTCA)
#define SRAM_WDT_AM_FLAG_ADDR            (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_WDT_AM_FLAG))
#define SRAM_WDT_CM_FLAG_ADDR            (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_WDT_CM_FLAG))
#define SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_ACORE_ONOFF_FLAG))
#define SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_CCORE_ONOFF_FLAG))
#define SRAM_CUR_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CUR_CPUFREQ_PROFILE))
#define SRAM_MAX_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MAX_CPUFREQ_PROFILE))
#define SRAM_MIN_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE))
#define SRAM_REBOOT_ADDR                 (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_REBOOT_INFO)
#define SRAM_TEMP_PROTECT_ADDR           (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_TEMP_PROTECT)
#define SRAM_DLOAD_ADDR                  (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DLOAD)
#define SRAM_SEC_SHARE                   (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_SEC_SHARE))
#define SRAM_DSP_MNTN_INFO_ADDR          (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO))
#define SRAM_DFS_DDRC_CFG_ADDR           (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DFS_DDRC_CFG)
#define SRAM_DUMP_POWER_OFF_FLAG_ADDR    (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DUMP_POWER_OFF_FLAG)
#define SRAM_PM_CHECK_ADDR               (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PM_CHECK_ADDR)

/*****************************************************************************
* 函 数 名  :  hwadp_init
*
* 功能描述  :  hwadp模块初始化
*
* 输入参数  :  无

* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int hwadp_init(void)
{
    int ret = BSP_OK;

    /*注册base addr*/
    hwadp_dts_register_base_addr();
    ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_AHB, (void*)DDR_ZSP_UP_ADDR);
    ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL, bsp_sysctrl_addr_phy_byindex(sysctrl_ao));
    if(bsp_sysctrl_addr_phy_byindex(sysctrl_ao) == bsp_sysctrl_addr_phy_byindex(sysctrl_pd))
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_PD, NULL);
    else
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_PD, bsp_sysctrl_addr_phy_byindex(sysctrl_pd));
    if(bsp_sysctrl_addr_phy_byindex(sysctrl_ao) == bsp_sysctrl_addr_phy_byindex(sysctrl_mdm))
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_MDM, NULL);
    else
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_MDM, bsp_sysctrl_addr_phy_byindex(sysctrl_mdm));
    if(bsp_sysctrl_addr_phy_byindex(sysctrl_ao) == bsp_sysctrl_addr_phy_byindex(sysctrl_ap_peri))
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_PERI_SYSCTRL, NULL);
    else
        ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_PERI_SYSCTRL, bsp_sysctrl_addr_phy_byindex(sysctrl_ap_peri));

    /*注册ddr*/
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_WAN, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN),
                                  (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN), SHM_SIZE_WAN);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_SOCP, BSP_DDR_SECT_ATTR_NONCACHEABLE, ioremap_wc(DDR_SOCP_ADDR, DDR_SOCP_SIZE),
                                   (void *)DDR_SOCP_ADDR, DDR_SOCP_SIZE);

    /**************************************GU   memmap   begin**************************/
    g_gu_ctrl.addr_phy = (void *)DDR_GU_ADDR;
    g_gu_ctrl.mem_size = DDR_GU_SIZE;
#ifndef BSP_CONFIG_HI3650
    g_gu_ctrl.addr_virt = ioremap_wc((unsigned long)g_gu_ctrl.addr_phy, g_gu_ctrl.mem_size);
    /*portland在用，2015年底删除(徐铖00266248)*/
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_NV, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_NV_ADDR),
                                  (void *)DDR_NV_ADDR, DDR_NV_SIZE);  
#endif
    /**************************************GU   memmap   end**************************/

    if(ret == BSP_OK)
        hwadp_printf("hwadp init ok.\n");
    else
        hwadp_printf("hwadp init fail.\n");
    
    return ret;
}

subsys_initcall(hwadp_init);

/*********************************可维可测信息**********************************************/

/*****************************************************************************
 函 数 名  : bsp_show_ip_addr
 功能描述  : 打印IP基地址信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void bsp_show_ip_addr(void)
{
    unsigned int i;

    for(i = 0; i < BSP_IP_TYPE_BUTTOM; i++)
    {
        hwadp_printf("ip_addr[%d] = 0x%p\n", i, g_base_addrs[i].ul_base_addr);
    }
}

/*****************************************************************************
 函 数 名  : BSP_DDR_ShowSectInfo
 功能描述  : 打印DDR内存段信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void BSP_DDR_ShowSectInfo(void)
{
    BSP_DDR_SECT_TYPE_E     enSectTypeIndex = (BSP_DDR_SECT_TYPE_E)0;

    hwadp_printf("\ntype       paddr      vaddr      size       attr\n");
    for(; enSectTypeIndex < BSP_DDR_SECT_TYPE_BUTTOM; enSectTypeIndex++)
    {
          hwadp_printf("0x%-8.8x 0x%8p 0x%8p 0x%-8.8x 0x%-8.8x\n\n", \
          g_ddr_info[enSectTypeIndex].enSectType, \
          g_ddr_info[enSectTypeIndex].pSectPhysAddr, \
          g_ddr_info[enSectTypeIndex].pSectVirtAddr, \
          g_ddr_info[enSectTypeIndex].ulSectSize, \
          g_ddr_info[enSectTypeIndex].enSectAttr);
    }
}

/*****************************************************************************
 函 数 名  : show_global_ddr_status
 功能描述  : DDR内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void show_global_ddr_status(void)
{
    hwadp_printf("%-30s%10s%10s\t\n", "name", "phy addr", "size");
    hwadp_printf("%-30s%10x%10x\n", "DDR_APP_ACP_ADDR", DDR_APP_ACP_ADDR, DDR_APP_ACP_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_ACORE_ADDR", DDR_ACORE_ADDR, DDR_ACORE_SIZE);
#ifdef DDR_ACORE_DTS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_ACORE_DTS_ADDR", DDR_ACORE_DTS_ADDR, DDR_ACORE_DTS_SIZE);
#endif
    hwadp_printf("%-30s%10x%10x\n", "DDR_MCORE_ADDR", DDR_MCORE_ADDR, DDR_MCORE_SIZE);
#ifdef DDR_MCORE_DTS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_MCORE_DTS_ADDR", DDR_MCORE_DTS_ADDR, DDR_MCORE_DTS_SIZE);
#endif
    hwadp_printf("%-30s%10p%10x\n", "DDR_SHARED_MEM_ADDR", g_mem_ctrl.sddr_phy_addr, g_mem_ctrl.sddr_mem_size);
    hwadp_printf("%-30s%10x%10x\n", "DDR_MNTN_ADDR", DDR_MNTN_ADDR, DDR_MNTN_SIZE);
    hwadp_printf("%-30s%10p%10x\n", "DDR_GU_ADDR", g_gu_ctrl.addr_phy, g_gu_ctrl.mem_size);
    hwadp_printf("%-30s%10x%10x\n", "DDR_TLPHY_IMAGE_ADDR", DDR_TLPHY_IMAGE_ADDR, DDR_TLPHY_IMAGE_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_LPHY_SDR_ADDR", DDR_LPHY_SDR_ADDR, DDR_LPHY_SDR_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_SOCP_ADDR", DDR_SOCP_ADDR, DDR_SOCP_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_LCS_ADDR", DDR_LCS_ADDR, DDR_LCS_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_HIFI_ADDR", DDR_HIFI_ADDR, DDR_HIFI_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_MDM_ACP_ADDR", DDR_MDM_ACP_ADDR, DDR_MDM_ACP_SIZE);
#ifdef DDR_SECURE_OS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_SECURE_OS_ADDR", DDR_SECURE_OS_ADDR, DDR_SECURE_OS_SIZE);
#endif
}

/*****************************************************************************
 函 数 名  : show_sram_status
 功能描述  : SRAM内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void show_sram_status(void)
{
    /*请依照先后顺序增加打印输出项*/
    int total_size = SRAM_SIZE_SMALL_SECTIONS + SRAM_SIZE_MCU_RESERVE + SRAM_SIZE_ICC + SRAM_SIZE_RTT_SLEEP_FLAG +
                     SRAM_SIZE_GU_MAC_HEADER;/*lint !e569 */
    hwadp_printf("%-30s%10s%10s%10s\n", "name", "phy addr", "virt addr", "size");
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_SMALL_SECTIONS_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS, SRAM_SIZE_SMALL_SECTIONS);/*lint !e778 */
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_MCU_RESERVE_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE, SRAM_SIZE_MCU_RESERVE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_ADDR_ICC", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC, SRAM_SIZE_ICC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_RTT_SLEEP_FLAG_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_RTT_SLEEP_FLAG),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_RTT_SLEEP_FLAG, SRAM_SIZE_RTT_SLEEP_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_GU_MAC_HEADER_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER), (unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER, SRAM_SIZE_GU_MAC_HEADER);
    hwadp_printf("%-30s%10p%10lx%10lx\n", "SRAM_DYNAMIC_SEC_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC), (unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC, SRAM_SIZE_DYNAMIC_SEC);
    hwadp_printf("total size: 0x%x\n", total_size);
    hwadp_printf("detailed info of SRAM_SMALL_SECTIONS_ADDR: \n");
    hwadp_printf("%-30s%10p%10p\n", "SRAM_USB_ASHELL_ADDR", SRAM_V2P(SRAM_USB_ASHELL_ADDR), SRAM_USB_ASHELL_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_UART_INFO_ADDR", SRAM_V2P(SRAM_UART_INFO_ADDR), SRAM_UART_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "MEMORY_AXI_DICC_ADDR", SRAM_V2P(MEMORY_AXI_DICC_ADDR), MEMORY_AXI_DICC_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DSP_DRV_ADDR", SRAM_V2P(SRAM_DSP_DRV_ADDR), SRAM_DSP_DRV_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_PCIE_INFO_ADDR", SRAM_V2P(SRAM_PCIE_INFO_ADDR), SRAM_PCIE_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_SEC_ROOTCA_ADDR", SRAM_V2P(SRAM_SEC_ROOTCA_ADDR), SRAM_SEC_ROOTCA_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_WDT_AM_FLAG_ADDR", SRAM_V2P(SRAM_WDT_AM_FLAG_ADDR), SRAM_WDT_AM_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_WDT_CM_FLAG_ADDR", SRAM_V2P(SRAM_WDT_CM_FLAG_ADDR), SRAM_WDT_CM_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR", SRAM_V2P(SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR), SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR", SRAM_V2P(SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR), SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CUR_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_CUR_CPUFREQ_PROFILE_ADDR), SRAM_CUR_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_MAX_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_MAX_CPUFREQ_PROFILE_ADDR), SRAM_MAX_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_MIN_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_MIN_CPUFREQ_PROFILE_ADDR), SRAM_MIN_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_REBOOT_ADDR", SRAM_V2P(SRAM_REBOOT_ADDR), SRAM_REBOOT_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_TEMP_PROTECT_ADDR", SRAM_V2P(SRAM_TEMP_PROTECT_ADDR), SRAM_TEMP_PROTECT_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DLOAD_ADDR", SRAM_V2P(SRAM_DLOAD_ADDR), SRAM_DLOAD_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_SEC_SHARE", SRAM_V2P(SRAM_SEC_SHARE), SRAM_SEC_SHARE);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DSP_MNTN_INFO", SRAM_V2P(SRAM_DSP_MNTN_INFO_ADDR), SRAM_DSP_MNTN_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DFS_DDRC_CFG_ADDR", SRAM_V2P(SRAM_DFS_DDRC_CFG_ADDR), SRAM_DFS_DDRC_CFG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DUMP_POWER_OFF_FLAG_ADDR", SRAM_V2P(SRAM_DUMP_POWER_OFF_FLAG_ADDR), SRAM_DUMP_POWER_OFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_PM_CHECK_ADDR", SRAM_V2P(SRAM_PM_CHECK_ADDR), SRAM_PM_CHECK_ADDR);
}

/*****************************************************************************
 函 数 名  : show_shared_ddr_status
 功能描述  : 共享内存内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void show_shared_ddr_status(void)
{
    /*请依照先后顺序增加打印输出项*/
    int total_size = SHM_SIZE_HIFI_MBX + SHM_SIZE_HIFI + SHM_SIZE_TLPHY + SHM_SIZE_TEMPERATURE
                   + SHM_SIZE_DDM_LOAD + SHM_SIZE_MEM_APPA9_PM_BOOT + SHM_SIZE_MEM_MDMA9_PM_BOOT
                   + SHM_SIZE_TENCILICA_MULT_BAND + SHM_SIZE_ICC + SHM_SIZE_IPF + SHM_SIZE_WAN
                   + SHM_SIZE_NV + SHM_SIZE_M3_MNTN + SHM_SIZE_TIMESTAMP + SHM_SIZE_IOS
                   + SHM_SIZE_RESTORE_AXI + SHM_SIZE_PMU + SHM_SIZE_PTABLE + SHM_SIZE_CCORE_RESET
                   +SHM_SIZE_PM_OM + SHM_SIZE_M3PM + SHM_SIZE_SLICE_MEM;
    hwadp_printf("%-30s%10s%10s%10s\n", "name", "phy addr", "virt addr", "size");
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_HIFI_MBX", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI_MBX), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI_MBX, SHM_SIZE_HIFI_MBX);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_HIFI", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI, SHM_SIZE_HIFI);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TLPHY", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TLPHY), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TLPHY, SHM_SIZE_TLPHY);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TEMPERATURE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TEMPERATURE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TEMPERATURE, SHM_SIZE_TEMPERATURE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_DDM_LOAD", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DDM_LOAD),(unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DDM_LOAD, SHM_SIZE_DDM_LOAD);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEM_APPA9_PM_BOOT", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_APPA9_PM_BOOT), (unsigned long)SHM_BASE_ADDR + SHM_OFFSET_APPA9_PM_BOOT, SHM_SIZE_MEM_APPA9_PM_BOOT);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEM_MDMA9_PM_BOOT", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT, SHM_SIZE_MEM_MDMA9_PM_BOOT);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TENCILICA_MULT_BAND", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TENCILICA_MULT_BAND), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TENCILICA_MULT_BAND, SHM_SIZE_TENCILICA_MULT_BAND);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_ICC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_ICC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_ICC, SHM_SIZE_ICC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_IPF", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IPF), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IPF, SHM_SIZE_IPF);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_WAN", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAN), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAN, SHM_SIZE_WAN);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_NV", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NV), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NV, SHM_SIZE_NV);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3_MNTN", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3_MNTN), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3_MNTN, SHM_SIZE_M3_MNTN);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TIMESTAMP", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP, SHM_SIZE_TIMESTAMP);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_IOS", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IOS), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IOS, SHM_SIZE_IOS);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_RESTORE_AXI", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RESTORE_AXI), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RESTORE_AXI, SHM_SIZE_RESTORE_AXI);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PMU", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PMU), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PMU, SHM_SIZE_PMU);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PTABLE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PTABLE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PTABLE, SHM_SIZE_PTABLE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CCORE_RESET", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_RESET), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_RESET, SHM_SIZE_CCORE_RESET);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PM_OM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PM_OM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PM_OM, SHM_SIZE_PM_OM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3PM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM, SHM_SIZE_M3PM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SLICE_MEM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SLICE_MEM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SLICE_MEM, SHM_SIZE_SLICE_MEM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_OSA_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_OSA_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_OSA_LOG, SHM_SIZE_OSA_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_WAS_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAS_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAS_LOG, SHM_SIZE_WAS_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SRAM_BAK", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_BAK), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_BAK, SHM_SIZE_SRAM_BAK);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SRAM_TO_DDR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_TO_DDR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_TO_DDR, SHM_SIZE_SRAM_TO_DDR);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMMGR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR, SHM_SIZE_MEMMGR);
    /*不满足KB对齐区，从SLICE_MEM中分配*/
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMMGR_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR_FLAG, SHM_SIZE_MEMMGR_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SYNC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SYNC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SYNC, SHM_SIZE_SYNC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_AT_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_AT_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_AT_FLAG, SHM_SIZE_AT_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CSHELL_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CHSELL_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CHSELL_FLAG, SHM_SIZE_CSHELL_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_DSP_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DSP_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DSP_FLAG, SHM_SIZE_DSP_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CDSP_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CDSP_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CDSP_FLAG, SHM_SIZE_CDSP_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PASTAR_DPM_INFO", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PASTAR_DPM_INFO), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PASTAR_DPM_INFO, SHM_SIZE_PASTAR_DPM_INFO);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CCORE_L2CACHE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_L2CACHE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_L2CACHE, SHM_SIZE_CCORE_L2CACHE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_LOADM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_LOADM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_LOADM, SHM_SIZE_LOADM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMREPAIR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMREPAIR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMREPAIR, SHM_SIZE_MEMREPAIR);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_NAND_SPEC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NAND_SPEC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NAND_SPEC, SHM_SIZE_NAND_SPEC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_VERSION", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_VERSION), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_VERSION, SHM_SIZE_VERSION);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_UART_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_UART_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_UART_FLAG, SHM_SIZE_UART_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3PM_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM_LOG, SHM_SIZE_M3PM_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PAN_RPC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PAN_RPC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PAN_RPC, SHM_SIZE_PAN_RPC);
    hwadp_printf("total size: 0x%x\n", total_size);
}

void show_hpm_temp(void)
{
#ifndef BSP_CONFIG_HI3650
    struct hpm_tem_print *hpm_ptr = ((struct hpm_tem_print * )bsp_dump_get_field_addr(DUMP_M3_BOOST));
    if(hpm_ptr == NULL)
    {
        hwadp_printf("error, can't find DUMP_SAVE_BOOT_MCORE field in dump.\n");
        return;
    }
    hwadp_printf("****************hpm_temperature****************\n");
    hwadp_printf("hpm_uhvt_opc: 0x%x\n", hpm_ptr->hpm_uhvt_opc);
    hwadp_printf("hpm_hvt_opc : 0x%x\n", hpm_ptr->hpm_hvt_opc);
    hwadp_printf("hpm_svt_opc : 0x%x\n", hpm_ptr->hpm_svt_opc);
    hwadp_printf("temperature : %d\n", hpm_ptr->temperature);
    hwadp_printf("up_volt     : %d\n", hpm_ptr->up_volt);
#endif
}

