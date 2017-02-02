

#ifndef __TAFCBAMNTN_H__
#define __TAFCBAMNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbaProcNvim.h"
#include  "TafMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 �궨��
*****************************************************************************/


#define TAF_CBA_MNTN_INFO_HEADER_LEN                        (24)                /* ��ά�ɲ�ṹ��ͷ������,
                                                                                   TAF_CBA_MNTN_INFO_STRU�ṹ�в���UNION���ֵĳ��� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_CBA_OM_MSG_ID_ENUM
{
    TAF_CBA_OM_MSG_LOG_INFO                                 = ID_TAF_MNTN_MSG_CBA_BASE,            /* _H2ASN_MsgChoice TAF_CBA_LOG_INFO_STRU */ /* CBA ģ��LOG INFO */

    TAF_CBA_OM_MSG_DUP_ETWS_PRIM_NTF_RECORD,                                    /* _H2ASN_MsgChoice TAF_CBA_LOG_DUP_RECORD_STRU */ /* �ظ�ETWS��֪ͨ��¼ */
    TAF_CBA_OM_MSG_DUP_CBS_RECORD,                                              /* _H2ASN_MsgChoice TAF_CBA_LOG_DUP_RECORD_STRU */ /* �ظ�CBS��¼ */

    TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,                                   /* _H2ASN_MsgChoice TAF_CBA_LOG_SAVE_RECORD_STRU */ /* ����ETWS��֪ͨ��¼ */
    TAF_CBA_OM_MSG_SAVE_CBS_RECORD,                                             /* _H2ASN_MsgChoice TAF_CBA_LOG_SAVE_RECORD_STRU */ /* ����CBS��¼ */

    TAF_CBA_OM_MSG_DEL_ETWS_PRIM_RECORD,                                        /* _H2ASN_MsgChoice TAF_CBA_LOG_DEL_RECORD_STRU */ /* ɾ��ETWS��֪ͨ��¼ */
    TAF_CBA_OM_MSG_DEL_DEL_CBS_RECORD,                                          /* _H2ASN_MsgChoice TAF_CBA_LOG_DEL_RECORD_STRU */ /* ɾ��CBS��¼ */

    TAF_CBA_OM_MSG_CBMI_DOWNLOAD_LIST,                                          /* _H2ASN_MsgChoice TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU */ /* CBMI DOWNLOAD list������ */
    TAF_CBA_OM_MSG_CBMI_RANGE_LIST,                                             /* _H2ASN_MsgChoice TAF_CBA_LOG_CBMI_RANGE_LIST_STRU */ /* CBMI RANGE List������ */

    TAF_CBA_OM_MSG_NVIM_INFO,                                                   /* _H2ASN_MsgChoice TAF_CBA_LOG_NVIM_INFO_STRU */ /* CBS���NV��Ϣ */

    TAF_CBA_OM_MSG_BUTT
};
typedef VOS_UINT32  TAF_CBA_OM_MSG_ID_ENUM_UINT32;


enum TAF_CBA_OM_LOG_ID_ENUM
{
    TAF_CBA_OM_LOG_RCV_PRIM_NTF_WHEN_ETWS_DISABLE,                              /* �յ�ETWS��֪ͨʱ ETWS ���Թر� */
    TAF_CBA_OM_LOG_ETWS_PRIM_NTF_MSGID_INVALID,                                 /* ��֪ͨ��ϢID��Ч */
    TAF_CBA_OM_LOG_CBS_MSGID_INVALID,                                           /* CBS��ϢID��Ч */
    TAF_CBA_OM_LOG_TICK_ERROR,                                                  /* VOS TICK����ȷ */
    TAF_CBA_OM_LOG_PAGEINDEX_INVALID,                                           /* PAGEINDEX��Ч */
    TAF_CBA_OM_LOG_PAGELEN_INVALID,                                             /* PAGELEN��Ч */

    TAF_CBA_OM_LOG_BUTT
};
typedef VOS_UINT32  TAF_CBA_OM_LOG_ID_ENUM_UINT32;


enum TAF_CBA_OM_DEL_REASON_ENUM
{
    TAF_CBA_OM_DEL_REASON_LIST_FULL,                                            /* ��¼����ɾ����¼ */
    TAF_CBA_OM_DEL_REASON_TIMEOUT,                                              /* ��¼��ʱɾ����¼ */
    TAF_CBA_OM_DEL_REASON_GS_CHG,                                               /* GS�仯ɾ����¼ */
    TAF_CBA_OM_DEL_REASON_USER,                                                 /* �û���������ɾ����¼ */

    TAF_CBA_OM_DEL_REASON_BUTT
};
typedef VOS_UINT8  TAF_CBA_OM_DEL_REASON_ENUM_UINT8;


enum TAF_CBA_OM_SAVE_TYPE_ENUM
{
    TAF_CBA_OM_SAVE_TYPE_RECORD_FULL,                                           /* CBS��¼���� */
    TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD,                                         /* ׷��һ��CBS��¼ */
    TAF_CBA_OM_SAVE_TYPE_UPDATE_RECORD_BITMAP,                                  /* ���½���ҳ��BITMAP */
    TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,                                        /* ����ԭCBS��¼ */
    TAF_CBA_OM_SAVE_TYPE_BUTT
};
typedef VOS_UINT8  TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8;

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


typedef struct
{
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId;
}TAF_CBA_LOG_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usPageBitmap;                           /* �ѽ���ҳ��BitMap(G��CBS��Ϣ��������Ϣ) */
    VOS_UINT16                          usMsgID;                                /* ����֪ͨ/CBS��ϢID */
    VOS_UINT16                          usSN;                                   /* ����֪ͨ/CBS���к� */
    VOS_UINT8                           aucRsv[2];
}TAF_CBA_LOG_DUP_RECORD_STRU;
typedef struct
{
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT16                          usMsgID;                                /* ����֪ͨ/CBS��ϢID */
    VOS_UINT16                          usSN;                                   /* ����֪ͨ/CBS���к� */
    VOS_UINT32                          ulDupDetcTimeLen;                       /* ��Чʱ��N,��λ: ��, Ϊ0��ʾһֱ��Ч */
    VOS_UINT32                          ulRcvTimeTick;                          /* �յ���Ϣʱ��ʱ���, ȡ�� VOS_GetTick, ��λ: 10 ms */
    VOS_UINT32                          ulCurrTick;
}TAF_CBA_LOG_DEL_RECORD_STRU;


typedef struct
{
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;                             /* �������� */
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usRecordNum;                            /* �µļ�¼���� */

    VOS_UINT32                          ulDupDetcTimeLen;                       /* ��Чʱ��N,��λ: ��, Ϊ0��ʾһֱ��Ч */
}TAF_CBA_LOG_SAVE_RECORD_STRU;
typedef struct
{
    VOS_UINT16                          usCbmidNum;                             /* �������Ĺ㲥id�������� */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_NUM];        /* ����Ĺ㲥��Ϣid */
}TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU;


typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /* С���㲥��ϢID�Ŀ�ʼ���  */
    VOS_UINT16                          usMsgIdTo;                              /* С���㲥��ϢID�Ľ������ */
}TAF_CBA_LOG_CBMI_RANGE_STRU;


typedef struct
{
    VOS_UINT16                          usCbmirNum;                             /* С���㲥��Ϣ��ID���� */
    VOS_UINT8                           aucRsv[2];
    TAF_CBA_LOG_CBMI_RANGE_STRU         astCbmiRange[TAF_CBA_MAX_CBMID_RANGE_NUM]; /* С���㲥��Ϣ�ķ�Χ��Ϣ */
}TAF_CBA_LOG_CBMI_RANGE_LIST_STRU;


typedef struct
{
    TAF_CBA_CBS_SERVICE_PARM_STRU       stCbsServiceParam;
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stEtwsMsCfg;                            /* �û����õ�ETWS����Ϣ */
}TAF_CBA_LOG_NVIM_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    TAF_CBA_OM_MSG_ID_ENUM_UINT32                           enMsgId;            /* ��Ϣ���� */      /* _H2ASN_Skip */

    union
    {
        TAF_CBA_LOG_INFO_STRU                               stLogInfo;          /* ��ά�ɲ�LOG��Ϣ */
        TAF_CBA_LOG_DUP_RECORD_STRU                         stDupRecordInfo;    /* ��ά�ɲ��ظ���¼��Ϣ */
        TAF_CBA_LOG_DEL_RECORD_STRU                         stDelRecordInfo;    /* ��ά�ɲ�ɾ����¼��Ϣ */
        TAF_CBA_LOG_SAVE_RECORD_STRU                        stSaveRecordInfo;   /* ��ά�ɲⱣ���¼��Ϣ */
        TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU                 stCbmiDownloadList; /* ��ά�ɲ�CBMID LIST��Ϣ */
        TAF_CBA_LOG_CBMI_RANGE_LIST_STRU                    stCbmiRangeList;    /* ��ά�ɲ�CBMIR LIST��Ϣ */
        TAF_CBA_LOG_NVIM_INFO_STRU                          stCbsNvimInfo;      /* CBS���NV��Ϣ */
    }u;
}TAF_CBA_MNTN_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucReserved1[3];
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;
 }TAF_CBA_MNTN_DCS_DECODE_HOOK_STRU;

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
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CBA_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_CBA_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_CBA_OM_MSG_DATA                 stMsgData;
}TafCbaMntn_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/

/* Deleted by wx270776 for OM�ں�, 2015-6-28, begin */
/* Deleted by wx270776 for OM�ں�, 2015-6-28, end */

VOS_VOID TAF_CBA_SndOmLogInfo(
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId
);

VOS_VOID TAF_CBA_SndOmDeledRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason,
    TAF_CBA_RECORD_STRU                *pstDelRecord
);


VOS_VOID TAF_CBS_SndOmSavedRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType,
    TAF_CBA_RECORD_STRU                *pstNewRecord,
    VOS_UINT16                          usRecordNum
);

VOS_VOID TAF_CBA_SndOmDupRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_RECORD_STRU                *pstOldRecord
);

VOS_VOID TAF_CBA_SndOmCbmiDownloadListInfo(VOS_VOID);

VOS_VOID TAF_CBA_SndOmCbmiRangeList(VOS_VOID);

VOS_VOID TAF_CBA_SndOmNvimInfo(VOS_VOID);


#endif

/* Deleted TAF_CBA_SndOmDcsInfo */

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

#endif /* end of TafCbaMntn.h */
