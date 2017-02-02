 /* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_display_effect.h"
#include "hisi_fb.h"

static bool g_is_ce_service_init = false;
static spinlock_t g_ce_service_lock;
static ce_service_t g_ce_services[CE_SERVICE_LIMIT];

extern int g_dss_effect_ce_en;

#define ce_service_wait_event(wq, condition)												\
{																							\
	long ret = 0;																			\
	do {																					\
		ret = wait_event_interruptible_timeout(wq, condition, msecs_to_jiffies(100000));	\
	} while(!ret);																			\
	if (ret == -ERESTARTSYS) {																\
		hisifb_ce_service_deinit();															\
	}																						\
}																							\


static inline ce_service_t *get_available_service(ce_service_status status)
{
	int i = 0;
	ce_service_t *service = NULL;
	hisifb_ce_service_init();
	for (i = 0; i < CE_SERVICE_LIMIT; i++) {
		if (g_ce_services[i].status == status) {
			g_ce_services[i].status = (g_ce_services[i].status + 1) % CE_SERVICE_STATUS_COUNT;
			service = &g_ce_services[i];
			break;
		}
	}
	return service;
}

static inline void service_transform_to_next_status(ce_service_t *service)
{
	service->status = (service->status + 1) % CE_SERVICE_STATUS_COUNT;
}

int do_contrast(dss_ce_info_t * info)
{
	if (g_is_ce_service_init) {
		ce_service_t *service = get_available_service(CE_SERVICE_HIST_REQ);

		if (service) {
			service->ce_info = info;
			wake_up_interruptible(&service->wq_hist);
			ce_service_wait_event(service->wq_lut, !service->ce_info || !g_is_ce_service_init);
			if (!g_is_ce_service_init) {
				info->algorithm_result = -1;
			}
		} else {
			info->algorithm_result = -1;
		}
	} else {
		hisifb_ce_service_init();
		info->algorithm_result = -1;
	}

	return info->algorithm_result;
}

void hisi_effect_init(struct hisi_fb_data_type *hisifd)
{
	spin_lock_init(&g_ce_service_lock);
	mutex_init(&(hisifd->ce_ctrl.ctrl_lock));
}

void hisifb_ce_service_init(void)
{
	spin_lock(&g_ce_service_lock);
	if (!g_is_ce_service_init) {
		int i = 0;
		memset(g_ce_services, 0, sizeof(g_ce_services));
		for (i = 0; i < CE_SERVICE_LIMIT; i++) {
			init_waitqueue_head(&g_ce_services[i].wq_hist);
			init_waitqueue_head(&g_ce_services[i].wq_lut);
		}
		g_is_ce_service_init = true;
	}
	spin_unlock(&g_ce_service_lock);
}

void hisifb_ce_service_deinit(void)
{
	spin_lock(&g_ce_service_lock);
	if (g_is_ce_service_init) {
		int i = 0;
		g_is_ce_service_init = false;
		for (i = 0; i < CE_SERVICE_LIMIT; i++) {
			wake_up_interruptible(&g_ce_services[i].wq_hist);
			wake_up_interruptible(&g_ce_services[i].wq_lut);
		}
	}
	spin_unlock(&g_ce_service_lock);
}

int hisifb_ce_service_get_support(struct fb_info *info, void __user *argp)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int support = 0;
	int ret = 0;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (pinfo->acm_ce_support || pinfo->prefix_ce_support) {
		support = 1;
	}

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_to_user(argp, &support, sizeof(support));
	if (ret) {
		HISI_FB_ERR("copy_to_user failed! ret=%d.\n", ret);
		return ret;
	}

	return ret;
}

int hisifb_ce_service_get_limit(struct fb_info *info, void __user *argp)
{
	int limit = CE_SERVICE_LIMIT;
	int ret = 0;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_to_user(argp, &limit, sizeof(limit));
	if (ret) {
		HISI_FB_ERR("copy_to_user failed! ret=%d.\n", ret);
		return ret;
	}

	return ret;
}

int hisifb_ce_service_get_hist(void __user *argp)
{
	ce_parameter_t param;
	ce_service_t *service = get_available_service(CE_SERVICE_IDLE);
	int ret = 0;

	if (service == NULL) {
		HISI_FB_ERR("service is NULL\n");
		return -2;
	}

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_from_user(&param, argp, sizeof(ce_parameter_t));
	if (ret) {
		HISI_FB_ERR("copy_from_user failed! ret=%d.\n", ret);
		return -2;
	}

	ce_service_wait_event(service->wq_hist, service->ce_info || !g_is_ce_service_init);
	if (service->ce_info) {
		param.service = service;
		param.width = service->ce_info->width;
		param.height = service->ce_info->height;
		param.hist_mode = service->ce_info->hist_mode;
		param.mode = service->ce_info->mode;
		param.ce_alg_param = *service->ce_info->p_ce_alg_param;
		ret = copy_to_user(param.histogram, service->ce_info->histogram, sizeof(service->ce_info->histogram));
		if (ret) {
			HISI_FB_ERR("copy_to_user failed(hist)! ret=%d.\n", ret);
			return -2;
		}
		ret = copy_to_user(argp, &param, sizeof(ce_parameter_t));
		if (ret) {
			HISI_FB_ERR("copy_to_user failed(param)! ret=%d.\n", ret);
			return -2;
		}
	} else {
		ret = -1;
	}

	return ret;
}

int hisifb_ce_service_set_lut(struct fb_info *info, void __user *argp)
{
	ce_parameter_t param;
	ce_service_t *service = NULL;
	int ret = 0;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_from_user(&param, argp, sizeof(ce_parameter_t));
	if (ret) {
		HISI_FB_ERR("copy_from_user(param) failed! ret=%d.\n", ret);
		return -2;
	}

	service = (ce_service_t *)param.service;
	if (service == NULL || service->ce_info == NULL) {
		HISI_FB_ERR("service or ce_info is NULL\n");
		return -1;
	}

	service->ce_info->algorithm_result = param.result;
	if (service->ce_info->algorithm_result == 0) {
		ret = copy_from_user(service->ce_info->lut_table, param.lut_table, sizeof(service->ce_info->lut_table));
		if (ret) {
			HISI_FB_ERR("copy_from_user(lut_table) failed! ret=%d.\n", ret);
			return -2;
		}
	}

	service->ce_info = NULL;
	service_transform_to_next_status(service);
	wake_up_interruptible(&service->wq_lut);
	return ret;
}

ssize_t hisifb_display_effect_ce_ctrl_show(struct fb_info *info, char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	dss_display_effect_t *ce_ctrl = NULL;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);
	ce_ctrl = &(hisifd->ce_ctrl);
	BUG_ON(ce_ctrl == NULL);

	return snprintf(buf, PAGE_SIZE, "%d\n", ce_ctrl->ctrl_enabled);
}

ssize_t hisifb_display_effect_ce_ctrl_store(struct fb_info *info, const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	dss_display_effect_t *ce_ctrl = NULL;
	unsigned int enable = 0;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);
	ce_ctrl = &(hisifd->ce_ctrl);
	BUG_ON(ce_ctrl == NULL);

	enable = (buf[0] == '1') ? 1 : 0;

	mutex_lock(&(ce_ctrl->ctrl_lock));
	if (ce_ctrl->ctrl_enabled != enable) {
		ce_ctrl->ctrl_enabled = enable;
	}
	mutex_unlock(&(ce_ctrl->ctrl_lock));

	return count;
}

