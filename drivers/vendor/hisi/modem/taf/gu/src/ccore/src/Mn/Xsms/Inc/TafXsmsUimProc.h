/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsUimProc.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : TafXsmsUimProc.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_UIM_PROC_H_
#define _TAF_XSMS_UIM_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"
#include "TafAppXsmsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* UIM���ж��ŵ�����¼�� */
#define TAF_XSMS_RECORD_NUM_MAX    (255)

/* UIM���ж��ŵ���󳤶� */
#define TAF_XSMS_RECORD_LEN_MAX    (255)

/* UIM����IMSI����󳤶� */
#define TAF_XSMS_IMSI_LEN_MAX      (10)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XSMS_UIM_MSG_STATUS_ENUM32
 ö��˵��  : UIM���ж��ŵ�״̬
*****************************************************************************/
enum TAF_XSMS_UIM_MSG_STATUS_ENUM
{
    TAF_XSMS_UIM_MSG_STATUS_FREE   = 0,
    TAF_XSMS_UIM_MSG_STATUS_READ   = 1,
    TAF_XSMS_UIM_MSG_STATUS_UNREAD = 3,
    TAF_XSMS_UIM_MSG_STATUS_SEND   = 5,
    TAF_XSMS_UIM_MSG_STATUS_UNSEND = 7,
    TAF_XSMS_UIM_MSG_STATUS_BUTT   = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_UIM_MSG_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_UIM_REQ_TYPE_ENUM32
 ö��˵��  : XSMS�뿨������Դ
*****************************************************************************/
enum TAF_XSMS_UIM_REQ_TYPE_ENUM
{
    TAF_XSMS_UIM_REQ_TYPE_INIT     = 0,
    TAF_XSMS_UIM_REQ_TYPE_AT       = 1,
    TAF_XSMS_UIM_REQ_TYPE_MO       = 2,
    TAF_XSMS_UIM_REQ_TYPE_MT       = 3,
    TAF_XSMS_UIM_REQ_TYPE_BUTT     = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_UIM_REQ_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_INIT_STATUS_ENUM
 ö��˵��  : EFSMS��ʼ��״̬
*****************************************************************************/
enum TAF_XSMS_INIT_STATUS_ENUM
{
    TAF_XSMS_INIT_STATUS_NOT_INIT  = 0,
    TAF_XSMS_INIT_STATUS_FINISH    = 1,
    TAF_XSMS_INIT_STATUS_BUTT      = 0xFFFFFFFF
};

typedef VOS_UINT32 TAF_XSMS_INIT_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_XSMS_UIM_MSG_STATUS_ENUM32
 ö��˵��  : UIM���ж��ŵ�ʹ��״̬
*****************************************************************************/
enum TAF_XSMS_EFSMS_STATUS_ENUM
{
    TAF_XSMS_EFSMS_STATUS_FREE     = 0,
    TAF_XSMS_EFSMS_STATUS_USED     = 1,
    TAF_XSMS_EFSMS_STATUS_BUTT     = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_EFSMS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_UIM_LOCK_ENUM8
 ö��˵��  : XSMS�ṩ�Ķ���API�Կ���������
*****************************************************************************/
enum TAF_XSMS_UIM_LOCK_ENUM
{
    TAF_XSMS_UIM_LOCK_UNLOCK       = 0,
    TAF_XSMS_UIM_LOCK_LOCKED       = 1,
    TAF_XSMS_UIM_LOCK_BUTT
};
typedef VOS_UINT8 TAF_XSMS_UIM_LOCK_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_FILEID_ENUM_ENUM_UINT32
 ö��˵��  :
*****************************************************************************/
enum TAF_XSMS_FILEID_ENUM
{
    TAF_XSMS_EFSMS_FILEID           = 0,
    TAF_XSMS_EFSMSS_FILEID          = 1,
    TAF_XSMS_EFIMSIT_FILEID         = 2,
    TAF_XSMS_FILEID_BUTT
};
typedef VOS_UINT32 TAF_XSMS_FILEID_ENUM_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
//extern TAF_XSMS_INIT_CTRL_INFO_STRU    g_stTAFXsmsInitCtrlInfo;
//extern TAF_XSMS_CTRL_INFO_STRU         g_stTAFXsmsReqCtrlInfo;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :TAF_XSMS_UIM_MSG_STRU
 �ṹ˵��  :XSMS�뿨������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��ϢID */
}TAF_XSMS_UIM_MSG_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_CURRENT_INIT_FILE_STRU
 �ṹ˵��  :XSMS�뿨������ǰ���ڶ�ȡ���ļ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrFile;         /* ��ǰ�ڶ�ȡ���ļ� */
    VOS_UINT8                           ucCurrIndex;        /* ��ǰ�ڶ�ȡ�ļ�¼ */
    VOS_UINT8                           ucRsv;
}TAF_XSMS_CURRENT_INIT_FILE_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_INIT_CTRL_INFO_STRU
 �ṹ˵��  :XSMS��ʼ��״̬���ƽṹ
*****************************************************************************/
typedef struct
{
    TAF_XSMS_INIT_STATUS_ENUM_UINT32    enSmsInitState;                                 /* SMS��ʼ��״̬ */
    TAF_XSMS_CURRENT_INIT_FILE_STRU     stCurrInitFile;                                 /* ��ǰ��ʼ�����ļ� */
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;                                     /* ���浱ǰ�������ͣ�����UIM/CSIMʱ�Ż��ʼ�� */
    VOS_UINT16                          usMessageId;                                    /* ���ŷ���ʱ��Ҫʹ�õ�ID */
    VOS_UINT8                           aucImsi[TAF_XSMS_IMSI_LEN_MAX];                /* EFIMSI���� */
    VOS_UINT8                           aucFreeIndex[(TAF_XSMS_RECORD_NUM_MAX + 1)/8]; /* EFSMSʹ������ */
    VOS_UINT8                           ucMaxRecord;                                    /* EFSMS����¼�� */
    VOS_UINT8                           ucRecordLen;                                    /* EFSMS��¼���� */
    VOS_UINT8                           ucTotalUsed;                                    /* EFSMS��ǰʹ�ü�¼�� */
    VOS_UINT8                           ucRsv;
    VOS_UINT8                          *pucContent;                                     /* EFSMS���ڴ��е����ݣ���ǰ��ʱ��ʹ�� */
}TAF_XSMS_INIT_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    :TAF_XSMS_CTRL_INFO_STRU
 �ṹ˵��  :XSMS����API�Ŀ��ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usClient;
    VOS_UINT8                           ucOpID;
    TAF_XSMS_UIM_LOCK_ENUM_UINT8        enUimLock;
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32   enAppMsgType;
}TAF_XSMS_CTRL_INFO_STRU;

typedef struct
{
    TAF_XSMS_FILEID_ENUM_ENUM_UINT32    enFileID;
    USIMM_DEF_FILEID_ENUM_UINT32        enUIMID;
    USIMM_DEF_FILEID_ENUM_UINT32        enCSIMID;
}TAF_XSMS_FILETABLE_STRU;

typedef struct
{
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
    VOS_UINT16                  usEfLen ;       /* �������ݳ��� */
    VOS_UINT8                   *pucEfContent;  /* ������������ */
}TAF_XSMS_SETFILE_INFO_STRU;

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 TAF_XSMS_FindFreeIndex(VOS_UINT8 *pucIndex);

extern VOS_VOID   TAF_XSMS_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue);

extern VOS_UINT32 TAF_XSMS_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo);

extern VOS_UINT32 TAF_XSMS_AtSmsDeleteReq(VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_MsgIdUpdataReq(VOS_UINT8 *pucMsgId);

extern VOS_UINT32 TAF_XSMS_AtSmsWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_PrlWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucPrl, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_CommonFileWriteReq(VOS_UINT8 ucLen, VOS_UINT8 * pucData, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_PrlReadReq(VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_InitFileReadReq(VOS_UINT8 ucIndex, VOS_UINT32 enFileId);

extern VOS_VOID   TAF_XSMS_PihStatusIndProc(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_PihMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitUsimmMaxRecordRspMsgProc(USIMM_QUERYFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitEfsmsFileMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitTimeOutMsgProc(VOS_VOID);

extern VOS_VOID   TAF_XSMS_InitUsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_MtGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_MtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg);

extern VOS_UINT32 TAF_XSMS_SetFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID,
                                        VOS_UINT32                      ulSendPara,
                                        TAF_XSMS_SETFILE_INFO_STRU      *pstFileInfo);

extern VOS_UINT32 TAF_XSMS_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32   enFileID,
                                        VOS_UINT32                    ulSendPara,
                                        VOS_UINT8                      ucIndex);
/* Added by h00313353 for iteration 9, 2015-2-26, begin */
extern VOS_UINT32 TAF_XSMS_QueryFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID);
/* Added by h00313353 for iteration 9, 2015-2-26, end */

/* Added by h00313353 for iteration 9, 2015-2-26, begin */
extern VOS_VOID TAF_XSMS_ChangeFileID(TAF_XSMS_FILEID_ENUM_ENUM_UINT32   enFileID,
                                      USIMM_DEF_FILEID_ENUM_UINT32      *penDefID);
/* Added by h00313353 for iteration 9, 2015-2-26, end */
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
