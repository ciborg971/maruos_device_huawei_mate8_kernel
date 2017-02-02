

#ifndef _TCPIP_CONFIG_H_
#define _TCPIP_CONFIG_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* Added by likaikun00213099 for Balong at 20140426 */
#ifndef TCPIP_FORBALONG
/*Modify 2008-08-26 liangjicheng  -Move dopra_def.h to head of this file. For V1R7C02*/
#include "dopra_def.h"
#endif
/* End of added by likaikun00213099 for Balong at 20140426 */

#ifdef TCPIP_DOPRA_V2
#include "vos_typdef.h"
#endif

#include "tcpip_id.h"

/*************************************************************************

              ������VISP����ͨ��Ʒ�ͷ���ͨ��Ʒ�������ṩ�ĺ�

**************************************************************************/

/************************************************************************************************
 * ע��汾�ű������, ����������ȡ�������, ����������仯, ��Ҫ��Ӧ���޸�HA�汾�ŵ����ɷ�ʽ
 * ��ʽ�汾�Ÿ�ʽΪ "VISP VxxxRxxxCxxBxxx" �� "VISP VxxxRxxxCxxBxxxSPCxxx";
 * Draft�汾�Ÿ�ʽΪ "VISP VxxxRxxxCxxBxxxDraftX���� "VISP VxxxRxxxCxxBxxxSPCxxxDraftX"��
 * ����x,X��Ϊ���������֣�Ӣ����ĸ���ִ�Сд��
 ************************************************************************************************/
#define TCPIP_HA_VERSION "VISP V100R008C06SPC001B001" 
#define DOPRA_VISP_VERSION "DOPRA IP V300R002C30SPC070" 


/* VISP��HA�޶���,  ����ͬһ��R/C�汾, R/C�汾�ŷ����仯���ִ�1���¿�ʼ��� */
/* B018 -> B021 (0 -> 1) �״�Э��δͨ���������� */
/* B013 -> B015 (1 -> 2) ͬ��V1R7C01B039��PPP�������� */
/* B020 -> B021 (3 -> 4) B021�汾����tlv���� */
/* B020 -> B021 (3 -> 4) B021�汾����ifnet tlv���� */
/* B021 -> B022 (4 -> 5) B022�汾����1AG tlv���� */
/* B022 -> B023 (5 -> 6) SPC020B001�汾����physical��ַ���� */
/* B022 -> B023 (5 -> 6) SPC020B001�汾����PPP TLV���� */
/* SPC010 -> SPC020 (6 -> 7) SPC020�汾����Public TLV���� */
/* SPC010 -> SPC020 (6 -> 7) SPC020�汾����DHCPָ�����ӿ�ʹ�ܱ��� */
/* SPC500 �汾����TRUNK�˿ڱ��ݼ�LACP��ǿ���� */
/* SPC330 (9 -> 10)�汾����ARP�ϻ�ʱ����ɢȫ�ֱ������� */
/* SPC330 (10 -> 11)�汾����ARP����VLAN ID�ֶα��� */
#define VISP_HA_UPDATE 11


/******************************************************************************
 * ���������궨���ˡ������͡��ء�����״̬��ֱ�Ӽ̳�VRP����غꡣ
 * ���磺
 *        #define TCPIP_IN_VRP           VRP_YES
 *        #define VRP_DISTRIBUTED        VRP_NO
 * ��ʾVISP����VRPV5֮�У�VISP���Ƿֲ�ʽ��ʽӦ�ã�������VISPϵͳ�ڱ���ʱ��
 * �Ϳ��Բ����ش��롣
 * ��Ҫע�������Щ�����ϻ����һ�Ժ꣬���ܱ�ͬʱ��Ϊ��VRP_YES����VRP_NO����
 * ע�⣬�벻Ҫ�޸����������ֵ��
 ******************************************************************************/
#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif

/******************************************************************************
 * LibС�ͻ����ü�HA��
******************************************************************************/

#ifdef TCPIP_MODULE_BEMINI
#define TCPIP_MODULE_MINI        VRP_YES
#else
#define TCPIP_MODULE_MINI        VRP_NO
#endif

#ifndef TCPIP_MODULE_NOHA
#define TCPIP_MODULE_HA        VRP_YES
#else
#define TCPIP_MODULE_HA        VRP_NO
#endif

/******************************************************************************
 * ����ֲ��ȡ���Ĺ���,Ĭ��û�иù���
******************************************************************************/
#ifndef TCPIP_ENABLEPCAP
#define TCPIP_MODULE_PCAP             VRP_NO
#else
#define TCPIP_MODULE_PCAP             VRP_YES
#endif

#ifndef TCPIP_ENABLEDCC
#define TCPIP_MODULE_DCC             VRP_NO
#else
#define TCPIP_MODULE_DCC             VRP_YES
#endif

#ifndef TCPIP_FORUSP
#define TCPIP_FOR_USP             VRP_NO
#else
#define TCPIP_FOR_USP             VRP_YES
#endif

#ifndef TCPIP_FORHERT
#define TCPIP_FOR_HERT             VRP_NO
#else
#define TCPIP_FOR_HERT             VRP_YES
#endif

#ifndef TCPIP_FORBALONG
#define TCPIP_FOR_BALONG           VRP_NO
#else
#define TCPIP_FOR_BALONG           VRP_YES
#endif
#ifndef TCPIP_FORBLUESTAR
#define TCPIP_FOR_BLUESTAR           VRP_NO
#else
#define TCPIP_FOR_BLUESTAR           VRP_YES
#endif
/************************************************************************
 * ��Щ����������Ϊstatic�������ڵ�Ԫ����ʱ���޷����øú�������ˣ���
 * ��Ԫ����֮ǰ����static�ĳ�STATIC��STATIC��������
 ************************************************************************/
#ifdef VRP_UNIT_TEST
#define STATIC
#else
#define STATIC  static
#endif

/******************************************************************************
 * ��ʶ��ͨ����ͷ���ͨ�����ȫ�ֺ�
 *   VISP��Ŀ����ͨ����ʹ��ʱ������VRPV5R2���Թ����Ӽ��ķ�ʽʹ�ã�ȫ�ֺ궨��Ϊ��
 *                  #define TCPIP_IN_VRP    VRP_YES
 *   VISP��Ŀ�ڷ���ͨ����ʹ��ʱ����mini VRP�ķ�ʽʹ�ã�ȫ�ֺ궨��Ϊ��
 *                  #define TCPIP_IN_VRP    VRP_NO
 ******************************************************************************/
#ifndef TCPIP_NOVRP
#define TCPIP_IN_VRP             VRP_YES
#else
#define TCPIP_IN_VRP             VRP_NO
#endif

#ifndef TCPIP_NONSR
#define TCPIP_NSR               VRP_YES
#else
#define TCPIP_NSR                VRP_NO
#endif

/* Added by likaikun00213099 for SafeModify at 20141213 */
#define  VOS_FUNC_TYPE_USER     1  /*��Ʒ�Զ���vos������������������ǰ�ȫ��*/
#define  VOS_FUNC_TYPE_SAFE     2  /*��ȫvos������*/
#define  VOS_FUNC_TYPE_BALONG   3  /*balong  vos ������*/

#define  VOS_FUNC_TYPE_SAFE_MBSC     4  /*���׿�������Ʒ�İ�ȫ������*/

#ifdef TCPIP_FORBALONG
    #define  TCPIP_VOS_FUNC_TYPE  VOS_FUNC_TYPE_BALONG
#else
/* default unsafe */
#ifndef TCPIP_VOS_FUNC_TYPE
    #define  TCPIP_VOS_FUNC_TYPE  VOS_FUNC_TYPE_USER
#endif
#endif

#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_BALONG) /*balong Ԥ����,ת���� */
   #include "vos_redef.h"
#endif

/* ��ȫ���Ĺ���ͷ�ļ���������ȫ/BALONG/�ǰ�ȫ�궨�� */
#include "vos_safedef.h"
/* End by likaikun00213099 for SafeModify at 20141213 */

/*Begin BC3D00605 liangjicheng  2008-11-11*/
#if 1
/* Modified by wujie 61195 for BC3D00428 */
/*ȱʡΪwindows*/
#if (TCPIP_NOVRP_VXWORKS == VRP_YES)
#define VRP_OS_WINDOWS           VRP_NO
#define VRP_OS_VXWORKS           VRP_YES
#define VRP_OS_LINUX             VRP_NO
#elif (TCPIP_NOVRP_LINUX == VRP_YES)
#define VRP_OS_WINDOWS           VRP_NO
#define VRP_OS_VXWORKS           VRP_NO
#define VRP_OS_LINUX             VRP_YES
#else
#define VRP_OS_WINDOWS           VRP_YES
#define VRP_OS_VXWORKS           VRP_NO
#define VRP_OS_LINUX             VRP_NO
#endif

/*ȱʡΪСͷ��*/
#ifndef TCPIP_BIG_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_YES
#define VRP_BIG_ENDIAN           VRP_NO
#else
#define VRP_LITTLE_ENDIAN        VRP_NO
#define VRP_BIG_ENDIAN           VRP_YES
#endif

#else
/*Modified by liangjicheng for DCL 2008-08-26*/
#if (VOS_OS_VER == VOS_WIN32)
#define VRP_OS_WINDOWS              VRP_YES
#define VRP_OS_VXWORKS              VRP_NO

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#elif (VOS_OS_VER == VOS_VXWORKS)
#define VRP_OS_WINDOWS              VRP_NO
#define VRP_OS_VXWORKS              VRP_YES

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#elif (VOS_CPU_TYPE == VOS_ARM)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#elif (VOS_CPU_TYPE == VOS_MIPS)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#elif (VOS_OS_VER == VOS_LINUX)
#define VRP_OS_WINDOWS              VRP_NO
#define VRP_OS_VXWORKS              VRP_YES

#if (VOS_CPU_TYPE == VOS_MIPS32)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#endif
#endif
/*End BC3D00605 liangjicheng  2008-11-11*/
#ifndef VOS_ARM
#define VOS_ARM                        8
#endif


/********************************************************************
 * ����������Ŀ���ؿ��Ծ����������VISP�汾�ǡ����а汾��
 * ���ǡ����԰汾�����������������Ҳ�ǻ���ġ��ڵ��԰汾
 * �У�Ӧ�ó������Ƕ������ĵ�����Ϣ�����ڷ��а汾�У����ǲ������
 ********************************************************************/
#define TCPIP_VERSION_RELEASE     VRP_NO
#define TCPIP_VERSION_DEBUG       VRP_YES



/* ��ƭ��ЩҪ��������vrpcfg.h���ļ� */
#ifndef _VRPCFG_H_
#define _VRPCFG_H_
#endif

#ifdef TCPIP_SUPPORT_ARMCPU
/*�ֽڶ���ר�ú꣬VOS_CopyVar(Dest, Src) �������ݽṹ��������������ͣ�����Src�����ݿ�����Dest��
ע�⣺Dest��Src�����ݽṹ���ͣ��ڲ���ʱ�����뱣֤��ȷ����һ�¡�*/
#define VOS_CopyVar(Dest, Src)\
{\
    (VOID)TCPIP_Mem_Copy((VOID *)&(Dest), sizeof(Dest),(VOID *)&(Src), sizeof(Dest));\
}
#define NOT_4BYTE_BONDARY(p)  (((ULONG)(p)& 0x00000003) != 0)
#define NOT_2BYTE_BONDARY(p)  (((ULONG)(p)& 0x00000001) != 0)
#else
#define VOS_CopyVar(Dest, Src)  {(Dest) = (Src);}
#endif


/*************************************************************************

 ������VISP�ڷ���ͨ��Ʒ������ʹ�õĺ꣬������
 1��VRPV5R2��vrpcfg.h�ļ��еĲ��ֺ꣬����VISP����Ҫ��ԭ�ⲻ���ؼ̳е�VISP֮��
 2��VISP��IFENT����·��ģ��ĺ�

 ע�⣺����ԭ�ⲻ���ؼ̳еĺ꣬�����Ҫ����Щ����������κθĶ�

**************************************************************************/
/* Added by Sun Mo 44939 2005-09-21 */
#define VRP_MODULE_IPHC            VRP_YES
#define VRP_MODULE_LINK_FRF20      VRP_NO
#define VRP_MODULE_VOS_IPC         VRP_NO
#define VRP_MODULE_RTPRO_RM        VRP_NO
#define VRP_MODULE_CFG_IC_BASE     VRP_NO
#define VRP_MODULE_QUEUE           VRP_NO
#define VRP_MODULE_SEC_L2TP        VRP_NO
#define VRP_MODULE_LINK_PPP_CCP    VRP_NO
#define VRP_MODULE_LINK_PPP_OSICP  VRP_NO
#define VRP_MODULE_CFG_BASE        VRP_NO
/* End of add of Sun Mo 44939 2005-09-21 */

#define VRP_MODULE_IPV6         VRP_YES
#define VRP_DISTRIBUTED         VRP_NO
#define VRP_MAIN_BOARD          VRP_NO
#define VRP_IO_BOARD            VRP_NO
#define VRP_CENTERALIZATION     VRP_YES
#define VRP_MAX_BOARD_NUM       32
#define VRP_MODULE_LINK_PPP     VRP_YES
#define VRP_PRODUCT_GSR         VRP_NO
#define TCPIP_MODULE_SFIB_RM    VRP_YES
#define TCPIP_MODULE_SFIB6_RM   VRP_YES
#define VRP_MODULE_FIB6CONTR    VRP_YES
#define VRP_MODULE_SEC_ACL      VRP_YES
#define VRP_VERSION_5           VRP_YES


#define VRP_MODULE_LINK_PPP_PAP     VRP_YES
#define VRP_MODULE_LINK_PPP_CHAP    VRP_YES
#define VRP_MODULE_LINK_PPP_IPCP    VRP_YES
#define VRP_MODULE_LINK_PPP_IP6CP   VRP_YES
#define VRP_MODULE_LINK_PPP_CBCP    VRP_NO
#define VRP_MODULE_LINK_PPP_DNS     VRP_YES
#define VRP_MODULE_LINK_PPP_MPLSCP  VRP_NO

#define VRP_MODULE_LINK_PPP_MP          VRP_YES
#define VRP_MODULE_LINK_PPPOE_CLIENT    VRP_YES
#define VRP_MODULE_LINK_PPP_MP_INBOARD  VRP_YES


#define VRP_MODULE_IP_BASE        VRP_YES
#define VRP_MODULE_IP_SOCKET      VRP_YES
#define VRP_MODULE_IP_TCP         VRP_YES
#define VRP_MODULE_IP_UDP         VRP_YES
#define VRP_MODULE_IP_ARP_PROXY   VRP_YES
#define VRP_MODULE_VJCOMP         VRP_YES


#define TCPIP_MODULE_FIBA         VRP_YES
#define VRP_MODULE_DNS_CLIENT     VRP_YES
#define VRP_MODULE_DHCP4C_BASE    VRP_YES
#define VRP_MODULE_IP_MCAST_BASE  VRP_YES

#define VRP_MODULE_CFG_PING       VRP_YES
#define VRP_MODULE_LINK_PPPOE     VRP_YES
#define VRP_MODULE_SEC_ACLACC     VRP_NO
#define VRP_MODULE_SEC_ETH_ACL    VRP_YES
#define VRP_MODULE_CFG_TRACERT    VRP_YES
#define VRP_MODULE_SEC_ATK        VRP_YES

#define VRP_MODULE_IFNET         VRP_YES
#define VRP_IFNET_LOGIC_ENHENCE  VRP_YES
#define VRP_MAX_ADAPTOR_NUM      3
#define VRP_IFNET_MP_GROUP       VRP_YES
#define VRP_IP_ICMP_REDIRECTS    VRP_YES
#define VRP_IP_ICMP_HOST_UNREACH VRP_YES

#ifndef VRP_NO_VRF6
#define VRP_MODULE_VRF6  VRP_YES
#else
#define VRP_MODULE_VRF6  VRP_NO
#endif

/*Added by zhukun,for compile ipv6,20040923*/
#ifndef FALSE
#define    FALSE          0
#endif
#ifndef TRUE
#define    TRUE           1
#endif
/*End,20040923*/

/*Added by lht06581 for pc-lint, 2005-12-01*/
#define VRP_MODULE_MPLS_LSPM_VPN            VRP_NO
#define VRP_MODULE_RTPRO_MPLS_VPN           VRP_NO
#define VRP_MODULE_RTPRO_BGP                VRP_NO
#define VRP_OPTIM_MBUF                      VRP_NO
#define VRP_MODULE_HA_DATA                  VRP_NO
#define VRP_MODULE_HA_SLAVE2MAIN            VRP_NO
#define VRP_MODULE_CFA                      VRP_NO
#define VRP_MODULE_SNMP                     VRP_NO
#define VRP_MODULE_LINK_VLAN                VRP_NO
#define USR_8011                            VRP_NO
#define L3_8011                             VRP_NO
#define VRP_MODULE_BAS_ACM                  VRP_NO
#define VRP_MODULE_LINK_ATM                 VRP_NO
#define VRP_MODULE_IP_VRRP                  VRP_NO
#define VRP_MODULE_SOCKET_ISIS              VRP_NO
#define VRP_MODULE_CFG_CLI_BASE             VRP_NO
#define VRP_MODULE_CFG_EXEC                 VRP_NO
#define VRP_MODULE_CFG_CLI_CFGFILE          VRP_NO
/*End, 2005-12-01*/

/*Add by wht06310 for pc-lint, 2005-12-01*/
#define IPV6_VLAN                             VRP_NO
#define VRP_MODULE_LINK_IPX                   VRP_NO
#define VRP_MODULE_LINK_IPOEOA                VRP_NO
#define VRP_MODULE_IP_MPLS_SOFTFW             VRP_NO
#define VRP_MODULE_SEC_NAT                    VRP_NO
#define VRP_MODULE_NATPT                      VRP_NO
#define VRP_MODULE_IP_SAN_FORWARD             VRP_NO
#define VRP_MODULE_WCCP2                      VRP_NO
#define VRP_IP_DIRECT_BROADCAST               VRP_NO
#define VRP_MODULE_SAN_TRVS                   VRP_NO
#define VRP_MODULE_LSPM_VPN                   VRP_NO
#define VRP_MODULE_IP_POLICY                  VRP_NO
#define VRP_MODULE_SEC_TIMERNG                VRP_NO
#define VRP_PRODUCT_8060                      VRP_NO
#define R8060_NP                              VRP_NO
#define VRP_MODULE_SACL                       VRP_NO
#define VRP_PRODUCT_8060_ROUTER_NE20          VRP_NO
#define PLATFORM_PRODUCT_SEPARATION_API       VRP_NO
#define PPI_CUSTOMIZE_QOS_FEATURE_ON          VRP_NO
#define R8070_MODULE_SECP                     VRP_NO
#define VRP_MODULE_IP_FAST_FORWARDING         VRP_NO
#define VRP_MODULE_MPLS_L2VPN_INTERWORKING    VRP_NO
#define VRP_MODULE_SEC_GRE                    VRP_NO
#define VRP_MODULE_IP_DHCP_SERVER             VRP_NO
#define VRP_MODULE_SEC_BLS                    VRP_NO
#define VRP_MODULE_TP                         VRP_NO
#define VRP_MODULE_IP_URPF                    VRP_NO
#define VRP_MODULE_IP_DHCP                    VRP_NO
#define VRP_HWPING_SNMP                       VRP_NO
#define MODULE_GRE_8011                       VRP_NO
#define VRP_MODULE_LINK_ETHERNET              VRP_NO
#define VRP_MODULE_MPLS                       VRP_NO
#define VRP_IP_VERIFY_SOURADD                 VRP_NO
#define VRP_CLEAR_IP_DF                       VRP_NO
#define VRP_MODULE_IP_PBR                     VRP_NO
#define VRP_MODULE_IP_DHCP_RELAY              VRP_NO
#define VRP_MODULE_IP_HELPER_ADDRESS          VRP_NO
#define VRP_PRODUCT_8060_FW                   VRP_NO
#define VRP_MODULE_SEC_ACLVPN                 VRP_NO
#define VRP_MODULE_NE5000QOS                  VRP_NO
#define VRP_PRODUCT_NE5000                    VRP_NO
#define VRP_MODULE_IP_MCAST_FORWARD           VRP_NO
#define VRP_MODULE_IP_MCAST_POLICY            VRP_NO
#define VRP_MODULE_SEC_IPSEC                  VRP_YES
#define VRP_MODULE_HRP                        VRP_NO
#define VRP_MODULE_LINK_MFR                   VRP_NO
#define NE80_MODULE_ADP                       VRP_NO
#define VRP_MODULE_NETSTREAM                  VRP_NO
#define VRP_MODULE_MPLSQOS                    VRP_NO
#define GSR_8011                              VRP_NO
#define VRP_MODULE_RTPRO_MCAST                VRP_NO
#define VRP_MODULE_RTPRO_MCAST_LOCAL          VRP_NO
#define VRP_OPTIM_VP                          VRP_NO
/*End, 2005-12-01*/

/* added by wht06501 for pc-lint, 2005-12-2 */
#define VRP_MODULE_VOS_VFS                    VRP_NO
#define VRP_MODULE_LSPV                       VRP_NO
/* end of wht06501 for pc-lint, 2005-12-2 */

#define VRP_MODULE_RADIUS_MP                VRP_NO
#define VRP_MODULE_PPP_BACKUP               VRP_NO
#define VRP_MAIN_BOARD_INTERFACE            VRP_NO
#define VRP_MODULE_LINK_IB                  VRP_NO
#define R8070_IFNET_IFBACKUP                VRP_NO
#define VRP_MODULE_LINK_PPP_IPXCP           VRP_NO
#define VRP_MODULE_STAC                     VRP_NO
#define VRP_MODULE_LINK_DDR                 VRP_NO
#define VRP_MODULE_QOS_LFI                  VRP_NO
#define VRP_MODULE_MPQOS                    VRP_NO
#define VRP_MODULE_QOS                      VRP_NO

#define VRP_MODULE_LINK_DDRS                VRP_NO
#define VRP_MODULE_SEC_FIREWALL             VRP_NO

#define IF_HOT_CTL                          VRP_NO
#define IF_INFO_CTL                         VRP_NO
#define VRP_MODULE_LINK_DLSW                VRP_NO
#define VRP_MODULE_VPN_L2VPN                VRP_NO
#define VRP_MODULE_TB_BASE                  VRP_NO
#define VRP_IFNET_INTERFACE_ENHANCE         VRP_NO
#define VRP_MODULE_LINK_FR                  VRP_NO
#define VRP_IFNET_ATMEXTEND                 VRP_NO
#define VRP_IFNET_E1_T1_E3_T3_CPOS          VRP_NO
#define VRP_MODULE_SEC_IKE                  VRP_YES
#define VRP_MODULE_SEC_ACL6                 VRP_NO
#define VRP_MODULE_TRUNK                    VRP_NO
#define VRP_MODULE_MPLS_LSPM                VRP_NO

/* Ϊ��ipv6����ģ���pc-lint�澯���������� */
#define VRPV5_PERF_OPT_VER                  VRP_NO
#define NE80_MODULE_DPT                     VRP_NO


/*As linux need more memory giving 512k  stack size for linux and 16k for others*/

#if (VOS_OS_VER == VOS_LINUX)
#define TCPIP_DEFAULT_STACK_SIZE 512*1024
#define TCPIP_LLDP_STACK_SIZE  512*1024
#else
#define TCPIP_DEFAULT_STACK_SIZE 16*1024
#define TCPIP_LLDP_STACK_SIZE  16*1024
#endif


#define TCPIP_PPPMUX_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP4C_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP4R_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP6R_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE

/*Modify 2008-08-26 liangjicheng  -Move dopra_def.h to head of this file. For V1R7C02*/
/*#include "dopra_def.h"*/
#include "v_configOS.h"
#include "tcpip_cpu.h"

#ifdef  __cplusplus
}
#endif

#endif  /* end of _TCPIP_CONFIG_H_ */

