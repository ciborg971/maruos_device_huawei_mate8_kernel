

#ifndef __LNASREPLAYPROC_H__
#define __LNASREPLAYPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasEmmSecuOm.h"
#include  "NasLmmPubMOsa.h"


#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#ifndef __PS_WIN32_RECUR__
#define __PS_WIN32_RECUR__      2
#endif


/* ��������ֵ */
#define NAS_PCREPLAY_EXPORT_VAR_FINISH          (0)
#define NAS_PCREPLAY_EXPORT_VAR_CONTINUE        (1)
#define NAS_PCREPLAY_EXPORT_VAR_ERROR           (2)
#if(VOS_WIN32 == VOS_OS_VER)
/*add data len*/
#define NAS_PC_REPLAY_COMPRESS_DATA_LEN         (150000)                 /* PC�ط�ѹ������������ȣ���λ���ֽ� */
#else
#define NAS_PC_REPLAY_COMPRESS_DATA_LEN         (15000)
#endif
#define NAS_PC_REPLAY_UNCOMPRESS_DATA_LEN       (1024*1024*1)           /* PC�ط�ѹ������������ȣ���λ���ֽ� */


#define NAS_REPLAY_EMC_MESSAGE_MAX_LEN          (350)
#define NAS_REPLAY_ESM_MESSAGE_MAX_LEN          (1600)
#define NAS_REPLAY_EMM_MESSAGE_MAX_LEN          (1600)


#define NAS_PCREPLAY_LEN_VOS_MSG_HEADER          16


#define NAS_REPLAY_MAX_PUB_INFO         10
#define NAS_REPLAY_MAX_GU_INFO          10
#define NAS_REPLAY_MAX_MS_NET_CAP       10
#define NAS_REPLAY_MAX_UEID_TMSI_INFO   10
#define NAS_REPLAY_MAX_LTE_CS_SRV_CFG   10
#define NAS_REPLAY_MAX_TIN_TYPE         10
#define NAS_REPLAY_MAX_ADD_UPDATE_RSLT  10
#define NAS_REPLAY_MAX_PS_BEARER_CTX    10
#define NAS_REPLAY_MAX_PS_BEARER_EXIST_BEFORE_ISR_ACT 10
#define NAS_REPLAY_MAX_PS_BEARER_AFTER_ISR_ACT_EXIST 10
#define NAS_REPLAY_MAX_EMC_NUM_LIST     10
#define NAS_REPLAY_MAX_PS_REG_CONTAIN_DRX_PARA 10
#define NAS_REPLAY_MAX_EUTRAN_DRX_LEN   10
#define NAS_REPLAY_MAX_NON_DRX_TIMER    10
#define NAS_REPLAY_MAX_SPLIT_PG_CYCLE_CODE 10
#define NAS_REPLAY_MAX_SPLIT_ON_CCCH        10
#define NAS_REPLAY_MAX_MS_CLASSMARK2        10
#define NAS_REPLAY_MAX_CS_ATTACH_ALLOW_FLG  10
#define NAS_REPLAY_MAX_PS_ATTACH_ALLOW_FLG  10
#define NAS_REPLAY_MAX_MS_MODE              10
#define NAS_REPLAY_MAX_PLMNID_IS_FORBID     10
#define NAS_REPLAY_MAX_PLMN_EXACTLY_CMP_FLG 10
#define NAS_REPLAY_MAX_PS_REG_STATUS        10
#define NAS_REPLAY_MAX_SIM_TYPE             10
#define NAS_REPLAY_MAX_KDF_KEY              10
#define NAS_REPLAY_MAX_SDF_PARA             10
#define NAS_REPLAY_MAX_PDP_MANAGE_INFO      10

#define NAS_REPLAY_MAX_CARD_IMSI            10
#define NAS_REPLAY_MAX_SERVICE_AVAILABLE    10
#define NAS_REPLAY_MAX_USIM_TEST_MODE       10

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_LMM_REPLAY_CONTEXT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LNAS������Ϣö��
*****************************************************************************/
enum NAS_LMM_REPLAY_CONTEXT_ENUM
{
    NAS_EMM_REPLAY_CONTEXT                = 0,
    NAS_ESM_REPLAY_CONTEXT,
    NAS_ERABM_REPLAY_CONTEXT,

    NAS_LMM_REPLAY_CONTEXT_BUTT
};
typedef VOS_UINT32 NAS_LMM_REPLAY_CONTEXT_ENUM_UINT32;



enum NAS_OM_LOG_MSG_ID_ENUM
{
    /* LMM���͸�OM����Ϣ */
    NAS_OM_LOG_PUB_INFO_IND    = 0x00,
    NAS_OM_LOG_GU_INFO_IND,
    NAS_OM_LOG_TIN_INFO_IND,
    NAS_OM_LOG_MS_NETWORK_CAPACILITY_INFO_IND,
    NAS_OM_LOG_UEIDTMSI_IND,
    NAS_OM_LOG_CS_SERVICE_FLAG_INFO_IND,

    NAS_OM_LOG_ADD_UPDATE_RSLT_INFO_IND,
    NAS_OM_LOG_PS_BEAR_CTX_INFO_IND,
    NAS_OM_LOG_PSBER_EXIST_BEF_ISRACT_INFO_IND,
    NAS_OM_LOG_BEAR_ISR_ACT_AFTER_INFO_IND,
    NAS_OM_LOG_EMERGENCY_NUMLIST_INFO_IND,
    NAS_OM_LOG_PSREG_CONTAINDRX_INFO_IND,

    NAS_OM_LOG_EUTRAN_PS_DRX_LEN_INFO_IND,
    NAS_OM_LOG_DRX_TIMER_INFO_IND,
    NAS_OM_LOG_SPLIT_PG_CYCLE_CODE_INFO_IND,
    NAS_OM_LOG_SPLIT_ON_CCCH_INFO_IND,
    NAS_OM_LOG_CLASSMARK2_INFO_IND,
    NAS_OM_LOG_CS_ATTACH_ALLOW_FLG_INFO_IND,
    NAS_OM_LOG_PS_ATTACH_ALLOW_FLG_INFO_IND,
    NAS_OM_LOG_MS_MODE_INFO_IND,
    NAS_OM_LOG_PLMN_IS_FORBID_INFO_IND,
    NAS_OM_LOG_PLMN_EXAXTLY_CMP_INFO_IND,
    NAS_OM_LOG_PS_REG_STATUS_INFO_IND,
    NAS_OM_LOG_SIM_TYPE_INFO_IND,
    NAS_OM_LOG_BSP_KDF_KEY_MAKE_INFO_IND,
    NAS_OM_LOG_SDF_PARA_INFO_IND,
    NAS_OM_LOG_PDP_MANAGE_INFO_IND,

    NAS_OM_LOG_CARD_IMSI_INFO_IND,
    NAS_OM_LOG_USIMM_SERVICE_INFO_IND,
    NAS_OM_LOG_USIMM_TEST_MODE_INFO_IND,

    NAS_OM_LOG_MSG_BUTT
};
typedef VOS_UINT32 NAS_OM_LOG_MSG_ID_ENUM_UINT32;



/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgName;
    VOS_UINT8                            aucData[4];
}NAS_PC_REPLAY_RUNNING_CONTEXT_STRU;



typedef VOS_UINT32 (*NAS_REPLAY_VAR_EXPORT_FUNC_PTR)(
    VOS_UINT8                           *pucDest,
    VOS_UINT8                           *pucDestEnd,
    VOS_UINT8                           *pucVar,
    VOS_UINT32                          *pulDatalen
);

typedef VOS_UINT32 (*NAS_REPLAY_VAR_IMPORT_FUNC_PTR)(
    VOS_UINT8                           *pucVar,
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulUsedCmpDataLen,
    VOS_UINT32                          *pulUnCmpLen
);



typedef struct{
    VOS_UINT8                              *pucItemAddr;                        /* Ҫ����/�����ȫ�ֱ�����ַ */
    VOS_UINT32                              ulItemLen;                          /* ����ʱҪ�����ȫ�ֱ����ĳ��� */
    VOS_UINT32                              ulCompressFlg;                      /* �˱����ڵ���ʱ�Ƿ�ѹ�� */
    NAS_REPLAY_VAR_EXPORT_FUNC_PTR          pExportFunc;                        /* �����������ĵ������� */
    NAS_REPLAY_VAR_IMPORT_FUNC_PTR          pImportFunc;                        /* �����������Ļָ����� */
}NAS_REPLAY_CTX_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LNAS_REPLAY_API_INFO_IMPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LNAS��API��Ϣ���뺯��
*****************************************************************************/
typedef VOS_UINT32 (*LNAS_REPLAY_API_IMPORT_FUNC_PTR)(MsgBlock * pstMsg);

/*****************************************************************************
 �ṹ��    : LNAS_REPLAY_API_INFO_IMPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LNAS�ط�ʱ����API��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulRcverPid;
    VOS_UINT32                          ulMsgNme;
    LNAS_REPLAY_API_IMPORT_FUNC_PTR      pImportFunc;  /* API��Ϣ���뺯��ָ�� */
}LNAS_REPLAY_API_INFO_IMPORT_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PUB_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_GetPubInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MMC_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType;
    MMC_LMM_PUB_INFO_STRU               stPubInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;
} NAS_LMM_LOG_PUB_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_REPLAY_PUB_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_GetPubInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    /*����API�����*/
    MMC_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType;

    /*����API�ĳ���*/
    MMC_LMM_PUB_INFO_STRU               stPubInfo;

    /*����API�ķ���ֵ*/
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;
}NAS_LMM_REPLAY_PUB_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_GU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_GetGuInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_GUMM_INFO_TYPE_ENUM_UINT32      ulInfoType;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;
} NAS_LMM_LOG_GU_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_REPLAY_GU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_GetGuInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    /*����API�����*/
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType;

    /*����API�ĳ���*/
    NAS_GUMM_INFO_STRU                stGuInfo;

    /*����API�ķ���ֵ*/
    MMC_LMM_RESULT_ID_ENUM_UINT32   ulRslt;
}NAS_LMM_REPLAY_GU_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_MS_NETWORK_CAPACILITY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetMsNetworkCapability API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  stMsNetworkCapbility;
}NAS_LMM_LOG_MS_NETWORK_CAPACILITY_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_UEIDTMSI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetUeIdTmsi API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           aucUeIdTmsi[4];
} NAS_LMM_LOG_UEIDTMSI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_UEID_TMSI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetUeIdTmsi API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUeIdTmsi[4];
}NAS_REPLAY_UEID_TMSI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_CS_SERVICE_FLAG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetUeIdTmsi API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgName;
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   ucMmlCsService;
    VOS_UINT8                               aucRsv[3];
} NAS_LMM_LOG_CS_SERVICE_FLAG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_TIN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetTinType API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
}NAS_LMM_LOG_TIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_ADD_UPDATE_RSLT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetAdditionUpdateRslt API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;
} NAS_LMM_LOG_ADD_UPDATE_RSLT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PS_BEAR_CTX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsBearerCtx API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[NAS_MML_MAX_PS_BEARER_NUM];
} NAS_LMM_LOG_PS_BEAR_CTX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_PS_BEARER_CONTEXT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsBearerCtx API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[NAS_MML_MAX_PS_BEARER_NUM];
} NAS_REPLAY_PS_BEARER_CONTEXT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PSBER_EXIST_BEF_ISRACT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_IsPsBearerExistBeforeIsrAct API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulExistFlag;
} NAS_LMM_LOG_PSBER_EXIST_BEF_ISRACT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PSBER_EXIST_AFTER_ISRACT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_IsPsBearerAfterIsrActExist API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulExistFlag;
} NAS_LMM_LOG_PSBER_EXIST_AFTER_ISRACT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_EMERGENCY_NUMLIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetEmergencyNumList API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     stMmlEmerNumList;
} NAS_LMM_LOG_EMERGENCY_NUMLIST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_EMERGENCY_NUMLISTS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetEmergencyNumList API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU     stMmlEmerNumList;
} NAS_REPLAY_EMERGENCY_NUMLISTS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PSREG_CONTAINDRX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsRegContainDrx API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8     enPsRegisterContainDrx;
    VOS_UINT8                           aucReserv[3];
}NAS_LMM_LOG_PSREG_CONTAINDRX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_UE_EUTRAN_PS_DRX_LEN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetUeEutranPsDrxLen API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucEutranDrxLen;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_UE_EUTRAN_PS_DRX_LEN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_NON_DRX_TIMER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetNonDrxTimer API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucNonDrxTimer;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_NON_DRX_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_DRX_SPLIT_PG_CYCLE_CODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetSplitPgCycleCode API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucSplitPgCycleCode;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_DRX_SPLIT_PG_CYCLE_CODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_DRX_SPLIT_ON_CCCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetSplitOnCcch  API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucSplitCcch;
    VOS_UINT8                           aucReserv[3];
}NAS_LMM_LOG_DRX_SPLIT_ON_CCCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_CLASSMARK2_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_Fill_IE_ClassMark2 API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN];
} NAS_LMM_LOG_CLASSMARK2_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_MS_CLASSMARK2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_Fill_IE_ClassMark2 API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsClassMark2[4];
}NAS_REPLAY_MS_CLASSMARK2_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_CS_ATTACH_ALLOW_FLG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsAttachAllowFlg API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_CS_ATTACH_ALLOW_FLG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_CS_ATTACH_ALLOW_FLG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsAttachAllowFlg API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucPsAttachAllow;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_PS_ATTACH_ALLOW_FLG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_MS_MODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetMsMode API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_MS_MODE_ENUM_UINT8          ucMsMode;
    VOS_UINT8                           aucReserv[3];
} NAS_LMM_LOG_MS_MODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PLMNID_IS_FOBID_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_PlmnIdIsForbid API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MMC_LMM_PLMN_ID_STRU                stPlmn;
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulRslt;
} NAS_LMM_LOG_PLMNID_IS_FOBID_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_PLMNID_IS_FORBID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Nas_PlmnIdIsForbid API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmn;
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulRslt;
}NAS_REPLAY_PLMNID_IS_FORBID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PLMN_EXACTLY_COMPARE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPlmnExactlyComparaFlg API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucRslt;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_LOG_PLMN_EXACTLY_COMPARE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_PS_REG_STATUS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetPsRegStatus API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegStatus;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_LOG_PS_REG_STATUS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_SIM_TYPE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :NAS_MML_GetSimType API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_LOG_SIM_TYPE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_KDF_KEY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :LDRV_CIPHER_GEN_KEY API�ĵ�����Ϣ�ṹ
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    NAS_LMM_BSP_INPUT_PARA_STRU         stBspInputPara;
    NAS_LMM_BSP_OUTPUT_PARA_STRU        stBspOutputPara;
    VOS_INT32                           lRslt;
}NAS_LMM_LOG_KDF_KEY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_KDF_KEY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :LDRV_CIPHER_GEN_KEY API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    NAS_LMM_BSP_INPUT_PARA_STRU         stBspInputPara;
    NAS_LMM_BSP_OUTPUT_PARA_STRU        stBspOutputPara;
    VOS_INT32                           lRslt;
}NAS_REPLAY_KDF_KEY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_OM_LOG_SDF_PARA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :APP_GetSdfPara API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSdfNum;
    APP_ESM_SDF_PARA_STRU               stSdfPara;
    VOS_UINT32                          ulRslt;
} NAS_OM_LOG_SDF_PARA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_REPLAY_SDF_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :APP_GetSdfPara API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSdfNum;
    APP_ESM_SDF_PARA_STRU               stSdfPara;
    VOS_UINT32                          ulRslt;
}NAS_REPLAY_SDF_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_OM_LOG_PDP_MANAGER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :APP_GetPdpManageInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    APP_ESM_PDP_MANAGE_INFO_STRU        stPdpManageInfo;
    VOS_UINT32                          ulRslt;
}NAS_OM_LOG_PDP_MANAGER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_PDP_MANAGE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :APP_GetPdpManageInfo API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
   APP_ESM_PDP_MANAGE_INFO_STRU        stPdpManageInfo;
   VOS_UINT32                          ulRslt;
}NAS_REPLAY_PDP_MANAGE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_CARD_IMSI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :USIMM_GetCardIMSI  API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           aucImsi[9];
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulRslt;
}NAS_LMM_LOG_CARD_IMSI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_CARD_IMSI_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  :USIMM_GetCardIMSI API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[9];
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRslt;
}NAS_REPLAY_CARD_IMSI_INFO;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_USIMM_SERVICE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :USIMM_IsServiceAvailable  API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    UICC_SERVICES_TYPE_ENUM_UINT32      enService;
    VOS_UINT32                          ulRslt;
}NAS_LMM_LOG_USIMM_SERVICE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_REPLAY_SERVICE_AVAILABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :USIMM_IsServiceAvailable API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    UICC_SERVICES_TYPE_ENUM_UINT32     enService;
    VOS_UINT32                          ulRslt;
}NAS_REPLAY_SERVICE_AVAILABLE_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_LOG_USIM_TEST_MODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :USIMM_IsTestCard  API�ĵ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulRslt;
}NAS_LMM_LOG_USIM_TEST_MODE_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*Nas_GetPubInfo API����ʱ��ȫ�ֱ���*/
extern NAS_LMM_REPLAY_PUB_INFO_STRU            g_astPubInfo[NAS_REPLAY_MAX_PUB_INFO];
extern VOS_UINT32                              g_ulPubInfoCount;
extern VOS_UINT32                              g_ulPubInfoIndex;

/*Nas_GetGuInfo API����ʱ��ȫ�ֱ���*/
extern NAS_LMM_REPLAY_GU_INFO_STRU             g_astGuInfo[NAS_REPLAY_MAX_GU_INFO];
extern VOS_UINT32                              g_ulGuInfoCount;
extern VOS_UINT32                              g_ulGuInfoIndex;

/*NAS_MML_GetMsNetworkCapability API����ʱ��ȫ�ֱ���*/
extern NAS_MML_MS_NETWORK_CAPACILITY_STRU g_astMsNetworkCapability[NAS_REPLAY_MAX_MS_NET_CAP];
extern VOS_UINT32               g_ulMsNetCapCount;
extern VOS_UINT32               g_ulMsNetCapIndex;


/*NAS_MML_GetUeIdTmsi API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_UEID_TMSI_INFO_STRU          g_astUeIdTmsiInfo[NAS_REPLAY_MAX_UEID_TMSI_INFO];
extern VOS_UINT32                              g_ulUeIdTmsiInfoCount;
extern VOS_UINT32                              g_ulUeIdTmsiInfoIndex;

/*NAS_MML_GetLteCsServiceCfg API����ʱ��ȫ�ֱ���*/
extern NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   g_astLteCsSrvCfg [NAS_REPLAY_MAX_LTE_CS_SRV_CFG];
extern VOS_UINT32                              g_ulLteCsSrvCfgCount;
extern VOS_UINT32                              g_ulLteCsSrvCfgIndex;

/*NAS_MML_GetTinType API����ʱ��ȫ�ֱ���*/
extern MMC_LMM_TIN_TYPE_ENUM_UINT32            g_astTinType[NAS_REPLAY_MAX_TIN_TYPE];
extern VOS_UINT32                              g_ulTinTypeCount;
extern VOS_UINT32                              g_ulTinTypeIndex;

/*NAS_MML_GetAdditionUpdateRslt API����ʱ��ȫ�ֱ���*/
extern NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32 g_astAddUpdateRslt[NAS_REPLAY_MAX_ADD_UPDATE_RSLT];
extern VOS_UINT32                              g_ulAddUpdateRsltCount;
extern VOS_UINT32                              g_ulAddUpdateRsltIndex;

/*NAS_MML_GetAdditionUpdateRslt API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_PS_BEARER_CONTEXT_INFO_STRU g_astPsBearCtx[NAS_REPLAY_MAX_PS_BEARER_CTX];
extern VOS_UINT32               g_ulPsBearCtxCount;
extern VOS_UINT32               g_ulPsBearCtxIndex;

/*NAS_MML_IsPsBearerExistBeforeIsrAct API����ʱ��ȫ�ֱ���*/
extern VOS_UINT32                  g_astBefIsrAct[NAS_REPLAY_MAX_PS_BEARER_EXIST_BEFORE_ISR_ACT];
extern VOS_UINT32                  g_ulBeIsrActCount;
extern VOS_UINT32                  g_ulBefIsrActIndex;

/*NAS_MML_IsPsBearerAfterIsrActExist API����ʱ��ȫ�ֱ���*/
extern VOS_UINT32 g_astAfterIsrActExist[NAS_REPLAY_MAX_PS_BEARER_AFTER_ISR_ACT_EXIST];
extern VOS_UINT32               g_ulAfterIsrActExistCount;
extern VOS_UINT32               g_ulAfterIsrActExistIndex;

/*NAS_MML_GetEmergencyNumList API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_EMERGENCY_NUMLISTS_INFO_STRU g_astEmcNumList[NAS_REPLAY_MAX_EMC_NUM_LIST];
extern VOS_UINT32               g_ulEmcNumListCount;
extern VOS_UINT32               g_ulEmcNumListIndex;

/*NAS_MML_GetPsRegContainDrx API����ʱ��ȫ�ֱ���*/
extern NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 g_astPsRegContainDrxPara[NAS_REPLAY_MAX_PS_REG_CONTAIN_DRX_PARA];
extern VOS_UINT32               g_ulPsRegContainDrxParaCount;
extern VOS_UINT32               g_ulPsRegContainDrxParaIndex;

/*NAS_MML_GetUeEutranPsDrxLen API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astUeEutranPsDrxLen[NAS_REPLAY_MAX_EUTRAN_DRX_LEN];
extern VOS_UINT32               g_ulUeEutranPsDrxLenCount;
extern VOS_UINT32               g_ulUeEutranPsDrxLenIndex;

/*NAS_MML_GetNonDrxTimer API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astNonDrxTimer[NAS_REPLAY_MAX_NON_DRX_TIMER];
extern VOS_UINT32               g_ulNonDrxTimerCount;
extern VOS_UINT32               g_ulNonDrxTimerIndex;

/*NAS_MML_GetSplitPgCycleCode API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astSplitPgCycleCode[NAS_REPLAY_MAX_SPLIT_PG_CYCLE_CODE];
extern VOS_UINT32               g_ulSplitPgCycleCodeCount;
extern VOS_UINT32               g_ulSplitPgCycleCodeIndex;

/*NAS_MML_GetSplitOnCcch API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astSplitOnCcch[NAS_REPLAY_MAX_SPLIT_ON_CCCH];
extern VOS_UINT32               g_ulSplitOnCcchCount;
extern VOS_UINT32               g_ulSplitOnCcchIndex;

/*NAS_MML_Fill_IE_ClassMark2 API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_MS_CLASSMARK2_STRU g_astMsClassMark2[NAS_REPLAY_MAX_MS_CLASSMARK2];
extern VOS_UINT32               g_ulMsClassMark2Count;
extern VOS_UINT32               g_ulMsClassMark2Index;

/*NAS_MML_GetCsAttachAllowFlg API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astCsAttachAllowFlg[NAS_REPLAY_MAX_CS_ATTACH_ALLOW_FLG];
extern VOS_UINT32               g_ulCsAttachAllowFlgCount;
extern VOS_UINT32               g_ulCsAttachAllowFlgIndex;

/*NAS_MML_GetPsAttachAllowFlg API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astPsAttachAllowFlg[NAS_REPLAY_MAX_PS_ATTACH_ALLOW_FLG];
extern VOS_UINT32               g_ulPsAttachAllowFlgCount;
extern VOS_UINT32               g_ulPsAttachAllowFlgIndex;

/*NAS_MML_GetMsMode API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astMsMode[NAS_REPLAY_MAX_MS_MODE];
extern VOS_UINT32               g_ulMsModeCount;
extern VOS_UINT32               g_ulMsModeIndex;

/*Nas_PlmnIdIsForbid API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_PLMNID_IS_FORBID_STRU g_astPlmnIdIsForbid[NAS_REPLAY_MAX_PLMNID_IS_FORBID];
extern VOS_UINT32               g_ulPlmnIdIsForbidCount;
extern VOS_UINT32               g_ulPlmnIdIsForbidIndex;

/*NAS_MML_GetPlmnExactlyComparaFlg API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astPlmnExactlyCmpFlg[NAS_REPLAY_MAX_PLMN_EXACTLY_CMP_FLG];
extern VOS_UINT32               g_ulPlmnExactlyCmpFlgCount;
extern VOS_UINT32               g_ulPlmnExactlyCmpFlgIndex;

/*NAS_MML_GetPsRegStatus API����ʱ��ȫ�ֱ���*/
extern VOS_UINT8  g_astPsRegStatus[NAS_REPLAY_MAX_PS_REG_STATUS];
extern VOS_UINT32               g_ulPsRegStatusCount;
extern VOS_UINT32               g_ulPsRegStatusIndex;

/*NAS_MML_GetSimType API����ʱ��ȫ�ֱ���*/
extern NAS_MML_SIM_TYPE_ENUM_UINT8 g_astSimType[NAS_REPLAY_MAX_SIM_TYPE];
extern VOS_UINT32               g_ulSimTypeCount;
extern VOS_UINT32               g_ulSimTypeIndex;

/*BSP_KDF_KeyMakeBSP_KDF_KeyMake API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_KDF_KEY_STRU g_astKdfKey[NAS_REPLAY_MAX_KDF_KEY];
extern VOS_UINT32               g_ulKdfKeyCount;
extern VOS_UINT32               g_ulKdfKeyIndex;

/*APP_GetSdfPara API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_SDF_PARA_STRU g_astSdfPara[NAS_REPLAY_MAX_SDF_PARA];
extern VOS_UINT32               g_ulSdfParaCount;
extern VOS_UINT32               g_ulSdfParaIndex;

/*APP_GetSdfPara API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_PDP_MANAGE_INFO_STRU g_astPdpManageInfo[NAS_REPLAY_MAX_PDP_MANAGE_INFO];
extern VOS_UINT32               g_ulPdpManageInfoCount;
extern VOS_UINT32               g_ulPdpManageInfoIndex;

/*USIMM_GetCardIMSI API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_CARD_IMSI_INFO g_astCardImsi[NAS_REPLAY_MAX_CARD_IMSI];
extern VOS_UINT32               g_ulCardImsiCount;
extern VOS_UINT32               g_ulCardImsiIndex;

/*USIMM_IsServiceAvailable API����ʱ��ȫ�ֱ���*/
extern NAS_REPLAY_SERVICE_AVAILABLE_STRU g_astServiceAvailable[NAS_REPLAY_MAX_SERVICE_AVAILABLE];
extern VOS_UINT32               g_ulServiceAvailableCount;
extern VOS_UINT32               g_ulServiceAvailableIndex;

/*USIMM_IsTestCard API����ʱ��ȫ�ֱ���*/
extern VOS_UINT32  g_astUsimTestMode[NAS_REPLAY_MAX_USIM_TEST_MODE];
extern VOS_UINT32               g_ulUsimTestModeCount;
extern VOS_UINT32               g_ulUsimTestModeIndex;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

#if(VOS_WIN32 == VOS_OS_VER)
/*�ڵ��廷���ݲ���������*/

extern VOS_UINT32 NAS_Replay_SaveCntxInfo
(
    VOS_UINT8                           *pucDestBufAddr, /* ѹ��������� */
    VOS_UINT32                          ulDestBufLen,
    NAS_REPLAY_CTX_INFO_STRU            *pstArrayAddr,
    VOS_UINT32                          ulArrayCnt,
    VOS_UINT32                          *pulCmpDatalen
);
extern VOS_UINT32 NAS_Replay_ExportVarible
(
    VOS_UINT8                           *pucDest, /* ѹ��������� */
    const VOS_UINT8                           *pucDestEnd,
    NAS_REPLAY_CTX_INFO_STRU            *pstVar,
    VOS_UINT32                          *pulDatalen
);

extern VOS_UINT32  NAS_EMM_ExportContextData(VOS_VOID);
extern VOS_UINT32  NAS_ESM_ExportContextData(VOS_VOID);
extern VOS_UINT32  NAS_ERABM_ExportContextData(VOS_VOID);
extern VOS_UINT32  NAS_REPLAY_ExportEmmInfo
(
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                     *pucDestEnd,
    const VOS_UINT8                     *pucVar,
    VOS_UINT32                          *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEmmEsmMsgBuf
(
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                           *pucDestEnd,
    const VOS_UINT8                           *pucVar,
    VOS_UINT32                          *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEmmFsmBufHighQueue
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEmmFsmBufMidQueue
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEmmFsmBufLowQueue
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportMmMainContext
(
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                     *pucDestEnd,
    const VOS_UINT8                     *pucVar,
    VOS_UINT32                          *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEsmDecodedNwMsg
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEsmAttBuffItemNum
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEsmPtiBuffItemNum
(
    VOS_UINT8 *pucDest,
    const VOS_UINT8 *pucDestEnd,
    VOS_UINT32  *pulDatalen
);
extern VOS_UINT32  NAS_REPLAY_ExportEsmEntity
(
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                     *pucDestEnd,
    const VOS_UINT8                     *pucVar,
    VOS_UINT32                          *pulDatalen
);

#ifdef __PS_WIN32_RECUR__

#if(VOS_WIN32 == VOS_OS_VER)
/*�ڵ��廷���ݲ�����*/

extern VOS_UINT32 NAS_REPLAY_RestoreContext
(
    NAS_REPLAY_CTX_INFO_STRU        *pstCtxTbl,
    VOS_UINT32                      ulCount,
    VOS_UINT8                       *pucSrc
);
extern VOS_UINT32 NAS_REPLAY_RestoreVar
(
    const NAS_REPLAY_CTX_INFO_STRU        *pstVar,
    const VOS_UINT8                       *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);


extern VOS_UINT32  NAS_REPLAY_ImportEmmInfo
(
    const VOS_UINT8                     *pucVar,
    const VOS_UINT8                     *pucSrc,
    VOS_UINT32                          *pulUsedCmpDataLen,
    VOS_UINT32                          *pulUnCmpLen
);

extern VOS_UINT32  NAS_REPLAY_ImportEmmEsmMsgBuf
(
    const VOS_UINT8                           *pucVar,
    const VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulUsedCmpDataLen,
    VOS_UINT32                          *pulUnCmpLen
);

extern VOS_UINT32  NAS_REPLAY_ImportEmmFsmBufHighQueue
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_REPLAY_ImportEmmFsmBufMidQueue
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_REPLAY_ImportEmmFsmBufLowQueue
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_REPLAY_ImportMmMainContex
(
    const VOS_UINT8                     *pucVar,
    const VOS_UINT8                     *pucSrc,
    VOS_UINT32                          *pulUsedCmpDataLen,
    VOS_UINT32                          *pulUnCmpLen
);

extern VOS_UINT32  NAS_REPLAY_ImportEsmDecodedNwMsg
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_REPLAY_ImportEsmAttBuffItemNum
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_REPLAY_ImportEsmPtiBuffItemNum
(
    const VOS_UINT8                 *pucSrc,
    VOS_UINT32                      *pulUsedCmpDataLen,
    VOS_UINT32                      *pulUnCmpLen
);
extern VOS_UINT32  NAS_Replay_ImportEsmEntity
(
    const VOS_UINT8                     *pucVar,
    const VOS_UINT8                     *pucSrc,
    VOS_UINT32                          *pulUsedCmpDataLen,
    VOS_UINT32                          *pulUnCmpLen
);

extern VOS_UINT32 NAS_REPLAY_SavePubInfo(MsgBlock * pstMsg);
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Stub_Nas_GetPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
);
extern VOS_UINT32 NAS_REPLAY_SaveGuInfo(MsgBlock * pstMsg);
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Stub_Nas_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
);
extern VOS_UINT32 NAS_REPLAY_SaveMsNetCap(MsgBlock * pstMsg);
extern VOS_VOID  Stub_NAS_MML_GetMsNetworkCapability
(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU   *pstMsNetCap
);
extern VOS_UINT32 NAS_REPLAY_SaveUeIdTmsi(MsgBlock * pstMsg);
extern VOS_UINT8* Stub_NAS_MML_GetUeIdTmsi
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveLteCsSrvCfg(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetLteCsServiceCfg
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveTinType(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_NAS_MML_GetTinType
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveAddUpdateRslt(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_NAS_MML_GetAdditionUpdateRslt
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsBearCtx(MsgBlock * pstMsg);
extern NAS_MML_PS_BEARER_CONTEXT_STRU *  Stub_NAS_MML_GetPsBearerCtx
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsBearerExistBeforeIsrAct(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_NAS_MML_IsPsBearerExistBeforeIsrAct
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsBearerAfterIsrActExist(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_NAS_MML_IsPsBearerAfterIsrActExist
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveEmcNumList(MsgBlock * pstMsg);
extern NAS_MML_EMERGENCY_NUM_LIST_STRU*  Stub_NAS_MML_GetEmergencyNumList
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsRegContainDrxPara(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetPsRegContainDrx
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveUeEutranPsDrxLen(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetUeEutranPsDrxLen
(
   VOS_VOID
);

extern VOS_UINT32 NAS_REPLAY_SaveNonDrxTimer(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetNonDrxTimer
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveSplitPgCycleCode(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetSplitPgCycleCode
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveSplitOnCcch(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetSplitOnCcch
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveMsClassMark2(MsgBlock * pstMsg);
extern VOS_VOID  Stub_NAS_MML_Fill_IE_ClassMark2
(
   VOS_UINT8  *pClassMark2
);
extern VOS_UINT32 NAS_REPLAY_SaveCsAttachAllowFlg(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetCsAttachAllowFlg
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsAttachAllowFlg(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetPsAttachAllowFlg
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveMsMode(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetMsMode
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePlmnIdIsForbid(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_Nas_PlmnIdIsForbid
(
   MMC_LMM_PLMN_ID_STRU  *pstPlmnId
);
extern VOS_UINT32 NAS_REPLAY_SavePlmnExactlyCmpFlg(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetPlmnExactlyComparaFlg
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SavePsRegStatus(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetPsRegStatus
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveSimType(MsgBlock * pstMsg);
extern VOS_UINT8  Stub_NAS_MML_GetSimType
(
   VOS_VOID
);
extern VOS_UINT32 NAS_REPLAY_SaveKdfKey(MsgBlock * pstMsg);
extern VOS_INT32  Stub_BSP_KDF_KeyMake
(
    NAS_LMM_BSP_INPUT_PARA_STRU         *pstBspInputPara,
    NAS_LMM_BSP_OUTPUT_PARA_STRU        *pstBspOutputPara
);
extern VOS_UINT32 NAS_REPLAY_SaveSdfPara(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_APP_GetSdfPara
(
    VOS_UINT32                         *pulSdfNum,
    APP_ESM_SDF_PARA_STRU              *pstSdfPara
);
extern VOS_UINT32 NAS_REPLAY_SavePdpManageInfo(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_APP_GetPdpManageInfo
(
    APP_ESM_PDP_MANAGE_INFO_STRU  *pstPdpManageInfo
);

extern VOS_UINT32 NAS_REPLAY_SaveCardImsi(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_USIMM_GetCardIMSI
(
    VOS_UINT8      *pucImsi
);
extern VOS_UINT32 NAS_REPLAY_SaveServiceAvailable(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_USIMM_IsServiceAvailable
(
    UICC_SERVICES_TYPE_ENUM_UINT32  ulServiceType
);
extern VOS_UINT32 NAS_REPLAY_SaveUsimTestMode(MsgBlock * pstMsg);
extern VOS_UINT32  Stub_USIMM_IsTestCard
(
    VOS_VOID
);
#endif
#endif
#endif
/*****************************************************************************
  9 OTHERS
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

#endif /* end of PsNvInterface.h */





