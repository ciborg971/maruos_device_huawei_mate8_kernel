ifdef CONFIG_ARCH_HI3650
ccflags-y += -I../../../../vendor/hisi/ap/platform/hi3650
endif
ifdef CONFIG_ARCH_HI6250
ccflags-y += -I../../../../vendor/hisi/ap/platform/hi6250
endif


obj-$(CONFIG_HISI_DDRC_FLUX) += hisi_ddr_ddrcflux.o

obj-$(CONFIG_HISI_DDRC_SEC) += hisi_ddr_secprotect.o

subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
