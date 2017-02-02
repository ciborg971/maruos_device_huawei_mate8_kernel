/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcSpmMsg.c
  Description     : ��C�ļ�ʵ��Spm��Ϣ�����Spm��Ϣ����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaCallManagement.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaImsAdaption.h"

#include "ImsaProcImsCallMsg.h"

/* xiongxianghui00253310 for PC-LINT 20140210 begin */
#include "ImsaProcUssdMsg.h"
/* xiongxianghui00253310 for PC-LINT 20140210 end */


/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCSPMMSG_C
#define    THIS_NAS_FILE_ID   NAS_FILE_ID_IMSAPROCSPMMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

extern VOS_UINT32 IMSA_CallSendSpmClprCnf
(
    const IMSA_SPM_CALL_GET_CLPR_CNF_STRU  *pstMsg
);

IMSA_SPM_CALL_MSG_ACT_STRU      g_stImsaSpmCallMsgActTbl[]=
{
    {ID_SPM_IMSA_CALL_ORIG_REQ,                     IMSA_CallProcSpmMsgOrig},
    {ID_SPM_IMSA_CALL_SUPS_CMD_REQ,                 IMSA_CallProcSpmMsgSups},
    {ID_SPM_IMSA_CALL_START_DTMF_REQ,               IMSA_CallProcSpmMsgStartDtmf},
    {ID_SPM_IMSA_CALL_STOP_DTMF_REQ,                IMSA_CallProcSpmMsgStopDtmf},
    {ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ,            IMSA_CallProcSpmMsgGetInfo},
    {ID_SPM_IMSA_CALL_GET_CLPR_REQ,                 IMSA_CallProcSpmMsgGetClprInfo},
    {ID_SPM_IMSA_CALL_MODIFY_REQ,                   IMSA_CallProcSpmMsgModifyReq},
    {ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ,     IMSA_CallProcSpmMsgAnswerRemoteModifyReq},
    {ID_SPM_IMSA_PROCESS_USSD_REQ,                  IMSA_SsProcSpmMsgProcessUssdReq},
    {ID_SPM_IMSA_RELEASE_REQ,                       IMSA_SsProcSpmMsgReleaseReq},
    {ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ,          IMSA_CallProcSpmMsgInviteNewPtpt},
    {ID_SPM_IMSA_CALL_ECONF_DIAL_REQ,               IMSA_CallProcSpmMsgEconfDial},
    {ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ,          IMSA_CallProcSpmMsgEconfAddUser},
    {ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ,    IMSA_CallProcSpmMsgGetEconfInfo}
};
VOS_UINT32        g_ulImsaSpmCallMsgActTblLen = sizeof(g_stImsaSpmCallMsgActTbl)
                                                / sizeof(IMSA_SPM_CALL_MSG_ACT_STRU);


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/

VOS_UINT32 IMSA_CallSendSpmClprCnf
(
    const IMSA_SPM_CALL_GET_CLPR_CNF_STRU  *pstMsg
)
{
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU *pstSpmCallMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmClprCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmClprCnf_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmCallMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_GET_CLPR_CNF_STRU));
    if (VOS_NULL_PTR == pstSpmCallMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmClprCnf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmClprCnf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ������Ϣ���� */
    IMSA_MEM_CPY(IMSA_GET_MSG_ENTITY(pstSpmCallMsg), IMSA_GET_MSG_ENTITY(pstMsg), IMSA_GET_MSG_LENGTH(pstSpmCallMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmCallMsg, ID_IMSA_SPM_CALL_GET_CLPR_CNF);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmCallMsg);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallProcSpmMsgGetClprInfo
(
    VOS_VOID     *pMsg
)
{
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU     stGetClprCnf    = {0};
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult        = VOS_FALSE;
    SPM_IMSA_CALL_GET_CLPR_REQ_STRU     *pstAppMsg      = VOS_NULL_PTR;

    pstAppMsg = (SPM_IMSA_CALL_GET_CLPR_REQ_STRU*)pMsg;

    IMSA_MEM_SET(&stGetClprCnf, 0x00, sizeof(IMSA_SPM_CALL_GET_CLPR_CNF_STRU));

    /* ����MN_CALL_EVT_CLPR_GET_CNF��Ϣ */
    stGetClprCnf.usClientId     = pstAppMsg->usClientId;
    stGetClprCnf.ulRet          = TAF_ERR_ERROR;

    /* ��������CALLID�Ƿ����,����Ϊ���� */
    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pstAppMsg->callId);
    if (VOS_NULL_PTR != pstCallEntity)
    {
        IMSA_CallReadCallEntityRedirectInfo(pstCallEntity, &stGetClprCnf);
    }

    ulResult = IMSA_CallSendSpmClprCnf(&stGetClprCnf);

    return ulResult;
}


VOS_UINT32 IMSA_CallSendSpmClccInfoCnf
(
    const IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU *pstMsg
)
{
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU *pstSpmCallMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmClccInfoCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmClccInfoCnf_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmCallMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU));
    if (VOS_NULL_PTR == pstSpmCallMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmClccInfoCnf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmClccInfoCnf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ������Ϣ���� */
    IMSA_MEM_CPY(IMSA_GET_MSG_ENTITY(pstSpmCallMsg), IMSA_GET_MSG_ENTITY(pstMsg), IMSA_GET_MSG_LENGTH(pstSpmCallMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmCallMsg, ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmCallMsg);

    return VOS_TRUE;
}

VOS_UINT32 IMSA_CallSendSpmGetEconfInfoCnf
(
    const IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU *pstMsg
)
{
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU *pstSpmEconfInfoMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmGetEconfInfoCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmGetEconfInfoCnf_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmEconfInfoMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU));
    if (VOS_NULL_PTR == pstSpmEconfInfoMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmGetEconfInfoCnf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmGetEconfInfoCnf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ������Ϣ���� */
    IMSA_MEM_CPY(IMSA_GET_MSG_ENTITY(pstSpmEconfInfoMsg), IMSA_GET_MSG_ENTITY(pstMsg), IMSA_GET_MSG_LENGTH(pstSpmEconfInfoMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmEconfInfoMsg, ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmEconfInfoMsg);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallProcSpmMsgGetInfo
(
    VOS_VOID *pMsg
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU stQryCnf = {0};
    VOS_UINT32 ulCount = 0;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulResult = VOS_FALSE;
    SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU *pstAppMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgGetInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgGetInfo_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU *)pMsg;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if ((IMSA_CALL_STATUS_IDLE == pstCallCtx->astCallEntity[i].enStatus) &&
                (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir))
            {
                continue;
            }
            IMSA_CallEntity2SpmCallInfoParam(&pstCallCtx->astCallEntity[i], &stQryCnf.astCallInfo[ulCount]);
            ulCount++;
        }
    }

    stQryCnf.ucNumOfCalls = (VOS_UINT8)ulCount;
    stQryCnf.usClientId = pstAppMsg->usClientId;
    stQryCnf.enReqType = pstAppMsg->enReqType;


    ulResult = IMSA_CallSendSpmClccInfoCnf(&stQryCnf);

    return ulResult;
}

VOS_UINT32 IMSA_SpmGetCallInfo(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU *pstCallInfo)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 ulCount = 0;
    VOS_UINT32 i = 0;

    IMSA_INFO_LOG("IMSA_SpmGetCallInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SpmGetCallInfo_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstCallInfo)
    {
        IMSA_ERR_LOG("IMSA_SpmGetCallInfo: pstCallInfo is null");
        TLPS_PRINT2LAYER_ERROR(IMSA_SpmGetCallInfo_ENUM, LNAS_NULL_PTR);
        return IMSA_FAIL;
    }

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            IMSA_CallEntity2SpmCallInfoParam(&pstCallCtx->astCallEntity[i], &(pstCallInfo->astCallInfo[ulCount]));
            ulCount++;
        }
    }

    pstCallInfo->ucNumOfCalls = (VOS_UINT8)ulCount;
    return IMSA_SUCC;
}


VOS_UINT32 IMSA_CallSendSpmStartDtmfCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_START_DTMF_CNF_STRU *pstStartDtmfCnf = VOS_NULL_PTR;

    (VOS_VOID)ucCallId;

    IMSA_INFO_LOG("IMSA_CallSendSpmStartDtmfCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmStartDtmfCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStartDtmfCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_START_DTMF_CNF_STRU));
    if (VOS_NULL_PTR == pstStartDtmfCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmStartDtmfCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmStartDtmfCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstStartDtmfCnf), 0, IMSA_GET_MSG_LENGTH(pstStartDtmfCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstStartDtmfCnf, ID_IMSA_SPM_CALL_START_DTMF_CNF);

    pstStartDtmfCnf->usClientId = usClientId;
    pstStartDtmfCnf->ucOpId     = ucOpId;
    pstStartDtmfCnf->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStartDtmfCnf);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallSendSpmStopDtmfCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_STOP_DTMF_CNF_STRU   *pstStopDtmfCnf = VOS_NULL_PTR;

    (VOS_VOID)ucCallId;

    IMSA_INFO_LOG("IMSA_CallSendSpmStopDtmfCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmStartDtmfCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStopDtmfCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_STOP_DTMF_CNF_STRU));
    if (VOS_NULL_PTR == pstStopDtmfCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmStopDtmfCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmStartDtmfCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstStopDtmfCnf), 0, IMSA_GET_MSG_LENGTH(pstStopDtmfCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstStopDtmfCnf, ID_IMSA_SPM_CALL_STOP_DTMF_CNF);

    pstStopDtmfCnf->usClientId = usClientId;
    pstStopDtmfCnf->ucOpId     = ucOpId;
    pstStopDtmfCnf->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStopDtmfCnf);

    return VOS_TRUE;
}



VOS_UINT32 IMSA_CallProcSpmMsgStartDtmf
(
    VOS_VOID* pMsg
)
{
    TAF_CALL_DTMF_PARAM_STRU            stStartDtmfParam    = {0};
    VOS_UINT32                          ulResult            = VOS_FALSE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    SPM_IMSA_CALL_START_DTMF_REQ_STRU           *pstAppMsg  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgStartDtmf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgStartDtmf_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_START_DTMF_REQ_STRU*)pMsg;

    IMSA_MEM_CPY(   &stStartDtmfParam,
                    &pstAppMsg->stDtmf,
                    sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* DTMF��Ϣ�Ϸ����ж� */
    if ( (VOS_OK != IMSA_CallCheckDtmfKey(&stStartDtmfParam.cKey))
      || (stStartDtmfParam.usOnLength < IMSA_DTMF_MIN_ONLENGTH) )
    {
        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_INVALID_PARAMETER);
        return VOS_TRUE;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���ٻ�ȡ���п��Է���DTMF�ĺ���ID */
    ulResult    = IMSA_CallCheckUserDtmfCallId(stStartDtmfParam.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    ulResult);
        return VOS_TRUE;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    if (IMSA_CallGetDtmfState() >= IMSA_CALL_DTMF_STATE_BUTT)
    {
        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_STATE_ERROR);
        return VOS_TRUE;
    }

    /* DTMF���ڷǿ���״̬���򻺴��DTMF */
    if (IMSA_CallGetDtmfState() != IMSA_CALL_DTMF_IDLE)
    {
        ulResult = IMSA_CallSaveDtmfInfo(pstAppMsg->stDtmf.CallId,
                                         pstAppMsg->stDtmf.cKey,
                                         pstAppMsg->stDtmf.usOnLength,
                                         pstAppMsg->usClientId,
                                         pstAppMsg->ucOpId);

        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(pstAppMsg->usClientId,
                                                  pstAppMsg->ucOpId,
                                                  pstAppMsg->stDtmf.CallId,
                                                  ulResult);
        return VOS_TRUE;
    }

    /* DTMF��ǰ���ڿ���̬�����͵�IMSЭ��ջ */
    if (VOS_TRUE != IMSA_CallSendImsMsgStartDtmf(   pstAppMsg->stDtmf.CallId,
                                                    stStartDtmfParam.cKey,
                                                    (VOS_UINT32)stStartDtmfParam.usOnLength))
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgStartDtmf: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgStartDtmf_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_IMSA_ERROR);

        return VOS_TRUE;
    }

    /* ���ͳɹ�������DTMF״̬ */
    IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);

    IMSA_CallFillCurrentDtmfInfo(   pstAppMsg->stDtmf.CallId,
                                    stStartDtmfParam.cKey,
                                    stStartDtmfParam.usOnLength,
                                    pstAppMsg->usClientId,
                                    pstAppMsg->ucOpId);

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_START_CNF);

    (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstAppMsg->usClientId,
                                                pstAppMsg->ucOpId,
                                                pstAppMsg->stDtmf.CallId,
                                                TAF_CS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallProcSpmMsgStopDtmf
(
    VOS_VOID* pMsg
)
{
    VOS_UINT32                          ulResult            = VOS_FALSE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    TAF_CALL_DTMF_PARAM_STRU            stStopDtmfParam     = {0};
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState         = IMSA_CALL_DTMF_STATE_BUTT;
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU         *pstAppMsg     = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgStopDtmf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgStopDtmf_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_STOP_DTMF_REQ_STRU*)pMsg;

    IMSA_MEM_CPY(   &stStopDtmfParam,
                    &pstAppMsg->stDtmf,
                    sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* STOP_DTMF����ʱ��OnLengthֵ��Ϊ0 */
    if (0 != stStopDtmfParam.usOnLength)
    {
        (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_INVALID_PARAMETER);
        return VOS_TRUE;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    enDtmfState = IMSA_CallGetDtmfState();
    if ( (IMSA_CALL_DTMF_STATE_BUTT <= enDtmfState)
      || (IMSA_CALL_DTMF_IDLE == enDtmfState) )
    {
        (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_STATE_ERROR);
        return VOS_TRUE;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���Լ��û�����ĺ���ID�Ƿ���Է���DTMF */
    ulResult    = IMSA_CallCheckUserDtmfCallId(stStopDtmfParam.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    ulResult);
        return VOS_TRUE;
    }

    /* �����ǰû�л����Ҵ��ڵȴ���ʱ����ʱ״̬����ͣ��ʱ��������STOP_DTMF�����򻺴� */
    if ((IMSA_CALL_DTMF_WAIT_TIME_OUT == enDtmfState)
        && (0 == IMSA_CallGetDtmfCnt()))
    {
        /* ͣDTMF duration��ʱ�� */
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer);

        if (VOS_TRUE != IMSA_CallSendImsMsgStopDtmf(pstAppMsg->stDtmf.CallId,
                                                    stStopDtmfParam.cKey))
        {
            IMSA_ERR_LOG("IMSA_CallProcSpmMsgStopDtmf: error occurs, should return failure to SPM");
            TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgStopDtmf_ENUM, LNAS_ERROR);

            (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstAppMsg->usClientId,
                                                        pstAppMsg->ucOpId,
                                                        pstAppMsg->stDtmf.CallId,
                                                        TAF_CS_CAUSE_IMSA_ERROR);
            return VOS_TRUE;
        }

        /* ���ͳɹ�������DTMF״̬ */
        IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);

        IMSA_CallFillCurrentDtmfInfo(   pstAppMsg->stDtmf.CallId,
                                        stStopDtmfParam.cKey,
                                        stStopDtmfParam.usOnLength,
                                        pstAppMsg->usClientId,
                                        pstAppMsg->ucOpId);

        IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_STOP_CNF);

        (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stDtmf.CallId,
                                                    TAF_CS_CAUSE_SUCCESS);
        return VOS_TRUE;
    }

    /* ��ǰ���ܷ���STOP_DTMF�����򻺴� */
    ulResult = IMSA_CallSaveDtmfInfo(pstAppMsg->stDtmf.CallId,
                                     pstAppMsg->stDtmf.cKey,
                                     pstAppMsg->stDtmf.usOnLength,
                                     pstAppMsg->usClientId,
                                     pstAppMsg->ucOpId);

    (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stDtmf.CallId,
                                             ulResult);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_CallSendSpmSupsCnfMsg(VOS_UINT16 usClientId,
                                      VOS_UINT32 ulOpId,
                                      VOS_UINT32 ulCallId,
                                      TAF_CS_CAUSE_ENUM_UINT32 ulResult)
{
    IMSA_INFO_LOG("IMSA_CallSendSpmSupsCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmSupsCnfMsg_ENUM, LNAS_ENTRY);

    return IMSA_CallSendSpmEvtAndCallInfo(usClientId,
                                          ulOpId,
                                          ulCallId,
                                          MN_CALL_EVT_SUPS_CMD_CNF,
                                          ulResult);
}


VOS_UINT32 IMSA_CallProcSpmMsgSups(VOS_VOID* pMsg)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    VOS_UINT32 ulCallId = 0;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSups is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSups_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *)pMsg;


    ulCallId = pstAppMsg->stCallMgmtCmd.callId;

    IMSA_INFO_LOG1("IMSA_CallProcSpmMsgSups", pstAppMsg->stCallMgmtCmd.enCallSupsCmd);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcSpmMsgSups_ENUM, LNAS_RCV_MSG, pstAppMsg->stCallMgmtCmd.enCallSupsCmd);

    switch (pstAppMsg->stCallMgmtCmd.enCallSupsCmd)
    {
        /* CHLD=0, Releases all held calls or sets User Determined User Busy (UDUB) for a waiting call */
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            ulResult = IMSA_CallProcSpmMsgSupsRelHeldOrUdub(ulCallId, pstAppMsg);
            break;
        /* CHLD=1, Releases all active calls (if any exist) and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            ulResult = IMSA_CallProcSpmMsgSupsRelActAcptOth(ulCallId, pstAppMsg);
            break;
        /* CHLD=1x, Releases a specific active call X*/
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            ulResult = IMSA_CallProcSpmMsgSupsRelCallX(ulCallId, pstAppMsg);
            break;
        /* ATH, Release all calls */
        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            ulResult = IMSA_CallProcSpmMsgSupsRelAllCall(ulCallId, pstAppMsg);
            break;
        /* CHLD=2, Places all active calls (if any exist) on hold and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            ulResult = IMSA_CallProcSpmMsgSupsHoldActAcptOth(ulCallId, pstAppMsg);
            break;
        /* CHLD=2x, Places all active calls on hold except call X with which communication shall be supported */
        case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
            ulResult = IMSA_CallProcSpmMsgSupsHoldAllExpectX(ulCallId, pstAppMsg);
            break;
        /* CHLD=3, Adds a held call to the conversation */
        case MN_CALL_SUPS_CMD_BUILD_MPTY:
            ulResult = IMSA_CallProcSpmMsgSupsBuidMpty(ulCallId, pstAppMsg);
            break;
        /* reject unsupported SPM command */
        case MN_CALL_SUPS_CMD_ECONF_REL_USER:
            ulResult = IMSA_CallProcSpmMsgSupsEconfRelUser(ulCallId, pstAppMsg);
            break;
        case MN_CALL_SUPS_CMD_ECONF_MERGE_CALL:
            ulResult = IMSA_CallProcSpmMsgSupsEconfRelUser(ulCallId, pstAppMsg);
            break;
        default:
            ulResult = VOS_FALSE;
            IMSA_ERR_LOG("IMSA_CallProcSpmMsgSups: not support sups message");
            TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSups_ENUM, LNAS_MSG_INVALID);

            (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 TAF_CS_CAUSE_IMSA_NOT_SUPPORTED_CMD);
    }

    return ulResult;
}


VOS_UINT32 IMSA_CallSendSpmOrigCnfMsg(VOS_UINT16 usClientId,
                                      VOS_UINT32 ulOpId,
                                      VOS_UINT32 ulCallId,
                                      TAF_CS_CAUSE_ENUM_UINT32 ulResult)
{
    IMSA_INFO_LOG("IMSA_CallSendSpmOrigCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmOrigCnfMsg_ENUM, LNAS_ENTRY);

    return IMSA_CallSendSpmEvtAndCallInfo(usClientId,
                                          ulOpId,
                                          ulCallId,
                                          MN_CALL_EVT_CALL_ORIG_CNF,
                                          ulResult);
}

VOS_UINT32 IMSA_CallSendSpmEconfDialCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU *pstEconfDialCnf = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmEconfDialCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmEconfDialCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEconfDialCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU));
    if (VOS_NULL_PTR == pstEconfDialCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmEconfDialCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmEconfDialCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstEconfDialCnf), 0, IMSA_GET_MSG_LENGTH(pstEconfDialCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstEconfDialCnf, ID_IMSA_SPM_CALL_ECONF_DIAL_CNF);

    pstEconfDialCnf->usClientId = usClientId;
    pstEconfDialCnf->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstEconfDialCnf->enCause    = ulResult;
    pstEconfDialCnf->ucCallId   = (VOS_UINT8)ulCallId;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstEconfDialCnf);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallSendSpmEconfAddUserCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU *pstEconfAddUserCnf = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmEconfAddUserCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmEconfAddUserCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEconfAddUserCnf= (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU));
    if (VOS_NULL_PTR == pstEconfAddUserCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmEconfAddUserCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmEconfAddUserCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstEconfAddUserCnf), 0, IMSA_GET_MSG_LENGTH(pstEconfAddUserCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstEconfAddUserCnf, ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF);

    pstEconfAddUserCnf->usClientId = usClientId;
    pstEconfAddUserCnf->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstEconfAddUserCnf->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstEconfAddUserCnf);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallProcSpmMsgOrig(VOS_VOID* pMsg)
{
    VOS_UINT32                          ulCheckRet      = 0;
    VOS_UINT32                          ulResult        = 0;
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam    = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType       = IMSA_EMC_CALL_TYPE_BUTT;
    SPM_IMSA_CALL_ORIG_REQ_STRU         *pstAppMsg      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgOrig is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgOrig_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_ORIG_REQ_STRU *)pMsg;

    pstOrigParam = &pstAppMsg->stOrig;

    /* Ŀǰֻ֧���������кͽ������к���Ƶ������������ */
    if (VOS_FALSE == IMSA_CallTypeAvailabilityCheck(pstOrigParam->enCallType))
    {
        (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             IMSA_CALL_INVALID_ID,
                                             TAF_CS_CAUSE_IMSA_NOT_SUPPORTED_CALL_TYPE);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE, VOS_NULL_PTR);
        /* ��ʱ�ȱ����ɵ�CHR���Ȳ�Ʒ�߿������µ�CHR���ٽ��ɵ�ɾ�� */
        IMSA_CallFailErrRecord( pstOrigParam->enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return VOS_FALSE;
    }

    if (VOS_FALSE == IMSA_CallCheckIsAllowNewOrig())
    {
        (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             IMSA_CALL_INVALID_ID,
                                             TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( pstOrigParam->enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return VOS_FALSE;
    }

    /* ���к��п����Լ�� */
    ulCheckRet = IMSA_CallAvailabilityCheck(pstOrigParam->enCallType, &enEmcType);

    IMSA_INFO_LOG1("IMSA_CallProcSpmMsgOrig: IMSA_CallAvailabilityCheck result", ulCheckRet);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcSpmMsgOrig_ENUM, 1, ulCheckRet);

    /* ��������Ϊ���Լ���������У�������Ҫ�ȷ������ע�ᣬ���ȷ������ʵ�壬��SPM�ظ�ORIG_CNF��
    ͬʱ��SPM����ORIG�¼�����ΪSPM��Ҫͨ�����¼�ȥ����callid����ֹ��IMSA��δ�յ�IMS��DIAL��Ϣʱ���յ�
    �û��ĹҶ�������IMSA���ϱ�ORIG�¼�ǰ��ֱ�ӱ�RELEASE�¼���SPM����û��callid���޷����� */
    if ((IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE == ulCheckRet) ||
        (IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED == ulCheckRet))
    {

        pstCallEntity = IMSA_CallEntityAlloc();
        if (VOS_NULL_PTR != pstCallEntity)
        {
            /* �����Ƿ��Ѿ���CS���Թ��ı�ʶ */
            pstCallEntity->bitOpRetryCsCall = pstOrigParam->ucCsCallRetryFlg;

            /* �������ģʽ */
            pstCallEntity->enMode = pstOrigParam->enCallMode;

            /* ������������� */
            pstCallEntity->enEmcType = enEmcType;

            /* ����CLIENT ID��OPID */
            pstCallEntity->usClientId = pstAppMsg->usClientId;
            pstCallEntity->ulOpId = pstAppMsg->ucOpId;

            /* ����CALL���� */
            pstCallEntity->enType = (IMSA_CALL_TYPE_ENUM_UINT8)pstAppMsg->stOrig.enCallType;

            /* ���±��к��� */
            IMSA_CallEntityUpdateCalledNumberByBcd(&(pstAppMsg->stOrig.stDialNumber), &pstCallEntity->stCalledNumber);


            /* ��SPM�ظ�ORIG_CNF */
            (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstCallEntity->ucSpmcallId,
                                                 TAF_CS_CAUSE_SUCCESS);

            /* ��SPM�ظ�ORIG�¼� */
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_ORIG);
        }
        else
        {
            /* ������Դʧ�ܣ��ܾ��ú������� */
            (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 IMSA_CALL_INVALID_ID,
                                                 TAF_CS_CAUSE_IMSA_ALLOC_ENTITY_FAIL);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, VOS_NULL_PTR);
            #endif

            return VOS_TRUE;
        }
    }
    else
    {
        /* ��Ƶ���б��գ�����Ƶ�����л�Ϊ�������� */
        if (MN_CALL_TYPE_VIDEO == pstAppMsg->stOrig.enCallType)
        {
            (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstAppMsg->usClientId,
                                                               pstAppMsg->ucOpId,
                                                               IMSA_CALL_INVALID_ID,
                                                               MN_CALL_TYPE_VIDEO,
                                                               MN_CALL_TYPE_VOICE,
                                                               IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);
        }

        (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             IMSA_CALL_INVALID_ID,
                                             TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE);

        #if (FEATURE_ON == FEATURE_PTM)
        if (VOS_FALSE == IMSA_CallCheckIsAllowNewOrig())
        {
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL, VOS_NULL_PTR);
        }
        else
        {
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, VOS_NULL_PTR);
        }
        #endif
        return VOS_TRUE;
    }

    if(ulCheckRet == IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE)
    {
        /* Send IMS command */
        ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, pstAppMsg);
        if (VOS_TRUE == ulResult)
        {
            /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
            IMSA_MEM_CPY(   &pstCallEntity->stSpmMsg,
                            &pstCallCtx->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU));

            /* ����������ʱ�� */
            IMSA_StartTimer(&pstCallCtx->stProctectTimer);

            /* �����ز����ʱ����ʱ�� */
            pstCallCtx->stRedialMaxTimer.ulTimerLen = IMSA_GetImsRedialCfgAddress()->ulCallRedialMaxTime;
            pstCallCtx->stRedialMaxTimer.usPara = pstCallEntity->ucCallEntityIndex;
            IMSA_StartTimer(&pstCallCtx->stRedialMaxTimer);
            IMSA_INFO_LOG1("Start redial max timer tick:", PS_GET_TICK());
            TLPS_PRINT2LAYER_INFO1(IMSA_CallProcSpmMsgOrig_ENUM, IMSA_TICK, PS_GET_TICK());
            IMSA_StartTcallTimer(pstCallEntity);
        }
        else
        {
            /* ֪ͨSPM release�¼� */
            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_ERROR);
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, VOS_NULL_PTR);
            #endif
        }
    }
    else/* ���ȷ��������Ҫ����������������ɹ����ٴ�������Ϣ */
    {
        IMSA_CallSpmOrigReqMsgSave(pstAppMsg);
        IMSA_StartTcallTimer(pstCallEntity);
    }

    return VOS_TRUE;
}

VOS_UINT32 IMSA_CallProcSpmMsgEconfDial(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulCheckRet      = 0;
    VOS_UINT32                          ulResult        = 0;
    TAF_CALL_ECONF_DIAL_REQ_STRU        *pstDialParam    = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType       = IMSA_EMC_CALL_TYPE_BUTT;
    VOS_UINT8                           i = 0;
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU *pstAppMsg        = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgEconfDial is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgEconfDial_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU*)pMsg;

    pstDialParam = &pstAppMsg->stDialReq;

    /* Ŀǰֻ֧���������͵���ǿ�෽ͨ�� */
    if (MN_CALL_TYPE_VOICE != pstDialParam->enCallType)
    {
        (VOS_VOID)IMSA_CallSendSpmEconfDialCnfMsg(pstAppMsg->usClientId,
                                                  pstAppMsg->ucOpId,
                                                  IMSA_CALL_INVALID_ID,
                                                  TAF_CS_CAUSE_IMSA_NOT_SUPPORTED_CALL_TYPE);

        return VOS_FALSE;
    }

    /* ���к��п����Լ�� */
    ulCheckRet = IMSA_CallAvailabilityCheck(pstDialParam->enCallType, &enEmcType);

    IMSA_INFO_LOG1("IMSA_CallProcSpmMsgEconfDial: IMSA_CallAvailabilityCheck result", ulCheckRet);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcSpmMsgEconfDial_ENUM, 1, ulCheckRet);

    if ((IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE == ulCheckRet) &&
        (VOS_TRUE == IMSA_CallCheckIsAllowNewOrig()))
    {

        pstCallEntity = IMSA_CallEntityAlloc();
        if (VOS_NULL_PTR != pstCallEntity)
        {
            /* �������ģʽ */
            pstCallEntity->enMode = pstDialParam->enCallMode;

            /* ������������� */
            pstCallEntity->enEmcType = enEmcType;

            /* ������ǿ�෽ͨ���ı�־λ */
            pstCallEntity->ucIsEconfFlag = VOS_TRUE;

            /* ���¶෽ͨ����ģʽ */
            pstCallEntity->enMpty = MN_CALL_IN_MPTY;

            /* ����CLIENT ID��OPID */
            pstCallEntity->usClientId = pstAppMsg->usClientId;
            pstCallEntity->ulOpId = pstAppMsg->ucOpId;

            pstCallEntity->enType = (IMSA_CALL_TYPE_ENUM_UINT8)pstAppMsg->stDialReq.enCallType;

            pstCallEntity->ucCurUserNum = (VOS_UINT8)pstAppMsg->stDialReq.stEconfCalllist.ulCallNum;

            /* ��������߳�Ա�б� */
            for (i = 0; i < pstCallEntity->ucCurUserNum; i++)
            {
                 IMSA_CallEntityUpdateCalledNumberByBcd(&(pstAppMsg->stDialReq.stEconfCalllist.astDialNumber[i]), &pstCallEntity->stEconfCalllist[i].stCalledNumber);

                pstCallEntity->stEconfCalllist[i].enCallState = IMSA_IMS_ECONF_CALLER_STATE_PREDIALING;
            }

            /* ��SPM�ظ�ORIG_CNF */
            (VOS_VOID)IMSA_CallSendSpmEconfDialCnfMsg(pstAppMsg->usClientId,
                                                      pstAppMsg->ucOpId,
                                                      pstCallEntity->ucSpmcallId,
                                                      TAF_CS_CAUSE_SUCCESS);

            /* ��SPM�ظ�ORIG�¼� */
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_ORIG);
        }
        else
        {
            /* ������Դʧ�ܣ��ܾ��ú������� */
            (VOS_VOID)IMSA_CallSendSpmEconfDialCnfMsg(pstAppMsg->usClientId,
                                                     pstAppMsg->ucOpId,
                                                     IMSA_CALL_INVALID_ID,
                                                     TAF_CS_CAUSE_IMSA_ALLOC_ENTITY_FAIL);
            return VOS_TRUE;
        }
    }
    else
    {
        (VOS_VOID)IMSA_CallSendSpmEconfDialCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 IMSA_CALL_INVALID_ID,
                                                 TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE);
        return VOS_TRUE;
    }

    /* Send IMS command */
    ulResult = IMSA_CallSendImsMsgCreatEconf(IMSA_CALL_INVALID_ID, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
        IMSA_MEM_CPY(   &pstCallEntity->stSpmMsg,
                        &pstCallCtx->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU));

        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

    }
    else
    {
        /* ֪ͨSPM release�¼� */
        IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_ERROR);
    }

    return VOS_TRUE;
}
VOS_UINT32 IMSA_CallProcSpmMsgEconfAddUser(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulResult        = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU *pstAppMsg   = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucCallNum       = 0;
    VOS_UINT8                           i = 0;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgEconfAddUser is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgEconfAddUser_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU*)pMsg;
    pstCallEntity = IMSA_CallEntityGetUsedByEconfFlag();

    /* �����������ǿ�෽ͨ����ֱ�ӷ���ʧ�� */
    if (VOS_NULL_PTR == pstCallEntity)
    {
        /* ��Ҫ֪ͨSPM ������������ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstAppMsg->usClientId,
                                           pstAppMsg->ucOpId,
                                           TAF_CS_CAUSE_IMSA_ERROR);
        return VOS_FALSE;
    }

    /* �ж������Ƿ񳬹�5�������������ֱ�ӷ���ʧ�� */
    if (IMSA_IMS_ECONF_CALLED_MAX_NUM < pstAppMsg->stEconfCalllist.ulCallNum)
    {
        /* ��Ҫ֪ͨSPM ������������ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstAppMsg->usClientId,
                                           pstAppMsg->ucOpId,
                                           TAF_CS_CAUSE_IMSA_ERROR);
        return VOS_FALSE;
    }

    ucCallNum = (VOS_UINT8)(pstCallEntity->ucCurUserNum + pstAppMsg->stEconfCalllist.ulCallNum);
    if (IMSA_IMS_ECONF_CALLED_MAX_NUM < ucCallNum)
    {
        /* ��Ҫ֪ͨSPM ������������ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstAppMsg->usClientId,
                                           pstAppMsg->ucOpId,
                                           TAF_CS_CAUSE_IMSA_ERROR);
        return VOS_FALSE;
    }

    /* �ں���ʵ���б��������ı��� */
    for (i = 0; i < pstAppMsg->stEconfCalllist.ulCallNum; i++)
    {
        IMSA_CallCopyRemoteAddrForm(&pstAppMsg->stEconfCalllist.astDialNumber[i],
                                     pstCallEntity->stEconfCalllist[pstCallEntity->ucCurUserNum].stCalledNumber.aucNumber);

        pstCallEntity->stEconfCalllist[pstCallEntity->ucCurUserNum].enCallState = IMSA_IMS_ECONF_CALLER_STATE_PREDIALING;

        pstCallEntity->ucCurUserNum++ ;
    }

    ulResult = IMSA_CallSendImsMsgEconfAddUser(IMSA_CALL_INVALID_ID, pstAppMsg);

    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgEconfAddUser: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgEconfAddUser_ENUM, LNAS_ERROR);

        /* ��Ҫ֪ͨSPM ������������ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstAppMsg->usClientId,
                                           pstAppMsg->ucOpId,
                                           TAF_CS_CAUSE_IMSA_ERROR);
        ulResult = VOS_FALSE;

    }

    return ulResult;

}

VOS_UINT32 IMSA_CallProcSpmMsgGetEconfInfo
(
    VOS_VOID *pMsg
)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU stQryCnf ={0};
    VOS_UINT32                          ulResult = VOS_FALSE;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    VOS_UINT8                           i= 0;
    SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU *pstAppMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgGetEconfInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgGetEconfInfo_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU*)pMsg;

    pstCallEntity = IMSA_CallEntityGetUsedByEconfFlag();

    if (VOS_NULL_PTR != pstCallEntity)
    {
        stQryCnf.ucNumOfCalls = pstCallEntity->ucCurUserNum;

        stQryCnf.ucNumOfMaxCalls = pstCallEntity->ucMaxUserNum;

        for (i = 0; i < pstCallEntity->ucCurUserNum; i ++)
        {
            /* ���������״̬ */
            stQryCnf.astCallInfo[i].enCallState = IMSA_EconfImsState2CsState(pstCallEntity->stEconfCalllist[i].enCallState);

            /* ��������ߺ��� */
            IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stEconfCalllist[i].stCalledNumber, &stQryCnf.astCallInfo[i].stCallNumber);

            /* ����display name */
            IMSA_MEM_CPY(stQryCnf.astCallInfo[i].aucDisplaytext,
                         pstCallEntity->stEconfCalllist[i].acAlpha,
                         TAF_IMSA_ALPHA_STRING_SZ);

            /* ����ԭ��ֵ */
            if (IMSA_OP_TRUE == pstCallEntity->stEconfCalllist[i].bitOpErrorInfo)
            {
                /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
                enSpmErr = IMSA_CallTransImsErr2SpmErr(pstCallEntity->stEconfCalllist[i].stErrorCode.usSipStatusCode);

                IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);
            }
            else
            {
                stQryCnf.astCallInfo[i].enCause = TAF_CS_CAUSE_SUCCESS;
            }

        }

        i = 0;

        /* ��������״̬ΪDISCONNECT״̬������Ҫ��AP���ѯ��״̬�󣬽����û����б���ɾ�������������û�ʱ��û��
        λ�ñ��������û���Ϣ ���ֻ�������DISCONNECT״̬���û���AP���Լ�ά�� */
        while(i < pstCallEntity->ucCurUserNum)
        {
            if (IMSA_IMS_ECONF_CALLER_STATE_DISCONNECT == pstCallEntity->stEconfCalllist[i].enCallState)
            {
                IMSA_MEM_CPY(&pstCallEntity->stEconfCalllist[i],
                            &pstCallEntity->stEconfCalllist[i + 1],
                            (IMSA_IMS_ECONF_CALLED_MAX_NUM - i - 1)*sizeof(IMSA_CALL_ECONF_SUMMARY_STRU));

                pstCallEntity->ucCurUserNum --;
            }
            else
            {
                i++;
            }
        }

    }

    stQryCnf.usClientId = pstAppMsg->usClientId;
    stQryCnf.enReqType = pstAppMsg->enReqType;
    stQryCnf.ucOpId = pstAppMsg->ucOpId;

    ulResult = IMSA_CallSendSpmGetEconfInfoCnf(&stQryCnf);


    return ulResult;
}

/* xiongxianghui00253310 add for conference 20140210 begin */

VOS_UINT32 IMSA_CallSendSpmInviteNewPtptCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU *pstInviteNewPtptCnf = VOS_NULL_PTR;

    (VOS_VOID)ulCallId;

    IMSA_INFO_LOG("IMSA_CallSendSpmInviteNewPtptCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmInviteNewPtptCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstInviteNewPtptCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU));
    if (VOS_NULL_PTR == pstInviteNewPtptCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmInviteNewPtptCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmInviteNewPtptCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstInviteNewPtptCnf), 0, IMSA_GET_MSG_LENGTH(pstInviteNewPtptCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstInviteNewPtptCnf, ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF);

    pstInviteNewPtptCnf->usClientId = usClientId;
    pstInviteNewPtptCnf->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstInviteNewPtptCnf->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstInviteNewPtptCnf);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallSendSpmCallTypeChangeInfoIndMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    MN_CALL_TYPE_ENUM_U8                enSrcCallType,
    MN_CALL_TYPE_ENUM_U8                enDestCallType,
    const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8    EmcSubType
)
{
    IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU *pstChangeInfoInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmCallTypeChangeInfoIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmCallTypeChangeInfoIndMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstChangeInfoInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstChangeInfoInd)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmCallTypeChangeInfoIndMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmCallTypeChangeInfoIndMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstChangeInfoInd), 0, IMSA_GET_MSG_LENGTH(pstChangeInfoInd));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstChangeInfoInd, ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND);

    pstChangeInfoInd->usClientId = usClientId;
    pstChangeInfoInd->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstChangeInfoInd->ucCallId     = (MN_CALL_ID_T)ulCallId;

    pstChangeInfoInd->enSrcCallType = enSrcCallType;
    pstChangeInfoInd->enDestCallType = enDestCallType;

    IMSA_CallSetSpmEmergencyCat(EmcSubType, &(pstChangeInfoInd->stEmergencyCat));

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstChangeInfoInd);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_CallSendSpmModifyCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_MODIFY_CNF_STRU *pstModifyCnf = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmModifyCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmModifyCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstModifyCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_MODIFY_CNF_STRU));
    if (VOS_NULL_PTR == pstModifyCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmModifyCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmModifyCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstModifyCnf), 0, IMSA_GET_MSG_LENGTH(pstModifyCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstModifyCnf, ID_IMSA_SPM_CALL_MODIFY_CNF);
    /*lint -e734*/
    pstModifyCnf->usClientId = usClientId;
    pstModifyCnf->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstModifyCnf->enCause    = ulResult;
    pstModifyCnf->callId     = ulCallId;
    /*lint +e734*/
    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstModifyCnf);

    return VOS_TRUE;
}

VOS_UINT32 IMSA_CallSendSpmAnswerRemoteModifyCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_MODIFY_CNF_STRU *pstModifyCnf = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmAnswerRemoteModifyCnfMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmAnswerRemoteModifyCnfMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstModifyCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_MODIFY_CNF_STRU));
    if (VOS_NULL_PTR == pstModifyCnf)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmAnswerRemoteModifyCnfMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmAnswerRemoteModifyCnfMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstModifyCnf), 0, IMSA_GET_MSG_LENGTH(pstModifyCnf));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstModifyCnf, ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF);
    /*lint -e734*/
    pstModifyCnf->usClientId = usClientId;
    pstModifyCnf->ucOpId     = (MN_OPERATION_ID_T)ulOpId;
    pstModifyCnf->enCause    = ulResult;
    pstModifyCnf->callId     = ulCallId;
    /*lint +e734*/
    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstModifyCnf);

    return VOS_TRUE;
}




/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgInviteNewPtpt
 Description    : SPM�·��������������������
 Input          : pstAppMsg      SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.xiongxianghui00253310      2014-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgInviteNewPtpt(VOS_VOID *pMsg)
{
    VOS_UINT32 ulResult     = VOS_FALSE;
    VOS_UINT32 ulCheckRst   = VOS_FALSE;
    IMSA_CALL_ENTITY_STRU  *pstCallEntity   = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *pstAppMsg   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgInviteNewPtpt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgInviteNewPtpt_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU*) pMsg;

    /* ����������������Լ�� */
    ulCheckRst = IMSA_CallInviteNewPtptAvailableCheck();
    if (VOS_FALSE == ulCheckRst)
    {
        IMSA_INFO_LOG1("IMSA_CallProcSpmMsgInviteNewPtpt: IMSA_CallInviteNewPtptAvailableCheck result", ulCheckRst);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcSpmMsgInviteNewPtpt_ENUM, 1, ulCheckRst);

        (VOS_VOID)IMSA_CallSendSpmInviteNewPtptCnfMsg(pstAppMsg->usClientId,
                                                      pstAppMsg->ucOpId,
                                                      IMSA_CALL_INVALID_ID,
                                                      TAF_CS_CAUSE_IMSA_ERROR);

        return ulResult;
    }

    pstCallEntity = IMSA_CallEntityAlloc();
    if (VOS_NULL_PTR != pstCallEntity)
    {
        /* ����CLIENT ID��OPID */
        pstCallEntity->usClientId = pstAppMsg->usClientId;
        pstCallEntity->ulOpId = pstAppMsg->ucOpId;

        ulResult = IMSA_CallSendImsMsgInviteNewPtpt(IMSA_CALL_INVALID_ID, pstAppMsg);
        if (VOS_TRUE == ulResult)
        {

            /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
            IMSA_MEM_CPY(   &pstCallEntity->stSpmMsg,
                            &pstCallCtx->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU));

            /* ����������ʱ�� */
            IMSA_StartTimer(&pstCallCtx->stProctectTimer);
        }
        else
        {
            IMSA_ERR_LOG("IMSA_CallProcSpmMsgInviteNewPtpt: send IMS msg failure");
            TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgInviteNewPtpt_ENUM, LNAS_FAIL);

            IMSA_CallEntityFree(pstCallEntity);
        }
    }
    else
    {
        /* ������Դʧ�ܣ��ܾ������� */
        (VOS_VOID)IMSA_CallSendSpmInviteNewPtptCnfMsg(pstAppMsg->usClientId,
                                                      pstAppMsg->ucOpId,
                                                      IMSA_CALL_INVALID_ID,
                                                      TAF_CS_CAUSE_IMSA_ALLOC_ENTITY_FAIL);
    }

    return ulResult;
}
/* xiongxianghui00253310 add for conference 20140210 end */



VOS_UINT32 IMSA_InsertSrvccBuff
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulDataLen
)
{
    IMSA_SRVCC_BUFFER_STRU             *pstSrvccBuff = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_InsertSrvccBuff  entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_InsertSrvccBuff_ENUM, LNAS_ENTRY);

    pstSrvccBuff = IMSA_GetSrvccBuffAddress();

    if (ulDataLen > sizeof(IMSA_SRVCC_BUFF_MSG_UNION))
    {
        IMSA_WARN_LOG("IMSA_InsertSrvccBuff:data len illegal");
        TLPS_PRINT2LAYER_WARNING(IMSA_InsertSrvccBuff_ENUM, LNAS_PARAM_INVALID);

        return IMSA_FAIL;
    }

    if (IMSA_CALL_MSG_SYNC_MAX_NUM <= pstSrvccBuff->ucBuffMsgNum)
    {
        IMSA_WARN_LOG("IMSA_InsertSrvccBuff:buffer full");
        TLPS_PRINT2LAYER_WARNING(IMSA_InsertSrvccBuff_ENUM, 2);

        return IMSA_FAIL;
    }

    IMSA_MEM_CPY(   &pstSrvccBuff->aucBuffMsgArray[pstSrvccBuff->ucBuffMsgNum],
                    pucData,
                    ulDataLen);

    pstSrvccBuff->ucBuffMsgNum++;

    return IMSA_SUCC;
}


VOS_VOID IMSA_CallOrigReqSrvccingProc
(
    const SPM_IMSA_CALL_ORIG_REQ_STRU  *pstCallOrigReq
)
{
    if (IMSA_FAIL == IMSA_InsertSrvccBuff( (VOS_UINT8*)pstCallOrigReq,
                                            sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU)))
    {
        IMSA_INFO_LOG("IMSA_CallOrigReqSrvccingProc:buffer fail");
        TLPS_PRINT2LAYER_INFO(IMSA_CallOrigReqSrvccingProc_ENUM, LNAS_FAIL);

        (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstCallOrigReq->usClientId,
                                             pstCallOrigReq->ucOpId,
                                             IMSA_CALL_INVALID_ID,
                                             TAF_CS_CAUSE_IMSA_SRVCCING_BUFF_MSG_FAIL);
    }

    IMSA_INFO_LOG("IMSA_CallOrigReqSrvccingProc:buffer succ");
    TLPS_PRINT2LAYER_INFO(IMSA_CallOrigReqSrvccingProc_ENUM, LNAS_SUCC);
}


VOS_VOID IMSA_CallSupsCmdReqSrvccingProc
(
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstCallSupsCmdReq
)
{
    if (IMSA_FAIL == IMSA_InsertSrvccBuff( (VOS_UINT8*)pstCallSupsCmdReq,
                                            sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU)))
    {
        IMSA_INFO_LOG("IMSA_CallSupsCmdReqSrvccingProc:buffer fail");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSupsCmdReqSrvccingProc_ENUM, LNAS_FAIL);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(   pstCallSupsCmdReq->usClientId,
                                                pstCallSupsCmdReq->ucOpId,
                                                pstCallSupsCmdReq->stCallMgmtCmd.callId,
                                                TAF_CS_CAUSE_IMSA_SRVCCING_BUFF_MSG_FAIL);
    }

    IMSA_INFO_LOG("IMSA_CallSupsCmdReqSrvccingProc:buffer succ");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSupsCmdReqSrvccingProc_ENUM, LNAS_SUCC);
}


VOS_VOID IMSA_CallStartDtmfReqSrvccingProc
(
    const SPM_IMSA_CALL_START_DTMF_REQ_STRU  *pstCallStartDtmfReq
)
{
    if (IMSA_FAIL == IMSA_InsertSrvccBuff( (VOS_UINT8*)pstCallStartDtmfReq,
                                            sizeof(SPM_IMSA_CALL_START_DTMF_REQ_STRU)))
    {
        IMSA_INFO_LOG("IMSA_CallStartDtmfReqSrvccingProc:buffer fail");
        TLPS_PRINT2LAYER_INFO(IMSA_CallStartDtmfReqSrvccingProc_ENUM, LNAS_FAIL);

        (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  pstCallStartDtmfReq->usClientId,
                                                    pstCallStartDtmfReq->ucOpId,
                                                    pstCallStartDtmfReq->stDtmf.CallId,
                                                    TAF_CS_CAUSE_IMSA_SRVCCING_BUFF_MSG_FAIL);
    }

    IMSA_INFO_LOG("IMSA_CallStartDtmfReqSrvccingProc:buffer succ");
    TLPS_PRINT2LAYER_INFO(IMSA_CallStartDtmfReqSrvccingProc_ENUM, LNAS_SUCC);
}


VOS_VOID IMSA_CallStopDtmfReqSrvccingProc
(
    const SPM_IMSA_CALL_STOP_DTMF_REQ_STRU  *pstCallStopDtmfReq
)
{
    if (IMSA_FAIL == IMSA_InsertSrvccBuff( (VOS_UINT8*)pstCallStopDtmfReq,
                                            sizeof(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU)))
    {
        IMSA_INFO_LOG("IMSA_CallStopDtmfReqSrvccingProc:buffer fail");
        TLPS_PRINT2LAYER_INFO(IMSA_CallStopDtmfReqSrvccingProc_ENUM, LNAS_FAIL);

        (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   pstCallStopDtmfReq->usClientId,
                                                    pstCallStopDtmfReq->ucOpId,
                                                    pstCallStopDtmfReq->stDtmf.CallId,
                                                    TAF_CS_CAUSE_IMSA_SRVCCING_BUFF_MSG_FAIL);
    }

    IMSA_INFO_LOG("IMSA_CallStopDtmfReqSrvccingProc:buffer succ");
    TLPS_PRINT2LAYER_INFO(IMSA_CallStopDtmfReqSrvccingProc_ENUM, LNAS_SUCC);
}


VOS_VOID IMSA_UssdProcUssdReqSrvccingProc
(
    const SPM_IMSA_PROCESS_USSD_REQ_STRU  *pstProcUssdReq
)
{
    if (IMSA_FAIL == IMSA_InsertSrvccBuff( (VOS_UINT8*)pstProcUssdReq,
                                            sizeof(SPM_IMSA_PROCESS_USSD_REQ_STRU)))
    {
        IMSA_INFO_LOG("IMSA_UssdProcUssdReqSrvccingProc:buffer fail");
        TLPS_PRINT2LAYER_INFO(IMSA_UssdProcUssdReqSrvccingProc_ENUM, LNAS_FAIL);
        (VOS_VOID)IMSA_SendSpmUssdErrorEvt( pstProcUssdReq->usClientId,
                                            pstProcUssdReq->ucOpId,
                                            TAF_ERR_IMSA_SRVCCING_BUFF_MSG_FAIL);
    }

    IMSA_INFO_LOG("IMSA_UssdProcUssdReqSrvccingProc:buffer succ");
    TLPS_PRINT2LAYER_INFO(IMSA_UssdProcUssdReqSrvccingProc_ENUM, LNAS_SUCC);
}


VOS_VOID IMSA_ClearSrvccBuff( VOS_VOID )
{
    IMSA_MEM_SET(   IMSA_GetSrvccBuffAddress(),
                    0,
                    sizeof(IMSA_SRVCC_BUFFER_STRU));
}


VOS_UINT32 IMSA_SrvccingBufferMsgProc( const VOS_VOID *pBuffMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pstHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pstHeader = (PS_MSG_HEADER_STRU *) pBuffMsg;

    /* �������SRVCC�����У���ֱ���˳� */
    if (IMSA_TRUE != IMSA_CallGetSrvccFlag())
    {
        return IMSA_MSG_NOT_PROC;
    }

    switch (pstHeader->ulMsgName)
    {
        case ID_SPM_IMSA_CALL_ORIG_REQ:

            IMSA_CallOrigReqSrvccingProc(pBuffMsg);
            break;

        case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:

            IMSA_CallSupsCmdReqSrvccingProc(pBuffMsg);
            break;

        case ID_SPM_IMSA_CALL_START_DTMF_REQ:

            IMSA_CallStartDtmfReqSrvccingProc(pBuffMsg);
            break;

        case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:

            IMSA_CallStopDtmfReqSrvccingProc(pBuffMsg);
            break;

        case ID_SPM_IMSA_PROCESS_USSD_REQ:

            IMSA_UssdProcUssdReqSrvccingProc(pBuffMsg);
            break;

        default:

            return IMSA_MSG_NOT_PROC;

    }

    return IMSA_MSG_PROCED;
}
VOS_VOID IMSA_CallSendCallMsgSyncInd
(
    VOS_UINT32                          ulSynMsgNum,
    const VOS_UINT32                   *pulSynMsgIndexArray
)
{
    IMSA_SRVCC_BUFFER_STRU             *pstSrvccBuff    = VOS_NULL_PTR;
    IMSA_CALL_MSG_SYNC_IND_STRU        *pstMsgSyncInd   = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if ((ulSynMsgNum == 0) || (ulSynMsgNum > IMSA_CALL_MSG_SYNC_MAX_NUM)
        || (VOS_NULL_PTR == pulSynMsgIndexArray))
    {
        return ;
    }

    IMSA_INFO_LOG("IMSA_CallSendCallMsgSyncInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendCallMsgSyncInd_ENUM, LNAS_ENTRY);

    pstSrvccBuff = IMSA_GetSrvccBuffAddress();

    pstMsgSyncInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_CALL_MSG_SYNC_IND_STRU));

    if (VOS_NULL_PTR == pstMsgSyncInd)
    {
        IMSA_ERR_LOG("IMSA_CallSendCallMsgSyncInd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendCallMsgSyncInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgSyncInd), 0, IMSA_GET_MSG_LENGTH(pstMsgSyncInd));

    for (i = 0; i < ulSynMsgNum; i++)
    {
        IMSA_MEM_CPY(   &pstMsgSyncInd->astMsgArray[pstMsgSyncInd->ucMsgNum],
                        &pstSrvccBuff->aucBuffMsgArray[pulSynMsgIndexArray[i]],
                        sizeof(IMSA_CALL_MSG_UNION));

        pstMsgSyncInd->ucMsgNum++;
    }

    /* ��д��Ϣͷ */
    IMSA_WRITE_CALL_MSG_HEAD(pstMsgSyncInd, ID_IMSA_CALL_MSG_SYNC_IND);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstMsgSyncInd);
}


/*****************************************************************************
 Function Name  : IMSA_CallSendCcwaCapInfo
 Description    : IMSA��CALLģ��ͨ��CCWA���ã�
 Input          : ucCcwacap---------------CCWA������Ϣ
                  0:��֧��CCWA
                  1:֧��CCWA
 Output         : None
 Return Value   :
                  ʧ��:VOS_FALSE ;
                  �ɹ�:VOS_TRUE
 History        :
      1.jiaguocai 00355737     2015-08-27  Draft Enact
*****************************************************************************/

VOS_VOID IMSA_CallSendCcwaCapInfo(VOS_UINT8 ucCcwacap)
{
    IMSA_CALL_CCWA_CAP_NOTIFY_STRU  *pstCcwaCapNotify = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendCcwaCapInfo is entered!");

    pstCcwaCapNotify = (VOS_VOID *)IMSA_ALLOC_MSG(sizeof(IMSA_CALL_CCWA_CAP_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstCcwaCapNotify)
    {
        IMSA_ERR_LOG("IMSA_CallSendCcwaCapInfo: alloc memory fail");
        return ;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstCcwaCapNotify), 0, IMSA_GET_MSG_LENGTH(pstCcwaCapNotify));

    /* ��д��Ϣͷ */
    IMSA_WRITE_CALL_MSG_HEAD(pstCcwaCapNotify, ID_IMSA_CALL_CCWA_CAP_NOTIFY);

    pstCcwaCapNotify->ucCcwaCap = ucCcwacap;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCcwaCapNotify);
}




VOS_VOID IMSA_SrvccSuccBuffProc( VOS_VOID )
{
    IMSA_SRVCC_BUFFER_STRU             *pstSrvccBuff    = VOS_NULL_PTR;
    PS_MSG_HEADER_STRU                 *pstHeader       = VOS_NULL_PTR;
    SPM_IMSA_PROCESS_USSD_REQ_STRU     *pstUssdReq      = VOS_NULL_PTR;
    VOS_UINT32                          ulSynMsgNum     = IMSA_NULL;
    VOS_UINT32                          aulSynMsgIndexArray[IMSA_CALL_MSG_SYNC_MAX_NUM] = {0};
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_SrvccSuccBuffProc  entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SrvccSuccBuffProc_ENUM, LNAS_ENTRY);

    pstSrvccBuff = IMSA_GetSrvccBuffAddress();

    if (pstSrvccBuff->ucBuffMsgNum == 0)
    {
        IMSA_INFO_LOG("IMSA_SrvccSuccBuffProc:no buffer msg");
        TLPS_PRINT2LAYER_INFO(IMSA_SrvccSuccBuffProc_ENUM, 1);
        return ;
    }

    for (i = 0; i < pstSrvccBuff->ucBuffMsgNum; i++)
    {
        pstHeader = (PS_MSG_HEADER_STRU *)(&pstSrvccBuff->aucBuffMsgArray[i]);

        if (pstHeader->ulMsgName != ID_SPM_IMSA_PROCESS_USSD_REQ)
        {
            aulSynMsgIndexArray[ulSynMsgNum] = i;
            ulSynMsgNum++;
            continue;
        }

        /* ��USSD֮ǰ�Ļ�����Ϣ����CALLģ�� */
        IMSA_CallSendCallMsgSyncInd(ulSynMsgNum, aulSynMsgIndexArray);
        ulSynMsgNum = 0;

        /* �ظ�ʧ�ܣ�ԭ��ֵΪSRVCC_SUCC������SPM��CS���ز� */
        pstUssdReq = (SPM_IMSA_PROCESS_USSD_REQ_STRU*)pstHeader;
        (VOS_VOID)IMSA_SendSpmUssdErrorEvt( pstUssdReq->usClientId,
                                            pstUssdReq->ucOpId,
                                            TAF_ERR_IMSA_SRVCCING_BUFF_MSG);
    }

    IMSA_CallSendCallMsgSyncInd(ulSynMsgNum, aulSynMsgIndexArray);
    /* ulSynMsgNum = 0; */

    /* �建�� */
    IMSA_ClearSrvccBuff();
}


VOS_VOID IMSA_SrvccFailBuffProc( VOS_VOID )
{
    IMSA_SRVCC_BUFFER_STRU             *pstSrvccBuff    = VOS_NULL_PTR;
    PS_MSG_HEADER_STRU                 *pstHeader       = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_SrvccFailBuffProc  entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SrvccFailBuffProc_ENUM, LNAS_ENTRY);

    pstSrvccBuff = IMSA_GetSrvccBuffAddress();

    if (pstSrvccBuff->ucBuffMsgNum == 0)
    {
        IMSA_INFO_LOG("IMSA_SrvccFailBuffProc:no buffer msg");
        TLPS_PRINT2LAYER_INFO(IMSA_SrvccFailBuffProc_ENUM, 1);
        return ;
    }

    for (i = 0; i < pstSrvccBuff->ucBuffMsgNum; i++)
    {
         pstHeader = (PS_MSG_HEADER_STRU *)(&pstSrvccBuff->aucBuffMsgArray[i]);

         switch (pstHeader->ulMsgName)
         {
            case ID_SPM_IMSA_CALL_ORIG_REQ:

                (VOS_VOID)IMSA_CallProcSpmMsgOrig((SPM_IMSA_CALL_ORIG_REQ_STRU *)&pstSrvccBuff->aucBuffMsgArray[i]);
                break;

            case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:

                (VOS_VOID)IMSA_CallProcSpmMsgSups((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *)&pstSrvccBuff->aucBuffMsgArray[i]);
                break;

            case ID_SPM_IMSA_CALL_START_DTMF_REQ:

                (VOS_VOID)IMSA_CallProcSpmMsgStartDtmf((SPM_IMSA_CALL_START_DTMF_REQ_STRU *)&pstSrvccBuff->aucBuffMsgArray[i]);
                break;

            case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:

                (VOS_VOID)IMSA_CallProcSpmMsgStopDtmf((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *)&pstSrvccBuff->aucBuffMsgArray[i]);
                break;

            case ID_SPM_IMSA_PROCESS_USSD_REQ:

                (VOS_VOID)IMSA_SsProcSpmMsgProcessUssdReq((SPM_IMSA_PROCESS_USSD_REQ_STRU *)&pstSrvccBuff->aucBuffMsgArray[i]);
                break;

            default:

                IMSA_WARN_LOG("IMSA_SrvccFailBuffProc:illegal buffer msg type!");
                TLPS_PRINT2LAYER_WARNING(IMSA_SrvccFailBuffProc_ENUM, LNAS_PARAM_INVALID);
                break;
         }
    }

    /* �建�� */
    IMSA_ClearSrvccBuff();
}
VOS_VOID IMSA_SrvccAbormalClearBuff
(
    IMSA_SRVCC_ABNORMAL_TYPE_ENUM_UINT32    enAbnormalType
)
{
    IMSA_SRVCC_BUFFER_STRU             *pstSrvccBuff    = VOS_NULL_PTR;
    PS_MSG_HEADER_STRU                 *pstHeader       = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;
    TAF_CS_CAUSE_ENUM_UINT32            ulTafCsCause    = TAF_CS_CAUSE_IMSA_SRVCC_ABNORMAL;
    VOS_UINT16                          usUssdError     = TAF_ERR_IMSA_SRVCC_ABNORMAL;

    pstSrvccBuff = IMSA_GetSrvccBuffAddress();

    if (pstSrvccBuff->ucBuffMsgNum == 0)
    {
        IMSA_INFO_LOG("IMSA_SrvccAbormalClearBuff:no buffer msg");
        TLPS_PRINT2LAYER_INFO(IMSA_SrvccAbormalClearBuff_ENUM, 1);
        return ;
    }

    IMSA_INFO_LOG("IMSA_SrvccAbormalClearBuff  entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SrvccAbormalClearBuff_ENUM, LNAS_ENTRY);

    if (IMSA_SRVCC_ABNORMAL_DEREG_REQ == enAbnormalType)
    {
        ulTafCsCause    = TAF_CS_CAUSE_IMSA_SRVCC_ABNORMAL_DEREG;
        usUssdError     = TAF_ERR_IMSA_SRVCC_ABNORMAL_DEREG;
    }

    for (i = 0; i < pstSrvccBuff->ucBuffMsgNum; i++)
    {
         pstHeader = (PS_MSG_HEADER_STRU *)(&pstSrvccBuff->aucBuffMsgArray[i]);

         switch (pstHeader->ulMsgName)
         {
            case ID_SPM_IMSA_CALL_ORIG_REQ:

                (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(((SPM_IMSA_CALL_ORIG_REQ_STRU*)pstHeader)->usClientId,
                                                    ((SPM_IMSA_CALL_ORIG_REQ_STRU*)pstHeader)->ucOpId,
                                                    IMSA_CALL_INVALID_ID,
                                                    ulTafCsCause);
                break;

            case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:

                (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU*)pstHeader)->usClientId,
                                                    ((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU*)pstHeader)->ucOpId,
                                                    ((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU*)pstHeader)->stCallMgmtCmd.callId,
                                                    ulTafCsCause);
                break;

            case ID_SPM_IMSA_CALL_START_DTMF_REQ:

                (VOS_VOID)IMSA_CallSendSpmStartDtmfCnfMsg(  ((SPM_IMSA_CALL_START_DTMF_REQ_STRU*)pstHeader)->usClientId,
                                                            ((SPM_IMSA_CALL_START_DTMF_REQ_STRU*)pstHeader)->ucOpId,
                                                            ((SPM_IMSA_CALL_START_DTMF_REQ_STRU*)pstHeader)->stDtmf.CallId,
                                                            ulTafCsCause);
                break;

            case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:

                (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg(   ((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU*)pstHeader)->usClientId,
                                                            ((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU*)pstHeader)->ucOpId,
                                                            ((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU*)pstHeader)->stDtmf.CallId,
                                                            ulTafCsCause);
                break;

            case ID_SPM_IMSA_PROCESS_USSD_REQ:

                /* �ظ�ʧ�ܣ�ԭ��ֵΪSRVICE NOT AVAILABLE */
                (VOS_VOID)IMSA_SendSpmUssdErrorEvt( ((SPM_IMSA_PROCESS_USSD_REQ_STRU*)pstHeader)->usClientId,
                                                    ((SPM_IMSA_PROCESS_USSD_REQ_STRU*)pstHeader)->ucOpId,
                                                    usUssdError);
                break;

            default:

                IMSA_WARN_LOG("IMSA_SrvccAbormalClearBuff:illegal buffer msg type!");
                TLPS_PRINT2LAYER_WARNING(IMSA_SrvccAbormalClearBuff_ENUM, LNAS_MSG_INVALID);
                break;
         }
    }

    /* �建�� */
    IMSA_ClearSrvccBuff();
}

VOS_UINT32 IMSA_CallProcSpmMsgModifyReq
(
    VOS_VOID *pMsg
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 ulResult = VOS_TRUE;
    SPM_IMSA_CALL_MODIFY_REQ_STRU *pstAppMsg    = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgModifyReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgModifyReq_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_MODIFY_REQ_STRU*)pMsg;


    ulResult = IMSA_CallSendImsMsgModify(pstAppMsg);

    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgModifyReq: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgModifyReq_ENUM, LNAS_ERROR);

        /* ��Ҫ֪ͨSPM �л�����ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmModifyCnfMsg(pstAppMsg->usClientId,
                                     pstAppMsg->ucOpId,
                                     pstAppMsg->callId,
                                     TAF_CS_CAUSE_IMSA_ERROR);
        ulResult = VOS_FALSE;

    }

    return ulResult;
}

VOS_UINT32 IMSA_CallProcSpmMsgAnswerRemoteModifyReq
(
    VOS_VOID *pMsg
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 ulResult = VOS_TRUE;
    SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU *pstAppMsg    = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgAnswerRemoteModifyReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgAnswerRemoteModifyReq_ENUM, LNAS_ENTRY);

    pstAppMsg = (SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU*)pMsg;


    ulResult = IMSA_CallSendImsMsgAnswerRemoteModify(pstAppMsg);

    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgAnswerRemoteModifyReq: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgAnswerRemoteModifyReq_ENUM, LNAS_ERROR);

        /* ��Ҫ֪ͨSPM �л�����ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmAnswerRemoteModifyCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->callId,
                                                 TAF_CS_CAUSE_IMSA_ERROR);
        ulResult = VOS_FALSE;

    }

    return ulResult;
}




VOS_VOID IMSA_ProcSpmCallMsg(const VOS_VOID *pRcvMsg)
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU                 *pstHeader = VOS_NULL_PTR;
    VOS_UINT32                           ulIndex = 0;
    IMSA_SPM_CALL_MSG_ACTION_FUN        pActFun;

    IMSA_INFO_LOG("IMSA_ProcSpmCallMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcSpmCallMsg_ENUM, LNAS_ENTRY);

    /* ��ȡ��Ϣͷָ��*/
    pstHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    if (VOS_NULL_PTR == pstHeader)
    {
        IMSA_ERR_LOG("IMSA_ProcSpmCallMsg: NULL message");
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcSpmCallMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_INFO_LOG1("IMSA_ProcSpmCallMsg: msg id", pstHeader->ulMsgName);

    if (IMSA_MSG_PROCED == IMSA_SrvccingBufferMsgProc(pRcvMsg))
    {
        IMSA_INFO_LOG("IMSA_ProcSpmCallMsg: Srvccing buffer!");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcSpmCallMsg_ENUM, 3);
        return ;
    }

    /*���ݻظ����,��ѯ������ ,������Ӧ����*/
    for (ulIndex = 0; ulIndex < g_ulImsaSpmCallMsgActTblLen; ulIndex++)
    {
        /* ͨ��MSG ID���Ҵ����� */
        if(pstHeader->ulMsgName == g_stImsaSpmCallMsgActTbl[ulIndex].enMsgName)
        {
            pActFun = g_stImsaSpmCallMsgActTbl[ulIndex].pfActionFun;

            /* �д����� */
            if (VOS_NULL_PTR != pActFun)
            {
                (VOS_VOID)(pActFun)((VOS_VOID*)pRcvMsg);
            }
        }
    }
    return;
}

/*lint +e961*/


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcSpmMsg.c */



