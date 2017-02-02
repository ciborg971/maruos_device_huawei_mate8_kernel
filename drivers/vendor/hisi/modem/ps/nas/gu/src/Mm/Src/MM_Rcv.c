

#include        "MM_Inc.h"
#include        "MmCcInterface.h"
#include        "GmmMmInterface.h"
#include        "NasMmProcLResult.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_RCV_C


#define NAS_MM_SYNC_INFO_CODEC_AMR      (0x05)
#define NAS_MM_SYNC_INFO_CODEC_AMR2     (0x06)
#define NAS_MM_SYNC_INFO_CODEC_AMRWB    (0x0a)


/*lint -save -e958 */

/***********************************************************************
 *  MODULE   : Mm_RcvMmcStartReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      2003.12.09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcStartReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


VOS_UINT8 Mm_RcvMmcPlmnSrchIni(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcPlmnUserSelReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ucRet    ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcPlmnUserSelReq(
                            VOS_VOID            *pRcvMsg                        /* �յ���ԭ��ͷָ��                         */
                            )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedAttachIni
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedAttachIni(
                                VOS_VOID            *pRcvMsg                    /* �յ���ԭ��ͷָ��                         */
                                )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedAttachAccept
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedAttachAccept(
                                    VOS_VOID            *pRcvMsg                /* �յ���ԭ��ͷָ��                         */
                                    )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MM_CONST_NUM_1 < pstMsg->enAttachResult)
        || ((GMMMM_ATTACH_RESLUT_PS_ONLY == pstMsg->enAttachResult)
            && ((NAS_MML_REG_FAIL_CAUSE_NULL != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION != pstMsg->enCause)))
			|| (MM_CONST_NUM_5 < pstMsg->ulAttachAttCounter))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmCombinedAttachAccept:WARNING: MMCMM_COMBINED_ATTACH_ACCEPTED CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        if (GMMMM_ATTACH_RESLUT_PS_ONLY == pstMsg->enAttachResult)
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
        }
        else if (GMMMM_ATTACH_RESLUT_COMBINED == pstMsg->enAttachResult)
        {
            g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
        }
        else
        {

        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmCombinedAttachRej
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmCombinedAttachRej(
                                VOS_VOID            *pRcvMsg                    /* �յ���ԭ��ͷָ��                         */
                                )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_COMBINED_ATTACH_REJECTED_STRU     *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (GMMMM_COMBINED_ATTACH_REJECTED_STRU *)pRcvMsg;                      /* ��Ϣת��                                 */

    if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pMsg->enCause)
        && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pMsg->enCause))
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pMsg->enCause;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}



/***********************************************************************
 *  MODULE   : Mm_RcvGmmImsiDetechIni
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmImsiDetechIni(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmImsiDetechComplete
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmImsiDetechComplete(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmNetworkDetechInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmNetworkDetechInd(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_NETWORK_DETACH_IND_STRU           *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_NETWORK_DETACH_IND_STRU *)pRcvMsg;                            /* ��Ϣת��                                 */

    /*��������෢���IMSI detach��MM�ϱ�NAS_OM_EVENT_IMSI_DETACH_IND�¼�*/
    if (GMMMM_NET_DETACH_IMSI == pstMsg->enDetachType)
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    if ((GMMMM_NET_DETACH_IMSI != pstMsg->enDetachType)
        && (GMMMM_NET_DETACH_NOATTACH != pstMsg->enDetachType)
        && (GMMMM_NET_DETACH_REATTACH != pstMsg->enDetachType))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_RcvGmmNetworkDetechInd:WARNING: MMCMM_NETWORK_DETACH_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        ucRet = MM_TRUE;
        if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->ulDetachCause)
            && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->ulDetachCause))
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->ulDetachCause;
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmGmmActionResultInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmGmmActionResultInd(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_GMM_ACTION_RESULT_IND_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MM_CONST_NUM_3 < pstMsg->enGmmActionType))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmGmmActionResultInd:WARNING: MMCMM_GMM_ACTION_RESULT_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        ucRet = MM_TRUE;
        if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->enCause))
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmAuthFailInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmAuthFailInd(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauInitiation
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauInitiation(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                             /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauAccepted
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauAccepted(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_COMBINED_RAU_ACCEPTED_STRU        *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_COMBINED_RAU_ACCEPTED_STRU *)pRcvMsg;                         /* ��Ϣת��                                 */

    if (GMMMM_RAU_RESULT_PS_ONLY == pstMsg->enRauResult)
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
    }
    else if (GMMMM_RAU_RESULT_COMBINED == pstMsg->enRauResult)
    {
        g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    else
    {

    }
    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauRejected
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauRejected(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_COMBINED_RAU_REJECTED_STRU        *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_COMBINED_RAU_REJECTED_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->enCause)
        && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->enCause))
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}



/***********************************************************************
 *  MODULE   : Mm_RcvMmcCoverageLostInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcCoverageLostInd(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    g_MmGlobalInfo.ucSysInfoFlg = MM_FALSE;

    return MM_TRUE;                                                             /* ���ؼ����                             */
}



VOS_UINT8 Mm_RcvCcEstReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                           ucRet;                             /* ����ֵ                                   */
    MMCC_EST_REQ_STRU                  *pMsg;                              /* ������յ�����Ϣ����ָ��                 */

    pMsg        = (MMCC_EST_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */
    ucRet       = MM_TRUE;

    if ( ( MM_CONST_NUM_0 == pMsg->ulCallType )
      || ( MM_CONST_NUM_2 < pMsg->ulCallType )
      || ( MM_CONST_NUM_7 < pMsg->ulCallPri )
      || ( MMCC_CALL_MODE_OTHER < pMsg->ulCallMode ) )
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcEstReq:WARNING: MMCC_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmCcEstReq.ulCallPri       = pMsg->ulCallPri;
        g_MmCcEstReq.ulCallType      = pMsg->ulCallType;
        g_MmCcEstReq.ulTransactionId = pMsg->ulTransactionId;
        g_MmCcEstReq.ulCallMode = pMsg->ulCallMode;
        if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
        {                                                                       /* ������������                             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg =
                MM_TRUE;          /* �����ǽ������еı�־                     */

            NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
        }
        else
        {                                                                       /* ������������                             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg =
                MM_FALSE;         /* �������������еı�־                     */

            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        /* ��λ�����ؽ����� */
        g_MmGlobalInfo.ucCallRetryCount = 0;

        NAS_MM_UpdateCallStatus_RcvCcEstReq(pMsg);
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvCcRelReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-09  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcRelReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMCC_REL_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCC_REL_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (((MMCC_RELEASE_ALL != pMsg->ulReleaseType)
        && (MMCC_RELEASE_SPECIFIC != pMsg->ulReleaseType))
        || ((MMCC_RELEASE_SPECIFIC == pMsg->ulReleaseType)
            && (MM_CONST_NUM_14 < pMsg->ulTransactionId)))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcRelReq:WARNING: MMCC_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmCcRelReq.ulReleaseType   = pMsg->ulReleaseType;
        g_MmCcRelReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcAbortReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.11    �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcAbortReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                     ucRet = MM_TRUE;              /* ����ֵ                                   */
    MMCC_ABORT_REQ_STRU                          *pMsg  = VOS_NULL_PTR;         /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCC_ABORT_REQ_STRU *)pRcvMsg;

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcAbortReq:WARNING: MMCC_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmCcAbortReq.ulTransactionId = pMsg->ulTransactionId;

        /* CC��ֹ���У����ò���Ҫ�������� */
        g_MmGlobalInfo.ucCallRetryCount = MM_CALL_RETRY_MAX_TIMES;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcDataReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.11  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcDataReq(
                   VOS_VOID            *pRcvMsg                                 /* �յ���ԭ��ͷָ��                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMCC_DATA_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTransactionId)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcDataReq:WARNING: MMCC_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcReestReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.11  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcReestReq(
                        VOS_VOID             *pRcvMsg                           /* �յ���ԭ��ͷָ��                         */
                        )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    MMCC_REEST_REQ_STRU                      *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCC_REEST_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTransactionId)
        || (MM_CONST_NUM_7 == pMsg->ulTransactionId))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcReestReq:WARNING: MMCC_REEST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmCcReestReq.ulTransactionId  = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcPagingInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.11    �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcPagingInd(
                        VOS_VOID             *pRcvMsg                           /* �յ���ԭ��ͷָ��                         */
                        )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    RRMM_PAGING_IND_STRU                     *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    MSG_HEADER_STRU                          *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU*)pRcvMsg;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* �ж��Ƿ�Ϊ GSM ��Ѱ����Ϣ */
        if (UEPS_PID_GAS != pMsgHeader->ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcPagingInd: WARNING: Receive WAS Page Ind in GSM!");

            return MM_FALSE;
        }

        /* ���ú��� MM_RcvGsmRrcPagingInd ���� */
        ucRet = MM_RcvGsmRrcPagingInd(pRcvMsg);

        return ucRet;
    }
    else
    {
        /* �ж��Ƿ�Ϊ WCDMA ��Ѱ����Ϣ */
        if (WUEPS_PID_WRR != pMsgHeader->ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcPagingInd: WARNING: Receive GSM Page Ind in WCDMA!");

            return MM_FALSE;
        }
    }

    pMsg = (RRMM_PAGING_IND_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
        || (MM_CONST_NUM_1 < pMsg->ulPagingType)
        || (MM_CONST_NUM_6 < pMsg->ulPagingCause)
        || (MM_CONST_NUM_4 < pMsg->ulPagingUeId))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcPagingInd:WARNING: RRMM_PAGING_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmGlobalInfo.ucPagingCause = (VOS_UINT8)pMsg->ulPagingCause;          /* ����Ѱ��ԭ��ֵ                           */

        if ((RRC_P_TMSI_GSM_MAP == pMsg->ulPagingUeId)
            || (RRC_TMSI_GSM_MAP_P_TMSI == pMsg->ulPagingUeId))
        {
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
        }
        else if (RRC_IMSI_GSM_MAP == pMsg->ulPagingUeId)
        {
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
        }
        else
        {
            ucRet = MM_FALSE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcPagingInd:WARNING: RRMM_PAGING_IND CHECK PRIMITIVE ERROR!");
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


VOS_UINT8 Mm_RcvRrcEstCnf(
                        VOS_VOID            *pRcvMsg                            /* �յ���ԭ��ͷָ��                         */
                        )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    RRMM_EST_CNF_STRU                       *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */
    NAS_MML_CONN_STATUS_INFO_STRU           *pstConnStatus;
    VOS_UINT32                               ulIsGsmOnlyEstCnfRslt;

    pstConnStatus       = NAS_MML_GetConnStatus();

    pMsg = (RRMM_EST_CNF_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {                                                                           /* ��ǰ�� GSM ����                          */
        if (UEPS_PID_GAS != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcEstCnf: WARNING: Receive WAS message in GSM.");
            return MM_FALSE;
        }
    }
    else
    {
        if (WUEPS_PID_WRR != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcEstCnf: WARNING: Receive GAS message in WCDMA.");
            return MM_FALSE;
        }
    }

    if (RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
    {                                                                           /* ����CS����Ϣ                             */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                "Mm_RcvRrcEstCnf: WARNING: Not receive CS domain message.");
        return MM_FALSE;
    }

    if (g_MmGlobalInfo.ucRrEstReqOpid != pMsg->ulOpId)
    {                                                                           /* OP ID�����                              */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                "Mm_RcvRrcEstCnf: WARNING: OPID is wrong.");
        return MM_FALSE;
    }

    if (   (RRC_EST_SUCCESS == pMsg->ulResult)
        || (RRC_EST_PRESENT == pMsg->ulResult))
    {
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);

        /* 24.008, 4.4.4.9, case f1, CR1099 update:
          ����RRC��·״̬ */
        pstConnStatus->ucCsSigConnStatusFlg     = VOS_TRUE;
        pstConnStatus->ucRrcStatusFlg           = VOS_TRUE;

        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_EST_SUCCESSED,
                                  pMsg->ulResult);
    }
    else
    {
        /* ����ʧ�ܣ����MM ��·���Ʊ��� */
        NAS_MM_ClearMmLinkCtrlStru();

        NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_EST_FAILED,
                                  pMsg->ulResult);

        /* ��LU������,random access rejʱ,��Ҫ�ٷ���һ��LU��������,�ڵڶ��ν���ʧ��ʱ,���CSFB��־
           ����ԭ��ֱֵ�����CSFB��־*/
#if (FEATURE_ON == FEATURE_LTE)
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pMsg->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
          && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt)
          && ((g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_1)
           || ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
            && (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt >= MM_CONST_NUM_1))))

        {
            return ucRet;
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
#endif

    }

    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8 Mm_RcvRrcRelInd(
    VOS_VOID                           *pRcvMsg                            /* �յ���ԭ��ͷָ��                         */
)
{
    VOS_UINT8                           ucRet = MM_TRUE;                  /* ����ֵ                                   */
    RRMM_REL_IND_STRU                  *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
        || (MM_CONST_NUM_1 < pMsg->ulRrcConnStatus)
        || (RRC_REL_CAUSE_BUTT <= pMsg->ulRelCause))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcRelInd:WARNING: RRMM_REL_IND CHECK PRIMITIVE ERROR!");
        return MM_FALSE;
    }

    /* ��·�ͷţ����MM ��·���Ʊ�����������CS ��������״̬ */
    pstConnStatus->ucCsSigConnStatusFlg = VOS_FALSE;
    if (RRC_RRC_CONN_STATUS_ABSENT == pMsg->ulRrcConnStatus)
    {
        pstConnStatus->ucRrcStatusFlg   = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ����ǰ����CSFB��־�������CSFB��־ */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {

        /* ���CSFB MT������ʱ����ʱ״̬�£��յ������REL����Ϊ��CSFB MT���쳣 */
        if (NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_PROTECT_TI_TIME_OUT == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND,
                                      pMsg->ulRelCause);

#if (FEATURE_ON == FEATURE_PTM)
            NAS_MM_CsfbMtFailRecord();
#endif
        }
        else
        {
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_RRC_REL_IND_RECEIVED,
                                      pMsg->ulRelCause);
        }


        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    }
#endif

    /* ��·�ͷź�ԭ����·��GAS�ϱ���Gas_RR_CHAN_IND��ϢʧЧ */
    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_FALSE;

    /* ����״̬���ж��Ƿ���Ҫ�������̺������MM��·���Ʊ��� */
    if (   (WAIT_FOR_OUTGOING_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_INITIATED != g_MmGlobalInfo.ucState))
    {
        NAS_MM_ClearMmLinkCtrlStru();
    }

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_RcvRrcRelInd:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_ABSENT");

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(pMsg->ulRelCause);
    }
    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8 Mm_RcvRrcSecurityInd(
                           VOS_VOID            *pRcvMsg                         /* �յ���ԭ��ͷָ��                         */
                           )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    RRMM_SECURITY_IND_STRU                   *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    pMsg = (RRMM_SECURITY_IND_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* �ж��Ƿ�Ϊ GSM ��ͬ��ָʾ��Ϣ */
        if (UEPS_PID_GAS!= pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcSecurityInd: WARNING: Receive WAS Security Ind in GSM!");

            return MM_FALSE;
        }

        ucRet = MM_RcvGsmRrcSyncInd(pRcvMsg);

        return ucRet;

    }
    else
    {
        /* �ж��Ƿ�Ϊ WCDMA ��ͬ��ָʾ��Ϣ */
        if (WUEPS_PID_WRR != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcSecurityInd: WARNING: Receive GAS Sync in WCDMA!");

            return MM_FALSE;
        }
    }

    if (RRC_SECURITY_MOBI_MSG < pMsg->ulRptMode)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcSecurityInd:WARNING: RRMM_SECURITY_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */

        g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;       /* ��ǰCS������·���յ�SMC��Ϣ */

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType = (VOS_UINT8)pMsg->ulRptMode;

        if ((RRC_SECURITY_DEL_CS_KEY == pMsg->ulRptMode)
            || (RRC_SECURITY_DEL_CS_PS_KEY == pMsg->ulRptMode))
        {
            NAS_MML_InitCsSecurityUmtsCkInvalid();
            NAS_MML_InitCsSecurityUmtsIkInvalid();

            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        }
        else
        {
            if ( RRC_SECURITY_CS_SMC_RCV == pMsg->ulRptMode )
            {
                g_MmSubLyrShare.MmShare.ucCsIntegrityProtect = NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
                Mm_TimerStop(MM_TIMER_T3218);                                   /* ͣT3218                                  */
                Mm_ComDelRandRes();                                             /* ɾ��RAND��RES                            */
            }
            #if 0
            else if(RRC_SECURITY_CS_SMC_CMPL == pMsg->ulRptMode)
            {
                g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg =
                    (VOS_UINT8)pMsg->ulCsCipherStatus;                              /* ���ü����Ƿ�����                         */
              /*  if ( RRC_INTEG_PROTECT_NOCHG != pMsg->ulIntegCmd ) */
                if ( RRC_INTEG_PROTECT_CS_START == pMsg->ulIntegCmd )
                {                                                               /* �����Ա���״̬�ı�                       */
                    g_MmGlobalInfo.CsSecutityInfo.ucIntegFlg =
                                                    MM_INTEG_PROTECT_START;     /* �����Ա�������                           */
                }
            }
            #endif
        }
        #if 0
        if (RRC_CIPHER_START == g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg)
        {
            if ( RRC_NAS_CIPHER_ALGO_UEA0 == pMsg->ulCsCipherAlgor )
            {
                g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_UEA0;
            }
            else if ( RRC_NAS_CIPHER_ALGO_UEA1 == pMsg->ulCsCipherAlgor )
            {
                g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_UEA1;
            }
            else
            {

            }
        }
        #endif
    }

    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8 Mm_RcvRrcSyncInd(
                       VOS_VOID            *pRcvMsg
                       )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    VOS_UINT8                                 i;
    RRMM_SYNC_IND_STRU                       *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */
    pMsg = (RRMM_SYNC_IND_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if  (RRC_NAS_MAX_RAB_SETUP < pMsg->ulRabCnt)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcSyncInd:WARNING: RRMM_SYNC_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        PS_MEM_SET(&g_RrMmSyncInd,0,sizeof(g_RrMmSyncInd));

        g_RrMmSyncInd.ulRabCnt = pMsg->ulRabCnt;

        for (i=0; i < pMsg->ulRabCnt; i++)
        {
            g_RrMmSyncInd.NasSyncInfo[i].ulRabId       = pMsg->NasSyncInfo[i].ulRabId;
            g_RrMmSyncInd.NasSyncInfo[i].ulCnDomainId  = pMsg->NasSyncInfo[i].ulCnDomainId;
            g_RrMmSyncInd.NasSyncInfo[i].ulRabSyncInfo = (VOS_UINT32)(pMsg->NasSyncInfo[i].ucRabSyncInfo);
        }

        /* �˴�Amr no change���͵�CCʱ��ת����release��CC�¿�����������Ҫ�޸� */
        g_RrMmSyncInd.ulReason      = pMsg->enAmrModeCfgType + 4;

        if ( g_RrMmSyncInd.ulRabCnt > 0 )
        {
            if (NAS_MM_SYNC_INFO_CODEC_AMR == (pMsg->NasSyncInfo[0].ucRabSyncInfo))
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR;
            }
            else if ( NAS_MM_SYNC_INFO_CODEC_AMR2 == (pMsg->NasSyncInfo[0].ucRabSyncInfo) )
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
            }
            else if ( NAS_MM_SYNC_INFO_CODEC_AMRWB == (pMsg->NasSyncInfo[0].ucRabSyncInfo) )
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMRWB;
            }
            else
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
            }

        }
        else
        {
            g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcDataInd
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.12  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcDataInd(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                               ucRet = MM_TRUE;                    /* ����ֵ                                   */

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmGprsDetechIni
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.12  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmGprsDetechIni(
                             VOS_VOID            *pRcvMsg                       /* �յ���ԭ��ͷָ��                         */
                            )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    GMMMM_GPRS_DETACH_INITIATION_STRU        *pstMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_GPRS_DETACH_INITIATION_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((GMMMM_COMBINED_DETACH_NORMAL != pstMsg->enDetachType)
        && (GMMMM_GPRS_DETACH_NORMAL != pstMsg->enDetachType))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_RcvGmmGprsDetechIni:WARNING: MMCMM_GPRS_DETACH_INITIATION CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        ucRet = MM_TRUE;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvGmmGprsDetechCmpl
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    2003.12.12  �°�����
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmGprsDetechCmpl(
                          VOS_VOID            *pRcvMsg                          /* �յ���ԭ��ͷָ��                         */
                          )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */

    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8   Mm_RcvAgntUsimAuthenticationCnf(
                                         VOS_VOID     *pMsg                     /* ��ǰ�������Ϣ                           */
                                        )
{
    VOS_UINT8                               ucRet = MM_TRUE;                    /* ���ؽ����ʼ��Ϊ�ɹ�                     */

    if (MM_RCV_AUTH_CNF_FLG
        != (MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvAgntUsimAuthenticationCnf:WARNING: g_MmGlobalInfo.ucRcvAgentFlg Abnormal");
        return MM_FALSE;
    }
    else
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    }

    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst)
    {
        NAS_MML_SetSimCsSecurityUmtsCk(g_AgentUsimAuthCnf.aucCipheringKey);
        NAS_MML_SetSimCsSecurityUmtsIk(g_AgentUsimAuthCnf.aucIntegrityKey);

        NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

        PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucRes,
                    g_AgentUsimAuthCnf.aucResponse, 4);

        /* ���� RES ���ڱ�־ */
        g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg = MM_AUTHEN_RES_PRESENT;

        if (MM_CONST_NUM_0 == g_AgentUsimAuthCnf.ucKcLength)                    /* g_AgentUsimAuthCnf.ucKcLength Ϊ�� */
        {
            /* ���ú��� NAS_MML_SecContext3GTO2G ��� KC */
            NAS_MML_SecContext3GTO2G(NAS_MML_GetSimCsSecurityUmtsIk(),
                                     NAS_MML_GetSimCsSecurityUmtsCk(),
                                     NAS_MML_GetSimCsSecurityGsmKc());

        }
        else
        {
            /* �� KC ���浽ȫ�ֱ��� */
            NAS_MML_SetSimCsSecurityGsmKc(g_AgentUsimAuthCnf.aucKc);

        }

        if (0 != g_AgentUsimAuthCnf.ucExtRspLength)
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength =
                               g_AgentUsimAuthCnf.ucExtRspLength;
            if (MM_MAX_RES_EXT_LEN <
                g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength)
            {
                 g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = MM_MAX_RES_EXT_LEN;
            }
            PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes,
                        g_AgentUsimAuthCnf.aucExtResponse,
                        g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);          /* ����Extern RES                           */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;
        }
    }
    else
    {
        if (AGENT_AUTH_FAIL_SQN == g_AgentUsimAuthCnf.ucFailureCause)
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength =
                g_AgentUsimAuthCnf.ucFailParaLength;
            if (0 != g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength)
            {
                if (14 < g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength)
                {
                    g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength = 14;
                }
                PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucFailPara,
                            g_AgentUsimAuthCnf.aucFailPara,
                            g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength);
            }
        }
    }

    return ucRet;
}


VOS_UINT8 Mm_RcvMmcDetachReq(
                         VOS_VOID            *pRcvMsg                           /* �յ���ԭ��ͷָ��                         */
                         )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    MMCMM_DETACH_REQ_STRU                    *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCMM_DETACH_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MMC_MM_PS_DETACH       != pMsg->enDetachType)
        && (MMC_MM_CS_DETACH    != pMsg->enDetachType)
        && (MMC_MM_PS_CS_DETACH != pMsg->enDetachType))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcDetachReq:WARNING: MMCMM_DETACH_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        ucRet = MM_TRUE;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


VOS_UINT8 Mm_RcvMmcPowerOffReq(
                         VOS_VOID            *pRcvMsg                           /* �յ���ԭ��ͷָ��                         */
                         )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    VOS_UINT8                                i;
    NAS_MML_EMERGENCY_NUM_LIST_STRU         *pstEmergencyNumList;
    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    Mm_TimerStop(MM_TIMER_STOP_ALL);

    pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

    for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
    {
        PS_MEM_SET(&pstEmergencyNumList->aucEmergencyList[i],
                    0xFF,
                    sizeof(NAS_MML_EMERGENCY_NUM_STRU));
    }

    pstEmergencyNumList->ucEmergencyNumber = 0;


    return ucRet;                                                               /* ���ؼ����                             */
}
/***********************************************************************
 *  MODULE   : Mm_RcvSsEstReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsEstReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSS_EST_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */
    pMsg = (MMSS_EST_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsEstReq:WARNING: MMSS_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSsEstReq.ulTi = pMsg->ulTi;

        /* ��һ�η���ssҵ��(�����ز�ʱ),��Ĭ��Ϊgu�µ�ҵ��
           ��������Ƿ���LMM�ģ��ڸ�LMM����csfb startʱ����¸ñ�־
        */
        if (VOS_FALSE == pMsg->ucRedialFlg)
        {
            NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_START);
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSsRelReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsRelReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSS_REL_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSS_REL_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTi)
        || (MM_CONST_NUM_7 == pMsg->ulTi))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsRelReq:WARNING: MMSS_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSsRelReq.ulTi = pMsg->ulTi;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSsDataReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsDataReq(
                   VOS_VOID            *pRcvMsg                                 /* �յ���ԭ��ͷָ��                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSS_DATA_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSS_DATA_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsDataReq:WARNING: MMSS_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */

    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSmsEstReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsEstReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSMS_EST_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSMS_EST_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsEstReq:WARNING: MMSMS_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSmsEstReq.ulEstCause = pMsg->ulEstCause;
        g_MmSmsEstReq.ulTi       = pMsg->ulTi;
    }

    g_MmGlobalInfo.ucPagingType = MM_MO_PAGING;

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSmsRelReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsRelReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSMS_REL_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSMS_REL_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTi)
        || (MM_CONST_NUM_7 == pMsg->ulTi))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsRelReq:WARNING: MMSMS_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSmsRelReq.ulTi = pMsg->ulTi;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSmsDataReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-09  �°�����
 *     2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsDataReq(
                   VOS_VOID            *pRcvMsg                                 /* �յ���ԭ��ͷָ��                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSMS_DATA_REQ_STRU                     *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSMS_DATA_REQ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsDataReq:WARNING: MMSMS_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */

    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcPromptRej
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-10  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcPromptRej(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMCC_PROMPT_REJ_STRU                    *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMCC_PROMPT_REJ_STRU *)pRcvMsg;                                                             /* ��Ϣת��                                 */

    g_MmCcPromptRej.ulRefuseCause = pMsg->ulRefuseCause;

    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8 Mm_RcvMmcAttachReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                           ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMCMM_ATTACH_REQ_STRU              *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();
    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();

    pMsg = (MMCMM_ATTACH_REQ_STRU*)pRcvMsg;                                     /* ��Ϣת��                                 */

    if ((MMC_MM_ATTACH_TYPE_GPRS != pMsg->enAttachType)
        && (MMC_MM_ATTACH_TYPE_IMSI != pMsg->enAttachType)
        && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pMsg->enAttachType))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcAttachReq:WARNING: MMCMM_ATTACH_REQ CHECK PRIMITIVE ERROR!");
    }

    if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
    {
        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {
            if ((VOS_TRUE == ucSimPsRegStatus)
                && (MM_UNSUPPORT_GPRS != g_MmGlobalInfo.usRac))
            {
                if((VOS_TRUE == ucPsAttachAllow)
                || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pMsg->enAttachType))
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_RcvMmcAttachReq:INFO: MmLikeB is MM_FALSE");
                }
            }
        }
    }

    return ucRet;                                                               /* ���ؼ����                             */
}




VOS_UINT8 Mm_RcvMmcRelReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    return MM_TRUE;                                                                   /* ���ؼ����                             */
}
/***********************************************************************
 *  MODULE   : Mm_RcvMmcModeChngReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      04-03-10  �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcModeChngReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMCMM_MODE_CHANGE_REQ_STRU              *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */
    pMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pRcvMsg;                                /* ��Ϣת��                                 */

    if ( (NAS_MML_MS_MODE_NULL != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_PS_CS != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_PS_ONLY != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_CS_ONLY != pMsg->enMsMode) )
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcModeChngReq:WARNING: MMCMM_MODE_CHANGE_REQ CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* ���ؼ����                             */
}
VOS_UINT8 Mm_RcvGmmLuIni(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    GMMMM_LU_INITIATION_STRU                *pstMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */

    pstMsg = (GMMMM_LU_INITIATION_STRU*)pRcvMsg;                                  /* ��Ϣת��                                 */

#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return MM_FALSE;
    }
#endif

    if ((GMMMM_NO_TIMER_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3312_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3311_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3302_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3330_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3412OrT3423_EXPIRED != pstMsg->enTimerExpiredFlg))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmLuIni:WARNING: MMCMM_LU_INITIATION CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* ���ؼ����                             */
}


VOS_UINT8 Mm_RcvRrcAcInfoChgInd(
                            VOS_VOID            *pRcvMsg                        /* �յ���ԭ��ͷָ��                         */
                            )
{
    /* USIM����ֹGSM����ʱ��������ע���Ѱ��ҵ��,�˴�ֱ�ӷ���MM_FALSE��
       ��ֹMm_Cell_S6_E74�������ó�ע���Ѱ�������� */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        return MM_FALSE;
    }
    return MM_TRUE;                                                             /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmAgentInquire
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��     2005.01.28  Agent��Ӧ
 ************************************************************************/
VOS_UINT8 Mm_RcvMmAgentInquire(
                            VOS_VOID            *pRcvMsg                        /* �յ���ԭ��ͷָ��                         */
                            )
{
    /*Mm_SndAgentInfo();*/
    return MM_TRUE;                                                             /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSsAbortReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��   2005.02.01    �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsAbortReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* ����ֵ                                   */
    MMSS_ABORT_REQ_STRU                     *pMsg  = VOS_NULL_PTR;              /* ������յ�����Ϣ����ָ��                 */
    pMsg = (MMSS_ABORT_REQ_STRU *)pRcvMsg;                                      /* ��Ϣת��                                 */

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsAbortReq:WARNING: MMSS_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSsAbortReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSmsAbortReq
 *  FUNCTION : ��Ϣ���
 *  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ��Ϣ�����
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��   2005.02.01    �°�����
       2.��    ��  : 2006��12��4��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsAbortReq(
                       VOS_VOID            *pRcvMsg                             /* �յ���ԭ��ͷָ��                         */
                       )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* ����ֵ                                   */
    MMSMS_ABORT_REQ_STRU                     *pMsg  = VOS_NULL_PTR;             /* ������յ�����Ϣ����ָ��                 */

    pMsg = (MMSMS_ABORT_REQ_STRU *)pRcvMsg;                                     /* ��Ϣת��                                 */

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
        ucRet = MM_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsAbortReq:WARNING: MMSMS_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ�е�ȡֵ�Ϸ����洢��Ϣ               */
        g_MmSmsAbortReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* ���ؼ����                             */
}
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

