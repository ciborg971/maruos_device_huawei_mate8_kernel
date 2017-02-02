/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmBsr.c
Author          :   y00307564
Version         :
Date            :   2015-04-02
Description     :   Contains all definitions of all states in better system
                    reselection FSM in MSCC module
History         :
    1) Date :   2015-04-02
       Author:  y00307564
       Modification: Create

    2) Date :   2015-04-11
       Author:  x00314862
       Modification: Create
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMsccFsmBsr.h"
#include "NasMntn.h"
#include "NasMsccCtx.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccFsmBsrTbl.h"
#include "NasMsccSndHsd.h"
#include "NasMsccSndMmc.h"
#include "NasMsccSndInternalMsg.h"
#include "MsccMmcInterface.h"
#include "NasMsccProcNvim.h"
#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"
#include "NasComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_BSR_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
Function Name   :   NAS_MSCC_BSR_CommonProcess
Description     :   Common process for whether LTE or HRPD will be searched for
Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_BSR_CommonProcess(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        NAS_MSCC_SndHsdBgSearchReq(VOS_RATMODE_LTE);

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_BG_SEARCH_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF,
                            TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF_LEN);
    }
    else
    {
        NAS_MSCC_SndMmcBgSearchReq(VOS_RATMODE_HRPD);

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_BG_SEARCH_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF,
                            TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF_LEN);
    }

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiBsrTimer_BSR_Init
Description     :   This function judge whether LTE or HRPD will be searched for
Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_BSR_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_BSR_CommonProcess(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiRetryTimerExpired_BSR_Init
Description     :   This function judge whether LTE or HRPD will be searched for
Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiRetryTimerExpired_BSR_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_BSR_CommonProcess(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdBgSearchCnf_BSR_WaitHsdBgSearchCnf
Description     :   This function implement the process when receive HSD_MSCC_BG_SEARCH_CNF_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdBgSearchCnf_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_BG_SEARCH_CNF_STRU                            *pstHsdMsccBgSearchCnf;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF);

    pstHsdMsccBgSearchCnf = (HSD_MSCC_BG_SEARCH_CNF_STRU *)pstMsg;

    if ((HSD_MSCC_HRPD_BSR_RSLT_FAIL      == pstHsdMsccBgSearchCnf->enRslt)
     || (HSD_MSCC_HRPD_BSR_RSLT_ENUM_BUTT == pstHsdMsccBgSearchCnf->enRslt))
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    if (HSD_MSCC_HRPD_BSR_RSLT_ABORT == pstHsdMsccBgSearchCnf->enRslt)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    if ((0 == pstHsdMsccBgSearchCnf->stPlmnList.ucHighPlmnNum)
     && (0 == pstHsdMsccBgSearchCnf->stPlmnList.ucLowPlmnNum))
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* query bg searched plmn list pri class type */
    NAS_MSCC_SndMmcPlmnPriClassQueryReq(&pstHsdMsccBgSearchCnf->stPlmnList);

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF, TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdBgSearchCnf
Description     :   This function implement the process when receive NAS_MSCC_ABORT_FSM_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF);

    /* store the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    /* stop BG search */
    NAS_MSCC_SndHsdStopBgSearchReq();

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF);

    /* start the protective timer */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdBgSearchCnfTimeExpired_BSR_WaitHsdBgSearchCnf
Description     :   This function implement the process when receive TiWaitHsdBgSearchCnfTimeExpired

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdBgSearchCnfTimeExpired_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdBgSearchCnfTimeExpired_BSR_WaitHsdBgSearchCnf ENTERED...");

    /* stop BG search */
    NAS_MSCC_SndHsdStopBgSearchReq();

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF);

    /* start the protective timer */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdStopBgSearchCnf_BSR_WaitHsdStopBgSearchCnf
Description     :   This function implement the process when receive HSD_MSCC_STOP_BG_SEARCH_CNF

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdStopBgSearchCnf_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the protective timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF);

    /* has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);
    }
    else
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdStopBgSearchCnf
Description     :   This function implement the process when receive MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* store the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdStopBgSearchCnfTimeExpired_BSR_WaitHsdStopBgSearchCnf
Description     :   This function implement the process when receive TimeOut event in state WaitHsdStopBgSearchCnf

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdStopBgSearchCnfTimeExpired_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdStopBgSearchCnfTimeExpired_BSR_WaitHsdStopBgSearchCnf ENTERED...");

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);
    }
    else
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPlmnPriClassQueryCnf_BSR_WaitMmcPlmnPriClassQueryCnf
Description     :   This function implement the process when receive ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnPriClassQueryCnf_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU                 *pstPlmnPriClassQryCnf;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enDestBsrSysPriClass;
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stTmpfPlmnList;
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstLtePrefPlmnList;

    pstPlmnPriClassQryCnf = (MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU *)pstMsg;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF);

    enDestBsrSysPriClass = NAS_MSCC_GetDestBsrSysPriClass_BSR();

    /* according to the pri class to select the required plmn list */
    PS_MEM_SET(&stTmpfPlmnList, 0x0, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));
    NAS_MSCC_GetPlmnListInPlmnPriClassListWithPriClass(&pstPlmnPriClassQryCnf->stPlmnPriClassList,
                                                       enDestBsrSysPriClass,
                                                       &stTmpfPlmnList);

    pstLtePrefPlmnList = NAS_MSCC_GetLtePrefPlmnListInfo_BSR();

    /* filter the plmn list according to the orignal sys mspl index,if the plmn is not
       in the mspl index,could not add the plmn to the dest lte prefered plmn list */
    NAS_MSCC_GetPlmnListAccordingtoSpecMsplIndex(NAS_MSCC_GetOrigSysMsplIndex_BSR(),
                                                 &stTmpfPlmnList,
                                                 pstLtePrefPlmnList);

    /* if there not exists any plmn with BG search result */
    if ((0 == pstLtePrefPlmnList->ucHighPlmnNum)
     && (0 == pstLtePrefPlmnList->ucLowPlmnNum))
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send ID_MSCC_HSD_POWER_SAVE_REQ */
    NAS_MSCC_SndHsdPowerSaveReq();

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_PREF_PLMN_QUERY_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPrefPlmnQueryCnf
Description     :   This function implement the process when receive MSCC_MSCC_ABORT_FSM_REQ_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF);

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPlmnPriClassQueryCnfTimeExpired_BSR_WaitMmcPlmnPriClassQueryCnf
Description     :   This function implement the process when receive timeout event

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnPriClassQueryCnfTimeExpired_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPlmnPriClassQueryCnfTimeExpired_BSR_WaitMmcPlmnPriClassQueryCnf ENTERED...");

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnf
Description     :   This function implement the process when receive HSD_MSCC_POWER_SAVE_CNF_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF);

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY,
                                 VOS_NULL_PTR,
                                 NAS_MSCC_GetLtePrefPlmnListInfo_BSR());

    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF);

    /* start the protective timer */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnf
Description     :   This function implement the process when receive Abort Msg

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* record the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdPowerSaveCnfTimeExpired_BSR_WaitHsdPowerSaveCnf
Description     :   This function implement the process when receive time out in state WaitHsdPowerSaveCnf

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfTimeExpired_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdPowerSaveCnfTimeExpired_BSR_WaitHsdPowerSaveCnf ENTERED...");

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPlmnSearchCnf_BSR_WaitMmcPlmnSearchCnf
Description     :   This function implement the process when receive MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSearchCnf_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstPlmnSelRlstInd = VOS_NULL_PTR;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);


    pstPlmnSelRlstInd = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE == pstPlmnSelRlstInd->enResult)
    {
        /* BG search successfully,so send the result as success to Main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_SUCCESS,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT == pstPlmnSelRlstInd->enResult)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MSCC_SndMmcPowerSaveReq();

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnf
Description     :   This function implement the process when receive MSCC_MSCC_ABORT_FSM_REQ_STRU
Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPlmnSearchCnfTimeExpired_BSR_WaitMmcPlmnSearchCnf
Description     :   This function implement the process when receive Timeout Msg in state WaitMmcPlmnSearchCnf
Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSearchCnfTimeExpired_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPlmnSearchCnfTimeExpired_BSR_WaitMmcPlmnSearchCnf ENTERED...");

    NAS_MSCC_SndMmcPowerSaveReq();

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveReAcqHrpd
Description     :   This function implement the process when receive MMC_MSCC_POWER_SAVE_CNF_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {

        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ */
    NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                             0,
                             VOS_NULL_PTR);

    /* Set the Camp On flag to FALSE */
    NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

    NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF_LEN);


    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPowerSaveReAcqHrpd
Description     :   This function implement the process when receive MSCC_MSCC_ABORT_FSM_REQ_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* record abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPowerSaveReAcqHrpdTimeExpired_BSR_WaitMmcPowerSaveReAcqHrpd
Description     :   This function implement the process when receive timeout Msg in state WaitMmcPowerSaveReAcqHrpd

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveReAcqHrpdTimeExpired_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveReAcqHrpdTimeExpired_BSR_WaitMmcPowerSaveReAcqHrpd ENTERED...");

    /* wait expired, send result as failure */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdAcquireCnfReAcqHrpd
Description     :   This function implement the process when receive HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU   *pstSysAcqCnf;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);

    pstSysAcqCnf = (HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstSysAcqCnf->enRslt)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    else if (NAS_MSCC_BSR_RESULT_ABORT == pstSysAcqCnf->enRslt)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    else
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdAcquireCnfReAcqHrpd
Description     :   This function implement the process when receive MSCC_MSCC_ABORT_FSM_REQ_STRU

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdAcqCnfReAcqHrpdTimeExpired_BSR_WaitHsdAcquireCnfReAcqHrpd
Description     :   This function implement the process when receive timeout msg when in state WaitHsdAcquireCnfReAcqHrpd

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-4-3
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdAcqCnfReAcqHrpdTimeExpired_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdAcquireCnfReAcqHrpdTimeExpired_BSR_WaitHsdAcquireCnfReAcqHrpd ENTERED...");

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcBgSearchCnf_BSR_WaitMmcBgSearchCnf
Description     :   The function receives the background search respon from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcBgSearchCnf_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_BG_SEARCH_CNF_STRU                            *pstBgSearchCnf    = VOS_NULL_PTR;
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF);

    pstBgSearchCnf         =  (MMC_MSCC_BG_SEARCH_CNF_STRU *)pstMsg;

    /* bg search cnf with fail, send message to L1 FSM with fail */
    if ((MSCC_MMC_BG_SRCH_RESULT_FAIL == pstBgSearchCnf->enRslt)
     || (MSCC_MMC_BG_SRCH_RESULT_BUTT == pstBgSearchCnf->enRslt))
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }
    else if (MSCC_MMC_BG_SRCH_RESULT_ABORT == pstBgSearchCnf->enRslt)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        if (0 == pstBgSearchCnf->ucHrpdSysNum)
        {
            NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                                  NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                                  NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

            /* Quit the Sub FSM */
            NAS_MSCC_QuitFsmL2();

            return VOS_TRUE;
        }

        enDestBsrSysType = NAS_MSCC_GetDestBsrSysType_BSR();

        /* send ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ */
        NAS_MSCC_SndHsdQryHrpdSysInfoReq(enDestBsrSysType, pstBgSearchCnf->ucHrpdSysNum, pstBgSearchCnf->astHrpdSysList);

        /* Switch state to NAS_MSCC_BSR_STA_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,
                            TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF_LEN);

        return VOS_TRUE;
    }
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcBgSearchCnf
Description     :   The function receives the Coverage Area Ind from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF);

    /* Set the Camp On flag to FALSE */
    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcBgSearchCnf_BSR_WaitMmcBgSearchCnf
Description     :   The function receives the abort message from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF);

    /* record the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    /* send MSCC_MMC_STOP_BG_SEARCH_HRPD_REQ */
    NAS_MSCC_SndMmcStopBgSearchReq();

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF);

    /* start the relative protective timer relative */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcBgSearchCnfExpired_BSR_WaitMmcBgSearchCnf
Description     :   The function receives the timer Expired message.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcBgSearchCnfExpired_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcBgSearchCnfExpired_BSR_WaitMmcBgSearchCnf ENTERED");

    /* send MSCC_MMC_STOP_BG_SEARCH_HRPD_REQ */
    NAS_MSCC_SndMmcStopBgSearchReq();

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF);

    /* start the relative protective timer relative */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcStopBgSearchCnf_BSR_WaitMmcStopBgSearchCnf
Description     :   The function receives the stop background search respon from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStopBgSearchCnf_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF);

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* if bg search timer out, send a bg search result as fail to main FSM,need start retry timer */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* if bg search timer out, send a bg search result as fail to main FSM, need not start retry timer */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcStopBgSearchCnf
Description     :   The function receives the Coverage Area Ind from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF);

    /* Set the Camp On flag to FALSE */
    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcStopBgSearchCnf
Description     :   The function receives abort message from mscc .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* record the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcStopBgSearchCnfExpired_BSR_WaitMmcStopBgSearchCnf
Description     :   The function receives the stop background search respon timer Expired .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcStopBgSearchCnfExpired_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcStopBgSearchCnfExpired_BSR_WaitMmcStopBgSearchCnf ENTERED");

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* if bg search timer out, send a bg search result as abort to main FSM,need start retry timer */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdQryHrpdSysInfoCnf_BSR_WaitHsdQryHrpdSysInfoCnf
Description     :   The function receives the qry prefer subnet respon from hsd .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdQryHrpdSysInfoCnf_BSR_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU                    *pstQryCnfMsg      = VOS_NULL_PTR;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enDestBsrSysPriClass;      /* 需要发起BSR的系统的pri class */
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                *pstHighPriSysInfo;

    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF);

    pstQryCnfMsg         = (HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU *)pstMsg;

    pstHighPriSysInfo    = NAS_MSCC_GetHrpdHighPrioSysInfo_BSR();
    enDestBsrSysPriClass = NAS_MSCC_GetDestBsrSysPriClass_BSR();

    NAS_MSCC_GetHighPriSysInfoInHrpdSysInfoListWithPriClass(pstQryCnfMsg->ucHrpdSysNum,
                                                            pstQryCnfMsg->astHrpdSysInfoList,
                                                            enDestBsrSysPriClass,
                                                            pstHighPriSysInfo);

    if (0 == pstHighPriSysInfo->ucFreqNum)
    {
        /* send a bg search result as fail to main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send MSCC_MMC_POWER_SAVE_REQ */
    NAS_MSCC_SndMmcPowerSaveReq();

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF);

    /* start the relative protective timer relative */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitHsdQryHrpdSysInfoCnf
Description     :   The function receives abort message .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF);

    /* send a bg search result as abort to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdQryHrpdSysInfoCnfExpired_WaitHsdQryHrpdSysInfoCnf
Description     :   The function receives the timer Expired message .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdQryHrpdSysInfoCnfExpired_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdQryHrpdSysInfoCnfExpired_WaitHsdQryHrpdSysInfoCnf ENTERED");

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveCnf
Description     :   The function receives the power save respon from MMC .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                *pstHighPriSysInfo = VOS_NULL_PTR;

    /* stop the prptectove timer relative */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* send a bg search result as abort to main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    pstHighPriSysInfo = NAS_MSCC_GetHrpdHighPrioSysInfo_BSR();

    /* send MSCC_HSD_SYSTEM_ACQUIRE_REQ */
    NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_HIGH_PRIORITY,
                             pstHighPriSysInfo->ucFreqNum,
                             (VOS_VOID*)pstHighPriSysInfo->astFreqInfo);

    /* Set the Camp On flag to FALSE */
    NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

    NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

    /* Switch state to NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF);

    /* start the relative protective timer relative */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcPowerSaveCnf
Description     :   The function receives the abort message .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* record the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_BSR_WaitMmcPowerSaveCnf
Description     :   The function receives the timer Expired message .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-03
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_BSR_WaitMmcPowerSaveCnf ENTERED");

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* if bg search timer out, send a bg search result as abort to main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdSystemAcquireCnf
Description     :   The function receives the system acquire cnf from hsd .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU   *pstSysAcqCnf;

    pstSysAcqCnf = (HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)pstMsg;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstSysAcqCnf->enRslt)          /* success */
    {

        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_SUCCESS,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }
    else if (NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED == pstSysAcqCnf->enRslt) /* abort */
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }
    else  /* failure/butt */
    {
        NAS_MSCC_SndHsdPowerSaveReq();

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                            TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN);

        return VOS_TRUE;
    }
}
/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdSystemAcquireCnfExpired_BSR_WaitHsdSystemAcquireCnf
Description     :   The function receives the time out .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSystemAcquireCnfExpired_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdSystemAcquireCnfExpired_BSR_WaitHsdSystemAcquireCnf ENTERED");

    NAS_MSCC_SndHsdPowerSaveReq();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                        TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdSystemAcquireCnf
Description     :   The function receives the abort msg .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF);

    /* send a bg search result as abort to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnfReAcqLte
Description     :   The function receives the power save cnf from hsd .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF);

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* send a bg search result as abort to main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send ID_MSCC_MMC_PLMN_SEARCH_REQ */
    NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                 VOS_NULL_PTR,
                                 VOS_NULL_PTR);

    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

    /* change state */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                        TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnfReAcqLte
Description     :   The function receives the abort msg from mscc .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* record the abort flag */
    NAS_MSCC_SetAbortFlag_BSR(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_BSR_WaitHsdPowerSaveCnfReAcqLte
Description     :   The function receives the time out msg .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_BSR_WaitHsdPowerSaveCnfReAcqLte ENTERED");

    /* if this proces has been aborted */
    if (VOS_TRUE == NAS_MSCC_GetAbortFlag_BSR())
    {
        /* if bg search timer out, send a bg search result as abort to main FSM */
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* send a bg search result as fail to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcPlmnSeachCnf_BSR_WaitMmcPlmnSearchCnfReAcqLte
Description     :   The function receives the plmn serach cnf from mmc .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSeachCnf_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstPlmnSelRlstInd = VOS_NULL_PTR;

    pstPlmnSelRlstInd = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);

    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE == pstPlmnSelRlstInd->enResult)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }
    else if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT == pstPlmnSelRlstInd->enResult)
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }
    else
    {
        NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                              NAS_MSCC_BSR_NEED_ACQ_SYS,
                              NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnfReAcqLte
Description     :   The function receives the abort msg .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF);

    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_ABORT,
                          NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiWaitMmcPlmnSeachCnfExpired_BSR_WaitMmcPlmnSearchCnfReAcqLte
Description     :   The function receives the time out msg .

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.

Outout parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-04-07
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSeachCnfExpired_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPlmnSeachCnfExpired_BSR_WaitMmcPlmnSearchCnfReAcqLte ENTERED");

    /* send a bg search result as abort to main FSM */
    NAS_MSCC_SndBsrResult(NAS_MSCC_BSR_RESULT_FAILURE,
                          NAS_MSCC_BSR_NEED_ACQ_SYS,
                          NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

