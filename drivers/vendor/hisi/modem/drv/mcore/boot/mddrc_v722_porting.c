

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)
void udelay(unsigned int us)
{
#ifndef BSP_CONFIG_EDA
    while(us--) {
		unsigned long t = (CFG_CLK_CPU_M3_BOOT/3)/1000000;
		while(t--)
			__asm__ __volatile__("nop");
	}
#endif
}


/*"当前区域的大小。
6'd15： 64KB；
6'd16：128KB；此时.bits.rgn_base_addr[   0]必须配置为零；
6'd17：256KB；此时.bits.rgn_base_addr[ 1:0]必须配置为零；
6'd18：512KB；此时.bits.rgn_base_addr[ 2:0]必须配置为零；
6'd19：  1MB；此时.bits.rgn_base_addr[ 3:0]必须配置为零；
6'd20：  2MB；此时.bits.rgn_base_addr[ 4:0]必须配置为零；
6'd21：  4MB；此时.bits.rgn_base_addr[ 5:0]必须配置为零；
6'd22：  8MB；此时.bits.rgn_base_addr[ 6:0]必须配置为零；
6'd23： 16MB；此时.bits.rgn_base_addr[ 7:0]必须配置为零；
6'd24： 32MB；此时.bits.rgn_base_addr[ 8:0]必须配置为零；
6'd25： 64MB；此时.bits.rgn_base_addr[ 9:0]必须配置为零；
6'd26：128MB；此时.bits.rgn_base_addr[10:0]必须配置为零；
6'd27：256MB；此时.bits.rgn_base_addr[11:0]必须配置为零；
6'd28：512MB；此时.bits.rgn_base_addr[12:0]必须配置为零；
6'd29：  1GB；此时.bits.rgn_base_addr[13:0]必须配置为零；
6'd30：  2GB；此时.bits.rgn_base_addr[14:0]必须配置为零；
6'd31：  4GB；此时.bits.rgn_base_addr[15:0]必须配置为零；
6'd32：  8GB；此时.bits.rgn_base_addr[16:0]必须配置为零；
6'd33： 16GB；此时.bits.rgn_base_addr[17:0]必须配置为零；
6'd34： 32GB；此时.bits.rgn_base_addr[18:0]必须配置为零；
6'd35： 64GB；此时.bits.rgn_base_addr[19:0]必须配置为零；
6'd36：128GB；此时.bits.rgn_base_addr[20:0]必须配置为零；
6'd37：256GB；此时.bits.rgn_base_addr[21:0]必须配置为零；
6'd38：512GB；此时.bits.rgn_base_addr[22:0]必须配置为零；
6'd39：1TB；  此时.bits.rgn_base_addr[23:0]必须配置为零。
注意：
1.rgn0不可配置，默认覆盖整个地址空间；
2.为每个区域配置的区域大小，
累加上其区域起始地址后，
不允许超出总的地址空间大小。" */
#define DDR_RGN_SIZE_64KB     (15)
#define DDR_RGN_SIZE_128KB    (16)
#define DDR_RGN_SIZE_256KB    (17)
#define DDR_RGN_SIZE_512KB    (18)
#define DDR_RGN_SIZE_1MB      (19)
#define DDR_RGN_SIZE_2MB      (20)
#define DDR_RGN_SIZE_4MB      (21)
#define DDR_RGN_SIZE_8MB      (22)
#define DDR_RGN_SIZE_16MB     (23)
#define DDR_RGN_SIZE_32MB     (24)
#define DDR_RGN_SIZE_64MB     (25)
#define DDR_RGN_SIZE_128MB    (26)
#define DDR_RGN_SIZE_256MB    (27)
#define DDR_RGN_SIZE_512MB    (28)
#define DDR_RGN_SIZE_1GB      (29)

/* 当前区域的安全权限属性。
sp[3]：安全读属性；
sp[2]：安全写属性；
sp[1]：非安全读属性；
sp[0]：非安全写属性；
sp[n]=0：禁止访问；
sp[n]=1：允许访问。*/ 

#define __DDR_SEC_R__    	(0x1<<3)
#define __DDR_SEC_W__    	(0x1<<2)
#define __DDR_UNSEC_R__    	(0x1<<1)
#define __DDR_UNSEC_W__    	(0x1<<0)
#define DDR_RGN_ATTR_SP_SEC		(__DDR_SEC_R__|__DDR_SEC_W__)
#define DDR_RGN_ATTR_SP_UNSEC	(__DDR_SEC_R__|__DDR_SEC_W__|__DDR_UNSEC_R__|__DDR_UNSEC_W__)


typedef union
{
	struct
	{
		u32 rgn_base_addr	: 24; 	/* 23:0 */
		u32 rgn_size		: 6;	/* 29:24 */
		u32 reserved1 		: 1;	/* 30:30 */
		u32 reg_en 			: 1;	/* 31:31 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_MAP;


typedef union
{
	struct
	{
		u32 spp				: 4;   /* 3:0 */
		u32 security_inv	: 1;   /* 4:4 */
		u32 reserved1 		: 3;   /* 7:5 */
		u32 mid_en 			: 1;   /* 8:8 */
		u32 mid_inv			: 1;   /* 9:9 */
		u32 reserved2 		: 6;   /* 15:10 */
		u32 subrgn_disable	: 16;  /* 31:16 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_ATTRIB;

#define DDR_RGN_MAP_BASE_ADDR(addr) ((addr)>>8)

#define DDR_SEC_BASE_ADDR	(0x90040000)
#define DDR_SEC_RGN_MAP_ADDR(ports, regions) 		(0x500+0x200*ports+0x10*regions)
#define DDR_SEC_RGN_ATTRIB_ADDR(ports, regions) 	(0x504+0x200*ports+0x10*regions)
#define DDR_SEC_MID_WR_ADDR(ports, regions) 		(0x508+0x200*ports+0x10*regions)
#define DDR_SEC_MID_RD_ADDR(ports, regions) 		(0x50c+0x200*ports+0x10*regions)


#define DDR_RGN_NUMBER	(16)
DDR_REG_SEC_RGN_MAP ddr_reg_sec_rgn_maps[16] = {0};
DDR_REG_SEC_RGN_ATTRIB ddr_reg_sec_rgn_attribs[16] = {0};


#define REGION_CONFIG_COMM(region,base_addr,size,ssp,sub_rgn)	\
do {	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_base_addr 	= (base_addr >> 16);	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_size 			= size;			\
	ddr_reg_sec_rgn_maps[region].bits.reg_en			= 1;			\
	ddr_reg_sec_rgn_attribs[region].bits.spp 			= ssp;			\
	ddr_reg_sec_rgn_attribs[region].bits.subrgn_disable	= sub_rgn;		\
}while (0)


void mddrc_sec_cfg(void)
{
	u32 region_start = 1;
	u32 region_end   = 12;
	
	/* region0 不可配，按目前的ddr 分配，使用11个region  配置 */
	REGION_CONFIG_COMM(1, 0xa0000000, DDR_RGN_SIZE_4MB, DDR_RGN_ATTR_SP_SEC, 0x1FFF);	
	REGION_CONFIG_COMM(2, 0xa0000000, DDR_RGN_SIZE_4MB, DDR_RGN_ATTR_SP_UNSEC, 0xE000);
	REGION_CONFIG_COMM(3, 0xa0000000, DDR_RGN_SIZE_64MB, DDR_RGN_ATTR_SP_SEC, 0x8000);	
	REGION_CONFIG_COMM(4, 0xa4000000, DDR_RGN_SIZE_64MB, DDR_RGN_ATTR_SP_SEC, 0x00FF);	
	REGION_CONFIG_COMM(5, 0xa6000000, DDR_RGN_SIZE_16MB, DDR_RGN_ATTR_SP_SEC, 0x0000);	
	REGION_CONFIG_COMM(6, 0xa7000000, DDR_RGN_SIZE_16MB, DDR_RGN_ATTR_SP_SEC, 0x01FF);	
	REGION_CONFIG_COMM(7, 0xa7000000, DDR_RGN_SIZE_16MB, DDR_RGN_ATTR_SP_UNSEC, 0xFE03);	
	REGION_CONFIG_COMM(8, 0xa7e00000, DDR_RGN_SIZE_2MB, DDR_RGN_ATTR_SP_UNSEC, 0x0000);	
	REGION_CONFIG_COMM(9, 0xa8000000, DDR_RGN_SIZE_32MB, DDR_RGN_ATTR_SP_UNSEC, 0x0000);	
	REGION_CONFIG_COMM(10, 0xaa00000, DDR_RGN_SIZE_16MB, DDR_RGN_ATTR_SP_UNSEC, 0x0007);	
	REGION_CONFIG_COMM(11, 0xaad00000, DDR_RGN_SIZE_1MB, DDR_RGN_ATTR_SP_UNSEC, 0x0000);	
	REGION_CONFIG_COMM(12, 0xaae00000, DDR_RGN_SIZE_2MB, DDR_RGN_ATTR_SP_UNSEC, 0x0000);	

	for(;region_start<=region_end;region_start++){
		writel(ddr_reg_sec_rgn_maps[region_start].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_MAP_ADDR(0,region_start));
		writel(ddr_reg_sec_rgn_maps[region_start].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_MAP_ADDR(1,region_start));
		writel(ddr_reg_sec_rgn_attribs[region_start].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_ATTRIB_ADDR(0,region_start));
		writel(ddr_reg_sec_rgn_attribs[region_start].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_ATTRIB_ADDR(1,region_start));
	}
}



void mddrc_init_emu()
{

	writel(0x7c0,			0x90000010);/*clock enable*/
	writel(0x60000,		0x90000364);/*reset de-assert*/
	writel(0x1,				0x90040404);/*mddrc_axi0 secure bypass*/
	writel(0x1,				0x90040604);/*mddrc_axi1 secure bypass*/
	writel(0x01e00211,	0x9004001c);/*1 rank; lpddr2; 32bit bl8*/
	writel(0x3f02,			0x90040024);/*cfg do lMR LPDDR2.Reset*/
	writel(0x1,				0x90040028);/*cmd_req*/
	writel(0x00630000,	0x90040014);/*LPDDR2.nWR=5;  LPDDR2.BL=8*/
	writel(0x10004,		0x90040018);/*LPDDR2.RL/WL=6/3 */
	writel(0x30105300,	0x90040020);/*sref_arefnum=3*/
	writel(0x1122,			0x9004002c);/*memmap:R-B-R-C(rank-bank-row-col);  bank:3bit;  row:13bit;  col:10bit*/
	writel(0xa0000000,	0x90040040);/*DDR_MEM BASE_ADDR*/
	writel(0x5498170e,	0x90040050);/*DDRC_TIMING1 (333Mhz)*/
	writel(0x18a7462c,	0x90040054);/*DDRC_TIMING2 (333Mhz)*/
	writel(0x0054e033,	0x9004005c);/*DDRC_TIMING4 (333Mhz)*/
	writel(0x0,				0x900400f4);/*ODT disable*/
	writel(0x0,				0x90040058);/*DDRC_TIMING3 (333Mhz)*/
	writel(0x0f000501,	0x900400ac);/*dt_byte:0xf;  rensel=0x2;  train_mode=1;  train_en=0(gate)*/
	writel(0x0,				0x90040004);/*sr_req=0*/
	while((readl(0x90040000) & 0x4))/*in_sr==0*/
	{};
	writel(0x1,				0x90040008);/*init_req=1*/
	while((readl(0x90040000) & 0x8))/*in_init==0 */
	{};

}

void v722_porting_mddrc_init(void)
{
	writel(0x7c0,      0x90000010);
	writel(0x60000,    0x90000364);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x404);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x604);
	writel(0x32308000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000101, HI_MDDRC_REGBASE_ADDR + 0xac);  
	writel(0x0,        HI_MDDRC_REGBASE_ADDR + 0x04);
	while((readl(HI_MDDRC_REGBASE_ADDR+0x00) & 0x4))
	{};

	/* 1us */
	udelay(1);

	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x3f02,     HI_MDDRC_REGBASE_ADDR + 0x24);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x28);

	/* 1us */
	udelay(1);

	writel(0x00220000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x20004,    HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x2c);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x30);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x34);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x38);
	writel(0xa0000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x32330603, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x04324607, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0x3230800c, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x00032032, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0,        HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x0f000103, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x08);
	while((readl(HI_MDDRC_REGBASE_ADDR+0x0) & 0x8))
	{};
	while((readl(HI_MDDRC_REGBASE_ADDR+0xd4) & 0xf))
	{};
	writel(0x30105700, HI_MDDRC_REGBASE_ADDR + 0x20);
}

void mddrc_init()
{

#ifdef BSP_CONFIG_EMU
    mddrc_init_emu();
#else
    v722_porting_mddrc_init();
	mddrc_sec_cfg();
#endif
}
