
#ifndef __CSSINTERFACE_H__
#define __CSSINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CSS_PLMN_ID_LEN                 (3)

#define CSS_MAX_RAT_NUM                 (3)
#define CSS_MAX_BAND_FREQ_RANGE_NUM     (20)

#define CSS_MAX_BAND_NUM                (22)
#define CSS_BAND_WIDTH                  (1.1)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum CSS_MSG_ID_ENUM
{
    ID_CSS_MULTI_BAND_SCAN_REQ,                 /* _H2ASN_MsgChoice CSS_MULTI_BAND_SCAN_REQ_STRU */ /* GUNAS��֪ͨCSSɨƵʱ����Ҫ�����н��뼼��������Ȼ����֪ͨ����������
                                                                                                        �����֪ͨCSSɨƵʱ����Ҫ�Ƚ��Լ������������Ϊ��ģ  */
    ID_CSS_STOP_BAND_SCAN_REQ,                  /* _H2ASN_MsgChoice CSS_STOP_BAND_SCAN_REQ_STRU */

    ID_CSS_MULTI_BAND_SCAN_CNF,                 /* _H2ASN_MsgChoice CSS_MULTI_BAND_SCAN_CNF_STRU */
    ID_CSS_STOP_BAND_SCAN_CNF,                  /* _H2ASN_MsgChoice CSS_STOP_BAND_SCAN_CNF_STRU */
};
typedef VOS_UINT32 CSS_MSG_ID_ENUM_UINT32;

/*********************************************************
 ö����    : CSS_BAND_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Bandָʾö��
**********************************************************/
enum CSS_BAND_IND_ENUM
{
    CSS_BAND_IND_NONE,
    CSS_BAND_IND_1                   = 1 ,
    CSS_BAND_IND_2,
    CSS_BAND_IND_3,
    CSS_BAND_IND_4,
    CSS_BAND_IND_5,
    CSS_BAND_IND_6,
    CSS_BAND_IND_7,
    CSS_BAND_IND_8,
    CSS_BAND_IND_9,
    CSS_BAND_IND_10,
    CSS_BAND_IND_11,
    CSS_BAND_IND_12,
    CSS_BAND_IND_13,
    CSS_BAND_IND_14,
    CSS_BAND_IND_15,
    CSS_BAND_IND_16,
    CSS_BAND_IND_17                = 17,
    CSS_BAND_IND_18,
    CSS_BAND_IND_19,
    CSS_BAND_IND_20,
    CSS_BAND_IND_21,
    CSS_BAND_IND_22,
    CSS_BAND_IND_23,
    CSS_BAND_IND_24,
    CSS_BAND_IND_25,
    CSS_BAND_IND_26,
    CSS_BAND_IND_27,
    CSS_BAND_IND_28,
    CSS_BAND_IND_29,
    CSS_BAND_IND_30,
    CSS_BAND_IND_31,
    CSS_BAND_IND_32,
    CSS_BAND_IND_33                = 33,
    CSS_BAND_IND_34,
    CSS_BAND_IND_35,
    CSS_BAND_IND_36,
    CSS_BAND_IND_37,
    CSS_BAND_IND_38,
    CSS_BAND_IND_39,
    CSS_BAND_IND_40,
    CSS_BAND_IND_41,
    CSS_BAND_IND_42,
    CSS_BAND_IND_43,
//    CSS_BAND_IND_64                = 64,

    /* �Ǳ�Ƶ��begin */
/*    CSS_BAND_IND_101  = 101,
    CSS_BAND_IND_102  = 102,
    CSS_BAND_IND_103  = 103,
    CSS_BAND_IND_104  = 104,
    CSS_BAND_IND_105  = 105,
    CSS_BAND_IND_106  = 106,
    CSS_BAND_IND_107  = 107,
    CSS_BAND_IND_108  = 108,
    CSS_BAND_IND_109  = 109,
    CSS_BAND_IND_110  = 110,
    CSS_BAND_IND_111  = 111,
    CSS_BAND_IND_112  = 112,
    CSS_BAND_IND_113  = 113,
    CSS_BAND_IND_114  = 114,
    CSS_BAND_IND_115  = 115,
    CSS_BAND_IND_116  = 116,*/
    /* �Ǳ�Ƶ��end */

    CSS_BAND_IND_BUTT
};
typedef VOS_UINT16 CSS_BAND_IND_ENUM_UINT16;

/*****************************************************************************
 ö����: CSS_COVERAGE_TYPE_ENUM_UINT8
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum CSS_COVERAGE_TYPE_ENUM
{
    CSS_COVERAGE_TYPE_NONE     = 0,                 /* �����縲�� */
    CSS_COVERAGE_TYPE_LOW      = 1,                 /* ���������縲��   */
    CSS_COVERAGE_TYPE_HIGH     = 2,                 /* �и��������縲�� */
    CSS_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT8  CSS_COVERAGE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum CSS_MULTI_BAND_SCAN_RESULT_ENUM
{
    CSS_MULTI_BAND_SCAN_RESULT_SUCC             = 0,                /* ɨƵ�ɹ� */
    CSS_MULTI_BAND_SCAN_RESULT_FAIL_SCANING     = 1,                /* ����ɨƵ�����У�ֱ��ʧ��   */
    CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS      = 2,                /* ����ԭ���µ�ɨƵʧ�� */
    CSS_MULTI_BAND_SCAN_RESULT_NO_RF            = 3,                /* ����Ƶ��Դ */
    CSS_MULTI_BAND_SCAN_RESULT_FAIL_BUTT
};
typedef VOS_UINT8  CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8;


enum CSS_MULTI_BAND_SCAN_TYPE
{
    CSS_BAND_SCAN_COMM,                     /* ͨ�õ�ɨ�跽ʽ */
    CSS_BAND_SCAN_MCC_BASED,                /* ����MCC��ɨ�跽ʽ */
    CSS_BAND_SCAN_ALL,                      /* ����ALL��ɨ�跽ʽ */
    CSS_BAND_SCAN_BUTT
};
typedef VOS_UINT32 CSS_BAND_SCAN_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : CSS_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼��ö�ٶ���
*****************************************************************************/
enum CSS_RAT_TYPE_ENUM
{
    CSS_RAT_GSM                     = 0,
    CSS_RAT_UMTS_FDD                = 1,
    CSS_RAT_LTE                     = 2,
    CSS_RAT_TYPE_BUTT
};
typedef VOS_UINT8  CSS_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CSS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ԭ�����������ݽṹ
*****************************************************************************/
enum CSS_RESULT_ENUM
{
    CSS_RESULT_SUCC                 = 0,                /* �����ɹ� */
    CSS_RESULT_FAIL ,                                   /* ����ʧ�� */
    CSS_RESULT_BUTT
};
typedef VOS_UINT32    CSS_RESULT_ENUM_UINT32;

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
�ṹ��    :CSS_PLMN_ID_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[CSS_PLMN_ID_LEN];
    VOS_UINT8                           ucRsv;
}CSS_PLMN_ID_STRU;



/*****************************************************************************
 �ṹ��    : CSS_FREQ_RANGE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ƶ�ʷ�ΧCSS_FREQ_RANGE_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCentralFreq;          /* ����Ƶ�㣬��λ100khz��������1.1M�ı����䣬
                                                                            ���������Ҫ�Լ������BAND�ı߽� */
    VOS_INT16                                   sRssi;                  /* RSSI��ֵ��������1/64 db */
}CSS_FREQ_RANGE_STRU;


/*****************************************************************************
 �ṹ��    : CSS_RAT_LIST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���뼼��LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatNum;
    CSS_RAT_TYPE_ENUM_UINT8             aucRatList[CSS_MAX_RAT_NUM];
}CSS_RAT_LIST;


/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ΧMULTI_BAND_SCAN_INFO_STRU
*****************************************************************************/
typedef struct
{
    CSS_BAND_IND_ENUM_UINT16                    enBandInd;                          /* Ƶ��ָʾ */
    VOS_UINT16                                  usFreqNum;                          /* ������ϱ���Ƶ����Ŀ */
    CSS_FREQ_RANGE_STRU                         astFreqScanResult[CSS_MAX_BAND_FREQ_RANGE_NUM];          /* Ƶ����Ϣ */
}CSS_BAND_SCAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CSS_BAND_SCAN_LIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������Χlist
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucBandNum;
    VOS_UINT8                                       aucReserve[3];
    CSS_BAND_SCAN_INFO_STRU                         astScanRange[CSS_MAX_BAND_NUM];
}CSS_BAND_SCAN_LIST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CSS_MULTI_BAND_SCAN_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_MULTI_BAND_SCAN_REQ_STRU��Ӧ�Ľṹ�壬֪ͨ�ײ����bandɨƵ
 ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucMcc[0] ||    MCC digit 2         |           MCC digit 1
    ---------------------------------------------------------------------------
    aucMcc[1] ||    0                   |           MCC digit 3
    ---------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*��Ϣ����*/
    VOS_UINT32                                      ulOpid;
    CSS_BAND_SCAN_TYPE_ENUM_UINT32                  enBandScanType;             /*ɨ������*/

    VOS_UINT32                                      bitOpMcc        : 1;
    VOS_UINT32                                      bitOpHighRssi   : 1;        /* �Ƿ��Ǹ�����������,��ALL���ͻ���COMM���͵�ɨƵʱ��
                                                                                    ����Ҫ�жϸ�bitλ�Ƿ���Ч */
    VOS_UINT32                                      bitSpace        : 30;

    VOS_UINT8                                       aucMcc[2];                  /* MCC����,MCC_BASED��������ʱ����ҪЯ�� */
    VOS_UINT8                                       aucReserve[2];
    CSS_RAT_LIST                                    stRatList;                  /* ����BAND��rat list */
}CSS_MULTI_BAND_SCAN_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CSS_STOP_BAND_SCAN_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_STOP_BAND_SCAN_REQ��Ӧ�Ľṹ�壬
             �߲�֪ͨ�ײ�ֹͣbandɨƵ
             CSS�յ�����֪ͨPHYֹͣɨƵ����֪ͨPHY�����ģ
             PHY�ظ������ģ��CSSͨ��CSS_STOP_BAND_SCAN_CNF�ظ��߲�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*��Ϣ����*/

    VOS_UINT8                                       aucReserve[4];
}CSS_STOP_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CSS_MULTI_BAND_SCAN_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_MULTI_BAND_SCAN_CNF_STRU��Ӧ�Ľṹ�壬
             PHY�ϱ�ɨƵ�����CSS���BAND����֮�󣬻��ȹ���PHY
             ����ͨ������Ϣ�ϱ��߲�ɨƵ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*��Ϣ����*/
    VOS_UINT32                                      ulOpid;

    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult;                   /* ɨ���������û��ɨ������������쳣ʱ��Я���Ľ��ʱʧ�� */
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enGsmCoverageType;      /* ���ɨƵ������ָʾ���Ǹ������������ϱ��Ľ��ֻ�и��������ǻ�����ɨƵ��� */
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enUmtsFddCoverageType;
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enLteCoverageType;
}CSS_MULTI_BAND_SCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CSS_RAT_COVERAGE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_GetBandScanInfo�����Ŵ�����뼼���͸��ǲ���
*****************************************************************************/
typedef struct
{
    CSS_RAT_TYPE_ENUM_UINT8                         enRatType;
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enCoverageType;

    VOS_UINT8                                       aucReserve[2];

}CSS_RAT_COVERAGE_STRU;

/*****************************************************************************
 �ṹ��    : CSS_STOP_BAND_SCAN_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSS_STOP_BAND_SCAN_CNF��Ӧ�Ľṹ�壬
             PHY�ϱ�ɨƵ�����CSS���BAND����֮�󣬻��ȹ���PHY
             ����ͨ������Ϣ�ϱ��߲�ɨƵ���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*��Ϣ����*/

    CSS_RESULT_ENUM_UINT32                          enResult;                   /*0�ɹ���1ʧ��*/
}CSS_STOP_BAND_SCAN_CNF_STRU;

typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export CSS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CSS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CSS_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CSS_INTERFACE_MSG_DATA           stMsgData;
} CssInterface_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* �ṩ���ⲿ���ã���ȡ�ϴ�ɨƵ�����API��
stRatCoverage:��ȡ�ĸ����뼼���µ����ָ��ǵ�ɨƵ�����
pstCssBandInfo���ⲿģ�鴫��洢ɨƵ����ĵ�ַ�����ڴ��ɵ����߷��䣬�Լ��ͷ� */
CSS_RESULT_ENUM_UINT32 CSS_GetBandScanInfo(CSS_RAT_COVERAGE_STRU stRatCoverage, CSS_BAND_SCAN_LIST_INFO_STRU* pstCssBandInfo);






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
