/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_pkt.c
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

#include "vos/vospubh/iunknown.h"

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_ann.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "ifnet/core/include/if_func.h"
#include "tcpip/trunk/include/trunk_inc.h"

extern struct IIF_COMP_TRUNK_ComIntFUNVtbl* g_pstIfTRUNKFunVtbl;

ULONG PTPV2_PktWithCastModeMatch(PTPV2_PORT_S *pstPortInfo, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{
    /*�������ͺ� PTP�˿����õĵ���/�ಥ/overmacģʽ�Ƿ�ƥ�䣬��ƥ������*/
    /*Ŀǰֻ��overmac*/
    if (TCPIP_PTP_CLOCK_IEEE8023_MODE != pstPortInfo->pstSubPortInfo->ucCastMode)
    {
        return TCPIP_PTP_ERR_CAST_MODE;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_GeneralPktProc
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UCHAR* pBuffer:
*               ULONG ulPacketLen:
*               TCPIP_PTP_ADDRINFO_S *pstAddrInfo:
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
ULONG PTPV2_GeneralPktProc(UCHAR* pBuffer, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{
    PTPV2_MSGHEADER_S* pstMsgHeader = NULL;
    ULONG ulRet      = TCPIP_PTP_OK;
    PTPV2_PORT_S *pstPortInfo = NULL;
    TCPIP_PTP_ADDRINFO_S stAddrInfo = { { 0 } };
    
    /* �����Ϸ��Լ�� */
    VOS_DBGASSERT(NULL != pBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    (VOID)TCPIP_Mem_Copy(&stAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S), pstAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S));

    /*���ע���˻�ȡ���Ĺ���,����л�ȡ���Ĵ������ڱ��ķ��ͣ������ĳ���*/
    /*Ŀǰ������ӿ�������Ϣ*/
    
    /*��ȡPTP�˿���Ϣ */
    ulRet = PTPV2_GetPortInfo(&stAddrInfo, &pstPortInfo);
    /*ĿǰBCӦ���У�Hertʱ�����ǻ�������˿�����PTP���ܵģ���ʵ��������
        �˿���Trunk�ĳ�Ա�˿ڡ������������Trunk�˿�����PTP��������ӿ���Ȼ
        ������˿ڣ����¸�������˿��޷�ƥ�䵽PTP�����ö˿���Ϣ�������ڵ�
        һ��ͨ������˿ڲ���ʧ�ܺ��ٴ�ͨ��Trunk�˿ڽ��в��ҡ�*/
    if (TCPIP_PTP_OK != ulRet)
    {
        ULONG ulTrunkIfIndex = 0;
        
        if ((NULL != g_pstIfTRUNKFunVtbl)
            && (g_pstIfTRUNKFunVtbl->pfTRUNK_IsTrunkPort(IF_GetIfByIndex(stAddrInfo.ulIfIndex))))
        {
            if (TCPIP_PTP_OK == g_pstIfTRUNKFunVtbl->pfTRUNK_GetTrunkIfByPortIf(
                                            stAddrInfo.ulIfIndex, &ulTrunkIfIndex))
            {
                /*���ӿ������ĳ�trunk�Ľӿ�����*/
                stAddrInfo.ulIfIndex = ulTrunkIfIndex;
                ulRet =  PTPV2_GetPortInfo(&stAddrInfo, &pstPortInfo);
            }
        }        
    }
    
    if (TCPIP_PTP_OK != ulRet)
    {
        /*������ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorAddrPackets ++;

        return ulRet;
    }

    /*��ȡ���Ļص�����*/
    if (NULL != g_pfPtpV2CapturePktFunc)
    {
        (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_IN, pBuffer, ulPacketLen, &stAddrInfo,
                                      pstPortInfo->pstSubPortInfo->usPortNo);
    }

    /*Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_INPUT)
    {
        PTPV2_ANN_PrintAnn((PTPV2_ANNOUNCE_MSG_S *)pBuffer, &stAddrInfo, TCPIP_PTP_PKT_IN);
    }

    pstMsgHeader = (PTPV2_MSGHEADER_S *)pBuffer;

    /* ���ݲ�ͬ�ı������ͣ����ɲ�ͬ�Ĵ��������� */
    switch (pstMsgHeader->ucmessageType)
    {
        case TCPIP_PTP_MSG_ANNOUNCE:  /* ANNOUNCE��Ϣ */
            ulRet = PTPV2_Ann_RcvMsg(pBuffer, ulPacketLen, &stAddrInfo, pstPortInfo);
            break;
        default:
            ulRet = TCPIP_PTP_ERR_MSGTYPE;
            break;
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_PktAnnSequenceIdCheck
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
 *  Description: announce�������кż��
*        Input: PTPV2_PORT_S *pstPtpPort:
*               PTPV2_MSGHEADER_S* pstMsgHeader:
*               TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo:
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
ULONG PTPV2_PktAnnSequenceIdCheck(PTPV2_PORT_S *pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo)
{
    ULONG ulRet   = TCPIP_PTP_OK;
    USHORT usNextSequenceId = 0; /* ��������һ�����ĵ����к� */
    PTPV2_FOREIGN_MASTER_S *pstFindMaster = NULL;
    USHORT usSequenceId = 0;

    VOS_DBGASSERT(NULL != pstPortAddrInfo);
    VOS_DBGASSERT(NULL != pstPtpPort);

    ulRet = PTPV2_GetForeignMasterByPortId(pstMsgHeader, &pstFindMaster);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*�Ҳ��������ǵ�һ���յ����ģ�������ͨ�����*/
        return TCPIP_PTP_OK;
    }

    /*��ȡannounce���ĵ����к�*/
    usSequenceId = VOS_NTOHS(pstMsgHeader->usSequenceId);

    usNextSequenceId = pstFindMaster->usRcvAnnSequenceId + 1;
    if (0 != PTPV2_PktCircularSpaceCmp(usNextSequenceId, usSequenceId, 0x8000))
    {
        if (usNextSequenceId > usSequenceId)
        {
           /*����ͳ��*/
           g_stGlobalPtpV2PktStat.ulRcvErrorSeqIdPackets ++;
           return TCPIP_PTP_ERR_SEQUENCEID;
        }

        /* ���յ����ĵ�sequnce id����Ԥ�ڵı����������һ����˵����;��·�ж����������� */
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorUnexpectedSeqIdPackets ++;
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_PktFlagfieldCheck(PTPV2_PORT_S *pstPtpPort, CHAR *pcFlagfield, ULONG ulMsgType)
{
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pcFlagfield);

    if((NULL == pstPtpPort) || (NULL == pcFlagfield))
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* ��һ���ֽ���ȷ�Լ�� */
    /* flag���һ���ֽڵĵ���λ�ǵ��ಥ��� */
    /*Ŀǰ��֧�ֶ���*/
    if (TCPIP_PTP_CLOCK_IEEE8023_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        if (0 != (((*pcFlagfield) >> 2) & 0x01))
        {
            return TCPIP_PTP_ERR_UNICASTFLAG;
        }
    }

    return TCPIP_PTP_OK;

}


/******************************************************************************
*Func Name   : PTPV2_PktGeneralHeaderCheck
*Description : PTP��Ϣͷͨ����Ϸ��Լ�⣬��PTP_PKT_HeaderCheck����
*Input       : PTP_PORT_S       *pstPtpPort   ʱ�Ӷ˿ڿ��ƿ�ָ��
*              PTP_MSGHEADER_S  *pstMsgHeader ��Ϣͷ
*              ULONG            ulPtpMsgType  ��Ϣ����
*              ULONG            ulPacketLen   ���ĳ���
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-5             wangchengyang  Create
*******************************************************************************/
ULONG PTPV2_PktGeneralHeaderCheck(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType, ULONG ulPacketLen)
{
    ULONG ulRet      = TCPIP_PTP_OK;

    if (pstMsgHeader->ucversionPTP != PTPV2_VERSION)
    {
        /*log*/
        return TCPIP_PTP_ERR_VERSION;
    }


    /* flagfield��Ϸ��Լ�� */
    ulRet = PTPV2_PktFlagfieldCheck(pstPtpPort, (CHAR*)(pstMsgHeader->ucflagField), ulPtpMsgType);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*log*/
        return ulRet;
    }

    /*Э��һ���Լ���Ż�*/
    if (PTPV2_CONTROLFIELD_ALL_OTHER != pstMsgHeader->ucControlField)
    {
        /*log*/
        return TCPIP_PTP_ERR_PACKET;
    }

    return TCPIP_PTP_OK;

}

ULONG PTPV2_BCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType)
{
    PTPV2_FOREIGN_MASTER_S *pstBMCParent = g_pstBmcEbest;

    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pstMsgHeader);

    if ((NULL == pstPtpPort) || (NULL == pstMsgHeader) )
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* flag���һ���ֽڵĵ���λ�ǵ��ಥ��� */
    if (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        pstMsgHeader->ucflagField[0] |= 0x04;
    }
    else
    {
        pstMsgHeader->ucflagField[0] &= 0xFB;
    }

    /*���ֶ��޸���Ҫ�����ϰ汾���ϰ汾��Slave��Ը��ֶ������*/
    /* If the port is transmitting a unicast Announce message
    under the terms of this subclause and is in the MASTER state,
    set  the flagField.alternateMasterFlag to FALSE,
    otherwise set the flagField.alternateMasterFlag to TRUE. */
    /*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
    /*����G.8265.1�й涨annouce��signing���ĵ�alternateMasterFlag�ֶζ�ӦΪFALSE*/
    pstMsgHeader->ucflagField[0] &= 0xFE;

    /* �ڶ����ֽ���� */
    if (TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
    {
        if (pstBMCParent != NULL)
        {
            pstMsgHeader->ucflagField[1] = pstBMCParent->ucFlagField[1];
        }
        else
        {
            /*��ǰû��ѡ��Դ��ʱ���������ParentDs��Ϣ���flagField�ֶ�*/
            pstMsgHeader->ucflagField[1] = 0;
            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bLeap61)
            {
                pstMsgHeader->ucflagField[1] |= 0x01;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bLeap59)
            {
                pstMsgHeader->ucflagField[1] |= 0x02;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bCurrentUtcOffsetValid)
            {
                pstMsgHeader->ucflagField[1] |= 0x04;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bPtpTimescale)
            {
                pstMsgHeader->ucflagField[1] |= 0x08;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bTimeTraceable)
            {
                pstMsgHeader->ucflagField[1] |= 0x10;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bFrequencyTraceable)
            {
                pstMsgHeader->ucflagField[1] |= 0x20;
            }
        }
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_OCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType)
{
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pstMsgHeader);

    if ((NULL == pstPtpPort) || (NULL == pstMsgHeader) )
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* flag���һ���ֽڵĵ���λ�ǵ��ಥ��� */
    if (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        pstMsgHeader->ucflagField[0] |= 0x04;
    }
    else
    {
        pstMsgHeader->ucflagField[0] &= 0xFB;
    }

    /*IEEE Std 1588 17.3
      If the port is transmitting a unicast Announce message
    under the terms of this subclause and is in the MASTER state,
    set  the flagField.alternateMasterFlag to FALSE,
    otherwise set the flagField.alternateMasterFlag to TRUE. */
    if ((TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
        && (TCPIP_PTP_PORT_ROLE_MASTER == pstPtpPort->pstSubPortInfo->ucPtpPortRole)
        && (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode))
    {
        pstMsgHeader->ucflagField[0] &= 0xFE;
    }
    else
    {
        pstMsgHeader->ucflagField[0] |= 0x01;
    }

    /* �ڶ����ֽ���� */
    if (TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
    {
        pstMsgHeader->ucflagField[1] = 0;
        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap61)
        {
            pstMsgHeader->ucflagField[1] |= 0x01;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap59)
        {
            pstMsgHeader->ucflagField[1] |= 0x02;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid)
        {
            pstMsgHeader->ucflagField[1] |= 0x04;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bPtpTimescale)
        {
            pstMsgHeader->ucflagField[1] |= 0x08;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bTimeTraceable)
        {
            pstMsgHeader->ucflagField[1] |= 0x10;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bFrequencyTraceable)
        {
            pstMsgHeader->ucflagField[1] |= 0x20;
        }

    }

    return TCPIP_PTP_OK;
}
/*
   Bits                                  Octets  Offset
   7     6     5     4   3   2   1   0
   |transportSpecific|  messageType  |     1       0
   |    reserved     |  versionPTP   |     1       1
   |           messageLength         |     2       2
   |           domainNumber          |     1       4
   |           reserved              |     1       5
   |           flagField             |     2       6
   |           correctionField       |     8       8
   |           reserved              |     4       16
   |           sourcePortIdentity    |     10      20
   |           sequenceId            |     2       30
   |           controlField          |     1       32
   |           logMessageInterval    |     1       33
*/
ULONG PTPV2_PktHeaderCheck(PTPV2_PORT_S* pstPtpPort,
                          UCHAR *pucBuffer,
                          ULONG ulPtpMsgType,
                          ULONG ulPacketLen,
                          TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    PTPV2_MSGHEADER_S* pstMsgHeader = NULL;
    ULONG  ulRet = TCPIP_PTP_OK;
    LONG lCmp = -1;

    /* �������ڲ�������ָ�벻����Ϊ�� */
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pucBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    if (NULL == g_pstPtpGlobalInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }
    pstMsgHeader = (PTPV2_MSGHEADER_S *)pucBuffer;

    /*PTP �˿ںŲ���Ϊ0��0xffff*/
    if (0 == pstMsgHeader->stSourcePortIdentity.usPortNumber
        || 0xFFFF == pstMsgHeader->stSourcePortIdentity.usPortNumber)
    {
        return TCPIP_PTP_ERR_PORTNO;
    }

    /*�Զ˵�Clock Id ���ܺͱ�����ͬ*/
    (VOID)VOS_Mem_Cmp(g_pstPtpGlobalInfo->szClockId,
        pstMsgHeader->stSourcePortIdentity.szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ), &lCmp);
    if (0 == lCmp)
    {
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorClockIdPackets ++;

        return TCPIP_PTP_ERR_CLOCKID;
    }

    ulRet =  PTPV2_PktGeneralHeaderCheck (pstPtpPort, pstMsgHeader, ulPtpMsgType, ulPacketLen);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /* ������Ҫ�����Ϣ���ͽ������֣���ֿ���� */
    switch (ulPtpMsgType)
    {
        case TCPIP_PTP_MSG_ANNOUNCE:
            ulRet = PTPV2_PktAnnSequenceIdCheck(pstPtpPort, pstMsgHeader, pstAddrInfo);

            break;

        default:
            ulRet = TCPIP_PTP_ERR_MSGTYPE;
            break;

    }

    return ulRet;
}

ULONG PTPV2_BuildAnnPktHeader(PTPV2_PORT_S* pstPtpPort,  PTPV2_MSGHEADER_S* pstMsgHeader)
{
    /* header��ǵ�Ҫ��������ת���������� */
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_SUB_INFO_S *pstPortSubInfo = NULL;
    ULONG ulPtpV2ClockType = 0;

    /* �������ڲ�������ָ�벻����Ϊ�� */
    VOS_DBGASSERT(NULL != pstPtpPort);

    pstPortSubInfo = pstPtpPort->pstSubPortInfo;
    VOS_DBGASSERT(NULL != pstPtpPort->pstSubPortInfo);
    if (NULL == pstPortSubInfo)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    ulPtpV2ClockType = PTPV2_GetClockType();

    pstMsgHeader->usSequenceId = VOS_HTONS(pstPortSubInfo->stPortAnnInfo.usSndAnnSequenceId);
    pstPortSubInfo->stPortAnnInfo.usSndAnnSequenceId ++;
    pstMsgHeader->cLogMessageInterval = pstPortSubInfo->stPortAnnInfo.clogAnnounceInterval;

    /* ��������������ͨ�ֶ� */
    pstMsgHeader->ucversionPTP = PTPV2_VERSION;
    pstMsgHeader->ucdomainNumber = g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber;
    pstMsgHeader->ucControlField = PTPV2_CONTROLFIELD_ALL_OTHER;
    pstMsgHeader->ucmessageType = (UCHAR)TCPIP_PTP_MSG_ANNOUNCE;

    pstMsgHeader->uctransportSpecific = 0;
    (VOID)TCPIP_Mem_Copy(pstMsgHeader->stSourcePortIdentity.szClockId,sizeof(TCPIP_PTP_CLOCK_ID_SZ), g_pstPtpGlobalInfo->szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ));
    pstMsgHeader->stSourcePortIdentity.usPortNumber = VOS_HTONS(pstPortSubInfo->usPortNo);
    if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        (VOID)PTPV2_OCBuildPktFlagfield(pstPtpPort, pstMsgHeader, TCPIP_PTP_MSG_ANNOUNCE);
    }
    else
    {
        (VOID)PTPV2_BCBuildPktFlagfield(pstPtpPort, pstMsgHeader, TCPIP_PTP_MSG_ANNOUNCE);
    }
    return ulRet;

}

ULONG PTPV2_ComputeSeqId(VOID *pThis, MBUF_S *pstMbuf)
{
    return TCPIP_PTP_OK;
}

ULONG PTPV2_OverMacSndAnnPkt(VOID *pThis, VOID *pData, VOID *pAddr)
{
    MBUF_S *pstMbuf = NULL;
    USHORT usEthType = 0;
    ULONG  ulRet = TCPIP_PTP_OK;
    IFNET_S *pstIfnet = NULL;
    ETHARP_ETHERHDR_S *pstEthHdr = NULL;
    PTPV2_PORT_S *pstPortInfo = NULL;
    ULONG ulLength = sizeof(ETHARP_ETHERHDR_S);
    MBUF_S *pstMultiPortMbuf = NULL;
    PTPV2_PORT_S *pstMultiPortInfo = NULL;
    IFNET_S *pstMultiPortIfnet = NULL;
    ULONG ulIter = 0;
    /*���ڴ����ȡ������Ϣ��Ŀǰ������ӿ�������Ϣ*/
    TCPIP_PTP_ADDRINFO_S *pstAddrInfo;
    TCPIP_PTP_ADDRINFO_S stMultiPortAddrInfo = {{0}};

    if (NULL == pThis || NULL == pData || NULL == pAddr)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstPortInfo = (PTPV2_PORT_S *)pThis;
    pstMbuf = (MBUF_S *)pData;
    pstAddrInfo = (TCPIP_PTP_ADDRINFO_S *)pAddr;

    pstIfnet = IF_GetIfByIndex(pstAddrInfo->ulIfIndex);
    if (NULL == pstIfnet)
    {
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulSndGetIfDropPackets ++;
        pstPortInfo->stPacketStat.ulSndGetIfDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281B, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt fail to get Ifnet!\r\n",
                0, 0, 0, 0);
        
        MBUF_Destroy(pstMbuf);
        
        return TCPIP_PTP_ERR;
    }

    pstMbuf->stDataBlockDescriptor.pucData -= ulLength;
    pstMbuf->stDataBlockDescriptor.ulDataLength += ulLength;
    pstMbuf->ulTotalDataLength += ulLength;
    pstEthHdr = MBUF_MTOD(pstMbuf, ETHARP_ETHERHDR_S*);

    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrDstMacAddr,PTPV2_MACADDRLEN, pstAddrInfo->stDstPortAddr.unAddr.ucMacAddr, PTPV2_MACADDRLEN);
    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrSrcMacAddr, PTPV2_MACADDRLEN,pstAddrInfo->stSrcPortAddr.unAddr.ucMacAddr, PTPV2_MACADDRLEN);

    usEthType = PTPV2_IEEE8023_ETHTYPE;
    pstEthHdr->usHdrType = VOS_HTONS(usEthType);

    /*OC master�£��������е�����ӿڶ�����һ�ݱ��Ľ��з���*/
    if (PTPV2_CLOCK_TYPE_OC == g_ulPtpV2ClockType)
    {
        (VOID)TCPIP_Mem_Copy((VOID *)&stMultiPortAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S), 
                             (VOID *)pstAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S));
        
        for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
        {
            pstMultiPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);
            if (NULL == pstMultiPortInfo)
            {
                continue;
            }

            pstMultiPortIfnet = IF_GetIfByIndex(pstMultiPortInfo->ulIfIndex);
            /* �����ĸ��Ʋ�ͨ�����������õĽӿڽ��з��� */
            /* Ϊ�����ظ����ͣ���ʱ���ų���ԭ���ķ��ͽӿ� */
            if (pstIfnet != pstMultiPortIfnet && NULL != pstMultiPortIfnet)
            {
                pstMultiPortMbuf = MBUF_RawCopy(pstMbuf, 0, pstMbuf->ulTotalDataLength,
                                            0, PTPV2_MID);
                if (NULL == pstMultiPortMbuf)
                {
                    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281C, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                                     "TCPIP PTPV2 LOG:PTPV2_OverMacSndAnnPkt Create mbuf fail!\n",0,0,0,0);
                }
                else
                {
                    UCHAR ucSrcMacAddr[PTPV2_MACADDRLEN] = {0};
                    /* �����ӿ���������MBuf��ʹ�������� */
                    MBUF_ASSIGN_SEND_IFNET_INDEX(pstMultiPortMbuf, pstMultiPortInfo->ulIfIndex);

                    /*���ݺͲ�Ʒ�����·���,��Բ�ͬ�Ľӿ���д��ͬ��ԴMAC
                                ������MASTER �������ӿڸ��Զ�slave���ͱ��ģ�����slave��ȡ��master
                                Դphysical��ַ��ͬ���·�������ʱ���鲻�ܻ���ԴMAC����*/
                    pstEthHdr = MBUF_MTOD(pstMultiPortMbuf, ETHARP_ETHERHDR_S*);
                    (VOID)TCPIP_GetEtharpMac(pstMultiPortInfo->ulIfIndex, ucSrcMacAddr);
                    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrSrcMacAddr, PTPV2_MACADDRLEN, ucSrcMacAddr, PTPV2_MACADDRLEN);
                    
                    {
                        ULONG ulPtpPktLen = pstMultiPortMbuf->ulTotalDataLength - ulLength;
                        UCHAR *pucPtpPkt  = MBUF_MTOD(pstMultiPortMbuf, UCHAR*);
                        
                        pucPtpPkt += ulLength;
                        /*�����ص�������Դ��ַ��ϢҪ���³ɷ��Ͷ˿ڵ�MAC*/
                        stMultiPortAddrInfo.ulIfIndex = pstMultiPortInfo->ulIfIndex;
                        (VOID)TCPIP_Mem_Copy((VOID *)(stMultiPortAddrInfo.stSrcPortAddr.unAddr.ucMacAddr), PTPV2_MACADDRLEN,
                                             (VOID *)ucSrcMacAddr, PTPV2_MACADDRLEN);
                        if (NULL != g_pfPtpV2CapturePktFunc)
                        {
                            (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_OUT, pucPtpPkt, 
                                    ulPtpPktLen, &stMultiPortAddrInfo, pstMultiPortInfo->pstSubPortInfo->usPortNo);
                        }
                    }
                    /*End of adding*/

                    /* �����Ľ�����·�㷢�� */
                    ulRet = pstMultiPortIfnet->if_pfQosTransmit(pstMultiPortIfnet, pstMultiPortIfnet->if_ulPhyLink, pstMultiPortMbuf);
                    if (TCPIP_PTP_OK != ulRet)
                    {
                        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281D, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt multi port QosTransmit fail! Ret = %u!\r\n",
                                ulRet, 0, 0, 0);
                    }
                }
            }
        }
    }

    {
        ULONG ulPtpPktLen = pstMbuf->ulTotalDataLength - ulLength;
        UCHAR *pucPtpPkt  = MBUF_MTOD(pstMbuf, UCHAR*);

        pucPtpPkt += ulLength;        
        if (NULL != g_pfPtpV2CapturePktFunc)
        {
            (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_OUT, pucPtpPkt, 
                        ulPtpPktLen, pstAddrInfo, pstPortInfo->pstSubPortInfo->usPortNo);
        }
    }
    /*End of adding*/

    ulRet = pstIfnet->if_pfQosTransmit(pstIfnet, pstIfnet->if_ulPhyLink, pstMbuf);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulSndDropPackets ++;
        pstPortInfo->stPacketStat.ulSndDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281E, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt QosTransmit fail! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
    }

    return ulRet;
}
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
/******************************************************************************
*Func Name   : PTPV2_PrintHeader
*Description : ����ͷ��ӡ�ӿ�
*Input       : PTP_MSGHEADER_S *pstMsgHeader ��Ϣͷ
*              PTP_ADDRINFO_S  *pstAddrInfo  ����/���ͱ��ĵĵ�ַ�Լ�UDP��Ϣ
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
VOID PTPV2_PrintHeader(PTPV2_MSGHEADER_S *pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{

    CHAR szBuf[1024] = {0};  /* ����������512���ֽڣ���ű�����Ϣ */
    //CHAR szDstAddr[256] = {0}; /* ����������32���ֽڣ�����Ŀ�ĵ�ַ�ַ��� */
    //CHAR szSrcAddr[256] = {0}; /* ����������32���ֽڣ�����Դ��ַ�ַ��� */
    /* ʱ�������Ϣ*/
    ULONG ulSysDate = 0; 
    ULONG ulSysTime = 0;
    ULONG ulSysMillSec = 0;
    ULONG ulHour = 0;
    ULONG ulMinute = 0;
    ULONG ulSecond = 0;
    CHAR *szMsgtype[]  = {
                          "PTPV2_MSG_SYNC",
                          "PTPV2_MSG_DELAY_REQ",
                          "PTPV2_MSG_PDELAY_REQ",
                          "PTPV2_MSG_PDELAY_RESP",
                          "",
                          "",
                          "",
                          "PTPV2_MSG_LIVE",
                          "PTPV2_MSG_FOLLOW_UP",
                          "PTPV2_MSG_DELAY_RESP",
                          "PTPV2_MSG_PDELAY_RESP_FOLLOW_UP",
                          "PTPV2_MSG_ANNOUNCE",
                          "PTPV2_MSG_SIGNALING",
                          "PTPV2_MSG_MANAGEMENT",
                          "PTPV2_MSG_HANDSHAKE_REQ",
                          "PTPV2_MSG_HANDSHAKE_RESP"
                          };
    INT32 i32Offset = 0;

    if ((NULL == pstMsgHeader)
        || (NULL == pstAddrInfo))
    {
        return ;
    }
    
    if ((pstAddrInfo->stDstPortAddr.usNetworkProtocol < TCPIP_PTP_PROTOCAL_UDP_IPV4)
        || (pstAddrInfo->stDstPortAddr.usNetworkProtocol > TCPIP_PTP_PROTOCAL_IEEE_802)
        || (pstAddrInfo->stSrcPortAddr.usNetworkProtocol < TCPIP_PTP_PROTOCAL_UDP_IPV4)
        || (pstAddrInfo->stSrcPortAddr.usNetworkProtocol > TCPIP_PTP_PROTOCAL_IEEE_802))
    {
        return;
    }
    
    /*
       Bits                                  Octets  Offset
       7     6     5     4   3   2   1   0
       |transportSpecific|  messageType  |     1       0
       |    reserved     |  versionPTP   |     1       1
       |           messageLength         |     2       2
       |           domainNumber          |     1       4
       |           reserved              |     1       5
       |           flagField             |     2       6
       |           correctionField       |     8       8
       |           reserved              |     4       16
       |           sourcePortIdentity    |     10      20
       |           sequenceId            |     2       30
       |           controlField          |     1       32
       |           logMessageInterval    |     1       33

    */

    /* ��ȡ��ǰʱ�� */
    if (VOS_OK == VOS_SYS_GetCurrentTime(&ulSysDate, &ulSysTime, &ulSysMillSec))
    {
        /*
        -------------------------------------------------------
        |  Hours(16 bits) | Minutes(8 bits) | Seconds(8 bits) |
        -------------------------------------------------------
        */       
        ulHour   = (ulSysTime >> 16) & 0xFFFF;
        ulMinute = (ulSysTime >> 8) & 0xFF;
        ulSecond = ulSysTime & 0xFF;
    }

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_1024, P4("\r\nPTPV2 PKT DEBUG [%02u:%02u:%02u %3u]:", ulHour, ulMinute, ulSecond, ulSysMillSec));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P1("\r\nIfIndex:%u", pstAddrInfo->ulIfIndex));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P0("\r\nHEADER INFO:"));
    
    /*Flag Field needs to be printed in Hex with the nibbles getting printed properly.
    For eg 0400 should get printed as 0x0400 and not 40*/
    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P9("\r\n    transportspecific : %u\r\n    messageType : %u (%s)\r\n    version : %u\r\n    length : %u\r\n    flagfield : 0x%02x%02x\r\n    correctionfield : %x%x",
                              pstMsgHeader->uctransportSpecific,
                              pstMsgHeader->ucmessageType,
                              szMsgtype[pstMsgHeader->ucmessageType],
                              pstMsgHeader->ucversionPTP,
                              VOS_NTOHS(pstMsgHeader->usmessageLength),
                              pstMsgHeader->ucflagField[0],
                              pstMsgHeader->ucflagField[1],
                              pstMsgHeader->uulcorrectionField.hi,
                              pstMsgHeader->uulcorrectionField.lo));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P8("\r\n    source clock id : %02x%02x%02x%02x%02x%02x%02x%02x ",
                              pstMsgHeader->stSourcePortIdentity.szClockId[0],
                              pstMsgHeader->stSourcePortIdentity.szClockId[1],
                              pstMsgHeader->stSourcePortIdentity.szClockId[2],
                              pstMsgHeader->stSourcePortIdentity.szClockId[3],
                              pstMsgHeader->stSourcePortIdentity.szClockId[4],
                              pstMsgHeader->stSourcePortIdentity.szClockId[5],
                              pstMsgHeader->stSourcePortIdentity.szClockId[6],
                              pstMsgHeader->stSourcePortIdentity.szClockId[7]));
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P4("\r\n    source port number : %u\r\n    sequenceId : %u\r\n    controlfield : %u\r\n    logmessageinterval : %d",
                              VOS_NTOHS(pstMsgHeader->stSourcePortIdentity.usPortNumber),
                              VOS_NTOHS(pstMsgHeader->usSequenceId),
                              pstMsgHeader->ucControlField,
                              pstMsgHeader->cLogMessageInterval));

   
    TCPIP_InfoOutput(szBuf);

    return;

}

ULONG PTPV2_GrandMasterIDCheck(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg)
{
    LONG lCmp = -1L;

    if (NULL == pstAnnMsg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    (VOID)VOS_Mem_Cmp((VOID*)g_pstPtpGlobalInfo->szClockId,(VOID*)pstAnnMsg->stGrandmasterIdentity,sizeof(TCPIP_PTP_CLOCK_ID_SZ),&lCmp);
    if (0 == lCmp)
    {
        return TCPIP_PTP_ERR;
    }
    
    return TCPIP_PTP_OK;
}

ULONG PTPV2_BuildAnnPktClockQa(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_CLOCK_QA_S* pstClockQA)
{
    if ((NULL == pstAnnMsg) || (NULL == pstClockQA))
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }
    
    (VOID)TCPIP_Mem_Copy((VOID *)&(pstAnnMsg->stGrandmasterClockQuality), sizeof(TCPIP_PTP_CLOCK_QA_S),
                                    (VOID *)pstClockQA, sizeof(TCPIP_PTP_CLOCK_QA_S));
     
    pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance =
         VOS_HTONS(pstClockQA->usOffsetScaledLogVariance);

    return TCPIP_PTP_OK;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
