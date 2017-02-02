

#ifndef __IMSAINTERFACE_H__
#define __IMSAINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "TafClientApi.h"


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




/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
 ö����    : IMSA_INTER_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������ϢID����
*****************************************************************************/
enum    IMSA_INTER_MSG_ID_ENUM
{
    /* CONTROL����REG����Ϣԭ�� */
    ID_IMSA_NORMAL_REG_STATUS_NOTIFY        = TAF_IMSA_COMM_MSG_BASE,           /* _H2ASN_MsgChoice IMSA_NORMAL_REG_STATUS_NOTIFY_STRU */

    ID_IMSA_INTER_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_INTER_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    ö����    : IMSA_SUBCRIBE_TYPE_ENUM
    ö��˵��  : ��������
*****************************************************************************/
enum IMSA_SUBCRIBE_TYPE_ENUM
{
    IMSA_SUBCRIBE_TYPE_NORMAL_REG       = 0x00,

    IMSA_SUBCRIBE_TYPE_BUTT             = 0xFF
};
typedef VOS_UINT8 IMSA_SUBCRIBE_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_NORMAL_REG_STATUS_ENUM
    ö��˵��  : ��ͨע��״̬
*****************************************************************************/
enum IMSA_NORMAL_REG_STATUS_ENUM
{
    IMSA_NORMAL_REG_STATUS_DEREG        = 0x00,
    IMSA_NORMAL_REG_STATUS_DEREGING     = 0x01,
    IMSA_NORMAL_REG_STATUS_REGING       = 0x02,
    IMSA_NORMAL_REG_STATUS_REG          = 0x03,

    IMSA_NORMAL_REG_STATUS_BUTT             = 0xFF
};
typedef VOS_UINT32 IMSA_NORMAL_REG_STATUS_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : IMSA_NORMAL_REG_STATUS_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_NORMAL_REG_STATUS_NOTIFY_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus;
    VOS_UINT32                          ulPara;
    VOS_UINT32                          ulSubscriptionId;
} IMSA_NORMAL_REG_STATUS_NOTIFY_STRU;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    IMSA_INTER_MSG_ID_ENUM_UINT32       ulMsgId;            /* _H2ASN_MsgChoice_Export IMSA_INTER_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_INTER_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    IMSA_INTERFACE_MSG_DATA             stMsgData;
} ImsaInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  IMSA_AddSubscription
(
    VOS_UINT32                          ulPid,
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulSubscriptionId
);

extern VOS_UINT32  IMSA_DeleteSubscription(VOS_UINT32 ulSubscriptionId);


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

#endif /* end of ImsaInterface.h */

