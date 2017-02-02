


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "MmcLmmInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMDETACHAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMDETACHAPPMSGPROC_C
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


VOS_UINT32  NAS_EMM_AppDetachReqMsgChk(const MMC_LMM_DETACH_REQ_STRU *pMsgMsg)
{

    /*��Ϣ���ݼ�� */
    if ((MMC_LMM_MO_DET_PS_ONLY == pMsgMsg->ulDetachType) ||
        (MMC_LMM_MO_DET_CS_ONLY == pMsgMsg->ulDetachType) ||
        (MMC_LMM_MO_DET_CS_PS == pMsgMsg->ulDetachType))
    {
        return  NAS_EMM_PARA_VALID;

    }
    else
    {
        return  NAS_EMM_PARA_INVALID;

    }

}
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* �����IMSI DETACH���򱾵�CS��DETACH��ֱ�ӻظ��ɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq:receive cs detach during emergency attach!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
            return   NAS_LMM_MSG_HANDLED;
        }

        /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
        NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

        /*ֹͣ��ʱ��T3410*/
        NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

        /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_PLMN_SEARCH,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        /*��MMC����APP_MM_DETACH_CNF*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttResetAttAttempCounter();

            /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
            NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();

        /* �������CONN̬,�ͷ�����*/
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        }

        return  NAS_LMM_MSG_HANDLED;
    }

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*ֹͣ��ʱ��T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return   NAS_LMM_MSG_HANDLED;
}


VOS_UINT32    NAS_EMM_MsRegSsAnyMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    /*VOS_UINT32                          ulRst;*/
    NAS_LMM_FSM_STATE_STRU               stDestState;
    MMC_LMM_STOP_REQ_STRU              *pstAttStopReq;

    (VOS_VOID)ulMsgId;

    /*ֹͣ���ж�ʱ��*/
    NAS_LMM_StopAllPtlTimer();
    NAS_LMM_StopAllStateTimer();

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAnyMsgAppStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyMsgAppStopReq_ENUM,LNAS_ENTRY);

    pstAttStopReq                       = pMsg;

    /* ����App��Ϣ����ز��� */
    NAS_EMM_SaveAppMsgPara(pstAttStopReq->ulMsgId,pstAttStopReq->ulOpId);
    /* ����ػ���ʶ,�ṩ��LRRC,����LRRC�жϿտ��Ƿ��ǹػ�detach �ñ�־
       ��LMM�յ�LRRC��power off cnf���ȴ�power off cnf��ʱ���߿���ʱ���(����Ϊ0) */
    NAS_LMM_SetEmmInfoLtePowerOffFlag(NAS_EMM_YES);
    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /*������ʱ��TI_NAS_EMM_PTL_SWITCH_OFF_TIMER*/
        NAS_LMM_StartPtlTimer(         TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

        /* ��״̬ת����MS_NULL + SS_NULL_WAIT_SWITCH_OFF״̬ */
        stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_EMM;
        stDestState.enMainState             = EMM_MS_NULL;
        stDestState.enSubState              = EMM_SS_NULL_WAIT_SWITCH_OFF;
        stDestState.enStaTId                = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(stDestState);

        /* ����DEATCH for power off��Ϣ */
        NAS_EMM_SendDetachForPowerOffReq();
    }
    else
    {
        NAS_EMM_ProcLocalStop();
    }

    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* ����App��Ϣ����ز��� */
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH���ҵ�ǰע����ΪPS����ֱ�ӷ��سɹ��������ǰע����Ϊ
       CS+PS������IMSI DETACH���� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq:Process Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            /*��APP����DETACH�ɹ�*/
            NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

            /* IMSI DETACH���ͷ���Դ */
            NAS_LMM_ImsiDetachReleaseResource();

            return  NAS_LMM_MSG_HANDLED;
        }

        /* ����IMSI DETACH���� */
        NAS_EMM_SendImsiDetachReqMo();
        return  NAS_LMM_MSG_HANDLED;
    }

    /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
       ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);



    }

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* ����App��Ϣ����ز��� */
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* �ж��Ƿ�ΪIMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
           ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
        if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            NAS_EMM_SetTauTypeNoProcedure();
            NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        }

        /*ֹͣ��ʱ��*/
        NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

        /*�޸�״̬��������״̬EMM_MS_REG��״̬EMM_SS_REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
        return  NAS_LMM_MSG_HANDLED;
    }

    /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
       ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
	/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
	/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}




/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_EMM_AppSendDetCnf
(
    MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulAppRslt
)
{
    LMM_MMC_DETACH_CNF_STRU              *pEmmAppDetCnfMsg;

    /*������Ϣ�ڴ�*/
    pEmmAppDetCnfMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_DETACH_CNF_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if (NAS_EMM_NULL_PTR == pEmmAppDetCnfMsg)
    {
        /*��ӡ����*/
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_AppSendDetCnf: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendDetCnf_ENUM,LNAS_NULL_PTR);
        return;

    }

    NAS_LMM_MEM_SET(pEmmAppDetCnfMsg, 0, sizeof(LMM_MMC_DETACH_CNF_STRU));

    /*����APP_MM_DETACH_CNF��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pEmmAppDetCnfMsg,
                                        sizeof(LMM_MMC_DETACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pEmmAppDetCnfMsg->ulMsgId           = ID_LMM_MMC_DETACH_CNF;

    /*�����Ϣ����*/
    pEmmAppDetCnfMsg->ulOpId            = NAS_EMM_GetAppMsgOpId();
    pEmmAppDetCnfMsg->ulDetachRslt      = ulAppRslt;
    pEmmAppDetCnfMsg->ulReqType         = NAS_EMM_GLO_AD_GetDetTypeMo();

    /*��MMC����APP_MM_DETACH_CNF��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(                   pEmmAppDetCnfMsg);

    /*���APP����*/
    NAS_EMM_ClearAppMsgPara();

    return;

}
VOS_VOID    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ulStatRst)
{
    EMM_ESM_STATUS_IND_STRU              *pEmmEsmStatMsg;


    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG1_INFO("NAS_EMM_EsmSendStatResult is entered", ulStatRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EsmSendStatResult_ENUM,LNAS_ENTRY,ulStatRst);

    /*������Ϣ�ڴ�*/
    pEmmEsmStatMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmEsmStatMsg)
    {
        return;
    }

    /*����ID_EMM_ESM_STATUS_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(         pEmmEsmStatMsg,
                                            sizeof(EMM_ESM_STATUS_IND_STRU)-
                                            NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pEmmEsmStatMsg->ulMsgId                 = ID_EMM_ESM_STATUS_IND;

    /*�����Ϣ����*/
    if (EMM_ESM_ATTACH_STATUS_ATTACHED == ulStatRst)
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_ATTACHED;
    }
    else if (EMM_ESM_ATTACH_STATUS_EMC_ATTACHING == ulStatRst)
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_EMC_ATTACHING;

        /*clear global:EpsContextStatusChange*/
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }
    else
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_DETACHED;

        /*clear global:EpsContextStatusChange*/
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }


    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_LMM_SEND_MSG(                       pEmmEsmStatMsg);

    return;

}


VOS_UINT32    NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*��APP����DETACH�ɹ�*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq is entered");\
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* ���3411�����У���Ҫ��MMC��ATTACH���������MMC�˳�����״̬����3402��ʱ����
       ��������֪ͨ��MMC�յ�ATTACH������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetAttType();
        NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);
    }

    /*ֹͣ��ʱ��T3411,T3402*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*��APP����DETACH�ɹ�*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();


    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32    NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg =                        (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*��APP����DETACH�ɹ�*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*��APP����DETACH�ɹ�*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*��APP����DETACH�ɹ�*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}

VOS_VOID NAS_EMM_MsRegSsWaitAccessGrantIndImsiDetachProc( VOS_VOID )
{
    /* �����ǰע����ΪCS+PS����ֱ�ӻظ��ɹ� */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return ;
    }

    /* �����������գ�����IMSI DETACH���� */
    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /*����IMSI DETACH REQUEST��Ϣ*/
        NAS_EMM_SendImsiDetachReqMo();

        return ;
    }

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH���ͷ���Դ */
    NAS_LMM_ImsiDetachReleaseResource();

    return ;
}

VOS_UINT32 NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �ж��Ƿ�ΪIMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����IMSI DETACH */
        NAS_EMM_MsRegSsWaitAccessGrantIndImsiDetachProc();

        return  NAS_LMM_MSG_HANDLED;
    }

    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {

        /*����DETACH REQUEST��Ϣ*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��APP����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH���򱾵�CS��DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��APP����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* �����IMSI DETACH����ֱ�ӷ��سɹ� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*��APP����DETACH�ɹ�*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
    NAS_LMM_StopStateTimer(                  TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    /*��MMC����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /* �������CONN̬,�ͷ�����*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

    }

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* �����IMSI DETACH��������ȼ����� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);
    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*NAS_EMM_GLO_AD_GetDetMode()         = pRcvEmmMsg->ulDetacbMode;*/

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32    NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH���򱾵�CS��DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
       ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    /*���TAU���ȫ�ֱ���*/
    NAS_EMM_TAU_ClearResouce();

    return  NAS_LMM_MSG_HANDLED;
}

/* lihong00150010 emergency tau&service begin */

VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq
(
    VOS_UINT32                         ulMsgId,
    VOS_VOID                          *pMsgStru
)
{
    NAS_LMM_INTRA_DETACH_REQ_STRU              *pRcvEmmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_LMM_INTRA_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_IntraDetReqChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq: MMC_MM_SYS_INFO_IND_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* �����IMSI DETACH���򱾵�CS��DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ��UE������ע�����н�������ʱ:
           ������С���л�������С����MME����ʾ������������ȥ�������зǽ���
           ���أ�������С���ȁG����Ȼ��ANYCELL�ѵ�����С����UE����TAI����TAI LIST
           �з���TAU��MME����TAU ACCEPT��Я��������Ϣɾ�����зǽ������أ�
           ������UE������ע�����н�������ʱ�������ܳ�ʱ�䴦��REG+LIMIT_SERVICE
           ̬���յ�CS DETACH���Ա���DETACH����Ϊ���������ͷ����зǽ������ؽ������ע�� */

        /* �������ܷ���IMSI DETACH���򲻿����ڱ���С�������IMSI DETACH�ɹ���ɣ�
           �����쳣����ֻ�����REG+NORMAL_SERVICE�����������REG+LIMIT_SERVICE̬��
           ����Ҫ״̬���� */

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        /*ֹͣ��ʱ��*/
        NAS_LMM_StopPtlTimer(           TI_NAS_EMM_PTL_T3411);
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

        /*����DETACH REQUEST��Ϣ*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��APP����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                                          VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH���򱾵�CS��DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ��UE������ע�����н�������ʱ:
           ������С���л�������С����MME����ʾ������������ȥ�������зǽ���
           ���أ�������С���ȁG����Ȼ��ANYCELL�ѵ�����С����UE����TAI����TAI LIST
           �з���TAU��MME����TAU ACCEPT��Я��������Ϣɾ�����зǽ������أ�
           ������UE������ע�����н�������ʱ�������ܳ�ʱ�䴦��REG+LIMIT_SERVICE
           ̬���յ�CS DETACH���Ա���DETACH����Ϊ���������ͷ����зǽ������ؽ������ע�� */

        /* �������ܷ���IMSI DETACH���򲻿����ڱ���С�������IMSI DETACH�ɹ���ɣ�
           �����쳣����ֻ�����REG+NORMAL_SERVICE�����������REG+LIMIT_SERVICE̬��
           ����Ҫ״̬���� */

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }
    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        /*ֹͣ��ʱ��*/
        NAS_LMM_StopPtlTimer(           TI_NAS_EMM_PTL_T3411);
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

        /*����DETACH REQUEST��Ϣ*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }
    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��APP����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();
    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    /* lihong00150010 emergency tau&service end */
    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                                      VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH���򱾵�CS��DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*�޸�״̬��������״̬DEREG��״̬SS_DEREG_NO_CELL_AVAILABLE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��APP����APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_ENTRY);

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*stop T3440*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_T3440);

    /*����RRC�����ͷ�ԭ��*/
    /*NAS_EMM_GLO_AD_GetConnRelCau()      = EMM_CONN_REL_CAUSE_REJVAL_OTHER;*/

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    NAS_LMM_PrintFsmState(               NAS_LMM_PARALLEL_FSM_EMM);

    /*����AppDetachReq*/
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq:Store APP DETACH AT:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

    return  NAS_LMM_STORE_LOW_PRIO_MSG;
}


#if (FEATURE_LPP == FEATURE_ON)
VOS_VOID    NAS_EMM_MsgLppTauInitWtCnfAppDetachReqSsOrLppHandle(VOS_VOID)
{
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_PS_ATTACH_NOT_ALLOWED);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
}
#endif



VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU             *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NNAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* �����IMSI DETACH��������ȼ����棬���᰸ͨ���ٸ����᰸���� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NNAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }
        if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
            && (NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause()))
        {
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* ��TAU�����SERVICE���̣�����Ҫ���ESM������Ϣ */
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*���SR����������SMS������UE��Ҫȥע�ᣬ��Ҫ�ظ�SMS����ʧ�ܣ��������SR�ķ���ԭ��*/
        if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
        {
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
        }

        #if (FEATURE_LPP == FEATURE_ON)
        NAS_EMM_MsgLppTauInitWtCnfAppDetachReqSsOrLppHandle();
        #endif

        if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        {
            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }

        /*���ESM_DATA����*/
        NAS_EMM_SerClearEsmDataBuf();
    }


    /* ������TAU�����DETACH������£����յ��û�DETACH��Ϣ�ĳ�������ΪAT����
       δ�ظ�֮ǰ�������·�ATָ�� */

    /*����TAUģ���ṩ�ĺ���*/
    NAS_EMM_TAU_AbnormalOver();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

    /* ��MMC���� MO DETACH ��� LMM_MMC_TAU_RESULT_IND*/

    ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    /* Svlte��CL������ѡʱ������б���DETACH(�ӿ�Լ������PS DETACH),��ʱ���ܷ��Ϳտ���Ϣ */
    if((NAS_EMM_YES == NAS_LMM_IsSvlteOrLcNeedLocalDetach())
        &&(MMC_LMM_MO_DET_PS_ONLY == pRcvEmmMsg->ulDetachType))
    {
        /* ��MMC�ظ�DETACH�ɹ���ͬʱDETACH��ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ,�ͷ���· */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        /* �����ʶ */
        NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* CL��ģʱMMCָʾLMM������б���DETACH */
    if(MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH == pRcvEmmMsg->ulDetachReason)
    {
        /* ��MMC�ظ�DETACH�ɹ���ͬʱDETACH��ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ,�ͷ���· */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        /*����DETACH REQUEST��Ϣ*/
        NAS_EMM_SendDetachReqMo();
    }

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfImsiDetachProc( VOS_VOID )
{
    /* �����ǰע����ΪCS+PS����ֱ�ӻظ��ɹ� */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        /* �����REG+ATTEMPT_TO_UPDATE_MM״̬�·����SERVICE���̣���3411�����У�
           ��Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ������������֪ͨ��
           MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
        if ((NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
            && (0 < NAS_EMM_TAU_GetEmmTAUAttemptCnt())
            && (5 > NAS_EMM_TAU_GetEmmTAUAttemptCnt()))
        {
             NAS_EMM_SetTauTypeNoProcedure();
            NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        }

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return ;
    }

    /*����SER_INITģ���ṩ�ĺ���*/
    NAS_EMM_SER_AbnormalOver();

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendImsiDetachReqMo();

    return ;
}
VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
    }

    /* �ж��Ƿ�ΪIMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����IMSI DETACH */
        NAS_EMM_MsSerInitSsWtCnSerCnfImsiDetachProc();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*����SER_INITģ���ṩ�ĺ���*/
    NAS_EMM_SER_AbnormalOver();

    /* �����REG+ATTEMPT_TO_UPDATE_MM״̬�·����SERVICE���̣���3411�����У�
       ��Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ������������֪ͨ��
       MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if ((NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        && (0 < NAS_EMM_TAU_GetEmmTAUAttemptCnt())
        && (5 > NAS_EMM_TAU_GetEmmTAUAttemptCnt()))
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
    }
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /* Svlte��CL������ѡʱ������б���DETACH(�ӿ�Լ������PS DETACH),��ʱ���ܷ��Ϳտ���Ϣ */
    if((NAS_EMM_YES == NAS_LMM_IsSvlteOrLcNeedLocalDetach())
        &&(MMC_LMM_MO_DET_PS_ONLY == pRcvEmmMsg->ulDetachType))
    {
        /* ��MMC�ظ�DETACH�ɹ���ͬʱDETACH��ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ,�ͷ���· */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        /* �����ʶ */
        NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* CL��ģʱMMCָʾLMM������б���DETACH */
    if(MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH == pRcvEmmMsg->ulDetachReason)
    {
        /* ��MMC�ظ�DETACH�ɹ���ͬʱDETACH��ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ,�ͷ���· */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        /*����DETACH REQUEST��Ϣ*/
        NAS_EMM_SendDetachReqMo();
    }

    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq(
                                                 VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO(            "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);


    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID            == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR(         "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* �����IMSI DETACH��������ȼ����� */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

















































