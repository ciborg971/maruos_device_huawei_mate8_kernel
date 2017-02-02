#ifndef _IPBIR_IP_H_
#define _IPBIR_IP_H_



#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_ip_map.h"    /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_ip_map.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_IP_H_ */

