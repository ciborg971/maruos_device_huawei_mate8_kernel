# hifi dsp device driver
ifeq ($(CONFIG_HIFI_IPC_3650),y)
EXTRA_CFLAGS += -DPLATFORM_HI3XXX
EXTRA_CFLAGS += -DPLATFORM_HI365X
EXTRA_CFLAGS += -DMULTI_MIC
EXTRA_CFLAGS += -I../vendor/hisi/modem/config/product/hi3650/config
EXTRA_CFLAGS += -I../vendor/hisi/modem/include/drv/common
EXTRA_CFLAGS += -I../vendor/hisi/modem/drv/common/include/
EXTRA_CFLAGS += -I../kernel/drivers/hisi/slimbus
EXTRA_CFLAGS += -Idrivers/hisi/hifi_mailbox/mailbox
EXTRA_CFLAGS += -Idrivers/hisi/hifi_mailbox/ipcm
endif

ifeq ($(CONFIG_HIFI_IPC_6250),y)
EXTRA_CFLAGS += -DPLATFORM_HI3XXX
EXTRA_CFLAGS += -DPLATFORM_HI6250
EXTRA_CFLAGS += -I../vendor/hisi/modem/config/product/hi6250/config
EXTRA_CFLAGS += -I../vendor/hisi/modem/include/drv/common
EXTRA_CFLAGS += -I../vendor/hisi/modem/drv/common/include/
EXTRA_CFLAGS += -I../kernel/drivers/hisi/slimbus
EXTRA_CFLAGS += -Idrivers/hisi/hifi_mailbox/mailbox
EXTRA_CFLAGS += -Idrivers/hisi/hifi_mailbox/ipcm
endif


obj-$(CONFIG_HIFI_DSP_ONE_TRACK)	+= mlib_ringbuffer.o
obj-$(CONFIG_HIFI_DSP_ONE_TRACK)	+= mlib_static_ringbuffer.o
obj-$(CONFIG_HIFI_DSP_ONE_TRACK)	+= soundtrigger_dma_drv.o
