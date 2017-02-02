


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccFsmSwitchOn.h"
#include "NasComm.h"
#include "NasMsccMlplMsplParse.h"
#include "NasMsccProcUsim.h"
#include "NasMsccMlplMsplApi.h"
#include "NVIM_Interface.h"
#include "NasMsccProcNvim.h"
#include "NasMsccComFunc.h"
#include "NasMsccMntn.h"
#include "NasMsccSndMma.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_SWITCH_ON_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimStatus_SwitchOn()
{

    MMA_MSCC_START_REQ_STRU        *pstStartReq = VOS_NULL_PTR;

    pstStartReq   = (MMA_MSCC_START_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    return pstStartReq->enCsimStatus;
}


NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimStatus_SwitchOn()
{

    MMA_MSCC_START_REQ_STRU        *pstStartReq = VOS_NULL_PTR;

    pstStartReq   = (MMA_MSCC_START_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    return pstStartReq->enUsimStatus;
}


NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrio_SwitchOn(VOS_VOID)
{

    MMA_MSCC_START_REQ_STRU        *pstStartReq = VOS_NULL_PTR;

    pstStartReq   = (MMA_MSCC_START_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    return &(pstStartReq->stRatPrio);
}



VOS_VOID NAS_MSCC_SndStartReq_SwitchOn(
    VOS_UINT32                          ulReceivePid
)
{
    MMA_MSCC_START_REQ_STRU                                *pstStartReq       = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio        = VOS_NULL_PTR;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
#endif

    switch (ulReceivePid)
    {
        case WUEPS_PID_MMC:
        {
            /* Get the Start from Entry message */
            pstStartReq   = (MMA_MSCC_START_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

            /* Send the Switch on indication to MMC */
            NAS_MSCC_SndMmcStartReq(pstStartReq);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF);

            /* Start the protection timer */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_START_CNF, TI_NAS_MSCC_WAIT_MMC_START_CNF_LEN);
        }
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
        {
            /* Send the Switch on indication to IMSA */
            NAS_MSCC_SndImsaStartReq(MSCC_IMSA_START_TYPE_POWER_ON);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF, TI_NAS_MSCC_WAIT_IMSA_START_CNF_LEN);
        }
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_XSD:
        {
            /* Get the Csim status from entry message */
            enCsimStatus = NAS_MSCC_GetCsimStatus_SwitchOn();

            /* Get Platform Rat capabilites */
            pstRatPrio = NAS_MSCC_GetRatPrio_SwitchOn();

            /* Send the Switch on indication to XSD */
            NAS_MSCC_SndXsdStartReq(enCsimStatus, pstRatPrio);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_XSD_START_CNF, TI_NAS_MSCC_WAIT_XSD_START_CNF_LEN);
        }
            break;
        case UEPS_PID_HSD:
        {
            /* Get the Csim status from entry message */
            enCsimStatus = NAS_MSCC_GetCsimStatus_SwitchOn();

            /* Get the Usim status from entry message */
            enUsimStatus = NAS_MSCC_GetUsimStatus_SwitchOn();

            /* Get Platform Rat capabilites */
            pstRatPrio = NAS_MSCC_GetRatPrio_SwitchOn();

            /* Send the Switch on indication to HSD */
            NAS_MSCC_SndHsdStartReq(enCsimStatus, enUsimStatus, pstRatPrio);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_START_CNF, TI_NAS_MSCC_WAIT_HSD_START_CNF_LEN);
        }
            break;
#endif

        default:
            NAS_TRACE_HIGH("\n*NAS_MSCC_SndStartReq_SwitchOn():invalid ulReceivePid \n");
            break;
    }

}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_SndUsimmReadFileReq_SwitchOn(VOS_VOID)
{
#ifdef DMT
    /* DTM���ԣ����������ʱ���� */
    if (NAS_MSCC_CARD_READ_STUB_TYPE_MLPL_NO_REPLY != genCardReadStubTypeForDmt)
    {
        NAS_MSCC_ReadUsimmFile(USIMM_CDMA_APP, USIMM_TELE_EFMLPL_ID);
    }

    NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MLPL);

    if (NAS_MSCC_CARD_READ_STUB_TYPE_MSPL_NO_REPLY != genCardReadStubTypeForDmt)
    {
        NAS_MSCC_ReadUsimmFile(USIMM_CDMA_APP, USIMM_TELE_EFMSPL_ID);
    }

    NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MSPL);

    return;
#endif

    NAS_MSCC_ReadUsimmFile(USIMM_CDMA_APP, USIMM_TELE_EFMLPL_ID);
    NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MLPL);

    NAS_MSCC_ReadUsimmFile(USIMM_CDMA_APP, USIMM_TELE_EFMSPL_ID);
    NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MSPL);

}
#endif
VOS_UINT32 NAS_MSCC_RcvMmaStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;
    MMA_MSCC_START_REQ_STRU            *pstMsgStartReq;

    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstMsgStartReq = (MMA_MSCC_START_REQ_STRU*)pstMsg;

    /* save card status */
    NAS_MSCC_SaveCardStatus(pstMsgStartReq->enUsimStatus, pstMsgStartReq->enCsimStatus);

    /* save prio rat list */
    NAS_MSCC_SavePrioRatList(&pstMsgStartReq->stRatPrio);

    /* ����ICCID�Ƿ����ı�ı�ʶ */
    NAS_MSCC_SaveIsCardChangedFlg(pstMsgStartReq->ucIsCardChanged);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == pstMsgStartReq->enCsimStatus)
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == pstMsgStartReq->enUsimStatus))
    {
        /* Read files from card */
        NAS_MSCC_SndUsimmReadFileReq_SwitchOn();

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CARD_READ_CNF,
                            TI_NAS_MSCC_WAIT_CARD_READ_CNF_LEN);

        return VOS_TRUE;

    }
#endif

    if (VOS_TRUE == NAS_MSCC_IsModuleOrderValid_SwitchOn())
    {
        /* Get the next Module ID*/
        ulRslt = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the start request to Next module */
            NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
            return VOS_TRUE;
        }
    }

    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaStartReq_SwitchOn_Init():Invalid Module order");

    /* send the result to Main FSM */
    NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 NAS_MSCC_RcvImsaStartCnf_SwitchOn_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Stop the Protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF);

    NAS_MSCC_SndMmaImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_ON);

    /* Get the next module ID */
    ulRslt = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);

    if (VOS_TRUE == ulRslt)
    {
        /* send start request to next module */
        NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
        return VOS_TRUE;
    }

    /* send the result to Main FSM */
    NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_SUCCESS);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaStartCnfExpired_SwitchOn_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* warning��ӡ */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitImsaStartCnfExpired_SwitchOn_WaitImsaStartCnf:time expired!");

    NAS_MSCC_SndMmaImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

    /* Get next Module ID */
    ulRslt = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);

    if (VOS_TRUE == ulRslt)
    {
        /* send start request to next module */
        NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
        return VOS_TRUE;
    }

    NAS_MSCC_ProcTimerExpired_SwitchOn();

    return VOS_TRUE;
}
#endif
VOS_UINT32 NAS_MSCC_RcvMmcStartCnf_SwitchOn_WaitMmcStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstStartCnf                         = (MMC_MSCC_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("start result=%d", pstStartCnf->ulResult);

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_START_CNF);

    /* Check whether the switch on result is success or not
        1)If result is success get the next module and the start request to nest module
        2)If result is Success and MOdule array is empty then send success result
        3)If result is failure send failure result */
    if ( NAS_MSCC_PIF_START_RESULT_SUCC == pstStartCnf->ulResult )
    {
        /* Get the next module ID*/
        ulRslt      = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send start request to next module */
            NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
            return VOS_TRUE;
        }

        /* If the module array is empty send the result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_SUCCESS);
    }
    else
    {
        NAS_TRACE_HIGH("NAS_MSCC_RcvMmcStartCnf_SwitchOn_WaitMmcStartCnf:Result Failure!");

        /* If the result is failure send the failure result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcStartCnfExpired_SwitchOn_WaitMmcStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Error LOG */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitMmcStartCnfExpired_SwitchOn_WaitMmcStartCnf:time expired!");

    /* Process the Timer Expired message */
    NAS_MSCC_ProcTimerExpired_SwitchOn();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvXsdStartCnf_SwitchOn_WaitXsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstStartCnf                         = (XSD_MSCC_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("start result=%d", pstStartCnf->enRslt);

    /* Stop the protection Timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_XSD_START_CNF);

    /* Check whether the switch on result is success or not
        1)If result is success get the next module and the start request to nest module
        2)If result is Success and MOdule array is empty then send success result
        3)If result is failure send failure result */
    if ( XSD_MSCC_START_RESULT_SUCC == pstStartCnf->enRslt )
    {
        /* Get the next module ID*/
        ulRslt      = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send start request to next module */
            NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
            return VOS_TRUE;
        }

        /* If the module array is empty send the result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_SUCCESS);
    }
    else
    {
        NAS_TRACE_HIGH("NAS_MSCC_RcvXsdStartCnf_SwitchOn_WaitXsdStartCnf:Result Failure!");

        /* If the result is failure send the failure result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitXsdStartCnfExpired_SwitchOn_WaitXsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Print Error Log */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitXsdStartCnfExpired_SwitchOn_WaitXsdStartCnf:time expired!");

    /* Process the Timer expire message */
    NAS_MSCC_ProcTimerExpired_SwitchOn();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdStartCnf_SwitchOn_WaitHsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_START_CNF_STRU            *pstStartCnf             = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstStartCnf                         = (HSD_MSCC_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("start result=%d", pstStartCnf->enRslt);

    /* Stop the protection Timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_START_CNF);

    /* Check whether the switch on result is success or not
        1)If result is success get the next module and the start request to nest module
        2)If result is Success and MOdule array is empty then send success result
        3)If result is failure send failure result */
    if ( HSD_MSCC_START_RESULT_SUCC == pstStartCnf->enRslt )
    {
        /* Get the next module ID*/
        ulRslt      = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send start request to next module */
            NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
            return VOS_TRUE;
        }

        /* If the module array is empty send the result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_SUCCESS);
    }
    else
    {
        NAS_TRACE_HIGH("NAS_MSCC_RcvHsdStartCnf_SwitchOn_WaitHsdStartCnf:Result Failure!");

        /* If the result is failure send the failure result */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);
    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdStartCnfExpired_SwitchOn_WaitHsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Print ERROR LOG*/
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitHsdStartCnfExpired_SwitchOn_WaitHsdStartCnf:time expired!");

    /* Process the timer expired message */
    NAS_MSCC_ProcTimerExpired_SwitchOn();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg  = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId;
    VOS_UINT32                                              ulModuleId;
    VOS_UINT32                                              ulRslt;

#ifdef DMT
    /* DMT����: �������MLPL��MSPLʧ�ܣ���ʱ����ʱ���� */
    if (NAS_MSCC_CARD_READ_STUB_TYPE_MLPL_MSPL_NO_REPLY == genCardReadStubTypeForDmt)
    {
        NAS_MSCC_SendCardReadTimerExpireMsgForDmt();

        return VOS_TRUE;
    }
#endif

    pstUsimmReadCnfMsg = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(pstUsimmReadCnfMsg->stCmdResult.enApptype,
                                              pstUsimmReadCnfMsg->stFilePath.ulPathLen,
                                              pstUsimmReadCnfMsg->stFilePath.acPath, &enEfId))
    {

        NAS_TRACE_HIGH("NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf :Error In USIMM_ChangePathToDefFileID!");

        return VOS_TRUE;
    }

    NAS_MSCC_RcvUsimmReadFileCnf(pstUsimmReadCnfMsg, enEfId);

    NAS_MSCC_ClearWaitCardReadCnfFlg_SwitchOn(enEfId);

    if (NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_NULL == NAS_MSCC_GetWaitCardReadCnfFlag_SwitchOn())
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CARD_READ_CNF);

        NAS_MSCC_ProcMlplMsplReadRslt_SwitchOn();

        if (VOS_TRUE == NAS_MSCC_IsModuleOrderValid_SwitchOn())
        {
            /* Get the next Module ID*/
            ulRslt = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);
            if (VOS_TRUE == ulRslt)
            {
                /* Send the start request to Next module */
                NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
                return VOS_TRUE;
            }
        }

        NAS_TRACE_HIGH("NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf :Invalid Module order");

        /* send the result to Main FSM */
        NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);

        /* Quit the SubFSM */
        NAS_MSCC_QuitFsmL2();
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitCardReadTimerExpire_SwitchOn_WaitCardReadCnf(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    VOS_UINT32                                              ulModuleId;
    VOS_UINT32                                              ulRslt;

    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitCardReadTimerExpire_SwitchOn_WaitCardReadCnf: timer out");

    NAS_MSCC_ResetWaitCardReadCnfFlg_SwitchOn();

    NAS_MSCC_ProcMlplMsplReadRslt_SwitchOn();

    if (VOS_TRUE == NAS_MSCC_IsModuleOrderValid_SwitchOn())
    {
        /* Get the next Module ID*/
        ulRslt = NAS_MSCC_GetNextModuleId_SwitchOn(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the start request to Next module */
            NAS_MSCC_SndStartReq_SwitchOn(ulModuleId);
            return VOS_TRUE;
        }
    }

    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaStartReq_SwitchOn_Init():Invalid Module order");

    /* send the result to Main FSM */
    NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}
#endif


VOS_VOID NAS_MSCC_ProcTimerExpired_SwitchOn(VOS_VOID)
{

    /* Send the internal message */
    NAS_MSCC_SndSwitchOnRslt(NAS_MSCC_SWITCH_ON_RESULT_FAILURE);

    /* Quit the sub FSM*/
    NAS_MSCC_QuitFsmL2();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_ProcMlplMsplReadRslt_SwitchOn(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return;
    }

    NAS_MSCC_ReadAndParseMlplMsplNvim();

    if (VOS_TRUE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return;
    }

    NAS_MSCC_ParseDefaultMlplMspl();
}


VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlg_SwitchOn(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
)
{
    switch (enEfId)
    {
        case USIMM_TELE_EFMLPL_ID:
            NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
                                                NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MLPL);
            break;

        case USIMM_TELE_EFMSPL_ID:
            NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
                                                NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MSPL);
            break;

        default:
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_ClearWaitCardReadCnfFlg_SwitchOn:WARNING: File Id Abnormal");
            break;
    }

    return;
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

