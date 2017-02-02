



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "LNasStkInterface.h"
#include    "LmmCssInterface.h"
#include    "NasLmmPubMEntry.h"

#if ( FEATURE_LPP == FEATURE_ON )
#include    "NasEmmSsMsgProc.h"
#endif

/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin */
#include "NasMmlCtx.h"
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, end */

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHCNMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHCNMSGPROC_C
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
NAS_LMM_REJ_CAUSE_PROC_STRU  gstEmmAttRejCauseProcTbl[]=
{
    {NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED,                       NAS_EMM_ProcRejCauseVal5},
    {NAS_LMM_CAUSE_ILLEGAL_UE,                              NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                              NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                      NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,     NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                          NAS_EMM_ProcRejCauseVal11},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                            NAS_EMM_ProcRejCauseVal12},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                          NAS_EMM_ProcRejCauseVal13},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,              NAS_EMM_ProcRejCauseVal14},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                         NAS_EMM_ProcRejCauseVal15},
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,NAS_EMM_ProcRejCauseVal35},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                  NAS_EMM_ProcRejCauseVal42}
};

VOS_UINT32        gstEmmAttRejCauseProcTblLen = sizeof(gstEmmAttRejCauseProcTbl)
                                                / sizeof(NAS_LMM_REJ_CAUSE_PROC_STRU);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/

VOS_UINT32  NAS_EMM_CnAttachAcpMsgChk(const NAS_EMM_CN_ATTACH_ACP_STRU  *pMsgMsg)
{

    NAS_LMM_UEID_STRU                   *pstEmmInfoUeIdAddr = VOS_NULL_PTR;

    /* EPS attach result�Ϸ��Լ��*/
    if ((NAS_EMM_CN_MSG_ATTACH_TYPE_PS != pMsgMsg->ucAttachRst)
       &&(NAS_EMM_CN_MSG_ATTACH_TYPE_PS_CS != pMsgMsg->ucAttachRst))
    {
        return  NAS_EMM_PARA_INVALID;
    }

    /* UEû��GUTI������Ҳû�з���GUTI*/
    pstEmmInfoUeIdAddr =                NAS_LMM_GetEmmInfoUeidAddr();
    if((NAS_EMM_BIT_NO_SLCT == pMsgMsg->ucBitOpGuti)
      &&(NAS_EMM_BIT_NO_SLCT == pstEmmInfoUeIdAddr->bitOpGuti))
    {
        /*����EMM STATUS, ���յ�conditional IE�������Ϣ */
        NAS_EMM_SendMsgEmmStatus( NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR );
        return  NAS_EMM_PARA_INVALID;
    }

    return NAS_EMM_PARA_VALID;

}
VOS_UINT32  NAS_EMM_CnAttachRejMsgChk(const NAS_EMM_CN_ATTACH_REJ_STRU *pMsgMsg)
{

    /*��Ϣ���ݼ�� */

    (VOS_VOID)pMsgMsg;
    return  NAS_EMM_PARA_VALID;


}
/*lint -e960*/
VOS_VOID    NAS_EMM_EsmSendEstCnf (EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ucEstRst)
{
    EMM_ESM_EST_CNF_STRU                 *pEmmEsmEstCnfMsg;


    /*������Ϣ�ڴ�*/
    pEmmEsmEstCnfMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_EST_CNF_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmEsmEstCnfMsg)
    {
        return;
    }

    /*����ID_EMM_ESM_EST_CNF��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(      pEmmEsmEstCnfMsg,
                                        (sizeof(EMM_ESM_EST_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pEmmEsmEstCnfMsg->ulMsgId            = ID_EMM_ESM_EST_CNF;

    /*�����Ϣ����*/
    pEmmEsmEstCnfMsg->ulEstRst           = ucEstRst;

    /*��ESM����ID_EMM_ESM_EST_CNF��Ϣ*/
    NAS_LMM_SEND_MSG(                   pEmmEsmEstCnfMsg);

    return;

}



VOS_VOID    NAS_EMM_EsmSendDataInd (const NAS_EMM_CN_MSGCON_STRU *pstEsmBearerReq)
{
    EMM_ESM_DATA_IND_STRU                *pEmmEsmBearerReqMsg;
    VOS_UINT32                          ulEsmMsgLen;
    VOS_UINT32                          ulDataIndLenNoHeader;


    ulEsmMsgLen                          = pstEsmBearerReq->ulMsgLen;
    ulDataIndLenNoHeader                = NAS_EMM_CountEsmDataIndLen(ulEsmMsgLen);


    /*������Ϣ�ڴ�*/
    if (ulEsmMsgLen < 4)
    {
        pEmmEsmBearerReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DATA_IND_STRU));

    }
    else
    {
        pEmmEsmBearerReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        ulDataIndLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    }

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmEsmBearerReqMsg)
    {
        return;
    }

    /*����ID_EMM_ESM_DATA_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pEmmEsmBearerReqMsg, ulDataIndLenNoHeader);

    /*�����ϢID*/
    pEmmEsmBearerReqMsg->ulMsgId         = ID_EMM_ESM_DATA_IND;

    /*�����Ϣ����*/
    pEmmEsmBearerReqMsg->stEsmMsg.ulEsmMsgSize = pstEsmBearerReq->ulMsgLen;

    NAS_LMM_MEM_CPY(                 pEmmEsmBearerReqMsg->stEsmMsg.aucEsmMsg,
                                        pstEsmBearerReq->aucMsg,
                                        pstEsmBearerReq->ulMsgLen);

    /*��ESM����ID_EMM_ESM_DATA_IND��Ϣ*/
    NAS_LMM_SEND_MSG(                   pEmmEsmBearerReqMsg);

    return;

}
VOS_VOID NAS_LMM_SendCssStartInd
(
    VOS_VOID
)
{
    LMM_CSS_START_IND_STRU             *pstLmmCssStartInd;

    /*������Ϣ�ռ�*/
    pstLmmCssStartInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_CSS_START_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstLmmCssStartInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_EMM_ATTACH_LOG_ERR("LMM_SendCssStartInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendCssStartInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_LMM_MEM_SET( pstLmmCssStartInd, 0, sizeof(LMM_CSS_START_IND_STRU));

    NAS_EMM_COMP_AD_CSS_PS_MSG_HEADER(pstLmmCssStartInd,
                                    (sizeof(LMM_CSS_START_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    pstLmmCssStartInd->ulMsgId = ID_LMM_CSS_START_IND;

    /*������Ϣ���ͺ��� */
    NAS_LMM_SEND_MSG(pstLmmCssStartInd);


    return ;
}


VOS_VOID NAS_LMM_SendCssStopInd
(
    VOS_VOID
)
{
    LMM_CSS_STOP_IND_STRU              *pstLmmCssStopInd;

    /*������Ϣ�ռ�*/
    pstLmmCssStopInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_CSS_STOP_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstLmmCssStopInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_EMM_ATTACH_LOG_ERR("LMM_SendCssStoptInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendCssStopInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_LMM_MEM_SET( pstLmmCssStopInd, 0, sizeof(LMM_CSS_STOP_IND_STRU));

    NAS_EMM_COMP_AD_CSS_PS_MSG_HEADER(pstLmmCssStopInd,
                                    (sizeof(LMM_CSS_STOP_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    pstLmmCssStopInd->ulMsgId = ID_LMM_CSS_STOP_IND;

    /*������Ϣ���ͺ��� */
    NAS_LMM_SEND_MSG(pstLmmCssStopInd);


    return ;
}


VOS_VOID    NAS_EMM_EsmSendStopNotifyInd (VOS_VOID)
{
    EMM_ESM_STOP_NOTIFY_IND_STRU                *pEmmEsmStopNotifyMsg;

    pEmmEsmStopNotifyMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STOP_NOTIFY_IND_STRU));

    /*�ж�����������ʧ�ܴ�ӡ�����˳�*/
    if (NAS_EMM_NULL_PTR == pEmmEsmStopNotifyMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EsmSendStopNotifyInd: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EsmSendStopNotifyInd_ENUM,LNAS_NULL_PTR);
        return;

    }

    /*����ID_EMM_ESM_DATA_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pEmmEsmStopNotifyMsg,
                                    (sizeof(EMM_ESM_STOP_NOTIFY_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pEmmEsmStopNotifyMsg->ulMsgId         = ID_EMM_ESM_STOP_NOTIFY_IND;

    /*��ESM����ID_EMM_ESM_STOP_NOTIFY_IND��Ϣ*/
    NAS_LMM_SEND_MSG(                   pEmmEsmStopNotifyMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_TcSendDataInd
 Description     : ��TC����ID_EMM_ETC_DATA_IND��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TcSendDataInd
(
    const NAS_EMM_CN_MSGCON_STRU       *pstTcMsg
)
{
    EMM_ETC_DATA_IND_STRU               *pEmmTcDataIndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTcMsgLen;
    VOS_UINT32                          ulDataIndLenNoHeader;


    ulTcMsgLen                          = pstTcMsg->ulMsgLen;
    ulDataIndLenNoHeader                = NAS_EMM_CountTcDataIndLen(ulTcMsgLen);


    /*������Ϣ�ڴ�*/
    if (ulTcMsgLen < 4)
    {
        pEmmTcDataIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ETC_DATA_IND_STRU));

    }
    else
    {
        pEmmTcDataIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        ulDataIndLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    }

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmTcDataIndMsg)
    {
        return;
    }

    /*����ID_EMM_ETC_DATA_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_COMP_AD_TC_MSG_HEADER(pEmmTcDataIndMsg, ulDataIndLenNoHeader);

    /*�����ϢID*/
    pEmmTcDataIndMsg->ulMsgId         = ID_EMM_ETC_DATA_IND;

    /*�����Ϣ����*/
    pEmmTcDataIndMsg->stTcMsg.ulTcMsgSize = pstTcMsg->ulMsgLen;

    NAS_LMM_MEM_CPY(                 pEmmTcDataIndMsg->stTcMsg.aucTcMsg,
                                        pstTcMsg->aucMsg,
                                        pstTcMsg->ulMsgLen);

    /*��TC����ID_EMM_ETC_DATA_IND��Ϣ*/
    NAS_LMM_SEND_MSG(                   pEmmTcDataIndMsg);

    /* ��ӡ������Ϣ */
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_TcSendDataInd:NORM:Send ID_EMM_ETC_DATA_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TcSendDataInd_ENUM,LNAS_END);
}


VOS_UINT32  NAS_EMM_CountEsmDataIndLen(VOS_UINT32 ulNasEsmMsgLen)
{
    VOS_UINT32                          ulMsgLen;

    ulMsgLen                          = NAS_EMM_AD_LEN_MSG_ID                      +
                                        NAS_EMM_AD_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  +
                                        (ulNasEsmMsgLen);

    return ulMsgLen;

}
/*****************************************************************************
 Function Name   : NAS_EMM_CountTcDataIndLen
 Description     : ����ID_EMM_ETC_DATA_IND��Ϣ����

 Input           : ulNasTcMsgLen------TC��Ϣ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010         2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CountTcDataIndLen(VOS_UINT32 ulNasTcMsgLen)
{
    VOS_UINT32                          ulMsgLen;

    ulMsgLen                          = NAS_EMM_AD_LEN_MSG_ID                      +
                                        NAS_EMM_AD_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  +
                                        (ulNasTcMsgLen);

    return ulMsgLen;

}


VOS_VOID    NAS_EMM_AttDataUpdate(VOS_UINT32 ulDeleteRplmn)
{

    /*���� EPS update statusΪEU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI*/
    NAS_EMM_ClearGuti();

    /*ɾ��LVR TAI*/
    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }

    /*ɾ��KSIasme*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    if((NAS_LMM_CAUSE_PLMN_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_TA_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_ROAM_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_NO_SUITABL_CELL == NAS_EMM_GLO_AD_GetAttRejCau()))
    {
        /*���ATTACH ATTEMPTING COUNTER������*/
        NAS_EMM_AttResetAttAttempCounter();
    }

    /* ����Ч�İ�ȫ������ֱ���ں����ڲ�д�� */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
    /*����PS LOC��Ϣ*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);

    return;

}


VOS_VOID  NAS_EMM_ProcRejCauseVal2(VOS_VOID)
{

    /*���ATTACH ATTEMPTING COUNTER��TRACKING AREA UPDATING ATTEMPT������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*����EPS UPDATE STAUSΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*������ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(            TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* leixiantiao 00258641v 2015-03-15 begin */
    /* �ϱ�EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}


VOS_VOID    NAS_EMM_ProcRejCauseVal5(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    /*��ESM����ATTACH���*/
    NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    /* ֪ͨIMSA���ٳ���CS�� */

    return;
}


VOS_VOID    NAS_EMM_ProcRejCauseVal3678(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
        NAS_EMM_SndEsmClearAllClBearerNotify();
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    /* ���֮ǰ��¼��attachԭ��ֵ */
    NAS_LMM_ClearEmmInfoMmcAttachReason();

    return;
}
VOS_VOID    NAS_EMM_ProcRejCauseVal11(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;
}
VOS_VOID    NAS_EMM_ProcRejCauseVal12(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    NAS_MM_TA_STRU                      stTa;

    (VOS_VOID)ucRejCauseVal;

    /* ��ȡ��ǰTA */
    NAS_EMM_GetCurrentTa(&stTa);

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;

}
VOS_VOID    NAS_EMM_ProcRejCauseVal13(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    NAS_MM_TA_STRU                      stTa;

    (VOS_VOID)ucRejCauseVal;

    /* ��ȡ��ǰTA */
    NAS_EMM_GetCurrentTa(&stTa);

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    /* ��Ҫ�ѵ�ǰTA����ʱ�б����޳� */
    NAS_LMM_DelCurrTaFromGradualForbTaList(&stTa);

    NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;
}
VOS_VOID    NAS_EMM_ProcRejCauseVal14(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;
}
VOS_VOID    NAS_EMM_ProcRejCauseVal15(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    /* ɾ�����ñ��� */
    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  stLteNoSubsPlmnList;
    VOS_UINT32                               ulIsNeedExecLteNotAllow = NAS_EMM_YES;

    (VOS_VOID)ucRejCauseVal;

    /* ɾ�����ô��� */

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    /* Forb Ta�б�ά���Ƶ�����4Gδ�����жϷ�֧ά�� */

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ��MMC���ͽ�� */
    NAS_EMM_AppSendAttRej();

    /*��15�ܾ�����ǰPLMNֻ��һ��*/
    stLteNoSubsPlmnList.ulPlmnNum = 1;
    /*������ǰPLMN*/
    NAS_LMM_MEM_CPY(&(stLteNoSubsPlmnList.astPlmnId[0]),
                     NAS_LMM_GetEmmInfoPresentPlmnAddr(),
                     sizeof(MMC_LMM_PLMN_ID_STRU));
    /*�������������չԭ��ֵ�����ҵ�ǰ��Ӧֵ��EUTRAN NOT ALLOW������������Э������*/
    if((NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetAttRejEmmExtCau())
        &&(NAS_EMM_EUTRAN_NOT_ALLOWED == NAS_EMM_GLO_AD_GetAttRejEmmExtCau())
        &&(PS_FALSE == NAS_EMM_GetLteNoSubscribeNvConfigDiscardExtCauseFlag()))
    {
        /*��15ԭ��ֵ�ܾ����ҵ�ǰ����չԭ��ֵ��ָʾUSIMδ��LTE��������������LTEδ��������*/
        /*NAS_EMM_SetLteNoSubscribeExtCauseFlag(NAS_EMM_EUTRAN_NOT_ALLOWED);*/
        NAS_LMM_LteNoSubscribeWithExtCauseHandle(&stLteNoSubsPlmnList);

        /* Forb Ta�б�ά�� */
        NAS_LMM_AddTaInForbListWithAttRejCauseVal15(NAS_EMM_YES, &ulIsNeedExecLteNotAllow);
    }
    else
    {
        /* Forb Ta�б�ά��, ���ж��Ƿ�Ҫ��4Gδ�������� */
        NAS_LMM_AddTaInForbListWithAttRejCauseVal15(NAS_EMM_NO, &ulIsNeedExecLteNotAllow);

        /* �ж��Ƿ�Ҫ��4Gδ�������� */
        if (NAS_EMM_YES == ulIsNeedExecLteNotAllow)
        {
            /*��15ԭ��ֵ�ܾ�����û�д���չԭ��ֵ����LTEδ������������*/
            NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(&stLteNoSubsPlmnList);
        }
    }
    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;

}
VOS_VOID  NAS_EMM_ProcRejCauseVal1617(VOS_VOID )
{

    /*����GCFЭ��36523 9.2.1.2.3�½������������ATTACH ATTEMPTING COUNTER��
      TRACKING AREA UPDATING ATTEMPT���������ٶ�TRACKING AREA UPDATING ATTEMPT
      ��������1*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*tracking area updating attempt counter shall be incremented*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt() ++;

     /*����EPS UPDATE STAUSΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*������ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* �ϱ�EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}
VOS_VOID  NAS_EMM_ProcRejCauseVal22(VOS_VOID )
{

     /* ���ó��Դ���Ϊ5 */
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()  = NAS_EMM_TAU_ATTEMPT_CNT_MAX;

    /*��������EU1 */
    NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_UPDATED_EU1;

    /*������ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    return;
}


VOS_VOID  NAS_EMM_ProcRejCauseVal18(VOS_VOID)
{

    /*���ATTACH ATTEMPTING COUNTER��TRACKING AREA UPDATING ATTEMPT������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*����EPS UPDATE STAUSΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*������ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*���������Ӹ���UE����ģʽ���в�ͬ�Ĵ���*/
    /* �ϱ�EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}

VOS_VOID    NAS_EMM_ProcRejCauseVal35(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if (NAS_RELEASE_R10)
    {
        NAS_EMM_ProcRejCauseVal11(ucRejCauseVal);
    }
    else
    {
        NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);
    }
}

VOS_VOID    NAS_EMM_ProcRejCauseVal42(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if (NAS_RELEASE_R11)
    {
        /* ���ó��Դ���Ϊ5 */
        NAS_EMM_GLO_AD_GetAttAtmpCnt()  = 5;

        /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
        /*��������EU2 NOT UPDATED*/
        NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_NOT_UPDATED_EU2;

        /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*��ESM����ATTACH���*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /* ��MMC���ͽ�� */
        NAS_EMM_AppSendAttRej();

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);
    }
    else
    {
        NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);
    }
    return;

}
VOS_VOID    NAS_EMM_ProcRejCauseValOther(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if((NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG == ucRejCauseVal) ||
       (NAS_LMM_CAUSE_INVALID_MANDATORY_INF == ucRejCauseVal)       ||
       (NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == ucRejCauseVal)  ||
       (NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == ucRejCauseVal)  ||
       (NAS_LMM_CAUSE_PROTOCOL_ERROR == ucRejCauseVal)||
       /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
       (VOS_TRUE == NAS_LMM_GetRoamingRejectNoRetryFlg(ucRejCauseVal)))
       /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt()  = 5;
    }
    else if(NAS_LMM_CAUSE_ESM_FAILURE == ucRejCauseVal)
    {
        /* ����AT&T����������AT&T��PLMN���յ�#19ʱ�����������⴦�� */
        if((NAS_EMM_YES == NAS_EMM_IsDamConfitionSatisfied())
            ||(NAS_EMM_YES == NAS_EMM_GetEmmInfoRej19AtmptCntFlag()))
        {
            NAS_EMM_DamAttachRej19CountProc();
        }
        else if(NAS_LMM_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST == NAS_EMM_GLO_AD_GetAttRejEsmCau())
        {
            /*CL multimode ��EMMԭ��ֵΪ#19��ESMԭ��ֵΪ#54ʱattach���Դ�����1 2014-02-14*/
            /* ���֮ǰ�����attachԭ��ֵ */
            NAS_LMM_ClearEmmInfoMmcAttachReason();
            NAS_EMM_GLO_AD_GetAttAtmpCnt() ++;
        }
        else
        {
            NAS_EMM_GLO_AD_GetAttAtmpCnt() = 5;
        }
    }
    else
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt() ++;
    }

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨESM������EMM��Ҫ������ע�ᣬESM����Ҫ�����̬���еĽ���PDN������¼ */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*��ESM����ATTACH���*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    NAS_EMM_ProcRejCauOtherAbnormal();

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* ֪ͨIMSA�ٳ���CS�� */
    }

    return;
}


VOS_VOID    NAS_EMM_RejCauseValProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    VOS_UINT32                          ulIndex = 0;
    NAS_LMM_REJ_CAUSE_PROC_FUN          pfRejCauseProcFun;

    for (ulIndex = 0; ulIndex < gstEmmAttRejCauseProcTblLen; ulIndex++)
    {
        if (ucRejCauseVal == gstEmmAttRejCauseProcTbl[ulIndex].enRejCauseVal)
        {
            pfRejCauseProcFun = gstEmmAttRejCauseProcTbl[ulIndex].pfRejCauseProcFun;

            /* �д����� */
            if (VOS_NULL_PTR != pfRejCauseProcFun)
            {
                (pfRejCauseProcFun)(ucRejCauseVal);
            }
            return;
        }
    }

    /* ����ԭ��ֵ�Ĵ��� */
    NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);

}
VOS_VOID  NAS_EMM_ProcEpsOnlySucc
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcEpsOnlySucc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_ENTRY);

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;
    /*lint -e961*/
    if (NAS_EMM_BIT_SLCT == pstAttAcp->ucBitOpEmmCau)
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProcEpsOnlySucc EmmCause:",pstAttAcp->ucEMMCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_CAUSE_NUMBER,pstAttAcp->ucEMMCause);
        NAS_EMM_ProcEpsOnlyWithCause(pstRcvMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcEpsOnlySucc No EmmCause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_NO_CAUSE);
        NAS_EMM_ProcEpsOnlyNoCause();
    }
    /*lint +e961*/
    return;
}
VOS_VOID  NAS_EMM_ProcEpsOnlyWithCause
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    NAS_EMM_GLO_AD_GetAttRejCau() = pstAttAcp->ucEMMCause;
    NAS_MML_SetOriginalRejectCause(pstAttAcp->ucEMMCause);
    switch (pstAttAcp->ucEMMCause)
    {
        case    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
                NAS_EMM_ProcRejCauseVal2();
                break;

        case    NAS_LMM_CAUSE_CS_NOT_AVAIL:
                NAS_EMM_ProcRejCauseVal18();
                break;
        case    NAS_LMM_CAUSE_PROCEDURE_CONGESTION:
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_ProcRejCauseVal22();
                }
                else
                {
                    NAS_EMM_ProcRejCauseVal1617();
                }
                break;
        default:
                NAS_EMM_ProcRejCauseVal1617();
                break;
    }
    return;
}


VOS_VOID  NAS_EMM_ProcEpsOnlyNoCause( VOS_VOID)
{
    NAS_MML_SetOriginalRejectCause(NAS_LMM_CAUSE_NULL);
    NAS_EMM_ProcRejCauseVal1617();

    return;
}


VOS_UINT32 NAS_EMM_TimerValTransfer(NAS_EMM_TIMER_UNIT_ENUM_UINT8        ucUnit,
                                  VOS_UINT8                           ucTimerVal)
{
    VOS_UINT32                          ulTimerValue = 0;

    switch(ucUnit)
    {
        case NAS_EMM_TIMER_UNIT_2SENDS:
             ulTimerValue = ucTimerVal*2*NAS_EMM_SECOND_TRANSFER_MILLISECOND;
             break;

        case NAS_EMM_TIMER_UNIT_1MINUTE:
             ulTimerValue = ucTimerVal*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;

        case NAS_EMM_TIMER_UNIT_6MINUTES:
             ulTimerValue = ucTimerVal*6*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;

             /*��ʱ��ʱ����Ϊ�㣬���������ö�ʱ��*/
        case NAS_EMM_TIMER_DEACTIVATE:
             ulTimerValue = 0;
             break;

             /*����ֵ����λΪ1min*/
        default:
             ulTimerValue = ucTimerVal*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;
    }

    return ulTimerValue;

}

VOS_VOID NAS_EMM_AttSetLai(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetLai_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpLai == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetLai()      = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_EMM_GLO_AD_GetLaiAddr(),
                                        &pstAttAcp->stLai,
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetLai()   = NAS_EMM_AD_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                NAS_EMM_GLO_AD_GetLaiAddr(),
                                        0,
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    return;
}
VOS_VOID NAS_EMM_AttSetEplms(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetEplms_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpPlmnList == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()   = NAS_EMM_AD_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        &pstAttAcp->stPlmnList,
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }
    else
    {
        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()   = NAS_EMM_AD_BIT_NO_SLCT;

        NAS_LMM_MEM_SET(                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        0,
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }
    return;
}
VOS_VOID NAS_EMM_AttSetMsId(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*��ӡ����*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetMsId_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpMsId == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetMsId()   = NAS_EMM_AD_BIT_SLCT;
        NAS_LMM_MEM_CPY(                NAS_EMM_GLO_AD_GetMsIdAddr(),
                                        &pstAttAcp->stMsId,
                                        sizeof(NAS_EMM_MSID_STRU));
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetMsId()   = NAS_EMM_AD_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                NAS_EMM_GLO_AD_GetMsIdAddr(),
                                        0,
                                        sizeof(NAS_EMM_MSID_STRU));
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveAttachAcpIe
 Description     : �洢ATTACH ACCPET��Я������Ԫ
 Input           : pMsgStru------------ATTACH ACCEPT��Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-02-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveAttachAcpIe
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU         *pRcvEmmMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen = NAS_EMM_NULL;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_ACP_STRU *)pMsgStru;

    /*����ATTACH���*/
    NAS_EMM_GLO_AD_SetAttRslt(pRcvEmmMsg->ucAttachRst);

    /*����T3412 VALUE*/
    ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3412Value.ucUnit,
                                           pRcvEmmMsg->stT3412Value.ucTimerVal);
    NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3412,ulTimerLen);

     /*����TAI LIST*/
    NAS_LMM_MEM_CPY(                    NAS_EMM_GLO_AD_GetTaiListAddr(),
                                        &(pRcvEmmMsg->stTaiList),
                                        sizeof(NAS_EMM_TA_LIST_STRU));

    /*�����µ�TAI List��ͬʱ����ForbTA for Roaming��ForbTA for RPOS*/
    NAS_EMMC_UpdateForbTaList();

    /*��ESM����ACTIVATE DEFAULT EPS BEARER REQUEST��Ϣ*/
    NAS_EMM_EsmSendDataInd(              &(pRcvEmmMsg->stMsgCon));

    /* ATTACH ACPЯ��GUTI,����GUTI��EMM��ȫ�ֱ�����*/
    if(NAS_EMM_BIT_SLCT == pRcvEmmMsg->ucBitOpGuti)
    {
        NAS_EMM_SetGuti(&(pRcvEmmMsg->stGuti));

    }

    /* Location area identification,MS identity,EMM cause,EPLMNS�յ�ATTACH ACCEPT���棬
        ����ATTACH COMPLETE�����ATTACHʧ�ܴӱ��ر���Ķ�ȡ��Я����MMC */

    NAS_EMM_AttSetLai(pMsgStru);

    NAS_EMM_AttSetEplms(pMsgStru);

    NAS_EMM_AttSetMsId(pMsgStru);

    if(pRcvEmmMsg->ucBitOpEmmCau == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetEmmCau() = NAS_EMM_AD_BIT_SLCT;
        NAS_EMM_GLO_AD_GetEmmCau()    = pRcvEmmMsg->ucEMMCause;
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetEmmCau()   = NAS_EMM_AD_BIT_NO_SLCT;
        NAS_EMM_GLO_AD_GetEmmCau()      = 0;
    }

    /*ATTACH ACPЯ��T3402,�޸Ķ�ʱ��ʱ��*/
    if(pRcvEmmMsg->ucBitOpT3402 == NAS_EMM_AD_BIT_SLCT)
    {
        ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3402Value.ucUnit,
                                            pRcvEmmMsg->stT3402Value.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,ulTimerLen);

    }
    else
    {
        /*���ATTACH ACP��Ϣ�в�Я��T3402��Ԫ����ָ�Ĭ��ֵ12min*/
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
    /*ATTACH ACPЯ��T3423,�޸Ķ�ʱ��ʱ��*/
    if(pRcvEmmMsg->ucBitOpT3423 == NAS_EMM_AD_BIT_SLCT)
    {
        ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3423Value.ucUnit,
                                            pRcvEmmMsg->stT3423Value.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);

    }
    else
    {
        /*���ATTACH ACP��Ϣ�в�Я��T3423��Ԫ����ָ�Ĭ��ֵΪT3412ʱ��*/
        NAS_LMM_GetPtlTimerLen(TI_NAS_EMM_PTL_T3412, &ulTimerLen);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);
    }
    /*leili modify for isr end*/

    /*����Emergency number list��ȫ�ֱ�����*/
    NAS_EMM_SetEmergencyList(   pRcvEmmMsg->ucBitOpEmergencyList,
                                &(pRcvEmmMsg->stEmergencyNumList));

    /*����EPS network feature support��ȫ�ֱ�����*/
    NAS_EMM_SetEpsNetFeature(   pRcvEmmMsg->ucBitOpEpsNetFeature,
                                pRcvEmmMsg->ucEpsNetFeature);

    /*����Additional update result��ȫ�ֱ�����*/
    if(EMM_ATTACH_RST_PS == pRcvEmmMsg->ucAttachRst)
    {
        /* ��EPS ONLY�ɹ� ��ulAdditionUpRslt����ΪNAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED */
        NAS_EMM_SetAddUpdateRslt(NAS_EMM_BIT_SLCT, NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED);
    }
    else
    {
        NAS_EMM_SetAddUpdateRslt(   pRcvEmmMsg->ucBitOpAdditionalUpRslt,
                                    pRcvEmmMsg->ulAdditionUpRslt);
    }

    /* lihong00150010 ims begin */
    /* ֪ͨMMC�����������б������Ƿ�֧��IMS VOICE�ͽ��������Լ�LTE��CS������ */
    /* NAS_EMM_SendGmmInfoChangeNotify(); */
    NAS_EMM_SendMmcInfoChangeNotify();
    /*NAS_EMM_SendMmInfoChangeNotify();*/
    /* lihong00150010 ims end */
    /* ����EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();
/* add by lihong00150010 for lpp feature begin */
#if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SndLcsPosCapInfoInd();
#endif
/* add by lihong00150010 for lpp feature end */
}
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_EMM_SaveAttachAcpIe
 Description     : �洢ATTACH ACCPET��Я������Ԫ
 Input           : pMsgStru------------ATTACH ACCEPT��Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-02-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveAttachRejIe
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_ATTACH_REJ_STRU         *pRcvEmmMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen = NAS_EMM_NULL;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_REJ_STRU *)pMsgStru;

     /*ATTACH REJЯ��T3402,��ATTACH REJ��Ϣ�������Ա����ģ��޸Ķ�ʱ��ʱ��*/
    if(pRcvEmmMsg->ucBitOpT3402 == NAS_EMM_AD_BIT_SLCT)
    {
        if (VOS_TRUE == NAS_LMM_GetMsgIsIntegrityFlag())
        {
            ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3402Value.ucUnit,
                                            pRcvEmmMsg->stT3402Value.ucTimerVal);
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,ulTimerLen);
        }
        else
        {
            /*���ATTACH REJ��Ϣ�������ģ���ָ�Ĭ��ֵ12min*/
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
        }

        /* ����T3402ʱ������ԴΪATATCH REJ */
        NAS_LMM_SetT3402Src(NAS_EMM_T3402_SRC_ATTACH_REJ);
    }
}


VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_ATTACH_ACP_STRU         *pRcvEmmMsg;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = VOS_NULL_PTR;
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulAttachAcpCnt = 1;
#endif

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_ACP_STRU *)pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* ���ATTACH ACP��Ϣ���ݲ��Ϸ�,��������Ϣ��ֱ�Ӷ���*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnAttachAcpMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp: NAS_EMM_CN_ATTACH_ACC_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);

    /* ������: ��¼ATTACH ACPʱ�� */
    NAS_LMM_SaveAttachAcpTimeStamp();
    NAS_EMM_ResetRejCauseChangedCounter();

    NAS_EMM_ResetHplmnAuthRejCout();

    /*ֹͣ��ʱ��T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    /* �洢ATTACH ACCPET��Я������Ԫ */
    NAS_EMM_SaveAttachAcpIe(pMsgStru);

    /* �յ�ATTACH ACP����ע��״̬����ΪRCV CN ACP */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP);

    /*���ATTACH ATTEMPTING COUNTER��TRACKING AREA UPDATING ATTEMPT������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /* ����AT&T��������: ATTACH�ɹ����CService���������۽����Σ�PS�����OK */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /*ע��ɹ���ע��ǰ��TAU/SERVICE/DETACHģ���¼����ʷ��Ϣ��Ӧ��Ӱ���������
      ���TAU/service/detach��Դ
    */
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();
    NAS_EMM_Detach_ClearResourse();

    /*����ע���EPS ONLY�ɹ�*/
    if ((MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType()) &&
        (EMM_ATTACH_RST_PS == pRcvEmmMsg->ucAttachRst))
    {
        NAS_EMM_ProcEpsOnlySucc(pMsgStru);
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_EPS_ONLY);
        #endif
    }
    else
    {
        /*����EPS UPDATE STAUSΪEU1*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

        /*������ʱ��TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

        /*�޸�״̬��������״̬REG_INIT��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
        NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                            EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                            TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    }

    /* lihong00150010 emergency tau&service begin */
    /* ���ձ�����������յ�ATTACH ACCEPTʱ�͸���GUTI, LAST VISIT TAI��EUֵ��
       ��д������NV */
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
    NAS_EMM_SetLVRTai(                  &pMmNetInfo->stPresentNetId);

    /* �ж�û�зŵ�����NAS_LMM_WritePsLoc�������������ڽ���ע�ᱻ�ܻ��߳��Դ���
       �ﵽ5��ʱ����Ҫɾ������ ��Э��ֻ�涨�ǽ���ע��ɹ���Ų�д������NV�� */
    if (NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /* lihong00150010 emergency tau&service end */

    /* ������뼼���仯��ʶ�����������������ATTACHʧ�ܵ�ԭ��ֵ
          ��ΪҪô��Ȼת����DEREG̬��ҪôMME�Ѿ���ѯ��UE��������*/
    NAS_EMM_ClearUeRadioAccCapChgFlag();

#if (VOS_OS_VER != VOS_WIN32)
    if(1 == s_ulAttachAcpCnt)
    {
        (VOS_VOID)LDRV_SYSBOOT_STAMPADD("UE attach success",__LINE__);
        s_ulAttachAcpCnt++;
    }
#endif

    return NAS_LMM_MSG_HANDLED;
}


/*lint -e960*/
VOS_VOID    NAS_EMM_SendRejEventToSTK(VOS_UINT8 ucCauseCode,
                      LNAS_STK_UPDATE_TYPE_ENUM_UINT8          enUpdateType)
{
    LNAS_STK_NETWORK_REJECTION_EVENT_STRU       *pEmmNetworkRejectMsg;
    NAS_MM_PLMN_ID_STRU     *pEmmPlmnID;
    NAS_MM_TAC_STRU         *pEmmTac;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SendRejEventToSTK is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendRejEventToSTK_ENUM,LNAS_ENTRY);
    /*������Ϣ�ڴ�*/
    pEmmNetworkRejectMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_STK_NETWORK_REJECTION_EVENT_STRU));

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pEmmNetworkRejectMsg)
    {
        return;
    }

    /*����ID_LNAS_STK_NETWORK_REJECTION_EVENT��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_STK_MSG_HEADER(      pEmmNetworkRejectMsg,
                                        (sizeof(LNAS_STK_NETWORK_REJECTION_EVENT_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pEmmNetworkRejectMsg->ulMsgName = ID_LNAS_STK_NETWORK_REJECTION_EVENT;

    /*�����Ϣ����*/
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.ucCauseCode = ucCauseCode;

    /*�����Ϣplmn*/
    pEmmPlmnID = NAS_LMM_GetEmmInfoPresentPlmnAddr();
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[0] =
                        pEmmPlmnID->aucPlmnId[0];
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[1] =
                        pEmmPlmnID->aucPlmnId[1];
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[2] =
                        pEmmPlmnID->aucPlmnId[2];

    /*�����ϢTAC*/
    pEmmTac = NAS_LMM_GetEmmInfoPresentTacAddr();
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTac    = pEmmTac->ucTac;
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTacCnt = pEmmTac->ucTacCnt;

    /*�����ϢenUpdateAttachType*/
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.enUpdateAttachType = enUpdateType;

    /*��stk����rejection��Ϣ*/
    NAS_LMM_SEND_MSG(pEmmNetworkRejectMsg);

    return;
}
/*lint +e960*/


VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru )
{
    NAS_EMM_CN_ATTACH_REJ_STRU          *pRcvEmmMsg;
    LNAS_STK_UPDATE_TYPE_ENUM_UINT8     uAttachType;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_REJ_STRU *) pMsgStru;

    /*��ӡ����ú���*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_ENTRY);

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*��Ϣ���ݼ��*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnAttachRejMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject: NAS_EMM_CN_ATTACH_REJ_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*ֹͣ��ʱ��T3410*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3410);

    if (NAS_RELEASE_R11)
    {
        /* �洢ATTACH REJЯ������Ԫ */
        NAS_EMM_SaveAttachRejIe(pMsgStru);
    }
    /* ������: ����attach��Rej���� */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ);
    /*����ATTACH�ܾ�ԭ��*/
    NAS_EMM_GLO_AD_GetAttRejCau()       = pRcvEmmMsg->ucCause;
    NAS_EMM_GLO_AD_GetAttRejEsmCau()    = pRcvEmmMsg->ucEsmCause;

    if(NAS_EMM_BIT_SLCT == pRcvEmmMsg->ucBitOpExtCause)
    {
        NAS_EMM_GLO_AD_OP_GetAttRejEmmExtCau() = NAS_EMM_BIT_SLCT;
        NAS_EMM_GLO_AD_GetAttRejEmmExtCau() = pRcvEmmMsg->ucExtendedEmmCause;
    }

    /* �յ�ATTACH REJ����ע��״̬����ΪRCV CN REJ */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ);

    /* ���ݵ�ǰ���������Ƿ��޸�ԭ��ֵ */
    NAS_LMM_AdaptRegRejCau(&NAS_EMM_GLO_AD_GetAttRejCau());

    /* xiongxianghui00253310 modify for ftmerrlog begin */
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_CN_REJ);
    #endif
    /* xiongxianghui00253310 modify for ftmerrlog end   */

    if(pRcvEmmMsg->ucBitOpMsgCon == NAS_EMM_AD_BIT_SLCT)
    {
        /*��ESM������Ϣ*/
        NAS_EMM_EsmSendDataInd(          &(pRcvEmmMsg->stMsgCon));
    }
    switch(NAS_EMM_GLO_GetCnAttReqType())
    {
        case MMC_LMM_ATT_TYPE_EPS_ONLY:
                uAttachType = LNAS_STK_UPDATE_TYPE_EPS_ATTACH;
                break;

        case  MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:
                uAttachType = LNAS_STK_UPDATE_TYPE_COMBINED_ATTACH;
                break;

        default:
                uAttachType = LNAS_STK_UPDATE_TYPE_EPS_ATTACH;
                break;

    }

    /*��ATTACH�����г���rej����rej�¼������STK*/
    NAS_EMM_SendRejEventToSTK(NAS_EMM_GLO_AD_GetAttRejCau(), uAttachType);

    /*�жϾܾ�ԭ��ֵ,���ݲ�ͬԭ��ֵ���д���*/
    NAS_EMM_RejCauseValProc(NAS_EMM_GLO_AD_GetAttRejCau());

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

