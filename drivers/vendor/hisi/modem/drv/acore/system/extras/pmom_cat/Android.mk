# Copyright 2010 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)

LOCAL_SHARED_LIBRARIES := libcutils libc

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= pmom_cat.c tarzip.c dpm_m3pm.c cpufreq_regulator.c ipc_clk.c wakelock_parse.c pm_parse.c bbp_pmu.c \
				icc.c nvim.c rfile.c dsp.c tcxo.c cosa.c


LOCAL_SHARED_LIBRARIES := libc libz
LOCAL_C_INCLUDES       := external/zlib
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/nv/tl/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/drv/common/include
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/include/drv/common


LOCAL_MODULE:= pmom_cat
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

