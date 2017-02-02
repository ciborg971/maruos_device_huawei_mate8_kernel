

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>



void mddrc_init()
{
	unsigned reg;
	unsigned delay = 100;

	reg = readl(0x90000064);
	writel(reg | (0x1 << 17), 0x90000064);
	
	/* Base Configuration of MDDRC */
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x10);
	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x00620000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x00010004, HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20); 
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x2c);  
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x52330704, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x06a7460b, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0xffd4e033, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x32508000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000501, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x04);
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};
	
	/* Configuration of PUB for DDR PHY ready for initilization */
	writel(0x80000000, HI_MDDRC_REGBASE_ADDR + 0x804);
	while(!(readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x1))
	{};
#ifdef BSP_CONFIG_NOT_DDR_BYPASSPLL
	writel(0x001b8000, HI_MDDRC_REGBASE_ADDR + 0x820);
#else
	writel(0xe01b8000, HI_MDDRC_REGBASE_ADDR + 0x820);
#endif
	
	writel(0x408, HI_MDDRC_REGBASE_ADDR + 0x888);
	writel(0x03808580, HI_MDDRC_REGBASE_ADDR + 0x80c);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xa80);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xb00);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xb80);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xc00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xc80);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xd00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xd80);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xe00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xe80);
	
	writel(0x01001586, HI_MDDRC_REGBASE_ADDR + 0x8b0);
	writel(0x006c64fe, HI_MDDRC_REGBASE_ADDR + 0x884);

	/*PUB_DX0GTR*/
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xac8);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xb48);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xbc8);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xc48);

	/* Configuration of PUB about Timing */	
	writel(0x20010010, HI_MDDRC_REGBASE_ADDR + 0x824);
	writel(0x19000900, HI_MDDRC_REGBASE_ADDR + 0x828);
	writel(0x0321046b, HI_MDDRC_REGBASE_ADDR + 0x830);
	writel(0x05380e53, HI_MDDRC_REGBASE_ADDR + 0x834);
	writel(0x5d0e8943, HI_MDDRC_REGBASE_ADDR + 0x88c);
	writel(0x22816295, HI_MDDRC_REGBASE_ADDR + 0x890);
	writel(0x10018c32, HI_MDDRC_REGBASE_ADDR + 0x894);
	writel(0x00000021, HI_MDDRC_REGBASE_ADDR + 0x898);
	writel(0x00000062, HI_MDDRC_REGBASE_ADDR + 0x8a0);
	writel(0x00000004, HI_MDDRC_REGBASE_ADDR + 0x8a4);
	writel(0x00000001, HI_MDDRC_REGBASE_ADDR + 0x8a8);
	writel(0x00181884, HI_MDDRC_REGBASE_ADDR + 0x880);
	writel(0x0000000c, HI_MDDRC_REGBASE_ADDR + 0xa44);

	writel(0x0000000d, HI_MDDRC_REGBASE_ADDR + 0xa54);/*PUB_ZQ1PR, for DX parts*/


	writel(0x00058906, HI_MDDRC_REGBASE_ADDR + 0xa40);
	while(delay)
	{
		delay--;
	}
	writel(0x00058902, HI_MDDRC_REGBASE_ADDR + 0xa40);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xa88);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xb08);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xb88);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xc08);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xc0c);

	/* Start initilization */
#ifdef BSP_CONFIG_NOT_DDR_BYPASSPLL
	writel(0x000001f3, HI_MDDRC_REGBASE_ADDR + 0x804);
#else
	writel(0x000001e3, HI_MDDRC_REGBASE_ADDR + 0x804);
#endif
	while((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x00000001))
	{
	};
#ifdef BSP_CONFIG_NOT_DDR_BYPASSPLL
	while(!((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x80000001) == 0x80000001))
	{};
#else
	while(!((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x00000001) == 0x00000001))
	{};
#endif
	writel(0x32508014, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x30005700, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf8);

	reg = readl(HI_MDDRC_REGBASE_ADDR + 0xa48);
	reg &= ~0xFFFC000;
	reg |= 0x1<<28;
	writel(reg, HI_MDDRC_REGBASE_ADDR + 0xa48);

	reg = readl(HI_MDDRC_REGBASE_ADDR + 0xa58);
	reg &= ~0xFFFC000;
	reg |= 0x1<<28;
	writel(reg, HI_MDDRC_REGBASE_ADDR + 0xa58);

	writel(0x00058906, HI_MDDRC_REGBASE_ADDR + 0xa40);/*power down ZQ w00*/
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xc0c);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x044);
	writel(0x000008e0, HI_MDDRC_REGBASE_ADDR + 0x24);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x28);
	while(!(readl(HI_MDDRC_REGBASE_ADDR + 0x48) & 0x200))
	{};
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x044);
	writel(0x01e70210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8e4);
}

int dram_test()
{ 
	unsigned reg = 0;
	int ret = 0;
	
	reg = readl(HI_SYSCTRL_BASE_ADDR);
	reg |= 0x1000000;
	writel(reg, HI_SYSCTRL_BASE_ADDR);
	
	writel(0x2, HI_SYSCTRL_BASE_ADDR + 0x484);
	
	writel(0x40272, HI_MDDRC_REGBASE_ADDR + 0x5008);
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x502c); 
	writel(0xffffffc, HI_MDDRC_REGBASE_ADDR + 0x5030);
	//writel(0x1fc, MDDRC_REGBASE_ADR + 0x5030); //����ʹ��
	writel(0x0f0f0f0f, HI_MDDRC_REGBASE_ADDR + 0x500c);
	writel(0xe1e1e1e1, HI_MDDRC_REGBASE_ADDR + 0x5010);
	writel(0x2d2d2d2d, HI_MDDRC_REGBASE_ADDR + 0x5014);
	writel(0xc3c3c3c3, HI_MDDRC_REGBASE_ADDR + 0x5018);
	writel(0x4b4b4b4b, HI_MDDRC_REGBASE_ADDR + 0x501c);
	writel(0xa5a5a5a5, HI_MDDRC_REGBASE_ADDR + 0x5020);
	writel(0x69696969, HI_MDDRC_REGBASE_ADDR + 0x5024);
	writel(0x87878787, HI_MDDRC_REGBASE_ADDR + 0x5028);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x5004);
	
	do
	{
		reg = readl(HI_MDDRC_REGBASE_ADDR + 0x5000);
		reg &= 0x1;
	}while(reg == 0);
	
	reg = readl(HI_MDDRC_REGBASE_ADDR + 0x5000);
	reg &= 0xE;
	if(reg != 0x0)
	{
		while(1);
	}
	else
	{
		ret = 0;
	}
	writel(0x0, HI_SYSCTRL_BASE_ADDR + 0x484);
	
	return ret; 
}

