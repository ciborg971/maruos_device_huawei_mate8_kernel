
#ifndef _GMM_RABM_INTERFACE_H_
#define _GMM_RABM_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define GMM_RABM_RRC_EST_CAUSE_ORG_SUBS_CALL    (0)         /* Originating Subscribed traffic clas Call */
#define GMM_RABM_RRC_EST_CAUSE_ORG_CONV_CALL    (1)         /* Originating Conversational Call          */
#define GMM_RABM_RRC_EST_CAUSE_ORG_STM_CALL     (2)         /* Originating Streaming Call               */
#define GMM_RABM_RRC_EST_CAUSE_ORG_INTER_CALL   (3)         /* Originating Interactive Call             */
#define GMM_RABM_RRC_EST_CAUSE_ORG_BG_CALL      (4)         /* Originating Background Call              */


/* SERVICE REQUEST�ɹ�ʧ�ܱ�־ */
#define GMM_RABM_SERVICEREQ_SUCCESS             (0)         /* SERVICE REQUEST�ɹ� */
#define GMM_RABM_SERVICEREQ_FAILURE             (1)         /* SERVICE REQUESTʧ�� */

#define GMM_RABM_SERVICEREQ_DELAYED             (2)         /* SERVICE REQUEST�ӳ��ط� */

#define GMM_RABM_SERVICEREQ_OOS                 (3)         /* AS�������½���ʧ�� */

/* RABM����PDU���ݵ���󳤶� */
#ifndef RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN
#define RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN      (19)
#endif

/* ucGmmRauCause */
#define GMM_RABM_RAU_UNDER_NORMAL               (0)         /* �����������·���RAU       */
#define GMM_RABM_RAU_UNDER_HANDOVER             (1)         /* ����ϵͳ�л������·���RAU */


/* ucResult */
#define GMM_RABM_RAU_SUCCESS                    (0)
#define GMM_RABM_RAU_FAILURE                    (1)


/* ucNpduValidFlg ��ֵ���� */
#define GMM_RABM_NPDU_INVALID                   (0)         /* N-PDU������Ч */
#define GMM_RABM_NPDU_VALID                     (1)         /* N-PDU������Ч */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ����   : GMM_RABM_MSG_ID_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : GMM��RABM֮���ԭ��
*****************************************************************************/
enum GMM_RABM_MSG_ID_ENUM
{
    ID_RABM_GMM_REESTABLISH_REQ                 = 0x0000,           /* _H2ASN_MsgChoice GMMRABM_REESTABLISH_REQ_STRU */
    ID_RABM_GMM_RAB_REL_IND                     = 0x0001,           /* _H2ASN_MsgChoice GMMRABM_RAB_REL_IND_STRU */
    ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP         = 0x0002,           /* _H2ASN_MsgChoice GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG */
    ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ         = 0x0003,           /* _H2ASN_MsgChoice RABM_GMM_MML_RPOCEDURE_SERVICE_QRY_REQ_STRU */

    ID_RABM_GMM_RAB_SETUP_IND                   = 0x0004,           /* _H2ASN_MsgChoice GMMRABM_RAB_SETUP_IND_STRU */

    ID_GMM_RABM_REESTABLISH_CNF                 = 0x1000,           /* _H2ASN_MsgChoice GMMRABM_REESTABLISH_CNF_STRU */
    ID_GMM_RABM_SYS_SRV_CHG_IND                 = 0x1001,           /* _H2ASN_MsgChoice GMM_RABM_SYS_SRV_CHG_IND_STRU */
    ID_GMM_RABM_ROUTING_AREA_UPDATE_IND         = 0x1002,           /* _H2ASN_MsgChoice GMMRABM_ROUTING_AREA_UPDATE_IND_MSG */
    ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF         = 0x1003,           /* _H2ASN_MsgChoice GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU */

    ID_GMM_RABM_MSG_BUTT
};
typedef VOS_UINT32 GMM_RABM_MSG_ID_ENUM_UINT32;


typedef VOS_UINT32 GMM_RABM_NET_RAT_ENUM_UINT32;


/* ��ǰRABM����״̬ */
typedef enum
{
    RABM_3G_ENUM = 0,
    RABM_2G_ENUM
} RABM_CUR_NET_ENUM;

enum RABM_RELRRC_OPERATE_ENUM
{
    RABM_FASTDORM_ENUM      = 0,
    RABM_RELEASE_RRC_ENUM   = 1,
    RABM_VOICEPREFER_ENUM   = 2
};
typedef VOS_UINT32 RABM_RELRRC_OPERATE_ENUM_UINT32;

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
 �ṹ��    : GMMRABM_REESTABLISH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_RABM_GMM_REESTABLISH_REQ�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                          ulRrcEstCause;      /* RRC���ӽ�����ԭ�� */
    VOS_UINT16                          usPdpContextStatus; /* ��Ҫ����PDP Context״̬ */
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    VOS_UINT16                          usUplinkDataStatus; /* ��Ҫ����PDP Context״̬ */
#else
    VOS_UINT8                           aucRsv[2];          /* 4�ֽڶ���                 */
#endif

} GMMRABM_REESTABLISH_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GMMRABM_REESTABLISH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_GMM_RABM_REESTABLISH_CNF�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                          ulResult;           /* SERVICE REQUEST�ɹ�ʧ�ܱ�־ */

} GMMRABM_REESTABLISH_CNF_STRU;


/*****************************************************************************
 �ṹ��    : GMMRABM_ROUTING_AREA_UPDATE_IND_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_RABM_GMM_ROUTING_AREA_UPDATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                          ulTLLI;             /* ���µ�TLLIֵ */
    VOS_UINT8                           aucRecvNPDUNumListIE[RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN];
    VOS_UINT8                           ucGmmRauCause;      /* ��ǰGMM����RAUʱ��ԭ�� */
    VOS_UINT8                           ucResult;
    VOS_UINT8                           aucReserve[3];
} GMMRABM_ROUTING_AREA_UPDATE_IND_MSG;


/*****************************************************************************
 �ṹ��    : GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_GMM_RABM_ROUTING_AREA_UPDATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           ucNpduValidFlg;     /* N-PDU number��Ч��־ */
    VOS_UINT8                           aucRecvNPDUNumListIE[RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN];

} GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG;


/*****************************************************************************
 �ṹ��    : GMMRABM_RAB_REL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_RABM_GMM_RAB_REL_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

} GMMRABM_RAB_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : GMMRABM_RAB_SETUP_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_RABM_GMM_RAB_SETUP_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

} GMMRABM_RAB_SETUP_IND_STRU;


/*****************************************************************************
 �ṹ��    : GMM_RABM_SYS_SRV_CHG_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��GMMRABM_SYS_SRV_CHG_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ         */ /* _H2ASN_Skip */
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode;          /* ��ǰϵͳģʽ   */
    VOS_BOOL                            bRatChangeFlg;      /* ��ϵͳ�л���־ */
    VOS_BOOL                            bDataSuspendFlg;    /* ����ָʾ��־   */
    VOS_UINT8                           ucReserve[3];
    VOS_UINT8                           ucRebuildRabFlag;    /* �Ƿ���Ҫ�ؽ�RB��Ϣ */
} GMM_RABM_SYS_SRV_CHG_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;

    RABM_RELRRC_OPERATE_ENUM_UINT32                     enOptFlag;
} RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU;


typedef struct
{
    VOS_UINT32                          bitOpGmmSpecificProcedure: 1;           /* �Ƿ����GMMר������ */
    VOS_UINT32                          bitOpPsSmsService: 1;                   /* �Ƿ����PS����� */
    VOS_UINT32                          bitOpCsSignal: 1;                       /* �Ƿ����CS���������� */

    VOS_UINT32                          bitSpare: 29;
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag;
} RABM_GMM_MML_PROC_STATUS_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    RABM_GMM_MML_PROC_STATUS_STRU       stMmlProcStatus;                        /* GMMר�����̣�PS����ţ�CS����������״̬ */
} GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU;



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
    GMM_RABM_MSG_ID_ENUM_UINT32         enMsgId;            /* _H2ASN_MsgChoice_Export GMM_RABM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_RABM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} GMM_RABM_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    GMM_RABM_INTERFACE_MSG_DATA         stMsgData;
} GmmRabmInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 NAS_RABM_IsPsRbExist(VOS_VOID);


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

#endif

