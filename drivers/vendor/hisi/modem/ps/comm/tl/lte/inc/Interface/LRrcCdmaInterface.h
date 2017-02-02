

#ifndef __LRRC_CDMA_INTERFACE_H__
#define __LRRC_CDMA_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/* LRRC��CDMA֮�����Ϣ��ַ */
#define LRRC_CDMA_INTRA_MSG_HDR                     (1000)
#define CDMA_LRRC_INTRA_MSG_HDR                     (2000)


#define LRRC_CDMA_BAND_MAX_NUM                      16


/* 1XRTT �� HRPD���ָ���֧������С����Ϊ16 */
#define LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM             16
#define LRRC_CDMA_CELL_MAX_NUM                      32


#define LRRC_CDMA_UINT8_INVALID                     (0XFF)
#define LRRC_CDMA_UINT16_INVALID                    (0XFFFF)
#define LRRC_CDMA_UINT32_INVALID                    (0XFFFFFFFF)


#define LRRC_CDMA_MEAS_CGI_RESULT                   16

#define CDMA_LRRC_LTE_EARFCN_MAX_NUM                7
#define CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM           8 //#define CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM           9 cdma�ӿ�������Ϊ8



#define LRRC_CDMA_CONN_MEAS_PERIOD_VALUE            200
#define LRRC_CDMA_IDLE_MEAS_PERIOD_VALUE            200

#define LTE_CDMA_LTE_PRI_INFO_MAX_NUM               4
#define LTE_CDMA_CDMA_PRI_INFO_MAX_NUM              3

#define LEE_CDMA_MIN_RSRP                           30

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    :LRRC_CDMA_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :LRRC�ڲ�ת��CDMA���ݽṹ�ڲ���Ϣ
*****************************************************************************/
enum LRRC_CDMA_MSG_TYPE_ENUM
{
    /* L->C CONN MEAS */
    LRRC_CDMA_CONN_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice LRRC_CDMA_CONN_MEAS_REQ_STRU */
    CDMA_LRRC_CONN_MEAS_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice CDMA_LRRC_CONN_MEAS_IND_STRU */

    /* L->C CELL RELSEL */
    LRRC_CDMA_CELL_RESEL_REQ                    = (LRRC_CDMA_INTRA_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice LRRC_CDMA_CELL_RESEL_REQ_STRU */
    CDMA_LRRC_CELL_RESEL_CNF                    = (CDMA_LRRC_INTRA_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice CDMA_LRRC_CELL_RESEL_CNF_STRU */


    /* L->C CELL REDIR */
    LRRC_CDMA_CELL_REDIR_REQ                    = (LRRC_CDMA_INTRA_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice LRRC_CDMA_CELL_REDIR_REQ_STRU */
    CDMA_LRRC_CELL_REDIR_CNF                    = (CDMA_LRRC_INTRA_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice CDMA_LRRC_CELL_REDIR_CNF_STRU */


    /* L->C IDLE MEAS */
    LRRC_CDMA_IDLE_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice LRRC_CDMA_IDLE_MEAS_REQ_STRU */
    CDMA_LRRC_IDLE_MEAS_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice CDMA_LRRC_IDLE_MEAS_IND_STRU */

    /* L->C IDLE PRI */
    LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ         = (LRRC_CDMA_INTRA_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU */
    /* C->L IDLE PRI */
    CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ         = (CDMA_LRRC_INTRA_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ_STRU */


    /* C->L  MEAS */
    CDMA_LRRC_MEAS_CELL_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice CDMA_LRRC_MEAS_CELL_REQ_STRU */
    LRRC_CDMA_MEAS_CELL_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice LRRC_CDMA_MEAS_CELL_IND_STRU */

    /* L->C MESA STOP */
    LRRC_CDMA_STOP_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_MEAS_REQ_STRU */

    /* C->L MESA STOP */
    CDMA_LRRC_STOP_MEAS_REQ                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_MEAS_REQ_STRU */

    /* L->C STOP Mobility */
    LRRC_CDMA_STOP_CELL_RESEL_REQ                 = (LRRC_CDMA_INTRA_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU */

    /* C->L STOP Mobility CNF */
    CDMA_LRRC_STOP_CELL_RESEL_CNF                 = (CDMA_LRRC_INTRA_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU */

    /* L->C STOP Mobility */
    LRRC_CDMA_STOP_CELL_REDIR_REQ                 = (LRRC_CDMA_INTRA_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU */

    /* C->L STOP Mobility CNF */
    CDMA_LRRC_STOP_CELL_REDIR_CNF                 = (CDMA_LRRC_INTRA_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_CELL_REDIR_CNF_STRU */

    LRRC_CDMA_MSG_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_CDMA_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����     :LRRC_CDMA_VALID_FLAG_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : ͨ���Ƿ���ڱ�־
*****************************************************************************/
enum LRRC_CDMA_VALID_FLAG_ENUM
{
    LRRC_CDMA_FLAG_INVALID                      = 0,
    LRRC_CDMA_FLAG_VALID                           ,

    LRRC_CDMA_FLAG_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_VALID_FLAG_ENUM_UINT8;


/*****************************************************************************
 ö����     :LRRC_CDMA_SYSTEM_TYPE_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : CDMA RAT��ϵͳ����
*****************************************************************************/
enum LRRC_CDMA_SYSTEM_TYPE_ENUM
{
    LRRC_CDMA_SYSTEM_TYPE_1XRTT                             = 0,
    LRRC_CDMA_SYSTEM_TYPE_HRPD,

    LRRC_CDMA_SYSTEM_TYPE_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����     :LRRC_CDMA_SYSTEM_TYPE_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : CDMA RAT��ϵͳ����
*****************************************************************************/
enum LRRC_CDMA_MEAS_TYPE_ENUM
{
    LRRC_CDMA_MEAS_TYPE_IRAT                               = 0,
    LRRC_CDMA_MEAS_TYPE_SIB8,

    LRRC_CDMA_MEAS_TYPE_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_MEAS_TYPE_UINT8;


/*****************************************************************************
 ö����     :LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : CDMAС���������
*****************************************************************************/
enum CDMA_LRRC_MEAS_RESULT_FLAG_ENUM
{
    /* Measurement completed successfully.Rest of the para are valid only in this case */
    CDMA_LRRC_MEAS_RESULT_SUCCESS               = 0,

    /* Measuremen failed since 1xRTT is on call,Need triger the meas again */
    CDMA_LRRC_MEAS_RESULT_1X_ONCALL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_ACQ_FAIL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_EMPTY_INFO,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_BAND_NOT_SPORT_FAIL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_FAIL,

    CDMA_LRRC_MEAS_RESULT_FLAG_BUTT
};
typedef VOS_UINT32    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32;


/*****************************************************************************
 ö����     :LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : LTEС���������
*****************************************************************************/
enum LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
{
    /* Measurement completed successfully */
    LRRC_CDMA_MEAS_RESULT_SUCCESS                           = 0,

    /* Meas failed, Need triger the meas again */
    LRRC_CDMA_MEAS_RESULT_ACQ_FAIL,

    /* Meas failed, Need triger the meas again*/
    LRRC_CDMA_MEAS_RESULT_BAND_NOT_SPORT_FAIL,

    /* Meas failed, Need triger the meas again*/
    LRRC_CDMA_MEAS_RESULT_FAIL,

    LRRC_CDMA_MEAS_RESULT_FLAG_BUTT
};
typedef VOS_UINT32    LRRC_CDMA_MEAS_RESULT_FLAG_ENUM_UINT32;


/*****************************************************************************
 ö����     :CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8
 Э����   :
 ASN.1����   :
 ö��˵�� : CDMA�ظ�С����ѡ�����ض���Ľ��
*****************************************************************************/
enum CDMA_LRRC_CELL_RESEL_RESULT_ENUM
{
    CDMA_LRRC_CELL_RESEL_RESULT_SUCCESS                     = 0,

    /* System change to target failed since target system could not be acquired */
    CDMA_LRRC_CELL_RESEL_RESULT_ACQ_FAIL,

    /* System change to target failed since PS registration on target system failed  */
    CDMA_LRRC_CELL_RESEL_RESULT_PS_REG_FAIL,

    /* System change to target failed since PS session establish on target system failed */
    CDMA_LRRC_CELL_RESEL_RESULT_PS_SESSION_FAIL,

    CDMA_LRRC_CELL_RESEL_RESULT_FAIL,

    CDMA_LRRC_CELL_RESEL_RESULT_BUTT
};
typedef VOS_UINT8    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8;

//#define CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8 CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8
typedef CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8 CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8;


/*****************************************************************************
 ö����     :CDMA_LRRC_CELL_REDIR_RESULT_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : ��������ö��
*****************************************************************************/
enum CDMA_LRRC_MEAS_BAND_WIDTH_ENUM
{
    CDMA_LRRC_MEAS_BAND_WIDTH_6RB               = 0,                /* ����Ϊ6RB   */
    CDMA_LRRC_MEAS_BAND_WIDTH_15RB                 ,                /* ����Ϊ15RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_25RB                 ,                /* ����Ϊ25RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_50RB                 ,                /* ����Ϊ50RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_75RB                 ,                /* ����Ϊ75RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_100RB                ,                /* ����Ϊ100RB */

    CDMA_LRRC_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 CDMA_LRRC_MEAS_BAND_WIDTH_ENUM_UINT8;

/*****************************************************************************
 ö����     :CDMA_LRRC_SYSCHG_STOP_REASON_ENUM
 Э����   :
 ASN.1����   :
 ö��˵�� : ��������ö��
*****************************************************************************/
enum LRRC_CDMA_SYSCHG_STOP_REASON_ENUM
{
    LRRC_CDMA_SYSCHG_STOP_REASON_RESEL              = 0,                /* ֹͣ��ѡ  */
    LRRC_CDMA_SYSCHG_STOP_REASON_REDIR                 ,                /* ֹͣ�ض���  */

    LRRC_CDMA_SYSCHG_STOP_REASON_BUTT
};
typedef VOS_UINT32 LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_MEAS_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA С����Ϣ�б�
*****************************************************************************/
typedef struct
{
    /* 0xffff ��ʾ��Ч */
    VOS_UINT16                  usCellToReportCgi;

    /* [0,2047] */
    VOS_UINT16                  usChannel;

    /* ��LTE�Ŀտ�ֵһ�� */
    VOS_UINT8                   ucBand;

    /* [[0,15],0xff], 0XFF,��ʾ��Ч */
    VOS_UINT8                   ucSearchWinSize;
    VOS_UINT16                  usCellNum;
    VOS_UINT16                  ausCellPn[LRRC_CDMA_CELL_MAX_NUM];
}LRRC_CDMA_MEAS_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����̬CDMA HPRDС����Ϣ�б�
*****************************************************************************/
typedef struct
{
    /* LTE CDMAϵͳ������Ӧ��С�������ڣ���λMS
       0:�����������һ�β�����������һ�β���һ��
       other:����һ��REQ�������ϱ��������,�̶�200ms
       ���㹫ʽ:
    */
    VOS_UINT32                          ulPeriod;

    /*  ���BAND���з��ͣ���һ��OBJ���ж�������ն�����з��� */
    VOS_UINT32                          ulBandInfoNum;
    LRRC_CDMA_MEAS_CELL_INFO_STRU       stLrrcCdemaMeasCellInfo[LRRC_CDMA_BAND_MAX_NUM];
}LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA С���������
*****************************************************************************/
typedef struct
{
    /* This is one from the meas cmd receive */
    VOS_UINT16                          usCellPn;

    /* CDMA pilot phase, in chips ,only for 1xRTT */
    VOS_UINT16                          usPilotPhase;

    /* (0,30),CDMA pilt strength ʵ�ʼ���ʱ��Ҫ���� -0.5  */
    VOS_INT16                           sPilotStrength;
    VOS_UINT16                          usReserved;
}CDMA_LRRC_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA С�����������Ϣ
*****************************************************************************/
typedef struct
{
    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32                  ulMeasResultFlg;

    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;

    /* 0: no CGI is available
       1: CGI is available
    */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucCgiResutlFlg;

    /* It carries the EVDO cell sector ID */
    VOS_UINT8                                               aucCgiResult[LRRC_CDMA_MEAS_CGI_RESULT];

    VOS_UINT16                                              usReserved;
    VOS_UINT16                                              usCellNum;
    CDMA_LRRC_CELL_MEAS_RESULT_STRU                         astCellResultList[LRRC_CDMA_CELL_MAX_NUM];
}CDMA_LRRC_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����̬CDMA HPRD�������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    CDMA_LRRC_MEAS_RESULT_STRU          stCdemaLrrcConnMeasResultInfo[LRRC_CDMA_BAND_MAX_NUM];
}CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMAϵͳ��LTE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usEarfcn;
    CDMA_LRRC_MEAS_BAND_WIDTH_ENUM_UINT8        ucMeasBandWidth;
    VOS_UINT8                                   ucRxLevMin;

    VOS_UINT8                                   ucRxLevMinOffset;
    VOS_UINT8                                   ucPeMax;
    VOS_UINT8                                   ucReserved;
    VOS_UINT8                                   ucPlmnNum;
    VOS_UINT32                                  ulPlmnId[CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM];
}CDMA_LRRC_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMAϵͳ��LTE�����б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulLteEarFcn; // num?
    CDMA_LRRC_CELL_INFO_STRU                    astLteCellInfo[CDMA_LRRC_LTE_EARFCN_MAX_NUM];
}CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE�������������Ϣ
*****************************************************************************/
typedef struct
{
    /* Ĭ����дֵ 0XFFFFFFFF */
    VOS_UINT32                                              ulPlmnId;
    VOS_UINT16                                              usCellId;

    /* [-141,0]*/
    VOS_INT16                                               sRsrp;
}LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE�����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usEarfcn;
    VOS_UINT8                                               aucReserved[1];
    VOS_UINT8                                               ucPlmnNum;
    LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU                    astCellResultInfo[CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM];
}LRRC_CDMA_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE������������б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCellResultNum;
    LRRC_CDMA_CELL_MEAS_RESULT_STRU                         astLteResult[CDMA_LRRC_LTE_EARFCN_MAX_NUM];
}LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_IDLE_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA IDLE С����Ϣ�б�
*****************************************************************************/
typedef struct
{
    /* 0xffff ��ʾ��Ч */
    VOS_UINT16                  usCellToReportCgi;
    VOS_UINT16                  usChannel;

    VOS_UINT8                   ucBand;

    VOS_UINT8                   ucCellReselectionPriority;
    VOS_UINT16                  usCellNum;
    VOS_UINT16                  ausCellPn[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}LRRC_CDMA_IDLE_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA IDLE HPRDС����Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    LRRC_CDMA_IDLE_CELL_INFO_STRU       astLrrcCdemaIdleCellInfo[LRRC_CDMA_CELL_MAX_NUM];
/* add for Balong CL begin */
#if (FEATURE_BALONG_CL == FEATURE_ON)
    VOS_UINT16                          usHighPrioNum;
    VOS_UINT8                           aucReserved[2];
#endif
/* add for Balong CL end */
}LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_IDLE_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA С�����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;

    /* 0: no CGI is available
       1: CGI is available
    */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucCgiResutlFlg;

    /* It carries the EVDO cell sector ID */
    VOS_UINT8                                               aucCgiResult[LRRC_CDMA_MEAS_CGI_RESULT];

    VOS_UINT16                                              usResered;
    VOS_UINT16                                              usCellNum;
    CDMA_LRRC_CELL_MEAS_RESULT_STRU                         astCellResultList[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}CDMA_LRRC_IDLE_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA HPRD�������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    CDMA_LRRC_IDLE_MEAS_RESULT_STRU     astLrrcCdemaIdleMeasResultInfo[LRRC_CDMA_CELL_MAX_NUM];
}CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_STOP_MEAS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA����ֹͣ������Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_CDMA_MEAS_TYPE_UINT8                               ucStopCmd;
    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               aucReserved[2];
}LRRC_CDMA_STOP_MEAS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA����ֹͣ������Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulStopMeasNum;
    LRRC_CDMA_STOP_MEAS_INFO_STRU                           astLrrcCdmaStopMeasInfo[LRRC_CDMA_SYSTEM_TYPE_BUTT];
}LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CONN_MEAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����CDMAָʾС������ԭ�������CONN
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_Meas_Cmd
             2���ӿ�Ŀǰ����ʹ��CONN̬����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU                 stLRrcCdmaHprdConnCellInfoList;
}LRRC_CDMA_CONN_MEAS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_CONN_MEAS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LRRCָʾС���������ԭ�������IDLE��CONN
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_Meas_Ind
             2���ӿ�Ŀǰ����ʹ��CONN̬����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;

    /* ��ʱ���� */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU               stCdmaLRrcHprdMeasResultList;
}CDMA_LRRC_CONN_MEAS_IND_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE����CDMA����ϵͳ����ѡ
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_System_Change_Req
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT8                                               ucBand;

    VOS_UINT16                                              usChannel;

    /* Cell Num must > 0 */
    VOS_UINT16                                              usCellNum;
    VOS_UINT16                                              ausCellPn[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}LRRC_CDMA_CELL_RESEL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LTE����ϵͳ����ѡ�ظ�
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8                  ucCellReselResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_CELL_RESEL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CELL_REDIR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE����CDMA����ϵͳ���ض���
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_System_Change_Req
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               ucBand;
    VOS_UINT16                                              usChannel;
}LRRC_CDMA_CELL_REDIR_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_CELL_REDIR_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LTE����ϵͳ���ض���ظ�
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8                  ucCellRedirResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_CELL_REDIR_CNF_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_IDLE_MEAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC����CDMAָʾС������ԭ�������IDLE̬
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_SIB8_Meas_Cmd
             2���ӿ�Ŀǰ����ʹ��IDLE̬����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               ucWindowSize;
    VOS_UINT8                                               ucReserved;

    /* CDMAϵͳ������Ӧ��С�������ڣ���λMS
       0:�����������һ�β�����������һ�β���һ��
       other:����һ��REQ�������ϱ�������� ��Ŀǰ�̶�Ϊ200ms
    */
    VOS_UINT32                                              ulPeriod;

    LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU                 stLRrcCdmaHprdIdleCellInfoList;
}LRRC_CDMA_IDLE_MEAS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_IDLE_MEAS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LRRCָʾС���������ԭ�������IDLE
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_Meas_Ind
             2���ӿ�Ŀǰ����ʹ��IDLE̬����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32                  ulMeasResultFlg;

    CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU               stCdmaLRrcHprdIdleMeasResultList;
}CDMA_LRRC_IDLE_MEAS_IND_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_MEAS_CELL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LTE���ڲ���LTEС��
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_RATMeas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU                      stCdmaLrrcMeasInfoList;
}CDMA_LRRC_MEAS_CELL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_MEAS_CELL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA�ϱ��������
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_RATMeas_Ind
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_MEAS_RESULT_FLAG_ENUM_UINT32                  ulReultFlag;

    LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU                    stLrrcMeasResultList;
}LRRC_CDMA_MEAS_CELL_IND_STRU;



/*****************************************************************************
 �ṹ��    : LRRC_CDMA_LTE_PRI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTEר�����ȼ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usLteEarfcn;
    VOS_UINT8                                               ucPri;
    VOS_UINT8                                               ucReserved;
}LRRC_CDMA_LTE_PRI_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_CDMA_PRI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMAר�����ȼ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;
    VOS_UINT8                                               ucPri;
}LRRC_CDMA_CDMA_PRI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_IDELMOBILITY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE���յ���ר�����ȼ���Ϣ
*****************************************************************************/
typedef struct
{
    /* ʣ��ʱ�� ��λ: S */
    VOS_UINT16                                              usT320LeftValue;
    VOS_UINT8                                               ucLtePriInfoNum;
    VOS_UINT8                                               ucCdmaPriInfoNum;

    LRRC_CDMA_LTE_PRI_INFO_STRU                             astrLrrcCdmaLtePriInfo[LTE_CDMA_LTE_PRI_INFO_MAX_NUM];
    LRRC_CDMA_CDMA_PRI_INFO_STRU                            astrLrrcCdmaCdmaPriInfo[LTE_CDMA_CDMA_PRI_INFO_MAX_NUM];
}LRRC_CDMA_IDELMOBILITY_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE���͸�CDMA��ר�����ȼ���Ϣ
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_Set_IdleModeMobilityCtrlInfo_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/


    LRRC_CDMA_IDELMOBILITY_INFO_STRU                        struLrrcCdmaIdleMobilityInfo;
}LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU;


typedef LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU    CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_STOP_MEAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA����ֹͣ����������
             1��ԭVIA�ӿ���MmcRatAPI_Stop_IRAT_Meas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU                      stLrrcCdmaStopMeasInfoList;
}LRRC_CDMA_STOP_MEAS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CDMA_LRRC_STOP_MEAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA��LTE����ֹͣ����������
             1��ԭVIA�ӿ���RatMmcAPI_Stop_IRAT_Meas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
}CDMA_LRRC_STOP_MEAS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_CDMA_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_GRR_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_CDMA_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_CDMA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_CDMA_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : LRrcCdmaInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRrcCdmaInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_CDMA_MSG_DATA                                       stMsgData;
}LRrcCdmaInterface_MSG;

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA����ֹͣ������������
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_System_Change_Abort_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32                ulLrrcCdmaSysChgStopReason;
}LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE��CDMA����ֹͣ������������
             1��ԭVIA�ӿ���MmcRatAPI_IRAT_System_Change_Abort_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32                ulLrrcCdmaSysChgStopReason;
}LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LTEֹͣϵͳ����ѡ�ظ�
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8                  ucCellReselResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LTEֹͣϵͳ���ض���ظ�
             1��ԭVIA�ӿ���RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8                  ucCellRedirResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_STOP_CELL_REDIR_CNF_STRU;

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

#endif /* end of LRrcCdmaInterface.h */
