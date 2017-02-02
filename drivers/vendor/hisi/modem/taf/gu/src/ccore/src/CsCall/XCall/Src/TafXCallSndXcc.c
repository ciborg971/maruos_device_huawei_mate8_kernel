

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallSndXcc.h"
#include "TafStdlib.h"
#include "Taf_Aps.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_SndXccOrigCallReq(
    VOS_UINT8                           ucCallId
)
{
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq = VOS_NULL_PTR;

    /* ������Ϣ */
    pstOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstOrigReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstOrigReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstOrigReq->ulReceiverPid           = UEPS_PID_XCC;
    pstOrigReq->enMsgId                 = ID_XCALL_XCC_ORIG_CALL_REQ;

    /* ��д��Ϣ���� */
    TAF_XCALL_BuildOrigCallPara(pstOrigReq, ucCallId);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstOrigReq);

    return;
}
VOS_VOID TAF_XCALL_SndXccAnswerCallReq(
    VOS_UINT8                           ucCallId
)
{
    XCALL_XCC_ANSWER_CALL_REQ_STRU     *pstAnswerCallReq  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAnswerCallReq = (XCALL_XCC_ANSWER_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_ANSWER_CALL_REQ_STRU));
    if (VOS_NULL_PTR == pstAnswerCallReq)
    {
        return;
    }

    /* �����Ϣ */
    pstAnswerCallReq->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstAnswerCallReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_ANSWER_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAnswerCallReq->enMsgId                = ID_XCALL_XCC_ANSWER_CALL_REQ;
    pstAnswerCallReq->usOpId                 = 0;
    pstAnswerCallReq->ucCallId               = ucCallId;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstAnswerCallReq);

}
VOS_VOID TAF_XCALL_SndXccHangUpCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangUpCallReq  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstHangUpCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_HANGUP_CALL_REQ_STRU));
    if (VOS_NULL_PTR == pstHangUpCallReq)
    {
        return;
    }

    /* �����Ϣ */
    pstHangUpCallReq->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstHangUpCallReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_HANGUP_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstHangUpCallReq->enMsgId                = ID_XCALL_XCC_HANGUP_CALL_REQ;
    pstHangUpCallReq->usOpId                 = 0;
    pstHangUpCallReq->ucCallId               = ucCallId;
    pstHangUpCallReq->enEndReason            = enEndReason;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstHangUpCallReq);

}
VOS_VOID TAF_XCALL_SndXccIncomingCallRsp(
    XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
)
{
    XCALL_XCC_INCOMING_CALL_RSP_STRU   *pstIncomingCallRsp  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstIncomingCallRsp = (XCALL_XCC_INCOMING_CALL_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_INCOMING_CALL_RSP_STRU));
    if (VOS_NULL_PTR == pstIncomingCallRsp)
    {
        return;
    }

    /* �����Ϣ */
    pstIncomingCallRsp->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstIncomingCallRsp + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_INCOMING_CALL_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstIncomingCallRsp->enMsgId                = ID_XCALL_XCC_INCOMING_CALL_RSP;
    pstIncomingCallRsp->usOpId                 = 0;
    pstIncomingCallRsp->ucCallId               = ucCallId;
    pstIncomingCallRsp->ucConnectId            = ucConnectId;
    pstIncomingCallRsp->enRslt                 = enRslt;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstIncomingCallRsp);

}
VOS_UINT32 TAF_XCALL_SndXccFlashReq(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigits
)
{
    XCALL_XCC_SEND_FLASH_REQ_STRU   *pstFlashReq  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstFlashReq = (XCALL_XCC_SEND_FLASH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_SEND_FLASH_REQ_STRU));
    if (VOS_NULL_PTR == pstFlashReq)
    {
        return VOS_ERR;
    }

    /* ��дVOS��Ϣͷ */
    pstFlashReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstFlashReq->ulSenderPid     = WUEPS_PID_TAF;
    pstFlashReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstFlashReq->ulReceiverPid   = UEPS_PID_XCC;

    /* ��д��Ϣ���� */
    PS_MEM_SET((VOS_UINT8 *)pstFlashReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstFlashReq->enMsgId    = ID_XCALL_XCC_SEND_FLASH_REQ;
    pstFlashReq->usOpId     = 0;
    pstFlashReq->ucCallId   = ucCallId;
    pstFlashReq->ucDigitNum = ucDigitNum;
    PS_MEM_CPY(pstFlashReq->aucDigit, pucDigits, ucDigitNum);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstFlashReq);

    return VOS_OK;
}



VOS_VOID TAF_XCALL_BuildOrigCallPara(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigPara,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CONFIG_STRU              *pstCallConfig = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    /* ���� PCLINT429 �澯 */
    pstOrigPara = pstOrigPara;

    pstCallConfig = TAF_XCALL_GetConfigInfo();
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* ��дORIG_CALL_REQ���� */
    pstOrigPara->ucCallId               = ucCallId;

    if (MN_CALL_TYPE_EMERGENCY == pstCallEntity->enCallType)
    {
        pstOrigPara->ucIsEmergencyCall  = VOS_TRUE;
    }
    else
    {
        pstOrigPara->ucIsEmergencyCall  = VOS_FALSE;
    }

    pstOrigPara->ucIsL2ErrReOrig        = pstCallEntity->ucIsL2ErrReOrig;
    pstOrigPara->ucReOrigCount          = pstCallEntity->ucReOrigCount;
    pstOrigPara->enDigitMode            = pstCallConfig->enDigitMode;

    /* so info */
    pstOrigPara->stSoInfo.enSo          = pstCallEntity->enSo;

    /* calling num */
    if (0 != pstCallEntity->stCallNumber.ucNumLen)
    {
        pstOrigPara->bitOpCallingPartyNum = VOS_TRUE;
        TAF_XCALL_BuildCallingNum(&pstOrigPara->stCallingPartyNum,
                                  pstCallEntity,
                                  pstOrigPara->enDigitMode);
    }

    /* calling num subaddress */
    if (VOS_TRUE == pstCallEntity->stCallSubNumber.IsExist)
    {
        pstOrigPara->bitOpCallingPartySubAddr = VOS_TRUE;
        TAF_XCALL_BuildCallingSubAddr(&pstOrigPara->stCallingPartySubAddr, pstCallEntity);
    }

    /* called num */
    TAF_XCALL_BuildCalledNum(&pstOrigPara->stCalledPartyNum,
                             pstCallEntity,
                             pstOrigPara->enDigitMode);

    /* called num subaddress */
    if (VOS_TRUE == pstCallEntity->stCalledSubAddr.IsExist)
    {
        pstOrigPara->bitOpCalledPartySubAddr = VOS_TRUE;
        TAF_XCALL_BuildCalledSubAddr(&pstOrigPara->stCalledPartySubAddr, pstCallEntity);
    }

    return;
}
VOS_VOID TAF_XCALL_BuildCallingNum(
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU  *pstCallingNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
)
{
    VOS_CHAR                                acDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(acDigit, 0, (XCC_XCALL_MAX_NUM_DIGIT_LEN + 1));

    pstCallingNum->enNumType    = (XCC_XCALL_NUMBER_TYPE_ENUM_UINT8)((pstCallEntity->stCallNumber.enNumType & TAF_XCALL_CALL_NUM_TYPE_VALID_BIT) >> 4);
    pstCallingNum->enNumPlan    = pstCallEntity->stCallNumber.enNumType & TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT;
    pstCallingNum->ucPi         = pstCallEntity->ucPi;
    pstCallingNum->ucSi         = pstCallEntity->ucSi;

    /*�ж�pstCallEntity->stCallNumber.aucBcdNum��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pstCallEntity->stCallNumber.aucBcdNum[pstCallEntity->stCallNumber.ucNumLen - 1] & 0xF0) == 0xF0)
    {
        pstCallingNum->ucDigitNum = (VOS_UINT8)((pstCallEntity->stCallNumber.ucNumLen * 2) - 1);
    }
    else
    {
        pstCallingNum->ucDigitNum = (VOS_UINT8)(pstCallEntity->stCallNumber.ucNumLen * 2);
    }

    /* ���к������ */
    pstCallingNum->ucDigitNum = TAF_XCALL_MIN(pstCallingNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN);

    if (XCC_XCALL_DIGIT_MODE_ASCII == enDigitMode)
    {
        /* BCD->ASCII */
        if (MN_ERR_NO_ERROR == TAF_STD_ConvertBcdNumberToAscii(pstCallEntity->stCallNumber.aucBcdNum,
                                                               pstCallEntity->stCallNumber.ucNumLen,
                                                               acDigit))
        {
            PS_MEM_CPY((VOS_CHAR *)pstCallingNum->aucDigit,
                        acDigit,
                        pstCallingNum->ucDigitNum);
        }
    }
    else
    {
        /* BCD->DTMF */
        TAF_STD_ConvertBcdNumberToDtmf(pstCallEntity->stCallNumber.aucBcdNum,
                                       pstCallEntity->stCallNumber.ucNumLen,
                                       pstCallingNum->aucDigit);
    }

    return;
}
VOS_VOID TAF_XCALL_BuildCallingSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
)
{
    /*TO DO:*/

    return;
}
VOS_VOID TAF_XCALL_BuildCalledNum(
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU   *pstCalledNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
)
{
    VOS_CHAR                                acDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(acDigit, 0, (XCC_XCALL_MAX_NUM_DIGIT_LEN + 1));

    pstCalledNum->enNumType = (XCC_XCALL_NUMBER_TYPE_ENUM_UINT8)((pstCallEntity->stCalledNumber.enNumType & TAF_XCALL_CALL_NUM_TYPE_VALID_BIT) >> 4);
    pstCalledNum->enNumPlan = pstCallEntity->stCalledNumber.enNumType & TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT;

    /*�ж�pstCallEntity->stCallNumber.aucBcdNum��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pstCallEntity->stCalledNumber.aucBcdNum[pstCallEntity->stCalledNumber.ucNumLen - 1] & 0xF0) == 0xF0)
    {
        pstCalledNum->ucDigitNum = (VOS_UINT8)((pstCallEntity->stCalledNumber.ucNumLen * 2) - 1);
    }
    else
    {
        pstCalledNum->ucDigitNum = (VOS_UINT8)(pstCallEntity->stCalledNumber.ucNumLen * 2);
    }

    /* ���к������ */
    pstCalledNum->ucDigitNum = TAF_XCALL_MIN(pstCalledNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN);

    if (XCC_XCALL_DIGIT_MODE_ASCII == enDigitMode)
    {
        /* BCD->ASCII */
        if (MN_ERR_NO_ERROR == TAF_STD_ConvertBcdNumberToAscii(pstCallEntity->stCalledNumber.aucBcdNum,
                                                               pstCallEntity->stCalledNumber.ucNumLen,
                                                               acDigit))
        {
            PS_MEM_CPY((VOS_CHAR *)pstCalledNum->aucDigit,
                       acDigit,
                       pstCalledNum->ucDigitNum);
        }
    }
    else
    {
        /* BCD->DTMF */
        TAF_STD_ConvertBcdNumberToDtmf(pstCallEntity->stCalledNumber.aucBcdNum,
                                       pstCallEntity->stCalledNumber.ucNumLen,
                                       pstCalledNum->aucDigit);
    }

    return;
}
VOS_VOID TAF_XCALL_BuildCalledSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
)
{
    /*TO DO:*/
    return;
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndXccBurstDTMFReq
 ��������  : ���͸�XCC��ϢID_XCALL_XCC_BURST_DTMF_REQ
 �������  : pstBurstDtmfInfo
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccBurstDTMFReq(
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstBurstDtmfInfo
)
{
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstBurstDTMFReq = VOS_NULL_PTR;

    /* ������Ϣ  */
    pstBurstDTMFReq = (XCALL_XCC_BURST_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_BURST_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstBurstDTMFReq)
    {
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ALLOC_MSG_FAIL;
    }

    /* ��дVOS��Ϣͷ */
    pstBurstDTMFReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBurstDTMFReq->ulSenderPid     = WUEPS_PID_TAF;
    pstBurstDTMFReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBurstDTMFReq->ulReceiverPid   = UEPS_PID_XCC;

    /* ��д��Ϣ���� */
    PS_MEM_SET((VOS_UINT8 *)pstBurstDTMFReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_BURST_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBurstDTMFReq->enMsgId     = ID_XCALL_XCC_SEND_BURST_DTMF_REQ;
    pstBurstDTMFReq->usOpId      = 0;
    pstBurstDTMFReq->ucCallId    = pstBurstDtmfInfo->ucCallId;
    pstBurstDTMFReq->ucDigitNum  = pstBurstDtmfInfo->ucDigitNum;
    pstBurstDTMFReq->ulOnLength  = pstBurstDtmfInfo->ulOnLength;
    pstBurstDTMFReq->ulOffLength = pstBurstDtmfInfo->ulOffLength;

    PS_MEM_CPY(pstBurstDTMFReq->aucDigit, pstBurstDtmfInfo->aucDigit, pstBurstDTMFReq->ucDigitNum);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstBurstDTMFReq);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
}
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndXccContDTMFReq
 ��������  : ���͸�XCC��ϢID_XCALL_XCC_CONT_DTMF_REQ
 �������  : pstContDtmfInfo
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccContDTMFReq(
    TAF_CALL_CONT_DTMF_PARA_STRU      *pstContDtmfInfo
)
{
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstContDTMFReq = VOS_NULL_PTR;

    /* ������Ϣ  */
    pstContDTMFReq = (XCALL_XCC_SEND_CONT_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstContDTMFReq)
    {
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ALLOC_MSG_FAIL;
    }

    /* ��дVOS��Ϣͷ */
    pstContDTMFReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstContDTMFReq->ulSenderPid     = WUEPS_PID_TAF;
    pstContDTMFReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstContDTMFReq->ulReceiverPid   = UEPS_PID_XCC;
    pstContDTMFReq->ulLength        = sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    PS_MEM_SET((VOS_UINT8 *)pstContDTMFReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstContDTMFReq->enMsgId     = ID_XCALL_XCC_SEND_CONT_DTMF_REQ;
    pstContDTMFReq->usOpId      = 0;
    pstContDTMFReq->ucCallId    = pstContDtmfInfo->ucCallId;
    pstContDTMFReq->enSwitch    = pstContDtmfInfo->enSwitch;
    pstContDTMFReq->ucDigit     = pstContDtmfInfo->ucDigit;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstContDTMFReq);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
}
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






