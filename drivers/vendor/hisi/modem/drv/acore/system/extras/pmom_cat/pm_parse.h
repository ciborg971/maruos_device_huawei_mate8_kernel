

#ifndef  __PM_PARSE_H__
#define  __PM_PARSE_H__

#ifdef __cplusplus
    extern "C" {
#endif
#include <linux/types.h>
struct pm_info_acore
{
    unsigned int pm_enter_count;
    unsigned int pm_enter_asm_count;
    unsigned int pm_enter_wfi_count;
    unsigned int pm_out_count;
    unsigned int suspend_start_time;
    unsigned int suspend_end_time;
    unsigned int resume_start_time;
    unsigned int resume_end_time;
    unsigned int stamp_addr;
    unsigned int gic_flag;   /* ������GIC ֱ�Ӵ�wfi�����������������̡� �ڻ���ж�ȡ��Ҫ�ŵ��ṹ���һλ */
    unsigned int sleep_flag; /* ������ suspend;0 - ������˯������ - �ظ�����; ż�� - ֻ��һ�� ;*/
    unsigned int deepsleep_nv;
};
struct pm_info_ccore
{
    unsigned int dpm_fail_count;
    unsigned int pm_enter_count;
    unsigned int pm_enter_asm_count;
    unsigned int pm_enter_wfi_count;
    unsigned int pm_out_count;
    unsigned int suspend_start_time;
    unsigned int suspend_end_time;
	unsigned int suspend_max_start_time;
    unsigned int suspend_max_end_time;
    unsigned int suspend_max_time;
    unsigned int resume_start_time;
    unsigned int resume_end_time;
    unsigned int resume_max_time;
    unsigned int dpm_suspend_max;
    unsigned int dpm_resume_max;
};

enum PM_LOG_TYPE{
	PM_LOG_NORMAL_RECORD,
	PM_LOG_IDLE_RECORD,
	PM_LOG_SET_WAKE_SRC_RECORD,
};
struct idle_pm_s{
	unsigned int slice;
	unsigned int idle_time_ms;
	unsigned int bbp_sleeptimer;
};
typedef enum tagPmType
{
	PM_TYPE_ACORE_SLEEP = 0,
	PM_TYPE_ACORE_WAKE = 1,
	PM_TYPE_CCORE_SLEEP = 2,
	PM_TYPE_CCORE_WAKE = 3,
	PM_TYPE_ASET_WSRC = 4,
	PM_TYPE_CSET_WSRC = 5,
	PM_TYPE_AUNSET_WSRC = 6,
	PM_TYPE_CUNSET_WSRC = 7,
	PM_TYPE_BUTTOM = 8
}T_PM_TYPE;
typedef enum pm_wake_src
{
    PM_WAKE_SRC_UART0 = 0, /*for acore at_uart*/
    PM_WAKE_SRC_SOCP ,     /*for acore sd_log*/
    PM_WAKE_SRC_DRX_TIMER, /*for ccore drx timer*/
    PM_WAKE_SRC_BUT,
}PM_WAKE_SRC_E;

struct pm_wake_src_s{
	unsigned int time_slice;
	unsigned int task_id;
	unsigned int set_type;
	unsigned int  wake_src;
};

int pm_msg_parse_acore(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int pm_msg_parse_ccore(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);



#ifdef __cplusplus
}
#endif
#endif

