
#ifndef _TAF_SPM_CTX_H_
#define _TAF_SPM_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "TafFsm.h"
#include  "TafSpmTimerMgmt.h"
#include  "Taf_MmiStrParse.h"
#if (FEATURE_ON == FEATURE_IMS)
#include  "ImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_SPM_MAX_MSG_BUFFER_LEN                    (1200)                    /* �������󳤶� */
/*
 * ע: Ŀǰÿ��ҵ������queue��ౣ��һ��ҵ��������Ϣ�����ڶ���queue���в�����֧�ֱ�����
 *     ҵ������Ĵ�����Ŀǰһ��ҵ������ֻ��Ӧһ��timer(��TAF_SPM_TIMER_ID_ENUM_UINT32ö
 *     �ٶ���)�����֧��ͬ����ҵ��֧�ֶ������, ����������Ӧ��ʱ����Ŀ����������������,
 *     �м�!!!
 */
#define TAF_SPM_MAX_CC_MSG_QUEUE_NUM                  (1)       /* ��󻺴������ҵ����ص���Ϣ���� */
#define TAF_SPM_MAX_SMS_MSG_QUEUE_NUM                 (3)       /* ��󻺴���SMSҵ����ص���Ϣ���� */
#define TAF_SPM_MAX_SS_MSG_QUEUE_NUM                  (1)       /* ��󻺴���SSҵ����صĸ��� */

#define TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM               (1)       /* �����ز�����queue�����Ŀ */
#define TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM              (1)       /* �����ز�����queue�����Ŀ */
#define TAF_SPM_MAX_SS_REDIAL_QUEUE_NUM               (1)       /* ����ҵ���ز�����queue�����Ŀ */

#define TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM       (5)                       /* ���client IDʵ��״̬������ */
#define TAF_SPM_INVALID_CLIENT_ID                     OMA_CLIENT_ID_BUTT        /* ��Ч��client id */
#define TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX    (0xff)
#define TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN             (40)
#define TAF_SPM_SSC_FDN_CHECK_BCD_MAX_LEN             (TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN / 2)
#define TAF_SPM_SSC_FDN_CHECK_7BIT_MAX_LEN            (((TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN * 8) + 6) / 7)
#define TAF_SPM_SSC_MAX_LEN                           (256)
#define TAF_SPM_CALL_CTRL_SS_STRING_LEN               ((TAF_SPM_SSC_MAX_LEN / 2) + 1)
#define TAF_SPM_USSD_STRING_LEN                       (160)
#define TAF_SPM_CALL_CTRL_USSD_STRING_LEN             (TAF_SPM_USSD_STRING_LEN + 1)
#define TAF_SPM_USSD_STR_MAX_LEN                      (256)
#define TAF_SPM_SSC_OFFSET                            (1)
#define TAF_SPM_NUM_TYPE_INVALID                      (0xff)                    /* ��Ч�������� */
#define TAF_SPM_FDN_CHECK_STR_MAX_LEN                 (40)
#define TAF_SPM_FDN_CHECK_BCD_MAX_LEN                 (TAF_SPM_FDN_CHECK_STR_MAX_LEN / 2)
#define TAF_SPM_FDN_CHECK_7BIT_MAX_LEN                (((TAF_SPM_FDN_CHECK_STR_MAX_LEN * 8) + 6) / 7)
#define TAF_SPM_GET_7BIT_STRING_SIZE(ulPackStrLen,ulUnpackStrLen) (ulUnpackStrLen = ((ulPackStrLen * 8) + 6) / 7)
#define TAF_SPM_GET_BCD_NUBMER_LENGTH(ulAsciiLength)                            (((ulAsciiLength) + 1)/2)

#define TAF_SPM_USIM_FILE_FIRST_RECORD                  (1)

#define TAF_SPM_USIM_FILE_SECOND_RECORD                 (2)

#define TAF_SPM_USIM_FILE_MAX_RECORD                    (255)


#define NAS_SPM_ONE_THOUSAND_MILLISECOND                (1000)                  /* 1000MS */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_SPM_FSM_ID_ENUM
{
    /* SPM MAIN̬״̬�������� */
    TAF_SPM_FSM_MAIN                                        = 0X00,

    /* SPM SERVICE CTRL״̬�� */
    TAF_SPM_FSM_SERVICE_CTRL                                = 0X01,

    TAF_SPM_FSM_BUTT

};
typedef VOS_UINT32 TAF_SPM_FSM_ID_ENUM_UINT32;



enum
{
    TAF_SPM_SRV_REQ_TYPE_CALL,                  /* CALL service request */
    TAF_SPM_SRV_REQ_TYPE_SS,                    /* SS service request */
    TAF_SPM_SRV_REQ_TYPE_SMS,                   /* SMS service request */

    TAF_SPM_SRV_REQ_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8;
enum TAF_SPM_SERVICE_STATUS_ENUM
{
    TAF_SPM_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* �������� */
    TAF_SPM_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* ���Ʒ��� */
    TAF_SPM_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* ������������� */
    TAF_SPM_SERVICE_STATUS_NO_IMSI                  = 3,                        /* ��imsi */
    TAF_SPM_SERVICE_STATUS_NO_SERVICE               = 4,                        /* �޷��� */
    TAF_SPM_SERVICE_STATUS_NO_CHANGE                = 5,
    TAF_SPM_SERVICE_STATUS_DEEP_SLEEP               = 6,
    TAF_SPM_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SPM_SERVICE_STATUS_ENUM_UINT8;
enum TAF_SPM_VP_NV_CFG_STATE_ENUM
{
    TAF_SPM_VP_MO_MT_BOTH               = 0,                                    /* ������Ƶ����(�������кͱ���) */
    TAF_SPM_VP_NONE                     = 1,                                    /* ��ֹ��Ƶ���кͱ��� */
    TAF_SPM_VP_MO_ONLY                  = 2,                                    /* ������Ƶ���У���ֹ��Ƶ���� */
    TAF_SPM_VP_MT_ONLY                  = 3,                                    /* ��ֹ��Ƶ���У�������Ƶ���� */
    TAF_SPM_VP_BUTT
};
typedef VOS_UINT8   TAF_SPM_VP_NV_CFG_STATE_ENUM_UINT8;


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

typedef VOS_UINT32  (*TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR)(struct MsgCB *pstMsg, VOS_UINT16 *pusClientId);


typedef struct
{
    VOS_UINT32                          ulSndPid;
    TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR  pGetMsgClientIdProcFunc;
}TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU;




typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_SPM_MAX_MSG_BUFFER_LEN];
} TAF_SPM_ENTRY_MSG_STRU;


typedef struct
{
    TAF_SPM_ENTRY_MSG_STRU              stMsgEntry;                             /* ����ľ������� */
}TAF_SPM_CACHE_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                             /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_CC_MSG_QUEUE_NUM]; /* SPM����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_SPM_MSG_CC_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_SMS_MSG_QUEUE_NUM]; /* SPM����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_SPM_MSG_SMS_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_SS_MSG_QUEUE_NUM]; /* SPM����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_SPM_MSG_SS_QUEUE_STRU;


typedef struct
{
    TAF_SPM_MSG_CC_QUEUE_STRU           stCcMsgQueue;                               /* buffer CC service request message queue */
    TAF_SPM_MSG_SMS_QUEUE_STRU          stSmsMsgQueue;                              /* buffer SMS service request message queue */
    TAF_SPM_MSG_SS_QUEUE_STRU           stSsMsgQueue;                               /* buffer SS service request message queue */
}TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM];
}TAF_SPM_CC_REDIAL_QUEUE_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM];
}TAF_SPM_SMS_REDIAL_QUEUE_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_SS_REDIAL_QUEUE_NUM];
}TAF_SPM_SS_REDIAL_QUEUE_STRU;
typedef struct
{
    TAF_SPM_CC_REDIAL_QUEUE_STRU        stCcMsgQueue;                               /* ���������Ϣ */
    TAF_SPM_SMS_REDIAL_QUEUE_STRU       stSmsMsgQueue;                              /* ���������Ϣ */
    TAF_SPM_SS_REDIAL_QUEUE_STRU        stSsMsgQueue;                               /* ���油��ҵ����Ϣ */
}TAF_SPM_REDIAL_MSG_CTX_STRU;
typedef struct
{
    VOS_UINT32                          ulSubscriptId;              /* my subscriptId in IMS */
    VOS_UINT8                           ucImsSmsSupported;          /* IMS SMS supported by IMS server, from ext_info */
    VOS_UINT8                           ucImsSmsSendingFlg;         /* IMS�������ڷ��ͱ�־ */
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus;              /* �ϴε�PS����״̬ */
    VOS_UINT8                           aucReserve[1];

    /* ɾ��IMSע��״̬���Ƶ�SDC�� */
    TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU   stBufferMsgQueue;           /* buffer mesage queue */
    TAF_SPM_REDIAL_MSG_CTX_STRU         stRedialMsgQueue;
}TAF_SPM_DOMAIN_SEL_CTX_STRU;



typedef struct
{
    VOS_UINT8                           aucReserve[4];
}TAF_SPM_SERVICE_CTRL_CTX_STRU;


typedef union
{
    TAF_SPM_SERVICE_CTRL_CTX_STRU                           stServiceCtrlCtx;

}TAF_SPM_FSM_EXTRA_CTX_UNION;




typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                                /* ��ǰ״̬ */

    /* �����ϢMSGID������  */
    TAF_SPM_ENTRY_MSG_STRU              stEntryMsg;

    /* ״̬������������ */
    TAF_SPM_FSM_EXTRA_CTX_UNION         unFsmCtx;

}TAF_SPM_FSM_CTX_STRU;



typedef struct
{
    TAF_SPM_FSM_CTX_STRU                stFsmCtx;                  /* ״̬����������Ϣ */

    /*********************����ҵ���ͨ����client id,����ʶ��ָ����״̬��******************************/
    VOS_UINT16                          usClientId;

    VOS_UINT8                           ucRunFlg;                  /* ״̬��������:VOS_TRUE:״̬����clientd ID��ռ�÷����� */
    VOS_UINT8                           aucRsv[1];
}TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU;
typedef struct
{
    TAF_SPM_FSM_CTX_STRU                stFsmCtx;               /* ״̬����������Ϣ */
}TAF_SPM_MAIN_FSM_CTX_STRU;
typedef struct
{
    VOS_UINT8                           ucUpdateEntryMsgFlg;                /* ���������Ϣ���:VOS-TRUE:��Ҫ����service ctrl�������Ϣ��VOS_FALSE:����Ҫ����,ֱ��͸�� */
    VOS_UINT8                           aucRsv[2];
    TAF_SPM_ENTRY_MSG_STRU              stServiceCtrlEntryMsg;              /* ���º��service ctrl�������Ϣ */
}TAF_SPM_MAIN_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU
 �ṹ˵��  : ��ѡ�񻺴�������󱣻���ʱ�������Ϣ
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBufferCcProtectTimerLen;              /* 0: ��ѡ��ʱ�����л��棻����0: ����CC����ı�����ʱ��ʱ������λ ms */
    VOS_UINT32                          ulBufferSmsProtectTimerLen;             /* 0: ��ѡ��ʱ�����л��棻����0: ����SMS����ı�����ʱ��ʱ������λ ms */
    VOS_UINT32                          ulBufferSsProtectTimerLen;              /* 0: ��ѡ��ʱ�����л��棻����0: ����SS����ı�����ʱ��ʱ������λ ms */
}TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU;
typedef struct
{
    VOS_UINT8                           ucSimCallCtrlSupportFlg;            /* SIM����call ctrl֧�ֱ�� */
    TAF_SPM_VP_NV_CFG_STATE_ENUM_UINT8  enVpCfgState;
    VOS_UINT8                           aucRsv[2];


    TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU           stBufferServiceReqProtectTimerInfo;                 

    VOS_UINT32                          ulMeStatus;
}TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU;


typedef struct
{
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
    MN_CALL_SUBADDR_STRU                stSubaddr;
    TAF_CS_CAUSE_ENUM_UINT32            enCheckRslt;                            /* ��¼����� */
    VOS_UINT32                          ulCheckCnfFlag;                         /* VOS_TRUE: �Ѿ��ظ�����VOS_FALSE:û�лظ��� */
}TAF_SPM_CALL_CHECK_INFO_STRU;


typedef struct
{
    VOS_UINT16                              usClientId;
    MN_OPERATION_ID_T                       ucopId;                             /* Operation ID */
    MN_CALL_TYPE_ENUM_U8                    enCallType;                         /* call Type */
    MN_CALL_MODE_ENUM_U8                    enCallMode;                         /* call mode */
    VOS_UINT8                               ucCallNum;                          /* �ܵĵ绰������� */
    VOS_UINT8                               ucSendSuccNum;                      /* ������ɹ��ĺ������ */
    VOS_UINT8                               ucRcvNum;                           /* �յ��ظ��ļ����� */
    MN_CALL_CS_DATA_CFG_STRU                stDataCfg;
    TAF_SPM_CALL_CHECK_INFO_STRU            astEconfCheckInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];
}TAF_SPM_CALL_ECONF_INFO_STRU;


typedef struct
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                   astEntityFsm[TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM];   /* ������client ID��Ӧ��״̬������ */

    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurrEntityFsm;                               /* ��ǰclient id����Ӧ��״̬����Ϣ */

    TAF_SPM_MAIN_FSM_CTX_STRU                               stCurMainFsm;                                   /* ��ǰ��״̬����Ϣ */

    TAF_SPM_TIMER_CTX_STRU                                  astSpmTimerCtx[TAF_SPM_MAX_TIMER_NUM];          /* SPM��ǰ�������еĶ�ʱ����Դ */

    TAF_SPM_MAIN_CTRL_INFO_STRU                             stMainCtrlInfo;                                 /* ��ܿ�����Ϣ */

    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                      stServiceCtrlCfgInfo;                           /* ҵ�����������Ϣ */

    TAF_SPM_DOMAIN_SEL_CTX_STRU                             stDomainSelCtx;                                 /* ��ѡ����Ϣ������� */

    TAF_SPM_CALL_ECONF_INFO_STRU                            stEconfInfo;

    VOS_UINT8                                               ucEcallHangUpImsFlag;
    VOS_UINT8                                               aucRsv[3];
}TAF_SPM_CONTEXT_STRU;
typedef VOS_UINT32  (*TAF_SPM_CALL_CTRL_MODIFY_FUNC_PTR)(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);


typedef struct
{
    MN_MMI_OPERATION_TYPE_ENUM_U8       ucMmiOperationType;                       /*��ǰ�Ĳ�������*/
    VOS_UINT8                           aucReserved1[3];
    TAF_SPM_CALL_CTRL_MODIFY_FUNC_PTR   pModifyFunc;
}TAF_SPM_SS_CALL_CTRL_MODIFY_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*******************************״̬�������Ĳ���API��������******************************/
VOS_VOID    TAF_SPM_SetCurrEntityFsmClientId(
    VOS_UINT16                          usClientId
);
VOS_UINT16  TAF_SPM_GetCurrEntityFsmClientId(VOS_VOID);

VOS_VOID    TAF_SPM_SetCurrEntityFsmState(
    VOS_UINT32                          ulState
);
VOS_UINT32  TAF_SPM_GetCurrEntityFsmState(VOS_VOID);


VOS_VOID    TAF_SPM_SetCurrEntityFsmRunFlg(
    VOS_UINT8                           ucRunFlg
);
VOS_UINT8   TAF_SPM_GetCurrEntityFsmRunFlg(VOS_VOID);


VOS_VOID TAF_SPM_SetCurrEntityFsmAddr(
    VOS_UINT8                           ucFsmIndex
);
TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmAddr(VOS_VOID);

TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmCtxAddr(VOS_VOID);

TAF_SPM_MAIN_FSM_CTX_STRU* TAF_SPM_GetCurrMainFsmAddr(VOS_VOID);

TAF_SPM_FSM_ID_ENUM_UINT32  TAF_SPM_GetCurrEntityFsmId(VOS_VOID);

/***********************������������****************************/
VOS_UINT16 TAF_SPM_GetEntityFsmClientIdByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

VOS_UINT32 TAF_SPM_GetCurrEntityFsmEntryMsgSndPid(VOS_VOID);
VOS_UINT16 TAF_SPM_GetCurrEntityFsmEntryMsgName(VOS_VOID);

VOS_UINT8 TAF_SPM_GetEntityFsmIndexByClientId(
    VOS_UINT16                          usClientId
);
VOS_UINT8 TAF_SPM_GetIdleEntityFsmIndex(VOS_VOID);

VOS_UINT8 TAF_SPM_GetEntityFsmRunFlgByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

TAF_SPM_TIMER_CTX_STRU*  TAF_SPM_GetTimerCtxAddr( VOS_VOID );

TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU*  TAF_SPM_GetServiceCtrlCfgInfoAddr( VOS_VOID );

VOS_VOID TAF_SPM_SetUpdateEntryMsgFlg(
    VOS_UINT8                           ucReplaceFlg
);

VOS_UINT8 TAF_SPM_GetUpdateEntryMsgFlg(VOS_VOID);


TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetServiceCtrlEntryMsgAddr(VOS_VOID);

VOS_VOID TAF_SPM_UpdateServiceCtrlEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_GetClientIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_VOID TAF_SPM_GetOpIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucOpId
);

VOS_UINT32 TAF_SPM_GetClientIdWithVosTimerMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT32 TAF_SPM_GetClientIdWithUsimMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);


VOS_UINT32 TAF_SPM_GetClientIdWithPbMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT32 TAF_SPM_GetClientIdWithTafMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_VOID  TAF_SPM_InitEntityFsmCtx(
    TAF_SPM_FSM_CTX_STRU               *pstCurrFsmCtx
);

VOS_VOID  TAF_SPM_InitMainFsm( VOS_VOID );

VOS_VOID  TAF_SPM_InitEntityFsm( VOS_VOID );

VOS_VOID TAF_SPM_FSM_InitEntityFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);

VOS_VOID TAF_SPM_FSM_InitMainFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);

VOS_VOID TAF_SPM_FSM_QuitCurrEntityFsm(VOS_VOID);

VOS_VOID  TAF_SPM_InitMainCtrlInfo(
    TAF_SPM_MAIN_CTRL_INFO_STRU        *pstMainCtrl
);

VOS_VOID  TAF_SPM_InitServiceCtrlCfgInfo(
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfg
);

VOS_VOID  TAF_SPM_InitFsmCtx_Main(VOS_VOID);

VOS_VOID  TAF_SPM_InitFsmCtx_ServiceCtrl(VOS_VOID);

TAF_SPM_CONTEXT_STRU* TAF_SPM_GetSpmCtxAddr( VOS_VOID );

TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetCurrEntityFsmEntryMsgAddr(VOS_VOID);

VOS_VOID TAF_SPM_SaveCurrEntityFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_GetClientId(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT32 TAF_SPM_GetClientIdWithStkMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT8 TAF_SPM_GetCcMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCcMsgQueueFull(VOS_VOID);

VOS_UINT8 TAF_SPM_GetSmsMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSmsMsgQueueFull(VOS_VOID);

VOS_UINT8 TAF_SPM_GetSsMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSsMsgQueueFull(VOS_VOID);
TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU *TAF_SPM_GetBufferMsgQueueAddr(VOS_VOID);
VOS_VOID TAF_SPM_InitBufferCcMsgQueue(
    TAF_SPM_MSG_CC_QUEUE_STRU          *pstCcMsgQueue
);
VOS_VOID TAF_SPM_InitBufferSmsMsgQueue(
    TAF_SPM_MSG_SMS_QUEUE_STRU              *pstSmsMsgQueue
);
VOS_VOID TAF_SPM_InitBufferSsMsgQueue(
    TAF_SPM_MSG_SS_QUEUE_STRU              *pstSsMsgQueue
);


TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(
    VOS_UINT8                           ucIndex
);

TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(
    VOS_UINT8                           ucIndex
);

TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_ClearMessagesInSmsQueue(VOS_VOID);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInCcQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSsQueue(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 TAF_SPM_PutMessageToCcQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_PutMessageToSmsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_PutMessageToSsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SetCcMsgQueueNum(
    VOS_UINT8                           ucCacheMsgNum
);

VOS_VOID TAF_SPM_InitServiceReqBufferMsgQueue(VOS_VOID);

#if (FEATURE_IMS == FEATURE_ON)
/* ɾ��IMSע��״̬���Ƶ�SDC�� */

VOS_VOID TAF_SPM_SetImsSmsSupportedOnImsServer(
    VOS_UINT8                           ucImsSmsSupported
);
VOS_UINT8 TAF_SPM_GetImsSmsSupportedOnImsServer(VOS_VOID);


VOS_VOID TAF_SPM_InitDomainSelCtx(TAF_SPM_DOMAIN_SEL_CTX_STRU *pstDomainSelMsgQueue);

VOS_UINT8 TAF_SPM_GetImsSmsSendingFlg(VOS_VOID);

VOS_VOID TAF_SPM_SetImsSmsSendingFlg(VOS_UINT8 ucImsSmsSendingFlg);

TAF_SPM_SERVICE_STATUS_ENUM_UINT8 TAF_SPM_GetLastPsServiceStatus(VOS_VOID);

VOS_VOID TAF_SPM_SetLastPsServiceStatus(TAF_SPM_SERVICE_STATUS_ENUM_UINT8 enCurrPsStatus);

TAF_SPM_REDIAL_MSG_CTX_STRU *TAF_SPM_GetRedialMsgQueueAddr(VOS_VOID);

VOS_VOID TAF_SPM_InitCallRedialBuffer(
    TAF_SPM_CC_REDIAL_QUEUE_STRU       *pstCallRedialQueue
);

VOS_UINT8 TAF_SPM_GetNumberOfCallRedialBuffer(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCallRedialBufferEmpty(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCallRedialBufferFull(VOS_VOID);

VOS_VOID TAF_SPM_SetNumberOfCallRedialBuffer(VOS_UINT8 ucCacheMsgNum);

VOS_UINT32 TAF_SPM_PutMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_FreeSpecificedIndexCallRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_InitSmsRedialBuffer(
    TAF_SPM_SMS_REDIAL_QUEUE_STRU      *pstSmsRedialQueue
);

VOS_UINT8 TAF_SPM_GetNumberOfSmsRedialBuffer(VOS_VOID);

VOS_VOID TAF_SPM_SetNumberOfSmsRedialBuffer(VOS_UINT8 ucCacheMsgNum);

VOS_UINT8 TAF_SPM_IsSmsRedialBufferEmpty(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSmsRedialBufferFull(VOS_VOID);

VOS_UINT32 TAF_SPM_PutMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(VOS_UINT8 ucIndex);

TAF_SPM_CALL_ECONF_INFO_STRU* TAF_SPM_GetCallEconfInfoAddr(VOS_VOID);

VOS_VOID TAF_SPM_InitEconfInfo(VOS_VOID);

VOS_UINT32 TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg(VOS_VOID);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID  TAF_SPM_SetEcallHangUpImsFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_SPM_GetEcallHangUpImsFlag(VOS_VOID);
#endif
#endif

TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU* TAF_SPM_GetBufferServiceReqProtectTimerInfo(VOS_VOID);
VOS_UINT32   TAF_Spm_GetBufferCcProtectTimerLen(VOS_VOID);
VOS_UINT32   TAF_SPM_GetBufferSmsProtectTimerLen(VOS_VOID);
VOS_UINT32   TAF_SPM_GetBufferSsProtectTimerLen(VOS_VOID);

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

#endif /* end of TafSpmCtx.h */

