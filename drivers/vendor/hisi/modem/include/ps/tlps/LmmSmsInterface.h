/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LmmSmsInterface.h
  Description     : LmmSmsInterface.h header file
  History         :
      1.sunbing 49683       2011-10-19   Draft Enact

******************************************************************************/

#ifndef __LMMSMSINTERFACE_H__
#define __LMMSMSINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    LMM_SMS_MSG_ID_ENUM
{
    /* SMS����LMM����Ϣԭ�� */
    ID_SMS_LMM_EST_REQ                  = 0x01+PS_MSG_ID_SMS_TO_LMM_BASE,       /* _H2ASN_MsgChoice SMS_LMM_EST_REQ_STRU */
    ID_SMS_LMM_DATA_REQ                 = 0x02+PS_MSG_ID_SMS_TO_LMM_BASE,       /* _H2ASN_MsgChoice SMS_LMM_DATA_REQ_STRU */


    /* LMM���͸�MMC����Ϣԭ��*/
    ID_LMM_SMS_EST_CNF                  = 0x01+PS_MSG_ID_LMM_TO_SMS_BASE,       /* _H2ASN_MsgChoice LMM_SMS_EST_CNF_STRU */
    ID_LMM_SMS_DATA_IND                 = 0x02+PS_MSG_ID_LMM_TO_SMS_BASE,       /* _H2ASN_MsgChoice LMM_SMS_DATA_IND_STRU */
    ID_LMM_SMS_ERR_IND                  = 0x03+PS_MSG_ID_LMM_TO_SMS_BASE,       /* _H2ASN_MsgChoice LMM_SMS_ERR_IND_STRU */
    ID_LMM_SMS_SERVICE_STATUS_IND       = 0x04+PS_MSG_ID_LMM_TO_SMS_BASE,       /* _H2ASN_MsgChoice LMM_SMS_SERVICE_STATUS_IND_STRU */

    ID_LMM_SMS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LMM_SMS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_SMS_ERR_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����״̬������
*****************************************************************************/
enum LMM_SMS_ERR_CAUSE_ENUM
{
    LMM_SMS_ERR_CAUSE_UE_MODE_PS_ONLY   = 0x00000000,
    LMM_SMS_ERR_CAUSE_ACCESS_BARRED,
    LMM_SMS_ERR_CAUSE_USIM_CS_INVALID,
    LMM_SMS_ERR_CAUSE_USIM_PS_INVALID,
    LMM_SMS_ERR_CAUSE_CS_SER_NOT_AVAILABLE,
    LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED,
    LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED,
    LMM_SMS_ERR_CAUSE_T3402_RUNNING,
    LMM_SMS_ERR_CAUSE_RRC_CONN_NOT_EXIST,
    LMM_SMS_ERR_CAUSE_OTHERS,

    LMM_SMS_ERR_CAUSE_BUTT
};
typedef VOS_UINT32 LMM_SMS_ERR_CAUSE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
 �ṹ����: SMS_LMM_EST_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SMS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          ulEstCause;   /*Ӧ�ò���Ҫ��*/
} SMS_LMM_EST_REQ_STRU;

/*****************************************************************************
 �ṹ����: LMM_SMS_EST_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SMS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} LMM_SMS_EST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMM_SMS_MSG_STRU
 �ṹ˵��  : LMM_SMS_MSG_STRU�տ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulSmsMsgSize;       /* ���Ȳ�����256                    */
    VOS_UINT8                          aucSmsMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ�����             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LMM_SMS_MSG_STRU;

/*****************************************************************************
 �ṹ����: SMS_LMM_DATA_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SMS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_SMS_MSG_STRU                    stSmsMsg;
} SMS_LMM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ����: LMM_SMS_DATA_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SMS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_SMS_MSG_STRU                    stSmsMsg;
} LMM_SMS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ����: LMM_SMS_REL_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ��·�ͷ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SMS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause;

} LMM_SMS_ERR_IND_STRU;


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

#endif /* end of LmmSmsInterface.h */
