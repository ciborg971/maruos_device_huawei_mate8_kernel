
#ifndef __APSNDINTERFACE_H__
#define __APSNDINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "PsTypeDef.h"
#include "mdrv.h"
#include "LPSCommon.h"
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define  APS_ND_MSG_HDR                     (PS_MSG_ID_APS_TO_ND_BASE)
#define  ND_APS_MSG_HDR                     (PS_MSG_ID_ND_TO_APS_BASE)



#define APS_NDCLIENT_IPV6_IFID_LENGTH         (8)
#define NDCLIENT_APS_IPV6_ADDR_LENGTH         (16)
#define NDCLIENT_APS_MAX_PREFIX_NUM_IN_RA     (6)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
ö����    : APS_NDCLIENT_MSG_TYPE_ENUM
Э����  :
ASN.1���� :
�ṹ˵��  : APS��ND CLIENT֮�����ϢID����
*****************************************************************************/
enum APS_NDCLIENT_MSG_TYPE_ENUM
{
    /* APS����NDCLIENT��ԭ�� */
    ID_APS_NDCLIENT_PDP_ACT_IND          = (APS_ND_MSG_HDR + 0x00),
    ID_APS_NDCLIENT_PDP_DEACT_IND        = (APS_ND_MSG_HDR + 0x01),
    ID_APS_NDCLIENT_REL_IND              = (APS_ND_MSG_HDR + 0x02),

    /* NDCLIENT����APS��ԭ�� */
    ID_NDCLIENT_APS_PARA_INFO_NOTIFY     = (ND_APS_MSG_HDR + 0x00),

    ID_APS_NDCLIENT_MSG_TYPE_BUTT
};
typedef VOS_UINT32  APS_NDCLIENT_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APS_NDCLIENT_PDP_ACT_IND
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6���͵�PDP����ָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ */        /*_H2ASN_Skip*/
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32       ulMsgId;            /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT8                               ucRabId;            /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                               aucRev[3];
    /*IPv6�ӿڱ�ʾ������������䣬����UE IPv6 Link local ��ַ������,aucIpv6InterfacId[0]Ϊ�ӿڱ�ʾ�����ֽ�,aucIpv6InterfacId[7]Ϊ�ӿڱ�ʾ�����ֽڣ�0,0,0,0,0,0,0,0Ϊ��Ч�ӿڱ�ʾ��*/
    VOS_UINT8                               aucIpv6InterfacId[APS_NDCLIENT_IPV6_IFID_LENGTH];
} APS_NDCLIENT_PDP_ACT_IND;

/*****************************************************************************
 �ṹ��    : APS_NDCLIENT_PDP_DEACT_IND
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6���͵�PDPȥ����ָʾ�ṹ
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   APS_NDCLIENT_MSG_TYPE_ENUM_UINT32    ulMsgId;            /*_H2ASN_Skip*/
   VOS_UINT8                            ucRabId;
   VOS_UINT8                            aucRev[3];
} APS_NDCLIENT_PDP_DEACT_IND;

/*****************************************************************************
 �ṹ��    : APS_NDCLIENT_REL_IND
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ�����ʵ����Դָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
} APS_NDCLIENT_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : NDCLIENT_APS_IPV6_PREFIX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6ǰ׺��Ϣָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[NDCLIENT_APS_IPV6_ADDR_LENGTH];
}NDCLIENT_APS_IPV6_PREFIX_STRU;

/*****************************************************************************
 �ṹ��    : NDCLIENT_APS_IPV6_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6������Ϣָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :31;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :22;

    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    NDCLIENT_APS_IPV6_PREFIX_STRU       astPrefixList[NDCLIENT_APS_MAX_PREFIX_NUM_IN_RA];
} NDCLIENT_APS_IPV6_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NDCLIENT_APS_PARA_INFO_NOTIFY
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ND CLIENT��APS�ϱ�IPV6��Ϣָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32   ulMsgId;

    VOS_UINT8                           ucRabId;            /* ���غ�*/
    VOS_UINT8                           aucRev[3];          /* ��Ϣ�ṹ�����*/

    NDCLIENT_APS_IPV6_INFO_STRU         stIpv6Info;
} NDCLIENT_APS_PARA_INFO_NOTIFY_STRU;

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

#endif /* end of ApsNdInterface.h */

