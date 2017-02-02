/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : nd_l2.h
  Version       : Initial Draft
  Author        : Karthik k70713
  Created       : 2009/12/1
  Last Modified :
  Description   : This file contains the structure and enum's required for
                  VLAN and VLANIF
  Function List :
  History       :
  1.Date        : 2009/12/1
    Author      : Karthik k70713
    Modification: Created file

******************************************************************************/


#ifndef _ND_L2_H
#define _ND_L2_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*add by wuling for ND64K project 2013-10-09 --start*/
#define IP6_ND_ADDRESS_TO_NETWORK(dst, src)\
{\
    dst[0] = VOS_HTONL(src[0]);\
    dst[1] = VOS_HTONL(src[1]);\
    dst[2] = VOS_HTONL(src[2]);\
    dst[3] = VOS_HTONL(src[3]);\
}

#define IP6_ND_HOST_PREFIX_LENGTH    128
/*add by wuling for ND64K project 2013-10-09 --end*/

/*add by wuling for ND64K project 2013-10-09 --start*/
enum IP6_ND_enum_for_return
{
    IP6_ND_enum_for_return_Continue = 1,
    IP6_ND_enum_for_return_OK,
    IP6_ND_enum_for_return_ERROR,
};

enum IP6_ND_enum_for_delete_type
{
    IP6_ND_enum_for_delete_All = 1,
    IP6_ND_enum_for_delete_Dynamic,
    IP6_ND_enum_for_delete_Static,
};

struct tagND_FOR_DO_SOMETHING_S;

typedef ULONG (*IP6_ND_FOR_DO_Proc_Type)(ND_NBENTRY_S*,struct tagND_FOR_DO_SOMETHING_S* );

typedef struct tagND_FOR_DO_SOMETHING_S
{
    ULONG       ulType;
    ULONG       ulSlot;
    ULONG       ulIfIndex;
    ULONG       ulItemNum;
    ULONG       ulSecond;
    ULONG       ulUSecond;
    USHORT      usVlanId;
    USHORT      usMasterOld;
    USHORT      usMasterNew;
    USHORT      usPad;
    NDINFO_S   *pstNDInfo;
    ND_TIMER_S  *pstNDTimer;
    IN6ADDR_S   stPrefix;
    IN6ADDR_S   stPrefixMask;
    IP6_ND_FOR_DO_Proc_Type     p_Do_Func;
    DLL_S       stPortInfo;
    USHORT      usStartVlanId;
    USHORT      usEndVlanId;
    ULONG       ulVrfIndex;
}ND_FOR_DO_SOMETHING_S;
/*add by wuling for ND64K project 2013-10-09 --end*/

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_L2_H*/

