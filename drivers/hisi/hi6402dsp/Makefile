# hi6402 dsp device driver
EXTRA_CFLAGS += -Idrivers/hisi/hi6402dsp/ap/med/
EXTRA_CFLAGS += -Idrivers/hisi/slimbus/

ifneq ($(TARGET_BUILD_VARIANT),user)
	EXTRA_CFLAGS += -DENABLE_HI6402_HIFI_DEBUG
endif
obj-$(CONFIG_HI6402_HIFI_MISC) += hi6402_hifi_misc.o
obj-$(CONFIG_HI6402_HIFI_MISC) += hi6402es_hifi_misc.o
