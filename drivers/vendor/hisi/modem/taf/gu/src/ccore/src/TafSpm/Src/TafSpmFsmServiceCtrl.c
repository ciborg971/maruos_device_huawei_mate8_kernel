

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmServiceCtrl.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "UsimPsInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafLog.h"
#include "TafSpmMntn.h"
#include "MnErrorCode.h"
#include "TafMmiEncode.h"
#include "TafSdcCtx.h"
#include "Taf_Tafm_Remote.h"
#include "TafSpmSndUsim.h"
#include "Taf_Ssa_EncodeDef.h"
#include "TafStdlib.h"
#include "mnmsgcbencdec.h"

#include "NasUsimmApi.h"

#include "NasStkInterface.h"

#include "TafSpmComFunc.h"
#include "MnCallApi.h"
#include "NasCcIe.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_SERVICE_CTRL_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/* SSҵ��Call Control�����Ϊ������Ҫ�޸ģ����ֲ������޸ĺ��� */
TAF_SPM_SS_CALL_CTRL_MODIFY_STRU        g_astTafSpmSsCallCtrlModifyTbl[] =
{
    {TAF_MMI_ACTIVATE_SS,       {0,0,0}, TAF_SPM_Modify2SsActivateMsg     },
    {TAF_MMI_DEACTIVATE_SS,     {0,0,0}, TAF_SPM_Modify2SsDeactivateMsg   },
    {TAF_MMI_INTERROGATE_SS,    {0,0,0}, TAF_SPM_Modify2SsInterrogateMsg  },
    {TAF_MMI_REGISTER_SS,       {0,0,0}, TAF_SPM_Modify2SsRegisterMsg     },
    {TAF_MMI_ERASE_SS,          {0,0,0}, TAF_SPM_Modify2SsEraseMsg        },
    {TAF_MMI_REGISTER_PASSWD,   {0,0,0}, TAF_SPM_Modify2SsRegPwdMsg       },
    {TAF_MMI_DEACTIVATE_CCBS,   {0,0,0}, TAF_SPM_Modify2DeactivateCcbsMsg }
};


/*lint -save -e958 */

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/


VOS_VOID TAF_SPM_StartFdnCheck_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    /* ��USIMģ�鷢�ͼ������ */
    ulRet = TAF_SPM_SendPbFdnCheckReq_ServiceCtrl(usClientId, pstMsg);

    if (VOS_FALSE == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_StartFdnCheck:TAF_SPM_SendPbFdnCheckReq_ServiceCtrl fail!");

        /* ����ʧ�ܵ�״̬���˳������Ϣ��TAF */
        TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL,
                                      TAF_CS_CAUSE_FDN_CHECK_FAILURE,
                                      usClientId,
                                      TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

        /* �˳�״̬�� */
        TAF_SPM_FSM_QuitCurrEntityFsm();

        return;
    }

    /* Ǩ��״̬���ȴ�USIM��FDN���ظ� */
    TAF_SPM_SetCurrEntityFsmState(TAF_SPM_SERVICE_CTRL_STA_WAIT_PB_FDN_CHECK_CNF);

    /* ������ʱ�� */
    TAF_SPM_StartTimer(TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF, TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF_LEN, usClientId);
}
VOS_VOID TAF_SPM_StartCallControlCheck_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    /* ��USIMģ�鷢�ͼ������ */
    ulRet = TAF_SPM_SendUsimEnvelopeReq_ServiceCtrl(usClientId, pstMsg);

    if (VOS_FALSE == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_StartCallControlCheck:TAF_SPM_SndUsimEnvelopeReq fail!");

        /* ����ʧ�ܵ�״̬���˳������Ϣ��TAF */
        TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL,
                                      TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER,
                                      usClientId,
                                      TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

        /* �˳�״̬�� */
        TAF_SPM_FSM_QuitCurrEntityFsm();

        return;
    }

    /* Ǩ��״̬���ȴ�USIM��call control���ظ� */
    TAF_SPM_SetCurrEntityFsmState(TAF_SPM_SERVICE_CTRL_STA_WAIT_USIM_CALL_CTRL_CNF);

    /* ������ʱ�� */
    TAF_SPM_StartTimer(TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF, TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF_LEN, usClientId);
}
VOS_UINT32 TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();


    /* ������ϢΪTAF_MSG_RLEASE_MSG��TAF_MSG_PROCESS_USS_MSG��Ϣ����USSD string
     * ����Ҫ����FDN��CALL control���
     */

    /* �Ƿ���ҪFDN��� */
    if (VOS_TRUE == TAF_SPM_IsNeedCheckFdn())
    {
        /* start FDN check procedure */
        TAF_SPM_StartFdnCheck_ServiceCtrl(usClientId, pstMsg);
        return VOS_TRUE;
    }

    /* �Ƿ���Ҫ����call contrl ��� */
    if (VOS_TRUE == TAF_SPM_IsNeedCallControl())
    {
        /* start call control check procedure */
        TAF_SPM_StartCallControlCheck_ServiceCtrl(usClientId, pstMsg);
        return VOS_TRUE;
    }

    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();

    /* �Ƿ���Ҫ����call contrl ��� */
    if (VOS_TRUE == TAF_SPM_IsNeedCallControl())
    {
        /* start call control procedure */
        TAF_SPM_StartCallControlCheck_ServiceCtrl(usClientId, pstMsg);

        return VOS_TRUE;
    }

    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_RcvAtCallReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;

    pstAppMsg                 = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();

    /* MIEC��AIECҲ���ڽ�����������Ҫ����FDN��CALL CONTROL��飬����test
     * eCall��reconfiguration ecallҲ����Ҫ��FDN��飬����������һ���ͣ�
     * ����������
     */
    if ((MN_CALL_TYPE_EMERGENCY != pstAppMsg->unParm.stOrig.enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     && (MN_CALL_TYPE_MIEC      != pstAppMsg->unParm.stOrig.enCallType)
     && (MN_CALL_TYPE_AIEC      != pstAppMsg->unParm.stOrig.enCallType)
#endif
       )
    {
        /* �Ƿ���ҪFDN��� */
        if (VOS_TRUE == TAF_SPM_IsNeedCheckFdn())
        {
            /* start FDN check procedure */
            TAF_SPM_StartFdnCheck_ServiceCtrl(usClientId, pstMsg);

            return VOS_TRUE;
        }

        /* �Ƿ���Ҫ����call contrl ��� */
        if (VOS_TRUE == TAF_SPM_IsNeedCallControl())
        {
            /* start call control check procedure */
            TAF_SPM_StartCallControlCheck_ServiceCtrl(usClientId, pstMsg);

            return VOS_TRUE;
        }
    }

    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}



VOS_UINT32 TAF_SPM_RcvStkCallReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();

    if (MN_CALL_TYPE_EMERGENCY != pstOrigParam->enCallType)
    {
        if (VOS_TRUE == TAF_SPM_IsNeedCallControl())
        {
            /* start call control check procedure */
            TAF_SPM_StartCallControlCheck_ServiceCtrl(usClientId, pstMsg);

            return VOS_TRUE;
        }
    }


    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_RcvAtSmsReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();


    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_RcvStkSmsReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;

    /* ����������Ϣ */
    TAF_SPM_SaveCurrEntityFsmEntryMsg(ulEventType, pstMsg);

    usClientId = TAF_SPM_GetCurrEntityFsmClientId();


    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                  TAF_CS_CAUSE_SUCCESS,
                                  usClientId,
                                  TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_RcvPbFdnCheckCnf_ServiceCtrl_WaitPbFdnCheckCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PB_FDN_CHECK_CNF_STRU              *pstFdnCheckCnf  = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
#endif
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usClientId;

    pstFdnCheckCnf      = (PB_FDN_CHECK_CNF_STRU*)pstMsg;
    usClientId          = TAF_SPM_GetCurrEntityFsmClientId();
    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
#if (FEATURE_ON == FEATURE_IMS)
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif
    ulRslt              = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* Econf ���� */
    if (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        pstEconfInfoAddr->ucRcvNum++;

        if (pstEconfInfoAddr->ucRcvNum == pstEconfInfoAddr->ucSendSuccNum)
        {
            TAF_SPM_StopTimer(TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF, usClientId);
        }

        /* ulSendPara��16λΪ֮ǰ������ʱ�����index */
        ulIndex = TAF_SPM_ECONF_GET_INDEX_FROM_PARA(pstFdnCheckCnf->ulSendPara);

        if (PB_FDN_CHECK_SUCC != pstFdnCheckCnf->enResult)
        {
            TAF_SPM_RecordEconfCheckRslt(ulIndex, TAF_CS_CAUSE_FDN_CHECK_FAILURE);
        }
        else
        {
            TAF_SPM_RecordEconfCheckRslt(ulIndex, TAF_CS_CAUSE_SUCCESS);
        }

        /* ȫ��������FDN�ļ���� */
        if (pstEconfInfoAddr->ucRcvNum == pstEconfInfoAddr->ucSendSuccNum)
        {
            ulRslt = TAF_SPM_ProcEconfCheckResult();
        }
        else
        {
            return VOS_TRUE;
        }
    }
    else
#endif
    {
        TAF_SPM_StopTimer(TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF, usClientId);

        if (PB_FDN_CHECK_SUCC != pstFdnCheckCnf->enResult)
        {
            ulRslt    = VOS_FALSE;
        }
        else
        {
            ulRslt    = VOS_TRUE;
        }
    }

    return TAF_SPM_ProcFdnCheckResult(ulRslt, usClientId, pstEntryMsg);
}
VOS_UINT32 TAF_SPM_RcvTiWaitPbFdnCheckCnfExpired_ServiceCtrl_WaitPbFdnCheckCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulIndex;
#endif

    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvTiWaitPbFdnCheckCnfExpired_ServiceCtrl_WaitPbFdnCheckCnf:timer expired!");

    usClientId      = TAF_SPM_GetCurrEntityFsmClientId();
    pstEntryMsg     = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
#if (FEATURE_ON == FEATURE_IMS)
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif

#if (FEATURE_ON == FEATURE_IMS)
    if (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��¼���,������û�лظ��Ľ����ΪTAF_CS_CAUSE_FDN_CHECK_FAILURE */
        for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
        {
            if (VOS_FALSE == pstEconfInfoAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag)
            {
                TAF_SPM_RecordEconfCheckRslt(ulIndex, TAF_CS_CAUSE_FDN_CHECK_FAILURE);
            }
        }

        ulRslt = TAF_SPM_ProcEconfCheckResult();

        /*  ���ʧ�ܣ������ԭ�����̣��˳�״̬�� */
        return TAF_SPM_ProcFdnCheckResult(ulRslt, usClientId, pstEntryMsg);
    }
#endif

    /* Ŀǰ��֧�ֲ���ҵ��,�������������Ϣ��ҵ������ת����ʧ��ԭ��ֵ */

    /* ����ʧ�ܵ�״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL, TAF_CS_CAUSE_FDN_CHECK_FAILURE, usClientId, pstEntryMsg);

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_RcvUsimEnvelopeCnf_ServiceCtrl_WaitUsimCallCtrlCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU                           *pstEnvelopeCnf  = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enFsmRslt;
    VOS_UINT16                                              usClientId;
    VOS_UINT32                                              ulCause;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg     = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8                         enSrvReqType;

    pstEntryMsg  = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    enSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    pstEnvelopeCnf  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
    usClientId      = TAF_SPM_GetCurrEntityFsmClientId();

    enFsmRslt           = TAF_SPM_SERVICE_CTRL_SUCC;
    ulCause             = TAF_CS_CAUSE_SUCCESS;

    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��ֹͣ������ʱ�����Ƶ��������������� */
        TAF_SPM_StopTimer(TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF, (VOS_UINT16)pstEnvelopeCnf->stCmdResult.ulSendPara);
    }

    /* ���ݲ�ͬ��ҵ��������в�ͬ�Ĵ��� */
    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:

            TAF_SPM_ProcCallEnvelopeCnf(pstEnvelopeCnf, &enFsmRslt, &ulCause);

            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:

            /* ��������չ */
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:

            /* ����USIM��envelop�Ļظ���Ϣ */
            TAF_SPM_ProcSsEnvelopeCnf(pstEnvelopeCnf, &enFsmRslt, &ulCause);

            break;

        default:

            break;
    }


#if (FEATURE_ON == FEATURE_IMS)
    if (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        return VOS_TRUE;
    }
#endif

    /* ����״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(enFsmRslt, ulCause, usClientId, TAF_SPM_GetCurrEntityFsmEntryMsgAddr());

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_RcvTiWaitUsimCallCtrlCnfExpired_ServiceCtrl_WaitUsimCallCtrlCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulIndex;
#endif

    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvTiWaitPbFdnCheckCnfExpired_ServiceCtrl_WaitPbFdnCheckCnf:timer expired!");

    usClientId      = TAF_SPM_GetCurrEntityFsmClientId();
    pstEntryMsg     = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();

#if (FEATURE_ON == FEATURE_IMS)
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif

#if (FEATURE_ON == FEATURE_IMS)
    if (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��û�з��صĽ����¼Ϊʧ�� */
        for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
        {
            if (VOS_FALSE == pstEconfInfoAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag)
            {
                TAF_SPM_RecordEconfCheckRslt(ulIndex, TAF_CS_CAUSE_CALL_CTRL_TIMEOUT);
            }
        }

        /* ����� */
        ulRslt = TAF_SPM_ProcEconfCheckResult();

        return TAF_SPM_ProcEconfCallCtrlCheckResult(ulRslt, pstEconfInfoAddr->usClientId, pstEntryMsg);
    }
#endif

    /* Ŀǰ��֧�ֲ���ҵ��,�������������Ϣ��ҵ������ת����ʧ��ԭ��ֵ */

    /* ����ʧ�ܵ�״̬���˳������Ϣ��TAF */
    TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL, TAF_CS_CAUSE_CALL_CTRL_TIMEOUT, usClientId, pstEntryMsg);

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_SendPbFdnCheckReq_ServiceCtrl(
    VOS_UINT16                         usClientId,
    struct MsgCB                      *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;
    VOS_UINT32                          ulResult;

    ulResult    = VOS_TRUE;

    pstEntryMsg  = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    enSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:

            ulResult = TAF_SPM_SendPbCallFdnCheckReq(usClientId, pstMsg);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:

            if (VOS_TRUE == TAF_SPM_IsUssdServiceType(pstEntryMsg->ulEventType))
            {
                ulResult = TAF_SPM_SendPbUssdFdnCheckReq(usClientId, pstMsg);
            }
            else
            {
                ulResult = TAF_SPM_SendPbSsFdnCheckReq(usClientId, pstMsg);
            }

            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:

            /* ��������չ */

            break;

        default:

            break;
    }

    return ulResult;
}
VOS_UINT32 TAF_SPM_SendUsimEnvelopeReq_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;
    VOS_UINT32                          ulResult;

    ulResult    = VOS_TRUE;

    pstEntryMsg  = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    enSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            ulResult = TAF_SPM_SendUsimCallEnvelopeReq_Call(usClientId, pstMsg);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:

            if (VOS_TRUE == TAF_SPM_IsUssdServiceType(pstEntryMsg->ulEventType))
            {
                ulResult = TAF_SPM_SendUsimUssdEnvelopeReq(usClientId, pstMsg);
            }
            else
            {
                ulResult = TAF_SPM_SendUsimSsEnvelopeReq(usClientId, pstMsg);
            }

            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:

            /* ��������չ */
            break;

        default:

            break;
    }

    return ulResult;
}
VOS_VOID TAF_SPM_ProcSsEnvelopeCnf(
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU                           *pstEnvelopeCnf,
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
)
{
    SI_STK_ENVELOPE_RSP_STRU            stCallCtrlRsp;
    VOS_UINT32                          ulUssdService;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;

    pstEntryMsg  = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();

    PS_MEM_SET(&stCallCtrlRsp, 0, sizeof(stCallCtrlRsp));

    ulUssdService = TAF_SPM_IsUssdServiceType(pstEntryMsg->ulEventType);

    if (VOS_TRUE == ulUssdService)
    {
        stCallCtrlRsp.uResp.CallCtrlRsp.SpecialData.ucTag = SI_CC_USSD_TAG;
    }
    else
    {
        stCallCtrlRsp.uResp.CallCtrlRsp.SpecialData.ucTag = SI_CC_SS_TAG;
    }

    /* ����OP���Ƿ���Ч��SpecialData.ucTagʼ������Ч�� */
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    stCallCtrlRsp.EnvelopeType                          = pstEnvelopeCnf->enEnvelopeType;
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */

    /* ֻ��Я��������������ʾ��ָʾ�ܾ�����Ϊ���ʧ��,�˴���ΪUSIM����
       �ݴ��֧,�����ΪOK��datalenΪ0Ҳ��Ϊ�ɹ� */
    if (VOS_OK != (pstEnvelopeCnf->stCmdResult.ulResult))
    {
        *pulCause = TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        stCallCtrlRsp.uResp.CallCtrlRsp.SpecialData.ucTag = SI_CC_ADDRESS_TAG;
        stCallCtrlRsp.Result                              = SI_STK_CTRL_NOT_ALLOW;

        NAS_STKAPI_CCResultInd(&stCallCtrlRsp);

        NAS_STKAPI_EnvelopeRspDataFree(&stCallCtrlRsp);

        return;
    }

    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    if (0 == pstEnvelopeCnf->stCnfData.ulRspDataLen)
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    {
        *pulCause  = TAF_CS_CAUSE_SUCCESS;
        *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;

        stCallCtrlRsp.Result    = SI_STK_CTRL_ALLOW_NOMODIFY;

        NAS_STKAPI_CCResultInd(&stCallCtrlRsp);

        return;
    }

    /* ��Ϣ���� */
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    (VOS_VOID)NAS_STKAPI_EnvelopeRsp_Decode(pstEnvelopeCnf->enEnvelopeType, pstEnvelopeCnf->stCnfData.ulRspDataLen, pstEnvelopeCnf->stCnfData.aucRspData, &stCallCtrlRsp);
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */

    if (SI_STK_CTRL_ALLOW_MODIFY == stCallCtrlRsp.Result)
    {
        TAF_SPM_ProcCallCtrlRsltAllowModify_SS(&stCallCtrlRsp, penRslt, pulCause);

        /* ����޸ĺ�Ĳ���������������Ҫ����stCallCtrlRsp�Ľ�� */
        if (TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY == *pulCause)
        {
            stCallCtrlRsp.Result = SI_STK_CTRL_NOT_ALLOW;
        }
    }
    else if (SI_STK_CTRL_NOT_ALLOW == stCallCtrlRsp.Result)
    {
        *pulCause = TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
    }
    else if (SI_STK_CTRL_ALLOW_NOMODIFY == stCallCtrlRsp.Result)
    {
        *pulCause  = TAF_CS_CAUSE_SUCCESS;
        *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;
    }
    else
    {
        /* SI_STK_CTRL_BUTT�������Ϊʧ�� */
        *pulCause  = TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER;
        *penRslt   = TAF_SPM_SERVICE_CTRL_FAIL;
    }

    NAS_STKAPI_CCResultInd(&stCallCtrlRsp);

    NAS_STKAPI_EnvelopeRspDataFree(&stCallCtrlRsp);
}
VOS_UINT32 TAF_SPM_IsCallCtrlModifyBeyondCapability_SS(
    SI_STK_ENVELOPE_RSP_STRU           *pstCallCtrlRsp
)
{
    SI_CC_SPECI_TAG_ENUM_UINT8          ucCurrServiceTag;

    VOS_UINT32                          ulUssdService;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;

    pstEntryMsg  = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();

    ulUssdService = TAF_SPM_IsUssdServiceType(pstEntryMsg->ulEventType);

    if (VOS_TRUE == ulUssdService)
    {
        ucCurrServiceTag = SI_CC_USSD_TAG;
    }
    else
    {
        ucCurrServiceTag = SI_CC_SS_TAG;
    }

    /*
    AT�����USSDҵ��Ҫ�󲻵�����ظ��������ظ���AT�˳�����״̬
    ��ˣ�USSDҵ�������޸ĺ�ֻ����USSDҵ��
    AT�����SSҵ��Ҫ��ȴ�����ظ���ظ�AT������
    ��ˣ�SSҵ�������޸ĺ�ֻ����SSҵ��
    ����޸�ǰ���޸ĺ�ҵ��Tag����ͬ��Ϊ��������
    */

    if (ucCurrServiceTag != pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucTag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_SPM_ProcSsCallCtrlRsltAllowModify(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
)
{
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam   = VOS_NULL_PTR;
    TAF_CHAR                           *pcOutRestMmiStr = VOS_NULL_PTR;
    TAF_CHAR                           *pcInMmiStr      = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSsStrLength;
    VOS_UINT8                           ucNumType;
    VOS_UINT32                          ulCurrMsgSendPid;

    pstMmiOpParam = (MN_MMI_OPERATION_PARAM_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MMI_OPERATION_PARAM_STRU));

    if (VOS_NULL_PTR == pstMmiOpParam)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: Fail to alloc memory.");
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    pcInMmiStr = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SPM_SSC_MAX_LEN);

    if (VOS_NULL_PTR == pcInMmiStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: Fail to alloc memory.");
        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
        return;
    }

    PS_MEM_SET(pcInMmiStr, 0, TAF_SPM_SSC_MAX_LEN);

    /*
    SSҵ��ĵ�һ���ֽ��Ǻ������ͣ��˴���¼�������������Ϊע���������µ��������
    �ο�Э�� 11.11: 10.5.1  EFADN (Abbreviated dialling numbers)
    TON and NPI
    Contents:
        Type of number (TON) and numbering plan identification (NPI).
    Coding:
        according to TS 04.08 [15]. If the Dialling Number/SSC String does not contain a dialling number,
        e.g. a control string deactivating a service, the TON/NPI byte shall be set to 'FF' by the ME (see note 2).
    NOTE 2: If a dialling number is absent, no TON/NPI byte is transmitted over the radio interface (see TS 04.08 [15]).
        Accordingly, the ME should not interpret the value 'FF' and not send it over the radio interface.
    */
    ucNumType     = pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue[0];
    ulSsStrLength = (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen - TAF_SPM_SSC_OFFSET);
    if (ulSsStrLength > TAF_SPM_GET_BCD_NUBMER_LENGTH(TAF_SPM_SSC_MAX_LEN))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: SS STRING length is overflow.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);
        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
        return;
    }

    ulRet = TAF_STD_ConvertBcdNumberToAscii((pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue + TAF_SPM_SSC_OFFSET),
                                  (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen - TAF_SPM_SSC_OFFSET),
                                  pcInMmiStr);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: Fail to TAF_STD_ConvertBcdNumberToAscii.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);
        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
        return;
    }

    pcOutRestMmiStr = (VOS_CHAR *)(pcInMmiStr + VOS_StrLen(pcInMmiStr));

    ulRet = MN_MmiStringParse((VOS_CHAR *)pcInMmiStr,
                              TAF_SDC_GetCsCallExistFlg(),
                              pstMmiOpParam,
                              &pcOutRestMmiStr);

    if ((MN_ERR_NO_ERROR != ulRet)
     || (TAF_MMI_PROCESS_USSD_REQ == pstMmiOpParam->MmiOperationType))
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: Fail decode SSC.");

        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    /* UE��֧��SSҵ��תUSSDҵ�� */
    if (TAF_MMI_PROCESS_USSD_REQ == pstMmiOpParam->MmiOperationType)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSsCallCtrlRsltAllowModify: SS => USSD not support.");

        *pulCause = TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    /* ������ת����ע�����������ת��ע����������к������� */
    if (TAF_MMI_REGISTER_SS == pstMmiOpParam->MmiOperationType)
    {
        pstMmiOpParam->RegisterSsReq.NumType = ucNumType;
    }

    /* ���벢�����Ϣ */
    ulCurrMsgSendPid = TAF_SPM_GetCurrEntityFsmEntryMsgSndPid();
    if (( MAPS_STK_PID != ulCurrMsgSendPid)
      && (WUEPS_PID_AT != ulCurrMsgSendPid))
    {
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
        PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);

        return;
    }
    ulRet = TAF_SPM_ModifySsEntryMsgByCallCtrlMsg(ulCurrMsgSendPid, pstMmiOpParam);
    if (VOS_TRUE != ulRet)
    {
        *pulCause = TAF_CS_CAUSE_UNKNOWN;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
    }
    else
    {
        *pulCause  = TAF_CS_CAUSE_SUCCESS;
        *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstMmiOpParam);
    PS_MEM_FREE(WUEPS_PID_TAF, pcInMmiStr);

    return;
}
VOS_VOID TAF_SPM_ProcUssdCallCtrlRsltAllowModify(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
)
{
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDcs;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_APP_SS_USSD_REQ_STRU            *pstUssdInfo         = VOS_NULL_PTR;

    if (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen > TAF_SS_MAX_USS_CHAR)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcUssdCallCtrlRsltAllowModify: Call Control result para error.");
        *pulCause              = TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER;
        *penRslt               = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    pstEntryMsg = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();

    /* MMI���������û��DCS��Ϣ������������ҪΪUSSD��Ϣ������ֵ */
    ucDcs = *(pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue);

    /* �޸�DCSֵ */
    pstUssdInfo = (MN_APP_SS_USSD_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    pstUssdInfo->stTafSsUssdReq.DatacodingScheme = ucDcs;


    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));
    ulRet = MN_MSG_DecodeCbsDcs(ucDcs,
                                pstUssdInfo->stTafSsUssdReq.UssdStr.aucUssdStr,
                                pstUssdInfo->stTafSsUssdReq.UssdStr.usCnt,
                                &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcUssdCallCtrlRsltAllowModify:WARNING: Decode Failure");
        *pulCause              = TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER;
        *penRslt               = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    PS_MEM_SET(&(pstUssdInfo->stTafSsUssdReq.UssdStr), 0x0, sizeof(TAF_SS_USSD_STRING_STRU));

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    {
        pstUssdInfo->stTafSsUssdReq.UssdStr.usCnt
        = TAF_STD_HexAlpha2AsciiString((pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue + TAF_SPM_SSC_OFFSET),
                                           (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen - TAF_SPM_SSC_OFFSET),
                                            pstUssdInfo->stTafSsUssdReq.UssdStr.aucUssdStr);
    }
    else
    {

        pstUssdInfo->stTafSsUssdReq.UssdStr.usCnt = pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen - TAF_SPM_SSC_OFFSET;
        PS_MEM_CPY(pstUssdInfo->stTafSsUssdReq.UssdStr.aucUssdStr,
                    (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue + TAF_SPM_SSC_OFFSET),
                    pstUssdInfo->stTafSsUssdReq.UssdStr.usCnt);
    }

    *pulCause  = TAF_CS_CAUSE_SUCCESS;
    *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;

    return;
}



VOS_VOID TAF_SPM_ProcCallCtrlRsltAllowModify_SS(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
)
{
    VOS_UINT32                          ulRet;

    /* UE��֧�ֲ���ҵ���޸ĵ�����ҵ�����͵�CALL CONTROLҵ�� */
    ulRet = TAF_SPM_IsCallCtrlModifyBeyondCapability_SS(pstCallCtrlRsp);
    if (VOS_TRUE == ulRet)
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcCallCtrlRsltAllowModify_SS: UE not support.");
        *pulCause              = TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY;
        *penRslt               = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }


    if ((VOS_FALSE == pstCallCtrlRsp->uResp.CallCtrlRsp.OP_SepcialData)
     || (VOS_NULL_PTR == pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.pValue)
     || (pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucLen < TAF_SPM_SSC_OFFSET))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcCallCtrlRsltAllowModify_SS: Call Control result para error.");
        *pulCause              = TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER;
        *penRslt               = TAF_SPM_SERVICE_CTRL_FAIL;

        return;
    }

    if (SI_CC_USSD_TAG == pstCallCtrlRsp->uResp.CallCtrlRsp.SpecialData.ucTag)
    {
        TAF_SPM_ProcUssdCallCtrlRsltAllowModify(pstCallCtrlRsp, penRslt, pulCause);
    }
    else
    {
        TAF_SPM_ProcSsCallCtrlRsltAllowModify(pstCallCtrlRsp, penRslt, pulCause);
    }

    return;
}


/*lint -e593  -e830*/


VOS_UINT32 TAF_SPM_ModifySsEntryMsgByCallCtrlMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam
)
{
    TAF_SPM_CALL_CTRL_MODIFY_FUNC_PTR                       pCallCtrlModFunc    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg         = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulModifyTblSize;
    VOS_UINT32                                              i;

    ulRet               = VOS_FALSE;
    ulModifyTblSize     = sizeof(g_astTafSpmSsCallCtrlModifyTbl) / sizeof(g_astTafSpmSsCallCtrlModifyTbl[0]);

    for (i = 0; i < ulModifyTblSize ; i++)
    {
        if (pstMmiOpParam->MmiOperationType == g_astTafSpmSsCallCtrlModifyTbl[i].ucMmiOperationType)
        {
            pCallCtrlModFunc = g_astTafSpmSsCallCtrlModifyTbl[i].pModifyFunc;
            break;
        }
    }

    if (VOS_NULL_PTR != pCallCtrlModFunc)
    {
        pstEntryMsg = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
        ulRet = pCallCtrlModFunc(ulSenderPid, pstMmiOpParam, pstEntryMsg->aucEntryMsgBuffer);

        /* ���ݷ��ͷ�PID��MMI��������޸������Ϣ��eventType */
        pstEntryMsg->ulEventType = TAF_BuildEventType(ulSenderPid, TAF_SPM_GetCurrEntityFsmEntryMsgName());
    }

    return ulRet;
}

/*lint +e593  +e830*/


VOS_UINT32 TAF_SPM_Modify2SsActivateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_ACTIVATE_REQ_STRU        *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_ACTIVATESS_REQ_STRU         *pstActivateSsReq      = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        pstAppMsg->usMsgName  = TAF_MSG_ACTIVATESS_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength   = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_ACTIVATESS_REQ_STRU)
                                 - sizeof(pstAppMsg->aucContent)  - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstActivateSsReq      = (TAF_SS_ACTIVATESS_REQ_STRU *)pstAppMsg->aucContent;
        PS_MEM_CPY(pstActivateSsReq,
                   &(pstMmiOpParam->ActivateSsReq),
                   sizeof(TAF_SS_ACTIVATESS_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_ACTIVATE_REQ_STRU *)pMsg;

        pstStkMsg->ulMsgId    = STK_SS_ACTIVATESS_REQ;
        pstStkMsg->ulLength   = sizeof(MN_APP_SS_ACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsActivateSsReq),
                   &(pstMmiOpParam->ActivateSsReq),
                   sizeof(TAF_SS_ACTIVATESS_REQ_STRU));
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_SPM_Modify2SsDeactivateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_DEACTIVATE_REQ_STRU      *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_DEACTIVATESS_REQ_STRU       *pstDeactivateSsReq    = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        pstAppMsg->usMsgName  = TAF_MSG_DEACTIVATESS_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength   = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_DEACTIVATESS_REQ_STRU)
                                 - sizeof(pstAppMsg->aucContent)  - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstDeactivateSsReq    = (TAF_SS_DEACTIVATESS_REQ_STRU *)pstAppMsg->aucContent;
        PS_MEM_CPY(pstDeactivateSsReq,
                   &(pstMmiOpParam->DeactivateSsReq),
                   sizeof(TAF_SS_DEACTIVATESS_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_DEACTIVATE_REQ_STRU *)pMsg;

        pstStkMsg->ulMsgId    = STK_SS_DEACTIVATESS_REQ;
        pstStkMsg->ulLength   = sizeof(MN_APP_SS_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsDeActivateSsReq),
                   &(pstMmiOpParam->DeactivateSsReq),
                   sizeof(TAF_SS_DEACTIVATESS_REQ_STRU));
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_SPM_Modify2SsInterrogateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_INTERROGATE_REQ_STRU     *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_INTERROGATESS_REQ_STRU      *pstInterrogateSsReq   = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        pstAppMsg->usMsgName  = TAF_MSG_INTERROGATESS_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength   = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_INTERROGATESS_REQ_STRU)
                                 - sizeof(pstAppMsg->aucContent)  - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstInterrogateSsReq   = (TAF_SS_INTERROGATESS_REQ_STRU *)pstAppMsg->aucContent;
        PS_MEM_CPY(pstInterrogateSsReq,
                   &(pstMmiOpParam->InterrogateSsReq),
                   sizeof(TAF_SS_INTERROGATESS_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_INTERROGATE_REQ_STRU *)pMsg;

        pstStkMsg->ulMsgId    = STK_SS_INTERROGATESS_REQ;
        pstStkMsg->ulLength   = sizeof(MN_APP_SS_INTERROGATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsInterrogateSsReq),
                   &(pstMmiOpParam->InterrogateSsReq),
                   sizeof(TAF_SS_INTERROGATESS_REQ_STRU));
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_SPM_Modify2SsRegisterMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_REGISTER_REQ_STRU        *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterSsReq      = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        pstAppMsg->usMsgName  = TAF_MSG_REGISTERSS_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength   = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_REGISTERSS_REQ_STRU) - sizeof(pstAppMsg->aucContent)  - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/

        pstRegisterSsReq      = (TAF_SS_REGISTERSS_REQ_STRU *)pstAppMsg->aucContent;
        PS_MEM_CPY(pstRegisterSsReq,
                   &(pstMmiOpParam->RegisterSsReq),
                   sizeof(TAF_SS_REGISTERSS_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_REGISTER_REQ_STRU *)pMsg;

        pstStkMsg->ulMsgId    = STK_SS_REGISTERSS_REQ;
        pstStkMsg->ulLength   = sizeof(MN_APP_SS_REGISTER_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsRegisterSsReq),
                   &(pstMmiOpParam->RegisterSsReq),
                   sizeof(TAF_SS_REGISTERSS_REQ_STRU));
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_SPM_Modify2SsEraseMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_ERASE_REQ_STRU           *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_ERASESS_REQ_STRU            *pstSsErasessReq       = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        pstAppMsg->usMsgName  = TAF_MSG_ERASESS_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength   = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_ERASESS_REQ_STRU)
                                 - sizeof(pstAppMsg->aucContent) - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstSsErasessReq       = (TAF_SS_ERASESS_REQ_STRU *)pstAppMsg->aucContent;
        PS_MEM_CPY(pstSsErasessReq,
                   &(pstMmiOpParam->EraseSsReq),
                   sizeof(TAF_SS_ERASESS_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_ERASE_REQ_STRU *)pMsg;

        pstStkMsg->ulMsgId    = STK_SS_ERASESS_REQ;
        pstStkMsg->ulLength   = sizeof(MN_APP_SS_ERASE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsEraseSsReq),
                   &(pstMmiOpParam->EraseSsReq),
                   sizeof(TAF_SS_ERASESS_REQ_STRU));
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_Modify2SsRegPwdMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    MN_APP_SS_REGPWD_REQ_STRU          *pstStkMsg             = VOS_NULL_PTR;
    TAF_SS_REGPWD_REQ_STRU             *pstSsRegPwdReq        = VOS_NULL_PTR;

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    if (WUEPS_PID_AT == ulSenderPid)
    {
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

        /* ��Ҫ�޸���Ϣ�������Ⱥ;�����Ϣ���� */
        pstAppMsg->usMsgName = TAF_MSG_REGPWD_MSG;
        /*lint -e961*/
        pstAppMsg->ulLength  = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_REGPWD_REQ_STRU)
                                - sizeof(pstAppMsg->aucContent) - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstSsRegPwdReq       = (TAF_SS_REGPWD_REQ_STRU *)pstAppMsg->aucContent;

        PS_MEM_CPY(pstSsRegPwdReq,
                   &(pstMmiOpParam->RegPwdReq),
                   sizeof(TAF_SS_REGPWD_REQ_STRU));
    }
    else
    {
        pstStkMsg = (MN_APP_SS_REGPWD_REQ_STRU *)pMsg;

        /* ��Ҫ�޸���Ϣ�������Ⱥ;�����Ϣ���� */
        pstStkMsg->ulMsgId   = STK_SS_REGPWD_REQ;
        pstStkMsg->ulLength  = sizeof(MN_APP_SS_REGPWD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        PS_MEM_CPY(&(pstStkMsg->stTafSsRegPwdReq),
                   &(pstMmiOpParam->RegPwdReq),
                   sizeof(TAF_SS_REGPWD_REQ_STRU));
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_Modify2DeactivateCcbsMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg             = VOS_NULL_PTR;
    TAF_SS_ERASECC_ENTRY_REQ_STRU      *pstSsEraseccReq       = VOS_NULL_PTR;

    /* STK���ᷢ�͸���Ϣ��ֻ������ATģ�鷢�� */
    if (WUEPS_PID_AT != ulSenderPid)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_Modify2DeactivateCcbsMsg: Sender Pid Error.");
        return VOS_FALSE;
    }

    /*
    �������pMsg��������û���Ϣ���ݣ�CALL CONTROL���ΪMODFIFY����Ҫ�����û���
    ִ�е�������Ϣ���Ͳ���ҵ����������������������漰������ʹ���û��·���TAF�����ݣ�
    ���ԣ���Ϣ�ṹ���������ֲ����£�
    */
    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

    /* ��Ҫ�޸���Ϣ�������Ⱥ;�����Ϣ���� */
    pstAppMsg->usMsgName = TAF_MSG_ERASECCENTRY_MSG;
    /*lint -e961*/
    pstAppMsg->ulLength  = sizeof(MN_APP_REQ_MSG_STRU) + sizeof(TAF_SS_ERASECC_ENTRY_REQ_STRU)
                              - sizeof(pstAppMsg->aucContent) - VOS_MSG_HEAD_LENGTH;
    /*lint +e961*/
    pstSsEraseccReq      = (TAF_SS_ERASECC_ENTRY_REQ_STRU *)pstAppMsg->aucContent;

    PS_MEM_CPY(pstSsEraseccReq,
               &(pstMmiOpParam->stCcbsEraseReq),
               sizeof(TAF_SS_ERASECC_ENTRY_REQ_STRU));

    return VOS_TRUE;
}
VOS_VOID TAF_SPM_ModifyCallReqEntryMsgWithCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* ���������Ϣ�е�PID����ʱAT����STK����ĺ���������Ϣ */
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstEntryMsg     = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    ulEventType     = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        pstAtOrigParam->stOrig.enCallType = enCallType;
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��ǿ�Ͷ෽ͨ�����ܸ���callType,  */
        ;
    }
#endif
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        pstStkOrigParam->enCallType = enCallType;
    }

    return;
}


VOS_VOID TAF_SPM_ModifyCallReqEntryMsgWithDailNumber(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    VOS_UINT32                          ulIndex
)
{
    /* ���������Ϣ�е�PID����ʱAT����STK����ĺ���������Ϣ */
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulNum;
#endif
    VOS_UINT32                          ulEventType;

    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    ulEventType         = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);
#if (FEATURE_ON == FEATURE_IMS)
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        if ((0                              < pstDialNumber->ucNumLen)
         && (MN_CALL_MAX_CALLED_BCD_NUM_LEN >= pstDialNumber->ucNumLen))
        {
            pstAtOrigParam->stOrig.stDialNumber.enNumType = pstDialNumber->enNumType;
            pstAtOrigParam->stOrig.stDialNumber.ucNumLen  = pstDialNumber->ucNumLen;

            PS_MEM_CPY(&(pstAtOrigParam->stOrig.stDialNumber.aucBcdNum[0]), &(pstDialNumber->aucBcdNum[0]), pstAtOrigParam->stOrig.stDialNumber.ucNumLen);
        }
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        ulNum = ((ulIndex + 1) > pstEconfInfoAddr->ucCallNum) ?
                (pstEconfInfoAddr->ucCallNum - 1) : ulIndex;

        if ((0                              < pstDialNumber->ucNumLen)
         && (MN_CALL_MAX_CALLED_BCD_NUM_LEN >= pstDialNumber->ucNumLen))
        {
            pstEconfInfoAddr->astEconfCheckInfo[ulNum].stCalledNumber.enNumType = pstDialNumber->enNumType;
            pstEconfInfoAddr->astEconfCheckInfo[ulNum].stCalledNumber.ucNumLen  = pstDialNumber->ucNumLen;
            PS_MEM_CPY(pstEconfInfoAddr->astEconfCheckInfo[ulNum].stCalledNumber.aucBcdNum,
                       pstDialNumber->aucBcdNum,
                       pstDialNumber->ucNumLen);
        }
    }
#endif
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        if ((0                              < pstDialNumber->ucNumLen)
         && (STK_CALL_ADDR_MAX_LEN          >= pstDialNumber->ucNumLen))
        {
            pstStkOrigParam->stCalledAddr.ucAddrType    = pstDialNumber->enNumType;
            pstStkOrigParam->stCalledAddr.ucLen         = pstDialNumber->ucNumLen;

            PS_MEM_CPY(pstStkOrigParam->stCalledAddr.aucAddr,pstDialNumber->aucBcdNum, pstStkOrigParam->stCalledAddr.ucLen);
        }

    }

    return;
}
VOS_VOID TAF_SPM_ModifyCallReqEntryMsgWithEmergencyCat(
    MN_CALL_EMERGENCY_CAT_STRU         *ppstEmergencyCat
)
{
    /* ���������Ϣ�е�PID����ʱAT����STK����ĺ���������Ϣ */
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstEntryMsg     = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    ulEventType     = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        PS_MEM_CPY(&pstAtOrigParam->stOrig.stEmergencyCat, ppstEmergencyCat,sizeof(MN_CALL_EMERGENCY_CAT_STRU));
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��ǿ�Ͷ෽ͨ���������stEmergencyCat */
        ;
    }
#endif
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        pstStkOrigParam->stEmergencyCat.bExist          = ppstEmergencyCat->bExist;
        pstStkOrigParam->stEmergencyCat.ucEmergencyCat  = ppstEmergencyCat->ucEmergencyCat;
    }

    return;
}



VOS_VOID TAF_SPM_ModifyCallReqEntryMsgWithSubAddr(
    MN_CALL_SUBADDR_STRU               *pstSubAddr,
    VOS_UINT32                          ulIndex
)
{
    /* ���������Ϣ�е�PID����ʱAT����STK����ĺ���������Ϣ */
    MN_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam     = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam      = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulNum;
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
#endif



    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    ulEventType         = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);
#if (FEATURE_ON == FEATURE_IMS)
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        if ((0                            < pstSubAddr->LastOctOffset)
         && (MN_CALL_MAX_SUBADDR_INFO_LEN > pstSubAddr->LastOctOffset))
        {
            PS_MEM_CPY(&pstAtOrigParam->stOrig.stSubaddr, pstSubAddr, sizeof(MN_CALL_SUBADDR_STRU));
        }
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        ulNum = ((ulIndex + 1) > pstEconfInfoAddr->ucCallNum) ?
                  (pstEconfInfoAddr->ucCallNum - 1) : ulIndex;

        if ((0                            < pstSubAddr->LastOctOffset)
         && (MN_CALL_MAX_SUBADDR_INFO_LEN > pstSubAddr->LastOctOffset))
        {
            PS_MEM_CPY(&pstEconfInfoAddr->astEconfCheckInfo[ulNum].stSubaddr, pstSubAddr, sizeof(MN_CALL_SUBADDR_STRU));
        }
    }
#endif
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        if ((0                        < pstSubAddr->LastOctOffset)
         && (STK_CALL_SUBADDR_MAX_LEN > pstSubAddr->LastOctOffset))
        {
            pstStkOrigParam->stSubAddr.ucLen            = pstSubAddr->LastOctOffset;
            pstStkOrigParam->stSubAddr.aucSubAddr[0]    = pstSubAddr->Octet3;

            PS_MEM_CPY(&(pstStkOrigParam->stSubAddr.aucSubAddr[1]),
                       &(pstSubAddr->SubAddrInfo[0]),
                       (pstStkOrigParam->stSubAddr.ucLen -1));
        }
    }

    return;
}
VOS_VOID TAF_SPM_ModifyCallReqEntryMsgWithBCInfo(
    const NAS_CC_IE_BC_STRU            *pstBc
)
{
    /* ���������Ϣ�е�PID����ʱAT����STK����ĺ���������Ϣ */
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;

    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    ulEventType         = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        PS_MEM_SET(&stDataCfgInfo, 0x0, sizeof(stDataCfgInfo));

        /* �ȸ�ԭʼֵ��ֹת��BC��Ϣ������������Ϣʧ�� */
        PS_MEM_CPY(&stDataCfgInfo, &pstAtOrigParam->stOrig.stDataCfg, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));

        /* ��BC1��Ϣת��Ϊ���ݺ���������Ϣ */
        MN_CALL_GetDataCfgInfoFromBc(pstBc, &stDataCfgInfo);

        PS_MEM_CPY(&pstAtOrigParam->stOrig.stDataCfg, &stDataCfgInfo, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��ǿ�Ͷ෽ͨ�����ܸ���stDataCfg, ��Ϊ�ܶ����ֻ��Ӧһ��stDataCfg */
        ;
    }
#endif
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        if ((0                   < pstBc->LastOctOffset)
         && (STK_CALL_BC_MAX_LEN > pstBc->LastOctOffset))
        {
            pstStkOrigParam->stBc.ucLen = pstBc->LastOctOffset;

            PS_MEM_CPY(&(pstStkOrigParam->stBc.aucBc[0]),
                       &(pstBc->Octet3),
                       pstStkOrigParam->stBc.ucLen);
        }
    }

    return;
}



VOS_UINT32 TAF_SPM_IsCallCtrlModifyBeyondCapability_CALL(
    SI_STK_CALLCTRL_RSP_STRU           *pstCallCtrlRsp,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_TYPE_ENUM_U8               *penCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulExistBc;
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_EMERGENCY_CAT_STRU          stTmpEmcCat;

    PS_MEM_SET(&stTmpEmcCat, 0, sizeof(stTmpEmcCat));

    /* �����º�ĺ��������Ƿ��������  */
    if (VOS_FALSE != pstCallCtrlRsp->OP_SepcialData)
    {
        if (SI_CC_ADDRESS_TAG != pstCallCtrlRsp->SpecialData.ucTag)
        {
            MN_WARN_LOG("TAF_SPM_IsCallCtrlModifyBeyondCapability_CALL: ucTag is not SI_CC_ADDRESS_TAG.");

            return VOS_TRUE;
        }

        stDialNumber.ucNumLen  = pstCallCtrlRsp->SpecialData.ucLen  - sizeof(stDialNumber.enNumType);
        stDialNumber.enNumType = *pstCallCtrlRsp->SpecialData.pValue;
        PS_MEM_CPY(stDialNumber.aucBcdNum,
                   (pstCallCtrlRsp->SpecialData.pValue + sizeof(stDialNumber.enNumType)),
                   stDialNumber.ucNumLen);

        /* VIDEO call������ͨ���д������������к����� */
        if ((MN_CALL_TYPE_VIDEO    != enCallType)
         && (MN_CALL_TYPE_VIDEO_RX != enCallType)
         && (MN_CALL_TYPE_VIDEO_TX != enCallType))
        {
            /* ����ǽ������и��½������е�CAT��Ϣ */
            if (VOS_TRUE == TAF_SPM_IsEmergencyNum(&stDialNumber,
                                                    VOS_FALSE,
                                                    &stTmpEmcCat))
            {
                *penCallType                    = MN_CALL_TYPE_EMERGENCY;

                pstEmergencyCat->bExist         = stTmpEmcCat.bExist;
                pstEmergencyCat->ucEmergencyCat = stTmpEmcCat.ucEmergencyCat;

                return VOS_FALSE;
            }
        }
    }

    /* �����º�ĺ��������Ƿ�֧�� */
    ulExistBc   = (0 != pstCallCtrlRsp->OP_CCP1) ? VOS_TRUE : VOS_FALSE;
    ulRet       = TAF_SPM_GetBcCallType(ulExistBc,
                                        pstCallCtrlRsp->CCP1.ulLen,
                                        pstCallCtrlRsp->CCP1.pucCCP,
                                        &enCallType);

    if (VOS_TRUE != ulRet)
    {
        return VOS_TRUE;
    }

    /* �޸ĺ�ĺ�������UE��֧�� */
    if (VOS_FALSE == TAF_SPM_IsUESupportMoCallType(enCallType))
    {
        MN_WARN_LOG("TAF_SPM_IsCallCtrlModifyBeyondCapability_CALL: Modified Calltype Not supported.");
        return VOS_TRUE;
    }

    *penCallType = enCallType;

    return VOS_FALSE;
}
VOS_VOID TAF_SPM_GetVaildBcdNum(
    VOS_UINT8                           ucSrcNumLen,
    VOS_UINT8                          *pucSrcBcdNum,
    VOS_UINT8                          *pucDestNumLen,
    VOS_UINT8                          *pucDestBcdNum
)
{
    VOS_UINT8                           aucTemp[2*MN_CALL_MAX_CALLED_BCD_NUM_LEN];
    VOS_UINT8                           ucFirstBcdNum;
    VOS_UINT8                           ucSecondBcdNum;
    VOS_UINT8                           ucBcdNumCount;
    VOS_UINT8                           ucDestBcdNum;
    VOS_UINT8                           ucMin;
    VOS_UINT32                          ulIndex;

    ucBcdNumCount       = 0;
    ucDestBcdNum        = 0;

    PS_MEM_SET(aucTemp, 0x00, sizeof(aucTemp));

    /* ѭ����Ҫ��BCD�뱣��ĵ绰���룬ת������Ӧ���������� */
    /* ��BCD����0x21,0x43��ת������Ӧ��1,2,3,4 */
    ucMin = (ucSrcNumLen < MN_CALL_MAX_CALLED_BCD_NUM_LEN) ? ucSrcNumLen : MN_CALL_MAX_CALLED_BCD_NUM_LEN;
    for ( ulIndex = 0; ulIndex < ucMin; ulIndex++)
    {
        ucFirstBcdNum = (VOS_UINT8)((*(pucSrcBcdNum + ulIndex)) & 0x0f);            /*low four bits*/

        if (0x0f != ucFirstBcdNum)
        {
            aucTemp[ucBcdNumCount] = ucFirstBcdNum;
            ucBcdNumCount++;
        }

        ucSecondBcdNum = (VOS_UINT8)(((*(pucSrcBcdNum + ulIndex)) >> 4) & 0x0f);   /*high four bits*/

        if (0x0f != ucSecondBcdNum)
        {
            aucTemp[ucBcdNumCount] = ucSecondBcdNum;
            ucBcdNumCount++;
        }
    }

    ucMin = (ucBcdNumCount < (2*MN_CALL_MAX_CALLED_BCD_NUM_LEN)) ? ucBcdNumCount : (2*MN_CALL_MAX_CALLED_BCD_NUM_LEN);
    for ( ulIndex = 0 ; ulIndex < ucMin; ulIndex++ )
    {
        /* aucTemp���������λΪ��4λ��ż��λΪ��4λ */
        if (1 == (ulIndex & 0x01))
        {
            pucDestBcdNum[(ulIndex >> 1)] |= (VOS_UINT8)(aucTemp[ulIndex] << 4);
        }
        else
        {
            pucDestBcdNum[(ulIndex >> 1)] = aucTemp[ulIndex];

            /* ������Ҫ�ڵ�λ����д֮��+1 */
            ucDestBcdNum++;
        }
    }

    if (1 == (ulIndex & 0x01))
    {
        pucDestBcdNum[(ulIndex >> 1)] |= 0xf0;
    }

    *pucDestNumLen = ucDestBcdNum;

}



VOS_VOID TAF_SPM_ModifyCallEntryMsgByCallCtrlMsg(
    SI_STK_CALLCTRL_RSP_STRU           *pstCallCtrlRsp,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat,
    VOS_UINT32                          ulIndex
)
{
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_SUBADDR_STRU                stSubAddr;
    VOS_UINT8                           ucNumLen;
    VOS_UINT8                           aucBcdNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN];

    PS_MEM_SET(&stDataCfgInfo, 0x00, sizeof(stDataCfgInfo));
    PS_MEM_SET(&stBc1CallCnf, 0x00, sizeof(stBc1CallCnf));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(stDialNumber));
    PS_MEM_SET(&stSubAddr, 0x00, sizeof(stSubAddr));
    PS_MEM_SET(aucBcdNum, 0x00, sizeof(aucBcdNum));

    /* ���������Ϣ�еĺ������� */
    TAF_SPM_ModifyCallReqEntryMsgWithCallType(enCallType);

    if (VOS_FALSE != pstCallCtrlRsp->OP_SepcialData)
    {
        stDialNumber.enNumType = *pstCallCtrlRsp->SpecialData.pValue;

        ucNumLen  = pstCallCtrlRsp->SpecialData.ucLen - sizeof(stDialNumber.enNumType);

        PS_MEM_CPY(aucBcdNum,
                    (pstCallCtrlRsp->SpecialData.pValue + sizeof(stDialNumber.enNumType)),
                     ucNumLen);

        PS_MEM_SET(stDialNumber.aucBcdNum, 0x00, sizeof(stDialNumber.aucBcdNum));

        TAF_SPM_GetVaildBcdNum(ucNumLen, aucBcdNum, &stDialNumber.ucNumLen, stDialNumber.aucBcdNum);

        /* ���������Ϣ�еĺ��к��� */
        TAF_SPM_ModifyCallReqEntryMsgWithDailNumber(&stDialNumber, ulIndex);

        /* ����ǽ�������ʱ,���������Ϣ�е�stEmergencyCat��Ϣ */
        if (MN_CALL_TYPE_EMERGENCY == enCallType)
        {
            TAF_SPM_ModifyCallReqEntryMsgWithEmergencyCat(pstEmergencyCat);
        }
    }

    if (VOS_FALSE != pstCallCtrlRsp->OP_SubAddr)
    {
        PS_MEM_SET(&stSubAddr, 0, sizeof(stSubAddr));
        stSubAddr.IsExist       = VOS_TRUE;
        stSubAddr.LastOctOffset = (VOS_UINT8)pstCallCtrlRsp->SubAddrStr.ulLen;
        PS_MEM_CPY(&stSubAddr.Octet3,
                   pstCallCtrlRsp->SubAddrStr.pucSubaddr,
                   stSubAddr.LastOctOffset);

        /* ����ʵ����ӵ�ַ */
        TAF_SPM_ModifyCallReqEntryMsgWithSubAddr(&stSubAddr, ulIndex);
    }

    if (VOS_FALSE != pstCallCtrlRsp->OP_CCP1)
    {
        PS_MEM_SET(&stBc1CallCnf, 0x00, sizeof(stBc1CallCnf));

        stBc1CallCnf.IsExist        = VOS_TRUE;
        stBc1CallCnf.LastOctOffset  = (VOS_UINT8)pstCallCtrlRsp->CCP1.ulLen;
        PS_MEM_CPY(&stBc1CallCnf.Octet3,
                   pstCallCtrlRsp->CCP1.pucCCP,
                   pstCallCtrlRsp->CCP1.ulLen);

        /* ���������Ϣ�����ݺ���������ϢstDataCfgInfo */
        TAF_SPM_ModifyCallReqEntryMsgWithBCInfo(&stBc1CallCnf);
    }

    return;
}


VOS_VOID TAF_SPM_ProcCallCtrlRsltAllowModify_CALL(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause,
    VOS_UINT32                                              ulIndex
)
{
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
#endif
    VOS_UINT32                          ulRet;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    MN_CALL_TYPE_ENUM_U8                enModifiedCallType;
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    MN_CALL_CS_DATA_CFG_STRU            stDataCfg;

    PS_MEM_SET(&stDataCfg, 0x00, sizeof(stDataCfg));
    PS_MEM_SET(&stEmergencyCat, 0, sizeof(stEmergencyCat));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(stDialNumber));
#if (FEATURE_ON == FEATURE_IMS)
    ulEventType         = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
#endif

    enCallType = MN_CALL_TYPE_VOICE;

#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        enCallType = pstEconfInfoAddr->enCallType;
    }
    else
#endif
    {
        TAF_SPM_GetCallInfoFromFsmEntryMsg(&stDialNumber, &enCallType, &enCallMode, &stDataCfg);
    }

    /* ���USIM�޸ĺ�ĺ��������Ƿ񳬳�UE������ */
    ulRet = TAF_SPM_IsCallCtrlModifyBeyondCapability_CALL(&pstCallCtrlRsp->uResp.CallCtrlRsp,
                                                          enCallType,
                                                          &enModifiedCallType,
                                                          &stEmergencyCat);

    /* ��������ֱ�ӷ��� */
    if (VOS_TRUE == ulRet)
    {
        *pulCause = TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

         return;
    }

#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        /* ��ǿ�Ͷ෽ͨ�������޸�Call Type, ���Ҫ�޸ģ��ж�Ϊ��������쳣 */
        if (enModifiedCallType != enCallType)
        {
            *penRslt   = TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY;
            *pulCause  = TAF_SPM_SERVICE_CTRL_FAIL;

            return;
        }
    }
#endif

    /* ʹ���޸ĺ�ĺ������ͺͽ�������CAT��Ϣ���������Ϣ */
    TAF_SPM_ModifyCallEntryMsgByCallCtrlMsg(&pstCallCtrlRsp->uResp.CallCtrlRsp,
                                             enModifiedCallType,
                                             &stEmergencyCat,
                                             ulIndex);

    *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;
    *pulCause  = TAF_CS_CAUSE_SUCCESS;

    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_SPM_ProcEconfEnvelopeCnf(
    VOS_UINT32                          ulCause,
    VOS_UINT32                          ulIndex
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulNum;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();

    ulNum = ((ulIndex + 1) > pstEconfInfoAddr->ucCallNum) ?
            (pstEconfInfoAddr->ucCallNum - 1) : ulIndex;

    /* ��¼��� */
    TAF_SPM_RecordEconfCheckRslt(ulNum, ulCause);

    /* ������н�����Ѿ��ظ� */
    if (pstEconfInfoAddr->ucRcvNum == pstEconfInfoAddr->ucSendSuccNum)
    {
        TAF_SPM_StopTimer(TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF, pstEconfInfoAddr->usClientId);

        ulRslt = TAF_SPM_ProcEconfCheckResult();

        (VOS_VOID)TAF_SPM_ProcEconfCallCtrlCheckResult(ulRslt, pstEconfInfoAddr->usClientId, pstEntryMsg);
    }
}
#endif


VOS_VOID TAF_SPM_ProcCallEnvelopeCnf(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU                           *pstEnvelopeCnf,
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
)
{
    SI_STK_ENVELOPE_RSP_STRU            stMoCallRsp;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulEntryMsgEventType;
    VOS_UINT32                          ulEconfFlag;
#endif
    VOS_UINT32                          ulIndex;

#if (FEATURE_ON == FEATURE_IMS)
    ulEntryMsgEventType = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    ulEconfFlag         = VOS_FALSE;
#endif
    ulIndex             = 0;

    PS_MEM_SET(&stMoCallRsp, 0, sizeof(SI_STK_ENVELOPE_RSP_STRU));

    /* ����OP���Ƿ���Ч��SpecialData.ucTagʼ������Ч�� */
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    stMoCallRsp.EnvelopeType                          = pstEnvelopeCnf->enEnvelopeType;
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    stMoCallRsp.uResp.CallCtrlRsp.SpecialData.ucTag   = SI_CC_ADDRESS_TAG;

    /* ֻ��Я��������������ʾ��ָʾ�ܾ�����Ϊ���ʧ��,�˴���ΪUSIM����
       �ݴ��֧,�����ΪOK��datalenΪ0Ҳ��Ϊ�ɹ� */
#if (FEATURE_ON == FEATURE_IMS)
    if (ulEntryMsgEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        ulIndex = TAF_SPM_ECONF_GET_INDEX_FROM_PARA(pstEnvelopeCnf->stCmdResult.ulSendPara);
        pstEconfInfoAddr->ucRcvNum++;
        ulEconfFlag = VOS_TRUE;
    }
#endif

    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    if (VOS_OK != (pstEnvelopeCnf->stCmdResult.ulResult))
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    {
        *pulCause = TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;

        stMoCallRsp.Result                              = SI_STK_CTRL_NOT_ALLOW;

        NAS_STKAPI_CCResultInd(&stMoCallRsp);

#if (FEATURE_ON == FEATURE_IMS)
		if (VOS_TRUE == ulEconfFlag)
		{
			TAF_SPM_ProcEconfEnvelopeCnf(*pulCause, ulIndex);
		}
#endif

        return;
    }

    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    if (0 == pstEnvelopeCnf->stCnfData.ulRspDataLen)
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    {
        *pulCause  = TAF_CS_CAUSE_SUCCESS;
        *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;

        stMoCallRsp.Result    = SI_STK_CTRL_ALLOW_NOMODIFY;

        NAS_STKAPI_CCResultInd(&stMoCallRsp);

#if (FEATURE_ON == FEATURE_IMS)
        if (VOS_TRUE == ulEconfFlag)
        {
            TAF_SPM_ProcEconfEnvelopeCnf(*pulCause, ulIndex);
        }
#endif

        return;
    }

    /* ��Ϣ���� */
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    (VOS_VOID)NAS_STKAPI_EnvelopeRsp_Decode(pstEnvelopeCnf->enEnvelopeType, pstEnvelopeCnf->stCnfData.ulRspDataLen, pstEnvelopeCnf->stCnfData.aucRspData, &stMoCallRsp);
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */

    if (SI_STK_CTRL_ALLOW_MODIFY == stMoCallRsp.Result)
    {
        TAF_SPM_ProcCallCtrlRsltAllowModify_CALL(&stMoCallRsp, penRslt, pulCause, ulIndex);

        /* ����޸ĺ�Ĳ���������������Ҫ����stCallCtrlRsp�Ľ�� */
        if (TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY == *pulCause)
        {
            stMoCallRsp.Result = SI_STK_CTRL_NOT_ALLOW;
        }
    }
    else if (SI_STK_CTRL_NOT_ALLOW == stMoCallRsp.Result)
    {
        *pulCause = TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED;
        *penRslt  = TAF_SPM_SERVICE_CTRL_FAIL;
    }
    else if (SI_STK_CTRL_ALLOW_NOMODIFY == stMoCallRsp.Result)
    {
        *pulCause  = TAF_CS_CAUSE_SUCCESS;
        *penRslt   = TAF_SPM_SERVICE_CTRL_SUCC;
    }
    else
    {
        /* SI_STK_CTRL_BUTT�������Ϊʧ�� */
        *pulCause  = TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER;
        *penRslt   = TAF_SPM_SERVICE_CTRL_FAIL;
    }

    NAS_STKAPI_CCResultInd(&stMoCallRsp);

    NAS_STKAPI_EnvelopeRspDataFree(&stMoCallRsp);

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == ulEconfFlag)
    {
        TAF_SPM_ProcEconfEnvelopeCnf(*pulCause, ulIndex);
    }
#endif

    return;
}
VOS_UINT32 TAF_SPM_ProcFdnCheckResult(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usClientId,
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    if (VOS_FALSE == ulRslt)
    {
        /* ����ʧ�ܵ�״̬���˳������Ϣ��TAF */
        TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL, TAF_CS_CAUSE_FDN_CHECK_FAILURE, usClientId, pstEntryMsg);

        /* �˳�״̬�� */
        TAF_SPM_FSM_QuitCurrEntityFsm();
    }
    else
    {
        if (VOS_FALSE == TAF_SPM_IsNeedCallControl())
        {
            /* ���ͳɹ���״̬���˳������Ϣ��TAF */
            TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC, TAF_CS_CAUSE_SUCCESS, usClientId, pstEntryMsg);

            /* �˳�״̬�� */
            TAF_SPM_FSM_QuitCurrEntityFsm();

            return VOS_TRUE;
        }

        TAF_SPM_StartCallControlCheck_ServiceCtrl(usClientId, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_ProcEconfCallCtrlCheckResult(
    VOS_UINT32                          enRslt,
    VOS_UINT16                          usClientId,
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    if (VOS_TRUE == enRslt)
    {
        TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_SUCC,
                                      TAF_CS_CAUSE_SUCCESS,
                                      usClientId,
                                      pstEntryMsg);
    }
    else
    {
        TAF_SPM_SndServiceCtrlRsltInd(TAF_SPM_SERVICE_CTRL_FAIL,
                                      TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER,
                                      usClientId,
                                      pstEntryMsg);
    }

    /* �˳�״̬�� */
    TAF_SPM_FSM_QuitCurrEntityFsm();

    return VOS_TRUE;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


