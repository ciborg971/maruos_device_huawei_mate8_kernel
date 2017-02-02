


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLppEmmMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasLppPublic.h"
#include    "NasLppSendMsg.h"
#include    "NasLppEncode.h"
#include    "NasLppOm.h"
#include    "NasLppDecode.h"
#include    "NasLppSendMsg.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



#define    THIS_FILE_ID            PS_FILE_ID_NASLPPEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPEMMMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)

static  VOS_UINT32              g_ulEmmLppOpId = 0;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e701*/

VOS_VOID  NAS_LPP_SndAllUplinkMsg(VOS_VOID)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool   = NAS_LPP_NULL_PTR;
    LPP_LMM_DATA_REQ_STRU           *pstLppDataReq      = NAS_LPP_NULL_PTR;
    LPP_LMM_DATA_REQ_STRU           *pstLppBuffDataReq  = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop             = 0;
    VOS_BOOL                         bSendFlag          = PS_FALSE;
    VOS_UINT32                       ulLength           = 0;
    VOS_UINT32                       ulUplinkIndx       = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_SndAllUplinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndAllUplinkMsg_ENUM, LNAS_LPP_SndAllUplinkMsgEnter);

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*�������index��ʹ�ñ��Ϊtrue��˵����Ӧ���������洢��������Ϣ*/
        if(PS_TRUE == pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag)
        {
            /*���л�������*/
            ulUplinkIndx = pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex;

            /*��Ӧ��������bitλ�����ˣ���˵��һ��������ֱ����Ϣ����֮*/
            if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulUplinkIndx)))
            {
                bSendFlag = pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].bSendBufFlag;
                pstLppBuffDataReq = &(pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].u.stLppDataReq);
                ulLength = pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].u.stLppDataReq.ulLength + VOS_MSG_HEAD_LENGTH;
                if(PS_FALSE == bSendFlag)
                {
                    NAS_LPP_INFO_LOG1("NAS_LPP_SndAllUplinkMsg: Send data req, pool index = !", ulUplinkIndx);
                    TLPS_PRINT2LAYER_INFO1(NAS_LPP_SndAllUplinkMsg_ENUM, LNAS_LPP_SndDataReqPoolIndex, ulUplinkIndx);
                    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU*)NAS_LPP_ALLOC_MSG(ulLength);
                    if(NAS_LPP_NULL_PTR == pstLppDataReq)
                    {
                        return;
                    }
                    NAS_LPP_MEM_CPY(pstLppDataReq,
                                    pstLppBuffDataReq,
                                    ulLength);

                    /*��ȡ�ɹ�������û�з��ͳɹ���������÷��ͺ�������dataReq��LMM*/
                    NAS_LPP_SND_MSG(pstLppDataReq);
                }
            }
        }
    }

    return;
}


VOS_VOID  NAS_LPP_ConnFailHandle(VOS_VOID)
{
    NAS_LPP_INFO_LOG("NAS_LPP_ConnFailHandle enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ConnFailHandle_ENUM, LNAS_LPP_ConnFailHandleEnter);

    NAS_LPP_SndIntraLppMsg(0, NAS_LPP_NULL_PTR, NAS_LPP_CONN_MANAGE_FAIL);
    NAS_LPP_ClearLppTransCnt();
    NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_IDLE);

    return;
}


VOS_VOID  NAS_LPP_RcvLppEmmEstCnf(const LMM_LPP_EST_CNF_STRU *stEstCnf)
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvLppEmmEstCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfEnter);

    /*ֹͣ������ʱ��*/
    NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                      NAS_LPP_TIMER_INVAILD_PARA,
                      TI_NAS_LPP_WAIT_EST_CNF);

    switch (stEstCnf->ulEstRst)
    {
        case LMM_LPP_EST_RESULT_SUCC:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: EST SUCC, Start Send Uplink Buffer Msg!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfEstSucc);

            /*�����ɹ�������ǰ������״̬�ó�CONNECT*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_CONNECT);

            /*����ȥȡ���л���buffer�е�ֱ����Ϣ�����͸�LMM*/
            NAS_LPP_SndAllUplinkMsg();

            /*��մ������Ϊ0*/
            NAS_LPP_ClearLppTransCnt();
            break;

        case LMM_LPP_EST_RESULT_FAIL_3411_RUNNING:
            /*3411���������У���10s֮���ٴγ��Է�����*/
            /*���ʣ��������һ����ʱ��ȥȡ��ͬ�ĳ�ʱʱ��*/
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: 3411 running!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnf3411Running);
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8,10000);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        case LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: sevice fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfServiceFail);
            /*SERVICER FAIL��������2s���ٳ��Է�����*/
            /*����ʧ�ܵĳ����������ؽ���*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, 2000);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        default:
            /*��������֮���״̬�����ٷ�������ֱ��֪ͨ��ֹ��ǰ����*/
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: No 3411 and sevice fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfBeside3411AndServiveFail);
            NAS_LPP_ConnFailHandle();
            break;
    }

    return;
}
NAS_LPP_MSG_IDENTITY_STRU*  NAS_LPP_GetLppMsgIndentityByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU       *pstLppMsgIndentity = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            NAS_LPP_INFO_LOG2("NAS_LPP_GetLppMsgIndentityByOpId: SOpid, DOpid!,", ulOpId, ulLmmLppOpId);
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppMsgIndentityByOpId_ENUM, LNAS_LPP_GetLppMsgIndentityByOpIdSourceOpId, ulOpId);
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppMsgIndentityByOpId_ENUM, LNAS_LPP_GetLppMsgIndentityByOpIdDestinationOpId, ulLmmLppOpId);
            if(ulOpId == ulLmmLppOpId)
            {
                pstLppMsgIndentity = &(pstUpMsgBuffPool->astLppUpMsg[ulLoop].stLppMsgIdentity);
                break;
            }
        }

    }

    return pstLppMsgIndentity;
}


LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                return  &(pstUpMsgBuffPool->astLppUpMsg[ulLoop]);
            }
        }

    }

    return NAS_LPP_NULL_PTR;
}



VOS_BOOL  NAS_LPP_GetLppMsgSendFlagByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;
    VOS_BOOL                         bSendFlag        = PS_FALSE;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                bSendFlag = pstUpMsgBuffPool->astLppUpMsg[ulLoop].bSendBufFlag;
            }
        }

    }

    return bSendFlag;
}


VOS_VOID  NAS_LPP_SetLppMsgSendFlagByOpId
(
    VOS_UINT32                  ulLmmLppOpId,
    VOS_BOOL                    bLppSendFlag
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                pstUpMsgBuffPool->astLppUpMsg[ulLoop].bSendBufFlag = bLppSendFlag;

                return;
            }
        }

    }

    return;
}



VOS_BOOL  NAS_LPP_IsAckDataCnf
(
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity
)
{
    if(NAS_LPP_UPLINK_MSG_TYPE_ACK == pstLppMsgIdentity->enUplinkMsgType)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


VOS_VOID  NAS_LPP_AckDataCnfSuccHandle
(
    VOS_UINT32          ulOpId
)
{
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_AckDataCnfSuccHandle is entered!");

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        return;
    }

    NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);

    return;
}


VOS_VOID  NAS_LPP_RcvLppEmDataCnf(const LMM_LPP_DATA_CNF_STRU *pstDataCnf)
{
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity  = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvLppEmDataCnf_ENUM, LNAS_LPP_RcvLppEmDataCnfResult, pstDataCnf->enDataCnfRst);

    switch (pstDataCnf->enDataCnfRst)
    {
        case LMM_LPP_SEND_RSLT_SUCCESS:
            /*
            ֱ���ɹ��������ڲ���Ϣ����Ӧ��transaction�������ش���ʱ����ͬʱ����Ӧ
            bufferָ������ΪNULL,��ʾ��ǰû�в���ʹ�ø�buffer
            */
            NAS_LPP_ClearLppTransCnt();
            /*ֱ���ɹ�,�����ڲ���Ϣ֪ͨtransaction�����ҽ�sendFlag���ó�TRUE*/
            pstLppMsgIdentity = NAS_LPP_GetLppMsgIndentityByOpId(pstDataCnf->ulOpId);
            if(NAS_LPP_NULL_PTR == pstLppMsgIdentity)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmDataCnf: don't find the LppMsgIndentity!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmDataCnf_ENUM, LNAS_LPP_RcvLppEmDataCnfDontFindUpBuff);

                return;
            }

            /*�����ǰ��Ϣ����ACK��Ϣ�Ļظ�����ôɾ����Ӧ������buffer�Ļ�����Ϣ*/
           /* if(PS_TRUE == NAS_LPP_IsAckDataCnf(pstLppMsgIdentity))
            {
                NAS_LPP_AckDataCnfSuccHandle(pstDataCnf->ulOpId);
                break;
            }*/

            NAS_LPP_SndIntraLppMsg( pstDataCnf->ulOpId, pstLppMsgIdentity, NAS_LPP_SUCCESS);

            /*��ֱ��buffer��SendFlag�ó�TRUE*/
            NAS_LPP_SetLppMsgSendFlagByOpId(pstDataCnf->ulOpId, PS_TRUE);

            break;

        case LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST:
            if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
            {
                /*��������û�дﵽ��󣬷�����*/
                NAS_LPP_LppLmmEstReq();

                /*����������ʱ��*/
                NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                                  NAS_LPP_TIMER_INVAILD_PARA,
                                  TI_NAS_LPP_WAIT_EST_CNF);

                /*���������1*/
                NAS_LPP_TransLppMsgAddCnt();
            }
            else
            {
                /*���������ﵽ��������֪ͨSession�ͷ����е���Դ*/
                NAS_LPP_ConnFailHandle();
            }
            break;

        case LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL:
            /*�ײ���󣬵ȴ�2s֮������*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, NAS_LPP_LOW_LAYER_FAIL_RE_REST_TIME_LEN);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        case LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING:
            /*��ʮ�����ٷ�����*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, NAS_LPP_3411_FAIL_RE_REST_TIME_LEN);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        default:
            /*��������֮���״̬�����ٷ�������ֱ��֪ͨ��ֹ��ǰ����*/
            NAS_LPP_ConnFailHandle();
            break;
    }

    return;
}


VOS_UINT32  NAS_LPP_CheckEcidDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{

    NAS_LPP_NORM_LOG("NAS_LPP_CheckEcidDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckEcidDownLinkMsg_ENUM, LNAS_LPP_CheckEcidDownLinkMsgEnter);

    /*ECID The field is optionally present, need ON, if ECID is requested. Otherwise it is not present.*/
    /*��������������ϱ�����ôһ����ECID�Ķ�λ������������������Ķ�λ����������Ϊ�Ǵ���*/
    if((NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria)
       && ((NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpOtdoaReqLocationInfo)
       || (NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpAGNSSReqLocationInfo)))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckEcidDownLinkMsg,LPP msg body: Tigger report NOT for OTDOA&GNSS!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckEcidDownLinkMsg_ENUM, LNAS_LPP_CheckEcidDownLinkMsgTiggerReportNotForOtdoaAndGnss);

        return NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR;
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}


VOS_UINT32  NAS_LPP_CheckCommomDownLinkMsg(LPP_MESSAGE_STRU *pstLppMsg)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU  *pstReqLocInfoR9Ies = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_CheckCommomDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgEnter);

    /*��Ϣͷ�ļ��*/
    /*�����ǰ������Ϣ�壬��transactionID��sequenceNumberһ������*/
    if((NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
       && ((NAS_LPP_NO_SLCT == pstLppMsg->bitOpLppTransactionId)
       || (NAS_LPP_NO_SLCT == pstLppMsg->bitOpSequenceNumber)))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckCommomDownLinkMsg,LPP msg body: No transId or sequence Number!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgLppMsgBodyNoTransIdOrSequenceNumber);

        return NAS_LPP_MSG_VERIFY_HEAD_FAIL;
    }

    /*�����ǰ��������Ϣ�壬����Ŀǰ��Э��汾��˵����ô����Ϣһ����ACK��Ϣ*/
    if((NAS_LPP_NO_SLCT == pstLppMsg->bitOpLppMessageBody)
      && ((NAS_LPP_NO_SLCT == pstLppMsg->bitOpAcknowledgement)
      || ((NAS_LPP_SLCT == pstLppMsg->bitOpAcknowledgement)
      && (NAS_LPP_NO_SLCT == pstLppMsg->stAcknowledgement.bitOpAckIndicator))))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckCommomDownLinkMsg,Ack Msg: No Ack or Have Ack but no AckIndicatior!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgAckMsgNoAckOrHaveAckButNoAckindicatior);

        return NAS_LPP_MSG_VERIFY_HEAD_FAIL;
    }

    if ( (NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
       &&(LPP_C1_MESSAGE_BODY_CHOSEN == pstLppMsg->stLppMessageBody.ulChoice)
       &&(LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN == pstLppMsg->stLppMessageBody.u.stC1.ulChoice) )
    {
        /*�����ϱ���ʽ�ļ��*/
        pstReqLocInfoR9Ies = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);
        if(NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpCommonIEsReqLocationInfo)
        {

            /*���Ҫ���������Ե��ϱ�����Ҫ������ϱ�һ���Լ������ϱ�����Ϣ*/
            if(NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpPeriodicalReportCriteria)
            {
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria =
                                                                                    NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stTriggerReportCriteria),
                                0,
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));

                /*����ϱ�һ�γ�������Ϣ*/
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.bitOpResponseTime = NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.stResponseTime),
                                0,
                                sizeof(LPP_MTA_COMMON_RESPONSE_TIME_STRU));
            }

            /*������ϱ�һ�εĳ�������Ҫ����������ϱ��ĳ���*/
            if((NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpQos)
                    && (NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.bitOpResponseTime))
            {
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria =
                                                                                    NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stTriggerReportCriteria),
                                0,
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));
            }

            /*�Ȳ����������ϱ����ֲ����ϱ�һ�εĳ�������һ���Ǵ����ϱ��ĳ���*/
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}


VOS_UINT32  NAS_LPP_CheckOtdoaDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{
    /*TODO*/
    return NAS_LPP_MSG_VERIFY_SUCC;
}
VOS_UINT32  NAS_LPP_CheckGnssDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{
    /*TODO*/
    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_CheckOtdoaNeighbourCell
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckOtdoaNeighbourCell
(
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU   *pstOtdoaNeighbourCellInfo,
    VOS_UINT32                           ulRefArfcn)
{
    VOS_UINT32 ulLoop,ulLoop1,ulEarfcn; /* referrencr earfcn���ﲻ��Ҫ֪����ȷ�Ĵ�С��ֻ����Ϊһ���ȽϵĻ�׼ֵ����*/

    if (pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt > LPP_MAX_FREQ_LAYERS_LEN)
    {
        NAS_LPP_ERR_LOG1("otdoa neighbor cell freq cnt overflow", pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighborCellFreqCntOverflow);

        return NAS_LPP_MSG_VERIFY_FAIL;
    }


    /* ǰ������:neighbour list��֧��additional neighbor list*/
    /*neighbour listÿ��Ƶ�ʲ����С����Ƶ��Ҫһ��*/
    for ( ulLoop = 0 ; ulLoop < pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt; ulLoop++ )
    {
        if (pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt > LPP_MAX_OTDOA_NEIGHBOUR_CELL_INFO_ELMENT_LEN)
        {
            NAS_LPP_ERR_LOG2("otdoa neighbor cell cell cnt overflow",
                             ulLoop,
                             pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoop, ulLoop);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoopCnt,
                                                pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);

            return NAS_LPP_MSG_VERIFY_FAIL;
        }

        /*ÿ��Ƶ��ĵ�һ��С��Ƶ��*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            ulEarfcn = ulRefArfcn;
        }


        for ( ulLoop1 = 1 ;
              ulLoop1 < pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;
              ulLoop1++ )
        {
            /*����ÿ��С����Ƶ��Ҫ����һ��:�Ƚϵ�n���͵�(n-1)��*/
            if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcn)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcn.ulArfcnValueEUTRA )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcnV9a0)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcnv9a0.ulArfcnValueEUTRAv9a0 )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor v9a0 cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else
            {
                /*ÿ��С����Ƶ�㶼������ȷ˵��*/
                if ( ulEarfcn != ulRefArfcn )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor ref cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
                else
                {
                }
            }

        }
    }


    return NAS_LPP_MSG_VERIFY_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetRefEarfcnFromOtdoaAssis
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetRefEarfcnFromOtdoaAssis( LPP_OTDOA_REF_CELL_INFO_STRU  *pstOtdoaRefCellInfo )
{
    VOS_UINT32 ulEarfcn;

    /*36.355  earfcnRef					ARFCN-ValueEUTRA			OPTIONAL,		-- Cond NotSameAsServ0
      This field is absent if earfcnRef-v9a0 is present. Otherwise, the field is mandatory present if the EARFCN of
      the OTDOA assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarFcnRef)
    {
         ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRef.ulArfcnValueEUTRA;
    }
    /*earfcnRef-v9a0			ARFCN-ValueEUTRA-v9a0		OPTIONAL		-- Cond NotSameAsServ2
      The field is absent if earfcnRef is present. Otherwise, the field is mandatory present if the EARFCN of the OTDOA
      assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    else if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcnRefV9a0)
            &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stEarfcnRefV9a0.bitOpARFCNValueEutraV9A0) )
    {
        ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRefV9a0.ulArfcnValueEUTRAv9a0;
    }
    /* ���bitOpEarFcnRef��bitOpEarfcnRefV9a0������,ʹ��serving cell��*/
    else
    {
        ulEarfcn = NAS_LPP_GetServingCell()->ulEarfcn;
    }

    return ulEarfcn;

}
/*****************************************************************************
 Function Name   : NAS_LPP_CheckAssisData
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckAssisData( LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU *pstProvideAssistanceData )
{
    LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU *pstProvideAssitDataR9;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU       *pstOtdoaAssisCfg;
    VOS_UINT32 ulRslt;

    pstProvideAssitDataR9 = &(pstProvideAssistanceData->u.stC1.u.stProvideAssitDataR9);

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    /* ����neighbour cell list��֧�� addtional neighbour list�����ԣ����е���ͬƵ���С��������һ��frequency cell ���*/
    if ( (NAS_LPP_SLCT == pstProvideAssistanceData->u.stC1.u.stProvideAssitDataR9.bitOpOTDOAProvideAssistData)
       &&(NAS_LPP_SLCT == pstProvideAssitDataR9->stOTDOAProvideAssistanceData.bitOpOtdoaNeighbourCellInfo) )
    {
        if ( LPP_LRRC_INFO_FLAG_VALID == pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag )
        {
            ulRslt = NAS_LPP_CheckOtdoaNeighbourCell(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaNeighbourCellInfo,
                                                     pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn);
            if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_CheckAssisData fail");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckAssisData_ENUM, LNAS_LPP_CheckOtdoaNeighbourCellFail);
                return ulRslt;
            }
        }
        else if ( NAS_LPP_SLCT ==pstProvideAssitDataR9->stOTDOAProvideAssistanceData.bitOpOtdoaReferenceCellInfo )
        {
            ulRslt = NAS_LPP_CheckOtdoaNeighbourCell(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaNeighbourCellInfo,
                                                     NAS_LPP_GetRefEarfcnFromOtdoaAssis(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaRefCellInfo) );
            if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_CheckAssisData fail1");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckAssisData_ENUM, LNAS_LPP_CheckOtdoaNeighbourCellFail1);
                return ulRslt;
            }
        }
        else
        {
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_CheckAssisDataAfterSave
 Description     :  �ڴ洢��֮���鸨������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckOtdoaAssisDataAfterSave( VOS_VOID )
{
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg;
    NAS_LPP_SERVING_CELL_STRU               *pstServingCell;
    LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU *pstNeighborFreqInfo;
    VOS_UINT32 ulLoop = 0,ulLoop1 = 0;

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();
    pstServingCell   = NAS_LPP_GetServingCell();

    NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave enter");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_CheckOtdoaAssisDataAfterSaveEnter);

    /*1������Ҫ2��С��:ref С����neighborС����Ҫ���ڣ�
       2��ref + neighbor��Ҫ����primary cell
       3��neighbor cell��Ƶ�������Ҫ����3��*/
    /*36.355 6.5.11
    The location server should include at least one cell for which the SFN can be obtained by the target device,
    e.g. the serving cell, in the assistance data, either as the assistance data reference cell or in the neighbour cell list.
    Otherwise the target device will be unable to perform the OTDOA measurement and the positioning operation will fail.*/
    if ( (LPP_LRRC_INFO_FLAG_VALID != pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag)
       ||(LPP_LRRC_INFO_FLAG_VALID != pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag) )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: ucOtdoaReferenceCellInfoFlag or ucOtdoaNeighbourCellInfoFlag inValid");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_RefCellOrNeighbourCellInValid);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    if ( (pstServingCell->usPhyCellId == pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.usPhyCellId)
       &&(pstServingCell->ulEarfcn == pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn) )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: Servie Cell Not in Reference Cell");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_ServiceCellNotRefCell);
        return NAS_LPP_MSG_VERIFY_SUCC;
    }

    for ( ulLoop = 0 ; ulLoop < pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum; ulLoop++ )
    {
        pstNeighborFreqInfo = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop];
        for ( ulLoop1 = 0 ; ulLoop1 < pstNeighborFreqInfo->ulCellNum; ulLoop1++ )
        {
            if ( (pstServingCell->usPhyCellId == pstNeighborFreqInfo->stOtdoaNeighbourCellInfoList[ulLoop1].usPhyCellId)
               &&(pstServingCell->ulEarfcn == pstNeighborFreqInfo->ulEarfcn) )
            {
                break;
            }
        }

        /* ������Ƶ�����ҵ�*/
        if (ulLoop1 < pstNeighborFreqInfo->ulCellNum)
        {
            break;
        }
    }

    /* ���û�ҵ�*/
    if (ulLoop >= pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: Servie Cell Not in Reference Cell1");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_ServiceCellNotRefCell1);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CheckGnssAssisDataAfterSave
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckGnssAssisDataAfterSave( VOS_VOID )
{
    return NAS_LPP_MSG_VERIFY_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CheckReqLocationInfo
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckReqLocationInfo( LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU *pstRequestLocationInformation )
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocationInfoR9;
    VOS_UINT32 ulRslt = NAS_LPP_MSG_VERIFY_SUCC;

    pstReqLocationInfoR9 = &pstRequestLocationInformation->u.stC1.u.stReqLocationInfoR9;
    NAS_LPP_INFO_LOG("NAS_LPP_CheckReqLocationInfo");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoEnter);

    /*У��ECID����asn����Ƿ���ȷ*/
    ulRslt = NAS_LPP_CheckEcidDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckReqLocationInfo: ECID CHECK ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoEcidCheckError);
        return ulRslt;
    }

    /*У��otdoa����asn����Ƿ���ȷ*/
    ulRslt = NAS_LPP_CheckOtdoaDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckReqLocationInfo: otdoa CHECK ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoOtdoaCheckError);
        return ulRslt;
    }

    /*У��gnss����asn����Ƿ���ȷ*/
    ulRslt = NAS_LPP_CheckGnssDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        return ulRslt;
    }
    return NAS_LPP_MSG_VERIFY_SUCC;
}
VOS_UINT32  NAS_LPP_CheckDownLinkMsg(LPP_MESSAGE_STRU *pstLppMsg)
{
    VOS_UINT32              ulRslt = NAS_LPP_MSG_VERIFY_SUCC;
    VOS_UINT32              ulMsgType;

    /*��Ϣͷ�ļ��*/
    /*�����ϱ���ʽ�ļ��*/
    /*��������������ϱ�����ôһ����ECID�Ķ�λ������������������Ķ�λ����������Ϊ�Ǵ���*/
    NAS_LPP_NORM_LOG("NAS_LPP_CheckDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_CheckDownLinkMsg_ENUM, LNAS_LPP_CheckDownLinkMsgEnterType, pstLppMsg->stLppMessageBody.u.stC1.ulChoice);

    /*У�鹫��������asn�Ƿ���ȷ*/
    ulRslt = NAS_LPP_CheckCommomDownLinkMsg(pstLppMsg);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckDownLinkMsg: COMMON CHECK FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckDownLinkMsg_ENUM, LNAS_LPP_CheckDownLinkMsgCommonCheckFail);
        return ulRslt;
    }

    /*�������û��msg body��ֱ���˳�*/
    if ( NAS_LPP_SLCT != pstLppMsg->bitOpLppMessageBody)
    {
        return ulRslt;
    }

    /*����ֱ���request capability/request location information/assistant data/down abort/down error*/
    ulMsgType = pstLppMsg->stLppMessageBody.u.stC1.ulChoice;
    switch ( ulMsgType )
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN :
            /*������*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN :
            ulRslt = NAS_LPP_CheckAssisData(&pstLppMsg->stLppMessageBody.u.stC1.u.stProvideAssistanceData);
            /*otdoa��assist data��transaction����ʱ���*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN :
            ulRslt = NAS_LPP_CheckReqLocationInfo(&pstLppMsg->stLppMessageBody.u.stC1.u.stRequestLocationInformation);
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN :
            /*������*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN :
            /*������*/
            break;
        default:
            break;
    }

    return ulRslt;
}


VOS_VOID NAS_LPP_RcvAckTransInLocationProvideProcess
(
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8 enLocationReportType,
    VOS_UINT8                               ucTransIndx,
    VOS_UINT8                               ucSessionIndex,
    VOS_UINT8                               ucSessionTransIndx
)
{
    /*��������֧���Ժϲ�����ʱ���������߼�����Ϊ���û���ϱ���ʽ���в�ͬ�Ĵ���*/
    NAS_LPP_INFO_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess enter!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_enLocationReportType, enLocationReportType);

    switch(enLocationReportType)
    {
        case NAS_LPP_REPORT_LOCATION_TYPE_ONCE:
            /*�����ֻ�ϱ�һ�εĳ�������ô���뵽�����֧һ�����쳣��
              ��ΪprovideLocationInformation�Ѿ���endtransactionFlag�ó�true��
            */
            NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess: Report ONCE abnormal!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_RcvAckTransInLocationProvideProcessReportOnceAbnormal);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_PERIOD:
            /*
            �����Դ�������������������֧����˵����ǰ�ϱ�����һ��û�дﵽ����, �����
            ����ֻ��Ҫ����transaction��״̬ת�ɵȲ���IND����(ͬʱֹͣ�ش���ʱ��)�������Զ�ʱ��
            ��ʱʱ����Ȼ�����provideLocation�������࣬ͬʱ���������Զ�ʱ����ֱ�������ﵽ����
            */
            NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER:
           /*
            ������������������������֧����˵����ǰduration�ϱ���ʱ��û�г�ʱ��������������ƣ�
            ����transaction��״̬ת��IDLE���ɣ�duration��ʱ����ʱ����Ȼ�����provide�������࣬
            ֱ��duration����
           */
           NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
           break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess: Report Type Error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_ReportTypeError);
            break;
    }
}


VOS_VOID NAS_LPP_RcvAckTransNotEndHandle
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity          = NAS_LPP_NULL_PTR;
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enReportLocationType    = 0;



    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: Don't find Transaction!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransNotEndHandle_ENUM, LNAS_LPP_DontFindTransaction);

        return;
    }

    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvAckTransNotEndHandle_ENUM, LNAS_LPP_enLastUpMsgId, pstTransEntity->enLastUpMsgId);

    switch(pstTransEntity->enLastUpMsgId)
    {
        case    NAS_LPP_AIR_MSG_PROVIDE_CAP:
                /*
                  �����һ�������ṩ������Ϣ�����࣬�����ʱtransactionӦ�ý�����
                  ����������ǽ����������֧��˵��transactionʵ����û�н�transaction
                  ���û�н����������쳣����¼һ�£���Ϊ�쳣����
                */
                NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: CapProvdie Process abnormal!");
                break;

        case    NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA:
                /*��һ������ӣ��յ�������Ϣ�����ACK��ͣ�ش���ʱ����ת��������ศ�����ݵȲ���*/
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_ASSISTDATA, LPP_SS_ASSISTDATA_WAIT_CN_CNF);
                break;

        case    NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO:
                /*�����һ�������ṩλ����Ϣ�����࣬��ô��Ҫ���ݵ�ǰ�ϱ���ʽ�������Ի�����������������
                �����ϱ�һ��*/
                /*��ȡ�ϱ�λ����Ϣ����*/
                enReportLocationType = NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx);
                NAS_LPP_RcvAckTransInLocationProvideProcess(enReportLocationType,
                                                            ucTransIndx,
                                                            ucSessionIndx,
                                                            ucTransIndx);
                break;

        case    NAS_LPP_AIR_MSG_UP_ERR:
                /*�ֽ׶β���ERR��Ϣ��ACK���ƣ���ʱԤ��*/
                break;

        case    NAS_LPP_AIR_MSG_UP_ABORT:
                /*Abort*/
                NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: Abort Process abnormal!");
                break;

        default:
            break;
    }
}
VOS_VOID NAS_LPP_NwMsgWithAckIeHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId
)
{
    LPP_UPLINK_MSG_BUF_STRU                    *pstUplinkMsgBuf         = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionTransIndx      = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity          = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionIndx           = 0;
    VOS_UINT8                                   ucTransIndx             = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_NwMsgWithAckIeHandle enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_Func_Enter);

    /*�������л���buffer*/
    pstUplinkMsgBuf = NAS_LPP_FindUpLinkBuffer(
                                    pstMsgHead->stAcknowledgement.stAckIndicator.ucSequenceNumber,
                                    ulSessionId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuf)
    {
        /*�ӱ���������ڿգ������л�����û���ҵ���Ӧ��Ϣ����*/
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgWithAckIeHandle: Don't find UpLink buffer Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_DontFindUplinkBufferMsg);

        return;
    }

    /*ͨ��buffer����е�identity�ҵ���Ӧtransactionʵ��*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(pstUplinkMsgBuf->stLppMsgIdentity.ulSessionId);
    NAS_LPP_SearchTransEntityIndx(ucSessionIndx,
                                  &(pstUplinkMsgBuf->stLppMsgIdentity.stTransId),
                                  &ucTransIndx,
                                  &ucSessionTransIndx);

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgWithAckIeHandle: Don't find Transaction!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_DontFindTransaction);
        return;
    }

    /*
      �ҵ���transactionʵ�壬�������˸�transaction������
      ���ͷ�transaction����Դ������clear��صĲ���
    */
    if(NAS_LPP_TRANS_END == pstTransEntity->ucTransEndFlag)
    {
        /*����Ӧ��transaction��λ���ṩ�����������һ����Ϣ�����ҵ�ǰsessionû��������transaction����running location�� ����Ҫ��session*/
        if( PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndx,&(pstUplinkMsgBuf->stLppMsgIdentity.stTransId)) )
        {
            NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle:No running transaction, Release this session!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_NoRunningTransReleaseSession);
            NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
        }
        else
        {
            NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle: Have other transaction, Just release this Transaction!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_HaveOtherTransJustReleaseThisTrans);
            NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
        }
    }
    else
    {
        /*transaction��û�н���*/
        /* ����ش����������Ϣ���յ�ACK������Ҫ����ش������������������������Ϣ��ACK����ش����� */
        pstTransEntity->ucRetranNum = 0;
        NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle: Transaction don't end!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_TransDontEnd);
        NAS_LPP_RcvAckTransNotEndHandle(ucSessionIndx, ucTransIndx, ucSessionTransIndx);
        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuf);
    }

    return;
}
VOS_VOID NAS_LPP_EncodeAckMsgWithMsgIndentiy
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppHead,
    VOS_UINT32                         *pulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_MSG_HEAD_STRU  *pstUplinkAckMsg = NAS_LPP_NULL_PTR;
    VOS_UINT16              usRslt          = 0;
    VOS_UINT16              usBitPos        = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_EncodeAckMsgWithMsgIndentiy enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeAckMsgWithMsgIndentiy_ENUM, LNAS_LPP_Func_Enter);


    pstUplinkAckMsg = NAS_LPP_MEM_ALLOC(sizeof(NAS_LPP_MSG_HEAD_STRU));
    if(NAS_LPP_NULL_PTR == pstUplinkAckMsg)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeAckMsgWithMsgIndentiy: Alloc mem fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeAckMsgWithMsgIndentiy_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }
    NAS_LPP_MEM_SET(pstUplinkAckMsg, 0, sizeof(NAS_LPP_MSG_HEAD_STRU));

    /*����׼��*/
    pstUplinkAckMsg->bitOpAcknowledgement = NAS_LPP_SLCT;
    pstUplinkAckMsg->stAcknowledgement.bAckRequested = PS_FALSE;
    pstUplinkAckMsg->stAcknowledgement.bitOpAckIndicator = NAS_LPP_SLCT;
    pstUplinkAckMsg->stAcknowledgement.stAckIndicator.ucSequenceNumber =
                                    pstLppHead->stSequenceNumber.ucSequenceNumber;
    pstUplinkAckMsg->bEndTransaction = PS_FALSE;
    /*
    ����transactionId��ACK��Ϣ�а���Э��Ҫ����Ҫ�������ǲο����޵µ�trace��
    Ҳ��transaction���������ˣ�����Ŀǰʵ��Ҳ�ǽ����������
    */
    pstUplinkAckMsg->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUplinkAckMsg->stTransactionId.enInitiator =
                                    pstLppHead->stTransactionId.enInitiator;
    pstUplinkAckMsg->stTransactionId.ucTransactionNumber =
                                    pstLppHead->stTransactionId.ucTransactionNumber;

    /*��ʼ����*/
    usRslt = NAS_LPP_EncodeMessage((LPP_MESSAGE_STRU*)pstUplinkAckMsg,
                                   &usBitPos,
                                    pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeAckMsgWithMsgIndentiy: Encode Ack msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeAckMsgWithMsgIndentiy_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        NAS_LPP_MEM_FREE(pstUplinkAckMsg);
        return;
    }
    *pulLppMsgLen = usBitPos/8;

    /*���������Ϣ���ʶ����Ϣ*/
    pstLppMsgIdentity->ulSessionId                      = ulSessionId;
    pstLppMsgIdentity->stTransId.enInitiator            =
                                pstUplinkAckMsg->stTransactionId.enInitiator;
    pstLppMsgIdentity->stTransId.ucTransactionNumber    =
                                pstUplinkAckMsg->stTransactionId.ucTransactionNumber;
    pstLppMsgIdentity->enUplinkMsgType                  =
                                NAS_LPP_UPLINK_MSG_TYPE_ACK;

    /*�ͷŶ�̬������ڴ�*/
    NAS_LPP_MEM_FREE(pstUplinkAckMsg);

    /*����ɹ�*/
    return;
}


VOS_VOID NAS_LPP_SaveUpMsgBufferIndex(VOS_UINT8 ucUplinkBuffIndx)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    VOS_UINT32                      ulLoop              = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_SaveUpMsgBufferIndex Enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveUpMsgBufferIndex_ENUM, LNAS_LPP_Func_Enter);

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*�����ǰindexû�б�ռ�ã���index��ֵ�洢����λ��*/
        if(PS_FALSE == pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag)
        {
            pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        = PS_TRUE;
            pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex = ucUplinkBuffIndx;
            break;
        }
    }

    NAS_LPP_OmUpMsgBuffMallocSuccInd(ucUplinkBuffIndx, pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
}

/*lint -e661*/
/*lint -e662*/

VOS_UINT16 NAS_LPP_PushUplinkMsgToBuff
(
    VOS_UINT32                          ulDataReqSize,
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
)
{
    LPP_UPLINK_MSG_BUF_STRU            *pstUplinkMsgBuf     = NAS_LPP_NULL_PTR;
    VOS_UINT8                           ucUpLinkBuffIndx    = PS_NULL_UINT8;
    VOS_UINT8                           ucLoop              = 0;
    VOS_BOOL                            bHaveSameProLocFlag = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU      *pstUpMsgBufPool = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_PushUplinkMsgToBuff enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_Func_Enter);

    /*
      ������buffer�������Ϣ�������ǰ����������µ�provideLocation��Ϣ���͸�����࣬�����µĸ��Ǿɵģ�
      ע��:ע�ⲻҪ����
    */
    pstUpMsgBufPool = NAS_LPP_GetLppUpMsgBuffPool();

    if(PS_TRUE == pstLppMsgIdentity->bIsProvideLocFalg)
    {
        for(ucLoop = 0; ucLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ucLoop++)
        {
            /*����Ѿ���������е���Ϣ�����Session��transaction��ͬ��������ProvideLocation��Ϣ�����һ�û�з��ͳɹ�������Ϊ���л����Ѿ�����
              һ��provideLocation��Ϣ�����ͣ���ʱ����Ҫ���µĸ��Ǿɵ���Ϣ
            */
            if((pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.ulSessionId == pstLppMsgIdentity->ulSessionId)
               && (pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.stTransId.ucTransactionNumber == pstLppMsgIdentity->stTransId.ucTransactionNumber)
               && (pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.stTransId.enInitiator == pstLppMsgIdentity->stTransId.enInitiator)
               && (PS_TRUE == pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.bIsProvideLocFalg)
               && (NAS_LPP_UPLINK_MSG_TYPE_PROCESS == pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.enUplinkMsgType)
               && (PS_FALSE == pstUpMsgBufPool->astLppUpMsg[ucLoop].bSendBufFlag))
            {
                NAS_LPP_WARN_LOG("NAS_LPP_PushUplinkMsgToBuff: Use New ProvideLocation Msg!");
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_UseNewProvideLocationMsg);

                bHaveSameProLocFlag = PS_TRUE;
                ucUpLinkBuffIndx    = ucLoop;
                break;
            }
        }
    }

    if(PS_FALSE == bHaveSameProLocFlag)
    {
        /*û����ͬ�Ļ������Ϣ�������µĻ���buffer*/
        pstUplinkMsgBuf = NAS_LPP_MallocUpMsgBuffer(&ucUpLinkBuffIndx);
        if(NAS_LPP_NULL_PTR == pstUplinkMsgBuf)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_PushUplinkMsgToBuff: Can't alloc UpMsg buffer!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_CanntAllocUpMsgBuffer);
            return  NAS_LPP_FAILURE;
        }
    }
    else
    {
        /*����ͬ�Ļ�����Ϣ��ֱ�Ӹ���֮*/
        pstUplinkMsgBuf = &(pstUpMsgBufPool->astLppUpMsg[ucUpLinkBuffIndx]);
    }

    /*�������л����������Ϣ*/
    NAS_LPP_SaveUpMsgBufferIndex(ucUpLinkBuffIndx);

    NAS_LPP_MEM_CPY(&(pstUplinkMsgBuf->stLppMsgIdentity),
                    pstLppMsgIdentity,
                    sizeof(NAS_LPP_MSG_IDENTITY_STRU));
    pstUplinkMsgBuf->bSendBufFlag = PS_FALSE;
    NAS_LPP_MEM_CPY(&(pstUplinkMsgBuf->u.stLppDataReq),
                    pstLppDataReq,
                    ulDataReqSize);

    return      NAS_LPP_SUCCESS;
}
/*lint +e662*/
/*lint +e661*/

VOS_UINT32  NAS_LPP_AllocEmmLppOpId( VOS_VOID )
{
    g_ulEmmLppOpId++;
    if(g_ulEmmLppOpId  == NAS_LMM_LPP_OPID_NOT_VAILID)
    {
        g_ulEmmLppOpId = 0;
    }
    return  (g_ulEmmLppOpId);
}


VOS_VOID NAS_LPP_FillWithLppDataReqMsg
(
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_WARN_LOG("NAS_LPP_FillWithLppDataReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_FillWithLppDataReqMsg_ENUM, LNAS_LPP_Func_Enter);

    /*��д�տ���Ϣͷ����*/
    pstLppDataReq->ulSessionId              = ulSessionId;
    pstLppDataReq->ulOpId                   = NAS_LPP_AllocEmmLppOpId();

    pstLppDataReq->stLppMsg.ulLppMsgSize    = ulLppMsgLen;
    NAS_LPP_MEM_CPY(pstLppDataReq->stLppMsg.aucLppMsg,
                    pucEncodeOutMsg,
                    ulLppMsgLen);

    /*��д��Ϣͷ*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstLppDataReq, ID_LPP_LMM_DATA_REQ);

    return;
}


VOS_VOID NAS_LPP_LppLmmEstReq( VOS_VOID )
{
    LPP_lMM_EST_REQ_STRU               *pstEstReqMsg;

    NAS_LPP_NORM_LOG("NAS_LPP_LppLmmEstReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmEstReq_ENUM, LNAS_LPP_Func_Enter);

    /* �����ڴ�  */
    pstEstReqMsg = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_lMM_EST_REQ_STRU));
    if( NAS_LPP_NULL_PTR == pstEstReqMsg )
    {
        return;
    }

    /*��д��Ϣͷ*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstEstReqMsg, ID_LPP_LMM_EST_REQ);

    /*������Ϣ���ͺ��� */
    NAS_LPP_SND_MSG(pstEstReqMsg);

    return;
}
VOS_VOID NAS_LPP_LppLmmDataReq
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulTmpLength     = 0;
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_LppLmmDataReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_Func_Enter);


    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( 0 == ulLppMsgLen)
    {
        NAS_LPP_WARN_LOG("NAS_LPP_LppLmmDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }
    else if(ulLppMsgLen > NAS_LPP_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLppMsgLen - NAS_LPP_MIN_SND_MSG_LEN ;
        pstLppDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LMM_DATA_REQ_STRU) + ulTmpLength);
    }
    else/*�������С��NAS_LPP_MIN_SND_MSG_LEN������Ŀռ����NAS_LPP_MIN_SND_MSG_LEN*/
    {
        pstLppDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LMM_DATA_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstLppDataReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_LppLmmDataReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /*��д�տ���Ϣͷ����*/
    pstLppDataReq->stLppMsg.ulLppMsgSize = ulLppMsgLen;

    /*���տ���Ϣ��ŵ�ID_LPP_LMM_DATA_REQ�ṹ��*/
    /*lint -e669*/
    NAS_LPP_MEM_CPY(pstLppDataReq->stLppMsg.aucLppMsg, pucEncodeOutMsg, ulLppMsgLen);
    /*lint +e669*/

    /*��дSessionId*/
    pstLppDataReq->ulSessionId = ulSessionId;

    /*��дOpId*/
    pstLppDataReq->ulOpId = ulOpId;

    /*��д��Ϣͷ*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstLppDataReq, ID_LPP_LMM_DATA_REQ);

    /*������Ϣ���ͺ��� */
    NAS_LPP_SND_MSG(pstLppDataReq);

}


VOS_VOID NAS_LPP_SendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
)
{
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq   = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulDataReqSize   = 0;
    VOS_UINT16                          usRslt          = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SendUplinkMsg_ENUM, LNAS_LPP_Func_Enter);

    ulDataReqSize = sizeof(LPP_LMM_DATA_REQ_STRU) + ulLppMsgLen - 4;
    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU *)NAS_LPP_MEM_ALLOC(ulDataReqSize);
    if (VOS_NULL_PTR == pstLppDataReq)
    {
          return ;
    }

    NAS_LPP_MEM_SET(pstLppDataReq, 0, ulDataReqSize);
    pstLppDataReq->ulLength = ulDataReqSize - VOS_MSG_HEAD_LENGTH;

    /*��װ��LMM���͵�DATA REQ*/
    NAS_LPP_FillWithLppDataReqMsg(ulLppMsgLen, pucEncodeOutMsg, pstLppDataReq, ulSessionId);

    /*�ڷ���������Ϣ֮ǰ���۵�ǰ����״̬��ʲô�����Ƚ�������Ϣ����*/
    usRslt = NAS_LPP_PushUplinkMsgToBuff(ulDataReqSize, pstLppDataReq, pstLppMsgIdentity);
    if (NAS_LPP_SUCCESS != usRslt)
    {
        NAS_LPP_MEM_FREE(pstLppDataReq);
        return ;
    }

    /*���ݵ�ǰ����·״̬�������Ƿ��������Ƿ�ֱ��*/
    switch(NAS_LPP_GetLppConnStatus())
    {
        case NAS_LPP_CONN_STATUS_IDLE:
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: IDLE, Start Est!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusIdle);

            /*Idle̬��������*/
            NAS_LPP_LppLmmEstReq();

            /*���������1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*������֮�󣬽���·�ó�ESTING*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ESTING);

            /*����������ʱ��*/
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_EST_CNF);
            break;

        case NAS_LPP_CONN_STATUS_ESTING:
            /*���������У�������������Ϣ���浽buffer��*/
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: ESTING!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusEsting);
            break;

        case NAS_LPP_CONN_STATUS_CONNECT:
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: CONNECT, DataReq!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusConnect);

            /*���������1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*����̬��ֱ�ӷ���ֱ����Ϣ*/
            NAS_LPP_LppLmmDataReq(ulSessionId,
                                  ulLppMsgLen,
                                  pucEncodeOutMsg,
                                  pstLppDataReq->ulOpId);
            break;

        default:
            break;
    }

    NAS_LPP_MEM_FREE(pstLppDataReq);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ResendUplinkMsg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ResendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU               *pstTransId )
{
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulDataReqSize = 0;
    LPP_UPLINK_MSG_BUF_STRU            *pstUpMsgBuf = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_ResendUplinkMsg");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_Func_Enter);

    /*Ѱ��������Ϣ����*/
    pstUpMsgBuf = NAS_LPP_SearchUpMsgBuff(ulSessionId, pstTransId);
    if (NAS_LPP_NULL_PTR == pstUpMsgBuf)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_ResendUplinkMsg: Can't find pstUpMsgBuf");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_DontFindUplinkBufferMsg);
        return;
    }

    /*�ش�ʱ��Ҫ��SendBuffFlag�ó�False��ԭ��������ߵ��ش�����ô�ϴ�һ���Ƿ��ͳɹ��ˣ�
    ��ʱsendflag�Ѿ��ó���true�����ش���ʱ����Ҫ����flag�ó�false�����յ�data cnf�ɹ�
    ֮�����ó�ture�����򣬻���ڷ��Ͳ���ȥ�����*/
    pstUpMsgBuf->bSendBufFlag = PS_FALSE;
    ulDataReqSize = pstUpMsgBuf->u.stLppDataReq.ulLength + VOS_MSG_HEAD_LENGTH;
    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU*)NAS_LPP_ALLOC_MSG(ulDataReqSize);
    if ( NAS_LPP_NULL_PTR == pstLppDataReq )
    {
        NAS_LPP_ERR_LOG("resend up msg alloc fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_CPY(pstLppDataReq, &pstUpMsgBuf->u.stLppDataReq, ulDataReqSize);

    /*���ݵ�ǰ����·״̬�������Ƿ��������Ƿ�ֱ��*/
    switch(NAS_LPP_GetLppConnStatus())
    {
        case NAS_LPP_CONN_STATUS_IDLE:
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusIdle);
            /*Idle̬��������*/
            NAS_LPP_LppLmmEstReq();

            /*����������1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*������֮�󣬽���·�ó�ESTING*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ESTING);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_EST_CNF);
            break;
        case NAS_LPP_CONN_STATUS_ESTING:
            /*���������У�������������Ϣ���浽buffer��*/
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusEsting);
            break;

        case NAS_LPP_CONN_STATUS_CONNECT:
            /*����̬��ֱ�ӷ���ֱ����Ϣ*/
            NAS_LPP_SND_MSG(pstLppDataReq);
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusConnect);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtodaCapability
 Description     : ��֯otodoa������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_EncodeOtodaCapability
(
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU    *pstProvideCapR9Ies,
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement,
    LRRC_SUPPORT_CAPABILITY_STRU            *pstLrrcCap
)
{
    VOS_UINT32                              ulLoop,ulBandNum = 0,ulExtBandNum = 0;
    VOS_UINT32                              ulTmpIndex ,ulTmpShit, ulTmp;

    NAS_LPP_INFO_LOG("NAS_LPP_ResendUplinkMsg");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeOtodaCapability_ENUM, LNAS_LPP_Func_Enter);

    if( (NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpOtdoaCapReq)
      &&(VOS_TRUE == pstLrrcCap->bRrcCapbilityFlag)
      &&(LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucOtdoaUeAssistFlag))/*ucOtdoaUeAssistFlag��36.331��ue������֧��*/
    {
        pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_SLCT;
        pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpOtdoaProvideCapExt = NAS_LPP_SLCT;

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stOtdoaMode.ucOTDOAMode = 0x01;  /*��0 bitΪ1����ʾ֧��OTDOA*/
        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stOtdoaMode.ucOTDOAModeLen = 1;

        /*additionalNeighbourCellInfoList
        This field, if present, indicates that the target device supports up to 3��24 OTDOA-NeighbourCellInfoElement in OTDOA NeighbourCellInfoList
        in OTDOA-ProvideAssistanceData without any restriction for the earfcn in each OTDOA-NeighbourCellInfoElement as specified in subclause 6.5.1.2. */
        /*pstProvideCapR9Ies->stOTDOAProvideCapabilities.enAdditionalNeighbourCellInfoListR10 = ;Ϊ�˴���3*24��ı�׼С���ṹ�����IE�������óɲ�����*/
        if (LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucAddOtdoaNeighbourCellInfoListFlag)
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_SLCT;
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.enAdditionalNeighbourCellInfoListR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_NO_SLCT;
        }

        for ( ulLoop = 0 ; ulLoop < LPP_MAX_SUPPORTED_BAND_EUTRA_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutra.astSupportedBandArray[ulBandNum].ulBandEutra = ulLoop+1;
                ulBandNum++;
            }
        }

        for ( ulLoop = LPP_MAX_SUPPORTED_BAND_EUTRA_NUM ; ulLoop < LRRC_LPP_MAX_BAND_IND_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                if ( ulExtBandNum >= LPP_MAX_SUPPORTED_BAND_EUTRA_NUM )
                {
                    NAS_LPP_ERR_LOG1("encode capability ,ext band overflow,ulLoop", ulLoop);
                    TLPS_PRINT2LAYER_INFO1(NAS_LPP_EncodeOtodaCapability_ENUM, LNAS_LPP_ExtBandOverflowLoop, ulLoop);
                    return NAS_LPP_FAILURE;
                }
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].bitOpBandEutraV9A0 = NAS_LPP_SLCT;
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].ulBandEutraV9A0 = ulLoop+1;
                ulExtBandNum++;
            }
        }

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutra.ulSupportBandNum = ulBandNum;
        if ( 0 != ulBandNum )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutra = NAS_LPP_SLCT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutra = NAS_LPP_NO_SLCT;
        }

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.ulSupportBandNum = ulExtBandNum;
        if ( 0 != ulExtBandNum )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutraV9A0  = NAS_LPP_SLCT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutraV9A0  = NAS_LPP_NO_SLCT;
        }

        if ( LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucInterFreqRSTDMeasFlag )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_SLCT;
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.enInterFreqRSTDmeasurementR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_NO_SLCT;
        }
    }
    else
    {
        pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_NO_SLCT;
    }

    return NAS_LPP_SUCCESS;
}
VOS_VOID NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsg,
    VOS_UINT32                         *pulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucTransIndx
)
{
    LPP_MESSAGE_STRU                       *pstUplinkProvideCap = NAS_LPP_NULL_PTR;
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU   *pstProvideCapR9Ies  = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement    = NAS_LPP_NULL_PTR;
    LRRC_SUPPORT_CAPABILITY_STRU           *pstLrrcCap;
    VOS_UINT16                              usRslt              = 0;
    VOS_UINT16                              usBitPos            = 0;

    NAS_LPP_ERR_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_Func_Enter);

    /*���LPP MSG BUFF*/
    NAS_LPP_ClearLppMsgBuff();

    /*��ȡLPP MSG BUFF*/
    pstUplinkProvideCap = NAS_LPP_GetLppMsgBuff();
    pstLrrcCap = NAS_LPP_GetLrrcCap();

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("encode capability with wrong index", ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_TransDontEnd);
        return;
    }

    /*�õ������ṩ�����ĵ�ַ*/
    pstProvideCapR9Ies  = NAS_LPP_GetUpLinkProvideCapIEAddr(pstUplinkProvideCap);

    /*�����ṩ������Ԫ*/
    pstUplinkProvideCap->bitOpLppTransactionId    = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpSequenceNumber      = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpAcknowledgement     = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpLppMessageBody      = NAS_LPP_SLCT;
    /*��transaction����*/
    pstUplinkProvideCap->bEndTransaction          = PS_TRUE;
    pstUplinkProvideCap->stTransactionId.enInitiator =
        pstLppMsg->stTransactionId.enInitiator;
    pstUplinkProvideCap->stTransactionId.ucTransactionNumber  =
        pstLppMsg->stTransactionId.ucTransactionNumber;
    pstUplinkProvideCap->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();
    pstUplinkProvideCap->stAcknowledgement.bitOpAckIndicator = NAS_LPP_NO_SLCT;
    /*��Ҫ�����ظ�ACK*/
    pstUplinkProvideCap->stAcknowledgement.bAckRequested  = PS_TRUE;
    pstUplinkProvideCap->stLppMessageBody.ulChoice        =
        LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.ulChoice =
        LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.u.stProvideCapabilities.ulChoice =
        LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.u.stProvideCapabilities.u.stC1.ulChoice =
        LPP_PROVIDE_CAPABILITIES_R9_CHOSEN;

    /*���������ECID�������������ECID���ṩ������Ϣ*/
    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpEcidCapReq)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Ecid Capa Req!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_EcidCpaReq);

        pstProvideCapR9Ies->bitOpECIDProvideCapabilities = NAS_LPP_SLCT;
        pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSupCnt = 3;

        /*���ECID֧�ֵ�����*/
        if(LPP_LRRC_INFO_FLAG_VALID == NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag())
        {
            /*111����RSRP, RSRQ�� RXTXTimeDiff��֧��*/
            pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x07; /*111*/
        }
        else
        {
            /*110����RSRP, RSRQ֧�֣� ����RXTXTimeDiff��֧��*/
            pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x06; /*110*/
        }
    }

    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpOtdoaCapReq)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Otdoa Capa Req!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_OtdoaCpaReq);

        if (NAS_LPP_SUCCESS != NAS_LPP_EncodeOtodaCapability(pstProvideCapR9Ies,pstTransElement,pstLrrcCap) )
        {
            NAS_LPP_ERR_LOG("Encode otdoa capability fail");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_EncodeOtdoaCapabilityFail);
            pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_NO_SLCT;
        }
    }

    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpAgnssCapReq)
    {
        /*LIFUXIN: TODO*/
    }

    /*��ʼ����*/
    usRslt = NAS_LPP_EncodeMessage(pstUplinkProvideCap,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Encode ProvideCap msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        return;
    }

    *pulLppMsgLen = usBitPos/8;

    /* ���������Ϣ���ʶ����Ϣ */
    pstLppMsgIdentity->ulSessionId                   =
                                                    ulSessionId;
    pstLppMsgIdentity->stTransId.enInitiator            =
                                                    pstUplinkProvideCap->stTransactionId.enInitiator;
    pstLppMsgIdentity->stTransId.ucTransactionNumber    =
                                                    pstUplinkProvideCap->stTransactionId.ucTransactionNumber;
    pstLppMsgIdentity->usSequnceNum                     =
                                                    pstUplinkProvideCap->stSequenceNumber.ucSequenceNumber;
    pstLppMsgIdentity->enUplinkMsgType                  =
                                                    NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    /* ����ɹ� */
    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CreatNewTransAndReqAssistData
 Description     :  �����µ�transaction��Ȼ�����븨������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CreatNewTransAndReqAssistData
(
    VOS_UINT8 ucSessionIndx,
    VOS_BOOL  enOtdoaAssist,
    VOS_BOOL  enGnssAssist
)
{
    VOS_UINT8                                   ucTmpTransIndx,ucTmpSessionTransIndex;

    NAS_LPP_ERR_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CreatNewTransAndReqAssistData_ENUM, LNAS_LPP_Func_Enter);

    /*����һ���µ�Transaction�����븨������*/
    NAS_LPP_CreatNewTrans(ucSessionIndx,&ucTmpSessionTransIndex,&ucTmpTransIndx);

    /*���µ�trans�����븨������*/
    if ( PS_NULL_UINT8 != ucTmpTransIndx )
    {
        NAS_LPP_SndUplinkReqAssistDataMsg(ucSessionIndx,ucTmpSessionTransIndex,ucTmpTransIndx,enOtdoaAssist,enGnssAssist);
        NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucTmpSessionTransIndex, LPP_MS_ASSISTDATA, LPP_SS_WAIT_INTRA_DATA_CNF);
    }
}

/*lint -e774*/
/*****************************************************************************
 Function Name   : NAS_LPP_AgainReqAssistData
 Description     :  �����굱ǰ�ĸ������� ���̺��ٴβ������븨������
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-9-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_AgainReqAssistData( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU                *pstCfgpara;
    NAS_LPP_LOC_TECH_MAP_STRU               *pstTechmap;
    VOS_UINT8 ucSessionIdx,ucOtdoaSessionIdx = PS_NULL_UINT8,ucGnssSessionIdx = PS_NULL_UINT8;
    VOS_BOOL enReqOtdoaAssis = VOS_FALSE, enReqGnssAssis = VOS_FALSE;

    NAS_LPP_ERR_LOG("NAS_LPP_AgainReqAssistData ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_AgainReqAssistData_ENUM, LNAS_LPP_Func_Enter);



    pstCfgpara = NAS_LPP_GetCfgPara();

    pstTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);

    /*���location reqҪ����otdoa�Ĳ��������ǣ���ǰotoda�ĸ�������û��*/
    if ( (NAS_LPP_NULL_PTR != pstTechmap)
       &&(LPP_LRRC_INFO_FLAG_INVALID == pstCfgpara->stOtdoaAssisCfg.ucOtdoaReferenceCellInfoFlag) )
    {
        enReqOtdoaAssis = VOS_TRUE;
        ucOtdoaSessionIdx = pstTechmap->ucSessionIndx;
    }

    /*gnss�Ƿ���Ҫ����assist data,TODO */
    /*{
        pstTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS);
        if (NAS_LPP_NULL_PTR != pstTechmap)
        {
            enReqGnssAssis = VOS_TRUE;
            ucGnssSessionIdx = pstTechmap->ucSessionIndx;
        }
    }*/

    /*�Ƚ���һ��transaction�����븨����Ϣ*/
    if ( (VOS_TRUE == enReqOtdoaAssis)
       ||(VOS_TRUE == enReqGnssAssis) )
    {
        if (PS_NULL_UINT8 != ucOtdoaSessionIdx )
        {
            ucSessionIdx = ucOtdoaSessionIdx;
        }
        else
        {
            ucSessionIdx = ucGnssSessionIdx;
        }

        NAS_LPP_CreatNewTransAndReqAssistData( ucSessionIdx, enReqOtdoaAssis, enReqGnssAssis);
    }

}
/*lint +e774*/

/*****************************************************************************
 Function Name   : NAS_LPP_StopTechLocForLackOfAssistData
 Description     : ȱ�ٸ������ݣ���Ҫֹͣ�Ĳ���:ֻ��OTDOA�д���������OTDOAû�и������ݣ����ң�OTDOA��transaction
                   ��û�������Ķ�λ��Ҫɾ����transaction��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_StopTechLocForLackOfAssistData( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU                *pstCfgpara;
    NAS_LPP_LOC_TECH_MAP_STRU               *pstTechmap;
    NAS_LPP_LOC_TECH_RUNING_STRU             stPosSearchRslt = {0};
    NAS_LPP_SUB_STATE_ENUM_UINT32            enSubState;

    NAS_LPP_INFO_LOG("NAS_LPP_StopTechLocForLackOfAssistData ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_StopTechLocForLackOfAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstCfgpara = NAS_LPP_GetCfgPara();

    pstTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);

    /*���location reqҪ����otdoa�Ĳ��������ǣ���ǰotoda�ĸ�������û��*/
    if ( NAS_LPP_NULL_PTR != pstTechmap )
    {
        if (LPP_LRRC_INFO_FLAG_INVALID == pstCfgpara->stOtdoaAssisCfg.ucOtdoaReferenceCellInfoFlag)
        {
            /*����transaction���Ƿ��������Ķ�λ����*/
            NAS_LPP_SearchRunningPosTechByTransIndx(pstTechmap->ucTransIndx,&stPosSearchRslt);
            if (1 == stPosSearchRslt.ucNum)
            {
                /*����һ������ABORT,����transaction*/
                NAS_LPP_SndUpLppAbortMsg(pstTechmap->ucSessionIndx,
                                         pstTechmap->ucSessionTranIndx,
                                         pstTechmap->ucTransIndx,
                                         LPP_COMMON_IES_ABORT_TARGET_DEVCIE_ABORT,
                                         VOS_TRUE,
                                         VOS_TRUE);

                NAS_LPP_SetEndTransFlg(pstTechmap->ucSessionIndx,
                                       pstTechmap->ucSessionTranIndx,
                                       VOS_TRUE);

                NAS_LPP_ChangeTransFsmState(pstTechmap->ucSessionIndx,
                                            pstTechmap->ucSessionTranIndx,
                                            NAS_LPP_GetLppMainState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx),
                                            LPP_SS_WAIT_INTRA_DATA_CNF);
            }
            else/*transaction���������Ķ�λ����*/
            {
                enSubState = NAS_LPP_GetLppSubState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx);
                if ((LPP_SS_WAIT_ASSISTDATA_RCV_CMP == enSubState)||(LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP == enSubState))
                {
                    NAS_LPP_ChangeTransFsmState(pstTechmap->ucSessionIndx,
                                                pstTechmap->ucSessionTranIndx,
                                                NAS_LPP_GetLppMainState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx),
                                                LPP_SS_WAIT_MEAS_IND);
                }
            }
        }
    }
}


NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_VerifyOrCreateTransaction
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                          *pucTransIndx,
    VOS_UINT8                          *pucSessionTransIndx
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU        *pstSessionEntity    = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucTransIndex        = 0;
    VOS_UINT32                                  ulRslt              = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANS_ID_STRU                       stTransId;
    VOS_UINT8                                   ucSessionIndx       = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_VerifyOrCreateTransaction ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 == ucSessionIndx)
    {
        /*û�ҵ�������sessionʵ��*/
        NAS_LPP_WARN_LOG("NAS_LPP_VerifyOrCreateTransaction: can't find Session!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_CanntFindSession);

        pstSessionEntity = NAS_LPP_MallocSessionEntity(ulSessionId); /*����sessionʵ��*/
        if(NAS_LPP_NULL_PTR == pstSessionEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Session Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_CanntAllocSessionEntity);
            return NAS_LPP_NULL_PTR;
        }

        ucTransIndex = NAS_LPP_MallocTransEntityIndx(&(pstLppMsgHead->stTransactionId)); /*����transactionʵ��*/
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Transcation Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_CanntAllocTransEntity);
            NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
            return NAS_LPP_NULL_PTR;
        }

        ulRslt = NAS_LPP_AddTransEntityToSession(pstSessionEntity, ucTransIndex, pucSessionTransIndx); /*��session��transaction��������*/
        if(NAS_LPP_SUCCESS != ulRslt)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: Transcation entity is full!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_TransEntityIsFull);
            return NAS_LPP_NULL_PTR;
        }
    }
    else
    {
        /*�ҵ���session����ȡʵ��ָ��*/
        pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
        if(NAS_LPP_NULL_PTR == pstSessionEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Get Session Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_CanntGetSessionEntity);
            return NAS_LPP_NULL_PTR;
        }

        stTransId.enInitiator           = pstLppMsgHead->stTransactionId.enInitiator;
        stTransId.ucTransactionNumber   = pstLppMsgHead->stTransactionId.ucTransactionNumber;
        /*���ҵ�sessionʵ�壬�����session��transactionʵ��*/
        NAS_LPP_SearchTransEntityIndx(ucSessionIndx,
                                      &stTransId,
                                      &ucTransIndex,
                                      pucSessionTransIndx);
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            /*û���ҵ����򴴽�transactionʵ��*/
            NAS_LPP_WARN_LOG("NAS_LPP_VerifyOrCreateTransaction: can't find transation!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_DontFindTransaction);
            ucTransIndex = NAS_LPP_MallocTransEntityIndx(&(pstLppMsgHead->stTransactionId));
            pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
            if(NAS_LPP_NULL_PTR == pstTransEntity)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Transcation Entity!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_CanntAllocTransEntity);
                return NAS_LPP_NULL_PTR;
            }

            ulRslt = NAS_LPP_AddTransEntityToSession(pstSessionEntity, ucTransIndex, pucSessionTransIndx); /*��session��transaction��������*/
            if(NAS_LPP_SUCCESS != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: Transcation entity is full!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_TransEntityIsFull);
                NAS_LPP_ReturnTransEntityToPool(ucTransIndex);

                return NAS_LPP_NULL_PTR;
            }
        }
    }

    *pucTransIndx = ucTransIndex;

    return pstTransEntity;
}


VOS_VOID NAS_LPP_SndUplinkProvideCapbilityMsg
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucTransIndx
)
{
    VOS_UINT32                          ulLppMsgLen     = 0;
    VOS_UINT8                          *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity = {0};

    NAS_LPP_NORM_LOG("NAS_LPP_SndUplinkProvideCapbilityMsg!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUplinkProvideCapbilityMsg_ENUM, LNAS_LPP_Func_Enter);

    /*�������֮�������Ĵ洢�ռ�*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_SndUplinkProvideCapbilityMsg:  Alloc Mem Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkProvideCapbilityMsg_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    /*���*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    /*��װ�ṩ������Ϣ,���һ�ȡ���ʶ����Ϣ*/
    NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo(pstLppMsgHead,
                                                        &ulLppMsgLen,
                                                        pucEncodeOutMsg,
                                                        &stLppMsgIdentity,
                                                        ulSessionId,
                                                        ucTransIndx);

    /*���ͱ���õ����ݸ�����*/
    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    /*�ͷŶ�̬�ڴ�*/
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return;
}
VOS_VOID NAS_LPP_RcvCapabitlityRequestHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_UINT8                                   ucSessionIndx       = 0;
    VOS_UINT8                                   ucTransIndx         = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvCapabitlityRequestHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvCapabitlityRequestHandle_ENUM, LNAS_LPP_Func_Enter);

    /*�õ�transaction��������Ĳ���*/
    pstTransEntity      = pstLppTransIndex->pstTransEntity;
    ucTransIndx         = pstLppTransIndex->ucTransIndx;
    ucSessionTransIndx  = pstLppTransIndex->ucSessionTransIndx;

    /*LIFUXIN: TODO*/
    /*
     ��OTDOA��ECID��˵����λ������Ϣһ�����ᱨ��LPP����GNSS��������Ϣ��Ҫ����GPSģ��
     ���ԣ�������Ҫת״̬����GNSS�����ظ�����������ʵ��
    */

    /*�ظ�ProvideCapbility��Ϣ*/
    NAS_LPP_SndUplinkProvideCapbilityMsg(pstLppMsgHead, ulSessionId,ucTransIndx);

    /*���session��index*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    /*��������sequenceNumber*/
    NAS_LPP_SetDownLinkMsgSequenceNum(ucSessionIndx,
                                      pstLppMsgHead->stSequenceNumber.ucSequenceNumber);

    /*��ʾ��ǰtransaction����յ�������ACK֮�󣬾Ϳ��Խ�����*/
    pstTransEntity->ucTransEndFlag   = PS_TRUE;

    /*��¼��ǰ���͵Ŀտ���Ϣ�������յ���������Ϣ֮�����ת��ʲô״̬*/
    pstTransEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_CAP;

    /*ת״̬,ת��������������״̬���ڲ���data cnf��Ҳ����ȷ�ϰѿտ���Ϣ���͵��˻�վ*/
    NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                ucSessionTransIndx,
                                LPP_MS_CAPABILITY,
                                LPP_SS_WAIT_INTRA_DATA_CNF);

    return;
}


/*****************************************************************************
Function Name   : NAS_LPP_CfgLrrcOtdoaMeas
Description     : ����LRRC��otoda����
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd

)
{
    NAS_LPP_NORM_LOG("NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans_ENUM, LNAS_LPP_LcsMeasCmd, ucLcsMeasCmd);

    NAS_LPP_SndOtdoaMeasReq(ucSessionIndx,ucSessionTransIndx,ucLcsMeasCmd);

    if (LPP_LRRC_LCS_MEAS_CMD_SETUP == ucLcsMeasCmd)
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_LOCATION,LPP_SS_WAIT_LRRC_MEAS_CNF);
    }
    else
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_LOCATION,LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF);
    }
}

/*****************************************************************************
Function Name   : NAS_LPP_RcvOtdoaAssistDataHandle
Description     : otdoa�ĸ������ݴ���
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RcvOtdoaAssistDataHandle
(
    VOS_UINT8                           ucSessionIndx,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap;
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU    *pstSessionEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity          = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulRslt;

    pstCfgPara = NAS_LPP_GetCfgPara();

    if ( (NAS_LPP_SLCT != pstCfgPara->bitOtdoaAssisChng))
    {
        return;
    }

    pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR  == pstSessionEntity)
    {
        return;
    }

    pstTransEntity = NAS_LPP_GetTransElementByIndex(pstLppTransIndex->ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransEntity)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_TransDontEnd);
        return;
    }
    /*�ڱ�session������transaction�����:��û��otdoa��location info req��transaction
     ֻ��OTDOA��request location transaction���еȴ��������ݵ������GNSS��һ��Ҫ��������.*/

    /*��assist data transaction�����ǣ����OTDOA�������Ƿ���ȫ����ȷ*/
    ulRslt = NAS_LPP_CheckOtdoaAssisDataAfterSave();
    if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_NAS_LPP_CheckOtdoaAssisDataAfterSaveFail);
        /* ����lpp error*/
        NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                 &pstTransEntity->stTransId,
                                 LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                 VOS_TRUE,
                                 VOS_TRUE);

        /*  �ͷŶ�Ӧ��todoa���� */
        pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_UP_ERR;
        NAS_LPP_MEM_SET(&pstCfgPara->stOtdoaAssisCfg, 0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU) );
    }

    pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if (NAS_LPP_NULL_PTR != pstLocTechmap)
    {
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_GetOtdoaRunningSucc);
        /*����в��ҵ�OTDOA��location info req�� ���Ǹ�transaction������������̣�����LRRC/GNSS*/
        if (pstLocTechmap->ucSessionIndx == ucSessionIndx)
        {
            if (NAS_LPP_MSG_VERIFY_SUCC == ulRslt)
            {
                /*loc infor req transaction������LRRC*/
                NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans(pstLocTechmap->ucSessionIndx,
                                                        pstLocTechmap->ucSessionTranIndx,
                                                        pstLocTechmap->ucTransIndx,
                                                        LPP_LRRC_LCS_MEAS_CMD_SETUP);
            }
            else
            {
                /*loc infor req transaction�� �ͷ�LRRC*/
                NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans(pstLocTechmap->ucSessionIndx,
                                                        pstLocTechmap->ucSessionTranIndx,
                                                        pstLocTechmap->ucTransIndx,
                                                        LPP_LRRC_LCS_MEAS_CMD_REL);
            }
        }
        else /* ���û�ҵ���������LRRC,��otdoa��loc infor req������LRRC*/
        {
        }
    }

}

/*****************************************************************************
Function Name   : NAS_LPP_RcvGnssAssistDataHandle
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvGnssAssistDataHandle( VOS_UINT8 ucSessionIndx )
{
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;
    VOS_UINT32 ulRslt;

    pstCfgPara = NAS_LPP_GetCfgPara();

    if ( (NAS_LPP_SLCT != pstCfgPara->bitGnssAssisChng))
    {
        return;
    }

    ulRslt = NAS_LPP_CheckGnssAssisDataAfterSave();
    if (NAS_LPP_MSG_VERIFY_SUCC == ulRslt)
    {
        /*����GNSS�����õ�CNF*/
    }

    pstCfgPara->bitGnssAssisChng  = NAS_LPP_NO_SLCT;

}
VOS_VOID NAS_LPP_RcvAssistDataProvideHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;
    VOS_UINT8 ucSessionIndx;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvAssistDataProvideHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvAssistDataProvideHandle_ENUM, LNAS_LPP_Func_Enter);

    /*1����������յ�location info req���ٲ����ռ�assist data�����������assist data��������TRANSACTION��
         ���Ǹ�location info req��transaction�����assist data����LRRC��gps��
      2��������л�С�����assist data ���£�ֱ�Ӹ���assist data����LRRC��gps*/

    /*���session��index*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity  )
    {
        NAS_LPP_ERR_LOG1("assist data not found session", ulSessionId);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAssistDataProvideHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    /*�ڸ������ݽ������ǰ���Ȳ�����LRRC��gnss*/
    if (VOS_TRUE != pstMsgHead->bEndTransaction)
    {
        return;
    }

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,pstLppTransIndex->ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvAssistDataProvideHandle:wrong session index,session trans index ",
                          ucSessionIndx,
                          pstLppTransIndex->ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_DontFindTransaction);
        return;
    }

    NAS_LPP_SetEndTransFlg( ucSessionIndx, pstLppTransIndex->ucSessionTransIndx,VOS_TRUE);

    NAS_LPP_RcvOtdoaAssistDataHandle(ucSessionIndx,pstLppTransIndex);
    NAS_LPP_RcvGnssAssistDataHandle(ucSessionIndx);

    /*ת�Ƶ�������LPP ACK�� DATA_CNF״̬*/
    NAS_LPP_ChangeTransFsmState( ucSessionIndx, pstLppTransIndex->ucSessionTransIndx, LPP_MS_ASSISTDATA, LPP_SS_WAIT_INTRA_DATA_CNF);

    /*�ж��Ƿ���Ҫ������������������Ϣ��:����������ݵ�transaction ��UE�Լ������ģ���������������*/
    if (LPP_INITIATOR_TYPE_TARGET_DEVICE != pstTransElementEntity->stTransId.enInitiator)
    {
        NAS_LPP_AgainReqAssistData();
    }
    else
    {
        /*�ж�����û�и������ݣ���Ҫֹͣ�Ķ�λ����:ֻ��OTDOA*/
        NAS_LPP_StopTechLocForLackOfAssistData();
    }

}
/*****************************************************************************
Function Name   : NAS_LPP_ProvideAssistDataConflictProcess
Description     :  �������ݵĶԳ崦��
               �����������̵ĶԳ崦��:�������assist data��һ���µ�transaction��( Ҳ�����Ҳ���һ��transaction)��
               ��Ҫ�ж��Ƿ�������һ���������������ڽ�����.
                   ����У����ӵ�����Ϣ,  ���ǣ���Ҫ����lpp ack.
                   ���û�У���������Ĵ���
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_ProvideAssistDataConflictProcess
(
    VOS_BOOL                            enFirstAssistData,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop,ucLoop1;
    VOS_UINT8 ucSessionIdx;

    NAS_LPP_NORM_LOG("NAS_LPP_ProvideAssistDataConflictProcess!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ProvideAssistDataConflictProcess_ENUM, LNAS_LPP_Func_Enter);

    /* ���ǵ�һ��*/
    if ( VOS_TRUE != enFirstAssistData )
    {
        return  NAS_LPP_SUCCESS;
    }

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    /*�����Ƿ���������assist data transaction����*/
    for ( ucLoop1 = 0 ; ucLoop1 < NAS_LPP_MAX_SESSION_COUNT; ucLoop1++ )
    {
        if ( 0 == (pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ucLoop1)) )
        {
            continue;
        }

        ucSessionIdx = ucLoop1;
        pstSessionEntity = &(pstSessionEntityPool->astLppSessionEntity[ucSessionIdx]);

        for ( ucLoop = 0 ; ucLoop < pstSessionEntity->stLppTrans.ucTransIdCount; ucLoop++ )
        {
            if (LPP_MS_ASSISTDATA == NAS_LPP_GetLppMainState(ucSessionIdx,ucLoop) )
            {
                return NAS_LPP_ASSIST_DATA_CONFLICT;
            }
        }
    }

    if (ucLoop1 >= NAS_LPP_MAX_SESSION_COUNT)
    {
        /*û�ҵ�����ʾ����ͻ*/
        return NAS_LPP_SUCCESS;
    }
    else
    {
        return NAS_LPP_ASSIST_DATA_CONFLICT;
    }
}
VOS_VOID NAS_LPP_RcvLocationRequestHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_UINT8                                   ucSessionIndx       = 0;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU              *pstOtdoaAssisCfg;
    NAS_LPP_CONFIG_PARA_STRU                   *pstCfgPara;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationRequestHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_Func_Enter);

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();
    pstCfgPara = NAS_LPP_GetCfgPara();

    /*
     Э��Լ�������session����һ��session�ڲ�����ͬʱ����ͬһ�ֶ�λ������
     transaction����runing������֮��ÿ������һ��locationReq������һ������
     session��û������runningͳһ���͵Ķ�λ������������һ�ֳ����������ǰ
     ��������������ֶ�λ���������� OTDOA�� ECID�� ����ECID ������һ��session
     �Ѿ������ˣ� ��ô���������ֻ��OTDOA�Ĳ��������OTDOA�Ĳ�������Ҳ������
     ��ôֱ�ӻظ������abort����
    */

    /*�õ�transaction��������Ĳ���*/
    ucSessionTransIndx  = pstLppTransIndex->ucSessionTransIndx;

    /*��ȡsessionIndx*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 == ucSessionIndx)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Search session Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    /*��������sequenceNumber*/
    NAS_LPP_SetDownLinkMsgSequenceNum(ucSessionIndx,
                                      pstLppMsgHead->stSequenceNumber.ucSequenceNumber);

    /*����ECID��������*/
    if(NAS_LPP_SLCT == pstCfgPara->bitEcidReq)
    {
        NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationRequestHandle: Req Ecid Meas Info");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReqEcidMeasInfo);

        /*��������ECID��λ�ò�����Ϣ����LRRC����������*/
        NAS_LPP_SndLppLrrcEcidMeasReq( ucSessionIndx, ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_SETUP);

        /*ת״̬���ȴ�LRRC����CNF*/
        NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_LRRC_MEAS_CNF);

        pstCfgPara->bitEcidReq = NAS_LPP_NO_SLCT;
    }

    /*����OTDOA��������*/
    if(NAS_LPP_SLCT == pstCfgPara->bitOtdoaReq)
    {
        /*TODO*/
        /*������������ ʵ�ֵĲ�������:
        1. ��⵱ǰ�Ƿ�������(������: ��session�Ƿ��й�OTDOA�ĸ�����Ϣ�������̣��Լ�locReq��ʱ�����OTDOA�ĸ�����Ϣ�Ƿ���Ч)
        2. ���������Ϣ��Ч��������transactionȥ����OTDOA�ĸ�������,����Ƕ��ֶ�λ��������ʱ��״̬��ʱ��ת�ɵ���������Ϣ���
        3. ��ECID����cnf�յ�֮�󣬼�Ȿsession������OTDOA��λ����Ϣ�����ҵ�ǰ��transaction���ڽ��и�����Ϣ�Ľ������̣���״̬
           ת�ɵȴ�������������ɣ� ������Ϣ�������֮���ڸ�LRRC����OTDOA�Ĳ�������״̬ת�ɵȴ�OTODA�Ĳ���cnf
        4. ���������Ϣ��Ч��ֱ�Ӹ�LRRC����OTDOA��������
        5. ����ǰ��λ������1
        */
        /*�ж�OTDOA���������Ƿ���Ч*/
        TLPS_PRINT2LAYER_WARNING2(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_RefCellFlagAndAssistChangeFlag, pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag, pstCfgPara->bitOtdoaAssisChng);
        if ( (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag)
           &&(NAS_LPP_SLCT != pstCfgPara->bitOtdoaAssisChng) )
        {
            /*ֱ������LRRC*/
            NAS_LPP_SndOtdoaMeasReq(ucSessionIndx, ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_SETUP);

            if ( LPP_SS_WAIT_LRRC_MEAS_CNF != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx) )
            {
                /*ת״̬���ȴ�LRRC����CNF*/
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_LRRC_MEAS_CNF);
            }
        }
        else
        {
            /* �ж��Ƿ����Ѿ��ڽ��еĸ�����������:
                  ����У����Ǹ������������̽����ˣ����ж��Ƿ�otdoa�ĸ���������Ч���Ƿ���Ҫ�������ݵ���������;
                  ���û�У��������븨������*/
            if (NAS_LPP_ASSIST_DATA_CONFLICT == NAS_LPP_ProvideAssistDataConflictProcess(VOS_TRUE,ulSessionId) )
            {
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_AssistDataRcvIsRunning);
                /* ת״̬���ȴ������������ */
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_ASSISTDATA_RCV_CMP);
            }
            else
            {
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_NoAssistDataReqAssistData);
                /* �������� */

                /* ת״̬���ȴ�LRRC����CNF */
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP);

                NAS_LPP_CreatNewTransAndReqAssistData(ucSessionIndx,VOS_TRUE,VOS_FALSE);
            }
        }

        pstCfgPara->bitOtdoaReq = NAS_LPP_NO_SLCT;
    }

    /*����GNSS��������*/
    if(NAS_LPP_SLCT == pstCfgPara->bitGnssReq)
    {
        /*TODO*/
        /*������������ʵ�ֲ�������:
        1. ����GNSS���������MTA
        2. ����ǰ�Ķ�λ������1
        3. GNSSģ��������ڸ������ݣ����LPP����meas IND��
        4. GNSSģ����������ڸ������ݣ�����LPP���͸�����Ϣ���� LPP�����µ�transactionȥ����GNSS�ĸ������ݣ�
           ��ʱ��Ӧ��LOCATION��transaction����Ҫת�ɵȴ�������Ϣ��ɣ�����LPP��˵��ֻҪ��MTA������λ����Ϣ����
           ֮��ֱ�ӵ�meas IND���ɣ���������м�ĸ�����Ϣ����
        */
        pstCfgPara->bitGnssReq = NAS_LPP_NO_SLCT;
    }

    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportType, NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx));

    /*���ݲ�ͨ���ϱ���ʽ������ͬ�Ķ�ʱ��*/
    switch(NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx))
    {
        case NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER:

            /*�������ʱ����0��˵���ǲ��޶��������ϱ�*/
            if(0 == NAS_LPP_GetTimerLen(TI_NAS_LPP_REPORT_DURATION,ucSessionIndx,ucSessionTransIndx))
            {
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportTypeTriggerNoLimitCnt);
                break;
            }

            /*������Ҫ��������duration��ʱ��*/
            NAS_LPP_TimerStart(ucSessionIndx,
                               ucSessionTransIndx,
                               TI_NAS_LPP_REPORT_DURATION);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_PERIOD:
            /*
            NAS_LPP_TimerStart(ucSessionIndx,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_PERIODICAL_REPORT);*/
            /*
            ���������Զ�ʱ������������ʱ���������ٴ����ֿ��ܣ�
            1. ��ǰû�и������ݣ�������
            2. �и������ݣ��Ȳ���cnf
            ���������������ͳһ���յ�LRRC�Ĳ����ظ���ʱ������
            �����Զ�ʱ��
            */
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_ONCE:
            NAS_LPP_TimerStart(ucSessionIndx,
                               ucSessionTransIndx,
                               TI_NAS_LPP_RESPONSE_TIMER);
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Error Report Type!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportTypeError);
            break;
    }

    return;
}


VOS_VOID NAS_LPP_RcvAortHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANS_ID_STRU stTransId;
    VOS_UINT8 ucSessionIndex;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvAortHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvAortHandle_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(ulSessionId);
    if (PS_NULL_UINT8 == ucSessionIndex)
    {
        NAS_LPP_ERR_LOG1("rev abort with wrong session id", ulSessionId);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAortHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    stTransId.enInitiator = pstLppMsgHead->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsgHead->stTransactionId.ucTransactionNumber;

    /*���������LPP ACK���� */
    if ( (NAS_LPP_SLCT == pstLppMsgHead->bitOpAcknowledgement)
       &&(PS_TRUE == pstLppMsgHead->stAcknowledgement.bAckRequested) )
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndex,
                                    pstLppTransIndex->ucSessionTransIndx,
                                    NAS_LPP_GetLppMainState(ucSessionIndex, pstLppTransIndex->ucSessionTransIndx),
                                    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK);
    }
    else
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     pstLppTransIndex->ucSessionTransIndx,
                                     &stTransId);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_AbortAndErrorProcess
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_AbortAndErrorProcess
(
VOS_UINT8                           ucSessionIndex,
VOS_UINT8                           ucSessionTransIndx,
NAS_LPP_TRANS_ID_STRU              *pstTransId
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_AbortAndErrorProcess!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_AbortAndErrorProcess_ENUM, LNAS_LPP_Func_Enter);

    if (PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndex, pstTransId) )
    {
        /*�ͷŶ�Ӧ�� session*/
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndex);
    }
    else
    {
        /*ֻ�ͷ�transaction*/
        NAS_LPP_ReleaseTransEntity(ucSessionIndex,ucSessionTransIndx);
    }
}


VOS_VOID NAS_LPP_RcvErrorHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANS_ID_STRU stTransId;
    VOS_UINT8 ucSessionIndex;

    NAS_LPP_WARN_LOG("NAS_LPP_RcvErrorHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvErrorHandle_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    stTransId.enInitiator = pstLppMsgHead->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsgHead->stTransactionId.ucTransactionNumber;

    /*���������LPP ACK���� */
    if ( (NAS_LPP_SLCT == pstLppMsgHead->bitOpAcknowledgement)
       &&(PS_TRUE == pstLppMsgHead->stAcknowledgement.bAckRequested) )
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndex,
                                    pstLppTransIndex->ucSessionTransIndx,
                                    NAS_LPP_GetLppMainState(ucSessionIndex, pstLppTransIndex->ucSessionTransIndx),
                                    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK);
    }
    else
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     pstLppTransIndex->ucSessionTransIndx,
                                     &stTransId);
    }

return;
}
VOS_VOID NAS_LPP_PassCheckLppDownLinkMsgHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulMsgType,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_INFO_LOG1("NAS_LPP_PassCheckLppDownLinkMsgHandle: LppMsgType =!", ulMsgType);
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_PassCheckLppDownLinkMsgHandle_ENUM, LNAS_LPP_Func_Enter, ulMsgType);

    switch(ulMsgType)
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN:
            /*���������LPP������Ϣ����*/
            NAS_LPP_RcvCapabitlityRequestHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN:
            /*������ṩ������Ϣ�Ĵ���*/
            NAS_LPP_RcvAssistDataProvideHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN:
            /*���������LPPλ����Ϣ����*/
            NAS_LPP_RcvLocationRequestHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            /*������·�ABORT��Ϣ�Ĵ���*/
            NAS_LPP_RcvAortHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            /*������·�ERROR��Ϣ�Ĵ���*/
            NAS_LPP_RcvErrorHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_PassCheckLppDownLinkMsgHandle: Error DownLink Msg Type!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PassCheckLppDownLinkMsgHandle_ENUM, LNAS_LPP_ErrorDownlinMsgType);
            break;
    }

    return;
}
VOS_VOID NAS_LPP_SndUplinkAckMsg
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId
)
{
    VOS_UINT32                          ulLppMsgLen     = 0;
    VOS_UINT8                          *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity = {0};

    NAS_LPP_WARN_LOG("NAS_LPP_SndUplinkAckMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUplinkAckMsg_ENUM, LNAS_LPP_Func_Enter);

    /*�������֮�������Ĵ洢�ռ�*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_SndUplinkAckMsg:  Alloc Mem Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkAckMsg_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    /*���*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    NAS_LPP_EncodeAckMsgWithMsgIndentiy(pstMsgHead,
                                        &ulLppMsgLen,
                                        pucEncodeOutMsg,
                                        &stLppMsgIdentity,
                                        ulSessionId);
    /*���ͱ���õ����ݸ�����*/
    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    /*�ͷŶ�̬�ڴ�*/
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return;
}


/*****************************************************************************
Function Name   : NAS_LPP_NwMsgPreProcess
Description     : LPP��Ϣ��ǰһ������Ϣ�Ĵ���
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_NwMsgPreProcess
(
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity,
    NAS_LPP_MSG_HEAD_STRU                   *pstMsgHead,
    VOS_UINT32                               ulSessionId,
    VOS_UINT32                               ulMsgType
)
{
    VOS_UINT32                          ulRslt          = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_NwMsgPreProcess is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_Func_Enter);

    /*���ȿ�����LPP��Ϣ��û�д���������Ϣ��ACK�ظ�������ǣ�����*/
    if((NAS_LPP_SLCT == pstMsgHead->bitOpAcknowledgement)
       && (NAS_LPP_SLCT == pstMsgHead->stAcknowledgement.bitOpAckIndicator))
    {
        /*����������Ϣ��ȷ��*/
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DownlinkAckMsg);
        NAS_LPP_NwMsgWithAckIeHandle(pstMsgHead,
                                     ulSessionId);
    }

    if(NAS_LPP_NO_SLCT == pstMsgHead->bitOpLppMessageBody)
    {
        /*��Ϣ�岻���ڣ���˵�������տ���Ϣ������ACK��Ϣ*/
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DownlinkMsgNoLppMsgBody);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    /*����LPP��Ϣbody*/
    if((NAS_LPP_SLCT == pstMsgHead->bitOpAcknowledgement)
       && (PS_TRUE == pstMsgHead->stAcknowledgement.bAckRequested))
    {
        /*��Ҫ�ظ�ACK��Ϣ*/
        NAS_LPP_SndUplinkAckMsg(pstMsgHead, ulSessionId);

        pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_UP_LPP_ACK;
    }

    /*�ظ���Ϣ���*/
    ulRslt = NAS_LPP_MsgDuplicateDetect(ulSessionId,
                                        pstMsgHead->stSequenceNumber.ucSequenceNumber);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgProcess: Duplicate Lpp Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DuplicateDetect);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    return NAS_LPP_SUCCESS;
}



VOS_VOID NAS_LPP_NwMsgProcess
(
NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
VOS_UINT32                          ulSessionId,
VOS_UINT32                          ulMsgType,
NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{

    /*ͨ���ظ���Ϣ��⴦����Ϣ*/
    NAS_LPP_PassCheckLppDownLinkMsgHandle(pstMsgHead,
                                          ulSessionId,
                                          ulMsgType,
                                          pstLppTransIndex);

    return;
}
VOS_UINT32  NAS_LPP_SaveDownLinkCapReqMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_REQUEST_CAPABILITIES_R9_IES_STRU       *pstReqCapInfo       = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElement     = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkCapReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkCapReqMsg_ENUM, LNAS_LPP_Func_Enter);

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("save capability with wrong index", ucTransIndx);
        return  NAS_LPP_MSG_PROCESS_CMPL;
    }

    pstReqCapInfo   = NAS_LPP_GetDownLinkCapReqIEAddr(pstLppMsg);

    pstTransElement->stCapReq.bitOpEcidCapReq   = pstReqCapInfo->bitOpECIDRequestCapabilities;
    pstTransElement->stCapReq.bitOpOtdoaCapReq  = pstReqCapInfo->bitOpOTDOARequestCapabilities;
    pstTransElement->stCapReq.bitOpAgnssCapReq  = pstReqCapInfo->bitOpAGNSSRequestCapabilities;

    return  NAS_LPP_MSG_VERIFY_SUCC;
}


/*****************************************************************************
Function Name   : NAS_LPP_SaveOtdoaRefCell
Description     : �洢otdoa��ref cell
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveOtdoaRefCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaAssist,
NAS_LPP_SERVING_CELL_STRU          *pstServingCell,
NAS_LPP_OTDOA_ASSIST_CFG_STRU      *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    LPP_OTDOA_REF_CELL_INFO_STRU                *pstOtdoaRefCellInfo;

    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8 aucAntennaPortConfig[LPP_LRRC_OTDOA_ANT_PORT_BUTT] =
                                    {LPP_LRRC_OTDOA_ANT_PORT_1_OR_2, LPP_LRRC_OTDOA_ANT_PORT_4};

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8 aucPrsMutType[LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16};

    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8 aucNumFrams[LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT] =
                                    {LPP_LRRC_OTDOA_NUMDL_FRAMES_1,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_2,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_4,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_6};

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8 aucBandWidth[LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100};

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8 aucCpType[LPP_LRRC_OTDOA_CP_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_CP_TYPE_NORMAL,
                                     LPP_LRRC_OTDOA_CP_TYPE_EXTENDED};

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaRefCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaRefCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaReferenceCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg  = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);
    pstOtdoaRefCellInfo = &(pstOtdoaAssist->stOtdoaRefCellInfo);

    pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaRefCellCfg->usPhyCellId = pstOtdoaRefCellInfo->usPhyCellId;
    pstOtdoaRefCellCfg->ucCpLen     = aucCpType[pstOtdoaRefCellInfo->enCpLength];

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpCellGlobalId)
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->stCellGlobalIdInfo.ulCellIdentity = pstOtdoaRefCellInfo->stCellGlobalId.ulCellIdentity;

        /*����֮���ת��*/
        NAS_LPP_LppPlmn2NasPlmn( &pstOtdoaRefCellInfo->stCellGlobalId.stPlmnIdentity, pstOtdoaRefCellCfg->stCellGlobalIdInfo.aucPlmnId);
    }
    else
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    pstOtdoaRefCellCfg->ulEarfcn = NAS_LPP_GetRefEarfcnFromOtdoaAssis(&(pstOtdoaAssist->stOtdoaRefCellInfo));

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpAntennaPortConfig)
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->ucAntennaPortConfig = aucAntennaPortConfig[pstOtdoaRefCellInfo->enAntennaPortConfig];
    }
    else
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpPrsInfo)
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

        if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsMutingInfoR9 )
           &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsInfoExt) )
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoType
                = aucPrsMutType[pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.ulChoice];

            /*prs-MutingInfo-r9       CHOICE {
                    po2-r9                  BIT STRING (SIZE(2)),
                    po4-r9                  BIT STRING (SIZE(4)),
                    po8-r9                  BIT STRING (SIZE(8)),
                    po16-r9                 BIT STRING (SIZE(16)),
                    ...
                } �16bit��2���ֽ�*/

           /*usPo2R9,usPo4R9,usPo8R9,usPo16R9����16bit*/
           pstOtdoaRefCellCfg->stPrsInfo.usPrsMutingInfo = pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.u.usPo2R9;
        }
        else
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        }

        pstOtdoaRefCellCfg->stPrsInfo.ucPrsBandWidth = aucBandWidth[pstOtdoaRefCellInfo->stPrsInfo.enPrsBandWith];
        pstOtdoaRefCellCfg->stPrsInfo.ucNumdlFrames  = aucNumFrams[pstOtdoaRefCellInfo->stPrsInfo.enNumDlFrames];
        pstOtdoaRefCellCfg->stPrsInfo.usPrsConfigurationIndex = (VOS_UINT16)pstOtdoaRefCellInfo->stPrsInfo.ulPrsConfigIndex;
    }
    else
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}

/*****************************************************************************
Function Name   :
Description     : �洢otodoa��������Ϣ
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID   NAS_LPP_SaveOtdoaNghbrCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg;
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU           *pstOtdoaNeighbourCellInfo;
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement;
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    VOS_UINT32 ulLoop,i,ulFreqNum,ulCellNum;

    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8 aucAntennaPortConfig[LPP_LRRC_OTDOA_ANT_PORT_BUTT] =
                                    {LPP_LRRC_OTDOA_ANT_PORT_1_OR_2, LPP_LRRC_OTDOA_ANT_PORT_4};

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8 aucPrsMutType[LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16};

    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8 aucNumFrams[LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT] =
                                    {LPP_LRRC_OTDOA_NUMDL_FRAMES_1,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_2,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_4,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_6};

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8 aucBandWidth[LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100};

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8 aucCpType[LPP_LRRC_OTDOA_CP_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_CP_TYPE_NORMAL,
                                     LPP_LRRC_OTDOA_CP_TYPE_EXTENDED};

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaNghbrCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaNghbrCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaNeighbourCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);

    pstOtdoaNeighbourCellInfo = &(pstOtdoaAssist->stOtdoaNeighbourCellInfo);

    pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    ulFreqNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    for ( ulLoop = 0 ; ulLoop < ulFreqNum; ulLoop++ )
    {
        /*ȡÿ��Ƶ���һ����Ϊfreq layer��freq*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if ( (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
                &&(NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.bitOpARFCNValueEutraV9A0) )
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn = pstOtdoaRefCellCfg->ulEarfcn;
        }

        pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulCellNum
            = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        ulCellNum = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        for ( i = 0 ; i < ulCellNum; i++ )
        {
            pstOtdoaNghbrCellCfg = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].stOtdoaNeighbourCellInfoList[i];
            pstNgnbrCellElement  = &pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[i];

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpCellGlobalId)
            {
                pstOtdoaNghbrCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_VALID;
                pstOtdoaNghbrCellCfg->stCellGlobalIdInfo.ulCellIdentity = pstNgnbrCellElement->stCellGlobalId.ulCellIdentity;

                NAS_LPP_LppPlmn2NasPlmn(&pstNgnbrCellElement->stCellGlobalId.stPlmnIdentity,pstOtdoaNghbrCellCfg->stCellGlobalIdInfo.aucPlmnId);
            }
            else
            {
                pstOtdoaNghbrCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_INVALID;
            }

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpCpLength)
            {
                pstOtdoaNghbrCellCfg->ucCpLen = aucCpType[pstNgnbrCellElement->enCpLength];
            }
            else
            {
                /*The field is mandatory present if the cyclic prefix length is not the same as for the assistance data reference cell;
                      otherwise it is not present.*/
                pstOtdoaNghbrCellCfg->ucCpLen = pstOtdoaRefCellCfg->ucCpLen;
            }

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpPrsInfo)
            {
                pstOtdoaNghbrCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

                /*
                    PRS-Info ::= SEQUENCE {
                        prs-Bandwidth           ENUMERATED { n6, n15, n25, n50, n75, n100, ... },
                        prs-ConfigurationIndex  INTEGER (0..4095),
                        numDL-Frames            ENUMERATED {sf-1, sf-2, sf-4, sf-6, ...},
                        ...,
                        prs-MutingInfo-r9       CHOICE {
                            po2-r9                  BIT STRING (SIZE(2)),
                            po4-r9                  BIT STRING (SIZE(4)),
                            po8-r9                  BIT STRING (SIZE(8)),
                            po16-r9                 BIT STRING (SIZE(16)),
                            ...
                        }                                                       OPTIONAL                -- Need OP
                    }

                pstNgnbrCellElement->stPrsInfo.bitOpPrsInfoExt���ñ�ʾ "..."֮����Ƿ���Ч */

                if ( (NAS_LPP_SLCT == pstNgnbrCellElement->stPrsInfo.bitOpPrsMutingInfoR9)
                    &&(NAS_LPP_SLCT == pstNgnbrCellElement->stPrsInfo.bitOpPrsInfoExt))
                {
                    pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

                    pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoType = aucPrsMutType[pstNgnbrCellElement->stPrsInfo.stPrsMutingInfoR9.ulChoice];

                    pstOtdoaNghbrCellCfg->stPrsInfo.usPrsMutingInfo = pstNgnbrCellElement->stPrsInfo.stPrsMutingInfoR9.u.usPo2R9;
                }
                else
                {
                    pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
                }

                pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsBandWidth      = aucBandWidth[pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsBandWidth];
                pstOtdoaNghbrCellCfg->stPrsInfo.ucNumdlFrames       = aucNumFrams[pstOtdoaNghbrCellCfg->stPrsInfo.ucNumdlFrames];
                pstOtdoaNghbrCellCfg->stPrsInfo.usPrsConfigurationIndex = (VOS_UINT16)pstNgnbrCellElement->stPrsInfo.ulPrsConfigIndex;

            }
            else
            {
                pstOtdoaNghbrCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
            }

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpAntennaPortconfig)
            {
                pstOtdoaNghbrCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_VALID;
                pstOtdoaNghbrCellCfg->ucAntennaPortConfig = aucAntennaPortConfig[pstNgnbrCellElement->enAntennaPortConfig];
            }
            else
            {
                pstOtdoaNghbrCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_INVALID;
            }

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpSlotNumberOffset)
            {
                pstOtdoaNghbrCellCfg->ucSlotNumberOffsetFlag = LPP_LRRC_INFO_FLAG_VALID;

                pstOtdoaNghbrCellCfg->ucSlotNumberOffset = (VOS_UINT8)pstNgnbrCellElement->usSlotNumberOffset;
            }
            else
            {
                pstOtdoaNghbrCellCfg->ucSlotNumberOffsetFlag = LPP_LRRC_INFO_FLAG_INVALID;
            }

            if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpPrsSubFrameOffset)
            {
                pstOtdoaNghbrCellCfg->ucPrsSubFramOffsettFlag = LPP_LRRC_INFO_FLAG_VALID;

                pstOtdoaNghbrCellCfg->usPrsSubframeOffset = pstNgnbrCellElement->usPrsSubframeOffset;
            }
            else
            {
                pstOtdoaNghbrCellCfg->ucPrsSubFramOffsettFlag = LPP_LRRC_INFO_FLAG_INVALID;
            }

            pstOtdoaNghbrCellCfg->usPhyCellId    = (VOS_UINT16)pstNgnbrCellElement->ulPhysCellId;
            pstOtdoaNghbrCellCfg->usExpectedRSTD = pstNgnbrCellElement->usExpectedRSTD;
            pstOtdoaNghbrCellCfg->usExpectedRSTDUncertainty = pstNgnbrCellElement->usExpectedRSTDUncertainty;
        }
    }

}

/*****************************************************************************
Function Name   : NAS_LPP_SaveOtdoaAssistData
Description     : �洢otdoa�ĸ�������
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveOtdoaAssistData
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaAssist
)
{
    NAS_LPP_SERVING_CELL_STRU     *pstServingCell;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU *pstOtdoaAssisCfg;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaAssistData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstServingCell = NAS_LPP_GetServingCell();
    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    /*�����error���Ͳ��ô���������,ֱ�ӽ�����ǰ��OTDOA�ĸ������ݴ���*/
    if (NAS_LPP_SLCT == pstOtdoaAssist->bitOpOtdoaError)
    {
        NAS_LPP_ERR_LOG1("otdoa error cause", pstOtdoaAssist->stOtdoaError.u.stLocationServerErrorCauses.enOtdoaLocationServerErrorCause);
        pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return NAS_LPP_FAILURE;
    }

    NAS_LPP_SaveOtdoaRefCell(pstOtdoaAssist,pstServingCell,pstOtdoaAssisCfg);

    NAS_LPP_SaveOtdoaNghbrCell(pstOtdoaAssist,pstOtdoaAssisCfg);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name   : NAS_LPP_SaveGnssAssistData
Description     : �洢GNSS�ĸ�������
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveGnssAssistData
(
    LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU *pstAgnssAssist
)
{
    return NAS_LPP_SUCCESS;
}


VOS_UINT32  NAS_LPP_SaveDownLinkAssistDataProvideMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU        *pstProvideAssitDataR9;
    NAS_LPP_CONFIG_PARA_STRU                   *pstCfgPara;
    NAS_LPP_LOC_TECH_MAP_STRU                  *pstTechMap;
    VOS_UINT32 ulRslt;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkAssistDataProvideMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkAssistDataProvideMsg_ENUM, LNAS_LPP_Func_Enter);

    pstProvideAssitDataR9 = &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideAssistanceData.u.stC1.u.stProvideAssitDataR9);

    pstCfgPara = NAS_LPP_GetCfgPara();

    if (NAS_LPP_SLCT == pstProvideAssitDataR9->bitOpOTDOAProvideAssistData)
    {
        /*�����transaction���յ��ĵ�һ��otdoa ��assist data��Ҫ����ǰ��otdoa�Ĳ�����ɾ��  */
        if (NAS_LPP_NO_SLCT == pstCfgPara->bitOtdoaAssisChng)
        {
            NAS_LPP_MEM_SET(&pstCfgPara->stOtdoaAssisCfg, 0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));
        }

        ulRslt = NAS_LPP_SaveOtdoaAssistData(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData);
        if (NAS_LPP_SUCCESS == ulRslt)
        {
            pstCfgPara->bitOtdoaAssisChng = NAS_LPP_SLCT;
        }
        else
        {
            /*ֻ��Э���otdoa error������Ż᷵��save error,���ԣ����˳�����������gnss��*/
            pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;
            NAS_LPP_MEM_SET(&pstCfgPara->stOtdoaAssisCfg, 0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));
            NAS_LPP_ERR_LOG("save otdoa error");

            /*�����otdoa�Ĳ������ͷ�otdoa�Ĳ���,����cnf��*/
            pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstTechMap)
            {
                NAS_LPP_ReleasePosTechMeas(pstTechMap->ucSessionIndx,pstTechMap->ucSessionTranIndx,NAS_LPP_POSITION_TECH_OTDOA);
            }
        }
    }

    if (NAS_LPP_SLCT == pstProvideAssitDataR9->bitOpAGNSSProvideAssistData)
    {
        ulRslt = NAS_LPP_SaveGnssAssistData(&pstProvideAssitDataR9->stAGNSSProvideAssistanceData);
        if (NAS_LPP_SUCCESS == ulRslt)
        {
            pstCfgPara->bitGnssAssisChng = NAS_LPP_SLCT;
        }
        else
        {
             return ulRslt;
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
Function Name   : NAS_LPP_SaveCommCfgInfo
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveCommCfgInfo
(
    LPP_COMMON_IES_REQ_LOCATION_INFO_STRU   *pstCommonIEsReqLocationInfo,
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo
)
{
    VOS_UINT8 aucRptAmnt[LPP_REPORT_AMOUNT_BUTT] = {1,2,4,8,16,32,64,0};
    VOS_UINT32 aulRptIntvl[LPP_REPORT_INTERVAL_BUTT] = {0,1000,2000,4000,8000,10000,16000,20000,32000,64000};
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16  aenRptIntvl[LPP_REPORT_INTERVAL_BUTT] =
    {   LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, /* �˶�ӦLPP�տ���Ϣ��ӦLPP_REPORT_INTERVAL_NO_PERIOD_REPORT�����Σ���������*/
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_2,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_4, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_8,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_10,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_20,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_32,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_64
    };

    NAS_LPP_NORM_LOG("NAS_LPP_SaveCommCfgInfo enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveCommCfgInfo_ENUM, LNAS_LPP_Func_Enter);

    /*�洢qos*/
    if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpQos)
    {
        pstLppCommCfgInfo->bitOpQos = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY(&pstLppCommCfgInfo->stQos, &pstCommonIEsReqLocationInfo->stQos, sizeof(LPP_MTA_COMMON_QOS_STRU));
    }

    /*�洢environment*/
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpEnvironment )
    {
        pstLppCommCfgInfo->enEnvironment = pstCommonIEsReqLocationInfo->enEnvironment;
    }
    else
    {
        pstLppCommCfgInfo->enEnvironment = LPP_ENVIRONMENT_BUTT;
    }

    /*�洢additional*/
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOPAddtionInfo )
    {
        pstLppCommCfgInfo->enAdditonInfo = pstCommonIEsReqLocationInfo->enAdditonInfo;
    }
    else
    {
        pstLppCommCfgInfo->enAdditonInfo = LPP_ADDITON_REPORT_ONLY_RETURN_INFO_REQ;
    }

    pstLppCommCfgInfo->enLocationInformationType = pstCommonIEsReqLocationInfo->enLocationInformationType;

    /*�洢bitOpLocationCoordinateType*/
    pstLppCommCfgInfo->bitOpLocationCoordinateType = pstCommonIEsReqLocationInfo->bitOpLocationCoordinateType;
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpLocationCoordinateType )
    {
        NAS_LPP_MEM_CPY(&pstLppCommCfgInfo->stLocationCoordinateType,
                        &pstCommonIEsReqLocationInfo->stLocationCoordinateType,
                        sizeof(LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU));
    }

    /*�洢bitOPVelocityTypes*/
    pstLppCommCfgInfo->bitOPVelocityTypes = pstCommonIEsReqLocationInfo->bitOPVelocityTypes;
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOPVelocityTypes )
    {
        NAS_LPP_MEM_CPY(&pstLppCommCfgInfo->stVeloctytype,
                        &pstCommonIEsReqLocationInfo->stVeloctytype,
                        sizeof(LPP_MTA_COMMON_VELOCITY_TYPE_STRU));
    }

    /*�洢�ϱ�׼��: �����ϱ������ȼ�,period>response>triger*/
    if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpPeriodicalReportCriteria)
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_PERIOD;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_PERIODICAL_REPORT;

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount
            = aucRptAmnt[pstCommonIEsReqLocationInfo->stPeriodReport.enReportAmount];

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval
            = aulRptIntvl[pstCommonIEsReqLocationInfo->stPeriodReport.enReportInterval];

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.enOtdoaRprtInterval
            = aenRptIntvl[pstCommonIEsReqLocationInfo->stPeriodReport.enReportInterval];
    }
    else if ( (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpQos)
            &&(NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->stQos.bitOpResponseTime))
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_ONCE;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_RESPONSE_TIMER;

        pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime
            = (VOS_UINT32)(pstCommonIEsReqLocationInfo->stQos.stResponseTime.ucTime) *1000;/*sת��ms*/
    }
    else if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpTriggeredReportCriteria)
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_REPORT_DURATION;

        pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration
            = (VOS_UINT32)(pstCommonIEsReqLocationInfo->stTriggerReportCriteria.ulReportDuration) *1000;/*sת��ms*/
    }
    else
    {
        NAS_LPP_ERR_LOG("no report criteria");
    }

}
VOS_UINT32  NAS_LPP_SaveDownLinkLoctionReqMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU          *pstReqLocationInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_LOCATION_REQ_STRU                  *pstLocationReqBuff  = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElement     = NAS_LPP_NULL_PTR;
    NAS_LPP_COMM_CONFIG_INFO_STRU              *pstLppCommCfgInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU        *pstSessionEntity    = NAS_LPP_NULL_PTR;
    NAS_LPP_CONFIG_PARA_STRU                   *pstConfigPara       = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                       stMsgHead;
    NAS_LPP_LOC_TECH_RUNING_STRU               *pstRunLocTech;
    VOS_UINT32 ulLoop;
    VOS_UINT8 ucIndex;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkLoctionReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR  == pstSessionEntity)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("save request with wrong index", ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_DontFindTransaction);
        return  NAS_LPP_MSG_VERIFY_FAIL;
    }

    /*����NW����λ�������Ϣ���Ա�����*/
    pstReqLocationInfo  = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);
    pstLocationReqBuff  = NAS_LPP_GetLocationReqBuff();
    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    pstConfigPara = NAS_LPP_GetCfgPara();

    /*��֧��ͬһ��transaction���Ⱥ�2��request location information����������ִ�����������������Ϣ*/
    if (pstTransElement->ucCommCfgIndex < NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG2("discard loc request, ucSessionIndx,ucTransIndx", ucSessionIndx,ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_SamePosTechError);
        NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                &pstTransElement->stTransId,
                                 LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                 VOS_FALSE,
                                 VOS_FALSE);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    /*���location request��Ҫ��Ķ�λ������֮ǰ�Ѿ������еģ��ܾ����淢�����Ķ�λ����:
      1)���location request��Ҫ��Ķ�λ�����в�����֮ǰ��û�еģ�����ѡ�������ⲿ�����·��Ķ�λ������
      2)���location request��Ҫ��Ķ�λ������֮ǰ�������У���������Ϣ������ABORT*/
    for ( ulLoop = 0 ; ulLoop < pstRunLocTech->ucNum; ulLoop++ )
    {
        if (NAS_LPP_POSITION_TECH_ECID == pstRunLocTech->astLocTechMap[ulLoop].enPositionTech)
        {
            pstReqLocationInfo->bitOpEcidReqLocationInfo = NAS_LPP_NO_SLCT;
        }
        else if (NAS_LPP_POSITION_TECH_OTDOA == pstRunLocTech->astLocTechMap[ulLoop].enPositionTech)
        {
            pstReqLocationInfo->bitOpOtdoaReqLocationInfo = NAS_LPP_NO_SLCT;
        }
        else//GNSS
        {
            pstReqLocationInfo->bitOpAGNSSReqLocationInfo = NAS_LPP_NO_SLCT;
        }
    }

    /*��������Ϣ,��LPP ACK*/
    if ( (NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
       &&(NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
       &&(NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo) )
    {
        NAS_LPP_ERR_LOG("all loc tech are already run,discard this lpp msg");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_SamePosTechError);
        NAS_LPP_SaveLppMsgHead(&stMsgHead,pstLppMsg);
        NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                &pstTransElement->stTransId,
                                 LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                 VOS_FALSE,
                                 VOS_FALSE);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpCommonIEsReqLocationInfo)
    {
        /*������comm��Ϣ�Ĵ洢��ַ*/
        ucIndex = NAS_LPP_MallocCommCfgInfoElementIndex(ucTransIndx);
        pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(ucIndex);
        if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo)
        {
            NAS_LPP_ERR_LOG("save req fail malloc comm buffer");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_MallocCfgBufferFail);
            return  NAS_LPP_MSG_PROCESS_CMPL;
        }

        /*��¼��comm �ĵ�ַ*/
        pstTransElement->ucCommCfgIndex = ucIndex;

        NAS_LPP_SaveCommCfgInfo(&pstReqLocationInfo->stCommonIEsReqLocationInfo, pstLppCommCfgInfo);
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
    {
        pstLocationReqBuff->bitOpEcidLocReq  = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY(&(pstLocationReqBuff->stEcidReqLocationInfo),
                        &(pstReqLocationInfo->stEcidReqLocationInfo),
                        sizeof(LPP_ECID_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitEcidReq = NAS_LPP_SLCT;
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
    {
        pstLocationReqBuff->bitOpOtdoaLocReq = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY(&(pstLocationReqBuff->stOtdoaReqLocationInfo),
                        &(pstReqLocationInfo->stOtdoaReqLocationInfo),
                        sizeof(LPP_OTDOA_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitOtdoaReq = NAS_LPP_SLCT;
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo)
    {
        pstLocationReqBuff->bitOpAgnssLocReq = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY(&(pstLocationReqBuff->stAGNSSReqLocationInfo),
                        &(pstReqLocationInfo->stAGNSSReqLocationInfo),
                        sizeof(LPP_AGNSS_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitGnssReq = NAS_LPP_SLCT;
    }

    /*���浱ǰ��Ч�Ķ�λ����*/
    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_ECID,ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA,ucSessionIndx,ucSessionTransIndx,ucTransIndx);

    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS,ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    }

    return  NAS_LPP_MSG_VERIFY_SUCC;
}


VOS_UINT32  NAS_LPP_SaveDownLinkMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    VOS_UINT32                          ulMsgType       = 0;
    VOS_UINT32                          ulReturnRslt    = NAS_LPP_MSG_PROCESS_CMPL;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkMsg_ENUM, LNAS_LPP_Func_Enter);

    ulMsgType       = NAS_LPP_GetDownlinkMsgType(pstLppMsg);

    switch(ulMsgType)
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN:
            ulReturnRslt = NAS_LPP_SaveDownLinkCapReqMsg(pstLppMsg, ucSessionIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN:
            /*���ڸ���������Ϣ�ı��棬Ŀǰ���OTDOA, GNSS�������׶�����*/
            ulReturnRslt = NAS_LPP_SaveDownLinkAssistDataProvideMsg(pstLppMsg, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN:
            /*����locationReq����Ϣ*/
            ulReturnRslt = NAS_LPP_SaveDownLinkLoctionReqMsg(pstLppMsg, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            ulReturnRslt = NAS_LPP_MSG_VERIFY_SUCC;
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            ulReturnRslt = NAS_LPP_MSG_VERIFY_SUCC;
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_SaveDownLinkMsg: Error DownLink Msg Type!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkMsg_ENUM, LNAS_LPP_ErrorDownLinkMsgType);
            break;
    }

    return ulReturnRslt;

}


VOS_VOID  NAS_LPP_SaveLppMsgHead
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    LPP_MESSAGE_STRU                   *pstLppMsgBuff
)
{
    NAS_LPP_NORM_LOG("NAS_LPP_SaveLppMsgHead is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveLppMsgHead_ENUM, LNAS_LPP_Func_Enter);

    pstMsgHead->bEndTransaction         = pstLppMsgBuff->bEndTransaction;
    pstMsgHead->bitOpAcknowledgement    = pstLppMsgBuff->bitOpAcknowledgement;
    pstMsgHead->bitOpLppMessageBody     = pstLppMsgBuff->bitOpLppMessageBody;
    pstMsgHead->bitOpLppTransactionId   = pstLppMsgBuff->bitOpLppTransactionId;
    pstMsgHead->bitOpSequenceNumber     = pstLppMsgBuff->bitOpSequenceNumber;

    NAS_LPP_MEM_CPY(&(pstMsgHead->stTransactionId),
                    &(pstLppMsgBuff->stTransactionId),
                    sizeof(LPP_TRANSACTION_ID_STRU));

    NAS_LPP_MEM_CPY(&(pstMsgHead->stSequenceNumber),
                    &(pstLppMsgBuff->stSequenceNumber),
                    sizeof(LPP_SEQUENCE_NUMBER_STRU));

    NAS_LPP_MEM_CPY(&(pstMsgHead->stAcknowledgement),
                    &(pstLppMsgBuff->stAcknowledgement),
                    sizeof(LPP_ACKNOWLEDGEMENT_STRU));

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_FirstAssistDataAndStartProtectTimer
Description     :  �ж�transaction�ĵ�һ���Ƿ���assist data
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-7  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_FirstLppMsgIsAssistData
(
    VOS_UINT32                          ulSessionId,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    NAS_LPP_TRANS_ID_STRU                   stTransId;
    VOS_UINT8                               ucSessionTransIndx;

    if (LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN != pstLppMsg->stLppMessageBody.u.stC1.ulChoice)
    {
        return VOS_FALSE;
    }

    stTransId.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;

    pstTransEntity = NAS_LPP_SearchTransEntity(ulSessionId,
                                               &(stTransId),
                                               &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_NORM_LOG("assist data is first lpp msg for transaction !");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LPP_DecodeFailProcess
Description     : ������ʧ�ܵ���Ϣ���ظ�����
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.wangensheng      2015-9-8  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DecodeFailProcess
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulDecodeFailRslt,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    VOS_UINT8                           ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
    NAS_LPP_TRANS_ID_STRU               stTransID;

    /* ���������ԭ��ֵӳ��Ϊ��Ϣ����ԭ��ֵ */
    switch ( ulDecodeFailRslt )
    {
        case NAS_LPP_DECODE_MSG_HEADER_ERROR_INCORRECT_VALUE:
        case NAS_LPP_DECODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TOO_SHORT:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_HEADER_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TYPE_NON_EXIST:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_UNDEFINED_ERROR:
        case NAS_LPP_DECODE_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;
        case NAS_LPP_DECODE_MSG_EPDU_ERROR_VALUE_ERROR:

            ucErrorType = LPP_COMMON_IES_ERROR_EPDU_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR:

            ucErrorType = LPP_COMMON_IES_ERROR_INCORRECT_DATA_VALUE;
            break;
        default:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;

    }

    stTransID.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransID.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;

    NAS_LPP_SndUpLppErrorMsg(ulSessionId,&stTransID,ucErrorType,PS_TRUE,PS_TRUE);
}

/*****************************************************************************
Function Name   : NAS_LPP_DownLinkMsgFailProcess
Description     : ������ʧ�ܵ���Ϣ���ظ�����
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.wangensheng      2015-9-8  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_DownLinkMsgFailProcess
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulDecodeFailRslt,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    VOS_UINT8                           ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
    NAS_LPP_TRANS_ID_STRU               stTransID;

    /* ���������ԭ��ֵӳ��Ϊ��Ϣ����ԭ��ֵ */
    switch ( ulDecodeFailRslt )
    {
        case NAS_LPP_MSG_VERIFY_HEAD_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_HEADER_ERROR;
            break;
        case NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR:
        case NAS_LPP_MSG_VERIFY_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR;
            break;

        default:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;

    }

    stTransID.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransID.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;
    NAS_LPP_SndUpLppErrorMsg(ulSessionId,&stTransID,ucErrorType,PS_TRUE,PS_TRUE);
}
VOS_VOID  NAS_LPP_RcvLppEmmDataInd(LMM_LPP_DATA_IND_STRU *pRcvMsg )
{
    VOS_UINT32                              ulRslt          = 0;
    VOS_UINT32                              ulRcvNwMsgLen   = 0;
    LPP_MESSAGE_STRU                       *pstLppMsgBuff   = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                   stMsgHead;
    VOS_UINT32                              ulMsgType       = 0;
    VOS_UINT8                               ucSessionIndx   = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               ucTransIndx     = 0;
    VOS_UINT8                               ucSessionTransIndx = 0;
    VOS_UINT32                              ulReturnRslt    = 0;
    NAS_LPP_TRANS_INDEX_STRU                stLppTransIndex;
    VOS_BOOL                                bFirstLppMsgIsAssistData;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmDataInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_Func_Enter);

    ulRcvNwMsgLen = pRcvMsg->stLppMsg.ulLppMsgSize;
    if( ulRcvNwMsgLen > LPP_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd:WARNING:EMM->LPP Message NW Msg over-long!");
        ulRcvNwMsgLen = LPP_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*���LPP MSG BUFF*/
    NAS_LPP_ClearLppMsgBuff();

    /*��ȡLPP MSG BUFF*/
    pstLppMsgBuff = NAS_LPP_GetLppMsgBuff();

    /*�տڽ���*/
    ulRslt = NAS_LPP_DecodeMessage(pRcvMsg->stLppMsg.aucLppMsg,
                                   ulRcvNwMsgLen,
                                   pstLppMsgBuff);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        /*���벻�ɹ�*/
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd: Decode Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_DecodeError);

        /*���ݲ�ͬ��ԭ��ֵ��ӳ�䵽�տڿ���ʶ���ԭ��ֵ��Ȼ������෢��ERROR��Ϣ*/
        /*TODO_error*/
        NAS_LPP_DecodeFailProcess( pRcvMsg->ulSessionId, ulRslt, pstLppMsgBuff);
        return;
    }

    /*��ȡ��ǰ�տ���Ϣ����*/
    ulMsgType = NAS_LPP_GetDownlinkMsgType(pstLppMsgBuff);

    /*����ɹ���������Ϣasn�ļ��*/
    ulRslt = NAS_LPP_CheckDownLinkMsg(pstLppMsgBuff);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd: Verify Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_VerifyFail);
        /*�տ�У��ʧ�ܣ�������෢��ERROR��Ϣ*/
        /*TODO_error*/
        /*������ص���NAS_LPP_MSG_VERIFY_HEAD_FAIL���������ظ�ERRORͷ����*/
        /*������ص���NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR��Ҳ������
        �ظ�ERROR����Ϣ�����*/
        NAS_LPP_DownLinkMsgFailProcess( pRcvMsg->ulSessionId, ulRslt, pstLppMsgBuff);
        return;
    }

    /*ȡ��LPP��Ϣͷͷ*/
    NAS_LPP_SaveLppMsgHead(&stMsgHead, pstLppMsgBuff);

    /*�ж��Ƿ���������assist data �ı�����ʱ��:
        1�� ���provide assist data ��transaction�ĵĵ�һ����Ϣ����Ҫ����������ʱ��;
        2�� �����ue��������ģ����յ�����cnf������*/
    bFirstLppMsgIsAssistData = NAS_LPP_FirstLppMsgIsAssistData(pRcvMsg->ulSessionId,pstLppMsgBuff);

    /*�����������̵ĶԳ崦��:*/
    if ( (NAS_LPP_SLCT == pstLppMsgBuff->bitOpLppMessageBody)
       &&(LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN == pstLppMsgBuff->stLppMessageBody.u.stC1.ulChoice) )
    {
        if (NAS_LPP_ASSIST_DATA_CONFLICT == NAS_LPP_ProvideAssistDataConflictProcess(bFirstLppMsgIsAssistData,pRcvMsg->ulSessionId) )
        {
            /*����LPP��Ϣbody*/
            if( (NAS_LPP_SLCT == stMsgHead.bitOpAcknowledgement)
              &&(PS_TRUE == stMsgHead.stAcknowledgement.bAckRequested) )
            {
                /*��Ҫ�ظ�ACK��Ϣ*/
                NAS_LPP_SndUplinkAckMsg(&stMsgHead, pRcvMsg->ulSessionId);
            }
            return;
        }
    }

    /*��ȡtransactionʵ��*/
    pstTransEntity = NAS_LPP_VerifyOrCreateTransaction(&stMsgHead,
                                                       pRcvMsg->ulSessionId,
                                                       &ucTransIndx,
                                                       &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Transcation Alloc Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_CanntAllocTransEntity);
        return;
    }

    /*��Ϣ���ظ��Լ�飬����ack�Ĵ���*/
    ulRslt = NAS_LPP_NwMsgPreProcess(pstTransEntity,&stMsgHead, pRcvMsg->ulSessionId, ulMsgType);

    /*���������ɣ�������������˳�*/
    if (NAS_LPP_MSG_PROCESS_CMPL == ulRslt)
    {
        return;
    }

    /*���transactionʵ��������Լ������±��Լ��ṹָ��*/
    stLppTransIndex.pstTransEntity      = pstTransEntity;
    stLppTransIndex.ucTransIndx         = ucTransIndx;
    stLppTransIndex.ucSessionTransIndx  = ucSessionTransIndx;

    /*��ȡsessionIndx����ʱһ������Sessionʵ��*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(pRcvMsg->ulSessionId);

    /*��������assist data�ı�����ʱ��*/
    if ( (VOS_TRUE == bFirstLppMsgIsAssistData)&& ( VOS_FALSE == pstLppMsgBuff->bEndTransaction))
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_ASSISTDATA,LPP_SS_ASSISTDATA_WAIT_CN_CNF);
    }

    /*�������пտ���Ϣ*/
    ulReturnRslt = NAS_LPP_SaveDownLinkMsg(pstLppMsgBuff, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulReturnRslt)
    {
        return ;
    }

    /*У��ɹ�, ������Ϣ*/
    NAS_LPP_NwMsgProcess(&stMsgHead,
                         pRcvMsg->ulSessionId,
                         ulMsgType,
                         &stLppTransIndex);

    return;
}
VOS_VOID NAS_LPP_RcvLppEmmStartInd( LMM_LPP_START_IND_STRU *pRcvMsg )
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmStartInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmStartInd_ENUM, LNAS_LPP_Func_Enter);

    /*��ʼ��LPP����ص�ȫ��ʵ��*/
    NAS_LPP_LppCtxInit();

    /*��ȡnv*/
    NAS_LPP_ReadLppNvConfig();

    return;
}


VOS_VOID NAS_LPP_RcvLppEmmStopInd( LMM_LPP_STOP_IND_STRU *pRcvMsg )
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmStopInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmStopInd_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_ReleaseAllSession();
    NAS_LPP_MEM_SET(NAS_LPP_GetLppEntityCtx(), 0, sizeof(NAS_LPP_ENTITY_STRU));
    g_ulEmmLppOpId = 0;
    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_RcvLppEmmCellChngInd
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLppEmmCellChngInd( LMM_LPP_CELL_CHANGE_IND *pRcvMsg)
{
    NAS_LPP_SERVING_CELL_STRU   *pstServingCell;
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmCellChngInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmCellChngInd_ENUM, LNAS_LPP_Func_Enter);

    pstServingCell = NAS_LPP_GetServingCell();

    pstServingCell->ulEarfcn    = pRcvMsg->ulEarfcn;
    pstServingCell->usPhyCellId = pRcvMsg->usPhyCellId;
    pstServingCell->ulCellIdentity = pRcvMsg->ulCellId;

    /*3������aucPlmnId�ĳ���*/
    NAS_LPP_MEM_CPY(pstServingCell->aucPlmnId, pRcvMsg->aucPlmnId, 3);
}
VOS_VOID NAS_LPP_RcvLppEmmRelInd( LMM_LPP_START_IND_STRU *pRcvMsg )
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmRelInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmRelInd_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_ReleaseAllSession();

    return;
}


VOS_VOID NAS_LPP_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_EmmMsgDistr is entered!");

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_EmmMsgDistr_ENUM, LNAS_LPP_Func_Enter, pEmmMsg->ulMsgName);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_LMM_LPP_DATA_IND:
            NAS_LPP_RcvLppEmmDataInd((LMM_LPP_DATA_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_EST_CNF:
            NAS_LPP_RcvLppEmmEstCnf((LMM_LPP_EST_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_DATA_CNF:
            NAS_LPP_RcvLppEmDataCnf((LMM_LPP_DATA_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_START_IND:
            NAS_LPP_RcvLppEmmStartInd((LMM_LPP_START_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_STOP_IND:
            NAS_LPP_RcvLppEmmStopInd((LMM_LPP_STOP_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_CELL_CHANGE_IND:
            NAS_LPP_RcvLppEmmCellChngInd((LMM_LPP_CELL_CHANGE_IND *)pRcvMsg);
            break;

        case ID_LMM_LPP_REL_IND:
            NAS_LPP_RcvLppEmmRelInd((LMM_LPP_START_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EmmMsgDistr:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EmmMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
            break;
    }

    return;
}
/*lint +e701*/
#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLppEmmMsgProc.c */
