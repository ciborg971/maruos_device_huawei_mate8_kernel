/************************************************************************
*                                                                      *
*                             ppp_dbug.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPPģ���debug��Ϣ����                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PPPģ��debug��Ϣ�����ȫ������                       *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_DBUG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPP_PrintDbgCntInteligently
 ��������  : PPPģ����Դ�ӡʧ����ɹ���־����
 �������  : ULONG ulCounter ʧ�ܻ�ɹ�������(0~799Ϊʧ�ܣ�800~Ϊ�ɹ�)
             ULONG ulValue ʧ�ܻ�ɹ��Ĵ���
             UCHAR *pucDefaultStrHead Ĭ�ϴ�ӡͷ
             ...
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��6��
    ��    ��   : chenmin00265046
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PrintDbgCntInteligently(ULONG ulCounter, ULONG ulValue, UCHAR *pucDefaultStrHead)
{
    if (ulValue != 0)
    {
        vos_printf("%s%lu: %lu <<<<<<<<<<<<<<<<< Not Zero!\r\n",pucDefaultStrHead, ulCounter, ulValue);
        return;
    }
}


/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ���������е��Կ���״̬�����Զ�һ���ӿڽ��У�Ҳ������ȫ�ֵġ� *
*                ���ڽӿڵĿ���״̬��һ������:�κ�ʱ������򿪿��أ�����    *
*                ��Ӧ��ȫ�ֿ���״̬Ϊonʱ�����ܵ����رսӿڿ���״̬��Ϊ��   *
*                ���������⣬����һ���жϣ�����ǶԽӿ�ִ��no debug������ *
*                �򽫽ӿڿ���״̬��Ϊȫ�ֿ��صĵ�ǰֵ��                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppDebugInfo:Ҫ����Ŀ������ݽṹָ��                   *
*                ucSet:ΪVRP_YES���������п��أ�ΪVRP_NO�����ر����п���  *
* OUTPUT       ����                                                         *
* RETURN       ��0:�ɹ�, ����:������                                        *
* CALLED BY    ��PPP_DebugAll                                               *
*                PPP_NoDebugAll                                             *
*                PPP_Debug_SetInterfaceOption                               *
*                PPP_Debug_SetGlobalOption                                  *
****************************************************************************/
VOID PPP_Debug_SetAllOptions( PPPDEBUGINFO_S *pstPppDebugInfo, UCHAR ucSet )
{
    g_ulPppDebugSwitch = (ULONG)ucSet;

    if ((pstPppDebugInfo != &g_stPppDebugInfo) && (ucSet == VRP_NO))
    {
        /* PPPЭ���¼����Կ��� */
        pstPppDebugInfo->bDebug_Core_Event = g_stPppDebugInfo.bDebug_Core_Event;

        /* IPCP������Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Error = g_stPppDebugInfo.bDebug_Ipcp_Error;

        /* IPCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Event = g_stPppDebugInfo.bDebug_Ipcp_Event;

        /* IPCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Packet = g_stPppDebugInfo.bDebug_Ipcp_Packet;

        /* IPCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_StateChange = g_stPppDebugInfo.bDebug_Ipcp_StateChange;

        /* CCP������Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Error = g_stPppDebugInfo.bDebug_Ccp_Error;

        /* CCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Event = g_stPppDebugInfo.bDebug_Ccp_Event;

        /* CCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Packet = g_stPppDebugInfo.bDebug_Ccp_Packet;

        /* CCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Ccp_StateChange = g_stPppDebugInfo.bDebug_Ccp_StateChange;


        /* PAP������Կ��� */
        pstPppDebugInfo->bDebug_Pap_Error = g_stPppDebugInfo.bDebug_Pap_Error;

        /* PAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Pap_Event = g_stPppDebugInfo.bDebug_Pap_Event;

        /* PAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Pap_Packet = g_stPppDebugInfo.bDebug_Pap_Packet;

        /* PAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Pap_StateChange = g_stPppDebugInfo.bDebug_Pap_StateChange;

        /* CHAP������Կ��� */
        pstPppDebugInfo->bDebug_Chap_Error = g_stPppDebugInfo.bDebug_Chap_Error;

        /* CHAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Chap_Event = g_stPppDebugInfo.bDebug_Chap_Event;

        /* CHAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Chap_Packet = g_stPppDebugInfo.bDebug_Chap_Packet;

        /* CHAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Chap_StateChange = g_stPppDebugInfo.bDebug_Chap_StateChange;

        /* EAP������Կ��� */
        pstPppDebugInfo->bDebug_Chap_Error = g_stPppDebugInfo.bDebug_EAP_Error;

        /* EAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Chap_Event = g_stPppDebugInfo.bDebug_EAP_Event;

        /* EAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Chap_Packet = g_stPppDebugInfo.bDebug_EAP_Packet;

        /* EAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Chap_StateChange = g_stPppDebugInfo.bDebug_EAP_StateChange;

        pstPppDebugInfo->bDebug_Ip_Packet = g_stPppDebugInfo.bDebug_Ip_Packet;

        pstPppDebugInfo->bDebug_Scp_Packet = g_stPppDebugInfo.bDebug_Scp_Packet;

        /* LCP������Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Error = g_stPppDebugInfo.bDebug_Lcp_Error;

        /* LCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Event = g_stPppDebugInfo.bDebug_Lcp_Event;

        /* LCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Packet = g_stPppDebugInfo.bDebug_Lcp_Packet;

        /* LCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Lcp_StateChange = g_stPppDebugInfo.bDebug_Lcp_StateChange;
    }
    else
    {
        /* PPPЭ���¼����Կ��� */
        pstPppDebugInfo->bDebug_Core_Event = ucSet;

        /* IPCP������Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Error = ucSet;

        /* IPCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Event = ucSet;

        /* IPCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_Packet = ucSet;

        /* IPCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Ipcp_StateChange = ucSet;

        /* CCP������Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Error = ucSet;

        /* CCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Event = ucSet;

        /* CCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Ccp_Packet = ucSet;

        /* CCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Ccp_StateChange = ucSet;

        /* PAP������Կ��� */
        pstPppDebugInfo->bDebug_Pap_Error = ucSet;

        /* PAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Pap_Event = ucSet;

        /* PAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Pap_Packet = ucSet;

        /* PAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Pap_StateChange = ucSet;

        /* CHAP������Կ��� */
        pstPppDebugInfo->bDebug_Chap_Error = ucSet;

        /* CHAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Chap_Event = ucSet;

        /* CHAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Chap_Packet = ucSet;

        /* CHAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Chap_StateChange = ucSet;
        /* EAP������Կ��� */
        pstPppDebugInfo->bDebug_EAP_Error = ucSet;

        /* EAP�¼����Կ��� */
        pstPppDebugInfo->bDebug_EAP_Event = ucSet;

        /* EAP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_EAP_Packet = ucSet;

        /* EAP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_EAP_StateChange = ucSet;

        pstPppDebugInfo->bDebug_Ip_Packet = ucSet;

        pstPppDebugInfo->bDebug_Scp_Packet = ucSet;

        /* LCP������Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Error = ucSet;

        /* LCP�¼����Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Event = ucSet;

        /* LCP���ĵ��Կ��� */
        pstPppDebugInfo->bDebug_Lcp_Packet = ucSet;

        /* LCP״̬ת�����Կ��� */
        pstPppDebugInfo->bDebug_Lcp_StateChange = ucSet;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����õ������Կ���״̬�����Զ�һ���ӿڽ��У�Ҳ������ȫ�ֵġ� *
*                ���ڽӿڵĿ���״̬��һ������:�κ�ʱ������򿪿��أ�����    *
*                ��Ӧ��ȫ�ֿ���״̬Ϊonʱ�����ܵ����رսӿڿ���״̬��Ϊ��   *
*                ���������⣬����һ���жϣ�����ǶԽӿ�ִ��no debug������ *
*                �򽫽ӿڿ���״̬��Ϊȫ�ֿ��صĵ�ǰֵ��                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppDebugInfo:Ҫ����Ŀ������ݽṹָ��                   *
*                ucSet:ΪVRP_YES���������п��أ�ΪVRP_NO�����ر����п���  *
*                ulType    :debug���ͣ�����event��error��packet��state      *
*                usProtocol:Э���(��0xc021��ʾLCP)��Ϊ0��ʾ"core"          *
* OUTPUT       ����                                                         *
* RETURN       ��0:�ɹ�, ����:������                                        *
* CALLED BY    ��PPP_DebugAll                                               *
*                PPP_NoDebugAll                                             *
*                PPP_Debug_SetInterfaceOption                               *
*                PPP_Debug_SetGlobalOption                                  *
****************************************************************************/
VOID PPP_Debug_SetOneOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                             UCHAR           ucSet,
                             ULONG           ulType,
                             USHORT          usProtocol)
{
    if ((pstPppDebugInfo != &g_stPppDebugInfo) && (ucSet == VRP_NO))
    {
        /* ���ȫ�ֿ��ص�״̬ */
        ucSet = PPP_Debug_GetOption(&g_stPppDebugInfo, ulType, usProtocol);
    }

    switch (usProtocol)
    {
        case 0:
            if (ulType == PPP_DEBUG_EVENT)
            {
                pstPppDebugInfo->bDebug_Core_Event = ucSet;
            }

            break;

        case PPP_LCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_Lcp_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_Lcp_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_Lcp_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_Lcp_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_SCP:
            if (ulType == PPP_DEBUG_PACKET)
            {
                pstPppDebugInfo->bDebug_Scp_Packet = ucSet;
            }

            break;

        case PPP_IP:
            if (ulType == PPP_DEBUG_PACKET)
            {
                pstPppDebugInfo->bDebug_Ip_Packet = ucSet;
            }

            break;

        case PPP_IPCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_Ipcp_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_Ipcp_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_Ipcp_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_Ipcp_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_CCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_Ccp_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_Ccp_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_Ccp_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_Ccp_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_PAP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_Pap_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_Pap_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_Pap_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_Pap_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_CHAP:
            /*lint -fallthrough*/
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_Chap_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_Chap_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_Chap_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_Chap_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }
        /*lint -e825*/
        case PPP_EAP:
        /*lint +e825*/
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    pstPppDebugInfo->bDebug_EAP_Error = ucSet;
                    break;

                case PPP_DEBUG_EVENT:
                    pstPppDebugInfo->bDebug_EAP_Event = ucSet;
                    break;

                case PPP_DEBUG_PACKET:
                    pstPppDebugInfo->bDebug_EAP_Packet = ucSet;
                    break;

                case PPP_DEBUG_STATE:
                    pstPppDebugInfo->bDebug_EAP_StateChange = ucSet;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        default:
            VOS_DBGASSERT ( 0 );
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ȡָ�����Կ���״̬��                                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppDebugInfo:Ҫ����Ŀ������ݽṹָ��                   *
*                ulType    :debug���ͣ�����event��error��packet��state      *
*                usProtocol:Э���(��0xc021��ʾLCP)��Ϊ0��ʾ"core"          *
* OUTPUT       ����                                                         *
* RETURN       ��ָ��ѡ���״̬                                             *
* CALLED BY    ��PPP_Debug_SetOneOption                                     *
****************************************************************************/
UCHAR PPP_Debug_GetOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                           ULONG           ulType,
                           USHORT          usProtocol)
{
    UCHAR ucSet = VRP_NO;

    switch (usProtocol)
    {
        case 0:
            if (ulType == PPP_DEBUG_EVENT)
            {
                ucSet = (UCHAR)pstPppDebugInfo->bDebug_Core_Event;
            }

            break;

        case PPP_LCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Lcp_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Lcp_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Lcp_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Lcp_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_SCP:
            if (ulType == PPP_DEBUG_PACKET)
            {
                ucSet = (UCHAR)pstPppDebugInfo->bDebug_Scp_Packet;
            }

            break;
        case PPP_IP:
            if (ulType == PPP_DEBUG_PACKET)
            {
                ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ip_Packet;
            }

            break;
        case PPP_IPCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ipcp_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ipcp_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ipcp_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ipcp_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_CCP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ccp_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ccp_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ccp_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Ccp_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        case PPP_PAP:
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Pap_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Pap_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Pap_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Pap_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        /*lint -e825*/
        case PPP_CHAP:
            /*lint +e825*/
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Chap_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Chap_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Chap_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_Chap_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }
        /*lint -e825*/
        case PPP_EAP:
        /*lint +e825*/
            switch (ulType)
            {
                case PPP_DEBUG_ERROR:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_EAP_Error;
                    break;

                case PPP_DEBUG_EVENT:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_EAP_Event;
                    break;

                case PPP_DEBUG_PACKET:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_EAP_Packet;
                    break;

                case PPP_DEBUG_STATE:
                    ucSet = (UCHAR)pstPppDebugInfo->bDebug_EAP_StateChange;
                    break;

                default:
                    VOS_DBGASSERT ( 0 );
            }

            break;

        default:
            VOS_DBGASSERT ( 0 );
    }

    return ucSet;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��������ڱ��ĵĵ�����Ϣ,ֻ��Է���PPP״̬���Ŀ���Э��       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
*                ucIsInPacket:�Ƿ������뱨��                                *
*                usProtocol:����Э���                                      *
*                ucIsInPacket:�����뱨��(PPP_DEBUG_PACKET_IN)               *
*                             �����������(PPP_DEBUG_PACKET_OUT)            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_LCP_ReceivePacket��                                    *
****************************************************************************/
VOID PPP_Debug_FsmPacket(PPPINFO_S* pstPppInfo,
                         UCHAR *    pPacket,
                         ULONG      ulLen,
                         USHORT     usProtocol,
                         UCHAR      ucIsInPacket)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    ULONG ulTotalLen = ulLen + PPP_HDRLEN;
    UCHAR ucCode, ucId;
    USHORT sFrameLen = 0;
    LONG lLen = (LONG)ulLen;

    /* ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  code |  ID   |    frame len  |   ...     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |------------- lLen / sFrameLen ------------|
                                    pPacket
     */

    szDebugBuf[0] = '\0';

    VOS_DBGASSERT(pstPppInfo);
    VOS_DBGASSERT(pPacket);

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Packet: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s(%04x) Pkt, Len %lu ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        (ucIsInPacket == PPP_DEBUG_PACKET_IN) ? "Input " : "Output",
                        PPP_Debug_GetProtocolName(usProtocol),
                        usProtocol,
                        ulTotalLen
            );

    /* �Ϸ��Լ�� */
    if (lLen < 4)
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      Value: %s ",
                            PPP_Debug_GetValueStr(pPacket, (UCHAR)lLen)
                );
        pBuf += VOS_sprintf(pBuf, "\r\n      Error: packet too short, discard.");
        PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

        return;
    }

    /* �������ݱ��� */
    switch (usProtocol)
    {
        case PPP_IP:
        case PPP_IPX:
        case PPP_OSI:
 #if (VRP_MODULE_IP_MPLS_SOFTFW == VRP_YES)
        case PPP_MPLS:
        case PPP_MPLS_MCAST:
 #endif
            PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);
            return;

        case PPP_SCP:
            return;

        default:
            break;
    }

    if (NULL == pPacket)
    {
        VOS_DBGASSERT(0);
        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(sFrameLen, pPacket);

    pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                        PPP_Debug_GetProtoState(pstPppInfo, usProtocol),
                        PPP_Debug_GetCode(ucCode),
                        ucCode,
                        ucId,
                        sFrameLen
            );

    sFrameLen -= 4;

    /* ������� */

    /*
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     ...   |  code |  ID   |    frame len  |          ...          |
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |-------- lLen ---------|
     |------ sFrameLen ------|
                                           pPacket
     */

    if (ucCode >= TERMREQ)
    {
        switch (ucCode)
        {
            case TERMREQ:
            case TERMACK:
                break;

            case CODEREJ:
                pBuf += VOS_sprintf(pBuf, "\r\n      Reject Code %x ", *pPacket);
                break;

            case PROTREJ:
                pBuf += VOS_sprintf(pBuf, "\r\n      Reject Protocol %s ", PPP_Debug_GetValueStr(pPacket, 2));
                break;

            case ECHOREQ:
            case ECHOREP:
                pBuf += VOS_sprintf(pBuf, "\r\n      Magic Number %s ", PPP_Debug_GetValueStr(pPacket, (UCHAR)sFrameLen));
                break;

            case DISCREQ:
            case IDENTIFIC:
            case TIMEREMAIN:
                break;

 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
            case RESETREQ:
            case RESETACK:

                /* Э��涨:RSETERQ��RSETACK���Ŀ��Դ�����ֽڵ�data,
                   ��Э�鲻����data������.�����ֻ��data���,
                 */
                pBuf += VOS_sprintf(pBuf, "%s ", PPP_Debug_GetValueStr(pPacket, (UCHAR)sFrameLen));
                break;
 #endif

            default:
                break;
        }

        PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

        return;
    }


    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������Э��״̬ת���ĵ�����Ϣ                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
*                ucNewState:״̬����״̬                                    *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ChangeState                                        *
****************************************************************************/
VOID PPP_Debug_FsmStateChange(PPPFSM_S *pstFsm, UCHAR ucNewState)
{
    PPPINFO_S *pstPppInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cState[20], cNewState[20];

    szDebugBuf[0] = 0;
    cState[0] = 0;
    cNewState[0] = 0;

    VOS_DBGASSERT(pstFsm);

    if (NULL == pstFsm)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */


    /* �ж��Ƿ����debug���� */
    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Lcp_StateChange == VRP_NO)
            {
                return;
            }

            break;

        case PPP_IPCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_StateChange == VRP_NO)
            {
                return;
            }

            break;

        case PPP_CCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_StateChange == VRP_NO)
            {
                return;
            }

            break;


        default:
            break;
    }

    if (pstFsm->ucState == ucNewState)
    {
        return;
    }

    if (pstFsm->ucState > (ULONG)PPP_STATE_OPENED)
    {
        /* �����״̬ */
        (VOID)VOS_sprintf(cState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cState, "%s", g_cPPP_Debug_state[pstFsm->ucState]);
    }

    if (ucNewState > (ULONG)PPP_STATE_OPENED)
    {
        /* �����״̬ */
        (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cNewState, "%s", g_cPPP_Debug_state[ucNewState]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                        PPP_Debug_GetInterfaceName((PPPINFO_S*)pstFsm->pPppInfo),
                        PPP_Debug_GetProtocolName(pstFsm->usProtocol),
                        cState,
                        cNewState);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), (PPPINFO_S*)pstFsm->pPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������Э�鷢���ⲿ�¼��ĵ�����Ϣ                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
*                ulEvent:״̬���¼�                                         *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent��                                     *
****************************************************************************/
VOID PPP_Debug_FsmEvent(PPPFSM_S* pstFsm, ULONG ulEvent)
{
    PPPINFO_S* pstPppInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    CHAR cState[20], cEvent[100];

    szDebugBuf[0] = 0;
    cState[0] = 0;
    cEvent[0] = 0;

    VOS_DBGASSERT(pstFsm);

    if (NULL == pstFsm)
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ((PPP_STATE_BUTT <= pstFsm->ucState) || (PPP_EVENT_FSM_BUTT <= ulEvent))
    {
         return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    /* �ж��Ƿ����debug���� */
    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:
            g_ulPppFsmStat[0][ulEvent * PPP_STATE_BUTT + pstFsm->ucState]++;
            if (pstPppInfo->stPppDebugInfo.bDebug_Lcp_Event == VRP_NO)
            {
                return;
            }

            break;

        case PPP_IPCP:
            g_ulPppFsmStat[1][ulEvent * PPP_STATE_BUTT + pstFsm->ucState]++;
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Event == VRP_NO)
            {
                return;
            }

            break;
        case PPP_IPV6CP:
            g_ulPppFsmStat[3][ulEvent * PPP_STATE_BUTT + pstFsm->ucState]++;
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipv6cp_Event == VRP_NO)
            {
                return;
            }

            break;

        case PPP_VSNCP:
            g_ulPppFsmStat[4][ulEvent * PPP_STATE_BUTT + pstFsm->ucState]++;

            return;


        case PPP_CCP:
            g_ulPppFsmStat[2][ulEvent * PPP_STATE_BUTT + pstFsm->ucState]++;
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Event == VRP_NO)
            {
                return;
            }

            break;
        default:
            break;
    }

    if (pstFsm->ucState > (ULONG)PPP_STATE_OPENED)
    {
        /* �����״̬ */
        (VOID)VOS_sprintf(cState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cState, "%s", g_cPPP_Debug_state[pstFsm->ucState]);
    }

    if (ulEvent > (ULONG)PPP_EVENT_FSM_RXR)
    {
        /* ������¼� */
        (VOID)VOS_sprintf(cEvent, "%s", "Error-Event");
    }
    else
    {
        (VOID)VOS_sprintf(cEvent, "%s", g_cPPP_Debug_event[ulEvent]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s Event ",
                        PPP_Debug_GetInterfaceName((PPPINFO_S*)pstFsm->pPppInfo),
                        PPP_Debug_GetProtocolName(pstFsm->usProtocol),
                        cEvent);

    pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                        cState);

    /* TO+�¼�:��ʾretransmit������ֵ */
    if (ulEvent == (ULONG)PPP_EVENT_FSM_TO_PLUS)
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit = %d ", pstFsm->sRetransmits);
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), (PPPINFO_S*)pstFsm->pPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����״̬�������¼�(��״̬���е�'-')��Ϣ                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
*                ulEvent:״̬���¼�                                         *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent��                                     *
****************************************************************************/
VOID PPP_Debug_FsmIllegalEvent(PPPFSM_S* pstFsm, ULONG ulEvent)
{
    PPPINFO_S *pstPppInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = 0;

    VOS_DBGASSERT(pstFsm);

    if (NULL == pstFsm)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */
    /* �ж��Ƿ����debug���� */
    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Lcp_Event == VRP_NO)
            {
                return;
            }

            break;

        case PPP_IPCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Event == VRP_NO)
            {
                return;
            }

            break;

        case PPP_CCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Event == VRP_NO)
            {
                return;
            }

            break;

        default:
            break;
    }

    /* ���������Ϣ��log��Ϣ */
    pBuf += VOS_sprintf(pBuf, "\r\n      It's an illegal event %lu", ulEvent);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), (PPPINFO_S*)pstFsm->pPppInfo);
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������Э����ִ������Ϣ                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
*                usLogLevel:LOG����                                         *
*                pString   :Ҫ������ִ�                                    *
* OUTPUT       ��                                                           *
* RETURN       ��                                                           *
* CALLED BY    ������Э��                                                   *
****************************************************************************/
VOID PPP_Debug_Error(PPPFSM_S *pstFsm, USHORT usLogLevel, CHAR *pString)
{
    PPPINFO_S *pstPppInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = 0;

    VOS_DBGASSERT(pstFsm);

    if (VRP_NO == g_ulPppDebugSwitch)
    {
        return;
    }

    if (NULL == pstFsm)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    /* �ж��Ƿ����debug���� */
    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Lcp_Error == VRP_NO)
            {
                return;
            }

            break;

        case PPP_IPCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Error == VRP_NO)
            {
                return;
            }

            break;

        case PPP_CCP:
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Error == VRP_NO)
            {
                return;
            }

            break;

        default:
            break;
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Error: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s ",
                        PPP_Debug_GetInterfaceName((PPPINFO_S*)pstFsm->pPppInfo),
                        PPP_Debug_GetProtocolName(pstFsm->usProtocol),
                        pString);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), (PPPINFO_S*)pstFsm->pPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����PPP�ں˷������¼�                                      *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                usLogLevel:LOG����                                         *
*                pString   :Ҫ������ִ�                                    *
* OUTPUT       ��                                                           *
* RETURN       ��                                                           *
* CALLED BY    ��Э�����ģ��                                               *
****************************************************************************/
VOID PPP_Debug_CoreEvent(PPPINFO_S *pstPppInfo,
                         USHORT     usLogLevel,
                         CHAR *     pString)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = 0;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    /* �ж��Ƿ����debug���� */
    if (pstPppInfo->stPppDebugInfo.bDebug_Core_Event == VRP_NO)
    {
        return;
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s : %s ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        pString);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ýӿ���                                                 *
* MODIFY DATE  ��modified by gxf for GGSN80 20030224                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_LcpPacket��                                      *
****************************************************************************/
CHAR *PPP_Debug_GetInterfaceName(PPPINFO_S *pstPppInfo)
{
    static CHAR szDebugStr[256];
    CHAR *str = szDebugStr;

    /*IFNET_S *pstIfnet ;*/

    szDebugStr[0] = 0;

    /*BYHD11699 for B027*/
    /*VOS_DBGASSERT(pstPppInfo) ;*/
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return NULL;
    }

    /*pstIfnet = (IFNET_S *)IF_GetIfByIndex(pstPppInfo->ulIfIndex) ;

    if(pstIfnet)
    {
        str += VOS_sprintf(str, "%s", pstIfnet->if_szIfName) ;
    }
    else
    {
        str[0] = 0 ;
    }*/

    /* deleted by gxf 20030311 for test    distributed code must del the coment */
    /*VOS_sprintf(str, "%s", pstPppInfo->pstConfigInfo->ucDomainName) ;*/
    VOS_sprintf(str, "%lu", pstPppInfo->ulRPIndex);
    return szDebugStr;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ñ���������                                             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_FsmPacket                                        *
****************************************************************************/
CHAR *PPP_Debug_GetCode(UCHAR ucCode)
{
    /* 15: RESETACK */
    if (ucCode <= 15)
    {
        return g_cPPP_Debug_code[ucCode];
    }
    else
    {
        return "UNKNOWN";
    }
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����Э��ѡ��������                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��usProtocol:Э���                                          *
*                ucType:��������                                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_LcpPacket��                                      *
****************************************************************************/
CHAR *PPP_Debug_GetTypeName(USHORT usProtocol, UCHAR ucType)
{
    static CHAR szDebugStr[256];
    CHAR *str = szDebugStr;

    szDebugStr[0] = 0;

    switch (usProtocol)
    {
        case PPP_LCP:
            str += VOS_sprintf(str, "%s", PPP_Debug_GetLcpTypeName(ucType));
            break;

        case PPP_IPCP:
            str += VOS_sprintf(str, "%s", PPP_Debug_GetIpcpTypeName(ucType));
            break;

        case PPP_CCP:
        case PPP_MCP:
            str += VOS_sprintf(str, "%s", PPP_Debug_GetCcpTypeName(ucType));
            break;

        default:
            str += VOS_sprintf(str, "UNKNOWN");
    }

    return szDebugStr;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����Э����                                                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��usProtocol:Э���                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_LcpPacket��                                      *
****************************************************************************/
CHAR *PPP_Debug_GetProtocolName(USHORT usProtocol)
{
    ULONG ulIndex;

    switch (usProtocol)
    {
        case PPP_IP:
            ulIndex = 0;
            break;
        case PPP_LCP:
            ulIndex = 1;
            break;
        case PPP_PAP:
            ulIndex = 2;
            break;
        case PPP_CHAP:
            ulIndex = 3;
            break;
        case PPP_IPCP:
            ulIndex = 4;
            break;
        case PPP_IPXCP:
            ulIndex = 5;
            break;
        case PPP_MP:
            ulIndex = 6;
            break;
        case PPP_BCP:
            ulIndex = 7;
            break;
        case PPP_BP:
            ulIndex = 8;
            break;
        case PPP_VJ_COMP:
            ulIndex = 9;
            break;
        case PPP_VJ_UNCOMP:
            ulIndex = 10;
            break;
        case PPP_IPX:
            ulIndex = 11;
            break;
        case PPP_CCP:
            ulIndex = 12;
            break;
        case PPP_MCCP:
            ulIndex = 13;
            break;
        case PPP_SCP:
            ulIndex = 14;
            break;
        case PPP_MCP:
            ulIndex = 15;
            break;
        case PPP_MPLSCP:
            ulIndex = 16;
            break;
        case PPP_MPLS_UNICAST:
            ulIndex = 17;
            break;
        case PPP_MPLS_MULTICAST:
            ulIndex = 18;
            break;
        case PPP_OSICP:
            ulIndex = 19;
            break;
        case PPP_OSI_NPDU:
            ulIndex = 20;
            break;
        case PPP_VSNCP:
            ulIndex = 21;
            break ;
        case PPP_EAP:
            ulIndex = 22;
            break;
        case PPP_IPV6CP:
            ulIndex = 23;
            break;
        default:
            return "UNKNOWN";
    }

    return g_cPPP_Debug_Protocol_Name[ulIndex];
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������ַ�����16���Ʊ�ʾ��ʽ                                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��pStr:�ַ�����ָ��                                          *
*                ucLen:�ַ�������                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_LcpPacket��                                      *
****************************************************************************/
CHAR *PPP_Debug_GetValueStr(UCHAR *pStr, UCHAR ucLen)
{
    UCHAR i;
    static CHAR szDebugStr[256];
    CHAR *pData = szDebugStr;

    szDebugStr[0] = 0;

    VOS_DBGASSERT(pStr);

    if (ucLen >= 200)
    {
        return "Too Long! ";
    }

    if (NULL == pStr)
    {
        VOS_DBGASSERT(0);
        return "NULL";
    }

    for (i = 0; i < ucLen; i++, pStr++)
    {
        pData += VOS_sprintf(pData, "%02x", *pStr);
    }

    pData += VOS_sprintf(pData, " ");

    return szDebugStr;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����Э��״̬                                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                usProtocol:Э���                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_LcpPacket��                                      *
****************************************************************************/
CHAR *PPP_Debug_GetProtoState(PPPINFO_S *pstPppInfo, USHORT usProtocol)
{
    PPPFSM_S *pstFsm = NULL;

    VOS_DBGASSERT(pstPppInfo);

    switch (usProtocol)
    {
        case PPP_LCP:
            if (NULL == pstPppInfo)
            {
                VOS_DBGASSERT(0);
                return "NULL";
            }

            if (pstPppInfo->pstLcpInfo)
            {
                pstFsm = &(((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stFsm);
            }

            break;

        case PPP_IPCP:
            if (NULL == pstPppInfo)
            {
                VOS_DBGASSERT(0);
                return "NULL";
            }

            if (pstPppInfo->pstIpcpInfo)
            {
                pstFsm = &(((PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo)->stFsm);
            }

            break;

        case PPP_CCP:
        case PPP_MCP:
            if (NULL == pstPppInfo)
            {
                VOS_DBGASSERT(0);
                return "NULL";
            }

            if (pstPppInfo->pstCcpInfo)
            {
                pstFsm = &(((PPP_CCP_INFO_S *)pstPppInfo->pstCcpInfo)->stFsm);
            }

            break;

        default:
            break;
    }

    if (pstFsm)
    {
        if (pstFsm->ucState <= (ULONG)PPP_STATE_OPENED)
        {
            return g_cPPP_Debug_state[pstFsm->ucState];
        }
        else
        {
            return "error-state";
        }
    }
    else
    {
        return "NULL";
    }
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����LCPЭ��ѡ��������                                      *
* MODIFY DATE  ��                                                           *
* INPUT        ��ucType:��������                                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_GetTypeName                                      *
****************************************************************************/
CHAR *PPP_Debug_GetLcpTypeName(UCHAR ucType)
{
    int iIndex;

    switch (ucType)
    {
        case LCP_CI_MRU:
        case LCP_CI_ASYNCMAP:
        case LCP_CI_AUTHTYPE:
        case LCP_CI_QUALITY:
        case LCP_CI_MAGICNUMBER:
        case LCP_CI_PCOMPRESSION:
        case LCP_CI_ACCOMPRESSION:
            iIndex = ucType;
            break;
        case LCP_CI_MRRU:
            iIndex = 9;
            break;
        case LCP_CI_SSNHF:
            iIndex = 10;
            break;
        case LCP_CI_DISCR:
            iIndex = 11;
            break;
        case LCP_CI_CALLBACK:
            iIndex = 12;
            break;
        default:
            return "UNKNOWN";
    }

    return (g_cPPP_Debug_LcpOption[iIndex]);
}


/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����IPCPЭ��ѡ��������                                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��ucType:��������                                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_GetTypeName                                      *
****************************************************************************/
CHAR *PPP_Debug_GetIpcpTypeName(UCHAR ucType)
{
    int iIndex;

    switch (ucType)
    {
        case IPCP_CI_ADDRS:
        case IPCP_CI_COMPRESSTYPE:
        case IPCP_CI_ADDR:
            iIndex = ucType;
            break;

        case IPCP_CI_DNSADDR0:
        case IPCP_CI_NBNSADDR0:
        case IPCP_CI_DNSADDR1:
        case IPCP_CI_NBNSADDR1:
            iIndex = ucType - IPCP_CI_DNSADDR0 + 4;
            break;

        default:
            return "UNKNOWN";
    }

    return g_cPPP_Debug_IpcpOption[iIndex];
}


/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����CCPЭ��ѡ��������                                      *
* MODIFY DATE  ��                                                           *
* INPUT        ��ucType:��������                                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Debug_GetTypeName                                      *
****************************************************************************/
CHAR *PPP_Debug_GetCcpTypeName(UCHAR ucType)
{
    switch (ucType)
    {
        case CI_STAC_COMPRESS:
            return "Stac Compress";
        case CI_MPPC_COMPRESS:
            return "Mppc Compress";

        default:
            return "UNKNOWN";
    }
}


/****************************************************************************
* CREATE DATE  ��2000/06/20                                                 *
* CREATED BY   ��Zhu Feng Zhi                                                 *
* FUNCTION     ��Ϊ�ַ������ʾ��ֹ��"/0",�Ա���ʾ							*
* MODIFY DATE  ��                                                           *
* INPUT        ��pStr:�ַ�����ָ��                                          *
*                ucLen:�ַ�������                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PAP_Debug_Packet,CHAP_Debug_Packet                         *
****************************************************************************/
CHAR *PPP_Debug_GetString(UCHAR *pStr, UCHAR ucLen)
{
    static CHAR szDebugStr[256];
    CHAR *pData = szDebugStr;

    szDebugStr[0] = 0;

    VOS_DBGASSERT(pStr);

    if (ucLen >= 200)
    {
        return "Too Long! ";
    }

    (VOID)VOS_MemCpy((UCHAR*)pData, (CHAR*)pStr, (ULONG)ucLen);

    /*����ַ���������*/
    if (pData[ucLen] != 0)
    {
        pData[ucLen] = 0;
    }

    return szDebugStr;
}
ULONG PPP_InitDebugInfo()
{
    PPP_MemSet((void *)&g_pstPppInnerDebugInfo[0], 0, sizeof(PPP_DEBUG_INFO_S) * PPP_INNER_COUTNER_END);

    PPP_MemSet((void *)&g_pstPppErrorDebugInfo, 0, sizeof(PPP_DEBUG_INFO_S) * PPP_ERROR_COUNTER_END);

    /* PPP�ڲ�������ʼ�� */
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_000, " Recieved A11 Up Event!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_001, " Recieved A11 Down Event!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_002, " Recieved Lap force Ip Address Release!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_003, " Recieved Lap force Ip Address Release!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_004, " Recieved Lap statisc Ip Address rebuilt start!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_005, " Recieved Lap statisc Ip Address rebuilt end!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_006, " Recieved Lap Moudle Ip Address conflict and active failed!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_007, " Recieved Lap Ip Address allocate success!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_008, " Recieved l2tp Up Event!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_009, " Recieved l2tp Down Event! ");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_010, " A11 Notfify Ppp Down!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_011, " Recieved PF Renego Msg!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_012, " A11 Notify Ppp Down!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_013, " Ppp notify Auth PPP renego start!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_014, " Lcp down notify L2TP down!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_015, " Lcp down delete Pppinfo CB!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_016, " Ipcp up success!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_017, " Ipcp up without ip address success!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_018, " Ipcp up with ip address success! ");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_019, " Subboard down result in renegotiation");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_020, " Check VJ forbidden!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_021, " Check MPPC forbidden!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_022, " Add compress user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_023, " Add VJ user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_024, " Add MPPC user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_025, " Add Stac_ZLS0 user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_026, " Add Stac_ZLS1 user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_027, " PPP Nego link list timeout ");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_028, " PPP fsm timout, PPP CB not exist");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_029, " PPP fsm timout, PPP Index is invalide");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_030, " Recieved Lcp configure request, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_031, " Recieved Lcp configure ack, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_032, " Recieved Lcp configure nak/reject, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_033, " Recieved Lcp terminate ack, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_034, " Recieved Lcp configure request, Ppp start renego and auth to AAA");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_035, " Recieved Lcp configure request, Ppp start renego notify to CM sucessfully");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_036, " PPP Start timer counter");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_037, " PPP timeout counter");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_038, " Lcp Up, PeerIPAddr is valid and bReNego is zero");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_039, " PPP create cb number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_040, " PPP delete cb number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_041, " PPP bReNego is true and ulPeerIPAddr is valid or user is CMIP!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_042, " PPP Recieved PPP_GET_PEERIPADDR enter Core!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_043, " PPP Recieved PPP_GET_PEERIPADDR enter Core!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_044, " PPP delete CB, release IP Address request!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_045, " PPP delete CB, release IP Address success!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_046, " PPP recieved AAA Ip Address!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_047, " PPP recieved AAA pool name null!");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_048, " Recieved Ipcp configure request, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_049, " Recieved Ccp configure request, PPP start renego");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_050, " Recieved Lcp configure request at auth phase");

    /*Modified by liushuang for pcc*/
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_051, " PPP Send SE Request to Pcrfc");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_052, " PPP Received SE Reply from pcrfc");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_053, " PPP Received SE Reply from pcrfc, retcode success");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_054, " PPP Received SE Reply from pcrfc, retcode rollback");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_055, " PPP Received SE Reply from pcrfc, retcode no rollback");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_056, " ppp mppc&vj user number add and mppc user number dec");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_057, " ppp mppc&vj user number add and vj user number dec");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_058, " ppp vj user number dec");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_059, " ppp mppc&vj user number dec and mppc user number add");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_060, " ppp mppc user number dec");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_061, " ppp mppc&vj user number dec and vj user number add");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_062, " ppp back vj user number add");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_063, " ppp back mppc user number add");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_064, " ppp add vj user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_065, " ppp add mppc user number");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_066, " ppp dec vj user number for ipcp down");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_067, " ppp dec vj user number for ppp down");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_068, " ppp dec mppc user number for ppp down");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_069, " ppp dec mppc user number for ccp down");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_070, " ppp dec vj user number for get add err");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_071, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_072, " Recieved Lcp configure request, PPP renego start");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_073, " ppp Timer Create fail");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_074, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_075, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_076, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_077, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_078, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_079, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_080, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_081, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_082, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_083, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_084, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_085, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_086, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_087, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_088, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_089, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_090, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_091, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_092, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_093, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_094, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_095, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_096, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_097, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_098, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_099, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_100, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_101, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_102, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_103, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_104, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_105, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_106, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_107, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_108, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_109, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_110, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_111, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_112, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_113, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_114, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_115, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_116, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_117, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_118, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_119, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_120, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_121, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_122, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_123, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_124, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_125, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_126, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_127, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_128, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_129, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_130, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_131, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_132, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_133, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_134, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_135, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_136, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_137, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_138, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_139, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_140, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_141, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_142, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_143, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_144, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_145, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_146, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_147, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_148, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_149, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_150, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_151, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_152, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_153, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_154, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_155, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_156, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_157, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_158, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_159, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_160, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_161, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_162, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_163, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_164, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_165, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_166, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_167, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_168, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_169, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_170, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_171, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_172, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_173, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_174, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_175, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_176, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_177, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_178, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_179, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_180, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_181, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_182, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_183, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_184, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_185, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_186, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_187, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_188, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_189, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_190, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_191, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_192, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_193, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_194, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_195, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_196, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_197, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_198, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_199, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_200, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_201, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_202, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_203, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_204, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_205, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_206, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_207, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_208, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_209, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_210, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_211, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_212, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_213, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_214, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_215, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_216, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_217, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_218, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_219, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_220, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_221, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_222, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_223, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_224, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_225, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_226, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_227, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_228, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_229, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_230, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_231, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_232, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_233, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_234, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_235, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_236, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_237, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_238, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_239, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_240, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_241, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_242, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_243, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_244, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_245, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_246, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_247, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_248, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_249, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_250, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_251, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_252, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_253, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_254, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_255, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_256, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_257, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_258, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_259, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_260, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_261, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_262, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_263, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_264, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_265, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_266, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_267, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_268, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_269, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_270, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_271, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_272, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_273, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_274, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_275, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_276, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_277, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_278, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_279, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_280, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_281, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_282, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_283, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_284, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_285, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_286, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_287, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_288, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_289, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_290, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_291, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_292, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_293, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_294, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_295, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_296, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_297, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_298, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_299, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_300, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_301, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_302, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_303, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_304, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_305, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_306, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_307, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_308, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_309, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_310, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_311, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_312, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_313, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_314, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_315, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_316, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_317, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_318, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_319, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_320, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_321, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_322, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_323, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_324, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_325, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_326, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_327, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_328, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_329, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_330, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_331, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_332, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_333, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_334, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_335, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_336, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_337, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_338, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_339, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_340, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_341, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_342, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_343, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_344, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_345, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_346, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_347, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_348, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_349, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_350, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_351, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_352, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_353, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_354, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_355, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_356, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_357, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_358, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_359, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_360, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_361, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_362, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_363, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_364, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_365, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_366, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_367, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_368, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_369, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_370, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_371, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_372, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_373, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_374, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_375, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_376, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_377, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_378, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_379, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_380, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_381, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_382, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_383, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_384, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_385, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_386, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_387, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_388, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_389, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_390, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_391, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_392, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_393, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_394, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_395, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_396, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_397, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_398, "");
    M_PPP_INNER_STAT_DEF(PPP_INNER_COUTNER_399, "");


    /* PPP���������ʼ�� */
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER000, " Recieved Lap force release IP Address, PPPInfo CB not exitst!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER001, " Recieved Lap reply message, PPPInfo CB not exitst!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER002, " Recieved Lap reply message, PPPInfo Dhcp null or Dhcp State error!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER003, " Recieved Lap reply message, Allocate IP Address failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER004, " Write Lap MCQueue failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER005, " Recieved l2tp RpIndex error!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER006, " Recieved l2tp Up message, PPPInfo CB not exist!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER007, " Recieved l2tp Up message, Call A11 L2tp Up failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER008, " Recieved PF renego event, find Rpcontext failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER009, " Recieved PF renego event, find A10 index failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER010, " Recieved PF renego event, Call Ppc renego failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER011, " A11 Notify Ppp Down write queue failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER012, " Ppp Lcp up to notify A11 cannot get Rpcontext!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER013, " Ppp ipcp up to notify A11 failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER014, " Ipcp up without ip, mipagent user deactive!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER015, " Ipcp up without ip, notify FA failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER016, " Ipcp up without ip, coraddr error or reached max user!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER017, " Ipcp up without ip, notify LAP release IP address failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER018, " Ipcp up with ip, renego other user type!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER019, " Ipcp up negoation noauth user!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER020, " Ipcp up with ip, radius allocate ip address!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER021, " AAA result success, pap/chap state error!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER022, " AAA result auth failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER023, " Recieved AAA result, Ppp info CB null!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER024, " All subboard down, deactive VJ user!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER025, " DomainIndex invaild, when increase compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER026, " DmpuId or DpeId invaild, when increase compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER027, " Invaild compress type, when increase compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER028, " DomainIndex invaild, when decrease compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER029, " DmpuId or DpeId invaild, when decrease compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER030, " VJ flag wrong, when decrease compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER031, " MPPC flag wrong, when decrease compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER032, " Invaild compress type, when decrease compress user number!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER033, " Recieved Ppp negoniation packet, user not exist!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER034, " Recieved Ppp illegal negoniation packet, it`s length too short");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER035, " PPP fsm timeout, lcp protocol ppp cb not exist");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER036, " PPP fsm timeout, ccp protocol ppp cb not exist");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER037, " PPP fsm timeout, ipcp protocol ppp cb not exist");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER038, " PPP fsm timeout, sub protocol type isnot matched protocol");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER039, " PPP fsm timeout, PppInfo is null");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER040, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER041, " PMIP User license is error");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER042, " PPP Recieved PPP_GET_PEERIPADDR enter Core, but ulPeerIPAddr is not 0!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER043, " PPP apply IP address, write LAP queue failed!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER044, " PPP apply IP address timeout, PeerIPAddr is valid!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER045, " PPP ipcp up without IP Address, PeerIPAddr is valid");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER046, " PPP ipcp up without IP Address, PeerIPAddr is valid");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER047, " PPP recieved LAP reply, but PeerIPAddr is valid");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER048, " CHAP recieved response, CHAP state is error!");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER049, " NAI lenth is error");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER050, " ppp cb is null when dec compress user count");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER051, " ppp cb is null when add compress user count");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER052, " ppp pap fail");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER053, " ppp chap fail");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER054, " ppp eap fail");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER055, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER056, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER057, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER058, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER059, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER060, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER061, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER062, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER063, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER064, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER065, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER066, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER067, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER068, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER069, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER070, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER071, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER072, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER073, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER074, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER075, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER076, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER077, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER078, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER079, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER080, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER081, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER082, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER083, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER084, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER085, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER086, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER087, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER088, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER089, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER090, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER091, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER092, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER093, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER094, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER095, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER096, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER097, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER098, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER099, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER100, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER101, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER102, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER103, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER104, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER105, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER106, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER107, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER108, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER109, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER110, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER111, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER112, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER113, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER114, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER115, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER116, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER117, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER118, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER119, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER120, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER121, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER122, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER123, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER124, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER125, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER126, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER127, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER128, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER129, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER130, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER131, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER132, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER133, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER134, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER135, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER136, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER137, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER138, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER139, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER140, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER141, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER142, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER143, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER144, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER145, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER146, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER147, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER148, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER149, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER150, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER151, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER152, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER153, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER154, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER155, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER156, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER157, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER158, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER159, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER160, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER161, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER162, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER163, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER164, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER165, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER166, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER167, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER168, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER169, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER170, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER171, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER172, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER173, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER174, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER175, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER176, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER177, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER178, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER179, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER180, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER181, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER182, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER183, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER184, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER185, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER186, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER187, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER188, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER189, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER190, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER191, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER192, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER193, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER194, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER195, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER196, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER197, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER198, "");
    M_PPP_ERROR_STAT_DEF(PPP_ERROR_COUNTER199, "");

    return VOS_OK;

}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
