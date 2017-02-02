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

#include "hisi_fb.h"
#include "hisi_overlay_utils.h"


/*******************************************************************************
** handle isr
*/
#if defined (CONFIG_HUAWEI_DSM)
void dss_underflow_debug_func(struct work_struct *work)
{
	struct clk *ddr_clk = NULL;
	unsigned long curr_ddr = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	static u32 underflow_index = 0;
	static ktime_t underflow_timestamp[UNDERFLOW_EXPIRE_COUNT];
	s64 underflow_msecs = 0;
	static bool init_underflow_timestamp = false;
	int i;

	if (!init_underflow_timestamp) {
		underflow_timestamp[underflow_index] = ktime_get();
		underflow_index ++;
	}
	if (underflow_index == UNDERFLOW_EXPIRE_COUNT) {
		init_underflow_timestamp = true;
		underflow_timestamp[UNDERFLOW_EXPIRE_COUNT - 1] = ktime_get();
		underflow_msecs = ktime_to_ms(underflow_timestamp[UNDERFLOW_EXPIRE_COUNT - 1]) - ktime_to_ms(underflow_timestamp[0]);
		for(i = 0; i < UNDERFLOW_EXPIRE_COUNT - 1; i ++)
			underflow_timestamp[i] = underflow_timestamp[i+1];
	}

	if ((underflow_msecs <= UNDERFLOW_INTERVAL) && (underflow_msecs > 0))
		HISI_FB_INFO("abnormal, underflow times:%d, interval:%llu, expire interval:%d\n", UNDERFLOW_EXPIRE_COUNT, underflow_msecs, UNDERFLOW_INTERVAL);
	else {
		HISI_FB_INFO("normal, underflow times:%d, interval:%llu, expire interval:%d\n", UNDERFLOW_EXPIRE_COUNT, underflow_msecs, UNDERFLOW_INTERVAL);
		return;
	}

	ddr_clk = clk_get(NULL, "clk_ddrc_freq");
	if (ddr_clk) {
		curr_ddr = clk_get_rate(ddr_clk);
		clk_put(ddr_clk);
	} else
		HISI_FB_ERR("Get ddr clk failed");

	if (work) {
		hisifd = container_of(work, struct hisi_fb_data_type, dss_underflow_debug_work);
		dumpDssOverlay(hisifd, &hisifd->ov_req, true);
	} else {
		HISI_FB_ERR("Get hisifd failed");
	}

	HISI_FB_INFO("Current ddr is %lu\n", curr_ddr);
	if (!dsm_client_ocuppy(lcd_dclient)) {
		dsm_client_record(lcd_dclient, "ldi underflow!\n");
		dsm_client_notify(lcd_dclient, DSM_LCD_LDI_UNDERFLOW_NO);
	}

}
#endif
irqreturn_t dss_pdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	//uint32_t isr_s2_glb = 0;
	uint32_t isr_s2_dpp = 0;
	uint32_t isr_s2_rch = 0;
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;
	uint32_t isr_te_vsync = 0;
	struct hisifb_secure *secure_ctrl = NULL;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);

	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_PDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS);
	//isr_s2_glb = inp32(hisifd->dss_base + GLB_INTS);
	isr_s2_dpp = inp32(hisifd->dss_base + GLB_GLB_DPP_INTS);
	isr_s2_rch = inp32(hisifd->dss_base + GLB_RCH_CE_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_RCH_CE_INTS, isr_s2_rch);
	outp32(hisifd->dss_base + GLB_GLB_DPP_INTS, isr_s2_dpp);
	//outp32(hisifd->dss_base + GLB_INTS, isr_s2_glb);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_PDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_PDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK));
	//isr_s2_glb &= ~(inp32(hisifd->dss_base + GLB_INT_MSK));
	isr_s2_dpp &= ~(inp32(hisifd->dss_base + GLB_GLB_DPP_INT_MSK));
	isr_s2_rch &= ~(inp32(hisifd->dss_base + GLB_RCH_CE_INT_MSK));

	if (is_mipi_cmd_panel(hisifd)) {
		isr_te_vsync = BIT_LCD_TE0_PIN;
	} else {
		isr_te_vsync = BIT_VSYNC;
	}

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;

		if (hisifd->color_temperature_flag > 0)
			hisifd->color_temperature_flag--;

		if (hisifd->mipi_dsi_bit_clk_upt_isr_handler &&
			hisifd->panel_info.dsi_bit_clk_upt_support &&
			!(isr_s2 & BIT_VACTIVE0_START)) {
			hisifd->mipi_dsi_bit_clk_upt_isr_handler(hisifd);
		}

		if (hisifd->panel_info.esd_enable && hisifd->esd_hrtimer_enable) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (hisifd->frame_end_wq) {
					queue_work(hisifd->frame_end_wq, &(hisifd->frame_end_work));
				}
			}
		}
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler)
			hisifd->ov_vactive0_start_isr_handler(hisifd);
	}

	if (isr_s2 & isr_te_vsync) {
		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}

		if (secure_ctrl->notify_secure_switch) {
			secure_ctrl->notify_secure_switch(hisifd);
		}
	}

#if 0
	if (isr_s2_glb & (BIT_CRC_OV0_INT | BIT_CRC_ITF0_INT | BIT_CRC_SUM_INT)) {
		if (hisifd->crc_isr_handler) {
			hisifd->crc_isr_handler(hisifd);
		}
	}
#endif

	if (isr_s2 & BIT_LDI_UNFLOW) {
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK, mask);

		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_PDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0) {
			HISI_FB_ERR("ldi underflow!\n");
			#if defined (CONFIG_HUAWEI_DSM)
			if (hisifd->dss_underflow_debug_workqueue && !g_fake_lcd_flag)
				queue_work(hisifd->dss_underflow_debug_workqueue, &hisifd->dss_underflow_debug_work);
			#endif
		}
	}

	if (isr_s2_rch & BIT_CE_END_RCH4_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch4_ce_end_wq) {
			queue_work(hisifd->rch4_ce_end_wq, &hisifd->rch4_ce_end_work);
		}
	}

	if (isr_s2_rch & BIT_CE_END_RCH2_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch2_ce_end_wq) {
			queue_work(hisifd->rch2_ce_end_wq, &hisifd->rch2_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_CE_END_IND) {
		if (hisifd->panel_info.acm_ce_support
		 && g_dss_effect_acm_ce_en == 1
		 && hisifd->dpp_ce_end_wq
		 && HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACM_CE)) {
			queue_work(hisifd->dpp_ce_end_wq, &hisifd->dpp_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_BACKLIGHT_INTP) {
		hisifb_sbl_isr_handler(hisifd);
	}

	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			HISI_FB_ERR("fb%d, SMMU_INTSTAT_NS=0x%x, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x,"
				"SMMU_FAULT_INFO=0x%x!\n", hisifd->index, isr_s2_smmu,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	}

	return IRQ_HANDLED;
}

irqreturn_t dss_sdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	//uint32_t isr_s2_glb = 0;
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_SDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS);
	//isr_s2_glb = inp32(hisifd->dss_base + GLB_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	//outp32(hisifd->dss_base + GLB_INTS, isr_s2_glb);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_SDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_SDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK));
	//isr_s2_glb &= ~(inp32(hisifd->dss_base + GLB_INT_MSK));

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler)
			hisifd->ov_vactive0_start_isr_handler(hisifd);
	}

	if (isr_s2 & BIT_VSYNC) {
		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}
	}

	if (isr_s2 & BIT_LDI_UNFLOW) {
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK, mask);

		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_SDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0)
			HISI_FB_ERR("ldi underflow!\n");
	}

	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	}

	return IRQ_HANDLED;
}

irqreturn_t dss_adp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2_smmu = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_OFF_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_CPU_OFF_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_OFF_INT_MSK));

#ifdef CONFIG_FIX_DSS_WCH_ISR_BUG
	if (isr_s1 & BIT_OFF_CMDLIST8) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W0 *0x40, 0xFF);
	}

	if (isr_s1 & BIT_OFF_CMDLIST9) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W1 *0x40, 0xFF);
	}
#else
	if (isr_s1 & BIT_OFF_WCH0_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH1_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH0_WCH1_FRM_END_INT) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0_WCH1]));
		}
	}
#endif

	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	}

	return IRQ_HANDLED;
}
