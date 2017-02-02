
/************************************************************************
 *                                                                      *
 *                             pap_def.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/01                                      *
 *  Author:             Zhu Fengzhi                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP��PAPЭ��ģ��˽�к궨��                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������PAPЭ��ģ���ȫ��˽�к궨��                          *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_PAP == VRP_YES )

#ifndef      _PAP_DEF_H_
#define      _PAP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

#define PAP_HEADERLEN	(sizeof (UCHAR) + sizeof (UCHAR) + sizeof (USHORT))


/* PAP ����֡���� codes. */
#define PAP_AUTHREQ	1	/* Authenticate-Request */
#define PAP_AUTHACK	2	/* Authenticate-Ack */
#define PAP_AUTHNAK	3	/* Authenticate-Nak */

/*PAP ״̬����״ֵ̬ */
#define PAP_STATE_CLIENT_INITIAL	0
#define PAP_STATE_SERVER_INITIAL	0
#define PAP_STATE_SEND_AUTHREQ		1
#define PAP_STATE_SERVER_LISTEN	    1
#define PAP_STATE_SERVER_SUCCESS	2
#define PAP_STATE_CLIENT_SUCCESS	2
#define PAP_STATE_SERVER_FAILED	    3
#define PAP_STATE_CLIENT_FAILED	    3
#define PAP_STATE_WAIT_AAA			4

/*PAP ����CORE���¼����� */
#define PAP_EVENT_CLIENTLOWERUP	0
#define PAP_EVENT_SERVERLOWERUP 1
#define	PAP_EVENT_LOWERDOWN		2

/*PAP �ȴ��Զ���֤�ʱ�� */
#define PAP_WAITREQUESTTIME	    60000   
#define PAP_WAITLNSAUTHTIME             10000   /*Added by wangliang ht04409 at 2006-2-13 for BYHD09482*/
/* added by gxf 20030221 */
#define PAP_WAITAAARSPTIME      20000   /* modified by gxf 20030516  AAA��������server������������ÿ�μ��3s��3*6=18 */
#define PAP_MAXAUTHTRANSMITS	1	/* max # times to send AUTH msg */

#define PPP_PAP_AAAAuthFailed(pstPapInfo) \
{   \
    AAA_AUTHREQ_S *pstMsgTemp = pstPapInfo->pstAAAAuthReqMsg;  \
    PPPINFO_S *pstPppInfoTemp = pstPapInfo->pstPppInfo;     \
    if(pstMsgTemp)                                          \
    {                                                   \
        PPP_Free (pstMsgTemp);                              \
        pstPapInfo->pstAAAAuthReqMsg = NULL;            \
    }                                                   \
    pstPapInfo->ucAuthTransmits = 0 ;                   \
    PAP_Debug_StateChange(pstPppInfoTemp, PAP_STATE_SERVER_FAILED, SERVER_STATE) ;  \
    pstPapInfo->ucServerState = PAP_STATE_SERVER_FAILED ;   \
    PPP_Core_ReceiveEventFromProtocol (pstPppInfoTemp,(ULONG)PPP_EVENT_PAPFAILED,NULL) ;    \
}

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_DEF_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_PAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */





