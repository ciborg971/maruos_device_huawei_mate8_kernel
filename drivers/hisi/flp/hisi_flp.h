/*
 * hisi flp driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author: lijiangxiong <lijiangxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*ioctrl cmd type*/
#define FLP_TAG_FLP         0
#define FLP_TAG_GPS         1
#define FLP_TAG_AR          2

#define FLP_IOCTL_TYPE_MASK             (0xF0)
#define FLP_IOCTL_PDR_START(x)          (0x464C0000 + ((x) * 0x100) + 1)
#define FLP_IOCTL_PDR_STOP(x)           (0x464C0000 + ((x) * 0x100) + 2)
#define FLP_IOCTL_PDR_READ(x)           (0x464C0000 + ((x) * 0x100) + 3)
#define FLP_IOCTL_PDR_WRITE(x)          (0x464C0000 + ((x) * 0x100) + 4)
#define FLP_IOCTL_PDR_CONFIG(x)         (0x464C0000 + ((x) * 0x100) + 5)

#define FLP_IOCTL_AR_START(x)           (0x464C0000 + ((x) * 0x100) + 0x11)
#define FLP_IOCTL_AR_STOP(x)            (0x464C0000 + ((x) * 0x100) + 0x12)
#define FLP_IOCTL_AR_READ(x)            (0x464C0000 + ((x) * 0x100) + 0x13)
#define FLP_IOCTL_AR_UPDATE(x)          (0x464C0000 + ((x) * 0x100) + 0x15)
#define FLP_IOCTL_AR_FLUSH(x)           (0x464C0000 + ((x) * 0x100) + 0x16)

/*common ioctrl*/
#define FLP_IOCTL_COMMON_GET_UTC        (0x464C0000 + 0xFFF1)
#define FLP_IOCTL_COMMON_SLEEP          (0x464C0000 + 0xFFF2)
#define FLP_IOCTL_COMMON_AWAKE_RET      (0x464C0000 + 0xFFF3)

enum{
    AR_STATE_IN_VEHICLE = 0,
    AR_STATE_ON_BICYCLE,
    AR_STATE_WALKING,
    AR_STATE_RUNNING,
    AR_STATE_STILL,
    AR_STATE_BUTT,
};

typedef struct flp_pdr_data {
    union {
        unsigned int    time_stamp[2];
        unsigned long   msec ;
    } time;
    unsigned int        step_count;
    int                 relative_position_x;
    int                 relative_position_y;
    int                 velocity_x;
    int                 velocity_y;
    unsigned int        migration_distance;
    int                 relative_altitude;
    unsigned int        absolute_bearing;
    unsigned int        reliability_flag;
}  __packed flp_pdr_data_t  ;

typedef struct buf_info {
    char *buf;
    unsigned long len;
} buf_info_t;

typedef struct pdr_start_config {
    unsigned int   report_interval;
    unsigned int   report_precise;
    unsigned int   report_count;
    unsigned int   report_times;   /*plan to remove */
} pdr_start_config_t;

/*AR struct*/
typedef struct ar_activity_event {
    unsigned int        event_type;         /*0:disable*/
    unsigned int        activity;
    union {
        unsigned int    time_stamp[2];
        unsigned long   msec ;
    } time ;
}  __packed ar_activity_event_t ;

typedef struct ar_start_config {
    unsigned int            report_interval;
    ar_activity_event_t   activity_list[6];
} ar_start_config_t;

