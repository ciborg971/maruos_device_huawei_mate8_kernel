

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMAPPMSGPROC_C
/*lint +e767*/


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
extern APP_ESM_DT_STRU          g_stEsmDtInfo;



/*****************************************************************************
  3 Function
*****************************************************************************/




VOS_VOID NAS_ESM_AppMsgDistr( VOS_VOID *pRcvMsg )
{
    APP_PS_MSG_HEADER_STRU                *pAppMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppMsgDistr_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pAppMsg->ulMsgId)
    {
        /*����յ�����ID_APP_ESM_PDP_SETUP_REQ��Ϣ*/
        case ID_APP_ESM_PDP_SETUP_REQ:

            /*������Ϣ������*/
            NAS_ESM_AppSdfSetupMsgProc(pRcvMsg);
            break;

        /*����յ�����ID_APP_ESM_PDP_RELEASE_REQ��Ϣ*/
        case ID_APP_ESM_PDP_RELEASE_REQ:

            /*������Ϣ������*/
            NAS_ESM_AppSdfReleaseMsgProc(pRcvMsg);
            break;

        /*����յ�����ID_APP_ESM_PDP_MODIFY_REQ��Ϣ*/
        case ID_APP_ESM_PDP_MODIFY_REQ:

            /*������Ϣ������*/
            NAS_ESM_AppSdfModifyMsgProc(pRcvMsg);
            break;

        /*����յ�����ID_APP_ESM_PDP_MANAGER_RSP��Ϣ*/
        case ID_APP_ESM_PDP_MANAGER_RSP:

            NAS_ESM_AppPdpManageRspMsgProc(pRcvMsg);
            break;

        case ID_APP_ESM_NDISCONN_REQ:

            NAS_ESM_AppNdisconnMsgProc(pRcvMsg);
            break;

        /*����յ�APP����������Ϣ*/
        case ID_APP_ESM_SET_TFT_REQ:
        case ID_APP_ESM_SET_QOS_REQ:
        case ID_APP_ESM_SET_EPS_QOS_REQ:
        case ID_APP_ESM_SET_APN_REQ:
        case ID_APP_ESM_SET_PCO_REQ:
        case ID_APP_ESM_SET_PDN_TYPE_REQ:
        case ID_APP_ESM_SET_BEARER_TYPE_REQ:
        case ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ:
        case ID_APP_ESM_SET_GW_AUTH_REQ:
        case ID_APP_ESM_SET_CGDCONT_REQ:

            /*���ò�������Ԥ������*/
            NAS_ESM_AppParaSetMsgProc(pRcvMsg);
            break;

        /*����յ�APP������ѯ��Ϣ*/
        case ID_APP_ESM_INQ_TFT_REQ:
        case ID_APP_ESM_INQ_QOS_REQ:
        case ID_APP_ESM_INQ_EPS_QOS_REQ:
        case ID_APP_ESM_INQ_APN_REQ:
        case ID_APP_ESM_INQ_PCO_REQ:
        case ID_APP_ESM_INQ_PDN_TYPE_REQ:
        case ID_APP_ESM_INQ_BEARER_TYPE_REQ:
        case ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_TFT_REQ:
        case ID_APP_ESM_INQ_GW_AUTH_REQ:
            /*���ò�����ѯԤ������*/
            NAS_ESM_AppParaQueryMsgProc(pRcvMsg);
            break;

        /*����յ�͸����������*/
        case OM_PS_TRANSPARENT_CMD_REQ:
            NAS_ESM_TransparentMsgProc(pRcvMsg);
            break;

        case ID_APP_ESM_IPV6_INFO_NOTIFY:

            /*���ò������ú���*/
            NAS_ESM_AppIpv6InfoNotifyMsgProc(pRcvMsg);
            break;
        case ID_APP_ESM_PROCEDURE_ABORT_NOTIFY:
            /* ����������ֹ������ */
            NAS_ESM_AppProcAbortNotifyProc(pRcvMsg);
            break;
        default:

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppMsgDistr:Warning:APP->SM,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_SendPdnConReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType, VOS_VOID *pRcvMsg)
{
    NAS_ESM_INFO_LOG2("NAS_ESM_SendPdnConReq entered:", enBearerType, NAS_ESM_GetEmmStatus());
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_SendPdnConReq_ENUM, LNAS_ENTRY, enBearerType, NAS_ESM_GetEmmStatus());

    switch(NAS_ESM_GetEmmStatus())
    {
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHED:
            if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(enBearerType))
            {
                NAS_ESM_DefltAttMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_DedictdAttMsgAppSdfSetupReq(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHING:
            if (NAS_ESM_BEARER_TYPE_EMERGENCY == enBearerType)
            {
                NAS_ESM_DefltDetMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppSdfSetupReqRefusedProc(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_DETACHED:
            if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(enBearerType))
            {
                NAS_ESM_DefltDetMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppSdfSetupReqRefusedProc(pRcvMsg);
            }
            break;
        default:
            NAS_ESM_INFO_LOG("NAS_ESM_SendPdnConReq: invalid status");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SendPdnConReq_ENUM, ESM_STATUS_ERROR);
    }
}


VOS_VOID NAS_ESM_SendNdisConnReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType,VOS_VOID *pRcvMsg)
{
    NAS_ESM_INFO_LOG1("NAS_ESM_SendNdisConnReq entered:",NAS_ESM_GetEmmStatus());
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SendNdisConnReq_ENUM, LNAS_ENTRY, NAS_ESM_GetEmmStatus());

    switch(NAS_ESM_GetEmmStatus())
    {
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHED:
            NAS_ESM_DefltAttMsgAppNdisConnReq(pRcvMsg);

            break;
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHING:
            if (NAS_ESM_BEARER_TYPE_EMERGENCY == enBearerType)
            {
                NAS_ESM_DefltDetMsgAppNidsConnReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppNdisConnReqRefusedProc(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_DETACHED:
            NAS_ESM_DefltDetMsgAppNidsConnReq(pRcvMsg);

            break;
        default:
            NAS_ESM_INFO_LOG("NAS_ESM_SendNdisConnReq: invalid status");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SendNdisConnReq_ENUM, ESM_STATUS_ERROR);
    }
}



VOS_VOID NAS_ESM_AppSdfSetupMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    APP_ESM_PDP_SETUP_REQ_STRU         *pAppMsg;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT32                          ulVerifyRslt        = APP_SUCCESS;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    pAppMsg = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG2("NAS_ESM_AppSdfSetupMsgProc is entered.", pAppMsg->ulCid, pAppMsg->enSetupType);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_AppSdfSetupMsgProc_ENUM, LNAS_ENTRY, pAppMsg->ulCid, pAppMsg->enSetupType);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv=pAppMsg->ulCid;

    /*����Ϣ��ȡ�����ι��̵�ulOPID����*/
    ulOpId=pAppMsg->ulOpId;

    /*����Ϣ��ȡ��MID����*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return ;
    }
    /*�ж�PPP���ų����������Ϸ��� */
    ulVerifyRslt = NAS_ESM_VerifyAppPppDialSceneAndParam(pRcvMsg);
    if(ulVerifyRslt != APP_SUCCESS)
    {
        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = ulVerifyRslt;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*���ulCidRecv�����Ƿ�*/
    if (ulCidRecv >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, ESM_CID_ERROR);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        /*���ú�������APP��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*��ѯ��̬���Ƿ��й�����EpsbId������У���ظ������ɹ�*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc is entered.111");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 3);

        /*���س��ؽ����ɹ���Ϣ*/
        stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId =ulEpsbId;
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨���ɹ�*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* ��������Ѿ����������ڽ����Ľ���PDN���ӣ������ٷ������PDN��������*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);
    if ((APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType) &&
        (PS_TRUE == NAS_ESM_HasEmergencyPdn()))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: only one emergency PDN allowed");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 4);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* ���EMM�����ڽ���ע��״̬�����ڽ��н���ע�ᣬ�����ٷ����κ�����PDN��������*/
    if (PS_TRUE == NAS_ESM_IsEmmEmcAttachedOrAttaching())
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: any PDN not allowed when emergency attach");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 5);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* ȱʡ��������APN��Back-off�㷨�ж��������������ֱ�Ӹ�APP��ʧ�� */
    if((APP_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        &&(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_SET(&stJudgmentPara, 0, sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
        NAS_ESM_MEM_CPY(&stJudgmentPara,
                          &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
        {
            /* ��װ�ṹ��pstEsmAppCnfMsg����APP��ʧ�� */
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode    = APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED;
            NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
            return;
        }
    }

    /*�ڶ�̬���У���ȡ���̱�ʶ*/
    if(NAS_ESM_FAILURE==NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        /*��ӡ�쳣��Ϣ��״̬�������߸�CID�Ѿ��ڱ���*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /*����CID������Ҷ�Ӧ��������*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);

    ulRslt = NAS_ESM_AppNdisconnMsgCheckApnValid(pstSdfPara->bitOpPdnType,
                                                pstSdfPara->enPdnType,
                                                pstSdfPara->bitOpApn,
                                                &(pstSdfPara->stApnInfo),
                                                &stEsmAppCnfMsg);
    if(NAS_ESM_FAILURE == ulRslt)
    {
        /*��ǰʹ�õ�APN��50����51����66�ľܾ��б���*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Rej Cause is 50/51/66!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, 7);

        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*����APP��Ϣ��¼�ı�ʶλ*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

    /*���汾�ι��̵�ulOpId����*/
    NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

    /*���汾�ι��̵�MID����*/
    NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

    /*�����յ���APP��Ϣ*/
    NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_SETUP_REQ);

    /*���ó���״̬�����*/
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType = (VOS_UINT8)pstSdfPara->enBearerCntxtType;

    /*����SDF���Ժ͵�ǰע��״̬������Ӧ�Ĵ�����*/
    NAS_ESM_SendPdnConReq(pstStateAddr->enBearerCntxtType, pRcvMsg);
}



VOS_VOID NAS_ESM_AppSdfReleaseMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_REQ_STRU    *pAppMsg             = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT32                          ulStateTblPdnDiscNum  = 0;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSdfReleaseMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfReleaseMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg=(APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg;

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pAppMsg->ulCid;

    /*����Ϣ��ȡ�����ι��̵�ulOPID����*/
    ulOpId=pAppMsg->ulOpId;

    /*����Ϣ��ȡ��MID����*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId = ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ��ͨ��ɾ��ʧ��*/
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return ;
    }
    /*����Ƿ�ulCidRecv�Ϸ�*/
    if(ulCidRecv < NAS_ESM_MAX_CID_NUM)
    {
        /*���CID�����Ƿ��뱾�ض�Ӧ��EPS����ulEpsbID���������û����ظ��ͷųɹ�*/
        if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
        {
            /* lihong00150010 ims begin */
            /* �ô�CID���Ҷ�̬��������ҳɹ������ͷŴ˶�̬���¼ */
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
            {
                /* ����APP����������ظ�ʧ����Ϣ */
                NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_ERROR));

                /*�ͷ�״̬����Դ*/
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }

            /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ������APP�����ͷ����*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
            /* lihong00150010 ims end */
            return;
        }

        /*��ȡ������Ϣ��ַ*/
        pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /* ��ѯ��̬��������ִ�е�PDNȥ������ */
        ulStateTblPdnDiscNum = NAS_ESM_QueryPdnDisconnNumInStateTbl();

        /*���ȥ����̬��������ִ�е�PDNȥ�������������һ��PDN���ӣ�UE�ܾ�����PDN ȥ��������*/
        if((NAS_ESM_MIN_PDN_NUM >= (NAS_ESM_GetCurPdnNum()- ulStateTblPdnDiscNum))
            && (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstBearerCntxtInfo->enBearerCntxtType))
           )
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:WARNING:The Last PDN CONNECT can not be disconnect!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, 1);

            /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ������APP�����ͷ�ʧ��
                    ԭ��ֵΪ:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
            stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulEpsbId = ulEpsbId ;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

            return ;
        }

        /*��鶯̬�����Ƿ�������������¼����ר�г��ص�ID��ͬ*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfReleaseMsgProc:Bearer is dealing!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfReleaseMsgProc_ENUM, 2);
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
            return;
        }

        /*�ڶ�̬���У���ȡ���̱�ʶIndex*/
        if(NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
        {
            /*��ӡ�쳣��Ϣ, ״̬�������߸�CID�Ѿ��ڱ���*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is dealing or resource is insufficient!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

            /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ������APP�����ͷ�ʧ��
                    ԭ��ֵΪ:APP_ERR_PS_INSUFFICIENT_RESOURCES*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

            return;
        }


        /*����APP��Ϣ��¼�ı�ʶλ*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

        /*���汾�ι��̵�ulOpId����*/
        NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

        /*���汾�ι��̵�MID����*/
        NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

        /*�����յ���APP��Ϣ*/
        NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_RELEASE_REQ);

        /*���ó���״̬����𡢹���������Ϣ*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->ulEpsbId           = ulEpsbId;
        pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(ulEpsbId);
        pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(ulEpsbId);
        pstStateAddr->ulLinkedEpsbId     = pstBearerCntxtInfo->ulLinkedEpsbId;

        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstStateAddr->enBearerCntxtType))
        {
            NAS_ESM_DefltAttMsgAppSdfRelReq(pRcvMsg);
        }
        else
        {
            NAS_ESM_DedictdAttMsgAppSdfRelReq(pRcvMsg);
        }

    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, ESM_CID_ERROR);

        /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ������APP�����ͷ�ʧ��
                            ԭ��ֵΪ:APP_ERR_PS_CALL_CID_INVALID*/
        stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSdfReleaseMsgProc
 Description     : ����APP��������޸���Ϣ
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2008-9-11  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_AppSdfModifyMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_REQ_STRU        *pAppMsg             = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfModifyMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg=(APP_ESM_PDP_MODIFY_REQ_STRU*)pRcvMsg;

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pAppMsg->ulCid;

    /*����Ϣ��ȡ�����ι��̵�ulOPID����*/
    ulOpId=pAppMsg->ulOpId;

    /*����Ϣ��ȡ��MID����*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId = ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM ��APP����ID_APP_ESM_PDP_MODIFY_CNF��Ϣ��ͨ���޸�ʧ��*/
        NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
        return ;
    }

    /*����Ƿ�ulCidRecv�Ϸ�*/
    if(ulCidRecv < NAS_ESM_MAX_CID_NUM)
    {
        /*���CID�����Ƿ��뱾�ض�Ӧ��EPS����ulEpsbID���������û����ظ��޸�ʧ��*/
        if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
        {

            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_NOT_MATCH_BEARER;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*����ǽ������أ���֧���޸Ĳ���*/
        if (APP_ESM_BEARER_TYPE_EMERGENCY == NAS_ESM_GetBearCntxtType(ulEpsbId))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc: modification for emergency not allowed");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfModifyMsgProc_ENUM, 1);

            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*�жϳ������ͣ������ȱʡ������ظ�����*/
        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ulEpsbId)))
        {
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_BEARER_TYPE_NOT_DEDICATED;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*��鶯̬�����Ƿ�������������¼����ר�г��ص�ID��ͬ*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc:Bearer is dealing!");
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
            return;
        }

        /*�ڶ�̬���У���ȡ���̱�ʶIndex*/
        if(NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
        {/*��ȡʧ�ܣ�״̬�������߸�CID�Ѿ��ڱ���*/
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is dealing or resource is insufficient!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

            /*ESM ��APP����APP_ESM_BEARER_RELEASE_CNF��Ϣ������APP�����ͷ�ʧ��
                    ԭ��ֵΪ:APP_ERR_PS_CALL_CID_INVALID*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*��ȡ������Ϣ��ַ*/
        pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*����APP��Ϣ��¼�ı�ʶλ*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

        /*���汾�ι��̵�ulOpId����*/
        NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

        /*���汾�ι��̵�MID����*/
        NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

        /*�����յ���APP��Ϣ*/
        NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_MODIFY_REQ);

        /*���ó���״̬����𡢹���������Ϣ*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->ulEpsbId           = ulEpsbId;
        pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(ulEpsbId);
        pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(ulEpsbId);
        pstStateAddr->ulLinkedEpsbId     = pstBearerCntxtInfo->ulLinkedEpsbId;

        NAS_ESM_DedictdAttMsgAppSdfModifyReq(pRcvMsg);

    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfModifyMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, ESM_CID_ERROR);

        /*ESM ��APP����APP_ESM_BEARER_MODIFY_CNF��Ϣ������APP�����ͷ�ʧ��
                            ԭ��ֵΪ:APP_ERR_PS_CALL_CID_INVALID*/
        stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgProc
 Description     : ����App�ظ��ĳ��ؼ��������޸ĵ���Ӧ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppPdpManageRspMsgProc( VOS_VOID *pRcvMsg )
{
    APP_ESM_PDP_MANAGER_RSP_STRU     *pAppMsg             = VOS_NULL_PTR;
    VOS_UINT32                        ulStateTblIndex     = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppPdpManageRspMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppPdpManageRspMsgProc_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPdpManageRspMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppPdpManageRspMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    pAppMsg=(APP_ESM_PDP_MANAGER_RSP_STRU*)pRcvMsg;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(pAppMsg->ulCid,
                                                           &ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPdpManageRspMsgProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppPdpManageRspMsgProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* �����û�����Ӧ���ͣ���ȡ��Ӧ�Ĳ��� */
    if (APP_ESM_BEARER_ACT_ACCEPT == pAppMsg->ulSetupRslt)
    {
        NAS_ESM_AppPdpManageRspMsgAcceptProc(ulStateTblIndex);
    }
    else
    {
        /* App�ܾ����ؼ��������޸ĵĴ��� */
        NAS_ESM_AppPdpManageRspMsgRefuseProc(ulStateTblIndex);
    }

}


VOS_VOID NAS_ESM_GetAppNdisconnInfo(VOS_VOID *pRcvMsg)
{
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara  = VOS_NULL_PTR;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(pAppMsg->ulCid);

    if (APP_ESM_PDP_FOR_EMC == pAppMsg->enEmergencyInd)
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_DEFAULT;
    }


    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPcscfDiscovery)
    {
        pstSdfPara->bitOpPcscfDiscovery = NAS_ESM_OP_TRUE;
        pstSdfPara->enPcscfDiscovery = pAppMsg->enPcscfDiscovery;
    }
    else
    {
        pstSdfPara->bitOpPcscfDiscovery = NAS_ESM_OP_FALSE;
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpImCnSignalFlg)
    {
        pstSdfPara->bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
        pstSdfPara->enImsCnSignalFlag = pAppMsg->enImCnSignalFlg;
    }
    else
    {
        pstSdfPara->bitOpImsCnSignalFlag = NAS_ESM_OP_FALSE;
    }
}


VOS_UINT32  NAS_ESM_SaveAppNdisconnInfo
(
    APP_ESM_NDISCONN_REQ_STRU           *pAppMsg ,
    NAS_ESM_APP_CNF_MSG_STRU            *pstEsmAppCnfMsg
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pAppMsg->ulCid,
                                                    APP_ESM_PARA_SETTING,
                                                    pAppMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: APN ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_APN_ERROR, ulRslt);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpGwAuth)
    {
        ulRslt = NAS_ESM_AppNdisConnSetGwAuthInfo(pAppMsg);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: GwAuth ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, LNAS_ERROR, ulRslt);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pAppMsg->ulCid,
                                                        APP_ESM_PARA_SETTING,
                                                        pAppMsg->enPdnType,
                                                        pAppMsg->bitOpIpv4AddrAlloc,
                                                        pAppMsg->enIpv4AddrAlloc);

        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: Pdn ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_PDN_TYPE_ERROR, ulRslt);
            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}


VOS_UINT32  NAS_ESM_AppNdisconnMsgCheckApnValid
(
    VOS_UINT32                           ulBitOpPdnType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU         *pstApnInfo,
    NAS_ESM_APP_CNF_MSG_STRU            *pstEsmAppCnfMsg
)
{
    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        if (NAS_ESM_OP_FALSE == ulBitOpPdnType)
        {
             /*��ӡ�쳣��Ϣ */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgCheckApnValid:Warning: PND INFO is not exist!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_PDN_TYPE_ERROR);
            return NAS_ESM_SUCCESS;
        }

        /* �����ǰʹ�õ�APN��#50�ܾ��б��У�ֱ�ӻظ�ʧ�� */
        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(enPdnType,ulBitOpApnInfo,pstApnInfo))
        {
            /*��ӡ�쳣��Ϣ����APN��#50�ܾ������������ٷ��� */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #50!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 50);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED);

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }

        /* �����ǰʹ�õ�APN��#51�ܾ��б��У�ֱ�ӻظ�ʧ�� */
        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(enPdnType,ulBitOpApnInfo,pstApnInfo))
        {
            /*��ӡ�쳣��Ϣ����APN��#50�ܾ������������ٷ��� */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #51!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 51);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED);

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }

        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(ulBitOpApnInfo,pstApnInfo))
        {
            /*��ӡ�쳣��Ϣ����APN��#50�ܾ������������ٷ��� */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #66!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 66);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN);

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}

/* lihong00150010 ims begin */

VOS_VOID  NAS_ESM_AppNdisconnMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG1("NAS_ESM_AppNdisconnMsgProc is entered.", pAppMsg->ulCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, 1, pAppMsg->ulCid);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv=pAppMsg->ulCid;
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);

    /*����Ϣ��ȡ�����ι��̵�ulOPID����*/
    ulOpId=pAppMsg->ulOpId;

    /*����Ϣ��ȡ��MID����*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    /* ���ó������� */
    /*
    if ((APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType)
        && (APP_ESM_BEARER_TYPE_DEFAULT != pstSdfPara->enBearerCntxtType))
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_DEFAULT;
    }
    */
    NAS_ESM_GetAppNdisconnInfo(pRcvMsg);

    if(NAS_ESM_SUCCESS != NAS_ESM_SaveAppNdisConnInfo(pRcvMsg))
    {
        return;
    }

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return ;
    }

    /*��ѯ��̬���Ƿ��й�����EpsbId������У���ظ������ɹ�*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AppNdisconnMsgProc is entered.111");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 1);

        /*���س��ؽ����ɹ���Ϣ*/
        stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId =ulEpsbId;
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

        /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨���ɹ� */
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return;
    }

    /* ��������Ѿ����������ڽ����Ľ���PDN���ӣ������ٷ������PDN��������*/
    if ((APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType) &&
        (PS_TRUE == NAS_ESM_HasEmergencyPdn()))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: only one emergency PDN allowed");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 2);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* ���EMM�����ڽ���ע��״̬�����ڽ��н���ע�ᣬ�����ٷ����κ�����PDN��������*/
    if (PS_TRUE == NAS_ESM_IsEmmEmcAttachedOrAttaching())
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: any PDN not allowed when emergency attach");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 3);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED;

        /*ESM ��APP����ID_APP_ESM_PDP_SETUP_CNF��Ϣ��ͨ�潨��ʧ��*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* ȱʡ��������APN��Back-off�㷨�ж��Ƿ�������PDN�������� */
    if((APP_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        &&(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_SET(&stJudgmentPara, 0, sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
        NAS_ESM_MEM_CPY(&stJudgmentPara,
                          &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
        {
            /*��װ�ṹ��pstEsmAppCnfMsg����APP��ʧ��*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode    = APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED;
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            return;
        }
    }

    /*�ڶ�̬���У���ȡ���̱�ʶ*/
    if(NAS_ESM_FAILURE==NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        /*��ӡ�쳣��Ϣ��״̬�������߸�CID�Ѿ��ڱ���*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

        /*��װ�ṹ��pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

        /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/

        return;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_AppNdisconnMsgCheckApnValid(pAppMsg->bitOpPdnType,
                                                                pAppMsg->enPdnType,
                                                                pAppMsg->bitOpApn,
                                                                &(pAppMsg->stApnInfo),
                                                                &stEsmAppCnfMsg))
    {
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*����APP��Ϣ��¼�ı�ʶλ*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

    /*���汾�ι��̵�ulOpId����*/
    NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

    /*���汾�ι��̵�MID����*/
    NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

    /*�����յ���APP��Ϣ*/
    NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_NDISCONN_REQ);

    /*���ó���״̬�����*/
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType = (VOS_UINT8)pstSdfPara->enBearerCntxtType;

    /*��¼pdn��������*/
    if(APP_ESM_PDN_REQUEST_TYPE_HANDOVER == pAppMsg->enPdnReqestType)
    {
        pstStateAddr->enPdnReqType = NAS_ESM_PDN_REQ_TYPE_HANDOVER;
    }
    else
    {
        pstStateAddr->enPdnReqType = NAS_ESM_PDN_REQ_TYPE_INITIAL;
    }

    /*����SDF���Ժ͵�ǰע��״̬������Ӧ�Ĵ�����*/
    NAS_ESM_SendNdisConnReq(pstStateAddr->enBearerCntxtType,pRcvMsg);
}
/* lihong00150010 ims end */

VOS_VOID NAS_ESM_DefltDetMsgAppNidsConnReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pstAppEsmSetupReqMsg= VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;


    pstAppEsmSetupReqMsg = (APP_ESM_NDISCONN_REQ_STRU *)pRcvMsg;


    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltDetMsgAppNidsConnReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv= pstAppEsmSetupReqMsg->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetMsgAppNidsConnReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*��װPDN_Connect_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_LOG1("NAS_ESM_DefltDetMsgAppNidsConnReq:WARNING:EncodePdnConReqMsg fail!,ERROR =", APP_ERR_UNSPECIFIED_ERROR);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, ESM_EncodePdnConReqMsg_fail, APP_ERR_UNSPECIFIED_ERROR);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*�����Ƿ�Ϊ����PDN��������*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();

    /*���ú�����SM��MM������ϢID_EMM_ESM_EST_REQ*/
    NAS_ESM_SndEsmEmmEstReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                               pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*״̬ת��*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

}



VOS_VOID NAS_ESM_DefltDetMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU         *pstAppEsmSetupReqMsg= VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;


    pstAppEsmSetupReqMsg = (APP_ESM_PDP_SETUP_REQ_STRU *)pRcvMsg;


    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltDetMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv= pstAppEsmSetupReqMsg->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*��װPDN_Connect_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetBInactPInactMsgAppBearSetupReq:WARNING:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, ESM_EncodePdnConReqMsg_fail);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*�����Ƿ�Ϊ����PDN��������*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();

    /*���ú�����SM��MM������ϢID_EMM_ESM_EST_REQ*/
    NAS_ESM_SndEsmEmmEstReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                               pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*״̬ת��*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

}


VOS_VOID  NAS_ESM_DefltAttMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    APP_ESM_PDP_SETUP_REQ_STRU         *pstAppEsmSetupReqMsg = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/

    ulCidRecv=((APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg)->ulCid;
    pstAppEsmSetupReqMsg = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;


    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    if (APP_ESM_PDP_SETUP_TYPE_PPP == pstAppEsmSetupReqMsg->enSetupType)
    {

        /*��װPDN_Connect_Req��Ϣ*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg_PPP(pstAppEsmSetupReqMsg,\
                                                          stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DefltDetBInactPInactMsgAppBearSetupReq:WARNING:NAS_ESM_EncodePdnConReqMsg_PPP fail!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 2);

            /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }
    }
    else
    {
        /*��װPDN_Connect_Req��Ϣ*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DefltAttBInactPInactMsgAppBearSetupReq:WARNING:EncodePdnConReqMsg fail!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, ESM_EncodePdnConReqMsg_fail);

            /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }
    }
    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*�����Ƿ�Ϊ����PDN��������*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����SM->EMM������Ϣ:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*����T3482��ʱ��*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

    /*״̬ת��*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}
VOS_VOID  NAS_ESM_DefltAttMsgAppNdisConnReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/

    ulCidRecv=((APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg)->ulCid;


    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*��װPDN_Connect_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq:WARNING:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, ESM_Tbl_index_Query_Fail);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;


    /*�����Ƿ�Ϊ����PDN��������*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����SM->EMM������Ϣ:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*����T3482��ʱ��*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

    /*״̬ת��*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}
VOS_VOID  NAS_ESM_DefltAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv=((APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg)->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;

    /*��װPDN_Disconnect_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnDisconReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq:WARNING:EncodePdnDisconReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, ESM_EncodePdnConReqMsg_fail);

        /*��APP�ظ�APP_ESM_BEARER_RELEASE_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����SM��MM������ϢID_EMM_ESM_DATA_REQ��PDN DISCONNECT REQ��*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_DISCONNECT_REQ);

    /*����T3492��ʱ��*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3492);

    /*״̬ת��*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}


VOS_VOID  NAS_ESM_AppNdisConnReqRefusedProc(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU           *pRcvMsgTemp         = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_AppNdisConnReqRefusedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, LNAS_ENTRY);

    /*ָ�������Ϣ*/
    pRcvMsgTemp = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisConnReqRefusedProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    NAS_ESM_LOG1("NAS_ESM_AppNdisConnReqRefusedProc:ERROR =", APP_ERR_SM_DETACHED);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, 1, APP_ERR_SM_DETACHED);

    /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
    NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_SM_DETACHED);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

}



VOS_VOID  NAS_ESM_AppSdfSetupReqRefusedProc(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU      *pRcvMsgTemp         = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_AppSdfSetupReqRefusedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupReqRefusedProc_ENUM, LNAS_ENTRY);

    /*ָ�������Ϣ*/
    pRcvMsgTemp = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupReqRefusedProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupReqRefusedProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
    NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_DETACHED);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

}


VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfSetupReq(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulLinkdCid          = NAS_ESM_NULL;
    VOS_UINT32                          ulLinkeEpsBid       = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU         *pRcvMsgTemp         = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*ָ�������Ϣ*/
    pRcvMsgTemp = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����CID�ҵ������CID,���LinkdCid�Ϸ���*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);
    if( (NAS_ESM_OP_FALSE == pstSdfPara->bitOpLinkdCId)
        ||(pstSdfPara->ulLinkdCId >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:LinkdCid Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, ESM_CID_ERROR);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_CID_INVALID);


        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /*����LinkdCid�ҵ����ض�Ӧ��EPS����*/
    ulLinkdCid = pstSdfPara->ulLinkdCId;
    if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulLinkdCid,&ulLinkeEpsBid))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:EpsbId Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_BEARER_INACTIVE);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;

    }

    /*����������ulLinkeEpsBid��״̬:�Ƿ񱻼���*/
    pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulLinkeEpsBid);

    /*������������ǽ������أ��򷵻�APPʧ��*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstBearerCntxtInfo->enBearerCntxtType)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:Linked EPS is emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 1);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }
    /*����������ش��ڼ���̬*/
    if((NAS_ESM_BEARER_STATE_ACTIVE==pstBearerCntxtInfo->enBearerCntxtState)
        &&(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstBearerCntxtInfo->enBearerCntxtType)))
    {
        /*����LinkeEpsBid*/
        NAS_ESM_SaveLinkedEpbsId(ulStateTblIndex, ulLinkeEpsBid);

        /*����PTI�������������Ϣ��*/
        NAS_ESM_AssignPTI(&ulPti);
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;


        /*���NAS_ESM_ENCODE_INFO_STRU*/
        NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
        stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
        stEncodeInfo.ulCid              = pstStateAddr->ulCid;
        stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
        stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
        stEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulLinkedEpsbId;

        /*��װBearer_Res_Alloc_Req��Ϣ*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResAllocReqMsg(stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:EncodeBearerResAllocReqMsg fail!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 2);

            /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }

        /*��¼�տ���Ϣ����*/
        pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
        pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
                = NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ;
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú�����ESM��EMM������Ϣ:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /* ��¼�տ���Ϣ */
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_BEARER_RESOUCE_ALLOC_REQ);

        /*����T3480��ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3480);

        /*ת��״̬*/
        NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);


    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq: link Eps beare inactive or dedicated bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 3);

        /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_BEARER_INACTIVE);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }


}

/*****************************************************************************
 Function Name   : NAS_ESM_IsQosChanged
 Description     : �жϳ���QOS�Ƿ����ı�
 Input           : pstResModEncodeInfo
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-9-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEpsQosChanged
(
    const NAS_ESM_RES_MOD_ENCODE_INFO_STRU   *pstResModEncodeInfo
)
{
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo;
    VOS_UINT8                           aucQos1[NAS_ESM_MAX_EPS_QOS_BYTE] = { NAS_ESM_NULL };
    VOS_UINT8                           aucQos2[NAS_ESM_MAX_EPS_QOS_BYTE] = { NAS_ESM_NULL };
    VOS_UINT32                          ulQosLen1           = NAS_ESM_NULL;
    VOS_UINT32                          ulQosLen2           = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    PS_MEM_SET(&stEpsQoSInfo, 0, sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    /* ��ȡ�޸ĺ�ĳ���QOS */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEpsQosAfterMod(*pstResModEncodeInfo,&stEpsQoSInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:NAS_ESM_GetEpsQosAfterMod failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 1);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /* ���޸ĺ�ĳ���QOS���б��� */
    if (NAS_ESM_SUCCESS != NAS_ESM_EncodeEpsQos(&stEpsQoSInfo, aucQos1, &ulQosLen1, NAS_MSG_FORMAT_TLV))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:Encode modified bearer qos failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 2);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /*����EpsIdȡ��������Ϣ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstResModEncodeInfo->ulEpsbId);

    /* �Ե�ǰ���ص�QOS���б��� */
    if (NAS_ESM_SUCCESS != NAS_ESM_EncodeEpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, aucQos2, &ulQosLen2, NAS_MSG_FORMAT_TLV))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:Encode current bearer qos failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 3);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /* �Ƚ��޸ĺ�ĳ���QOS�������뵱ǰ����QOS�ı����� */
    if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(aucQos1, aucQos2, NAS_ESM_MAX_EPS_QOS_BYTE))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:NAS_ESM_MEM_CMP failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 4);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    return NAS_ESM_EPS_QOS_CHANGE_TYPE_NO_CHANGE;
}
VOS_VOID    NAS_ESM_GetUeSetupPacketfilters
(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulPfNum,
    NAS_ESM_CONTEXT_TFT_STRU           *pstSdfPfArray
)
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntInfo       = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTmpTftInfo       = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    pstSdfCntInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

    *pulPfNum = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfCntInfo->ulSdfPfNum; ulCnt++)
    {
        pstTmpTftInfo = &pstSdfCntInfo->astSdfPfInfo[ulCnt];

        if (NAS_ESM_NULL != pstTmpTftInfo->ucPacketFilterId)
        {
            NAS_ESM_MEM_CPY(&pstSdfPfArray[*pulPfNum],
                             pstTmpTftInfo,
                             sizeof(NAS_ESM_CONTEXT_TFT_STRU));
            (*pulPfNum)++;
        }
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_GetBearerResourceModifyType
 Description     : ��ȡ������Դ�޸�����
 Input           : ulCid
 Output          : None
 Return          : NAS_ESM_SDF_OP_TYPE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-8-28  Draft Enact

*****************************************************************************/
NAS_ESM_SDF_OP_TYPE_ENUM_UINT8  NAS_ESM_GetBearerResourceModifyType
(
    const NAS_ESM_RES_MOD_ENCODE_INFO_STRU   *pstResModEncodeInfo
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_SUCCESS;
    VOS_UINT32                          ulPfNum             = NAS_ESM_NULL;
    NAS_ESM_SDF_OP_TYPE_ENUM_UINT8      enSdfOpType         = NAS_ESM_SDF_OP_TYPE_BUTT;
    VOS_UINT32                          ulPfArrayLen        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntInfo       = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstSdfPfArray       = VOS_NULL_PTR;

    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQueryNwPfIdSucc(pstResModEncodeInfo))
    {
        return NAS_ESM_SDF_OP_TYPE_ADD_PF;
    }

    ulPfArrayLen = sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstSdfPfArray = (VOS_VOID*)NAS_ESM_MEM_ALLOC(ulPfArrayLen);

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstSdfPfArray)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_GetBearerResourceModifyType:Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_GetBearerResourceModifyType_ENUM, LNAS_NULL_PTR);
        return NAS_ESM_SDF_OP_TYPE_BUTT;
    }

    NAS_ESM_GetUeSetupPacketfilters(pstResModEncodeInfo->ulCid,
                                   &ulPfNum,
                                    pstSdfPfArray);

    /* ��ȡSDF�ľ�̬��Ϣ */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstResModEncodeInfo->ulCid);

    /* �ж�PF��Ϣ�Ƿ����ı� */
    ulRslt = NAS_ESM_TftMatch(pstSdfPara->astCntxtTftInfo,
                              pstSdfPara->ulPfNum,
                              pstSdfPfArray,
                              ulPfNum);

    /* ��ȡSDF�Ķ�̬��Ϣ */
    pstSdfCntInfo = NAS_ESM_GetSdfCntxtInfo(pstResModEncodeInfo->ulCid);

    /* PFδ�����ı� */
    if (NAS_ESM_SUCCESS == ulRslt)
    {
        /* ����GBR���򷵻��޸�����Ϊֻ�޸�QOS�����߷����޸�����Ϊ���޸� */
        if ((PS_TRUE == NAS_ESM_IsGbrBearer(pstSdfCntInfo->stSdfQosInfo.stQosInfo.ucQCI))
            && (NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED == NAS_ESM_IsEpsQosChanged(pstResModEncodeInfo)))
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_QOS;
        }
        else
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_NO_CHANGE;
        }
    }
    /* PF�����ı� */
    else
    {
        /* ����GBR���򷵻��޸�����Ϊ���޸�QOS���޸�TFT�����߷����޸�����Ϊ
           ֻ�޸�TFT */
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstSdfCntInfo->stSdfQosInfo.stQosInfo.ucQCI))
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_QOS_AND_PF;
        }
        else
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_PF;
        }
    }

    /* �ͷ��ڴ�ռ� */
    NAS_ESM_MEM_FREE(pstSdfPfArray);

    return enSdfOpType;
}
VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfModifyReq
(
    const APP_ESM_PDP_MODIFY_REQ_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_SDF_OP_TYPE_ENUM_UINT8      enSdfOpType         = NAS_ESM_SDF_OP_TYPE_BUTT;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv = pRcvMsg->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stResModEncodeInfo, 0, sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU));
    stResModEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stResModEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stResModEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stResModEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;

    stResModEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulEpsbId;

    /* ��ȡSDF�ľ�̬��Ϣ */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    if ((NAS_ESM_NULL == pstSdfPara->ulPfNum) || (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING:No tft information or no qos information!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 1);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* ��ȡ������Դ�޸����� */
    enSdfOpType = NAS_ESM_GetBearerResourceModifyType(&stResModEncodeInfo);

    NAS_ESM_LOG1("NAS_ESM_DedictdAttMsgAppSdfModifyReq modify type:", enSdfOpType);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 2, enSdfOpType);

    /* �����������Ϊ�޸��쳣����ֱ�Ӹ�APP�ظ��޸�ʧ�� */
    if ((NAS_ESM_SDF_OP_TYPE_BUTT == enSdfOpType)
     || (NAS_ESM_SDF_OP_TYPE_ADD_PF == enSdfOpType))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:Add packetfilter is not support!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 3);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_INSUFFICIENT_RESOURCES);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* �����������Ϊ���޸ģ���ֱ�Ӹ�APP�ظ��޸ĳɹ� */
    if (NAS_ESM_SDF_OP_TYPE_NO_CHANGE == enSdfOpType)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:no information changes!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 4);

        NAS_ESM_SndEsmAppSdfModCnfSuccMsg(ulStateTblIndex, APP_ESM_BEARER_MODIFY_TFT);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    stResModEncodeInfo.enSdfOpType = enSdfOpType;

    /*��װBearer_Res_Mod_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsg(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, EncodeBearerResModReqMsg_fail);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;

    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����ESM��EMM������Ϣ:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /*����T3481��ʱ��*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3481);

    /*״̬ת��*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}
VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv=((APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg)->ulCid;

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stResModEncodeInfo, 0, sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU));
    stResModEncodeInfo.bitOpESMCau        = NAS_ESM_OP_TRUE;
    stResModEncodeInfo.ucESMCau           = NAS_ESM_CAUSE_REGULAR_DEACTIVATION;
    stResModEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stResModEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stResModEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stResModEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulEpsbId;
    stResModEncodeInfo.enSdfOpType        = NAS_ESM_SDF_OP_TYPE_DELETE_SDF;

    /*��װBearer_Res_Mod_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsg(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq:WARNING:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, EncodeBearerResModReqMsg_fail);

        /*��APP�ظ�APP_ESM_BEARER_RELEASE_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;


    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����ESM��EMM������Ϣ:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /*����T3481��ʱ��*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3481);

    /*״̬ת��*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}


/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg)
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_CNF_STRU         *pSmAppSetupCnf      = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    if(VOS_NULL_PTR == pstEsmAppCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pSmAppSetupCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_SETUP_CNF_STRU));
    /*lint +e433 +e826*/

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppSetupCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppSetupCnf), 0, \
                NAS_ESM_GET_MSG_LENGTH(pSmAppSetupCnf));

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*���ulRabId����*/
        pSmAppSetupCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppSetupCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*���ulCid����*/
    pSmAppSetupCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*���ulOpId����*/
    pSmAppSetupCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*���MID����*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*���ulErrorCode����*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppSetupCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*���bitOpErrorCodeΪfalse,��ǰ������Ϊ�գ���ʾû����*/
        pSmAppSetupCnf->ulRslt = APP_SUCCESS;
    }


    /*�����ؽ����ɹ�*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
                            &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*����״̬��ֵ*/
        pSmAppSetupCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*�������͸�ֵ*/
        pSmAppSetupCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

        /* ����ר�г��أ���ֵLinkCid */
        pSmAppSetupCnf->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppSetupCnf->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppSetupCnf->ulLinkCid)
        {
            pSmAppSetupCnf->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppSetupCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }

        /*���ص�ַ��ֵ*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppSetupCnf->bitOpPdnAddr = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupCnf->stPDNAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupCnf->stSubnetMask),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if (NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppSetupCnf->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupCnf->stGateWayAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        /*����APN����*/
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn )
        {
            pSmAppSetupCnf->bitOpApn = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupCnf->stApnInfo), \
                        (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo), \
                        sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*����SDF QOS����*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppSetupCnf->ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppSetupCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupCnf->stSdfQosInfo), \
                            (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo), \
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*����PCO��Ϣ*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_ProcSetUpMsgPcoInfo(pSmAppSetupCnf,pEpsCntxtInfo);
        }

    }
    else
    {
        pSmAppSetupCnf->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpSdfQos         = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpLinkCid        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppSetupCnf,ID_APP_ESM_PDP_SETUP_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppSetupCnf);

}
/*lint -specific(+e433)*/


VOS_VOID  NAS_ESM_SetNdisConnCnfMsgPcoInfo
(
    APP_ESM_NDISCONN_CNF_STRU          *pstEsmAppNdisConnCnf,
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsCntxtInfo
)
{
    NAS_ESM_PCO_TRANSFORM_STRU          stTransPco = {0};

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                &(pstEpsCntxtInfo->stPcoInfo),
                                &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 1);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Prim Dns is exist one!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 2);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Dns is exist two!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 3);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 4);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Prim P-CSCF is exist one!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 5);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:P-CSCF is exist two!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 6);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)(VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }

    return;
}


/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg)
{
    VOS_UINT16                          usOriginalId                = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId                = NAS_ESM_NULL;
    APP_ESM_NDISCONN_CNF_STRU          *pSmAppNdisConnCnfCnf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo               = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo             = VOS_NULL_PTR;


    if(VOS_NULL_PTR == pstEsmAppCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppNdisConnCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppNdisConnCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pSmAppNdisConnCnfCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_NDISCONN_CNF_STRU));
    /*lint +e433 +e826*/

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppNdisConnCnfCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppNdisConnCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppNdisConnCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppNdisConnCnfCnf), 0, \
                NAS_ESM_GET_MSG_LENGTH(pSmAppNdisConnCnfCnf));

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*���ulRabId����*/
        pSmAppNdisConnCnfCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppNdisConnCnfCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*���ulCid����*/
    pSmAppNdisConnCnfCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*���ulOpId����*/
    pSmAppNdisConnCnfCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*���MID����*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*���ulErrorCode����*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppNdisConnCnfCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*���bitOpErrorCodeΪfalse,��ǰ������Ϊ�գ���ʾû����*/
        pSmAppNdisConnCnfCnf->ulRslt = APP_SUCCESS;
    }


    /*�����ؽ����ɹ�*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
        &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*����״̬��ֵ*/
        pSmAppNdisConnCnfCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*�������͸�ֵ*/
        pSmAppNdisConnCnfCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;


        /*���ص�ַ��ֵ*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppNdisConnCnfCnf->bitOpPdnAddr = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppNdisConnCnfCnf->stPDNAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppNdisConnCnfCnf->stSubnetMask),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if (NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppNdisConnCnfCnf->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppNdisConnCnfCnf->stGateWayAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        /*����APN����*/
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn )
        {
            pSmAppNdisConnCnfCnf->bitOpApn = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppNdisConnCnfCnf->stApnInfo), \
                        (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo), \
                        sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*����SDF QOS����*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppNdisConnCnfCnf->ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppNdisConnCnfCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppNdisConnCnfCnf->stSdfQosInfo), \
                            (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo), \
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*����PCO��Ϣ*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_SetNdisConnCnfMsgPcoInfo(pSmAppNdisConnCnfCnf,pEpsCntxtInfo);
        }

    }
    else
    {
        pSmAppNdisConnCnfCnf->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpSdfQos         = NAS_ESM_OP_FALSE;

        pSmAppNdisConnCnfCnf->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppNdisConnCnfCnf,ID_APP_ESM_NDISCONN_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppNdisConnCnfCnf);

}
/*lint -specific(+e433)*/

/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulRslt
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_IND_STRU         *pSmAppSetupInd      = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    /*����ulOpId������һ��ulOpId����*/
    ulOpId = NAS_ESM_OPID_TYPE_SETUP_IND;

    /*��ñ���StateTblָ��*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*��ù�����CID����*/
    ulCid = pStateTblAddr->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pSmAppSetupInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_SETUP_IND_STRU));
    /*lint +e433 +e826*/
    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppSetupInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppSetupInd), 0, \
                NAS_ESM_GET_MSG_LENGTH(pSmAppSetupInd));

    /*���䱾�ι���APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppSetupInd,ID_APP_ESM_PDP_SETUP_IND,\
                              usOriginalId,usTerminalId,0);

    /*��װ��Ϣ����*/
    pSmAppSetupInd->ulCid = ulCid;
    pSmAppSetupInd->ulOpId= ulOpId;

    pSmAppSetupInd->ulRslt = ulRslt;

    if (APP_SUCCESS == ulRslt)
    {
        /*��ñ���EpsB���������Ľṹָ��*/
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

        pSmAppSetupInd->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        pSmAppSetupInd->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

        /* ����ר�г��أ���ֵLinkCid */
        pSmAppSetupInd->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppSetupInd->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppSetupInd->ulLinkCid)
        {
            pSmAppSetupInd->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppSetupInd->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }

        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppSetupInd->bitOpPdnAddr = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupInd->stPDNAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupInd->stSubnetMask),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppSetupInd->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupInd->stGateWayAddrInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo), \
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        pSmAppSetupInd->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->ulRabId = pEpsCntxtInfo->ulEpsbId;

        /*����APN����*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn)
        {
            pSmAppSetupInd->bitOpApn = NAS_ESM_OP_TRUE;

            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupInd->stApnInfo),\
                        (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo), \
                        sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*����SDF QOS����*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppSetupInd->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppSetupInd->stSdfQosInfo), \
                        (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo), \
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*����PCO��Ϣ*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_ProcSetUpMsgPcoInfo(pSmAppSetupInd,pEpsCntxtInfo);

        }

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pSmAppSetupInd);

        NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);
    }
    else
    {
        pSmAppSetupInd->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpSdfQos         = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpLinkCid        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpRabId          = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pSmAppSetupInd);
    }
}
/*lint -specific(+e433)*/

VOS_VOID NAS_ESM_SndEsmAppSdfModCnfMsg
(
    const NAS_ESM_APP_CNF_MSG_STRU      *pstEsmAppCnfMsg
)
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_CNF_STRU        *pSmAppModCnf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmAppModCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_MODIFY_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppModCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppModCnf), 0, \
                NAS_ESM_GET_MSG_LENGTH(pSmAppModCnf));

    /* ��ȡ�޸����� */
    if ( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpModifyType )
    {
        pSmAppModCnf->enBearerModifyType = pstEsmAppCnfMsg->enModfyType;
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg : Warning --> error modify type.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, 1);
        pSmAppModCnf->enBearerModifyType = APP_ESM_BEARER_MODIFY_BUTT;
    }

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*���ulRabId����*/
        pSmAppModCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppModCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppModCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*���ulCid����*/
    pSmAppModCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*���ulOpId����*/
    pSmAppModCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*���MID����*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*���ulErrorCode����*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppModCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*���bitOpErrorCodeΪfalse,��ǰ������Ϊ�գ���ʾû����*/
        pSmAppModCnf->ulRslt = APP_SUCCESS;
    }


    /*�����ؽ����ɹ�*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
       &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*����״̬��ֵ*/
        pSmAppModCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppModCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*�������͸�ֵ*/
        pSmAppModCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppModCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

         /*����SDF QOS����*/
         pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppModCnf->ulCid);
         if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
         {
             pSmAppModCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
             NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppModCnf->stSdfQosInfo), \
                         (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo), \
                         sizeof(APP_ESM_EPS_QOS_INFO_STRU));
         }
    }
    else
    {
        pSmAppModCnf->bitOpBearerState = NAS_ESM_OP_FALSE;
        pSmAppModCnf->bitOpBearerType = NAS_ESM_OP_FALSE;
        pSmAppModCnf->bitOpSdfQos = NAS_ESM_OP_FALSE;
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppModCnf,ID_APP_ESM_PDP_MODIFY_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppModCnf);

}
VOS_VOID NAS_ESM_SndEsmAppSdfModIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_IND_STRU        *pSmAppModifyInd     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;

    /*����ulOpId������һ��ulOpId����*/
    ulOpId = NAS_ESM_OPID_TYPE_MODIFY_IND;

    /*��ñ���StateTblָ��*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����ulOpId�����Ҷ�Ӧ��������*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    /*��ù�����CID����*/
    ulCid = pStateTblAddr->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmAppModifyInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_MODIFY_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppModifyInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfModIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppModifyInd), 0, \
                    NAS_ESM_GET_MSG_LENGTH(pSmAppModifyInd));

    /*���䱾�ι���APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppModifyInd,ID_APP_ESM_PDP_MODIFY_IND,\
                               usOriginalId,usTerminalId,0);

    /*��װ��Ϣ����*/
    pSmAppModifyInd->ulCid = ulCid;
    pSmAppModifyInd->ulOpId= ulOpId;

    pSmAppModifyInd->enBearerModifyType = enModfyType;

    pSmAppModifyInd->ulRslt = APP_SUCCESS;

    pSmAppModifyInd->bitOpBearerState = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

    pSmAppModifyInd->bitOpBearerType = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->enBearerType = pEpsCntxtInfo->enBearerCntxtType;


    pSmAppModifyInd->bitOpRabId = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->ulRabId = pEpsCntxtInfo->ulEpsbId;


    /*����SDF QOS����*/
    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);
    if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
    {
        pSmAppModifyInd->bitOpSdfQos= NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pSmAppModifyInd->stSdfQosInfo), \
                    (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo), \
                    sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }


    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppModifyInd);
}
VOS_VOID NAS_ESM_SndEsmAppSdfRelIndMsg
(
    VOS_UINT32                          ulCid,
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_IND_STRU       *pSmAppRelInd        = VOS_NULL_PTR;
     NAS_ESM_EPSB_CNTXT_INFO_STRU      *pEpsCntxtInfo       = VOS_NULL_PTR;

     NAS_ESM_LOG2("NAS_ESM_SndEsmAppSdfRelIndMsg", ulCid, ulEpsbId);
     TLPS_PRINT2LAYER_INFO2(NAS_ESM_SndEsmAppSdfRelIndMsg_ENUM, LNAS_ENTRY, ulCid, ulEpsbId);

    /*����ulOpId������һ��ulOpId����*/
    ulOpId = NAS_ESM_OPID_TYPE_RELEASE_IND;

    /*����ulEpsbId�����Ҷ�Ӧ��������*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmAppRelInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_RELEASE_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppRelInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfRelIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfRelIndMsg_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppRelInd), 0, NAS_ESM_GET_MSG_LENGTH(pSmAppRelInd));

    /*���䱾�ι���APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppRelInd,ID_APP_ESM_PDP_RELEASE_IND,\
                              usOriginalId,usTerminalId,0);

    /*��װ��Ϣ����*/
    pSmAppRelInd->ulCid = ulCid;
    pSmAppRelInd->ulOpId= ulOpId;

    pSmAppRelInd->ulRslt = APP_SUCCESS;

    /* ����PDN��Ϣ */
    pSmAppRelInd->bitOpPdnAddr = pEpsCntxtInfo->bitOpPdnAddr;
    NAS_ESM_MEM_CPY(    &pSmAppRelInd->stPDNAddrInfo,
                        &pEpsCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* ����ר�г��أ���ֵLinkCid */
    pSmAppRelInd->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppRelInd->ulCid);
    if (NAS_ESM_ILL_CID != pSmAppRelInd->ulLinkCid)
    {
        pSmAppRelInd->bitOpLinkCid = NAS_ESM_OP_TRUE;
    }
    else
    {
        pSmAppRelInd->bitOpLinkCid = NAS_ESM_OP_FALSE;
    }

    pSmAppRelInd->ulEpsbId = ulEpsbId;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppRelInd);

}



VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfMsg( const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg )
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_CNF_STRU       *pSmAppRelCnf       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU        *pEpsCntxtInfo      = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmAppRelCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_RELEASE_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppRelCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfRelCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfRelCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppRelCnf), 0, NAS_ESM_GET_MSG_LENGTH(pSmAppRelCnf));

    /*���ulCid����*/
    pSmAppRelCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*���ulOpId����*/
    pSmAppRelCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*���MID����*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*���ulErrorCode����*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppRelCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        pSmAppRelCnf->ulRslt = APP_SUCCESS;
    }

    /*�����ͷ�CNF��Ϣ*/
    if ((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
       &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /* ����PDN��Ϣ */
        pSmAppRelCnf->bitOpPdnAddr = pEpsCntxtInfo->bitOpPdnAddr;
        NAS_ESM_MEM_CPY(    &pSmAppRelCnf->stPDNAddrInfo,
                            &pEpsCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        /* ����ר�г��أ���ֵLinkCid */
        pSmAppRelCnf->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppRelCnf->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppRelCnf->ulLinkCid)
        {
            pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }
    }
    else
    {
        pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        pSmAppRelCnf->bitOpPdnAddr = NAS_ESM_OP_FALSE;
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppRelCnf,ID_APP_ESM_PDP_RELEASE_CNF,\
                               usOriginalId,usTerminalId,\
                               pstEsmAppCnfMsg->ulSn);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppRelCnf);

}
VOS_VOID NAS_ESM_SaveAppOpId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulOpId )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*���ݲ���ulStateTblIndex������״̬��λ��*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����ulOpId����*/
    pstStateAddr->stAppMsgRecord.ulAppMsgOpId = ulOpId;
}


VOS_VOID NAS_ESM_SaveAppMidHeader( VOS_UINT32 ulStateTblIndex,
                                                VOS_UINT16  usOriMid,
                                                VOS_UINT16 usTerMid)

{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*���ݲ���ulStateTblIndex������״̬��λ��*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����APP��Ϣ�е�MID����*/
    pstStateAddr->stAppMsgRecord.usOriginalId = usOriMid;
    pstStateAddr->stAppMsgRecord.usTerminalId= usTerMid;
}


VOS_VOID NAS_ESM_AssignMidHeader( VOS_UINT16  *pusOriMid,VOS_UINT16 *pusTerMid)
{
    /*��ʼ��MID����ֵ*/
    *pusOriMid = NAS_ESM_APP_ORIGIN_MID;  /*FFS*/
    *pusTerMid = NAS_ESM_APP_TERMIN_MID;
}


VOS_VOID  NAS_ESM_SaveAppMsgType( VOS_UINT32 ulStateTblIndex, APP_ESM_MSG_TYPE_ENUM_UINT32 enAppMsgType )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*���ݲ���ulStateTblIndex������״̬��λ��*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����APP��Ϣ����*/
    pstStateAddr->stAppMsgRecord.enAppMsgType = enAppMsgType;
}

VOS_VOID  NAS_ESM_SaveLinkedEpbsId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulLinkedEpsbId )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*���ݲ���ulStateTblIndex������״̬��λ��*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����APP��Ϣ����*/
    pstStateAddr->ulLinkedEpsbId = ulLinkedEpsbId;
}


VOS_VOID  NAS_ESM_ProcSetUpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo)
{
    APP_ESM_PDP_SETUP_IND_STRU         *pstSmAppSetup       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_PCO_TRANSFORM_STRU          stTransPco          = {NAS_ESM_NULL};

    pstEpsCntxtInfo = pstCntxtInfo;
    pstSmAppSetup = pstRsvMsg;

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                &(pstEpsCntxtInfo->stPcoInfo),
                                &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 1);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 2);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSmAppSetup->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 3);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSmAppSetup->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSmAppSetup->stDnsSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 4);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 5);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSmAppSetup->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 6);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)(VOS_VOID*)&(pstSmAppSetup->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSmAppSetup->stPCscfSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgRefuseProc
 Description     : App�ܾ����ؼ��������޸ĵĴ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppPdpManageRspMsgRefuseProc
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* �жϻ�����Ϣ�Ƿ���� */
    if (pstStateAddr->pstDecodedNwMsg == VOS_NULL_PTR)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Decoded Nw Msg not exist!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_NULL_PTR, 1);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucESMCau    = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = pstStateAddr->pstDecodedNwMsg->ucEpsbId;

    /*����ռ�ͼ���Ƿ����ɹ�,���ڴ��SM׼���ظ����������Ϣ*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_NULL_PTR, 2);
        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /* ���ݻ���Ŀտ���Ϣ���ͣ����������Ӧ�ľܾ���Ϣ */
    switch (pstStateAddr->pstDecodedNwMsg->enEsmCnMsgType)
    {
        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_ActDefltBearFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_ActDediBearFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_BearModFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        default:
            NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Msg type illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_MSG_INVALID);

            /*�ͷ�״̬����Դ*/
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            break;
    }

    /*�ͷſտ���Ϣռ�õĿռ�*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg    = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgAcceptProc
 Description     : App���ܳ��ؼ��������޸ĵĴ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppPdpManageRspMsgAcceptProc
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* �жϻ�����Ϣ�Ƿ���� */
    if (pstStateAddr->pstDecodedNwMsg == VOS_NULL_PTR)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgAcceptProc:ERROR:Decoded Nw Msg not exist!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_NULL_PTR, 1);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = pstStateAddr->ulEpsbId;

    /*����ռ�ͼ���Ƿ����ɹ�,���ڴ��SM׼���ظ����������Ϣ*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgAcceptProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_NULL_PTR, 2);
        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /* ���ݻ���Ŀտ���Ϣ���ͣ����������Ӧ�ľܾ���Ϣ */
    switch (pstStateAddr->pstDecodedNwMsg->enEsmCnMsgType)
    {
        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_DefltBearActMsgAutoAccept(ulStateTblIndex,
                                              stEncodeInfo,
                                              pstStateAddr->pstDecodedNwMsg);
            break;
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                             stEncodeInfo,
                                             pstStateAddr->pstDecodedNwMsg);
            break;
        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                         pstStateAddr->pstDecodedNwMsg);
            break;
        default:
            NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Msg type illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_MSG_INVALID);

            /*�ͷ�״̬����Դ*/
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            break;
    }

    /*�ͷſտ���Ϣռ�õĿռ�*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg    = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}
VOS_VOID NAS_ESM_AppProcAbortNotifyProc( VOS_VOID *pRcvMsg )
{
    APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU   *pAppMsg = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU        *pstStateAddr   = VOS_NULL_PTR;
    VOS_UINT32 ulRcvCid  = NAS_ESM_ILL_CID;
    VOS_UINT32 ulStateId = NAS_ESM_ILL_STATETAL_INDEX;

    NAS_ESM_INFO_LOG("NAS_ESM_AppProcAbortNotifyProc enter!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppProcAbortNotifyProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU*)pRcvMsg;

    ulRcvCid = pAppMsg->ulCid;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, LNAS_EMM_LTE_SUSPEND);
        return;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulRcvCid, &ulStateId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: CID is not in state table!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, ESM_CID_ERROR);
        return;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateId);

    /* �����ȡ�����ǽ������ؽ�����������ֹͣ�ӳ��ͷŷǽ������ض�ʱ�� */
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);
    }

    if((NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
       && (NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
       && ((ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
            || (ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: attaching!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, 1);

        /* ����APP�������������µ�ATTACH����, �������̬���е�APP��ر�ʶ */
        /* ����ֹESM����, ����֤EMM���̼������� */
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_FALSE;
        return;
    }
    else
    {
        /* ����Ƿǽ������أ�����֪ͨEMMɾ������ESM���̵��µĻ������Ϣ
           ����ǽ������أ������ͷŶ�̬����Դʱ*/
        if (NAS_ESM_BEARER_TYPE_EMERGENCY != pstStateAddr->enBearerCntxtType)
        {
            NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(pstStateAddr->ulCid, PS_FALSE);
        }

        /* ��������, ֱ���ͷŶ�̬����Դ */
        NAS_ESM_RelStateTblResource(ulStateId);
        return;
    }

}
VOS_UINT32 NAS_ESM_VerifyAppPppDialSceneAndParam( VOS_VOID *pRcvMsg )
{
    APP_ESM_PDP_SETUP_REQ_STRU      *pstAppPdpSetupReq = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU           *pstSdfPara = VOS_NULL_PTR;

    pstAppPdpSetupReq   = (APP_ESM_PDP_SETUP_REQ_STRU *)pRcvMsg;
    pstSdfPara  = NAS_ESM_GetSdfParaAddr(pstAppPdpSetupReq->ulCid);

    /* ����PDP�������� */
    if (APP_ESM_PDP_SETUP_TYPE_PPP != pstAppPdpSetupReq->enSetupType)
    {
        return APP_SUCCESS;
    }

    /* ȥע��״̬�²�����PPP���� */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_VerifyAppPppDialSceneAndParam:ERR: PPP dial up is not allowed when ESM is detached!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_VerifyAppPppDialSceneAndParam_ENUM, 1);
        return APP_ERR_SM_DETACHED;
    }

    /* PPP���ű�����ȱʡ�������� */
    if(pstSdfPara->enBearerCntxtType != APP_ESM_BEARER_TYPE_DEFAULT)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_VerifyAppPppDialSceneAndParam:ERR: Bearer type is not default!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_VerifyAppPppDialSceneAndParam_ENUM, 2);
        return APP_ERR_SM_BEARER_TYPE_NOT_DEFAULT;

    }
    return APP_SUCCESS;

}


VOS_VOID NAS_ESM_EncodeEpsUlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                            *pSendUlAmbr
)
{
    VOS_UINT32                          ulULApnAmbrExt;
    VOS_UINT32                          ulULApnAmbrExt2;

    VOS_UINT32                          ulULApnAmbr;

    VOS_UINT32                          *pTmpSendAmbr         = pSendUlAmbr;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsAmbr:INFO:NAS_ESM_EncodeEpsAmbr been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsUlAmbr_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendAmbr) || (VOS_NULL_PTR == pstEpsAmbr))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsAmbr:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsUlAmbr_ENUM, LNAS_NULL_PTR);
        return ;
    }

    *pTmpSendAmbr = (VOS_UINT32)pstEpsAmbr->ucULApnAmbr;

    ulULApnAmbr = (VOS_UINT32)pstEpsAmbr->ucULApnAmbr;


    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpULApnAmbrExt)
    {
        ulULApnAmbrExt = (((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt)<< NAS_ESM_MOVEMENT_8_BITS);

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulULApnAmbrExt ;

        *pTmpSendAmbr = (ulULApnAmbr | ulULApnAmbrExt) ;

        *pSendUlAmbr = (ulULApnAmbr | ulULApnAmbrExt);

    }

    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpULApnAmbrExt2)
    {
        ulULApnAmbrExt2 = (((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt2)<< NAS_ESM_MOVEMENT_16_BITS);

        *pTmpSendAmbr = (*pTmpSendAmbr )| ulULApnAmbrExt2 ;
    }

    return ;
}

VOS_VOID NAS_ESM_EncodeEpsDlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                          *pSendDlAmbr
)
{
    VOS_UINT32                          ulDLApnAmbrExt;
    VOS_UINT32                          ulDLApnAmbrExt2;

    VOS_UINT32                          *pTmpSendAmbr         = pSendDlAmbr;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsDlAmbr:INFO:NAS_ESM_EncodeEpsAmbr been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsDlAmbr_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendAmbr) || (VOS_NULL_PTR == pstEpsAmbr))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsAmbr:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsDlAmbr_ENUM, LNAS_NULL_PTR);
        return ;
    }

    *pTmpSendAmbr = (VOS_UINT32)pstEpsAmbr->ucDLApnAmbr;


    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpDLApnAmbrExt)
    {
        ulDLApnAmbrExt = ((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt)<< NAS_ESM_MOVEMENT_8_BITS;

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulDLApnAmbrExt ;

    }

    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpDLApnAmbrExt2)
    {
        ulDLApnAmbrExt2 = ((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt2)<< NAS_ESM_MOVEMENT_16_BITS;

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulDLApnAmbrExt2 ;
    }

    return ;
}



VOS_UINT32  NAS_ESM_CompareEsmInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_ESM_SUCCESS;
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    VOS_UINT32                          ulDLApnAmbr = NAS_ESM_NULL;
    VOS_UINT32                          ulULApnAmbr = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_CompareEsmInfo:entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CompareEsmInfo_ENUM, LNAS_ENTRY);

    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        NAS_ESM_EncodeEpsUlAmbr(&(pstEpsbCntxtInfo->stApnAmbrInfo),&ulULApnAmbr);
        NAS_ESM_EncodeEpsDlAmbr(&(pstEpsbCntxtInfo->stApnAmbrInfo),&ulDLApnAmbr);

        ulCnt = ulEpsbId - NAS_ESM_MIN_EPSB_ID;

        NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered,ulCnt = !",ulCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 1, ulCnt);

        g_stEsmOmInfo[ulCnt].ulEpsbId = ulEpsbId;

        NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered,g_stEsmOmInfo[ulCnt].ulEpsbId = !",g_stEsmOmInfo[ulCnt].ulEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 2, g_stEsmOmInfo[ulCnt].ulEpsbId);

        /* �Ƚϳ���״̬�Ƿ���ͬ */
        if (g_stEsmOmInfo[ulCnt].enBearerCntxtState != pstEpsbCntxtInfo->enBearerCntxtState)
        {
            g_stEsmOmInfo[ulCnt].enBearerCntxtState = pstEpsbCntxtInfo->enBearerCntxtState;
            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚϳ��������Ƿ���ͬ */
        if (g_stEsmOmInfo[ulCnt].enBearerCntxtType != pstEpsbCntxtInfo->enBearerCntxtType)
        {
            g_stEsmOmInfo[ulCnt].enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�LINKCID�Ƿ���ͬ */
        if (g_stEsmOmInfo[ulCnt].ulLinkBearId != pstEpsbCntxtInfo->ulLinkedEpsbId)
        {
            g_stEsmOmInfo[ulCnt].ulLinkBearId = pstEpsbCntxtInfo->ulLinkedEpsbId;
            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�CID�Ƿ���ͬ */
        if (g_stEsmOmInfo[ulCnt].ulCid != pstEpsbCntxtInfo->ulBitCId)
        {
            g_stEsmOmInfo[ulCnt].ulCid = pstEpsbCntxtInfo->ulBitCId;
            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�QOS�����Ƿ���ͬ */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stSdfQosInfo),
                                                &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                                                sizeof(APP_ESM_EPS_QOS_INFO_STRU)))
        {
            NAS_ESM_MEM_CPY(&(g_stEsmOmInfo[ulCnt].stSdfQosInfo),
                            &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));

            NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered!,g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI = ",g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 3, g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI);

            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�APN�Ƿ���ͬ */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stApn),
                                                &(pstEpsbCntxtInfo->stApnInfo),
                                                sizeof(APP_ESM_APN_INFO_STRU)))
        {
            NAS_ESM_MEM_CPY(&(g_stEsmOmInfo[ulCnt].stApn),
                            &(pstEpsbCntxtInfo->stApnInfo),
                            sizeof(APP_ESM_APN_INFO_STRU));

            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�IP ADDR�Ƿ���ͬ */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stIpAddr),
                                                 &(pstEpsbCntxtInfo->stPdnAddrInfo),
                                                 sizeof(APP_ESM_IP_ADDR_STRU)))
        {
            NAS_ESM_MEM_CPY(&(g_stEsmOmInfo[ulCnt].stIpAddr),
                             &(pstEpsbCntxtInfo->stPdnAddrInfo),
                             sizeof(APP_ESM_IP_ADDR_STRU));

            ulRst = NAS_ESM_FAILURE;
        }

        /* �Ƚ�AMBR */
        if ((ulULApnAmbr!= g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulULApnAmbr)
            ||(ulDLApnAmbr!= g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulDLApnAmbr))
        {


            g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulULApnAmbr = ulULApnAmbr;
            g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulDLApnAmbr = ulDLApnAmbr;

            ulRst = NAS_ESM_FAILURE;
        }

    }

    return ulRst;
}
/*lint +e961*/
/*lint +e960*/



VOS_UINT32  NAS_ESM_DtComparePdpInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_ESM_SUCCESS;

    NAS_OM_ACT_PDP_INFO_STRU   *pstActPdpInfo = (VOS_VOID *) NAS_ESM_MEM_ALLOC(sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    if (VOS_NULL_PTR == pstActPdpInfo)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_DtComparePdpInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DtComparePdpInfo_ENUM, LNAS_NULL_PTR);
        return NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_SET(pstActPdpInfo, 0, sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    /*��ȡ������ص���Ϣ*/
    NAS_ESM_GetActPdpInfo(pstActPdpInfo);

    /*�Ƚϼ��������Ϣ�Ƿ�仯*/
    if( 0 != NAS_ESM_MEM_CMP(&g_stEsmDtInfo.stActPdpInfo,pstActPdpInfo,sizeof(NAS_OM_ACT_PDP_INFO_STRU)))
    {
        ulRst = NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_FREE(pstActPdpInfo);

    return ulRst;

}


VOS_VOID NAS_ESM_DtJudgeifNeedRpt(VOS_VOID)
{

    /*�ж��Ƿ���Ҫ�ϱ�pdp*/
    if(APP_ESM_DT_REPORT_STATUS_OPEN== g_ulRptPdpStatus)
    {
        if(NAS_ESM_FAILURE == NAS_ESM_DtComparePdpInfo())
        {
            #if (VOS_WIN32 != VOS_OS_VER)
            NAS_ESM_ReportActPdpInfo();
            #endif
        }
    }

    return;
}
VOS_UINT32 NAS_ESM_CheckSdfHaveUplinkPacketFilter
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara
)
{
    VOS_UINT32                             ulIndex     = 0;
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8  enDirection = APP_ESM_TRANSFER_DIRECTION_BUTT;

    for(ulIndex = 0; ulIndex < pstSdfPara->ulPfNum; ulIndex++)
    {
        enDirection = pstSdfPara->astCntxtTftInfo[ulIndex].enDirection;
        if((APP_ESM_TRANSFER_DIRECTION_UPLINK == enDirection)
            ||(APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == enDirection))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_CheckSdfHaveUplinkPacketFilter: Info, there is uplink PF.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckSdfHaveUplinkPacketFilter_ENUM, LNAS_SUCC);
            return NAS_ESM_SUCCESS;
        }
    }

    NAS_ESM_WARN_LOG("NAS_ESM_CheckSdfHaveUplinkPacketFilter: WARN, no uplink PF.");
    TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckSdfHaveUplinkPacketFilter_ENUM, LNAS_FAIL);
    return NAS_ESM_FAILURE;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

