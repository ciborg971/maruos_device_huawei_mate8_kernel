
#ifndef  MSG_IMSA_INTERFACE_H
#define  MSG_IMSA_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafClientApi.h"
#include "NasSms.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/


enum MSG_IMSA_MSG_TYPE_ENUM
{
    ID_MSG_IMSA_RP_DATA_REQ   =TAF_MSG_IMSA_MSG_BASE,       /* _H2ASN_MsgChoice MSG_IMSA_RP_DATA_REQ_STRU */
    ID_MSG_IMSA_REPORT_REQ,                                 /* _H2ASN_MsgChoice MSG_IMSA_REPORT_REQ_STRU */
    ID_MSG_IMSA_SMMA_REQ,                                   /* _H2ASN_MsgChoice MSG_IMSA_SMMA_REQ_STRU */

    ID_IMSA_MSG_DATA_IND      =TAF_MSG_IMSA_MSG_BASE+0x100,  /* _H2ASN_MsgChoice IMSA_MSG_DATA_IND_STRU */
    ID_IMSA_MSG_REPORT_IND,                                 /* _H2ASN_MsgChoice IMSA_MSG_REPORT_IND_STRU */
    ID_IMSA_MSG_MT_ERR_IND,                                 /* _H2ASN_MsgChoice IMSA_MSG_MT_ERR_IND_STRU */

    ID_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  MSG_IMSA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
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
  7 STRUCT����
*****************************************************************************/

typedef SMT_SMR_DATA_STRU MSG_IMSA_RP_DATA_REQ_STRU;


typedef SMT_SMR_DATA_STRU MSG_IMSA_REPORT_REQ_STRU;


typedef SMT_SMR_SMMA_STRU MSG_IMSA_SMMA_REQ_STRU;


typedef SMR_SMT_EST_IND_STRU IMSA_MSG_DATA_IND_STRU;


typedef SMR_SMT_MO_REPORT_STRU IMSA_MSG_REPORT_IND_STRU;


typedef SMR_SMT_MT_ERR_STRU IMSA_MSG_MT_ERR_IND_STRU;


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
    MSG_IMSA_MSG_TYPE_ENUM_UINT32       enMsgId;
    
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MSG_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}MSG_IMSA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MSG_IMSA_MSG_DATA                   stMsgData;
}MsgImsaInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MSG_IMSA_INTERFACE_H */
