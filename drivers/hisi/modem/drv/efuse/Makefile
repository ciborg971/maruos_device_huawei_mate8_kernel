# generic efuse driver support: platform drivers, dedicated expander chips, etc

-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

ifneq ($(strip $(CFG_BSP_CONFIG_HI3650)),YES)
obj-y	   += efuse_balong.o
endif

obj-y	   += efuse_comm.o

