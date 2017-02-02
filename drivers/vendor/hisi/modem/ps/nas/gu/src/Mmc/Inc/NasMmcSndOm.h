
#ifndef _NAS_MMC_SND_OM_H
#define _NAS_MMC_SND_OM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasMmcCtx.h"
#include  "NasMmlLib.h"
#include  "NasMmSublayerDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM
{
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_RUNNING_CONTEXT,                               /* ���MMC������������ */
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_FSM_STACK,                                     /* ���MMC��״̬��ջ����*/
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_FSM_BUTT
};
typedef VOS_UINT32 NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MMC_OM_MSG_ID_ENUM_U32
 �ṹ˵��  : MMC���͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : MMC���͸�OM�Ŀ�ά�ɲ���ϢIDö��
*****************************************************************************/
enum NAS_MMC_OM_MSG_ID_ENUM
{
    /* MMC���͸�OM����Ϣ */
    MMCOM_LOG_FSM_INFO_IND                          = 0x1000,      /*_H2ASN_MsgChoice  NAS_MMC_LOG_FSM_INFO_STRU */
    MMCOM_LOG_GUTI_INFO_IND                         = 0x1001,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_GUTI_INFO_STRU */
    MMCOM_LOG_BUFFER_MSG_INFO_IND                   = 0x1002,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_BUffER_MSG_INFO_STRU */
    MMCOM_LOG_PLMN_SELECTION_LIST                   = 0x1003,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU */
    MMCOM_LOG_INTER_MSG_INFO_IND                    = 0x1004,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_INTER_MSG_INFO_STRU */
    MMCOM_LOG_DRX_TIMER_STATUS_IND                  = 0x1005,
    MMCOM_LOG_DPLMN_LIST                            = 0x1006,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_DPLMN_LIST_STRU */
    MMCOM_LOG_NPLMN_LIST                            = 0x1007,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_NPLMN_LIST_STRU */
    MMCOM_LOG_AS_PLMN_SELECTION_LIST                = 0x1008,

    MMCOM_LOG_RPLMN_RELATED_INFO                    = 0x100A,
    MMCOM_LOG_FORBIDDEN_PLMN_RELATED_INFO           = 0x100B,
    MMCOM_LOG_RPLMN_CFG_INFO                        = 0x100C,

    MMCOM_LOG_HISTORY_RELATED_INFO                  = 0x100D,

    MMCOM_LOG_FSM_PLMN_SELECTION_CTX_RELATED_INFO   = 0x1020,
    MMCOM_LOG_FSM_L1_MAIN_CTX_RELATED_INFO          = 0x1021,

    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    MMCOM_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO   = 0x1024,
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

    MMCOM_LOG_MMC_TIMER_STATUS                      = 0x2000 ,  /*_H2ASN_MsgChoice  NAS_MMC_TIMER_INFO_STRU */

    MMCOM_LOG_MMC_PLATFORM_RAT_CAP                  = 0x3000 ,  /*_H2ASN_MsgChoice  NAS_MMC_TIMER_INFO_STRU */

    /* ������Ϣֻ��������ʱ��ȡNV�����USIM API��ȡ��ȫ�ֱ��������ڴӿ�����ʼ�Ļط� */
    MMCOM_FIXED_PART_CONTEXT                        = 0xaabb , /*_H2ASN_MsgChoice  NAS_MMC_FIXED_CONTEXT_MSG_STRU */
    MMCOM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY     = 0xaaaa ,     /*_H2ASN_MsgChoice  NAS_MMC_SDT_MSG_STRU */
    MMCOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MMC_OM_MSG_ID_ENUM_U32;

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
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulTopState;
}NAS_MMC_LOG_FSM_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_LMM_GUTI_STRU                   stGutiMsg;
}NAS_MMC_LOG_GUTI_INFO_STRU;
#endif



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    NAS_MMC_MSG_QUEUE_STRU              stMsgQueue;
}NAS_MMC_LOG_BUffER_MSG_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_LOG_INTER_MSG_INFO_STRU
 �ṹ˵��  : �ڲ���Ϣ��������֪ͨ
 1.��    ��   : 2012��4��12��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucFullFlg;
    VOS_UINT8                           ucMsgLenValidFlg;
    VOS_UINT8                           aucReserve[2];
}NAS_MMC_LOG_INTER_MSG_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT16                                              usDplmnListNum;
    VOS_UINT8                                               aucReserve[2];
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                   astDPlmnList[NAS_MMC_MAX_CFG_DPLMN_NUM];
}NAS_MMC_LOG_DPLMN_LIST_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT16                                              usNplmnListNum;
    VOS_UINT8                                               aucReserve[2];
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                   astNPlmnList[NAS_MMC_MAX_CFG_NPLMN_NUM];
}NAS_MMC_LOG_NPLMN_LIST_STRU;
typedef struct
{
    VOS_UINT8                                               aucImeisv[NAS_MML_MAX_IMEISV_LEN];          /* IMEISV */
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;                            /* MMC��ǰ����ģʽ,�Զ�ģʽ���ֶ�ģʽ*/
    NAS_MML_MS_NETWORK_CAPACILITY_STRU                      stMsNetworkCapability;                  /* MS network capability*/
    VOS_UINT8                                               ucPsAutoAttachFlg;                          /* PS�Զ�Attach��־en_NV_Item_Autoattach */
    NAS_MML_EQUPLMN_INFO_STRU                               stEquPlmnInfo;                              /* EQUPLMN��Ϣ */
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                         stBGSrchCfg;
    VOS_UINT32                                              ulQuickStartFlag;
} NAS_MMC_FIXED_CONTEXT_MSG_STRU;
typedef struct{
    VOS_UINT32                          ulMcc;             /* �������MCC    */
    VOS_UINT32                          ulMnc;             /* �������MNC    */
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;        /* ��������       */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;         /* ����Ľ��뼼�� */
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus;       /* ����Ĵ���״̬ */
    NAS_MMC_NET_QUALITY_ENUM_UINT8      enQuality;         /* ������ź����� */
}NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU;


typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU                    astPlmnSelectionList[NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST];/* �����б� */
}NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU;


typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSrchedPlmn;
}NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU;
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_PLMN_ID_STRU                                    stGetLteRplmn;      /* ��ȡ��ǰLTE��RPLMN */
    NAS_MML_PLMN_ID_STRU                                    stGetGuRplmn;       /* ��ȡ��ǰGU��RPLMN */
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;         /* RPLMN�Ķ������� */
    NAS_MML_LAI_STRU                                        stLastSuccLai;      /* CS�����һ��ע��ɹ���LAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��LAI�����ֵΪ��Чֵ */
    NAS_MML_RAI_STRU                                        stLastSuccRai;      /* PS�����һ��ע��ɹ���RAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��RAI�����ֵΪ��Чֵ */
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8                enPsUpdateStatus;   /* status of routing update */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;   /* status of location update */
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;           /* �ֻ�ģʽ */
    VOS_UINT8                                               ucReserved;
}NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU;
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;         /* RPLMN�Ķ������� */
}NAS_MMC_LOG_RPLMN_CFG_INFO_STRU;



typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        stSimForbidenInfo;  /* SIM���еĽ�ֹ������Ϣ */
    NAS_MML_ROAM_CFG_INFO_STRU                              stRoamCfg;          /* ROAM�Ķ������� */
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                         stPlmnLockCfg;      /* ������������,������������� */
    NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU                   stLteRoamCfg;       /* LTE�������ζ������� */
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU                       stRatFirbiddenStatusCfg;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;/* ȥʹ��LTE������� */
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;
    VOS_UINT32                                              ulDisableLteRoamFlg;/* ��ֹLTE���ε��µ�disable LTE��� */
}NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MMC_HISTORY_SEARCH_INFO_STRU                        stHistorySearchInfo;
    NAS_MMC_GET_GEO_INFO_STRU                               stGetGeoInfo;
}NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                           stMsgHeader;                      /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                 ucAbortFlg;                       /* ��ǰ״̬����־�Ƿ��յ���ֹҪ��,VOS_TRUE:�յ�, VOS_FALSE:δ�յ� */
    VOS_UINT8                                 ucRelRequestFlg;                  /* �Ƿ��������������Ƿ�,VOS_TRUE:����������, VOS_FALSE:�����ȴ��ͷ� */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8           ucInterSysSuspendRat;             /* ��¼��ϵͳ״̬������ʱ�Ľ��뼼�������ע����ʱ��G�л���W */
    VOS_UINT8                                 ucSrvTrigPlmnSearchFlag;          /* �Ƿ����ҵ�񴥷�������ʶ��VOS_TRUE:���ڣ�VOS_FALSE:������*/
    NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU stRegRlstInfo;                    /* ����ѡ��״̬����ע������Ϣ */
    NAS_MMC_RAT_SEARCH_INFO_STRU              astSearchRatInfo[NAS_MML_MAX_RAT_NUM];  /* ���治ͬ���뼼����������Ϣ */
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU  stForbRoamLaInfo;
    NAS_MML_PLMN_ID_STRU                      stForbGprsPlmn;                   /* "forbidden PLMNs for GPRS service"  */
    NAS_MML_PLMN_ID_STRU                      stCsPsMode1ReCampLtePlmn;         /* ���浱ǰL�����PLMNID */
    NAS_MML_PLMN_WITH_RAT_STRU                stCurrSearchingPlmn;              /* ��ǰ���ڳ��Ե����缰����뼼��,����at+cops=0 9074 nv������ʱ�жϵ�ǰ���������������Ƿ�Ϊhplmn */
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32      enCurrSearchingType;              /* ��������ָ���ѣ�history�� */
    VOS_UINT8                                 ucExistRplmnOrHplmnFlag;          /* ������ϱ���searched plmn info�Ƿ����rplmn��hplmn��ʶ */
    VOS_UINT8                                 aucReserve[3];
}NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU                           stMsgHeader;                      /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU        stRegRsltInfo;                    /* ��������״̬��ע������Ϣ */
    VOS_UINT32                                ulCurTimerCount;                  /* ��ǰAvailable Timer�������� */
    VOS_UINT32                                ulCurHighRatHplmnTimerCount;      /* ��ǰhigh prio rat hplmn Timer�������� */
    VOS_UINT32                                ulCurNcellSearchTimerCount;       /* ��ǰncell���������������� */
    VOS_UINT32                                ulCurHistorySearchTimerCount;     /* ��ǰhistory������������ */
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8   enAvailableTimerType;
    VOS_UINT8                                 aucReserved[3];
}NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU;


/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU
 �ṹ˵��  : ��ֹLA��Чʱ���б���صĿ�ά�ɲ���Ϣ�ṹ��
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU    stForbLaWithValidPeriodCfg;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU             stForbLaWithValidPeriod;
}NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU;
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucReserve;
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId;


    VOS_UINT32                          ulTimerRemainLen;/* ��ʱ����ʱ�� */
}NAS_MMC_TIMER_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
    VOS_UINT32                          ulFileLen;                              /* �ļ����� */
    VOS_UINT8                           aucFileContent[4];                      /* �ļ����� */
}NAS_MMC_GET_CACHE_FILE_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
    VOS_UINT8                           ucDrxTimerStatus;                       /*  DRX��ʱ����״̬ */
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_DRX_TIMER_STAUTS_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
    NAS_MML_PLATFORM_RAT_CAP_STRU       stPlatformRatCap;                       /*  ƽ̨�������� */
}NAS_MMC_PLATFORM_RAT_CAP_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_MMC_LogMmcFsmInfo( VOS_VOID );

#if (FEATURE_LTE == FEATURE_ON)
VOS_VOID  NAS_MMC_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
);
#endif

VOS_VOID  NAS_MMC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID NAS_MMC_SndOutsideFixedContextData( VOS_VOID );


VOS_VOID NAS_MMC_SndPcRepalyCtxInfo(
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM_UINT32                ulContextType
);

VOS_VOID NAS_MMC_SndOutsideContextData( VOS_VOID );

/* Modified by wx270776 for OM�ں�, 2015-7-10, begin */
VOS_VOID NAS_MMC_SndOmOtaCnf(
    VOS_UINT32                          ulErrCode,
    OM_NAS_OTA_REQ_STRUCT              *pstOtaReq
);
/* Modified by wx270776 for OM�ں�, 2015-7-10, end */

VOS_VOID NAS_MMC_SndOmInquireCnfMsg(
    ID_NAS_OM_INQUIRE_STRU             *pstOmInquireMsg
);

VOS_VOID  NAS_MMC_ConvertPlmnIdToOmDispalyFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    PLMN_ID_STRUCT                     *pstOmPlmnIdFormat
);

VOS_VOID NAS_MMC_SndOmPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
);

VOS_VOID NAS_MMC_LogRplmnRelatedInfo(VOS_VOID);
VOS_VOID NAS_MMC_LogForbiddenPlmnRelatedInfo(VOS_VOID);
VOS_VOID NAS_MMC_LogRplmnCfgInfo(VOS_VOID);

VOS_VOID NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(
    NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU *pstFsmPlmnSelectionCtx
);
VOS_VOID NAS_MMC_LogFsmL1MainCtxRelatedInfo(
    NAS_MMC_FSM_L1_MAIN_CTX_STRU       *pstFsmL1MainCtx
);
VOS_VOID NAS_MMC_LogHistoryRelatedInfo(VOS_VOID);

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
VOS_VOID NAS_MMC_LogForbLaWithValidPeriodListInfo(VOS_VOID);
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

VOS_VOID  NAS_MMC_SndOmMmcTimerStatus(
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus,
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulTimerRemainLen
);

VOS_VOID NAS_MMC_SndOmEquPlmn(VOS_VOID);

VOS_VOID  NAS_MMC_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
);


VOS_VOID NAS_MMC_SndOmInternalMsgQueueDetailInfo(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pInternalMsgQueue
);

VOS_VOID  NAS_MMC_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
);


VOS_VOID  NAS_MMC_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus );

VOS_VOID  NAS_MMC_SndOmPlatformRatCap( VOS_VOID );

NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32 NAS_MMC_GetPlmnHUOType(NAS_MML_PLMN_ID_STRU *pstPlmn);


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID  NAS_MMC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
 );
VOS_VOID  NAS_MMC_SndAcpuOmFtmRptInd(
    VOS_UINT8                           *pucTmsi,
    VOS_UINT32                           ulLen
);
VOS_VOID NAS_MMC_SndAcpuOmCurTmsi(VOS_VOID);
VOS_VOID NAS_MMC_SndAcpuOmCurPtmsi(VOS_VOID);
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

#endif

