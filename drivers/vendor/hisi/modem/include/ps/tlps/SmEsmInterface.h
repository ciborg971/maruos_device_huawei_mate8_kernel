

#ifndef _SM_ESM_INTERFACE_H_
#define _SM_ESM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define SM_ESM_MAX_LENGTH_OF_APN            (100)
#define SM_ESM_MAX_TFT_PF_NUM               (16)

#define SM_ESM_IPV4_ADDR_LEN                (4)
#define SM_ESM_IPV6_ADDR_LEN                (16)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ����   : SM_ESM_MSG_ID_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : SM��ESM֮���ԭ��
*****************************************************************************/
enum SM_ESM_MSG_ID_ENUM
{
    /* SM->ESM����Ϣԭ�� */
    ID_SM_ESM_PDP_CONTEXT_INFO_IND       = (0x01+PS_MSG_ID_SM_TO_ESM_BASE),     /* _H2ASN_MsgChoice SM_ESM_PDP_CONTEXT_INFO_IND_STRU */

    /* ESM->SM����Ϣԭ�� */
    ID_ESM_SM_EPS_BEARER_INFO_IND        = (0x01+PS_MSG_ID_ESM_TO_SM_BASE),     /* _H2ASN_MsgChoice SM_ESM_EPS_BEARER_INFO_IND_STRU */
    ID_ESM_APS_ESM_NOTIFICATION_IND      = (0x02+PS_MSG_ID_ESM_TO_SM_BASE),     /* _H2ASN_MsgChoice ESM_APS_NOTIFICATION_IND_STRU */

    ID_SM_ESM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 SM_ESM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : SM_ESM_PDP_OPTION_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PDP��EPS BEARER״̬ö��
*****************************************************************************/
enum SM_ESM_PDP_OPTION_ENUM
{
    SM_ESM_PDP_OPT_ACTIVATE             = 0,
    SM_ESM_PDP_OPT_MODIFY                  ,
    SM_ESM_PDP_OPT_DEACTIVATE              ,

    SM_ESM_PDP_OPT_BUTT
};
typedef VOS_UINT32 SM_ESM_PDP_OPTION_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : SM_ESM_PDP_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PDP��ַ����ö��
*****************************************************************************/
enum SM_ESM_PDP_TYPE_ENUM
{
    SM_ESM_PDP_PPP                      = 0,
    SM_ESM_PDP_IPV4                        ,
    SM_ESM_PDP_IPV6                        ,
    SM_ESM_PDP_IPV4V6                      ,

    SM_ESM_PDP_TYPE_BUTT
};
typedef VOS_UINT8 SM_ESM_PDP_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PACKET FILTER����ö��
*****************************************************************************/
enum SM_ESM_TRANSFER_DIRECTION_ENUM
{
    SM_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER           = 0x00,
    SM_ESM_TRANSFER_DIRECTION_DOWNLINK                      = 0x01,
    SM_ESM_TRANSFER_DIRECTION_UPLINK                        = 0x02,
    SM_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK               = 0x03,

    SM_ESM_TRANSFER_DIRECTION_BUTT
};
typedef VOS_UINT8 SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : SM_ESM_BCM_ENUM_UINT8
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : BEARER CONTROL MODEö��
*****************************************************************************/
enum SM_ESM_BCM_ENUM
{
    SM_ESM_BCM_MS_ONLY                  = 0x01,
    SM_ESM_BCM_MS_NW                    = 0x02,

    SM_ESM_BCM_BUTT
};
typedef VOS_UINT8 SM_ESM_BCM_ENUM_UINT8;

/* lihong00150010 ims begin */
/*****************************************************************************
 ö������: SM_ESM_PDP_EMC_IND_ENUM
 ö��˵��: PDP�������Ƿ��������
*****************************************************************************/
enum SM_ESM_PDP_EMC_IND_ENUM
{
    SM_ESM_PDP_NOT_FOR_EMC                 = 0x00,
    SM_ESM_PDP_FOR_EMC                     = 0x01,

    SM_ESM_PDP_EMC_IND_BUTT                = 0xFF
};
typedef VOS_UINT8 SM_ESM_PDP_EMC_IND_ENUM_UINT8;

/*****************************************************************************
 ö����  : SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM
 ö��˵��:
*****************************************************************************/
enum SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM
{
    SM_ESM_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    SM_ESM_PDP_FOR_IM_CN_SIG_ONLY          = 0x01,

    SM_ESM_PDP_IM_CN_SIG_FLAG_BUTT         = 0xFF
};
typedef VOS_UINT8 SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8;

/* lihong00150010 ims end */

/*sunbing 49683 2013-10-14 VoLTE begin*/
enum ESM_APS_NOTIFICATION_IND_ENUM
{
    ESM_APS_NOTIFICATION_IND_SRVCC_HO_CANCELLED         = 0,

    ESM_APS_NOTIFICATION_IND_BUTT
};
typedef VOS_UINT32 ESM_APS_NOTIFICATION_IND_ENUM_UINT32;
/*sunbing 49683 2013-10-14 VoLTE end*/

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
 �ṹ����   : SM_ESM_APN_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.008 section 10.5.6.1 APNΪ�����ֽ�(δ����)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;           /* APN����    */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */
    VOS_UINT8                           aucValue[SM_ESM_MAX_LENGTH_OF_APN];

} SM_ESM_APN_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PDP_ADDR_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.008 section 10.5.6.4 PDP address
              aucIpV4Addr[0]Ϊ��ַ���ֽ�λ��aucIpV4Addr[3]Ϊ��ַ���ֽ�λ
              aucIpV6Addr[0]Ϊ��ַ���ֽ�λ��aucIpV6Addr[15]Ϊ��ַ���ֽ�λ
*****************************************************************************/
typedef struct
{
    SM_ESM_PDP_TYPE_ENUM_UINT8          enPdpType;          /* PDP��ַ���� */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ���  */
    VOS_UINT8                           aucIpV4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[SM_ESM_IPV6_ADDR_LEN];

} SM_ESM_PDP_ADDR_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PDN_ADDR_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.301 section 9.9.4.9 PDN address
              aucIpV4Addr[0]Ϊ��ַ���ֽ�λ��aucIpV4Addr[3]Ϊ��ַ���ֽ�λ
              aucIpV6Addr[0]Ϊ��ַ���ֽ�λ��aucIpV6Addr[15]Ϊ��ַ���ֽ�λ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;           /* PDN��ַ���� */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ���  */
    VOS_UINT8                           aucIpV4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[SM_ESM_IPV6_ADDR_LEN ];

} SM_ESM_PDN_ADDR_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PCO_IPV4_ITEM_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : aucPriDns   - Primary DNS server Address
              aucSecDns   - Secondary DNS server Address
              aucGateWay  - Peer IP address
              aucPriNbns  - Primary WINS DNS address
              aucSecNbns  - Seocndary WINS DNS address
              aucPriPcscf - Primary P-CSCF address
              aucSecPcscf - Seocndary P-CSCF address

              aucGateWay[0]Ϊ��ַ���ֽ�λ��aucGateWay[3]Ϊ��ַ���ֽ�λ
              aucPriNbns[0]Ϊ��ַ���ֽ�λ��aucPriNbns[3]Ϊ��ַ���ֽ�λ
              aucSecNbns[0]Ϊ��ַ���ֽ�λ��aucSecNbns[3]Ϊ��ַ���ֽ�λ
              aucPriPcscf[0]Ϊ��ַ���ֽ�λ��aucPriPcscf[3]Ϊ��ַ���ֽ�λ
              aucSecPcscf[0]Ϊ��ַ���ֽ�λ��aucSecPcscf[3]Ϊ��ַ���ֽ�λ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpGateWay    : 1;
    VOS_UINT32                          bitOpPriNbns    : 1;
    VOS_UINT32                          bitOpSecNbns    : 1;
    VOS_UINT32                          bitOpPriPcscf   : 1;
    VOS_UINT32                          bitOpSecPcscf   : 1;
    VOS_UINT32                          bitOpThiPcscf   : 1;
    VOS_UINT32                          bitOpSpare      : 24;

    VOS_UINT8                           aucPriDns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucGateWay[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPriNbns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPriPcscf[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscf[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscf[SM_ESM_IPV4_ADDR_LEN];

} SM_ESM_PCO_IPV4_ITEM_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PCO_IPV6_ITEM_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : aucPriDns   - Primary DNS server Address
              aucSecDns   - Secondary DNS server Address
              aucPriPcscf - Primary P-CSCF address
              aucSecPcscf - Seocndary P-CSCF address

              aucPriDns[0]Ϊ��ַ���ֽ�λ��aucPriDns[15]Ϊ��ַ���ֽ�λ
              aucSecDns[0]Ϊ��ַ���ֽ�λ��aucSecDns[15]Ϊ��ַ���ֽ�λ
              aucPriPcscf[0]Ϊ��ַ���ֽ�λ��aucPriPcscf[15]Ϊ��ַ���ֽ�λ
              aucSecPcscf[0]Ϊ��ַ���ֽ�λ��aucSecPcscf[15]Ϊ��ַ���ֽ�λ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpPriPcscf   : 1;
    VOS_UINT32                          bitOpSecPcscf   : 1;
    VOS_UINT32                          bitOpThiPcscf   : 1;
    VOS_UINT32                          bitOpSpare      : 27;

    VOS_UINT8                           aucPriDns[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucPriPcscf[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscf[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscf[SM_ESM_IPV6_ADDR_LEN];

} SM_ESM_PCO_IPV6_ITEM_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PDP_QOS_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.008 section 10.5.6.5 Quality of service
              GU NAS�ṩ����QOS����������ֵ��δ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucMaximSduSize;
    VOS_UINT8                           ucMaxBitRateForUp;
    VOS_UINT8                           ucMaxBitRateForDown;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucGuarantBitRateForUp;
    VOS_UINT8                           ucGuarantBitRateForDown;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT8                           ucMaxBitRateForDownExt;
    VOS_UINT8                           ucGuarantBitRateForDownExt;
    VOS_UINT8                           ucMaxBitRateForUpExt;
    VOS_UINT8                           ucGuarantBitRateForUpExt;
    VOS_UINT8                           ucMaxBitRateForDownExt_2;
    VOS_UINT8                           ucGuarantBitRateForDownExt_2;
    VOS_UINT8                           ucMaxBitRateForUpExt_2;
    VOS_UINT8                           ucGuarantBitRateForUpExt_2;

    VOS_UINT8                           aucReserved[1];

} SM_ESM_PDP_QOS_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_EPS_QOS_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.301 section 9.9.4.3 EPS Quality of service
              L NAS�ṩ��QOS��������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQCI;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulULMaxRate ;       /* ��λΪkbps */
    VOS_UINT32                          ulDLMaxRate;        /* ��λΪkbps */
    VOS_UINT32                          ulULGMaxRate;       /* ��λΪkbps */
    VOS_UINT32                          ulDLGMaxRate;       /* ��λΪkbps */

} SM_ESM_EPS_QOS_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.008 section 10.5.6.12 Traffic Flow Template��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask : 1;
    VOS_UINT32                          bitOpProtocolId         : 1;
    VOS_UINT32                          bitOpSingleLocalPort    : 1;
    VOS_UINT32                          bitOpLocalPortRange     : 1;
    VOS_UINT32                          bitOpSingleRemotePort   : 1;
    VOS_UINT32                          bitOpRemotePortRange    : 1;
    VOS_UINT32                          bitOpSecuParaIndex      : 1;
    VOS_UINT32                          bitOpTypeOfService      : 1;
    VOS_UINT32                          bitOpFlowLabelType      : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask : 1;
    VOS_UINT32                          bitOpSpare              : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection;
    VOS_UINT8                           ucPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;             /*Э���*/
    VOS_UINT8                           ucTypeOfService;          /*TOS*/

    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucRmtIpv4Address[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpAddress[0]ΪIP��ַ���ֽ�λ
                                                                    ucSourceIpAddress[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv4Mask[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpMask[0]ΪIP��ַ���ֽ�λ ,
                                                                    ucSourceIpMask[3]Ϊ���ֽ�λ */
    VOS_UINT8                           aucRmtIpv6Address[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Address[0]ΪIPv6�ӿڱ�ʶ���ֽ�λ
                                                                    ucRmtIpv6Address[15]ΪIPv6�ӿڱ�ʶ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv6Mask[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Mask[0]Ϊ���ֽ�λ
                                                                    ucRmtIpv6Mask[15]Ϊ���ֽ�λ*/

    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/
    VOS_UINT8                           aucLocalIpv4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr [SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];

} SM_ESM_PF_STRU;
#else
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask : 1;
    VOS_UINT32                          bitOpProtocolId         : 1;
    VOS_UINT32                          bitOpSingleLocalPort    : 1;
    VOS_UINT32                          bitOpLocalPortRange     : 1;
    VOS_UINT32                          bitOpSingleRemotePort   : 1;
    VOS_UINT32                          bitOpRemotePortRange    : 1;
    VOS_UINT32                          bitOpSecuParaIndex      : 1;
    VOS_UINT32                          bitOpTypeOfService      : 1;
    VOS_UINT32                          bitOpFlowLabelType      : 1;
    VOS_UINT32                          bitOpSpare              : 22;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection;
    VOS_UINT8                           ucPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;             /*Э���*/
    VOS_UINT8                           ucTypeOfService;          /*TOS*/

    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucRmtIpv4Address[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpAddress[0]ΪIP��ַ���ֽ�λ
                                                                    ucSourceIpAddress[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv4Mask[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpMask[0]ΪIP��ַ���ֽ�λ ,
                                                                    ucSourceIpMask[3]Ϊ���ֽ�λ */
    VOS_UINT8                           aucRmtIpv6Address[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Address[0]ΪIPv6�ӿڱ�ʶ���ֽ�λ
                                                                    ucRmtIpv6Address[15]ΪIPv6�ӿڱ�ʶ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv6Mask[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Mask[0]Ϊ���ֽ�λ
                                                                    ucRmtIpv6Mask[15]Ϊ���ֽ�λ*/

    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/

} SM_ESM_PF_STRU;

#endif

/*****************************************************************************
 �ṹ����   : SM_ESM_CID_PF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : CID����PF�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCid;
    SM_ESM_PF_STRU                      stPf;

} SM_ESM_CID_PF_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_TFT_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : TFT�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPfNum;
    SM_ESM_CID_PF_STRU                  astCidPf[SM_ESM_MAX_TFT_PF_NUM];

} SM_ESM_TFT_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_EPS_APN_AMBR_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ��TS 24.008 section 9.9.4.2 APN aggregate maximum bit rate��δ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDLApnAmbrExt   : 1;
    VOS_UINT32                          bitOpULApnAmbrExt   : 1;
    VOS_UINT32                          bitOpDLApnAmbrExt2  : 1;
    VOS_UINT32                          bitOpULApnAmbrExt2  : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucDLApnAmbr;
    VOS_UINT8                           ucULApnAmbr;
    VOS_UINT8                           ucDLApnAmbrExt;
    VOS_UINT8                           ucULApnAmbrExt;
    VOS_UINT8                           ucDLApnAmbrExt2;
    VOS_UINT8                           ucULApnAmbrExt2;

    VOS_UINT8                           aucReserved[2];

} SM_ESM_EPS_APN_AMBR_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_TRANSACTION_ID_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : Transaction ID ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTiFlag;
    VOS_UINT8                           ucTiValue;

    VOS_UINT8                           aucReserved[2];

} SM_ESM_TRANSACTION_ID_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_PDP_CONTEXT_INFO_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : SM -> ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpLinkedNsapi    : 1;
    VOS_UINT32                          bitOpPdpQos         : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpPcoIpv4Item    : 1;
    VOS_UINT32                          bitOpPcoIpv6Item    : 1;
    /* lihong00150010 ims begin */
    VOS_UINT32                          bitOpEmcInd         : 1;
    VOS_UINT32                          bitOpImCnSigalFlag  : 1;
    VOS_UINT32                          bitSpare            : 24;
    /* lihong00150010 ims end */
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption;

    SM_ESM_TRANSACTION_ID_STRU          stTransId;

    VOS_UINT32                          ulNsapi;

    /* �˳��ض�Ӧ��CID��һ��BIT��Ӧһ��CID���ɵ͵���,���磺BIT1����CID 1��BIT32����CID 32 */
    VOS_UINT32                          ulBitCid;

    /* ���μ���,��˳�Ա��Ч */
    VOS_UINT32                          ulLinkedNsapi;

    SM_ESM_PDP_ADDR_STRU                stPdpAddr;
    SM_ESM_PDP_QOS_STRU                 stPdpQos;
    SM_ESM_APN_STRU                     stApn;
    SM_ESM_TFT_STRU                     stTft;
    SM_ESM_PCO_IPV4_ITEM_STRU           stPcoIpv4Item;
    SM_ESM_PCO_IPV6_ITEM_STRU           stPcoIpv6Item;

    /* lihong00150010 ims begin */
    SM_ESM_PDP_EMC_IND_ENUM_UINT8           enEmergencyInd;
    SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8    enImCnSignalFlag;
    VOS_UINT8                           aucReserved[2];
    /* lihong00150010 ims begin */

} SM_ESM_PDP_CONTEXT_INFO_IND_STRU;


/*****************************************************************************
 �ṹ����   : SM_ESM_EPS_BEARER_INFO_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ESM -> SM
              EPS Bearer���κβ���(Activate, Modify, Deactivate), ���EPS�ĳ�����Ϣ
              �а���TI, ���ڴ���Ϣ�б�����д. �����Ϣ�в�Я��TI, SMֱ�Ӷ�������Ϣ
              linked EPS bearer identity (if available) ӳ��Ϊ linked TI;
              PDN address and APN of the default EPS bearer contextӳ��ΪPDP address and APN of the default PDP context;
              TFT of the default EPS bearer contextӳ��Ϊ the TFT of the default PDP context;
              TFTs of the dedicated EPS bearer contexts ӳ��ΪTFTs of the secondary PDP contexts;
              ����������ΪSM_ESM_PDP_OPT_MODIFYʱ��OP��Ϊ0�����ʾ�����´��OP��Ϊ1�����ʾ���´��
              ����Ҫɾ��TFT��Ϣʱ����bitOpPf��Ϊ1��ulPfNum��Ϊ0��
              ��Ҫɾ��DNS��NBNS,P-CSCF����ʱ����Ҫ����ӦOP����Ϊ1����Ӧ��������Ϊȫ0��
              ucLlcSapi��ucRadioPriority��ucPacketFlowId������ĺϷ�����GUģ��SM����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;            /* _H2ASN_Skip */

    VOS_UINT32                          bitOpLinkedEpsbId   : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpApnAmbr        : 1;
    VOS_UINT32                          bitOpTransId        : 1;
    VOS_UINT32                          bitOpNegQos         : 1;
    VOS_UINT32                          bitOpLlcSapi        : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpPcoIpv4Item    : 1;
    VOS_UINT32                          bitOpPcoIpv6Item    : 1;
    VOS_UINT32                          bitOpBcm            : 1;
    /* lihong00150010 ims begin */
    VOS_UINT32                          bitOpEmcInd         : 1;
    VOS_UINT32                          bitOpImCnSigalFlag  : 1;
    /* lihong00150010 ims end */
    VOS_UINT32                          bitOpErrorCode      : 1;
    VOS_UINT32                          bitOpSpare          : 16;

    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption;

    /* EPS bearer identityӳ��ΪNSAPI */
    VOS_UINT32                          ulEpsbId;

    /* �˳��ض�Ӧ��CID��һ��BIT��Ӧһ��CID���ɵ͵���,���磺BIT1����CID 1��BIT32����CID 32 */
    VOS_UINT32                          ulBitCid;

    /* ��˳��ع�����EPS����ID */
    VOS_UINT32                          ulLinkedEpsbId;

    SM_ESM_PDN_ADDR_STRU                stPdnAddr;
    SM_ESM_EPS_APN_AMBR_STRU            stEpsApnAmbr;
    SM_ESM_EPS_QOS_STRU                 stEpsQos;
    SM_ESM_TFT_STRU                     stTft;
    SM_ESM_APN_STRU                     stApn;
    SM_ESM_PDP_QOS_STRU                 stNegQos;
    SM_ESM_PCO_IPV4_ITEM_STRU           stPcoIpv4Item;
    SM_ESM_PCO_IPV6_ITEM_STRU           stPcoIpv6Item;

    SM_ESM_TRANSACTION_ID_STRU          stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    SM_ESM_BCM_ENUM_UINT8               enBcm;

    /* lihong00150010 ims begin */
    SM_ESM_PDP_EMC_IND_ENUM_UINT8           enEmergencyInd;
    SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8    enImCnSignalFlag;
    VOS_UINT8                           aucReserved[2];
    /* lihong00150010 ims begin */
    
    VOS_UINT32                          ulErrorCode;   /* �յ�����ԭ��ֵ��֪ͨSM�Ĵ����� */
} SM_ESM_EPS_BEARER_INFO_IND_STRU;

/*sunbing 49683 2013-10-14 VoLTE begin*/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                              ulMsgId;        /* _H2ASN_Skip */
    ESM_APS_NOTIFICATION_IND_ENUM_UINT32    enNotificationIndicator;
}ESM_APS_NOTIFICATION_IND_STRU;
/*sunbing 49683 2013-10-14 VoLTE end*/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    SM_ESM_MSG_ID_ENUM_UINT32           ulMsgId;            /* _H2ASN_MsgChoice_Export SM_ESM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          SM_ESM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} SM_ESM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    SM_ESM_INTERFACE_MSG_DATA           stMsgData;
} SmEsmInterface_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
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
