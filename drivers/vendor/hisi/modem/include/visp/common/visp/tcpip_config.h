

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

/*----------------------------------------------------------------------
 * ���������궨���ˡ������͡��ء�����״̬��ֱ�Ӽ̳�VRP����غꡣ
 *  ���磺
 *        #define TCPIP_IN_VRP           VRP_YES
 *        #define VRP_DISTRIBUTED        VRP_NO
 * ��ʾVISP����VRPV5֮�У�VISP���Ƿֲ�ʽ��ʽӦ�ã�������VISPϵͳ�ڱ���ʱ��
 * �Ϳ��Բ����ش��롣
 * ��Ҫע�������Щ�����ϻ����һ�Ժ꣬���ܱ�ͬʱ��Ϊ��VRP_YES����VRP_NO����
 * ע�⣬�벻Ҫ�޸����������ֵ��
 */
#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif


/*----------------------------------------------------------------------
 * ��ʶ��ͨ����ͷ���ͨ�����ȫ�ֺ�
 *   VISP��Ŀ����ͨ����ʹ��ʱ������VRPV5R2���Թ����Ӽ��ķ�ʽʹ�ã�ȫ�ֺ궨��Ϊ��
 *                  #define TCPIP_IN_VRP    VRP_YES
 *   VISP��Ŀ�ڷ���ͨ����ʹ��ʱ����mini VRP�ķ�ʽʹ�ã�ȫ�ֺ궨��Ϊ��
 *                  #define TCPIP_IN_VRP    VRP_NO
 */

/*Modified by dengxiong for D00173*/
#ifndef TCPIP_NOVRP
#define TCPIP_IN_VRP             VRP_YES
#else
#define TCPIP_IN_VRP             VRP_NO
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
   #include "tcpip/public/vos_redef.h"
#endif

/* ��ȫ���Ĺ���ͷ�ļ���������ȫ/BALONG/�ǰ�ȫ�궨�� */
#include "tcpip/public/vos_safedef.h"
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
#define VRP_OS_WINDOWS           	VRP_YES
#define VRP_OS_VXWORKS           	VRP_NO

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif

#elif (VOS_OS_VER == VOS_VXWORKS)
#define VRP_OS_WINDOWS           	VRP_NO
#define VRP_OS_VXWORKS           	VRP_YES

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#elif (VOS_CPU_TYPE == VOS_ARM)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#elif (VOS_CPU_TYPE == VOS_MIPS)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif 

#elif (VOS_OS_VER == VOS_LINUX)
#define VRP_OS_WINDOWS           	VRP_NO
#define VRP_OS_VXWORKS           	VRP_YES

#if (VOS_CPU_TYPE == VOS_MIPS32)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif

#endif
#endif
/*End BC3D00605 liangjicheng  2008-11-11*/
#ifndef VOS_ARM
#define VOS_ARM                        8
#endif

/*----------------------------------------------------------------------
 * ����������Ŀ���ؿ��Ծ����������VISP�汾�ǡ����а汾��
 * ���ǡ����԰汾�����������������Ҳ�ǻ���ġ��ڵ��԰汾
 * �У�Ӧ�ó������Ƕ������ĵ�����Ϣ�����ڷ��а汾�У�����
 * �������
 */
#define TCPIP_VERSION_RELEASE     VRP_NO
#define TCPIP_VERSION_DEBUG       VRP_YES

/*----------------------------------------------------------------------*/

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


/*Added by lht06581 for pc-lint, 2005-12-01*/
#define VRP_MODULE_HA_DATA                  VRP_NO
#define VRP_MODULE_HA_SLAVE2MAIN            VRP_NO
#define VRP_MODULE_SNMP                     VRP_NO
#define VRP_MODULE_CFG_CLI_BASE             VRP_NO
/*End, 2005-12-01*/


/*Add for IR IPSec/IKE*/
#define VRP_MODULE_SEC_IPSEC                VRP_YES 

#define VRP_MODULE_SEC_IKE                  VRP_YES

#define VRP_MODULE_SEC_ENCRY_BLOWFISH       VRP_YES
#define VRP_MODULE_SEC_ENCRY_3DES           VRP_YES
#define VRP_MODULE_SEC_ENCRY_CAST           VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_DES            VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_RIPEMD         VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_SHA            VRP_YES
#define VRP_MODULE_SEC_ENCRY_SKIPJACK       VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_IKE_GNU              VRP_YES /* YES & NO*/

/* Added by Vivek, for DH changes (OpenSource) */
#define VRP_MODULE_UTIL_BN                  VRP_YES /* YES & NO*/


/*Modify 2008-08-26 liangjicheng  -Move dopra_def.h to head of this file. For V1R7C02*/
/*#include "dopra_def.h"*/
#include "v_configOS.h"

#ifdef  __cplusplus
}
#endif

#endif  /* end of _TCPIP_CONFIG_H_ */


