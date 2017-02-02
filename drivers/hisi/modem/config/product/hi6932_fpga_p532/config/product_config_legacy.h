/* MD5: 7b1387c9ca835dcf4f9d4bfcffff89da*/
#if !defined(__PRODUCT_CONFIG_LEGACY_H__)
#define __PRODUCT_CONFIG_LEGACY_H__

#ifndef BALONG_OBUILD_VERSION
#define BALONG_OBUILD_VERSION 10 
#endif 

#ifndef CONFIG_VERSION_STUB
#define CONFIG_VERSION_STUB 
#endif 

#ifndef HW_VERSION_STUB
#define HW_VERSION_STUB 0XFF000200 
#endif 

#ifndef PXXX_BOARD_TYPE_BBIT			
#define PXXX_BOARD_TYPE_BBIT			 
#endif 

#ifndef BBIT_VERSION                	
#define BBIT_VERSION                	 0X2 
#endif 

#ifndef FEATURE_OBJ_CMP 				
#endif 

#ifndef FEATURE_OBJ_DUMP				
#endif 

#ifndef FTP_REPLY_TIME_OUT
#define FTP_REPLY_TIME_OUT 0 
#endif 

#ifndef PRODUCT_CONTROL_VERSION
#define PRODUCT_CONTROL_VERSION "121" 
#endif 

#ifndef PRODUCT_HISILICON_VERSION
#define PRODUCT_HISILICON_VERSION hi6932 
#endif 

#ifndef PRODUCT_NV_SPLITFILE
#define PRODUCT_NV_SPLITFILE binfilesplit "0" 
#endif 

#ifndef PRODUCT_NV_FILE_MAX_SIZE
#define PRODUCT_NV_FILE_MAX_SIZE binfileLimitSize "100" 
#endif 

#ifndef PRODUCT_NV_BIN_MODEM_NUNBER
#define PRODUCT_NV_BIN_MODEM_NUNBER bin_modem_number "2" 
#endif 

#ifndef PRODUCT_NV_XNV_MODEM_NUNBER
#define PRODUCT_NV_XNV_MODEM_NUNBER xnv_modem_number "2" 
#endif 

#ifndef PRODUCT_NV_XNV_PDT_VERSION
#define PRODUCT_NV_XNV_PDT_VERSION hi6932_fpga_p532 
#endif 

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 p532_bbe16_nocache 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux/p532_bbe16_nocache/config 
#endif 

#ifndef TENSILICA_BUILDS	
#define TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux 
#endif 

#ifndef TENSILICA_TOOLS	
#define TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RE-2014.5-linux 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x49000000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x49100000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x49050000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x49158000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x50000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_TDS_DTCM_SIZE		
#define LPHY_TDS_DTCM_SIZE		 0x30000 
#endif 

#ifndef LPHY_TDS_ITCM_SIZE		
#define LPHY_TDS_ITCM_SIZE		 0x38000 
#endif 

#ifndef LPHY_TOTAL_IMG_SIZE
#define LPHY_TOTAL_IMG_SIZE ((LPHY_PUB_DTCM_SIZE)+(LPHY_PUB_ITCM_SIZE)+(LPHY_LTE_DTCM_SIZE)*2+(LPHY_LTE_ITCM_SIZE)*2+(LPHY_TDS_DTCM_SIZE)+(LPHY_TDS_DTCM_SIZE)) 
#endif 

#ifndef TL_PHY_LALG_PATH    	
#define TL_PHY_LALG_PATH    	 modem/include/phy 
#endif 

#ifndef TL_PHY_FPGA_P532    	
#define TL_PHY_FPGA_P532    	 
#endif 

#ifndef TL_PHY_BBE16_CACHE
#endif 

#ifndef TL_PHY_HI6932         	
#define TL_PHY_HI6932         	 
#endif 

#ifndef TL_PHY_FEATURE_LTE_LCS  	
#define TL_PHY_FEATURE_LTE_LCS  	 
#endif 

#ifndef TL_PHY_RTT_COMM_DEBUG
#define TL_PHY_RTT_COMM_DEBUG 
#endif 

#ifndef FEATURE_TLPHY_SINGLE_XO		
#define FEATURE_TLPHY_SINGLE_XO		 
#endif 

#ifndef GU_INC_PATH
#define GU_INC_PATH COMM_CODE_GU/Balong_GU_Inc/GUL_CS 
#endif 

#ifndef GU_PRODUCT_VERSION
#define GU_PRODUCT_VERSION VERSION_V7R1 
#endif 

#ifndef RAT_GU
#define RAT_GU 0 
#endif 

#ifndef RAT_GUL
#define RAT_GUL 1 
#endif 

#ifndef RAT_MODE
#define RAT_MODE RAT_GUL 
#endif 

#ifndef GU_RAT_MODE
#define GU_RAT_MODE RAT_GUL 
#endif 

#ifndef TTF_SKB_EXP
#endif 

#ifndef HIFI_INCLUDE
#endif 

#ifndef HIFI_LINK_DIR_NAME
#define HIFI_LINK_DIR_NAME hifi_ld_V7R2_SFT 
#endif 

#ifndef XTENSA_CORE_HIFI
#define XTENSA_CORE_HIFI v7r2_hifi 
#endif 

#ifndef PLATFORM_CHIP_TYPE
#define PLATFORM_CHIP_TYPE p532 
#endif 

#ifndef CHIP_MODEM_ARM_ARCH
#define CHIP_MODEM_ARM_ARCH CORTEX_A9 
#endif 

#ifndef CONFIG_FASTBOOT_UART_NUM
#define CONFIG_FASTBOOT_UART_NUM 1 
#endif 

#ifndef CONFIG_MODULE_VIC
#define CONFIG_MODULE_VIC 
#endif 

#ifndef CONFIG_AT_UART
#endif 

#ifndef CONFIG_CSHELL
#endif 

#ifndef CONFIG_ICC
#define CONFIG_ICC 
#endif 

#ifndef CONFIG_OF
#define CONFIG_OF 
#endif 

#ifndef CONFIG_CPUFREQ
#endif 

#ifndef CONFIG_CCORE_REGULATOR
#define CONFIG_CCORE_REGULATOR 
#endif 

#ifndef CONFIG_CCORE_WDT
#define CONFIG_CCORE_WDT 
#endif 

#ifndef CONFIG_ACORE_WDT
#define CONFIG_ACORE_WDT 
#endif 

#ifndef CONFIG_PMIC_HI6551
#define CONFIG_PMIC_HI6551 
#endif 

#ifndef CONFIG_PMIC_FPGA
#define CONFIG_PMIC_FPGA 
#endif 

#ifndef CONFIG_COUL
#endif 

#ifndef CONFIG_SPI
#endif 

#ifndef CONFIG_SFLASH
#endif 

#ifndef CONFIG_ABB
#define CONFIG_ABB 
#endif 

#ifndef CONFIG_DSP
#define CONFIG_DSP 
#endif 

#ifndef CONFIG_HIFI
#endif 

#ifndef CONFIG_HKADC
#define CONFIG_HKADC 
#endif 

#ifndef CONFIG_ONOFF
#define CONFIG_ONOFF 
#endif 

#ifndef CONFIG_BBP
#define CONFIG_BBP 
#endif 

#ifndef CONFIG_BBP_ON
#define CONFIG_BBP_ON 
#endif 

#ifndef CONFIG_PA_RF
#endif 

#ifndef CONFIG_PASTAR
#endif 

#ifndef CONFIG_MIPI
#endif 

#ifndef ENABLE_SHELL_SYM
#define ENABLE_SHELL_SYM 
#endif 

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 
#endif 

#ifndef CONFIG_BSP_TEST_CCORE
#endif 

#ifndef CONFIG_BALONG_CCLK
#endif 

#ifndef CONFIG_CCORE_PM
#endif 

#ifndef CONFIG_MODULE_IPC
#define CONFIG_MODULE_IPC 
#endif 

#ifndef CONFIG_IPCM_USE_FPGA_VIC
#define CONFIG_IPCM_USE_FPGA_VIC 
#endif 

#ifndef CONFIG_MODULE_TIMER
#define CONFIG_MODULE_TIMER 
#endif 

#ifndef CONFIG_MODULE_SYNC
#define CONFIG_MODULE_SYNC 
#endif 

#ifndef CONFIG_LEDS_CCORE
#endif 

#ifndef CONFIG_HAS_CCORE_WAKELOCK
#endif 

#ifndef CONFIG_CCORE_BALONG_PM
#endif 

#ifndef CONFIG_BALONG_EDMA
#define CONFIG_BALONG_EDMA 
#endif 

#ifndef CONFIG_BALONG_EDMA_TEST
#define CONFIG_BALONG_EDMA_TEST 
#endif 

#ifndef CONFIG_IPF_VESION
#define CONFIG_IPF_VESION 2 
#endif 

#ifndef CONFIG_IPF_ADQ_LEN
#define CONFIG_IPF_ADQ_LEN 3 
#endif 

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
#define CONFIG_IPF_BACKUP_ON_LPM3 
#endif 

#ifndef CONFIG_CCORE_I2C
#endif 

#ifndef TL_PS_MAX_TRCH_NUM_8
#define TL_PS_MAX_TRCH_NUM_8 
#endif 

#ifndef FEATURE_ON
#define FEATURE_ON 1 
#endif 

#ifndef FEATURE_OFF
#define FEATURE_OFF 0 
#endif 

#ifndef MEMORY_SIZE_32M
#define MEMORY_SIZE_32M 1 
#endif 

#ifndef MEMORY_SIZE_64M
#define MEMORY_SIZE_64M 2 
#endif 

#ifndef MEMORY_SIZE_128M
#define MEMORY_SIZE_128M 3 
#endif 

#ifndef MEMORY_SIZE_256M
#define MEMORY_SIZE_256M 4 
#endif 

#ifndef MEMORY_SIZE_512M
#define MEMORY_SIZE_512M 5 
#endif 

#ifndef PS_PTL_VER_DANAMIC
#define PS_PTL_VER_DANAMIC 20 
#endif 

#ifndef FEATURE_CS
#define FEATURE_CS FEATURE_ON 
#endif 

#ifndef FEATURE_GFAX
#define FEATURE_GFAX FEATURE_OFF 
#endif 

#ifndef FEATURE_WFAX
#define FEATURE_WFAX FEATURE_OFF 
#endif 

#ifndef BALONG_UDP_V1R1
#define BALONG_UDP_V1R1 FEATURE_OFF 
#endif 

#ifndef BALONG_UDP_V1R2
#define BALONG_UDP_V1R2 FEATURE_OFF 
#endif 

#ifndef FEATURE_PTABLE_UDP
#define FEATURE_PTABLE_UDP FEATURE_ON 
#endif 

#ifndef FEATURE_STICK								
#define FEATURE_STICK								 FEATURE_OFF 
#endif 

#ifndef FEATURE_E5
#define FEATURE_E5 FEATURE_OFF 
#endif 

#ifndef FEATURE_E5_UDP
#define FEATURE_E5_UDP FEATURE_OFF 
#endif 

#ifndef FEATURE_HILINK
#define FEATURE_HILINK FEATURE_OFF 
#endif 

#ifndef FEATURE_SEC_BOOT
#define FEATURE_SEC_BOOT FEATURE_OFF 
#endif 

#ifndef FEATURE_PPPOE
#define FEATURE_PPPOE FEATURE_OFF 
#endif 

#ifndef FEATURE_MERGE_OM_CHAN						
#define FEATURE_MERGE_OM_CHAN						 FEATURE_ON 
#endif 

#ifndef FEATURE_UPDATEONLINE
#define FEATURE_UPDATEONLINE FEATURE_OFF 
#endif 

#ifndef FEATURE_SDIO
#define FEATURE_SDIO FEATURE_OFF 
#endif 

#ifndef FEATURE_KEYBOARD
#define FEATURE_KEYBOARD FEATURE_OFF 
#endif 

#ifndef FEATURE_CHARGE
#define FEATURE_CHARGE FEATURE_OFF 
#endif 

#ifndef FEATURE_ICC_DEBUG
#define FEATURE_ICC_DEBUG FEATURE_ON 
#endif 

#ifndef FEATURE_OLED
#define FEATURE_OLED FEATURE_OFF 
#endif 

#ifndef FEATURE_TFT
#define FEATURE_TFT FEATURE_OFF 
#endif 

#ifndef FEATURE_MMI_TEST
#define FEATURE_MMI_TEST FEATURE_OFF 
#endif 

#ifndef FEATURE_INTERPEAK
#define FEATURE_INTERPEAK FEATURE_OFF 
#endif 

#ifndef FEATURE_INTERPEAK_MINI
#define FEATURE_INTERPEAK_MINI FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_E5
#define IPWEBS_FEATURE_E5 FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_WIRELESS_DONGLE
#define IPWEBS_FEATURE_WIRELESS_DONGLE FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_LIGHTNING_CARD
#define IPWEBS_FEATURE_LIGHTNING_CARD FEATURE_OFF 
#endif 

#ifndef FEATURE_WEBNAS
#define FEATURE_WEBNAS FEATURE_OFF 
#endif 

#ifndef FEATURE_WIRELESS_DONGLE
#define FEATURE_WIRELESS_DONGLE FEATURE_OFF 
#endif 

#ifndef FEATURE_PMU_PROTECT
#define FEATURE_PMU_PROTECT FEATURE_OFF 
#endif 

#ifndef FEATURE_VXWORKS_TCPIP
#define FEATURE_VXWORKS_TCPIP FEATURE_OFF 
#endif 

#ifndef FEATURE_M2
#define FEATURE_M2 FEATURE_OFF 
#endif 

#ifndef FEATURE_MEMORY_SIZE
#define FEATURE_MEMORY_SIZE MEMORY_SIZE_64M 
#endif 

#ifndef FEATURE_ECM_RNDIS
#define FEATURE_ECM_RNDIS FEATURE_OFF 
#endif 

#ifndef FEATURE_BREATH_LIGHT
#define FEATURE_BREATH_LIGHT FEATURE_OFF 
#endif 

#ifndef FEATURE_LEDSTATUS
#define FEATURE_LEDSTATUS FEATURE_OFF 
#endif 

#ifndef FEATURE_E5_LED
#define FEATURE_E5_LED FEATURE_OFF 
#endif 

#ifndef FEATURE_RTC
#define FEATURE_RTC FEATURE_OFF 
#endif 

#ifndef FEATURE_RECONFIG
#define FEATURE_RECONFIG FEATURE_ON 
#endif 

#ifndef FEATURE_HWENCRY_REWORK
#define FEATURE_HWENCRY_REWORK FEATURE_OFF 
#endif 

#ifndef FEATURE_MMU_BIG
#define FEATURE_MMU_BIG FEATURE_OFF 
#endif 

#ifndef FEATURE_TTFMEM_CACHE
#define FEATURE_TTFMEM_CACHE FEATURE_OFF 
#endif 

#ifndef FEATURE_SDUPDATE
#define FEATURE_SDUPDATE FEATURE_OFF 
#endif 

#ifndef FEATURE_EPAD
#define FEATURE_EPAD FEATURE_OFF 
#endif 

#ifndef FEATURE_HSIC_SLAVE
#define FEATURE_HSIC_SLAVE FEATURE_OFF 
#endif 

#ifndef FEATURE_MANUFACTURE_LOG
#define FEATURE_MANUFACTURE_LOG FEATURE_OFF 
#endif 

#ifndef FEATURE_MEM_MONITOR
#define FEATURE_MEM_MONITOR FEATURE_ON 
#endif 

#ifndef FEATURE_DRV_REPLAY_DUMP						
#define FEATURE_DRV_REPLAY_DUMP						 FEATURE_OFF 
#endif 

#ifndef FEATURE_SKB_EXP
#define FEATURE_SKB_EXP FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_CHANNEL_REDUCE
#define FEATURE_SOCP_CHANNEL_REDUCE FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_DECODE_INT_TIMEOUT
#define FEATURE_SOCP_DECODE_INT_TIMEOUT FEATURE_ON 
#endif 

#ifndef FEATURE_RTOSCK
#define FEATURE_RTOSCK FEATURE_ON 
#endif 

#ifndef FEATURE_PTM
#define FEATURE_PTM FEATURE_OFF 
#endif 

#ifndef CONFIG_HISI_PTM
#define CONFIG_HISI_PTM FEATURE_OFF 
#endif 

#ifndef FEATURE_COMPRESS_WRITE_LOG_FILE
#define FEATURE_COMPRESS_WRITE_LOG_FILE FEATURE_OFF 
#endif 

#ifndef FEATURE_CBT_LOG
#define FEATURE_CBT_LOG FEATURE_OFF 
#endif 

#ifndef FEATURE_IMS
#define FEATURE_IMS FEATURE_OFF 
#endif 

#ifndef FEATURE_SAMPLE_LTE_CHAN 			
#define FEATURE_SAMPLE_LTE_CHAN 			 FEATURE_OFF 
#endif 

#ifndef FEATURE_TTF_RLC_PIGGY_BACKED
#define FEATURE_TTF_RLC_PIGGY_BACKED FEATURE_OFF 
#endif 

#ifndef FEATURE_W_R99_DL_DUAL_MAILBOX
#define FEATURE_W_R99_DL_DUAL_MAILBOX FEATURE_ON 
#endif 

#ifndef FEATURE_ASSEMBLY_MEM_CPY
#define FEATURE_ASSEMBLY_MEM_CPY FEATURE_ON 
#endif 

#ifndef FEATURE_HSPA_PERF_IMP
#define FEATURE_HSPA_PERF_IMP FEATURE_ON 
#endif 

#ifndef FEATURE_RACH_NO_ACK_DEBUG
#define FEATURE_RACH_NO_ACK_DEBUG FEATURE_OFF 
#endif 

#ifndef FEATURE_RLC_REASSEMBLE
#define FEATURE_RLC_REASSEMBLE FEATURE_ON 
#endif 

#ifndef FEATURE_CIPHER_MASTER
#define FEATURE_CIPHER_MASTER FEATURE_ON 
#endif 

#ifndef FEATURE_HDLC_ENHANCE
#define FEATURE_HDLC_ENHANCE FEATURE_ON 
#endif 

#ifndef FEATURE_EDMAC
#define FEATURE_EDMAC FEATURE_OFF 
#endif 

#ifndef FEATURE_POWER_DRV
#define FEATURE_POWER_DRV FEATURE_OFF 
#endif 

#ifndef FEATURE_SIM_NOTIFY
#define FEATURE_SIM_NOTIFY FEATURE_OFF 
#endif 

#ifndef FEATURE_HW_CODEC
#define FEATURE_HW_CODEC FEATURE_OFF 
#endif 

#ifndef FEATURE_ANT_SHARE				
#define FEATURE_ANT_SHARE				 FEATURE_OFF 
#endif 

#ifndef FEATURE_BSP_LCH_OM
#define FEATURE_BSP_LCH_OM FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_CDMA						
#define FEATURE_UE_MODE_CDMA						 FEATURE_OFF 
#endif 

#ifndef FEATURE_NV_PARTRION_MULTIPLEX
#define FEATURE_NV_PARTRION_MULTIPLEX FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_R11
#define FEATURE_LTE_R11 FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_MBMS
#define FEATURE_LTE_MBMS FEATURE_OFF 
#endif 

#ifndef FEATURE_LTE_NAS_R11
#define FEATURE_LTE_NAS_R11 FEATURE_OFF 
#endif 

#ifndef FEATURE_LPP
#define FEATURE_LPP FEATURE_OFF 
#endif 

#ifndef FEATURE_LTE_CDMA_R11
#define FEATURE_LTE_CDMA_R11 FEATURE_OFF 
#endif 

#ifndef FEATURE_LPHY_RFIC_HI6362
#define FEATURE_LPHY_RFIC_HI6362 FEATURE_ON 
#endif 

#ifndef FEATURE_BALONG_CL
#define FEATURE_BALONG_CL FEATURE_UE_MODE_CDMA 
#endif 

#ifdef OBC_IMAGE_MODEM
#endif 

#ifdef OBC_IMAGE_APP
#endif 

#ifdef OBC_IMAGE_BOOTROM
#endif 

#ifdef OBC_IMAGE_BOOTLOADER
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
