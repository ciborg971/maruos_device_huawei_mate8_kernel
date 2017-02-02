

#ifndef _TAF_XPDS_XSMS_INTERFACE_H_
#define _TAF_XPDS_XSMS_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafAppXsmsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16
 ö��˵��  : XPDS XSMS ������Ϣ����
*****************************************************************************/
enum TAF_XPDS_XSMS_MSG_TYPE_ENUM
{
    ID_XSMS_XPDS_RCV_IND                 = 0,    /* _H2ASN_MsgChoice TAF_XSMS_XPDS_REV_IND_STRU */
    ID_XPDS_XSMS_SEND_REQ                = 1,    /* _H2ASN_MsgChoice TAF_XPDS_XSMS_SEND_REQ_STRU */

    ID_XPDS_XSMS_MSG_TYPE_BUTT
};

typedef VOS_UINT16 TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16;

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
 �ṹ��    : TAF_XSMS_XPDS_REV_IND_STRU
 �ṹ˵��  : XSMS��XPDS �ϱ���Ϣ
****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16  enMsgName;          /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    TAF_XSMS_ADDR_STRU                  stXsmsAddr;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[4];
}TAF_XSMS_XPDS_REV_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XPDS_XSMS_SEND_REQ_STRU
 �ṹ˵��  : XPDS �oXSMS��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16  enMsgName;          /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    TAF_XSMS_ADDR_STRU                  stXsmsAddr;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[4];
}TAF_XPDS_XSMS_SEND_REQ_STRU;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16  ulMsgId;            /*_H2ASN_MsgChoice_Export TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16*/
    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XPDS_XSMS_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}TAF_XPDS_XSMS_PIF_MSG_TYPE_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_XSMS_PIF_MSG_TYPE_DATA     stMsgReq;
}TafXpdsXsmsInterface_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/




#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

