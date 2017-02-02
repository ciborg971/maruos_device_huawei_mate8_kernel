/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TcRabmInterface.h
  Description     : EmmTcInterface.h header file
  History         :
      1.lihong00150010       2009-10-14   Draft Enact

******************************************************************************/

#ifndef __TCRABMINTERFACE_H__
#define __TCRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/*RABM->TC Command��Ϣǰ3���ֽں궨�� RABM->TC*/
#define ERABM_ETC_MSG_ID_HEADER            PS_MSG_ID_RABM_TO_TC_BASE

/*TC ->RABM Command��Ϣǰ3���ֽں궨�� TC->RABM*/
#define ETC_ERABM_MSG_ID_HEADER            PS_MSG_ID_TC_TO_RABM_BASE

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : ETC_ERABM_MSG_TYPE_ENUM
 ö��˵��  : TC��RABM��Ϣ����
*****************************************************************************/
enum ETC_ERABM_MSG_TYPE_ENUM
{
    /*��Ϣԭ��*/
    /*TC���͸�RABM����Ϣԭ��*/
    ID_ETC_ERABM_ACTIVATE_TEST_MODE             = (0x01+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_ACTIVATE_TEST_MODE_STRU */
    ID_ETC_ERABM_DEACTIVATE_TEST_MODE           = (0x02+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_DEACTIVATE_TEST_MODE_STRU */
    ID_ETC_ERABM_REL_REQ                        = (0x03+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_REL_REQ_STRU */
    ID_ETC_ERABM_SUSPEND_RSP                    = (0x04+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_SUSPEND_RSP_STRU */
    ID_ETC_ERABM_RESUME_RSP                     = (0x05+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_RESUME_RSP_STRU */

    /*RABM���͸�TC����Ϣԭ��*/
    ID_ETC_ERABM_REL_IND                        = (0x01+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_REL_IND_STRU */
    ID_ETC_ERABM_SUSPEND_IND                    = (0x02+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_SUSPEND_IND_STRU */
    ID_ETC_ERABM_RESUME_IND                     = (0x03+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_RESUME_IND_STRU */

    ID_ETC_ERABM_BUTT
};
typedef VOS_UINT32 ETC_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : ETC_ERABM_RSLT_TYPE_ENUM
 ö��˵��  : TC�ظ�RABM��Ϣ���ö��
*****************************************************************************/
enum ETC_ERABM_RSLT_TYPE_ENUM
{
    ETC_ERABM_RSLT_TYPE_SUCC             = 0x00, /*�ɹ�*/
    ETC_ERABM_RSLT_TYPE_FAIL             = 0x01, /*ʧ��*/

    ETC_ERABM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 ETC_ERABM_RSLT_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : ETC_ERABM_ACTIVATE_TEST_MODE_STRU
 �ṹ˵��  : ETC_ERABM_ACTIVATE_TEST_MODE_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ETC_ERABM_ACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 �ṹ��    : ETC_ERABM_DEACTIVATE_TEST_MODE_STRU
 �ṹ˵��  : ETC_ERABM_DEACTIVATE_TEST_MODE_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ETC_ERABM_DEACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 �ṹ��    : ETC_ERABM_REL_REQ_STRU
 �ṹ˵��  : ETC_ERABM_REL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* ��Ϣͷ*/
    VOS_UINT32                           ulReserved;         /* ������*/
}ETC_ERABM_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ETC_ERABM_REL_IND_STRU
 �ṹ˵��  : ETC_ERABM_REL_IND_STRU���ݽṹ
*****************************************************************************/
typedef ETC_ERABM_REL_REQ_STRU ETC_ERABM_REL_IND_STRU;

/*****************************************************************************
 �ṹ����: ETC_ERABM_SUSPEND_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:RABM->TC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} ETC_ERABM_SUSPEND_IND_STRU;

/*****************************************************************************
 �ṹ����: ETC_ERABM_SUSPEND_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:TC->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt;
} ETC_ERABM_SUSPEND_RSP_STRU;

/*****************************************************************************
 �ṹ����: ETC_ERABM_RESUME_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:RABM->TC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} ETC_ERABM_RESUME_IND_STRU;


/*****************************************************************************
 �ṹ����: ETC_ERABM_RESUME_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:TC->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt;
} ETC_ERABM_RESUME_RSP_STRU;


typedef struct
{
    ETC_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export ETC_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          ETC_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}ETC_ERABM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    ETC_ERABM_MSG_DATA                    stMsgData;
}TcRabmInterface_MSG;

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

#endif /* end of TcRabmInterface.h */
