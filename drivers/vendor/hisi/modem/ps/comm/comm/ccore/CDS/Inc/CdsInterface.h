

#ifndef __CDS_INTERFACE_H__
#define __CDS_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CdsMmcInterface.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*��������������*/
#define CDS_MAX_SOFT_FILTER_NUM                 (128)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : CDS_UL_IPF_BEARER_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����IPF���˽����Bearer ID���ݶ���
              IPF Filter ID:
               0~4      ����
               5~15     EPS Bearer ID
               16       ����DHCP
               17       ����DHCPv6
               18       ����ICMP
               19       ����ICMPv6
               20       ����Link Local Address FE80
               21       ����Link Local Address FF
               22~62    ��ʱ����������չ
               63       ��ƥ���κ�Filter

*****************************************************************************/
typedef enum CDS_UL_IPF_BEARER_ID_ENUM
{
    CDS_UL_IPF_BEARER_ID_RSV0         = 0,
    CDS_UL_IPF_BEARER_ID_EPSBID5      = 5,
    CDS_UL_IPF_BEARER_ID_EPSBID15     = 15,
    CDS_UL_IPF_BEARER_ID_DHCPV4       = 16,
    CDS_UL_IPF_BEARER_ID_DHCPV6       = 17,
    CDS_UL_IPF_BEARER_ID_ICMPV4       = 18,
    CDS_UL_IPF_BEARER_ID_ICMPV6       = 19,
    CDS_UL_IPF_BEARER_ID_LL_FE80      = 20,
    CDS_UL_IPF_BEARER_ID_LL_FF        = 21,
    CDS_UL_IPF_BEARER_ID_INVALID      = 63 /*0x3F */
}CDS_UL_IPF_BEARER_ID_ENUM;

typedef VOS_UINT32  CDS_UL_IPF_BEARER_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : CDS_SOFTFILTER_DIRECTION_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CDS�����������
*****************************************************************************/
enum CDS_SOFTFILTER_DIRECTION_ENUM
{
    CDS_SOFTFILTER_DIRECTION_PRE_REL7_TFT_FILTER          = 0x00,
    CDS_SOFTFILTER_DIRECTION_DOWNLINK                     = 0x01,
    CDS_SOFTFILTER_DIRECTION_UPLINK                       = 0x02,
    CDS_SOFTFILTER_DIRECTION_UPLINK_DOWNLINK              = 0x03,
    CDS_SOFTFILTER_DIRECTION_BUTT
};
typedef VOS_UINT8 CDS_SOFTFILTER_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 ö����    : CDS_SOFTFILTER_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CDS����������Ͷ���
*****************************************************************************/
enum CDS_SOFTFILTER_TYPE_ENUM
{
    CDS_SOFTFILTER_TYPE_IPV4       = 0x00,
    CDS_SOFTFILTER_TYPE_IPV6       = 0x01,
    CDS_SOFTFILTER_TYPE_BUTT
};
typedef VOS_UINT8 CDS_SOFTFILTER_TYPE_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CDS_SOFTFILTER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask        : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask        : 1;
    VOS_UINT32                          bitOpLcIpv4AddrAndMask         : 1;
    VOS_UINT32                          bitOpLcIpv6AddrAndMask         : 1;
    VOS_UINT32                          bitOpProtocolId                : 1;
    VOS_UINT32                          bitOpSingleLocalPort           : 1;
    VOS_UINT32                          bitOpLocalPortRange            : 1;
    VOS_UINT32                          bitOpSingleRemotePort          : 1;
    VOS_UINT32                          bitOpRemotePortRange           : 1;
    VOS_UINT32                          bitOpSecuParaIndex             : 1;
    VOS_UINT32                          bitOpTypeOfService             : 1;
    VOS_UINT32                          bitOpFlowLabelType             : 1;
    VOS_UINT32                          bitOpSpare                     : 20;

    VOS_UINT32                              ulPacketFilterId;
    CDS_SOFTFILTER_DIRECTION_ENUM_UINT8     enDirection;
    CDS_SOFTFILTER_TYPE_ENUM_UINT8          enFilterType;
    VOS_UINT16                              usPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved1[3];

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;

    VOS_UINT8                           ucProtocolId;
    VOS_UINT8                           ucTypeOfService;          /*TOS*/
    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved2[1];

    IPV4_ADDR_UN                        unLocalIpv4Addr;
    IPV4_ADDR_UN                        unLocalIpv4Mask;
    IPV4_ADDR_UN                        unRmtIpv4Addr;
    IPV4_ADDR_UN                        unRmtIpv4Mask;
    IPV6_ADDR_UN                        unLocalIpv6Addr;
    IPV6_ADDR_UN                        unLocalIpv6Mask;
    IPV6_ADDR_UN                        unRmtIpv6Addr;
    IPV6_ADDR_UN                        unRmtIpv6Mask;
    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/
}CDS_SOFTFILTER_INFO_STRU;


/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_UINT32  CDS_GetRanMode(VOS_VOID);
extern VOS_UINT32  CDS_SetUlSoftFilter(const CDS_SOFTFILTER_INFO_STRU *pstUlFilterInfo, VOS_UINT32 ulFilterNum);
extern VOS_UINT32  CDS_IsPsDataAvail(VOS_VOID);



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif

