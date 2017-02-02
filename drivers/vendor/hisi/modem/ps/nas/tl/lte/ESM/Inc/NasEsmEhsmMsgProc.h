

#ifndef _NASESMEHSMMSGPROC_H
#define _NASESMEHSMMSGPROC_H



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "ehsm_esm_pif.h"
#include    "NasEsmPublic.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* ESM�����EHRPD�µ�PDN������Ϣ����ֵ */
#define NAS_ESM_EHRPD_PDN_MAX_NUM                                       11

/* ESM�ڻָ����ع����е�һ�η��ͼ���ȱʡ����ʧ�� */
#define NAS_ESM_FIRST_FAIL_TIME                                         1

/* ESM��EHRPD���ػָ�������������ȱʡ����ACP����ʧ�ܵ������� */
#define NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES                          5

/* ��ȡEHRPDʵ��ȫ�ֱ�����ַ�궨�� */
#define NAS_ESM_GET_EHRPD_ENTITY_ADDR()                     (&g_stEsmEhrpdEntity)

/* ��ȡ������EHRPDʵ��״̬ */
#define NAS_ESM_GET_EHRPD_ENTITY_STATE()                    (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->enEntityState)
#define NAS_ESM_SET_EHRPD_ENTITY_STATE(state)               (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->enEntityState = (state))

/* ��ȡEHRPDʵ��������ʹ�õ�PDN�����궨�� */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()            (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->ucEhrpdPdnTotalNum)

/* ��ȡ����Ϊi��EHRPD PDNʵ���ַ */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i)                (&(NAS_ESM_GET_EHRPD_ENTITY_ADDR()->astEhrpdPdnEntityList[i]))

/* ��ȡ����������Ϊi��EHRPD PDNʵ���attach flag��ַ */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i)                   (NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i)->ucAttachPdnFlag)
#define NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i, ucAttachFlag)     (NAS_ESM_GET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i) = (ucAttachFlag))



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : NAS_ESM_EHRPD_ENTITY_STATE_ENUM
 �ṹ˵��  : ESM��EHRPDʵ��״̬
*****************************************************************************/
enum NAS_ESM_EHRPD_ENTITY_STATE_ENUM
{
    /* �ȴ��ָ�̬ */
    NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER                      = 0x00,

    /* HANDOVER ATTACH��PDN����δ�յ�������Ӧ */
    NAS_ESM_EHRPD_ENTITY_STATE_ATTACH_PDN_REQ_NOT_RCV_CN_RSP      = 0X01,

    /* �Ѿ��յ�������ĵ�һ��ȱʡ���ؼ������� */
    NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ   = 0x02,

    NAS_ESM_EHRPD_ENTITY_STATE_BUTT
};
typedef VOS_UINT8  NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_ESM_PDN_RECONNECT_RESULT_ENUM
 �ṹ˵��  : ESM��EHRPD PDN���ӻָ����
*****************************************************************************/
enum NAS_ESM_PDN_RECONNECT_RESULT_ENUM
{
    NAS_ESM_PDN_RECONNECT_RESULT_SUCC             = 0x00,   /* �ָ��ɹ� */
    NAS_ESM_PDN_RECONNECT_RESULT_FAIL             = 0x01,   /* �ָ�ʧ�� */

    NAS_ESM_PDN_RECONNECT_RESULT_BUTT
};
typedef VOS_UINT8  NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : EHSM_ESM_MSG_HEADER_STRU
 �ṹ˵��  : EHSMģ�鷢��ESMģ����Ϣͷ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EHSM_ESM_PIF_MSG_TYPE_ENUM_UINT16   enMsgId;
    VOS_UINT16                          usOpId;
} EHSM_ESM_MSG_HEADER_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ESM_EHRPD_NW_MSG_RECORD_STRU
 �ṹ˵��  : EHRPDʵ���¼�ķ��������տ���Ϣ�����Ϣ
*****************************************************************************/
typedef struct
{
    /* SM����CN�Ŀտ���Ϣ���ͣ�Ŀǰֻ���¼����ȱʡ����ACP����������������չ */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;
    VOS_UINT8                           ucSendFailTimes;    /* ����ʧ�ܴ��� */
    VOS_UINT8                           aucRsv[2];          /* ���� */

    /* L�»ָ����ع����м�¼����NW��Ϣ��OPID��Ŀǰֻ���¼����ȱʡ����ACP�ģ���������������չ  */
    VOS_UINT32                          ulNwMsgOpId;

} NAS_ESM_EHRPD_NW_MSG_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU
 �ṹ˵��  : ESM�ڲ���¼��EHRPD�µ�PDN������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpApn          :1;
    VOS_UINT32                          bitOpApnAmbr      :1;
    VOS_UINT32                          bitOpPcoIpv4Item  :1;
    VOS_UINT32                          bitOpPcoIpv6Item  :1;
    VOS_UINT32                          bitOpSpare        :28;

    VOS_UINT32                          ulBitCid;                     /* CID                                   */
    VOS_UINT32                          ulEpsbId;                     /* ����ID                                */
    EHSM_ESM_PDN_ADDR_STRU              stPdnAddr;
    APP_ESM_APN_INFO_STRU               stApn;                        /* APN��ʽҪע�⣬�˴������ΪESM�ڲ�ʹ�õ�APN��ʽ */
    EHSM_ESM_APN_AMBR_STRU              stApnAmbr;
    EHSM_ESM_PCO_IPV4_ITEM_STRU         stPcoIpv4Item;
    EHSM_ESM_PCO_IPV6_ITEM_STRU         stPcoIpv6Item;
} NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_EHRPD_PDN_ENTITY_STRU
 �ṹ˵��  : ESM�ڲ�����ÿ��EHRPD���ص�ʵ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsedFlag;         /* ��PDNʵ���Ƿ�����: 1���ã�0δ����   */
    VOS_UINT8                           ucAttachPdnFlag;    /* ��PDN�Ƿ���ע��PDN: 1�ǣ�0����        */
    VOS_UINT8                           ucIsOnReconnFlag;   /* ��PDNʵ���Ƿ��ڳ��ػָ�������       */
    VOS_UINT8                           ucRsv;

    VOS_UINT32                          ulHandoverEpsbId;   /* L�»ָ����������ĳ���ID             */

    NAS_ESM_EHRPD_NW_MSG_RECORD_STRU    stNwMsgRecord;      /* �տ���Ϣ��ؼ�¼                      */
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /* ��ʱ��ʹ����Ϣ                        */
    NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU stEhPdnContextInfo; /* EHRPD������������Ϣ                   */
} NAS_ESM_EHRPD_PDN_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_EHRPD_ENTITY_STRU
 �ṹ˵��  : ESM���������EHRPDʵ��ṹ
*****************************************************************************/
typedef struct
{
    NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8         enEntityState;      /* EHRPDʵ��״̬ */

    /* EHRPDʵ���м�¼��PDN����������������¼PDNʵ���б����ж��ٸ�ʵ�屻ʹ��
    ��ע����ǣ�ʹ�õĲ�һ����ǰucEhrpdPdnTotalNum�������ֻ��һ������ */
    VOS_UINT8                                     ucEhrpdPdnTotalNum;
    VOS_UINT8                                     aucRsv[2];          /* ����                                */

    /* LTE�¼�¼��EHRPD����ʵ����Ϣ�б� */
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                 astEhrpdPdnEntityList[NAS_ESM_EHRPD_PDN_MAX_NUM];
} NAS_ESM_EHRPD_ENTITY_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU
 �ṹ˵��  : ESM��OM����Ŀ�ά�ɲ��PDNʵ����Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8         enEntityState;      /* EHRPDʵ��״̬ */
    VOS_UINT8                                     ucEntityIndex;      /* ��PDNʵ��������ţ���Χ0-10 */
    VOS_UINT8                                     ucRsv[2];
    /* LTE�¼�¼��EHRPD����ʵ�� */
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                 stEhPdnEntityInfo;
} NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU
 �ṹ˵��  : ESM��OM����Ŀ�ά�ɲ��PDNʵ��������Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    VOS_UINT32                                    ulEhrpdPdnTotalNum;
} NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

extern NAS_ESM_EHRPD_ENTITY_STRU        g_stEsmEhrpdEntity;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ESM_EhsmMsgDistr(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_InitEhrpdEntity(VOS_VOID);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoMsgProc(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_EhsmClearAllBearerNotifyMsgProc(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoConnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoModifiedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID);
extern VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID);
extern VOS_UINT32 NAS_ESM_AllocPdnIndexInEhrpdEntity(
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SaveEhrpdPdnInfo(
    VOS_UINT32                          ulIndex,
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_DeleteEhrpdPdnEntityInfo(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(
    APP_ESM_APN_INFO_STRU              *pstApn,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetAttachPdnInEhrpdEntity(
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetAttachCidInEhrpdEntity(
    VOS_UINT32                         *pulCid
);
extern VOS_UINT32 NAS_ESM_GetNextReconnectEhrpdPdn(
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_PerformEhrpdPdnReconnect(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd
);
extern VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
);
extern VOS_UINT32 NAS_ESM_IsBackOffAllowedToReconn(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_UINT32 NAS_ESM_CheckAllowedPdnEntityToReconnect(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverSuccProc(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverFailProc(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(
    VOS_UINT32                          ulOpId
);
extern VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(
    VOS_UINT32                          ulOpId
);
extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulAttachPdnFlag
);
extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(
    VOS_UINT32                                    ulIndex,
    NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8       enResult
);
extern VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID);
extern VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID);
extern VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/
#endif


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

#endif
