
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafMmaCtx.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMain.h"
#include "TafMmaSndApp.h"
#include "TafMmaComFunc.h"


#include "TafMmaMntn.h"
#include "NasComm.h"
/* Added by h00313353 for Iteration 13, 2015-4-13, begin */
#include "TafMmaFsmMain.h"
#include "TafMmaFsmMainTbl.h"
/* Added by h00313353 for Iteration 13, 2015-4-13, end */



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_MAIN_C
#define     STA_WARNING_PRINT   PS_LOG_LEVEL_WARNING

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
extern STATUS_CONTEXT_STRU                     g_StatusContext;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/


VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;

    /* �ػ�ʱ��Ҫ�ж��Ƿ���Ҫ��ֹ��������,����ʱ����Ҫ�ж� */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhModeSet->PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;

    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)pstMsg;

    /* �ػ�ʱ��Ҫ�ж��Ƿ���Ҫ��ֹ��������,����ʱ����Ҫ�ж� */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhoneModeSetReq->stPhoneModePara.PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}




VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    /* Modified by l00301449 for Iteration 13, 2015-04-07, begin */
    switch (g_StatusContext.ulFsmState)
    {
        case STA_FSM_NULL:
        case STA_FSM_STOP:
            TAF_MMA_SetSyscfg_PowerOffStatus(pstRcvMsg);
            break;

        case STA_FSM_PLMN_RESEL:
            /* �����6F15�������Զ��������·�SYSCFG��
                  �����AT�����ģ���AT��֤���д����˴����账�� */
            if (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == TAF_MMA_GetAutoPlmnSelUser())
            {
                /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
                TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

                /* ����SYS CFG״̬�� */
                TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            }
            else
            {
                TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgSetReq_Main: wrong state!");
            }

            break;

        case STA_FSM_ENABLE:
            /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

            /* ����SYS CFG״̬�� */
            TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            break;


        default:
            TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

            break;
    }
    /* Modified by l00301449 for Iteration 13, 2015-04-08, end */

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PLMN_LIST_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
    if (NULL == pstPlmnListCnfPara)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_LIST_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_LIST_REQ))
    {
        /* ֱ�ӻظ�plmn listʧ�� */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
         /* ֱ�ӻظ�plmn listʧ�� */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_LIST_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        /* ֱ�ӻظ�plmn listʧ�� */
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* ������Ƿֶ��ϱ��е��״β�ѯ����ֱ�ӵ��û����е������ϱ� */
    if (0 != pstPlmnListCtrl->usCurrIndex)
    {
        Sta_PlmnListEventReport();

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    /* ����ԭ�е�plmn list���� */
    MMA_PhonePlmnList();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }


    /* �����ǰΪCLģʽ����ȴ�CDMA�����ػ� */
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_TRUE;
    }



    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstPhoneModeRslt    = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx           = VOS_NULL_PTR;

    pstPhoneModeRslt = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();

    if (TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC == pstPhoneModeRslt->enRslt)
    {
        /*����ʹ��״̬������״̬��־��*/
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    }
    else
    {
        /* ��ʼ��ȫ�ֱ��� */
        TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

        TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

        TAF_SDC_InitLcConfigPara(&(pstSdcCtx->stMsCfgInfo.stMsCapInfo.stLcConfigPara));

        g_StatusContext.ulFsmState = STA_FSM_NULL;
    }

    return VOS_TRUE;
}

/* Added by h00313353 for Iteration 13, 2015-5-5, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSysCfgRsltInd_Main
 ��������  : �յ�MMA��SysCfg״̬���˳���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��5��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode = TAF_SDC_SYS_MODE_BUTT;
    enSubMode = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_E_UTRAN,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_1X_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_CDMA_1X,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_HRPD_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_EVDO,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }
    }

#endif

    /* �˳�SYSCFG״̬����Ǩ�Ƶ�ǰL1״̬��idle״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_IDLE);

    return VOS_TRUE;
}

/* Added by h00313353 for Iteration 13, 2015-5-5, end */

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����SYS CFG״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ڲ���״̬�ı���Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ڲ���״̬�ı���Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstDetachReqMsg;

    pstDetachReqMsg                     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;
    /* Deleted by h00313353 for Iteration 13, 2015-4-13, begin */
    /* Deleted by h00313353 for Iteration 13, 2015-4-13, end */

    /* Added by h00313353 for Iteration 13, 2015-4-13, begin */
    /* ENABLE��RESTART״̬�������DETACH */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvDetachReq_Main():FSM state not in Enabled or Restart!");

        return VOS_TRUE;
    }

    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����System Config״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
    /* Added by h00313353 for Iteration 13, 2015-4-13, end */

    return VOS_TRUE;
}



/* Modified by l00301449 for Iteration 13, 2015-04-11, begin */

VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ENABLE����refresh�������Զ�����������attach */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)pstMsg)->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PHONE_MSG_UNMATCH);

        return VOS_TRUE;
    }
    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����SYS CFG״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-4 end */

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_IsRefreshTrigger_Main(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* refresh�������Զ����� */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    /* refresh������SYSCFG*/
    /* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, begin */
    /* �����SYSCFG���̣���SYSCFG״̬���д���abort���˴�ɾ�� */
    /* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, end */

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_ProcImsSwitchOff_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* �����ǰ����IMSҵ������У�������ر�IMSҵ�� */
    if (VOS_TRUE == TAF_SDC_IsImsSrvExist())
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_SERVICE_EXIST);

        return VOS_TRUE;
    }

    /* ���������ѡ�����ó���PS_ONLY��������ر�IMSҵ�� */
    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == TAF_SDC_GetVoiceDomain())
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_VOICE_DOMAIN_PS_ONLY);

        return VOS_TRUE;
    }

    /* ����IMSҵ������������NV */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }

    /* ��ǰIMSЭ��ջ�Ѿ��رջ��ߴ��ڷ���ģʽ״̬��
       ����Ҫ��IMSA���ر�����ֻ����NV���� */
    if ((TAF_SDC_IMS_SWITCH_STATE_OFF == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_ProcImsSwitchOn_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* ����NV���ڸ�IMSA����start req��ǰ�棬IMSA�յ�start req���NV���Ҫ�����µ�NVֵ */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_TRUE))
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);

        return VOS_TRUE;
    }

    /* ��ǰIMSЭ��ջ�Ѿ��������ߴ��ڷ���ģʽ״̬��
       ����Ҫ��IMSA����������ֻ����NV����  */
    if ((TAF_SDC_IMS_SWITCH_STATE_ON == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstSetReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult   = VOS_TRUE;
    pstSetReq  = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)pstMsg;


    /* �����ǰ������AT�������ڴ�����ֱ�Ӹ��ϲ�ظ�ʧ�ܣ�
       �������������������IMS���أ�������ظ���ʱ����Ҫ���� */
    if ((STA_FSM_ENABLE != g_StatusContext.ulFsmState)
     && (STA_FSM_NULL   != g_StatusContext.ulFsmState)
     && (STA_FSM_STOP   != g_StatusContext.ulFsmState))
    {
        /* ���ǿ������ģ�����AT���������� */
        if (VOS_FALSE == TAF_MMA_IsRefreshTrigger_Main())
        {
            /* ���ϲ�ظ�ʧ�� */
            TAF_MMA_SndImsSwitchSetCnf(&pstSetReq->stCtrl,
                                       TAF_MMA_APP_OPER_RESULT_FAILURE,
                                       TAF_ERR_UNSPECIFIED_ERROR);

            return VOS_TRUE;
        }
    }

    /* �ر�IMSҵ�� */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_OFF == pstSetReq->enImsSwitch)
    {
        ulResult = TAF_MMA_ProcImsSwitchOff_Main(pstSetReq);
    }
    else
    {
        ulResult = TAF_MMA_ProcImsSwitchOn_Main(pstSetReq);
    }

    /* ����VOS_FALSE��������Ҫ������IMS_SWITCH״̬������ */
    if ( VOS_FALSE == ulResult )
    {
        /* ����IMS SWITCH״̬�� */
        TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_IMS_SWITCH);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʱû�д���ֻ��Ϊ�˺����Ļ��洦���Ժ��������Ҫ��������������Ӵ��� */

    return VOS_TRUE;
}
#endif
VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT32                          ulRet;
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnSpecialSelMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnSpecialSelMsg = (TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)pstMsg;

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_SPEC_SEL_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ))
    {
        /* ֱ�ӻظ�SEL����ʧ�� */
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstPlmnSpecialSelMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, ucCtxIndex);

    /* ��CLģʽʱ�򣬲�֧��AT����ѡ������,ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ת���û�����PLMN�ַ�ΪPLMN ID */
    ulRet = MMA_FormatPlmnStr2PlmnId(&stPlmn,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucFormatType,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.usOperNameLen,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucOperName);
    if( VOS_TRUE == ulRet)
    {
        MMA_PlmnId2NasStyle(&stPlmn);

        /* ͨ��ԭ�е�TAF_PH_EVT_PLMN_SEL_CNF��Ϣ��ָ���ѽ�����͸�AT */
        MMA_PhonePlmnUserSel(pstPlmnSpecialSelMsg->stCtrl.usClientId, pstPlmnSpecialSelMsg->stCtrl.ucOpId, stPlmn, pstPlmnSpecialSelMsg->stPlmnUserSel.enAccessMode, TAF_PLMN_RESELETION_MANUAL);
    }
    else
    {
        /*������*/
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_PARA_ERROR);
    }

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucError;
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU   *pstPlmnReselMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnReselMsg = (TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)pstMsg;

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ))
    {
        /* ֱ�ӻظ�RESEL����ʧ�� */
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstPlmnReselMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, ucCtxIndex);

    ucError = TAF_ERR_NO_ERROR;
    ucError = MMA_CheckUsimStatusForPlmnSel();
    if(TAF_ERR_NO_ERROR != ucError)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvPlmnAutoReselReq_Main():WARNING:UsimStatus Error!");
        /*������*/
        TAF_MMA_ProcPlmnAutoReselCnf(ucError);
        return VOS_TRUE;
    }

    /* ��CLģʽʱ�򣬲�֧��AT����ѡ������,ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    Sta_PlmnReselectAuto(pstPlmnReselMsg->stCtrl.ucOpId);

    return VOS_TRUE;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


