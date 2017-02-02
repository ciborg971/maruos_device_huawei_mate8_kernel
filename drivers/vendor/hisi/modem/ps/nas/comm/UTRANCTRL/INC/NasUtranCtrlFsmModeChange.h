
#ifndef _NAS_UTRANCTRL_FSM_MODE_CHANGE_H_
#define _NAS_UTRANCTRL_FSM_MODE_CHANGE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
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
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
);

VOS_VOID NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
);

NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  NAS_UTRANCTRL_GetMasterMode_ModeChange(VOS_VOID);

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

#endif /* end of NasUtranCtrlFsmModeChange.h */


