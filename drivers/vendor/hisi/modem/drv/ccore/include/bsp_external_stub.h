

#ifndef _BSP_EXTERNAL_STUB_H
#define _BSP_EXTERNAL_STUB_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DRV_BUILD_SEPARATE
#include "TLPhyInterface.h"

/* SOCP DSP CHAN ADDR */
#define SOCP_DSP_CHN_ADDR          (LPHY_MAILBOX_HDLC_BUF_BASE_ADDR)
#define SOCP_DSP_CHN_SIZE          (LPHY_MAILBOX_HDLC_BUF_SIZE)

#else

/* SOCP DSP CHAN ADDR */
#define SOCP_DSP_CHN_ADDR          (0x49F80000 + 0x400)
#define SOCP_DSP_CHN_SIZE          (0x2000)

/* MAILBOX */
#ifndef LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR
#define LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR        0
#define LPHY_MAILBOX_LHPA_UP_BASE_ADDR          0
#define LPHY_MAILBOX_OM_DOWN_BASE_ADDR          0

#define LPHY_MAILBOX_LMAC_UP_BASE_ADDR          0
#define LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR        0


#define LPHY_MAILBOX_LHPA_DOWN_SIZE             0x8000
#define LPHY_MAILBOX_LHPA_UP_SIZE               0x8000

#define LPHY_MAILBOX_OM_DOWN_SIZE               0x8000

#define MASTER_TCM_ADDR_OFFSET                  0

#define LPHY_MAILBOX_LOAD_MEMORY_ADDR           0

#define LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR     0
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

