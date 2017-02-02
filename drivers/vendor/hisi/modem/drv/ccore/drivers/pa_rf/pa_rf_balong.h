#ifndef _PA_RF_BALONG_H_
#define _PA_RF_BALONG_H_

#include <mdrv_pmu.h>
#include <osl_spinlock.h>
#include <bsp_om.h>
#include <bsp_regulator.h>

#ifndef PARF_OK
#define PARF_OK      0
#endif

#ifndef PARF_ERROR
#define PARF_ERROR   -1
#endif

/* print func */
#define parf_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, "[pa_rf]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define parf_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PARF, "[pa_rf]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define parf_print_always(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, "[pa_rf]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct pmu_parf_ops
{
    /* dpm interface */
    s32 (*pmu_pa_power_on)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_pa_power_off)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_rf_power_on)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_rf_power_off)(PWC_COMM_MODEM_E modem_id);
    PWC_COMM_STATUS_E (*pmu_pa_power_status)(PWC_COMM_MODEM_E modem_id);
    PWC_COMM_STATUS_E (*pmu_rf_power_status)(PWC_COMM_MODEM_E modem_id);

    /* DRV interface */
    s32 (*drv_pastar_exc_check)(PWC_COMM_MODEM_E modem_id);
    s32 (*drv_modem_voltage_set)(EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv );
    s32 (*drv_modem_voltage_get)(EM_MODEM_CONSUMER_ID_E consumer_id, u32 *voltage_mv );
    s32 (*drv_modem_voltage_list)(EM_MODEM_CONSUMER_ID_E consumer_id, u16 **list, u32 *size);
    s32 (*drv_modem_apt_enable)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_apt_disable)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_apt_status_get)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_mode_config)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);  

    s32 (*bsp_pmu_exc_check)(void);
};

struct parf_power_ctrl_s
{
    int is_exist;
    s32 status_stub;    /* 不存在的电源开关时需要保存状态 */
    char *name;
    struct regulator *regulator;
};

#endif
