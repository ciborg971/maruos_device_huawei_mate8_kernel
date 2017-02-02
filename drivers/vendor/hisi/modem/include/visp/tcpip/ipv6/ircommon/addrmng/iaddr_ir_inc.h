/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : iaddr_ir_inc.h
  Version       : Initial Draft
  Author        : Saravanya71677
  Created       : 2007/12/7
  Last Modified :
  Description   : iaddr_ir_inc.h header file
  Function List :
  History       :
  1.Date        : 2007/12/7
    Author      : Saravanya71677
    Modification: Created file

******************************************************************************/


#ifndef __IADDR_IR_INC_H__
#define __IADDR_IR_INC_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"
#include "ipv6/ircommon/addrmng/addr_ir_pub.h"
#include "ipv6/ircommon/addrmng/addr_ir_gen.h"

/* Interface IDs declaration for ADDR Router Interfaces */
#define IID_IP6_ADDR_IR_FUN 201

/* Interface IDs declaration for ADDR ND HOST Interfaces */
#define IID_IP6_ADDR_HOST_IR_FUN 301

/*******************************************************************************
                                ADDR ROUTER LEVEL 2 V-tables
*******************************************************************************/

DECLARE_INTERFACE(IIF_IP6_ADDR_IR_FUN)
{
    IUNKNOWN_METHODS

    /* No Ext Use, Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_DADCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Head)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_First_Addr)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Next_Addr)(IP6IFADDR_S *pstIp6IfAddr);

    /* No Ext Use - Nd alone uses */
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);

    /* Used By ND alone */
    METHOD_(IP6IFADDR_S *, pfIP6_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
        IP6IFNET_S *pIp6IfNet);

    /* Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_PrefixLen2Mask) (IN6ADDR_S *pstMask,
        ULONG ulPrefixLen);

    /* Used by ND */
    METHOD_(ULONG, pfIP6_Addr_CheckDADType)(VOID *pstIf);

    METHOD_(ULONG, pfIP6_Addr_IsValidSpecialProxyAddr)(ULONG ulIfIndex, 
                                                   IN6ADDR_S *pstIP6Addr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_GetExactAddrNoPrefix)(ULONG ulVrfIndex, 
                                                        IN6ADDR_S *pstIn6Addr);
    /*DAD��չ֪ͨ����*/
    METHOD_(VOID, pfIP6_Addr_DADExtCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);

};

/*******************************************************************************
                                ADDR ND HOST LEVEL 2 V-tables
*******************************************************************************/
DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_IR_FUN)
{
    IUNKNOWN_METHODS

    /* No Ext Use, Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_DADCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Head)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_First_Addr)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Next_Addr)(IP6IFADDR_S *pstIp6IfAddr);

    /* No Ext Use - Nd alone uses */
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);

    /* Used By ND alone */
    METHOD_(IP6IFADDR_S *, pfIP6_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
        IP6IFNET_S *pIp6IfNet);

    /* Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_PrefixLen2Mask) (IN6ADDR_S *pstMask,
        ULONG ulPrefixLen);


    /* Used by ND */
    METHOD_(ULONG, pfIP6_Addr_CheckDADType)(VOID *pstIf);

    /* ND uses */
    METHOD_(ULONG, pfIP6_Addr_HandleHostEvents)(IP6_ADDR_HOSTEVENT_S *pstNDHostEvent);
    METHOD_(ULONG, pfIP6_Addr_SetMTU)(ULONG ulIfnetIndex,
                                                ULONG ulIsNoCmd, ULONG ulMtu);

    /* UT Begin : Srinivas D S 03-12-2007
       Description : Function pointer is added */

    /* ND uses */
    METHOD_(ULONG, pfIP6_Addr_SelectIntfwithValidAddr)(ULONG ulIfIndex,
                                                ULONG *pulAddrState);
    /* UT End : Srinivas D S 03-12-2007 */
    
    METHOD_(ULONG, pfIP6_Addr_IsValidSpecialProxyAddr)(ULONG ulIfIndex, 
                                                   IN6ADDR_S *pstIP6Addr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_GetExactAddrNoPrefix)(ULONG ulVrfIndex, 
                                                        IN6ADDR_S *pstIn6Addr);
    /*DAD��չ֪ͨ����*/
    METHOD_(VOID, pfIP6_Addr_DADExtCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);

};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IADDR_IR_INC_H__ */

