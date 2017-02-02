

#ifndef __TAF_XSMS_STK_INTERFACE_H__
#define __TAF_XSMS_STK_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafAppXsmsInterface.h"


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
enum TAF_XSMS_STK_MSG_TYPE_ENUM
{
    ID_STK_XSMS_SEND_SMS_REQ            = 0,        /* _H2ASN_MsgChoice STK_XSMS_SEND_SMS_REQ_STRU*/ /***< @sa STK_XSMS_SEND_SMS_REQ_STRU */
    ID_XSMS_STK_SEND_SMS_CNF            = 1,        /* _H2ASN_MsgChoice XSMS_STK_SEND_SMS_CNF_STRU*/ /***< @sa XSMS_STK_SEND_SMS_CNF_STRU */
    ID_XSMS_STK_SEND_SMS_RSLT_IND       = 2,        /* _H2ASN_MsgChoice XSMS_STK_SEND_SMS_RSLT_IND_STRU*/ /***< @sa XSMS_STK_SEND_SMS_RSLT_IND_STRU */
    ID_XSMS_STK_RCV_SMS_IND             = 3,        /* _H2ASN_MsgChoice XSMS_STK_RCV_SMS_IND_STRU*/ /***< @sa XSMS_STK_RCV_SMS_IND_STRU */
    ID_XSMS_STK_MSG_TYPE_BUTT
};

typedef VOS_UINT32 TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32;


enum TAF_XSMS_STK_PP_DOWNLOAD_ERR_ENUM
{
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_NONE           = 0,
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_DEST_BUSY      = 33,
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_OTHER_PROBLEM  = 39
};

typedef VOS_UINT16 TAF_XSMS_STK_PP_DOWNLOAD_ERR_ENUM16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/** ****************************************************************************
 * Name        : STK_XSMS_SEND_SMS_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    TAF_XSMS_MESSAGE_STRU               st1XSms;
}STK_XSMS_SEND_SMS_REQ_STRU;

/** ****************************************************************************
 * Name        : XSMS_STK_SEND_SMS_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    VOS_UINT32                          ulRet;                /* FALSE:Xsms���ڱ�ռ�� TRUE������������ */
}XSMS_STK_SEND_SMS_CNF_STRU;


/** ****************************************************************************
 * Name        : XSMS_STK_SEND_SMS_RSLT_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    VOS_UINT32                          ulSendSucc;           /* FALSE:����ʧ�ܣ� TRUE:���ͳɹ� */
    VOS_UINT32                          ulCauseCode;          /* ʧ��ԭ��ֵ���ɹ�ʱ���Դ��ֶ� */
}XSMS_STK_SEND_SMS_RSLT_IND_STRU;

/** ****************************************************************************
 * Name        : XSMS_STK_RCV_SMS_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulTpduLen;
    TAF_XSMS_MESSAGE_STRU               st1XSms;
    VOS_UINT8                           aucTpduData[4];
}XSMS_STK_RCV_SMS_IND_STRU;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif /* End of TafXsmsSTkInterface.h */


