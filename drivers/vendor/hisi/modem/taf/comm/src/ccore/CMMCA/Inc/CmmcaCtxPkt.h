/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CmmcaCtxPkt.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��1��13��
  ����޸�   :
  ��������   : CmmcaCtxPkt.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��13��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CMMCACTXPKT_H__
#define __CMMCACTXPKT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* APN�ַ�������󳤶� */
#define CMMCA_APN_LEN_MAX                                   (99)

/* IPV4��ַ���� */
#define CMMCA_IPV4_ADDR_LEN                                 (4)

/* IPV6��ַ���� */
#define CMMCA_IPV6_ADDR_LEN                                 (16)

/* IPV6 interface id�ĳ��� */
#define CMMCA_IPV6_INTERFACE_ID_BYTE_LEN                    (8)
#define CMMCA_IPV6_INTERFACE_ID_BIT_LEN                     (64)

/* IPV6 ǰ׺�ĳ��� */
#define CMMCA_IPV6_PREFIX_BYTE_LEN                          (8)
#define CMMCA_IPV6_PREFIX_BIT_LEN                           (64)

/* ֧�ֵĵ�ַ������ */
#define CMMCA_SUPPORTED_ADDR_NUM_MAX                        (4)

/* Ӧ��֧�ֵ�PDN���� */
#define CMMCA_SUPPORTED_PDN_NUM_MAX                         (4)

/* ĿǰӦ�����֧��4��PDN,Ϊ��֧��CMMC˫ջ����,CMMCA�����PDNʵ�������2 */
#define CMMCA_PDN_CONN_ENTITY_NUM_MAX                       (2 * CMMCA_SUPPORTED_PDN_NUM_MAX)

/* PDN����ʵ��index��Чֵ */
#define CMMCA_PDN_CONN_ENTITY_INDEX_INVALID                 (0xFF)

/* PDN ID�����ֵ */
#define CMMCA_PDN_ID_MAX                                    (20)

/* PDN ID����Сֵ*/
#define CMMCA_PDN_ID_MIN                                    (1)

/* PDN ID����Чֵ */
#define CMMCA_PDN_ID_INVALID                                (0xFF)

/* PDN ID��Ч���ж� */
#define CMMCA_IS_VALID_PDN_ID(ucPdnId)\
    (((ucPdnId) >= CMMCA_PDN_ID_MIN) && ((ucPdnId) <= CMMCA_PDN_ID_MAX))

/* PDN TYPE��Ч���ж� */
#define CMMCA_IS_VALID_PDN_TYPE(ucPdnType)\
    (((ucPdnType) >= CMMCA_IP_TYPE_IPV4) && ((ucPdnType) <= CMMCA_IP_TYPE_IPV4V6))

/* PDN ����������Ч���ж� */
#define CMMCA_IS_VALID_PDN_REQUEST_TYPE(ucRequestType)\
    ((CMMCA_PDN_REQUEST_TYPE_INITIAL == (ucRequestType)) || (CMMCA_PDN_REQUEST_TYPE_HANDOVER == (ucRequestType)))

/* APN�ַ���Ч���ж� */
#define CMMCA_IS_VALID_APN_CHAR(ucApnCharacter)\
    ((('A' <= (ucApnCharacter)) && ('Z' >= (ucApnCharacter))) \
    || (('a' <= (ucApnCharacter)) && ('z' >= (ucApnCharacter))) \
    || (('0' <= (ucApnCharacter)) && ('9' >= (ucApnCharacter))) \
    || ('-' == (ucApnCharacter)) \
    || ('.' == (ucApnCharacter)))

/* APN��β�ַ���Ч���ж� */
#define CMMCA_IS_VALID_APN_FIRST_AND_LAST_CHAR(ucApnCharacter)\
    ((('A' <= (ucApnCharacter)) && ('Z' >= (ucApnCharacter))) \
    || (('a' <= (ucApnCharacter)) && ('z' >= (ucApnCharacter))) \
    || (('0' <= (ucApnCharacter)) && ('9' >= (ucApnCharacter))))



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum CMMCA_IP_TYPE_ENUM
{
    CMMCA_IP_TYPE_IPV4                  = 0x01,
    CMMCA_IP_TYPE_IPV6                  = 0x02,
    CMMCA_IP_TYPE_IPV4V6                = 0x03,

    CMMCA_IP_TYPE_BUTT
};

typedef VOS_UINT8 CMMCA_IP_TYPE_ENUM_UINT8;


enum CMMCA_PDN_REQUEST_TYPE_ENUM
{
    CMMCA_PDN_REQUEST_TYPE_INITIAL      = 0x01,
    CMMCA_PDN_REQUEST_TYPE_HANDOVER     = 0x03,

    CMMCA_PDN_REQUEST_TYPE_BUTT
};

typedef VOS_UINT8 CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8;


enum CMMCA_PDP_STATE_ENUM
{
    CMMCA_PDP_STATE_INACTIVE            = 0,
    CMMCA_PDP_STATE_ACTIVE              = 1,

    CMMCA_PDP_STATE_BUTT
};
typedef VOS_UINT8  CMMCA_PDP_STATE_ENUM_UINT8;


enum CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM
{
    CMMCA_PDN_SEL_BEARER_CTRL_MODE_UE            = 1,
    CMMCA_PDN_SEL_BEARER_CTRL_MODE_NW_AND_UE     = 2,

    CMMCA_PDN_SEL_BEARER_CTRL_MODE_BUTT
};
typedef VOS_UINT8  CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM_UINT8;


enum CMMCA_CONN_STATUS_ENUM
{
    CMMCA_CONN_STATUS_CONNING,
    CMMCA_CONN_STATUS_CONNED,
    CMMCA_CONN_STATUS_DISCING,
    CMMCA_CONN_STATUS_INTERNAL_DISCING,                                         /* RA��ʱ���ڲ�ȥ���� */
    CMMCA_CONN_STATUS_BUTT
};
typedef VOS_UINT8  CMMCA_CONN_STATUS_ENUM_UINT8;




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

typedef struct
{
    CMMCA_IP_TYPE_ENUM_UINT8            enIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[CMMCA_IPV6_ADDR_LEN];
}CMMCA_IP_ADDRESS_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPriDns   : 1;
    VOS_UINT32                          bitOpSecDns   : 1;
    VOS_UINT32                          bitOpSpare    : 30;

    VOS_UINT8                           aucPriDns[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_IPV4_DNS_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_IPV4_PCSCF_STRU;


typedef struct
{
    VOS_UINT32                          bitOpGateWayAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           aucGateWayAddr[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_GATEWAY_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[CMMCA_IPV6_ADDR_LEN];
}CMMCA_PDP_IPV6_DNS_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[CMMCA_IPV6_ADDR_LEN];
}CMMCA_PDP_IPV6_PCSCF_STRU;



typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpSpare          : 24;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucReserved;

    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
}CMMCA_SEL_SDF_PARA_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;                                  /* Cid */
    VOS_UINT8                           ucRabId;                                /* RabId */
    CMMCA_PDP_STATE_ENUM_UINT8          enPdpState;                             /* PDP ״̬:���δ���� */
    VOS_UINT8                           aucReserved1[1];

    CMMCA_IP_ADDRESS_STRU               stPdpAddr;

    CMMCA_PDP_GATEWAY_STRU              stPdpGateWay;                           /* IPV4 Gateway��Ϣ */
    CMMCA_PDP_IPV4_DNS_STRU             stPdpIpv4Dns;                           /* IPV4 DNS��Ϣ */
    CMMCA_PDP_IPV4_PCSCF_STRU           stPdpIpv4Pcscf;                         /* IPV4 P-CSCF��Ϣ */

    VOS_UINT8                           aucPdpIpv6IfId[CMMCA_IPV6_INTERFACE_ID_BYTE_LEN];   /* IPV6 Interface id��Ϣ */

    CMMCA_PDP_IPV6_DNS_STRU             stPdpIpv6Dns;                           /* IPV6 DNS��Ϣ */
    CMMCA_PDP_IPV6_PCSCF_STRU           stPdpIpv6Pcscf;                         /* IPV6 P-CSCF��Ϣ */
}CMMCA_PDP_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucUsedFlg;                              /* ʵ������־ */

    VOS_UINT8                           ucPdnId;                                /* �����PDN ID */
    CMMCA_IP_TYPE_ENUM_UINT8            enUserPdnType;                          /* �����PDN���� */
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enPdnReqType;                           /* �����request type */

    CMMCA_CONN_STATUS_ENUM_UINT8        enConnStatus;                           /* ��¼����״̬ */

    VOS_UINT8                           aucReserved[3];

    CMMCA_SEL_SDF_PARA_STRU             stSelSdfPara;                           /* ѡ�в��ŵ�SDF��Ϣ */

    CMMCA_PDP_INFO_STRU                 stPdpInfo;
}CMMCA_PDN_CONN_ENTITY_STRU;


typedef struct
{
    /* �����PDN������ʵ������ */
    VOS_UINT8                           aucPdnToIndexTbl[CMMCA_PDN_ID_MAX + 1];

    VOS_UINT8                           aucReserved[3];

    /* PDNʵ�� */
    CMMCA_PDN_CONN_ENTITY_STRU          astPdnConnEntity[CMMCA_PDN_CONN_ENTITY_NUM_MAX];
}CMMCA_PKT_CTX_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/



VOS_VOID CMMCA_PKT_InitCtx(VOS_VOID);

CMMCA_PKT_CTX_STRU* CMMCA_PKT_GetCtxAddr(VOS_VOID);

CMMCA_PDN_CONN_ENTITY_STRU* CMMCA_PKT_GetPdnEntityAddr(
    VOS_UINT8                           ucIndex
);

CMMCA_CONN_STATUS_ENUM_UINT8 CMMCA_PKT_GetConnStatus(
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_SetConnStatus(
    VOS_UINT8                           ucIndex,
    CMMCA_CONN_STATUS_ENUM_UINT8        enConnStatus
);

VOS_VOID CMMCA_PKT_SetUserPdnType(
    VOS_UINT8                           ucIndex,
    CMMCA_IP_TYPE_ENUM_UINT8            enPdnType
);

CMMCA_IP_TYPE_ENUM_UINT8 CMMCA_PKT_GetUserPdnType(
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_SetPdnRequestType(
    VOS_UINT8                           ucIndex,
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enPdnReqType
);

VOS_VOID CMMCA_PKT_SavePdpInfo(
   CMMCA_PDP_INFO_STRU                *pstPdpInfo,
   TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
);

VOS_VOID CMMCA_PKT_SaveIpv6RaInfo(
    CMMCA_PDP_INFO_STRU                *pstPdpInfo,
    TAF_PS_IPV6_INFO_IND_STRU          *pstIpv6InfoInd
);

VOS_VOID CMMCA_PKT_FreePdnConnEntity(
    VOS_UINT8                           ucPdnId
);

VOS_UINT8 CMMCA_PKT_FindPdnConnEntityIndex(
    VOS_UINT8                           ucPdnId
);

VOS_VOID CMMCA_PKT_SavePdnConnEntityIndex(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_AssignPdnConnEntity(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucIndex
);


#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CmmcaCtxPkt.h */

