

#ifndef  _TCPIP_PUBLIC_H_
#define  _TCPIP_PUBLIC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include"tcpip/public/tcpip_config.h"

/* ��VRPVOS��ͷ�ļ����� */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/paf.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/compbase.h"

/*PUBLICģ�����������������ͷ�ļ�*/
#include "tcpip/ifnet/include/tcpip_ifnet.h"    
#include "tcpip/ifnet/core/include/if_ha.h"
#include "tcpip/ip4/am4/core/include/am4_ha.h"
#include "tcpip/icmp4/include/icmp_api.h"
#include "tcpip/icmp4/core/include/icmp_fun.h"
#include "tcpip/socket4/include/tcpip_socket4.h"    
#include "tcpip/socket4/core/include/sock_ha.h"
#include "tcpip/etharp/core/include/etharp_ha.h"
#include "tcpip/trunk/include/tcpip_trunk.h"
#include "tcpip/ppp/include/tcpip_ppp.h"
#include "tcpip/ppp/include/tcpip_pppmux.h"
#include "tcpip/ppp/include/tcpip_mp.h"
#include "tcpip/ppp/core/include/ppp_ha.h"
#include "tcpip/pppoec/include/tcpip_poec.h"
#include "tcpip/pppoec/core/include/poec_ha.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_ha.h"
#include "tcpip/sfib4/shell/include/sfib_sh_ha.h"
#include "tcpip/bfd/cbb/include/bfd_inc.h"
#include "tcpip/poes/include/tcpip_poes.h"

/*PUBLICģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_ha.h"
#include "tcpip/public/ip_dmain.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_optim.h"

#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/tcpip_pub_ha.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_gr.h"

#ifdef __cplusplus
}
#endif

#endif 

