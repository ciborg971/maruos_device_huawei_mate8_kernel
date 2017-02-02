

#ifndef __TAFCBACTX_H__
#define __TAFCBACTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "product_config.h"
#include  "MnMsgApi.h"


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

#define TAF_CBA_MAX_CBMID_NUM                               (20)                /* �����Լ�¼DOWNLOAD�㲥����Ϣ���͵ĸ������������ݻ����ļ�CBMID���� */

#define TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM            (5)                 /* ��Чʱ���������������ָ��MCC���� */

#define TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM                (30)                /* �����ETWS Primary Notify(��֪ͨ)��ʷ��¼������ */

#define TAF_CBA_MAX_CBS_RECORD_NUM                          (150)               /* �����CBS(����ETWS Secondary Notify)��ʷ��¼������ */

#define TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM     (2)                 /* ����û������õ�ETWS��MSG ID��Χ���� */

#define TAF_CBA_INVALID_MCC                                 (0xffffffff)        /* MCC����Чֵ */
#define TAF_CBA_INVALID_MNC                                 (0xffffffff)        /* MNC����Чֵ */


/*******************************************************************************
Э�鶨���ETWS CBS��ϢID�ķ�Χ: ��23041 9.4.1.2.2
4352 0x1100 ETWS CBS Message Identifier for earthquake warning message.
4353 0x1101 ETWS CBS Message Identifier for tsunami warning message.
4354 0x1102 ETWS CBS Message Identifier for earthquake and tsunami combined warning message.
4355 0x1103 ETWS CBS Message Identifier for test message.
          The UE silently discards this message. A UE specially designed
          for testing purposes may display its contents.
4356 0x1104 ETWS CBS Message Identifier for messages related to other emergency types.
4357 - 4359 0x1105 - 0x1107 ETWS CBS Message Identifier for future extension.
*******************************************************************************/
#define TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_FROM                (4352)
#define TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_TO                  (4359)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_CBA_CBSTATUS_ENUM_UINT8
 �ṹ˵��  :  �û����õ�CBS����ʹ�����
 1.��    ��   : 2012��03��17��
   ��    ��   : zhoujun 40661
   �޸�����   : ������ö������
*****************************************************************************/
enum TAF_CBA_CBSSTATUS_ENUM
{
    TAF_CBA_CBSTATUS_DISABLE             = 0x00,                                /* CBS����δʹ�� */
    TAF_CBA_CBSTATUS_W_ENABLE            = 0x01,                                /* Wģ��CBS����ʹ�� */
    TAF_CBA_CBSTATUS_G_ENABLE            = 0x02,                                /* Gģ��CBS����ʹ�� */
    TAF_CBA_CBSTATUS_WG_ENABLE           = 0x03,                                /* W��Gģ��CBS���ܾ�ʹ�� */
    TAF_CBA_CBSTATUS_BUTT                                                       /* ��Чֵ */
};
typedef VOS_UINT8 TAF_CBA_CBSTATUS_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_CBA_NET_RAT_TYPE_ENUM_UINT8
 �ṹ˵��  : ���뼼����ö��ֵ
 1.��    ��   : 2012��03��19��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum TAF_CBA_NET_RAT_TYPE_ENUM
{
    TAF_CBA_NET_RAT_TYPE_GSM,                                                   /* GSM���뼼�� */
    TAF_CBA_NET_RAT_TYPE_WCDMA,                                                 /* WCDMA���뼼�� */
    TAF_CBA_NET_RAT_TYPE_LTE,                                                   /* LTE���뼼�� */
    TAF_CBA_NET_RAT_TYPE_BUTT                                                   /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT8 TAF_CBA_NET_RAT_TYPE_ENUM_UINT8;


enum TAF_CBA_READ_SIM_FILES_FLG_ENUM
{
    TAF_CBA_READ_SIM_FILES_FLG_NULL                                      = 0x00,/* ��ʼ��ȡ���, ��ʾ����ȡ�κ�USIM�ļ� */
    TAF_CBA_READ_CBMI_FILE_FLG                                           = 0x01,/* ��ȡCBMI �ļ���� */
    TAF_CBA_READ_CBMIR_FILE_FLG                                          = 0x02,/* ��ȡCBMIR �ļ���� */
    TAF_CBA_READ_CBMID_FILE_FLG                                          = 0x04,/* ��ȡCBMID �ļ���� */
    TAF_CBA_READ_SIM_FILES_FLG_BUTT                                      = 0x08 /* ��Ч��� */
};
typedef VOS_UINT8 TAF_CBA_READ_SIM_FILES_FLG_ENUM_UINT8;
enum TAF_CBA_DUP_DETECT_CFG_ENUM
{
    TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE                       = 0,    /* ����Ҫ�ظ����, �����ϱ���Ӧ�õ�CBS(��ETWS), �����ص�USIM��CBS */
    TAF_CBA_DUP_DETECT_CFG_ONLY_DOWNLOAD_TYPE_ENABLE        = 1,    /* �������ص�USIM��CBS���ظ����, �ϱ���Ӧ�õ�CBS(��ETWS)�����ظ���� */
    TAF_CBA_DUP_DETECT_CFG_ALL_DISABLE                      = 2,    /* �������ظ����, �����ϱ���Ӧ�õ�CBS(��ETWS), �����ص�USIM��CBS */
    TAF_CBA_DUP_DETECT_CFG_BUTT                             = 3
};
typedef VOS_UINT8 TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8;


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
    VOS_UINT8                           ucEfCbmiExistFlg;                       /* USIM���Ƿ����EFCBMI �ļ��ı�־, VOS_TRUE: ����, VOS_FALSE: ������ */
    VOS_UINT8                           ucRsv;                                  /* 4�ֽڶ��� */
    VOS_UINT16                          usEfCbmiFileLen;                        /* ��EFCBMI �ļ��ж�ȡ�����ݵ�ʵ�ʳ���, EF�ļ�����(�Զ�������˵���ļ����ȣ��������ļ���˵�Ǽ�¼����) */
}TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucEfCbmirExistFlg;                      /* USIM���Ƿ����EFCBMIR �ļ��ı�־,  VOS_TRUE: ����, VOS_FALSE: ������  */
    VOS_UINT8                           ucRsv;                                  /* 4�ֽڶ��� */
    VOS_UINT16                          usEfCbmirFileLen;                       /* ��EFCBMIR �ļ��ж�ȡ�����ݵ�ʵ�ʳ��� , EF�ļ�����(�Զ�������˵���ļ����ȣ��������ļ���˵�Ǽ�¼����) */
}TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucEfCbmidExistFlg;                      /* USIM���Ƿ����EFCBMID �ļ��ı�־, VOS_TRUE: ����, VOS_FASLE: ������ */
    VOS_UINT8                           ucRsv;                                  /* 4�ֽڶ��� */
    VOS_UINT16                          usEfCbmidFileLen;                       /* ��EFCBMID �ļ��ж�ȡ�����ݵ�ʵ�ʳ���, EF�ļ�����(�Զ�������˵���ļ����ȣ��������ļ���˵�Ǽ�¼����) */
}TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU;
typedef struct
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU                      stEfCbmiFileInfo;   /* ��¼USIM�е�Cbmir�ļ���Ϣ */
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                     stEfCbmirFileInfo;  /* ��¼USIM�е�Cbmir�ļ���Ϣ */
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                     stEfCbmidFileInfo;  /* ��¼USIM�е�Cbmid�ļ���Ϣ */
}TAF_CBA_SIM_INFO_STRU;
typedef struct
{
    VOS_UINT16                          usCbmidNum;                             /* �������Ĺ㲥id�������� */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_NUM];        /* ����Ĺ㲥��Ϣid */
}TAF_CBA_CBMI_DOWNLOAD_LIST_STRU;


typedef struct
{
    TAF_CBA_CBSTATUS_ENUM_UINT8                             enCbStatus;         /* CBSҵ���Ƿ����ñ�־ */
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8                       enDupDetectCfg;     /* CBS�ظ����˿��� */

    VOS_UINT8                                               ucRptAppFullPageFlg; /* VOS_TRUE: �ϱ���ҳ��88���ֽ�; VOS_FALSE: �ϱ�ʵ����Ч�ֽ� */
    VOS_UINT8                                               ucRsv;              /* 4�ֽڶ��룬���� */


    TAF_CBA_CBMI_RANGE_LIST_STRU                            stCbMiRangeList;    /* �û�ָ���Ľ���/�ܾ���Ϣ��ID */

    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                         stCbMiDownloadList; /* sim��ָ��������Data Download��������Ϣ��ID */
}TAF_CBA_MS_CFG_CBS_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulSpecMccTimeLen;                       /* ��λ:��, �������Լ���ʱ��/��֪ͨ��MCC��ָ��Mcc����ʹ�ô��ظ����ʱ�� */
    VOS_UINT32                          ulOtherMccTimeLen;                      /* ��λ:��, �������Լ���ʱ��/��֪ͨ��MCC����ָ��Mcc����ʹ�ô��ظ����ʱ�� */
    VOS_UINT32                          aulSpecMcc[TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM];  /* ����������ص�MCC */
}TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU;
typedef struct
{
    VOS_UINT8                                               ucEnhDupDetectFlg;  /* DoCoMo��ǿ���ظ���ⶨ�������Ƿ񼤻�, VOS_TRUE:����,VOS_FALSE:δ���� */
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              ulNormalTimeLen;    /* ��λ:��, ��������δ����ʱʹ�ô��ظ����ʱ�� */
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU                stDupDetectTimeLen; /* �������Լ���ʱ���ظ����ʱ���������� */
}TAF_CBA_DUP_DETECT_CFG_STRU;
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_ETWS_MSGID_RANGE_STRU;


typedef struct
{
    VOS_UINT8                                               ucEtwsEnableFlg;    /* ETWS���Կ���, VOS_TRUE:����, VOS_FALSE:δ���� */
    VOS_UINT8                                               aucRsv[3];

    TAF_CBA_DUP_DETECT_CFG_STRU                             stDupDetectCfg;     /* �ظ����������Ϣ */

    VOS_UINT32                                              ulTempEnableCbsTimeLen;  /* ��λ:��, CBS����δ����ʱ,�յ���֪ͨ����ʱʹ��CBS�Խ��մ�֪ͨ��ʱ�� */

    TAF_CBA_ETWS_MSGID_RANGE_STRU                           astSpecEtwsMsgIdList[TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM];  /* �û����Ƶ�ETWS��MSG ID�ķ�Χ */
}TAF_CBA_MS_CFG_ETWS_INFO_STRU;



typedef struct
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;                              /* ���յ�����CBS��Ϣ�Ľ��뼼�� */
    VOS_UINT8                           ucTotalPage;                            /* ��ҳ����G��CBS��Ϣ��������Ϣ�� */
    VOS_UINT16                          usPageBitmap;                           /* �ѽ���ҳ��BitMap(G��CBS��Ϣ��������Ϣ) */

    VOS_UINT16                          usMsgID;                                /* ����֪ͨ/CBS��ϢID */
    VOS_UINT16                          usSN;                                   /* ����֪ͨ/CBS���к� */

    TAF_CBA_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          ulDupDetcTimeLen;                       /* ��Чʱ��N,��λ: ��, Ϊ0��ʾһֱ��Ч */
    VOS_UINT32                          ulRcvTimeTick;                          /* �յ���Ϣʱ��ʱ���, ȡ�� VOS_GetTick, ��λ: 10 ms */
}TAF_CBA_RECORD_STRU;
typedef struct
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;                       /* ����ģʽ */
    VOS_UINT8                           aucRsv3[3];                             /* 4�ֽڶ���  */

    TAF_CBA_PLMN_ID_STRU                stCurPlmn;                              /* PLMN ID  */

    VOS_UINT16                          usSa;                                   /* ��������Ϣ  */
    VOS_UINT8                           aucRsv2[2];                             /* 4�ֽڶ���  */

    VOS_UINT32                          ulCellId;                               /* С��ID  */
}TAF_CBA_NETWORK_INFO_STRU;


typedef struct
{
#if (FEATURE_ETWS == FEATURE_ON)

    VOS_UINT16                          usRcvEtwsPrimNtfNum;                    /* ETWS��֪ͨ��ʷ��¼���� */
    VOS_UINT8                           aucRsv[2];                              /* 4�ֽڶ���  */
    TAF_CBA_RECORD_STRU                 astRcvEtwsPrimNtfList[TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM];   /* ETWS��֪ͨ��ʷ��¼�� */
#endif

    VOS_UINT16                          usRcvCbsNum;                            /* CBS(����ETWS��֪ͨ)��ʷ��¼���� */
    VOS_UINT8                           aucRsv1[2];                             /* 4�ֽڶ���  */
    TAF_CBA_RECORD_STRU                 astRcvCbsList[TAF_CBA_MAX_CBS_RECORD_NUM];  /* CBS(����ETWS��֪ͨ)��ʷ��¼�� */
}TAF_CBA_RECORD_LIST_STRU;


typedef struct
{
    TAF_CBA_SIM_INFO_STRU               stCbsSimInfo;                           /* CBSģ��SIM�������Ϣ */
    TAF_CBA_MS_CFG_CBS_INFO_STRU        stCbsMsCfg;                             /* �û����õ�CBS��Ϣ */
#if (FEATURE_ETWS == FEATURE_ON)
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stEtwsMsCfg;                            /* �û����õ�ETWS����Ϣ */
#endif
    TAF_CBA_NETWORK_INFO_STRU           stCbsNetworkInfo;                       /* ��ǰ������Ϣ, ���е� RatType��ȡ��MMC;
                                                                                   PLMN��SA, CELL ID��δʹ�� */

    TAF_CBA_NETWORK_INFO_STRU           stOldNetworkInfo;                       /* ������ϴ� GS_STATUS_CHANGE_IND ��������Ϣ.
                                                                                   Ŀǰ�������ж���ϵͳ������GS CHG TYPE */

    TAF_CBA_RECORD_LIST_STRU            stRcvRecordList;                        /* CBS��ETWS��ʷ��¼��Ϣ */
}TAF_CBA_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID TAF_CBA_InitSimInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitCbmiRangeList(VOS_VOID);

VOS_VOID  TAF_CBA_InitCbsMsCfgInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitOldNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitRecordList(VOS_VOID);

VOS_VOID  TAF_CBA_InitCtx(VOS_VOID);

TAF_CBA_CTX_STRU* TAF_CBA_GetCbaCtx(VOS_VOID);

TAF_CBA_SIM_INFO_STRU* TAF_CBA_GetSimInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU* TAF_CBA_GetEfCbmiInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU* TAF_CBA_GetEfCbmiRangeInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU* TAF_CBA_GetEfCbmidInfo(VOS_VOID);


TAF_CBA_MS_CFG_CBS_INFO_STRU* TAF_CBA_GetMsCfgCbsInfo(VOS_VOID);

TAF_CBA_CBSTATUS_ENUM_UINT8 TAF_CBA_GetCbsStatus(VOS_VOID);
VOS_VOID TAF_CBA_SetCbsStatus(
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus
);

VOS_VOID TAF_CBA_SetDupDetectCfg(
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enTmpDupDetectCfg
);

TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8 TAF_CBA_GetDupDetectCfg(VOS_VOID);


VOS_VOID TAF_CBA_SetRptAppFullPageFlg(
    VOS_UINT8                           ucTmpRptAppFullPageFlg
);

VOS_UINT8 TAF_CBA_GetRptAppFullPageFlg(VOS_VOID);



TAF_CBA_CBMI_DOWNLOAD_LIST_STRU* TAF_CBA_GetCbmiDownloadList(VOS_VOID);

VOS_UINT16 TAF_CBA_GetCbmiDownloadNum(VOS_VOID);

TAF_CBA_CBMI_RANGE_LIST_STRU* TAF_CBA_GetCbMiRangeList(VOS_VOID);

TAF_CBA_CBMI_RANGE_STRU* TAF_CBA_GetCbmiRangeListHead(VOS_VOID);

VOS_UINT16 TAF_CBA_GetCbmiRangNum(VOS_VOID);

VOS_VOID TAF_CBA_SetCbmiRangeNum(
    VOS_UINT16                          usCbmiRangNum
);

#if (FEATURE_ETWS == FEATURE_ON)
VOS_VOID TAF_CBA_InitEtwsMsCfgInfo(VOS_VOID);

TAF_CBA_MS_CFG_ETWS_INFO_STRU* TAF_CBA_GetMsCfgEtwsInfo(VOS_VOID);

VOS_VOID TAF_CBA_SetMsCfgEtwsInfo(
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstMsCfgEtwsInfo
);

VOS_VOID TAF_CBA_SetEtwsEnableFlg(
    VOS_UINT8                           ucEtwsEnableFlg
);

VOS_UINT32 TAF_CBA_GetEtwsEnableFlg(VOS_VOID);

VOS_VOID  TAF_CBA_SetEnhDupDetcFlg(
    VOS_UINT8       ucDetcFlg
);

VOS_UINT8  TAF_CBA_GetEnhDupDetcFlg(VOS_VOID);

VOS_UINT32  TAF_CBA_GetNormalDupDetcTimeLen(VOS_VOID);

TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU* TAF_CBA_GetEnhDupDetcTimeLenCfg(VOS_VOID);

TAF_CBA_ETWS_MSGID_RANGE_STRU* TAF_CBA_GetUserSpecEtwsMsgIdList(VOS_VOID);

VOS_UINT16 TAF_CBA_GetRcvEtwsPrimNtfNum(VOS_VOID);

VOS_VOID TAF_CBA_SetRcvEtwsPrimNtfNum(
    VOS_UINT16                          usEtwsPrimNtfNum
);

TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvEtwsPrimNtfList(VOS_VOID);
#endif


TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetNetworkInfo(VOS_VOID);

TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetOldNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_SetOldNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkinfo
);

TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetNetRatType(VOS_VOID);

VOS_VOID TAF_CBA_SetNetRatType(
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetMode
);

TAF_CBA_PLMN_ID_STRU* TAF_CBA_GetCurrPlmn(VOS_VOID);

TAF_CBA_RECORD_LIST_STRU* TAF_CBA_GetRcvRecordListInfo(VOS_VOID);

VOS_UINT16 TAF_CBA_GetRcvCbsNum(VOS_VOID);

VOS_VOID TAF_CBA_SetRcvCbsNum(
    VOS_UINT16                          usNewRcvCbsNum
);

TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvCbsList(VOS_VOID);

VOS_VOID TAF_CBA_Init(VOS_VOID);

VOS_VOID TAF_CBA_UpdateTempEnableCbsTimerLen(VOS_VOID);


#endif



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

#endif /* end of TafCbaCtx.h */
