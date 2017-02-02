/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaFsmSysCfg.h
  �� �� ��   : ����
  ��    ��   : l00301449
  ��������   : 2015��4��9��
  ����޸�   :
  ��������   : TafMmaFsmSysCfg.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_MMA_FSM_SYS_CFG_H__
#define __TAF_MMA_FSM_SYS_CFG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafMmaCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_ONE_RAT_NUM            (1)

#define TAF_MMA_TWO_RAT_NUM            (2)

#define TAF_MMA_THREE_RAT_NUM          (3)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
    VOS_UINT8                           ucDetachOperation;
    VOS_UINT8                           ucAttachOperation;
    VOS_UINT8                           ucSysCfgOperation;
    VOS_UINT8                           ucReserved;
}TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

enum TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM
{
    TAF_MMA_GUL_RAT_SUBMODE_G,                      /* G RAT */
    TAF_MMA_GUL_RAT_SUBMODE_U,                      /* U RAT */
    TAF_MMA_GUL_RAT_SUBMODE_L,                      /* L RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GU,                     /* GU RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GL,                     /* GL RAT */
    TAF_MMA_GUL_RAT_SUBMODE_UL,                     /* UL RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GUL,                    /* GUL RAT */

    TAF_MMA_GUL_RAT_SUBMODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8;
enum TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM
{
    TAF_MMA_CL_RAT_SUBMODE_1X,                     /* 1X RAT */
    TAF_MMA_CL_RAT_SUBMODE_HRPD,                   /* HRPD RAT */
    TAF_MMA_CL_RAT_SUBMODE_L,                      /* L RAT */
    TAF_MMA_CL_RAT_SUBMODE_C,                      /* 1X&HRPD RAT */
    TAF_MMA_CL_RAT_SUBMODE_1XL,                    /* 1X&L RAT */
    TAF_MMA_CL_RAT_SUBMODE_HRPDL,                  /* HRPD&L_RAT */
    TAF_MMA_CL_RAT_SUBMODE_CL,                     /* C&L_RAT */

    TAF_MMA_CL_RAT_SUBMODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8;
enum TAF_MMA_RAT_MODE_TYPE_ENUM
{
    TAF_MMA_RAT_MODE_GUL_TO_GUL,
    TAF_MMA_RAT_MODE_GUL_TO_CL,
    TAF_MMA_RAT_MODE_CL_TO_GUL,
    TAF_MMA_RAT_MODE_CL_TO_CL,

    TAF_MMA_RAT_MODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8;


enum TAF_MMA_RAT_SET_TYPE_ENUM
{
    TAF_MMA_RAT_SET_L_ONLY,         /* RAT������L */
    TAF_MMA_RAT_SET_GUL,            /* RAT���ٰ���G��U */
    TAF_MMA_RAT_SET_CL,             /* RAT���ٰ���1X��HRPD */

    TAF_MMA_RAT_SET_BUTT
};
typedef VOS_UINT8 TAF_MMA_RAT_SET_TYPE_ENUM_UINT8;

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAttachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvAutoAttachSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ReportRslt_SysCfg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enAttachRslt,
    VOS_UINT16                          usPhoneError
);


VOS_UINT32 TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_MMA_DETACH_TYPE_ENUM_UINT8 TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

TAF_MMA_ATTACH_TYPE_ENUM_UINT8 TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT32  TAF_MMA_GetCurrFsmEntryMsgId_SysCfg(VOS_VOID);

TAF_CS_SERVICE_ENUM_UINT32  TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT8 TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT8 TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_VOID TAF_MMA_NotifyCsServiceChange_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_VOID TAF_MMA_GetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
);


VOS_VOID TAF_MMA_ProcInterSysCfgCnfFail_SysCfg(VOS_VOID);

VOS_VOID TAF_MMA_ProcSysCfgOper_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
);

VOS_VOID TAF_MMA_GetAttachOperType_SysCfg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
);
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetDetachOperType_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enDetachDomain
);

VOS_VOID TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus,
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                    *penAttachRslt,
    VOS_UINT16                                             *pusPhoneError
);

VOS_VOID TAF_MMA_WritePrioAccessModeToNvim(VOS_VOID);

VOS_VOID TAF_MMA_UpdatePrioAccessMode(
    TAF_MMA_SYS_CFG_PARA_STRU                              *pstCurrSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSysCfg
);

VOS_UINT32 TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU           *pstCurSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstOldSyscfg
);

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

#endif /* end of TafMmaFsmSysCfg.h */

