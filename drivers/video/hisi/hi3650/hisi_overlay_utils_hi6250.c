/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_overlay_utils.h"


uint32_t g_dss_module_base[DSS_CHN_MAX][MODULE_CHN_MAX] = {
	/* D2 */
	{
	MIF_CH0_OFFSET,
	AIF0_CH0_OFFSET,
	AIF1_CH0_OFFSET,
	MCTL_CTL_MUTEX_RCH0,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD0_DBG,
	DSS_RCH_D2_DMA_OFFSET,
	DSS_RCH_D2_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D2_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* D3 */
	{
	MIF_CH1_OFFSET,
	AIF0_CH1_OFFSET,
	AIF1_CH1_OFFSET,
	MCTL_CTL_MUTEX_RCH1,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD1_DBG,
	DSS_RCH_D3_DMA_OFFSET,
	DSS_RCH_D3_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D3_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* V0 */
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	 0,	0,	0,	0,	0,	0,	0,	0,	0,
	},

	/* G0 */
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	 0,	0,	0,	0,	0,	0,	0,	0, 0,},

	/* V1 */
	{
	MIF_CH4_OFFSET,
	AIF0_CH4_OFFSET,
	AIF1_CH4_OFFSET,
	MCTL_CTL_MUTEX_RCH4,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD4_DBG,
	DSS_RCH_VG1_DMA_OFFSET,
	DSS_RCH_VG1_DFC_OFFSET,
	DSS_RCH_VG1_SCL_OFFSET,
	DSS_RCH_VG1_SCL_LUT_OFFSET,
	DSS_RCH_VG1_SHARPNESS_OFFSET,
	DSS_RCH_VG1_POST_CLIP_OFFSET,
	DSS_RCH_VG1_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0,
	},

	/* G1 */
	{
	MIF_CH5_OFFSET,
	AIF0_CH5_OFFSET,
	AIF1_CH5_OFFSET,
	MCTL_CTL_MUTEX_RCH5,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD5_DBG,
	DSS_RCH_G1_DMA_OFFSET,
	DSS_RCH_G1_DFC_OFFSET,
	DSS_RCH_G1_SCL_OFFSET,
	0,
	0,
	DSS_RCH_G1_POST_CLIP_OFFSET,
	0,
	0,
	0,
	0,
	0,
	0
	},

	/* D0 */
	{
	MIF_CH6_OFFSET,
	AIF0_CH6_OFFSET,
	AIF1_CH6_OFFSET,
	MCTL_CTL_MUTEX_RCH6,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD6_DBG,
	DSS_RCH_D0_DMA_OFFSET,
	DSS_RCH_D0_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D0_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* D1 */
	{
	MIF_CH7_OFFSET,
	AIF0_CH7_OFFSET,
	AIF1_CH7_OFFSET,
	MCTL_CTL_MUTEX_RCH7,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD7_DBG,
	DSS_RCH_D1_DMA_OFFSET,
	DSS_RCH_D1_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D1_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* W0 */
	{
	MIF_CH8_OFFSET,
	AIF0_CH8_OFFSET,
	AIF1_CH8_OFFSET,
	MCTL_CTL_MUTEX_WCH0,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_OV_IEN,
	0,
	0,
	DSS_WCH0_DMA_OFFSET,
	DSS_WCH0_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_WCH0_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* W1 */
	{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0},
};

uint32_t g_dss_module_ovl_base[DSS_OVL_IDX_MAX][MODULE_OVL_MAX] = {
	{DSS_OVL0_OFFSET,
	 DSS_MCTRL_CTL0_OFFSET},

	{0,
	 0},

	{DSS_OVL2_OFFSET,
	 DSS_MCTRL_CTL2_OFFSET},

	{0,
	 0},
};

//SCF_LUT_CHN coef_idx
int g_scf_lut_chn_coef_idx[DSS_CHN_MAX] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

uint32_t g_dss_module_cap[DSS_CHN_MAX][MODULE_CAP_MAX] = {
	/* D0 */
	{0,0,1,0,0,0,1,0,0,0,1},
	/* D1 */
	{0,0,1,0,0,0,1,0,0,0,1},
	/* V0 */
	{0,0,0,0,0,0,0,0,0,0,0},
	/* G0 */
	{0,0,0,0,0,0,0,0,0,0,0},
	/* V1 */
	{0,1,1,1,0,0,1,0,1,1,1},
	/* G1 */
	{0,1,0,0,0,0,1,0,0,0,0},
	/* D2 */
	{0,0,1,0,0,0,0,0,0,0,1},
	/* D3 */
	{0,0,1,0,0,0,0,0,0,0,1},

	/* W0 */
	{1,0,1,0,0,0,0,1,0,1,1},
	/* W1 */
	{0,0,0,0,0,0,0,0,0,0,0},
};


uint32_t g_dss_mif_sid_map[DSS_CHN_MAX] = {
	1, 2, 0, 0, 3, 4, 5, 6, 7, 0
};

uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX] = {
	4, 8, 0, 0, 12, 16, 20, 24, 28, 0
};

/*
uint32_t g_dss_mif_sid_map[DSS_CHN_MAX] = {
	0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX] = {
	0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};
*/

uint32_t g_fpga_flag = 1;

int hisi_dss_aif_handler(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block)
{
	int i = 0;
	int k = 0;
	dss_layer_t *layer = NULL;
	dss_wb_layer_t *wb_layer = NULL;
	int chn_idx = 0;
	dss_aif_bw_t *aif_bw = NULL;
	dss_aif_bw_t *aif1_bw = NULL;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block== NULL);

	if (pov_req->wb_enable) {
		for (k = 0; k < pov_req->wb_layer_nums; k++) {
			wb_layer = &(pov_req->wb_layer_infos[k]);
			chn_idx = wb_layer->chn_idx;

			aif_bw = &(hisifd->dss_module.aif_bw[chn_idx]);
			aif_bw->bw = wb_layer->dst.buf_size *
				(wb_layer->src_rect.w * wb_layer->src_rect.h) / (wb_layer->dst.width * wb_layer->dst.height);
			aif_bw->chn_idx = chn_idx;
			aif_bw->axi_sel = AXI_CHN1;
			aif_bw->is_used = 1;
		}
	}

	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &pov_h_block->layer_infos[i];
		chn_idx = layer->chn_idx;

		if (layer->need_cap & (CAP_BASE | CAP_DIM | CAP_PURE_COLOR))
			continue;

		aif_bw = &(hisifd->dss_module.aif_bw[chn_idx]);
		aif_bw->is_used = 1;
		aif_bw->chn_idx = chn_idx;
		if (pov_req->ovl_idx == DSS_OVL0) {
			aif_bw->axi_sel = AXI_CHN0;
		} else {
			aif_bw->axi_sel = AXI_CHN1;
		}

		aif1_bw = &(hisifd->dss_module.aif1_bw[chn_idx]);
		aif1_bw->is_used = 1;
		aif1_bw->chn_idx = chn_idx;
		aif1_bw->axi_sel = AXI_CHN0;
	}

	return 0;
}

void hisi_dss_qos_on(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	outp32(hisifd->noc_dss_base + 0xc, 0x2);
	outp32(hisifd->noc_dss_base + 0x10c, 0x2);
	outp32(hisifd->noc_dss_base + 0x18c, 0x2);
}


//debug
void hisifb_disreset_dss(struct hisi_fb_data_type *hisifd)
{
	char __iomem *peri_crg_base = hisifd->peri_crg_base;

	////////////////////////////////////////////////////////////////////////////
	//
	// VIVO BUS POWERUP
	//
	//1:module clk enable
	//PLL2 16div
	outp32(peri_crg_base + CLKDIV10, 0x0f800780);
	//PLL3 16div 100M
	outp32(peri_crg_base + CLKDIV10, 0x30003000);
	//gt_clk_vivobus
	outp32(peri_crg_base + CLKDIV20, 0x00020002);
	//gt_clk_vivobus2ddrc
	outp32(peri_crg_base + PEREN0, 0x00001000);
	//2:module unrst: ip_rst_vivobus
	outp32(peri_crg_base + PERRSTDIS0, 0x00000040);

	////////////////////////////////////////////////////////////////////////////
	//
	// DSS POWERUP
	//
	//1:module mtcmos on, dsssubsyspwren
	outp32(peri_crg_base + PERPWREN, 0x00000020);
	//udelay(100);
	mdelay(1);

	//Fix bug
	//2:vivo bus module clk enable, //PLL3 16div
	outp32(peri_crg_base + CLKDIV10, 0x0F800780);
	//before div: gt_clk_edc0 gt_clk_ldi1 gt_clk_ldi0
	outp32(peri_crg_base + CLKDIV18, 0x01C001C0);
	//after div: gt_clk_edc0, gt_clk_ldi0, gt_clk_ldi1
	//gt_aclk_dss, gt_pclk_dss
	outp32(peri_crg_base + PEREN3, 0x0002F000);
	//udelay(1);
	mdelay(1);

	//3:module clk disable
	outp32(peri_crg_base + PERDIS3, 0x0002F000);
	outp32(peri_crg_base + CLKDIV18, 0x01C00000);
	//udelay(1);
	mdelay(1);

	//4:module iso disable, dsssubsysisoen
	outp32(peri_crg_base + ISODIS, 0x00000040);

	//5:memory rempair

	//6:module unrst, ip_prst_dss ip_rst_dss
	outp32(peri_crg_base + PERRSTDIS3, 0x00000C00);
	outp32(peri_crg_base + PERRSTDIS2, 0x00000001);

	//7:module clk enable, sc_div_vivobus, 3 div, PLL3 ????
	outp32(peri_crg_base + CLKDIV10, 0x0f800100); //533M
	//outp32(peri_crg_base + CLKDIV10, 0x3f800100); //480M
	//gt_clk_edc0, gt_clk_ldi1, gt_clk_ldi0
	outp32(peri_crg_base + CLKDIV18, 0x01C001C0);
	//after div: gt_clk_edc0, gt_clk_ldi0, gt_clk_ldi1
	//gt_aclk_dss, gt_pclk_dss
	outp32(peri_crg_base + PEREN3, 0x0002F000);
}

void hisifb_sctrl_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{
	char __iomem *sctrl_base = hisifd->sctrl_base;

	//SCTRL open all clk
	//SCTRL_CLKDIV2
	writel(0x00FF00FF, sctrl_base + 0x108); //'SCCLKDIV2
	//SCTRL_PEREN0
	writel(0xFFFFFFFF, sctrl_base + 0x030); //'SCPEREN0
	//SCTRL_PEREN1
	writel(0xFFFFFFFF, sctrl_base + 0x040); //'SCPEREN1
	//SCPERRSTDIS0
	writel(0xFFFFFFFF, sctrl_base + 0x204); //'SCPERRSTDIS0
	//SCPERRSTDIS1
	writel(0xFFFFFFFF, sctrl_base + 0x210); //'SCPERRSTDIS1
	//SCPERRSTDIS2
	writel(0xFFFFFFFF, sctrl_base + 0x21c); //'SCPERRSTDIS2
	//writel(0xFFFFFFFF, 0x4020A840); //SCEFUSESEL
}

void hisifb_crgperi_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{
	char __iomem *peri_crg_base = hisifd->peri_crg_base;

	// open all div_andgate
	//CRGPERI_CLKDIV18
	writel(0xFFFFFFFF, peri_crg_base + 0x0F0);
	//CRGPERI_CLKDIV19
	writel(0xFFFFFFFF, peri_crg_base + 0x0F4);
	//CRGPERI_CLKDIV20
	writel(0xFFFFFFFF, peri_crg_base + 0x0F8);

	//crgperi open all clk
	//writel(0xFFFFFFFF, CRGPERI_PEREN(0));
	//writel(0xFFFFFFFF, CRGPERI_PEREN(1));
	//writel(0xFFFFFFFF, CRGPERI_PEREN(2));
	//writel(0xFFFFFFFF, CRGPERI_PEREN(3));
	//writel(0xFFFFFFFF, CRGPERI_PEREN(4));
	//writel(0xFFFFFFFF, CRGPERI_PEREN(5));

	//crgperi disable all rst
	//CRGPERI_RST_DIS0
	writel(0xFFFFFFFF, peri_crg_base + 0x064);
	//CRGPERI_RST_DIS1
	writel(0xFFFFFFFF, peri_crg_base + 0x070);
	//CRGPERI_RST_DIS2
	writel(0xFFFFFFFF, peri_crg_base + 0x07C);
	//CRGPERI_RST_DIS3
	writel(0xFFFFFFFF, peri_crg_base + 0x088);
	//CRGPERI_RST_DIS4
	writel(0xFFFFFFFF, peri_crg_base + 0x094);
	//CRGPERI_RST_DIS5
	writel(0xFFFFFFFF, peri_crg_base + 0x0A0);
}


void hisifb_adjust_block_rect(int block_num, dss_rect_t *ov_block_rects[], dss_wb_layer_t *wb_layer)
{
	int i = 0;
	dss_rect_t block_rect;
	bool need_adjust_block = false;

	BUG_ON(ov_block_rects == NULL);
	BUG_ON(wb_layer == NULL);

	if ((block_num > 1) && (ov_block_rects[block_num - 1]->w < HISI_DSS_MIN_ROT_AFBCE_BLOCK_SIZE)) {
		if ((wb_layer->transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_V))
			&& (wb_layer->need_cap == CAP_AFBCE)) {
			if (g_debug_ovl_block_composer) {
				HISI_FB_INFO("before_adjust:ov_block_rects[%d]:[%d:%d:%d:%d]\n",
					block_num - 1, ov_block_rects[block_num-1]->x, ov_block_rects[block_num-1]->y, ov_block_rects[block_num-1]->w,
					ov_block_rects[block_num-1]->h);
			}

			block_rect = *ov_block_rects[block_num - 1];
			ov_block_rects[block_num - 1]->w += HISI_DSS_MIN_ROT_AFBCE_BLOCK_SIZE;
			if (ov_block_rects[block_num - 1]->w > HISI_DSS_MAX_ROT_AFBCE_BLOCK_SIZE) {
				ov_block_rects[block_num - 1]->w = HISI_DSS_MAX_ROT_AFBCE_BLOCK_SIZE;
			}

			block_rect.x -= ov_block_rects[block_num - 1]->w - block_rect.w;
			ov_block_rects[block_num - 1]->x = ALIGN_UP(block_rect.x, AFBC_BLOCK_ALIGN);
			ov_block_rects[block_num - 1]->w -= ov_block_rects[block_num - 1]->x - block_rect.x;

			need_adjust_block = true;
		}
	}

	if (need_adjust_block && g_debug_ovl_block_composer) {
		for (i = 0; i < block_num; i++) {
			HISI_FB_INFO("after_adjust:ov_block_rects[%d]:[%d:%d:%d:%d]\n",
				i, ov_block_rects[i]->x, ov_block_rects[i]->y, ov_block_rects[i]->w,
				ov_block_rects[i]->h);
		}
	}
}



