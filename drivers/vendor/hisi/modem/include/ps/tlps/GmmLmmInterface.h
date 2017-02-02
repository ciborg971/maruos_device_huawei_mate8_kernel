
#ifndef __GMMLMMINTERFACE_H__
#define __GMMLMMINTERFACE_H__

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
#define LMM_GMM_NAS_TOKEN_LEN           32   /*���Ȳ�ȷ�ϣ���Э����û���ҵ�����*/
#define LMM_GMM_CK_LEN                  16
#define LMM_GMM_IK_LEN                  16

/* lihong00150010 ims begin */
#define LMM_GMM_EMERGENCY_NUM_MAX_LEN            (46)
#define LMM_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS   (16)
/* lihong00150010 ims end */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    GMM_LMM_MSG_ID_ENUM
{
    /* GMM����LMM����Ϣԭ�� */
    ID_GMM_LMM_RESEL_SECU_INFO_REQ      = 0x01+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_RESEL_SECU_INFO_REQ */
    ID_GMM_LMM_HO_SECU_INFO_REQ         = 0x02+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_HO_SECU_INFO_REQ  */
    ID_GMM_LMM_INFO_CHANGE_NOTIFY_REQ   = 0x03+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_INFO_CHANGE_NOTIFY_REQ */
    ID_GMM_LMM_TIMER_STATE_NOTIFY        = 0x04+PS_MSG_ID_GMM_TO_LMM_BASE,      /* _H2ASN_MsgChoice GMM_LMM_TIMER_STATE_NOTIFY_STRU */

    ID_GMM_LMM_BEGIN_SESSION_NOTIFY    = 0x05+PS_MSG_ID_GMM_TO_LMM_BASE,        /* _H2ASN_MsgChoice GMM_LMM_BEGIN_SESSION_NOTIFY_STRU */
    ID_GMM_LMM_END_SESSION_NOTIFY      = 0x06+PS_MSG_ID_GMM_TO_LMM_BASE,        /* _H2ASN_MsgChoice GMM_LMM_END_SESSION_NOTIFY_STRU */

    /* LMM���͸�GMM����Ϣԭ��*/
    ID_LMM_GMM_RESEL_SECU_INFO_CNF      = 0x01+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_RESEL_SECU_INFO_CNF */
    ID_LMM_GMM_HO_SECU_INFO_CNF         = 0x02+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_HO_SECU_INFO_CNF */
    /* lihong00150010 ims begin */
    ID_LMM_GMM_INFO_CHANGE_NOTIFY       = 0x03+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_INFO_CHANGE_NOTIFY_STRU */
    /* lihong00150010 ims end */

    ID_GMM_LMM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 GMM_LMM_MSG_ID_ENUM_UINT32;



/*****************************************************************************
 ö����: GMM_LMM_RESULT_ID_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum    GMM_LMM_RESULT_ID_ENUM
{
    GMM_LMM_SUCC                        = 0x00000000,
    GMM_LMM_FAIL                        ,
    GMM_LMM_ERR_ID_BUTT
};
typedef VOS_UINT32 GMM_LMM_RESULT_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_GMM_SECU_INFO_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum    LMM_GMM_SECU_INFO_RSLT_ENUM
{
    LMM_GMM_SECU_INFO_RSLT_SUCC         = 0,
    LMM_GMM_SECU_INFO_RSLT_FAIL,

    LMM_GMM_SECU_INFO_RSLT_BUTT
};
typedef VOS_UINT32 LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32;


enum    GMM_LMM_GPRS_MM_STATE_ENUM
{
    GMM_LMM_GPRS_MM_STATE_IDLE           = 0,           /* G��GMMΪidle̬ */
    GMM_LMM_GPRS_MM_STATE_STANDBY        = 1,           /* G��GMMΪstandby̬ */
    GMM_LMM_GPRS_MM_STATE_READY          = 2,           /* G��GMMΪready̬ */

    GMM_LMM_GPRS_MM_STATE_BUTT
};
typedef VOS_UINT32 GMM_LMM_GPRS_MM_STATE_ENUM_UINT32;
enum    GMM_LMM_PACKET_MM_STATE_ENUM
{
    GMM_LMM_PACKET_MM_STATE_PMM_DETACH     = 0,           /* W��GMMΪdetach̬ */
    GMM_LMM_PACKET_MM_STATE_PMM_IDLE       = 1,           /* W��GMMΪidle̬ */
    GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED  = 2,           /* W��GMMΪconnect̬ */

    GMM_LMM_PACKET_MM_STATE_BUTT
};
typedef VOS_UINT32 GMM_LMM_PACKET_MM_STATE_ENUM_UINT32;
enum    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM
{
    GMM_LMM_GPRS_NOT_SUSPENSION             = 0,           /* G��GMMΪ�ǹ���̬ */
    GMM_LMM_GPRS_SUSPENSION                 = 1,           /* G��GMMΪ����̬ */

    GMM_LMM_GPRS_SUSPENSION_BUTT
};
typedef VOS_UINT32 GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32;
/*****************************************************************************
 ö����    : GMM_LMM_TIMER_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :��ʱ�����������
*****************************************************************************/
enum    GMM_LMM_TIMER_STATE_ENUM
{
    GMM_LMM_TIMER_STOP         = 0,
    GMM_LMM_TIMER_START,
    GMM_LMM_TIMER_EXP,

    GMM_LMM_TIMER_BUTT
};
typedef VOS_UINT32 GMM_LMM_TIMER_STATE_ENUM_UINT32;


/* lihong00150010 ims begin */
/*****************************************************************************
 ö����    : LMM_GMM_NW_IMS_VOICE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����֧�ֵ�IMS VOICEö��
*****************************************************************************/
enum LMM_GMM_NW_IMS_VOICE_ENUM
{
    LMM_GMM_NW_IMS_VOICE_NOT_SUPPORTED   = 0,
    LMM_GMM_NW_IMS_VOICE_SUPPORTED        = 1,

    LMM_GMM_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT32 LMM_GMM_NW_IMS_VOICE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_GMM_NW_EMC_BS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����֧�ֵ�EMC BEARER SERVICEEö��
*****************************************************************************/
enum LMM_GMM_NW_EMC_BS_ENUM
{
    LMM_GMM_NW_EMC_BS_NOT_SUPPORTED      = 0,
    LMM_GMM_NW_EMC_BS_SUPPORTED           = 1,

    LMM_GMM_NW_EMC_BS_BUTT
};
typedef VOS_UINT32 LMM_GMM_NW_EMC_BS_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_GMM_LTE_CS_CAPBILITY_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE��CS������
*****************************************************************************/
enum LMM_GMM_LTE_CS_CAPBILITY_ENUM
{
    LMM_GMM_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    LMM_GMM_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    LMM_GMM_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    LMM_GMM_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT32 LMM_GMM_LTE_CS_CAPBILITY_ENUM_UINT32;
/* lihong00150010 ims end */


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
�ṹ��    :GMM_LMM_RESEL_SECU_INFO_REQ_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];  /*Ԥ��*/
}GMM_LMM_RESEL_SECU_INFO_REQ_STRU;

/*****************************************************************************
�ṹ��    :LMM_GMM_UMTS_SECU_CONTEXT_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          KSI;
    VOS_UINT8                           aucUmtsCk[LMM_GMM_CK_LEN];
    VOS_UINT8                           aucUmtsIk[LMM_GMM_IK_LEN];
}LMM_GMM_UMTS_SECU_CONTEXT_STRU;

/*****************************************************************************
�ṹ��    :LMM_GMM_RESEL_SECU_INFO_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LMM_GMM_UMTS_SECU_CONTEXT_STRU      stUmtsSecuContext;
    VOS_UINT8                           aucNasToken[LMM_GMM_NAS_TOKEN_LEN];

}LMM_GMM_RESEL_SECU_INFO_STRU;

/*****************************************************************************
�ṹ��    :GMM_LMM_RESEL_SECU_INFO_REQ_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSecuInfo   : 1;
    VOS_UINT32                          bitSpare        : 31;

    LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32  enRslt;
    LMM_GMM_RESEL_SECU_INFO_STRU        stReselSecuInfo;
}LMM_GMM_RESEL_SECU_INFO_CNF_STRU;

/*****************************************************************************
�ṹ��    :GMM_LMM_HO_SECU_INFO_REQ_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];  /*Ԥ��*/
}GMM_LMM_HO_SECU_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��    : GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
        ��Gģ��Lģ����ϵͳ�任����Gģ����ʱ����Ҫ��Lģ���ʹ���Ϣ������bitOpGConnStateΪ1����֪Gģ������״̬��
        ��Uģ��Lģ����ϵͳ�任����Uģ����ʱ����Ҫ��Lģ���ʹ���Ϣ������bitOpUConnStateΪ1����֪Uģ������״̬��
        ��Gģ��Lģ����ϵͳ�任����Gģ����ʱ����Ҫ��Lģ���ʹ���Ϣ��֪ͨLMM PS���״̬��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                                              bitOpGprsMmState         : 1;
    VOS_UINT32                                              bitOpPacketMmState       : 1;
    VOS_UINT32                                              bitOpGprsSuspensionState : 1;
    VOS_UINT32                                              bitSpare                 : 29;

    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32                       enGprsMmState;         /* G��GMM����״̬ */
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32                     enPacketMmState;       /* W��GMM����״̬ */
    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32               enGprsSuspensionState; /* GMM�Ƿ�Ϊ������״̬ */
} GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU;

/* lihong00150010 ims begin */
/*****************************************************************************
 �ṹ��    : LMM_GMM_EMERGENCY_NUM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCategory;
    VOS_UINT8                           ucEmcNumLen;    /*���������볤�ȣ���aucEmcNum����Ч����*/
    VOS_UINT8                           aucEmcNum[LMM_GMM_EMERGENCY_NUM_MAX_LEN];
} LMM_GMM_EMERGENCY_NUM_STRU;

/*****************************************************************************
 �ṹ��    : LMM_GMM_INFO_CHANGE_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    VOS_UINT32                              bitOpEmcNumList : 1;
    VOS_UINT32                              bitOpImsVoPS    : 1;
    VOS_UINT32                              bitOpEmcBS      : 1;
    VOS_UINT32                              bitOpLteCsCap   : 1;
    VOS_UINT32                              bitSpare        : 28;

    VOS_UINT8                               ucEmergencyNumAmount;
    VOS_UINT8                               aucReserved[3];
    LMM_GMM_EMERGENCY_NUM_STRU              astEmergencyNumList[LMM_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS];

    LMM_GMM_NW_IMS_VOICE_ENUM_UINT32        enNwImsVoPS;
    LMM_GMM_NW_EMC_BS_ENUM_UINT32           enNwEmcBS;
    LMM_GMM_LTE_CS_CAPBILITY_ENUM_UINT32    enLteCsCap ;
} LMM_GMM_INFO_CHANGE_NOTIFY_STRU;
/* lihong00150010 ims end */


/*****************************************************************************
�ṹ��    :LMM_GMM_HO_SECU_INFO_CNF_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSecuCntxt  : 1;
    VOS_UINT32                          bitSpare        : 31;

    LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32  enRslt;
    LMM_GMM_UMTS_SECU_CONTEXT_STRU      stHoUmtsSecuCntxt;
}LMM_GMM_HO_SECU_INFO_CNF_STRU;


enum GMM_LMM_SESSION_TYPE_ENUM
{
    GMM_LMM_SESSION_TYPE_MO_SMS,
    GMM_LMM_SESSION_TYPE_MT_SMS,
    GMM_LMM_SESSION_TYPE_PS_ATTACH,
    GMM_LMM_SESSION_TYPE_PS_RAU,
    GMM_LMM_SESSION_TYPE_PS_DETACH,
    GMM_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,
    GMM_LMM_SESSION_TYPE_PS_STREAM_CALL,
    GMM_LMM_SESSION_TYPE_PS_INTERACT_CALL,
    GMM_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,
    GMM_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    GMM_LMM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMM_LMM_SESSION_TYPE_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}GMM_LMM_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}GMM_LMM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
�ṹ��    :LMM_GMM_TIMER_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :��ʱ�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          bitOpT3312  :1;
    VOS_UINT32                          bitOpRsv    :31;

    GMM_LMM_TIMER_STATE_ENUM_UINT32      enT3312State;
}GMM_LMM_TIMER_STATE_NOTIFY_STRU;




typedef struct
{
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_MsgChoice_Export GMM_LMM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_LMM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}GMM_LMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    GMM_LMM_INTERFACE_MSG_DATA           stMsgData;
} GmmLmmInterface_MSG;







/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern    GMM_LMM_RESULT_ID_ENUM_UINT32  STUB_NAS_LMM_CompLmmHoSecuInfoCnf(
                    LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf );

/* lihong00150010 rrc connection failure begin */
/*****************************************************************************
 ��������: Nas_GetLrrcConnFailureFlag
 Э����:
 ASN.1 ����:
 ����˵��: ��ȡrrc connection failure��ʶ��LNAS�ṩ��GU NAS����
           VOS_TRUE��ʾ��ʶ��Ч����ϵͳ��GU��Ҫ����RAU
           VOS_FALSE��ʾ��ʶ��Ч
*****************************************************************************/
extern VOS_UINT32  Nas_GetLrrcConnFailureFlag( VOS_VOID );

/* lihong00150010 rrc connection failure end */


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

#endif /* end of GmmLmmInterface.h */

















