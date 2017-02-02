

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaUnSolicitedReport.h"

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_UNSILICITED_REPORT_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID TAF_MTA_RcvAtSetCurcNotify(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_CURC_SET_NOTIFY_STRU                *pstAtMtaSetCurcNotify   = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaSetCurcNotify   = (AT_MTA_CURC_SET_NOTIFY_STRU *)pstAtMtaMsg->aucContent;
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* ����CURCȫ�ֱ��� */
    pstCurcRptCtrl->enStatusRptGeneralControl = pstAtMtaSetCurcNotify->enCurcRptType;
    PS_MEM_CPY(pstCurcRptCtrl->aucRptCfg, pstAtMtaSetCurcNotify->aucRptCfg, sizeof(pstCurcRptCtrl->aucRptCfg));

    /* ��STK������Ϣ֪ͨ����CURC���� */
    TAF_MTA_SndStkCurcRptCfgInfoInd(pstAtMtaSetCurcNotify);

    return;
}


VOS_VOID TAF_MTA_RcvAtQryCurcReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU                    stQryCurcCnf;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;

    /* ��ȡCURCȫ�ֱ��� */
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* �����Ϣ���� */
    PS_MEM_SET(&stQryCurcCnf, 0x00, sizeof(stQryCurcCnf));
    stQryCurcCnf.enResult       = MTA_AT_RESULT_NO_ERROR;
    stQryCurcCnf.enCurcRptType  = (AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8)
                                    pstCurcRptCtrl->enStatusRptGeneralControl;

    PS_MEM_CPY(stQryCurcCnf.aucRptCfg, pstCurcRptCtrl->aucRptCfg, sizeof(stQryCurcCnf.aucRptCfg));

    /* ��AT���Ͳ�ѯCURC�ظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_CURC_QRY_CNF,
                     sizeof(stQryCurcCnf),
                     (VOS_UINT8*)&stQryCurcCnf);

    return;
}
VOS_VOID TAF_MTA_RcvAtSetUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU        *pstSetUnsolicitedRptReq = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU         stSetUnsolicitedRptCnf;
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex;
    VOS_UINT32                                  ulRptCmdStatus;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetUnsolicitedRptReq = (AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* ���µ����������������ϱ���ȫ�ֱ��� */
    switch (pstSetUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_SET_MODE_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_MODE;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucModeRptFlg;
            break;

        case AT_MTA_SET_SRVST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SRVST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSrvstRptFlg;
            break;

        case AT_MTA_SET_RSSI_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_RSSI;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucRssiRptFlg;
            break;

        case AT_MTA_SET_TIME_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_TIME;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucTimeRptFlg;
            break;

        case AT_MTA_SET_CTZR_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZV;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCtzrRptFlg;
            break;

        /* DSFLOWRPT��������ͨ��ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ��APS���£��˴�ɾ�� */

        case AT_MTA_SET_SIMST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SIMST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSimstRptFlg;
            break;


        case AT_MTA_SET_CREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCregRptFlg;

            TAF_SDC_SetCregType(pstSetUnsolicitedRptReq->u.ucCregRptFlg);
            break;

        case AT_MTA_SET_CGREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CGREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCgregRptFlg;

            TAF_SDC_SetCgregType(pstSetUnsolicitedRptReq->u.ucCgregRptFlg);
            break;

        case AT_MTA_SET_CEREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CEREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCeregRptFlg;

            TAF_SDC_SetCeregType(pstSetUnsolicitedRptReq->u.ucCeregRptFlg);
            break;

        default:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_BUTT;
            ulRptCmdStatus  = VOS_TRUE;
            break;
    }

    TAF_SDC_UpdateRptCmdStatus(enRptCmdIndex, ulRptCmdStatus);

    /* �����Ϣ���� */
    PS_MEM_SET(&stSetUnsolicitedRptCnf, 0x00, sizeof(stSetUnsolicitedRptCnf));
    stSetUnsolicitedRptCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* ��AT�������ûظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,
                     sizeof(stSetUnsolicitedRptCnf),
                     (VOS_UINT8*)&stSetUnsolicitedRptCnf);

    return;
}
VOS_VOID TAF_MTA_RcvAtQryUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU        *pstQryUnsolicitedRptReq = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU          *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU         stQryUnsolicitedRptCnf;

    pstAtMtaMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstQryUnsolicitedRptReq     = (AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* ��ȡ�������������ϱ���ȫ�ֱ��� */
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stQryUnsolicitedRptCnf, 0x00, sizeof(stQryUnsolicitedRptCnf));
    stQryUnsolicitedRptCnf.enReqType = pstQryUnsolicitedRptReq->enReqType;
    stQryUnsolicitedRptCnf.enResult  = MTA_AT_RESULT_NO_ERROR;

    switch (pstQryUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_QRY_TIME_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucTimeRptFlg =
                        (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_TIME);
            break;

        case AT_MTA_QRY_CTZR_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucCtzvRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CTZV);

            break;

        case AT_MTA_QRY_CSSN_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssiRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSI);

            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssuRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSU);
            break;

        case AT_MTA_QRY_CUSD_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucCusdRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CUSD);
            break;

         default:
            break;
    }

    /* ��AT���Ͳ�ѯ�ظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,
                     sizeof(stQryUnsolicitedRptCnf),
                     (VOS_UINT8*)&stQryUnsolicitedRptCnf);

    return;
}


VOS_VOID TAF_MTA_RcvTafAgentGetSysModeReq(VOS_VOID *pMsg)
{
    TAFAGENT_MTA_GET_SYSMODE_CNF_STRU          *pstGetSysModeCnf    = VOS_NULL_PTR;

    /* Modified by l00305157 for for Service_State_Optimize_PhaseI, 2014-11-29, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;

    /* ��ȡϵͳģʽ */
    /* 1x CDMA�޷���״̬��ע��״̬��ʱ�ϱ�,ȡ��ǰ��ϵͳģʽ��ϵͳ��ģʽ��3GPPʱȡAppNetworkInfo�е�ϵͳģʽ��ϵͳ��ģʽ */
    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {
        enSysMode    = TAF_SDC_SYS_MODE_CDMA_1X;
        enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
    }
    else
    {
        enSysMode    = TAF_SDC_GetAppSysMode();
        enSysSubMode = TAF_SDC_GetAppSysSubMode();
    }
    
    /* Modified by l00305157 for for Service_State_Optimize_PhaseI, 2014-11-29, end */

    pstGetSysModeCnf = (TAFAGENT_MTA_GET_SYSMODE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAFAGENT_MTA_GET_SYSMODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstGetSysModeCnf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:alloc msg failed.");
        return;
    }

    /* ��Ϣͷ */
    pstGetSysModeCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulSenderPid                   = UEPS_PID_MTA;
    pstGetSysModeCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;

    /* ��Ϣ���� */
    pstGetSysModeCnf->enMsgId                 = ID_TAFAGENT_MTA_GET_SYSMODE_CNF;
    pstGetSysModeCnf->ulRet                   = VOS_OK;
    pstGetSysModeCnf->stSysMode.enSysSubMode  = enSysSubMode;
    pstGetSysModeCnf->stSysMode.enRatType     = enSysMode;

    /* ��TAFAGENT���Ͳ�ѯ�ظ� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstGetSysModeCnf))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:send msg failed.");

        return;
    }

    return;
}
VOS_VOID TAF_MTA_SndStkCurcRptCfgInfoInd(AT_MTA_CURC_SET_NOTIFY_STRU *pMsg)
{
    TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU          *pstStkCurcRptInfo  = VOS_NULL_PTR;

    /* �����ڴ� */
    pstStkCurcRptInfo = (TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ڴ�����쳣���� */
    if (VOS_NULL_PTR == pstStkCurcRptInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd:alloc msg failed.");
        return;
    }

    /* ��д����Ϣ���� */
    pstStkCurcRptInfo->ulSenderPid      = UEPS_PID_MTA;
    pstStkCurcRptInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulReceiverPid    = MAPS_STK_PID;
    pstStkCurcRptInfo->ulMsgId          = TAF_STK_CURC_RPT_CFG_INFO_IND;
    PS_MEM_CPY(pstStkCurcRptInfo->aucCurcRptCfg,
               pMsg->aucRptCfg,
               sizeof(pstStkCurcRptInfo->aucCurcRptCfg));

    /* ������Ϣ�쳣���� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstStkCurcRptInfo))
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd: PS_SEND_MSG ERROR");
        return;
    }

    return;
}

#ifdef DMT

VOS_UINT32 DMT_GetSysMode(TAF_AGENT_SYS_MODE_STRU *pstSysMode)
{
    TAF_SDC_SYS_INFO_STRU                 *pst3gppSysInfo     = VOS_NULL_PTR;

    /* ��ȡϵͳģʽ */
    pst3gppSysInfo   = TAF_SDC_GetSysInfo();

    pstSysMode->enSysSubMode  = pst3gppSysInfo->enSysSubMode;
    pstSysMode->enRatType     = pst3gppSysInfo->enSysMode;

    return VOS_OK;
}
#endif

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

