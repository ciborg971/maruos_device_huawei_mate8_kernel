
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_SND_XCC_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmCpLinkCtrl.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndXcc.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))


/*****************************************************************************
 Func Name    : TAF_XPDS_EncodeDataBurstMsg
 Description  : function to send the Call orig req to xcc


  History       :
  1.Date        :  25-08-2015
    Author      :  Arjun A00903922
    Modification:  Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SendCallOrigMsgtoXcc(
    VOS_UINT8                           ucIsL2ErrReOrig
)
{

    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstCallReq;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen   = sizeof(XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU);

    pstCallReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XPDS, ulMsgLen);
    if (VOS_NULL_PTR == pstCallReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SendCallOrigMsgtoXcc: malloc failed");
        return VOS_ERR;
    }

    pstCallReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCallReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCallReq->ulSenderPid         = UEPS_PID_XPDS;
    pstCallReq->ulReceiverPid       = UEPS_PID_XCC;
    pstCallReq->ulLength            = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstCallReq->usOpId    = 0x00;
    pstCallReq->enMsgId   = ID_XPDS_XCC_ORIG_AGPS_CALL_REQ;
    pstCallReq->ucCallId  = 0x00;
    pstCallReq->enSo      = TAF_CDMA_SO_36_LOC_SERV;

    pstCallReq->ucIsL2ErrReOrig     = ucIsL2ErrReOrig;
    pstCallReq->ucL2ErrReOrigCount  = 0x00; // ??

    PS_SEND_MSG(UEPS_PID_XPDS, pstCallReq);

    return VOS_OK;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_SendIncomingCallRspMsgtoXcc
 Description  : function to send the incoming call resp to xcc


  History       :
  1.Date        :  25-08-2015
    Author      :  Arjun A00903922
    Modification:  Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SendIncomingCallRspMsgtoXcc(
    VOS_UINT8                           ucConnectId
)
{

    XPDS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallPsp;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen   = sizeof(XPDS_XCC_INCOMING_CALL_RSP_STRU);

    pstIncomingCallPsp = (XPDS_XCC_INCOMING_CALL_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XPDS, ulMsgLen);
    if (VOS_NULL_PTR == pstIncomingCallPsp)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SendIncomingCallRspMsgtoXcc: malloc failed");
        return VOS_ERR;
    }

    pstIncomingCallPsp->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstIncomingCallPsp->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstIncomingCallPsp->ulSenderPid         = UEPS_PID_XPDS;
    pstIncomingCallPsp->ulReceiverPid       = UEPS_PID_XCC;
    pstIncomingCallPsp->ulLength            = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstIncomingCallPsp->enMsgId             = ID_XPDS_XCC_INCOMING_CALL_RSP;
    pstIncomingCallPsp->enRslt              = XCC_XPDS_RESULT_SUCC;

    pstIncomingCallPsp->ucCallId            = 0x00;
    pstIncomingCallPsp->ucConnectId         = ucConnectId;
    pstIncomingCallPsp->usOpId              = 0x00;

    PS_SEND_MSG(UEPS_PID_XPDS, pstIncomingCallPsp);

    return VOS_OK;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_SendAnswerCallReqMsgtoXcc
 Description  : function to send the answer call req to xcc


  History       :
  1.Date        :  25-08-2015
    Author      :  Arjun A00903922
    Modification:  Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SendAnswerCallReqMsgtoXcc(VOS_VOID)
{
    XPDS_XCC_ANSWER_CALL_REQ_STRU      *pstAnswerCallReq;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen   = sizeof(XPDS_XCC_ANSWER_CALL_REQ_STRU);

    pstAnswerCallReq = (XPDS_XCC_ANSWER_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XPDS, ulMsgLen);
    if (VOS_NULL_PTR == pstAnswerCallReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SendAnswerCallReqMsgtoXcc: malloc failed");
        return VOS_ERR;
    }

    pstAnswerCallReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAnswerCallReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAnswerCallReq->ulSenderPid       = UEPS_PID_XPDS;
    pstAnswerCallReq->ulReceiverPid     = UEPS_PID_XCC;
    pstAnswerCallReq->ulLength          = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstAnswerCallReq->ucCallId          = 0x00;
    pstAnswerCallReq->usOpId            = 0x00;

    pstAnswerCallReq->enMsgId           = ID_XPDS_XCC_ANSWER_CALL_REQ;

    PS_SEND_MSG(UEPS_PID_XPDS, pstAnswerCallReq);

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


