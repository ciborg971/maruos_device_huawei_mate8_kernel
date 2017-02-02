
#ifndef __CSSOMINTERFACE_H__
#define __CSSOMINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CssInterface.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CSS_TIMER_ID_TO_MSG_ID_BASE     (0x20)
#define CSS_OM_MAX_COMM_BAND_NUM           (22)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
    ö����    : CSS_TIMER_RUN_STA_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    CSS_TIMER_RUN_STA_ENUM
{
    CSS_TIMER_RUNNING                = 0x00,
    CSS_TIMER_STOPED,
    CSS_TIMER_INVALID,

    CSS_TIMER_BUTT
};
typedef VOS_UINT32   CSS_TIMER_RUN_STA_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : CSS_MAIN_STATE_ENUM
 �ṹ˵��  : CSS�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    CSS_OM_MAIN_STATE_ENUM
{
    /*=================== CSS����״̬ ===================*/
    CSS_OM_MS_IDLE                         = 0x0000,
    CSS_OM_MS_SCAN                                 ,           /* ɨƵ�����е�״̬ */
    CSS_OM_MS_STOP_SCAN                            ,           /* ֹͣɨƵ������״̬ */

    CSS_OM_MAIN_STATE_BUTT
};
typedef VOS_UINT16 CSS_OM_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : CSS_SUB_STATE_ENUM
 �ṹ˵��  : CSS�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    CSS_OM_SUB_STATE_ENUM
{
    /*=================== CSS����״̬ ===================*/
    CSS_OM_SS_WAIT_START_IND                   = 0x0000,           /* �ȴ�������״̬��ֻ��������Ϣ */
    CSS_OM_SS_IDLE                                     ,
    CSS_OM_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF            ,           /* �ȴ�������ģ�ظ�״̬ */
    CSS_OM_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF          ,           /* �ȴ����ô�ģ�ظ�״̬ */
    CSS_OM_SS_WAIT_BAND_SCAN_IND                       ,           /* �ȴ�������ϱ�ɨƵ���״̬ */
    CSS_OM_SS_WAIT_STOP_SCAN_CNF                       ,           /* �ȴ�������ϱ�ֹͣɨƵ���״̬ */

    CSS_OM_SS_STATE_BUTT
};
typedef VOS_UINT16 CSS_OM_SUB_STATE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_FAIL_REASON_ENUM
 �ṹ˵��  :
*****************************************************************************/
enum    CSS_BAND_SCAN_FAIL_REASON_ENUM
{
    CSS_BAND_SCAN_FAIL_REASON_NONE                  = 0x0000,           /* û��ʧ��ԭ��ֵ */
    CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT                                     ,
    CSS_BAND_SCAN_FAIL_REASON_SCANING                       ,           /* �ȴ�������ģ�ظ�״̬ */
    CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING                  ,           /* �ȴ����ô�ģ�ظ�״̬ */

    CSS_BAND_SCAN_FAIL_REASON_BUTT
};
typedef VOS_UINT8 CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8;


enum CSS_OM_MSG_ID_ENUM
{
    ID_CSS_STATE_CHANGE_IND,                            /* _H2ASN_MsgChoice CSS_STATE_CHANGE_IND_STRU */
    ID_CSS_COMM_BAND_NV_INFO_IND,                       /* _H2ASN_MsgChoice CSS_COMM_BAND_NV_INFO_IND_STRU */
    ID_CSS_RAT_THRESHOLD_INFO_IND,                      /* _H2ASN_MsgChoice CSS_RAT_THRESHOLD_INFO_IND_STRU */
    ID_CSS_BAND_SCAN_RESULT_IND,                        /* _H2ASN_MsgChoice CSS_BAND_SCAN_RESULT_IND_STRU */
    ID_CSS_BAND_SCAN_API_INFO_IND,                      /* _H2ASN_MsgChoice CSS_BAND_SCAN_API_INFO_IND_STRU */
    ID_CSS_UE_SUPORT_BAND_INFO_IND,                     /* _H2ASN_MsgChoice CSS_UE_SUPPORT_BAND_INFO_IND_STRU */
    ID_CSS_BAND_SCAN_ABNORMAL_INFO_IND,

    ID_TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF    = 0x00 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF      = 0x01 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_SCAN_IND                 = 0x02 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_STOP_SCAN_CNF            = 0x03 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/

    ID_CSS_INTRA_MSG_BUTT
};
typedef VOS_UINT32 CSS_OM_MSG_ID_ENUM_UINT32;

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
 �ṹ��     : CSS_OM_BAND_PARA_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : ���õ�BAND���Լ���BAND��Ӧ�Ľ��뼼��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpLteSupport: 1;
    VOS_UINT8                           bitOpTdsSupport: 1;
    VOS_UINT8                           bitOpWcdmaSupport: 1;
    VOS_UINT8                           bitOpGsmSupport: 1;
    VOS_UINT8                           bitOpSpare: 4;

    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[2];
} CSS_OM_BAND_PARA_STRU;

/*****************************************************************************
 �ṹ��     : CSS_NV_COMM_BAND_CONFIG_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : ���õ�COMM BAND��Ϣʱ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNum;
    VOS_UINT8                           aucRsv[3];
    CSS_OM_BAND_PARA_STRU               astBand[CSS_NV_MAX_COMM_BAND_NUM];
} CSS_OM_COMM_BAND_CONFIG_STRU;

/*****************************************************************************
 �ṹ��     : CSS_OM_RSSI_THRESHOLD_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �����뼼����Ӧ�Ŀ�פ�������Լ�����������
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sGHighRssiThresHold;/* Gģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sGLowRssiThresHold;/* Gģ��Ӧ�Ŀ�פ����������ֵ */
    VOS_INT16                                   sWHighRssiThresHold;/* Wģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sWLowRssiThresHold;/* Wģ��Ӧ�Ŀ�פ����������ֵ */
    VOS_INT16                                   sLHighRssiThresHold;/* Lģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sLLowRssiThresHold;/* Lģ��Ӧ�Ŀ�פ����������ֵ */
} CSS_OM_RSSI_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CSS_TIMER_INFO_STRU
 �ṹ˵��  : log��CSS��ʱ���������
 1.��    ��   : 2015��05��25��
   ��    ��   : w0209181
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    CSS_TIMER_RUN_STA_ENUM_UINT32           enTimerStatus;   /* ��ʱ��״̬*/

    VOS_UINT16                              usTimerId;       /* ��ʱ��ID*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulTimerRemainLen;/* ��ʱ����ʱ�� */
}CSS_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CSS_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_STATE_CHANGE_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*��Ϣ����*/
    CSS_OM_MAIN_STATE_ENUM_UINT16                      enPreMainState;     /* ת״̬֮ǰ����״̬ */
    CSS_OM_SUB_STATE_ENUM_UINT16                       enPreSubState;      /* ת״̬֮ǰ����״̬ */
    CSS_OM_MAIN_STATE_ENUM_UINT16                      enCurMainState;     /* ת״̬֮�����״̬ */
    CSS_OM_SUB_STATE_ENUM_UINT16                       enCurSubState;      /* ת״̬֮�����״̬ */
}CSS_STATE_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : CSS_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_STATE_CHANGE_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32               ulMsgId;                    /*��Ϣ����*/
    VOS_UINT32                              ulFileName;
    VOS_UINT32                              ulLineNo;
    CSS_OM_MAIN_STATE_ENUM_UINT16           enCurMainState;     /* ת״̬֮�����״̬ */
    CSS_OM_SUB_STATE_ENUM_UINT16            enCurSubState;      /* ת״̬֮�����״̬ */
    CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8    enBandScanFailReason;   /* ɨƵʧ�ܵ�ԭ��ֵ */
    VOS_UINT8                               ucPara1;
    VOS_UINT8                               ucPara2;
    VOS_UINT8                               ucRsv;
}CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : CSS_COMM_BAND_NV_INFO_IND_STRU
 Э����  : NV���õ�COMM BAND��Ϣ
 ASN.1���� :
 �ṹ˵��  : CSS_COMM_BAND_NV_INFO_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*��Ϣ����*/
    CSS_OM_COMM_BAND_CONFIG_STRU                    stCommBandInfo;
}CSS_COMM_BAND_NV_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CSS_COMM_BAND_NV_INFO_IND_STRU
 Э����  : NV���õ�COMM BAND��Ϣ
 ASN.1���� :
 �ṹ˵��  : CSS_COMM_BAND_NV_INFO_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*��Ϣ����*/
    CSS_OM_RSSI_THRESHOLD_STRU                      stBandThresholdInfo;
}CSS_RAT_THRESHOLD_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CSS_OM_BAND_SCAN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    CSS_BAND_IND_ENUM_UINT16                    enBandInd;                          /* Ƶ��ָʾ */
    VOS_UINT8                                   ucFreqNum;                          /* ������ϱ���Ƶ����Ŀ */
    VOS_UINT8                                   ucDynMemSize;                       /* ��BAND�¶�̬�ڴ�Ĵ�С */
    CSS_FREQ_RANGE_STRU                         astFreqScanResult[CSS_MAX_BAND_FREQ_RANGE_NUM];          /* Ƶ����Ϣ */
}CSS_OM_BAND_SCAN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CSS_OM_BAND_SCAN_LIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDynMemSize;
    VOS_UINT8                                       ucBandNum;
    VOS_UINT8                                       aucReserve;
    CSS_OM_BAND_SCAN_INFO_STRU                      astScanRange[CSS_MAX_BAND_NUM];
}CSS_OM_BAND_SCAN_LIST_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_RESULT_IND_STRU
 Э����  : �������մ洢��ɨƵ���
 ASN.1���� :
 �ṹ˵��  : CSS_BAND_SCAN_RESULT_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                        ulMsgId;                    /*��Ϣ����*/
    CSS_OM_BAND_SCAN_LIST_INFO_STRU                  stBandScanResult;
}CSS_BAND_SCAN_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_API_INFO_IND_STRU
 Э����  : ��������API����ȡɨƵ�������Ϣ
 ASN.1���� :
 �ṹ˵��  : CSS_BAND_SCAN_API_INFO_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*��Ϣ����*/
    CSS_RAT_COVERAGE_STRU                           stRatCoverage;
    CSS_BAND_SCAN_LIST_INFO_STRU                    stBandScanResult;
}CSS_BAND_SCAN_API_INFO_IND_STRU;
typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare23     :23;
}CSS_GSM_BAND_STRU;

typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpareBand10       :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}CSS_WCDMA_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulBand;

    CSS_GSM_BAND_STRU                       stBitBand;
}CSS_GSM_BAND_SET_UN;

typedef union
{
    VOS_UINT32                          ulBand;

    CSS_WCDMA_BAND_STRU                     stBitBand;
}CSS_WCDMA_BAND_SET_UN;

/*******************************************************************************
 �ṹ��    : LTE_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��Ƶ�ζ���,aulLteBand[0]�����32,aulLteBand[1]�����32��Band,
            ���� �û�����Band1,Band3,��aulLteBand[0]=0x05,aulLteBand[1]=0x00
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          aulLteBand[2];
}CSS_LTE_BAND_STRU;


typedef struct
{
    CSS_WCDMA_BAND_SET_UN                   unWcdmaBand;                            /* wcdma��ǰ����֧�ֵ�Ƶ�� */
    CSS_GSM_BAND_SET_UN                     unGsmBand;                              /* gsm��ǰ����֧�ֵ�Ƶ�� */
    CSS_LTE_BAND_STRU                       stLteBand;                              /* lte��ǰ����֧�ֵ�Ƶ�� */
}CSS_UE_SUPPORT_FREQ_BAND_STRU;


/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_API_INFO_IND_STRU
 Э����  : ��������API����ȡɨƵ�������Ϣ
 ASN.1���� :
 �ṹ˵��  : CSS_BAND_SCAN_API_INFO_IND��Ӧ�Ľṹ�壬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*��Ϣ����*/
    CSS_UE_SUPPORT_FREQ_BAND_STRU                   stUeSupportBand;
}CSS_UE_SUPPORT_BAND_INFO_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export CSS_OM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CSS_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CSS_OM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_INTERFACE_MSG_DATA           stMsgData;
} CssOmInterface_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif /* end of ComInterface.h */

