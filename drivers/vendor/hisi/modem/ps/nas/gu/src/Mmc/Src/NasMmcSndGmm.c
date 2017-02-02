
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMmcSndGmm.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcProcRegRslt.h"
#include "MM_Share.h"
#include "NasMmcComFunc.h"
#include "NVIM_Interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_GMM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

VOS_VOID NAS_MMC_SndGmmStartReq(VOS_VOID)
{
    MMCGMM_START_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg  = (MMCGMM_START_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_START_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_START_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}




VOS_VOID NAS_MMC_SndGmmPowerOffReq(VOS_VOID)
{
    MMCGMM_POWER_OFF_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg  = (MMCGMM_POWER_OFF_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_POWER_OFF_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���  */
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_POWER_OFF_REQ;              /* ��д��Ϣ����                             */

    NAS_MML_SndInternalMsg(pstMsg);
}
VOS_VOID   NAS_MMC_SndGmmPlmnSchInit(VOS_VOID)
{
    MMCGMM_PLMN_SEARCH_INITIATED_STRU  *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_PLMN_SEARCH_INITIATED_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_PLMN_SEARCH_INITIATED_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstInternalMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_PLMN_SEARCH_INITIATED_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���                             */
    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_PLMN_SEARCH_INITIATED;              /* ��д��Ϣ����                             */

    NAS_MML_SndInternalMsg(pstInternalMsg);

}



VOS_VOID NAS_MMC_SndGmmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
)
{
    /*��GMM���͹���ָʾ,����ԭ������ָ�� */
    MMCGMM_SUSPEND_IND_ST              *pstSndMsg       = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg  = (MMCGMM_SUSPEND_IND_ST*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SUSPEND_IND_ST));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName       = MMCGMM_SUSPEND_IND;
    pstSndMsg->MsgHeader.ulLength        = sizeof(MMCGMM_SUSPEND_IND_ST) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ucSuspendCause            = pstMsg->ucSuspendCause;
    pstSndMsg->ucSuspendOrigen           = pstMsg->ucSuspendOrigen;

    pstSndMsg->ucSuspendDestination      = pstMsg->ucSuspendDestination;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}
VOS_VOID NAS_MMC_SndGmmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    /*��GMM���ͻָ�ָʾ,����ԭ������ָ�� */
    MMCGMM_RESUME_IND_ST               *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg  = (MMCGMM_RESUME_IND_ST*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_RESUME_IND_ST));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    pstSndMsg->MsgHeader.ulLength
        = sizeof(RRMM_RESUME_IND_ST) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName   = MMCGMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucPsSigExistFlg       = VOS_FALSE;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

VOS_VOID  NAS_MMC_SndGmmCoverageLostInd(VOS_VOID)
{
    MMCGMM_COVERAGE_LOST_IND_STRU      *pstInternalMsg;

    pstInternalMsg  = (MMCGMM_COVERAGE_LOST_IND_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_COVERAGE_LOST_IND_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    /* ��д��Ϣ���  */
    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_COVERAGE_LOST_IND;
    pstInternalMsg->MsgHeader.ulLength    = sizeof(MMCGMM_COVERAGE_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID NAS_MMC_SndGmmAttachReq(
    VOS_UINT32                          ulOpid,
    VOS_UINT32                          ulMmcAttachType
)
{
    MMCGMM_ATTACH_REQ_STRU             *pstMsg;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */

    pstMsg          = (MMCGMM_ATTACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_ATTACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_ATTACH_REQ;
    pstMsg->ulOpid                      = ulOpid;
    pstMsg->enAttachType                = ulMmcAttachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}
VOS_VOID NAS_MMC_SndGmmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType,  /* detach���� */
    MMC_GMM_DETACH_REASON_ENUM_UINT32   enDetachReason /* detachԭ�� */
)
{
    MMCGMM_DETACH_REQ_STRU             *pstMsg;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCGMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_DETACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_DETACH_REQ;
    pstMsg->ulOpid                      = ulOpid;
    pstMsg->enDetachType                = enDetachType;
    pstMsg->enDetachReason              = enDetachReason;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}
VOS_VOID NAS_MMC_SndGmmRelReq(VOS_VOID)
{
    /* ��GMM����PS���������ͷ���Ϣ */
    MMCGMM_REL_REQ_STRU                *pstSndGmmRelMsg     = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndGmmRelMsg = (MMCGMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndGmmRelMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmRelReq:ALLOC MEM ERROR!");
        return;
    }

    pstSndGmmRelMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndGmmRelMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndGmmRelMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndGmmRelMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    /* ��д��Ϣ��� */
    pstSndGmmRelMsg->MsgHeader.ulMsgName         = MMCGMM_REL_REQ;
    pstSndGmmRelMsg->MsgHeader.ulLength          = sizeof(MMCGMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndGmmRelMsg);

    return;

}






#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndGmmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{
    /* ����ԭ������ָ�� */
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg          = (MMC_GMM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmLteSysinfoInd:Alloc Mem Failed");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstLmmSysInfoMsg, sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU));

    pstMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->ulMsgId           = MMCGMM_LTE_SYS_INFO_IND;
    pstMsg->ulLength          = sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return ;
}
VOS_VOID  NAS_MMC_SndGmmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU        *pstAttachInd
)
{
    MMCGMM_LMM_ATTACH_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_ATTACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_ATTACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmAttachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstAttachInd, sizeof(MMCGMM_LMM_ATTACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_ATTACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_ATTACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
VOS_VOID  NAS_MMC_SndGmmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstActionResultInd
)
{
    MMCGMM_LMM_TAU_RESULT_IND_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_TAU_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmTauResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_TAU_RESULT_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
VOS_VOID  NAS_MMC_SndGmmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstActionResultInd
)
{
    MMCGMM_LMM_MT_DETACH_IND_STRU      *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCGMM_LMM_MT_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmMtDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_MT_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstActionResultInd
)
{
    MMCGMM_LMM_LOCAL_DETACH_IND_STRU   *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCGMM_LMM_LOCAL_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_LOCAL_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    MMCGMM_LMM_MO_DETACH_IND_STRU      *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCGMM_LMM_MO_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmMoDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstLmmDetachCnf, sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_MO_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstSerInd
)
{
    MMCGMM_LMM_SERVICE_RESULT_IND_STRU *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_SERVICE_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmSerResultnd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstSerInd, sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_SERVICE_RESULT_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmStatusInd(
    LMM_MMC_STATUS_IND_STRU            *pstStatusInd
)
{
    MMCGMM_LMM_STATUS_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_STATUS_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_STATUS_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstStatusInd, sizeof(MMCGMM_LMM_STATUS_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_STATUS_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_STATUS_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
)
{
    MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTimerStatusNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstTimerStatusNotify, sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_TIMER_STATE_NOTIFY;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmEmergencyNumList(
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstEmergencyNumList
)
{
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg = (MMCGMM_EMERGENCY_NUM_LIST_IND_STRU *)
                  NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmEmergencyNumList,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstEmergencyNumList, sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU)
                                       - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_EMERGENCY_NUM_LIST_IND;


    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#endif



VOS_VOID NAS_MMC_SndGmmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU         *pstMsg;

    /* ���ڲ���Ϣ�����л�ȡһ����ʱ���͵Ŀռ� */
    pstMsg          = (MMCGMM_MODE_CHANGE_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_MODE_CHANGE_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmModeChangeReq:Alloc Mem Failed");
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_MODE_CHANGE_REQ;
    pstMsg->enMsMode                    = enMsMode;

    NAS_MML_SndInternalMsg(pstMsg);
}



VOS_VOID   NAS_MMC_SndGmmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SYS_INFO_IND_STRU           *pstInternalMsg    = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SYS_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET(pstInternalMsg, 0x00, sizeof(MMCGMM_SYS_INFO_IND_STRU));

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU *)pstMsg;

    /* ��䷢����Ϣ */
    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstInternalMsg->MsgHeader.ulMsgName         = MMCGMM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength          = sizeof(MMCGMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ulCellId              = pstRrMmSysInfoInd->ulCellId;

    /* ����ϵͳ��Ϣ�����ݣ����Maskֵ */
    pstInternalMsg->ulMask = NAS_MMC_GetOptMask_WasSysinfo(pstRrMmSysInfoInd);

    /* ����Common��Ϣ */
    pstInternalMsg->ulCnCommonSize  = (VOS_UINT32)pstRrMmSysInfoInd->ucCnCommonSize;

    PS_MEM_CPY(pstInternalMsg->aucCnCommonInfo,
               pstRrMmSysInfoInd->aucCnCommonInfo, RRC_NAS_MAX_SIZE_NAS_GSM_MAP);

    PS_MEM_CPY(pstInternalMsg->aulPsInfo,
               pstRrMmSysInfoInd->aucPsInfo, RRC_NAS_MAX_SIZE_NAS_GSM_MAP);

    pstInternalMsg->ulPsInfoSize           = (VOS_UINT32)pstRrMmSysInfoInd->ucPsInfoSize;
    pstInternalMsg->PlmnId.ulMcc           = pstRrMmSysInfoInd->PlmnId.ulMcc;
    pstInternalMsg->PlmnId.ulMnc           = pstRrMmSysInfoInd->PlmnId.ulMnc;

    pstInternalMsg->ulPsDrxLength          = pstRrMmSysInfoInd->ulPsDrxLength;

    pstInternalMsg->ulUserSrchFlg          = VOS_FALSE;

    pstInternalMsg->ulForbiddenMask    = ulForbiddenFlg;

    /* ��Hplmn��CSע�ᱻ�ܺ󣬷�E5ʱ�����ڷ���ע�� ,E5ʱ��HplmnRejlist����¼ֵ */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        if (VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(NAS_MMC_REG_DOMAIN_PS))
        {
            if (MMCMM_NO_FORBIDDEN == ulForbiddenFlg)
            {
                pstInternalMsg->ulForbiddenMask   = MMCMM_FORBIDDEN_PLMN;
            }

            if (VOS_TRUE == NAS_MML_GetHplmnRegisterCtrlFlg())
            {
                pstInternalMsg->ulForbiddenMask   &= (~MMCMM_FORBIDDEN_PLMN);
            }
        }
    }


    /* ��barתΪ��bar�ı�־λ */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID   NAS_MMC_SndGmmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstInternalMsg  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_GSM_SYS_INFO_IND_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_GSM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength    = sizeof(MMCGMM_GSM_SYS_INFO_IND_ST) - VOS_MSG_HEAD_LENGTH;

    /* ���CS��Ϣ */
    pstInternalMsg->ucAttachDetach           = pstGrrMmSysInfo->ucAttachDetach;
    pstInternalMsg->ucLRTimerT3212           = pstGrrMmSysInfo->ucLRTimerT3212;
    pstInternalMsg->ucGprsSupportInd         = pstGrrMmSysInfo->ucGprsSupportInd;
    pstInternalMsg->usLac                    = pstGrrMmSysInfo->usLac;
    pstInternalMsg->ucSgsnRelease            = pstGrrMmSysInfo->ucSgsnRelease;

    /* ���PS��Ϣ */
    if ( GRRMM_NW_OP_MODE_III == pstGrrMmSysInfo->ucNetworkOperationMode)
    {
        pstInternalMsg->ucNetworkOperationMode   = GRRMM_NW_OP_MODE_II;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode   = pstGrrMmSysInfo->ucNetworkOperationMode;
    }

    pstInternalMsg->ucRac                    = pstGrrMmSysInfo->ucRac;
    pstInternalMsg->usCellId                 = pstGrrMmSysInfo->usCellId;
    pstInternalMsg->stPlmnId.ulMcc           = pstGrrMmSysInfo->PlmnId.ulMcc;
    pstInternalMsg->stPlmnId.ulMnc           = pstGrrMmSysInfo->PlmnId.ulMnc;

    pstInternalMsg->ucDrxTimerMax            = pstGrrMmSysInfo->ucDrxTimerMax;

    pstInternalMsg->ulUserSrchFlg            = VOS_FALSE;

    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* ��Hplmn��CSע�ᱻ�ܺ󣬷�E5ʱ�����ڷ���ע�� ,E5ʱ��HplmnRejlist����¼ֵ */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        if ((VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(NAS_MMC_REG_DOMAIN_PS))
         && (MMCMM_NO_FORBIDDEN == ulForbiddenFlg))
        {
            pstInternalMsg->ulForbiddenFlg   = MMCMM_FORBIDDEN_PLMN;
        }
    }

    /* ��Hplmn��PSע�ᱻ�ܺ󣬷�E5ʱ�����ڷ���ע�� ,E5ʱ��HplmnRejlist����¼ֵ */
    if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
     && (VOS_FALSE == ulUserSrchFlg))
    {
        if ((VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(NAS_MMC_REG_DOMAIN_PS))
         && (NAS_MML_PLMN_FORBID_NULL == ulForbiddenFlg))
        {
            pstInternalMsg->ulForbiddenFlg  = MMC_GMM_FORBIDDEN_PLMN;
        }
    }

    pstInternalMsg->unAcInfo.ucRestrictType               = pstGrrMmSysInfo->unAcInfo.ucRestrictType;

    /* �����GSM��ֹ���룬֪ͨMM/GMM����ֹ����ע�� */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        pstInternalMsg->unAcInfo.ucRestrictType            = RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE;
    }

    /* ��barתΪ��bar�ı�־λ */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;

}


VOS_VOID  NAS_MMC_SndGmmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstSndMsg           = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_W_AC_INFO_CHANGE_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmWasAcInfoChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_W_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstSndMsg->MsgHeader.ulMsgName          = MMCGMM_W_AC_INFO_CHANGE_IND;

    pstSndMsg->enCsRestrictRegisterChange   = NAS_MML_RESTRICTION_NO_CHANGE;
    pstSndMsg->enPsRestrictRegisterChange   = NAS_MML_RESTRICTION_NO_CHANGE;

    /* CSע������ޱ�Ϊ������ */
    if ((VOS_TRUE == ucOldCsResTrictionRegister)
     && (VOS_FALSE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* CSע��Ӳ����ޱ�Ϊ���� */
    if ((VOS_FALSE == ucOldCsResTrictionRegister)
     && (VOS_TRUE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* PSע������ޱ�Ϊ������ */
    if ((VOS_TRUE == ucOldPsResTrictionRegister)
     && (VOS_FALSE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* PSע��Ӳ����ޱ�Ϊ���� */
    if ((VOS_FALSE == ucOldPsResTrictionRegister)
     && (VOS_TRUE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }


    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}
VOS_VOID  NAS_MMC_SndGmmVoiceDomainChangeNotify(VOS_VOID)
{
    MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU *pstSndMsg           = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmVoiceDomainChangeNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstSndMsg->MsgHeader.ulMsgName         = MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

