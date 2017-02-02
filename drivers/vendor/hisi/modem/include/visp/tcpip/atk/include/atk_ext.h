/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              atk_ext.h
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: This header file includes all header files need for ATK 
*                module.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/

#ifndef _ATK_EXT_H_
#define _ATK_EXT_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"
#include "tcpip/public/tcpip_id.h"

#include "dopra/vos/config/vrpvos/vos/vospubh/basetype.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_err.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ker.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_mem.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/mbuf.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_util.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_id.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/compbase.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_tmr.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/systrace.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/wlst_inc.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_time.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_arg.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_lib.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_task.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"

#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/public/entry/tcpip_entry.h"

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"

#include "tcpip/atk/include/atk_api.h"
#include "tcpip/atk/core/include/atk_var.h"
#include "tcpip/atk/core/include/iatk.h"
#include "tcpip/atk/core/include/iatk_fac.h"
#include "tcpip/atk/core/include/atk_cfg.h"
#include "tcpip/atk/core/include/atk_func.h"
#include "tcpip/atk/core/include/atk_var.h"


#ifdef  __cplusplus
}
#endif

#endif  /* _ATK_EXT_H_ */

