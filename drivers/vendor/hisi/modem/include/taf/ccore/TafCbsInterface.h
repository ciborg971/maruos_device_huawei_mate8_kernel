

#ifndef __TAFCBSINTERFACE_H__
#define __TAFCBSINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define  CBS_MAX_MSG_LEN                (1246)
#define  CBS_MIN_MSG_LEN                (1)
#define  CBS_MAX_MSG_ID_NUM             (100)

#define  GAS_CBS_MAX_CBPAGE_LEN         (88)                                    /*�㲥����Ϣһҳ����󳤶�*/

#define  CBS_MSGID_RANGE_MAX            (20)                                    /*������Ϣ�����б�ֶ�����*/

#define  RR_CBS_ETWS_SECURITY_INFO_LEN  (50) 

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����: TAF_CBS_MSG_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��: CBSģ��ͽ����֮�����ϢID
*****************************************************************************/
enum TAF_CBS_MSG_TYPE_ENUM
{
    ID_BMC_CBS_DATA_IND                 =  0x0001,                              /* _H2ASN_MsgChoice BMC_CBS_DATA_IND_STRU */
    ID_GAS_CBS_DATA_IND                 =  0x0003,                              /* _H2ASN_MsgChoice GAS_CBS_DATA_IND_STRU */
    ID_BMC_CBS_CFG_CNF                  =  0x0005,                              /* _H2ASN_MsgChoice BMC_CBS_CFG_CNF_STRU */
    ID_GAS_CBS_CFG_CNF                  =  0x0007,                              /* _H2ASN_MsgChoice GAS_CBS_CFG_CNF_STRU */
    ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND   =  0x0009,                              /* _H2ASN_MsgChoice RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU */
    ID_LRRC_CBS_DATA_IND                =  0x000B,                              /* _H2ASN_MsgChoice LRRC_CBS_DATA_IND_STRU */
    ID_RR_CBS_GS_STATUS_CHANGE_IND      =  0x000D,                              /* _H2ASN_MsgChoice RR_CBS_GS_STATUS_CHANGE_IND_STRU */
    ID_CBS_BMC_CFG_REQ                  =  0x0002,                              /* _H2ASN_MsgChoice CBS_BMC_CFG_REQ_STRU */
    ID_CBS_GAS_CFG_REQ                  =  0x0004,                              /* _H2ASN_MsgChoice CBS_GAS_CFG_REQ_STRU */
    ID_TAF_CBS_MSG_TYPE_BUTT            =  0xFFFF
};
typedef VOS_UINT16 TAF_CBS_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����: TAF_CBS_CFG_RSLT_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��: ���������CBS���ܵĽ��
*****************************************************************************/
enum TAF_CBS_CFG_RSLT_ENUM
{
    TAF_CBS_CFG_RSLT_SUCC               = 0,
    TAF_CBS_CFG_RSLT_FAIL,
    TAF_CBS_CFG_RSLT_BUTT
};
typedef VOS_UINT32   TAF_CBS_CFG_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����: TAF_CBS_GS_CHG_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��: ��������������
*****************************************************************************/
enum TAF_CBS_GS_CHG_TYPE_ENUM
{
    TAF_CBS_GS_CHG_TYPE_CHG_PLMN        = 0,                                    /* UE��PLMN�ı�*/
    TAF_CBS_GS_CHG_TYPE_CHG_SA          = 1,                                    /* UE�ķ������ı�*/
    TAF_CBS_GS_CHG_TYPE_CHG_CELL        = 2,                                    /* UE��С�����*/
    TAF_CBS_GS_CHG_TYPE_CHG_RAT         = 3,                                    /* UE��ϵͳ���(˫ģ�л�)*/
    TAF_CBS_GS_CHG_TYPE_NO_CHG          = 4,                                    /* UE��С��״̬δ�ı�*/
    TAF_CBS_GS_CHG_TYPE_CHG_BUTT
};
typedef  VOS_UINT8 TAF_CBS_GS_CHG_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: TAF_CBS_CFG_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��: ���ý�����CBS���ܼ���/ȥ����
*****************************************************************************/
enum TAF_CBS_CFG_ENUM
{
    TAF_CBS_CFG_ACTIVE                  = 0,
    TAF_CBS_CFG_DEACTIVE,
    TAF_CBS_CFG_BUTT
};
typedef  VOS_UINT32   TAF_CBS_CFG_ENUM_UINT32;



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
 �ṹ����: TAF_CBS_PLMN_ID_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: PLMN ID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}TAF_CBS_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ����: TAF_CBS_NETWORK_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ��ǰפ����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpSa         : 1;
    VOS_UINT32                          bitOpCellId     : 1;
    VOS_UINT32                          bitSpare        : 29;

    TAF_CBS_PLMN_ID_STRU                stCurPlmn;                              /* ��ǰ Plmn */
    VOS_UINT16                          usSa;                                   /* ��ǰ��������Ϣ  */
    VOS_UINT8                           aucRsv[2];                              /* �ֽڶ��뱣�� */
    VOS_UINT32                          ulCellId;                               /* ��ǰС��ID  */
}TAF_CBS_NETWORK_INFO_STRU;

/*****************************************************************************
 �ṹ����: BMC_CBS_DATA_IND_STRU,LRRC_CBS_DATA_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: WģCBS��Ϣ/ETWS��Ϣ����, LģETWS��Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣�����*/

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* ��ǰ������Ϣ */

    VOS_UINT16                          usCBMID;                                /* CBS��ϢID */

    /*aabbbbbb bbbbcccc, indicate Serial Number
    aa          GS
    bbbbbb      Message Code
    cccc        Update Number
    */
    VOS_UINT16                          usSerialNum;                            /* CBS��Ϣ���к� */

    /*aaaa bbbb,indicate Data-Coding-Scheme
    aaaa        Coding Group Bits
    bbbb        Use of bits 3..0
    */
    VOS_UINT8                           ucDataCodeScheme;                       /* ���ݱ��뷽ʽ */
    VOS_UINT8                           aucRsv[1];

    VOS_UINT16                          usCBDataLen;                            /* [CBS_MIN_MSG_LEN,CBS_MAX_MSG_LEN],CBS��Ϣ����,��λ���ֽ�*/
    VOS_UINT8                           aucCBData[4];                           /* CBS��Ϣ�壬REF:3GPP TS 23.041: CHAPTER 9.4.2.2.5 CBS Data*/
}BMC_CBS_DATA_IND_STRU,LRRC_CBS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ����: GAS_CBS_PAGE_DATA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: GģCBS��Ϣҳ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucData[GAS_CBS_MAX_CBPAGE_LEN];
}GAS_CBS_PAGE_DATA_STRU;

/*****************************************************************************
 �ṹ����: GAS_CBS_DATA_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: GģCBS��Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣�����*/

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* ��ǰ������Ϣ */

    VOS_UINT8                           ucPageNum;                              /* ��ǰCBS��Ϣ������Ϣҳ����*/
    VOS_UINT8                           aucRsv[3];

    GAS_CBS_PAGE_DATA_STRU              astPageData[1];                         /* ��ǰCBS��Ϣҳ�����б�, Refer to 23041 9.4.1.2 Message Parameter*/
}GAS_CBS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ����: CBS_MSGID_RANGE_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /* Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /* Cell broadcast message id value range to    */
}CBS_MSGID_RANGE_STRU;

/*****************************************************************************
 �ṹ����: CBS_BMC_CFG_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ֪ͨ�����CBS���ܼ���/ȥ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣����� */

    TAF_CBS_CFG_ENUM_UINT32             enCbsActive;                            /* CBS����� */
}CBS_BMC_CFG_REQ_STRU;

typedef CBS_BMC_CFG_REQ_STRU CBS_GAS_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ����: BMC_CBS_CFG_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����/ȥ����CBS���ܵĽ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣����� */

    TAF_CBS_CFG_RSLT_ENUM_UINT32        enRslt;                                 /* �ϲ� ԭ��֤ʵ��� */
}BMC_CBS_CFG_CNF_STRU;

typedef BMC_CBS_CFG_CNF_STRU GAS_CBS_CFG_CNF_STRU;


/*****************************************************************************
 �ṹ��    :    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :    �ϱ���֪ͨ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣����� */

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* ��ǰ������Ϣ */

    VOS_UINT16                          usWarnType;                             /* �澯���� */
    VOS_UINT16                          usMessageId;                            /* ��ϢID */
    VOS_UINT16                          usSerialNumber;                         /* ���к� */
    
    VOS_UINT8                           ucSecurityInfoPresent;                  /* ��ȫ��Ϣ�Ƿ����, VOS_TRUE:����, VOS_FALSE:������ */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucSecurityInfo[RR_CBS_ETWS_SECURITY_INFO_LEN];
}RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU;

/*****************************************************************************
 �ṹ����: RR_CBS_GS_STATUS_CHANGE_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����λ�ñ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* �ӽ��̱�ʶ,���ڶ�λ�ӽ��̣����� */
    
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType;                            /* �������������� */
    VOS_UINT8                           aucRsv[3];                              /* �ֽڶ��뱣�� */

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* ��ǰ������Ϣ */
}RR_CBS_GS_STATUS_CHANGE_IND_STRU;


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
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgID;                                /*_H2ASN_MsgChoice_Export TAF_CBS_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsg[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CBS_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}TAF_CBS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_CBS_MSG_DATA                    stMsgData;
} TafCbsInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/




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

#endif /* end of TafCbsInterface.h */
