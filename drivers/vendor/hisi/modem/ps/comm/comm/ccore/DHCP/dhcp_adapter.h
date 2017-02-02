
#ifndef      _DHCP_ADAPTER_H_
#define      _DHCP_ADAPTER_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "v_IO.h"
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "TTFComm.h"
#include "TTFLink.h"
#include "dhcpc_def.h"
#include "dhcp_inc.h"
#include "dhcpc_dbg.h"
#include "dhcpv6_def.h"
#include "dhcpv6c_pkt.h"
#include "taf_aps_dhcp_pif.h"
#include "CdsDhcpInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define CTTF_DHCP_TRACE_DATA_MSG(pMsg)            DIAG_TraceReport(pMsg)

#define DHCP_MAX_EPSB_ID              (15)                /*���ĳ��غ�*/
#define DHCP_MIN_EPSB_ID              (5)                 /*��С�ĳ��غ�*/

#define DHCP_ENTITY_MAX_NUM           (11)

/*ͨ��ModemId��EpsId��ϳ�exEpsId����2bitΪModemId,��6bitΪEpsId*/
#define DHCP_FORM_EXEPSID(ModemId,EpsId)          (VOS_UINT8)((VOS_UINT8)(((ModemId) << 6) | (EpsId)))

/*��ExEpsId�л��ModemId*/
#define DHCP_GET_MODEMID_FROM_EXEPSID(ExEpsId)    (VOS_UINT16)(((ExEpsId) & 0xC0) >> 6)

/*��ExEpsId�л��EpsId*/
#define DHCP_GET_EPSID_FROM_EXEPSID(ExEpsId)      (VOS_UINT8)((ExEpsId) & 0x3F)

#define IP_GetTimerPara(pMsg)                     (((REL_TIMER_MSG *)pMsg)->ulPara)
#define IP_GetTimerName(pMsg)                     (((REL_TIMER_MSG *)pMsg)->ulName)

#define IP_PACKAGE_HEADER_RESERVE                 (2)

#define IP_UDP_INIT_CHECKSUM                      (0)
#define IP_IPV6_LINK_LOCAL_PREFIX                 (0xfe80)
#define IP_IPV6_LINK_LOCAL_MASK                   (0xffc0)
#define IP_IPV6_DHCP_HOP_LIMIT                    (0xff)
#define IP_IPV6_DHCP_VALID_CODE                   (0)
#define IP_IPV6_TRAFFIC_CLASS                     (0xe0)

#define IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET       (6)
#define IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET         (4)
#define IP_IPV6_BASIC_HOP_LIMIT_OFFSET            (7)
#define IP_IPV6_SRC_ADDR_OFFSET                   (8)
#define IP_IPV6_DST_ADDR_OFFSET                   (24)

#define IP_UDP_SOURCE_PORT_OFFSET                 (0)
#define IP_UDP_DEST_PORT_OFFSET                   (2)
#define IP_UDP_LEN_OFFSET                         (4)
#define IP_UDP_CHECKSUM_OFFSET                    (6)

#define DHCP_IP_MAX_PREFIX_NUM_IN_RA              (6)
#define DHCP_IPV6_IF_OFFSET                       (8)
#define DHCP_IPV6_IF_LEN                          (8)
#define DHCP_IP_IPV6_PREFIX_LENGTH                (8)

/*IP��ַ����*/
#define IP_IPV4_ADDR_LEN                (4)

#define IP_IPV6_ADDR_LEN                (16)

/* ip��ͷУ��ĳ���,��16λ���м�� */
#define IPCHECKLEN                                (10)

#define IP_BITMOVE_24                             (24)

#define IP_BITMOVE_16                             (16)

#define IP_BITMOVE_8                              (8)

#define IP_BITMOVE_4                              (4)

#define IP_SetUint16Data(pucFirstByte, usUint16Data)\
            {\
                (*(pucFirstByte)) = ((usUint16Data) >> IP_BITMOVE_8) & 0xff;\
                (*((pucFirstByte) + 1)) = (usUint16Data) & 0xff;\
            }

#define IP_SetUint32Data(pucFirstByte, ulUint32Data)\
            {\
                (*(pucFirstByte)) = ((ulUint32Data) >> IP_BITMOVE_24) & 0xff;\
                (*((pucFirstByte) + 1)) = ((ulUint32Data) >> IP_BITMOVE_16) & 0xff;\
                (*((pucFirstByte) + 2)) = ((ulUint32Data) >> IP_BITMOVE_8) & 0xff;\
                (*((pucFirstByte) + 3)) = (ulUint32Data) & 0xff;\
            }


#define SDB_MAX_PDSN_RP_CONTEXT_NUM   (10)
#define PPP_MAX_USER_NUM              SDB_MAX_PDSN_RP_CONTEXT_NUM

#define DHCP_PRINTF_MSG(pMsg)         printf(pMsg)

#define DHCP_OM_START_FILTER_REQ_OFFSET_LEN     /*lint -e(545) -e(413)*/offsetof(DHCP_CDS_START_FILTER_REQ_STRU, enMsgId)
#define DHCP_OM_STOP_FILTER_REQ_OFFSET_LEN      /*lint -e(545) -e(413)*/offsetof(DHCP_CDS_STOP_FILTER_REQ_STRU, enMsgId)
#define DHCP_OM_DNS_IPV6_CNF_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(DHCP_APS_DNS_IPV6_CNF_STRU, enMsgId)
#define DHCP_OM_DATA_REQ_OFFSET_LEN             /*lint -e(545) -e(413)*/offsetof(DHCP_CDS_DATA_REQ_STRU, enMsgId)
#define DHCP_OM_TRANS_DATA_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_DHCP_TRACE_DATA_STRU, aucValue)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : DHCP_TIMER_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : DHCP��ʱ��ö��
*****************************************************************************/
enum DHCP_TIMER_ENUM
{
    /* DHCP��ʱ�� */
    DHCP_TIMER_RS               = 0,

    DHCP_TIMER_BUTT
};
typedef VOS_UINT32 DHCP_TIMER_ENUM_UINT32;

/*****************************************************************************
 ö����    : IP_VERSION_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IP�汾
*****************************************************************************/
enum IP_VERSION_TYPE_ENUM
{
    IP_VERSION_4                        = 4,
    IP_VERSION_6                        = 6,

    IP_VERSION_BUTT
};
typedef VOS_UINT8 IP_VERSION_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

enum DHCP_TRACE_MSG_TYPE_ENUM
{
    ID_CTTF_DHCP_TRACE_IP_DATA_TO_CDS               = 0x0000,                   /* DHCP��CDS����Ϣ���� */

    ID_CTTF_DHCP_TRACE_MSG_TYPE_BUTT
};
typedef VOS_UINT16  DHCP_TRACE_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : IPv6_PSEDUOHEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6α�ײ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucIPSrc[IP_IPV6_ADDR_LEN];             /*ԴIP��ַ*/
    VOS_UINT8                           aucIPDes[IP_IPV6_ADDR_LEN];             /*Ŀ��IP��ַ*/
    VOS_UINT32                          ulUpperLength;                          /*����UPPER-LAYER���ȣ�������α�ײ�����*/
    VOS_UINT8                           ucZero[3];                              /*ȫ��Ϊ0*/
    VOS_UINT8                           ucNextHead;
}IPV6_PSEDUOHEADER_STRU;

/*****************************************************************************
 �ṹ��    : DHCP_TIMER_STRU
 Э����  :
 ASN.1���� :��
 �ṹ˵��  : ��ʱ���ṹ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hTm;                                    /* ��ʱ��ָ�� */
    VOS_UINT32                          ulName;                                 /* ��ʱ������ */
    VOS_UINT8                           ucLoopTimes;                            /* ѭ���������� */
    VOS_UINT8                           ucStatus;                               /* ��ʱ����״̬ */
    VOS_UINT8                           aucReserved[2];
}DHCP_TIMER_STRU;                                                            /* ��ʱ���ṹ�� */

typedef struct
{
    VOS_UINT32                          ulSendMsgSize;         /* ��Ϣ���ܳ��� */
    VOS_UINT32                          ulResv;                /*Ϊ��ͬ64λ����ϵͳ���ݣ�ָ�������8�ֽڶ���λ��*/
    VOS_UINT8                          *pucSendMsg;            /* ��Ϣ���׵�ַ */
}DHCP_SND_MSG_STRU;

/* DHCPʵ�� */
typedef struct
{
    VOS_UINT8                           ucEpsbId;       /*DSDA�޸ĺ󣬸�2bit����ModemId����6bit����EPSID*/
    VOS_UINT8                           ucflag;
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16  enMsgType;

    VOS_UINT8                           aucInterfaceId[TAF_APS_DHCP_IPV6_IFID_LEN];
    VOS_UINT8                           aucRouterIpAddr[TAF_APS_DHCP_IPV6_ADDR_LEN];
    DHCP_TIMER_STRU                     stTimerInfo;
    DHCP_SND_MSG_STRU                   stIpSndNwMsg;
    VOS_UINT16                          usRouterLifeTime;
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulReachableTimer;
    VOS_UINT32                          ulReTransTime;
    VOS_UINT32                          ulMtu;
    VOS_UINT16                          usSeqNum;
    VOS_UINT8                           ucWaitRspTimeOutNum;
    VOS_UINT8                           ucResendTimeout;
    VOS_UINT32                          aulMSISDN[2];       /*MSISDN*/
    VOS_UINT32                          aulIMSI[2];         /*IMSI*/
    VOS_UINT32                          aulIMEI[2];         /* IMEI */
}DHCP_ENTITY_STRU;

/** ****************************************************************************
* Name        : CDS_DHCP_MSG_INFO_STRU
*
* Description : CDS����DHCP�Ĺ�����Ϣ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
}CDS_DHCP_MSG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucValue[DHCPV6C_SEND_MSG_MAXLEN];
} CTTF_DHCP_TRACE_DATA_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 DHCP_Init(enum VOS_INIT_PHASE_DEFINE InitPhase);
extern VOS_VOID DHCP_MsgProc(struct MsgCB * pMsg);
VOS_VOID DHCP_RespApsDnsIpv6ReqCmd(VOS_VOID* pDhcpDNSInfo, VOS_UINT8 ucEpsId,VOS_UINT32 ulResult);
VOS_UINT32 DHCP_SendInfoReqPacket(DHCP_ENTITY_STRU *pstDhcpEntity);
VOS_VOID DHCP_AddEntityNum(VOS_UINT16 usModemId);
VOS_VOID DHCP_SubEntityNum(VOS_UINT16 usModemId);



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _DHCP_ADAPTER_H_ */



