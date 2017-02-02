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
	{
	MIF_CH2_OFFSET,
	AIF0_CH2_OFFSET,
	AIF1_CH2_OFFSET,
	MCTL_CTL_MUTEX_RCH2,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD2_DBG,
	DSS_RCH_VG0_DMA_OFFSET,
	DSS_RCH_VG0_DFC_OFFSET,
	DSS_RCH_VG0_SCL_OFFSET,
	DSS_RCH_VG0_SCL_LUT_OFFSET,
	DSS_RCH_VG0_SHARPNESS_OFFSET,
	DSS_RCH_VG0_POST_CLIP_OFFSET,
	DSS_RCH_VG0_CSC_OFFSET,
	DSS_RCH_VG0_CE_OFFSET,
	DSS_RCH_VG0_CE0_LUT_OFFSET,
	DSS_RCH_VG0_CE1_LUT_OFFSET,
	DSS_RCH_VG0_CE2_LUT_OFFSET,
	DSS_RCH_VG0_CE3_LUT_OFFSET,
	},

	/* G0 */
	{
	MIF_CH3_OFFSET,
	AIF0_CH3_OFFSET,
	AIF1_CH3_OFFSET,
	MCTL_CTL_MUTEX_RCH3,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD3_DBG,
	DSS_RCH_G0_DMA_OFFSET,
	DSS_RCH_G0_DFC_OFFSET,
	DSS_RCH_G0_SCL_OFFSET,
	0,
	0,
	DSS_RCH_G0_POST_CLIP_OFFSET,
	0,
	0,
	0,
	0,
	0,
	0
	},

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
	DSS_RCH_VG1_CE_OFFSET,
	DSS_RCH_VG1_CE0_LUT_OFFSET,
	DSS_RCH_VG1_CE1_LUT_OFFSET,
	DSS_RCH_VG1_CE2_LUT_OFFSET,
	DSS_RCH_VG1_CE3_LUT_OFFSET,
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
	MIF_CH9_OFFSET,
	AIF0_CH9_OFFSET,
	AIF1_CH9_OFFSET,
	MCTL_CTL_MUTEX_WCH1,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_OV_IEN,
	0,
	0,
	DSS_WCH1_DMA_OFFSET,
	DSS_WCH1_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_WCH1_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},
};

uint32_t g_dss_module_ovl_base[DSS_OVL_IDX_MAX][MODULE_OVL_MAX] = {
	{DSS_OVL0_OFFSET,
	DSS_MCTRL_CTL0_OFFSET},

	{DSS_OVL1_OFFSET,
	DSS_MCTRL_CTL1_OFFSET},

	{DSS_OVL2_OFFSET,
	DSS_MCTRL_CTL2_OFFSET},

	{DSS_OVL3_OFFSET,
	DSS_MCTRL_CTL3_OFFSET},
};

//SCF_LUT_CHN coef_idx
int g_scf_lut_chn_coef_idx[DSS_CHN_MAX] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


uint32_t g_dss_module_cap[DSS_CHN_MAX][MODULE_CAP_MAX] = {
	/* D2 */
	{0,0,1,0,0,0,1,0,0,0,1},
	/* D3 */
	{0,0,1,0,0,0,0,0,0,0,1},
	/* V0 */
	{0,1,1,0,1,1,1,0,0,1,1},
	/* G0 */
	{0,1,0,0,0,0,1,0,0,0,0},
	/* V1 */
	{0,1,1,1,0,1,1,0,1,1,1},
	/* G1 */
	{0,1,0,0,0,0,1,0,0,0,0},
	/* D0 */
	{0,0,1,0,0,0,0,0,0,0,1},
	/* D1 */
	{0,0,1,0,0,0,0,0,0,0,1},

	/* W0 */
	{1,0,1,0,0,0,0,1,0,1,1},
	/* W1 */
	{1,0,1,0,0,0,0,1,0,1,1},
};

uint32_t g_dss_mif_sid_map[DSS_CHN_MAX] = {
    0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX] = {
    0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

uint32_t g_fpga_flag = 0;

static void aif_bw_sort(dss_aif_bw_t a[], int n)
{
	int i = 0;
	int j = 0;
	dss_aif_bw_t tmp;

	for (; i < n; ++i) {
		for (j = i; j < n - 1; ++j) {
			if (a[j].bw > a[j+1].bw) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

int hisi_dss_aif_handler(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block)
{
	int i = 0;
	int k = 0;
	dss_layer_t *layer = NULL;
	dss_wb_layer_t *wb_layer = NULL;
	int chn_idx = 0;
	dss_aif_bw_t *aif_bw = NULL;
	uint32_t tmp = 0;
	uint32_t bw_sum = 0;

	int rch_cnt = 0;
	int axi0_cnt = 0;
	int axi1_cnt = 0;
	dss_aif_bw_t aif_bw_tmp[DSS_CHN_MAX];

	dss_aif_bw_t *aif1_bw = NULL;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block== NULL);

	memset(aif_bw_tmp, 0, sizeof(aif_bw_tmp));

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

	rch_cnt = 0;
	//i is not chn_idx, is array idx
	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &pov_h_block->layer_infos[i];
		chn_idx = layer->chn_idx;

		if (layer->need_cap & (CAP_BASE | CAP_DIM | CAP_PURE_COLOR))
			continue;

		//MMBUF
		if (layer->need_cap & CAP_AFBCD) {
			aif1_bw = &(hisifd->dss_module.aif1_bw[chn_idx]);
			aif1_bw->is_used = 1;
			aif1_bw->chn_idx = chn_idx;
			if ((pov_req->ovl_idx == DSS_OVL0) ||
				(pov_req->ovl_idx == DSS_OVL1)) {
				if ((i % 2) == 0) {
					aif1_bw->axi_sel = AXI_CHN0;
				} else {
					aif1_bw->axi_sel = AXI_CHN1;
				}
			} else {
				if ((i % 2) == 0) {
					aif1_bw->axi_sel = AXI_CHN1;
				} else {
					aif1_bw->axi_sel = AXI_CHN0;
				}
			}

			if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer) {
				HISI_FB_INFO("fb%d, aif1, chn_idx=%d, axi_sel=%d.\n",
					hisifd->index, chn_idx, aif1_bw->axi_sel);
			}
		}

		aif_bw_tmp[i].bw = layer->img.buf_size *
			(layer->src_rect.w * layer->src_rect.h) / (layer->img.width * layer->img.height);
		aif_bw_tmp[i].chn_idx = chn_idx;
		aif_bw_tmp[i].axi_sel = 0;
		aif_bw_tmp[i].is_used = 1;

		bw_sum += aif_bw_tmp[i].bw;
		rch_cnt++;
	}

	//sort
	aif_bw_sort(aif_bw_tmp, rch_cnt);

	//i is not chn_idx, is array idx
	for (i = 0; i < DSS_CHN_MAX; i++) {
		if (aif_bw_tmp[i].is_used != 1)
			continue;

		tmp += aif_bw_tmp[i].bw;

		if ((pov_req->ovl_idx == DSS_OVL0) || (pov_req->ovl_idx == DSS_OVL1)) {
			if (tmp <= (bw_sum / 2)) {
				aif_bw_tmp[i].axi_sel = AXI_CHN0;
				if (axi0_cnt >= AXI0_MAX_DSS_CHN_THRESHOLD) {
					aif_bw_tmp[i - AXI0_MAX_DSS_CHN_THRESHOLD].axi_sel = AXI_CHN1;
					axi1_cnt++;
					axi0_cnt--;
				}
				axi0_cnt++;
			} else {
				aif_bw_tmp[i].axi_sel = AXI_CHN1;
				axi1_cnt++;
			}
		} else {
			if (tmp <= (bw_sum / 2)) {
				aif_bw_tmp[i].axi_sel = AXI_CHN1;
				if (axi1_cnt >= AXI1_MAX_DSS_CHN_THRESHOLD) {
					aif_bw_tmp[i - AXI1_MAX_DSS_CHN_THRESHOLD].axi_sel = AXI_CHN0;
					axi0_cnt++;
					axi1_cnt--;
				}
				axi1_cnt++;
			} else {
				aif_bw_tmp[i].axi_sel = AXI_CHN0;
				axi0_cnt++;
			}
		}

		chn_idx = aif_bw_tmp[i].chn_idx;
		hisifd->dss_module.aif_bw[chn_idx] = aif_bw_tmp[i];

		if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer) {
			HISI_FB_INFO("fb%d, aif0, chn_idx=%d, axi_sel=%d, bw=%u.\n",
				hisifd->index, chn_idx, aif_bw_tmp[i].axi_sel, aif_bw_tmp[i].bw);
		}
	}

	return 0;
}

void hisi_dss_qos_on(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	outp32(hisifd->noc_dss_base + 0xc, 0x2);
	outp32(hisifd->noc_dss_base + 0x8c, 0x2);
	outp32(hisifd->noc_dss_base + 0x10c, 0x2);
	outp32(hisifd->noc_dss_base + 0x18c, 0x2);
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


//debug
void hisifb_disreset_dss(struct hisi_fb_data_type *hisifd)
{

}

void hisifb_sctrl_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{

}

void hisifb_crgperi_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{

}




