/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  hisi_mutex_service.c
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/mutex.h>
#include <linux/sched.h>

#include "mutex_service.h"

unsigned int g_mutex_service_ready = 0;
static DEFINE_MUTEX(start_mutex);


/*�洢����ҵ���ʼ����Ϣ������*/
static struct operation_data operation_data_array[] = {
    {_HISI_MUTEX_OPERATION(MUTEX_SERVICE_WIFIDIS_ID, MUTEX_SERVICE_WIFI_NAME,   5000, MUTEX_SERVICE_PRIORITY_5, MUTEX_SERVICE_GROUP_ID)},
    {_HISI_MUTEX_OPERATION(MUTEX_SERVICE_MIRROR_ID,  MUTEX_SERVICE_MIRROR_NAME, 5000, MUTEX_SERVICE_PRIORITY_5, MUTEX_SERVICE_GROUP_ID)},
    {_HISI_MUTEX_OPERATION(MUTEX_SERVICE_HMP_ID,     MUTEX_SERVICE_HMP_NAME,    10000, MUTEX_SERVICE_PRIORITY_5, MUTEX_SERVICE_GROUP_ID)},
    {_HISI_MUTEX_OPERATION(MUTEX_SERVICE_HDMI_ID,    MUTEX_SERVICE_HDMI_NAME,   10000, MUTEX_SERVICE_PRIORITY_6, MUTEX_SERVICE_GROUP_ID)},
};

/* mutex platform device definition*/
static struct platform_device plat_mutex_operation_dev = {
    .name = "hisi_mutex_service",
    .id = -1,
};

static struct device_attribute attributes[] = {

    __ATTR(service_start, 0220, NULL, hisi_app_service_start),
    __ATTR(service_stop, 0220, NULL, hisi_app_service_stop),
    __ATTR(notify_preempt_msg_mirror, 0444, notify_preempt_to_app_mirror, NULL ),
    __ATTR(notify_preempt_msg_wifi_display, 0444, notify_preempt_to_app_wifidisplay, NULL ),
    __ATTR(notify_preempt_msg_hmp, 0444, notify_preempt_to_app_hmp, NULL ),
    __ATTR(notify_app_alive_mirror, 0222, NULL, notify_alive_to_app_mirror ),
    __ATTR(notify_app_alive_wifi_display, 0222, NULL,  notify_alive_to_app_wifidisplay ),
    __ATTR(notify_app_alive_hmp, 0222, NULL,  notify_alive_to_app_hmp ),
};




static int get_id_by_name(const char *name)
{
    int i = 0;
    int hisi_id = -1;
    struct operation_data *array_head = &operation_data_array[0];

    if (!name) {
        pr_err("%s:%d:name is null\n", __func__, __LINE__);
        return -1;
    }

    for (i = 0; i < LEN_OF_DATA_ARRAY; i++) {
        pr_err("%s:%d:strcmp name:%s:%s\n", __func__, __LINE__, array_head->operation_name, name);
        if (0 == strncmp(array_head->operation_name, name, strlen(array_head->operation_name))) {
            hisi_id = i;
            break;
        }
        array_head++;
    }

    return hisi_id;
}


static int find_mutex_id(int id)
{
    int i = 0;
    int ret = -1;
    struct operation_data *array_head = &operation_data_array[0];
    struct operation_data *cur_operation = &operation_data_array[id];

    for (i = 0; i < LEN_OF_DATA_ARRAY; i++) {
        if (array_head->mutex_group_id == cur_operation->mutex_group_id) {
            if (REGISTER == array_head->status) {
                ret = array_head->operation_id;
                break;
            }
        }
        array_head++;
    }

    return ret;
}


static int hisi_mutex_register(int cur_id)
{
    int mutex_id = -1;
    struct operation_data *cur_operation = &operation_data_array[cur_id];
    struct operation_data *mut_operation = NULL;

    struct timeval tv;

    /*��ȡ��ǰʱ��*/
    memset(&tv, 0, sizeof(tv));
    do_gettimeofday(&tv);
    cur_operation->now_sec = tv.tv_sec;

    mutex_id = find_mutex_id(cur_id);
    if (mutex_id < 0) {
        return START_OK;
    }

    mut_operation = &operation_data_array[mutex_id];

    /*�жϱ������Ļ���ҵ���뵱ǰʱ�����ʱ�ӹ�ϵ*/
    if ( T2 < (cur_operation->now_sec - mut_operation->now_sec) ){		
        mut_operation->status = UN_REGISTER;
        pr_info("%s:%d:mut_operation has been killed, stop & start cur_operation", __func__, __LINE__);
        return START_OK;
    }

    /*��������ҵ���뵱ǰҵ���ϵΪ �����ڣ�������ռ*/
    if (mut_operation->priority >= cur_operation->priority) {
        pr_err("%s:%d:can not preempt", __func__, __LINE__);
        return START_ERROR;
    }
    else if (mut_operation->priority < cur_operation->priority) {
        /*��ʱҵ��Ϊ�ں�̬ҵ��*/
        if (NULL != mut_operation->callback) {
            pr_info("%s:%d:kernel operation ,callback to stop", __func__, __LINE__);
            mut_operation->status = NOTIFY_PREEMPT;
            mut_operation->callback(mutex_id);
        }
        else {
            pr_info("%s:%d:usr operation, wake up read interface to stop", __func__, __LINE__);
            mut_operation->status = NOTIFY_PREEMPT;
            wake_up(&mut_operation->read_wait);
        }

        /*�ȴ���ʱҵ��ֹͣ*/
        if (0 == wait_event_timeout(mut_operation->write_wait, mut_operation->status == UN_REGISTER, msecs_to_jiffies(mut_operation->timeout))) {
            pr_err("%s:%d:%d:stop timeout", __func__, __LINE__, mut_operation->status);
            return START_TIMEOUT;
        }
    }
    return START_OK;

}
int hisi_mutex_mng_service_start(int  hisi_id, pPREEMPTFUNC callback)
{
    int ret = 0;
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    /*ҵ��ID������*/
    if (hisi_id >= LEN_OF_DATA_ARRAY || hisi_id < 0) {
        pr_err("%s:%d:%d:operation_id not exist", __func__, __LINE__, hisi_id);
        return STATUS_INVALID;
    }

    cur_operation = &operation_data_array[hisi_id];

    mutex_lock(&start_mutex);

    /*��ǰҵ����ע��*/
    if (cur_operation->status == REGISTER) {

	 /*��ȡ��ǰʱ��*/
        memset(&tv, 0, sizeof(tv));
        do_gettimeofday(&tv);

        if ( T2 < (tv.tv_sec - cur_operation->now_sec) ){
		ret = START_OK;
	      	pr_info("%s:%d:cur_operation has been killed & now restart", __func__, __LINE__);
        }else{
		ret = STATUS_INVALID;
        	pr_err("%s:%d:cur_operation register", __func__, __LINE__);
        }
		
        mutex_unlock(&start_mutex);
        return ret;
    }

    /*ҵ��ע�ắ��������ע����*/
    ret = hisi_mutex_register(hisi_id);

    if (ret == START_OK) {
        pr_info("%s:%d:%d:start_ok", __func__, __LINE__, ret);
        cur_operation->callback = callback;
        cur_operation->status = REGISTER;

        mutex_unlock(&start_mutex);
        return ret;
    }

    mutex_unlock(&start_mutex);
    return ret;
}


int hisi_mutex_mng_service_stop(int  hisi_id)
{
    struct operation_data *cur_operation = NULL;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    /*ҵ��ID������*/
    if (hisi_id >= LEN_OF_DATA_ARRAY) {
        pr_err("%s:%d:%d:operation_id not exist", __func__, __LINE__, hisi_id);
        return STOP_ERROR;
    }
    cur_operation = &operation_data_array[hisi_id];

    /*��ǰҵ��δ����*/
    if (cur_operation->status == UN_REGISTER) {
        pr_err("%s:%d:%d:operation un_register", __func__, __LINE__, hisi_id);
        return STATUS_INVALID;
    }

    /*��ҵ�������ڱ���ռ����ֹͣҵ��*/
    if (cur_operation->status == NOTIFY_PREEMPT) {
        pr_info("%s:%d:preempt", __func__, __LINE__);
        cur_operation->status = UN_REGISTER;
        wake_up(&cur_operation->write_wait);
    }
    else {
        pr_info("%s:%d:normal stop", __func__, __LINE__);
        cur_operation->status = UN_REGISTER;
    }

    return STOP_OK;
}
int hisi_mutex_mng_notify_alive(int  hisi_id)
{
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    /*ҵ��ID������*/
    if (hisi_id >= LEN_OF_DATA_ARRAY) {
        pr_err("%s:%d:%d:operation_id not exist", __func__, __LINE__, hisi_id);
        return STATUS_INVALID;
    }
    cur_operation = &operation_data_array[hisi_id];

    /*��ǰҵ��δ����*/
    if (cur_operation->status == UN_REGISTER) {
        pr_err("%s:%d:%d:operation un_register", __func__, __LINE__, hisi_id);
        return STATUS_INVALID;
    }

    /*��ȡ��ǰʱ��*/
    memset(&tv, 0, sizeof(tv));
    do_gettimeofday(&tv);
    cur_operation->now_sec = tv.tv_sec;

    return STATUS_ALIVE;
}
static ssize_t hisi_app_service_start(struct device *pdev, struct device_attribute *attr,
                        const char *buf, size_t size)
{
    int hisi_id = 0;
    int ret = 0;
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    hisi_id = get_id_by_name(buf);

    /*ҵ�����ֲ�����*/
    if (hisi_id < 0) {
        dev_err(pdev, "%s:%d:operation_name is not exist\n", __func__, __LINE__);
        return STATUS_INVALID;
    }
    cur_operation = &operation_data_array[hisi_id];

    mutex_lock(&start_mutex);

    /*��ǰҵ����ע��*/
    if (cur_operation->status == REGISTER) {

	 /*��ȡ��ǰʱ��*/
        memset(&tv, 0, sizeof(tv));
        do_gettimeofday(&tv);

        if ( T2 < (tv.tv_sec - cur_operation->now_sec) ){
		ret = START_OK;
	      	pr_info("%s:%d:cur_operation has been killed & now restart", __func__, __LINE__);
        }else{
		ret = STATUS_INVALID;
        	pr_err("%s:%d:cur_operation register", __func__, __LINE__);
        }
		
        mutex_unlock(&start_mutex);
        return ret;
    }

    /*ҵ��ע�ắ��������ע����*/
    ret = hisi_mutex_register(hisi_id);

    if (ret == START_OK) {
        dev_info(pdev, "%s:%d:%d:start_ok\n", __func__, __LINE__, ret);
        cur_operation->status = REGISTER;

        mutex_unlock(&start_mutex);
        return ret;
    }

    mutex_unlock(&start_mutex);
    return ret;
}


static ssize_t hisi_app_service_stop(struct device *pdev, struct device_attribute *attr,
                        const char *buf, size_t size)
{
    int hisi_id = 0;
    struct operation_data *cur_operation = NULL;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    hisi_id = get_id_by_name(buf);

    /*ҵ�����ֲ�����*/
    if (hisi_id < 0) {
        dev_err(pdev, "%s:%d:operation_name is not exist\n", __func__, __LINE__);
        return STATUS_INVALID;
    }

    cur_operation = &operation_data_array[hisi_id];

    /*��ǰҵ��δ����*/
    if (cur_operation->status == UN_REGISTER) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return STOP_ERROR;
    }

    /*��ҵ�������ڱ���ռ����ֹͣҵ��*/
    if (cur_operation->status == NOTIFY_PREEMPT) {
        pr_info("%s:%d:operation preempted", __func__, __LINE__);
        cur_operation->status = UN_REGISTER;
        wake_up(&cur_operation->write_wait);
    }
    else {
        pr_info("%s:%d:normal stop", __func__, __LINE__);
	    cur_operation->status = UN_REGISTER;
        wake_up(&cur_operation->read_wait);
    }

    return STOP_OK;
}
static ssize_t notify_preempt_to_app_mirror(struct device *pdev, struct device_attribute *attr,
                       char *buf)
{
    struct operation_data *cur_operation = NULL;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_MIRROR_ID];

    /*��ǰҵ��δ����*/
    if (UN_REGISTER== cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }

     wait_event_interruptible(cur_operation->read_wait, (cur_operation->status == NOTIFY_PREEMPT) || (cur_operation->status == UN_REGISTER));
     dev_info(pdev, "%s:%d:notify_preempt\n", __func__, __LINE__);
     return sprintf(buf, "%s\n", NOTIFY_PREEMPT_STRING);
	
}
static ssize_t notify_preempt_to_app_wifidisplay(struct device *pdev, struct device_attribute *attr,
                       char *buf)
{
    struct operation_data *cur_operation = NULL;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_WIFIDIS_ID];


    /*��ǰҵ��δ����*/
    if (UN_REGISTER== cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }

   wait_event_interruptible(cur_operation->read_wait, (cur_operation->status == NOTIFY_PREEMPT) || (cur_operation->status == UN_REGISTER));
   dev_info(pdev, "%s:%d:notify_preempt\n", __func__, __LINE__);
   return sprintf(buf, "%s\n", NOTIFY_PREEMPT_STRING);

}
static ssize_t notify_preempt_to_app_hmp(struct device *pdev, struct device_attribute *attr,
                       char *buf)
{
    struct operation_data *cur_operation = NULL;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_HMP_ID];


    /*��ǰҵ��δ����*/
    if (UN_REGISTER == cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }
   wait_event_interruptible(cur_operation->read_wait, (cur_operation->status == NOTIFY_PREEMPT) || (cur_operation->status == UN_REGISTER));
   dev_info(pdev, "%s:%d:notify_preempt\n", __func__, __LINE__);
   return sprintf(buf, "%s\n", NOTIFY_PREEMPT_STRING);

}
static ssize_t  notify_alive_to_app_mirror(struct device *pdev, struct device_attribute *attr,
                      const char *buf, size_t size)
{
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_MIRROR_ID];

    /*��ǰҵ��δ����*/
    if (UN_REGISTER == cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }
	
    /*��ȡ��ǰʱ��*/
    memset(&tv, 0, sizeof(tv));
    do_gettimeofday(&tv);
    cur_operation->now_sec = tv.tv_sec;

    return size;
}


static ssize_t  notify_alive_to_app_wifidisplay(struct device *pdev, struct device_attribute *attr,
                      const char *buf, size_t size)
{
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_WIFIDIS_ID];

    /*��ǰҵ��δ����*/
    if (UN_REGISTER == cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }

    /*��ȡ��ǰʱ��*/
    memset(&tv, 0, sizeof(tv));
    do_gettimeofday(&tv);
    cur_operation->now_sec = tv.tv_sec;

    return size;
}


static ssize_t  notify_alive_to_app_hmp(struct device *pdev, struct device_attribute *attr,
                      const char *buf, size_t size)
{
    struct operation_data *cur_operation = NULL;
    struct timeval tv;

    BUG_ON(!HISI_MUTEX_SERVICE_INIT);

    cur_operation = &operation_data_array[MUTEX_SERVICE_HMP_ID];

    /*��ǰҵ��δ����*/
    if (UN_REGISTER == cur_operation->status) {
        dev_err(pdev, "%s:%d:operation un_register\n", __func__, __LINE__);
        return (ssize_t)(-1);
    }

    /*��ȡ��ǰʱ��*/
    memset(&tv, 0, sizeof(tv));
    do_gettimeofday(&tv);
    cur_operation->now_sec = tv.tv_sec;

    return size;
}

static int create_sysfs_interfaces(struct device *dev)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(attributes); i++)
        if (device_create_file(dev, attributes + i))
            goto error;
    return 0;

error:
    for ( ; i >= 0; i--)
        device_remove_file(dev, attributes + i);
    dev_err(dev, "%s:Unable to create interface\n", __func__);
    return -1;
}

static int remove_sysfs_interfaces(struct device *dev)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(attributes); i++)
        device_remove_file(dev, attributes + i);
    return 0;
}


static int  mutex_service_probe(struct platform_device *pdev)
{
    int i = 0;
    struct device *dev = &pdev->dev;
    struct operation_data *array_head = &operation_data_array[0];
    g_mutex_service_ready = 1;

    /*��ʼ�������е�����*/
    for (i = 0; i < LEN_OF_DATA_ARRAY; i++) {
        array_head->status = UN_REGISTER;
        array_head->callback = NULL;
        init_waitqueue_head(&array_head->write_wait);
        init_waitqueue_head(&array_head->read_wait);
        array_head++;
    }

    create_sysfs_interfaces(dev);

    return 0;
}
static int  mutex_service_remove(struct platform_device *pdev)
{
    g_mutex_service_ready = 0;

    if (!pdev) {
        pr_err("%s:%d:dev is not exist", __func__, __LINE__);
        return -1;
    }

    remove_sysfs_interfaces(&pdev->dev);

    return 0;
}

/* Description : platform driver definition*/
static struct platform_driver platform_mutex_service_driver = {
    .probe = mutex_service_probe,
    .remove = mutex_service_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name = "hisi_mutex_service",
    },
};

static int __init mutex_service_init(void)
{
    int ret = 0;

    ret = platform_device_register(&plat_mutex_operation_dev);

    if (0 != ret) {
        pr_err("%s:%d", __func__, __LINE__);
        return ret;
    }

    ret = platform_driver_register(&platform_mutex_service_driver);
    if (0 != ret) {
        pr_err("%s:%d", __func__, __LINE__);
        return ret;
    }

    return ret;
}

static void __exit mutex_service_exit(void)
{
    platform_driver_unregister(&platform_mutex_service_driver);
    return;
}

module_init(mutex_service_init);
module_exit(mutex_service_exit);

MODULE_DESCRIPTION("Hisilicon Mutex Service Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liuhailong");
