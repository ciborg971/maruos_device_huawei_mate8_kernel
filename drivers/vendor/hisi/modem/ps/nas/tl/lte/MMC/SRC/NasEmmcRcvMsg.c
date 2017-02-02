

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmcRcvMsg.h"
#include  "NasEmmcPublic.h"
#include  "NasEmmcSendMsg.h"
#include  "NasEmmcMain.h"
#include  "NasEmmPubUResume.h"
#include  "NasLmmPubMPrint.h"
#include  "NasLmmPubMTimer.h"
#include  "NasEmmTauSerInclude.h"
#include  "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include  "NasEmmLppMsgProc.h"
#endif
#include "TlPsDrv.h"
/*end*/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMCRCVMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMCRCVMSG_C
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


VOS_UINT32  NAS_EMMC_RcvEmmStartReq( MsgBlock *pMsg )
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvEmmStartReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvEmmStartReq_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvEmmStartReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvEmmStartReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    NAS_EMMC_Init();

    /*����EMMC_EMM_START_CNF��Ϣ*/
    NAS_EMMC_SendEmmStartCnf();

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMMC_RcvEmmStopReq( MsgBlock *pMsg )
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvEmmStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvEmmStopReq_ENUM
,LNAS_ENTRY);
    (void)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvEmmStopReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvEmmStopReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*����EMMC_EMM_START_CNF��Ϣ*/
    NAS_EMMC_SendEmmStopCnf();

    return NAS_LMM_MSG_HANDLED;
}



/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMMC_RcvMmcPlmnSrchReq(MsgBlock *pMsg )
{

    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMmcPlmnReq = NAS_EMMC_NULL_PTR;
    LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32   ulPlmnType;
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulPlmnSrchReqCnt = 1;
#endif

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcPlmnSrchReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �ṹת�� */
    pstMmcPlmnReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pMsg;

    /* ����������� */
    ulPlmnType = NAS_LMM_MmcPlmnReqTypeCheck(pstMmcPlmnReq->enSrchType);
    if (LRRC_LNAS_PLMN_SEARCH_TYPE_BUTT == ulPlmnType)
    {
        NAS_LMM_EMMC_LOG_ERR(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN TYPE IS ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /*�ǿ���̬ʱ���ظ�LIST�����ܾ�.
    LMM�����Ƿ��ڿ���̬��MMC����ֱ���·�MMC_LMM_PLMN_SEARCH_REQҪ��LMM����
    LIST������
    1) ��LMM���ڷǿ���̬��LMM�ظ�LMM_MMC_PLMN_SEARCH_CNF��
    ���Ϊ LIST�����ܾ�;
    2) ���MMC�ڿ���̬����MMC_LMM_PLMN_SEARCH_REQ�������LMM�յ�����Ϣʱת����
    ���������У�����������ΪLIST,��LMM�ظ�MMC_LMM_PLMN_SEARCH_CNF�����Ϊ
    LIST�����ܾ���
    20130603 BEGIN */
    /*
    if((LRRC_LNAS_PLMN_SEARCH_LIST == ulPlmnType)
        && (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN LIST TYPE IS REJECT!");
        NAS_EMMC_SendMmcPlmnListSrchRej();
        return NAS_LMM_MSG_HANDLED;
    }
    */

    /* �����ǰ����IDLE̬ �� NAS_EMM_CONN_RELEASING */
    /*lint -e539*/
    /*lint -e830*/
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
         /* ����list���� , ��ظ�list�ܾ� */
        if(LRRC_LNAS_PLMN_SEARCH_LIST == ulPlmnType)
        {
            NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN LIST TYPE IS REJECT!");
            TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL2);
            NAS_EMMC_SendMmcPlmnListSrchRej();
        }
        else
        {   /* ������ list �������� ����������������Ϣ */
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq:Not Idle,Discard!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL3);
        }

        return NAS_LMM_MSG_HANDLED;
    }
    NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN SEARCH BEGIN!");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL4);
    /*lint +e830*/
    /*lint +e539*/

#if (VOS_OS_VER != VOS_WIN32)
    if(1 == s_ulPlmnSrchReqCnt)
    {
        (VOS_VOID) LDRV_SYSBOOT_STAMPADD("LTE Cell search start",__LINE__);
        s_ulPlmnSrchReqCnt++;
    }
#endif
    /*end*/

    /* �ṹת�� */
    pstMmcPlmnReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pMsg;

    /* �����ǰ���뼼��û��L����LTE��DISABLED����ֻ��ӦLIST��������������ֱ�ӷ��� */
    if((NAS_LMM_FAIL == NAS_EMM_lteRatIsExist())
     ||(NAS_LMM_SUCC == NAS_EMM_IsLteDisabled()))
    {
        if(MMC_LMM_PLMN_SRCH_LIST != pstMmcPlmnReq->enSrchType)
        {
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq: LTE IS NOT EXIST or LTE DISABLED");
            TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL5);
            return NAS_LMM_MSG_HANDLED;
        }
    }

    if (MMC_LMM_PLMN_SRCH_USER_SPEC == pstMmcPlmnReq->enSrchType)
    {
        NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_YES);
    }

    if (pstMmcPlmnReq->enSrchType != MMC_LMM_PLMN_SRCH_LIST)
    {
        /*����EMMC_EMM_PLMN_IND��Ϣ*/
        NAS_EMMC_SendEmmPlmnInd();
    }

/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    /*����RRC_MM_PLMN_SEARCH_REQ��Ϣ*/
    NAS_EMMC_SendRrcPlmnSrchReq(pstMmcPlmnReq);

    /* ����lIST��ʱ������������� */
    if (VOS_FALSE == NAS_EMMC_IsBgListSearch(pstMmcPlmnReq->enSrchType))
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_VALID);
        NAS_LMM_StartStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    return NAS_LMM_MSG_HANDLED;

}






VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchCnf (MsgBlock *pMsg)
{
    LRRC_LMM_PLMN_SEARCH_CNF_STRU         *pstPlmnCnf = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcPlmnSrchCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcPlmnSrchCnf_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcPlmnSrchCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcPlmnSrchCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ���������������ʶ������� */
    if (NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);
        NAS_LMM_StopStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    /* �ṹת�� */
    pstPlmnCnf = (LRRC_LMM_PLMN_SEARCH_CNF_STRU *)pMsg;

    /*����LMM_MMC_PLMN_SRCH_CNF��Ϣ*/
    NAS_EMMC_SendMmcPlmnSrchCnf(pstPlmnCnf);

    return NAS_LMM_MSG_HANDLED;
}
/* ɾ��û�е��ú��� */

VOS_UINT32 NAS_LMM_PreProcMmcLteSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfoInd = NAS_EMMC_NULL_PTR;
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo;
    VOS_UINT32                          ulTaCellIdChangeInfo;
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulMatchRslt;
    /* lihong00150010 emergency tau&service begin */
    EMMC_EMM_CELL_STATUS_ENUM_UINT32    enCellStatus = EMMC_EMM_CELL_STATUS_NORMAL;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 enForbdInfo = EMMC_EMM_NO_FORBIDDEN;
    /* lihong00150010 emergency tau&service end */

    NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_LMM_PreProcMmcLteSysInfoInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ����Ǵ�ģ������ */
    if(NAS_EMM_IS_SUSPEND == NAS_EMM_IsSuspended())
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:EMM_MS_RRC_CONN_REL_INIT is discard");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �ṹת�� */
    pstLteSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)pMsg;

    /* ĿǰRRC��NAS�ϱ���ϵͳ��Ϣ�����г�����astSuitPlmnList����ֻ�ϱ�1��PLMN,
       stSpecPlmnIdList�е�ulSuitPlmnNum Ҳֻ��Ĺ̶�ֵΪ1*/

    /* ���ù��������ʶ */
    if (pstLteSysInfoInd->stLteSysInfo.stSpecPlmnIdList.ulSuitPlmnNum > 1)
    {
        NAS_EMMC_SetShareNetFlag(VOS_TRUE);
    }
    else
    {
        NAS_EMMC_SetShareNetFlag(VOS_FALSE);
    }

    /*NAS_EMM_SetLteNoSubscribeExtCauseFlag(NAS_EMM_EUTRAN_ALLOWED);*/

    /*TA����CELL ID �ı�*/
    NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID( &pstLteSysInfoInd->stLteSysInfo,
                                                &ulTaCellIdChangeInfo);

    /*ϵͳ��Ϣ�е�PLMN�Ƿ��ھܾ�#18�б���*/
    ulMatchRslt = NAS_EMMC_PlmnMatchRej18PlmnList((NAS_MM_PLMN_ID_STRU *)&pstLteSysInfoInd->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /*���õ�ǰPLMN�Ƿ��ھܾ�#18�б��еı�ʶ*/
    NAS_EMMC_SetRejCause18Flag(ulMatchRslt);

    NAS_LMM_EMMC_LOG1_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:ulMatchRslt = ",
                                ulMatchRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL2,
                                ulMatchRslt);

    if ((NAS_EMM_REJ_YES == ulMatchRslt) &&
        (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:Reg Domain update");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL3);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* �ж�ϵͳ��Ϣ�Ƿ����仯*/
    /* lihong00150010 emergency tau&service begin */
    NAS_EMMC_ProcessMmcLteSysInfoInd(   &pstLteSysInfoInd->stLteSysInfo,
                                        &ulChangeInfo,
                                        &enCellStatus,
                                        &enForbdInfo);
    /* lihong00150010 emergency tau&service end */

    /* The emergency number(s) received in the Emergency Number List IE are valid only in networks
        in the same country as the cell on which this IE is received.    */
    /* ֪ͨMMC�����������б������Ƿ�֧��IMS VOICE�ͽ��������Լ�LTE��CS������ */
    if (NAS_EMM_IsCountryChanged())
    {
        NAS_EMM_ClearEmergencyList();

        NAS_EMM_SendMmcInfoChangeNotify();

    }

    /* lihong00150010 emergency tau&service begin */
    NAS_EMMC_SendEmmSysInfoInd(ulChangeInfo,enCellStatus,enForbdInfo);
    /* lihong00150010 emergency tau&service end */

    if (NAS_RELEASE_R11)
    {
        /* ���PLMN�����ı䣬��T3402��ʱ����Դ��ATTACH REJ����T3402��ʱ������ΪĬ��ֵ */
        if ((EMMC_EMM_CHANGE_PLMN == ulChangeInfo) && (NAS_EMM_T3402_SRC_ATTACH_REJ == NAS_LMM_GetT3402Src()))
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
            {
			    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-09-28,Begin */
                NAS_LMM_Stop3402Timer();
				/* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-09-28,End */
            }
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
            NAS_LMM_SetT3402Src(NAS_EMM_T3402_SRC_OTHERS);
        }
    }

    if (EMMC_EMM_NO_CHANGE != ulChangeInfo)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:Sys info is change");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL4);

        /*��APP����APP_MM_REG_STAT_IND��Ϣ*/
        NAS_EMM_AppRegStatInd(NAS_LMM_GetNasAppRegState(),NAS_LMM_GetEmmCurFsmMS());
    }

   /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvRrcSysInfoInd(MsgBlock *pMsg )
{
    LRRC_LMM_SYS_INFO_IND_STRU         *pstSysInfoInd = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcSysInfoInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ��·�ͷŹ����к�AUTH_INIT״̬���������յ�ϵͳ��Ϣ��ֱ�Ӷ��� */
    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY))
        || (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_LMM_EMMC_LOG1_NORM("NAS_EMMC_RcvRrcSysInfoInd: releasing or 3440 and reattach delay is runing, discard!", NAS_EMM_GetConnState());
        TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1,NAS_EMM_GetConnState());
        return NAS_LMM_MSG_HANDLED;
    }

    /* �ṹת�� */
    pstSysInfoInd = (LRRC_LMM_SYS_INFO_IND_STRU *)pMsg;

    /* ���Not Camp On��ʶ */
    NAS_EMMC_SetNotCampOnFlag(VOS_FALSE);

    #if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SendLppCellChangeInd(pstSysInfoInd->ulCellId,
                                 pstSysInfoInd->ulArfcn,
                                 pstSysInfoInd->usPhysCellId,
                                 pstSysInfoInd->stSpecPlmnIdList.astSuitPlmnList[0].aucPlmnId);
    #endif

    /*����LMM_MMC_SYS_INFO_IND��Ϣ*/
    NAS_EMMC_SendMmcSysInfo(pstSysInfoInd);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvMmcEplmnNotifyReq(MsgBlock *pMsg)
{
    MMC_LMM_EPLMN_NOTIFY_REQ_STRU       *pstEplmnReq;
    NAS_MM_PLMN_LIST_STRU               *pstEPlmnList;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcEplmnNotifyReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcEplmnNotifyReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstEplmnReq                        = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)pMsg;

    /* �����ЧPLMN�б� */
    pstEPlmnList = NAS_EMMC_GetEplmnListAddr();
    if(MMC_LMM_MAX_EQUPLMN_NUM < (pstEplmnReq->ulEplmnNum))
    {
        pstEPlmnList->ulPlmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
    }
    else
    {
        pstEPlmnList->ulPlmnNum = pstEplmnReq->ulEplmnNum;
        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum = pstEplmnReq->ulEplmnNum;
    }
    NAS_LMM_MEM_CPY(&(pstEPlmnList->astPlmnId[0]),&(pstEplmnReq->astEplmnList[0]),
                    sizeof(NAS_MM_PLMN_ID_STRU)*(pstEPlmnList->ulPlmnNum));
    NAS_LMM_MEM_CPY(&(NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->astPlmnId[0]),&(pstEplmnReq->astEplmnList[0]),
                    sizeof(NAS_MM_PLMN_ID_STRU)*(NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum));
    /*����RRC_MM_EQU_PLMN_NOTIFY_REQ��Ϣ*/
    NAS_EMMC_SendRrcEplmnNotifyReq(pstEplmnReq);

    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_RcvMmcEplmnNotifyReq: SEND FORB_TA TO LRRC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvMmcStopSrchReq( MsgBlock *pMsg)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcStopSrchReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcStopSrchReq_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcStopSrchReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcStopSrchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ���������������ʶ������� */
    if (NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);
        NAS_LMM_StopStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    /*����RRC_MM_PLMN_SEARCH_STOP_REQ��Ϣ*/
    NAS_EMMC_SendRrcPlmnSrchStopReq();

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchStopCnf(MsgBlock *pMsg)
{

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcPlmnSrchStopCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcPlmnSrchStopCnf_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcPlmnSrchStopCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcPlmnSrchStopCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*����LMM_MMC_STOP_SRCH_CNF��Ϣ*/
    NAS_EMMC_SendMmcStopSrchCnf();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvRrcAreaLostInd(MsgBlock *pMsg )
{
    LRRC_LMM_AREA_LOST_IND_STRU *pstAreaLostIndMsg = NAS_EMMC_NULL_PTR;
    MMC_LMM_AREA_LOST_REASON_UINT32 enAreaLostReason;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcAreaLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcAreaLostInd_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcAreaLostInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcAreaLostInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstAreaLostIndMsg = (LRRC_LMM_AREA_LOST_IND_STRU *)pMsg;

    (VOS_VOID)pstAreaLostIndMsg;

    /*ת��AREA LOST REASON*/
    #if (FEATURE_ON == FEATURE_DSDS)
    if(LRRC_LNAS_RADIO_RESOURCE_AREA_LOST == pstAreaLostIndMsg->enRptMode)
    {
        enAreaLostReason = MMC_LMM_AREA_LOST_REASON_NO_RF;
    }
    else
    #endif
    {
        enAreaLostReason = MMC_LMM_AREA_LOST_REASON_NO_COVERAGE;
    }

    /* �յ�area lost ����*/
    NAS_EMMC_ProcessRrcAreaLostInd();

    /*����ID_EMMC_EMM_COVERAGE_LOST_IND��Ϣ*/
    NAS_EMMC_SendEmmCoverageLostInd();

    /* �����ǰCSFB��ʱ��ʱ�������У�˵����REG-NORMAL̬���ͷŹ������յ�CSFB��
       �������ͷź���С�����ֶ�������ʱӦ����ȥGU��������CSFB */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        /* ֹͣCSFBʱ�Ӷ�ʱ�� */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

        /* ��MMC�ϱ�SERVICEʧ�ܴ�������ȥGU */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
    }

    /*����LMM_MMC_AREA_LOST_IND��Ϣ*/
    NAS_EMMC_SendMmcAreaLostInd(enAreaLostReason);



    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvMmcUserPlmnEndNotify(MsgBlock *pMsg )
{
    VOS_UINT32                                  i = 0;
    NAS_LMM_NETWORK_INFO_STRU                   *pstNetInfo = NAS_LMM_NULL_PTR;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enResult = NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcUserPlmnEndNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_ENTRY);

    (void)pMsg;

     /* ��μ�� */
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMMC_RcvMmcUserPlmnEndNotify:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_HANDLED;
    }

    pstNetInfo = (VOS_VOID*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    NAS_EMM_PUBU_LOG1_NORM("NAS_LMM_PreProcMmcUserPlmnEndNotify:Rej15 TA NUM =, ",
                               pstNetInfo->stForbTaForRej15.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_FUNCTION_LABEL1,
                               pstNetInfo->stForbTaForRej15.ulTaNum);

    for (i = 0; i < pstNetInfo->stForbTaForRej15.ulTaNum; i++)
    {
        /* �ȼ�����ʱ�б�, �������п����ж� */
        enResult = NAS_LMM_AddTaInGradualForbTempTaList(&pstNetInfo->stForbTaForRej15.astTa[i]);
        /* �����ж��Ƿ�Ҫ����Roam Forb�б� */
        if ((NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == enResult)
            && (NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(&pstNetInfo->stForbTaForRej15.astTa[i], &pstNetInfo->stForbTaForRoam)))
        {
            NAS_LMM_AddTaInTaList( &pstNetInfo->stForbTaForRej15.astTa[i],
                                &pstNetInfo->stForbTaForRoam,
                                NAS_MM_MAX_TA_NUM);

        }
    }

    /*ɾ���ܾ�15 TA�б�*/
    NAS_LMM_MEM_SET(&pstNetInfo->stForbTaForRej15, 0, sizeof(NAS_MM_FORB_TA_LIST_STRU));

    /*����û�ָ��������ʶ*/
    NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_NO);

    NAS_EMM_PUBU_LOG1_NORM("NAS_LMM_PreProcMmcUserPlmnEndNotify:FORB TA NUM =, ",
                                  pstNetInfo->stForbTaForRoam.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_FUNCTION_LABEL2,
                                  pstNetInfo->stForbTaForRoam.ulTaNum);

    /*����LRRC_LMM_CELL_SELECTION_CTRL_REQ��Ϣ��RRC*/
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvMmcBgPlmnSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_BG_PLMN_SEARCH_REQ_STRU  *pstMmcMsg = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcBgPlmnSearchReq: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_ENTRY);

    /* ��ڲ������ */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgPlmnSearchReq: input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �����ǰ���ǿ���̬�������˱��������� */
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgPlmnSearchReq: not idle, discard!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }
    pstMmcMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)pMsg;

    /* ��LRRC���ͱ��������� */
    NAS_EMMC_SendRrcBgPlmnSearchReq(pstMmcMsg);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvMmcStopBgPlmnSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *pstMmcMsg;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcStopBgPlmnSearchReq: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcStopBgPlmnSearchReq_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcStopBgPlmnSearchReq: input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcStopBgPlmnSearchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstMmcMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)pMsg;

    /* ��LRRC����ֹͣ���������� */
    NAS_EMMC_SendRrcBgPlmnSearchStopReq(pstMmcMsg);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcBgPlmnSearchCnf: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcBgPlmnSearchCnf_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if (NAS_LMM_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcBgPlmnSearchCnf: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcBgPlmnSearchCnf_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �ṹת�� */
    pLrrcMsg = (LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU *)pMsg;

    /* ����LMM_MMC_BG_PLMN_SEARCH_CNF��Ϣ */
    NAS_EMMC_SendMmcBgPlmnSearchCnf(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchStopCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcBgPlmnSearchStopCnf: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcBgPlmnSearchStopCnf_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcBgPlmnSearchStopCnf: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcBgPlmnSearchStopCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �ṹת�� */
    pLrrcMsg = (LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU *)pMsg;

    /* ����LMM_MMC_STOP_BG_PLMN_SEARCH_CNF��Ϣ */
    NAS_EMMC_SendMmcBgPlmnSearchStopCnf(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvRrcNotCampOnInd(MsgBlock *pMsg)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcNotCampOnInd: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcNotCampOnInd_ENUM
,LNAS_ENTRY);

    (VOS_VOID)pMsg;

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcNotCampOnInd: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcNotCampOnInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �յ�NOT_CAMP_ON����*/
    NAS_EMMC_ProcessRrcNotCampOnInd();

    /* ����ID_EMMC_EMM_COVERAGE_LOST_IND��Ϣ */
    /* NAS_EMMC_SendEmmCoverageLostInd(); */

    /* ����LMM_MMC_NOT_CAMP_ON_IND��Ϣ */
    NAS_EMMC_SendMmcNotCampOnInd();

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvRrcSearchPlmnInfoInd(MsgBlock *pMsg)
{
    LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcSearchPlmnInfoInd: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcSearchPlmnInfoInd_ENUM,LNAS_ENTRY);

    /* ��μ�� */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcSearchPlmnInfoInd: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcSearchPlmnInfoInd_ENUM,LNAS_MSG_INVALID);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �ṹת�� */
    pLrrcMsg = (LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU *)pMsg;

    /* ����LMM_MMC_SEARCHED_PLMN_INFO_IND��Ϣ */
    NAS_EMMC_SendMmcSearchPlmnInfoInd(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU    *pstBgSearchCnf = NAS_EMMC_NULL_PTR;

    pstBgSearchCnf = (LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU*)pMsg;

    /* ��MMC���ͱ�����EHRPD�Ľ����Ϣ */
    NAS_EMMC_SendMmcBgSearchHrpdCnf(pstBgSearchCnf);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdStopCnf(MsgBlock *pMsg)
{
    /* ��MMC����ֹͣ������EHRPD��CNF��Ϣ */
    NAS_EMMC_SendMmcStopBgSearchHrpdCnf();

    return NAS_LMM_MSG_HANDLED;
}
#endif
VOS_UINT32  NAS_EMMC_RcvMmcCellSelectionReq(  MsgBlock *pMsg )
{
    MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU    *pstCellSelReq;
    LRRC_LNAS_RESEL_TYPE_ENUM_UINT32          ulReselType;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcCellSelectionReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcCellSelectionReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* �ṹת�� */
    pstCellSelReq = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)pMsg;

    if (MMC_LMM_RESEL_SUITABLE == pstCellSelReq->ulSelecType)
    {
        NAS_LMM_EMMC_LOG1_NORM("NAS_EMMC_RcvMmcCellSelectionReq: Cell type = ",
                                pstCellSelReq->ulSelecType);
        TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_FUNCTION_LABEL1,
                                pstCellSelReq->ulSelecType);
        ulReselType = LRRC_LNAS_RESEL_SUITABLE;
    }
    else
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcCellSelectionReq:Input Cell type is err! ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }


    /*����RRC_MM_CELL_SELECTION_CTRL_REQ��Ϣ*/
    NAS_EMMC_SendRrcCellSelectionReq(ulReselType);

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32 NAS_EMMC_RcvMmcGsmSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_GSM_SYS_INFO_IND_STRU      *pstGsmSysInfoInd = NAS_EMMC_NULL_PTR;

    /* ���Lģ��ǰ���ڼ���̬���򲻴���GU��SYS_INFO,ֱ�Ӷ���*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcGsmSysInfoInd:LTE is not SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcGsmSysInfoInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    pstGsmSysInfoInd                    = (MMC_LMM_GSM_SYS_INFO_IND_STRU*)pMsg;

    /*����GUϵͳ��Ϣ�е�������Ϣ*/
    NAS_EMMC_GetGuSysInfoAddr()->bitOpRac   = pstGsmSysInfoInd->bitOpRac;
    NAS_EMMC_GetGuSysInfoAddr()->ucRac      = pstGsmSysInfoInd->ucRac;
    NAS_EMMC_GetGuSysInfoAddr()->usLac      = pstGsmSysInfoInd->usLac;
    NAS_EMMC_GetGuSysInfoAddr()->ulCellId   = pstGsmSysInfoInd->ulCellId;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[0];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[1];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[2];

    /*����GSM��ʽ*/
    NAS_EMMC_GetGuSysInfoAddr()->ucRatType  = 0 ;


    /*�յ�GUϵͳ��Ϣ,ֹͣ���е�T3402�Լ�T3411 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

    /* �յ�ϵͳ��Ϣ���ж�LAI�Ƿ����仯 */
    NAS_LMM_SetEmmInfoLaiChangeFlag(NAS_MML_IsCsLaiChanged());

/*lint -e960*/
/* GCF������������3402�����в�ֹͣ3402��Ҳ�������������3402��ʱ����Ȼ���壬
   3411��ʱ���Ȳ��޸ģ��ݻ�����ԭ����ֹͣ���� */
#if (VOS_OS_VER != VOS_WIN32)
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        {
           return NAS_LMM_MSG_HANDLED;
        }
    }
#endif
/*lint +e960*/

    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_LMM_Stop3402Timer();
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(0);

    NAS_EMM_AttResetAttAttempCounter();

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32 NAS_EMMC_RcvMmcUmtsSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_WCDMA_SYS_INFO_IND_STRU    *pstUmtsSysInfoInd = NAS_EMMC_NULL_PTR;

    /* ���Lģ��ǰ���ڼ���̬���򲻴���GU��SYS_INFO,ֱ�Ӷ���*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcUmtsSysInfoInd:LTE is not SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcUmtsSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    pstUmtsSysInfoInd                   = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU*)pMsg;

    /*����GUϵͳ��Ϣ�е�������Ϣ*/
    NAS_EMMC_GetGuSysInfoAddr()->bitOpRac   = pstUmtsSysInfoInd->bitOpRac;
    NAS_EMMC_GetGuSysInfoAddr()->ucRac      = pstUmtsSysInfoInd->ucRac;
    NAS_EMMC_GetGuSysInfoAddr()->usLac      = pstUmtsSysInfoInd->usLac;
    NAS_EMMC_GetGuSysInfoAddr()->ulCellId   = pstUmtsSysInfoInd->ulCellId;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[0];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[1];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[2];

    /*����UMTS��ʽ*/
    NAS_EMMC_GetGuSysInfoAddr()->ucRatType  = 1 ;


    /*�յ�GUϵͳ��Ϣ,ֹͣ���е�T3402�Լ�T3411 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

    /* �յ�ϵͳ��Ϣ���ж�LAI�Ƿ����仯 */
    NAS_LMM_SetEmmInfoLaiChangeFlag(NAS_MML_IsCsLaiChanged());

/*lint -e960*/
/* GCF������������3402�����в�ֹͣ3402��Ҳ�������������3402��ʱ����Ȼ���壬
   3411��ʱ���Ȳ��޸ģ��ݻ�����ԭ����ֹͣ���� */
#if (VOS_OS_VER != VOS_WIN32)
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        {
           return NAS_LMM_MSG_HANDLED;
        }
    }
#endif
/*lint +e960*/

    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,Begin */
    NAS_LMM_Stop3402Timer();
    /* Mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION,2015-07-21,End */

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(0);

    NAS_EMM_AttResetAttAttempCounter();

    return NAS_LMM_MSG_HANDLED;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32  NAS_EMMC_RcvMmcBgSearchHrpdReq(MsgBlock *pMsg)
{
    /* �����ǰ���ǿ���̬�������˱��������� */
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgSearchHrpdReq: not idle, discard!");
        return NAS_LMM_MSG_DISCARD;
    }

    /* ��LRRC���ͱ�����EHRPD������Ϣ */
    NAS_EMMC_SendRrcBgSearchHrpdReq();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvMmcStopBgSearchHrpdReq(MsgBlock *pMsg)
{
    /* ��LRRC����ֹͣ������EHRPD���� */
    NAS_EMMC_SendRrcBgSearchHrpdStopReq();

    return NAS_LMM_MSG_HANDLED;
}
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif









