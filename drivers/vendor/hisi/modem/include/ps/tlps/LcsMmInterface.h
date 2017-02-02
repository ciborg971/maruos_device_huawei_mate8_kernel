

#ifndef __LCSMMINTERFACE_H__
#define __LCSMMINTERFACE_H__

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
#include "MmCmInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/
#define PS_MSG_ID_LCS_TO_MM_BASE 0
#define PS_MSG_ID_MM_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LCS_MM_MSG_ID_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : LCS��MM֮�����Ϣö��
*****************************************************************************/
enum    LCS_MM_MSG_ID_ENUM_UINT32
{
    /* LCS����MM����Ϣԭ�� */
    ID_LCS_MM_EST_REQ                   = 0x01+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_EST_REQ_STRU */
    ID_LCS_MM_DATA_REQ                  = 0x02+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_DATA_REQ_STRU */
    ID_LCS_MM_REL_REQ                   = 0x03+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_REL_REQ_STRU */


    /* MM���͸�LCS����Ϣԭ��*/
    ID_MM_LCS_EST_CNF                   = 0x01+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_EST_CNF_STRU */
    ID_MM_LCS_DATA_IND                  = 0x02+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_DATA_IND_STRU */
    ID_MM_LCS_REL_IND                   = 0x03+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_REL_IND_STRU */

    ID_LCS_MM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LCS_MM_MSG_ID_ENUM_UINT32;




/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: LCS_MM_EST_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LCS����MM����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} LCS_MM_EST_REQ_STRU;

/*****************************************************************************
 �ṹ����: MM_LCS_EST_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:MM��SS�Ľ����ظ����ظ�����Ϣ����Ϊ�Ž����ɹ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} MM_LCS_EST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LCS_MM_AIR_MSG_STRU
 �ṹ˵��  : LCS�տ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulLcsMsgSize;       /* ���Ȳ�����256                    */
    VOS_UINT8                          aucLcsMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ�����             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LCS_MM_AIR_MSG_STRU;

/*****************************************************************************
 �ṹ����: LCS_MM_DATA_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LCS�������ݷ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    LCS_MM_AIR_MSG_STRU                 stLcsMsg;
} LCS_MM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ����: MM_LCS_DATA_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:���෢�͵�LCS�տ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    LCS_MM_AIR_MSG_STRU                 stLcsMsg;
} MM_LCS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ����: LCS_MM_REL_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LCS֪ͨMMʵ���ͷ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} LCS_MM_REL_REQ_STRU;


/*****************************************************************************
 �ṹ����: MM_LCS_REL_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: MM֪ͨLCS��·�ͷ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SS_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    VOS_UINT32      			ulRelCause;
} MM_LCS_REL_IND_STRU;


/*****************************************************************************
 �ṹ����: LPP_LCS_GNSS_ASSISTDATA_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LPP����LCS��ȡGNSS��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulLppMsgSize;       
    VOS_UINT8                           aucLppMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ����� */
}LPP_LCS_GNSS_ASSISTDATA_REQ_STRU;

/*****************************************************************************
 �ṹ����: LCS_LPP_GNSS_ASSISTDATA_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulRslt;/*0:��ʾ�ɹ���1����ʾʧ��*/
}LCS_LPP_GNSS_ASSISTDATA_CNF_STRU;


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

#endif /* end of LcsMmInterface.h */


