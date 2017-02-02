/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmSysAcq.h
Author          :   m00312079
Version         :
Date            :   2015-04-03
Description     :   NasMsccFsmSysAcq.c Header file
Function list   :
History         :   creat
    1) Date :
       Author:
       Modification:
******************************************************************************/
#ifndef __NAS_MSCC_FSM_SYS_ACQ_H__
#define __NAS_MSCC_FSM_SYS_ACQ_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasMsccPifInterface.h"
#include  "NasMsccSndMmc.h"
#include  "NasMsccCtx.h"
#include  "NasMsccTimerMgmt.h"
#include  "NasMsccFsmSysAcqTbl.h"
#include  "NasMsccSndXsd.h"
#include  "NasMsccSndHsd.h"
#include  "NasMsccSndInternalMsg.h"
#include  "NasMsccSysAcqStrategy.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdSysAcqCnf_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdSysSyncInd_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSysAcqCnfExpired_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPlmnSrchCnf_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSrchCnfExpired_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcAcqCnf_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvXsd1xSystemServiceInfoInd_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiInitLocInfoIndExpired_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MSCC_QuitFsmSysAcq(
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt
);

NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32 NAS_MSCC_GetCLSysAcqScene_SysAcq(VOS_VOID);

NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU* NAS_MSCC_GetCLSysAcqSysList_SysAcq(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedReAcqLte_SysAcq(VOS_VOID);
VOS_VOID NAS_MSCC_SndMmcPowerSaveReq_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsdPowerSaveReq_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcPlmnSearchReq_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsdSysAcqReq_SysAcq(VOS_VOID);


VOS_VOID NAS_MSCC_SrchNetwork_SysAcq(
    VOS_RATMODE_ENUM_UINT32             ulRatMode
);

VOS_VOID NAS_MSCC_SrchInitLoc_SysAcq(
    VOS_RATMODE_ENUM_UINT32             ulRatMode
);

VOS_UINT32 NAS_MSCC_SrchNetworkByLteInitLocInfo_SysAcq(
     NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU                *pstLteInitLocSta
);

VOS_UINT32 NAS_MSCC_SrchNetworkBy1xInitLocInfo_SysAcq(
    NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU                  *pst1xInitLocSta
);

VOS_UINT32 NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_Proc1xInitSysAcqSucc_SysAcq(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysInfoInd
);

VOS_VOID NAS_MSCC_Proc1xInitSysAcqFail_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_ProcLteInitSysAcqSucc_SysAcq(
    MMC_MSCC_ACQ_CNF_STRU              *pstAcqCnf
);

VOS_VOID NAS_MSCC_ProcLteInitSysAcqFail_SysAcq(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedUse1xInitAcqLocInfo_SysAcq(VOS_VOID);
VOS_UINT32 NAS_MSCC_IsNeedUseLteInitAcqLocInfo_SysAcq(VOS_VOID);

#endif

#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif
#endif


