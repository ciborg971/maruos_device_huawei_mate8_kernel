/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  rf_power.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  ���ڹ�����Ƶ��������
*
*   �޸ļ�¼ :  2015��3��23��  v1.00  zuofenghua  ����
*
*************************************************************************/

#ifndef __RF_MIPI_CFG_H__
#define __RF_MIPI_CFG_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif            /* __cplusplus */

#include <product_config.h>
#include <drv_nv_def.h>

#define SYS_INIT_MIPI_NUM         48
#define MDM_POWERON_MIPI_NUM      8
#define MDM_POWEROFF_MIPI_NUM     16
#define ALL_MDM_POWEROFF_MIPI_NUM 16
#define MDM_DPM_NUM               8                   

#define MIPI_ONE_BYTE   1
#define MIPI_TWO_BYTE   2
#define MIPI_THREE_BYTE 3
#define MIPI_FOUR_BYTE  4

#ifdef CONFIG_RFFE_MIPI
/*rf mipi write*/
int balong_rf_mipi_write(RF_NV_MIPI_CMD_STRU *cmd, RF_NV_MIPI_BYTE_DATA_STRU *data, int cnt, int max);

/*suspend*/
int balong_rf_config_by_mipi_suspend(void);

/*resume*/
int balong_rf_config_by_mipi_resume(void);

/*modem poweron*/
int balong_rf_config_by_mipi_modem_on(u32 modem_id);

/*one modem poweroff*/
int balong_rf_config_by_mipi_modem_off(u32 modem_id);

/*all modem poweroff*/
int balong_rf_config_by_mipi_allmodem_off(void);

/*init*/
int balong_rf_config_by_mipi_init(void);
#else
static inline int balong_rf_mipi_write(RF_NV_MIPI_CMD_STRU *cmd, RF_NV_MIPI_BYTE_DATA_STRU *data, int cnt, int max)
{
    return RFFE_OK;
}

static inline int balong_rf_config_by_mipi_suspend(void)
{
    return RFFE_OK;
}

/*resume*/
static inline int balong_rf_config_by_mipi_resume(void)
{
    return RFFE_OK;
}

/*modem poweron*/
static inline int balong_rf_config_by_mipi_modem_on(u32 chn_id)
{
    return RFFE_OK;
}

/*one modem poweroff*/
static inline int balong_rf_config_by_mipi_modem_off(u32 modem_id)
{
    return RFFE_OK;
}

/*all modem poweroff*/
static inline int balong_rf_config_by_mipi_allmodem_off(void)
{
    return RFFE_OK;
}

/*init*/
static inline int balong_rf_config_by_mipi_init(void)
{
    return RFFE_OK;
}

#endif

#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */

