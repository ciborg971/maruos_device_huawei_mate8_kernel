

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMTIMERMSGPROC_C
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



/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID NAS_ESM_TimerMsgDistr(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulIndex         = NAS_ESM_NULL;
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType     = TI_NAS_ESM_TIMER_PARA_BUTT;
    NAS_BACKOFF_INIT_INFO_STRU          stInitPara;

    NAS_ESM_INFO_LOG("NAS_ESM_TimerMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_TimerMsgDistr_ENUM, LNAS_ENTRY);

    /*����Ϣ��ȡ��״̬��ID*/
    ulIndex = PS_GET_REL_TIMER_NAME(pRcvMsg);

    enTimerType = (NAS_ESM_TIMER_PARA_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pRcvMsg);

    /*�жϳ���ulStateTblIndex�Ϸ���*/
    if (PS_FALSE == NAS_ESM_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_TimerMsgDistr:WARNING:Timer->SM ,Invalid Timer Name or Para !");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_TimerMsgDistr_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*��ʱ����ʱ����*/
    switch(enTimerType)
    {
        case TI_NAS_ESM_T3482:
            NAS_ESM_ProcTimerMsgT3482Exp(pRcvMsg);
            break;
        case TI_NAS_ESM_T3492:
            NAS_ESM_ProcTimerMsgT3492Exp(pRcvMsg);
            break;
        case TI_NAS_ESM_T3480:
            NAS_ESM_ProcTimerMsgT3480Exp(pRcvMsg);
            break;
        case TI_NAS_ESM_T3481:
            NAS_ESM_ProcTimerMsgT3481Exp(pRcvMsg);
            break;
        case TI_NAS_ESM_WAIT_APP_CNF:
            NAS_ESM_ProcTimerMsgWaitAppCnfExp(pRcvMsg);
            break;
        case TI_NAS_ESM_WAIT_PTI_INVALID:
            NAS_ESM_ProcTimerMsgWaitPtiInvaidExp(pRcvMsg);
            break;
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
            NAS_ESM_ProcTimerMsgAttachBearerReestExp(pRcvMsg);
            break;
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
            NAS_ESM_ProcTimerMsgDeferRelNonEmcExp(pRcvMsg);
            break;

        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:
        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:
        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:
            /* Back-off�㷨�ͷ���ʱ����ʱ���������⴦�� */
            break;

        case TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF:

            /* ������ʱ */
            NAS_ESM_MEM_SET(&stInitPara, 0, sizeof(NAS_BACKOFF_INIT_INFO_STRU));
            stInitPara.bitOpSimFxFlag = NAS_ESM_OP_FALSE;
            NAS_BACKOFF_OperateInit(&stInitPara);
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC:

            /* ��EHRPD���ػָ�ʧ�ܵĴ��� */
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);

            break;
        #endif

        default:
            NAS_ESM_WARN_LOG("NAS_ESM_TimerMsgDistr:WARNING:Illegal Timer Type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_TimerMsgDistr_ENUM, LNAS_ERROR);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcTimerMsgWaitPtiInvaidExp
 Description     : �ȴ�PTIʧЧ��ʱ����ʱ����
 Input           : pMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-2  Draft Enact

*****************************************************************************/
/*lint -e961*/
VOS_VOID NAS_ESM_ProcTimerMsgWaitPtiInvaidExp(const VOS_VOID * pMsg)
{
    VOS_UINT32                          ulEsmBuffIndex      = NAS_ESM_NULL;
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstPtiBuffItem      = VOS_NULL_PTR;

    /* ��ȡ��Ϣ�а�����ESM�����¼������ */
    ulEsmBuffIndex = PS_GET_REL_TIMER_NAME(pMsg);

    /* ��ȡ�����¼ */
    pstPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                            NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulEsmBuffIndex);

    if (pstPtiBuffItem == VOS_NULL_PTR)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgWaitPtiInvaidExp:WARN:Get buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgWaitPtiInvaidExp_ENUM, 1);
        return ;
    }

    NAS_ESM_INFO_LOG2("NAS_ESM_ProcTimerMsgWaitPtiInvaidExp:NORM:PTI is deleted from Esm Buffer!",
                       pstPtiBuffItem->ucPti, ulEsmBuffIndex);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_ProcTimerMsgWaitPtiInvaidExp_ENUM, 2, pstPtiBuffItem->ucPti, ulEsmBuffIndex);

    /* ��������¼ */
    NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulEsmBuffIndex);
}


VOS_VOID    NAS_ESM_ProcTimerMsgT3482Exp(const VOS_VOID * pMsg)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU                 *pTimer3482          = VOS_NULL_PTR;
    VOS_UINT32                          ulErrorCode         = APP_ERR_TIME_OUT;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

	#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
	#endif

    NAS_BACKOFF_MAINTAIN_PARA_STRU      stMaintainPara;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgT3482Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgT3482Exp_ENUM, LNAS_ENTRY);

    /*��ȡ��Ϣ�а�����״̬��StateTblIndex*/
    ulStateTblIndex = PS_GET_REL_TIMER_NAME(pMsg);
    pstStateAddr    = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstSdfPara      = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* ����APN������Back-off�㷨����ά�� */
    if(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {
        NAS_ESM_MEM_SET(&stMaintainPara, 0, sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU));
        NAS_ESM_MEM_CPY(&stMaintainPara.stApnInfo,
                          &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        stMaintainPara.enPdpResult = NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP;
        stMaintainPara.ucCnCause   = NAS_BACKOFF_PDP_CAUSE_NULL;
        NAS_BACKOFF_OperateMaintain(NAS_BACKOFF_NETRAT_LTE, &stMaintainPara);
    }

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgT3482Exp: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3482Exp_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_PdnConFailRecord(VOS_NULL_PTR, ESM_OM_ERRLOG_TIMEOUT_T3482);
    #endif
    /*������Ϣ��Ӧ��ulStateTblIndex,��ȡ������Ķ�ʱ��T3482*/
    pTimer3482 = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

    /*��ʱ����++*/
    pTimer3482->ucExpireTimes++;

    /* ���δ��������������APN����Back-off�㷨�����ж�����������㷢��������
       ֱ�����ó�ʱ����Ϊ��󣬴�����ΪBack-off�㷨��������                 */
    if((TI_NAS_ESM_T3482_TIMER_MAX_EXP_NUM > pTimer3482->ucExpireTimes)
        &&(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_SET(&stJudgmentPara, 0, sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
        NAS_ESM_MEM_CPY(&stJudgmentPara,
                          &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
        {
            pTimer3482->ucExpireTimes = TI_NAS_ESM_T3482_TIMER_MAX_EXP_NUM;
            ulErrorCode = APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED;
        }
    }

    /*�����ǰ��ʱ����ʱ����С��NAS_ESM_MAX_TIMER_EXPIRE_TIMES��*/
    if(pTimer3482->ucExpireTimes < TI_NAS_ESM_T3482_TIMER_MAX_EXP_NUM)
    {
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú���:SM��MM������Ϣ:NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /*����������ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

        /*�ϱ��տ���Ϣ*/
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                                   pstStateAddr->stNwMsgRecord.ulMsgLength,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                   ESM_PDN_CONNECT_REQ);
        return;
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {
        /* �����EHRPD���ػָ��ĳ�ʱ�������� */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(&pstSdfPara->stApnInfo, &ulIndex))
        {
            /* EHRPD���ػָ�ʧ�ܴ��� */
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);

            /*�ͷ�״̬����Դ*/
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            return;
        }
    }
    #endif

    if(ID_APP_ESM_NDISCONN_REQ == NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) )
    {
        /*���ú���:����ȷ����Ϣ֪ͨAPP�����γ�����Դ�������ʧ��*/
        NAS_ESM_LOG1("NAS_ESM_ProcTimerMsgT3482Exp:ERROR =", ulErrorCode);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcTimerMsgT3482Exp_ENUM, 1, ulErrorCode);
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, ulErrorCode);
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgT3482Exp:WARNING:ExpireTimes exceed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3482Exp_ENUM, 2);

        /*��APP�ظ���Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                                            ulErrorCode);
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}
/*lint +e961*/

VOS_VOID    NAS_ESM_ProcTimerMsgT3492Exp(const VOS_VOID * pMsg)
{
    VOS_UINT32                          ulStateTblIndex  = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU                 *pTimer3492       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgT3492Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgT3492Exp_ENUM, LNAS_ENTRY);

    /*��ȡ��Ϣ�а�����״̬��StateTblIndex*/
    ulStateTblIndex = PS_GET_REL_TIMER_NAME(pMsg);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgT3492Exp: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3492Exp_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_PdnDisconFailRecord(VOS_NULL_PTR, ESM_OM_ERRLOG_TIMEOUT_T3492);
    #endif
    /*������Ϣ��Ӧ��ulStateTblIndex,��ȡ������Ķ�ʱ��*/
    pTimer3492 = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

    /*��ʱ����++*/
    pTimer3492->ucExpireTimes++;

    /*�����ǰ��ʱ����ʱ����С��NAS_ESM_MAX_TIMER_EXPIRE_TIMES��*/
    if(pTimer3492->ucExpireTimes < TI_NAS_ESM_T3492_TIMER_MAX_EXP_NUM)
    {
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú���:SM��MM������Ϣ:NAS_ESMCN_PDN_DISCONNECT_REQ*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /*����������ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3492);

        /*�ϱ��տ���Ϣ*/
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                                   pstStateAddr->stNwMsgRecord.ulMsgLength,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                   ESM_PDN_DISCONNECT_REQ);
        return;

    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttingBInactPPendMsgT3492Exp:WARNING:ExpireTimes exceed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3492Exp_ENUM, 1);

        /*�����ͷ�ȱʡ������Դ,��APP�ظ��ͷųɹ���Ϣ*/
        NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

        /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_LOCAL);
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}


VOS_VOID   NAS_ESM_ProcTimerMsgT3480Exp
(
    const VOS_VOID * pMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulErrorCode         = APP_ERR_TIME_OUT;
    NAS_ESM_TIMER_STRU                 *pTimer3480          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgT3480Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgT3480Exp_ENUM, LNAS_ENTRY);

    /*��ȡ��Ϣ�а�����״̬��StateTblIndex*/
    ulStateTblIndex = PS_GET_REL_TIMER_NAME(pMsg);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgT3480Exp: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3480Exp_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_ResAllocFailRecord(VOS_NULL_PTR, ESM_OM_ERRLOG_TIMEOUT_T3480);
    #endif
    /*������Ϣ��Ӧ��ulStateTblIndex,��ȡ������Ķ�ʱ��*/
    pTimer3480 = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

    /*��ʱ����++*/
    pTimer3480->ucExpireTimes++;

    /*�����ǰ��ʱ����ʱ����С��NAS_ESM_MAX_TIMER_EXPIRE_TIMES��*/
    if(pTimer3480->ucExpireTimes < TI_NAS_ESM_T3480_TIMER_MAX_EXP_NUM)
    {
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú���:SM��MM������Ϣ:NAS_ESMCN_BEARER_RES_MOD_REQ*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /*����������ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3480);

        /*�ϱ��տ���Ϣ*/
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                                   pstStateAddr->stNwMsgRecord.ulMsgLength,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                   ESM_BEARER_RESOUCE_ALLOC_REQ);

        return;

    }

    if(ID_APP_ESM_PDP_SETUP_REQ == NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) )
    {
        /*���ú���:����ȷ����Ϣ֪ͨAPP�����γ�����Դ�������ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, ulErrorCode);
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}
VOS_VOID    NAS_ESM_ProcTimerMsgT3481Exp(const VOS_VOID * pMsg)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulErrorCode         = APP_ERR_TIME_OUT;
    VOS_UINT32                          ulActCidNum         = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU                 *pTimer3481          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgT3481Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgT3481Exp_ENUM, LNAS_ENTRY);

    /*��ȡ��Ϣ�а�����״̬��StateTblIndex*/
    ulStateTblIndex = PS_GET_REL_TIMER_NAME(pMsg);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgT3481Exp: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgT3481Exp_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_ResModFailRecord(VOS_NULL_PTR, ESM_OM_ERRLOG_TIMEOUT_T3481);
    #endif
    /*������Ϣ��Ӧ��ulStateTblIndex,��ȡ������Ķ�ʱ��*/
    pTimer3481 = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

    /*��ʱ����++*/
    pTimer3481->ucExpireTimes++;

    /*�����ǰ��ʱ����ʱ����С��NAS_ESM_MAX_TIMER_EXPIRE_TIMES��*/
    if(pTimer3481->ucExpireTimes < TI_NAS_ESM_T3481_TIMER_MAX_EXP_NUM)
    {
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú���:SM��MM������Ϣ:NAS_ESMCN_BEARER_RES_MOD_REQ*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /*����������ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3481);

        /*�ϱ��տ���Ϣ*/
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                                   pstStateAddr->stNwMsgRecord.ulMsgLength,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                   ESM_BEARER_RESOUCE_MOD_REQ);
        return;

    }

    if(ID_APP_ESM_PDP_SETUP_REQ == NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) )
    {
        /*���ú���:����ȷ����Ϣ֪ͨAPP�����γ�����Դ�������ʧ��*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, ulErrorCode);
    }
    else  if(ID_APP_ESM_PDP_RELEASE_REQ == NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) )
    {
        ulActCidNum = NAS_ESM_GetBearerLinkedCidNum(pstStateAddr->ulEpsbId);

        /* ���ֻ��Ӧһ�������Cid,˵��AppҪ�ͷ����е�SDF */
        if (ulActCidNum == NAS_ESM_BEARER_ACT_CID_NUM_ONE)
        {
            /* �����ͷŴ˳��� */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

            /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_LOCAL);
        }
        else
        {
            NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, ulErrorCode);
        }
    }
    else
    {
        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, ulErrorCode);
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcTimerMsgWaitAppCnfExp
 Description     : �ȴ�APP�ظ���ʱ����ʱ������
 Input           : VOS_VOID *pMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcTimerMsgWaitAppCnfExp(const VOS_VOID * pMsg)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgWaitAppCnfExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgWaitAppCnfExp_ENUM, LNAS_ENTRY);

    /*��ȡ��Ϣ�а�����״̬��StateTblIndex*/
    ulStateTblIndex = PS_GET_REL_TIMER_NAME(pMsg);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcTimerMsgWaitAppCnfExp: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcTimerMsgWaitAppCnfExp_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* App�ܾ����ؼ��������޸ĵĴ��� */
    NAS_ESM_AppPdpManageRspMsgRefuseProc(ulStateTblIndex);
}


VOS_VOID NAS_ESM_ProcTimerMsgAttachBearerReestExp(const VOS_VOID * pMsg)
{
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcTimerMsgAttachBearerReestExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgAttachBearerReestExp_ENUM, LNAS_ENTRY);

    (VOS_VOID)pMsg;

    /*���֧��˫APN������ע����أ������д���*/
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        if (NAS_ESM_UNASSIGNED_EPSB_ID == NAS_ESM_GetAttachBearerId())
        {
            NAS_ESM_ReestablishAttachBearer();
        }
    }
}


VOS_VOID NAS_ESM_ProcTimerMsgDeferRelNonEmcExp(const VOS_VOID * pMsg)
{
    NAS_ESM_INFO_LOG("NAS_ESM_ProcTimerMsgDeferRelNonEmcExp: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgDeferRelNonEmcExp_ENUM, LNAS_ENTRY);

    (VOS_VOID)pMsg;

    if (PS_TRUE == NAS_ESM_HasEstingEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcTimerMsgDeferRelNonEmcExp: esting emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgDeferRelNonEmcExp_ENUM, 1);

        /*����������ػ�δ�����ɹ������������ӳٶ�ʱ��*/
        NAS_ESM_TimerStart(0, TI_NAS_ESM_REL_NON_EMC_BEARER);
    }
    else if (PS_TRUE == NAS_ESM_HasExistedEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcTimerMsgDeferRelNonEmcExp: existed emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgDeferRelNonEmcExp_ENUM, 2);

        /*����������ؽ����ɹ������ͷ����зǽ�������*/
        NAS_ESM_DeactAllNonEmcPdn();
    }
    else
    {
        /*����������ؽ���ʧ�ܣ���������*/
        NAS_ESM_INFO_LOG("NAS_ESM_ProcTimerMsgDeferRelNonEmcExp: no emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcTimerMsgDeferRelNonEmcExp_ENUM, 3);
    }

    return;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
