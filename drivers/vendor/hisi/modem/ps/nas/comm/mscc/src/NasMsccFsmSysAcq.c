/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmSysAcq.c
Author          :   m00312079
Version         :
Date            :   2015-04-03
Description     :   Contains all definitions of all Functions used in System Acquire FSM
History         :   Creat
    1) Date :
       Author:
       Modification:
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccFsmSysAcq.h"
#include "NasComm.h"
#include "NasMsccProcNvim.h"
#include "NasMsccCtx.h"
#include "NasMsccComFunc.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_SYS_ACQ_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccSysAcqReq_SysAcq_Init
Description     :   This function deals with the init of the System Acquire FSM

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SYS_ACQ_STRU                             *pstSystemAcqReq;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;
    NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_UINT32           enBuildSysAcqListScene;

    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstSystemAcqReq = (NAS_MSCC_MSCC_SYS_ACQ_STRU*)pstMsg;

    pstSysListInfo  = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    NAS_MSCC_ConvertSysAcqSceneToBuildSysAcqListScene(pstSystemAcqReq->enSysAcqScene,
                                                     &enBuildSysAcqListScene);

    NAS_MSCC_BuildSysAcqList(enBuildSysAcqListScene,
                             VOS_NULL_PTR,
                             VOS_NULL_PTR,
                             pstSysListInfo);

    PS_MEM_SET(&stNextAcqSysInfo,
               0x00,
               sizeof(NAS_MSCC_SYS_ACQ_SYS_INFO_STRU));

    /* send next acquire rat mode for normal aquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_TRUE == ulRslt)
    {
        /* search network or power save */
        NAS_MSCC_SrchNetwork_SysAcq(stNextAcqSysInfo.ulRatMode);

        return VOS_TRUE;
    }

    /* if get the next Acq sys Info fail, it should process intial search to get loaction */
    ulRslt = NAS_MSCC_GetNextInitialAcquireSysInAcqSysList(pstSysListInfo,
                                                          &stNextAcqSysInfo);

    if (VOS_FALSE == ulRslt)
    {
        /* abnormal case, should quit fsm with fail result */
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    NAS_MSCC_SrchInitLoc_SysAcq(stNextAcqSysInfo.ulRatMode);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdSysAcqCnf_SysAcq_WaitHsdSysAcqCnf
Description     :   MSCC receives System Acquire confirmation from HSD,
                    this function is called to process the Comfirm

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdSysAcqCnf_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU                       *pstSysAcqCnf;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;

    pstSysAcqCnf                     = (HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)pstMsg;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);

    pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstSysAcqCnf->enRslt)
    {
        /* refresh the system acquire result */
        NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_HRPD,
                                                      NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_REGISTERED,
                                                      pstSysListInfo);
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS);

        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED == pstSysAcqCnf->enRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    /* refresh the system acquire result */
    NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_HRPD,
                                                  NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,
                                                  pstSysListInfo);

    /* system acquire failed, so power save hrpd */
    NAS_MSCC_SndHsdPowerSaveReq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdSysAcqCnf
Description     :   MSCC receives Abort Fsm req from HSD,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);
    NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdSysSyncInd_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;

    if (VOS_TRUE == NAS_MSCC_IsNeedReAcqLte_SysAcq())
    {
        pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();
        pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();

        pstSysAcqFsmCtx->ucNeedReAcqLteFlg = VOS_FALSE;
        NAS_MSCC_ResetAcqRatStatusInNormalAcqSysList(pstSysListInfo);

        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);
        NAS_MSCC_SndHsdPowerSaveReq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdSysAcqCnfExpired_SysAcq_WaitHsdSysAcqCnf
Description     :   This function is used to handle timer expire message,
                    when MSCC is waiting for Hsd system Acquire confirm message from HSD

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSysAcqCnfExpired_SysAcq_WaitHsdSysAcqCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;

    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdSysAcqCnfExpired_SysAcq_WaitHsdSysAcqCnf: timer out");

    pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    /* refresh the system acquire result */
    NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_HRPD,
                                                  NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,
                                                  pstSysListInfo);

    NAS_MSCC_SndHsdPowerSaveReq_SysAcq();
    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdPowerSaveCnf_SysAcq_WaitHsdPowerSaveCnf
Description     :   MSCC receives power save cnf from HSD,
                    this function is called to process the confirm

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF);

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_SysAcq())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

        return VOS_TRUE;
    }

    pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    /* send next acquire rat mode for normal aquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_FALSE == ulRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdPowerSaveCnf
Description     :   MSCC receives Abort Fsm req from HSD,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_MSCC_SetAbortFlag_SysAcq(VOS_TRUE);
     return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysAcq_WaitHsdPowerSaveCnf
Description     :   This function is used to handle timer expire message,
                    when MSCC is waiting for Hsd power save confirm message from HSD

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysAcq_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysAcq_WaitHsdPowerSaveCnf: timer out");

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_SysAcq())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

        return VOS_TRUE;
    }

    NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcPlmnSrchCnf_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstMmcPlmnSeleRlstInd;
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;

    pstMmcPlmnSeleRlstInd                     = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);

    pstSysAcqFsmCtx  = NAS_MSCC_GetSysAcqFsmCtxAddr();

    pstSysListInfo   = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE == pstMmcPlmnSeleRlstInd->enResult)
    {
        /* refresh the system acquire result */
        NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_LTE,
                                                      NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_REGISTERED,
                                                      pstSysListInfo);

        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS);

        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT == pstMmcPlmnSeleRlstInd->enResult)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C == pstMmcPlmnSeleRlstInd->enResult)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C);

        return VOS_TRUE;
    }
    if (VOS_TRUE == pstMmcPlmnSeleRlstInd->ucLteCoverageFlg)
    {
        /* lte is not the normal service and the coverage is ok, so set the ReAcqLteFlg to false */
        pstSysAcqFsmCtx->ucNeedReAcqLteFlg = VOS_FALSE;
    }

    /* refresh the system acquire result */
    NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_LTE,
                                                  NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,
                                                  pstSysListInfo);

    /* Plmn search cnf failed, so power save the lte */
    NAS_MSCC_SndMmcPowerSaveReq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPlmnSrchCnf
Description     :   MSCC receives Abort Fsm req from HSD,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);
    NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPlmnSrchCnfExpired_SysAcq_WaitMmcPlmnSrchCnf
Description     :   This function is used to handle timer expire message,
                    when MSCC is waiting for Mmc Plmn search confirm message from MMC

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSrchCnfExpired_SysAcq_WaitMmcPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;

    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPlmnSrchCnfExpired_SysAcq_WaitMmcPlmnSrchCnf: timer out");

    pstSysListInfo  = NAS_MSCC_GetCLSysAcqSysList_SysAcq();
    /* refresh the system acquire result */
    NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(VOS_RATMODE_LTE,
                                                  NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,
                                                  pstSysListInfo);

    NAS_MSCC_SndMmcPowerSaveReq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPowerSaveCnf_SysAcq_WaitMmcPowerSaveCnf
Description     :   MSCC receives power save cnf from mmc,
                    this function is called to process the confirm

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_SysAcq())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

        return VOS_TRUE;
    }

    /* 如果LTE注册被拒卡无效,这里直接退出状态机,状态机外面触发搜HRPD */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    pstSysListInfo = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    /* send next acquire rat mode for normal aquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_FALSE == ulRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

        return VOS_TRUE;
    }

    NAS_MSCC_SndHsdSysAcqReq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPowerSaveCnf
Description     :   MSCC receives Abort Fsm req from HSD,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_MSCC_SetAbortFlag_SysAcq(VOS_TRUE);
     return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysAcq_WaitMmcPowerSaveCnf
Description     :   This function is used to handle timer expire message,
                    when MSCC is waiting for Mmc power save confirm message from MMC

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysAcq_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysAcq_WaitMmcPowerSaveCnf: timer out");

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_SysAcq())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

        return VOS_TRUE;
    }

    NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcAcqCnf_SysAcq_WaitInitlocInfoInd
Description     :   MSCC receives acq cnf from mmc,
                    this function is called to process the confirm

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcqCnf_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ACQ_CNF_STRU              *pstAcqCnf;

    pstAcqCnf = (MMC_MSCC_ACQ_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_ACQ_RESULT_SUCCESS == pstAcqCnf->enAcqRslt)
    {
        NAS_MSCC_ProcLteInitSysAcqSucc_SysAcq(pstAcqCnf);
    }
    else
    {
        NAS_MSCC_ProcLteInitSysAcqFail_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitInitlocInfoInd
Description     :   MSCC receives Abort Fsm req from HSD,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);
    NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvXsd1xSystemServiceInfoInd_SysAcq_WaitInitlocInfoInd
Description     :   MSCC receives 1x system service ind from xsd,
                    this function is called to process the request

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsd1xSystemServiceInfoInd_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pstSysInfoInd;

    pstSysInfoInd = (XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU *)pstMsg;

    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE  == pstSysInfoInd->stSysSrvInfo.enServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == pstSysInfoInd->stSysSrvInfo.enServiceStatus))
    {
        NAS_MSCC_Proc1xInitSysAcqSucc_SysAcq(pstSysInfoInd);
    }
    else
    {
        NAS_MSCC_Proc1xInitSysAcqFail_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiInitLocInfoIndExpired_SysAcq_WaitInitlocInfoInd
Description     :   This function is used to handle timer expire message,
                    when MSCC is waiting for Mmc acquire confirm message from MMC

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiInitLocInfoIndExpired_SysAcq_WaitInitlocInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           uc1xInitAcqFinishFlg;
    VOS_UINT8                           ucLteInitAcqFinishFlg;

    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiInitLocInfoIndExpired_SysAcq_WaitInitlocInfoInd: timer out");

    uc1xInitAcqFinishFlg  = NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq();
    ucLteInitAcqFinishFlg = NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq();

    /* both 1x and lte initial acquire are not finished,we consider lte inital acquire failed
       and search hrpd first */
    if ((VOS_FALSE == uc1xInitAcqFinishFlg)
     && (VOS_FALSE == ucLteInitAcqFinishFlg))
    {
        NAS_MSCC_ProcLteInitSysAcqFail_SysAcq();

        return VOS_TRUE;
    }

    /* if 1x initial acquire not finished,we consider 1x inital acquire failed */
    if (VOS_FALSE == uc1xInitAcqFinishFlg)
    {
        NAS_MSCC_Proc1xInitSysAcqFail_SysAcq();

        return VOS_TRUE;
    }

    /* if lte initial acquire not finished,we consider lte inital acquire failed */
    if (VOS_FALSE == ucLteInitAcqFinishFlg)
    {
        NAS_MSCC_ProcLteInitSysAcqFail_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_QuitFsmSysAcq
Description     :   This function send internal message and quit the sysAcq fsm

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_QuitFsmSysAcq(
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt
)
{
    /* send the result to Main FSM */
    NAS_MSCC_SndInternalSysAcqRsltCnf(enRslt);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCLSysAcqScene_SysAcq
Description     :   The function is used to get SysAcq Scene in FSM
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32 NAS_MSCC_GetCLSysAcqScene_SysAcq(VOS_VOID)
{

    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enCurrSysAcqScene;
    NAS_MSCC_MSG_STRU                                      *pstEntryMsg;
    NAS_MSCC_MSCC_SYS_ACQ_STRU                             *pstSysAcq;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    pstSysAcq             = (NAS_MSCC_MSCC_SYS_ACQ_STRU *)pstEntryMsg->aucMsgBuffer;
    enCurrSysAcqScene     = pstSysAcq->enSysAcqScene;

    return enCurrSysAcqScene;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCLSysAcqScene_SysAcq
Description     :   The function is used to get SysAcq Scene in FSM
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU* NAS_MSCC_GetCLSysAcqSysList_SysAcq(VOS_VOID)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;

    pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();

    return &(pstSysAcqFsmCtx->stSysAcqListInfo);
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedReAcqLte_SysAcq
Description     :   The function is to judge wether reAcq LTE when hrpd is synced or not in FSM
Input parameters:   VOID
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-08-21
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_IsNeedReAcqLte_SysAcq(VOS_VOID)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;
    VOS_UINT8                                               ucNeedReAcqLteFlg;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enCurrSysAcqScene;

    enCurrSysAcqScene   = NAS_MSCC_GetCLSysAcqScene_SysAcq();

    /* 定制需求:开机搜网时，当LTE优先于HPRD并且NV2014中的ucReAcqLteOnHrpdSyncIndFlag为TRUE时，
        如果第一次搜索LTE失败，接下来在搜索HRPD时如果HPRD有覆盖，则先power save HRPD，再给LTE搜索一次的机会*/
    if (NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON == enCurrSysAcqScene)
    {
        pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();
        pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();
        ucNeedReAcqLteFlg   = pstSysAcqFsmCtx->ucNeedReAcqLteFlg;

        if ((VOS_RATMODE_LTE == pstSysListInfo->astNormalAcqSysList[0].ulRatMode)
         && (VOS_TRUE == ucNeedReAcqLteFlg))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndMmcPowerSaveReq_SysAcq
Description     :   The function is send mmc power save req in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_VOID NAS_MSCC_SndMmcPowerSaveReq_SysAcq(VOS_VOID)
{
    /*power save LTE*/
    NAS_MSCC_SndMmcPowerSaveReq();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSACQ_STA_WAIT_MMC_POWER_SAVE_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN);

}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdPowerSaveReq_SysAcq
Description     :   The function is send Hsd power save req in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_VOID NAS_MSCC_SndHsdPowerSaveReq_SysAcq(VOS_VOID)
{
    /*power save hrpd*/
    NAS_MSCC_SndHsdPowerSaveReq();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSACQ_STA_WAIT_HSD_POWER_SAVE_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN);
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndMmcPlmnSearchReq_SysAcq
Description     :   The function is send MmcPlmnSearchReq in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_VOID NAS_MSCC_SndMmcPlmnSearchReq_SysAcq(VOS_VOID)
{
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32 enAcqReason;

    if (NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON == NAS_MSCC_GetCLSysAcqScene_SysAcq())
    {
        enAcqReason = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;
    }
    else
    {
        enAcqReason = NAS_MSCC_PIF_ACQ_REASON_OTHER;
    }

    NAS_MSCC_SndMmcPlmnSearchReq(enAcqReason,
                                 VOS_NULL_PTR,
                                 VOS_NULL_PTR);

    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSACQ_STA_WAIT_MMC_PLMN_SEARCH_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF_LEN);
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdSysAcqReq_SysAcq
Description     :   The function is send HsdSysAcqReq in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_VOID NAS_MSCC_SndHsdSysAcqReq_SysAcq(VOS_VOID)
{
    MSCC_HSD_ACQUIRE_REASON_ENUM_UINT32 enAcqReason;

    if (NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON == NAS_MSCC_GetCLSysAcqScene_SysAcq())
    {
        enAcqReason = MSCC_HSD_ACQUIRE_REASON_POWER_UP;
    }
    else
    {
        enAcqReason = MSCC_HSD_ACQUIRE_REASON_OTHER;
    }

    /*acquire Hrpd*/
    NAS_MSCC_SndHsdSysAcqReq(enAcqReason,
                             0,
                             VOS_NULL_PTR);

    /* Set the Camp On flag to FALSE */
    NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

    NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF_LEN);
}



VOS_VOID NAS_MSCC_SrchNetwork_SysAcq(
    VOS_RATMODE_ENUM_UINT32             ulRatMode
)
{
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();

    switch (ulRatMode)
    {
        case VOS_RATMODE_LTE :

            /* LTE如果正常驻留,此时不立即搜索LTE,成功退出状态机即可; */
            if (VOS_TRUE == NAS_MSCC_Is3gppNormalService())
            {
                NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS);

                return;
            }

            if (VOS_TRUE == ucHrpdActFlg)
            {
                NAS_MSCC_SndHsdPowerSaveReq_SysAcq();
            }
            else
            {
                NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();
            }

            break;

        case VOS_RATMODE_HRPD :

            /* HRPD如果正常驻留,此时不立即搜索HRPD,成功退出状态机即可; */
            if (VOS_TRUE == NAS_MSCC_IsHrpdNormalService())
            {
                NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS);

                return;
            }

            if (VOS_TRUE == uc3gppActFlg)
            {
                NAS_MSCC_SndMmcPowerSaveReq_SysAcq();
            }
            else
            {
                NAS_MSCC_SndHsdSysAcqReq_SysAcq();
            }

            break;

        default:

            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SrchNetwork_SysAcq: unknown ulRatMode!");
            NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
            break;
    }

    return;
}



VOS_VOID NAS_MSCC_SrchInitLoc_SysAcq(
    VOS_RATMODE_ENUM_UINT32             ulRatMode
)
{
    MMA_MSCC_ACQ_REQ_STRU                                   stAcqReq;;

    /* LTE如果正常驻留,此时不立即搜索LTE,成功退出状态机即可; */
    if (VOS_TRUE == NAS_MSCC_Is3gppNormalService())
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS);

        return;
    }

    if (VOS_RATMODE_LTE == ulRatMode)
    {
        /* 初始搜索LTE */
        stAcqReq.enAcqReason             = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;
        stAcqReq.ucNotRegAfterAcqSucc    = VOS_TRUE;
        NAS_MSCC_SndMmcAcqReq(&stAcqReq);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND,
                            TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND_LEN);
    }
    else
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
    }
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SrchNetworkByLteLocInfo_SysAcq
Description     :   The function is search initial location in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_SrchNetworkByLteInitLocInfo_SysAcq(
     NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU                *pstLteInitLocSta
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;

    pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    NAS_MSCC_BuildSysAcqList(NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_SUCC,
                             VOS_NULL_PTR,
                             &pstLteInitLocSta->stLteLocInfo,
                             pstSysListInfo);

    /* send next acquire rat mode for normal acquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_TRUE ==  ulRslt)
    {
        if (VOS_RATMODE_HRPD == stNextAcqSysInfo.ulRatMode)
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

            NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_HRPD_PRIO);

            /* Plmn search cnf failed, so power save the lte */
            NAS_MSCC_SndMmcPowerSaveReq_SysAcq();
            return VOS_TRUE;
        }

        if (VOS_RATMODE_LTE == stNextAcqSysInfo.ulRatMode)
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

            NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_LTE_PRIO);

            NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();

            return VOS_TRUE;
        }
    }

    NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL);

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SrchNetworkBy1xLocInfo_SysAcq
Description     :   The function is search initial location in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_SrchNetworkBy1xInitLocInfo_SysAcq(
    NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU                  *pst1xInitLocSta
)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;

    pstSysListInfo = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    NAS_MSCC_BuildSysAcqList(NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_SUCC,
                             &pst1xInitLocSta->st1xLocInfo,
                             VOS_NULL_PTR,
                             pstSysListInfo);

    /* send next acquire rat mode for normal aquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_TRUE == ulRslt)
    {
        if (VOS_RATMODE_HRPD == stNextAcqSysInfo.ulRatMode)
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

            NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_HRPD_PRIO);

            /* Plmn search cnf failed, so power save the lte */
            NAS_MSCC_SndMmcPowerSaveReq_SysAcq();

            return VOS_TRUE;
        }

        if (VOS_RATMODE_LTE == stNextAcqSysInfo.ulRatMode)
        {
            NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_LTE_PRIO);

            /* use 1x initial acq location info to determine lte is more prefered,so here
               if lte system acqurie is not finsished,we should first wait lte initial acquire finish */
            if (VOS_TRUE == NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq())
            {
                NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

                /* lte initial acquire locaiton info is invalid we srch hrpd,else we srch lte */
                if (NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID == NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq())
                {
                    /* use default system acquire list */
                    return NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq();
                }
                else
                {
                    NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();
                }
            }

            return VOS_TRUE;
        }
    }

    NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL);

    return VOS_FALSE;
}
/*****************************************************************************
Function Name   :   NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq
Description     :   The function is search initial location in sysAcq Fsm
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq(VOS_VOID)
{
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysListInfo;
    VOS_UINT32                                              ulRslt;
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                          stNextAcqSysInfo;

    pstSysListInfo      = NAS_MSCC_GetCLSysAcqSysList_SysAcq();

    NAS_MSCC_BuildSysAcqList(NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_FAIL,
                             VOS_NULL_PTR,
                             VOS_NULL_PTR,
                             pstSysListInfo);

    /* send next acquire rat mode for normal aquire req */
    ulRslt = NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(pstSysListInfo,
                                                         &stNextAcqSysInfo);

    if (VOS_TRUE == ulRslt)
    {
        if (VOS_RATMODE_HRPD == stNextAcqSysInfo.ulRatMode)
        {
            /* Plmn search cnf failed, so power save the lte */
            NAS_MSCC_SndMmcPowerSaveReq_SysAcq();

            return VOS_TRUE;
        }

        if (VOS_RATMODE_LTE == stNextAcqSysInfo.ulRatMode)
        {
            NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




VOS_VOID NAS_MSCC_Proc1xInitSysAcqSucc_SysAcq(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysInfoInd
)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU      *pstSysAcqFsmCtx;
    VOS_UINT32                          ulRslt;

    pstSysAcqFsmCtx = NAS_MSCC_GetSysAcqFsmCtxAddr();

    pstSysAcqFsmCtx->st1xInitLocSta.ucAcqFinishFlg    = VOS_TRUE;

    NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL);

    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.ulMcc = pst1xSysInfoInd->stSysSrvInfo.stServiceInfo.ulMcc;
    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.ulMnc = pst1xSysInfoInd->stSysSrvInfo.stServiceInfo.usMnc;
    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.usSid = pst1xSysInfoInd->stSysSrvInfo.usSid;
    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.usNid = pst1xSysInfoInd->stSysSrvInfo.usNid;

    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.en1xPrioClass =
                    NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(pst1xSysInfoInd->stSysSrvInfo.en1xPriClass);

    pstSysAcqFsmCtx->st1xInitLocSta.st1xLocInfo.enAIPrioClass=
                    NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(pst1xSysInfoInd->stSysSrvInfo.enAIPriClass);
    /* judge if we can use 1x initial loc info,if not,return */
    if (VOS_FALSE == NAS_MSCC_IsNeedUse1xInitAcqLocInfo_SysAcq())
    {
        return;
    }

    ulRslt = NAS_MSCC_SrchNetworkBy1xInitLocInfo_SysAcq(&pstSysAcqFsmCtx->st1xInitLocSta);

    if (VOS_TRUE == ulRslt)
    {
        return;
    }

    /* if lte initial location info is not ready,wait */
    if (VOS_FALSE == NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq())
    {
        return;
    }

    /* judge if we can use lte initial loc info */
    if (VOS_TRUE == NAS_MSCC_IsNeedUseLteInitAcqLocInfo_SysAcq())
    {
        ulRslt = NAS_MSCC_SrchNetworkByLteInitLocInfo_SysAcq(&pstSysAcqFsmCtx->stLteInitLocSta);

        if (VOS_TRUE == ulRslt)
        {
            return;
        }
    }

    /* use default search list */
    ulRslt = NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

    if (VOS_FALSE == ulRslt)
    {
       NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
    }

    return;
}




VOS_VOID NAS_MSCC_Proc1xInitSysAcqFail_SysAcq(VOS_VOID)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU      *pstSysAcqFsmCtx;
    VOS_UINT32                          ulRslt;

    pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();

    pstSysAcqFsmCtx->st1xInitLocSta.ucAcqFinishFlg = VOS_TRUE;

    NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID);

    /* if lte initial location info is not ready,wait */
    if (VOS_FALSE == NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq())
    {
        return;
    }

    /* judge if we can use lte initial loc info */
    if (VOS_TRUE == NAS_MSCC_IsNeedUseLteInitAcqLocInfo_SysAcq())
    {
        ulRslt = NAS_MSCC_SrchNetworkByLteInitLocInfo_SysAcq(&pstSysAcqFsmCtx->stLteInitLocSta);

        if (VOS_TRUE == ulRslt)
        {
            return;
        }
    }

    /* use default search list */
    ulRslt = NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

    if (VOS_FALSE == ulRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
    }

    return;
}

VOS_VOID NAS_MSCC_ProcLteInitSysAcqSucc_SysAcq(
    MMC_MSCC_ACQ_CNF_STRU              *pstAcqCnf
)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU      *pstSysAcqFsmCtx;
    VOS_UINT32                          ulRslt;
    NAS_MSCC_3GPP_SYS_INFO_STRU        *pst3gppSysInfo = VOS_NULL_PTR;

    pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

    pst3gppSysInfo->enPrioClass = NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(pstAcqCnf->enPrioClass);

    pstSysAcqFsmCtx = NAS_MSCC_GetSysAcqFsmCtxAddr();

    pstSysAcqFsmCtx->stLteInitLocSta.ucAcqFinishFlg = VOS_TRUE;

    NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL);

    pstSysAcqFsmCtx->stLteInitLocSta.stLteLocInfo.ulMcc = pstAcqCnf->stPlmnId.ulMcc;
    pstSysAcqFsmCtx->stLteInitLocSta.stLteLocInfo.ulMnc = pstAcqCnf->stPlmnId.ulMnc;
    pstSysAcqFsmCtx->stLteInitLocSta.stLteLocInfo.enPrioClass = pst3gppSysInfo->enPrioClass;

    /* here first judge 1x location info is used and is already lte prefered,
       then we can directly srch lte */
    if (NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_LTE_PRIO == NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq())
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

        NAS_MSCC_SndMmcPlmnSearchReq_SysAcq();

        return;
    }

    /* judge if we can use lte initial acquire location info or not,if not,return */
    if (VOS_FALSE == NAS_MSCC_IsNeedUseLteInitAcqLocInfo_SysAcq())
    {
        return;
    }

    ulRslt = NAS_MSCC_SrchNetworkByLteInitLocInfo_SysAcq(&pstSysAcqFsmCtx->stLteInitLocSta);

    if (VOS_TRUE == ulRslt)
    {
        return;
    }

    /* if 1x initial location info is not ready,wait */
    if (VOS_FALSE == NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq())
    {
        return;
    }

    /* judge if we can use 1x initial acquire location info or not */
    if (VOS_TRUE == NAS_MSCC_IsNeedUse1xInitAcqLocInfo_SysAcq())
    {
        ulRslt = NAS_MSCC_SrchNetworkBy1xInitLocInfo_SysAcq(&pstSysAcqFsmCtx->st1xInitLocSta);

        if (VOS_TRUE == ulRslt)
        {
            return;
        }
    }

    /* use default search list */
    ulRslt = NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

    if (VOS_FALSE == ulRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
    }

    return;
}




VOS_VOID NAS_MSCC_ProcLteInitSysAcqFail_SysAcq(VOS_VOID)
{
    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU      *pstSysAcqFsmCtx;
    VOS_UINT32                          ulRslt;

    pstSysAcqFsmCtx = NAS_MSCC_GetSysAcqFsmCtxAddr();

    pstSysAcqFsmCtx->stLteInitLocSta.ucAcqFinishFlg   = VOS_TRUE;

    NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID);

    /* lte initial acquire failed and we can directly power save lte and search hrpd */
    ulRslt = NAS_MSCC_SrchNetworkByNonInitLocInfo_SysAcq();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND);

    if (VOS_FALSE == ulRslt)
    {
        NAS_MSCC_QuitFsmSysAcq(NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE);
    }

    return;
}

VOS_UINT32 NAS_MSCC_IsNeedUse1xInitAcqLocInfo_SysAcq(VOS_VOID)
{
    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enLteInitLocInfoStatus;

    ucIs1xLocInfoPrefThanLte = NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.ucIs1xLocInfoPrefThanLte;

    /* 1x preferred and 1x location info is not used and valid */
    if ((NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL == NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq())
     && (VOS_TRUE                                         == ucIs1xLocInfoPrefThanLte))
    {
        return VOS_TRUE;
    }

    /* lte preferred and lte location info is invalid or valid but search mlpl failed */
    enLteInitLocInfoStatus = NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq();

    if ((VOS_FALSE                                           == ucIs1xLocInfoPrefThanLte)
     && ((NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID          == enLteInitLocInfoStatus)
      || (NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL == enLteInitLocInfoStatus)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}





VOS_UINT32 NAS_MSCC_IsNeedUseLteInitAcqLocInfo_SysAcq(VOS_VOID)
{
    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            en1xInitLocInfoStatus;

    ucIs1xLocInfoPrefThanLte = NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.ucIs1xLocInfoPrefThanLte;

    /* first judge 1x support or not, if not support,directly use lte loc info */
    if (VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        return VOS_TRUE;
    }

    /* Lte preferred and Lte location info is not used and valid */
    if ((NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL == NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq())
     && (VOS_FALSE                                        == ucIs1xLocInfoPrefThanLte))
    {
        return VOS_TRUE;
    }

    /* 1x preferred and 1x location info is invalid or valid but search mlpl failed */
    en1xInitLocInfoStatus = NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq();

    if ((VOS_TRUE                                            == ucIs1xLocInfoPrefThanLte)
     && ((NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID          == en1xInitLocInfoStatus)
      || (NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL == en1xInitLocInfoStatus)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


