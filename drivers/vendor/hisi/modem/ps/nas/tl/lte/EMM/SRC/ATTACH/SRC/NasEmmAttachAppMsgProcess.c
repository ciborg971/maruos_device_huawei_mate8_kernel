


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmTauInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHAPPMSGPROC_C
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


VOS_UINT32  NAS_EMM_AppAttachReqMsgChk(const MMC_LMM_ATTACH_REQ_STRU *pMsgpMsg)
{
    /*��Ϣ���ݼ��*/
    if ((MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pMsgpMsg->ulAttachType) ||
        (MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pMsgpMsg->ulAttachType) ||
        (MMC_LMM_ATT_REQ_TYPE_CS_PS == pMsgpMsg->ulAttachType))
    {
        return  NAS_EMM_PARA_VALID;
    }
    else
    {
        NAS_EMM_SaveAppMsgPara(pMsgpMsg->ulMsgId, pMsgpMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_EMM_PARA_INVALID;
    }
}
VOS_UINT32    NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru)
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq: NAS_EMM_CN_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*���津��ATTACH��ԭ��*/
    NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_APP;

    /* �û�����ATTACH����ΪIMSI��UEģʽΪPS����ֱ�ӻظ�FAILURE ,
       �û�����ATTACH����ΪIMSI��UEģʽΪCS_PS����ʱע��״̬ΪNULL����ֱ�ӻظ�FAILURE ,
       ���ϣ�dereg.normalserive״̬��CS��ATTACH��ֱ�ӻظ�ʧ�� */
    if (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    }

    /*�û�����ATTACH����ΪPS����CS_PS��ֱ�ӷ���ATTACH�����ATTACH��Ϣʱ�ж�ATTACH����*/
    else
    {

        /*��ESM����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
        NAS_EMM_EsmSendPdnConnInd(           NAS_EMM_DEFAULT_CID);

        /*������ʱ��TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_PDN_RSP);

        /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_PDN_RSP*/
        NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                            EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                            TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    }


   return   NAS_LMM_MSG_HANDLED;

}





/*lint -e960*/
VOS_VOID    NAS_EMM_EsmSendPdnConnInd(VOS_UINT32 ulCid)
{
    EMM_ESM_PDN_CON_IND_STRU             *pEmmEsmPdnIndMsg;


    /*������Ϣ�ڴ�*/
    pEmmEsmPdnIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_IND_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmEsmPdnIndMsg)
    {
        return;
    }

    /*����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(      pEmmEsmPdnIndMsg,
                                        (sizeof(EMM_ESM_PDN_CON_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pEmmEsmPdnIndMsg->ulMsgId            = ID_EMM_ESM_PDN_CON_IND;

    /*�����Ϣ����*/
    pEmmEsmPdnIndMsg->ulCId              = ulCid;

    if(MMC_LMM_ATT_REASON_HANDOVER == NAS_LMM_GetEmmInfoMmcAttachReason())
    {
        pEmmEsmPdnIndMsg->enPdnReqType = EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER;
    }
    else
    {
        pEmmEsmPdnIndMsg->enPdnReqType = EMM_ESM_PDN_CON_REQ_TYPE_INITIAL;
    }
    /* ������: ��¼ATTACH����Startʱ�� */
    NAS_LMM_SaveAttachStartTimeStamp();
    /*��ESM����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
    NAS_LMM_SEND_MSG(                   pEmmEsmPdnIndMsg);

    return;


}
VOS_UINT32    NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;
    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;

    (VOS_VOID)ulMsgId;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;
    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;

    (VOS_VOID)ulMsgId;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /* ATTEMPINT TO ATTACH״̬�£���3411��ʱ�󣬻��Զ�����ATTACH��������APP
    ��ATTACH REQ����ATTACH���̣�
    ����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;

}


VOS_UINT32    NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                     VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);

        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;



}
VOS_UINT32    NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*��MMC����ATTACHʧ��*/
    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

    /* ATTACH NEEDED ״̬�£���3402��ʱ�󣬻��Զ�����ATTACH��������APP
    ��ATTACH REQ����ATTACH���̣�
    ����NAS_LMM_MSG_HANDLED��������DISCARD������MMC�ٴ���һ��*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;


  }



VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* �û�����ATTACH����ΪIMSI��UEģʽΪPS����ֱ�ӻظ�FAILURE ,
       �û�����ATTACH����ΪIMSI��UEģʽΪCS_PS����ʱע��״̬ΪNULL����ֱ�ӻظ�FAILURE ,
       ���ϣ�reginit.waitEsmPdnRsp״̬��CS��ATTACH��ֱ�ӻظ�ʧ�� */
    if(MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACHʧ��*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*���Դ���Ϣ*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq IS IGNORE");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_END);

    return  NAS_LMM_MSG_DISCARD;
}


VOS_UINT32    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* �û�����ATTACH����ΪIMSI��UEģʽΪPS����ֱ�ӻظ�FAILURE ,
       �û�����ATTACH����ΪIMSI��UEģʽΪCS_PS����ʱע��״̬ΪNULL����ֱ�ӻظ�FAILURE ,
       ���ϣ�RegInitSsWtCnAttCnf״̬��CS��ATTACH��ֱ�ӻظ�ʧ�� */
    if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
      &&(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode()))
    {
        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*��MMC����ATTACHʧ��*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* �����ȼ����� */
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq  IS NAS_LMM_STORE_LOW_PRIO_MSG");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_END);
    return  NAS_LMM_STORE_LOW_PRIO_MSG;
}
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /* �û�����ATTACH����ΪIMSI��UEģʽΪPS����ֱ�ӻظ�FAILURE ,
       ���ϣ�reginit.WtEsmBearerCnf״̬��CS��ATTACH��ֱ�ӻظ�ʧ�� */
    if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
      &&(NAS_EMM_NO== NAS_EMM_IsCsPsUeMode()))
    {
        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*��MMC����ATTACHʧ��*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq IS NAS_LMM_STORE_LOW_PRIO_MSG");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_END);
    return NAS_LMM_STORE_LOW_PRIO_MSG;
}

VOS_UINT32    NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_DATA_CNF))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    return NAS_LMM_STORE_LOW_PRIO_MSG;

}


VOS_UINT32    NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*UE��������ΪCS����CS_PS,����ģʽ��PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }
    /*UE��������ΪCS����CS_PS,����ģʽ��CS_PS,ע����ΪCS_PS*/

    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*ע����ΪPS*/
    else if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        if( (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
            ||(NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag()))
        {
            NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
            return NAS_LMM_MSG_HANDLED;
        }
        /*����TAU*/
        NAS_EMM_SendIntraTauReq(ID_APP_MM_MSG_TYPE_BUTT,NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {
        return NAS_LMM_MSG_HANDLED;
    }

}



VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);


    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32    NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
            &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {

        /*����APP����*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

}
VOS_UINT32    NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_LIMITED_SERVICE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);


    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32    NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_PLMN_SEARCH))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32    NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*����ģʽ��PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /*ע����ΪCS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*ע����ΪPS*/
    if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        if( (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
            ||(NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag()))
        {
            NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
            return NAS_LMM_MSG_HANDLED;
        }
        /*����TAU*/
        /*���BAR���ܷ����������Է���,�ڲ���Ϣ�����л��жϣ��˴������ж�*/
        NAS_EMM_SendIntraTauReq(ID_APP_MM_MSG_TYPE_BUTT,NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH);
        return NAS_LMM_MSG_HANDLED;
    }

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e960*/


VOS_UINT32    NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU             *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NO_CELL_AVAILABLE))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq: APP_MM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }
    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

}

VOS_UINT32    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* ��ӡ,*/
    NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq: Receive Message APP ATTACH.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_RCV_MSG);


    return NAS_LMM_STORE_LOW_PRIO_MSG;
}
VOS_UINT32    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)(ulMsgId);


    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;

    /* ��ӡ,*/
    NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: Receive Message APP ATTACH.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_RCV_MSG);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: NAS_EMM_CN_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /*��MMC�ظ�Detach Cnf */
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {/* lihong00150010 emergency tau&service end */
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: No USIM");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_EMM_NO_USIM);

        NAS_EMM_ProcLocalNoUsim();
    }
    else
    {
        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    }
    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);


    /*���±����û�����ATTACH����������*/
    NAS_EMM_GLO_SetAttReqType(pRcvEmmMsg->ulAttachType);

    /*CS���attach����ֱ�ӷ���ʧ�� */
    if (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    }

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);


    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*����ģʽ��PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }
    /*����ģʽ��CS_PS*/
    /*ע����ΪCS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*ע����ΪPS*/
    if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*��ӡ������Ϣ*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*����APP����*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*��MMC����ATTACH�ɹ�*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*����������IMSI����CS_ps,����ģʽ��PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /*����������IMSI����CS_ps����ģʽ��CS_PS,ע����ΪCS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*����������IMSI����CS_ps����ģʽ��CS_PS,ע����ΪPS*/
    if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        /* ����TAU�����SERVICE */
        /*ֹͣT3417��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

        /*Inform RABM that SER fail*/
        NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

        /*����SER����*/
        /* NAS_EMM_SER_AbnormalOver();*/

        /*�������̳�ͻ��־λ*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_IMSI_ATTACH);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /*����TAU Procedure*/
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);

        return NAS_LMM_MSG_HANDLED;
    }

    return  NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

