/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : nd_sh_info.h
  Version       : Initial Draft
  Author        :
  Created Date  :
  Last Modified :
  Description   : Contains error information enums
  Function List :
  History       :
******************************************************************************/

/*Modification by Syed Ajim for fix BYAD01452  2003-10-21*/
/* Delete MACRO Gard #if( VRP_MODULE_SEC_ACL6 == VRP_YES ) */
/* Modification end */

#ifndef _ND_HLP_H_
#define _ND_HLP_H_


#ifdef    __cplusplus
extern "C"{
#endif


/* For chinese/english info Inf_ND_En OR Inf_ND_Ch */
enum ND_ERROR_EN
{
    ND_PREFERRED_LIFE_TIME_EXCEED,
    ND_CLI_PREFIXES_EXCEED,
    ND_CLI_PREFIX_NOT_EXIST,
    ND_NO_NB_ENTRY_INTERFACE,
    ND_INTERFACE_NOT_SUPPORTED,
    ND_NO_NB_ENTRY_ROUTER,
    ND_INVALID_MAC_ADDRESS,
    ND_INVALID_STATIC_ENTRY_UNSPECIFIED,
    ND_INVALID_STATIC_ENTRY_MULTICAST,
    ND_INVALID_STATIC_ENTRY_LOOPBACK,
    ND_INVALID_STATIC_ENTRY_V4_COMP,
    ND_INVALID_STATIC_ENTRY_V4_MAPPED,
    ND_ADDRESS_CONFLICT,
    ND_CANNOT_DELETE_DYNAMIC_ENTRY,
    ND_STATIC_ENTRY_DOES_NOT_EXIST,
    ND_NB_ENTRY_INTERFACE_EXCEED,
    ND_STATIC_ENTRY_EXCEED,
    ND_ROUTER_LIFE_TIME_LESS,

    /* Begin : Defect ID: BYAD12218,     Modifier:Rajesh,   Date:2004/9/13
       Reason   : To config Minimum RA interval.*/
    ND_ROUTER_LIFE_TIME_MIN_MORE_MAX,


    ND_ROUTER_LIFE_TIME_MIN_MORE_MAX_UNDO,

    /* lizhanbin 43795 for SWFD22264: Set MIN-RA more than 0.75*MAX-RA
       Date:2006/06/13 */
    ND_ROUTER_LIFE_TIME_MIN_MORE,/*RA-MIN is over RA-MAX*(3/4) */

    ND_RA_INTERVAL_EXCEEDS,
    ND_SERIAL_NOT_SUPPORTED,
    ND_MAX_NB_PER_BOARD,

    /* IPv6 Start  DefectID: SWFD22473   Mod:Bharath   Date : 2006/02/15 */
    ND_INVALID_PREFIX_ENTRY_UNSPECIFIED,
    ND_INVALID_PREFIX_ENTRY_MULTICAST,
    ND_INVALID_PREFIX_ENTRY_LOOPBACK,
    ND_INVALID_PREFIX_ENTRY_V4_COMP,
    ND_INVALID_PREFIX_ENTRY_V4_MAPPED,
    ND_INVALID_PREFIX_ENTRY_LINKLOCAL,
    ND_INVALID_PREFIX_ENTRY_LESS,

    /* IPv6 End  DefectID: SWFD22473   Mod:Bharath   Date : 2006/02/15 */
    /* BEGIN: Added by karthik 70713, 2006/11/22   PN:AC4D01192*/
    ND_DAD_NOT_SUP_ON_INT,

    /* BEGIN: Added by karthik 70713, 2006/11/22   PN:AC4D01209*/
    ND_NBMA_NOT_SUPPORTED,

    /* END:   Added by karthik 70713, 2006/11/22 */
    ND_ERROR_MAX_NO,

    /* Added begin: 2006-12-20, Anand 71831, for Defect Id :   AC4D01410
    * Reason: To allow configure RA prefix with length 0 */
    ND_INVALID_PREFIX_ENTRY_RANGE,

    /* Begin: Added by Santhosh 71702, 2007/12/27
       Description: Added for IAS support */
    ND_INVALID_PORT_NAME,
    ND_INVALID_IFINDEX,

    /* End: Added by Santhosh 71702, 2007/12/27 */

    /* Begin: Added by Santhosh 71702, 2008/1/21, Defect:AC4D04807 */
    ND_NO_ND_INFO,

    /* End: Added by Santhosh 71702, 2008/1/21, Defect:AC4D04807 */

    /* Added end: for Defect Id : AC4D01410 */

    /* Begin : Changes for AC4D05683 by Ranjith on 18-03-2008 */
    /* Description : Added Error Info */ 
    
    ND_MAX_STATIC_NB_PER_BOARD, /* 39 */

    /* End : Changes for AC4D05683 by Ranjith on 18-03-2008 */
    
    IP6_ENUM_NDERROR_PAD = IP6_ND_MAX_ENUM_VALUE
};


#ifdef __cplusplus
}
#endif


#endif

