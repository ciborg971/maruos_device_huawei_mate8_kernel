EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifi_mailbox/ipcm

EXTRA_CFLAGS += -DBSP_CORE_APP
ifdef CONFIG_HIFI_RESET
EXTRA_CFLAGS += -D_HIFI_WD_DEBUG
endif

ifeq ($(CONFIG_HIFI_IPC_3650),y)
EXTRA_CFLAGS += -DPLATFORM_HI3XXX
EXTRA_CFLAGS += -DPLATFORM_HI365X
EXTRA_CFLAGS += -Idrivers/hisi/hifidsp
endif

ifeq ($(CONFIG_HIFI_IPC_6250),y)
EXTRA_CFLAGS += -DPLATFORM_HI3XXX
EXTRA_CFLAGS += -DPLATFORM_HI6250
EXTRA_CFLAGS += -Idrivers/hisi/hifidsp
endif

obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_table.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_gut.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_ifc.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_msg.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_debug.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_port_linux.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_ifc.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox.o
