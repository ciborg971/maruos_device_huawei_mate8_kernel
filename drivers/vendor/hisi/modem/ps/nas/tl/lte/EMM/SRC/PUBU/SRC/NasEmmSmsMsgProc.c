/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmSmsMsgProc.c
  Description     :
  History         :
     1.sunbing 49683      2011-11-3   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include  "NasLmmPubMFsm.h"
#include  "NasEmmPubUGlobal.h"
#include  "NasLmmPubMOsa.h"

#include  "NasEmmSmsInterface.h"
#include  "NasLmmPubMStack.h"
#include  "NasEmmSmsMsgProc.h"
#include  "NasEmmMrrcPubInterface.h"
#include  "NasEmmAttDetInclude.h"
#include  "NasLmmPubMOm.h"

/*lint -e767*/
#define    PS_FILE_ID_NASEMMSMSMSGPROC_C   3000
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSMSMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSMSMSGPROC_C
/*lint +e767*/



/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name   : NAS_LMM_SndLmmSmsEstCnf
 Description     : ���ͽ����ɹ���Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing 49683      2011-11-3  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_LMM_SndLmmSmsEstCnf( VOS_VOID )
{
    LMM_SMS_EST_CNF_STRU            *pLmmSmsEstCnfMsg;

    /*������Ϣ�ڴ�*/
    pLmmSmsEstCnfMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_SMS_EST_CNF_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pLmmSmsEstCnfMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pLmmSmsEstCnfMsg,0,sizeof(LMM_SMS_EST_CNF_STRU));

    /* �����Ϣͷ */
    NAS_LMM_COMP_SMS_MSG_HEADER( pLmmSmsEstCnfMsg,
                                 sizeof(LMM_SMS_EST_CNF_STRU)-NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pLmmSmsEstCnfMsg->ulMsgId          = ID_LMM_SMS_EST_CNF;

    /*�����Ϣ����*/
    pLmmSmsEstCnfMsg->ulOpId           = 0;

    NAS_LMM_SEND_MSG(pLmmSmsEstCnfMsg);
}


/*****************************************************************************
 Function Name   : NAS_LMM_SndLmmSmsErrInd
 Description     : ������Ϣ֪ͨSMSģ�飬û����·͸��SMS��Ϣ
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing 49683      2011-11-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_ENUM_UINT32  enErrCause)
{
    LMM_SMS_ERR_IND_STRU            *pLmmSmsErrIndMsg;

    /*������Ϣ�ڴ�*/
    pLmmSmsErrIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_SMS_ERR_IND_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pLmmSmsErrIndMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pLmmSmsErrIndMsg,0,sizeof(LMM_SMS_ERR_IND_STRU));

    /* �����Ϣͷ */
    NAS_LMM_COMP_SMS_MSG_HEADER( pLmmSmsErrIndMsg,
                                 sizeof(LMM_SMS_ERR_IND_STRU)-NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pLmmSmsErrIndMsg->ulMsgId          = ID_LMM_SMS_ERR_IND;

    /*�����Ϣ����*/
    pLmmSmsErrIndMsg->ulOpId           = 0;

    pLmmSmsErrIndMsg->enErrCause       = enErrCause;


    NAS_LMM_SEND_MSG(pLmmSmsErrIndMsg);

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_CompCnUplinkNasTransportMsg
  Input     : pMsg         :SMS͸����������Ϣ
                pulIndex     : �������룬Ҳ�����
  Output   :pucCnNasMsg  : ָ�� LRRC_LNAS_MSG_STRU.aucNasMsg
  NOTE     :
  Return   :VOS_VOID
  History  :
    1.  FTY  2011.11.15  �¹�����

*******************************************************************************/
VOS_VOID NAS_EMM_SMS_CompCnUplinkNasTransportMsg
               (VOS_UINT8 *pucCnNasMsg, VOS_UINT32 *pulIndex, const LMM_SMS_MSG_STRU * pSmsMsg)
{
    VOS_UINT32 ulIndex = NAS_LMM_NULL;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SMS_CompCnUplinkNasTransportMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SMS_CompCnUplinkNasTransportMsg_ENUM,LNAS_ENTRY);

    /* ��� Protocol Discriminator + Security header type */
    pucCnNasMsg[ulIndex++] = EMM_CN_MSG_PD_EMM;

    /* ���UpLink nas transort message identity   */
    pucCnNasMsg[ulIndex++] = NAS_EMM_CN_MT_UPLINK_NAS_TRANSPORT;

    /*���NAS msg*/
    pucCnNasMsg[ulIndex++] = (VOS_UINT8)pSmsMsg->ulSmsMsgSize;
    NAS_LMM_MEM_CPY(&(pucCnNasMsg[ulIndex]),
                      pSmsMsg->aucSmsMsg,
                      pSmsMsg->ulSmsMsgSize);
    ulIndex += pSmsMsg->ulSmsMsgSize;

    *pulIndex += ulIndex;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg
  Input    :pMsg         :SMS͸����������Ϣ
  Output   :pMrrcDataReqMsg  : ָ�� LRRC_LNAS_MSG_STRU
  NOTE     :
  Return   :
  History  :
    1.  FTY  2011.11.15  �¹�����

*******************************************************************************/
VOS_VOID NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg
                    (NAS_EMM_MRRC_DATA_REQ_STRU *pMrrcDataReqMsg, const LMM_SMS_MSG_STRU * pSmsMsg)
{
    VOS_UINT32               uldataReqMsgLenNoHeader   = NAS_LMM_NULL;
    VOS_UINT32               ulCnNasMsgLen             = NAS_LMM_NULL;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_CompMsgUpLinkNasTransportMrrcDataReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg_ENUM,LNAS_ENTRY);

    /*����MRRC_DATA_REQ �е� NAS_MSG_STRU,��CN��Ϣ(Compose the msg of):UpLink NAS Transport*/
    NAS_EMM_SMS_CompCnUplinkNasTransportMsg(pMrrcDataReqMsg->stNasMsg.aucNasMsg, &ulCnNasMsgLen, pSmsMsg);

    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = ulCnNasMsgLen;

    uldataReqMsgLenNoHeader = NAS_EMM_CountMrrcDataReqLen(ulCnNasMsgLen);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < uldataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg, Size error ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg_ENUM,LNAS_ERROR);

        return ;
    }

    /* ��дMRRC_DATA_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, uldataReqMsgLenNoHeader);

    /* ��дMRRC_DATA_REQ ����ϢID��ʶ */
    pMrrcDataReqMsg->ulMsgId                 = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��� NAS_EMM_NAS_UPLINK_NAS_TRANSPORT*/
    pMrrcDataReqMsg->enEstCaue     = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pMrrcDataReqMsg->enCallType    = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pMrrcDataReqMsg->enEmmMsgType  = NAS_EMM_NAS_UPLINK_NAS_TRANSPORT;
    pMrrcDataReqMsg->enDataCnf     = LRRC_LMM_DATA_CNF_NOT_NEED;
    pMrrcDataReqMsg->ulEsmMmOpId   = NAS_LMM_OPID;

    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_LMM_SendMrrcDataReq_SMS
  Input    : pMsg         :SMS͸����������Ϣ
  Output   :
  NOTE     :
  Return   :VOS_VOID
  History  :
    1.  FTY  2011.11.14  �¹�����

*******************************************************************************/
VOS_VOID    NAS_EMM_SMS_SendMrrcDataReq_SmsData( MsgBlock * pMsg)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    SMS_LMM_DATA_REQ_STRU               *pRcvSmsMsg        = NAS_EMM_NULL_PTR ;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SMS_SendMrrcDataReq_SmsData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SMS_SendMrrcDataReq_SmsData_ENUM,LNAS_ENTRY);

    if (NAS_EMM_NULL_PTR == pMsg)
    {
        /*��ӡ����*/
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SMS_SendMrrcDataReq_SmsData: Input para is invalid!--pMsg is NULL!");
         TLPS_PRINT2LAYER_ERROR(NAS_EMM_SMS_SendMrrcDataReq_SmsData_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* �������Ϣ��������DOPRA��Ϣ */
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    pRcvSmsMsg = (SMS_LMM_DATA_REQ_STRU *)pMsg;

    /* ����MRRC_DATA_REQ ��Ϣ*/
    NAS_EMM_SMS_CompMsgUpLinkNasTransportMrrcDataReqMsg(pMrrcDataReqMsg,  &(pRcvSmsMsg->stSmsMsg));

    /* zhaochen 00308719 begin for SMS Message hook */
    if (NAS_EMM_NO == NAS_LMM_IsMsgContainsSMS(pMrrcDataReqMsg->stNasMsg.ulNasMsgSize, &pMrrcDataReqMsg->stNasMsg.aucNasMsg[0]))
    {
        /*�տ���Ϣ�ϱ� UPLINK NAS TRANSPORT*/
        NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_UPLINK_NAS_TRANSPORT,(NAS_MSG_STRU *)&(pMrrcDataReqMsg->stNasMsg));
    }
    /* zhaochen 00308719 end for SMS Message hook */

    /*�ؼ��¼��ϱ� UPLINK NAS TRANSPORT*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_EMM_UPLINK_NAS_TRANSPORT);

    /* ������Ϣ(Send the msg of) MRRC_DATA_REQ(UPLINK NAS TRANSPORT) */
    NAS_EMM_SndUplinkNasMsg(pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;

}



VOS_UINT32  NAS_EMM_IsSmsNotRetransmitConditionSatisfied
(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32    *penErrCause
)
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32    enUeOperationMode = NAS_LMM_UE_MODE_BUTT;

    enUeOperationMode = NAS_LMM_GetEmmInfoUeOperationMode();

    /* PS ONLY */
    if  ( (NAS_LMM_UE_PS_MODE_1 == enUeOperationMode)
        ||(NAS_LMM_UE_PS_MODE_2 == enUeOperationMode) )
    {
        *penErrCause = LMM_SMS_ERR_CAUSE_UE_MODE_PS_ONLY;
        return NAS_EMM_YES;
    }

    /* #2��CS����Ч */
    if ( NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag() )
    {
        *penErrCause = LMM_SMS_ERR_CAUSE_USIM_CS_INVALID;
        return NAS_EMM_YES;
    }

    /* #18��CS�򲻿��� */
    if ( NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag() )
    {
        *penErrCause = LMM_SMS_ERR_CAUSE_CS_SER_NOT_AVAILABLE;
        return NAS_EMM_YES;
    }

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* CS������ע�� */
    if ( NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetCsAttachAllowFlg() )
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_IsSmsNotRetransmitConditionSatisfied: Cs attach not allowed!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsNotRetransmitConditionSatisfied_ENUM,LNAS_FUNCTION_LABEL1);
        *penErrCause = LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED;
         return NAS_EMM_YES;
    }

    /* PS������ע�� */
    if ( NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetPsAttachAllowFlg() )
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_IsSmsNotRetransmitConditionSatisfied: Ps attach not allowed!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsNotRetransmitConditionSatisfied_ENUM,LNAS_FUNCTION_LABEL2);
        *penErrCause = LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED;
         return NAS_EMM_YES;
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    return NAS_EMM_NO;

}
VOS_UINT32  NAS_EMM_SomeStateRcvSmsMsgCommProc(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause = LMM_SMS_ERR_CAUSE_OTHERS;

    /* ��ȡ��ǰ״̬ */
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                      NAS_EMM_CUR_SUB_STAT);
    /*add by lifuxin for Lnas est process re-construct start*/
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }
    /*add by lifuxin for Lnas est process re-construct end*/

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /* ��״̬�Ĵ��� */
    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI):

                enErrCause = LMM_SMS_ERR_CAUSE_USIM_PS_INVALID;
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_ATTACH_NEEDED):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):

                enErrCause = LMM_SMS_ERR_CAUSE_ACCESS_BARRED;
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_ATTEMPTING_TO_ATTACH):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                /* 3402�����ϱ�LMM_SMS_ERR_CAUSE_T3402_RUNNING �����������LMM_SMS_ERR_CAUSE_OTHERS*/
                if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
                {
                    enErrCause = LMM_SMS_ERR_CAUSE_T3402_RUNNING;
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):

                return NAS_LMM_STORE_LOW_PRIO_MSG;

        default:
                /* ��������״̬һ���ϱ�ԭ��ֵLMM_SMS_ERR_CAUSE_OTHERS */
                break;
    }

    NAS_LMM_SndLmmSmsErrInd(enErrCause);
    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_RcvSmsEstReqMsgProc(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;

    /* ��ȡ��ǰ״̬ */
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                      NAS_EMM_CUR_SUB_STAT);

    /* EMM_SS_REG_NORMAL_SERVICE */
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
    {
        /* ������������̬����״̬������ */
        if(NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
        {
            return NAS_LMM_MSG_DISCARD;
        }
        NAS_LMM_SndLmmSmsEstCnf();
        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
        return NAS_LMM_MSG_HANDLED;
    }
    else  /* ����״̬����������������ͬ�Ĵ��� */
    {
        return NAS_EMM_SomeStateRcvSmsMsgCommProc();
    }
}


VOS_UINT32  NAS_EMM_RcvSmsDataReqMsgProc(MsgBlock * pMsg)
{
    VOS_UINT32                          ulCurEmmStat;

    /* ��ȡ��ǰ״̬ */
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                      NAS_EMM_CUR_SUB_STAT);

    /* EMM_SS_REG_NORMAL_SERVICE */
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
    {
        if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
        {
            /*��������NAS͸����Ϣ�����ҷ��͸�RRC*/
            NAS_EMM_SMS_SendMrrcDataReq_SmsData(pMsg);
        }
        else
        {
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_RRC_CONN_NOT_EXIST);
        }
        return NAS_LMM_MSG_HANDLED;
    }
    else  /* ����״̬�����뽨��������ͬ�Ĵ��� */
    {
        return NAS_EMM_SomeStateRcvSmsMsgCommProc();
    }
}





VOS_UINT32  NAS_EMM_PreProcMsgSmsDataReq( MsgBlock * pMsg )
{
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause = LMM_SMS_ERR_CAUSE_BUTT;

    if (VOS_NULL_PTR == pMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PreProcMsgSmsDataReq:  ERR, Null Ptr!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgSmsDataReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* ���ܷ��Ͷ���Ϣ��Ҳ�����ط� */
    if (NAS_EMM_YES == NAS_EMM_IsSmsNotRetransmitConditionSatisfied(&enErrCause))
    {
        NAS_LMM_SndLmmSmsErrInd(enErrCause);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �����ܷ��Ͷ���Ϣ�����һ�����ݵ�ǰ״̬���� */
    return NAS_EMM_RcvSmsDataReqMsgProc(pMsg);

}

VOS_UINT32 NAS_EMM_SndSmsdataFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    (VOS_VOID)pMsg;
    *pulIsDelBuff = VOS_TRUE;
    NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
    NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_NULL);

    return NAS_EMM_SUCC;

}


VOS_UINT32  NAS_EMM_PreProcMsgSmsEstReq(MsgBlock * pMsg )
{
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause = LMM_SMS_ERR_CAUSE_BUTT;

    if (VOS_NULL_PTR == pMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PreProcMsgSmsEstReq:  ERR, Null Ptr!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgSmsEstReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* ���ܷ�������Ҳ�����ط� */
    if (NAS_EMM_YES == NAS_EMM_IsSmsNotRetransmitConditionSatisfied(&enErrCause))
    {
        NAS_LMM_SndLmmSmsErrInd(enErrCause);
        return NAS_LMM_MSG_HANDLED;
    }

    /* ���ݵ�ǰ״̬������Ӧ���� */
    return NAS_EMM_RcvSmsEstReqMsgProc();

}

/*****************************************************************************
 Function Name   : NAS_LMM_SmsSendDataInd
 Description     : ��SMS����ID_LMM_SMS_DATA_IND
 Input           :
 Output          :
 Return          : ������
 History         :
    1.FTY         2011-11-16  Draft Enact
    2.sunbing     2011-12-30  �޸���Ϣ����
*****************************************************************************/
VOS_VOID NAS_LMM_SndLmmSmsDataInd(const VOS_UINT8* aucMsg,VOS_UINT32 ulMsgLen)
{
    LMM_SMS_DATA_IND_STRU                  *pLmmSmsDataInd      = NAS_EMM_NULL_PTR;
    VOS_UINT32                              ulTmpLength         = 0;

    if( 0 == ulMsgLen)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_LMM_SndLmmSmsDataInd: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SndLmmSmsDataInd_ENUM,LNAS_ERROR);
        return ;
    }
    else if(ulMsgLen > NAS_EMM_4BYTES_LEN)
    {
        ulTmpLength = ulMsgLen - NAS_EMM_4BYTES_LEN ;
        pLmmSmsDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_SMS_DATA_IND_STRU) + ulTmpLength);
    }
    else/*�������С��NAS_EMM_4BYTES_LEN������Ŀռ����NAS_EMM_4BYTES_LEN*/
    {
        ulTmpLength = 0;
        pLmmSmsDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_SMS_DATA_IND_STRU));
    }

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pLmmSmsDataInd)
    {
        return ;
    }

    /*����ID_EMM_ESM_DATA_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_LMM_COMP_SMS_MSG_HEADER(pLmmSmsDataInd,
                                (sizeof(LMM_SMS_DATA_IND_STRU)+ ulTmpLength)-NAS_EMM_LEN_VOS_MSG_HEADER);
    /*�����ϢID*/
    pLmmSmsDataInd->ulMsgId = ID_LMM_SMS_DATA_IND;

    /*�����Ϣ����*/
    pLmmSmsDataInd->ulOpId = 0;
    pLmmSmsDataInd->stSmsMsg.ulSmsMsgSize = ulMsgLen;

    /*lint -e669*/
    NAS_LMM_MEM_CPY(pLmmSmsDataInd->stSmsMsg.aucSmsMsg,aucMsg,ulMsgLen);/*lint !e669 !e670*/
    /*lint +e669*/

    /*��SMS����ID_LMM_SMS_DATA_IND��Ϣ*/
    NAS_LMM_SEND_MSG(pLmmSmsDataInd);

}
/*lint +e961*/
/*lint +e960*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

