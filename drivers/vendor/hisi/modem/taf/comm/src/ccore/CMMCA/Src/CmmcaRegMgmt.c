
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaRegMgmt.h"
#include "CmmcaCtx.h"

#include "CbpaPsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_REG_MGMT_C

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* MMA��Ϣ������ */
const CMMCA_REG_MMA_EVT_FUNC_TBL_STRU       g_astCmmcaRegEvtFuncTbl[] =
{
    {ID_TAF_MMA_SYS_CFG_SET_CNF,
        CMMCA_REG_RcvMmaSysCfgCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,
        CMMCA_REG_RcvMmaPhoneModeSetcnf},
    {ID_TAF_MMA_ACQ_BEST_NETWORK_CNF,
        CMMCA_REG_RcvMmaAcqCnf},
    {ID_TAF_MMA_SERVICE_STATUS_IND,
        CMMCA_REG_RcvMmaServiceStateInd},
    {ID_TAF_MMA_ACQ_IND,
        CMMCA_REG_RcvMmaAcqInd},
    {ID_TAF_MMA_POWER_SAVE_CNF,
        CMMCA_REG_RcvMmaPowerSaveCnf},
    {ID_TAF_MMA_REG_CNF,
        CMMCA_REG_RcvMmaRegCnf},
    {ID_TAF_MMA_DETACH_CNF,
        CMMCA_REG_RcvMmaDetachCnf},
    {ID_TAF_MMA_SYS_INFO_IND,
        CMMCA_REG_RcvMmaSysInfoInd},
    {ID_TAF_MMA_SIM_STATUS_IND,
        CMMCA_REG_RcvMmaSimStatusInd}
};

/* g_astCmmcaRegEvtFuncTbl��Item���� */
const VOS_UINT32 g_ulCmmcaRegEvtFuncTblSize  = sizeof(g_astCmmcaRegEvtFuncTbl) / sizeof(g_astCmmcaRegEvtFuncTbl[0]);

/*****************************************************************************
  3 ��������
*****************************************************************************/



VOS_VOID CMMCA_REG_RcvRatModeReq(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
    CMMCA_MMC_RAT_MODE_REQ_STRU         stModeReq;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stModeReq, 0, sizeof(CMMCA_MMC_RAT_MODE_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseModeReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                 pstDataInd->aucData,
                                 &stModeReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatModeReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
        return;
    }

    /* ĿǰCL��������balong modem��Ҫ����ΪPS only����˴�ʱ����ctxΪPS */
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    pstRegCtx->enSrvDomain = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */

    /* ����API�ӿ�TAF_MMA_SysCfgReq */
    PS_MEM_SET(&stSysCfgPara, 0x00, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    /* ���ڹ��ڰ汾���Ĵ�������������NV8266�رգ�2��ʾ���ı� */
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    stSysCfgPara.enRoam                    = TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON;
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */

    /* �����������NV8266������������Ϊ4����ʾ���ı� */
    if (VOS_TRUE == pstRegCtx->stUserCfgInfo.ucIsRoamActive)
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
        stSysCfgPara.enRoam = TAF_MMA_ROAM_UNCHANGE;
        /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    }

    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stSysCfgPara.enSrvDomain               = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    stSysCfgPara.enUserPrio                = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    stSysCfgPara.stRatOrder.ucRatOrderNum  = 1;
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    stSysCfgPara.stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    /* Ƶ�β��ı� */
    stSysCfgPara.stGuBand.ulBandLow        = TAF_PH_BAND_NO_CHANGE;
    stSysCfgPara.stGuBand.ulBandHigh       = 0;
    stSysCfgPara.stLBand.ulBandLow         = TAF_PH_BAND_NO_CHANGE;
    stSysCfgPara.stLBand.ulBandHigh        = 0;

    if (VOS_TRUE != TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stSysCfgPara))
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}
VOS_VOID CMMCA_REG_RcvPowerUpReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_POWERUP_REQ_STRU      stPowerUpReq;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    ucOpId = 0;

    PS_MEM_SET(&stPowerUpReq, 0, sizeof(CMMCA_MMC_RAT_POWERUP_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParsePowerUpReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPowerUpReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerUpReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        return;
    }

    /* ����API�ӿ�TAF_MMA_PhoneModeSetReq(full mode)���Ϳ�����Ϣ��MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;
    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPhoneModePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerUpReq: PhoneModeSetReq SEND fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}
VOS_VOID CMMCA_REG_RcvPowerDownReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd      = VOS_NULL_PTR;
    CMMCA_MMC_RAT_POWERDOWN_REQ_STRU    stPowerDownReq;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stPowerDownReq, 0, sizeof(CMMCA_MMC_RAT_POWERDOWN_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParsePowerDownReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPowerDownReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerDownReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(stPowerDownReq.enRatId, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* ����API�ӿ�TAF_MMA_PhoneModeSetReq(mini mode)���Ϳ�����Ϣ��MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_MINI;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;

    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPhoneModePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerDownReq: TAF_MMA_PhoneModeSetReq SEND fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(stPowerDownReq.enRatId, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}
VOS_VOID CMMCA_REG_RcvRatAcqReq(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_ACQ_REQ_STRU          stAcqReq;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stAcqReq, 0, sizeof(CMMCA_MMC_RAT_ACQ_REQ_STRU));
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    PS_MEM_SET(&stAcqPara, 0, sizeof(TAF_MMA_ACQ_PARA_STRU));

    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseAcqReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                pstDataInd->aucData,
                                &stAcqReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);
        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatAcqReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);

        return;
    }

    /* ����API�ӿ�TAF_MMA_AcqReq�����ʼ��������*/
    if (CMMCA_RAT_ACQ_REQ_REASON_INIT_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_POWER_UP;
    }
    else if (CMMCA_RAT_ACQ_REQ_REASON_OOS_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_OOS;
    }
    else if (CMMCA_RAT_ACQ_REQ_REASON_BSR_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_HIGH_PRIO;
    }
    else
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_OOS;
        CMMCA_WARNING_LOG("CMMCA_REG_RcvRatAcqReq: unkownn acq reason!");
    }

    if (VOS_TRUE != TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stAcqPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatAcqReq: TAF_MMA_AcqBestNetworkReq SEND fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* ����Modem��״̬ΪACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}


VOS_VOID CMMCA_REG_RcvMccSearchReq(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;
    CMMCA_RAT_MMC_RAT_SYS_INFO_STRU     stSysInfo;

    PS_MEM_SET(&stSysInfo, 0, sizeof(CMMCA_RAT_MMC_RAT_SYS_INFO_STRU));

    /* ��ѯCMMCA���ر����MCC��Ϣ*/
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    /* �ظ�ID_CMMCA_RAT_MMC_MCC_SEARCH_RSP��RAT */
    stSysInfo.ulMcc = pstRegCtx->stPlmnId.Mcc;
    stSysInfo.ulMnc = pstRegCtx->stPlmnId.Mnc;

    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    stSysInfo.stEutran.usEarfcn = (VOS_UINT16)pstRegCtx->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    CMMCA_REG_SndMccSearchRsp(CMMCA_MMC_RAT_ID_EUTRAN, &stSysInfo);

    return;
}


VOS_VOID CMMCA_REG_RcvPsRegReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_PS_REG_REQ_STRU       stPsRegReq;
    TAF_MMA_REG_PARA_STRU               stRegPara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stPsRegReq, 0, sizeof(CMMCA_MMC_RAT_PS_REG_REQ_STRU));
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParsePsRegReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPsRegReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPsRegReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* ����MMAģ��API�ӿ�TAF_MMA_RegReq������ָ�����������緢��ע��*/
    stRegPara.bitOpPrioClass       = 1;

    if (CMMCA_RAT_GMSS_PRIORITY_CLASS_HOME == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_HOME;
    }
    else if (CMMCA_RAT_GMSS_PRIORITY_CLASS_PREF == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_PREF;
    }
    else if (CMMCA_RAT_GMSS_PRIORITY_CLASS_ANY == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
    }
    else
    {
        CMMCA_WARNING_LOG("CMMCA_REG_RcvPsRegReq: unkown enPriorityClass!");
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
    }
    stRegPara.bitOpEpsAttachReason = 1;
    if (CMMCA_RAT_ATTACH_TYPE_HANDOVER == stPsRegReq.ucAttachType)
    {
        stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_HANDOVER;
    }
    else
    {
        stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_INITIAL;
    }

    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stRegPara.enAttachDomain       = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */

    if (VOS_TRUE != TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stRegPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPsRegReq: TAF_MMA_RegReq SEND fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* ����Modem��״̬ΪACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}


VOS_VOID CMMCA_REG_RcvCellInfoPsRegReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                                *pstDataInd           = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU                *pstCellInfoPsRegReq  = VOS_NULL_PTR;
    TAF_MMA_REG_PARA_STRU                                   stRegPara;
    VOS_UINT32                                              ulRslt;
    VOS_UINT8                                               ucOpId;
    VOS_UINT32                                              i;
    CMMCA_RAT_SYS_INFO_STRU                                 stRatInfo;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));
    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    /* Ϊ��������Ϣ�����ڴ� */
    pstCellInfoPsRegReq = (CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_CMMCA, sizeof(CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU));
    if (VOS_NULL_PTR == pstCellInfoPsRegReq)
    {
        /* �쳣��ӡ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: PS_MEM_ALLOC fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseCellInfoPsRegReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    pstCellInfoPsRegReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

        return;
    }

    /* ����MMAģ��API�ӿ�TAF_MMA_RegReq������ָ�����������緢��ע��*/
    stRegPara.bitOpCellInfo        = 1;
    stRegPara.bitOpEpsAttachReason = 1;
    stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_HANDOVER; /* C->L��ѡʱ��д��ԭ�� */
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stRegPara.enAttachDomain       = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    stRegPara.stCellInfo.ulArfcn   = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.usEarfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    stRegPara.stCellInfo.ucCellNum = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.usNumCell;
    stRegPara.stCellInfo.ucPlmnNum = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.ucNumPlmn;

    for ( i = 0; i < stRegPara.stCellInfo.ucCellNum; i++ )
    {
        stRegPara.stCellInfo.ausCellId[i] = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.ausCellId[i];
    }

    for ( i = 0; i < stRegPara.stCellInfo.ucPlmnNum; i++ )
    {
        stRegPara.stCellInfo.astPlmnId[i].Mcc = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.aulMcc[i];
        stRegPara.stCellInfo.astPlmnId[i].Mnc = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.aulMnc[i];
    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

    if (VOS_TRUE != TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stRegPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: TAF_MMA_RegReq SEND fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* ����Modem��״̬ΪACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}
VOS_VOID CMMCA_REG_RcvPktDataCmdReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    VOS_UINT8                           ucOpId;
    VOS_UINT32                          ulRslt;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPktDataCmdReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* ִ��Detach���� */
    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));
    stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_3GPP2_ATTACHED;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPktDataCmdReq: TAF_MMA_DetachReq SEND fail!");

        /* ֱ�ӻ�REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}
VOS_VOID CMMCA_REG_RcvNoServiceReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU   stNoServReq;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stNoServReq, 0 , sizeof(CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseNoServiceReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stNoServReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

        return;
    }

    /* ���ԭ��ֵ��OOS����MMAģ��API�ӿ�TAF_MMA_DetachReq������LTE detach���� */
    if (CMMCA_MMC_RAT_NOSVC_CAUSE_OOSA != stNoServReq.enCause)
    {
        /* ִ��Detach���� */
        PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));
        stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_USER_DETACH;
        /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
        stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;
        /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
        if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
        {
            CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: TAF_MMA_DetachReq SEND fail!");

            /* ֱ�ӻ�RSP(FAIL) */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

            /* �ͷ�opid,��ջ��� */
            CMMCA_DelItemInCmdBufferQueue(ucOpId);

            return ;
        }
    }
    /* �������TAF_MMA_PowerSaveReq */
    else
    {
        /* ִ��PowerSave���� */
        PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));
        if (VOS_TRUE != TAF_MMA_PowerSaveReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPowerSavePara))
        {
            CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: TAF_MMA_PowerSaveReq SEND fail!");

            /* ֱ�ӻ�RSP(FAIL) */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

            /* �ͷ�opid,��ջ��� */
            CMMCA_DelItemInCmdBufferQueue(ucOpId);
        }
    }

    return;
}


VOS_VOID CMMCA_REG_RcvBearDetachReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU  stBearDetachReq;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stBearDetachReq, 0, sizeof(CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseBearDetachReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                      pstDataInd->aucData,
                                      &stBearDetachReq);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        return;
    }

    /* ����OPID,����pMsg����OPID��Ӧ��buffer */
    ucOpId = 0x0;

    CMMCA_AssignOpid(&ucOpId);

    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);

    if (VOS_OK != ulRslt)
    {
        /* ��ӡ������Ϣ */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvBearDetachReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        return;
    }

    /* ִ��Detach���� */
    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_USER_DETACH;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */

    if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvBearDetachReq: TAF_MMA_DetachReq SEND fail!");

        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return ;
    }

    return;
}
VOS_VOID CMMCA_REG_RcvMmaSysCfgCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    ucOpid       = ((TAF_MMA_SYS_CFG_CNF_STRU*)pMsg)->ucOpid;
    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaSysCfgCnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_RAT_MODE_REQ ,������cnf */
    if (ID_CMMCA_MMC_RAT_RAT_MODE_REQ != CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaSysCfgCnf: cmdId invalid!");

        return;
    }

    /* �ظ�ID_CMMCA_RAT_MMC_RAT_MODE_RSP��RAT */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != ((TAF_MMA_SYS_CFG_CNF_STRU*)pMsg)->enRslt)
    {

        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
    }
    else
    {
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_SUCC);
    }

    /* �ͷ�opid,��ջ��� */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}


VOS_VOID CMMCA_REG_RcvMmaPhoneModeSetcnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    ucOpid       = ((TAF_MMA_PHONE_MODE_SET_CNF_STRU*)pMsg)->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPhoneModeSetcnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_POWERUP_REQ/ID_CMMCA_MMC_RAT_POWERDOWN_REQ ,������cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_POWERUP_REQ   != usCmdId)
     && (ID_CMMCA_MMC_RAT_POWERDOWN_REQ != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPhoneModeSetcnf: cmdId invalid!");

        return;
    }

    /* ����Modem��״̬ΪINACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

    /* ����ID_TAF_MMA_PHONE_MODE_SET_CNF����ظ�����ID_CMMCA_RAT_MMC_POWERUP_RSP/ID_CMMCA_RAT_MMC_POWERDOWN_RSP�ػ���Ӧ��RAT */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    if (ID_CMMCA_MMC_RAT_POWERUP_REQ == usCmdId)
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS ==(((TAF_MMA_PHONE_MODE_SET_CNF_STRU*)pMsg)->enRslt))
        {
            CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_SUCCESS);  /* �����ɹ� */
            pstRegCtx = CMMCA_REG_GetCtxAddr();
            if (VOS_FALSE == pstRegCtx->ucPsSimValid)/* �����������б���Ŀ�״̬��Ϣ������NTWָʾ��CBPCA */
            {
                CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_INIT, &stRatInfo); /* �޿� */
            }
        }
        else
        {
            CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL); /* ����ʧ�� */
        }
    }
    else
    {
        CMMCA_REG_SndPowerDownRsp(CMMCA_MMC_RAT_ID_EUTRAN);  /* �ػ��ɹ� */

    }

    /* �ͷ�opid,��ջ��� */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}


VOS_VOID CMMCA_REG_RcvMmaAcqCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer    = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx       = VOS_NULL_PTR;
    TAF_MMA_ACQ_CNF_STRU               *pstAcqCnf       = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    pstAcqCnf    = (TAF_MMA_ACQ_CNF_STRU*)pMsg;
    ucOpid       = pstAcqCnf->ucOpid;
    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaAcqCnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_ACQ_REQ,������cnf */
    if (ID_CMMCA_MMC_RAT_ACQ_REQ != CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaAcqCnf: cmdId invalid!");

        return;
    }

    if (TAF_MMA_APP_OPER_RESULT_REJECT == pstAcqCnf->enRslt)
    {
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_ACQ_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpid);

        return;
    }

    /* �����ȡ�ɹ��������յ���plmn id��Ƶ�� */
    pstRegCtx               = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc = pstAcqCnf->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc = pstAcqCnf->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, begin */
    pstRegCtx->ulArfcn      = pstAcqCnf->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, end */
    pstRegCtx->enPrioClass  = pstAcqCnf->enPrioClass;

    /* �ظ�ID_CMMCA_RAT_MMC_ACQ_RSP��CBPCA */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAcqCnf->enRslt)
    {
        enRslt = CMMCA_RAT_ACQ_RESULT_ACQUIRED;
    }
    else
    {
        enRslt = CMMCA_RAT_ACQ_RESULT_ACQFAILED;
    }

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstAcqCnf->enPrioClass);

    stRatInfo.ulMcc           = pstAcqCnf->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstAcqCnf->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, begin */
    stRatInfo.usEarfcn        = (VOS_UINT16)pstAcqCnf->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, end */

    CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, enRslt, &stRatInfo);


    /* �ͷ�opid,��ջ��� */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}


VOS_VOID CMMCA_REG_RcvMmaServiceStateInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstServStatusInd  = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;
    VOS_UINT32                          i;

    /* ��ȡ���µķ���״̬��Ϣ������ */
    pstServStatusInd        = (TAF_MMA_SERVICE_STATUS_IND_STRU*)pMsg;
    pstRegCtx               = CMMCA_REG_GetCtxAddr();

    /* ��������, �����ǰ��������6����Ϣ��Ӧ�Ĳ��������ñ�״̬������ */
    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if ((VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
         && (CMMCA_OPID_INVILID_VALUE != pstCmdBufferQueue[i].ucOpId))
        {
            usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBufferQueue[i].pucMsgInfo);
            if ((ID_CMMCA_MMC_RAT_ACQ_REQ              == usCmdId)
             || (ID_CMMCA_MMC_RAT_PS_REG_REQ           == usCmdId)
             || (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ == usCmdId)
             || (ID_CMMCA_MMC_RAT_POWERDOWN_REQ        == usCmdId)
             || (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ       == usCmdId)
             || (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ    == usCmdId))
            {
                pstRegCtx->ucPsSrvSta     = pstServStatusInd->PsSrvSta;
                pstRegCtx->ucPsSimValid   = pstServStatusInd->ucPsSimValid;
                pstRegCtx->ucCsSrvSta     = pstServStatusInd->CsSrvSta;
                pstRegCtx->ucCsSimValid   = pstServStatusInd->ucCsSimValid;

                return;
            }
        }
    }

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    if (TAF_REPORT_SRVSTA_NO_SERVICE == pstServStatusInd->PsSrvSta)
    {
        stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
        stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    }
    else
    {
        stRatInfo.ulMcc           = pstRegCtx->stPlmnId.Mcc;
        stRatInfo.ulMnc           = pstRegCtx->stPlmnId.Mnc;
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
        stRatInfo.usEarfcn        = (VOS_UINT16)pstRegCtx->ulArfcn;
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    }

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstRegCtx->enPrioClass);

    /* �жϷ���״̬�Ƿ����仯������仯��Ҫ������״̬ */
    if (CMMCA_MODEM_STATUS_ACTIVE == CMMCA_GetModemStatus())
    {
        CMMCA_REG_SndNtwIndRpt(&stRatInfo, pstServStatusInd);
    }

    /* �������µķ���״̬��Ϣ�������� */
    pstRegCtx->ucPsSrvSta   = pstServStatusInd->PsSrvSta;
    pstRegCtx->ucPsSimValid = pstServStatusInd->ucPsSimValid;
    pstRegCtx->ucCsSrvSta   = pstServStatusInd->CsSrvSta;
    pstRegCtx->ucCsSimValid = pstServStatusInd->ucCsSimValid;

    return;
}


VOS_VOID CMMCA_REG_RcvMmaAcqInd(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACQ_IND_STRU               *pstAcqInd   = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx   = VOS_NULL_PTR;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;


    /* �������µķ���״̬��Ϣ�������� */
    pstAcqInd = (TAF_MMA_ACQ_IND_STRU*)pMsg;
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    pstRegCtx->stPlmnId.Mcc     = pstAcqInd->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc     = pstAcqInd->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, begin */
    pstRegCtx->ulArfcn          = pstAcqInd->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, end */
    pstRegCtx->enPrioClass      = pstAcqInd->enPrioClass;

    /* �ظ�ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND(RAT_ACQUIRE)��RAT */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstAcqInd->enPrioClass);

    stRatInfo.ulMcc           = pstAcqInd->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstAcqInd->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, begin */
    stRatInfo.usEarfcn        = (VOS_UINT16)pstAcqInd->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, end */

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAcqInd->enRslt)
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_ACQED, CMMCA_RAT_CPST_ACQUIRED, &stRatInfo);
    }

    return;
}


VOS_VOID CMMCA_REG_RcvMmaPowerSaveCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer    = VOS_NULL_PTR;
    TAF_MMA_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    pstPowerSaveCnf = (TAF_MMA_POWER_SAVE_CNF_STRU*)pMsg;
    ucOpid          = pstPowerSaveCnf->ucOpid;
    pstCmdBuffer    = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPowerSaveCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_NO_SERVICE_REQ/ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ/
        ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,������cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_NO_SERVICE_REQ         != usCmdId)
     && (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ != usCmdId)
     && (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ      != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPowerSaveCnf: cmdId invalid!");
        return;
    }

    if (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ == usCmdId)
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstPowerSaveCnf->enRslt)
        {
            /* �ظ�ID_CMMCA_RAT_MMC_NO_SERVICE_RSP��CBPCA */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_SUCC);



            /* ����Modem��״̬ΪINACTIVE */
            CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);
        }
        else
        {
            /* �ظ�ID_CMMCA_RAT_MMC_NO_SERVICE_RSP/ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP��CBPCA */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);
        }
    }
    else if (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ == usCmdId)
    {
        /* �ظ�ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP��CBPCA */
        CMMCA_REG_SndPktDataCmdRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_DISABLED);


        /* ����Modem��״̬ΪINACTIVE */
        CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);
    }
    else
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstPowerSaveCnf->enRslt)
        {
            CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_SUCC);

            /* �ظ�ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND(RAT_ACQUIRE)��RAT */
            PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

            stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
            stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
            stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

            CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_PS_DEREGED, CMMCA_RAT_CPST_SYSLOST, &stRatInfo);
        }
        else
        {
            CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);
        }
    }

    /* �ͷ�opid,��ջ��� */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}
 VOS_VOID CMMCA_REG_RcvMmaRegCnf(
     VOS_VOID                           *pMsg
 )
 {
     CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
     CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
     TAF_MMA_REG_CNF_STRU               *pstRegCnf    = VOS_NULL_PTR;
     VOS_UINT8                           ucOpid;
     CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
     CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    pstRegCnf = (TAF_MMA_REG_CNF_STRU*)pMsg;
    ucOpid    = pstRegCnf->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaRegCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_PS_REG_REQ,������cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_PS_REG_REQ           != usCmdId)
     && (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaRegCnf: cmdId invalid!");
        return;
    }

    /* �������µķ���״̬��Ϣ�������� */
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc     = pstRegCnf->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc     = pstRegCnf->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstRegCtx->ulArfcn          = pstRegCnf->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    pstRegCtx->enPrioClass      = pstRegCnf->enPrioClass;

    /* �ظ�ID_CMMCA_RAT_MMC_PS_REG_RSP/ID_CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP��CBPCA */
    /* ����ע����������CMMCA��ǰ״̬ */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstRegCnf->enPrioClass);

    stRatInfo.ulMcc           = pstRegCnf->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstRegCnf->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    stRatInfo.usEarfcn        = (VOS_UINT16)pstRegCnf->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    CMMCA_REG_SndRegRsp(pstRegCnf->enRslt, pstRegCnf->enLmmAttachRegStatus, usCmdId, &stRatInfo);

    /*�ظ�ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND��CBPCA */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstRegCnf->enRslt)
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_AUTOMATIC, CMMCA_RAT_CPST_REGISTERED, &stRatInfo);
    }
    else
    {
        if (VOS_FALSE == pstRegCtx->ucPsSimValid)
        {
            CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_SYSLOST, &stRatInfo);
        }
    }

    /* �ͷ�opid,��ջ��� */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

     return;
 }


VOS_VOID CMMCA_REG_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;

    /* ������Ϣ��opid,����opid���һ����������Ϣ */
    ucOpid = ((TAF_MMA_DETACH_CNF_STRU*)pMsg)->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* ����������Ϣ�쳣�жϣ��������ID_CMMCA_MMC_RAT_NO_SERVICE_REQ/ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ/
        ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,������cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_NO_SERVICE_REQ         != usCmdId)
     && (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ != usCmdId)
     && (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ      != usCmdId))
    {

        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf:  cmdId invalid!");
        return;
    }

    /* ����TAF_MMA_PowerSaveReq */
    PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));
    if (VOS_TRUE != TAF_MMA_PowerSaveReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid, &stPowerSavePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf: TAF_MMA_PowerSaveReq SEND fail!");

        /* �ͷ�opid,��ջ��� */
        CMMCA_DelItemInCmdBufferQueue(ucOpid);
    }

    return;
}


VOS_VOID CMMCA_REG_RcvMmaSimStatusInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx       = VOS_NULL_PTR;
    TAF_MMA_SIM_STATUS_IND_STRU        *pstSimStatusInd = VOS_NULL_PTR;

    /* �������µķ���״̬��Ϣ�������� */
    pstSimStatusInd = (TAF_MMA_SIM_STATUS_IND_STRU*)pMsg;
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    if (TAF_MMA_CARD_STATUS_AVAILABLE == pstSimStatusInd->enCardStatus)
    {
        pstRegCtx->ucPsSimValid     = VOS_TRUE;
        pstRegCtx->ucCsSimValid     = VOS_TRUE;
    }
    else
    {
        pstRegCtx->ucPsSimValid     = VOS_FALSE;
        pstRegCtx->ucCsSimValid     = VOS_FALSE;
    }

    return;
}
VOS_VOID  CMMCA_REG_RcvMmaSysInfoInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;
    TAF_MMA_SYS_INFO_IND_STRU          *pstSysInfoInd     = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;
    VOS_UINT32                          i;

    /* �������µ�λ����Ϣ�������� */
    pstSysInfoInd = (TAF_MMA_SYS_INFO_IND_STRU*)pMsg;

    pstRegCtx               = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc = pstSysInfoInd->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc = pstSysInfoInd->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstRegCtx->ulArfcn      = pstSysInfoInd->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* ��������, �����ǰ��������5����Ϣ��Ӧ�Ĳ��������ñ�״̬������ */
    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if ((VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
         && (CMMCA_OPID_INVILID_VALUE != pstCmdBufferQueue[i].ucOpId))
        {
            usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBufferQueue[i].pucMsgInfo);
            if ((ID_CMMCA_MMC_RAT_ACQ_REQ              == usCmdId)
             || (ID_CMMCA_MMC_RAT_PS_REG_REQ           == usCmdId)
             || (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ == usCmdId)
             || (ID_CMMCA_MMC_RAT_POWERDOWN_REQ        == usCmdId)
             || (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ       == usCmdId))
            {
                pstRegCtx->enPrioClass  = pstSysInfoInd->enPrioClass;

                return;
            }
        }
    }

    /* �����ǰ�����������������ȼ������˸ı䣬�ϱ�ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstSysInfoInd->enPrioClass);

    stRatInfo.ulMcc           = pstSysInfoInd->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstSysInfoInd->stPlmnId.Mnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    stRatInfo.usEarfcn        = (VOS_UINT16)pstSysInfoInd->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstRegCtx->ucPsSrvSta)
     && (pstRegCtx->enPrioClass != pstSysInfoInd->enPrioClass))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_PRI_CHG, CMMCA_RAT_CPST_REGISTERED, &stRatInfo);
    }

    pstRegCtx->enPrioClass  = pstSysInfoInd->enPrioClass;

    return;
}
VOS_VOID CMMCA_REG_RcvMmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulIndex;
    CMMCA_REG_MMA_EVT_FUNC              pMmaEvtFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstHeader  = VOS_NULL_PTR;  /* ������Ϣͷָ��*/

    /* ��ȡ��Ϣͷָ��*/
    pstHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ���g_astCmmcaRegEvtFuncTbl */
    for (ulIndex = 0; ulIndex < g_ulCmmcaRegEvtFuncTblSize; ulIndex++)
    {
        if (pstHeader->ulMsgName == g_astCmmcaRegEvtFuncTbl[ulIndex].ulMsgId)
        {
            pMmaEvtFunc = g_astCmmcaRegEvtFuncTbl[ulIndex].pMmaEvtFunc;

            break;
        }
    }

    if (VOS_NULL_PTR == pMmaEvtFunc)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaMsg: Not find msg proc func");
        return;
    }
    else
    {
        pMmaEvtFunc(pstMsg);
    }

    return;
}
VOS_VOID CMMCA_REG_SndNtwIndRpt(
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo,
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstServStatusInd
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;

    /* ��ȡ���µķ���״̬��Ϣ������ */
    pstRegCtx               = CMMCA_REG_GetCtxAddr();

    /* �жϷ���״̬�Ƿ����仯������仯 */
    /* ���·���״̬Ϊ����Ч���ϱ�RAT_SUSPEND */
    if ((VOS_TRUE == pstRegCtx->ucPsSimValid)
     && (VOS_FALSE == pstServStatusInd->ucPsSimValid))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_SYSLOST, pstRatInfo);

        return;
    }

    /* ���·���״̬Ϊ�޷�������Ʒ����ϱ�RAT_SYSLOST */
    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstRegCtx->ucPsSrvSta)
     && (TAF_REPORT_SRVSTA_NORMAL_SERVICE != pstServStatusInd->PsSrvSta))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SYSLOST, CMMCA_RAT_CPST_SYSLOST, pstRatInfo);

        return;
    }

    /* ���·���״̬Ϊ���������ϱ�RAT_RECOVERY */
    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE != pstRegCtx->ucPsSrvSta)
     && (TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstServStatusInd->PsSrvSta))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_RECOVERY, CMMCA_RAT_CPST_REGISTERED, pstRatInfo);
    }

    return;
}
VOS_VOID CMMCA_REG_SndPowerUpRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8                 enResult
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;

    /* ���� CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    CMMCA_RAT_MMC_POWERUP_RSP_STRU      stPowerUpRsp;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_POWERUP_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPowerUpRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ����CMMCA_PackBearDiscRsp�������������Ϣ */
    stPowerUpRsp.enRatId  = enRatId;
    stPowerUpRsp.enResult = enResult;

    ulRslt = CMMCA_PackPowerUpRsp(&stPowerUpRsp, CMMCA_CMD_RAT_POWERUP_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        CMMCA_ERROR_LOG("CMMCA_REG_SndPowerUpRsp:CMMCA_PackPowerUpRsp fail");

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_POWERUP_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndPowerDownRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8     enRatId
)
{
    /* ���� CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    CMMCA_RAT_MMC_POWERDOWN_RSP_STRU    stPowerDownRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndModeRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ����CMMCA_PackPowerDownRsp�������������Ϣ */
    stPowerDownRsp.enRatId = enRatId;
    ulRslt = CMMCA_PackPowerDownRsp(&stPowerDownRsp, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndModeRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_MMC_MODE_RSP_RESULT_ENUM_UINT8                    enResult
)
{
    CMMCA_RAT_MMC_RAT_MODE_RSP_STRU     stModeCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_MODE_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndModeRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    stModeCnf.enRatId  = enRatId;
    stModeCnf.enResult = enResult;

    /* ����CMMCA_PackModeRsp�������������Ϣ */
    ulRslt = CMMCA_PackModeRsp(&stModeCnf, CMMCA_CMD_RAT_MODE_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_MODE_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndAcqRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    CMMCA_RAT_MMC_ACQ_RSP_STRU          stAcqCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_ACQ_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndAcqRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_RAT_MMC_ACQ_RSP_STRU */
    stAcqCnf.enRatId                                  = enRatId;
    stAcqCnf.enResult                                 = enRslt;
    stAcqCnf.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stAcqCnf.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stAcqCnf.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    stAcqCnf.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    if (CMMCA_RAT_ACQ_RESULT_ACQUIRED == enRslt)
    {
        stAcqCnf.stRatSysInfo.ucRatInfoValid          = VOS_TRUE;
    }
    else
    {
        stAcqCnf.stRatSysInfo.ucRatInfoValid          = VOS_FALSE;
    }

    /* ����CMMCA_PackModeRsp�������������Ϣ */
    ulRslt = CMMCA_PackAcqRsp(&stAcqCnf, CMMCA_CMD_RAT_ACQ_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_ACQ_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndMccSearchRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_MMC_RAT_SYS_INFO_STRU    *pstSysInfo
)
{

    CMMCA_RAT_MMC_MCC_SEARCH_RSP_STRU   stMccSearchRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_SEARCH_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndMccSearchRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_RAT_MMC_ACQ_RSP_STRU */
    stMccSearchRsp.enRatId        = enRatId;
    stMccSearchRsp.ulMcc          = pstSysInfo->ulMcc;
    stMccSearchRsp.ulMnc          = pstSysInfo->ulMnc;
    stMccSearchRsp.ucRatInfoValid = VOS_TRUE;

    stMccSearchRsp.stEutran.usEarfcn = pstSysInfo->stEutran.usEarfcn;
    stMccSearchRsp.stEutran.ulPlmn   = pstSysInfo->stEutran.ulPlmn;

    /* ����CMMCA_PackMccSearchRsp�������������Ϣ */
    ulRslt = CMMCA_PackMccSearchRsp(&stMccSearchRsp, CMMCA_CMD_RAT_SEARCH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_SEARCH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndRegRsp(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachRegStatus,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_REGISTERED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_SUCCESS, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }

    }
    /* פ�����磬ע��ʧ�� */
    else if (TAF_MMA_APP_OPER_RESULT_FAILURE == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_ACQUIRED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_PS_REG_FAIL, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
    }
    /* ����ʧ�� */
    else if (TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_ACQFAILED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_ACQ_FAIL, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
    }
    else
    {

        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        }

        else
        {
            CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        }
    }


    return;
}


VOS_VOID CMMCA_REG_SndPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_REG_RESULT_ENUM_UINT8                         enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
)
{

    CMMCA_RAT_MMC_PS_REG_RSP_STRU       stPsRegRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_PS_REG_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPsRegRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_RAT_MMC_PS_REG_RSP_STRU */
    stPsRegRsp.enRatId                                  = enRatId;
    stPsRegRsp.enResult                                 = enResult;
    stPsRegRsp.enLmmAttachRegStatus                     = enLmmAttachRegStatus;
    stPsRegRsp.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stPsRegRsp.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stPsRegRsp.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    if ((CMMCA_RAT_REG_RESULT_REGISTERED == enResult)
     || (CMMCA_RAT_REG_RESULT_ACQUIRED   == enResult))
    {
        stPsRegRsp.stRatSysInfo.ucRatInfoValid          = VOS_TRUE;
    }
    else
    {
        stPsRegRsp.stRatSysInfo.ucRatInfoValid          = VOS_FALSE;
    }

    stPsRegRsp.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* ����CMMCA_PackModeRsp�������������Ϣ */
    ulRslt = CMMCA_PackPsRegRsp(&stPsRegRsp, CMMCA_CMD_RAT_PS_REG_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_PS_REG_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndCellInfoPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_MMC_STATUS_ENUM_UINT8                         enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
)
{

    CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU                 stCellInfoPsRegRsp;
    VOS_UINT8                                              *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndCellInfoPsRegRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* ���� CMMCA_RAT_MMC_PS_REG_RSP_STRU */
    stCellInfoPsRegRsp.enRatId                                               = enRatId;
    stCellInfoPsRegRsp.stIratRegRsp.enResult                                 = enResult;
    stCellInfoPsRegRsp.stIratRegRsp.enLmAttachRegStatus                      = enLmmAttachRegStatus;
    stCellInfoPsRegRsp.stIratRegRsp.enTargetSystemType                       = CMMCA_RAT_SYSTEM_TYPE_EUTRAN;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    if ((CMMCA_RAT_MMC_STATUS_SUCCESS == enResult)
     || (CMMCA_RAT_MMC_STATUS_PS_REG_FAIL == enResult))
    {
         stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ucRatInfoValid         = VOS_TRUE;
    }
    else
    {
         stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ucRatInfoValid         = VOS_FALSE;
    }
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* ����CMMCA_PackCellInfoPsRegRsp�������������Ϣ */
    ulRslt = CMMCA_PackCellInfoPsRegRsp(&stCellInfoPsRegRsp, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN, pucCmdData);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndNoServiceRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
)
{

    CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU   stNoServRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndNoServiceRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* ���� CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU */
    stNoServRsp.enRatId  = enRatId;
    stNoServRsp.ucStatus = ucStatus;

    /* ����CMMCA_PackNoServiceRsp�������������Ϣ */
    ulRslt = CMMCA_PackNoServiceRsp(&stNoServRsp, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndNtwStChgInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8   enCause,
    CMMCA_RAT_CPST_ENUM_UINT8           enStatus,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU   stNtwStChgInd;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndNtwStChgInd: PS_MEM_ALLOC fail!");
        return;
    }

    /* ��ʼ��stNtwStChgInd */
    PS_MEM_SET(&stNtwStChgInd, 0, sizeof(CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU));

    /* ���� CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU */
    stNtwStChgInd.enRatId                     = enRatId;
    stNtwStChgInd.enStatus                    = enStatus;
    stNtwStChgInd.enCause                     = enCause;
    stNtwStChgInd.enSysPri                    = pstRatInfo->enPriorityClass;
    if (CMMCA_RAT_CPST_REGISTERED == enStatus)
    {
        stNtwStChgInd.enPsType                = CMMCA_RAT_PS_TYPE_LTE;
    }
    else
    {
        stNtwStChgInd.enPsType                = CMMCA_RAT_PS_TYPE_NO_PS;
    }
    stNtwStChgInd.ulMcc                       = pstRatInfo->ulMcc;
    stNtwStChgInd.ulMnc                       = pstRatInfo->ulMnc;
    stNtwStChgInd.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* ����CMMCA_PackModeRsp�������������Ϣ */
    ulRslt = CMMCA_PackNtwStateChangeInd(&stNtwStChgInd, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}
VOS_VOID CMMCA_REG_SndMmcRejInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enSourceRat,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enApiID,
    CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8 enCause
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    CMMCA_MMC_CMD_REJ_IND_STRU          stRegInd;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_REJ_IND_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndMmcRejInd: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_MMC_CMD_REJ_IND_STRU */
    stRegInd.enSourceRat  = enSourceRat;
    stRegInd.enApiID      = enApiID;
    stRegInd.enCause      = enCause;

    /* ����CMMCA_PackModeRsp�������������Ϣ */
    ulRslt = CMMCA_PackCmdRejInd(&stRegInd, CMMCA_CMD_RAT_REJ_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_REJ_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_REG_SndPktDataCmdRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8              enCmdRsp
)
{

    CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU stPktDataCmdRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPktDataCmdRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* ���� CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU */
    stPktDataCmdRsp.enRatId  = enRatId;
    stPktDataCmdRsp.enCmdRsp = enCmdRsp;

    /* ����CMMCA_PackPktDataCmdRsp�������������Ϣ */
    ulRslt = CMMCA_PackPktDataCmdRsp(&stPktDataCmdRsp, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_PKT_SndBearDetachRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
)
{
    CMMCA_RAT_MMC_BEAR_DETACH_RSP_STRU  stBearDetachRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_SndBearDetachRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* ���� CMMCA_RAT_MMC_BEARER_DETACH_RSP_STRU */
    stBearDetachRsp.enRatId  = enRatId;
    stBearDetachRsp.ucStatus = ucStatus;

    /* ����CMMCA_PackBearDetachRsp�������������Ϣ */
    ulRslt = CMMCA_PackBearDetachRsp(&stBearDetachRsp, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8 CMMCA_REG_ConvertTafPriToCmmcaPri(
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8      enTafPriClass
)
{
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8    enCmmcaPriClass;

    if (TAF_MMA_PLMN_PRIORITY_HOME == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_HOME;
    }
    else if (TAF_MMA_PLMN_PRIORITY_PREF == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_PREF;
    }
    else if (TAF_MMA_PLMN_PRIORITY_ANY == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_ANY;
    }
    else
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;
    }

    return enCmmcaPriClass;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

