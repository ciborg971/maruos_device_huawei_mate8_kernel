
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasComm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmlLib.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcSndOm.h"
/* Add by l00324781 for CDMA Iteration 12, 2015-6-8, begin */
#include "NasMmcSndInternalMsg.h"
/* Add by l00324781 for CDMA Iteration 12, 2015-6-8, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_SUSPEND_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************�˴�Ϊ��ϵͳ����ʱ�������õĺ�����ȡ********************************************/
#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ConvertLmmSysChngTypeToMmcType(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
)
{
    switch ( enSysChngType )
    {
        case MMC_LMM_SUS_TYPE_RSL :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLRESELECT;
            break;

        case MMC_LMM_SUS_TYPE_HO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_HANDOVER;
            break;

        case MMC_LMM_SUS_TYPE_CCO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE;
            break;

        case MMC_LMM_SUS_TYPE_REDIR :
            *penSuspendCause = MMC_SUSPEND_CAUSE_REDIRECTION;
            break;

        case MMC_LMM_SUS_TYPE_CCO_REVERSE :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK;
            break;

        default:
            *penSuspendCause = MMC_SUSPEND_CAUSE_BUTT;
            break;
    }
    return;

}



VOS_VOID NAS_MMC_ConvertLmmSysChngDirToMmcType(
    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
    MMC_SUSPEND_DESTINATION_UINT8      *penSuspendDestination,
    MMC_SUSPEND_ORIGEN_UINT8           *penSuspendOrigen
)
{
    switch ( ulSysChngDir )
    {
        case MMC_LMM_SYS_CHNG_DIR_L2W:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_WCDMA;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_L2G:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_GSM;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_G2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_GSM;
            break;

        case MMC_LMM_SYS_CHNG_DIR_W2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_WCDMA;
            break;

        /* ����L2C case�Ĵ�������ΪLTE��Ŀ�ķ�ΪCDMA */
        case MMC_LMM_SYS_CHNG_DIR_L2C:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_HRPD;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        default:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_BUTT;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_BUTT;
            break;
    }

    return;
}
VOS_VOID    NAS_MMC_ConvertLmmSuspendMsgToGUtype(
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendIndMsg,
    RRMM_SUSPEND_IND_ST                *pstGuSuspendIndMsg
)
{
    /* ת��L�Ĺ�������ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLmmSuspendIndMsg->ulSysChngType,&(pstGuSuspendIndMsg->ucSuspendCause));

    /* Lģ�£�SUSPEND��������GU�²�ͬ��ת��һ��SUSPEND������ */
    NAS_MMC_ConvertLmmSysChngDirToMmcType(pstLmmSuspendIndMsg->ulSysChngDir,
                                          &(pstGuSuspendIndMsg->ucSuspendDestination),
                                          &(pstGuSuspendIndMsg->ucSuspendOrigen));

    return;
}


VOS_VOID NAS_MMC_SndLmmEquPlmn_InterSysChangeLte()
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId   = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsSimPlmnIdInDestBcchPlmnList;
    VOS_UINT32                                              ulIsBcchPlmnIdInDestSimPlmnList;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
    PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();

    ulIsSimPlmnIdInDestBcchPlmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    ulIsBcchPlmnIdInDestSimPlmnList = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    /* �ֶ�ģʽ�£�����û�ָ�������粻��EPLMN�б��У���֪ͨLMM��ǰ��EPLMN��ϢΪ�û�ָ��������
       ����֪ͨLMM��ǰEPLMN��Ϣ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        if ( (VOS_FALSE == ulIsSimPlmnIdInDestBcchPlmnList)
          && (VOS_FALSE == ulIsBcchPlmnIdInDestSimPlmnList))
        {
            /* ֻ׼��֪ͨ�û�ָ�������� */
            stSndEquPlmnInfo.ucEquPlmnNum = 1;
            stSndEquPlmnInfo.astEquPlmnAddr[0].ulMcc = pstUserSpecPlmnId->stPlmnId.ulMcc;
            stSndEquPlmnInfo.astEquPlmnAddr[0].ulMnc = pstUserSpecPlmnId->stPlmnId.ulMnc;
        }
    }

    NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
    NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
    NAS_MMC_SndOmEquPlmn();

    return;
}

#endif
VOS_VOID    NAS_MMC_SndSuspendRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if ( RRC_NAS_SUSPEND_SUCCESS == enSuspendRslt)
    {
        ulRslt = MMC_LMM_SUCC;
    }
    else
    {
        ulRslt = MMC_LMM_FAIL;
    }

#endif

    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, UEPS_PID_GAS);
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, WUEPS_PID_WRR);
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendRsp(ulRslt);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRsp:Unexpected Rat Type!");
            break;
    }

}



VOS_VOID    NAS_MMC_SndResumeRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* ����RRMM_RESUME_RSP */
            NAS_MMC_SndAsResumeRsp(WUEPS_PID_WRR);

#if (FEATURE_ON == FEATURE_LTE)
            /* ֪ͨLMM�ָ���� */
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsResumeRsp(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndResumeRsp:Unexpected Rat Type!");
            break;
    }

    return;
}





VOS_VOID    NAS_MMC_BulidResumeMsg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_GSM;
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BulidResumeMsg:Unexpected Rat Type!");
            return;
    }

    pstMsg->ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    pstMsg->ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;

    return;
}



NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendOrigenRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;
#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enRat;
    }

    /* ���ݹ���Ŀ�ķ�����ȡ����ǰ���������� */
    switch(stGuSuspendMsg.ucSuspendOrigen)
    {
        case MMC_SUSPEND_ORIGEN_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;
        case MMC_SUSPEND_ORIGEN_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_ORIGEN_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}
NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendDestinationRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Invalid Event Type!");
            return enRat;
    }

    /* ���ݹ���Ŀ�ķ�����ȡ����ǰ���������� */
    switch(stGuSuspendMsg.ucSuspendDestination)
    {
        case MMC_SUSPEND_DESTINATION_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case MMC_SUSPEND_DESTINATION_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_DESTINATION_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}
MMC_SUSPEND_CAUSE_ENUM_UINT8    NAS_MMC_GetSuspendCause(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause = MMC_SUSPEND_CAUSE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enSuspendCause;
    }

    return enSuspendCause;
}

/* Modify by l00324781 for CDMA Iteration 12, 2015-6-1, begin */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))
VOS_UINT32 NAS_MMC_IsInterSysReselectToHrpd(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            return VOS_FALSE;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return VOS_FALSE;
    }

    if (MMC_SUSPEND_DESTINATION_HRPD == stGuSuspendMsg.ucSuspendDestination)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
#endif
/* Modify by l00324781 for CDMA Iteration 12, 2015-6-1, end */

/* Add by l00324781 for CDMA Iteration 12, 2015-6-8, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_StartResumeTimer_InterSysCellResel
 ��������  : ƴƬ��CLģʽ�£���ϵͳ�л�����LTE��ѡ���ض���HRPD�����У�MME�յ��ڲ�ģ��MM��GMM��SuspendRsp��Ϣ����
           : ���ݲ�ͬ�л����ͣ�������ͬʱ����ʱ��
 �������  : ��
 �������  :
 �� �� ֵ  : VOS_TRUE,��LTE��HRPD���л���VOS_FALSE������LTE��HRPD���л�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_StartResumeTimer_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND, TI_NAS_MMC_WAIT_CMMCA_RESUME_IND_LEN);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
        /* �ض��򣬶�ʱ��ʱ��Ϊ180s */
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN);
        }
        /* ��ѡ����ʱ��ʱ��Ϊ35s  */
        else /* (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg())) */
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN);
        }
#endif

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel
 ��������  : ƴƬ��CLģʽ�£���ϵͳ�л�����LTE��ѡ���ض���HRPD�����У�MME�յ��ڲ�ģ��MM��GMM��ResumeRsp��Ϣ����
           : ���ݲ�ͬ�л����ͣ����Ͳ�ͬ���͵Ĺ��������Ϣ
 �������  : ��
 �������  :
 �� �� ֵ  : VOS_TRUE,��LTE��HRPD���л���VOS_FALSE������LTE��HRPD���л�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (MMC_RESUME_ORIGEN_HRPD == NAS_MMC_GetResumeOrign_InterSysCellResel())
    {
        /* ֪ͨLMM��ǰ�Ѿ��ָ� */
        NAS_MMC_SndLmmResumeNotify();

        /* ����״̬���ɹ��Ľ�� */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

        if (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
        else /* ����ѡ�����ض��� */
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_REDIRECTION, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
#endif

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/* Add by l00324781 for CDMA Iteration 12, 2015-6-8, end */
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

