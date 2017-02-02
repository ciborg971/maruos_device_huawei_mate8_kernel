
#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES := pscomm nas encodix
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was),)
MOUDULES += gas was ttf ascomm
endif
ifeq ($(CFG_FEATURE_BASTET), FEATURE_ON)
MOUDULES += bastet
MOUDULES += bstopenssl
endif

# process
.PHONY: gups nas gas was ttf pscomm ascomm bastet bstopenssl encodix
gups: $(MOUDULES)

nas:
	$(MAKE)  -f MODEM_CORE/makefile_nas.mk INSTANCE_ID=$(INSTANCE_ID)
	$(MAKE)  -f MODEM_CORE/makefile_rabm.mk INSTANCE_ID=$(INSTANCE_ID)
gas:
	$(MAKE)  -f MODEM_CORE/makefile_gas.mk	INSTANCE_ID=$(INSTANCE_ID)
was:
	$(MAKE)  -f MODEM_CORE/makefile_was.mk	INSTANCE_ID=$(INSTANCE_ID)
ttf:
	$(MAKE)  -f MODEM_CORE/makefile_ttf.mk INSTANCE_ID=$(INSTANCE_ID)
ascomm:
	$(MAKE)  -f MODEM_CORE/makefile_ascomm.mk INSTANCE_ID=$(INSTANCE_ID)
pscomm:
	$(MAKE)  -f MODEM_CORE/makefile_pscomm.mk INSTANCE_ID=$(INSTANCE_ID)
bastet:
	$(MAKE)  -f MODEM_CORE/makefile_bastet.mk
bstopenssl:
	$(MAKE)  -f MODEM_CORE/makefile_bstopenssl.mk
encodix:
	$(MAKE)  -f MODEM_CORE/makefile_encodix.mk
	
CLEAN_MOUDULES:= clean-nas clean-pscomm clean-encodix
ifeq ($(CFG_FEATURE_BASTET), FEATURE_ON)
CLEAN_MOUDULES += clean-bastet
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was),)
CLEAN_MOUDULES += clean-gas clean-was clean-ttf clean-ascomm
CLEAN_MOUDULES += clean-bstopenssl
endif

.PHONY: clean-gups clean-nas clean-gas clean-was clean-ttf clean-pscomm clean-ascomm clean-bastet clean-bstopenssl clean-encodix

clean-nas:
	$(MAKE)  -f MODEM_CORE/makefile_nas.mk clean INSTANCE_ID=$(INSTANCE_ID)
	$(MAKE)  -f MODEM_CORE/makefile_rabm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-gas:
	$(MAKE)  -f MODEM_CORE/makefile_gas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-was:
	$(MAKE)  -f MODEM_CORE/makefile_was.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-ttf:
	$(MAKE)  -f MODEM_CORE/makefile_ttf.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-ascomm:
	$(MAKE)  -f MODEM_CORE/makefile_ascomm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-pscomm:
	$(MAKE)  -f MODEM_CORE/makefile_pscomm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-bastet:
	$(MAKE)  -f MODEM_CORE/makefile_bastet.mk clean
clean-bstopenssl:
	$(MAKE)  -f MODEM_CORE/makefile_bstopenssl.mk clean

clean-encodix:
	$(MAKE)  -f MODEM_CORE/makefile_encodix.mk clean
clean-gups: $(CLEAN_MOUDULES)
