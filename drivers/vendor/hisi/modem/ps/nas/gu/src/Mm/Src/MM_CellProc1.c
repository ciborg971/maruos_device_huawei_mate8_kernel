
#include        "MM_Inc.h"
#include        "NasCommDef.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"

#include        "NasMmSndOm.h"
#include        "NasMmEcall.h"
#include        "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC1_C

/*lint -save -e958 */

VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
)
{
    VOS_UINT32                          ulPos;

    /* �¼���¼��־����һ: ���Դ��������� */
    if (NAS_MNTN_CS_ATTEMPT_MAX == pstCsUnavailableInfo->ucTimes)
    {
        pstCsUnavailableInfo->bRecordRequired = VOS_TRUE;
    }

    /* �¼���¼��־���ö�: ע��ʧ��ԭ��ֵָʾ��ǰפ��λ�޷��ṩ������ѡ���ٳ���ע�� */
    NAS_MNTN_ServiceUnavailableType(usCause, &pstCsUnavailableInfo->bRecordRequired);

    /* �쳣����ֱ���˳�һ: ע��ʧ��ԭ��ֵû��ָʾ��ǰפ��λ�޷��ṩ����
       ��ע��ʧ�ܼ�����ֵΪ0 */
    if ((VOS_TRUE != pstCsUnavailableInfo->bRecordRequired)
     && (0 == g_MmGlobalInfo.LuInfo.ucLuAttmptCnt))
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StoreCsUnavailableInfo: Error Counter.");
        return;
    }

    /* �쳣����ֱ���˳���: ע��ʧ�ܼ�����ֵ�������ֵ */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt > NAS_MNTN_CS_ATTEMPT_MAX)
    {
        return;
    }

    /* ��¼ע��ʧ��ԭ��ֵ��ȫ�ֱ��� */
    if (0 != g_MmGlobalInfo.LuInfo.ucLuAttmptCnt)
    {
        ulPos = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt - 1;

    }
    else
    {
        ulPos = 0;
    }

    pstCsUnavailableInfo->aulCause[ulPos]= usCause;
    pstCsUnavailableInfo->ucTimes = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_RcvCcEstReq_CSFB(VOS_VOID)
{
    VOS_UINT32                          ulCsfbExistFlg;
    ulCsfbExistFlg = NAS_MML_IsCsfbServiceStatusExist();

    if ((MM_CONST_NUM_8  > g_MmCcEstReq.ulTransactionId)
     || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
     || (VOS_TRUE == ulCsfbExistFlg))
    {
        if (VOS_TRUE == ulCsfbExistFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);
        }
        else
        {
            /* ti�Ƿ����ظ�NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }

        /* Mm_RcvCcEstReq�����ж�����ǽ�����������ucEstingCallTypeFlg����Ҫ��� */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        return;
    }

    /* ���潨������ */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

    /* ����CSFB״̬ */
    if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        /* ��¼CSFBҵ������ʼ */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_START);
    }
    else
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        /* ��¼CSFBҵ������ʼ */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START);
    }

    /* ��L����CSFB���̿�ʼ����,CSFB�Ƿ���Է�����ж���LMM���������������,
       L��ظ�LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    return;

}


VOS_VOID NAS_MM_RcvSsEstReq_CSFB(VOS_VOID)
{
    /* �Ѿ���CSFB���̣�������������CSFB��������Ӧ���ظ�SS����ʧ�� */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);

        return;
    }

    if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
     || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
    {                                                                       /* TI���Ϸ� */
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

        return;
    }

    /* ���潨������ */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);

    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* ����CSFB״̬ */
    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* ��L����CSFB���̿�ʼ����,CSFB�Ƿ���Է�����ж���LMM���������������,
       L��ظ�LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_START);

    return;

}
#endif

VOS_VOID Mm_Cell_S3_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
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

        /* �����ǰפ��LTE,��ֱ�ӻظ�CCʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);      /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
VOS_VOID NAS_MM_ProcCcEstReq_IdleLimitedService(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {                                                                   /* �ǽ�������                               */
        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
    }
    else
    {                                                                   /* ���ǽ�������                             */
        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);      /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            /*״̬ΪNO IMSI���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* cs only limited service, cs+ps limited service, no imsiʱ����ͨ���л�cs detach������ */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* ֪ͨCC����ʧ��                           */
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /*����÷������󲢽���CSע��*/
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();
                }
            }

        }

    }
}


VOS_VOID Mm_Cell_S4_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;


    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
           /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* ��MM_IDLE_NO_IMSI״̬ʱ�յ���ͨ��������ֱ�ӻظ�CS_SIM_INVALID,
           ����״̬һ�����յ�ϵͳ��Ϣ��δע��ʱ������,��ʱ�޷��ṩCS������Ҫ�ز� */
        if ( (VOS_FALSE           == NAS_MML_GetSimCsRegStatus())
          && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* ֪ͨCC����ʧ��                           */

            return;
        }

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
            
            /* �����ǰPS ONLYʱ֧��CSҵ��NVδ���������ʧ�� */
            if ( (NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
              && (MMCC_MO_NORMAL_CALL      == g_MmCcEstReq.ulCallType) )
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);       /* ֪ͨCC����ʧ��                           */
                
                return;
            }

            NAS_MM_RcvCcEstReq_CSFB();
           
            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);            /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            NAS_MM_ProcCcEstReq_IdleLimitedService();
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S9_E24(
                        VOS_VOID            *pRcvMsg                           /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ��������Ҳ�������״̬����ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* �����ǰפ��LTE,��ֱ�ӻظ�CCʧ�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE);                              /* ֪ͨCC����ʧ��                           */

            return;
        }
#endif


        if(VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            if(MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                          /* ֪ͨCC����ʧ��                           */

                return;
            }
        }

        if ((MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);                          /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /*����÷������� */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
    }
    return;
}


VOS_VOID Mm_Cell_S10_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request�ṹ��                 */
    VOS_UINT8                           ucRst;

    PS_MEM_SET(&CmSvcReq,0x00,sizeof(CmSvcReq));

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        ucRst = Mm_ComJudgeLimitSvc();
        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
            || (MM_TRUE == ucRst))
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                   /* ֪ͨCC����ʧ��                           */
        }
        /*lint -e701*/
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] &
            (0x01 << (g_MmCcEstReq.ulTransactionId - 8))))
        /*lint +e701*/
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* ������������                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* ���CM SERVICE REQUEST�ṹ��             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_FALSE;                                                 /* ���ǽ�������                             */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
            }
            else if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* ���н�������                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* ���CM SERVICE REQUEST�ṹ��             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_TRUE;                                                  /* �ǽ�������                               */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
            }
            else
            {
            }
            Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                (VOS_UINT8)g_MmCcEstReq.ulTransactionId;                        /* ��¼���ڽ�����MM����                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;            /* ��¼���ڽ�����MM���ӵ�PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E24:NORMAL: STATUS is  WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        /*lint +e701*/
    }

    return;
}
VOS_VOID Mm_Cell_S11_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E24:WARNING: MMCC_EST_REQ check fail.");;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                             /* ֪ͨCC����ʧ��                           */
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /* ������Ϣ */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
      }

    return;
}
VOS_VOID Mm_Cell_S19_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        MM_WARN_LOG(" \nMM:Recieve CC EST REQUEST ERROR!\r " );
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�,֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* �ǽ�������                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                {
                    /* �Ѿ�����һ��������MM���ӽ�������,֪ͨCC����ʧ�� */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /* ������Ϣ */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }
    return;
}
VOS_VOID Mm_Cell_S10_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if (MM_FALSE == Mm_RcvCcRelReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType)
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            /*lint -e701*/
            if ((MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId)
                && (MM_CONST_NUM_0 !=
               (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & (0x01 << g_MmCcRelReq.ulTransactionId))))
            {                                                                   /* �ͷ����ཨ����MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & (~(VOS_UINT8)(0x01 << g_MmCcRelReq.ulTransactionId)));    /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ((MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_0 != (g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & (0x01 << (g_MmCcRelReq.ulTransactionId - 8)))))
            {                                                                   /* �ͷ�CC������MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & (~(VOS_UINT8)(0x01 <<
                    (g_MmCcRelReq.ulTransactionId - 8))));                      /* ���MM���Ӵ��ڱ�־                       */
            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����, ֪ͨCCָ���ͷŵ�MM���Ӳ����� */
                Mm_SndCcRelInd(g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
            }
            /*lint +e701*/
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
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* û��MM���Ӵ���                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                    ucStaOfRcvXXEstReq;                                         /* ������е�״̬                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* �����ͷ�CC������MM����                   */
            if ( ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* û��MM���Ӵ���                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                          /* ������е�״̬                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
    }

    return;
}
VOS_VOID Mm_Cell_S13_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* �ͷ������ؽ���MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* ���MM�����ؽ���־                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] & ( 0x01 <<
                ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* �ͷ�CC�ؽ���MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[1] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* ���MM�����ؽ���־                       */
            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
            }
            if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
                && (MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
            {                                                                   /* û�еȴ��ؽ���MM���Ӵ���                 */
                Mm_TimerStop(MM_TIMER_PROTECT_CC);                              /* ��������TIMER                            */
                if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
                    && ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ) )
                {                                                               /* ȫ���ͷţ�û��Ҫ���ؽ���MM����           */
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* ��¼Ǩ��֮ǰ��״̬                       */
                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                         || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                          && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)))
                        {
                            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        }


                    }
                }
                else
                {
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* ��¼Ǩ��֮ǰ��״̬                       */
                    Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
                    Mm_TimerStart(MM_TIMER_T3230);                              /* ��������TIMER                            */

                    MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                        = NAS_MML_GetCsLastSuccMcc();
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                        = NAS_MML_GetCsLastSuccMnc();
                    MsgReEstReq.MmIeLai.IeLai.ulLac
                        = NAS_MML_GetCsLastSuccLac();

                    NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

                    Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
                }
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                = 0;                                                            /* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                = 0;                                                            /* �����ͷ�CC������MM����                   */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }

        /*lint +e701*/
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S16_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/

        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* �ͷ����ཨ����MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]=
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
               ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* �ͷ�CC������MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId == g_MmCcRelReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;                                                 /* ���ò����ڻ����MM���� */

            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* �����ͷ�CC������MM����                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* ���ò����ڻ����MM����                   */
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();


        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S32_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        /* ��Ϣ�����ʧ�� */
        ;
    }
    else
    {
        /* ��Ϣ������ɹ�*/
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            /* ����MMCC_ABORT_REQ��Ӧ����Ҫ��MM���ڽ��������ӱ�������
               ���MM���ڽ��������ӱ��û������������˵�LTEʱ��������ҵ���Ǵ��ڣ��ͻᴥ���ͷ�ҵ�������
            */
            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);


#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S2_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }


            if ( VOS_FALSE == ucCsSigConnStatusFlg )
            {
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S9_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        NAS_MM_UpdateCsServiceConnStatusFlg();
    }
    return;
}
VOS_VOID Mm_Cell_S10_E26(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /*lint -e701*/
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
        .aucMMConnExtFlg[1]
            & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (((0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1])
                &&(0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[0]))
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E26:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT8)(0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    /*lint +e701*/
    return;
}

VOS_VOID Mm_Cell_S12_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        return;
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcAbortReq.ulTransactionId )
        {
            /* ��ֹ��MM���ӽ��������ڽ�����,������뼼����ͬ����rel req */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );

            /* ���MM���ȫ�ֱ��� */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI  = NO_MM_CONN_ESTING;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId ==
                     g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

VOS_VOID Mm_Cell_S16_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E26:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}
VOS_VOID Mm_Cell_S10_E27(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( ( MM_CONST_NUM_7 == pMmCcDataReq->ulTransactionId )
            || ( MM_CONST_NUM_15 == pMmCcDataReq->ulTransactionId ) )
        {                                                                       /* TIO ����111                              */
            Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��CC����Ϣ������ȥ                       */
        }
        else
        {                                                                       /* TIO ������111                            */
            /*lint -e701*/
            if ( ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0]
                & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
                || ( ( MM_CONST_NUM_7 < pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1]
                & ( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) ) ) ) ) )
            {                                                                   /* ��TI��MM���Ӵ���                         */
                Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��CC����Ϣ������ȥ                       */
            }
            else
            {
                /* ��TI��MM���Ӳ�����                       */
                Mm_SndCcRelInd(pMmCcDataReq->ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
            }

            /*lint +e701*/
        }
    }

    return;
}
VOS_VOID Mm_Cell_S13_E28(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcReestReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmCcReestReq.ulTransactionId )
        {                                                                       /* �����ཨ����MM�����ؽ�                   */
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
            & ( 0x01 << g_MmCcReestReq.ulTransactionId ) ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] |
                    ( 0x01 << g_MmCcReestReq.ulTransactionId ) );               /* ���������ؽ���MM���ӵı�־               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnReestFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] &
                    (~(VOS_UINT8)( 0x01 << g_MmCcReestReq.ulTransactionId ) ) );    /* ��������ؽ���MM���ӵı�־               */
            }
            else
            {
                Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* ֪ͨCC�ؽ���ʧ��                         */
            }

        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
            & ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* ��CC������MM�����ؽ�                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] |
                ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) );           /* ���������ؽ���MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] &
                (~(VOS_UINT8)( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) );/* ��������ؽ���MM���ӵı�־               */
        }
        else
        {
            /* Ҫ���ؽ���MM���Ӳ�����                   */
            Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                                  /* ֪ͨCC�ؽ���ʧ��                         */
        }
        /*lint +e701*/
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
            && (MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
        {                                                                       /* û�еȴ��ؽ���MM���Ӵ���                 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E28:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
            MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                = NAS_MML_GetCsLastSuccMcc();
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                = NAS_MML_GetCsLastSuccMnc();
            MsgReEstReq.MmIeLai.IeLai.ulLac
                = NAS_MML_GetCsLastSuccLac();

            NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

            Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        }
    }

    return;
}
VOS_VOID Mm_Cell_S2_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if (MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Mm_Cell_S2_E31:WARNING: Msg is invalid.");
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

    /* ֪ͨMMC CS����Ҫ������Ҫֹͣ���� */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO,
           "Mm_Cell_S2_E31:INFO: Rcv Paging in Plmn Search, Wait camping.");

    return;
}
VOS_VOID Mm_Cell_S3_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);


    CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();            /* �洢CKSN                                 */
    g_MmGlobalInfo.ucStaOfRcvXXEstReq
        = g_MmGlobalInfo.ucState;

    NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* ��ǰ���� GSM ���� */
    {
        /* �� GAS ���ͽ��� RR ���� */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS ���� */
    {
        Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* ��䲢���� PAGING RESPONSE ��Ϣ          */
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* ��������TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}

VOS_VOID Mm_Cell_S4_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                        )
{
    MM_MSG_PAGING_RSP_STRU              CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();



    enMsMode        = NAS_MML_GetMsMode();

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 24.008��4.2.2.3��it may respond to paging (with IMSI).*/
    if (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
       && (VOS_TRUE == ucCsAttachAllow))
       || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
          &&(NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)))
    {
        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* �洢CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&CmRspRsp.MmIeMobileId.MobileID);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                 /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}

VOS_VOID Mm_Cell_S5_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* �� IMEI Ѱ���Ĵ��� */
    if (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {

        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* �洢CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    }

    return;
}
VOS_VOID Mm_Cell_S6_E31(
    VOS_VOID                           *pstRcvMsg
)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enMsMode                = NAS_MML_GetMsMode();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    if (MM_FALSE == Mm_RcvRrcPagingInd(pstRcvMsg))
    {
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* MM_IDLE_LOCATION_UPDATE_NEEDED״̬�����ǰCS ע��״̬��Ӧ��ͨѰ����
       ����ֻ����Ӧ IMSI Ѱ�� */
    if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
     || (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
        && (VOS_TRUE == ucCsAttachAllow))
      || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
        && (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))))
    {

        stCmRspRsp.MmIeCksn.ucCksn            = NAS_MML_GetSimCsSecurityCksn(); /* �洢CKSN                                 */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq     = g_MmGlobalInfo.ucState;
        NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())            /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0,
                           VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd(&stCmRspRsp);                                 /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;

}


VOS_VOID Mm_Cell_S12_E32(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    RRMM_EST_CNF_STRU       *pRrMmEstCnf;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */

        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);


        /* ����ǰ�����CS��ȥע�� */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        /* �ڽ���CS���н��������У���������ظ�����ʧ�ܣ�ԭ��ֵΪ: Conn_Fail��
             �Աȱ�ˣ����ֱ�˻����·���������ֱ��CC T303��ʱ���ж�Ϊֹ,
            ����������ߵ绰��ͨ�� */
        if (  (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
           && ((RRC_EST_EST_CONN_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_NOT_ALLOW == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_TIME_OUT == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_RA_RESOURCE_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL == pRrMmEstCnf->ulResult))
           && (MM_IE_PD_CALL_CONTROL == g_MmGlobalInfo.ucMMConnEstingPD))
        {
            g_MmGlobalInfo.ucCallRetryCount++;

            /* Ϊ�˷�ֹMM/GAS��������ƹ�Ҳ���������ϵͳ��Ϣ������������Ƴ��Դ��� */
            if (g_MmGlobalInfo.ucCallRetryCount < MM_CALL_RETRY_MAX_TIMES)
            {
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }
        }

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_RecordCsPagingFail_WaitForRrConnection(pRrMmEstCnf->ulResult);
#endif

        /* �����Ϣ�����־               */
        NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

        /* ֻ�н��������RRC_EST_SUCCESS����RRC_EST_PRESENT������Ҫ����ҵ����ڱ�־ */

        NAS_MM_ProcEstCnfCauseAtState12(pRrMmEstCnf->ulResult);
    }

    return;
}
VOS_VOID Mm_Cell_S14_E32(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_EST_CNF_STRU       *pRrMmEstCnf;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;


        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);

        /* ����ǰ�����CS��ȥע�� */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        switch ( pRrMmEstCnf->ulResult)
        {
        case RRC_EST_SUCCESS:                                                   /* �������ӽ����ɹ�                         */
        case RRC_EST_PRESENT:                                                   /* �����������Ѿ�����                       */
            if ( RRC_EST_PRESENT == pRrMmEstCnf->ulResult )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION PRESENT !");
            }
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );

            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
            break;
        /* case RRC_EST_DELING:  */                                                  /* ���������������ͷ�                       */
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:

        case RRC_EST_RJ_SNW:

        case RRC_EST_RJ_NO_RF:

        case RRC_EST_RJ_T3122_RUNNING:

        case RRC_EST_OTHER_ACCESS_BARRED:
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        /* RRC_EST_RJ_RA_FAIL�Ǵ�ԭ����RRC_EST_RANDOM_ACCESS_REJECT�ɲ�����ģ���RRC_EST_RANDOM_ACCESS_REJECT�Ĵ�����һ��
           RRC_EST_RJ_CELL_BAR �Ǵ�ԭ����RRC_EST_ACCESS_BARRED�в�����ģ���RRC_EST_ACCESS_BARRED�Ĵ�����һ�� */
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_CELL_BAR:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:
            /*lint -e701*/
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM�������ڵȴ��ؽ� */
                    Mm_SndCcRelInd(i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM�������ڵȴ��ؽ� */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);/* ֪ͨCC,MM�����ؽ�ʧ��                    */
                }
            }

            /*lint +e701*/

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E32:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);   /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
            }

            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: ulResult Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}


VOS_VOID Mm_Cell_S9_E33(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    RRMM_REL_IND_STRU                   *pRrmmRelInd;
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;
    VOS_UINT8                           ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                           ucRst;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrmmRelInd->ulRelCause,
                    pRrmmRelInd->ulRrcConnStatus);

        if (VOS_TRUE == ucRst)
        {
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */

            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

            /* ���·���ǰMM CONNECTION�������� */
            NAS_MM_RetryMmConnectionProc(g_MmGlobalInfo.ucMMConnEstingPD);
            return;
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */

            /* �ͷŵ�ǰ���ڽ�����MM���ӵ�TI */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();

            /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* ����LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
                Mm_ComLuOnly();

                return ;
            }

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
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}


VOS_VOID NAS_MM_NotifyCcErrInd(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
)
{
    VOS_UINT8   i;

    i = 0;

    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* �ؽ���MM����                             */
        /*lint -e701*/
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndCcErrInd(i, enCause);                                         /* ֪ͨCC,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndCcErrInd(i + 8, enCause);                                              /* ֪ͨCC,MM����ʧЧ                        */
        }


        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSsRelInd(i, enCause);                                                  /* ֪ͨSS,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSsRelInd(i + 8, enCause);                                              /* ֪ͨSS,MM����ʧЧ                        */
        }

        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSmsRelInd(i, enCause);                 /* ֪ͨSS,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSmsRelInd((i + 8), enCause);          /* ֪ͨSS,MM����ʧЧ                        */
        }
        /*lint +e701*/

    }
}
VOS_VOID NAS_MM_HandleRelIndCause15AtS10(VOS_UINT8    ucRrConnRelFlg)
{
    VOS_UINT8    ucTiValidFlg;

    ucTiValidFlg = MM_TRUE;

    NAS_MM_NotifyCcErrInd(NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];      /* ��¼��Ҫ�ؽ��ı�־                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];      /* ��¼��Ҫ�ؽ��ı�־                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */

    if ((MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
        || (MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]))
    {
        Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
        Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* ��������TIMER                            */
    }
    else
    {
        if (MM_TRUE == ucRrConnRelFlg)
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        Mm_ComProcCauseProcess();

        if ( MM_FALSE == Mm_ComChkLu() )
        {
            if ((MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
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

            Mm_ComCheckDelayDetach();
        }
        else
        {
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndCcRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* ֪ͨCC����ʧ��                           */
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSmsRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
            }
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}

VOS_VOID Mm_Cell_S10_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        /* RRC_REL_CAUSEת��ΪMMCC_REL_CAUSE */
        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);

        if ((MM_TRUE == ucRrConnRelFlg)
         && (RRC_REL_CAUSE_RL_FAILURE != pRrmmRelInd->ulRelCause))
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
                NAS_MM_HandleRelIndCause15AtS10(ucRrConnRelFlg);
                break;

            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_ComRelAllMmConn(enMmCcRelCause);

                                                              /* �ͷ�����mm����                           */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();

                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);         /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);


                /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
                if ( VOS_TRUE == ucEmergencyLauFlg )
                {
                    /* ����LAU */
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
                    Mm_ComLuOnly();

                    return ;
                }

                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                    Mm_ComCheckDelayMmConn( MM_FALSE );

                    Mm_ComCheckDelayDetach();
                }
                break;

            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}
VOS_VOID Mm_Cell_S11_E33(
    VOS_VOID                           *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
)
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
    VOS_UINT8                           ucCsServiceConnStatusFlg;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        }

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* MT�ĳ����ҷ�CSFB MT���¼�쳣 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            /* �յ�CS PAGING�����ӽ����ɹ�������δ�յ�ҵ����Ϣ���յ��ײ��ͷ�ָʾ���쳣��¼ */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED);
        }

        /* ��CSFB MT������ʱ����ʱ״̬���յ�REL IND�����CSFB��״̬��Ϣ */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_TimerStop( MM_TIMER_T3240 );
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

                /*����Э��4.7.5.1.4��ATTACH����RAU�ܾ�ԭ��ֵΪ15������LAU*/
                if (( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal))
                 && (  (MM_GMM_RAU_PROC                       == g_MmGlobalInfo.ucProc)
                    || (MM_GMM_ATTACH_PROC                    == g_MmGlobalInfo.ucProc) )
                 && (MM_NORMAL_SERVICE                        == g_MmGlobalInfo.ucMmServiceState) )
                {
                    /* �Աȱ��:��PSע��ʧ��#15ʱ,��Ӱ��CS��ע�����.
                       ��PS��ע��ʧ��,CSע��ɹ�ʱ,MMC��ɾ����ֹLAI,Ȼ��PS���ٷ���һ��ע��,���ս���ǵ�ǰ��LAI�����ֹLAI�б��� */
                    /*Mm_ComProcCauseProcess�н�ȫ�ֱ���g_MmGlobalInfo.ucProc��
                      g_MmGlobalInfo.ucCauseVal���*/
                    /* Mm_ComProcCauseProcess(); */
                    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
                    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
                    Mm_ComProcCauseProcess_Handling_LU_PROC();
                }
                else
                {
                    Mm_ComProcCauseProcess();

                    /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                       �ж������ǰ��PSҵ����Ҫ����LAU */
                    if ( VOS_TRUE == ucEmergencyLauFlg )
                    {
                        /* ����LAU */
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                        Mm_ComLuOnly();

                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return ;
                    }

                    if ((MM_TRUE == Mm_ComChkLu())
                      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING ==
                                                g_MmGlobalInfo.ucState))
                    {
                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return;
                    }
                }

                /*����LAU�����ѷ���LAU�������´���:*/

                (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                Mm_ComCheckDelayMmConn(MM_FALSE);

                NAS_MM_UpdateCsServiceConnStatusFlg();

                /*û�л���ҵ�����ʱ,�������������ΪPS ONLY��ҪDetach CS*/
                Mm_ComCheckDelayDetach();

                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}

VOS_VOID    Mm_Cell_S12_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    RRMM_REL_IND_STRU                  *pstRelMsg  = VOS_NULL_PTR;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    VOS_UINT8                           ucCsServiceConnStatusFlg;

    pstRelMsg = (RRMM_REL_IND_STRU *)pRcvMsg;

    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

    NAS_MM_ClearAuthInfo();

    enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pstRelMsg->ulRelCause);


    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if (MM_TRUE == ucValidFlg)
    {
        /* ֹͣ������ʱ�� */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* ֪ͨMMC���Ӳ����� */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

        /* ��¼Ǩ��֮ǰ��״̬  */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* ״̬Ǩ��   */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* �������MM���ӽ��������з���LAI�ı䣬����Ҫ�ͷ�����MM����,���ڽ���MM���� */
        if(VOS_FALSE == g_MmGlobalInfo.ucPendingLu)
        {
            Mm_ComRelAllMmConn(enMmCcRelCause);
        }

        /* �������LU���� */


        /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
        if ( VOS_TRUE == ucEmergencyLauFlg )
        {
            /* ����LAU */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
            Mm_ComLuOnly();

            return ;
        }

        if (MM_FALSE == Mm_ComChkLu())
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
        }

        g_MmGlobalInfo.ucPendingLu = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* �յ�CS PAGING�����ӽ���ʱ�յ��ײ��ͷ�ָʾ���쳣��¼ */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED);
        }

        /* ��CSFB MT������ʱ����ʱ״̬���յ�REL IND�����CSFB��״̬��Ϣ */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        Mm_ComCheckDelayDetach();

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: ulRelCause Abnormal");
    }
}

VOS_VOID Mm_Cell_S14_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd    = VOS_NULL_PTR;
    VOS_UINT8                ucTiValidFlg   = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        Mm_TimerStop( MM_TIMER_T3230 );                                         /* ͣTIMER3230                              */
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);       /* ֪ͨCC,MM���ӽ���ʧ��                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();


            /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* ����LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();

                return ;
            }

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
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                /* WAIT FOR REESTABLISH(WAIT FOR EST_CNF)�յ�rel ind�����ز� */
                NAS_MM_RelBufferedServiceEstReq(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
VOS_VOID Mm_Cell_S16_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;


    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        Mm_TimerStop( MM_TIMER_T3230 );                                         /* ͣTIMER3230                              */

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);


        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcErrInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                        /* ֪ͨCC,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcErrInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                    /* ֪ͨCC,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSsRelInd(i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                        /* ֪ͨSS,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSsRelInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                    /* ֪ͨSS,MM����ʧЧ                        */

                }
                if ( MM_CONST_NUM_0 !=
                    (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSmsRelInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );        /* ֪ͨSS,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[1]  & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSmsRelInd( (i + 8), NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE ); /* ֪ͨSS,MM����ʧЧ                        */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];/* ��¼��Ҫ�ؽ��ı�־                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];/* ��¼��Ҫ�ؽ��ı�־                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            if ( ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[0] )
                || ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[1] )
                )
            {
                Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: STATUS is  WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
                Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* ��������TIMER                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();
                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    if ( ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                        RcvXXEstReq.ucFlg ) )
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

                    Mm_ComCheckDelayDetach();
                }
                else
                {
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                 NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* ֪ͨCC����ʧ��                           */

                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                    }
                }
            }
            break;
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_ComRelAllMmConn(enMmCcRelCause);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S16_E33:WARNING: ulRelCause Abnormal");
            break;
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S9_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
            && ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState))
        {
            Mm_TimerStop( MM_TIMER_T3212 );                                     /* ͣT3212                                  */
        }
        if ( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* �����Ա����Ͱ�ȫģʽ����                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */
            switch ( g_MmGlobalInfo.ucMMConnEstingPD )
            {                                                                   /* ȷ�����ĸ�PD������MM����                 */
            case MM_IE_PD_CALL_CONTROL:                                         /* CCҪ������MM����                       */
                Mm_SndCcEstCnf(
                    (VOS_UINT32)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                        ucMMConnEstingTI), MMCC_EST_SUCCESS );  /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI ) );                                   /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[1] |
                        (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI - 8 )) );                              /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
#if (FEATURE_ON == FEATURE_ECALL)
                /* ����eCall��ʱ��������ʶ */
                NAS_MM_RecordEcallTimerStartNeededFlag();
#endif

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            case MM_IE_PD_SMS_MSG:                                              /* SMSҪ������MM����                      */
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())      /* ��GSM�����ж���Ϣ������Ҫ����SAPI3       */
                {
                    if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)            /* ���� */
                    {
                        if (MM_FALSE == MM_SndSapi3EstReq())
                        {
                            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E34: ERROR: snd SAPI3 est fail.");

                            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */

                            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                            g_MmGlobalInfo.ucPagingType     = MM_NO_PAGING;

                            return;
                        }

                        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                        g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                        return;
                    }
                }

                Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    ucMMConnEstingTI );                                         /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[0] |=
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI );                                     /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI - 8 ) );                               /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                  /* SSҪ������MM����                       */
                Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI, MMSS_EST_SUCCESS );                       /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[0]
                     |= (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI );                                     /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI - 8 ) );                               /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E34:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
                break;
            }
            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                /* ����û�����ڽ���������                   */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E34:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            && ((RR_SYN_TCH == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
                 ||(RR_SYN_TCH_MODIFY == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
            }
        }
        else
        {
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E34
  FUNCTION : ��MM CONNECTION ACTIVE״̬��
             �յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_WARNING,
                "Mm_Cell_S10_E34: WARNING: Receive RR Security false.");

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState) || (WAIT_FOR_NETWORK_COMMAND == g_MmGlobalInfo.ucState))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
            }
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E34
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2. ��    ��   : 2006��12��5��
        ��    ��   : luojian 60022475
        �޸�����   : Maps3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */

    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (RRC_SECURITY_CS_SMC_CMPL ==
                    g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* �����Ա����Ͱ�ȫģʽ����                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM�����ؽ��ɹ�                     */
                    Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS );                  /* ֪ͨCC,MM�����ؽ��ɹ�                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM�����ؽ��ɹ�                     */
                    Mm_SndCcReestCnf( ( i + 8 ), MMCC_REEST_SUCCESS );          /* ֪ͨCC,MM�����ؽ��ɹ�                    */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ucPreState  = g_MmGlobalInfo.ucState;                /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E34:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */

#if (FEATURE_ON == FEATURE_ECALL)
            /* ����eCall��ʱ��������ʶ */
            NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E35
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�RRMM_SYNC_IND�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2. ��    ��   : 2007��02��16��
        ��    ��   : luojian 60022475
        �޸�����   : 3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E35(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSyncInd(pRcvMsg) )
    {
        return;
    }

    Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E36
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(AUTHENTICATION REQUEST)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E36(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    Mm_ComAuthenRcvAuthenReq();                                                 /* �յ�AUTHEN REQ�Ĵ���                     */

    return;
}
VOS_VOID Mm_Cell_S9_E37(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8       ucCause;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */

    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);    }

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

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E38
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(IDENTITY REQUEST)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E38(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComIdentity();                                                           /* IDENTITY���̵Ĵ���                       */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E39
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(TMSI REALLOCATION COMMAND)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E39(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComTmsiReloc();                                                          /* TMSI RELOC����                           */

    return;
}
VOS_VOID Mm_Cell_S9_E40(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣTIMER3230                              */
    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* ȷ�����ĸ�PD������MM����                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CCҪ������MM����                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI ) );                                           /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                 | (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI - 8 ) ) );                                     /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndCcEstCnf( (VOS_UINT32)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI), MMCC_EST_SUCCESS );                               /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */

#if (FEATURE_ON == FEATURE_ECALL)
        /* ����eCall��ʱ��������ʶ */
        NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        break;
    case MM_IE_PD_SMS_MSG:                                                      /* SMSҪ������MM����                      */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* ��GSM�����ж���Ϣ������Ҫ����SAPI3       */
        {
            if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)                    /* ���� */
            {
                if (MM_FALSE == MM_SndSapi3EstReq())
                {
                    Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E40: ERROR: snd SAPI3 est fail.");

                    g_MmGlobalInfo.ucMMConnEstingPD         = NO_MM_CONN_ESTING; /* ����û�����ڽ���������           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                    g_MmGlobalInfo.ucPagingType             = MM_NO_PAGING;

                    return;
                }

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                return;
            }
        }
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI ) ;                                            /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI - 8 ) );                                       /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI);                                                  /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */
        break;
    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SSҪ������MM����                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI );                                             /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI - 8 ) );                                       /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI, MMSS_EST_SUCCESS );                               /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E40:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* ����û�����ڽ���������                   */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E40:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* ����Ƿ��б�������Ҫ������MM����         */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_CcExist
 ��������  : CCҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_CcExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;

        /* ����ԭ��ֵ */
        default:

            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                /* ֪ͨCC,MM���ӽ���ʧ��                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_SsExist
 ��������  : SSҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SsExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;

         /* ����ԭ��ֵ */
         default:

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI           /* ������ڽ���MM���ӵı�־ */
                = NO_MM_CONN_ESTING;

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_SmsExist
 ��������  : SMSҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SmsExist( VOS_VOID )


{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
         case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

             if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

             }
             else
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
             }


             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                 = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

             break;

        /* ����ԭ��ֵ */
         default:

             Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

             break;
    }

    return;
}
VOS_VOID Mm_Cell_S9_E41(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                        /* ͣT3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣMM_TIMER_T3230                         */

    /* Modified by n00355355 for User_Exp_Improve, 2015-8-19, begin */
    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* ȷ�����ĸ�PD������MM����                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CCҪ������MM����                       */

        NAS_MM_ProcCmServiceRej_CcExist();

        break;

    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SSҪ������MM����                       */

        NAS_MM_ProcCmServiceRej_SsExist();

        break;

    case MM_IE_PD_SMS_MSG:                                                      /* SMSҪ������MM����                      */

        NAS_MM_ProcCmServiceRej_SmsExist();

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E41:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }
    /* Modified by n00355355 for User_Exp_Improve, 2015-8-19, end */

    Mm_SndMmcCmSvcRejInd( g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause );

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* �ܾ�ԭ��ֵ#4                             */
        Mm_ComRejectCause4();                                                   /* �ܾ�ԭ��ֵ#4�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComRejectCause6();                                                   /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ��¼Ҫ�����״̬                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* ����TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }

        break;
    default:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ��¼Ҫ�����״̬                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* ����TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }

        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* ����û�����ڽ���������                   */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S14_E41(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣMM_TIMER_T3230                         */

    for ( i = 0; i < MM_CONST_NUM_7; i++ )
    {                                                                           /* �ؽ���MM����                             */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( i, (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));             /* ֪ͨCC,MM���ӽ���ʧ��                    */
        }
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( ( i + 8 ), (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                            /* ֪ͨCC,MM���ӽ���ʧ��                    */
        }
        /*lint +e701*/
    }

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                                       /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                                       /* ������ڵ�MM���ӱ�־                     */

    Mm_SndMmcCmSvcRejInd(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause);

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* �ܾ�ԭ��ֵ#4                             */
        Mm_ComRejectCause4();                                                   /* �ܾ�ԭ��ֵ#4�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComRejectCause6();                                                   /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* ��¼Ҫ�����״̬                         */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM��������                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* ����TIMER3240                            */
        break;
    default:
        break;
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S9_E42(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣT3212                                  */

    switch (g_MmMsgAbort.MmIeRejCause.ucRejCause )
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComAbortCause6();                                                    /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */
        /* ֪ͨMMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:                                          /* �ܾ�ԭ��ֵ#17                            */

#if (FEATURE_ON == FEATURE_PTM)
        /* MT�ĳ����� �ñ��ΪTRUEʱΪMT */
        if (VOS_TRUE == NAS_MML_GetCsServiceConnStatusFlg())
        {
            /* �յ�CS PAGING�����ӽ����ɹ�������δ�յ�ҵ����Ϣ���յ�����ABORT���쳣��¼ */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_ABORT);
        }
#endif

        Mm_ComAbortCause17();                                                   /* �ܾ�ԭ��ֵ#17�Ĺ�������                  */
        /* ֪ͨMMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);
        break;
    default:
        break;
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E43
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(MM INFORMATION)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E43(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComInfo();                                                               /* MM INFO���̵Ĵ���                        */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E50
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-12  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8           ucTI = 0;                                               /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8          *pucCMMsg = VOS_NULL_PTR;                                /* ָ������ת��                             */
    VOS_UINT8          *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
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
        /*lint -e701*/
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

            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                ͳһ״̬��Ǩ�� WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION */
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E50:NORMAL: STATUS is  WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC������MM����                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��CC����MMCC_DATA_IND                    */
        }
        /*lint +e701*/

    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E1
  Function: MM_NULL ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.09   �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}

VOS_VOID Mm_Cell_S1_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E1:NORMAL: STATUS is MM_STATE_NULL");

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

VOS_VOID Mm_Cell_S1_E3(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */

        /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
        if ((MM_IDLE_NO_CELL_AVAILABLE != g_MmGlobalInfo.ucState)
         && (MM_IDLE_PLMN_SEARCH       != g_MmGlobalInfo.ucState))
        {
            g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;
        }

        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}
VOS_VOID Mm_Cell_S3_E6(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvGmmCombinedAttachIni(pMsg))
    {

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E6:NORMAL: STATUS is LOCATION_UPDATING_PENDING");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Mm_Cell_S9_E1(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ͣtimer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S9_E4 */



VOS_VOID Mm_Cell_S10_E1(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S10_E4 */

VOS_VOID Mm_Cell_S11_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3240].ucTimerStatus)
        {                                                                       /* ���timer 3240��������,��ֹͣ            */
            Mm_TimerStop(MM_TIMER_T3240);                                       /* ͣtimer 3240                             */
        }
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S11_E4 */

VOS_VOID Mm_Cell_S12_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E1:NORMAL: STATUS is  MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S12_E4 */


VOS_VOID Mm_Cell_S13_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E1:NORMAL: STATUS is MM_STATE_NULL");

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
/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S13_E4 */


VOS_VOID Mm_Cell_S14_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S14_E4 */


VOS_VOID Mm_Cell_S16_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ͣtimer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);



        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S16_E4 */

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S19_E4 */



VOS_UINT8 Mm_Get_UserSpecificSearchFlg_From_SysInfo(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    MMCMM_SYS_INFO_IND_STRU            *pSysInfoInd             = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pGsmSysInfoInd          = VOS_NULL_PTR;

    pSysInfoInd      = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;
    pGsmSysInfoInd   = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    if (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
    {
        return VOS_FALSE;
    }

    if (MMCMM_SYS_INFO_IND == pSysInfoInd->MsgHeader.ulMsgName )
    {
        ucUserSpecificSearchFlg = pSysInfoInd->ucUserSpecificSearchFlg;
    }
    else
    {
        ucUserSpecificSearchFlg = pGsmSysInfoInd->ucUserSpecificSearchFlg;
    }

    return ucUserSpecificSearchFlg;
}



VOS_VOID Mm_Cell_S1_E5(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();


    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if ((VOS_TRUE == ulLaiChangeFlag)
     || (MM_TRUE  == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    /* CS ONLY��PS ONLY,��NMO1����Ҫ��������ע�� */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: mmLikeB is MM_TRUE");

            if (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( ( VOS_FALSE == ulLaiChangeFlag ) &&
                     ( NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
                {
                    if ( MM_TRUE
                     == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                            MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                        Mm_ComLuOnly();                                 /* ����LU REQ                               */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn());

                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* ����LU����                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
            }
            else
            {
                if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* ����LU����                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
                else
                {
                    switch ( NAS_MML_GetCsUpdateStatus() )
                    {
                    case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                            MM_NORMAL_SERVICE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        break;
                    case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                        MM_ATTEMPTING_TO_UPDATE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_FAILURE,
                                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);    /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */
                        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {   /* A+II����Bģʽ                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }
}
VOS_VOID Mm_MakeCcEstReq(MMCC_EST_REQ_STRU *pMsg)
{
    pMsg->ulCallPri =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallPri;
    pMsg->ulCallType =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;
    pMsg->ulTransactionId =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;
    pMsg->ulCallMode =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallMode;

}

VOS_VOID Mm_MakeSmsEstReq(MMSMS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId;
    pMsg->ulEstCause = g_MmSmsEstReq.ulEstCause;
}

VOS_VOID Mm_MakeSsEstReq(MMSS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId;
}


VOS_VOID Mm_MakeGPagingInd(GRRMM_PAGING_IND_ST *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = GRRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = UEPS_PID_GAS;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(GRRMM_PAGING_IND_ST) - VOS_MSG_HEAD_LENGTH;
    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ucMSIDType                = GAS_TMSI;
    }
    else
    {
        pMsg->ucMSIDType                = GAS_IMSI;
    }
    pMsg->ucPagingType                  = 0;

    return;
}


VOS_VOID Mm_MakeWPagingInd(RRMM_PAGING_IND_STRU *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = RRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(RRMM_PAGING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->ulPagingCause                 = g_MmGlobalInfo.ucPagingCause;
    pMsg->ulCnDomainId                  = RRC_NAS_CS_DOMAIN;

    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ulPagingUeId              = RRC_TMSI_GSM_MAP_P_TMSI;
    }
    else
    {
        pMsg->ulPagingUeId              = RRC_IMSI_GSM_MAP;
    }

    pMsg->ulPagingType                  = 0;
}


VOS_VOID Mm_DealWithBuffMsg(VOS_VOID)
{
    MMCC_EST_REQ_STRU                   CcEstReqMsg;
    MMSMS_EST_REQ_STRU                  SmsMsg;                                 /* ������յ�����Ϣ����ָ��                 */
    MMSS_EST_REQ_STRU                   SsMsg;                                  /* ������յ�����Ϣ����ָ��                 */
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: deal with buffer message! ");
    if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start CC message preceed! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[23][g_MmGlobalInfo.ucState](&CcEstReqMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[61][g_MmGlobalInfo.ucState](&SmsMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[64][g_MmGlobalInfo.ucState](&SsMsg);
            /*lint +e961*/
        }
        else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
                /*lint +e961*/
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
                /*lint +e961*/
            }
        }
        else
        {
        }
    }
    else if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState )
        && (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState )
        && (WAIT_FOR_RR_CONNECTION_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState ))
    {
        if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start EMC! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E24(&CcEstReqMsg);

        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E62(&SmsMsg);
        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E65(&SsMsg);
        }
        else
        {
        }
    }
    else if (MM_WAIT_FOR_ATTACH == g_MmGlobalInfo.ucState)
    {
        if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {/* ��ʱС���϶�û�з����仯 */
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                Mm_Cell_S3_E31(&stGPagingMsg);
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                Mm_Cell_S3_E31(&stWPagingMsg);
            }
        }
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
            /* ����LAU���� �н������Ƚ��н�����*/
            enLauType = NAS_MM_GetLuType();

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);
        }

    }
    else
    {
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}



VOS_VOID Mm_Cell_S2_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurrentRatType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_LOCA_INFO_FLG);


    enCurrentRatType = NAS_MML_GetCurrNetRatType();

    if (( MM_CKSN_INVALID != NAS_MML_GetSimCsSecurityCksn() )
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrentRatType))
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
    }

    /* �����ǰLAI��֮ǰפ����LAI��ȷ����仯,��Ҫ���atttemp conterֵ */
    if (VOS_TRUE == NAS_MM_IsNeedClearAttemptCounter())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    /* CS ONLY,PS ONLY��NMO1��GMM��Ҫ��������ע�� */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
        )
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: LikeB is MM_TRUE");

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

            if ( ( VOS_FALSE == ulLaiChangeFlag )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
            {
                if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                        {
                            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                        }

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);

                    }
                    else if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
            }
            else
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {
        /* A+II����Bģʽ                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }

    Mm_DealWithBuffMsg();
}



VOS_VOID Mm_Cell_S2_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        return;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        /* �����EMC�������ȴ��ϲ����ֹ, �����ǰno rfֱ�Ӹ�cc�ظ�ʧ�� */
        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         || (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))

        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                        /* ֪ͨSMS����ʧ��                          */
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);

        /* TC״̬�յ�COVERAGE LOST��Ϣʱ��֪ͨTC�����ͷ� */
        NAS_MM_SndTcRrRelInd();
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_SERVICE);

        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E21:INFO: MmServiceState is MM_NO_SERVICE");
}
VOS_VOID Mm_Cell_S14_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E21:WARNING: MMCMM_COVERAGE_LOST_IND is not correct.");
        return;
    }

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                                  /* ��������TIMER                            */

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E21:INFO: MmServiceState is MM_NO_SERVICE");




    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);


    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    return;
}
VOS_VOID Mm_RcvRrmmRelInd()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* ��дEST CNF��Ϣ���� */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;

    RrRelInd.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrRelInd.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrRelInd.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*ֱ�ӵ���GMM������ϢRRMM_REL_IND�ĺ���*/
    /*lint -e961*/
    gaMmStateTable[33 - 1][g_MmGlobalInfo.ucState](&RrRelInd);
    /*lint +e961*/
    return;
}
/*******************************************************************************
  Module:   Mm_RcvRrmmEstCnf
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID Mm_RcvRrmmEstCnf()
{
    RRMM_EST_CNF_STRU                   RrEstCnf;

    /* ��дEST CNF��Ϣ���� */
    RrEstCnf.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrEstCnf.MsgHeader.ulMsgName        = RRMM_EST_CNF;

    RrEstCnf.ulOpId                     = g_MmGlobalInfo.ucRrEstReqOpid;
    RrEstCnf.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrEstCnf.ulResult                   = RRC_EST_EST_CONN_FAIL;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrEstCnf.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrEstCnf.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*lint -e961*/
    gaMmStateTable[31][g_MmGlobalInfo.ucState](&RrEstCnf);
    /*lint +e961*/

    return;
}
VOS_VOID Mm_Cell_S9_E21(VOS_VOID *pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg))
    {
        return;
    }

    switch (g_MmGlobalInfo.ucState)
    {
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case WAIT_FOR_OUTGOING_MM_CONNECTION:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            break;
        case LOCATION_UPDATING_INITIATED:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
             || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );
                Mm_ComDelLai();
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

                NAS_MML_InitUeIdTmsiInvalid();

                /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
                }
                /* Modified by h00313353 for iteration 9, 2015-2-4, end */

                Mm_TimerStart(MM_TIMER_T3211);
            }
            break;
        case LOCATION_UPDATE_REJECTED:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* ͣT3218                                  */
            Mm_ComDelRandRes();
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* ͣT3218                                  */
            Mm_ComDelRandRes();
            break;
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            break;
        default:
            break;
    }

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    Mm_ComProcCauseClear();

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E21:INFO: MmServiceState is MM_NO_SERVICE");

    return;
}


VOS_UINT8 NAS_MM_GetStaOfRcvXXEstReq_CSFB(VOS_VOID)
{
    VOS_UINT8                           ucState;
    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case LOCATION_UPDATING_PENDING:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_WAIT_FOR_ATTACH:
            if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
            {
                ucState = MM_IDLE_NO_IMSI;
            }
            else if ( ( MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                   && ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
            {
                ucState = MM_IDLE_LIMITED_SERVICE;
            }
            else if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
            {
                ucState = MM_IDLE_LOCATION_UPDATE_NEEDED;
            }
            else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                  || (VOS_TRUE == ulLaiChangeFlag))
            {
                ucState = MM_IDLE_ATTEMPTING_TO_UPDATE;
            }
            else
            {
                ucState = MM_IDLE_NORMAL_SERVICE;
            }
            break;

        default:
            ucState = g_MmGlobalInfo.ucState;
            break;
    }

    return ucState;
}
#if (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_MM_ResponseLmmPagingInd_CSFB(VOS_VOID)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;

    Mm_TimerStop(MM_TIMER_T3211);
    stCmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();                /* �洢CKSN                                 */


    NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())                /* ��ǰ���� GSM ���� */
    {
        /* �� GAS ���ͽ��� RR ���� */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS ���� */
    {
        g_MmGlobalInfo.ucPagingCause = RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL;
        Mm_ComMsgPagingRspSnd( &stCmRspRsp );                                   /* ��䲢���� PAGING RESPONSE ��Ϣ          */
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */

    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* ��������TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}



VOS_VOID NAS_MM_PerformBufferedSsService(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                          usMsgSize = 0;                          /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                          *pucCmSvcReq = 0;                        /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */


    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
        = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                        RcvXXEstReq.ulTransactionId
        = g_MmSsEstReq.ulTi;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

    Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);      /* ���CM SERVICE REQUEST�ṹ��             */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );       /* ���CM SERVICE REQUEST ��Ϣ              */
    if (VOS_NULL_PTR == pucCmSvcReq)
    {                                                                           /* ��Ϣ����ʧ��                             */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_PerformBufferedSsService: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                                 /* ����                                     */
    }
    else
    {                                                                           /* ��Ϣ�����ɹ�                             */
        Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
           MM_FALSE, usMsgSize, pucCmSvcReq);                                   /* ������Ϣ                                 */
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                        /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        (VOS_UINT8)g_MmSsEstReq.ulTi;                                           /* ��¼���ڽ�����MM���ӵ�TI                 */
    g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;             /* ��¼���ڽ�����MM���ӵ�PD                 */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

VOS_VOID NAS_MM_RcvSysInfo_CSFB(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulLaiChangeFlag;

    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus  = NAS_MML_GetCsUpdateStatus();

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();

    /* CSFB ���̣����LAI�ı䣬��LAU, ���LAIδ�䣬��ֱ�ӷ���ҵ�� */
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:

            /* 3GPP 24008 4.4.1:
               indicating to the network that the MS, configured to use CS fallback
               and SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell in
               NMO II or III, after intersystem change from S1 mode to Iu or A/Gb mode,
               the TIN indicates "GUTI" and the location area of the current cell is the
               same as the stored location area; NOTE1:The location updating procedure
               can be delayed when the intersystem change is due to CS fallback.
               In this case, the MS has to remember that it has to perform a
               location updating procedure after the RR connection is released,
               if the MS is still in GERAN/UTRAN.*/

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {

                /* ��ǰ���ڻ����CCҵ�񣬷���CCҵ�� */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* ��¼�յ���������ʱ��״̬                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* ��MMC����MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                    return;
                }

                /* �޻����CCҵ�񣬽����쳣���� */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* ����LAU����,LAU�ɹ������CSFB������ */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            Mm_ComLuOnly();

            return ;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                /* ��ǰ���ڻ����SSҵ�񣬷��𻺴��SSҵ�� */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                {
                    /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* ��¼�յ���������ʱ��״̬                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* ��MMC����MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_PerformBufferedSsService();
                    return;
                }

                /* �޻����CCҵ�񣬽����쳣���� */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:SS BUFFER SERVICE NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* ����LAU����,LAU�ɹ������CSFB��SSҵ�� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:

            if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
            {
                /* ����LAUЯ��CSMT��־ */
                NAS_MM_SetCsfbMtLauFlg(VOS_TRUE);
            }

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��MMC����MMCMM_LU_RESULT_IND */

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());            /* CREG״̬Ǩ�� */

                /* ��GU�£��ظ�paging response */
                NAS_MM_ResponseLmmPagingInd_CSFB();

                /* ��¼״̬ΪCSFB MT�ѷ���paging response */
                NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,
                                          NAS_MML_REG_FAIL_CAUSE_NULL);

                /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                return;
            }

            /* �޸�Ϊ���յ�CSFBѰ��ʱ��������ʱ�� */

            /* ����LAU���� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            /* ��¼״̬ΪCSFB MT����LAU���� */
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_LAU,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            /* ���lai��ͬ��ע����������lauֱ�ӷ���������� */
            if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
            {
                /* NV����lai�ı�����lau�ٽ��н������У�����LAU���� */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

                Mm_ComLuOnly();
                return;
            }

            /* ��ǰ���ڻ����CCҵ�񣬷���CCҵ�� */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
            {
                /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* ��¼�յ���������ʱ��״̬                 */

                /* ������CSFB��GU,����Ҫ��LAUʱ���ϱ�CS��ע��״̬ */
                NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist();

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }

            /* �޻����CCҵ�񣬽����쳣���� */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            return;

         default:
            break;
    }

    return;
}
#endif

VOS_VOID Mm_Cell_S3_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrentNetRatType;
    VOS_UINT8                           ucT3211RunFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg  = Mm_ComJudgeCsServExist();

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    enCurrentNetRatType = NAS_MML_GetCurrNetRatType();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    ucT3211RunFlg       = VOS_FALSE;



    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ( (VOS_TRUE == ulLaiChangeFlag) ||
        ((g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE) && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
        {
            ucT3211RunFlg = VOS_TRUE;
            Mm_TimerStop(MM_TIMER_T3211);
        }
    }
    /* <==AT2D01490 */

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
      )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                if ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
                            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
        }
        else
        {                                                                       /* RAC������0                               */
            if ( VOS_TRUE == ulLaiChangeFlag )
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
            }
        }
    }
    else
    {                                                                           /* ��A+Iģʽ                                */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComNetModeChange();
        }
        else
        {
            if ( VOS_TRUE == ulLaiChangeFlag )
            {                                                               /* ���LAI��                                */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                if (VOS_TRUE == ucT3211RunFlg)
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* A+0ģʽ,PS��֧��ʱ,LAI���ı�ʱ,3212��ʱ����LAU����Ӧ�ٴ��յ�ϵͳ��Ϣ��Ӧ��
                       �ٴη���LAU */
                    if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                     && (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                                        MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                        return;
                    }

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }

                if (enCurrentNetRatType != g_MmGlobalInfo.enPreRatType)
                {


                    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
                    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                            & MM_WAIT_CS_ATTACH))
                    {
                        NAS_MM_SndMmcAttachCnf();
                    }
                    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
                }


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            }
        }
    }

    if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
     && ((MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
      || (VOS_TRUE == ulEmergencyCallFlg)))
    {
        Mm_DealWithBuffMsg();
    }
}

VOS_VOID Mm_Cell_S3_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

VOS_VOID Mm_Cell_S3_E11(VOS_VOID *pMsg)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU   *pGprsDetachInit;

    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    pGprsDetachInit = (GMMMM_GPRS_DETACH_INITIATION_STRU*)pMsg;

    if ( GMMMM_GPRS_DETACH_NORMAL == pGprsDetachInit->enDetachType )
    {
        ;                                                                       /* �մ���                                   */
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
    }
}


VOS_VOID Mm_Cell_S32_E32(
    VOS_VOID                           *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
    }
    else
    {
        if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            if (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
            {
                /* CC�����RR���ӵĽ���, ֪ͨCC����ʧ��             */
                Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
            {
                /* SS�����RR���ӵĽ��� ��֪ͨSS,MM���ӽ���ʧ��      */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
            {
                /* SMS�����RR���ӵĽ��� ,֪ͨSMS,MM���ӽ���ʧ��      */
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else
            {
                /* û�����ڽ�����MM���ӣ������� */
            }

            /* ҵ�񴥷��Ľ������� */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
            {

                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            /* �����Ϣ�����־ */
            NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

            g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        }
    }

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

