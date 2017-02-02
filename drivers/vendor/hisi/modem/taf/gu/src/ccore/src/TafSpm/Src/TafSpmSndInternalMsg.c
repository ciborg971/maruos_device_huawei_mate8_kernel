
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafLog.h"
#include "TafSpmCtx.h"
#include "TafSpmSndInternalMsg.h"
#include "TafInternalInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_INTERNAL_MSG_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
    VOS_UINT32                                              ulCause,
    VOS_UINT16                                              usClientId,
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU      *pstServiceCtrlRstInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstServiceCtrlRstInd = (TAF_SPM_SERVICE_CTRL_RSLT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU));
    if (VOS_NULL_PTR == pstServiceCtrlRstInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_INT8*)pstServiceCtrlRstInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstServiceCtrlRstInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstServiceCtrlRstInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND;

    /* ��д��Ϣ���� */
    pstServiceCtrlRstInd->enResult                  = enRslt;
    pstServiceCtrlRstInd->ulCause                   = ulCause;
    pstServiceCtrlRstInd->usClientId                = usClientId;
    pstServiceCtrlRstInd->stEntryMsg.ulEventType    = pstEntryMsg->ulEventType;

    PS_MEM_CPY(pstServiceCtrlRstInd->stEntryMsg.aucEntryMsgBuffer,
                pstEntryMsg->aucEntryMsgBuffer,
                sizeof(pstEntryMsg->aucEntryMsgBuffer));

    /* �����ڲ���Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstServiceCtrlRstInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: Send message failed.");
    }

    return;
}

/* �ŵ�IMS�꿪�����湫��ʹ�� */

VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_IND_STRU        *pstDomainSelInd = VOS_NULL_PTR;

    /* allocate memory for message */
    pstDomainSelInd = (TAF_SPM_DOMAIN_SEL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_TAF,
                                                        sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU));
    /* return if memory allocation is failure */
    if (VOS_NULL_PTR == pstDomainSelInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Memory allocation is failure!");

        return;
    }

    /* initialize message */
    PS_MEM_SET(((VOS_INT8*)pstDomainSelInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* fill message header */
    pstDomainSelInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDomainSelInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_DOMAIN_SEL_IND;

    /* send domain selection indication message to self */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstDomainSelInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Send message failed.");
    }

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaRsp = VOS_NULL_PTR;
    TAF_SPM_SMMA_IND_STRU              *pstSmmaInd = VOS_NULL_PTR;

    pstSmmaRsp = (TAF_SPM_SMMA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_SPM_SMMA_RSP_STRU));

    if (VOS_NULL_PTR == pstSmmaRsp)
    {
        MN_WARN_LOG("TAF_SPM_SendMsgSmmaRsp:ERROR: VOS_AllocMsg fail.");
        return;
    }

    pstSmmaInd  = (TAF_SPM_SMMA_IND_STRU *)pstMsg;
    
    PS_MEM_SET(pstSmmaRsp, 0, sizeof(TAF_SPM_SMMA_RSP_STRU));

    pstSmmaRsp->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulSenderPid          = WUEPS_PID_TAF;
    pstSmmaRsp->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulReceiverPid        = WUEPS_PID_TAF;
    pstSmmaRsp->ulLength             = sizeof(TAF_SPM_SMMA_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSmmaRsp->ulMsgId              = ID_TAF_SPM_SMMA_RSP;
    pstSmmaRsp->clientId             = pstSmmaInd->clientId;
    pstSmmaRsp->opId                 = pstSmmaInd->opId;
    pstSmmaRsp->enMsgSignallingType  = enMsgSignallingType;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmmaRsp ) )
    {
        MN_WARN_LOG( "TAF_SPM_SendMsgSmmaRsp:WARNING:SEND ID_TAF_SPM_SMMA_RSP msg FAIL!" );
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
)
{
    TAF_CALL_TAF_REL_CALL_REQ_STRU     *pstRelCallReq = VOS_NULL_PTR;

    pstRelCallReq = (TAF_CALL_TAF_REL_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                        sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstRelCallReq)
    {
        MN_WARN_LOG("TAF_SPM_SndTafRelCallReq:ERROR: VOS_AllocMsg fail.");
        return;
    }

    PS_MEM_SET(pstRelCallReq, 0, sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    pstRelCallReq->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstRelCallReq->ulSenderPid          = WUEPS_PID_TAF;
    pstRelCallReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstRelCallReq->ulReceiverPid        = WUEPS_PID_TAF;
    pstRelCallReq->ulLength             = sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRelCallReq->ulMsgId              = TAF_CALL_TAF_REL_CALL_REQ;

    pstRelCallReq->usClientId           = usClientId;
    pstRelCallReq->ucOpId               = ucOpId;
    pstRelCallReq->enRelType            = enRelType;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstRelCallReq))
    {
        MN_WARN_LOG( "TAF_SPM_SndTafRelCallReq:WARNING:SEND TAF_SPM_SndTafRelCallReq msg FAIL!" );
    }

    return;
}
#endif
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


