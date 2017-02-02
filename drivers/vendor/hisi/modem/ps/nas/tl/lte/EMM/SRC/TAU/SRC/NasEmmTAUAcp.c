

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "EmmLppInterface.h"
#include "NasEmmLppMsgProc.h"
#include    "NasEmmSsMsgProc.h"
#endif

/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin */
#include "NasMmlCtx.h"
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, end */

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUACP_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUACP_C
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

/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_TAU_SetLai(VOS_VOID *pstRcvMsg )
{
    NAS_EMM_CN_TAU_ACP_STRU             *pstTauAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_SetLai: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SetLai_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTauAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;

    if(NAS_EMM_BIT_SLCT == pstTauAcp->ucBitOpLai)
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_SetLai: LAI is valid");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SetLai_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAU_GetOpLai()          = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_EMM_TAU_GetLaiAddr(),
                                        &pstTauAcp->stLai,
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    else
    {
        NAS_EMM_TAU_GetOpLai()          = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                NAS_EMM_TAU_GetLaiAddr(),
                                        0,
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    return;
}
VOS_VOID  NAS_EMM_TAU_SetMsId(VOS_VOID *pstRcvMsg )
{
    NAS_EMM_CN_TAU_ACP_STRU             *pstTauAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_SetMsId: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SetMsId_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTauAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;

    if(NAS_EMM_BIT_SLCT == pstTauAcp->ucBitOpMsId)
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_SetMsId: MS ID is valid");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SetMsId_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAU_GetOpMsId()         = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_EMM_TAU_GetMsIdAddr(),
                                        &pstTauAcp->stMsId,
                                        sizeof(MMC_LMM_MS_IDNETITY_STRU));
    }
    else
    {
        NAS_EMM_TAU_GetOpMsId()         = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                NAS_EMM_TAU_GetMsIdAddr(),
                                        0,
                                        sizeof(MMC_LMM_MS_IDNETITY_STRU));
    }
    return;
}
VOS_VOID  NAS_EMM_TAU_SetCnCause(VOS_VOID *pstRcvMsg )
{
    NAS_EMM_CN_TAU_ACP_STRU             *pstTauAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_SetCnCause: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SetCnCause_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTauAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;
    if(NAS_EMM_BIT_SLCT == pstTauAcp->ucBitOpEmmCau)
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_SetEplmnList: EPLMN is valid");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SetCnCause_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAU_GetOpCnCause()      = NAS_EMM_BIT_SLCT;
        NAS_EMM_TAU_GetCnCause()        = pstTauAcp->ucEMMCause;
        NAS_MML_SetOriginalRejectCause(pstTauAcp->ucEMMCause);
    }
    else
    {
        NAS_EMM_TAU_GetOpCnCause()      = NAS_EMM_BIT_NO_SLCT;
        NAS_EMM_TAU_GetCnCause()        = NAS_LMM_CAUSE_NULL;
        NAS_MML_SetOriginalRejectCause(NAS_LMM_CAUSE_NULL);
    }
    return;
}
VOS_VOID  NAS_EMM_TAU_SetEplmnList(VOS_VOID *pstRcvMsg )
{
    NAS_EMM_CN_TAU_ACP_STRU             *pstTauAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_SetEplmnList: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SetEplmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTauAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;

    if(NAS_EMM_BIT_SLCT == pstTauAcp->ucBitOpEquivalentPLMNs)
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_SetCnCause: cause is valid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SetEplmnList_ENUM,LNAS_FUNCTION_LABEL1);


        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()    = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        &pstTauAcp->stEquivalentPLMNs,
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }
    else
    {

        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()    = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        0,
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    return;
}
VOS_VOID NAS_EMM_TAU_TauAcpEmergencyCsfbSerCollisionProc(VOS_VOID)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, begin */
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, end */

    /*��MMC�ϱ�TAU���*/
    NAS_EMM_MmcSendTauActionResultIndSucc();

    /* �����SMS ONLY�������� (�������� ���� CSFB_NOT_PREFERED)������Ҫdisable LTE */
    if((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == enAddUpdateRslt)
        || ((NAS_LMM_UE_CS_PS_MODE_1 == NAS_LMM_GetEmmInfoUeOperationMode())
            &&(NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt)))
    {
        /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

        /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        NAS_EMM_DisableLteCommonProc();
    }
    else
    {
        /* ����UE����CSFB */
        NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

        /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

        /*������ʱ��3417ext*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);
    }

    return ;
}


VOS_VOID NAS_EMM_TAU_TauAcpNormalCsfbSerCollisionProc(VOS_VOID)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, begin */
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, end */

    if (NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == enAddUpdateRslt)
    {
        /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

        NAS_EMM_MmcSendTauActionResultIndSucc();

        /* ����SMS ONLY,��ͨCSFB����ȥGU��Э��˵��Ҫ�ٷ���MO CSFB��EXT SER������������ȥGU */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

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
        return ;
    }

    if ((NAS_EMM_YES == NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded())
        && (NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt))
    {
        /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

        /* ��֪ͨTAU�����Ȼ��֪ͨMMģ����Ҫ��GUģȥ����CS������ */
        NAS_EMM_MmcSendTauActionResultIndSucc();
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        /*NAS_EMM_DisableLteCommonProc();*/
        return ;
    }

    NAS_EMM_MmcSendTauActionResultIndSucc();

    /* ����UE����CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /* ��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

    /* ������ʱ��3417ext */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF */
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);
    return ;
}


VOS_VOID NAS_EMM_TAU_TauAcpSerCollisionProc(VOS_VOID)
{
    /* ����SERVICE����ԭ��Ĳ�ͬ��������Ӧ���� */
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:

            NAS_EMM_MmcSendTauActionResultIndSucc();
            NAS_LMM_SndLmmSmsEstCnf();
            NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
            NAS_EMM_SER_SndEsmBufMsg();

            /* ʶ����ҪDISABLE LTE�ĳ�������RRC����·�ͷ����� */
            /*NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable();*/
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
            return;

        /* �����������TAU��Ӧ�������CSFB��֧��������ж���Ҫ�����Ϸ����� */
        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:

            if ((NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
                && (NAS_EMM_CSFB_ABORT_FLAG_VALID != NAS_EMM_SER_GetEmmSerCsfbAbortFlag()))
            {
                NAS_EMM_TAU_TauAcpNormalCsfbSerCollisionProc();
                return;
            }
            break;

        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

            if ((NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
                && (NAS_EMM_CSFB_ABORT_FLAG_VALID != NAS_EMM_SER_GetEmmSerCsfbAbortFlag()))
            {
                NAS_EMM_TAU_TauAcpEmergencyCsfbSerCollisionProc();
                return;
            }
            break;

        default:
            break;
    }

    NAS_EMM_MmcSendTauActionResultIndSucc();
    NAS_EMM_SER_SndEsmBufMsg();

    /* ʶ����ҪDISABLE LTE�ĳ�������RRC����·�ͷ����� */
    /*NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable();*/

    return;

}


VOS_VOID NAS_EMM_TAU_TauAcpCollisionProc()
{

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO(               "NAS_EMM_TAU_TauAcpCollisionProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TauAcpCollisionProc_ENUM,LNAS_ENTRY);

    /*����ԭ��ֵ�����ô���*/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case    NAS_EMM_COLLISION_DETACH   :
                NAS_EMM_MmcSendTauActionResultIndSucc();

                /* �������DETACH��TAU��ϱ�ʶ */
                NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_NO);
                NAS_EMM_TAU_SendDetachReq();
                break;

        case    NAS_EMM_COLLISION_SERVICE    :

                NAS_EMM_TAU_TauAcpSerCollisionProc();
                break;

        default    :
                NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_TauAcpCollisionProc : NO Emm Collision.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TauAcpCollisionProc_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }
    NAS_EMM_TAU_SaveEmmCollisionCtrl(   NAS_EMM_COLLISION_NONE);

}
VOS_VOID NAS_EMM_TAU_TauAcpTaOnlySerCollisionProc
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp   = NAS_EMM_NULL_PTR;
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause = LMM_SMS_ERR_CAUSE_OTHERS;

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pMsgStru;

    /* ����SERVICE����ԭ��Ĳ�ͬ��������Ӧ���� */
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:

            /* ���ݲ�ͬ��ԭ��ֵ, ��SMS�ظ���ͬԭ��ֵ��ERR_IND */
            if ( NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pstTAUAcp->ucEMMCause)    /* #2 */
            {
                enErrCause = LMM_SMS_ERR_CAUSE_USIM_CS_INVALID;
            }
            else if (NAS_LMM_CAUSE_CS_NOT_AVAIL == pstTAUAcp->ucEMMCause)       /* #18 */
            {
                enErrCause = LMM_SMS_ERR_CAUSE_CS_SER_NOT_AVAILABLE;
            } /* #16#17#22 */
            else if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
            {
                /* 3402���� */
                enErrCause = LMM_SMS_ERR_CAUSE_T3402_RUNNING;
            }
            else   /* 3411���л�����ԭ�� */
            {
                enErrCause = LMM_SMS_ERR_CAUSE_OTHERS;
            }

            NAS_LMM_SndLmmSmsErrInd(enErrCause);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
            break ;

        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:

            if(NAS_EMM_CSFB_ABORT_FLAG_VALID != NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
            {
                /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
                NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
                /* ESR���̱�TAU���̴��,TAU ACP PS ONLY����ֱ�ӽ����绰,δ��ߺ�ͨ��,ԭ��ֵ��Ϊ2ʱ,��ҪȥGU�³��� */
                if(NAS_EMM_REJ_YES != NAS_LMM_GetEmmInfoRejCause2Flag())
                {
                    /*��MMC�ϱ�TAU��� */
                    NAS_EMM_MmcSendTauActionResultIndSucc();

                    /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ, ע�����ϱ�SERVICE���˳�򲻿ɵߵ� */
                    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
                    NAS_EMM_SER_SndEsmBufMsg();

                    /* ��diable LTE����ΪAPI����TAU CMP��Ϣ��ֱ���ͷż��� */
                    NAS_EMM_DisableLteCommonProc();
                    #if (FEATURE_ON == FEATURE_PTM)
                    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
                    {
                        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
                    }
                    else
                    {
                        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
                    }
                    #endif
                    return;
                }
                else
                {
                    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
                    /* ��ͨCSFB��֪ͨMM��ֹCSFB */
                    NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_PS_ONLY, NAS_LMM_CAUSE_NULL);
                }
            }
            break ;

        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

            /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

            /*��MMC�ϱ�TAU��� */
            NAS_EMM_MmcSendTauActionResultIndSucc();

            /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ, ע�����ϱ�SERVICE���˳�򲻿ɵߵ� */
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
            NAS_EMM_SER_SndEsmBufMsg();

            /* ��diable LTE����ΪAPI����TAU CMP��Ϣ��ֱ���ͷż��� */
            NAS_EMM_DisableLteCommonProc();
            return ;

        default:
            break ;
    }

    NAS_EMM_MmcSendTauActionResultIndSucc();

    NAS_EMM_SER_SndEsmBufMsg();
    return ;
}


VOS_VOID NAS_EMM_TAU_TauAcpTaOnlyCollisionProc
(
    VOS_VOID                           *pMsgStru
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TauAcpTaOnlyCollisionProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TauAcpTaOnlyCollisionProc_ENUM,LNAS_ENTRY);

    /*����ԭ��ֵ�����ô���*/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case    NAS_EMM_COLLISION_DETACH   :
                NAS_EMM_MmcSendTauActionResultIndSucc();

                /* �������DETACH��TAU��ϱ�ʶ */
                NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_NO);
                NAS_EMM_TAU_SendDetachReq();
                break;

        case    NAS_EMM_COLLISION_SERVICE    :
                NAS_EMM_TAU_TauAcpTaOnlySerCollisionProc(pMsgStru);
                break;

        default    :
                NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_TauAcpTaOnlyCollisionProc : NO Emm Collision.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TauAcpTaOnlyCollisionProc_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }
    NAS_EMM_TAU_SaveEmmCollisionCtrl(   NAS_EMM_COLLISION_NONE);

}
VOS_VOID  NAS_EMM_TAU_TauSuccProc
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp      = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo     = NAS_EMM_NULL_PTR;

    pstTAUAcp  = (NAS_EMM_CN_TAU_ACP_STRU*)pMsgStru;

    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /*����EU1 UPDATED,�����õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

    /* ����LastRegNetId */
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /* lihong00150010 emergency tau&service end */
    /*if new GUTI or TMSI, send TAU COMPLETE*/
    if((EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpGuti)
        || ((EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpMsId)
            && (NAS_EMM_MS_ID_TYPE_TMSI_PTMSI_MTMSI == NAS_EMM_TAU_GetMsIdentityType(pstTAUAcp->stMsId))))
    {
        NAS_EMM_TAU_SendMrrcDataReqTauCmpl();
        NAS_EMM_TAU_SaveEmmTauCompleteFlag(NAS_EMM_TAU_COMPLETE_VALID);
    }
    if(NAS_EMM_TAU_COMPLETE_INVALID == NAS_EMM_TAU_GetEmmTauCompleteFlag())
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        /*�������Ҫ����TAU CMP��Ϣ�������TAU���̱���*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif
        /* ������:����TAU�ɹ����� */
        NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);
        /* ������: �����ϵͳTAU��־���ñ�־����ϵͳTAUʱ���� */
        NAS_EMM_SetOmInterTauFlag(NAS_EMM_NO);
    }


/* lihong00150010 emergency tau&service begin */
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_SndEmcEsmMsg();
    }
    /* lihong00150010 emergency tau&service end */

    /*leili modify for isr begin*/
    NAS_EMM_TAU_SetISRAct(pstTAUAcp->ucEPSupdataRst);
    /*leili modify for isr end*/

    /*��� EPS ���������ı����־*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_NOCHANGE);

    /* �������TAU��ԭ��ֵ */
    NAS_EMM_TAU_SaveEmmTAUStartCause(   NAS_EMM_TAU_START_CAUSE_DEFAULT);

    /*���UEָ����DRX���ڱ仯������UEָ���� Drx_Cycle��RRC*/

    if(NAS_EMM_DRX_CYCLE_LEN_CHANGED == NAS_EMM_GetDrxCycleLenChangeFlag())
    {
        NAS_EMM_SendUeSpecDrxCycleLenToRrc();
        NAS_EMM_SetDrxCycleLenChangeFlag(NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED);
    }
    NAS_EMM_UpdateLteContainDrxFlag();
    NAS_EMM_TAU_SaveEmmTauContainDrxFlag(NAS_EMM_NO);

    /* TAU�ɹ��������FIRST TAU FLAG���´η���TAUʱ����Я��
       radio capability information update needed IE */
    NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_NOT_FIRST_TAU);

    /* TAU�ɹ��������LAU��������RAU��ʶ */
    NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED);
    NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_NOT_HAPPENED);
    NAS_LMM_SetEmmInfoT3412ExpCtrl(    NAS_EMM_T3412_EXP_NO);
    NAS_LMM_SetEmmInfoDrxNetCapChange(  NAS_EMM_NO);
    NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_NOCHANGE);
    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);

    NAS_LMM_SetEmmInfoGConnState(GMM_LMM_GPRS_MM_STATE_IDLE);
    NAS_LMM_SetEmmInfoUConnState(GMM_LMM_PACKET_MM_STATE_PMM_IDLE);



    /* ���VOICE DOMAIN�����仯�ı�ʶ */
    NAS_EMM_SetVoiceDomainChange(NAS_EMM_NO);
    NAS_LMM_SetEmmInfoLaiChangeFlag(VOS_FALSE);
    NAS_LMM_SetEmmInfoCsEmcConneExitFlag(VOS_FALSE);

    /*TAU�ɹ��󣬱�����ϵͳ�任�ɹ������������ԭ���¼*/
     NAS_EMM_ClearResumeInfo();

     /* ���UE���������仯��¼��ʶ */
    NAS_EMM_ClearUeRadioAccCapChgFlag();

}


VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal2
(
    VOS_VOID                           *pstRcvMsg
)
{
    /*���TRACKING AREA UPDATING ATTEMPT������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /* ��¼UE��ԭ��ֵ2�ܾ�����֮���ٷ�������ATTACH������TAU��ֱ���ػ����߰ο� */
    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

    /* TAU�ɹ��Ĵ��� */
    NAS_EMM_TAU_TauSuccProc(pstRcvMsg);

    /*TAU��IDLE̬�´������Ҳ�Я��'ACTIVE'��־��������T3440���ͷ�����*/
    if((NAS_EMM_TAU_NO_BEARER_EST_REQ == NAS_EMM_TAU_GetEmmTauReqActiveCtrl())
       &&(NAS_EMM_CONN_DATA != NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        /*����TAU�ͷ�ԭ��*/
        NAS_EMM_SetNormalServiceRelCause(NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_2);
        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*�޸�״̬��������״̬REG��״̬REG_NORMAL_SERVICE*/
        /*NAS_EMM_AdStateConvert( EMM_MS_REG,
                                EMM_SS_REG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        NAS_EMM_MmcSendTauActionResultIndSucc();

        NAS_EMM_WaitNetworkRelInd();
    }
    else
    {
        NAS_EMM_TAU_ClearActiveFlagProc();

        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*ת��EMM״̬��MS_REG+SS_NORMAL_SERVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        if(NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
        {
            /*�ж����̳�ͻ��־λ����������Ӧ����*/
            NAS_EMM_TAU_TauAcpTaOnlyCollisionProc(pstRcvMsg);
        }
        else
        {
            NAS_EMM_MmcSendTauActionResultIndSucc();
        }
    }
}


VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal18
(
    VOS_VOID                           *pstRcvMsg
)
{
   /* NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp   = NAS_EMM_NULL_PTR;

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;*/

    /*���TRACKING AREA UPDATING ATTEMPT������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*�ѵ�ǰPLMN���뵽�ܾ�#18�б���*/
    NAS_EMMC_AddPlmnInRej18PlmnList(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /*���þܾ�18��ʶ*/
    NAS_EMMC_SetRejCause18Flag(NAS_EMM_REJ_YES);

    /* TAU�ɹ��Ĵ��� */
    NAS_EMM_TAU_TauSuccProc(pstRcvMsg);

    /*TAU��IDLE̬�´������Ҳ�Я��'ACTIVE'��־��������T3440���ͷ�����*/
    if((NAS_EMM_TAU_NO_BEARER_EST_REQ == NAS_EMM_TAU_GetEmmTauReqActiveCtrl())
       &&(NAS_EMM_CONN_DATA != NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        /*����TAU�ͷ�ԭ��*/
        NAS_EMM_SetNormalServiceRelCause(NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_18);
        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*�޸�״̬��������״̬REG��״̬REG_NORMAL_SERVICE*/
        /*NAS_EMM_AdStateConvert( EMM_MS_REG,
                                EMM_SS_REG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        NAS_EMM_MmcSendTauActionResultIndSucc();

        NAS_EMM_WaitNetworkRelInd();
    }
    else
    {
        NAS_EMM_TAU_ClearActiveFlagProc();

        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*ת��EMM״̬��MS_REG+SS_NORMAL_SERVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        if(NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
        {
            /*�ж����̳�ͻ��־λ����������Ӧ����*/
            NAS_EMM_TAU_TauAcpTaOnlyCollisionProc(pstRcvMsg);
        }
        else
        {
            NAS_EMM_MmcSendTauActionResultIndSucc();

            /* ʶ��ԭ��ֵ18 disable Lģ�ĳ���,�ͷ���· */
            /*NAS_EMM_RecogAndProc18Disable(pstTAUAcp->ucEMMCause);*/
        }
    }
}


VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal1617
(
    VOS_VOID                           *pstRcvMsg
)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, begin */
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;
    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, end */

    /*TAU ATTEMPT COUNT ++*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

    /* TAU�ɹ��Ĵ��� */
    NAS_EMM_TAU_TauSuccProc(pstRcvMsg);

    /*TAU��IDLE̬�´������Ҳ�Я��'ACTIVE'��־��������T3440���ͷ�����*/
    if((NAS_EMM_TAU_NO_BEARER_EST_REQ == NAS_EMM_TAU_GetEmmTauReqActiveCtrl())
       &&(NAS_EMM_CONN_DATA != NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        /*����TAU�ͷ�ԭ��*/
        NAS_EMM_SetNormalServiceRelCause(NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722);
        NAS_EMM_TAU_ProcCause161722TauAttemptCont();

        NAS_EMM_WaitNetworkRelInd();

        return ;
    }

    NAS_EMM_TAU_ClearActiveFlagProc();

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {/* lihong00150010 emergency tau&service end */
        /*������ʱ��TI_NAS_EMM_PTL_T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /* lihong00150010 emergency delete */
        /*�޸�״̬��������״̬REG��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, begin */
        if (NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode)
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE);
        }
        else if (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode)
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, end */
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);
        }
        else
        {
        }

        /*�޸�״̬��������״̬REG��״̬EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                    TI_NAS_EMM_PTL_T3402);
    }

    if(NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*�ж����̳�ͻ��־λ����������Ӧ����*/
        NAS_EMM_TAU_TauAcpTaOnlyCollisionProc(pstRcvMsg);
    }
    else
    {
        NAS_EMM_MmcSendTauActionResultIndSucc();

        /* ʶ��ԭ��ֵ16,17,22 disable Lģ�ĳ���,�ͷ���· */
        /*NAS_EMM_RecogAndProc161722Disable(pstTAUAcp->ucEMMCause);*/
    }
}
VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal22
(
    VOS_VOID                           *pstRcvMsg
)
{
    /*TAU ATTEMPT COUNT ++*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt() = NAS_EMM_TAU_ATTEMPT_CNT_MAX;

    /* TAU�ɹ��Ĵ��� */
    NAS_EMM_TAU_TauSuccProc(pstRcvMsg);

    /*TAU��IDLE̬�´������Ҳ�Я��'ACTIVE'��־��������T3440���ͷ�����*/
    if((NAS_EMM_TAU_NO_BEARER_EST_REQ == NAS_EMM_TAU_GetEmmTauReqActiveCtrl())
       &&(NAS_EMM_CONN_DATA != NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        /*����TAU�ͷ�ԭ��*/
        NAS_EMM_SetNormalServiceRelCause(NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722);
        NAS_EMM_TAU_ProcCause22TauAttemptContR11();

        NAS_EMM_WaitNetworkRelInd();

        return ;
    }

    /*clear 'active' flag */
    NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);
    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /*������ʱ��TI_NAS_EMM_T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

        /* lihong00150010 emergency delete */
            /*�޸�״̬��������״̬REG��״̬EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
            NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_PTL_T3402);
    }

    if(NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*�ж����̳�ͻ��־λ����������Ӧ����*/
        NAS_EMM_TAU_TauAcpTaOnlyCollisionProc(pstRcvMsg);
    }
    else
    {
        NAS_EMM_MmcSendTauActionResultIndSucc();

    }
}




VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlyWithCause
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp   = NAS_EMM_NULL_PTR;

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;

    switch (pstTAUAcp->ucEMMCause)
    {
        case    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
                NAS_EMM_TAU_ProcTauAcpCauseVal2(pstRcvMsg);


                break;

        case    NAS_LMM_CAUSE_CS_NOT_AVAIL:
                NAS_EMM_TAU_ProcTauAcpCauseVal18(pstRcvMsg);

                break;
        case    NAS_LMM_CAUSE_PROCEDURE_CONGESTION:
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_TAU_ProcTauAcpCauseVal22(pstRcvMsg);
                }
                else
                {
                    NAS_EMM_TAU_ProcTauAcpCauseVal1617(pstRcvMsg);
                }
                break;
        default:
                NAS_EMM_TAU_ProcTauAcpCauseVal1617(pstRcvMsg);

                break;

    }
    return;
}


VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlyNoCause( VOS_VOID *pstRcvMsg )
{
    NAS_EMM_TAU_ProcTauAcpCauseVal1617(pstRcvMsg);

}


VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlySucc
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp   = NAS_EMM_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcTaUpdatedOnlySucc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcTaUpdatedOnlySucc_ENUM,LNAS_ENTRY);

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU *)pstRcvMsg;

    if (NAS_EMM_BIT_SLCT == pstTAUAcp->ucBitOpEmmCau)
    {
        NAS_EMM_TAU_LOG1_NORM("NAS_EMM_ProcTaUpdatedOnlySucc EmmCause:",pstTAUAcp->ucEMMCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_ProcTaUpdatedOnlySucc_ENUM,LNAS_CAUSE_NUMBER,
                                        pstTAUAcp->ucEMMCause);
        NAS_EMM_TAU_ProcTaUpdatedOnlyWithCause(pstRcvMsg);
    }
    else
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_ProcTaUpdatedOnlySucc No EmmCause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcTaUpdatedOnlySucc_ENUM,LNAS_NO_CAUSE);
        NAS_EMM_TAU_ProcTaUpdatedOnlyNoCause(pstRcvMsg);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_IsCombinedTauTaUpdatedOnly
 Description     : �ж��Ƿ�Ϊ����TAU�����ֵΪTA UPDATE ONLY�ĳ���
 Input           : enEmmTauType-------------------TAU ����
                   enEpsUpdateRslt----------------TAU���ֵ
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_TAU_IsCombinedTauTaUpdatedOnly
(
    MMC_LMM_TAU_TYPE_ENUM_UINT32            enEmmTauType,
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8       enEpsUpdateRslt
)
{
    /* �ж��Ƿ�Ϊ����TAU */
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != enEmmTauType)
         && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != enEmmTauType))
    {
        return  NAS_EMM_NO;
    }

    /* �жϽ��ֵ�Ƿ�ΪTA UPDATE ONLY */
    if ((NAS_EMM_EPS_UPDATE_RST_TA_UPDATED != enEpsUpdateRslt)
        && (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR != enEpsUpdateRslt))
    {
        return  NAS_EMM_NO;
    }

    return  NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SaveTauAcpIe
 Description     : �洢TAU ACCPET��Я������Ԫ
 Input           : pMsgStru------------TAU ACCEPT��Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-08-23  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SaveTauAcpIe
(
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulTimerLen  = NAS_EMM_NULL;
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp   = NAS_EMM_NULL_PTR;
    NAS_EMM_TA_LIST_STRU               *pstTALIST   = NAS_EMM_NULL_PTR;

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU*)pMsgStru;

    NAS_EMM_TAU_SaveEpsUpdateRslt(pstTAUAcp->ucEPSupdataRst);

    /*����ȫ�ֱ����е�GUTI*/
    NAS_EMM_TauUpdateGutiFromCnMsg(pstTAUAcp);

    if(EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpEPSstatus)
    {
        /*��ESM������ϢMM_ESM_BEARER_STATUS_IND*/
        NAS_EMM_TAU_SendEsmBearerStatusInd(pstTAUAcp);
    }

    if(EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpTaiList)
    {
        pstTALIST = (NAS_EMM_TA_LIST_STRU*)  &(pstTAUAcp->stTaiList);

        NAS_EMM_TAUSER_TaiListSet(pstTALIST);

        /*�����µ�TAI List��ͬʱ����ForbTA for Roaming��ForbTA for RPOS*/
        NAS_EMMC_UpdateForbTaList();
    }

    /*����T3412��ʱ������*/
    if(EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpT3412)
    {
        ulTimerLen = NAS_EMM_TimerValTransfer(pstTAUAcp->stT3412.ucUnit,
                                              pstTAUAcp->stT3412.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3412,ulTimerLen);
    }

    /*����Location area identification*/
    NAS_EMM_TAU_SetLai(pMsgStru);

    /*����MS identity*/
    NAS_EMM_TAU_SetMsId(pMsgStru);

    /*����EMM cause*/
    NAS_EMM_TAU_SetCnCause(pMsgStru);

    /*����T3402��ʱ������*/
    if(EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpT3402)
    {
         ulTimerLen = NAS_EMM_TimerValTransfer(pstTAUAcp->stT3402.ucUnit,
                                              pstTAUAcp->stT3402.ucTimerVal);
         NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,ulTimerLen);
    }
    else
    {
        /*���TAU ACP��Ϣ�в�Я��T3402��Ԫ����ָ�Ĭ��ֵ12min*/
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
        ulTimerLen = NAS_LMM_TIMER_T3402_LEN;
    }

    /* AT&T��������3402ʱ�������֪ͨMMC */
    if(ulTimerLen != NAS_EMM_GetEmmInfoDamParaT3402Len())
    {
        NAS_EMM_GetEmmInfoDamParaT3402Len() = ulTimerLen;
        NAS_EMM_SendMMCT3402LenNotify(ulTimerLen);
    }

    /*leili modify for isr begin*/
    /*����T3402��ʱ������*/
    if(EMM_TAU_AD_BIT_SLCT == pstTAUAcp->ucBitOpT3423)
    {
         ulTimerLen = NAS_EMM_TimerValTransfer(pstTAUAcp->stT3423.ucUnit,
                                              pstTAUAcp->stT3423.ucTimerVal);
         NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);
    }
    else
    {
        /*���ATTACH ACP��Ϣ�в�Я��T3423��Ԫ����ָ�Ĭ��ֵΪT3412ʱ��*/
        NAS_LMM_GetPtlTimerLen(TI_NAS_EMM_PTL_T3412, &ulTimerLen);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);
    }
    /*leili modify for isr end*/
    /*����Equivalent PLMNs*/
    NAS_EMM_TAU_SetEplmnList(pMsgStru);

    /*TAU ACPЯ��Emergency number list,����Emergency number list��ȫ�ֱ�����*/
    NAS_EMM_SetEmergencyList(   pstTAUAcp->ucBitOpEmergencyList,
                                &(pstTAUAcp->stEmergencyNumList));

    /*TAU ACPЯ��EPS network feature support,����EPS network feature support��ȫ�ֱ�����*/
    NAS_EMM_SetEpsNetFeature(   pstTAUAcp->ucBitOpEpsNetFeature,
                                pstTAUAcp->ucEpsNetFeature);

    /*TAU ACPЯ��Additional update result,����Additional update result��ȫ�ֱ�����*/
    if(NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype())
    {
        /* ������TAU,��TAU ACPЯ��Additional update result,�����Additional update result��ȫ�ֱ�����*/
        if(NAS_EMM_BIT_SLCT == pstTAUAcp->ucBitOpAdditionalUpRslt)
        {
            NAS_EMM_SetAddUpdateRslt(   pstTAUAcp->ucBitOpAdditionalUpRslt,
                                        pstTAUAcp->ulAdditionUpRslt);
        }
    }
    else
    {
        if ((NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED != pstTAUAcp->ucEPSupdataRst)
            && (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR != pstTAUAcp->ucEPSupdataRst))
        {
            /* ��������TAU ACPΪTA UPDAE ONLY ��ulAdditionUpRslt����ΪNAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED */
            NAS_EMM_SetAddUpdateRslt(NAS_EMM_BIT_SLCT, NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED);
        }
        else
        {
            /* ��������TAU ACPΪCOMBINED TA UPDAE �����Additional update result��ȫ�ֱ����� */
            NAS_EMM_SetAddUpdateRslt(   pstTAUAcp->ucBitOpAdditionalUpRslt,
                                        pstTAUAcp->ulAdditionUpRslt);
        }
    }

    /* lihong00150010 ims begin */
    /* ֪ͨMMC�����������б������Ƿ�֧��IMS VOICE�ͽ��������Լ�LTE��CS������ */
    /* NAS_EMM_SendGmmInfoChangeNotify(); */
    NAS_EMM_SendMmcInfoChangeNotify();
    /*NAS_EMM_SendMmInfoChangeNotify();*/
    /* lihong00150010 ims end */
/* add by lihong00150010 for lpp feature begin */
#if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SndLcsPosCapInfoInd();
#endif
/* add by lihong00150010 for lpp feature end */
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SetTauRegDomain
 Description     : �յ�TAU ACCPET��Ϣʱ����ע����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-08-23  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SetTauRegDomain
(
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8   enEPSupdataRst
)
{
    if((NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype())
        && ((NAS_EMM_EPS_UPDATE_RST_TA_UPDATED == enEPSupdataRst)
         || (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR == enEPSupdataRst)))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_TAU_SetTauRegDomain: periodic TAU not needed set regdomains:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SetTauRegDomain_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }
    if ((NAS_EMM_EPS_UPDATE_RST_TA_UPDATED == enEPSupdataRst)
     || (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR == enEPSupdataRst))
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
    }
}
/*leili modify for isr begin*/

VOS_UINT32  NAS_EMM_GetUeSuppISR(VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU               *pstPubInfo;
    NAS_EMM_MS_NET_CAP_STRU             *pstMsNetCap;
    VOS_UINT32                          ulRslt = NAS_EMM_BIT_NO_SLCT;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pstMsNetCap = NAS_LMM_GetEmmInfoMsNetCapAddr();
    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpMsNetCap)
    {
        if (NAS_EMM_BIT_SLCT == ((pstMsNetCap->aucMsNetCap[2] >> NAS_EMM_MOVEMENT_4_BITS)
                                    & NAS_EMM_LOW_1_BITS_F))
        {
            ulRslt = NAS_EMM_BIT_SLCT;
        }

    }

    return ulRslt;
}



VOS_UINT32 NAS_EMM_IsAnnexP5AConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    /*ĿǰGU��L����voice domain preference for E-UTRAN,���������ú��޸�*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP5AConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP5AConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    if ((NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetGUNwImsVoiceSupportFlg())
        &&(NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsAnnexP5AConditionSatisfied: B)condition is Satisfied");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP5AConditionSatisfied_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_UINT32 NAS_EMM_IsAnnexP5BConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP5BConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP5BConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    if ((NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED == NAS_LMM_GetGUNwImsVoiceSupportFlg())
        &&(NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsAnnexP5BConditionSatisfied: B)condition is Satisfied");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP5BConditionSatisfied_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}



VOS_UINT32  NAS_EMM_IsAnnexP5ConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /*C)����û��ʵ��*/
    if ((MMC_LMM_IMS_VOICE_CAP_AVAILABLE == pstPubInfo->enImsaVoiceCap)
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
        &&(VOS_TRUE == NAS_LMM_GetImsVoiceMMEnableFlg())
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        &&( (NAS_EMM_YES ==NAS_EMM_IsAnnexP5AConditionSatisfied())
            ||(NAS_EMM_YES == NAS_EMM_IsAnnexP5BConditionSatisfied())))
    {

        return NAS_EMM_YES;
    }


    return NAS_EMM_NO;
}
VOS_VOID  NAS_EMM_TAU_SetISRAct
(
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8   enEPSupdataRst
)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    /*UE��֧��ISR����*/
    if (NAS_EMM_BIT_NO_SLCT == NAS_EMM_GetUeSuppISR())
    {
        /*���� LMM_MMC_TIN_TYPE_IND*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        /*���³��ص�ISR��ʶ*/
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
        return;
    }

    if ((NAS_EMM_EPS_UPDATE_RST_TA_UPDATED == enEPSupdataRst) ||
        (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED == enEPSupdataRst))
    {
        /*���� LMM_MMC_TIN_TYPE_IND*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

        /*���³��ص�ISR��ʶ*/
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    }
    else
    {
        /*����annex P.5,����TINֵΪGUTI*/
        if ((NAS_LMM_RSM_SYS_CHNG_DIR_W2L == NAS_EMM_GetResumeDir())
            && (NAS_EMM_YES == NAS_EMM_IsAnnexP5ConditionSatisfied()))
        {
            /*���� LMM_MMC_TIN_TYPE_IND*/
            NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

            /*���³��ص�ISR��ʶ*/
            /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
            NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
            NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
            /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
            return;
        }
        /* �����VOICE DOMAIN�����仯��������TAU����ISR�������Ҫ��TINֵ����ΪGUTI */
        if (NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE == NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            /*���� LMM_MMC_TIN_TYPE_IND*/
            NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

            /*���³��ص�ISR��ʶ*/
            /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
            NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
            NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
            /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

            return;
        }

        if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
        {
            if (GMM_LMM_TIMER_EXP == NAS_EMM_GetEmmInfoT3312State())
            {
                 /*���� LMM_MMC_TIN_TYPE_IND*/
                NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

                /*���³��ص�ISR��ʶ*/
                /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
                NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
                NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
            }/*PC REPLAY MODIFY BY LEILI END*/
            else
            {
                /*���� LMM_MMC_TIN_TYPE_IND*/
                NAS_EMM_SetTinType(MMC_LMM_TIN_RAT_RELATED_TMSI);
            }
        }
    }
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_TAU_SetISRAct,UE SUPPORT ISR is end");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SetISRAct_ENUM,LNAS_END);

    return;
}
/*leili modify for isr end*/

VOS_VOID    NAS_EMM_TAU_RcvTAUAcp(VOS_VOID *pMsgStru)
{
    NAS_EMM_CN_TAU_ACP_STRU            *pstTAUAcp      = NAS_EMM_NULL_PTR;

    LRRC_LMM_SYS_INFO_IND_STRU          stRrcSysInfo = {0};
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo   = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_Tau_RcvTAUAcp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvTAUAcp_ENUM,LNAS_ENTRY);

    pstTAUAcp = (NAS_EMM_CN_TAU_ACP_STRU*)pMsgStru;

    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /*ֹͣT3430*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    /* �洢TAU ACCPET��Я������Ԫ */
    NAS_EMM_TAU_SaveTauAcpIe(pMsgStru);

    /* ���GUTI�е�PLMN�뵱ǰPLMN��ͬ������ǰPLMN���³�GUTI�еģ�ͬʱ��MMC��ϵͳ��Ϣ */
    if ( NAS_EMM_SUCC == NAS_EMM_UpdatePresentPlmnInfo() )
    {
        stRrcSysInfo.stSpecPlmnIdList.ulSuitPlmnNum                   = 1;
        stRrcSysInfo.stSpecPlmnIdList.astSuitPlmnList[0].aucPlmnId[0] = pMmNetInfo->stPresentNetId.stPlmnId.aucPlmnId[0];
        stRrcSysInfo.stSpecPlmnIdList.astSuitPlmnList[0].aucPlmnId[1] = pMmNetInfo->stPresentNetId.stPlmnId.aucPlmnId[1];
        stRrcSysInfo.stSpecPlmnIdList.astSuitPlmnList[0].aucPlmnId[2] = pMmNetInfo->stPresentNetId.stPlmnId.aucPlmnId[2];
        stRrcSysInfo.stTac.ucTac                                      = pMmNetInfo->stPresentNetId.stTac.ucTac;
        stRrcSysInfo.stTac.ucTacCont                                  = pMmNetInfo->stPresentNetId.stTac.ucTacCnt;
        stRrcSysInfo.ulCellId                                         = pMmNetInfo->stPresentNetId.ulCellId;
        stRrcSysInfo.enCellStatusInd                                  = LRRC_LNAS_CELL_STATUS_NORMAL;
        stRrcSysInfo.aulLteBand[0]                                    = pMmNetInfo->stPresentNetId.aulLteBand[0];
        stRrcSysInfo.aulLteBand[1]                                    = pMmNetInfo->stPresentNetId.aulLteBand[1];

        /*����LMM_MMC_SYS_INFO_IND��Ϣ*/
        NAS_EMMC_SendMmcSysInfo(&stRrcSysInfo);
    }


    NAS_EMM_TAU_SetTauRegDomain(pstTAUAcp->ucEPSupdataRst);

    /* ����AT&T��������: TAU�ɹ����CService���������۽����Σ�PS�����OK */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /*����TAU�Ľ��ֵΪTA UPDAE ONLY����*/
    if (NAS_EMM_YES == NAS_EMM_TAU_IsCombinedTauTaUpdatedOnly(  NAS_EMM_TAU_GetTAUtype(),
                                                                pstTAUAcp->ucEPSupdataRst))
    {
        NAS_EMM_TAU_ProcTaUpdatedOnlySucc(pMsgStru);
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_TAUErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_EPS_ONLY);
        #endif

        return ;
    }

    /*����TAU���Լ�����*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /* TAU�ɹ��Ĵ��� */
    NAS_EMM_TAU_TauSuccProc(pMsgStru);

    /*TAU��IDLE̬�´������Ҳ�Я��'ACTIVE'��־��������T3440���ͷ�����*/
    if((NAS_EMM_TAU_NO_BEARER_EST_REQ == NAS_EMM_TAU_GetEmmTauReqActiveCtrl())
       &&(NAS_EMM_CONN_DATA != NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        /*����TAU�ͷ�ԭ��*/
        NAS_EMM_SetNormalServiceRelCause(NAS_EMM_NORMALSERVICE_REL_CAUSE_NULL);
        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*�޸�״̬��������״̬REG��״̬REG_NORMAL_SERVICE*/
        /*NAS_EMM_AdStateConvert( EMM_MS_REG,
                                EMM_SS_REG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        NAS_EMM_MmcSendTauActionResultIndSucc();

        NAS_EMM_WaitNetworkRelInd();
    }
    else
    {
        NAS_EMM_TAU_ClearActiveFlagProc();

        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /*ת��EMM״̬��MS_REG+SS_NORMAL_SERVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        if(NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
        {
            /*�ж����̳�ͻ��־λ����������Ӧ����*/
            NAS_EMM_TAU_TauAcpCollisionProc();
        }
        else
        {
            /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
            NAS_EMM_MmcSendTauActionResultIndSucc();

            /* ʶ��SMS only����CS fallback not preferred disable Lģ�ĳ���,�ͷ���· */
            /*NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable();*/
        }
    }


    return;

}
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                                  ulRslt              = NAS_EMM_FAIL;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_NORM( "Nas_Emm_MsTauInitSsWaitCNCnfMsgTAUAcp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);

    NAS_EMM_ResetRejCauseChangedCounter();

    NAS_EMM_ResetHplmnAuthRejCout();

    /*ֹͣT3416��ɾ��RAND,RES*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*������Ϣ������*/
    NAS_EMM_TAU_RcvTAUAcp(pMsgStru);

    return NAS_LMM_MSG_HANDLED;

}



VOS_VOID  NAS_EMM_TAU_CollisionDetachProc( VOS_VOID )
{
    /* ��ӡ����ú���*/
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_CollisionDetachProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CollisionDetachProc_ENUM,LNAS_ENTRY);

    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_DETACH_REQ))
    {
        /**��APP ����APP DETACH CNF(SUCCESS)*******/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
    }

    /*�����ͻ��־*/
    NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);

    NAS_EMM_TAU_ClearActiveFlagProc();

    /* �������DETACH��TAU��ϱ�ʶ */
    NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_NO);

    /* �����ͻ��DETACH���Ͳ���IMSI DEACH������ֹͣ��ʱ����֪ͨESM����DETACHED̬ */
    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /* �رյ�ǰEMM�ĳ�Del Forb Ta Proid֮���״̬��ʱ��, Del Forb Ta Proidֻ���ڹػ�ʱֹͣ*/
        NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

        /*��ESM ����STATUS IND(DETACH)*/
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /*���TAU������*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt( NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    }

    return;
}


VOS_VOID  NAS_EMM_TAU_CollisionServiceProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara,
    VOS_UINT8                           ucRatChange
)
{
    /* ESR�����з���TAU����,TAUʧ�ܵ���CSFB����ʧ��,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
    if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
    }

    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:

            /* �ϱ�TAU��� */
            NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);

            /* ֪ͨRABM ���SERVICE ʧ�� */
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
            break ;

        #if (FEATURE_LPP == FEATURE_ON)
        case NAS_EMM_SER_START_CAUSE_LPP_EST_REQ:

            NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);

            /* ֪ͨRABM ���SERVICE ʧ�� */
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
            break;

        case NAS_EMM_SER_START_CAUSE_SS_EST_REQ:
            NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                    NAS_EMM_SER_GetSsOrLppOpid());

            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);

            /* ֪ͨRABM ���SERVICE ʧ�� */
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
            break;
        #endif

        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
            if (NAS_EMM_TRANSFER_RAT_ALLOW == ucRatChange)
            {
                 /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MM����ֹ֮�� */
                NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
            }
            else
            {
                NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL, NAS_LMM_CAUSE_NULL);

                /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MM����ֹ֮�� */
                NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);
            }
            break;
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:

            /* NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_FAILURE);*/

            /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MM����ֹ֮�� */
            NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

            /* ��MMC�ϱ�SERVICEʧ�ܴ�������ȥGU */
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
            break ;

        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

            /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MMC��SER���֮ǰ*/
            NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

            /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

            break ;

        default:
            /* �ϱ�TAU��� */
            NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

            /* ֪ͨRABM ���SERVICE ʧ�� */
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
            break ;
    }

    /* �����ͻ��־ */
    NAS_EMM_TAU_SaveEmmCollisionCtrl( NAS_EMM_COLLISION_NONE);

    NAS_EMM_TAU_ClearActiveFlagProc();

    /**����������ݵı�־��������**************/
    NAS_EMM_SerClearEsmDataBuf();

    return;

}


VOS_VOID  NAS_EMM_TAU_RelIndCollisionProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara
)
{

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_RelIndCollisionProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RelIndCollisionProc_ENUM,LNAS_ENTRY);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case    NAS_EMM_COLLISION_DETACH:

                /* ��MMC��TAU��� */
                NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

                if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
                {

                    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
                    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                                EMM_SS_DEREG_NORMAL_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                    /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
                    NAS_EMM_TAU_CollisionDetachProc();

                    /*����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
                    NAS_LMM_DeregReleaseResource();
                }
                else
                {
                    /* �����IMSI DETACH���ͣ��򱾵�CS��ȥע�ᣬ��������TAU�������յ�RRC��·�ͷ� */

                    /* ����ע����ΪPS */
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

                    /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
                    NAS_EMM_TAU_CollisionDetachProc();

                    /* IMSI DETACH���ͷ���Դ */
                    NAS_LMM_ImsiDetachReleaseResource();
                }
                break;

        case    NAS_EMM_COLLISION_SERVICE:

                /* ��MMC��TAU����ڳ�ͻ�н��д��� */
                NAS_EMM_TAU_CollisionServiceProc(pfTauRslt,pvPara,NAS_EMM_TRANSFER_RAT_ALLOW);
                break;

        default :
                NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_RelIndCollisionProc : NO Emm Collision.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RelIndCollisionProc_ENUM,LNAS_FUNCTION_LABEL1);

                /* ��MMC��TAU��� */
                NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt,pvPara);

                break;
    }

    return;
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




