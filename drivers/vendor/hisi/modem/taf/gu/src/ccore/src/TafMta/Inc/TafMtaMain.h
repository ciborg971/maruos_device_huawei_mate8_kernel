

#ifndef __TAFMTAMAIN_H__
#define __TAFMTAMAIN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtMtaInterface.h"
#include "MtaRrcInterface.h"
#include "MtaPhyInterface.h"
#include "TafAppMma.h"
#include "TafMtaCtx.h"

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
typedef VOS_VOID (*MTA_MSG_PROC_FUNC)(VOS_VOID* pMsg);


typedef struct
{
    VOS_UINT32                          ulMsgType;                              /* MTA������ϢID */
    MTA_MSG_PROC_FUNC                   pProcMsgFunc;
}MTA_MSG_PROC_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID TAF_MTA_InitCtx(TAF_MTA_CONTEXT_STRU *pstMtaCtx);
extern VOS_UINT32 TAF_MTA_InitPid(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 TAF_MTA_InitTask( VOS_VOID );
extern VOS_VOID TAF_MTA_ProcMsg (struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvAtMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvGasMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvGphyMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvTimerMsg(VOS_VOID *pstMsg);
extern VOS_VOID TAF_MTA_RcvWcomMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvWphyMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvTcMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvNasMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_SndAtMsg(
           AT_APPCTRL_STRU                    *pAppCtrl,
           VOS_UINT32                          ulMsgId,
           VOS_UINT32                          ulLen,
           VOS_UINT8                          *pData);
extern VOS_UINT32 TAF_MTA_SearchMsgProcTab(
           VOS_UINT32                          ulMsgCnt,
           VOS_VOID                           *pstMsg,
           const MTA_MSG_PROC_STRU            *pstMsgProcTab);


extern  VOS_VOID TAF_MTA_RcvWrrMsg(struct MsgCB *pstMsg);

extern  VOS_VOID TAF_MTA_RcvApmMsg(struct MsgCB *pstMsg);

/* Added by zwx247453 for Refclkfreq, 2015-06-17, begin */
VOS_VOID TAF_MTA_RcvRttAgentMsg(struct MsgCB *pstMsg);
/* Added by zwx247453 for Refclkfreq, 2015-06-17, end */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
extern VOS_VOID TAF_MTA_RcvMtcMsg(struct MsgCB *pstMsg);
#endif



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
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


