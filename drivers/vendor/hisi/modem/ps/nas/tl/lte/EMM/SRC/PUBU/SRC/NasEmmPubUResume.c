

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmPubUResume.h"
#include "NasEmmPubUSuspend.h"
#include "NasLmmPubMFsm.h"
#include "NasLmmPublic.h"
#include "NasLmmPubMOsa.h"
#include "NasEmmPubUGlobal.h"
#include "NasLmmPubMTimer.h"
#include "MmcLmmInterface.h"
#include "NasEmmcEmmInterface.h"
#include "NasEmmTauInterface.h"
#include "NasEmmMrrcPubInterface.h"
#include "NasEmmAttDetInterface.h"
#include "NasEmmPlmnInterface.h"
#include "NasEmmSecuInterface.h"
#include "NasEmmAttDetInclude.h"

#include "NasEmmTAUProc.h"
#include "NasEmmPlmn.h"
#include "NasEmmPubUGlobal.h"


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

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBURESUME_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBURESUME_C
/*lint +e767*/


/* DCM�������� GU��L���л����жϱ���TA����, ��ʼ��Ϊ�ر� */
VOS_UINT32    g_ulHoIgnoreForbidTaFlag = NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_INVALID;

/* ����CSFB�������� RRC������GU��L����ϵͳ�任TAU����NV����, ��: 1, �ر�: 0
���ܿ���ʱ������RRC������GU��L����ϵͳ�任�󣬵�L�¾�Ҫ����imsi_attach���͵�TAU */
VOS_UINT32    g_ulNasCsfbTauType2Flag = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMM_PUBU_FSMTranState
 Description     :
 Input           :
 Output          :
 Return          :

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_PUBU_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  usMs,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    usTi)
{
    NAS_LMM_FSM_STATE_STRU              EmmStat;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_FSMTranState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_FSMTranState_ENUM,LNAS_ENTRY);

    EmmStat.enFsmId                   = NAS_LMM_PARALLEL_FSM_EMM;
    EmmStat.enMainState               = usMs;
    EmmStat.enSubState                = usSs;
    EmmStat.enStaTId                  = usTi;
    NAS_LMM_StaTransProc(EmmStat);

    /* ������ʱ�� */
    NAS_LMM_StartStateTimer(usTi);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveLrrcResumePara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_SaveLrrcResumePara( const LRRC_LMM_RESUME_IND_STRU  *pLrrcLmmResumeInd )
{
    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_LRRC);
    NAS_EMM_SetResumeDir(pLrrcLmmResumeInd->enRsmDir);
    NAS_EMM_SetResumeType(pLrrcLmmResumeInd->enResumeType);

    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeResumeAddr(),
                    NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    sizeof(NAS_LMM_FSM_STATE_STRU));
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMmcResumePara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveMmcResumePara( VOS_VOID )
{
    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_MMC);

    NAS_LMM_MEM_CPY( NAS_EMM_GetStateBeforeResumeAddr(),
                    NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                    sizeof(NAS_LMM_FSM_STATE_STRU));

    return;
}



VOS_UINT32  NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_RESUME_IND_STRU  *pLrrcLmmResumeInd;

    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    (VOS_VOID)ulMsgId;

    pLrrcLmmResumeInd = (LRRC_LMM_RESUME_IND_STRU *)pMsgStru;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd: DIR = , enResumeType =.",
                        pLrrcLmmResumeInd->enRsmDir,
                        pLrrcLmmResumeInd->enResumeType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_RESUME_DIR,
                        pLrrcLmmResumeInd->enRsmDir);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        pLrrcLmmResumeInd->enResumeType);

    /* ��¼RESUME���� */
    NAS_EMM_SaveLrrcResumePara(pLrrcLmmResumeInd);

    /* ����ESM, ERABM */
    NAS_EMM_SendEsmResumeInd();
    NAS_EMM_SendErabmResumeInd();

    /* ״̬Ǩ�� */
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_RESUME,
                                EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
                                TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER);

    /* ��ǰ�� LTEΪ����̬ */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;
    if(LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE > pLrrcLmmResumeInd->enResumeType)
    {
        /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

        /* ɾ����ǰС�� */
        NAS_EMMC_DeleteCurrentAreaCellId();
    }

    /* �ж������HO���͵�resume,�����ӳ�䰲ȫ�����Ĳ����ı�־*/
    if(LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmResumeInd->enResumeType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
        NAS_EMM_SecuSetInterRatHoNotMapped();

        /*��GU->L���л��������Ƚ�L����·״̬�л�Ϊ��������̬�����ڴ�������յ���RABM DRB��������Ϣ */
        NAS_EMM_ChangeRrcConnStateToEstSignal();

        /* ֹͣT3412��T3423��ʱ��*/
        NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_T3412);
        NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_T3423);

        /*leili modify for isr begin*/

        /*֪ͨGUģT3412ֹͣ*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_STOP);

        /*֪ͨGUģT3423ֹͣ*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_STOP);

        /*leili modify for isr end*/
    }

    /*leili modify for isr begin*/

    /*RESEL/HO/REDIR:Lģ�յ�RESUME��Ϣ�����Ϊ�ù��̽�����������˵�GUģ*/
    if ((LRRC_LMM_SYS_CHNG_TYPE_RESEL == pLrrcLmmResumeInd->enResumeType) ||
        (LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmResumeInd->enResumeType) ||
        (LRRC_LMM_SYS_CHNG_TYPE_REDIR == pLrrcLmmResumeInd->enResumeType))
    {
        if (EMM_MS_REG != NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
            return NAS_LMM_MSG_HANDLED;
        }
        NAS_EMM_ProcInterSystemTransferBearerInfo();
    }
    /*CCO���̵ȴ�����TAU�����ɹ������Ϊ�ù��̽���:����ISR�������أ����CCO�ɹ�
       ȥ����ISR�����³��ص�ISR��ʶ�����CCOʧ�ܲ�ȥ����ISR*/
    if (LRRC_LMM_SYS_CHNG_TYPE_CCO == pLrrcLmmResumeInd->enResumeType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:CCO TYPE.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_CCO_TYPE);
        if (EMM_MS_REG != NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
            return NAS_LMM_MSG_HANDLED;
        }
        if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()) &&
            (NAS_EMM_SUCC == NAS_EMM_IsBearIsrActAfter()))
        {
            NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_VALID);
            NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_RAT_RELATED_TMSI);
            NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        }
    }
    /*leili modify for isr end*/
    return NAS_LMM_MSG_HANDLED;

}


/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcResumeInd( VOS_VOID )
{
    LMM_MMC_RESUME_IND_STRU           *pstMmcSuspendIndMsg;

    /* ����MMC�ڲ���Ϣ */
    pstMmcSuspendIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendIndMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendMmcResumeInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcResumeInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcSuspendIndMsg, 0, sizeof(LMM_MMC_RESUME_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_RESUME_IND_STRU));

    /* �����ϢID */
    pstMmcSuspendIndMsg->ulMsgId        = ID_LMM_MMC_RESUME_IND;

    /* �����Ϣ�� */
    pstMmcSuspendIndMsg->ulOpId         = NAS_EMM_OPID_MMC;

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendIndMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SendEsmResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendEsmResumeInd( VOS_VOID )
{
    EMM_ESM_RESUME_IND_STRU           *pstEsmResumeIndMsg;

    /* ����DOPRA��Ϣ */
    pstEsmResumeIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstEsmResumeIndMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstEsmResumeIndMsg, 0, sizeof(EMM_ESM_RESUME_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmResumeIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_RESUME_IND_STRU));

    /* �����ϢID */
    pstEsmResumeIndMsg->ulMsgId        = ID_EMM_ESM_RESUME_IND;


    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstEsmResumeIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendErabmResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendErabmResumeInd( VOS_VOID )
{
    EMM_ERABM_RESUME_IND_STRU           *pstLrabmResumeIndMsg;

    /* ����DOPRA��Ϣ */
    pstLrabmResumeIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstLrabmResumeIndMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrabmResumeIndMsg, 0, sizeof(EMM_ERABM_RESUME_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_ERABM_MSG_HEADER((pstLrabmResumeIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ERABM_RESUME_IND_STRU));

    /* �����ϢID */
    pstLrabmResumeIndMsg->ulMsgId        = ID_EMM_ERABM_RESUME_IND;
    pstLrabmResumeIndMsg->enSysChngType  = NAS_EMM_GetResumeType();


    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrabmResumeIndMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendLrcResumeRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SendLrcResumeRsp( VOS_VOID)
{
    LRRC_LMM_RESUME_RSP_STRU           *pstLrrcResumeRspMsg;

    /* ����DOPRA��Ϣ */
    pstLrrcResumeRspMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_RESUME_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcResumeRspMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrrcResumeRspMsg, 0, sizeof(LRRC_LMM_RESUME_RSP_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcResumeRspMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_RESUME_RSP_STRU));

    /* �����ϢID */
    pstLrrcResumeRspMsg->enMsgId       = ID_LRRC_LMM_RESUME_RSP;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrrcResumeRspMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_NoCellSuspendMsgMmcPlmnReq
 Description     : ����ǰ�� LTEΪ����̬�����ESM��ERABM֪ͨ�������ΪLTE����̬
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-5  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_NoCellSuspendMsgMmcPlmnReq( VOS_VOID )
{
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

    /* ����ǰ�� LTEΪ����̬�����ESM��ERABM֪ͨ�������ΪLTE����̬ */
    if( (   (NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
           ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_NO_CELL_AVAILABLE))
         )
         && (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
       )
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_NoCellSuspendMsgMmcPlmnReq: LTE SUSPEND. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NoCellSuspendMsgMmcPlmnReq_ENUM,LNAS_EMM_LTE_SUSPEND);

        /* ��ǰ�� LTEΪ����̬ */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* ��¼RESUME���� */
        NAS_EMM_SaveMmcResumePara();

        /*leili modify for isr begin*/
        /*ȥ����ISR������ڻ�ȡ��ȫ����֮ǰ�����򣬻�ȡ������ȷ�İ�ȫ����*/
        NAS_EMM_ProcInterSystemTransferBearerInfo();
        /*leili modify for isr end*/

        /* ����״̬��Ϊ����̬ */

        /* ��TIN ==  PTMSI�����ȡGU�İ�ȫ���� */
        NAS_EMM_MmcRsmGetSecuPara();

        /* ����ESM, ERABM */
        NAS_EMM_SendEsmResumeInd();
        NAS_EMM_SendErabmResumeInd();

        /* �������ϲ�����PLMN ID����Ϣ���������פ������Ҫ�ϱ�location info */
        /* ɾ����ǰС�� */
        NAS_EMMC_DeleteCurrentAreaCellId();
        /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

        if(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        {
             /* �����ǰΪע��̬���ҵ�ǰֻ��L���뼼������TINΪPTMSIʱ����LOCAL DETACH��
                �������յ�ϵͳ��Ϣʱһ������ATTACH */
            if ((MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
                &&(NAS_LMM_SUCC ==  NAS_EMM_lteRatIsOnlyExist()))
            {

                NAS_EMM_LocalDetachProc();
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
                #endif

                /* ��״̬ת����MS_DEREG + SS_DEREG_PLMN_SEARCH״̬ */
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                            EMM_SS_DEREG_PLMN_SEARCH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

                return NAS_LMM_MSG_HANDLED;
            }

        }

        /* ��״̬ת����MS_RESUME + SS_RESUME_MMCORI_WAIT_SYS_INFO״̬ */
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_RESUME,
                                        EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_DISCARD;
}


/*****************************************************************************
 Function Name   : NAS_EMM_NoImsiSuspendMsgMmcPlmnReq
 Description     : ����ǰ�� LTEΪ����̬�����ESM��ERABM֪ͨ�������ΪLTE����̬
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-5  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_NoImsiSuspendMsgMmcPlmnReq( VOS_VOID )
{
    /* ����ǰ�� LTEΪ����̬�����ESM��ERABM֪ͨ�������ΪLTE����̬ */
    if(     (NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
         && (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
       )
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_NoImsiSuspendMsgMmcPlmnReq: LTE SUSPEND. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NoImsiSuspendMsgMmcPlmnReq_ENUM,LNAS_EMM_LTE_SUSPEND);

        /* ��ǰ�� LTEΪ����̬ */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* ��¼RESUME���� */
        NAS_EMM_SaveMmcResumePara();

        /* ����״̬��Ϊ����̬ */


        /* ����ESM, ERABM */
        NAS_EMM_SendEsmResumeInd();
        NAS_EMM_SendErabmResumeInd();
        /* ת�Ƶ�EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND״̬ */
        NAS_EMM_PUBU_FSMTranState(EMM_MS_RESUME,
                                  EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
                                  TI_NAS_EMM_STATE_NO_TIMER);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcRsmGetSecuPara
 Description     : MMC�ָ�LTEʱ����ȡGU�İ�ȫ����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-5-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcRsmGetSecuPara( VOS_VOID )
{
    MMC_LMM_PUB_INFO_STRU           stTin;
    MMC_LMM_RESULT_ID_ENUM_UINT32   ulRst;
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ulRst = NAS_EMM_GetGulPubInfo(MMC_LMM_TIN_TYPE, &stTin);
    if(MMC_LMM_FAIL == ulRst)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MmcRsmGetSecuPara: NAS_EMM_GetGulPubInfo rst = ",
                                ulRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcRsmGetSecuPara_ENUM,LNAS_FUNCTION_LABEL1,ulRst);
        return;
    }
    /*PC REPLAY MODIFY BY LEILI END*/

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MmcRsmGetSecuPara:  ulTinType = ",
                            stTin.u.ulTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcRsmGetSecuPara_ENUM,LNAS_EMM_TIN_TYPE,
                            stTin.u.ulTinType);

    if(MMC_LMM_TIN_P_TMSI == stTin.u.ulTinType)
    {
        NAS_EMM_SecuResumeIdle();
    }

    return;
}


VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    VOS_UINT32                          ulRst;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd_ENUM,LNAS_ENTRY);

    /* ֹͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    /* ����ʱ���ֻ��˵Ĵ���ʹ�GU������RESUME��ȫ��ͬ */
    ulRst = NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd(ulMsgId, pMsgStru);

    return ulRst;

}


VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_SECU_PARA_IND_STRU        *pstLrrcSecuParaInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    /* ��ȡ LRRC_LMM_SECU_PARA_IND��Ϣ*/
    pstLrrcSecuParaInd = (LRRC_LMM_SECU_PARA_IND_STRU *)pMsgStru;

    /* ���LMM�����ڹ���̬���򱨴�*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd:sta err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* ���� secu ģ��ĺ��������� current mapped secu context������*/
    NAS_EMM_SecuRrcSecuParamIndHo(pstLrrcSecuParaInd->aucSecuPara);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_REL_IND_STRU              *pLrrcRelInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_ENTRY);

    pLrrcRelInd = (LRRC_LMM_REL_IND_STRU *)pMsgStru;

    /* ����ͷ�ԭ��ֵ,��������л�ʧ�ܣ���Ӧ���� L->GU�� HO��CCO �ɹ� */
    if(LRRC_LNAS_REL_CAUSE_GU2L_HO_ERR != pLrrcRelInd->enRelCause)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd: enRelCause = , .",
                                pLrrcRelInd->enRelCause );
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_REL_CAUSE,
                                pLrrcRelInd->enRelCause );

        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd: SuspendType = , ResumeType = .",
                                NAS_EMM_GetSuspendType(),
                                NAS_EMM_GetResumeType() );
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_SUSPEND_TYPE,
                                NAS_EMM_GetSuspendType());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_RESUME_TYPE,NAS_EMM_GetResumeType());

        return NAS_LMM_MSG_HANDLED;
    }

    /* �ͷ�ԭ��ֵ������л�ʧ�ܣ��ָ���ȫ������ */
    /* ���� secu ģ�麯�����ָ���ȫ������״̬*/
    NAS_EMM_SecuRrcRelIndHoFail();

    return NAS_LMM_MSG_HANDLED;

}
VOS_UINT32  NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp_ENUM,LNAS_ENTRY);

    NAS_EMM_GetUplayerCount()++;

    if(NAS_EMM_RESUME_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {

        /* ͣ��ʱ�� */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER);

        /* ����˴ι�����ϲ���Ӧ��¼��Ϊ��һ�ι��������׼�� */
        NAS_EMM_GetUplayerCount() = NAS_EMM_RESUME_UPLAYER_NUM_INITVALUE;

        /* ��MMC���ͻָ� */
        NAS_EMM_SendMmcResumeInd();

        /* RESUME�����ı�����״̬:
        REVERSE���͵ģ�����REVERSEǰ������״̬��
        ��GU�����ģ���ѡ���ض���: ����IDLE��
                     �л�: �ȴ�LRRC���Զ���������Ϣ��ֱ�ӽ�������״̬����
                            �յ�REL_IND��Ϣ��
                     CCO: LNAS��������������ʱ������״̬ */
        /*NAS_EMM_ResumeConnStateChng(); */

        /* �����HO_REVERSE/CCO_REVERSE����Ҫ����ȫ״̬�ָ�Ϊ����̬*/
        if((NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
         ||(NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType()))
        {
            NAS_EMM_SecuHoOrCcoReverse();
        }

        /* ��LRRC��Ӧ */
        NAS_EMM_SendLrcResumeRsp();

        /* ��״̬: ���ۻ��ˣ�����GU->L�����Ƚ����ϵͳ��Ϣ��״̬��
        �ڵ�ϵͳ��Ϣ��״̬�£��ڴ���ϵͳ��Ϣ��REL��Ϣ��������Ϣʱ��
        �ٸ���RESUME�����͡���Ϣ���ͣ��������˺��״̬��*/

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_RESUME,
                                    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
                                    TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    }


    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgWtOtherTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ����˴ι�����ϲ���Ӧ��¼��Ϊ��һ�ι��������׼�� */
    NAS_EMM_GetUplayerCount() = NAS_EMM_RESUME_UPLAYER_NUM_INITVALUE;

    /* ��λ����*/
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_RESUME_ECM_FAIL);

    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_PreProcSysWhenResumingReverse(
                            const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    /* ͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    /* �ж�RESUME�����������REVERSE���ͣ���ֱ�ӷ��أ���������״̬������*/
    if((NAS_LMM_SYS_CHNG_TYPE_RSL   == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_HO    == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_CCO   == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysWhenResumingReverse:NOT REVERSE. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysWhenResumingReverse_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* û��ִ�������֧����RESUME����ΪREVERSE����������������Ҫ�ͷ�����:
       1)С������
       2)����IDLE̬��
       3)������Emergency Bearer*/

    /* Ȼ�����ֲ�ͬ�Ļ������ͣ����в�ͬ����*/
    switch(NAS_EMM_GetResumeType())
    {
        /* ���ResumeType���������ѡ���ˣ���������:
           1)����ǰ��״̬ΪDereg.Attach_Needed��״̬�ָ�ΪDereg.Attach_Needed��
             ����״̬����������
           2)����ǰ��״̬ΪReg.WtAccessGrantInd������BarProcedure����ͬ����
             ���ٽ���״̬��
           3)����״̬Ǩ�Ƶ�Dereg.No_Cell_Available;Reg.No_Cell_Available����Dereg.No_Imsi,
             ����״̬����������
        */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
                ulRslt = NAS_EMM_PreProcSysInfoReselReverse(pstsysinfo);
                break;

        /*���ڹ�������з���ѡ���˵ĳ������յ�RESUME�󣬼����յ�SYS��Ҫ���ݹ���ǰ
        ��״̬��ת�������˵���״̬��Ȼ���ٽ���״̬��������ʼ��׼��LTE���� */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                ulRslt = NAS_EMM_PreProcSysInfoHoAndCcoReverse(pstsysinfo);
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                ulRslt = NAS_LMM_MSG_DISCARD;
                break;

        default :
                NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PreProcSysWhenResumingReverse:ResumeType err. ");
                TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcSysWhenResumingReverse_ENUM,LNAS_ERROR);
                break;
    }

    return  ulRslt;
}



VOS_VOID  NAS_EMM_ReverseStateChng( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ReverseStateChng: CurState = ",
                            NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReverseStateChng_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefSuspend());

    /* ���ݼ�¼�� staBeforeSuspend Ǩ��״̬*/
    if(( EMM_MS_REG == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_TAU_INIT == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_SER_INIT == NAS_EMM_GetMsBefSuspend()))
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}
VOS_VOID  NAS_EMM_ReverseStateChngAsPlmnInd( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ReverseStateChng: CurState = ",
                            NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReverseStateChngAsPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefSuspend());

    /* ���ݼ�¼�� staBeforeSuspend Ǩ��״̬*/
    if(( EMM_MS_REG == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_TAU_INIT == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_SER_INIT == NAS_EMM_GetMsBefSuspend()))
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}
VOS_UINT32  NAS_EMM_PreProcSysInfoReselReverse(
                                   const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    VOS_UINT32                          ulEmmStaBeforeSuspend = 0;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_HANDLED;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_ENTRY);

    /* ��ȡ����ǰ��״̬*/
    ulEmmStaBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_GetMsBefSuspend(),
                                                      NAS_EMM_GetSsBefSuspend());

    /* ���ݹ���ǰ��״̬����ͬ����*/
    switch(ulEmmStaBeforeSuspend)
    {
        /* ����ǰ��״̬ΪDereg.Attach_Needed������С���Ƿ񱻽�����MMC�ϱ�ATTACH
           ��������ٽ���״̬������
         */
        case NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_DEREG,
                                        EMM_SS_DEREG_ATTACH_NEEDED):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Dereg.Attach_Needed");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_EMM_ATTACH_NEEDED);
             /* �ж�ϵͳ��Ϣ�����������Ǩ�Ƶ����Ʒ���*/

            if((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
                || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
            {
                /* ״̬Ǩ��: Reg.Limite_Service*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_DEREG,
                                                EMM_SS_DEREG_LIMITED_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                NAS_EMM_SetAttType();

                /*��MMC����ATTACH���*/
                NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
            }
            else
            {
                /*EMM��ǰ״̬Ǩ�Ƶ�DEREG.ATTACH_NEEDED*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_DEREG,
                                                EMM_SS_DEREG_ATTACH_NEEDED,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                /*��MMC����ATTACH���*/
                NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

            }
            ulRslt = NAS_LMM_MSG_HANDLED;
            break;

        /* ����ǰ��״̬ΪReg.WtAccessGrantInd,�����겻�ٽ���״̬��  */
        case NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG,
                                        EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Reg.WtAccessGrantInd");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_FUNCTION_LABEL1);

            /* �ж�ϵͳ��Ϣ�����������Ǩ�Ƶ����Ʒ���*/
            if((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
                 || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
            {
                NAS_EMM_SetTauTypeNoProcedure();

                /* ���Bar��Ϣ*/
                NAS_EMM_ClearBarResouce();

                /* ״̬Ǩ��: Reg.Limite_Service*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                                EMM_SS_REG_LIMITED_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);

            }
            else
            {
                /* ϵͳ��Ϣ������������REG̬�½�Bar�Ĺ�������*/
                NAS_EMM_RegBarCommProc();

                /* ���������������EMM��ǰ��״̬��Ȼ����Resume.RrcOriWtSysInfo,
                   ��˵��û�д����κ����̣���Ҫ��MMC�ϱ����������״̬Ǩ�Ƶ�
                   Reg.WtAccessGrantInd״̬����֮�����BarProcedure
                */
                if((EMM_MS_RESUME                           == NAS_LMM_GetEmmCurFsmMS())
                 &&(EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND  == NAS_LMM_GetEmmCurFsmSS()))
                {
                    NAS_EMM_SetTauTypeNoProcedure();

                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                                EMM_SS_REG_WAIT_ACCESS_GRANT_IND,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                    ulTauRslt = MMC_LMM_TAU_RSLT_ACCESS_BARED;
                    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


                }
            }

            ulRslt = NAS_LMM_MSG_HANDLED;
            break;

        /* ����״̬,Ǩ��״̬�󣬼�������״̬������*/
        default:
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Others.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_ReverseStateChng();
            ulRslt = NAS_LMM_MSG_DISCARD;
            break;
    }

    return ulRslt;
}
VOS_UINT32  NAS_EMM_PreProcSysInfoHoAndCcoReverse(
                                   const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{/* lihong00150010 emergency tau&service begin */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoHoAndCcoReverse is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoHoAndCcoReverse_ENUM,LNAS_ENTRY);
    if(((EMMC_EMM_NO_FORBIDDEN  != pstsysinfo->ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
        &&(NAS_EMM_CONN_IDLE   != NAS_EMM_GetConnState())
        &&(NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {/* lihong00150010 emergency tau&service end */
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                            EMM_SS_REG_LIMITED_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SetTauTypeNoProcedure();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);


        /*����RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(      NAS_LMM_NOT_BARRED);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                        EMM_SS_REG_NO_CELL_AVAILABLE,
                        TI_NAS_EMM_STATE_NO_TIMER);
    return NAS_LMM_MSG_DISCARD;

}


VOS_VOID  NAS_EMM_GU2LResumeStateChng(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_GU2LResumeStateChng: CurState = ",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GU2LResumeStateChng_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* ���ݼ�¼�� staBeforeSuspend Ǩ��״̬*/
    if( EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}
VOS_VOID  NAS_EMM_GU2LResumeStateChngAsPlmnInd(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_GU2LResumeStateChngAsPlmnInd: CurState = ",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GU2LResumeStateChngAsPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* ���ݼ�¼�� staBeforeSuspend Ǩ��״̬*/
    if( EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}
VOS_VOID  NAS_EMM_RegForbidSysInfoProc( EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RegForbidSysInfoProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegForbidSysInfoProc_ENUM,LNAS_ENTRY);

    if (NAS_RELEASE_CTRL)
    {
        /* �жϳ����������Ƿ񼤻���δ����򱾵�DETACH��ת��DEREG+LIMITED_SERVICE״̬��
        �������򱣳�ԭ�д��� */
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_LocalDetachProc();
            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_GU2L_NO_EPS_BEAR);
            #endif
            NAS_LMM_DeregReleaseResource();

            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
            NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

            NAS_EMM_AppSendAttRsltForb(ulForbiddenInfo);

        }
        else
        {
            /* ע��̬������REG.LIMITED�� */
            NAS_EMM_SetTauTypeNoProcedure();

            NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
            /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
            NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbiddenInfo);
        }
    }
    else
    {
        /* ע��̬������REG.LIMITED�� */
        NAS_EMM_SetTauTypeNoProcedure();

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbiddenInfo);
    }


    return;
}
VOS_VOID  NAS_EMM_GU2LNoEpsBearProc(VOS_VOID)
{
    VOS_UINT32                          ulRst;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_GU2LNoEpsBearProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GU2LNoEpsBearProc_ENUM,LNAS_ENTRY);

    NAS_EMM_LocalDetachProc();
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_GU2L_NO_EPS_BEAR);
    #endif

    NAS_LMM_DeregReleaseResource();

    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    /* ���·���ATTACH */
    ulRst = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_SUCC != ulRst)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_GU2LNoEpsBearProc:  send INTRA ATTACH REQ ERR !");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_GU2LNoEpsBearProc_ENUM,LNAS_EMM_SEND_ATT_REQ_ERR);
    }

    return;
}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd: \
                            Input para invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    /*���BAR��ʶ*/
    NAS_EMM_ClearBarResouce();


    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd:\
                            NAS_EMM_GetResumeType()= ,NAS_EMM_GetMsBefSuspend()",
                            NAS_EMM_GetResumeType(),NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetResumeType(),
                            NAS_EMM_GetMsBefSuspend());

    /* GU��L����ѡ���ض���ʱ��MMC�յ�LMM��RESUME IND�ͻ��·��������� */
    if (NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
    {
        if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_RrcResumeReselTypeSetTauStartCause();
        }
        /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
        NAS_EMM_SecuResumeIdle();
        NAS_EMM_GU2LResumeStateChngAsPlmnInd();

        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType())
    {
        if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_RrcResumeRedirTypeSetTauStartCause();
        }
        /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
        NAS_EMM_SecuResumeIdle();
        NAS_EMM_GU2LResumeStateChngAsPlmnInd();

        return NAS_LMM_MSG_HANDLED;
    }

    /* L2GU���˹����п����յ�MMC������������Ϣ��CCO/HO�Ļ��˹�����Ϊ����̬��
       Ҳ�����յ�MMC������������Ϣ */
    if((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_ReverseStateChngAsPlmnInd();
    }

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* ֪ͨESMִ���˱���DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* ��MMC��DETACH�ɹ� */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* �޿�״̬������ǽ���ע�����п���Ҫ��L */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq: NO_IMSI ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_EMM_NO_IMSI);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_DeregReleaseResource();

        /* ����CCO�ĳ�����ȫ������RRC���ͷţ�CCOֻ�ܿ���������������GAS��CNF��ʱ���� */
        if(LRRC_LMM_SYS_CHNG_TYPE_CCO != NAS_EMM_GetResumeType())
        {
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
        }

        return  NAS_LMM_MSG_HANDLED;

    }

    /* �п� */
    switch(NAS_EMM_GetResumeType())
    {
                /* ��ѡ���ض�����ѡ���ˡ��ض�����˺�CCO�ĳ���������DETACH��ϵͳ��Ϣ */
        case    LRRC_LMM_SYS_CHNG_TYPE_RESEL:
        case    LRRC_LMM_SYS_CHNG_TYPE_REDIR:
        case    LRRC_LMM_SYS_CHNG_TYPE_CCO:
        case    LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE:
        case    LRRC_LMM_SYS_CHNG_TYPE_REDIR_REVERSE:

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
                NAS_LMM_DeregReleaseResource();
                break;

                /* �л����л����˺�CCO���˵ĳ�������������DETACH���RRC���ͷ� */
        case    LRRC_LMM_SYS_CHNG_TYPE_HO:
        case    LRRC_LMM_SYS_CHNG_TYPE_HO_REVERSE:
        case    LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE:

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
                NAS_LMM_DeregReleaseResource();

                /* �ͷ�RRC���޸�����״̬Ϊ�ͷŹ����� */
                NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
                NAS_EMM_SetConnState(NAS_EMM_CONN_WAIT_SYS_INFO);
                break;

        default:
                NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq: Invalid resume type = ",
                                        NAS_EMM_GetResumeType());
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_EMM_RESUME_TYPE,
                                        NAS_EMM_GetResumeType());
                break;
    }

    return  NAS_LMM_MSG_HANDLED;

}
VOS_VOID  NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg(VOS_VOID)
{

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg_ENUM,LNAS_ENTRY);
    if (NAS_RELEASE_CTRL)
    {
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_GU2LNoEpsBearProc();
        }
        else
        {
            NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
        }
    }
    else
    {
        NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
    }
    return;
}

/* lihong00150010 emergency tau&service begin */

VOS_VOID  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden
(
    const EMMC_EMM_SYS_INFO_IND_STRU   *pstsysinfo
)
{
    /* ����ϵͳ�任����ʱ��������ANY CELLפ��ʱ��LTE����ѡ */
    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden: Forbidden ");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden_ENUM,LNAS_EMM_FORBIDDEN);

    /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
    NAS_EMM_SecuResumeIdle();

    if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {   /* ע��̬������REG.LIMITED�� */
        /* lihong00150010 emergency tau&service begin */
        if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_RegForbidSysInfoProc(pstsysinfo->ulForbiddenInfo);
            if (MMC_LMM_CONN_IDLE != NAS_EMM_GetConnState())
            {
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:Limited Srv Connected");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden_ENUM,LNAS_FUNCTION_LABEL1);

                /*����NAS_EMM_REL_REQ*/
                NAS_EMM_RelReq(         NAS_LMM_NOT_BARRED);
            }
        }
        else
        {
            NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
        }
    }/* lihong00150010 emergency tau&service end */
    else
    {   /* δע��: ��������״̬: DEREG. NO_CELL��NO IMSI�����ܽ���DEREG.LIMITED */
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SetAttType();

        /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
        NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
    }
}
/* lihong00150010 emergency tau&service end */

VOS_UINT32  NAS_EMM_IsHoIgnoreForbSysInfo(
                     EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo)
{
    VOS_UINT32                           ulIsHplmnFlag = NAS_EMM_NO;

    ulIsHplmnFlag = NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(&(pstsysinfo->stPlmnId));

    /*DCM��������*/
    if((NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_VALID == g_ulHoIgnoreForbidTaFlag)
            &&(NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:DCM");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_YES;
    }

    /*4Gδ����HPLMN����*/
    if((PS_SUCC != LPS_OM_IsTestMode())
                && (PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch())
                && (NAS_EMM_YES == ulIsHplmnFlag))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:Hplmn");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }

    /*4Gδ����VHPLMN*/
    if((PS_SUCC != LPS_OM_IsTestMode())
                && (PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch())
                && (NAS_EMM_YES != ulIsHplmnFlag))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:Vplmn");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd: ResumeType = ",
                        NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        NAS_EMM_GetResumeType());

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;

    /* ͣ��ʱ�� */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        ||(NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* ��RESUME֮ǰ�� NO IMSI״̬��������Ҫ����NO IMSI״̬ */
    if(EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
    {
        /*��MMC����ע���� ��Ϣ*/

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_NO_IMSI,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*��MMC����ATTACHʧ��*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);

        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd: NO_IMSI ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_NO_IMSI);
        return  NAS_LMM_MSG_HANDLED;
    }

    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    /* ���DCM������������л�����TA�ı�ʶ��Ч����GU��L���л������Ǳ���TA FOR Roaming */
    /* �����4Gδ���������л���������Ҳ������TA����*/
    if(NAS_EMM_YES == NAS_EMM_IsHoIgnoreForbSysInfo(pstsysinfo))
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo);
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
        }
    }

    /*GU2L��LRRC�ܷ�פ������"forbidden tracking areas for regional provision of service"�б�
    �е�TAС��������ȷ������ʱ���ջ�פ��ʵ�֣�SYS�жϽ�ֹע�� */
    if((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
/* lihong00150010 emergency tau&service begin */
        NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden(pstsysinfo);
/* lihong00150010 emergency tau&service end */
    }
    else
    {   /* ���SYS�ж��ܹ�ע��, ����RESUMEǰ��״̬, �ж��Ƿ���ATTACH������TAU */

        if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            /* �жϳ����������Ƿ񼤻���δ����򱾵�DETACH��ת��DEREG+NORMAL_SERVICE״̬��
            ����ATTACH���̣�
            �������򱣳�ԭ�д��� */
            NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg();
        }
        else
        {
            /*δע��̬: ��״̬ΪDEREG.NORMAL_SERVICE*/
            NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg();
        }
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd
(
    VOS_UINT32      ulMsgId,
    VOS_VOID        *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:NAS_EMM_GetResumeType() = ",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /*���BAR��ʶ*/
    NAS_EMM_ClearBarResouce();

    /* �رյ�ǰEMM�ĳ�Del Forb Ta Proid֮���״̬��ʱ��, Del Forb Ta Proidֻ���ڹػ�ʱֹͣ*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    switch(NAS_EMM_GetResumeType())
    {
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
                    || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
                    && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
                {
                    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:LAU OR COMBINED RAU");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
                {
                    NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:EMC CSFB,LAI CHANG ");
                    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_IsG2LGmmSuspendAndIsrAct();
                }
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
                NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                break;
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                /*CCO/REDIR/RESEL�����ڴ�״̬�����յ�������Ϣ*/
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                break;
        default:
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_ERROR);
                break;

    }
    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode(VOS_VOID)
{
    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
VOS_UINT32 NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
)
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (GMM_LMM_GPRS_SUSPENSION == NAS_LMM_GetEmmInfoPsState())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode(VOS_VOID)
{
    if ((NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        && (VOS_TRUE == NAS_LMM_GetEmmInfoCsEmcConneExitFlag())
        && (VOS_TRUE == NAS_LMM_GetEmmInfoLaiChangeFlag())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir )
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}




VOS_UINT32 NAS_EMM_IsPmmConnectAndIsrAct
(
    VOS_VOID
)
{
    if ((GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == NAS_LMM_GetEmmInfoUConnState())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

VOS_UINT32 NAS_EMM_IsG2LAndGprsStateReady
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
)
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (GMM_LMM_GPRS_MM_STATE_READY == NAS_LMM_GetEmmInfoGConnState()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

VOS_UINT32 NAS_EMM_IsW2LAndPmmConnect
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
)
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_W2L == enRsmDir)
        && (GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == NAS_LMM_GetEmmInfoUConnState()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}


VOS_VOID NAS_EMM_SetTinToPtmsiWhenIsrAct(VOS_VOID)
{
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU          *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SetTinToPtmsiWhenIsrAct is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinToPtmsiWhenIsrAct_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    if (((NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
        || (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
        || (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir)))
        &&(MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);

        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SetTinToPtmsiWhenIsrAct: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinToPtmsiWhenIsrAct_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }
    return ;
}
VOS_VOID NAS_EMM_IsG2LGmmSuspendAndIsrAct(VOS_VOID)
{
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsG2LGmmSuspendAndIsrAct is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsG2LGmmSuspendAndIsrAct_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    if ((NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);

        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsG2LGmmSuspendAndIsrAct: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsG2LGmmSuspendAndIsrAct_ENUM,LNAS_FUNCTION_LABEL2);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    }
    return;
}


VOS_VOID  NAS_EMM_RrcResumeReselTypeSetTauStartCause(VOS_VOID  )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    /* ��ȡTINֵ */
    enTinType = NAS_EMM_GetTinType();

    if(NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
    }
    else
    {
        NAS_EMM_ProcConnGu2LReselect();
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_GPRS_READY_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:PMM-CONNECTED init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_PMM_CONNECTED_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         �������ʱ����TAU�����е� */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }


    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == enTinType))
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:ISR ACT and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }
    return;
}



VOS_VOID  NAS_EMM_RrcResumeRedirTypeSetTauStartCause(VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    /* ��ȡTINֵ */
    ulTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         �������ʱ����TAU�����е� */
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (GMM_LMM_GPRS_SUSPENSION == NAS_LMM_GetEmmInfoPsState())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if ((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:ISR ACT and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }
    return;
}

VOS_VOID  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc(VOS_VOID)
{
    /*����GU2L�ĳ��������ݼ���ǰ״̬����NO CELL״̬��NO IMSI״̬ */
    if(NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    NAS_EMM_GU2LResumeStateChng();
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        /*����RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    return;

}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:NAS_EMM_GetResumeType()=",
                               NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_RESUME_TYPE,
                               NAS_EMM_GetResumeType());

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_RatErrRecord(EMM_OM_ERRLOG_REVERSE_WAIT_SYSINFO_TIMEOUT_PROCEDURE);
    #endif

    switch(NAS_EMM_GetResumeType())
    {
        /*���ڹ�������л��˵ĳ��������ݹ���״̬����NO CELL״̬��NO IMSI״̬ */

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                NAS_EMM_ReverseStateChng();
                if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
                {
                    /*����RRC_MM_REL_REQ*/
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                break;
        /*����GU2L�ĳ��������ݼ���ǰ״̬����NO CELL״̬��NO IMSI״̬ */
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
                if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
                {
                    NAS_EMM_RrcResumeReselTypeSetTauStartCause();
                }
                /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:

                if((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
                    && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
                {
                    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:LAU OR COMBINED RAU");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
                {
                    NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:EMC CSFB,LAI CHANG ");
                    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_IsG2LGmmSuspendAndIsrAct();
                }

                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
                NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

                /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
                {
                    NAS_EMM_RrcResumeRedirTypeSetTauStartCause();
                }
                /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        default :
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_ERROR);
                break;
    }
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:NAS_EMM_GetResumeType()=",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /* ֪ͨERABM�ͷ�����,Ԥ�������Ѿ����ˣ��˴����ٷ� */

    switch(NAS_EMM_GetResumeType())
    {
        /*���ڹ�������л��˵ĳ������յ��ͷź󣬽���NO CELL״̬��NO IMSI״̬ */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                /*ֹͣ��ʱ��TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);
                NAS_EMM_ReverseStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                /*GU->L����HO���������յ�LRRC_LMM_REL_IND��Ϣ������Ԥ�������������ͷ�*/
                break;
        default :
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd_ENUM,LNAS_ERROR);
                break;
    }
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetResumeType() =",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());
    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*����RESUMEǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }
        if (NAS_RELEASE_R11)
        {
            if (NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
            {
                NAS_EMM_SetTinToPtmsiWhenIsrAct();
            }
            else
            {
                NAS_EMM_IsG2LGmmSuspendAndIsrAct();
            }
        }

        /*��������TAU��������ʱ��־*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);

    }
    else
    {
        /*���˹��̵Ĵ���*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL2,
                                     NAS_EMM_GetMsBefSuspend());

        /*����SUSPENDǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*��������TAU��������ʱ��־*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetResumeType() =",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());
    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*����RESUMEǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /* ���ó��������ı仯*/
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
    }
    else
    {
        /*���˹��̵Ĵ���*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL2,
                                    NAS_EMM_GetMsBefSuspend());

        /*����SUSPENDǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /* ���ó��������ı仯*/
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    }
    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_ProcInterSysCheckRrcRelCause(VOS_VOID)
{
    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:load balance");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL1);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE);
        return NAS_EMM_YES;
    }
    else if(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        /* ����ɾ�������������PENDING,��ᷢ��SERVICE */
        NAS_EMM_TAU_IsUplinkPending();

        if(NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:Init Ser.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_SER_UplinkPending();
        }
        else
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:RRC connection failure");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL3);

            /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
            NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL);
        }

        return NAS_EMM_YES;
    }
    else
    {

    }

    return NAS_EMM_NO;
}
VOS_UINT32 NAS_EMM_ProcSysCheck3412Exp( VOS_VOID )
{
    if (NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCheck3412Exp:REG+NO_AVAILABE_CELL T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCheck3412Exp_ENUM,LNAS_FUNCTION_LABEL1);
        if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
        {
            /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
            NAS_EMM_SecuResumeIdle();
        }

        if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
        }

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_EMM_YES;
    }

    /* Э��24301 5.3.5�½�����������ڷ�REG+NO_AVAILABLE_CELL״̬�£�T3412��ʱ��
     �򵱻ص�REG+NORMAL_SERVICE̬��Ӧ���� Periodic TAU*/
    if(NAS_EMM_T3412_EXP_YES_OTHER_STATE == NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCheck3412Exp:Other State T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCheck3412Exp_ENUM,LNAS_FUNCTION_LABEL2);
        if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
        {
            /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
            NAS_EMM_SecuResumeIdle();
        }

        NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_T3412EXP);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_ProcSysCommonCheckTauFlag( VOS_VOID )
{
    /* ���TA����TA List�У���Ҫ����TAU */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:TAI not in TAI LIST init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_LIST_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����ESM�����޸ĳ���������*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����UE_NET_CAP or DRX�ı䣬����TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /* �����ǰע����ΪPS���ҵ�ǰ����������CS���ע�ᣬ��������TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:current reg domain=PS,can register in cs domain");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*�����ǰEUֵ����EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:EU value is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /*�ж�RRC Relԭ���ʶ*/
    if(NAS_EMM_YES == NAS_EMM_ProcInterSysCheckRrcRelCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* ���UE��������������� */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*���T3412������ʱ��*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCheck3412Exp() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:3412 exp");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcHoSysCommonCheckTauFlag
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2013-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_ProcHoSysCommonCheckTauFlag( VOS_VOID )
{
    /* ���TA����TA List�У���Ҫ����TAU */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:TAI not in TAI LIST init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_LIST_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����ESM�����޸ĳ���������*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����UE_NET_CAP or DRX�ı䣬����TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /* �����ǰע����ΪPS���ҵ�ǰ����������CS���ע�ᣬ��������TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:current reg domain=PS,can register in cs domain");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*�����ǰEUֵ����EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:EU value is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /* ���UE��������������� */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*���T3412������ʱ��*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCheck3412Exp() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:3412 exp");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*leili modify for isr begin*/

VOS_VOID  NAS_EMM_ProcConnGu2LReselect( VOS_VOID )
{
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32 enPacketMmState = GMM_LMM_PACKET_MM_STATE_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcConnGu2LReselect is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcConnGu2LReselect_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

     /* ��ȡTINֵ */
    enTinType = NAS_EMM_GetTinType();

    /* ��ȡUģ����״̬ */
    enPacketMmState = NAS_LMM_GetEmmInfoUConnState();

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    if ((GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == enPacketMmState)
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == enTinType))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        /*PC REPLAY MODIFY BY LEILI END*/
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcConnGu2LReselect: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcConnGu2LReselect_ENUM,LNAS_FUNCTION_LABEL2);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    }
    return;
}
/*leili modify for isr end*/

VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegReselect( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo      = NAS_EMM_NULL_PTR;

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    /*leili modify for isr begin*/
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
    }
    else
    {
        NAS_EMM_ProcConnGu2LReselect();
    }
    /*leili modify for isr end*/

    /* ��ȡTINֵ */
    enTinType = NAS_EMM_GetTinType();

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL1);

            /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
                TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    /* For case l, if the TIN indicates "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before
    initiating the tracking area updating procedure.*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_GPRS_READY_TAU);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:PMM-CONNECTED init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_PMM_CONNECTED_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         �������ʱ����TAU�����е� */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);

        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_SRVCC);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(enRsmDir))

    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*��TA����TA List��������װ�����溯���ж�*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCommonCheckTauFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* ���������������ϣ�����Ҫ����TAU,ֱ�ӻظ���������*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL2);

    /* ��ȡEMMά����������Ϣ*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA��TAI List�У����� L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

    /* ת��EMM״̬��MS_REG+SS_NORMAL_SEARVICE*/
    /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);*/
    /* lihong00150010 emergency tau&service end */
    NAS_EMM_SetTauTypeNoProcedure();
    /* ע��/����״̬�ϱ�����MMC�Ż�:�ȱ���EUֵ�ٻظ�TAU��� */
    /* ȷ��EU״̬ΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
    /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    /* ���Active flag */
    NAS_EMM_TAU_ClearActiveFlagProc();

    return;
}
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegRedirect( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU              *pMmNetInfo  = NAS_EMM_NULL_PTR;

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* ��ȡTINֵ */
    ulTinType = NAS_EMM_GetTinType();

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL1);

            /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
                TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         �������ʱ����TAU�����е� */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*��TA����TA List���������жϣ���װ������ĺ���*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCommonCheckTauFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* ���������������ϣ�����Ҫ����TAU,ֱ�ӻظ���������*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL3);

    /* ��ȡEMMά����������Ϣ*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA��TAI List�У����� L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
    /* lihong00150010 emergency tau&service begin */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

    /* ת��EMM״̬��MS_REG+SS_NORMAL_SEARVICE*/
    /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);*/
    /* lihong00150010 emergency tau&service end */
    NAS_EMM_SetTauTypeNoProcedure();

    /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

    /* ȷ��EU״̬ΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

    /* ���Active flag */
    NAS_EMM_TAU_ClearActiveFlagProc();

    return;
}


VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegCco( VOS_VOID )
{
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegCco: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegCco_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* CCO��Ҫ���������ݶ�����TAU */
    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
    && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegCco:combined succ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegCco_ENUM,LNAS_FUNCTION_LABEL1);

        /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
            TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_CCO);

    return;
}
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LHo( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU              *pMmNetInfo  = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo: ENTER.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_ENTRY);

    NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

    /* ��ȡTINֵ */
    ulTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL1);

            /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
                TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* ISR���������£��ж��Ƿ���Ҫ����TAU */

    /* ��ȡ�ָ����� */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         �������ʱ����TAU�����е� */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);

        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* ������: ��ϵͳTAUʹ����ϵͳTAU�ӿ� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*��TA����TA List���������жϣ���װ������ĺ���*/
    if(NAS_EMM_YES == NAS_EMM_ProcHoSysCommonCheckTauFlag())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* ���������������ϣ�����Ҫ����TAU,ֱ�ӻظ���������*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL3);

    /* ��ȡEMMά����������Ϣ*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA��TAI List�У����� L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);

    /* ת��EMM״̬��MS_REG+SS_NORMAL_SEARVICE*/
    NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    NAS_EMM_SetTauTypeNoProcedure();
    /* ע��/����״̬�ϱ�����MMC�Ż�:�ȱ���EUֵ�ٻظ�TAU��� */
    /* �ȱ���EUֵ�ٻظ�TAU��� */
    /* ȷ��EU״̬ΪEU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
    /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    /* �ϱ�EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();

    return;
}
VOS_VOID  NAS_EMM_ProcSuitSysWhenRsmGu2LReg(VOS_VOID)
{
    /* ����CSFB�������󿪹ش�ʱ������RRC��������ϵͳ�任��L�¾�����
       IMSI_ATTACH����TAU,Ŀ���ǽ������type1���͵�TAU���¸����޷��յ��������⣬
       GCF���Գ����˿�����Ч������Э������ */
    if((NAS_EMM_YES == g_ulNasCsfbTauType2Flag)
        &&(PS_SUCC != LPS_OM_IsTestMode()))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: LanZhou CSFB flag is valid, set reg domain ps.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* �����TMO������������ѡ���ض����CCO����任��L�·���TAUӦЯ��active��ʶ */
    if(NAS_EMM_YES == NAS_EMM_IsTmoUsimCard())
    {
        if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
            ||(NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType())
            ||(NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: TMO card, save active flag ctrl.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_TAU_SaveEmmTmoActiveFlagCtrl(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_VALID);
        }
    }

    switch ( NAS_EMM_GetResumeType())
    {
        case NAS_LMM_SYS_CHNG_TYPE_RSL:

            NAS_EMM_ProcSysWhenRsmGu2LRegReselect();
            break;

        case NAS_LMM_SYS_CHNG_TYPE_REDIR:

            NAS_EMM_ProcSysWhenRsmGu2LRegRedirect();
            break;
        case NAS_LMM_SYS_CHNG_TYPE_CCO:
            NAS_EMM_ProcSysWhenRsmGu2LRegCco();
            break;

        case NAS_LMM_SYS_CHNG_TYPE_HO:
            NAS_EMM_ProcSysWhenRsmGu2LHo();
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: HO.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL3);
            break;
    }

    return;
}
VOS_VOID  NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg(VOS_VOID)
{
    VOS_UINT32                          ulSendResult = NAS_EMM_FAIL;

    /* ��״̬ת����MS_DEREG + SS_DEREG_NORMAL_SERVICE״̬ */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ��TIN ==  PTMSI�����ȡGU�İ�ȫ���� */
    NAS_EMM_MmcRsmGetSecuPara();

    /* ��ATTACHģ�鷢��EMM_INTRA_ATTACH_REQ��Ϣ */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_FAIL == ulSendResult)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg : Send IntraMsg Failure !");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg_ENUM,LNAS_FAIL);
        return ;
    }

    return;
}
VOS_VOID  NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg(VOS_VOID)
{
    VOS_UINT32                          ulSendResult;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;

    PS_MEM_SET(&stCurTa, 0, sizeof(NAS_MM_TA_STRU));
    /* ��ȡ��ǰTA���ϴγ���ע���TA��Ϣ */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* TA���ϴγ��Է���ע���TA��ͬ���ж�ʱ������Ӧ�õȳ�ʱ*/
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg: The same as last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg_ENUM,LNAS_EMM_TA_NO_CHANGE);

        if(NAS_EMM_YES == NAS_EMM_Attach_IsTimerRunning())
        {
            return;
        }
    }

    /*����attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /* ��״̬ת����MS_DEREG + SS_DEREG_NORMAL_SERVICE״̬ */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* ��TIN ==  PTMSI�����ȡGU�İ�ȫ���� */
    NAS_EMM_MmcRsmGetSecuPara();

    /* ��ATTACHģ�鷢��EMM_INTRA_ATTACH_REQ��Ϣ */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_FAIL == ulSendResult)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg : Send IntraMsg Failure !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg_ENUM,LNAS_FAIL);
        return ;
    }

    return;
}


VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_ENTRY);

    /*����RESUMEǰ��״̬����״̬Ǩ��*/
    if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        /*MMC����Lģ����Ҫ����TAUԭ�������*/
        NAS_EMM_MmcResumeSetTauStartCause();

        /* ��״̬ת����MS_DEREG + SS_DEREG_PLMN_SEARCH״̬ */
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* ���RESUME֮ǰ��״̬ΪNO IMSI */
        if (EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            /* ��״̬ת����MS_DEREG + SS_DEREG_NO_IMSI״̬ */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* ��״̬ת����MS_DEREG + SS_DEREG_NORMAL_SERVICE״̬ */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return NAS_LMM_MSG_HANDLED;
}



VOS_VOID  NAS_EMM_ResumeProcPTMSITau( VOS_VOID )
{

    NAS_EMM_TAU_LOG2_INFO("NAS_EMM_ProcPTMSITau:NAS_EMM_TAU_GetEmmT3412ExpCtrl() = ,\
        NAS_LMM_GetEmmInfoRegDomain()", NAS_LMM_GetEmmInfoT3412ExpCtrl(),
        NAS_LMM_GetEmmInfoRegDomain());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_ResumeProcPTMSITau_ENUM,LNAS_FUNCTION_LABEL1,
                                        NAS_LMM_GetEmmInfoT3412ExpCtrl(),
                                        NAS_LMM_GetEmmInfoRegDomain());

    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
        && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
            TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    }
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    return;
}
VOS_VOID  NAS_EMM_MmcResumeSetTauStartCause(VOS_VOID)
{
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32            enTinType   = MMC_LMM_TIN_BUTT;

    enTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcResumeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcResumeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MmcResumeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmcResumeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*c)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"*/
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
           and the UE previously either performed a location area update procedure
           or a combined routing area update procedure in A/Gb or Iu mode,
           in order to re-establish the SGs association. In this case the EPS update
           type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
    {
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    }

    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were not resumed before
    returning to S1 mode, the UE shall set the TIN to "P-TMSI" before initiating
    the combined tracking area updating procedure*/
    if (NAS_RELEASE_R11)
    {
        /* ��ȡ�ָ����� */
        enRsmDir = NAS_EMM_GetResumeDir();
        if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(enRsmDir))
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        }
    }

    return;
}
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* �رյ�ǰEMM�ĳ�Del Forb Ta Proid֮���״̬��ʱ��, Del Forb Ta Proidֻ���ڹػ�ʱֹͣ*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /*����RESUMEǰ��״̬����״̬Ǩ��*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        /* ���RESUME֮ǰ��NO IMSI̬ */
        if(EMM_SS_DEREG_NO_IMSI== NAS_EMM_GetSsBefResume())
        {
            /* ��״̬ת����MS_DEREG + SS_DEREG_NO_IMSI״̬ */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* ��״̬ת����MS_DEREG + SS_DEREG_NO_CELL_AVAILABLE״̬ */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /*MMC����Lģ����Ҫ����TAUԭ�������*/
    NAS_EMM_MmcResumeSetTauStartCause();

    /* ��״̬ת����MS_REG + SS_REG_NO_CELL_AVAILABLE״̬ */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_ENTRY);

    /* ֪ͨESMִ���˱���DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* ����CL�汾��PS DETACH֪ͨESMɾ������EHRPD��س��ؼ�¼ */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* ��MMC��DETACH�ɹ� */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* �п����Ǵ��ڽ���ע����޿�״̬ */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        /* �޿� */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* �п� */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_PLMN_SEARCH,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcOriResumeCheckTauFlag
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY         2012-02-27   Draft Enact

*****************************************************************************/
VOS_UINT32   NAS_EMM_MmcOriResumeCheckTauFlag(VOS_VOID)
{
    /* ���TA����TAI List�У�����TA-Updating���͵�TAU*/
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:TA not in TAI List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����ESM�����޸ĳ���������*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����UE_NET_CAP or DRX�ı䣬����TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*��ǰע����ΪPS,��������������CS���ע��*/
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:current reg domain=PS,can register in cs domain.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*EUֵ����EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag: EU is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /*��RRC Relԭ���ʶ�����ж�*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_EMM_REL_CAUSE);

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return NAS_EMM_YES;
    }


    /* ���UE��������������� */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag: UE radio capability change. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);
        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }


    /* ����ʱ��T3412��ʱ */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:T3412 Exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL6);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_VOID  NAS_EMM_MmcOriResumeSysInfoProc(VOS_VOID)
{
    /* ���T3411/3402�����У�����Ҫ�ȳ�ʱ�����Ƚ��ó���ʶ����� */
    if (NAS_EMM_SUCC == NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp())
    {
        return;
    }

    /* ע��̬���յ�ϵͳ��Ϣ,����Ҫ��T3411����T3402��ʱ�Ĺ������� */

    NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc();

    return;
}


VOS_VOID  NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg(VOS_VOID)
{

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg_ENUM,LNAS_ENTRY);
    if (NAS_RELEASE_CTRL)
    {
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_GU2LNoEpsBearProc();
        }
        else
        {
            /* �����յ�SYS_INFO�Ĺ�������*/
            NAS_EMM_MmcOriResumeSysInfoProc();
        }
    }
    else
    {
        /* �����յ�SYS_INFO�Ĺ�������*/
        NAS_EMM_MmcOriResumeSysInfoProc();
    }
    return;
}



VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd: ResumeType = ",
                        NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        NAS_EMM_GetResumeType());

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;
    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
    if(PS_TRUE == NAS_EMM_GetCsfbProcedureFlag())
    {
         NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
         NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
    }

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* ���RESUME֮ǰ״̬ΪMS_DEREG + SS_DEREG_NO_IMSI */
    if (EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
    {
        /* ��״̬ת����MS_DEREG + SS_DEREG_NO_IMSI״̬ */
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_NO_IMSI,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);;

        return NAS_LMM_MSG_HANDLED;
    }


    if ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd: Forb sys info");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_FORB_INFO);

        /*����RESUMEǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
            NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_SetAttType();

            /*��MMC����LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ*/
            NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
        }
        else
        {   /* lihong00150010 emergency tau&service begin */
            if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
            {
                /*MMC����Lģ����Ҫ����TAUԭ�������*/
                NAS_EMM_MmcResumeSetTauStartCause();
                NAS_EMM_RegForbidSysInfoProc(pstsysinfo->ulForbiddenInfo);
            }
            else
            {
                NAS_EMM_MmcOriResumeSysInfoProc();
            }/* lihong00150010 emergency tau&service end */
        }

        return NAS_LMM_MSG_HANDLED;
    }

    /*����RESUMEǰ��״̬����״̬Ǩ��*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg();
    }
    else
    {
        /* �жϳ����������Ƿ񼤻���δ����򱾵�DETACH��ת��DEREG+NORMAL_SERVICE״̬��
            ����ATTACH���̣�
            �������򱣳�ԭ�д��� */
        NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg();
    }
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /*����RESUMEǰ��״̬����״̬Ǩ��*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /*��������TAU��������ʱ��־*/
    /* ���GCF9.2.3.1.5 ������UE������MMC���������������ڼ�T3412��ʱ�������TAU������combined TAU with IMSI���͵�*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /*����RESUMEǰ��״̬����״̬Ǩ��*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* ���ó��������ı仯*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    VOS_UINT32                          ulRslt;
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd_ENUM,LNAS_ENTRY);

    /* ���ResumeType�����������ѡ���ˣ����ӡ������Ϣ*/
    if(LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE != NAS_EMM_GetResumeType())
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd:ResumeType Err.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �������ѡ���ˣ��������̬�µĴ�����ͬ*/
    ulRslt = NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd(ulMsgId, pMsgStru);

    return ulRslt;
}

VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    /* ��ӡ����ú���*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*����RESUMEǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*����DRX��NetCapability�ı��־*/
        if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
        {
            NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
        }
    }
    else
    {
        /*���˹��̵Ĵ���*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL2,
                                    NAS_EMM_GetMsBefSuspend());

        /*����SUSPENDǰ��״̬����״̬Ǩ��*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*����DRX��NetCapability�ı��־*/
        if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
        {
            NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
        }
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    /* ��ӡ����ú���*/
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* ��������ָ��������*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*���RESUMEǰ��״̬DEREG��������*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
    /*����DRX��NetCapability�ı��־*/
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceCapChangeNotify(MsgBlock *    pMsg )
{

    MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU     *pstImsVoiceCapNotify;
    NAS_EMM_PUB_INFO_STRU                        *pstPubInfo;
    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8              enImsaVoiceCap;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_ENTRY);

    pstImsVoiceCapNotify = (VOS_VOID*)pMsg;
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    enImsaVoiceCap = pstPubInfo->enImsaVoiceCap;

    pstPubInfo->enImsaVoiceCap = pstImsVoiceCapNotify->enImsVoiceCap;

    if ((MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE == enImsaVoiceCap)
        && (MMC_LMM_IMS_VOICE_CAP_AVAILABLE == pstImsVoiceCapNotify->enImsVoiceCap))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify: IMS voice avail");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_EMM_IMS_VOICE_AVAIL);

        if ((NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
            && ((NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
                ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
                ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))))
        {
            /*p��when the UE activates mobility management for IMS voice termination as specified in 3GPP TS 24.008 [13],
            annex P.2, and the TIN indicates "RAT-related TMSI";*/
            /*IMS voice from not available to available,ISR���start TAU*/
            /*lint -e960*/
            if ((NAS_EMM_YES == NAS_EMM_IsAnnexP2ConditionSatisfied())
                && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
            {
                NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify: start TAU");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_P2);
            }
            /*lint +e960*/
        }

    }

    return NAS_LMM_MSG_HANDLED;
}





VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceDomainChangeInd(MsgBlock *    pMsg )
{

    MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU        *pstImsVoiceDomainChangInd;
    NAS_EMM_PUB_INFO_STRU                        *pstPubInfo;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            enVoiceDomain;
    VOS_UINT32                                  ulCurEmmStat;
    NAS_LMM_PTL_TI_ENUM_UINT16                  enPtlTimerId;
    MMC_LMM_TAU_RSLT_ENUM_UINT32                ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceDomainChangeInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_ENTRY);

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    pstImsVoiceDomainChangInd = (VOS_VOID*)pMsg;
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    enVoiceDomain = pstPubInfo->ulVoiceDomain;

    //pstPubInfo->ulVoiceDomain = pstImsVoiceDomainChangInd->enVoiceDomain;

    /* ���voice domainû�з����仯��ֱ���˳� */
    if (enVoiceDomain == pstImsVoiceDomainChangInd->enVoiceDomain)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* �����ǰ���ڴ�ģ����ֱ���˳� */
    if (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
        NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        /* ���ô���TAU�ı�ʶ */
        NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �ڿ������߹ػ���DETACH�����У����������Ϣ */
    if((EMM_MS_NULL == NAS_EMM_CUR_MAIN_STAT) ||
        (EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT) ||
        (EMM_MS_DEREG_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        /* ֹͣ ��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
    }

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
                return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                /* ���T3411����������3402��������ȶ�ʱ����ʱ */
                if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
                {
                    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                    /* �������TAU����ԭ�� */
                    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                 /* �������Ƿ�BAR����: TAU;   ��: �������⴦�� */
                if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
                {
                    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcImsVoiceDomainChangeInd: TAU  start");
                    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_FUNCTION_LABEL1);

                    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                    /* �������TAU����ԭ�� */
                    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                /* ��ֹԭ��TAU���̣����·��� */
                ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

                NAS_EMM_AdStateConvert(EMM_MS_REG,
                                       EMM_SS_REG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                break;

        /* SERVICE�����У���ֹԭ��SERVICE���̣����·���TAU */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */

                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);

                NAS_EMM_SER_AbnormalOver();


                /*�������̳�ͻ��־λ*/
                NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

                /* ת��REG.PLMN-SEARCH��ϵͳ��Ϣ */
                NAS_EMM_AdStateConvert(EMM_MS_REG,
                                       EMM_SS_REG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* ȫ�����ͷţ�RRC�ڿ���̬������̬���������ͬ */
                /* �����������̬��ֱ�ӷ����ͷ���Ϣ */
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: Connected! SndRrcRelReq. ");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_FUNCTION_LABEL2);

                /*����RRC_MM_REL_REQ*/
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):
                return NAS_LMM_STORE_HIGH_PRIO_MSG;

        default:
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
                /* ���ô���TAU�ı�ʶ */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_LMM_PreProcMmcCsConnStatusNotify(MsgBlock *    pMsg )
{

    MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU     *pstCsConnStatusNotify;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcCsConnStatusNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcCsConnStatusNotify_ENUM,LNAS_ENTRY);

    pstCsConnStatusNotify = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)pMsg;

    /* ��������˽������������¼���������ı�ʶ����������ñ�ʶ */
    if((VOS_TRUE == pstCsConnStatusNotify->ucCsRrConnStatusFlg) &&
        (VOS_TRUE == pstCsConnStatusNotify->ucCsEmergencyConnStatusFlg))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcCsConnStatusNotify is entered,EMC CONN EXIT");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcCsConnStatusNotify_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoCsEmcConneExitFlag(VOS_TRUE);
    }
    else
    {
    }
    return NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */

