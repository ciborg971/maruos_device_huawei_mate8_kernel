#ifndef _DWC_OTG_HICOMMON_
#define _DWC_OTG_HICOMMON_

/* include platform head-file */
#if defined(CONFIG_HI6250_USB)
#include "dwc_otg_hi6250.h"
#else
#error "Passable some error, It should be set a platform"
#endif

/* Public inteface */
void dwc_otg_hicommon_wake_lock(void);
void dwc_otg_hicommon_wake_unlock(void);
int dwc_otg_hicommon_probe_stage2(void);
int dwc_otg_hicommon_is_power_on(void);

void update_charger_type(void);
int dwc_otg_hcd_setup(void);
void dwc_otg_hcd_shutdown(void);

#endif
