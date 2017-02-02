

#ifndef __PM_OM_PLATFORM_H__
#define __PM_OM_PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include <bsp_dump.h>
#include <bsp_icc.h>

#define PM_OM_DUMP_ID           DUMP_CP_PM_OM
#define PM_OM_DUMP_SIZE         (0x10000)
#define PM_OM_ICC_CHN_ID        (ICC_CHANNEL_ID_MAKEUP(ICC_CHN_IFC, IFC_RECV_FUNC_PM_OM))
#define PM_OM_CPUID             (IPC_CORE_CCORE)
#define PM_OM_WAKEUP_INTERVAL   (3000)

struct pm_om_platform
{
	struct pm_om_ctrl *ctrl;
	u32 wakeup_interval;
	u32 timestamp;
};

int pm_om_fwrite_trigger(void);
int pm_om_platform_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_PLATFORM_H__ */
