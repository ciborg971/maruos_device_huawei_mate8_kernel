
#ifndef _PMU_BALONG_H_
#define _PMU_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_pmu.h>
#include <bsp_icc.h>
#include <bsp_om.h>

/*print*/
#define  pmu_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  pmu_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct pmu_adp_ops{
    char* (*version_get)(void);
    int (*sim_upres_disable)(u32 sim_id);
    void (*dcxo_compensate)(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
    void (*rfclk_enable)(u32 rf_id);
    void (*rfclk_disable)(u32 rf_id);
    u32 (*get_rtc_value)(void);
    int (*ocp_register)(int volt_id,PMU_OCP_FUNCPTR func);
};

/*º¯ÊýÉùÃ÷*/
void pmu_pmic_init(void);
void pmu_dcdc_init(void);
int pmu_adpops_register(struct pmu_adp_ops *pmic_ops);
int dummy_sim_upres_disable(u32 para);


#ifdef __cplusplus
}
#endif

#endif /* end #define _PMU_TEST_H_*/

