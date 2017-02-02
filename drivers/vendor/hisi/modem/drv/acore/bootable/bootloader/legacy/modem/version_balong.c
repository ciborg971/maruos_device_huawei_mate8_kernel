#include <boot.h>
#include <debug.h>
#include <platform.h>
#include <bsp_memmap.h>
#include <fdt_ops.h>
#include <partition_ops.h>
#include <hi_modem.h>
#include <module.h>
#include <system.h>
#include <boardid.h>
#include <emmc_ops.h>
#include <hkadc.h>
#include <hisi_secureboot.h>
#include <modemid.h>
#include <module_level.h>
#include <modem.h>
#include <version_balong.h>
#include <sys.h>
#include <hi_version.h>
#include <boardid.h>
#include <modemid.h>
static u32 g_is_verison_ddr_init = 0;
/*lint -save -e838 -e835 -e716 -e717 -e774*/
/*****************************************************************************
* �� �� ��  	: balong_version_get_hw_version
*
* ��������  : ���Ӳ���汾������
*
* �������  : ��
* �������  :
*
* �� �� ֵ  	: Ӳ���汾������
* �޸ļ�¼  :
*
*****************************************************************************/
u32 balong_version_get_hw_version(u8* is_udp)
{
/*stub,������product_config.define��*/
#ifdef CONFIG_VERSION_STUB
	*is_udp = 1;
	return HW_VERSION_STUB;/*ʹ��product_config.define�ж����ID*/
#else
    u32 productid = 0;
    struct modemid_operators *modemid_ops = get_operators(MODEMID_MODULE_NAME_STR);
	if(!modemid_ops){
		PRINT_ERROR("can not get modemid_ops!\n");
		return 1;
	}
    
    productid = modemid_ops->get_productid();
    *is_udp = 0;
    PRINT_ERROR("get modemid_ops:0x%x!\n",productid);
    return productid;
#endif
}

/*****************************************************************************
* ����	: bsp_get_board_actual_type
* ����	: get board actual type
* ����	: void
* ���	: void
* ����	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(void)
{
	switch(bsp_get_version_info()->plat_type){
		case PLAT_ASIC:
			#ifdef PXXX_BOARD_TYPE_ONLY_SOC
				return BSP_BOARD_TYPE_SOC;
			#elif defined(PXXX_BOARD_TYPE_BBIT)
			    return BSP_BOARD_TYPE_BBIT;
			#else
				return BSP_BOARD_TYPE_ASIC;
			#endif				
		case PLAT_PORTING:
			return BSP_BOARD_TYPE_SFT;
        case PLAT_EMU:
			return BSP_BOARD_TYPE_ASIC;
		default:
			return BSP_BOARD_TYPE_MAX;
	}
}

/*****************************************************************************
* ����	: bsp_version_init
* ����	: bsp_save_chip_version ;  bsp_save_hw_version
* ����	: void
* ���	: void
*
*****************************************************************************/
void bsp_version_init(void)
{
    u32 chip_version = 0;
    u32 hw_version = HW_VER_INVALID;
    BSP_VERSION_INFO_S *p_version_info = (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
	if(sizeof(BSP_VERSION_INFO_S) > SHM_SIZE_VERSION)
	{
		cprintf("[bsp_version_init]:sizeof(BSP_VERSION_INFO_S) > SHM_SIZE_VERSION!\n");
		return ;
	}
	memset(p_version_info, 0, sizeof(BSP_VERSION_INFO_S));

	//version ddr�ռ��ʼ����־������return֮ǰ��1��Ч
    g_is_verison_ddr_init = 1;

	//CHIP_VERSION_ADDR	
	chip_version = (u32)readl((unsigned)CHIP_VER_ADDR);
	p_version_info->chip_type= (VERSION_CHIP_TYPE_E)((chip_version & CHIP_TYPE_MASK) >> 16);
	p_version_info->plat_type= (VERSION_PLAT_TYPE_E)((chip_version & PLAT_TYPE_MASK) >> 12);
	p_version_info->eco_id = (u32)(chip_version & ECO_INFO_MASK);

       //K3 plat type definition differ from balong, delte this after chicago
       //(1) for asic, plat type == 0, do nothing
       //(2) for fpga, plat type == 1, change to  a
       //(2) for emu, plat type == 2, change to  e
       if(0x1 == p_version_info->plat_type)
            p_version_info->plat_type = 0xa;
       else if(0x2 == p_version_info->plat_type)
            p_version_info->plat_type = 0xe;


	//Ĭ��Ϊ��ģƽ̨GUTL
	p_version_info->multimode_type = PROTOCOL_TYPE_GUL;

	//board id ,HW_VERSION_ADDR	
	hw_version = balong_version_get_hw_version(&(p_version_info->is_mbb_udp));
	if(HW_VER_INVALID==hw_version)
		cprintf("[bsp_save_hw_version]:get hw version failed!\n");
	p_version_info->board_id = hw_version;

	//board id udp masked
	p_version_info->board_id_udp_masked = p_version_info->is_mbb_udp ? (hw_version & HW_VER_UDP_MASK) : hw_version;

	//board type
	p_version_info->board_type = bsp_get_board_actual_type();

	return;
}
const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
    if(!g_is_verison_ddr_init)
    {
        /* coverity[loop_bottom] */
        while(1){}//avoid accessing the ddr addr before init
    }
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}

/* bsp_set_multimode_type() ֻ��board_fpga.c ���ã�Ĭ��Ϊ��ģ*/
void bsp_set_multimode_type(int gul)
{
	BSP_VERSION_INFO_S *p_version_info = (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);

	if(!gul)
	{
		p_version_info->multimode_type = PROTOCOL_TYPE_LTE_ONLY;
	}
}

/* bsp_version_get_chip_type() ֻ�� bsp_disable_non_on_clk  ����*/
VERSION_CHIP_TYPE_E bsp_version_get_chip_type(void)
{
    u32 chip_version = (u32)readl((unsigned)CHIP_VER_ADDR);
    VERSION_CHIP_TYPE_E chip_type = (VERSION_CHIP_TYPE_E)((chip_version & CHIP_TYPE_MASK) >> 16);
    return chip_type;
}
/*lint -restore*/



