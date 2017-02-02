

#ifndef __RRCRLCINTERFACE_H__
#define __RRCRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* WCDMAЭ��ջ������ϵͳ���������ݽṹ */
#include "PsTypeDef.h"
#include "WUe.h"
#include "WUeL2L3.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣ���Ͷ���
*****************************************************************************/
enum RRC_RLC_MSG_TYPE_ENUM
{
    ID_RRC_RLC_AM_DATA_REQ              =  0x0000,      /* _H2ASN_MsgChoice RRC_RLC_AM_DATA_REQ_STRU */
    ID_RLC_RRC_AM_DATA_CNF              =  0x0001,      /* _H2ASN_MsgChoice RLC_RRC_AM_DATA_CNF_STRU */
    ID_RRC_RLC_UM_DATA_REQ              =  0x0002,      /* _H2ASN_MsgChoice RRC_RLC_UM_DATA_REQ_STRU */
    ID_RLC_RRC_AM_DATA_IND              =  0x0003,      /* _H2ASN_MsgChoice RLC_RRC_AM_DATA_IND_STRU */
    ID_RRC_RLC_TM_DATA_REQ              =  0x0004,      /* _H2ASN_MsgChoice RRC_RLC_TM_DATA_REQ_STRU */
    ID_RLC_RRC_UM_DATA_IND              =  0x0005,      /* _H2ASN_MsgChoice RLC_RRC_UM_DATA_IND_STRU */
    ID_RRC_RLC_AM_CONFIG_REQ            =  0x0006,      /* _H2ASN_MsgChoice RRC_RLC_AM_CONFIG_REQ_STRU */
    ID_RLC_RRC_TM_DATA_IND              =  0x0007,      /* _H2ASN_MsgChoice RLC_RRC_TM_DATA_IND_STRU */
    ID_RRC_RLC_UM_CONFIG_REQ            =  0x0008,      /* _H2ASN_MsgChoice RRC_RLC_UM_CONFIG_REQ_STRU */
    ID_RLC_RRC_CONFIG_CNF               =  0x0009,      /* _H2ASN_MsgChoice RLC_RRC_CONFIG_CNF_STRU */
    ID_RRC_RLC_TM_CONFIG_REQ            =  0x000a,      /* _H2ASN_MsgChoice RRC_RLC_TM_CONFIG_REQ_STRU */
    ID_RLC_RRC_RELEASE_CNF              =  0x000b,      /* _H2ASN_MsgChoice RLC_RRC_RELEASE_CNF_STRU */
    ID_RRC_RLC_RELEASE_REQ              =  0x000c,      /* _H2ASN_MsgChoice RRC_RLC_RELEASE_REQ_STRU */
    ID_RLC_RRC_SUSPEND_CNF              =  0x000d,      /* _H2ASN_MsgChoice RLC_RRC_SUSPEND_CNF_STRU */
    ID_RRC_RLC_SUSPEND_REQ              =  0x000e,      /* _H2ASN_MsgChoice RRC_RLC_SUSPEND_REQ_STRU */
    ID_RLC_RRC_RESUME_CNF               =  0x000f,      /* _H2ASN_MsgChoice RLC_RRC_RESUME_CNF_STRU */
    ID_RRC_RLC_RESUME_REQ               =  0x0010,      /* _H2ASN_MsgChoice RRC_RLC_RESUME_REQ_STRU */
    ID_RLC_RRC_STOP_CNF                 =  0x0011,      /* _H2ASN_MsgChoice RLC_RRC_STOP_CNF_STRU */
    ID_RRC_RLC_STOP_REQ                 =  0x0012,      /* _H2ASN_MsgChoice RRC_RLC_STOP_REQ_STRU */
    ID_RLC_RRC_CONTINUE_CNF             =  0x0013,      /* _H2ASN_MsgChoice RLC_RRC_CONTINUE_CNF_STRU */
    ID_RRC_RLC_CONTINUE_REQ             =  0x0014,      /* _H2ASN_MsgChoice RRC_RLC_CONTINUE_REQ_STRU */
    ID_RLC_RRC_STATUS_IND               =  0x0015,      /* _H2ASN_MsgChoice RLC_RRC_STATUS_IND_STRU */
    ID_RRC_RLC_MODE_CHANGE_REQ          =  0x0016,      /* _H2ASN_MsgChoice RRC_RLC_MODE_CHANGE_REQ_STRU */
    ID_RLC_RRC_ULDATA_TX_IND            =  0x0017,      /* _H2ASN_MsgChoice RLC_RRC_ULDATA_TX_IND_STRU */
    ID_RRC_RLC_CIPHER_CONFIG_REQ        =  0x0018,      /* _H2ASN_MsgChoice RRC_RLC_CIPHER_CONFIG_REQ_STRU */

    ID_RLC_RRC_MODE_CHANGE_CNF          =  0x0019,      /* _H2ASN_MsgChoice RLC_RRC_MODE_CHANGE_CNF_STRU */

    ID_RLC_RRC_CIPHER_CONFIG_CNF        =  0x001b,      /* _H2ASN_MsgChoice RLC_RRC_CIPHER_CONFIG_CNF_STRU */
    ID_RLC_RRC_CIPHERING_ACTIVE_IND     =  0x001d,      /* _H2ASN_MsgChoice RLC_RRC_CIPHER_ACTIVE_IND_STRU */
    ID_RLC_RRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RRC_RLC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ���CTCH���������RB ID����UM RLC�������ͷ�ʱʹ�� */
#define RLCITF_CTCH_RB_ID               33

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : RLCITF_DISCARD_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����SDU����ģʽ
*****************************************************************************/
enum RLCITF_DISCARD_MODE_ENUM
{
    RLCITF_TIMER_EXP                    = 0,            /* Timer based discard */
    RLCITF_MAXDAT_RETX                  = 1,            /* SDU discard after MaxDAT number of transmission */
    RLCITF_NO_DISCARD                   = 2,            /* No discard */
    RLCITF_DISCARD_MODE_BUTT
};
typedef VOS_UINT8 RLCITF_DISCARD_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RRC_RLC_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RLC_AM_CONFIG_REQԭ��������
*****************************************************************************/
enum RRC_RLC_CFG_MODE_ENUM
{
    RRC_RLC_CFG_MODE_SETUP              = 0,            /* ��AM/UM/TM RLCʵ��Ľ��� */
    RRC_RLC_CFG_MODE_REEST              = 1,            /* ��AM/UM    RLCʵ����ؽ� */
    RRC_RLC_CFG_MODE_MODIFY             = 2,            /* ��AM/UM/TM RLCʵ��������޸� */
    RRC_RLC_CFG_MODE_NO_CHANGE          = 3,            /* ��AM/UM/TM RLCʵ������ò��� */
    RRC_RLC_CFG_MODE_BUTT
} ;
typedef VOS_UINT8 RRC_RLC_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RLCITF_AM_REEST_SIDE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AMʵ���ؽ�������ָʾ
*****************************************************************************/
enum RLCITF_AM_REEST_SIDE_ENUM
{
    RLCITF_AM_TX_REEST                 = 0,             /* AMʵ�巢�Ͷ��ؽ� */
    RLCITF_AM_RX_REEST                 = 1,             /* AMʵ����ն��ؽ� */
    RLCITF_AM_BOTH_REEST               = 2,             /* AMʵ����ն�/���Ͷ��ؽ� */
    RLCITF_AM_REEST_BUTT
};
typedef VOS_UINT8 RLCITF_AM_REEST_SIDE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RLCITF_EVENT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�㷢����Ҫ�ϱ����¼����
*****************************************************************************/
enum RLCITF_EVENT_TYPE_ENUM
{
    RLCITF_EVENT_DATALINK_LOSS          = 0,            /* RLC�㷢��������·��ʧ�¼�                */
    RLCITF_EVENT_RESET                  = 1,            /* RLC�㷢��RESET�¼�                       */
    RLCITF_EVENT_UM_DECIPHER_ABNORMAL   = 2,            /* RLC�㷢������UM�����쳣�¼�                       */

    RLCITF_EVENT_BUTT
};
typedef VOS_UINT8 RLCITF_EVENT_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM SDU CRC Fail deliver methord
*****************************************************************************/
enum RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM
{
    RLC_TM_CRC_FAIL_SDU_NULL            =   0x000,      /*Ϊ����IT����ʱ����Ϣ�����Ӹ������������ */
    RLC_TM_CRC_FAIL_SDU_NO_DETECT       =   0x001,      /*�����SDU�Ƿ���ȷ*/
    RLC_TM_CRC_FAIL_SDU_DELIVER         =   0x010,      /*��⵽����ʱ��������SDU���͸��ϲ�*/
    RLC_TM_CRC_FAIL_SDU_NO_DELIVER      =   0x011,      /*��⵽����ʱ��ֱ�ӽ�SDU���� */
    RLC_TM_CRC_FAIL_BUTT
} ;
typedef VOS_UINT8 RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RLCITF_RSLT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC���ý��
*****************************************************************************/
enum RLCITF_RSLT_ENUM
{
    RLCITF_SUCC                         = 0,
    RLCITF_FAIL                            ,

    RLCITF_RSLT_BUTT
};
typedef VOS_UINT32   RLCITF_RSLT_ENUM_UINT32;

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
 �ṹ��    : RLCITF_POLL_INFO_STRU
 Э����  : 10.3.4.4 Polling info
 ASN.1���� : PollingInfo
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerPollProh;    /* Timer_Poll_Prohibit��ʱ����ֵ, Ϊ0ʱ��ʾδ���øö�ʱ�� 10..550 by step of 10; 600..1000 by step of 50; 0 */
    VOS_UINT16                          usTimerPoll;        /* Timer_Poll��ʱ����ֵ, Ϊ0ʱ��ʾδ���øö�ʱ�� 10..550 by step of 10; 600..1000 by step of 50; 0 */
    VOS_UINT8                           ucPollPdu;          /* ÿ���͸ò���ָ��������PDUʱ����һ��POLL, Ϊ0ʱ��ʾδ���ô˴�����ʽ 0, 1, 2, 4, 8, 16, 32, 64, 128 */
    VOS_UINT8                           ucPollSdu;          /* ÿ���͸ò���ָ��������SDUʱ����һ��POLL, Ϊ0ʱ��ʾδ���ô˴�����ʽ 0, 1, 4, 16, 64 */
    PS_BOOL_ENUM_UINT8                  enLastTxPduPoll;    /* ��TX BUF�����һ��PDU������ʱ�Ƿ����POLL */
    PS_BOOL_ENUM_UINT8                  enLastReTxPduPoll;  /* ��RETX BUF�����һ��PDU������ʱ�Ƿ����POLL */
    VOS_UINT8                           ucPollWnd;          /* ״̬����J���ڵ��ڸ�ֵʱ����һ��POLL, Ϊ0ʱ��ʾδ���ô˴�����ʽ 0, 50, 60, 70, 80, 85, 90, 95, 99 */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usTimerPollPrd;     /* Timer_Poll_Periodic��ʱ����ֵ, Ϊ0ʱ��ʾδ���øö�ʱ�� 0, 100, 200, 300, 400, 500, 750, 1000, 2000 */
}RLCITF_POLL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_EXPLI_DISCARD_STRU
 Э����  :
 ASN.1���� : ExplicitDiscard
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerMrw;         /*  ��λms. Timer_MRW��ʱ����ֵ, �ö�ʱ����������MRW SUFI���ش�.
                                                               Integer(50,60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 300, 400, 500, 700, 900) */
    VOS_UINT16                          usTimerDiscard;     /*  ��λms.Timer_discard��ʱ����ֵ, �ö�ʱ�������������Ͳ���ӦSDU�Ķ��� 100,
                                                                250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000,
                                                                4500, 5000, 7500*/
    VOS_UINT8                           ucMaxMrw;           /*MRW SUFI���Ա��ش��������� 1, 4, 6, 8, 12 16, 24, 32*/
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
} RLCITF_EXPLI_DISCARD_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_MAX_DAT_RETRANS_STRU
 Э����  :
 ASN.1���� : MaxDAT_Retransmissions
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxDat;           /*  ��һ��AMD PDU�ش�����������ֵʱ, ������PDU�а���������SDU segments
                                                                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40*/
    VOS_UINT8                           ucMaxMrw;           /*  MRW SUFI���Ա��ش��������� 1, 4, 6, 8, 12 16, 24, 32 */
    VOS_UINT16                          usTimerMrw;         /*  ��λms.Timer_MRW��ʱ����ֵ,�ö�ʱ����������MRWSUFI���ش� 50, 60,
                                                                70,80, 90, 100, 120,140, 160, 180, 200,300, 400, 500, 700,900*/
} RLCITF_MAX_DAT_RETRANS_STRU;


/*****************************************************************************
 �ṹ��    : RLCITF_DISCARD_MODE_CHOICE_STRU
 Э����  : 10.3.4.25 Transmission RLC Discard
 ASN.1���� : TransmissionRLC_Discard
 �ṹ˵��  : RLC�Ķ���ģʽ
*****************************************************************************/
typedef struct
{
    #define    RLCITF_TIMER_BASED_EXPLI_DISCARD_MODE_CHOSEN        0
    #define    RLCITF_TIMER_BASED_NO_EXPLI_DISCARD_MODE_CHOSEN     1
    #define    RLCITF_MAX_DAT_RETRANS_DISCARD_MODE_CHOSEN          2
    #define    RLCITF_NO_DISCARD_DISCARD_MODE_CHOSEN               3

    VOS_UINT32                          ulChoice;

    union
    {
        RLCITF_EXPLI_DISCARD_STRU       stTimerBasedExpli;  /* ����ģʽΪTimer based discard with
                                                               explicit signalingʱ�Ķ�����������     */
        VOS_UINT8                       ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
        RLCITF_MAX_DAT_RETRANS_STRU     stMaxDatRetrans;    /* ����ģʽΪSDU discard after MaxDAT
                                                               number of transmissionʱ�Ķ����������� */
        VOS_UINT8                       ucNoDisMaxDat;      /* ����ģʽΪNo discardʱ�Ķ����������� 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40 */
    } u;
}RLCITF_DISCARD_MODE_CHOICE_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_AM_RLC_STRU
 Э����  :
 ASN.1���� : UL_AM_RLC_Mode
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitPollInfo    : 1;
    VOS_UINT32                          bitSpare       : 31;

    RLCITF_DISCARD_MODE_CHOICE_STRU     stRlcDiscardMode;
    /* ASN.1 �ı� : TransmissionWindowSize */
    VOS_UINT16                          usTxWndSize;        /* ���ʹ����� 1, 8, 16, 32, 64, 128, 256, 512, 768, 1024, 1536, 2047, 2560, 3072, 3584, 4095                    */
    /* ASN.1 �ı� : TimerRST */
    VOS_UINT16                          usTimerRst;         /* Timer_RST��ʱ����ֵ 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000           */
    /* ASN.1 �ı� : MaxRST */
    VOS_UINT8                           ucMaxRst;           /* RESET PDU���Ա��ش��������� 1, 4, 6, 8, 12 16, 24, 32 */
    PS_BOOL_ENUM_UINT8                  enSendMrwInd;       /* �����RLCʵ����PS�򣬲�������"Support for lossless SRNS relocation or for lossless DL RLC PDU size change"��������ΪPS_TRUE;*/
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    RLCITF_POLL_INFO_STRU               stPollInfo;         /* POLL���� */
}RLCITF_UL_AM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_RLC_STATUS_INFO_STRU
 Э����  : 10.3.4.1 Downlink RLC STATUS info
 ASN.1���� : DL_RLC_StatusInfo
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerStaProh;     /* ��λms.Timer_Status_Prohibit��ʱ����ֵ, Ϊ0ʱ��ʾδ���øö�ʱ�� 10..550 by step of 10; 550..1000 by step of 50; */
    VOS_UINT16                          usTimerStaPeriod;   /* ��λms.Timer_Status_Periodic��ʱ����ֵ, Ϊ0ʱ��ʾδ���øö�ʱ�� 0, 100, 200, 300, 400, 500, 750, 1000, 2000 */
    PS_BOOL_ENUM_UINT8                  enMissPduInd;       /* ���ղ��⵽RLC PDU��ʧʱ�Ƿ���״̬���� */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}RLCITF_DL_RLC_STATUS_INFO_STRU;

/*V3 R7_7C1 Start */

/*Flexible Size*/
enum   RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_7_BIT        = 7,
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_15_BIT       = 15,
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_BUTT
};

typedef VOS_UINT16   RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : DL_RLC_PDU_SIZE_CHOICE_STRU
 Э����  : 10.3.4.23 RLC info
 ASN.1���� : CHOICE DL RLC PDU size
 �ṹ˵��  : DL RLC PDU size ѡ��
*****************************************************************************/

typedef struct
{
#define    RLCITF_DL_AM_PDU_FIXED_SIZE_CHOSEN        0/*Fixed size*/
#define    RLCITF_DL_AM_PDU_FLEXIBLE_SIZE_CHOSEN     1/*Flexible size*/

    VOS_UINT32                          ulChoice;
    union
    {
        VOS_UINT16                                          usDlRlcAmPduFixedSize;                  /*Fixed size��DL RLC PDU size����λbit,Integer(16..5000 by step of 8)*/
        RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16        enDlRlcAmPduLiSizeForFlexibleSize;      /*Flexible Size: 7bits or 15bits  */
    } u;
    VOS_UINT8                           aucRsv[2];
}RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 �ṹ��    : RLCITF_DL_AM_RLC_STRU
 Э����  :
 ASN.1���� : DL_AM_RLC_Mode
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitDlRlcPduSize    : 1;/*��stDlRlcPduSize.ulChoice ΪFIXED_SIZEʱ�� 0: AMD PDU size is not configured
                                                                 ��stDlRlcPduSize.ulChoice ΪFLEXIBLE_SIZEʱ   ��Ч*/
    VOS_UINT32                          bitSpare           : 31;

    /*V3 R7_7C1 Start */
    RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU   stDlRlcPduSize;     /*DL RLC PDU size*/
    PS_BOOL_ENUM_UINT8                  enInSeqDeliv;       /* �Ƿ�SN˳�����ϲ��ύSDU */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    /* V3 R7_7C1 End */

    VOS_UINT16                          usRxWndSize;        /* ���մ����� 1, 8, 16, 32, 64, 128, 256, 512, 768, 1024, 1536, 2047, 2560, 3072, 3584, 4095   */
    RLCITF_DL_RLC_STATUS_INFO_STRU      stDlRlcStaInfo;
}RLCITF_DL_AM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_UM_RLC_STRU
 Э����  :
 ASN.1���� : UL_UM_RLC_Mode
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitTxRlcDiscard       : 1;
    VOS_UINT32                          bitSpare              : 31;

    /* 10.3.4.25    Transmission RLC Discard */
    /* UM RLC����������ѡ��������ã�ֻ�����÷���ʾ���� */
    VOS_UINT8                           ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}RLCITF_UL_UM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_UM_RLC_STRU
 Э����  :
 ASN.1���� : DL_UM_RLC_Mode_r6
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitDlUmRlcLiSize    : 1;
    VOS_UINT32                          bitDlRecpWinSize    : 1;
    VOS_UINT32                          bitSpare            : 30;

    VOS_UINT8                           ucDlUmRlcLiSize;    /* R5����, 7, 15 */
    VOS_UINT8                           ucDlRecpWinSize;    /* R6����,MBMS���ܣ��ݲ�ʹ�ã�32, 48, 64, 80, 96, 112 */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RLCITF_DL_UM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_TM_RLC_STRU
 Э����  :
 ASN.1���� : UL_TM_RLC_Mode
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitTxRlcDiscard      : 1;
    VOS_UINT32                          bitSpare             : 31;

    /* TM RLC����������ѡ��������ã�ֻ�����÷���ʾ���� */
    VOS_UINT8                           ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
    PS_BOOL_ENUM_UINT8                  enSegInd;           /* �ֶ�ָʾ */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RLCITF_UL_TM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_TM_RLC_STRU
 Э����  :
 ASN.1���� : DL_TM_RLC_Mode
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSegInd;           /* �ֶ�ָʾ */
    RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM_UINT8     enErrSduInd;  /* CRC fail SDU����ָʾ   */
    VOS_UINT8                               aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RLCITF_DL_TM_RLC_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_SUSPEND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* Ҫ�������ݴ����RB��, [1, 31]  */
    VOS_UINT16                          usN;                /* ����ǰ�ɼ������͵�PDU��Ŀ, ��ʵ�֣�RRC�̶���Ϊ0 AM: [0, 4096] UM:[0, 1024]*/
}RLCITF_SUSPEND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_RLC_SN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* radio bear identity, [1, 31] */
    VOS_UINT16                          usCurSn;            /* VT(S)/VT(US) */
}RLCITF_RLC_SN_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_RB_CIPHER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlActTimeRlcSn        : 1;
    VOS_UINT32                          bitDlActTimeRlcSn        : 1;
    VOS_UINT32                          bitSpare                 : 30;

    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* RB��ʶ,��Ӧ��CN���ʶ, ��RLC������Ϣ���ṩ [1, 31] */
    VOS_INT16                           sUlActTimeRlcSn;    /* -1��ʾ����������м��ܼ���ʱ��; RLC SN, AM:0..4095, UM:0..127 */
    VOS_INT16                           sDlActTimeRlcSn;    /* -1��ʾ����������м��ܼ���ʱ��; RLC SN, AM:0..4095, UM:0..127 */
}RLCITF_RB_CIPHER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_AM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����AM RLC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, [2, 32]     */
    PS_BOOL_ENUM_UINT8                  enCnfIndFlg;        /* ��AM RLCʵ��ȷ�϶Զ˽��յ�RLC SDU��,
                                                            �Ƿ���Ҫʹ��RLC_RRC_AM_DATA_CNFԭ����߲㷢��ȷ�� */
    VOS_UINT32                          ulMui;              /* �ϲ�PDU��� */
    PS_BOOL_ENUM_UINT8                  enDiscardIndFlg;    /* ��IE�ݲ�ʹ�ã����ϲ�PDU������ʱ,�Ƿ���Ҫʹ��RLC_RRC_AM_DATA_CNFԭ�����ϲ�ָʾ*/
    PS_BOOL_ENUM_UINT8                  enNeedProtect;      /* �Ƿ���Ҫ����� */
    VOS_UINT16                          usDataLen;          /* ���ݲ��ֳ���, ��λ: byte         */
    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_AM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_AM_DATA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����AM RLC��Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, [2, 31]    */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulMui;              /* �ϲ�PDU��� */
    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* �ϲ�PDU���ͽ�� */
}RLC_RRC_AM_DATA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_UM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����UM RLC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, 1, 5-31     */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usDataLen;          /* ���ݲ��ֳ���, ��λ: byte          */
    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_UM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_AM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AM RLC�������ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT8                           ucRbId;             /* ���յ��ϲ�PDU��RB�� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usDataLen;          /* ���ݲ��ֳ���, ��λ: byte     */
    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_AM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_UM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UM RLC�������ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* ���յ��ϲ�PDU��RB��, 0-1, 5-31 */

    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usDataLen;          /* ���ݲ��ֳ���, ��λ: byte     */
    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_UM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_TM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM RLC�������ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* ���յ��ϲ�PDU��RB��, 5-31     */

    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulDatabitLen;       /* �ύ���ϲ�PDU�ĳ���, ��λ: bit  */

    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_TM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_TM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM RLC�������·�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, 0, 5-31        */

    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulDataBitLen;       /* �ϲ�PDU���ݳ���, ��λ: bit  */
    VOS_UINT8                           aucData[4];         /* �ϲ�����,��ǰ��Ĳ���һ��ռ����������Ϣ���ڴ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_TM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����߼��ŵ�PDUSize�б�, ��λ: Bit
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[3];

    VOS_UINT8                           ucPduSizeCnt;       /* �����߼��ŵ���ʹ�õ�PduSize��������*/
    VOS_UINT16                          ausPduSize[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/*�������±���RrcMacInterface.h�ӿ��е�MACITF_RACH_DCH_LOCH_MAPP_STRU��aucRlcSizeIdx[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH]�������±�����˳��һ��
                                                                                           ����25.331 8.6.5.1   Transport Format Set��������
                                                                                           DCCH/DTCH:
                                                                                           ������߼��ŵ�ӳ�䵽DCH��  ��ô������Ԫ��ֵ����RrcMacInterface.h�ӿ���TFS��Ӧ��RLC SIZEֵ;
                                                                                           ������߼��ŵ�ӳ�䵽RACH�� ��ô������Ԫ��ֵ��RrcMacInterface.h�ӿ���TFS��Ӧ��RLC SIZEֵ - 24bit(TCTF��UE-Id type��C-RNTI��C/T);
                                                                                           ������߼��ŵ�ӳ�䵽E-DCH����ô������Ԫ��ֵ��RrcMacInterface.h�ӿ���RB MAPPING�ж�Ӧ��RLC SIZEֵ
                                                                                           CCCH:
                                                                                           ������߼��ŵ�ӳ�䵽RACH�� ��ô������Ԫ��ֵ��RrcMacInterface.h�ӿ���TFS��Ӧ��RLC SIZEֵ - 2bit(TCTF)
                                                                                         */
}RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU;


/*****************************************************************************
 �ṹ��    : RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UL RLC PDU flexible SIZE
             ����UL AM MODE RLC,LI�ش��ڣ�UM TMģʽ��LI������.
             ��Э��25.331: If "CHOICE Uplink RLC mode" in the IE "RLC info"
             that applies for that RB  is "AM RLC " this IE is mandatory present.
             Otherwise the IE is not needed
             MinRlcPduSize��usLargestRlcPduSize 25.322����TMģʽû������ʹ�ã�
             Ŀǰ���TM���粻��������FLEXIBLE size
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucReserve1[2];             /* 4�ֽڶ��룬���� */
    RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16    enLenIndSize;               /* ������LIʱ��дBUTT */
    VOS_UINT16                                      usMinRlcPduSize;            /* Integer (16..12040 by step of 8) */
    VOS_UINT16                                      usLargestRlcPduSize;        /* Integer (16..12040 by step of 8) */
}RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_LOCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC���߼��ŵ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];                         /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucLochLabel;                            /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,34*2-1] */
    VOS_UINT8                           ucLochPrio;                             /* [1,8],�����߼��ŵ����ȼ�,����ԽС,���ȼ�Խ�� */

    #define    RLCITF_RLC_PDU_SIZE_FIXED_SIZE   0                               /* Fixed size */
    #define    RLCITF_RLC_PDU_SIZE_FLEX_SIZE    1                               /* Flexible size */

    VOS_UINT32                                  ulChoice;

    union
    {
        RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU  stFixedSize;                    /* Fixed size */
        RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU   stFlexSize;                     /* Flexible Size */
    } u;

}RLCITF_UL_LOCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_LOCH_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����߼��ŵ�ӳ�䣬һ��RB����ӳ��1������2���߼��ŵ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucLochCnt;          /* RBӳ����߼��ŵ����� */
    RLCITF_UL_LOCH_INFO_STRU            astUlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];/*�����±�Ϊ0ʱ��Ӧ��һ���߼��ŵ�, �����±�Ϊ1ʱ��Ӧ�ڶ����߼��ŵ�*/
}RLCITF_UL_LOCH_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_LOCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DL RLC���߼��ŵ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochLabel;        /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,[0,34*2-1]] */
    /* ���в���Ҫ����RLC SIZE����MACָʾRLC��WAS��MAC��TFS��ָʾMAC */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}RLCITF_DL_LOCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_LOCH_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����߼��ŵ�ӳ�䣬һ��RB����ӳ��1������2���߼��ŵ�,AM RLCʵ����ܶ�Ӧ2��
             �߼��ŵ����ýṹֻ��AM RLCʹ�á�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochCnt;          /* RBӳ����߼��ŵ����� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    RLCITF_DL_LOCH_INFO_STRU            astDlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];
}RLCITF_DL_LOCH_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_TM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UL TM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    RLCITF_UL_LOCH_INFO_STRU            stTmUlLochInfo;
    RLCITF_UL_TM_RLC_STRU               stUlTmPara;      /* RLC TMʵ�����в���  */
}RLCITF_UL_TM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_TM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DL TM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    RLCITF_DL_LOCH_INFO_STRU            stTmDlLochInfo;
    RLCITF_DL_TM_RLC_STRU               stDlTmPara;      /* RLC TMʵ�����в���  */
}RLCITF_DL_TM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_UM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UL UM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUlHfn;        /*�μ�RLCITF_UL_AM_RLC_INFO_STRU�ж�HFN������*/
    RLCITF_UL_LOCH_INFO_STRU            stUmUlLochInfo;
    RLCITF_UL_UM_RLC_STRU               stUlUmPara;     /* RLC UMʵ�����в���  */
}RLCITF_UL_UM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_UM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DL UM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDlHfn;        /*�μ�RLCITF_DL_AM_RLC_INFO_STRU�ж�HFN������*/
    RLCITF_DL_LOCH_INFO_STRU            stUmDlLochInfo;
    RLCITF_DL_UM_RLC_STRU               stDlUmPara;     /* RLC UMʵ�����в���  */
}RLCITF_DL_UM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_UL_AM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UL AM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    /*****************************************************************************
    HFN
     1) RRC���½����ؽ�AM/UM RLCʵ��ʱ����Ҫ����HFN��
        RLC��RLC SN=0�����õ�HFN��ʼά��COUNT-Cֵ��
     2) RRC�����ü��ܲ���ʱ��Ҳ��Ҫ��AM/UM RLCʵ������HFN��
        ����ʱ�䵽ʱ��RLC��ʼ���������õ�HFN��
        ����ʱ��RLC SN,��ʼά��COUNT-C,(����ʱ�䵽ǰ����ά��ԭ����COUNT-C)

        RRC_RLC_CFG_MODE_MODIFYʱ��ulUlHfn RRC�������ã�RLC��������;
        RRC_RLC_CFG_MODE_SETUP/RRC_RLC_CFG_MODE_REESTʱ,ulUlHfn RRCҪ�����ã�RLC����������
    *****************************************************************************/
    VOS_UINT32                          ulUlHfn;
    RLCITF_UL_LOCH_INFO_LIST_STRU       stAmUlLochInfo;
    RLCITF_UL_AM_RLC_STRU               stUlAmPara;      /* RLC AMʵ�����в���  */
}RLCITF_UL_AM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_DL_AM_RLC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DL AM RLC������Ϣ
*****************************************************************************/
typedef struct
{
    /*  RRC_RLC_CFG_MODE_MODIFYʱ��ulDlHfn RRC�������ã�RLC��������;
        RRC_RLC_CFG_MODE_SETUP/RRC_RLC_CFG_MODE_REESTʱ,ulDlHfn RRCҪ�����ã�RLC����������
    */
    VOS_UINT32                          ulDlHfn;
    RLCITF_DL_LOCH_INFO_LIST_STRU       stAmDlLochInfo;
    RLCITF_DL_AM_RLC_STRU               stDlAmPara;      /* RLC AMʵ�����в���  */
}RLCITF_DL_AM_RLC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_AM_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AM RLC������Ϣ, ����ȫ�䣬����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID     */

    VOS_UINT8                           ucRbId;             /* Ҫ���õ�RB��, 2-31    */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* ��ʶ��ǰRB�����ĸ�CN������RBʱ��BUTT */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* ��������ģʽ */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* ��������ģʽ */

    /*V3 R7_SpecialHE Start */
    PS_BOOL_ENUM_UINT8                  enSpecialHEField;  /*Special HE Field�Ƿ�ʹ�� PS_TRUE��ʾʹ�ã�PS_FALSE��ʾ��ʹ�� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    /* V3 R7_SpecialHE End */

    RLCITF_UL_AM_RLC_INFO_STRU          stUlAmRlcInfo;      /* ����AM RLC����*/
    RLCITF_DL_AM_RLC_INFO_STRU          stDlAmRlcInfo;      /* ����AM RLC����*/
}RRC_RLC_AM_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_UM_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UM RLC������Ϣ, ����ȫ�䣬����������
             ����RB0��ֻ��д
             enCfgMode = RLC_RRC_CONFIG_MODE_SETUP;
             ucRbId = 0;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID */

    VOS_UINT8                           ucRbId;             /* [0,32]����RLCITF_CTCH_RB_ID,*/
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* ��ʶ��ǰRB�����ĸ�CN������RBʱ��BUTT */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* ��������ģʽ */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* ��������ģʽ */

    /*V3 R7_7C1 Start */
    PS_BOOL_ENUM_UINT8                  enEBit;           /*E-bit:The absence of this IE implies: "normal E-bit interpretation"*/
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    /* V3 R7_7C1 End */

    RLCITF_UL_UM_RLC_INFO_STRU          stUlUmRlcInfo;      /* ����UM RLC����*/
    RLCITF_DL_UM_RLC_INFO_STRU          stDlUmRlcInfo;      /* ����UM RLC����*/

}RRC_RLC_UM_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_RLC_TM_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM RLC������Ϣ, ����ȫ��, ����������
             ����RB0, ֻ��д
             enUlCfgMode = RRC_RLC_CFG_MODE_SETUP;
             enDlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE;
             ucRbId = 0;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������ʶ     */

    VOS_UINT8                           ucRbId;             /* Ҫ���õ�RB��, 0, 5-32    */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* ��ʶ��ǰRB�����ĸ�CN������RBʱ��BUTT */
    PS_BOOL_ENUM_UINT8                  enSrbInd;           /* RBs whose identities shall be set between 5 and 32 may be used as
                                                               signalling radio bearer for the RRC messages on the DCCH sent in RLC transparent mode (RLC-TM).*/
    VOS_UINT8                           aucReserve[3];     /* 4�ֽڶ��룬���� */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* ��������ģʽ */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* ��������ģʽ */

    RLCITF_UL_TM_RLC_INFO_STRU          stUlTmRlcInfo;      /* ����TM RLC����, enUlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE��Ч */
    RLCITF_DL_TM_RLC_INFO_STRU          stDlTmRlcInfo;      /* ����TM RLC����, enDlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE��Ч*/

}RRC_RLC_TM_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������ʶ */
    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* ���ý��, ��RB����ʧ�ܻ�REQ��������, ��ʧ�� */
}RLC_RRC_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�ͷ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID            */

    VOS_UINT8                           ucCnt;              /* [0,PS_WUE_MAX_RB_NUM],�ͷŵ�RB����Ŀ, Ϊ0ʱȫ�ͷ�  */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* �ͷŵ�RB ID���б�[0,32]����RLCITF_CTCH_RB_ID */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_RLC_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�ͷ���Ӧ, ���ͷ�һ��δ���õ�RB��RRC_RLC_RELEASE_REQ��Ϣ�������󣬻�ʧ��;
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC��������
             RRC����RLC���ܲ���������RRC�����л�ʱ����RLC��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID        */

    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucSuspendRbCnt;     /* ��Ҫ�����RB����, [1, 31] */
    RLCITF_SUSPEND_INFO_STRU            astSuspendInfo[PS_WUE_MAX_RB_NUM];
}RRC_RLC_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* operation identity */

    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucSuspendRbCnt;            /* �������RB����, [1, 31] */
    RLCITF_RLC_SN_STRU                  astRlcSn[PS_WUE_MAX_RB_NUM];/* suspended result */

    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* suspend resultΪVOS_NGʱ, aResult��usRB2Sn��Ч */
}RLC_RRC_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�ָ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;             /* Operation ID            */

    VOS_UINT8                           ucResumeRbCnt;      /* ���ָ����ݴ����RB����, [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* Ҫ�ָ����ݴ����RB��, [1, 31]    */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_RLC_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�ָ���Ӧ
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU        RLC_RRC_RESUME_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRC_RLC_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1) ��RRC�յ�������Ϣ��IE��"RB information to reconfigure"
                ������IE"RB stop/continue"ֵΪstop, ����RRC_RLC_STOP_REQԭ��,
                ����ֹͣRB ID����2��RLCʵ��;
             2) ����Ӳ�л�ʱ;
             3) D2D����ʱ;
             4) CELL/URA UPDATEʱ;
             5) ������ϵͳ�л�����ѡʱ, ���յ�NAS�صĹ�����Ӧ��Ϣ��,
                �ᴥ����ԭ��ֹͣ���е�RLCʵ��;
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;             /* Operation ID                */

    VOS_UINT8                           ucStopRbCnt;        /* ��ֹͣ��RB���� [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* Ҫֹͣ���ݴ����RB�� [1, 31]   */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_RLC_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLCֹͣ��Ӧ
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_CONTINUE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ��RLC��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID                */

    VOS_UINT8                           ucContinueRbCnt;    /* Ҫ�������ݴ����RB����, [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* Ҫ�������ݴ����RB��, [1, 31]    */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_RLC_CONTINUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_CONTINUE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_CONTINUE_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RLC_RRC_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1) ��RLC RESET���̽�����, ���͸�ԭ��
             2) ��������·�����Ӷ�ʧ��ʱ��, ���͸�ԭ��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* �����¼���RB�ı��, [2, 32]        */

    RLCITF_EVENT_TYPE_ENUM_UINT8        enEventType;        /* �¼�����                    */
}RLC_RRC_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_ULDATA_TX_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC��������ָʾ
             ��RLC�������ʵ���ڽ��յ�RRC�Ľ���CELL_PCH��URA_PCH״̬��֪ͨ��,
             ��������������Ҫ����, ʹ�ø���ԭ����RRC����ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RLC_RRC_ULDATA_TX_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_MODE_CHANGE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLCģʽ�ı�����
             ����ָʾ�������õ��������ݴ���ģʽ�������ݴ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* operation identity */
    WUEL2L3_UL_MODE_ENUM_UINT8          enMode;             /* L2����ģʽ  */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}RRC_RLC_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_MODE_CHANGE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLCģʽ�ı�������Ӧ
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_MODE_CHANGE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RLCITF_CIPHER_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC��������
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enHfnAddOneInd;     /* PS_TRUE��RRC�������õ�HFNҪ����1��RLC������ά��,��μ�25.331,8.3.6.3��8.3.3.3��8.2.2.3������*/
    WUEL2L3_CIPHER_ALGO_ENUM_UINT8      enCipherAlgo;       /* �����㷨 */

    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucCsRbCnt;          /* AM,UMģʽCS��RB����,���ucCsRbCnt����Ϊ0, �����CS����Ҫ���� 0..3 */
    RLCITF_RB_CIPHER_INFO_STRU          astCsRbCipherInfo[PS_WUE_MAX_CS_RB_NUM];   /* CS��RB�б���RB��Ӧ�������м��ܼ���ʱ�� */
    VOS_UINT8                           aucCsCk[WUE_CIPHER_KEY_LEN];/* CS�������Կ */
    VOS_UINT32                          ulCsRbCountCMsb;    /* ����AM RLC: ulCsRbCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB��CS������COUNT_C; ulCsRbCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB��CS������COUNT_C;
                                                               ����UM RLC: ulCsRbCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB��CS������COUNT_C; ulCsRbCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB��CS������COUNT_C; */

    VOS_UINT8                           aucReserve2[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucPsRbCnt;          /* AM,UMģʽPS��RB����, ���ucPsRbCnt����Ϊ0, �����PS����Ҫ���� 0..3 */
    RLCITF_RB_CIPHER_INFO_STRU          astPsRbCipherInfo[PS_WUE_MAX_PS_RB_NUM];   /* PS��RB�б���RB��Ӧ�������м��ܼ���ʱ�� */
    VOS_UINT8                           aucPsCk[WUE_CIPHER_KEY_LEN]; /* PS�������Կ */
    VOS_UINT32                          ulPsRbCountCMsb;    /* ����AM RLC: ulPsRbCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB��PS������COUNT_C; ulPsRbCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB��PS������COUNT_C;
                                                               ����UM RLC: ulPsRbCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB��PS������COUNT_C; ulPsRbCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB��PS������COUNT_C; */

    VOS_UINT8                           aucReserve3[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucSrbCnt;           /* [0,4],AM,UMģʽSRB���������ucSrbCnt����Ϊ0, �����û����������RB���ܲ�������������RB����Ҫ���� */
    RLCITF_RB_CIPHER_INFO_STRU          astSrbCipherInfo[PS_WUE_MAX_SRB_NUM];    /* SRB�б���RB��Ӧ�������м��ܼ���ʱ�� */
    VOS_UINT8                           aucLatestDomainCk[WUE_CIPHER_KEY_LEN];/* �����ļ�����Կ */
    VOS_UINT32                          ulLatestDomainCountCMsb;  /* ����RB2-4,ʹ��AM RLC: ulLatestDomainCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB������COUNT_C; ulLatestDomainCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)ֱ�������γɶ�ӦRB������COUNT_C;
                                                                     ����RB1,  ʹ��UM RLC: ulLatestDomainCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB������COUNT_C; ulLatestDomainCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)ֱ�������γɶ�ӦRB������COUNT_C; */
}RLCITF_CIPHER_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_CIPHER_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpID;             /* ������ʶ*/

    RLCITF_CIPHER_CONFIG_INFO_STRU      stCipherInfo;
}RRC_RLC_CIPHER_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_CIPHER_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC��������������Ӧ
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_CIPHER_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RLC_RRC_CIPHER_ACTIVE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UM,AM��RLCͨ�����ԭ��֪ͨWAS��TM����MAC֪ͨWAS
             ֪ͨRRC��RB����/���м��������Ѿ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* RB identity, [0, 31] */
    WUEL2L3_DIR_ENUM_UINT8               enDir;              /* indicate uplink or downlink direction ciphering active  */
}RLC_RRC_CIPHER_ACTIVE_IND_STRU;


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
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RRC_RLC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_RLC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_RLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_RLC_MSG_DATA                    stMsgData;
}RrcRlcInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 WTTF_RLC_GetMaxCountCForCipher(VOS_UINT8 ucRbId,VOS_UINT32 *pulUlCountC,VOS_UINT32 *pulDlCountC);
extern VOS_UINT32 WTTF_RLC_GetRbDlRlcPduSize(VOS_UINT8 ucRbId, RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU *pstDlRlcPduSize);
extern VOS_UINT32 WTTF_RLC_AmGetUlActTimeRlcSn(VOS_UINT8 ucRbId, VOS_UINT32 ulLastSduByteLen, VOS_UINT32 *pulActTimeRlcSn);
extern VOS_UINT32 WTTF_RLC_GetEntityState(VOS_UINT8 ucRbId);
extern VOS_UINT32 WTTF_RLC_GetAmSrbSendState
(
    VOS_UINT8                           ucRbId,
    VOS_UINT32                         *pulThreshold,
    VOS_UINT32                         *pulBo
);


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

#endif /* end of RrcRlcInterface.h */


