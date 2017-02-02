

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmlCtx.h"
#include        "NasMmSndOm.h"


#include "NasStkInterface.h"
#include "NasMmEcall.h"
#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC3_C
extern VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID);

/*lint -save -e958 */

VOS_VOID Mm_Cell_S10_E66(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        /*lint -e701*/
        if ((MM_CONST_NUM_7 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & (0x01 << g_MmSsRelReq.ulTi))))
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)(0x01 << g_MmSsRelReq.ulTi);                       /* ����ñ�־λ                             */
        }
        if ((MM_CONST_NUM_7 < g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_15 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & (0x01 << (g_MmSsRelReq.ulTi - 8)))))
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)(0x01 << (g_MmSsRelReq.ulTi - 8));                 /* ����ñ�־λ                             */
        }
        if ((MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* MM��������                               */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E66:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */

            NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
        }


        /*lint +e701*/

    }

    return;
}

VOS_VOID Mm_Cell_S12_E66(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                       )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E66:WARNING: Rcv SS Rel Req error.");
    }
    else
    {
        if ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI == g_MmSsRelReq.ulTi )
          && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
        {
            /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if (( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
             && ( g_MmSsRelReq.ulTi == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }

    }

    return;
}


VOS_VOID Mm_Cell_S24_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        ;                                                                       /* �մ���                                   */
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ����������Bģʽ��ȫ����                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        default:
            break;
        }
    }

}
VOS_VOID Mm_Cell_S3_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT8                                ucState;

    ucState                             = g_MmGlobalInfo.ucState;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
            if (MM_GMM_SR_PROC == ucActionType)
            {
                Mm_ComGmmSrCauseHandle(pstGmmActionRstInd->enCause);   /* ����SR����ԭ��ֵ�Ĺ�������               */
            }
        }
        else
        {                                                                       /* ���Ϊ��A+Iģʽ�ĳ���                    */
            if (MM_NULL_PROC != ucActionType)
            {
                Mm_ComCauseHandleAllProc(ucActionType,
                                         pstGmmActionRstInd->enCause); /* ����ԭ��ֵ�Ĵ���                         */

                if ( (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                  && ( (MM_IDLE_NORMAL_SERVICE == ucState)
                    || (MM_IDLE_ATTEMPTING_TO_UPDATE == ucState) ) )
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
                }
            }
        }
    }
}


VOS_VOID Mm_Cell_S24_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;


    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S24_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                          (VOS_UINT8)pstGmmActionRstInd->enCause); /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if (MM_GMM_ATTACH_PROC == ucActionType)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ��ȫ����                  */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;

            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                /* ��LOCATION UPDATE REJECTED״̬���յ�PS��ܾ�ԭ��ֵ15ʱ����CS�򱻾ܵ�ԭ��ֵ���� */
                break;

            default:
                break;
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E16
  Function: ��LOCATION UPDATE REJECTED״̬��,
                �յ�MMCMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* ����ɾ��IMSI�Ĺ�������                   */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E16:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}
VOS_VOID Mm_Cell_S25_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComToNoImsiHandle();

    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
    Mm_ComSetMmState(IMSI_DETACH_INITIATED);


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E16:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E16
  Function: ��IMSI DETACH INITIATED״̬��,
                            �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComToNoImsiHandle();
}

VOS_VOID Mm_Cell_S3_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                         /* ���ý�ֹע��CS��ı�ʶ                   */

                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;              /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
                Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                                 NAS_MML_GetSimCsSecurityCksn());     /* ����MM��Ϣ                               */

                /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
                if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                             & MM_WAIT_CS_DETACH))
                {
                    NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                    /* ����ȴ���־ */
                    g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
                }

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;          /* ����DETACH����                           */

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* ��������TIMER                            */

                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* ���÷���״̬                             */
            }
        }
        else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                             /* ���ý�ֹע��CS��ı�ʶ                   */
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* ����MM��Ϣ                               */

            /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else
        {

        }
    }

}

VOS_VOID Mm_Cell_S4_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                      /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E22:INFO: MmServiceState is MM_DETACHED");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        if ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}
VOS_VOID Mm_Cell_S6_E22(VOS_VOID* pMsg)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;

    enServiceStatus = NAS_MM_GetLauUptNeededCsSrvStatus();

    if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
     || (MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus))
    {
        Mm_Cell_S3_E22(pMsg);
    }
    else
    {
        Mm_Cell_S4_E22(pMsg);
    }
}

VOS_VOID Mm_Cell_S8_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S8_E22:INFO: MmServiceState is MM_NO_IMSI");

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    }
}
VOS_VOID Mm_Cell_S9_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        /* ͣ�ȴ�������ʱ�� */
        Mm_TimerStop(MM_TIMER_T3218);

        /* �ڼ�Ȩ�����У��������Ȩ��־��Ϣ */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* ֹͣ������ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(IMSI_DETACH_PENDING);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_PENDING");
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */

                if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
                {
                    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
                }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                  /* ����DETACH����                           */

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                        g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* ����MM��Ϣ                               */

            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));                  /* ��дMobileID                             */

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);

            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }

    }
}
VOS_VOID Mm_Cell_S12_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                                g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;              /* ����DETACH����                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                /* �����ȴ�������� */
                return;
            }

            /* ֹͣWAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ״̬�ı�����ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */

            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                         /* ��������TIMER                            */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
}

VOS_VOID Mm_Cell_S14_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */

        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                         g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();

        }
        else
        {

            Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                      /* ����DETACH����                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


            /* �Ƚ����ɹ����ٷ���IMSI DETACH */
        }
    }
}
VOS_VOID Mm_Cell_S0_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                     /* ����MM��Ϣ                               */

    Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E23:NORMAL: STATUS is MM_STATE_NULL");
}
VOS_VOID Mm_Cell_S3_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

#if (FEATURE_ON == FEATURE_LTE)

    /* �����ǰפ��LTE,��ֱ�ӻظ��ػ� */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();                                                 /* ��MMC����MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

        return;
    }
#endif

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);

            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }

    }
    else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();                                                 /* ��MMC����MMCMM_POWER_OFF_CNF             */

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

    }
    else
    {
    }
    return;
}
VOS_VOID Mm_Cell_S9_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
            Mm_TimerStart(MM_TIMER_T3240);
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
VOS_VOID Mm_Cell_S12_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
VOS_VOID Mm_Cell_S14_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* ����������ʱ��                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */

                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S22_E23
  Function: WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��06��01��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥA32D10964�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_NEED_DELAY;                        /* ����DETACH����                           */
    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
}
/*******************************************************************************
  Module:   Mm_Cell_S25_E23
  Function: ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */
}
VOS_UINT32 NAS_MM_IsNeedStopT3213_EstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT != ulResult)
     && (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO != ulResult)
     && (RRC_EST_RJ_RA_FAIL != ulResult)
     && (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO != ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

VOS_VOID Mm_Cell_S22_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*                                      pRrcEstCnf;
    VOS_UINT8                                               ucTiValidFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsGsmOnlyEstCnfRslt;
    VOS_UINT32                                  ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ucTiValidFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;



    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);


    /* ����ǰ�����CS��ȥע�� */
    if (VOS_TRUE == NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(pRrcEstCnf->ulResult))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrcEstCnf);

        return;
    }



    if (NAS_MM_IsNeedStopT3213_EstCnf(pRrcEstCnf->ulResult))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        Mm_TimerStop(MM_TIMER_T3213);                                           /* ֹͣ�������ʧ�ܵĹ��� */
    }

    if ((RRC_EST_SUCCESS != pRrcEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrcEstCnf->ulResult))
    {
        /*���PS ONLY����ֱ�ӽ���limit service*/
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComCheckDelayMmConn(MM_FALSE);

#if (FEATURE_ON == FEATURE_ECALL)
            /* PS ONLY��ECALL ONLYģʽ�²�����CS������attach���*/
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            return;
        }
    }

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION PRESENT!");
        }

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        Mm_TimerStart(MM_TIMER_T3210);                                          /* ����������ʱ��                           */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* �������������Ѵ���                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR���ӽ����ɹ�                           */
        Mm_ComSetMmState(LOCATION_UPDATING_INITIATED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION ESTING!");
        break;

    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:


    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        /* ����2G�����´�����ԭ��RRC_EST_RANDOM_ACCESS_REJECT */
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pRrcEstCnf->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
         && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt))
        {
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;

            /* ������������������������ʧ�ܳ��� */
            if (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                Mm_TimerStop(MM_TIMER_T3213);
                Mm_TimerStart(MM_TIMER_T3213);                                  /* ����T3213 */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                break;
            }

            Mm_TimerStop(MM_TIMER_T3213);                                       /* ֹͣ�������ʧ�ܵĹ��� */
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;

            if ( (VOS_TRUE == ulIsTestCard)
              && ((RRC_EST_RANDOM_ACCESS_REJECT == pRrcEstCnf->ulResult)
               || (RRC_EST_RJ_RA_FAIL == pRrcEstCnf->ulResult)) )
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }

        NAS_MM_ProcLuAttemptCounter(pRrcEstCnf->ulResult);


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,�Ҹ���״̬ΪU1��ʱ��         */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                              MM_MMC_LU_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); */           /* ��MMC����MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* ��MMC����MMCMM_LU_RESULT_IND             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn());
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
                g_T3211Flag = 1;
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* GSM�½���ʧ�ܣ�����RR_CONNECTION_FAILURE����, W�½���ʧ�ܣ��������̲��ı� */

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* ��U2�Ĺ������� */
                Mm_ComToU2Handle();

                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();

            NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(pRrcEstCnf->ulResult));
        }


        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */

             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_ACCESS_BARRED:
        /* ����2G�����´�����ԭ��RRC_EST_IMMEDIATE_ASSIGN_REJECT */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && (RRC_EST_IMMEDIATE_ASSIGN_REJECT == pRrcEstCnf->ulResult) )
        {
            break;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt++;

        if ((RRC_EST_REGISTER_ACCESS_BARRED == pRrcEstCnf->ulResult)
         || (RRC_EST_ACCESS_BARRED          == pRrcEstCnf->ulResult))
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* ��MMC����MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        }
        else
        {


            /* ����ָ�ɾܾ���ɾ��EPLMN */

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);                       /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");

        if (MM_FALSE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                                       /* û�еȴ���CC��������Ҫ������MM����       */
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���ӽ���ʧ��                           */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;

    case RRC_EST_RJ_T3122_RUNNING :

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);


        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);

        break;


    case RRC_EST_RJ_NO_RF:
        NAS_MM_ProcLauEstCnfNoRf();
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING:  Result Abnormal");
        break;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

}

VOS_VOID Mm_Cell_S25_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*      pRrcEstCnf;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;
    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:
        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION PRESENT!");
            return;
        }

        Mm_TimerStart(MM_TIMER_T3220);                                          /* ����T3220                                */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* �������������Ѵ���                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S25_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR���ӽ����ɹ�                           */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION ESTING!");
        break;
    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_ACCESS_BARRED:

    case RRC_EST_OTHER_ACCESS_BARRED:

    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CELL_BAR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:

    case RRC_EST_RJ_NO_RF:

    case RRC_EST_RJ_T3122_RUNNING:

    case RRC_EST_RJ_INTER_RAT:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        /* �����������ޣ����ñ�־λ */
        if (RRC_EST_REGISTER_ACCESS_BARRED  == pRrcEstCnf->ulResult)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }

        /* �ǽ������в���������ע���Ѱ����� */
        if  (((RRC_EST_ACCESS_BARRED  == pRrcEstCnf->ulResult)
           || (RRC_EST_RJ_CELL_BAR == pRrcEstCnf->ulResult))
          && (MMCC_EMERGENCY_CALL   !=  g_MmCcEstReq.ulCallType))
        {
            NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }


        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */
            Mm_SndMmcPowerOffCnf();                                             /* ��MMC����MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: Result Abnormal");
        break;
    }

}
VOS_VOID Mm_Cell_S22_E33(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucValidFlg;
    RRMM_REL_IND_STRU                   *pMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRst;
    MM_LAI_STRU                        *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCampLaiInfo  = VOS_NULL_PTR;

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;
    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        ucRst = NAS_MM_RetryCurrentProcedureCheck(pMsg->ulRelCause,
                    pMsg->ulRrcConnStatus);
        if (VOS_TRUE == ucRst)
        {
            /* LAU���յ�ϵͳ��Ϣ�������·��� */
            g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* ��CS�����ڽ���CS������ʱ,���PS������Ҫ���ͷ����ڽ�����PS������,
           ��������������ͷ��������ڽ���������,�Ӷ���Ӱ�쵽CS���ҵ��.
           Ϊ�����������,�涨��������½�����NAS���͵������ͷ�ָʾ�е�
           ԭ��ֵ��ΪRRC_REL_CAUSE_NAS_REL_SUCCESS,MM���յ���ԭ��ֵ���ͷ�
           ָʾ֮����Ϊ����ʧ��,�����ȴ�����������ϱ�ϵͳ��Ϣ,���·�������.*/
        if (RRC_REL_CAUSE_NAS_REL_SUCCESS == pMsg->ulRelCause)
        {
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            /* �������LU���� */
            if (MM_FALSE == Mm_ComChkLu())
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
            }
        }
        else
        {

            /*���PS ONLY����ֱ�ӽ���limit service*/
            if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
            {
                 Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

                 NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                 Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                 PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                 Mm_ComCheckDelayMmConn(MM_FALSE);

#if (FEATURE_ON == FEATURE_ECALL)
                /* PS ONLY��ECALL ONLYģʽ�²�����CS������attach���*/
                if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
                {
                    return;
                }
#endif
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
                return;
            }



            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }


            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

            if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
            {
                NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(pMsg->ulRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E33:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* ��U2�Ĺ������� */
                Mm_ComToU2Handle();


                /* T3212��ʱ���������� */
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS);

            }

            NAS_MM_SndMmcRrConn_RcvRelInd();

            Mm_ComCheckDelayMmConn(MM_FALSE);
        }

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: ulRelCause Abnormal");
    }
}
VOS_VOID Mm_Cell_S23_E33(VOS_VOID* pMsg)
{
    RRMM_REL_IND_STRU*                                      pRrcRelInd;
    VOS_UINT8                                               ucTiValidFlg = MM_TRUE;
    VOS_UINT8                                               ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                                               ucRst;
    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    pRrcRelInd = (RRMM_REL_IND_STRU*)pMsg;

    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*Ǩ��״̬��limit service*/
        /*���ñ�־Attach not allow*/
        /*ָʾ�ϲ�ҵ��ʧ��*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrcRelInd->ulRelCause,
                pRrcRelInd->ulRrcConnStatus);
    if (VOS_TRUE == ucRst)
    {
        /* LAU���յ�ϵͳ��Ϣ�������·��� */
        g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        return;
    }


    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

    NAS_MM_UpdateLauRetryFlg_RcvRelInd(pRrcRelInd);



    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* ��Ҫ���MM�����GMM��causeֵ */
    Mm_ComProcCauseClear();

    /* ����ǰ�����CS��ȥע�� */
    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();
    }
}

VOS_VOID Mm_Cell_S24_E33(VOS_VOID* pMsg)
{
    VOS_UINT8                   ucOldCsUpdateStatus;
    VOS_UINT8                   ucTempCsUpdateStatus;
    VOS_UINT8                   ucTiValidFlg = MM_TRUE;
    VOS_UINT8                   ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    NAS_MM_ClearAuthInfo();

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ֹͣT3240                                */


    ucOldCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                             /* ����ԭ��ֵ�Ĺ�������                     */
    ucTempCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    NAS_MML_SetCsUpdateStatus(ucOldCsUpdateStatus);

    NAS_MML_SetCsUpdateStatus(ucTempCsUpdateStatus);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();

    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_ComCheckDelayDetach();
}

VOS_VOID  Mm_Cell_S25_E33( VOS_VOID* pMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg = Mm_RcvRrcRelInd(pMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E33:WARNING: ulRelCause Abnormal");
    }
    return;
}
VOS_VOID Mm_Cell_S26_E33(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }
    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* ֹͣT3220                                */
    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                          NAS_MML_GetSimCsSecurityCksn());

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E33:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* ��Ҫ���MM�����GMM��causeֵ */
    Mm_ComProcCauseClear();
}

VOS_VOID Mm_Cell_S23_E51(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_T3210);                                               /* ֹͣT3210                                */

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);          /* ��¼���̺�ԭ��ֵ                         */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_TimerStart(MM_TIMER_T3240);                                              /* ����T3240                                */
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {                                                                           /* �ж�LU Counter�Ƿ�С��4                  */
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged()) &&
            (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* �ж�LAI�Ƿ�δ�ı�,�Ҹ���״̬ΪU1         */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    }

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E51:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
}
VOS_VOID Mm_Cell_S3_E52(VOS_VOID* pMsg)
{
    /* AT&T ��������GSM-BTR-1-0644��GSM-BTR-1-0650��GSM-BTR-1-0652
       ��GSM-BTR-1-0656Ҫ������ģʽII��CS lau����#17��PS attach�ɹ���
       MM T3211��ʱ����ʱCS��lau����#17��Ҫ��PS��Ҫ��rau,�ó���MM��Ҫ֪ͨGMM��RAU*/
    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
      && (MM_NET_MODE_II == g_MmGlobalInfo.ucNewNtMod))
    {
        NAS_MM_SndGmmT3211ExpiredNotify(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    }

    if (g_MmGlobalInfo.LuInfo.ucLuType >= MM_IE_LUT_TYPE_BUTT)
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
    }

    Mm_ComLuOnly();                                                             /* ����LU REQ                               */
}


VOS_VOID Mm_Cell_S9_E52(VOS_VOID* pMsg)
{
    Mm_TimerStart(MM_TIMER_T3211);
}


VOS_VOID Mm_Cell_S1_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;

        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }
        return;
    }

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }

        if (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;                      /* ����T3212����ı�ʶ                      */
    }


    /* T3212��ʱ����ʱ��ATTEMPT 2 UPDATE״̬����Ҫ���COUNTERֵ */
    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }
}
VOS_VOID Mm_Cell_S3_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    /* ����ģʽI�£����GMM�Ѿ�ע��������ڽ���ע�ᣬT3212������
    GCF44.2.1.2.8 */
    /* �˴��Ӳ��Կ��ж���Ϊ����GCF����ʱ��������LAU��������������Ҫ����LAU */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
          && (MM_NET_MODE_I    == g_MmGlobalInfo.ucNtMod))
        {
            if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
            {
                return;
            }
        }
    }

    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
             g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;           /* ����LU����                               */
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
    }
}
VOS_VOID Mm_Cell_S5_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* ����LU����                               */
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����                               */
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
    }

    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;

}
VOS_VOID Mm_Cell_S6_E54(VOS_VOID* pMsg)
{
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult;

    enEstCnfResult = NAS_MM_GetEstCnfResult();

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 24008 4.4.4.9������:
        c)  Random access failure (A/Gb mode only)
        Timer T3213 is started. When it expires the procedure is attempted again if still necessary.
        NOTE 1: As specified in 3GPP TS 45.008 [34], a cell reselection then takes place, with return to
        the cell inhibited for 5 seconds if there is at least one other suitable cell. Typically the
        selection process will take the mobile station back to the cell where the random access failed
        after 5 seconds.
        If at the expiry of timer T3213 a new cell has not been selected due to the lack of
        valid information (see 3GPP TS 45.008 [34]), the mobile station may as an option delay
        the repeated attempt for up to 8 seconds to allow cell re-selection to take place.
        In this case the procedure is attempted as soon as a new cell has been selected or
        the mobile station has concluded that no other cell can be selected.
        */
        if((VOS_TRUE == GMM_IsGasCellReselect())
        || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
        || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult))
        {
            if(g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                Mm_TimerStart(MM_TIMER_T3213);
            }
            else
            {
                Mm_TimerStart(MM_TIMER_T3211);
            }
        }
        else
        {
            Mm_ComLuOnly();
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
        }

        if ( (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
          || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult) )
        {
            NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
        }
    }
}

VOS_VOID Mm_Cell_S26_E58(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* ֹͣT3220                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E58:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
}

/*******************************************************************************
  Module:   Mm_Cell_S24_E60
  Function: ��LOCATION UPDATE REJECTED״̬��,���յ�T3240����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E60(VOS_VOID* pMsg)
{
    Mm_T3240Expire();
}


VOS_VOID Mm_Cell_S23_E45(VOS_VOID* pMsg)
{
    MM_LAI_STRU                                             stCurLai;
    NAS_MML_LAI_STRU                                       *pstCurrCampLai = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucLacChangeFlg;
    NAS_MML_LAI_STRU                                       *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnAddr = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stTempEplmnAddr;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                        *pstEmergencyNumList;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    ucLacChangeFlg                              = VOS_FALSE;
    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;


    PS_MEM_SET(&stTempEplmnAddr, 0x00, sizeof(stTempEplmnAddr));

    if (MM_TRUE == g_MmMsgLuAccpt.ucEmcFlg)
    {
        pstEmergencyNumList->ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }

    else if (0 != pstEmergencyNumList->ucEmergencyNumber)
    {

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstEmergencyNumList->ulMcc, pstCurrCampLai->stPlmnId.ulMcc))
        {
            pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

            for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
            {
                pstEmergencyNumList->aucEmergencyList[i].ucCategory = 0xFF;

                for (j = 0; j < NAS_MML_EMERGENCY_NUM_MAX_LEN; j++)
                {
                    pstEmergencyNumList->aucEmergencyList[i].aucEmcNum[j] = 0xFF;
                }
            }

            pstEmergencyNumList->ucEmergencyNumber = 0;
        }

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else
    {
    }

    if (VOS_FALSE ==  MM_ComCmpLai(g_MmMsgLuAccpt.MmIeLAI.IeLai, stCurLai))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S23_E45:WARNING: LU ACCEPTED LAI ERROR!");
        ucLacChangeFlg = VOS_TRUE;
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3210);

    /* ֹͣT3212��ʱ�������ظ�Ϊ���õ�Ĭ��ʱ�� */
    Mm_TimerStop(MM_TIMER_T3212);

    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);


    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                        /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E45:INFO: MmServiceState is MM_NORMAL_SERVICE");
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;

    /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
    g_MmGlobalInfo.MsCsInfo.ucOldRac
        = NAS_MML_GetCurrCampRac();

    pstCsSuccLai->stPlmnId.ulMcc = pstCurrCampLai->stPlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc = pstCurrCampLai->stPlmnId.ulMnc;
    pstCsSuccLai->aucLac[0]      = pstCurrCampLai->aucLac[0];
    pstCsSuccLai->aucLac[1]      = pstCurrCampLai->aucLac[1];

    pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

    /* �����·���non broadcase lai��ϵͳ��Ϣ�Ĳ�ͬ�ҺϷ�����Ҫ����last success lai�������ͷź���Ҫ����lau */
    if ((VOS_TRUE == ucLacChangeFlg)
     && (MM_INVALID_LAI != g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac))
    {
        pstCsSuccLai->stPlmnId.ulMcc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
        pstCsSuccLai->aucLac[0]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
        pstCsSuccLai->aucLac[1]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (0x00FF);

        PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
        g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_TRUE;
    }

    if (MM_TRUE == g_MmMsgLuAccpt.ucMobileIDFlg)
    {
        if (MM_MS_ID_IMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                         & MM_MS_ID_IMSI_PRESENT))
        {                                                                       /* �������IMSI                             */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* ����TMSI��Ч                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_MS_ID_TMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                            & MM_MS_ID_TMSI_PRESENT))
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;/* ����TMSI��Ч                             */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);

            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            Mm_ComMsgTmsiRelocCpltSnd();                                        /* �����෢��TMSI REALLOCATION COMPLETE     */
        }
        else
        {
        }
    }

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);                  /* ���ø���״̬                             */
    Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );                                                         /* ֪ͨRRC,MM��Attach״̬                   */
    /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
    }
    /* Modified by h00313353 for iteration 9, 2015-2-4, end */




    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;



    /* LAU�ɹ�������EPLMN/RPLMN */

    /* �������·���EPLMN�б���ɾ����Ч ����ֹ�Ͳ��������ε����� */
    if ( MM_TRUE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        /* ����EPlmn��Ϣ�б�  */
        NAS_MM_GenerateEPlmnInfo(g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                 g_MmMsgLuAccpt.MmIePlmnList.aPlmnId,
                                 &stTempEplmnAddr);
    }
    else
    {
        stTempEplmnAddr.ucEquPlmnNum = 0x1;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
    }

    pstEplmnAddr = NAS_MML_GetEquPlmnList();


    /* ��EPLMN���浽MMLȫ�ֱ��� */
    PS_MEM_CPY(pstEplmnAddr, &stTempEplmnAddr, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    /* ��EPLMN���µ�NV�� */
    NAS_MM_WriteEplmnNvim(pstEplmnAddr);


    if (VOS_TRUE == NAS_MM_IsGURplmnChanged(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType()))
    {
        /* ����RPlmn��Ϣ��ȫ�ֱ����� */
        NAS_MML_UpdateGURplmn(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MM_WriteRplmnWithRatNvim(NAS_MML_GetRplmnCfg());
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_SUCCESS,
                                NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                             NAS_MML_REG_FAIL_CAUSE_NULL);


    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);                   /* ��¼���̺�ԭ��ֵ                         */

    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
    {
        g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
    }


    g_MmSubLyrShare.MmShare.ucSpecProFlg = MM_UPDATED_SPECIFIC_PROCEDURE;

    if (MM_TRUE == g_MmMsgLuAccpt.ucFollowOFlg)
    {                                                                           /* �����Follow On����                      */
        Mm_ComFollowOnProc();                                                   /* ����Follow On�Ĺ�������                  */
    }
    else
    {
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E45:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ֹͣT3240                                */
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulDeactiveIsrFlg = NAS_MM_IsNeedDeactiveIsrAfterLau();
    if (VOS_TRUE == ulDeactiveIsrFlg)
    {
        /* ȥ����ISR,����TINֵΪP-TMSI */
        NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif


}



NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_MM_ConvertMmLuTypeToStkLuType (LAU_TYPE_ENUM_UINT8 enMmLuType)
{
    switch (enMmLuType)
    {
        case MM_IE_LUT_NORMAL_LU:
             return NAS_STK_LUT_NORMAL_LU;

        case MM_IE_LUT_PERIODIC_UPDATING:
             return NAS_STK_LUT_PERIODIC_UPDATING;

        case MM_IE_LUT_IMSI_ATTACH:
             return NAS_STK_LUT_IMSI_ATTACH;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmLuTypeToStkLuType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}


/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_MM_ConvertMmRatTypeToStkRatType (NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType)
{
    switch (enMmRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmRatTypeToStkRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */


VOS_VOID NAS_MM_SndStkLauRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstLai = VOS_NULL_PTR;

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MM_ERR_LOG("NAS_MM_ReportStkLauRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstLai      =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mcc = pstLai->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mnc = pstLai->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.usLac           = (pstLai->aucLac[0] << 8) | (pstLai->aucLac[1]);

    pstMsg->stNetworkRejectionEvent.enRejType                             = NAS_STK_LAU_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                                 = NAS_MM_ConvertMmRatTypeToStkRatType(pstLai->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode                           = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType                    = NAS_MM_ConvertMmLuTypeToStkLuType(NAS_MM_GetLuType());

    pstMsg->ulMsgName                                                     = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstMsg))
    {
        MM_ERR_LOG("NAS_MM_SndStkLauRej: PS_SEND_MSG ERROR");
    }

    return;
}


VOS_VOID Mm_Cell_S23_E46(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                              ulT3412StatusChgNeedRegFlg;
#endif

    g_MmGlobalInfo.ucRejectCause = g_MmMsgLuRjct.MmIeRejCause.ucRejCause;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    Mm_TimerStop(MM_TIMER_T3210);                                               /* ֹͣT3210                                */
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */
    Mm_ComSaveProcAndCauseVal(MM_LU_PROC,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);           /* ��¼���̺�ԭ��ֵ                         */

    NAS_MM_SndStkLauRej(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_REJECT,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    switch(g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        /* ����CS����Ч��һ��Ҫ���յ��ܾ�ԭ��ֵʱ����
           ��ΪGMM����GMM��Ϣʱ���жϴ˱�־ */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        break;
    default:
        if ((g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX)
         && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
        }
#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
            /*
            Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS
            should set the attempt counter to 4.
            */
        if (   (NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || ( (g_MmMsgLuRjct.MmIeRejCause.ucRejCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
              && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) )
            )
        {
            /* now only WAS and WTTF support REL-6 */
            /* WCDMA/GSM���޸�Ϊ4��:
                3GPP 24008 4.4.4.9 Abnormal cases on the mobile station side:
                g)Location updating reject, other causes than those treated in subclause 4.4.4.7,
                and cases of MM cause values #22 and #25, if considered as abnormal cases according to subclause 4.4.4.7
                Upon reception of the cause codes #22, # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.
            */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }
#endif

        /* ����Ҫ��������ʱ���Ѵ����޸�Ϊ4�� */
        if (VOS_FALSE == NAS_MM_IsLauRejNeedRetry(g_MmMsgLuRjct.MmIeRejCause.ucRejCause))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* �ж�LU Counter�Ƿ�С��4                  */
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* �ж�LAI�Ƿ�δ�ı�,�Ҹ���״̬ΪU1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */

            /* Steering of Roaming ���� */
            /* SOR ����: 4������ʧ��,���������������פ���ڱ��ܾ������磬�ն���Ҫ�ٳ���һ��ע�� */



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        }
        break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function����ȥ����ISR������
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
    }

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if (VOS_TRUE == ulT3412StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif
    NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                g_MmGlobalInfo.usCauseVal);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             g_MmGlobalInfo.usCauseVal);
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E46:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
    Mm_TimerStart(MM_TIMER_T3240);                                              /* ֹͣT3240                                */
}
VOS_VOID Mm_Cell_S0_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
    }

    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
}
VOS_VOID Mm_Cell_S1_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucRet;

    ucRet = Mm_RcvMmcAttachReq( pMsg );
    if (MM_FALSE == ucRet)
    {
    }
    else
    {

        /*������״̬��Ҫֱ�ӻظ����*/
        if (( MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
#if (!defined(__PS_WIN32_RECUR__)) && ( VOS_WIN32 != VOS_OS_VER )
            || ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
#endif
            )
        {
            /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* ɾ��ԭ���˴�����״̬�ϱ�*/
        }
        else
        {
        }
    }
}
VOS_VOID Mm_Cell_S4_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    MMCMM_ATTACH_REQ_STRU                      *pRcvMsg             = VOS_NULL_PTR;
    VOS_UINT8                                   ucPsAttachAllow;
    VOS_UINT8                                   ucSimPsRegStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucPsRestrictRegisterFlg;

    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    ucPsRestrictRegisterFlg = NAS_MML_GetPsRestrictRegisterFlg();

    pRcvMsg = (MMCMM_ATTACH_REQ_STRU*)pMsg;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (VOS_TRUE == ucSimPsRegStatus)
         && (VOS_FALSE == ucPsRestrictRegisterFlg)
         && ((VOS_TRUE == ucPsAttachAllow)
          || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pRcvMsg->enAttachType)))
        {                                                                       /* ����ģʽI                                */
        }
        else
        {                                                                       /* ����ģʽII                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
                {
                    /*��ǰС����barʱ��ֱ�ӻظ�MMCMM_ATTACH_CNF,����ȴ�ATTACH�����־λ */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* ��MMC����MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);


                    return;
                }

                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        /* ��ǰ���update״̬��U1״̬��ֱ�ӻظ�MMCMM_ATTACH_CNF,����ȴ�ATTACH�����־λ */

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */

                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */

                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
            }
        }

    }
}


VOS_VOID Mm_Cell_S19_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucRet = Mm_RcvMmcAttachReq(pMsg);

    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽI                                */
            ;
        }
        else
        {                                                                       /* ����ģʽII                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S19_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");
                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S19_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */
                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S1_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU  *pRcvMsg;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        pRcvMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pRcvMsg->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_NULL:
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S1_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}




VOS_VOID Mm_Cell_S22_E1(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcStartReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_ComInit();                                                           /* ȫ�ֱ�����ʼ��                           */
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
}
VOS_VOID Mm_Cell_S9_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                               ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
        if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                & MM_WAIT_CS_ATTACH))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
    }
}
VOS_VOID Mm_Cell_S3_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E12:INFO: MmLikeB is MM_TRUE");

                if (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S4_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    VOS_UINT32                          ulCurrMMState;

    ulCurrMMState  = Mm_GetState();

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����Ϊ����Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( (VOS_TRUE               == NAS_MM_IsCsEnableLau())
              && (MM_IDLE_LIMITED_SERVICE == ulCurrMMState) )
            {

                /* λ����û�иı�,����Ҫ���� */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}


VOS_VOID Mm_Cell_S17_E12(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����Ϊ����Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( VOS_TRUE == NAS_MM_IsCsEnableLau() )
            {
                /* λ����û�иı�,����Ҫ���� */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}
VOS_VOID Mm_Cell_S0_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
         g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;

        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {                                                                       /* SIM���ڵĳ���                            */
            NAS_MML_SetSimCsRegStatus(VOS_TRUE);
        }
        else
        {                                                                       /* SIM�����ڵĳ���                          */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        }

        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ԭ״̬                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {                                                                   /* ���ڻ���ϵͳ��Ϣ�ĳ���                   */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM��Ч�ĳ���                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ԭ״̬                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM��Ч�ĳ���                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        default:
            break;
        }
    }
}
VOS_VOID Mm_Cell_S3_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* ����ģʽΪI�ĳ���                        */
                if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                {
                    Mm_TimerStop(MM_TIMER_T3212);                               /* ͣT3212                                  */
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}

VOS_VOID Mm_Cell_S9_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_TRUE != ucRet )
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* ����ģʽΪI�ĳ���                        */
                if (MM_TRUE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E20:INFO: MmLikeB is MM_FALSE");
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
VOS_VOID Mm_Cell_S11_E27(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;

    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if (MM_FALSE == Mm_RcvCcDataReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((pMmCcDataReq->ulTransactionId <= 15)
            && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
        {                                                                       /* TIO ����111������CS����������            */
            Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                            &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);                          /* ��CC����Ϣ������ȥ                       */
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E50
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-04-09    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                       /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = (RRMM_DATA_IND_STRU *) pRcvMsg;            /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ͣT3212                                  */

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                            pRrDataInd->RcvNasMsg.ulNasMsgSize,
                            WUEPS_MEM_NO_WAIT);                                 /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S14_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
               sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);         /* ��ʼ���ڴ�                               */

    PS_MEM_CPY (pucCMMsg,
                &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
                pRrDataInd->RcvNasMsg.ulNasMsgSize);                            /* �õ���Ϣ����                             */
    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                            /* �õ�CC��Ϣ�е�TI                         */
    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI))
        && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* ��CC����MMCC_EST_IND                     */
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    return;
}

VOS_VOID Mm_Cell_S22_E5(VOS_VOID* pMsg)
{

    VOS_UINT8  ucTiValidFlg = MM_TRUE;



    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}

VOS_VOID Mm_Cell_S23_E5(VOS_VOID* pMsg)
{


    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* ͣT3210                                  */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */
        if (MMCMM_FORBIDDEN_PLMN ==
            (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN); /* ��¼���̺�ԭ��ֵ                         */
        }
        else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            )
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);   /* ��¼���̺�ԭ��ֵ                         */
        }
        else
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM); /* ��¼���̺�ԭ��ֵ                         */
        }
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);

        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    g_MmGlobalInfo.usCauseVal);
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 g_MmGlobalInfo.usCauseVal);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E5:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}
VOS_VOID Mm_Cell_S23_E22(VOS_VOID* pMsg)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }


    /* ��LAUʱ�������ǰ���������ѽ������ˣ���ֱ�ӷ���DETACH REQ������ */
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return;
        }

        /* �ڼ�Ȩ�����У��������Ȩ��־��Ϣ */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* ֹͣ������ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }


        /* ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        /* ���CS���������Ӵ���                     */
        /* ֹͣLAU�ı�����ʱ��T3210 */
        Mm_TimerStop(MM_TIMER_T3210);
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);                             /* ��д��Ϣ,������Ϣ                        */
        Mm_TimerStart(MM_TIMER_T3220);                                          /* ����T3220                                */
    }

    /* �����ǰ������δ�����ã�����յ�EST_CNF�����DETACH�Ĵ���  */

    return;

}

VOS_VOID Mm_Cell_S24_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;



    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */

        /* ���ע�������¿���Ч���򷵻�  */
        if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
        {
            NAS_MM_LocalDetach();
            return;
        }

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                            g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));


            /* ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
}


VOS_VOID Mm_Cell_S6_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    if (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E14
  Function: ��MM NULL״̬��,���յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.08  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E14(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E13
  Function: ��MM NULL״̬��,���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.08  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E13(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

}

VOS_VOID Mm_Cell_S4_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd = VOS_NULL_PTR;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+Iģʽ                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* ���ΪA+Iģʽ                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* ����������Bģʽ                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );
            Mm_ComDelLai();
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}

VOS_VOID Mm_Cell_S5_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    VOS_UINT8                           ucOldUpdateSts;
    VOS_UINT8                           ucTempUpdateSts;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+Iģʽ                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* ���ΪA+Iģʽ                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* ����������Bģʽ                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmServiceState is MM_LIMITED_SERVICE");
            ucOldUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            ucTempUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(ucOldUpdateSts);
            NAS_MML_SetCsUpdateStatus(ucTempUpdateSts);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}


VOS_VOID    Mm_Cell_S6_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* ֪ͨCC����ʧ��                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* NAS�޸Ĳ����ص绰 */


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* �ǽ�������                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
                {
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

                    /* TI�Ϸ�  */
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                    {
                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                  /* ֪ͨCC����ʧ��                           */
                    }
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

                    /* GU��location update needed״̬�յ�cc��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
                    /* MM��unbar to bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
                }
            }
        }
    }
}
VOS_VOID    Mm_Cell_S6_E62( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);            /* ֪ͨSMS����ʧ��                           */
            return;
        }

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
                = NAS_MML_GetCurrNetRatType();

            /* ���CM SERVICE REQUEST�ṹ�� */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &stCmSvcReq);

            /* ���CM SERVICE REQUEST ��Ϣ */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );
            }

            /* ��¼���ڽ�����MM���ӵ�TI��PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;

            /* ����������ʱ�� */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* ֪ͨMMC/GMM��CS���ҵ���Ѿ����� */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* ��¼״̬ */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

            /* ����ҵ����ڱ�־ */
            NAS_MM_UpdateCsServiceBufferStatusFlg();
            NAS_MM_UpdateCsServiceConnStatusFlg();
        }
        else
        {
            /* GU��location update needed״̬�յ�sms��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM��access bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                /* ֪ͨSMS����ʧ��                           */
        }
    }
}


VOS_VOID    Mm_Cell_S6_E65( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӷ��� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

           /* ������������ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            /* ���CM SERVICE REQUEST�ṹ�� */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);

            /* ���CM SERVICE REQUEST ��Ϣ */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if (VOS_NULL_PTR == pucCmSvcReq)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
            }

            /* ��¼���ڽ�����MM���ӵ�TI��PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = (VOS_UINT8)g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;

            /* ����������ʱ�� */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* ��¼״̬ */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
        else
        {
            /* ==>A32D12640 */
            /* GU��location update needed״̬�յ�ss��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM��access bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }
}

VOS_VOID    Mm_Cell_S5_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)


        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* ֪ͨCC����ʧ��                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            /* �����ǰפ��LTE,��Ҳ���Է�����ͨ���� */

            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq =
            g_MmGlobalInfo.ucState;                                             /* ��¼�յ���������ʱ��״̬                 */

        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* �ǽ�������                               */
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                /* ���ǽ�������                             */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* �Ѿ�����һ��������MM���ӽ�������         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* ֪ͨCC����ʧ��                           */

                    return;
                }

                if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    /* �������ز���ԭ��ֵ */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
                    return;
                }

                /* ������Ϣ */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
                {
                    NAS_MM_SndGmmRegisterInit();                                    /* ֪ͨGMM����ע��                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S0_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pMsg) )
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S0_E22:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        switch ( pMmcDetachReq->enDetachType )
        {
        case MMC_MM_CS_DETACH:
        case MMC_MM_PS_CS_DETACH:
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);

                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            if ( MM_STATE_NULL != Mm_GetState() )
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S0_E22:WARNING: Detach Cause Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E59
  Function: ��MM NULL״̬��,�յ�T3230����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.28  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E59(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3230);                                               /* ֹͣTIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E60
  Function: ��MM NULL״̬��,�յ�T3240����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E60(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3240);                                               /* ֹͣTIMER3230                            */
}
VOS_VOID Mm_Cell_S11_E36(VOS_VOID* pMsg)
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComAuthenRcvAuthenReq();
}
VOS_VOID Mm_Cell_S11_E37(VOS_VOID* pMsg)
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣT3240                                  */

    Mm_TimerStart( MM_TIMER_T3240 );                                            /* ����T3240                                */

    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);


    Mm_ComAuthenRcvAuthenRej();                                                 /* �յ�AUTHEN REJ�Ĵ���                     */

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
}


VOS_VOID Mm_Cell_S11_E38(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComIdentity();                                                           /* IDENTITY���̵Ĵ���                       */

    return;
}
VOS_VOID Mm_Cell_S11_E39(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComTmsiReloc();
    return;
}


VOS_VOID Mm_Cell_S11_E43(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComInfo();                                                               /* MM INFO���̵Ĵ���                        */
    return;
}
VOS_VOID Mm_Cell_S11_E44(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    return;
}


VOS_VOID Mm_Cell_S11_E47(VOS_VOID* pMsg)
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));


    MM_Fill_IE_ClassMark2(aucClassmark2);

    if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        return;
    }
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* ��֧��CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* ��䲢���� MM STATUS ��Ϣ                */
    }
    else
    {                                                                           /* ֧��CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* ��CC����MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}


VOS_VOID    Mm_Cell_S5_E62( VOS_VOID*pMsg )
{


    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);/* ֪ͨSMS����ʧ��                          */
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰפ��LTE,��ֱ�ӻظ�SMSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* ֪ͨSMS����ʧ��                          */

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* �������ز���ԭ��ֵ */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }


    return;
}
VOS_VOID    Mm_Cell_S5_E65( VOS_VOID*pMsg )
{
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* ��ATTEMPT TO UPDATE״̬���Է��𲹳�ҵ�� */
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }

    return;
}


VOS_VOID    Mm_Cell_S22_E24( VOS_VOID*pMsg )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState)
            {
                /* �쳣����:LTE�²���Ǩ�Ƶ��⼸��״̬ */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);                              /* ֪ͨCC����ʧ��                           */

                return;
            }

            /* �����ǰפ��LTE,MM LOCATION_UPDATING_PENDING״̬�յ��������л���ͨ������Ҫ��LMM
               ����ID_MM_LMM_CSFB_SERVICE_START_NOTIFY��tauע�ᱻ��#17 1�Σ�mm��Ǩ��location update pending */
            NAS_MM_RcvCcEstReq_CSFB();
            return;


        }
#endif
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                              /* ֪ͨCC����ʧ��                           */

            return;
        }


        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
               g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
                )
            {
                /* �Ѿ�����һ��������MM���ӽ�������         */
                Mm_SndCcRelInd(
                    g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                        /* ֪ͨCC����ʧ��                           */
            }
            else
            {
                /* ������Ϣ */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E40
  FUNCTION : ��WAIT FOR NETWORK COMMAND ״̬���յ�
                RRMM_DATA_IND(CM SERVICE ACCEPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E40(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */


    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    return;
}


VOS_VOID Mm_Cell_S1_E24(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
        /* ��ǰno rfʱ�յ�ҵ������mm��Ҫ֪ͨmmc�ȴ�����������ͨ������Ҫ����Ч������ҵ������ */
        if (VOS_TRUE == NAS_MM_IsCcServiceNeedTriggerPlmnSearch())
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */
        {
            /*����÷������� */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);        /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            if ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
            {
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* �Ѿ�����һ��������MM���ӽ�������         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* ֪ͨCC����ʧ��                           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;                                     /* ��¼�յ���������ʱ��״̬                 */
                if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
                    ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
                {
                    /* TI���Ϸ�                                 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                      /* ֪ͨCC����ʧ��                           */
                }
                else
                {
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
            }
            else
            {
                Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                     /* ֪ͨCC����ʧ��                           */
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E71
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�TCMM_TEST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E71(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_TEST_REQ_STRU           *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_ACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerPause(MM_TIMER_STOP_ALL);                                       /* ��ͣ����Timer                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ԭ״̬Ǩ��                               */
        Mm_ComSetMmState(TEST_CONTROL_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  TEST_CONTROL_ACTIVE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E71:NORMAL: STATUS is TEST_CONTROL_ACTIVE");
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E72
  FUNCTION : ��TEST_CONTROL_ACTIVE״̬���յ�TCMM_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E72(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_DATA_REQ_STRU          *pTcmmDataReq;

    pTcmmDataReq = ( TCMM_DATA_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "SendTcMsg = %d \r",pTcmmDataReq->SendTcMsg.ulTcMsgSize); */

    Mm_SndRrDataReq(
                pTcmmDataReq->SendTcMsg.ulTcMsgSize,
                &pTcmmDataReq->SendTcMsg.aucTcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��TC����Ϣ������ȥ                       */
}

VOS_VOID Mm_Cell_S9_E73(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    RRMM_DATA_IND_STRU          *pRrmmDataInd;

    pRrmmDataInd = ( RRMM_DATA_IND_STRU* )pRcvMsg;


    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    Mm_SndTcDataInd(
                pRrmmDataInd->RcvNasMsg.ulNasMsgSize,
                pRrmmDataInd->RcvNasMsg.aucNasMsg);
}



VOS_VOID Mm_Cell_S31_E71(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_TEST_REQ_STRU          *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_DEACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
        }
        else
        {
            switch ( g_MmGlobalInfo.ucMmServiceState )
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_NORMAL_SERVICE\r " );           */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");


                if (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }

                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;
            case MM_DETACHED:
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                /*WUEPS_TRACE(MM_LOG_LEVEL_1,                                   */
                /*    "\nMM:ucState = %d\r", g_MmGlobalInfo.ucState);           */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S31_E71:WARNING: g_MmGlobalInfo.ucMmServiceState Abnormal");
                break;
            }
        }
    }

}

VOS_VOID Mm_Cell_S31_E33(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣ��ͷ��ַ                         */
)
{
    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "RRMM_REL_IND = %d \r",RRMM_REL_IND);         */

    Mm_TimerStop( MM_TIMER_T3240 );

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                             /* RR���Ӳ�����                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    /* TC״̬���յ�����������ͷ���Ϣʱ����TC����TCMM_RR_REL_IND */
    NAS_MM_SndTcRrRelInd();
}


/*******************************************************************************
  MODULE   : Mm_Cell_S0_E21
  FUNCTION : ��NULL״̬���յ�MMCMM_COVERAGE_LOST_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.06 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E21(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                        /* �����쳣����                             */
    }

}


/*******************************************************************************
  MODULE   : Mm_Cell_S3_E34
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.06 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E34(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* �����쳣����                             */
    }

}




VOS_VOID Mm_Cell_S25_E24(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */                                                        /* �����쳣����                             */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH );                 /* ֪ͨCC����ʧ��                           */
    }
    return;
}
VOS_VOID Mm_Cell_S22_E13(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT( 0 ); */

        return;
    }



    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*    " \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* Deleted by libin 05-03-22 begin: NAS_IT_BUG_017 */
        /* Mm_SndRrRelReq(); */                                                 /* ��RRC����RRMM_REL_REQ(CS��)              */
        /* Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
        /* Deleted by libin 05-03-22 end */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*    " \nMM:MmServiceState is MM_ATTEMPTING_TO_UPDATE \r " );          */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        /* Modified by libin 05-03-22 begin: NAS_IT_BUG_017 */
        Mm_ComToU2Handle();                                                     /* ����MM��U2�Ĵ���                         */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        /* Modified by libin 05-03-22 end */

    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            /* Modified by libin 05-03-22 begin: NAS_IT_BUG_017 */
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* ��RRC����RRMM_REL_REQ(CS��)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* ����DETACH���̵�ԭ��ֵ����               */
            /* Modified by libin 05-03-22 end */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            /* Modified by libin 05-03-22 begin: NAS_IT_BUG_017 */
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* ��RRC����RRMM_REL_REQ(CS��)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* ����DETACH���̵�ԭ��ֵ����               */
            /* Modified by libin 05-03-22 end */
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
                /* Modified by libin 05-03-22 begin: NAS_IT_BUG_017 */
                Mm_ComNetDetachCauseHandle(
                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);                              /* ��RRC����RRMM_REL_REQ(CS��)              */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pstNetWkDetachInd->ulDetachCause);
                /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd
                ->ulDetachCause); */                                            /* ����DETACH���̵�ԭ��ֵ����               */
                /* Modified by libin 05-03-22 end */
            }
            break;
        default:
            break;
        }
    }
}

VOS_VOID Mm_Cell_S23_E13(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */

        return;
    }



    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* ֹͣT3210                                */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* ֹͣT3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*    " \nMM:MmServiceState is MM_NO_IMSI \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* ֹͣT3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            break;
        default:
            break;
        }
    }
}

VOS_VOID Mm_Cell_S0_E16(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* �����쳣����                             */
        return;
    }

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);


    Mm_ComDelLai();                                                            /* ɾ��LAI     */
    NAS_MML_InitUeIdTmsiInvalid();
    NAS_MML_SetSimCsSecurityCksn(NAS_MML_CKSN_INVALID);


}
VOS_VOID Mm_Cell_S0_E33(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    return;
}
VOS_VOID Mm_Cell_S2_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg                          = Mm_RcvRrcRelInd(pRcvMsg);
    if ( MM_TRUE == ucValidFlg )
    {
        Mm_TimerStop(MM_TIMER_WAIT_CONNECT_REL);

        /* ֪ͨMMC���Ӳ����� */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        /* �ͷ�����MM����,���ڽ���MM���� */
        /* IDLE PLMN SERCH��wait for attach��imsi detach pending��״̬�յ�rel ind��
           �ײ����쳣��CS��Ӧ��δע��ɹ����ͷ����е�MM���ӣ����ز� */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S2_E33:WARNING: ulRelCause Abnormal");
    }
}

VOS_VOID Mm_Cell_S26_E37(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_ComToNoImsiHandle();
    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);


    /* �ж�DETACH�ȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

}



VOS_VOID Mm_Cell_S17_E22(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* �����쳣����                             */

        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pRcvMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        /* ������RAU�����У��յ�DETACH_REQ ��Ϣ��GMM���ᷢ�� DETACH���̣�MM��Ҫ���ñ�־λ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_CS_DETACH;
    }
}

VOS_VOID Mm_Cell_S17_E23(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                       /* �����쳣����                             */

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* �����ǰפ��LTE,��ֱ�ӻظ��ػ� */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */
        Mm_ComSetMmState(MM_NULL);

        return;
    }
#endif

    if (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_NULL);
    }
    else
    {

        Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
    }


    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */
}


VOS_VOID Mm_Cell_S25_E76(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /*A32D10964==>*/
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    if ((MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
      && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));
        Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);
    }
    /*<==A32D10964*/
    switch(g_MmGlobalInfo.ucDetachType)
    {
        case MM_DETACH_CS_POWEROFF:
        /*A32D10964==>*/
        case MM_DETACH_NEED_DELAY:
        /*<==A32D10964*/
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());                     /* ����MM��Ϣ                               */

            Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is  MM_STATE_NULL");
            Mm_TimerStop(MM_TIMER_STOP_ALL);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
            }

            break;
        case MM_DETACH_CS_NORMAL:
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E76:WARNING: Detach type is unexpect.");
            break;

    }
    return;
}

VOS_VOID Mm_Cell_S9_E75(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* WUEPS_ASSERT(0); */
}

VOS_VOID Mm_Cell_S12_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* WUEPS_ASSERT(0); */
    VOS_UINT8 ucCause;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E77:WARNING: Wait for RRMM_EST_CNF expired");

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_RR_CONN_EST_FAIL;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;              /* ��¼Ǩ��֮ǰ��״̬                       */


    if (NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
    {
        /* CC�����RR���ӵĽ���                     */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {                                                                   /* SS�����RR���ӵĽ���                     */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {                                                                   /* SMS�����RR���ӵĽ���                    */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);          /* ֪ͨSMS,MM���ӽ���ʧ��                   */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {                                                                   /* û�����ڽ�����MM���ӣ�������             */

#if (FEATURE_ON == FEATURE_PTM)
        /* �յ�CS PAGING�����ӽ�����ʱ���쳣��¼ */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT);
#endif

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    /* ��Ҫ����LU�����ͷŻ����ҵ�� */
    if (MM_TRUE == Mm_ComChkLu())
    {
        if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */
        }

        if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }

    }


}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E77
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��MM_TIMER_PROTECT_SIGNALLING���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    Mm_RcvRrmmEstCnf();
}

VOS_VOID Mm_Cell_S14_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8 i;
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E77:WARNING: MM_TIMER_PROTECT_SIGNALLING expire at WAIT FOR REESTABLISH(WAIT FOR EST_CNF).");


    /*lint -e701*/
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                   /* �ؽ���MM����                             */
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);       /* ֪ͨCC,MM�����ؽ�ʧ��                    */
        }
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcRelInd( ( i + 8 ),NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);/* ֪ͨCC,MM�����ؽ�ʧ��                    */

        }
    }

    /*lint +e701*/

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    if ( MM_FALSE == Mm_ComChkLu() )
    {

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                            RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */
        }

        if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        }

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


}



VOS_VOID Mm_Cell_S6_E74(VOS_VOID *pRcvMsg)
{
    RRMM_AC_INFO_CHANGE_IND_STRU               *pRrMmAcInfoChgInd;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    pRrMmAcInfoChgInd = (RRMM_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvRrcAcInfoChgInd(pRcvMsg) )
    {
        return;
    }
    if (( RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
     || ( RRC_NAS_T3122_EXPIRE == pRrMmAcInfoChgInd->ulAcChangeInd) )
    {
        if (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
        }

        if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
         && (VOS_FALSE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);

            NAS_MM_SndGmmRegisterInit();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E74:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if (( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1                 */
                if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            }

            if ((g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt < MM_CONST_NUM_4)
             || (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd))
            {
                Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            }

            if (g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt >= MM_CONST_NUM_4)
            {
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
}


VOS_VOID Mm_Cell_S0_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */                                                     /* �����쳣����                             */
        return;
    }
    else
    {
        /* ��Ϣ������ɹ�                         */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* ֪ͨCC����ʧ��                           */
    }
    return;
}

/* Added by wjf for Status for MM 20050127 begin */
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E40
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.11  Status for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E40(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU    Msg;

    Msg.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;

    Mm_ComMsgMmStatusSnd(&Msg);
}
/* Added by wjf for Status for MM 20050127 end */



VOS_VOID Mm_Cell_S31_E1(VOS_VOID* pMsg)
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {


        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        /* Modified by libin agent for MM 20050131 begin */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E1:NORMAL: STATUS is MM_STATE_NULL");
        /* Modified by libin agent for MM 20050131 end */

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* ȫ�ֱ�����ʼ��                           */
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}

VOS_VOID Mm_Cell_S0_E78(VOS_VOID* pMsg)
{
#if 0
    PS_OM_MSG_HEAD_STRU *pNewMsg;
    pNewMsg = (PS_OM_MSG_HEAD_STRU *)pMsg;

    switch (pNewMsg->ulMsgID)
    {
        case AGENT_MM_INQUIRE:
            Mm_RcvMmAgentInquire(pMsg);
            break;
        case MM_TRANS_STATUS_INFO_REQ:
            Mm_SndAgentTransInfo(pNewMsg);
            break;
        default:
            break;
    }
#endif
}


VOS_VOID Mm_Cell_S31_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }


    /* TC״̬���յ��ػ�����ʱ����������REL_REQ */
    if ( g_MmGlobalInfo.ucCsSigConnFlg == MM_CS_SIG_CONN_PRESENT )
    {
        NAS_MM_SndTcRrRelInd();

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                /* ==>A32D12706 */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                Mm_ComSetMmState(IMSI_DETACH_INITIATED);
                /* <==A32D12706 */
            }
            else
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
                Mm_SndMmcPowerOffCnf();
                Mm_ComSetMmState(MM_STATE_NULL);

            }
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* ����������ʱ��                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E79
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��MM_TIMER_PROTECT_CC���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.28  �¹�����
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E79(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

}


VOS_VOID Mm_Cell_S13_E79(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S13_E79:WARNING: MM_TIMER_PROTECT_CC expire at WAIT FOR REESTABLISH(WAIT FOR REEST REQ).");

    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E79:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_ComProcCauseProcess();

    if ( MM_FALSE == Mm_ComChkLu() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);                      /* ֪ͨCC����ʧ��                           */
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E15
  FUNCTION : ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬��GMMMM_LU_INITIATION���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.28  �¹�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E15(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if ( MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* �쳣������                             */
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}



VOS_VOID Mm_Cell_S9_E5(VOS_VOID* pMsg)
{
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoMsg;



    g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

    /* G���ڸ�״̬�յ�ϵͳ��Ϣ��Ԥ�����������ֻ����W���յ�����Ϣ */
    pstSysInfoMsg   = (MMCMM_SYS_INFO_IND_STRU*)pMsg;

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
    /* MM����ͨ���У�PS��bar���ڼ�T3312��ʱ��GMM��֪ͨMM����ʱMM�ὫT3212��ʱ��־
       ��λTRUE,�˺����PS�ִ�barתΪ��bar, MM��Ҫ��T3212��ʱ��־�������
       ���򣬵�ͨ������ʱ��Mm_ComChkLu���� ��⵽�ñ�־λ�󣬻ᷢ��������LU���̡� */
    if (  (VOS_TRUE == pstSysInfoMsg->ucPsChanged2UnBarFlg)
        &&(MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
    {
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
}



VOS_VOID Mm_Cell_S12_E5(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucLaiChange;
    VOS_UINT32                          ulCsServExist;

    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;

    ucLaiChange    = NAS_MML_IsCsLaiChanged();
    ulCsServExist  = Mm_ComJudgeCsServExist();

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == NAS_MML_GetCsRegisterBarToUnBarFlg())
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* פ���������磬�ҵ�ǰ�޽����������� */
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {

        g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

        /* ����פ��������������������������ڽ��������н���פ��������С����״̬δˢ�£�����T3212���쳣
           ֹͣ�����ҽ���������������ϱ���������״̬ */
        if ( (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
          && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
            {
                g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
            }

            return;
        }

        ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange)
         && (VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
        }

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }
    else
    {
        /* ����ϵͳ�л�������ҵ���������з���λ�����ı� */
        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

            /* �ͷ����ӣ��������ͷź����Ƚ���LU/RAU��Ȼ��������������Ϣ */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E50
  FUNCTION : ��MM_CONNECTION_ACTIVE״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      2005.02.02  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E50(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                           /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S10_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }

    /*lint -e701*/
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
        sizeof( VOS_UINT8 ) * pRrDataInd->RcvNasMsg.ulNasMsgSize );                 /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�CC��Ϣ�е�TI                         */
    if ( ( MM_CONST_NUM_7 == ucTI ) || ( MM_CONST_NUM_15 == ucTI ) )
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��CC����MMCC_EST_IND                     */
    }
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC������MM����                           */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��CC����MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else
    {

    }


    /*lint +e701*/

    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    return;
}

VOS_VOID Mm_Cell_S5_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            if (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* ֪ͨL CSFB ������ֹ */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }

                if (MM_IDLE_PLMN_SEARCH == Mm_GetState())
                {
                    NAS_MM_SndMmcCsfbAbortInd();
                }
            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
VOS_VOID Mm_Cell_S32_E80(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* ֪ͨL CSFB ������ֹ */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
VOS_VOID Mm_Cell_S9_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E81
  FUNCTION : ��MM IDLE ATTEMPTING TO UPDATE,WAIT FOR NETWORK COMMAND״̬���յ�
             MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
      1. ��    ��   : 2007��3��9��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥA32D09099����
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmSmsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E81
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAN");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}
VOS_VOID Mm_Cell_S10_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        /*lint -e701*/

        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        /* modified by libin for MM_Review_HW_BUG_030 2005-03-18 begin */
        /*    & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 )))) */
            & (0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ))))
        /* modified by libin for MM_Review_HW_BUG_030 2005-03-18 end */
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if ( ( ( 0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
/* modified by gaoyan for PC-LINT 05-03-15 begin */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT32)(0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ));
/* modified by gaoyan for PC-LINT 05-03-15 end */
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E81
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/

        if ( 0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if ( ( ( 0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
/* modified by gaoyan for PC-LINT 05-03-15 begin */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                &= ~(VOS_UINT32)(0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ));
/* modified by gaoyan for PC-LINT 05-03-15 end */
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSmsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S12_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {
            /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */


#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E81
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


VOS_VOID Mm_Cell_S16_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E80:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E81
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E81:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


/* Added by libin 05-03-28 begin: NAS_IT_BUG_034 */
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E66
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬���յ�MMSS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.03.28  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E66(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)( 0x01 << g_MmSsRelReq.ulTi );                          /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) );                  /* ����ñ�־λ                             */
        }
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                RcvXXEstReq.ulTransactionId == g_MmSsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* ���ò����ڻ����MM���� */
        }
        if ( ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION\r " );      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E66:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        /*lint +e701*/
    }

    return;
}
/* Added by libin 05-03-28 end */

/* Added by libin 05-04-14 begin: NAS_IT_BUG_055 */
/*******************************************************************************
  MODULE   : Mm_Cell_S27_E82
  FUNCTION : ��PROCESS CM SERVICE PROMPT״̬��
             �յ�MM_TIMER_PROTECT_CCBS EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.04.14  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E82(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MM_TIMER_PROTECT_CCBS EXPIRED\r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S27_E82:INFO: MM_TIMER_PROTECT_CCBS EXPIRED");
    MsgMmStatus.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER;  /* Service option temporarily out of order  */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    if ( MM_FALSE == Mm_ComMmConnExist( ) )
    {                                                                           /* û�д��ڵ�MM���� */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
            ucStaOfRcvXXEstReq;                                                 /* ������е�״̬                           */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM��������                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {                                                                           /* �д��ڵ�MM���� */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    }
}



/* Mm_Cell_S27_E33_Handling_REL_CAUSE_NOT_RL_FAILURE����ʹ�ã�ɾ�� */


/* ɾ��S27E33 */


/* Added by libin 05-04-14 end */


VOS_VOID Mm_Cell_S9_E83(VOS_VOID *pRcvMsg)
{
    GRRMM_EST_SAPI3_CNF_ST             *pstEstSapi3Cnf;

    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "Mm_Cell_S9_E83:STATE: WAIT_FOR_OUTGOING_MM_CONNECTION Receive GRRMM_EST_SAPI3_CNF.");

    /* ��Ϣ��� */
    if (MM_IE_PD_SMS_MSG != g_MmGlobalInfo.ucMMConnEstingPD)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_Cell_S9_E83: WARNING: Receive GRRMM_EST_SAPI3_CNF error.");

        return;
    }

    /* ��Ϣ������ɹ� */
    pstEstSapi3Cnf = (GRRMM_EST_SAPI3_CNF_ST*)pRcvMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);  /* ֹͣ����TIMER */

    if (MM_EST_SAPI3_SUCCESS == pstEstSapi3Cnf->ucResult)
    {
        /* ��MM���ӽ����ɹ� */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        /*lint -e701*/
        /* TI С��7 */
        if (MM_CONST_NUM_7 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
        {
            /* ����MM���Ӵ��ڱ�־ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]   |=
                (VOS_UINT8)(0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        }
        else /*TI����7 */
        {
            /* ���� MM ���Ӵ��ڱ�־ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]   |=
                (VOS_UINT8)(0x01 << (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI - 8 ) );
        }
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;  /* ��¼Ǩ��֮ǰ��״̬               */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E83:NORMAL: STATUS is MM_CONNECTION_ACTIVE");

        g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                            = NO_MM_CONN_ESTING;
        Mm_ComCheckDelayMmConn(MM_FALSE);                          /* ����Ƿ��б�������Ҫ������MM���� */

        NAS_MM_UpdateCsServiceConnStatusFlg();

        return;
    }
    else /* SAPI3 ����ʧ�� */
    {
        /* ֪ͨ SMS, MM ���ӽ���ʧ�� */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL);

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "Mm_Cell_S9_E83: ERROR: SAPI3 est fail.");
    }

    g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S6_E86(VOS_VOID *pRcvMsg)
{
    GAS_RR_CHAN_MOD_IND_ST   *pChanMod;
    MMCC_CHANNEL_MODE_ENUM_U32        enMmCcChanMode;

    pChanMod = (GAS_RR_CHAN_MOD_IND_ST *)pRcvMsg;

    /* ����GSM�����²������ԣ���ʼ��ΪĬ��ֵ */
    g_RrMmSyncInd.ulRabCnt = 1;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabId = 0;
    g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId = 0;
    g_RrMmSyncInd.ulReason = MMCC_GSM_RES_ASSIGNED;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = 0;

    enMmCcChanMode = MM_ComGetChanMode(pChanMod->enChanMod);
    if(MMCC_CHAN_MOD_SIG_ONLY == enMmCcChanMode)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                        "Mm_Cell_S6_E86:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
    }

    g_RrMmSyncInd.ulChannelMode = enMmCcChanMode;

    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_TRUE;

    Mm_SndCcSyncInd();
}
VOS_VOID NAS_MM_ProcInterRatReselInLuProcedure(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*Ǩ��״̬��limit service*/
        /*���ñ�־Attach not allow*/
        /*ָʾ�ϲ�ҵ��ʧ��*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcInterRatReselInLuProcedure:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */

            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* ��U2״̬�����浱ǰ��LAI��Ϣ */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        /* ��U2�Ĺ������� */
        Mm_ComToU2Handle();

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212�Ƚ���ֹͣ                                */
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    NAS_MM_ProcDelayService();

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }

    return;
}
VOS_VOID NAS_MM_ProcDelayService(VOS_VOID)
{
    VOS_UINT8                                   ucRrConnRelFlg;
    VOS_UINT8                                   ucTiValidFlg;

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    return;
}


VOS_VOID Mm_Cell_S2_E15(
    VOS_VOID                           *pRcvMsg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMmcLuIni = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg))
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}




VOS_VOID Mm_Cell_S3_E54(VOS_VOID* pMsg)
{
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return;
    }

    /* LTE�²��ܷ���LAU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* ����LAU */
        Mm_ComLuOnly();
    }

    return;
}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
