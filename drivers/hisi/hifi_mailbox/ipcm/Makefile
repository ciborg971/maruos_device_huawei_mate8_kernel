EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifi_mailbox/mailbox/
ifeq ($(CONFIG_HIFI_IPC_3650),y)
EXTRA_CFLAGS += -DPLATFORM_HI365X
EXTRA_CFLAGS += -Iinclude/modem/include/config/hi365x
EXTRA_CFLAGS += -Iinclude/modem/include/drv/hi365x
endif
ifeq ($(CONFIG_HIFI_IPC_6250),y)
EXTRA_CFLAGS += -DPLATFORM_HI6250
EXTRA_CFLAGS += -Iinclude/modem/include/config/hi62x0
EXTRA_CFLAGS += -Iinclude/modem/include/drv/hi62x0
endif

obj-$(CONFIG_HIFI_IPC)					:= bsp_ipc.o


