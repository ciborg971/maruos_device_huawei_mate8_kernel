ifeq ($(CONFIG_FB_3650),y)
obj-$(CONFIG_FB_3650) := hisifb.o
endif

ifeq ($(CONFIG_FB_6250),y)
obj-$(CONFIG_FB_6250) := hisifb.o
endif

hisifb-objs := \
	hisi_mipi_dsi_host.o \
	hisi_mipi_dsi.o \
	hisi_rgb2mipi.o \
	hisi_fb_spi.o \
	hisi_pwm.o \
	hisi_blpwm.o \
	hisi_sensorhub_blpwm.o \
	hisi_dpe.o \
	hisi_dpe_utils.o \
	hisi_fb_panel.o \
	hisi_fb_isr.o \
	hisi_fb_vsync.o \
	hisi_fb_secure.o \
	hisi_fb_buf_sync.o \
	hisi_fb_bl.o \
	hisi_fb_utils.o \
	hisi_fb.o \
	hisi_display_effect.o \
	hisi_overlay_utils.o \
	hisi_overlay_online.o \
	hisi_overlay_offline.o \
	hisi_block_algorithm.o \
	hisi_overlay_cmdlist_utils.o \
	hisi_offlinecomposer_panel.o \
	hisi_cfg_sbl.o

hisifb-objs += \
	panel/lcdc_fake_panel.o \
	panel/mipi_fake_panel.o \
	panel/hdmi_fake_panel.o \
	panel/mipi_lcd_external_panel.o \
	panel/mipi_tianma_OTM9608A.o \
	panel/mipi_jdi_OTM1902B.o \
	panel/mipi_jdi_NT35695.o \
	panel/mipi_qunchuang_ER63419.o \
	panel/mipi_auo_NT35597.o \
	panel/mipi_jdi_OTM1906A.o \
	panel/mipi_lg_eR69006A.o \
	panel/mipi_jdi_NT35695_cut2_5.o \
	panel/mipi_jdi_NT35695_cut3_1.o \
	panel/mipi_jdi_NT36850.o \
	panel/mipi_sharp_NT35597.o \
	panel/mipi_lg_R69006_5p5.o \
	panel/mipi_sharp_NT35695_5p5.o \
	panel/mipi_lg_ER69007.o \
	panel/mipi_sharp_knt_NT35597.o\
	panel/mipi_jdi_R63452_5p5.o
	
ifeq ($(CONFIG_FB_3650),y)
hisifb-objs += \
	hisi_overlay_utils_hi3650.o
endif

ifeq ($(CONFIG_FB_6250),y)
hisifb-objs += \
	hisi_overlay_utils_hi6250.o \
	panel/mipi_boe_OTM1901A.o \
	panel/mipi_tm_OTM1901A.o \
	panel/mipi_auo_OTM1901A.o \
	panel/mipi_cmi_OTM1901A.o \
	panel/mipi_boe_OTM1906C.o \
	panel/mipi_jdi_NT35695_VNS.o \
	panel/mipi_lg_eR69006A_VNS.o
endif
hisifb-objs += voltage/tps65132.o
hisifb-objs += voltage/ina231.o


EXTRA_CFLAGS += -Idrivers/video/hisi/hi3650 \
		-Idrivers/video/hisi/panel \
		-Idrivers/video/hisi \
		-Idrivers/atfdriver \
		-Idrivers/tzdriver


clean:
	rm *.o .*cmd
