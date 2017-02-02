


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasMmlCtx.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMDETACHCNMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMDETACHCNMSGPROC_C
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

VOS_UINT32    NAS_EMM_CnDetachAcpMoMsgChk(                /*�����ʱû��ʹ��, ʹ��LINT���﷨���*/
                                   const NAS_EMM_CN_DETACH_ACP_MO_STRU   *pMsgMsg )
{

    /*��Ϣ���ݼ��*/

    (VOS_VOID)pMsgMsg;
    return  NAS_EMM_PARA_VALID;
}


VOS_UINT32    NAS_EMM_CnDetachReqMtMsgChk(
                                    const NAS_EMM_CN_DETACH_REQ_MT_STRU   *pMsgMsg )
{

    /*��Ϣ���ݼ��*/
    if ((NAS_EMM_DETACH_TYPE_MT_REATTACH == pMsgMsg->ucDetType)
        || (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pMsgMsg->ucDetType)
        || (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pMsgMsg->ucDetType))
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
VOS_VOID NAS_EMM_MsRegSsNmlSrvMsgCnImsiDetachReq()
{
    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
     /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ���UEģʽΪCS/PS������CS��ע�ᣬû�б�ԭ��ֵ2�ܾ���������
       "combined TA/LA updating with IMSI attach"���͵�����TAU */
    if ((NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        && (NAS_EMM_AUTO_ATTACH_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
        && (NAS_EMM_REJ_NO == NAS_LMM_GetEmmInfoRejCause2Flag())
        && (NAS_EMM_REJ_NO == NAS_EMMC_GetRejCause18Flag()))
    {
        /* ����TAU START CAUSE Ϊ CN IMSI DETACH */
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_CN_IMSI_DETACH);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        NAS_EMM_TAU_SetImsiDetachFlag(NAS_EMM_IMSI_DETACH_VALID);

        /* �ж��Ƿ��������Pending*/
        NAS_EMM_TAU_IsUplinkPending();
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_MT_IMSI_DETACH);
    }
    /*PC REPLAY MODIFY BY LEILI END*/
}

VOS_VOID    NAS_EMM_DetDataUpdate(VOS_UINT32 ulDeleteRplmn, VOS_UINT8 ucCnCause)
{
    NAS_MM_TA_STRU                      stTa;

    /* ��ȡ��ǰTA */
    NAS_EMM_GetCurrentTa(&stTa);

    /*����update statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(ulDeleteRplmn);
    /* #13��#15�����, #15��Ҫ�����Ƿ�Ҫ�߽���Forb���� */
    if (NAS_LMM_CAUSE_ROAM_NOT_ALLOW == ucCnCause)
    {
        /* ��Ҫ�ѵ�ǰTA����ʱ�б����޳� */
        NAS_LMM_DelCurrTaFromGradualForbTaList(&stTa);

        NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }
    else if (NAS_LMM_CAUSE_NO_SUITABL_CELL == ucCnCause)
    {
        /* �жϼ�����ʱ�����б��� */
        /* �ж��Ƿ���Ҫ����ROAM Forb�б� */
        if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stTa))
        {
            NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        }

        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }
    else if (NAS_LMM_CAUSE_TA_NOT_ALLOW == ucCnCause)
    {
        NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
        /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    }
    else
    {
        ;
    }
    return;
}


VOS_VOID  NAS_EMM_ProcDetCauseVal2( VOS_VOID )
{
    /* �޷�ֱ�ӽ���DEREG+NORMAL_SERVICE̬����Ϊ��״̬�޷������������
       �ᵼ��DETACH ACCPET��Ϣ�޷����ͣ���������ֱ�Ӹ�RRC����·�ͷţ�����
       ���ܱ�֤DETACH ACCPET�ܹ��������ͣ���ΪLMM�ȸ�RRC������·�ͷ�����
       ���RRC��������ֱ����Ϣ */

    /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
       ��Lģ�������ܷ�������ATTACH������TAU */
    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

    NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;
}
VOS_VOID    NAS_EMM_ProcDetCauseVal3678(VOS_UINT8 ucDetCause)
{
    NAS_EMM_DetDataUpdate(NAS_EMM_DELETE_RPLMN,ucDetCause);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
    return;
}


VOS_VOID    NAS_EMM_ProcDetCauseVal11(VOS_UINT8 ucDetCause)
{
    /*reset attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN,ucDetCause);

    /*Ϊ�ϱ�����״̬,������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}


VOS_VOID    NAS_EMM_ProcDetCauseVal12(VOS_UINT8 ucDetCause)
{
    /*����attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN, ucDetCause);

    /*Ϊ�ϱ�����״̬,������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}


VOS_VOID    NAS_EMM_ProcDetCauseVal13(VOS_UINT8 ucDetCause)
{

    /*����attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN,ucDetCause);

    /*Ϊ�ϱ�����״̬,������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}



VOS_VOID    NAS_EMM_ProcDetCauseVal14(VOS_UINT8 ucDetCause)
{

    /*����attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN,ucDetCause);

    /*Ϊ�ϱ�����״̬,������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}


VOS_VOID    NAS_EMM_ProcDetCauseVal15(VOS_UINT8 ucDetCause)
{

    /*����attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN,ucDetCause);

    /*Ϊ�ϱ�����״̬,������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);


    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}


VOS_VOID    NAS_EMM_ProcDetNoCauseOrOtherCause(VOS_VOID )
{
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_ProcDetNoCauseOrOtherCause enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDetNoCauseOrOtherCause_ENUM,LNAS_ENTRY);

    NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt();

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();
}
VOS_VOID    NAS_EMM_DetCauseValProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucDetCause)
{
    /*���ݲ�ͬԭ��ֵ���д���*/
    switch (ucDetCause)
    {
        case NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
            NAS_EMM_ProcDetCauseVal2();
            break;

        case NAS_LMM_CAUSE_ILLEGAL_UE:
        case NAS_LMM_CAUSE_ILLEGAL_ME:
        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            NAS_EMM_ProcDetCauseVal3678(ucDetCause);
            break;

        case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            NAS_EMM_ProcDetCauseVal11(ucDetCause);
            break;

        case NAS_LMM_CAUSE_TA_NOT_ALLOW:
            NAS_EMM_ProcDetCauseVal12(ucDetCause);
            break;

        case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            NAS_EMM_ProcDetCauseVal13(ucDetCause);
            break;

        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            NAS_EMM_ProcDetCauseVal14(ucDetCause);
            break;

        case NAS_LMM_CAUSE_NO_SUITABL_CELL:
            NAS_EMM_ProcDetCauseVal15(ucDetCause);
            break;

/* CSG������δʵ�֣��յ�REJ #25����CSG��������default�����֧*/

        default:
            NAS_EMM_ATTACH_LOG1_INFO(   "DETACH REQUEST-- OtherCause: ",
                                        ucDetCause);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_DetCauseValProc_ENUM,LNAS_CAUSE_NUMBER,ucDetCause);

            NAS_EMM_ProcDetNoCauseOrOtherCause();
            break;

    }
}
VOS_VOID    NAS_EMM_AppSendDetIndMt
(
   const  NAS_EMM_CN_DETACH_REQ_MT_STRU   *pRcvEmmMsg
)
{
    LMM_MMC_DETACH_IND_STRU              *pDetIndMsg;

    if(NAS_EMM_NULL_PTR == pRcvEmmMsg)
    {
        /*��ӡ����*/
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_AppSendDetIndMt: Input null!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendDetIndMt_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*������Ϣ�ڴ�*/
    pDetIndMsg= (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_DETACH_IND_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if (NAS_EMM_NULL_PTR == pDetIndMsg)
    {
        /*��ӡ����*/
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_AppSendDetIndMt: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendDetIndMt_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*�����Ϣ�ռ�*/
    NAS_LMM_MEM_SET(pDetIndMsg, 0, sizeof(LMM_MMC_DETACH_IND_STRU));


    /*����LMM_MMC_DETACH_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pDetIndMsg,
                                        sizeof(LMM_MMC_DETACH_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pDetIndMsg->ulMsgId                 = ID_LMM_MMC_DETACH_IND;

    /*�����Ϣ����*/
    pDetIndMsg->ulOpId                  = NAS_EMM_OPID_TYPE_DETACH_IND;
    pDetIndMsg->ulDetachType            = MMC_LMM_DETACH_MT;

    pDetIndMsg->bitOpCnReqType          = NAS_EMM_AD_BIT_SLCT;
    pDetIndMsg->ulCnReqType             = pRcvEmmMsg->ucDetType;

    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        NAS_EMM_DETACH_LOG1_NORM("NAS_EMM_AppSendDetIndMt:detach cause =",
                                NAS_EMM_GLO_AD_GetDetEmmCau());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendDetIndMt_ENUM,LNAS_CAUSE_NUMBER,NAS_EMM_GLO_AD_GetDetEmmCau());
        pDetIndMsg->bitOpCnCause    = NAS_EMM_AD_BIT_SLCT;
        pDetIndMsg->ucCnCause       = NAS_EMM_GLO_AD_GetDetEmmCau();
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(                   pDetIndMsg);

    return;
}



VOS_VOID  NAS_EMM_MmcSendDetIndLocal
(
    MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32 ulLocDetType
)
{

    LMM_MMC_DETACH_IND_STRU              *pDetIndMsg;

    /*������Ϣ�ڴ�*/
    pDetIndMsg= (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_DETACH_IND_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if (NAS_EMM_NULL_PTR == pDetIndMsg)
    {
        /*��ӡ����*/
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MmcSendDetIndLocal: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendDetIndLocal_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*�����Ϣ�ռ�*/
    NAS_LMM_MEM_SET(pDetIndMsg, 0, sizeof(LMM_MMC_DETACH_IND_STRU));



    /*����LMM_MMC_DETACH_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pDetIndMsg,
                                        sizeof(LMM_MMC_DETACH_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*�����ϢID*/
    pDetIndMsg->ulMsgId                 = ID_LMM_MMC_DETACH_IND;

    /*�����Ϣ����*/
    pDetIndMsg->ulOpId                  = NAS_EMM_OPID_TYPE_DETACH_IND;
    pDetIndMsg->ulDetachType            = MMC_LMM_DETACH_LOCAL;
    pDetIndMsg->bitOpLocDetType         = NAS_EMM_AD_BIT_SLCT;
    pDetIndMsg->ulLocDetType            = ulLocDetType;

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_LMM_SendLmmMmcMsg(                   pDetIndMsg);

}
VOS_VOID    NAS_EMM_CompCnDetachAcpMt(NAS_EMM_MRRC_DATA_REQ_STRU *pDetAccMtMsg)
{
    VOS_UINT32                          ulIndex             = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pTempDetAccMtMsg      = pDetAccMtMsg;
    VOS_UINT32                          ulDataReqLenNoHeader;


    if (NAS_EMM_NULL_PTR == pDetAccMtMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompCnDetachAcpMt: Mem Alloc Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnDetachAcpMt_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ���Protocol Discriminator + Security header type */
    pTempDetAccMtMsg->stNasMsg.aucNasMsg[ulIndex++]  = EMM_CN_MSG_PD_EMM;

    /* ��� Detach accept message identity   */
    pTempDetAccMtMsg->stNasMsg.aucNasMsg[ulIndex++]  = NAS_EMM_CN_MT_DETACH_ACP_MO;

    /*�ڲ���Ϣ���ȼ���*/
    ulDataReqLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    /*�����Ϣ����*/
    pTempDetAccMtMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pTempDetAccMtMsg, ulDataReqLenNoHeader);

    /*�����ϢID*/
    pTempDetAccMtMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*�����Ϣ����*/
    pTempDetAccMtMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pTempDetAccMtMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pTempDetAccMtMsg->enEmmMsgType             = NAS_EMM_MSG_DETACH_ACP;

    pTempDetAccMtMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    return;
}


VOS_VOID    NAS_EMM_MrrcSendDetAcpMt()
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg;
    NAS_MSG_STRU                        *pstNasMsg;


    /*����С��Ϣ���ȣ�������Ϣ�ڴ�,��Ҫ�ǿ��Ƿ�����пռ�*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC( NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*���췢�������DETACH ACCEPT��Ϣ*/
    NAS_EMM_CompCnDetachAcpMt(pIntraMsg);


    /*��OM���Ϳտ���ϢDETACH REQUEST*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_DETACH_ACP_MT, pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_DETACH_ACP_MT);

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(            pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;

}
VOS_VOID    NAS_EMM_DetCnDetReqNotReattach(
                               const NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg)
{
    (VOS_VOID)pRcvEmmMsg;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_DetCnDetReqNotReattach: is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DetCnDetReqNotReattach_ENUM,LNAS_ENTRY);
    if(NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        /*�ж�ԭ��ֵ,������ԭ��ֵ���в�ͬ����*/
        /*NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));*/

        NAS_EMM_DetCauseValProc(NAS_EMM_GLO_AD_GetDetEmmCau());
    }
    else
    {   /* ��CN��Ϣ��û����дԭ�� */

        /* ��CN��Ϣ��û����дԭ��,ͬԭ��ֵΪ"OTHER"�Ĵ��� */
        NAS_EMM_ProcDetNoCauseOrOtherCause();
    }

}
VOS_VOID  NAS_EMM_ProcNoUsimCnDetReqNotReattach(
                               const NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg)
{
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_ProcNoUsimCnDetReqNotReattach: is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcNoUsimCnDetReqNotReattach_ENUM,LNAS_ENTRY);

    (VOS_VOID)pRcvEmmMsg;

    if(NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        switch(NAS_EMM_GLO_AD_GetDetEmmCau())
        {
            case NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:

                NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

                NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;
                break;
            case NAS_LMM_CAUSE_ILLEGAL_UE:
            case NAS_LMM_CAUSE_ILLEGAL_ME:
            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
            case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
                NAS_EMM_DetDataUpdate(NAS_EMM_DELETE_RPLMN,NAS_EMM_GLO_AD_GetDetEmmCau());
                break;

            case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            case NAS_LMM_CAUSE_TA_NOT_ALLOW:
            case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            case NAS_LMM_CAUSE_NO_SUITABL_CELL:
                 /*reset attach attempt counter*/
                NAS_EMM_AttResetAttAttempCounter();

                NAS_EMM_DetDataUpdate(NAS_EMM_NOT_DELETE_RPLMN,NAS_EMM_GLO_AD_GetDetEmmCau());
                break;
            default:
                NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt();
                break;

        }
    }
    else
    {
        NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt();
    }
    return;
}
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq
                                (NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg)
{

    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq_ENUM,LNAS_ENTRY);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt()  = 0;

    /* �����ܴ���TAU���DETACH����TAU���SERVICE�ĳ�������Ϊ������ڳ�ͻ���������
       ACTIVE��ʶ�������TAU�ɹ��󲻻����ȴ�RRC��·�ͷŵ�״̬ */

    /* 24301 5.3.1�½�ָ����״̬���յ�CN DETACHʱ��Ҫֹͣ3440��ʱ��������CN DETACH��Ϣ��
       upon receipt of a DETACH REQUEST message, the UE shall stop timer T3440
       and respond to the network initiated detach as specified in subclause 5.5.2.3.*/

    /* ����IMSI DETACH���͵�CN DETACH */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq:Process Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgImsiDetachReq(pRcvEmmMsg);

        return  NAS_LMM_MSG_HANDLED;
    }

    /* ����re-attach not required���ͣ�ԭ��ֵΪ#2��CN DETACH */
    if ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
        && (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
        && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq:Process cause2 detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgNotReattach2DetachReq(pRcvEmmMsg);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*����TAUģ���ṩ�ĺ���*/
    NAS_EMM_TAU_AbnormalOver();

    /* ��MMC���� MO DETACH ��� LMM_MMC_TAU_RESULT_IND*/
    /*NAS_EMM_MmcSendTauActionResultIndOthertype(MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE);*/

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_MrrcSendDetAcpMt();

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /*detach type == re-attached required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    return  NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru )
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: NAS_EMM_CN_DETACH_REQ_MT_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    /*������ͷŹ����У�ֱ�Ӷ�������Ϣ*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /*
    ����������ͷŹ����У�����3440�����ţ�˵���������ͷ���·��
    ������ڼ�����������detach����ʱҪ����detach���ͽ�����Ӧ
    ����
    */
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        return NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq(pRcvEmmMsg);
    }

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    if( ! ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
            && (NAS_EMM_AD_BIT_SLCT == pRcvEmmMsg->ucBitOpCause)
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pRcvEmmMsg->ucEmmCause)))
    {
        NAS_EMM_MrrcSendDetAcpMt();
    }
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: Process Imsi Detach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        NAS_EMM_MsRegSsNmlSrvMsgCnImsiDetachReq();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: Process reattach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

        /*״̬Ǩ��,�ȴ��յ�ϵͳ��Ϣ����ATTACH����*/
        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        /* �ж��Ƿ�Ϊԭ��ֵ2 */
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
        {
            NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: Process reattach not required,cause2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL3);

            /* ����ע����ΪPS */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

            /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
               ��Lģ�������ܷ�������ATTACH������TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }
        else
        {
            NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq: Process reattach not required,cause other!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL4);
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
            NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
        }
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    return  NAS_LMM_MSG_HANDLED;
}

/* lihong00150010 emergency tau&service begin */
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq
 Description     : ��״̬REG+��״̬REG_LIMIT_SERVICE���յ����෢�͵�
                   DETACH REQUEST��Ϣ

 Input           :

 Return          :

 History         :
    1.lihong00150010         2012-12-31     Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_ENTRY);

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq: NAS_EMM_CN_DETACH_REQ_MT_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*��ǰ״̬ʱ��·�ͷŹ����У���ֱ�ӷ��أ�������*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    if( ! ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
            && (NAS_EMM_AD_BIT_SLCT == pRcvEmmMsg->ucBitOpCause)
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pRcvEmmMsg->ucEmmCause)))
    {
        NAS_EMM_MrrcSendDetAcpMt();
    }
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq: Process Imsi Detach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq: Process reattach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

        /*״̬Ǩ��,�ȴ��յ�ϵͳ��Ϣ����ATTACH����*/
        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_PLMN_SEARCH,
                                TI_NAS_EMM_STATE_NO_TIMER);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        /* �ж��Ƿ�Ϊԭ��ֵ2 */
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
        {
            NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq: Process reattach not required,cause2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL3);

            /* ����ע����ΪPS */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

            /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
               ��Lģ�������ܷ�������ATTACH������TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }
        else
        {
            NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq: Process reattach not required,cause other!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL4);
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
            NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
        }
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    return  NAS_LMM_MSG_HANDLED;
}
/* lihong00150010 emergency tau&service end */


VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq: NAS_EMM_CN_DETACH_REQ_MT_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    /* IMSI DETACH���͵�CN DETACH����T3411��ʱֱ�ӷ���TAU */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq: Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_MrrcSendDetAcpMt();

        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        NAS_EMM_MsRegSsNmlSrvMsgCnImsiDetachReq();
        return  NAS_LMM_MSG_HANDLED;
    }

    /* ����re-attach not required���ͣ�ԭ��ֵΪ#2��CN DETACH */
    if ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
        && (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
        && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq:Discard cause2 detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_MSG_DISCARD;
    }

    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*������ͷŹ����У�ֱ�Ӷ�������Ϣ*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /*
    ����������ͷŹ����У�����3440�����ţ�˵���������ͷ���·��
    ������ڼ�����������detach����ʱҪ����detach���ͽ�����Ӧ
    ����
    */
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        return NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq(pRcvEmmMsg);
    }
    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_MrrcSendDetAcpMt();

    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /*detach type == re-attached required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-24  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_LMM_INTRA_DETACH_REQ_STRU      *pRcvEmmMsg = NAS_EMM_NULL_PTR;

    pRcvEmmMsg                          = (NAS_LMM_INTRA_DETACH_REQ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG1_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq is entered", ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq_ENUM,LNAS_ENTRY,ulMsgId);

    (VOS_VOID)ulMsgId;

     /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_IntraDetReqChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq: NAS_EMM_IntraDetReqChk err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }
    /* �����IMSI DETACH���ͣ��򱾵�ȥע��CS��ֹͣ��ʱ��3411��3402��ת��REG+NORMAL_SERVICE̬ */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq:Proceed Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
           ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
        if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            NAS_EMM_SetTauTypeNoProcedure();
            NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        }

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        /*ֹͣ��ʱ��*/
        NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

        /*�޸�״̬��������״̬EMM_MS_REG��״̬EMM_SS_REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq:Proceed EPS Detach or EPS/IMSI Detach");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL2);

    /* ���3411�����У���Ҫ��MMC��TAU���������MMC�˳�����״̬����3402��ʱ����
       ��������֪ͨ��MMC�յ�TAU������Դ���Ϊ5ʱ�����˳�����״̬�� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
	/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
	/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
    /*����DETACH REQUEST��Ϣ*/
    NAS_EMM_SendDetachReqMo();

   return   NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMM_ProcNoUsimOfDrgInitMsgCnDetachReq( VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_ProcNoUsimCnDetReqNotReattach(pRcvEmmMsg);
    }

    /*NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);*/
    NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                            EMM_SS_DEREG_NO_IMSI,
                            TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    /* ��MMC�ظ�LMM_MMC_USIM_STATUS_CNF */
    NAS_EMM_SendMmcUsimStatusCnf();

    /* lihong00150010 emergency tau&service begin */
    /* ����ο���ʶ */
    NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;
    /* lihong00150010 emergency tau&service end */

    return;
}
VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq(VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;
    /*����detachȫ�ֱ�������֮���NAS_LMM_DeregReleaseResource����������������ξֲ���������ʱ����*/
    VOS_UINT8                            ucBitOpEmmCauz;
    NAS_EMM_CN_CAUSE_ENUM_UINT8          ucEmmCauz;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;


    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_ENTRY);

    /*check the current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*check the msg content*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq: NAS_EMM_CN_DETACH_REQ_MT_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    if (VOS_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_DETACH_REQ))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq: Send LMM_MMC_DETACH_CNF");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
    }

    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ֪ͨESM�������EHRPD���ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    if( ! ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
            && (NAS_EMM_AD_BIT_SLCT == pRcvEmmMsg->ucBitOpCause)
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pRcvEmmMsg->ucEmmCause)))
    {
        NAS_EMM_MrrcSendDetAcpMt();
    }
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        ucBitOpEmmCauz = NAS_EMM_GLO_AD_OP_GetDetEmmCau();
        ucEmmCauz      = NAS_EMM_GLO_AD_GetDetEmmCau();

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();

        NAS_EMM_GLO_AD_OP_GetDetEmmCau() = ucBitOpEmmCauz;
        NAS_EMM_GLO_AD_GetDetEmmCau()    = ucEmmCauz   ;
        NAS_EMM_ProcNoUsimOfDrgInitMsgCnDetachReq((VOS_VOID*)pRcvEmmMsg);

        return NAS_LMM_MSG_HANDLED;
    }

    ucBitOpEmmCauz = NAS_EMM_GLO_AD_OP_GetDetEmmCau();
    ucEmmCauz      = NAS_EMM_GLO_AD_GetDetEmmCau();

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = ucBitOpEmmCauz;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = ucEmmCauz   ;


    /* lihong00150010 emergency tau&service end */
    /* �����IMSI���͵�CN DETACH�����RRC����RRC_MM_REL_REQ��Ϣ������������״̬�� */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq:Process Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);

        /* �޷�ֱ�ӽ���DEREG+NORMAL_SERVICE̬����Ϊ��״̬�޷������������
           �ᵼ��DETACH ACCPET��Ϣ�޷����ͣ���������ֱ�Ӹ�RRC����·�ͷţ�����
           ���ܱ�֤DETACH ACCPET�ܹ��������ͣ���ΪLMM�ȸ�RRC������·�ͷ�����
           ���RRC��������ֱ����Ϣ */
        NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();

        return  NAS_LMM_MSG_HANDLED;
    }
    /*detach type == re-attached required,will not attach for inside UE detach*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq: Cn Detach Reattach Request!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        /* ʵ��GCF��App������Detach��ͻ�Ĵ��� */
        NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq: Cn Detach Not Reattach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL4);

        NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);

    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);
    return  NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;
    /*����detachȫ�ֱ�������֮���NAS_LMM_DeregReleaseResource����������������ξֲ���������ʱ����*/
    VOS_UINT8                            ucBitOpEmmCauz;
    NAS_EMM_CN_CAUSE_ENUM_UINT8          ucEmmCauz;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq is entered",
                                                    ulMsgId,
                                                    pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_ENTRY,
                                                    ulMsgId,
                                                    pMsgStru);

    /*check the current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*check the msg content*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq: NAS_EMM_CN_DETACH_REQ_MT_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    if (VOS_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_DETACH_REQ))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq: Send LMM_MMC_DETACH_CNF");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
    }

    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    ucBitOpEmmCauz = NAS_EMM_GLO_AD_OP_GetDetEmmCau();
    ucEmmCauz      = NAS_EMM_GLO_AD_GetDetEmmCau();

    /* IMSI DETACH���ͷ���Դ */
    NAS_LMM_ImsiDetachReleaseResource();

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = ucBitOpEmmCauz;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = ucEmmCauz   ;

    /*�޸�״̬��������״̬EMM_MS_REG��״̬EMM_SS_REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                EMM_SS_REG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    if( ! ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
            && (NAS_EMM_AD_BIT_SLCT == pRcvEmmMsg->ucBitOpCause)
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pRcvEmmMsg->ucEmmCause)))
    {
        NAS_EMM_MrrcSendDetAcpMt();
    }
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/

    /* �����IMSI���͵�CN DETACH�����RRC����RRC_MM_REL_REQ��Ϣ������������״̬�� */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq:Process Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);

        if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
        {

            /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
            NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

            /*�ȴ�RRC_REL_IND*/
            NAS_EMM_WaitNetworkRelInd();

            return  NAS_LMM_MSG_HANDLED;
        }
    }

    /*detach type == re-attached required,will not attach for inside UE detach*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq: Cn Detach Reattach Request!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;
    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq: Cn Detach Not Reattach!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL4);

        /* �ж��Ƿ�Ϊԭ��ֵ2 */
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
            && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
        {
            /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
               ��Lģ�������ܷ�������ATTACH������TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

            if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
            {
                /*�ȴ�RRC_REL_IND*/
                NAS_EMM_WaitNetworkRelInd();
            }
        }
        else
        {
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
            NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
        }
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegInitMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegInitMsgCnDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_ENTRY);

    /* �ж���״̬�Ƿ�ΪREG_INIT̬ */
    if (EMM_MS_REG_INIT != NAS_EMM_CUR_MAIN_STAT)
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitMsgCnDetachReq: STATE ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitMsgCnDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    /* ����IMSI DETACH���͵�CN DETACH */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegInitMsgCnDetachReq:Discard Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    if (NAS_RELEASE_R11)
    {
        /* g)Detach procedure collision
        the EMM cause value is not #2 "IMSI unknown in HSS", the detach procedure shall be progressed*/
        if ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType) &&
            (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())      &&
            (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
        {
            NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegInitMsgCnDetachReq:Discard reattach not allowed and cause #2 Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL2);
            return  NAS_LMM_MSG_DISCARD;
        }
    }

    /*detach type == re-attach required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        /* �˷�֧����֪ͨESM���EHRPD���ؼ�¼������ᵼ�³���״̬��һ�� */

        /*���Դ���Ϣ������ATTACH���̣��ȴ�������Ӧ��Ϣ*/
        NAS_EMM_DETACH_LOG_NORM("DETACH REQUEST MESSAGE IS IGNORE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitMsgCnDetachReq_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ֹͣ����ATTACH��ʱ�� */
    NAS_LMM_StopAllAttachTimer();

    /*detach type == re-attach not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        if(EMM_SS_ATTACH_WAIT_ESM_PDN_RSP == NAS_EMM_CUR_SUB_STAT)
        {
            /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
            NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE);
        }
        else
        {
            /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
            NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE);
        }

        NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

        /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
        /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
        if( ! ((NAS_EMM_AD_BIT_SLCT == pRcvEmmMsg->ucBitOpCause)
                && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pRcvEmmMsg->ucEmmCause)))
        {
            NAS_EMM_MrrcSendDetAcpMt();
        }
        /*yanglei 00307272 2015-01-27 for Cn detach issue end*/



        /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
        NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

        /* ֪ͨESM�������EHRPD���ؼ�¼ */
        NAS_EMM_SndEsmClearAllClBearerNotify();

        NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        /*cn detach�ϱ����˳�򲻻�Ӱ��MMC�Ĵ�����˲�����*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

    }

    return  NAS_LMM_MSG_HANDLED;
}

VOS_VOID NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetReqCollisionDetProc(const VOS_UINT32 *pvTauRslt)
{
    /* ��MMC���� MO DETACH ��� LMM_MMC_TAU_RESULT_IND*/
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)pvTauRslt);

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        NAS_EMM_TAU_CollisionDetachProc();

        /*����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();
    }
    else
    {
        /*�޸�״̬��������״̬EMM_MS_REG��״̬EMM_SS_REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        NAS_EMM_TAU_CollisionDetachProc();

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
    }
    return;

}



VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_DETACH_REQ_MT_STRU      *pRcvEmmMsg;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        enTauRslt = MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE;
    /*����detachȫ�ֱ�������֮���NAS_LMM_DeregReleaseResource����������������ξֲ���������ʱ����*/
    VOS_UINT8                            ucBitOpEmmCauz;
    NAS_EMM_CN_CAUSE_ENUM_UINT8          ucEmmCauz;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *)pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    /* ����IMSI DETACH���͵�CN DETACH */
    if (NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq:Discard Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ����re-attach not required���ͣ�ԭ��ֵΪ#2��CN DETACH */
    if ((NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
        && (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
        && (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau()))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq:Discard cause2 detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq_ENUM,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*����TAUģ���ṩ�ĺ���*/
    NAS_EMM_TAU_AbnormalOver();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_MrrcSendDetAcpMt();

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case NAS_EMM_COLLISION_SERVICE:

            /* ��MMC�ϱ�TAU����ڳ�ͻ������ִ�� */
            NAS_EMM_TAU_CollisionServiceProc(NAS_EMM_MmcSendTauActionResultIndOthertype,
                                      (VOS_VOID*)&enTauRslt,
                                      NAS_EMM_TRANSFER_RAT_NOT_ALLOW);

            /* ����ǽ���CSFB����re-attach�����ٷ���ATTACHֱ�������ͷ� */
            if((NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
                && (VOS_FALSE == NAS_EMM_SER_IsNotEmergencyCsfb()))
            {
                NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NORMAL_SERVICE,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /*�ȴ�RRC_REL_IND*/
                NAS_EMM_WaitNetworkRelInd();

                /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
                NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);
                return NAS_LMM_MSG_HANDLED;
            }
            break;

        case NAS_EMM_COLLISION_DETACH:
            ucBitOpEmmCauz = NAS_EMM_GLO_AD_OP_GetDetEmmCau();
            ucEmmCauz      = NAS_EMM_GLO_AD_GetDetEmmCau();

            NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetReqCollisionDetProc(&enTauRslt);

            NAS_EMM_GLO_AD_OP_GetDetEmmCau() = ucBitOpEmmCauz;
            NAS_EMM_GLO_AD_GetDetEmmCau()    = ucEmmCauz   ;
            break;

        default:

            /* ��MMC���� MO DETACH ��� LMM_MMC_TAU_RESULT_IND*/
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&enTauRslt);
            break;

    }

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /*detach type == re-attached required*/
    if (NAS_EMM_DETACH_TYPE_MT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

        /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
        return  NAS_LMM_MSG_HANDLED;

    }

    /*detach type == re-attached not required*/
    if (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType)
    {
        NAS_EMM_DetCnDetReqNotReattach(pRcvEmmMsg);
    }

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pRcvEmmMsg);

   return  NAS_LMM_MSG_HANDLED;
}
VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnImsiDetatchReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_MrrcSendDetAcpMt();

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /*���SR����������SMS����������CS��û��ע�ᣬ��Ҫ�ظ�SMS����ʧ�ܣ��������SR�ķ���ԭ��
      ��ESM����RABM�ȴ�����SR���������*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
     /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ���UEģʽΪCS/PS������CS��ע�ᣬû�б�ԭ��ֵ2�ܾ���������
       "combined TA/LA updating with IMSI attach"���͵�����TAU */
    if ((NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        && (NAS_EMM_AUTO_ATTACH_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
        && (NAS_EMM_REJ_NO == NAS_LMM_GetEmmInfoRejCause2Flag())
        && (NAS_EMM_REJ_NO == NAS_EMMC_GetRejCause18Flag()))
    {
        /*ֹͣT3417��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

        /*ֹͣT3417ext��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        if (VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
        {
            /*Inform RABM that SER fail*/
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
        }

        /*�������̳�ͻ��־λ*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);
        /* lihong00150010 emergency tau&service begin */
        if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        /* lihong00150010 emergency tau&service end */
        NAS_EMM_TAU_SetImsiDetachFlag(NAS_EMM_IMSI_DETACH_VALID);

        /*����TAU Procedure*/
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_MT_IMSI_DETACH);
    }
     /*PC REPLAY MODIFY BY LEILI END*/
}
VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnReAttachDetatchReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    NAS_EMM_SER_AbnormalOver();

    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,Begin */
    NAS_LMM_Stop3402Timer();
    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,End */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /* ��MRRC����DETACH ACCEPT��Ϣ */
    NAS_EMM_MrrcSendDetAcpMt();

    /* CSFB���� */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* ��MMC����LMM_MMC_DETACH_IND��Ϣ */
        NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

        /* ��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();

        return;
    }
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����ATTACH�Ĵ��� */
    NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
    /* ��MMC����LMM_MMC_DETACH_IND��Ϣ */
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    /*�ȴ�RRC_REL_IND*/
    NAS_EMM_WaitNetworkRelInd();

    return;

}



/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetachCause2
 Description     : ��״̬SER_INIT+��״̬ATTACH_WAIT_CN_SER_CNF���յ������
                   ��ϢDETACH REQUEST(reattach not required���ͣ�ԭ��ֵΪ2)

 Input           : pstRcvEmmMsg--------------CN DETACH��Ϣָ��
 Output          : NONE
 Return          : NODE

 History         :
    1.lihong00150010         2012-02-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetachCause2
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    /* ��MRRC����DETACH ACCEPT��Ϣ */
    /*NAS_EMM_MrrcSendDetAcpMt();*/
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/


     /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
       ��Lģ�������ܷ�������ATTACH������TAU */
    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

    /* ����SER����ԭ�������Ӧ���� */
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_USIM_CS_INVALID);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
            break;

        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
            NAS_EMM_SER_AbnormalOver();

            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            /* ��MM����ֹ */
            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL, NAS_LMM_CAUSE_NULL);

            /* ״̬Ǩ�Ƶ�REG.NORMAL_SERVICE*/
            NAS_EMM_AdStateConvert(EMM_MS_REG,
                           EMM_SS_REG_NORMAL_SERVICE,
                           TI_NAS_EMM_STATE_NO_TIMER);

            if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
            {
                /*�ȴ�RRC_REL_IND*/
                NAS_EMM_WaitNetworkRelInd();
            }
            break;


        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:
            NAS_EMM_SER_AbnormalOver();
            NAS_EMM_AdStateConvert(EMM_MS_REG,
                                   EMM_SS_REG_NORMAL_SERVICE,
                                   TI_NAS_EMM_STATE_NO_TIMER);

            /* ��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

            /*�ȴ�RRC_REL_IND*/
            NAS_EMM_WaitNetworkRelInd();
            break;

        default:
            break;
    }

    /* ��MMC����LMM_MMC_DETACH_IND��Ϣ */
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    return;
}
VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnNotReAttachDetatchReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
       ��Lģ�������ܷ�������ATTACH������TAU */
    if ((NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetDetEmmCau())
        &&(NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau()))
    {
        NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetachCause2(pstRcvEmmMsg);

        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
             /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,Begin */
             NAS_LMM_Stop3402Timer();
             /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,End */
             NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
        }
        return;
    }

    /* ����SER_INITģ���ṩ�ĺ��� */
    NAS_EMM_SER_AbnormalOver();
    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,Begin */
    NAS_LMM_Stop3402Timer();
    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,End */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /* ��MRRC����DETACH ACCEPT��Ϣ */
    NAS_EMM_MrrcSendDetAcpMt();

    /* CSFB���� */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /* ������ǽ���CSFB��MM����ֹ��Ϣ */
        if (VOS_TRUE == NAS_EMM_SER_IsNotEmergencyCsfb())
        {
            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
        }
        else
        {
            /* ����CSFB��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        }
    }

    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ���ݲ�ͬԭ��ֵ������Ӧ���� */
    NAS_EMM_DetCnDetReqNotReattach(pstRcvEmmMsg);

    /* ��MMC����LMM_MMC_DETACH_IND��Ϣ */
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    return;

}
VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{

    NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_REQ_MT_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachReqMtMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_GLO_AD_OP_GetDetEmmCau() = pRcvEmmMsg->ucBitOpCause;
    NAS_EMM_GLO_AD_GetDetEmmCau()    = pRcvEmmMsg->ucEmmCause;
    /*ԭ��ֵ����Ҫ�滻�������ͳһ�滻������ԭ��ֵ�����滻���*/
    if ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
         && (NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH == pRcvEmmMsg->ucDetType))
    {
        NAS_LMM_AdaptRegRejCau(&(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }


    NAS_EMM_DETACH_LOG1_INFO("Detach type is:",pRcvEmmMsg->ucDetType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq_ENUM,LNAS_FUNCTION_LABEL1,pRcvEmmMsg->ucDetType);

    NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_DetachErrRecord(pRcvEmmMsg);
    #endif

    switch(pRcvEmmMsg->ucDetType)
    {
        case NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH:

            NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnImsiDetatchReq(pRcvEmmMsg);
            break;

        case NAS_EMM_DETACH_TYPE_MT_REATTACH:

            NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnReAttachDetatchReq(pRcvEmmMsg);
            break;

        case NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH:

            NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnNotReAttachDetatchReq(pRcvEmmMsg);
            break;

        default:
            break;
    }

    return NAS_LMM_MSG_HANDLED;

}
VOS_VOID NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgImsiDetachReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    /* ԭ��ֵ16,17,22�ᵼ��UE����REG+ATTEMPT_TO_UPDATE_MM״̬������״̬��Ŀǰ��
       ����IMSI���͵�CN DETACH */
    if (NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722 == NAS_EMM_GetNormalServiceRelCause())
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgImsiDetachReq:Discard Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgImsiDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ��MMC���� MT DETACH ��� LMM_MMC_TAU_RESULT_IND*/
    /*NAS_EMM_MmcSendTauActionResultIndOthertype(MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE);*/

    /*��MRRC����DETACH ACCEPT��Ϣ*/
    NAS_EMM_MrrcSendDetAcpMt();

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
     /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ���UEģʽΪCS/PS������CS��ע�ᣬû�б�ԭ��ֵ2�ܾ���������
       "combined TA/LA updating with IMSI attach"���͵�����TAU */
    if ((NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        && (NAS_EMM_AUTO_ATTACH_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
        && (NAS_EMM_REJ_NO == NAS_LMM_GetEmmInfoRejCause2Flag())
        && (NAS_EMM_REJ_NO == NAS_EMMC_GetRejCause18Flag()))
    {

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /* ����TAU START CAUSE Ϊ CN IMSI DETACH */
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_CN_IMSI_DETACH);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        NAS_EMM_TAU_SetImsiDetachFlag(NAS_EMM_IMSI_DETACH_VALID);

        /* �ж��Ƿ��������Pending*/
        NAS_EMM_TAU_IsUplinkPending();
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_MT_IMSI_DETACH);
    }
    else
    {
        /* ��ֹTAU���� */
        NAS_EMM_TAU_AbnormalOver();
        /* lihong00150010 emergency tau&service begin */
        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();
        /*NAS_EMM_AdStateConvert( EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/
        /* lihong00150010 emergency tau&service end */
        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        /*�ȴ�RRC_REL_IND*/
        NAS_EMM_WaitNetworkRelInd();
    }
    /*PC REPLAY MODIFY BY LEILI END*/
}


VOS_VOID NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgNotReattach2DetachReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
)
{
    /* ԭ��ֵ16,17,22�ᵼ��UE����REG+ATTEMPT_TO_UPDATE_MM״̬������״̬��Ŀǰ��
       ����reattach not required��ԭ��ֵΪ2��CN DETACH */
    if (NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722 == NAS_EMM_GetNormalServiceRelCause())
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvWaitRrcRelMsgNotReattach2DetachReq:Discard Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgNotReattach2DetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ��ֹTAU���� */
    NAS_EMM_TAU_AbnormalOver();

    /* ��MMC���� MO DETACH ��� LMM_MMC_TAU_RESULT_IND*/
    /*NAS_EMM_MmcSendTauActionResultIndOthertype(MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE);*/

    /*yanglei 00307272 2015-01-27 for Cn detach issue start*/
    /*����detach typeΪre-attach not required��#2ԭ��ֵ�����������MRRC����DETACH ACCEPT��Ϣ*/
    /*��MRRC����DETACH ACCEPT��Ϣ*/
    /*NAS_EMM_MrrcSendDetAcpMt();*/
    /*yanglei 00307272 2015-01-27 for Cn detach issue end*/

    /*��MMC����LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_AppSendDetIndMt(pstRcvEmmMsg);

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /* ���CN DETACH��reattach not required���ͣ�ԭ��ֵΪ2��
       ��Lģ�������ܷ�������ATTACH������TAU */
    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
    /* lihong00150010 emergency tau&service begin */
    NAS_EMM_TranStateRegNormalServiceOrRegLimitService();
    /*NAS_EMM_AdStateConvert(             EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/
    /* lihong00150010 emergency tau&service end */
    /* IMSI DETACH���ͷ���Դ */
    NAS_LMM_ImsiDetachReleaseResource();

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_WaitNetworkRelInd();
    return;
}
VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_DETACH_ACP_MO_STRU       *pRcvEmmMsg;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_ACP_MO_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp is entered",
                                                ulMsgId,
                                                pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_ENTRY,
                                                ulMsgId,
                                                pMsgStru);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachAcpMoMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /* �����ǰ����������̬����ֱ��ת��REG+NORMAL_SERVIC̬��������ͷ�RRC��·
       ����ת��REG+NORMAL_SERVIC̬ */
    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp:data conn");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_AdStateConvert(             EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp:not data conn");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL2);

    NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_DETACH_CNF��Ϣ*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH���ͷ���Դ */
    NAS_LMM_ImsiDetachReleaseResource();

    /* ���������£���������������̬��ʱ����IMSI DETACH�������ڸ�״̬�����ˣ����û�����ݰ��������������ͷ�*/
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_WaitNetworkRelInd();
    }
    else
    {
        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);
    }

    return   NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_DETACH_ACP_MO_STRU       *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (NAS_EMM_CN_DETACH_ACP_MO_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��,���д���ӡ���˳�*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnDetachAcpMoMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ֪ͨESM�������EHRPD���ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        NAS_EMM_ProcLocalNoUsim();
    }/* lihong00150010 emergency tau&service end */
    else
    {
        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    }

    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return   NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMM_ProcDetachAuthRej(VOS_UINT32  ulCause)
{
   NAS_EMM_DETACH_LOG_INFO("NAS_EMM_ProcDetachAuthRej is entered");
   TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDetachAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulCause;


    /*��ֹDETACH����*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

     /*����update statusΪEU3*/
    /* leixiantiao 00258641v 2015-03-15 begin */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*��ESM����ID_EMM_ESM_STATUS_IND��Ϣ*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_DETACH_CNF��Ϣ*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_AUTH_REJ);
    /* lihong00150010 emergency tau&service begin */
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /* ��MMC�ظ�LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();

        /* ����ο���ʶ */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;
    }
    /* lihong00150010 emergency tau&service end */
    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return;

}
VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthRej enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ��Ȩ�ܾ��Ż����� */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ProcDetachAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);


    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej
 Description     : ��״̬EMM_MS_REG+��״̬EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF���յ�AUTH REJ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-09-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej is entered",
                                                ulMsgId,
                                                pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej_ENUM,LNAS_ENTRY,
                                                ulMsgId,
                                                pMsgStru);

    /* ��Ȩ�ܾ��Ż����� */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ProcDetachAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);

    return NAS_LMM_MSG_HANDLED;
}
VOS_VOID  NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd
(
    VOS_UINT32                          ulCause
)
{
    (VOS_VOID)ulCause;

    /*ֹͣ��ʱ��T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* �п����������ͷ�ԭ��ֵ����ɱ���DETACH*/

    /* ����ע����ΪPS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);


    /*upon different cause value, enter different dealing*/
    switch (ulCause)
    {
        case LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ:
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE);
            break;

        case LRRC_LNAS_REL_CAUSE_CONN_FAIL:
            /* NAS_EMM_TAU_SaveEmmTAUStartCause(    NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE); */
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
            break;
        default:
            break;
    }

    /*�޸�״̬��������״̬sREG��״̬EMM_SS_REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                EMM_SS_REG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC����LMM_MMC_DETACH_CNF��Ϣ*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH���ͷ���Դ */
    NAS_LMM_ImsiDetachReleaseResource();

    /*send INTRA_CONN2IDLE_REQ����������״̬*/
    NAS_EMM_CommProcConn2Ilde();
}
VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    LRRC_LMM_REL_IND_STRU              *pMsgRrcRelInd  = (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                          ulCause;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd is entered",
                                                ulMsgId,
                                                pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd_ENUM,LNAS_ENTRY,
                                                ulMsgId,
                                                pMsgStru);
    /*check the input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*check current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*���ԭ��ֵ*/
    ulCause = pMsgRrcRelInd->enRelCause;

    NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(ulCause);

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif









































