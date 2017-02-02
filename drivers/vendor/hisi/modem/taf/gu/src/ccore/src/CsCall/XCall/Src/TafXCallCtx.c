

/*****************************************************************************
  1 ͷ�ļ�����
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
  2 ȫ�ֱ�������
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
  3 ��������
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

    /* ��ʼ������ʵ�� */
    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        TAF_XCALL_InitSpecCallEntity(ucCallId);
    }

    /* ��ʼ��sups mgmt */
    PS_MEM_SET(&(pstXcallCtx->stSupsCmdMgmt), 0, sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* ��ʼ��configure */
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
    /* ���ҿ��е�CALL ID��������µĺ��� */
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        /* �����δ�����ʵ�壬���ص�Call id ��ֵΪʵ�������±�ֵ��1 */
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
    /* Ŀǰ�����ز��Ѿ�ʵ��,����״̬���ж����ﲻ��Ҫ */

    /* �����Ϊ�������ҵ�ǰ����һ·������������,���еľ���״̬��XCC
       �����ж��ܷ��� */
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        if (VOS_TRUE == TAF_XCALL_IsMtCallInstanceExist())
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* �������Ч���ܾ���ͨ�� */
        if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
        {
            return VOS_FALSE;
        }
    }

    /* ��ǰ��������Ϊnormal callʱ�����к���ʵ�嶼����IDLE̬,���Է����º��� */
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
    /* ����CALL ID�������ʵ�� */
    MN_CALL_ORIG_PARAM_STRU            *pstOrig       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstOrig       = &pstCallPara->unParm.stOrig;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* ��¼����callҵ���û�����Ϣ(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               pstCallPara->ulSenderPid,
                               pstCallPara->clientId,
                               pstCallPara->opId);
    /* ��ʼ�����в��� */
    pstCallEntity->enCallDir            = MN_CALL_DIR_MO;
    pstCallEntity->enCallState          = MN_CALL_S_DIALING;
    pstCallEntity->enCallType           = pstOrig->enCallType;
    pstCallEntity->enCause              = TAF_CS_CAUSE_SUCCESS;
    pstCallEntity->ucConnectId          = 0;
    pstCallEntity->ucConRef             = 0;
    pstCallEntity->enSo                 = TAF_XCALL_GetConfigInfo()->enSoInitType;
    pstCallEntity->ucIsAlertAnsByPass   = VOS_FALSE;


    /* ��ʼ�����к��� */
    PS_MEM_CPY(&pstCallEntity->stCalledNumber,
               &pstOrig->stDialNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    PS_MEM_CPY(&pstCallEntity->stCalledSubAddr,
               &pstOrig->stSubaddr,
               sizeof(MN_CALL_SUBADDR_STRU));

    /* ���к���Ӻ�ת�� */
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

    /* �˴������ж�call id����Ч�ԣ����ݴ����call id�������ʵ�� */
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* ��¼����callҵ���û�����Ϣ(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               ulModuleId,
                               MN_CLIENT_ID_BROADCAST,
                               0);


    /* ����SO */
    pstCallEntity->enSo               = pstIncomingCallInd->enSo;

    /* ����By pass Flag */
    pstCallEntity->ucIsAlertAnsByPass = pstIncomingCallInd->ucIsAlertAnsByPass;

    /* ����Connect Reference */
    pstCallEntity->ucConRef           = pstIncomingCallInd->ucConRef;

    /* ����Connect Id */
    pstCallEntity->ucConnectId        = pstIncomingCallInd->ucConnectId;

    /* ���º���״̬ */
    pstCallEntity->enCallState        = MN_CALL_S_INCOMING;

    /* ���º������� */
    pstCallEntity->enCallType         = MN_CALL_TYPE_VOICE;

    /* ���·������Dir */
    pstCallEntity->enCallDir          = MN_CALL_DIR_MT;

    /* ����������� */
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
        /* ��call id��Ӧ���¼��Ѵ��� */
        if (pstSupsCmdMgmt->astKeyEvts[i].ucCallId == ucCallId)
        {
            pstSupsCmdMgmt->astKeyEvts[i].enEvt      = enEvt;
            pstSupsCmdMgmt->astKeyEvts[i].enSubseqOp = enSubseqOp;
            return;
        }
    }

    /* ���һ����ע�¼�, �������������д�¼����� */
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

    /* ���Ҷ�Ӧ��ע���¼� */
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

    /* ���Ҷ�Ӧ��ע���¼� */
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

    /*��ȡmcc */
    pstSdc1xSysInfo      = TAF_SDC_Get1xSysInfo();
    usCurMcc             = pstSdc1xSysInfo->stServiceInfo.usMcc;

    /* ��ȡBCD���볤�� */
    ucCurCallBcdNumLen   = pstCallEntity->stCallNumber.ucNumLen;

    /* ��ȡ��������*/
    enCurNumType         = pstCallEntity->stCallNumber.enNumType;

    /*��ȡ���к��� */
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    PS_MEM_CPY(aucCurCallBcdNum, pstCallEntity->stCallNumber.aucBcdNum, sizeof(aucCurCallBcdNum));

    /*��BCD����и�ʽ�ĺ���ת��ΪASCII��ʽ */
    PS_MEM_SET(acCurCallAsciiNum, 0, sizeof(acCurCallAsciiNum));
    TAF_STD_ConvertBcdNumberToAscii(aucCurCallBcdNum, ucCurCallBcdNumLen, acCurCallAsciiNum);

    /*����ģʽ�£��Ӻ�ת������ */
    ucCurCallAsciiNumLen  = (VOS_UINT8)VOS_StrLen(acCurCallAsciiNum);
    TAF_TranslateNumToPlus(usCurMcc, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCallAsciiNum, &ucCurCallAsciiNumLen);

    /*��ASCII���и�ʽ�ĺ���ת��ΪBCD�� */
    ucCurCallBcdNumLen    = 0;
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    TAF_STD_ConvertAsciiNumberToBcd(acCurCallAsciiNum, aucCurCallBcdNum, &ucCurCallBcdNumLen);

    /*��ת����ĺ�����Ϣд�� */
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


    /*��ȡmcc */
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();
    usCurMcc          = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);

    /* ��ȡBCD���볤�� */
    aucCurCalledBcdNumLen = pstCallEntity->stCalledNumber.ucNumLen;

    /* ��ȡ��������*/
    enCurNumType      = pstCallEntity->stCalledNumber.enNumType;

    /*��ȡ���к��� */
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));
    PS_MEM_CPY(aucCurCalledBcdNum, pstCallEntity->stCalledNumber.aucBcdNum, sizeof(aucCurCalledBcdNum));

    /*��BCD����и�ʽ�ĺ���ת��ΪASCII��ʽ */
    PS_MEM_SET(acCurCalledAsciiNum, 0, sizeof(acCurCalledAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(aucCurCalledBcdNum, aucCurCalledBcdNumLen, (VOS_CHAR*)acCurCalledAsciiNum))
    {
        return;
    }

    /*����ģʽ�£��Ӻ�ת������ */
    ucCurCalledAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)acCurCalledAsciiNum);
    TAF_TranslatePlusToNum(usCurMcc, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCalledAsciiNum, &ucCurCalledAsciiNumLen);

    /*��ASCII���и�ʽ�ĺ���ת��ΪBCD�� */
    aucCurCalledBcdNumLen = 0;
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));

    (VOS_VOID)TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)acCurCalledAsciiNum, aucCurCalledBcdNum, &aucCurCalledBcdNumLen);

    /*��ת����ĺ�����Ϣд�� */
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

    /* ���д��ں��룬���Ƚ����еĺ�������ϱ������� */
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

    /* �б�δ��,��APP���ƵĽ��������������Ϣ */
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
/* 1. Buffer����������XCallProcAppŲ��XCallCtx.c��
   2. Cont DTMF��BURST DTMF��Ϣ����һ������
*/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetDtmfBufCnt
 ��������  : ��ȡCALLģ��BURST DTMF��CONT DTMF�Ļ������
 �������  : VOS_UINT8   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸�,Cont DTMF��Burst DTMF�����һ
*****************************************************************************/
VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8 ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->stDtmfBuffer.ucDtmfCnt;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IncrementDtmfBufCnt
 ��������  : CALLģ��DTMF�Ļ����������1
 �������  : VOS_UINT8   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸�,Cont DTMF��Burst DTMF�����һ

*****************************************************************************/
VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt++;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_DecrementDtmfBufCnt
 ��������  : CALLģ��DTMF�Ļ�������Լ�1
 �������  : VOS_UINT8   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸�,Cont DTMF��Burst DTMF�����һ
*****************************************************************************/
VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt--;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetDtmfBuffListHead
 ��������  : ��ȡCALLģ��DTMF�Ļ����ͷ���
 �������  : VOS_UINT8   ucCallId
 �������  : ��
 �� �� ֵ  : HI_LIST_S
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF��Burst DTMF�����һ
*****************************************************************************/
HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return &(pstCallEntity->stDtmfBuffer.stList);
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_DelDtmfNode
 ��������  : ɾ��DTMF���������еĽڵ�
 �������  : pstNode    -- ��Ҫɾ��DTMF���������еĽڵ�
           : ucCallId   -- Call ʵ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF ��Burst DTMF�����һ
*****************************************************************************/
VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
)
{
    /* �ӹ��˱���ɾ���ڵ� */
    msp_list_del(&pstNode->stList);

    /* �ͷŽڵ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNode);

    TAF_XCALL_DecrementDtmfBufCnt(ucCallId);

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_AddBurstDtmfInfo
 ��������  : ����DTMF��Ϣ��DTMF����
 �������  : pstDtmfInfo   -- ������DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF��Burst DTMF�����һ
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    /* ������˱�ڵ��ڴ� */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stBurstDtmf, &pstBurstDtmfInfo->stBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_BURST_DTMF_REQ;

    /* ���ڵ����ӵ�DTMF���������� */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/

}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SaveBurstDtmfInfo
 ��������  : ��DTMF��Ϣ���浽DTMF������
 �������  : pstDtmfInfo    -- ��Ҫ���浽�����е�DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF ��Burst DTMF�����һ
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8             enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* �жϻ����Ƿ��Ѿ����� */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveBurstDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* ��BURST DTMF��Ϣ���浽������ */
    enResult = TAF_XCALL_AddBurstDtmfInfo(pstBurstDtmfInfo);
    if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* ��DTMF�Ļ��������һ */
    TAF_XCALL_IncrementDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CleanDtmfBuff
 ��������  : ����DTM������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF ��Burst DTMF�����һ
*****************************************************************************/
VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId)
{
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstHead     = VOS_NULL_PTR;
    TAF_XCALL_DTMF_NODE_STRU           *pstNode     = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallCtx = VOS_NULL_PTR;

   /* ���û�л��棬��ֱ���˳� */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* �ͷŻ����ڴ� */
    /*lint -e961*/
    /* ѭ���������˱����ͷŹ��˱�����нڵ� */
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

            /* ����ʱ����Ҫ�������е�����BURST DTMF��Ϣ�ظ���ʽ��Ӧ */
            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);

            /* ����ʱ����Ҫ�������е�����CONT DTMF��Ϣ�ظ���ʽ��Ӧ */
            TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                      pstXcallCtx->stClientInfo.ucOpId,
                                      VOS_ERR);
        }
        else /* Ŀǰֻ����CONT DTMF��BURST DTMF,�������ʹ��� */
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_CleanDtmfBuff: Node MsgType Error ", pstNode->enMsgType);
        }

        /* �ӹ��˱���ɾ���ڵ� */
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

    /* ���û�л��棬��ֱ���˳� */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* ����账��DTMF���棬��״̬��ΪACTIVE�����建�� */
    if (MN_CALL_S_ACTIVE != TAF_XCALL_GetCallState(ucCallId))
    {
        /* ��DTMF���� */
        TAF_XCALL_CleanDtmfBuff(ucCallId);
        return;
     }

    /*lint -e961*/
    /* ѭ���������˱����ͷŹ��˱�����нڵ� */
    pstHead = TAF_XCALL_GetDtmfBuffListHead(ucCallId);

    msp_list_for_each_safe(pstMe, pstTmp, pstHead)
    /*lint +e961*/
    {
        /*lint -e961*/
        pstNode     = msp_list_entry(pstMe, TAF_XCALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        /* ��һ��NODE������BURST DTMF��CONT DTMF���������ͽ��벻ͬ�����֧ */
        if (TAF_CALL_APP_SEND_BURST_DTMF_REQ == pstNode->enMsgType)
        {
            /* �������callid ��һ�£���������� */
            if(ucCallId != pstNode->unDtmf.stBurstDtmf.ucCallId)
            {
                /* ͬһCallʵ���µĻ��������б������Ϣ��call id�ض���ͬ�������ͬ�������쳣 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stBurstDtmf.ucCallId);
                TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);
                continue;
            }

            PS_MEM_CPY(&stBurstDtmfCurInfo, &pstNode->unDtmf.stBurstDtmf, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

            /* �ӹ��˱���ɾ���ڵ� */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);

            if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccBurstDTMFReq(&stBurstDtmfCurInfo))
            {
                /* ���ͳɹ������ñ�ʶλΪVOS_TRUE,ֱ���˳�ѭ�� */
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stBurstDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF);
                break;
            }

            /* ����ʧ�ܣ���call id��Ӧ��ʵ���л�ȡ��Ϣ���ظ�ʧ�ܵĽ��������������һ������ */
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(stBurstDtmfCurInfo.ucCallId);

            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            /* �������callid ��һ�£���������� */
            if (ucCallId != pstNode->unDtmf.stContDtmf.ucCallId)
            {
                /* ͬһCallʵ���µĻ��������б������Ϣ��call id�ض���ͬ�������ͬ�������쳣 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);
                TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

                continue;
            }

            PS_MEM_CPY(&stContDtmfCurInfo, &pstNode->unDtmf.stContDtmf, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

            /* �ӹ��˱���ɾ���ڵ� */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

            if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccContDTMFReq(&stContDtmfCurInfo))
            {
                /* ���ͳɹ������ñ�ʶλΪVOS_TRUE,ֱ���˳�ѭ�� */
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

            /* ����ʧ�ܣ���call id��Ӧ��ʵ���л�ȡ��Ϣ���ظ�ʧ�ܵĽ��������������һ������ */
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
 �� �� ��  : TAF_XCALL_AddContDtmfInfo
 ��������  : ����CONT DTMF��Ϣ��DTMF����
 �������  : pstContDtmfInfo   -- ������CONT DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstContDtmfInfo->stContDTMFPara.ucCallId);

    /* ������˱�ڵ��ڴ� */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stContDtmf, &pstContDtmfInfo->stContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_CONT_DTMF_REQ;

    /* ���ڵ����ӵ� DTMF���������� */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SaveContDtmfInfo
 ��������  : ��CONT DTMF��Ϣ���浽CONT DTMF������
 �������  : pstContDtmfInfo    -- ��Ҫ���浽�����е�CONT DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8              enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* �жϻ����Ƿ��Ѿ����� */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstContDtmfInfo->stContDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveContDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* ��CONT DTMF��Ϣ���浽������ */
    enResult = TAF_XCALL_AddContDtmfInfo(pstContDtmfInfo);
    if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* ��CONT DTMF�Ļ��������һ */
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





