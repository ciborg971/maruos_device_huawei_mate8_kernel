

#ifndef __CDSNDINTERFACE_H__
#define __CDSNDINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "LPSCommon.h"
#include "PsTypeDef.h"
#include "TTFMemInterface.h"

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#pragma warning(disable:4200)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NDCLIENT_CDS_MSG_HDR                  (PS_MSG_ID_NDCLIENT_TO_CDS_BASE)
#define CDS_NDCLIENT_MSG_HDR                  (PS_MSG_ID_CDS_TO_NDCLIENT_BASE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NDCLIENT_CDS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��ND CLIENT���ص�ȷ����Ϣ
*****************************************************************************/
enum NDCLIENT_CDS_RESULT_ENUM
{
    NDCLIENT_CDS_RESULT_SUCC                 = 0x00,
    NDCLIENT_CDS_RESULT_FAIL                 = 0x01,

    NDCLIENT_CDS_RESULT_BUTT
};
typedef VOS_UINT32 NDCLIENT_CDS_RESULT_ENUM_UINT32;

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
 �ṹ��    : NDCLIENT_CDS_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ND CLIENT��CDSģ���Ľӿ���Ϣ
*****************************************************************************/
enum NDCLIENT_CDS_MSG_TYPE_ENUM
{
    ID_NDCLIENT_CDS_START_FILTER_REQ         = (NDCLIENT_CDS_MSG_HDR + 0x00), /**/    /* NDCLIENT֪ͨCDS����RA���� */
    ID_CDS_NDCLIENT_START_FILTER_CNF         = (CDS_NDCLIENT_MSG_HDR + 0x00), /**/    /* ������Ϣȷ����Ϣ */

    ID_NDCLIENT_CDS_STOP_FILTER_REQ          = (NDCLIENT_CDS_MSG_HDR + 0x01), /**/    /* NDCLIENT֪ͨCDSֹͣRA���� */
    ID_CDS_NDCLIENT_STOP_FILTER_CNF          = (CDS_NDCLIENT_MSG_HDR + 0x01), /**/    /* ������Ϣȷ����Ϣ */

    ID_NDCLIENT_CDS_DATA_REQ                 = (NDCLIENT_CDS_MSG_HDR + 0x02), /**/    /* ND CLIENT��CDS����RS��Ϣ */

    ID_CDS_NDCLIENT_ND_DATA_IND              = (CDS_NDCLIENT_MSG_HDR + 0x02), /**/    /* IMS�£��ϱ�ND DATA IND */

    ID_NDCLIENT_CDS_MSG_TYPE_END
};
typedef VOS_UINT32 NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NDCLIENT_CDS_DATA_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ND CLIENT��CDS����RS��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32  ulMsgId;             /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16               enModemId;           /*ModemId*/
    VOS_UINT8                          ucRabId;             /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                          aucRev[1];           /*����λ*/
    TTF_MEM_ST                        *pstIpPacket;         /*���ݰ�ָ��*/
} NDCLIENT_CDS_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NDCLIENT_CDS_START_FILTER_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ND CLIENT��CDS���Ϳ���RA��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} NDCLIENT_CDS_START_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CDS_NDCLIENT_START_FILTER_CNF
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��ND CLIENT�ظ�����RA��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    NDCLIENT_CDS_RESULT_ENUM_UINT32     enRslt;
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} CDS_NDCLIENT_START_FILTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NDCLIENT_CDS_STOP_FILTER_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ND CLIENT��CDS����ֹͣRA��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} NDCLIENT_CDS_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CDS_NDCLIENT_STOP_FILTER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��ND CLIENT�ظ�ֹͣRA��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    NDCLIENT_CDS_RESULT_ENUM_UINT32     enRslt;
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} CDS_NDCLIENT_STOP_FILTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CDS_NDCLIENT_STOP_FILTER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������IMS IPV6���س����£�CDS��ND������˺��ϱ�����ND CLIENT.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   enMsgId;                                /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                           aucRsv[1];                              /*����λ*/
    VOS_UINT32                          ulLen;                                  /*���ݰ�����*/
    VOS_UINT8                           aucData[0];                             /*���ݰ�����*/
}CDS_NDCLIENT_ND_DATA_IND_STRU;

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

#endif /* end of CdsNdInterface.h */

