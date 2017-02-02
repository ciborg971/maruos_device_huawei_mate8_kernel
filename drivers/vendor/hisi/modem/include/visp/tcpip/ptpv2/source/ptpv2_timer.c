/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_timer.c
*
*  Project Code:
*   Module Name: PTPV2 timer
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/ptpv2/include/ptpv2_ann.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"

/*******************************************************************************
*    Func Name: PTPV2_CreateLogicTimer
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: ����PTPV2 �߼���ʱ��
*        Input: ULONG ulPeriod:
*               PTPV2_FUNC_LOGIC_TIMER pfFunc:
*               VOID* pArg:
*               ULONG* pulTimerId:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CreateLogicTimer(ULONG ulPeriod, PTPV2_FUNC_LOGIC_TIMER pfFunc, VOID* pArg, ULONG* pulTimerId)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    ULONG ulTime = 0;
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    if (NULL == pfFunc)
    {
        return TCPIP_PTP_ERR_INVALID_PARA;
    }

    /* �ж��߼���ʱ���Ƿ񳬳���� */
    if (g_PtpV2TimerList.u4_Count >= PTPV2_LOGIC_TIMER_MAX_NUM)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280E, TCPIP_LOG_LEVEL_DEBUG, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_CreateLogicTimer failed, up to max!", 0, 0, 0, 0);
        return TCPIP_PTP_ERR_TIMER_NUM_FULL;
    }

    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_TIMER, sizeof(PTPV2_LOGIC_TIMER_S));
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280F, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_CreateLogicTimer Malloc  pstLogicTimer  Failed!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    pstLogicTimer->ulPeriod = ulPeriod;
    pstLogicTimer->pfFunc = pfFunc;
    pstLogicTimer->pArg = pArg;
    pstLogicTimer->ulDelFlag = PTPV2_TIMER_NOT_DELETE;

    /*���ö�ʱ���ڵ��ָ��(��ַ)��ΪTimerId*/
    pstLogicTimer->ulTimerId = (ULONG)pstLogicTimer;
    *pulTimerId = pstLogicTimer->ulTimerId;

    /*��ȡ��ǰʱ�䲢��ֵ����Ӧʱ���ֶ�*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /* �����ʱ����ʱʱ��ulOutTime + ulTimeLowʱ��С��0xFFFFFFFF,
     *�ͱ���ulEndTimeHigh���䣬ֱ����ulEndTimeLow�ϼ���ulOutTime���� */
    ulTime = 0xFFFFFFFF - ulTimeLow;
    if (ulTime >= ulPeriod)
    {
        pstLogicTimer->ulEndTimeLow = ulTimeLow + ulPeriod;
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh;
    }
    /* �����ʱ����ʱ���� + ulTimeLowʱ�����0xFFFFFFFF,
     *ulEndTimeHigh��Ҫ��1����ulEndTimeLow�ϼ������� */
    else
    {
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh + 1;
        pstLogicTimer->ulEndTimeLow = ulPeriod + ulTimeLow;
    }

    DLL_Add(&g_PtpV2TimerList, (DLL_NODE_S*)pstLogicTimer);

    /*��ʱ��Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\ncreate logic timer:");

        PTPV2_TimerPrint(pstLogicTimer);
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_ResetLogicTimer(ULONG ulTimerId)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    ULONG ulTime = 0;
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)ulTimerId;
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2810, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_ResetLogicTimer LogicTimerId is zero!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_LOGIC_TIMERID_NULL;
    }

    /* ��������Ƿ�Ϊ�� */
    if (0 == g_PtpV2TimerList.u4_Count)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2811, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_ResetLogicTimer  There is no timer!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_LOGIC_TIMER_NUM_ZERO;
    }

    /*��ȡ��ǰʱ�䲢��ֵ����Ӧʱ���ֶ�*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /*�����ʱ����ʱ���� + ulTimeLowʱ�䲻����0xFFFFFFFF,
     *ulEndTimeHigh���ֲ��䣬ֱ����ulEndTimeLow�ϼ���ulOutTime����*/
    ulTime = 0xFFFFFFFF - ulTimeLow;
    if (ulTime >= pstLogicTimer->ulPeriod)
    {
        pstLogicTimer->ulEndTimeLow = ulTimeLow + pstLogicTimer->ulPeriod;
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh;
    }
    /*�����ʱ����ʱ���� + ulTimeLowʱ�����0xFFFFFFFF,
     *ulEndTimeHigh��Ҫ��1����ulEndTimeLow�ϼ������� */
    else
    {
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh + 1;
        pstLogicTimer->ulEndTimeLow = pstLogicTimer->ulPeriod + ulTimeLow;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DeleteLogicTimer
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: ɾ��PTP �߼���ʱ��
*        Input: ULONG ulTimerId:��ʱ��Id
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_DeleteLogicTimer(ULONG ulTimerId)
{
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    /*TimerId��Ϊ����Ŀ��ƿ�ָ���ַ������Ϊ��*/
    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)ulTimerId;
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2812, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG:PTPV2_DeleteLogicTimer logicTimerId is not exist!", 0, 0, 0, 0);
        return TCPIP_PTP_ERR_LOGIC_TIMERID_NULL;
    }

    /*��DelFlag����ΪPTPV2_TIMER_DELETE����ʾ����ɾ���ö�ʱ��*/
    pstLogicTimer->ulDelFlag = PTPV2_TIMER_DELETE;

    /*��ʱ��Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\ndelete logic timer:");

        PTPV2_TimerPrint(pstLogicTimer);
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_BaseTimerProc
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2�Ļ���ʱ��
*        Input: VOID* pArg:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_BaseTimerProc(VOID* pArg)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    PTPV2_LOGIC_TIMER_S* pstIter = NULL;
    PTPV2_LOGIC_TIMER_S* pstDelTimer = NULL;
    ULONG ulCount = 0;

    (VOID)pArg;
    /*��ȡ��ǰʱ�䲢��ֵ����Ӧʱ���ֶ�*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /*��������������ô���������*/
    DLL_Scan(&g_PtpV2TimerList, pstIter, PTPV2_LOGIC_TIMER_S*)
    {
        /*ɾ����ʱ��*/
        if(PTPV2_TIMER_DELETE == pstIter->ulDelFlag)
        {
            pstDelTimer = pstIter;
            pstIter = (PTPV2_LOGIC_TIMER_S *)(DLL_Previous(&g_PtpV2TimerList,(DLL_NODE_S *)pstIter));
            DLL_Delete(&g_PtpV2TimerList, (DLL_NODE_S*)pstDelTimer);
            (VOID)TCPIP_Free(pstDelTimer);

            continue;
        }

        if ((pstIter->ulEndTimeHigh < ulTimeHigh) ||
            ((pstIter->ulEndTimeHigh == ulTimeHigh) && (pstIter->ulEndTimeLow <= ulTimeLow)))
        {

            if (( NULL != pstIter->pfFunc ) && (0 != pstIter->ulTimerId))
            {
                (VOID)pstIter->pfFunc(pstIter->pArg);
                ulCount ++;
            }
        }

        /* ÿ����500���ͷ�1ms cpu */
        if (LEN_512 == ulCount)
        {
            ulCount = 0;
            (VOID)VOS_T_Delay(1);
        }

    }

    return;
}

ULONG PTPV2_AnnSndTimerOut(VOID* pArg)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstMBuf = NULL;
    UCHAR ucSrcMacAddr[PTPV2_MACADDRLEN] = {0};
    UCHAR *pucDstMacAddr = NULL;
    /*���ڴ����ȡ������Ϣ��Ŀǰ������ӿ�������Ϣ*/
    TCPIP_PTP_ADDRINFO_S stAddrInfo;
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;

    (VOID)TCPIP_Mem_Set((VOID *)&stAddrInfo, 0, sizeof(TCPIP_PTP_ADDRINFO_S));

    /* �����Ϸ��Լ�� */
    if (NULL == pArg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /*��pArgǿ��ת��PTP PORT*/
    pstPtpPort = (PTPV2_PORT_S*)pArg;

    /*BC�����û������ѡ��ʱ��Դ�������ж˿ڶ�����Ҫ���ͱ���
      Ϊ�˽��͸��Ӷȣ���ʱ������������ʱ�򴴽�
    */
    if (g_ucPtpGotTimeSourceFlag == PTPV2_NO && PTPV2_CLOCK_TYPE_BC == PTPV2_GetClockType())
    {
        return TCPIP_PTP_ERR_NO_TIME_SOURCE;
    }
 

    if (NULL == pstPtpPort->pfPtpBuildAnnPktFunc || NULL == pstPtpPort->pfPtpSndAnnPktFunc)
    {
        return TCPIP_PTP_ERR;
    }

    /*����Э�鴦��������Ann����*/
    ulRet = pstPtpPort->pfPtpBuildAnnPktFunc((VOID *)pstPtpPort,(VOID **)&pstMBuf);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /*����ͳ��*/
    g_stGlobalPtpV2PktStat.ulSndAnnPackets ++;
    pstPtpPort->stPacketStat.ulSndAnnPackets ++;

    /*��ȡ��ַ��Ϣ*/
    /*��ȡĿ�ĵ�ַ*/
    if (TCPIP_PTP_DELAY_MACHENISM_E2E == pstPtpPort->pstSubPortInfo->ucDelayMechanism)
    {
        pucDstMacAddr = (UCHAR *)g_szMacPTPV2_E2E;
    }
    else
    {
        pucDstMacAddr = (UCHAR *)g_szMacPTPV2_P2P;
    }

    /*��ȡԴphysical��ַ*/
    (VOID)TCPIP_GetEtharpMac(pstPtpPort->ulIfIndex, &ucSrcMacAddr[0]);

    /*���ע���˻�ȡ���Ĺ���,����л�ȡ���Ĵ������ڱ��ķ��ͣ������ĳ���*/
    stAddrInfo.ulIfIndex = pstPtpPort->ulIfIndex;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stDstPortAddr.unAddr.ucMacAddr, 8,(VOID*)pucDstMacAddr, PTPV2_MACADDRLEN);
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stSrcPortAddr.unAddr.ucMacAddr, 8,(VOID*)ucSrcMacAddr, PTPV2_MACADDRLEN);
    stAddrInfo.stDstPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stDstPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    stAddrInfo.stSrcPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stSrcPortAddr.usAddressLength   = PTPV2_MACADDRLEN;

    /*Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_OUTPUT)
    {
        PTPV2_ANN_PrintAnn((PTPV2_ANNOUNCE_MSG_S *)pstMBuf->stDataBlockDescriptor.pucData,
                           &stAddrInfo, TCPIP_PTP_PKT_OUT);
    }

    /*����Э�鴦��������Ann����,��������*/
    (VOID)pstPtpPort->pfPtpSndAnnPktFunc(pstPtpPort, pstMBuf, &stAddrInfo);

    /*��ʱ��Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\nsnd timer timeout:");

        pstLogicTimer = (PTPV2_LOGIC_TIMER_S *)(pstPtpPort->pstSubPortInfo->ulAnnSndTimerId);

        PTPV2_TimerPrint(pstLogicTimer);
    }

    /*����Ann���Ͷ�ʱ��*/
    ulRet = PTPV2_ResetLogicTimer(pstPtpPort->pstSubPortInfo->ulAnnSndTimerId);

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_AnnRcvTimerOut
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:  announce���ն�ʱ��������
*        Input: VOID* pArg:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AnnRcvTimerOut(VOID* pArg)
{
    PTPV2_PORT_S *pstPtpPort = NULL;
    PTPV2_FOREIGN_MASTER_S *pstForeign = NULL;
    PTPV2_FOREIGN_MASTER_S *pstSelectMaster = NULL;
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;

    if (NULL == pArg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstForeign = (PTPV2_FOREIGN_MASTER_S *)pArg;
    pstPtpPort = pstForeign->pstPortInfo;

    /*PTP �˿�����Ϊ�գ�˵��ϵͳ�����쳣*/
    if (NULL == pstPtpPort || NULL == pstPtpPort->pstSubPortInfo)
    {
        VOS_DBGASSERT(NULL != pstPtpPort);
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /* Ann���ռ�����++ */
    pstForeign->ulAnnRcvTimerCount ++;

    /*��ʱ��������
      ɾ������ʱ��Դ & ������ѡһ��Դ
    */
    if (pstForeign->ulAnnRcvTimerCount >= pstPtpPort->pstSubPortInfo->stPortAnnInfo.ucAnnRcvTimeoutNum)
    {
        /*ɾ������ʱ��Դ*/
        (VOID)PTPV2_DelForeignMaster(pstForeign);

        /*����ѡԴ*/
        (VOID)PTPV2_BMCProcess(&pstSelectMaster);

        /*ѡԴ�������²���*/
        (VOID)PTPV2_BMCNotify(pstSelectMaster);

        return TCPIP_PTP_OK;
    }

    /*��ʱ��Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\nrcv timer timeout:");

        pstLogicTimer = (PTPV2_LOGIC_TIMER_S *)(pstForeign->ulAnnRcvTimerId);

        PTPV2_TimerPrint(pstLogicTimer);
    }

    ulRet = PTPV2_ResetLogicTimer(pstForeign->ulAnnRcvTimerId);

    return ulRet;
}

/*
�澯����:
1. �ڵ�һ������PTP ��Ҫ�����澯��ʱ��,��ʱ����ʱ���ж��Ƿ���ѡ�е�ʱ��Դ��
   û��ѡ�е�ʱ��Դ�����ϱ��澯
2. ѡ��ʱ��Դ���·�ADD ������Ҫȡ���澯����
3. ж��PTPv2 ģ�飬��Ҫȡ���澯����
*/
VOID PTPV2_WarningTimerProc(ULONG ulOperType)
{
    TCPIP_PTP_WARN_PARAM_S  stPtpWarnPara = {0};

    if (NULL != g_pfPtpV2WarnOutput && PTPV2_NO == PTPV2_HaveParent())/*û��ѡ��Դ�����ϱ��澯*/
    {
        /*�ϱ�ѡԴʧ�ܸ澯*/
        stPtpWarnPara.ucWarnType = TCPIP_PTP_WARN_BMC_FAIL;
        stPtpWarnPara.ucWarnState = TCPIP_PTP_WARNING_BEGIN;

        (VOID)g_pfPtpV2WarnOutput(&stPtpWarnPara);
        g_pstPtpGlobalInfo->usWarningRecord |= TCPIP_PTP_WARN_BMC_FAIL_FLAG;
    }

    /*һ���Ը澯��ʱ������ʱ��ɾ����Id����*/
    g_ulPtpWarningTimerId = 0;

    return;
}

ULONG PTPV2_CreateWarningTimer()
{
    if (0 != g_ulPtpWarningTimerId)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2813, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
            "TCPIP PTPV2 LOG: PTPV2_CreateWarningTimer  warning timer id = %#x exist.\r\n",
            g_ulPtpWarningTimerId, 0, 0, 0);
    }

    /*һ���Զ�ʱ����30���жϵ�ǰ��û��Դ��û��Դ�ϱ��澯����Դ����������*/
    if (TCPIP_PTP_OK != VOS_Timer_Create(g_ulPtpV2TaskId,
                                         g_ulPtpV2TimerQId,
                                         PTPV2_WANRING_TIMER_INTERVAL,
                                         (VOID  (*)(VOID*))PTPV2_WarningTimerProc,
                                         (VOID*)0,
                                         &g_ulPtpWarningTimerId,
                                         VOS_TIMER_NOLOOP))
    {

        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2814, TCPIP_LOG_LEVEL_CRITICAL,
            LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_CreateWarningTimer Create warning timer failed.\r\n",
            0, 0, 0, 0);

        return TCPIP_PTP_ERR_CREATE_TIMER;
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_DeleteWarningTimer()
{
   if (0 != g_ulPtpWarningTimerId)
   {
        (VOID)VOS_Timer_Delete(g_ulPtpWarningTimerId);
        g_ulPtpWarningTimerId = 0;
   }

   return TCPIP_PTP_OK;
}

/******************************************************************************
*Func Name   : PTPV2_TimerPrint
*Description : ��ʱ����Ϣ��ӡ�ӿ�
*Input       : PTPV2_LOGIC_TIMER_S *pstLogicTimer 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-05-14           dutianyi       Create
*******************************************************************************/
VOID PTPV2_TimerPrint(PTPV2_LOGIC_TIMER_S *pstLogicTimer)
{
    CHAR szBuf[LEN_512] = {0};      /* ����������512���ֽڣ���ű�����Ϣ */
    INT32 i32Offset = 0;

    if (NULL == pstLogicTimer)
    {
        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P8("\r\n %30s : %#x \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                             "TimerId", pstLogicTimer->ulTimerId,
                             "Period", pstLogicTimer->ulPeriod,
                             "EndTimeHigh", pstLogicTimer->ulEndTimeHigh,
                             "EndTimeLow", pstLogicTimer->ulEndTimeLow));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                                P4("\r\n %30s : %#x \r\n %30s : %u \r\n",
                                "Func", pstLogicTimer->pfFunc,
                                "DelFlag", pstLogicTimer->ulDelFlag));

    TCPIP_InfoOutput(szBuf);

    return;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

