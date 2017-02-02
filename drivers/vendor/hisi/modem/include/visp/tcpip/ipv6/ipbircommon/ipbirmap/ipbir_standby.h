#ifndef _IPBIR_STANDBY_H_
#define _IPBIR_STANDBY_H_



#if (VRP_YES == TCPIP_IN_VRP)
/* not required */                                                               /* for IPOS map*/
#else
#if ((VRP_OS_WINDOWS == VRP_NO) && (VRP_PRODUCT_8070 == VRP_NO))
#include "ipbircommon/ipbirmap/visp/ipbir_visp_standby_map.h"  /* for VISP map*/
#endif
#endif

#endif  /* end of _IPBIR_STANDBY_H_ */

