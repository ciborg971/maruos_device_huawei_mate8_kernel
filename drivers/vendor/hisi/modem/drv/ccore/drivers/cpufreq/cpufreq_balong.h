

#ifndef __BALONG_CPUFREQ_H__
#define __BALONG_CPUFREQ_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */
/*lint --e{322} */
#include <product_config.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <osl_list.h>
#include <osl_thread.h>
#include <bsp_memmap.h>
#include <bsp_icc.h>
#include <bsp_ipc.h>
#include <bsp_dpm.h>
#include <bsp_om.h>
#include <bsp_pm_om.h>
#include <mdrv_pm.h>
#include <bsp_cpufreq.h>


#define  cpufreq_err(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MUDU_CPUFREQ, "[cpufreq]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  cpufreq_info(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MUDU_CPUFREQ, "[cpufreq]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  cpufreq_debug(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MUDU_CPUFREQ, "[cpufreq]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))



#ifndef BSP_OK
#define BSP_OK              (0)
#endif

#ifndef BSP_ERROR
#define BSP_ERROR           (-1)
#endif

#ifndef BSP_TRUE
#define BSP_TRUE            (1)
#endif

#ifndef BSP_FALSE
#define BSP_FALSE           (0)
#endif

#ifndef BSP_NULL
#define BSP_NULL            (void*)0
#endif

#define CPUFREQ_INVALID_PROFILE   (0xFF)




/********************ö�� �ṹ�� start**********************/

typedef struct
{
    u32 usProfileUpLimit;
    u32 usProfileDownLimit;
} DFS_PROFILELIMIT_STRU;

typedef struct
{
    u32                ulDFSFunEnableFlag;
    u32                ulTimerLen;
    u32                usProfileUpTime;
    u32                usProfileDownTime;
    u32                ulProfileNum;
    DFS_PROFILELIMIT_STRU astThresHold;
} DFS_CONFIGINFO_STRU;


typedef struct
{
    u32 enCurProfile;
    u32 ulCurSysUpTime;
    u32 ulCurSysDownTime;
    u32 ulStartTime;
    u32 aulVoteMap;
} DFS_CONTROL_STRU;



struct cpufreq_frequency_table {
	unsigned int	index;     /* any */
	unsigned int	frequency; /* kHz - doesn't need to be in ascending
				    * order */
};

struct cpufreq_pm_om_qos_log {
	unsigned int taskid;
	unsigned int qos_id;
	unsigned int req_id;
	unsigned int req_value;
	unsigned int req_true_value;
};

typedef struct {
	u32 minprof;
	u32 maxprof;
	u32 curprof;
    u32 ccorelockflag;
}T_CPUFREQ_ST;

typedef struct {
	u32	pll;
	u32 clkdiv;
}T_CPUFREQ_PROFILE;

typedef struct {
	u32	a9pllcfg0;
	u32 a9pllcfg1;
}T_CPUFREQ_PLL_CONFIG;

struct cpufreq_governor_ops{
	int (*governor_init)(ST_PWC_DFS_STRU cpufreq_nv);
	int (*governor_release)();
	int (*governor_decision)(unsigned int cpuload);
	int (*governor_resume)(struct dpm_device *cpufreq_resume);
};
struct cpufreq_governor_s{
	struct list_head   entry;
	char *gov_name;
	int gov_id;
	struct cpufreq_governor_ops gov_ops;
};
struct cpufreq_driver_ops{
	int (*driver_init)();
	int (*driver_release)();
	int (*driver_target)(struct cpufreq_msg *msg);
	int (*driver_resume)(struct dpm_device *cpufreq_resume);
	int (*get_current_profile)();
};
struct cpufreq_driver_s{
	struct list_head   entry;
	char *drv_name;
	int drv_id;
	struct cpufreq_driver_ops drv_ops;
};
struct cpufreq_core_st{
    int g_ddr_request_id;
    int g_last_ddr_value_id;
    int g_cpufreq_lock_status_flag;
    int g_cpufreq_is_sync_ddr;
    int g_cpufreq_ddr_max_profile;
	char *cdrx_dump_addr;
};
/***************************for v9r1 start***********************************/
/*
 *  DFS Device QoS
 */
#define DFS_QOS_ID_ACPU_MINFREQ       (DFS_QOS_ID_ACPU_MINFREQ_E)
#define DFS_QOS_ID_ACPU_MAXFREQ       (DFS_QOS_ID_ACPU_MAXFREQ_E)
#define DFS_QOS_ID_CCPU_MINFREQ       (DFS_QOS_ID_CCPU_MINFREQ_E)
#define DFS_QOS_ID_CCPU_MAXFREQ       (DFS_QOS_ID_CCPU_MAXFREQ_E)
#define DFS_QOS_ID_DDR_MINFREQ        (DFS_QOS_ID_DDR_MINFREQ_E)
#define DFS_QOS_ID_DDR_MAXFREQ        (DFS_QOS_ID_DDR_MAXFREQ_E)
#define DFS_QOS_ID_GPU_MINFREQ        (DFS_QOS_ID_GPU_MINFREQ_E)
#define DFS_QOS_ID_GPU_MAXFREQ        (DFS_QOS_ID_GPU_MAXFREQ_E)
#define DFS_QOS_ID_BUS_MINFREQ        (DFS_QOS_ID_BUS_MINFREQ_E)
#define DFS_QOS_ID_BUS_MAXFREQ        (DFS_QOS_ID_BUS_MAXFREQ_E)
/*lint --e{830}*/
extern struct cpufreq_core_st         g_cpufreq_core_ctrl;
#define BALONG_DDRFREQUENCY_MAX       (g_cpufreq_core_ctrl.g_cpufreq_ddr_max_profile)
#define BALONG_DDRFREQUENCY_MIN       (0)
#define CPUFREQ_ARGV_KHZ2MHZ          (1000)
#define CDRX_DUMP_CPUF_MAGIC          (0xabababab)
#define CDRX_DUMP_CPUF_MAGIC_ADDR     (CDRX_DUMP_CPUF_OFFSET)            /* 0x200 */
#define CDRX_DUMP_CPUF_CUR_PROF_ADDR  (CDRX_DUMP_CPUF_MAGIC_ADDR + 4)    /* 0x204 */
#define CDRX_DUMP_CPUF_DDR_FREQ_ADDR  (CDRX_DUMP_CPUF_CUR_PROF_ADDR + 4) /* 0x208 */
#define CDRX_DUMP_CPUF_CPULOAD_ADDR   (CDRX_DUMP_CPUF_DDR_FREQ_ADDR + 4) /* 0x20C */
#define CDRX_DUMP_CPUF_ICC_SLICE_ADDR (CDRX_DUMP_CPUF_CPULOAD_ADDR + 4)  /* 0x210 */

enum DIFF_MODE_VOTE{
	DIFF_MODE_OF_LT = 0,
	DIFF_MODE_OF_GU,
	END_OF_DIFF_MODE
};
struct DFS_Qos_ST {
	int request_id;   						/*�����ģ��id��*/
	int request_flag;						/*�����Ƿ���Ч1:��Ч*/
	int request_type;						/*��������ͣ�DDR OR CPU?*/
	int request_profile;					/*�����Ӧֵ������profile��Ƶ��ֵ*/
	int task_id;
	struct list_head   entry;
};

/***************************for v9r1 end***********************************/

/********************ö�� �ṹ�� end**********************/

#ifndef CPUFREQ_ENTRY_INVALID
#define CPUFREQ_ENTRY_INVALID (~0)
#endif

#ifndef CPUFREQ_TABLE_END
#define CPUFREQ_TABLE_END     (~1)
#endif
extern u32 g_ulCCpuload;
int cpufreq_dfs_get_profile(void);
void cpufreq_lock_mcore_freq(bool lock_flag);
int cpufreq_get_ccore_profile(int request_freq);
int cpufreq_get_ddr_profile(int request_freq);
int cpufreq_get_bus_profile(int request_freq);
int cpufreq_get_qos_profile(int request_id, int request_freq);
int cpufreq_qos_request(int qos_id, unsigned int req_value, int* req_id);
int cpufreq_qos_release(int qos_id, int* req_id);
int cpufreq_qos_update(int qos_id, int req_id, unsigned int req_value);
int cpufreq_reg_init(void);
void cpufreq_recv_msg(struct cpufreq_msg *rmsg);
unsigned int cpufreq_cpu_load(void);
unsigned int cpufreq_get_load_result(void);
void cpufreq_balong_flow_callback(void);
u32 cpufreq_is_enable(void);
int cpufreq_find_min_profile(unsigned int a9freq, unsigned int ddrfreq, unsigned int slowfreq);
int cpufreq_get_current_profile(void);
void cpufreq_set_enable(int lock_flag);
void cpufreq_api_init(void);
void cpufreq_governor_init(ST_PWC_DFS_STRU cpufreq_nv);
void cpufreq_driver_init(void);
int cpufreq_driver_target(struct cpufreq_msg *msg);
int cpufreq_icc_send(struct cpufreq_msg *msg);
int cpufreq_governor_decision(unsigned int cpuload);
void cpufreq_driver_register(struct cpufreq_driver_s *cpufreq_drv);
void cpufreq_governor_register(struct cpufreq_governor_s *cpufreq_gov);
unsigned int cpufreq_assistant_regulate_ddr(int cur_profile, unsigned int result);
void cpufreq_debug_record_icc_msg(struct cpufreq_msg *msg);
void cpufreq_debug_record_target_msg(struct cpufreq_msg *msg);
void cpufreq_find_frequence(int profile, struct cpufreq_query *freq_table);
/****************************��*end*********************************/

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif
