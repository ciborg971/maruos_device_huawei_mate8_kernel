

#ifndef __MAC_DATA_H__
#define __MAC_DATA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_mib.h"
#include "mac_user.h"
#include "oam_ext_if.h"
#include "mac_regdomain.h"
#include "hal_ext_if.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 暂时放在这里，需要放入oal_net.h */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#define OAL_SWAP_BYTEORDER_16(_val) ((((_val) & 0x00FF) << 8) + (((_val) & 0xFF00) >> 8))
#define OAL_HOST2NET_SHORT(_x)  OAL_SWAP_BYTEORDER_16(_x)
#define OAL_NET2HOST_SHORT(_x)  OAL_SWAP_BYTEORDER_16(_x)
#define OAL_HOST2NET_LONG(_x)   OAL_SWAP_BYTEORDER_32(_x)
#define OAL_NET2HOST_LONG(_x)   OAL_SWAP_BYTEORDER_32(_x)

#define OAL_IPPROTO_UDP        17         /* User Datagram Protocot */
#define OAL_IPPROTO_ICMPV6     58         /* ICMPv6 */
#endif


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    MAC_DATA_DHCP                 = 0,
    MAC_DATA_ARP                  = 1,
    MAC_DATA_EAPOL                = 2,
    MAC_DATA_VIP                  = 2,  /* MAC_DATA_VIP == MAC_DATA_EAPOL, 提高关键帧判断效率，减少mips*/
    MAC_DATA_ND                   = 3,
    MAC_DATA_DHCPV6               = 4,
    MAC_DATA_TDLS                 = 5,
    MAC_DATA_PPPOE                = 6,
    MAC_DATA_WAPI                 = 7,
    MAC_DATA_VLAN                 = 8,
    MAC_DATA_BUTT
}mac_data_type_enum;
typedef oal_uint8 mac_data_type_enum_uint8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* channel结构体 */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern  oal_bool_enum_uint8 mac_is_dhcp_port(udp_hdr_stru *pst_udp_hdr);
extern oal_bool_enum_uint8 mac_is_nd(oal_ipv6hdr_stru  *pst_ipv6hdr);
extern oal_bool_enum_uint8 mac_is_dhcp6(oal_ipv6hdr_stru  *pst_ether_hdr);
extern oal_uint8 mac_get_data_type(oal_netbuf_stru *pst_netbuff);
extern oal_uint8 mac_get_eth_type(mac_ether_header_stru *pst_eth_hdr, oal_uint16 *pus_len);
extern oal_uint8 mac_get_data_type_by_snap(mac_llc_snap_stru *pst_snap);
oal_bool_enum_uint8 mac_is_eapol_key_ptk(mac_eapol_header_stru  *pst_eapol_header);
extern  oal_uint8 mac_get_data_type_from_80211(oal_netbuf_stru *pst_netbuff, oal_uint16 us_mac_hdr_len);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of mac_vap.h */

