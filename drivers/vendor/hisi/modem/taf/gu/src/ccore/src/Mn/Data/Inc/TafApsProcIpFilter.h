

#ifndef __TAFAPSIPF_H__
#define __TAFAPSIPF_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Ps.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �������Filter��ĿΪ128 */
#define TAF_APS_IPF_MAX_UL_FILTER               (128)

/* ����FilterĿǰʹ��8�� */
#define TAF_APS_IPF_MAX_DL_FILTER               (8)

/* ����NIDS Filter�����Ŀ */
#define TAF_APS_IPF_MAX_UL_NDIS_FILTER          (12)

/* ��ǰ����NDIS Filter��Ŀ */
#define TAF_APS_IPF_CUR_UL_NDIS_FILTER_NUM      (10)

/* IPF ʹ�õ�Filter���� */
#define TAF_APS_IPF_IPTYPE_IPV4                 (0)
#define TAF_APS_IPF_IPTYPE_IPV6                 (1)
#define TAF_APS_IPF_IPTYPE_IPV4V6               (2)
#define TAF_APS_IPF_IPTYPE_INVALID              (3)

#define TAF_APS_NO_UPPERLAYER                   (0)

/* ��NDIS�������ݰ��Ĺ�����Ԥ�������ȼ�������0-5 */
#define TAF_APS_IPF_UL_NDIS_PRIORITY_NUM        (6)

#define TAF_APS_MIN_AIR_TFT_PRIORITY            (255)

/* ΪĬ�ϳ������õ����ȼ� ,������������TFT Filter�����ȼ� */
#define TAF_APS_IPF_LOWEST_PRI                  (TAF_APS_IPF_UL_NDIS_PRIORITY_NUM+\
                                                 TAF_APS_MIN_AIR_TFT_PRIORITY+1)

/* IPF���˲�ƥ������Filter */
#define TAF_APS_IPF_INVALID_BEARER_ID           (0x3F)

#define TAF_APS_IPF_UL_IPV4_FILTER_ID(rabid, filterid)\
    ((((VOS_UINT32)rabid)<<8)|((VOS_UINT32)(filterid)))

#define TAF_APS_IPF_UL_IPV6_FILTER_ID(rabid, filterid)\
    ((((VOS_UINT32)rabid)<<12)|((VOS_UINT32)(filterid)))
/* ���º궨��ΪNAS IPF Filter ���в����� */
/* #define TAF_APS_IPF_CONFIG_INFO_PTR()          &g_stTafApsIpfConfigInfo */
#define TAF_APS_IPF_FILTER_LIST_PTR()           &g_stTafApsIpfFilterArray

/* ��������Filter��Ŀ */
#define TAF_APS_IPF_ADD_UL_FILTER_NUM()         (((TAF_APS_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum)++)
/* ��������Filter��Ŀ */
#define TAF_APS_IPF_SET_UL_FILTER_NUM(num)      ((TAF_APS_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum = (num))
/* ��ȡ��������Filter��Ŀ */
#define TAF_APS_IPF_GET_UL_FILTER_NUM()         ((TAF_APS_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum)
/* ��ȡ����ָ��λ�õ�Filter */
#define TAF_APS_IPF_GET_UL_FILTER_PTR(num)      (&((TAF_APS_IPF_FILTER_LIST_PTR())->astUlFilter[num]))
/* �ж�����FIlter�����Ƿ��� */
#define TAF_APS_IPF_IS_UL_FILTER_FULL()         (TAF_APS_IPF_GET_UL_FILTER_NUM() >= TAF_APS_IPF_MAX_UL_FILTER)

/* ��������Filter��Ŀ */
#define TAF_APS_IPF_ADD_DL_FILTER_NUM()         (((TAF_APS_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum)++)
/* ��������Filter��Ŀ */
#define TAF_APS_IPF_SET_DL_FILTER_NUM(num)      ((TAF_APS_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum = (num))
/* ��ȡ��������Filter��Ŀ */
#define TAF_APS_IPF_GET_DL_FILTER_NUM()         ((TAF_APS_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum)
/* ��ȡ����ָ��λ�õ�Filter */
#define TAF_APS_IPF_GET_DL_FILTER_PTR(num)      (&((TAF_APS_IPF_FILTER_LIST_PTR())->astDlFilter[num]))
/* �ж�����FIlter�����Ƿ��� */
#define TAF_APS_IPF_IS_DL_FILTER_FULL()         ((TAF_APS_IPF_GET_DL_FILTER_NUM() >= TAF_APS_IPF_MAX_DL_FILTER))

/* IPF���ȼ��ȽϺ������� */
typedef VOS_INT (*TAF_APS_IPF_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/* IPF����NDIS Filter���� */
#define TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(filter_id)\
    pstFilter = &g_astTafApsUlNdisFilter[filter_id];\
    PS_MEM_SET(pstFilter, 0x0, sizeof(TAF_APS_IPF_UL_NDIS_FILTER_INFO))

#define TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(iptype)\
    pstFilter->ucIpType = (iptype)

#define TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(priority)\
    pstFilter->usPriority = (priority)

#define TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(protocol)\
    pstFilter->ucProtocolId = (protocol);\
    pstFilter->bitOpProtocolId = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_PORT_HI(port_hi)\
    pstFilter->usPortHi = (port_hi);\
    pstFilter->bitOpPort = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_PORT_LO(port_lo)\
    pstFilter->usPortLo = (port_lo);\
    pstFilter->bitOpPort = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(type)\
    pstFilter->usIcmpType = (type);\
    pstFilter->bitOpType = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(code)\
    pstFilter->usIcmpCode = (code);\
    pstFilter->bitOpCode = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_DSTADDR_FE80()\
    pstFilter->aucDstAdrr[0] = 0xfe;\
    pstFilter->aucDstAdrr[1] = 0x80;\
    pstFilter->aucDstMask[0] = 0xff;\
    pstFilter->aucDstMask[1] = 0xc0;\
    pstFilter->bitOpDstAdrr = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_DSTADDR_FF()\
    pstFilter->aucDstAdrr[0] = 0xff;\
    pstFilter->aucDstMask[0] = 0xff;\
    pstFilter->bitOpDstAdrr = VOS_TRUE

#define TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(filter_id)

/* ����NDIS DHCPv4 Filter����, UDP Ŀ�Ķ˿�Ϊ68 */
#define TAF_APS_IPF_DEF_UL_NDIS_DHCPV4_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_DHCP4);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(17);\
    TAF_APS_IPF_UL_NDIS_FILTER_PORT_HI(67);\
    TAF_APS_IPF_UL_NDIS_FILTER_PORT_LO(67);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_DHCP4)

/* ����NDIS Filter����, UDPĿ�Ķ˿�546 */
#define TAF_APS_IPF_DEF_UL_NDIS_DHCPV6_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_DHCP6);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(17);\
    TAF_APS_IPF_UL_NDIS_FILTER_PORT_HI(546);\
    TAF_APS_IPF_UL_NDIS_FILTER_PORT_LO(546);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_DHCP6)

/* ����NDIS ICMP Router Solicitation Filter����, Э���58��Type 133�� code 0 */
#define TAF_APS_IPF_DEF_UL_NDIS_ICMP_RS_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_RS);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(133);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_RS)

/* ����NDIS ICMP Router Advertisement Filter����, Э���58��Type 134�� code 0 */
#define TAF_APS_IPF_DEF_UL_NDIS_ICMP_RA_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_RA);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(134);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_RA)

/* ����NDIS ICMP Neighbor Solicitation Filter����, Э���58��Type 135�� code 0 */
#define TAF_APS_IPF_DEF_UL_NDIS_ICMP_NS_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_NS);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(135);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_NS)

/* ����NDIS ICMP Neighbor Advertisement Filter����, Э���58��Type 136�� code 0 */
#define TAF_APS_IPF_DEF_UL_NDIS_ICMP_NA_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_NA);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(136);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_NA)

/* ����NDIS ICMP REDIRECT Filter����, Э���58��Type 137�� code 0 */
#define TAF_APS_IPF_DEF_UL_NDIS_ICMP_REDIRECT_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_REDIRECT);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(137);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_REDIRECT)

/* ����NDIS ICMP ECHO REQUEST����, Э���58��Type 128�� code 0��Ŀ�ĵ�ַΪFE80��ͷ */
#define TAF_APS_IPF_DEF_UL_NDIS_LOC_PING6_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_LOC_PING6);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    TAF_APS_IPF_UL_NDIS_FILTER_DSTADDR_FE80();\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPTYPE(128);\
    TAF_APS_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_LOC_PING6)

/* ����NDIS Ŀ�ĵ�ַFE80��ͷ���� */
#define TAF_APS_IPF_DEF_UL_NDIS_LOC_FE80_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_LOC_FE80);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_DSTADDR_FE80();\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_LOC_FE80)

/* ����NDIS Ŀ�ĵ�ַFF��ͷ���� */
#define TAF_APS_IPF_DEF_UL_NDIS_LOC_FF_FILTER()\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(TAF_APS_IPF_UL_NDIS_FILTER_LOC_FF);\
    TAF_APS_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_DSTADDR_FF();\
    TAF_APS_IPF_UL_NDIS_FILTER_PRIORITY(1);\
    TAF_APS_IPF_UL_NDIS_FILTER_DEFINE_END(TAF_APS_IPF_UL_NDIS_FILTER_LOC_FF)

/* ��ȡ����NDIS�û������Filter */
#define TAF_APS_IPF_GET_UL_NDIS_USER_FILTER(filter_id)\
    (&g_astTafApsUlNdisFilter[filter_id])

/* ����ҵ�Filter ID��Ӧ��Ӧ���ø�������Bid */
#define TAF_APS_IPF_CONV_ULNDISFILTER_TO_BID(filter_id)\
    (g_aulTafApsUlNdisFilterTypeTable[filter_id][1])

#define TAF_APS_IPF_GET_UL_NDIS_FILTER_FLAG()     (g_enTafApsUlNdisFilterValidFlag)
#define TAF_APS_IPF_SET_UL_NDIS_FILTER_FLAG(flag) (g_enTafApsUlNdisFilterValidFlag = (flag))

/*�����չ��������־������17bit����Ϊ0*/
#define TAF_APS_IPF_CLR_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) & 0x0000FFFF)

/*������չ��������־������17bit����Ϊ1*/
#define TAF_APS_IPF_SET_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) | 0x00010000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_APS_IPF_UL_NDIS_FILTER_TYPE
 ö��˵��  : ����NDIS��������
*****************************************************************************/
enum TAF_APS_IPF_UL_NDIS_FILTER_TYPE
{
    TAF_APS_IPF_UL_NDIS_FILTER_DHCP4 = 0,
    TAF_APS_IPF_UL_NDIS_FILTER_DHCP6,
    TAF_APS_IPF_UL_NDIS_FILTER_RS,
    TAF_APS_IPF_UL_NDIS_FILTER_RA,
    TAF_APS_IPF_UL_NDIS_FILTER_NS,
    TAF_APS_IPF_UL_NDIS_FILTER_NA,
    TAF_APS_IPF_UL_NDIS_FILTER_REDIRECT,
    TAF_APS_IPF_UL_NDIS_FILTER_LOC_PING6,
    TAF_APS_IPF_UL_NDIS_FILTER_LOC_FE80,
    TAF_APS_IPF_UL_NDIS_FILTER_LOC_FF,
    TAF_APS_IPF_UL_NDIS_FILTER_BUTT
};
typedef VOS_UINT32  TAF_APS_IPF_UL_NDIS_FILTER_TYPE_UINT32;

/*****************************************************************************
 ö����    : TAF_APS_IPF_DIRECTION
 ö��˵��  :  IPF Filter����
*****************************************************************************/
enum TAF_APS_IPF_DIRECTION
{
    TAF_APS_IPF_DIRECTION_UL = 0,
    TAF_APS_IPF_DIRECTION_DL,
    TAF_APS_IPF_DIRECTION_BUTT
};
typedef VOS_UINT32  TAF_APS_IPF_DIRECTION_UINT32;

/*****************************************************************************
 ö����    : TAF_APS_UL_NDIS_FILTER_FLAG_ENUM
 ö��˵��  : ����NDIS�������ݰ���FILTER�����Ƿ���Чö��
               0        ��Ч
               1        ��Ч

*****************************************************************************/
enum TAF_APS_UL_NDIS_FILTER_FLAG_ENUM
{
    TAF_APS_UL_NDIS_FILTER_VALID        = 0,                                    /* ��Ч */
    TAF_APS_UL_NDIS_FILTER_INVALID      = 1,                                    /* ��Ч */

    TAF_APS_UL_NDIS_FILTER_FLAG_BUTT
};
typedef VOS_UINT32 TAF_APS_UL_NDIS_FILTER_FLAG_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_APS_IPF_FILTER_ARRAY
 �ṹ˵��  : IPF FILTER���нṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulUpLinkUsedNum;
    VOS_UINT32                      ulDownLinkUsedNum;
    IPF_FILTER_CONFIG_S             astUlFilter[TAF_APS_IPF_MAX_UL_FILTER];
    IPF_FILTER_CONFIG_S             astDlFilter[TAF_APS_IPF_MAX_DL_FILTER];
}TAF_APS_IPF_FILTER_ARRAY;

/*****************************************************************************
 �ṹ��    : TAF_APS_IPF_IP4FRAG_CONTEXT
 �ṹ˵��  : IPv4 ��Ƭ�����Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucSrcAddr[TAF_IPV4_ADDR_LEN];                           /* Դ��ַ */
    VOS_UINT8           ucDstAddr[TAF_IPV4_ADDR_LEN];                           /* Ŀ�ĵ�ַ */
    VOS_UINT8           ucIpId[TAF_IPV4_ADDR_LEN];                              /* IP IDentification */
}TAF_APS_IPF_IP4FRAG_CONTEXT;

/*****************************************************************************
 �ṹ��    : TAF_APS_IPF_IP6FRAG_CONTEXT
 �ṹ˵��  : IPv6 ��Ƭ�����Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucSrcAddr[TAF_IPV6_ADDR_LEN];                           /* Դ��ַ */
    VOS_UINT8           ucDstAddr[TAF_IPV6_ADDR_LEN];                           /* Ŀ�ĵ�ַ */
    VOS_UINT8           ucIpId[TAF_IPV4_ADDR_LEN];                              /* IP IDentification */
}TAF_APS_IPF_IP6FRAG_CONTEXT;

/*****************************************************************************
 �ṹ��    : TAF_APS_IPF_UL_NDIS_FILTER_INFO
 �ṹ˵��  : ����NDIS Filterʹ�õļ��׽ṹ��������������NDIS�������ݰ���FILTER
*****************************************************************************/
typedef struct
{
    VOS_UINT16          bitOpProtocolId:1;
    VOS_UINT16          bitOpPort:1;
    VOS_UINT16          bitOpType:1;
    VOS_UINT16          bitOpCode:1;
    VOS_UINT16          bitOpDstAdrr:1;
    VOS_UINT16          bitRsv:11;

    VOS_UINT8           ucIpType;                                               /* ip type, v4 or v6 */
    VOS_UINT8           ucProtocolId;
    VOS_UINT16          usPortHi;                                               /* dest port */
    VOS_UINT16          usPortLo;                                               /* dest port */
    VOS_UINT16          usIcmpType;
    VOS_UINT16          usIcmpCode;
    VOS_UINT8           aucDstAdrr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8           aucDstMask[TAF_IPV6_ADDR_LEN];
    VOS_UINT16          usPriority;
    VOS_UINT8           aucReserved[2];
}TAF_APS_IPF_UL_NDIS_FILTER_INFO;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern IPF_FILTER_CONFIG_S * TAF_APS_IpfGetFreeFilter(
    TAF_APS_IPF_DIRECTION_UINT32        enDir
);

extern VOS_INT32  TAF_APS_IpfCompare(
    const VOS_VOID                     *arg1,
    const VOS_VOID                     *arg2
);

extern VOS_UINT32 TAF_APS_IpfGenerateBaseIpv4Filter(
    const APS_PDP_ADDR_ST              *pstPdpAddr,
    VOS_UINT8                           ucRabId
);

#if (FEATURE_ON == FEATURE_IPV6)
extern VOS_UINT32 TAF_APS_IpfGenerateBaseIpv6Filter(
    VOS_UINT8                          *pucPdpAddr,
    VOS_UINT8                           ucRabId
);
#endif

extern VOS_UINT32 TAF_APS_IpfGenerateFilterWithoutTFT(
    VOS_UINT8                           ucPdpId
);

extern VOS_VOID TAF_APS_IpfConvertOtherPartToFilter(
    const TAF_PDP_PF_STRU              *pstPdpPf,
    IPF_MATCH_INFO_S                   *pstIpFilter
);

extern VOS_UINT32 TAF_APS_IpfCheckFilterType(
    const TAF_PDP_PF_STRU              *pstPdpPf,
    VOS_UINT8                           ucPdpType
);

extern VOS_UINT32 TAF_APS_IpfGenerateFilters(VOS_VOID);

extern VOS_VOID TAF_APS_IpfConfigUlFilter(VOS_UINT8 ucPdpId);

extern VOS_VOID TAF_APS_SetUlNdisFilterValidFlag(
    TAF_APS_UL_NDIS_FILTER_FLAG_ENUM_UINT32   enUlNdisFilterFlag
);
extern VOS_UINT32 TAF_APS_IpfAddUlNdisFilter(
    VOS_UINT32                          ulFilterId
);
extern VOS_UINT32 TAF_APS_IpfRmvUlNdisFilter(
    VOS_UINT32                          ulFilterId
);
extern VOS_VOID TAF_APS_IpfUlNdisFilterInit( VOS_VOID );


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafApsProcIpFilter.h */

