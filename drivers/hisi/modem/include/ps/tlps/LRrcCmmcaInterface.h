

#ifndef __LRRC_CMMCA_INTERFACE_H__
#define __LRRC_CMMCA_INTERFACE_H__

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
/* LRRC��CMMCA֮�����Ϣ��ַ */
#define LRRC_CMMCA_MSG_HDR                        000000
#define CMMCA_LRRC_MSG_HDR                        050000


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    :LRRC_CMMCA_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :LRRC��CMMCA֮�����Ϣ
*****************************************************************************/
enum LRRC_CMMCA_MSG_TYPE_ENUM
{
    /* LRRC-> CMMCA CDMA MSG */
    /* LRRC-> CMMCA CDMA MSG: MMC_RAT_API_IRAT_MEAS_CMD */
    LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ                       = (LRRC_CMMCA_MSG_HDR + 0x00),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU */

    /* LRRC-> CMMCA CDMA MSG: MMC_RAT_API_IRAT_SYSTEM_CHG_REQ */
    LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_REQ                 = (LRRC_CMMCA_MSG_HDR + 0x01),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_REQ_STRU */

    /* LRRC-> CMMCA CDMA MSG:MMC_RAT_API_IRAT_SIB8_MEAS_CMD */
    LRRC_CMMCA_CDMA_MSG_IRAT_SIB8_MEAS_IND                  = (LRRC_CMMCA_MSG_HDR + 0x02),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_IRAT_SIB8_MEAS_IND_STRU */

    /* LRRC-> CMMCA CDMA MSG:  resverved */
    LRRC_CMMCA_CDMA_MSG_IRAT_SET_PRIINFO_REQ                = (LRRC_CMMCA_MSG_HDR + 0x03),      /* _H2ASN_MsgChoice  */

    /* LRRC-> CMMCA CDMA MSG:MMC_RAT_API_IRAT_RATMEAS_IND */
    LRRC_CMMCA_CDMA_MSG_IRAT_RATMEAS_IND                    = (LRRC_CMMCA_MSG_HDR + 0x04),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_IRAT_RATMEAS_IND_STRU */

    /* LRRC-> CMMCA CDMA MSG:MMC_RAT_API_STOP_IRAT_MEAS_CMD */
    LRRC_CMMCA_CDMA_MSG_STOP_IRAT_MEAS_REQ                  = (LRRC_CMMCA_MSG_HDR + 0x05),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_STOP_IRAT_MEAS_REQ_STRU */

    /* LRRC->CMMCA CDMA MSG:MMC_RAT_API_IRAT_SYSTEM_CHG_ABORT_CMD */
    LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_ABORT_CMD           = (LRRC_CMMCA_MSG_HDR + 0x06),      /* _H2ASN_MsgChoice LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_ABORT_CMD_STRU */

    /* CMMCA->LRRC CDMA MSG */
    /* CMMCA->LRRC CDMA MSG:RAT_MMC_API_IRAT_MEAS_IND */
    CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND                       = (CMMCA_LRRC_MSG_HDR + 0x00),      /* _H2ASN_MsgChoice CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU */

    /* CMMCA->LRRC CDMA MSG:RAT_MMC_API_IRAT_SYSTEM_CHG_RSP */
    CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP                 = (CMMCA_LRRC_MSG_HDR + 0x01),      /* _H2ASN_MsgChoice CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP_STRU */

    /* CMMCA->LRRC CDMA MSG:RAT_MMC_API_IRAT_SIB8_MEAS_IND */
    CMMCA_LRRC_CDMA_MSG_IRAT_SIB8_MEAS_IND                  = (CMMCA_LRRC_MSG_HDR + 0x02),      /* _H2ASN_MsgChoice CMMCA_LRRC_CDMA_MSG_IRAT_SIB8_MEAS_IND_STRU */

    /* CMMCA->LRRC CDMA MSG: */
    CMMCA_LRRC_CDMA_MSG_IRAT_SET_PRIINFO_REQ                = (CMMCA_LRRC_MSG_HDR + 0x03),      /* _H2ASN_MsgChoice  */

    /* CMMCA->LRRC CDMA MSG:RAT_MMC_API_IRAT_LTEMEAS_CMD */
    CMMCA_LRRC_CDMA_MSG_IRAT_LTEMEAS_REQ                    = (CMMCA_LRRC_MSG_HDR + 0x04),      /* _H2ASN_MsgChoice CMMCA_LRRC_CDMA_MSG_IRAT_LTEMEAS_REQ_STRU */

    /* CMMCA->LRRC CDMA MSG:RAT_MMC_API_STOP_IRAT_RATMEAS_CMD */
    CMMCA_LRRC_CDMA_MSG_STOP_IRAT_RATMEAS_REQ               = (CMMCA_LRRC_MSG_HDR + 0x05),      /* _H2ASN_MsgChoice CMMCA_LRRC_CDMA_MSG_STOP_IRAT_RATMEAS_REQ_STRU */

    LRRC_CMMCA_MSG_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_CMMCA_MSG_TYPE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : MMC_RAT_API_IRAT_MEAS_CMD
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CMMCAת��MMC_RAT_API_IRAT_MEAS_CMD��Ϣ��VIA
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* ����������VIA MMC_RAT_API_IRAT_MEAS_CMD �������� */
    VOS_UINT32                                              ulLen;
    VOS_UINT8                                               aucMsgData[4];
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU;

typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_REQ_STRU;
typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_IRAT_SIB8_MEAS_IND_STRU;
typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_IRAT_SET_PRIINFO_REQ_STRU;
typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_IRAT_RATMEAS_IND_STRU;
typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_STOP_IRAT_MEAS_REQ_STRU;
typedef LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_ABORT_CMD_STRU;

/*****************************************************************************
 �ṹ��    : CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CMMCAת��RAT_MMC_API_IRAT_MEAS_IND��Ϣ��LRRC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* ����������VIA RAT_MMC_API_IRAT_MEAS_IND �������� */
    VOS_UINT32                                              ulLen;
    VOS_UINT8                                               aucMsgData[4];
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU;


typedef CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU  CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP_STRU;
typedef CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU  CMMCA_LRRC_CDMA_MSG_IRAT_SIB8_MEAS_IND_STRU;
typedef CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU  CMMCA_LRRC_CDMA_MSG_IRAT_SET_PRIINFO_STRU;
typedef CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU  CMMCA_LRRC_CDMA_MSG_IRAT_LTEMEAS_REQ_STRU;
typedef CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU  CMMCA_LRRC_CDMA_MSG_STOP_IRAT_RATMEAS_REQ_STRU;



/*****************************************************************************
 �ṹ��    : LRRC_CMMCA_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_CMMCA_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32                         enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_CMMCA_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_CMMCA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_CMMCA_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : LRrcCmmcaInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRrcCmmcaInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_CMMCA_MSG_DATA                                       stMsgData;
}LRrcCmmcaInterface_MSG;


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

#endif /* end of LRrcCmmcaInterface.h */
