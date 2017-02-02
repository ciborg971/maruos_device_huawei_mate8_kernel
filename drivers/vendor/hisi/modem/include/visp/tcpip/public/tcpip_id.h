

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_ID_H
#define _TCPIP_ID_H


/********************************************************/
/*                  define the CID base                 */
/********************************************************/
#ifndef CID_GLOBAL_BASE
#define CID_GLOBAL_BASE     0       /* VRPV5 defined it*/
#endif
#ifndef CID_INTERNAL
#define CID_INTERNAL        100     /* VRPV5 defined it*/
#endif

#define CID_IPV4_BASE       ( (CID_GLOBAL_BASE) + 10*(CID_INTERNAL) ) /* �ȴ�VRPV5R1ͳһ���� */
#define CID_IPV4V6_BASE     ( (CID_GLOBAL_BASE) + 11*(CID_INTERNAL) ) /* �ȴ�VRPV5R1ͳһ���� */
#define CID_SEC_BASE        ( (CID_GLOBAL_BASE) + 12*(CID_INTERNAL) ) /* �����IR IPSEC/IKE��CID�ռ� */    
#define CID_VISP_IPV6_BASE  ( (CID_GLOBAL_BASE) + 13*(CID_INTERNAL) ) /* �����VISP��IPv6��CID�ռ� */    

#ifndef CID_IPV6_BASE
#define CID_IPV6_BASE       ((CID_GLOBAL_BASE) + 2*(CID_INTERNAL))    /* �����IR IPv6��CID�ռ� */
#endif

/********************************************************/
/*                  define IID base                     */
/********************************************************/
#ifndef IID_GLOBAL_BASE
#define IID_GLOBAL_BASE     0       /* VRPV5 defined it*/
#endif
#ifndef IID_INTERNAL
#define IID_INTERNAL        1000    /* VRPV5 defined it*/
#endif

#define IID_IPV4_BASE       ( (IID_GLOBAL_BASE) + 10*(IID_INTERNAL) )   /* �ȴ�VRPV5R1ͳһ���� */
#define IID_IPV4V6_BASE     ( (IID_GLOBAL_BASE) + 11*(IID_INTERNAL) )   /* �ȴ�VRPV5R1ͳһ���� */
#define IID_SEC_BASE        ( (IID_GLOBAL_BASE) + 12*(IID_INTERNAL) )   /* �����IR IPSEC/IKE��IID�ռ�*/    
#define IID_VISP_IPV6_BASE  ( (IID_GLOBAL_BASE) + 13*(IID_INTERNAL) )   /* �����VISP��IPv6��IID�ռ� */

#ifndef IID_IPV6_BASE
#define IID_IPV6_BASE       ((IID_GLOBAL_BASE) + 2*(IID_INTERNAL))      /* �����IR IPv6��IID�ռ� */
#endif

/********************************************************/
/*                  define CID and IID                  */
/********************************************************/

/* IPv4 DHCP Client component, only using out of VRP */
#define CID_IPV4_DHCPC4             ( CID_IPV4_BASE + 1 ) 

#define IID_IPV4_DHCPC4_INTF_FUN    ( IID_IPV4_BASE + 10 )
#define IID_IPV4_DHCPC4_INTF_CFG    ( IID_IPV4_BASE + 11 )
#define IID_IPV4_DHCPC4_INTF_SSA    ( IID_IPV4_BASE + 12 )


/* IPv4 Socket component */
#define CID_IPV4_SOCKET4            ( CID_IPV4_BASE + 2 )

#define IID_IPV4_SOCKET4_INTF_FUN   ( IID_IPV4_BASE + 20 )
#define IID_IPV4_SOCKET4_INTF_CFG   ( IID_IPV4_BASE + 21 )
#define IID_IPV4_SOCKET4_INTF_SSA   ( IID_IPV4_BASE + 22 )


/* IPv4 TCP component */
#define CID_IPV4_TCP4               ( CID_IPV4_BASE + 3 )

#define IID_IPV4_TCP4_INTF_FUN      ( IID_IPV4_BASE + 30 )
#define IID_IPV4_TCP4_INTF_CFG      ( IID_IPV4_BASE + 31 )
#define IID_IPV4_TCP4_INTF_SSA      ( IID_IPV4_BASE + 32 )

/* IPv4 UDP component */
#define CID_IPV4_UDP4               ( CID_IPV4_BASE + 4 )

#define IID_IPV4_UDP4_INTF_FUN      ( IID_IPV4_BASE + 40 )
#define IID_IPV4_UDP4_INTF_CFG      ( IID_IPV4_BASE + 41 )
#define IID_IPV4_UDP4_INTF_SSA      ( IID_IPV4_BASE + 42 )


/* IPv4 RawIP component */
#define CID_IPV4_RAWIP4             ( CID_IPV4_BASE + 5 )

#define IID_IPV4_RAWIP4_INTF_FUN    ( IID_IPV4_BASE + 50 )
#define IID_IPV4_RAWIP4_INTF_CFG    ( IID_IPV4_BASE + 51 )
#define IID_IPV4_RAWIP4_INTF_SSA    ( IID_IPV4_BASE + 52 )


/* IPv4 ICMP component */
#define CID_IPV4_ICMP4              ( CID_IPV4_BASE + 6 )

#define IID_IPV4_ICMP4_INTF_FUN     ( IID_IPV4_BASE + 60 )
#define IID_IPV4_ICMP4_INTF_CFG     ( IID_IPV4_BASE + 61 )
#define IID_IPV4_ICMP4_INTF_SSA     ( IID_IPV4_BASE + 62 )


/* IPv4 Protocol Process component */
#define CID_IPV4_PP4                ( CID_IPV4_BASE + 7 )

#define IID_IPV4_PP4_INTF_FUN       ( IID_IPV4_BASE + 70 )
#define IID_IPV4_PP4_INTF_CFG       ( IID_IPV4_BASE + 71 )
#define IID_IPV4_PP4_INTF_SSA       ( IID_IPV4_BASE + 72 )


/* IPv4 Address Manager component */
#define CID_IPV4_AM4                ( CID_IPV4_BASE + 8 )

#define IID_IPV4_AM4_INTF_FUN       ( IID_IPV4_BASE + 80 )
#define IID_IPV4_AM4_INTF_CFG       ( IID_IPV4_BASE + 81 )
#define IID_IPV4_AM4_INTF_SSA       ( IID_IPV4_BASE + 82 )


/* IPv4 Simple FIB Container component, only using out of VRP*/
#define CID_IPV4_SFIBC4             ( CID_IPV4_BASE + 9 )

#define IID_IPV4_SFIBC4_INTF_FUN    ( IID_IPV4_BASE + 90 )
#define IID_IPV4_SFIBC4_INTF_FIBA   ( IID_IPV4_BASE + 91 )
#define IID_IPV4_SFIBC4_INTF_SSA    ( IID_IPV4_BASE + 92 )
#define IID_IPV4_SFIBC4_INTF_CFG    ( IID_IPV4_BASE + 93 )


/* Begin: Added by A00903540 to support Distributed IP */
#define CID_IPV4_DISTIP                ( CID_IPV4_BASE + 0xA )
#define IID_DIP_INTF_FUN            ( IID_IPV4_BASE + 100 )
#define IID_DIP_INTF_CFG            ( IID_IPV4_BASE + 101 )
#define IID_DIP_INTF_SSA            ( IID_IPV4_BASE + 102 )
/* End: Added by A00903540 to support Distributed IP */

/* IPv4 and IPv6 Ping component */
#define CID_COMP_PING               ( CID_IPV4V6_BASE + 1 )

#define IID_COMP_PING_INTF_FUN      ( IID_IPV4V6_BASE + 10 )
#define IID_COMP_PING_INTF_CFG      ( IID_IPV4V6_BASE + 11 )
#define IID_COMP_PING_INTF_SSA      ( IID_IPV4V6_BASE + 12 )


/* IPv4 and IPv6 TraceRoute component */
#define CID_COMP_TRRT               ( CID_IPV4V6_BASE + 2 )

#define IID_COMP_TRRT_INTF_FUN      ( IID_IPV4V6_BASE + 20 )
#define IID_COMP_TRRT_INTF_CFG      ( IID_IPV4V6_BASE + 21 )
#define IID_COMP_TRRT_INTF_SSA      ( IID_IPV4V6_BASE + 22 )


/* IPv4 and IPv6 DNS Client component */
#define CID_COMP_DNSC               ( CID_IPV4V6_BASE + 3 )

#define IID_COMP_DNSC_INTF_FUN      ( IID_IPV4V6_BASE + 30 )
#define IID_COMP_DNSC_INTF_CFG      ( IID_IPV4V6_BASE + 31 )
#define IID_COMP_DNSC_INTF_SSA      ( IID_IPV4V6_BASE + 32 )


/* IPv4 and IPv6 Simple FIBAgent component, only using out of VRP */
#define CID_COMP_SFIBA              ( CID_IPV4V6_BASE + 4 ) 

#define IID_COMP_SFIBA_INTF_FUN     ( IID_IPV4V6_BASE + 40 )
#define IID_COMP_SFIBA_INTF_CFG     ( IID_IPV4V6_BASE + 41 )
#define IID_COMP_SFIBA_INTF_SSA     ( IID_IPV4V6_BASE + 42 )


/* IFNET component, only using out of VRP */
#define CID_COMP_IFNET              ( CID_IPV4V6_BASE + 5 ) 

#define IID_COMP_IFNET_INTF_FUN     ( IID_IPV4V6_BASE + 50 )
#define IID_COMP_IFNET_INTF_CFG     ( IID_IPV4V6_BASE + 51 )
#define IID_COMP_IFNET_INTF_SSA     ( IID_IPV4V6_BASE + 52 )
#define IID_COMP_IFNET_INTF_PUB     ( IID_IPV4V6_BASE + 53 )


/* Etherner&ARP protocol component, only using out of VRP */
#define CID_COMP_ETHARP             ( CID_IPV4V6_BASE + 6 )

#define IID_COMP_ETHARP_INTF_FUN    ( IID_IPV4V6_BASE + 60 )
#define IID_COMP_ETHARP_INTF_CFG    ( IID_IPV4V6_BASE + 61 )
#define IID_COMP_ETHARP_INTF_SSA    ( IID_IPV4V6_BASE + 62 )
#define IID_COMP_ETHARP_INTF_IFG    IID_COMP_IFNET_INTF_PUB


/* PPP protocol component, only using out of VRP */
#define CID_COMP_PPP                ( CID_IPV4V6_BASE + 7 )

#define IID_COMP_PPP_INTF_FUN       ( IID_IPV4V6_BASE + 70 )
#define IID_COMP_PPP_INTF_CFG       ( IID_IPV4V6_BASE + 71 )
#define IID_COMP_PPP_INTF_SSA       ( IID_IPV4V6_BASE + 72 )
#define IID_COMP_PPP_INTF_IFG       IID_COMP_IFNET_INTF_PUB



#define CID_COMP_ATK                ( CID_IPV4V6_BASE + 8 )

#define IID_COMP_ATK_INTF_FUN       ( IID_IPV4V6_BASE + 80 )
#define IID_COMP_ATK_INTF_CFG       ( IID_IPV4V6_BASE + 81 )
#define IID_COMP_ATK_INTF_IFG       IID_COMP_IFNET_INTF_PUB

/* Added by Sun Mo 44939 2005-09-21 */
#define CID_COMP_IPHC               ( CID_IPV4V6_BASE + 9 )

#define IID_COMP_IPHC_INTF_FUN      ( IID_IPV4V6_BASE + 90 )
#define IID_COMP_IPHC_INTF_CFG      ( IID_IPV4V6_BASE + 91 )
#define IID_COMP_IPHC_INTF_SSA      ( IID_IPV4V6_BASE + 92 )
/* End of add of Sun Mo 44939 2005-09-21 */


#define CID_COMP_POEC               ( CID_IPV4V6_BASE + 10)

#define IID_COMP_POEC_INTF_FUN      ( IID_IPV4V6_BASE + 100 )   
#define IID_COMP_POEC_INTF_CFG      ( IID_IPV4V6_BASE + 101 )   
#define IID_COMP_POEC_INTF_SSA      ( IID_IPV4V6_BASE + 102 )   


/*Component ID declaration for MP*/
#define CID_COMP_MP                 ( CID_IPV4V6_BASE + 11 )

/*interface IDs declaration*/
#define IID_COMP_MP_INTF_FUN        ( IID_IPV4V6_BASE + 111 )
#define IID_COMP_MP_INTF_CFG        ( IID_IPV4V6_BASE + 112 )
#define IID_COMP_MP_INTF_SSA        ( IID_IPV4V6_BASE + 113 )

/* Component ID declaration for PPPMUX */
#define CID_COMP_PPPMUX             ( CID_IPV4V6_BASE + 12 )

/*interface IDs declaration*/
#define IID_COMP_PPPMUX_INTF_FUN    ( IID_IPV4V6_BASE + 121 )
#define IID_COMP_PPPMUX_INTF_CFG    ( IID_IPV4V6_BASE + 122 )
#define IID_COMP_PPPMUX_INTF_SSA    ( IID_IPV4V6_BASE + 123 )


/* Component ID declaration for TRUNK */
#define CID_COMP_TRUNK              ( CID_IPV4V6_BASE + 13 )

/*interface IDs declaration*/
#define IID_COMP_TRUNK_INTF_FUN     ( IID_IPV4V6_BASE + 131 )
#define IID_COMP_TRUNK_INTF_CFG     ( IID_IPV4V6_BASE + 132 )
#define IID_COMP_TRUNK_INTF_SSA     ( IID_IPV4V6_BASE + 133 )

/* Component ID declaration for POES */
#define CID_COMP_POES             ( CID_IPV4V6_BASE + 14 )

/*interface IDs declaration*/
#define IID_COMP_POES_INTF_FUN   ( IID_IPV4V6_BASE + 141 )
#define IID_COMP_POES_INTF_CFG   ( IID_IPV4V6_BASE + 142 )
#define IID_COMP_POES_INTF_SSA   ( IID_IPV4V6_BASE + 143 )

/* Component ID declaration for DHCP4R */
#define CID_COMP_DHCP4R             ( CID_IPV4V6_BASE + 15 )

/*interface IDs declaration*/
#define IID_COMP_DHCP4R_INTF_FUN    ( IID_IPV4V6_BASE + 151 )
#define IID_COMP_DHCP4R_INTF_CFG    ( IID_IPV4V6_BASE + 152 )
#define IID_COMP_DHCP4R_INTF_SSA    ( IID_IPV4V6_BASE + 153 )

/* Component ID declaration for OSICP */
#define CID_COMP_OSICP             ( CID_IPV4V6_BASE + 16 )

/*interface IDs declaration*/
#define IID_COMP_OSICP_INTF_FUN    ( IID_IPV4V6_BASE + 161 )
#define IID_COMP_OSICP_INTF_CFG    ( IID_IPV4V6_BASE + 162 )
#define IID_COMP_OSICP_INTF_SSA    ( IID_IPV4V6_BASE + 163 )


/* Component ID declaration for OAM3AH */
#define CID_COMP_OAM3AH             ( CID_IPV4V6_BASE + 17 )

/*interface IDs declaration*/
#define IID_COMP_OAM3AH_INTF_FUN    ( IID_IPV4V6_BASE + 171 )
#define IID_COMP_OAM3AH_INTF_CFG    ( IID_IPV4V6_BASE + 172 )
#define IID_COMP_OAM3AH_INTF_SSA    ( IID_IPV4V6_BASE + 173 )

/* Component ID declaration for OAM1AG */
#define CID_COMP_OAM1AG             ( CID_IPV4V6_BASE + 18 )

/*interface IDs declaration*/
#define IID_COMP_OAM1AG_INTF_FUN    ( IID_IPV4V6_BASE + 181 )
#define IID_COMP_OAM1AG_INTF_CFG    ( IID_IPV4V6_BASE + 182 )
#define IID_COMP_OAM1AG_INTF_SSA    ( IID_IPV4V6_BASE + 183 )
/* Component ID declaration for IGMP */
#define CID_COMP_IGMP            ( CID_IPV4V6_BASE + 21 )

/*interface IDs declaration*/
#define IID_COMP_IGMP_INTF_FUN    ( IID_IPV4V6_BASE + 211 )
#define IID_COMP_IGMP_INTF_CFG    ( IID_IPV4V6_BASE + 212 )
#define IID_COMP_IGMP_INTF_SSA    ( IID_IPV4V6_BASE + 213 )

/* VISPV1R7C03 */
/* Component ID declaration for L2IF */
#define CID_COMP_L2IF             ( CID_IPV4V6_BASE + 22 )

/*interface IDs declaration*/
#define IID_COMP_L2IF_INTF_FUN    ( IID_IPV4V6_BASE + 221 )
#define IID_COMP_L2IF_INTF_CFG    ( IID_IPV4V6_BASE + 222 )
#define IID_COMP_L2IF_INTF_SSA    ( IID_IPV4V6_BASE + 223 )

/* Component ID declaration for VRRP */
#define CID_COMP_VRRP             ( CID_IPV4V6_BASE + 23 )
/*interface IDs declaration*/
#define IID_COMP_VRRP_INTF_FUN    ( IID_IPV4V6_BASE + 231 )
#define IID_COMP_VRRP_INTF_CFG    ( IID_IPV4V6_BASE + 232 )
#define IID_COMP_VRRP_INTF_SSA    ( IID_IPV4V6_BASE + 233 )

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/* Component ID declaration for IGMP */
#define CID_COMP_VRF            ( CID_IPV4V6_BASE + 24 )

/*interface IDs declaration*/
#define IID_COMP_VRF_INTF_FUN    ( IID_IPV4V6_BASE + 241 )
#define IID_COMP_VRF_INTF_CFG    ( IID_IPV4V6_BASE + 242 )
#define IID_COMP_VRF_INTF_SSA    ( IID_IPV4V6_BASE + 243 )
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define CID_COMP_SYNCE            ( CID_IPV4V6_BASE + 25)

/*interface IDs declaration*/
#define IID_COMP_SYNCE_INTF_FUN    ( IID_IPV4V6_BASE + 251 )
#define IID_COMP_SYNCE_INTF_CFG    ( IID_IPV4V6_BASE + 252 )
#define IID_COMP_SYNCE_INTF_SSA    ( IID_IPV4V6_BASE + 253 )

/*���ͬNSR��ص����ID*/
#define CID_COMP_NSR                  ( CID_IPV4V6_BASE + 26 )

/*interface IDs declaration*/
#define IID_COMP_NSR_INTF_FUN    ( IID_IPV4V6_BASE + 261 )
#define IID_COMP_NSR_INTF_CFG    ( IID_IPV4V6_BASE + 262 )
#define IID_COMP_NSR_INTF_SSA    ( IID_IPV4V6_BASE + 263 )


/*====================IPV6���CID/IID=============================*/

/* Component ID declaration for PPMNG  */
#define CID_IPV6_PPMNG              (CID_VISP_IPV6_BASE)

/* Interface IDs declaration */
#define IID_IPV6_PPMNG_INTF_CFG     (IID_VISP_IPV6_BASE)    
#define IID_IPV6_PPMNG_INTF_SSA     (IID_VISP_IPV6_BASE + 1)  
#define IID_IPV6_PPMNG_INTF_FUN     (IID_VISP_IPV6_BASE + 2)


/* IPv6 Socket component */
#define CID_IPV6_SOCKET6            (CID_VISP_IPV6_BASE + 1)

#define IID_IPV6_SOCKET6_INTF_FUN   (IID_VISP_IPV6_BASE + 10)
#define IID_IPV6_SOCKET6_INTF_CFG   (IID_VISP_IPV6_BASE + 11)
#define IID_IPV6_SOCKET6_INTF_SSA   (IID_VISP_IPV6_BASE + 12)


/* IPv6 Simple FIB Container component, only using out of VRP*/
#define CID_IPV6_SFIBC6             (CID_VISP_IPV6_BASE + 2 ) 

#define IID_IPV6_SFIBC6_INTF_FUN    (IID_VISP_IPV6_BASE + 20)
#define IID_IPV6_SFIBC6_INTF_FIBA   (IID_VISP_IPV6_BASE + 21)
#define IID_IPV6_SFIBC6_INTF_SSA    (IID_VISP_IPV6_BASE + 22)
#define IID_IPV6_SFIBC6_INTF_CFG    (IID_VISP_IPV6_BASE + 23)

/* VRF6 Component*/
#define CID_IPV6_VRF6            ( CID_VISP_IPV6_BASE + 3 )

#define IID_IPV6_VRF6_INTF_FUN   ( IID_VISP_IPV6_BASE + 30 )
#define IID_COMP_VRF6_INTF_FUN    ( IID_VISP_IPV6_BASE + 30 )
#define IID_COMP_VRF6_INTF_CFG    ( IID_VISP_IPV6_BASE + 31 )
#define IID_COMP_VRF6_INTF_SSA    ( IID_IPV4V6_BASE + 32 )


/*==============================================================*/

/*******************************************************
                    MID
  ģ��ID(��MID)��Ҫ�����������ڴ桢ע����Ϣ���С�ע�������еȵ�ʱ
  �����ָ���ģ�顣VISP��Ŀ��ģ��ID����������Ϊ��MID_COMP_ģ����
  MIDȡֵ������ULONG�ĸ�2���ֽ�.
  
  ע��VISP��Ŀ��MID������VRPV5������ģ���MID��ͻ, ��vos_id.h��
        ����VISP��Ŀ��MID�ڴ˴�����
*******************************************************/
#define MID_COMP_BASE               0x0E000000   /*VISP���ֶ����MIDֵ*/
#define MID_COMP_BASE6              0x0E800000   /*IR��IPV6�����MIDֵ*/


/* �����޸�ģ����.�������MID,��ÿ��MID�ĵ�����λ��0x00010000,�޸���Ҫͬ���޸�TCPIP_MidInfo_IPV4�ַ�����Ϣ */
#define MID_COMP_PING               ( MID_COMP_BASE + 0x00010000 )
#define MID_COMP_TRRT               ( MID_COMP_BASE + 0x00020000 )
#define MID_COMP_DNSC               ( MID_COMP_BASE + 0x00030000 )
#define MID_COMP_DHCPC4             ( MID_COMP_BASE + 0x00040000 )
#define MID_COMP_SOCKET             ( MID_COMP_BASE + 0x00050000 )
#define MID_COMP_TCP4               ( MID_COMP_BASE + 0x00060000 )
#define MID_COMP_UDP4               ( MID_COMP_BASE + 0x00070000 )
#define MID_COMP_RAWIP4             ( MID_COMP_BASE + 0x00080000 )
#define MID_COMP_ICMP4              ( MID_COMP_BASE + 0x00090000 )
#define MID_COMP_PP4                ( MID_COMP_BASE + 0x000a0000 )
#define MID_COMP_AM4                ( MID_COMP_BASE + 0x000b0000 )
#define MID_COMP_SFIB               ( MID_COMP_BASE + 0x000c0000 )
#define MID_COMP_IFNET              ( MID_COMP_BASE + 0x000d0000 )
#define MID_COMP_ETHARP             ( MID_COMP_BASE + 0x000e0000 )
#define MID_COMP_PPP                ( MID_COMP_BASE + 0x000f0000 )
#define MID_COMP_ACL4               ( MID_COMP_BASE + 0x00100000 )
#define MID_COMP_ATTACK             ( MID_COMP_BASE + 0x00110000 )
#define MID_COMP_SECMAIN            ( MID_COMP_BASE + 0x00120000 )
#define MID_COMP_SECSTAT            ( MID_COMP_BASE + 0x00130000 )
#define MID_COMP_WAITLIST           ( MID_COMP_BASE + 0x00140000 )
#define MID_COMP_COM                ( MID_COMP_BASE + 0x00150000 )
#define MID_COMP_FIBA               ( MID_COMP_BASE + 0x00160000 )
#define MID_COMP_FIBC4              ( MID_COMP_BASE + 0x00170000 )
#define MID_COMP_PPP_STAC           ( MID_COMP_BASE + 0x00180000 )
#define MID_COMP_PPP_STAC_HASH      ( MID_COMP_BASE + 0x00190000 )
#define MID_COMP_PPP_VJCOMP         ( MID_COMP_BASE + 0x001a0000 )
#define MID_COMP_IPHC               ( MID_COMP_BASE + 0x001b0000 )
#define MID_COMP_PPPOE_CLIENT       ( MID_COMP_BASE + 0x001c0000 )
#define MID_COMP_MP                 ( MID_COMP_BASE + 0x001d0000 )
#define MID_COMP_PPPMUX             ( MID_COMP_BASE + 0x001e0000 )
#define MID_COMP_PUBLIC             ( MID_COMP_BASE + 0x001f0000 )
#define MID_COMP_TRUNK              ( MID_COMP_BASE + 0x00200000 )
#define MID_COMP_HA                 ( MID_COMP_BASE + 0x00210000 )
#define MID_COMP_BFD                ( MID_COMP_BASE + 0x00220000 )
#define MID_COMP_POES               ( MID_COMP_BASE + 0x00230000 )
#define MID_COMP_DHCP4R             ( MID_COMP_BASE + 0x00240000 )
#define MID_COMP_OSICP              ( MID_COMP_BASE + 0x00250000 )
#define MID_COMP_MBUF               ( MID_COMP_BASE + 0x00260000 )
#define MID_COMP_GADS               ( MID_COMP_BASE + 0x00270000 )
#define MID_COMP_OAM3AH             ( MID_COMP_BASE + 0x00280000 )
#define MID_COMP_OAM1AG             ( MID_COMP_BASE + 0x00290000 )
#define MID_COMP_IGMP               ( MID_COMP_BASE + 0x002a0000 )

#define MID_COMP_DCL                ( MID_COMP_BASE + 0x002b0000 )
#define MID_COMP_I3AGENT            ( MID_COMP_BASE + 0x002c0000 )
#define MID_COMP_MIB                ( MID_COMP_BASE + 0x002d0000 )
#define MID_COMP_RIP                ( MID_COMP_BASE + 0x002e0000 )
#define MID_COMP_OSPF               ( MID_COMP_BASE + 0x002f0000 )
#define MID_COMP_RTM                ( MID_COMP_BASE + 0x00300000 )
#define MID_COMP_DIAGNOSE           ( MID_COMP_BASE + 0x00310000 )
#define MID_COMP_RTP                ( MID_COMP_BASE + 0x00320000 )
#define MID_COMP_VLINK              ( MID_COMP_BASE + 0x00330000 )
#define MID_COMP_IPOA               ( MID_COMP_BASE + 0x00340000 )
#define MID_COMP_VLAN               ( MID_COMP_BASE + 0x00350000 )
#define MID_COMP_BFDEXT             ( MID_COMP_BASE + 0x00360000 )
#define MID_COMP_PTP                ( MID_COMP_BASE + 0x00370000 )
#define MID_COMP_L2IF               ( MID_COMP_BASE + 0x00380000 )

/* VISPV1R7C03,Ϊ֧��NP�·�ʧ�ܶ���֪ͨ������ģ��ID, ע��: ��IDֻ����L2IFģ��NP�·�ʧ��֪ͨ */
#define MID_COMP_L2IF_VLAN          ( MID_COMP_L2IF + 0x1000 )
#define MID_COMP_L2IF_PORT          ( MID_COMP_L2IF + 0x2000 )
#define MID_COMP_L2IF_MAC           ( MID_COMP_L2IF + 0x3000 )
#define MID_COMP_L2IF_QINQ          ( MID_COMP_L2IF + 0x4000 )

#define MID_COMP_MSTP               ( MID_COMP_BASE + 0x00390000 )
#define MID_COMP_VRRP               ( MID_COMP_BASE + 0x003a0000 )

#define MID_COMP_VRF                ( MID_COMP_BASE + 0x003b0000 )
/* Added by hanna55555, VISPV1R8C01 for ACL6, 2009/4/8 */
#define MID_COMP_ACL6               ( MID_COMP_BASE + 0x003c0000 )
/*End of Added by hanna55555, 2009/4/8 */
#define MID_COMP_OSPFV3             ( MID_COMP_BASE + 0x003d0000 )
#define MID_COMP_RIPNG              ( MID_COMP_BASE + 0x003e0000 )

#define MID_COMP_BLS                ( MID_COMP_BASE + 0x003f0000 )
#define MID_COMP_WLS                ( MID_COMP_BASE + 0x00400000 )
#define MID_COMP_FIREWALL           ( MID_COMP_BASE + 0x00410000 )

#define MID_COMP_GR                 ( MID_COMP_BASE + 0x00420000 )
#define MID_COMP_SYNCE              ( MID_COMP_BASE + 0x00430000 )

/*Start TWAMP addition*/
#define MID_COMP_TWAMP          ( MID_COMP_BASE + 0x00440000 )
/*END TWAMP addition*/

/*Start POLICYRT addition*/
#define MID_COMP_POLICYRT          ( MID_COMP_BASE + 0x00450000 )
/*END POLICYRT addition*/

/*NSR���ģ��ID*/
#define MID_COMP_NSR          ( MID_COMP_BASE + 0x00460000 )

/*LLDP�齨ģ��ID*/
#define MID_COMP_LLDP               ( MID_COMP_BASE + 0x00470000 )

/*Added by dutianyi00217007��for PTPV2*/
#define MID_COMP_PTPV2              ( MID_COMP_BASE + 0x00480000 )

/* Begin: Added by A00903540 to support Distributed IP */
#define MID_COMP_DISTIP               ( MID_COMP_BASE + 0x00490000 )
/* End: Added by A00903540 to support Distributed IP */

/* Added by a00900892��on 03-08-2014 for IP attack statistics module. */
#define MID_COMP_ATK                ( MID_COMP_BASE + 0x004A0000 )

/* Added by LY(57500) for A82D13999, IRģ��IDʹ��VISPͳһ�ṩ��ģ��ID, �޸���Ҫͬ���޸�TCPIP_MidInfo_IPV6*/
#define MID_COMP_PPMNG              ( MID_COMP_BASE6 + 0x00000000 )
#define MID_COMP_SOCK6              ( MID_COMP_BASE6 + 0x00010000 )
#define MID_COMP_FIBC6              ( MID_COMP_BASE6 + 0x00020000 ) 
#define MID_COMP_TCP6               ( MID_COMP_BASE6 + 0x00030000 )
#define MID_COMP_ADDRMNG            ( MID_COMP_BASE6 + 0x00040000 )
#define MID_COMP_ICMP6              ( MID_COMP_BASE6 + 0x00050000 )
#define MID_COMP_ND                 ( MID_COMP_BASE6 + 0x00060000 )
#define MID_COMP_RIP6               ( MID_COMP_BASE6 + 0x00070000 )
#define MID_COMP_UDP6               ( MID_COMP_BASE6 + 0x00080000 )
#define MID_COMP_PMTU               ( MID_COMP_BASE6 + 0x00090000 )
#define MID_COMP_DHCP6C             ( MID_COMP_BASE6 + 0x000a0000 )
#define MID_COMP_DHCP6R             ( MID_COMP_BASE6 + 0x000b0000 )
#define MID_COMP_IPSEC              ( MID_COMP_BASE6 + 0x000c0000 )
#define MID_COMP_IKE                ( MID_COMP_BASE6 + 0x000d0000 )
#define MID_COMP_UTIL               ( MID_COMP_BASE6 + 0x000e0000 )
#define MID_COMP_TWL                ( MID_COMP_BASE6 + 0x000F0000 )
#define MID_COMP_EAP                ( MID_COMP_BASE6 + 0x00100000 )

#define MID_COMP_VRF6                ( MID_COMP_BASE6 + 0x00200000 )

/*ע: �������޸�MIDʱ���뱣֤MID��ŵ�������, ������ͬ������TCPIP_MidInfo_EN*/

/* ���涨��MID_COMP_*** �ķ�ʽ��Ϊ����VISP����ģ��ID��ʽͳһ,������ʹ�õ�
*  MID_*** ��ʽ�Ǹ�IRʹ�õģ������ڲ�ʹ�õ������������
*  ע��: �����ⲿ�ֺ�ֻ�ڸ�IR��tcpip_id.hͷ�ļ��ж���,����VISP���õ�tcpip_id.h(�����ļ�)�ж��壬
*  ����visp����ʱ��Щ�����vos_id.h�ж���һ�£����±���ʱ��������warning
*/
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
/* End Add by LY(57500) for A82D13999, IRģ��IDʹ��VISPͳһ�ṩ��ģ��ID, 2007-4-18 */

/*******************************************************
                   Waitlist ID   
   VISP�����WAITLISTֵ��100��ʼ,��IR����ʱ��1000��ʼ 
********************************************************/
#define WAITLIST_COMP_BASE               100     /*����VISP WAITLIST�ռ�*/
#define WAITLIST_COMP_IR_BASE            1000    /*����IR WAITLIST�ռ�*/

/*Begin: Add by wan for VISPV1R7 Integration, 2008-05-15*/
#define WAITLIST_UNICASTADDR                    WAITLIST_COMP_IR_BASE + 1
/*End of addition by wn for VISPV1R7 Integration*/

/* VISP����ģ�����ж���Waitlist ID */
#define WAITLIST_COMP_ARP_ENTRY         ( WAITLIST_COMP_BASE + 1 )
#define WAITLIST_COMP_DNS_CACHE_S       ( WAITLIST_COMP_BASE + 2 )
#define WAITLIST_COMP_TYPE_VOS_RADIX    ( WAITLIST_COMP_BASE + 3 )
#define WAITLIST_COMP_SOCK_HEADCACHE    ( WAITLIST_COMP_BASE + 4 )
#define WAITLIST_COMP_AM4_Addr          ( WAITLIST_COMP_BASE + 5 )
#define WAITLIST_COMP_ACL               ( WAITLIST_COMP_BASE + 6 )
#define WAITLIST_COMP_PPP_INFO          ( WAITLIST_COMP_BASE + 7 )
#define WAITLIST_COMP_IFNET_CONFIG      ( WAITLIST_COMP_BASE + 8 )
#define WAITLIST_COMP_MP_USERINFO       ( WAITLIST_COMP_BASE + 9 )
#define WAITLIST_COMP_PPPMUX_INFO       ( WAITLIST_COMP_BASE + 10 )
#define WAITLIST_COMP_MTSOFT_MAINTYPE   ( WAITLIST_COMP_BASE + 11 )
#define WAITLIST_COMP_DEVICE_MAINTYPE   ( WAITLIST_COMP_BASE + 12 )
#define WAITLIST_COMP_DHCP_CFG_INFO     ( WAITLIST_COMP_BASE + 13 )
#define WAITLIST_COMP_DHCP_SESSION_INFO ( WAITLIST_COMP_BASE + 14 )
#define WAITLIST_COMP_POESCB            ( WAITLIST_COMP_BASE + 15 )
#define WAITLIST_COMP_DHCP4R_CFG_INFO   ( WAITLIST_COMP_BASE + 16 )
#define WAITLIST_COMP_MP_MPGROUP        ( WAITLIST_COMP_BASE + 17 )
#define WAITLIST_COMP_OAM3AH_PORTINFO   ( WAITLIST_COMP_BASE + 18 )
#define WAITLIST_COMP_L2IF_FDB          ( WAITLIST_COMP_BASE + 19 )
#define WAITLIST_COMP_L2TRANS           ( WAITLIST_COMP_BASE + 20 )
#define WAITLIST_COMP_ARPGUARD_DYNAMIC  ( WAITLIST_COMP_BASE + 21 )
#define WAITLIST_COMP_ARPGUARD_STATIC   ( WAITLIST_COMP_BASE + 22 )
#define WAITLIST_COMP_VRF               ( WAITLIST_COMP_BASE + 23 )
#define WAITLIST_COMP_ETHALAN           ( WAITLIST_COMP_BASE + 24 )
#define WAITLIST_COMP_SYNCE_IFINFO      ( WAITLIST_COMP_BASE + 25 )
#define WAITLIST_COMP_ETHVLAN_CONSISTENCY_WARNING_IFINFO      ( WAITLIST_COMP_BASE + 26 )
#define WAITLIST_COMP_IGMP_CONFIG      ( WAITLIST_COMP_BASE + 27)
#define WAITLIST_COMP_TWAMP_CTTRL_SESS (WAITLIST_COMP_BASE + 28)
#define WAITLIST_COMP_POLICY_ROUTE (WAITLIST_COMP_BASE + 29)

/* Add by c00902193, 2013-11-22, to support IPConflict get */
#define WAITLIST_COMP_ARP_IPCONFLICT (WAITLIST_COMP_BASE + 30)

/* Q0���� */
#define WAITLIST_COMP_SOCK_LISTENSOCKQ0 (WAITLIST_COMP_BASE + 31)
/* Q���� */
#define WAITLIST_COMP_SOCK_LISTENSOCKQ (WAITLIST_COMP_BASE + 32)


/**********************************************************
               DEBUG��Ϣ�����ͺ궨��
               VISP DEBUG��Ϣͳһ����Ϊ3���ȼ�
**********************************************************/
#define IC_INFO_LOG             1
#define IC_INFO_TRAP            2
#define IC_INFO_DEBUG           3

#define TCPIP_IC_INFO_LOG       1
#define TCPIP_IC_INFO_TRAP      2
#define TCPIP_IC_INFO_DEBUG     3

/* Wanghui add, D00645: Define length MACRO, to remove magic numbers */
#define LEN_4        4
#define LEN_8        8
#define LEN_16       16
#define LEN_32       32
#define LEN_64       64
#define LEN_128      128
#define LEN_192      192
#define LEN_256      256
#define LEN_512      512
#define LEN_1024     1024
#define LEN_2048     2048
#define LEN_4096     4096

/************************************************************
              VISPԤ���ò������Ͷ���
************************************************************/

typedef enum TCPIP_PRECONFIG_INFO_Etag
{
    /*һ���ӿ������̬ARP����������Ĭ��ֵ:512,������ֵ1~4096��*/
    ETH_MAX_STATIC_ARP,  /* 0 */

    /*һ���ӿ������̬ARP����������Ĭ��ֵ:256,������ֵ1~65536��*/
    ETH_MAX_DYNAM_ARP,   /* 1 */

    /*���·�ɱ�����Ŀ��Ĭ��ֵ:64,������ֵ1~1024��*/
    SFIB_SRM_ROUTE_NUM,  /* 2 */

    /*�Ƿ���IFNET�ϱ���VLINK��Ϣ�����ɶԶ�·�ɡ�Ĭ��ֵ:1,����������ֵ:0,������1,����*/
    SFIB_SRM_VLINK,      /* 3 */

    /*���·�ɱ�����Ŀ��Ĭ��ֵ:64,������ֵ1~1024��*/
    SFIB6_SRM_ROUTE_NUM, /* 4 */

    /*�Ƿ���IFNET�ϱ���VLINK6��Ϣ���ɶԶ�·�ɡ�Ĭ��ֵ:1,����������ֵ:0,������1,����*/
    SFIB6_SRM_VLINK,     /* 5 */

    /*Request���ĵ��ش�������Ĭ��ֵ:5,������ֵ1~10��*/
    PPP_CFG_CONFREQS,    /* 6 */

    /*����ȱʡͬ�첽ת���ַ�����Ĭ��ֵ:0xffffffff (���п����ֶ�ת��) */
    PPP_CFG_DEFAULT_ACCM,/* 7 */

    /*����ȱʡMRU��Ĭ��ֵ:1500,������ֵ46~2000��*/
    PPP_CFG_DEFAULT_MRU, /* 8 */

    /*����: ȱʡEcho��ʱʱ��(��λ: ����)��Ĭ��ֵ:10000,������ֵ:1~30000*/
    PPP_CFG_ECHO_TIMEOUT,/* 9 */

    /*PPP����Ƿ���ҪCHAP֧�֡�Ĭ��ֵ:0,����Ҫ��������ֵ:0,����Ҫ��1����Ҫ��*/
    PPP_CFG_NEED_CHAP,   /* 10 */

    /*����ȱʡ�Ƿ���ҪLCPЭ�̡�Ĭ��ֵ:1,��Ҫ��������ֵ:0,����Ҫ��1����Ҫ��*/
    PPP_CFG_NEED_LCP,    /* 11 */

    /*��һ��Э�̲��ɹ��Ժ��Ƿ�ȴ�һ��ʱ������ѭ��Э�̡�Ĭ��ֵ:1,��Ҫ��������ֵ:0,����Ҫ��1,��Ҫ��*/
    PPP_CFG_NEED_LOOPNEGO,/* 12 */

    /*����ȱʡ�Ƿ���ҪNCPЭ�̡�Ĭ��ֵ:1,��Ҫ��������ֵ:0,����Ҫ��1,��Ҫ��*/
    PPP_CFG_NEED_NCP,     /* 13 */

    /*PPP����Ƿ���ҪPAP֧�֡�Ĭ��ֵ:0,����Ҫ��������ֵ:0,����Ҫ��1,��Ҫ��*/
    PPP_CFG_NEED_PAP,     /* 14 */

    /*����: һ��Э�̵ĳ�ʱʱ��(��λ: ����)��Ĭ��ֵ:6000,������ֵ:1~30000*/
    PPP_CFG_NEGO_TIMEOUT, /* 15 */

    /*һ�����нڵ����PPP���ƿ���, һ����ӿ�����ͬ��Ĭ��ֵ:64,������ֵ1~4096*/
    PPP_CFG_MAX_CTLNUM,   /* 16 */

    /*PPPģ���ʼ��ʱ�Ƿ񴴽��첽���Ķ��У�Ĭ��ֵ:PPP_NO_ASYQUE(��),
    ������ֵ:PPP_NO_ASYQUE(��), PPP_NEED_ASYQUE(��Ҫ)*/
    PPP_CFG_NEED_ASYQUE,  /* 17 */

    /*����TCP��ʽ�����CIDֵ��Ĭ��ֵ:15,������ֵ:3-255*/
    PPP_CFG_TCP_SPACE,    /* 18 */

    /*���÷�TCP��ʽ�����CIDֵ��Ĭ��ֵ:15,������ֵ:3-65535*/
    PPP_CFG_NON_TCP_SPACE,/* 19 */

    /*�����Ƿ�Э��(Enhanced) RTP Compression��ѡ�Ĭ��ֵ:1��������ֵ:0,��Э�̣�1��Э��*/
    PPP_CFG_RTP_COMPRESSION,/* 20 */

    /*�����Ƿ�Э��ֻѹ��TCP/��TCP����ѹ����ѡ��*/
    /*Ĭ��ֵ:0��������ֵ:0��ѹ��ȫ������, 1��ֻѹ����TCP���ģ�2��ѹ��TCP���ģ�3��ȫ����ѹ��*/
    PPP_CFG_COMPRESS_TYPE,  /* 21 */

    /*���ò��ú���ѡ·����, ������ֵ: 0 ~ 5, Ĭ��ֵΪ1(ѡ�������ӵĵȼ�·����)��������ΧȡĬ��ֵ*/
    SFIB4_CFG_ROUTE_BALANCE,/* 22 */

    /*���ò��ú���ѡ·����, ������ֵ: 0 ~ 2, Ĭ��ֵΪ1(ѡ�������ӵĵȼ�·����)��������ΧȡĬ��ֵ*/
    SFIB6_CFG_ROUTE_BALANCE,/* 23 */

    /*���ձ���ʱ�Ƿ����뱾����ַ�ȽϵĿ��ء������ڽ��ձ������뱾����ַ���Ƚϣ�
     ����ͬ��ֱ���Ͻ�������㴦��Ĭ��ֵ:0(��)��������ֵ:0(��), 1(��)*/
    PP4_CFG_DIRECTLOOKUPIP, /* 24 */

    /*����:����3����ֵΪMBUF CACHE��head,DBD,DB��Ŀ,����ֵ������2��n�η�*/
    MBUF_CFG_HEAD_CACHE_NUM,/*Ĭ��ֵ128������ֵ��1��4096֮�䣬������ΧȡĬ��ֵ*/  /* 25 */
    MBUF_CFG_DBD_CACHE_NUM, /*Ĭ��ֵ128������ֵ��1��4096֮�䣬������ΧȡĬ��ֵ*/  /* 26 */
    MBUF_CFG_DB_CACHE_NUM,  /*Ĭ��ֵ128������ֵ��1��8192֮�䣬������ΧȡĬ��ֵ*/  /* 27 */

    /*�Ƿ��MBUF CACHE���й������ݻ��Ᵽ��, Ĭ��ֵ:1(��)��������ֵ:0,��; 1,��*/
    MBUF_CFG_CACHE_LOCK,    /* 28 */

    /*����TCPCB�Ƿ񻺴���һ���ͳ��ӿ���Ϣ��Ĭ��ֵ:1(��)��������ֵ:0,��1,��*/
    TCP4_CFG_NEED_CACHE,    /* 29 */

    /*SOCKRUN�������ȼ���ȡֵ��Χ1~255��Ĭ��ֵ100��*/
    SKT_TASK_SOCK_PRIO,     /* 30 */

    /*SOCKRUN�����ջ��С��ȡֵ��Χ8K~64K��Ĭ��ֵΪ16K��*/
    SKT_TASK_SOCK_STACKSIZE,/* 31 */

    /*ʵ�ֹ�����OSP�Ķ�������OSPʹ�ù������Լ���RMģ�飬����VISP SFIB��SimpleRM���ԡ�*/
    /*ʵ��SGSN�Ķ�̬·��Э������SGSN�û�ʹ��DCL RTMģ�飬����VISP SFIB��SimpleRM���ԡ�*/
    /*1 - ʹ��VISP SimpleRMģ�飬 0 - ʹ�ù������RMģ�飬2 - ʹ��DCL RTMģ�顣Ĭ��ֵΪ1����ʹ��VISP SimpleRM��*/
    SFIB_SRM_CFG_ENABLE,    /* 32 */

    /*�Ƿ���Ҫʹ�õ���������ȡֵ:VRP_YES(��Ҫ)��VRP_NO(����Ҫ).Ĭ��ֵ:VRP_NO*/
    TCPIP_CFG_NEED_SWITCHTASK, /* 33 */

    /*��������������ȼ�,ȡֵ:VOS_T_PRIORITY_IDLE��VOS_T_PRIORITY_ABOVE_NORMAL��Ĭ��ΪVRP_TASK_DELAY_PRIO*/
    TCPIP_CFG_SWITCHTASK_PRIOR,/* 34 */

    /*�Ƿ�ʹ��ȫ��SOCKET, ȡֵ:1-ʹ��, 0-��ʹ��; Ĭ��ֵ: VRP_YES(ʹ��)*/
    SKT_GLOBAL_SOCKET_EN,      /* 35 */

    /*�Ƿ�ʹ��TCP���ʹ����Ż�, ȡֵ:1-ʹ��, 0-��ʹ��; Ĭ��ֵ: VRP_NO(��ʹ��)*/
    TCP4_OUTPUT_OPTIMIZE,      /* 36 */

    /*ʵ�ֹ����綨�������Ƿ�ʹ��˫OSPF���ԣ�ȡֵ: 1-ʹ�ܣ�0-��ʹ�ܣ�Ĭ��ֵ:VRP_NO(��ʹ��) */
    RAWIP_DOUBLE_OSPF,         /* 37 */

    /*�Ƿ���Ҫʹ��MPQOS��ȡֵ:VRP_YES(��Ҫ)��VRP_NO(����Ҫ)��Ĭ��ֵ:VRP_NO*/
    TCPIP_CFG_NEED_MPQOS,      /* 38 */

    /*�Ƿ�ʹ��IP���е����Ż���ȡֵ:0-��ʹ��, 1-ʹ��; Ĭ��ֵ: 0 */
    ETH_IPINPUT_OPTIMIZE,      /* 39 */

    /*�Ƿ�ʹ��UDP���������Ż���ʹ�ܺ󽫲�֧�ֿ��DHCP Relay, ȡֵ:0-��ʹ��, 1-ʹ��; Ĭ��ֵ: 0 */
    UDP4_OUTPUT_OPTIMIZE,      /* 40 */

    /*����ģ��ʹ��HA����:0-��ʹ�ܣ�1:ʹ�ܻ���ģ�飬2:ʹ��ETHģ�飬4:ʹ��PPPģ��......0xffffffff-ʹ��ȫ��ģ��HA���� */
    TCPIP_NEED_ENABLE_HA,      /* 41 */ 

    /*HA�Ƿ񱸷ݶ�̬ARP���1-���ݣ�0-������*/
    ETHARP_HA_DYNA_ARP,        /* 42 */

    /*�ӿ�physical��ַ�����÷�ʽ��0-�������ARP,1-ֱ������(����һ�£���������Ч),2-����һ�£����ݺ�������Ч */
    ETHARP_HA_SETMAC_METHOD,   /* 43 */

    /*Add for UDP6&RawIP6 source cache,0-��ʹ��,1-ʹ��, Ĭ��ֵ:0*/
    IPV6_IR_HEADCACHE,         /* 44 */

    /*Add for TCP6 next-hop and output interface cache,0-��ʹ��,1-ʹ��, Ĭ��ֵ:0*/
    TCP6_CFG_NEED_CACHE,       /* 45 */

    /*Add for TCP6 output optimize,0-��ʹ��,1-ʹ��, Ĭ��ֵ:0*/
    TCP6_OUTPUT_OPTIMIZE,      /* 46 */

    /* Trunkģ��ϵͳ���ȼ� */
    TRUNK_SYS_PRI,             /* 47 */
    
    /* DHCP4Rʹ������ģʽ, 0-�ӿ�ģʽ��1-ȫ��ģʽ ,2-�������Զ�ģʽ */
    DHCP4R_CFG_MODE,          /* 48 */

    /* ·�ɱ��·�NPģʽ,1-�·�����,0-ȫ����,Ĭ��Ϊ0*/
    SFIB_NP_UPDATEMODE,              /* 49 */
    
    /* IPHC�Ƿ���NPģʽ,1-NPģʽ,0-��NPģʽ Ĭ��Ϊ0*/
    PPP_CFG_IPHC_NP_SWITCH, /* 50 */

    TCPIP_ENABLE_CACHEDPKT,          /* 51 ���Ļ��湦�� 0-��ʹ��,1-ʹ��, Ĭ��ֵ:1*/
    
    SFIB_ROUTE_SUBNET_BROADCAST,     /* 52 �����㲥·�ɣ�0-��ʹ�ܣ�1-ʹ�ܣ�Ĭ��ֵ:0*/

    /* �Ƿ�Э��OSICPֱ���ϱ�UP,1Э��,0��Э�� */
    PPP_CFG_NEED_OSICP,              /* 53 */

    /* �Ƿ�ʹ��HA�������� 0-��ʹ��, 1-ʹ��, Ĭ��ֵ:0 */
    TCPIP_ENABLE_HA_UPDATE,          /* 54 */

    /* 3ah npģʽ */
    OAM3AH_NP_MODE,                  /* 55 3AH NPģʽ,0-VISP���ģʽ,1-��NP,2-ȫNP */   
    
    OAM1AG_NP_MODE,                  /*56,1ag np ģʽ,0-���ģʽ,1-��NPģʽ,2-ȫNPģʽ*/
    
    IF_CFG_3DIMENSION_ENABLE,        /*57���ýӿ�ά����0-һά�ӿڣ�1-�ֲ�ʽ3ά�ӿڣ�2-����ʽ��ά�ӿڣ�Ĭ��ֵΪ0*/

    PPP_CFG_IPHC_UNIDIRECTION,       /* 58, �Ƿ�֧��IPHC������ 0-��ʹ��, 1-ʹ��, Ĭ��ֵ:0*/

    IGMP_CFG_IFS_NUMS,               /* 59, ÿ���ӿڼ���Ķಥ��ﵽ�����ʱ��֧������IGMP�Ľӿ��ܸ��� */

    IF_CFG_MULTIGRP_NUMS,            /* 60, һ���ӿ����öಥ��ĸ���*/

    /*DHCP Client��ַ����ģʽ*/
    DHCP4C_ADDR_CFG_MODE,            /*61  0��DHCP CLient��ȡ��ַ����Ϊ��ͬ����; 1������Ϊ��ͬ����*/

    PTP_CFG_TASK_PRI,                /*62, PTP�������ȼ�,Ĭ��100,��Χ0~255*/

    PTP_CFG_DEV_TYPE,                /*63, PTPʱ���豸����,Ĭ��0,��Χ0~5: 0-OC,1-E2ETC,2-P2PTC,3-OC+E2ETC,4-OC+P2PTC,5-BCĿǰ��֧��,Ϊ����*/

    PTP_CFG_SOFT_MODE,               /*64, PTPʱ����������ģʽ,Ĭ��1: 0-����ģʽ,1-PTP���� FPGAͬ��ģʽ*/

    OAM3AH_LINKEVENT_FRAME_ACT,      /* 65  3AH ��֡���֡��ʵ�ַ�ʽ; 0-VISPʵ��; 1-���(NP/����)ʵ��; Ĭ��ֵ 0 */
    /*ETHARP ��ַ��ͻ��⴦��ģʽ,Ĭ��Ϊ0*/
    ETHARP_IP_CONFLICT_MODE,        /*66  0�����ⲿģ�鴦��(������ͨ��TCPIP_RegFuncDealIpConflictHookע��);
                                          1����VISP���д���; */
    PPP_CHAP_CLIENT_CHECKUSER,      /*67 Chap Client���Ƿ���֤Server���͹�����USER NAME 0:����֤  1:��֤, Ĭ��Ϊ0 */                                      

    /* 3AH ��֡�����¼�����ֵ����ģʽ;ȡֵ����:
       0-���õĴ�֡�����¼��Ĵ���ֵΪʱ��ֵ,�·���������,����������Ϊ��ʱ���ڵ���С�ߴ�֡��Ŀ��Ϊ��֡�����¼��Ĵ���ֵ; 
       1-���õĴ�֡�����¼��Ĵ���ֵΪ֡��Ŀ,����һ��ʱ���������ܹ����յ���С�ߴ�֡��Ŀ; 
       Ĭ��ֵ:0   */
    OAM3AH_ERR_FRMPRD_EVENT_SETMODE,      /* 68 */

    /* 3AH ������������¼�����ֵ����ģʽ;ȡֵ����:
   0-���õĴ�����������¼��Ĵ���ֵΪʱ��ֵ,�·���������,����������Ϊ��ʱ�����ܽ��յķ�������Ϊ������������¼��Ĵ���ֵ; 
   1-���õĴ�����������¼��Ĵ���ֵΪ������,����һ��ʱ���������ܹ����յķ�����; 
   Ĭ��ֵ:0   */
    OAM3AH_ERR_SYMPRD_EVENT_SETMODE,      /* 69 */

    DCL_DIAG_MOMORY_TRACE,           /* 70 �Ƿ�ʹ��DCL�ṩ���ڴ�׷�ٹ��ܣ�Ĭ�ϲ�ʹ�ܡ�
                                        �˹��ܿ��Լ�¼DCL�и�ģ����ڴ����ʹ����� */
    VLINK_ROUTE_PRIORITY,            /* 71 Ԥ����VLINK·�ɵ����ȼ�,Ĭ��ֵΪ0,ȡֵ��ΧΪ0--255 */

    IPC_ROUTE_CFG_ENABLE,           /* 72 ֧��IPC·���·�ʧЧ��ʹ�����ã�Ĭ��ֵΪ0-��ʹ�ܣ�ȡֵ��Χ0--1*/

    RTM_CFG_ATM_TYPE,                    /* 73 ATM�ӿ����͵ľ�̬·��ʹ�����ã�Ĭ��ֵΪ0-��ʹ�ܣ�ȡֵ��Χ0--1*/

    IPC_VLINK_ROUTE_NOTIFY_ENABLE,  /* 74 ֧��VLINK·���ϱ�֪ͨDCL,Ĭ��ֵΪ0-��ʹ�ܣ�ȡֵ��Χ0--1*/
    
    L2IF_CFG_ML_NUM,                /* 75 L2IF ML��Ŀ,Ĭ��4096��������0-16k */
    L2IF_CFG_STATIC_FDB_NUM,        /* 76 L2IF ��̬FDB������Ŀ,Ĭ��128,������0-1024 */

    NCP_NEED_MP_HEAD,                /* 77,NCP�����Ƿ���Ҫ��װMPͷ����Ĭ��Ϊ1��������װMPͷ����0��ʾ����װMPͷ��*/
    
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    VRF_CFG_MAX_INSTANCE_NUM,       /* 78 ���VRFʵ��������Ĭ��ֵΪ1��ȡֵ��Χ1~1024��*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /* VISP1.8.1 ֧��1AG��׼Э�鿪��*/
    OAM1AG_DEFAULT_VERSION,          /* 79 1AGĬ��ʹ�õİ汾��, ȡֵ��Χ:0~1��0 : ��ʾʹ��Draft7�汾��1AGЭ��; 1��ʾʹ�ñ�׼�汾��1AGЭ��. Ĭ��ֵΪ0,��Draft7  */
    
    /*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/7 */
    BFD_IPV6_ENABLE,                 /* 80,Ĭ�ϲ�ʹ��IPv6 BFD, 0--��ʹ��,1---ʹ��*/
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/7 */
    
    ETH_ARP_NOTNET_REPLY,           /* 81 ETHARP���ظ���ͬ���ε�ARP����,ȱʡ��Ӧ0�������ò���Ӧ1 */
    PPPMUX_NP_MODE,                 /* 82 ��NPģʽ�²�����PMUX����ȱʡ0������������Ϊ1������ */

    SFIB_UPDATE_FIB_NP_MODE,         /* 83 VISP·�ɱ����֪ͨNP·�ɸ��µ�ģʽ��0��ԭ��ģʽ��������ɾ��1������ģʽ����ɾ���� */

    ARP_GUARD_BLACK_EXPIRE_TIME,     /* 84,ARP�������ϻ�ʱ��,Ĭ��20����,ȡֵ��Χ5���ӵ�20���� */

    ETH_STATICARP_DOWNLOAD,          /* 85 ����(���ɾ������)��̬ARP�·�NP, 0-���·� 1-�·� Ĭ��ֵ0 */

    ETH_ARPMISS_NOTNET_TIMEOUT,      /* 86 �û��ϱ�ARP MISS,�����ַ�ͽӿڲ���ͬһ������Ԫ�ϻ�ʱ��, 0~300s,Ĭ����0,���ȴ���ʱ��ʱ�� */

    ETHARP_CHECK_PKT_SRCMAC,         /* 87 �Ƿ���ETH���ĵ�ԴMAC,1Ϊ���,0Ϊ�����,Ĭ��Ϊ1 , 2 :src mac will be checked inside ARP packet**/

    PPP_CFG_GLOBAL_TIMER,            /* 88,PPP��ʱ��ģʽ��ȱʡȫ��ģʽ1��������Ϊ����ģʽ0 */
    /* End of addition */

    SFIB6_NP_UPDATEMODE,              /* 89 ·�ɱ��·�NPģʽ,1-�·�����,0-ȫ����,Ĭ��Ϊ0*/
    SFIB6_UPDATE_FIB_NP_MODE,        /* 90 VISP·�ɱ����֪ͨNP·�ɸ��µ�ģʽ��0��ԭ��ģʽ��������ɾ��1������ģʽ����ɾ���� */

    /*Added by eswar*/
    /*Pre configuration IDs for firewall module*/
    FW_WLS_MAX_RULE,        /* 91 Maximum number of rules for whitelist*/

    FW_BLS_MAX_RULE,        /* 92 Maximum number of rules for blacklist*/

    FW_AD_IF_CFG_MAX_RULE,    /* 93 Maximum number of interface based attack rules*/

    FW_AD_FLOOD_CFG_MAX_RULE,    /* 94 Maximum number flood based atrack rules*/

    FW_ACLFW_MAX_IFINDEX,    /* 95 Maximum number interface indexes binding with acl group*/

    FW_ACL_RFC_MAX_MEM_USE,    /* 96 Maximum memory usage for acl rfc*/

    FW_ENABLE_MAC_BASE_ACL_FILTER,    /* 97 To enable/disable mac based acl filter*/
    /*End of addition*/

    /* Ϊ֧��RPU����Ӧ�ó������Ӹ�Ԥ���� */
    ETHARP_FREEARP_REPLY_UNICAST,            /* 98, �Ƿ�Ե�ַ��ͻ�����ARP���õ���Ӧ��ȱʡΪ0(�㲥)��1(����) */

    PPI_DOWNLOAD_MODE_FOR_SGSN,      /* 99 PPI�·�ģʽ,1ΪSGSNģʽ:BFD�Ựɾ��ʱֻ�·�BFD_PPI_USER_DELETE,
                                     ���·�BFD_PPI_SESSION_DELETE ; ��Ա�˿ڴ�Trunk�Ƴ�ʱ���������ϱ��澯
                                     0Ϊȱʡģʽ:BFD�Ựɾ��ʱ�·�BFD_PPI_USER_DELETE��BFD_PPI_SESSION_DELETE ;
                                     ��Ա�˿ڴ�Trunk�Ƴ�ʱ�������ϱ��澯*/
    

    TCPIP_SOCK_TIMER_QUE_LEN,        /* 100 ֧��Ԥ����SOCK����ʱ�����еĳ��� */
    PTP_IPV6_ENABLE,        /*101 ʹ��PTP IPv6��1: ʹ�ܣ�0: ȥʹ��*/
    SYNCE_DEFAULT_QL,                    /*102 ͬ����̫Ĭ������ֵ*/                                 
    TCP_SYN_USE_CONFIG_TOS,         /* 103 TCP��������ʱ����ʹ�öԶ˱�����Я����TOSֵ������ʹ�ñ������õ�TOSֵ */
    SOCK_RAND_PORT_ENHANCE,         /* 104 �Ż�SOCKET����˿ڵ����ɷ�ʽ */
    BFD_MULTI_HOP_TTL,
    BFD_TOTAL_SESSION_NUM,          /* 106  BFD total session number ȱʡΪ512~5120�����ݲ�Ʒ��Ҫ����*/
    OSPF_DEFUALT_COST,              /*107  OSPF �ӿ�Ĭ�� COSTֵ*/
    OSPF_DEFAULT_PRIORITY,          /*108  OSPF �ӿ�Ĭ�� DR���ȼ�*/
    PPP_IPCP_SUBOPTION_AUTO_ADAPT,    /*109  PPP IP-Compression-Protocol ��ѡ������ӦЭ��IPHC: 
                                          0��ʾ������ӦЭ��;1��ʾ����ӦЭ�̣������ڱ���δʹ��IPHC��ѡ��Э�̵��������Ч!! */
    TCPIP_TRACE_ROUTE_USE_DIP_FOR_SIP, /* 110 0:ICMP��Ӧ��Դ��ַ����ӿ���ƥ��ĵ�ַ��1:ICMP��Ӧ��Դ��ַ�ǽ��յ��ı��ĵ�Ŀ��IP*/
    TRUNK_NP_MODE,                  /*111 Lacp����ģʽ: 1,��NP�շ�lacp���ģ�0����Э��ջ�շ� */
    BFD_MAX_SESSION_NUM,            /*112  BFD�Ự�����չ1000~5120*/

    LLDP_CFG_TASK_PRI,              /*113  LLDP�������ȼ�,Ĭ��100,��Χ0~255*/

    SOCK_BIND_MAX_PORT,             /*114  socket  �˿ں����ֵԤ���ã�Ĭ��50000����Χ50000~65535*/
    OAM3AH_BOARD_STATE,             /* 115 �Ƿ�ʹ��3AH��ӿ�״̬�������� */
    TRUNK_LB_TONEUP,                /* 116 Trunk����·������ǿ  Ĭ��Ϊ0������ǿ ��Χ0��1*/
    ETHATRP_EXPIRE_UPDATEMODE,     /*117  Distinguish between main interface and sub interface for setting the expire time value and also the effect of the change on existing Arp entries
                                                    Range:[0,2] 0:Main-interface mode with affecting existing entries(SGSN) 1: Sub interface mode with affecting existing entries(HERT) 2: subinterface mode without affecting existing entries(MCCP)*/             
    TCPIP_HA_KEEPALIVE, /* 118 : 0(ȱʡֵ):������HAͨ�������, 1-5:����HAͨ������ܱ�������(s) */
    ETHIF_MAX_NUM,      /*119 �ɴ��������ӿ�����Ĭ��4096����Χ4096~65535*/
    ETHIF_UPDATE_TIMER_PERIOD,      /*120 ARP ��ʱ���������� ����Χ100~5000ms*/
    OAM1AG_CC_ENABLE_MODE,         /*121  ��?��??��0-1, ??��??a0:??���������????��   1 ???����?2aD����a�̣�?��????*/ 
    SKT_TASK_SOCK_LINUX_STACKSIZE, /* 122 linux??��???????�䨮D??�ꨨ??�̡�??��8K~16M��???��??��?a8M*/
    
    ETH_ARP_PPI_UPDATE_ON_REF,    /*123 Product has to use this key in pre-config if refreshed expire time and fake ARP entry has to be updated on NP using PPI*/

    ETHARP_EXPIRETIME,   /*124, Using this user can set the expiry time, Entry will not be deleted within this time if ARP Response is not recieved*/
    SUBIF_MAX_VIDNUM,   /* 125,Maximum VLAN ID */
    LINK_IO_CTL_QUEUE_LENGTH,
    ETHARP_ARP_PKTS_ONETIME,     /*127 ARP����һ�δ���ĸ�����Ĭ��40�������1000��*/
    LLDP_ADD_PORT_MODE,  /*128,�ṩԤ���ã������ɲ�Ʒ���ӿ���ӵ�LLDP�Ķ˿ڱ�Ĭ��VISP�ڴ����ӿ�ʱ�������,DTS*/
    ETHARP_MAX_SYS_DYNAM_ARP,    /*129 ����ϵͳ����̬APR���� */
    TCP_LAND_ATTACK_SWITCH,      /*130 TCP LAND���������أ�VRP_NO��ʾ�رգ�VRP_YES��ʾ�򿪣�Ĭ��VRP_NO:0 �ر�*/
    ETH_ARP_DEL_DELAY_TIME,      /* 131 �Ƿ�֧�ֽӿ�����down�ӳ�ɾ���ӿ��µ�ARP���� 0:��֧��;1-5:�ӳ�ʱ�� */
    /*Added by guojianjun178934, NSR����Ԥ������, 2012/11/26   ���ⵥ��:20121126_NSR_01 */
    NSR_OSPF_ENABLE,          /*132 �Ƿ�ʹ��OSPF NSR, 0-��ʹ��, 1-ʹ��, Ĭ��ֵ:0*/
    NSR_CFG_TASK_PRI,         /*133  NSR�������ȼ�,Ĭ��100,��Χ0~255*/
    /* End of Added by guojianjun178934, 2012/11/26   ���ⵥ��:20121126_NSR_01 */
    TRUNK_NSR_FEATURE,              /* 134 TRUNK NSR���Բü��� */
    BFD_NSR_FEATURE,                /* 135 BFD NSR���Բü��� */
    OAM1AG_MD_NUM,              /*136 �ڴ��Ż�֧��Ԥ����MD���� */
    OAM1AG_MA_NUM,              /*137 �ڴ��Ż�֧��Ԥ����MA���� */
    OAM1AG_MEP_NUM,             /*138 �ڴ��Ż�֧��Ԥ����MEP���� */
    OAM1AG_RMEP_NUM,            /*139 �ڴ��Ż�֧��Ԥ����RMEP���� */
    /* Added by c00902193, 2013/8/30  CHANDRA*/	
    PLC_ROUTE_MAX_POLICY_VRF,
    PLC_ROUTE_MAX_POLICY_NODE,
    /* End of Added by c00902193, 2013/8/30 */

    NSR_ENABLE,                 /*142 �Ƿ�ʹ��NSR, 0-��ʹ��, 1-ʹ��, Ĭ��ֵ:0*/
    /*Added by zhoushisong202096, ֧��MBUFԤ�����ȿ���չ, 2013/11/25 */
    MBUF_CFG_USER_RESERVE_SPACE,    /*143 ֧��MBUFԤ�����ȿ���չ��*/
    /* End of Added by zhoushisong202096, 2013/11/25 */
    TRUNK_IFNUM_MAX,                /*144 ֧�ֿ�����Trunk���ӿ���Ŀ��Ĭ��32����Χ32~128*/
    /*Added by fengjing209023, TCP4,6 cookie���� 2014/1/21 */
    TCP4_COOKIE_SWITCH,             /*145 TCP4 COOKIE���� */
    TCP6_COOKIE_SWITCH,             /*146 TCP6 COOKIE���� */
    /* End of Added by fengjing209023, 2014/1/21 */

    /*Added by fengjing209023, MAC���ܿ��� 2014/3/21 */
    MAC_CHANGE_IP6_STATE_SWITCH,    /*147 MAC���ܿ��� */  
    /*Added by fengjing209023, MAC���ܿ��� 2014/3/21 */

    IP6_DOWN_NO_PPI_DEL_ND,  /*148*/
    
    ETH_STATICARP_REF_DIFFNET,   /* 149 �ڲ�ʹ���ϸ�ѧϰ�ĳ����²�ͬ���ε�ARP�����Ƿ�ˢ�¾�̬ARP����(0 ˢ��ARP���� 1 ��ˢ��) */
    ARP_STRICT_LEARN_SWITCH_MODE, /* 150 ARP�ϸ�ѧϰȫ��ģʽ�ͽӿ�ģʽ���ÿ���(0ȫ��ģʽ 1�ӿ�ģʽ��Ĭ��0) */

    IPV4_ADDR_SUPPORT_32BITS_MASK_SWITCH, /* 151 IPV4��ַ֧��32λ���룬��֧��RTM·��ģʽ */

    /* Added by likaikun00213099 for IP same subnet support at 20140526 */
    IPV4_ADDR_SUPPORT_SAME_SUBNET, /* 152 IPV4��ַ֧�ֲ�ͬ�ӿ�ͬ���ε�ַ����(0 ��֧�� 1 ֧�֣�Ĭ�ϲ�֧��)
                                          cation:1.�����õ�ǰֻ֧��SRMģʽ,DCLģʽ�Բ�֧�֡�*/
    /* End of Added by likaikun00213099 for IP same subnet support at 20140526 */

    TCPIP_ICMP_REFLECT_SRCIP_WITH_DSTIP, /*153 CSECɨ�谲ȫ���⣬0:Ĭ��ֵ������ICMP��ӦԴIP����ȫ����;
                                                            1:��ICMP��ӦԴIP����ȫ������Դ��ַ
                                                              �ǽ��յ��ı��ĵ�Ŀ��IP */

    SKT_TASK_DHCP4R_PRIO,       /*154 DHCP4R�������ȼ�,Ĭ��ֵ:100,��Χ1~255*/
    /* Added end */

    SFIB_ROUTE_CACHE_SWITCH,    /*155 ·�ɻ��濪�أ�0-�رգ�1-�򿪣�Ĭ��ֵ:1*/
    /* Added end */

    IPV6_ND_NO_DAD_SWITCH,      /*156 ����DAD���أ�0-�رգ�1-�򿪣�Ĭ��ֵ:0 ��ǰֻ֧��������ģʽ */
    /* Added end */     

    /*���а汾Ԥ��������Ҫ����һ�£���ǰ�޸ģ���C10����������C20������*/
    /* Added by fengjing209023 for ȫ�ֶ�̬��������� */
    ARP_BLACKLIST_SYS_MAXNUM,
    /* Added end */    
    
    /* Added by likaikun00213099 for port security at 20140806 */
    BFD4_PORT_SHOW_SWITCH,      /*158 BFD�Ƿ������ʾ�˿ڣ�0-����ʾ��1-��ʾ��Ĭ��ֵ:1 ������ʾ */

    DHCP4R_PORT_OPEN_SWITCH,    /*159 DHCP4R�Ƿ���⿪���˿ڣ�0-��������1-������Ĭ��ֵ:1 ���⿪�� */

    PTP_PORT_OPEN_SPECIFIC_SWITCH,/*160 PTP�Ƿ���⿪���˿ڣ�0-��������1-������Ĭ��ֵ:1 ���⿪�� 
                                        CAUTION: ����Թ��� *specific */
    /* End of added by likaikun00213099 */

    /*tcp�첽��ϢsocketӦ��Ĭ�ϱ���ǰ�����*/
    SOCK_FIOASYNC_COMPLIANCE_SWITCH, /*161 TCP4/TCP6��socket�Ƿ�̳и�socket�첽��Ϣ���ԣ�0-�̳�; 1-���̳�; Ĭ��0�̳� */

    LLDP_INTERFACE_AND_NEIGBOR_MAX_NUM,         /*162 LLDP maximum supported interface */
    
    ETHARP_SWAP_POLICY_SWITCH, /*163 ARP���������µ�ԭ���滻����,Ĭ��Ϊ1������ԭ�е��滻����,0ʱ�ر��滻����*/

    IP_INPUT_TYPE,                  /*164 �ֲ�ʽsocket��IP���տ��� */
    
    ACLFW6_MAX_IFINDEX,         /*165 Maximum interface Index supported for acl6 firewall*/

    /* Added by Chandra 902193 for IPv6 same subnet support at 20140912 */
    IPV6_ADDR_SUPPORT_SAME_SUBNET,    /* 166 Set as 1 to support same subnet address on multiple interface */
    /* End of Added by Chandra 902193 for IPv6 same subnet support at 20140912 */

    /* Added by caiqizheng for S-IP-C20-005-VRF.001 */
    RTM_SCK_COM_SWITCH,    /*167 ��̬·��ģʽ��SCK����ü����أ�0-�رգ�1-�򿪣�Ĭ��ֵ:1*/
    /* Added end */

    /*Added by Upasi u84012585 to set DNS server timeout value passed by user, date 5/03/2015*/
    DNS_QUERY_TIMEOUT_VALUE,   /**< �����û�ָ����DNS�������˳�ʱʱ�䣬��λ�롣ȡֵ��Χ[1, 5]��Ĭ��ֵ5 */
    /* End */

    TCP_REASS_MAXSEG,   /* 169 TCP�����������Ŀ */
    TCPIP_MAX_COM_PARA_NUM           /* ö�ٱ߽�ֵ������Ԥ������ʱ�����ڴ�֮ǰ���� */

    /* ע��: ������޸�Ԥ����(������/ɾ����/�޸�ö����)ö��ֵ�������ͬ�� TCPIP_PreConfigKeyInfo_EN. */
}TCPIP_PRECONFIG_INFO_E;


#endif  /* end of _TCPIP_ID_H_ */

#ifdef  __cplusplus
}
#endif

