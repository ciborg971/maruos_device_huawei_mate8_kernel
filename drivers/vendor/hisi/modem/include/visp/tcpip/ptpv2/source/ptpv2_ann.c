/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_ann.c
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP Ann
*  Date Created: 2008-06-02
*        Author: ̷ǿ
*   Description: Announce��Ϣ���պͷ��ʹ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02      ̷ǿ                  Create
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"

#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: PTPV2_Ann_RcvMsg
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UCHAR* pucBuffer:
*               ULONG ulPacketLen:
*               TCPIP_PTP_ADDRINFO_S* pstAddrInfo:
*               PTPV2_PORT_S *pstPortInfo:
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
ULONG PTPV2_Ann_RcvMsg (UCHAR* pucBuffer, ULONG ulPacketLen, 
                                  TCPIP_PTP_ADDRINFO_S* pstAddrInfo, PTPV2_PORT_S *pstPortInfo)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;
    PTPV2_FOREIGN_MASTER_S* pstSelectMaster = NULL;
    ULONG ulPtpV2ClockType = 0;

    VOS_DBGASSERT(NULL != pucBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    /*ȫ�ֱ���ͳ��*/
    g_stGlobalPtpV2PktStat.ulRcvAnnPackets ++;
    /*�˿ڱ���ͳ��*/
    pstPortInfo->stPacketStat.ulRcvAnnPackets ++;

    pstAnnMsg = (PTPV2_ANNOUNCE_MSG_S*) pucBuffer;

    ulPtpV2ClockType = PTPV2_GetClockType();

    /*
      �Ƿ���Դ���ann����
      ����:1���˿ڱ�����Ч   && 2�������Ѿ�start &&  3��������OC master
    */
    if (NULL == pstPortInfo->pstSubPortInfo || PTPV2_NO == pstPortInfo->pstSubPortInfo->ucWorkState
        || (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType
            && TCPIP_PTP_PORT_ROLE_MASTER == pstPortInfo->pstSubPortInfo->ucPtpPortRole))
    {
        ulRet =  TCPIP_PTP_ERR_NO_START;

        goto EXIT_LABEL;
    }

    /*ģʽ�Ƿ�ƥ��*/
    ulRet =  PTPV2_PktWithCastModeMatch(pstPortInfo, pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }
        
    /*announce���ĵ���ȷ�Լ��*/
    ulRet = PTPV2_PktHeaderCheck(pstPortInfo,
                               pucBuffer,
                               TCPIP_PTP_MSG_ANNOUNCE,
                               ulPacketLen,
                               pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*If the stepsRemoved field of S is 255 or greater, S shall not be qualified.*/
    if (PTPV2_MAX_STEPSREMOVED <= VOS_NTOHS(pstAnnMsg->usStepsRemoved))
    {
        ulRet = TCPIP_PTP_ERR_STEPSREMOVED;
        goto EXIT_LABEL;
    }

    ulRet = PTPV2_GrandMasterIDCheck(pstAnnMsg);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*BMC Ԥ����:����µ�ʱ��Դ���߸��¾ɵ�*/ /*����forgein  matser*/
    ulRet = PTPV2_BMCPreProcess(pstPortInfo, pstAnnMsg, pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*ѡԴ����*/
    (VOID)PTPV2_BMCProcess(&pstSelectMaster);

    /*ѡԴ�������²���*/
    (VOID)PTPV2_BMCNotify(pstSelectMaster);

EXIT_LABEL:
    if (TCPIP_PTP_OK != ulRet)
    {
        /*������ͳ��*/
        g_stGlobalPtpV2PktStat.ulRcvErrorForeMasterPackets ++;
        pstPortInfo->stPacketStat.ulRcvErrorForeMasterPackets ++;
    }

    return ulRet;
}


ULONG PTPV2_BC_MasterBuildAnnPkt(VOID* pThis, VOID** ppData)
{
    ULONG ulRet = TCPIP_PTP_OK;
    USHORT usAnnPktLen = LEN_64;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstSndBuf = NULL;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;
    PTPV2_FOREIGN_MASTER_S *pstVirutalD0 = g_pstVirtualD0;

    pstPtpPort = (PTPV2_PORT_S*)pThis;
    VOS_DBGASSERT(NULL != pstPtpPort);

    /*ֻ����˿�ΪMASTER��ɫ�ɷ�����,AR-IP-PTP.002*/
    if (pstPtpPort->pstSubPortInfo->ucPtpPortRole != TCPIP_PTP_PORT_ROLE_MASTER)
    {        
        return TCPIP_PTP_ERR;
    }    

    /*����announce����*/
    pstSndBuf = (MBUF_S*)MBUF_CreateForControlPacket(LEN_128, sizeof(PTPV2_ANNOUNCE_MSG_S),
                MBUF_TYPE_DATA, PTPV2_MID);
    if (NULL == pstSndBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2816, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_BC_MasterBuildAnnPkt fail to create mbuf!\r\n",
                0, 0, 0, 0);
        
        return TCPIP_PTP_ERR;
    }

    pstAnnMsg = MBUF_MTOD(pstSndBuf, PTPV2_ANNOUNCE_MSG_S*);

    (VOID)TCPIP_Mem_Set((CHAR *)pstAnnMsg, 0, sizeof(PTPV2_ANNOUNCE_MSG_S)); 

    ulRet = PTPV2_BuildAnnPktHeader(pstPtpPort, &(pstAnnMsg->stMsgHeader));
    if (TCPIP_PTP_OK != ulRet)
    {
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulSndBuildDropPackets ++;
        pstPtpPort->stPacketStat.ulSndBuildDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2817, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_BC_MasterBuildAnnPkt fail to build ann header! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
        MBUF_Destroy(pstSndBuf);
        return ulRet;
    }

    pstAnnMsg->stMsgHeader.usmessageLength = VOS_HTONS(usAnnPktLen);

    /*����ԴEbestʱ,utc/���ȼ�/stepRemoved/timesource/GMid����Դ��ȡ,�����VirtualD0��ȡ*/
    if (PTPV2_YES == PTPV2_HaveParent())
    {
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(g_pstPtpGlobalInfo->stParentDs.sCurrentUtcOffset);
        pstAnnMsg->ucGrandmasterPriority1 = g_pstPtpGlobalInfo->stParentDs.ucGrandmasterPriority1;
        pstAnnMsg->ucGrandmasterPriority2 = g_pstPtpGlobalInfo->stParentDs.ucGrandmasterPriority2;
        pstAnnMsg->usStepsRemoved = VOS_HTONS(g_pstPtpGlobalInfo->stParentDs.usStepsRemoved + 1);
        pstAnnMsg->ucTimeSource = g_pstPtpGlobalInfo->stParentDs.ucTimeSource;
        (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,
                           (VOID*)(g_pstPtpGlobalInfo->stParentDs.szGrandMasterId), TCPIP_PTP_CLOCK_ID_LEN);

        if (0xFE != g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa.ucClockAccuracy)
        {   
            /*ѡ��Դ,�������õ�visp,��ȡ�������õ�ʱ������*/
            (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa));
        }
        else
        {
            /*ѡ��Դ,û�����õ�visp,��ȡѡԴ��ʱ������*/
            (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stParentDs.stParentClockQA));
        }
    }
    else if (NULL != pstVirutalD0)
    {
        /*û��ѡ��Դ,��D0ֵ����*/
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(pstVirutalD0->sCurrentUtcOffset);
        pstAnnMsg->ucGrandmasterPriority1 = pstVirutalD0->ucGrandmasterPriority1;
        pstAnnMsg->ucGrandmasterPriority2 = pstVirutalD0->ucGrandmasterPriority2;
        pstAnnMsg->usStepsRemoved = VOS_HTONS(pstVirutalD0->usStepsRemoved + 1);
        pstAnnMsg->ucTimeSource = pstVirutalD0->ucTimeSource;
        (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,
                           (VOID*)&(pstVirutalD0->szForeignMasterPortId), TCPIP_PTP_CLOCK_ID_LEN);

        /*û��ѡ��Դ,����ѡ��Դȴû�����õ�visp,��ȡD0��ʱ������*/
        (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(pstVirutalD0->stGrandmasterClockQuality));
    }

    *ppData = pstSndBuf;
    return ulRet;

}

ULONG PTPV2_OC_MasterBuildAnnPkt(VOID* pThis, VOID** ppData)
{
    ULONG ulRet = TCPIP_PTP_OK;
    USHORT usAnnPktLen = LEN_64;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstSndBuf = NULL;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;

    pstPtpPort = (PTPV2_PORT_S*)pThis;
    VOS_DBGASSERT(NULL != pstPtpPort);
 
    /*OC masterҪ���й���announce����*/
    pstSndBuf = (MBUF_S*)MBUF_CreateForControlPacket(LEN_128, sizeof(PTPV2_ANNOUNCE_MSG_S),
                MBUF_TYPE_DATA, PTPV2_MID);
    if (NULL == pstSndBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2818, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OC_MasterBuildAnnPkt!\r\n",
                0, 0, 0, 0);
        return TCPIP_PTP_ERR;
    }

    pstAnnMsg = MBUF_MTOD(pstSndBuf, PTPV2_ANNOUNCE_MSG_S*);

    (VOID)TCPIP_Mem_Set((CHAR *)pstAnnMsg, 0, sizeof(PTPV2_ANNOUNCE_MSG_S)); 

    ulRet = PTPV2_BuildAnnPktHeader(pstPtpPort, &(pstAnnMsg->stMsgHeader));
    if (TCPIP_PTP_OK != ulRet)
    {
        /*����ͳ��*/
        g_stGlobalPtpV2PktStat.ulSndBuildDropPackets ++;
        pstPtpPort->stPacketStat.ulSndBuildDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2819, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OC_MasterBuildAnnPkt fail to build ann header! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
        /*����*/
        MBUF_Destroy(pstSndBuf);
        return ulRet;
    }

    pstAnnMsg->stMsgHeader.usmessageLength = VOS_HTONS(usAnnPktLen);

    if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid)
    {
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset);
    }
    else
    {
        pstAnnMsg->sCurrentUtcOffset = 0; /*utc ��Ч����ֵΪ0*/
    }

    pstAnnMsg->ucGrandmasterPriority1 = g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriority1;
    pstAnnMsg->ucGrandmasterPriority2 = g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriority2;
    /*ʱ�������Ա�������Ϊ׼*/
    (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa));

    (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,(VOID*)(g_pstPtpGlobalInfo->szClockId), TCPIP_PTP_CLOCK_ID_LEN);
    pstAnnMsg->usStepsRemoved = VOS_HTONS(g_pstPtpGlobalInfo->usStepsRemoved);
    pstAnnMsg->ucTimeSource =  g_pstPtpGlobalInfo->ucTimeSource;

    *ppData = pstSndBuf;
    return ulRet;
}

/******************************************************************************
*Func Name   : PTPV2_ANN_PrintAnn
*Description : announce���Ĵ�ӡ�ӿ�
*Input       : PTPV2_ANNOUNCE_MSG_S *pstAnnMsg: ��Ϣͷ
*              TCPIP_PTP_ADDRINFO_S *pstAddrInfo:  ����/���ͱ��ĵĵ�ַ�Լ�UDP��Ϣ
*              ULONG ulFlag:        ���:0-���ͱ���;��0-���ձ���
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
VOID PTPV2_ANN_PrintAnn(PTPV2_ANNOUNCE_MSG_S *pstAnnMsg, TCPIP_PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag)
{    
    CHAR szBuf[LEN_512] = {0};  /* ����������512���ֽڣ���ű�����Ϣ */
    CHAR szInOrOut[10] = {0};
    INT32 i32Offset = 0;
    
    if ((NULL == pstAnnMsg) || (NULL == pstAddrInfo))
    {
        return;
    }
    
    if (0 == ulFlag)
    {
        i32Offset = TCPIP_SNPRINTF0(szInOrOut, 10, P0("send"));
    }
    else
    {
        i32Offset = TCPIP_SNPRINTF0(szInOrOut, 10, P0("receive"));
    }
    
    /* �ȴ�ӡ��ʾ��Ϣ */
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P1("\r\n----------announce msg %s begin----------",szInOrOut));
    
    TCPIP_InfoOutput(szBuf);

    (VOID)TCPIP_Mem_Set(szBuf, 0, LEN_512);
    
    /* ��ӡ��Ϣͷ */
    PTPV2_PrintHeader((PTPV2_MSGHEADER_S *)pstAnnMsg, pstAddrInfo);
    
    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\nANNOUNCE INFO:"));    

    /* ��ӡannounce��Ϣ���������� */
    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P8("\r\n    originTimestamp : Nano-%u,Low-%u,High-%u \r\n    utcoffset : %d\r\n    grandmasterPri1 : %u\r\n    grandmasterQuality : Accuracy-%u,class-%u,offset-%u ",
                              pstAnnMsg->stOriginTimestamp.ulNanoseconds,
                              pstAnnMsg->stOriginTimestamp.ulSecondsLow,
                              pstAnnMsg->stOriginTimestamp.usSecondsHigh,
                              VOS_NTOHS(pstAnnMsg->sCurrentUtcOffset),
                              pstAnnMsg->ucGrandmasterPriority1,
                              pstAnnMsg->stGrandmasterClockQuality.ucClockAccuracy,
                              pstAnnMsg->stGrandmasterClockQuality.ucClockClass,
                              VOS_NTOHS(pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance)));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P11("\r\n    grandmasterPri2 : %u\r\n    grandmasterId : %02x%02x%02x%02x%02x%02x%02x%02x\r\n    stepsremoved : %u\r\n    timesource : %u",
                              pstAnnMsg->ucGrandmasterPriority2,
                              pstAnnMsg->stGrandmasterIdentity[0],
                              pstAnnMsg->stGrandmasterIdentity[1],
                              pstAnnMsg->stGrandmasterIdentity[2],
                              pstAnnMsg->stGrandmasterIdentity[3],
                              pstAnnMsg->stGrandmasterIdentity[4],
                              pstAnnMsg->stGrandmasterIdentity[5],
                              pstAnnMsg->stGrandmasterIdentity[6],
                              pstAnnMsg->stGrandmasterIdentity[7],
                              VOS_NTOHS(pstAnnMsg->usStepsRemoved),
                              pstAnnMsg->ucTimeSource));
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P1("\r\n----------announce msg %s end------------",szInOrOut));

    TCPIP_InfoOutput(szBuf);
    
}

#ifdef __cplusplus
}
#endif
