/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              fw_acl_def.h
 *
 *  Project Code: VISP1.6
 *   Module Name: ACL4
 *  Date Created: 2006-12-01
 *        Author: lijing 52889
 *   Description: �궨��
 *   Version:      1
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-12-01      lijing 52889    Create
 *  2008-10-24      liangjicheng   C02NEWR-ACL  support SCTP
 *  2012-02-16      r00902615      Added new Macro ACL_DELETE_ALL_RULE
 *
 ************************************************************************/
#ifndef _FW_ACL_DEF_H_
#define _FW_ACL_DEF_H_

#ifdef  __cplusplus
extern "C" 
{
#endif


/**********************************************************
*   IP�ײ���غ궨��
***********************************************************/
/* IP�ײ�TOS�ֶεĺ궨�� */
#define ACL_TOS_NORMAL              0x0
#define ACL_TOS_MIN_MONETARY_COST   0x1
#define ACL_TOS_MAX_RELIABILITY     0x2
#define ACL_TOS_MAX_THROUGHPUT      0x4
#define ACL_TOS_MIN_DELAY           0x8
#define ACL_TOS_ALL                 0xff
#define ACL_TOS_MASK                0x1e
#define ACL_GET_TOS(p)              (((p) & ACL_TOS_MASK)>>1)

/* IP�ײ����ȼ��ֶεĺ궨�� */
#define ACL_PRE_ROUTINE             0x0
#define ACL_PRE_PRIORITY            0x1
#define ACL_PRE_IMMEDIATE           0x2
#define ACL_PRE_FLASH               0x3
#define ACL_PRE_FLASH_OVERRIDE      0x4
#define ACL_PRE_CRITICAL            0x5
#define ACL_PRE_INTERNET            0x6
#define ACL_PRE_NETWORK             0x7
#define ACL_PRE_ALL                 0xff
#define ACL_PRE_MASK                0xe0
#define ACL_GET_PRE(p)              (((p) & ACL_PRE_MASK)>>5)

/* IP�ײ�DSCP�ֶεĺ궨�� */
#define ACL_DSCP_ALL                0xff
#define ACL_DSCP_MASK               0xfc
#define ACL_GET_DSCP(p)             (((p) & ACL_DSCP_MASK)>>2)


/* ȡ���ĸ��ֶεĺ궨�� */
#define IPPROTOCAL(pIp)     pIp->ip_chPr
#define IPSRCADDR(pIp)      pIp->ip_stSrc.s_ulAddr
#define IPDSTADDR(pIp)      pIp->ip_stDst.s_ulAddr
#define IPTOS(pIp)          ((pIp->ip_chTOS>>1)&0x0f)
#define IPPRECEDENCE(pIp)   ((pIp->ip_chTOS>>5)&0x07)
#define TCPSPORT(pTcp)      pTcp->usSrcPort
#define TCPDPORT(pTcp)      pTcp->usDstPort
#define UDPSPORT(pUdp)      pUdp->uh_usSPort
#define UDPDPORT(pUdp)      pUdp->uh_usDPort
#define ICMPTYPE(pIcmp)     pIcmp->icmp_chType
#define ICMPCODE(pIcmp)     pIcmp->icmp_chCode
#define IPDSCP(pIp)         ((pIp->ip_chTOS>>2)&0x3f)

/**********************************************************
*   ����λ��غ궨�壬�ڱ���ƥ��ʱ�ɶ�ָ���ֶβ���Ƚ�
***********************************************************/
/* �����ֶθ�λ�Ķ��� */
#define ACL_SIPByte     0x0001     
#define ACL_DIPByte     0x0002
#define ACL_PROByte     0x0004
#define ACL_TOSByte     0x0008
#define ACL_PREByte     0x0010
#define ACL_SPORTByte   0x0020
#define ACL_DPORTByte   0x0040
#define ACL_DSCPByte    0x0400

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-21 */
#define ACL_VRFByte     0x0080

/* End:VISP1.7C03 VRF wangchengyang,2009-01-21 */

/* ��ȡ����λ��־ */
#define ACL_ING_SIP(ulByte)         (ACL_SIPByte & (ulByte))
#define ACL_ING_DIP(ulByte)         (ACL_DIPByte & (ulByte))
#define ACL_ING_PRO(ulByte)         (ACL_PROByte & (ulByte))
#define ACL_ING_TOS(ulByte)         (ACL_TOSByte & (ulByte))
#define ACL_ING_PRE(ulByte)         (ACL_PREByte & (ulByte))
#define ACL_ING_SPORT(ulByte)       (ACL_SPORTByte & (ulByte))
#define ACL_ING_DPORT(ulByte)       (ACL_DPORTByte & (ulByte))
#define ACL_ING_DSCP(ulByte)        (ACL_DSCPByte & (ulByte))

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-21 */
#define ACL_ING_VRF(ulByte)        (ACL_VRFByte & (ulByte))

/* End:VISP1.7C03 VRF wangchengyang,2009-01-21 */

/* ���ú���λ��Ϣ */
#define ACL_SETING_SIP(ulByte)      ((ulByte) |= ACL_SIPByte)
#define ACL_SETING_DIP(ulByte)      ((ulByte) |= ACL_DIPByte)
#define ACL_SETING_PRO(ulByte)      ((ulByte) |= ACL_PROByte)
#define ACL_SETING_TOS(ulByte)      ((ulByte) |= ACL_TOSByte)
#define ACL_SETING_PRE(ulByte)      ((ulByte) |= ACL_PREByte)
#define ACL_SETING_SPORT(ulByte)    ((ulByte) |= ACL_SPORTByte)
#define ACL_SETING_DPORT(ulByte)    ((ulByte) |= ACL_DPORTByte)
#define ACL_SETING_DSCP(ulByte)     ((ulByte) |= ACL_DSCPByte)

/**********************************************************
*   ���������غ궨��
***********************************************************/
/* ȱʡ��������ID */
#define ACL_BASIC_RULE_TYPE     1
#define ACL_ADVANCE_RULE_TYPE   2
#define ACL_IFBASED_RULE_TYPE   3
#define ACL_EXTMAC_RULE_TYPE    4


/**********************************************************
*   �������غ궨��
***********************************************************/
/* ������������ܺ� */

/*Modified from 9999 to 28999 - Rishab Joshi. */
#define ACL_MAX_GROUPNUM_SUM  32999

/* ȱʡ�������͵Ĺ��������ȱʡֵ */
#define ACL_BAS_DEFAULT_MIN     2000
#define ACL_BAS_DEFAULT_MAX     2999

#define ACL_ADV_DEFAULT_MIN     3000
#define ACL_ADV_DEFAULT_MAX     3999

/* Added by Rishab Joshi for IPSEC requirement. */
#define ACL_ADV_DEFAULT_MAX_IPSEC       26999

#define ACL_IF_DEFAULT_MIN      1000
#define ACL_IF_DEFAULT_MAX      1999

#define ACL_EXTMAC_DEFAULT_MIN  4000
#define ACL_EXTMAC_DEFAULT_MAX  4999 /* Changed from 4099 to 4999 for C06 */

#define ACL_EXTADV_DEFAULT_MIN  5000

/* ȫ���������� */
/*B015 liangjicheng 2008-12-12 SGSN NEWR 3000->10000*/

/* Modified from 10000 to 20000 - Rishab Joshi. */
#define ACL_MAX_ALLRULE_SUM   24000

/* һ������������������ */
#define ACL_MAX_GROUPRULE_SUM   1024

/* �����鲽����Χ */
#define ACL_MIN_STEP    1
#define ACL_MAX_STEP    20

/* ������Ĭ�ϲ��� */
#define ACL_DEFAULT_STEP    5


/* Э���ȡֵ��Χ */
#define ACL_MIN_PROID    0
#define ACL_MAX_PROID    255

/*Begin C02NEWR-ACL liangjicheng 2008-10-24   */
/* ICMP Code��ȡֵ��Χ */
#define ACL_MIN_ICMPCODE  0
/* Begin V300R002C10 - CGP CR: 201406165275 -Modify ICMP code range 0-255, c00902193 on 30th June 2014 */
/* #define ACL_MAX_ICMPCODE  15 */
#define ACL_MAX_ICMPCODE  255
/* End V300R002C10 - CGP CR: 201406165275 -Modify ICMP code range 0-255, c00902193 on 30th June 2014 */

/* ICMP Type��ȡֵ��Χ */
#define ACL_MIN_ICMPTYPE  0
/* Begin V300R002C10 - CGP CR: 201406165275 -Modify ICMP code range 0-255, c00902193 on 30th June 2014 */
/* fine ACL_MAX_ICMPTYPE  19 */
#define ACL_MAX_ICMPTYPE  255
/* End V300R002C10 - CGP CR:201406165275 -Modify ICMP code range 0-255, c00902193 on 30th June 2014 */
/*End    C02NEWR-ACL */


/* ��Ч��������� */
#define ACL_INVALID_GROUPNUM    0

/* ��Ч�������� */
#define ACL_INVALID_SUBNO       0xffffffff
#define ACL_DELETE_ALL_RULE     0xffffffff

/* ��̫MTU */
#define ACL_ETHERNETMTU     0x0600

/*��̫��֡��ʽ*/
#define ACL_PKTFMT_ETHNT_2   0
#define ACL_PKTFMT_EN_SNAP   1
#define ACL_PKTFMT_8023_IPX  2
#define ACL_PKTFMT_8022_IPX  3

/* VLAN ����ֵ */
#define  ACL_VLANTYPE_DOT1Q   0x8100 

/* VLANͷ�ĳ��� */
#define  ACL_VLANHDR_SIZE   4 



/**********************************************************
*   �����궨��
***********************************************************/

/* �������Ƿ���� */
#define ACL_GROUP_IS_EXIST(pstGroup) ((pstGroup) != NULL)

/* waitlist ID */
#define ACL_WaitListID 9006

/* physical��ַ���� */
#define ACL_MACADDR_LEN 6

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
#define ACL_DEFAULT_VRFINDEX 0
#define ACL_ANY_VRFINDEX     0xFFFFFFFFL

/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */

/* ACL Flags */
#define ACL_YES 1
#define ACL_NO  0

/* ACL Flags */
#define ACL_ENABLED 1
#define ACL_DISABLED 0


/* Added by bhaskar on 2009-10-20 */
/* ACL�ķ�Χ */
#define ACL_NUM_MIN             1

#define ACL_BAS_MIN             1
#define ACL_BAS_MAX             99

#define ACL_ADV_MIN             100
#define ACL_ADV_MAX             199

#define ACL_NUM_MIDDLE          199

/* VRPV3R001M06B03D003_BRIDGE_TZB ֧�ֹ�����̫֡ͷ��ACL */
#define ACL_EXTMAC_MIN          700
#define ACL_EXTMAC_MAX          799

#define ACL_NUM_MIDDLE2         1000

#define ACL_IF_MIN              1000
#define ACL_IF_MAX              1999

#define ACL_BAS_MIN_EXT         2000
#define ACL_BAS_MAX_EXT         2999

#define ACL_ADV_MIN_EXT         3000
#define ACL_ADV_MAX_EXT         3999

#define ACL_NUM_MIDDLE3         3999 /* add for SACL */

#define ACL_EXTMAC_MIN_EXT      4000
#define ACL_EXTMAC_MAX_EXT      4999 /* Changed from 4099 to 4999 for C06 */

#define ACL_NUM_MIDDLE4         4999 /* Changed from 4099 to 4999 for C06 */

/* simple acl ��������� */
#define SACL_MAX_RULE_NUM       (1024*32)

/* simple acl �����ŵķ�Χ */
#define ACL_SIMPLE_MIN          10000
#define ACL_SIMPLE_MAX          (10000 + (SACL_MAX_RULE_NUM) - 1)


/*Begin : Added by robins. to fix TRAN warnings*/
#ifndef VRP_MODULE_SEC_ETH_ACL
#define VRP_MODULE_SEC_ETH_ACL VRP_YES
#endif

#ifndef VRP_MODULE_SACL
#define VRP_MODULE_SACL VRP_NO
#endif
/*End : Added by robins. to fix TRAN warnings*/


/* ����ĺ�Ҫ�Ӵ�С���� */
#if(VRP_MODULE_SACL == VRP_YES)
    #define ACL_NUM_MAX                     ACL_SIMPLE_MAX
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_SIMPLE_MAX + 1)
#elif(VRP_MODULE_SEC_ETH_ACL == VRP_YES)
    #define ACL_NUM_MAX                     ACL_NUM_MIDDLE4
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_NUM_MIDDLE4 + 1)
#else
    #define ACL_NUM_MAX                     ACL_NUM_MIDDLE3
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_NUM_MIDDLE3 + 1)
#endif

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
#ifndef ACL_MAX_VRFNAME_LENGTH
#define ACL_MAX_VRFNAME_LENGTH      31               
#endif

/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */

/*ACL_ShowGroup���������� liuyu B016*/
#define ACL_ALL_RULE 1
#define ACL_SINGLE_RULE 0

/* ACL��ע��ICMP�ײ����� */
#define ACL_ICMP_HEADLEN 4

#define ACL_IS_RANGE(x, min, max)   (((x) <= (max)) && ((x) >= (min)))

#define ACL_LOCK_ACL    0 
#define ACL_LOCK_RFC    1
#define ACL_LOCK_SFE    2
#define ACL_LOCK_TIMER  3
#define ACL_NUM_LOCKS   4

#define ACL_OK 0

/* ������ƥ��˳�� */
#define ACL_MATCHORDER_DEFAULT  0
#define ACL_MATCHORDER_CONFIG   1
#define ACL_MATCHORDER_AUTO     2


/*Begin C02NEWR-ACL liangjicheng 2008-10-24   PROT_SCTP*/
/*#define PROT_SCTP        132*/

/*End C02NEWR-ACL liangjicheng 2008-10-24   PROT_SCTP*/

/*Bhaskar 28-10-2009: Comment End*/

/* �˿ں�ȡֵ��Χ */
#define ACL_MIN_PORTNUM 0
#define ACL_MAX_PORTNUM 65535

/* �����ַ */
#define IPADDRANY ((127 << 24) + (255 << 16) + (255 << 8) + 254)

/* ����ӿ����� */
#define IFINDEXANY 0xffffffff

#define  ACL_DSTSRCMAC_SIZE   12

/*ע��������*/
/*TRNG_RegCmd();*/

#define FW_ACL_COMMON_TIMER_MILLSEC  (1 * 60) * 1000

#ifndef ETHARP_INPUT
#define ETHARP_INPUT 0
#endif

#ifndef ETHARP_OUTPUT
#define ETHARP_OUTPUT 1
#endif

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif

#ifdef  __cplusplus
}
#endif
   
#endif

