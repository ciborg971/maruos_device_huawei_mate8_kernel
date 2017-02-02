
#ifndef __CSSLPHYINTERFACE_H__
#define __CSSLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#include "LPSCommon.h"
#endif
#include "TLPhyInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define CSS_LPHY_MAX_FREQ_NUM    100
#define CSS_LPHY_MSG_HDR                (0x00000B00)         /* PS_MSG_ID_CSS_TO_LPHY_BASE begin with  */
#define LPHY_CSS_MSG_HDR                (0x00001E95)         /* PS_MSG_ID_LPHY_TO_CSS_BASE begin with  */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : CSS_LPHY_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CSS <-> LPHY �ӿ���ϢID
*****************************************************************************/
enum CSS_LPHY_MSG_ID_ENUM
{
    ID_CSS_LPHY_BAND_SCAN_REQ                   = CSS_LPHY_MSG_HDR + 0x00, /* _H2ASN_MsgChoice CSS_LPHY_BAND_SCAN_REQ_STRU */
    ID_CSS_LPHY_STOP_BAND_SCAN_REQ              = CSS_LPHY_MSG_HDR + 0x01, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BAND_SCAN_REQ_STRU */
    ID_CSS_LPHY_SET_WORK_MODE_REQ               = CSS_LPHY_MSG_HDR + 0x02, /* _H2ASN_MsgChoice CSS_LPHY_SET_WORK_MODE_REQ_STRU */

    ID_CSS_LPHY_BAND_SCAN_IND                   = LPHY_CSS_MSG_HDR + 0x21, /* _H2ASN_MsgChoice CSS_LPHY_BAND_SCAN_IND_STRU */
    ID_CSS_LPHY_STOP_BAND_SCAN_CNF              = LPHY_CSS_MSG_HDR + 0x22, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BAND_SCAN_CNF_STRU */
    ID_CSS_LPHY_SET_WORK_MODE_CNF               = LPHY_CSS_MSG_HDR + 0x23, /* _H2ASN_MsgChoice CSS_LPHY_SET_WORK_MODE_CNF_STRU */

};
typedef  VOS_UINT32  CSS_LPHY_MSG_ID_ENUM_UINT32;


/*********************************************************
 ö����    : CSS_LPHY_BAND_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Bandָʾö��
**********************************************************/
enum CSS_LPHY_BAND_IND_ENUM
{
    CSS_LPHY_BAND_IND_NONE,
    CSS_LPHY_BAND_IND_1                   = 1 ,
    CSS_LPHY_BAND_IND_2,
    CSS_LPHY_BAND_IND_3,
    CSS_LPHY_BAND_IND_4,
    CSS_LPHY_BAND_IND_5,
    CSS_LPHY_BAND_IND_6,
    CSS_LPHY_BAND_IND_7,
    CSS_LPHY_BAND_IND_8,
    CSS_LPHY_BAND_IND_9,
    CSS_LPHY_BAND_IND_10,
    CSS_LPHY_BAND_IND_11,
    CSS_LPHY_BAND_IND_12,
    CSS_LPHY_BAND_IND_13,
    CSS_LPHY_BAND_IND_14,
    CSS_LPHY_BAND_IND_15,
    CSS_LPHY_BAND_IND_16,
    CSS_LPHY_BAND_IND_17                = 17,
    CSS_LPHY_BAND_IND_18,
    CSS_LPHY_BAND_IND_19,
    CSS_LPHY_BAND_IND_20,
    CSS_LPHY_BAND_IND_21,
    CSS_LPHY_BAND_IND_22,
    CSS_LPHY_BAND_IND_23,
    CSS_LPHY_BAND_IND_24,
    CSS_LPHY_BAND_IND_25,
    CSS_LPHY_BAND_IND_26,
    CSS_LPHY_BAND_IND_27,
    CSS_LPHY_BAND_IND_28,
    CSS_LPHY_BAND_IND_29,
    CSS_LPHY_BAND_IND_30,
    CSS_LPHY_BAND_IND_31,
    CSS_LPHY_BAND_IND_32,
    CSS_LPHY_BAND_IND_33                = 33,
    CSS_LPHY_BAND_IND_34,
    CSS_LPHY_BAND_IND_35,
    CSS_LPHY_BAND_IND_36,
    CSS_LPHY_BAND_IND_37,
    CSS_LPHY_BAND_IND_38,
    CSS_LPHY_BAND_IND_39,
    CSS_LPHY_BAND_IND_40,
    CSS_LPHY_BAND_IND_41,
    CSS_LPHY_BAND_IND_42,
    CSS_LPHY_BAND_IND_43,
//    CSS_LPHY_BAND_IND_64                = 64,

    /* �Ǳ�Ƶ��begin */
/*    CSS_LPHY_BAND_IND_101  = 101,
    CSS_LPHY_BAND_IND_102  = 102,
    CSS_LPHY_BAND_IND_103  = 103,
    CSS_LPHY_BAND_IND_104  = 104,
    CSS_LPHY_BAND_IND_105  = 105,
    CSS_LPHY_BAND_IND_106  = 106,
    CSS_LPHY_BAND_IND_107  = 107,
    CSS_LPHY_BAND_IND_108  = 108,
    CSS_LPHY_BAND_IND_109  = 109,
    CSS_LPHY_BAND_IND_110  = 110,
    CSS_LPHY_BAND_IND_111  = 111,
    CSS_LPHY_BAND_IND_112  = 112,
    CSS_LPHY_BAND_IND_113  = 113,
    CSS_LPHY_BAND_IND_114  = 114,
    CSS_LPHY_BAND_IND_115  = 115,
    CSS_LPHY_BAND_IND_116  = 116,*/
    /* �Ǳ�Ƶ��end */

    CSS_LPHY_BAND_IND_BUTT
};
typedef VOS_UINT16 CSS_LPHY_BAND_IND_ENUM_UINT16;

/*****************************************************************************
 ö����    : CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE RTT����ģʽ
*****************************************************************************/
enum CSS_LPHY_WORK_MODE_TYPE_ENUM
{
    CSS_LPHY_WORK_MODE_TYPE_ACTIVE                = 0,                         /* LTE���ڹ���̬ */
    CSS_LPHY_WORK_MODE_TYPE_INACTIVE              = 1,                         /* LTE���ڲ���̬ */
    CSS_LPHY_WORK_MODE_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : CSS_LPHY_DSDS_RFSHARED_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :DSDS����������RF shared�Ƿ�ʹ��
*****************************************************************************/
enum CSS_LPHY_DSDS_RFSHARED_ENUM
{
    CSS_LPHY_DSDS_RFSHARED_DISABLE           = 0,    /* ������ */
    CSS_LPHY_DSDS_RFSHARED_ENABLE            = 1,    /* ���� */
    CSS_LPHY_DSDS_RFSHARED_BUTT
};
typedef VOS_UINT16  CSS_LPHY_DSDS_RFSHARED_ENUM_UINT16;

/*****************************************************************************
 ö����    : CSS_LPHY_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ԭ�����������ݽṹ
*****************************************************************************/
enum CSS_LPHY_RESULT_ENUM
{
    CSS_LPHY_RESULT_SUCC                 = 0,                /* �����ɹ� */
    CSS_LPHY_RESULT_FAIL ,                                   /* ����ʧ�� */
    CSS_LPHY_RESULT_BUTT
};
typedef VOS_UINT16    CSS_LPHY_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ɨƵ����
*****************************************************************************/
enum CSS_LPHY_BAND_SCAN_TYPE_ENUM
{
    CSS_LPHY_BAND_SCAN_TYPE_INIT                  = 0,                         /* ��ʼɨƵ */
    CSS_LPHY_BAND_SCAN_TYPE_CONT                  = 1,                         /* ����ɨƵ */
    CSS_LPHY_BAND_SCAN_TYPE_IRAT                  = 2,                         /* ֻ��ʹ�ø����͵�ɨƵʱ�������Ż��ϱ�RSSIֵ */
    CSS_LPHY_BAND_SCAN_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : LTEģʽ����
*****************************************************************************/
enum CSS_LPHY_LTE_MODE_TYPE_ENUM
{
    CSS_LPHY_LTE_MODE_TYPE_FDD                = 0,                             /* LTE FDD ��ʽ */
    CSS_LPHY_LTE_MODE_TYPE_TDD                = 1,                             /* LTE TDD ��ʽ */
    CSS_LPHY_LTE_MODE_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16;
/*****************************************************************************
  5 Struct
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CSS_LPHY_FREQ_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16              usFreqBegin;
    VOS_UINT16              usFreqEnd;
}CSS_LPHY_FREQ_RANGE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CSS_LPHY_BAND_SCAN_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջָʾ�����ɨƵ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                     ulMsgId;                        /*_H2ASN_Skip*/     /* ԭ����ϢID */
    VOS_UINT16                                      usOpId;                         /* ������ʶ�� */
    VOS_UINT16                                      bitOpLteSupport: 1;             /* enBandInd�Ƿ�֧��L��ʽ*/
    VOS_UINT16                                      bitOpWcdmaSupport: 1;           /* enBandInd�Ƿ�֧��G��ʽ*/
    VOS_UINT16                                      bitOpGsmSupport: 1;             /* enBandInd�Ƿ�֧��W��ʽ*/
    VOS_UINT16                                      bitOpSpace: 13;                 /* �����ֶ� */
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16             enBandScanType;                 /* ɨƵ���� */
    VOS_UINT16                                      usRsv;
    CSS_LPHY_BAND_IND_ENUM_UINT16                   enBandInd;                      /* Ƶ��ָʾ */
    CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16              enLteModeType;                  /* ָʾƵ����������ʽ����, FDD��TDD */
    CSS_LPHY_FREQ_RANGE_INFO_STRU                   stFreqRangeInfo;                /* Ƶ����Ϣ */
}CSS_LPHY_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_STOP_BAND_SCAN_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջָʾ�����ֹͣɨƵ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                     ulMsgId;                        /*_H2ASN_Skip*/     /* ԭ����ϢID */
    VOS_UINT16                                      usOpId;                         /* ������ʶ�� */
    VOS_UINT16                                      usRsv;
}CSS_LPHY_STOP_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_FREQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�ʺ�����������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCentralFreq;      /* ����Ƶ�� */
    VOS_INT16                                   lRssi;              /* RSSI��ֵ */
}CSS_LPHY_FREQ_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ɨƵ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      bitOpLteSupport: 1;             /* enBandInd�Ƿ�֧��L��ʽ*/
    VOS_UINT16                                      bitOpWcdmaSupport: 1;           /* enBandInd�Ƿ�֧��G��ʽ*/
    VOS_UINT16                                      bitOpGsmSupport: 1;             /* enBandInd�Ƿ�֧��W��ʽ*/
    VOS_UINT16                                      bitOpSpace: 13;                 /* �����ֶ� */
    VOS_UINT16                                      usRsv;
    CSS_LPHY_BAND_IND_ENUM_UINT16                   enBandInd;                      /* Ƶ��ָʾ */
    VOS_UINT16                                      usFreqRangeNum;                 /* ������ϱ���Ƶ����Ŀ */
    CSS_LPHY_FREQ_INFO_STRU                         astFreqScanResult[CSS_LPHY_MAX_FREQ_NUM];          /* Ƶ����Ϣ */
}CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_BAND_SCAN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ָʾɨƵ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/     /* ԭ����ϢID */
    VOS_UINT16                                    usOpId;                       /* ������ʶ�� */
    VOS_UINT16                                    usNoRfValid;                  /* DSDS����NORFָʾ */
    CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU           stBandScanResult;             /* ɨƵ��� */
}CSS_LPHY_BAND_SCAN_IND_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_SET_WORK_MODE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_LPHY_SET_WORK_MODE_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType;                   /* ָʾLTE����ģʽ��0:���ڹ���̬��1:���ڲ���̬ */
    VOS_UINT16                                usRsv;
    CSS_LPHY_DSDS_RFSHARED_ENUM_UINT16        enDsdsRfShardFlg;
}CSS_LPHY_SET_WORK_MODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_STOP_BAND_SCAN_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_LPHY_STOP_BAND_SCAN_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16               enStopBandScanRslt;
}CSS_LPHY_STOP_BAND_SCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CSS_LPHY_SET_WORK_MODE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_LPHY_SET_WORK_MODE_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16               enWorkModeCfgRslt;
}CSS_LPHY_SET_WORK_MODE_CNF_STRU;


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

#endif /* end of ����ģ��+����ģ��+Interface.h */



