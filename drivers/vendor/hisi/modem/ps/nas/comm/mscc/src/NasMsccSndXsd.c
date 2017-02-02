

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccSndXsd.h"
#include "NasMntn.h"
#include "xsd_mscc_pif.h"
#include "MmaMsccInterface.h"
#include "NasMsccComFunc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_XSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID NAS_MSCC_SndXsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
)
{
    MSCC_XSD_START_REQ_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* Allocate the memory for Message */
    pstMsg = (MSCC_XSD_START_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_START_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdStartReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_START_REQ;
    pstMsg->enCardStatus                 = enCsimStatus;

    pstMsg->enModemId                    = VOS_GetModemIDFromPid(UEPS_PID_MSCC);
    pstMsg->ucSuppRatNum                 = pstRatPrio->ucRatNum;

    for (i = 0; i < NAS_MSCC_PIF_MAX_RAT_NUM; i++)
    {
        pstMsg->aenRatMode[i] = NAS_MSCC_TransferMsccToVosRat(pstRatPrio->aucRatPrio[i]);
    }


    pstMsg->ucIsCardChanged             = NAS_MSCC_GetIsCardChangedFlg();

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* send the start request to XSD */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("NAS_MSCC_SndXsdStartReq successfully...");

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_SndXsdPowerOffReq
Description     :   Send the message to XSD

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-02-03
        Author  :   K00902809
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
)
{
    MSCC_XSD_POWER_OFF_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_POWER_OFF_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdPowerOffReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_XSD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_XSD_POWER_OFF_REQ;
    pstMsg->enCause                    = enCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("Send xsd Cdma Power Off Msg!");

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCdmaMoCallStartNtf
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
)
{
    MSCC_XSD_MO_CALL_START_NTF_STRU    *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_MO_CALL_START_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_MO_CALL_START_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCdmaMoCallStartNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_MO_CALL_START_NTF;
    pstMsg->enCallType                   = pstCdmaMoCallStartNtf->enCallType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);


}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU    *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF;
    pstMsg->enCallType                   = pstCdmaMoCallRedialSysAcqNtf->enCallType;
    pstMsg->enCause                      = pstCdmaMoCallRedialSysAcqNtf->enCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCdmaMoCallSuccessNtf
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
)
{
    MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU  *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCdmaMoCallSuccessNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_MO_CALL_SUCCESS_NTF;
    pstMsg->enCallType                   = pstCdmaMoCallSuccessNtf->enCallType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCdmaMoCallEndNtf
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
)
{
    MSCC_XSD_1X_MO_CALL_END_NTF_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_1X_MO_CALL_END_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_1X_MO_CALL_END_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCdmaMoCallEndNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_1X_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_1X_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_MO_CALL_END_NTF;
    pstMsg->enCallType                   = pstCdmaMoCallEndNtf->enCallType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCfreqLockNtf
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf
)
{
    MSCC_XSD_CFREQ_LOCK_NTF_STRU       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_CFREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_CFREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCfreqLockNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_CFREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY((VOS_INT8*)pstMsg, pstCfreqLockNtf, sizeof(MSCC_XSD_CFREQ_LOCK_NTF_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_CFREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_CFREQLOCK_NTF;


    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdCdmacsqSetReq
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
)
{
    MSCC_XSD_CDMACSQ_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_CDMACSQ_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdCdmacsqSetReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    PS_MEM_CPY((VOS_INT8*)pstMsg, (VOS_INT8*)pstCdmacsqSetReq, sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_CDMACSQ_SET_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}


VOS_VOID NAS_MSCC_SndXsdSysAcqReq(VOS_VOID)
{
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdSysAcqReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndXsdPowerSaveReq(VOS_VOID)
{
    MSCC_XSD_POWER_SAVE_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* Allocate the memory for Message */
    pstMsg = (MSCC_XSD_POWER_SAVE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_POWER_SAVE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdPowerSaveReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_POWER_SAVE_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* send the Power save request to XSD */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndXsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
)
{
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT16                          i;

    /* Allocate the memory for Message */
    pstMsg = (MSCC_XSD_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_SYS_CFG_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdSysCfgReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;

    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_SYS_CFG_REQ;
    pstMsg->ucSuppRatNum                 = pstSysCfgReq->stRatPrioList.ucRatNum;
    pstMsg->stCdmaBand                   = pstSysCfgReq->stBand.unCdmaBand.stCdmaBitBand;

    for (i = 0; i < pstSysCfgReq->stRatPrioList.ucRatNum; i++)
    {
        pstMsg->aenRatMode[i]            = NAS_MSCC_TransferMsccToVosRat(pstSysCfgReq->stRatPrioList.aucRatPrio[i]);
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* send the system config request to XSD */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}




VOS_VOID NAS_MSCC_SndXsdHrpdCasStatusInd(
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstCasStatusInd
)
{
    MSCC_XSD_CAS_STATUS_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_CAS_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_CAS_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdHrpdCasStatusInd:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    /* Modified by t00323010 for CDMA Iteration 16 2015-8-7 begin */
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    /* Modified by t00323010 for CDMA Iteration 16 2015-8-7 end */
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_CAS_STATUS_IND;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/* Added by z00316370 for UTS 2015-5-22 begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdHandsetInfoQryReq
 ��������  : ��XSD�����ֻ���Ϣ��ѯ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdHandsetInfoQryReq(
    VOS_UINT32                          ulInfoType
)
{
    MSCC_XSD_HANDSET_INFO_QRY_STRU      *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_XSD_HANDSET_INFO_QRY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MSCC_XSD_HANDSET_INFO_QRY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdHandsetInfoQryReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_HANDSET_INFO_QRY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_HANDSET_INFO_QRY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_HANDSET_INFO_QRY_REQ;
    pstMsg->ulInfoType                   = ulInfoType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/* Added by z00316370 for UTS 2015-5-22 end */

VOS_VOID NAS_MSCC_SndXsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
)
{
    MSCC_XSD_SRV_ACQ_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_XSD_SRV_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_SRV_ACQ_REQ;
    pstMsg->enSrvType                    = pstSrvAcqReq->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndXsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
)
{
    MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdBeginSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_BEGIN_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstBeginSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndXsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
)
{
    MSCC_XSD_END_SESSION_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_XSD_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdEndSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_END_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstEndSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/* Added by h00313353 for Iteration 17, 2015-7-7, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndXsdEndEmcCallBackReq
 ��������  : ��XSD��������񴥷�������ָʾ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdEndEmcCallBackNtf( VOS_VOID )
{
    MSCC_XSD_END_EMC_CALLBACK_NTF_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_XSD_END_EMC_CALLBACK_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_END_EMC_CALLBACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndXsdSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                     sizeof(MSCC_XSD_END_EMC_CALLBACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_END_EMC_CALLBACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_END_EMC_CALLBACK_NTF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/* Added by h00313353 for Iteration 17, 2015-7-7, end */

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



