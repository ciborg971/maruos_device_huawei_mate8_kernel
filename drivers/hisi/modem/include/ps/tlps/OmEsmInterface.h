

#ifndef __OMESMINTERFACE_H__
#define __OMESMINTERFACE_H__

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
/*OM->ESM Command��Ϣǰ3���ֽں궨�� OM->ESM*/
#define OM_ESM_MSG_ID_HEADER                               PS_MSG_ID_OM_TO_ESM_BASE

/*ESM->OM Command��Ϣǰ3���ֽں궨�� ESM->OM*/
#define ESM_OM_MSG_ID_HEADER                               PS_MSG_ID_ESM_TO_OM_BASE


#define OM_ESM_REPORT_INFO_OPEN                       1
#define OM_ESM_REPORT_INFO_CLOSE                      0

#define OM_MAX_IPV4_ADDR_LEN                               4
#define OM_MAX_IPV6_ADDR_LEN                               16

#define OM_MAX_APN_LEN                                     99

#define OM_ESM_MAX_EPSB_NUM                                (11)                /*��������*/




/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : OM_ESM_MSG_TYPE_ENUM
 ö��˵��  : OM��SM��Ϣȡֵ
*****************************************************************************/
enum OM_ESM_MSG_TYPE_ENUM
{
    ID_OM_ESM_INFO_REPORT_REQ              = 0x01+OM_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_ESM_INFO_REPORT_REQ_STRU*/
    ID_OM_ESM_INFO_REPORT_CNF              = 0x01+ESM_OM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_ESM_INFO_REPORT_CNF_STRU*/


    ID_OM_ESM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 OM_ESM_MSG_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö����    : OM_ESM_INFO_REPORT_ENUM
 ö��˵��  : ESM�ϱ�Э��״̬�Ŀ���״̬
*****************************************************************************/
enum OM_ESM_INFO_REPORT_ENUM
{
    OM_ESM_INFO_REPORT_CLOSE,        /* ����Ҫ�ϱ� */
    OM_ESM_INFO_REPORT_OPEN,         /* ��Ҫ�ϱ� */
    OM_ESM_INFO_REPORT_BUTT
};
typedef VOS_UINT32 OM_ESM_INFO_REPORT_UINT32;

/*****************************************************************************
 ö����    : OM_ESM_BEARER_STATE_ENUM
 ö��˵��  : ����״̬ȡֵ
*****************************************************************************/
enum ESM_BEARER_CONTEXT_STATE_ENUM
{
    BEARER_CONTEXT_INACTIVE       = 0x00,
    BEARER_CONTEXT_ACTIVE      = 0x01,
    BEARER_CONTEXT_BUTT
};
typedef VOS_UINT32 ESM_BEARER_CONTEXT_STATE_ENUM_UINT32;


/*****************************************************************************
 ö����    : OM_ESM_BEARER_TYPE_ENUM
 ö��˵��  : ��������ȡֵ
*****************************************************************************/
enum ESM_BEARER_TYPE_ENUM
{
    BEARER_TYPE_DEFAULT         = 0x00,
    BEARER_TYPE_DEDICATED       = 0x01,
    BEARER_TYPE_EMERGENCY       = 0x02,
    BEARER_TYPE_BUTT
};
typedef VOS_UINT32 ESM_BEARER_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : OM_ESM_APN_INFO_STRU
 �ṹ˵��  : APN  ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApnName[OM_MAX_APN_LEN];
}OM_ESM_APN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ESM_EPS_QOS_INFO_STRU
 �ṹ˵��  : EPS_QOS  ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQCI;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulULMaxRate;    /* ��λΪkbps */
    VOS_UINT32                          ulDLMaxRate;    /* ��λΪkbps */
    VOS_UINT32                          ulULGMaxRate;   /* ��λΪkbps */
    VOS_UINT32                          ulDLGMaxRate;   /* ��λΪkbps */
}OM_ESM_EPS_QOS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ESM_CONTEXT_APN_AMBR_STRU
 �ṹ˵��  : APN AMBR ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulDLApnAmbr;
    VOS_UINT32                           ulULApnAmbr;

}OM_ESM_CONTEXT_APN_AMBR_STRU;

/*****************************************************************************
 �ṹ��    : OM_ESM_IP_ADDR_STRU
 �ṹ˵��  : IP��ַ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[OM_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[OM_MAX_IPV6_ADDR_LEN];
}OM_ESM_IP_ADDR_STRU;


/*****************************************************************************
 �ṹ��    : OM_ESM_STATE_INFO_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCid;
    ESM_BEARER_CONTEXT_STATE_ENUM_UINT32     enBearerCntxtState;
    ESM_BEARER_TYPE_ENUM_UINT32         enBearerCntxtType;
    VOS_UINT32                          ulLinkBearId;
    OM_ESM_APN_INFO_STRU                stApn;
    OM_ESM_CONTEXT_APN_AMBR_STRU        stApnAmbrInfo;
    OM_ESM_EPS_QOS_INFO_STRU            stSdfQosInfo;
    OM_ESM_IP_ADDR_STRU                 stIpAddr;
} OM_ESM_STATE_INFO_STRU;

/* ����HSO SG������ʾ */
typedef struct
{
    OM_ESM_STATE_INFO_STRU              stEsmInfo[OM_ESM_MAX_EPSB_NUM];//��������
} DIAG_ESM_INFO_IND_STRU;



/* ����HSO SG������ʾ */

/*****************************************************************************
 �ṹ��    :  OM_ESM_INFO_REPORT_REQ_STRU
 �ṹ˵��  : ID_ OM_ESM_INFO_REPORT_REQ ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    VOS_UINT32                          ulOpId;
    OM_ESM_INFO_REPORT_UINT32          enRptCtrl;
} OM_ESM_INFO_REPORT_REQ_STRU;
/*****************************************************************************
 �ṹ��    :  APP_ESM_INFO_REPORT_CNF_STRU
 �ṹ˵��  : ID_ APP_ESM_INFO_REPORT_CNF ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} OM_ESM_INFO_REPORT_CNF_STRU;



typedef struct
{
    OM_ESM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export OM_ESM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}OM_ESM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    OM_ESM_INTERFACE_MSG_DATA           stMsgData;
} OMEsmInterface_MSG;






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

