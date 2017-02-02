


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "EmmTcInterface.h"
/* lihong00150010 emergency tau&service begin */
#include "NasEmmAttDetInclude.h"
/* lihong00150010 emergency tau&service ends */

#include "ImsaIntraInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmLppMsgProc.h"
#include "EmmLppInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICESERREQ_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICESERREQ_C
/*lint +e767*/



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/* lihong00150010 emergency tau&service begin */

VOS_UINT32 NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_ENTRY);

    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;

    /* ������ǽ���ҵ������ */
    if (VOS_TRUE != pstReestReq->ulIsEmcType)
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq:Not EMC!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /*�����������̬����ӡ������Ϣ*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* ������,��ֹEMM��RABMά����RRC��·״̬��һ��,����UE��ʱ���޷�������*/
        /* ����2���յ�ERABM�Ľ�������ʱ,��RRC��·״̬����ΪIDLE̬*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*��������״̬*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);

    return NAS_LMM_MSG_HANDLED;
}
/* lihong00150010 emergency tau&service end */

VOS_UINT32 NAS_EMM_MsRegSsNormalMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsRegSsNormalMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /*��鵱ǰ״̬������ָ��*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_ERROR);
         return NAS_LMM_MSG_HANDLED;
    }

    /*�����������̬����ӡ������Ϣ*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* ������,��ֹEMM��RABMά����RRC��·״̬��һ��,����UE��ʱ���޷�������*/
        /* ����2���յ�ERABM�Ľ�������ʱ,��RRC��·״̬����ΪIDLE̬*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*��������״̬*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

/*modified by jiqiang for CSFB 20140922 begin */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsNormalMsgRabmReestReq: Msg discard, CSFB delay timer is running.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }
/*modified by jiqiang for CSFB 20140922 end */

    /* lihong00150010 emergency tau&service begin */
    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;
    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);
    /* lihong00150010 emergency tau&service end */
    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /*��鵱ǰ״̬������ָ��*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_ERROR);
         return NAS_LMM_MSG_HANDLED;
    }

    /*�����������̬����ӡ������Ϣ*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* ������,��ֹEMM��RABMά����RRC��·״̬��һ��,����UE��ʱ���޷�������*/
        /* ����2���յ�ERABM�Ľ�������ʱ,��RRC��·״̬����ΪIDLE̬*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*��������״̬*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

    /* ��¼UPDATE_MM��ʶ */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
    /* lihong00150010 emergency tau&service begin */
    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;
    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);
    /* lihong00150010 emergency tau&service end */

    return NAS_LMM_MSG_HANDLED;
}

/* lihong00150010 emergency tau&service begin */
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq
 Description     : Reg.Limit_Service״̬���յ�RABM�����쳣���ͷ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*������ͷŹ����У���ֱ�Ӷ���*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* ��������״̬Ϊ�ͷŹ����� */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }


    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;
}
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgRabmRelReq
 Description     : Reg.Normal_Service״̬���յ�RABM�����쳣���ͷ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing      2010-12-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgRabmRelReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*������ͷŹ����У���ֱ�Ӷ���*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* ��������״̬Ϊ�ͷŹ����� */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq
 Description     : ������REG+ATTEMPT_TO_UPDATE_MM״̬���յ�RABM���ͷ���·����
 Input           : ulMsgId-------------------------��ϢID
                   pMsgStru------------------------��Ϣָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*������ͷŹ����У���ֱ�Ӷ���*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* ��������״̬Ϊ�ͷŹ����� */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq
 Description     : ��ס״̬ΪEMM_RS_REG_INIT����״̬ΪEMM_SS_ATTACH_WAIT_CN_ATTACH_CNF
                   ���յ�ID_EMM_ETC_DATA_REQ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgTcDataReq
 Description     : ��ס״̬ΪEMM_RS_REG����״̬ΪEMM_SS_NORMAL_SERVICE
                   ���յ�ID_EMM_ETC_DATA_REQ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*������ͷŹ����У���ֱ�Ӷ���*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* ͸��ETC��Ϣ */
         NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
        return NAS_LMM_MSG_HANDLED;
    }


    /*CONNģʽ�£�ת��TC��Ϣ��IDLEģʽ�£���ӡ������Ϣ*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
    }
    else
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgTcDataReq:Warning:RRC connection is not Exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*������ͷŹ����У���ֱ�Ӷ���*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* ͸��ETC��Ϣ */
         NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
        return NAS_LMM_MSG_HANDLED;
    }


    /*CONNģʽ�£�ת��TC��Ϣ��IDLEģʽ�£���ӡ������Ϣ*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
    }
    else
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq:Warning:RRC connection is not Exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ERROR);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong00150010  2009-09-25  �¹�����
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgEsmDataReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* ���LRRC REL��С��פ���ϱ�ϵͳ��Ϣǰ�յ�ESM�������ؽ����������ڿտڷ���ʧ�ܣ�����detach,�������ATTACH����
           ����:�ȸ����ȼ����棬�ȵ��յ�LRRCϵͳ��Ϣ����*/
        if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
            ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
        {
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
    }

    if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }


    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* ����ǽ������͵ģ���ֹͣT3440��ʱ������������·�ͷ� */
        if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
        {
            NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* ��������״̬Ϊ�ͷŹ����� */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
        return NAS_LMM_STORE_HIGH_PRIO_MSG;

    }


    /*CONN̬��ת��ESM��Ϣ*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }

/*modified by jiqiang for CSFB 20140922 begin */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsNormalMsgEsmDataReq: Msg discard, CSFB delay timer is running.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_EMM_DISCARD, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }
/*modified by jiqiang for CSFB 20140922 end */

    NAS_EMM_SER_RcvEsmDataReq(pMsgStru);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgSmsEstReq
 Description     : ��������״̬�´���SMS��������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing 49683      2011-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgSmsEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgSmsEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgSmsEstReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgSmsEstReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*��Ϊ���������Ѿ�����Ԥ�����������������˵��CS���Ѿ�ע�ᣬ
      ��������ڿ���̬������ֱ�ӻظ������ɹ�*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_LMM_SndLmmSmsEstCnf();

        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
        return NAS_LMM_MSG_HANDLED;
    }
    /* ������: ��Mt Ser Flag��־ */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*����SER����ԭ��Ϊ NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_LPP == FEATURE_ON)

VOS_UINT32  NAS_EMM_MsRegSsNormalMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgLppEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgLppEstReq_ENUM, LNAS_LPP_Func_Enter);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgLppEstReq_ENUM, LNAS_LPP_CheckStatusError);
        return NAS_LMM_MSG_DISCARD;
    }


    /*��������ڿ���̬������ֱ�ӻظ������ɹ�*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);

        return NAS_LMM_MSG_HANDLED;
    }

    /*����SER����ԭ��Ϊ NAS_EMM_SER_START_CAUSE_LPP_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq_ENUM, LNAS_LPP_Func_Enter);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq_ENUM, LNAS_LPP_CheckStatusError);
        return NAS_LMM_MSG_DISCARD;
    }


    /*��������ڿ���̬������ֱ�ӻظ������ɹ�*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);

        return NAS_LMM_MSG_HANDLED;
    }

    /*����SER����ԭ��Ϊ NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}
#endif


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* ���LRRC REL��С��פ���ϱ�ϵͳ��Ϣǰ�յ�ESM�������ؽ����������ڿտڷ���ʧ�ܣ�����detach,�������ATTACH����
           ����:�ȸ����ȼ����棬�ȵ��յ�LRRCϵͳ��Ϣ����*/
        if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
            ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
        {
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
    }

    if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* ����ǽ������͵ģ���ֹͣT3440��ʱ������������·�ͷ� */
        if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
        {
            NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* ��������״̬Ϊ�ͷŹ����� */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /*CONN̬��ת��ESM��Ϣ*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }
    /* ��¼UPDATE_MM��ʶ */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
    NAS_EMM_SER_RcvEsmDataReq(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMM_MsTauInitMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                                )
{
    VOS_UINT32                      ulRslt                = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");

        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgRabmReestReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_MSG_DISCARD;
    }
VOS_UINT32 NAS_EMM_MsTauInitMsgRrcPagingInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                                )
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgRrcPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRrcPagingInd_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgRrcPagingInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_STORE_HIGH_PRIO_MSG;
}
VOS_UINT32 NAS_EMM_MsSerInitMsgEsmdataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt             = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstsmdatareq       = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitMsgEsmdataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitMsgEsmdataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT ,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitMsgEsmdataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*SERģ�����л���ESM DATA��Ϣ*/
    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU        *)pMsgStru;

    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* lihong00150010 emergency tau&service begin */
        /* ����������͵�ESM��Ϣ */
        NAS_EMM_SaveEmcEsmMsg(pMsgStru);
        /* lihong00150010 emergency tau&service end */
    }
    NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMM_MsTauInitMsgEsmdataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt             = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstsmdatareq       = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgEsmdataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgEsmdataReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgEsmdataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU *)pMsgStru;

    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
    }

    /* ����ǰTAU�Ǵ����SERVICE��TAU����,
       �򽫴��յ���ESM��Ϣ���� */
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*SERģ�����л���ESM DATA��Ϣ*/
        NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);
        /* lihong00150010 emergency tau&service begin */
        if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
        {
            /* ����������͵�ESM��Ϣ */
            NAS_EMM_SaveEmcEsmMsg(pMsgStru);
        }
        /* lihong00150010 emergency tau&service end */
        return  NAS_LMM_MSG_HANDLED;
    }

    /*add by lifuxin for Lnas est process re-construct start*/
    /*��TAU_INIT+WAIT_CN_CNF״̬���ҵ�ǰ������״̬��NAS_EMM_CONN_ESTING��
      �����ǰTAU�����Ǵ��SERVCIE����TAU�� ����Ҫ���棬 ��������TAU������
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_MSG_HANDLED;
    }
    /*add by lifuxin for Lnas est process re-construct end*/

    /* ͸��SM��Ϣ */
    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstsmdatareq->stEsmMsg, pstsmdatareq->ulOpId);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitMsgRabmRelReq
 Description     : TauInit.WtTauCnf״̬���յ������쳣����ֹ��ǰTAU���̣�����ͬ
                   �ײ��쳣
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing           2010-12-29  Draft Enact
    2.lihong00150010    2012-12-14  Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitMsgRabmRelReq(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsTauInitMsgRabmRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*��ֹ��ǰTAU����*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

    NAS_EMM_TAU_ProcAbnormal();

    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitMsgRabmRelReq:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmRelReq_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                        (VOS_VOID*)NAS_EMM_NULL_PTR);
    }
    /* lihong00150010 emergency tau&service end */

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);



    return  NAS_LMM_MSG_HANDLED;
}
VOS_VOID    NAS_EMM_SER_RcvRabmReestReq
(
    VOS_UINT32                          ulIsEmcType
)
{
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_Ser_RcvRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRabmReestReq_ENUM,LNAS_ENTRY);
    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RABM_REEST);
    }
    /* ������: ��Mt Ser Flag��־ */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /* lihong00150010 emergency tau&service end */
    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}
VOS_VOID    NAS_EMM_SER_RcvRrcStmsiPagingInd(VOS_VOID)
{

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRrcStmsiPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcStmsiPagingInd_ENUM,LNAS_ENTRY);
    /* ������: ����SER����ΪMT Ser */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_YES);
    /* ������: ��¼Mt Ser��������ʱ�� */
    NAS_EMM_SaveMtSerStartTimeStamp();
    /*����SER����ԭ��Ϊ NAS_EMM_SER_START_CAUSE_RRC_PAGING*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RRC_PAGING);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;

}
VOS_UINT32 NAS_EMM_SER_CsDomainNotRegProcNormalCsfb(VOS_VOID)
{
    NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_CsDomainNotRegProcNormalCsfb is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CsDomainNotRegProcNormalCsfb_ENUM, LNAS_ENTRY);

    /* ��#2�ܾ�����ֱ����ֹ */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CsDomainNotRegProcNormalCsfb:REJ#2!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CsDomainNotRegProcNormalCsfb_ENUM, LNAS_END);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);
        return NAS_LMM_MSG_HANDLED;
    }

    /* UPDATE MM̬��״̬������ */
    if ((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
      &&(EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS()))
    {
        return NAS_LMM_MSG_DISCARD;
    }

    /* ����״̬����ȥGU */
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedHighPrioStore(VOS_VOID)
{
    if (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Esting, High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /* T3440��ʱ�������ڼ䲻�ٸ����ȼ����棬��Ϊ����delay��ʱ������ֹ��������һֱ�����ͷŵ��µķ������������ */
    if ((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Releasing, High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SUCC;
    }

    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Don't need high prio store.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL3);
    return NAS_EMM_FAIL;
}
VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedLowPrioStore
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_AUTH_INIT:
        case    EMM_MS_RESUME:

                NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:TAU, need store!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL1);
                return NAS_EMM_SUCC;

        case    EMM_MS_SER_INIT:
                if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
                    &&(MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp))
                {
                    return NAS_EMM_FAIL;
                }

                /* ��ǰ���Ѿ����ڵ�MO CSFB��ͻ������ */
                if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:SER, need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL2);
                    return NAS_EMM_SUCC;
                }

                break;

        case    EMM_MS_REG:

                if (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Imsi detach, need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL3);
                    return NAS_EMM_SUCC;
                }

                break;

        case    EMM_MS_REG_INIT:

                if ((EMM_SS_ATTACH_WAIT_RRC_DATA_CNF == NAS_LMM_GetEmmCurFsmSS())
                ||(EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF == NAS_LMM_GetEmmCurFsmSS()))
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Wait rrc data cnf and wait esm bearer cnf,need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL4);
                    return NAS_EMM_SUCC;
                }

                break;

        default:
            break;
    }

    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Don't need store.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL4);
    return NAS_EMM_FAIL;
}
VOS_UINT32 NAS_EMM_SER_VerifyNormalCsfb(VOS_VOID)
{
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* ����CS_PS UE mode����ʧ�� */
    if (NAS_EMM_YES != NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb:Not CS_PS UE mode!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* �ж�UE�Ƿ�֧��CSFB,���CS SERVICEδʹ�ܣ���Ĭ��֧��CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
      &&(NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb: UE is not support csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    /* �ж��Ƿ���L��ģ */
    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb: Lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}


VOS_UINT32 NAS_EMM_SER_VerifyMtCsfb( VOS_VOID )
{
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* MT CALLʱ���ж�ע����:���GU2L,L��TAU���ڵײ��쳣,����TAUʧ��ת��ATTEMP_TO_UPDATE_MM̬ʱ�յ�CS PAGING���������� */

    /* �ж�UE�Ƿ�֧��CSFB,���CS SERVICEδʹ�ܣ���Ĭ��֧��CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
        && (NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyMtCsfb:ue is not support csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyMtCsfb_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* ɾ��ԭ���õ�ע�ʹ��룬��SMS ONLY������ж� */
    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
    }
    #endif

    /* �ж��Ƿ���L��ģ */
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyMtCsfb:lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyMtCsfb_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}
VOS_UINT32 NAS_EMM_SER_VerifyCsfb(MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvType)
{

    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* �ж�ע�����Ƿ�ΪCS+PS */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:cs is not registered!");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL1);
       return NAS_EMM_FAIL;
    }

    /* �ж�UE�Ƿ�֧��CSFB,���CS SERVICEδʹ�ܣ���Ĭ��֧��CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
       && (NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:ue is not support csfb!");\
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL2);
       return NAS_EMM_FAIL;
    }

    /* ����MO���͵ģ�������̬�������ڽ������͵ģ���Ԥ���������Ѿ��жϣ�
    Ӧ�ò�����֣��ڵ��÷�֧��ע�� */
    /* �ж������Ƿ�Я����SMS ONLY */
    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
        && (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvType))
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:additional update result sms only");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL3);
       return NAS_EMM_FAIL;
    }

    /* �ж��Ƿ���L��ģ */
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:lte only");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL4);
       return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}



VOS_VOID    NAS_EMM_SER_RcvRrcCsPagingInd
(
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
)
{

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRrcCsPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcCsPagingInd_ENUM,LNAS_ENTRY);

    /* ���MT CSFB�����Ƿ��ܹ����� */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyMtCsfb())
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_RcvRrcCsPagingInd:cannot csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcCsPagingInd_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ��MMģ�鷢��MM_MM_CSFB_SERVICE_PAGING_IND��Ϣ */
    NAS_EMM_MmSendCsfbSerPaingInd(  NAS_EMM_MT_CSFB_TYPE_CS_PAGING,
                                    VOS_NULL_PTR,
                                    enPagingUeId);
    return;
}


VOS_VOID    NAS_EMM_SER_RcvEsmDataReq(VOS_VOID   *pMsgStru)
{
    EMM_ESM_DATA_REQ_STRU        *pstsmdatareq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    NAS_EMM_SER_LOG_INFO( "Nas_Emm_Ser_RcvEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvEsmDataReq_ENUM,LNAS_ENTRY);
    /* lihong00150010 emergency tau&service begin */
    /* ����SERVICE����ԭ��ֵ */
    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC);

        /* ����������͵�ESM��Ϣ */
        NAS_EMM_SaveEmcEsmMsg(          pMsgStru);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ);
    }
    /* lihong00150010 emergency tau&service end */
    /* ������:����Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*SERģ�����л���ESM DATA��Ϣ*/
    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU        *)pMsgStru;
    NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}


VOS_VOID  NAS_EMM_SER_UplinkPending( VOS_VOID )
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_UplinkPending is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_UplinkPending_ENUM,LNAS_ENTRY);
    /* ������: ��Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*����SER����ԭ��Ϊ NAS_ESM_SER_START_CAUSE_UPLINK_PENDING*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_ESM_SER_START_CAUSE_UPLINK_PENDING);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

     /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}



VOS_VOID  NAS_EMM_SER_SmsEstReq( VOS_VOID )
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SmsEstReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SmsEstReq_ENUM,LNAS_ENTRY);

    /*����SER����ԭ��Ϊ NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    return;
}
/*lint -e960*/
/*lint -e961*/
VOS_BOOL NAS_EMM_SER_IsSameEsmMsgInBuf
(
    const EMM_ESM_DATA_REQ_STRU               *pMsgStru
)
{
    VOS_UINT32                          i       = 0;
    EMM_ESM_DATA_REQ_STRU              *pEsmMsg = NAS_LMM_NULL_PTR;

    /* �����Ϣ���Ⱥ�������ͬ������Ϊ���ظ���Ϣ */
    for (i = 0; i < g_stEmmEsmMsgBuf.ulEsmMsgCnt; i++)
    {
        if (NAS_LMM_NULL_PTR != g_stEmmEsmMsgBuf.apucEsmMsgBuf[i])
        {
            pEsmMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[i];

            /* lihong00150010 emergency tau&service begin */
            if ((pMsgStru->stEsmMsg.ulEsmMsgSize == pEsmMsg->stEsmMsg.ulEsmMsgSize)
             && (0 == NAS_LMM_MEM_CMP(pMsgStru->stEsmMsg.aucEsmMsg,
                                     pEsmMsg->stEsmMsg.aucEsmMsg,
                                     pEsmMsg->stEsmMsg.ulEsmMsgSize))
             && (pMsgStru->ulOpId == pEsmMsg->ulOpId)
             && (pMsgStru->ulIsEmcType == pEsmMsg->ulIsEmcType)
               )
            {
                return VOS_TRUE;
            }
            /* lihong00150010 emergency tau&service end */
        }
        else
        {
            NAS_EMM_SER_LOG_WARN( "NAS_EMM_SER_IsSameEsmMsgInBuf: Null buffer item.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_IsSameEsmMsgInBuf_ENUM,LNAS_FUNCTION_LABEL1);
        }
    }

    return VOS_FALSE;
}

/* lihong00150010 emergency tau&service begin */

VOS_UINT32 NAS_EMM_SER_FindEsmMsg
(
    VOS_UINT32                          ulOpid
)
{
    VOS_UINT32                          ulIndex     = NAS_EMM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmMsg   = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_FindEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_FindEsmMsg_ENUM,LNAS_ENTRY);

    for (ulIndex = NAS_EMM_NULL; ulIndex < g_stEmmEsmMsgBuf.ulEsmMsgCnt; ulIndex++)
    {
        pstEsmMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex];
        if (ulOpid == pstEsmMsg->ulOpId)
        {
            return ulIndex;
        }
    }

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_FindEsmMsg failed!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_FindEsmMsg_ENUM,LNAS_FAIL);

    return NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM;
}
VOS_VOID NAS_EMM_SER_DeleteEsmMsg
(
    VOS_UINT32                          ulOpid
)
{
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt  = NAS_EMM_NULL;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_DeleteEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_DeleteEsmMsg_ENUM,LNAS_ENTRY);

    ulIndex = NAS_EMM_SER_FindEsmMsg(ulOpid);
    if (ulIndex >= g_stEmmEsmMsgBuf.ulEsmMsgCnt)
    {
        return ;
    }

    ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex]);

    if (NAS_COMM_BUFF_SUCCESS != ulRslt)
    {
       NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_DeleteEsmMsg, Memory Free is not succ");
       TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_DeleteEsmMsg_ENUM,LNAS_FUNCTION_LABEL1);
    }

    g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex] = NAS_LMM_NULL_PTR;

    for (; ulIndex < (g_stEmmEsmMsgBuf.ulEsmMsgCnt - 1); ulIndex++)
    {
        g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex] = g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex+1];
    }

    g_stEmmEsmMsgBuf.apucEsmMsgBuf[g_stEmmEsmMsgBuf.ulEsmMsgCnt - 1] = NAS_LMM_NULL_PTR;

    g_stEmmEsmMsgBuf.ulEsmMsgCnt--;
}
/* lihong00150010 emergency tau&service end */


VOS_VOID NAS_EMM_SER_SaveEsmMsg(const EMM_ESM_DATA_REQ_STRU  *pMsgStru)
{
    VOS_VOID                            *pMsgBuf   = NAS_LMM_NULL_PTR;
    VOS_UINT32                           ulBufSize = 0;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_Ser_SaveEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_ENTRY);

    /* �����ظ���SM��Ϣ���������*/
    if ((VOS_FALSE == NAS_EMM_SER_IsSameEsmMsgInBuf(pMsgStru))
     && (NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM > g_stEmmEsmMsgBuf.ulEsmMsgCnt))
    {
        ulBufSize = pMsgStru->stEsmMsg.ulEsmMsgSize +
                    sizeof(pMsgStru->stEsmMsg.ulEsmMsgSize) +
                    sizeof(pMsgStru->ulOpId) +
                    sizeof(pMsgStru->ulIsEmcType) +
                    EMM_LEN_VOS_MSG_HEADER +
                    EMM_LEN_MSG_ID;

        /* ����ռ� */
        pMsgBuf = NAS_COMM_AllocBuffItem(NAS_COMM_BUFF_TYPE_EMM, ulBufSize);

        if (NAS_LMM_NULL_PTR != pMsgBuf)
        {
            NAS_LMM_MEM_CPY(pMsgBuf, pMsgStru, ulBufSize);

            g_stEmmEsmMsgBuf.apucEsmMsgBuf[g_stEmmEsmMsgBuf.ulEsmMsgCnt] = pMsgBuf;
            g_stEmmEsmMsgBuf.ulEsmMsgCnt++;

        }
        else
        {
            NAS_EMM_SER_LOG_INFO( "NAS_EMM_Ser_SaveEsmMsg: NAS_AllocBuffItem return null pointer.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL1);
        }
    }
    else
    {
        NAS_EMM_SER_LOG1_INFO( "NAS_EMM_Ser_SaveEsmMsg: ESM Msg Not Buffered, Buffered msg number is:",
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL2,
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);
    }

    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_Ser_SaveEsmMsg: Buffered msg number is:",
                           g_stEmmEsmMsgBuf.ulEsmMsgCnt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL3,
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);

    return;
}
VOS_UINT32 NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)(ulMsgId);
    NAS_EMM_SER_LOG_INFO("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq_ENUM,LNAS_ENTRY);
    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
    return NAS_LMM_MSG_HANDLED;
}




VOS_VOID  NAS_EMM_MsTauSerSsWaitCnCnfEmergencyCsfbProc(VOS_VOID)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    /* TAU������, ���������Զ������Դ */
    if (EMM_MS_TAU_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ */
        ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

        NAS_EMM_TAU_AbnormalOver();
    }
    else  /* SER������,��ֹSER */
    {
        NAS_EMM_SER_AbnormalOver();
    }

    /* ת��REG.PLMN-SEARCH��MMC���� */
    NAS_EMM_AdStateConvert(EMM_MS_REG,
                           EMM_SS_REG_PLMN_SEARCH,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* �����������̬��ѹջ�ͷŴ��� */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}


VOS_VOID  NAS_EMM_MsAnySsWaitCnDetachCnfEmergencyCsfbProc(VOS_VOID)
{
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* REG. EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF ̬*/
    if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* ��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ */
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_AdStateConvert(EMM_MS_REG,
                               EMM_SS_REG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_ImsiDetachReleaseResource();
    }
    else /* DEREG_INIT. EMM_SS_DETACH_WAIT_CN_DETACH_CNF ̬*/
    {
        /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* ֪ͨESM�����Դ */
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* �����������̬��ѹջ�ͷŴ��� */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}


VOS_VOID  NAS_EMM_MsRegInitSsAnyStateEmergencyCsfbProc(VOS_VOID)
{
    /* ��MMC�ϱ�ATTACH���Ϊʧ�� */
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_FAILURE);

    /* ATTACHͣ��ʱ�� + �����Դ */
    NAS_EMM_Attach_SuspendInitClearResourse();

    /* �޸�״̬��������״̬DEREG��״̬DEREG_PLMN_SEARCH, ��ʱ����״̬���ϱ��ı�*/
    NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                           EMM_SS_DEREG_PLMN_SEARCH ,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /* ֪ͨESM�����Դ */
    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* �����������̬��ѹջ�ͷŴ��� */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}


VOS_UINT32  NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc(VOS_VOID)
{

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
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_CannotDirectlyStartMoEmergencyCsfbProc:High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_REG_INIT:
            /* ����SERVICE����ԭ��Ϊ����CSFB, ���ڸ�MMC�ϱ�SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            NAS_EMM_MsRegInitSsAnyStateEmergencyCsfbProc();
            break;

        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:
            /* ����SERVICE����ԭ��Ϊ����CSFB, ���ڸ�MMC�ϱ�SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            NAS_EMM_MsTauSerSsWaitCnCnfEmergencyCsfbProc();
            break;

        case    EMM_MS_AUTH_INIT:
        case    EMM_MS_RESUME:
            NAS_EMM_SER_LOG_NORM( "NAS_EMM_CannotDirectlyStartMoEmergencyCsfbProc:Low priority storage!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    EMM_MS_REG:
        case    EMM_MS_DEREG_INIT:
            /* ����SERVICE����ԭ��Ϊ����CSFB, ���ڸ�MMC�ϱ�SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            if ((EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                || (EMM_SS_DETACH_WAIT_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_MsAnySsWaitCnDetachCnfEmergencyCsfbProc();
            }
            else
            {
                /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            break;

        default:
            /* ����SERVICE����ԭ��Ϊ����CSFB, ���ڸ�MMC�ϱ�SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            break;
    }

    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    NAS_EMM_SER_LOG_NORM( "NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg:enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg_ENUM,LNAS_ENTRY);

    switch (NAS_LMM_GetEmmCurFsmSS())
    {
        /* ��Щ״̬����״̬������ */
        case    EMM_SS_REG_NORMAL_SERVICE         :
        case    EMM_SS_REG_WAIT_ACCESS_GRANT_IND  :
        case    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM:

                return NAS_LMM_MSG_DISCARD;

        /* ���޷�����IMS�绰�Ƿ���ڣ�����������ȥGU */
        case    EMM_SS_REG_LIMITED_SERVICE        :

                /* �����IMS�绰����ֹCSFB�����򴥷�����ȥGU */
                #if (FEATURE_ON == FEATURE_IMS)
                if (VOS_TRUE == IMSA_IsCallConnExist())
                {
                    NAS_EMM_SER_LOG_WARN("NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg:Limit service,IMS call!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg_ENUM, LNAS_FUNCTION_LABEL1);
                    NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);
                }
                else
                #endif
                {
                    /* ������MO����MT����ȥGU����������CSFBĿǰ�����ߵ����� */
                    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }
                #if (FEATURE_ON == FEATURE_PTM)
                if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
                }
                #endif
                break;

        /* ������״ֱ̬������ȥGU */
        case    EMM_SS_REG_ATTEMPTING_TO_UPDATE   :
        case    EMM_SS_REG_PLMN_SEARCH            :
        case    EMM_SS_REG_NO_CELL_AVAILABLE      :

                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

                #if (FEATURE_ON == FEATURE_PTM)
                if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
                }
                else
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
                }
                #endif
                break;

        /* ֻʣ��1����״̬IMSI DETACH��ǰ���Ѿ������� */
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}

VOS_UINT32  NAS_EMM_RcvMmNormalCsfbNotifyMsgProc
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32          enCsfbSrvTyp
)
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM, LNAS_ENTRY);

    /* ���CSFB ABORT��ʶ */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /* ���CSFB�����Ƿ��ܹ����� */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyNormalCsfb())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);

        return NAS_LMM_MSG_HANDLED;
    }

    /* ����Ƿ���Ҫ�����ȼ����� */
    if (NAS_EMM_SUCC == NAS_EMM_SER_CheckCsfbNeedHighPrioStore())
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }
    /* �ж��Ƿ���Ҫ�����ȼ����� */
    if (NAS_EMM_SUCC == NAS_EMM_SER_CheckCsfbNeedLowPrioStore(enCsfbSrvTyp))
    {
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* ע������CS_PS�Ĵ��� */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        return NAS_EMM_SER_CsDomainNotRegProcNormalCsfb();
    }

    /* �ж������Ƿ�Я����SMS ONLY������ǣ�ȥGU���������������̬��Ҫ�ͷ���· */
    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3442)))
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc:Sms only or T3442 is running!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM, LNAS_FUNCTION_LABEL1);
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        #if (FEATURE_ON == FEATURE_PTM)
        if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
        }
        else if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
        }
        else
        {
        }
        #endif
        return NAS_LMM_MSG_HANDLED;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_SER_INIT:
                /* ��Ȧ���Ӷ� */
                return NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg(enCsfbSrvTyp);

        case    EMM_MS_REG:

                return NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg(enCsfbSrvTyp);

        default:/*����״̬Ϊ�����״̬�����Ӹ澯��ӡ*/
                NAS_EMM_PUBU_LOG1_ERR("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc: Main State is err!",NAS_EMM_CUR_MAIN_STAT);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM,LNAS_EMM_MAIN_STATE,NAS_EMM_CUR_MAIN_STAT);

                NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

                /*Ϊ�ݴ����Ӷ�MM�Ļظ�*/
                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_FAILURE, NAS_LMM_CAUSE_NULL);
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32  NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc(VOS_VOID)
{
    /* ���CSFB ABORT��ʶ */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /* L��ģ���ܷ������CSFB */
    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS, NAS_LMM_CAUSE_NULL);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �˴���Service������־��Ҫ��Ϊ�˵��޷�����CSFBʱ�ظ�MMC Service���ʹ�ã�
       ����ǰ��״̬ΪSer Init����ʱ�ñ�־�ᵼ��Service�����쳣 */

    /* ���ܿ���ֱ�ӷ������CSFB����, ���ݵ�ǰ����״̬���в�ͬ����*/
    if (NAS_EMM_SUCC == NAS_EMM_SER_VerifyCsfb(MM_LMM_CSFB_SERVICE_MO_EMERGENCY))
    {
        if((NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
            || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
            || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
        {
            return  NAS_LMM_STORE_HIGH_PRIO_MSG;
        }

        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        {
            NAS_EMM_SER_LOG_NORM( "NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc:High priority storage!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc_ENUM,LNAS_FUNCTION_LABEL1);
                if (NAS_RELEASE_R11)
                {
                    /* upon receiving a request from upper layers to establish either a CS emergency call or
                    a PDN connection for emergency bearer services, the UE shall stop timer T3340 and
                    shall locally release the NAS signalling connection, before proceeding as specified in subclause 5.6.1*/
                    /* ���״̬����RELEASING״̬����֮ǰ�϶���������T3440��ʱ�� */
                    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

                    /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
                    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

                    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
                    NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

                    /* ��������״̬Ϊ�ͷŹ����� */
                    NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
                }
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }

        switch(NAS_EMM_CUR_MAIN_STAT)
        {
            case    EMM_MS_TAU_INIT:
            case    EMM_MS_SER_INIT:
            case    EMM_MS_AUTH_INIT:
            case    EMM_MS_RESUME:
                NAS_EMM_SER_LOG_NORM( "NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc:Low priority storage!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc_ENUM,LNAS_FUNCTION_LABEL2);
                return NAS_LMM_STORE_LOW_PRIO_MSG;

            /*ֻ��REG+NORMAL_SERVICE̬����ֱ�ӷ������CSFB*/
            case    EMM_MS_REG:
                if (EMM_SS_REG_NORMAL_SERVICE == NAS_EMM_CUR_SUB_STAT)
                {
                    return NAS_LMM_MSG_DISCARD;
                }
                break;

            default:
                break;

        }
    }

    /* ��Ȼ����ֱ�ӷ������״̬����������������Ϊ���ܷ��� */
    return NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc();

}


VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerStartNotify( MsgBlock * pMsg )
{
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify = VOS_NULL_PTR;

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU*)pMsg;

    /* ����CSFB�Ĵ��� */
    if (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        return NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc();
    }
    else  /* MO��MT��NORMAL CSFB�Ĵ��� */
    {
        return NAS_EMM_RcvMmNormalCsfbNotifyMsgProc(pstCsfbSerStartNotify->enCsfbSrvType);
    }
}


VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*����SER����ԭ��ֵ*/
    if (MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ);
    }
    else if (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);
    }

    /* ��������ͷŹ����У���ײ㴦��δפ��״̬������CSFB��ʱ��ʱ�������յ�ϵͳ��Ϣʱ�ٿ��Ƿ��� */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
     ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()) \
     /* Ϊ���T3440��ʱ�������ڼ�����һֱ���ͷ���·��������Ӧ����̫�������⣬
     �˶�ʱ�������ڼ䲻�ٸ����ȼ����棬��Ϊ����delay��ʱ�� */
     ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
       NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);
       return NAS_LMM_MSG_HANDLED;
    }

    /* ����UE����CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */

    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* MO CSFB���ܷ��� */
    if (MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* ��״̬�������յ�����CSFB,Ԥ�������ѹ�� */

    /* ���MT��BAR������MT CSFB����ֱ������ȥGU */
    if ((NAS_EMM_SUCC == NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MT))
      &&(MM_LMM_CSFB_SERVICE_MT_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType))
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        #if (FEATURE_ON == FEATURE_PTM)
        /* ����״̬���յ�CS PAGING��Ϣʱ���������ϱ�CHR�����յ�CSFB START NOTIFYʱ���ϱ� */
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
        #endif
        return NAS_LMM_MSG_HANDLED;
    }

    /* ����SER����ԭ��ΪMT CSFB */
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

    /* ����UE����CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */
    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}

/* ɾ����ʹ�õ�UPDATE MM̬�յ�CS PAGING�����Ķ��� */

VOS_UINT32 NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
        {
            /*ֹͣ��ʱ��T3417ext*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*����SER����ԭ��ֵ*/
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ);

            /* ����UE����CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */

            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /*������ʱ��T3417ext*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            return NAS_LMM_MSG_HANDLED;
        }
    }

    /* �жϵ�ǰ��MT CSFB������ESR�����У��������ٴδ���MT CSFB�������´���ESR����ʱ��T3417EXT��������
       ����յ���MO���͵�CSFB��ֱ�Ӷ���*/
    if ((NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
        {
            /*ֹͣ��ʱ��T3417ext*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*����SER����ԭ��ֵ*/
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

            /* ����UE����CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */

            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /*������ʱ��T3417ext*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);
        }
    }
    /* ��MO CSFB��ͻ�ĳ������ڻ��泡������ǰ���Ѿ����� */
    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32  NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*�����MO CSFB���߽���CSFB����ֱ�ӻظ�ʧ�ܣ�����MMCѡ����GU�������ǰΪ
      ����̬������Ҫ�����ͷ���· */
    if ((MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
        || (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType))
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

    /* ��������ͷŹ����У���ײ㴦��δפ��״̬������CSFB��ʱ��ʱ�������յ�ϵͳ��Ϣʱ�ٿ��Ƿ���
    Ϊ���T3440��ʱ�������ڼ�����һֱ���ͷ���·��������Ӧ����̫�������⣬�˶�ʱ�������ڼ䲻�ٸ�
    ���ȼ����棬��Ϊ����delay��ʱ�� */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
     ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
     ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
       NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);
       return NAS_LMM_MSG_HANDLED;
    }

    /* ����UE����CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */

    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



