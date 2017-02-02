

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallSndApp.h"
#include "AtMnInterface.h"
#include "NasStkInterface.h"
#include "TafXCallCtx.h"
#include "TafSdcCtx.h"

/* Added by y00307564 for CDMA Iteration 8 2015-2-15 begin */
#include "MmaAppLocal.h"
/* Added by y00307564 for CDMA Iteration 8 2015-2-15 end */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_APP_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_SndCsEvtToAt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usLength,
    VOS_VOID                           *pData
)
{
    MN_AT_IND_EVT_STRU                 *pstMsg     = VOS_NULL_PTR;
    TAF_UINT32                          ulTmpAddr;
    TAF_UINT16                          usEventTypeLen;
    TAF_UINT16                          usMsgLength;

    usEventTypeLen                     = sizeof(ulEvtId);

    usMsgLength = (VOS_UINT16)((sizeof(MN_AT_IND_EVT_STRU) + usLength) - 4 + usEventTypeLen);

    /* �����ڴ� */
    pstMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, usMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
         return;
    }

    /* �������ػ����ʵ��������pMsg->aucValue;*/
    pstMsg->ulReceiverPid              = WUEPS_PID_AT;
    pstMsg->usMsgName                  = (VOS_UINT16)MN_CALLBACK_CS_CALL;
    pstMsg->clientId                   = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);

    /* ��д����Ϣ���� */

    pstMsg->usLen                      = usMsgLength - VOS_MSG_HEAD_LENGTH;

    ulTmpAddr = (VOS_UINT32)pstMsg->aucContent;
    PS_MEM_CPY(pstMsg->aucContent, &ulEvtId, usEventTypeLen);
    PS_MEM_CPY((VOS_VOID *)(ulTmpAddr + usEventTypeLen),
               pData,
               usLength);

    /*������Ϣ��AT;*/
    PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID TAF_XCALL_SndCsEvtToStk(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulModuleId,
    MN_CALL_INFO_STRU                  *pstCallInfo
)
{
    MN_APP_CS_CALLINFO_MSG_STRU        *pstMsg;

    /* Ϊ�ظ�STK����ϢTAF_STK_CS_CALLINFO_EVENT_IND�����ڴ� */
    pstMsg   = (MN_APP_CS_CALLINFO_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                        sizeof(MN_APP_CS_CALLINFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid   = ulModuleId;
    pstMsg->ulMsgId         = TAF_STK_CS_CALLINFO_EVENT_IND;
    pstMsg->enEventType     = ulEvtId;
    pstMsg->ulLength        = sizeof(MN_APP_CS_CALLINFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY(&(pstMsg->stCsCallInfo), pstCallInfo, sizeof(MN_CALL_INFO_STRU));

    /*������Ϣ��STK;*/
    PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);

    return;
}
VOS_VOID TAF_XCALL_SndCallOrigCnf(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientid,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    MN_CALL_INFO_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId                 = usClientid;
    stCallInfo.opId                     = 0;

    /* ����ʱ���ϲ�ֻ��ע�����Ƿ�ɹ� */
    stCallInfo.enCause                  = enCause;
    stCallInfo.enCallType               = enCallType;
    stCallInfo.enVoiceDomain            = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ����MN_CALL_EVT_CALL_ORIG_CNF��Ϣ */
    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_CALL_ORIG_CNF,
                               usClientid,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_CALL_ORIG_CNF,
                                ulModuleId,
                                &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;

}



VOS_VOID TAF_XCALL_SndSupsCmdCnf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = usClientId;
    stCallInfo.opId          = ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCause       = enCause;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_SUPS_CMD_CNF,
                               usClientId,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_SUPS_CMD_CNF,
                                ulModuleId,
                                &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */
}
VOS_VOID TAF_XCALL_SndSupsResult(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = usClientId;
    stCallInfo.opId          = ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enSsResult    = enSsResult;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_SS_CMD_RSLT,
                               usClientId,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_SS_CMD_RSLT,
                                ulModuleId,
                                &stCallInfo);
    }
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;
}
VOS_VOID TAF_XCALL_SndCallIncomingInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCallState   = pstCallEntity->enCallState;

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_INCOMING,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_INCOMING,
                            MAPS_STK_PID,
                            &stCallInfo);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;
}
VOS_VOID TAF_XCALL_SndCallOrigInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = pstCallEntity->stClientInfo.usClientId;
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_ORIG,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_ORIG,
                            MAPS_STK_PID,
                            &stCallInfo);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;
}
VOS_VOID TAF_XCALL_SndCallConnectInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCallDir     = pstCallEntity->enCallDir;
    PS_MEM_CPY(&(stCallInfo.stConnectNumber), &(pstCallEntity->stConnectNumber), sizeof(MN_CALL_BCD_NUM_STRU));

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_CONNECT,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_CONNECT,
                            MAPS_STK_PID,
                            &stCallInfo);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;
}
VOS_VOID TAF_XCALL_SndCallReleaseInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCause       = pstCallEntity->enCause;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* TO DO: ulPreCallTime enNoCliCause */

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    /* release �㲥�ϱ� */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_RELEASED,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_RELEASED,
                            MAPS_STK_PID,
                            &stCallInfo);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    return;
}
VOS_VOID TAF_XCALL_SndCallAllReleaseInd(
    VOS_UINT32                          ulModuleId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    /* Ŀǰֻ��AT�������Ϣ���������ulModuleIdԤ�� */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_ALL_RELEASED,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    return;
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndBurstDTMFCnf
 ��������  : �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_CNF
 �������  : VOS_UINT16                                  usClientId,
             VOS_UINT8                                   ucOpId,
             TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 enResult,
             VOS_UINT8                                   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndBurstDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 enResult,
    VOS_UINT8                                   ucCallId
)
{
    TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU                   stSendBurstDTMFCnf;

    PS_MEM_SET(&stSendBurstDTMFCnf, 0 ,sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFCnf.enResult   = enResult;
    stSendBurstDTMFCnf.usClientId = usClientId;
    stSendBurstDTMFCnf.ucOpId     = ucOpId;
    stSendBurstDTMFCnf.ucCallId   = ucCallId;

    /* �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_BURST_DTMF_CNF,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU),
                          &stSendBurstDTMFCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndBurstDTMFRslt
 ��������  : �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_RSLT
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndBurstDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU   stSendBurstDTMFRslt;

    PS_MEM_SET(&stSendBurstDTMFRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFRslt.usClientId  = usClientId;
    stSendBurstDTMFRslt.ucOpId      = ucOpId;
    stSendBurstDTMFRslt.ucResult    = ucResult;

    /* �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_RSLT�� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU),
                           &stSendBurstDTMFRslt);
}
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */

VOS_VOID TAF_XCALL_SndFlashRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_FLASH_RSLT_STRU   stFlashRslt;

    PS_MEM_SET(&stFlashRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_FLASH_RSLT_STRU));

    /* ��д��Ϣ */
    stFlashRslt.ucResult   = ucResult;
    stFlashRslt.usClientId = usClientId;
    stFlashRslt.ucOpId     = ucOpId;

    /* �ϱ�TAF_CALL_EVT_SEND_FLASH_RSLT�¼� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_FLASH_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_FLASH_RSLT_STRU),
                           &stFlashRslt);

    return;
}


VOS_VOID TAF_XCALL_SndCalledNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU                   stCalledNum;

    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpCalledNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU */
    stCalledNum.usClientId = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCalledNum.ucOpId     = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stCalledNum.ucCallId   = pstInfoRecInd->ucCallId;
    stCalledNum.enNumType  = pstInfoRecInd->stCalledNumInfo.enNumType;
    stCalledNum.enNumPlan  = pstInfoRecInd->stCalledNumInfo.enNumPlan;
    stCalledNum.ucDigitNum = pstInfoRecInd->stCalledNumInfo.ucDigitNum;
    PS_MEM_CPY(stCalledNum.aucDigit,
               pstInfoRecInd->stCalledNumInfo.aucDigit,
               pstInfoRecInd->stCalledNumInfo.ucDigitNum);



    /* ����TAF_CALL_EVT_CALLED_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CALLED_NUM_INFO_IND,
                           stCalledNum.usClientId,
                           sizeof(XCC_XCALL_CONNECTED_NUM_INFO_STRU),
                           &stCalledNum);

    return;
}


VOS_VOID TAF_XCALL_SndCallingPratNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU  stCallingNum;

    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU */
    stCallingNum.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCallingNum.ucOpId      = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stCallingNum.ucCallId    = pstInfoRecInd->ucCallId;
    stCallingNum.ucPi        = pstInfoRecInd->stCallingNumInfo.ucPi;
    stCallingNum.ucSi        = pstInfoRecInd->stCallingNumInfo.ucSi;
    stCallingNum.enNumType   = pstInfoRecInd->stCallingNumInfo.enNumType;
    stCallingNum.enNumPlan   = pstInfoRecInd->stCallingNumInfo.enNumPlan;
    stCallingNum.ucDigitNum  = pstInfoRecInd->stCallingNumInfo.ucDigitNum;
    PS_MEM_CPY(stCallingNum.aucDigit,
               pstInfoRecInd->stCallingNumInfo.aucDigit,
               pstInfoRecInd->stCallingNumInfo.ucDigitNum);



    /* ����TAF_CALL_EVT_CALLING_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CALLING_NUM_INFO_IND,
                           stCallingNum.usClientId,
                           sizeof(TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU),
                           &stCallingNum);

    return;
}



VOS_VOID TAF_XCALL_SndConnNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU   stConnNum;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpConnNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU */
    stConnNum.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stConnNum.ucOpId      = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stConnNum.ucCallId    = pstInfoRecInd->ucCallId;
    stConnNum.enNumType   = pstInfoRecInd->stConnNumInfo.enNumType;
    stConnNum.enNumPlan   = pstInfoRecInd->stConnNumInfo.enNumPlan;
    stConnNum.ucPi        = pstInfoRecInd->stConnNumInfo.ucPi;
    stConnNum.ucSi        = pstInfoRecInd->stConnNumInfo.ucSi;
    stConnNum.ucDigitNum  = pstInfoRecInd->stConnNumInfo.ucDigitNum;
    PS_MEM_CPY(stConnNum.aucDigit,
               pstInfoRecInd->stConnNumInfo.aucDigit,
               pstInfoRecInd->stConnNumInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_CONN_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CONN_NUM_INFO_IND,
                           stConnNum.usClientId,
                           sizeof(TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU),
                           &stConnNum);

    return;
}


VOS_VOID TAF_XCALL_SndRedirNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU       stRedirNum;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpRedirNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU */
    stRedirNum.usClientId       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stRedirNum.ucOpId           = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stRedirNum.ucCallId         = pstInfoRecInd->ucCallId;
    stRedirNum.bitOpPi          = pstInfoRecInd->stRedirNumInfo.bitOpPi;
    stRedirNum.bitOpSi          = pstInfoRecInd->stRedirNumInfo.bitOpSi;
    stRedirNum.bitOpRedirReason = pstInfoRecInd->stRedirNumInfo.bitOpRedirReason;
    stRedirNum.enNumType        = pstInfoRecInd->stRedirNumInfo.enNumType;
    stRedirNum.enNumPlan        = pstInfoRecInd->stRedirNumInfo.enNumPlan;
    stRedirNum.ucPi             = pstInfoRecInd->stRedirNumInfo.ucPi;
    stRedirNum.ucSi             = pstInfoRecInd->stRedirNumInfo.ucSi;
    stRedirNum.ucRedirReason    = pstInfoRecInd->stRedirNumInfo.enRedirReason;
    stRedirNum.ucDigitNum       = pstInfoRecInd->stRedirNumInfo.ucDigitNum;
    PS_MEM_CPY(stRedirNum.aucDigitNum,
               pstInfoRecInd->stRedirNumInfo.aucDigit,
               pstInfoRecInd->stRedirNumInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_REDIR_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_REDIR_NUM_INFO_IND,
                           stRedirNum.usClientId,
                           sizeof(TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU),
                           &stRedirNum);

    return;
}


VOS_VOID TAF_XCALL_SndDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_DISPLAY_INFO_IND_STRU                      stDisPlayInfo;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpDisplayInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_DISPLAY_INFO_IND_STRU */
    stDisPlayInfo.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stDisPlayInfo.ucOpId      = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stDisPlayInfo.ucCallId   = pstInfoRecInd->ucCallId;
    stDisPlayInfo.ucDigitNum = pstInfoRecInd->stDisplayInfo.ucDigitNum;
    PS_MEM_CPY(stDisPlayInfo.aucDigit,
               pstInfoRecInd->stDisplayInfo.aucDigit,
               pstInfoRecInd->stDisplayInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_DISPLAY_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_DISPLAY_INFO_IND,
                           stDisPlayInfo.usClientId,
                           sizeof(TAF_CALL_EVT_DISPLAY_INFO_IND_STRU),
                           &stDisPlayInfo);

    return;
}


VOS_VOID TAF_XCALL_SndExtDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU                 *pstExtDisPlayInfo = VOS_NULL_PTR;

    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    VOS_UINT32                                              ulLoop;

    if (VOS_TRUE != pstInfoRecInd->bitOpExtDisplay)
    {
        return;
    }

    pstExtDisPlayInfo = (TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                        sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstExtDisPlayInfo)
    {
        return;
    }

    PS_MEM_SET(pstExtDisPlayInfo, 0, sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU));

    /* ���TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU */
    pstExtDisPlayInfo->usClientId        = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstExtDisPlayInfo->ucOpId            = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    pstExtDisPlayInfo->ucCallId          = pstInfoRecInd->ucCallId;
    pstExtDisPlayInfo->ucDisplayType     = pstInfoRecInd->stExtDisplayInfo.enDisplayType;
    pstExtDisPlayInfo->ucInfoRecsDataNum = pstInfoRecInd->stExtDisplayInfo.ucNumExtDispData;
    pstExtDisPlayInfo->ucExtDispInd      = pstInfoRecInd->stExtDisplayInfo.ucExtDispInd;
    for (ulLoop = 0; ulLoop < pstExtDisPlayInfo->ucInfoRecsDataNum; ulLoop++)
    {
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDispalyTag
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].enDisplayTag;
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDispalyLen
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDispalyLen;
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDigitNum
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDigitNum;
        PS_MEM_CPY(pstExtDisPlayInfo->aucInfoRecsData[ulLoop].aucDigit,
                   pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].aucDigit,
                   pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDigitNum);
    }

    /* ����TAF_CALL_EVT_EXT_DISPLAY_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND,
                           pstExtDisPlayInfo->usClientId,
                           sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU),
                           pstExtDisPlayInfo);


    PS_MEM_FREE(WUEPS_PID_TAF, pstExtDisPlayInfo);

    return;
}


VOS_VOID TAF_XCALL_SndLineCtrlInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU                    stLineCtrlInfo;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpLineCtrlInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU */
    stLineCtrlInfo.usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stLineCtrlInfo.ucOpId                    = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stLineCtrlInfo.ucCallId                  = pstInfoRecInd->ucCallId;
    stLineCtrlInfo.ucPolarityIncluded        = pstInfoRecInd->stLineCtrlInfo.ucPolarityIncluded;
    stLineCtrlInfo.ucToggleModePresent       = pstInfoRecInd->stLineCtrlInfo.ucToggleModePresent;
    stLineCtrlInfo.ucToggleMode              = pstInfoRecInd->stLineCtrlInfo.ucToggleMode;
    stLineCtrlInfo.ucReversePolarityPresent  = pstInfoRecInd->stLineCtrlInfo.ucReversePolarityPresent;
    stLineCtrlInfo.ucReversePolarity         = pstInfoRecInd->stLineCtrlInfo.ucReversePolarity;
    stLineCtrlInfo.ucPowerDenialTime         = pstInfoRecInd->stLineCtrlInfo.ucPowerDenialTime;

    /* ����TAF_CALL_EVT_LINE_CTRL_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_LINE_CTRL_INFO_IND,
                           stLineCtrlInfo.usClientId,
                           sizeof(TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU),
                           &stLineCtrlInfo);

    return;
}


VOS_VOID TAF_XCALL_SndSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_SIGNAL_INFO_IND_STRU   stSignalInfo;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpSignalInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_SIGNAL_INFO_IND_STRU */
    stSignalInfo.usClientId   = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stSignalInfo.ucOpId       = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stSignalInfo.ucCallId     = pstInfoRecInd->ucCallId;
    stSignalInfo.ucSignalType = pstInfoRecInd->stSignalInfo.ucSignalType;
    stSignalInfo.ucAlertPitch = pstInfoRecInd->stSignalInfo.ucAlertPitch;
    stSignalInfo.ucSignal     = pstInfoRecInd->stSignalInfo.ucSignal;

    /* ����TAF_CALL_EVT_SIGNAL_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SIGNAL_INFO_IND,
                           stSignalInfo.usClientId,
                           sizeof(TAF_CALL_EVT_SIGNAL_INFO_IND_STRU),
                           &stSignalInfo);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCCWACInfoInd
 ��������  : ����TAF_CALL_EVT_CCWAC_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �����ɺ���
  2.��    ��   : 2015��1��17��
    ��    ��   : y00307564
    �޸�����   : ����PI, SI�ֶ�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCCWACInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CCWAC_INFO_IND_STRU    stCCWAC;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 begin */
    if (VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo)
    {
        return;
    }

    /* Modify  by Y00307564 for 1X SS Project, 2014-11-27, begin */
    /* ���TAF_CALL_EVT_CCWAC_INFO_IND_STRU */
    stCCWAC.usClientId = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCCWAC.ucOpId     = MMA_OP_ID_INTERNAL;
    /* Modified by y00307564 for CDMA Iteration 8 2015-2-15 end */

    stCCWAC.ucCallId   = pstInfoRecInd->ucCallId;
    stCCWAC.enNumType  = pstInfoRecInd->stCallingNumInfo.enNumType;
    stCCWAC.enNumPlan  = pstInfoRecInd->stCallingNumInfo.enNumPlan;
    stCCWAC.ucDigitNum = pstInfoRecInd->stCallingNumInfo.ucDigitNum;

    /* Added by y00307564 for CDMA 1X Iteration 6 2015-1-17 begin */
    stCCWAC.ucPi       = pstInfoRecInd->stCallingNumInfo.ucPi;
    stCCWAC.ucSi       = pstInfoRecInd->stCallingNumInfo.ucSi;
    /* Added by y00307564 for CDMA 1X Iteration 6 2015-1-17 end */

    PS_MEM_CPY(stCCWAC.aucDigit,
               pstInfoRecInd->stCallingNumInfo.aucDigit,
               pstInfoRecInd->stCallingNumInfo.ucDigitNum);

    if (VOS_TRUE == pstInfoRecInd->bitOpSignalInfo)
    {
        stCCWAC.ucSignalIsPresent = VOS_TRUE;
        stCCWAC.ucAlertPitch      = pstInfoRecInd->stSignalInfo.ucAlertPitch;
        stCCWAC.ucSignalType      = pstInfoRecInd->stSignalInfo.ucSignalType;
        stCCWAC.ucSignal          = pstInfoRecInd->stSignalInfo.ucSignal;
    }
    else
    {
        stCCWAC.ucSignalIsPresent = VOS_FALSE;
    }
    /* Modify  by Y00307564 for 1X SS Project, 2014-11-27, end */

    /* ����TAF_CALL_EVT_CCWAC_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CCWAC_INFO_IND,
                           stCCWAC.usClientId ,
                           sizeof(TAF_CALL_EVT_CCWAC_INFO_IND_STRU),
                           &stCCWAC);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallingNumSignalInfoInd
 ��������  : ����calling num signal or both
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��13��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �����ɺ���
_____________________________________________________________________________
|call state      |    active                    |         inactive           |
|________________|______________________________|____________________________|
|bitOpcallingnum |     0        |       1       |       0     |     1        |
|________________|______________|_______________|_____________|______________|
|           |0   |   signal     |    ccwac      |      NA     |calling num   |
|BitOpSignal|____|______________|_______________|_____________|______________|
|           |1   |   signal     |    ccwac      |   signal    |    both      |
|___________|____|______________|_______________|_____________|______________|

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallingNumSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;

    if ((VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo) && (VOS_TRUE != pstInfoRecInd->bitOpSignalInfo))
    {
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstInfoRecInd->ucCallId);

    if (MN_CALL_S_ACTIVE == enCallState)
    {
        /* ����active̬,�ɱ��еĶ�Ӧ��ϵ��֪��������calling numberֱ�ӷ���ccwac������������signal */
        if (VOS_TRUE == pstInfoRecInd->bitOpCallingNumInfo)
        {
            TAF_XCALL_SndCCWACInfoInd(pstInfoRecInd);
        }
        else
        {
            TAF_XCALL_SndSignalInfoInd(pstInfoRecInd);
        }
    }
    else
    {
        /* ����inactive̬,�ɱ��еĶ�Ӧ��ϵ��֪,������calling number or signal��ֱ�ӷ��ͼ��� */
        TAF_XCALL_SndCallingPratNumInfoInd(pstInfoRecInd);

        TAF_XCALL_SndSignalInfoInd(pstInfoRecInd);

    }

}



VOS_VOID TAF_XCALL_SndXlemaCnf(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{

    /* ����MN_CALL_EVT_XLEMA_CNF��Ϣ */
    TAF_XCALL_SndCsEvtToAt(pstEccNumInfo->enEvent,
                           pstEccNumInfo->usClientId,
                           sizeof(MN_CALL_ECC_NUM_INFO_STRU)-sizeof(pstEccNumInfo->enEvent),
                           &pstEccNumInfo->usClientId);

    return;

}




/* Added by l00324781 for CDMA Iteration 16, 2015-7-24,begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndContDTMFCnf
 ��������  : �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_CNF
 �������  : VOS_UINT16                                  usClientId,
             VOS_UINT8                                   ucOpId,
             TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
             VOS_UINT8                                   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndContDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
    VOS_UINT8                                   ucCallId
)
{
    TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU                    stSendContDTMFCnf;

    PS_MEM_SET(&stSendContDTMFCnf, 0 ,sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU));

    /* ��д��Ϣ */
    stSendContDTMFCnf.enResult   = enResult;
    stSendContDTMFCnf.usClientId = usClientId;
    stSendContDTMFCnf.ucOpId     = ucOpId;
    stSendContDTMFCnf.ucCallId   = ucCallId;

    /* �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_CONT_DTMF_CNF,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU),
                           &stSendContDTMFCnf);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndContDTMFRslt
 ��������  : �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_RSLT
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndContDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU                   stSendContDTMFRslt;

    PS_MEM_SET(&stSendContDTMFRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU));

    /* ��д��Ϣ */
    stSendContDTMFRslt.usClientId  = usClientId;
    stSendContDTMFRslt.ucOpId      = ucOpId;
    stSendContDTMFRslt.ucResult    = ucResult;

    /* �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_RSLT�� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU),
                           &stSendContDTMFRslt);
}
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */


VOS_VOID TAF_XCALL_SndBurstDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDtmfInd
)
{
    TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU                    stSendBurstDTMFInd;

    PS_MEM_SET(&stSendBurstDTMFInd, 0 ,sizeof(TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFInd.usClientId  = usClientId;
    stSendBurstDTMFInd.ucOpId      = ucOpId;
    stSendBurstDTMFInd.ucCallId    = pstBurstDtmfInd->ucCallId;
    stSendBurstDTMFInd.ucDigitNum  = pstBurstDtmfInd->ucDigitNum;

    PS_MEM_CPY(stSendBurstDTMFInd.aucDigit, pstBurstDtmfInd->aucDigit, sizeof(stSendBurstDTMFInd.aucDigit));

    stSendBurstDTMFInd.ulOnLength  = pstBurstDtmfInd->ulOnLength;
    stSendBurstDTMFInd.ulOffLength = pstBurstDtmfInd->ulOffLength;

    /* Send the Burst DTMF Ind to AT */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_RCV_BURST_DTMF_IND,
                           usClientId,
                           sizeof(TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU),
                          &stSendBurstDTMFInd);
    return;
}


/* Added by k902809 for CDMA Iteration 16, 2015-7-25, begin */
/*****************************************************************************
Function Name   :   TAF_XCALL_SndContDTMFInd
Description     :   The function sends the Continuous DTMF Ind to AT
Input parameters:   usClientId - the client ID
                    ucOpId     - OpId
                    pstContDtmfInd - contains the parameters received in the Continuous DTMF Message.

Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-07-25
        Author  :   K00902809
        Modify content :Create
*****************************************************************************/
VOS_VOID TAF_XCALL_SndContDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDtmfInd
)
{
    TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU                     stSendContDTMFInd;

    PS_MEM_SET(&stSendContDTMFInd, 0 ,sizeof(TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU));

    stSendContDTMFInd.usClientId    = usClientId;
    stSendContDTMFInd.ucOpId        = ucOpId;
    stSendContDTMFInd.ucCallId      = pstContDtmfInd->ucCallId;
    stSendContDTMFInd.enSwitch      = pstContDtmfInd->enSwitch;
    stSendContDTMFInd.ucDigit       = pstContDtmfInd->ucDigit;

    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_RCV_CONT_DTMF_IND,
                           usClientId,
                           sizeof(TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU),
                          &stSendContDTMFInd);
    return;
}

/* Added by k902809 for CDMA Iteration 16, 2015-7-25, end */
#endif



/*lint -restore*/



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





