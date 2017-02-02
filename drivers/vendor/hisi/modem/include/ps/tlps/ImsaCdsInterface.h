

#ifndef __IMSACDSINTERFACE_H__
#define __IMSACDSINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


#define IMSA_CDS_MSG_ID_HEADER        0
#define CDS_IMSA_MSG_ID_HEADER        10

#define IMSA_CDS_MAX_IMS_BEARER_NUM     (8)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 ö����    : IMSA_CDS_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IMSA��CDS֮�����Ϣ
*****************************************************************************/
enum    IMSA_CDS_MSG_ID_ENUM
{
    /* IMSA����CDS����Ϣԭ�� */
    ID_IMSA_CDS_SET_IMS_BEARER_REQ          = 0x00 + IMSA_CDS_MSG_ID_HEADER,    /* _H2ASN_MsgChoice IMSA_CDS_SET_IMS_BEARER_REQ_STRU */

    /* CDS����IMSA����Ϣԭ�� */
    ID_IMSA_CDS_SET_IMS_BEARER_CNF          = 0x00 + CDS_IMSA_MSG_ID_HEADER,    /* _H2ASN_MsgChoice IMSA_CDS_SET_IMS_BEARER_CNF_STRU */

    ID_IMSA_CDS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_CDS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : IMSA_CDS_IMS_BEARER_TYPE_ENUM
 ö��˵��  : ��������ö��
*****************************************************************************/
enum IMSA_CDS_IMS_BEARER_TYPE_ENUM
{
    IMSA_CDS_IMS_BEARER_TYPE_SIGNAL     = 0x00,
    IMSA_CDS_IMS_BEARER_TYPE_MEDIA      = 0x01,

    IMSA_CDS_IMS_BEARER_TYPE_BUTT       = 0xFF
};
typedef VOS_UINT8 IMSA_CDS_IMS_BEARER_TYPE_ENUM_UINT8;





/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : IMSA_CDS_IMS_BEARER_STRU
 �ṹ˵��  : IMS���ؽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEpsbId;
    IMSA_CDS_IMS_BEARER_TYPE_ENUM_UINT8 enBearerType;
    VOS_UINT8                           aucReserved[2];
} IMSA_CDS_IMS_BEARER_STRU;

/* Add by lihong 2013-12-23 Ut��ims����APN begin */
/*****************************************************************************
 �ṹ��    : IMSA_CDS_IMS_PORT_INFO_STRU
 �ṹ˵��  : IMSʹ�õĶ˿���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMinImsPort;       /* С�� */
    VOS_UINT16                          usMaxImsPort;       /* С�� */
} IMSA_CDS_IMS_PORT_INFO_STRU;
/* Add by lihong 2013-12-23 Ut��ims����APN end */

/*****************************************************************************
 �ṹ��    : IMSA_CDS_SET_IMS_BEARER_REQ_STRU
 �ṹ˵��  : IMSA����CDS���й��˳���������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulImsBearerNum;
    IMSA_CDS_IMS_BEARER_STRU            astImsBearerArray[IMSA_CDS_MAX_IMS_BEARER_NUM];

    /* Add by lihong 2013-12-23 Ut��ims����APN begin */
    IMSA_CDS_IMS_PORT_INFO_STRU         stImsPortInfo;
    /* Add by lihong 2013-12-23 Ut��ims����APN end */
} IMSA_CDS_SET_IMS_BEARER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CDS_SET_IMS_BEARER_REQ_STRU
 �ṹ˵��  : IMSA����CDS���й��˳��ػظ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulResult;
} IMSA_CDS_SET_IMS_BEARER_CNF_STRU;

typedef struct
{
    IMSA_CDS_MSG_ID_ENUM_UINT32         enMsgId;            /*_H2ASN_MsgChoice_Export IMSA_CDS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_CDS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_CDS_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_CDS_INTERFACE_MSG_DATA         stMsgData;
} ImsaCdsInterface_MSG;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of ImsaCdsInterface.h */

