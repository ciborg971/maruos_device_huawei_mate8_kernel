


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccCtx.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccSndMma.h"
#include "PsLogdef.h"
#include "NasMsccSndXsd.h"
#include "NasMsccSndHsd.h"
#include "NasMsccSndMmc.h"
#include "NasComm.h"
#include "NasMsccComFunc.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccProcNvim.h"
#include "NasMsccFsmSysCfg.h"

#include "NasMsccSndRrm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_MAIN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef DMT
    VOS_UINT32 g_ulDisableAutoSysAcq;
#endif
/*****************************************************************************
  3 ��������
*****************************************************************************/






VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ReadNvim();

    /* Start the Switch ON FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SWITCH_ON);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvMsccStartCnf_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU                  *pstSwitchOnRslt;

    pstSwitchOnRslt                     = (NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    if (NAS_MSCC_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnRslt->enRslt)
    {
        /* Send Switch On Cnf with Success result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_SUCC);

        /* Set next state to Deactive */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* �����ϱ���ǰ����CL mode����GUL mode */
        NAS_MSCC_SndRrmRatCombModeInd();
        #endif
    }
    else
    {
        /* Send Switch On Cnf with Fail result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_FAIL);

        NAS_TRACE_HIGH("NAS_MSCC_RcvMsccStartCnf_Main_Null: Switch ON result Failed!");
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#ifdef DMT
    if (VOS_TRUE == g_ulDisableAutoSysAcq)
    {
        /* For ST testing purpose: Test sys cfg handling in DEACTIVE state */
        return VOS_TRUE;
    }
#endif

    NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(pstMsg);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Start the Power OFF FSM  */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvHsdSysAcqInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU                   *pstHsdSysAcqInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstHsdSysAcqInd                     = (HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU *)pstMsg;





    /* Added by m00312079 for CDMA Iteration 10 2015-4-7 begin */

    /* only failure situation should be dealt with, success situcation will be
        left for session negotiation */
    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC != pstHsdSysAcqInd->enRslt)
    {
        ucSimPsRegStatus = NAS_MSCC_GetSimPsRegStatus();

        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            VOS_FALSE,
                                            VOS_FALSE,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);
        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */


        if ((VOS_TRUE  == NAS_MSCC_IsNeedPerformCLSysAcq())
         && (VOS_TRUE  == ucSimPsRegStatus))
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST);

            return VOS_TRUE;
        }
    }
    /* Added by m00312079 for CDMA Iteration 10 2015-4-7 end */

    /* �����֧��LTE,��ΪHRPD�����Ĳ�������;֪ͨ����ʼ��ϵͳģʽΪDO */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
    }
    else
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                           MSCC_MMA_ACQ_SYS_TYPE_DO,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvInternalSysAcqReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);

    /* ����L2 System Acquire״̬�� */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcRegRejPlmnSeleInd_Main_Active
Description     :   process ID_MMC_MSCC_REG_REJ_PLMN_SELE_IND message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcRegRejPlmnSeleInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_REG_REJ_PLMN_SELE_IND     *pstRegRejPlmnSeleInd;

    pstRegRejPlmnSeleInd = (MMC_MSCC_REG_REJ_PLMN_SELE_IND *)pstMsg;

    /* ��������������ֱ���˳� */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        return VOS_TRUE;
    }

    /* ע�ᱻ�ܲ���Ҫ���������,MSCC����ֱ�ӹص�LTE����HRPD */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST);

        return VOS_TRUE;
    }

    /* LTE��ע�ᱻ�������������;��ȴ�MMC������ָʾ;������Ҫ����������HRPD */
    if (VOS_FALSE == pstRegRejPlmnSeleInd->ucPlmnSeleFlg)
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST);
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcBsrFailureRslt_Main_Active
Description     :   Process BSR failure result
Input parameters:   NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU: BSR FSM return result
Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-4-13
        Author  :   t00323010
        Modify content :Create for Iteration 10
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcBsrFailureRslt_Main_Active(
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf
)
{
    VOS_UINT8                           uc3gppActiveFlg;

    if (NAS_MSCC_BSR_NEED_ACQ_SYS == pstBsrSearchRsltCnf->enIsNeedAcqSys)
    {
        uc3gppActiveFlg = NAS_MSCC_Get3gppActiveFlg();

        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            /* BG�����л�LTEʱ���ע�ᱻ�ܿ���Ч,��Ҫͨ�����������е�HRPD��ȥ */
            if (VOS_TRUE == uc3gppActiveFlg)
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST);

                return;
            }

            /* LTE��PSע�ᱻ�ܿ���Ч����HRPD��,������HSD��ѡ����ʱ������������;���ﲻ������ */
            if ((VOS_TRUE  == NAS_MSCC_GetSimPsRegStatus())
             && (VOS_FALSE == uc3gppActiveFlg))
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST);

                return;
            }
        }
    }
    else
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
        {
            /* ��ȻĿǰBSRʧ�ܳ���������������Retry Timer��ʶ, ��Ȼ�ȱ�����if��֧ */
            if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
            {
                NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                    TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
            }
            else
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active
Description     :   process the internal BSR result message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf = VOS_NULL_PTR;

    pstBsrSearchRsltCnf = (NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU *)pstMsg;

    switch (pstBsrSearchRsltCnf->enRslt)
    {
        /* BSRפ���������ȼ���ʽ�ɹ� */
        case NAS_MSCC_BSR_RESULT_SUCCESS:

            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                NAS_MSCC_StartBsrTimer();
            }

            break;

        case NAS_MSCC_BSR_RESULT_FAILURE:

            NAS_MSCC_ProcBsrFailureRslt_Main_Active(pstBsrSearchRsltCnf);

            break;

        case NAS_MSCC_BSR_RESULT_ABORT:

            /* ��Ȼ��������Ҫ����BSR Retry Timer��ǣ��������������������BSR��ʱ��������������Retry��ʱ�� */
            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
                {
                    NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                        TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
                }
                else
                {
                    NAS_MSCC_StartBsrTimer();
                }
            }

            break;

        default:

            NAS_WARNING_LOG(UEPS_PID_MSCC, "BSR FSM return result is except");

            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucDataServiceOn1xFlg;

    ucSimPsRegStatus        = NAS_MSCC_GetSimPsRegStatus();
    ucDataServiceOn1xFlg    = NAS_MSCC_GetDataServiceSwitchTo1xFlg();

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus)
     && (VOS_TRUE == ucDataServiceOn1xFlg))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED);

        return VOS_TRUE;
    }
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active
Description     :   process period trying high prio network search timer expiry message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_ProcInterSysAcqSucc_Main(VOS_VOID)
{
    /* system acquire succ clear data service switch to 1x flag, in the next flow,will start available
       timer after CL system acquire both failed */
    NAS_MSCC_SetDataServiceSwitchTo1xFlg(VOS_FALSE);

    /* �ж��Ƿ���Ҫ������������BSR��ʱ�� */
    if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StartBsrTimer();
        }
        else
        {
            if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

    NAS_MSCC_ResetCurAvailableTimerStartCount_L1Main();

    if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC);
    }
    else
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC);
    }

    return;
}
VOS_VOID NAS_MSCC_ProcInterSysAcqFail_Main(VOS_VOID)
{
    NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                       MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                       MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);

    /* LTEע�ᱻ�ܿ���Ч,��������available timer,ֱ������HRPD */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

        return;
    }

    /* Ps domain switch to 1x, sys acq fail, need to start BSR Timer */
    if (VOS_TRUE == NAS_MSCC_GetDataServiceSwitchTo1xFlg())
    {
        NAS_MSCC_StartBsrTimer();
    }
    else
    {
        if (VOS_TRUE == NAS_MSCC_StartTimer(TI_NAS_MSCC_AVAILABLE_TIMER, NAS_MSCC_GetNextAvailableTimerLength_L1Main()))
        {
            NAS_MSCC_AddCurAvailableTimerStartCount_L1Main();
        }
    }

    /* if both 1x and hrpd ,lte no service,start scan timer */
    if (NAS_MSCC_SERVICE_STATUS_NO_SERVICE == NAS_MSCC_GetCurr1xServiceStatus())
    {
        /* we start the timer only in CL mode */
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        }
    }

    return;
}
VOS_UINT32 NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstSysAcqRslt = VOS_NULL_PTR;

    pstSysAcqRslt = (NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU *)pstMsg;

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqSucc_Main();

        return VOS_TRUE;
    }

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqFail_Main();
    }

    if ( NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C == pstSysAcqRslt->enRslt )
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
    }
    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiSleepTimerExpired_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* here must be CL mode */
    NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main();

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_ProcRfAvailableInd_Main_Deactive()
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;

    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* �ػ�����NULL״̬��ֻ�н�SLEEPģʽʱ���Ż��DEACTIVE״̬ */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq();

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED);

        return;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}
VOS_UINT32 NAS_MSCC_RcvMmcMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvXsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq = VOS_NULL_PTR;

    pstSrvAcqReq = (MMA_MSCC_SRV_ACQ_REQ_STRU *)pstMsg;

    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* �ػ�����NULL״̬��ֻ�н�SLEEPģʽʱ���Ż��DEACTIVE״̬ */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

        NAS_MSCC_SndXsdSrvAcqReq(pstSrvAcqReq);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED);

        return VOS_TRUE;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive
Description     :   proc for ID_MMA_MSCC_CDMA_MO_CALL_START_NTF message
Input parameters:   ulEventType
                    pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER);

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */

VOS_UINT32 NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdSrvst;

    /* maybe here is the buffered scan timer expied message,should judge the service
       status, if one of the system is normal service, hould ignore this message */

    enHrpdSrvst = NAS_MSCC_GetCurrHrpdServiceStatus();

    if ((NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
     || (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enHrpdSrvst))
    {
        /* discard this message */
        return VOS_TRUE;
    }

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
    if (VOS_TRUE == NAS_MSCC_Get1xSysAcqMoCallFlag())
    {
        NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        return VOS_TRUE;
    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */

    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main(VOS_VOID)
{
    VOS_UINT8                           ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq();

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED);

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}
#endif


VOS_VOID NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU                       *pstMmaSysAcqReq = VOS_NULL_PTR;

    pstMmaSysAcqReq = (MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* Set the Current FSM state to Active */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

        return;
    }

    /* ���洦��CLģʽ�µ�ϵͳ�������� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq();

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON);

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* hrpd and lte could not both perform system acquire,here return */
        return;
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* Send HSD system acquire request if CDMA EVDO is supported */
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_POWER_UP,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }
#endif

    return;
}


VOS_VOID NAS_MSCC_PerformSystemAcquireUponSysCfg_Main(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          uc3gppNormalSrvFlg;
    VOS_UINT32                          ucHrpdNormalSrvFlg;
    VOS_UINT8                           ucSimPsRegStatus;
#endif

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
         if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
         {
             NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                          VOS_NULL_PTR,
                                          VOS_NULL_PTR);

             NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

             NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
         }

         return;
    }

    /* ���洦��CLģʽ�µ�ϵͳ�������� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    if (VOS_TRUE == NAS_MSCC_IsNeedStartScanTimerUponSyscfg())
    {
        NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
        {
            NAS_MSCC_SndXsdSysAcqReq();

            NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
        }
    }

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    uc3gppNormalSrvFlg  = NAS_MSCC_Is3gppNormalService();
    ucHrpdNormalSrvFlg  = NAS_MSCC_IsHrpdNormalService();

    /* ���3GPP��HRPD�Ѿ���normal service��פ����������ȼ�,����Ҫ����;ֱ�ӷ��� */
    if ((VOS_TRUE  == NAS_MSCC_IsCampOnHighestPrioritySystem())
     && ((VOS_TRUE == uc3gppNormalSrvFlg)
      || (VOS_TRUE == ucHrpdNormalSrvFlg)))
    {
        return;
    }

    /* ����CL����������PS����Ч,��CL�������� */
    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET);

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
        {
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSD��DEACTIVE״̬�յ�RF AVAILABLE IND��˵��֮ǰHSD����RF��Դ
       ����Ԥ�������жϣ������ǰģ����֧�֣��򲻽�״̬�����������Ͻ��ú���
       һ����CLģʽ��
       ������CLģʽ����������:(1)SYSCFG���ò�֧��CL;(2)SYSCFG֧��CL����������CL������ */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)HRPD��֧�ֺ�SYSCFG�����÷�֧;
           (2)��֧��CLģʽ������1X��HRPDʧ�ܣ�TI_NAS_MSCC_SCAN_TIMER��ʱ����ʱ��HSD����DEACTVE״̬
           (3)֧��CLģʽ��������HRPD+LTE�������ģʽ */
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
        {
            /* Send HSD system acquire request if CDMA EVDO is supported */
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            /* Set the Camp On flag to FALSE */
            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        /* ͣAVAILABLE��ʱ�� */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* ��HRPD��Դ���õĳ������� */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActiveFlg;

    ucHrpdActiveFlg = NAS_MSCC_GetHrpdActiveFlg();

    /* MMC��DEACTIVE״̬�յ�RF AVAILABLE IND��˵��֮ǰMMC����RF��Դ
       ����Ԥ�������жϣ������ǰģ����֧�֣��򲻽�״̬�����������Ͻ��ú���
       һ����CLģʽ */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)LTE��֧�ֺ�SYSCFG�����÷�֧;
           (2)��֧��CLģʽ������1X��LTEʧ�ܣ�TI_NAS_MSCC_SCAN_TIMER��ʱ����ʱ��MMC����DEACTVE״̬
           (3)֧��CLģʽ��������HRPD+LTE�������ģʽ */
        if ( (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
          && (VOS_FALSE == ucHrpdActiveFlg) )
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    /* ���HRPD��ǰHRPDδ������Ļ�������HRPD���ģʽ���� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
    {
        /* ͣAVAILABLE��ʱ�� */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* ��lte��Դ���ó�ʱ������������CL  */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE);
    }

    return VOS_TRUE;
}


#endif
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectionRsltInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstMmcSysAcqCnf = VOS_NULL_PTR;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enMmaSysAcqRlst;

    pstMmcSysAcqCnf                     = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF == pstMmcSysAcqCnf->enResult)
    {
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            /* check the current mode(only CL mode) and find the prior system in mspl*/
            if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST);
            }


            return VOS_TRUE;
        }
    }
#endif

    enMmaSysAcqRlst = NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst(pstMmcSysAcqCnf->enResult);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE == pstMmcSysAcqCnf->enResult)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE      == pstMmcSysAcqCnf->enResult))
    {
        /* check the current mode(only CL mode) and find the prior system in mspl*/
        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST);

            return VOS_TRUE;
        }
    }
#endif

    /* GULģʽ����ԭ���߼�֪ͨMMA��������,ģʽΪ3GPP */
    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                           MSCC_MMA_ACQ_SYS_TYPE_3GPP,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                      MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                      MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;
}


MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_GetSystemAcquireFinalResult(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enAcqRslt
)
{

    if(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == enAcqRslt)
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE;
    }
    else
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE;
    }

}




VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Start the System config FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYSTEM_CONFIG);

    return VOS_TRUE;
}

/* ɾ���˺��� */

VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* set the user rat priority */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        /* Send the system acquire if Sleep timer is running */
        if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_SLEEP_TIMER))
        {
            /* �ڷ���ϵͳ�����ֹͣsleep timer��ʱ�� */
            NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

            NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

            /* Set the Current FSM state to Active */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);
        }

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* ǰ��CL��GUL֮���б��ʱ���ϱ� */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq  = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();


    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        /* ֹͣ��صĶ�ʱ�� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == NAS_MSCC_IsHrpdAndLteBothSupported())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);
        }

        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);
#endif
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* Note: firstly, set user rat priority. And then process system acquire. */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* ǰ��CL��GUL֮���б��ʱ���ϱ� */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}
VOS_VOID NAS_MSCC_ProcPowerOffResult_Main(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
)
{
    if (NAS_MSCC_POWEROFF_RSLT_POWER_OFF == enRslt)
    {
        /* Added by m00312079 for CDMA Iteration 10 2015-4-8 begin */
        NAS_MSCC_StopAllTimer();
        /* Added by m00312079 for CDMA Iteration 10 2015-4-8 end */

        /* Send the Power off result cnf to MMA */
        NAS_MSCC_SndMmaPowerOffRsltCnf();

        /* Reset the Context For MSCC */
        NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_POWEROFF);

        /* set next state to NULL */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_NULL);

        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* stop all timer */
    NAS_MSCC_StopAllTimer();

    NAS_MSCC_ResetCurAvailableTimerStartCount_L1Main();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SLEEP_TIMER, NAS_MSCC_GetSleepTimerLength());
#endif

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


