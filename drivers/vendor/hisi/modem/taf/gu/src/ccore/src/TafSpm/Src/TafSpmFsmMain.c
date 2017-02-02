

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "AtMnInterface.h"
#include "TafTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "SsInclude.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmSndInternalMsg.h"
#include "MnErrorCode.h"
#include "TafLog.h"
#include "AtMnInterface.h"

#include "NasStkInterface.h"
#include "MnCallMnccProc.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafSdcLib.h"
#include "MnCallApi.h"

#include "TafAgentInterface.h"

#include "TafSpmRedial.h"
#include "TafSpmComFunc.h"
#include "TafSpmServiceDomainSelProc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_C

/*lint -save -e958 */

VOS_UINT32 TAF_SPM_RcvAppReqMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucIdleFsmIndex;

    (VOS_VOID)TAF_SPM_GetClientIdWithAppMsg(pstMsg, &usClientId);
    TAF_SPM_GetOpIdWithAppMsg(pstMsg, &ucOpId);

    /* �ж��Ƿ��д��ڿ���״̬�� */
    ucIdleFsmIndex = TAF_SPM_GetIdleEntityFsmIndex();

    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX == ucIdleFsmIndex)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvAppReqMsg_Main():WARNING: No Idle Entiy Fsm Exist!");
        /* ��ʱ��Ӧ��Ϊ��ʽ��Ӧ */
        TAF_SPM_SendServiceRequetFail_Main(ulEventType, pstMsg, MN_ERR_CLASS_SPM_BEYOND_CONCURRENCY_CAPABILITY);

#if (FEATURE_ON == FEATURE_IMS)
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_UNKNOWN);

        TAF_SPM_ReportEconfCheckRslt();
#endif
    }
    else
    {
        /* ���õ�ǰ״̬�������� */
        TAF_SPM_SetCurrEntityFsmAddr(ucIdleFsmIndex);

        /* ���õ�ǰclient IDʵ��״̬����client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* ����service ctrl״̬��,����fdn&CALL control��� */
        TAF_SPM_FSM_InitEntityFsm(TAF_SPM_FSM_SERVICE_CTRL,
                                      TAF_SPM_GetServiceCtrlFsmDescAddr(),
                                      TAF_SPM_SERVICE_CTRL_STA_INIT);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_RcvSpmServiceCtrlResultInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU                         *pstServiceCtrlRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucOpId;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulAppEventType;
    struct MsgCB                                           *pstAppMsg          = VOS_NULL_PTR;
#if (FEATURE_IMS == FEATURE_ON)
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
#endif

    ulRet   = VOS_TRUE;

    pstServiceCtrlRslt = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;

    TAF_SPM_GetOpIdWithAppMsg((struct MsgCB*)pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer, &ucOpId);

    pstAppMsg      = (struct MsgCB*)&(pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer[0]);
    ulAppEventType = pstServiceCtrlRslt->stEntryMsg.ulEventType;

    /* �����Ϊʧ�� */
    if (TAF_SPM_SERVICE_CTRL_FAIL == pstServiceCtrlRslt->enResult)
    {
        /* ��AT��STK����ʧ�ܽ��,Я��cause,��ʱ��Ӧ�޸�Ϊ��ʽ��Ӧ */
        TAF_SPM_SendServiceRequetFail_Main(ulAppEventType, pstAppMsg, pstServiceCtrlRslt->ulCause);

        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    enDomainSelRslt = TAF_SPM_ProcServiceRequestDomainSelection(ulAppEventType, pstAppMsg);

    ulRet           = TAF_SPM_ProcInitialDomainSelectionResult(ulAppEventType, pstAppMsg, enDomainSelRslt);
#else
    ulRet           = TAF_SPM_ProcReqMsgBasedOnNasSignalling(ulAppEventType, pstAppMsg);
#endif

    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* �����Ϊ�ɹ����ø��������Ϣ��ǲ������޸ĺ�������Ϣ��ȫ�ֱ����� */
    TAF_SPM_UpdateServiceCtrlEntryMsg(ulAppEventType, pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    return VOS_FALSE;
}

/* ɾ�� */


/* ��IMSA��Ϣ�Ĵ���ŵ�Ԥ������ʵ�� */

VOS_VOID TAF_SPM_SendServiceRequetFail_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)ulCause);
            break;

        default:
            break;

    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

