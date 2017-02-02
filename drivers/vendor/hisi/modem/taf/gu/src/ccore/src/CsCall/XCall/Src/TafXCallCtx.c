

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallCtx.h"
#include "TafSdcCtx.h"
#include "TafStdlib.h"
#include "TafXCallMntn.h"
#include "MnClient.h"
#include "siapppb.h"

#include "TafCdmaPlusTranslate.h"

/* Added by h00313353 for Iteration 17, 2015-7-7, begin */
#include "TafXCallProcNvim.h"
/* Added by h00313353 for Iteration 17, 2015-7-7, end */
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
#include "TafLog.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXcc.h"
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_XCALL_CTX_STRU                      g_stTafXcallCtx;

TAF_XCALL_CS_ERR_CODE_MAP_STRU          g_astTafXcallErrCodeMapTbl[] =
{
    {TAF_CS_CAUSE_SUCCESS,                                  TAF_XCC_CAUSE_SUCCESS},
    {TAF_CS_CAUSE_XCALL_NO_SERVICE,                         TAF_XCC_CAUSE_NO_SERVICE},
    {TAF_CS_CAUSE_XCALL_MAX_ACCESS_PROBES,                  TAF_XCC_CAUSE_MAX_ACCESS_PROBES},
    {TAF_CS_CAUSE_XCALL_REORDER,                            TAF_XCC_CAUSE_REORDER},
    {TAF_CS_CAUSE_XCALL_INTERCEPT,                          TAF_XCC_CAUSE_INTERCEPT},
    {TAF_CS_CAUSE_XCALL_ACCESS_DENYIED,                     TAF_XCC_CAUSE_ACCESS_DENYIED},
    {TAF_CS_CAUSE_XCALL_LOCK,                               TAF_XCC_CAUSE_LOCK},
    {TAF_CS_CAUSE_XCALL_ACCT_BLOCK,                         TAF_XCC_CAUSE_ACCT_BLOCK},
    {TAF_CS_CAUSE_XCALL_NDSS,                               TAF_XCC_CAUSE_NDSS},
    {TAF_CS_CAUSE_XCALL_REDIRECTION,                        TAF_XCC_CAUSE_REDIRECTION},
    {TAF_CS_CAUSE_XCALL_NOT_ACCEPT_BY_BS,                   TAF_XCC_CAUSE_NOT_ACCEPT_BY_BS},
    {TAF_CS_CAUSE_XCALL_ACCESS_IN_PROGRESS,                 TAF_XCC_CAUSE_ACCESS_IN_PROGRESS},
    {TAF_CS_CAUSE_XCALL_ACCESS_FAIL,                        TAF_XCC_CAUSE_ACCESS_FAIL},
    {TAF_CS_CAUSE_XCALL_ABORT,                              TAF_XCC_CAUSE_ABORT},


    {TAF_CS_CAUSE_XCALL_SIGNAL_FADE,                        TAF_XCC_CAUSE_SIGNAL_FADE},
    {TAF_CS_CAUSE_XCALL_CHANNEL_ASSIGN_TIMEOUT,             TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT},
    {TAF_CS_CAUSE_XCALL_BS_RELEASE,                         TAF_XCC_CAUSE_BS_RELEASE},
    {TAF_CS_CAUSE_XCALL_OTHER_SERVICE_IN_TCH,               TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH},
    {TAF_CS_CAUSE_XCALL_CCS_NOT_SUPPORT,                    TAF_XCC_CAUSE_CCS_NOT_SUPPORT},
    {TAF_CS_CAUSE_XCALL_NORMAL_RELEASE,                     TAF_XCC_CAUSE_NORMAL_RELEASE},
    {TAF_CS_CAUSE_XCALL_SO_REJ,                             TAF_XCC_CAUSE_SO_REJ},
    {TAF_CS_CAUSE_XCALL_RELEASE_TIME_OUT,                   TAF_XCC_CAUSE_RELEASE_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_CONNECT_ORDER_ACK_FAILURE,          TAF_XCC_CAUSE_CONNECT_ORDER_ACK_FAILURE},
    {TAF_CS_CAUSE_XCALL_INCOMING_RSP_TIME_OUT,              TAF_XCC_CAUSE_INCOMING_RSP_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_L2_ACK_TIME_OUT,                    TAF_XCC_CAUSE_L2_ACK_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_POWER_DOWN_IND,                     TAF_XCC_CAUSE_POWER_DOWN_IND},

    {TAF_CS_CAUSE_XCALL_CONNID_NOT_FOUND,                   TAF_XCC_CAUSE_CONNID_NOT_FOUND},
    {TAF_CS_CAUSE_XCALL_ACCESS_CNF_TIMEOUT,                 TAF_XCC_CAUSE_ACCESS_CNF_TIMEOUT},
    {TAF_CS_CAUSE_XCALL_ACCESS_IND_TIMEOUT,                 TAF_XCC_CAUSE_ACCESS_TCH_TIMEOUT},

    {TAF_CS_CAUSE_XCALL_UNKNOWN,                            TAF_XCC_CAUSE_UNKNOWN},
    {TAF_CS_CAUSE_XCALL_CALL_NOT_ALLOWED,                   TAF_XCC_CAUSE_CALL_NOT_ALLOWED},

    {TAF_CS_CAUSE_XCALL_XCALL_HANGUP,                       TAF_XCC_CAUSE_XCALL_HANGUP},

    {TAF_CS_CAUSE_XCALL_WAIT_L2_ACK_RELEASE,                TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE},
    {TAF_CS_CAUSE_XCALL_EMERGENCY_CALL_FLASHED,             TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED},
    {TAF_CS_CAUSE_XCALL_EMERGENCY_CALL_ABORT,               TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT},

    {TAF_CS_CAUSE_XCALL_NDSS_REDIAL_IND,                    TAF_XCC_CAUSE_NDSS_REDIAL_IND},

    {TAF_CS_CAUSE_XCALL_MT_SMS_IN_TCH,                      TAF_XCC_CAUSE_MT_SMS_IN_TCH},
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

TAF_XCALL_CTX_STRU* TAF_XCALL_GetCtxAddr(VOS_VOID)
{
    return &(g_stTafXcallCtx);
}


TAF_XCALL_CALL_ENTITY_STRU* TAF_XCALL_GetCallEntityAddr(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->astCallEntity[ucCallId - 1]);
}


TAF_XCALL_CONFIG_STRU* TAF_XCALL_GetConfigInfo(VOS_VOID)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->stConfig);
}


VOS_VOID TAF_XCALL_UpdateDigitMode(
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
)
{
    TAF_XCALL_CONFIG_STRU              *pstCallConfig = VOS_NULL_PTR;

    pstCallConfig                       = TAF_XCALL_GetConfigInfo();
    pstCallConfig->enDigitMode          = enDigitMode;

    return;
}


VOS_VOID TAF_XCALL_InitSpecCallEntity(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(pstCallEntity, 0, sizeof(TAF_XCALL_CALL_ENTITY_STRU));

    pstCallEntity->ulUsed         = VOS_FALSE;

    pstCallEntity->enSo           = TAF_XCALL_SO_BUTT;

    pstCallEntity->enCallState    = MN_CALL_S_IDLE;

    pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_BUTT;

    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    /*lint -e717*/
    HI_INIT_LIST_HEAD(&pstCallEntity->stDtmfBuffer.stList);
    /*lint +e717*/
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */
}


VOS_VOID TAF_XCALL_InitNvConfig( VOS_VOID )
{
    TAF_XCALL_ReadEmcCallRedialPeriod();

    TAF_XCALL_Read1xVoiceSoCfgNvim();
    TAF_XCALL_ReadStartAndStopContDtmfIntervalLen();
    return;
}


VOS_VOID TAF_XCALL_InitCtx(VOS_VOID)
{
    VOS_UINT8                           ucCallId;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    /* 初始化呼叫实体 */
    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        TAF_XCALL_InitSpecCallEntity(ucCallId);
    }

    /* 初始化sups mgmt */
    PS_MEM_SET(&(pstXcallCtx->stSupsCmdMgmt), 0, sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* 初始化configure */
    PS_MEM_SET(&(pstXcallCtx->stConfig), 0, sizeof(TAF_XCALL_CONFIG_STRU));
    pstXcallCtx->stConfig.enDigitMode   = TAF_XCALL_DIGIT_MODE_DTMF;

    TAF_XCALL_InitAllTimers(pstXcallCtx->astTimerCtx);

    /* Added by h00313353 for Iteration 17, 2015-7-7, begin */
    TAF_XCALL_InitNvConfig();
    /* Added by h00313353 for Iteration 17, 2015-7-7, end */
}
TAF_XCALL_TIMER_CTX_STRU*  TAF_XCALL_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_XCALL_GetCtxAddr()->astTimerCtx;
}




VOS_UINT32  TAF_XCALL_AllocCallId(
    VOS_UINT8                      *pucCallId
)
{
    /* 查找空闲的CALL ID，分配给新的呼叫 */
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        /* 如果有未分配的实体，返回的Call id 的值为实体数组下标值加1 */
        if (VOS_FALSE == pstXcallCtx->astCallEntity[i].ulUsed)
        {
            *pucCallId = i + 1;

            TAF_XCALL_InitSpecCallEntity(*pucCallId);
            pstXcallCtx->astCallEntity[i].ulUsed = VOS_TRUE;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


VOS_UINT32 TAF_XCALL_IsAllowMoCallInCurrentStatus(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* 目前呼叫重拨已经实现,服务状态的判定这里不需要 */

    /* 发起的为紧急呼且当前存在一路被叫则允许发起,被叫的具体状态在XCC
       进行判定能否发起 */
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        if (VOS_TRUE == TAF_XCALL_IsMtCallInstanceExist())
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* 如果卡无效，拒绝普通呼 */
        if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
        {
            return VOS_FALSE;
        }
    }

    /* 当前呼叫类型为normal call时，所有呼叫实体都处于IDLE态,可以发起新呼叫 */
    if (VOS_TRUE == TAF_XCALL_ExistCallInstance())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XCALL_IsAvailCallId(
    VOS_UINT8                           ucCallId
)
{
    if ((0 == ucCallId)
     || (TAF_XCALL_CALL_ENTITY_MAX_NUM < ucCallId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XCALL_IsAvailVoiceCallSo(
    VOS_UINT16                          usSo
)
{
    if ((TAF_XCALL_SO_3_EVRC == usSo)
     || (TAF_XCALL_SO_68_EVRC_B == usSo)
     || (TAF_XCALL_SO_73_EVRC_NW == usSo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_XCALL_CreateMoCallEntity(
    VOS_UINT8                           ucCallId,
    MN_CALL_APP_REQ_MSG_STRU           *pstCallPara
)
{
    /* 根据CALL ID分配呼叫实体 */
    MN_CALL_ORIG_PARAM_STRU            *pstOrig       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstOrig       = &pstCallPara->unParm.stOrig;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 记录发起call业务用户的信息(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               pstCallPara->ulSenderPid,
                               pstCallPara->clientId,
                               pstCallPara->opId);
    /* 初始化呼叫参数 */
    pstCallEntity->enCallDir            = MN_CALL_DIR_MO;
    pstCallEntity->enCallState          = MN_CALL_S_DIALING;
    pstCallEntity->enCallType           = pstOrig->enCallType;
    pstCallEntity->enCause              = TAF_CS_CAUSE_SUCCESS;
    pstCallEntity->ucConnectId          = 0;
    pstCallEntity->ucConRef             = 0;
    pstCallEntity->enSo                 = TAF_XCALL_GetConfigInfo()->enSoInitType;
    pstCallEntity->ucIsAlertAnsByPass   = VOS_FALSE;


    /* 初始化被叫号码 */
    PS_MEM_CPY(&pstCallEntity->stCalledNumber,
               &pstOrig->stDialNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    PS_MEM_CPY(&pstCallEntity->stCalledSubAddr,
               &pstOrig->stSubaddr,
               sizeof(MN_CALL_SUBADDR_STRU));

    /* 呼叫号码加号转换 */
    TAF_XCALL_TranlatePlusToCallNum(pstCallEntity);

    pstCallEntity->stRedirectNumber.ucNumLen    = 0;
    pstCallEntity->stConnectNumber.ucNumLen     = 0;

    return;
}
VOS_VOID TAF_XCALL_CreateMtCallEntity(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    /* 此处不再判断call id的有效性，根据传入的call id分配呼叫实体 */
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 记录发起call业务用户的信息(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               ulModuleId,
                               MN_CLIENT_ID_BROADCAST,
                               0);


    /* 更新SO */
    pstCallEntity->enSo               = pstIncomingCallInd->enSo;

    /* 更新By pass Flag */
    pstCallEntity->ucIsAlertAnsByPass = pstIncomingCallInd->ucIsAlertAnsByPass;

    /* 更新Connect Reference */
    pstCallEntity->ucConRef           = pstIncomingCallInd->ucConRef;

    /* 更新Connect Id */
    pstCallEntity->ucConnectId        = pstIncomingCallInd->ucConnectId;

    /* 更新呼叫状态 */
    pstCallEntity->enCallState        = MN_CALL_S_INCOMING;

    /* 更新呼叫类型 */
    pstCallEntity->enCallType         = MN_CALL_TYPE_VOICE;

    /* 更新发起呼叫Dir */
    pstCallEntity->enCallDir          = MN_CALL_DIR_MT;

    /* 更新来电号码 */
    TAF_XCALL_UpdateCallingNum(ucCallId, &(pstIncomingCallInd->stCallingPartyNum));

    return;
}


VOS_VOID TAF_XCALL_FreeCallEntity(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_InitSpecCallEntity(ucCallId);
}


VOS_VOID TAF_XCALL_UpdateClientInfo(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stClientInfo.ulModuleId = ulModuleId;
    pstCallEntity->stClientInfo.usClientId = usClientId;
    pstCallEntity->stClientInfo.ucOpId     = ucOpId;

    return;
}


VOS_VOID TAF_XCALL_UpdateCallState(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallState = enCallState;

    return;
}


VOS_VOID TAF_XCALL_UpdateCallType(
    VOS_UINT8                           ucCallId,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallType = enCallType;
}


VOS_VOID TAF_XCALL_UpdateCallDir(
    VOS_UINT8                           ucCallId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallDir = enCallDir;
}



VOS_VOID TAF_XCALL_UpdateSo(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enSo = enSo;
}


VOS_VOID TAF_XCALL_UpdateConnectId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity              = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucConnectId = ucConnectId;
}


VOS_VOID TAF_XCALL_UpdateConnectRef(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity           = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucConRef = ucConRef;
}


VOS_VOID TAF_XCALL_UpdateAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsAlertAnsByPass
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucIsAlertAnsByPass = ucIsAlertAnsByPass;
}


VOS_VOID TAF_XCALL_UpdateCcCause(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCcCause
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCause            = enCcCause;
}


VOS_VOID TAF_XCALL_UpdateDiscCallDir(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsUser
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    if (VOS_TRUE == pstCallEntity->stDiscDir.ucDiscCallFlag)
    {
        return;
    }

    pstCallEntity->stDiscDir.ucIsUser       = ucIsUser;
    pstCallEntity->stDiscDir.ucDiscCallFlag = VOS_TRUE;

    return;
}


VOS_VOID TAF_XCALL_UpdateCallingNum(
    VOS_UINT8                                               ucCallId,
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           aucDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* num type:
        bit7 | bit6 bit5 bit4 | bit3 bit2 bit1 bit0
          1  |     num type   |    num plan
     */
    pstCallEntity->stCallNumber.enNumType = 0x80 | (VOS_UINT8)(pstXccCallNum->enNumType << 4) | (pstXccCallNum->enNumPlan& 0x0F);

    pstCallEntity->ucPi                   = pstXccCallNum->ucPi;
    pstCallEntity->ucSi                   = pstXccCallNum->ucSi;

    PS_MEM_CPY(aucDigit, pstXccCallNum->aucDigit, TAF_XCALL_MIN(pstXccCallNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN));

    (VOS_VOID)TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)aucDigit,
                                    pstCallEntity->stCallNumber.aucBcdNum,
                                    &(pstCallEntity->stCallNumber.ucNumLen));

    return;
}


TAF_XCALL_SUPS_CMD_MGMT_STRU* TAF_XCALL_GetSupsCmdMgmt(VOS_VOID)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->stSupsCmdMgmt);

}


TAF_XCALL_CLIENT_INFO_STRU* TAF_XCALL_GetClientInfo(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return &(pstCallEntity->stClientInfo);
}


MN_CALL_STATE_ENUM_U8 TAF_XCALL_GetCallState(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCallState;
}


TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_GetSo(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enSo;
}


MN_CALL_TYPE_ENUM_U8 TAF_XCALL_GetCallType(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCallType;
}



VOS_UINT8 TAF_XCALL_GetAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->ucIsAlertAnsByPass;
}


TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_GetCcCause(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCause;
}


VOS_UINT32 TAF_XCALL_GetCallIdFromConnectId(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                          *pucCallId
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (ucConnectId == pstXcallCtx->astCallEntity[i].ucConnectId))
        {
            *pucCallId = (VOS_UINT8)(i + 1);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID TAF_XCALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    *pulNumOfCalls = 0;

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (enCallState == pstXcallCtx->astCallEntity[i].enCallState))
        {
            *pucCallIds++ = (VOS_UINT8)(i + 1);
            (*pulNumOfCalls)++;
        }
    }
}


VOS_VOID TAF_XCALL_GetNotIdleStateCalls(
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    *pulNumOfCalls = 0;

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (MN_CALL_S_IDLE != pstXcallCtx->astCallEntity[i].enCallState))
        {
            *pucCallIds++ = (VOS_UINT8)(i + 1);
            (*pulNumOfCalls)++;
        }
    }
}


TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_MapXccCauseToCsCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astTafXcallErrCodeMapTbl)/sizeof(TAF_XCALL_CS_ERR_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astTafXcallErrCodeMapTbl[ulCnt].enXccCause == enXccCause)
        {
            return g_astTafXcallErrCodeMapTbl[ulCnt].enCsCause;
        }
    }

    return TAF_CS_CAUSE_UNKNOWN;
}


VOS_UINT32 TAF_XCALL_ExistCallInstance(VOS_VOID)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_XCALL_RegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
)
{
    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    if (pstSupsCmdMgmt->ucNumOfKeyEvt >= TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM)
    {
        return;
    }

    for (i = 0; i < pstSupsCmdMgmt->ucNumOfKeyEvt; i++)
    {
        /* 该call id对应的事件已存在 */
        if (pstSupsCmdMgmt->astKeyEvts[i].ucCallId == ucCallId)
        {
            pstSupsCmdMgmt->astKeyEvts[i].enEvt      = enEvt;
            pstSupsCmdMgmt->astKeyEvts[i].enSubseqOp = enSubseqOp;
            return;
        }
    }

    /* 添加一个关注事件, 根据输入参数填写事件内容 */
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].ucCallId   = ucCallId;
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].enEvt      = enEvt;
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].enSubseqOp = enSubseqOp;

    pstSupsCmdMgmt->ucNumOfKeyEvt++;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    return;
}


VOS_VOID TAF_XCALL_DeRegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
)
{
    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    ucNumOfKeyEvt  = pstSupsCmdMgmt->ucNumOfKeyEvt;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    /* 查找对应关注的事件 */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if ((ucCallId == pstSupsCmdMgmt->astKeyEvts[i].ucCallId)
           &&(enEvt == pstSupsCmdMgmt->astKeyEvts[i].enEvt))
        {
            break;
        }
    }

    if (i >= ucNumOfKeyEvt)
    {
        return;
    }

    PS_MEM_CPY(&(pstSupsCmdMgmt->astKeyEvts[i]),
               &(pstSupsCmdMgmt->astKeyEvts[i + 1]),
               ((ucNumOfKeyEvt - i) - 1) * sizeof(TAF_XCALL_SUPS_CMD_KEY_EVT_STRU));

    pstSupsCmdMgmt->ucNumOfKeyEvt--;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();
}
VOS_VOID TAF_XCALL_GetSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                   *penEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                      *penSubseqOp
)
{

    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    ucNumOfKeyEvt  = pstSupsCmdMgmt->ucNumOfKeyEvt;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    /* 查找对应关注的事件 */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if (ucCallId == pstSupsCmdMgmt->astKeyEvts[i].ucCallId)
        {
            *penEvt      = pstSupsCmdMgmt->astKeyEvts[i].enEvt;
            *penSubseqOp = pstSupsCmdMgmt->astKeyEvts[i].enSubseqOp;
            return;
        }
    }

    *penEvt      = TAF_XCALL_SS_PROG_EVT_BUTT;
    *penSubseqOp = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    return;
}

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, begin */
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */

VOS_VOID TAF_XCALL_SetWaitForXCCDTMFCnfFlag(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enWaitForXCCDTMFCnfFlag = enWaitForXCCDTMFCnfFlag;

    return;
}


TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8 TAF_XCALL_GetWaitForXCCDTMFCnfFlag(
    VOS_UINT8       ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enWaitForXCCDTMFCnfFlag;
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, end */

VOS_UINT32 TAF_XCALL_IsMtCallInstanceExist(VOS_VOID)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE       == pstXcallCtx->astCallEntity[i].ulUsed)
         && (MN_CALL_DIR_MT == pstXcallCtx->astCallEntity[i].enCallDir))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


MN_CALL_DIR_ENUM_U8 TAF_XCALL_GetCallDir(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    MN_CALL_DIR_ENUM_U8                 enCallDir;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    enCallDir = pstCallEntity->enCallDir;

    return enCallDir;
}



#if 0

VOS_VOID TAF_XCALL_TranlateCallNumToPlus(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
)
{
    VOS_UINT16                                              usCurMcc;
    MN_CALL_NUM_TYPE_ENUM_U8                                enCurNumType;
    VOS_UINT8                                               aucCurCallBcdNum[TAF_MT_MAX_BCD_NUM_LEN];
    VOS_UINT8                                               ucCurCallBcdNumLen;
    VOS_INT8                                                acCurCallAsciiNum[TAF_MT_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucCurCallAsciiNumLen;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;

    /*获取mcc */
    pstSdc1xSysInfo      = TAF_SDC_Get1xSysInfo();
    usCurMcc             = pstSdc1xSysInfo->stServiceInfo.usMcc;

    /* 获取BCD号码长度 */
    ucCurCallBcdNumLen   = pstCallEntity->stCallNumber.ucNumLen;

    /* 获取号码类型*/
    enCurNumType         = pstCallEntity->stCallNumber.enNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    PS_MEM_CPY(aucCurCallBcdNum, pstCallEntity->stCallNumber.aucBcdNum, sizeof(aucCurCallBcdNum));

    /*将BCD码呼叫格式的号码转换为ASCII格式 */
    PS_MEM_SET(acCurCallAsciiNum, 0, sizeof(acCurCallAsciiNum));
    TAF_STD_ConvertBcdNumberToAscii(aucCurCallBcdNum, ucCurCallBcdNumLen, acCurCallAsciiNum);

    /*语音模式下，加号转换处理 */
    ucCurCallAsciiNumLen  = (VOS_UINT8)VOS_StrLen(acCurCallAsciiNum);
    TAF_TranslateNumToPlus(usCurMcc, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCallAsciiNum, &ucCurCallAsciiNumLen);

    /*将ASCII呼叫格式的号码转换为BCD码 */
    ucCurCallBcdNumLen    = 0;
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    TAF_STD_ConvertAsciiNumberToBcd(acCurCallAsciiNum, aucCurCallBcdNum, &ucCurCallBcdNumLen);

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pstCallEntity->stCallNumber.aucBcdNum, aucCurCallBcdNum, sizeof(aucCurCallBcdNum));
    pstCallEntity->stCallNumber.ucNumLen  = ucCurCallBcdNumLen;
    pstCallEntity->stCallNumber.enNumType = enCurNumType;

    return;
}
#endif

VOS_VOID TAF_XCALL_TranlatePlusToCallNum(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
)
{
    VOS_UINT16                                              usCurMcc;
    MN_CALL_NUM_TYPE_ENUM_U8                                enCurNumType;
    VOS_UINT8                                               aucCurCalledBcdNum[TAF_MO_MAX_BCD_NUM_LEN];
    VOS_UINT8                                               aucCurCalledBcdNumLen;
    VOS_INT8                                                acCurCalledAsciiNum[TAF_MO_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucCurCalledAsciiNumLen;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;


    /*获取mcc */
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();
    usCurMcc          = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);

    /* 获取BCD号码长度 */
    aucCurCalledBcdNumLen = pstCallEntity->stCalledNumber.ucNumLen;

    /* 获取号码类型*/
    enCurNumType      = pstCallEntity->stCalledNumber.enNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));
    PS_MEM_CPY(aucCurCalledBcdNum, pstCallEntity->stCalledNumber.aucBcdNum, sizeof(aucCurCalledBcdNum));

    /*将BCD码呼叫格式的号码转换为ASCII格式 */
    PS_MEM_SET(acCurCalledAsciiNum, 0, sizeof(acCurCalledAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(aucCurCalledBcdNum, aucCurCalledBcdNumLen, (VOS_CHAR*)acCurCalledAsciiNum))
    {
        return;
    }

    /*语音模式下，加号转换处理 */
    ucCurCalledAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)acCurCalledAsciiNum);
    TAF_TranslatePlusToNum(usCurMcc, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCalledAsciiNum, &ucCurCalledAsciiNumLen);

    /*将ASCII呼叫格式的号码转换为BCD码 */
    aucCurCalledBcdNumLen = 0;
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));

    (VOS_VOID)TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)acCurCalledAsciiNum, aucCurCalledBcdNum, &aucCurCalledBcdNumLen);

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pstCallEntity->stCalledNumber.aucBcdNum, aucCurCalledBcdNum, sizeof(aucCurCalledBcdNum));
    pstCallEntity->stCalledNumber.ucNumLen  = aucCurCalledBcdNumLen;
    pstCallEntity->stCalledNumber.enNumType = enCurNumType;

    return;
}


VOS_VOID TAF_XCALL_GetEccNumList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx = VOS_NULL_PTR;

    pstEccNumInfo->ulEccNumCount = 0;

    /* 卡中存在号码，则先将卡中的号码放入上报内容中 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetSimStatus())
    {
        pstUcimEccNumList = TAF_SDC_Get1xCallUcimEmccNumList();

        for (i = 0; i < TAF_XCALL_MIN(pstUcimEccNumList->ucEccNumCount, TAF_SDC_MAX_UCIM_ECC_NUM); i++)
        {
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc              = 0xffffffff;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory = 0;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent  = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen        = pstUcimEccNumList->astUcimEccNumList[i].ucEccNumLen;
            VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                       pstUcimEccNumList->astUcimEccNumList[i].aucEccNum,
                       USIM_ECC_LEN);
            pstEccNumInfo->ulEccNumCount++;

        }
    }

    /* 列表未满,将APP定制的紧急呼号码加入消息 */
    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();
    if (pstEccNumInfo->ulEccNumCount < MN_CALL_MAX_EMC_NUM)
    {
        for (i = 0; i < TAF_XCALL_MIN(pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount,TAF_SDC_MAX_CUSTOM_ECC_NUM); i++)
        {
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc
                = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ulMcc;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory
                = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent
                = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen
                = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

            VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                       pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);

            pstEccNumInfo->ulEccNumCount++;

        }

    }

}

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, begin */
/* 1. Buffer操作函数从XCallProcApp挪到XCallCtx.c中
   2. Cont DTMF和BURST DTMF消息公用一个缓存
*/
/*****************************************************************************
 函 数 名  : TAF_XCALL_GetDtmfBufCnt
 功能描述  : 获取CALL模块BURST DTMF和CONT DTMF的缓存个数
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8 ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->stDtmfBuffer.ucDtmfCnt;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IncrementDtmfBufCnt
 功能描述  : CALL模块DTMF的缓存个数自增1
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一

*****************************************************************************/
VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt++;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_DecrementDtmfBufCnt
 功能描述  : CALL模块DTMF的缓存个数自检1
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt--;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetDtmfBuffListHead
 功能描述  : 获取CALL模块DTMF的缓存的头结点
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : HI_LIST_S
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return &(pstCallEntity->stDtmfBuffer.stList);
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_DelDtmfNode
 功能描述  : 删除DTMF缓存链表中的节点
 输入参数  : pstNode    -- 需要删除DTMF缓存链表中的节点
           : ucCallId   -- Call 实例号
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
)
{
    /* 从过滤表中删除节点 */
    msp_list_del(&pstNode->stList);

    /* 释放节点内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNode);

    TAF_XCALL_DecrementDtmfBufCnt(ucCallId);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_AddBurstDtmfInfo
 功能描述  : 增加DTMF信息到DTMF缓存
 输入参数  : pstDtmfInfo   -- 新增的DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    /* 申请过滤表节点内存 */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stBurstDtmf, &pstBurstDtmfInfo->stBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_BURST_DTMF_REQ;

    /* 将节点增加到DTMF缓存链表中 */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/

}
/*****************************************************************************
 函 数 名  : TAF_XCALL_SaveBurstDtmfInfo
 功能描述  : 将DTMF信息保存到DTMF缓存中
 输入参数  : pstDtmfInfo    -- 需要保存到缓存中的DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8             enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* 判断缓存是否已经满了 */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveBurstDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* 将BURST DTMF信息保存到缓存中 */
    enResult = TAF_XCALL_AddBurstDtmfInfo(pstBurstDtmfInfo);
    if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* 将DTMF的缓存个数加一 */
    TAF_XCALL_IncrementDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_CleanDtmfBuff
 功能描述  : 重置DTM缓存信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId)
{
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstHead     = VOS_NULL_PTR;
    TAF_XCALL_DTMF_NODE_STRU           *pstNode     = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallCtx = VOS_NULL_PTR;

   /* 如果没有缓存，则直接退出 */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* 释放缓存内存 */
    /*lint -e961*/
    /* 循环遍历过滤表，并释放过滤表的所有节点 */
    pstHead = TAF_XCALL_GetDtmfBuffListHead(ucCallId);
    msp_list_for_each_safe(pstMe, pstTmp, pstHead)
    /*lint +e961*/
    {
        /*lint -e961*/
        pstNode = msp_list_entry(pstMe, TAF_XCALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        if (TAF_CALL_APP_SEND_BURST_DTMF_REQ == pstNode->enMsgType)
        {
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stBurstDtmf.ucCallId);

            /* 重置时，需要给缓存中的所有BURST DTMF信息回复正式响应 */
            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);

            /* 重置时，需要给缓存中的所有CONT DTMF信息回复正式响应 */
            TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                      pstXcallCtx->stClientInfo.ucOpId,
                                      VOS_ERR);
        }
        else /* 目前只缓存CONT DTMF和BURST DTMF,其它类型错误 */
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_CleanDtmfBuff: Node MsgType Error ", pstNode->enMsgType);
        }

        /* 从过滤表中删除节点 */
        TAF_XCALL_DelDtmfNode(pstNode, ucCallId);
    }

    return;
}
VOS_VOID TAF_XCALL_ProcDtmfBuffer(VOS_UINT8 ucCallId)
{
    TAF_XCALL_DTMF_NODE_STRU           *pstNode             = VOS_NULL_PTR;
    TAF_CALL_BURST_DTMF_PARA_STRU       stBurstDtmfCurInfo;
    TAF_CALL_CONT_DTMF_PARA_STRU        stContDtmfCurInfo;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallCtx;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstHead     = VOS_NULL_PTR;

    /* 如果没有缓存，则直接退出 */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* 如果需处理DTMF缓存，且状态不为ACTIVE，则清缓存 */
    if (MN_CALL_S_ACTIVE != TAF_XCALL_GetCallState(ucCallId))
    {
        /* 清DTMF缓存 */
        TAF_XCALL_CleanDtmfBuff(ucCallId);
        return;
     }

    /*lint -e961*/
    /* 循环遍历过滤表，并释放过滤表的所有节点 */
    pstHead = TAF_XCALL_GetDtmfBuffListHead(ucCallId);

    msp_list_for_each_safe(pstMe, pstTmp, pstHead)
    /*lint +e961*/
    {
        /*lint -e961*/
        pstNode     = msp_list_entry(pstMe, TAF_XCALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        /* 下一条NODE可能是BURST DTMF或CONT DTMF，根据类型进入不同处理分支 */
        if (TAF_CALL_APP_SEND_BURST_DTMF_REQ == pstNode->enMsgType)
        {
            /* 如果两个callid 不一致，则继续查找 */
            if(ucCallId != pstNode->unDtmf.stBurstDtmf.ucCallId)
            {
                /* 同一Call实例下的缓存链表中保存的消息的call id必定相同。如果不同，属于异常 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stBurstDtmf.ucCallId);
                TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);
                continue;
            }

            PS_MEM_CPY(&stBurstDtmfCurInfo, &pstNode->unDtmf.stBurstDtmf, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

            /* 从过滤表中删除节点 */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);

            if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccBurstDTMFReq(&stBurstDtmfCurInfo))
            {
                /* 发送成功，设置标识位为VOS_TRUE,直接退出循环 */
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stBurstDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF);
                break;
            }

            /* 发送失败，从call id对应的实体中获取信息，回复失败的结果，继续处理下一条缓存 */
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(stBurstDtmfCurInfo.ucCallId);

            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            /* 如果两个callid 不一致，则继续查找 */
            if (ucCallId != pstNode->unDtmf.stContDtmf.ucCallId)
            {
                /* 同一Call实例下的缓存链表中保存的消息的call id必定相同。如果不同，属于异常 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);
                TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

                continue;
            }

            PS_MEM_CPY(&stContDtmfCurInfo, &pstNode->unDtmf.stContDtmf, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

            /* 从过滤表中删除节点 */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

            if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccContDTMFReq(&stContDtmfCurInfo))
            {
                /* 发送成功，设置标识位为VOS_TRUE,直接退出循环 */
                if (TAF_CALL_CONT_DTMF_START == stContDtmfCurInfo.enSwitch)
                {
                    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stContDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF);
                }
                else
                {
                    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stContDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF);
                }

                break;
            }

            /* 发送失败，从call id对应的实体中获取信息，回复失败的结果，继续处理下一条缓存 */
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(stContDtmfCurInfo.ucCallId);

            TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                      pstXcallCtx->stClientInfo.ucOpId,
                                      VOS_ERR);
        }
        else
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcBurstDtmfBuffer: Node MsgType Error ", pstNode->enMsgType);

            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);
        }
    }

    return;
}
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, end */

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/*****************************************************************************
 函 数 名  : TAF_XCALL_AddContDtmfInfo
 功能描述  : 增加CONT DTMF信息到DTMF缓存
 输入参数  : pstContDtmfInfo   -- 新增的CONT DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新生成函数
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstContDtmfInfo->stContDTMFPara.ucCallId);

    /* 申请过滤表节点内存 */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stContDtmf, &pstContDtmfInfo->stContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_CONT_DTMF_REQ;

    /* 将节点增加到 DTMF缓存链表中 */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SaveContDtmfInfo
 功能描述  : 将CONT DTMF信息保存到CONT DTMF缓存中
 输入参数  : pstContDtmfInfo    -- 需要保存到缓存中的CONT DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新生成函数
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8              enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* 判断缓存是否已经满了 */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstContDtmfInfo->stContDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveContDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* 将CONT DTMF信息保存到缓存中 */
    enResult = TAF_XCALL_AddContDtmfInfo(pstContDtmfInfo);
    if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* 将CONT DTMF的缓存个数加一 */
    TAF_XCALL_IncrementDtmfBufCnt(pstContDtmfInfo->stContDTMFPara.ucCallId);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
}

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */


VOS_UINT32 TAF_XCALL_GetStartAndStopContDtmfIntervalLen(VOS_VOID)
{
    return TAF_XCALL_GetConfigInfo()->ulStartAndStopContDtmfIntervalLen;
}


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





