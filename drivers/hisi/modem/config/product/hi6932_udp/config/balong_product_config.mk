 mkfilepath := $(abspath $(lastword $(MAKEFILE_LIST)))
 current_dir :=$(dir $(mkfilepath))

 include $(current_dir)/balong_product_config_legacy.mk
 include $(current_dir)/balong_product_config_drv.mk
 



