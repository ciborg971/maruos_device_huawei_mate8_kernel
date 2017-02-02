

#ifndef _USIMM_API_H_
#define _USIMM_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**/
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*����USIMMģ����ܵ������Ϣ����*/
#define USIMM_MAX_MSG_NUM               100


/*SAT�������Ͷ���*/
#define USIMM_SATCMD_TAG                0xD0
#define USIMM_CMDDETAIL_TAG             0x81

/*������ٿ���ʱ��Ŀ��ļ�����*/
#define USIMM_EF6F62Len                 250
#define USIMM_EF6F7BLen                 12
#define USIMM_EF6F60Len                 170
#define USIMM_EF6F61Len                 250
#define USIMM_EF6F31Len                 1
#define USIMM_EF6FADLen                 4
#define USIMM_EF6F38Len                 7
#define USIMM_EF6F7ELen                 11
#define USIMM_EF6F73Len                 14
#define USIMM_EF6F53Len                 11
#define USIMM_EF6F07Len                 9
#define USIMM_EF6F08Len                 33
#define USIMM_EF6F09Len                 33
#define USIMM_EF6F20Len                 2
#define USIMM_EF6F52Len                 8
#define USIMM_EF4F20Len                 9
#define USIMM_EF4F52Len                 9
#define USIMM_EF6FB7Len                 14
#define USIMM_EF6F78Len                 2
#define USIMM_EF6F5BLen                 6
#define USIMM_EF6F5CLen                 3
#define USIMM_EF6FC4Len                 50
#define USIMM_EF6F74Len                 50

/*����OM͸��ͨ�����ص���Ϣ����*/
#define USIMM_OM_GET_CNF                0
#define USIMM_OM_SET_CNF                1
#define USIMM_GET_PRIMID                0xAA01
#define USIMM_SET_PRIMID                0xAA02

#define USIMM_TRANS_PRIMID              0x5001

/* ����USIM��ʼ���б��� */
#define USIMM_INIT_USIM_CARD_NUM        (11)

/* ����SIM��ʼ���б��� */
#define USIMM_INIT_SIM_CARD_NUM         (9)

/* ���忨���ͳ�ʼ���б��� */
#define USIMM_CARD_INIT_TBL_SIZE        (2)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

enum USIMM_CARDSTATUS_IND_ENUM
{
    USIMM_CARDSTATUS_IND_PLUGOUT = SIM_CARD_OUT,
    USIMM_CARDSTATUS_IND_PLUGIN  = SIM_CARD_IN,
    USIMM_CARDSTATUS_IND_BUTT
};

typedef VOS_UINT USIMM_CARDSTATUS_IND_ENUM_UINT32;
#endif

typedef VOS_UINT16 USIMM_CMDTYPE_ENUM_UINT16;
typedef VOS_UINT32 USIMM_CMDTYPE_ENUM_UINT32;


enum USIMM_FILE_TYPE_ENUM
{
    USIMM_EF_FILE               = 0,
    USIMM_DF_FILE               = 1,
    USIMM_FILE_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_FILE_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32       gulUSIMMOpneSpeed;

extern const VOS_UINT8  g_aucServIsimToUsim[];

/*****************************************************************************
  5 PV ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


typedef struct
{
    VOS_UINT16                      usEfid;
    VOS_UINT16                      usEFLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
}USIMM_SETCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEfId;
    VOS_UINT16                      usEfLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       ucTotalNum;
    VOS_UINT16                      usDataLen;
    VOS_UINT8                       *pucEf;
}USIMM_GETCNF_INFO_STRU;


typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;      /* Integrity key */
    VOS_UINT8                      *pucCK;      /* Cipher key */
    VOS_UINT8                      *pucGsmKC;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAuthRes; /* Auth user response */
}USIMM_TELECOM_AUTH_INFO_STRU;
typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;
    VOS_UINT8                      *pucCK;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAutsRes;
    VOS_UINT8                      *pucKs_ext_NAF;
    VOS_UINT8                      *pucResponse;
    VOS_UINT8                      *pucSessionKey;
}USIMM_IMS_AUTH_INFO_STRU;

typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;      /* Integrity key */
    VOS_UINT8                      *pucCK;      /* Cipher key */
    VOS_UINT8                      *pucAuthr;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAuthRes; /* Auth user response */
}USIMM_CDMA_AUTH_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEFId;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       ucRecordLen;
    VOS_UINT32                      ulFileStatus;
    VOS_UINT32                      ulFileReadUpdateFlag;
}USIMM_FILECNF_INFO_STRU;

typedef struct
{
    VOS_UINT8                       ucSW1;
    VOS_UINT8                       ucSW2;
    VOS_UINT8                       ucDataType;
    VOS_UINT8                       ucRsv;
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       *pucData;
}USIMM_ENVELOPECNF_INFO_STRU;

typedef struct
{
    VOS_UINT32                      ulErrorCode;
    VOS_UINT8                       ucSW1;
    VOS_UINT8                       ucSW2;
    VOS_UINT8                       ucRsv;
    VOS_UINT8                       ucLen;
    VOS_UINT8                       *pContent;
}USIMM_RACCESSCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEfid;
    VOS_UINT16                      usTotalRecNum;
    VOS_UINT32                      ulLen;
    VOS_UINT8                       *pucData;
}USIMM_SEARCHCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usFileId;
    VOS_UINT16                      usEfLen;
    NV_ID_ENUM_U16                  enNVId;
}USIMM_OPENSPEED_FILE_TO_NVID;

/*****************************************************************************
  8 API �·���Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
}USIMM_MsgBlock;


typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_FBDN_HANDLE_ENUM_UINT32   enFDNHandleType;
    VOS_UINT8                       aucPIN2[USIMM_PINNUMBER_LEN];
}USIMM_FDN_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_PIN_CMD_TYPE_ENUM_UINT32  enCmdType;
    USIMM_PIN_TYPE_ENUM_UINT32      enPINType;
    VOS_UINT8                       aucOldPIN[USIMM_PINNUMBER_LEN];
    VOS_UINT8                       aucNewPIN[USIMM_PINNUMBER_LEN];
}USIMM_PIN_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulPathLen;
    VOS_UINT16                      ausPath[USIMM_MAX_PATH_LEN];
    VOS_UINT16                      usDataLen;
    VOS_UINT16                      usRsv;
    VOS_UINT8                       aucContent[300];
}USIMM_GACCESS_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_CARDAPP_ENUM_UINT32       enAppType;
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType;
    VOS_UINT8                       ucOpId;
    VOS_UINT8                       aucRsv[3];
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       aucData[USIMM_AUTH_MSG_PADDING_LEN];
}USIMM_CMDTYPE_AUTHEN_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;          /* ��Ϣ���� */
    VOS_UINT16                          usRsv;              /* Rsv */
    VOS_UINT16                          usDataLen;          /* APDU���� */
    VOS_UINT8                           aucContent[300];      /* APDU������ */
}USIMM_ISDB_ACCESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_ACCESS_CHANNEL_REQ_STRU
 �ṹ˵��  : USIMģ��ACCESS CHANNEL APDU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;                              /* ��Ϣ���� */
    VOS_UINT32                          ulSessionID;                            /* ͨ���� */
    VOS_UINT32                          ulDataLen;                              /* ͸�����ݳ��� */
    VOS_UINT8                           aucData[300];                             /* ����������� */
}USIMM_ACCESS_CHANNEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_SENDTPDU_CNFINFO_STRU
 �ṹ˵��  : USIMģ��SEND TPDU REQ���ص����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSw1;
    VOS_UINT8                           ucSw2;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                          *pucData;
    VOS_UINT8                          *pucTPDUHead;
}USIMM_SENDTPDU_CNFINFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
}USIMM_DEACTIVE_CARD_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT16       enMsgType;
    VOS_UINT16                      usRsv;
}USIMM_ACTIVE_CARD_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulCardInOutStatus;
}USIMM_CARD_INOUT_IND_STRU;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;
    USIMM_CARDSTATUS_IND_ENUM_UINT32    ulCardStatus;
}USIMM_CARD_STATUS_IND_STRU;
#endif

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulSessionID;
    USIMM_FILEPATH_INFO_STRU        stFilePath;
    VOS_UINT8                       aucTPDUHead[USIMM_TPDU_HEAD_LEN];
    VOS_UINT8                       aucRsv[3];
    VOS_UINT32                      ulTPDUDataLen;
    VOS_UINT8                       aucTPDUData[300];
}USIMM_SENDTPDU_REQ_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    const VOS_CHAR                     *pcFilePath;
}USIMM_FILEID_PATHSTR_TABLE_STRU;


/***********************************************************
����API�ӿ�
***********************************************************/

extern VOS_UINT32 USIMM_ApiParaCheckSimple(VOS_VOID);

extern VOS_UINT32 USIMM_AsciiToHexCode(
    VOS_CHAR                            *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_CHAR                            *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_UINT32 USIMM_GetFilePathFormStr(
    USIMM_FILEPATH_INFO_STRU            *pstFilePath,
    VOS_UINT16                          *pusDFID,
    VOS_UINT16                          *pusSubDFID,
    VOS_UINT16                          *pusEFID);

extern USIMM_FILE_TYPE_ENUM_UINT32 USIMM_GetFileIDFromStr(
    USIMM_FILEPATH_INFO_STRU            *pstFilePath,
    VOS_UINT16                          *pusFID);

extern VOS_UINT32 USIMM_StrToFilePath(
    USIMM_FILEPATH_INFO_STRU *pstFilePath,
    VOS_UINT16              *pusPath,
    VOS_UINT32              *pusPathLen);

extern VOS_VOID USIMM_ChangePathToAsciiString(
    VOS_UINT8                           *pucPath,
    VOS_UINT8                            ucPathLen,
    USIMM_FILEPATH_INFO_STRU            *pstFilePath);

extern VOS_UINT32 USIMM_SendInitCardMsg(
    VOS_UINT32                          ulSenderPid,
    USIMM_CMDTYPE_REQ_ENUM_UINT32       enMsgType);

extern VOS_UINT32 USIMM_Read_OpenSpeedFile(
    USIMM_READFILE_REQ_STRU             *pstMsg,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_ApiParaCheck(VOS_VOID);

extern VOS_VOID USIMM_MaxRecordNumCnf(
    USIMM_QUERYFILE_REQ_STRU            *pstNewMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_FILECNF_INFO_STRU             *pstCnfInfo);

extern VOS_VOID USIMM_PinHandleCnf(
    USIMM_PINHANDLE_REQ_STRU            *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_PIN_INFO_STRU                 *pstPINinfo);

extern VOS_VOID USIMM_SetSPBFileCnf(
    USIMM_SETMUTILFILE_REQ_STRU         *pstReqMsg,
    VOS_UINT32                          ulErrorCode);

extern VOS_VOID USIMM_SetFileCnf(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_SETCNF_INFO_STRU              *pstCnfInfo);

extern VOS_VOID USIMM_GetFileCnf(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo);

extern VOS_VOID USIMM_ResetCnf(
    VOS_UINT32                          ulReceiverPid,
    USIMM_REFRESH_TYPE_ENUM_UINT32      enRefreshType,
    VOS_UINT32                          ulResult,
    VOS_UINT16                          usSATLen);

extern VOS_VOID USIMM_TelecomAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_TELECOM_AUTH_INFO_STRU        *pstCnfInfo);

extern VOS_VOID USIMM_ImsAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_IMS_AUTH_INFO_STRU            *pstCnfInfo);

extern VOS_VOID USIMM_CardStatusInd(
    VOS_UINT32                          ulReceiverPid);

extern VOS_VOID USIMM_RestrictedAccessCnf(
    USIMM_RACCESS_REQ_STRU              *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_RACCESSCNF_INFO_STRU          *pstCnfInfo);

extern VOS_VOID USIMM_TerminalResponseCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulErrorCode,
    VOS_UINT32                          ulSendPara,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2);

extern VOS_VOID USIMM_EnvelopeCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulErrorCode,
    USIMM_ENVELOPECNF_INFO_STRU         *pstCnfInfo);

extern VOS_VOID USIMM_SatDataInd(
    VOS_UINT8                           ucCmdType,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                           *pData);

extern VOS_VOID USIMM_VsimReDhNegotiateInd(VOS_VOID);

extern VOS_VOID USIMM_SingleCmdCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    USIMM_CARDAPP_ENUM_UINT32           enApptype);

extern VOS_VOID USIMM_EccNumberInd(
    VOS_UINT8                           ucEccType,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT8                           *pucData);

extern VOS_VOID USIMM_XeccNumberInd(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucData);

extern VOS_VOID USIMM_FDNCnf(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    VOS_UINT32                          ulResult);

extern USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_GetPhyCardType(VOS_VOID);

extern VOS_VOID USIMM_SearchHandleCnf(
    USIMM_SEARCHFILE_REQ_STRU           *pstMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_SEARCHCNF_INFO_STRU           *pstCnfInfo);

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_VOID USIMM_SCICardOutNotify(
    VOS_UINT32                          ulCardInOutStatus);

extern VOS_VOID USIMM_SciCardStatusIndCbFunc(
    USIMM_CARDSTATUS_IND_ENUM_UINT32    enCardStatus);
#endif

extern VOS_VOID USIMM_OpenChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT8                           ucChannelNo);

extern VOS_VOID USIMM_CloseChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode);

extern VOS_VOID USIMM_CdmaAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_CDMA_AUTH_INFO_STRU           *pstCnfInfo);

extern VOS_VOID USIMM_BSChallengeCnf(
    USIMM_CMDHEADER_REQ_STRU            *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucRandBs);

extern VOS_VOID USIMM_GenerateKeyVpmCnf(
    USIMM_GENERATE_KEYVPM_REQ_STRU      *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulVpmLen,
    VOS_UINT8                           *pucVpm,
    VOS_UINT8                           *pucKey);

extern VOS_VOID USIMM_CdmaSepcAuthCnf(
    USIMM_CMDHEADER_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulErrCode,
    USIMM_CDMASPEC_AUTHTYPE_ENUM_UINT32 enAuthType,
    USIMM_CDMASPECAUTH_DATA_UNION      *puAuthCnf);

extern VOS_VOID USIMM_CardTimeOutEventInd(VOS_VOID);

#else

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*����USIMMģ����ܵ������Ϣ����*/
#define USIMM_MAX_MSG_NUM               100


/*SAT�������Ͷ���*/
#define USIMM_SATCMD_TAG                0xD0
#define USIMM_CMDDETAIL_TAG             0x81

/*������ٿ���ʱ��Ŀ��ļ�����*/
#define USIMM_EF6F62Len                 250
#define USIMM_EF6F7BLen                 12
#define USIMM_EF6F60Len                 170
#define USIMM_EF6F61Len                 250
#define USIMM_EF6F31Len                 1
#define USIMM_EF6FADLen                 4
#define USIMM_EF6F38Len                 7
#define USIMM_EF6F7ELen                 11
#define USIMM_EF6F73Len                 14
#define USIMM_EF6F53Len                 11
#define USIMM_EF6F07Len                 9
#define USIMM_EF6F08Len                 33
#define USIMM_EF6F09Len                 33
#define USIMM_EF6F20Len                 2
#define USIMM_EF6F52Len                 8
#define USIMM_EF4F20Len                 9
#define USIMM_EF4F52Len                 9
#define USIMM_EF6FB7Len                 14
#define USIMM_EF6F78Len                 2
#define USIMM_EF6F5BLen                 6
#define USIMM_EF6F5CLen                 3
#define USIMM_EF6FC4Len                 50
#define USIMM_EF6F74Len                 50

/*����OM͸��ͨ�����ص���Ϣ����*/
#define USIMM_OM_GET_CNF                0
#define USIMM_OM_SET_CNF                1
#define USIMM_GET_PRIMID                0xAA01
#define USIMM_SET_PRIMID                0xAA02

#define USIMM_TRANS_PRIMID              0x5001

/* ����USIM��ʼ���б��� */
#define USIMM_INIT_USIM_CARD_NUM        (12)

/* ����SIM��ʼ���б��� */
#define USIMM_INIT_SIM_CARD_NUM         (9)

/* ���忨���ͳ�ʼ���б��� */
#define USIMM_CARD_INIT_TBL_SIZE        (2)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

enum USIMM_CARDSTATUS_IND_ENUM
{
    USIMM_CARDSTATUS_IND_PLUGOUT = SIM_CARD_OUT,
    USIMM_CARDSTATUS_IND_PLUGIN  = SIM_CARD_IN,
    USIMM_CARDSTATUS_IND_BUTT
};

typedef VOS_UINT USIMM_CARDSTATUS_IND_ENUM_UINT32;
#endif


enum USIMM_APP_TYPE_ENUM
{
    USIMM_GSM_APP                       = 0,
    USIMM_UMTS_APP,
    USIMM_PB_APP,
    USIMM_ATT_APP,
    USIMM_ISIM_APP,
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    USIMM_3GPP2_APP,
#endif
    USIMM_UNLIMIT_APP,
    USIMM_APP_BUTT
};
typedef VOS_UINT32 USIMM_APP_TYPE_ENUM_UINT32;

typedef VOS_UINT16 USIMM_CMDTYPE_ENUM_UINT16;
typedef VOS_UINT32 USIMM_CMDTYPE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32       gulUSIMMOpneSpeed;

extern const VOS_UINT8  g_aucServIsimToUsim[];

/*****************************************************************************
  5 PV ����
*****************************************************************************/

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT16                      usEfid;
    VOS_UINT16                      usEFLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
}USIMM_SETCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEfId;
    VOS_UINT16                      usEfLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       ucTotalNum;
    VOS_UINT16                      usDataLen;
    VOS_UINT8                       *pucEf;
}USIMM_GETCNF_INFO_STRU;


typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;      /* Integrity key */
    VOS_UINT8                      *pucCK;      /* Cipher key */
    VOS_UINT8                      *pucGsmKC;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAuthRes; /* Auth user response */
}USIMM_TELECOM_AUTH_INFO_STRU;
typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;
    VOS_UINT8                      *pucCK;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAutsRes;
    VOS_UINT8                      *pucKs_ext_NAF;
}USIMM_IMS_AUTH_INFO_STRU;

typedef struct
{
    USIMM_AUTH_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                      *pucIK;      /* Integrity key */
    VOS_UINT8                      *pucCK;      /* Cipher key */
    VOS_UINT8                      *pucAuthr;
    VOS_UINT8                      *pucAuts;
    VOS_UINT8                      *pucAuthRes; /* Auth user response */
}USIMM_CDMA_AUTH_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEFId;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       ucRecordLen;
    VOS_UINT32                      ulFileStatus;
    VOS_UINT32                      ulFileReadUpdateFlag;
}USIMM_FILECNF_INFO_STRU;

typedef struct
{
    VOS_UINT8                       ucSW1;
    VOS_UINT8                       ucSW2;
    VOS_UINT8                       ucDataType;
    VOS_UINT8                       ucRsv;
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       *pucData;
}USIMM_ENVELOPECNF_INFO_STRU;

typedef struct
{
    VOS_UINT32                      ulErrorCode;
    VOS_UINT8                       ucSW1;
    VOS_UINT8                       ucSW2;
    VOS_UINT8                       ucRsv;
    VOS_UINT8                       ucLen;
    VOS_UINT8                       *pContent;
}USIMM_RACCESSCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usEfid;
    VOS_UINT16                      usTotalRecNum;
    VOS_UINT32                      ulLen;
    VOS_UINT8                       *pucData;
}USIMM_SEARCHCNF_INFO_STRU;

typedef struct
{
    VOS_UINT16                      usFileId;
    VOS_UINT16                      usEfLen;
    NV_ID_ENUM_U16                  enNVId;
}USIMM_OPENSPEED_FILE_TO_NVID;

/*****************************************************************************
  8 API �·���Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
}USIMM_MsgBlock;


typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT32                      ulSendPara;
    VOS_UINT16                      usFileID;
    VOS_UINT16                      usDataLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucContent[3];
}USIMM_SETFILE_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT32                      ulSendPara;
    VOS_UINT16                      usFileID;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       ucRsv;
}USIMM_GETFILE_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType;
    VOS_UINT32                      ulOpId;
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       aucData[USIMM_APDU_DATA_MAXLEN+1];
}USIMM_AUTH_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_FBDN_HANDLE_ENUM_UINT32   enFDNHandleType;
    VOS_UINT8                       aucPIN2[USIMM_PINNUMBER_LEN];
}USIMM_FDN_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_PIN_CMD_TYPE_ENUM_UINT32  enCmdType;
    USIMM_PIN_TYPE_ENUM_UINT32      enPINType;
    VOS_UINT8                       aucOldPIN[USIMM_PINNUMBER_LEN];
    VOS_UINT8                       aucNewPIN[USIMM_PINNUMBER_LEN];
}USIMM_PIN_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT16                      usEfId;
    VOS_UINT16                      usRev;
}USIMM_MAXRECORD_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulSendPara;
    VOS_UINT32                      ulPathLen;
    VOS_UINT16                      ausPath[USIMM_MAX_PATH_LEN];
    VOS_UINT16                      usDataLen;
    VOS_UINT16                      usRsv;
    VOS_UINT8                       aucContent[300];
}USIMM_GACCESS_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_CARDAPP_ENUM_UINT32       enAppType;
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType;
    VOS_UINT8                       ucOpId;
    VOS_UINT8                       aucRsv[3];
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       aucData[USIMM_AUTH_MSG_PADDING_LEN];
}USIMM_CMDTYPE_AUTHEN_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;          /* ��Ϣ���� */
    VOS_UINT32                          ulSendPara;
    VOS_UINT16                          usRsv;              /* Rsv */
    VOS_UINT16                          usDataLen;          /* APDU���� */
    VOS_UINT8                           aucContent[300];      /* APDU������ */
}USIMM_ISDB_ACCESS_REQ_STRU;



/*****************************************************************************
 �ṹ��    : USIMM_CHANNEL_AIDFCPINFO_STRU
 �ṹ˵��  : USIMģ��CHANNEL AID FCP INFO�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAIDFCPLen;                            /* AIDѡ�к󷵻����ݳ��� */
    VOS_UINT8                           aucADFFcp[USIMM_TPDU_DATA_LEN_MAX];     /* AID��FCP���� */
}USIMM_CHANNEL_AIDFCPINFO_STRU;


/*****************************************************************************
 �ṹ��    : USIMM_ACCESS_CHANNEL_REQ_STRU
 �ṹ˵��  : USIMģ��ACCESS CHANNEL APDU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;                              /* ��Ϣ���� */
    VOS_UINT32                          ulSendPara;
    VOS_UINT32                          ulSessionID;                            /* ͨ���� */
    VOS_UINT32                          ulDataLen;                              /* ͸�����ݳ��� */
    VOS_UINT8                           aucData[300];                             /* ����������� */
}USIMM_ACCESS_CHANNEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_SENDTPDU_CNFINFO_STRU
 �ṹ˵��  : USIMģ��SEND TPDU REQ���ص����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSw1;
    VOS_UINT8                           ucSw2;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                          *pucData;
    VOS_UINT8                          *pucTPDUHead;
}USIMM_SENDTPDU_CNFINFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT16                      usEfId;
    VOS_UINT16                      usRsv;
    VOS_UINT8                       ucLen;
    VOS_UINT8                       aucContent[255];
}USIMM_SEARCH_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
}USIMM_DEACTIVE_CARD_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT16       enMsgType;
    VOS_UINT16                      usRsv;
}USIMM_ACTIVE_CARD_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulCardInOutStatus;
}USIMM_CARD_INOUT_IND_STRU;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32           enMsgType;
    USIMM_CARDSTATUS_IND_ENUM_UINT32    ulCardStatus;
}USIMM_CARD_STATUS_IND_STRU;
#endif

typedef struct
{
    VOS_MSG_HEADER
    USIMM_CMDTYPE_ENUM_UINT32       enMsgType;
    VOS_UINT32                      ulSendPara;
    VOS_UINT32                      ulSessionID;
    USIMM_FILEPATH_INFO_STRU        stFilePath;
    VOS_UINT8                       aucTPDUHead[USIMM_TPDU_HEAD_LEN];
    VOS_UINT8                       aucRsv[3];
    VOS_UINT32                      ulTPDUDataLen;
    VOS_UINT8                       aucTPDUData[300];
}USIMM_SENDTPDU_REQ_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    const VOS_CHAR                     *pcFilePath;
}USIMM_FILEID_PATHSTR_TABLE_STRU;


/***********************************************************
����API�ӿ�
***********************************************************/

extern VOS_UINT32 USIMM_ApiParaCheckSimple(VOS_VOID);

extern VOS_UINT32 USIMM_AsciiToHexCode(VOS_CHAR *pucSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pucDst, VOS_UINT32 *pulDstLen);

extern VOS_UINT32 USIMM_GetFilePathFormStr(USIMM_FILEPATH_INFO_STRU *pstFilePath, VOS_UINT16  *pusDFID, VOS_UINT16  *pusSubDFID, VOS_UINT16 *pusEFID);

extern VOS_UINT32 USIMM_StrToFilePath(USIMM_FILEPATH_INFO_STRU *pstFilePath, VOS_UINT16 *pusPath, VOS_UINT32  *pusPathLen);

extern VOS_VOID USIMM_ChangePathToAsciiString(VOS_UINT8 *pucPath, VOS_UINT8 ucPathLen, VOS_CHAR *pucDest, VOS_UINT16 *pusLen);

extern VOS_UINT32 USIMM_SendInitCardMsg(VOS_UINT32 ulSenderPid, USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgType);

extern VOS_UINT32 USIMM_Read_OpenSpeedFile(USIMM_READFILE_REQ_STRU *pstMsg, VOS_UINT16 usFileID);

extern VOS_UINT32 USIMM_ApiParaCheck(VOS_VOID);

extern VOS_VOID USIMM_MaxRecordNumCnf(USIMM_QUERYFILE_REQ_STRU  *pstNewMsg,VOS_UINT32 ulErrorCode,USIMM_FILECNF_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_PinHandleCnf(USIMM_PINHANDLE_REQ_STRU  *pstReqMsg,VOS_UINT32 ulResult, USIMM_PIN_INFO_STRU *pstPINinfo);

extern VOS_VOID USIMM_SetSPBFileCnf(USIMM_SETMUTILFILE_REQ_STRU *pstReqMsg,VOS_UINT32 ulErrorCode);

extern VOS_VOID USIMM_SetFileCnf(USIMM_UPDATEFILE_REQ_STRU *pstNewMsg, VOS_UINT32 ulErrorCode,USIMM_SETCNF_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_GetFileCnf(USIMM_READFILE_REQ_STRU *pstNewMsg, VOS_UINT32 ulErrorCode, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_ResetCnf(VOS_UINT32 ulReceiverPid,USIMM_REFRESH_TYPE_ENUM_UINT32 enRefreshType,VOS_UINT32 ulResult, VOS_UINT16 usSATLen);

extern VOS_VOID USIMM_TelecomAuthCnf(USIMM_AUTH_REQ_STRU  *pstMsg,  USIMM_TELECOM_AUTH_INFO_STRU  *pstCnfInfo);

extern VOS_VOID USIMM_ImsAuthCnf(USIMM_AUTH_REQ_STRU *pstMsg, USIMM_IMS_AUTH_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_CardStatusInd(VOS_UINT32 ulReceiverPid);

extern VOS_VOID USIMM_RestrictedAccessCnf( USIMM_RACCESS_REQ_STRU *pstReqMsg, VOS_UINT32 ulResult,  USIMM_RACCESSCNF_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_TerminalResponseCnf(VOS_UINT32 ulReceiverPid,VOS_UINT32 ulErrorCode, VOS_UINT32 ulSendPara, VOS_UINT8 ucSW1,VOS_UINT8 ucSW2);

extern VOS_VOID USIMM_EnvelopeCnf(VOS_UINT32 ulReceiverPid, VOS_UINT32 ulSendPara, VOS_UINT32 ulErrorCode, USIMM_ENVELOPECNF_INFO_STRU *pstCnfInfo);

extern VOS_VOID USIMM_SatDataInd(VOS_UINT8   ucCmdType,VOS_UINT16 usDataLen,VOS_UINT8 *pData);

extern VOS_VOID USIMM_VsimReDhNegotiateInd(VOS_VOID);

extern VOS_VOID USIMM_SingleCmdCnf(VOS_UINT32  ulReceiverPid, VOS_UINT32 ulMsgName, VOS_UINT32 ulSendPara, VOS_UINT32 ulResult, USIMM_CARDAPP_ENUM_UINT32 enApptype);

extern VOS_VOID USIMM_EccNumberInd(VOS_UINT8 ucEccType,VOS_UINT16 usEfLen,VOS_UINT8 ucRecordNum,VOS_UINT8 *pucData);

extern VOS_VOID USIMM_FDNCnf(VOS_UINT32 ulReceiverPid, VOS_UINT32 ulResult,VOS_UINT32 ulErrCode,USIMM_CARDAPP_ENUM_UINT32 enAppType, VOS_UINT32 ulSendPara,VOS_UINT32 ulFDNState);
extern USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_GetPhyCardType(VOS_VOID);

extern VOS_VOID USIMM_SearchHandleCnf(USIMM_SEARCHFILE_REQ_STRU *pstMsg, VOS_UINT32  ulErrorCode, USIMM_SEARCHCNF_INFO_STRU   *pstCnfInfo);

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_VOID USIMM_SCICardOutNotify(VOS_UINT32 ulCardInOutStatus);

extern VOS_VOID USIMM_SciCardStatusIndCbFunc(USIMM_CARDSTATUS_IND_ENUM_UINT32 enCardStatus);
#endif

extern VOS_VOID USIMM_OpenChannelCnf(VOS_UINT32  ulReceiverPid, VOS_UINT32 ulSendPara, VOS_UINT32 ulResult, VOS_UINT32  ulErrCode,  VOS_UINT32 ulSessionId, VOS_UINT8  ucChannelId);

extern VOS_VOID USIMM_CloseChannelCnf(VOS_UINT32 ulReceiverPid, VOS_UINT32 ulSendPara, VOS_UINT32 ulResult, VOS_UINT32 ulErrCode);

extern VOS_VOID USIMM_SendTPDUCnf(VOS_UINT32 ulReceiverPid, VOS_UINT32  ulSendPara, VOS_UINT32  ulResult, VOS_UINT32   ulErrCode,  USIMM_SENDTPDU_CNFINFO_STRU  *pstDataCnf, USIMM_FILEPATH_INFO_STRU  *pstFilePath);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
extern VOS_UINT32 USIMM_CdmaParaCheckSimple(VOS_VOID);

extern VOS_VOID USIMM_CdmaAuthCnf(USIMM_AUTH_REQ_STRU *pstMsg, USIMM_CDMA_AUTH_INFO_STRU  *pstCnfInfo);

extern VOS_VOID USIMM_BSChallengeCnf(USIMM_CMDHEADER_REQ_STRU *pstReqMsg, VOS_UINT32 ulResult, VOS_UINT32 ulErrCode, VOS_UINT32 ulDataLen, VOS_UINT8 *pucRandBs);

extern VOS_VOID USIMM_GenerateKeyVpmCnf(USIMM_GENERATE_KEYVPM_REQ_STRU *pstReqMsg, VOS_UINT32 ulResult,  VOS_UINT32 ulErrCode, VOS_UINT32 ulVpmLen, VOS_UINT8 *pucVpm, VOS_UINT8 *pucKey);

#endif

#endif
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

#endif /* end of UsimmApi.h*/

