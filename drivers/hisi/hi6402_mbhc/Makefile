# hi6402 mbhc driver
ifeq ($(CONFIG_HI6402_MBHC_ANC),y)
EXTRA_CFLAGS += -DANC_HEADSET
EXTRA_CFLAGS += -DINVERT_HEADSET
endif

obj-$(CONFIG_HI6402_MBHC)	:= hi6402_mbhc.o
# obj-$(CONFIG_HI6402_MBHC)	+= hi6402es_mbhc.o
