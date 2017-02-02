

#ifndef __USIMM_T1_DL_H__
#define __USIMM_T1_DL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "usimmapdu.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����Ϣ��ΧΪ1-254 */
#define     USIMM_T1_MAX_IFS                        (254)
#define     USIMM_T1_MIN_IFS                        (1)

/* LRCУ����Ϊһ�ֽ� */
#define     USIMM_T1_LRC_SIZE                       (1)

/* CRCУ����Ϊ���ֽ� */
#define     USIMM_T1_CRC_SIZE                       (2)

/* ���������ش����Դ���Ϊ2*/
#define     USIMM_T1_MAX_ATTEMPTS_TIMES             (2)

/* I-BLOCK�鷢�ͳ�ʼ��� */
#define     USIMM_T1_I_BLOCK_INIT_SEQ               (0)

/* WTXĬ��ֵ,Ĭ�ϵȴ�һ��BWTʱ�� */
#define     USIMM_T1_DEFAULT_WTX                    (1)

/* I-block ��PCB�ֽ��У�N(S) bit��λ�� */
#define     USIMM_I_BLOCK_PCB_NS_BIT                (7)

/* I-block ��PCB�ֽ��У�N(S) bit������ */
#define     USIMM_I_BLOCK_PCB_NS_BIT_MASK           (0x40)

/* I-block ��PCB�ֽ��У�More data bit��λ�� */
#define     USIMM_I_BLOCK_PCB_MORE_DATA_BIT         (6)

/* I-block ��PCB�ֽ��У�More data bit������ */
#define     USIMM_I_BLOCK_PCB_MORE_DATA_BIT_MASK    (0x20)

/* R-block ��PCB�ֽ��У���6 bit������ */
#define     USIMM_R_BLOCK_PCB_SIXTH_BIT_MASK        (0x20)

/* R-block ��PCB�ֽ��У�N(R) bit��λ�� */
#define     USIMM_R_BLOCK_PCB_NR_BIT                (5)

/* R-block ��PCB�ֽ��У�N(R) bit������ */
#define     USIMM_R_BLOCK_PCB_NR_BIT_MASK           (0x10)

/* R-block ��PCB�ֽ��У�error code bit������ */
#define     USIMM_R_BLOCK_PCB_ERRCODE_BIT_MASK      (0x0F)

/* S-block ��PCB�ֽ��У�request/response bit������ */
#define     USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK      (0x20)

/* ����PCB�ֽڸ���bitȷ�������� */
#define     USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK        (0xC0)

/* S-block ��PCB�ֽ���,S-block�����ͻ�ȡ */
#define     USIMM_T1_BLOCK_PCB_S_BLOCK_TYPE_BIT_MASK (0x3F)

/* ����ʼ���С */
#define     USIMM_T1_PROLOGUE_FIELD_SIZE            (3)

/* �����������С */
#define     USIMM_T1_EPILOGUE_FIELD_MAX_SIZE        (USIMM_T1_CRC_SIZE)

/* �������С */
#define     USIMM_T1_BLOCK_MAX_SIZE                 (USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_EPILOGUE_FIELD_MAX_SIZE)

/* PROLOGUE FIELD ��NAD/PCB/LEN����ֽ�ƫ�� */
#define     T1_NAD                                  (0)
#define     T1_PCB                                  (1)
#define     T1_LEN                                  (2)

/* ������Ϣ����ʼ�ֽ� */
#define     T1_INFO_START_BYTE                      (3)

/* T1 CASE1��APDU���� */
#define     T1_CASE1_APDU_LEN                       (4)

/* T1�п����ص�״̬�ֳ��� */
#define     T1_CARD_SW_LEN                          (2)

/* T1�н�������buf��С,data+sw,�ݶ�Ϊ260�ֽ� */
#define     USIMM_T1_RCV_BUF_SIZE                   (260)

/* Le�ֶ����ֵ */
#define     USIMM_LE_MAX_LEN                        (0xFF)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ö����    : USIMM_T1_BLOCK_TYPE_ENUM_UINT32
 �ṹ˵��  : T=1Э���п�����ö�ٶ���
*****************************************************************************/
enum USIMM_T1_BLOCK_TYPE_ENUM
{
    USIMM_T1_BLOCK_TYPE_I,              /* information block�����ڷ���Ӧ�ò���Ϣ���ݣ�PCB�ֽ�bit8Ϊ0��ʾI-BLOCK */
    USIMM_T1_BLOCK_TYPE_R       = 0x80, /* receive ready block������Ӧ��PCB bit8bit7Ϊ10��ʾR-BLOCK������Ϣ�� */
    USIMM_T1_BLOCK_TYPE_S       = 0xC0, /* supervisory block, ���ڷ��Ϳ�����Ϣ��PCB bit8bit7Ϊ11��ʾS-BLOCK*/
    USIMM_T1_BLOCK_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_T1_BLOCK_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32
 �ṹ˵��  : T=1Э����I���Ϳ��PCB�ֽ��У�more data bit��ȡֵö�ٶ���
*****************************************************************************/
enum USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM
{
    USIMM_T1_I_BLOCK_WITHOUT_MORE_DATA,              /* û���¸����飬MORE DATA BIT Ϊ0*/
    USIMM_T1_I_BLOCK_WITH_MORE_DATA,                 /* �����¸����飬MORE DATA BIT Ϊ1*/
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_BUTT
};
typedef VOS_UINT32      USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32
 �ṹ˵��  : T=1Э����S���Ϳ������Ͷ���
*****************************************************************************/
enum USIMM_T1_S_BLOCK_TYPE_ENUM
{
    USIMM_T1_S_BLOCK_RESYNCH_REQ        = 0xC0, /* ���ڷ�����ͬ������Ŀǰֻ����UE������������Ϣ�� */
    USIMM_T1_S_BLOCK_RESYNCH_RES        = 0xE0,
    USIMM_T1_S_BLOCK_IFS_REQ            = 0xC1, /* ����Э����Ϣ���С����Ϣ��Ϊһ���ֽ� */
    USIMM_T1_S_BLOCK_IFS_RES            = 0xE1,
    USIMM_T1_S_BLOCK_ABORT_REQ          = 0xC2, /* ������ֹ���鴫�䣬����UE���ɷ��� */
    USIMM_T1_S_BLOCK_ABORT_RES          = 0xE2,
    USIMM_T1_S_BLOCK_WTX_REQ            = 0xC3, /* ���ڿ������ն˶�ȴ�N��BWT�������ݣ�ֻ���ɿ�����UE����Ϣ��Ϊһ���ֽ� */
    USIMM_T1_S_BLOCK_WTX_RES            = 0xE3,
    USIMM_T1_S_BLOCK_ERR_VPP_STATE      = 0xE4, /* ����ָʾ�����VPP״̬��Ŀǰδʹ�� */
    USIMM_T1_S_BLOCK_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM
 �ṹ˵��  : T=1Э���п������У������ö��
*****************************************************************************/
enum USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM
{
    USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC   = 0, /* ����������һ�ֽ�LRCУ�� */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_CRC   = 1, /* �������������ֽ�CRCУ�� */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_BUTT
};

typedef VOS_UINT32      USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_PROC_STATE_ENUM
 �ṹ˵��  : T=1 ����״̬ö��
*****************************************************************************/
enum USIMM_T1_PROC_STATE_ENUM
{
    USIMM_T1_PROC_STATE_IDLE,                               /* ��ǰδ�����κ����� */
    USIMM_T1_PROC_STATE_SENT_APDU,                          /* ��ǰ�����˵���APDU */
    USIMM_T1_PROC_STATE_SENT_CHAIN_APDU,                    /* ��ǰ����������APDU */
    USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ,                   /* ��ǰ������S BLOCK(request)*/
    USIMM_T1_PROC_STATE_BUTT
};

typedef VOS_UINT32      USIMM_T1_PROC_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1DL_HANDLE_STATE_ENUM
 �ṹ˵��  : T=1 ���״̬��ö��
*****************************************************************************/
enum USIMM_T1DL_HANDLE_STATE_ENUM
{
    USIMM_T1DL_HANDLE_STATE_IDLE,                           /* ��ǰδ���κ��� */
    USIMM_T1DL_HANDLE_STATE_SEND_IFS,                       /* ��ǰ����IFS REQ */
    USIMM_T1DL_HANDLE_STATE_SEND_INFO,                      /* ��ǰ����ҵ������ */
    USIMM_T1DL_HANDLE_STATE_RCV_BLOCK,                      /* ��ǰ�������ݿ� */
    USIMM_T1DL_HANDLE_STATE_BUTT
};

typedef VOS_UINT32      USIMM_T1DL_HANDLE_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_R_BLOCK_ERRCODE_ENUM
 �ṹ˵��  : T=1 R BLOCK ��������ö��
*****************************************************************************/
enum USIMM_T1_R_BLOCK_ERRCODE_ENUM
{
    USIMM_T1_R_BLOCK_ERROR_FREE         = 0, /* denote an error-free acknowledgement */
    USIMM_T1_R_BLOCK_REDUNDANCY_ERR     = 1, /* indicate a redundancy code error or a character parity error */
    USIMM_T1_R_BLOCK_OTHER_ERR          = 2, /* indicate other error */
    USIMM_T1_R_BLOCK_ERRCODE_BUTT
};

typedef VOS_UINT32      USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : USIMM_T1_PROLOGUE_FIELD_STRU
 �ṹ˵��  : T=1����ʼ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNAD;    /* Node address byte, bit1-bit3:SAD; bit5-bit7:DAD */
    VOS_UINT8       ucPCB;    /* Protocol control byte */
    VOS_UINT8       ucLen;    /* �����ֽڣ�ָʾ������Ϣ�򳤶� */
    VOS_UINT8       ucRsv;    /* ���� */
}USIMM_T1_PROLOGUE_FIELD_STRU;

typedef VOS_UINT32 (*PUSIMMT1DLRECVBLKPROC)(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData);

/*****************************************************************************
 �ṹ��    : USIMMT1DL_RECV_FUNC_STATUS
 �ṹ˵��  : T=1���տ鴦��
*****************************************************************************/
typedef struct
{
    USIMM_T1_PROC_STATE_ENUM_UINT32     enStateId;          /* ״̬ID */
    PUSIMMT1DLRECVBLKPROC               pProcFun;           /* ������ */
}USIMMT1DL_RECV_FUNC_STATUS;

typedef VOS_UINT32 (*PUSIMMT1DLHANDLEPROC)(USIMM_APDU_ST* pstAPDUData);

/*****************************************************************************
 �ṹ��    : USIMMT1DL_HANDLE_FUNC_STATUS
 �ṹ˵��  : T=1���״̬������
*****************************************************************************/
typedef struct
{
    USIMM_T1DL_HANDLE_STATE_ENUM_UINT32 enStateId;          /* ״̬ID */
    PUSIMMT1DLHANDLEPROC                pProcFun;           /* ������ */
}USIMMT1DL_HANDLE_FUNC_STATUS;

/*****************************************************************************
 �ṹ��    : USIMM_T1_I_BLOCK_PCB_PARA_STRU
 �ṹ˵��  : T=1 I BLOCK�����ṹ�壬���ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulSeqNum;           /* I BLOCK��� */
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32              enMoreBit;          /* I BLOCK more data ָʾ */
}USIMM_T1_I_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_R_BLOCK_PCB_PARA_STRU
 �ṹ˵��  : T=1 R BLOCK�����ṹ�壬���ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulSeqNum;           /* R BLOCK��� */
    USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32                    enErrcode;          /* R BLOCK������ָʾ */
}USIMM_T1_R_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_S_BLOCK_PCB_PARA_STRU
 �ṹ˵��  : T=1 S BLOCK�����ṹ�壬���ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef struct
{
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32                       enSBlkType;         /* S BLOCK���� */
}USIMM_T1_S_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_BLOCK_PARA_UNION
 �ṹ˵��  : T=1 ���ֿ����͸��Բ����ṹ�����壬���ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef union
{
    USIMM_T1_I_BLOCK_PCB_PARA_STRU      stIBlockPara;       /*I BLOCK�����ṹ */
    USIMM_T1_R_BLOCK_PCB_PARA_STRU      stRBlockPara;       /*R BLOCK�����ṹ */
    USIMM_T1_S_BLOCK_PCB_PARA_STRU      stSBlockPara;       /*S BLOCK�����ṹ */
}USIMM_T1_BLOCK_PARA_UNION;

/*****************************************************************************
 �ṹ��    : USIMM_T1_BLOCK_PARA_STRU
 �ṹ˵��  : T=1������ṹ�����ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef struct
{
    USIMM_T1_BLOCK_TYPE_ENUM_UINT32     enBlockType;        /* ������ */
    USIMM_T1_BLOCK_PARA_UNION           uBlockPara;         /* ����Ӧ���Ͷ�Ӧ�Ĳ����ṹ�� */
}USIMM_T1_BLOCK_PARA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_S_BLOCK_STRU
 �ṹ˵��  : T=1������ṹ�����ڽ����յ��Ŀ���Ӧ����
*****************************************************************************/
typedef struct
{
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType;         /* S BLOCK���� */
    VOS_UINT8                           ucLen;              /* S BLOCK����Ϣ�����ݳ��� */
    VOS_UINT8                           ucData;             /* S BLOCK����Ϣ������ */
    VOS_UINT16                          usRsv;              /* �����ֽ� */
}USIMM_T1_S_BLOCK_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_CTRL_CTX_STRU
 �ṹ˵��  : T=1Э��Ŀ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIFSC;             /* IFSC */
    VOS_UINT32                                              ulIFSD;             /* IFSD */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enErrDetectMode;    /* CRC��LRC */
    VOS_UINT32                                              ulBWTTimes;         /* BWT���� */
    USIMM_T1_S_BLOCK_STRU                                   stSBlkPara;         /* ������S BLOCK�Ľṹ */
    USIMM_T1DL_HANDLE_STATE_ENUM_UINT32                     enT1HandleState;    /* T=1һ��״̬�� */
    USIMM_T1_PROC_STATE_ENUM_UINT32                         enT1ProcState;      /* T=1����մ���״̬�� */
    VOS_UINT32                                              ulUESeqNum;         /* UE��һ�η�������I BLOCK��� */
    VOS_UINT32                                              ulUICCSeqNum;       /* UE�����ӿ��յ������ */
    VOS_UINT32                                              ulRcvBlkChainFlg;   /* �յ�����ı��: VOS_TRUE-�յ�����, VOS_FALSE-δ�յ����� */
    VOS_UINT32                                              ulSendBlkChainFlg;  /* ��������ı��: VOS_TRUE-��������, VOS_FALSE-δ�������� */
    VOS_UINT32                                              ulUnexpectCount;    /* �յ�������Ԥ�ڿ������ */
}USIMM_T1_CTRL_CTX_STRU;


/*****************************************************************************
 �ṹ��    : USIMM_T1_SEND_DATA_STRU
 �ṹ˵��  : T=1���ݷ��ͽṹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucInfoData[USIMM_APDU_HEADLEN+USIMM_APDU_MAXLEN];          /* ������������ */
    VOS_UINT8       aucRsv[3];                                                  /* �����ֽ� */
    VOS_UINT32      ulTotalLen;                                                 /* �����������ݳ��� */
    VOS_UINT8      *pucLastInfoData;                                            /* �ѷ�������ָ�� */
    VOS_UINT32      ulLastTotalLen;                                             /* �ѷ������ݳ����ܳ��� */
    VOS_UINT32      ulLastLen;                                                  /* �ϸ���Ƭ�������ݳ��� */
}USIMM_T1_SEND_DATA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_RCV_DATA_STRU
 �ṹ˵��  : T=1���ݽ��սṹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucInfoData[USIMM_T1_RCV_BUF_SIZE];     /* ���տ�����Ϣ�����ݣ�data+sw */
    VOS_UINT32      ulDataLen;                              /* ������Ϣ�����ݳ��� */
}USIMM_T1_RCV_DATA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_DL_T1_PARA_STRU
 �ṹ˵��  : T=1�����ṹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIFSC;             /* IFSC */
    VOS_UINT32                                              ulIFSD;             /* IFSD */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enErrDetectMode;    /* CRC��LRC */
}USIMM_DL_T1_PARA_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_T1_STATISTIC_STRU
 �ṹ˵��  : T=1��ά�ɲ�ͳ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulSndIBlkSuccCnt;                       /* ����I-Block�ɹ�����ͳ�� */
    VOS_UINT32      ulSndIBlkFailCnt;                       /* ����I-Blockʧ�ܴ���ͳ�� */

    VOS_UINT32      ulSndRBlkSuccCnt;                       /* ����R-Block�ɹ�����ͳ�� */
    VOS_UINT32      ulSndRBlkFailCnt;                       /* ����R-Blockʧ�ܴ���ͳ�� */

    VOS_UINT32      ulSndSBlkResynchReqSuccCnt;             /* ����S-Block(RESYNCH Request)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkResynchReqFailCnt;             /* ����S-Block(RESYNCH Request)ʧ�ܴ���ͳ�� */
    VOS_UINT32      ulSndSBlkIFSReqSuccCnt;                 /* ����S-Block(IFS Request)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkIFSReqFailCnt;                 /* ����S-Block(IFS Request)ʧ�ܴ���ͳ�� */
    VOS_UINT32      ulSndSBlkIFSRspSuccCnt;                 /* ����S-Block(IFS Response)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkIFSRspFailCnt;                 /* ����S-Block(IFS Response)ʧ�ܴ���ͳ�� */
    VOS_UINT32      ulSndSBlkAbortReqSuccCnt;               /* ����S-Block(ABORT Request)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkAbortReqFailCnt;               /* ����S-Block(ABORT Request)ʧ�ܴ���ͳ�� */
    VOS_UINT32      ulSndSBlkAbortRspSuccCnt;               /* ����S-Block(ABORT Response)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkAbortRspFailCnt;               /* ����S-Block(ABORT Response)ʧ�ܴ���ͳ�� */
    VOS_UINT32      ulSndSBlkWTXRspSuccCnt;                 /* ����S-Block(WTX Response)�ɹ�����ͳ�� */
    VOS_UINT32      ulSndSBlkWTXRspFailCnt;                 /* ����S-Block(WTX Response)ʧ�ܴ���ͳ�� */

    VOS_UINT32      ulRcvNADErrBlkCnt;                      /* ���յ�NAD������Block����ͳ�� */
    VOS_UINT32      ulRcvBlkSizeAbnormalBlkCnt;             /* ���յ������쳣(С��������С�鳤�Ȼ�����������鳤��)��Block����ͳ�� */
    VOS_UINT32      ulRcvBlkSizeErrBlkCnt;                  /* ���յ����ȴ���(ͷ+LEN+EDC���Ȳ����ڽ��յ����ܳ���)��Block����ͳ�� */
    VOS_UINT32      ulRcvEDCErrBlkCnt;                      /* ���յ�EDC������Block����ͳ�� */
    VOS_UINT32      ulRcvMoreThanIFSDErrBlkCnt;             /* ���յ���Ϣ�򳬹�IFSD��Block����ͳ�� */

    VOS_UINT32      ulRcvInvalidLenRBlkCnt;                 /* ���յ�LEN���Ȳ�Ϊ0��R-Block����ͳ�� */
    VOS_UINT32      ulRcvInvalidBit6OfPCBRBlkCnt;           /* ���յ�PCB��bit 6��Ϊ0��R-Block����ͳ�� */
    VOS_UINT32      ulRcvTriggerResendRBlkCnt;              /* ���յ�����UE�ط���R-Block����ͳ�� */
    VOS_UINT32      ulRcvAbnormalRBlkCnt;                   /* ���յ�������Э�������߼���R-Block����ͳ�� */

    VOS_UINT32      ulRcvAbnormalIBlkCnt;                   /* ���յ�������Э�������߼���I-Block����ͳ�� */

    VOS_UINT32      ulRcvInvalidLenSBlkCnt;                 /* ���յ�LEN���Ȳ�����Э���߼�(��WTX REQ��LEN!=1)��S-Block����ͳ�� */
    VOS_UINT32      ulRcvInvalidTypeSBlkCnt;                /* ���յ�Type������Э���߼���S-Block����ͳ�� */
    VOS_UINT32      ulRcvAbnormalSBlkCnt;                   /* ���յ�������Э�������߼���S-Block����ͳ�� */

    VOS_UINT32      ulDeactCardCnt;                         /* ȥ�������ͳ�� */
    VOS_UINT32      ulSetBWTFailCnt;                        /* ���õ���ӿ�����BWTʧ�ܴ���ͳ�� */
    VOS_UINT32      ulProtocolSwitchFailCnt;                /* ���õ���ӿڽ���T=0��T=1Э�������л�ʧ�ܴ���ͳ�� */
}USIMM_T1_STATISTIC_STRU;


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern USIMM_T1_STATISTIC_STRU         g_stT1StatisticInfo;

extern USIMM_DL_T1_PARA_STRU           g_stUSIMMT1Para;

extern USIMM_T1_CTRL_CTX_STRU          g_stUsimmT1CtrlCtx;

/* T=1 ���ݷ�����Ϣ�ṹ  */
extern USIMM_T1_SEND_DATA_STRU         g_stT1SendDataInfo;

/* T=1 ���ݽ�����Ϣ�ṹ  */
extern USIMM_T1_RCV_DATA_STRU          g_stT1RcvDataInfo;

/*****************************************************************************
  6 OTHERS����
*****************************************************************************/
extern VOS_UINT32 USIMM_T1DLUpdateParaByATR(USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32 enEDCType, VOS_UINT32 ulIFSC, VOS_UINT32 ulIFSD);

extern VOS_UINT32 USIMM_T1DLHandle(USIMM_APDU_ST* pstAPDUData);

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

#endif /* end of usimmt1dl.h*/

