/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : TAf_ApsForTafm.h
  Author      : ��³��
  Version     : V200R001
  Date        : 2005-0
  Description : ��ͷ�ļ�������---
  History     :
  1. Date:2005-0 -
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by ��³�� FOR A32D02144
  3. 2006-02-28 delete by ��³�� FOR A32D02268
  4. 2006-08-09 modify by J60010247 for A32D03479
************************************************************************/

#ifndef _TAF_APSFORTAFM_H_
#define _TAF_APSFORTAFM_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"
#include "PppInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)     �����ֽڶ��뷽ʽ
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 �궨��
  #define
*****************************************************************************/

#ifndef TAF_APS_SUCC
#define TAF_APS_SUCC                            0
#endif

#ifndef TAF_APS_FAIL
#define TAF_APS_FAIL                            1
#endif



#define TAF_PS_PARA_VALID                   0
#define TAF_PS_PARA_INVALID                 1

#define TAF_CID_LEN                         1
#define TAF_ACTTYPE_LEN                     1

#define TAF_CGACT_DEACT                     0
#define TAF_CGACT_ACT                       1

#define TAF_ACT_DFLT_CID                    0
#define TAF_ACT_ALL_CID                     0xFF
#define TAF_DEACT_ALL_CID                   0xFF



#define TAF_PPP_HEADER_LEN                  20
#define TAF_PPP_IPCP_MAX_LEN                100     /*2��DNS��2��NetBiosDns,1��IP*/
#define TAF_CID_PDPTYPE_LEN                 2


#define TAF_CGACT_ORDER_VALID(ucOrder) ((TAF_CGACT_DEACT        == (ucOrder))\
                                    ||  (TAF_CGACT_ACT          == (ucOrder)))

#define TAF_PS_PDP_CONTEXT_CID_VALID(ucCid) (ucCid <= TAF_MAX_CID)

#define TAF_PS_CID_VALID(ucCid)        ((1 <= ucCid) && (ucCid <= TAF_MAX_CID))

#define TAF_PS_OPID_VALID(OpId)        (OpId <= 134)

#define TAF_PDPTYPE_VALID(PdpType)     ((TAF_PDP_IPV4           == PdpType )    \
                                    ||  (TAF_PDP_IPV6           == PdpType )    \
                                    ||  (TAF_PDP_IPV4V6         == PdpType )    \
                                    ||  (TAF_PDP_PPP            == PdpType ))

#define TAF_PDP_D_COMP_VALID(PdpDcomp) ((TAF_PDP_D_COMP_OFF     == PdpDcomp)    \
                                    ||  (TAF_PDP_D_COMP_ON      == PdpDcomp)    \
                                    ||  (TAF_PDP_D_COMP_V42     == PdpDcomp))

#define TAF_PDP_H_COMP_VALID(PdpHcomp) ((TAF_PDP_H_COMP_OFF     == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_ON      == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_RFC1144 == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_RFC2507 == PdpHcomp))


#define TAF_PS_QOS_TRAFFICCLASS_VALID(QosTrafficClass)  ((QosTrafficClass <= 4))

#define TAF_PS_QOS_DELIVERORDER_VALID(DeliverOrder)     ((DeliverOrder <= 2))

#define TAF_PS_QOS_DELIVERERRSDU_VALID(DeliverErrSdu)   ((DeliverErrSdu <= 3))

#define TAF_PS_QOS_MAXSDUSIZE_VALID(MaxSduSize)         ((MaxSduSize <= 1520))

#define TAF_PS_QOS_MUXBITUL_VALID(MaxBitUl)             ((MaxBitUl <= 256000))

#define TAF_PS_QOS_MUXBITDL_VALID(MaxBitDl)             ((MaxBitDl <= 256000))

#define TAF_PS_QOS_RESIDUALBER_VALID(ResidualBer)       ((ResidualBer <= 9))

#define TAF_PS_QOS_SDUERRRATIO_VALID(SduErrRatio)       ((SduErrRatio <= 7))

#define TAF_PS_QOS_TRANSDELAY_VALID(TransDelay)         ((TransDelay <= 4100))

#define TAF_PS_QOS_TRAFFHANDLEPRIOR_VALID(TraffHandlePrior) ((TraffHandlePrior <= 3))

#define TAF_PS_QOS_GUARANTBITUL_VALID(GuarantBitUl)     ((GuarantBitUl <= 256000))

#define TAF_PS_QOS_GUARANTBITDL_VALID(GuarantBitDl)     ((GuarantBitDl <= 256000))




#define TAF_PS_INFO_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_INFO, String)
#define TAF_PS_NORM_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String)
#define TAF_PS_WARN_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_WARNING, String)
#define TAF_PS_ERR_LOG(String)          TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_ERROR, String)

#define TAF_PDP_AUTH_VALID(AUTH)       ((TAF_PDP_ACTIVATE_NO_AUTH == AUTH) || (TAF_PDP_ACTIVATE_AUTH == AUTH))

/*PCO�������ܰ�����IPCP���ĸ���,ref to Q*/
#define APS_PCO_MAX_IPCP_PKT_NUM        (4)

/*PCOͷ�ĳ���*/
#define APS_PCO_CONFIG_HDR_LEN          (4)

/*IP��ַ����*/
#define APS_PPP_IP_ADDR_LEN             (6)

/*��NBNS��ַ����*/
#define APS_PPP_PRI_NBNS_LEN            (6)

/*��DNS��ַ����*/
#define APS_PPP_PRI_DNS_LEN             (6)

/*��NBNS��ַ����*/
#define APS_PPP_SEC_NBNS_LEN            (6)

/*��NBNS��ַ����*/
#define APS_PPP_SEC_DNS_LEN             (6)




/*******************************************************************************
  3 ö�ٶ���
  typedef enum
{
    ģ����_��������_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2
    MAPS_TEMPLATE_BUTT,    �����ͳһ��BUTT����Ϊ���һ��ö��ֵ��
}MAPS_TEMPLATE_ENUM;   ģ����_ö����������_ENUM
*******************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
extern VOS_UINT8* pgucMapsTemplateBuffer;   ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ��������������
*****************************************************************************/

/*****************************************************************************
  5 UNION����
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  6 STRUCT����
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_ST;

          �¼��ϱ�ʱʹ�ûص�����,��APP����APS����¼����ڴ�.
          ��ACT_CNFʱ�������PCO����Ҫ�ڱ�׼���¼��ṹ�����׹��һ����
          �棬���PCO��Ϣ�����PCO��Ϣ�����ݽṹ����:
          -------------------------------
          |  PS_EVENT_STRU              |
          -------------------------------
 BEGIN :  |  AUTH_LEN (2 OCT)           |
          -------------------------------
          |  AUTH�� (AUTH_LEN OCT)      |
          -------------------------------
          |  IPCP_LEN (2 oct)           |
          -------------------------------
 END   :  |  IPCP�� (IPCP_LEN OCT)      |
          -------------------------------

          IPCP�������ݸ�ʽ����:
          -------------------------------
          |  ��ǰ�Ӱ��ĸ��� (1 OCT)     |
          -------------------------------
          |  P1_LEN (2 OCT)             |
          -------------------------------
          |  P1�� (P1_LEN OCT)          |
          -------------------------------
          |  P2_LEN (2 oct)             |
          -------------------------------
          |  P2�� (P2_LEN OCT)          |
          -------------------------------
          |  P3_LEN (2 oct)             |
          -------------------------------
          |  P3�� (P3_LEN OCT)          |
          -------------------------------
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usLen;              /*PPP֡��code�ͺ���������ĳ���*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                          *pProtIdCont;        /*��PPP֡��code�ͺ��������*/
} APS_PCO_PPP_ST;


typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_PPP_ST;

typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_ACK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_NAK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_REJ_PPP_ST;

typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_ACK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_NAK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_REJ_PPP_ST;

typedef struct
{
    VOS_UINT8               ucIpcpPktNum;
    VOS_UINT8               aucRsv[3];
    APS_PCO_IPCP_PPP_ST     stIpcpPkt[APS_PCO_MAX_IPCP_PKT_NUM];
}APS_PCO_IPCP_ST;


typedef struct
{
    VOS_UINT16                          usLen;              /*PPP֡��ID�ͺ���������ĳ���*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                          *pProtIdCont;        /*��PPP֡��ID�ͺ��������*/
} APS_PPP_ID_ST;



#define MN_APS_MAX_PROTOCOL_ID_NUM      (4)
#define MN_APS_MAX_PROTOCOL_CONTENT_LEN (127)

#define MN_APS_IPCP_PROTOCOL_ID         (0x8021)            /* Internet Protocol Control Protocol */
#define TAF_APS_IPV4_PCSCF_PROTOCOL_ID  (0x000C)            /* IPv4 P-CSCF Container Identifier */

#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_IPV6_DNS_PROTOCOL_ID     (0x0003)            /* IPv6 DNS Container Identifier */
#define TAF_APS_IPV6_PCSCF_PROTOCOL_ID  (0x0001)            /* IPv6 P-CSCF Container Identifier */
#endif

/*****************************************************************************
 �ṹ����   : MN_APS_CONFIG_PROTOCOL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : Protocol identifier���ݽṹ
*****************************************************************************/
typedef struct
{
  VOS_UINT8                             aucProtocolId[2];   /* Protocol identifier */
  VOS_UINT16                            usProtocolLen;      /* Protocol id���ݳ��� */
  VOS_UINT8                             aucProtocolContents[MN_APS_MAX_PROTOCOL_CONTENT_LEN];
  VOS_UINT8                             aucReserved[1];
} MN_APS_CONFIG_PROTOCOL_STRU;


/*****************************************************************************
 �ṹ����   : MN_APS_PROTOCOL_CFG_OPTIONS_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���TS 24.008 section 10.5.6.3 Protocol configuration options
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucConfigProtocol;   /* Configuration protocol  */
    VOS_UINT8                           ucProtocolIdsNum;   /* Protocol identifier num */
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */
    MN_APS_CONFIG_PROTOCOL_STRU         stProtocolInfo[MN_APS_MAX_PROTOCOL_ID_NUM];

} MN_APS_PROTOCOL_CFG_OPTIONS_STRU;


/*****************************************************************************
  7 ��Ϣͷ����
  ģ���������士HEADER
#define MAPS_TEMPLATE_HEADER            VOS_UINT16    usTotalsMsgLen;\
                                        VOS_UINT32    ulSendModuleId;\
                                        VOS_UINT32    ulRecvModuleId;
*****************************************************************************/


/*****************************************************************************
  8 ��Ϣ����
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     ��Ϣ��
} MAPS_TEMPLATE_MSG;
*****************************************************************************/


/*****************************************************************************
  9 FUNCTIONS����
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*<>     �ڽ����ļ��ж��壬��Ҫ��Զ��ʹ�õĺ���        <>*/
/*=======================================================*/

VOS_VOID    Aps_Str2LenStr(     VOS_UINT32                  ulStrMaxLen,
                                VOS_UINT8                  *pStr,
                                VOS_UINT8                  *pLenStr );
VOS_UINT32  Aps_Option12Cids(   VOS_UINT8                  *paucCid );
VOS_UINT32  Aps_Option0Cid(     VOS_UINT8                  *paucCid );

/*****************************************************************************
  10 OTHERS����
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/
