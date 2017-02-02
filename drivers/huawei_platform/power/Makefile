obj-$(CONFIG_HUAWEI_CHARGER)	+= charger/
obj-$(CONFIG_HISI_COULOMETER)	+= coulometer/hisi_coul/
obj-$(CONFIG_HUAWEI_BATTERY)	+= battery/
obj-$(CONFIG_HUAWEI_KSTATE)	+= hw_kstate/
obj-$(CONFIG_INPUT_HW_ATE)	+= ate/
obj-$(CONFIG_HUAWEI_BASTET)	+= bastet/
obj-$(CONFIG_HUAWEI_SMPL)	+= smpl/
obj-$(CONFIG_HUAWEI_USB_SHORT_CIRCUIT_PROTECT)	+= usb_short_circuit_protect/

ifeq ($(HLTHERM_RUNTEST),true)
CFLAGS_KERNEL += -DCONFIG_HLTHERM_RUNTEST
endif

obj-$(CONFIG_HUAWEI_MSG_POLICY) += msgnotify/
