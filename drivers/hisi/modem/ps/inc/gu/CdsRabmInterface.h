

#ifndef __CDSRABMINTERFACE_H__
#define __CDSRABMINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TTFMemInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define RABM_CDS_MSG_HDR                (0x00)
#define CDS_RABM_MSG_HDR                (0x10)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum RABM_RAB_STATUS_ENUM
{
    RABM_RAB_STATUS_IDLE                = 0x00,             /* RAB����̬ */
    RABM_RAB_STATUS_ACTIVE              = 0x01,             /* RAB����̬ */
    RABM_RAB_STATUS_SUSPEND             = 0x02,             /* RAB����̬ */
    RABM_RAB_STATUS_FAIL                = 0x03,             /* PDPδ���RAB������ */
    RABM_RAB_STATUS_BUTT
};
typedef VOS_UINT32 RABM_RAB_STATUS_ENUM_UINT32;


enum CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM
{
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC    = 0,                   /* �����ؽ��ɹ� */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_DRB_CONN        = 1,                   /* GUģRABM��ά��DRB״̬����δʹ�� */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_BUTT
};
typedef VOS_UINT32 CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32;

/* QCI���� */
enum QCI_TYPE_ENUM
{
    QCI_TYPE_QCI1_GBR           = 1,
    QCI_TYPE_QCI2_GBR           = 2,
    QCI_TYPE_QCI3_GBR           = 3,
    QCI_TYPE_QCI4_GBR           = 4,
    QCI_TYPE_QCI5_NONGBR        = 5,
    QCI_TYPE_QCI6_NONGBR        = 6,
    QCI_TYPE_QCI7_NONGBR        = 7,
    QCI_TYPE_QCI8_NONGBR        = 8,
    QCI_TYPE_QCI9_NONGBR        = 9,

    QCI_TYPE_BUTT
};

typedef VOS_UINT8  QCI_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


enum CDS_RABM_MSG_ID_ENUM
{
    /* CDS����RABM����Ϣ */
    ID_CDS_RABM_SERVICE_IND             = CDS_RABM_MSG_HDR + 0x00,              /* ҵ��������Ϣ���ٷ�RABM���������ؽ� */

    /* RABM����CDS����Ϣ */
    ID_RABM_CDS_SEND_BUFF_DATA_IND      = RABM_CDS_MSG_HDR + 0x00,              /* RABM֪ͨCDS��ָʾ���Է������� */
    ID_RABM_CDS_FREE_BUFF_DATA_IND      = RABM_CDS_MSG_HDR + 0x01,              /* RABM֪ͨCDS��ָʾ�ͷŻ������ݰ� */
    ID_QOS_FC_RABM_RAB_CREATE_IND       = RABM_CDS_MSG_HDR + 0x02,              /* _H2ASN_MsgChoice CDS_FC_START_CHANNEL_IND_STRU */
    ID_QOS_FC_RABM_RAB_RELEASE_IND      = RABM_CDS_MSG_HDR + 0x03,              /* _H2ASN_MsgChoice CDS_FC_STOP_CHANNEL_IND_STRU */
    ID_RABM_CDS_VOICEPREFER_ACT_IND     = RABM_CDS_MSG_HDR + 0x04,              /* _H2ASN_MsgChoice RABM_CDS_VOICEPREFER_ACT_IND_STRU */
    ID_RABM_CDS_MSG_ID_BUTT
};
typedef VOS_UINT32 CDS_RABM_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;            /* ��Ϣ�� */
    VOS_UINT8                           ucRabId;            /* Rab ID */
    VOS_UINT8                           aucReserved[3];     /* ����λ */
} CDS_RABM_SERVICE_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32                             enMsgId;                                /* ��Ϣ�� */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32        enSndBuffDataAllowedType;               /* ��������ָʾ���� */
    VOS_UINT8                                               ucRabId;                                /* Rab ID */
    VOS_UINT8                                               aucReserved[3];                         /* ����λ */
} CDS_RABM_SEND_BUFF_DATA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgID;            /* ��Ϣ�� */
    VOS_UINT8                           ucRabId;            /* Rab ID */
    VOS_UINT8                           aucReserved[3];     /* ����λ */
} CDS_RABM_FREE_BUFF_DATA_IND_STRU;
typedef struct
{
    VOS_UINT8                           ucRabId;            /* RAB IDֵ */
    VOS_UINT8                           aucRev[3];          /* ����λ */
    VOS_UINT32                          ulSduLen;           /* ���ݳ��� */
    TTF_MEM_ST                         *pstSdu;             /* ����������ָ�� */
}CDS_RABM_TRANS_DATA_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    QCI_TYPE_ENUM_UINT8                 enQci;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkRabId;
    VOS_UINT8                           ucRev;
} QOS_FC_RAB_CREATE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucRev[3];
} QOS_FC_RAB_RELEASE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    VOS_UINT32                          ulVoicePreferActInd;
}RABM_CDS_VOICEPREFER_ACT_IND_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetRabIdStatus
(
    VOS_UINT8                           ucRabId
);

VOS_VOID NAS_RABM_UL_DataReq
(
    CDS_RABM_TRANS_DATA_STRU           *pstUlData
);

extern VOS_VOID CDS_GSM_DL_DataInd
(
    CDS_RABM_TRANS_DATA_STRU           *pstDlData,
    MODEM_ID_ENUM_UINT16                enModemId
);
extern VOS_VOID CDS_UMTS_DL_DataInd
(
    CDS_RABM_TRANS_DATA_STRU           *pstDlData,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern VOS_VOID NAS_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag);

VOS_UINT32 NAS_RABM_GetDefaultRabId(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucDeftRabId
);


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

#endif /* end of CdsRabmInterface.h */
