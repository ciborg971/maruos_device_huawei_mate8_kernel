# Core information

MSPDIR = ../../../../oam/comm





ifneq ($(CFG_RAT_MODE),RAT_GU)
MSP_COMM_SRC_FILES += \
	$(MSPDIR)/comm/nvim/Nvm_fw_api.c \
	$(MSPDIR)/comm/nvim/Nvm_fw_proc.c
endif
	
			
