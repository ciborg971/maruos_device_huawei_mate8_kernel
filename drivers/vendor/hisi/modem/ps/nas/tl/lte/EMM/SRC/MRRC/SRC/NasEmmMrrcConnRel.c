


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmGIMComm.h"
#include    "NasEmmMrrc.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMMRRCREL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMMRRCREL_C
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
NAS_EMM_MRRC_CTRL_STRU                  g_stEmmMrrcCtrl;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcRelInit
 Discription    : MRRC ����ģ���ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcRelInit(VOS_VOID)
{
    g_stEmmMrrcCtrl.ulRelCause = NAS_EMM_NORMALSERVICE_REL_CAUSE_NULL;

    /*����Դ*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /*�ı�����״̬,ͬʱ�Ͽ���ȫ����*/
    NAS_EMM_MrrcChangeRrcStatusToIdle();

    return;
}

/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_EMM_SndRrcRelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus)
{
    LRRC_LMM_REL_REQ_STRU                *pRelReqMsg;

    /* �����ڴ�*/
    pRelReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_REL_REQ_STRU));
    if(NAS_EMM_NULL_PTR == pRelReqMsg)
    {
        /* ��ӡ�ڴ����ʧ��log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndRrcRelReq:Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndRrcRelReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*���VOS��Ϣͷ*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pRelReqMsg, (sizeof(LRRC_LMM_REL_REQ_STRU) - NAS_EMM_VOS_HEADER_LEN));

    /*�����ϢID*/
    pRelReqMsg->enMsgId    = ID_LRRC_LMM_REL_REQ;

    /*�������*/
    pRelReqMsg->enBarInd   = enBarStatus;

    /*����RRC_MM_EST_REQ*/
    NAS_LMM_SEND_MSG(pRelReqMsg);

    return;
}


VOS_VOID NAS_EMM_WaitNetworkRelInd(VOS_VOID)
{
    /* �쿴RRC�����Ƿ��Ѿ��ͷ� */
    if (NAS_EMM_YES == NAS_LMM_IsRrcConnectStatusIdle())
    {
        /*��ӡ�Ѿ��ͷ�*/
        NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_WaitNetworkRelInd:Rrc Conn release already");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_WaitNetworkRelInd_ENUM,LNAS_FUNCTION_LABEL1);

        /*ת���ڲ���REL IND*/
        NAS_EMM_CommProcConn2Ilde();
        /*֪ͨ RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    }
    else
    {
        /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_T3440);
    }
    return ;
}
VOS_VOID NAS_EMM_RelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus)
{
    /* �쿴RRC�����Ƿ��Ѿ��ͷ� */
    if (NAS_EMM_YES == NAS_LMM_IsRrcConnectStatusIdle())
    {
        /*��ӡ�Ѿ��ͷ�*/
        NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RelReq:Rrc Conn release already");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RelReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*ת���ڲ���REL IND*/
        NAS_EMM_CommProcConn2Ilde();
        /*֪ͨ RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    }
    else
    {
        /*����RRC_MM_REL_REQ*/
        NAS_EMM_SndRrcRelReq(enBarStatus);

        /* ��RRC���ͷź�����״̬��Ϊ�ͷŹ����� */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);
    }

    return ;
}
VOS_UINT32  NAS_EMM_PreProcMsgRrcMmRelCnf(MsgBlock * pMsg)
{
    VOS_UINT32                          ulCurEmmStat;

    /* ��ӡ����ú�����INFO_LEVEL */
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_PreProcMsgRrcMmRelCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcMmRelCnf_ENUM,LNAS_ENTRY);

    /*��μ��*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgRrcMmRelCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgRrcMmRelCnf_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /* ��LRRC�ͷ�ʱ�ر�CIPHERʱ��ת�Ƶ�LMM�ͷ�ʱ�ر�:��������������ȼ��ͣ���LMM��ʹ��CIPHER��ʱ��
       ������ռ��LRRC��CIPHERʱ�ӹرգ�����LMM DATA ABORT���� */
    #if (VOS_OS_VER != VOS_WIN32)
    /*�͹��ķ���Ϊ��ʡ���ģ���LTEģLNAS�յ�LRRC�ͷŵ�ʱ�������ӿڹص� cipher ʱ���Լ�ͶƱ�Ƿ��pll��
     Э��ջֻ������һ���ӿڣ��汾����֧�ɵ����ڴ˽ӿ��ڲ����з�װ*/
    (VOS_VOID)LDRV_CIPHER_DISABLE();
    #endif
    /*ֹͣ��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTHʧ�ܴ�������*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* ״̬��ջ*/
        NAS_EMM_FSM_PopState();

        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                                    NAS_EMM_CUR_SUB_STAT);

        /* 3�ο���Ȩʧ�ܺ������ͷ�, �յ�Rel Cnf, ״̬��ջ��, ��Ҫ����Ӧ����(ͬAuth Init̬���յ�Rel IND)
           ���:��3�μ�Ȩʧ�ܺ�, LNAS�����ͷ�, ֻ�˳�Auth Init״̬, ��δ�Ե�ǰ��������Ӧ����, �Ӷ�����
           ״̬�쳣, ��:ע�������3�μ�Ȩʧ�ܺ�, LMM�����ͷź󻹴���Attach Init״̬, ��ʵ����·�Ѿ��ͷ���*/
        switch(ulCurEmmStat)
        {
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                    NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                    NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                    NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                    NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                    NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                    NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            default:
                    NAS_EMM_CommProcConn2Ilde();
                    break;
        }
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_CommProcConn2Ilde();
    return NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMM_MsAuthInitEnterIdleProc(VOS_UINT32 ulCause)
{
    if (EMM_MS_REG_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_TAU_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_DEREG_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        if (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(ulCause);
        }
        else if (EMM_SS_REG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(ulCause);
        }
        else if (EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd(ulCause);
        }
        else
        {
            return ;
        }
    }
    else
    {
        return ;
    }
}





VOS_UINT32  NAS_EMM_PreProcMsgTiWaitRrcRelTO(MsgBlock * pMsg)
{
    /* ��ӡ����ú�����INFO_LEVEL */
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgTiWaitRrcRelTO is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgTiWaitRrcRelTO_ENUM,LNAS_ENTRY);

    /*��μ��*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgTiWaitRrcRelTO:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgTiWaitRrcRelTO_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    NAS_EMM_CommProcConn2Ilde();
    /* RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTHʧ�ܴ�������*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* ״̬��ջ*/
        NAS_EMM_FSM_PopState();

        NAS_EMM_MsAuthInitEnterIdleProc(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
    }
    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_PreProcMsgWaitRrcRel3440TO(MsgBlock * pMsg)
{
    /* ��ӡ����ú�����INFO_LEVEL */
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgWaitRrcRel3440TO is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgWaitRrcRel3440TO_ENUM,LNAS_ENTRY);

    /*��μ��*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgWaitRrcRel3440TO:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgWaitRrcRel3440TO_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*����RRC_MM_REL_REQ*/
    NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

    NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

    /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMM_PreProcMsgReAttachDelayTO(MsgBlock * pMsg)
{
    (VOS_VOID)pMsg;

    /* ����״̬�´����ݲ�����,������TAU��Service������޸� */

    /* ֹͣT3440��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /*���ڲ�attach���� */
    (VOS_VOID)NAS_EMM_SendIntraAttachReq();

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ETC_DATA_REQ_STRU              *pstTcdataReq = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    (VOS_VOID)ulMsgId;
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_GIM_NORMAL_LOG( "NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq_ENUM,LNAS_ENTRY);

    /*��μ��*/
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstTcdataReq = (EMM_ETC_DATA_REQ_STRU*)pMsgStru;

    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);

    if ((ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
         ||(ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        if(NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        {
            if (NAS_RELEASE_R11)
            {
                return NAS_LMM_STORE_HIGH_PRIO_MSG;
            }
            else
            {
                /* ͸��TC��Ϣ */
                NAS_EMM_SER_SendMrrcDataReq_Tcdata(pstTcdataReq);
            }
        }
    }
    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    (VOS_VOID)ulMsgId;
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);

    if ((ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
         ||(ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        if (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        {
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*������ʱ��TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* ��������״̬Ϊ�ͷŹ����� */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
    }
    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg)
{
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd: Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    /* ֹͣ��ǰ��ѹջ���� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /* ��ջ */
    NAS_EMM_FSM_PopState();


    /* EMM��EMM�Լ�����AREA LOST��Ϣ���Ը�ѹջǰ�����̴��� */
    NAS_EMMC_SendEmmCoverageLostInd();
    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTHʧ�ܴ�������*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* ״̬��ջ*/
        NAS_EMM_FSM_PopState();

        NAS_EMM_MsAuthInitEnterIdleProc(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
    }
    return  NAS_LMM_MSG_HANDLED;
}
VOS_VOID  NAS_EMM_MrrcChangeRrcStatusToIdle( VOS_VOID )
{
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_MrrcChangeRrcStatusToIdle is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcChangeRrcStatusToIdle_ENUM,LNAS_ENTRY);

    /*�����ǰ����״̬����IDLE������ MMC�ϱ�*/
    if(NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONN_IDLE);
    }

    /*��RRC����״̬��Ϊ������״̬*/
    /* mod by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,begin */
    NAS_EMM_SetConnState( NAS_EMM_CONN_IDLE);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,end */

    /*����̬��CONN����IDLE�����µ�ǰ��ȫ������״̬�仯*/
    NAS_EMM_ConnToIdleTransSecuSta();

    return;
}
VOS_VOID  NAS_EMM_ProcDeregMmcRelReq(VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU              EmmState;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcDeregMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDeregMmcRelReq_ENUM,LNAS_ENTRY);

    /* ֹͣATTACH��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);
    /*NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3416);

    /* ��EMM״̬ת����MS_DEREG + SS_PLMN_SEARCH״̬ */
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_DEREG;
    EmmState.enSubState                 = EMM_SS_DEREG_PLMN_SEARCH;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��MMC�ϱ�attach���*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_FAILURE);

    /*��RRC����RRC_MM_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;
}


VOS_VOID  NAS_EMM_ProcDetachMmcRelReq(VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU              EmmState;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcDetachMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDetachMmcRelReq_ENUM,LNAS_ENTRY);

    /* ֹͣdetach��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /* ��EMM״̬ת����MS_DEREG + SS_PLMN_SEARCH״̬ */
        EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
        EmmState.enMainState                = EMM_MS_DEREG;
        EmmState.enSubState                 = EMM_SS_DEREG_NO_IMSI;
        EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        /* ��MMC�ظ�LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();

        /* ����ο���ʶ */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;
    }/* lihong00150010 emergency tau&service end */
    else
    {
        /* ��EMM״̬ת����MS_DEREG + SS_PLMN_SEARCH״̬ */
        EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
        EmmState.enMainState                = EMM_MS_DEREG;
        EmmState.enSubState                 = EMM_SS_DEREG_NORMAL_SERVICE;
        EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);
    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��RRC����RRC_MM_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;
}
VOS_VOID  NAS_EMM_ProcRegMmcRelReq(VOS_VOID )
{
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcRegMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReq_ENUM,LNAS_ENTRY);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3416);*/

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* �ͷŻ����ESM��Ϣ*/
    NAS_EMM_SerClearEsmDataBuf();

    /* ��ս���Bar��Ϣ*/
    NAS_EMM_ClearBarResouce();


    /* ��״̬ת����MS_REG + SS_REG_PLMN_SEARCH״̬ */
    /*
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_REG;
    EmmState.enSubState                 = EMM_SS_REG_PLMN_SEARCH;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);
    */
    return;
}



VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileTauInit(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileTauInit");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileTauInit_ENUM,LNAS_ENTRY);

    /*�ͷŴ���*/
    NAS_EMM_ProcRegMmcRelReq();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

    /*����TAU�쳣������������*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;
    NAS_EMM_TAU_ProcAbnormal();
    /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ�ڳ�ͻ�ڲ����� */
    NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                    (VOS_VOID*)NAS_EMM_NULL_PTR);

    /*��RRC����RRC_MM_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}
VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileSerInit(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileSerInit");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileSerInit_ENUM,LNAS_ENTRY);

    /*�ͷŴ���*/
    NAS_EMM_ProcRegMmcRelReq();

    /*ת��״̬*/
    NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

    /*��RRC����RRC_MM_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}
VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileImsiDetach(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileImsiDetach");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileImsiDetach_ENUM,LNAS_ENTRY);

    /*��IMSI detach���д���*/
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
    NAS_LMM_ImsiDetachReleaseResource();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*����RRC���������ͷ�*/
    NAS_EMM_ProcRegMmcRelReq();

    /*ת��״̬*/
    NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

    /*��RRC����RRC_MM_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

}
/*lint +e961*/
/*lint +e960*/




/***************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ��ϵͳ+ģ��+�ļ���.c */
