#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore

ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_MOUDLE_NAME	?=encodix_ccore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_1)
OBC_LOCAL_MOUDLE_NAME	?=encodix1_ccore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_2)
OBC_LOCAL_MOUDLE_NAME	?=encodix2_ccore
endif

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_flags.mk

#USER FLAGS
CC_USER_FLAGS   ?=
AS_USER_FLAGS   ?=



ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls
endif

CC_USER_FLAGS += -march=armv6

#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=

ifneq ($(INSTANCE_ID) ,)
CC_USER_DEFINES	+=-D$(strip $(INSTANCE_ID) )
endif
				
#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm.inc

#ps common include directories
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004a \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \

ifeq ($(CFG_RAT_MODE),RAT_GU)
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Inc 
endif

ifeq ($(CFG_RAT_MODE),RAT_GUL)
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Inc
endif

#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/ed_lib.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/csn1lib.c \

ifeq ($(CFG_RAT_MODE),RAT_GU)
OBC_LOCAL_SRC_FILE += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/CSN1DataTypes.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/Downlink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/ed_c.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/ed_c_known_ie.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/ed_c_recog.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/L3Downlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/L3Uplink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/PLENDownlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/ts04.18_support.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/Uplink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Src/UserDefinedDataTypes.c
endif	

ifeq ($(CFG_RAT_MODE),RAT_GUL)	
OBC_LOCAL_SRC_FILE += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/CSN1DataTypes.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/Downlink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c_known_ie.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c_recog.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/L3Downlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/L3Uplink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/PLENDownlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ts04.18_support.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/Uplink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/UserDefinedDataTypes.c
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
ifeq ($(OBB_MODEM_OS_TYPE), VXWORKS)
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_vxworks6.8_rules.mk
else
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
endif