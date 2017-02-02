EXTRA_CFLAGS 	+= -I$(BALONG_TOPDIR)/modem/include/drv/ccore
EXTRA_CFLAGS 	+= -I$(BALONG_TOPDIR)/modem/include/drv/common
EXTRA_CFLAGS 	+= -I$(BALONG_TOPDIR)/modem/drv/common/include/
EXTRA_CFLAGS 	+= -Idrivers/hisi/mntn/blackbox/platform_lpm3
EXTRA_CFLAGS 	+= -I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/
-include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
EXTRA_CFLAGS 	+= -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc/

obj-$(CONFIG_HI3XXX_IRQ_AFFINITY)			+= hi3xxx_irq_affinity.o
obj-$(CONFIG_HI3XXX_IRQ_AFFINITY_DEBUGFS)	+= irq_affinity_debugfs.o
obj-$(CONFIG_HI3XXX_POWER_OFF)				+= hi3xxx_poweroff.o
obj-$(CONFIG_HI3XXX_CMDLINE_PARSE)  += hi3xxx_cmdline_parse.o
obj-$(CONFIG_HISI_SR)    += pm.o
obj-$(CONFIG_HI3XXX_SIM_HOTPLUG)			+= hisi_sim_hotplug.o
obj-$(CONFIG_HISI_SR_DEBUG) 				+= hisi_lpregs.o
obj-$(CONFIG_HISI_LPM3_DEBUG)		+= hisi_lpm3_debug.o
obj-$(CONFIG_HI3XXX_MODEM_ETB)		+= hi3xxx_modem_etb.o
obj-$(CONFIG_HISI_BOOST5V_CONTROL)  += hisi_boost5v_control.o

subdir-ccflags-$(CONFIG_HISI_BB)		+= -Idrivers/hisi/mntn/blackbox/

