


#include "product_config.h"
#include "securec.h"
#include "osl_types.h"
#include "osl_bio.h"
#include "osl_module.h"
#include "bsp_version.h"
#include "bsp_memmap.h"
#include "bsp_hardtimer.h"

void p531_fpga_test_init(void)
{
//已确认该函数没有人在用，memset和logMsg编译不过，这里注掉
#if 0
	u32 reg;
	u32 *mem = (u32 *)0x20680000;
	u32 size = 6145;
	memset_s(mem, size, 0xaa, size);
	while(size -->0)
	{
		reg = readl((unsigned)(mem++));
		if(0xaaaaaaaa != reg)
			{
				logMsg("write failed!!!\n", 0, 0, 0, 0, 0, 0);
				break;
			}
	}
	logMsg("fpgs init test successed\n", 0, 0, 0, 0, 0, 0);
#endif
}

void p531_fpga_multi_mode_init(void)
{
	/* GU模需要单独处理 */
	if(PROTOCOL_TYPE_GUL == bsp_get_board_mode_type())
	{
		#ifdef BSP_CONFIG_P531_FPGA
		/* GU 模解复位*/	
		writel(0xffffffff, 0x27050008);    
		writel(0xffffffff, 0x27050018);  
		#endif
		/* LBUS解锁 */
		writel(0x10, 0x220a2024);
	}
}

void k3v3_fpga_init(void)
{
    u8 iregVal;

	if(PROTOCOL_TYPE_GUL == bsp_get_board_mode_type())
	{
		/* LBUS解锁 */
		writel(0x10, 0xe1fa0024);

        /*hi6551配置*/
        /*配置ldo24为3v*/
        writel(0x04, (0xe1f96000+(0xb4<<2)));
        /*打开ldo24*/
        writel(0x20, (0xe1f96000+(0x36<<2)));
        /*auxdac 开关受寄存器控制*/
        iregVal = (u8)readl(0xe1f96000+(0x11c<<2));
        iregVal |=  0x01;
        writel((u32)iregVal, 0xe1f96000+(0x11c<<2));
	}
}

void k3v5_fpga_init(void)
{
	if(PROTOCOL_TYPE_GUL == bsp_get_board_mode_type())
	{
		/* LBUS解锁 */
		writel(0x110, 0xe1fa0024);
        udelay(100000);
	}
}


void board_fpga_init(void)
{
#if defined (BSP_CONFIG_P531_FPGA) || defined(BSP_CONFIG_V7R2_SFT)
    p531_fpga_multi_mode_init();
#endif

#ifdef BSP_CONFIG_K3V3_SFT
    k3v3_fpga_init();
#endif

#if defined(BSP_CONFIG_V8R5_SFT)
    k3v5_fpga_init();
#endif


    return;
}

