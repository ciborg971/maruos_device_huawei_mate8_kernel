

#ifndef  _TCPIP_H_
#define  _TCPIP_H_

#ifdef  __cplusplus
extern "C"{
#endif


/*******************************************************************************
*  产品使用说明:
*  1. 产品只使用ipv4功能时,只需要包含tcpip.h即可;
*  2. 产品需要使用ipv6功能时,必须先包含tcpip.h头文件,再包含tcpip_ipv6.h头文件;
*******************************************************************************/

/* 修改该文件时需注意,要保证单独包含tcpip.h文件时可以编译通过 */
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/tcpip_id.h"

#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_sock.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ip4/am4/include/am4_api.h"
#include "tcpip/ip4/pp4/include/pp4_api.h"
#include "tcpip/icmp4/include/icmp_api.h"

#include "tcpip/sfib4/include/sfib4_api.h"

#include "tcpip/tcp4/include/tcp_api.h"
#include "tcpip/udp4/include/udp_api.h"
#include "tcpip/rawip4/include/rawip_api.h"

#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/arpguard/include/arpguard_api.h"
#include "tcpip/trunk/include/trunk_api.h"
#include "tcpip/1ag/include/1ag_api.h"
#include "tcpip/3ah/include/3ah_api.h"

#include "tcpip/ppp/include/mp_api.h"
#include "tcpip/ppp/include/ppp_api.h"
#include "tcpip/ppp/include/pppmux_api.h"
#include "tcpip/pppoec/include/poec_api.h"
#include "tcpip/poes/include/poes_api.h"
#include "tcpip/iphc/include/iphc_api.h"

#include "tcpip/ping/include/ping_api.h"
#include "tcpip/tracert/include/trrt_api.h"
#include "tcpip/dnsc/include/dns_api.h"

#include "tcpip/acl4/include/acl_api.h"

#include "tcpip/bfd/include/bfd_api.h"
#include "tcpip/dhcp4c/include/dhcp4c_api.h"
#include "tcpip/dhcp4r/include/dhcp4r_api.h"

#include "tcpip/ptp/include/ptp_api.h"

#include "tcpip/ipv6/ppmng/include/ppmng_api.h"
#include "tcpip/ipv6/sfib6/include/sfib6_api.h"

#include "tcpip/l2if/include/l2if_api.h"
#include "tcpip/mstp/include/mstp_api.h"
#include "tcpip/vrrp/include/vrrp_api.h"
#include "tcpip/vrf/include/vrf_api.h"

#include "tcpip/public/debug/tcpip_pcap_api.h"
#include "tcpip/public/debug/tcpip_dcc_api.h"
#include "tcpip/public/debug/tcpip_ncc_api.h"
/* 数据面对应的控制面头文件 */
#include "tcpip/public/ppimsg/tcpip_sfe_api.h"
#include "rtpro/api/inc/ospf_api.h"
#include "rtpro/api/inc/rm_api.h"
#include "tcpip/bfd_ext/include/bfd_ext_api.h"
#include "rtpro/api/inc/rip_api.h"
#include "rtpro/api/inc/diagnose_api.h"

#include "tcpip/ipv6/dhcp6c/include/dhcp6c_api.h"

/* 未包含算法和dopra CBB的对外头文件，因为可能和dopra的头文件冲突,请根据需要自行包含 */

/*adding vrf6_api.h for VRF6 related symbols*/
#include "tcpip/vrf6/include/vrf6_api.h"
#include "tcpip/vlan/include/ethvln_api.h"
#ifdef __cplusplus
}
#endif

#endif

