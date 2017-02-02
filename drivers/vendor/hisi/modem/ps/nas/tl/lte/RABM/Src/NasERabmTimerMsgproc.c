


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmTimerMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTIMERMSGPROC_C
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

/*lint -e960*/
VOS_VOID NAS_ERABM_WaitEpsbActTimerExpire( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    (VOS_VOID)enTimerName;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_WaitEpsbActTimerExpire is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitEpsbActTimerExpire_ENUM, LNAS_ENTRY);

    if (NAS_ERABM_WAIT_EPSB_ACT_MSG == NAS_ERABM_GetWaitEpsbActSign())
    {
        /* ��ESM������״̬��Ϣ */
        NAS_ERABM_InformEsmBearerStatus(0);

        /*����ȴ�EPS���ؼ����ʶ*/
        NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

        /*֪ͨ��̨NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER��ʱ����ʱ*/
        NAS_ERABM_NORM_LOG("NAS_ERABM_WaitEpsbActTimerExpire: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER expire!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitEpsbActTimerExpire_ENUM, LNAS_FUNCTION_LABEL1);
    }
}
VOS_VOID NAS_ERABM_WaitRbReestTimerExpier
(
    NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName,
    VOS_UINT32                      ulTimerPara
)
{
    NAS_ERABM_START_TIMER_STRU           *pstTimerInfo       = VOS_NULL_PTR;

    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_WaitRbReestTimerExpier: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }
    if(NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMERֹͣʱ���¼��������򲻸���,
           NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER����ʱ���������ؽ�,ʹUE������״̬һ��*/
        /*���¶�ʱ����ʱ����*/
        pstTimerInfo->ucExpireTimes++;
    }
    /*lint -e961*/
    NAS_ERABM_LOG1("NAS_ERABM_WaitRbReestTimerExpier:data pending = ",NAS_ERABM_GetUpDataPending());
    TLPS_PRINT2LAYER_INFO1(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_UpDataPendingValue, NAS_ERABM_GetUpDataPending());
    /*lint +e961*/
    /* ����ʱ������9�����ڣ����ҳ���û�ж�Ӧ��DRB��
       ����EMM����EMM_ERABM_REEST_REQ��Ϣ��������������������
       ��ʱ����������������ʱ�������ͷŻ�����Ϣ*/
    if (( pstTimerInfo->ucExpireTimes < TI_NAS_ERABM_WAIT_RB_REEST_TIMER_MAX_EXP_NUM)
        &&(NAS_ERABM_SUCCESS== NAS_ERABM_IsAllActtiveBearerWithoutDrb())
        &&(NAS_ERABM_SERVICE_STATE_INIT == NAS_ERABM_GetEmmSrState()) )
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_EMM_RB_ReestTimerExpire:INFO:Expire times less than 9!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_FUNCTION_LABEL1);
        /* lihong00150010 emergency tau&service begin */
        NAS_ERABM_SndRabmEmmReestReq(ulTimerPara);
        NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                NAS_ERABM_WAIT_RB_REEST_TIMER,
                                ulTimerPara);
        /* lihong00150010 emergency tau&service end */
    }
    else
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_EMM_RB_ReestTimerExpire:INFO:Expire times is 9!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_FUNCTION_LABEL2);

        /*���¶�ʱ����ʱ����*/
        pstTimerInfo->ucExpireTimes = 0;

        /*SERVICE����ֹͣ*/
        NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

        /* ֪ͨL2�ͷŻ�������ݰ� */
        /*APPITF_FreeAllofRabmBuf();*/

        /* ֪ͨCDS�ͷŻ�������ݰ� */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();

        /* �����������������־*/
        NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
    }
}


/*****************************************************************************
 Function Name   : NAS_ERABM_WaitRbResumeTimerExpier
 Description     : DRB����ʱ����ʱ����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing      2010-12-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_WaitRbResumeTimerExpier( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;

    (VOS_VOID)enTimerName;

    NAS_ERABM_INFO_LOG("NAS_ERABM_WaitRbResumeTimerExpier is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbResumeTimerExpier_ENUM, LNAS_ENTRY);

    /*RRC��·�쳣��֪ͨEMM�ͷ���·*/
    NAS_ERABM_SndRabmEmmRelReq();

    /* �ͷ�����RB */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        NAS_ERABM_RcvRbRelease(ulEpsbId);
    }

    /* ֪ͨL2�ͷŻ�������ݰ� */
    /*APPITF_FreeAllofRabmBuf();*/

    /* ֪ͨCDS�ͷŻ�������ݰ� */
    NAS_ERABM_SndErabmCdsFreeBuffDataInd();

    /* �����������������־*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

}


VOS_VOID  NAS_ERABM_WaitTcFreeBufferTimer( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    (VOS_VOID)enTimerName;

    /*APPITF_FreeAllofRabmBuf();*/

    /* ֪ͨCDS�ͷŻ�������ݰ� */
    NAS_ERABM_SndErabmCdsFreeBuffDataInd();

    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    return;
}


VOS_VOID   NAS_ERABM_TimerMsgDistr(const VOS_VOID *pRcvMsg )
{

    VOS_UINT32                           ulTimerIndex  = 0;
    NAS_ERABM_START_TIMER_STRU           *pstTimerInfo = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TimerMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ENTRY);

    ulTimerIndex = PS_GET_REL_TIMER_NAME(pRcvMsg);

    pstTimerInfo = NAS_ERABM_GetRbTimer(ulTimerIndex);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    if (PS_GET_REL_TIMER_NAME(pRcvMsg) == pstTimerInfo->enName)
    {
        switch (pstTimerInfo->enName)
        {
            case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
                NAS_ERABM_WaitEpsbActTimerExpire(NAS_ERABM_WAIT_EPSB_ACT_TIMER);
                break;

            case NAS_ERABM_WAIT_RB_REEST_TIMER:
                /* lihong00150010 emergency tau&service begin */
                NAS_ERABM_WaitRbReestTimerExpier(NAS_ERABM_WAIT_RB_REEST_TIMER,PS_GET_REL_TIMER_PARA(pRcvMsg));
                break;
                /* lihong00150010 emergency tau&service end */
            case NAS_ERABM_WAIT_RB_RESUME_TIMER:
                NAS_ERABM_WaitRbResumeTimerExpier(NAS_ERABM_WAIT_RB_RESUME_TIMER);
                break;

            case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
                NAS_ERABM_WaitTcFreeBufferTimer(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
                break;
            case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
                /* ȥע��RF��Դ֪ͨ */
                NAS_ERABM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
                break;
            default:
                NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr:RB TimerExpire: unreasonable Timer expire");
                TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_UnreasonableTimerExpire);
                break;
        }
    }
    else
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr: RBSETUP Timer Expire info err!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_RBSETUPTimerExpireInfoErr);
    }
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

