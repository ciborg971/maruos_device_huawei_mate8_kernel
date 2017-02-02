


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_net.h"
#include "mac_frame.h"
#include "mac_data.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_NET_C

#define OAL_HIGH_HALF_BYTE(a) (((a) & 0xF0) >> 4)
#define OAL_LOW_HALF_BYTE(a)  ((a) & 0x0F)

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL

#define WLAN_TOS_TO_HCC_QUEUE(_tos) (      \
        (((_tos) == 0) || ((_tos) == 3)) ? WLAN_UDP_BE_QUEUE : \
        (((_tos) == 1) || ((_tos) == 2)) ? WLAN_UDP_BK_QUEUE : \
        (((_tos) == 4) || ((_tos) == 5)) ? WLAN_UDP_VI_QUEUE : \
        WLAN_UDP_VO_QUEUE)

#define WLAN_DATA_VIP_QUEUE (WLAN_HI_QUEUE)
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

oal_net_device_stru  *g_past_net_device[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT] = {OAL_PTR_NULL};

oal_net_stru  g_st_init_net;

oal_sock_stru g_st_sock;

#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

 OAL_INLINE oal_bool_enum_uint8 oal_netbuf_is_dhcp_port(oal_udp_header_stru *pst_udp_hdr)
{
    if (((OAL_HOST2NET_SHORT(pst_udp_hdr->source) == 68)
        && (OAL_HOST2NET_SHORT(pst_udp_hdr->dest) == 67))
        ||((OAL_HOST2NET_SHORT(pst_udp_hdr->source) == 67)
        && (OAL_HOST2NET_SHORT(pst_udp_hdr->dest) == 68)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}



oal_bool_enum_uint8 oal_netbuf_is_nd(oal_ipv6hdr_stru  *pst_ipv6hdr)
{
    //oal_ipv6hdr_stru       *pst_ipv6hdr          = OAL_PTR_NULL;
    oal_icmp6hdr_stru      *pst_icmp6hdr;

    //pst_ipv6hdr = (oal_ipv6hdr_stru *)(pst_snap + 1);
    if (OAL_IPPROTO_ICMPV6 == pst_ipv6hdr->nexthdr)
    {
        pst_icmp6hdr = (oal_icmp6hdr_stru *)(pst_ipv6hdr + 1);

        if((MAC_ND_RSOL == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_RADVT == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_NSOL == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_NADVT == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_RMES == pst_icmp6hdr->icmp6_type))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}


oal_bool_enum_uint8 oal_netbuf_is_dhcp6(oal_ipv6hdr_stru  *pst_ipv6hdr)
{
    //oal_ipv6hdr_stru       *pst_ipv6hdr          = OAL_PTR_NULL;
    oal_udp_header_stru           *pst_udp_hdr;

    //pst_ipv6hdr = (oal_ipv6hdr_stru *)(pst_snap + 1);
    if (MAC_UDP_PROTOCAL == pst_ipv6hdr->nexthdr)
    {
        pst_udp_hdr = (oal_udp_header_stru *)(pst_ipv6hdr + 1);

        if (((OAL_HOST2NET_SHORT(pst_udp_hdr->source) == MAC_IPV6_UDP_SRC_PORT)
            && (OAL_HOST2NET_SHORT(pst_udp_hdr->dest) == MAC_IPV6_UDP_DES_PORT))
            ||((OAL_HOST2NET_SHORT(pst_udp_hdr->source) == MAC_IPV6_UDP_DES_PORT)
            && (OAL_HOST2NET_SHORT(pst_udp_hdr->dest) == MAC_IPV6_UDP_SRC_PORT)))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}



#ifdef _PRE_WLAN_FEATURE_FLOWCTL
/*****************************************************************************
 �� �� ��  : oal_netbuf_get_txtid
 ��������  : ��lan�������ĵ�ҵ��ʶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��3��3��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oal_netbuf_get_txtid(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tos)
{
    oal_ether_header_stru  *pst_ether_header;
    oal_ip_header_stru     *pst_ip;
    oal_vlan_ethhdr_stru   *pst_vlan_ethhdr;
    oal_uint32              ul_ipv6_hdr;
    oal_uint32              ul_pri;
    oal_uint16              us_vlan_tci;
    oal_uint8               uc_tid = 0;
	oal_tcp_header_stru    *pst_tcp;

    /* ��ȡ��̫��ͷ */
    pst_ether_header = (oal_ether_header_stru *)oal_netbuf_data(pst_buf);

    switch (pst_ether_header->us_ether_type)
    {
        /*lint -e778*//* ����Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):
            /* ��IP TOS�ֶ�Ѱ�����ȼ� */
            /*----------------------------------------------------------------------
                tosλ����
             ----------------------------------------------------------------------
            | bit7~bit5 | bit4 |  bit3  |  bit2  |   bit1   | bit0 |
            | �����ȼ�  | ʱ�� | ������ | �ɿ��� | ����ɱ� | ���� |
             ----------------------------------------------------------------------*/
            pst_ip = (oal_ip_header_stru *)(pst_ether_header + 1);      /* ƫ��һ����̫��ͷ��ȡipͷ */

            uc_tid = pst_ip->uc_tos >> WLAN_IP_PRI_SHIFT;

            /* ����chariot����Ľ������⴦����ֹ���� */
            if (pst_ip->uc_protocol == MAC_TCP_PROTOCAL)
            {
                pst_tcp = (oal_tcp_header_stru *)(pst_ip + 1);

                if ((OAL_HOST2NET_SHORT(MAC_CHARIOT_NETIF_PORT) == pst_tcp->us_dport)
                        || (OAL_HOST2NET_SHORT(MAC_CHARIOT_NETIF_PORT) == pst_tcp->us_sport))
                {
                    uc_tid = WLAN_TIDNO_VOICE;
                }
            }

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
            /* ��IPv6 traffic class�ֶλ�ȡ���ȼ� */
            /*----------------------------------------------------------------------
                IPv6��ͷ ǰ32Ϊ����
             -----------------------------------------------------------------------
            | �汾�� | traffic class   | ������ʶ |
            | 4bit   | 8bit(ͬipv4 tos)|  20bit   |
            -----------------------------------------------------------------------*/
            ul_ipv6_hdr = *((oal_uint32 *)(pst_ether_header + 1));  /* ƫ��һ����̫��ͷ��ȡipͷ */

            ul_pri = (OAL_NET2HOST_LONG(ul_ipv6_hdr) & WLAN_IPV6_PRIORITY_MASK) >> WLAN_IPV6_PRIORITY_SHIFT;

            uc_tid = (oal_uint8)(ul_pri >> WLAN_IP_PRI_SHIFT);

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_PAE):
            uc_tid = WLAN_DATA_VIP_TID;
            break;

#ifdef _PRE_WLAN_FEATURE_WAPI
        case OAL_HOST2NET_SHORT(ETHER_TYPE_WAI):
            uc_tid = WLAN_DATA_VIP_TID;
            break;
#endif

        case OAL_HOST2NET_SHORT(ETHER_TYPE_VLAN):
            /* ��ȡvlan tag�����ȼ� */
            pst_vlan_ethhdr = (oal_vlan_ethhdr_stru *)oal_netbuf_data(pst_buf);

            /*------------------------------------------------------------------
                802.1Q(VLAN) TCI(tag control information)λ����
             -------------------------------------------------------------------
            |Priority | DEI  | Vlan Identifier |
            | 3bit    | 1bit |      12bit      |
             ------------------------------------------------------------------*/
            us_vlan_tci = OAL_NET2HOST_SHORT(pst_vlan_ethhdr->h_vlan_TCI);

            uc_tid = us_vlan_tci >> OAL_VLAN_PRIO_SHIFT;    /* ����13λ����ȡ��3λ���ȼ� */

            break;

        /*lint +e778*/
        default:
            break;
    }

    /* ���θ�ֵ */
    *puc_tos = uc_tid;

    return;
}
#endif
oal_bool_enum_uint8 oal_netbuf_is_tcp_ack(oal_ip_header_stru  *pst_ip_hdr)
{
    oal_tcp_header_stru    *pst_tcp_hdr;
    oal_uint32              ul_ip_pkt_len;
    oal_uint32              ul_ip_hdr_len;
    oal_uint32              ul_tcp_hdr_len;

    pst_tcp_hdr     = (oal_tcp_header_stru *)(pst_ip_hdr + 1);
    ul_ip_pkt_len   = OAL_NET2HOST_SHORT(pst_ip_hdr->us_tot_len);
    ul_ip_hdr_len   = (OAL_LOW_HALF_BYTE(pst_ip_hdr->us_ihl)) << 2;
    ul_tcp_hdr_len  = (OAL_HIGH_HALF_BYTE(pst_tcp_hdr->uc_offset)) << 2;

    if (ul_tcp_hdr_len + ul_ip_hdr_len == ul_ip_pkt_len)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;

}

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL


oal_bool_enum_uint8 oal_netbuf_is_tcp_ack6(oal_ipv6hdr_stru  *pst_ipv6hdr)
{
    oal_tcp_header_stru    *pst_tcp_hdr;
    oal_uint32              ul_ip_pkt_len;
    oal_uint32              ul_tcp_hdr_len;

    pst_tcp_hdr     = (oal_tcp_header_stru *)(pst_ipv6hdr + 1);
    ul_ip_pkt_len   = OAL_NET2HOST_SHORT(pst_ipv6hdr->payload_len); /*ipv6 ���غ�, ipv6����ͷ���̶�Ϊ40�ֽ� */
    ul_tcp_hdr_len  = (OAL_HIGH_HALF_BYTE(pst_tcp_hdr->uc_offset)) << 2;

    if (ul_tcp_hdr_len == ul_ip_pkt_len)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
oal_uint16 oal_netbuf_select_queue(oal_netbuf_stru *pst_buf)
{
    oal_ether_header_stru  *pst_ether_header;
    oal_ip_header_stru     *pst_ip;
    oal_ipv6hdr_stru       *pst_ipv6;
    oal_udp_header_stru    *pst_udp_hdr;
    oal_tcp_header_stru    *pst_tcp_hdr;
    oal_vlan_ethhdr_stru   *pst_vlan_ethhdr;
    oal_uint32              ul_ipv6_hdr;
    oal_uint32              ul_pri;
    oal_uint16              us_vlan_tci;
    oal_uint8               uc_tos;
    oal_uint8               us_queue = WLAN_NORMAL_QUEUE;

    /* ��ȡ��̫��ͷ */
    pst_ether_header = (oal_ether_header_stru *)oal_netbuf_data(pst_buf);

    switch (pst_ether_header->us_ether_type)
    {
        /*lint -e778*//* ����Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):

            pst_ip = (oal_ip_header_stru *)(pst_ether_header + 1);      /* ƫ��һ����̫��ͷ��ȡipͷ */

            /* ��udp��������qos��� */
            if (MAC_UDP_PROTOCAL == pst_ip->uc_protocol)
            {
                /* ��IP TOS�ֶ�Ѱ�����ȼ� */
                /*----------------------------------------------------------------------
                    tosλ����
                 ----------------------------------------------------------------------
                | bit7~bit5 | bit4 |  bit3  |  bit2  |   bit1   | bit0 |
                | �����ȼ�  | ʱ�� | ������ | �ɿ��� | ����ɱ� | ���� |
                 ----------------------------------------------------------------------*/
                uc_tos = pst_ip->uc_tos >> WLAN_IP_PRI_SHIFT;
                us_queue = WLAN_TOS_TO_HCC_QUEUE(uc_tos);

                /* �����DHCP֡�������DATA_HIGH_QUEUE */
                pst_udp_hdr = (oal_udp_header_stru *)(pst_ip + 1);
                if (OAL_TRUE == oal_netbuf_is_dhcp_port(pst_udp_hdr))
                {
                    us_queue = WLAN_DATA_VIP_QUEUE;
                }
            }
            else if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol) /* ����TCP ack��TCP data���� */
            {
                /* ����chariot����Ľ������⴦����ֹ���� */
                pst_tcp_hdr = (oal_tcp_header_stru *)(pst_ip + 1);

                if ((OAL_HOST2NET_SHORT(MAC_CHARIOT_NETIF_PORT) == pst_tcp_hdr->us_dport)
                        || (OAL_HOST2NET_SHORT(MAC_CHARIOT_NETIF_PORT) == pst_tcp_hdr->us_sport))
                {
                    us_queue = WLAN_DATA_VIP_QUEUE;
                }
                else
                {

                    if (OAL_TRUE == oal_netbuf_is_tcp_ack(pst_ip))
                    {
                        us_queue = WLAN_TCP_ACK_QUEUE;
 //                       OAL_IO_PRINT("oal_netbuf_select_queue:: tcp ack frame\r\n");
                    }
                    else
                    {
                        us_queue = WLAN_TCP_DATA_QUEUE;
//                        OAL_IO_PRINT("oal_netbuf_select_queue:: tcp data frame\r\n");
                    }
                }
            }
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):

            /* ��IPv6 traffic class�ֶλ�ȡ���ȼ� */
            /*----------------------------------------------------------------------
                IPv6��ͷ ǰ32Ϊ����
             -----------------------------------------------------------------------
            | �汾�� | traffic class   | ������ʶ |
            | 4bit   | 8bit(ͬipv4 tos)|  20bit   |
            -----------------------------------------------------------------------*/
            pst_ipv6    = (oal_ipv6hdr_stru *)(pst_ether_header + 1); /* ƫ��һ����̫��ͷ��ȡipͷ */
            ul_ipv6_hdr = (*(oal_uint32 *)pst_ipv6);

            if (MAC_UDP_PROTOCAL == pst_ipv6->nexthdr) /* UDP���� */
            {
                ul_pri = (OAL_NET2HOST_LONG(ul_ipv6_hdr) & WLAN_IPV6_PRIORITY_MASK) >> WLAN_IPV6_PRIORITY_SHIFT;
                uc_tos = (oal_uint8)(ul_pri >> WLAN_IP_PRI_SHIFT);
                us_queue = WLAN_TOS_TO_HCC_QUEUE(uc_tos);
            }
            else if (MAC_TCP_PROTOCAL == pst_ipv6->nexthdr) /* TCP���� */
            {
                if (OAL_TRUE == oal_netbuf_is_tcp_ack6(pst_ipv6))
                {
                    us_queue = WLAN_TCP_ACK_QUEUE;
                }
                else
                {
                    us_queue = WLAN_TCP_DATA_QUEUE;
                }
            }
            /* �����ND֡�������WLAN_DATA_VIP_QUEUE���л��� */
            else if (OAL_TRUE == oal_netbuf_is_nd((oal_ipv6hdr_stru *)(pst_ether_header + 1)))
            {
                us_queue = WLAN_DATA_VIP_QUEUE;
            }

            /* �����DHCPV6֡�������WLAN_DATA_VIP_QUEUE���л��� */
            else if (OAL_TRUE == oal_netbuf_is_dhcp6((oal_ipv6hdr_stru *)(pst_ether_header + 1)))
            {
                us_queue = WLAN_DATA_VIP_QUEUE;
            }
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_PAE):
            /* �����EAPOL֡�������VO���з��� */
            us_queue = WLAN_DATA_VIP_QUEUE;
            break;

        /* TDLS֡��������������������ȼ�TID���� */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_TDLS):
            us_queue = WLAN_DATA_VIP_QUEUE;
            break;

        /* PPPOE֡������������(���ֽ׶�, �Ự�׶�)��������ȼ�TID���� */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC):
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES):
            us_queue = WLAN_DATA_VIP_QUEUE;
            break;

#ifdef _PRE_WLAN_FEATURE_WAPI
        case OAL_HOST2NET_SHORT(ETHER_TYPE_WAI):
            us_queue = WLAN_DATA_VIP_QUEUE;
            break;
#endif

        case OAL_HOST2NET_SHORT(ETHER_TYPE_VLAN):

            /* ��ȡvlan tag�����ȼ� */
            pst_vlan_ethhdr = (oal_vlan_ethhdr_stru *)oal_netbuf_data(pst_buf);

            /*------------------------------------------------------------------
                802.1Q(VLAN) TCI(tag control information)λ����
             -------------------------------------------------------------------
            |Priority | DEI  | Vlan Identifier |
            | 3bit    | 1bit |      12bit      |
             ------------------------------------------------------------------*/
            us_vlan_tci = OAL_NET2HOST_SHORT(pst_vlan_ethhdr->h_vlan_TCI);

            uc_tos = us_vlan_tci >> OAL_VLAN_PRIO_SHIFT;    /* ����13λ����ȡ��3λ���ȼ� */
            us_queue = WLAN_TOS_TO_HCC_QUEUE(uc_tos);

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
            /* �����ARP֡�������WLAN_DATA_VIP_QUEUE���л��� */
            us_queue = WLAN_DATA_VIP_QUEUE;
            break;

        /*lint +e778*/
        default:
            us_queue = WLAN_NORMAL_QUEUE;
            OAL_IO_PRINT("{oal_netbuf_select_queue::unkown us_ether_type[%d], us_queue = %d}\r\n", pst_ether_header->us_ether_type, us_queue);
            break;
    }

    /* �쳣���� */
    if (us_queue >= WLAN_NET_QUEUE_BUTT)
    {
        OAL_IO_PRINT("{oal_netbuf_select_queue:: error queue_type = %d}\r\n", us_queue);
        us_queue = WLAN_NORMAL_QUEUE;
    }

    return us_queue;
}

/*lint -e19*/
oal_module_symbol(oal_netbuf_is_tcp_ack6);
oal_module_symbol(oal_netbuf_select_queue);
/*lint +e19*/

#endif


/*lint -e19*/
oal_module_symbol(oal_netbuf_is_dhcp_port);
oal_module_symbol(oal_netbuf_is_dhcp6);
oal_module_symbol(oal_netbuf_is_nd);
oal_module_symbol(oal_netbuf_is_tcp_ack);

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
oal_module_symbol(oal_netbuf_get_txtid);
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

