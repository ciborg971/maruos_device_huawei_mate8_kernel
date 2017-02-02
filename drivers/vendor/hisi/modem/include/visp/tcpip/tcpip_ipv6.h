

#ifndef  _TCPIP_IPV6_H_
#define  _TCPIP_IPV6_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*******************************************************************************
*  ��Ʒʹ��˵��:
*  1. ��Ʒֻʹ��ipv4����ʱ,ֻ��Ҫ����tcpip.h����;
*  2. ��Ʒ��Ҫʹ��ipv6����ʱ,�����Ȱ���tcpip.hͷ�ļ�,�ٰ���tcpip_ipv6.hͷ�ļ�;
*******************************************************************************/

/* �޸ĸ��ļ�ʱ��ע��,Ҫ��֤��������tcpip_ipv6.h�ļ�ʱ���Ա���ͨ�� */
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/ipv6/ppmng/include/ppmng_api.h"
#include "tcpip/acl6/include/acl6_cbb_api.h"
#include "tcpip/acl6/include/acl6_api.h"

#include "tcpip/public/dopra_cbb/include/utlsll.h"

#include    "common/ipos/ipv6/ip6_pub.h"
#include    "common/ipos/ipv6/raw_ip6_public.h"

#include    "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include    "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include    "common/ipos/ipv6/basic/nd/nd_public.h"
#include    "common/ipos/ipv6/basic/pathmtu/pmtu_public.h"

#include    "common/ipos/ipv6/ipv6_ppi.h"
#include    "common/ipos/ipv6/tcp6_public.h"

#include    "common/ipos/adapter/addr_api.h"
#include    "common/ipos/adapter/icmpv6_api.h"
#include    "common/ipos/adapter/nd_api.h"
#include    "common/ipos/adapter/pmtu_api.h"
#include    "common/ipos/adapter/rawip6_api.h"
#include    "common/ipos/adapter/tcp6_api.h"
#include    "common/ipos/adapter/udp6_api.h"

/* δ�����㷨��dopra CBB�Ķ���ͷ�ļ�����Ϊ���ܺ�dopra��ͷ�ļ���ͻ,�������Ҫ���а��� */

#ifdef __cplusplus
}
#endif

#endif 

