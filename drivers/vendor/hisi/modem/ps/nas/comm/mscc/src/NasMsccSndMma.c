

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccSndMma.h"
#include "MmaMsccInterface.h"
#include "NasMntn.h"
#include "xsd_mscc_pif.h"
#include "NasComm.h"
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
#include "NasMsccCtx.h"
#include "NasMsccFsmBsrTbl.h"
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_MMA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaRssiInd
 ��������  : �����ź�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��30��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MSCC_SndMmaRssiInd(MMC_MSCC_RSSI_IND_STRU *pstMsg)

{
    MSCC_MMA_RSSI_IND_STRU              *pstRssiInfoInd      = VOS_NULL_PTR;


    pstRssiInfoInd = (MSCC_MMA_RSSI_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                         sizeof(MSCC_MMA_RSSI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRssiInfoInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaRssiInd():ERROR:Memory Alloc Error for pstRssiInfoInd ");
        return;
    }

    PS_MEM_CPY(((VOS_UINT8*)pstRssiInfoInd), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_RSSI_IND_STRU));

    /* �����Ϣͷ */
    pstRssiInfoInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_RSSI_IND;
    pstRssiInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRssiInfoInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstRssiInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRssiInfoInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstRssiInfoInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_RSSI_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstRssiInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstRssiInfoInd);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaMmInfo
 ��������  : �ϱ������·���MM INFO��Ϣ�а����������Ϣ
 �������  : NAS_MM_INFO_IND_STRU *pstMmInfo - MM INFO�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �º�����

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaMmInfo(MMC_MSCC_MM_INFO_IND_STRU* pstMsg)
{
    MSCC_MMA_MM_INFO_IND_STRU           *pstMmInfoInd       = VOS_NULL_PTR;

    pstMmInfoInd = (MSCC_MMA_MM_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                         sizeof(MSCC_MMA_MM_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstMmInfoInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaMmInfo():ERROR:Memory Alloc Error for pstMmInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMmInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_MM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��MSCC_MMA_MM_INFO_IND_STRU��Ϣ��װ���� */
    PS_MEM_CPY(((VOS_UINT8*)pstMmInfoInd), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_MM_INFO_IND_STRU));

    /* �����Ϣͷ */
    pstMmInfoInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_MM_INFO_IND;
    pstMmInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMmInfoInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMmInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMmInfoInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstMmInfoInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_MM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMmInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstMmInfoInd);

    return;
}



VOS_VOID NAS_MSCC_SndMmaDataTranAttri(
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU   *pstMsg
)
{
    MSCC_MMA_DATATRAN_ATTRI_IND_STRU   *pstDataTransAttriInd = VOS_NULL_PTR;

    pstDataTransAttriInd = (MSCC_MMA_DATATRAN_ATTRI_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                               sizeof(MSCC_MMA_DATATRAN_ATTRI_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDataTransAttriInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaDataTranAttri():ERROR:Memory Alloc Error for pstDataTransAttriInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDataTransAttriInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_DATATRAN_ATTRI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDataTransAttriInd->enDataTranAttri             = pstMsg->enDataTranAttri;

    /* �����Ϣͷ */
    pstDataTransAttriInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_DATATRAN_ATTRI_IND;
    pstDataTransAttriInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDataTransAttriInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstDataTransAttriInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDataTransAttriInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstDataTransAttriInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_DATATRAN_ATTRI_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstDataTransAttriInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstDataTransAttriInd);

    return;
}
VOS_VOID NAS_MSCC_SndMmaImsVoiceCapInd(
    VOS_UINT8                           ucImsVoiceAvail
)
{
    MSCC_MMA_IMS_VOICE_CAP_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMA_IMS_VOICE_CAP_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaImsVoiceCapInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMA_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMA_IMS_VOICE_CAP_IND;
    pstMsg->ucAvail                    = ucImsVoiceAvail;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmaNetworkCapabilityInfoInd(
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU              *pstNwCapInfoInd
)
{
    MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaNetworkCapabilityInfoInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND;

    pstMsg->enLteCsCap                 = pstNwCapInfoInd->enLteCsCap;
    pstMsg->enNwEmcBsCap               = pstNwCapInfoInd->enNwEmcBsCap;
    pstMsg->enNwImsVoCap               = pstNwCapInfoInd->enNwImsVoCap;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmaRegResultInd(
    MMC_MSCC_REG_RESULT_IND_STRU       *pstMmcMsccRegResultInd
)
{
    MSCC_MMA_REG_RESULT_IND_STRU            *pstRegResultInd = VOS_NULL_PTR;

    pstRegResultInd = (MSCC_MMA_REG_RESULT_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                      sizeof(MSCC_MMA_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRegResultInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaRegResultInd():ERROR:Memory Alloc Error for pstStartCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRegResultInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstRegResultInd), (VOS_UINT8*)pstMmcMsccRegResultInd, sizeof(MSCC_MMA_REG_RESULT_IND_STRU));


    /* �����Ϣͷ */
    pstRegResultInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_REG_RESULT_IND;
    pstRegResultInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRegResultInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstRegResultInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRegResultInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstRegResultInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstRegResultInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstRegResultInd);

    return;

}
VOS_VOID NAS_MSCC_SndMma3gppSysInfoInd(
    MMC_MSCC_SYS_INFO_IND_STRU         *pstMmcMsccSysInfoInd
)
{
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU            *pstSysInfoInd = VOS_NULL_PTR;

    pstSysInfoInd = (MSCC_MMA_3GPP_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                      sizeof(MSCC_MMA_3GPP_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSysInfoInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMma3gppSysInfoInd():ERROR:Memory Alloc Error for pstStartCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSysInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_3GPP_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstSysInfoInd), (VOS_UINT8*)pstMmcMsccSysInfoInd, sizeof(MSCC_MMA_3GPP_SYS_INFO_IND_STRU));


    /* �����Ϣͷ */
    pstSysInfoInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_3GPP_SYS_INFO_IND;
    pstSysInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSysInfoInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSysInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSysInfoInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSysInfoInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_3GPP_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSysInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSysInfoInd);

    return;

}
VOS_VOID NAS_MSCC_SndMmaServiceStatusInd(
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstMmcMsccSrvStatusInd
)
{
    MSCC_MMA_SERVICE_STATUS_IND_STRU            *pstSrvStatusInd = VOS_NULL_PTR;

    pstSrvStatusInd = (MSCC_MMA_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                      sizeof(MSCC_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSrvStatusInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaServiceStatusInd():ERROR:Memory Alloc Error for pstStartCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSrvStatusInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstSrvStatusInd), (VOS_UINT8*)pstMmcMsccSrvStatusInd, sizeof(MSCC_MMA_SERVICE_STATUS_IND_STRU));


    /* �����Ϣͷ */
    pstSrvStatusInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_SERVICE_STATUS_IND;
    pstSrvStatusInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrvStatusInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSrvStatusInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrvStatusInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSrvStatusInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSrvStatusInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSrvStatusInd);

    return;

}
VOS_VOID NAS_MSCC_SndMmaSystemAcquireStartInd(
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType
)
{
    MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU                 *pstSystemAcquireStartInd = VOS_NULL_PTR;

    pstSystemAcquireStartInd = (MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSystemAcquireStartInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSystemAcquireStartInd():ERROR:Memory Alloc Error for pstPlmnSelRlstInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSystemAcquireStartInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSystemAcquireStartInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_SYSTEM_ACQUIRE_START_IND;
    pstSystemAcquireStartInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSystemAcquireStartInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSystemAcquireStartInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSystemAcquireStartInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSystemAcquireStartInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSystemAcquireStartInd->enSysType                     = enSysType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSystemAcquireStartInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSystemAcquireStartInd);

    return;
}


VOS_VOID NAS_MSCC_SndMmaDetachInd(
    MMC_MSCC_DETACH_IND_STRU           *pstMsg
)
{
    MSCC_MMA_DETACH_IND_STRU           *pstDetachInd   = VOS_NULL_PTR;


    pstDetachInd = (MSCC_MMA_DETACH_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                         sizeof(MSCC_MMA_DETACH_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDetachInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaDetachInd():ERROR:Memory Alloc Error for pstDetachInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDetachInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* �����Ϣͷ */
    pstDetachInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_DETACH_IND;
    pstDetachInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDetachInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstDetachInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDetachInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstDetachInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDetachInd->ulDetachCause               = pstMsg->ulDetachCause;
    pstDetachInd->enNetworkDetachType         = pstMsg->enNetworkDetachType;

    pstDetachInd->enCnDomainId                = pstMsg->enCnDomainId;
    pstDetachInd->enServiceStatus             = pstMsg->enServiceStatus;
    pstDetachInd->ucOriginalDetachCause       = pstMsg->ucOriginalDetachCause;
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstDetachInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstDetachInd);

}




VOS_VOID NAS_MSCC_SndMmaAttachCnf(
     MMC_MSCC_ATTACH_CNF_STRU          *pstMsg
)
{
    MSCC_MMA_ATTACH_CNF_STRU             *pstAttachCnf = VOS_NULL_PTR;

    pstAttachCnf = (MSCC_MMA_ATTACH_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_ATTACH_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstAttachCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaAttachCnf():ERROR:Memory Alloc Error for pstAttachCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAttachCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachCnf->enServiceStatus             = pstMsg->enServiceStatus;
    pstAttachCnf->enCnDomainId                = pstMsg->enCnDomainId;

    pstAttachCnf->stPlmnId                    = pstMsg->stPlmnId;

    pstAttachCnf->ulOpID                      = pstMsg->ulOpID;

    /* �����Ϣͷ */
    pstAttachCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_ATTACH_CNF;
    pstAttachCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAttachCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstAttachCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAttachCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstAttachCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstAttachCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstAttachCnf);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaDetachCnf
 ��������  : ����ԭ��D_MMC_DETACH_CNF�Ĺ�������
 �������  : VOS_UINT32  ulCnDomainId
             VOS_UINT32  ulServiceStatus
             VOS_UINT32  ulOpid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaDetachCnf(
    MMC_MSCC_DETACH_CNF_STRU           *pstMsg
)
{
    MSCC_MMA_DETACH_CNF_STRU            *pstDetachCnf = VOS_NULL_PTR;

    pstDetachCnf = (MSCC_MMA_DETACH_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_DETACH_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDetachCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaDetachCnf():ERROR:Memory Alloc Error for pstDetachCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDetachCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDetachCnf->enServiceStatus             = pstMsg->enServiceStatus;
    pstDetachCnf->enCnDomainId                = pstMsg->enCnDomainId;

    pstDetachCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_DETACH_CNF;
    pstDetachCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDetachCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstDetachCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDetachCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstDetachCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstDetachCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstDetachCnf);

    return;
}

VOS_VOID NAS_MSCC_SndMmaCoverageInd(
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pstMsg
)
{
    MSCC_MMA_COVERAGE_AREA_IND_STRU    *pstCoverageInd   = VOS_NULL_PTR;

    pstCoverageInd = (MSCC_MMA_COVERAGE_AREA_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                          sizeof(MSCC_MMA_COVERAGE_AREA_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCoverageInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCoverageInd():ERROR:Memory Alloc Error for pstCoverageInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCoverageInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_COVERAGE_AREA_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstCoverageInd), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_COVERAGE_AREA_IND_STRU));


    /* �����Ϣͷ */
    pstCoverageInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_COVERAGE_AREA_IND;
    pstCoverageInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCoverageInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCoverageInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCoverageInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCoverageInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_COVERAGE_AREA_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCoverageInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstCoverageInd);

    return;
}
VOS_UINT32 NAS_MSCC_SndMmaServRejRsltInd(
    MMC_MSCC_SERV_REJ_IND_STRU         * pstMsg
)
{
    MSCC_MMA_SERV_REJ_IND_STRU         *pstServReqRsltInd = VOS_NULL_PTR;

    pstServReqRsltInd = (MSCC_MMA_SERV_REJ_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstServReqRsltInd)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaServRejRsltInd():ERROR:Memory Alloc Error");
        return VOS_ERR;
    }
    PS_MEM_SET(((VOS_UINT8*)pstServReqRsltInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* �����Ϣͷ */
    pstServReqRsltInd->MsgHeader.ulMsgName        = ID_MSCC_MMA_SRV_REJ_IND;
    pstServReqRsltInd->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstServReqRsltInd->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstServReqRsltInd->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstServReqRsltInd->MsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstServReqRsltInd->MsgHeader.ulLength         = sizeof(MSCC_MMA_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����Ϣ */
    pstServReqRsltInd->enCnDomainId = pstMsg->enCnDomainId;;
    pstServReqRsltInd->usRejCause   = pstMsg->usRejCause;
    pstServReqRsltInd->ucOriginalRejCause         = pstMsg->ucOriginalRejCause;
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstServReqRsltInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstServReqRsltInd);

    return VOS_OK;
}
VOS_VOID NAS_MSCC_SndMmaUsimAuthFailInd(
    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU   *pstMsg
 )
{
    MSCC_MMA_USIM_AUTH_FAIL_IND_STRU    *pstUsimAuthFailInd       = VOS_NULL_PTR;

    pstUsimAuthFailInd = (MSCC_MMA_USIM_AUTH_FAIL_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstUsimAuthFailInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaUsimAuthFailInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstUsimAuthFailInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstUsimAuthFailInd), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_USIM_AUTH_FAIL_IND_STRU));


    /* �����Ϣͷ */
    pstUsimAuthFailInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_USIM_AUTH_FAIL_IND;
    pstUsimAuthFailInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstUsimAuthFailInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstUsimAuthFailInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstUsimAuthFailInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstUsimAuthFailInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstUsimAuthFailInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstUsimAuthFailInd);

    return;
}
VOS_VOID NAS_MSCC_SndMmaCsServiceConnStatusInd(
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
)
{
    MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU    *pstCsServiceConnStatusInd = VOS_NULL_PTR;

    pstCsServiceConnStatusInd = (MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCsServiceConnStatusInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCsServiceConnStatusInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsServiceConnStatusInd) + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstCsServiceConnStatusInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND;
    pstCsServiceConnStatusInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsServiceConnStatusInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCsServiceConnStatusInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsServiceConnStatusInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCsServiceConnStatusInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����Ϣ*/
    pstCsServiceConnStatusInd->ucCsServiceConnStatusFlag   = pstMsg->ucCsServiceConnStatusFlag;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCsServiceConnStatusInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstCsServiceConnStatusInd);

    return;
}






VOS_VOID NAS_MSCC_SndMmaSysCfgCnf(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32      ulSysCfgCnfRst
)
{
    MSCC_MMA_SYS_CFG_SET_CNF_STRU        *pstSyscfgSetCnf = VOS_NULL_PTR;

    pstSyscfgSetCnf = (MSCC_MMA_SYS_CFG_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                          sizeof(MSCC_MMA_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSyscfgSetCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSysCfgCnf():ERROR:Memory Alloc Error for pstSyscfgSetCnf ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSyscfgSetCnf + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MSCC_MMA_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSyscfgSetCnf->enRst                       = ulSysCfgCnfRst;

    /* �����Ϣͷ */
    pstSyscfgSetCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_SYS_CFG_CNF;
    pstSyscfgSetCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSyscfgSetCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSyscfgSetCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSyscfgSetCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSyscfgSetCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSyscfgSetCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSyscfgSetCnf);

    return;
}
VOS_VOID NAS_MSCC_SndMmaNetScanCnf(
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstMsg
)
{
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf       = VOS_NULL_PTR;

    pstNetScanCnf = (MSCC_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                          sizeof(MSCC_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstNetScanCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaNetScanCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstNetScanCnf) + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(MSCC_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH );

    PS_MEM_CPY((VOS_UINT8*)pstNetScanCnf, (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_NET_SCAN_CNF_STRU));

    /* �����Ϣͷ */
    pstNetScanCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_NET_SCAN_CNF;
    pstNetScanCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstNetScanCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstNetScanCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstNetScanCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstNetScanCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstNetScanCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstNetScanCnf);

    return;
}
VOS_VOID NAS_MSCC_SndMmaAbortNetScanCnf(
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstMsg
)
{
    MSCC_MMA_ABORT_NET_SCAN_CNF_STRU    *pstNetScanStopCnf   = VOS_NULL_PTR;

    pstNetScanStopCnf = (MSCC_MMA_ABORT_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                          sizeof(MSCC_MMA_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstNetScanStopCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaAbortNetScanCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstNetScanStopCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstNetScanStopCnf), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_ABORT_NET_SCAN_CNF_STRU));


    /* �����Ϣͷ */
    pstNetScanStopCnf->MsgHeader.ulMsgName                  = ID_MSCC_MMA_ABORT_NET_SCAN_CNF;
    pstNetScanStopCnf->MsgHeader.ulSenderCpuId              = VOS_LOCAL_CPUID;
    pstNetScanStopCnf->MsgHeader.ulSenderPid                = UEPS_PID_MSCC;
    pstNetScanStopCnf->MsgHeader.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    pstNetScanStopCnf->MsgHeader.ulReceiverPid              = WUEPS_PID_MMA;
    pstNetScanStopCnf->MsgHeader.ulLength                   = sizeof(MSCC_MMA_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstNetScanStopCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstNetScanStopCnf);

    return;
}





/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPlmnListAbortCnf
 ��������  : ��MMA����ID_MSCC_MMA_PLMN_LIST_ABORT_CNF��Ϣ
 �������  : usSearchPlmnNum �����б��б����PLMN ID����
             pstListInfo     �����б���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��2��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnListAbortCnf(
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU    *pstMmcPlmnListAbortCnf
)
{
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU    *pstPlmnListAbortCnf = VOS_NULL_PTR;

    pstPlmnListAbortCnf = (MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstPlmnListAbortCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnListAbortCnf():ERROR:Memory Alloc Error for pstPlmnListAbortCnf ");
        return;
    }


    /* �����Ϣͷ */
    PS_MEM_SET(((VOS_UINT8*)pstPlmnListAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstPlmnListAbortCnf), (VOS_UINT8*)pstMmcPlmnListAbortCnf, sizeof(MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU));

    pstPlmnListAbortCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_PLMN_LIST_ABORT_CNF;
    pstPlmnListAbortCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListAbortCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPlmnListAbortCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnListAbortCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstPlmnListAbortCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnListAbortCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnListAbortCnf);
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf
 ��������  : ��MMA����MMA_MMC_SPEC_PLMN_SEARCH_ABORT_CNF��Ϣ
 �������  : pstSndMmaMsg - MMA_MMC_SPEC_PLMN_SEARCH_ABORT_CNF��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��2��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf(
    MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU               *pstMsg
)
{
    /* ��MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU��װ��Ϣ������ */
    MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU                *pstSpecPlmnSrchAbortCnf = VOS_NULL_PTR;

    pstSpecPlmnSrchAbortCnf = (MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                  sizeof(MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSpecPlmnSrchAbortCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf():ERROR:Memory Alloc Error for pstSpecPlmnSrchAbortCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSpecPlmnSrchAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulMsgName            = ID_MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulSenderPid          = UEPS_PID_MSCC;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulReceiverPid        = WUEPS_PID_MMA;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulLength             = sizeof(MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSpecPlmnSrchAbortCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSpecPlmnSrchAbortCnf);

    return;

}


VOS_VOID NAS_MSCC_SndMmaAcInfoChangeInd(
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU  *pstMsg
)
{
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChgInd = VOS_NULL_PTR;

    pstAcInfoChgInd = (MSCC_MMA_AC_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                         sizeof(MSCC_MMA_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstAcInfoChgInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaAcInfoChangeInd():ERROR:Memory Alloc Error for pstAcInfoChgInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcInfoChgInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstAcInfoChgInd), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_AC_INFO_CHANGE_IND_STRU));


    /* �����Ϣͷ */
    pstAcInfoChgInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_AC_INFO_CHANGE_IND;
    pstAcInfoChgInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcInfoChgInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstAcInfoChgInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcInfoChgInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstAcInfoChgInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstAcInfoChgInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstAcInfoChgInd);

    return;
}
VOS_VOID NAS_MSCC_SndMmaEplmnInfoInd(
    MMC_MSCC_EPLMN_INFO_IND_STRU       *pstMsg
)
{
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoInd = VOS_NULL_PTR;

    pstEplmnInfoInd = (MSCC_MMA_EPLMN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                          sizeof(MSCC_MMA_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEplmnInfoInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaEplmnInfoInd():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstEplmnInfoInd) + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(MSCC_MMA_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH );
    PS_MEM_CPY(pstEplmnInfoInd, pstMsg, sizeof(MSCC_MMA_EPLMN_INFO_IND_STRU));

    /* �����Ϣͷ */
    pstEplmnInfoInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_EPLMN_INFO_IND;
    pstEplmnInfoInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEplmnInfoInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstEplmnInfoInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEplmnInfoInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstEplmnInfoInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstEplmnInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstEplmnInfoInd);

    return;
}
VOS_VOID NAS_MSCC_SndMmaEOPlmnSetCnf(
    MMC_MSCC_EOPLMN_SET_CNF_STRU       *pstMsg
)
{
    MSCC_MMA_EOPLMN_SET_CNF_STRU       *pstSPlmnSetCnf = VOS_NULL_PTR;

    pstSPlmnSetCnf = (MSCC_MMA_EOPLMN_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSPlmnSetCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaEOPlmnSetCnf():ERROR:Memory Alloc Error for pstSPlmnSetCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSPlmnSetCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstSPlmnSetCnf->ulResult                    = pstMsg->ulResult;

    pstSPlmnSetCnf->MsgHeader.ulMsgName         = ID_MSCC_MMA_EOPLMN_SET_CNF;
    pstSPlmnSetCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSPlmnSetCnf->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSPlmnSetCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSPlmnSetCnf->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSPlmnSetCnf->MsgHeader.ulLength          = sizeof(MSCC_MMA_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSPlmnSetCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstSPlmnSetCnf);

    return;

}


VOS_VOID NAS_MSCC_SndMmaCampOnInd(
    MMC_MSCC_CAMP_ON_IND_STRU_STRU     *pstMsg
)
{
    MSCC_MMA_CAMP_ON_IND_STRU_STRU     *pstCampOnInd       = VOS_NULL_PTR;

    pstCampOnInd = (MSCC_MMA_CAMP_ON_IND_STRU_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCampOnInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCampOnInd():ERROR:Memory Alloc Error for pstCampOnInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCampOnInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstCampOnInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_CAMP_ON_IND;
    pstCampOnInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCampOnInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCampOnInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCampOnInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCampOnInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCampOnInd->ucCampOnFlg                 = pstMsg->ucCampOnFlg;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCampOnInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstCampOnInd);

    return;
}



/*****************************************************************************
  �� �� ��  : NAS_MSCC_SndMmaWCipherInfo
  ��������  : ����ID_MSCC_MMA_UMTS_CIPHER_INFO_IND��Ϣ
  �������  : MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU               *pstMsg
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaWCipherInfo(
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU *pstMsg)
{
    MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU *pstWCipherInfo       = VOS_NULL_PTR;

    pstWCipherInfo = (MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstWCipherInfo )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCampOnInd():ERROR:Memory Alloc Error for pstCampOnInd ");
        return;
    }

    PS_MEM_CPY(((VOS_UINT8*)pstWCipherInfo), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU));


    /* �����Ϣͷ */
    pstWCipherInfo->MsgHeader.ulMsgName         = ID_MSCC_MMA_UMTS_CIPHER_INFO_IND;
    pstWCipherInfo->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstWCipherInfo->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstWCipherInfo->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstWCipherInfo->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstWCipherInfo->MsgHeader.ulLength          = sizeof(MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstWCipherInfo);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstWCipherInfo);

    return;
}


/*****************************************************************************
  �� �� ��  : NAS_MSCC_SndMmaGCipherInfo
  ��������  : ����ID_MSCC_MMA_GPRS_CIPHER_INFO_IND��Ϣ
  �������  : MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU               *pstMsg
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaGCipherInfo(
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU *pstMsg
)
{
    MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU *pstGCipherInfo       = VOS_NULL_PTR;

    pstGCipherInfo = (MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstGCipherInfo )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCampOnInd():ERROR:Memory Alloc Error for pstCampOnInd ");
        return;
    }

    PS_MEM_CPY(((VOS_UINT8*)pstGCipherInfo), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU));


    /* �����Ϣͷ */
    pstGCipherInfo->MsgHeader.ulMsgName         = ID_MSCC_MMA_GPRS_CIPHER_INFO_IND;
    pstGCipherInfo->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstGCipherInfo->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstGCipherInfo->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstGCipherInfo->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstGCipherInfo->MsgHeader.ulLength          = sizeof(MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstGCipherInfo);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstGCipherInfo);

    return;
}
VOS_VOID NAS_MSCC_SndMmaAcqCnf(
    MMC_MSCC_ACQ_CNF_STRU              *pstMsg
)
{
    MSCC_MMA_ACQ_CNF_STRU               *pstAcqCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstAcqCnf = (MSCC_MMA_ACQ_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAcqCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaAcqCnf():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcqCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcqCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcqCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstAcqCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAcqCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_ACQ_CNF;

    /* �����Ϣ���� */
    pstAcqCnf->enAcqRslt                     = pstMsg->enAcqRslt;
    pstAcqCnf->ulArfcn                       = pstMsg->ulArfcn;
    pstAcqCnf->stPlmnId.ulMcc                = pstMsg->stPlmnId.ulMcc;
    pstAcqCnf->stPlmnId.ulMnc                = pstMsg->stPlmnId.ulMnc;
    pstAcqCnf->enPrioClass                   = pstMsg->enPrioClass;

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstAcqCnf);

    return;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  �� �� ��  : NAS_MSCC_SndMmaAcqInd
  ��������  : ����AcqInd��Ϣ
  �������  : MMC_MSCC_ACQ_IND_STRU               *pstMsg
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaAcqInd(
    MMC_MSCC_ACQ_IND_STRU               *pstMsg
)
{
    MSCC_MMA_ACQ_IND_STRU               *pstAcqInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstAcqInd = (MSCC_MMA_ACQ_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAcqInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaAcqInd():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcqInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstAcqInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcqInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstAcqInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcqInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstAcqInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAcqInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_ACQ_IND;

    /* �����Ϣ���� */
    pstAcqInd->enAcqRslt                     = pstMsg->enAcqRslt;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstAcqInd->ulArfcn                       = pstMsg->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    pstAcqInd->stPlmnId.ulMcc                = pstMsg->stPlmnId.ulMcc;
    pstAcqInd->stPlmnId.ulMnc                = pstMsg->stPlmnId.ulMnc ;
    pstAcqInd->enPrioClass                   = pstMsg->enPrioClass;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstAcqInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstAcqInd);

    return;
}
#endif


VOS_VOID NAS_MSCC_SndMmaRegCnf(
    MMC_MSCC_REG_CNF_STRU              *pstMsg
)
{
    MSCC_MMA_REG_CNF_STRU              *pstRegCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstRegCnf = (MSCC_MMA_REG_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRegCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaRegCnf():ERROR:Memory Alloc Error for pstRegCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRegCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstRegCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRegCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstRegCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRegCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstRegCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRegCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_REG_CNF;

    /* �����Ϣ���� */
    pstRegCnf->enRegRslt                     = pstMsg->enRegRslt;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstRegCnf->ulArfcn                       = pstMsg->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    pstRegCnf->stPlmnId.ulMcc                = pstMsg->stPlmnId.ulMcc;
    pstRegCnf->stPlmnId.ulMnc                = pstMsg->stPlmnId.ulMnc;
    pstRegCnf->enPrioClass                   = pstMsg->enPrioClass;
    pstRegCnf->enLmmAttachClRegStatus        = pstMsg->enLmmAttachClRegStatus;
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstRegCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstRegCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPowerSaveCnf
 ��������  : ��MMA����PowerSaveCnf
 �������  : MMC_MSCC_POWER_SAVE_CNF_STRU       *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPowerSaveCnf(
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstMsg
)
{
    MSCC_MMA_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPowerSaveCnf = (MSCC_MMA_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPowerSaveCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPowerSaveCnf():ERROR:Memory Alloc Error for pstPowerSaveCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPowerSaveCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPowerSaveCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPowerSaveCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstPowerSaveCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPowerSaveCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_POWER_SAVE_CNF;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPowerSaveCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPowerSaveCnf);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPsServiceConnStatusInd
 ��������  : ��MMA����psҵ����������״̬��Ϣ
 �������  : MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPsServiceConnStatusInd(
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
)
{
    MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU               *pstPsServiceConnStatusInd = VOS_NULL_PTR;

    pstPsServiceConnStatusInd = (MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPsServiceConnStatusInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCsServiceConnStatusInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPsServiceConnStatusInd) + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPsServiceConnStatusInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND;
    pstPsServiceConnStatusInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPsServiceConnStatusInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPsServiceConnStatusInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPsServiceConnStatusInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstPsServiceConnStatusInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����Ϣ*/
    pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag     = pstMsg->ucPsServiceConnStatusFlag;
    pstPsServiceConnStatusInd->enPsSigType                   = pstMsg->enPsSigType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPsServiceConnStatusInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPsServiceConnStatusInd);

    return;
}

/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaRfAvailInd
 ��������  : ��MMA����MmaPlmnListCnf
 �������  : MMC_MSCC_RF_AVAILABLE_IND_STRU      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaRfAvailInd(
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *pstMsg
)
{
    /* ��MSCC_MMA_AREA_LOST_NO_RF_STATUS_IND_STRU��Ϣ�����װ */
    MSCC_MMA_RF_AVAILABLE_IND_STRU      *pstRfAvailInd = VOS_NULL_PTR;

    pstRfAvailInd = (MSCC_MMA_RF_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_RF_AVAILABLE_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRfAvailInd )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaRfAvailInd():ERROR:Memory Alloc Error for pstServiceStatusInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRfAvailInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstRfAvailInd->stMsgHeader.ulMsgName           = ID_MSCC_MMA_RF_AVAILABLE_IND;
    pstRfAvailInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstRfAvailInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstRfAvailInd->stMsgHeader.ulLength            = sizeof(MSCC_MMA_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRfAvailInd->ucRfAvailFlg                    = pstMsg->ucRfAvailFlg;;
    pstRfAvailInd->enRatType                       = pstMsg->enRatType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstRfAvailInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstRfAvailInd);

    return;
}
/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, end */


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaRfAvailInd
 ��������  : ��MMA����MmaPlmnListCnf
 �������  : MMC_MSCC_PLMN_LIST_CNF_STRU        *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnListCnf(
    MMC_MSCC_PLMN_LIST_CNF_STRU        *pstMsg
)
{
    MSCC_MMA_PLMN_LIST_CNF_STRU      *pstPlmnListCnf = VOS_NULL_PTR;

    pstPlmnListCnf = (MSCC_MMA_PLMN_LIST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_LIST_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnListCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnListCnf():ERROR:Memory Alloc Error for pstServiceStatusInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnListCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstPlmnListCnf), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_PLMN_LIST_CNF_STRU));


    /* �����Ϣͷ */
    pstPlmnListCnf->MsgHeader.ulMsgName           = ID_MSCC_MMA_PLMN_LIST_CNF;
    pstPlmnListCnf->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPlmnListCnf->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstPlmnListCnf->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListCnf->MsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstPlmnListCnf->MsgHeader.ulLength            = sizeof(MSCC_MMA_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnListCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnListCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaSrchedPlmnInfo
 ��������  : ��MMA����SrchedPlmnInfo
 �������  : MMC_MSCC_PLMN_LIST_CNF_STRU        *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaSrchedPlmnInfo(
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU                     *pstMsg
)
{
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU                     *pstSrchedPlmnInfo = VOS_NULL_PTR;
    pstSrchedPlmnInfo = (MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSrchedPlmnInfo )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSrchedPlmnInfo():ERROR:Memory Alloc Error for pstSrchedPlmnInfo ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSrchedPlmnInfo) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstSrchedPlmnInfo), (VOS_UINT8*)pstMsg, sizeof(MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU));


    /* �����Ϣͷ */
    pstSrchedPlmnInfo->stMsgHeader.ulMsgName           = ID_MSCC_MMA_SRCHED_PLMN_INFO_IND;
    pstSrchedPlmnInfo->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSrchedPlmnInfo->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstSrchedPlmnInfo->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSrchedPlmnInfo->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstSrchedPlmnInfo->stMsgHeader.ulLength            = sizeof(MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSrchedPlmnInfo);
    PS_SEND_MSG(UEPS_PID_MSCC, pstSrchedPlmnInfo);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPlmnListRej
 ��������  : ��MMA����PlmnLIstRej
 �������  : MMC_MSCC_PLMN_LIST_REJ_STRU        *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnListRej(
    MMC_MSCC_PLMN_LIST_REJ_STRU        *pstMsg
)
{
    MSCC_MMA_PLMN_LIST_REJ_STRU      *pstPlmnListRej = VOS_NULL_PTR;

    pstPlmnListRej = (MSCC_MMA_PLMN_LIST_REJ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_LIST_REJ_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnListRej )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnListRej():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnListRej) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH);


    /* �����Ϣͷ */
    pstPlmnListRej->MsgHeader.ulMsgName           = ID_MSCC_MMA_PLMN_LIST_REJ;
    pstPlmnListRej->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPlmnListRej->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstPlmnListRej->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListRej->MsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstPlmnListRej->MsgHeader.ulLength            = sizeof(MSCC_MMA_PLMN_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnListRej);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnListRej);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPlmnSpecialSelCnf
 ��������  : ��MMA����PlmnSpecialSelCnf
 �������  : MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU  *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelCnf(
   MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU  *pstMsg
)
{
    MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU      *pstPlmnSpecialSelCnf = VOS_NULL_PTR;

    pstPlmnSpecialSelCnf = (MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnSpecialSelCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnSpecialSelCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnSpecialSelCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPlmnSpecialSelCnf->enResult = pstMsg->enResult;
    /* �����Ϣͷ */
    pstPlmnSpecialSelCnf->MsgHeader.ulMsgName           = ID_MSCC_MMA_PLMN_SPECIAL_SEL_CNF;
    pstPlmnSpecialSelCnf->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPlmnSpecialSelCnf->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstPlmnSpecialSelCnf->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPlmnSpecialSelCnf->MsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstPlmnSpecialSelCnf->MsgHeader.ulLength            = sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnSpecialSelCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnSpecialSelCnf);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPlmnSpecialSelRej_PreProc
 ��������  : ��MMA����PlmnSpecialSelRej
 �������  : MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU   *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelRej(
  MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU   *pstMsg
)
{
    MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU      *pstPlmnSpecialSelRej = VOS_NULL_PTR;

    pstPlmnSpecialSelRej = (MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnSpecialSelRej )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnSpecialSelRej():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnSpecialSelRej) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU) - VOS_MSG_HEAD_LENGTH);


    /* �����Ϣͷ */
    pstPlmnSpecialSelRej->MsgHeader.ulMsgName           = ID_MSCC_MMA_PLMN_SPECIAL_SEL_REJ;
    pstPlmnSpecialSelRej->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPlmnSpecialSelRej->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstPlmnSpecialSelRej->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPlmnSpecialSelRej->MsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstPlmnSpecialSelRej->MsgHeader.ulLength            = sizeof(MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnSpecialSelRej);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnSpecialSelRej);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPlmnReselCnf_PreProc
 ��������  : ��MMA����PlmnReselCnf
 �������  : MMC_MSCC_PLMN_RESEL_CNF_STRU         *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPlmnReselCnf(
  MMC_MSCC_PLMN_RESEL_CNF_STRU         *pstMsg
)
{
    MSCC_MMA_PLMN_RESEL_CNF_STRU      *pstPlmnReselCnf = VOS_NULL_PTR;

    pstPlmnReselCnf = (MSCC_MMA_PLMN_RESEL_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                              sizeof(MSCC_MMA_PLMN_RESEL_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnReselCnf )
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPlmnReselCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnReselCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PLMN_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPlmnReselCnf->enResult = pstMsg->enResult;
    /* �����Ϣͷ */
    pstPlmnReselCnf->MsgHeader.ulMsgName           = ID_MSCC_MMA_PLMN_RESEL_CNF;
    pstPlmnReselCnf->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPlmnReselCnf->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstPlmnReselCnf->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPlmnReselCnf->MsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstPlmnReselCnf->MsgHeader.ulLength            = sizeof(MSCC_MMA_PLMN_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnReselCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnReselCnf);

    return;
}
VOS_VOID NAS_MSCC_SndMmaGetGeoCnf(
    MMC_MSCC_GET_GEO_CNF_STRU          *pstMsg
)
{
    MSCC_MMA_GET_GEO_CNF_STRU          *pstSndMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstSndMsg = (MSCC_MMA_GET_GEO_CNF_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMA_GET_GEO_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaGetGeoCnf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* �����Ϣ���� */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* ��д��Ϣͷ */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMA, ID_MSCC_MMA_GET_GEO_CNF);

    /* ��д��Ϣ���� */
    /* PLMN ID */
    PS_MEM_CPY(&(pstSndMsg->stPlmnId), &(pstMsg->stPlmnId), sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;

}


VOS_VOID NAS_MSCC_SndMmaStopGetGeoCnf(
    MMC_MSCC_STOP_GET_GEO_CNF_STRU     *pstMsg
)
{
    MSCC_MMA_STOP_GET_GEO_CNF_STRU     *pstSndMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstSndMsg = (MSCC_MMA_STOP_GET_GEO_CNF_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMA_STOP_GET_GEO_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaStopGetGeoCnf:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* �����Ϣ���� */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* ��д��Ϣͷ */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMA, ID_MSCC_MMA_STOP_GET_GEO_CNF);

    /* ��д��Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;

}
VOS_VOID NAS_MSCC_SndMmaSrvAcqCnf(
    MMC_MSCC_SRV_ACQ_CNF_STRU          *pstMsg
)
{
    MSCC_MMA_SRV_ACQ_CNF_STRU          *pstSrvAcqCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstSrvAcqCnf = (MSCC_MMA_SRV_ACQ_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSrvAcqCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MMC_SndMmaSrvAcqCnf():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSrvAcqCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSrvAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSrvAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSrvAcqCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSrvAcqCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_SRV_ACQ_CNF;

    /* �����Ϣ���� */
    pstSrvAcqCnf->enResult                      = pstMsg->enResult;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSrvAcqCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSrvAcqCnf);

    return;
}




VOS_VOID NAS_MSCC_SndMmaSwitchOnRsltCnf(
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulRslt
)
{
    MSCC_MMA_START_CNF_STRU             *pstMsg = VOS_NULL_PTR;

    /* Alloc memory for start cnf structure  */
    pstMsg = (MSCC_MMA_START_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSwitchOnRsltCnf: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMA_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMA_START_CNF;
    pstMsg->ulResult                   = ulRslt;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Sending the message using VOS */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("start result=%d", ulRslt);

    return;

}




VOS_VOID NAS_MSCC_SndMmaPowerOffRsltCnf(VOS_VOID)
{
    MSCC_MMA_POWER_OFF_CNF_STRU         *pstMsg = VOS_NULL_PTR;

    /* Alloc memory for start cnf structure  */
    pstMsg = (MSCC_MMA_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPowerOffRsltCnf: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMA_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMA_POWER_OFF_CNF;

     /* Sending the message using VOS */

     /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
     NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
     /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;

}


VOS_VOID NAS_MSCC_SndMmaSystemAcquireEndInd(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult,
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType
)
{
    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU                   *pstMsg = VOS_NULL_PTR;

    /* Alloc memory for System acquire cnf structure  */
    pstMsg = (MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSystemAcqireEndInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMA_SYSTEM_ACQUIRE_END_IND;
    pstMsg->enResult                     = enResult;
    pstMsg->enAcqSysType                 = enAcqSysType;

    pstMsg->enAcqRsltType                = enAcqRsltType;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* Sending the message using VOS */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;

}


/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
VOS_VOID NAS_MSCC_SndMmaHrpdServiceStatusInd(
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enHrpdSrvSta,
    VOS_UINT8                                               ucIsNewSession,
    VOS_UINT8                                               ucIsEhrpdSupport,
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType
)
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */
{
    MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU                  *pstMsg = VOS_NULL_PTR;

    /* Alloc memory for start cnf structure  */
    pstMsg = (MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaHrpdServiceStatusInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMA_HRPD_SERVICE_STATUS_IND;
    pstMsg->enSrvSta                     = enHrpdSrvSta;
    pstMsg->ucIsNewSession               = ucIsNewSession;
    /* Add by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
    pstMsg->ucIsEhrpdSupport             = ucIsEhrpdSupport;
    /* Add by l00324781 for CDMA Iteration 12, 2015-5-30, end */

    /* Added by m00312079 for CDMA Iteration 12 2015-6-2 begin */
    pstMsg->enCurrSessionRelType         = enCurrSessionRelType;
    /* Added by m00312079 for CDMA Iteration 12 2015-6-2 end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* invoke VOS sending msg primitive */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);
}


VOS_VOID NAS_MSCC_SndMmaHrpdOverheadMsgInd(
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstMsccOhmMsg
)
{
    MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU                    *pstMsg = VOS_NULL_PTR;

    /* Alloc memory for start cnf structure  */
    pstMsg = (MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
              sizeof(MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaHrpdServiceStatusInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND;

    pstMsg->usBandClass                  = pstMsccOhmMsg->usBandClass;
    pstMsg->usFreq                       = pstMsccOhmMsg->usFreq;
    pstMsg->ulMcc                        = pstMsccOhmMsg->ulMcc;
    pstMsg->ucUATIColorCode              = pstMsccOhmMsg->ucUATIColorCode;
    pstMsg->ucSubNetMask                 = pstMsccOhmMsg->ucSubNetMask;
    pstMsg->ucSecondaryColorCodeCount    = pstMsccOhmMsg->ucSecondaryColorCodeCount;
    pstMsg->lLongitude                   = pstMsccOhmMsg->lLongitude;
    pstMsg->lLatitude                    = pstMsccOhmMsg->lLatitude;
    pstMsg->ulSector24                   = pstMsccOhmMsg->ulSector24;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* invoke VOS sending msg primitive */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaCFPlmnSetCnf
 ��������  : ��MMA����confirm message
 �������  : MMC_MSCC_CFPLMN_SET_CNF_STRU         *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��05��
   ��    ��   : f0279542
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaCFPlmnSetCnf(
    MMC_MSCC_CFPLMN_SET_CNF_STRU       *pstMsg
)
{
    MSCC_MMA_CFPLMN_SET_CNF_STRU       *pstFPlmnCnf = VOS_NULL_PTR;

    pstFPlmnCnf = (MSCC_MMA_CFPLMN_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                  sizeof(MSCC_MMA_CFPLMN_SET_CNF_STRU)- VOS_MSG_HEAD_LENGTH);
    if(VOS_NULL_PTR == pstFPlmnCnf)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCFPlmnSetCnf:ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstFPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstFPlmnCnf->stMsgHeader.ulMsgName           = ID_MSCC_MMA_CFPLMN_SET_CNF;
    pstFPlmnCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstFPlmnCnf->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstFPlmnCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstFPlmnCnf->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstFPlmnCnf->stMsgHeader.ulLength            = sizeof(MSCC_MMA_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstFPlmnCnf->enResult                        = pstMsg->enResult;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstFPlmnCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstFPlmnCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaCFPlmnQueryCnf
 ��������  : ��MMA����confirm message
 �������  : MMC_MSCC_CFPLMN_SET_CNF_STRU         *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��05��
   ��    ��   : f0279542
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaCFPlmnQueryCnf(
    MMC_MSCC_CFPLMN_QUERY_CNF_STRU     *pstMsg
)
{
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU     *pstFPlmnCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstFPlmnCnf = (MSCC_MMA_CFPLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                    sizeof(MSCC_MMA_CFPLMN_QUERY_CNF_STRU)- VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstFPlmnCnf)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCFPlmnQueryCnf:ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstFPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstFPlmnCnf->stMsgHeader.ulMsgName           = ID_MSCC_MMA_CFPLMN_QUERY_CNF;
    pstFPlmnCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstFPlmnCnf->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstFPlmnCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstFPlmnCnf->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMA;
    pstFPlmnCnf->stMsgHeader.ulLength            = sizeof(MSCC_MMA_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstFPlmnCnf->enResult                        = pstMsg->enResult;
    pstFPlmnCnf->ucPlmnNum                       = pstMsg->ucPlmnNum;

    if (pstFPlmnCnf->ucPlmnNum > NAS_MSCC_PIF_MAX_CFPLMN_NUM)
    {
        pstFPlmnCnf->ucPlmnNum = NAS_MSCC_PIF_MAX_CFPLMN_NUM;
    }

    for (ulLoop = 0; ulLoop < pstFPlmnCnf->ucPlmnNum; ulLoop++)
    {
        pstFPlmnCnf->astPlmn[ulLoop].ulMcc = pstMsg->astPlmn[ulLoop].ulMcc;
        pstFPlmnCnf->astPlmn[ulLoop].ulMnc = pstMsg->astPlmn[ulLoop].ulMnc;
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstFPlmnCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    PS_SEND_MSG(UEPS_PID_MSCC, pstFPlmnCnf);
    return;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPrefPlmnQueryCnf
 ��������  : ��MMA����PrefPlmnQueryCnf
 �������  : MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU  *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��05��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPrefPlmnQueryCnf(
    MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU  *pstMsg
)
{
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU  *pstPrefPlmnCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPrefPlmnCnf = (MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPrefPlmnQueryCnf ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPrefPlmnCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstPrefPlmnCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_PREF_PLMN_QUERY_CNF;

    /* �����Ϣ���� */
    pstPrefPlmnCnf->enCmdType                     = pstMsg->enCmdType;
    pstPrefPlmnCnf->usPlmnNum                     = pstMsg->usPlmnNum;
    pstPrefPlmnCnf->ulFromIndex                   = pstMsg->ulFromIndex;
    pstPrefPlmnCnf->ulValidPlmnNum                = pstMsg->ulValidPlmnNum;
    pstPrefPlmnCnf->enRslt                        = pstMsg->enRslt;

    PS_MEM_CPY(&(pstPrefPlmnCnf->stPlmnName), &(pstMsg->stPlmnName), sizeof(NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaPrefPlmnSetCnf
 ��������  : ��MMA����PrefPlmnSetCnf
 �������  : MMC_MSCC_PREF_PLMN_SET_CNF_STRU  *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��05��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaPrefPlmnSetCnf(
    MMC_MSCC_PREF_PLMN_SET_CNF_STRU  *pstMsg
)
{
    MSCC_MMA_PREF_PLMN_SET_CNF_STRU  *pstPrefPlmnCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstPrefPlmnCnf = (MSCC_MMA_PREF_PLMN_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaPrefPlmnSetCnf ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPrefPlmnCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstPrefPlmnCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_PREF_PLMN_SET_CNF;

    /* �����Ϣ���� */
    pstPrefPlmnCnf->enRslt                        = pstMsg->enRslt;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnCnf);

    return;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */

/* Added by x00314862 for CDMA Iteration 9 2015-2-11 begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaCdmacsqSetCnf
 ��������  : ��MMA����MSCC_MMA_CDMACSQ_SET_CNF
 �������  : XSD_MSCC_CDMACSQ_SET_CNF_STRU      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaCdmacsqSetCnf(
    XSD_MSCC_CDMACSQ_SET_CNF_STRU      *pstMsg
)
{
    MSCC_MMA_CDMACSQ_SET_CNF_STRU  *pstCdmacsqSetCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstCdmacsqSetCnf = (MSCC_MMA_CDMACSQ_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_CDMACSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCdmacsqSetCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCdmacsqSetCnf():ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCdmacsqSetCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_CDMACSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstCdmacsqSetCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCdmacsqSetCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCdmacsqSetCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCdmacsqSetCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCdmacsqSetCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_CDMACSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCdmacsqSetCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_CDMACSQ_SET_CNF;

    /* �����Ϣ���� */
    pstCdmacsqSetCnf->enRslt                        = pstMsg->enRslt;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCdmacsqSetCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstCdmacsqSetCnf);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaCdmacsqSignalQualityInd
 ��������  : ��MMA����MSCC_MMA_CDMACSQ_IND_STRU
 �������  : XSD_MSCC_CDMACSQ_IND_STRU      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaCdmacsqSignalQualityInd(
   XSD_MSCC_CDMACSQ_IND_STRU           *pstMsg
)
{
    MSCC_MMA_CDMACSQ_IND_STRU  *pstCdmacsqInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstCdmacsqInd = (MSCC_MMA_CDMACSQ_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_CDMACSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCdmacsqInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaCdmacsqSignalQualityInd():ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCdmacsqInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_CDMACSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstCdmacsqInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCdmacsqInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCdmacsqInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCdmacsqInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCdmacsqInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_CDMACSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCdmacsqInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND;

    /* �����Ϣ���� */
    pstCdmacsqInd->cCdmaRssi                     = pstMsg->cCdmaRssi;
    pstCdmacsqInd->cCdmaEcIo                     = pstMsg->cCdmaEcIo;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCdmacsqInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstCdmacsqInd);

}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMma1xSystemServiceInfoInd
 ��������  : ��MMA����MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND
 �������  : XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMma1xSystemServiceInfoInd(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                *pstMsg
)
{
    MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU  *pstSysSrvInfoInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstSysSrvInfoInd = (MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSysSrvInfoInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMma1xSystemServiceInfoInd():ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSysSrvInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstSysSrvInfoInd), pstMsg, sizeof(MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU));


    /* �����Ϣͷ */
    pstSysSrvInfoInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSysSrvInfoInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSysSrvInfoInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSysSrvInfoInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSysSrvInfoInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSysSrvInfoInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND;

    /* �����Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSysSrvInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSysSrvInfoInd);

}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMma1xSystemServiceInfoInd
 ��������  : ��MMA����MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU
 �������  : MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaLmmCellSignInfoReportInd(
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstMsg
)
{
    MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstLmmCellSignInfoInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstLmmCellSignInfoInd = (MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstLmmCellSignInfoInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaLmmCellSignInfoReportInd():ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstLmmCellSignInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pstLmmCellSignInfoInd), pstMsg, sizeof(MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU));


    /* �����Ϣͷ */
    pstLmmCellSignInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstLmmCellSignInfoInd->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstLmmCellSignInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstLmmCellSignInfoInd->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstLmmCellSignInfoInd->MsgHeader.ulLength          = sizeof(MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLmmCellSignInfoInd->MsgHeader.ulMsgName         = ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND;

    /* �����Ϣ���� */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstLmmCellSignInfoInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstLmmCellSignInfoInd);
}
/* Added by x00314862 for CDMA Iteration 9 2015-2-11 end */

VOS_VOID NAS_MSCC_SndMma1xSystemTimeInd(
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU   *pstMsg
)
{
    MSCC_MMA_1X_SYSTEM_TIME_IND_STRU   *pst1xSystemTimeInd = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pst1xSystemTimeInd = (MSCC_MMA_1X_SYSTEM_TIME_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_1X_SYSTEM_TIME_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pst1xSystemTimeInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMma1xSystemTimeInd():ERROR:Memory Alloc Error for pst1xSystemTimeInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pst1xSystemTimeInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_1X_SYSTEM_TIME_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    PS_MEM_CPY(((VOS_UINT8*)pst1xSystemTimeInd), pstMsg, sizeof(MSCC_MMA_1X_SYSTEM_TIME_IND_STRU));


    /* �����Ϣͷ */
    pst1xSystemTimeInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pst1xSystemTimeInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pst1xSystemTimeInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pst1xSystemTimeInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pst1xSystemTimeInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_1X_SYSTEM_TIME_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pst1xSystemTimeInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_1X_SYSTEM_TIME_IND;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pst1xSystemTimeInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pst1xSystemTimeInd);

    return;
}
VOS_VOID NAS_MSCC_SndMmaUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
)
{
    MSCC_MMA_UE_STATE_IND_STRU          *pstUeStatus = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstUeStatus = (MSCC_MMA_UE_STATE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMA_UE_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUeStatus)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaUeStatusInd():ERROR:Memory Alloc Error for pst1xSystemTimeInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstUeStatus) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_UE_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstUeStatus->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstUeStatus->ulSenderPid       = UEPS_PID_MSCC;
    pstUeStatus->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstUeStatus->ulReceiverPid     = WUEPS_PID_MMA;
    pstUeStatus->ulLength          = sizeof(MSCC_MMA_UE_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstUeStatus->enMsgId           = ID_MSCC_MMA_1X_UE_STATUS_IND;
    pstUeStatus->ucUeMainState     = ucUeMainState;
    pstUeStatus->ucUeSubState      = ucUeSubState;

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_MSCC, pstUeStatus);

    return;
}


#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID NAS_MSCC_SndMmaImsStartCnf(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult
)
{
    MSCC_MMA_IMS_START_CNF_STRU                            *pstStartCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstStartCnf = (MSCC_MMA_IMS_START_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
               sizeof(MSCC_MMA_IMS_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStartCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaImsStartCnf():ERROR:Memory Alloc Error for pst1xSystemTimeInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstStartCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_IMS_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstStartCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstStartCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstStartCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstStartCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstStartCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_IMS_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstStartCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_IMS_START_CNF;
    pstStartCnf->enResult                      = enResult;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstStartCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstStartCnf);

    return;
}
VOS_VOID NAS_MSCC_SndMmaImsStopCnf(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult
)
{
    MSCC_MMA_IMS_STOP_CNF_STRU                             *pstStopCnf = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstStopCnf = (MSCC_MMA_IMS_STOP_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
               sizeof(MSCC_MMA_IMS_STOP_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStopCnf)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaImsStopCnf():ERROR:Memory Alloc Error for pst1xSystemTimeInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstStopCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMA_IMS_STOP_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstStopCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstStopCnf->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstStopCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstStopCnf->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstStopCnf->stMsgHeader.ulLength          = sizeof(MSCC_MMA_IMS_STOP_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstStopCnf->stMsgHeader.ulMsgName         = ID_MSCC_MMA_IMS_STOP_CNF;
    pstStopCnf->enResult                      = enResult;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstStopCnf);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstStopCnf);

    return;

}
VOS_VOID NAS_MSCC_SndMmaImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
)
{
    MSCC_MMA_IMS_SWITCH_STATE_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_MMA_IMS_SWITCH_STATE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMA_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaImsSwitchStateInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMA_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMA_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMA_IMS_SWITCH_STATE_IND;
    pstMsg->enImsSwitch                  = enImsSwitch;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#endif




/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaInterSysStartInd
 ��������  : mscc��mma������ϢMSCC_MMA_INTERSYS_START_IND_STRU
 �������  : enOrignRatMode      ��Ϣ����
             enDestRatMode       ��Ϣ����
             enInterSysCause     ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
 1.��    ��   : 2015��5��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaInterSysStartInd(
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause
)
{
    MSCC_MMA_INTERSYS_START_IND_STRU   *pInterSysStartInd = VOS_NULL_PTR;

        /* ������Ϣ�� */
    pInterSysStartInd = (MSCC_MMA_INTERSYS_START_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pInterSysStartInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaInterSysStartInd():ERROR:Memory Alloc Error for pInterSysStartInd!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pInterSysStartInd) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pInterSysStartInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pInterSysStartInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pInterSysStartInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pInterSysStartInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pInterSysStartInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pInterSysStartInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_INTERSYS_START_IND;

    /* �����Ϣ�� */
    pInterSysStartInd->enOrignRatMode       = enOrignRatMode;
    pInterSysStartInd->enDestRatMode        = enDestRatMode;
    pInterSysStartInd->enInterSysCause      = enInterSysCause;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pInterSysStartInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pInterSysStartInd);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaInterSysEndInd
 ��������  : mscc��mma������ϢMSCC_MMA_INTERSYS_END_IND_STRU
 �������  : enCampedRatMode      ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
 1.��    ��   : 2015��5��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCampedRatMode
)
{
    MSCC_MMA_INTERSYS_END_IND_STRU     *pInterSysEndInd = VOS_NULL_PTR;

        /* ������Ϣ�� */
    pInterSysEndInd = (MSCC_MMA_INTERSYS_END_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pInterSysEndInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaInterSysEndInd():ERROR:Memory Alloc Error for pInterSysEndInd!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pInterSysEndInd) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pInterSysEndInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pInterSysEndInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pInterSysEndInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pInterSysEndInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pInterSysEndInd->stMsgHeader.ulLength          = sizeof(MSCC_MMA_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pInterSysEndInd->stMsgHeader.ulMsgName         = ID_MSCC_MMA_INTERSYS_END_IND;

    /* �����Ϣ�� */
    pInterSysEndInd->enCampedRatMode = enCampedRatMode;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pInterSysEndInd);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pInterSysEndInd);

    return;
}
/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaSidInd
 ��������  :  �ϱ�mma sid��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaSidInd(
    VOS_UINT16                          usSid
)
{
    MSCC_MMA_1X_SID_IND_STRU           *pstSndMsg = VOS_NULL_PTR;

        /* ������Ϣ�� */
    pstSndMsg = (MSCC_MMA_1X_SID_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_1X_SID_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSidInd():ERROR:Memory Alloc Error for pInterSysEndInd!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_1X_SID_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSndMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_1X_SID_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_1X_SID_IND;

    /* �����Ϣ�� */
    pstSndMsg->usSid = usSid;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);

    return;
}


VOS_VOID NAS_MSCC_SndMmaSyncServiceAvailInd(
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                   *pstSyncSrvAvailInd
)
{
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                   *pstSndMsg = VOS_NULL_PTR;

        /* ������Ϣ�� */
    pstSndMsg = (MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaSyncServiceAvailInd():ERROR:Memory Alloc Error for pInterSysEndInd!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSndMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND;

    /* �����Ϣ�� */
    pstSndMsg->usBandClass     = pstSyncSrvAvailInd->usBandClass;
    pstSndMsg->usFreq          = pstSyncSrvAvailInd->usFreq;
    pstSndMsg->usSid           = pstSyncSrvAvailInd->usSid;
    pstSndMsg->usNid           = pstSyncSrvAvailInd->usNid;
    pstSndMsg->enServiceStatus = pstSyncSrvAvailInd->enServiceStatus;
    pstSndMsg->ucRoamingInd    = pstSyncSrvAvailInd->ucRoamingInd;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);

    return;
}

/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, end */



#endif
/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, end */

/* Added by z00316370 for UTS 2015-5-22 begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaHandsetInfoQryCnf
 ��������  : ��MMA����ID_MSCC_MMA_CL_SYSTEM_ACQUIRE_END_IND
 �������  : NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32 enRslt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��22��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmaHandsetInfoQryCnf(
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU                     *pstInfo
)
{
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU *pstCnfMsg = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstCnfMsg = (MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmaHandsetInfoQryCnf:ERROR:Memory Alloc Error for pstClSysAcqEndInd!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCnfMsg) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstCnfMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCnfMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstCnfMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCnfMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstCnfMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnfMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_HANDSET_INFO_QRY_CNF;

    pstCnfMsg->enInfoType                    = pstInfo->enInfoType;
    pstCnfMsg->ucCasState                    = pstInfo->ucCasState;
    pstCnfMsg->ucCasSubSta                   = pstInfo->ucCasSubSta;
    pstCnfMsg->enHighVer                     = pstInfo->enHighVer;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstCnfMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstCnfMsg);

    return;
}
/* Added by z00316370 for UTS 2015-5-22 end */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



