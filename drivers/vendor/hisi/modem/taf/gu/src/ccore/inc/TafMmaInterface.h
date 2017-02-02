

#ifndef __TAF_MMA_INTERFACE_H__
#define __TAF_MMA_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "NasStkInterface.h"

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
/*****************************************************************************
 ö����    : TAF_MMA_PID_MSG_TYPE_ENUM
 �ṹ˵��  : TAF PID��MMA PID֮�����Ϣ�ӿ�ö��
*****************************************************************************/
enum TAF_MMA_PID_MSG_TYPE_ENUM
{
    MMCM_OM_MAINTAIN_INFO_IND                               = 0x00000000,       /* _H2ASN_MsgChoice MMCM_OM_MAINTAIN_INFO_IND_STRU */

    MN_USIM_STATUS_IND                                      = 0x00000001,       /* _H2ASN_MsgChoice MNPH_USIM_STATUS_IND_STRU */
    MMA_TAF_POWER_OFF_IND                                   = 0x00000002,       /* _H2ASN_MsgChoice TAF_MMA_POWER_OFF_IND_STRU */
    ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY                     = 0x00000003,       /* _H2ASN_MsgChoice MMA_MSG_CS_SERVICE_IND */
    ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY                 = 0x00000004,       /* _H2ASN_MsgChoice MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY             = 0x00000005,       /* _H2ASN_MsgChoice MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_RAT_CHANGE_NOTIFY                            = 0x00000006,       /* _H2ASN_MsgChoice MMA_TAF_RAT_CHANGE_NOTIFY_STRU */

    ID_MMA_TAF_IMS_VOICE_CAP_IND                            = 0x00000007,       /* _H2ASN_MsgChoice MMA_TAF_IMS_VOICE_CAP_IND_STRU */

    /* �ƶ���tafappmma.h �� */


    ID_MMA_TAF_1X_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_TAF_1X_SERVICE_STATUS_IND_STRU */

    ID_MMA_TAF_POWER_ON_IND,                                                    /* _H2ASN_MsgChoice TAF_MMA_POWER_ON_IND_STRU */
    ID_MMA_APS_EPDSZID_INFO_IND,                                                /* _H2ASN_MsgChoice MMA_APS_EPDSZID_INFO_IND_STRU */



    ID_MMA_APS_CL_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_APS_CL_SERVICE_STATUS_IND_STRU */

    ID_TAF_MMA_PID_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_PID_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MNPH_USIM_STATUS_ENUM
 �ṹ˵��  : MNPH_USIM_STATUS_ENUM��Ϣ�е� enUsimStatus
*****************************************************************************/
enum MNPH_USIM_STATUS_ENUM
{
    MNPH_USIM_STATUS_AVILABLE         = 0, /* ����Ч */
    MNPH_USIM_STATUS_NOT_AVAILABLE    = 1, /* ����Ч */
    MNPH_USIM_STATUS_BUTT
};
typedef VOS_UINT32 MNPH_USIM_STATUS_ENUM_U32;


/* ת�Ƶ�tafappmma.h �� */

enum MMA_TAF_RAT_TYPE_ENUM
{
    MMA_TAF_RAT_TYPE_NULL,          /* ��ǰδ���κ�������פ�� */
    MMA_TAF_RAT_TYPE_GSM,           /* GSM���뼼�� */
    MMA_TAF_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    MMA_TAF_RAT_TYPE_LTE,           /* LTE���뼼�� */
    MMA_TAF_RAT_TYPE_1X,            /* CDMA-1X���뼼�� */
    MMA_TAF_RAT_TYPE_HRPD,          /* CDMA-HRPD���뼼�� */
    MMA_TAF_RAT_TYPE_EHRPD,         /* CDMA-EHRPD���뼼�� */
    MMA_TAF_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 MMA_TAF_RAT_TYPE_ENUM_UINT32;


enum MMA_APS_SYS_ACQUIRE_ENUM
{
    MMA_APS_SYS_ACQUIRE_NULL,          /* ��ǰδ���κ�������פ�� */
    MMA_APS_SYS_ACQUIRE_LTE,           /* LTE���뼼�� */
    MMA_APS_SYS_ACQUIRE_1X,            /* CDMA-1X���뼼�� */
    MMA_APS_SYS_ACQUIRE_EVDO,          /* CDMA-EVDO���뼼�� */
    MMA_APS_SYS_ACQUIRE_1X_EVDO,       /* CDMA-1X&EVDO���뼼�� */
    MMA_APS_SYS_ACQUIRE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 MMA_APS_SYS_ACQUIRE_ENUM_UINT32;



enum MMA_TAF_CL_STATUS_ENUM
{
    MMA_TAF_CL_STATUS_DO_NO_SERVICE,                  /* DO���з����Ϊ�޷��� */
    MMA_TAF_CL_STATUS_LTE_NO_SERVICE,                 /* LTE���з����Ϊ�޷��� */
    MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE,              /* ��ǰDO��LTE����������δ���κ�������פ�� */
    MMA_TAF_CL_STATUS_LTE_NORMAL_SERVICE,             /* LTE�������� */
    MMA_TAF_CL_STATUS_HRPD_NORMAL_SERVICE,            /* HRPD�������� */
    MMA_TAF_CL_STATUS_EHRPD_NORMAL_SERVICE,           /* EHRPD�������� */
    MMA_TAF_CL_STATUS_BUTT                            /* ��Ч��ֵ */
};
typedef VOS_UINT32 MMA_TAF_CL_STATUS_ENUM_UINT32;

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
typedef struct
{
    VOS_MSG_HEADER
    unsigned long                       ulMsgName;

    VOS_UINT8                           ucOmConnectFlg;                         /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM���õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */

    VOS_UINT8                           aucRsv2[2];                             /* ����   */
}MMCM_OM_MAINTAIN_INFO_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus;
}MNPH_USIM_STATUS_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           aucReserve[4];
}TAF_MMA_POWER_OFF_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CS_SERVICE_ENUM_UINT32          enCSState;
}MMA_MSG_CS_SERVICE_IND;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}MMA_TAF_RAT_CHANGE_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucImsVoiceAvail;                        /* IMS VOICE�Ƿ����:VOS_TRUE:IMS voice����; VOS_FALSE: IMS VOICE������ */
    VOS_UINT8                           aucReserve[3];                         /* ���� */
}MMA_TAF_IMS_VOICE_CAP_IND_STRU;


/* �ƶ���tafappmma.h�� */

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulExist1XService;
}MMA_TAF_1X_SERVICE_STATUS_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;                              /* _H2ASN_Skip */
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus;
    VOS_UINT8                           ucIsNewSession;
    VOS_UINT8                           aucReserved[3];
}MMA_APS_CL_SERVICE_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;                              /* _H2ASN_Skip */
}TAF_MMA_POWER_ON_IND_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;                              /* _H2ASN_Skip */
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT8                           ucPzid;
    VOS_UINT8                           ucReserved[3];
}MMA_APS_EPDSZID_INFO_IND_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/* ASN�����ṹ */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MMA_PID_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_PID_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_DATA                    stMsgData;
}TafMmaInterface_MSG;

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

#endif /* end of TafMmaInterface.h */


