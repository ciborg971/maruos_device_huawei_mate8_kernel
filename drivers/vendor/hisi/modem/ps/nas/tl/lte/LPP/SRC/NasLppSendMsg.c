/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppSendMsg.c
  Description     :
  History         :
     1.XiaoJun       2015-7-30   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "LPPLRrcInterface.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPSENDMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPSENDMSG_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_UINT16  NAS_LPP_EncodeMessage
(
    LPP_MESSAGE_STRU                   *pstLppMsg,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
);
extern VOS_VOID NAS_LPP_SendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
);
/*****************************************************************************
 Function Name  : NAS_LPP_SndLppLrrcEcidMeasReq
 Description    : 给LRRC发送ECID测量请求
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      XIAOJUN  2015-7-24  新开发
*****************************************************************************/

VOS_VOID NAS_LPP_SndLppLrrcEcidMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_ECID_MEAS_REQ_STRU *pstEcidMeasReq;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLppLrrcEcidMeasReq enter");

    pstEcidMeasReq = (LPP_LRRC_ECID_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstEcidMeasReq)
    {
        NAS_LPP_ERR_LOG("lpp snd ecid meas req allocal msg null");
        return;
    }

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstEcidMeasReq,ID_LPP_LRRC_ECID_MEAS_REQ);

    pstEcidMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;
    pstEcidMeasReq->ucRxTxTimeDiffMeasFlag = PS_TRUE;

    NAS_LPP_SND_MSG(pstEcidMeasReq);

    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_ECID,NAS_LPP_SLCT);
}


/*****************************************************************************
 Function Name   : NAS_LPP_SndOtdoaMeasReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SndOtdoaMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_OTDOA_MEAS_REQ_STRU            *pstOtdoaMeasReq;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo;

    pstOtdoaMeasReq = (LPP_LRRC_OTDOA_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU));

    if (NAS_LPP_NULL_PTR == pstOtdoaMeasReq)
    {
        NAS_LPP_ERR_LOG("lpp snd otdoa meas req allocal msg null");
        return;
    }

    pstTransEntity = NAS_LPP_GetTransEntity(ucSessionIndx, ucSessionTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG2("lpp snd otdoa meas req :with wrong index",ucSessionIndx, ucSessionTransIndx);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo)
    {
        NAS_LPP_ERR_LOG1("lpp snd otdoa meas req :with wrong comm cfg index", pstTransEntity->ucCommCfgIndex);
        return ;
    }

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstOtdoaMeasReq,ID_LPP_LRRC_OTDOA_MEAS_REQ);

    pstOtdoaMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;


    if (LPP_LRRC_LCS_MEAS_CMD_SETUP == ucLcsMeasCmd)
    {
        pstOtdoaMeasReq->ucOtdoaMeasAssistanceDataFlag = LPP_LRRC_INFO_FLAG_VALID;

        if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppCommCfgInfo->stReportCriteria.enType)
        {
            pstOtdoaMeasReq->enOtdoaRprtInterval = pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.enOtdoaRprtInterval;
        }
        else
        {
            pstOtdoaMeasReq->enOtdoaRprtInterval = LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16;  /*REPORT ONCEDE ,¸ølrrcµÄÊÇÕÛÖÐµÄÊ±¼ä³¤¶È*/
        }

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaReferenceCellInfoFlag
            = pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag;

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaNeighbourCellInfoFlag
            = pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag;

        NAS_LPP_MEM_CPY(&pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaReferenceCellInfo,
                        &pstOtdoaAssisCfg->stOtdoaReferenceCellInfo,
                        sizeof(LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU));

        NAS_LPP_MEM_CPY(&pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaNeighbourCellInfo,
                        &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo,
                        sizeof(LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU));
    }

    NAS_LPP_SND_MSG(pstOtdoaMeasReq);

    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_OTDOA,NAS_LPP_SLCT);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppAbortMsg
 Description     : ×é×°¡¢±àÂëÉÏÐÐµÄABORTÏûÏ¢
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SndUpLppAbortMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_COMMON_IES_ABORT_ENUM_UINT8     enAbortCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstUpAbort = NAS_LPP_NULL_PTR;
    LPP_C1_EXT_ABORT_STRU                   *pstAbortExtC1 = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity ={0};
    VOS_UINT16 usRslt,usBitPos = 0;
    VOS_UINT32 ulLppMsgLen;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        /*ÊÍ·ÅÉêÇëµÄ¶¯Ì¬ÄÚ´æ*/
        NAS_LPP_ERR_LOG1("snd abort: Don't find the session! ucSessionIndx",ucSessionIndx);
        return;
    }

    /*»ñÈ¡transactionÊµÌå*/
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /*ÊÍ·ÅÉêÇëµÄ¶¯Ì¬ÄÚ´æ*/
        NAS_LPP_ERR_LOG1("snd abort: Don't find the transaction!ucTransIndx",ucTransIndx);
        return;
    }

    /*·ÖÅä±àÂëÖ®ºóÂëÁ÷µÄ´æ´¢¿Õ¼ä*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("enocde up abort  Alloc Mem Fail!");
        return;
    }

    /*Çå¿Õ*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);


    /*»ñÈ¡LPP MSG BUFF*/
    pstUpAbort = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET(pstUpAbort, 0, sizeof(LPP_MESSAGE_STRU));

    pstUpAbort->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUpAbort->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstUpAbort->bitOpLppMessageBody   = NAS_LPP_SLCT;

    if ( PS_TRUE == enNeedAck )
    {
         pstUpAbort->bitOpAcknowledgement  = NAS_LPP_SLCT;
         pstUpAbort->stAcknowledgement.bAckRequested = enNeedAck;

         /* ÎÞÐèack indicator*/
    }

    /*pstUpAbort->stTransactionId.bitOpTransactionIDExtÔÝÊ±Ã»ÓÃ£¬Ä¬ÈÏÎª0*/
    pstUpAbort->stTransactionId.enInitiator = pstTransEntity->stTransId.enInitiator;
    pstUpAbort->stTransactionId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    pstUpAbort->bEndTransaction = bEndTransaction;

    pstUpAbort->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstUpAbort->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUpAbort->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN;
    pstUpAbort->stLppMessageBody.u.stC1.u.stAbort.stC1.ulChoice = LPP_CRITI_EXT_ABORT_CHOSEN;

    pstAbortExtC1 = &(pstUpAbort->stLppMessageBody.u.stC1.u.stAbort.stC1.u.stAbortExtC1);
    pstAbortExtC1->ulChoice = LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN;
    pstAbortExtC1->u.stAbortR9.bitOpAbortR9IEsExt  = NAS_LPP_SLCT;
    pstAbortExtC1->u.stAbortR9.bitOpCommonIesAbort = NAS_LPP_SLCT;
    pstAbortExtC1->u.stAbortR9.stCommonIesAbort.bitOpCommonIEsAbortExt= NAS_LPP_SLCT;
    pstAbortExtC1->u.stAbortR9.stCommonIesAbort.enCommonIesAbortCasue = enAbortCause;


    /*¿ªÊ¼±àÂë*/
    usRslt = NAS_LPP_EncodeMessage(pstUpAbort,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode LPP abort msg Fail!");
        return;
    }

    ulLppMsgLen = usBitPos/8;

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransEntity->stTransId.enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = pstSessionEntity->ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstUpAbort->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(pstSessionEntity->ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppErrorMsg
 Description     : ×é×°¡¢±àÂëÉÏÐÐµÄerrorÏûÏ¢
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SndUpLppErrorMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU              *pstTransID,
    LPP_COMMON_IES_ERROR_ENUM_UINT8     enErrorCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
)

{
    VOS_UINT8                               *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstUpError = NAS_LPP_NULL_PTR;
    LPP_ERROR_R9_STRU                       *pstErrorR9 = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity = {0};
    VOS_UINT16 usRslt,usBitPos = 0;
    VOS_UINT32 ulLppMsgLen;


    /*·ÖÅä±àÂëÖ®ºóÂëÁ÷µÄ´æ´¢¿Õ¼ä*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("enocde up error  Alloc Mem Fail!");
        return;
    }

    /*Çå¿Õ*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);


    /*»ñÈ¡LPP MSG BUFF*/
    pstUpError = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET(pstUpError, 0, sizeof(LPP_MESSAGE_STRU));

    pstUpError->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUpError->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstUpError->bitOpLppMessageBody   = NAS_LPP_SLCT;

    if ( PS_TRUE == enNeedAck )
    {
         pstUpError->bitOpAcknowledgement  = NAS_LPP_SLCT;
         pstUpError->stAcknowledgement.bAckRequested = enNeedAck;

         /* ÎÞÐèack indicator*/
    }

    /*pstUpAbort->stTransactionId.bitOpTransactionIDExtÔÝÊ±Ã»ÓÃ£¬Ä¬ÈÏÎª0*/
    pstUpError->stTransactionId.enInitiator = pstTransID->enInitiator;
    pstUpError->stTransactionId.ucTransactionNumber = pstTransID->ucTransactionNumber;

    pstUpError->bEndTransaction = bEndTransaction;

    pstUpError->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstUpError->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUpError->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN;
    pstUpError->stLppMessageBody.u.stC1.u.stError.ulChoice = LPP_ERROR_R9_IES_CHOSEN;

    pstErrorR9 = &(pstUpError->stLppMessageBody.u.stC1.u.stError.u.stErrorR9);
    pstErrorR9->bitOpCommonIesError = NAS_LPP_SLCT;
    /*pstErrorR9->stCommonIesError.bitOpCommonIEsErrorExt =*/
    pstErrorR9->stCommonIesError.enCommonIesErrorCasue= enErrorCause;


    /*¿ªÊ¼±àÂë*/
    usRslt = NAS_LPP_EncodeMessage(pstUpError,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode LPP error msg Fail!");
        return;
    }

    ulLppMsgLen = usBitPos/8;

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransID->enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransID->ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstUpError->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_SndUplinkReqAssistDataMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SndUplinkReqAssistDataMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_BOOL                            enOtdoaAssist,
    VOS_BOOL                            enGnssAssist
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               *pucEncodeOutMsg  = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstReqAssistData = NAS_LPP_NULL_PTR;
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU     *pstRequestAsisstDataR9;
    NAS_LPP_SERVING_CELL_STRU               *pstServingCell;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity ={0};

    VOS_UINT16 usRslt,usBitPos = 0;
    VOS_UINT32 ulLppMsgLen;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        /*ÊÍ·ÅÉêÇëµÄ¶¯Ì¬ÄÚ´æ*/
        NAS_LPP_ERR_LOG1("snd assist: Don't find the session! ucSessionIndx",ucSessionIndx);
        return;
    }

    /*»ñÈ¡transactionÊµÌå*/
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /*ÊÍ·ÅÉêÇëµÄ¶¯Ì¬ÄÚ´æ*/
        NAS_LPP_ERR_LOG1("snd assist: Don't find the transaction!ucTransIndx",ucTransIndx);
        return;
    }

    pstServingCell = NAS_LPP_GetServingCell();

    /*·ÖÅä±àÂëÖ®ºóÂëÁ÷µÄ´æ´¢¿Õ¼ä*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("enocde up error  Alloc Mem Fail!");
        return;
    }

    /*Çå¿Õ*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);


    /*»ñÈ¡LPP MSG BUFF*/
    pstReqAssistData = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET(pstReqAssistData, 0, sizeof(LPP_MESSAGE_STRU));

    pstReqAssistData->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstReqAssistData->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpLppMessageBody   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpAcknowledgement  = NAS_LPP_SLCT;

    pstReqAssistData->stAcknowledgement.bAckRequested = VOS_TRUE;

     /* ÎÞÐèack indicator*/

    pstReqAssistData->bEndTransaction = VOS_FALSE;

    pstReqAssistData->stTransactionId.bitOpTransactionIDExt = NAS_LPP_NO_SLCT;
    pstReqAssistData->stTransactionId.ucTransactionNumber   = pstTransEntity->stTransId.ucTransactionNumber;
    pstReqAssistData->stTransactionId.enInitiator = LPP_INITIATOR_TYPE_TARGET_DEVICE;

    pstReqAssistData->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstReqAssistData->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN;
    pstRequestAsisstDataR9 = &pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.u.stRequestAssitDataR9;

    pstRequestAsisstDataR9->bitOpCommonIEsRequestAssitData = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.bitOpPrimaryCellID = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.ulCellIdentity = pstServingCell->ulCellIdentity;
    NAS_LPP_NasPlmn2LppPlmn(pstServingCell->aucPlmnId,
                            &pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.stPlmnIdentity);

    if (VOS_TRUE == enOtdoaAssist)
    {
        pstRequestAsisstDataR9->bitOpOTDOARequestAssistData    = NAS_LPP_SLCT;
        pstRequestAsisstDataR9->stOTDOARequestAssistanceData.usPhyCellId = pstServingCell->usPhyCellId;
    }
/*
    if (VOS_TRUE == enGnssAssist)
    {
        pstRequestAsisstDataR9->bitOpAGNSSRequestAssistData    = NAS_LPP_SLCT;
        pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.bitOpGNSSCommAssistData
        pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.bitOpGNSSGenericAssistData
        pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.stGNSSCommonAssistDataReq.
        pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.stGNSSGenericAssistDataReq
    }
*/
    /* ¿ªÊ¼±àÂë */
    usRslt = NAS_LPP_EncodeMessage(pstReqAssistData,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode assist data msg Fail!");
        return;
    }

    ulLppMsgLen = usBitPos/8;

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransEntity->stTransId.enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = pstSessionEntity->ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstReqAssistData->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(pstSessionEntity->ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    pstTransEntity->enLastUpMsgId  = NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA;
}
VOS_VOID  NAS_LPP_SndIntraLppMsg
(
    VOS_UINT32                                  ulOpId,
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity,
    NAS_LPP_ERROR_CODE_ENUM_UINT32       enErrorCode
)
{
    NAS_LPP_INTRA_DATA_CNF_STRU           *pstInterDataCnf;

    NAS_LPP_NORM_LOG("NAS_LPP_SndIntraLppMsg is entered!");

    /* ÉêÇëÄÚ´æ  */
    pstInterDataCnf = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(NAS_LPP_INTRA_DATA_CNF_STRU));
    if( NAS_LPP_NULL_PTR == pstInterDataCnf )
    {
        return;
    }

    if(NAS_LPP_NULL_PTR != pstLppMsgIdentity)
    {
        NAS_LPP_MEM_CPY(&(pstInterDataCnf->stLppMsgIdentity),
                        pstLppMsgIdentity,
                        sizeof(NAS_LPP_MSG_IDENTITY_STRU));
    }
    pstInterDataCnf->enRslt = enErrorCode;
    pstInterDataCnf->ulOpId = ulOpId;

    /*ÌîÐ´ÏûÏ¢Í·*/
    NAS_LPP_INTER_WRITE_EMM_MSG_HEAD(pstInterDataCnf, ID_NAS_LPP_INTRA_DATA_CNF);

    /*µ÷ÓÃÏûÏ¢·¢ËÍº¯Êý */
    NAS_LPP_SND_MSG(pstInterDataCnf);

    return;

}

#if 0
/*****************************************************************************
 Function Name   : NAS_LPP_SndIntraAssistDataUpdateMsg
 Description     :  ·¢ËÍÄÚ²¿µÄ¸¨ÖúÊý¾Ý¸üÐÂµÄÏûÏ¢
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SndIntraAssistDataUpdateMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
)
{
    NAS_LPP_INTRA_ASSIST_DATA_UPDATE_STRU   *pstIntraAssistDataUpdate;

    pstIntraAssistDataUpdate = (NAS_LPP_INTRA_ASSIST_DATA_UPDATE_STRU *)NAS_LPP_ALLOC_MSG(sizeof(NAS_LPP_INTRA_ASSIST_DATA_UPDATE_STRU));
    if (NAS_LPP_NULL_PTR == pstIntraAssistDataUpdate)
    {
        NAS_LPP_ERR_LOG("lpp snd assist date update msg null");
        return;
    }

    NAS_LPP_WRITE_INTRA_MSG_HEAD(pstIntraAssistDataUpdate,ID_NAS_LPP_INTRA_ASSIST_DATA_UPDATE);

    pstIntraAssistDataUpdate->ucSessionIndex = ucSessionIndx;
    pstIntraAssistDataUpdate->ucSessionTransIndex = ucSessionTransIndx;
    pstIntraAssistDataUpdate->ucTransIndex = ucTransIndx;

    NAS_LPP_SND_MSG(pstIntraAssistDataUpdate);

}
#endif


#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

