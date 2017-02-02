

#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_syscrg.h>
#include <soc_memmap.h>
#include <hi_uart.h>
#include <bsp_dfs_training.h>

#ifndef min
#define min(a,b)        ((a) < (b) ? (a) : (b))
#endif

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)

TCM_DFS_TRAINING *tcm_dfs = (TCM_DFS_TRAINING * )DFS_DDR_TRAINING_DATA_ADDR;

const unsigned ddr_freq_type[6] = {133, 200, 266, 333, 450, 533};
const unsigned a9pll_ctrl1[6] = {0x855555, 0x555555, 0x855555, 0x6d5555, 0xc00000, 0x855555};
const unsigned a9pll_ctrl2[6] = {0x1101037, 0x2201053, 0x1101037, 0x2101045, 0x210105d, 0x1101037};
const unsigned busdiv_crgcfg[6] = {0x40007777, 0x40001300, 0x40003311, 0x40001300, 0x40001300, 0x40001300};

#ifdef BSP_CONFIG_LPDDR2
const unsigned timing0[6]    = {0x63210B07, 0x6331500A, 0x6441D50D, 0x654A180F, 0x666AE114, 0x677B6718};
const unsigned timing1[6]    = {0x862A01D,  0xC62A02B,  0xF72A039,  0x1372A047, 0x1972A060, 0x1E82A071};
const unsigned timing2[6]    = {0x4300901F, 0x4300D02F, 0x5301103F, 0x6401504F, 0x8501C06A, 0x9502107E};
const unsigned timing3[6]    = {0xAF444035, 0xAF466035, 0xAF486035, 0xAF4A8046, 0xAF4E2057, 0xAF50C057};
const unsigned timing4[6]    = {0x600000,   0x600000,   0x600000,   0x600000,   0x600000,   0x600000};
const unsigned timing5[6]    = {0x1080708,  0x2080A08,  0x2080D08,  0x2081008,  0x3181508,  0x3181908};
const unsigned timing6[6]    = {0x44,       0x44,       0x44,       0x44,       0x44,       0x44};
const unsigned dramtimer0[6] = {0x18C72232, 0x20CA3332, 0x290D4432, 0x354F4542, 0x45946752, 0x51D87852};
const unsigned dramtimer1[6] = {0x61D1236,  0x82B1A36,  0x8392236,  0x8472A36,  0xA603836,  0xA714236};
const unsigned dramtimer2[6] = {0x20040C1F, 0x20040C2D, 0x20050C3C, 0x2006104B, 0x20081464, 0x20091477};
const unsigned dramtimer3[6] = {0x8014CC86, 0x801F44C9, 0x8029950B, 0x80340D4E, 0x804655C3, 0x80534E16};
const unsigned dramtimer4[6] = {0x0,        0x0,        0x0,        0x0,        0x0,        0x0};
const unsigned dramtimer5[6] = {0x4,        0x4,        0x4,        0x4,        0x4,        0x4};
const unsigned misc[6]       = {0x20440605, 0x20440605, 0x20440605, 0x20440605, 0x20440705, 0x20440705};
const unsigned modereg01[6]  = {0x106C3,    0x106C3,    0x106C3,    0x106C3,    0x106C3,    0x106C3};
const unsigned modereg23[6]  = {0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000};
const unsigned dmsel[6]      = {0x24504A00, 0x24504A00, 0x24504A00, 0x24504A00, 0x24704A00, 0x24704A00};
const unsigned ioctrl3[6]    = {0x800C000,  0x800C000,  0x800C000,  0x800C000,  0xC000,     0xC000};
#elif defined(BSP_CONFIG_LPDDR3)
const unsigned timing0[6]    = {0xB3210B07, 0xB331500A, 0xB441D50D, 0xB54A180F, 0xB66AE114, 0xB77B6718};
const unsigned timing1[6]    = {0x562A013,  0x762A01B,  0x972A024,  0xC72A02D,  0xF72A03C,  0x1282A047};
const unsigned timing2[6]    = {0x4500901F, 0x4500B02F, 0x5500F03F, 0x6501204F, 0x8501806A, 0x9501C07E};
const unsigned timing3[6]    = {0xAF444145, 0xAF466145, 0xAF486145, 0xAF4A8245, 0xAF4E2255, 0xAF50C255};
const unsigned timing4[6]    = {0x10B00000, 0x10B00000, 0x10B00000, 0x10B00000, 0x10B00000, 0x10B00000};
const unsigned timing5[6]    = {0x11080708, 0x12080A08, 0x12080D08, 0x12081008, 0x13181508, 0x13181908};
const unsigned timing6[6]    = {0x44,       0x44,       0x44,       0x44,       0x44,       0x44};
const unsigned timing7[6]    = {0x0,        0x0,        0x0,        0x0,        0x0,        0x0};
const unsigned dramtimer0[6] = {0x18C72252, 0x20CA3352, 0x290D4452, 0x354F4552, 0x45946752, 0x51D87852};
const unsigned dramtimer1[6] = {0x61D126B,  0x82B166B,  0x8391E6B,  0x847246B,  0xA60306B,  0xA71386B};
const unsigned dramtimer2[6] = {0x2004101F, 0x2004102D, 0x2005103C, 0x2006104B, 0x20081464, 0x20091477};
const unsigned dramtimer3[6] = {0x8014CC86, 0x801F44C9, 0x8029950B, 0x80340D4E, 0x804655C3, 0x80534E16};
const unsigned dramtimer4[6] = {0x3008407,  0x3008489,  0x300858C,  0x300860F,  0x3008713,  0x3008817};
const unsigned dramtimer5[6] = {0x4,        0x4,        0x4,        0x4,        0x4,        0x4};
const unsigned misc[6]       = {0x20440605, 0x20440605, 0x20440605, 0x20440605, 0x20440705, 0x20440705};
const unsigned modereg01[6]  = {0x11643,    0x11643,    0x11643,    0x11643,    0x11643,    0x11643};
const unsigned modereg23[6]  = {0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000, 0xFF0A0000};
const unsigned dmsel[6]      = {0x24504A00, 0x24504A00, 0x24504A00, 0x24504A00, 0x24704A00, 0x24704A00};
const unsigned ioctrl3[6]    = {0x800C000,  0x800C000,  0x800C000,  0x800C000,  0xC000,     0xC000};
#endif

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

int mddrc_freq_init(PLL_DIV_CTRL ddr_freq,unsigned int rank_sum)
{
	unsigned n, m, reg;

	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(0x90000000 + 0x454), 0, 0, 0x1);/*set ddrphy_pll bypass mode*/
	else
		osl_reg_set_bit((void *)(0x90000000 + 0x454), 0, 0, 0x0);/*set ddrphy_pll mission mode*/

	/*2���ֶ��ر�phy��ʱ���ſ�(bypass_mode��Ҫ�˲��裬mission mode����Ҫ)*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF054), 7, 7, 0x1);/*bypass ģʽ����Ҫ�ֶ���AC��ʱ���ſ�*/

		for(n = 0; n < 4; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF248 + 0x80*n), 27, 27, 0x1);/*bypass ģʽ����Ҫ�ֶ���DX��ʱ���ſ�*/
		}

		/*bypass_mode��phy pll����������mission_mode��phy pll�������Զ��ر�ʱ���ſ�*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 31, 31, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 14, 14, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 9,  12, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 8,  8, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 0,  3, 0xF);

		/*3��PHY��ʱ�Ӵ򿪺���Ҫ��PHY��ʱ���ſؽ���Ӳ�����ƣ�bypass mode��Ҫ�˲��裬mission mode����Ҫ��*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 31, 31, 0x0);/*ԭ����phyupdate�ڸ���delay_lineʱ�������ر�phy��ʱ�ӣ�������glitch,����phy�ڲ�����*/
	}

	/*phy & PHY Counter�ĸ�λ�Ѿ�����Ӳ���ɿأ���Ҫִ�������λ������ĳЩ�Ĵ���״̬δ֪*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x0);

	/*4���ر�phy pll(bypass_mode��Ҫ�˲���,mission mode����Ҫ)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE018), 0, 2, 0x7);/*�ر�phy��pll,ʡ����*/

	/*5-1��ֻ��mission mode��Ҫ��PHY PLL�������� �üĴ������ڵ���pll ��sp��it��cpi ������ֵ����ͬ��Ƶ������ֵ��ͬ��
	�ֲ�δ˵��v7r5�費��Ҫ����̨��ȷ�ϣ���Ҫ��ȷv7r5��ʲôֵ��ʵ����v7r5ֻ��һ��missionƵ�㣬
	������Ĵ��������ò���������Ƶ���̣�*/
	if(ddr_freq_type[ddr_freq] > 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 26, 27, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 23, 24, 0x2);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 20, 22, 0x4);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF010), 11, 11, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF020), 0,  5,  0x2);

		for(n = 0; n < 2; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 10, 11, 0x0);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 7,  8,  0x2);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 4,  6,  0x4);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF210 + 0x100*n), 0,  5,  0x2);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF220 + 0x100*n), 10, 10, 0x1);
		}
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE018), 0,  2,  0x0);/*missionģʽ��Ҫ�ֶ����pll����pwdn*/
	}
	/*5-2��ODT(Ĭ��ֵ�㣬��ʹ��)�����������������  �Լ�VREF*/
	for(n = 0; n < 2; n++) {
		/*0:240�� 1:120�� 2:80�� 3��60�� 4:60�� 5:48�� 6:40�� 7:34��*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF204 + 0x100*n), 14, 16, 0x7);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF204 + 0x100*n), 11, 13, 0x7);
	}
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 23, 25, 0x7);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 20, 22, 0x7);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 17, 19, 0x7);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF024), 0,  1, 0x0);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 22, 23, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 18, 19, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 12, 13, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 6,  7,  0x3);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 0,  1,  0x3);

	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF218 + 0x100*n), 0, 1, 0x0);
	}
	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 24, 25, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 18, 19, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 12, 13, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 6,  7,  0x3);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 0,  1,  0x3);
	}

	/*5-3��data_swap/rs_passthrough����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE070), 0, 31, misc[ddr_freq]);   /*MISC(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE084), 0, 31, dmsel[ddr_freq]);  /*DMSEL(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xEFF0), 0, 31, ioctrl3[ddr_freq]);/*IOCTL3(PACK)*/

	/*6������phy���ּĴ���*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE078), 2, 2, 0x1);     /*PHYCTRL0*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE01C), 16, 31, 0x1000);/*PHY_PLL������Ҫ��ʱ��(>=20us)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE01C), 0, 7, 0xA0);    /*PHY_PLL��λ��Ҫ��ʱ��(>=1us)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 0, 0, 0x0);     /*rdqscyc���127������ff corner�£�ÿ��dely_line���11ps,rdqscyc�����1.4ns���ң���˽�������Ϊ0 ��delymeas У׼T/2��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1D4), 16, 20, 0xC);   /*�趨CA��CK֮���T/4��λ��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE010), 12, 31, 0x7000);/*�൱�������ֲ�Ĳ���tINIT3(200us,lpddr2/3��ͬ)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE014), 0, 19, 0x10);   /*�൱�������ֲ�Ĳ���tINIT1(100ns��lpddr2/3��ͬ)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 0, 7, 0x0);     /*������һ���Ѿ���֤��cke��ck֮���ʱ���ϵ��pack���������������������ᵼ��cke��ck֮���ʱ���ϵΥ��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE02C), 0, 2, 0x5);     /*����DRAM���ͣ�5��lpddr2/3��*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE030), 0, 31, dramtimer0[ddr_freq]);/*DRAMTIMER0(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE034), 0, 31, dramtimer1[ddr_freq]);/*DRAMTIMER1(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE038), 0, 31, dramtimer2[ddr_freq]);/*DRAMTIMER2(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE03C), 0, 31, dramtimer3[ddr_freq]);/*DRAMTIMER3(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE040), 0, 31, dramtimer4[ddr_freq]);/*DRAMTIMER4(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0BC), 0, 31, dramtimer5[ddr_freq]);/*DRAMTIMER5(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE064), 0, 31, modereg01[ddr_freq]); /*MODEREG01(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE068), 0, 31, modereg23[ddr_freq]); /*MODEREG23(PACK)*/

	/*7������dterrstop*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 30, 30, 0x0);/*bypass mode����0��mission mode��1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 29, 29, 0x0);/*bypass mode����0��mission mode��1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 23, 23, 0x1);/*bypass mode����1��mission mode��0*/
	}
	else {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 30, 30, 0x1);/*bypass mode����0��mission mode��1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 29, 29, 0x1);/*bypass mode����0��mission mode��1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 23, 23, 0x0);/*bypass mode����1��mission mode��0*/
	}
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 24, 29, 0x30);/*�������������������(2015-05-08)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 21, 21, 0x1);/*vince�ظ���V7R5����0��1������*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 24, 31, 0x1A);/*Rule: (0x40/Cycle(ns)))��V7R5��400MHz���㣬64/2.5 Լ= 26*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 16, 19, 0xF);/*�������������������(2015-05-08)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE118), 8,  11, 0x5);/*�������������������(2015-05-08)*/

	/*8������phy��̬���٣�����dfi�ӿ�update��ֹ*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 5, 5, 0x1);/*ע�⣺Ĭ��ֵΪ1��������رգ���retrain_en�ܿ�*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 4, 4, 0x0);/*ʹ���ſش���չ��󣬾Ͳ���ʹ���ſش��ڵĶ�̬����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 6, 6, 0x1);/*������رգ���retrain_en�ܿ�*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 16, 31, 0x400);/*ע�⣺Ĭ��ֵΪ1����������Ҫ̨�и�һ���ο�ֵ��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 14, 14, 0x0);/*rdqsg��GDS retrain����һֱ����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 13, 13, 0x0);/*ע�⣺Ĭ��ֵΪ1����ʼ��ǰ���ó�0����ʼ��������Ҫ��������*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 0, 12, 0x400);/*ע�⣺�趨rspʱ���㹻��ȷ������������Ӧphyupdate������ʱ����ΪĬ��ֵ��*/

	/*9��ʹ��PHY���ſ�չ����*/
	for(n = 0; n < 4; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF238 + 0x80*n), 28, 29, 0x3);/*�ſش���չ������*/
	}

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 16, 21, 0x2);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 10, 15, 0x2);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 4,  9,  0x10);/*SDR mode:6'b01000��1/2cycle����HDR��6'b10000��1cycle��*/

	/*10������phy��ʼ��*/
	/*ֻ��delay_meas(bypass_mode��Ҫ�˲��裬mission mode����Ҫ)*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 31, 0x5);/*dlymeans_en*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};/*ȷ��delay_meas training���*/
		reg = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C), 0, 8);/*rdqsbdl*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF054), 8, 16, min(reg,255));/*rdqsbdl������255ȡ255*/
		for(n = 0; n < 4; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF250 + 0x80*n), 12, 20, min(reg,255));/*rdqsbdl������255ȡ255*/
		}
	}

#ifdef BSP_CONFIG_LPDDR2
	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1469);
	else
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x176F);
#elif defined(BSP_CONFIG_LPDDR3)
	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1469);
	else
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1FFF);
#endif

	/*11������DMC�Ĺ���ģʽ����������*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 8, 8, 1); /*1(SDR)/0(HDR)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 20, 21, rank_sum - 1); /*0��1rank  1��2rank*/
#ifdef BSP_CONFIG_LPDDR2
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 0, 3, 2); /*������������  2��LPDDR2    3��LPDDR3*/
#elif defined(BSP_CONFIG_LPDDR3)
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 0, 3, 3); /*������������  2��LPDDR2    3��LPDDR3*/
#endif
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 4, 5, 2); /*DDR����λ��Ϊ32bits*/

	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 8, 9, 1); /*������������ 0��4bank   1��8bank*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 4, 6, 3); /*��ʵ�ʶԽӵ���������*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 0, 2, 1); /*��ʵ�ʶԽӵ���������*/
	}

#ifdef BSP_CONFIG_LPDDR2
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8200), 16, 20, 0x8); /*����Ϊwl+4���ɽ���DMC�Ĺ���:LPDDR2��8��LPDDR3��A*/
#elif defined(BSP_CONFIG_LPDDR3)
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8200), 16, 20, 0xA); /*����Ϊwl+4���ɽ���DMC�Ĺ���:LPDDR2��8��LPDDR3��A*/
#endif

	/*12������DMC��ʱ�����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8100), 0, 31, timing0[ddr_freq]);/*DDRC_CFG_TIMING0*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8104), 0, 31, timing1[ddr_freq]);/*DDRC_CFG_TIMING1*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8108), 0, 31, timing2[ddr_freq]);/*DDRC_CFG_TIMING2*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x810C), 0, 31, timing3[ddr_freq]);/*DDRC_CFG_TIMING3*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8110), 0, 31, timing4[ddr_freq]);/*DDRC_CFG_TIMING4*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8114), 0, 31, timing5[ddr_freq]);/*DDRC_CFG_TIMING5*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8118), 0, 31, timing6[ddr_freq]);/*DDRC_CFG_TIMING6*/
#ifdef BSP_CONFIG_LPDDR3
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x811C), 0, 31, timing7[ddr_freq]);/*DDRC_CFG_TIMING7*/
#endif

	/*13��ȷ�ϳ�ʼ���Ѿ�����*/
	while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};

	/*14��ȷ��PHY��ʼ��������û�з�������*/
	if(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE008), 0, 31) != 0x0)
		return -1;

	if(rank_sum == 2) { /*rank��Ϊ2ʱִ���������ã�rank��Ϊ1ʱ����Ҫ����*/
		/*15���趨��ʼ�����ڵ�rank*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 0, 3, 0x1); /*ѡ��rank1*/

		/*16������rank1��gt_train*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 5, 6, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0, 0x1);

		/*17��ȷ��rank1��gt_train���*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};

		/*18��ȷ��rank1��gt_trainingû�з�������*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE008), 0, 31) != 0x0){};

		/*19���趨retrain��ʼ��rankΪrank0*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 0, 3, 0x0);/*ѡ��rank0*/
	}

	/*20�����浱ǰƵ���training�����Ĵ���*/
	if(ddr_freq_type[ddr_freq] <= 400) { /*bypass_modeƵ�㱣��*/
		tcm_dfs->TRAINING[ddr_freq].ddr_freq = ddr_freq_type[ddr_freq];
		for(n = 0; n < 4; n++) {
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNGDS[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE23C + 0x80*n), 0, 31);
		}

		for(m = 0; m < 2; m++) {
			for(n = 0; n < 4; n++) {
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSGDLY[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE240 + 0x80*n +0x400*m), 0, 31);
			}
		}
	}
	else { /*mission modeƵ�㱣��*/
		tcm_dfs->TRAINING[ddr_freq].ddr_freq = ddr_freq_type[ddr_freq];
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL0 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE140), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL1 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE144), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL2 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE148), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL3 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE14C), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL4 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE150), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ADDRPHBOUND = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1D4), 0, 31);
		for(n = 0; n < 4; n++) {
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL0[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE210 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL1[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE214 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL2[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE218 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNOEBDL[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE228 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE230 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE234 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWLSL[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE238 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNGDS[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE23C + 0x80*n), 0, 31);
		}

		for(m = 0; m < 2; m++) {
			for(n = 0; n < 4; n++) {
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQNBDL0[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE21C + 0x80*n +0x800*m), 0, 31);
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQNBDL1[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE220 + 0x80*n +0x800*m), 0, 31);
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSGDLY[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE240 + 0x80*n +0x400*m), 0, 31);
			}
		}
	}
	return 0;
}

void a9pll_div_ctrl(PLL_DIV_CTRL ddr_freq)
{
	unsigned reg;

	osl_reg_set_bit((void *)(0x90000000 + 0x30), 0, 3, 0x8); /*��PERIPLL����ο�ʱ��*/
	osl_reg_set_bit((void *)(0x90000000 + 0x144), 0, 3, 0x8); /*A9����ο�ʱ��Դѡ��PERI PLL*/
	reg = osl_reg_get_bit((void *)(0x90000000 + 0x208), 8, 8);
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 8, 8, 0x1); /*0�����߼��Զ�����ARM PLL��PD״̬��1�����������ARM PLL����״̬�����pdʹ�� */
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 0, 0, 0x1); /*����A9 PLL powdown*/
	osl_reg_set_bit((void *)(0x90000000 + 0x200), 0, 31, a9pll_ctrl1[ddr_freq]); /*����Ŀ��Ƶ��*/
	osl_reg_set_bit((void *)(0x90000000 + 0x204), 0, 31, a9pll_ctrl2[ddr_freq]); /*����Ŀ��Ƶ��*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 0, 0, 0x0); /*���A9 PLL powdown*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 3, 3, 0x1); /*4����λʱ�������ֹ*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 5, 5, 0x1); /*vco�����ֹ*/
	while(osl_reg_get_bit((void *)(0x90000000 + 0x208), 31, 31) != 0x1){}; /*�ȴ�A9 PLL lock*/
	osl_reg_set_bit((void *)(0x90000000 + 0x104), 0, 31, busdiv_crgcfg[ddr_freq]); /*����Ŀ��Ƶ��*/
	osl_reg_set_bit((void *)(0x90000000 + 0x144), 0, 3, 0x1); /*A9����ο�ʱ��Դѡ��A9 PLL*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 8, 8, reg); /*�ָ���Ƶǰ������pll_ctrlֵ*/
	osl_reg_set_bit((void *)(0x90000000 + 0x34), 0, 3, 0x8); /*�ر�PERIPLL����ο�ʱ��*/
}

void mddrc_init(void)
{
	unsigned i, ret = 0;

	/*1��MDDRC+PACK+PHY ��ϵͳ����Χ���ã�ּ��ΪDDR��ϵͳ�ṩ�ȶ��ġ���ȷ��ʱ���Լ����ʵ�ϵͳ�����źţ���bypass mode �����á���λ����*/
	osl_reg_set_bit((void *)(0x90000000 + 0x10), 0, 31, 0x7c0);  /*��mddrc/ddrphy���clk*/

	/*2-22����mddrc_freq_init����*/
#ifdef BSP_CONFIG_HIMDDRCV510_533
	a9pll_div_ctrl(DDR_FREQ_533);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*�ֶ���λmddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*�ֶ��⸴λmddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_533, 1); /*��ʼ��533M,����1��rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_333)
	a9pll_div_ctrl(DDR_FREQ_333);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*�ֶ���λmddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*�ֶ��⸴λmddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_333, 1); /*��ʼ��333M,����1��rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_133)
	a9pll_div_ctrl(DDR_FREQ_133);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*�ֶ���λmddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*�ֶ��⸴λmddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_133, 1); /*��ʼ��133M,����1��rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_ALL)
	for(i = 0; i < DDR_FREQ_MAX; i++) {
		a9pll_div_ctrl(i);
		osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*�ֶ���λmddrc/ddrphy*/
		osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*�ֶ��⸴λmddrc/ddrphy*/
		ret += mddrc_freq_init(i, 1); /*����1��rank*/
	}
#endif

	if(ret != 0)
		print_info("\nmddrc init fail\n");
	else
		print_info("\nmddrc init ok\n");

	/*23������AXI_IF�ĵ�ַӳ��ģʽ��V7R5��������������region,����ʵ�ʵĵ�ַӳ���������øüĴ�����*/
#if 0 /*exclusive/������������ʱ����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x20),  0, 1, 0x1);/*�Ƿ�Ҫʹ��exclusive���ܣ�Ĭ��ʹ�ܣ����Ƿ�Ҫ�򿪶�wrap�����֣�Ĭ�Ͻ�ֹ0��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x20),  8, 19, 0x1);/*ʹ�ܷ�����ģʽ��Ĭ�Ͻ�ֹ��*/
#endif
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x100), 0, 12, 0x1640);/*�������������ϵͳӦ�ó�������,�������ó�һ��region,1G��������Ƭ���óɣ�0x1640*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 28, 30, 0x4);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 24, 25, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 16, 18, 0x4);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 8,  15, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 0,  5, 0x4);

	/*24������AXI_IF/SEC/QOSBUF/DMC�ĸ��ֿ�ѡ���ܣ���ʱ���ԣ�����ʵ���������ã�*/

	/*25���ú궨��������������̵����ȶ����ٿ���*/
#if 0
	/*25-1��ʹ��pd,asref,lp����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 20,  31, 0x1);/*dmc��������asref_prd*1024�����ں�������ˢ��(��ҪӰ�����ܣ��ο�K3)��K3û��ʵ��������Ϊ1us��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 16,  19, 0x1);/*ddr_cke��phy�ڲ�·����ʱ���ſس�һ��cycle*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 4,  15, 0x20);/*dmc��������pd_prd�����ں����power_down״̬(�ο�V9R1����Ϊ8���Ƿ��̫Ƶ����Ӱ�����ܣ��ο�K3)��K3û��ʵ��������Ϊ23cycle��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 2,  2, 0x0);  /*����pd��ر�DDRʱ��(pd_en��lp_en�Ƿ񶼻��CKʱ���ſأ���)����ΪV9R1��bug,����V8R1��Ҳ����Ϊ0��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 0,  0, 0x1);  /*ʹ��pd����*/
	/*25-2��ʹ���Զ�ˢ���Ż�����*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x802C), 2,  2, 0x1);  /*1���Զ�ˢ���Ż�  0���Զ�ˢ�·��Ż�ģʽ*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x802C), 5,  6, 0x2);  /*�����Զ�ˢ���Ż���ˮ��Ϊ4*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 16, 31, 0x3);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 1,  1, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 0,  0, 0x1);
	/*25-3��ʹ��ZQУ׼*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 23, 23, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 22, 22, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 16, 16, 0x1);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 21, 24, 0x0);/*DDRC_CFG_LP.tlp_wakeup>=t_wakeup_thrd_lv2���ر�ʱ�Ӻ�CA*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 12, 15, 0x7);/*��Ӧʱ�䣬����С�� DDRC_CFG_LP.tlp_resp������LP�ò�����Ӧ��ֻ��DFIЭ��涨���7��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 8,  11, 0x6);/*lv3��wakeup time��Ҫ�㹻��ȷ��pll power_up ֮��������������ǰ�����²����õ�����ΪĬ��ֵ6��*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 16, 19, 0xA);/*DDRC_CFG_LP.t_wcke ��Ϊ�˱�֤PHY�ڽ���͹���֮ǰcke��͸����DRAM,�ӷ��沨��������
																   ��SDR��HDR ģʽ�£�cke��dfi�ӿڵ�DRAM�ֱ���Ҫ���ĺͰ��ģ��������A�������㹻��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 12, 15, 0xF);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 8,  11, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 0,  0,  0x1);/*��pd_en=1������ʹ��lp_en*/
	/*25-4������dfi�ӿ�updateʹ��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 13,  13,  0x1);/*ע�⣺Ĭ��ֵΪ1����ʼ��ǰ���ó�0����ʼ��������Ϊ1*/
#endif

	/*26�����ÿ����˳���ˢ��*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8000), 0,  1,  0x0);

	/*27��ȷ���Ѵ��ڷ���ˢ��̬*/
	while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8294), 0, 0) != 0x0){};

	/*28������DMC��AXI�ķ�ѹ*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8000), 1,  1,  0x1);
}

