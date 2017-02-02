

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccSndMmc.h"
#include "NasMntn.h"
#include "NasMsccCtx.h"
#include "NasComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_MMC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_VOID NAS_MSCC_SndMmcImsVoiceCapNotify(
    VOS_UINT8                           ucImsVoiceAvail,
    VOS_UINT8                           ucIsExistPersistentBearer
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsVoiceCapNotify: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY;
    pstMsg->ucAvail                    = ucImsVoiceAvail;

    pstMsg->ucIsExistPersistentBearer  = ucIsExistPersistentBearer;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcSignalReportReq(
    MMA_MSCC_SIGN_REPORT_REQ_STRU      *pstSigReportReq
)
{
    MSCC_MMC_SIGN_REPORT_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_SIGN_REPORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSignalReportReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SIGN_REPORT_REQ;
    pstMsg->ucActionType               = pstSigReportReq->ucActionType;
    pstMsg->ucRrcMsgType               = pstSigReportReq->ucRrcMsgType;
    pstMsg->ucSignThreshold            = pstSigReportReq->ucSignThreshold;
    pstMsg->ucMinRptTimerInterval      = pstSigReportReq->ucMinRptTimerInterval;


    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;

}

VOS_VOID NAS_MSCC_SndMmcModeChangeReq(
    MMA_MSCC_MODE_CHANGE_REQ_STRU      *pstModeChangeReq
)
{
    MSCC_MMC_MODE_CHANGE_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_MODE_CHANGE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcModeChangeReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_MODE_CHANGE_REQ;
    pstMsg->enMsMode                   = pstModeChangeReq->enMsMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcAttachReq(
    MMA_MSCC_ATTACH_REQ_STRU           *pstAttachReq
)
{
    MSCC_MMC_ATTACH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_ATTACH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcAttachReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_ATTACH_REQ;
    pstMsg->ulOpID                     = pstAttachReq->ulOpID;
    pstMsg->enAttachType               = pstAttachReq->enAttachType;
    pstMsg->enEpsAttachReason          = pstAttachReq->enEpsAttachReason;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcDetachReq(
    MMA_MSCC_DETACH_REQ_STRU           *pstDetachReq
)
{
    MSCC_MMC_DETACH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_DETACH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcDetachReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_DETACH_REQ;
    pstMsg->ulOpID                     = pstDetachReq->ulOpID;
    pstMsg->enDetachType               = pstDetachReq->enDetachType;
    pstMsg->enDetachReason             = pstDetachReq->enDetachReason;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}



VOS_VOID NAS_MSCC_SndMmcPlmnListReq(VOS_VOID)
{
    MSCC_MMC_PLMN_LIST_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_PLMN_LIST_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnListReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_LIST_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcPlmnListAbortReq(VOS_VOID)
{
    MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnListAbortReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_LIST_ABORT_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcPlmnUserReselReq(
    MMA_MSCC_PLMN_USER_RESEL_REQ_STRU  *pstPlmnUserReselReq
)
{
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_PLMN_USER_RESEL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnUserReselReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_USER_RESEL_REQ;
    pstMsg->enPlmnSelMode              = pstPlmnUserReselReq->enPlmnSelMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );


    return;
}


VOS_VOID NAS_MSCC_SndMmcPlmnSpecialReq(
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU     *pstPlmnSpecialReq
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnSpecialReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_SPECIAL_REQ;
    pstMsg->stPlmnId                   = pstPlmnSpecialReq->stPlmnId;
    pstMsg->enAccessMode               = pstPlmnSpecialReq->enAccessMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}
VOS_VOID  NAS_MSCC_SndMmcSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ� */
    pstMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SYS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcSysCfgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SYS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName           = ID_MSCC_MMC_SYS_CFG_SET_REQ;

    pstMsg->ucOnlyRoamParaChanged         = VOS_FALSE;

    /*���β�����д*/
    pstMsg->enRoamCapability              = pstSysCfgReq->enRoamCapability;

    /*����ģʽpMsg->stRatPrioList������д*/
    PS_MEM_CPY(&(pstMsg->stRatPrioList), &(pstSysCfgReq->stRatPrioList), sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));

    /* GUƵ�����ò�����д*/
    pstMsg->stBand.unGsmBand.ulBand        = pstSysCfgReq->stBand.unGsmBand.ulBand;
    pstMsg->stBand.unWcdmaBand.ulBand      = pstSysCfgReq->stBand.unWcdmaBand.ulBand;

    pstMsg->stBand.unCdmaBand.ulCdmaBand   = pstSysCfgReq->stBand.unCdmaBand.ulCdmaBand;

    /* LƵ�����ò�����д */
    pstMsg->stBand.stLteBand.aulLteBand[0] = pstSysCfgReq->stBand.stLteBand.aulLteBand[0];
    pstMsg->stBand.stLteBand.aulLteBand[1] = pstSysCfgReq->stBand.stLteBand.aulLteBand[1];

    pstMsg->ucOnlyRoamParaChanged = pstSysCfgReq->ucOnlyRoamParaChanged;

    pstMsg->ucIsNeedAttachPs = pstSysCfgReq->ucIsNeedAttachPs;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /*��Ϣ����*/
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
VOS_VOID NAS_MSCC_SndMmcNetScanMsgReq(
    MMA_MSCC_NET_SCAN_REQ_STRU         *pstNetScanReq
)
{
    MSCC_MMC_NET_SCAN_REQ_STRU         *pstMsg              = VOS_NULL_PTR;

    /* ������Ϣ�ڴ� */
    pstMsg = (MSCC_MMC_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_NET_SCAN_REQ;

    /* GUƵ�����ò�����д */
    pstMsg->stBand.unGsmBand.ulBand     = pstNetScanReq->stBand.unGsmBand.ulBand;
    pstMsg->stBand.unWcdmaBand.ulBand   = pstNetScanReq->stBand.unWcdmaBand.ulBand;
    pstMsg->sCellPow                    = pstNetScanReq->sCellPow;
    pstMsg->usCellNum                   = pstNetScanReq->usCellNum;
    pstMsg->ucRat                       = pstNetScanReq->ucRat;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /*��Ϣ����*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcAbortNetScanMsgReq(VOS_VOID)
{
    MSCC_MMC_ABORT_NET_SCAN_REQ_STRU   *pstMsg              = VOS_NULL_PTR;

    /* ������Ϣ�ڴ� */
    pstMsg = (MSCC_MMC_ABORT_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcAbortNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_ABORT_NET_SCAN_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /*��Ϣ����*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}
VOS_VOID NAS_MSCC_SndMmcPlmnSearchReq(
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason,
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                   *pstInitAcqPlmnInfo,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo
)
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_SEARCH_REQ;

    pstMsg->enAcqReason = enAcqReason;

    if ((NAS_MSCC_PIF_ACQ_REASON_POWER_UP == enAcqReason)
     && (VOS_NULL_PTR                     != pstInitAcqPlmnInfo))
    {
        PS_MEM_CPY(&(pstMsg->stInitAcqPlmnInfo), pstInitAcqPlmnInfo, sizeof(NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU));
    }

    if ((NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == enAcqReason)
     && (VOS_NULL_PTR                          != pstHighPrioPlmnInfo))
    {
        PS_MEM_CPY(&(pstMsg->stHighPrioPlmnList), pstHighPrioPlmnInfo, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));
    }
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcSpecPlmnSearchAbortReq(VOS_VOID)
{
    MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSpecPlmnSearchAbortReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcOmMaintainInfoInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstMaintainInfoInd
)
{
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_OM_MAINTAIN_INFO_IND;
    pstMsg->ucOmConnectFlg             = pstMaintainInfoInd->ucOmConnectFlg;
    pstMsg->ucOmPcRecurEnableFlg       = pstMaintainInfoInd->ucOmPcRecurEnableFlg;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}



VOS_VOID NAS_MSCC_SndMmcUpdateUplmnNotify( VOS_VOID )
{
    MSCC_MMC_UPDATE_UPLMN_NTF_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_UPDATE_UPLMN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcUpdateUplmnNtf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_UPDATE_UPLMN_NTF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID NAS_MSCC_SndMmcOtherModemInfoNotify(
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstOtherModemInfoNtf
)
{
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOtherModemInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY;
    pstMsg->bitOpCurrCampPlmnId          = pstOtherModemInfoNtf->bitOpCurrCampPlmnId;
    pstMsg->stCurrCampPlmnId.ulMcc       = pstOtherModemInfoNtf->stCurrCampPlmnId.ulMcc;
    pstMsg->stCurrCampPlmnId.ulMnc       = pstOtherModemInfoNtf->stCurrCampPlmnId.ulMnc;
    pstMsg->bitOpEplmnInfo               = pstOtherModemInfoNtf->bitOpEplmnInfo;
    pstMsg->stEplmnInfo.ucEquPlmnNum     = pstOtherModemInfoNtf->stEplmnInfo.ucEquPlmnNum;

    PS_MEM_CPY(pstMsg->stEplmnInfo.astEquPlmnAddr, pstOtherModemInfoNtf->stEplmnInfo.astEquPlmnAddr,
               sizeof(pstMsg->stEplmnInfo.astEquPlmnAddr));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC,pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify(
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU     *pstOhterModemDplmnNplmnInfoNtf
)
{
    MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                 sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY;


    PS_MEM_CPY(&pstMsg->stCmccDplmnNplmnInfo,
        &pstOhterModemDplmnNplmnInfoNtf->stCmccDplmnNplmnInfo, sizeof(pstMsg->stCmccDplmnNplmnInfo));

    PS_MEM_CPY(&pstMsg->stUnicomDplmnNplmnInfo,
        &pstOhterModemDplmnNplmnInfoNtf->stUnicomDplmnNplmnInfo, sizeof(pstMsg->stUnicomDplmnNplmnInfo));

    PS_MEM_CPY(&pstMsg->stCtDplmnNplmnInfo,
        &pstOhterModemDplmnNplmnInfoNtf->stCtDplmnNplmnInfo, sizeof(pstMsg->stCtDplmnNplmnInfo));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcNcellInfoNotify(
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstNcellInfoNtf
)
{
    MSCC_MMC_NCELL_INFO_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_NCELL_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcNcellInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_NCELL_INFO_NOTIFY;

    pstMsg->stTdsNcellInfo.ucTdsArfcnNum = pstNcellInfoNtf->stTdsNcellInfo.ucTdsArfcnNum;
    PS_MEM_CPY(pstMsg->stTdsNcellInfo.ausTdsArfcnList, pstNcellInfoNtf->stTdsNcellInfo.ausTdsArfcnList,
               sizeof(pstMsg->stTdsNcellInfo.ausTdsArfcnList));

    pstMsg->stLteNcellInfo.ucLteArfcnNum = pstNcellInfoNtf->stLteNcellInfo.ucLteArfcnNum;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    PS_MEM_CPY(pstMsg->stLteNcellInfo.aulLteArfcnList, pstNcellInfoNtf->stLteNcellInfo.aulLteArfcnList,
               sizeof(pstMsg->stLteNcellInfo.aulLteArfcnList));
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcPsTransferNotify(
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstPsTransferNtf
)
{
    MSCC_MMC_PS_TRANSFER_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_PS_TRANSFER_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPsTransferInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_PS_TRANSFER_NOTIFY;
    pstMsg->enSolutionCfg                = pstPsTransferNtf->enSolutionCfg;
    pstMsg->ucCause                      = pstPsTransferNtf->ucCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif



VOS_VOID NAS_MSCC_SndMmcEOPlmnSetReq(
    MMA_MSCC_EOPLMN_SET_REQ_STRU       *pstEOPlmnSetReq
)
{
    MSCC_MMC_EOPLMN_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ� */
    pstMsg = (MSCC_MMC_EOPLMN_SET_REQ_STRU*)PS_ALLOC_MSG(
                                         UEPS_PID_MSCC,
                                         sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcEOPlmnSetReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_EOPLMN_SET_REQ;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����Ϣ���� */
    pstMsg->ucIndex      = pstEOPlmnSetReq->ucIndex;
    pstMsg->ucOPlmnCount = pstEOPlmnSetReq->ucOPlmnCount;

    PS_MEM_CPY(pstMsg->aucVersion, pstEOPlmnSetReq->aucVersion, sizeof(pstMsg->aucVersion));

    PS_MEM_CPY(pstMsg->aucOPlmnWithRat, pstEOPlmnSetReq->aucOPlmnWithRat, sizeof(pstMsg->aucOPlmnWithRat));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /*��Ϣ����*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcAcqReq(
    MMA_MSCC_ACQ_REQ_STRU              *pstAcqReq
)
{
    MSCC_MMC_ACQ_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_ACQ_REQ;
    pstMsg->enAcqReason                  = pstAcqReq->enAcqReason;
    pstMsg->ucNotRegAfterAcqSucc        = pstAcqReq->ucNotRegAfterAcqSucc;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcRegReq(
    MMA_MSCC_REG_REQ_STRU              *pstRegReq
)
{
    MSCC_MMC_REG_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_REG_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcRegReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_REG_REQ;
    pstMsg->bitOpPrioClass               = pstRegReq->bitOpPrioClass;
    pstMsg->bitOpCellInfo                = pstRegReq->bitOpCellInfo;
    pstMsg->bitSpare                     = pstRegReq->bitSpare;
    pstMsg->enPrioClass                  = pstRegReq->enPrioClass;

    PS_MEM_CPY(&(pstMsg->stCellInfo), &(pstRegReq->stCellInfo), sizeof(NAS_MSCC_PIF_REG_CELL_INFO_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcPowerSaveReq(VOS_VOID)
{
    MSCC_MMC_POWER_SAVE_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_POWER_SAVE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPowerSaveReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_POWER_SAVE_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

#if(FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_MSCC_SndMmcSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_SRV_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_SRV_ACQ_REQ;
    pstMsg->enSrvType                    = pstSrvAcqReq->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
)
{
    MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcBeginSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_BEGIN_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstBeginSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmcEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
)
{
    MSCC_MMC_END_SESSION_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcEndSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_END_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstEndSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif



VOS_VOID NAS_MSCC_SndMmcImsSrvInfoNotify(
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU  *pstImsSrvInfoNtf
)
{
    MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcImsSrvInfoNotify:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY;
    pstMsg->ucImsCallFlg                 = pstImsSrvInfoNtf->ucImsCallFlg;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_TransferMsccToMmcRat(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstPlmnRatPrio,
    NAS_MSCC_PIF_3GPP2_RAT_STRU        *pst3Gpp2Rat
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstPlmnRatPrio, 0, sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));
    PS_MEM_SET(pst3Gpp2Rat, 0, sizeof(NAS_MSCC_PIF_3GPP2_RAT_STRU));

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        switch (pstRatPrio->aucRatPrio[i])
        {
            case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_GSM;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
                pst3Gpp2Rat->auc3GPP2Rat[pst3Gpp2Rat->ucRatNum] = NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X;
                pst3Gpp2Rat->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
                pst3Gpp2Rat->auc3GPP2Rat[pst3Gpp2Rat->ucRatNum] = NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD;
                pst3Gpp2Rat->ucRatNum++;
                break;

            default:
                break;
        }
    }

}



VOS_VOID NAS_MSCC_SndMmcStartReq(
    MMA_MSCC_START_REQ_STRU            *pstStartReq
)
{
    MSCC_MMC_START_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    /* Allocate memory for Stat request */
    pstMsg = (MSCC_MMC_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStartReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_START_REQ;
    pstMsg->enRegDomain                = pstStartReq->enRegDomain;
    pstMsg->enCsimStatus               = NAS_MSCC_PIF_CARD_STATUS_BUTT;
    pstMsg->enUsimStatus               = pstStartReq->enUsimStatus;

    NAS_MSCC_TransferMsccToMmcRat(&pstStartReq->stRatPrio, &pstMsg->stPlmnRatPrio, &pstMsg->st3Gpp2Rat);

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->enCallMode                 = pstStartReq->enCallMode;
#endif
    pstMsg->enRegCtrl                  = pstStartReq->enRegCtrl;

    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT != pstStartReq->enUsimStatus)
    {
        PS_MEM_CPY(pstMsg->aucImsi, pstStartReq->aucImsi, NAS_MAX_IMSI_LENGTH);
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    NAS_TRACE_HIGH("SEND MSG!");

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndMmcPowerOffReq
Description     :   Send the message to MMC

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-02-03
        Author  :   K00902809
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_SndMmcPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
)
{
    MSCC_MMC_POWER_OFF_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocate memory for new message  */
    pstMsg = (MSCC_MMC_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_POWER_OFF_REQ;
    pstMsg->enCause                    = enCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send the message */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    NAS_TRACE_HIGH("Send Msg!");

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcCFPlmnSetReq
 ��������  : ��MMC����fplmn��������Ϣ
 �������  : pstCFPlmnReq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��7��
   ��    ��   : f00279542s
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCFPlmnSetReq(
    MMA_MSCC_CFPLMN_SET_REQ_STRU       *pstCFPlmnReq
)
{
    MSCC_MMC_CFPLMN_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_CFPLMN_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                         sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCFPlmnSetReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CFPLMN_SET_REQ;
    pstMsg->enCmdType                    = pstCFPlmnReq->enCmdType;
    pstMsg->stPlmnInfo.ulMcc             = pstCFPlmnReq->stPlmnInfo.ulMcc;
    pstMsg->stPlmnInfo.ulMnc             = pstCFPlmnReq->stPlmnInfo.ulMnc;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcCFPlmnQueryReq
 ��������  : ��MMC����fplmn��������Ϣ
 �������  :pstCFPlmnReq : query req info
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��7��
   ��    ��   : f00279542s
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCFPlmnQueryReq(
    MMA_MSCC_CFPLMN_QUERY_REQ_STRU     *pstCFPlmnReq
)
{
    MSCC_MMC_CFPLMN_QUERY_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_CFPLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                               sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCFPlmnQueryReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CFPLMN_QUERY_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcSdtConnedInd
 ��������  : ����mscc������ ��������
 �������  : pstMaintainInfoInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��7��
   ��    ��   : f00279542s
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcSdtConnedInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstSdtConnInfoInd
)
{
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                   sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSdtConnedInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SDT_CONNECTED_IND;
    pstMsg->ucOmConnectFlg             = pstSdtConnInfoInd->ucOmConnectFlg;
    pstMsg->ucOmPcRecurEnableFlg       = pstSdtConnInfoInd->ucOmPcRecurEnableFlg;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);
    return;
}
/* Added by y00307564 for CDMA Iteration 8 2015-2-4 begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcPrefPlmnSetReq
 ��������  : ����ID_MSCC_MMC_PREF_PLMN_SET_REQ��Ϣ
 �������  : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��04��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPrefPlmnSetReq(
    MMA_MSCC_PREF_PLMN_SET_REQ_STRU    *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPrefPlmnSetReq = (MSCC_MMC_PREF_PLMN_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                     sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnSetReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPrefPlmnSetReq ERROR:Memory Alloc Error for pstPrefPlmnSetReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPrefPlmnSetReq) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPrefPlmnSetReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnSetReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnSetReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnSetReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPrefPlmnSetReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnSetReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PREF_PLMN_SET_REQ;

    /* �����Ϣ���� */
    pstPrefPlmnSetReq->enPrefPlmnParaType            = pstMsg->enPrefPlmnParaType;

    PS_MEM_CPY(&(pstPrefPlmnSetReq->stCtrl),
               &(pstMsg->stCtrl),
               sizeof(NAS_MSCC_CTRL_STRU));

    PS_MEM_CPY(&(pstPrefPlmnSetReq->stPrefPlmnOpt),
               &(pstMsg->stPrefPlmnOpt),
               sizeof(NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnSetReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnSetReq);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcPrefPlmnQueryReq
 ��������  : ����ID_MSCC_MMC_PREF_PLMN_QUERY_REQ��Ϣ
 �������  : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��04��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPrefPlmnQueryReq(
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU  *pstPrefPlmnQueryReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPrefPlmnQueryReq = (MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnQueryReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPrefPlmnQueryReq ERROR:Memory Alloc Error for pstPrefPlmnQueryReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnQueryReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPrefPlmnQueryReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnQueryReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PREF_PLMN_QUERY_REQ;

    /* �����Ϣ���� */
    pstPrefPlmnQueryReq->enCmdType                     = pstMsg->enCmdType;
    pstPrefPlmnQueryReq->bPlmnSelFlg                   = pstMsg->bPlmnSelFlg;
    pstPrefPlmnQueryReq->stCpolInfo.enPrefPLMNType     = pstMsg->stCpolInfo.enPrefPLMNType;
    pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex        = pstMsg->stCpolInfo.ulFromIndex;
    pstPrefPlmnQueryReq->stCpolInfo.ulPlmnNum          = pstMsg->stCpolInfo.ulPlmnNum;
    pstPrefPlmnQueryReq->stCpolInfo.ulValidPlmnNum     = pstMsg->stCpolInfo.ulValidPlmnNum;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnQueryReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnQueryReq);

    return;
}
/* Added by y00307564 for CDMA Iteration 8 2015-2-4 end */

VOS_VOID NAS_MSCC_SndMmcGetGeoReq(
    MMA_MSCC_GET_GEO_REQ_STRU          *pstMsg
)
{
    MSCC_MMC_GET_GEO_REQ_STRU          *pstSndMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstSndMsg = (MSCC_MMC_GET_GEO_REQ_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMC_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* �����Ϣ���� */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* ��д��Ϣͷ */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMC, ID_MSCC_MMC_GET_GEO_REQ);

    /* ��д��Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;
}
VOS_VOID NAS_MSCC_SndMmcStopGetGeoReq(
    MMA_MSCC_STOP_GET_GEO_REQ_STRU     *pstMsg
)
{
    MSCC_MMC_STOP_GET_GEO_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstSndMsg = (MSCC_MMC_STOP_GET_GEO_REQ_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMC_STOP_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStopGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* �����Ϣ���� */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* ��д��Ϣͷ */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMC, ID_MSCC_MMC_STOP_GET_GEO_REQ);

    /* ��д��Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;
}


#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MSCC_SndMmcVoiceDomainChangeInd(
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32                   enVoiceDomain
)
{
    MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU                  *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcVoiceDomainChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->enVoiceDomain                = enVoiceDomain;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
)
{
    MSCC_MMC_IMS_SWITCH_STATE_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_IMS_SWITCH_STATE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsSwitchStateInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_SWITCH_STATE_IND;
    pstMsg->enImsSwitch                  = enImsSwitch;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#endif


VOS_VOID NAS_MSCC_SndMmcAutoReselSetReq(
    VOS_UINT8                           ucActiveFlg
)
{
    MSCC_MMC_AUTO_RESEL_SET_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMC_AUTO_RESEL_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsSwitchStateInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_AUTO_RESEL_SET_REQ;
    pstMsg->ucActiveFlg                  = ucActiveFlg;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/* Added by y00307564 for CDMA Iteration 10 2015-4-3 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_SndMmcBgSearchReq
Description     :   MSCC send msg to MMC background search HRPD

Input parameters:   VOS_RATMODE_ENUM_UINT32             enRatMode
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-04-03
    Author         : y00307564
    Modify content : Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
)
{
    MSCC_MMC_BG_SEARCH_REQ_STRU        *pstMsccMmcBgSearchReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstMsccMmcBgSearchReq = (MSCC_MMC_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsccMmcBgSearchReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcBgSearchReq ERROR:Memory Alloc Error for pstMsccMmcBgSearchReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsccMmcBgSearchReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstMsccMmcBgSearchReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsccMmcBgSearchReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsccMmcBgSearchReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsccMmcBgSearchReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsccMmcBgSearchReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsccMmcBgSearchReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_BG_SEARCH_REQ;

    /* �����Ϣ���� */
    pstMsccMmcBgSearchReq->enRatMode                     = enRatMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsccMmcBgSearchReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsccMmcBgSearchReq);

}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndMmcBgSearchReq
Description     :   MSCC send msg to MMC background search HRPD

Input parameters:
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-04-03
    Author         : y00307564
    Modify content : Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcStopBgSearchReq(VOS_VOID)
{
    MSCC_MMC_STOP_BG_SEARCH_REQ_STRU   *pstMsccMmcStopBgSearchReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstMsccMmcStopBgSearchReq = (MSCC_MMC_STOP_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsccMmcStopBgSearchReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStopBgSearchReq ERROR:Memory Alloc Error for pstMsccMmcBgSearchReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsccMmcStopBgSearchReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_STOP_BG_SEARCH_REQ;

    /* �����Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsccMmcStopBgSearchReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsccMmcStopBgSearchReq);

}



VOS_VOID NAS_MSCC_SndMmcPlmnPriClassQueryReq(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstPlmnList
)
{
    MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU                 *pstPlmnPriClassQueryReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPlmnPriClassQueryReq = (MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPlmnPriClassQueryReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnPriClassQueryReq ERROR:Memory Alloc Error for pstPrefPlmnQueryReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnPriClassQueryReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPlmnPriClassQueryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPlmnPriClassQueryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPlmnPriClassQueryReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPlmnPriClassQueryReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ;

    PS_MEM_CPY(&pstPlmnPriClassQueryReq->stPlmnListInfo, pstPlmnList, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnPriClassQueryReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnPriClassQueryReq);

    return;
}

/* Added by y00307564 for CDMA Iteration 10 2015-4-3 end */

/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmcInterSysHrpdInd
 ��������  : ����MSCC_MMC_INTERSYS_HRPD_NTF_STRU��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcInterSysHrpdInd(VOS_VOID)
{
    MSCC_MMC_INTERSYS_HRPD_NTF_STRU    *pstInterSysHrpdInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstInterSysHrpdInd = (MSCC_MMC_INTERSYS_HRPD_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstInterSysHrpdInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcInterSysHrpdInd ERROR:Memory Alloc Error for pstInterSysHrpdInd ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstInterSysHrpdInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstInterSysHrpdInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInterSysHrpdInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstInterSysHrpdInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInterSysHrpdInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstInterSysHrpdInd->stMsgHeader.ulLength          = sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterSysHrpdInd->stMsgHeader.ulMsgName         = ID_MSCC_MMC_INTERSYS_HRPD_NTF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstInterSysHrpdInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstInterSysHrpdInd);

    return;
}
#endif
/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, end */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



