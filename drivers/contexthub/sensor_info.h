/*
 *  drivers/misc/inputhub/inputhub_route.h
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <inputhub@huawei.com>
 *
 */
#ifndef	__SENSORS_H__
#define	__SENSORS_H__

#define PDC_SIZE		27
#define SENSOR_PLATFORM_EXTEND_DATA_SIZE    48
#define EXTEND_DATA_TYPE_IN_DTS_BYTE        0
#define EXTEND_DATA_TYPE_IN_DTS_HALF_WORD   1
#define EXTEND_DATA_TYPE_IN_DTS_WORD        2

enum sensor_name {
	ACC,
	MAG,
	GYRO,
	ALS,
	PS,
	AIRPRESS,
	HANDPRESS,
	CAP_PROX,
	SENSOR_MAX
};

typedef enum
{
	SUC=1,
	EXEC_FAIL,
	NV_FAIL,
	COMMU_FAIL
}RET_TYPE;

enum detect_state {
	DET_INIT=0,
	DET_FAIL,
	DET_SUCC
};

struct i2c_data{
	uint8_t bus_num;
	uint8_t i2c_address;
	uint16_t reg_address;
	uint8_t reg_type;
	uint8_t reg_len;
	uint8_t data[MAX_I2C_DATA_LENGTH];
};

struct t_sensor_get_data
{
	atomic_t reading;
	struct completion complete;
	struct sensor_data data;
};

struct sensor_status
{
	int status[TAG_SENSOR_END];//record whether sensor is in activate status, already opened and setdelay
	int delay[TAG_SENSOR_END];//record sensor delay time
	int opened[TAG_SENSOR_END];//record whether sensor was opened
	char gyro_selfTest_result[5];
	char mag_selfTest_result[5];
	char accel_selfTest_result[5];
	char selftest_result[TAG_SENSOR_END][5];
	struct t_sensor_get_data get_data[TAG_SENSOR_END];
};
struct g_sensor_platform_data{
    uint8_t bustype;
    uint8_t busnum;
    uint8_t i2c_address;
    uint8_t axis_map_x;
    uint8_t axis_map_y;
    uint8_t axis_map_z;
    uint8_t negate_x;
    uint8_t negate_y;
    uint8_t negate_z;
    uint8_t gpio_int1;
    uint8_t gpio_int2;
    uint16_t poll_interval;
    int offset_x;
    int offset_y;
    int offset_z;
    uint8_t g_sensor_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct gyro_platform_data{
    uint8_t bustype;
    uint8_t busnum;
    uint8_t exist;
    uint8_t i2c_address;
    uint8_t axis_map_x;
    uint8_t axis_map_y;
    uint8_t axis_map_z;
    uint8_t negate_x;
    uint8_t negate_y;
    uint8_t negate_z;
    uint8_t gpio_int1;
    uint8_t gpio_int2;
    uint16_t poll_interval;
    uint8_t gyro_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct compass_platform_data {
    uint8_t bustype;
    uint8_t busnum;
	uint8_t i2c_address;
	uint8_t axis_map_x;
	uint8_t axis_map_y;
	uint8_t axis_map_z;
	uint8_t negate_x;
	uint8_t negate_y;
	uint8_t negate_z;
	uint8_t outbit;
	uint8_t calibrate_method;
	uint8_t gpio_drdy;
	uint8_t gpio_rst;
	uint8_t pdc_data[PDC_SIZE];
	uint16_t poll_interval;
    uint8_t compass_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct als_platform_data{
    uint8_t bustype;
    uint8_t busnum;
	uint8_t i2c_address;
	uint8_t gpio_int1;
	uint8_t atime;
	uint8_t again;
	uint16_t poll_interval;
	uint16_t init_time;
	int threshold_value;
	int GA1;
	int GA2;
	int GA3;
	int COE_B;
	int COE_C;
	int COE_D;
	uint8_t als_phone_type;
	uint8_t als_phone_version;
    uint8_t als_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct ps_platform_data{
    uint8_t bustype;
    uint8_t busnum;
	uint8_t i2c_address;
	uint8_t ps_pulse_count;
	uint8_t gpio_int1;
	uint8_t persistent;
	uint8_t ptime;
	uint8_t p_on;  //need to close oscillator
	uint16_t poll_interval;
	uint16_t init_time;
	int min_proximity_value;
	int pwindows_value;
	int pwave_value;
	int threshold_value;
	int rdata_under_sun;
    uint8_t ps_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct airpress_platform_data{
    uint8_t bustype;
    uint8_t busnum;
	uint8_t i2c_address;
    int offset;
	uint16_t poll_interval;
	uint8_t airpress_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

#define CYPRESS_CHIPS		2
struct handpress_platform_data{
    uint8_t bustype;
    uint8_t busnum;
	uint8_t id[CYPRESS_CHIPS];
	uint8_t i2c_address[CYPRESS_CHIPS];
	uint8_t t_pionts[CYPRESS_CHIPS];
	uint16_t poll_interval;
	uint32_t irq[CYPRESS_CHIPS];
	uint8_t handpress_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct cap_prox_platform_data{
    uint8_t bustype;
    uint8_t busnum;
	uint8_t i2c_address;
	uint8_t gpio_int;
	uint16_t poll_interval;
	uint32_t init_reg_val[17];      /* init value */
	uint16_t freespace[2];
	uint16_t cal_fact_base[2];
	uint16_t cal_offset[2];
	uint16_t digi_offset[2];
	uint8_t cap_prox_extend_data[8];
};


struct pdr_start_config {
    unsigned int   report_interval;
    unsigned int   report_precise;
    unsigned int   report_count;
    unsigned int   report_times;
};

typedef struct {
    unsigned int sub_cmd;
    union {
        struct pdr_start_config start_param;
        unsigned int stop_param;
    };
} pdr_ioctl_t;

typedef struct pdr_result_data {
    unsigned int   time_stamp[2];
    unsigned int    step_count;
    int             relative_position_x;
    int             relative_position_y;
    int             velocity_x;
    int             velocity_y;
    unsigned int    migration_distance;
    unsigned int    absolute_altitude;
    unsigned int    absolute_bearing;
    unsigned int    reliability_flag;
} pdr_result_data_t;

extern struct sensor_status sensor_status;
extern  bool sensor_info_isensor_version;

extern void update_sensor_info(const pkt_header_t *pkt);
extern void disable_sensors_when_suspend(void);
extern void enable_sensors_when_resume(void);
extern void disable_sensors_when_reboot(void);
extern void enable_sensors_when_recovery_iom3(void);
extern void reset_calibrate_when_recovery_iom3(void);
extern sys_status_t iom3_sr_status;
extern const char *get_sensor_info_by_tag(int tag);
extern ssize_t show_sensor_read_airpress_common(struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t show_airpress_set_calidata_common(struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t show_mag_calibrate_method(struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t sensors_calibrate_show(int tag, struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t sensors_calibrate_store(int tag, struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
#endif	/* __SENSORS_H__ */
