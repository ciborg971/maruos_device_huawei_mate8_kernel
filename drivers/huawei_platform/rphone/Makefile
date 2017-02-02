ifeq ($(CONFIG_KRETPROBES), y)
KERNEL_DIR=$(PWD)
EXTRA_CFLAGS += -Ifs/
EXTRA_CFLAGS += -fno-pic

obj-m := rfile.o
rfile-objs := rfile/rasfile.o rasbase/rasbase.o rasbase/rasprobe.o rasbase/rasproc.o
obj-m += rmem.o
rmem-objs := rmem/rasmemory.o rasbase/rasbase.o  rasbase/rasproc.o

endif
