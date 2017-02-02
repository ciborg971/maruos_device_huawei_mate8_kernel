#ifndef __MDRV_CCORE_SYSBOOT_H__
#define __MDRV_CCORE_SYSBOOT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_sysboot_commmon.h>

typedef enum DRV_SHUTDOWN_REASON_tag_s
{
	DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�          */
	DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣                   */
	DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����                 */
	DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�               */
	DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
	DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ         */
	DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ                 */
	DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_E;


typedef enum
{
	DRV_START_MODE_CHARGING = 0, /* ��翪��ģʽ, ps ��ҵ������  */
	DRV_START_MODE_NORMAL ,     /* ��������ģʽ������ҵ������     */
	DRV_START_MODE_UPDATE,      /* ����ģʽ */
	DRV_START_MODE_BUILT
}DRV_START_MODE_E;

#define DRV_NOT_START_UMTS (0x55aa5a5a)

DRV_START_MODE_E mdrv_sysboot_get_bootmode(void);

void mdrv_sysboot_poweroff(void);

void mdrv_sysboot_shutdown(DRV_SHUTDOWN_REASON_E eReason);

int mdrv_sysboot_stampadd(const char * phaseName, unsigned int param);

int  mdrv_sysboot_ok(void);

unsigned int mdrv_sysboot_check_startps(void);

#ifdef __cplusplus
}
#endif
#endif
