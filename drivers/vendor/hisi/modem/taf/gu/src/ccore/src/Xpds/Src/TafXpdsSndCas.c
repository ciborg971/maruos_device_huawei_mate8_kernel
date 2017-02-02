

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsSndCas.h"
#include "TafXpdsMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 1
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_SND_CAS_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID TAF_XPDS_SndCasSyncTimeReq(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    XPDS_CAS_TIME_SYNC_REQ_STRU        *pstCASTimeSyncReq;
    VOS_UINT32                          ulCASReceiverPid;
    PS_BOOL_ENUM_UINT8                  enForcePulse;
    VOS_UINT32                          ulLength;

    enForcePulse                        = VOS_FALSE;

    /* ��ǰ����״̬ */
    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulCASReceiverPid      = UEPS_PID_HRUP;
    }
    else if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode) || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        ulCASReceiverPid      = UEPS_PID_1XCMEAS;
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasSyncTimeReq: Current Sys mode not avilable!");

        ulCASReceiverPid      = UEPS_PID_1XCMEAS;
        enForcePulse          = VOS_TRUE;
    }

    /* ������Ϣ��CAS��ȡSYNC */
    ulLength           = sizeof(XPDS_CAS_TIME_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCASTimeSyncReq  = (XPDS_CAS_TIME_SYNC_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_XPDS, ulLength);

    if (VOS_NULL_PTR == pstCASTimeSyncReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasSyncTimeReq: Alloc msg fail!");

        return;
    }

    pstCASTimeSyncReq->stMsgHeader.ulMsgName        = ID_XPDS_CAS_TIME_SYNC_REQ;
    pstCASTimeSyncReq->stMsgHeader.ulReceiverPid    = ulCASReceiverPid;
    pstCASTimeSyncReq->enForcePulse                 = enForcePulse;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XPDS, pstCASTimeSyncReq);

    return;
}


VOS_VOID TAF_XPDS_SndCasRefLocReq(
    TAF_SDC_SYS_MODE_ENUM_UINT8             enSysMode,
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8    enRptType
)
{
    XPDS_CAS_REF_LOC_REQ_STRU          *pstRefLocReq;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulReceiverPid;

    /* start��cnf:��������CAS�·�STOP��Ϣ������CASһֱ�ϱ���Ϣ */
    ulLength      = sizeof(XPDS_CAS_REF_LOC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRefLocReq  = (XPDS_CAS_REF_LOC_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_XPDS, ulLength);

    if (VOS_NULL_PTR == pstRefLocReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasRefLocReq: Alloc msg fail!");

        return ;
    }

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulReceiverPid      = UEPS_PID_HRUP;
    }
    else if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
          || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        ulReceiverPid      = UEPS_PID_1XCMEAS;
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasRefLocReq: Current Sys mode not avilable!");

        ulReceiverPid      = UEPS_PID_1XCMEAS;
    }

    pstRefLocReq->stMsgHeader.ulMsgName     = ID_XPDS_CAS_REF_LOC_REQ;
    pstRefLocReq->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstRefLocReq->enRptType                 = enRptType;

    /* ������Ϣ��CAS */
    PS_SEND_MSG(UEPS_PID_XPDS, pstRefLocReq);

    return ;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_SndCasDataBurstMsg
 Description  : Function for encoding and sending the
                CNAS_CAS_1X_DSCH_DATA_REQ_STRU msg to CAS

  History       :
  1.Date        :  25-08-2015
    Author      :  Arjun a00903922
    Modification:  Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SndCasDataBurstMsg(
    VOS_UINT8                          *pcPdeBuf,
    VOS_UINT32                          ulLength
)
{
    TAF_XPDS_DATA_BURST_MSG_STRU        stDataBurstMsg;
    VOS_UINT32                          ulLengthDataReq;
    VOS_UINT8                           aucDestBuf[TAF_XPDS_MAX_PDM_MSG_BUF_LEN];

    PS_MEM_SET(aucDestBuf,      0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);
    PS_MEM_SET(&stDataBurstMsg, 0x00, sizeof(TAF_XPDS_DATA_BURST_MSG_STRU));
    ulLengthDataReq             = 0;

    stDataBurstMsg.ucBurstType  = 0x05;
    stDataBurstMsg.ucMsgNum     = 0x01;
    stDataBurstMsg.ucNumMsgs    = 0x01;
    stDataBurstMsg.ucNumFields  = (VOS_UINT8)(ulLength - 1); // subtracting 1 for the length field

    /* copying the PDE Msg to aucData, not copying the length field*/

#if BIG_ENDIAN
    PS_MEM_CPY(stDataBurstMsg.aucData, pcPdeBuf + 1, stDataBurstMsg.ucNumFields);
#else
    VOS_UINT32                      ulLoopCount;

    for (ulLoopCount = 0; ulLoopCount < stDataBurstMsg.ucNumFields; ulLoopCount++)
    {
        stDataBurstMsg.aucData[ulLoopCount] = pcPdeBuf[1 + ulLoopCount];
    }
#endif

    TAF_XPDS_EncodeDataBurstMsg(&stDataBurstMsg, aucDestBuf, &ulLengthDataReq);

    TAF_XPDS_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_DATA_BURST_MSG,
                               0,
                               (VOS_UINT16)ulLengthDataReq,
                               aucDestBuf);

    return;

}

/*****************************************************************************
 Func Name    : TAF_XPDS_SndCasDschDataReq
 Description  : Function for sending the CNAS_CAS_1X_DSCH_DATA_REQ_STRU msg
                to the CAS

  History       :
  1.Date        :  25-08-2015
    Author      :  Arjun a00903922
    Modification:  Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SndCasDschDataReq(
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enTxcDschMsgType,
    VOS_UINT8                               ucMsgSeqNum,
    VOS_UINT16                              usMsgDataLen,
    VOS_UINT8                              *pucMsgData
)
{
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDataReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;


    ulMsgLen   = sizeof(CNAS_CAS_1X_DSCH_DATA_REQ_STRU) + usMsgDataLen - sizeof(pstDataReq->aucMsgData);

    pstDataReq = (CNAS_CAS_1X_DSCH_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XPDS, ulMsgLen);

    if (VOS_NULL_PTR == pstDataReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasDschDataReq: malloc failed");
        return;
    }

    PS_MEM_SET(pstDataReq, 0, ulMsgLen);

    /* �����Ϣ */
    pstDataReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDataReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDataReq->ulSenderPid         = UEPS_PID_XPDS;
    pstDataReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstDataReq->ulLength            = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstDataReq->enMsgId             = ID_CNAS_CAS_1X_DSCH_DATA_REQ;
    pstDataReq->usOpId              = 0;
    pstDataReq->enTxDschMsgType     = enTxcDschMsgType;
    pstDataReq->ucMsgSeqNum         = ucMsgSeqNum;
    pstDataReq->enIsAmDataReq       = VOS_FALSE; //??
    pstDataReq->usMsgDataLen        = (VOS_UINT16)(usMsgDataLen * 8);

    PS_MEM_CPY(pstDataReq->aucMsgData, pucMsgData, usMsgDataLen);

    PS_SEND_MSG(UEPS_PID_XPDS, pstDataReq);

    return;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_SndCasDschDataReq
 Description  : Function for sending the CNAS_CAS_1X_DSCH_DATA_REQ_STRU msg
                to the CAS

  History       :
  1.Date        :  11-09-2015
    Author      :  Arjun a00903922
    Modification:  Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SndCasPdeSessionEndMsg(VOS_VOID)
{
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
    VOS_UINT8                          *pucMsgBuff;
    VOS_UINT32                          ulTotLength;
    VOS_UINT32                          ulTempLen;

    /* allocate memory for the message */
    pucMsgBuff  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucMsgBuff)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndCasPdeSessionEndMsg, malloc failed");
        return VOS_ERR;
    }

    PS_MEM_SET(pucMsgBuff, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    stPdMsgHeader.ucSessStart = 0;
    stPdMsgHeader.ucSessEnd   = 1;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();

    stPdMsgHeader.ucPdMsgType = 0;

    /* number of req and response is 0 as of now in session end message */
    stPdMsgHeader.ucNumOfReq   = 0;
    stPdMsgHeader.ucNumOfResp  = 1;

    ulTotLength              = 0;
    ulTempLen                = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;
    ulTempLen    = 0;

    TAF_XPDS_EncodeProvMsInfo(pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;

    /* update the length field of data burst message */
    pucMsgBuff[0] = (VOS_UINT8)ulTotLength;

    ulTotLength += 1;

    /* need to send message to PDE */
    TAF_XPDS_SndCasDataBurstMsg(pucMsgBuff, ulTotLength);

    /* freeing the memory */
    PS_MEM_FREE(UEPS_PID_XPDS, pucMsgBuff);

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

