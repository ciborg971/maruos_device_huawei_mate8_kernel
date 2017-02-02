

#ifndef __NASMMCEMMINTERFACE_H__
#define __NASMMCEMMINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasLmmPublic.h"
#include  "NasLmmPubMIntraMsg.h"
#include  "AppMmInterface.h"


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
  2 Macro
*****************************************************************************/
#define MMC_EMM_GetMainCtxAddr()        (&g_stMmcGlobalCtrl)

#define MMC_EMM_GetSimState()           ((MMC_EMM_GetMainCtxAddr())->ulSimStat)


#define MMC_EMM_GetHplmnActListAddr()   (&g_stNvDataHplmnAct)
#define MMC_EMM_GetUplmnActListAddr()   (&g_stUplmnAct)
#define MMC_EMM_GetOplmnActListAddr()   (&g_stOplmnAct)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    MMC_EMM_MSG_ID_ENUM
{
    /* EMM����MMC����Ϣԭ�� */
    ID_MMC_EMM_START_REQ                = ID_NAS_LMM_INTRA_MMC_EMM_START_REQ,
    ID_MMC_EMM_STOP_REQ                 = ID_NAS_LMM_INTRA_MMC_EMM_STOP_REQ,
    ID_MMC_EMM_PLMN_REQ                 = ID_NAS_LMM_INTRA_MMC_EMM_PLMN_REQ,
    ID_MMC_EMM_CELL_SELECTION_CTRL_REQ  = ID_NAS_LMM_INTRA_MMC_EMM_CELL_SELECTION_CTRL_REQ,
    ID_MMC_EMM_ACTION_RESULT_REQ        = ID_NAS_LMM_INTRA_MMC_EMM_ACTION_RESULT_REQ,
    ID_MMC_EMM_USIM_STATUS_IND          = ID_NAS_LMM_INTRA_MMC_EMM_USIM_STATUS_IND,

    /* MMC����EMM����Ϣԭ�� */
    ID_MMC_EMM_START_CNF                = ID_NAS_LMM_INTRA_MMC_EMM_START_CNF,
    ID_MMC_EMM_STOP_CNF                 = ID_NAS_LMM_INTRA_MMC_EMM_STOP_CNF,
    ID_MMC_EMM_PLMN_IND                 = ID_NAS_LMM_INTRA_MMC_EMM_PLMN_IND,
    ID_MMC_EMM_SYS_INFO_IND             = ID_NAS_LMM_INTRA_MMC_EMM_SYS_INFO_IND,
    ID_MMC_EMM_COVERAGE_LOST_IND        = ID_NAS_LMM_INTRA_MMC_EMM_COVERAGE_LOST_IND,

    ID_MMC_EMM_MSG_ID_ENUM_BUTT         = ID_NAS_LMM_INTRA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 MMC_EMM_MSG_ID_ENUM_UINT32;

enum    MMC_EMM_FORBIDDEN_INFO_ENUM
{
    MMC_EMM_NO_FORBIDDEN                = 0x0000,   /* �����κν�ֹ�б���*/
    MMC_EMM_FORBIDDEN                   = 0x0001,   /* �ڽ�ֹ�б���*/

    MMC_EMM_FORBIDDEN_INFO_BUTT
};
typedef VOS_UINT32 MMC_EMM_FORBIDDEN_INFO_ENUM_UINT32;


enum    MMC_EMM_CHANGE_INFO_ENUM
{
    MMC_EMM_NO_CHANGE   = 0x0000,    /* �κ���Ϣ��û�иı�              */
    MMC_EMM_CHANGE_PLMN  = 0x0001,   /* PLMN ID �ı�         */
    MMC_EMM_CHANGE_TA       = 0x0002,   /* TA �ı� */
    MMC_EMM_CHANGE_CELL  = 0x0004,   /* CELL ID �ı�     */

    MMC_EMM_CHANGE_INFO_BUTT
};
typedef VOS_UINT32 MMC_EMM_CHANGE_INFO_ENUM_UINT32;


enum    MMC_EMM_ACTION_TYPE_ENUM
{
    MMC_EMM_ACTION_TAU                  = 0,        /* TAU    */
    MMC_EMM_ACTION_ATTACH               = 1,        /* ATTACH */
    MMC_EMM_ACTION_DETACH               = 2,        /* DETACH */
    MMC_EMM_ACTION_SERVICE              = 3,        /* SERVICE */
    MMC_EMM_ACTION_AUTHENTICATION       = 4,        /* AUTHENTICATION */
    MMC_EMM_ACTION_NO_ACTION            = 5,        /* other*/
    MMC_EMM_ACTION_TYPE_BUTT
};
typedef VOS_UINT32 MMC_EMM_ACTION_TYPE_ENUM_UINT32;

enum    MMC_EMM_ACTION_RESULT_ENUM
{
    MMC_EMM_ACTION_SUCCESS              = 0,        /* �����ɹ� */
    MMC_EMM_ACTION_FAILURE              = 1,        /* ����ʧ�� */

    MMC_EMM_ACTION_RESULT_BUTT
};
typedef VOS_UINT32 MMC_EMM_ACTION_RESULT_ENUM_UINT32;

typedef NAS_MM_CN_CAUSE_ENUM_UINT8 MMC_EMM_ACTION_CAUSE_ENUM_UINT8;

/* EMMָʾMMC������ԭ��ֵ */
enum MMC_EMM_PLMN_REQ_CAUSE_ENUM
{
    MMC_EMM_PLMN_REQ_CAUSE_PS_START     = 0,        /* Э��ջ������Ҫ�������� */
    MMC_EMM_PLMN_REQ_CAUSE_PLMN_SELECT  = 1,        /* ��Ҫ����PLMNѡ�� */
    MMC_EMM_PLMN_REQ_CAUSE_BUTT
};
typedef VOS_UINT32 MMC_EMM_PLMN_REQ_CAUSE_ENUM_UINT32;


enum MMC_EMM_START_REQ_CAUSE_ENUM
{
    MMC_EMM_START_REQ_CAUSE_NORMAL_START    = 0,    /* �������� */
    MMC_EMM_START_REQ_CAUSE_NEED_RESET      = 1,    /* ��Ҫ��λ */
    MMC_EMM_START_REQ_CAUSE_BUTT
};
typedef VOS_UINT32 MMC_EMM_START_REQ_CAUSE_ENUM_UINT32;

/*��״̬*/
enum MMC_EMM_SIM_STAT_ENUM
{
    MMC_EMM_SIM_STATUS_UNAVAILABLE,
    MMC_EMM_SIM_STATUS_AVAILABLE,
    MMC_EMM_SIM_STATUS_BUTT
};
typedef VOS_UINT32 MMC_EMM_SIM_STAT_ENUM_UINT32;

/*�����ȼ�������ʶ*/
enum MMC_EMM_HITH_PRIO_ENUM
{
    MMC_EMM_HIGH_PRIO_UNAVAILABLE,
    MMC_EMM_HIGH_PRIO_AVAILABLE,
    MMC_EMM_HIGH_PRIO_BUTT
};
typedef VOS_UINT32 MMC_EMM_HIGH_PRIO_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : MMC_EMM_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_START_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    MMC_EMM_START_REQ_CAUSE_ENUM_UINT32 enCause;
} MMC_EMM_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_START_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_START_CNF_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} MMC_EMM_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_STOP_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    VOS_UINT32                          ulReserved;

} MMC_EMM_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_STOP_CNF_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} MMC_EMM_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_PLMN_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_PLMN_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    MMC_EMM_PLMN_REQ_CAUSE_ENUM_UINT32  enCause; /* ����������ԭ�� */
} MMC_EMM_PLMN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_PLMN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_PLMN_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} MMC_EMM_PLMN_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_EMMC_CELL_SELECTION_CTRL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS_EMMC_CELL_SELECTION_CTRL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    VOS_UINT32                          ulReserved;

} MMC_EMM_CELL_SELECTION_CTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_SYS_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_SYS_INFO_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

    MMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;           /* PLMN ID            */
    NAS_MM_TAC_STRU                     stTac;              /* Tracking Area Code */
    VOS_UINT32                          ulCellId;           /* Cell Identity      */
    MMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo;    /* ��ֹ��Ϣ */
} MMC_EMM_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_COVERAGE_LOST_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_COVERAGE_LOST_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} MMC_EMM_COVERAGE_LOST_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_ACTION_RESULT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_ACTION_RESULT_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

    MMC_EMM_ACTION_TYPE_ENUM_UINT32     ulEmmActionType; /* EMM���в��������� */

    MMC_EMM_ACTION_RESULT_ENUM_UINT32   ulActionResult;  /* �������          */

    MMC_EMM_ACTION_CAUSE_ENUM_UINT8     ucCause;         /* ����ʧ��ԭ��      */

    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulAttemptCount;  /* ATTACH��TAUʧ�ܳ��Դ��� */

    NAS_MM_PLMN_LIST_STRU               stEplmn;         /* ��Ч��PLMN        */

} MMC_EMM_ACTION_RESULT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_USIM_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_USIM_STATUS_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    USIMM_CARD_STATUS_ENUM_UINT32       enCardStatus;   /* USIM״̬
 */
}MMC_EMM_USIM_STATUS_IND_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32   g_ulNvDataMapNum;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID    NAS_EMMC_FsmReg(     VOS_VOID );
/*extern  NAS_EMMC_ERROR_CODE_ENUM_UINT32 NAS_EMMC_MsgProcessInFsm
        (
            MsgBlock                   *pMsg,
            VOS_UINT32                  ulEventType
        );*/

extern  VOS_VOID    NAS_LMM_GetRegServiceState
    (
        APP_EMM_REG_STATE_ENUM_UINT32       *pulRegState,
        APP_EMM_SRV_STATE_ENUM_UINT32       *pulServiceState
    );
extern VOS_VOID    NAS_LMM_GetPlmnSelMode
    (
        APP_EMM_SEL_MODE_ENUM_UINT32        *pulPlmnSelMode
    );
extern VOS_VOID    NAS_LMM_GetRplmnAndEplmnInfo
(
    APP_EMM_EPLMN_LIST_STRU             *pstEPlmnList,
    APP_PLMN_ID_STRU                    *pstRplmn
);
extern VOS_VOID    NAS_LMM_GetForbInfo
    (
        APP_EMM_PLMN_LIST_STRU              *pstFplmnList,
        APP_TA_LIST_STRU                    *pstForbTaList
    );
extern VOS_VOID NAS_EMMC_WriteSimMncLength(VOS_UINT8    ucMncLen);
extern VOS_VOID    NAS_EMMC_ClearFplmnGlobal( VOS_VOID );
extern VOS_VOID     NAS_EMMC_SendEmmCoverageLostInd( VOS_VOID );
extern NAS_EMMC_ERROR_CODE_ENUM_UINT32 NAS_EMMC_AnyStateMsgEmmStartReq
(
   MsgBlock                            *pMsg
);
extern NAS_EMMC_ERROR_CODE_ENUM_UINT32 NAS_EMMC_AnyStateMsgEmmStopReq
        (
            MsgBlock                            *pMsg
        );
extern NAS_EMMC_ERROR_CODE_ENUM_UINT32 NAS_EMMC_AnyStateMsgAppPlmnReselReq
        (
            MsgBlock                            *pMsg
        );

extern NAS_EMMC_ERROR_CODE_ENUM_UINT32  NAS_EMMC_AnyStateMsgAppPlmnSelReq( MsgBlock   *pMsg);
extern VOS_UINT32  NAS_LMM_AnyStateMsgAppInqPlmnSelReq( MsgBlock   *pMsg );
extern NAS_EMMC_ERROR_CODE_ENUM_UINT32 NAS_EMMC_AnyStateMsgAppLockPlmnReq(MsgBlock *pMsg);
extern  VOS_VOID  NAS_EMMC_UpdateForbTaList( VOS_VOID );

extern  VOS_UINT32 * NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_ENUM_UINT32 ulGlobleParaName);
extern  VOS_UINT8 * NAS_EMMC_GetMmcGlobleAddr(NAS_LMM_GLOBLE_PARA_ENUM_UINT32 ulGlobleParaName);
extern  VOS_VOID    NAS_EMMC_WriteUplmn2Nv( VOS_VOID );
extern  VOS_VOID    NAS_EMMC_WriteFplmn2Nv( VOS_VOID );
extern  VOS_VOID    NAS_EMM_AppRegStatInd( NAS_APP_REG_STAT_ENUM_UINT32   ulNasAppState,
                                           NAS_LMM_MAIN_STATE_ENUM_UINT16  enMainState);
extern  VOS_UINT32  NAS_LMM_GetFplmnMaxNum( VOS_VOID);
extern  VOS_VOID    NAS_EMMC_DeleteCurrentAreaCellId( VOS_VOID );
extern  VOS_VOID    NAS_EMMC_ReadMmcNvim( VOS_VOID );
extern  VOS_VOID    NAS_EMMC_SetMmcInitValue( VOS_VOID );
extern  VOS_VOID    NAS_EMMC_SetHplmnSearchTimerGlobParaDefValue( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_CheckSimLrvTaiValid( const VOS_UINT8 *pucSimRecord,
                                                      const VOS_UINT32 ulIndex,
                                                      const VOS_UINT32 ulLen );
extern VOS_UINT32  NAS_EMM_CheckSimGutiValid( const VOS_UINT8 *pucSimRecord,
                                                          const VOS_UINT32 ulIndex,
                                                          const VOS_UINT32 ulLen );
extern VOS_VOID    NAS_EMMC_SendIntraUsimStatusInd(const USIMM_CARD_STATUS_ENUM_UINT32 enUsimStatusInd );
extern VOS_UINT32  NAS_EMMC_AnyStateMsgUsimStatusInd(     MsgBlock *pMsg );
extern VOS_VOID    NAS_EMMC_FsmInit( VOS_VOID );
extern NAS_EMMC_ERROR_CODE_ENUM_UINT32  NAS_EMMC_AnyStateMsgAppPlmnListReq
        (
            MsgBlock                           *pMsg
        );



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

#endif /* end of MmcEmmInterface.h */
