

#ifndef _GPHYCSTINTERFACE_H_
#define _GPHYCSTINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
   ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
   �궨��
*****************************************************************************/

/*CST��GPHY֮���ԭ��*/
#define ID_CST_PH_DATA_REQ                      0xD751
#define ID_PH_CST_READY_TO_SEND                 0x7D52

/*****************************************************************************
   ȫ�ֱ�������
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************

*****************************************************************************/
typedef struct
{
    VOS_UINT16   usMsgType;       /* ��ϢID */
    VOS_UINT16   usChanType;   /* ���з���TCH�ŵ�����*/
} PH_CST_READY_TO_SEND_STRU;

/* ===== 1. ��Ϣ  =====*/
typedef struct
{
    VOS_MSG_HEADER
    PH_CST_READY_TO_SEND_STRU stSendInd;
} GHPA_CST_READY_TO_SEND_MSG;

#define CST_DL_BUF_LEN  19

typedef struct
{
    VOS_UINT16   usMsgType;         /* ����������Ϣ*/
    VOS_UINT16   usErrorFlag;       /* �������ָʾ*/
    VOS_UINT16   usTn;              /* ʱ϶��*/
    VOS_UINT16   ausRsv;            /* ���뱣��*/
    VOS_UINT32   ulFrmNum;          /* ��ǰ֡��*/
    VOS_UINT16   usBitLen;          /* ���ݵ�bit����*/
    VOS_UINT16   ausBitData[CST_DL_BUF_LEN]; /* ������ */
}PH_CST_DATA_IND_STRU;

/*GSM����������ָʾ��Ϣ*/
typedef struct
{
    VOS_MSG_HEADER
    PH_CST_DATA_IND_STRU stSendReq;
} PH_CST_DATA_IND_MSG;


typedef struct
{
    VOS_UINT16   usMsgType;   /* ����������Ϣ*/
    VOS_UINT16   ausRsv;      /* ���뱣��*/
    VOS_UINT16   usBitLen;    /* ���ݵ�bit����*/
    VOS_UINT16   ausBitData[CST_DL_BUF_LEN];  /* ������ */
}CST_PH_DATA_REQ_STRU;

/* =====   =====*/
typedef struct
{
    VOS_MSG_HEADER
    CST_PH_DATA_REQ_STRU stSendReq;
} CST_PH_DATA_REQ_MSG;

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#pragma pack(0)

/*****************************************************************************
  9 ��������
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* The end*/


