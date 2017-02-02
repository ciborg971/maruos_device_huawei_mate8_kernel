

#ifndef _TAF_MMA_MAIN_
#define _TAF_MMA_MAIN_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "TafMmaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MMA_BATTERY_FULL                100
#define MMA_RSCP_MIN                    (-145)
#define MMA_ECNO_MIN                    (-32)
#define MMA_TI_UNUSED                   0


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
VOS_UINT32 TAF_MMA_BuildEventType(
    struct MsgCB                       *pstMsg
);
VOS_VOID  TAF_MMA_InitTask( VOS_VOID );

VOS_UINT32 TAF_MMA_InitPid(
    enum VOS_INIT_PHASE_DEFINE          ip
);

VOS_UINT32 TAF_MMA_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

VOS_VOID  TAF_MMA_InitCtx(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_MMA_CONTEXT_STRU                *pstMmaCtx
);
VOS_UINT32  TAF_MMA_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  TAF_MMA_MsgProc(
    struct MsgCB                       *pstMsg
);

VOS_VOID  TAF_MMA_MsgProcEntry(
    struct MsgCB                       *pstMsg
);


VOS_VOID  TAF_MMA_RegFsm( VOS_VOID );

VOS_VOID TAF_MMA_ReadNvim(VOS_VOID);
VOS_UINT32  TAF_MMA_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ProcessBufferMsg( VOS_VOID );
VOS_VOID TAF_MMA_InitInternalTimer(VOS_VOID);
VOS_VOID  TAF_MMA_InitAllTimers(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_MMA_TIMER_CTX_STRU              *pstMsccTimerCtx
);

VOS_VOID  TAF_MMA_InitOperCtx(
    TAF_MMA_OPER_CTX_STRU               *pstMmaOperCtx
);
VOS_VOID TAF_MMA_InitOrigMeInfo( VOS_VOID );
VOS_VOID TAF_MMA_InitPhoneModeCtrlCtx(
    TAF_MMA_PHONE_MODE_CTRL_CTX_STRU   *pstCtrlCtx
);
VOS_VOID TAF_MMA_InitSyscfgInfo(VOS_VOID);
VOS_VOID TAF_MMA_InitStatusCtx(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType
);
VOS_VOID TAF_MMA_InitUsimInfo(VOS_VOID);
VOS_VOID TAF_MMA_InitTi(VOS_VOID);
VOS_VOID TAF_MMA_InitTimerId(VOS_VOID);
VOS_VOID TAF_MMA_InitSdcNetworkInfo(VOS_VOID);
VOS_VOID TAF_MMA_InitTimerLen(VOS_VOID);
VOS_VOID TAF_MMA_InitMePersonalisationStatus(VOS_VOID);
VOS_VOID TAF_MMA_InitMmaGlobalValue(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType
);
VOS_VOID TAF_MMA_InitNetworkSelectionMenuCtx(VOS_VOID);
VOS_VOID TAF_MMA_InitRatBalancingCtx(VOS_VOID);
VOS_VOID TAF_MMA_InitBandInfo(VOS_VOID);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
VOS_VOID TAF_MMA_InitAttachInfo(VOS_VOID);

VOS_VOID TAF_MMA_InitDsdsInfo(VOS_VOID);
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

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

#endif /* end of TafMmaMain.h */

