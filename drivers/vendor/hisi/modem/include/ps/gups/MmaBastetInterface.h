
#ifndef _MMA_BASTET_INTERFACE_H_
#define _MMA_BASTET_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum BST_RATMODE_ENUM
{
    BST_RATMODE_GSM                     = 0x00,
    BST_RATMODE_WCDMA                   = 0x01,
    BST_RATMODE_LTE                     = 0x02,
    BST_RATMODE_TDS                     = 0x03,
    BST_RATMODE_BUTT
};
typedef VOS_UINT8  BST_RATMODE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

enum MMA_BASTET_MSG_ID_ENUM
{
    /* MMA����Bastet����Ϣԭ�� */
    ID_MMA_BASTET_RAT_MODE_IND                  = 0,   /* _H2ASN_MsgChoice MMA_BASTET_RAT_MODE_IND_STRU */
    ID_MMA_BASTET_CS_SERVICE_IND,                      /* _H2ASN_MsgChoice MMA_BASTET_CS_SERVICE_IND_STRU */
    ID_MMA_BASTET_SERVICE_STATUE_IND,                  /* _H2ASN_MsgChoice MMA_BASTET_SERVICE_STATUS_IND_STRU */
    ID_MMA_BASTET_ID_ENUM_BUTT
};
typedef VOS_UINT32  MMA_BASTET_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;         /*_H2ASN_Skip*/
    BST_RATMODE_ENUM_UINT8              enRatMode;           /* ��ǰ������ʽ*/
    VOS_UINT8                           aucReserve1[3];     /* �ֽڶ��� */
}MMA_BASTET_RAT_MODE_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  bCSConnected;       /* �Ƿ����CSҵ��*/
    VOS_UINT8                           aucReserve1[3];     /* �ֽڶ��� */
}MMA_BASTET_CS_SERVICE_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;           /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  bCsInservice;           /*CS�Ƿ��з���*/
    PS_BOOL_ENUM_UINT8                  bPsInservice;           /*PS�Ƿ��з���*/
    VOS_UINT8                           aucReserve1[2];       /* �ֽڶ��� */
}MMA_BASTET_SERVICE_STATUS_IND_STRU;



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
    MMA_BASTET_MSG_ID_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export MMA_BASTET_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMA_BASTET_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMA_BASTET_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMA_BASTET_MSG_DATA                 stMsgData;
}MmaBastetInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

