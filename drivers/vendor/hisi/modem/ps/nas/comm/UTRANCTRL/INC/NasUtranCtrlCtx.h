
#ifndef _NAS_UTRANCTRL_CTX_H_
#define _NAS_UTRANCTRL_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "NasFsm.h"
#include  "NasUtranCtrlInterface.h"
#include  "NasMmlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN                    (1600)              /* �������󳤶� */

#define NAS_UTRANCTRL_OCTET_MOVE_SIXTEEN_BITS               (0x10)              /* ��һ���ֽ��ƶ�16λ */
#define NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM                     (20)                /* ��󻺴�ĸ��� */

#define NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM (0XFF)              /* ģʽ�Զ��л���֧������SIM������UTRANģʽ���л� */
#define NAS_UTRANCTRL_TIMER_ID_START_INDEX                  (9000)              /* UTRANCTRLģ�鶨ʱ��ID�Ŀ�ʼ���� */

#define NAS_UTRANCTRL_HONGKONG_MCC                          (0x40504)           /* ��۹����� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_UTRANCTRL_FSM_ID_ENUM
{
    /* UTRANCTRL MAIN̬״̬�������� */
    NAS_UTRANCTRL_FSM_MAIN                                  = 0X00,

    /* UTRANCTRL ����״̬�� */
    NAS_UTRANCTRL_FSM_SWITCH_ON                             = 0X01,

    /* UTRANCTRL �ػ�״̬�� */
    NAS_UTRANCTRL_FSM_POWER_OFF                             = 0X02,

    /* UTRANCTRL PLMN SELECTION ״̬�� */
    NAS_UTRANCTRL_FSM_PLMN_SELECTION                        = 0X03,

    /* UTRANCTRL SYSCFG״̬�� */
    NAS_UTRANCTRL_FSM_SYSCFG                                = 0X04,

    /* UTRANCTRL ģʽ�ı�״̬�� */
    NAS_UTRANCTRL_FSM_MODE_CHANGE                           = 0X05,

    NAS_UTRANCTRL_FSM_BUTT

};
typedef VOS_UINT32 NAS_UTRANCTRL_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MMC_WAIT_AS_START_CNF_ENUM
 �ṹ˵��  : ���ڱ���յ���GU�����Ŀ����ظ���Ϣ
*****************************************************************************/
enum NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_ENUM
{
    NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL                  = 0x00,
    NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF                   = 0x01,
    NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF                   = 0x02,
    NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF                    = 0x04,
    NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF                   = 0x08,
};
typedef VOS_UINT8 NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_ENUM_UINT8;


enum NAS_UTRANCTRL_MASTER_MODE_ENUM
{
    NAS_UTRANCTRL_MASTER_MODE_WCDMA,                                            /* ��ģΪWCDMA */
    NAS_UTRANCTRL_MASTER_MODE_TDSCDMA,                                          /* ��ģΪTDSCDMA */
    NAS_UTRANCTRL_MASTER_MODE_GSM,                                              /* ��ģΪGSM */
    NAS_UTRANCTRL_MASTER_MODE_LTE,                                              /* ��ģΪLTE */
    NAS_UTRANCTRL_MASTER_MODE_BUTT
};
typedef VOS_UINT8 NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8;



enum NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM
{
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY               = 0,                 /* ��ǰΪFDD ONLY */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY               = 1,                 /* ��ǰΪTDD ONLY */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO                   = 2,                 /* ��ǰ�Զ��л�ģʽ */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_BUTT                   = 3
};
typedef VOS_UINT8 NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8;
enum NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM
{
    NAS_UTRANCTRL_INIT_CTX_STARTUP                    = 0,
    NAS_UTRANCTRL_INIT_CTX_POWEROFF                   = 1,
    NAS_UTRANCTRL_INIT_CTX_BUTT
};
typedef VOS_UINT32 NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8;

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
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN];
} NAS_UTRANCTRL_ENTRY_MSG_STRU;


typedef struct
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       stMsgEntry;     /* ����ľ������� */
}NAS_UTRANCTRL_CACH_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCurrIndex;                            /* ��¼��ǰ�������index */
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_UTRANCTRL_CACH_MSG_INFO_STRU   astMsgQueue[NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM]; /* MMC����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}NAS_UTRANCTRL_MSG_QUEUE_STRU;
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0��UTRANģʽΪFDD 1��UTRANģʽΪTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* ֧��TD����Ĺ��ҺŸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ����IMSI PLMN����UTRANģʽ�Ƿ�AUTO SWITCHʱ����ǰIMSI��PLMN�ڴ��б��еĶ�֧���Զ��л�������̶�ΪWģ */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];/* ��TD����Ĺ������б� */
    NAS_MML_PLMN_ID_STRU                astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];/* IMSI PLMN �б� */
}NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU;




typedef struct
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enCurrUtranMode;    /* NVIM�б����UTRANģʽ */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enPreUtranMode;     /* �ϴη���RRC��UTRANģʽ */

    VOS_UINT8                                               ucReserved;         /* �����ֶ� */

    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;/* ��ǰUTRAN���Զ��л�ģʽ */
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU               stUtranModeAutoSwitch;/* ģʽ�Զ��л���Ϣ  */

    VOS_UINT8                                               ucIsUtranTddCsSmcNeeded; /* NVIM�б����UTRANTDD CS SMC�Ƿ���Ҫ */
    VOS_UINT8                                               ucIsUtranTddPsSmcNeeded; /* NVIM�б����UTRANTDD PS SMC�Ƿ���Ҫ */
    VOS_UINT8                                               aucReserved[2];

}NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU;


typedef struct
{
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU  stCustomCfg;                           /* NVIM�еĶ�����Ϣ */
 }NAS_UTRANCTRL_MS_CFG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucSearchedSpecTdMccFlg;                 /* ��¼�Ƿ����ѵ��й������ʶ */
    VOS_UINT8                           aucReserve[3];
}NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU;
typedef struct
{
    VOS_UINT8                           ucAbortFlg;                             /* ״̬����ϱ�� */
    VOS_UINT8                           aucReserve[3];
}NAS_UTRANCTRL_FSM_PLMN_SELECTION_CTX_STRU;
typedef struct
{
    VOS_UINT8                                               ucWaitSlaveModeUtranModeCnfFlg;
    VOS_UINT8                                               aucReserve[3];
}NAS_UTRANCTRL_FSM_MODE_CHANGE_CTX_STRU;


typedef union
{
    NAS_UTRANCTRL_FSM_PLMN_SELECTION_CTX_STRU               stPlmnSelectionCtx;

    NAS_UTRANCTRL_FSM_MODE_CHANGE_CTX_STRU                  stModeChangeCtx;
}NAS_UTRANCTRL_FSM_EXTRA_CTX_UNION;



typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                                /* L1״̬ */

    /* �����ϢMSGID������  */
    NAS_UTRANCTRL_ENTRY_MSG_STRU        stEntryMsg;

    /* ״̬������ */
    NAS_UTRANCTRL_FSM_EXTRA_CTX_UNION   unFsmCtx;

}NAS_UTRANCTRL_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucReplaceMmcMsgFlg;                     /* �滻����MMC����Ϣ���:VOS-TRUE:��Ҫ�û������Ϣ�滻����MMC����Ϣ��VOS_FALSE:����Ҫ�滻����MMC����Ϣ */

    VOS_UINT8                           ucSwitchOnPlmnSearchFlag;            /* ��ʶ�Ƿ�Ϊ��������������ֻ�п�������������������tds�Ĵ���VOS_TRUE:�ǿ������� */
    VOS_UINT8                           aucReserve[2];

    NAS_UTRANCTRL_ENTRY_MSG_STRU        stBufferUtranSndMmcMsg;                 /* �����W/TD���͸�MMC����Ϣ */
    NAS_UTRANCTRL_ENTRY_MSG_STRU        stBufferMmcSndUtranMsg;                 /* �����MMC���͸�W/TD����Ϣ */
}NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucUeSndPcRecurFlg;                      /* PC�ط��Ƿ���Ҫ����ȫ�ֱ���,VOS_TRUE:��Ҫ, VOS_FALSE:����Ҫ, */
    VOS_UINT8                           aucRsv3[3];
}NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU;
typedef struct
{
    NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU                     stUeMaintainInfo;   /* PC�ط���Ϣ�ṹ�� */

}NAS_UTRANCTRL_MAINTAIN_CTX_STRU;
typedef struct
{
    NAS_UTRANCTRL_FSM_CTX_STRU                              stCurFsm;               /* ��ǰ��״̬����Ϣ */
    NAS_UTRANCTRL_MS_CFG_INFO_STRU                          stMsCfgInfo;            /* MS��������Ϣ */

    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU                       stMainCtrlInfo;         /* ״̬��ջ��Ϣ */
    NAS_UTRANCTRL_MSG_QUEUE_STRU                            stBufferEntryMsgQueue;  /* NAS UNTRANCTRL������Ϣ���� */
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU                 stPlmnSearchCtrl;       /* PLMN�������������� */
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                         stMaintainInfo;         /* ��ν�ɲ������� */
}NAS_UTRANCTRL_CTX_STRU;
#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
NAS_UTRANCTRL_CTX_STRU* NAS_UTRANCTRL_GetUtranCtrlCtx( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_InitCustomCfgInfo(
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU   *pstCustomCfg
);

VOS_VOID  NAS_UTRANCTRL_InitMsCfgCtx(
    NAS_UTRANCTRL_MS_CFG_INFO_STRU       *pstMsCfgInfo
);

VOS_VOID  NAS_UTRANCTRL_InitCurrFsmCtx(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurrFsmCtx
);
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetPreUtranMode(VOS_VOID);
VOS_VOID NAS_UTRANCTRL_SetPreUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);

VOS_VOID NAS_UTRANCTRL_SetCurrUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8   enUtranMode
);

VOS_VOID NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded
);

VOS_VOID NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded
);
NAS_UTRANCTRL_FSM_CTX_STRU* NAS_UTRANCTRL_GetCurFsmAddr(VOS_VOID);

NAS_FSM_DESC_STRU* NAS_UTRANCTRL_GetCurFsmDesc(VOS_VOID);

NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetCurrEntryMsgAddr(VOS_VOID);

NAS_UTRANCTRL_FSM_ID_ENUM_UINT32 NAS_UTRANCTRL_GetCurrFsmId(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_GetCurrFsmEventType(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 NAS_UTRANCTRL_FSM_GetCurrState(VOS_VOID);


VOS_VOID  NAS_UTRANCTRL_InitInternalMsgQueue(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstMsgQueue
);

VOS_VOID  NAS_UTRANCTRL_SwitchCurrFsmCtx(
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enNewFsmId
);

VOS_VOID  NAS_UTRANCTRL_InitMainCtrlInfo(
    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU  *pstMainCtrl
);

VOS_VOID  NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferEntryMsgQueue
);

VOS_VOID  NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU       *pstPlmnSearchCtrl
);

VOS_VOID  NAS_UTRANCTRL_InitMaintainInfo(
    NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8                  enInitType,
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                        *pstMaintainInfo
);

VOS_VOID NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag
);
VOS_UINT8 NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag(VOS_VOID);



VOS_VOID NAS_UTRANCTRL_SetReplaceMmcMsgFlg(
    VOS_UINT8       ucReplaceFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetReplaceMmcMsgFlg(VOS_VOID);

NAS_UTRANCTRL_MSG_QUEUE_STRU* NAS_UTRANCTRL_GetCachMsgBufferAddr(VOS_VOID);
VOS_VOID* NAS_UTRANCTRL_GetNextCachBufferMsg(VOS_VOID);
VOS_VOID  NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Main(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_SwitchOn(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PowerOff(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PlmnSelection(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Syscfg(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_ModeChange(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_UTRANCTRL_GetSearchedSpecTdMccFlg(VOS_VOID);

VOS_UINT32* NAS_UTRANCTRL_GetSpecTdMccList(VOS_VOID);

VOS_UINT8   NAS_UTRANCTRL_GetSpecTdMccListNum(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_SetCurUtranSwitchMode(
    VOS_UINT8                               ucSwitchMode
);

VOS_UINT8 NAS_UTRANCTRL_GetUePcRecurFlg(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetCurUtranSwitchMode(VOS_VOID);


VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg(VOS_VOID);
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr(VOS_VOID);
VOS_UINT32 NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(VOS_VOID);


/* ����״̬�������Ĳ������� */
VOS_VOID NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(
    VOS_UINT8       ucAbortFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetAbortFlg_PlmnSelection(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr(VOS_VOID);


NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU* NAS_UTRANCTRL_GetUtranModeAutoSwtich(VOS_VOID);


VOS_UINT8  NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg
);

VOS_VOID  NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitUtranModeCnfFlg
);

VOS_VOID  NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange(VOS_VOID);


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

#endif /* end of NasNAS_UTRANCTRLCtx.h */
