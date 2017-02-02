/*
 * Atmel maXTouch Touchscreen driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Copyright (C) 2011-2012 Atmel Corporation
 * Copyright (C) 2012 Google, Inc.
 *
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
 #include "atomic_op.h"
 #include "plug.h"
 #include <linux/firmware.h>
 
#ifndef ATMEL_CONFIG_H
#define ATMEL_CONFIG_H
#define MAX_KEYS_SUPPORTED_IN_DRIVER 6
/* Each client has this additional data */

struct mxt_info {
	u8 family_id;
	u8 variant_id;
	u8 version;
	u8 build;
	u8 matrix_xsize;
	u8 matrix_ysize;
	u8 object_num;
};

struct mxt_object {
	u8 type;
	u16 start_address;
	u8 size_minus_one;
	u8 instances_minus_one;
	u8 num_report_ids;
} __packed;

struct mxt_config_info {
	u8 self_chgtime_max;
	u8 self_chgtime_min;
};

/* The platform data for the Atmel maXTouch touchscreen driver */
struct mxt_platform_data {
	unsigned long irqflags;
	const u8 *num_keys;  //len is NUM_KEY_TYPE
	const unsigned int (*keymap)[MAX_KEYS_SUPPORTED_IN_DRIVER];

	unsigned long gpio_reset;
	const char *cfg_name;

	const struct mxt_config_info *config_array;
};

struct mxt_refs_delta_data {
	int Average;
	int MaxNum;
	int MinNum;
	int refs_data_Average;
	int refs_data_MaxNum;
	int refs_data_MinNum;
	int deltas_data_Average;
	int deltas_data_MaxNum;
	int deltas_data_MinNum;
};

struct mxt_data {
	struct mxt_refs_delta_data refs_delta_data;
	struct ts_fingers *ts_cache;

	struct mxt_platform_data *pdata;

	struct mxt_object *object_table;
	struct mxt_info *info;
	void *raw_info_block;
	unsigned int max_x;
	unsigned int max_y;
	u8 x_size;
	u8 y_size;
	u8 x_origin;
	u8 y_origin;
	bool in_bootloader;
	u16 mem_size;

	u8 tchcfg[4];

	struct bin_attribute mem_access_attr;
	bool debug_enabled;
	bool debug_v2_enabled;
	u8 *debug_msg_data;
	u16 debug_msg_count;
	struct bin_attribute debug_msg_attr;
	struct mutex debug_msg_lock;
	u8 max_reportid;
	u32 config_crc;
	u32 info_crc;

	u16 addr;
	u16 bootloader_addr;

	struct mutex bus_access_mutex;

	struct t7_config t7_cfg;
	u8 *msg_buf;
	u8 t6_status;
	u8 last_message_count;
	u8 num_touchids;
	u8 num_stylusids;
	unsigned long t15_keystatus;
	bool use_retrigen_workaround;
	//
	struct regulator *reg_vddio;
	struct regulator *reg_avdd;
	bool use_regulator;

	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;

	char fw_name[128];
	char cfg_name[128];
#define ALT_CHIP_BIT_FW  (1<<8)
	unsigned long alt_chip;

	/* Cached parameters from object table */
	u16 T5_address;
	u8 T5_msg_size;
	u8 T6_reportid;
	u16 T6_address;
	u16 T7_address;
	u16 T8_address;
	u16 T9_address;
	u8 T9_reportid_min;
	u8 T9_reportid_max;
	u8 T15_reportid_min;
	u8 T15_reportid_max;
	u16 T15_address;
	u16 T18_address;
	u16 T19_address;
	u8 T19_reportid;
	u8  t19_msg[1];
	u16 T24_address;
	u8 T24_reportid;
	u16 T25_address;
	u8  T25_reportid;
	u8  t25_msg[6];
	u16 T37_address;
	u16 T38_address;
	u16 T40_address;
	u16 T42_address;
	u8 T42_reportid_min;
	u8 T42_reportid_max;
	u16 T44_address;
	u16 T46_address;
	u16 T47_address;
	u8 T48_reportid;
	u16 T55_address;
	u16 T56_address;
	u8 T61_reportid_min;
	u8 T61_reportid_max;
	u16 T61_address;
	u16 T61_instances;
	u8 T63_reportid_min;
	u8 T63_reportid_max;
	u16 T65_address;
	u16 T68_address;
	u8 T68_reportid_min;
	u8 T68_reportid_max;	
	u16 T71_address;
	u16 T72_address;
	u8 T72_reportid_min;
	u8 T72_reportid_max;
	u16 T78_address;
	u16 T80_address;
	u16 T81_address;
	u8 T81_reportid_min;
	u8 T81_reportid_max;
	u16 T92_address;
	u8 T92_reportid;
	u16 T93_address;
	u8 T93_reportid;
	u8 T97_reportid_min;
	u8 T97_reportid_max;
	u16 T96_address;
	u16 T97_address;
	u16 T99_address;
	u8 T99_reportid;
	u16 T100_address;
	u8 T100_reportid_min;
	u8 T100_reportid_max;
	u16 T102_address;
	u8  T102_reportid;
	u16 T104_address;
	u16 T113_address;
	u16 T115_address;
	u8 T115_reportid;
	/* Protect access to the T37 object buffer, used by debugfs */	
	struct mutex T37_buf_mutex;
	int *T37_buf;
	size_t T37_buf_size;
	/* for reset handling */
	struct completion reset_completion;

	/* Enable reporting of input events */
	bool enable_reporting;

#define MXT_WK_ENABLE 1
#define MXT_WK_DETECTED 2

	/* Indicates whether device is in suspend */
	bool suspended;
	
	struct mutex access_mutex;
	//
#if defined(CONFIG_MXT_IRQ_WORKQUEUE)
#define MXT_EVENT_IRQ 1
#define MXT_EVENT_EXTERN 2
#define MXT_EVENT_IRQ_FLAG 5
	unsigned long busy;
	wait_queue_head_t wait;
#endif

#if defined(CONFIG_MXT_PLUGIN_SUPPORT)
	struct plug_interface plug;
#endif
	//
	struct ts_device_data *chip_data;
	struct platform_device *ts_dev;
};

/* Configuration file */
#define MXT_CFG_MAGIC		"OBP_RAW V1"

/* Registers */
#define MXT_OBJECT_START	0x07
#define MXT_OBJECT_SIZE		6
#define MXT_INFO_CHECKSUM_SIZE	3
//Block size (should more than T5 size(10), less than 255)
#define MXT_MAX_BLOCK_READ	250
#define MXT_MAX_BLOCK_WRITE	128

/* Object types */

/* MXT_GEN_MESSAGE_T5 object */
#define MXT_RPTID_NOMSG		0xff

/* MXT_GEN_COMMAND_T6 field */
#define MXT_COMMAND_RESET	0
#define MXT_COMMAND_BACKUPNV	1
#define MXT_COMMAND_CALIBRATE	2
#define MXT_COMMAND_REPORTALL	3
#define MXT_COMMAND_DIAGNOSTIC	5

/* Define for T6 status byte */
#define MXT_T6_STATUS_RESET	(1 << 7)
#define MXT_T6_STATUS_OFL	(1 << 6)
#define MXT_T6_STATUS_SIGERR	(1 << 5)
//#define MXT_T6_STATUS_CAL	(1 << 4)
#define MXT_T6_STATUS_CFGERR	(1 << 3)
#define MXT_T6_STATUS_COMSERR	(1 << 2)

#define MXT_POWER_CFG_RUN		0
#define MXT_POWER_CFG_DEEPSLEEP		1

/* MXT_TOUCH_MULTI_T9 field */
#define MXT_T9_ORIENT		9
#define MXT_T9_RANGE		18

/* MXT_TOUCH_MULTI_T9 status */
#define MXT_T9_UNGRIP		(1 << 0)
#define MXT_T9_SUPPRESS		(1 << 1)
#define MXT_T9_AMP		(1 << 2)
#define MXT_T9_VECTOR		(1 << 3)
#define MXT_T9_MOVE		(1 << 4)
#define MXT_T9_RELEASE		(1 << 5)
#define MXT_T9_PRESS		(1 << 6)
#define MXT_T9_DETECT		(1 << 7)

struct t9_range {
	u16 x;
	u16 y;
} __packed;

/* MXT_TOUCH_MULTI_T9 orient */
#define MXT_T9_ORIENT_SWITCH	(1 << 0)

/* MXT_SPT_COMMSCONFIG_T18 */
#define MXT_COMMS_CTRL		0
#define MXT_COMMS_CMD		1
#define MXT_COMMS_RETRIGEN	  (1 << 6)

/* Define for MXT_GEN_COMMAND_T6 */
#define MXT_BOOT_VALUE		0xa5
#define MXT_RESET_VALUE		0x01
#define MXT_BACKUP_VALUE	0x55

/* Define for MXT_PROCI_TOUCHSUPPRESSION_T42 */
#define MXT_T42_MSG_TCHSUP	(1 << 0)

/* T47 Stylus */
#define MXT_TOUCH_MAJOR_T47_STYLUS	1
#define MXT_TOUCH_MAJOR_T15_VIRTUAL_KEY 2

/* T63 Stylus */
#define MXT_T63_STYLUS_PRESS	(1 << 0)
#define MXT_T63_STYLUS_RELEASE	(1 << 1)
#define MXT_T63_STYLUS_MOVE		(1 << 2)
#define MXT_T63_STYLUS_SUPPRESS	(1 << 3)

#define MXT_T63_STYLUS_DETECT	(1 << 4)
#define MXT_T63_STYLUS_TIP		(1 << 5)
#define MXT_T63_STYLUS_ERASER	(1 << 6)
#define MXT_T63_STYLUS_BARREL	(1 << 7)

#define MXT_T63_STYLUS_PRESSURE_MASK	0x3F

/* Define for NOISE SUPPRESSION T72 */
#define MXT_T72_NOISE_SUPPRESSION_NOISELVCHG	(1 << 4)

/* T100 Multiple Touch Touchscreen */
//#define MXT_T100_CTRL		0
#define MXT_T100_CFG1		1
#define MXT_T100_SCRAUX		2
#define MXT_T100_TCHAUX		3
#define MXT_T100_XRANGE		13
#define MXT_T100_YRANGE		24

#define MXT_T100_XSIZE		9
#define MXT_T100_YSIZE		20
#define MXT_T100_XORIGIN		8
#define MXT_T100_YORIGIN		19

#define MXT_T100_CFG_SWITCHXY	(1 << 5)

#define MXT_T100_SCRAUX_NUMTCH	(1 << 0)
#define MXT_T100_SCRAUX_TCHAREA	(1 << 1)
#define MXT_T100_SCRAUX_ATCHAREA	(1 << 2)
#define MXT_T100_SCRAUX_INTTCHAREA		(1 << 3)

#define MXT_T100_TCHAUX_VECT	(1 << 0)
#define MXT_T100_TCHAUX_AMPL	(1 << 1)
#define MXT_T100_TCHAUX_AREA	(1 << 2)
#define MXT_T100_TCHAUX_HW		(1 << 3)
#define MXT_T100_TCHAUX_PEAK	(1 << 4)
#define MXT_T100_TCHAUX_AREAHW	(1 << 5)

#define MXT_T100_DETECT		(1 << 7)
#define MXT_T100_TYPE_MASK	0x70
#define MXT_T100_TYPE_STYLUS	0x20

#define MXT_T100_EVENT_MASK	0x0f
#define MXT_T100_EVENT_NO_EVENT	0
#define MXT_T100_EVENT_MOVE	1
#define MXT_T100_EVENT_DOWN	4
#define MXT_T100_EVENT_UP	5

/* MXT_SPT_SELFCAPHOVERCTECONFIG_T102 */
#define MXT_SELF_CHGTIME	13

/* cmd and message */
#define MXT_SELFCAP_CMD	0x1
#define MXT_SELFCMD_TUNE	0x1
#define MXT_SELFCMD_NVM_TUNE	0x2
#define MXT_SELFCMD_RAM_TUNE	0x3
#define MXT_SELFCMD_RAM_FINE	0x4
#define MXT_SELFCMD_STORE	0x5
#define MXT_SELFCMD_BG_TUNE	0x6

/* Command to unlock bootloader */
#define MXT_UNLOCK_CMD_MSB	0xaa
#define MXT_UNLOCK_CMD_LSB	0xdc

#define I2C_ACCESS_R_REG_FIXED   (1 << 0)   //don't mov reg address if read len is too long
#define I2C_ACCESS_NO_REG   (1 << 4)  // no reg address, directly access i2c reg 
#define I2C_ACCESS_NO_CACHE   (1 << 5)  //no dma cache need

/* Bootloader mode status */
#define MXT_WAITING_BOOTLOAD_CMD	0xc0	/* valid 7 6 bit only */
#define MXT_WAITING_FRAME_DATA	0x80	/* valid 7 6 bit only */
#define MXT_FRAME_CRC_CHECK	0x02
#define MXT_FRAME_CRC_FAIL	0x03
#define MXT_FRAME_CRC_PASS	0x04
#define MXT_APP_CRC_FAIL	0x40	/* valid 7 8 bit only */
#define MXT_BOOT_STATUS_MASK	0x3f
#define MXT_BOOT_EXTENDED_ID	(1 << 5)
#define MXT_BOOT_ID_MASK	0x1f

#define MXT_T6_CMD_PAGE_UP		0x01
#define MXT_T6_CMD_PAGE_DOWN		0x02
#define MXT_T6_CMD_DELTAS		0x10
#define MXT_T6_CMD_REFS			0x11
#define MXT_T6_CMD_DEVICE_ID		0x80
#define MXT_T6_CMD_TOUCH_THRESH		0xF4

#define PID_MAGIC_WORD0 64
#define PID_MAGIC_WORD1 0

#define MISC_PDS_HEAD_LEN 2
#define MISC_PDS_DATA_LEN 9

/* Touchscreen absolute values */
#define MXT_MAX_AREA		0xff

enum {
	T15_T97_KEY = 0,
	T19_KEY,
	T24_KEY,
	T42_KEY,
	T61_KEY,
	T81_KEY,
	T92_KEY,
	T93_KEY,
	T99_KEY,
	T115_KEY,
	T116_KEY,
	NUM_KEY_TYPE
};

enum f54_rawdata_limit {
	RAW_DATA_UP = 0,
	RAW_DATA_LOW = 1,
	DELT_DATA_UP = 2,
	DELT_DATA_LOW = 3,
	RX_TO_RX_UP = 4,
	RX_TO_RX_LOW = 5,
	TX_TO_TX_UP = 6,
	TX_TO_TX_LOW = 7,
};

extern int mxt_debug_msg_init(struct mxt_data *data);
extern int __mxt_read_reg(struct mxt_data *data, u16 reg, u16 len, void *val);
extern int __mxt_write_reg(struct mxt_data *data, u16 reg, u16 len, const void *val);
extern void mxt_debug_msg_remove(struct mxt_data *data);
extern void mxt_debug_msg_add(struct mxt_data *data, u8 *msg);
extern int mxt_check_firmware_version(struct mxt_data *data);
extern int mxt_update_file_name(struct mxt_data *data, char **file_name);
extern void mxt_update_config_file_name(struct mxt_data *data, char *file_name);
extern void mxt_update_fw_file_name(struct mxt_data *data, char *file_name);
extern int mxt_update_cfg_name_by_fw_name(struct mxt_data *data, char **file_name,
				const char *buf, size_t count);
extern int mxt_load_fw(struct mxt_data *data);
extern int mxt_t6_command(struct mxt_data *data, u16 cmd_offset, u8 value, bool wait);
extern int mxt_probe_info_block(struct mxt_data *data);
extern int mxt_bootloader_read(struct mxt_data *data, u8 *val, unsigned int count);
extern int mxt_bootloader_write(struct mxt_data *data, const u8 * const val, unsigned int count);
extern int mxt_lookup_bootloader_address(struct mxt_data *data, bool retry);
extern void mxt_free_object_table(struct mxt_data *data);
extern int mxt_send_bootloader_cmd(struct mxt_data *data, bool unlock);
extern int mxt_update_cfg(struct mxt_data *data);
extern void mxt_free_input_device(struct mxt_data *data);
extern int mxt_T37_fetch(struct mxt_data *data, u8 mode);
extern int process_messages(struct mxt_data *data, int timeout);
extern u32 mxt_calculate_crc(u8 *base, off_t start_off, off_t end_off);
extern int mxt_soft_reset(struct mxt_data *data);
extern int mxt_init_t7_power_cfg(struct mxt_data *data);
extern struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type);
extern int mxt_configure_objects(struct mxt_data *data);
extern int mxt_write_reg(struct mxt_data *data, u16 reg, u8 val);
extern int mxt_mem_access_init(struct mxt_data *data);
extern int get_deltas_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_rx2rx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_tx2tx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern void get_average_max_min_data(struct mxt_data *data, char *buf);
extern int mxt_t25_selftest(struct mxt_data *data);
#endif
