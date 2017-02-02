/****************************************************************************/
/*                                                                          */
/*                          ip6_pub.h                                       */
/*                                                                          */
/*  Project Code    : VRP3.0                                                */
/*  Author          :                                                       */
/*  Create Date     :                                                       */
/*  Description     :                                                       */
/*  Others          :                                                       */
/*--------------------------------------------------------------------------*/
/*  Function List   :                                                       */
/*  Name                Function                                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.     */
/*                      ALL RIGHTS RESERVED                                 */
/*                                                                          */
/****************************************************************************/

 
#ifndef _IP6_PUB_H
#define _IP6_PUB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "ipv6/ppmng/core/include/ppmng_pub.h"
#include "ipv6/ppmng/core/include/ppmng_proto_mgnt.h"

/* IPv6 address���ݽṹ
   �ýṹ������IPv6��ַ�����ݡ�
   ������IPv6��ַ128bit�ľ������ݣ����ù�����������Ե�ַ�ֶεĲ��� */

/*begin added by liangjicheng for VLAN IPV6 20080808 */
/* �жϵ�ַ�Ƿ���ͬ�ĺ�IN6_ARE_ADDR_EQUAL
   ���룺IN6ADDR_S  *a    ָ����жϵĵ�ַ
        IN6ADDR_S  *b    ָ����жϵĵ�ַ
   ���أ�0������ͬ    1������ͬ     */
#define IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))

#define IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)
/*end added by liangjicheng for VLAN IPV6 20080808 */

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IP6_TYPE_H_ */
