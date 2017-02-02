




#ifndef __NASIPINTERFACE_H__
#define __NASIPINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "PsTypeDef.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack(4)
#else
 #pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_IP_IPV6_IFID_LENGTH         (8)
#define NAS_IP_IPV6_ADDR_LENGTH         (16)
#define NAS_IP_IPV4_ADDR_LENGTH         (4)
#define NAS_IP_MAX_DNS_SERVER_NUM       (2)




#define ESM_IP_MSG_HDR                  (PS_MSG_ID_NAS_TO_IP_BASE)
#define IP_ESM_MSG_HDR                  (PS_MSG_ID_IP_TO_NAS_BASE)
#define RABM_IP_MSG_HDR                 (PS_MSG_ID_NAS_TO_IP_BASE + 0x08)
#define IP_RABM_MSG_HDR                 (PS_MSG_ID_IP_TO_NAS_BASE + 0x08)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_IP_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��IP����Ϣԭ������
*****************************************************************************/
enum NAS_IP_MSG_ID_ENUM
{
    /* ESM����IP��ԭ�� */
    ID_ESM_IP_START_REQ                 = (ESM_IP_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice ESM_IP_START_REQ_STRU */
    ID_ESM_IP_STOP_REQ                  = (ESM_IP_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice ESM_IP_STOP_REQ_STRU */
    ID_ESM_IP_CONFIG_PARA_REQ           = (ESM_IP_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice ESM_IP_CONFIG_PARA_REQ_STRU */
    ID_ESM_IP_PDP_RELEASE_IND           = (ESM_IP_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice ESM_IP_PDP_RELEASE_IND_STRU */
    ID_ESM_IP_REL_IND                   = (ESM_IP_MSG_HDR + 0x04),  /* _H2ASN_MsgChoice ESM_IP_REL_IND_STRU */
    ID_ESM_IP_NW_PARA_IND               = (ESM_IP_MSG_HDR + 0x05),  /* _H2ASN_MsgChoice ESM_IP_NW_PARA_IND_STRU */

    /* IP����ESM��ԭ�� */
    ID_ESM_IP_START_CNF                 = (IP_ESM_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice ESM_IP_START_CNF_STRU */
    ID_ESM_IP_STOP_CNF                  = (IP_ESM_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice ESM_IP_STOP_CNF_STRU */
    ID_ESM_IP_STATE_IND                 = (IP_ESM_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice ESM_IP_STATE_IND_STRU */
    ID_ESM_IP_CONFIG_PARA_IND           = (IP_ESM_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice ESM_IP_CONFIG_PARA_IND_STRU */

    /* RABM����IP��ԭ�� */
    ID_IP_RABM_START_FILTER_CNF         = (RABM_IP_MSG_HDR + 0x00), /* _H2ASN_MsgChoice IP_RABM_START_FILTER_CNF_STRU */
    ID_IP_RABM_STOP_FILTER_CNF          = (RABM_IP_MSG_HDR + 0x01), /* _H2ASN_MsgChoice IP_RABM_STOP_FILTER_CNF_STRU */
    ID_IP_RABM_DATA_IND                 = (RABM_IP_MSG_HDR + 0x02), /* _H2ASN_MsgChoice IP_RABM_DATA_IND_STRU */

    /* IP����RABM��ԭ�� */
    ID_IP_RABM_START_FILTER_REQ         = (IP_RABM_MSG_HDR + 0x00), /* _H2ASN_MsgChoice IP_RABM_START_FILTER_REQ_STRU */
    ID_IP_RABM_STOP_FILTER_REQ          = (IP_RABM_MSG_HDR + 0x01), /* _H2ASN_MsgChoice IP_RABM_STOP_FILTER_REQ_STRU */

    ID_NAS_IP_MSG_ID_BUTT
};
typedef VOS_UINT32   NAS_IP_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_IP_DHCPV4_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : DHCPV4ʹ�ñ�ʶ
*****************************************************************************/
enum NAS_IP_DHCPV4_FLAG_ENUM
{
    NAS_IP_DHCPV4_NOT_USED              = 0x00,
    NAS_IP_DHCPV4_USED                  = 0x01,
    NAS_IP_DHCPV4_BUTT
};
typedef VOS_UINT32 NAS_IP_DHCPV4_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_IP_ICMPV6_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ICMPV6ʹ�ñ�ʶ
*****************************************************************************/
enum NAS_IP_ICMPV6_FLAG_ENUM
{
    NAS_IP_ICMPV6_NOT_USED              = 0x00,
    NAS_IP_ICMPV6_USED                  = 0x01,
    NAS_IP_ICMPV6_BUTT
};
typedef VOS_UINT32 NAS_IP_ICMPV6_FLAG_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_IP_STATE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IP״̬ö��
*****************************************************************************/
enum NAS_IP_STATE_TYPE_ENUM
{
    NAS_IP_STATE_TYPE_FOURTH_DISCOVER_EXPIRE    = 1,
    NAS_IP_STATE_TYPE_FOURTH_REQUEST_EXPIRE     = 2,
    NAS_IP_STATE_TYPE_T1_EXPIRE                 = 3,
    NAS_IP_STATE_TYPE_T2_EXPIRE                 = 4,
    NAS_IP_STATE_TYPE_T_EXPIRE                  = 5,
    NAS_IP_STATE_TYPE_BUTT
};
typedef VOS_UINT32  NAS_IP_STATE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_IP_FILTER_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ݰ���������ö��
*****************************************************************************/
enum NAS_IP_FILTER_TYPE_ENUM
{
    NAS_IP_FILTER_TYPE_DHCPV4          = 0x00,
    NAS_IP_FILTER_TYPE_ICMPV6          = 0x01,
    NAS_IP_FILTER_TYPE_BUTT
};
typedef VOS_UINT32 NAS_IP_FILTER_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_IP_FILTER_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��IP���صĽ��ö��
*****************************************************************************/
enum NAS_IP_RESULT_ENUM
{
    NAS_IP_RESULT_SUCCESS              = 0x00,
    NAS_IP_RESULT_FAIL                 = 0x01,
    NAS_IP_RESULT_BUTT
};
typedef VOS_UINT32 NAS_IP_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_IP_IP_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IP����ö��
*****************************************************************************/
enum NAS_IP_IP_TYPE_ENUM
{
    NAS_IP_IP_TYPE_IPV4                 = 0x01,
    NAS_IP_IP_TYPE_IPV6                 = 0x02,
    NAS_IP_IP_TYPE_IPV4_IPV6            = 0x03,

    NAS_IP_IP_TYPE_BUTT
};
typedef VOS_UINT8 NAS_IP_IP_TYPE_ENUM_8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : ESM_IP_CONFIG_PARA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_CONFIG_PARA_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /*ָʾ�Ƿ���DHCPv4����ȡIPv4������0��ʾ����DHCPv4����ȡIPv4������1��ʾ��DHCPv4����ȡIPv4����*/
    NAS_IP_DHCPV4_FLAG_ENUM_UINT32      enDhcpv4Flag;

    /*IPV4��ʽ��IP��ַ��aucIpv4Addr[0]ΪIP��ַ���ֽ�λ��aucIpv4Addr[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucIpv4Addr[NAS_IP_IPV4_ADDR_LENGTH];

    /*ָʾ�Ƿ���ICMPv6����ȡIPv6������0��ʾ����ICMPv6����ȡIPv6������1��ʾ��ICMPv6����ȡIPv6����*/
    NAS_IP_ICMPV6_FLAG_ENUM_UINT32      enIcmpv6Flag;

    /*IPv6�ӿڱ�ʾ������������䣬����UE IPv6 Link local ��ַ������,aucIpv6InterfacId[0]Ϊ�ӿڱ�ʾ�����ֽ�,aucIpv6InterfacId[7]Ϊ�ӿڱ�ʾ�����ֽڣ�0,0,0,0,0,0,0,0Ϊ��Ч�ӿڱ�ʾ��*/
    VOS_UINT8                           aucIpv6InterfacId[NAS_IP_IPV6_IFID_LENGTH];
} ESM_IP_CONFIG_PARA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_IP_IP_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP��ַ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[NAS_IP_IPV4_ADDR_LENGTH];
    VOS_UINT8                           aucIpV6Addr[NAS_IP_IPV6_ADDR_LENGTH];
}NAS_IP_IP_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : NAS_IP_DNS_SER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DNS���������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDnsSerNum;        /*DNS����������*/
    VOS_UINT8                           aucReserved[3];
    NAS_IP_IP_ADDR_STRU                 astDnsServer[NAS_IP_MAX_DNS_SERVER_NUM];
}NAS_IP_DNS_SER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_IP_IPV6_PREFIX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6ǰ׺���ݽṹ
*****************************************************************************/
typedef struct
{
    /*Global��ַǰ׺��Чbitλ�ĳ���*/
    VOS_UINT32                          ulGlobalPrefixLength;

    /*Global��ַǰ׺��aucIpv6AddrPrefix[0]Ϊǰ׺�ĸ��ֽ�λ����Чλ����*/
    VOS_UINT8                            aucIpv6AddrPrefix[NAS_IP_IPV6_IFID_LENGTH];
}NAS_IP_IPV6_PREFIX_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_CONFIG_PARA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_CONFIG_PARA_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpIpv4Addr                     : 1;
    VOS_UINT32                          bitOpDnsServer                    : 1;
    VOS_UINT32                          bitOpIpv6Prefix                   : 1;
    VOS_UINT32                          bitOpSpare                        : 29;

    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /*ͨ��DHCP��õ�IPV4��ʽ��IP��ַ��aucIpv4Addr[0]ΪIP��ַ���ֽ�λ��aucIpv4Addr[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucIpv4Addr[NAS_IP_IPV4_ADDR_LENGTH];

    /* DNS������ */
    NAS_IP_DNS_SER_STRU                 stDnsServer;

    /* ȫ��IPv6��ַǰ׺ */
    NAS_IP_IPV6_PREFIX_STRU             stIpv6Prefix;
} ESM_IP_CONFIG_PARA_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_PDP_RELEASE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_PDP_RELEASE_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
   VOS_UINT8                            ucEpsbId;
   VOS_UINT8                            aucRev[3];
} ESM_IP_PDP_RELEASE_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_STATE_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /* IPģ��״̬ */
    NAS_IP_STATE_TYPE_ENUM_UINT32       enIpState;
} ESM_IP_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_START_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_START_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_START_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
} ESM_IP_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_STOP_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_STOP_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
} ESM_IP_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_REL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_REL_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : IP_RABM_START_FILTER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP_RABM_START_FILTER_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_FILTER_TYPE_ENUM_UINT32      enFilterType;
} IP_RABM_START_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IP_RABM_START_FILTER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP_RABM_START_FILTER_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_RESULT_ENUM_UINT32           enRslt;
} IP_RABM_START_FILTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : IP_RABM_STOP_FILTER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP_RABM_STOP_FILTER_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_FILTER_TYPE_ENUM_UINT32      enFilterType;
} IP_RABM_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IP_RABM_STOP_FILTER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP_RABM_STOP_FILTER_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_RESULT_ENUM_UINT32           enRslt;
} IP_RABM_STOP_FILTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : ESM_IP_NW_PARA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ESM_IP_NW_PARA_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpIpAddr         : 1;
    VOS_UINT32                          bitOpSubnetMask     : 1;
    VOS_UINT32                          bitOpGateWay        : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucEpsbId;           /* ���غ�*/
    VOS_UINT8                           aucRev[3];          /* ��Ϣ�ṹ�����*/

    NAS_IP_IP_ADDR_STRU                 stIpAddr;           /* IP��ַ */
    NAS_IP_IP_ADDR_STRU                 stSubnetMask;       /* �������� */
    NAS_IP_IP_ADDR_STRU                 stGateWay;          /* Ĭ������ */
    NAS_IP_DNS_SER_STRU                 stDnsServer;        /* DNS�������б� */
} ESM_IP_NW_PARA_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_IP_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS_IP_MSG_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpMsgSize;
    VOS_UINT8                           aucIpMsg[4];
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}NAS_IP_MSG_STRU;

/*****************************************************************************
 �ṹ��    : IP_RABM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP_RABM_DATA_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /* DHCPv4�� */
    NAS_IP_MSG_STRU                     stIpMsg;
} IP_RABM_DATA_IND_STRU;


typedef struct
{
    NAS_IP_MSG_ID_ENUM_UINT32           enMsgID;            /*_H2ASN_MsgChoice_Export NAS_IP_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_IP_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_IP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    NAS_IP_MSG_DATA                     stMsgData;
} NasIpInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/*****************************************************************************
 Function Name   : IP_IsDhcpv4ServerPacket
 Description     : �ж��Ƿ�ΪDHCPV4 SERVER��
 Input           : pucIpMsg---------------------IP���ݰ��׵�ַ
                   ulIpMsgLen-------------------IP���ݰ�����
 Output          : VOS_VOID
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-11-29  Draft Enact

*****************************************************************************/
extern VOS_UINT32 IP_IsDhcpv4ServerPacket
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen
);
extern VOS_INT32  IP_PrintEsmIpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IP_PrintRabmIpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

/*****************************************************************************
  9 OTHERS
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

#endif /* end of NasIpInterface.h */
