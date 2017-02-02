/*
 * hifi om.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __HIFI_OM_H__
#define __HIFI_OM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef PLATFORM_HI3XXX
#define LOG_PATH_HISI_LOGS "/data/hisi_logs/"
#define LOG_PATH_RUNNING_TRACE "/data/hisi_logs/running_trace/"
#define LOG_PATH_HIFI_LOG "/data/hisi_logs/running_trace/hifi_log/"
#define FILE_NAME_DUMP_DSP_LOG		 "hifi.log"
#define FILE_NAME_DUMP_DSP_BIN		 "hifi.bin"
#define FILE_NAME_DUMP_DSP_PANIC_LOG "hifi_panic.log"
#define FILE_NAME_DUMP_DSP_PANIC_BIN "hifi_panic.bin"
#define FILE_NAME_DUMP_DSP_OCRAM_BIN "hifi_ocram.bin"
#define FILE_NAME_DUMP_DSP_TCM_BIN   "hifi_tcm.bin"
#endif
#define HIFIDEBUG_PATH                                "hifidebug"
#define HIFIDEBUG_LEVEL_PROC_FILE                     "debuglevel"
#define HIFIDEBUG_DSPDUMPLOG_PROC_FILE                "dspdumplog"
#define HIFIDEGUB_FAULTINJECT_PROC_FILE               "dspfaultinject"

#ifndef LOG_TAG
#define LOG_TAG "hifi_misc "
#endif

#define HIFI_DUMP_FILE_NAME_MAX_LEN 256
#define DSP_DUMP_MAX_EFFECTS_CNT        (10)/*与HIFI  中dps_dump.h 中的定义保持一致*/

typedef enum {
	DUMP_DSP_LOG,
	DUMP_DSP_BIN
}DUMP_DSP_TYPE;

typedef enum {
	DSP_NORMAL,
	DSP_PANIC,
	DSP_LOG_BUF_FULL
}DSP_ERROR_TYPE;

typedef enum {
	NORMAL_LOG = 0,
	NORMAL_BIN,
	PANIC_LOG,
	PANIC_BIN,
	OCRAM_BIN,
	TCM_BIN
}DUMP_DSP_INDEX;

enum HIFI_CPU_LOAD_INFO_ENUM
{
	HIFI_CPU_LOAD_REPORT   = 0,              /* 定时上报cpu频率 */
	HIFI_CPU_LOAD_VOTE_UP,                   /* 投票ddr上调 */
	HIFI_CPU_LOAD_VOTE_DOWN,                 /* 投票ddr下调 */
	HIFI_CPU_LOAD_LACK_PERFORMANCE,          /* 性能不足 */
	HIFI_CPU_LOAD_INFO_BUTT
};

enum HIFI_CPU_OM_INFO_ENUM
{
	HIFI_CPU_OM_LOAD_INFO= 0,     /*DDR 调时hifi发消息类型*/
	HIFI_CPU_OM_ALGO_MCPS_INFO,       /*DDR调频到顶或播放卡顿hifi发送算法占用mcps信息*/
	HIFI_CPU_OM_INFO_BUTT
};
enum EFFECT_ALGO_ENUM                          /*算法列表*/
{
	ID_EFFECT_ALGO_START                =0,
	ID_EFFECT_ALGO_FORMATER,
	ID_EFFECT_ALGO_FORTE_VOICE_SPKOUT,
	ID_EFFECT_ALGO_FORTE_VOICE_MICIN,
	ID_EFFECT_ALGO_FORTE_VOICE_SPKOUT_BWE,
	ID_EFFECT_ALGO_FORTE_VOIP_MICIN,
	ID_EFFECT_ALGO_FORTE_VOIP_SPKOUT,
	ID_EFFECT_ALGO_IN_CONVERT_I2S_GENERAL,
	ID_EFFECT_ALGO_IN_CONVERT_I2S_HI363X,
	ID_EFFECT_ALGO_INTERLACE,
	ID_EFFECT_ALGO_OUT_CONVERT_I2S_GENERAL,
	ID_EFFECT_ALGO_OUT_CONVERT_I2S_HI363X,
	ID_EFFECT_ALGO_SWAP,
	ID_EFFECT_ALGO_IMEDIA_WNR_MICIN,
	ID_EFFECT_ALGO_IMEDIA_WNR_SPKOUT,
	ID_EFFECT_ALGO_SWS_INTERFACE,
	ID_EFFECT_ALGO_DTS,
	ID_EFFECT_ALGO_DRE,
	ID_EFFECT_ALGO_CHC,
	ID_EFFECT_ALGO_SRC,
	ID_EFFECT_ALGO_TTY,
	ID_EFFECT_ALGO_KARAOKE_RECORD,
	ID_EFFECT_ALGO_KARAOKE_PLAY,
	ID_EFFECT_ALGO_MLIB_CS_VOICE_CALL_MICIN,
	ID_EFFECT_ALGO_MLIB_CS_VOICE_CALL_SPKOUT,
	ID_EFFECT_ALGO_MLIB_VOIP_CALL_MICIN,
	ID_EFFECT_ALGO_MLIB_VOIP_CALL_SPKOUT,
	ID_EFFECT_ALGO_MLIB_AUDIO_PLAY,
	ID_EFFECT_ALGO_MLIB_AUDIO_RECORD,
	ID_EFFECT_ALGO_MLIB_SIRI_MICIN,
	ID_EFFECT_ALGO_MLIB_SIRI_SPKOUT,
	ID_EFFECT_ALGO_EQ,
	ID_EFFECT_ALGO_MBDRC6402,
	ID_EFFECT_ALGO_IMEDIA_VOIP_MICIN,
	ID_EFFECT_ALGO_IMEDIA_VOIP_SPKOUT,
	ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_MICIN,
	ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_SPKOUT,
	ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_SPKOUT_BWE,
	ID_EFFECT_ALGO_BUTT
};

enum EFFECT_STREAM_ID{
	AUDIO_STREAM_PCM_OUTPUT         = 0,
	AUDIO_STREAM_PLAYER_OUTPUT,
	AUDIO_STREAM_MIXER_OUTPUT,
	AUDIO_STREAM_VOICE_OUTPUT,
	AUDIO_STREAM_VOICEPP_OUTPUT,
	AUDIO_STREAM_OUTPUT_CNT,

	AUDIO_STREAM_PCM_INPUT          = 0x10,
	AUDIO_STREAM_VOICE_INPUT,
	AUDIO_STREAM_VOICEPP_INPUT,
	AUDIO_STREAM_INPUT_CNT,
};

#ifdef PLATFORM_HI6XXX
typedef struct
{
	unsigned int		work_id;
	struct work_struct	work_stru;
} hifi_mntn_work_stru;
#endif

struct hifi_om_s {
	struct task_struct* kdumpdsp_task;
	struct semaphore	dsp_dump_sema;

	unsigned int	debug_level;
	unsigned int	dsp_debug_level;
	unsigned int*	dsp_debug_level_addr;

	unsigned int	pre_dsp_dump_timestamp;
	unsigned int*	dsp_time_stamp;
	unsigned int	pre_exception_no;
	unsigned int*	dsp_exception_no;

	unsigned int*	dsp_panic_mark;

	unsigned int*	dsp_log_cur_addr;
	char*			dsp_log_addr;
	char*			dsp_bin_addr;
	char			cur_dump_time[HIFI_DUMP_FILE_NAME_MAX_LEN];
	bool			first_dump_log;
	bool			force_dump_log;
	DSP_ERROR_TYPE  dsp_error_type;

	bool			dsp_loaded;
	unsigned int	dsp_loaded_sign;

	unsigned int*	dsp_debug_kill_addr;

#ifdef PLATFORM_HI6XXX
	hifi_mntn_work_stru 	 hifi_mntn_work;
	struct workqueue_struct *hifi_mntn_wq;
#endif
};

struct hifi_dsp_dump_info{
	DSP_ERROR_TYPE error_type;
	DUMP_DSP_TYPE dump_type;
	char* file_name;
	char* data_addr;
	unsigned int data_len;
};

typedef struct
{
	unsigned short	effect_stream_id;
	unsigned short	effect_algo_id;
	unsigned int	effect_algo_mcps;
}hifi_effect_mcps_stru;

typedef struct
{
	unsigned int	cpu_load;
	unsigned int	avg_cpu_Load;
	unsigned int	ddr_freq;
}hifi_cpu_load_info_stru;

 typedef struct
{
	unsigned int	recv_msg_type;            /* CPU负载上报消息类型 */
	hifi_cpu_load_info_stru	cpu_load_info;
	unsigned int	info_type;
	unsigned int	report_interval;
} hifi_om_load_info_stru;

typedef struct
{
	unsigned int	recv_msg_type;
	hifi_cpu_load_info_stru	cpu_load_info;
	hifi_effect_mcps_stru	effect_mcps_info[DSP_DUMP_MAX_EFFECTS_CNT];
} hifi_om_effect_mcps_stru;

 typedef struct
{
	unsigned short	msg_id;
	unsigned short	reserve;
	unsigned int	  value[30];
} hifi_om_info_stru;

extern struct hifi_om_s g_om_data;

typedef struct {
	char level_char;
	unsigned int level_num;
} debug_level_com;

typedef struct _hifi_str_cmd {
	unsigned short msg_id;
	unsigned short str_len; /*length of string, include \0 */
	char           str[0];
} hifi_str_cmd;

struct hifi_effect_info_stru {
	unsigned int	effect_id;
	char		effect_name[64];
} ;

#ifdef PLATFORM_HI3XXX
#define HIFI_STAMP (unsigned int)readl(g_om_data.dsp_time_stamp)
#endif

#ifdef PLATFORM_HI6XXX
#define HIFI_STAMP 0
#endif

#define logd(fmt, ...) \
do {\
	if (g_om_data.debug_level >= 3) {\
		printk(LOG_TAG"[D][%u]:%s:%d: "fmt, HIFI_STAMP, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
	}\
} while(0);

#define logi(fmt, ...) \
do {\
	if (g_om_data.debug_level >= 2) {\
		printk(LOG_TAG"[I][%u]:%s:%d: "fmt, HIFI_STAMP, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
	}\
} while(0);


#define logw(fmt, ...) \
do {\
	if (g_om_data.debug_level >= 1) {\
		printk(LOG_TAG"[W][%u]:%s:%d: "fmt, HIFI_STAMP, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
	}\
} while(0);

#define loge(fmt, ...) \
do {\
		printk(LOG_TAG"[E][%u]:%s:%d: "fmt, HIFI_STAMP, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
} while(0);

#define IN_FUNCTION   logd("begin.\n");
#define OUT_FUNCTION  logd("end.\n");

void hifi_om_init(struct platform_device *dev, unsigned char* hifi_priv_base_virt, unsigned char* hifi_priv_base_phy);
void hifi_om_deinit(struct platform_device *dev);

int hifi_dsp_dump_hifi(unsigned long arg);
void hifi_dump_panic_log(void);

bool hifi_is_loaded(void);

void hifi_om_effect_mcps_info_show(hifi_om_effect_mcps_stru *hifi_mcps_info);
void hifi_om_cpu_load_info_show(hifi_om_load_info_stru *hifi_om_info);

#ifdef PLATFORM_HI3XXX
int hifi_get_dmesg(void __user *arg);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

