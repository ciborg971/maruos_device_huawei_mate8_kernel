

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasLmmPubMStack.h"

#include "NasEmmPubUSuspend.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmLppMsgProc.h"
#include "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICESERSTOP_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICESERSTOP_C
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




VOS_UINT32 NAS_EMM_MsSerInitMsgRabmDrbSetupInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
    VOS_UINT32                      ulRslt                  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitMsgRabmDrbSetupInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN("NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitMsgRabmDrbSetupInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*������Ϣ������*/
    NAS_EMM_SER_RcvRabmDrbSetupInd(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


VOS_VOID NAS_EMM_SER_SndEsmBufMsg( VOS_VOID )
{
    EMM_ESM_DATA_REQ_STRU                *pstMsg = NAS_LMM_NULL_PTR;
    VOS_UINT32                            i      = 0;
    VOS_UINT32                            ulRslt = 0;
    VOS_UINT32                            ulCurEmmStat;

    /* lihong00150010 emergency tau&service begin */
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);
    if ((ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SndEsmBufMsg:state is not allowed to send msg.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SndEsmBufMsg_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_SerClearEsmDataBuf();
        return ;
    }
    /* lihong00150010 emergency tau&service end */

    for (i = 0; i < g_stEmmEsmMsgBuf.ulEsmMsgCnt; i++)
    {
       pstMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[i];

       /*��ESM��Ϣ*/
       NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstMsg->stEsmMsg, pstMsg->ulOpId);
       ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pstMsg);

       if (NAS_COMM_BUFF_SUCCESS != ulRslt)
       {
           NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_RcvRabmDrbSetupInd, Memory Free is not succ");
           TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_SndEsmBufMsg_ENUM,LNAS_FUNCTION_LABEL2);

       }

       g_stEmmEsmMsgBuf.apucEsmMsgBuf[i] = NAS_LMM_NULL_PTR;
    }

    g_stEmmEsmMsgBuf.ulEsmMsgCnt = 0;
}
VOS_VOID    NAS_EMM_SER_RcvRabmDrbSetupInd(const VOS_VOID   *pMsgStru)
{
    NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType = NAS_LMM_OM_TAU_START_TYPE_OTHERS;
    (VOS_VOID)pMsgStru;

    /* Э��涨EXTENDED SERVICE���̳ɹ���ֹ�ı�ʶ����ϵͳ�任��������DRB���� */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /*ת����ȫ������״̬*/
        NAS_EMM_SecuStateConvert(   EMM_CUR_SECU_EXIST_ACTIVE,
                                    NAS_LMM_GetSecuCurFsmNS());

        return ;
    }
    /* ������: ����SER�ɹ����� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);
    /* ������: ��¼Ser���̽���ʱ�� */
    NAS_EMM_SaveSerEndTimeStamp();
    /*ֹͣ��ʱ��3417*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת����ȫ������״̬*/
    NAS_EMM_SecuStateConvert(   EMM_CUR_SECU_EXIST_ACTIVE,
                                NAS_LMM_GetSecuCurFsmNS());

    /*����SER�Ľ��ΪNAS_EMM_SER_RESULT_SUCC*/
    /*NAS_EMM_SER_SaveSERresult(NAS_EMM_SER_RESULT_SUCC);*/
    /* lihong00150010 emergency tau&service begin */
    /*SR���̳ɹ������SR����������SMS��������Ҫ�ظ�SMS�����ɹ�*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmSmsEstCnf();
        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_SUCC,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif

    NAS_EMM_TranStatePsNormalServiceOrPsLimitService();

    /* ���ͻ����ESM��Ϣ*/
    NAS_EMM_SER_SndEsmBufMsg();

    NAS_EMM_SER_ClearResource();

    /* ���RRC��·�ͷŴ���TAU��ԭ�� */
    /*NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);*/

    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_NO);

    /* ����AT&T��������: SER�ɹ����CService���� */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_REG+SS_REG_NORMAL_SERVIC*/
    /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/

    /*����в������������߳��ظ����仯��TAUδ��ɣ��򴥷���TAU
      ע:�ó���һ��������̬�´���TAU������Ҫ�ж���������*/
    if (NAS_EMM_YES == NAS_EMM_SER_SuccNeedtoContinueTau(&enTauStartType))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRabmDrbSetupInd: Need to Continue Tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);

        if(NAS_LMM_TIMER_STOPED == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(enTauStartType);
        }
    }
    else
    {
        if (NAS_EMM_YES != NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* ��RRC����ʧ�ܴ�����TAUʧ�ܣ�T3411�������е�ʱ��service�ɹ�����ʱ�Ͳ����ٷ���TAU��
            ����ģ�LMM��Ҫ��MMC��һ����TAU�ɹ�����Ϣ��֪ͨMMC��ǰTAU�Ѿ��ɹ����Ա�MMC����״̬*/
            if(NAS_EMM_TRIGGER_TAU_RRC_REL_NO != NAS_LMM_GetEmmInfoTriggerTauRrcRel())
            {
                NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRabmDrbSetupInd: send tau result");
                NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
            }
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

            /*���TAU��Դ��ע��:��NAS_EMM_SER_SndEsmBufMsg��ִ��˳���ܵߵ�*/
            NAS_EMM_TAU_ClearResouce();

        }

    }


    return;
}
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerAbortNotify( MsgBlock * pMsg )
{
    VOS_UINT32                          ulCurEmmStat    = NAS_EMM_NULL;
    /*VOS_UINT32                          ulStaAtStackBase= NAS_EMM_NULL;*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_ENTRY);

    (VOS_VOID)pMsg;

    /* ��¼CSFB ABORT��ʶ */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_VALID);

    /* ���CSFBʱ�Ӷ�ʱ�������У���ֹCSFB���̣�����Ѿ�����TAU��SER�����������ʱ��ABORT��ʶ���д��� */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
    /*add by lifuxin for extra TAU issue 2015-06-18 start*/
    /*���õ�ǰ��EUֵ��csfb���̱�ʶΪ�������²���*/
    if(PS_TRUE == NAS_EMM_GetCsfbProcedureFlag())
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
    }
    /*add by lifuxin for extra TAU issue 2015-06-18 end*/

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    /* MM��ֹCSFB����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

    /* ���LMM��ǰ״̬Ϊ����������ʱ��״̬Ϊ��SERVICE_INIT+WAIT_SER_CN_CNF��
       ����CSFB����ʱ����ֹCSFB���̣���RRC����·�ͷ���������������¼
       ABORT��ʶ */
    /*add by lifuxin for Lnas est process re-construct start*/
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: esting.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL1);

        if ((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SubState =",
                                EMM_SS_SER_WAIT_CN_SER_CNF);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_EMM_SUB_STATE,
                                EMM_SS_SER_WAIT_CN_SER_CNF);

            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /* ����RRC��·�ͷ� */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
        }
    }
    /*add by lifuxin for Lnas est process re-construct end*/
    /* ��״̬�� EMM_MS_SUSPEND + EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND */
    else if (ulCurEmmStat ==
                NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_SUSPEND,
                                            EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: WAIT_OTHER_SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL1);

        /* ֹͣ��ʱ�� */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* ����˴ι�����ϲ���Ӧ��¼���ָ����̽�ʹ�� */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;
        /* ��LRRC�ظ�SUSPEND RSP(SUCC)�����LRRC�յ�SUSPEND REL REQֹͣ�������̣���������פ�����ϱ�RESUME IND���� */
        /* ���� LRRC_LMM_SUSPEND_RSP*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_SUCC);

        /*����LRRC_LMM_SUSPEND_REL_REQ��Ϣ*/
        NAS_EMM_SndLrrcSuspendRelReq();


        NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SuspendRelCause =",
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_CAUSE_NUMBER,
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);

        /* ״̬Ǩ��*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                        EMM_SS_SUSPEND_WAIT_END,
                                        TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    }

    /* ��״̬�� EMM_MS_SUSPEND + EMM_SS_SUSPEND_WAIT_END */
    else if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_SUSPEND,
                                                    EMM_SS_SUSPEND_WAIT_END))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SUSPEND_WAIT_END.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL2);

        /*����LRRC_LMM_SUSPEND_REL_REQ��Ϣ*/
        NAS_EMM_SndLrrcSuspendRelReq();

        NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SuspendRelCause =",
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_CAUSE_NUMBER,
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);


    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: no other action.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL3);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




