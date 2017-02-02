/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_basic_inc.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-04
*        Author: Wangchengyang
*   Description: BFD(CBB & Shell)ģ���C�ļ������Ļ���ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-04    Wangchengyang    Create
*
*******************************************************************************/
#ifndef _BFD_BASE_INC_H_
#define _BFD_BASE_INC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************/
/* BFD Extern Header Files in Non-DataCom Enviroment (VISP)           */
/**********************************************************************/
/* VOS Basic Header Files */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_intr.h"


/* use VISP's new developed IFNET's headerfile */
#include "tcpip/ifnet/include/if_def.h"
#include "tcpip/ifnet/include/iifnet_inc.h"

#include "tcpip/public/ip_dmain.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/ip4/pp4/include/ipp4_inc.h"
#include "tcpip/ip4/pp4/core/include/pp4_input.h"

#include "tcpip/vrrp/core/include/vrrp_def.h"

#include "public/entry/tcpip_entry.h" 

/* the new SFIB has not defined all needed types.
 * still need the old ip module head files
 */
#include "tcpip/ip4/vrpip/ip_pub.h"
#include "tcpip/sfib4/include/ifiba_inc.h"

#include "tcpip/icmp4/include/icmp_pub.h"
#include "tcpip/icmp4/include/icmp_core.h"
#include "tcpip/icmp4/include/iicmp_inc.h"


#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"

#include "tcpip/socket4/core/include/sock_comp.h"
#include "tcpip/socket4/core/include/isock.h"
#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */
/*#include "tcpip/socket4/core/include/sock_key.h"*/
#include "tcpip/socket4/core/include/sock_err.h"
#include "tcpip/ipv6/socket6/core/include/sock6_pub.h"

#include "tcpip/udp4/core/include/udp.h"
#include "tcpip/udp4/core/include/udp_var.h"
#include "tcpip/udp4/core/include/udp_cmd.h"

/* VISP PPI */
#include "public/tcpip_ppi.h"

/* VISP Debug */
#include "tcpip/public/tcpip_debug.h"

/* add for BfdOverTrunkPort */
#include "tcpip/trunk/include/trunk_inc.h"

/*********************************************************************/
/* BFD Inner Header Files in All Enviroment                          */
/*********************************************************************/
#include "bfd/cbb/include/bfd_inc.h"

#include "tcpip/public/tcpip_gr.h"

/*���NSR������ص�ͷ�ļ�*/
#include "tcpip/nsr/include/nsr_api.h"
#include "tcpip/nsr/include/nsr_common.h"
#include "tcpip/nsr/include/insr.h"

extern VOS_UINT32 VOS_QueueGetMsgNum( VOS_UINT32 ulQueueId );

#ifdef __cplusplus
}
#endif

#endif

