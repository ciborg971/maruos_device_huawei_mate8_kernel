

#ifndef _TCPIP_DNSC_H_
#define _TCPIP_DNSC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/systrace.h"
#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/paf.h"

/*DNSCģ�����������������ͷ�ļ�*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "ipv6/ppmng/core/include/ppmng_pub.h" 

#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"
#include "common/ipos/ipv6/basic/nd/nd_public.h"

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/socket4/include/sock_inc.h" 

#include "tcpip/public/arith_cbb/include/arith_ip.h"
#include "tcpip/public/entry/tcpip_entry.h"

#include "common/ipos/ipv6/ip6_pub.h"

/*DNSCģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tcpip/dnsc/include/dns_api.h"
#include "tcpip/dnsc/core/include/dns_def.h"
#include "tcpip/dnsc/include/dns_pub.h"
#include "tcpip/dnsc/core/include/idns.h"
#include "tcpip/dnsc/include/dns_ext.h"
#include "tcpip/dnsc/core/include/dns_type.h"
#include "tcpip/dnsc/core/include/dns_var.h"
#include "tcpip/dnsc/shell/include/dns_sh_info.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_DNSC_H_ */

