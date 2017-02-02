

#ifndef  _TCPIP_H_
#define  _TCPIP_H_

#ifdef  __cplusplus
extern "C"{
#endif


/*******************************************************************************
*  ��Ʒʹ��˵��:
*  1. ��Ʒֻʹ��ipv4����ʱ,ֻ��Ҫ����tcpip.h����;
*  2. ��Ʒ��Ҫʹ��ipv6����ʱ,�����Ȱ���tcpip.hͷ�ļ�,�ٰ���tcpip_ipv6.hͷ�ļ�;
*******************************************************************************/

/* �޸ĸ��ļ�ʱ��ע��,Ҫ��֤��������tcpip.h�ļ�ʱ���Ա���ͨ�� */
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
/* �������Ӧ�Ŀ�����ͷ�ļ� */
#include "tcpip/public/ppimsg/tcpip_sfe_api.h"
#include "rtpro/api/inc/ospf_api.h"
#include "rtpro/api/inc/rm_api.h"
#include "tcpip/bfd_ext/include/bfd_ext_api.h"
#include "rtpro/api/inc/rip_api.h"
#include "rtpro/api/inc/diagnose_api.h"

#include "tcpip/ipv6/dhcp6c/include/dhcp6c_api.h"

/* δ�����㷨��dopra CBB�Ķ���ͷ�ļ�����Ϊ���ܺ�dopra��ͷ�ļ���ͻ,�������Ҫ���а��� */

/*adding vrf6_api.h for VRF6 related symbols*/
#include "tcpip/vrf6/include/vrf6_api.h"
#include "tcpip/vlan/include/ethvln_api.h"
#ifdef __cplusplus
}
#endif

#endif

