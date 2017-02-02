/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_mac.c
*
*  Project Code:
*   Module Name: PTPV2 func
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
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: PTPV2_OverMacRcvPktHookEntry
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: overmac���Ľ�����ڣ��ҽ���ETHARP
*        Input: MBUF_S* pstMBuf:
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
ULONG PTPV2_OverMacRcvPktHookEntry (MBUF_S* pstMBuf)
{
    ULONG ulPktLen = 0;
    ULONG ulRet = 0;
    UINTPTR ulMsg[4] = {0};
    USHORT usEthType = 0;
    USHORT usTPID = 0;
    ULONG ulIfIndex = 0;
    ULONG ulPtpPkt = PTPV2_NO;

    TCPIP_PTPV2_IEEE8023VLAN_HEAD_S* pstEthVlanHeader = NULL;

    VOS_DBGASSERT(NULL != pstMBuf);

    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);/*��ȡ���ĳ���*/

    /*��֤ǰ������(��MBUF_MAKE_MEMORY_CONTINUOUS);*/
    MBUF_MAKE_MEMORY_CONTINUOUS(pstMBuf, ulPktLen, PTPV2_MID, ulRet);
    if (TCPIP_PTP_OK != ulRet || NULL == pstMBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280A, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Make Mbuf continue failed!\n", 0, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR;
        
        goto EXIT_LABEL;
    }

    ulIfIndex = MBUF_GET_RECEIVE_IFNET_INDEX(pstMBuf);/*��ӿ�����*/
    /* ��ȡ��VLAN��Ethͷ(MBUF_MTOD);*/
    pstEthVlanHeader = MBUF_MTOD(pstMBuf, TCPIP_PTPV2_IEEE8023VLAN_HEAD_S*);
    if (NULL == pstEthVlanHeader)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280B, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: mbuf head is NULL(If Index: %#x)!\n", ulIfIndex, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR;
        
        goto EXIT_LABEL;
    }

    usTPID = VOS_NTOHS(pstEthVlanHeader->usTPID);
    usEthType = VOS_NTOHS(pstEthVlanHeader->usPTPType);/* ��ȡETHͷ */

    /* ���usTPID == 0x8100  && usEthType == 0x88F7 ����Я��VLAN ��1588
       ���usTPID == 0x88F7 ���ǲ�Я��vlan��1588����
       ������϶�����1588���ģ�����ԭ�����̴���
    */
    if ((usTPID == PTPV2_IEEE8023_ETHTYPE)
        || (usTPID == VLANTYPE_DOT1Q && PTPV2_IEEE8023_ETHTYPE == usEthType))
    {
        ulPtpPkt  = PTPV2_YES;
    }

    /*��PTP�����򷵻ظ�ETHARP ģ�鴦��*/
    if (PTPV2_NO == ulPtpPkt)
    {
        ulRet = TCPIP_PTP_ERR;
        goto EXIT_LABEL;
    }

    /*����Ϣд�뵽PTP����*/
    ulMsg[0] = PTPV2_IEEE8023_MSG_TYPE;     /*��Ϣ����*/
    ulMsg[1] = (UINTPTR)pstMBuf;             /*��Ϣ���ݵ�ַ*/
    ulMsg[2] = (UINTPTR)ulPktLen;                   /*��Ϣ����*/
    ulMsg[3] = (UINTPTR)ulIfIndex;                  /*��ӿ�����*/

    if (TCPIP_PTP_OK != VOS_Que_Write(g_ulPtpV2PktQId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0))
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280C, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTP LOG: Writer message que failed! \n", 0, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR_WRITE_QUE_FAIL;
        goto EXIT_LABEL;
    }

    /*�¼�ʧ�� ��Ϣ�Ѿ�д�� �����ͷ��ڴ�*/
    if (TCPIP_PTP_OK != VOS_Ev_Write(g_ulPtpV2TaskId, PTPV2_IEEE8023MSG_EVENT_ID))
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280D, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTP LOG: Writer event que failed\n", 0, 0, 0, 0);
    }

    ulRet = TCPIP_PTP_OK;

EXIT_LABEL:
    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPv2_OverMacPktRcvProc
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: MBUF_S* pstMBuf:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_OverMacPktRcvProc(MBUF_S* pstMBuf)
{
    TCPIP_PTP_ADDRINFO_S stAddrInfo;
    ULONG ulRet = TCPIP_PTP_OK;
    TCPIP_PTPV2_IEEE8023VLAN_HEAD_S* pstEthVlanHeader = NULL;
    UCHAR* pBuffer = NULL;
    ULONG ulPktLen = 0;
    ULONG ulIfRcvIndex = 0;
    USHORT usTPID = 0;
    PTPV2_MSGHEADER_S *pstMsgHeader = NULL;
    ULONG ulPtpExactLen = 0;

    if (NULL == pstMBuf)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);    /*��ȡ���ĳ���*/
    ulIfRcvIndex = MBUF_GET_RECEIVE_IFNET_INDEX(pstMBuf);/*��ȡ��ӿ�����*/
    pstEthVlanHeader = MBUF_MTOD(pstMBuf, TCPIP_PTPV2_IEEE8023VLAN_HEAD_S *);

    /*���ȴ�����󳤶ȵı���ֱ�Ӷ���*/
    if (ulPktLen > PTPV2_MAXIMUM_PKT_SIZE)
    {
        ulRet = TCPIP_PTP_ERR_PACKET_LEN;

        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorTotalLenPackets ++;
        
        goto EXIT_LABEL;
    }

    usTPID = VOS_NTOHS(pstEthVlanHeader->usTPID);
    /*��ʱ���Ƚ�VLAN������*/
    if (VLANTYPE_DOT1Q == usTPID)
    {
        /*ɾ������ͷ�е�VLAN�ֶ� */
        TCPIP_Mem_Move((CHAR*)pstEthVlanHeader + DOT1Q_TAG_SIZE, sizeof(*pstEthVlanHeader) - DOT1Q_TAG_SIZE, pstEthVlanHeader, PTPV2_MACADDRLEN * 2);
        MBUF_CUT_HEAD(pstMBuf, DOT1Q_TAG_SIZE);
        ulPktLen -= DOT1Q_TAG_SIZE;
        MBUF_MAKE_MEMORY_CONTINUOUS(pstMBuf, ulPktLen, PTPV2_MID, ulRet);
        if (ulRet != MBUF_OK || pstMBuf == NULL)
        {
            ulRet = TCPIP_PTP_ERR_INVALID_MBUF;

            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2F90, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Make Mbuf continue failed!\n", 0, 0, 0, 0);
            
            goto EXIT_LABEL;
        }
    }

    pBuffer = MBUF_MTOD(pstMBuf, UCHAR*);
    VOS_DBGASSERT(NULL != pBuffer);

    (VOID)TCPIP_Mem_Set((CHAR*)&stAddrInfo, 0, sizeof(TCPIP_PTP_ADDRINFO_S));

    /*��ȡMAC�����Ϣ*/
    /* Ŀ����Ϣ */
    stAddrInfo.stDstPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stDstPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stDstPortAddr.unAddr.ucMacAddr,8, (VOID*)pBuffer, PTPV2_MACADDRLEN);
    /* Դ��Ϣ */
    stAddrInfo.stSrcPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stSrcPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stSrcPortAddr.unAddr.ucMacAddr, 8,(VOID*)((ULONG)pBuffer + PTPV2_MACADDRLEN), PTPV2_MACADDRLEN);
    stAddrInfo.ulIfIndex = ulIfRcvIndex;

    /*ȥ��2�㱨��ͷ������ָ��PTP����λ��*/
    MBUF_CUT_HEAD(pstMBuf, sizeof(TCPIP_PTPV2_IEEE8023_HEAD_S));

    pBuffer = MBUF_MTOD(pstMBuf, UCHAR*);
    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);    /*���»�ȡ���ĳ���*/
    /* ������ݱ�ʵ�ʳ�����ȥ�������;
       ������ݱ�ʵ�ʶ̣���������
    */
    pstMsgHeader = (PTPV2_MSGHEADER_S*)pBuffer;

    /*����ͬ����������*/
    if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber != pstMsgHeader->ucdomainNumber )
    {
       ulRet = TCPIP_PTP_ERR_INVALID_DOMAIN;

       /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorDomainNoPackets ++;
       
       goto EXIT_LABEL;
    }

    ulPtpExactLen = VOS_NTOHS(pstMsgHeader->usmessageLength);
    /*ʵ�����ݹ��̣�����*/
    if (ulPtpExactLen > ulPktLen) 
    {
        ulRet = TCPIP_PTP_ERR_PACKET_LEN;

        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorPtpLenPackets ++;
        
        goto EXIT_LABEL;
    }
    /* ���MBUF�����ݳ����Ƿ����PTP���ĵ��ܳ�������ǣ�Ҫ��ȥ����Ĳ���*/
    else if (ulPtpExactLen < ulPktLen)
    {
        if (MBUF_OK != MBUF_CutTail(pstMBuf,  ulPktLen - ulPtpExactLen))
        {
            ulRet = TCPIP_PTP_ERR_PACKET_LEN;

            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2F92, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Cut Mbuf tail failed!\n", 0, 0, 0, 0);
            
            goto EXIT_LABEL;
        }
    }

    ulRet = PTPV2_GeneralPktProc(pBuffer, ulPktLen, &stAddrInfo);

EXIT_LABEL:
    
    MBUF_Destroy(pstMBuf);
    
    return ulRet;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

