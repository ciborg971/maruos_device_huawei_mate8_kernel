

#ifndef  __BBP_PMU_H__
#define  __BBP_PMU_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

struct bbp_pwc_infolog
{
    unsigned int ops_id;
    unsigned int   act_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   act_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    unsigned int   act_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   task_id;
};
struct bbp_pwc_actlog
{
    u32 ops_id;
    u32 pwc_id;
    u64 vote_lock; /*��ǰͶƱ���*/
    unsigned int   act_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   act_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    unsigned int   act_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   task_id;
};
typedef enum{
    BBP_LOG_INFO,/*����*/
    BBP_LOG_ACTUAL/*ʵ�ʲ����˵�/��/pll*/
}BBP_LOG_TYPE_E;
typedef enum{
	BBP_LOG_POWERON = 0,
	BBP_LOG_POWEROFF,
	BBP_LOG_CLKON,
	BBP_LOG_CLKOFF,
	BBP_LOG_PLLON,
	BBP_LOG_PLLOFF,
	BBP_LOG_OTHERS
}BBP_LOG_ID_E;


struct pmu_pmom_log {
    u32 ops_id;
	u32 volt_id;
	u32 task_id;
};
enum PMU_OPS_ID
{
	PMU_OPS_ENABLE = 0,
	PMU_OPS_DISABLE = 1,
	PMU_OPS_IS_ENABLED = 2,
	PMU_OPS_GET_VOLT = 3,
	PMU_OPS_SET_VOLT = 4,
	PMU_OPS_GET_CURR = 5,
	PMU_OPS_SET_CURR = 6,
	PMU_OPS_OTHERS
};

int bbp_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int pmu_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __BBP_PMU_H__ */