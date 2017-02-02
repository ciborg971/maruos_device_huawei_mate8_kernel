/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipbir_ipv6trans_tailor.h
  Version       : Initial Draft
  Author        : Prabhu H 71185
  Project Code  : IPB IR V1R2
  Created       : 2006/8/30
  Last Modified :
  Description   : Place holder for IR feature support macros in IPv6 module
  Function List :
  History       :
  1.Date        : 2006/8/30
    Author      : Prabhu H 71185
    Modification: Created file for IPBIRV100R002.IP.E001

******************************************************************************/

#ifndef _IPB_IR_IPV6_TAILOR_H
#define _IPB_IR_IPV6_TAILOR_H

#ifdef _cplusplus
extern "C"{
#endif

/* Changed by karthik as part of macro clean-up*/
#define IPB_IR_IPV6_TRANS_NEW_MIB_SUPPORT     VRP_NO

/* Removed by karthik as part of macro clean-up*/
/*#define IPB_IR_IPV6_AVL_TREE_SUPPORT            VRP_YES*/

/* Added by Prabhu H (71185) for MIB Coupling */
#define IPB_IR_VERSION_INDEPENDENT_TRANSPORT_MIB    VRP_NO

/* Begin: Modified by Guru for IPOS-IRV1R1 on 2006-04-10 */
/* Reason: Socket6 in VISP has not merged VPNv6 changes,
   so we cant compile our code with socket6, hence defining
   TCP6_VRP_MODULE_IPV6_VPN as VRP_MODULE_IPV6_VPN */
#ifndef VRP_MODULE_IPV6_VPN
#define VRP_MODULE_IPV6_VPN VRP_NO
#endif
#define TCP6_VRP_MODULE_IPV6_VPN   VRP_YES
#define UDP6_VRP_MODULE_IPV6_VPN   VRP_YES
#define RAWIP6_VRP_MODULE_IPV6_VPN VRP_YES

#ifndef VRP_MODULE_RTPRO_BGP
#define VRP_MODULE_RTPRO_BGP VRP_NO
#endif
#define TCP6_VRP_MODULE_RTPRO_BGP VRP_NO

#ifndef VRP_MODULE_MPLS
#define VRP_MODULE_MPLS VRP_NO
#endif
#define TCP6_VRP_MODULE_MPLS VRP_MODULE_MPLS
/* End: Modified by Guru for IPOS-IRV1R1 on 2006-04-10 */

/* Purify tool applicability in IPv6 Transport modules */
#define IPBIR_IPV6_TRANS_MODULES_PURIFY_TEST    VRP_NO
#define IPBIR_IPV6_TCP6_PURIFY_TEST             VRP_NO
#define IPBIR_IPV6_UDP6_PURIFY_TEST             VRP_NO
#define IPBIR_IPV6_RAWIP6_PURIFY_TEST           VRP_NO

/*Enable calling testability call back on global semaphore lock and unlock*/
#define IPBIR_IPV6_SEM_TEST                     VRP_NO

/* Begin : Added by Suraj+72063 */
/* For using Stub framework */
#define IPBIR_USE_PIPE_STUB                     VRP_YES

/* Enable / Disable Pipe Support */
#define IPBIR_IPV6_TRANSPORT_PIPE_SUPPORT       VRP_NO

/* End : Added by Suraj+72063 */

/* BEGIN : Added by Rajat Phull, 12-02-2008 */
/* For NULL Pointer Validation related to IN6PCB Callbacks */
#ifndef VRP_MODULE_SEC_IPSEC6
#define VRP_MODULE_SEC_IPSEC6                   VRP_NO
#endif

/* END : Added by Rajat Phull */


#define TEST_TCP6_APP                                    VRP_NO


/* Begin : Added by Karthik For dopraV2 malloc fail issue */

/*Added by guojianjun178934, 删除此宏定义，直接使用vos_id.h中的定义, 2013/12/19   问题单号:20131219_1_Compile */
/* End of Added by guojianjun178934, 2013/12/19   问题单号:20131219_1_Compile */

/* End : Added by Karthik For dopraV2 malloc fail issue */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IPB_IR_IPV6_TAILOR_H */

