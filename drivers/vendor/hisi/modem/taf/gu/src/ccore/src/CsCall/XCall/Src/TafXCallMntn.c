

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_INFO_STRU  *pstLogCallInfoMsg;

    pstLogCallInfoMsg = (TAF_XCALL_MNTN_LOG_CALL_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                    sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    if (VOS_NULL_PTR == pstLogCallInfoMsg)
    {
        return;
    }

    PS_MEM_SET(pstLogCallInfoMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    /* ��Ϣ��װ */
    pstLogCallInfoMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulReceiverPid       = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulLength            = sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLogCallInfoMsg->enMsgId             = ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND;

    PS_MEM_CPY(pstLogCallInfoMsg->astCallEntity,
               TAF_XCALL_GetCtxAddr()->astCallEntity,
               TAF_XCALL_CALL_ENTITY_MAX_NUM * sizeof(TAF_XCALL_CALL_ENTITY_STRU));

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(pstLogCallInfoMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstLogCallInfoMsg);

    return;

}


VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU                   stLogSupsCmdMgmt;

    PS_MEM_SET(&stLogSupsCmdMgmt, 0x00, sizeof(stLogSupsCmdMgmt));

    /* ��Ϣ��װ */
    stLogSupsCmdMgmt.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulSenderPid         = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulReceiverPid       = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulLength            = sizeof(stLogSupsCmdMgmt) - VOS_MSG_HEAD_LENGTH;

    stLogSupsCmdMgmt.enMsgId             = ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT;

    PS_MEM_CPY(&(stLogSupsCmdMgmt.stSupsCmdMgmt),
               TAF_XCALL_GetSupsCmdMgmt(),
               sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stLogSupsCmdMgmt);

    return;

}

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_MNTN_LogEmcCallRedialPeriod
 ��������  : ��ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU              stLogEmcCallRedialPeriod;

    PS_MEM_SET(&stLogEmcCallRedialPeriod, 0x00, sizeof(stLogEmcCallRedialPeriod));

    /* ��Ϣ��װ */
    stLogEmcCallRedialPeriod.ulSenderCpuId                  = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulSenderPid                    = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulReceiverCpuId                = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulReceiverPid                  = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulLength                       = sizeof(TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogEmcCallRedialPeriod.enMsgId                        = ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD;
    stLogEmcCallRedialPeriod.ulEmcRedialPeriod              = TAF_XCALL_GetConfigInfo()->ulEmcRedialPeriod;

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stLogEmcCallRedialPeriod);

    return;
}

/* Added by h00313353 for Iteration 17, 2015-8-7, end */

/*****************************************************************************
 �� �� ��  : TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval
 ��������  : ��TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU                   stLogMntn;

    PS_MEM_SET(&stLogMntn, 0x00, sizeof(stLogMntn));

    /* ��Ϣ��װ */
    stLogMntn.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stLogMntn.ulSenderPid       = WUEPS_PID_TAF;
    stLogMntn.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stLogMntn.ulReceiverPid     = WUEPS_PID_TAF;
    stLogMntn.ulLength          = sizeof(TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMntn.enMsgId           = ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL;
    stLogMntn.ulStartAndStopContDtmfInterval = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stLogMntn);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




