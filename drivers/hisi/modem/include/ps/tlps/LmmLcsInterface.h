

#ifndef __LMMLCSINTERFACE_H__
#define __LMMLCSINTERFACE_H__

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
#define PS_MSG_ID_LCS_TO_LMM_BASE 0
#define PS_MSG_ID_LMM_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LMM_LCS_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LMM��LCS֮�����Ϣö��
*****************************************************************************/
enum    LMM_LCS_MSG_ID_ENUM
{
    /* LCS����LMM����Ϣԭ�� */
    ID_LCS_LMM_EST_REQ                  = 0x01+PS_MSG_ID_LCS_TO_LMM_BASE,       /* _H2ASN_MsgChoice LCS_LMM_EST_REQ_STRU */
    ID_LCS_LMM_DATA_REQ                 = 0x02+PS_MSG_ID_LCS_TO_LMM_BASE,       /* _H2ASN_MsgChoice LCS_LMM_DATA_REQ_STRU */


    /* LMM���͸�LCS����Ϣԭ��*/
    ID_LMM_LCS_EST_CNF                  = 0x01+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_EST_CNF_STRU */
    ID_LMM_LCS_DATA_CNF                 = 0x02+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_DATA_CNF_STRU */
    ID_LMM_LCS_DATA_IND                 = 0x03+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_DATA_IND_STRU */
    ID_LMM_LCS_POS_CAP_INFO_IND         = 0x04+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_POS_CAP_INFO_IND_STRU */
    ID_LMM_LCS_REL_IND                  = 0x05+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_REL_IND_STRU */

    ID_LMM_LCS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LMM_LCS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_LCS_EST_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������ö��
*****************************************************************************/
enum LMM_LCS_EST_RESULT_ENUM
{
    LMM_LCS_EST_RSLT_SUCC                           = 0,/* �����ɹ� */
    LMM_LCS_EST_RSLT_FAIL_PS_NOT_ATTACHED           = 1,/* PS��δע�� */
    LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED     = 2,/* PS������ע�� */
    LMM_LCS_EST_RSLT_FAIL_USIM_PS_INVALID           = 3,/* USIM����Ч */
    LMM_LCS_EST_RSLT_FAIL_ACCESS_BARRED             = 4,/* ��BAR */
    LMM_LCS_EST_RSLT_FAIL_STATE_CANNOT_SERVICE      = 5,/* ��ǰ״̬�޷�����SERVICE */
    LMM_LCS_EST_RSLT_FAIL_EPC_LCS_NOT_SUPPORT       = 6,/* EPC-LCS��֧�� */
    LMM_LCS_EST_RSLT_FAIL_3411_RUNNING              = 7,/* 3411�����У����Թ�10s�ٳ��� */
    LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL              = 8,/* SERVICEʧ�ܣ�����2s���ٳ��� */
    LMM_LCS_EST_RSLT_FAIL_OTHERS                    = 9,/* ����ʧ��ԭ��ֵ */

    LMM_LCS_EST_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LCS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: LMM_LCS_SEND_RSLT_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:��Ϣ���ͽ��ö��
*****************************************************************************/
enum LMM_LCS_SEND_RSLT_ENUM
{
    LMM_LCS_SEND_RSLT_SUCCESS                       = 0,/* ���ͳɹ� */
    LMM_LCS_SEND_RSLT_FAIL_PS_NOT_ATTACHED          = 1,/* PS��δע�� */
    LMM_LCS_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED    = 2,/* PS������ע�� */
    LMM_LCS_SEND_RSLT_FAIL_USIM_PS_INVALID          = 3,/* USIM����Ч */
    LMM_LCS_SEND_RSLT_FAIL_ACCESS_BARRED            = 4,/* ��BAR */
    LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST       = 5,/* ����״̬�����ڣ�SS������EST_REQ������ */
    LMM_LCS_SEND_RSLT_FAIL_EPC_LCS_NOT_SUPPORT      = 6,/* EPC-LCS��֧�� */
    LMM_LCS_SEND_RSLT_RSLT_FAIL_3411_RUNNING        = 7,/* 3411�����У����Թ�10s�ٳ��� */
    LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER                = 8,/* �ײ㷢��ʧ�ܣ�����1s���ٳ��� */
    LMM_LCS_SEND_RSLT_FAIL_OHTERS                   = 9,/* ����ʧ��ԭ��ֵ */

    LMM_LCS_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LCS_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: LMM_LCS_NW_EPC_LCS_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:�����EPC-LCS����
*****************************************************************************/
enum LMM_LCS_NW_EPC_LCS_ENUM
{
    LMM_LCS_NW_EPC_LCS_NOT_SUPPORT          = 0,
    LMM_LCS_NW_EPC_LCS_SUPPORT              = 1,

    LMM_LCS_NW_EPC_LCS_BUTT
};
typedef VOS_UINT32 LMM_LCS_NW_EPC_LCS_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: LMM_LCS_NW_CS_LCS_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:�����CS-LCS����
*****************************************************************************/
enum LMM_LCS_NW_CS_LCS_ENUM
{
    LMM_LCS_NW_CS_LCS_NO_INFORMATION        = 0,
    LMM_LCS_NW_CS_LCS_SUPPORT               = 1,
    LMM_LCS_NW_CS_LCS_NOT_SUPPORT           = 2,
    LMM_LCS_NW_CS_LCS_RESERVED              = 3,

    LMM_LCS_NW_CS_LCS_BUTT
};
typedef VOS_UINT32 LMM_LCS_NW_CS_LCS_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: LMM_LCS_REL_CAUSE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:�ͷ�ԭ��ֵ
*****************************************************************************/
enum LMM_LCS_REL_CAUSE_ENUM
{
    LMM_LCS_REL_CAUSE_USER_INACTIVITY       = 0,
    LMM_LCS_REL_CAUSE_USER_OHTERS           = 1,

    LMM_LCS_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LMM_LCS_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: LCS_LMM_EST_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:SS����LMM����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} LCS_LMM_EST_REQ_STRU;

/*****************************************************************************
 �ṹ����: LMM_LCS_EST_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM��SS�Ľ����ظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_EST_RESULT_ENUM_UINT32      enEstRst;           /*�������*/
} LMM_LCS_EST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMM_LCS_MSG_STRU
 �ṹ˵��  : LCS�տ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulLcsMsgSize;
    VOS_UINT8                          aucLcsMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ�����             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LMM_LCS_MSG_STRU;


/*****************************************************************************
 �ṹ����: LCS_LMM_DATA_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LCS�������ݷ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                           ulOpId;

    LMM_LCS_MSG_STRU                     stLcsMsg;
} LCS_LMM_DATA_REQ_STRU;


/*****************************************************************************
 �ṹ����: LMM_LCS_DATA_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM��SS���ݷ��ͽ���ظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_SEND_RSLT_ENUM_UINT32       enDataCnfRst;       /* Data cnf��� */
} LMM_LCS_DATA_CNF_STRU;


/*****************************************************************************
 �ṹ����: LMM_LCS_DATA_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:���෢�͵�SS�տ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_MSG_STRU                    stLcsMsg;
} LMM_LCS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ����: LMM_LCS_POS_CAP_INFO_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �����LCS��LPP�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_NW_EPC_LCS_ENUM_UINT32      enNwEpcLcs;
    LMM_LCS_NW_CS_LCS_ENUM_UINT32       enNwCsLcs;
} LMM_LCS_POS_CAP_INFO_IND_STRU;


/*****************************************************************************
 �ṹ����: LMM_LCS_REL_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LMM֪ͨLCS��·�ͷ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_REL_CAUSE_ENUM_UINT32       enRelCause;
} LMM_LCS_REL_IND_STRU;


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

#endif /* end of LmmLcsInterface.h */

