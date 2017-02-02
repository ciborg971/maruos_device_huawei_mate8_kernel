

#ifndef __OMEMMINTERFACE_H__
#define __OMEMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/*OM->EMM Command��Ϣǰ3���ֽں궨�� OM->EMM*/
#define OM_EMM_MSG_ID_HEADER                               PS_MSG_ID_OM_TO_EMM_BASE

/*EMM->OM Command��Ϣǰ3���ֽں궨�� EMM->OM*/
#define EMM_OM_MSG_ID_HEADER                               PS_MSG_ID_EMM_TO_OM_BASE

#define OM_EMM_REPORT_INFO_OPEN                       1
#define OM_EMM_REPORT_INFO_CLOSE                      0

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : OM_EMM_MSG_TYPE_ENUM
 ö��˵��  : OM��EMM��Ϣȡֵ
*****************************************************************************/
enum OM_EMM_MSG_TYPE_ENUM
{
    ID_OM_EMM_INFO_REPORT_REQ              = 0x01+OM_EMM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_EMM_INFO_REPORT_REQ_STRU*/
    ID_OM_EMM_INFO_REPORT_CNF              = 0x01+EMM_OM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_EMM_INFO_REPORT_CNF_STRU*/


    ID_OM_EMM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 OM_EMM_MSG_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö����    : OM_EMM_INFO_REPORT_ENUM
 ö��˵��  : EMM�ϱ�Э��״̬�Ŀ���״̬
*****************************************************************************/
enum OM_EMM_INFO_REPORT_ENUM
{
    OM_EMM_INFO_REPORT_CLOSE,        /* ����Ҫ�ϱ� */
    OM_EMM_INFO_REPORT_OPEN,         /* ��Ҫ�ϱ� */
    OM_EMM_INFO_REPORT_BUTT
};
typedef VOS_UINT32 OM_EMM_INFO_REPORT_UINT32;

enum NAS_EMM_SECU_ALG_ENUM
{
    EEA0               = 0x000,
    EEA1               = 0x001,
    EEA2               = 0x002,
    EEA3               = 0x003,
    NAS_EMM_SECU_ALG_BUTT
};
typedef VOS_UINT16 NAS_EMM_SECU_ALG_ENUM_UINT16;


enum NAS_EMM_INTEGRITY_ALG_ENUM
{
    EIA0               = 0x000,
    EIA1               = 0x001,
    EIA2               = 0x002,
    EIA3               = 0x003,
    NAS_EMM_INTEGRITY_ALG_BUTT
};
typedef VOS_UINT16 NAS_EMM_INTEGRITY_ALG_ENUM_UINT16;


enum NAS_UE_OPERATION_MODE_ENUM
{
   PS_MODE_1                 = 1,    /* PS MODE 1 */
   PS_MODE_2                 = 2,    /* PS MODE 2 */
   CS_PS_MODE_1              = 3,    /* CS/PS MODE 1 */
   CS_PS_MODE_2              = 4,    /* CS/PS MODE 2 */
   NAS_UE_MODE_BUTT
};
typedef VOS_UINT32   NAS_UE_OPERATION_MODE_ENUM_UINT32;
/*****************************************************************************
 ö����    : OM_EMM_MAIN_STATE_ENUM
 ö��˵��  : EMM��״̬
*****************************************************************************/
enum   EMM_MAIN_STATE_ENUM
{
    /*=================== EMM����״̬ ===================*/
    EMM_NULL                                = 0x0000,   /* ��״̬           */
    EMM_DEREGISTERED                        = 0x0001,   /* DETACH״̬       */
    EMM_REGISTERED_INITIATED                = 0x0002,   /* ATTACH������״̬ */
    EMM_REGISTERED                          = 0x0003,   /* ATTACH״̬       */
    EMM_DEREGISTERED_INITIATED              = 0x0004,   /* DETACH������״̬ */
    EMM_TRACKING_AREA_UPDATING_INITIATED    = 0x0005,   /* TAU������״̬    */
    EMM_SERVICE_REQUEST_INITIATED           = 0x0006,   /* SERVICE������״̬*/
    EMM_STATE_BUTT
};
typedef VOS_UINT16 EMM_MAIN_STATE_ENUM_UINT16;



/*****************************************************************************
 ö����    : OM_EMM_SUB_STATE_ENUM
 ö��˵��  : EMM��״̬
*****************************************************************************/
enum    EMM_SUB_STATE_ENUM
{

    /*=================== EMM����״̬ ===================*/
    EMM_SS_NULL                             = 0x0000,  /* ����״̬ */
    /*========== OM_EMM_MS_DEREG�µ���״̬ ==============*/
    EMM_DEREGISTERED_NORMAL_SERVICE         = 0x0001,  /* δע����������״̬ */
    EMM_DEREGISTERED_LIMITED_SERVICE        = 0x0002,  /* δע�����Ʒ���״̬ */
    EMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   = 0x0003,  /* δע��ȴ�����ATTCH״̬*/
    EMM_DEREGISTERED_PLMN_SEARCH            = 0x0004,  /* δע������״̬ */
    EMM_DEREGISTERED_NO_IMSI                = 0x0005,  /* δע�Ῠ��Ч״̬ */
    EMM_DEREGISTERED_ATTACH_NEEDED          = 0x0006,  /* δע����Ҫ����ATTACH״̬ */
    EMM_DEREGISTERED_NO_CELL_AVAILABLE      = 0x0007,  /* δע��û�п���С��״̬ */

    /*========== OM_EMM_MS_REG�µ���״̬ ================*/
    EMM_REGISTERED_NORMAL_SERVICE           = 0x0011,  /* ע����������״̬ */
    EMM_REGISTERED_ATTEMPTING_TO_UPDATE     = 0x0012,  /* ע��ȴ�����TA����״̬ */
    EMM_REGISTERED_LIMITED_SERVICE          = 0x0013,  /* ע�����Ʒ���״̬ */
    EMM_REGISTERED_PLMN_SEARCH              = 0x0014,  /* ע������״̬ */
    EMM_REGISTERED_UPDATE_NEEDED            = 0x0015,  /* ע����ҪTA����״̬ */
    EMM_REGISTERED_NO_CELL_AVAILABLE        = 0x0016,  /* ע��û�п���С��״̬ */
    EMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  = 0x0017,  /* ����ע��ֻע��ɹ�EPS�����״̬ */
    EMM_REGISTERED_IMSI_DETACH_INITIATED    = 0x0018,  /* IMSI DETACH�ȴ�����ظ�״̬ */
    EMM_SS_BUTT
};
typedef VOS_UINT16  EMM_SUB_STATE_ENUM_UINT16;
/*****************************************************************************
 ö����    : OM_EMM_UPDATE_STAT_ENUM
 ö��˵��  : EMM UPDATE״̬
*****************************************************************************/
enum    EMM_UPDATE_STATE_ENUM
{
    EU1_UPDATED                  = 0x00,   /* ����״̬       */
    EU2_NOT_UPDATED              = 0x01,   /* δ����״̬     */
    EU3_ROAMING_NOT_ALLOWED      = 0x02,   /* ���β�����״̬ */

    EU_BUTT
};
typedef VOS_UINT32  EMM_UPDATE_STATE_ENUM_UINT32;


typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
} OM_PLMN_ID_STRU;

/*****************************************************************************
�ṹ����    :OM_GUTI_HEAD_STRU
ʹ��˵��    :OM_GUTI_HEAD_STRU����ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}OM_GUTI_HEAD_STRU;

/*****************************************************************************
�ṹ����    :OM_MME_GROUPID_STRU
ʹ��˵��    :OM_MME_GROUPID_STRU����ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}OM_MME_GROUPID_STRU;

/*****************************************************************************
�ṹ����    :OM_MME_CODE_STRU
ʹ��˵��    :OM_MME_CODE_STRU����ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}OM_MME_CODE_STRU;

/*****************************************************************************
�ṹ����    :OM_MTMSI_STRU
ʹ��˵��    :OM_MTMSI_STRU����ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}OM_MTMSI_STRU;


/*****************************************************************************
�ṹ����    :OM_GUTI_STRU
ʹ��˵��    :OM_GUTI_STRU����ز���
*****************************************************************************/
typedef struct
{
    OM_GUTI_HEAD_STRU                  stGutiHead;
    OM_PLMN_ID_STRU                    stPlmn;
    OM_MME_GROUPID_STRU                stMmeGroupId;
    OM_MME_CODE_STRU                   stMmeCode;
    OM_MTMSI_STRU                      stMTmsi;
}OM_GUTI_STRU;


typedef struct
{
    EMM_MAIN_STATE_ENUM_UINT16          enMainState;        /*MM��״̬*/
    EMM_SUB_STATE_ENUM_UINT16           enSubState;         /*MM��״̬*/
    EMM_UPDATE_STATE_ENUM_UINT32        enEmmUpState;       /*EMM update״̬*/
    OM_GUTI_STRU                        stGuti;         /*GUTI */
    NAS_EMM_SECU_ALG_ENUM_UINT16         enAlgSecurity;
    NAS_EMM_INTEGRITY_ALG_ENUM_UINT16    enAlgIntegrity;
    NAS_UE_OPERATION_MODE_ENUM_UINT32       enLteUeMode;
} OM_EMM_STATE_INFO_STRU;



/*****************************************************************************
 �ṹ��    :  OM_EMM_INFO_REPORT_REQ_STRU
 �ṹ˵��  : ID_OM_EMM_INFO_REPORT_REQ ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    VOS_UINT32                          ulOpId;
    OM_EMM_INFO_REPORT_UINT32          enRptCtrl;
} OM_EMM_INFO_REPORT_REQ_STRU;
/*****************************************************************************
 �ṹ��    :  OM_EMM_INFO_REPORT_CNF_STRU
 �ṹ˵��  : ID_ OM_EMM_INFO_REPORT_CNF ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} OM_EMM_INFO_REPORT_CNF_STRU;



typedef struct
{
    OM_EMM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export OM_EMM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}OM_EMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    OM_EMM_INTERFACE_MSG_DATA           stMsgData;
} OMEmmInterface_MSG;






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

#endif /* end of AppEsmInterface.h */


