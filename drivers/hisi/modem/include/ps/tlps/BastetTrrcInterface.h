

#ifndef __BASTETTRRCINTERFACE_H__
#define __BASTETTRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TRRC_BASTET_MSG_HDR                  (0)
#define BASTET_TRRC_MSG_HDR                  (0)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  ö����    : TRRC_BASTET_MSG_ID_ENUM
  Э����  :
  ASN.1���� :
  ö��˵��  : TRRC��Bastetģ����Ϣ����
*****************************************************************************/
enum TRRC_BASTET_MSG_ID_ENUM
{
    /* TRRC����Bastet����Ϣԭ�� */
    ID_TRRC_BASTET_RRC_STATUS_IND           = TRRC_BASTET_MSG_HDR + 0x00,         /* _H2ASN_MsgChoice TRRC_BASTET_STATUS_IND_STRU */
    ID_TRRC_BASTET_SERVICE_CELL_INFO_IND    = TRRC_BASTET_MSG_HDR + 0x01,         /* _H2ASN_MsgChoice TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU */
    ID_TRRC_BASTET_ID_ENUM_BUTT
};
typedef VOS_UINT32  TRRC_BASTET_MSG_ID_ENUM_UINT32;

enum BASTET_TRRC_STATE_ENUM
{
    BASTET_TRRC_STATE_IDLE              = 0,         /* IDLE̬ */
    BASTET_TRRC_STATE_CELL_PCH             ,         /* CELL_PCH̬ */
    BASTET_TRRC_STATE_URA_PCH              ,         /* URA_PCH̬ */
    BASTET_TRRC_STATE_CELL_FACH            ,         /* CELL_FACH̬ */
    BASTET_TRRC_STATE_CELL_DCH             ,         /* CELL_DCH̬ */

    BASTET_TRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_TRRC_STATE_ENUM_UINT8;
/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
/*****************************************************************************
  �ṹ��    : TRRC_BASTET_STATUS_IND_STRU
  Э����  :
  ASN.1���� :
  �ṹ˵��  : TRRC��Bastetģ�鷢��RRC״̬��Ϣ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/
    BASTET_TRRC_STATE_ENUM_UINT8        enRrcState;          /* ��ǰRRC״̬ */
    VOS_UINT8                           aucReserved[3];      /* �ֽڶ��� */
} TRRC_BASTET_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ����   : TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : TDS����С����Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/

    VOS_UINT32                          ulCellId;
    VOS_INT16                           sRscp;                /*��Χ(-141,-44),99Ϊ��Ч*/
    VOS_UINT8                           aucResv[2];
}TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU;



/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/


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
    TRRC_BASTET_MSG_ID_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export TRRC_BASTET_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                               aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TRRC_BASTET_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}Bastet_TRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    Bastet_TRRC_MSG_DATA                    stMsgData;
}BastetTrrcInterface_MSG;


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

#endif /* end of BastetTrrcInterface.h */
