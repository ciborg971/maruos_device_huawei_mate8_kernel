

#ifndef __BASTETWRRCINTERFACE_H__
#define __BASTETWRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
typedef VOS_UINT32 ( *BST_WRRC_RECV_NET_QUAL_FUNC)(
    const VOS_UINT32        ulModemId,
    const VOS_UINT32        ulRatMode,
    const VOS_UINT32        ulCellId,
    const VOS_INT16         sRscp,
    const VOS_INT16         sEcio );
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  ö����    : WRRC_BASTET_MSG_ID_ENUM
  Э����  :
  ASN.1���� :
  ö��˵��  : WRRC��Bastetģ�鷢����Ϣ����
*****************************************************************************/
enum WRRC_BASTET_MSG_ID_ENUM
{
    /* WRRC����Bastet����Ϣԭ�� */
    ID_WRRC_BASTET_RRC_STATUS_IND       = 0,      /* _H2ASN_MsgChoice WRRC_BASTET_STATUS_IND_STRU */
    ID_WRRC_BASTET_NET_QUAL_CB,                   /* _H2ASN_MsgChoice BST_WRRC_REG_NET_CB_STRU */
    ID_WRRC_BASTET_ID_ENUM_BUTT
};
typedef VOS_UINT32 WRRC_BASTET_MSG_ID_ENUM_UINT32;

enum BASTET_WRRC_STATE_ENUM
{
    BASTET_WRRC_STATE_CELL_DCH          = 0,
    BASTET_WRRC_STATE_CELL_FACH         = 1,
    BASTET_WRRC_STATE_CELL_PCH          = 2,
    BASTET_WRRC_STATE_URA_PCH           = 3,
    BASTET_WRRC_STATE_IDLE              = 4,
    BASTET_WRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_WRRC_STATE_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
/*****************************************************************************
  �ṹ��    : WRRC_BASTET_RRC_STATUS_IND_STRU
  Э����  :
  ASN.1���� :
  �ṹ˵��  : WRRC��Bastetģ�鷢����Ϣ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/
    BASTET_WRRC_STATE_ENUM_UINT8        enRrcState;          /* ��ǰRRC״̬ */
    VOS_UINT8                           aucReserved[3];      /* �ֽڶ��� */
} WRRC_BASTET_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : BST_WRRC_REG_NET_CB_STRU
 �ṹ˵��  : BASTET��WRRC����ԭ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /*_H2ASN_Skip*/
    VOS_UINT32                          ulModemId;
    VOS_UINT32                          ulRatMode;
    BST_WRRC_RECV_NET_QUAL_FUNC         pfRcvCb;
} BST_WRRC_REG_NET_CB_STRU;
typedef struct
{
    VOS_UINT32                         ulModemId;
    VOS_UINT32                         ulRatMode;
    BST_WRRC_RECV_NET_QUAL_FUNC        pfFunCB;
}BST_WRRC_NET_QUAL_STRU;

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
    WRRC_BASTET_MSG_ID_ENUM_UINT32      enMsgID;    /*_H2ASN_MsgChoice_Export WRRC_BASTET_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          WRRC_BASTET_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}BASTET_Wrrc_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    BASTET_Wrrc_MSG_DATA                stMsgData;
}BastetWrrcinterface_MSG;


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

#endif /* end of BastetWrrcinterface.h */
