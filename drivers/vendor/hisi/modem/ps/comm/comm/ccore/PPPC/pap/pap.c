/************************************************************************
*                                                                      *
*                             pap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/01                                      *
*  Author:             Zhu Fengzhi                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��PAPЭ��ģ��                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PAPЭ��ģ���ȫ���ӿں������ڲ�������                *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PAP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP��ʼ��PAP���ƿ�                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_PAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo;
    PPPCONFIGINFO_S *pstConfig;

    if (pstPppInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_279);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((pstPapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_280);
        return;
    }
    pstPapInfo->ucUsed = 1;
    pstPapInfo->pstPppInfo = pstPppInfo;
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_INITIAL;
    pstPapInfo->ucServerState = PAP_STATE_SERVER_INITIAL;
    pstPapInfo->ucId = 0;
    pstPapInfo->ucPeerId = 0;
    pstPapInfo->ulSendReqTimeout = pstConfig->ulNegTimeOut;
    pstPapInfo->ulWaitReqTimeout = PAP_WAITREQUESTTIME;
    pstPapInfo->ulWaitLnsAuthTimeOut = PAP_WAITLNSAUTHTIME;/*Added by wangliang ht04409 at 2006-2-13 for BYHD09482*/
    pstPapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;
    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ulClientTimeoutID = 0;
    pstPapInfo->ulServerTimeoutID = 0;
    pstPapInfo->usAuthClientFailureTimes = 0;
    pstPapInfo->usAuthServerFailureTimes = 0;

    /* added by gxf 20030221 */
    pstPapInfo->ulWaitAuthRspTimeout = PAP_WAITAAARSPTIME;
    pstPapInfo->ulAuthMaxTransmits = PAP_MAXAUTHTRANSMITS;
    pstPapInfo->ucAuthTransmits  = 0;
    pstPapInfo->pstAAAAuthReqMsg = NULL;

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�����ⲿ�¼�.�¼�������ClientUp��ServerUp��Down            *                                           Open��Close            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,����Ϊ����ֵ:                                 *
*                    PAP_EVENT_CLIENTLOWERUP:�����²�UP                        *
*                    PAP_EVENT_SERVERLOWERUP:�Զ��²�UP                        *
*                    PAP_EVENT_LOWERDOWN:�²�DOWN                            *
*                pPara:�¼��Ĳ���,ΪNULL                                    *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_PAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, ULONG ulCmd, char *pPara)
{
    if (pstPppInfo == 0)
    {
        return;
    }

    switch (ulCmd)
    {
        case PAP_EVENT_CLIENTLOWERUP:
            PPP_PAP_ClientLowerUp(pstPppInfo);
            break;

        case PAP_EVENT_SERVERLOWERUP:
            PPP_PAP_ServerLowerUp(pstPppInfo);
            break;

        case PAP_EVENT_LOWERDOWN:
            PPP_PAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_281);
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Error Event!" );
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP����LowerUp,�ɶԶ���֤�ҷ�                                *
*                 ����PAP_STATE_SEND_AUTHREQ״̬,��Զ˷�����֤����              *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_ClientLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCONFIGINFO_S                    *pstConfig       = pstPppInfo->pstUsedConfigInfo;
    PPPPAPINFO_S                       *pstPapInfo      = pstPppInfo->pstPapInfo;
    VOS_UINT32                          ulRet;


    PPPC_INFO_LOG("\r\nPPP_PAP_ClientLowerUp \r\n");/*add by chenmin00265046*/

    if ((pstPapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_282);
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_CLIENTLOWERUP);

    ulRet = PPP_GetConfigUserName(pstPapInfo->szPapUsrName);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get username fail when pap client up.");
    }

    ulRet = PPP_GetConfigPassWord(pstPapInfo->szPapUsrPwd);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get pass word fail when pap client up.");
    }

    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ucId = 0;
    pstPapInfo->ulSendReqTimeout = pstConfig->ulNegTimeOut;
    pstPapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;
    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ulClientTimeoutID = 0;
    pstPapInfo->usAuthClientFailureTimes = 0;

    PPP_PAP_SendAuthReq(pstPppInfo);

    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SEND_AUTHREQ, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_SEND_AUTHREQ;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAPԶ��LowerUp,���Ҷ���֤�Զ�                                *
*                 ����PAP_STATE_SERVER_LISTEN״̬,�ȴ��Զ��ͳ���֤��            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;

    if (pstPapInfo == NULL)
    {
        return;
    }

    pstPapInfo->ucPeerId = 0;
    pstPapInfo->ulWaitReqTimeout  = PAP_WAITREQUESTTIME;
    pstPapInfo->ulServerTimeoutID = 0;
    pstPapInfo->usAuthServerFailureTimes = 0;

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_SERVERLOWERUP);

    /*����ȴ��Զ��ͳ���֤����ʱ��ʱ�� */
    (VOS_VOID)VOS_StartRelTimer((HTIMER)&(pstPapInfo->ulServerTimeoutID),
                                MID_PPPC,
                                pstPapInfo->ulWaitReqTimeout,
                                pstPppInfo->ulRPIndex,
                                PPPC_PAP_WAIT_FOR_REQ_TIMER,
                                VOS_TIMER_LOOP,
                                VOS_TIMER_PRECISION_0);

    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_LISTEN, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_SERVER_LISTEN;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAPLowerDown                                                *
*                 ����PAP_STATE_SERVER_INITIAL״̬������PAP_STATE_CLIENT_INITIAL״̬*
*                 ͬʱɾ����ʱ��                                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_LOWERDOWN);
    PPP_PAP_DeleteTimer(pstPppInfo);    /*ɾ����ʱ�� */
    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_INITIAL, SERVER_STATE);
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_INITIAL, CLIENT_STATE);

    pstPapInfo->ucClientState = PAP_STATE_CLIENT_INITIAL;
    pstPapInfo->ucServerState = PAP_STATE_SERVER_INITIAL;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�յ�pap ���ݰ�,��������ͷ������Ӧ����                    *
*                pHead:��ű����ڴ��ͷָ�����Э���,Ӧ�����ͷ�����ڴ�    *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_PAP_ReceivePacket (PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    UCHAR ucCode, ucId;
    ULONG ulCiLen;

    if (pstPppInfo == NULL)
    {
        return;
    }

    /*������ĵ�����Ϣ*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 1);

    PPPC_INFO_LOG("\r\n PPP_PAP_ReceivePacket \r\n");/*add by chenmin00265046*/

    /*��������ͷ(code,id, length)*/
    if (ulLen < FSM_HDRLEN)        /* ������İ�̫������ */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_283);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /* ��ñ������ֶ�ֵ,���ƶ�����ָ�� */
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if ((ulCiLen > ulLen) || (ulCiLen < PAP_HEADERLEN))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_284);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Error packet length!");
        return;
    }

    ulCiLen -= PAP_HEADERLEN;

    /* ���� code ������Ӧ�Ķ��� */
    switch (ucCode)
    {
        case PAP_AUTHREQ:/* �յ� Authenticate-Request */
            PPP_DBG_OK_CNT(PPP_PHOK_932);
            PPP_PAP_ReceiveAuthReq(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case PAP_AUTHACK:/*�յ� Authenticate_Ack */
            PPP_PAP_ReceiveAuthAck(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case PAP_AUTHNAK:/* �յ� Authenticate-Nak */
            PPP_PAP_ReceiveAuthNak(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_285);
            PPP_PAP_ReceiveUnknownCode(pstPppInfo); /* code�ܾ� */
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��ɾ����ʱ��                                                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��                                                            *
****************************************************************************/
VOID PPP_PAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo;

    if (pstPppInfo == NULL)
    {
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        return;
    }

    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));   /* ɾ��Client��ʱ�� */
        pstPapInfo->ulClientTimeoutID = 0;
    }

    if (pstPapInfo->ulServerTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));    /* ɾ��Server ��ʱ�� */
        pstPapInfo->ulServerTimeoutID = 0;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�յ�һ�Ƿ�Э��,֪ͨ�ײ�DOWN                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveUnknownCode(PPPINFO_S *pstPppInfo)
{
    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_CODEREJECT);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�յ���֤�����,������ǰ״̬�����д���                    *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthReq(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR ucPeerIdLen, ucPswLen;
    AAA_AUTHREQ_S *pstMsg;
    CHAR msg[256] = {0};

    LONG lLen = (LONG)ulLen;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* ��ǰ��pap���ƿ���id��ֵ��������Э����pap response�� idΪ0 */
    pstPapInfo->ucPeerId = ucId;

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVEREQUEST);

    if ((pstPapInfo->ucServerState == PAP_STATE_SERVER_INITIAL)
        || (pstPapInfo->ucServerState == PAP_STATE_WAIT_AAA))
    {
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_286);
        return;
    }

    /*���Ѿ���֤���ٴ��յ���֤���������ϴ���֤����ظ��Է���*/
    if (pstPapInfo->ucServerState == PAP_STATE_SERVER_SUCCESS)
    {
        if ( ( 0 == pstPppInfo->bReNego )
                && (0 == pstPppInfo->bPppClient)
                 && (1 == pstPppInfo->bPppMode))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_287);
        }
        else
        {
            /*������������Ϣ*/
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Receive request again!");
            PPP_PAP_SendResponse(pstPppInfo, PAP_AUTHACK, ucId, AuthMsgError, 0); /* return auth-ack */
            PPP_DBG_ERR_CNT(PPP_PHERR_288);
        }
        return;
    }

    if (pstPapInfo->ucServerState == PAP_STATE_SERVER_FAILED)
    {
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Receive request again!");
        PPP_PAP_SendResponse(pstPppInfo, PAP_AUTHNAK, ucId, AuthMsgError, 0); /* return auth-nak */
        PPP_DBG_ERR_CNT(PPP_PHERR_289);
        return;
    }

    if (pstPapInfo->pstAAAAuthReqMsg)
    {
        /* ���Ѿ�������ڴ�, ֱ��ʹ�� */
        pstMsg = pstPapInfo->pstAAAAuthReqMsg;
    }
    else
    {
        pstMsg = (AAA_AUTHREQ_S *)PPP_Malloc( sizeof(AAA_AUTHREQ_S));
        if (!pstMsg)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_290);
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
            return;
        }

        pstPapInfo->pstAAAAuthReqMsg = pstMsg;
    }

    PPP_MemSet((void *)pstMsg, 0, sizeof(AAA_AUTHREQ_S));

    /* �����û���������    */
    PPP_GETCHAR(ucPeerIdLen, pPacket);
    lLen -= (LONG)(sizeof (UCHAR) + ucPeerIdLen + sizeof (UCHAR));
    if (lLen < 0)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_26);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (USHORT)VOS_StrLen(AuthMsgError));

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_291);
        return;
    }

    if ((ucPeerIdLen > A11_MAX_NAI_LENGTH) || (ucPeerIdLen == 0)) /* Modified by heyajun kf1199 at 2004-07-29 V800R001B03C01B010 for BYHD03108 */
    {
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too long or NULL PeerId!");
        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (USHORT)VOS_StrLen(AuthMsgError));
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_27);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_292);
        return;
    }

    pstMsg->ucUsernameLen = ucPeerIdLen;

    (VOID)VOS_sprintf((char*)pstMsg->ucUsername, "%*.*s", pstMsg->ucUsernameLen, pstMsg->ucUsernameLen, pPacket);

    /*ָ���Ƶ�Passwd_Lengthλ��*/
    PPP_INCPTR(ucPeerIdLen, pPacket);    /*ָ���Ƶ�Passwd_Lengthλ��*/
    PPP_GETCHAR(ucPswLen, pPacket);
    if (lLen < ucPswLen)
    {
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_28);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_DBG_ERR_CNT(PPP_PHERR_293);
        return;
    }

    if (ucPswLen > PPP_MAXUSERPWDLEN)
    {
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too long Password!");
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_29);

        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (USHORT)VOS_StrLen(AuthMsgError));

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_294);
        return;
    }

    /*ɾ���ȴ�Request ��ʱ��ʱ��*/
    if (pstPapInfo->ulServerTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    if ((0 != pstPppInfo->ucNAI[0]) && 0 != VOS_StrCmp((CHAR*)(pstMsg->ucUsername), (CHAR*)(pstPppInfo->ucNAI)))
    {
        PPP_PAP_AAAAuthFailed(pstPapInfo);

        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_30);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/

        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "NAI != username");
        PPP_DBG_ERR_CNT(PPP_PHERR_295);
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_PAP_ReceiveAuthReq:The domain index(%u)(%u)",
                 pstPppInfo->usCDBIndex,
                 pstPppInfo->usVirtualDomainIdx);
    if ((pstPppInfo->usCDBIndex >= RM_MAX_APN_NUM)
        && (pstPppInfo->usVirtualDomainIdx >= RM_MAX_APN_NUM))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_933);
        if (VOS_OK != PPP_GetDomainInfoByName(pstPppInfo, pstMsg->ucUsername))
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_PAP_AAAAuthFailed(pstPapInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_296);
            return;
        }
    }
#if 0
    A11_UpdateDomainIndexAtEntryState(pstPppInfo->ulRPIndex, pstPppInfo->usCDBIndex, VOS_FALSE);
#endif
    (VOID)VOS_sprintf((char*)pstPppInfo->ucNAI, "%s", pstMsg->ucUsername);

    /* ����LOCK��־�ж��Ƿ���������Ǳ�LOCK�����������������Э��ʧ�� */
    if ((PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
        || (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usVirtualDomainIdx].ucLock))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_31);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_PAP_ReceiveAuthReq:The domain is locked, the domainindex is (%u)(%u)",
                 pstPppInfo->usCDBIndex,
                 pstPppInfo->usVirtualDomainIdx);
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_297);
        return;
    }

    PPP_PerfInc(&g_stPppPerfStatistic.ulPapTotal, PERF_TYPE_PPPC_PAP_AUTHEN_NUM, pstPppInfo->bEhrpdUser);

    if(VOS_TRUE == pstPppInfo->bAuthFlag)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n [ppp]PPP_PAP_ReceiveAuthReq: pstPppInfo->bAuthFlag is %u PpcFlag %d",
                            pstPppInfo->bAuthFlag,
                            pstPppInfo->bPpcAAAFlag);


        /* ��Э�̲���Ҫ��AAA��Ȩ */
        if (0 == pstPppInfo->bPpcAAAFlag)
        {
            (VOID)VOS_sprintf(msg, "Welcome to %s.", pstPppInfo->pstConfigInfo->cChapHostName);
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_SUCCESS, pstPapInfo->ucPeerId,
                                 msg, (USHORT )VOS_StrLen(msg));
            /* ���״̬ת��������Ϣ */
            PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_SUCCESS, SERVER_STATE);
            pstPapInfo->ucServerState = PAP_STATE_SERVER_SUCCESS;

            PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

            if (NULL != pstPapInfo->pstAAAAuthReqMsg)
            {
                PPP_Free( pstPapInfo->pstAAAAuthReqMsg);
                pstPapInfo->pstAAAAuthReqMsg = NULL;
                pstMsg = NULL;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_934);
            pstPppInfo->bAuthServer = VRP_NO;
            PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPSUCCESS, NULL);

            return;
        }
    }

    /* End Added by hyj for B02 */

    /* ������֤��Ϣ��stMsg */
    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;
    pstMsg->usCDBIndex = pstPppInfo->usCDBIndex;
    pstMsg->ucPwdLen = ucPswLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucPwd, pPacket, (ULONG )pstMsg->ucPwdLen);
    pstMsg->ucPwd[pstMsg->ucPwdLen] = 0x0;
    /*pstMsg->usVPNID = pstPppInfo->usVPNID;*/
    pstMsg->ucPktID = ucId;
    pstMsg->stIMSI = pstPppInfo->stIMSI;

    pstMsg->ucRenegoFlag = pstPppInfo->bPpcAAAFlag;

    (VOID)VOS_MemCpy((CHAR *)pstPapInfo->szPapUsrPwd, pPacket, (ULONG )pstMsg->ucPwdLen);
    pstPapInfo->szPapUsrPwd[pstMsg->ucPwdLen] = 0x0;


    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_WAIT_AAA, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_WAIT_AAA;

#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* ����PPP �� L2TP ͨ������ stOption ���� */
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* ������֤���� */
        pstOptionalPara->usAuthenType = L2TP_PPP_PAP;

        /* ����������֤�û��� */
        VOS_MemCpy(pstOptionalPara->szAuthenName,
                        pstMsg->ucUsername,
                        pstMsg->ucUsernameLen);
        pstOptionalPara->szAuthenName[pstMsg->ucUsernameLen] = 0x0;

        /* �����û����� */
        VOS_MemCpy(pstOptionalPara->szResponse,
                        pstMsg->ucPwd,
                        pstMsg->ucPwdLen);
        pstOptionalPara->szResponse[pstMsg->ucPwdLen] = 0x0;
        pstOptionalPara->ulResponseLen = pstMsg->ucPwdLen;

        /* ������֤�� ID */
        pstOptionalPara->usAuthenID = ucId;
    }
#endif

    /* ���÷��͵ĺ�������ֱ���ڴ˴����� */
    PPP_PAP_SendAAAAuthReq(pstPapInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_935);
    return;
}




/*****************************************************************************
 �� �� ��  : PPP_PAP_ReceiveAAAResult
 ��������  : Papģ���յ�AAA�ļ�Ȩ��Ϣ
 �������  : AAA_AUTHRSP_S *pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PAP_ReceiveAAAResult(AAA_AUTHRSP_S *pMsg)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S * pstPapInfo;
    CHAR msg[256]   = {0};          /*ħ�����֣�Ҫ�궨��*/
    USHORT usMsgLen = 0;

    PPP_TRACE("\r\n---PPP_PAP_ReceiveAAAResult---\r\n");
    VOS_DBGASSERT(pMsg);

    /*�ж������������Ч��*/
    if (NULL == pMsg)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_PAP_ReceiveAAAResult: Invalid input parameter!");
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (pstPppInfo == NULL)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_PAP_ReceiveAAAResult: User %d isn't exist!", pMsg->ulSDBIndex);
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_936);
    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_PAP_ReceiveAAAResult: User %d  papinfo isn't exist!",
                 pMsg->ulSDBIndex);
        return;
    }

    /* ɾ����ʱ�� */
    if (pstPapInfo->ulServerTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    /* �ͷ�AAA��֤������Ϣ */
    if (pstPapInfo->pstAAAAuthReqMsg)
    {
        PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
        pstPapInfo->pstAAAAuthReqMsg = NULL;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_AAARESULT);

    if (pstPapInfo->ucServerState != PAP_STATE_WAIT_AAA)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_298);

        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    if (pMsg->ucResult == 0) /* AAA ��֤ͨ�� */
    {
        PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

        PPP_DBG_OK_CNT(PPP_PHOK_937);
        (VOID)VOS_sprintf(msg, "Welcome to %s.", pstPppInfo->pstConfigInfo->cChapHostName);
        PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_SUCCESS, pstPapInfo->ucPeerId,
                             msg, (USHORT )VOS_StrLen( msg ));

        /* ���״̬ת��������Ϣ */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_SUCCESS, SERVER_STATE);
        pstPapInfo->ucServerState = PAP_STATE_SERVER_SUCCESS;

        /*���ں˱�Server�� PAP ��֤�ɹ� */
        pstPppInfo->bAuthServer = VRP_NO;
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPSUCCESS, (CHAR*)pMsg);
    }

    else        /* AAA��֤δ�� */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_299);
        if (pMsg->ucReplyMsg[0] == 0)
        {
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_FAILED, pstPapInfo->ucPeerId,
                                 "Authenticate failed.",
                                 sizeof("Authenticate failed."));
        }
        else
        {
            usMsgLen = (VOS_UINT16)VOS_StrLen((CHAR *)(pMsg->ucReplyMsg));
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_FAILED, pstPapInfo->ucPeerId,
                                 (CHAR *)(pMsg->ucReplyMsg), usMsgLen);
        }

        /* ���״̬ת��������Ϣ */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_FAILED, SERVER_STATE);
        pstPapInfo->ucServerState = PAP_STATE_SERVER_FAILED;

        /*ɾ����ʱ�� */
        PPP_PAP_DeleteTimer(pstPppInfo);

        /*���ں˱�Server��PAP��֤ʧ��*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
    }
    PPP_DBG_OK_CNT(PPP_PHOK_938);
    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\nPPP_PAP_ReceiveAAAResult Done !");
    return;
}



/*****************************************************************************
 �� �� ��  : PPP_PAP_SendAAAAuthReq
 ��������  : ��AAA���ͼ�Ȩ����
 �������  : AAA_AUTHREQ_S *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��2��21��
    ��    ��   : gxf
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PAP_SendAAAAuthReq(PPPPAPINFO_S *pstPapInfo)
{
#if 0
    AAA_AUTHREQ_S *pstMsg;
    ULONG ulRet;
    PPPINFO_S *pstPppInfo;
    PPP_DBG_OK_CNT(PPP_PHOK_939);

    PPP_TRACE("\r\n---Into PPP_PAP_SendAAAAuthReq---\r\n");
    if (NULL == pstPapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_300);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstPapInfo=NULL");
        return;
    }

    pstMsg = pstPapInfo->pstAAAAuthReqMsg;
    if (NULL == pstMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_301);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstMsg=NULL");
        return;
    }

    pstPppInfo = pstPapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_302);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstPppInfo=NULL");
        return;
    }


    /* ���ڿ����Ƿ�NAIת����Сд��� */
    if (1 == M_SPM_USER_NAME_LOWERCASE)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_940);
        VOS_lowercase((CHAR*)(((AAA_AUTHREQ_S*)pstMsg)->ucUsername));
    }

    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;

    /* BEGIN: Modified by luofang, 2012/9/26 */
    ((AAA_AUTHREQ_S*)pstMsg)->ucPPPFlag =1;
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                         g_ullPppAuthCsi,
                         AUTH_MSG_TYPE_PPP,
                         PPP_AUTH_FLAG,
                         (UCHAR *)pstMsg,
                         sizeof( AAA_AUTHREQ_S ));
    if ( VOS_OK != ulRet )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_303);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_PAP_SendAAAAuthReq: PPP_SendRtMsg Err!!");
        return;
    }


    /* ���ó�ʱ��ʱ�� */
    VOS_DBGASSERT(pstPapInfo->ulServerTimeoutID == 0);
    ulRet = PGP_Timer_Create(PPP_SELF_CSI,
                             PPP_MSG_TYPE_TIMER,
                             pstPapInfo->ulWaitAuthRspTimeout,
                             PPP_PAP_AuthRspTimeout,
                             (VOID*)pstPppInfo->ulRPIndex, /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
                             &(pstPapInfo->ulServerTimeoutID),
                             VOS_TIMER_LOOP);
    if (ulRet != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_304);
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "PGP_Timer_Create error!");
    }

    ++pstPapInfo->ucAuthTransmits;
    PPP_DBG_OK_CNT(PPP_PHOK_941);
#endif
    return ;
}



/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�յ��Զ�ACK,���д���                                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthAck(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR ucMsgLen;

    /*CHAR *stMsg ;*/

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVEACK);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ) /* �Ƿ��¼� */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_305);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /* ���� Message */
    if (ulLen < sizeof (UCHAR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_306);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    PPP_GETCHAR(ucMsgLen, pPacket); /*ȡ�� ACK ���ĵ�Message ���� */
    if (ulLen < ucMsgLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_307);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /*ɾ����ʱ��*/
    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    /*stMsg = (CHAR *) pPacket ;*/    /*ȡ�� ACK ���ĵ�Message ���� */

    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_SUCCESS, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_SUCCESS;

    /*���ں˱� Client ��PAP ��֤�ɹ� */
    pstPppInfo->bAuthClient = VRP_NO;
    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPSUCCESS, NULL);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP�յ��Զ�NAK,���д���                                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthNak(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR ucMsgLen;

    /*CHAR *stMsg ;*/
    CHAR cErrstr[100];

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVENAK);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ) /* �쳣�¼� */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_308);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /*���� Message*/
    if (ulLen < sizeof (UCHAR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_309);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    PPP_GETCHAR(ucMsgLen, pPacket); /*ȡ�� NAK ���ĵ�Message ���� */
    if (ulLen < ucMsgLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_310);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /* ɾ����ʱ�� */
    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    /*stMsg = (CHAR *) pPacket ;*/
    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_FAILED, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_FAILED;

    /*Client��֤ʧ�ܴ�����һ*/
    pstPapInfo->usAuthClientFailureTimes += 1;

    /*������������Ϣ*/
    (VOID)VOS_sprintf(cErrstr, "Client failed No. %2d !",
                      pstPapInfo->usAuthClientFailureTimes );
    PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstPapInfo->usAuthClientFailureTimes >= PPP_MAXAUTHFAILTIMES)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_311);
        /*������Զ�������֤����,���ں˱�PAP ��֤ʧ�� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_PAPFAILED, NULL);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_942);
        /*����,�ٴ���Զ�������֤ */
        PPP_PAP_SendAuthReq(pstPppInfo);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP��Զ˷�����֤����                                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ClientLowerUp,PPP_PAP_SendAuthReqTimeout,            *
*                 PPP_PAP_ReceiveAuthNak                                        *
****************************************************************************/
VOID PPP_PAP_SendAuthReq(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR *pHead, *pPacket;
    ULONG ulLen = 0;
    ULONG ulOffset;
    UCHAR tmplen;
    ULONG ulErrorCode;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;
    if (!pHead)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_312);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
        return;
    }

    pPacket = pHead + ulOffset;
    ulLen = PAP_HEADERLEN + 2 + VOS_StrLen((CHAR*)pstPapInfo->szPapUsrName)
            + VOS_StrLen((CHAR*)pstPapInfo->szPapUsrPwd);

    PPP_PUTCHAR(PAP_AUTHREQ, pPacket);            /*PAP CODE */
    PPP_PUTCHAR(++pstPapInfo->ucId, pPacket);    /*PAP ID */
    PPP_PUTSHORT((USHORT)ulLen, pPacket);                /*PAP LENGTH*/

    /* дPeer_Id Length �� Peer_Id*/
    tmplen = (UCHAR )VOS_StrLen((CHAR*) pstPapInfo->szPapUsrName);
    PPP_PUTCHAR(tmplen, pPacket );
    (VOID)VOS_MemCpy((CHAR *)pPacket,
                       (pstPapInfo->szPapUsrName),
                       (ULONG)tmplen );

    PPP_INCPTR(tmplen, pPacket);

    /*д Passwd_Length ��Password */
    tmplen = (UCHAR )VOS_StrLen((CHAR*) pstPapInfo->szPapUsrPwd);
    PPP_PUTCHAR( tmplen, pPacket );
    (VOID)VOS_MemCpy((CHAR *)pPacket,
                       (pstPapInfo->szPapUsrPwd),
                       (ULONG)tmplen);
    PPP_INCPTR(tmplen, pPacket);

    pPacket -= ulLen;

    /*������ĵ�����Ϣ*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 0);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, ulLen, PPP_PAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_313);
        /*���������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstPapInfo->ulClientTimeoutID == 0)
    {
        /*���õȴ���֤��ʱ��ʱ��*/
        (VOS_VOID)VOS_StartRelTimer((HTIMER)&(pstPapInfo->ulClientTimeoutID),
                                    MID_PPPC,
                                    pstPapInfo->ulSendReqTimeout,
                                    pstPppInfo->ulRPIndex,
                                    PPPC_PAP_SEND_AUTH_REQ_TIMER,
                                    VOS_TIMER_LOOP,
                                    VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_314);
        VOS_DBGASSERT(0);
    }

    ++pstPapInfo->ucTransmits;

    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SEND_AUTHREQ, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_SEND_AUTHREQ;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP��Զ˷�����Ӧ(ACK��NAK)                                *
* MODIFY DATE  ��                                                            *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 ucCode: ��֤�ɹ�/ʧ�ܱ���code                                *
*                 stMsg: �ش���Ϣ                                                *
*                 ucMsgLen: ��Ϣ����                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_PAP_ClientLowerUp,PPP_PAP_SendAuthReqTimeout,            *
*                 PPP_PAP_ReceiveAuthNak                                        *
****************************************************************************/
VOID PPP_PAP_SendResponse(PPPINFO_S * pstPppInfo, UCHAR ucCode, UCHAR ucId, char *stMsg, USHORT usMsgLen)
{
    PPPPAPINFO_S *pstPapInfo;
    UCHAR *pHead, *pPacket;
    ULONG ulLen = 0;
    ULONG ulOffset;
    ULONG ulErrorCode;

    PPP_TRACE("\r\n---Into PPP_PAP_SendResponse---\r\n");

    if (pstPppInfo == NULL)
    {
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        return;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;
    if (!pHead)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_315);
        /*������������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
        return;
    }

    pPacket = pHead + ulOffset;
    ulLen = (USHORT )(PAP_HEADERLEN + 1 + usMsgLen);

    PPP_PUTCHAR(ucCode, pPacket);            /*PAP CODE */
    PPP_PUTCHAR(ucId, pPacket);            /*PAP ID */
    PPP_PUTSHORT((USHORT)ulLen, pPacket);            /*PAP LENGTH*/

    /* дMessage Length �� Message */
    PPP_PUTCHAR(usMsgLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )pPacket, stMsg, (ULONG)usMsgLen);
    PPP_INCPTR(usMsgLen, pPacket);

    pPacket -= ulLen;

    /*������ĵ�����Ϣ*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 0);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, ulLen, PPP_PAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_316);
        /*���������Ϣ*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��Server�˵ȴ��Զ˷�����֤����ʱ,���ں˱�PAP��֤ʧ��       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ����ulServerTimeoutID����                                    *
****************************************************************************/
VOS_VOID PPP_PAP_WaitReqTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S *pstPapInfo;
    PPP_DBG_OK_CNT(PPP_PHOK_943);

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_317);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_318);
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_WAITREQTIMEOUT);

    /* �����ʱ�� */
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
    pstPapInfo->ulServerTimeoutID = 0;
    if (pstPapInfo->ucServerState != PAP_STATE_SERVER_LISTEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_319);
        return;
    }

    /* ���״̬ת��������Ϣ */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_FAILED, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_SERVER_FAILED;
    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);


    PPP_PAP_DeleteTimer(pstPppInfo);    /*ɾ����ʱ�� */
    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_REQTIMEOUT);
    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPFAILED, NULL);


    if (0 == SOFTPARA_BIT1383)
    {
        A11_ReqNumSubProc(pstPppInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_320);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_321);
    }


    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��PAP Client�˵ȴ���֤�����ʱ                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ����ulClientTimeoutID��ʱ������                                *
****************************************************************************/
VOS_VOID PPP_PAP_SendAuthReqTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S *pstPapInfo;

    PPP_DBG_OK_CNT(PPP_PHOK_944);

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0L)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_322);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == 0L)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_323);
        return;
    }

    /* �����ʱ�� */
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
    pstPapInfo->ulClientTimeoutID = 0;

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_REQUESTTIMEOUT);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_324);
        return;
    }

    if (pstPapInfo->ucTransmits >= pstPapInfo->ulMaxTransmits)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_325);
        /* ���״̬ת��������Ϣ */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_FAILED, CLIENT_STATE);
        pstPapInfo->ucClientState = PAP_STATE_CLIENT_FAILED;

        PPP_PAP_DeleteTimer(pstPppInfo);    /*ɾ����ʱ�� */
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_SEND_REQTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_PAPFAILED, NULL);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_945);

    PPP_PAP_SendAuthReq(pstPppInfo);        /* Send Authenticate-Request */

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_PAP_AuthRspTimeout
 ��������  : PAP Server�˵ȴ�AAA��֤�����ʱ
 �������  : VOID *pPppInfo
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��2��21��
    ��    ��   : gxf
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PAP_AuthRspTimeout(VOID *ulIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPPAPINFO_S *pstPapInfo = NULL;
    AAA_AUTHREQ_S *pstAuthMsg = NULL;
    ULONG ulIdxTmp = (ULONG)ulIndex;

    PPP_TRACE("\r\n---Into PPP_PAP_AuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_946);

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_326);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    pstPapInfo = (PPPPAPINFO_S *)pstPppInfo->pstPapInfo;
    VOS_DBGASSERT(pstPapInfo);
    if (NULL == pstPapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_327);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo=NULL", ulIdxTmp);
        return;
    }

    pstAuthMsg = pstPapInfo->pstAAAAuthReqMsg;
    if (NULL == pstAuthMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_328);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstAuthMsg=NULL", ulIdxTmp);
        return;
    }

    pstPppInfo = pstPapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_329);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo->pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    if(pstPapInfo->ucServerState != PAP_STATE_WAIT_AAA)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_330);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo->ucServerState(%d)",
                         ulIdxTmp, pstPapInfo->ucServerState);
        return;
    }

    /* ����¼�������Ϣ */
    PAP_Debug_Event(pstPppInfo, PAP_WAITAAARSPTIMEOUT);

    /* �����ʱ�� */
    VOS_DBGASSERT(pstPapInfo->ulServerTimeoutID);
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
    pstPapInfo->ulServerTimeoutID = 0;

    if (pstPapInfo->ucAuthTransmits >= pstPapInfo->ulAuthMaxTransmits)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_32);
        PPP_DBG_ERR_CNT(PPP_PHERR_331);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        /*End of liushuang*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_AAATIMEOUT);
        PPP_PAP_AAAAuthFailed(pstPapInfo);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_947);
        PPP_PAP_SendAAAAuthReq(pstPapInfo);
    }

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
