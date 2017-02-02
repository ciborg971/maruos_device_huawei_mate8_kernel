/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : omnosig.h
  �� �� ��   : ����
  ��    ��   : ����47350
  ��������   : 2011��9��27��

  ����޸�   :
  ��������   : omnosig.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��9��27��
    ��    ��   : ����47350
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OM_NOSIG_H__
#define __OM_NOSIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "omprivate.h"
#include "cbtrl.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SHL1(x)                         (x | (1<<16))
#define SHL2(x)                         (x | (2<<16))
#define CBT_INDEXNOEXIT                 (0xFFFF)
#define CBT_CHAN_MAX_SEGMENT_COUNT      (10)
#define CBT_GE_MAX_BAND_SUPPORT         (4)


#define OM_FRAME_NUM_REG_MASKBIT                      (0x7FF)

/* ��ȡ�Ĵ�������ʱ���� */
#define OM_EDGE_BLER_TASK_DELAY         (2000)

/* �ȴ�DSP�ظ��ĳ�ʱ���� */
#define OM_NOSIG_WAIT_TIME_LEN          (5000)

/* ���֡��*/
#define OM_FRAME_MAX_NUM                (2715648)

/*�Ĵ�����λ��Ӧ֡��*/
#define OM_HIHG_ADDR_FRAME_NUM                        (1326)

/*�·���Ϣ��Ӧ����ʱ��*/
#define OM_DL_MSG_FRAME_NUM                           (50)

/*��������������ݳ��ȣ�������32λ����ʾ */
#define OM_R99_MAILBOX_MAX_PHY_DATA_IND_LEN           ((328)*4)

/*���д����ŵ�����*/
#define OM_UL_TRANS_CHANNEL_NUM                       (2)

/*R99 ������������*/
#define OM_R99_DECODE_BUF_INDEX_INIT                  (0x0)
#define OM_R99_DECODE_BUF_INDEX_FIRST                 (0x1)
#define OM_R99_DECODE_BUF_INDEX_SECOND                (0x2)

#define OM_OFFSET_OF(s, m) ((VOS_SIZE_T)&(((s *)0)->m))


typedef VOS_UINT32 (* CBT_PFNTRANSMSG)(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_GE_DL_MODE
{
    OM_GE_DL_MODE_GSM,
    OM_GE_DL_MODE_EDGE,
    OM_GE_DL_MODE_BUTT
};

typedef VOS_UINT32 OM_GE_DL_MODE_ENUM_UINT32;

enum OM_R99_MAILBOX_MUTEX_ENUM
{
    OM_R99_MAILBOX_MUTEX_DATA_NOT_EXIST             = 0,        /* ��������������ݣ�  ��д�����ɶ�;*/
    OM_R99_MAILBOX_MUTEX_DATA_EXIST                 = 1,        /* ��������������ݣ�����д��  �ɶ�;*/
    OM_R99_MAILBOX_MUTEX_BUTT
};

typedef VOS_UINT16 OM_R99_MAILBOX_MUTEX_ENUM_UINT16;


typedef enum
{
    CBT_STATE_INIT     = 0,
    CBT_STATE_LOOPBACK,
    CBT_STATE_TEST,
    CBT_STATE_HANDOVER
}CBT_LIST_MODE_STATE_ENUM;

typedef enum
{
    CBT_ACTION_CALL     = 0,
    CBT_ACTION_HANDOVER,
    CBT_ACTION_PCLHANDOVER,
    CBT_ACTION_RELEASE,
    CBT_ACTION_BUTT
} CBT_ACTION_ENUM;

typedef enum
{
    CBT_TO_DSP = 0,
    DSP_TO_CBT,
    DIRECTION_BUTT
} CBT_DIRECTION_ENUM;

typedef VOS_UINT16 CBT_DIRECTION_ENUM_UINT16;

typedef enum
{
    CBT_CALL_ERROR      = 0xFFFF0001,
    CBT_HANDOVER_ERROR,
    CBT_RELEASE_ERROR,

    CBT_WAITTOTALFRAMES_ERROR,
    CBT_WAITTXFRAMES_ERROR,

    CBT_SETPOWER_ERROR,
    CBT_CHANCOUNT_ERROR
} CBT_LM_ERROR_CODE_ENUM;

typedef enum
{
    CBT_DATA_UMTS = 0,
    CBT_DATA_GSM,
    CBT_DATA_EDGE,
    CBT_DATA_BUTT
} CBT_DATA_DOMAIN_MODE_ENUM;


typedef enum
{
    W_TPC_DISENABLE,
    W_TPC_ENABLE
} CBT_W_TPC_CONTROL_ENUM;

typedef VOS_UINT16 CBT_W_TPC_CONTROL_ENUM_UINT16;
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

/*****************************************************************************
�ṹ��    : CBT_LIST_MODE_MSG_STRU
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulMsgId;
    VOS_UINT16                  usDataLen;
    VOS_UINT16                  usPosition;
} CBT_LIST_MODE_MSG_STRU;

/*****************************************************************************
�ṹ��    : CBT_CONVERT_MSG_STRU
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulMsgId;
    CBT_DIRECTION_ENUM_UINT16   enDirection;
    VOS_UINT16                  usRsv;
    CBT_PFNTRANSMSG             pfnCbtTrans;
} CBT_CONVERT_MSG_STRU;

/*****************************************************************************
�ṹ��    : CBT_GETMSG_CNF_STRU
�ṹ˵��  : list mode��Ҫ��msgid�ظ���Ϣ��ʽ
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulResult;
    VOS_UINT32  ulCount;
    VOS_UINT8   aucData[4];
} CBT_GETMSG_CNF_STRU;
/*****************************************************************************
�ṹ��    : CBT_GETMSG_CNF_STRU
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulMsgId;        /*��Ϣ���ͺ���ϢID*/
    VOS_UINT32      ulMsgLen;       /* ��Ϣ�ĳ��� */
    VOS_MSG_HEADER
} CBT_TRANS_MSG_HEAD_STRU;

/*****************************************************************************
�ṹ��    : CBT_POWER_CTRL_UNION
�ṹ˵��  :
*****************************************************************************/
typedef union
{
    VOS_UINT16      usGsmPcl;       /*Gsm���õ�PCL�ȼ�*/
    VOS_INT16       sWPower10th;    /*Wcdma���õ�����power*/
} CBT_POWER_CTRL_UNION;
/*****************************************************************************
�ṹ��    : CBT_LIST_MODE_SEGMENT_STRU
�ṹ˵��  : listmode һ��segment�����ݽṹ
*****************************************************************************/
typedef struct
{
    CBT_W_TPC_CONTROL_ENUM_UINT16   usEnableTpc;    /*W mode enable tpc control  1: enable, 0 disable*/
    VOS_UINT16                      usRsv;
    CBT_POWER_CTRL_UNION            unWgPowerCtrl;
    VOS_UINT16                      usTxFramCnt;

} CBT_LIST_MODE_SEGMENT_STRU;

/*****************************************************************************
�ṹ��    : CBT_LIST_MODE_CHAN_STRU
�ṹ˵��  : listmode һ���ŵ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulBand;
    VOS_UINT16                  usTxChan;
    VOS_UINT16                  usRxChan;

    VOS_UINT16                  usDurationFrameCnt;
    VOS_UINT16                  usReportFrameCnt;

    VOS_UINT32                  ulSegmentCount;
    CBT_LIST_MODE_SEGMENT_STRU  stSegment[CBT_CHAN_MAX_SEGMENT_COUNT];
} CBT_LIST_MODE_CHAN_STRU;

typedef struct
{
    VOS_UINT16              usEnableReport;  /* �Ƿ�ʹ����Ϣ�ϱ�,0���ϱ���1�ϱ� */
    VOS_UINT16              usRcvMsgPrimId;  /* �ȴ���ϢID */
    VOS_UINT16              usSyncStatus;    /* ����Wͬ��״̬ */
    CBT_MODEM_SSID_STRU     stModemSsid;       /* Modem */
    VOS_UINT8               ucReserve;       /* ������ */
    CBT_COMPONENT_MODE_STRU stCompMode;        /* ���ID */
    VOS_UINT16              usRsv2;
    VOS_SEM                 ulNoSigSyncSem;  /* ���еȴ���Ϣͬ���ź��� */
    VOS_UINT32              ulTotalFrameNum; /* �ϱ���BER��֡�� */
    VOS_UINT32              ulCurFrameNum;   /* �ϱ���BER��ǰ֡�� */
}OM_NOSIG_CTRL_STRU;

/*****************************************************************************
�ṹ��    : CBT_LISTMODE_MSG_CONTEXT_REQ_STRU
�ṹ˵��  : listmode������Ϣ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usMode;
    VOS_UINT16                  usRsv;
    VOS_UINT32                  ulMsgCount;
    VOS_UINT8                   aucData[4];
} CBT_LISTMODE_MSG_CONTEXT_REQ_STRU;

/*****************************************************************************
�ṹ��    : CBT_LISTMODE_BEGIN_PROC_STRU
�ṹ˵��  : listmode��ʼ����req��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usEnableReport;
    VOS_UINT16                  usMode;
    VOS_UINT32                  ulChanCount;
    VOS_UINT8                   aucData[4];
} CBT_LISTMODE_TEST_PROC_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;   /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT32                  ulFirstErrNum;
    VOS_UINT32                  ulFirstTotalNum;
    VOS_UINT32                  ulSecondErrNum;
    VOS_UINT32                  ulSecondTotalNum;
}CBT_EDGE_BLER_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;    /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT16                  usModeType;  /*1:GSM 2: EDGE*/
    VOS_UINT16                  usReverse2;  /*Not used now.*/
}CBT_GE_DL_STATUS_REQ_STRU;

typedef struct
{
    VOS_UINT16  usNsMsgType;    /* VOS_FALSE:�·���Ϣ, VOS_TRUE:�ȴ�CNF����IND��Ϣ */
    VOS_UINT16  usNsMsgLen;     /* ��Ϣ�ĳ��� */
    VOS_UINT16  usRcvMsgPrimId; /* ������Ϣ��IDֵ */
    VOS_UINT16  usReserve;      /* ���� */
}OM_NOSIG_MSG_HEAD_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;   /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT16                  usFrameNum;
    VOS_UINT16                  usReserve;
}CBT_WC_BER_DATA_REQ_STRU;

typedef struct
{
    UINT16                      usEnableTpc;
    INT16                       sDedicatePower; /* ��λ 0.125 dBm*/
}CBT_C_SET_POWER_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU       stHeader;
    VOS_UINT16              usPrimId;            /*Indicates current msg type.*/
    VOS_UINT16              usToolId;            /*Not used now.*/
    VOS_UINT32              ulMsgLength;
    VOS_UINT16              usTotalFrameNum;
    VOS_UINT16              usCurFrameNum;
    VOS_UINT32              ulDataLen;           /* ���ݳ���,��λ:�ֽ�,����ֵ����4��������,��Χ[0..WTTFPHY_MAX_PHY_DATA_REQ_LEN-1] */
    VOS_UINT8               aucData[OM_BER_DATA_MAX_SIZE]; /* �������ݿ� */
}CBT_W_BER_DATA_IND_STRU;

/*����С����Ϣ�ṹ*/
typedef struct
{
   VOS_UINT16       usPrimaryScramCode;
   VOS_UINT16       usReferenceTime;
}CANDIDATE_CELL_STRU;

/*Ƶ����Ϣ�ṹ��*/
typedef struct
{
    VOS_UINT16      usLowFreq;
    VOS_UINT16      usHighFreq;
}FREQ_BAND_STRU;

/*Ƶ����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT16      usFreqBandNo;
    VOS_UINT16      usTxRxFreqSepatation;
    VOS_UINT16      usDLFreqInfo;
    VOS_UINT16      usReserve;
}FREQ_INFO_STRU;

/*Ƶ���б�ṹ*/
typedef struct
{
    VOS_UINT16          usFreqCnt;
    VOS_UINT16          usReserve;
    FREQ_INFO_STRU      astFreqList[20];
    VOS_UINT16          usTxRxFreqSeparation;
    VOS_UINT16          usFreqBandNo;
    VOS_UINT16          usReportCellNumInd;  /*�ϱ�С���ĸ���*/
    VOS_UINT16          usReserve1;
}FREQ_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16  usMsgId;
    VOS_UINT16  usOpId;
    VOS_UINT16  usCellSearchType;
    VOS_UINT16  usFreqInfo;
    VOS_INT16   sRSCPThreshold;
    VOS_UINT16  usCandidateCellNumm;

    CANDIDATE_CELL_STRU   astCandidateCell[64]; /*����С����Ϣ*/
    FREQ_BAND_STRU        stFreqBand;
    FREQ_LIST_STRU        stFreqList;
}CELL_SEARCHING_REQ_STRU;

/*DownLink Info*/
typedef struct
{
    VOS_UINT16   usSecScramCode;      /*��2���룬 0��ʾû��*/
    VOS_INT16    sOvsfCodeNum;        /*��Ƶ��*/
    VOS_UINT16   usReserve;
    VOS_UINT16   usScrambCodeChange;  /*����ı��ʾ��1-nochange*/
}DOWN_LINK_INFO_STRU;

/*Compress MODE TGPS INFO*/
typedef struct
{
   VOS_UINT16   usTgpsi;
   VOS_UINT16   usTgpStausFlag;
   VOS_INT16    sTgcfn;
   VOS_UINT16   usReserve;
   VOS_INT16    sTgrc;
   VOS_INT16    usTgmp;
   VOS_UINT16   usTgsn;
   VOS_UINT16   usTgL1;
   VOS_UINT16   usTgL2;
   VOS_INT16    sTgd;
   VOS_UINT16   usTGPL1;
   VOS_UINT16   usTGPL2;
   VOS_UINT16   usRpp;
   VOS_UINT16   usITP;
   VOS_UINT16   usDLFrameType;
   VOS_UINT16   usDeltaSIR1;
   VOS_UINT16   usDelatSIRafter1;
   VOS_UINT16   usDeltaSIR2;
   VOS_UINT16   usDelatSIRafter2;
   VOS_UINT16   usNIdentifyabort;
   VOS_UINT16   usTReconfirmabort;
   VOS_UINT16   usReserve1;
   VOS_UINT16   usULMethod;
   VOS_UINT16   usReserve2;
}COMPRESS_MODE_TGPS_INFO_STRU;

/*Compress mode*/
typedef struct
{
    VOS_UINT16   usTGPSCnt;
    VOS_UINT16   usReserve;
    COMPRESS_MODE_TGPS_INFO_STRU stCompressModeTgpsInfo[6];

}COMPRESS_MODE_STRU;

/*RL�����ṹ*/
typedef struct
{
    VOS_UINT16   usPhyType;            /*�����ŵ����� 2 dldpch*/
    VOS_INT16    sActiveTime;          /*-1�����·�*/
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usSlotFormat;         /*ʱ϶��ʽ������Ĭ�ϵ���11*/
    VOS_UINT16   usDpchFrameOffset;    /*֡ƫ�ƣ�Ĭ����0*/
    VOS_UINT16   usTdIndicator;
    VOS_UINT16   usDpchChanNum;        /*DPCH��ʽ,1��*/
    VOS_UINT16   usDownLinkScramCode;  /*���� 9*/
    DOWN_LINK_INFO_STRU  stDownLinkInfo;
    VOS_UINT16   usDpcMode;            /*���й��ʿ���ģʽ  1-singel*/
    VOS_UINT16   usTpcCombIndex;       /*TPC��ϵ���������������[0,5];*/
    VOS_UINT16   usTimingIndication;   /*Ӳ�л���ʱָʾ��4-��Ӳ�л�*/
    VOS_INT16    sCfnSfnOffset;

    COMPRESS_MODE_STRU stCompressMode;
    VOS_UINT16   usNeedSyncAInd;
    VOS_UINT16   usPcpichTDIndicator;
    VOS_UINT16   usBlindHhoFlag;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
    VOS_UINT16   usSecndCpichValidInd;

    VOS_UINT16   usSecondDlScramblCode;
    VOS_UINT16   usOvsfCodeNum;
    VOS_UINT16   usPo2;
    VOS_UINT16   usPo3;
}RL_PARA_STRU;

typedef struct
{
    VOS_UINT16   usPhyType;            /*�����ŵ����� 2 dldpch*/
    VOS_INT16    sActiveTime;
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usSlotFormat;         /*ʱ϶��ʽ������Ĭ�ϵ���11*/
    VOS_UINT16   usDpchFrameOffset;
    VOS_UINT16   usTdIndicator;
    VOS_UINT16   usDpchChanNum;
    VOS_UINT16   usDownLinkScramCode;  /*���� 9*/
    DOWN_LINK_INFO_STRU  stDownLinkInfo;
    VOS_UINT16   usDpcMode;            /*���й��ʿ���ģʽ  1-singel*/
    VOS_UINT16   usTpcCombIndex;       /*TPC��ϵ���������������[0,5];*/
    VOS_UINT16   usTimingIndication;   /*Ӳ�л���ʱָʾ��4-��Ӳ�л�*/
    VOS_INT16    sCfnSfnOffset;

    COMPRESS_MODE_STRU stCompressMode;
    /*V3R2��V3R1��ͬ(usNeedSyncAInd)*/
    VOS_UINT16   usRsv;
    VOS_UINT16   usNeedSync;
    VOS_UINT16   usPostVerification;

    VOS_UINT16   usPcpichTDIndicator;
    VOS_UINT16   usBlindHhoFlag;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
    VOS_UINT16   usSecndCpichValidInd;

    VOS_UINT16   usSecondDlScramblCode;
    VOS_UINT16   usOvsfCodeNum;
    VOS_UINT16   usPo2;
    VOS_UINT16   usPo3;

    VOS_UINT16   usSuncDetect;
    VOS_UINT16   usT312;
    VOS_UINT16   usN312;
    VOS_UINT16   usT313;
    VOS_UINT16   usN313;
    VOS_UINT16   usN315;
    VOS_UINT16   usDisableUlDcchTimer;
    VOS_UINT16   usResumeUlDcchTimer;
}CBT_V3R2_RL_PARA1_STRU;

typedef struct
{
    VOS_UINT16   usPhyType;            /*�����ŵ����� 2 dldpch*/

    VOS_INT16    sActivateTime;
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usScramCodeType;
    VOS_UINT32   ulScramCodeNum;

    VOS_INT16    sDpchInitialTxPower;
    VOS_UINT16   usPcPreamble;
    VOS_UINT16   usPowerControlAlgorithm;
    VOS_UINT16   usTpcStepSize;
    VOS_INT16    sUlDpchPowerOffset;
    VOS_UINT16   usBlindHhoFlag;

    VOS_UINT16   usDpchNum;
    VOS_UINT16   usSlotFormat;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
}CBT_V3R2_RL_PARA2_STRU;

/*������DL dpch REQ*/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16              usPrimId;
    VOS_UINT16              usOpId;
    VOS_UINT16              usPhyChannelNum;    /*�����ŵ�����*/
    VOS_UINT16              usParaSize;         /*��Ϣ����*/
    CBT_V3R2_RL_PARA1_STRU  stRlPara1;
    CBT_V3R2_RL_PARA2_STRU  stRlPara2;
}RL_SETUP_DL_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16  usPrimId;
    VOS_UINT16  usFreqBand;
    VOS_UINT16  usFreqNum;
    VOS_UINT16  usFreqInfo[67];
}EVT_MPH_RXLEV_REQ_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 CBT_WCellSearchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_WCampedMainCellFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_WRlSetUpDldpchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);

VOS_UINT32 CBT_GeRxLevReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStartBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStopBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeImmedAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeChannelAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStopDedicatedReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);

VOS_UINT32 CBT_GeSiUpdateReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeDlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeUlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);


VOS_UINT32 CBT_GetListModeMsgID(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_ListModeMsgContext(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_ListModeTestProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_CSyncStatusProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_CFrameErrorRate(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 CBT_CSetPower(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
#endif

VOS_VOID   CBT_FramesStatistics(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID   CBT_CLoopTestProc(VOS_VOID);

#endif

VOS_UINT32 OM_BtTransProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_WSyncStatusProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_EdgeBlerProc (CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_GeDlStatusProc (CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_BerConfigProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_VOID   OM_LoopTestProc(VOS_VOID);


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

#endif /* end of omnosig.h */

