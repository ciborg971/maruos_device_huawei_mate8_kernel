

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmPubUSuspend.h"
#include "NasLmmPublic.h"
#include "NasLmmPubMOsa.h"
#include "NasEmmPubUGlobal.h"
#include "NasEmmAttDetInterface.h"
#include "NasEmmTauInterface.h"
#include "NasEmmMrrcPubInterface.h"
#include "NasEmmSecuInterface.h"
#include "NasEmmSerInterface.h"
#include "NasLmmPubMTimer.h"
#include "NasEmmPlmnInterface.h"
#include "NasEmmPlmn.h"
#include "NasLmmPubMEntry.h"
#include "NasEmmPubUEntry.h"
#include "NasEmmAttDetInclude.h"
#include "NasEmmPubUResume.h"
#include "NasMmlCtx.h"
#include "NasEmmcPublic.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif



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

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBSUSPEND_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBSUSPEND_C
/*lint +e767*/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*leili modify for isr begin*/

/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_ProcInterSystemTransferBearerInfo(VOS_VOID)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcInterSystemTransferBearerInfo is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSystemTransferBearerInfo_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */

    /*����ISR��������,ȥ����ISR,�������г��ص�ISR��ʶΪ����ǰ*/
    if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()) &&
        (NAS_EMM_SUCC == NAS_EMM_IsBearIsrActAfter()))
    {
         /*����TINֵΪP-TMSI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        /*�������г��ص�ISR��ʶΪISR����ǰ*/
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        /*PC REPLAY MODIFY BY LEILI END*/
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcInterSystemTransferBearerInfo: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSystemTransferBearerInfo_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */
    }

    return;
}

/*leili modify for isr end*/

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgMmcSuspendReq
 Description     : �յ�MMC�Ĺ���������Ϣ����״̬�µĴ���ͬ�յ�RRC�Ĺ�����Ϣ��

 MMC��������ģʽ��С����ͨ����ԭ�����Lģ��
 LMM�յ�����Ϣ��֪ͨESM��ERABM�����ٸ�LRRC����SUSPEND_REQ��Ϣ��֪ͨLRRC���ڹ���״̬��
 LMM�յ�����Ϣ���״̬��ͬ��LMM�յ�LRRC�ϱ��Ĺ�����Ϣ���״̬��
 Լ����
 1��LMM���ڿ���̬����MMC��ֱ���·�MMC_LMM_SUSPEND_REQ�������LMM;
 2��LMM������������̬����MMC��Ҫ���·�MMC_LMM_REL_REQ�����ͷ�LMM���������ӣ�ʹLMM�������̬��Ȼ�����·�MMC_LMM_SUSPEND_REQ�������LMM��
 3��LMM������������̬����MMC���ܽ�LMM���𣻣�
 4��LMM�������������̬������������̬���յ�MMC_LMM_SUSPEND_REQ�����LMMֱ�Ӷ���;
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgMmcSuspendReq( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_PreProcMsgMmcSuspendReq: enter.  NAS_EMM_CUR_MAIN_STAT = ,CONN_STATE = ",
                            NAS_EMM_CUR_MAIN_STAT,
                            NAS_EMM_GetConnState());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_EMM_MAIN_STATE,
                            NAS_EMM_CUR_MAIN_STAT);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_EMM_CONN_STATE,
                            NAS_EMM_GetConnState());
    /* �������ֳ�����һ����L�ϱ���������̬��MMC�Ĺ�����Ϣ�Գ壬����RRC֧��������̬�´���NAS�Ĺ�������
    ��SYSCFGEX����ʵ��ʱ��֧�֡����ȡ����MMC����������̬����Lģ�����ƣ����ǰ�����MMC�������̴���*/

    /*add by lifuxin for Lnas est process re-construct start*/
    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_PreProcMsgMmcSuspendReq enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_ENTRY);
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_PreProcMsgMmcSuspendReq enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_ENTRY);
            break;
    }
    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_NULL:
                 /* �������̡��ػ��������յ�����MMC�ظ�����ʧ�� */
                NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SendMmcSuspendCnf( MMC_LMM_FAIL )");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_FAIL);
                NAS_EMM_SendMmcSuspendCnf( MMC_LMM_FAIL );
                break;

        case    EMM_MS_SUSPEND:
                /* MMC�ظ����͹�����Ϣ��������������ΪLNAS�����Ȼ���MMC�ظ� */
                if ( EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
                {
                    return NAS_LMM_MSG_HANDLED;
                }
                else if (EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeSuspendAddr());
                }
                else
                {
                    /* RRC����NAS,�Ѿ��յ�MMC�Ĺ�����Ӧ����SYSCFGEX����¹����Ѿ���ESM��ERABM
                    ���͹�������Ϣ�����Բ���Ҫ�ظ����� */
                    /* ��ո�����ȫ�ֱ�����ͬʱ������T3412��T3423��ֹͣ����Э��״̬��ʱ��, */
                    NAS_EMM_SuspendInitRelResource();

                    /* ��ֹͣ3412��ʱ�� */

                    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

                    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);
                    /*leili modify for isr begin*/
                    NAS_EMM_ProcInterSystemTransferBearerInfo();
                    /*leili modify for isr end*/

                    /* ��¼����Ĳ���: ����Դ */
                    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_MMC);

                    /* EMM״̬Ǩ��, ��������ʱ��*/
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                                EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
                                                TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
                }
                break;

        case    EMM_MS_RESUME:
                /*RESUME�������յ�MMC������Ϣ�Ĵ���*/
                NAS_EMM_ProcMsResumeMsgMmcSuspendReq();
                break;

        default  :
                /* ����״̬�������״̬����:
                ���浱ǰ״̬����ղ��ֱ���, ��ESM/ERABM/LRRC���͹���������Ϣ�� */
                NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_ValidStateMsgMmcSuspendReq");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM));
                break;
    }


    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ValidStateMsgMmcSuspendReq
 Description     : ��Ч״̬�´���MMC�Ĺ�����Ϣ

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ValidStateMsgMmcSuspendReq
(
    NAS_LMM_FSM_STATE_STRU *pstState
)
{
    (void) pstState;
    NAS_EMM_PUBU_LOG2_INFO(" NAS_EMM_ValidStateMsgMmcSuspendReq:pstState->enMainState,pstState->enSubState",
                            pstState->enMainState,
                            pstState->enSubState);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ValidStateMsgMmcSuspendReq_ENUM,LNAS_EMM_MAIN_STATE,
                            pstState->enMainState);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ValidStateMsgMmcSuspendReq_ENUM,LNAS_EMM_SUB_STATE,
                            pstState->enSubState);

    /* ��ո�����ȫ�ֱ�����ͬʱ������T3412��T3423��ֹͣ����Э��״̬��ʱ��, */
    NAS_EMM_SuspendInitRelResource();

    /* ��ֹͣ3412��ʱ�� */

    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);
    /*leili modify for isr begin*/
    NAS_EMM_ProcInterSystemTransferBearerInfo();
    /*leili modify for isr end*/
    /* ��¼����ǰ��״̬*/
    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeSuspendAddr(),
                    pstState,
                    sizeof(NAS_LMM_FSM_STATE_STRU));

    /* ��¼����Ĳ���: ����Դ */
    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_MMC);
    /* ����������ͣ��������:����L2GU HOʱ,����������ΪHO,��HOʧ�ܻ��˵�Lʱ,���ڹ�������δ�����,
        ��L�·�������, MMC����LMM,LMM��ERABM����ID_EMM_ERABM_SUSPEND_IND��Ϣ��Я���Ĺ�������ΪHO,
        ��ERABM�ڴ���HO���͵Ĺ���ʱ������г��ص�DRB״̬״̬��Ϊ����̬,���º���L��������ͨ*/
    NAS_EMM_SetSuspendType(LRRC_LMM_SYS_CHNG_TYPE_BUTT);
    /* ����IDLE̬*/
    /*NAS_EMM_MrrcChangeRrcStatusToIdle();*/

    /* ���� ESM ������Ϣ*/
    NAS_EMM_SendEsmSuspendInd();

    /* ���� ERABM ������Ϣ*/
    NAS_EMM_SendErabmSuspendInd();

    /* EMM״̬Ǩ��, ��������ʱ��*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* ��ǰ�� LTEΪ����̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}



VOS_VOID  NAS_EMM_ProcMsResumeMsgMmcSuspendReq(VOS_VOID)
{
    /*RESUME״̬���յ�MMC�Ĺ�����Ϣ����*/
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ProcMsResumeMsgMmcSuspendReq:NAS_EMM_CUR_SUB_STAT",
            NAS_EMM_CUR_SUB_STAT);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcMsResumeMsgMmcSuspendReq_ENUM,LNAS_EMM_SUB_STATE,
            NAS_EMM_CUR_SUB_STAT);

    if (EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND == NAS_LMM_GetEmmCurFsmSS())
    {
       NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeResumeAddr());
    }
    else
    {
        /*RESUME+RRCORI_WAIT_SYS_INFO��RESUME+RRCRSM_WAIT_OTHER_RESUME�Ĵ���*/
        NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq();
    }

    return;
}



VOS_VOID  NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO(" NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq:NAS_EMM_GetResumeType()",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /*RESUME+RRCORI_WAIT_SYS_INFO��RESUME+RRCRSM_WAIT_OTHER_RESUME״̬���յ�MMC������Ϣ�Ĵ���*/
    switch (NAS_EMM_GetResumeType())
    {
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
            /* MMC��L2GU���˺�ȴ�ϵͳ��Ϣ��ʱ����ʱ���·�����������Ϣ*/
            NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeSuspendAddr());
            break;

        default:
            /* GU2L��Ӧ���յ�MMC�Ĺ�����Ϣ��Ϊ���ݴ�Ҳ�����˴���*/
            NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeResumeAddr());
            break;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendRelCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendRelCnf( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgRrcSuspendRelCnf entred");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendRelCnf_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB
        == NAS_EMM_GetSuspendRelCause())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgRrcSuspendRelCnf:NO SEND TO MMC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendRelCnf_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* ֪ͨMMCSuspendRelCnf*/
    NAS_EMM_SendMmcSuspendRelCnf();

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendRelCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc(MsgBlock * pMsg)
{
    VOS_UINT32                          ulMsgId = ID_LRRC_LMM_SUSPEND_IND;
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsg;

    if(   (LRRC_LMM_SYS_CHNG_TYPE_REDIR       == pLrrcLmmSuspendInd->enSysChngType)
        || (LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE == pLrrcLmmSuspendInd->enSysChngType) )
    {   /* �������̣����REDIRECT����CCO_REVERSE, ����Ҫ���� */

        /*add by lifuxin for suspend&esting collision 2014-12-09 start*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
        NAS_EMM_SecuCurrentContextUpNasCountBack();
        NAS_EMM_CommProcConn2Ilde();
        /* RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
        /*add by lifuxin for suspend&esting collision 2014-12-09 end*/

        /*add by lifuxin for Lnas est process re-construct start*/
        NAS_LMM_EstingOrReleasingProcessTimerHandle();
        NAS_LMM_IfEmmHasBeenPushedThenPop();
        (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
    }
    else
    {   /* �����RESEL,����;
           ���������У����ᷢ��CCO, HO,*/
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc: RESEL ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
    }

}



/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendInd( MsgBlock * pMsg )
{
    VOS_UINT32                          ulMsgId = ID_LRRC_LMM_SUSPEND_IND;
    VOS_UINT32                          ulRslt;
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_PreProcMsgRrcSuspendInd: discard. enSysChngType = ",
                        pLrrcLmmSuspendInd->enSysChngType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL1,
                        pLrrcLmmSuspendInd->enSysChngType);
    if(NAS_LMM_SYSCFG_FLAG_VALID == NAS_LMM_GetEmmInfoSyscfgCtrl())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInd: NAS_LMM_SYSCFG_YES");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL2);
        /* ��RRC�ع���ʧ��*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }
    if(NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInd: NAS_EMM_PLMN_SRCH_YES");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL3);
        /* ��RRC�ع���ʧ��*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }
    /*add by lifuxin for Lnas est process re-construct start*/
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc(pMsg);
        return NAS_LMM_MSG_HANDLED;
    }
    /*add by lifuxin for Lnas est process re-construct end*/

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc();
        return NAS_LMM_MSG_HANDLED;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_NULL:
                /* ��RRC�ع���ʧ��*/
                NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
                break;

        case    EMM_MS_SUSPEND:
        case    EMM_MS_RESUME :
                /* ֻ����CL��ģ������ʱ�򣬿������̡��ػ����̣����𡢻ָ������в����յ�*/
                /* ��RRC�ع���ʧ��*/
                NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
                break;

        case    EMM_MS_AUTH_INIT:
                NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_REG_INIT:
                NAS_EMM_MsRegInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_DEREG_INIT:
                NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_REG:

                if ( EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

                    #if (FEATURE_ON == FEATURE_DSDS)
                    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
                    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                    #endif

                    NAS_EMM_AdStateConvert( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

                    NAS_LMM_ImsiDetachReleaseResource();
                }

                ulRslt = NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                (VOS_VOID)ulRslt;
                break;
        case    EMM_MS_SER_INIT:
                NAS_EMM_MsSerInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_TAU_INIT:
                NAS_EMM_MsTauInitRcvLrrcSuspendIndProc(pMsg);
                break;
        default  :
                /* ����״̬: ���浱ǰ״̬����ղ��ֱ���, ��LRRC���͹���������Ϣ�� */
                ulRslt = NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                (VOS_VOID)ulRslt;
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_RcvLrrcSuspendInd( VOS_UINT32  ulMsgId,
                                  const VOS_VOID   *pMsgStru  )
{
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RcvLrrcSuspendInd: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcSuspendInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsgStru;

    /* ��¼������� */
    NAS_EMM_SaveLrrcSuspendPara(pLrrcLmmSuspendInd);

    /* ���SUSPEND������HO,����DL_NASCOUNT*/
    if(   (LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmSuspendInd->enSysChngType)
       && (NAS_EMM_BIT_SLCT == pLrrcLmmSuspendInd->bitOpHoSecuPara))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RcvLrrcSuspendInd: HO.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SecuUpdateDlNasCountHo(
            pLrrcLmmSuspendInd->stHoSecuPara.ucHoSecuPara);
    }

    /*leili modify for isr begin*/
    if (LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE == pLrrcLmmSuspendInd->enSysChngType)
    {
        NAS_EMM_CcoInterSystemFailProc();
    }
    /*leili modify for isr end*/

    /* ֪ͨMMC���� */
    NAS_EMM_SendMmcSuspendInd();


    /* EMM״̬Ǩ��, ��������ʱ��*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
                                TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    /* ��ǰ�� LTEΪ����̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp(VOS_UINT32        ulMsgId,
                                                             VOS_VOID   *pMsgStru   )
{
    MMC_LMM_SUSPEND_RSP_STRU           *pMmcEmmRusRsp   = VOS_NULL_PTR;
    LRRC_LNAS_RESULT_ENUM_UINT32        ulRslt          = LRRC_LNAS_SUCC;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_ENTRY);

    pMmcEmmRusRsp           = (MMC_LMM_SUSPEND_RSP_STRU*)pMsgStru;

    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    /*��MMC��Ӧʧ��*/
    if ( MMC_LMM_FAIL == pMmcEmmRusRsp->ulRst)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp fail enter: MMC enRslt = ",
                               pMmcEmmRusRsp->ulRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_FAIL,
                               pMmcEmmRusRsp->ulRst);

        /*�ָ�״̬*/
        NAS_LMM_MEM_CPY( NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    NAS_EMM_GetStateBeforeSuspendAddr(),
                    sizeof(NAS_LMM_FSM_STATE_STRU));

        /* ��ǰ�� LTEΪ����̬ */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* ֹͣ����ESM,ERABM,��MMC�Ĺ���ʧ����Ϣת����LRRC */
        /* ���� LRRC_LMM_SUSPEND_RSP*/

        ulRslt          = LRRC_LNAS_FAIL;
        NAS_EMM_SendLrrcSuspendRsp(ulRslt);
        NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc();
    }
    else if(MMC_LMM_SUCC == pMmcEmmRusRsp->ulRst)
    {
        /* ������Դ */
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp: succ enter.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_SUCC);

        /*�յ�MMC��MMC_LMM_SUSPEND_NOTIFY��Ϣ���������ģ��ȫ�ֱ���*/
        /* ���� ESM ������Ϣ*/
        NAS_EMM_SendEsmSuspendInd();

        /* ���� ERABM ������Ϣ*/
        NAS_EMM_SendErabmSuspendInd();
        /* ֹͣ��ʱ�� */
        NAS_LMM_SuspendInitStopLmmTimer();

        /* EMM״̬Ǩ��, ��������ʱ��*/
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                    EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
                                    TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    }
    else
    {

    }

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LNAS_RESULT_ENUM_UINT32    ulRslt = LRRC_LNAS_FAIL;
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp_ENUM,LNAS_TIMER_EXPIRED);

    /*�ָ�״̬*/
    NAS_LMM_MEM_CPY( NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                NAS_EMM_GetStateBeforeSuspendAddr(),
                sizeof(NAS_LMM_FSM_STATE_STRU));

    /* ��ǰ�� LTEΪ����̬, �ָ�����ǰ�ļ���̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;


    /* ���ڵ�MMC��Ӧ��ʱ�����ٹ���ESM��ERABM����MMC�Ĺ���ʧ����Ϣת����LRRC */
    /* ���� LRRC_LMM_SUSPEND_RSP*/
    NAS_EMM_SendLrrcSuspendRsp(ulRslt);
    NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc();

    return  NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LNAS_RESULT_ENUM_UINT32        ulRslt          = LRRC_LNAS_SUCC;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp_ENUM,LNAS_ENTRY);

    NAS_EMM_GetUplayerCount()++;

    /* RRC����Ӧ����ζ�Ź���֪ͨ���  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM <= NAS_EMM_GetUplayerCount())
    {
        /* ֹͣ��ʱ�� */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* ����˴ι�����ϲ���Ӧ��¼���ָ����̽�ʹ�� */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /* RRC����Ĺ���Ϊ�յ�MMC����Ӧ����RRC������Ӧ��Ȼ��ȴ�������� */

        /* ���� LRRC_LMM_SUSPEND_RSP*/
        NAS_EMM_SendLrrcSuspendRsp(ulRslt);

        /* ״̬Ǩ��*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                        EMM_SS_SUSPEND_WAIT_END,
                                        TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    }

    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    NAS_LMM_EMMC_LOG1_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq.uspendRelCause =",
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);

    /* ֹͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* ����˴ι�����ϲ���Ӧ��¼���ָ����̽�ʹ�� */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    /* ���� LRRC_LMM_SUSPEND_RSP*/
    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_SUCC);

    /*����LRRC_LMM_SUSPEND_REL_REQ��Ϣ*/
    NAS_EMM_SndLrrcSuspendRelReq();

    /* ֱ��ת��EMM_SS_SUSPEND_WAIT_END̬�ȴ�RESUME IND��Ϣ */
    NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                    EMM_SS_SUSPEND_WAIT_END,
                                    TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);
    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    pstAppDetReq = (MMC_LMM_DETACH_REQ_STRU*)pMsgStru;

    /* ֹͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* ����˴ι�����ϲ���Ӧ��¼ */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    /* �����������̣��˻�L��ģ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

    /* ����ESM, ERABM */
    NAS_EMM_SendEsmResumeInd();
    NAS_EMM_SendErabmResumeInd();

    /* ��MMC��DETACH�ɹ� */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ��MMC���ͻָ� */
    NAS_EMM_SendMmcResumeInd();

    /* ��RRC�ع���ʧ�ܣ��˻�L��ģ��ϵͳ��Ϣ*/
    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);

    /* �����CSFB���µĹ�����ֹCSFB�͹�����˵�L��ģ */
    if(LRRC_LMM_SUS_CAUSE_CSFB == NAS_EMM_GetSuspendCause())
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

        /* ֪ͨMM��ֹCSFB */
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);

        /* ֻ��CSFB�ĳ�������������յ�CS DETACH������������CS DETACHԤ�������Ѿ����� */
        if(MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType)
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

            /* ����֮ǰע����ΪCS_PS�������Ƿ����ע�ᶼ�϶���ע��̬ */
            NAS_EMM_AdStateConvert(EMM_MS_REG,
                                   EMM_SS_REG_NO_CELL_AVAILABLE,
                                   TI_NAS_EMM_STATE_NO_TIMER);

            /* IMSI DETACH���ͷ���Դ */
            NAS_LMM_ImsiDetachReleaseResource();

            /* ��RRC���ͷţ���������״̬Ϊ�ͷŹ����� */
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

            return NAS_LMM_MSG_HANDLED;
        }
    }

    /* �յ�����PS��CS_PS���ͣ�ȫ��ִ�б���DETACH������CSFB���� */

    /* ֪ͨESMִ���˱���DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* �п����Ǵ��ڽ���ע����޿�״̬ */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        /* �޿� */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* �п� */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_CELL_AVAILABLE,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /* �л���CCO�ĳ�������RRC���ͷ� ����ѡ���ض����CSFB������RRC��Ȼ���ͷ�*/
    if((NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetSuspendType())
        ||(NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetSuspendType()))
    {
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
    }

    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32  NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_GetUplayerCount()++;

    /* ������ 2����ζ�� ESM��ERABM������� */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {
        /* ֪ͨRRC���� */
        NAS_EMM_SendLrrcSuspendReq();
    }

    /* ������ 3����ζ�� RRC����Ӧ����ζ�Ź���֪ͨ���  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_ALL <= NAS_EMM_GetUplayerCount())
    {
        /* ֹͣ��ʱ�� */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* ����˴ι�����ϲ���Ӧ��¼���ָ����̽�ʹ�� */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /* ����ɹ���֮ǰ��GU��L����ϵͳ�任���������ͼ�¼��Ϣ������� */
        NAS_EMM_ClearResumeInfo();

        /* MMC����Ĺ�����Ϊ�յ�RRC������ɣ���MMC��Ӧ����ɹ��� */
        /* ��MMC���͹�����Ӧ */
        NAS_EMM_SendMmcSuspendCnf(MMC_LMM_SUCC);

        /* �����������״̬ */
        NAS_EMM_SuspendEndStateChng();
    }

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSuspendSsMmcOrSyscfgOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ��MMC��DETACH�ɹ� */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ֪ͨESMִ���˱���DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* �޸Ĺ���ǰ״̬�������������� */
    NAS_EMM_SetMsBefSuspend(EMM_MS_DEREG);

    /* �п����Ǵ��ڽ���ע����޿�״̬ */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_IMSI);

    }
    else
    {
        NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_CELL_AVAILABLE);
    }

    /* ֹͣ����EMMЭ�鶨ʱ�� ��������NAS_LMM_DeregReleaseResourceΪ��ֹ��ͣ��ǰ״̬��ʱ�� */
    NAS_LMM_StopAllEmmPtlTimer();

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_PUBM_ClearResource();
    NAS_EMM_PUBU_ClearResource();
    NAS_EMM_SECU_ClearResource();
    NAS_EMM_Attach_ClearResourse();
    NAS_EMM_Detach_ClearResourse();
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp_ENUM,LNAS_ENTRY);

    /*MMC����ESM/RAMB��ʱ*/
    if( EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
    {
        if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM > NAS_EMM_GetUplayerCount())
        {
            NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_ECM_FAIL);
        }
        else
        {
            NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_RRC_FAIL);
        }
    }
    else/*RRC����ESM/RAMB��ʱ*/
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_ECM_FAIL);

    }

    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgMmcResumeNotify(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ���TAU Start Cause */
    /*NAS_EMM_TAU_GetEmmTAUStartCause() = NAS_EMM_TAU_START_CAUSE_DEFAULT;*/

    /* ֹͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    /* ����T3412��T3423��ֹͣ״̬��ʱ��, ��ո�����ȫ�ֱ���*/
    NAS_EMM_SuspendInitRelResource();

    /* ����ɹ���֮ǰ��GU��L����ϵͳ�任���������ͼ�¼��Ϣ������� */
    NAS_EMM_ClearResumeInfo();

    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);

    /* ����ǲ�������CL�汾����ִ�д˷�֧�Ĵ��� */
    #if (FEATURE_ON != FEATURE_UE_MODE_CDMA)
    if (NAS_LMM_SUS_SYS_CHNG_DIR_L2C == NAS_EMM_GetSuspendDir())
    {
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_CELL_AVAILABLE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ,�ͷ���· */
        NAS_LMM_DeregReleaseResource();
        return NAS_LMM_MSG_HANDLED;
    }
    #endif

    /* �����������״̬ */
    NAS_EMM_SuspendEndStateChng();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    NAS_LMM_EMMC_LOG1_NORM("NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq",
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);


    /*����LRRC_LMM_SUSPEND_REL_REQ��Ϣ*/
    NAS_EMM_SndLrrcSuspendRelReq();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SuspendEndStateChng
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-4  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SuspendEndStateChng( VOS_VOID)
{
    switch(NAS_EMM_GetMsBefSuspend())
    {
        case    EMM_MS_REG:
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:
                /* ��ע��ɹ���תΪREG ��NO CELL״̬ */
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
                break;

        default  :
                if(EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
                {
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_IMSI,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                }
                else
                {
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                }
               break;
    }

   return;
}
VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgWtEndTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ��λ */
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_WAIT_MMC_END_FAIL);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LMM_ACCESS_GRANT_IND_STRU     *pstRrcMmGrantInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulEmmStaBeforeSuspend = 0;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_ENTRY);

    /* ��ο�ָ����*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd: NULL PTR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* ��ȡLRRC_LMM_ACCESS_GRANT_IND��Ϣ**/
    pstRrcMmGrantInd = (LRRC_LMM_ACCESS_GRANT_IND_STRU *)pMsgStru;

    /* ��ȡ����ǰ��״̬*/
    ulEmmStaBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_GetMsBefSuspend(),
                                                      NAS_EMM_GetSsBefSuspend());
    /* ���ݹ���ǰ��״̬����ͬ����*/
    switch(ulEmmStaBeforeSuspend)
    {
        /* ����ǰ��״̬ΪDereg.Attach_Needed��
           ��������MO_Signal Bar���򽫹���ǰ״̬�޸�ΪDereg.Normal_Service;
           ���򣬴�ӡ������Ϣ���������
         *
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG,
                                       EMM_SS_DEREG_ATTACH_NEEDED):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Dereg.Attach_Needed.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_EMM_ATTACH_NEEDED);
            if ((LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL       == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT== pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_ALL             == pstRrcMmGrantInd->enAccessGrantType))
            {
                NAS_EMM_SetMsBefSuspend(EMM_MS_DEREG);
                NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NORMAL_SERVICE);
            }
            else
            {
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:GrantType Err. ");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_ERROR);
            }
            break;

        /* ����ǰ��״̬ΪReg.WtAccessGrantInd������GrantType���޸�BarType*/
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,
                                       EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Reg.WtAccessGrantInd.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_ClearBarType(pstRrcMmGrantInd->enAccessGrantType);
            break;

        /* ����״̬����ӡ������Ϣ*/
        default:
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Sta Err or LRRC Err.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_FUNCTION_LABEL2);
            break;
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SaveLrrcSuspendPara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveLrrcSuspendPara( const LRRC_LMM_SUSPEND_IND_STRU  *pLrrcLmmSuspendInd )
{
    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_LRRC);
    NAS_EMM_SetSuspendDir(pLrrcLmmSuspendInd->enSysChngDir);
    NAS_EMM_SetSuspendType(pLrrcLmmSuspendInd->enSysChngType);
    NAS_EMM_SetSuspendCause(pLrrcLmmSuspendInd->enSusCause);
    NAS_EMM_SetSuspendSecuPara((pLrrcLmmSuspendInd->stHoSecuPara).ucHoSecuPara);

    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeSuspendAddr(),
                    NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    sizeof(NAS_LMM_FSM_STATE_STRU));

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SuspendInitRelResource
 Description     : �յ�������Ϣ��Ҫ�岿����Դ������Դ��ͬ��LOCAL DETACH���壬
                   ��Ҫ��ģ���ṩר���ڹ���ʱ����ĺ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SuspendInitRelResource( VOS_VOID)
{

    /* ֹͣ����T3402,T3412��T3423������EMMЭ�鶨ʱ��*/
    NAS_LMM_SuspendInitStopLmmTimer();

    /* �ͷſ��ܴ��ڵĶ�̬�ڴ� */
    NAS_LMM_FreeDynMem();

    /*PUBM����*/
    NAS_LMM_PUBM_ClearResource();

    /*===============  EMM����ģ������  ===============*/

    /* EMM����������������״̬��Ϣ */
    NAS_EMM_PUBU_SuspendClearResource();

    NAS_EMM_SECU_ClearResource();
    NAS_EMM_Attach_SuspendInitClearResourse();
    NAS_EMM_Detach_ClearResourse();

    /* TAU������ֹͣT3402��T3411��ʱ��*/
    NAS_EMM_TAU_SuspendInitClearResouce();
    NAS_EMM_SER_ClearResource();

    /*���bar���̺�����*/
    NAS_EMM_ClearBarResouce();

    NAS_EMM_ClrAllUlDataReqBufferMsg();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SuspendEndRelResource
 Description     : ���������ֹͣT3412, ���T3412�ĳ�ʱ��־
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SuspendEndRelResource( VOS_VOID)
{

    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3412);

    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_NO);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcSuspendCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcSuspendCnf( MMC_LMM_RESULT_ID_ENUM_UINT32 ulSuspendRst )
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstMmcSuspendCnfMsg;

    /* ����MMC�ڲ���Ϣ */
    pstMmcSuspendCnfMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendCnfMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendMmcSuspendCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcSuspendCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcSuspendCnfMsg,0,sizeof(LMM_MMC_SUSPEND_CNF_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendCnfMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_CNF_STRU));

    /* �����ϢID */
    pstMmcSuspendCnfMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_CNF;

    /* �����Ϣ�� */
    pstMmcSuspendCnfMsg->ulOpId         = NAS_EMM_OPID_MMC;
    pstMmcSuspendCnfMsg->ulRst          = ulSuspendRst;

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendCnfMsg);

    return;
}
VOS_VOID  NAS_EMM_SendMmcSuspendRelCnf(VOS_VOID )
{
    LMM_MMC_SUSPEND_REL_CNF_STRU           *pstMmcSuspendRelCnfMsg;

    /* ����DOPRA��Ϣ */
    pstMmcSuspendRelCnfMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_REL_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendRelCnfMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcSuspendRelCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcSuspendRelCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcSuspendRelCnfMsg,0,sizeof(LMM_MMC_SUSPEND_REL_CNF_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendRelCnfMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_REL_CNF_STRU));

    /* �����ϢID */
    pstMmcSuspendRelCnfMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_REL_CNF;


    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendRelCnfMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcSuspendInd(VOS_VOID )
{
    LMM_MMC_SUSPEND_IND_STRU           *pstMmcSuspendIndMsg;

    /* ����DOPRA��Ϣ */
    pstMmcSuspendIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendIndMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcSuspendInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcSuspendInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcSuspendIndMsg,0,sizeof(LMM_MMC_SUSPEND_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_IND_STRU));

    /* �����ϢID */
    pstMmcSuspendIndMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_IND;

    /* �����Ϣ�� */
    if(NAS_LMM_SUS_SYS_CHNG_DIR_L2W == NAS_EMM_GetSuspendDir())
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2W;
    }
    else if(NAS_LMM_SUS_SYS_CHNG_DIR_L2C == NAS_EMM_GetSuspendDir())
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2C;
    }
    else
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2G;
    }


    switch(NAS_EMM_GetSuspendType())
    {
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_RSL;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_HO;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_CCO;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_REDIR;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_CCO_REVERSE;
                break;

        default    :
                NAS_EMM_PUBU_LOG1_ERR("NAS_EMM_SendMmcSuspendInd: ERROR, enSysChngType =",
                                    NAS_EMM_GetSuspendType());
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SendMmcSuspendInd_ENUM,LNAS_ERROR,
                                    NAS_EMM_GetSuspendType());
                break;
    }


    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendIndMsg);

    return;
}




/*****************************************************************************
 Function Name   : NAS_EMM_SendEsmSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendEsmSuspendInd( VOS_VOID )
{
    EMM_ESM_SUSPEND_IND_STRU           *pstEsmSuspendIndMsg;

    /* ����DOPRA��Ϣ */
    pstEsmSuspendIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstEsmSuspendIndMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstEsmSuspendIndMsg,0,sizeof(EMM_ESM_SUSPEND_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_SUSPEND_IND_STRU));

    /* �����ϢID */
    pstEsmSuspendIndMsg->ulMsgId        = ID_EMM_ESM_SUSPEND_IND;


    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstEsmSuspendIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendErabmSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendErabmSuspendInd( VOS_VOID )
{
    EMM_ERABM_SUSPEND_IND_STRU           *pstLrabmSuspendIndMsg;

    /* ����DOPRA��Ϣ */
    pstLrabmSuspendIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstLrabmSuspendIndMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrabmSuspendIndMsg, 0, sizeof(EMM_ERABM_SUSPEND_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_ERABM_MSG_HEADER((pstLrabmSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ERABM_SUSPEND_IND_STRU));

    /* �����ϢID */
    pstLrabmSuspendIndMsg->ulMsgId        = ID_EMM_ERABM_SUSPEND_IND;
    pstLrabmSuspendIndMsg->enSysChngType  = NAS_EMM_GetSuspendType();


    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrabmSuspendIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendLrrcSuspendReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendLrrcSuspendReq( VOS_VOID )
{
    LRRC_LMM_SUSPEND_REQ_STRU           *pstLrrcSuspendReqMsg;

    /* ����DOPRA��Ϣ */
    pstLrrcSuspendReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendReqMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrrcSuspendReqMsg, 0, sizeof(LRRC_LMM_SUSPEND_REQ_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendReqMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_REQ_STRU));

    /* �����ϢID */
    pstLrrcSuspendReqMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_REQ;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrrcSuspendReqMsg);

    return;
}
VOS_VOID  NAS_EMM_SndLrrcSuspendRelReq( VOS_VOID )
{
    LRRC_LMM_SUSPEND_REL_REQ_STRU           *pstLrrcSuspendRelReqMsg;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SndLrrcSuspendRelReq: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLrrcSuspendRelReq_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pstLrrcSuspendRelReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_REL_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendRelReqMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrrcSuspendRelReqMsg, 0, sizeof(LRRC_LMM_SUSPEND_REQ_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendRelReqMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_REL_REQ_STRU));

    /* �����ϢID */
    pstLrrcSuspendRelReqMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_REL_REQ;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrrcSuspendRelReqMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SendLrrcSuspendRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendLrrcSuspendRsp( LRRC_LNAS_RESULT_ENUM_UINT32 ulRst )
{
    LRRC_LMM_SUSPEND_RSP_STRU           *pstLrrcSuspendRspMsg;

    /* ����DOPRA��Ϣ */
    pstLrrcSuspendRspMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendRspMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrrcSuspendRspMsg, 0, sizeof(LRRC_LMM_SUSPEND_RSP_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendRspMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_RSP_STRU));

    /* �����ϢID */
    pstLrrcSuspendRspMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_RSP;
    pstLrrcSuspendRspMsg->enRslt        = ulRst;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrrcSuspendRspMsg);

    return;
}
VOS_UINT32  NAS_EMM_PreProcMsgMmcActionRstReq( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enPreMainState;
    /* ���浱ǰ״̬�����ж�gu action�Ƿ�����emm״̬�ı� */
    enPreMainState = NAS_LMM_GetEmmCurFsmMS();

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: enActionType = , ulActRst = ",
                            pMmcActResult->enActionType,
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->enActionType,
                            pMmcActResult->ulActRst);

    /* ���ǹ���̬������������ */
    if(NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_GetCurLteState = , ",
                            NAS_EMM_GetCurLteState());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_FUNCTION_LABEL2,
                            NAS_EMM_GetCurLteState());

        return NAS_LMM_MSG_HANDLED;
    }

    /* ����DEREG.NOCELLAVAILABLE,DEREG.NOIMSI,REG.NOCELLAVAILABLE����״̬����������Ϣ*/
    if(NAS_EMM_STATE_INVALID == NAS_EMM_CheckMmcActionRstReqStateValid())
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_CUR_MAIN_STAT  = , NAS_EMM_CUR_SUB_STAT = ",
                            NAS_EMM_CUR_MAIN_STAT,
                            NAS_EMM_CUR_SUB_STAT);

        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_EMM_MAIN_STATE,
                            NAS_EMM_CUR_MAIN_STAT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_EMM_SUB_STATE,
                            NAS_EMM_CUR_SUB_STAT);


        return NAS_LMM_MSG_HANDLED;
    }

    /*������Ϣ������*/
    NAS_EMM_SaveGuActRstPara(pMsg);

    /*��Ȩ�ܾ�GUģCS��PS��CS_PS�Ĵ�����ͬ��LģҲ�����տ���Ч���� */
    if (MMC_LMM_RSLT_TYPE_AUTH_REJ == pMmcActResult->ulActRst)
    {
        /*����ͬ�ܾ�ԭ��3*/
        NAS_EMM_ProcGuDettRejCause3();
        /*��GU��action��������EMM״̬�ı䣬��EMM״̬�����ı���ESM����StatusInd��Ϣ*/
        NAS_EMM_GuActionSendStatusInd(enPreMainState);

        return NAS_LMM_MSG_HANDLED;
    }

    /* ����ҵ�����ͣ����ò�ͬģ���ṩ�Ĵ����� */
    NAS_EMM_GuActionMsgDistr(pMsg);

    /*��GU��action��������EMM״̬�ı䣬��EMM״̬�����ı���ESM����StatusInd��Ϣ*/
    NAS_EMM_GuActionSendStatusInd(enPreMainState);

    return NAS_LMM_MSG_HANDLED;
}
VOS_VOID  NAS_EMM_SaveGuActRstPara( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    NAS_EMM_GetGuActType() = pMmcActResult->enActionType;
    NAS_EMM_GetGuActRst()  = pMmcActResult->ulActRst;
    NAS_EMM_GetGuActRstOpReqDomain() = pMmcActResult->bitOpReqDomain;
    NAS_EMM_GetGuActReqDomain() = pMmcActResult->ulReqDomain;
    NAS_EMM_GetGuActRstOpRstDomain()= pMmcActResult->bitOpRstDomain;
    NAS_EMM_GetGuActRstDomain() = pMmcActResult->ulRstDomain;
    NAS_EMM_GetGuActRstOpMtDetachType()= pMmcActResult->bitOpMtDetachType;
    NAS_EMM_GetGuActMtDetachType() = pMmcActResult->ulMtDetachType;
    NAS_EMM_GetGuActRstOpCnCause() = pMmcActResult->bitOpCnCause;
    NAS_EMM_GetGuActCnCause() = pMmcActResult->ucCnCause;
    NAS_EMM_GetGuActRstOpAtmpCnt() = pMmcActResult->bitOpAtmpCnt;
    NAS_EMM_GetGuActAttemptCount() = pMmcActResult->ulAttemptCount;

    return;
}


VOS_UINT32  NAS_EMM_CheckMmcActionRstReqStateValid( VOS_VOID )
{
    VOS_UINT32                          ulRet = NAS_EMM_STATE_INVALID;
    VOS_UINT32                          ulCurEmmStat;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NO_CELL_AVAILABLE):

                ulRet = NAS_EMM_STATE_VALID;
                break;
        default    :
                break;
    }
    return ulRet;
}

VOS_VOID  NAS_EMM_GuActionMsgDistr( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    switch(pMmcActResult->enActionType)
    {
        case    MMC_LMM_ACTION_ATTACH:
                NAS_EMM_ProGuAttachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_RAU:

        case    MMC_LMM_ACTION_PERIODC_RAU:
                NAS_EMM_ProGuRauRst(pMsg);
                break;
        case    MMC_LMM_ACTION_MT_DETACH:
                NAS_EMM_ProGuMtDetachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_LOCAL_DETACH:
                NAS_EMM_ProGuLocalDetachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_MO_DETACH:
                NAS_EMM_ProGuMoDetachRst(pMsg);
                break;
        case    MMC_LMM_ACTION_LAU:
                NAS_EMM_ProGuLauRst(pMsg);
                break;

        case    MMC_LMM_ACTION_PS_SERVICE_REQ:
                NAS_EMM_ProGuServiceRst(pMsg);
                break;

        case    MMC_LMM_ACTION_CM_REQ:
                NAS_EMM_ProGuCmRst(pMsg);
                break;
        case    MMC_LMM_ACTION_MM_ABORT:
                NAS_EMM_ProGuAbortRst(pMsg);
                break;

        default    :
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: default RST.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuActionMsgDistr_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }

    return;
}


VOS_VOID  NAS_EMM_GuActionSendStatusInd( NAS_LMM_MAIN_STATE_ENUM_UINT16 enPreMainState)
{
    /* �жϵ�ǰ״̬�Ƿ�ı�,��û�иı��򲻸�esm������Ӧ״̬��Ϣ */
    if(NAS_EMM_CUR_MAIN_STAT == enPreMainState)
    {
        return;
    }
    /*���ݵ�ǰ״̬����ESM����Ӧ��״̬��Ϣ*/
    if(EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT )
    {
        /* ֪ͨESM״̬�ı� */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);
    }
    else if(EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        /* ֪ͨESM״̬�ı� */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    else
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_GetCurLteState = . ",
                            NAS_EMM_GetCurLteState());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_GuActionSendStatusInd_ENUM,LNAS_FUNCTION_LABEL1);
    }
    return;
}

VOS_VOID  NAS_EMM_GuAttachActionRej( MsgBlock * pMsg  )
{
    /*�����ж�������ͽ����ֻ����ԭ��ֵ���д���*/
    NAS_EMM_GuCombinedAndPsOnlyAttachRej(pMsg);


}
VOS_UINT32  NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb( MsgBlock * pMsg  )
{

    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulReqDomain))
     &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

VOS_UINT32  NAS_EMM_CheckGuActReqDomainPsRstDomainPs( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain))
     &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

VOS_UINT32  NAS_EMM_CheckGuActReqDomainCombiRstDomainPs( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
       &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulReqDomain))
       &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
       &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}


VOS_UINT32  NAS_EMM_CheckMmUpStateAndLaiChange( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCsUpdateStatus)
            && (MMC_LMM_CS_UPDATE_STATUS_UPDATED != pMmcActResult->ucCsUpdateStatus))
        || ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpLaiChangFlg)
            && (VOS_TRUE == pMmcActResult->ucLaiChangFlg)))
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}

VOS_UINT32  NAS_EMM_CheckGprsUpStateAndRaiChange( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpGprsUpdateStatus)
            && (MMC_LMM_GPRS_UPDATE_STATUS_UPDATED != pMmcActResult->ucGprsUpdateStatus))
        || ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRaiChangFlg)
            && (VOS_TRUE == pMmcActResult->ucRaiChangFlg)))
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}


VOS_VOID  NAS_EMM_ProcCsDomainRetainPsDomainNull
(
    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs
)
{
    NAS_LMM_REG_DOMAIN_ENUM_UINT32      enRegDoamin;

    /*���浱ǰע����*/
    enRegDoamin = NAS_LMM_GetEmmInfoRegDomain();

    /*����DEREG��״̬*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        usSs,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*����ע����״̬*/
    if(NAS_LMM_REG_DOMAIN_CS_PS == enRegDoamin)
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
    }
    else if(NAS_LMM_REG_DOMAIN_CS == enRegDoamin)
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    }
    return;
}
VOS_VOID  NAS_EMM_ProcPsDomainRetainCsDomainNull( VOS_VOID)
{
    /*����ע����״̬*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    }
    return;
}

/*leili modify for cs domain end*/

VOS_VOID  NAS_EMM_GuCombinedAndPsOnlyAttachRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*GU��CN REJʱһ���ὫbitOpCnCause��ΪTURE,�˴������ݴ�*/

    switch(pMmcActResult->ucCnCause)
    {
        /* #3,6,7,8��#3ԭ��ֵ���� */
        case NAS_LMM_CAUSE_ILLEGAL_UE:
        case NAS_LMM_CAUSE_ILLEGAL_ME:
        case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            NAS_EMM_ProcGuAttRejCause3();

            break;

        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_EMM_ProcGuAttRejCause7();
            break;

        /* attach #11,12,13,15��#11ԭ��ֵ���� */
        case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_LMM_CAUSE_TA_NOT_ALLOW:
        case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_LMM_CAUSE_NO_SUITABL_CELL:

            NAS_EMM_ProcGuAttachRejCause11();

            break;

        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            NAS_EMM_ProcGuAttachRejCause14();
            break;

        /*#95,96,97,99,101,GU�´���AttachAttempCounter��Ϊ5*/
        case NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG:
        case NAS_LMM_CAUSE_INVALID_MANDATORY_INF:
        case NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
        case NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
        case NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE:

            /*����attach=5�Ĵ���*/
            NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

            break;

        /*����ԭ��ֵ������AttachAttempCounter��1��ֱ��AttachAttempCounterΪ5ʱL�Ŵ���*/
        default:

            NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

            break;
    }
}


VOS_VOID  NAS_EMM_GuRauActionRej( MsgBlock * pMsg  )
{
    /*�����ж��������ע����ֻ����ԭ��ֵ���д���*/
    NAS_EMM_GuCmbAndPsOnlyRauRej(pMsg);

}
VOS_VOID  NAS_EMM_GuCmbAndPsOnlyRauRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*���ΪCN_REJʱ��GUһ��Я��CN CAUSE,���ٶ�bitOpCnCause�ݴ�*/
    switch(pMmcActResult->ucCnCause)
    {
        /* #3,6��#3ԭ��ֵ����*/
        case    NAS_LMM_CAUSE_ILLEGAL_UE:
        case    NAS_LMM_CAUSE_ILLEGAL_ME:
            NAS_EMM_ProcGuDettRejCause3();
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_EMM_ProcGuDettRejCause7();
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            if (NAS_RELEASE_R11)
            {
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : CS_PS!!!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_ProcGuDettRejCause3();
            }
            else
            {
                /*�������PS Only������£�ԭ��ֵ8����other case����*/
                if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : PS_only!!!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL2);
                    NAS_EMM_ProcGuRauAttemptCounter(pMsg);
                }
                /*�������CS/PS������£�ԭ��ֵ8����ԭ��ֵ3�Ĵ���*/
                else
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : CS_PS!!!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL3);
                    NAS_EMM_ProcGuDettRejCause3();
                }
            }
            break;

        /*#9ԭ��ֵ����*/
        case    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED:

            NAS_EMM_ProcGuRauSerRejCause9();
            break;

        /*#10ԭ��ֵ����*/
        case    NAS_LMM_CAUSE_IMPLICIT_DETACHED:

            if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            {
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                            EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            }
            else
            {
                /*����CS�򱣳ֲ���,PS��ȥע��*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
            }

            break;

        /*#11,12*/
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW:

            NAS_EMM_ProcGuRauSerRejCause11();

            /*���TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            NAS_EMM_ProcGuRauSerRejCause14();

            /*���TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        /* #25ԭ��ֵ����other���� */
        /*#13,15*/
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL:
            NAS_EMM_ProcGuRauSerRejCause13();

            /*���TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        /*#95,96,97,99,101,GU�´���AttachAttempCounter��Ϊ5*/
        case    NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG:
        case    NAS_LMM_CAUSE_INVALID_MANDATORY_INF:
        case    NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
        case    NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
        case    NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE:

            /* ��RauAttmeptCounter�Ĵ���RauAttemptCounterΪ5������ΪEU2*/
            NAS_EMM_ProcGuRauAttemptCounter(pMsg);
            break;

        /*����ԭ��ֵ������RAUAttempCounter��1����RAUAttempCounter�Ĵ���*/
        default    :
            NAS_EMM_ProcGuRauAttemptCounter(pMsg);
            break;
    }
    return;
}


VOS_VOID  NAS_EMM_GuLauActionRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*���ΪCN_REJʱ��GUһ��Я��CN CAUSE,���ٶ�bitOpCnCause�ݴ�*/
    switch(pMmcActResult->ucCnCause)
    {
        case    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
        case    NAS_LMM_CAUSE_ILLEGAL_UE:
        case    NAS_LMM_CAUSE_ILLEGAL_ME:
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLauRst: LAU REJ,CAUSE2");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuLauActionRej_ENUM,LNAS_CAUSE_NUMBER);

                /* ���LAU���ܣ�ԭ��ֵΪ2����Lģ�������ܷ�������ATTACH������TAU */
                NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

                /*CSע�������Ϊȥע��,PSע���򲻱�*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();
                break;

        /*#11,#12,#13,#15��#3ԭ��ֵ����*/
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW:
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL:

                /*CSע�������Ϊȥע��,PSע���򲻱�*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();
                break;
        default:
                NAS_EMM_ProcGuLauAttemptCounter(pMsg);
                break;

    }
}
VOS_VOID  NAS_EMM_ProcGuRauAttemptCounter (MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 <= pMmcActResult->ulAttemptCount))
    {
        /* RauAttemptCounterΪ5������ΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /* lihong00150010 emergency tau&service begin */
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /* lihong00150010 emergency tau&service end */

        /*������ͽ����ΪPS_ONLYʱ,CS��PS�򲻱�,������ͽ����ΪCS+PSʱ,CS��ȥ
        ע��,PS�򱣳ֲ���*/
        if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
        {
            /*CS��ȥע��,PS�򱣳ֲ���*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }
    }

    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 > pMmcActResult->ulAttemptCount))
    {
        /* ���GPRS update status��ΪGU1������RAI�����������EPS update status
           ��ΪEU2 */
        if (NAS_EMM_SUCC == NAS_EMM_CheckGprsUpStateAndRaiChange(pMsg))
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcGuRauAttemptCounter:set eu2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /* lihong00150010 emergency tau&service begin */
            if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
            {
                /*����PS LOC��Ϣ*/
                NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
            }
            /* lihong00150010 emergency tau&service end */
        }

        /*������ͽ����ΪPS_ONLYʱ,CS��PS�򲻱�;������ͽ����ΪCS+PSʱ,MM Update
        state��ΪU1��LAI�ı�,CS��ȥע��,PS�򱣳ֲ���,����,CS��PS�򲻱�*/
        if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (NAS_EMM_SUCC == NAS_EMM_CheckMmUpStateAndLaiChange(pMsg)))
        {

            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcGuRauAttemptCounter:set eu2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_FUNCTION_LABEL2);

            /*CS��ȥע��,PS�򱣳ֲ���*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }
    }
    else
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProcGuRauAttemptCounter: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GuAttachSuccCommonProcess
 Description     : GU ATTACH�ɹ���������
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-09-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GuAttachSuccCommonProc( MsgBlock * pMsg )
{
    NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
    }
    else
    {
        /*����ǰע����ΪCS��NULL:���ΪCS,����ΪCS+PS;���ΪNULL,����ΪPS*/
        if (NAS_LMM_REG_DOMAIN_CS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
        }
        else
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
        }
    }

    /* If the UE initiates the first tracking area updating procedure following
       an attach in A/Gb mode or Iu mode, the UE shall include a UE radio
       capability information update needed IE in the TRACKING AREA UPDATE
       REQUEST message. �����GUģע��ɹ�����Ҫ���ϵ�һ��TAU��ʶ */
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_GuAttachSuccCommonProc:set first tau");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuAttachSuccCommonProc_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);
}


VOS_VOID NAS_EMM_ProGuAttachSucc
(
    MsgBlock                           *pMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED);
    if (NAS_RELEASE_R11)
    {
        /* ��ATTACH�ĳ��Դ������� */
        NAS_EMM_GLO_AD_GetAttAtmpCnt()      = 0;
    }

    if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
        || (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg)))
    {
        /* GU ATTACH�ɹ��������� */
        NAS_EMM_GuAttachSuccCommonProc(pMsg);
        return ;
    }

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCombiRstDomainPs(pMsg))
    {
        /* GU ATTACH�ɹ��������� */
        /*NAS_EMM_GuAttachSuccCommonProc(pMsg);*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*����CS��ȥע�ᣬPS��ע��*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProGuAttachSucc:set first tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuAttachSucc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);

        /* �������ATTACH,GPRS�ɹ�ONLY��ԭ��ֵΪ2����Lģ�������ܷ�������ATTACH������TAU */
        if ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
            && (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pMmcActResult->ucCnCause))
        {
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }

        return ;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuAttachRst
 Description     : ����״̬�£�����GU������ATTACH���
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Hanlufeng 41410      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuAttachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuAttachRst: ulActRst = .",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAttachRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*ֻ��������������ͬʱΪPS ONLY����PS/IMSIʱ��
      ��������ע��ֻ��PS�ɹ�������Я��ԭ��ֵΪ#2,16,17,22
      �����ΪSUCC*/
    if(MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProGuAttachSucc(pMsg);
    }

    /*GU����������Ӧ(��ʱ�͵ײ�ʧ��)���µ�ʧ��
      ������û��Я��ԭ��ֵʱ�Ĵ���,��ʱ��������ͽ����ΪPS ONLY��PS/IMSI��
      ������ΪPS/IMSI�����ΪPS ONLY��Ӧ��MMC_LMM_RSLT_TYPE_CN_REJ �� FAILURE��ʽ�·�
      ������ΪCS ONLY�����ΪCS ONLY������*/
    else if ( (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
            &&((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
             ||(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))))
    {

        /*ֻ��AttachAttempCounter=5ʱ�Ŵ���*/
        NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

    }

    /*GU��PS only��PS/IMSI������ܾ���
      ��������ΪPS/IMSI�������ΪPSʱ����CN_Rej֪ͨ��L
      ������ͽ������ж��ڴ������ڲ�*/
    else if(MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
    {

        NAS_EMM_GuAttachActionRej(pMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuAttachRst: ulActRst = .",
                            pMmcActResult->ulActRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAttachRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProGuRauRstSucc
 Description     : ����״̬�£�����GU������RAU�ɹ����
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-09-23  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuRauRstSucc
(
    MsgBlock                           *pMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /* lihong00150010 rrc connection failure begin */
    if (NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);
    }
    /* lihong00150010 rrc connection failure end */

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*����ǰע����ֻ��Ϊ:CS+PS��PS:�������ֶ����ֲ���*/

        return ;
    }

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCombiRstDomainPs(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /* �������RAU,GPRS�ɹ�ONLY��ԭ��ֵΪ2����Lģ�������ܷ�������ATTACH������TAU */
        if ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
            && (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pMmcActResult->ucCnCause))
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuRauRstSucc: RAU,GPRS ONLY,CAUSE2");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuRauRstSucc_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }

        /*����ǰע����ֻ��Ϊ:CS+PS��PS:���ΪCS+PS,����ΪPS;���ΪPS,�ͱ��ֲ���*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);


        return ;
    }

    /* ��GU��L����ϵͳ�任�������GU���������LAU��������RAU�ɹ�������Ҫ����TAU��
       TAU����Ϊcombined TA/LA with IMSI attach */
    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*����ǰע����ֻ��Ϊ:CS+PS��PS:�������ֶ�����ΪCS+PS*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);

        if (MMC_LMM_ACTION_PERIODC_RAU != pMmcActResult->enActionType)
        {
            /* ��¼GUģ�������������RAU�ɹ� */
            NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
        }


        return ;
    }
}


VOS_VOID NAS_EMM_ProGuRauRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuRauRst: ulActRst = .",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuRauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*������Ǳ�bar�������Ƿ������Ե�����rau����ͳһ����־��Ϊhappend*/
    if ((MMC_LMM_RSLT_TYPE_ACCESS_BARRED != pMmcActResult->ulActRst))
    {
        if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (MMC_LMM_ACTION_PERIODC_RAU != pMmcActResult->enActionType))
        {
            /* ��¼GUģ���������RAU */
            NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
        }
    }

    /*ֻ��������������ͬʱΪPS ONLY����PS/IMSIʱ��
      ��������ע��ֻ��PS�ɹ�������Я��ԭ��ֵΪ#2,16,17,22
      �����ΪSUCC*/
    if( MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProGuRauRstSucc(pMsg);
    }

     /*GU����������Ӧ(��ʱ�͵ײ�ʧ��)���µ�ʧ��
      ������û��Я��ԭ��ֵʱ�Ĵ���,��ʱ��������ͽ����ΪPS ONLY��PS/IMSI��
      ������ΪPS/IMSI�����ΪPS ONLY��Ӧ��MMC_LMM_RSLT_TYPE_CN_REJ �� FAILURE��ʽ�·�
      ������ΪCS ONLY�����ΪCS ONLY������*/
    else if ( (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
             &&( (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
               ||(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))))
    {
        /*��RauAttemptCounter������*/
        NAS_EMM_ProcGuRauAttemptCounter(pMsg);
    }
    else if(MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
    {

        /*����REJ��Ϣ����������CN REJ��causeֵ������*/
        NAS_EMM_GuRauActionRej(pMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuRauRst: ulActRst = .",
                            pMmcActResult->ulActRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuRauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);
    }

    return;
}

VOS_UINT32  NAS_EMM_CheckGuMtDetachTypeImsi( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_IMSI_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_IMSI_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_IMSI == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}


VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}


VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttRequ( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_REATTACH_REQUIRED == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}


VOS_VOID NAS_EMM_ProGuMtDetachRstCauseValue( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
    {
        switch(pMmcActResult->ucCnCause)
        {
            case NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
                /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
                   ��Lģ�������ܷ�������ATTACH������TAU */
                NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);


                /*CS��ȥע��,PS�򱣳ֲ���*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();


                break;

            /* #3,6,8��#3ԭ��ֵ���� */
            case NAS_LMM_CAUSE_ILLEGAL_UE:
            case NAS_LMM_CAUSE_ILLEGAL_ME:
            case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

                NAS_EMM_ProcGuDettRejCause3();
                break;

            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
                NAS_EMM_ProcGuDettRejCause7();
                break;


            /* dettach #11,12,13,15��ͬ dettach #11ԭ��ֵ���� */
            case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            case NAS_LMM_CAUSE_TA_NOT_ALLOW:
            case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            case NAS_LMM_CAUSE_NO_SUITABL_CELL:
                NAS_EMM_ProcGuDettachRejCause11();
                break;

            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
                NAS_EMM_ProcGuDettachRejCause14();
                break;


            /*����ԭ��ֵ��������ԭ��ֵʱ24008Э�������,GUδ����
              24301Dereg��ɾ��GUTI,LVR TAI,TAI LIST,KSI*/
            default:
                NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRstCauseValue: ucCnCause = , ulAttemptCount = ",
                        pMmcActResult->ucCnCause,
                        pMmcActResult->ulAttemptCount);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_CAUSE_NUMBER,
                        pMmcActResult->ucCnCause);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                        pMmcActResult->ulAttemptCount);

                /*����CS�򱣳ֲ���,PS��ȥע��*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);


                break;
        }

    }
    else
    {
        /*����ԭ��ֵ��������ԭ��ֵʱ24008Э�������,GU����Dereg.NormalService,
          �Ҵ�ʱGU����LЯ��ԭ��ֵIE�����ӿ�����
          24301Dereg��ɾ��GUTI,LVR TAI,TAI LIST,KSI*/
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRstCauseValue: ucCnCause = , ulAttemptCount = ",
                        pMmcActResult->ucCnCause,
                        pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_CAUSE_NUMBER,
                        pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                        pMmcActResult->ulAttemptCount);

        /*����CS�򱣳ֲ���,PS��ȥע��*/
        NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuMoDetachRst
 Description     : ����״̬�£�����GU������MO DETACH���
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-11-18   Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuMoDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuMoDetachRst: ulMoDetachType = ",
                            pMmcActResult->ulMoDetachType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->ulMoDetachType);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMoDetachType)
    {
        /* ����IMSI DETACH���� */
        if(MMC_LMM_MO_DET_CS_ONLY == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:Cs Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL2);

            /*����ǰע����Ϊ:CS+PS,CS��PS:���ΪCS+PS,����ΪPS;���ΪPS,���ֲ���,
            ���ΪCS,����ΪNULL*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();

        }

        /* ����EPS DETACH����*/
        else if(MMC_LMM_MO_DET_PS_ONLY == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:Ps Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL3);

            /*����ǰע����ֻ��Ϊ:CS+PS��PS:���ΪCS+PS,����ΪCS;���ΪPS,����ΪNULL*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        /*IMSI/EPS DETACH���� */
        else if(MMC_LMM_MO_DET_CS_PS == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:CS+PS Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL4);

            /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
            NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);
           /*����ǰע����ֻ��Ϊ:CS+PS��PS:����ΪNULL*/
        }
        /*���������ӡ*/
        else
        {
            /* �Ƿ���MO DETACH���ͣ������� */
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProGuMoDetachRst:Illegal Mo Detach Type");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL5);
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuLocalDetachRst
 Description     : ����״̬�£�����GU������LOCAL DETACH���
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-11-18   Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuLocalDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLocalDetachRst: ulLocalDetachType = ",
                            pMmcActResult->ulLocalDetachType);
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL1);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpLocalDetachType)
    {
        /* ����IMSI PGAING���͵ı���DETACH */
        if(MMC_LMM_GU_LOCAL_DET_IMSI_PAGING == pMmcActResult->ulLocalDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLocalDetachRst:Imsi Pgaing");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL2);

            /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
            /*����EU statusΪEU2*/
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,*/
            NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
             /*CS�򱣳ֲ���,PS��ȥע��*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        /* �����������͵ı���DETACH */
        else if(MMC_LMM_GU_LOCAL_DET_OTHERS == pMmcActResult->ulLocalDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLocalDetachRst:Others");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL3);

            /*����DEREG.EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
            NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

            /*ע�����ݲ�����*/

        }
        /*���������ӡ*/
        else
        {
            /* �Ƿ���LOCAL DETACH���ͣ������� */
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProGuLocalDetachRst:Illegal Local Detach Type");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL4);
        }
    }

    return;
}



VOS_VOID NAS_EMM_ProGuMtDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = , ulMtDetachType = ",
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
    {
        /*GU MT GPRS DETACH������3�֣�IMSI,RE_ATT_REQU,RE_ATT_NOT_REQU�������
          ���������DETACH TYPEת�����*/
        /*���ΪIMSI detachʱ���Ȳ����� causeֵ��EMMҲ����Ǩ״̬��EMM���账��*/

        if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypeImsi(pMsg))
        {
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = .",
                            pMmcActResult->ulReqDomain);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_EMM_REG_DOMAIN,
                            pMmcActResult->ulReqDomain);

            /*CS��ȥע��,PS�򱣳ֲ���*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }

        /*���ΪPS detach,re_attach_not_required�����ԭ��ֵ����*/
        else if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ(pMsg))
        {
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ucCnCause = .", pMmcActResult->ucCnCause);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
            NAS_EMM_ProGuMtDetachRstCauseValue(pMsg);
        }

        /*���ΪPS detach,re_attach_required Ǩ״̬*/
        else if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypePsReAttRequ(pMsg))
        {
            NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = , ulMtDetachType = ",
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);
            TLPS_PRINT2LAYER_INFO2(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL2,
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);

           /*CS�򱣳ֲ���,PS��ȥע��*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }

        /*���������ӡ*/
        else
        {
            /*�Ƿ�MT DETACH���ͣ�����������*/
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = .",
                            pMmcActResult->ulReqDomain);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL3,
                            pMmcActResult->ulReqDomain);
        }

    }

    return;
}
VOS_VOID NAS_EMM_ProGuLauRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*������Ǳ�bar����ͳһ����־��Ϊhappend*/
    if (MMC_LMM_RSLT_TYPE_ACCESS_BARRED != pMmcActResult->ulActRst)
    {
        /* ��¼GUģ���������LAU */
        NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
    }


    /* ��GU��L����ϵͳ�任�������GU���������LAU��������RAU�ɹ�������Ҫ����TAU��
       TAU����Ϊcombined TA/LA with IMSI attach */
    if (MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        /*���ΪNULL,����ΪCS;���ΪPS,����ΪCS+PS,����ע���򱣳ֲ���*/
        if (NAS_LMM_REG_DOMAIN_NULL == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
        }
        else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
        }
        else
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLauRst:Reg domain is not change");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLauRst_ENUM,LNAS_FUNCTION_LABEL1);
        }

        /* ��¼GUģ���������LAU�ɹ� */
        NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);

        return ;
    }

    /* LAU���ܾ�*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        NAS_EMM_GuLauActionRej(pstMsg);
        return ;
    }

    /* LAUʧ��*/
    if (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProcGuLauAttemptCounter(pstMsg);
        return;
    }
    /*LAU���뱻bar*/
    if (MMC_LMM_RSLT_TYPE_ACCESS_BARRED == pMmcActResult->ulActRst)
    {
        /*������*/

    }
    return;
}


VOS_VOID NAS_EMM_ProGuCmRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuCmRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*CN REJ*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        if (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_VLR == pMmcActResult->ucCnCause)
        {
            /*CSע�������Ϊȥע��,PSע���򲻱�*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }

        if (NAS_EMM_CAUSE_ILLEGAL_ME == pMmcActResult->ucCnCause)
        {
            /* ���CM���ܣ�ԭ��ֵΪ6����Lģ�������ܷ�������ATTACH������TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

            /*CSע�������Ϊȥע��,PSע���򲻱�*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }
    }

    /*�������ֵ������*/

    return;
}
VOS_VOID NAS_EMM_ProGuAbortRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAbortRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*CN REJ*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        if (NAS_EMM_CAUSE_ILLEGAL_ME == pMmcActResult->ucCnCause)
        {
            /* ���CM���ܣ�ԭ��ֵΪ6����Lģ�������ܷ�������ATTACH������TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

            /*CSע�������Ϊȥע��,PSע���򲻱�*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }
    }

    /*�������ֵ������*/

    return;
}




VOS_VOID NAS_EMM_ProGuServiceRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuServiceRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*Serviceֻ�账��CN REJ�����*/
    /* GU��Service REQ��PS ONLY��CS only���������ֻ����PS only */
    /*���ΪCN_REJʱ��GUһ��Я��CN CAUSE,���ٶ�bitOpCnCause�ݴ�*/
    if((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
     &&(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg)))
    {

        switch(pMmcActResult->ucCnCause)
        {
            /*#3,6��#3ԭ��ֵ����*/
            case NAS_LMM_CAUSE_ILLEGAL_UE:
            case NAS_LMM_CAUSE_ILLEGAL_ME:

                NAS_EMM_ProcGuDettRejCause3();
                break;
            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
                NAS_EMM_ProcGuDettRejCause7();
                break;
            case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_ProcGuDettRejCause3();
                }
                else
                {
                    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuDetachRst: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
                    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
                    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                                pMmcActResult->ulAttemptCount);
                }
                break;
            /*#9�Ĵ���*/
            case NAS_LMM_CAUSE_UE_ID_NOT_DERIVED:
                NAS_EMM_ProcGuRauSerRejCause9();
                break;

            /*#10�Ĵ���*/
            case NAS_LMM_CAUSE_IMPLICIT_DETACHED:

                 /*����CS�򱣳ֲ���,PS��ȥע��*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
                break;

            /*#11,12�Ĵ���*/
            case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            case NAS_LMM_CAUSE_TA_NOT_ALLOW:
                NAS_EMM_ProcGuRauSerRejCause11();
                break;

            /* #25ԭ��ֵ����other���� */
            /*#13,15,25*/
            case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            case NAS_LMM_CAUSE_NO_SUITABL_CELL:
                NAS_EMM_ProcGuRauSerRejCause13();
                break;

            /*other cause��GU abort service*/
            default    :
                NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuDetachRst: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);
                break;
        }
    }

    return;
}
VOS_VOID  NAS_EMM_GuActionClearRegInfo( VOS_UINT32 ulDeleteRplmn )
{
    /*ɾ��GUTI*/
    NAS_EMM_ClearGuti();

    /*ɾ��LVR TAI*/

    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }

    /*ɾ��KSI*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    /*����PS LOC��Ϣ*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
}
VOS_VOID  NAS_EMM_ProcGuAttRejCause3( VOS_VOID )
{
    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /* lihong00150010 emergency tau&service end */

    /*����DEREG.EMM_SS_DEREG_NO_IMSI��״̬*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    return;
}
VOS_VOID  NAS_EMM_ProcGuAttRejCause7( VOS_VOID )
{
    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /* lihong00150010 emergency tau&service end */

    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*����ǰע����״̬ΪCS��NULL:ע���򱣳ֲ���*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_IMSI);

    return;
}



VOS_VOID  NAS_EMM_ProcGuDettRejCause3( VOS_VOID )
{
    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /* lihong00150010 emergency tau&service end */

    /*����DEREG.EMM_SS_DEREG_NO_IMSI��״̬*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*����ǰע����ֻ��Ϊ:CS+PS��PS:����Э�����ע����ΪNULL*/

    return;
}


VOS_VOID  NAS_EMM_ProcGuDettRejCause7( VOS_VOID )
{
    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /* lihong00150010 emergency tau&service end */

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*����CS�򱣳ֲ���,PS��ȥע��*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_IMSI);

    return;
}
/*leili modify for cs domain end*/


VOS_VOID  NAS_EMM_ProcGuDettachRejCause11( VOS_VOID )
{
    /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*���Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*����ǰע����ֻ��Ϊ:CS+PS��PS:����Э�����ע����ΪNULL*/

    return;
}


VOS_VOID  NAS_EMM_ProcGuDettachRejCause14( VOS_VOID )
{
    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    /*���Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*����CS�򱣳ֲ���,PS��ȥע��*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}
/*leili modify for cs domain end*/

VOS_VOID  NAS_EMM_ProcGuAttachRejCause11( VOS_VOID )
{
    /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*���Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*���ܸ���ǰע����״̬,����Э��ע������Ҫ����ΪNULL*/
    return;
}


VOS_VOID  NAS_EMM_ProcGuAttachRejCause14( VOS_VOID )
{
    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008ɾ��GUTI, LVR TAI, TAI list and KSI,
      24301ɾ��GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*���Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*����ǰע����״̬ΪCS��NULL:ע���򱣳ֲ���*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}


VOS_VOID  NAS_EMM_ProcGuAttachAttemptCounterEq5( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 <= pMmcActResult->ulAttemptCount))
    {
        if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
        {
            /*����CSע���򲻱�,PSȥע��*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        else
        {
            /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬,ע����ΪNULL*/
            NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

            /*����ǰע����״̬ΪCS��NULL:����Э�����ע����ΪNULL*/
        }
        /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
        /*����EU statusΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*24.008GUTI, LVR TAI, TAI list and KSI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    }

    /*AttachAttempCounter<5ʱ��������ֻ��ӡ*/
    else
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProcGuAttachAttemptCounterEq5: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuAttachAttemptCounterEq5_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuAttachAttemptCounterEq5_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);

        /*����ǰע����״̬ΪCS��NULL:����Э��,������ͽ����ΪPS_IMSIʱ,
        LAI�����MM״̬��ΪU1,����ע����ΪNULL;��������,CS domain���ֲ���,PS��ȥע��;*/
        if((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (NAS_EMM_SUCC == NAS_EMM_CheckMmUpStateAndLaiChange(pMsg)))
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
        }
    }
    return;
}


VOS_VOID  NAS_EMM_ProcGuRauSerRejCause9( VOS_VOID )
{
    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU2*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*ɾ��GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
     /*����CS�򱣳ֲ���,PS��ȥע��*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}


VOS_VOID  NAS_EMM_ProcGuRauSerRejCause11( VOS_VOID )
{
    /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*����ǰע����ֻ��Ϊ:CS+PS��PS:����Э�����ע����ΪNULL*/

    return;
}
VOS_VOID  NAS_EMM_ProcGuRauSerRejCause14( VOS_VOID )
{
    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*����CS�򱣳ֲ���,PS��ȥע��*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}


VOS_VOID  NAS_EMM_ProcGuRauSerRejCause13( VOS_VOID )
{
    /*����EMM_SS_DEREG_NO_CELL_AVAILABLE��״̬*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*����EU statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /* lihong00150010 emergency tau&service end */

    /*����ǰע����ֻ��Ϊ:CS+PS��PS:���ע����ΪCS+PS,����ΪPS;���ע����ΪPS,���ֲ���*/
    NAS_EMM_ProcPsDomainRetainCsDomainNull();

    return;
}


VOS_VOID  NAS_EMM_ProcGuLauAttemptCounter(MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
        &&(4 <= pMmcActResult->ulAttemptCount))
       || ((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpLaiChangFlg)
        &&(VOS_TRUE == pMmcActResult->ucLaiChangFlg))
       || ((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCsUpdateStatus)
        &&(MMC_LMM_CS_UPDATE_STATUS_UPDATED != pMmcActResult->ucCsUpdateStatus)))
    {
        /*CSע�������Ϊȥע��,PSע���򲻱�*/
        NAS_EMM_ProcPsDomainRetainCsDomainNull();
    }
    return;
}
VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfBandNotSupport( VOS_VOID )
{
    /*add by lifuxin for Lnas est process re-construct start*/
    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_ProcRrcSysCfgCnfBandNotSupport");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfBandNotSupport_ENUM,LNAS_FUNCTION_LABEL1);
            break;
    }

    /* ��¼����ǰ��״̬*/
    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeSuspendAddr(),
                    NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    sizeof(NAS_LMM_FSM_STATE_STRU));

    /*��ESM ERABM��������Ϣ */
    NAS_EMM_SendEsmSuspendInd();

    /* ���� ERABM ������Ϣ */
    NAS_EMM_SendErabmSuspendInd();

    /* EMM״̬Ǩ��, ��������ʱ��*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* ��ǰ�� LTEΪ����̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}


VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfLteNotActive( VOS_VOID )
{

    /*add by lifuxin for Lnas est process re-construct start*/
    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            break;

        default:
            break;
    }

    /* ��¼����ǰ��״̬*/
    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeSuspendAddr(),
                    NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    sizeof(NAS_LMM_FSM_STATE_STRU));

    /*��ESM ERABM��������Ϣ */
    NAS_EMM_SendEsmSuspendInd();

    /* ���� ERABM ������Ϣ */
    NAS_EMM_SendErabmSuspendInd();

    /* EMM״̬Ǩ��, ��������ʱ��*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* ��ǰ�� LTEΪȥSUSPEND̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}



VOS_UINT32  NAS_LMM_ProcRrcSysCfgCnfNotSuspend(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    /* ��ӡ���뺯�� */
    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_ProcRrcSysCfgCnfNotSuspend is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfNotSuspend_ENUM,LNAS_ENTRY);

    /* L������ģ */
    if (NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_LMM_ProcRrcSysCfgCnfNotSuspend:  CUR_LTE_ACTIVE.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfNotSuspend_ENUM,LNAS_FUNCTION_LABEL1);

        /*add by lifuxin for Lnas est process re-construct start*/
        if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
        {
            /* ֹͣ ��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
        }
        /*add by lifuxin for Lnas est process re-construct end*/

        /* ��ȡEMM��ǰ״̬ */
        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                          NAS_EMM_CUR_SUB_STAT);


        /* ���ݲ�ͬ��״̬���в�ͬ���������¼UE���������仯
               ����ǰ�������⴦���״̬���ڴ��� */
        switch(ulCurEmmStat)
        {
            /* EMM_MS_REG_INIT��������״̬һ���� */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):

                    /* ��MMC�ظ���� */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* ��ֹATTACH���̣�����ATTACH */
                    ulRslt = NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                    /* ��MMC�ظ���� */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* ��GU�仯ֱ�ӷ���TAU����L�仯����DETACH������ATTACH */
                    ulRslt = NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):

                    /* ��MMC�ظ���� */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* ��GU�仯��δ��BAR������TAU����L�仯��δ��BAR������DETACH������ATTACH��
                       �类BAR, ����״̬���� */
                    ulRslt = NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):

                    /* ���������仯������ȼ����棬��δ�仯�������⴦��ֱ�ӻظ�MMC */
                    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
                    {
                        ulRslt = NAS_LMM_STORE_LOW_PRIO_MSG;
                    }
                    else
                    {
                        ulRslt = NAS_LMM_MSG_HANDLED;
                        (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
                    }
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):

                    /* ��MMC�ظ���� */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* ��ֹTAU��SER, ֱ���ͷ�, ת��REG.PLMN_SEARCH��ϵͳ��Ϣ */
                    ulRslt = NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc();
                    break;
            default:

                    /* ���������Ϊ�Ѵ���*/
                    /* ��MMC�ظ���� */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;
        }
    }
    else
    {
        /* L���ڴ�ģ�������⴦�� */
        /* ��MMC�ظ���� */
        (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
        ulRslt = NAS_LMM_MSG_HANDLED;
    }

    return ulRslt;
}
VOS_UINT32  NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulSysCfgRst = MMC_LMM_SUCC;
    VOS_UINT32                          ulSendResult;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_GetUplayerCount()++;

    /* ������ 2����ζ�� ESM��ERABM������� */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {
        /* ֪ͨRRC���� */
        NAS_EMM_SendLrrcSuspendReq();
    }

    /* ������ 3����ζ�� RRC����Ӧ����ζ�Ź���֪ͨ���  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_ALL <= NAS_EMM_GetUplayerCount())
    {
        /*syscfg�����SUSPEND�������ǰ�������ӣ�RRC������ID_LRRC_LMM_REL_IND������SUSPEND��Ӧ */
        /* ֹͣ��ʱ�� */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* ����˴ι�����ϲ���Ӧ��¼���ָ����̽�ʹ�� */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /*��������Դ*/
        /* ��ո�����ȫ�ֱ�����ͬʱ������T3412��T3423��ֹͣ����Э��״̬��ʱ��, */
        NAS_EMM_SuspendInitRelResource();

        /* ����ɹ���֮ǰ��GU��L����ϵͳ�任���������ͼ�¼��Ϣ������� */
        NAS_EMM_ClearResumeInfo();

        /*��ֹͣT3412*/

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

        NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);
        /* �����������״̬ */
        NAS_EMM_SuspendEndStateChng();

        /* ��MMC�ظ�SYS CFG���*/
        ulSendResult = NAS_LMM_SendMmcSysCfgCnf(ulSysCfgRst);

        if (NAS_EMM_SEND_RRC_OK != ulSendResult)
        {
            /* ��ӡ������ERROR_LEVEL */
            NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SendMmcSysCfgCnf : Send Msg Failure!!! ulSendResult=",
                                     ulSendResult);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp_ENUM,LNAS_SND_RST,
                                     ulSendResult);
        }
    }

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp_ENUM,LNAS_ENTRY);

    /*�յ���Ϣ��������2��˵��ESM��RABM�Ļظ���Ϣ��û����ȫ*/
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM > NAS_EMM_GetUplayerCount())
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_ECM_FAIL);
    }
    else
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_RRC_FAIL);
    }

    /* ����˴ι�����ϲ���Ӧ��¼ */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY         2012-02-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;
    NAS_EMM_TAU_LOG_INFO(               "NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq_ENUM,LNAS_ENTRY);
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR(            "NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc(VOS_VOID)
{

    /* ��ӡ���뺯�� */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    /* ���UE�������������仯 */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc: UE radio capability is changed, re-attach needed!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* ֹͣATTACH��ʱ�� */
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

        /* �޸�״̬��������״̬DEREG��״̬DEREG_PLMN_SEARCH,��ʱ����״̬���ϱ��ı�*/
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                           EMM_SS_DEREG_PLMN_SEARCH ,
                           TI_NAS_EMM_STATE_NO_TIMER);

        /* ֪ͨESM�����Դ */
        NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* �����������̬��ֱ�ӷ����ͷ���Ϣ */
        if(NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            /*����RRC_MM_REL_REQ*/
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        }

        /* ת��DEREG.PLMN-SEARCH̬���յ�ϵͳ��Ϣ��Ȼ�ᷢ��ATTACH */
    }

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc(VOS_VOID)
{
    NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId;

    /* ��ӡ���뺯�� */
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_ENTRY);

    /* ���GU�����仯��T3411��T3402δ����������TAU */
    if ((NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
        &&(NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc: TAU  start !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
    }

    /* ���LTE�����仯������DETACH�����TAU��SER��Դ, ת��DEREG.NORMAL-SERVICE������ATTACH */
    else if (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc: LTE change, local detach and re-attach needed.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL2);
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc:  Connected.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL3);

            /*���SYSCFG���µı���DETACH��MMC���ͷŲ���Ӧ���������⣬��RRC���ͷ�
                 ѹջ������Ϊ�˷�ֹ����SERVICE���� */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            return NAS_LMM_MSG_HANDLED;
        }
        /* ����DETACH֮������ATTACH  */
        NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc();
    }
    else
    {
        /* �ޱ仯�������⴦�� */
    }

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc(VOS_VOID)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    /* ��ӡ���뺯�� */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG== NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: UE Radio capability is not changed. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* �����TAU�����У���ֹTAU */
    if (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: TAU procedure is stopped. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL2);

        /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ */
        ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif
    }

    /* �����Ȼ��SER�����У���ֹSER*/
    else
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: SER procedure is stopped. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_SER_AbnormalOver();
    }

    /* ת��REG.PLMN-SEARCH��ϵͳ��Ϣ */
    NAS_EMM_AdStateConvert(EMM_MS_REG,
                           EMM_SS_REG_PLMN_SEARCH,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /* ȫ�����ͷţ�RRC�ڿ���̬������̬���������ͬ */
    /* �����������̬��ֱ�ӷ����ͷ���Ϣ */
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: Connected! SndRrcRelReq. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL4);

    /*����RRC_MM_REL_REQ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc(VOS_VOID)
{

    /* ��ӡ���뺯�� */
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    /* GU�����仯 */
    if (NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* �������Ƿ�BAR����: TAU;   ��: �������⴦�� */
        if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: TAU  start");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);

            /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        }
    }

    /* LTE�����仯 */
    else if (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: LTE  radio capability is changed.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL2);


        /* �������Ƿ�BAR����: ����DETACH��ת��DEREG.NORMAL̬�����ڲ�ATTACH;
                            ��: ����״̬���� */
        if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: MO_SIGNAL  isn't  barred.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL3);

            /* ����DETACH֮������ATTACH */
            NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc();
        }
    }
    else
    {
        /* �ޱ仯�������⴦��*/
    }

    return  NAS_LMM_MSG_HANDLED;
}

VOS_VOID  NAS_EMM_MsRegInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    /*���ݵ�ǰ��״̬���� */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_ATTACH_WAIT_ESM_PDN_RSP:
            /* ע��������ֹ��ͣ��ʱ�������Դ�����1�����ݳ��Դ�������֪ͨESM����DETACHED̬��������������*/
             NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_PDN_RSP);
             NAS_EMM_EsmSendStatResult(       EMM_ESM_ATTACH_STATUS_DETACHED);

             NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
             NAS_EMM_AppSendAttFailWithPara();
             NAS_EMM_AttNrmFailProc();

             (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);

            break;

        default:

            /*ͣATTACH���״̬��ʱ��������ATTACH���Դ��������ݳ��Դ������д���
            ��MMC�ϱ�ATTACHʧ�ܣ�֪ͨESM����DETACHED����RRC����·�ͷ�����ѹջ*/
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_RRC_DATA_CNF);

            NAS_EMM_TAU_SendEsmStatusInd(  EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
            NAS_EMM_AppSendAttFailWithPara();
            NAS_EMM_AttNrmFailProc();

            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

            break;
    }

}

VOS_VOID  NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    /*���ݵ�ǰ��״̬���� */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_DETACH_WAIT_CN_DETACH_CNF:
            /* ����DETACH���Դ���Ϊ0��ֹͣDETACH���״̬��ʱ������MMC����DETACH�ɹ�
               ֪ͨESM����DETACHED��ת��DEREG+NORMAL_SERVICE̬����RRC����·�ͷ�����ѹջ*/
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

            #if (FEATURE_ON == FEATURE_DSDS)
            /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
            NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
            #endif

            NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

            /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

            break;



        default:
            break;
    }

}

VOS_VOID  NAS_EMM_MsSerInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*���ݵ�ǰ��״̬���� */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_SER_WAIT_CN_SER_CNF:

            /* ����SERVICE���������ֱ���*/
            if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
               NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
               NAS_EMM_SER_ClearResource();
               NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);


               /*֪ͨERABM SERVICE ����ʧ��*/
               NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

               NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            #if (FEATURE_LPP == FEATURE_ON)
            else if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
                NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
                NAS_EMM_SER_ClearResource();
                NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*֪ͨERABM SERVICE ����ʧ��*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }

            else if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
                NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                        NAS_EMM_SER_GetSsOrLppOpid());
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
                NAS_EMM_SER_ClearResource();
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*֪ͨERABM SERVICE ����ʧ��*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            #endif
            else if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            {
                /* ����Ѿ��յ�ABORT��Ϣ�� */
                if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_MsSerInitRcvLrrcSuspendIndProc:CSFB is already aborted!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitRcvLrrcSuspendIndProc_ENUM,LNAS_FUNCTION_LABEL1);

                    /* ��LRRC��Ӧ����ʧ�� */
                    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);

                    NAS_EMM_SER_ClearResource();

                    /* ״̬��Ϊ reg.normal service */
                    NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
                }
                else
                {
                    (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                }
            }
            else
            {/* lihong00150010 emergency tau&service begin */
                NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
                /*NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);*/
            /* lihong00150010 emergency tau&service end */
                /*֪ͨERABM SERVICE ����ʧ��*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_SER_ClearResource();

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }

            break;

        default:
            break;
    }

}

VOS_VOID  NAS_EMM_MsTauInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    /* ���쳣ʧ�ܴ���,��MMC�ϱ�ʧ��,������������*/
    ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);

    return;
}
VOS_VOID  NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    /* ͣT3418��T3420��ʱ����ת��AUTH_INIT+WAIT_REL_IND̬����RRC����·�ͷ�����ѹջ*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3420);



    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

}
VOS_VOID  NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc( VOS_VOID)
{
    if (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc:T3440 is running");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc_ENUM,LNAS_EMM_T3440_RUNNING);

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*����RRC_MM_REL_REQ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);
    }
    else
    {
        /*���ݽӿ����������� */
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc: discard. state = ",
                        NAS_EMM_CUR_MAIN_STAT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc_ENUM,LNAS_EMM_MAIN_STATE,
                        NAS_EMM_CUR_MAIN_STAT);
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
    }
    return;
}


VOS_VOID  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc(VOS_VOID)
{
    NAS_LMM_FSM_STATE_STRU             *pstStatBeforeSuspend  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulStatBeforeSuspend;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId;

    pstStatBeforeSuspend   =  NAS_EMM_GetStateBeforeSuspendAddr();

    ulStatBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(pstStatBeforeSuspend->enMainState,
                                        pstStatBeforeSuspend->enSubState);

    switch (ulStatBeforeSuspend)
    {
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
            /* ���T3430�Ѿ���ʱ,����T3430��ʱ���д���*/
            if (NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_TAU_T3430))
            {
                /*TAU ATTEMPT COUNT ++*/
                NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

                /*������Ϣ������*/
                NAS_EMM_TAU_RcvT3430Exp();
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
            /* ���T3417EXT��ʱ,���ոö�ʱ����ʱ���� ,�жϹ���֮ǰ������CSFB����,֮ǰ�����״̬����ʱ,���CSFB,���������ԭ��*/
            if ((NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3417_EXT))
                 && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
            {

                NAS_EMM_SER_AbnormalOver();

                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_NULL);

                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT, NAS_LMM_CAUSE_NULL);

                /*ת��EMM״̬��MS_REG+EMM_SS_REG_NORMAL_SERVICE*/
                NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

                if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
                {
                    /* �����δ��ɵ�TAU������յ�ϵͳ��Ϣ���ٴ��� */


                    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }

            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_ATTEMPTING_TO_ATTACH):
            /* ���3411��3402���ѳ�ʱ,����T3411��ʱ���� */
            if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            {
                /*����ATTATCH*/
                NAS_EMM_AD_Reattach();
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
            /* ���3411��3402���ѳ�ʱ,����T3411��ʱ���� */
            if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            {
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /*������Ϣ������*/
                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_MMC_SUSPEND_FAIL);
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            /* ���3411�Ѿ���ʱ,��Ҫ�ж�TAU��������*/
            if (NAS_LMM_TIMER_STOPED == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
            {
                /*����������ܹ�����TAU�ĳ���*/
                NAS_EMM_RegSomeStateMsgSysInfoCommProc();
            }
            break;
        default:
            /* �������������� */
            break;


    }

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */
