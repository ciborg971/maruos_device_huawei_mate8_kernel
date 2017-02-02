#
# Makefile for the modem drivers.
#
-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

obj-y				+= sysctrl/
obj-y				+= s_memory/
ifeq ($(strip $(CFG_CONFIG_MODULE_TIMER)),YES)
obj-y				+= balong_timer/
endif
ifeq ($(strip $(CFG_CONFIG_MODULE_IPC)),YES)
obj-y				+= ipc/
endif
obj-y				+= icc/
obj-y				+= reset/

obj-y				+= sync/
ifeq ($(strip $(CFG_ENABLE_BUILD_SOCP)),YES)
obj-y			+= socp/
endif
obj-$(CONFIG_RFILE_SUPPORT)	+= rfile/
obj-y				+= nvim/
obj-y		+= dsp/
# make sure temperature between nvim and loadm
obj-y				+= temperature/

obj-$(CONFIG_IMAGE_LOAD) += loadm/

obj-y			+= adp/
obj-y			+= hwadp/
obj-y			+= version/

ifeq ($(strip $(CFG_CONFIG_SYSBUS)),YES)
obj-y			+= sys_bus/
endif

obj-y			+= ipf/
obj-y 			+= psam/
obj-y			+= udi/

ifeq ($(strip $(CFG_CONFIG_RFFE_ANTEN)),YES)
obj-y				+= antenna/
endif

 
obj-$(CONFIG_MEM_BALONG)	+= mem/

obj-y 	+= onoff/

ifeq ($(strip $(CFG_CONFIG_EFUSE)),YES)
obj-y 	+= efuse/
endif

ifeq ($(strip $(CFG_CONFIG_CSHELL)),YES)
obj-y               += cshell/
endif

obj-y				+= om/
ifeq ($(strip $(CFG_CONFIG_SC)),YES)
obj-y  				+= misc/
endif
obj-y			+= pm_om/
 
obj-$(CONFIG_PMIC_OCP) += ocp/

ifeq ($(LLTMDRV_HUTAF_COV),true)
obj-y			+= lltcov/
endif

ifeq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
obj-y                   += busstress/$(OBB_PRODUCT_NAME)
endif
