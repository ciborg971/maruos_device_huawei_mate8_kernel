/************************************************************************
*                                                                      *
*                             ppp_init.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPPģ���ʼ������                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PPPģ��ĳ�ʼ������                                  *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
#include "hdlc_hardware.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_INIT_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if 1
ULONG g_ulA11RpifVpnId = 0;
stDomainNumInfo g_pstA11DomainNumInfo[5];
VOID PPP_RPNegoListProc(VOID* pPara);
#endif

ULONG g_ulHsgwPppPerfInitOkFlg = VOS_FALSE;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID PPPC_MsgTimerProc( struct MsgCB * pMsg )
{
    REL_TIMER_MSG  *pPsMsg      = (REL_TIMER_MSG  *)pMsg;
    VOS_UINT32      ulPppId     = pPsMsg->ulName;
    VOS_VOID *      pFsm;


    /*�ж����Ǹ��׶������Ķ�ʱ��*/
    switch(pPsMsg->ulPara)
    {
        /* CHAP Challenge�ش���ʱ�� */
        case PPPC_CHAP_CHALLENGE_RESEND_TIMER:

            PPP_CHAP_ChallengeTimeout(ulPppId);

            break;

        /* CHAP Response�ش���ʱ�� */
        case PPPC_CHAP_RESPONSE_RESEND_TIMER:

            PPP_CHAP_ResponseTimeout(ulPppId);


            break;

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        /* EAP���ͼ�Ȩ����ʱ��ʱ�� */
        case PPPC_EAP_SEND_AAA_AUTH_REQ_TIMER:

            PPP_EAP_WaitAuthRspTimeout(ulPppId);

            break;

        /* EAP����EAP REQ��ʱ�� */
        case PPPC_EAP_SEND_EAP_REQ_TIMER:

            PPP_EAP_WaitEAPRspTimeout(ulPppId);

            break;
#endif

        /* LCP����Echo Req��ʱ�� */
        case PPPC_LCP_SEND_ECHO_REQ_TIMER:

            pFsm    = pPsMsg->ulName;
            PPP_LCP_EchoTimeOut(pFsm);

            break;

        /* PAP�ȴ��Զ˷�����֤����ʱ�� */
        case PPPC_PAP_WAIT_FOR_REQ_TIMER:

            PPP_PAP_WaitReqTimeout(ulPppId);

            break;

        /* PAP���õȴ���֤��ʱ��ʱ�� */
        case PPPC_PAP_SEND_AUTH_REQ_TIMER:

            PPP_PAP_SendAuthReqTimeout(ulPppId);

            break;

        case PPPC_NEGO_TIMEOUT_TIMER:

            PPP_NegoListProc(VOS_NULL_PTR);

            break;

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        /* CCP��ʱ��ʱ�� */
        case PPPC_CCP_TIMEOUT_TIMER:

            PPP_CCP_Timeout(ulPppId);

            break;
#endif

        /* FSM�ش���ʱ�� */
        case PPPC_FSM_RETRANSMIT_TIMER:

            pFsm    = (VOS_VOID *)pPsMsg->ulName;
            PPP_FSM_TimeOut(pFsm);

            break;

        /* PA��TRLPResponse��ʱ�� */
        case PPPC_HRPD_PA_AGENT_RLP_RSP_TIMER:

            PPPC_HRPD_PaAgentRlpTimeout(pPsMsg->ulName);

            break;

        case PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER:

            PPPC_AwakeSelfReachMaxProcTimeoutProc();

            break;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
        /* HDLC�����װĿ�Ŀռ�ʧ�ܶ�ʱ�� */
        case PPPC_HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL:
            g_stHdlcConfigInfo.stHdlcFrmTimerHandle = VOS_NULL_PTR;
            PPPC_AwakeSelfProcUlDataTimeoutProc();
            break;
#endif

        default:
        {
            PPPC_WARNING_LOG1("unknow timer!\r\n", pPsMsg->ulPara);
        }
    }


    return;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara18_CallBack
 ��������  : �ص�����, ����ο���L2TP���������Ϣ��Я����IMSI��Ϣ��ʽ
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara534_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1146);
    g_ulSoftPara534 = ucNewValue;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara89_CallBack
 ��������  : �ص�����, ����ο���lcpЭ��ʱ�Ƿ���е�ַ����Э����ѹ����Э��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_SoftPara89_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1147);
    g_ulSoftPara577 = ucNewValue;
    g_ulACompressOnoff = g_ulSoftPara577 & 0x01;
    g_ulPCompressOnoff = (g_ulSoftPara577 & 0x02) >> 1;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara20_CallBack
 ��������  : �ص�����, ����ο�������ѹ��Э�̵�CPU����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara20_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1148);
    g_ulDmpuCpuThreshold = ucNewValue;
    g_ulDmpuCpuThreshold = ((g_ulDmpuCpuThreshold > 0) && (g_ulDmpuCpuThreshold <= 100))?g_ulDmpuCpuThreshold:80;
    return ;
}


/*****************************************************************************
 �� �� ��  : PPP_SoftPara21_CallBack
 ��������  : �ص�����, ����ο�������ѹ��Э�̵�VJ�û���
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara21_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1149);
    g_ulSoftPara537 = ucNewValue;
    g_ulMaxVJNum = ((50<=g_ulSoftPara537)&&(80>=g_ulSoftPara537))
                                ?(g_ulSoftPara537 * 100):6000;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara99_CallBack
 ��������  : �ص�����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara99_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1150);
    g_ulSoftPara585 = ucNewValue;
    if (g_ulSoftPara585 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1151);
        g_ulSoftPara585 = 0;
    }
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara100_CallBack
 ��������  : �ص�����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara100_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1152);
    g_ulSoftPara586 = ucNewValue;

    if (g_ulSoftPara586 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1153);
        g_ulSoftPara586 = 0;
    }

    return ;
}
/*****************************************************************************
 �� �� ��  : PPP_SoftPara569_CallBack
 ��������  : �ص�����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013-01-31
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara569_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1154);
    g_ucUdpCheckSumFlag = ucNewValue;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara101_CallBack
 ��������  : �ص�����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara101_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1155);
    g_ulSoftPara587 = ucNewValue;

    if (g_ulSoftPara587 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1156);
        g_ulSoftPara587 = 0;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara66_CallBack
 ��������  : �ص�����, �û����в�Я������Ϣʱ�Ƿ���Ҫƥ�䵽PDSN������,���ֵΪ0ʱ,��ƥ�乹����;����,ƥ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara66_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1157);
    g_ulSoftPara562 = ucNewValue;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara71_CallBack
 ��������  : �ص�����, Chap Response��Ϣ���Ƿ��������û�����,���ֵΪ0ʱ,��������;����,������
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2012-10-14
  ��    ��   : zhaichao
  �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara71_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1158);
    g_ulSoftPara567 = ucNewValue;
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftPara76_CallBack
 ��������  : �ص�����, IPCPЭ�̽׶�PDSN���͵�Request��Ϣ��Я����IP��ַ��2.2.2.2����RP�߼��ڵ�ַ
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-10-14
    ��    ��   : zhaichao
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SoftPara76_CallBack(ULONG ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1159);
    g_ulSoftPara571 = ucNewValue;
    return ;
}

ULONG SPM_GetByteValue(ULONG ulSoftparaNum, UCHAR* ucByteValue)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_SoftParaInit
 ��������  : ��ʼ��PPPģ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_SoftParaInit()
{
    ULONG ulRet = VOS_OK;
    UCHAR ucSoftParaValue = 0;

    /*byte 18*/
    ulRet = SPM_GetByteValue(M_SPM_L2TP_IMSI_FORMAT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara534 = ucSoftParaValue;
    }

    /*byte 66*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_MATCH_CONSTRUCTDOMAIN, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara562 = ucSoftParaValue;
    }

    /*byte 71*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_CHAPRESPONSE_USERNAME, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara567 = ucSoftParaValue;
    }

    /*byte 76*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_IPCP_IPADDR, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara571 = ucSoftParaValue;
    }

    /*byte 89*/
    ulRet = SPM_GetByteValue(M_SPM_PPPCOMPRESS_FLAG, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara577 = 0x3;//ucSoftParaValue; /*changed by chenmin00265046*/
    }

    /*byte 20*/
    ulRet = SPM_GetByteValue(M_SPM_PPPCOMPRESS_LIMIT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulDmpuCpuThreshold = ucSoftParaValue;
    }

    /*byte 21*/
    ulRet = SPM_GetByteValue(M_SPM_PPPVJ_LIMIT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara537 = ucSoftParaValue;
    }

    /*byte 99*/
    ulRet = SPM_GetByteValue(M_SPM_LCP_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara585 = ucSoftParaValue;
    }

    /*byte 100*/
    ulRet = SPM_GetByteValue(M_SPM_AUTH_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara586 = ucSoftParaValue;
    }

        /*byte 101*/
    ulRet = SPM_GetByteValue(M_SPM_IPCP_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara587 = ucSoftParaValue;
    }

    /*byte 569*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_UDP_CHECKSUM, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ucUdpCheckSumFlag = ucSoftParaValue;
    }

    g_ulDmpuCpuThreshold = ((g_ulDmpuCpuThreshold > 0) && (g_ulDmpuCpuThreshold <= 100))?g_ulDmpuCpuThreshold:80;
    g_ulMaxVJNum = ((50<=g_ulSoftPara537)&&(80>=g_ulSoftPara537))
                                ?(g_ulSoftPara537 * 100):6000;

    if (g_ulSoftPara585 > 10)
    {
        g_ulSoftPara585 = 0;
    }

    if (g_ulSoftPara586 > 10)
    {
        g_ulSoftPara586 = 0;
    }

    if (g_ulSoftPara587 > 10)
    {
        g_ulSoftPara587 = 0;
    }

    g_ulACompressOnoff = g_ulSoftPara577 & 0x01;
    g_ulPCompressOnoff = (g_ulSoftPara577 & 0x02) >> 1;


    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������PPP���ƿ�,�����ӵ�PPP���ƿ�������                      *
* MODIFY DATE  ��modified by gxf for GGSN80 20030212                        *
* �������     : ULONG ulRpIndex                                            *
*                USHORT usDomainIndex                                       *
*                USHORT usVpnId                                             *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP��װ����                                                *
****************************************************************************/
ULONG PPP_CreateCB(ULONG ulRPIndex, PPP_LUPPARA_S *pstUpPara)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    USHORT usIpv6addr[IPV6_ADDR_LEN] = {0XFE80,0,0,0,0,0,0,0};

    PPP_TRACE("\r\n---Into PPP_CreateCB: ulRPIndex %u---\r\n", ulRPIndex);
    if (!((ulRPIndex <= PPP_MAX_USER_NUM)) || !pstUpPara)
    {
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CreateCB: Parameter error!");
        return VOS_ERR;
    }

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_039);

    PPP_DBG_OK_CNT(PPP_PHOK_1160);

    if (PPP_CB_STATE_USED == g_astPppPool[ulRPIndex].usState)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n The user %u is already exist!", ulRPIndex);
        g_astPppPool[ulRPIndex].ulRPIndex = ulRPIndex;
        PPP_DBG_ERR_CNT(PPP_PHERR_490);
        (VOID)PPP_ClearCB(&g_astPppPool[ulRPIndex]);
    }

    pstPppInfo = &g_astPppPool[ulRPIndex];
    PPP_MemSet((VOID *)pstPppInfo, 0, sizeof(PPPINFO_S));

    if (VOS_OK != PPP_InitCB(pstPppInfo))
    {
        (VOID)PPP_ClearCB(pstPppInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_491);
        /* ����ʧ�� */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CreateCB: PPP_InitCB failed!");

        return VOS_ERR;
    }
    pstPppInfo->bEhrpdUser = pstUpPara->beHRPDMode;
    pstPppInfo->usTokenId = pstUpPara->usTokenId;
    //pstPppInfo->bBit328SoftPara = SOFTPARA_BIT1406;
    pstPppInfo->ulRPIndex = ulRPIndex;
    pstPppInfo->usState = PPP_CB_STATE_USED;
    pstPppInfo->stIMSI = pstUpPara->stIMSI;
    pstPppInfo->ucServiceOpt = pstUpPara->ucServiceOpt;
    pstPppInfo->usPcfIndex = pstUpPara->usPcfIndex;
    pstPppInfo->ulPcfIP = pstUpPara->ulPcfIP;
    pstPppInfo->ulNegoStartTime = VOS_GetTick();
    pstPppInfo->usPeerId = VOS_NULL_WORD;
    pstPppInfo->ucAAAType = VOS_NULL_BYTE;
    pstPppInfo->ulNowUTCInSec = VOS_GetTick();
    pstPppInfo->bIPCPNakHandFlag = VOS_TRUE;

    /* ��ʼ̬��Ϊ��Ч,��Ϊ��Э��ʱ����ip���� */
    pstPppInfo->bIPTech = PPP_USERTYPE_NULL;

    /* �Ȱ��ӿ���DPEID����Ϊ��Ч */
    pstPppInfo->ucDmpuId = 0xFF;
    pstPppInfo->ucDpeId  = 0xFF;

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);

    if (0 == (g_ulSoftPara571 & 0x01))
    {
        pstPppInfo->ulIPAddr = g_ulA11RpifIp;
    }
    else
    {
        pstPppInfo->ulIPAddr = 0x2020202;  /* IPCPЭ���б��ص�ַ���ù̶���ַ2.2.2.2 */
    }

    pstPppInfo->usCDBIndex = VOS_NULL_WORD;
    pstPppInfo->usVirtualDomainIdx = VOS_NULL_WORD;

    /* IPV6CPЭ���б��ص�ַ���ù̶���ַFE80::rp��v4��ַ*/
    VOS_MemCpy((void *)(&usIpv6addr[6]), (void *)&(g_ulA11RpifIp),sizeof(ULONG));
    VOS_MemCpy(pstPppInfo->usIpv6Addr, usIpv6addr, IPV6_ADDR_LEN*2);

    /* ��ʼ��������Ϣ */
    if (VOS_OK != PPP_InitConfigInfo(pstPppInfo) )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_492);
        (VOID)PPP_ClearCB(pstPppInfo);
        pstPppInfo->usState = PPP_CB_STATE_FREE;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CreateCB: PPP_InitConfigInfo failed!");

        return VOS_ERR;
    }

    (VOID)PPP_NodeAdd(ulRPIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_DeleteCB
 ��������  : ɾ��PPP���ƿ�,����PPP���ƿ�������ɾ����
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_DeleteCB(PPPINFO_S *pstPppInfo)
{
    VOS_UINT8                           ucPppId;


    if ((VOS_NULL_PTR == pstPppInfo) || (PPP_CB_STATE_FREE == pstPppInfo->usState))
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_040);
    PPP_DBG_OK_CNT(PPP_PHOK_1161);

    PPP_TRACE("\r\n---Into PPP_DeleteCB: ulRPIndex %u---\r\n", pstPppInfo->ulRPIndex);

    /* ɾ��PPP���ƿ�ʱ��Ҫ�����Ϣ���� */
    PPPC_ClearUlDataQ();
    PPPC_ClearDlDataQ();

    /* ���ppp id��Pdn id֮���ӳ���ϵ */
    PPPC_ClearMappingByPppId(pstPppInfo->ulRPIndex);

#if 0
    if (E_CRM_ACTIVE  == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1162);

        if ( pstPppInfo->bVjFlag )
        {
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_071);
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_VJ);
        }

        /* IPV6��ջ�û�����Ҫ���л���pcf������ͳ�Ʋμ�CR20120413016 */
        if (PDSN_PPP_IPTYE_IPV6 != pstPppInfo->ucIpCapability )
        {
            SNMP_TerminatePhaseProc(pstPppInfo);
        }

        if ((PPPA11DOWN != pstPppInfo->bFailFlag)
            && (PPPA11DOWNNOLCPTER != pstPppInfo->bFailFlag))
        {

            /*��USM֪ͨ��ȥ��������Դ��֪ͨUSMȥ��*/
            PPP_DBG_OK_CNT(PPP_PHOK_1163);
            (VOID)USM_NotifyReleaseUserMsg(pstPppInfo->ulRPIndex, pstPppInfo->ucPppRleaseCode);
        }
        else if (PPPA11DOWN == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1164);
            /* USM֪ͨ��ȥ�����Դ��Ҫ����Ӧ */
            (VOID)USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                      E_USM_MSGTYPE_PPP2USM_RELEASE,
                                      VOS_NULL_PTR);

        }

        pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;
        pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;

        /* �����ehrpd�û�, ��Ҫ֪ͨdiam auth����STR��Ϣ, ���ǲ���Ҫ�ȴ���Ӧ */
        if ((VOS_TRUE == pstPppInfo->bEhrpdUser)
           && (VOS_NULL_WORD != pstPppInfo->usPeerId))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1165);
            PPP_EAP_NotifyDiamAuthRelease(pstPppInfo);
        }

        /* ��ʱ����,��¼�ı������ */

    }
#endif
    ucPppId = (VOS_UINT8)pstPppInfo->ulRPIndex;

    /* ������ƿ��ڲ����� */
    (VOID)PPP_ClearCB(pstPppInfo);

    /* added by gxf 20030215 */
    g_astPppPool[pstPppInfo->ulRPIndex].usState = PPP_CB_STATE_FREE;

    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);/* Added by heyajun kf1199 at 2003-09-23 V800R001B02D002 for BYHD00224 */

    PPPC_JudgeCmdRseultWhenDeleteCB(ucPppId);

    PPP_MemSet(&g_astPppPool[pstPppInfo->ulRPIndex], 0, sizeof(PPPINFO_S));



    /* ��ʼ��PA AGENT������ */
    PPPC_HRPD_PaAgentInit();

    /* ������������ڴ� */
    PPPC_ClearUlEncapMem();

    /* �����Ƭ����״̬ */
    FWD_PppRebuildIncompleteSliceStatInit();

    return VOS_OK;
}
VOID PPP_ClearCB_LCP(PPPLCPINFO_S *pstPppLcpInfo)
{
    PPPLCPINFO_S * pstLcpInfo = (PPPLCPINFO_S *)pstPppLcpInfo;
    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstLcpInfo->stFsm.ulTimeOutID)
    {
        /*modified by huzhiyong ȥ�����ԣ�������ɾ���ش���ʱ������������2002/03/08*/

        /*
            VOS_DBGASSERT(0);
         */
        (VOID)VOS_StopRelTimer(&(pstLcpInfo->stFsm.ulTimeOutID));
        pstLcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstLcpInfo->stFsm.ulEchoTimeoutID != 0)
    {
        VOS_DBGASSERT(0);
        (VOID)VOS_StopRelTimer(&(pstLcpInfo->stFsm.ulEchoTimeoutID));
        pstLcpInfo->stFsm.ulEchoTimeoutID = 0;
    }
    pstLcpInfo->ucUsedFlag = 0;
    return;
}


VOID PPP_ClearCB_PAP(PPPPAPINFO_S *pstPppPapInfo)
{
    PPPPAPINFO_S * pstPapInfo = pstPppPapInfo;
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_ClearCB_PAP: Delete PAPINFO!");

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstPapInfo->ulServerTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    if (pstPapInfo->ulClientTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    /* added by gxf 20030317 */
    if (VOS_NULL_PTR != pstPapInfo->pstAAAAuthReqMsg)
    {
        (VOID)PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
        pstPapInfo->pstAAAAuthReqMsg = VOS_NULL_PTR;
    }
    pstPapInfo->ucUsed = 0;
    return;
}


VOID PPP_ClearCB_CHAP(PPPCHAPINFO_S *pstPppChapInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppChapInfo;
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_ClearCB_CHAP: Delete CHAPINFO!");

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstChapInfo->ulRespTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    /* added by gxf 20030317 */
    if (VOS_NULL_PTR != pstChapInfo->pstAAAAuthReqMsg)
    {
        (VOID)PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
        pstChapInfo->pstAAAAuthReqMsg = VOS_NULL_PTR;
    }
    pstChapInfo->ucUsed = 0;
    return;
}

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
/****************************************************************************
* CREATE DATE  ��2010-07-17                                                 *
* CREATED BY   ��WANGYONG                                                   *
* FUNCTION     ��PPP_ClearCB_EAP���PPP���ƿ�EAP����                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��PPPEAPINFO_S *pstPppEapInfo                                *
* OUTPUT       ����                                                         *
* RETURN       ����                                                         *
* CALLED BY    ��PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_EAP(PPPEAPINFO_S *pstPppEapInfo)
{
    PPPEAPINFO_S *pstEapInfo = pstPppEapInfo;
    PPP_DebugOut((ULONG)FSU_TID_PPPC, 2, "\r\n PPP_ClearCB_EAP: Delete EAPINFO!");

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstEapInfo->ulRspTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulRspTimeoutID);
        pstEapInfo->ulRspTimeoutID = 0;
    }

    if (pstEapInfo->ulWaitAuthRspTimeID)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulWaitAuthRspTimeID);
        pstEapInfo->ulWaitAuthRspTimeID = 0;
    }

    /* �ͷ�EAP */
    if (VOS_NULL_PTR != pstEapInfo->pucEAP)
    {
        PPP_Free(pstEapInfo->pucEAP);
        pstEapInfo->pucEAP = VOS_NULL_PTR;
    }

    pstEapInfo->ucUsed = 0;
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : PPP_ClearCB_IPCP
 ��������  : PPP_ClearCB_IPCP���PPP���ƿ�IPCP����
 �������  : PPPIPCPINFO_S *pstIpcpInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_ClearCB_IPCP(PPPIPCPINFO_S *pstIpcpInfo)
{
    if (VOS_NULL_PTR == pstIpcpInfo)
    {
        return ;
    }

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstIpcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
        pstIpcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstIpcpInfo->pstPppInfo && pstIpcpInfo->pstPppInfo->bVjFlag)
    {
        PPP_CompUserNumDel(pstIpcpInfo->pstPppInfo, PPP_USERSTAT_VJ);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_067);
    }

    /* ���ӻ�����Ϣ�����ͷ� */
    if ( pstIpcpInfo->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
        pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
        pstIpcpInfo->ulIpv4cpLen = 0;
    }

    pstIpcpInfo->ucUsedFlag = 0;
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_ClearCB_IPV6CP
 ��������  : ���PPP���ƿ�IPV6CP����
 �������  : PPPIPV6CPINFO_S *pstPppIpv6cpInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_ClearCB_IPV6CP(PPPIPV6CPINFO_S *pstPppIpv6cpInfo)
{
    PPPIPV6CPINFO_S * pstIpv6cpInfo = pstPppIpv6cpInfo;

    if (VOS_NULL_PTR == pstPppIpv6cpInfo)
    {
        return ;
    }

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstIpv6cpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
        pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
    }

    /* ���ӻ�����Ϣ�����ͷ� */
    if ( pstIpv6cpInfo->pucIpv6cpMsg )
    {
        (VOID)PPP_Free(pstIpv6cpInfo->pucIpv6cpMsg);
        pstIpv6cpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
        pstIpv6cpInfo->ulIpv6cpLen = 0;
    }

    if (0 != pstIpv6cpInfo->ucUsedFlag)
    {
        pstIpv6cpInfo->ucUsedFlag = 0;
        PPP_DBG_OK_CNT(PPP_PHOK_1166);
    }

    return;
}

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

VOID PPP_ClearCB_CCP(PPP_CCP_INFO_S *pstCcpInfo)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_ClearCB_CCP: Delete CCPINFO!");

    if (VOS_NULL_PTR == pstCcpInfo)
    {
        return;
    }

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstCcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstCcpInfo->stFsm.ulTimeOutID));
        pstCcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstCcpInfo->ulCcpTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstCcpInfo->ulCcpTimeoutID));
        pstCcpInfo->ulCcpTimeoutID = 0;
    }

    pstCcpInfo->ucPppCompType = 0;
    pstCcpInfo->ucUsed = 0;

    /* ���ѹ���û���ͳ�� */
    pstPppInfo = pstCcpInfo->pstPppInfo;
    if (pstPppInfo)
    {
        if (pstPppInfo->bMppcFlag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_MPPC);
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_068);
        }
        if (pstPppInfo->bLzs0Flag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS0);
        }
        if (pstPppInfo->bLzs1Flag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS1);
        }
    }

    return;
}


VOID PPP_ClearCB_STAC(STAC_COMPRESSINFO_S *pstPppStacCompressInfo, STAC_DECOMPRESSINFO_S* pstPppStacDecompressInfo)
{
    if (pstPppStacCompressInfo)
    {
        (VOID)PPP_Free(pstPppStacCompressInfo);
    }

    if (pstPppStacDecompressInfo)
    {
        STAC_DECOMPRESSINFO_S* pstStacDecompressInfo = pstPppStacDecompressInfo;

        /*��Ӷ��ڶ�ʱ���ı���*/
        if (pstStacDecompressInfo->ulTimeoutID)
        {
            (VOID)VOS_StopRelTimer(&(pstStacDecompressInfo->ulTimeoutID));
            pstStacDecompressInfo->ulTimeoutID = 0;
        }
        (VOID)PPP_Free(pstPppStacDecompressInfo);
    }

    return;
}
#endif

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����PPP���ƿ��ڲ�����                                      *
* MODIFY DATE  ��modified by gxf 20030317                                   *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_DeleteCB��PPP_CreateCB                                 *
****************************************************************************/
ULONG PPP_ClearCB_TestStub(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    /* ���������Ϣ */
    PPP_ClearConfigInfo(pstPppInfo);

    /*
      ��ɾ��PPP���ƿ���ǰһ����һ��LOW DOWN�¼����������е�NCP���ƿ�Ӧ��ΪNULL
      ���������ִ�е����Ե�ʱ�򣬻����ǵͲ������IPC����������
      ��PPP������Ա���������Ӱ��PPP����,�ö��Խ�����ʾ������
      shiyong 2001/04/27
     */

    /* �����Э����ƿ� */
    PPP_ClearLCPCB(pstPppInfo->pstLcpInfo);


    PPP_ClearPAPCB(pstPppInfo->pstPapInfo);

    PPP_ClearCHAPCB(pstPppInfo->pstChapInfo);

    PPP_ClearIPCPCB(pstPppInfo->pstIpcpInfo);

    PPP_ClearIPV6CPCB(pstPppInfo->pstIpV6cpInfo);

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
#endif

    /* L2TP��Ҫ�Ĳ��� */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (pstPppInfo->pstPppRenegoInfo)
    {
        (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
        pstPppInfo->pstPppRenegoInfo = VOS_NULL_PTR;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_ClearALL(pstPppInfo);
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_ClearEAPCB(pstPppInfo->pstEapInfo);
#endif

    /* added by gxf 20030215 */
    pstPppInfo->usState = PPP_CB_STATE_FREE;

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����PPP���ƿ��ڲ�����                                      *
* MODIFY DATE  ��modified by gxf 20030317                                   *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_DeleteCB��PPP_CreateCB                                 *
****************************************************************************/
ULONG PPP_ClearCB(PPPINFO_S *pstPppInfo)
{
    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
        return PPP_ClearCB_TestStub(pstPppInfo);
    }

    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    /* ɾ���ϵ�hash */
    if ((pstPppInfo->usPeerId != VOS_NULL_WORD)
        && (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1167);
        if (VOS_OK != Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_493);
        }
        pstPppInfo->usPeerId = VOS_NULL_WORD;
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;
    }
    /* ���������Ϣ */
    PPP_ClearConfigInfo(pstPppInfo);

    /*
      ��ɾ��PPP���ƿ���ǰһ����һ��LOW DOWN�¼����������е�NCP���ƿ�Ӧ��ΪNULL
      ���������ִ�е����Ե�ʱ�򣬻����ǵͲ������IPC����������
      ��PPP������Ա���������Ӱ��PPP����,�ö��Խ�����ʾ������
      shiyong 2001/04/27
     */

    /* �����Э����ƿ� */
    PPP_ClearLCPCB(pstPppInfo->pstLcpInfo);


    PPP_ClearPAPCB(pstPppInfo->pstPapInfo);

    PPP_ClearCHAPCB(pstPppInfo->pstChapInfo);

    PPP_ClearIPCPCB(pstPppInfo->pstIpcpInfo);

    PPP_ClearIPV6CPCB(pstPppInfo->pstIpV6cpInfo);

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
#endif

    /* L2TP��Ҫ�Ĳ��� */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (pstPppInfo->pstPppRenegoInfo)
    {
        (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
        pstPppInfo->pstPppRenegoInfo = VOS_NULL_PTR;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_ClearALL(pstPppInfo);
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_ClearEAPCB(pstPppInfo->pstEapInfo);
#endif

    /* added by gxf 20030215 */
    pstPppInfo->usState = PPP_CB_STATE_FREE;

    return VOS_OK;
}
VOID PPP_DelAllResource(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /* ���� RPIndex ��ȡ PPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        return;
    }

    /* �����ehrpd�û�, ��Ҫ֪ͨdiam auth����STR��Ϣ, ���ǲ���Ҫ�ȴ���Ӧ */
    if ((VOS_TRUE == pstPppInfo->bEhrpdUser)
       && (VOS_NULL_WORD != pstPppInfo->usPeerId))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1168);
#if 0
        PPP_EAP_NotifyDiamAuthRelease(pstPppInfo);
#endif
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1169);

    (VOID)PPP_ClearCB(pstPppInfo);

    PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ʼ��PPP���ƿ�                                            *
* MODIFY DATE  ��modified by gxf for GGSN80 20030212                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_CreateCB                                               *
****************************************************************************/
ULONG PPP_InitCB(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    /* ��ʼ���ӿڵ�debug����״̬Ϊ��ǰȫ�ֿ���״̬ */
    pstPppInfo->stPppDebugInfo = g_stPppDebugInfo;

    PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);

    /* ��ʼ��LCP���ƿ�
       ��������ڴ�ʧ����PPP_Core_ReceiveEventFromShell�л��ٴ����� */
    if (pstPppInfo->pstLcpInfo)
    {
        PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
        PPP_LCP_Init(pstPppInfo);
    }

    /*��ʼ����Э����ƿ�*/
    pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;       /* IPCP ���ƿ�ָ�� */
    pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;     /* IPV6CP ���ƿ�ָ�� */
    pstPppInfo->pstCcpInfo = VOS_NULL_PTR;        /* CCP  ���ƿ�ָ�� */
    pstPppInfo->pL2tpPara = VOS_NULL_PTR;         /* L2TP ���� */

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    PPP_GETHDLCADDR(pstPppInfo->pstHdlcInfo, pstPppInfo->ulRPIndex);

    /* ��ʼ��HDLC���ƿ� */
    if (pstPppInfo->pstHdlcInfo)
    {
        PPP_MemSet((void *)pstPppInfo->pstHdlcInfo, 0, sizeof(struct hdlc));
    }

#endif
    /* ��ʼ��������Ϣ */
    /*pstPppInfo->ulResetTimerId = 0 ;*/
    pstPppInfo->usPhase = (UCHAR)PPP_PHASE_DEAD;

    pstPppInfo->bAuthServer = VRP_NO;
    pstPppInfo->bAuthClient = VRP_NO;

 #ifdef __PRODUCT_TYPE_PDSN80
    /* added by gxf 20030507  PDSN is async mode */
    pstPppInfo->bIsAsync = 1;
    pstPppInfo->bSynAsyConvert = 1;

    /* ȱʡͬ/�첽ת���ַ���
       lcp openedǰ����0xffffffff��lcp opened�����ulLocalAccm | ulRemoteAccm����ת��
     */
 #else
    pstPppInfo->bIsAsync = 1;
    pstPppInfo->bSynAsyConvert = 1;
 #endif
    pstPppInfo->ulRemoteAccm = VOS_HTONL(0xffffffff);
    pstPppInfo->ulLocalAccm = VOS_HTONL(PPP_DEFAULT_ACCM);

    return VOS_OK;
}


VOID PPP_CompInitInfo(PPPCONFIGINFO_S *pstConfigInfo)
{
 #ifdef    __PRODUCT_TYPE_PDSN80
    /* Modified start by liutao 38563 at 2004-10-29 V800R002 for PPPC��ֲ */
    if (g_ucPppCcpType & M_PPPCOMPRESS_MPPC_FLAG)
    {
        pstConfigInfo->bMppcCompress = 1;
    }
    else
    {
        pstConfigInfo->bMppcCompress = 0;
    }

    if (g_ucPppCcpType & M_PPPCOMPRESS_STAC_FLAG)
    {
        pstConfigInfo->bStacCompress = 1;
    }
    else
    {
        pstConfigInfo->bStacCompress = 0;
    }

    /* Modified end by liutao 38563 at 2004-10-29 V800R002 for PPPC��ֲ */
 #endif
}


USHORT PPP_GetUserMru(ULONG ulEhrpdFlg)
{
    /* (CR-0000050651---MRU���ȱ仯)
       ������õ�mru������1501ʱ��PDSN��HSGW��ʹ�����õ�mru����Э�̣������
       �õ�mruΪ1501ʱ��PDSN����1500Э�̣�HSGW����1501Э�� */

    if ( (PPP_MRU_MAX_HSGW == g_stPppCfgInfo.usMru)
         && VOS_TRUE != ulEhrpdFlg )
    {
        return PPP_MRU_MAX_PDSN;
    }

    return g_stPppCfgInfo.usMru;
}
/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ʼ��PPP������Ϣ                                          *
* MODIFY DATE  ��modified by gxf for GGSN80 20030212                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_InitCB                                                 *
****************************************************************************/
ULONG PPP_InitConfigInfo(PPPINFO_S *pstPppInfo)
{
    PPPCONFIGINFO_S *pstConfigInfo = VOS_NULL_PTR;
    DOMAINDNS_S stApnDns = { 0 };  /* DNS���� */

    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    PPP_GETCONFIGADDR(pstConfigInfo,pstPppInfo->ulRPIndex);
    if (!pstConfigInfo)
    {
        /* ʧ�� */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Config Info: Malloc Err!!");
        return VOS_ERR;
    }

    PPP_MemSet((VOID *)pstConfigInfo, 0, sizeof(PPPCONFIGINFO_S));
    pstConfigInfo->bUsedFlag = 1;

    if (pstPppInfo->bEhrpdUser)
    {
        pstConfigInfo->bAuthMethod = 1;
        pstConfigInfo->bAuthRmtPap = 0;
        pstConfigInfo->bAuthRmtChap = 0;
        pstConfigInfo->bAuthRmtEap = 1;
    }
    else
    {
        pstConfigInfo->bAuthMethod = g_stPppCfgInfo.ucAuthmod;
        pstConfigInfo->bAuthRmtEap= 0;

        /* �������Ϊ���û���Ȩ��������û�����PAP��CHAP��֤ */
        if (0 != pstConfigInfo->bAuthMethod)
        {
            /* ��֤��ʽ���ȼ� 0:both pap and chap 1:only pap 2:only chap */
            if (g_stPppCfgInfo.ucAuthoption != 2)
            {
                pstConfigInfo->bAuthRmtPap = 1;
            }

            if (g_stPppCfgInfo.ucAuthoption != 1)
            {
                pstConfigInfo->bAuthRmtChap = 1;
            }
        }

    }

    pstConfigInfo->usMru = PPP_GetUserMru(pstPppInfo->bEhrpdUser);

    VOS_StrCpy((CHAR*)pstConfigInfo->cChapHostName, (CHAR*)g_stPppCfgInfo.aucHostname);
    if ((g_stPppCfgInfo.ucTimeout > 0) && (g_stPppCfgInfo.ucTimeout <= (PPP_MAXTIMEOUTTIME / 1000)))
    {
        pstConfigInfo->ulNegTimeOut = g_stPppCfgInfo.ucTimeout * 1000;
    }
    else
    {
        pstConfigInfo->ulNegTimeOut = PPP_DEFTIMEOUTTIME;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP NegoTimeouttime configure error!");
    }

    /* ��CDB�л�ȡDNS */
    if (VOS_OK == (RDA_GetApnDNSCfg(pstPppInfo->usCDBIndex, &stApnDns)))
    {
        pstPppInfo->ulDNSAddr1 = stApnDns.ulMainDNSServer;
        pstPppInfo->ulDNSAddr2 = stApnDns.ulBackupDNSServer;
    }
    /* Modified by hyj for B02 */
    else if (VOS_OK == (RDA_GetApnDNSCfg(AAA_DEFAULT_DOMAIN_INDEX, &stApnDns)))
    {
        pstPppInfo->ulDNSAddr1 = stApnDns.ulMainDNSServer;
        pstPppInfo->ulDNSAddr2 = stApnDns.ulBackupDNSServer;
    }
    else
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_InitConfigInfo: Get DNS configure information failed!");
    }

    /* �����û���Ȩ */
    if (!pstConfigInfo->bAuthMethod)
    {
        /* ȱʡ��������Ϣ */
        pstPppInfo->usCDBIndex = 0;
        pstPppInfo->usVirtualDomainIdx = 0;
        VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR*)g_pstApnByIndex[0].aucAPN);
    }

    if (g_stPppCfgInfo.ucVSNCPFlag & PPP_VSNCP_APN_AMBR_FLAG)
    {
        pstConfigInfo->bVsncpAPNAmbrFlag = VOS_TRUE;

    }
    if (g_stPppCfgInfo.ucVSNCPFlag & PPP_VSNCP_DEFUALT_APN_INDICATIOR_FLAG)
    {
        pstConfigInfo->bVsncpDefApnIndFlag = VOS_TRUE;

    }

    /* ѹ������ֵ��ʼ�� */
    PPP_CompInitInfo(pstConfigInfo);

    pstPppInfo->pstUsedConfigInfo = pstConfigInfo;
    pstPppInfo->pstConfigInfo = pstConfigInfo;



    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �����PPP������Ϣ                                            *
* MODIFY DATE  ��modified by gxf for GGSN80 20030212                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��                                                           *
* CALLED BY    ��PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearConfigInfo(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    if (pstPppInfo->pstUsedConfigInfo)
    {
        ((PPPCONFIGINFO_S *)pstPppInfo->pstUsedConfigInfo)->bUsedFlag = 0;
        pstPppInfo->pstUsedConfigInfo = VOS_NULL_PTR;
    }

    pstPppInfo->pstConfigInfo = VOS_NULL_PTR;
    pstPppInfo->pstUsedConfigInfo = VOS_NULL_PTR;

    return;
}


/*****************************************************************************
 �� �� ��  : PPP_UP
 ��������  : PPPģ���ṩ��A11�Ľӿں�������A10��·���ú�ֱ��֪ͨPPP�����������л�
 �������  : ULONG ulRPIndex
             PPP_LUPPARA_S*pstUpPara
 �������  : ��
 �� �� ֵ  : ULONG VOS_OK/VOS_ERR
 ���ú���  : PPP_A11_IoCtl
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��9��24��
    ��    ��   : ZhangJun HT04406
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_UP(ULONG ulRPIndex, PPP_LUPPARA_S*pstUpPara)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /* ������� */
    if (VOS_NULL_PTR == pstUpPara)
    {
        return VOS_ERR;
    }

    /* ����ulRPIndex����PPP_CreateCB�м��,�ʴ˴������ */

    /* ����PPP���ƿ� */
    if (VOS_OK != PPP_CreateCB(ulRPIndex, pstUpPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_494);
        /* ����ppp���ƿ�ʧ�� */
        return VOS_ERR;
    }

    /* ���� RPIndex ��ȡ PPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    /* �˴������� PPP���ƿ� �Ƿ���Ч */

    /* ��������м�Ȩ������ǰ����DHCP���� */

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_495);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_UP: GETPPPINFOPTRBYRP failed!");
        return VOS_ERR;
    }

    PPP_Core_ReceiveEventFromShell(pstPppInfo, (ULONG)PPPISLUP, VOS_NULL_PTR);

    /* ����ɹ� */
    return VOS_OK;
}

/* Added End by ZhangJun HT04406 at 2005/09/24 for PDSN�����Ż� */


ULONG PPP_A11_IsLupProc(ULONG ulRPIndex, CHAR *pPara)
{
    if (!pPara)
    {
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_A11_IsLupProc: UPPara is VOS_NULL_PTR!");
        return VOS_ERR;
    }

    if (VOS_OK != PPP_UP(ulRPIndex, (PPP_LUPPARA_S*)pPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_496);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_A11_IsLupProc: Call PPP_UP() Failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}
ULONG PPP_UsmIsLdownProc(ULONG ulRPIndex, UCHAR* pucPara)
{
    PPP_A11MSG_S stMsg = {0};
    ULONG ulRet = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    SDB_RETURNCODE_E enSdbReturn = SDB_SUCCESS;
    PppLDownPara *pstDownPara = (PppLDownPara *)pucPara;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_UsmIsLdownProc: Lower notify user %u down", ulRPIndex);

    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_497);
        return VOS_ERR;
    }

    enSdbReturn = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulRPIndex,
                                                            (UCHAR **)&pstRpContext);
    if ((SDB_SUCCESS != enSdbReturn) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_498);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_UsmIsLdownProc: Failed to Query SDB!");

        return VOS_ERR;
    }

    stMsg.ulRPIndex = ulRPIndex;
    stMsg.ulMsgCode = PPP_MSG_CODE_LINK_DOWN;

    if (pstDownPara != VOS_NULL_PTR)
    {
        stMsg.ulLcpSendFlag = pstDownPara->ulLcpSendFlag;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                "\r\n PPP_UsmIsLdownProc: LCP flag = %u",
                                pstDownPara->ulLcpSendFlag);
    }

    if (VOS_FALSE == stMsg.ulLcpSendFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1170);
        (VOID)PPP_USMNotifyRelease(&stMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_USMNotifyRelease: notify ppp %u down; no need send LCP", ulRPIndex);
        return VOS_OK;
    }

    ulRet = PPP_SendRtMsg(g_ullPppA11Csi,
                         PPP_SELF_CSI,
                         PPP_MSG_TYPE_USM,
                         PPP_MSG_CODE_LINK_DOWN,
                         (UCHAR *)&stMsg,
                         sizeof( PPP_A11MSG_S ));
    if ( VOS_OK != ulRet )
    {

        PPP_DBG_ERR_CNT(PPP_PHERR_499);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER011);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_UsmIsLdownProc: PPP_SendRtMsg failed!");
        return VOS_ERR;

    }
    PPP_DBG_OK_CNT(PPP_PHOK_1171);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : Ppp_UsmIoCtl
 ��������  : USM֪ͨPPP�ײ�UP�͵ײ�DOWN
 �������  : ULONG ulRPIndex
             ULONG ulCmd
             CHAR *pPara
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG Ppp_UsmIoCtl(ULONG ulRPIndex, ULONG ulCmd, CHAR *pPara)
{
    ULONG ulRet = VOS_OK;

    if (!((ulRPIndex <= PPP_MAX_USER_NUM)) || (ulCmd >= ISLTUEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_500);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\nPpp_UsmIoCtl Input para error ulRPIndex %d!", ulRPIndex);
        return VOS_ERR;
    }

    switch ( ulCmd )
    {
        case PPP_ISLUP :
        {
            /*����USM֪ͨ�ĵײ���·����OK��Ϣ����ʼLCPЭ��*/;
            PPP_DBG_OK_CNT(PPP_PHOK_1172);
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_000);
            ulRet = PPP_A11_IsLupProc(ulRPIndex, pPara);
            break;
        }
        case PPP_ISLDOWN :
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1173);
            /*����USM֪ͨ��ȥ����Ϣ*/;
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_012);
            ulRet = PPP_UsmIsLdownProc(ulRPIndex, (UCHAR *)pPara);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_501);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,"\r\nPpp_UsmIoCtl enter default branch %d!", ulCmd);
            ulRet = VOS_ERR;
            break;
        }
    }

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\nPpp_UsmIoCtl success !");
    return ulRet;
}




ULONG PPP_ModDomainInfoForCMIP(ULONG ulRpIndex, USHORT usDomainIdx)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    ULONG ulvjModFlag = VOS_FALSE;
    ULONG ulMppcModFlag = VOS_FALSE;
    ULONG ulLzs0Flag = VOS_FALSE;
    ULONG ulLzs1Flag = VOS_FALSE;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        /* ����ͳ��:��ЧЭ�̱�����*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_ModDomainInfoForCMIP: User[%u] pppinfo isn't exist! domainindex[%u]",
                      ulRpIndex, usDomainIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_502);
        return VOS_ERR;
    }

    if (pstPppInfo->usCDBIndex != usDomainIdx)
    {
        if (VOS_TRUE == pstPppInfo->bVjFlag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_VJ);
            ulvjModFlag = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bMppcFlag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_MPPC);
            ulMppcModFlag  = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bLzs0Flag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_ZLS0);
            ulLzs0Flag = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bLzs1Flag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_ZLS1);
            ulLzs1Flag = VOS_TRUE;
        }
    }

    pstPppInfo->usCDBIndex = usDomainIdx;
    pstPppInfo->usVirtualDomainIdx = usDomainIdx;

    if (VOS_TRUE == ulvjModFlag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_VJ);
    }

    if (VOS_TRUE == ulMppcModFlag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_MPPC);
    }

    if (VOS_TRUE == ulLzs0Flag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_ZLS0);
    }

    if (VOS_TRUE == ulLzs1Flag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_ZLS1);
    }

    /* �޸Ŀ��ƿ��е����ݣ�֪ͨ���� */

    return VOS_OK;
}

/* Modified by heyajun kf1199 at 2004-07-12 V800R001B03D005 for BYHD02971 */
ULONG PPP_GetDomainInfoByName(PPPINFO_S *pstPppInfo, UCHAR* pucName)
{
    ULONG ulRet = 0;
    ULONG ulMapRet = 0;
    USHORT usRealDomainIndex = 0;
    USHORT usVirtualDomainIdx = 0;
    PPPCONFIGINFO_S *pstConfigInfo = pstPppInfo->pstConfigInfo;
    UCHAR szDomain[L2TP_DOMAINNAME_MAXLEN + 1];
    UCHAR szUserTemp[L2TP_USER_NAME_LEN + 1];
    UCHAR szUsername[A11_MAX_NAI_LENGTH + 1]; /* �û��� */

    PPP_MemSet((void *)szUsername, 0, A11_MAX_NAI_LENGTH + 1);
    VOS_StrCpy((CHAR*)szUsername, (CHAR *)pucName);

    if(0 == (g_ulSoftPara562 & 0x01))
    {
        usVirtualDomainIdx = (USHORT)GetDomainIndexByName(szUsername);

        if ((usVirtualDomainIdx > 0) && (usVirtualDomainIdx < RM_MAX_APN_NUM))
        {
            ulRet = (ULONG)A11_GetVirtualDomainStatusByIndex(usVirtualDomainIdx);
            if (VOS_OK == ulRet)
            {
                ulMapRet = (ULONG)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1174);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1175);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1176);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR *)pstConfigInfo->ucDomainName, (CHAR *)szUsername);
            return VOS_OK;
        }
    }

    PPP_MemSet((void *)szDomain, 0, sizeof(szDomain));
    PPP_MemSet((void *)szUserTemp, 0, sizeof(szUserTemp));

    if (L2TP_SeparateUserName((CHAR*)pucName, (CHAR*)szDomain, (CHAR*)szUserTemp))
    {
        usVirtualDomainIdx = (USHORT)GetDomainIndexByName(szDomain);

        if ((usVirtualDomainIdx > 0) && (usVirtualDomainIdx < RM_MAX_APN_NUM))
        {
            ulRet = (ULONG)A11_GetVirtualDomainStatusByIndex(usVirtualDomainIdx);
            if (VOS_OK == ulRet)
            {
                ulMapRet = (ULONG)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1177);
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n PPP_GetDomainInfoByName1: virtual_domain(%d)realdomain(%d)",
                                 usVirtualDomainIdx,
                                 usRealDomainIndex);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1178);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1179);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)pucName);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n PPP_GetDomainInfoByName1: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                         pstPppInfo->usVirtualDomainIdx,
                         pstPppInfo->usCDBIndex);
        }
        else    /* �û�����Ч���߸�����û������, ȡȱʡֵ */
        {
            usVirtualDomainIdx = 0;
            if (VOS_TRUE == g_pstApnByIndex[0].ucVirtualApn)
            {
                ulMapRet = (ULONG)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n PPP_GetDomainInfoByName2: virtual_domain(%d)realdomain(%d)",
                                 usVirtualDomainIdx,
                                 usRealDomainIndex);
                    PPP_DBG_OK_CNT(PPP_PHOK_1180);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1181);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1182);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[usRealDomainIndex].aucAPN));
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n PPP_GetDomainInfoByName2: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                         pstPppInfo->usVirtualDomainIdx,
                         pstPppInfo->usCDBIndex);
        }
    }
    else
    {
        usVirtualDomainIdx = 0;
        if (VOS_TRUE == g_pstApnByIndex[0].ucVirtualApn)
        {
            ulMapRet = (ULONG)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
            if (VOS_OK == ulMapRet)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n PPP_GetDomainInfoByName3: virtual_domain(%d)realdomain(%d)",
                             usVirtualDomainIdx,
                             usRealDomainIndex);
                PPP_DBG_OK_CNT(PPP_PHOK_1183);
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1184);
                usRealDomainIndex = usVirtualDomainIdx;
            }
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1185);
            usRealDomainIndex = usVirtualDomainIdx;
        }
        pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
        pstPppInfo->usCDBIndex = usRealDomainIndex;
        VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[usRealDomainIndex].aucAPN));
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_GetDomainInfoByName3: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                     pstPppInfo->usVirtualDomainIdx,
                     pstPppInfo->usCDBIndex);
    }

    return VOS_OK;
}
ULONG PPP_OmAuthInitial()
{
    /* PAP��֤���Դ��� */
    g_stPppPerfStatistic.ulPapTotal = 0;

    /* PAP��֤�ɹ����� */
    g_stPppPerfStatistic.ulPapSuccess = 0;

    /* CHAP��֤���Դ��� */
    g_stPppPerfStatistic.ulChapTotal = 0;

    /* CHAP��֤�ɹ����� */
    g_stPppPerfStatistic.ulChapSuccess = 0;

    return VOS_OK;
}


ULONG PPP_OmCompInitial()
{
    return VOS_OK;
}

ULONG PPP_OmInitial()
{
    ULONG ulRet = VOS_OK;

    if ( VOS_TRUE == g_ulHsgwPppPerfInitOkFlg )
    {
        return VOS_OK;
    }

    /* ע������ͳ�� */
    /* �յ���Э�̱����� */
    g_stPppPerfStatistic.ulReceiveNego = 0;

    /* �յ���Ч�ı����� */
    g_stPppPerfStatistic.ulReceiveNegoErr = 0;

    /* ���͵�Э�̱������� */
    g_stPppPerfStatistic.ulSendNego = 0;

    /* LCPЭ�̳��Դ��� */
    g_stPppPerfStatistic.ulLcpTotal = 0;

    /* LCPЭ�̳ɹ����� */
    g_stPppPerfStatistic.ulLcpSuccess = 0;

    /* IPCPЭ�̳��Դ��� */
    g_stPppPerfStatistic.ulIpcpTotal = 0;

    /* IPCPЭ�̳ɹ����� */
    g_stPppPerfStatistic.ulIpcpSuccess = 0;

    /* PPPЭ��ʱ���ܺ� */
    g_stPppPerfStatistic.ulPppNegoTotalTime = 0;
    /* PPPЭ�̴��� */
    g_stPppPerfStatistic.ulPppNegoNum = 0;
    /* ƽ��PPPЭ��ʱ�� */
    g_stPppPerfStatistic.ulPppNegoTime = 0;

    ulRet = PPP_OmAuthInitial();
    if (VOS_ERR == ulRet)
    {
        return VOS_ERR;
    }

    ulRet = PPP_OmCompInitial();
    if (VOS_ERR == ulRet)
    {
        return VOS_ERR;
    }

    /* CCPЭ�̳��Դ��� */
    g_stPppPerfStatistic.ulCcpTotal = 0;

    /* CCPЭ�̳ɹ����� */
    g_stPppPerfStatistic.ulCcpSuccess = 0;


    g_stPppPerfStatistic.ulCurVjUser = 0;

    g_stPppPerfStatistic.ulCurMppcUser = 0;

    g_stPppPerfStatistic.ulCurMppcVjUser = 0;

    g_stIpv6PerfStatistic.ulIpv6CpNegoAttempt   = 0;

    g_stIpv6PerfStatistic.ulIpv6CpNegoSucc      = 0;

    g_stIpv6PerfStatistic.ulMipIpv4v6UserActNum = 0;

    g_stIpv6PerfStatistic.ulSipIpv6UserActNum   = 0;

    /* HSGW ����ͳ�� */

    /* �ڲ�����ȫ�ֱ�����ʼ�� */
    PPP_MemSet((VOID *)&g_stPppDebugImsi, 0, sizeof(IMSI_S));

    g_ulHsgwPppPerfInitOkFlg = VOS_TRUE;

    return VOS_OK;
}
VOID PPP_OmMsg_LCP(UCHAR uccode, ULONG *pulGiMsgType, UCHAR ucflag, ULONG ulIndex)
{
    switch (uccode)
    {
        case VEDRSPEC:
            *pulGiMsgType = PPP_TRC_LCP_VERSION_CAP;
            break;
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_LCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_LCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_LCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_LCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_LCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_LCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_LCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_LCP_PROTREJ;
            break;
        case ECHOREQ:
            *pulGiMsgType = PPP_TRC_LCP_ECHOREQ;
            break;
        case ECHOREP:
            *pulGiMsgType = PPP_TRC_LCP_ECHOREP;
            break;
        case IDENTIFIC:
            *pulGiMsgType = PPP_TRC_LCP_INDENTI;
            break;
        case DISCREQ:
            *pulGiMsgType = PPP_TRC_LCP_DISCREQ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_IPV6CP(UCHAR uccode, ULONG *pulGiMsgType, UCHAR ucflag, ULONG ulIndex)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_IPV6CP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_IPV6CP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_IPCP(UCHAR uccode, ULONG *pulGiMsgType, UCHAR ucflag, ULONG ulIndex)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_IPCP_CONFREQ;

            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_IPCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_IPCP_CONFNAK;


            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_IPCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_IPCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_IPCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_IPCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_IPCP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_SCCP(UCHAR uccode, ULONG *pulGiMsgType)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_SCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_SCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_SCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_SCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_SCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_SCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_SCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_SCP_PROTREJ;
            break;
        case RESETREQ:
            *pulGiMsgType = PPP_TRC_SCP_RESETREQ;
            break;
        case RESETACK:
            *pulGiMsgType = PPP_TRC_SCP_RESETACK;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_PAP(UCHAR uccode, ULONG *pulGiMsgType)
{
    switch (uccode)
    {
        case PAP_AUTHREQ:
            *pulGiMsgType = PPP_TRC_PAP_AUTHREQ;
            break;
        case PAP_AUTHACK:
            *pulGiMsgType = PPP_TRC_PAP_AUTHACK;
            break;
        case PAP_AUTHNAK:
            *pulGiMsgType = PPP_TRC_PAP_AUTHNAK;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_CHAP(UCHAR uccode, ULONG *pulGiMsgType, ULONG ulIndex)
{
    switch (uccode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
            *pulGiMsgType = PPP_TRC_CHAP_CHALLENGE;


            break;
        case CHAP_PACKET_CODE_RESPONSE:
            *pulGiMsgType = PPP_TRC_CHAP_RESPONSE;
            break;
        case CHAP_PACKET_CODE_FAILURE:
            *pulGiMsgType = PPP_TRC_CHAP_FAILURE;
            break;
        case CHAP_PACKET_CODE_SUCCESS:
            *pulGiMsgType = PPP_TRC_CHAP_SUCCSSS;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_EAP(UCHAR uccode, ULONG *pulGiMsgType)
{
    switch (uccode)
    {
        case EAP_PACKET_CODE_REQUEST:
            *pulGiMsgType = PPP_TRC_EAP_REQUEST;
            break;
        case EAP_PACKET_CODE_RESPONSE:
            *pulGiMsgType = PPP_TRC_EAP_RESPONSE;
            break;
        case EAP_PACKET_CODE_SUCCESS:
            *pulGiMsgType = PPP_TRC_EAP_SUCCSSS;
            break;
        case EAP_PACKET_CODE_FAILURE:
            *pulGiMsgType = PPP_TRC_EAP_FAILURE;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


VOID PPP_OmMsg_VSNCP(UCHAR uccode, ULONG *pulGiMsgType)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_VSNCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_VSNCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}


ULONG PPP_OmMsgUserCheck(UCHAR ulCheckRpFlg, ULONG ulIndex, ULONG *pulIP)
{
    ULONG ulResult = VOS_ERR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S* pstRpContext = VOS_NULL_PTR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_OmMsgUserCheck: Rp or Gn message trace.");

    if (VOS_TRUE == ulCheckRpFlg)
    {
        ulResult = (ULONG)SDB_GetRpContextByIndex(ulIndex, (UCHAR**)&pstRpContext);
        if ((VOS_OK != ulResult) || (VOS_NULL_PTR == pstRpContext))
        {
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_OmMsgUserCheck: Get PcfIP failed.");
            PPP_DBG_ERR_CNT(PPP_PHERR_503);

            /*PPP_Free(pMsg);*//* Deleted by heyajun kf1199 at 2003-09-23 V800R001B02D002 for BYHD00224 */
            return VOS_ERR;
        }

        *pulIP = pstRpContext->ulPcfIP;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_504);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_OmMsgUserCheck: Rp or Gn message trace pstPppInfo is VOS_NULL_PTR.");
        return VOS_ERR;
    }

    /* BEGIN: Added by longsirui 41291, 2008/3/1   ���ⵥ��:AX4D00767 */
    /*�ͻ���ģʽppp������GN�ڸ���*/
    if (1 == pstPppInfo->bPppClient)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_505);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_OmMsgUserCheck: Client mode have no Rp or Gn message trace.bPppClient = %d",
                     pstPppInfo->bPppClient);
        return VOS_ERR;
    }

    /* END:   Added by longsirui 41291, 2008/3/1 */

    if (VOS_FALSE == ulCheckRpFlg)
    {
        *pulIP = pstPppInfo->ulPeerIPAddr;
    }

    return VOS_OK;
}


VOID PPP_OmMsgRpTrc(ULONG ulIndex, ULONG ulGiMsgType, ULONG ulLen, UCHAR *pMsg, IMSI_S *pstImsi)
{

    ULONG ulPcfIP = 0;
    ULONG ulRet = VOS_OK;
    A11_S_IFTRC_FILTER stRpIfFilter;  /* PR������Ϣ */
    ULONG ulTreLen = 0;

    /* ���bit1408��, ���flag+protocol+imsilen+imsi */
    if ( SOFTPARA_BIT1408 )
    {
        *pMsg = (UCHAR)SOFTPARA_BIT1408;
        pMsg += (1+ulLen+2);
        PPP_PUTSHORT(sizeof(IMSI_S), pMsg);/*lint !e669 !e662 */
        VOS_MemCpy((VOID*)pMsg, (VOID*)pstImsi, sizeof(IMSI_S));/*lint !e669*/
        ulTreLen = ulLen + 2+1+2+sizeof(IMSI_S);
        pMsg -=(1+ulLen+2+2);
    }
    else
    {
        ulTreLen = ulLen + 2+1;
    }

    PPP_MemSet((void *)&stRpIfFilter, 0, sizeof(A11_S_IFTRC_FILTER));

    if ((VOS_TRUE == Trc_IsTraceTaskEnabled((VOS_UINT8)TRC_TYPE_RPCSN)) && (ulIndex != 0))
    {
        ulRet = PPP_OmMsgUserCheck(VOS_TRUE, ulIndex, &ulPcfIP);
        if (VOS_ERR == ulRet)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_506);
            return;
        }

        /* �����˲��� */
        stRpIfFilter.ulMsgType = RP_MSGTYPE_PPP;
        stRpIfFilter.ulLogicIp = g_ulA11RpifIp;
        stRpIfFilter.ulPeerIp = ulPcfIP;
        stRpIfFilter.ulVpnIndex = g_ulA11RpifVpnId;

    }
    return;
}
VOID PPP_OmMsgUserTrc(IMSI_S *pstImsi, ULONG ulGiMsgType, ULONG ulLen, UCHAR *pMsg)
{

    IMSI_S stImsiTemp;
    UCHAR aucImsiTemp[M_IMSI_LEN];
    /* S_FAM_BAM_TRC_TIME_DATA stTrcTime = {0};
    ULONG ulMillSecs = 0; */
    A11_S_USERTRC_FILTER stUserFilter;  /* PDSN�û����� */

    if (VOS_NULL_PTR == pstImsi)
    {
        return ;
    }

    PPP_MemSet((void *)&stImsiTemp, 0, sizeof(IMSI_S));
    PPP_MemSet((void *)aucImsiTemp, 0,  M_IMSI_LEN);

    PPP_MemSet((void *)&stUserFilter, 0, sizeof(A11_S_USERTRC_FILTER));
    VOS_MemCpy((VOID *)&stImsiTemp, (VOID *)pstImsi, sizeof(IMSI_S));

#if 0
    if (VOS_TRUE == A11_CheckIsEnableUserTrce(stImsiTemp))
    {
        /* �����Ϣ���� */
        stUserFilter.ulMsgType = PUSER_MSGTYPE_PPP;

        ImsiToString(stImsiTemp, aucImsiTemp);
        (VOID)VOS_MemCpy(stUserFilter.aucImsi, aucImsiTemp, IMSI_ASCII_LEN);

        if (VOS_OK != VOS_TmGet(&(stTrcTime.stDate), &(stTrcTime.stTime), &ulMillSecs))
        {
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,"\r\n VOS_TmGet failed.");
        }

        stTrcTime.ulTick = (ULONG)PGP_getTimeByTicksInMisc();

        /* ���ø��ٽӿں��� */
        FamTrcSendTrcMsgWithTime(TRC_TYPE_PDSN_USER,
                         (VOS_UINT8 *)&stUserFilter,
                         ulGiMsgType + ((ULONG)PUSER_MSGTYPE_PPP << 24), /* Modified by heyajun kf1199 at 2003-09-26 V800R001B02D003 for BYHD00407 */
                         (USHORT)(ulLen + 3),
                         pMsg,
                         stTrcTime);
    }
#endif
    return;
}

/*=======================================================================
 *  ��������:  PPP_OmMsgTrc
 *  �������:  2003��7��
 *  ��    ��:  KF1199 heyajun
 *  ��������:  ��Ϣ����
 *  �������:  pstPppInfo       ���ƿ�ָ��
 *             usProtocol       Э������
 *             pMsg             �����ٵ���Ϣָ��
 *             usMsgLen         ��Ϣ����
 *  �������:  ��
 *  ��������:  VOID
 *  ȫ�ֱ���:  g_struTrcTraceFlag  �ӿڸ��ٱ�־
 *  ����˵��:
 *  ���ú���:  FamTrcSendTrcMsg
 *  ��������:
 *=======================================================================*/
VOID PPP_OmMsgTrc(ULONG ulIndex, USHORT usProtocol, UCHAR* pPacket, ULONG ulLen, UCHAR ucflag, ULONG ulLnsIP,
                  IMSI_S *pstImsi, UCHAR ucEhrpdMode)
{

    ULONG ulGiMsgType = 0;        /* ������Ϣ���� */
    UCHAR uccode = 0;             /* ��������*/
    UCHAR pTraceMsg[1024] = {0};
    UCHAR *pMsg = VOS_NULL_PTR;

    if (ulLen >= (1024 - sizeof(USHORT) - sizeof(UCHAR)))
    {
        ulLen = 1024 - sizeof(USHORT) - sizeof(UCHAR);
    }

    /* ��ȡЭ������� */
    uccode = *pPacket;

    /* �жϸ�����Ϣ���� */
    switch (usProtocol)
    {
        case PPP_LCP:

            PPP_OmMsg_LCP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;

        case PPP_IPCP:

            PPP_OmMsg_IPCP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;

        case PPP_IPV6CP:

            PPP_OmMsg_IPV6CP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;
        case PPP_SCCP:

            PPP_OmMsg_SCCP(uccode, &ulGiMsgType);
            break;

        case PPP_PAP:

            PPP_OmMsg_PAP(uccode, &ulGiMsgType);
            break;
        case PPP_EAP:
            PPP_OmMsg_EAP(uccode, &ulGiMsgType);
            break;
        case PPP_VSNCP:
            PPP_OmMsg_VSNCP(uccode, &ulGiMsgType);
            break;
        case PPP_CHAP:

            PPP_OmMsg_CHAP(uccode, &ulGiMsgType, ulIndex);
            break;
        case PPP_SCP:
            return;
        default:
            ulGiMsgType = PPP_TRC_INVALIDPACKET;
            PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_OmMsgTrc:  invalid msg type ulMsgType = %d!", ulGiMsgType);
            return;
    }

    if (PPP_TRACE_OUT == ucflag)
    {
        ulGiMsgType += 256;
    }
    if (VOS_TRUE == ucEhrpdMode)
    {
        ulGiMsgType += 0x00001000;
    }

    pMsg = pTraceMsg;
    PPP_PUTCHAR(0,pMsg);
    PPP_PUTSHORT(usProtocol, pMsg);
    VOS_MemCpy((VOID*)pMsg, (VOID*)pPacket, ulLen);
    pMsg -= 3;

    /* �û����� */
    PPP_OmMsgUserTrc(pstImsi, ulGiMsgType, ulLen, pMsg);

    /* Rp�ӿڸ��� */
    PPP_OmMsgRpTrc(ulIndex, ulGiMsgType, ulLen, pMsg, pstImsi);
    return;
}

/*=======================================================================
 *  ��������:  PPP_IpcCallback
 *  �������:  2003��7��
 *  ��    ��:  KF1199 heyajun
 *  ��������:  IPC��Ϣ�ص�����
 *  �������:
 *  �������:  ��
 *  ��������:  VOID
 *  ȫ�ֱ���:
 *  ����˵��:
 *  ���ú���:
 *  ��������:
 *=======================================================================*/
ULONG PPP_NodeAdd(ULONG ulRpIndex, ULONG ulPDNIndex, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    ULONG ulReturn = 0;

    (VOID)PPP_NodeDelete(ulRpIndex);
    /* modified by luofang  ��ƽ̨ 20120925 */
    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_507);
        /* �ڴ�����ʧ��,����ʧ�� */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_NodeAdd: PPP_Malloc failed for user %u", ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));
    pNode->ulRpIndex = ulRpIndex;
    pNode->ucNodeType = ucNodeType;
    if (PPP_NEGO_LIST_NODE_LCP_START == pNode->ucNodeType)
    {
        pNode->ucCounter = 12;
    }
    else
    {
        pNode->ucCounter = 6;
    }
    pNode->pNext = g_pstPppNegoList;  /* �ҵ�����ͷ */
    g_pstPppNegoList = pNode;
    PPP_DBG_OK_CNT(PPP_PHOK_1468);

    /* check with liukai */
#if 0
    ulReturn = (ULONG)SDB_GetRpContextByIndex(ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_770);
        return VOS_OK;
    }

    if (pstRpContext->beHRPDMode)
    {
        for (i = 0; i < A11_MAX_PDN_NUM; i++)
        {
            if (pstRpContext->ausPdnIndexArray[i] != 0)
            {
                (VOID)PPP_PDNNodeDelete((ULONG)pstRpContext->ausPdnIndexArray[i]);
            }
        }
    }
#endif
    return VOS_OK;
}

ULONG PPP_NodeDelete(ULONG ulRpIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulRpIndex == ulRpIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1469);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_NegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /*lint -e746*/
    PPP_CompRescSyn();
    /*lint +e746*/

    (VOID)PPP_OmInitial();

    ulOneSecondTimer++;

    /* �����ϱ�һ��PPP�澯 */
    if (0 == ulOneSecondTimer % 3)
    {
        PPP_A11_AlarmProc();
    }

    if(0 == ulOneSecondTimer % 10)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                ULONG ulIndex = pstNode->ulRpIndex;
                ULONG ucNodeType = pstNode->ucNodeType;

                /* ɾ���ڵ�, �޸����� */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                /* ֪ͨЭ�̽��������û�Э��ʧ�ܣ����ƿ��Ѿ�ɾ��, ������֪ͨ */
                if (PPP_CB_STATE_USED == g_astPppPool[ulIndex].usState)
                {
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP nego timeout delete user %u", ulIndex);
                    PPP_INNER_COUNTER(PPP_INNER_COUTNER_027);

                    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
                    if ((VOS_NULL_PTR == pstPppInfo)
                        || (VOS_NULL_PTR == pstPppInfo->pstLcpInfo))
                    {
                        continue;
                    }
                    if (PPP_NEGO_LIST_NODE_LCP_START == ucNodeType)
                    {
                        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_14);
                        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_TOTAL_TIMEOUT);
                        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                        //(VOID)PPP_Shell_ISLIoCtl(ulIndex, PPP_ISLDOWN, VOS_NULL_PTR);
                        /*End of liushuang*/
                        A11_PPP_TermTag(ulIndex, PPP_Negotiation_Fail);
                        PPP_DBG_ERR_CNT(PPP_PHERR_508);
                    }
                    else
                    {
                        PPP_DBG_ERR_CNT(PPP_PHERR_771);
                        (VOID)PPP_DeleteCB(pstPppInfo);
                    }
                }
            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }
    PPP_PDNNegoListProc(pPara);
    PPP_RPNegoListProc(pPara);
}



/*=======================================================================
 *  ��������:  PPP_IpcCallback
 *  �������:  2003��7��
 *  ��    ��:  KF1199 heyajun
 *  ��������:  IPC��Ϣ�ص�����
 *  �������:
 *  �������:  ��
 *  ��������:  VOID
 *  ȫ�ֱ���:
 *  ����˵��:
 *  ���ú���:
 *  ��������:
 *=======================================================================*/
ULONG PPP_PDNNodeAdd(ULONG ulRpIndex, ULONG ulPDNIndex, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode = VOS_NULL_PTR;

    (VOID)PPP_PDNNodeDelete(ulPDNIndex);

    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_767);
        /* �ڴ�����ʧ��,����ʧ�� */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_PDNNodeAdd: PPP_Malloc failed for user %u", ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));

    pNode->ulRpIndex = ulRpIndex;
    pNode->ulPDNIndex = ulPDNIndex;
    pNode->ucNodeType = ucNodeType;
    pNode->ucCounter = 30;     /* 2sһ���̶ȣ��ܹ�60s */
    pNode->pNext = g_pstPppPDNNegoList;  /* �ҵ�����ͷ */
    g_pstPppPDNNegoList = pNode;

    PPP_DBG_OK_CNT(PPP_PHOK_1466);
    return VOS_OK;
}

ULONG PPP_PDNNodeDelete(ULONG ulPDNIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppPDNNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulPDNIndex == ulPDNIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppPDNNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1467);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_PDNNegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppPDNNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    ULONG ulPDNIndex = 0;
    ULONG ulRpIndex = 0;
    ULONG ulRet = 0;

    if(0 == ulOneSecondTimer % 2)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                ulPDNIndex = pstNode->ulPDNIndex;
                ulRpIndex = pstNode->ulRpIndex;

                /* ɾ���ڵ�, �޸����� */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppPDNNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppPDNNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                /* ��ȡPPPC���ƿ�ָ��*/
                GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
                if (VOS_NULL_PTR == pstPppInfo)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_768);
                    continue;
                }
                ulRet = SDB_GetPdnContextByIndex(ulPDNIndex, &pstPDNContext);
                if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_769);
                    continue;
                }

                PPP_DBG_ERR_CNT(PPP_PHERR_775);
                /* ��ʼ��VSNCP���ƿ� */
                PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, pstPDNContext->stEhrpd.ucPdnId);
                stVSNCPInfo.ulPDNRleaseCode = AM_RELCODE_PDN_HSGW_IDLETIMEOUT;
                /* ֪ͨPDNȥ�� */
                PPP_CORE_VSNCPFinishProc(pstPppInfo);
                /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
                PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }

}


/*=======================================================================
 *  ��������:  PPP_RPNodeAdd
 *  �������:  2003��7��
 *  ��    ��:  KF1199 heyajun
 *  ��������:  IPC��Ϣ�ص�����
 *  �������:
 *  �������:  ��
 *  ��������:  VOID
 *  ȫ�ֱ���:
 *  ����˵��:
 *  ���ú���:
 *  ��������:
 *=======================================================================*/
ULONG PPP_RPNodeAdd(ULONG ulRpIndex, ULONG ulReleaseCode, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode = VOS_NULL_PTR;

    (VOID)PPP_RPNodeDelete(ulRpIndex);

    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_776);
        /* �ڴ�����ʧ��,����ʧ�� */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_RPNodeAdd: PPP_Malloc failed for user %u",
                     ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));

    pNode->ulRpIndex = ulRpIndex;
    pNode->ulPDNIndex = ulReleaseCode;  /* ʹ�ô��ֶα���release code */
    pNode->ucNodeType = ucNodeType;
    pNode->ucCounter = 60;     /* 2sһ���̶ȣ��ܹ�60s */
    pNode->pNext = g_pstPppRPNegoList;  /* �ҵ�����ͷ */
    g_pstPppRPNegoList = pNode;

    PPP_DBG_OK_CNT(PPP_PHOK_1473);
    return VOS_OK;
}

ULONG PPP_RPNodeDelete(ULONG ulRPIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppRPNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulRpIndex == ulRPIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppRPNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1474);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_RPNegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppRPNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    ULONG ulRpIndex = 0;
    ULONG ulReleaseCode = 0;

    if(0 == ulOneSecondTimer % 2)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                ulRpIndex = pstNode->ulRpIndex;
                ulReleaseCode = pstNode->ulPDNIndex;
                /* ɾ���ڵ�, �޸����� */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppRPNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppRPNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                (VOID)USM_NotifyReleaseUserFunc(ulRpIndex, ulReleaseCode, VOS_NULL_PTR);

                PPP_DBG_ERR_CNT(PPP_PHERR_777);
            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }

}



/************************************************************
������:     PPPGetPPPConfig
����:       CDB�еõ�ppp������
����:       CDB���ĺ���
������:
����:
���:
����:       PPP_OK,PPP_ERROR
����:
 **************************************************************/
VOID PPPGetPPPConfig(VOID)
{
    PPP_CFG_INFO_REC_S stPppCfgRec;

    (VOID)VOS_MemSet(&stPppCfgRec, 0, sizeof(stPppCfgRec));     /* ��ʼ��PPP_CFG_INFO_REC_S */

    g_stPppCfgInfo.ucAuthmod = PPPCFG_AUTHMODE_NONE;
    VOS_StrCpy((CHAR*)g_stPppCfgInfo.aucHostname, PPPCFG_HOSTNAME_DEFAULT_PDSN);
    g_stPppCfgInfo.usMru = PPP_GetDefaultMru();      /* mod by w00316385, ʹ��Ĭ�ϵ�MRU����NV���ж�ȡ */
    g_stPppCfgInfo.ucTimeout = PPPCFG_TIMEOUT_DEFAULT;
    g_stPppCfgInfo.ucAuthoption = PPPCFG_AUTHOPTION_DEFAULT;/* Added by LHT04029 at 2006-06-16 R2C02B025 for BYHD10294 */
    g_stPppCfgInfo.ucIpv6Flag = 1;
    g_stPppCfgInfo.ucVSNCPFlag = (PPP_VSNCP_APN_AMBR_FLAG | PPP_VSNCP_DEFUALT_APN_INDICATIOR_FLAG);

    return;
}

/************************************************************
������:            CDB_PppCfgModNotify
����:              ppp ���øı�ʱnotify����
����:               CDB���ĺ���
������:            CDB �ص�
����:
���:
����:               ��
����:
 **************************************************************/
VOID CDB_PppCfgModNotify( CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*     pNewValue, UCHAR*     pOldValue)
{
    /*��������Ƿ�*/
    if ((M_OS_PPPCFG_TBL_ID != nTbl) || (VOS_NULL_PTR == pNewValue) || (VOS_NULL_PTR == pOldValue))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCfgModNotify: ERROR INPUT PARA");
        return;
    }

    g_stPppCfgInfo.ucAuthmod = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucAuthmod;
    VOS_StrCpy((CHAR *) (g_stPppCfgInfo.aucHostname), (CHAR *)((PPP_CFG_INFO_REC_S*)pNewValue)->aucHostname);
    g_stPppCfgInfo.usMru = ((PPP_CFG_INFO_REC_S*)pNewValue)->usMru;
    g_stPppCfgInfo.ucTimeout = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucTimeout;
    g_stPppCfgInfo.ucAuthoption = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucAuthoption;/* Added by LHT04029 at 2006-06-16 R2C02B025 for BYHD10294 */
    g_stPppCfgInfo.ucIpv6Flag = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucIpv6Flag;
    g_stPppCfgInfo.ucVSNCPFlag = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucVSNCPFlag;
    return;
}

/************************************************************
������:     CDB_PppCfgAddNotify
����:           ppp ���øı�ʱnotify����
����:           CDB���ĺ���
������:      CDB �ص�
����:
���:
����:           ��
����:
 **************************************************************/
VOID CDB_PppCfgAddNotify(      CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*    pValue)
{
    /*��������Ƿ�*/
    if ((M_OS_PPPCFG_TBL_ID != nTbl) || (VOS_NULL_PTR == pValue))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCfgAddNotify: ERROR INPUT PARA");
        return;
    }

    g_stPppCfgInfo.ucAuthmod = ((PPP_CFG_INFO_REC_S*)pValue)->ucAuthmod;
    VOS_StrCpy((CHAR *) (g_stPppCfgInfo.aucHostname), (CHAR *)(((PPP_CFG_INFO_REC_S*)pValue)->aucHostname));
    g_stPppCfgInfo.usMru = ((PPP_CFG_INFO_REC_S*)pValue)->usMru;
    g_stPppCfgInfo.ucTimeout = ((PPP_CFG_INFO_REC_S*)pValue)->ucTimeout;
    g_stPppCfgInfo.ucAuthoption = ((PPP_CFG_INFO_REC_S*)pValue)->ucAuthoption;/* Added by LHT04029 at 2006-06-16 R2C02B025 for BYHD10294 */
    g_stPppCfgInfo.ucIpv6Flag = ((PPP_CFG_INFO_REC_S*)pValue)->ucIpv6Flag;
    g_stPppCfgInfo.ucVSNCPFlag = ((PPP_CFG_INFO_REC_S*)pValue)->ucVSNCPFlag;

    return;
}

/************************************************************
������:     CDB_PppCompressGetGlobalVar
����:       ��ѹ��ȫ�ֱ�����ֵ
����:
������:
����:
���:
����:       PPP_OK,PPP_ERROR
����:
 **************************************************************/

VOID CDB_PppCompressGetGlobalVar(PPP_COMPRESS_CFG *pstCompCfg)
{
   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_VJ_FLAG)
   {
       g_ucPppVjSwitch = 1;
   }
   else
   {
       g_ucPppVjSwitch = 0;

       /* Modified start by liutao 38563 at 2004-10-29 V800R002 for PPPC��ֲ */
   }

   g_ucPppCcpSwitch = 0;
   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_MPPC_FLAG)
   {
       g_ucPppCcpSwitch = 1;
       g_ucPppCcpType |= M_PPPCOMPRESS_MPPC_FLAG;
   }
   else
   {
       g_ucPppCcpType &= ~M_PPPCOMPRESS_MPPC_FLAG;
   }

   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_STAC_FLAG)
   {
       g_ucPppCcpSwitch = 1;
       g_ucPppCcpType |= M_PPPCOMPRESS_STAC_FLAG;
   }
   else
   {
       g_ucPppCcpType &= ~M_PPPCOMPRESS_STAC_FLAG;
   }
}

VOS_UINT32 DBApiQuerySingle(CDB_TBLID nTableId,
                            VOS_INT32 dwCondNum,
                            S_CFG_CDB_CONDITION *pCond,
                            VOS_INT8 *pTuple)
{
    return 0;
}

/************************************************************
������:     PPPGetCompressConfig
����:       CDB�еõ�ѹ��������
����:       CDB���ĺ���
������:
����:
���:
����:       PPP_OK,PPP_ERROR
����:
 **************************************************************/
VOID PPPGetCompressConfig(VOID)
{
    ULONG ulRetCode = M_CFG_DB_API_DBERROR;
    S_CFG_CDB_CONDITION stCdbCon[2];
    PPP_COMPRESS_CFG stCompCfg = { 0 };
    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;


    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());

    stCdbCon[0].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[0].udwFieldId = M_OS_PPPCOMPRESS_FLD_GROUPNUMBER;
    *(UCHAR*)stCdbCon[0].aValue = (UCHAR)ucGroupId;


    stCdbCon[1].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[1].udwFieldId = M_OS_PPPCOMPRESS_FLD_INSTANCEID;
    *(UCHAR*)stCdbCon[1].aValue = (UCHAR)ucInstanceId;

    ulRetCode = DBApiQuerySingle(M_OS_PPPCOMPRESS_TBL_ID,
                                2,
                                stCdbCon,
                                (CHAR*)(&stCompCfg));

    if (M_CFG_DB_API_SUCCESS == ulRetCode)
    {
        CDB_PppCompressGetGlobalVar(&stCompCfg);
        return;
    }

    stCdbCon[0].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[0].udwFieldId = M_OS_PPPCOMPRESS_FLD_GROUPNUMBER;
    *(UCHAR*)stCdbCon[0].aValue = (UCHAR)ucGroupId;

    stCdbCon[1].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[1].udwFieldId = M_OS_PPPCOMPRESS_FLD_INSTANCEID;
    *(UCHAR*)stCdbCon[1].aValue = 0;

    ulRetCode = DBApiQuerySingle(M_OS_PPPCOMPRESS_TBL_ID,
                                2,
                                stCdbCon,
                                (CHAR*)(&stCompCfg));

    if (M_CFG_DB_API_SUCCESS == ulRetCode)
    {
        CDB_PppCompressGetGlobalVar(&stCompCfg);
        return;
    }

    g_ucPppVjSwitch  = 0;
    g_ucPppCcpSwitch = 0;

    return;
}

/************************************************************
������:            CDB_PppCompressCfgModNotify
����:              compress���øı�ʱnotify����
����:              CDB���ĺ���
������:            CDB �ص�
����:
���:
����:               ��
����:
 **************************************************************/
VOID CDB_PppCompressCfgModNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR* pNewValue, UCHAR* pOldValue)
{
    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;
    PPP_COMPRESS_CFG *pstCompCfg = VOS_NULL;


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgModNotify: ENTER");

    /*��������Ƿ�*/
    if ((M_OS_PPPCOMPRESS_TBL_ID != nTbl) || (VOS_NULL_PTR == pNewValue) || (VOS_NULL_PTR == pOldValue))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgModNotify: ERROR INPUT PARA");
        return;
    }

    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());
    pstCompCfg = (PPP_COMPRESS_CFG *)pNewValue;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgModNotify: pstCompCfg->ucCompressFlag = %d, pstCompCfg->ucGroupNumber = %d. pstCompCfg->ucInstanceId = %d",
                 pstCompCfg->ucCompressFlag,pstCompCfg->ucGroupNumber,pstCompCfg->ucInstanceId);

    if (pstCompCfg->ucGroupNumber != ucGroupId)
    {
         return;
    }

    if((0 != ucInstanceId) && (pstCompCfg->ucInstanceId != ucInstanceId))
    {
        return;
    }

    CDB_PppCompressGetGlobalVar(pstCompCfg);

    return;
}

/************************************************************
������:     CDB_PppCompressCfgAddNotify
����:       compress���øı�ʱnotify����
����:       CDB���ĺ���
������:     CDB �ص�
����:
���:
����:       ��
����:
 **************************************************************/
VOID CDB_PppCompressCfgAddNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*  pValue)
{

    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;
    PPP_COMPRESS_CFG *pstCompCfg = VOS_NULL;


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgAddNotify: ENTER");

    /*��������Ƿ�*/
    if ((M_OS_PPPCOMPRESS_TBL_ID != nTbl) || (VOS_NULL_PTR == pValue))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgAddNotify: ERROR INPUT PARA");
        return;
    }

    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());
    pstCompCfg = (PPP_COMPRESS_CFG *)pValue;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "CDB_PppCompressCfgAddNotify: pstCompCfg->ucCompressFlag = %d, pstCompCfg->ucGroupNumber = %d. pstCompCfg->ucInstanceId = %d",
                 pstCompCfg->ucCompressFlag,pstCompCfg->ucGroupNumber,pstCompCfg->ucInstanceId);

    if (pstCompCfg->ucGroupNumber != ucGroupId)
    {
         return;
    }

    if((0 != ucInstanceId) && (pstCompCfg->ucInstanceId != ucInstanceId))
    {
        return;
    }

    CDB_PppCompressGetGlobalVar(pstCompCfg);

    return;
}

ULONG PPP_A11_GetDnsAddress(ULONG ulRpIndex, ULONG * pulDNSAddress1, ULONG * pulDNSAddress2)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    if ((VOS_NULL == pulDNSAddress1)
        || (VOS_NULL == pulDNSAddress2))
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_510);
        return VOS_ERR;
    }

    *pulDNSAddress1 = pstPppInfo->ulDNSAddr1;
    *pulDNSAddress2 = pstPppInfo->ulDNSAddr2;

    return VOS_OK;
}
ULONG PPP_GetIpV6Capbility(VOID)
{
    /* �Ƿ�֧��ipv6,0��ʾ֧��*/
    if (0 == g_stPppCfgInfo.ucIpv6Flag)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}
ULONG PPP_GetRetryInterval(VOID)
{
    return (ULONG)g_stPppCfgInfo.ucTimeout;
}




ULONG PPP_CheckVjLimit()
{
    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* ������������ʱ����Э��VJѹ��:1.���ش�;2.�ӿ���λ���ӿ��û���δ����;3.���ӿ�DPE��CPUδ����; 4.Licenseδ���� */
        if ((1 == g_ucPppVjSwitch)
            && (((PPP_CPU_ONLINE == g_ulPppSubBordStat[0]) && (HSGW_PRODUCT_VJ_USER_NUMBER > g_ulDmpuVjUser[0]))
               || ((PPP_CPU_ONLINE == g_ulPppSubBordStat[1]) && (HSGW_PRODUCT_VJ_USER_NUMBER > g_ulDmpuVjUser[1])))
            && (g_ulMinDmpuDpeCpuRate < g_ulDmpuCpuThreshold))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1187);
            return VOS_OK;
        }

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
            "\r\nPPP_CheckVjLimit: g_ucPppVjSwitch = %lu, g_ulPppSubBordStat[0] = %lu, g_ulDmpuVjUser[0] = %lu, g_ulMinDmpuDpeCpuRate = %lu",
            g_ucPppVjSwitch, g_ulPppSubBordStat[0], g_ulDmpuVjUser[0], g_ulMinDmpuDpeCpuRate);
    }
    else
    {
        if ((1 == g_ucPppVjSwitch)
            && (HSGW_PRODUCT_VJ_USER_NUMBER_PER_SC > g_ulDmpuVjUser[0])
#ifdef __LINUX_PLATFORM__
            && (CMP_CHECK_CPU_USAGE > MON_CpuUsage_MaxCpuOrTidUsage())
#endif
            )
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1188);
            return VOS_OK;
        }
    }

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_020);
    return VOS_ERR;
}
ULONG PPP_CheckCcpLimit( )
{
    /* Ŀǰֻ֧��MPPCѹ�� */
    /*lint -e746*/
    return PPP_CheckMppcLimit();
    /*lint +e746*/
}
ULONG PPP_CheckMppcLimit( )
{
    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* ������������ʱ����Э��MPPCѹ��:1.���ش�;2.�ӿ���λ���ӿ��û���δ����;3.���ӿ�DPE��CPUδ����; 4.Licenseδ���� */
        if ((1 == g_ucPppCcpSwitch) &&(g_ucPppCcpType & M_PPPCOMPRESS_MPPC_FLAG)
            && (((PPP_CPU_ONLINE == g_ulPppSubBordStat[0]) && (HSGW_PRODUCT_MPPC_PDP_NUMBER > g_ulDmpuMppcUser[0]))
                || ((PPP_CPU_ONLINE == g_ulPppSubBordStat[1]) && (HSGW_PRODUCT_MPPC_PDP_NUMBER > g_ulDmpuMppcUser[1])))
            && (g_ulMinDmpuDpeCpuRate < g_ulDmpuCpuThreshold))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1189);
            return VOS_OK;
        }

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                    "\r\nPPP_CheckMppcLimit: g_ucPppCcpSwitch = %lu, g_ucPppCcpType = %lu, g_ulPppSubBordStat[0] = %lu, g_ulDmpuMppcUser[0] = %lu, g_ulMinDmpuDpeCpuRate = %lu",
                    g_ucPppCcpSwitch, g_ucPppCcpType, g_ulPppSubBordStat[0], g_ulDmpuMppcUser[0], g_ulMinDmpuDpeCpuRate);
    }
    else
    {
       if ((1 == g_ucPppCcpSwitch)
            && (HSGW_PRODUCT_MPPC_PDP_NUMBER_PER_SC > g_ulDmpuMppcUser[0])
 #ifdef __LINUX_PLATFORM__
            && (CMP_CHECK_CPU_USAGE > MON_CpuUsage_MaxCpuOrTidUsage())
 #endif
        )
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1190);
            return VOS_OK;
        }
    }
    PPP_INNER_COUNTER(PPP_INNER_COUTNER_021);
    return VOS_ERR;
}
ULONG PPP_CheckStacLimit( )
{
    return VOS_ERR;
}




VOID PPP_CompUserNumAdd(PPPINFO_S *pstPppInfo, ULONG ulCompType)
{
#if 0
    ULONG usDomainIndex = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_022);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER051);
        return;
    }

    usDomainIndex = pstPppInfo->usCDBIndex;
    if (MAX_DOMAIN_NUM <= usDomainIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_511);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER025);
        return;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        ucDmpuId = pstPppInfo->ucDmpuId;
        ucDpeId  = pstPppInfo->ucDpeId;
        if ((MAX_DMPU_NUM <= ucDmpuId) || (MAX_DPE_NUM_PDSN <= ucDpeId))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_512);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER026);
            return;
        }
    }

    switch(ulCompType)
    {
        case PPP_USERSTAT_VJ:
        {
            if (pstPppInfo->bVjFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_513);
                return;
            }

            /* VJ�û�ͳ������ */
            pstPppInfo->bVjFlag = VOS_TRUE;

            /* License���ӿ��û���ͳ�� */
            //A11_LicenseStatistic(1, LICE_PDSN_ITEM_TCPIP_PPP_NUM, SC_GRM_ADD);
            (VOID)A11_CompressStatistic(1, E_GRM_VJ_USERNUM, ucDmpuId, ucDpeId, SC_GRM_ADD);

            /* ���Լ��� */
            g_ulDmpuVjUser[ucDmpuId]++;
            g_usPppVjUserNUm[ucDmpuId][ucDpeId]++;

            /* ����ͳ�ƣ����ͬʱЭ����MPPCѹ�� */
            if (pstPppInfo->bMppcFlag)
            {
                /* MPPC+VJ�û�����һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulMppVjUserNum++;
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                /* MPPC�û�����һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulMppcUserNum);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1191);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_056);
            }
            else
            {
                /* ֻ֧��VJѹ����VJ�û�ͳ�Ƽ�һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulVjUserNum++;

                PPP_PerfInc(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1192);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_023);
            }

            break;
        }
        case PPP_USERSTAT_MPPC:
        {
            if (pstPppInfo->bMppcFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_514);
                return;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1193);
            /* MPPC�û�ͳ������ */
            pstPppInfo->bMppcFlag = VOS_TRUE;


            /* ���Լ��� */
            g_ulDmpuMppcUser[ucDmpuId]++;
            g_usPppMppcUserNum[ucDmpuId][ucDpeId]++;

            /* ����ͳ�ƣ����ͬʱЭ����VJѹ�� */
            if (pstPppInfo->bVjFlag)
            {
                /* MPPC+VJ�û�����һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulMppVjUserNum++;
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcVjUser, PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                /* VJ�û�����һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulVjUserNum);

                PPP_PerfDec(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1194);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_057);
            }
            else
            {
                /* ֻ֧��MPPCѹ����MPPC�û�ͳ�Ƽ�һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulMppcUserNum++;

                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1195);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_024);
            }
            break;
        }
        case PPP_USERSTAT_ZLS0:
        {
            if (pstPppInfo->bLzs0Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_515);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1196);
            pstPppInfo->bLzs0Flag = VOS_TRUE;
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_025);
            g_usPppLzs0UserNum++;
            break;
        }
        case PPP_USERSTAT_ZLS1:
        {
            if (pstPppInfo->bLzs1Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_516);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1197);
            pstPppInfo->bLzs1Flag = VOS_TRUE;
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_026);
            g_usPppLzs1UserNum++;
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_517);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER027);
            break;
        }
    }
#endif
    return;
}
VOID PPP_CompUserNumDel(PPPINFO_S *pstPppInfo, ULONG ulCompType)
{

    ULONG usDomainIndex = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    PPP_DBG_OK_CNT(PPP_PHOK_1198);
    PPP_INNER_COUNTER(PPP_INNER_COUTNER_027);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER050);
        return;
    }

    usDomainIndex = pstPppInfo->usCDBIndex;
    if (MAX_DOMAIN_NUM <= usDomainIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_518);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER028);
        return;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        ucDmpuId = pstPppInfo->ucDmpuId;
        ucDpeId  = pstPppInfo->ucDpeId;
        if ((MAX_DMPU_NUM <= ucDmpuId) || (MAX_DPE_NUM_PDSN <= ucDpeId))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_519);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER029);
            return;
        }
    }

    switch(ulCompType)
    {
        case PPP_USERSTAT_VJ:
        {
         /*It is not supported currently*/
	#if 0		
            if (VOS_TRUE != pstPppInfo->bVjFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_520);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER030);
                return;
            }

            pstPppInfo->bVjFlag = VOS_FALSE;

            /* ���Լ��� */
            PPP_SUBCOUNT(g_ulDmpuVjUser[ucDmpuId]);
            PPP_SUBCOUNT(g_usPppVjUserNUm[ucDmpuId][ucDpeId]);

            /* ����ͳ�ƣ����ͬʱЭ����MPPCѹ�� */
            if (pstPppInfo->bMppcFlag)
            {
                /* MPPC+VJѹ���û�����һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulMppVjUserNum);

                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                /* MPPC�û�����һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulMppcUserNum++;

                PPP_DBG_OK_CNT(PPP_PHOK_1199);
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_059);
            }
            else
            {
                /* ֻ֧��VJѹ����VJ�û�ͳ�Ƽ�һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulVjUserNum);
                PPP_DBG_OK_CNT(PPP_PHOK_1200);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_058);
            }
	#endif
            break;
        }
        case PPP_USERSTAT_MPPC:
        {
            if (VOS_TRUE != pstPppInfo->bMppcFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_521);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER031);
                return;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1201);
            pstPppInfo->bMppcFlag = VOS_FALSE;

            PPP_SUBCOUNT(g_ulDmpuMppcUser[ucDmpuId]);
            PPP_SUBCOUNT(g_usPppMppcUserNum[ucDmpuId][ucDpeId]);

            /* ����ͳ�ƣ����ͬʱЭ����VJѹ�� */
            if (pstPppInfo->bVjFlag)
            {
                /* MPPC+VJѹ���û�����һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulMppVjUserNum);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                /* VJ�û�ͳ�Ƽ�һ */
                g_pstA11DomainNumInfo[usDomainIndex].ulVjUserNum++;

                PPP_DBG_OK_CNT(PPP_PHOK_1202);
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_061);
            }
            else
            {
                /* ֻ֧��MPPCѹ����MPPC�û�ͳ�Ƽ�һ */
                PPP_SUBCOUNT(g_pstA11DomainNumInfo[usDomainIndex].ulMppcUserNum);

                PPP_DBG_OK_CNT(PPP_PHOK_1203);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_060);
            }
            break;
        }
        case PPP_USERSTAT_ZLS0:
        {
            if (VOS_TRUE != pstPppInfo->bLzs0Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_522);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1204);

            pstPppInfo->bLzs0Flag = VOS_FALSE;
            PPP_SUBCOUNT(g_usPppLzs0UserNum);
            break;
        }
        case PPP_USERSTAT_ZLS1:
        {
            if (VOS_TRUE != pstPppInfo->bLzs1Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_523);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1205);

            pstPppInfo->bLzs1Flag = VOS_FALSE;
            PPP_SUBCOUNT(g_usPppLzs1UserNum);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_524);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER032);
            break;
        }
    }
    return;
}


VOS_VOID PPP_CompUserClear(  )
{
    return ;
}


VOID PPP_CompRescSyn()
{
    ULONG ulRmiIndex = 0;
    ULONG ulDmpuIndex = 0;
    ULONG ulDpeIndex = 0;
    ULONG ulTotalDpeNum = 0;
    ULONG ulCpuRate = 0;
    ULONG ulResult = 0;
    SC_COMPRESS_STATE_S stDmpuStat[MAX_DMPU_NUM] = { 0 };

    if (CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1206);
        return ;
    }

    ulResult = A11_GetCompStatNum(&stDmpuStat[0]);
    if (VOS_OK != ulResult)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_525);
        PPP_DebugOut( ( ULONG )MID_PPPC, LOGLVL_COMMON,
                    "\r\n [ppp]PPP_CompRescSyn: Call GRM_ScGetCompStatNum faild!");
        return;
    }

    /* �õ����ӿ�����DPE��������С����, */
    g_ulMaxDmpuDpeCpuRate = 0;
    g_ulMinDmpuDpeCpuRate = 100;
    VOS_MemSet(g_ulDmpuDpeCpuRate, 0, sizeof(g_ulDmpuDpeCpuRate));
    VOS_MemSet(g_ulDmpuMppcUser, 0, sizeof(g_ulDmpuMppcUser));
    VOS_MemSet(g_ulDmpuVjUser, 0, sizeof(g_ulDmpuVjUser));

    for( ulDmpuIndex = 0; ulDmpuIndex < MAX_DMPU_NUM; ulDmpuIndex++ )
    {
        g_ulDmpuDpeNumber[ulDmpuIndex] = 0;
        if ((PPP_CPU_ONLINE != g_ulPppSubBordStat[ulDmpuIndex])
            || (MAX_DPE_NUM_PDSN < stDmpuStat[ulDmpuIndex].ulDmpuDpeNum))
        {
            continue;
        }

        g_ulDmpuDpeNumber[ulDmpuIndex] = stDmpuStat[ulDmpuIndex].ulDmpuDpeNum;

        /* �õ���DPE��CPUռ���ʣ��Լ�������С���� */
        for (ulDpeIndex = 0; ulDpeIndex < g_ulDmpuDpeNumber[ulDmpuIndex]; ulDpeIndex++)
        {
            ulCpuRate = stDmpuStat[ulDmpuIndex].ucDpeCpuRate[ulDpeIndex];
            if (ulCpuRate > g_ulMaxDmpuDpeCpuRate)
            {
                g_ulMaxDmpuDpeCpuRate = ulCpuRate;
            }
            if (ulCpuRate < g_ulMinDmpuDpeCpuRate)
            {
                g_ulMinDmpuDpeCpuRate = ulCpuRate;
            }

            g_ulDmpuDpeCpuRate[ulTotalDpeNum++] = ulCpuRate;
        }
    }

    /*�������DPE��CPUռ���ʺ����ռ����֮��Ĳ�ֵ������¼��ֵ�ۼƺ� */
    ulCpuRate = 0;
    for ( ulDpeIndex = 0; ulDpeIndex < ulTotalDpeNum; ulDpeIndex++)
    {
        ulCpuRate += g_ulMaxDmpuDpeCpuRate - g_ulDmpuDpeCpuRate[ulDpeIndex] + 1;
        g_ulDmpuDpeCpuRate[ulDpeIndex] = ulCpuRate;
    }

    /* ͳ��ѹ���û��� */
    for (ulRmiIndex = 0; ulRmiIndex < MAX_DMPU_NUM; ulRmiIndex++)
    {
        for (ulDmpuIndex = 0; ulDmpuIndex < MAX_DMPU_NUM; ulDmpuIndex++ )
        {
            if (PPP_CPU_ONLINE != g_ulPppSubBordStat[ulDmpuIndex])
            {
                continue;
            }

            /* �õ����ӿ����û�����������RMI������RMI����ĺ� */
            for (ulDpeIndex = 0; ulDpeIndex < g_ulDmpuDpeNumber[ulDmpuIndex]; ulDpeIndex++)
            {
                g_ulDmpuMppcUser[ulDmpuIndex] += stDmpuStat[ulRmiIndex].ulMppcUserNum[ulDmpuIndex][ulDpeIndex];
                g_ulDmpuVjUser[ulDmpuIndex]   += stDmpuStat[ulRmiIndex].ulVjUserNum[ulDmpuIndex][ulDpeIndex];
            }
        }
    }

    return;
}

ULONG PPP_CompCheckVjUserNum(UCHAR *pucDmpuId)
{
    ULONG ulResult = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucAnotherDmpu = 0;

    if(VOS_NULL_PTR == pucDmpuId)
    {
        return VOS_ERR;
    }

    ucDmpuId = *pucDmpuId;

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* ѡ�е��ӿ�VJ�û����Ѿ��ﵽ���ֵ */
        if (g_ulMaxVJNum <= g_ulDmpuVjUser[ucDmpuId])
        {
            /*����һ���ӿ��û����Ƿ�ﵽ��� */
            ucAnotherDmpu = (ucDmpuId == 0 ? 1 : 0);
            if ((PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucAnotherDmpu])
                || (g_ulMaxVJNum <= g_ulDmpuVjUser[ucAnotherDmpu]))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_780);
                return VOS_ERR;
            }

            /* û�дﵽ�����ֱ��ѡ����һ���ӿ���DPE���� */
            *pucDmpuId = ucAnotherDmpu;
        }
    }
    else
    {
        /*�жϵ�ǰsg�û����Ƿ�ﵽ���ֵ*/
        if (HSGW_PRODUCT_VJ_USER_NUMBER <= g_ulDmpuVjUser[0])
        {
              /* �û����Ѿ��ﵽ���ޣ�����ֹipcp */
              PPP_DBG_ERR_CNT(PPP_PHERR_781);
              return VOS_ERR;
        }
    }

    return VOS_OK;
}

ULONG PPP_CompCheckMppcUserNum(UCHAR *pucDmpuId)
{
    ULONG ulResult = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucAnotherDmpu = 0;

    if(VOS_NULL_PTR == pucDmpuId)
    {
        return VOS_ERR;
    }

    ucDmpuId = *pucDmpuId;

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* ѡ�е��ӿ�MPPC�û����Ѿ��ﵽ���ֵ */
        if (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[ucDmpuId])
        {
            /*����һ���ӿ��û����Ƿ�ﵽ��� */
            ucAnotherDmpu = (ucDmpuId == 0 ? 1 : 0);
            if ((PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucAnotherDmpu])
                || (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[ucAnotherDmpu]))
            {
                /* �ӿ�����λ�����û���Ҳ�Ѿ��ﵽ���ޣ�����ֹCCP */
                PPP_DBG_ERR_CNT(PPP_PHERR_782);
                return VOS_ERR;
            }

            /* û�дﵽ�����ֱ��ѡ����һ���ӿ���DPE���� */
            *pucDmpuId = ucAnotherDmpu;
        }
    }
    else
    {
        /*�жϵ�ǰsg�û����Ƿ�ﵽ���ֵ*/
        if (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[0])
        {
              /* �û����Ѿ��ﵽ���ޣ�����ֹccp */
              PPP_DBG_ERR_CNT(PPP_PHERR_783);
              return VOS_ERR;
        }
    }

    return VOS_OK;
}


ULONG PPP_CompSelectDmpuDpe(UCHAR *pucDmpuId, UCHAR* pucDpeId)
{
    ULONG ulRand = 0;

    if ((VOS_NULL_PTR == pucDmpuId ) || (VOS_NULL_PTR == pucDpeId))
    {
        return VOS_ERR;
    }

    if (VOS_TRUE == g_ulStubDpeNo)
    {
        *pucDmpuId = g_ucStubDmpuId;
        *pucDpeId = 0;
        return VOS_OK;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {

        if ((0 == g_ulDmpuDpeNumber[0]) && (0 == g_ulDmpuDpeNumber[1]))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_526);
            return VOS_ERR;
        }

        /*��󸺺ɴ���70%���Ҹ��ɲ������5%������ð�����ѡ�� */
        if ((70 < g_ulMaxDmpuDpeCpuRate) && (5 + g_ulMinDmpuDpeCpuRate < g_ulMaxDmpuDpeCpuRate ))
        {
            /* ������������봰�ھ���ѡ���ĸ�DPE */
            (VOID)PPPC_CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(ULONG));
            ulRand = ulRand % (g_ulDmpuDpeCpuRate[(g_ulDmpuDpeNumber[0]+g_ulDmpuDpeNumber[1] - 1)]);

             /* ѡ��0���ӿ� */
            if ((0 != g_ulDmpuDpeNumber[0]) && (ulRand < g_ulDmpuDpeCpuRate[g_ulDmpuDpeNumber[0]-1]))
            {
                *pucDmpuId = 0;
                *pucDpeId = (UCHAR)PPP_CompBinSelectDpe(0,
                                            (LONG)(g_ulDmpuDpeNumber[0] - 1),
                                            ulRand);
            }
            else /* ѡ��1���ӿ� */
            {
                *pucDmpuId = 1;
                *pucDpeId = (UCHAR)PPP_CompBinSelectDpe((LONG)g_ulDmpuDpeNumber[0],
                                            (LONG)(g_ulDmpuDpeNumber[0] + g_ulDmpuDpeNumber[1] - 1),
                                            ulRand);
                *pucDpeId -= (UCHAR)g_ulDmpuDpeNumber[0];
            }
        }
        else
        {
            /* ������ѯ��ʽ */
            g_ulLastSelDmpuDpe = (g_ulLastSelDmpuDpe + 1) % (g_ulDmpuDpeNumber[0] + g_ulDmpuDpeNumber[1]);
            if (g_ulLastSelDmpuDpe < g_ulDmpuDpeNumber[0])
            {
                *pucDmpuId = 0;
                *pucDpeId = (UCHAR)g_ulLastSelDmpuDpe;
            }
            else
            {
                *pucDmpuId = 1;
                *pucDpeId = (UCHAR)(g_ulLastSelDmpuDpe - g_ulDmpuDpeNumber[0]);
            }
        }
    }
    else
    {
        /* F��ѡ��SG */
        *pucDmpuId = (UCHAR)DVM_GetSelfCpuId();
        *pucDpeId  = (UCHAR)PSM_Inf_GetSGIndexBySGID(PPP_SELF_SGID);
    }

    return VOS_OK;
}

LONG PPP_CompBinSelectDpe(LONG llow, LONG lhigh, ULONG ulSearchData)
{
    LONG lmid = 0;  /* �˴�Ҫʹ���з�����������С���±�0����� */

    while (llow <= lhigh)
    {
        lmid = (llow + lhigh) / 2;
        if (g_ulDmpuDpeCpuRate[lmid] == ulSearchData)
        {
           return lmid + 1;
        }
        else if (ulSearchData < g_ulDmpuDpeCpuRate[lmid])
        {
            lhigh = lmid - 1;
        }
        else
        {
            llow = lmid + 1;
        }
    }
    return llow;
}
ULONG PPP_CheckRenegoFlag
(       ULONG ulRpIndex,
        UCHAR * pucRegoFlag)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pucRegoFlag)
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        return VOS_ERR;
    }

    if (VOS_TRUE == pstPppInfo->bPpcAAAFlag)
    {
        *pucRegoFlag = VOS_TRUE;
    }
    else
    {
        *pucRegoFlag = VOS_FALSE;
    }

    return VOS_OK;
}



ULONG PPP_L2tpIpcpMsgProc(PMBUF_S *pMbuf )
{
#if 0
    ULONG ulLen = 0;
    ULONG ulReturn = 0;
    ULONG ulA10Index = 0;
    ULONG ulIpAddr = 0;
    UCHAR *pPacket = VOS_NULL_PTR;
    PDN_CONTEXT_S   *pstPdnRec = VOS_NULL;
    FWD_TO_CTRL_HDR *pstCtrl   = VOS_NULL;

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1207);

    /*�ײ��ϱ���PPPЭ�̱�������A10Index����Ҫת����RpIndex*/
    pstCtrl = PMBUF_MTOD(pMbuf, FWD_TO_CTRL_HDR *);

    ulA10Index = pstCtrl->ulPdpIndex;
    ulA10Index = (ULONG)A11_A10GlobalIndexToA10ScIndex(ulA10Index);
    if (0 == ulA10Index)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_527);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: ulA10Index IS INVALID!");
        return VOS_ERR;
    }

    ulReturn = (ULONG)SDB_GetPdnContextByA10IndexForPdsn(ulA10Index, (UCHAR **)&pstPdnRec);
    if ((ulReturn != SDB_SUCCESS) || (VOS_NULL_PTR == pstPdnRec))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_528);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Return Error,A10Index[%d]", ulA10Index);
        return VOS_ERR;
    }

    if (E_PDNTYPE_L2TP != pstPdnRec->ucPdnType)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_529);
        PPP_DebugOut((ULONG)FSU_TID_PPPC, PDSN_DBGLVL_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: It is not L2TP user! pdnindex = %d pdntype %d",
                      pstPdnRec->ulPdnIndex, pstPdnRec->ucPdnType);
        return VOS_ERR;
    }

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pMbuf) - sizeof(FWD_TO_CTRL_HDR);
    if (ulLen > PPP_DEFAULT_NEGO_PACKET_LEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_530);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Msg is too long! len = %d", ulLen);
        return VOS_ERR;
    }

    pPacket = g_ucPppRcvPacketHead;
    PGP_MemZero((void *)pPacket,  PPP_DEFAULT_NEGO_PACKET_LEN + PPP_RESERVED_PACKET_HEADER);

    (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, sizeof(FWD_TO_CTRL_HDR), ulLen, pPacket);

    ulReturn = PPP_GetIpAddrFromPacket(pPacket, ulLen, &ulIpAddr);
    if (VOS_OK != ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_531);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Get IpAddr faild!");
        return VOS_ERR;
    }

    if ((0 != ulIpAddr) && (0xFFFFFFFF != ulIpAddr)
        && (pstPdnRec->ulIpV4Addr != ulIpAddr))
    {
        pstPdnRec->ulIpV4Addr = ulIpAddr;
    }
#endif
    return VOS_OK;
}
ULONG PPP_GetIpAddrFromPacket(UCHAR *pPacket, ULONG ulLen, ULONG *pulIpAddr )
{
    ULONG ulOffset = 0;
    ULONG ulIpAddr = 0;
    ULONG  lCiLen  = 0;
    USHORT usProtocol = 0;
    UCHAR ucCode = 0;
    UCHAR cilen  = 0;
    UCHAR citype = 0;

    /* ���Э���,������PPPͷ���� */
    ulOffset = PPP_Core_GetProtocol(VOS_NULL_PTR, pPacket, &usProtocol);
    if (((ulOffset == 0) || (ulLen < ulOffset))
        || (PPP_IPCP != usProtocol))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_532);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_GetIpAddrFromPacket: Wrong Msg! Offset = %d, Protocol = %d",
                      ulOffset, usProtocol);
        return VOS_ERR;
    }

    /* �ƶ�ָ�� */
    pPacket += ulOffset;
    ulLen   -= ulOffset;

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(cilen, pPacket);  /* ID���ã���ʱ���һ�� */
    PPP_GETSHORT(lCiLen, pPacket);

    if ((lCiLen > ulLen) || (lCiLen < FSM_HDRLEN)
        || ((CONFREQ != ucCode) && (CONFACK != ucCode)))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_533);
        return VOS_ERR;
    }

    /* ���ĳ��ȼ�ȥFSMͷ�ĳ��� */
    lCiLen -= FSM_HDRLEN;

    while (lCiLen >= IPCP_CILEN_ADDR)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);

        if (IPCP_CILEN_VOID > cilen)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_534);
            return VOS_ERR;
        }

        if ((IPCP_CI_ADDR == citype) && (IPCP_CILEN_ADDR == cilen))
        {
             PPP_GETADDR(ulIpAddr, pPacket);
             *pulIpAddr = ulIpAddr;
             return VOS_OK;
        }

        pPacket += (cilen - IPCP_CILEN_VOID);
        lCiLen  -= cilen;
    }

    PPP_DBG_ERR_CNT(PPP_PHERR_535);
    return VOS_ERR;
}


ULONG PPP_GetIpAddrByBufReq( ULONG ulRpIndex, ULONG *pulReqIpAddr )
{
    ULONG ulRet = VOS_OK;
    UCHAR *pucPacket = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pulReqIpAddr)
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_536);
        return VOS_ERR;
    }

    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
    if ((VOS_NULL_PTR == pstIpcpInfo) || (VOS_NULL_PTR == pstIpcpInfo->pucIpv4cpMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_537);
        return VOS_ERR;
    }

    pucPacket = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;

    /* �����ʱ���Ѿ���protocolƫ�Ƶ��ˣ���Ҫ���²��� */
    pucPacket -= sizeof(USHORT);
    *(USHORT*)pucPacket = VOS_HTONS(PPP_IPCP);

    ulRet = PPP_GetIpAddrFromPacket(pucPacket,
                                    pstIpcpInfo->ulIpv4cpLen + sizeof(USHORT),
                                    pulReqIpAddr);

    return ulRet;
}

VOID PPP_SendInnerMsg(ULONG ulPara)
{
    PPP_INNER_MSG_S stInnerMsg = {0};
    ULONG ulReturn = 0;

    stInnerMsg.ulCurRenegoIndex = ulPara;

    /* ʹ��RTD�����ڲ���Ϣ��PPP������ */
    ulReturn = PPP_SendRtMsg(PPP_SELF_CSI, PPP_SELF_CSI,PPP_MSG_TYPE_INNER, PPP_INNER_MSG_CODE_RENEGO,
                             (UCHAR *)&stInnerMsg, sizeof(PPP_INNER_MSG_S));
    if (VOS_OK != ulReturn)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "PPP_SendInnerMsg fail.%u",ulReturn);
        return;
    }

    return;
}

VOID PPP_ClearVjFlag(ULONG  ulRpIndex)
{
    SDB_PDSN_RP_CONTEXT_S *pstRPContext = VOS_NULL_PTR;    /* A10 ������ָ��*/
    SDB_RETURNCODE_E enSdbRet = SDB_SYSTEM_FAILURE;

    enSdbRet = SDB_GetRpContextByIndex(ulRpIndex,
                                     (UCHAR **)&pstRPContext);
    if ((enSdbRet != SDB_SUCCESS) || (VOS_NULL_PTR == pstRPContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "PPP_ClearVjFlag fail");
        PPP_DBG_ERR_CNT(PPP_PHERR_538);
        return ;
    }

    pstRPContext->bVjFlag = VOS_FALSE;
    return;
}

ULONG PPP_A11_GetSubBoardStat( UCHAR ucDmpuId )
{
    if(CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        return VOS_OK;
    }

    ucDmpuId = ucDmpuId - PPP_CPU_2_ON_SPU;

    /*dmpuIDȡֵΪ0����1*/
    if(ucDmpuId > 1)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_778);
        return VOS_ERR;
    }

    if(PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucDmpuId])
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_779);
        return VOS_ERR;
    }
    return VOS_OK;
}

#define __PPP__BACKUP__PROC__
ULONG PPP_EncapL2tpPppcUpInfo(PDN_CONTEXT_S *pstPdnContext, L2TP_NOTIFY_PPPC_UP_INFO *pstL2tpUpInfo)
{
#if 0
    ULONG ulRet = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;


    CKP_DBG_INC_COUTER(CKP_SUCC_99);


    /* ���Ȳ���rp�������Ƿ���ڲ������򴴽�����ֱ�Ӹ��������� */
    ulRet = (ULONG)SDB_GetRpContextByIndex(pstPdnContext->ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {

        CKP_DBG_INC_COUTER(CKP_ERR_40);

        return VOS_ERR;
    }

    pstL2tpUpInfo->ucDpeId              = pstRpContext->ucDpeId;
    pstL2tpUpInfo->ulGtpuIndex          = pstRpContext->ausA10IndexArray[0] + (SDB_MAX_PDSN_A10_CONTEXT_NUM * PPP_SELF_CMPIDXINSG);
    //pstL2tpUpInfo->ulFilterTableIndex   = pstPdnContext->ulPdnIndex;
    pstL2tpUpInfo->ulTeidc              = pstPdnContext->ulTeidc;
    pstL2tpUpInfo->ulPdpindex           = PDN_PDNScIndexToPDNGlobalIndex(pstPdnContext->ulPdnIndex);
    pstL2tpUpInfo->usApnIndex           = pstPdnContext->usDomainIdx;
    pstL2tpUpInfo->ulIFIndex            = pstPdnContext->stL2tp.ulIfIndex;
    pstL2tpUpInfo->ulLocalIP            = pstPdnContext->stL2tp.ulLacAddr;
    pstL2tpUpInfo->ulPeerIP             = pstPdnContext->stL2tp.ulLnsAddr;
    pstL2tpUpInfo->usLocalTunnelId      = pstPdnContext->stL2tp.usLocalTid;
    pstL2tpUpInfo->usLocalSessionId     = pstPdnContext->stL2tp.usLocalSid;
    pstL2tpUpInfo->usPeerTunnelId       = pstPdnContext->stL2tp.usPeerTid;
    pstL2tpUpInfo->usPeerSessionId      = pstPdnContext->stL2tp.usPeerSid;
    pstL2tpUpInfo->ucCompInstIdx        = (UCHAR)PPP_SELF_CMPIDX;
    VOS_MemCpy(pstL2tpUpInfo->szImsi, &pstRpContext->stImsi, sizeof(A11_IMSI_S));
    VOS_MemCpy(pstL2tpUpInfo->szMsisdn, pstRpContext->szMsisdn, sizeof(GTP_MSISDN));
#endif
    return VOS_OK;

}
VOID PPP_BackupUpdateData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPPLCPINFO_S* pstLcpInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    //PPPDHCPINFO_S* pstDhcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_100);
#endif
    /* LCP */
    if (pstPppInfo->pstLcpInfo)
    {
        pstLcpInfo = pstPppInfo->pstLcpInfo;
        VOS_MemCpy((VOID*)&(pstLcpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stLcpGotOptions),
                     sizeof(PPP_LCP_OPTION_S));
        pstLcpInfo->stFsm.ucPktId = pstPppInfobkp->ucLcpPktId;
        pstLcpInfo->stFsm.ucEchoState = pstPppInfobkp->ucEchoState;        /*r002*/
    }

    /* LCP IPCP DHCP�д�����Ϊ���� */
    /* ipv4 ipcp */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlg)
    {
        if (pstPppInfo->pstIpcpInfo)
        {
            pstIpcpInfo = pstPppInfo->pstIpcpInfo;
            VOS_MemCpy((VOID*)&(pstIpcpInfo->stGotOptions),
                         (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                         sizeof(PPP_IPCP_OPTION_S));
            pstIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
            if (1 == pstIpcpInfo->stGotOptions.neg_vj)
            {
                pstPppInfo->pstConfigInfo->bEnableVJComp = 1;        /* Added by liutao 38563 at 2004-11-02 V800R002 for PPPC��ֲ */
            }
        }
        /* �޿��ƿ�����Ҫ�½� */
        else
        {
            /* ΪIPCP�ӿ��ƿ������ڴ� */
            PPP_GETIPCPADDR(pstIpcpInfo,pstPppInfo->ulRPIndex);
            if (VOS_NULL_PTR == pstIpcpInfo)
            {
#if 0
                CKP_DBG_INC_COUTER(CKP_ERR_41);
#endif
                PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_BkpPppDataUpdate: get ipcp addr failed.");
                (VOID)PPP_ClearCB(pstPppInfo);

                return;
            }
            else
            {
                PPP_MemSet((VOID *)pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

                pstPppInfo->pstIpcpInfo = pstIpcpInfo;
                PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

                /* ����State״ֵ̬Ϊsuccess */
                pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

                PPP_IPCP_resetci(&pstIpcpInfo->stFsm);

                pstIpcpInfo->stFsm.ucState = PPP_STATE_OPENED;
                VOS_MemCpy((VOID*)&(pstIpcpInfo->stGotOptions),
                             (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                             sizeof(PPP_IPCP_OPTION_S));
                pstIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
                pstPppInfo->bVjFlag = VOS_FALSE;
                if (1 == pstIpcpInfo->stGotOptions.neg_vj)
                {
                    pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
                }
            }
        }
    }
    else
    {
        /* ��ջipv4ɾ�� */
        if(pstPppInfo->pstIpcpInfo != VOS_NULL_PTR)
        {
            PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
            pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;
        }
    }

    /* ipv6 ipcp */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlgV6)
    {
        if(VOS_NULL_PTR != ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo)))
        {
            (VOID)VOS_MemCpy((VOID*)&(((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stGotOptions),
                               (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                               sizeof(PPP_IPV6CP_OPTION_S));
            ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        }
        /* �޿��ƿ�����Ҫ�½� */
        else
        {
            PPP_GETIPV6CPADDR(pstIpv6cpInfo,pstPppInfo->ulRPIndex);
            if (VOS_NULL_PTR == pstIpv6cpInfo)
            {
#if 0
                CKP_DBG_INC_COUTER(CKP_ERR_42);
#endif
                PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_BkpPppDataCreate: get ipv6 ipcp addr failed.");
                (VOID)PPP_ClearCB(pstPppInfo);

                return;
            }

            PPP_MemSet((VOID *)pstIpv6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

            pstPppInfo->pstIpV6cpInfo = pstIpv6cpInfo;
            PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

            /* ����State״ֵ̬Ϊsuccess */
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

            PPP_IPV6CP_resetci(&pstIpv6cpInfo->stFsm);

            pstIpv6cpInfo->stFsm.ucState = PPP_STATE_OPENED;
            VOS_MemCpy((VOID*)&(pstIpv6cpInfo->stGotOptions),
                         (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                         sizeof(PPP_IPV6CP_OPTION_S));
            pstIpv6cpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        }
    }
    else
    {
        /* ��ջipv6ɾ�� */
        if(pstPppInfo->pstIpV6cpInfo != VOS_NULL_PTR)
        {
            PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
            pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;
        }
    }

    if (VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
    {
        pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
        pstCcpInfo->ucUsed = VOS_FALSE;
        pstPppInfo->pstCcpInfo = VOS_NULL_PTR;
    }

    return;
}
ULONG PPP_BackupCreateData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPPLCPINFO_S *pstPppLcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
    //PPPDHCPINFO_S* pstDhcpInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstPppIpcpInfo = VOS_NULL_PTR;
#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPPEAPINFO_S *pstEapInfo = VOS_NULL_PTR;
#endif
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_101);
#endif
    pstPppInfo->usPhase = PPP_PHASE_NETWORK;

    //pstPppInfo->ulIPAddr = g_ulA11RpifIp;
    pstPppInfo->ulIPAddr = pstPppInfobkp->ulIPAddr;

    /* IPV6CPЭ���б��ص�ַ���ù̶���ַFE80::rp��v4��ַ*/
    //VOS_Mem_Copy((void *)(&usIpv6addr[6]), (void *)&g_ulA11RpifIp,sizeof(ULONG));
    //VOS_Mem_Copy(pstPppInfo->usIpv6Addr, usIpv6addr, IPV6_ADDR_LEN*2);

    VOS_MemCpy(pstPppInfo->usIpv6Addr, pstPppInfobkp->usIpv6Addr, IPV6_ADDR_LEN*2);

    /* LCP���ݻָ� */
    /* ΪLCP�ӿ��ƿ������ڴ� */
    PPP_GETLCPADDR(pstPppLcpInfo, pstPppInfo->ulRPIndex);
    if (!pstPppLcpInfo)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_43);
#endif
        PPP_DebugOut((ULONG)FSU_TID_PPPC, 1,
                "\r\n PPP_BkpRestore: get lcp addr failed");
        return VOS_ERR;
    }

    PPP_MemSet((VOID*)pstPppLcpInfo, 0, sizeof(PPPLCPINFO_S));

    if (PPP_InitConfigInfo(pstPppInfo) == VOS_ERR)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_44);
#endif
        (VOID)PPP_ClearCB(pstPppInfo);
        return VOS_ERR;
    }

    pstPppInfo->ulNegoEndTime = VOS_GetTick();

    pstPppInfo->pstLcpInfo = pstPppLcpInfo;
    PPP_LCP_Init(pstPppInfo);
    PPP_LCP_resetci(&pstPppLcpInfo->stFsm);
    pstPppLcpInfo->stFsm.ucState = PPP_STATE_OPENED;
    VOS_MemCpy((VOID*)&(pstPppLcpInfo->stGotOptions),
                 (VOID*)&(pstPppInfobkp->stLcpGotOptions),
                 sizeof(PPP_LCP_OPTION_S));
    pstPppLcpInfo->stFsm.ucPktId = pstPppInfobkp->ucLcpPktId;
    pstPppLcpInfo->stFsm.ucEchoState = pstPppInfobkp->ucEchoState;        /*r002*/

    /* ipv4 IPCP���ݻָ� */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlg)
    {
        /* ΪIPCP�ӿ��ƿ������ڴ� */
        PPP_GETIPCPADDR(pstPppIpcpInfo,pstPppInfo->ulRPIndex);
        if (!pstPppIpcpInfo)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_45);
#endif
            PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_BkpPppDataCreate: get ipcp addr failed.");
            (VOID)PPP_ClearCB(pstPppInfo);

            return VOS_ERR;
        }

        PPP_MemSet((VOID *)pstPppIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

        pstPppInfo->pstIpcpInfo = pstPppIpcpInfo;
        PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

        /* ����stateΪsuccess */
        pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

        PPP_IPCP_resetci(&pstPppIpcpInfo->stFsm);

        pstPppIpcpInfo->stFsm.ucState = PPP_STATE_OPENED;
        VOS_MemCpy((VOID*)&(pstPppIpcpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                     sizeof(PPP_IPCP_OPTION_S));
        pstPppIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        pstPppInfo->bVjFlag = VOS_FALSE;
        if (1 == pstPppIpcpInfo->stGotOptions.neg_vj)
        {
            /* Added start by liutao 38563 at 2004-11-03 V800R002 for PPPC��ֲ */
            pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
            /* Added end by liutao 38563 at 2004-11-03 V800R002 for PPPC��ֲ */
        }
    }

    /* LCP IPCP DHCP�д�����Ϊ���� */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlgV6)
    {
        /* ipv6 IPCP���ݻָ� */
        PPP_GETIPV6CPADDR(pstIpv6cpInfo,pstPppInfo->ulRPIndex);
        if (!pstIpv6cpInfo)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_46);
#endif
            PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_BkpPppDataCreate: get ipv6 ipcp addr failed.");
            /* pstPppInfo->pstLcpInfo = VOS_NULL_PTR; */
            (VOID)PPP_ClearCB(pstPppInfo);

            return VOS_ERR;
        }

        PPP_MemSet((VOID *)pstIpv6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

        pstPppInfo->pstIpV6cpInfo = pstIpv6cpInfo;
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

        /* ����stateΪsuccess */
        pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

        PPP_IPV6CP_resetci(&pstIpv6cpInfo->stFsm);

        pstIpv6cpInfo->stFsm.ucState = PPP_STATE_OPENED;
        VOS_MemCpy((VOID*)&(pstIpv6cpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                     sizeof(PPP_IPV6CP_OPTION_S));
        pstIpv6cpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    /* eap */
    if (pstPppInfo->bEhrpdUser)
    {
        /*����EAP���ƿ�*/
        PPP_GETEAPADDR(pstPppInfo->pstEapInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstEapInfo != VOS_NULL_PTR)
        {
            /* ��ʼ��EAP���ƿ� */
            PPP_EAP_Init(pstPppInfo);
            pstEapInfo = pstPppInfo->pstEapInfo;
            pstEapInfo->ucState = EAP_STATE_SUCCESS;
        }
        else
        {

            CKP_DBG_INC_COUTER(CKP_ERR_47);

            PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\n PPP_BkpPppDataCreate: get eap addr failed.");
            (VOID)PPP_ClearCB(pstPppInfo);
            return VOS_ERR;
        }
    }
    /* VSNCP�ָ� �����*/
#endif

    pstPppInfo->pstPapInfo   = VOS_NULL_PTR;
    pstPppInfo->pstChapInfo  = VOS_NULL_PTR;
    pstPppInfo->pL2tpPara    = VOS_NULL_PTR;
    pstPppInfo->pstVsncpInfo = VOS_NULL_PTR;

    return VOS_OK;
}


VOID PPP_BackupRestoreVsncp(PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId)
{
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_102);
#endif
    pstPdnContext->stEhrpd.stVSNCP.ucPktId       = ucPktId;
    pstPdnContext->stEhrpd.stVSNCP.ucPDNID       = ucPDNID;
    pstPdnContext->stEhrpd.stVSNCP.ucState       = PPP_STATE_OPENED;
    pstPdnContext->stEhrpd.stVSNCP.ucUsedFlag    = VOS_TRUE;

    return;
}


VOID PPP_BackupRestoreCompData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_103);
#endif
    pstPppInfo->bMppcFlag = VOS_FALSE;

    if (pstPppInfobkp->bMppc)
    {
        PPP_GETCCPADDR(pstCcpInfo, pstPppInfo->ulRPIndex);
        pstPppInfo->pstCcpInfo = pstCcpInfo;
        /* END:   Modified by longsirui 41291, 2008/1/17 */
        if (pstCcpInfo)
        {
            PPP_MemSet(pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* ��ʼ��CCP���ƿ� */
            PPP_CCP_init(pstPppInfo);
            pstCcpInfo->stFsm.ucState = PPP_STATE_OPENED;
            pstCcpInfo->stGotOptions.bMppc_compress = 1;
            pstCcpInfo->stGotOptions.bStac_compress = 0;

            pstCcpInfo->ucPppCompType   = PPPCOMP_MPPC;
        }
    }

    return;
}


VOID PPP_BackupEncapUpdatePppInfo(PPPINFO_S *pstPppInfo, UCHAR **ppucCurrent, ULONG *pulEncapLen)
{
    ULONG                     ulEncapLen      = 0;
    CKP_BACKUP_PPPALLINFO_S  *pstCkpPppBkInfo = VOS_NULL_PTR;
    CKP_BACKUP_MSGTLV_HEAD_S *pstMsgTlvHead   = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_104);
#endif
    ulEncapLen = sizeof(CKP_BACKUP_PPPALLINFO_S);

    /* ����TLVͷ */
    pstMsgTlvHead = (CKP_BACKUP_MSGTLV_HEAD_S*)(*ppucCurrent);
    pstMsgTlvHead->ulSdbIndex = pstPppInfo->ulRPIndex;
    pstMsgTlvHead->ulType     = CKP_BACKUP_TYPE_UPDATE_PPP;
    pstMsgTlvHead->usStrLen   = (USHORT)ulEncapLen;
    pstMsgTlvHead->ucNum      = 1;

    /* ����TLV������ */
    pstCkpPppBkInfo = (CKP_BACKUP_PPPALLINFO_S *)pstMsgTlvHead->ucValue;

    pstCkpPppBkInfo->bIsAsync        = pstPppInfo->bIsAsync;
    pstCkpPppBkInfo->bSynAsyConvert  = pstPppInfo->bSynAsyConvert;
    pstCkpPppBkInfo->bLoopBacked     = pstPppInfo->bLoopBacked;
    pstCkpPppBkInfo->bLowerIsUp      = pstPppInfo->bLowerIsUp;
    pstCkpPppBkInfo->bIPReleaseFlg   = pstPppInfo->bIPReleaseFlg;
    pstCkpPppBkInfo->bIPTech         = pstPppInfo->bIPTech;
    pstCkpPppBkInfo->bAuthServer     = pstPppInfo->bAuthServer;
    pstCkpPppBkInfo->bAuthClient     = pstPppInfo->bAuthClient;
    pstCkpPppBkInfo->bReNego         = pstPppInfo->bReNego;
    pstCkpPppBkInfo->bReNegoV6       = pstPppInfo->bReNegoV6;
    pstCkpPppBkInfo->bEAPAuthFlag    = pstPppInfo->bEAPAuthFlag;

    pstCkpPppBkInfo->bIPCPNakHandFlag = pstPppInfo->bIPCPNakHandFlag;
    pstCkpPppBkInfo->ucAAAType       = pstPppInfo->ucAAAType;

    pstCkpPppBkInfo->bPppStateFlg = 0;
    pstCkpPppBkInfo->bPppStateFlgV6 = 0;
    if (VOS_OK == PDN_JudgeSubPDNStateActive(pstPppInfo->ulRPIndex, E_PDN_STACK_TYPE_IPV4))
    {
        pstCkpPppBkInfo->bPppStateFlg = PPP_STATE_SUCCESS;
    }
    if (VOS_OK == PDN_JudgeSubPDNStateActive(pstPppInfo->ulRPIndex, E_PDN_STACK_TYPE_IPV6))
    {
        pstCkpPppBkInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;
    }
    pstCkpPppBkInfo->bPppMode        = pstPppInfo->bPppMode;
    pstCkpPppBkInfo->bPppClient      = pstPppInfo->bPppClient;
    pstCkpPppBkInfo->bPhaseFlag      = pstPppInfo->bPhaseFlag;
    pstCkpPppBkInfo->bPpcAAAFlag     = pstPppInfo->bPpcAAAFlag;
    pstCkpPppBkInfo->bPppSuccess     = pstPppInfo->bPppSuccess;
    pstCkpPppBkInfo->bAuthFlag       = pstPppInfo->bAuthFlag;
    pstCkpPppBkInfo->bIpcpSucFlag    = pstPppInfo->bIpcpSucFlag;
    pstCkpPppBkInfo->bRecvLcpMsgFlag = pstPppInfo->bRecvLcpMsgFlag;
   // pstCkpPppBkInfo->bBit328SoftPara = pstPppInfo->bBit328SoftPara;
    pstCkpPppBkInfo->bIpv6cpNoToPDN  = pstPppInfo->bIpv6cpNoToPDN;
    pstCkpPppBkInfo->bIpcpNoToPDN    = pstPppInfo->bIpcpNoToPDN;
    pstCkpPppBkInfo->bEhrpdUser      = pstPppInfo->bEhrpdUser;
    pstCkpPppBkInfo->ulRemoteAccm    = pstPppInfo->ulRemoteAccm;
    pstCkpPppBkInfo->ulLocalAccm     = pstPppInfo->ulLocalAccm;

    pstCkpPppBkInfo->ulPcfIP         = pstPppInfo->ulPcfIP;
    pstCkpPppBkInfo->ulIPAddr        = pstPppInfo->ulIPAddr;

    if (PPP_STATE_SUCCESS == pstCkpPppBkInfo->bPppStateFlg)
    {
        pstCkpPppBkInfo->ulPeerIPAddr = pstPppInfo->ulPeerIPAddr;
    }

    /* ˫ջ����DNS AND POOLNAME ���� */
    pstCkpPppBkInfo->ulDNSAddr1         = pstPppInfo->ulDNSAddr1;
    pstCkpPppBkInfo->ulDNSAddr2         = pstPppInfo->ulDNSAddr2;
    pstCkpPppBkInfo->ulNowUTCInSec      = pstPppInfo->ulNowUTCInSec;
    pstCkpPppBkInfo->usPeerId           = pstPppInfo->usPeerId;
    pstCkpPppBkInfo->usCDBIndex         = pstPppInfo->usCDBIndex;
    pstCkpPppBkInfo->usVirtualDomainIdx = pstPppInfo->usVirtualDomainIdx;
    pstCkpPppBkInfo->usMtu              = pstPppInfo->usMtu;
    pstCkpPppBkInfo->usPcfIndex         = pstPppInfo->usPcfIndex;

    /* ����Ƕ�̬aaa����Ҫ���host��realm */
    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        if (VOS_OK != Diam_AUTHGetDynAAAInfoByIndex(pstPppInfo->usPeerId,
                                                    pstCkpPppBkInfo->aucAAAHost,
                                                    pstCkpPppBkInfo->aucAAARealm,
                                                    &pstCkpPppBkInfo->usDynPeerId))
        {
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "PPP_BackupEncapUpdatePppInfo: Diam_AUTHGetDynAAAInfoByIndex Err!! dynaaacbindex[%u]",
                         pstPppInfo->usPeerId);
            PPP_DBG_ERR_CNT(PPP_PHERR_539);
            pstCkpPppBkInfo->usPeerId           = VOS_NULL_WORD;
            pstCkpPppBkInfo->ucAAAType          = VOS_NULL_BYTE;
            pstCkpPppBkInfo->usDynPeerId        = VOS_NULL_WORD;
        }
    }



    VOS_MemCpy(pstCkpPppBkInfo->usIpv6Addr, pstPppInfo->usIpv6Addr, sizeof(pstCkpPppBkInfo->usIpv6Addr));

    if (PPP_STATE_SUCCESS == pstCkpPppBkInfo->bPppStateFlgV6 )
    {
        VOS_MemCpy(pstCkpPppBkInfo->usPeerIPv6Addr,
                     pstPppInfo->usPeerIPv6Addr, sizeof(pstCkpPppBkInfo->usPeerIPv6Addr));
    }

    //VOS_Mem_Copy(pstCkpPppBkInfo->ucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

    pstCkpPppBkInfo->ucServiceOpt   = pstPppInfo->ucServiceOpt;
    pstCkpPppBkInfo->ucFSMFailType  = pstPppInfo->ucFSMFailType;
    pstCkpPppBkInfo->ucDmpuId       = pstPppInfo->ucDmpuId;
    pstCkpPppBkInfo->ucDpeId        = pstPppInfo->ucDpeId;
    pstCkpPppBkInfo->ucIpCapability = pstPppInfo->ucIpCapability;

    if(VOS_NULL_PTR != ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stLcpGotOptions),
                                       (VOID*)&(((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stGotOptions),
                                       sizeof(PPP_LCP_OPTION_S));
        pstCkpPppBkInfo->ucLcpPktId  = ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stFsm.ucPktId;
        pstCkpPppBkInfo->ucEchoState =
                 ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stFsm.ucEchoState;                                             /*r002*/
    }

    if(VOS_NULL_PTR != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stIpcpGotOptions),
                           (VOID*)&(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stGotOptions),
                           sizeof(PPP_IPCP_OPTION_S));
        pstCkpPppBkInfo->ucIpcpPktId =
                      ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stFsm.ucPktId;
    }
    if(VOS_NULL_PTR != ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stIpv6cpGotOptions),
                           (VOID*)&(((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stGotOptions),
                           sizeof(PPP_IPV6CP_OPTION_S));
        pstCkpPppBkInfo->ucIpcpPktId =
                      ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stFsm.ucPktId;
    }

    if (pstPppInfo->pstCcpInfo
        && (PPP_STATE_OPENED == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stFsm.ucState)
        && (1 == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stGotOptions.bStac_compress))
    {
        //pstCkpPppBkInfo->bStac = 1;
        pstCkpPppBkInfo->usStac_historys
            = ((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->stGotOptions.usStac_historys;
    }

    if (pstPppInfo->pstCcpInfo
        && (PPP_STATE_OPENED == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stFsm.ucState)
        && (1 == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stGotOptions.bMppc_compress))
    {
        pstCkpPppBkInfo->bMppc = 1;
    }

    *pulEncapLen += ulEncapLen + CKP_BACKUP_TLV_SIZE;
    *ppucCurrent += ulEncapLen + CKP_BACKUP_TLV_SIZE;

    return;
}
VOID PPP_BackupDecapUpdatePppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext,
                                                PPPINFO_S *pstPppInfo, UCHAR *pucCurrent)
{
    CKP_BACKUP_PPPALLINFO_S *pstCkpPppBkInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_105);
#endif
    pstCkpPppBkInfo = (CKP_BACKUP_PPPALLINFO_S *)pucCurrent;

    pstPppInfo->ulRPIndex       = pstRpContext->ulRpIndex;
    pstPppInfo->usTokenId       = pstRpContext->usTokenId;
    VOS_MemCpy(&(pstPppInfo->stIMSI), &(pstRpContext->stImsi), sizeof(IMSI_S));
    pstPppInfo->bIsAsync        = pstCkpPppBkInfo->bIsAsync;
    pstPppInfo->bSynAsyConvert  = pstCkpPppBkInfo->bSynAsyConvert;
    pstPppInfo->bLoopBacked     = pstCkpPppBkInfo->bLoopBacked;
    pstPppInfo->bLowerIsUp      = pstCkpPppBkInfo->bLowerIsUp;
    pstPppInfo->bIPReleaseFlg   = pstCkpPppBkInfo->bIPReleaseFlg;
    pstPppInfo->bIPTech         = pstCkpPppBkInfo->bIPTech;
    pstPppInfo->bAuthServer     = pstCkpPppBkInfo->bAuthServer;
    pstPppInfo->bAuthClient     = pstCkpPppBkInfo->bAuthClient;
    pstPppInfo->bReNego         = pstCkpPppBkInfo->bReNego;
    pstPppInfo->bReNegoV6       = pstCkpPppBkInfo->bReNegoV6;
    pstPppInfo->bPppStateFlg    = pstCkpPppBkInfo->bPppStateFlg;
    pstPppInfo->bPppMode        = pstCkpPppBkInfo->bPppMode;
    pstPppInfo->bPppClient      = pstCkpPppBkInfo->bPppClient;
    pstPppInfo->bPhaseFlag      = pstCkpPppBkInfo->bPhaseFlag;
    pstPppInfo->bPpcAAAFlag     = pstCkpPppBkInfo->bPpcAAAFlag;
    pstPppInfo->bPppSuccess     = pstCkpPppBkInfo->bPppSuccess;
    pstPppInfo->bAuthFlag       = pstCkpPppBkInfo->bAuthFlag;
    pstPppInfo->bIpcpSucFlag    = pstCkpPppBkInfo->bIpcpSucFlag;
    pstPppInfo->bPppStateFlgV6  = pstCkpPppBkInfo->bPppStateFlgV6;
    pstPppInfo->bRecvLcpMsgFlag = pstCkpPppBkInfo->bRecvLcpMsgFlag;
    //pstPppInfo->bBit328SoftPara = pstCkpPppBkInfo->bBit328SoftPara;
    pstPppInfo->bIpv6cpNoToPDN  = pstCkpPppBkInfo->bIpv6cpNoToPDN;
    pstPppInfo->bIpcpNoToPDN    = pstCkpPppBkInfo->bIpcpNoToPDN;
    pstPppInfo->bEhrpdUser      = pstCkpPppBkInfo->bEhrpdUser;
    pstPppInfo->ulRemoteAccm    = pstCkpPppBkInfo->ulRemoteAccm;
    pstPppInfo->ulLocalAccm     = pstCkpPppBkInfo->ulLocalAccm;
    pstPppInfo->bEAPAuthFlag    = pstCkpPppBkInfo->bEAPAuthFlag;

    pstPppInfo->bIPCPNakHandFlag= pstCkpPppBkInfo->bIPCPNakHandFlag;
    pstPppInfo->ulPcfIP         = pstCkpPppBkInfo->ulPcfIP;
    pstPppInfo->ulIPAddr        = pstCkpPppBkInfo->ulIPAddr;
    pstPppInfo->ulPeerIPAddr    = pstCkpPppBkInfo->ulPeerIPAddr;

    /* ˫ջ����DNS AND POOLNAME ���� */
    pstPppInfo->ulNowUTCInSec      = pstCkpPppBkInfo->ulNowUTCInSec;
    pstPppInfo->usPeerId           = pstCkpPppBkInfo->usPeerId;
    pstPppInfo->ucAAAType          = pstCkpPppBkInfo->ucAAAType;
    pstPppInfo->usCDBIndex         = pstCkpPppBkInfo->usCDBIndex;
    pstPppInfo->usVirtualDomainIdx = pstCkpPppBkInfo->usVirtualDomainIdx;
    pstPppInfo->usMtu              = pstCkpPppBkInfo->usMtu;
    pstPppInfo->usPcfIndex         = pstCkpPppBkInfo->usPcfIndex;

    VOS_MemCpy(pstPppInfo->usIpv6Addr, pstCkpPppBkInfo->usIpv6Addr, sizeof(pstPppInfo->usIpv6Addr));

    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6 )
    {
        VOS_MemCpy(pstPppInfo->usPeerIPv6Addr,
                     pstCkpPppBkInfo->usPeerIPv6Addr, sizeof(pstPppInfo->usPeerIPv6Addr));
    }

    VOS_MemCpy(pstPppInfo->ucNAI, pstRpContext->pucNAI, sizeof(pstPppInfo->ucNAI));

    pstPppInfo->ucServiceOpt   = pstCkpPppBkInfo->ucServiceOpt;
    pstPppInfo->ucFSMFailType  = pstCkpPppBkInfo->ucFSMFailType;
    pstPppInfo->ucDmpuId       = pstCkpPppBkInfo->ucDmpuId;
    pstPppInfo->ucDpeId        = pstCkpPppBkInfo->ucDpeId;
    pstPppInfo->ucIpCapability = pstCkpPppBkInfo->ucIpCapability;

    if (PPP_CB_STATE_USED == pstPppInfo->usState)   /* ��ʾ����PPP���ƿ� */
    {
        PPP_BackupUpdateData(pstPppInfo, pstCkpPppBkInfo);
    }
    else  /* ��ʾ�½�PPP���ƿ� */
    {
        (VOID)PPP_BackupCreateData(pstPppInfo, pstCkpPppBkInfo);
    }

    /* DNS�����ڿ��ƿ������ֵ,�����������.�����֮ǰ��,PPP_BackupCreateData�����ֵ�ɳ�ʼֵ�� */
    pstPppInfo->ulDNSAddr1     = pstCkpPppBkInfo->ulDNSAddr1;
    pstPppInfo->ulDNSAddr2     = pstCkpPppBkInfo->ulDNSAddr2;

    PPP_BackupRestoreCompData(pstPppInfo, pstCkpPppBkInfo);

    return;
}


ULONG PPP_BackupMasterCreUpdPppProc(ULONG ulRpIndex, ULONG ulOperType,
                                                  UCHAR **ppucCurrent, ULONG *pulEncapLen)
{
    ULONG ulRet = 0;
    ULONG ulPdnType = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_106);
#endif
    if (VOS_NULL_PTR == ppucCurrent || VOS_NULL_PTR == *ppucCurrent || VOS_NULL_PTR == pulEncapLen)
    {
        return VOS_ERR;
    }

    /* ��RP������ */
    ulRet = SDB_GetRpContextByIndex(ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_48);
#endif
        return VOS_ERR;
    }

    /* l2tp�û�û��ppp���ƿ� */
    if (VOS_TRUE != pstRpContext->beHRPDMode)
    {
        (VOID)PDN_GetPdnType((ULONG)pstRpContext->ausPdnIndexArray[0], &ulPdnType);
        if (E_PDNTYPE_L2TP == ulPdnType)
        {
            return VOS_OK;
        }
    }

    /* ���� RPIndex ��ȡ PPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        /* ʱ�������п��ܳ��������ĳ�����ֱ�ӷ���OK���� */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_BackupMasterCreUpdPppProc:get ppp cb fail %u", ulRpIndex);
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_49_GetPppNull);
#endif
        return VOS_OK;
    }

    /* ��װCKP_BACKUP_PPPALLINFO_S */
    PPP_BackupEncapUpdatePppInfo(pstPppInfo, ppucCurrent, pulEncapLen);
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_107);
#endif
    return VOS_OK;

}
ULONG PPP_BackupRebuildDynAAACB(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstCkpPppBkInfo)
{
    ULONG ulRet = 0;

    if ((pstCkpPppBkInfo->ucAAAType == pstPppInfo->ucAAAType)
        && (pstCkpPppBkInfo->usPeerId == pstPppInfo->usPeerId))
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_178);
#endif
        return VOS_OK;
    }


    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        /* ɾ���ϵ�hash */
        ulRet = Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex);
        if (ulRet != VOS_OK)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_95);
#endif
            return VOS_ERR;
        }

#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_179);
#endif
    }

    if (M_DIAMAUTH_DYNAAA_AAA == pstCkpPppBkInfo->ucAAAType)
    {
        ulRet = Diam_AUTHBackupRebuildDynAAACB(pstCkpPppBkInfo->usPeerId,
                                               pstCkpPppBkInfo->usDynPeerId,
                                               pstCkpPppBkInfo->aucAAAHost,
                                               pstCkpPppBkInfo->aucAAARealm);
        if (VOS_OK != ulRet)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_96);
#endif
            return VOS_ERR;
        }
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_180);
#endif
    }

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_181);
#endif

    return VOS_OK;
}
ULONG PPP_BackupSlaveCreUpdPppProc(UCHAR *pucCurrent)
{
    ULONG ulRet = 0;
    ULONG ulRpIndex = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    CKP_BACKUP_MSGTLV_HEAD_S *pstMsgTlvHead = VOS_NULL_PTR;

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_108);
#endif

    if (VOS_NULL_PTR == pucCurrent)
    {
        return VOS_ERR;
    }

    pstMsgTlvHead = (CKP_BACKUP_MSGTLV_HEAD_S*)pucCurrent;

    ulRpIndex = pstMsgTlvHead->ulSdbIndex;

    /* ���Ȳ���rp�������Ƿ���ڲ������򴴽�����ֱ�Ӹ��������� */
    ulRet = (ULONG)SDB_GetRpContextByIndex(ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_50);
#endif
        return VOS_ERR;
    }

    if ( ulRpIndex > PPP_MAX_USER_NUM )
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_51);
#endif
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_BackupSlaveCreUpdPppProc:rp index err %u", ulRpIndex);
        return VOS_ERR;
    }

    /* ���� RPIndex ��ȡ PPP���ƿ� */
    pstPppInfo = &g_astPppPool[ulRpIndex];

    if (PPP_CB_STATE_USED != pstPppInfo->usState)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_109);
#endif
        PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;
        pstPppInfo->usPeerId = VOS_NULL_WORD;
    }

    ulRet = PPP_BackupRebuildDynAAACB(pstPppInfo, (CKP_BACKUP_PPPALLINFO_S *)pstMsgTlvHead->ucValue);
    if (ulRet != VOS_OK)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_97);
#endif
        return VOS_ERR;
    }

    /* ���װCKP_BACKUP_PPPALLINFO_S */
    PPP_BackupDecapUpdatePppInfo(pstRpContext, pstPppInfo, pstMsgTlvHead->ucValue);



    pstPppInfo->usState = PPP_CB_STATE_USED;

    return VOS_OK;
}
VOID PPP_BackupSlaveDelResource(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_110);
#endif
    /* ���� RPIndex ��ȡ PPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        return;
    }

    (VOID)PPP_ClearCB(pstPppInfo);

    PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));

    return;
}
ULONG PPP_BackupSmoothPppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext)
{
    ULONG ulPdnType = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_116);
#endif
    /* l2tp�û�û��ppp���ƿ�ֱ�ӷ��سɹ� */
    if (VOS_TRUE != pstRpContext->beHRPDMode)
    {
        (VOID)PDN_GetPdnType((ULONG)pstRpContext->ausPdnIndexArray[0], &ulPdnType);
        if (E_PDNTYPE_L2TP == ulPdnType)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_SUCC_117);
#endif
            return VOS_OK;
        }
    }

    /* ���� RPIndex ��ȡ PPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_262_RP_SMOOTH_PPP_NOT_EXSIT);
#endif
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_BackupSmoothPppInfo: ppp not used %u",
                     pstRpContext->ulRpIndex);
        return VOS_ERR;
    }

    /* �Ƚ�RP�����Ƿ�һ�� */
    if (pstPppInfo->ulRPIndex != pstRpContext->ulRpIndex)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_263_RP_SMOOTH_PPP_RP_NOT_SAME);
#endif
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_BackupSmoothPppInfo: rp not equal %u,%u",
                     pstPppInfo->ulRPIndex, pstRpContext->ulRpIndex);
        return VOS_ERR;
    }

    /* �Ƚ�IMSI�Ƿ�һ�� */
    if (0 != VOS_MemCmp(&pstRpContext->stImsi, &pstPppInfo->stIMSI, sizeof(A11_IMSI_S)))
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_264_RP_SMOOTH_PPP_IMSI_NOT_SAME);
#endif
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_BackupSmoothPppInfo: imsi not equal");
        return VOS_ERR;
    }

    /* ƽ��ѹ���û��� */
    if ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
        && (1 == ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stGotOptions.neg_vj))
    {
        PPP_CompUserNumAdd((PPPINFO_S*)pstPppInfo, PPP_USERSTAT_VJ);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_062);
    }

    if ((VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
        &&(PPPCOMP_MPPC == ((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->ucPppCompType))
    {
        PPP_CompUserNumAdd((PPPINFO_S*)pstPppInfo, PPP_USERSTAT_MPPC);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_063);
    }

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_163);
#endif

    return VOS_OK;
}

VOID PPP_BackupSmoothSubBoardDown()
{
#ifdef __VXWORKS_PLATFORM__
    PPP_SubBoardDown();
#endif
    return;
}
VOID PPP_LI_SetAuInfo(LI_CDMA2000_PDPINFO_S *pstLiContextInfo, ULONG ulRpindex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPPAPINFO_S *pstPapInfo   = VOS_NULL_PTR;
    PPPCHAPINFO_S *pstChapInfo = VOS_NULL_PTR;

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_118);
#endif

    if (VOS_NULL_PTR == pstLiContextInfo)
    {
        return ;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpindex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut((ULONG)FSU_TID_PPPC, 1,
                     "\r\n PPP_LI_SetAuInfo: Find PPP CB is wrong, ulRpIndex:%u", ulRpindex);
        return ;
    }

    pstPapInfo = (PPPPAPINFO_S*)pstPppInfo->pstPapInfo;

    pstChapInfo = (PPPCHAPINFO_S*)pstPppInfo->pstChapInfo;

    /* neither pap nor chap  consider whether return err !!!!!!!!!!!!!!!!!!!!!*/
    if ((!pstPapInfo) && (!pstChapInfo))
    {
        PPP_DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\nPPP PPP_LI_SetAuInfo : auth info err or no auth struct!");
        return ;
    }

    pstLiContextInfo->ucAuFlag = 1;

    if (pstPapInfo)/* if it is pap */
    {
        pstLiContextInfo->ucAuType = AUTH_PAP_PPP;
        pstLiContextInfo->ucSubPasswordLen = (UCHAR)VOS_StrLen((CHAR *)pstPapInfo->szPapUsrPwd);
        VOS_MemCpy((VOID *)pstLiContextInfo->szSubPassword, (VOID *) pstPapInfo->szPapUsrPwd,
                     (ULONG )pstLiContextInfo->ucSubPasswordLen);
    }
    else if (pstChapInfo)/* if it is chap */
    {
        pstLiContextInfo->ucAuType = AUTH_CHAP_PPP;
        pstLiContextInfo->ucChapChallengeLen = pstChapInfo->ucChalLen;
        VOS_MemCpy((VOID *)pstLiContextInfo->szChapChallenge, (VOID *) pstChapInfo->szChallenge,
                     (ULONG )pstChapInfo->ucChalLen);
    }

    return ;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
