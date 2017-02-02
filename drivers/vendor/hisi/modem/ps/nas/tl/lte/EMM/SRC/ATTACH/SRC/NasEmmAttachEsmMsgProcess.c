




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasMmlLib.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHESMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHESMMSGPROC_C
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
/*����Ȧ���Ӷ�*/
EMM_ESM_DATA_CNF_MAP_STRU  g_astEmmEsmDataCnfTbl[] =
{
    {LRRC_LMM_SEND_RSLT_SUCCESS,                EMM_ESM_SEND_RSLT_SUCCESS},
    {LRRC_LMM_SEND_RSLT_FAILURE_HO,             EMM_ESM_SEND_RSLT_FAILURE_HO},
    {LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL,       EMM_ESM_SEND_RSLT_FAILURE_CONN_REL},
    {LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,  EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN},
    {LRRC_LMM_SEND_RSLT_FAILURE_TXN,            EMM_ESM_SEND_RSLT_FAILURE_TXN},
    {LRRC_LMM_SEND_RSLT_FAILURE_RLF,            EMM_ESM_SEND_RSLT_FAILURE_RLF},
    {LRRC_LMM_SEND_RSLT_NO_RF,                  EMM_ESM_SEND_RSLT_NORF}
};
VOS_UINT32        g_ulEmmEsmDataCnfTblLen = sizeof(g_astEmmEsmDataCnfTbl)
                                               / sizeof(EMM_ESM_DATA_CNF_MAP_STRU);

/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_UINT32  NAS_EMM_EsmPdnRspMsgChk( const EMM_ESM_PDN_CON_RSP_STRU *pMsgpMsg)
{
    /*��Ϣ���ݼ��*/
    if ((EMM_ESM_PDN_CON_RSLT_SUCC == pMsgpMsg->ulRst) ||
         (EMM_ESM_PDN_CON_RSLT_FAIL == pMsgpMsg->ulRst))
    {
        return  NAS_EMM_PARA_VALID;

    }
    else
    {
        return  NAS_EMM_PARA_INVALID;

    }

}
/*lint -e960*/
/*lint -e961*/
VOS_VOID *NAS_EMM_AttRsltCommProc(VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pstMmcAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AttRsltCommProc:����LMM_MMC_ATTACH_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AttRsltCommProc_ENUM,LNAS_BEGIN);

    /*������Ϣ�ڴ�*/
    pstMmcAttMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_IND_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if ((NAS_EMM_NULL_PTR == pstMmcAttMsg))
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AttRsltCommProc: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttRsltCommProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_NULL_PTR;

    }

    NAS_LMM_MEM_SET(pstMmcAttMsg,0,sizeof(LMM_MMC_ATTACH_IND_STRU));

    /*����LMM_MMC_ATTACH_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pstMmcAttMsg,
                                        sizeof(LMM_MMC_ATTACH_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/

    pstMmcAttMsg->ulMsgId       = ID_LMM_MMC_ATTACH_IND;

    /*�����Ϣ����----OPID*/
    pstMmcAttMsg->ulOpId        = NAS_EMM_OPID_TYPE_ATTACH_IND;

    /* �ϱ�ATTACH INDʱȡ��ǰע��״̬ȫ�ֱ����ϱ���MMC��Ȼ����� */
    pstMmcAttMsg->enClAttRegStatus = NAS_EMM_GLO_AD_GetAttClRegStatus();

    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND);

    return pstMmcAttMsg;

}
/* ɾ�����˵��ú���NAS_EMM_AppSendAttInd */

VOS_VOID    NAS_EMM_MmcSendAttCnf
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32                ulAttRslt
)
{
    LMM_MMC_ATTACH_CNF_STRU            *pstAttCnf;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MmcSendAttCnf:�ظ�LMM_MMC_ATTACH_CNF!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendAttCnf_ENUM,LNAS_BEGIN);

    /*������Ϣ�ڴ�*/
    pstAttCnf = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if ((NAS_EMM_NULL_PTR == pstAttCnf))
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MmcSendAttCnf: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendAttCnf_ENUM,LNAS_NULL_PTR);
        return ;

    }

    NAS_LMM_MEM_SET(pstAttCnf,0,sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*��Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pstAttCnf,
                                        sizeof(LMM_MMC_ATTACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* �����Ϣ */

    pstAttCnf->ulMsgId       = ID_LMM_MMC_ATTACH_CNF;

    /*�����Ϣ����----OPID*/
    pstAttCnf->ulOpId        = NAS_EMM_GetAppMsgOpId();

    pstAttCnf->ulAttachRslt  = ulAttRslt;
    pstAttCnf->ulReqType     = NAS_EMM_GLO_GetAttReqType();

    NAS_LMM_SendLmmMmcMsg(pstAttCnf);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*���APP_ATTACH_REQ��Ϣ*/
    NAS_EMM_ClearAppMsgPara();
}

VOS_VOID    NAS_EMM_AppSendAttSucc( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pstMmcAttMsg = NAS_EMM_NULL_PTR;

     NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:ENTER!");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
    }

    /* ���� LMM_MMC_ATTACH_IND */
    pstMmcAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstMmcAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttSucc_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    pstMmcAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_SUCCESS;

    /*�����Ϣ����----ATTACH��������*/
    pstMmcAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*�����Ϣ����----����������*/
    pstMmcAttMsg->bitOpCnRslt       = NAS_EMM_BIT_SLCT;

    if (EMM_ATTACH_RSLT_EPS_ONLY == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pstMmcAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;
    }
    else if (EMM_ATTACH_RSLT_COMBINED_ATTACH == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pstMmcAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttSucc:CN RSLT is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttSucc_ENUM,LNAS_ACT_RESULT);
    }

    /*�����Ϣ����----EPLMN*/
    pstMmcAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttSucc:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY(                &pstMmcAttMsg->stEplmnList,
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*�����Ϣ����----LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_LAI_NUMBER);
        pstMmcAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                 &pstMmcAttMsg->stLai,
                                        NAS_EMM_GLO_AD_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    /*�����Ϣ����----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_TMSI_NUMBER);
        pstMmcAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                 pstMmcAttMsg->stMsIdentity.aucMsIdentity,
                                        NAS_EMM_GLO_AD_GetMsIdAddr(),
                                        NAS_MAX_SIZE_MS_IDENTITY);

    }
    /*�����Ϣ����----EMM CAUSE*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetEmmCau())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_CAUSE_NUMBER);
        pstMmcAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
        pstMmcAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetEmmCau();
    }

    /* xiongxianghui00253310 modify 2014-01-13 begin */
    /*
    if ((NAS_LMM_CAUSE_MSC_UNREACHABLE == NAS_EMM_GLO_AD_GetEmmCau())
        || (NAS_LMM_CAUSE_NETWORK_FAILURE == NAS_EMM_GLO_AD_GetEmmCau())
        || (NAS_LMM_CAUSE_PROCEDURE_CONGESTION == NAS_EMM_GLO_AD_GetEmmCau()))
    */
    if (0 != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    /* xiongxianghui00253310 modify 2014-01-13 end */
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:tau attempt couter");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_ATTEMPT_COUNTER);
        pstMmcAttMsg->bitOpAtmpCnt      = NAS_EMM_BIT_SLCT;
        pstMmcAttMsg->ulAttemptCount    = NAS_EMM_TAU_GetEmmTAUAttemptCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pstMmcAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}


VOS_VOID NAS_EMM_AppSendAttRejEpsOnly( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_CN_REJ);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRejEpsOnly:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_CN_REJ;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*�����Ϣ����----����������*/
    pEmmAppAttMsg->bitOpCnRslt  = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ulCnRslt     = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;

    /* ֻ��#2#16#17#18#22ʱ��ԭ��ֵ������ԭ��ֵ������ԭ��ֵ��������� */
    pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_NO_SLCT;
    pEmmAppAttMsg->ucCnCause         = NAS_EMM_CAUSE_BUTT;

    /*�����Ϣ����----EPLMN*/
    pEmmAppAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRejEpsOnly:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY(                &pEmmAppAttMsg->stEplmnList,
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*�����Ϣ����----LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRejEpsOnly:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_LAI_NUMBER);
        pEmmAppAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                 &pEmmAppAttMsg->stLai,
                                        NAS_EMM_GLO_AD_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }

    /*�����Ϣ����----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRejEpsOnly:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_TMSI_NUMBER);
        pEmmAppAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                pEmmAppAttMsg->stMsIdentity.aucMsIdentity,
                                        NAS_EMM_GLO_AD_GetMsIdAddr(),
                                        NAS_MAX_SIZE_MS_IDENTITY);

    }

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);

    return;
}
VOS_VOID    NAS_EMM_AppSendAttRej( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRej:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRej_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_CN_REJ);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRej:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRej_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_CN_REJ;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*�����Ϣ����----����ܾ�ԭ��*/
    pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetAttRejCau();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}
VOS_VOID    NAS_EMM_AppSendAttTimerExp(VOS_VOID)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttTimerExp:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttTimerExp_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_TIMER_EXP);
    }


    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttTimerExp:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttTimerExp_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_TIMER_EXP;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*�����Ϣ����----ATTACH���Դ���*/
    pEmmAppAttMsg->bitOpAtmpCnt      = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ulAttemptCount    = NAS_EMM_GLO_AD_GetAttAtmpCnt();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}
VOS_VOID NAS_EMM_AppSendAttFailWithPara( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithPara:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithPara_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttFailWithPara:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttFailWithPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt         = MMC_LMM_ATT_RSLT_FAILURE;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}



VOS_VOID    NAS_EMM_AppSendAttOtherType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttOtherType:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(ulAttRslt);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttOtherType:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    if ((MMC_LMM_ATT_RSLT_ACCESS_BAR == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_AUTH_REJ == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_ESM_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_T3402_RUNNING == ulAttRslt))
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttOtherType:ulAttRslt =",
                                ulAttRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ACT_RESULT,
                                ulAttRslt);

        pEmmAppAttMsg->ulAttachRslt  = ulAttRslt;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttOtherType:ulAttRslt is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ERROR);
    }

    /*�����Ϣ����----ATTACH��������*/
    /*NAS_EMM_SetAttType();*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}
VOS_VOID    NAS_EMM_AppSendAttRstDefaultReqType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRstDefaultReqType:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(ulAttRslt);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRstDefaultReqType:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ����----ATTACH���*/
    if ((MMC_LMM_ATT_RSLT_ACCESS_BAR == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_AUTH_REJ == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_SUCCESS == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_ESM_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_T3402_RUNNING == ulAttRslt))
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRstDefaultReqType:ulAttRslt =",
                                ulAttRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ACT_RESULT,
                                ulAttRslt);

        pEmmAppAttMsg->ulAttachRslt  = ulAttRslt;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttOtherType:ulAttRslt is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ERROR);
    }

    /*�����Ϣ����----ATTACH��������*/
    NAS_EMM_SetAttType();

    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}



VOS_VOID    NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst)
{
    LMM_MMC_ATTACH_CNF_STRU             *pEmmAppAttMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRstInTau:�ظ�LMM_MMC_ATTACH_CNF!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRstInTau_ENUM,LNAS_BEGIN);

    /*������Ϣ�ڴ�*/
    pEmmAppAttMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if ((NAS_EMM_NULL_PTR == pEmmAppAttMsg))
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRstInTau: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRstInTau_ENUM,LNAS_NULL_PTR);
        return ;

    }

    NAS_LMM_MEM_SET(pEmmAppAttMsg,0,sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*��Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pEmmAppAttMsg,
                                        sizeof(LMM_MMC_ATTACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* �����Ϣ */

    pEmmAppAttMsg->ulMsgId              = ID_LMM_MMC_ATTACH_CNF;

    /*�����Ϣ����----OPID*/
    pEmmAppAttMsg->ulOpId               = NAS_EMM_GetAppMsgOpId();

    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt         = ulAttRst;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType            = NAS_EMM_GLO_GetAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_CNF������LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*���APP_ATTACH_REQ��Ϣ*/
    NAS_EMM_ClearAppMsgPara();
    return;
}

VOS_VOID NAS_EMM_AppSendAttFailWithAllPara( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;


    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_ENTRY);

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if ((NAS_EMM_NULL_PTR == pEmmAppAttMsg))
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttFailWithAllPara: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_NULL_PTR);
        return;

    }


    /*�����Ϣ����----ATTACH���*/
    pEmmAppAttMsg->ulAttachRslt         = MMC_LMM_ATT_RSLT_FAILURE;

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    /*�����Ϣ����----����������*/
    pEmmAppAttMsg->bitOpCnRslt       = NAS_EMM_BIT_SLCT;

    /* zhangcaixia for syscfg_attach begin */
    if (EMM_ATTACH_RSLT_EPS_ONLY == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pEmmAppAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;
    }
    else if (EMM_ATTACH_RSLT_COMBINED_ATTACH == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pEmmAppAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI;
    }

    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttFailWithAllPara:CN RSLT is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_ERROR);
    }

    /*�����Ϣ����----EPLMN*/
    pEmmAppAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttFailWithAllPara:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY(                &pEmmAppAttMsg->stEplmnList,
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*�����Ϣ����----LAI*/
    /* zhangcaixia for syscfg_attach begin */
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_LAI_NUMBER);
        pEmmAppAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                &pEmmAppAttMsg->stLai,
                                        NAS_EMM_GLO_AD_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }

    /*�����Ϣ����----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_TMSI_NUMBER);
        pEmmAppAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                pEmmAppAttMsg->stMsIdentity.aucMsIdentity,
                                        NAS_EMM_GLO_AD_GetMsIdAddr(),
                                        NAS_MAX_SIZE_MS_IDENTITY);
    }

    /*�����Ϣ����----EMM CAUSE*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetEmmCau())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_CAUSE_NUMBER);
        pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
        pEmmAppAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetEmmCau();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}
VOS_VOID    NAS_EMM_AppSendAttPsNotAllow(  VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttPsNotAllow:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttPsNotAllow_ENUM,LNAS_ENTRY);

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttPsNotAllow:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttPsNotAllow_ENUM,LNAS_NULL_PTR);
        return;
    }

    pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW;


    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = MMC_LMM_ATT_TYPE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*���MMC_LMM_ATTACH_REQ��Ϣ*/
    NAS_EMM_ClearAppMsgPara();
    return;
}

/* zhangcaixia for syscfg_attach end */

VOS_VOID  NAS_EMM_AppSendAttRsltForb
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRsltForb:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_ENTRY);


    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRsltForb:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRsltForb:ulForbInfo =",
                                  ulForbInfo);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_EMM_FORB_INFO,
                                  ulForbInfo);
    /*�����Ϣ����----ATTACH���*/
    if (EMMC_EMM_FORBIDDEN_PLMN == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_PLMN;
    }
    else if (EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_RPOS == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS;
    }
    else if (EMMC_EMM_NO_FORBIDDEN == ulForbInfo)
    {
        /* ���ϵͳ��Ϣδ�����ҵ��ô˺����ϱ�ATTACH�������һ����ANY CELL����� */
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FAILURE;
    }

    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttRsltForb:ulForbInfo is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_ERROR);
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FAILURE;
    }

    /*�����Ϣ����----ATTACH��������*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /* ���û���LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(pEmmAppAttMsg->ulAttachRslt);
    }

   #if (FEATURE_ON == FEATURE_DSDS)
   /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
   NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
   #endif

    /*��MMC����LMM_MMC_ATTACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* ������: ����attach Other Fail���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}
VOS_UINT32  NAS_EMM_CountMrrcDataReqLen(VOS_UINT32 ulNasCnMsgLen)
{
    VOS_UINT32                          ulMsgLen;
    ulMsgLen                            = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                          (ulNasCnMsgLen-NAS_EMM_LEN_VOS_MSG_HEADER))
                                          -NAS_EMM_4BYTES_LEN;

    return ulMsgLen;
}


VOS_VOID    NAS_EMM_CompCnAttachReqNasMsg(  VOS_UINT8      *pucAttReqCn,
                                            VOS_UINT32     *pulIndex)
{
    VOS_UINT32                          ulIndex     = NAS_LMM_NULL;
    VOS_UINT32                          ulIeLength = NAS_LMM_NULL;

    VOS_UINT8                           ucKsi;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompCnAttachReqNasMsg: is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompCnAttachReqNasMsg_ENUM,LNAS_ENTRY);

    ulIndex                             = *pulIndex;

    /* ��� Protocol Discriminator + Security header type */
    pucAttReqCn[ulIndex++]              = EMM_CN_MSG_PD_EMM;

    /* ��� Attach request message identity   */
    pucAttReqCn[ulIndex++]              = NAS_EMM_CN_MT_ATTACH_REQ;

    /*���Attach type + NKSI*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    NAS_EMM_SetAttType();
    NAS_EMM_ATTACH_LOG1_NORM("Attach Type: ", NAS_EMM_GLO_GetCnAttReqType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_CompCnAttachReqNasMsg_ENUM,LNAS_EMM_ATTACH_TYPE,
                                        NAS_EMM_GLO_GetCnAttReqType());
    pucAttReqCn[ulIndex++]              = ((VOS_UINT8)(NAS_EMM_GLO_GetCnAttReqType())|
                                           ((VOS_UINT8)(ucKsi << NAS_LMM_MOVEMENT_4_BITS)));

    /*���EPS mobile identity*/
    NAS_EMM_EncodeEpsMobileId(          &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* ���UE network capability �Ǳ�ѡIE, LV��3~14*/
    NAS_EMM_EncodeUeNetCapa(            &(pucAttReqCn[ulIndex]),
                                        NAS_LMM_IE_FORMAT_LV,
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���ESM message container*/
    NAS_EMM_EncodeEsmContainer(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Old P-TMSI signature*/
    NAS_EMM_EncodePtmsiSignature(       &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Additional GUTI*/
    NAS_EMM_EncodeAdditionalGuti(       &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Last visited registered TAI*/
    NAS_EMM_EncodeLRVTai(               &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���DRX parameter*/
    NAS_EMM_EncodeDrxPara(              &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*���MS network capability*/
    NAS_EMM_EncodeMsNetworkCapability( &(pucAttReqCn[ulIndex]),
                                       &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;


    /*���LAI*/
    NAS_EMM_EncodeLai(                  &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;


    /*���TMSI STATUS*/
    NAS_EMM_EncodeTmsiStatus(           &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*���Mobile station classmark 2*/
    NAS_EMM_EncodeMsClassMark2(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*���Mobile station classmark 3*/
    NAS_EMM_EncodeMsClassMark3(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Supported Codecs*/
    NAS_EMM_EncodeSupportedCodecs(      &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Additional update type*/
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_EncodeAdditionUpdateType(   &(pucAttReqCn[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    /*���Voice domain preference and UE's usage setting*/
    NAS_EMM_EncodeVoiceDomainAndUsageSetting(&(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    if (NAS_RELEASE_CTRL)
    {
        /* ���Old GUTI type */
        NAS_EMM_EncodeGutiType(             &(pucAttReqCn[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    if (NAS_RELEASE_R11)
    {

        /* ����ATTACH���ű������Ԫ */
        if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
        {
            /* ���TMSI based NRI container */
            NAS_EMM_EncodeTmsiBasedNriContainer(    &(pucAttReqCn[ulIndex]),
                                                    &ulIeLength);
            ulIndex                             += ulIeLength;
        }
    }

    *pulIndex = ulIndex;

}

VOS_VOID    NAS_EMM_CompCnAttachReq(NAS_EMM_MRRC_DATA_REQ_STRU *pAttReqMsg)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pTempAttReqMsg  =pAttReqMsg;
    VOS_UINT32                          ulIndex         = 0;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;

    if (NAS_EMM_NULL_PTR == pAttReqMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompCnAttachReq: Mem Alloc Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnAttachReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);

    /*����ATTACH REQ�տ���Ϣ*/
    NAS_EMM_CompCnAttachReqNasMsg(pTempAttReqMsg->stNasMsg.aucNasMsg, &ulIndex);

    /*�ڲ���Ϣ���ȼ���*/
    ulDataReqMsgLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_CompCnAttachReq, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnAttachReq_ENUM,LNAS_ERROR);
        return ;
    }

    /*���NAS��Ϣ����*/
    pTempAttReqMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pTempAttReqMsg, ulDataReqMsgLenNoHeader);

    /*�����ϢID*/
    pTempAttReqMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    /*�����Ϣ����*/
    if ((EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        || (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau()))
    {
        pTempAttReqMsg->enEstCaue           = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
        pTempAttReqMsg->enCallType          = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
    }
    else
    {
        pTempAttReqMsg->enEstCaue           = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
        pTempAttReqMsg->enCallType          = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    }
    pTempAttReqMsg->enEmmMsgType             = NAS_EMM_MSG_ATTACH_REQ;

    pTempAttReqMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

    return;
}


VOS_VOID    NAS_EMM_EncodeUeNetCapa(    VOS_UINT8                  *pMsg,
                                        NAS_LMM_IE_FORMAT_ENUM_UINT8 ucIeFormat,
                                        VOS_UINT32                 *pulIeLength)
{
    VOS_UINT8                          *pMsgPreAddr;
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength) ||
       (NAS_LMM_IE_FORMAT_ERR(ucIeFormat)))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeUeNetCapa ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeUeNetCapa_ENUM,LNAS_NULL_PTR);
        /*
        NAS_EMM_ATTACH_LOG2_ERR(        "NAS_EMM_EncodeUeNetCapa ERR !! pMsg = , pIeLength = ",
                                        pMsg,
                                        pulIeLength);
        */
        return;
    }

    /* ��IE������Ϣ�ĵ�ַ��ֵ����ʱ���� */
    pMsgPreAddr     = pMsg;

    /* ����Ĳ���IE���ȳ�ʼ��Ϊ0 */
    (*pulIeLength)  = NAS_EMM_NULL;

    /* ָ�� UeNetCap*/
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    switch(ucIeFormat)
    {
        case    NAS_LMM_IE_FORMAT_LV:
                (*pMsgPreAddr) = pstUeNetCap->ucUeNetCapLen;
                pMsgPreAddr ++;         /* ��ַ��1, ָ��V���׵�ַ */
                (*pulIeLength) += 1;    /* NAS_LMM_IE_FORMAT_LV�е�L,�������� 1*/

                /* ��BREAK������ʹ�������CASE���V����� */
                /*lint -fallthrough*/
                /*lint +fallthrough*/
        case    NAS_LMM_IE_FORMAT_V:
                /* coverity[ptr_arith] */
                NAS_LMM_MEM_CPY(        pMsgPreAddr,
                                        (&(pstUeNetCap->ucUeNetCapLen) + 1),
                                        (pstUeNetCap->ucUeNetCapLen));
                (*pulIeLength) += (pstUeNetCap->ucUeNetCapLen);
                break;


        default :
                NAS_EMM_ATTACH_LOG1_ERR("NAS_EMM_EncodeUeNetCapa ERR!! ucIeFormat =",
                                        ucIeFormat);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_EncodeUeNetCapa_ENUM,LNAS_IE_FORMAT,
                                        ucIeFormat);
                break;
    }

    return;
}
VOS_VOID  NAS_EMM_CompMappedGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_LMM_GUTI_STRU                    stMappedGuti;

    PS_MEM_SET(&stMappedGuti, 0, sizeof(NAS_LMM_GUTI_STRU));
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompMappedGuti is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompMappedGuti_ENUM,LNAS_ENTRY);

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompMappedGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompMappedGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*��ȡMapped*/
    NAS_EMM_DeriveMappedGuti(&stMappedGuti);

    /*���GUTI*/
    pucReqMsg[ulIndex++]                = NAS_EMM_AD_LEN_GUTI;
    pucReqMsg[ulIndex++]                = NAS_EMM_AD_ID_GUTI;
    NAS_LMM_MEM_CPY(                     &(pucReqMsg[ulIndex]),
                                        stMappedGuti.stPlmnId.aucPlmnId,
                                        NAS_EMM_AD_LEN_PLMN_ID);
    ulIndex                             += NAS_EMM_AD_LEN_PLMN_ID;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeGroupId.ucGroupId;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeGroupId.ucGroupIdCnt;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeCode.ucMmeCode;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsi;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt1;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt2;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt3;

    *pulIeLength                        = ulIndex;

    return;
}



VOS_VOID  NAS_EMM_CompNativeGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompNativeGuti is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompNativeGuti_ENUM,LNAS_ENTRY);

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompNativeGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompNativeGuti_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*���GUTI*/
    /*============ GUTI ============ begin */
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetLen();
    pucReqMsg[ulIndex++]                = (NAS_EMM_GLO_AD_GetOeToi()|
                                             NAS_EMM_HIGH_HALF_BYTE_F);

    NAS_LMM_MEM_CPY(                     &(pucReqMsg[ulIndex]),
                                        NAS_EMM_GLO_AD_GetGutiPlmn(),
                                        NAS_EMM_AD_LEN_PLMN_ID);
    ulIndex                             += NAS_EMM_AD_LEN_PLMN_ID;
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMmeGroupId();
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMMeGroupIdCnt();
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMMeCode();

    NAS_LMM_MEM_CPY(                     &(pucReqMsg[ulIndex]),
                                        NAS_EMM_GLO_AD_GetMTmsiAddr(),
                                        sizeof(NAS_EMM_MTMSI_STRU));
    ulIndex                             += sizeof(NAS_EMM_MTMSI_STRU);

    *pulIeLength                        = ulIndex;

    return;
}


VOS_VOID  NAS_EMM_CompImsi
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompImsi: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompImsi_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*���IMSI*/
    /*============ IMSI ============ begin */
    NAS_LMM_MEM_CPY(                     &(pucReqMsg[ulIndex]),
                                        NAS_EMM_GLO_AD_GetImsi(),
                                        NAS_EMM_AD_LEN_CN_MSG_IMSI);

    ulIndex                             += NAS_EMM_AD_LEN_CN_MSG_IMSI;
    *pulIeLength                        = ulIndex;
    /*============ IMSI ============ end */

    return;
}
VOS_VOID  NAS_EMM_CompImei
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*���IMEI*/
    /*============ IMEI ============ begin */
    NAS_LMM_MEM_CPY(                     &(pucReqMsg[ulIndex]),
                                        NAS_EMM_GLO_AD_GetImei(),
                                        NAS_EMM_AD_LEN_CN_MSG_IMEI);

    /* GU NV�д洢��IMEI��ATTACH REQ��EPS mobile identity�еĽṹ������ͬ��
       NV IMEI�е�type of identityΪ'010'����ATTACH REQ��Я����IMEI�е�
       type of identityΪ'011' */
    pucReqMsg[1]                        &= (~NAS_EMM_LOW_3_BITS_F);
    pucReqMsg[1]                        |= 0x03;

    ulIndex                             += NAS_EMM_AD_LEN_CN_MSG_IMEI;
    *pulIeLength                        = ulIndex;
    /*============ IMEI ============ end */

    return;
}
VOS_VOID  NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_CompMappedGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}


VOS_VOID  NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_CompNativeGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
        return;
    }

    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_CompMappedGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
        return;
    }

    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}


VOS_VOID  NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_CompNativeGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}


VOS_VOID  NAS_EMM_EncodeEpsMobileId
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    ulTinType = NAS_EMM_GetTinType();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */

    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId( &(pucReqMsg[ulIndex]),
                                                        &ulLen);
            *pulIeLength            = ulLen;
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId(  &(pucReqMsg[ulIndex]),
                                                                        &ulLen);
            *pulIeLength            = ulLen;
        }
        else if (MMC_LMM_TIN_INVALID == ulTinType)
        {
            NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId( &(pucReqMsg[ulIndex]),
                                                          &ulLen);
            *pulIeLength            = ulLen;
        }
        else
        {

        }
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeEpsMobileId:NOT SUPPOR MUTI MODE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeEpsMobileId: GUTI VALID!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);

            NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength                = ulLen;
        }
        else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
        {
            NAS_EMM_CompImsi(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength            = ulLen;
        }
        else
        {
            NAS_EMM_CompImei(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength            = ulLen;
        }
    }

    return;
}


VOS_VOID  NAS_EMM_EncodeEsmContainer
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT16                          usEsmMsgLen = NAS_EMM_NULL;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeEsmContainer: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeEsmContainer_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    usEsmMsgLen                         = (VOS_UINT16)NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen;
    pucReqMsg[ulIndex++]                = (usEsmMsgLen>>8)& 0xFF;

    pucReqMsg[ulIndex++]                = usEsmMsgLen & 0xFF;
    NAS_LMM_MEM_CPY(                    &(pucReqMsg[ulIndex]),
                                        (NAS_EMM_GLO_AD_GetEsmMsgAddr()->aucMsg),
                                        NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen);

    ulIndex                             += NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen;

    *pulIeLength                        = ulIndex;

    return;
}



VOS_VOID  NAS_EMM_EncodePtmsiSignature
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;
    /*Coverity �澯���� 2013-9-26 Begin */
    VOS_UINT32                          ulEmmRslt;
    VOS_UINT32                          ulTinType;
    /*Coverity �澯���� 2013-9-26 End */

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodePtmsiSignature: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*��ʼ��*/
    NAS_LMM_MEM_SET(&stGuInfo, 0, sizeof(NAS_GUMM_INFO_STRU));
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*�ж��Ƿ����LAI*/
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI_SIGNATURE,&stGuInfo);
    /*Coverity �澯���� 2013-9-26 Begin */
    ulEmmRslt = NAS_EMM_CheckMutiModeSupport();
    ulTinType = NAS_EMM_GetTinType();
    /* Я�� old P-TMSI signature IE������:
       (MultiMode) && (TIN = P-TMSI����INVALID)&&(P-TMSI,P-TMSI signature��RAI��Ч)
    */
    if (NAS_EMM_SUCC == ulEmmRslt)
    {
        if ((MMC_LMM_TIN_P_TMSI == ulTinType) ||
            (MMC_LMM_TIN_INVALID == ulTinType))
        {
            if ((MMC_LMM_SUCC == ulRslt)
            &&(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity()))
            {
                NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodePtmsiSignature:P-TMSI SIGNATURE VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_FUNCTION_LABEL1);

                /*���Old P-TMSI signature*/
                pucReqMsg[ulIndex++]    = NAS_EMM_AD_PTMSI_SIGNATURE_IEI;
                NAS_LMM_MEM_CPY(        &(pucReqMsg[ulIndex]),
                                        stGuInfo.u.stPtmsiSignature.aucPtmsiSign,
                                        NAS_MAX_SIZE_PTMSI_SIGNATURE);
                ulIndex                 += NAS_MAX_SIZE_PTMSI_SIGNATURE;
                *pulIeLength            = ulIndex;
            }
        }

    }
    /*PC REPLAY MODIFY BY LEILI END*/
    NAS_EMM_ATTACH_LOG2_INFO("NAS_EMM_EncodePtmsiSignature: NAS_EMM_CheckMutiModeSupport()= ,NAS_EMM_GetTinType() = ",
                            ulEmmRslt,
                            ulTinType);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_EMM_MLTI_MODE_TIN,ulEmmRslt,ulTinType);
    /*Coverity �澯���� 2013-9-26 End */
    return;
}



VOS_VOID  NAS_EMM_EncodeAdditionalGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeAdditionalGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeAdditionalGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

     /* Я��Additional GUTI������:
      (MultiMode) && (TIN = P-TMSI�� P-TMSI��RAI��Ч) &&(GUTI��Ч)
    */
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if ((MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
          &&(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity()))
        {
            if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
            {
                NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeAdditionalGuti: GUTI VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeAdditionalGuti_ENUM,LNAS_FUNCTION_LABEL1);
                pucReqMsg[ulIndex++]    = NAS_EMM_AD_ADDITION_GUTI_IEI;
                NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]), &ulLen);
                *pulIeLength            = ulLen + ulIndex;
            }
        }
    }
    return;
}


VOS_VOID  NAS_EMM_EncodeLRVTai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeLRVTai: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeLRVTai_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /*�ж��Ƿ�֧��Last visited registered TAI��TAC��Ϊ0XFFFE*/
    if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GetLVRTaiOpBit()) &&
        (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(NAS_LMM_GetEmmInfoLastRegPlmnAddr())) &&
        (VOS_FALSE == NAS_LMM_TacIsInvalid(NAS_LMM_GetEmmInfoLastRegTacAddr())))
    {
        /*���Last visited registered TAI*/
        pucReqMsg[ulIndex++]            = NAS_EMM_AD_TAI_IEI;
        NAS_LMM_MEM_CPY(                &(pucReqMsg[ulIndex]),
                                        NAS_EMM_GLO_AD_GetLastRegPlmnId(),
                                        NAS_EMM_AD_LEN_PLMN_ID);
        ulIndex                         += NAS_EMM_AD_LEN_PLMN_ID;
        pucReqMsg[ulIndex++]            = NAS_EMM_GLO_AD_GetLastRegTac();
        pucReqMsg[ulIndex++]            = NAS_EMM_GLO_AD_GetLastRegTacCnt();

        *pulIeLength                    = ulIndex;

    }
    return;
}


VOS_VOID  NAS_EMM_EncodeDrxPara
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT8                           ucDrxByte;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeDrxPara: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeDrxPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*��GU->L,��GUģЯ��DRX����ʱ��Lģ��Я��*/
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_SUCC == NAS_EMM_IsGuContainPsRegDrx())
        && (NAS_EMM_NO == NAS_LMM_GetEmmInfoDrxNetCapChange()))
    {
        return;
    }

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_EncodeDrxPara:ucNonDrxTimer = , ucSplitOnCcch = ",
                           NAS_MML_GetNonDrxTimer(),NAS_MML_GetSplitOnCcch());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeDrxPara_ENUM,LNAS_FUNCTION_LABEL1,
                           NAS_MML_GetNonDrxTimer(),NAS_MML_GetSplitOnCcch());

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_EncodeDrxPara:ucSplitPgCode = , ucPsDrxLen = ",
                           NAS_MML_GetSplitPgCycleCode(),NAS_MML_GetUeEutranPsDrxLen());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeDrxPara_ENUM,LNAS_FUNCTION_LABEL2,
                           NAS_MML_GetSplitPgCycleCode(),NAS_MML_GetUeEutranPsDrxLen());
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    if (NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
    {
        NAS_EMM_TAU_SaveEmmTauContainDrxFlag(NAS_EMM_YES);
    }

    pucReqMsg[ulIndex++]            = NAS_EMM_AD_DRX_IEI;
    pucReqMsg[ulIndex++]            = NAS_EMM_GetSplitPgCycleCode();
    ucDrxByte                       = NAS_EMM_GetNonDrxTimer();
    ucDrxByte                      |= (VOS_UINT8)(NAS_EMM_GetSplitOnCcch()
                                                    << NAS_EMM_AD_MOVEMENT_3_BITS);
    ucDrxByte                      |= (VOS_UINT8)(NAS_EMM_GetUeEutranPsDrxLen()
                                                    << NAS_EMM_AD_MOVEMENT_4_BITS);
    pucReqMsg[ulIndex++]            = ucDrxByte;

    *pulIeLength                    = ulIndex;
    /*PC REPLAY MODIFY BY LEILI END*/
    return;
}
VOS_VOID  NAS_EMM_EncodeMsNetworkCapability
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_EMM_MS_NET_CAP_STRU             *pstMsNetCap;
    NAS_LMM_PUB_INFO_STRU               *pstEmmInfo;

    /*add by lifuxin 2014-07-22 for coverity start*/
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  stMsNetCapa = {0};
    /*add by lifuxin 2014-07-22 for coverity start*/

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsNetworkCapability: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    pstEmmInfo                          = NAS_LMM_GetEmmInfoAddr();
    pstMsNetCap                         = NAS_LMM_GetEmmInfoMsNetCapAddr();

    /* ��������ǵ�ģ�������MS network capability��Ԫ*/
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Single Mode.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL1);
        return;

    }

    /* ��ǰΪ��ģ�µ�TAU��Ϣ����ΪPeriodic TAU�������MS network capability��Ԫ*/
    if((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
     &&(NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Periodic TAU.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* ������������MS network capability��Ԫ*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Fill MsNetCap IE.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL3);

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    NAS_EMM_GetMsNetworkCapability(&stMsNetCapa);
    /*PC REPLAY MODIFY BY LEILI END*/

    /* ����GU��ȡ��MS�����������浽���� */
    if (NAS_LMM_NULL != stMsNetCapa.ucNetworkCapabilityLen)
    {
        pstEmmInfo->bitOpMsNetCap = NAS_EMM_BIT_SLCT;
        pstMsNetCap->ucMsNetCapLen = stMsNetCapa.ucNetworkCapabilityLen;
        NAS_LMM_MEM_CPY(            pstMsNetCap->aucMsNetCap,
                                                stMsNetCapa.aucNetworkCapability,
                                                NAS_MM_MAX_MS_NET_CAP_LEN);
    }
    else
    {
        pstEmmInfo->bitOpMsNetCap = NAS_EMM_BIT_NO_SLCT;

    }
    if(NAS_MM_MAX_MS_NET_CAP_LEN >= stMsNetCapa.ucNetworkCapabilityLen)
    {
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_NET_CAPA_IEI;

        pucReqMsg[ulIndex++]        = stMsNetCapa.ucNetworkCapabilityLen;
        NAS_LMM_MEM_CPY(            &(pucReqMsg[ulIndex]),
                                    stMsNetCapa.aucNetworkCapability,
                                    stMsNetCapa.ucNetworkCapabilityLen);

        ulIndex                     += stMsNetCapa.ucNetworkCapabilityLen;

        *pulIeLength                = ulIndex;
        return;
    }

    if(NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_MsNetCap())
    {
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_NET_CAPA_IEI;
        pucReqMsg[ulIndex++]        = pstMsNetCap->ucMsNetCapLen;
        NAS_LMM_MEM_CPY(            &(pucReqMsg[ulIndex]),
                                    pstMsNetCap->aucMsNetCap,
                                    pstMsNetCap->ucMsNetCapLen);

        ulIndex                     += pstMsNetCap->ucMsNetCapLen;

        *pulIeLength                = ulIndex;

    }

    return;
}



VOS_VOID  NAS_EMM_EncodeLai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeLai: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeLai_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeLai:cn msg type,attach type,tau type",
                             enCnMsgType,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeLai_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL1,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* �����ATTACH REQ��Ϣ���Ҳ�������ע�ᣬ��Я��LAI ��Ԫ */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType()))
    {
        return ;
    }

    /* �����TAU REQ��Ϣ���Ҳ�������TAU����Я��LAI ��Ԫ */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype()))
    {
        return ;
    }

    /* �����IMSI CN DETACH ���µ�����TAU����Я��LAI��Ϣ */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_IMSI_DETACH_VALID == NAS_EMM_TAU_GetImsiDetachFlag()))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeLai:Imsi cn detach no LAI!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL2);

        return ;
    }
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*�ж��Ƿ����LAI*/
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_LAI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeLai:LAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL3);

        /*���Old location area identification*/
        pucReqMsg[ulIndex++]            = NAS_EMM_AD_LAI_IEI;
        NAS_LMM_MEM_CPY(                 &(pucReqMsg[ulIndex]),
                                        stGuInfo.u.stLai.stPlmnId.aucPlmnId,
                                        NAS_EMM_AD_LEN_PLMN_ID);
        ulIndex                         += NAS_EMM_AD_LEN_PLMN_ID;

        pucReqMsg[ulIndex++]            = stGuInfo.u.stLai.stLac.ucLac;
        pucReqMsg[ulIndex++]            = stGuInfo.u.stLai.stLac.ucLacCnt;
        *pulIeLength                    = ulIndex;
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    return;
}
VOS_VOID  NAS_EMM_EncodeTmsiStatus
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeTmsiStatus: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeTmsiStatus:cn msg type,attach type,tau type",
                             enCnMsgType,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_FUNCTION_LABEL1,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* �����ATTACH REQ��Ϣ���Ҳ�������ע�ᣬ��Я��TMSI STATUS ��Ԫ */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType()))
    {
        return ;
    }

    /* �����TAU REQ��Ϣ���Ҳ�������TAU����Я��TMSI STATUS ��Ԫ */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype()))
    {
        return ;
    }
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_TMSI_STATUS,&stGuInfo);

    /* �����IMSI CN DETACH ���µ�����TAU������GUģ������TMSI��Ϣ�������TMSI STATUS��Ԫ */
    if (((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
                && (NAS_EMM_IMSI_DETACH_VALID == NAS_EMM_TAU_GetImsiDetachFlag()))
        || ((MMC_LMM_SUCC == ulRslt) && (MMC_LMM_TMSI_STATUS_INVALID == stGuInfo.u.ulTmsiStatus)))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeTmsiStatus:TMSI STATUS INVALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_FUNCTION_LABEL2);

        /*���TMSI IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_IEI_TMSI;

        /* ��� TMSI�� spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_IE_TMSI_SPARE;

        /* ��� TMSI�� flag */
        pucReqMsg[ulIndex]              |= (VOS_UINT8)MMC_LMM_TMSI_STATUS_VALID;
        ulIndex ++;
        *pulIeLength                    = ulIndex;
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    return;
}


VOS_VOID  NAS_EMM_EncodeMsClassMark2
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                          *pucReqMsg           = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN] = {0};
    VOS_UINT32                          ulIsSupportSrvccToGU= NAS_EMM_BIT_NO_SLCT;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsClassMark2: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_NULL_PTR);

        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    ulIsSupportSrvccToGU = NAS_EMM_GetSuppSrvccToGU();

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeMsClassMark2:cn mst type",
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeMsClassMark2:support srvcc or not,attach type,tau type",
                             ulIsSupportSrvccToGU,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL1,
                             ulIsSupportSrvccToGU);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL2,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* �����ATTACH REQ��Ϣ���Ҳ�������ע�ᣬҲ��֧��SRVCC TO GU����Я��CLASSMARK2��Ԫ */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType())
        && (NAS_EMM_BIT_NO_SLCT == ulIsSupportSrvccToGU))
    {
        return ;
    }

    /* �����TAU REQ��Ϣ���Ҳ�������TAU��Ҳ��֧��SRVCC TO GU����Я��CLAMARK2��Ԫ */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_BIT_NO_SLCT == ulIsSupportSrvccToGU))
    {
        return ;
    }
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ��GU��ȡclassmark2 */
    NAS_EMM_FillIEClassMark2(aucMsClassMark2);
    /*PC REPLAY MODIFY BY LEILI END*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsClassMark2: MsClassMark2's value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                        aucMsClassMark2,
                        NAS_MML_CLASSMARK2_LEN);

    if(NAS_MML_CLASSMARK2_LEN > aucMsClassMark2[0])
    {
        /*���Mobile station classmark 2 IEI*/
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_CLASSMARK2_IEI;

        /* ��Ԫ���� */
        pucReqMsg[ulIndex++]        = aucMsClassMark2[0];

        /* ����������֮���ʣ�ಿ�� */
        NAS_LMM_MEM_CPY(&pucReqMsg[ulIndex], &aucMsClassMark2[1], aucMsClassMark2[0]);
        ulIndex += aucMsClassMark2[0];
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_EncodeMsClassMark2: MsClassMark2's length is ERR:", aucMsClassMark2[0]);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL4,aucMsClassMark2[0]);
    }

    *pulIeLength = ulIndex;

    return;
}
VOS_VOID  NAS_EMM_EncodeMsClassMark3
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8            *pucReqMsg;
    VOS_UINT32           ulIndex = NAS_EMM_NULL;
    /*sunbing 49683 2013-10-14 VoLTE begin*/
    VOS_UINT8            aucMsClassMark3[NAS_EMM_AD_LEN_MS_CLASSMARK3+1] = {0};/*����һ��byte��Lenth�ı���ռ�*/
    /*sunbing 49683 2013-10-14 VoLTE end*/


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsClassMark3: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*�ж��Ƿ�֧��Mobile station classmark 3*/
    if (NAS_EMM_BIT_SLCT != NAS_EMM_GetSuppSrvccToGU())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeMsClassMark3:Not support SRVCC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*sunbing 49683 2013-10-14 VoLTE begin*/
    /* ��GU��ȡclassmark3 */
    if(MMC_LMM_UTRAN_MODE_FDD == NAS_LMM_GetEmmInfoUtranMode())
    {
        NAS_MML_Fill_IE_FddClassMark3(aucMsClassMark3);
    }
    else
    {
        NAS_MML_Fill_IE_TddClassMark3(aucMsClassMark3);
    }

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsClassMark3: MsClassMark3's value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_FUNCTION_LABEL2);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                        aucMsClassMark3,
                        NAS_EMM_AD_LEN_MS_CLASSMARK3+1);

    if(NAS_EMM_AD_LEN_MS_CLASSMARK3 >= aucMsClassMark3[0])
    {
        /*���Mobile station classmark 3 IEI*/
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_CLASSMARK3_IEI;

        /* ��Ԫ���� */
        pucReqMsg[ulIndex++]        = aucMsClassMark3[0];

        /* ����������֮���ʣ�ಿ�� */
        NAS_LMM_MEM_CPY(&pucReqMsg[ulIndex], &aucMsClassMark3[1], aucMsClassMark3[0]);
        ulIndex += aucMsClassMark3[0];
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_EncodeMsClassMark3: MsClassMark3's length is ERR:", aucMsClassMark3[0]);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_ERROR,aucMsClassMark3[0]);
    }

    *pulIeLength = ulIndex;
    /*sunbing 49683 2013-10-14 VoLTE end*/

    return;
}


VOS_VOID  NAS_EMM_EncodeSupportedCodecs
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_LMM_CODEC_LIST_STRU             *pstCodecList;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeSupportedCodecs: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeSupportedCodecs_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    pstCodecList                        = NAS_LMM_GetEmmInfoSupCodecListAddr();

    /*�ж��Ƿ�֧��Supported Codecs*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GetSuppSrvccToGU())
    {
        if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_SupCodecList())
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeSupportedCodecs:Encode upported Codecs");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeSupportedCodecs_ENUM,LNAS_FUNCTION_LABEL1);

            /*���Supported Codecs IEI*/
            pucReqMsg[ulIndex++]        = NAS_EMM_AD_SUPPORT_CODECS_IEI;

            /* ��� Supported Codecs�� L */
            pucReqMsg[ulIndex++]        = pstCodecList->ucLenOfCodecList;

            /* ��� Supported Codecs�� V */
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].ucSysId;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].ucLenOfBitmap;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].aucCodecBitmap[0];
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].aucCodecBitmap[1];

            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].ucSysId;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].ucLenOfBitmap;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].aucCodecBitmap[0];
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].aucCodecBitmap[1];

            *pulIeLength                = ulIndex;

        }
    }

    return;
}



VOS_VOID  NAS_EMM_EncodeAdditionUpdateType
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    /* add by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,begin */
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;
    /* add by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,end */

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeAdditionUpdateType: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,begin */
    ulCsService = NAS_EMM_GetCsService();
    /* coverity[unchecked_value] */
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeAdditionUpdateType:cs service :",
                             ulCsService);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_EMM_CSSERVICECFG,
                             ulCsService);

    /*�ж��Ƿ�Я��Additional update type*/
    if (NAS_LMM_CS_SERVICE_SMS_ONLY == ulCsService)
    {
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,end */
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeAdditionUpdateType:SMS ONLY");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_FUNCTION_LABEL1);

        /*���Additional update type IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_IEI_AUT;

        /* ��� Additional update type�� spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_IE_AUT_SPARE;

        /* ��� Additional update type�� AUTV */
        pucReqMsg[ulIndex]              |= NAS_EMM_IE_AUTV;
        ulIndex ++;
        *pulIeLength                    = ulIndex;

    }

    return;
}


VOS_VOID  NAS_EMM_EncodeVoiceDomainAndUsageSetting
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    NAS_EMM_PUB_INFO_STRU               *pstPubInfo;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt;
    /* add by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,begin */
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;
    /* add by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,end */
    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeVoiceDomainAndUsageSetting: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,begin */
    ulCsService = NAS_EMM_GetCsService();
    NAS_EMM_ATTACH_LOG2_NORM("NAS_EMM_EncodeVoiceDomainAndUsageSetting:\
                            NAS_EMM_GetVoiceDomain=,NAS_EMM_GetCsService()=",
                            NAS_EMM_GetVoiceDomain(),
                            ulCsService);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetVoiceDomain(),
                            ulCsService);


    /*����Э��Ҫ�� ��VOIC domain preference and UE's usage setting, Э����
    ����: The IE shall be included if the UE supports CS fallback and SMS
    over SGs, or if the UE is configured to support IMS voice, ��֧��csfb��
    ʱ�򣬱�����CS+PS��ע�᷽ʽ������EPS onlyʱ������ҪЯ����IE*/
    /*�ж��Ƿ�Я��Voice domain preference and UE's usage setting*/
    if (((NAS_LMM_CS_SERVICE_CSFB_SMS == ulCsService) &&
         (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())) ||
        (((NAS_LMM_VOICE_DOMAIN_CS_ONLY < NAS_EMM_GetVoiceDomain()) &&
          (NAS_LMM_VOICE_DOMAIN_BUTT > NAS_EMM_GetVoiceDomain())) &&
          (NAS_LMM_CS_SERVICE_1xCSFB != ulCsService)))
    {
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-14,end */
        pstPubInfo = NAS_LMM_GetEmmInfoAddr();
        if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeVoiceDomainAndUsageSetting: Encode Voice Domain");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_FUNCTION_LABEL2);

            /*���Voice domain preference and UE's usage setting IEI*/
            pucReqMsg[ulIndex++]            = NAS_EMM_AD_VOICE_DOMAIN_AND_USAGE_SETTING_IEI;

            /* ��� Voice domain preference and UE's usage setting�� L */
            pucReqMsg[ulIndex++]            = NAS_EMM_AD_LEN_VOICE_DOMAIN;

            /* ��� Voice domain preference and UE's usage setting�� V */
            NAS_EMM_SetUeUsageSetting();
            ulRslt = NAS_LMM_GetEmmInfoVoiceDomain();
            pucReqMsg[ulIndex]              = (VOS_UINT8)(NAS_EMM_GLO_AD_GetUsgSetting() << NAS_EMM_AD_MOVEMENT_2_BITS);
            pucReqMsg[ulIndex]              |= (VOS_UINT8)ulRslt;
            ulIndex ++;
            *pulIeLength                    = ulIndex;
        }
    }

    return;
}
VOS_VOID  NAS_EMM_EncodeTmsiBasedNriContainer
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                          *pucTmsi             = VOS_NULL_PTR;
    VOS_UINT8                          *pucReqMsg           = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, begin */
    /* ��ȡ��ǰ��TMSI */
    pucTmsi  = NAS_EMM_GetUeIdTmsi();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,end */

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeTmsiBasedNriContainer: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeTmsiBasedNriContainer_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeTmsiBasedNriContainer:TMSI :",
                             pucTmsi);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeTmsiBasedNriContainer_ENUM,LNAS_EMM_TMSI_NUMBER,pucTmsi);

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /* ���TMSI��Ч���򲻱������Ԫ */
    if(VOS_FALSE  == NAS_MML_IsTmsiValid())
    {
        return;
    }

    if (VOS_NULL_PTR == pucTmsi )
    {
        return;
    }

    /*���Mobile station classmark 2 IEI*/
    pucReqMsg[ulIndex++]        = NAS_EMM_AD_TMSI_BASED_NRI_CONTAINER_IEI;

    /* ��Ԫ���� */
    pucReqMsg[ulIndex++]        = NAS_EMM_AD_LEN_TMSI_BASED_NRI_CONTAINER;

    /* ��TMSI�д� bit23��bit14��10bit�����ݱ���ΪTMSI based NRI container��Ԫ */
    /* NRI container value shall start with bit 8 of octet 3, which corresponds to bit 23 of TMSI.
        Bit 7 of octet 4 corresponds to TMSI bit 14.
        Bits 6, 5, 4, 3, 2, and 1 in octet 4 are spare and shall be set to zero.*/

    pucReqMsg[ulIndex++]        = pucTmsi[2];
    pucReqMsg[ulIndex++]        = (pucTmsi[1] & NAS_EMM_HITH2_BYTE);

    *pulIeLength                = ulIndex;

    return;
}



NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinPtmsiEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinPtmsiEncodeGutiType:TIN IS P-TMSI");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinPtmsiEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinPtmsiEncodeGutiType: P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinPtmsiEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);
        /*ӳ��GUTI��Ч*/
        ucGutiType = NAS_EMM_GUTI_TYPE_MAPPED;
    }
    return ucGutiType;
}
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType_ENUM,LNAS_EMM_TIN_TYPE);
        /*GUTI��Ч*/
        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;
    }
    return ucGutiType;
}
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinInvaidEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:TIN INVALID");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);
        /*GUTI��Ч*/
        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;

    }
    else if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL3);
        /*ӳ��GUTI��Ч*/
        ucGutiType = NAS_EMM_GUTI_TYPE_MAPPED;

    }
    else
    {
        ;
    }
    return ucGutiType;
}


NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_SingleModeEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SingleModeEncodeGutiType:NOT SUPPOR MUTI MODE");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SingleModeEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        /*GUTI��Ч*/
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SingleModeEncodeGutiType: GUTI VALID!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SingleModeEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);

        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;
    }
    return ucGutiType;
}
VOS_VOID  NAS_EMM_EncodeGutiType
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeGutiType: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeGutiType_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*֧�ֶ�ģ*/
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            ucGutiType = NAS_EMM_MutiModeTinPtmsiEncodeGutiType();
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            ucGutiType = NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType();
        }
        else if (MMC_LMM_TIN_INVALID == ulTinType)
        {
            ucGutiType = NAS_EMM_MutiModeTinInvaidEncodeGutiType();

        }
        else
        {

        }
    }
    else
    {
        /*��ģ*/
        ucGutiType = NAS_EMM_SingleModeEncodeGutiType();

    }

    if (NAS_EMM_GUTI_TYPE_BUTT == ucGutiType)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeGutiType:not encode guti type");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeGutiType_ENUM,LNAS_EMM_TIN_TYPE);
        return;
    }

    /*GUTI��ЧЯ����IE*/
    /*���GUTI TYPE IEI*/
    pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_GUTI_TYPE_IEI;

    /* ��� GUTI TYPE�� spare */
    pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

    /* ���GUTI TYPE��GUTI type */
    pucReqMsg[ulIndex]              |= ucGutiType;

    ulIndex ++;

    *pulIeLength                        = ulIndex;

    return;
}


VOS_VOID    NAS_EMM_CompCnAttachCmp
(
    LRRC_LNAS_MSG_STRU                 *pAttCmp,
    VOS_UINT32                         *pulIndex,
    const EMM_ESM_MSG_STRU             *pstEsmMsg
)
{
    VOS_UINT32                          ulIndex     = *pulIndex;
    VOS_UINT16                          usEsmMsgLen = NAS_EMM_NULL;

    /*������CN��Ϣ�Ŀռ�*/
    /* xiongxianghui00253310 delete memset 2013-11-26 begin */
    /* NAS_LMM_MEM_SET(pAttCmp->aucNasMsg, 0, pAttCmp->ulNasMsgSize); */
    /* xiongxianghui00253310 delete memset 2013-11-26 end   */

    /* ��� Protocol Discriminator + Security header type */
    pAttCmp->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* ��� Attach request message identity   */
    pAttCmp->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_ATTACH_CMP;

    /*���ESM message container*/
    usEsmMsgLen                         = (VOS_UINT16)pstEsmMsg->ulEsmMsgSize;
    pAttCmp->aucNasMsg[ulIndex++]       = (usEsmMsgLen>>8)& 0xFF;
    pAttCmp->aucNasMsg[ulIndex++]       = usEsmMsgLen & 0xFF;

    NAS_LMM_MEM_CPY(                    &(pAttCmp->aucNasMsg[ulIndex]),
                                        pstEsmMsg->aucEsmMsg,
                                        pstEsmMsg->ulEsmMsgSize);

    *pulIndex = ulIndex + pstEsmMsg->ulEsmMsgSize;
}
VOS_VOID    NAS_EMM_MrrcSendAttReq( VOS_VOID )
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg = NAS_EMM_NULL_PTR;
    NAS_MSG_STRU                        *pstNasMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_MrrcSendAttReq,ESM MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcSendAttReq_ENUM,LNAS_BEGIN);

    /*������Ϣ�ڴ�*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*����ATTACH REQUEST��Ϣ*/
    NAS_EMM_CompCnAttachReq( pIntraMsg);

    /* ���������ATTACH����֪ͨMM����MM LOCATION UPDATING PENDING״̬ */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_SendMmCombinedStartNotifyReq(MM_LMM_COMBINED_ATTACH);
    }

    /*��OM���Ϳտ���ϢATTACH REQUEST*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));

    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_ATTACH_REQ,
                                        pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_ATTACH_REQ);
    /* ������: ����attach������� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
    NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*��MRRC����ATTACH REQUEST��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    /* ����ATTACH������ǰTA��Ϣͬ����Last���Է���ע���TA��Ϣ�� */
    NAS_EMM_SaveLastAttemptRegTa();

    /* ����ATTACH����ע��״̬����ΪATTACHδ���� */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND);

    NAS_LMM_MEM_FREE(pIntraMsg);
    /* ������: ��¼ATTACH REQ SNDʱ�� */
    NAS_LMM_SaveAttachReqSndTimeStamp();
    return;

}
VOS_VOID    NAS_EMM_MrrcSendAttCmp
(
    const EMM_ESM_MSG_STRU             *pstEsmMsg
)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg;
    VOS_UINT32                          ulMrrcDataReqMsgLenNoHeader;
    NAS_MSG_STRU                       *pstNasMsg;
    VOS_UINT32                          ulIndex             =0;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_MrrcSendAttCmp,ESM MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcSendAttCmp_ENUM,LNAS_BEGIN);

    /*������Ϣ�ڴ�*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /* xiongxianghui00253310 add memset 2013-11-26 begin */
    /*lint -e669*/
    NAS_LMM_MEM_SET(pIntraMsg, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);
    /*lint +e669*/
    /* xiongxianghui00253310 add memset 2013-11-26 end   */

    /*����ATTACH COMPLETE��Ϣ*/
    NAS_EMM_CompCnAttachCmp(            &(pIntraMsg->stNasMsg),&ulIndex,pstEsmMsg);

    ulMrrcDataReqMsgLenNoHeader         = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulMrrcDataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_MrrcSendAttCmp, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MrrcSendAttCmp_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pIntraMsg);
        return ;
    }

    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pIntraMsg, ulMrrcDataReqMsgLenNoHeader);

    /*�����ϢID*/
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*�����Ϣ����*/
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MSG_ATTACH_CMP;

    /*�����Ϣ�Ƿ���ҪRRC�Դ�����ȷ��*/
    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    /*�����Ϣ��EMM���͵Ļ���ESM���͵�*/
    pIntraMsg->ulEsmMmOpId             = NAS_LMM_OPID;

    /*�����Ϣ����*/
    pIntraMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*��OM���Ϳտ���ϢATTACH COMPLETE*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_ATTACH_CMP, pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_ATTACH_CMP);

    /*��MRRC����ATTACH COMPLETE��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);
    /* ������: ��¼ATTACH CMP Sndʱ�� */
    NAS_LMM_SaveAttachCmpSndTimeStamp();
    return;

}
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
#if (VOS_OS_VER != VOS_WIN32)
    FTM_TMODE_ENUM                      enMspFtmMode = EN_FTM_TMODE_SIGNAL ;
#endif

    EMM_ESM_PDN_CON_RSP_STRU             *pRcvEmmMsg;

    pRcvEmmMsg                          = (EMM_ESM_PDN_CON_RSP_STRU *) pMsgStru;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG1_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp: STATE ERR! ulMsgId:",ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_ERROR,ulMsgId);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_EsmPdnRspMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp: EMM_ESM_PDN_CON_RSP_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_PARAM_INVALID);
        return NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*ֹͣ��ʱ��WAIT_ESM_PDN_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*ֹͣ��ʱ��T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*ֹͣ��ʱ��T3402*/
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    if(EMM_ESM_PDN_CON_RSLT_SUCC == pRcvEmmMsg->ulRst)
    {
        /*����ESM��Ϣ*/
        NAS_LMM_MEM_CPY(             NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                                        &(pRcvEmmMsg->stEsmMsg),
                                        (pRcvEmmMsg->stEsmMsg.ulEsmMsgSize)+4);

#if (VOS_OS_VER != VOS_WIN32)
        /*BTģʽ�£�����������⣬�޸�������ʱ���ȴ�������Ӧ*/
        if((LPS_OM_GetTmode(&enMspFtmMode)== ERR_MSP_SUCCESS)&&(EN_FTM_TMODE_SIGNAL_NOCARD == enMspFtmMode))
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp:T3410 modify 240s!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_ModifyStateTimer(TI_NAS_EMM_T3410, 240000);         /*240s*/
        }
#endif

        /*������ʱ��T3410*/
        NAS_LMM_StartStateTimer(     TI_NAS_EMM_T3410);

        /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_CN_ATTACH_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                        TI_NAS_EMM_T3410);

        NAS_EMM_MrrcSendAttReq();

        /* 33401 CR457������UE������ȥע��̬תȥע��̬ʱ����Ҫ��SIM������NV�еİ�ȫ
        ����������Ϊ��Ч*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


    }
    else
    {
        /*��MMC������Ϣ*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ESM_FAILURE);

        /*ATTACH�����Դ*/
        NAS_EMM_Attach_ClearResourse();

        /*��ESM����ID_EMM_ESM_REL_IND*/
        NAS_EMM_EsmSendRelInd();

        /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /* �������CONN̬,�ͷ�����*/
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        }

    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    EMM_ESM_PDN_CON_SUCC_REQ_STRU      *pRcvEmmMsg = VOS_NULL_PTR;
    /*NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = VOS_NULL_PTR;*/
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulNasSndDrvCnt = 1;
#endif

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (EMM_ESM_PDN_CON_SUCC_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(                  TI_NAS_EMM_WAIT_ESM_BEARER_CNF);


#if (VOS_OS_VER != VOS_WIN32)
    if (1 == s_ulNasSndDrvCnt)
    {
        (VOS_VOID)LDRV_SYSBOOT_STAMPADD("Nas reg End",__LINE__);
        s_ulNasSndDrvCnt++;
    }
#endif

    /*������ʱ��TI_NAS_EMM_WAIT_RRC_DATA_REQ_CNF*/
    NAS_LMM_StartStateTimer(            TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*�޸�״̬��������״̬REG��״̬REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_RRC_DATA_CNF,
                                        TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*��MRRC����ATTACH COMPLETE*/
    NAS_EMM_MrrcSendAttCmp(             &pRcvEmmMsg->stEsmMsg);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    NAS_EMM_ATTACH_LOG2_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq is entered",
                                        ulMsgId,
                                        pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_ENTRY,
                                        ulMsgId,
                                        pMsgStru);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*check input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* ������: ����attach ESM����ʧ�ܴ��� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ESM_FAIL);
    /*֪ͨAPPȱʡ���ؼ���ʧ��*/
    /*NAS_EMM_AttSendAppResult(APP_ERR_MM_ATTACH_FAIL_ACT_DEFAULT_BEARER_FAIL);*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_ESM_FAILURE);

    /* ����ATTACH������дDETACH���� */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_CS_PS);
    }
    else
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_PS_ONLY);
    }

    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq(VOS_UINT32  ulMsgId,
                                           VOS_VOID   *pMsgStru)
{
    EMM_ESM_EST_REQ_STRU                 *pRcvEmmMsg;

    pRcvEmmMsg                          = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*ֹͣ��ʱ��T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*ֹͣ��ʱ��T3402*/
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);

    if (VOS_TRUE == pRcvEmmMsg->ulIsEmcType)
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

        /* ����������͵�ESM��Ϣ */
        NAS_EMM_SaveEmcEsmMsg(          (VOS_VOID*)pRcvEmmMsg);

        /* ������ͨATTACH���� */
        NAS_EMM_EsmSendPdnConnInd(      0);
        NAS_LMM_StartStateTimer(        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    }
    else
    {
        /*����ESM��Ϣ*/
        NAS_LMM_MEM_CPY(                NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                                        &(pRcvEmmMsg->stEsmMsg),
                                        (pRcvEmmMsg->stEsmMsg.ulEsmMsgSize)+4);
        /*���津��ATTACH��ԭ��*/
        NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM;

        /*������ʱ��T3410*/
        NAS_LMM_StartStateTimer(        TI_NAS_EMM_T3410);

        /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_CN_ATTACH_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                        TI_NAS_EMM_T3410);
        /* ������: ��¼ATTACH����Startʱ�� */
        NAS_LMM_SaveAttachStartTimeStamp();
        /*��MRRC����ATTACH REQUEST��Ϣ*/
        NAS_EMM_MrrcSendAttReq();
        /* 33401 CR457������UE������ȥע��̬תȥע��̬ʱ����Ҫ��SIM������NV�еİ�ȫ
        ����������Ϊ��Ч*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq
 Description     : ��״̬DEREG+��״̬DEREG_ATTEMPT_TO_ATTACH���յ�ESM����Ϣ
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010         2012-10-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                               *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pRcvEmmMsg = NAS_EMM_NULL_PTR;

    pRcvEmmMsg                          = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE != pRcvEmmMsg->ulIsEmcType)
    {
        /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*ֹͣ��ʱ��T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*ֹͣ��ʱ��T3402*/
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    NAS_MML_SetPsAttachAllowFlg(    NAS_EMM_AUTO_ATTACH_ALLOW);

    /* ��¼ATTACH����ԭ��ֵ */
    NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

    /* ����������͵�ESM��Ϣ */
    NAS_EMM_SaveEmcEsmMsg(          pMsgStru);

    /* ������ͨATTACH���� */
    NAS_EMM_EsmSendPdnConnInd(      0);
    NAS_LMM_StartStateTimer(        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                    EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                    TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    return  NAS_LMM_MSG_HANDLED;
}
VOS_VOID  NAS_EMM_StartEmergencyAttach( VOS_VOID )
{
    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_StartEmergencyAttach is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_StartEmergencyAttach_ENUM,LNAS_ENTRY);

    /*ֹͣ��ʱ��T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*ֹͣ��ʱ��T3402*/
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*���津��ATTACH��ԭ��*/
    NAS_EMM_GLO_AD_GetAttCau()    = EMM_ATTACH_CAUSE_ESM_EMC_ATTACH;
    NAS_MML_SetPsAttachAllowFlg(    NAS_EMM_AUTO_ATTACH_ALLOW);
    NAS_LMM_SetEmmInfoRegStatus(    NAS_LMM_REG_STATUS_EMC_REGING);
    NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

    /*������ʱ��T3410*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3410);

    /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_CN_ATTACH_CNF*/
    NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                    EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                    TI_NAS_EMM_T3410);
    /* ������: ��¼ATTACH����Startʱ�� */
    NAS_LMM_SaveAttachStartTimeStamp();
    /*��MRRC����ATTACH REQUEST��Ϣ*/
    NAS_EMM_MrrcSendAttReq();
    /* 33401 CR457������UE������ȥע��̬תȥע��̬ʱ����Ҫ��SIM������NV�еİ�ȫ
    ����������Ϊ��Ч*/
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


}


VOS_UINT32  NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ���������ֱ�ӻظ�ʧ�� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*����ESM��Ϣ*/
    NAS_LMM_MEM_CPY(        NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                           &(pstEsmEstReq->stEsmMsg),
                            (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ���������ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*����ESM��Ϣ*/
    NAS_LMM_MEM_CPY(        NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                           &(pstEsmEstReq->stEsmMsg),
                            (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ���������ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*����ESM��Ϣ*/
    NAS_LMM_MEM_CPY(        NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                           &(pstEsmEstReq->stEsmMsg),
                            (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_DATA_REQ_STRU                 *pstEsmDataReq = NAS_EMM_NULL_PTR;

    pstEsmDataReq                        = (EMM_ESM_DATA_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ���������ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmDataReq->ulIsEmcType)
    {
        /* lihong00150010 emergency tau&service begin */
        if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
            (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
        {
            NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
            return NAS_LMM_MSG_HANDLED;
        }
        /* lihong00150010 emergency tau&service end */
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*//* ESM�������������̬��¼ */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /*����ESM��Ϣ*/
    NAS_LMM_MEM_CPY(        NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                           &(pstEsmDataReq->stEsmMsg),
                            (pstEsmDataReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegInitMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsRegInitMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);


    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (EMM_MS_REG_INIT != NAS_EMM_AD_CUR_MAIN_STAT)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ���������ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ڽ��е�ATTACH���� */
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_T3410);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_RRC_DATA_CNF);



    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
    NAS_EMM_AppSendAttFailWithPara();
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt() >= 5)
    {
        /*����update statusΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    }

    NAS_EMM_AttResetAttAttempCounter();

    /* �������IDLE̬,ֱ�ӷ������ע��*/
    if (NAS_EMM_CONN_IDLE               == NAS_EMM_GetConnState())
    {
        /*����ESM��Ϣ*/
        NAS_LMM_MEM_CPY(                NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                                       &(pstEsmEstReq->stEsmMsg),
                                        (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ��¼ATTACH����ԭ��ֵ */
    NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_LMM_SetEmmInfoIsEmerPndEsting(  VOS_TRUE);

    /* ����������͵�ESM��Ϣ */
    NAS_EMM_SaveEmcEsmMsg(              (VOS_VOID*)pstEsmEstReq);

    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ������ͣ��򲻿����յ�������յ���ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ������ǽ������ͣ��򲻿����յ�������յ���ֱ�Ӷ��� */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq( VOS_VOID )
{
    VOS_UINT32                          ulCurEmmMsStat = NAS_LMM_GetEmmCurFsmMS();
    VOS_UINT32                          ulCurEmmSsStat = NAS_LMM_GetEmmCurFsmSS();

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq:EpsNumId=0");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq_ENUM,LNAS_BEGIN);

    /* ��״̬Ϊ��ע��̬��ֱ�ӷ��� */
    if ((EMM_MS_NULL == ulCurEmmMsStat)||(EMM_MS_DEREG == ulCurEmmMsStat))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* R10�汾��CSFB�����⴦�� */
    if (NAS_RELEASE_CTRL)
    {
        if ((EMM_MS_SER_INIT == ulCurEmmMsStat)
            && (EMM_SS_SER_WAIT_CN_SER_CNF == ulCurEmmSsStat)
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq:ESR procedure");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq_ENUM,LNAS_FUNCTION_LABEL1);

            /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_PLMN_SEARCH,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
            NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
            #endif

            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

            /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
            NAS_LMM_DeregReleaseResource();

            /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
            NAS_EMM_RelReq(                           NAS_LMM_NOT_BARRED);

            return NAS_LMM_MSG_HANDLED;

        }
    }

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /* ����ο���ʶ */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;

        /* ��MMC�ظ�LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();
    }
    /* lihong00150010 emergency tau&service end */

    /* ���ݵ�ǰ��״ִ̬�в�ͬ�ı���DETACH���� */
    switch(ulCurEmmMsStat)
    {
        case    EMM_MS_REG:
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:

                /* ֪ͨESMִ���˱���DETACH */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

                /* ���ݲ�ͬ����״̬ת����Ӧ��δע��״̬ */
                NAS_LMM_MsRegSsAnyLocalDetStateTrans();

                /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

                /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
                NAS_LMM_DeregReleaseResource();

                /* ���δע��״̬��Ŀ��״̬Ϊ�����������·���ATTACH */
                if(EMM_SS_DEREG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
                {
                    /* ������IDLE����פ��ֱ�ӷ���ATTACH�������ͷ���·���յ�ϵͳ��Ϣ�ٷ��� */
                    if(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
                    {
                        (VOS_VOID)NAS_EMM_SendIntraAttachReq();
                        return NAS_LMM_MSG_HANDLED;
                    }

                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                    return NAS_LMM_MSG_HANDLED;
                }

                /* ������normal״ֱ̬�ӵ�ϵͳ��Ϣ */
                break;

        case    EMM_MS_SUSPEND:

                /* ֪ͨESMִ���˱���DETACH */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

                /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
                #endif

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
                break;

        default:
                /* ����״̬����RESUME��REG_INIT����ǰ����³���״̬ */
                break;

    }

    return NAS_LMM_MSG_HANDLED;
}
/*leili modify for isr begin*/

NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_ProcEsmBearState
(
    VOS_UINT32      ulEpsId,
    VOS_VOID        *pstMsg
)
{
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;
    VOS_UINT32              i = 0;

    pstEsmBearerStatusReq               =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    for (i = 0; i < pstEsmBearerStatusReq->ulEpsIdNum; i++)
    {
        if (ulEpsId == pstEsmBearerStatusReq->aulEsmEpsId[i])
        {
            return NAS_EMM_BEARER_STATE_ACTIVE;
        }
    }
    return NAS_EMM_BEARER_STATE_INACTIVE;
}


NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_IsEpsBearStatusAct (VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstEpsBearerCxt;
    VOS_UINT32              i = 0;

    /*add by lifuxin 2014-07-22 for coverity start*/
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30, begin*/
    pstEpsBearerCxt = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30, begin*/
    if(VOS_NULL == pstEpsBearerCxt)
    {
        return NAS_EMM_BEARER_STATE_INACTIVE;
    }
    /*add by lifuxin 2014-07-22 for coverity end*/

    for(i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstEpsBearerCxt[i].enPsBearerState)
        {
            return NAS_EMM_BEARER_STATE_ACTIVE;
        }
    }
    return NAS_EMM_BEARER_STATE_INACTIVE;
}


VOS_VOID  NAS_EMM_UpdateEpsBearStatus(VOS_VOID *pstMsg)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[EMM_ESM_MAX_EPS_BEARER_NUM];
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsId;
    NAS_EMM_BEARER_STATE_ENUM_UINT8     ucEsmBearerState;
    VOS_UINT32                          i = NAS_EMM_NULL;
    VOS_UINT32                          j = NAS_EMM_NULL;
    VOS_UINT16                          usBearerSate;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx         = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus is entry:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    PS_MEM_SET(astPsBearerCtx, 0, sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU)*EMM_ESM_MAX_EPS_BEARER_NUM);

    pstEsmBearerStatusReq =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*ISR���������ESM���͵ĳ�����Ϣ����MMLȫ�ֱ���*/
    if(MMC_LMM_TIN_RAT_RELATED_TMSI != NAS_EMM_GetTinType())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: ISRû�м���");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL1);
        for(i = 0; i < pstEsmBearerStatusReq->ulEpsIdNum; i++)
        {
            j = pstEsmBearerStatusReq->aulEsmEpsId[i] - NAS_EMM_MIN_EPS_ID;

            astPsBearerCtx[j].enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
        }
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_LMM_MEM_CPY(pstPsBearerCtx, astPsBearerCtx, sizeof(astPsBearerCtx));

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: UPDATE PS BEARER INFO");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
        return;
    }

    /*ISR�������ESM������Ϣ����MMLȫ�ֱ���*/
    NAS_LMM_MEM_CPY(astPsBearerCtx, pstPsBearerCtx, sizeof(astPsBearerCtx));

    for (i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        ulEpsId = i + NAS_EMM_MIN_EPS_ID;
        ucEsmBearerState = NAS_EMM_ProcEsmBearState(ulEpsId,pstEsmBearerStatusReq);

        usBearerSate = NAS_LMM_PUB_COMP_BEARERSTATE(astPsBearerCtx[i].enPsBearerState,ucEsmBearerState);
        switch(usBearerSate)
        {
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_ACTIVE,NAS_EMM_BEARER_STATE_INACTIVE):

                /*MML�г���״̬���ESM�г���״̬��������ݵ�ǰISR��ʶ�ж��Ƿ�ȥ����ISR*/
                astPsBearerCtx[i].enPsBearerState = NAS_MML_PS_BEARER_STATE_INACTIVE;
                if (NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT == astPsBearerCtx[i].enPsBearerIsrFlg)
                {
                    /*����TINֵΪGUTI*/
                    NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

                    /*�������г��ص�ISR��ʶΪNONE*/
                    NAS_EMM_UpdateBearISRFlag(astPsBearerCtx);

                }
                astPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
                break;
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_INACTIVE,NAS_EMM_BEARER_STATE_ACTIVE):

                /*MML�г���״̬�����ESM�г���״̬�������MML�г���״̬��ISR��ʶ*/
                astPsBearerCtx[i].enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
                astPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
                break;

            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_ACTIVE,NAS_EMM_BEARER_STATE_ACTIVE):
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_INACTIVE,NAS_EMM_BEARER_STATE_INACTIVE):

                NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: MML BEARER INFO NOT CHANGE:");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL3);
                break;
            default:
                break;
        }
    }

    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_LMM_MEM_CPY(pstPsBearerCtx, astPsBearerCtx, sizeof(astPsBearerCtx));
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: UPDATE PS BEARER INFO");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL4);

    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    /*PC REPLAY MODIFY BY LEILI END*/
    return;
}

/*leili modify for isr end*/

/* lihong00150010 ims begin */
/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcEmcBearerStatusNotify
 Description     : ��MMC����LMM_MMC_EMC_BEARER_STATUS_NOTIFY��Ϣ
 Input           : ucIsEmcPdpActive----------------EMC PDP�Ƿ񼤻��ʶ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2013-12-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmcEmcBearerStatusNotify
(
    VOS_UINT8                           ucIsEmcPdpActive
)
{
    LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU *pstEmcPdpStatusNotify = VOS_NULL_PTR;

    /* ����DOPRA��Ϣ */
    pstEmcPdpStatusNotify = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstEmcPdpStatusNotify)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmcBearerStatusNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmcBearerStatusNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstEmcPdpStatusNotify,0,sizeof(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstEmcPdpStatusNotify),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));

    /* �����ϢID */
    pstEmcPdpStatusNotify->ulMsgId          = ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY;
    pstEmcPdpStatusNotify->ucIsEmcPdpActive = ucIsEmcPdpActive;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstEmcPdpStatusNotify);

    return;
}
/* lihong00150010 ims end */

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq
 Description     : �յ�ESM BEARER STATUS REQ��Ϣʱ����ע��״̬
 Input           : Pointer of EMM_ESM_BEARER_STATUS_REQ_STRU
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2012-10-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq
(
    const EMM_ESM_BEARER_STATUS_REQ_STRU *pstEsmBearerStatusReq
)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[EMM_ESM_MAX_EPS_BEARER_NUM];
    VOS_UINT32                          ulCurEmmStat = NAS_EMM_NULL;

    /* add by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    /* add by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    PS_MEM_SET(astPsBearerCtx, 0, sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU)*EMM_ESM_MAX_EPS_BEARER_NUM);

    if (0 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:DEREG");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_DEREG);
        return ;
    }

    /* ע������У��򲻸���״̬����ATTACH COMPLETE���ͳɹ�
       ���ٸ��£��������͸��£����޷���REG_INIT+WAIT_RRC_DATA_CNF״̬��ʹ��
       NAS_LMM_REG_STATUS_EMC_REGING��ʶ�����ֽ���ע�ỹ����ͨע�ᣬATTACH����
       ԭ��ֵ�ڽ������ؼ���ɹ��嶯̬��ʱ��֪ͨEMM��� */
    if (EMM_MS_REG_INIT == NAS_EMM_AD_CUR_MAIN_STAT)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:attaching.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* ����г��أ���û�н������أ������״̬Ϊ����ע�� */
    if (VOS_FALSE == pstEsmBearerStatusReq->ulExistEmcPdnFlag)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:NORM REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL3);

        /* ���״̬������ע�����н������ر�Ϊ����ע�ᣬ���MMC����
           LMM_MMC_EMC_BEARER_STATUS_NOTIFY��Ϣ��ָʾ���������ͷ� */
        if (NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_SendMmcEmcBearerStatusNotify(VOS_FALSE);
        }

        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED);
        return ;
    }
     /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ����н������أ��ҳ�����Ϊ1�������״̬Ϊ����ע�� */
    if (1 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:EMC REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL4);

        /* lihong00150010 emergency tau&service begin */
        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                    NAS_EMM_CUR_SUB_STAT);

        if (((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
            || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
            && (NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
        {
            NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
            /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
            NAS_LMM_Stop3402Timer();
            /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

            /* TAU��ɺ�����ͨ��ESM������ϢIEȥ�������зǽ������� */
            NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }

        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_EMC_REGED);

        if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
            && (NAS_EMM_NOT_SUSPEND == NAS_EMM_IsSuspended()))
        {
            /* ȥ����ISR */
            NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
        }
        /* lihong00150010 emergency tau&service end */
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
        NAS_LMM_MEM_CPY(astPsBearerCtx, pstPsBearerCtx, sizeof(astPsBearerCtx));

        /*�������г��ص�ISR��ʶΪNONE*/
        NAS_EMM_UpdateBearISRFlag(astPsBearerCtx);

        NAS_LMM_MEM_CPY(pstPsBearerCtx, astPsBearerCtx, sizeof(astPsBearerCtx));
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

        return ;
    }
     /*PC REPLAY MODIFY BY LEILI END*/
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:NORM REGED AND EMC BEARER");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:state:",NAS_LMM_GetEmmInfoRegStatus());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_EMM_REG_STATE,
                                        NAS_LMM_GetEmmInfoRegStatus());

    /* ����н������أ��ҳ���������1�������״̬Ϊ����ע�����н������� */
    /* ���״̬������ע���Ϊ����ע�����н������أ����MMC����
       LMM_MMC_EMC_BEARER_STATUS_NOTIFY��Ϣ��ָʾ�������ؽ��� */
    if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
    {
        NAS_EMM_SendMmcEmcBearerStatusNotify(VOS_TRUE);
    }

    NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR);

    return ;
}


VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq( VOS_VOID *pstMsg )
{
    VOS_UINT32                          ulRes = NAS_LMM_MSG_HANDLED;
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_ENTRY);

    /* �������*/
    if (NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq: NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_FAIL;
    }
    /*leili modify for isr begin*/
    pstEsmBearerStatusReq               =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    /* ��������л��ģ�յ��ģ����ó��ط������ֱ�ӷ��أ�MML����ά���ĳ���������ȫ�ֱ��������޸ģ�����ģ����ά�� */
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq: LTE CUR SUSPEND");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* L��ģ  */

    /* ����EMM����ά���ĳ���������*/
    NAS_EMM_UpdateEpsBearStatus((VOS_VOID*)pstEsmBearerStatusReq);
    /*leili modify for isr end*/

    /* ����ע��״̬ */
    NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq(pstEsmBearerStatusReq);

    /* ������Ϊ0��ͳһ�ڴ˴��� */
    if (0 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        if (EMM_MS_DEREG != NAS_LMM_GetEmmCurFsmMS())
        {
            /*add by lifuxin for Lnas est process re-construct start*/
            NAS_LMM_EstingOrReleasingProcessTimerHandle();
            /*add by lifuxin for Lnas est process re-construct end*/

            /* �ж�״̬�Ƿ���Ҫ��ջ*/
            NAS_LMM_IfEmmHasBeenPushedThenPop();

            ulRes = NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq();
            return ulRes;
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /* ��������Ϊ0����L����ģ���жϱ��γ��ر仯�����ESM����ִ�У�
       ����Ϣ����״̬�����������������̽��� */
    if (EMM_ESM_BEARER_CNTXT_MOD_LOCAL == pstEsmBearerStatusReq->enBearerCntxtMod)
    {
        return NAS_LMM_MSG_DISCARD;
    }
    else
    {
        return NAS_LMM_MSG_HANDLED;
    }
}


VOS_UINT32 NAS_EMM_SndAttachReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;

    enMainState                         = NAS_LMM_GetEmmCurFsmMS();

    *pulIsDelBuff = VOS_TRUE;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (EMM_MS_REG_INIT != enMainState)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndAttachReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }
    /* ������: ����attach REQ DATA REQ����ʧ�ܴ��� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
        #if (FEATURE_ON == FEATURE_DSDS)
        case LRRC_LMM_SEND_RSLT_NO_RF:
        #endif
            /* ����ATTACH���� */
            /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);

            if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
            {
                NAS_EMM_StartEmergencyAttach();

                return  NAS_EMM_SUCC;
            }

            if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            {
                /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
                NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
            }
            else
            {
                /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
            }

            /* ״̬Ǩ��Dereg.Normal_Service������INTRA_ATTACH_REQ��Ϣ*/
            NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            (VOS_VOID)NAS_EMM_SendIntraAttachReq();

            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;
}
VOS_VOID NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_ENUM_UINT32 enDataCnfRst, VOS_UINT32 ulEsmEmmOpId)
{
    EMM_ESM_DATA_CNF_STRU               *pstEmmEsmDataCnf = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendEsmDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendEsmDataCnf_ENUM,LNAS_ENTRY);

    /*������Ϣ�ڴ�*/
    pstEmmEsmDataCnf   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DATA_CNF_STRU));
    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pstEmmEsmDataCnf)
    {
        return;
    }

    /*����ID_EMM_ESM_DATA_CNF��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pstEmmEsmDataCnf,
                                   (sizeof(EMM_ESM_DATA_CNF_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pstEmmEsmDataCnf->ulMsgId  = ID_EMM_ESM_DATA_CNF;

    /*�����ϢOPID*/
    pstEmmEsmDataCnf->ulEsmEmmOpId = ulEsmEmmOpId;

    pstEmmEsmDataCnf->enDataCnfRst = enDataCnfRst;

    /*��ESM����ID_EMM_ESM_DATA_CNF��Ϣ*/
    NAS_LMM_SEND_MSG(pstEmmEsmDataCnf);
}
VOS_VOID NAS_EMM_RcvLrrcEsmDataCnfHandle(const LRRC_LMM_DATA_CNF_STRU  *pstRrcMmDataCnf, VOS_UINT32 ulEsmEmmOpId)
{
    EMM_ESM_SEND_RSLT_ENUM_UINT32       enEmmEsmDataCnfRst = EMM_ESM_SEND_RSLT_BUTT;
    VOS_UINT32                          ulLoop = 0;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RcvLrrcEsmDataCnfHandle is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcEsmDataCnfHandle_ENUM,LNAS_ENTRY);

    /*������*/
    if(VOS_NULL == pstRrcMmDataCnf)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_RcvLrrcEsmDataCnfHandle(ERR): Input is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RcvLrrcEsmDataCnfHandle_ENUM,LNAS_NULL_PTR);
        return;
    }

    for(ulLoop = 0; ulLoop < g_ulEmmEsmDataCnfTblLen; ulLoop++)
    {
        if(g_astEmmEsmDataCnfTbl[ulLoop].enSendRslt == pstRrcMmDataCnf->enSendRslt)
        {
            enEmmEsmDataCnfRst = g_astEmmEsmDataCnfTbl[ulLoop].enEmmEsmDataCnfRst;
            break;
        }
    }

    /*��ESM����data cnf��Ϣ*/
    if(EMM_ESM_SEND_RSLT_BUTT != enEmmEsmDataCnfRst)
    {
        NAS_EMM_SendEsmDataCnf(enEmmEsmDataCnfRst, ulEsmEmmOpId);
    }
}


VOS_UINT32 NAS_EMM_SndEsmMsgSuccProc(VOS_VOID* pMsg)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = NAS_EMM_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);
    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    NAS_EMM_RcvLrrcEsmDataCnfHandle(pstRrcMmDataCnf, pEmmMrrcMgmtData->ulEsmMmOpId);
    return NAS_EMM_SUCC;
}


VOS_UINT32 NAS_EMM_SndEsmMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    VOS_UINT32                            ulRrcMmDataReqMsgLen;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    /* �ӵ�ǰ״̬���л�ȡ״̬ */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();
    enSubState                          = NAS_LMM_GetEmmCurFsmSS();

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }
    NAS_EMM_RcvLrrcEsmDataCnfHandle(pstRrcMmDataCnf, pEmmMrrcMgmtData->ulEsmMmOpId);

    ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                           pEmmMrrcMgmtData->ulNasMsgLength) -
                           NAS_EMM_4BYTES_LEN;
    /* ������Ϣ�ڴ�*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);

    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SndEsmMsgFailProc: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndEsmMsgFailProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if ((EMM_MS_REG_INIT == enMainState)
                || (EMM_MS_TAU_INIT == enMainState)
                || ((EMM_MS_REG == enMainState)
                    && ((EMM_SS_REG_NORMAL_SERVICE == enSubState)
                        || (EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == enSubState)
                        || (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == enSubState))))
            {
                pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

                pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_ESM;
                pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

                NAS_LMM_MEM_CPY(pMrrcDataMsg->stNasMsg.aucNasMsg,
                                 pEmmMrrcMgmtData->aucNasMsgContent,
                                 pEmmMrrcMgmtData->ulNasMsgLength);

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
            }
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

        default:
            break;
    }

    /*�ͷ��������ڴ� */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/

VOS_VOID NAS_EMM_RestartAttProcedural(VOS_VOID)
{
    /* ����ATTACH���� */
    /* ֹͣ��ʱ��TI_NAS_EMM_T3410 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_StartEmergencyAttach();

        return;
    }

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /* ״̬Ǩ��Dereg.Normal_Service������INTRA_ATTACH_REQ��Ϣ*/
    NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                            EMM_SS_DEREG_NORMAL_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

    /*����ATTACH REQ�ڲ���Ϣ��ATTACHģ��*/
    (VOS_VOID)NAS_EMM_SendIntraAttachReq();

    return ;
}
VOS_VOID NAS_EMM_EsmDataReqRetranSndUplink(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    /* ����OPID��ȡ��������Ϣ */
    pEmmMrrcMgmtData                    = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }

    /* ��Ϣ���� */
    ulRrcMmDataReqMsgLen                = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                            pEmmMrrcMgmtData->ulNasMsgLength) -
                                            NAS_EMM_4BYTES_LEN;

    /* ������Ϣ�ڴ� */
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);
    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        return;
    }

    /* ����Ϣ�ڴ渳ֵ */
    pMrrcDataMsg->enDataCnf             = LRRC_LMM_DATA_CNF_NEED;
    pMrrcDataMsg->enEmmMsgType          = NAS_EMM_MSG_ESM;
    pMrrcDataMsg->ulMsgId               = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pMrrcDataMsg->ulEsmMmOpId           = pEmmMrrcMgmtData->ulEsmMmOpId;
    pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

    NAS_LMM_MEM_CPY(pMrrcDataMsg->stNasMsg.aucNasMsg,
                    pEmmMrrcMgmtData->aucNasMsgContent,
                    pEmmMrrcMgmtData->ulNasMsgLength);


    /* ���·�������ֱ�� */
    NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);

    /* �ͷ��������ڴ� */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
}


VOS_VOID NAS_EMM_EsmDataReqRetranSndService(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData;
    VOS_UINT32                          ulEmmEsmDataReqLen;
    EMM_ESM_DATA_REQ_STRU              *pstEmmEsmDataReq = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_EsmDataReqRetranSndService enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EsmDataReqRetranSndService_ENUM,LNAS_ENTRY);

    /* ����OPID��ȡ��������Ϣ */
    pEmmMrrcMgmtData                    = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }

    ulEmmEsmDataReqLen                  = (sizeof(EMM_ESM_DATA_REQ_STRU)+
                                            pEmmMrrcMgmtData->ulNasMsgLength) -
                                            NAS_EMM_4BYTES_LEN;

    /* ������Ϣ�ڴ� */
    pstEmmEsmDataReq = (EMM_ESM_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulEmmEsmDataReqLen);
    if(VOS_NULL_PTR == pstEmmEsmDataReq)
    {
        return;
    }

    /* ��ֵ���� */
    pstEmmEsmDataReq->ulLength                    = ulEmmEsmDataReqLen - 20;
    pstEmmEsmDataReq->ulMsgId                     = ID_EMM_ESM_DATA_REQ;
    pstEmmEsmDataReq->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstEmmEsmDataReq->ulSenderPid                 = PS_PID_ESM;
    pstEmmEsmDataReq->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstEmmEsmDataReq->ulReceiverPid               = PS_PID_MM;
    pstEmmEsmDataReq->ulIsEmcType                 = pEmmMrrcMgmtData->ulIsEsmMsgEmcType;
    pstEmmEsmDataReq->ulOpId                      = pEmmMrrcMgmtData->ulEsmMmOpId;
    pstEmmEsmDataReq->stEsmMsg.ulEsmMsgSize       = pEmmMrrcMgmtData->ulNasMsgLength;

    NAS_LMM_MEM_CPY(pstEmmEsmDataReq->stEsmMsg.aucEsmMsg,
                    pEmmMrrcMgmtData->aucNasMsgContent,
                    pEmmMrrcMgmtData->ulNasMsgLength);

    NAS_EMM_PUBU_LOG2_INFO( "NAS_EMM_EsmDataReqRetranSndService isEmcType,esmmmopid:",
                            pstEmmEsmDataReq->ulIsEmcType,
                            pstEmmEsmDataReq->ulOpId);
    TLPS_PRINT2LAYER_INFO2( NAS_EMM_EsmDataReqRetranSndService_ENUM,
                            LNAS_FUNCTION_LABEL1,
                            pstEmmEsmDataReq->ulIsEmcType,
                            pstEmmEsmDataReq->ulOpId);


    /* ����SERVICE����ԭ��ֵ */
    if (VOS_TRUE == pstEmmEsmDataReq->ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC);

        /* ����������͵�ESM��Ϣ */
        NAS_EMM_SaveEmcEsmMsg(pstEmmEsmDataReq);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ);
    }

    /* ������:����Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*SERģ�����л���ESM DATA��Ϣ*/
    NAS_EMM_SER_SaveEsmMsg(pstEmmEsmDataReq);

    /*������ʱ��3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    /* �ͷ��������ڴ� */
    NAS_LMM_MEM_FREE(pstEmmEsmDataReq);

}



VOS_VOID NAS_EMM_EsmDataReqRetranProc(VOS_UINT32 ulOpid)
{
    /* �������������̬����������̬��ֱ�ӷ� */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        /* ���·�������ֱ�� */
        NAS_EMM_EsmDataReqRetranSndUplink(ulOpid);
        return;
    }

    /* IDLE̬��Ҫ�ȷ�SERVICE */
    NAS_EMM_EsmDataReqRetranSndService(ulOpid);

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

