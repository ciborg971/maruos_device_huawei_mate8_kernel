

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmEmmMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmETcMsgProc.h"
#include  "LUPAppItf.h"
/*#include  "R_ITF_FlowCtrl.h"*/
#include  "NasERabmCdsMsgProc.h"
#include  "CdsInterface.h"



/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMEMMMSGPROC_C
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
/* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER Ĭ��ʱ�� */
VOS_UINT32             g_ulErabmRfRecoveryTimerLength = 60000;


/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID NAS_ERABM_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg = VOS_NULL_PTR;

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_EmmMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pEmmMsg->ulMsgName)
    {
        /*����յ�����EMM_ERABM_REEST_IND��Ϣ������NAS_ERABM_RcvRabmEmmReest_Ind����*/
        case ID_EMM_ERABM_REEST_IND:
            NAS_ERABM_RcvRabmEmmReestInd((EMM_ERABM_REEST_IND_STRU*)pRcvMsg);
            break;

        /*����յ�����EMM_ERABM_REL_IND��Ϣ������NAS_ERABM_RcvRabmEmmRelInd����*/
        case ID_EMM_ERABM_REL_IND:
            NAS_ERABM_RcvRabmEmmRelInd();
            break;

        case ID_EMM_ERABM_RRC_CON_REL_IND:
            NAS_ERABM_RcvRabmEmmRrcConRelInd((EMM_ERABM_RRC_CON_REL_IND_STRU *)pRcvMsg);
            break;

        case ID_EMM_ERABM_SUSPEND_IND:
            NAS_ERABM_RcvRabmEmmSuspendInd( (EMM_ERABM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        case ID_EMM_ERABM_RESUME_IND:
            NAS_ERABM_RcvRabmEmmResumeInd( (EMM_ERABM_RESUME_IND_STRU *) pRcvMsg );
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_EmmMsgDistr:WARNING:EMM->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}


/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ERABM_RcvRabmEmmReestInd(const EMM_ERABM_REEST_IND_STRU *pRcvMsg )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmEmmReestInd:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    switch(pRcvMsg->enReEstState)
    {
        /*case EMM_ERABM_REEST_STATE_SUCC:*/
        case EMM_ERABM_REEST_STATE_FAIL:

            /*��ӡ����ú���*/
            NAS_ERABM_LOG1("NAS_ERABM_RcvRabmEmmReestInd: receive Emm Reset result: .",
                          pRcvMsg->enReEstState);
            TLPS_PRINT2LAYER_INFO1(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_EmmResetResult, pRcvMsg->enReEstState);
            if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
            {
                /* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER����ʱ,�������Իָ���·,�������̬RF����,
                    UE����IDLE̬������UE������״̬��һ������ */
                break;
            }
            /*SERVICE���̽���*,ֹͣ��ʱ��*/
            NAS_ERABM_TimerStop(NAS_ERABM_WAIT_RB_REEST_TIMER);
            NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);
            /* ���������ģʽ�� */
            if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
            {
                /* ֪ͨL2�ͷŻ�������ݰ� */
                /*APPITF_FreeAllofRabmBuf();*/

                /* ֪ͨCDS�ͷŻ�������ݰ� */
                NAS_ERABM_SndErabmCdsFreeBuffDataInd();

                /* �����������������־*/
                NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
            }
            else if (NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER))
            /*����ģʽ�²������棬����ԭ��������Pending״̬*/
            {
                NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER start.");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL1);
                /* lihong00150010 emergency tau&service begin */
                NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH,
                                        NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER,
                                        NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
            }   /* lihong00150010 emergency tau&service end */
            else
            {
                NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER is running.");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL2);
            }
            break;

        case EMM_ERABM_REEST_STATE_INITIATE:

            /*��ӡ����ú���*/
            NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: receive EMM_ERABM_REEST_STATE_INITIATE .");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL3);
            /*SERVICE��������,������ʱ��*/
            if (NAS_ERABM_SERVICE_STATE_TERMIN == NAS_ERABM_GetEmmSrState())
            {/* lihong00150010 emergency tau&service begin */
                NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                        NAS_ERABM_WAIT_RB_REEST_TIMER,
                                        VOS_FALSE);
                NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_INIT);
            }/* lihong00150010 emergency tau&service end */
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmEmmReestInd:WARNNING: EstState illegal!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_EstStateillegal);
            break;
    }
}
VOS_VOID  NAS_ERABM_RcvRabmEmmRelInd( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ENTRY);

    /* ֪ͨCDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* ��CDS����CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }

    /*�ͷ�������Դ,�ص�������ʼ�����״̬*/
    NAS_ERABM_ClearRabmResource();

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

}


VOS_VOID  NAS_ERABM_RcvRabmEmmRrcConRelInd( EMM_ERABM_RRC_CON_REL_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRrcConRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRrcConRelInd_ENUM, LNAS_ENTRY);

    NAS_ERABM_TimerStop( NAS_ERABM_WAIT_RB_RESUME_TIMER);

    NAS_ERABM_TimerStop( NAS_ERABM_WAIT_RB_REEST_TIMER);

    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*ֹͣ�����ȴ���ʱ��*/
    NAS_ERABM_TimerStop(NAS_ERABM_WAIT_EPSB_ACT_TIMER);

    /*����ȴ����ؽ�����ʶ */
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);


    /* ���������ģʽ�� */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        /* ֪ͨL2�ͷŻ�������ݰ� */
        /*APPITF_FreeAllofRabmBuf();*/

        /* ��ϵͳ�л��ɹ���RRC���ϱ���·�ͷ���DRB�����˳�������֪ͨCDS�建�� */
        if (NAS_ERABM_L_MODE_STATUS_NORMAL == NAS_ERABM_GetLModeStatus())
        {
            /* (1)�����ǰ������Pending ��ʶ���������ݻ���,���CDS���ͷŻ��� */
            /* (2)�����Ѽ���DRB,���CDS���ͷŻ��� */
            if((EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_GetUpDataPending())
               || ((NAS_ERABM_FAILURE == NAS_ERABM_IsAllActtiveBearerWithoutDrb())
                    && (NAS_ERABM_NULL != NAS_ERABM_GetActiveEpsBearerNum())))
            {
                /* ֪ͨCDS�ͷŻ�������ݰ� */
                NAS_ERABM_SndErabmCdsFreeBuffDataInd();

                /* �����������������־ */
                NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
            }
        }

    }
    else  /*����ģʽ�²������棬����ԭ��������Pending״̬*/
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRrcConRelInd: Do not release buffer .");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRrcConRelInd_ENUM, LNAS_ERABM_NotReleaseBuffer);
    }
    /* �ͷ�ԭ��ֵΪNO RF��DRB��������0 */
    if((EMM_ERABM_REL_CAUSE_NO_RF == pRcvMsg->enRelCause)&&(NAS_ERABM_FAILURE== NAS_ERABM_IsAllActtiveBearerWithoutDrb()))
    {   /* �ͷ�ԭ��ֵΪNO_RFʱ��������ʱ��NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER������RRMע��֪ͨ
           ��NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER��ʱ�������ڼ䣬�յ�RRM��RF��Դ֪ͨʱ������RB�ؽ���
           ʹUE������״̬����һ�� */
        if(NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
        {
            NAS_ERABM_TimerStart(   NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH,
                                    NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER,
                                    VOS_FALSE);
            NAS_ERABM_SndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
        }
        /* ��������DATA PENDING��־ */
        NAS_ERABM_SetUpDataPending(EMM_ERABM_UP_DATA_PENDING);
    }

    /* �ͷ�����RB */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        NAS_ERABM_RcvRbRelease(ulEpsbId);
    }
    return;
}



VOS_VOID NAS_ERABM_SndRabmEmmReestReq
(
    VOS_UINT32                          ulIsEmcType
)
{
    EMM_ERABM_REEST_REQ_STRU    *pstReestReq = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstReestReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(
                                        sizeof(EMM_ERABM_REEST_REQ_STRU));
    if ( VOS_NULL_PTR == pstReestReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmReestReq:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_MSG_ENTITY(pstReestReq), NAS_ERABM_NULL,\
                     NAS_ERABM_GET_MSG_LENGTH(pstReestReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstReestReq, ID_EMM_ERABM_REEST_REQ);
    /* lihong00150010 emergency tau&service begin */
    pstReestReq->ulIsEmcType = ulIsEmcType;
    /* lihong00150010 emergency tau&service end */
    /* ������Ϣ���ͺ��� */
    NAS_ERABM_SND_MSG(pstReestReq);

}


VOS_VOID NAS_ERABM_SndRabmEmmDrbSetupInd( VOS_VOID )
{
    EMM_ERABM_DRB_SETUP_IND_STRU    *pstDrbSetInd = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstDrbSetInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(
                                        sizeof(EMM_ERABM_DRB_SETUP_IND_STRU));
    if ( VOS_NULL_PTR == pstDrbSetInd )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmDrbSetupInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_MSG_ENTITY(pstDrbSetInd), NAS_ERABM_NULL,\
                     NAS_ERABM_GET_MSG_LENGTH(pstDrbSetInd));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstDrbSetInd, ID_EMM_ERABM_DRB_SETUP_IND);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstDrbSetInd);

}


VOS_VOID NAS_ERABM_SndRabmEmmRelReq( VOS_VOID)
{
    EMM_ERABM_REL_REQ_STRU    *pstRelReq  = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRelReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstRelReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmRelReq:ERROR:Alloc msg fail!" );
        return;
    }

    NAS_ERABM_MEM_SET(NAS_ERABM_GET_MSG_ENTITY(pstRelReq), NAS_ERABM_NULL,\
                     NAS_ERABM_GET_MSG_LENGTH(pstRelReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRelReq, ID_EMM_ERABM_REL_REQ);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstRelReq);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmSuspendRsp
 Description     : ERABMģ��ظ�ID_EMM_ERABM_SUSPEND_RSP��Ϣ
 Input           : EMM_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmSuspendRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
)
{
    EMM_ERABM_SUSPEND_RSP_STRU          *pstRabmEmmSuspendRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRabmEmmSuspendRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_SUSPEND_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRabmEmmSuspendRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmSuspendRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ERABM_MEM_SET( NAS_ERABM_GET_MSG_ENTITY(pstRabmEmmSuspendRsp), 0, NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmSuspendRsp));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRabmEmmSuspendRsp, ID_EMM_ERABM_SUSPEND_RSP);

    /*��д��Ӧ���*/
    pstRabmEmmSuspendRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ERABM_SND_MSG(pstRabmEmmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmResumeRsp
 Description     : ESMģ��ظ�ID_EMM_ERABM_RESUME_RSP��Ϣ
 Input           : EMM_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmResumeRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
)
{
    EMM_ERABM_RESUME_RSP_STRU            *pstRabmEmmResumeRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRabmEmmResumeRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_RESUME_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRabmEmmResumeRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmResumeRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ERABM_MEM_SET( NAS_ERABM_GET_MSG_ENTITY(pstRabmEmmResumeRsp), 0, NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmResumeRsp));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRabmEmmResumeRsp, ID_EMM_ERABM_RESUME_RSP);

    /*��д��Ӧ���*/
    pstRabmEmmResumeRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ERABM_SND_MSG(pstRabmEmmResumeRsp);
}
EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32 NAS_ERABM_IsDataPending( VOS_VOID )
{
    /* ����CDS��¼�Ƿ������л������ݣ��Լ�RABM��¼�Ƿ�����������PENDING��ͬ���� */
    return (EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32)(CDS_IsPsDataAvail()||NAS_ERABM_GetUpDataPending());
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmSuspendInd
 Description     : ERABMģ���յ�ID_EMM_ERABM_SUSPEND_IND������
 Input           : EMM_ERABM_SUSPEND_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-03      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmSuspendInd(const EMM_ERABM_SUSPEND_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId        = NAS_ERABM_NULL;
    VOS_UINT8                           ucTimerIndex    = NAS_ERABM_NULL;

    /* ����״̬Ϊ����̬ */
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_SUSPENDED);
    if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* ȥע��RF��Դ֪ͨ */
        NAS_ERABM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
        /* ֹͣ��ʱ��NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER */
        NAS_ERABM_TimerStop(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER);
    }

    /* ֹͣ��ʱ�� */
    for (ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++)
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }
    /* ������л���CCO���͵Ĺ�����ɾ��DRB��Ϣ��ֻ��DRB��״̬��ΪNAS_ERABM_RB_SUSPENDED��
       ��ΪL-GU�л�����CCOʧ�ܻ��˳ɹ�ʱ��RRC�����ϱ�LRRC_LRABM_RAB_IND��Ϣ����
       ֻ�ϱ�LRRC_LRABM_STATUS_IND��Ϣ�ָ��������������͵Ĺ�����ɾ��DRB��Ϣ*/
    if ((EMM_ERABM_SYS_CHNG_TYPE_HO == pRcvMsg->enSysChngType)
         || (EMM_ERABM_SYS_CHNG_TYPE_CCO == pRcvMsg->enSysChngType))
    {
        /* ��DRB״̬��ΪNAS_ERABM_RB_SUSPENDED */
        for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
        {
            /* ��ӱ���,��ֹ����RbState��������Ϊ����̬ */
            if(NAS_ERABM_ILL_RB_ID != NAS_ERABM_GetEpsbRbIdInfo(ulEpsbId))
            {
                NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_SUSPENDED);
            }
        }
    }


    /*����ȴ�EPS���ؼ����ʶ*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*SERVICE����ֹͣ*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /* ֪ͨL2�ͷŻ�������ݰ� */
    /*APPITF_FreeAllofRabmBuf();*/

    /* �����������������־*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /* ֪ͨETC���� */
    NAS_ERABM_SndRabmTcSuspendInd();

    /* �ظ�EMM����ɹ� */
    NAS_ERABM_SndRabmEmmSuspendRsp(EMM_ERABM_RSLT_TYPE_SUCC);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmResumeInd
 Description     : SMģ���յ�ID_EMM_ERABM_RESUME_IND������
 Input           : EMM_ERABM_RESUME_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-03      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmResumeInd(const EMM_ERABM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* ����״̬Ϊ����̬ */
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_NORMAL);

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmResumeInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmResumeInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

    /* ֪ͨETC��� */
    NAS_ERABM_SndRabmTcResumeInd();

    /* �ظ�EMM��ҳɹ� */
    NAS_ERABM_SndRabmEmmResumeRsp(EMM_ERABM_RSLT_TYPE_SUCC);
}
/*****************************************************************************
 Function Name   : NAS_ERABM_SndRrmRegisterInd
 Description     : ��RRMע��RF��Դ֪ͨ,TASKTypeҪ��ȥע��ʱ����һ��
 Input           : RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
 Output          : None
 Return          : None

 History         :
    1.leixiantiao            2015-01-06      Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{

    /* ����ԭ������ָ�� */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU *)NAS_ERABM_ALLOC_MSG(sizeof(PS_RRM_REGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ����ʧ�� */
        return;
    }

    NAS_ERABM_MEM_SET(pstMsg, NAS_ERABM_NULL,sizeof(PS_RRM_REGISTER_IND_STRU));

    /*��д��Ϣͷ*/
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulLength            = sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = MODEM_ID_0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*������Ϣ*/
    NAS_ERABM_SND_MSG(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_ERABM_SndRrmDeRegisterInd
 Description     : ��RRM����ȥע��RF��Դ֪ͨ,TASKTypeҪ��ע��ʱ����һ��
 Input           : RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
 Output          : None
 Return          : None

 History         :
    1.leixiantiao            2015-01-06      Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_SndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{

    /* ����ԭ������ָ�� */
    PS_RRM_DEREGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU *)NAS_ERABM_ALLOC_MSG(sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ����ʧ�� */
        return;
    }

    NAS_ERABM_MEM_SET(pstMsg, NAS_ERABM_NULL,sizeof(PS_RRM_DEREGISTER_IND_STRU));

    /*��д��Ϣͷ*/
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulLength            = sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = MODEM_ID_0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*������Ϣ*/
    NAS_ERABM_SND_MSG(pstMsg);
    return;
}

/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

