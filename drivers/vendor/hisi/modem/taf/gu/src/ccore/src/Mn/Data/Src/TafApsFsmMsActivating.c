

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "MmcApsInterface.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivating.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndSm.h"
#include "TafApsSndRabm.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#endif
#include "TafApsComFunc.h"
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"

#include "TafSdcLib.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSACTIVATING_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
    TAF_PDP_TABLE_STRU                 *pstCidCtx;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();
    ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstCidCtx            = TAF_APS_GetTafCidInfoAddr(ucCid);

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* �ϱ�PDP������� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                    TAF_PS_CAUSE_SIM_INVALID);

        /* �����Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }
    }

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF����, ��������*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */


    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == pstCidCtx->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstCidCtx->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* �ϱ�PDP������� */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_SIM_INVALID);

        /* �����Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS);
        }
    }

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF����, ��������*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ucT3402State;
#endif

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* �ϱ�PDP������� */
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_SIM_INVALID);

        /* �����Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                   pstCallOrigReq->stDialParaInfo.ucCid,
                                   TAF_PS_CAUSE_SUCCESS);
        }
    }

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF����, ��������*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
            if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
            {
                ucT3402State   = TAF_APS_IsT3402Running();

                if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
                 && (VOS_TRUE  == ucT3402State))
                {
                    /* ֹͣ�������̶�ʱ�� */
                    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                                      ucPdpId);

                    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH);

                    /* �ͷ�APS��Դ */
                    Aps_ReleaseApsResource(ucPdpId);

                    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
                    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
                    TAF_APS_QuitCurrSubFsm();
                    return VOS_TRUE;
                }
            }
#endif
            TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);

            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���ڼ����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP�������, ERROR */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�PDP�������, NO_ERROR */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�PDP�������, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg         = VOS_NULL_PTR;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstEntryMsg            = TAF_APS_GetCurrSubFsmMsgAddr();
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ʱ�����״̬Ϊ��Ч����Ҫ��ֹ���� */
    if (VOS_FALSE == pstServStaChangeInd->ulPsSimRegStatus)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ������¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SIM_INVALID);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: Unknown message!");
                break;
        }
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: Unknown message!");
                break;
        }
    }
#endif
    else
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: RAT type is NULL!");
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��ʱ��ʣ��ʱ�� */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* ���ʣ��ʱ����0, ֹͣ��ǰ����, ���´���ǰ��״̬�������Ϣ */
    if (0 != ulRemainTimeLen)
    {
        /* ��¼ʣ��ʱ�� */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����״̬�������Ϣ���ڲ���Ϣ���� */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
#endif
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ȥ�����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��SM����ABORT����, ȡ����ǰ������� */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�PDP�������, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��SM����ABORT����, ȡ����ǰ������� */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����˵��,��״̬���в���Ҫ��TEARDOWN
       �ٽ����жϴ���,APS���յ�ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ��?�Ƚ���Ԥ��
       ��,�����Ϣ�д���TEARDOWN,Ԥ�������ҳ�������ЩPDP��ȥ����,Ȼ��,��
       ID_PMC_SMREG_PDP_DEACTIV_IND�ַ�����Ӧ��ʵ��״̬��,����,��״̬���в���
       ��ID_PMC_SMREG_PDP_DEACTIV_IND�е�TEARDOWN�������� */

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ��״̬���յ�ID_PMC_SMREG_PDP_DEACTIV_INDΪ�쳣��Ϣ,�ϱ������¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmPdpActivateRej;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpActivateRej = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ����PDPȥ����ָʾ��Ϣ ,�ϱ���AT��Aps_PdpActRej�ڲ�ʵ�� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpActivateRej->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSmPdpActSecRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmSecPdpActivateRej;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmSecPdpActivateRej  = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ����PDPȥ����ָʾ��Ϣ ,�ϱ���AT��Aps_PdpActRej�ڲ�ʵ�� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmSecPdpActivateRej->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTCNF_PARA_ST                  stParam;
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    #endif
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmPdpActivateCnf;


    PS_MEM_SET(&stParam, 0x00, sizeof(stParam));


    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpActivateCnf = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    #endif

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �������Ĳ��� */
    ulRet = Aps_PdpActCnfParaCheck(pstSmPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        if (APS_PDPTYPE_INVALID == ulRet)
        {
            /* �ϱ�����ʧ�� */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* �����ڲ���Ϣ, ȥ����PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);
        }
        else
        {
            /* �ϱ�����ʧ�� */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

            /* �����ڲ���Ϣ, ȥ����PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
        }

        return VOS_TRUE;
    }

    /* ���QOS�Ƿ�����MINҪ�� */
    if (APS_PARA_VALID  == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* ����MINQOS */
        Aps_PdpActCnfQosSatisfy(ucPdpId, &stParam, pstSmPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_ACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* �����ַ������IPv6, ��Ҫͬ����ND Client */
        if (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
#endif

        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_GSM:
                /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:
                /* ����ɹ�����������ͳ�� */
                TAF_APS_StartDsFlowStats(pstSmPdpActivateCnf->ucNsapi);

                /* �����ǰAPSʵ���PDP����ΪIPv4, ��Ҫ����IPF */
                if (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId))
                {
                    /* ����IP������ */
                    TAF_APS_IpfConfigUlFilter(ucPdpId);
                }

                /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* ������MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTSECCNF_PARA_ST               stParam;
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmSecPdpActivateCnf;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmSecPdpActivateCnf  = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType           = TAF_APS_GetCurrPdpEntityRatType();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �������Ĳ��� */
    ulRet = Aps_PdpActSecCnfParaCheck(pstSmSecPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        /* �ϱ�����ʧ�� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER );

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

        return VOS_TRUE;
    }

    /* ���QOS�Ƿ�����MINҪ�� */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* ����MINQOS */
        Aps_PdpActSecCnfQosSatisfy(ucPdpId, &stParam, pstSmSecPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_ACTIVATE);
#endif

        /* ���ݵ�ǰģ��״̬Ǩ�� */
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_GSM:

                /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:

                /* �����ǰAPSʵ���PDP����ΪIPv4, ��Ҫ����IPF, Ŀǰ��֧��Secondary PDP */

                /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }

    }
    else
    {
        /* ������MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ��״̬���յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_INDΪ�쳣��Ϣ,�ϱ������¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ��ʱ��LģӦ����һ���쳣��Ϣ */
    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* �ͷ�SM��Դ */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ȥ�����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* �ϱ�PDP��������¼�*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��SM����ABORT����, ȡ����ǰ������� */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�PDP�������, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��SM����ABORT����, ȡ����ǰ������� */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����˵��,��״̬���в���Ҫ��TEARDOWN
       �ٽ����жϴ���,APS���յ�ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ���Ƚ���Ԥ��
       ��,�����Ϣ�д���TEARDOWN,Ԥ�������ҳ�������ЩPDP��ȥ����,Ȼ��,��
       ID_PMC_SMREG_PDP_DEACTIV_IND�ַ�����Ӧ��ʵ��״̬��,����,��״̬���в���
       ��ID_PMC_SMREG_PDP_DEACTIV_IND�е�TEARDOWN�������� */

   /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ��״̬���յ�ID_PMC_SMREG_PDP_DEACTIV_INDΪ�쳣��Ϣ,�ϱ������¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* �����Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE*/
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ��״̬���յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_INDΪ�쳣��Ϣ,�ϱ������¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* �����Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE*/
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmPdpActivateRej;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpActivateRej = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ����PDPȥ����ָʾ��Ϣ ,�ϱ���AT��Aps_PdpActRej�ڲ�ʵ�� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpActivateRej->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
#endif
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
#if (FEATURE_ON == FEATURE_LTE)
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg            = TAF_APS_GetCurrSubFsmMsgAddr();
#endif

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType) )
    {
        /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* LTEģ��Ҫ��GUģ����abort��Ϣ,����Lģ����PDP�������� */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend: Unknown message!");
                break;
        }
    }
#endif
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend: Wrong RAT type!");
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��ʱ��ʣ��ʱ�� */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* ���ʣ��ʱ����0, ֹͣ��ǰ����, ���´���ǰ��״̬�������Ϣ */
    if (0 != ulRemainTimeLen)
    {
        /* ��¼ʣ��ʱ�� */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* ��GUģ����ABORT��Ϣ */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����״̬�������Ϣ���ڲ���Ϣ���� */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
#endif


VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��SM����ABORT���� */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatTypeSuspend;
    APS_ACTCNF_PARA_ST                  stParam;
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    #endif
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmPdpActivateCnf;

    PS_MEM_SET(&stParam, 0x00, sizeof(stParam));

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpActivateCnf         = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatTypeSuspend        = TAF_APS_GET_RAT_TYPE_IN_SUSPEND();
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    #endif

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �������Ĳ��� */
    ulRet = Aps_PdpActCnfParaCheck(pstSmPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        if (APS_PDPTYPE_INVALID == ulRet)
        {
            /* �ϱ�����ʧ�� */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* �����ڲ���Ϣ, ȥ����PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);
        }
        else
        {
            /* �ϱ�����ʧ�� */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

            /* �����ڲ���Ϣ, ȥ����PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
        }

        return VOS_TRUE;
    }

    /* ���QOS�Ƿ�����MINҪ�� */
    if (APS_PARA_VALID  == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* ����MINQOS */
        Aps_PdpActCnfQosSatisfy(ucPdpId, &stParam, pstSmPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_ACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* �����ַ������IPv6, ��Ҫͬ����ND Client */
        if (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
#endif

        switch (enCurrRatTypeSuspend)
        {
            case TAF_APS_RAT_TYPE_GSM:
                /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:
                /* ����ɹ�����������ͳ�� */
                TAF_APS_StartDsFlowStats(pstSmPdpActivateCnf->ucNsapi);

                /* �����ǰAPSʵ���PDP����ΪIPv4, ��Ҫ����IPF */
                if (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId))
                {
                    /* ����IP������ */
                    TAF_APS_IpfConfigUlFilter(ucPdpId);
                }

                /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* ������MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ȥ�����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼�*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*---------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ---------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;


    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����˵��,��״̬���в���Ҫ��TEARDOWN
       �ٽ����жϴ���,APS���յ�ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����Ԥ����,
       �����Ϣ�д���TEARDOWN,Ԥ�������ҳ�������ЩPDP��ȥ����,Ȼ��,��
       ID_PMC_SMREG_PDP_DEACTIV_IND�ַ�����Ӧ��ʵ��״̬��,����,��״̬���в���
       ��ID_PMC_SMREG_PDP_DEACTIV_IND�е�TEARDOWN�������� */

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));


    /* �ͷ�SNDCP��Դ */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ulResult                            = VOS_OK;
    pstSnActivateRsp                    = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �����Ϣ���� */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp: Check para failed!");

        /* �ϱ�����ʧ�� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* �յ�SN_ACT_RSP���޸�APSʵ�����, ����XID����, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* ����RABM�Ĵ���ģʽ */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    /* �����ǰAPSʵ���PDP����ΪIPv4, ��Ҫ����IPF, Ŀǰֻ֧��Primary PDP */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)) )
    {
        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(pstSnActivateRsp->ucNsapi);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*�ϱ�����ʧ�ܲ�����Դ*/
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* �ͷ�SNDCP��Դ */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ��ʱ��NULLģӦ����һ���쳣��Ϣ */
    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp: Wrong RAT Type:", pstServStaChangeInd->enRatType);

        return VOS_TRUE;
    }

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, SM_TAF_CAUSE_SM_MAX_TIME_OUT);

    /* �����ڲ���Ϣ, ����PDPȥ�������� */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���ڼ����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼�*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*---------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ---------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����˵��,��״̬���в���Ҫ��TEARDOWN
       �ٽ����жϴ���,APS���յ�ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ��?�Ƚ���Ԥ��
       ��,�����Ϣ�д���TEARDOWN,Ԥ�������ҳ�������ЩPDP��ȥ����,Ȼ��,��
       ID_PMC_SMREG_PDP_DEACTIV_IND�ַ�����Ӧ��ʵ��״̬��,����,��״̬���в���
       ��ID_PMC_SMREG_PDP_DEACTIV_IND�е�TEARDOWN�������� */

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ��ȡ��ǰ״̬����APS���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ͷ�SNDCP��Դ */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    /* ��ȡ��Ϣ���� */
    pstSnStatusReq = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;

    /* ��ȡ��ǰ״̬����APS���� */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���SNDCPָ����SAPI��APSʵ���SAPI�Ƿ�ƥ�� */
    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* ��ȡ��ǰ״̬����APS���� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ͷ�SNDCP��Դ */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd     = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity            = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    switch (pstServStaChangeInd->enRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
            /* GUģ�� ,����Ҫ����,������SM�Ļظ�,״̬�ص�
               TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
            break;

        case TAF_APS_RAT_TYPE_WCDMA:
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
#endif
            /* ֹͣ�������̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            /* �ͷ�SNDCP��Դ */
            Aps_ReleaseSndcpResource(ucPdpId);

            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
            TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* ����ɹ�����������ͳ�� */
            TAF_APS_StartDsFlowStats(pstPdpEntity->ucNsapi);

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE_SUSPEND, �˳���״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
            break;

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF,
                "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend: Wrong RAT Type:", pstServStaChangeInd->enRatType);
            break;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* �����ڲ���Ϣ, ����PDPȥ�������� */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_MAX_TIME_OUT);
    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ulResult                            = VOS_OK;
    pstSnActivateRsp                    = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �����Ϣ���� */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp: Check para failed!");

        /* �ϱ�����ʧ�� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* �յ�SN_ACT_RSP���޸�APSʵ�����, ����XID����, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* ����RABM�Ĵ���ģʽ */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    /* �����ǰAPSʵ���PDP����ΪIPv4, ��Ҫ����IPF, Ŀǰֻ֧��Primary PDP */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)) )
    {
        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(pstSnActivateRsp->ucNsapi);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ȥ�����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼�*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��SM����ABORT����, ȡ����ǰ������� */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aPdpActivateCnf_MsActivate_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_PDP_ACTIVATE_CNF_STRU      *pstL4aPdpActivateCnf;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT32                          ulRet;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aPdpActivateCnf = (APS_L4A_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity         = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

#endif

    /* ȱʡ���ؼ���ɹ���, ��Ҫ���PDP�����Ƿ�ƥ�� */
    if (VOS_FALSE == pstL4aPdpActivateCnf->bitOpLinkCid)
    {
        ulRet = TAF_APS_ValidatePdpType(TAF_APS_GetPdpEntDialPdpType(ucPdpId, pstL4aPdpActivateCnf->ucCid),
                                        pstL4aPdpActivateCnf->stIpAddrInfo.enPdpType);
        if (ulRet != VOS_OK)
        {
            /* �ϱ�����ʧ�� */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* �����ڲ���Ϣ, ȥ����PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            return VOS_TRUE;
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* ���´����� */
    if ( (VOS_TRUE == pstL4aPdpActivateCnf->bitOpEsmCause)
      && (APS_L4A_SUCCESS != pstL4aPdpActivateCnf->ulEsmCause) )
    {
        pstPdpEntity->bitOpCause    = VOS_TRUE;
        pstPdpEntity->enCause       = TAF_APS_MapL4aCause(pstL4aPdpActivateCnf->ulEsmCause);
    }
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /*------------------------------------------------------------------
       �����ַ������IPv6, ��Ҫͬ����ND Client, Ŀǰ�ܹ���Ҫ���յ�ESM
       ��EPS����ͬ����Ϣ��֪ͨND Client
    ------------------------------------------------------------------*/

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats((VOS_UINT8)pstL4aPdpActivateCnf->ulRabId);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvL4aPdpActivateRej_MsActivate_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    APS_L4A_PDP_ACTIVATE_REJ_STRU      *pstL4aPdpActivateRej;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aPdpActivateRej    = (APS_L4A_PDP_ACTIVATE_REJ_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapL4aCause(pstL4aPdpActivateRej->ulEsmCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitL4aActivateCnf: Wrong RAT type:", pstServStaChangeInd->enRatType);
        return VOS_TRUE;
    }

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF_SUSPEND);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

#if (FEATURE_ON == FEATURE_IPV6)
        /* �����ַ������IPv6, ��Ҫͬ����ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��SM����ABORT����, ȡ����ǰ������� */
    TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetNdisconnCnf_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_SET_NDISCONN_CNF_STRU      *pstL4aSetNdisconnCnf;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aSetNdisconnCnf    = (APS_L4A_SET_NDISCONN_CNF_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    if (APS_L4A_SUCCESS != pstL4aSetNdisconnCnf->ulErrorCode)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aPppDialCnf_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_PPP_DIAL_CNF_STRU          *pstL4aPppDialCnf;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aPppDialCnf        = (APS_L4A_PPP_DIAL_CNF_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    if (APS_L4A_SUCCESS != pstL4aPppDialCnf->ulErrorCode)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ȥ�����APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼�*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);


    /* �ϱ�PDP�������, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aPdpActivateRej_MsActivate_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_PDP_ACTIVATE_REJ_STRU      *pstL4aPdpActivateRej;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aPdpActivateRej                = (APS_L4A_PDP_ACTIVATE_REJ_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��������벻����ϵͳ, ��ü���������ֹ */
    if (APS_L4A_ERR_SM_SUSPENDED != pstL4aPdpActivateRej->ulEsmCause)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapL4aCause(pstL4aPdpActivateRej->ulEsmCause));

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
    }

    return VOS_TRUE;

}
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��SM����ABORT����, ȡ����ǰ������� */
    TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

#if (FEATURE_ON == FEATURE_IPV6)
        /* �����ַ������IPv6, ��Ҫͬ����ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif

    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_LTE != pstServStaChangeInd->enRatType)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitL4aActivateCnfSuspend: Wrong RAT type:", pstServStaChangeInd->enRatType);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_APS_RAT_TYPE_1X   == pstServStaChangeInd->enRatType)
         || (TAF_APS_RAT_TYPE_HRPD == pstServStaChangeInd->enRatType))
        {

            /* ��ʼ��, ��ȡ��Ϣ���� */
            ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

            /* ֹͣ�������̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            TAF_APS_QuitCurrSubFsm();
        }
#endif
        return VOS_TRUE;
    }

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��ʱ��ʣ��ʱ�� */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* ���ʣ��ʱ����0, ֹͣ��ǰ����, ���´���ǰ��״̬�������Ϣ */
    if (0 != ulRemainTimeLen)
    {
        /* ��¼ʣ��ʱ�� */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* ��Lģ����ABORT��Ϣ */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����״̬�������Ϣ���ڲ���Ϣ���� */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

#endif


VOS_UINT32 TAF_APS_RcvL4aSetNdisconnCnf_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_SET_NDISCONN_CNF_STRU      *pstL4aSetNdisconnCnf;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aSetNdisconnCnf    = (APS_L4A_SET_NDISCONN_CNF_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    if (APS_L4A_SUCCESS != pstL4aSetNdisconnCnf->ulErrorCode)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aPppDialCnf_MsActivating_WaitL4aActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_PPP_DIAL_CNF_STRU          *pstL4aPppDialCnf;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstL4aPppDialCnf        = (APS_L4A_PPP_DIAL_CNF_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    if (APS_L4A_SUCCESS != pstL4aPppDialCnf->ulErrorCode)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitL4aActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}
#endif


VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ�� */
    enRet   = TAF_PS_CAUSE_SUCCESS;

    /* ��ȡAPSʵ������ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid   = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);
    if (VOS_TRUE == pstTafCidInfo->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstTafCidInfo->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    /* ����PDP�������� */
    enRet = TAF_APS_PsCallOrig(ucPdpId);
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* ���APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}


VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ�� */
    enRet             = TAF_PS_CAUSE_SUCCESS;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg       = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg         = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡAPSʵ������ */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));

    /* ����PDP�������� */
    enRet = MN_APS_RcvPppDialOrigReq(ucPdpId,
                                     &(pstPppDialOrigReq->stPppDialParaInfo));
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* ���APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ�������� */
    enRet          = TAF_PS_CAUSE_SUCCESS;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg      = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡAPSʵ������ */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���ú���IP���� */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, pstCallOrigReq->stDialParaInfo.enPdpType);

    /* ����PDP�������� */
    enRet = MN_APS_RcvCallOrigReq(ucPdpId, &(pstCallOrigReq->stDialParaInfo));
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* ���APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
    TAF_PDP_TABLE_STRU                 *pstCidCtx;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg          = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡAPSʵ������ */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���ע����ز�������ע�������ʶΪTRUE, �򻺴�ú��н������� */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* ����ôμ��������PDP���ͣ�����Ƕ���PDP�������Ҫ�ҵ���PDP����Ӧ��CID */
    pstCidCtx = TAF_APS_GetTafCidInfoAddr(ucCid);
    if (VOS_TRUE == pstCidCtx->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstCidCtx->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    /* ��L4A����EPS���ؼ������� */
    TAF_APS_SndL4aSetCgactReq(ucPdpId, pstSetPdpCtxStateReq);

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}


VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    TAF_APS_IPCP_INFO_STRU              stIpcpInfo;
    VOS_UINT32                          ulDecAuthRst;
    VOS_UINT32                          ulDecIpcpRst;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ�� */
    PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));
    PS_MEM_SET(&stIpcpInfo, 0, sizeof(TAF_APS_IPCP_INFO_STRU));

    /* ��ȡ��Ϣ���� */
    pstEntryMsg       = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg         = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡAPSʵ������ */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���ע����ز�������ע�������ʶΪTRUE, �򻺴�ú��н������� */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* ����PPP DIAL REQ��AUTH��IPCP��Ԫ */
    ulDecAuthRst = TAF_APS_DecodeAuthInfo(&stAuthInfo,
                                             &(pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth));
    ulDecIpcpRst = TAF_APS_DecodeIpcpPkt(&stIpcpInfo,
                                         pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stIPCP.aucIpcp,
                                         pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stIPCP.usIpcpLen);
    if ((VOS_OK != ulDecAuthRst)
     || (VOS_OK != ulDecIpcpRst))
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* ���APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    if (TAF_PDP_PPP == TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid))
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* ���APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    /* ��L4A����PPP�������� */
    TAF_APS_SndL4aPppDialReq(pstPppDialOrigReq,
                             &stAuthInfo,
                             &stIpcpInfo);

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ucT3402State;
#endif

    /* ��ȡ��Ϣ���� */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg      = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡAPSʵ������ */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡCID */
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        ucT3402State   = TAF_APS_IsT3402Running();

        if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
         && (VOS_TRUE  == ucT3402State))
        {
            /* ֹͣ�������̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH);

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            TAF_APS_QuitCurrSubFsm();
            return;
        }
    }
#endif

    /* ���ע����ز�������ע�������ʶΪTRUE, �򻺴�ú��н������� */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* ���ú���IP���� */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    /* ��L4A����EPS���ؼ������� */
    (VOS_VOID)TAF_APS_SndL4aCallOrigReq(pstCallOrigReq);

    /* ��״̬Ǩ����TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}

#endif

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

