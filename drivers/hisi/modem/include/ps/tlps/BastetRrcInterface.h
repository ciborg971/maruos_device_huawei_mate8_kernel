

#ifndef __BASTETRRCINTERFACE_H__
#define __BASTETRRCINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"


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
  2 �궨��
*****************************************************************************/
#define LRRC_BASTET_MSG_HDR                  (0)
#define BASTET_LRRC_MSG_HDR                  (0)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum BASTET_LRRC_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                              /* ��ϢID */                    /* ��ע */
    ID_BASTET_LRRC_CON_TO_IDLE_NTF              = LRRC_BASTET_MSG_HDR + 0x00,   /* _H2ASN_MsgChoice BASTET_RRC_LTE_TO_IDLE_REQ_STRU */
    ID_LRRC_BASTET_RRC_STATUS_IND               = LRRC_BASTET_MSG_HDR + 0x01,   /* _H2ASN_MsgChoice BASTET_RRC_LRRC_STATUS_IND_STRU */
    ID_LRRC_BASTET_SERVICE_CELL_INFO_IND        = LRRC_BASTET_MSG_HDR + 0x02,   /* _H2ASN_MsgChoice LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU */

    ID_BASTET_LRRC_MSG_TYPE_BUTT
};
typedef VOS_UINT32 BASTET_LRRC_MSG_TYPE_ENUM_UINT32;



enum BASTET_LRRC_STATE_ENUM
{
    BASTET_LRRC_STATE_IDLE          = 0,
    BASTET_LRRC_STATE_CONNECTED,
    BASTET_LRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_LRRC_STATE_ENUM_UINT8;



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
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/
}BASTET_RRC_LTE_TO_IDLE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/
    BASTET_LRRC_STATE_ENUM_UINT8                enRrcState;
    VOS_UINT8                                   enReserve[3];
}BASTET_RRC_LRRC_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ����   : LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LTE����С����Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulCellId;
    VOS_INT16                           sRsrp;                /*��Χ(-141,-44),99Ϊ��Ч*/
    VOS_INT16                           sRsrq;                /*��Χ(-40,-6),99Ϊ��Ч*/
}LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU;



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
    BASTET_LRRC_MSG_TYPE_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export BASTET_LRRC_MSG_TYPE_ENUM_UINT32*/

    VOS_UINT8                                 aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          BASTET_LRRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}BASTET_RRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    BASTET_RRC_MSG_DATA                       stMsgData;
}BastetRrcInterface_MSG;



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

