
#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MODULES_DIR := $(filter-out build comm inc,$(shell ls $(BALONG_TOPDIR)/modem/ps/as/cdma))

MODULES_DIR_NAS := $(filter-out build comm inc,$(shell ls $(BALONG_TOPDIR)/modem/ps/nas))

MOUDULES := $(if $(findstring cdma,$(MODULES_DIR_NAS)),cnas, )
MOUDULES += $(if $(findstring cas,$(MODULES_DIR)),cas, )
MOUDULES += $(if $(findstring cttf,$(MODULES_DIR)),cttf, )
MOUDULES += cpscomm cencodix
	
# process
.PHONY: cnas cas cttf cpscomm cencodix 
cps: $(MOUDULES)
cnas:
	$(MAKE)  -f modem/makefile_cnas.mk INSTANCE_ID=$(INSTANCE_ID)
cttf:
	$(MAKE)  -f modem/makefile_cttf.mk INSTANCE_ID=$(INSTANCE_ID)
cas:
	$(MAKE)  -f modem/makefile_cas.mk	INSTANCE_ID=$(INSTANCE_ID)
cpscomm:
	$(MAKE)  -f modem/makefile_cpscomm.mk	INSTANCE_ID=$(INSTANCE_ID)
cencodix:
	$(MAKE)  -f modem/makefile_cencodix.mk	INSTANCE_ID=$(INSTANCE_ID)

CLEAN_MOUDULES := $(if $(findstring cdma,$(MODULES_DIR_NAS)),clean-cnas, )
CLEAN_MOUDULES += $(if $(findstring cas,$(MODULES_DIR)),clean-cas , )
CLEAN_MOUDULES += $(if $(findstring cttf,$(MODULES_DIR)),clean-cttf , )
CLEAN_MOUDULES += clean-cpscomm clean-cencodix

.PHONY: clean-cps clean-cnas clean-cas clean-cttf clean-cpscomm clean-cencodix

clean-cnas:
	$(MAKE)  -f modem/makefile_cnas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-cas:
	$(MAKE)  -f modem/makefile_cas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-cttf:
	$(MAKE)  -f modem/makefile_cttf.mk      clean INSTANCE_ID=$(INSTANCE_ID)
clean-cpscomm:
	$(MAKE)  -f modem/makefile_cpscomm.mk      clean INSTANCE_ID=$(INSTANCE_ID)
clean-cencodix:
	$(MAKE)  -f modem/makefile_cencodix.mk      clean INSTANCE_ID=$(INSTANCE_ID)

clean-cps: $(CLEAN_MOUDULES)
