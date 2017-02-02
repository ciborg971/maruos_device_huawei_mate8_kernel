
#include "siappstk.h"

/*******************************************************************
*������:������Ϣʧ��
*���⺯����������:
*Ԥ�ڽ����
************************* �޸ļ�¼ *********************************
#  1.��    ��:
#    ��    ��:
#    �޸�����: �½�CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_MENUSEL;

    if (VOS_ERR != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*������:�����������
*���⺯����������:
*Ԥ�ڽ����
************************* �޸ļ�¼ *********************************
#  1.��    ��:
#    ��    ��:
#    �޸�����: �½�CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case2(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	if (VOS_ERR != SI_STK_MenuSelection(0,0,0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*������:�����������2
*���⺯����������:
*Ԥ�ڽ����
************************* �޸ļ�¼ *********************************
#  1.��    ��:
#    ��    ��:
#    �޸�����: �½�CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case3(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_PPDOWN;

    if (VOS_ERR != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*������:������Ϣ�ɹ�
*���⺯����������:
*Ԥ�ڽ����
************************* �޸ļ�¼ *********************************
#  1.��    ��:
#    ��    ��:
#    �޸�����: �½�CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case4(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_MENUSEL;

    if (VOS_OK != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}



unsigned int uttest_SI_STK_SetUpCallConfirm_case1(void)
{
	// ��������
	VOS_UINT32                          ulAction;
	MN_CLIENT_ID_T						ClientId;
	VOS_UINT32                          ulRet;

	ulAction							=	SI_STK_SETUPCALL_BUTT;
	ClientId							=	0;

	// ���ñ��⺯��
	ulRet = SI_STK_SetUpCallConfirm(ClientId, ulAction);

	// ִ�м��
    if (VOS_ERR != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


unsigned int uttest_SI_STK_SetUpCallConfirm_case2(void)
{
	// ��������
	VOS_UINT32                          ulAction;
	MN_CLIENT_ID_T						ClientId;
	VOS_UINT32                          ulRet;

	ulAction							=	SI_STK_SETUPCALL_ALLOW;
	ClientId							=	0;

	// ���ñ��⺯��
	ulRet = SI_STK_SetUpCallConfirm(ClientId, ulAction);

	// ִ�м��
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


/*******************************************************************
�����������      :
������������      :
Ԥ�ڽ��          : ��������
�޸���ʷ          :
1.��   ��  : 2012-09-24
  ��   ��  :
  �޸����� :
*******************************************************************/
unsigned int uttest_SI_STK_SendReqMsg_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case2(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case3(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case4(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;
	MODEM_ID_ENUM_UINT16    enModemID = MODEM_ID_1;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case5(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_QuerySTKCommand_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STK_QuerySTKCommand(0,0))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_TerminalResponse_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_STK_TERMINAL_RSP_STRU  stTRStru = {0};

	if (TAF_FAILURE != SI_STK_TerminalResponse(0,0, &stTRStru))
	{
        return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STKDualIMSIChangeReq_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STKDualIMSIChangeReq(0,0))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STKIsDualImsiSupport_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STKIsDualImsiSupport())
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case6(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}
