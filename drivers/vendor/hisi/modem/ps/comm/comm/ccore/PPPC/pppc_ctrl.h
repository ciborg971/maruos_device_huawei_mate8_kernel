
#ifndef      _PPPC_CTRL_H_
#define      _PPPC_CTRL_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtPppInterface.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "v_IO.h"
#include "TTFComm.h"
#include "TTFLink.h"
#include "taf_aps_ppp_pif.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "PsTypeDef.h"
#include "cttf_hrpd_pa_ppp_pif.h"
#include "pppc_pa_agent.h"
#include "UsimPsInterface.h"

#include "TtfDrvInterface.h"
#include "pppc_uim.h"
#include "TtfIpComm.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PPP_MNTN_TRACE_MSG(pMsg)                DIAG_TraceReport(pMsg)

/* �������л��۵ı���֡���ﵽ����ʱ,��Ҫ����PPPC������,��һ�ֱ������� */
#define PPPC_MAX_NOTIFY_PPPC_PROC_CNT           (200)

/* �������д���Ĵ����ﵽ����ʱ,��Ҫ����PPPC��ʱ�ͷ�CPU,��һ�ֱ������� */
#define PPPC_MAX_NOTIFY_PPPC_DELAY_CNT          (50)

/* ��̫������֡�������������䳤�ȱ�����46~1500�ֽ�֮�� */
#define PPPC_MIN_FRAME_LEN                      (46)
#define PPPC_MAX_FRAME_LEN                      (1500)

/* 1X��HRPD������RLP���͸�PPPC�ķ�Ƭ���Ŀ��ܵ����ֵ */
#define PPPC_MAX_FRAGMENT_BIT_LEN               (12288)

/* ��������TTF�ڴ����洢����󳤶� */
#define PPPC_MAX_UL_ENCAP_LEN                   (1600)

/* ����������ﵽ����ʱ�˳�PPPC,���ڻ���PPPC���� */
#define PPPC_REACH_MAX_PROC_TIMER_AWAKE_LEN     (300)

/* ���������ڴ滺��Ƭ��,ÿƬ�������PPPC_MAX_UL_ENCAP_LEN�ֽ� */
#define PPPC_MAX_UL_ENCAP_MEM_NUM               (2)

/* CDS�����������1500�ֽ�,����PPP����������չΪ1(0x7e)+3(0xff03)+4(0x0021)+1500*2+4(FCS)+1(0x7e) */
#define PPPC_MAX_UL_DATA_LEN                    (3013)

/* �����нڵ����ۼƴﵽ100(ÿ���ڵ���������20Ƭ����)��ʱ,����300ms��ʱ���������ж��� */
#define PPPC_MAX_DL_NODE_CNT                    (100)

#define PPPC_OM_TRANS_DATA_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_PPPC_TRACE_DATA_STRU, aucValue)
#define PPPC_OM_DIAL_CNF_OFFSET_LEN             /*lint -e(545) -e(413)*/offsetof(PPPC_AT_CDMA_DIAL_MODE_CNF_STRU, enMsgId)
#define PPPC_OM_ACT_CNF_OFFSET_LEN              /*lint -e(545) -e(413)*/offsetof(PPP_APS_ACT_CNF_STRU, enMsgId)
#define PPPC_OM_DEACT_CNF_OFFSET_LEN            /*lint -e(545) -e(413)*/offsetof(PPP_APS_DEACT_CNF_STRU, enMsgId)
#define PPPC_OM_DEACT_NOTIFY_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(PPP_APS_DEACT_NTF_STRU, enMsgId)

#define PPPC_OM_ATTACH_CNF_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU, enMsgId)
#define PPPC_OM_DETACH_CNF_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU, enMsgId)
#define PPPC_OM_PDN_CONN_CNF_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU, enMsgId)
#define PPPC_OM_PDN_DISC_CNF_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU, enMsgId)
#define PPPC_OM_DETACH_IND_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_DETACH_IND_STRU, enMsgId)
#define PPPC_OM_PDN_DISC_IND_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU, enMsgId)

#define PPPC_OM_QOS_REQ_OFFSET_LEN              /*lint -e(545) -e(413)*/offsetof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU, enMsgId)
#define PPPC_OM_QOS_CLOSE_REQ_OFFSET_LEN        /*lint -e(545) -e(413)*/offsetof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU, enMsgId)


#define PPPC_PDN_ID_UNIQUE                      (1)
#define PPPC_PPP_ID_FOR_ACCESS_AUTH             (0)                             /* ���ڽ����Ȩ��PPP ID�̶���дΪ0 */
#define PPPC_PPP_ID_MIN                         (1)
#define PPPC_PPP_ID_MAX                         (PPP_MAX_USER_NUM)
#define PPPC_MAX_PA_BINDING_APP_NUM             (3)
#define PPPC_HRPD_PA_DATA_STREAM_NUM            (2)                             /* ����ʱ����Ĭ����Ϊ2������һ�� */

/* bit postion mask value is zero */
#define PPPC_BIT_MASK_EMPTY                     (0)

/* bit postion mask value is one */
#define PPPC_BIT_MASK_ON                        (1)

/**
 * Maximum number of NAI.
 */
#define PPPC_HRPD_MAX_NUM_NAI                   (15)

#define PPPC_HRPD_MAX_NAI_LENGTH                (255)

/* Get high 16 bits from 32 bits */
#define PPPC_GET_HIGH_16_BITS(ulVal)            (((ulVal) >> 16) & 0xFF)

/* Get low 16 bits from 32 bits */
#define PPPC_GET_LOW_16_BITS(ulVal)             ((ulVal) & 0xFF)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : PPPC_PROC_LINK_DIRECTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �жϴ��������ж��е�����
*****************************************************************************/
enum PPPC_PROC_LINK_DIRECTION_ENUM
{
    PPPC_PROC_BY_STAMP                  = 0,                /* ����ʱ������������ж��� */
    PPPC_PROC_UL_NODE                   = 1,                /* �������ж��� */
    PPPC_PROC_DL_NODE                   = 2,                /* �������ж��� */

    PPPC_PROC_BUTT
};
typedef VOS_UINT16  PPPC_PROC_LINK_DIRECTION_ENUM_UINT16;

/*****************************************************************************
 ö����    : PPPC_INNER_MSG_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ���л������б���Ҫ��ʱ֪ͨPPPģ�鴦��
*****************************************************************************/
enum PPPC_INNER_MSG_TYPE_ENUM
{
    PPPC_DL_DATA_PROC_NOTIFY            = 0,                /* �յ�������Ϣ֪ͨ */
    PPPC_UL_DATA_PROC_NOTIFY            = 1,                /* �յ�������Ϣ֪ͨ */
    PPPC_HDLC_PROC_AS_FRM_PACKET_IND    = 2,                /* �յ����д�Ӳ��HDLC��װ���� */

    PPPC_DATA_PROC_BUTT
};
typedef VOS_UINT16  PPPC_INNER_MSG_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_HRPD_PA_STREAM_STATE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum PPPC_HRPD_PA_STREAM_STATE_ENUM
{
    PPPC_STREAM_CLOSE_STATE        = 0x00,
    PPPC_STREAM_OPEN_STATE         = 0x01,
    PPPC_STREAM_STATE_BUTT         = 0x02
};
typedef VOS_UINT8 PPPC_HRPD_PA_STREAM_STATE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :PPPC_UIM_MSG_STRU
 �ṹ˵��  :PPPC�뿨������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��ϢID */
}PPPC_UIM_MSG_STRU;


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/** ****************************************************************************
* Name        : PPPC_DATA_Q_NOTIFY_CNT_STRU
*
* Description : PPP�����ж��дӿյ��ǿյ�֪ͨ��Ϣ����.
*******************************************************************************/
typedef struct
{
    volatile VOS_UINT32                 ulNotifyMsgCnt;                         /* PPPC��Ϣ�����д��������Ϣ���� */
    VOS_SPINLOCK                        stSpinLock;                             /* ������ */
} PPPC_DATA_Q_NOTIFY_CNT_STRU;

/** ****************************************************************************
* Name        : PPPC_DATA_LINK_NODE_STRU
*
* Description : ��������������.
*******************************************************************************/
typedef struct
{
    TTF_NODE_ST                         stNode;                                 /* PPP���������� */
    VOS_UINT32                          ulTimeStamp;                            /* ���ʱ��� */
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;                              /* ����ģʽ */
    VOS_UINT8                           ucPdnId;                                /* ���غ� */
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;                           /* IP������, ֻ�������� */
    VOS_UINT8                           ucStreamNum;                            /* ����,HRPD/eHRPDʹ�� */
    VOS_UINT8                           ucNumReservLabels;                      /**< MFPA/EMPA relevant only */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucReservLabel[CTTF_HRPD_PA_MAX_NUM_RESERV_LABELS];
    VOS_UINT16                          usHigherLayerProtocol;                  /* usHigherLayerProtocol */
    VOS_UINT8                           aucReserv[2];
    VOS_UINT32                          ulPduCnt;                               /* ָʾһ���ڵ��д洢��TTF�ڴ���� */
    TTF_MEM_ST                         *pstPduMem;                              /* PPP�����б���,�ڲ����� */
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo;                           /* data info of cds */
}PPPC_DATA_LINK_NODE_STRU;


/** ****************************************************************************
* Name        : PPPC_DATA_PROC_NOTIFY_MSG
*
* Description : ����֪ͨ��Ϣ.
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */        /*_H2ASN_Skip*/
    PPPC_INNER_MSG_TYPE_ENUM_UINT16     enMsgType;                              /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT8                           aucResv[2];
}PPPC_DATA_PROC_NOTIFY_MSG;

/** ****************************************************************************
* Name        : APS_CMD_MSG_LINK_NODE_STRU
*
* Description : �洢APS����PPP����Ϣ
*******************************************************************************/
typedef  struct
{
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;                          /* ��Ϣ���� */
    TAF_APS_PPP_RAT_MODE_ENUM_UINT8         enMode;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8        enPdnType;
}APS_CMD_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : EHSM_CMD_MSG_LINK_NODE_STRU
*
* Description : �洢EHSM����PPP����Ϣ
*******************************************************************************/
typedef  struct
{
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;             /* ��Ϣ���� */
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8     enPdnType;
    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8  enAttachType;
    VOS_UINT8                               ucAddressAllocCause;
    VOS_UINT8                               aucReserved[3];
    CNAS_CTTF_EHRPD_APN_STRU                stApn;
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU        stPdnAddress;
    CNAS_CTTF_EHRPD_PCO_STRU                stPco;
    VOS_UINT8                               aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];
}EHSM_CMD_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : PPPC_APS_MSG_LINK_NODE_STRU
*
* Description : �洢APS/EHSM����PPP����Ϣ����ڵ�
*******************************************************************************/
typedef  struct
{
    TTF_NODE_ST                             stNode;                             /* ���ڶ��йҽ� */
    VOS_UINT32                              ulSenderPid;                        /* ������Ϣ��PID */
    VOS_UINT16                              usOpId;
    VOS_UINT8                               ucPppId;
    VOS_UINT8                               ucPdnId;
    PS_BOOL_ENUM_UINT8                      enIsHandling;                       /* PS_TRUE:��ǰ�нڵ����ڴ��� PS_FALSE:û�нڵ㱻���� */
    VOS_UINT8                               aucReserved[3];
    APS_CMD_LINK_NODE_STRU                  stApsCmdNode;
    EHSM_CMD_LINK_NODE_STRU                 stEhsmCmdNode;
}PPPC_APS_MSG_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : PPPC_PID_PDNID_MAPPING_STRU
*
* Description : ppp id��Pdn idӳ����Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPdnId;
    VOS_UINT8                                               ucPppId;
    PS_BOOL_ENUM_UINT8                                      enValidFlag;
    VOS_UINT8                                               aucReserved[1];
}PPPC_PID_PDNID_MAPPING_STRU;

/*******************************************************************************
* Name        : PPPC_CONTEXT_INFO_STRU
*
* Description : �洢HRPD(����eHRPD)ģ�����������Ϣ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16               aenApplicationType[3];
    PS_BOOL_ENUM_UINT8                                      enIsSendOpenFlag;   /* ״̬��Close���������� */
    PS_BOOL_ENUM_UINT8                                      enIsDoingAcessAuth; /* ������BSC���н����ȨЭ�� */
    VOS_UINT8                                               ucAccessAuthLen;
    VOS_UINT8                                               aucReserv[3];
    VOS_UINT8                                               aucAccessAuthUserName[CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN+1]; /* ��BSC�����Ȩ�û��� */
    VOS_UINT32                                              ulRandu;
}PPPC_HRPD_CONTEXT_STRU;

/*******************************************************************************
* Name        : PPPC_CONTEXT_INFO_STRU
*
* Description : pppģ����������Ϣ
*******************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                                    enModemId;
    TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8                  enDialMode;         /* PPPĬ��Ϊ�м�ģʽ TAF_APS_PPP_CDATA_DIAL_MODE_RELAY */
    PPPC_RAT_MODE_ENUM_UINT8                                enRatMode;          /* ��ǰ����ģʽ1X/HRPD/eHRPD */
    VOS_UINT32                                              ulSendPid;          /* ���𼤻��Pid */
    VOS_UINT16                                              usMru;              /* PPPC��������ʱ��ֵ������ʱ�������޸ĸ�ֵ */
    PS_BOOL_ENUM_UINT8                                      enCaveEnable;       /* CAVE�㷨ʹ�ܿ��أ�0��֧��CAVE�㷨 */
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8                        enPdnType;
    VOS_UINT32                                              ulUserNameLen;      /* ���Ȳ��ᳬ��TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN */
    VOS_UINT32                                              ulPasswordLen;      /* ���Ȳ��ᳬ��TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN */
    VOS_UINT8                                               aucUserName[TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN+1]; /* ��Ȩ�û��� */
    VOS_UINT8                                               aucPassword[TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN+1]; /* ��Ȩ���� */
    VOS_UINT32                                              ulPppIdBitMask;     /* ��bitλ����¼��ǰ��ʹ�õ�PppId,��bit1��ʼ��ʾ */
    VOS_UINT32                                              aulPppIdMapPdnId[PPP_MAX_USER_NUM + 1];   /* ӳ��PdnId,��bit��ӳ�䵱ǰPppId��Ӧ�Ķ��PdnId */
    PPPC_HRPD_CONTEXT_STRU                                  stHrpdContext;
}PPPC_CONTEXT_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_DATA_UL_ENCAP_MEM_STRU
*
* Description : �������ݴ�����PPPC���ڴ�ṹ,Ϊ������ʽ������Ԫ��.
*******************************************************************************/
typedef struct
{
    TTF_MEM_ST                                             *pstDataPtr;         /* �����������ݵ��ڴ�,����1600�ֽ� */
    PS_BOOL_ENUM_UINT8                                      enPtrIsUsed;        /* ָʾ�ڴ��Ƿ�ʹ�� */
    VOS_UINT8                                               aucReserv[3];
} PPPC_DATA_UL_ENCAP_MEM_STRU;

/** ****************************************************************************
* Name        : PPPC_HRPD_RESERVATION_QOS_INFO_STRU
*
* Description : Ӧ��֪ͨPPPC����QoSЭ��ʱЯ������Ϣ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16               enApplicationType;
    VOS_UINT8                                               ucNumFwdReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               ucNumRevReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    CTTF_HRPD_QOS_STRU                                      astFwdReservations[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ]; /**< Parameters for each reservation */
    CTTF_HRPD_QOS_STRU                                      astRevReservations[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ]; /**< Parameters for each reservation */
} PPPC_HRPD_RESERVATION_QOS_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU
*
* Description : Ӧ��֪ͨPPPC����QoSЭ��ʱЯ������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumFwdReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               ucNumRevReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               aucReserv1[2];
    VOS_UINT8                                               aucFwdReservationLabels[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ];
    VOS_UINT8                                               aucRevReservationLabels[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ];
}PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 PPPC_Init(enum VOS_INIT_PHASE_DEFINE InitPhase );
extern VOS_VOID PPPC_MsgProc( struct MsgCB * pMsg );

extern VOS_VOID PPPC_ShowDLProcStats(VOS_VOID);
extern VOS_VOID PPPC_ShowULProcStats(VOS_VOID);
VOS_VOID PPPC_1X_IncreaseNegoRcvCnt(VOS_VOID);
VOS_VOID PPPC_HRPD_IncreaseNegoRcvCnt(VOS_VOID);

VOS_UINT8 *PPP_GetUlEncapDataPtr(VOS_VOID);
VOS_VOID PPP_InitEncapDataPtr(VOS_VOID);
VOS_VOID PPPC_ClearUlEncapMem(VOS_VOID);

VOS_UINT16 PPPC_HRPD_GetAppType(VOS_VOID);
VOS_UINT8 PPPC_HRPD_GetStreamNumber(VOS_VOID);

TTF_MEM_ST *PPPC_AdapterMBuftoTtfMemory
(
    PMBUF_S                            *pstMBuf,
    VOS_UINT32                          ulMemPoolId,
    VOS_UINT32                          ulOffset,
    VOS_UINT32                          ulLength
);

VOS_VOID PPPC_IsReadyToRespActCmd(VOS_VOID* pPppInfo);
VOS_VOID PPPC_JudgeApsCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId);
VOS_VOID PPPC_ClearUlDataQ(VOS_VOID);
VOS_VOID PPPC_ClearDlDataQ(VOS_VOID);
VOS_VOID PPPC_SendApsDeactNotify(VOS_UINT8 ucPppId);
VOS_UINT32 PPPC_ULSendNegoFrame(PMBUF_S *pstMBuf, VOS_UINT32 ulRPIndex);
VOS_VOID PPPC_RespApsDeActCmd(VOS_UINT32 ulResult);
VOS_UINT32 PPPC_GetPppIdByPdn(VOS_UINT8 ucPdnId, VOS_UINT8 *pucPppId);
VOS_UINT32 PPPC_1XHrpdGetPdnId(VOS_UINT16 usPppId, VOS_UINT8 *pucPdnId);
VOS_UINT32 PPPC_SndDlDataNotify(VOS_VOID);
VOS_UINT32 PPPC_SndUlDataNotify(VOS_VOID);
VOS_VOID PPPC_MappingPppIdandPdnId(VOS_UINT8 ucPppId, VOS_UINT8 ucPdnId);
VOS_VOID PPPC_ClearMappingByPppId(VOS_UINT8 ucPppId);
VOS_VOID PPPC_ActReqMsgNodeProc(VOS_VOID);
VOS_VOID PPPC_DeActReqMsgNodeProc(VOS_VOID);
TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 PPPC_GetDialMode(VOS_VOID);
VOS_UINT32 PPPC_RcvCdsUlFrame
(
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstTtfMemory,
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
);
VOS_VOID PPP_SendRlpDlDatatoCds
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
);
VOS_UINT32 PPPC_GetCurrentPdnId(VOS_UINT8 *pucPdnId);
VOS_UINT32 PPPC_1X_GetPdnId(VOS_UINT8 ucPppId, VOS_UINT8 *pucPdnId);
PPPC_RAT_MODE_ENUM_UINT8 PPPC_GetRatMode(VOS_VOID);
VOS_UINT8 PPPC_GetCurrentPppId(VOS_VOID);
VOS_UINT16 PPP_GetDefaultMru(VOS_VOID);
VOS_VOID PPPC_SendEhsmDetachNotify(VOS_UINT8 ucPppId);
VOS_VOID PPPC_RespApsActFail
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
);
VOS_VOID PPPC_RespApsDeActFail
(
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
);
VOS_VOID PPPC_RespEhsmAttachFail
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
);
VOS_VOID PPPC_RespEhsmPdnConnectFail
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
);
VOS_VOID PPPC_RespEhsmPdnDisconnectFail
(
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
);
VOS_VOID PPPC_SendPdnConnectCnf
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstMsgLinkNode,
    VOS_UINT32                          ulResult
);
VOS_VOID PPPC_DequeueProc(PPPC_PROC_LINK_DIRECTION_ENUM_UINT16 enProcDire);
VOS_VOID PPPC_AwakeSelfReachMaxProcTimeoutProc(VOS_VOID);
PS_BOOL_ENUM_UINT8 PPPC_IsDoingAccessAuth(VOS_VOID);
VOS_VOID PPPC_ChangeAccessAuthState(PS_BOOL_ENUM_UINT8 enIsDoingAcessAuth);
VOS_UINT32 PPPC_HRPD_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileID);
PS_BOOL_ENUM_UINT8 PPPC_IsCaveAlgorithmEnable(VOS_VOID);
VOS_VOID PPPC_SaveAccessAuthUserNameInfo(VOS_UINT8 *pstMsg);


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



