
#include <string.h>
#include <securec.h>
#include <product_config.h>
#include <osl_types.h>
#include <of.h>
#include <mdrv_memory.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <drv_mailbox_cfg.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <bsp_om.h>
#include <bsp_sysctrl.h>
#include <bsp_dump_mem.h>
#include <bsp_dump_drv.h>
#include <bsp_hwadp.h>

#define hwadp_printf(fmt,...)   (bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HWADP,fmt,##__VA_ARGS__))

struct ul_base_addr_info {
    BSP_IP_TYPE_E enIPType;
    void *ul_base_addr;
};

struct ul_int_info {
    BSP_INT_TYPE_E enIPType;
    unsigned int   irq_num;
};

struct ul_mem_info {
    BSP_DDR_TYPE_E enIPType;
    void *mem_base_addr;
    unsigned int size;
};

struct gu_ctrl {
    void *addr_virt;
    void *addr_phy;
    unsigned int mem_size;
};

//static struct ul_base_addr_info g_base_addrs[BSP_IP_TYPE_BUTTOM];
/*lint --e{551}*/
static struct ul_int_info  g_irq_nums[BSP_INT_TYPE_BUTTOM];
static struct ul_mem_info  g_mem_info[BSP_DDR_TYPE_BUTTOM];
BSP_AXI_SECT_INFO_S        g_sram_info[BSP_AXI_SECT_TYPE_BUTTOM];
BSP_DDR_SECT_INFO_S        g_ddr_info[BSP_DDR_SECT_TYPE_BUTTOM];
static struct gu_ctrl      g_gu_ctrl;


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
	[BSP_IP_TYPE_BBPDMA]     ={BSP_IP_TYPE_BBPDMA,     (void*)HI_BBP_DMA_BASE_ADDR},
	[BSP_IP_TYPE_BBPDBG]     ={BSP_IP_TYPE_BBPDBG,     (void*)HI_BBP_DBG_BASE_ADDR},
	[BSP_IP_TYPE_BBPSRC]     ={BSP_IP_TYPE_BBPSRC,     (void*)HI_BBP_SRC_BASE_ADDR},
	[BSP_IP_TYPE_SOCP]       ={BSP_IP_TYPE_SOCP,       (void*)HI_SOCP_REGBASE_ADDR},

    /*Balong one基地址变更-2,20150206讨论确定*/
    [BSP_IP_TYPE_BBP_COMM]   ={BSP_IP_TYPE_BBP_COMM,   (void*)HI_CTU_BASE_ADDR},
    [BSP_IP_TYPE_BBP_COMM_ON]={BSP_IP_TYPE_BBP_COMM_ON,(void*)HI_BBP_COMM_ON_BASE_ADDR},
    [BSP_IP_TYPE_BBP_CDMA]   ={BSP_IP_TYPE_BBP_CDMA,   (void*)HI_BBP_CDMA_BASE_ADDR},
    [BSP_IP_TYPE_BBP_CDMA_ON]={BSP_IP_TYPE_BBP_CDMA_ON,(void*)HI_BBP_CDMA_ON_BASE_ADDR},
    [BSP_IP_TYPE_BBP_GLB_ON] ={BSP_IP_TYPE_BBP_GLB_ON, (void*)HI_BBP_GLB_ON_BASE_ADDR},
    [BSP_IP_TYPE_BBP_GSDR]   ={BSP_IP_TYPE_BBP_GSDR,   (void*)HI_BBP_GSDR_BASE_ADDR},
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
* 函 数 名  :  mdrv_getmeminfo
*
* 功能描述  :  mem内存查询
*
* 输入参数  :  enSectType: 需要查询的mem类型
*
* 输出参数  :  *addr: mem地址，*size:mem大小
*
* 返 回 值  :  MDRV_OK/MDRV_ERROR
*
* 修改记录  :
*****************************************************************************/
int mdrv_getmeminfo(BSP_DDR_TYPE_E enDdrType, unsigned int *addr, unsigned int *size)
{
    int i = 0;

    if(!addr || !size || (enDdrType >= BSP_DDR_TYPE_BUTTOM))
        return MDRV_ERROR;

    for(i = 0; i < BSP_DDR_TYPE_BUTTOM; i++) {
        if(enDdrType == g_mem_info[i].enIPType) {
            *addr = (unsigned int)g_mem_info[i].mem_base_addr;
            *size = g_mem_info[i].size;
            return MDRV_OK;
        }
    }

    return MDRV_ERROR;
}

/*****************************************************************************
* 函 数 名  :  mdrv_get_fix_axi_addr
*
* 功能描述  :  AXI内存段查询接口
*
* 输入参数  :  enSectType: 需要查询的内存段类型
*
* 输出参数  :  pstSectInfo:  查询到的内存段信息
*
* 返 回 值  :  BSP_OK/BSP_ERROR
*
* 修改记录  :
*****************************************************************************/
int mdrv_get_fix_axi_addr(BSP_AXI_SECT_TYPE_E enSectType, BSP_AXI_SECT_INFO_S *pstSectInfo)
{
    if(BSP_NULL == pstSectInfo)
    {
        return BSP_ERROR;
    }

    (void)memcpy_s((void *)pstSectInfo,sizeof(BSP_AXI_SECT_INFO_S),(const void *)(&g_sram_info[enSectType]), sizeof(BSP_AXI_SECT_INFO_S));

    return BSP_OK;
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

    (void)memcpy_s((void *)pstSectInfo, sizeof(BSP_DDR_SECT_INFO_S),(const void *)(&g_ddr_info[pstSectQuery->enSectType]), sizeof(BSP_DDR_SECT_INFO_S));

    return MDRV_OK;
}

/*请徐经翠移走*/
void l2_cache_sync(void)
{
#if defined (HI_MDMA9_L2_REGBASE_ADDR) && defined (INCLUDE_L2_CACHE)
    (*(volatile unsigned *) (HI_MDMA9_L2_REGBASE_ADDR_VIRT+0x730)) = (0);
#endif
}

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
* 函 数 名  :  bsp_hwadp_register_mem_info
*
* 功能描述  :  底软注册到hwadp模块供上层使用的mem信息
*
* 输入参数  :  type: 需提供mem信息对应的枚举类型；
*              *addr:需提供的mem的地址；
*              size: 需提供的mem的大小；
*
* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int bsp_hwadp_register_mem_info(BSP_DDR_TYPE_E type, void *addr, unsigned int size)
{
    if(type >= BSP_DDR_TYPE_BUTTOM)
        return BSP_ERROR;

    g_mem_info[type].enIPType= type;
    g_mem_info[type].mem_base_addr = addr;
    g_mem_info[type].size = size;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  :  bsp_hwadp_register_sram
*
* 功能描述  :  底软注册到hwadp模块供上层使用的sram信息
*
* 输入参数  :  type: 需提供mem信息对应的枚举类型；
*              *sram_virt:需提供的sram的虚拟地址；
*              *sram_phy:需提供的sram的物理地址；
*              size: 需提供的sram的大小；
*
* 返 回 值  :  BSP_OK:成功；BSP_ERROR:失败。
*
* 修改记录  :
*****************************************************************************/
int bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_E type, void *sram_virt, void *sram_phy, unsigned int size)
{
    if(type >= BSP_AXI_SECT_TYPE_BUTTOM)
        return BSP_ERROR;

    g_sram_info[type].enSectType= type;
    g_sram_info[type].pSectVirtAddr = sram_virt;
    g_sram_info[type].pSectPhysAddr = sram_phy;
    g_sram_info[type].ulSectSize = size;

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
#define SRAM_CDSP_MNTN_INFO_ADDR          (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CDSP_MNTN_INFO))
#define SRAM_CDSP_DRV_ADDR                (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CDSP_DRV))

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

    /*注册mem info*/
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_GU,
                                      (void *)DDR_UPA_ADDR,
                                      DDR_UPA_SIZE + DDR_CQI_SIZE + DDR_APT_SIZE + DDR_ET_SIZE + DDR_NV_SIZE + DDR_ZSP_UP_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_TLPHY,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TLPHY),
                                      SHM_SIZE_TLPHY);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_TEMPERATURE,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE),
                                      SHM_SIZE_TEMPERATURE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG,
                                      (void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_RTT_SLEEP_FLAG),
                                       SRAM_SIZE_RTT_SLEEP_FLAG);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_TIMESTAMP,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TIMESTAMP),
                                      SHM_SIZE_TIMESTAMP);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,
                                      (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_DRV),
                                      sizeof(unsigned int));
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_DSP_MNTN_INFO,
                                      (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO),
                                      SRAM_DSP_MNTN_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_BANDNV,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TENCILICA_MULT_BAND),
                                      SHM_SIZE_TENCILICA_MULT_BAND);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_IMAGE,(void*)DDR_TLPHY_IMAGE_ADDR,DDR_TLPHY_IMAGE_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_LPHY_SDR,(void*)DDR_LPHY_SDR_ADDR,DDR_LPHY_SDR_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_LCS,(void*)DDR_LCS_ADDR,DDR_LCS_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_HIFI,(void*)DDR_HIFI_ADDR,DDR_HIFI_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,(void*)MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG),MAILBOX_HEAD_LEN);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,(void*)MAILBOX_HEAD_ADDR(HIFI, BBE16, MSG),MAILBOX_HEAD_LEN);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,(void*)MAILBOX_QUEUE_ADDR(BBE16, HIFI, MSG),MAILBOX_QUEUE_SIZE(BBE16, HIFI, MSG));
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,(void*)MAILBOX_QUEUE_ADDR(HIFI, BBE16, MSG),MAILBOX_QUEUE_SIZE(HIFI, BBE16, MSG));

    /*注册sram*/
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_TEMPERATURE, (void *)SRAM_TEMP_PROTECT_ADDR,
                                   (void *)SRAM_V2P(SRAM_TEMP_PROTECT_ADDR), SRAM_TEMP_PROTECT_SIZE);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_DICC, MEMORY_AXI_DICC_ADDR,
                                   (void *)SRAM_V2P((unsigned long)MEMORY_AXI_DICC_ADDR), 8);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_HIFI, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_HIFI),
                                   (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_HIFI), SHM_SIZE_HIFI);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_TTF_BBP, (void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER),
                                   (void *)SRAM_V2P((void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)), SRAM_SIZE_GU_MAC_HEADER);

    /*注册ddr*/
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_WAN, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN),
                                  (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN), SHM_SIZE_WAN);
	ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_MODEM_SR_STAMP, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MODEM_SR_STAMP),
                                  (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MODEM_SR_STAMP), SHM_SIZE_MODEM_SR_STAMP);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_HIFI, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DDR_HIFI_ADDR,
                                  (void *)DDR_HIFI_ADDR, DDR_HIFI_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_SOCP, BSP_DDR_SECT_ATTR_NONCACHEABLE, ioremap_wc((MMU_VA_T)DDR_SOCP_ADDR, DDR_SOCP_SIZE),
                                   (void *)DDR_SOCP_ADDR, DDR_SOCP_SIZE);

    /**************************************GU   memmap   begin**************************/
    g_gu_ctrl.addr_phy = (void *)DDR_GU_ADDR;
    g_gu_ctrl.mem_size = DDR_GU_SIZE;
    g_gu_ctrl.addr_virt = ioremap_wc((MMU_VA_T)g_gu_ctrl.addr_phy, g_gu_ctrl.mem_size);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_UPA, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_UPA_ADDR),
                                  (void *)DDR_UPA_ADDR, DDR_UPA_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_CQI, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_CQI_ADDR),
                                  (void *)DDR_CQI_ADDR, DDR_CQI_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_APT, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_APT_ADDR),
                                  (void *)DDR_APT_ADDR, DDR_APT_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ET, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_ET_ADDR),
                                  (void *)DDR_ET_ADDR, DDR_ET_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_NV, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_NV_ADDR),
                                  (void *)DDR_NV_ADDR, DDR_NV_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ZSP_UP, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_ZSP_UP_ADDR),
                                   (void *)DDR_ZSP_UP_ADDR, DDR_ZSP_UP_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ECS_TEE, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DRV_DDR_PHY_TO_VIRT((void *)DDR_ECS_TEE_ADDR),
                                   (void *)DDR_ECS_TEE_ADDR, DDR_ECS_TEE_SIZE);
    /**************************************GU   memmap   end**************************/

    if(ret == BSP_OK)
        hwadp_printf("hwadp init ok.\n");
    else
        hwadp_printf("hwadp init fail.\n");
    
    return ret;
}


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
 函 数 名  : bsp_show_irq_num
 功能描述  : 打印中断信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
void bsp_show_irq_num(void)
{
    unsigned int i;

    for(i = 0; i < BSP_INT_TYPE_BUTTOM; i++)
    {
        hwadp_printf("irq_num[%d] = %d\n", i, mdrv_int_get_num(i));
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
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CDSP_DRV_ADDR", SRAM_V2P(SRAM_CDSP_DRV_ADDR), SRAM_CDSP_DRV_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CDSP_MNTN_INFO_ADDR", SRAM_V2P(SRAM_CDSP_MNTN_INFO_ADDR), SRAM_CDSP_MNTN_INFO_ADDR);
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
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MODEM_SR_STAMP", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MODEM_SR_STAMP), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MODEM_SR_STAMP, SHM_SIZE_MODEM_SR_STAMP);
    hwadp_printf("total size: 0x%x\n", total_size);
}

unsigned int   * MemAddr32 = 0x00000000;
/*******************************************************************************
* writeM - write a unsigned int value to perihical address
* adpt for gu
* RETURNS: N/A
*/
void writeM(unsigned int pAddr, unsigned int value)
{
    *(volatile unsigned int *)(pAddr)=value;
}

/***********************************************************
 Function: memRead32--read memory and display the value
            adpt for gu
 Input:    the start address
 return:   void
************************************************************/
void memRead32 (unsigned int uiMemAddr32)
{
    if (0 != uiMemAddr32)
    {
         MemAddr32 = (unsigned int *)(uiMemAddr32 & 0xFFFFFFFC);
    }

    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x0), 
            readl((unsigned int)(MemAddr32+0x0)),
            readl((unsigned int)(MemAddr32+0x1)),
            readl((unsigned int)(MemAddr32+0x2)),
            readl((unsigned int)(MemAddr32+0x3)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x4),
            readl((unsigned int)(MemAddr32+0x4)),
            readl((unsigned int)(MemAddr32+0x5)),
            readl((unsigned int)(MemAddr32+0x6)),
            readl((unsigned int)(MemAddr32+0x7)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x8),
            readl((unsigned int)(MemAddr32+0x8)),
            readl((unsigned int)(MemAddr32+0x9)),
            readl((unsigned int)(MemAddr32+0xa)),
            readl((unsigned int)(MemAddr32+0xb)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0xc),
            readl((unsigned int)(MemAddr32+0xc)),
            readl((unsigned int)(MemAddr32+0xd)),
            readl((unsigned int)(MemAddr32+0xe)),
            readl((unsigned int)(MemAddr32+0xf)));        
    MemAddr32 += 0x10;
}

/***********************************************************
 Function: r--simple read memory command
           adpt for gu
 Input:    the start address
 return:  void
************************************************************/
void r(unsigned int newMemAddr32)
{
    memRead32(newMemAddr32);
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

