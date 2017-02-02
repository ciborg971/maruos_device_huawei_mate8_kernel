
#ifndef __MMLMMINTERFACE_H__
#define __MMLMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#include "LPSCommon.h"

#include "PsTypeDef.h"



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define MM_LMM_EMERGENCY_NUM_MAX_LEN            (46)
#define MM_LMM_EMERGENCY_NUM_LIST_MAX_RECORDS   (16)
#define MM_LMM_CK_LEN                           16
#define MM_LMM_IK_LEN                           16

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum MM_LMM_MSG_ID_ENUM
{
    /* MM����LMM����Ϣԭ�� */
    ID_MM_LMM_CSFB_SERVICE_START_NOTIFY = 0x01+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU */
    ID_MM_LMM_CSFB_SERVICE_ABORT_NOTIFY = 0x02+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU */
    ID_MM_LMM_HO_SECU_INFO_REQ          = 0x03+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_HO_SECU_INFO_REQ_STRU */
    ID_MM_LMM_SRVCC_STATUS_NOTIFY              = 0x04+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_SRVCC_STATUS_NOTIFY_STRU*/
    ID_MM_LMM_BEGIN_SESSION_NOTIFY      = 0x05+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_BEGIN_SESSION_NOTIFY_STRU*/
    ID_MM_LMM_END_SESSION_NOTIFY        = 0x06+PS_MSG_ID_MM_TO_LMM_BASE,        /* _H2ASN_MsgChoice MM_LMM_END_SESSION_NOTIFY_STRU*/

    /* LMM���͸�MM����Ϣԭ��*/
    ID_LMM_MM_COMBINED_START_NOTIFY_REQ = 0x01+PS_MSG_ID_LMM_TO_MM_BASE,        /* _H2ASN_MsgChoice LMM_MM_COMBINED_START_NOTIFY_REQ_STRU */
    ID_LMM_MM_CSFB_SERVICE_END_IND      = 0x02+PS_MSG_ID_LMM_TO_MM_BASE,        /* _H2ASN_MsgChoice LMM_MM_CSFB_SERVICE_END_IND_STRU */
    ID_LMM_MM_CSFB_SERVICE_PAGING_IND   = 0x03+PS_MSG_ID_LMM_TO_MM_BASE,        /* _H2ASN_MsgChoice LMM_MM_CSFB_SERVICE_PAGING_IND_STRU */
    ID_LMM_MM_INFO_CHANGE_NOTIFY        = 0x04+PS_MSG_ID_LMM_TO_MM_BASE,        /* _H2ASN_MsgChoice LMM_MM_INFO_CHANGE_NOTIFY_STRU */
    ID_LMM_MM_HO_SECU_INFO_CNF          = 0x05+PS_MSG_ID_LMM_TO_MM_BASE,        /* _H2ASN_MsgChoice LMM_MM_HO_SECU_INFO_CNF_STRU */

    ID_MM_LMM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 MM_LMM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : MM_LMM_COMBINED_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������������
*****************************************************************************/
enum MM_LMM_COMBINED_TYPE_ENUM
{
    MM_LMM_COMBINED_ATTACH              = 0,
    MM_LMM_COMBINED_TAU                 = 1,
    MM_LMM_COMBINED_DETACH              = 2,

    MM_LMM_COMBINED_TYPE_BUTT
};
typedef VOS_UINT32 MM_LMM_COMBINED_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MM_LMM_CSFB_SERVICE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CSFB����
*****************************************************************************/
enum    MM_LMM_CSFB_SERVICE_TYPE_ENUM
{
    MM_LMM_CSFB_SERVICE_MO_NORMAL       = 0,
    MM_LMM_CSFB_SERVICE_MO_EMERGENCY    = 1,
    MM_LMM_CSFB_SERVICE_MT_NORMAL       = 2,

    MM_LMM_CSFB_SERVICE_BUTT
};
typedef VOS_UINT32 MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MM_LMM_CSFB_SERVICE_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : SERVICE�Ľ������
*****************************************************************************/
enum   MM_LMM_CSFB_SERVICE_RSLT_ENUM
{
    MM_LMM_CSFB_SERVICE_RSLT_FAILURE                         = 0,   /* ����ʧ��ԭ��             */
    MM_LMM_CSFB_SERVICE_RSLT_CN_REJ                          = 1,   /* ����ܾ�                 */
    MM_LMM_CSFB_SERVICE_RSLT_AUTH_REJ                        = 2,   /* ��Ȩ�ܾ�                 */
    MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT               = 3,   /* EXT T3417��ʱ            */
    MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL                 = 4,   /* MMC�·�DETACH���µ�ʧ��  */
    MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL                  = 5,   /* �����·�DETACH���µ�ʧ�� */
    MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS     = 6,   /* �����㷢��CSFB������     */
    MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_EMM_STATE  = 7,   /* EMM״̬���ܷ���CSFB      */
    MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_SMS_ONLY     = 8,   /* TAU���SER���ΪSMS ONLY */
    MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_PS_ONLY      = 9,   /* TAU���SER���ֻPS�ɹ�   */
    MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL     = 10,  /* TAU���SER��������쳣   */

    MM_LMM_CSFB_SERVICE_RSLT_BUTT
};
typedef VOS_UINT32 MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MM_PAGING_IND_UE_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PAGING IND��enPagingUeIdȡֵ
*****************************************************************************/
enum   LMM_MM_PAGING_IND_UE_ID_ENUM
{
    LMM_MM_PAGING_IND_UE_ID_IMSI                    = 0,
    LMM_MM_PAGING_IND_UE_ID_S_TMSI                  = 1,
    LMM_MM_PAGING_IND_UE_ID_TMSI                    = 2,

    LMM_MM_PAGING_IND_UE_ID_BUTT
};
typedef VOS_UINT32 LMM_MM_PAGING_IND_UE_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MM_NW_IMS_VOICE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����Ƿ�֧��IMS VOICEö��
*****************************************************************************/
enum LMM_MM_NW_IMS_VOICE_ENUM
{
    LMM_MM_NW_IMS_VOICE_NOT_SUPPORTED   = 0,
    LMM_MM_NW_IMS_VOICE_SUPPORTED        = 1,

    LMM_MM_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT32 LMM_MM_NW_IMS_VOICE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MM_NW_EMC_BS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����Ƿ�֧�ֽ�����ö��
*****************************************************************************/
enum LMM_MM_NW_EMC_BS_ENUM
{
    LMM_MM_NW_EMC_BS_NOT_SUPPORTED      = 0,
    LMM_MM_NW_EMC_BS_SUPPORTED           = 1,

    LMM_MM_NW_EMC_BS_BUTT
};
typedef VOS_UINT32 LMM_MM_NW_EMC_BS_ENUM_UINT32;

/*****************************************************************************
 ö����    : MM_LMM_SECU_INFO_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ȡL��CS��ȫ�����ĵĽ��ö��
*****************************************************************************/
enum  MM_LMM_SECU_INFO_RSLT_ENUM
{
    MM_LMM_SECU_INFO_RSLT_SUCC         = 0,
    MM_LMM_SECU_INFO_RSLT_FAIL_EIA0,
    MM_LMM_SECU_INFO_RSLT_FAIL_OTHERS,
    MM_LMM_SECU_INFO_RSLT_BUTT
};
typedef VOS_UINT32 MM_LMM_SECU_INFO_RSLT_ENUM_UINT32;


/*****************************************************************************
 ö����    : MM_LMM_SRVCC_STATUS_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ȡSRVCC��״̬
*****************************************************************************/
enum  MM_LMM_SRVCC_STATUS_ENUM
{
    MM_LMM_SRVCC_STATUS_START         = 0,
    MM_LMM_SRVCC_STATUS_SUCC,
    MM_LMM_SRVCC_STATUS_FAIL,

    MM_LMM_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32 MM_LMM_SRVCC_STATUS_ENUM_UINT32;


enum MM_LMM_SESSION_TYPE_ENUM
{

    MM_LMM_SESSION_TYPE_MO_NORMAL_CALL,
    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CALL,
    MM_LMM_SESSION_TYPE_MO_SS,
    MM_LMM_SESSION_TYPE_MO_SMS,
    MM_LMM_SESSION_TYPE_MT_NORMAL_CALL,
    MM_LMM_SESSION_TYPE_MT_SMS,
    MM_LMM_SESSION_TYPE_MT_SS,
    MM_LMM_SESSION_TYPE_MO_NORMAL_CSFB,
    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CSFB,
    MM_LMM_SESSION_TYPE_MT_CSFB,
    MM_LMM_SESSION_TYPE_LAU,
    MM_LMM_SESSION_TYPE_DETACH,
    MM_LMM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MM_LMM_SESSION_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
�ṹ��    :LMM_MM_COMBINED_START_NOTIFY_REQ_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MM_LMM_COMBINED_TYPE_ENUM_UINT32    enCombinedType;     /* ������������ */
} LMM_MM_COMBINED_START_NOTIFY_REQ_STRU;



/*****************************************************************************
 �ṹ��    : MM_LMM_CSFB_SERVICE_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MM֪ͨLMM����CSFB����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvType;
} MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MM֪ͨLMM��ֹCSFB����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MM_CSFB_SERVICE_END_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM֪ͨMM�� CSFB�����쳣��ֹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32  enCsfbSrvRslt;

    VOS_UINT32                            ulCnCause;        /* �����ΪCN REJʱ��Ч */
} LMM_MM_CSFB_SERVICE_END_IND_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MM_CSFB_SERVICE_PAGING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM֪ͨMM����MT CSFB����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSsCodeValue: 1;
    VOS_UINT32                          bitOpCli        : 1;
    VOS_UINT32                          bitSpare        : 30;

    VOS_UINT8                           ucSsCodeValue;
    VOS_UINT8                           ucCliLength;       /* 1~12*/
    VOS_UINT8                           aucRes[2];
    VOS_UINT8                           aucCliValue[12];

    LMM_MM_PAGING_IND_UE_ID_ENUM_UINT32    enPagingUeId;
} LMM_MM_CSFB_SERVICE_PAGING_IND_STRU;

/*****************************************************************************
�ṹ��    :LMM_MM_EMERGENCY_NUM_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :����������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;
    VOS_UINT8                           ucEmcNumLen;/*���������볤�ȣ���aucEmcNum����Ч����*/
    VOS_UINT8                           aucEmcNum[MM_LMM_EMERGENCY_NUM_MAX_LEN];
} LMM_MM_EMERGENCY_NUM_STRU;

/*****************************************************************************
�ṹ��    :LMM_MM_INFO_CHANGE_NOTIFY_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :LMM_MM_INFO_CHANGE_NOTIFY��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpEmcNumList : 1;
    VOS_UINT32                          bitOpImsVoPS    : 1;
    VOS_UINT32                          bitOpEmcBS      : 1;
    VOS_UINT32                          bitSpare        : 29;

    VOS_UINT8                           ucEmergencyNumAmount;
    VOS_UINT8                           aucReserved[3];
    LMM_MM_EMERGENCY_NUM_STRU           astEmergencyNumList[MM_LMM_EMERGENCY_NUM_LIST_MAX_RECORDS];

    LMM_MM_NW_IMS_VOICE_ENUM_UINT32     enNwImsVoPS;
    LMM_MM_NW_EMC_BS_ENUM_UINT32        enNwEmcBS;
} LMM_MM_INFO_CHANGE_NOTIFY_STRU;


/*****************************************************************************
�ṹ��    :MM_LMM_HO_SECU_INFO_REQ_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :MM_LMM_HO_SECU_INFO_REQ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];  /*Ԥ��*/
}MM_LMM_HO_SECU_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ����: MM_LMM_SRVCC_STATUS_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MM_LMM_SRVCC_STATUS_ENUM_UINT32     enSrvccStatus;
} MM_LMM_SRVCC_STATUS_NOTIFY_STRU;


/*****************************************************************************
�ṹ��    :MM_LMM_GU_SECU_CONTEXT_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :LMMӳ�䵽GU�İ�ȫ�����Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulKSI;
    VOS_UINT8                           aucCk[MM_LMM_CK_LEN];
    VOS_UINT8                           aucIk[MM_LMM_IK_LEN];
}MM_LMM_GU_SECU_CONTEXT_STRU;


/*****************************************************************************
�ṹ��    :LMM_MM_HO_SECU_INFO_CNF_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :ID_LMM_MM_HO_SECU_INFO_CNF��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSecuCntxt  : 1;
    VOS_UINT32                          bitSpare        : 31;

    MM_LMM_SECU_INFO_RSLT_ENUM_UINT32   enRslt;
    MM_LMM_GU_SECU_CONTEXT_STRU         stHoSecuCntxt;
}LMM_MM_HO_SECU_INFO_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    MM_LMM_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MM_LMM_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ */   /*_H2ASN_Skip*/
    MM_LMM_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MM_LMM_END_SESSION_NOTIFY_STRU;


typedef struct
{
    MM_LMM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_MsgChoice_Export MM_LMM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MM_LMM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MM_LMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    MM_LMM_INTERFACE_MSG_DATA            stMsgData;
} MmLmmInterface_MSG;





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

#endif /* end of MmLmmInterface.h */




