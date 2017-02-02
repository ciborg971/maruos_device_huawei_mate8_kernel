

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccSndHsd.h"
#include "NasMntn.h"

#include "NasMsccCtx.h"
#include "MsccMmcInterface.h"
#include "hsd_mscc_pif.h"
#include "NasComm.h"
#include "NasMsccComFunc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_HSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID NAS_MSCC_SndHsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
)
{
    MSCC_HSD_START_REQ_STRU            *pstMsg            = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* Allocate the memory for Message */
    pstMsg = (MSCC_HSD_START_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_START_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdStartReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_START_REQ;
    pstMsg->enCsimStatus                 = enCsimStatus;
    pstMsg->enUsimStatus                 = enUsimStatus;
    pstMsg->enModemId                    = MODEM_ID_0;

    pstMsg->ucSuppRatNum                 = pstRatPrio->ucRatNum;
    pstMsg->ucIsCardChanged              = NAS_MSCC_GetIsCardChangedFlg();

    for (i = 0; i < NAS_MSCC_PIF_MAX_RAT_NUM; i++)
    {
        pstMsg->aenRatMode[i] = NAS_MSCC_TransferMsccToVosRat(pstRatPrio->aucRatPrio[i]);
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* send start request message to HSD */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("SEND MSG!");

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdPowerOffReq
Description     :   Send the message to HSD

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-02-03
        Author  :   K00902809
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdPowerOffReq(
    MSCC_HSD_POWER_OFF_CAUSE_ENUM_UINT32 enCause
)
{
    MSCC_HSD_POWER_OFF_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_POWER_OFF_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdPowerOffReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_POWER_OFF_REQ;
    pstMsg->enCause          = enCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("Send Hsd Cdma Power Off Msg!");

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCdmaMoCallStartNtf
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
VOS_VOID NAS_MSCC_SndHsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
)
{
    MSCC_HSD_DATA_CALL_START_NTF_STRU  *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_DATA_CALL_START_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_DATA_CALL_START_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmaMoCallStartNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_DATA_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_DATA_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_DATA_CALL_START_NTF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);


}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf
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
VOS_VOID NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
)
{
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU             *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ;


    pstMsg->enCallType                   = pstCdmaMoCallRedialSysAcqNtf->enCallType;
    pstMsg->enCause                      = pstCdmaMoCallRedialSysAcqNtf->enCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCdmaMoCallSuccessNtf
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
VOS_VOID NAS_MSCC_SndHsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
)
{
    MSCC_HSD_DATA_CALL_SUCC_NTF_STRU  *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_DATA_CALL_SUCC_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_DATA_CALL_SUCC_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmaMoCallSuccessNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_DATA_CALL_SUCC_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_DATA_CALL_SUCC_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_DATA_CALL_SUCC_NTF;


    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}




/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCdmaMoCallEndNtf
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
VOS_VOID NAS_MSCC_SndHsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
)
{
    MSCC_HSD_DATA_CALL_END_NTF_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_DATA_CALL_END_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_DATA_CALL_END_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmaMoCallEndNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_DATA_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_DATA_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_DATA_CALL_END_NTF;


    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCfreqLockNtf
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

  2.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �޸�HSD�ӿ�

*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf
)
{
    VOS_UINT32                          ulRet;
    MSCC_HSD_CFREQ_LOCK_NTF_STRU       *pstMsg = VOS_NULL_PTR;


    pstMsg = (MSCC_HSD_CFREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_CFREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCfreqLockNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_CFREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_CFREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_CFREQLOCK_NTF;

    pstMsg->enFreqLockMode               = pstCfreqLockNtf->enFreqLockMode;
    pstMsg->usHrpdBandClass              = pstCfreqLockNtf->usHrpdBandClass;
    pstMsg->usHrpdFreq                   = pstCfreqLockNtf->usHrpdFreq;
    pstMsg->usHrpdPn                     = pstCfreqLockNtf->usHrpdPn;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    
    ulRet = PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCfreqLockNtf:ERROR:PS_SEND_MSG FAILURE!");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndHsdCdmacsqSetReq
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
VOS_VOID NAS_MSCC_SndHsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
)
{
    /*VOS_UINT32                          ulRet;
    MMA_MSCC_CDMACSQ_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;


    pstMsg = (MSCC_XSD_CDMACSQ_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmacsqSetReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    PS_MEM_CPY((VOS_INT8*)pstMsg, (VOS_INT8*)pstCdmacsqSetReq, sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_CDMACSQ_SET_REQ;


    ulRet = PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdCdmacsqSetReq:ERROR:PS_SEND_MSG FAILURE!");
    }
    */

}


VOS_VOID NAS_MSCC_SndHsdSysAcqReq(
    MSCC_HSD_ACQUIRE_REASON_ENUM_UINT32 enAcqReason,
    VOS_UINT8                           ucHighPrioHrpdNum,
    VOS_VOID                           *pucHighPrioHrpdList
)
{
    MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdSysAcqReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ;

    /* Modified by y00307564 for CDMA Iteration 10, 2015-4-7, begin */
    pstMsg->enReason                     = enAcqReason;

    if ((MSCC_HSD_ACQUIRE_REASON_HIGH_PRIORITY == enAcqReason)
     && (0                                     < ucHighPrioHrpdNum))
    {
        pstMsg->ucFreqNum = ucHighPrioHrpdNum;

        PS_MEM_CPY(&(pstMsg->astFreqInfo[0]), pucHighPrioHrpdList, sizeof(MSCC_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU) * ucHighPrioHrpdNum);
    }
    /* Modified by y00307564 for CDMA Iteration 10, 2015-4-7, end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndHsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
)
{
    MSCC_HSD_SYS_CFG_REQ_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT16                          i;

    /* Allocate the memory for Message */
    pstMsg = (MSCC_HSD_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_SYS_CFG_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdSysCfgReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_SYS_CFG_REQ;
    pstMsg->ucSuppRatNum                 = pstSysCfgReq->stRatPrioList.ucRatNum;
    pstMsg->stCdmaBand                   = pstSysCfgReq->stBand.unCdmaBand.stCdmaBitBand;

    for (i = 0; i < pstSysCfgReq->stRatPrioList.ucRatNum; i++)
    {
        pstMsg->aenRatMode[i]            = NAS_MSCC_TransferMsccToVosRat(pstSysCfgReq->stRatPrioList.aucRatPrio[i]);
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* send the system config request to HSD */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/* Added for CDMA Iteration 10 2015-5-4 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsd1xSysChgInd
Description     :   Send the message to HSD

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-04
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsd1xSysChgInd(
    VOS_UINT8                           ucIs1xAvail,
    MSCC_HSD_1X_SYS_INFO_STRU          *pst1xSysInfo
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
              sizeof(MSCC_HSD_1X_SYS_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsd1xSysChgInd:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_HSD_1X_SYS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_1X_SYS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_1X_SYS_CHANGE_IND;

    pstMsg->ucIs1xAvail                  = ucIs1xAvail;
    PS_MEM_CPY(&pstMsg->st1xSysInfo, pst1xSysInfo, sizeof(MSCC_HSD_1X_SYS_INFO_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdPowerSaveReq
Description     :   Send the message to HSD

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-04
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdPowerSaveReq(VOS_VOID)
{
    MSCC_HSD_POWER_SAVE_REQ_STRU    *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_POWER_SAVE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
              sizeof(MSCC_HSD_POWER_SAVE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdPowerSaveReg:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_HSD_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_POWER_SAVE_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/* Added by m00312079 for CDMA Iteration 10 2015-4-4 end */
/* Added by x00314862 for CDMA Iteration 10 2015-4-3 begin */
/*****************************************************************************
Input parameters:   VOS_RATMODE_ENUM_UINT32             enRatMode
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-03
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
)
{
    MSCC_HSD_BG_SEARCH_REQ_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_BG_SEARCH_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdBgSearchReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_BG_SEARCH_REQ;

    pstMsg->enRatMode                    = enRatMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


/*****************************************************************************
Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-03
        Author  :   x00314862
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdStopBgSearchReq(VOS_VOID)
{
    MSCC_HSD_STOP_BG_SEARCH_REQ_STRU                    *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_STOP_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_STOP_BG_SEARCH_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdStopBgSearchReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_STOP_BG_SEARCH_REQ;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}



/* Added by x00314862 for CDMA Iteration 10 2015-4-3 end */


/* Added by y00307564 for CDMA Iteration 10 2015-4-3 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdQryHrpdSysInfoReq
Description     :   MSCC send msg to hsd qry sys info

Input parameters:   NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType,
                    VOS_UINT8                                               ucHrpdSysNum,
                    MSCC_MMC_HRPD_SYS_STRU                                 *pstHrpdSysList

Outout parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-04-03
    Author         : y00307564
    Modify content : Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdQryHrpdSysInfoReq(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType,
    VOS_UINT8                                               ucHrpdSysNum,
    MSCC_MMC_HRPD_SYS_STRU                                 *pstHrpdSysList
)
{
    MSCC_HSD_SYS_TYPE_ENUM_UINT8                            enSysType;
    MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU                    *pstMsccQryHrpdSysInfoReq = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstMsccQryHrpdSysInfoReq = (MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsccQryHrpdSysInfoReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdQryHrpdSysInfoReq ERROR:Memory Alloc Error for pstMsccQryHrpdSysInfoReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsccQryHrpdSysInfoReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulReceiverPid     = UEPS_PID_HSD;
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulLength          = sizeof(MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsccQryHrpdSysInfoReq->stMsgHeader.ulMsgName         = ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ;

    /* �����Ϣ���� */
    if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == enDestBsrSysType)
    {
        enSysType = MSCC_HSD_SYS_TYPE_CDMA2000_AI;
    }
    else if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == enDestBsrSysType)
    {
        enSysType = MSCC_HSD_SYS_TYPE_CDMA2000_HRPD;
    }
    else
    {
        enSysType = MSCC_HSD_SYS_TYPE_ENUM_BUTT;
    }

    pstMsccQryHrpdSysInfoReq->enSysType     = enSysType;
    pstMsccQryHrpdSysInfoReq->ucHrpdSysNum  = NAS_COMM_MIN(MSCC_MMC_BG_HRPD_MAX_SYS_NUM, ucHrpdSysNum);
    PS_MEM_CPY(pstMsccQryHrpdSysInfoReq->astHrpdSysList, pstHrpdSysList, sizeof(MSCC_MMC_HRPD_SYS_STRU) * ucHrpdSysNum);

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsccQryHrpdSysInfoReq);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsccQryHrpdSysInfoReq);

}
/* Added by y00307564 for CDMA Iteration 10 2015-4-3 end */

/* Added by m00312079 for CDMA Iteration 10 2015-4-4 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_SndHsdDisableLteNtf
Description     :   Send the message to HSD

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-04-04
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdDisableLteNtf(VOS_VOID)
{
    MSCC_HSD_DISABLE_LTE_NTF_STRU      *pstMsg = VOS_NULL_PTR;

    /* Allocate memory to send message  */
    pstMsg = (MSCC_HSD_DISABLE_LTE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC,
              sizeof(MSCC_HSD_DISABLE_LTE_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdDisableLteNtf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_HSD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_DISABLE_LTE_NTF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Send Message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndHsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
)
{
    MSCC_HSD_SRV_ACQ_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_HSD_SRV_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_SRV_ACQ_REQ;
    pstMsg->enSrvType                    = pstSrvAcqReq->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndHsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
)
{
    MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdBeginSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_BEGIN_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstBeginSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndHsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
)
{
    MSCC_HSD_END_SESSION_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_HSD_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_HSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndHsdEndSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_HSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_HSD_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_HSD_END_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstEndSessionNtf->enSrvType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



