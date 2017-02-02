
#ifndef  CALL_IMSA_INTERFACE_H
#define  CALL_IMSA_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallApi.h"
#include "TafClientApi.h"
#include "SpmImsaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#define   CALL_IMSA_MAX_ENTITY_NUM                          7

#define   IMSA_CALL_MSG_SYNC_MAX_NUM                        2

#define   IMSA_CALL_DTMF_REQ_MSG_MAX_NUM                    16
/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/


enum CALL_IMSA_SRVCC_STATUS_ENUM
{
    CALL_IMSA_SRVCC_STATUS_START        = 0,     /* SRVCC��ʼ */
    CALL_IMSA_SRVCC_STATUS_SUCCESS      = 1,     /* SRVCC�ɹ� */
    CALL_IMSA_SRVCC_STATUS_FAIL         = 2,     /* SRVCCʧ�� */
    CALL_IMSA_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32  CALL_IMSA_SRVCC_STATUS_ENUM_UINT32;
enum CALL_IMSA_SRVCC_CALL_STATE_ENUM
{
    CALL_IMSA_SRVCC_CALL_DIALING,                                                          /* dialing (MO call) */
    CALL_IMSA_SRVCC_CALL_ALERTING,                                                         /* alerting (MO call) */
    CALL_IMSA_SRVCC_CALL_ACTVING,                                                          /* activing --���״̬Э��涨Ҫ��GU���ش�connect��Ϣ */
    CALL_IMSA_SRVCC_CALL_ACTIVE,                                                           /* active */
    CALL_IMSA_SRVCC_CALL_HELD,                                                             /* held */
    CALL_IMSA_SRVCC_CALL_INCOMING,                                                         /* incoming (MT call) */
    CALL_IMSA_SRVCC_CALL_WAITING,                                                          /* waiting (MT call) */
    CALL_IMSA_SRVCC_CALL_BUTT
};
typedef VOS_UINT8  CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8;

enum CALL_IMSA_MSG_TYPE_ENUM
{
    ID_CALL_IMSA_SRVCC_STATUS_NOTIFY        = TAF_CALL_IMSA_MSG_BASE,            /* _H2ASN_MsgChoice CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU */

    ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY     = TAF_CALL_IMSA_MSG_BASE+0x100,      /* _H2ASN_MsgChoice CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU */

    ID_IMSA_CALL_MSG_SYNC_IND,                                                   /* _H2ASN_MsgChoice IMSA_CALL_MSG_SYNC_IND_STRU */

    ID_IMSA_CALL_CCWA_CAP_NOTIFY,                                                /* _H2ASN_MsgChoice IMSA_CALL_CCWA_CAP_NOTIFY_STRU */

    ID_CALL_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  CALL_IMSA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  3 ���Ͷ���
****************************************************************************/

typedef struct
{
    MN_CALL_ID_T                        CallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF����ʱ�䣬0: ����ֹͣDTMF */
    VOS_UINT16                          usOffLength;                            /* stop dtmf req��start dtmf reqʱ��������λms*/
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[3];
}IMSA_CALL_DTMF_REQ_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           aucReserve[3];
    IMSA_CALL_DTMF_REQ_INFO_STRU        astDtmf[IMSA_CALL_DTMF_REQ_MSG_MAX_NUM];
}TAF_CALL_DTMF_BUFF_STRU;



typedef struct
{
    MN_CLIENT_ID_T                                          clientId;
    MN_OPERATION_ID_T                                       opId;
    VOS_UINT8                                               ucCallId;
    VOS_UINT8                                               ucTi;                      /* TI��Ϣ������TI FLAG��TI��������ʽ�ο��������� */
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enCallState;               /* IMSAͬ��������IMS���µĺ���״̬ */
    MN_CALL_MODE_ENUM_U8                                    enCallMode;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    MN_CALL_DIR_ENUM_U8                                     enCallDir;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucLocalAlertedFlag; /* IMS���Ƿ���Ҫ���б������� */
    VOS_UINT8                                               ucEConferenceFlag;  /* ���ڱ�ʶͨ���Ƿ�����ǿ�Ͷ෽ͨ��: VOS_TRUE: ��ǿ�Ͷ෽ͨ�� VOS_FALSE: ����ǿ�Ͷ෽ͨ�� */
    MN_CALL_BCD_NUM_STRU                                    stCallNumber;
    MN_CALL_CALLED_NUM_STRU                                 stCalledNumber;
    MN_CALL_BCD_NUM_STRU                                    stRedirectNumber;
    MN_CALL_BCD_NUM_STRU                                    stConnectNumber;
}CALL_IMSA_SRVCC_CALL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucStartedHifiFlag;
    VOS_UINT8                           aucReserve[2];
    CALL_IMSA_SRVCC_CALL_INFO_STRU      astCallInfo[CALL_IMSA_MAX_ENTITY_NUM];
    TAF_CALL_DTMF_BUFF_STRU             stDtmfBuffInfo;
}CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    CALL_IMSA_SRVCC_STATUS_ENUM_UINT32  enSrvccStatus;
}CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU;

typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export CALL_IMSA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CALL_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}CALL_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CALL_IMSA_INTERFACE_MSG_DATA        stMsgData;
} CallImsaInterface_MSG;
typedef union
{
    SPM_IMSA_CALL_ORIG_REQ_STRU         stOrigReq;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     stSupsCmd;
    SPM_IMSA_CALL_START_DTMF_REQ_STRU   stStartDtmf;
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU    stStopDtmf;
}IMSA_CALL_MSG_UNION;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           aucReserve[3];
    IMSA_CALL_MSG_UNION                 astMsgArray[IMSA_CALL_MSG_SYNC_MAX_NUM];
}IMSA_CALL_MSG_SYNC_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucCcwaCap;                              /* 0:��֧��ccwa; 1:֧��ccwa */
    VOS_UINT8                           aucReserve[3];
}IMSA_CALL_CCWA_CAP_NOTIFY_STRU;
/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
/*
  IMSA�ṩ��API����TAF CALLģ����ã��ú����л����ڴ�ķ�����ͷš�
  CALLģ��֪ͨIMSA SRVCC����ʱ��CALLģ����øú��������ڻ�ȡSRVCC������ת��CS��ĺ�����Ϣ��
  ����ڴ���CALL���䣬pstCallInfoָ����ڴ��СΪCALL_IMSA_MAX_ENTITY_NUM*sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU)
  ����ֵVOS_FALSE, VOS_TRUE
*/
extern VOS_UINT32 CALL_IMSA_GetSrvccCallInfo(VOS_UINT8* pucCallNum,
                                  CALL_IMSA_SRVCC_CALL_INFO_STRU* pstCallInfo);


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

#endif /* CALL_IMSA_INTERFACE_H */

