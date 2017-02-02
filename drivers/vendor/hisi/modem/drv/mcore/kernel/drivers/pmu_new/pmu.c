#include <product_config.h>
#include <osl_bio.h>
#include <osl_malloc.h>
#include <soc_memmap.h>
#include <libfdt.h>
#include <bsp_shared_ddr.h>

#include <bsp_pm_om.h>
#include <bsp_hardtimer.h>
#include <bsp_pmu.h>
#include <bsp_version.h>
#include <hi_pmu.h>

#define  pmu_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  pmu_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct pmu_ops_strc
{
    void (*pmu_init)(void);
};
static u32 pmic_base_addr;

/*----------------------------------�����Ĵ��������ӿ�---------------------------------------*/
void pmic_reg_write(u32 addr, u32 value)
{
    writel(value,(pmic_base_addr + (addr << 2)));
}
/*****************************************************************************
* �� �� ��  : pmu_reg_read
*
* ��������  : ��pmuоƬ�Ĵ����Ķ�����
*
* �������  : u16 addr����д��ļĴ�����ַ
*             u8 u8Data������������
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void  pmic_reg_read(u32 addr, u32 *pValue)
{
    *pValue = readl(pmic_base_addr + (addr << 2));
}
/*****************************************************************************
* �� �� ��  : pmu_reg_write_mask
*
* ��������  : ��pmuоƬ�Ĵ�����ĳЩbit��λ
*
* �������  : u16 addr����д��ļĴ�����ַ
*             u8 u8Data������������
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void pmic_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    u32 reg_tmp = 0;

    pmic_reg_read(addr, &reg_tmp);
    reg_tmp &= ~mask;
    reg_tmp |= value;
    pmic_reg_write(addr, reg_tmp);
}
int pmic_reg_show(u32 addr)
{
    u32 value = 0;

    pmic_reg_read(addr, &value);
    pmu_print_error("pmuRead addr 0x%x value is 0x%x!!\n",addr,value);
    return (int)value;
}

s32 bsp_pmu_suspend(void)
{
    u32 pmu_version = 0;
	/* ����OUT_PMUA��Դ����ECO */
	pmic_reg_write(0x0A2, 0x01);
	
	/* ����THERMAL ģ��Ref_top����ECO */
	//pmic_reg_write_mask(0x0AA, 0x1, 0x1);
	
	/* ����0x117�Ĵ�������� */
	pmic_reg_write(0x117, 0x6c);
	/* ����xo_core_en��ʹ���ź��øߣ�xo_ldo_enʹ���ź��õ� */
	pmic_reg_write(0x10B, 0x04);

    pmic_reg_read( 5, &pmu_version);
    if( 0x20 == pmu_version ) /* pmu version v520*/
    {
        /* buck2��ldo32���硣
           �� ldo32 �� ddrphy_IO ���緽���£���Ҫ�� ddr����ˢ��/ldo32�µ�֮��ر�buck2
           �������ﲻ�� buck2  */
    }
    else
    {
    	/* ����buck2 �ر� */
    	pmic_reg_write_mask(0x09c, 0x0, 0x2);
    }
    return 0;
}
s32 bsp_pmu_resume(void)
{

    u32 pmu_version = 0;

    pmic_reg_read( 5, &pmu_version);
    if( 0x20 == pmu_version ) /* pmu version v520*/
    {
        /* buck2��ldo32���硣
           �� ldo32 �� ddrphy_IO ���緽���£���Ҫ�� ddr����ˢ��/ldo32�µ�֮��ر�buck2
           ddr �ϵ�֮ǰ �� buck2 �� ldo32
           �������ﲻ�� buck2  */
    }
    else
    {
    	/* ����buck2 �� */
    	pmic_reg_write_mask(0x09c, 0x2, 0x2);
    }

	
	/* ����xo_core_en��ʹ���ź��õͣ�xo_ldo_enʹ���ź��ø� */
	pmic_reg_write(0x10B, 0x07);
	/* ����0x117�Ĵ����� */
	pmic_reg_write(0x117, 0x00);
	

	/* ����THERMAL ģ��Ref_top�˳�ECO */
	//pmic_reg_write_mask(0x0AA, 0x0, 0x1);

	/* ����OUT_PMUA��Դ�˳�ECO */
	pmic_reg_write(0x0A2, 0x00);
    return 0;
}

s32 bsp_pmu_sdio_suspend(void)
{
    return 0;
}
s32 bsp_pmu_sdio_resume(void)
{
    return 0;
}
#if 0

/*��ѯpmuÿһ·ʵ�ʵĿ���״̬���͹��ĵ���*/
void bsp_pmu_volt_state_save(void)
{
    return;
}
u8 bsp_pmu_version_get(void)
{
    return 0;
}
#endif
void bsp_pmu_init(void)
{
	pmic_base_addr = PMIC_BASE_ADDR;
    printk("\npmu init\n");
    return;
}

