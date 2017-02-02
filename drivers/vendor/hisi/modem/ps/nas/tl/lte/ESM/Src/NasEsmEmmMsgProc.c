

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmEmmMsgProc.h"
#include    "NasEsmNwMsgProc.h"
#include    "NasEsmInclude.h"
#include    "NasEsmIpMsgProc.h"
/*#include  "IpDhcpv4Server.h"*/
#include "NasEsmAppMsgParaProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMEMMMSGPROC_C
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
#if (FEATURE_ON == FEATURE_PTM)
NAS_ESM_CN_CAUSE_TRANS_STRU          g_astEsmErrlogErrNoMap[] =
{
    /*------------casue-----------------------------------error id---------------------------*/
    {NAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING,      ESM_OM_ERRLOG_CAUSE_OPERATOR_DETERMINE_BARRING},
    {NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES,          ESM_OM_ERRLOG_CAUSE_INSUFFICIENT_RESOURCES},
    {NAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN,          ESM_OM_ERRLOG_CAUSE_UNKNOWN_OR_MISSING_APN},
    {NAS_ESM_CAUSE_UNKNOWN_PDN_TYPE,                ESM_OM_ERRLOG_CAUSE_UNKNOWN_PDN_TYPE},
    {NAS_ESM_CAUSE_USER_AUTH_FAIL,                  ESM_OM_ERRLOG_CAUSE_USER_AUTH_FAIL},
    {NAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW,           ESM_OM_ERRLOG_CAUSE_REQ_REJ_BY_SGW_OR_PGW},
    {NAS_ESM_CAUSE_REQ_REJ_UNSPECITY,               ESM_OM_ERRLOG_CAUSE_REQ_REJ_UNSPECITY},
    {NAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT,      ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_NOT_SUPPORT},
    {NAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED,      ESM_OM_ERRLOG_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED},
    {NAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER,   ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER},
    {NAS_ESM_CAUSE_PTI_ALREADY_IN_USED,             ESM_OM_ERRLOG_CAUSE_PTI_ALREADY_IN_USED},
    {NAS_ESM_CAUSE_REGULAR_DEACTIVATION,            ESM_OM_ERRLOG_CAUSE_REGULAR_DEACTIVATION},
    {NAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT,              ESM_OM_ERRLOG_CAUSE_EPS_QOS_NOT_ACCEPT},
    {NAS_ESM_CAUSE_NETWORK_FAILURE,                 ESM_OM_ERRLOG_CAUSE_NETWORK_FAILURE},
    {NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT,            ESM_OM_ERRLOG_CAUSE_SYNTACTIC_ERR_IN_TFT},
    {NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER,   ESM_OM_ERRLOG_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER},
    {NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER, ESM_OM_ERRLOG_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER},
    {NAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT,          ESM_OM_ERRLOG_CAUSE_BEARER_WITHOUT_TFT_ACT},
    {NAS_ESM_CAUSE_PTI_MISMATCH,                    ESM_OM_ERRLOG_CAUSE_PTI_MISMATCH},
    {NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED,    ESM_OM_ERRLOG_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED},
    {NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED,       ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED,       ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED, ESM_OM_ERRLOG_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED,    ESM_OM_ERRLOG_CAUSE_ESM_INFORMATION_NOT_RECEIVED},
    {NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST,   ESM_OM_ERRLOG_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST},
    {NAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED, ESM_OM_ERRLOG_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED},
    {NAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST,  ESM_OM_ERRLOG_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST},
    {NAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE,           ESM_OM_ERRLOG_CAUSE_UNSUPPORTED_QCI_VALUE},
    {NAS_ESM_CAUSE_INVALID_PTI_VALUE,               ESM_OM_ERRLOG_CAUSE_INVALID_PTI_VALUE},
    {NAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE,  ESM_OM_ERRLOG_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE},
    {NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION,   ESM_OM_ERRLOG_CAUSE_INVALID_MANDATORY_INFORMATION},
    {NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED, ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED},
    {NAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA, ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA},
    {NAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED, ESM_OM_ERRLOG_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED},
    {NAS_ESM_CAUSE_CONDITIONAL_IE_ERROR,            ESM_OM_ERRLOG_CAUSE_CONDITIONAL_IE_ERROR},
    {NAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA,     ESM_OM_ERRLOG_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA},
    {NAS_ESM_CAUSE_PROTOCOL_ERROR,                  ESM_OM_ERRLOG_CAUSE_PROTOCOL_ERROR},
    {NAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER, ESM_OM_ERRLOG_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER},
};

static VOS_UINT32   g_astEsmErrlogErrNum
        = sizeof(g_astEsmErrlogErrNoMap)/sizeof(NAS_ESM_CN_CAUSE_TRANS_STRU);
#endif



/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID NAS_ESM_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EmmMsgDistr_ENUM, LNAS_ENTRY);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_EMM_ESM_SUSPEND_IND:
            NAS_ESM_RcvEsmEmmSuspendInd( (EMM_ESM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        case ID_EMM_ESM_RESUME_IND:
            NAS_ESM_RcvEsmEmmResumeInd( (EMM_ESM_RESUME_IND_STRU *) pRcvMsg );
            break;
        /*����յ�����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
        case ID_EMM_ESM_PDN_CON_IND:

            /*����Sm_RcvEsmEmmDataInd����*/
            NAS_ESM_RcvEsmEmmPdnConInd( (EMM_ESM_PDN_CON_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ESM_DATA_IND��Ϣ*/
        case ID_EMM_ESM_DATA_IND:

            /*����Sm_RcvEsmEmmDataInd����*/
            NAS_ESM_RcvEsmEmmDataInd( (EMM_ESM_DATA_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ESM_EST_CNF��Ϣ*/
        case ID_EMM_ESM_EST_CNF:

            /*����Sm_RcvEsmEmmDataInd����*/
            NAS_ESM_RcvEsmEmmEstCnf( (EMM_ESM_EST_CNF_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ESM_STATUS_IND��Ϣ*/
        case ID_EMM_ESM_STATUS_IND:

            /*����Sm_RcvEsmEmmStatusInd����*/
            NAS_ESM_RcvEsmEmmStatusInd( (EMM_ESM_STATUS_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ESM_BEARER_STATUS_IND��Ϣ*/
        case ID_EMM_ESM_BEARER_STATUS_IND:

            /*����Sm_RcvEsmEmmBearerStatusInd����*/
            NAS_ESM_RcvEsmEmmBearerStatusInd( (EMM_ESM_BEARER_STATUS_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ESM_REL_IND��Ϣ*/
        case ID_EMM_ESM_REL_IND:
            NAS_ESM_RcvEsmEmmRelInd();
            break;
        case ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND:
            NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd();
            break;
        case ID_EMM_ESM_START_NOTIFY_IND:
            NAS_ESM_RcvEsmEmmStartNotifyInd();
            break;

        case ID_EMM_ESM_PLMN_CHANGE_IND:
            NAS_ESM_RcvEsmEmmPlmnChangeInd();
            break;

        case ID_EMM_ESM_STOP_NOTIFY_IND:
            NAS_ESM_RcvEsmEmmStopNotifyInd();
            break;
        /*PC REPLAY MODIFY BY LEILI END*/
        #if(VOS_WIN32 == VOS_OS_VER)
        case ID_EMM_ESM_REPLAY_EXPORT_CTX_IND:
            NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:EMM->SM Message ID_EMM_ESM_REPLAY_EXPORT_CTX_IND!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, 1);
            (void)NAS_ESM_ExportContextData();
            (void)NAS_ERABM_ExportContextData();

            break;
        #endif
        /*PC REPLAY MODIFY BY LEILI END*/

        /*�յ�ID_ESM_EMM_DATA_CNF�Ĵ���*/
        case ID_EMM_ESM_DATA_CNF:
             NAS_ESM_RcvEsmEmmDataCnf((EMM_ESM_DATA_CNF_STRU *)pRcvMsg);
             break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY:
             NAS_ESM_RcvEsmEmmClearClBearerNotify();
             break;
        #endif

        default:
            NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:EMM->SM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

VOS_VOID NAS_ESM_RcvEsmEmmRelInd(VOS_VOID)
{
    /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    NAS_ESM_RcvEmmDetachMsg();
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_RcvEsmEmmSuspendInd(const EMM_ESM_SUSPEND_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();

    (VOS_VOID)pRcvMsg;

    /* ����״̬Ϊ����̬ */
    NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_SUSPENDED);

    /*����ӳ��ͷŷǽ������ض�ʱ�����ڣ���ֹͣ*/
    NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);

    /* ��ն�̬�������APP��Ϣ����ظ�APP��Ӧ����ʧ�ܣ�ԭ��ֵΪ���� */
    NAS_ESM_ClearStateTable(APP_ERR_SM_SUSPENDED, PS_FALSE);

    /* �ͷ�ATTACHING���ͻ����¼ */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paAttBuffer[ulCnt] != VOS_NULL_PTR)
        {
            NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);
        }
    }

    /* ��ESM��ǰ״̬Ϊע���У���״̬תΪȥע��̬����GUģע��ɹ���֪ͨLMM��
       ����LMM֪ͨESM����ע��̬�� */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);
    }

    /* ���֧��˫APN����ֹͣע������ؽ���ʱ�� */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
    }

    /* �ظ�EMM����ɹ� */
    NAS_ESM_SndEsmEmmSuspendRsp(EMM_ESM_RSLT_TYPE_SUCC);
}


VOS_VOID  NAS_ESM_RcvEsmEmmResumeInd(const EMM_ESM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* ����״̬Ϊ����̬ */
    NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_NORMAL);

    /* �ظ�EMM��ҳɹ� */
    NAS_ESM_SndEsmEmmResumeRsp(EMM_ESM_RSLT_TYPE_SUCC);

    /* ���֧��˫APN�����ж��Ƿ���Ҫ����ע������ؽ���ʱ�� */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        if ((NAS_ESM_GetCurPdnNum() > 0) &&
            (NAS_ESM_UNASSIGNED_EPSB_ID == NAS_ESM_GetAttachBearerId()))
        {
            /* ���ע������ؽ���ʱ��ʱ����Ϊ0�����������ؽ����� */
            if (0 != NAS_ESM_GetAttachBearerReestTimerLen())
            {
                NAS_ESM_TimerStart(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
            }
        }
    }
}

VOS_VOID  NAS_ESM_RcvEsmEmmPdnConIndFindSdfPara
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    APP_ESM_SDF_PARA_STRU              *pstAppSdfPara
)
{
    VOS_UINT32                          ulCur               = NAS_ESM_NULL;
    VOS_UINT32                          ulSdfNum            = NAS_ESM_NULL;

    /* ��һ��ȡ12��NV���� */
    for (ulCur = NAS_ESM_MIN_CID; ulCur < NAS_ESM_CID_NV_NUM; ulCur++)
    {
        pstAppSdfPara->ulCId = ulCur;
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        if (APP_FAILURE == NAS_ESM_GetSdfPara(&ulSdfNum, pstAppSdfPara))
        {
            continue;
        }

        if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
        {
            /* ���ѡȡ��NV������APN��#50�ܾ�����ѡȡ��һ�� */
            if (NAS_ESM_FAILURE == NAS_ESM_IsCurrentApnAvailable(pstAppSdfPara->enPdnType,
                                                                pstAppSdfPara->bitOpApn,
                                                                &(pstAppSdfPara->stApnInfo)))
            {
                continue;
            }
        }

        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);
        NAS_ESM_MEM_CPY(pstSdfPara, pstAppSdfPara, sizeof(APP_ESM_SDF_PARA_STRU));
    }
}
VOS_VOID  NAS_ESM_RcvEsmEmmPdnConInd(const EMM_ESM_PDN_CON_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulRegCId            = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    APP_ESM_SDF_PARA_STRU              *pstAppSdfPara       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pEpsbManageInfo     = VOS_NULL_PTR;


    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmPdnConInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_ENTRY);

    (VOS_VOID)pRcvMsg;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmPdnConInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_EMM_LTE_SUSPEND);

        NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_NORMAL);
    }

    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_RcvEsmEmmPdnConInd:NORM: received abnormal Pdn Con Ind !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_STATUS_ERROR);

        if (PS_TRUE == NAS_ESM_HasEmergencyPdn())
        {
            /*����н������أ���������ͷ����зǽ�������*/
            NAS_ESM_ClearEsmResoureWhenEstingEmcPdn();
        }
        else
        {
            /*ESMȥע�ᣬ�ͷ���Դ*/
            NAS_ESM_RcvEmmDetachMsg();
        }
    }

    pstAppSdfPara = NAS_ESM_MEM_ALLOC(sizeof(APP_ESM_SDF_PARA_STRU));

    if (VOS_NULL_PTR == pstAppSdfPara)
    {
         /*��ӡ���Ϸ���Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_NULL_PTR);

        /* �ظ�EMM ID_EMM_ESM_PDN_CON_RSP��FAIL�� */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        return;
    }

    /* ��һ��ȡ12��NV���� */
    NAS_ESM_RcvEsmEmmPdnConIndFindSdfPara(pstSdfPara,pstAppSdfPara);

    NAS_ESM_MEM_FREE(pstAppSdfPara);

    /* ��APP��ȡ���ع���ģʽ���������ȡ�Զ�����ģʽ */
    pEpsbManageInfo = NAS_ESM_GetBearerManageInfoAddr();
    if (APP_FAILURE == NAS_ESM_GetPdpManageInfo(pEpsbManageInfo))
    {
        /*��ӡ������Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmPdnConInd:WARN: Fail to get PDP Manage Info from APP!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_FAIL);
        pEpsbManageInfo->enMode = APP_ESM_BEARER_MANAGE_MODE_AUTO;
        pEpsbManageInfo->enType = APP_ESM_BEARER_MANAGE_TYPE_ACCEPT;
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    /* ��ȡ����ע���CID�����ȼ�˳���ɸߵ���ΪCID0 > CID1-CID11 > CID12-CID20 */
    /* ���˸�����Ӫ����������, ��ҪGU NV��CID0��ʼ��Ϊר�����ͣ�CID11Ϊȱʡ����*/
    ulRegCId = NAS_ESM_GetRegistCid();
    /* add by yanglei 00307272 for KEY_INFO_REPORT3, 2015-08-19, begin */
    NAS_ESM_SndOmRegCidInfo(ulRegCId);
    /* add by yanglei 00307272 for KEY_INFO_REPORT3, 2015-08-19, end */
    if (NAS_ESM_ILL_CID == ulRegCId)
    {
        /*��ӡ���Ϸ���Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd: There is no default bearer type sdf");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, 1);

        /* �ظ�EMM ID_EMM_ESM_PDN_CON_RSP��FAIL�� */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        return ;
    }

    NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmPdnConInd:The cid of the found sdf is :", ulRegCId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_CID_IS, ulRegCId);

    /* ��ע���õ�CID������Ϣ���õ���̬���SDF���� */
    if (NAS_ESM_SUCCESS != NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl(&ulStateTblId,
                                        ulRegCId, pRcvMsg->enPdnReqType))
    {
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);

    /*����PTI,����洢��������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId               = pstStateAddr->ulEpsbId;

    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /*��װPDN_Connect_Req��Ϣ*/
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd:ERROR:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_EncodePdnConReqMsg_fail);

        /* �ظ�EMM ID_EMM_ESM_PDN_CON_RSP��FAIL��*/
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        NAS_ESM_RelStateTblResource(ulStateTblId);

        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*��EMM����ID_EMM_ESM_PDN_CON_RSP*/
    NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_SUCC, \
                                  pstStateAddr->stNwMsgRecord.ulMsgLength,\
                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /*ת��״̬*/
    NAS_ESM_SetProcTransState(ulStateTblId, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
}

/*****************************************************************************
 Function Name   : NAS_ESM_BufferDecodedNwMsg
 Description     : ����ESM��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-19  Draft Enact
    2.lihong00150010      2010-02-09 Modify
    3.lihong00150010      2010-04-22 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_BufferDecodedNwMsg
(
    const EMM_ESM_INTRA_DATA_IND_STRU  *pstEmmEsmIntraDataIndMsg,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    NAS_ESM_ATTACHING_BUFF_ITEM_STRU   *pstDecodedNwMsg     = VOS_NULL_PTR;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();
    VOS_UINT32                          ulBuffItemLen       = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    /* �ж��Ƿ��ѵ���ϵͳ�ܹ��洢�����¼�ļ��� */
    if (pstEsmBuffManInfo->ucAttBuffItemNum >= NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:WARN:Attaching Buffer is full!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, 1);
        return;
    }

    /* ���㻺���¼���� */
    ulBuffItemLen = sizeof(NAS_ESM_ATTACHING_BUFF_ITEM_STRU);

    /* ��ȡ�����¼�ռ� */
    pstDecodedNwMsg = (NAS_ESM_ATTACHING_BUFF_ITEM_STRU *)
                                NAS_COMM_AllocBuffItem( NAS_COMM_BUFF_TYPE_ESM,
                                                        ulBuffItemLen);
    if (VOS_NULL_PTR == pstDecodedNwMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:WARN:NAS_COMM_AllocBuffItem is failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* ���������Ժ��������Ϣ */
    NAS_ESM_MEM_CPY(&pstDecodedNwMsg->stDecodedNwMsg,
                    pstEmmEsmIntraDataIndMsg,
                    sizeof(EMM_ESM_INTRA_DATA_IND_STRU));

    /* ���������� */
    pstDecodedNwMsg->enDecodeRslt = enEsmCause;

    /* �������ڴ洢�����¼�׵�ַ��ָ�� */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paAttBuffer[ulCnt] == VOS_NULL_PTR)
        {
            break;
        }
    }

    if (ulCnt >= NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:Get the valuable which stores buffer item addr failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, LNAS_FAIL);
        return ;
    }

    /* ��¼�洢�����¼���׵�ַ */
    pstEsmBuffManInfo->paAttBuffer[ulCnt] = (VOS_VOID *)pstDecodedNwMsg;

    /* ���ӻ����¼���� */
    pstEsmBuffManInfo->ucAttBuffItemNum++;

    NAS_ESM_INFO_LOG1("NAS_ESM_BufferDecodedNwMsg:INFO:Buffer network msg success!", ulCnt);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_BufferDecodedNwMsg_ENUM, 2, ulCnt);
}


VOS_VOID NAS_ESM_RcvEsmEmmDataInd( EMM_ESM_DATA_IND_STRU *pRcvMsg )
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_ESM_NULL;
    EMM_ESM_INTRA_DATA_IND_STRU        *pstEmmEsmIntraDataIndMsg = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpSmMsg         = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;
    NAS_ESM_NW_MSG_STRU                *pstEsmNwMsgIE       = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDataInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmDataInd_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    pstEmmEsmIntraDataIndMsg = NAS_ESM_MEM_ALLOC(sizeof(EMM_ESM_INTRA_DATA_IND_STRU));
    if(VOS_NULL_PTR == pstEmmEsmIntraDataIndMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataInd:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_NULL_PTR, 1);
        return;
    }

    NAS_ESM_MEM_SET(pstEmmEsmIntraDataIndMsg, 0, sizeof(EMM_ESM_INTRA_DATA_IND_STRU));

    /*�����ڲ���ID_EMM_ESM_DATA_IND��Ϣ(Я��һ���ѽ����Ŀտ���Ϣ)*/
    pstEmmEsmIntraDataIndMsg->ulSenderPid = PS_PID_MM;

    pstEsmNwMsgIE = &(pstEmmEsmIntraDataIndMsg->stEsmNwMsgIE);

    /*ȡ������Ϣ��������SM��Ϣ�ĳ���*/
    ulRcvNwMsgLen = pRcvMsg->stEsmMsg.ulEsmMsgSize;
    if( ulRcvNwMsgLen > ESM_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING:EMM->SM Message NW Msg over-long!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_MSG_INVALID, 1);
        ulRcvNwMsgLen = ESM_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*ȡ��SM��Ϣ�׵�ַ*/
    pucTmpSmMsg = pRcvMsg->stEsmMsg.aucEsmMsg;

    pstEmmEsmIntraDataIndMsg->ulMsgId = ID_EMM_ESM_DATA_IND;

    /*���NAS_ESM_NW_MSG_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)pstEsmNwMsgIE, 0, sizeof(NAS_ESM_NW_MSG_STRU));

    /*���ÿտ���Ϣ��������, �������ʧ��ֱ�ӷ���*/
    enEsmCause = NAS_ESM_DecodeNwMsg( pucTmpSmMsg,
                                   &ulRcvNwMsgLen,
                                    pstEsmNwMsgIE );

    /* ��SM��״̬ΪNAS_ESM_PS_REGISTER_STATUS_ATTACHING���Ҵ���Ϣ��Ϊ
       ESM INFORMATION REQ��Ϣ����ȱʡ���ؼ���������Ϣ�������Ϣ���л��棻
       ����ֱ�Ӵ�����Ϣ */
    if((NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
        && (NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ != pstEsmNwMsgIE->enEsmCnMsgType)
        && (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ != pstEsmNwMsgIE->enEsmCnMsgType)
        && (NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ != pstEsmNwMsgIE->enEsmCnMsgType))
    {
        /* ����ESM��Ϣ */
        NAS_ESM_BufferDecodedNwMsg(pstEmmEsmIntraDataIndMsg, enEsmCause);

        NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);

        return;
    }

    /*����ռ�ͼ���Ƿ����ɹ�,���ڴ��SM׼���ظ����������Ϣ*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataInd:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_NULL_PTR, 2);

        NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);
        return;
    }

    /*����������󣬷��ؾܾ�����*/
    if( NAS_ESM_CAUSE_SUCCESS != enEsmCause )
    {
        NAS_ESM_ProcNwMsgForDecodeError(pstEsmNwMsgIE,enEsmCause);

        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING: NW Message Error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_MSG_INVALID, 2);
    }
    else/*�����Ϣ�����ɹ�*/
    {
        /*��������տ���Ϣ*/
        NAS_ESM_NwMsgProcess(pstEmmEsmIntraDataIndMsg);
    }

    /*�ͷſտ���Ϣռ�õĿռ�*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;

    NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);
}



VOS_VOID NAS_ESM_RcvEsmEmmBearerStatusInd(const EMM_ESM_BEARER_STATUS_IND_STRU *pRcvMsg )
{
    VOS_UINT32                  ulCnt                       = NAS_ESM_NULL;
    VOS_UINT32                  ulQueryRslt                 = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbId                    = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                  ulStateTblIndex             =  NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo          = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /* ���ESM���ڷ�ע��̬��ע����̬����ֱ�ӷ��� */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd:WARNING:Msg is discard cause ESM state is not attached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    /*ȡ��ID_EMM_ESM_BEARER_STATUS_IND��Ϣ�е�EPSID��Ϣ*/
    ulEpsbIdNum = pRcvMsg->ulEpsIdNum;
    NAS_ESM_MEM_CPY(aulEpsbId, pRcvMsg->aulEsmEpsId, ulEpsbIdNum*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��ѯÿһ��������Ϣ*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*ȡ��������Ϣ*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*����˳���δ����*/
        if( NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState )
        {
            continue;
        }

        ulQueryRslt = NAS_ESM_FAILURE;

        /*��ѯID_EMM_ESM_BEARER_STATUS_IND��Ϣ��EPSID��Ϣ���Ƿ�����˳���ID*/
        for( ulCnt = 0; ulCnt < ulEpsbIdNum; ulCnt++ )
        {
            if( ulEpsbId == aulEpsbId[ulCnt] )
            {
                ulQueryRslt = NAS_ESM_SUCCESS;
                break;
            }
        }

        /*���������*/
        if( NAS_ESM_FAILURE == ulQueryRslt )
        {
            /*֪ͨAPP�ͷų��أ����ͷ���س��غ���Դ*/
            NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*���֧��˫APN������ע����أ������д���*/
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        if (NAS_ESM_UNASSIGNED_EPSB_ID == NAS_ESM_GetAttachBearerId())
        {
            NAS_ESM_ReestablishAttachBearer();
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_BufferedNwMsgProc
 Description     : ����ESM������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-8-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_BufferedNwMsgProc()
{
    NAS_ESM_ATTACHING_BUFF_ITEM_STRU   *pstDecodedNwMsg     = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    /*����ռ�ͼ���Ƿ����ɹ�,���ڴ��SM׼���ظ����������Ϣ*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);

    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_BufferedNwMsgProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_BufferedNwMsgProc_ENUM, LNAS_NULL_PTR);
        return;
    }

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        /* ��ȡ�����¼ */
        pstDecodedNwMsg = (NAS_ESM_ATTACHING_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);

        if (pstDecodedNwMsg == VOS_NULL_PTR)
        {
            continue;
        }

        NAS_ESM_INFO_LOG1("NAS_ESM_BufferedNwMsgProc:NORM:Buffer Itmem Index:", ulCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_BufferedNwMsgProc_ENUM, 1, ulCnt);

        pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
        NAS_ESM_MEM_SET(    pstEsmSndNwMsg->pucNwMsg,
                            NAS_ESM_NULL,
                            ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);

        /*����������󣬷��ؾܾ�����*/
        if( NAS_ESM_CAUSE_SUCCESS != pstDecodedNwMsg->enDecodeRslt)
        {
            NAS_ESM_ProcNwMsgForDecodeError(&pstDecodedNwMsg->stDecodedNwMsg.stEsmNwMsgIE,
                                            pstDecodedNwMsg->enDecodeRslt);

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_BufferedNwMsgProc:WARNING: NW Message Error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferedNwMsgProc_ENUM, 2);
        }
        else/*�����Ϣ�����ɹ�*/
        {
            /*��������տ���Ϣ*/
            NAS_ESM_NwMsgProcess(&pstDecodedNwMsg->stDecodedNwMsg);
        }

        /* ��������¼ */
        NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);
    }

    /*�ͷſտ���Ϣռ�õĿռ�*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}
VOS_VOID NAS_ESM_RcvEsmEmmEstCnf(const EMM_ESM_EST_CNF_STRU *pRcvMsg )
{
    EMM_ESM_ATTACH_RESULT_ENUM_UINT32   ulEstRst         = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  = 0;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG2("NAS_ESM_RcvEsmEmmEstCnf is entered.", NAS_ESM_GetLModeStatus(), pRcvMsg->ulEstRst);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_RcvEsmEmmEstCnf_ENUM, LNAS_ENTRY, NAS_ESM_GetLModeStatus(), pRcvMsg->ulEstRst);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmEstCnf: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmEstCnf_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /*ȡ����Ϣ����*/
    ulEstRst = ((EMM_ESM_EST_CNF_STRU *)pRcvMsg)->ulEstRst;

    /*�жϵ�ǰEMMע��״̬�������Attaching��������Ϣ���ݣ�����ע��״̬��������*/
    if( NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
    {
        /*ע��ɹ�*/
        if( EMM_ESM_ATTACH_RESULT_SUCC == ulEstRst )
        {
            /*����ע��״̬*/
            NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHED);

            /* ����ESM������Ϣ */
            NAS_ESM_BufferedNwMsgProc();
        }
        else
        {
            /*EMMע��ʧ�ܻ�ȥע�ᣬ�ͷ���Դ*/
            NAS_ESM_RcvEmmDetachMsg();
        }
    }
    else if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED == NAS_ESM_GetEmmStatus())
    {
        /* �������PDN���ӽ��������EMM StatusInd�Գ�ʱ����ֵ��˷�֧��
         * �Գ�ʱEMM��Խ���PDN��EstReq������ʧ�ܣ�ESM������������:
         *      1. ���ı�ESM��¼��Emmע��״̬
         *      2. ������Ľ���PDN���ӽ�����Ϣʹ��DataReq�����ط���������T3482
         */
        if ((EMM_ESM_ATTACH_RESULT_FAIL == ulEstRst) &&
            (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexForEmc(&ulStateTblIndex)))
        {
            pstStateTblInfo = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmEstCnf", pstStateTblInfo->ulCid);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_RcvEsmEmmEstCnf_ENUM, 1, pstStateTblInfo->ulCid);

            NAS_ESM_SndEsmEmmDataReqMsg(pstStateTblInfo->stNwMsgRecord.ulOpId,
                                        pstStateTblInfo->stNwMsgRecord.ucIsEmcPdnReq,
                                        pstStateTblInfo->stNwMsgRecord.ulMsgLength,
                                        pstStateTblInfo->stNwMsgRecord.aucMsgBuff);

            /*����T3482��ʱ��*/
            NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

            /*״̬ת��*/
            /*֮ǰ�Ѿ����ģ����ﲻ������״̬*/
        }
    }
    else
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmEstCnf:Register Status is not attachingl!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmEstCnf_ENUM, ESM_STATUS_ERROR);
    }
}


VOS_VOID NAS_ESM_RcvEsmEmmStatusInd(const EMM_ESM_STATUS_IND_STRU *pRcvMsg )
{
    EMM_ESM_ATTACH_STATUS_ENUM_UINT32   ulEstRst;

	#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
    #endif

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStatusInd_ENUM, LNAS_ENTRY);

    /*ȡ����Ϣ����*/
    ulEstRst = ((EMM_ESM_STATUS_IND_STRU *)pRcvMsg)->enEMMStatus;

    /*�����Ϣ����ΪATTACHED����¼ע��״̬*/
    if( EMM_ESM_ATTACH_STATUS_ATTACHED == ulEstRst )
    {
        /*����ע��״̬*/
        NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHED);

        /* ����ESM������Ϣ */
        NAS_ESM_BufferedNwMsgProc();

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
        {
            /* PDN���ӻָ��ɹ��Ĵ��� */
            NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
        }
        #endif
    }
    /*��Ϣ����ΪDETACHED���ͷ���Դ*/
    else if(EMM_ESM_ATTACH_STATUS_DETACHED == ulEstRst)
    {
        /*����ӳ��ͷŷǽ������ض�ʱ�����ڣ���ֹͣ*/
        NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);

        /*EMMע��ʧ�ܻ�ȥע�ᣬ�ͷ���Դ*/
        NAS_ESM_RcvEmmDetachMsg();
    }
    else if (EMM_ESM_ATTACH_STATUS_EMC_ATTACHING == ulEstRst)
    {
        /* �ɽ���PDN���ӵ���EMM��TAU/Service/Attachʧ�ܣ��Һ�����Ҫ���н���ע�ᣬ
         * ESM�������ע���������Դ
         */
        NAS_ESM_ClearEsmResoureWhenEstingEmcPdn();
    }
    else
    {
        /*bsun ��鶯̬����������*/
        NAS_ESM_NORM_LOG("NAS_ESM_RcvEsmEmmStatusInd:NORM:UE re-entry Sevice NW!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStatusInd_ENUM, 1);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEmmDetachMsg
 Description     : SM�յ�EMMע��ʧ�ܻ�ȥע����Ϣ���ظ�APP��Ϣ���ͷű�����Դ
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing      2008-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEmmDetachMsg( VOS_VOID )
{
    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEmmDetachMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEmmDetachMsg_ENUM, LNAS_ENTRY);

    /* ֪ͨRABM�����Դ */
    NAS_ESM_SndEsmRabmRelIndMsg();


    /*����Դ*/
    NAS_ESM_ClearEsmResource();
}
/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmSuspendRsp
 Description     : ESMģ��ظ�ID_EMM_ESM_SUSPEND_RSP��Ϣ
 Input           : EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmSuspendRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    EMM_ESM_SUSPEND_RSP_STRU           *pstEsmEmmSuspendRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstEsmEmmSuspendRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEsmEmmSuspendRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmSuspendRsp:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmSuspendRsp_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pstEsmEmmSuspendRsp), 0, NAS_ESM_GET_MSG_LENGTH(pstEsmEmmSuspendRsp));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEsmEmmSuspendRsp, ID_EMM_ESM_SUSPEND_RSP);

    /*��д��Ӧ���*/
    pstEsmEmmSuspendRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEsmEmmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmResumeRsp
 Description     : ESMģ��ظ�ID_EMM_ESM_RESUME_RSP��Ϣ
 Input           : EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmResumeRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    EMM_ESM_RESUME_RSP_STRU            *pstEsmEmmResumeRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstEsmEmmResumeRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEsmEmmResumeRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmResumeRsp:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmResumeRsp_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pstEsmEmmResumeRsp), 0, NAS_ESM_GET_MSG_LENGTH(pstEsmEmmResumeRsp));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEsmEmmResumeRsp, ID_EMM_ESM_RESUME_RSP);

    /*��д��Ӧ���*/
    pstEsmEmmResumeRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEsmEmmResumeRsp);
}
VOS_VOID NAS_ESM_SndEsmEmmBearerStatusReqMsg(
                    EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32 enBearerCntxtChangeMod)
{
    VOS_UINT32                  ulCnt                       = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    EMM_ESM_BEARER_STATUS_REQ_STRU *pSmEmmBearStatusReqMsg   = VOS_NULL_PTR;

    /*�ҳ��Ѽ�����أ�����¼��ID*/
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        /*�˳����Ѽ���*/
        if( NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulCnt) )
        {
            /*�����Ѽ������ID,׼�����͸�RABM*/
            aulEpsbId[ulEpsbIdNum++] = ulCnt;
        }
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmEmmBearStatusReqMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_STATUS_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmBearStatusReqMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmBearerStatusReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmBearerStatusReqMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pSmEmmBearStatusReqMsg), 0, \
               NAS_ESM_GET_MSG_LENGTH(pSmEmmBearStatusReqMsg));

    /*�˴��޸ĳ��������ĵķ�ʽ*/
    pSmEmmBearStatusReqMsg->enBearerCntxtMod = enBearerCntxtChangeMod;

    /*��ulEpsbIdNum��pulEpsbId����pSmEmmBearStatusReqMsg*/
    pSmEmmBearStatusReqMsg->ulEpsIdNum = ulEpsbIdNum;
    NAS_ESM_MEM_CPY((VOS_UINT8*)pSmEmmBearStatusReqMsg->aulEsmEpsId, (VOS_UINT8*)aulEpsbId,
               (pSmEmmBearStatusReqMsg->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��д��ǰ�Ƿ��н���PDN����*/
    pSmEmmBearStatusReqMsg->ulExistEmcPdnFlag = NAS_ESM_HasExistedEmergencyPdn();

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmBearStatusReqMsg,ID_EMM_ESM_BEARER_STATUS_REQ);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmBearStatusReqMsg);

}
VOS_VOID NAS_ESM_SndEsmEmmPdnConRspMsg( EMM_ESM_PDN_CON_RSLT_ENUM_UINT32        ulRst,
                                                          VOS_UINT32 ulLength, const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength       = NAS_ESM_NULL;
    EMM_ESM_PDN_CON_RSP_STRU           *pSmEmmPdnConRsp   = VOS_NULL_PTR;

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ䣬������Ϣͷ��*/
    /* lint -e831 */
    if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmPdnConRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_RSP_STRU) + ulTmpLength);
    }
    /* lint +e831 */
    else/*�������С��ESM_MIN_SND_MSG_LEN������Ŀռ����ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmPdnConRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_RSP_STRU));
    }


    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmEmmPdnConRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmPdnConRspMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmPdnConRspMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmEmmPdnConRsp), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConRsp));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmPdnConRsp,ID_EMM_ESM_PDN_CON_RSP);

    /*��д��Ӧ���*/
    pSmEmmPdnConRsp->ulRst = ulRst;

    /*�����Ӧ���Ϊ�ɹ�����д�տ���Ϣ*/

    if( EMM_ESM_PDN_CON_RSLT_SUCC == ulRst )
    {
        /*��д�տ���Ϣͷ����*/
        pSmEmmPdnConRsp->stEsmMsg.ulEsmMsgSize = ulLength;

        /*���տ���Ϣ��ŵ�EMM_ESM_PDN_CON_RSP_STRU�ṹ��*/
        /*lint -e669*/
        NAS_ESM_MEM_CPY(pSmEmmPdnConRsp->stEsmMsg.aucEsmMsg, pucSendMsg, ulLength);/*lint !e669*/
        /*lint +e669*/
    }


    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmPdnConRsp);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmEstReqMsg
 Description     : �������пտ���Ϣ������MM����ע��
 Input           : VOS_UINT32 ulLength
                   VOS_UINT8 *pucSendMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-28  Draft Enact

*****************************************************************************/

/*lint -e669*/
/*lint -e831*/
VOS_VOID NAS_ESM_SndEsmEmmEstReqMsg(VOS_UINT32 ulOpId,
                                      VOS_UINT8  ucIsEmcPdnType,
                                      VOS_UINT32 ulLength,
                                      const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_EST_REQ_STRU               *pSmEmmEstReq        = VOS_NULL_PTR;

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmEstReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmEstReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmEstReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_EST_REQ_STRU) + ulTmpLength);
    }
    else/*�������С��ESM_MIN_SND_MSG_LEN������Ŀռ����ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmEstReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_EST_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmEmmEstReq)
    {
         /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmEstReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmEstReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmEmmEstReq), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmEstReq));

    /*��д�տ���Ϣͷ����*/
    pSmEmmEstReq->stEsmMsg.ulEsmMsgSize    = ulLength;

    /*���տ���Ϣ��ŵ�EMM_ESM_EST_REQ_STRU�ṹ��*/
    /*lint -e669*/
    NAS_ESM_MEM_CPY(pSmEmmEstReq->stEsmMsg.aucEsmMsg, pucSendMsg, ulLength);
    /*lint +e669*/

    /*��д�Ƿ��ǽ���PDN������������*/
    pSmEmmEstReq->ulIsEmcType = ucIsEmcPdnType;

    /*��дOpId*/
    pSmEmmEstReq->ulOpId = ulOpId;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmEstReq,ID_EMM_ESM_EST_REQ);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmEstReq);

}
/*lint +e831*/
/*lint +e669*/


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmPdnConSuccReqMsg
 Description     : ATTACH�����У�ESM����ȱʡ���سɹ���
                   ��EMM����EMM_ESM_PDN_CON_SUCC_REQ_STRU��Ϣ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndEsmEmmPdnConSuccReqMsg
(
     VOS_UINT32                         ulLength,
     const VOS_UINT8                   *pucSendMsg
)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_PDN_CON_SUCC_REQ_STRU      *pSmEmmPdnConSucc    = VOS_NULL_PTR;

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmPdnConSuccReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmPdnConSuccReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    else if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmPdnConSucc = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_SUCC_REQ_STRU) + ulTmpLength);
    }
    else/*�������С��ESM_MIN_SND_MSG_LEN������Ŀռ����ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmPdnConSucc = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_SUCC_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmEmmPdnConSucc)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmPdnConSuccReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmPdnConSuccReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmEmmPdnConSucc), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConSucc));

    /*��д�տ���Ϣͷ����*/
    pSmEmmPdnConSucc->stEsmMsg.ulEsmMsgSize = ulLength;

    /*���տ���Ϣ��ŵ�EMM_ESM_DATA_REQ_STRU�ṹ��*/
    /*lint -e669 */
    NAS_ESM_MEM_CPY(pSmEmmPdnConSucc->stEsmMsg.aucEsmMsg, pucSendMsg, ulLength);/*lint !e669 !e670*/
    /*lint +e669*/

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmPdnConSucc,ID_EMM_ESM_PDN_CON_SUCC_REQ);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmPdnConSucc);

}


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmDataReqMsg
 Description     : ��MM����DATA_REQ��Ϣ��Я�����пտ���Ϣ
 Input           : VOS_UINT32 ulLength
                   VOS_UINT8 *pucSendMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndEsmEmmDataReqMsg( VOS_UINT32 ulOpId,
                                       VOS_UINT8 ulIsEmcPdnType,
                                       VOS_UINT32 ulLength,
                                       const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pSmEmmDataReq       = VOS_NULL_PTR;

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmDataReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmDataReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    else if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmDataReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_DATA_REQ_STRU) + ulTmpLength);
    }
    else/*�������С��ESM_MIN_SND_MSG_LEN������Ŀռ����ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmDataReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_DATA_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmEmmDataReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmDataReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmDataReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmEmmDataReq), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmDataReq));

    /*��д�տ���Ϣͷ����*/
    pSmEmmDataReq->stEsmMsg.ulEsmMsgSize = ulLength;

    /*���տ���Ϣ��ŵ�EMM_ESM_DATA_REQ_STRU�ṹ��*/
    /*lint -e669*/
    NAS_ESM_MEM_CPY(pSmEmmDataReq->stEsmMsg.aucEsmMsg, pucSendMsg, ulLength);/*lint !e669 !e670*/
    /*lint +e669*/

    /*��д�Ƿ��ǽ���PDN������������*/
    pSmEmmDataReq->ulIsEmcType = ulIsEmcPdnType;

    /*��дOpId*/
    pSmEmmDataReq->ulOpId = ulOpId;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmDataReq,ID_EMM_ESM_DATA_REQ);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmDataReq);

}



/*leili modify for isr begin*/

VOS_VOID NAS_ESM_SndEsmEmmBearerModifyReq( VOS_UINT32 ulEpsId)
{
    EMM_ESM_BEARER_MODIFY_REQ_STRU  *pSmEmmBearModReq   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmEmmBearModReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_MODIFY_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmBearModReq )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmBearerModifyReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmBearerModifyReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pSmEmmBearModReq), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmBearModReq));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmBearModReq,ID_EMM_ESM_BEARER_MODIFY_REQ);

    pSmEmmBearModReq->ulEpsId = ulEpsId;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmBearModReq);

}
/*leili modify for isr end*/


VOS_VOID NAS_ESM_SndEsmEmmRelReqMsg( VOS_VOID )
{
    EMM_ESM_REL_REQ_STRU  *pSmEmmRelReq   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmEmmRelReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_REL_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmRelReq )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmRelReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmRelReqMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pSmEmmRelReq), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmRelReq));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmRelReq,ID_EMM_ESM_REL_REQ);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmRelReq);

}
VOS_VOID  NAS_ESM_ClearStateTable( VOS_UINT32 ulAppErrType, VOS_UINT32 ulKeepEmc )
{
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG2("NAS_ESM_ClearStateTable is entered.", ulAppErrType, ulKeepEmc);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_ClearStateTable_ENUM, LNAS_ENTRY, ulAppErrType, ulKeepEmc);

    /*����״̬�������APP��Ϣ����ظ�APP*/
    for( ulStateTblId = 0; ulStateTblId < NAS_ESM_MAX_STATETBL_NUM; ulStateTblId++ )
    {
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);

        /*����������������ض�Ӧ�Ķ�̬�������������*/
        if ((NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType) &&
            (PS_TRUE == ulKeepEmc))
        {
            /* lihong00150010 emergency tau&service begin */
            NAS_ESM_INFO_LOG("NAS_ESM_ClearStateTable:stop 3482");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearStateTable_ENUM, 1);

            /* ����ǽ���PDN����TAU����SERVICE��ʧ�ܺ���Ҫ�������ע��ĳ�����
               ��Ҫֹͣ3482��ʱ�����������ע�������3482���ܳ�ʱ */
            NAS_ESM_TimerStop(ulStateTblId, TI_NAS_ESM_T3482);
            /* lihong00150010 emergency tau&service ends */
            continue;
        }

        /* �����״̬�����APP��Ϣ��¼�����ݼ�¼�ظ���Ϣ*/
        if( NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord )
        {
            /*ȡ���˳����м�¼��APP��Ϣ����*/
            enAppMsgType = pstStateAddr->stAppMsgRecord.enAppMsgType;

            /*��������¼����Ϣ���ͻظ���Ϣ*/
            switch( enAppMsgType )
            {
                /*�����ID_APP_ESM_PDP_SETUP_REQ*/

                case ID_APP_ESM_PDP_SETUP_REQ:
                    /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/

                    NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(    ulStateTblId, \
                                                            ulAppErrType);
                    break;

                case ID_APP_ESM_PDP_RELEASE_REQ:
                    if (APP_ERR_SM_SUSPENDED == ulAppErrType)
                    {
                        /*��APP����ID_APP_ESM_PDP_RELEASE_CNF(ʧ��)��Ϣ*/
                        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblId, ulAppErrType);
                    }
                    else
                    {
                        /*��APP����ID_APP_ESM_PDP_RELEASE_CNF(�ɹ�)��Ϣ*/
                        NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(ulStateTblId);
                    }
                    break;

                case ID_APP_ESM_PDP_MODIFY_REQ:
                    /*��APP����ID_APP_ESM_PDP_MODIFY_CNF(ʧ��)��Ϣ*/
                    NAS_ESM_SndEsmAppSdfModCnfFailMsg(  ulStateTblId, \
                                                        ulAppErrType);
                    break;

                case ID_APP_ESM_NDISCONN_REQ:
                    /*��APP����ID_APP_ESM_NDISCONN_CNF(ʧ��)��Ϣ*/
                    NAS_ESM_LOG1("NAS_ESM_ClearStateTable:ERROR =", ulAppErrType);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ClearStateTable_ENUM, LNAS_ERROR, ulAppErrType);
                    NAS_ESM_SndEsmAppNdisConnCnfFailMsg(    ulStateTblId, \
                                                            ulAppErrType);
                    break;

                default:
                    break;
            }
        }

        NAS_ESM_RelStateTblResource(ulStateTblId);
    }

}


EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32 NAS_ESM_IsUpSingnalPending( VOS_VOID )
{
    VOS_UINT32                          ulStateTblIndex = NAS_ESM_NULL;
    VOS_UINT32                          ulTimerMaxExpTimer = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU                 *pstTimerInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, LNAS_ENTRY);

    /* �ж��Ƿ��������ڵȴ�������Ӧ*/
    for (ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++)
    {
        if (NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING
                == NAS_ESM_GetProcTransState(ulStateTblIndex))
        {
            /* �жϸ����̶�Ӧ��ʱ�ĳ�ʱ����*/
            pstTimerInfo = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

            /* �ж����̶�Ӧ��ʱ��û�����У���ʾ����*/
            if(VOS_NULL_PTR == pstTimerInfo->hTimer)
            {
                NAS_ESM_WARN_LOG("NAS_ESM_IsUpSingnalPending:warn: Timer not running.");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsUpSingnalPending_ENUM, LNAS_TIMER_STOP);
                continue;
            }

            /* ��ȡ���̶�Ӧ��ʱ�������ʱ����*/
            ulTimerMaxExpTimer = NAS_ESM_GetTimerMaxExpNum(pstTimerInfo->enPara);

            /* �����ʱ����С����������1�����ش���������������*/
            if((pstTimerInfo->ucExpireTimes) < (ulTimerMaxExpTimer-1))
            {
                NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:Uplink singnal pending.");
                TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 1);
                return EMM_ESM_UP_SINGNAL_PENDING;
            }
            else
            {
                /*��ʱ����ʱ�����Ѿ�������������1������Ϊ������������*/
                NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:ExpireTimex >= Max-1");
                TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 2);
                continue;
            }
        }
    }

    NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:no uplink signal pending.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 3);
    return EMM_ESM_NO_UP_SINGNAL_PENDING;
}

VOS_UINT32 NAS_ESM_GetRegistCid(VOS_VOID)
{
    VOS_UINT32                          ulCur;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulEhrpdCid;

    /* ������ڼ�¼��EHRPD������Ϣ����Ҫ���ȼ���Ƿ��Ѿ���������ע���CID */
    if (0 < NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachCidInEhrpdEntity(&ulEhrpdCid))
        {
            return ulEhrpdCid;
        }
    }
    #endif

    /* �����ж�CID0�Ƿ�Ϊȱʡ���� */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_NULL);
    if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
    {
       return NAS_ESM_NULL;
    }

    /* ��CID11-CID1Ѱ��ȱʡ�������͵�CID */
    for (ulCur = 1; ulCur < NAS_ESM_CID_NV_NUM; ulCur++ )
    {
       pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

       if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
       {
           return ulCur;
       }
    }

    /* ���֮ǰ������CID�����������������CID12-CID20Ѱ��ȱʡ�������͵�CID */
    for (ulCur = NAS_ESM_CID_NV_NUM; ulCur < NAS_ESM_MAX_UE_CONTRUL_CID_NUM; ulCur++ )
    {
       pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

       if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
       {
           return ulCur;
       }
    }

    return NAS_ESM_ILL_CID;
}


VOS_UINT32 NAS_ESM_ValidCidAttachBearerReest(VOS_UINT32 ulCid)
{
    VOS_UINT32 ulEpsbId = 0;
    VOS_UINT32 ulStateTblId = 0;
    VOS_UINT32 ulResult = PS_FALSE;

    if (NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid, &ulEpsbId))
    {
        if (NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCid, &ulStateTblId))
        {
            ulResult = PS_TRUE;
        }
    }
    else
    {
        if (NAS_ESM_BEARER_STATE_INACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
        {
            ulResult = PS_TRUE;
        }
    }

    return ulResult;
}


VOS_VOID NAS_ESM_ReestablishAttachBearer( VOS_VOID )
{
     VOS_UINT32                          ulPti               = NAS_ESM_NULL;
     VOS_UINT32                          ulRegCId            = NAS_ESM_NULL;
     VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
     VOS_UINT32                          ulCur               = NAS_ESM_NULL;
     VOS_UINT32                          ulSdfNum            = NAS_ESM_NULL;
     NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
     APP_ESM_SDF_PARA_STRU              *pstAppSdfPara       = VOS_NULL_PTR;
     NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
     NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
     NAS_ESM_PDP_MANAGE_INFO_STRU       *pEpsbManageInfo     = VOS_NULL_PTR;


    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ReestablishAttachBearer is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_EMM_LTE_SUSPEND);
        return;
    }

    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ReestablishAttachBearer: ESM status is not ATTACHED !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_STATUS_ERROR);
        return;
    }

    pstAppSdfPara = NAS_ESM_MEM_ALLOC(sizeof(APP_ESM_SDF_PARA_STRU));

    if (VOS_NULL_PTR == pstAppSdfPara)
    {
         /*��ӡ���Ϸ���Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* ��һ��ȡ12��NV���� */
    for (ulCur = NAS_ESM_MIN_CID; ulCur < NAS_ESM_CID_NV_NUM; ulCur++)
    {
        pstAppSdfPara->ulCId = ulCur;
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        if (APP_FAILURE == NAS_ESM_GetSdfPara(&ulSdfNum, pstAppSdfPara))
        {
            continue;
        }

        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);
        NAS_ESM_MEM_CPY(pstSdfPara, pstAppSdfPara, sizeof(APP_ESM_SDF_PARA_STRU));
    }

    NAS_ESM_MEM_FREE(pstAppSdfPara);

    /* ��APP��ȡ���ع���ģʽ���������ȡ�Զ�����ģʽ */
    pEpsbManageInfo = NAS_ESM_GetBearerManageInfoAddr();
    if (APP_FAILURE == NAS_ESM_GetPdpManageInfo(pEpsbManageInfo))
    {
        /*��ӡ������Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer:WARN: Fail to get PDP Manage Info from APP!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, 1);
        pEpsbManageInfo->enMode = APP_ESM_BEARER_MANAGE_MODE_AUTO;
        pEpsbManageInfo->enType = APP_ESM_BEARER_MANAGE_TYPE_ACCEPT;
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    /* ��ȡ����ע���CID�����ȼ�˳���ɸߵ���ΪCID0 > CID1-CID11 > CID12-CID20 */
    /* ���˸�����Ӫ����������, ��ҪGU NV��CID0��ʼ��Ϊר�����ͣ�CID11Ϊȱʡ����*/
    ulRegCId = NAS_ESM_GetRegistCid();
    /* add by yanglei 00307272 for KEY_INFO_REPORT3, 2015-08-19, begin */
    NAS_ESM_SndOmRegCidInfo(ulRegCId);
    /* add by yanglei 00307272 for KEY_INFO_REPORT3, 2015-08-19, end */
    if (NAS_ESM_ILL_CID == ulRegCId)
    {
        /*��ӡ���Ϸ���Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer: There is no default bearer type sdf");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, 2);
        return ;
    }

    NAS_ESM_LOG1("NAS_ESM_ReestablishAttachBearer:The cid of the found sdf is :", ulRegCId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_CID_IS, ulRegCId);

    /* ���CID�Ƿ����ע������ؽ������� */
    if (PS_FALSE == NAS_ESM_ValidCidAttachBearerReest(ulRegCId))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer: Invalid CID");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_CID_ERROR);
        return;
    }

    /*�ڶ�̬���У���ȡ���̱�ʶ*/
    if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(NAS_ESM_ATTACH_CID, &ulStateTblId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer:WARNING:insufficient resource!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, 4);
        return ;
    }

    /*����ѯ����ulRegCId����������CID0�У�����ע��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_ATTACH_CID);
    NAS_ESM_MEM_CPY(    pstSdfPara,
                        NAS_ESM_GetSdfParaAddr(ulRegCId),
                        sizeof(NAS_ESM_SDF_PARA_STRU));

    /*���ó�ʼ״̬*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType  = NAS_ESM_BEARER_TYPE_DEFAULT;

    /*����PTI,����洢��������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
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
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer:ERROR:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_FAIL);

        NAS_ESM_RelStateTblResource(ulStateTblId);
        return ;
    }

    /*��¼�տ���Ϣ����*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
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
    NAS_ESM_TimerStart(ulStateTblId,TI_NAS_ESM_T3482);

    /*ת��״̬*/
    NAS_ESM_SetProcTransState(ulStateTblId, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}
VOS_VOID NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd(VOS_VOID)
{
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, LNAS_ENTRY);

    if (PS_TRUE == NAS_ESM_HasExistedEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: existed emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 1);

        /*�����ǰ���Ѿ������Ľ���PDN���ӣ��������ͷ����зǽ���PDN����*/
        NAS_ESM_DeactAllNonEmcPdn();
    }
    else if (PS_TRUE == NAS_ESM_HasEstingEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: esting emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 2);

        /*�����ǰ�����ڽ����Ľ���PDN���ӣ����ӳ��ͷ����зǽ���PDN����*/
        NAS_ESM_TimerStart(0, TI_NAS_ESM_REL_NON_EMC_BEARER);
    }
    else
    {   /*�����ǰû�н���PDN����������*/
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: no emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 3);
    }

    return;
}
VOS_VOID NAS_ESM_RcvEsmEmmStartNotifyInd(VOS_VOID)
{
    NAS_BACKOFF_INIT_INFO_STRU          stInitPara;

    NAS_ESM_MEM_SET(&stInitPara, 0, sizeof(NAS_BACKOFF_INIT_INFO_STRU));

    if(NAS_ESM_SUCCESS != NAS_ESM_ReadUsimBackOffRpmPdpPara())
    {
        /* ����ʧ�ܣ�ֱ�ӳ�ʼ��BackOff�㷨 */
        stInitPara.bitOpSimFxFlag = NAS_ESM_OP_FALSE;
        NAS_BACKOFF_OperateInit(&stInitPara);
    }
    else
    {
        /* �����ɹ���������ʱ���ȿ��ظ���Ϣ,����������һ����β�ʹ�ã���0 */
        NAS_ESM_TimerStart(0, TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF);
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ������EHRPDʵ���ʼ�� */
    NAS_ESM_InitEhrpdEntity();
    #endif

    return;
}
VOS_VOID NAS_ESM_RcvEsmEmmPlmnChangeInd(VOS_VOID)
{
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32 enResetCause;

    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmPlmnChangeInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPlmnChangeInd_ENUM, LNAS_ENTRY);

    enResetCause = NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE;

    /* ��λBACKOFF�㷨 */
    NAS_BACKOFF_OperateReset(NAS_BACKOFF_NETRAT_LTE, &enResetCause);
    return;
}
VOS_VOID NAS_ESM_RcvEsmEmmStopNotifyInd(VOS_VOID)
{
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32 enResetCause;

    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmStopNotifyInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStopNotifyInd_ENUM, LNAS_ENTRY);

    enResetCause = NAS_BACKOFF_RESET_CAUSE_SWITCH_OFF;

    /* ��λBACKOFF�㷨 */
    NAS_BACKOFF_OperateReset(NAS_BACKOFF_NETRAT_LTE, &enResetCause);

    /* ��ձ���ԭ��ֵ#50��#51���б� */
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej50Info);
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej51Info);
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej66Info);

    pg_stNasEsmEntity->pstPdnRej50Info =  VOS_NULL_PTR;
    pg_stNasEsmEntity->pstPdnRej51Info =  VOS_NULL_PTR;
    pg_stNasEsmEntity->pstPdnRej66Info =  VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* �ػ����������EHRPD���ؼ�¼ */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();
    #endif

    return;
}
VOS_VOID NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(VOS_UINT32 ulOpId, VOS_UINT8 ucIsEmcPdnType)
{
    EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU *pSmEmmNotify      = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG2("NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg: enter", ulOpId, ucIsEmcPdnType);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg_ENUM, LNAS_ENTRY, ulOpId, ucIsEmcPdnType);

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    pSmEmmNotify= (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmEmmNotify)
    {
         /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmEmmNotify), 0, NAS_ESM_GET_MSG_LENGTH(pSmEmmNotify));

    /*��д�Ƿ��ǽ���PDN������������*/
    pSmEmmNotify->ulIsEmcType = ucIsEmcPdnType;

    /*��дOpId*/
    pSmEmmNotify->ulOpId = ulOpId;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmNotify, ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmEmmNotify);
}
/*lint +e961*/
/*lint +e960*/

#if (FEATURE_ON == FEATURE_PTM)

ESM_OM_ERRLOG_ID_ENUM_UINT16  NAS_ESM_CnCauseProc(VOS_UINT8 ucCnCause)
{
    ESM_OM_ERRLOG_ID_ENUM_UINT16   ulErrId = 0;
    VOS_UINT32 i;

    NAS_ESM_INFO_LOG("NAS_ESM_CnCauseProc!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CnCauseProc_ENUM, LNAS_ENTRY);

    for(i = 0; i < g_astEsmErrlogErrNum; i++)
    {
        if(ucCnCause == g_astEsmErrlogErrNoMap[i].ulEsmCnCasue)
        {
            ulErrId = g_astEsmErrlogErrNoMap[i].ulEsmErrId;
            break;
        }
    }
    if(g_astEsmErrlogErrNum == i)
    {
            ulErrId = ESM_OM_ERRLOG_CAUSE_OTHERS;
    }

    return ulErrId;
}


VOS_VOID NAS_ESM_SndEsmErrlogToEmm(
                 VOS_VOID     *pstEsmErrRslt,  VOS_UINT32   ulEsmErrLength)
{
    EMM_ESM_SAVE_ERRLOG_IND_STRU        *pstSaveEsmErrMsg = NAS_ESM_NULL;
    VOS_UINT32                          ulLength          = 0;

    NAS_ESM_NORM_LOG("NAS_ESM_SndEsmErrlogToEmm!!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmErrlogToEmm_ENUM, LNAS_ENTRY);

    /*������Ϣ�ĳ��ȷ���ռ�*/
    ulLength = sizeof(EMM_ESM_SAVE_ERRLOG_IND_STRU) + ulEsmErrLength - 4;

    pstSaveEsmErrMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(ulLength);
    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstSaveEsmErrMsg)
    {
         /*��ӡ�쳣��Ϣ*/
         NAS_ESM_ERR_LOG("NAS_ESM_SndEsmErrlogToEmm:ERROR:Alloc Msg fail!");
         TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmErrlogToEmm_ENUM, LNAS_NULL_PTR);
         return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(pstSaveEsmErrMsg, 0, ulLength);

    /*��дʵ�ʵ�esm errlog��Ϣͷ����*/
    pstSaveEsmErrMsg->stEmmEsmErrlog.ulEsmMsgSize = ulEsmErrLength;

    /*��дʵ��Ҫд�뻺������esm errlog����*/
    NAS_ESM_MEM_CPY(pstSaveEsmErrMsg->stEmmEsmErrlog.aucEsmMsg, pstEsmErrRslt, ulEsmErrLength);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstSaveEsmErrMsg, ID_EMM_ESM_SAVE_ERRLOG_IND);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstSaveEsmErrMsg);
}


VOS_VOID  NAS_ESM_PdnConFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_PDN_CONN_REJ_RESULT_EVENT_STRU            stEsmPdnConnFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_PdnConFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnConRejRecord_ENUM, LNAS_ENTRY);


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_PDN_CONN_REJ_RESULT_EVENT_STRU);

    PS_MEM_SET(&stEsmPdnConnFailRslt, 0x00, ulLength);

    /*���esm fail�쳣����ͷ*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmPdnConnFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmPdnConnFailRslt.enFailCause =
                    NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmPdnConnFailRslt.enEsmTimeout = enErrEsmTimeOut;

    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, Begin */
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmPdnConnFailRslt.stPositionInfo));
    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, End */

    /*����ESM errlog��Ϣ��EMM��Ϊ��ֹ�������´洢logʧ�ܣ���EMM����*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmPdnConnFailRslt, ulLength);
}


VOS_VOID  NAS_ESM_PdnDisconFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_PDN_DISCONN_REJ_RESULT_EVENT_STRU         stEsmPdnDisconFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;


    NAS_ESM_NORM_LOG("NAS_ESM_PdnDisconFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnDisconRejRecord_ENUM, LNAS_ENTRY);


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_PDN_DISCONN_REJ_RESULT_EVENT_STRU);

    PS_MEM_SET(&stEsmPdnDisconFailRslt, 0x00, ulLength);

    /*���esm fail�쳣����ͷ*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmPdnDisconFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmPdnDisconFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmPdnDisconFailRslt.enEsmTimeout = enErrEsmTimeOut;

    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, Begin */
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmPdnDisconFailRslt.stPositionInfo));
    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, End */

    /*����ESM errlog��Ϣ��EMM��Ϊ��ֹ�������´洢logʧ�ܣ���EMM����*/
     NAS_ESM_SndEsmErrlogToEmm(&stEsmPdnDisconFailRslt, ulLength);
}


VOS_VOID  NAS_ESM_ResModFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU             stEsmResModFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_ResModFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ResModRejRecord_ENUM, LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU);

    PS_MEM_SET(&stEsmResModFailRslt, 0x00, ulLength);

    /*���esm fail�쳣����ͷ*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmResModFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmResModFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmResModFailRslt.enEsmTimeout = enErrEsmTimeOut;

    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, Begin */
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmResModFailRslt.stPositionInfo));
    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, End */

    /*����ESM errlog��Ϣ��EMM��Ϊ��ֹ�������´洢logʧ�ܣ���EMM����*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmResModFailRslt, ulLength);
}


VOS_VOID  NAS_ESM_ResAllocFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU           stEsmResAllocFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_ResAllocFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ResAllocRejRecord_ENUM, LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU);

    PS_MEM_SET(&stEsmResAllocFailRslt, 0x00, ulLength);

    /*���esm fail�쳣����ͷ*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmResAllocFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmResAllocFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmResAllocFailRslt.enEsmTimeout = enErrEsmTimeOut;

    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, Begin */
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmResAllocFailRslt.stPositionInfo));
    /* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, End */

    /*����ESM errlog��Ϣ��EMM��Ϊ��ֹ�������´洢logʧ�ܣ���EMM����*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmResAllocFailRslt, ulLength);
}
#endif


/*lint -e960*/
NAS_ESM_STATE_INFO_STRU* NAS_ESM_FindMsgInStateTable(VOS_UINT32 ulEmmEsmOpId)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt = VOS_ERR;
    NAS_ESM_STATE_INFO_STRU             *pstStatTblnfo = VOS_NULL_PTR;

    /*��ȡ��̬����׵�ַ*/
    pstStatTblnfo = NAS_ESM_GetStateTblAddr(0);

    for (ulIndex = 0; ulIndex < NAS_ESM_MAX_STATETBL_NUM; ulIndex++)
    {
        if (ulEmmEsmOpId == pstStatTblnfo->stNwMsgRecord.ulOpId)
        {
            ulRslt = VOS_OK;
            break;
        }
        else
        {
            pstStatTblnfo++;
        }
    }

    if (VOS_ERR == ulRslt)
    {
        return VOS_NULL_PTR;
    }

    return pstStatTblnfo;
}
/*lint +e960*/

VOS_UINT32 NAS_ESM_IsExistAllFailStateTable(VOS_VOID)
{
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  = 0;
    VOS_UINT32                          ulHaveOneSuccOrSendingFlag = VOS_FALSE;

    for(ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++)
    {
        pstStateTblInfo = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if((NAS_ESM_BEARER_DATA_CNF_SENDING == pstStateTblInfo->enEsmBearerDataCnf)
            || (NAS_ESM_BEARER_DATA_CNF_SUCC == pstStateTblInfo->enEsmBearerDataCnf))
        {
            ulHaveOneSuccOrSendingFlag = VOS_TRUE;
            break;
        }
    }

    if(VOS_TRUE == ulHaveOneSuccOrSendingFlag)
    {
        return ESM_BEARER_STATUS_AT_LEAST_ONE_BEAER_RUNING;
    }
    else
    {
        return ESM_BEARER_STATUS_BESIDE_RUNING;
    }
}


/*lint -e961*/
VOS_VOID NAS_ESM_RcvEsmEmmDataCnf(const EMM_ESM_DATA_CNF_STRU   *pEmmEsmDataCnfMsg)
{
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;

    /*������*/
    if(VOS_NULL == pEmmEsmDataCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataCnf(ERR): Input is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmDataCnf_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_LOG2("NAS_ESM_RcvEsmEmmDataCnf: enBearerDataCnf, EmmEsmOpId:",
                    pEmmEsmDataCnfMsg->enDataCnfRst, pEmmEsmDataCnfMsg->ulEsmEmmOpId);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_RcvEsmEmmDataCnf_ENUM, 1, pEmmEsmDataCnfMsg->enDataCnfRst, pEmmEsmDataCnfMsg->ulEsmEmmOpId);

    /*����Emm��������OpIdȥ���Ҷ�Ӧ�Ķ�̬����*/
    pstStateTblInfo = NAS_ESM_FindMsgInStateTable(pEmmEsmDataCnfMsg->ulEsmEmmOpId);

    /*���³���״̬*/
    switch(pEmmEsmDataCnfMsg->enDataCnfRst)
    {
        case  EMM_ESM_SEND_RSLT_SUCCESS:

              /* ԭDSDSֻ��עPDN REQ����˴��ڶ�̬��Ŵ���EHRPD�����෴��ֻ��ע�������ACP����Ȼ�Ҳ�����̬�� */
              if (NAS_ESM_NULL != pstStateTblInfo)
              {
                  #if (FEATURE_ON == FEATURE_DSDS)
                  pstStateTblInfo->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SUCC;
                  #endif
              }
              else
              {
                  #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                  /* ���ͳɹ���EHRPDʵ����Դ�OPID���������⴦�� */
                  NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(pEmmEsmDataCnfMsg->ulEsmEmmOpId);
                  #endif
              }

              break;
        case  EMM_ESM_SEND_RSLT_EMM_DISCARD:
        case  EMM_ESM_SEND_RSLT_FAILURE_HO:
        case  EMM_ESM_SEND_RSLT_FAILURE_CONN_REL:
        case  EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
        case  EMM_ESM_SEND_RSLT_FAILURE_TXN:
        case  EMM_ESM_SEND_RSLT_FAILURE_RLF:
        case  EMM_ESM_SEND_RSLT_NORF:

              /* ԭDSDSֻ��עPDN REQ����˴��ڶ�̬��Ŵ���EHRPD�����෴��ֻ��ע�������ACP����Ȼ�Ҳ�����̬�� */
              if (NAS_ESM_NULL != pstStateTblInfo)
              {
                  #if (FEATURE_ON == FEATURE_DSDS)
                  pstStateTblInfo->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_FAIL;
                  #endif
              }
              else
              {
                  #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                  /* EHRPDʵ��Ҫ�����Ƿ���Ҫ�Է���ʧ�ܵĳ������д��� */
                  NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(pEmmEsmDataCnfMsg->ulEsmEmmOpId);
                  #endif
              }

              break;
        default:
              break;
    }

    if (NAS_ESM_NULL != pstStateTblInfo)
    {
        /*ͨ��������̬���Լ���������״̬�������ж������̬�������ٴ���һ����sending��succ״̬��
          ��ô������end session�� �����û��sending״̬�Լ�succ״̬�ĳ��أ�����������������
          1����ǰ���ض���FAIL�ġ� 2����ǰ����FAIL��NULL�����֮�����������������������ǰû�г���
          ����ʹ����Ƶ��Դ��
        */
        NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmDataCnf: IsRunning:", NAS_ESM_IsExistAllFailStateTable());
        if( ESM_BEARER_STATUS_BESIDE_RUNING == NAS_ESM_IsExistAllFailStateTable())
        {
            #if (FEATURE_ON == FEATURE_DSDS)
            NAS_ESM_SendEndSessionNotify();
            #endif
        }
    }
}
/*lint +e961*/

VOS_UINT32  NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl(
    VOS_UINT32                                   *pulStateTblId,
    VOS_UINT32                                    ulRegCid,
    EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32          enPdnReqType
)
{
    NAS_ESM_STATE_INFO_STRU                      *pstStateAddr = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU                        *pstSdfPara   = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                                    ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                *pstPdnEntity = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, LNAS_ENTRY);

    /* ����CL��ģ�汾��ͨ����ѯEHRPDʵ���¼��ȷ�ϣ��ҵ�Ҳ����Ϊhandover���� */

    /* ��ά�ɲ⣬�ϱ�HIDSʵ��״̬ */
    NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

    /* �����Ƿ���ڴ��ָ���EHRPD���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        /*�ڶ�̬���л�ȡ���̱�ʶ*/
        if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(ulRegCid, pulStateTblId))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl:CMDA insufficient resource!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, ESM_EHSM_STATETABLE_NOT_ENOUGH);

            /* �ظ�EMM ID_EMM_ESM_PDN_CON_RSP(FAIL) */
            NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);
            return NAS_ESM_FAILURE;
        }

        /* ���ö�̬���ʼ״̬ */
        pstStateAddr                     = NAS_ESM_GetStateTblAddr(*pulStateTblId);

        pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
        pstStateAddr->enBearerCntxtType  = NAS_ESM_BEARER_TYPE_DEFAULT;
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

        /* ��PDNʵ���е���Ϣ���õ�SDF�У���������ֱ��ʹ�ô�ע��CID��SDF���еĲ��� */
        pstPdnEntity                     = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
        pstSdfPara                       = NAS_ESM_GetSdfParaAddr(ulRegCid);
        NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

        /* ����ʵ�����PDN������δ�յ�������Ӧ̬ */
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ATTACH_PDN_REQ_NOT_RCV_CN_RSP);

        return NAS_ESM_SUCCESS;
    }
    #endif
    /* �������� */

    /*�ڶ�̬���л�ȡ���̱�ʶ*/
    if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(NAS_ESM_ATTACH_CID, pulStateTblId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl:insufficient resource!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, ESM_STATETABLE_NOT_ENOUGH);

        /* �ظ�EMM ID_EMM_ESM_PDN_CON_RSP(FAIL) */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);
        return NAS_ESM_FAILURE;
    }

    /* ���ö�̬���ʼ״̬ */
    pstStateAddr                         = NAS_ESM_GetStateTblAddr(*pulStateTblId);
    pstStateAddr->enBearerCntxtState     = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType      = NAS_ESM_BEARER_TYPE_DEFAULT;

    /* VIAƴƬ�汾��handover���ͣ���EMM��������Ϣ���п��� */
    if(EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER == enPdnReqType)
    {
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_HANDOVER;
    }
    else
    {
        /* ������������initial���� */
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_INITIAL;
    }

    /*�������ulRegCid��SDF����������CID0�У�����ע��*/
    pstSdfPara                           = NAS_ESM_GetSdfParaAddr(NAS_ESM_ATTACH_CID);
    NAS_ESM_MEM_CPY(pstSdfPara,
                    NAS_ESM_GetSdfParaAddr(ulRegCid),
                    sizeof(NAS_ESM_SDF_PARA_STRU));

    return NAS_ESM_SUCCESS;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID  NAS_ESM_RcvEsmEmmClearClBearerNotify(VOS_VOID)
{
    /* ����ESM��������ģ */

    /* EMM֪ͨ���EHRPD���ص�ԭ��������յ�MMC��DETACH�����࿨��Чԭ��ֵREJ��
    ��ȨREJ��CN MT DETACH(not-reattach)���������ֳ���������Ҫǿ����APS�ϱ�����
    �ָ�ʧ�ܣ��������������쳣�����ڱȽ�������������ʹ���APS�ϱ�Ҳ���������� */

    /* ���EHRPDʵ�岻���Ѿ��յ������һ��ȱʡ���ؼ������� */
    if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ != NAS_ESM_GET_EHRPD_ENTITY_STATE())
    {
        /* ֪ͨEHSM������г��� */
        NAS_ESM_SndEhsmClearAllBearerNotifyMsg();

        /* ǿ������EHRPDʵ��������յ������һ��ȱʡ��������Ŀ���Ǻ��������ʱ���APS�ϱ��ָ�ʧ�� */
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ);
    }

    /* �������EHRPD���ؼ�¼���ϱ��ָ�ʧ�� */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    return;
}
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmEmmMsgProc.c */
