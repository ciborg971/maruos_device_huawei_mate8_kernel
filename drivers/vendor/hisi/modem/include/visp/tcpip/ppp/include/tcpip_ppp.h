/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ppp.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPP 
*  Date Created: 2007-08-20
*        Author: X36317
*   Description: PPPģ�����������ͷ�ļ�,���û�ʹ��PPPģ�����ʹ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-08-20   X36317       Create
*
*******************************************************************************/

#ifndef _TCPIP_PPP_H_
#define _TCPIP_PPP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"  
    
/* ��VRPVOS��ͷ�ļ����� */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/compbase.h"

/*PPPģ�����������������ͷ�ļ�*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"

#include "tcpip/etharp/core/include/etharp_pub_type.h"  
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */
/* ��Ϊ��ǰ�Ĳ��Դ�������һЩPPPmux����غ�����Ϊ��ֱ��ʹ��,��ֱ�Ӱ���*/
#include "tcpip/ppp/include/pppmux_basic_inc.h"
/* ppp_sh_main_cen�����а�����IPHC����ʾ��������������һЩ����ͷ�ļ� */
#include "ip4/pp4/include/pp4_pub.h"
#include "udp4/core/include/udp.h"
#include "tcp4/core/include/tcp.h"

#include "tcpip/dhcp4c/include/dhcp4c_api.h"

#include "tcpip/ppp/include/ppp_api.h"
#include "tcpip/ppp/include/ippp_inc.h"
#include "tcpip/ppp/core/include/ppp_ipcp_typ.h"

#include "tcpip/iphc/core/include/iphc_def.h"
#include "tcpip/iphc/core/include/iphc_typ.h"
#include "tcpip/iphc/include/iphc_api.h"
#include "tcpip/iphc/core/include/iphc_fun.h"

/*PPPģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tcpip/ppp/core/include/ippp.h"
#include "tcpip/ppp/core/include/ppp_lcp_type.h"
#include "tcpip/ppp/core/include/ppp_ip6cp_type.h"
#include "tcpip/ppp/core/include/ppp_chap_type.h"
#include "tcpip/ppp/core/include/ppp_pap_type.h"
#include "tcpip/ppp/core/include/ppp_core_var.h"
#include "tcpip/ppp/core/include/ppp_lqm_type.h"
#include "tcpip/ppp/shell/include/ppp_sh_main_cen.h"
#include "tcpip/ppp/core_osicp/include/osicp_type.h"
#include "tcpip/ppp/include/imp_inc.h"
#include "tcpip/ppp/core/include/ppp_core_hdr.h"
#include "tcpip/ppp/core/include/ppp_gr.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_PPP_H_ */

