


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmLppMsgProc.h"
#include "EmmLppInterface.h"
#include "NasEmmSsMsgProc.h"
#include "NasEmmSerProc.h"
#endif


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICEABNORMAL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICEABNORMAL_C
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
/* �������ı� */
NAS_LMM_SER_REJ_CAUSE_PROC_STRU  gstEmmSerRejCauseProcTbl[] =
{
    {NAS_LMM_CAUSE_ILLEGAL_UE,                                  NAS_EMM_SER_SERREJ368},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                                  NAS_EMM_SER_SERREJ368},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                          NAS_EMM_SER_SERREJ7},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,         NAS_EMM_SER_SERREJ8},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                           NAS_EMM_SER_SERREJ9},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                           NAS_EMM_SER_SERREJ10},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                              NAS_EMM_SER_SERREJ11},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                                NAS_EMM_SER_SERREJ12},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                              NAS_EMM_SER_SERREJ13},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                             NAS_EMM_SER_SERREJ15},
    {NAS_LMM_CAUSE_CS_NOT_AVAIL,                                NAS_EMM_SER_SERREJ18},
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, NAS_EMM_SER_SERREJ35},
    {NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED,                   NAS_EMM_SER_SERREJ39},
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,             NAS_EMM_SER_SERREJ40},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                      NAS_EMM_SER_SERREJ42}
};
VOS_UINT32        gstEmmSerRejCauseProcTblLen = sizeof(gstEmmSerRejCauseProcTbl)
                                                / sizeof(NAS_LMM_SER_REJ_CAUSE_PROC_STRU);

/*******************************************************************************
  Module   : NAS_EMM_SER_AbnormalNeedtoContinueTau
  Function :
  Input    :
  Output   :
  NOTE     : ��
  Return   : ��
  History  :
    1.FTY    2012-02-27  �¹�����
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_AbnormalNeedtoContinueTau(VOS_VOID)
{
    if((NAS_EMM_T3412_EXP_NO < NAS_LMM_GetEmmInfoT3412ExpCtrl())
      &&(NAS_EMM_T3412_EXP_BUTT > NAS_LMM_GetEmmInfoT3412ExpCtrl()))
    {
        return NAS_EMM_YES;
    }

    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        return NAS_EMM_YES;
    }

    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        return NAS_EMM_YES;
    }
    if(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        return NAS_EMM_YES;
    }
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange())
    {
        return NAS_EMM_YES;
    }

    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        return NAS_EMM_YES;
    }


    return NAS_EMM_NO;

}


VOS_UINT32 NAS_EMM_SER_SuccNeedtoContinueTau(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 *pulTauStartType)
{
    *pulTauStartType = NAS_LMM_OM_TAU_START_TYPE_OTHERS;

    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        *pulTauStartType = NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED;
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        *pulTauStartType = NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED;
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange())
    {
        *pulTauStartType = NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE;
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;

}


VOS_VOID    NAS_EMM_SER_RcvRrcRelInd(VOS_VOID)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_RcvRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcRelInd_ENUM,LNAS_ENTRY);

    /*����SER�Ľ��Ϊ NAS_EMM_SER_RESULT_ABNORMAL*/
    /*NAS_EMM_SER_SaveSERresult(NAS_EMM_SER_RESULT_ABNORMAL);*/
    /* lihong00150010 emergency tau&service begin */
    NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_REG+EMM_SS_REG_NORMAL_SERVICE*/
    /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/

    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

        /*send INTRA_CONN2IDLE_REQ����������״̬*/
        NAS_EMM_CommProcConn2Ilde();
        return ;
    }

    /*send INTRA_CONN2IDLE_REQ����������״̬*/
    NAS_EMM_CommProcConn2Ilde();

    /* �����δ��ɵ�TAU�������ڴ˴������ж�ʱ���ȶ�ʱ����ʱ���޶�ʱ���Ⱥ����յ�ϵͳ��Ϣ�ٴ��� */

    return;
}
VOS_VOID  NAS_EMM_ServiceReqRejectOtherCause
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_ServiceReqRejectOtherCause is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ServiceReqRejectOtherCause_ENUM,LNAS_ENTRY);

    /* ����AT&T�������󣬶�SERVICEʧ�ܳ��������Ĵ��� */
    NAS_EMM_SER_CServiceCountProc();

    /* lihong00150010 emergency tau&service begin */
    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ServiceReqRejectOtherCause: CAUSE_ESM_DATA_REQ_EMC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ServiceReqRejectOtherCause_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
    }
    /* lihong00150010 emergency tau&service end */
    /* �����δ��ɵ�TAU������REG+NORMAL_SERVICE״̬���յ�ϵͳ��Ϣ���ٴ��� */

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);


    return;
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_SerClearEsmDataBuf( VOS_VOID )
{
    VOS_UINT32                          i      = 0;
    VOS_UINT32                          ulRslt = 0;

     NAS_EMM_SER_LOG_INFO("NAS_EMM_SerClearEsmDataBuf entered!");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_SerClearEsmDataBuf_ENUM,LNAS_ENTRY);

     /**����������ݵı�־��������**************/
     for (i = 0; i < g_stEmmEsmMsgBuf.ulEsmMsgCnt; i++)
     {
         if (NAS_LMM_NULL_PTR != g_stEmmEsmMsgBuf.apucEsmMsgBuf[i])
         {
            ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM,
                                (VOS_VOID *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[i]);

            if (NAS_COMM_BUFF_SUCCESS != ulRslt)
            {
                NAS_EMM_SER_LOG_WARN("NAS_EMM_SerClearEsmDataBuf, Memory Free is not succ");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_SerClearEsmDataBuf_ENUM,LNAS_FUNCTION_LABEL1);
            }

            g_stEmmEsmMsgBuf.apucEsmMsgBuf[i] = NAS_LMM_NULL_PTR;
         }
         else
         {
             NAS_EMM_SER_LOG1_WARN("NAS_EMM_SerClearEsmDataBuf, Buffer item is null:",i);
             TLPS_PRINT2LAYER_WARNING1(NAS_EMM_SerClearEsmDataBuf_ENUM,LNAS_FUNCTION_LABEL2,i);
         }
     }

     g_stEmmEsmMsgBuf.ulEsmMsgCnt = 0;

}
VOS_UINT32 NAS_EMM_SER_IsNotEmergencyCsfb(VOS_VOID)
{
    if (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/* #7��ҪȥGU�³��� */
VOS_VOID  NAS_EMM_SER_SERREJ368
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ367 entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ368_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /* set the EPS update status to EU3 ROAMING NOT ALLOWED */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /*USIM��Ч��ֱ���ػ���ο�*/
    /*�ݲ�����*/
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI, TI_NAS_EMM_STATE_NO_TIMER);

    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if ((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        && (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb()))
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }


    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return;
}

VOS_VOID  NAS_EMM_SER_SERREJ7
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ367 entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ7_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /* set the EPS update status to EU3 ROAMING NOT ALLOWED */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);
    /*USIM��Ч��ֱ���ػ���ο�*/
    /*�ݲ�����*/
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI, TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
    }
    else if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
    }
    else
    {
    }
    #endif

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ8
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    if (NAS_RELEASE_R11)
    {
        /* �޸ĺ����� */
        NAS_EMM_SER_SERREJ368(pMsgStru);
    }
    else
    {
        NAS_EMM_ServiceReqRejectOtherCause(pMsgStru);
    }
}
VOS_VOID  NAS_EMM_SER_SERREJ9
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ9 entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ9_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /* ��������EU2 NOT UPDATED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /* ɾ��GUTI,KSIasme,TAI list,L.V.R TAI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /* ���к�ͨ������: ��R13Э��������,SerRej #9,��ҪȥGU�ϳ��� */
    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);
    /* lihong00150010 emergency tau&service begin */
    /* ����ǽ�����PDN���������SERVICE����ֱ�ӷ������ע�᣻
       ����ǽ���CSFB,ֱ���ͷ���·�������ڲ�ATTACH; */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SERREJ9: CAUSE_ESM_DATA_REQ_EMC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ9_ENUM,LNAS_FUNCTION_LABEL1);

        /*����ESM��Ϣ*/
        NAS_LMM_MEM_CPY(        (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                               &(pstEsmMsg->stEsmMsg),
                                (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();
    }
    else if (VOS_FALSE == NAS_EMM_SER_IsCsfbProcedure())
    {/* CSFB �յ�#9ʱ��ҪȥGU�³��Դ�绰 */
    /* lihong00150010 emergency tau&service end */
        if (NAS_RELEASE_R11)
        {
            /*�ȴ�RRC_REL_IND*/
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
            /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
               ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����*/
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);
        }
    }
    else
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    /* ���SER��TAU������Դ*/
    NAS_EMM_SER_ClearResource();
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;

}
VOS_VOID  NAS_EMM_SER_SERREJ10
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ10 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ10_ENUM,LNAS_ENTRY);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /* ���к�ͨ������: ��R13Э��������,SerRej #10,��ҪȥGU�ϳ��� */

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /* ת��EMM״̬��MS_DEREG+SS_DEREG_NORMAL_SERVICE:״̬ת������ִ��ɾ���°�ȫ������*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ����DEREG̬����дͳһд��ȫ�����ģ����ձ�ˣ���SER��#10�ܾ�������ȫ������д�� */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
    /* lihong00150010 emergency tau&service end */
    /* ����ǽ�����PDN���������SERVICE����ֱ�ӷ������ע�᣻
       ����ǽ���CSFB,ֱ���ͷ���·�������ڲ�ATTACH; */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SERREJ10: CAUSE_ESM_DATA_REQ_EMC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ10_ENUM,LNAS_FUNCTION_LABEL1);

        /*����ESM��Ϣ*/
        NAS_LMM_MEM_CPY(        (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                               &(pstEsmMsg->stEsmMsg),
                                (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();
    }
    else if (VOS_FALSE == NAS_EMM_SER_IsCsfbProcedure())
    {/* CSFB�����յ�ESR #10ʱ,��ҪȥGU�³��� */
        if (NAS_RELEASE_R11)
        {
            /*�ȴ�RRC_REL_IND*/
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
            /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
               ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����*/
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);

        }

    }
    else
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    /* ���SER��TAU������Դ*/
    NAS_EMM_SER_ClearResource();
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;

}
VOS_VOID  NAS_EMM_SER_SERREJ11
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{
     /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ11 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ11_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,L.V.R TAI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_DEREG+EMM_SS_DEREG_LIMITED_SERVICE*/
    /*�յ�MMC����ָ�����ת��PLMN_SEARCH̬*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_LIMITED_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }

    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
    }
    #endif

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ12
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{

    NAS_MM_TA_STRU                      stTa;

    /* ��ȡ��ǰTA */
    NAS_EMM_GetCurrentTa(&stTa);

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ12 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ12_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,L.V.R TAI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*store the current TAI in the list of
                  "forbidden tracking areas for regional provision of service"*/
    NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_LIMITED_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }
    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
    }
    #endif

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ13
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{

    NAS_MM_TA_STRU                      stCurrentTa;
    NAS_MM_TA_LIST_STRU                *pstTaiList;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ13 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ13_ENUM,LNAS_ENTRY);

    /*����EU3 ROAMING NOT ALLOWED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /* lihong00150010 emergency tau&service end */
    /*Remove current TA from TAI List*/
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* ��Ҫ�ѵ�ǰTA����ʱ�б����޳� */
    NAS_LMM_DelCurrTaFromGradualForbTaList(&stCurrentTa);

    pstTaiList = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_DeleteTaFromTaList(&stCurrentTa, pstTaiList, NAS_MM_MAX_TA_NUM);

    /*store the current TAI in the list of
                "forbidden tracking areas for roaming"*/
    NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());

    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    /* lihong00150010 emergency tau&service begin */
    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }

    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
    }
    #endif

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_SER_SERREJ13: CAUSE_ESM_DATA_REQ_EMC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ13_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_LIMITED_SERVICE);
    }
    else
    {
        /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_REG+SS_REG_LIMITED_SERVICE�յ�MMC����ָ��
          ����ת��PLMN_SEARCH̬*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);
    }
    /* lihong00150010 emergency tau&service end */
    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ15
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{

    NAS_MM_TA_STRU                      stCurrentTa;
    NAS_MM_TA_LIST_STRU                *pstTaiList;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enGradualForbResult = NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ15 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ15_ENUM,LNAS_ENTRY);

    /*����EU3 ROAMING NOT ALLOWED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /* lihong00150010 emergency tau&service end */
    /*Remove current TA from TAI List*/
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    pstTaiList = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_DeleteTaFromTaList(&stCurrentTa, pstTaiList, NAS_MM_MAX_TA_NUM);

    /* �жϼ�����ʱ�����б��� */
    enGradualForbResult = NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa);

    /* �ж��Ƿ���Ҫ����ROAM Forb�б� */
    if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == enGradualForbResult)
    {
        /*store the current TAI in the list of
                       "forbidden tracking areas for roaming"*/
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
    }
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    /* lihong00150010 emergency tau&service begin */
    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }

    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ== NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
    }
    #endif

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_SER_SERREJ15: CAUSE_ESM_DATA_REQ_EMC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ15_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_LIMITED_SERVICE);
    }
    else
    {
        /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_REG+SS_REG_LIMITED_SERVICE�յ�MMC����ָ��
          ����ת��PLMN_SEARCH̬*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);
    }
    /* lihong00150010 emergency tau&service end */
    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ18
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    /* ���Կ�ģʽ�£�����Э��Ҫ�����CSFB����
       �ǲ��Կ�ģʽ��,Ϊ�����û����飬����ֹ�绰��������GU�¼�����绰 */
    if ((PS_SUCC == LPS_OM_IsTestMode())
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        && (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb()))
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }

    /*ת��EMM״̬��MS_REG+SS_REG_NORMAL_SERVIC*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /* ����̬�£��ͷ���·��������GU�¼�����绰 */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        #if (FEATURE_ON == FEATURE_PTM)
        if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
        }
        else if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
        }
        else
        {
        }
        #endif
    }

    return;

}

VOS_VOID NAS_EMM_SER_SERREJ35
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    /* �ж�nas r10�����Ƿ�� */
    if (NAS_RELEASE_CTRL)
    {
        NAS_EMM_SER_SERREJ11(pMsgStru);
    }
    else
    {
        NAS_EMM_ServiceReqRejectOtherCause(pMsgStru);
    }
    return;

}
VOS_VOID  NAS_EMM_SER_SERREJ40
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ40 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ40_ENUM,LNAS_ENTRY);

    (VOS_VOID)pMsgStru;

    /* ����EMM_ESM_STATUS_IND(ȥע��)*/
    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ת��EMM״̬��MS_DEREG+SS_DEREG_NORMAL_SERVICE:״̬ת������ִ��ɾ���°�ȫ������*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /* �����CSFB���̻����CSFB������ѡ��GUģ */
    if ((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        || (VOS_FALSE == NAS_EMM_SER_IsNotEmergencyCsfb()))
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        if (NAS_RELEASE_R11)
        {
            /*�ȴ�RRC_REL_IND*/
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
                /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
                   ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����
                */
                NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);
        }
    }

    /* ���SER��TAU������Դ*/
    NAS_EMM_SER_ClearResource();
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;
}
VOS_VOID  NAS_EMM_SER_SERREJ39
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)
{
    VOS_UINT32                      ulTimerLen      = NAS_EMM_NULL;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ39 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ39_ENUM,LNAS_ENTRY);

    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if ((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        && (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb()))
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ, pMsgStru->ucEMMCause);
    }

    /*ת��EMM״̬��MS_REG+SS_REG_NORMAL_SERVIC*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

    /* ����ǽ���CSFB���߲�����������̬,�����ͷ� */
    if ((VOS_FALSE == NAS_EMM_SER_IsNotEmergencyCsfb())
        || (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState()))
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    if (NAS_EMM_BIT_SLCT != pMsgStru->ucBitOpT3442)
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_SERREJ39:No T3442!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_SERREJ39_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    ulTimerLen = NAS_EMM_TimerValTransfer(  pMsgStru->stT3442.ucUnit,
                                            pMsgStru->stT3442.ucTimerVal);

    if (NAS_EMM_NULL != ulTimerLen)
    {
        NAS_LMM_ModifyStateTimer(TI_NAS_EMM_STATE_SERVICE_T3442,ulTimerLen);
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3442);
    }

    return;
}


VOS_VOID  NAS_EMM_SER_SERREJ42
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
)

{
     /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SERREJ42 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SERREJ42_ENUM,LNAS_ENTRY);

    if (NAS_RELEASE_R11)
    {
        /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
        /*����EU3 ROAMING NOT ALLOWED*/
        NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_NOT_UPDATED_EU2;

        /*ɾ��GUTI,KSIasme,TAI list,L.V.R TAI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
        /* lihong00150010 emergency tau&service begin */
        if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

            /* ��¼ATTACH����ԭ��ֵ */
            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
        }
        else
        {
            NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
        }
        /* lihong00150010 emergency tau&service end */
        /*ת��EMM״̬��MS_DEREG+EMM_SS_DEREG_LIMITED_SERVICE*/
        /*�յ�MMC����ָ�����ת��PLMN_SEARCH̬*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_LIMITED_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

        /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
        if ((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            && (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb()))
        {
            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_REJ,pMsgStru->ucEMMCause);
        }

        /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendSerResultIndRej(pMsgStru->ucEMMCause);

        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        NAS_EMM_ServiceReqRejectOtherCause(pMsgStru);
    }

    return;
}


#if (FEATURE_PTM == FEATURE_ON)
 VOS_VOID NAS_EMM_SerCnRejErrRecord(
                    NAS_EMM_CN_SER_REJ_STRU *pMsgStru,
                    EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8 enCsfbFailCause,
                    EMM_OM_ERRLOG_TYPE_ENUM_UINT16   enErrlogType)
 {
      if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
      {
          NAS_EMM_ExtServiceErrRecord(
                  pMsgStru->ucEMMCause,
                  enCsfbFailCause);
      }
      else
      {
          NAS_EMM_NorServiceErrRecord((VOS_VOID*)pMsgStru, enErrlogType);
      }
 }
#endif


VOS_VOID    NAS_EMM_SER_RcvServiceRejectMsg(NAS_EMM_CN_SER_REJ_STRU   *pMsgStru)
{
    VOS_UINT32                              ulIndex = 0;
    NAS_LMM_SER_REJ_CAUSE_PROC_FUN          pfRejCauseProcFun;

    NAS_EMM_SER_LOG_INFO( "Nas_Emm_Ser_RcvServiceRejectMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvServiceRejectMsg_ENUM,LNAS_ENTRY);

    /*�쳣ֹͣ SER*/
    NAS_EMM_SER_AbnormalOver();

    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

    /*����SER�Ľ��Ϊ NAS_EMM_SER_RESULT_REJ*/
    /*NAS_EMM_SER_SaveSERresult(NAS_EMM_SER_RESULT_REJ);*/

    NAS_LMM_AdaptRegRejCau(&(pMsgStru->ucEMMCause));



    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_SerCnRejErrRecord((VOS_VOID*)pMsgStru, EMM_OM_LMM_CSFB_FAIL_CAUSE_CN_REJ, EMM_OM_ERRLOG_TYPE_CN_REJ);
    #endif

    for (ulIndex = 0; ulIndex < gstEmmSerRejCauseProcTblLen; ulIndex++)
    {
        if (pMsgStru->ucEMMCause == gstEmmSerRejCauseProcTbl[ulIndex].enRejCauseVal)
        {
            pfRejCauseProcFun = gstEmmSerRejCauseProcTbl[ulIndex].pfRejCauseProcFun;

            /* �д����� */
            if (VOS_NULL_PTR != pfRejCauseProcFun)
            {
                (pfRejCauseProcFun)(pMsgStru);
            }
            return;
        }
    }

    /* ����ԭ��ֵ�Ĵ��� */
    NAS_EMM_ServiceReqRejectOtherCause(pMsgStru);

    return;

}
VOS_VOID NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm(VOS_VOID)
{
    NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId = NAS_LMM_STATE_TI_BUTT;

    if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
    {
        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm:Upt-MM state.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm_ENUM,LNAS_FUNCTION_LABEL1);

            /* ��״̬ת����MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM״̬ */
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* ��״̬ת����MS_REG + SS_REG_NORMAL_SERVICE״̬ */
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }

    }
    else
    {
        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm: with imsi attach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_SendIntraTauReq(    ID_APP_MM_MSG_TYPE_BUTT,
                                    NAS_LMM_INTRA_TAU_TYPE_UPDATE_MM);
            return;
        }

        NAS_EMM_TAU_LOG_NORM("NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm: normal service state.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm_ENUM,LNAS_FUNCTION_LABEL3);
        /* ��״̬ת����MS_REG + SS_REG_NORMAL_SERVICE״̬ */
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    }
    return;

}

/* lihong00150010 emergency tau&service begin */

VOS_VOID NAS_EMM_TranStatePsNormalServiceOrPsLimitService(VOS_VOID)
{
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();
    }
}
/* lihong00150010 emergency tau&service end */

VOS_VOID  NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd( VOS_UINT32 ulCause)
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*ֹͣSERVICE����*/
    NAS_EMM_SER_AbnormalOver();

    /* CSFB���̵Ĵ��� */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd:CSFB");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd_ENUM,LNAS_FUNCTION_LABEL1);

        /*ת��EMM״̬��MS_REG+SS_REG_NORMAL_SERVICE*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);
        if ((LRRC_LNAS_REL_CAUSE_L2GU_REDIRECT != ulCause) && (LRRC_LNAS_REL_CAUSE_CSFB_HIGH_PRIOR != ulCause))
        {
            /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

            #if (FEATURE_PTM == FEATURE_ON)
            if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            {
                NAS_EMM_ExtServiceErrRecord(EMM_OM_ERRLOG_CN_CAUSE_NULL, EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_REL_OTHER);
            }
            #endif
        }

        /*send INTRA_CONN2IDLE_REQ����������״̬*/
        NAS_EMM_CommProcConn2Ilde();
        return;
    }
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd:CAUSE_ESM_DATA_REQ_EMC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_NORMAL_SERVICE);

        /*send INTRA_CONN2IDLE_REQ����������״̬*/
        NAS_EMM_CommProcConn2Ilde();
        return;
    }
    /* lihong00150010 emergency tau&service end */

    /*upon different cause value, enter different dealing*/
    switch (ulCause)
    {
        case LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ:
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(  NAS_EMM_COLLISION_SERVICE);
            /*NAS_EMM_TAU_StartTAUREQ(             NAS_EMM_MSG_LOAD_BALANCING_TAU);*/
            /*
            NAS_EMM_TAUSER_FSMTranState(       EMM_MS_REG,
                                                EMM_SS_REG_PLMN_SEARCH,
                                                TI_NAS_EMM_STATE_NO_TIMER);
            */
            NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

            /*send INTRA_CONN2IDLE_REQ����������״̬*/
            NAS_EMM_CommProcConn2Ilde();
            break;

        case LRRC_LNAS_REL_CAUSE_CONN_FAIL:
            /* NAS_EMM_TAU_SaveEmmTAUStartCause(    NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE); */
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
            /*NAS_EMM_TAU_SaveEmmCollisionCtrl(    NAS_EMM_COLLISION_SERVICE);*/
            /*NAS_EMM_TAU_StartTAUREQ(             NAS_EMM_MSG_LOAD_BALANCING_TAU);*/
            /*
            NAS_EMM_TAUSER_FSMTranState(       EMM_MS_REG,
                                                EMM_SS_REG_PLMN_SEARCH,
                                                TI_NAS_EMM_STATE_NO_TIMER);
            */
            NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

            /*send INTRA_CONN2IDLE_REQ����������״̬*/
            NAS_EMM_CommProcConn2Ilde();
            break;

        default:
            NAS_EMM_SER_RcvRrcRelInd();
            break;
    }

    return;
}
VOS_UINT32  NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)

{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthRej enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthRej_ENUM,LNAS_ENTRY);

    /* ��Ȩ�ܾ��Ż����� */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);


    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgRrcRelInd(
                                                            VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru)
{
    LRRC_LMM_REL_IND_STRU                 *pRrcRelInd     = (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                          ulCause;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCnSerCnfMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*���ԭ��ֵ*/
    ulCause                                             =   pRrcRelInd->enRelCause;
    /* ������: ����Ser Rel Fail���� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_NorServiceErrRecord((VOS_VOID*)pMsgStru, EMM_OM_ERRLOG_TYPE_LRRC_REL);
    #endif

    NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(        ulCause);

    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp(  VOS_UINT32  ulMsgId,
                                                             VOS_VOID   *pMsgStru
                                                          )
{
    VOS_UINT32                      ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    /* ������: ����Ser ��ʱ����ʱ���� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EXP);
    /* ����AT&T�������󣬶�SERVICEʧ�ܳ��������Ĵ��� */
    NAS_EMM_SER_CServiceCountProc();

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_NorServiceErrRecord((VOS_VOID*)pMsgStru, EMM_OM_ERRLOG_TYPE_TIMEOUT);
    #endif

    /*���SR����������SMS��������Ҫ�ظ�SMS����ʧ�ܣ��������SR�ķ���ԭ��*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif

    /*���ESM_DATA����*/
    NAS_EMM_SerClearEsmDataBuf();

    /* ����AT&T��������SERVICE��ʱ��֪ͨMMCʧ�ܴ��� */
    NAS_EMM_MmcSendSerResultIndT3417Exp();

    /*Inform RABM that SER fail*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp: CAUSE_ESM_DATA_REQ_EMC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
    }
    /* lihong00150010 emergency tau&service end */
    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;

}

VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                      ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_AbnormalOver();

    #if (FEATURE_PTM == FEATURE_ON)
        if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        {
            NAS_EMM_ExtServiceErrRecord(EMM_OM_ERRLOG_CN_CAUSE_NULL, EMM_OM_LMM_CSFB_FAIL_CAUSE_EXT3417_EXP);
        }
    #endif

    /* ״̬Ǩ�Ƶ�REG.NORMAL_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                            EMM_SS_REG_NORMAL_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

    if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
    {

        if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
        {
            /* �����δ��ɵ�TAU������REG+NORMAL_SERVICE״̬���յ�ϵͳ��Ϣ���ٴ��� */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
        }
    }
    /* ������ǽ���CSFB��MO CSFB��MM����ֹ��Ϣ,�����MMC�ϱ�SER����ͷŵȹ��� */
    else if ((VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb())
         && (VOS_FALSE == NAS_EMM_SER_IsMoCsfbProcedure()))
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_NULL);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT, NAS_LMM_CAUSE_NULL);
        if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
        {
            /* �����δ��ɵ�TAU������REG+NORMAL_SERVICE״̬���յ�ϵͳ��Ϣ���ٴ��� */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
        }
    }
    else
    {
        /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
        /* NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);*/

        /* ����AT&T���������޸Ľӿڣ�EXT SERVICE��ʱ��֪ͨMMC��ʱʱʧ�ܴ������� */
        NAS_EMM_MmcSendSerResultIndT3417Exp();

        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32 NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject(  VOS_UINT32  ulMsgId,
                                                                  VOS_VOID   *pMsgStru
                                                              )
{
    VOS_UINT32                      ulRslt          = NAS_EMM_FAIL;
    NAS_EMM_CN_SER_REJ_STRU         *pstserrej      = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);

    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    /* ������: ����Ser Rej���� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ);
    /*ֹͣT3416��ɾ��RAND,RES*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*������Ϣ������*/
    pstserrej  =  (NAS_EMM_CN_SER_REJ_STRU*)pMsgStru;
    NAS_EMM_SER_RcvServiceRejectMsg(pstserrej);

    return NAS_LMM_MSG_HANDLED;
}


VOS_VOID NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej(VOS_UINT32  ulCause)
{
    NAS_EMM_SER_LOG_INFO(              "NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulCause;

    /*��ֹSER*/
    NAS_EMM_SER_AbnormalOver();
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /* �����CSFB���̣��Ҳ��ǽ���CSFB�����MM����ֹ��Ϣ */
    if ((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        && (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb()))
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_AUTH_REJ, NAS_LMM_CAUSE_NULL);
    }

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /* set the EPS update status to EU3 ROAMING NOT ALLOWED */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*USIM��Ч��ֱ���ػ���ο�*/
    /*�ݲ�����*/
    /* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* lihong00150010 emergency tau&service end */
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI, TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_AUTH_REJ);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);


    return;
}
/*lint +e961*/
/*lint +e960*/

VOS_VOID NAS_EMM_SerbarCommProc(VOS_VOID)
{
    /*ֹͣSERVICE����*/
    NAS_EMM_SER_AbnormalOver();
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND, TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_ACCESS_BARED);

    /*send INTRA_CONN2IDLE_REQ����������״̬*/
    NAS_EMM_CommProcConn2Ilde();

    #if (FEATURE_PTM == FEATURE_ON)
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_ExtServiceErrRecord(EMM_OM_ERRLOG_CN_CAUSE_NULL, EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_EST_ACCESS_BAR);
    }
    #endif


    return;
 }
VOS_VOID  NAS_EMM_SER_ProcMoCallAccessBar(VOS_VOID)

{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ProcMoCallAccessBar is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ProcMoCallAccessBar_ENUM,LNAS_ENTRY);
    if((NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
       /*��ӦѰ����SERVICE���̲�����RRC_EST_ACCESS_BARRED_MO_CALL�����*/
        NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_ProcMoCallAccessBar:Barred Type ERR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_ProcMoCallAccessBar_ENUM,LNAS_ERROR);
        return;
    }

    NAS_EMM_SerbarCommProc();

    return;
}
VOS_VOID  NAS_EMM_SER_ProcBarAllAccessBar(VOS_VOID)

{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ProcBarAllAccessBar is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ProcBarAllAccessBar_ENUM,LNAS_ENTRY);
    if (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_ProcBarAllAccessBar:emergency Barred Type ERR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_ProcBarAllAccessBar_ENUM,LNAS_ERROR);
        return;
    }

    NAS_EMM_SerbarCommProc();

    return;
}


VOS_VOID  NAS_EMM_SER_ProcMoCsfbAccessBar(VOS_VOID)

{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ProcMoCsfbAccessBar is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ProcMoCsfbAccessBar_ENUM,LNAS_ENTRY);
    if(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        /*ֹͣSERVICE����*/
        NAS_EMM_SER_AbnormalOver();

        /*�����MMC�ϱ������������Lģ����bar�����´���CSFB����*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND, TI_NAS_EMM_STATE_NO_TIMER);

        /*send INTRA_CONN2IDLE_REQ����������״̬*/
        NAS_EMM_CommProcConn2Ilde();
    }
    return;
}
VOS_VOID  NAS_EMM_SER_ProcMoCallAndCsfbAccessBar(VOS_VOID)

{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ProcMoCallAndCsfbAccessBar is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ProcMoCallAndCsfbAccessBar_ENUM,LNAS_ENTRY);
    if((NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        /*��ӦѰ����SERVICE���̲�����RRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB�����*/
        NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_ProcMoCallAndCsfbAccessBar:mo call and csfb Barred Type ERR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_ProcMoCallAndCsfbAccessBar_ENUM,LNAS_ERROR);
        return;
    }
    NAS_EMM_SerbarCommProc();

    return;
}
VOS_VOID  NAS_EMM_SER_ProcCellSearchFail(VOS_VOID)

{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ProcCellSearchFail is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ProcCellSearchFail_ENUM,LNAS_ENTRY);

    /* ERABM�յ�ID_EMM_ERABM_REEST_IND���ʧ�ܻ���ID_EMM_ERABM_RRC_CON_REL_INDʱ��������ֹͣ1s��ʱ��������ʱ����������ʱ��
       ERABM��CDS֪ͨ�ٴδ���LMM��������
       ��LRRC cell searchʱ����ܻ�ܳ��������ᵼ��ƹ��ЧӦ(ERABMһֱ����LMM������)���������������ȼ�������Ȳ���
       ���Դ˴�:ser����ʧ��ԭ��ΪLRRC_EST_CELL_SEARCHINGʱ������ERABM����ID_EMM_ERABM_REEST_IND��ID_EMM_ERABM_RRC_CON_REL_IND��Ϣ */

    /*ֹͣT3417��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ֹͣT3440��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /*ֹͣT3417ext��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*���SR����������SMS��������Ҫ�ظ�SMS����ʧ�ܣ��������SR�ķ���ԭ��*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        /* SER�쳣��ԭ��ֵ�ϱ���ʱ��LMM_SMS_ERR_CAUSE_OTHERS��
           �Ժ����Ҫ������Ӧ��ԭ��ֵ���о���ϸ�ִ����ϱ�׼ȷ��ԭ��ֵ
           �˴���Ϊ�������� */
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif

    /*���ESM_DATA����*/
    NAS_EMM_SerClearEsmDataBuf();

    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /*modified by jiqiang for CSFB 20140922 begin */
        /* ��UE���������з���CSFB��ext_service����֮���յ�LRRC_LMM_EST_CNF,ԭ��ֵΪRRC_EST_CELL_SEARCHING��
        ������ʱTimer�����ٷ���MMC_LMM_SERVICE_RSLT_FAILURE;begin*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);
        /*modified by jiqiang for CSFB 20140922 end */
    }

    NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

    /*�����ǰ����״̬����IDLE������ MMC�ϱ�*/
    if(NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(MMC_LMM_STATUS_TYPE_CONN_STATE,
                                 MMC_LMM_CONN_IDLE);
    }

    /* ��RRC����״̬����ΪIDLE */
    NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);

    NAS_EMM_ClrAllUlDataReqBufferMsg();


    return;
}
VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd(   VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{

    VOS_UINT32                          ulRslt;
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *pMrrcConnectFailRelInd       = NAS_EMM_NULL_PTR;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd_ENUM,LNAS_ENTRY);
    pMrrcConnectFailRelInd              = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)pMsgStru;

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ������: ����ESM FAILԭ��ֵ��ͬ���и��¼��� */
    NAS_LMM_UpdateSerEstFailCounter(pMrrcConnectFailRelInd->enEstResult);
    /* lihong00150010 emergency tau&service begin */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        /*ֹͣSERVICE����*/
        NAS_EMM_SER_AbnormalOver();

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();

        /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
        #endif
        NAS_EMM_CommProcConn2Ilde();

        if (LRRC_EST_CELL_SEARCHING == pMrrcConnectFailRelInd->enEstResult)
        {
            /* ��¼ATTACH����ԭ��ֵ */
            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_PLMN_SEARCH,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /*����ESM��Ϣ*/
            /*lint -e960*/
            NAS_LMM_MEM_CPY(        (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                                   &(pstEsmMsg->stEsmMsg),
                                    (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);
            /*lint +e960*/
            NAS_EMM_StartEmergencyAttach();
        }

        return  NAS_LMM_MSG_HANDLED;
    }
    /* lihong00150010 emergency tau&service end */

    /*Process according different EST result*/
    switch(pMrrcConnectFailRelInd->enEstResult)
    {
        case    LRRC_EST_ACCESS_BARRED_MO_CALL:

                /*����bar���̺�����*/
                NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_SERVICE, pMrrcConnectFailRelInd->enEstResult);

                NAS_EMM_SER_ProcMoCallAccessBar();

                break;
        case    LRRC_EST_ACCESS_BARRED_ALL:

                /*����bar���̺�����*/
                NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_SERVICE, pMrrcConnectFailRelInd->enEstResult);

                NAS_EMM_SER_ProcBarAllAccessBar();
                break;

        case    LRRC_EST_ACCESS_BARRED_MO_CSFB:
                /*����bar���̺�����*/
                NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_SERVICE, pMrrcConnectFailRelInd->enEstResult);

                NAS_EMM_SER_ProcMoCsfbAccessBar();
                break;

        case    LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB:

                /*����bar���̺�����*/
                NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_SERVICE, pMrrcConnectFailRelInd->enEstResult);

                NAS_EMM_SER_ProcMoCallAndCsfbAccessBar();
                break;
                /* ����ʧ�ܣ�RRC���ڽ���С��������Ǩ�Ƶ�Reg.Plmn_Search*/
        case    LRRC_EST_CELL_SEARCHING:

                NAS_EMM_SER_ProcCellSearchFail();
                break;

        default:
                /*ֹͣSERVICE����*/
                NAS_EMM_SER_AbnormalOver();
                NAS_EMM_SER_RcvRrcRelInd();

                #if (FEATURE_PTM == FEATURE_ON)
                if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
                {
                    NAS_EMM_ExtServiceErrRecord(EMM_OM_ERRLOG_CN_CAUSE_NULL, EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_EST_FAIL);
                }
                #endif

                break;

    }
    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMM_SndServiceReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{

    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndServiceReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndServiceReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }
    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }
    /* ������: ����Ser REQ Snd Fail���� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:

            /*  ��Ҫ����Ӧ�Ļ�����Ϣ��ulHoWaitSysInfoFlag����Ϊtrue */
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            /*ֹͣT3417��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ֹͣT3440��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*ֹͣT3417ext��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*������ʱ��3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;
}

VOS_UINT32 NAS_EMM_SndExtendedServiceReqSuccProc(VOS_VOID* pMsg)
{
    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/

    NAS_EMM_SetCsfbProcedureFlag(PS_TRUE);

    /* ESR�տڷ��ͳɹ�(��REJ BY UE),֪ͨLRRC CSFB��������,LRRC�յ�����Ϣ���������ʱ��,����ʱ����ʱ֮ǰδ�յ������ͷ�
       ��Ϣ,LRRC�����ͷ�,���ڽ��CSFB�������಻�·��ض����ͷŵ�����*/
    if((NAS_EMM_CSFB_RSP_REJECTED_BY_UE == NAS_EMM_SER_GetEmmSerCsfbRsp())
        &&(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndExtendedServiceReqSuccProc CSFB Rej By Ue");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SndExtendedServiceReqSuccProc_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }
    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_START);
    return NAS_EMM_SUCC;
}


VOS_UINT32 NAS_EMM_SndExtendedServiceReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;


    *pulIsDelBuff = VOS_TRUE;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndExtendedServiceReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndExtendedServiceReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }

    if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndExtendedServiceReqFailProc: ABORT!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndExtendedServiceReqFailProc_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_EMM_SUCC;
    }

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:

            /*  ��Ҫ����Ӧ�Ļ�����Ϣ��ulHoWaitSysInfoFlag����Ϊtrue */
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        /* ����������Ϣʱ,LRRC����RF��Դ״̬,��RF��Դ������LRRC������ԭ��ֵ,��־ulNoRfWaitSysInfoFlag�����ж�֮��LMM�յ�ϵͳ��Ϣ���ش��ÿտڡ�
           ��ǰʵ�ֽ�����LRRC��Ȼ���LMM�ϱ�REL_IND����SYSTEM_INFO_IND��Ϣ*/
        case LRRC_LMM_SEND_RSLT_NO_RF:
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

            break;
        #endif
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            /* ����SERVICE ���� */
            /*ֹͣT3417��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ֹͣT3440��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*ֹͣT3417ext��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*������ʱ��3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            break;

        default:
            /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
            ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
            ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
            �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
            if(PS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            {
                NAS_EMM_SetCsfbProcedureFlag(PS_TRUE);
            }
            break;
        }

    return NAS_EMM_SUCC;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


