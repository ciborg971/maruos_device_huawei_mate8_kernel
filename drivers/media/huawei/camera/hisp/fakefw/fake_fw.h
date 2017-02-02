/*
 *  Hisilicon K3 SOC camera driver source file
 *
 *  Copyright (C) Huawei Technology Co., Ltd.
 *
 * Author:      x00306635
 * Email:       xujirun@hisilicon.com
 * Date:        2014-11-11
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __FAKE_FIRMWARE_INTERFACE__
#define __FAKE_FIRMWARE_INTERFACE__

#define MAX_ACQUIRE_CAMERA_NUM       2
#define PORTING_L

typedef enum {
	CAMERA_OPENED,
	CAMERA_CLOSED,
} camera_status_e;

typedef struct _tag_fake_fw_camera_info_t {
	unsigned int handle;
	unsigned int camera_id;
	char sensor_name[32];
	camera_status_e status;
	msg_req_usecase_config_t usecase_config;
} fake_fw_camera_info_t;

/**
 * @brief the huawei fw fake fw interface.
 */
typedef struct _tag_fake_fw_msg_pro {
	/* fake firmware function table */
	int (*acquire_camera) (hisp_msg_t *isp_msg);
	int (*release_camera) (hisp_msg_t *isp_msg);
	int (*usecase_config) (hisp_msg_t *isp_msg);
	int (*request) (hisp_msg_t *isp_msg);
	int (*req_get_cap) (hisp_msg_t *isp_msg);
	int (*use_mem_pool) (hisp_msg_t *isp_msg);
	int (*set_cal_data) (hisp_msg_t *isp_msg);
	int (*unmap_buffer) (hisp_msg_t *isp_msg);
	int (*set_isp_regs) (hisp_msg_t *isp_msg);
	int (*get_isp_regs) (hisp_msg_t *isp_msg);
	int (*set_i2c_regs) (hisp_msg_t *isp_msg);
	int (*get_i2c_regs) (hisp_msg_t *isp_msg);
	int (*msg_event) (hisp_msg_t *isp_msg);
	int (*msg_log) (hisp_msg_t *isp_msg);
} fake_fw_msg_pro_t;

typedef struct _tag_fake_fw_intf {
	fake_fw_msg_pro_t *msg_pro;
} fake_fw_intf_t;

#endif /* __FAKE_FIRMWARE_INTERFACE__ */
