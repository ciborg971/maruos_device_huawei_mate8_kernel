


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CDS.h"
#include "CdsImsProc.h"
#include "CdsUlProc.h"
#include "CdsDlProc.h"
#include "CdsMsgProc.h"
#include "CdsDebug.h"
#include "CdsIpfCtrl.h"
#include "CdsSoftFilter.h"
//#include "LPdcpDlProc.h"

#if (CDS_FEATURE_ON == CDS_FEATURE_IMS)
#include "ImsNicInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_IMS_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
VOS_UINT32  g_ulCdsTracePktFlg = PS_FALSE;
CDS_IMS_DL_FRAGMENT_BUFF_STRU  g_stCdsImsDlFragInfoBuff = {0};

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

#if (CDS_FEATURE_OFF == CDS_FEATURE_IMS)



/* IMS���������������ݷ��ͻص����� */
typedef VOS_UINT32 (*IMS_NIC_SEND_UL_DATA_FUNC)(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId)
{
    (VOS_VOID)pFunc;
    (VOS_VOID)enModemId;
    return PS_SUCC;
}
VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    (VOS_VOID)pData;
    (VOS_VOID)usLen;
    (VOS_VOID)enModemId;

    return PS_SUCC;
}

#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_LTE)

VOS_UINT32 CDS_ERABM_GetDefaultEpsbId(VOS_UINT8 ucDrbId, VOS_UINT8 *pucDeftEpsbId)
{
    (VOS_VOID)ucDrbId;
    *pucDeftEpsbId = 5;
    return PS_SUCC;
}
#endif


TTF_MEM_ST* CDS_TtfMemCopyAlloc(TTF_MEM_ST *pstSrc, VOS_UINT32 ulLen)
{
    TTF_MEM_ST      *pstDest;

    pstDest = CDS_AllocTtfMem(ulLen);
    if (VOS_NULL_PTR == pstDest)
    {
        return VOS_NULL_PTR;
    }

    /*�ڴ濽��*/
    if (PS_SUCC != TTF_MemGetHeadData(UEPS_PID_CDS,
                                      pstSrc,
                                      pstDest->pData,
                                      pstDest->usUsed))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDest);
        return VOS_NULL_PTR;
    }

    return pstDest;
}
VOS_VOID CDS_SendIpPacket2PC(TTF_MEM_ST *pstIpPkt)
{
    TTF_MEM_ST          *pstDbgPkt;

    if (PS_TRUE != g_ulCdsTracePktFlg)
    {
        return ;
    }

    /*�������ڴ�*/
    pstDbgPkt = CDS_TtfMemCopyAlloc(pstIpPkt, pstIpPkt->usUsed);
    if (VOS_NULL_PTR == pstDbgPkt)
    {
        return ;
    }

    /*����CDS DEBUG���ݽ��սӿ�*/
    CDS_LTE_RecvDbgData(pstDbgPkt);
    return;
}



VOS_UINT32 CDS_RxDataFromImsNIC(const VOS_UINT8 *pData, VOS_UINT16 usLen,MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_ENTITY_STRU             *pstCdsEntity;
    TTF_MEM_ST                  *pstTtfPkt;
    VOS_INT32                    lLock;

    CDS_DBG_IMS_UL_RX_FUN_CALL_NUM(1);

    /*����ж�*/
    if (VOS_NULL_PTR == pData)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "CDS_RxPktFromImsNIC:Input Para is NULL");
        CDS_PRINT_ERROR(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    if ((0 == usLen) || (usLen > ETH_MAX_MTU))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RxPktFromImsNIC ; Packet Length Error.",usLen);
        CDS_PRINT_ERROR1(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_PKT_LEN_ERROR,usLen);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RxPktFromImsNIC ; Modem ID Error.",enModemId);
        CDS_PRINT_ERROR1(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    CDS_DBG_IMS_UL_RX_NIC_PKT_NUM(1);

    /*����TTF�ڴ�,�����俽����TTF�ڴ���*/
    pstTtfPkt = CDS_AllocTtfMem(usLen);
    if (VOS_NULL_PTR == pstTtfPkt)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RxDataFromImsNIC: Alloc Mem Fail.");
        CDS_PRINT_ERROR(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_MEM_ALLOC_FAIL);
        CDS_DBG_IMS_UL_ALLOC_MEM_FAIL_NUM(1);
        return PS_FAIL;
    }
    PS_MEM_CPY(pstTtfPkt->pData,pData,usLen);

    /*���*/
    lLock = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstIMSDataQue,pstTtfPkt))
    {
        VOS_Splx(lLock);
        CDS_DBG_IMS_UL_EN_QUE_FAIL_NUM(1);
        TTF_MemFree(UEPS_PID_CDS, pstTtfPkt);
        CDS_SendEventToCds(CDS_EVENT_UL_IMS_PROC);
        CDS_DBG_IMS_UL_TRIGGER_IMS_EVENT_NUM(1);
        return PS_FAIL;
    }
    VOS_Splx(lLock);
    CDS_DBG_IMS_UL_EN_QUE_SUCC_NUM(1);

    /*wakeup cds*/
    CDS_SendEventToCds(CDS_EVENT_UL_IMS_PROC);
    CDS_DBG_IMS_UL_TRIGGER_IMS_EVENT_NUM(1);
    return PS_SUCC;
}




VOS_VOID CDS_UlProcImsData(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32              ulCnt;
    TTF_MEM_ST             *pstIpPkt;
    VOS_INT32               lLock;
    CDS_ENTITY_STRU        *pstCdsEntity;
    IPF_RESULT_STRU        *pstIpfResult;
    VOS_UINT16              usResult;

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    for (ulCnt = 0; ulCnt < CDS_IMS_QUE_SIZE; ulCnt ++)
    {
        lLock = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstIMSDataQue, (VOS_VOID **)&pstIpPkt))
        {
            VOS_Splx(lLock);
            break;
        }
        VOS_Splx(lLock);

        /*���������*/
        usResult = 0;
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_IMS_UL_SOFT_FILTER_FAIL_NUM(1);
            continue;
        }

        /*�����˽���浽TTF��*/
        pstIpfResult = (IPF_RESULT_STRU *)((VOS_UINT32)&usResult);
        CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstIpPkt, usResult, enModemId, pstIpfResult->usBearedId);

        pstIpPkt->ucReserve = CDS_JudgIpPktType((VOS_UINT8)pstIpfResult->usBearedId,pstCdsEntity,pstIpPkt);
        CDS_PRINT_INFO2(CDS_UlProcImsData_ENUM, CDS_PRINT_TYPE, pstIpPkt->ucReserve,pstIpPkt->usUsed);       
        
        /*Added by l00304941 for LTE PDU Report,2015-03-13*/
        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_IMS_UL_IP_PKT_HOOK(pstIpPkt); /*�h��*/

        /*���͵��տ�*/
        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
        CDS_DBG_IMS_UL_SEND_PKT_TO_RAN_NUM(1);

    }

    return;
}
VOS_UINT32 CDS_IsNdClientPkt(const TTF_MEM_ST *pstIpPkt)
{
    CDS_IP_DATA_INFO_STRU       stIpv6Info = {0};
    ICMP_HDR_STRU              *pstIcmpHdr;

    /*��IPv6���ݰ�*/
    if (IP_VERSION_V6 != IP_GET_VERSION(pstIpPkt->pData))
    {
        return PS_FALSE;
    }

    /*����IPv6���ݰ�*/
    CDS_DecodeIpv6Packet(pstIpPkt, &stIpv6Info);

    /*NextHdr����ICMPv6*/
    if (IPV6_NEXTHDR_ICMP != stIpv6Info.ucNextHdr)
    {
        return PS_FALSE;
    }

    /*IP��Ƭ*/
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != stIpv6Info.ucIpSegType)
    {
        return PS_FALSE;
    }

    /*ƫ�Ƶ�ICMPv6ͷ,�ж�Type��Χ*/
    pstIcmpHdr = (ICMP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + stIpv6Info.ulHdrLen));
    if ((ICMPV6_TYPE_RS <= pstIcmpHdr->ucType)
        && (ICMPV6_TYPE_REDIRECT >= pstIcmpHdr->ucType))
    {
        return PS_TRUE;
    }

    return  PS_FALSE;
}
VOS_VOID CDS_SendNdDataIndMsg(TTF_MEM_ST *pstNdPkt, VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_NDCLIENT_ND_DATA_IND_STRU  *pstDataInd;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                      ulPktLen;

    CDS_ASSERT(VOS_NULL_PTR != pstNdPkt);
    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_SendNdDataIndMsg.ucRabid=",ucRabId);
    CDS_PRINT_INFO1(CDS_SendNdDataIndMsg_ENUM, CDS_PRINT_RABID, ucRabId);

    /*������Ϣ�ڴ�*/
    ulPktLen = TTF_MemGetLen(UEPS_PID_CDS,pstNdPkt);
    ulMsgLen = sizeof(CDS_NDCLIENT_ND_DATA_IND_STRU) + ulPktLen;
    pstDataInd = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstDataInd)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SendNdDataIndMsg : Alloc Msg Fail. Size=",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_SendNdDataIndMsg_ENUM,CDS_PRINT_ALLOC_MEM_FAIL_HDRLEN,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstDataInd,UEPS_PID_NDCLIENT);
    pstDataInd->enMsgId   = ID_CDS_NDCLIENT_ND_DATA_IND;
    pstDataInd->enModemId = pstCdsEntity->usModemId;
    pstDataInd->ucRabId   = ucRabId;
    pstDataInd->ulLen     = ulPktLen;

    /*�ڴ濽��*/
    if (PS_SUCC != TTF_MemGetHeadData(UEPS_PID_CDS,
                                      pstNdPkt,
                                      pstDataInd->aucData,
                                      (VOS_UINT16)ulPktLen))
    {
        /*lint -e961*/
        PS_FREE_MSG(UEPS_PID_CDS, pstDataInd);
        /*lint +e961*/
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SendNdDataIndMsg : TTF_MemGetHeadData Error.");
        CDS_PRINT_ERROR(CDS_SendNdDataIndMsg_ENUM,CDS_PRINT_MEM_GET_HEAD_DATA);
        return ;
    }

    /*������Ϣ*/
    CDS_SEND_MSG(pstDataInd);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_SendNdDataIndMsg Succ.");
    CDS_PRINT_INFO(CDS_SendNdDataIndMsg_ENUM, LL2_FUNCTION_EXIT);

    return;
}


VOS_UINT32 CDS_IsImsBearer(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32      ulCnt;

    /*����*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if (ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}
VOS_UINT32 CDS_IsImsDefBearer(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32      ulCnt;

    /*����*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if ((IMSA_CDS_IMS_BEARER_TYPE_SIGNAL == pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType)
            && (ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}
VOS_VOID CDS_ImsSaveFragmentPktInfo(const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    CDS_IMS_DL_FRAGMENT_BUFF_STRU   *pstImsFragBuff;

    if (VOS_NULL_PTR == pstIpPktInfo)
    {
        return;
    }

    pstImsFragBuff = CDS_IMS_GET_DL_FRAGMENT_BUFF();

    PS_MEM_CPY(&(pstImsFragBuff->astIpPktInfo[pstImsFragBuff->ulIndex]),
               pstIpPktInfo,
               sizeof(CDS_IP_DATA_INFO_STRU));

    pstImsFragBuff->ulIndex = TTF_MOD_ADD(pstImsFragBuff->ulIndex,1,CDS_IMS_DL_FRAGMENT_BUFF_SIZE);

    return ;
}


VOS_UINT32 CDS_ImsGetDestPortFromFragBuff(VOS_UINT16 *pusDestPort,
                                                    const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    VOS_UINT32                       ulCnt;
    CDS_IP_DATA_INFO_STRU           *pstBuffPktInfo;
    CDS_IMS_DL_FRAGMENT_BUFF_STRU   *pstImsFragBuff;

    pstImsFragBuff = CDS_IMS_GET_DL_FRAGMENT_BUFF();

    for(ulCnt = 0; ulCnt < CDS_IMS_DL_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstBuffPktInfo = &(pstImsFragBuff->astIpPktInfo[ulCnt]);

        if ((PS_TRUE == CDS_IsIpv4FragInfoEq(pstIpPktInfo, pstBuffPktInfo))
            || (PS_TRUE == CDS_IsIpv6FragInfoEq(pstIpPktInfo, pstBuffPktInfo)))
        {
            *pusDestPort = pstBuffPktInfo->usDestPort;
            return PS_SUCC;
        }
    }

    return PS_FAIL;
}


VOS_UINT32 CDS_ImsGetPktDestPort(VOS_UINT16 *pusDestPort,
                                        const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    /*��IP��Ƭ��*/
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT == pstIpPktInfo->ucIpSegType)
    {
        *pusDestPort = pstIpPktInfo->usDestPort;
        return PS_SUCC;
    }

    /*ͷ��Ƭ������IP����Ϣ*/
    if (CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD == pstIpPktInfo->ucIpSegType)
    {
        *pusDestPort = pstIpPktInfo->usDestPort;
        CDS_ImsSaveFragmentPktInfo(pstIpPktInfo);
        return PS_SUCC;
    }

    /*�м��Ƭ��β��Ƭ���ӻ�������в���Ŀ�Ķ˿ں�*/
    if (PS_SUCC != CDS_ImsGetDestPortFromFragBuff(pusDestPort,pstIpPktInfo))
    {
        *pusDestPort = 0;
        return PS_FAIL;
    }

    /*�쳣����,�˿ںŲ���Ϊ0*/
    if (0 == *pusDestPort)
    {
        return PS_FAIL;
    }

    return PS_SUCC;

}


VOS_UINT32 CDS_IsImsUtPkt(const TTF_MEM_ST *pstIpPkt,const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_IP_DATA_INFO_STRU       stIpPktInfo = {0};
    VOS_UINT16                  ulDestPort  = 0;

    /*�������ݰ�*/
    if (IP_VERSION_V4 == IP_GET_VERSION(pstIpPkt->pData))
    {
        CDS_DecodeIpv4Packet(pstIpPkt, &stIpPktInfo);
    }
    else if (IP_VERSION_V6 == IP_GET_VERSION(pstIpPkt->pData))
    {
        CDS_DecodeIpv6Packet(pstIpPkt, &stIpPktInfo);
    }
    else
    {
        return PS_FALSE;
    }

    /*����IPSECЭ��*/
    if ((0 != stIpPktInfo.ulAhSpi) || (0 != stIpPktInfo.ulEspSpi))
    {
        return PS_FALSE;
    }

    /*��ȡĿ�Ķ˿ں�ʧ�ܣ����͵�IMSЭ��ջ����*/
    if (PS_SUCC != CDS_ImsGetPktDestPort(&ulDestPort, &stIpPktInfo))
    {
        CDS_DBG_IMS_DL_GET_DEST_PORT_FAIL_NUM(1);
        return PS_FALSE;
    }

    /*û��Ŀ�Ķ˿ں�*/
    if ((ulDestPort >= pstCdsEntity->stImsPortInfo.usMinImsPort)
        && (ulDestPort <= pstCdsEntity->stImsPortInfo.usMaxImsPort))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


VOS_VOID CDS_DlProcImsUtPkt(CDS_IMS_SDU_STRU *pstImsSdu, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32              ulResult;
    VOS_UINT8               ucDeftRabId;
    TTF_MEM_ST             *pstIpPkt;

    CDS_DBG_IMS_DL_RX_IMS_Ut_PKT_NUM(1);

    if (MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        ulResult = CDS_GUGetDefaultRabId(pstImsSdu->ucRabId,&ucDeftRabId,pstCdsEntity->usModemId);
    }
    else
    {
        ulResult = CDS_ERABM_GetDefaultEpsbId(pstImsSdu->ucDrbId,&ucDeftRabId);
    }

    if (PS_SUCC != ulResult)
    {
        TTF_MemFree(UEPS_PID_CDS, pstImsSdu->pstSdu);
        CDS_DBG_IMS_DL_Ut_PKT_PROC_ERR_NUM(1);
        return;
    }

    /*�����Ҫ��Ϣ*/
    pstIpPkt = pstImsSdu->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstImsSdu->ulSduLen,
                                         pstCdsEntity->usModemId,
                                         ucDeftRabId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(1);
        CDS_DBG_IMS_DL_Ut_PKT_PROC_ERR_NUM(1);
        return;
    }

    CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(1);
    CDS_DBG_IMS_DL_Ut_PKT_PROC_SUCC_NUM(1);

    return;
}


VOS_VOID CDS_DlProcImsData(CDS_IMS_SDU_STRU *pstImsSdu, const CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST          *pstImsPkt;

    CDS_DBG_IMS_DL_RX_IMS_PKT_NUM(1);

    /*����Ƿ������ڴ棬�򿽱��������ڴ��ϣ��������ʹ��ԭ�����ڴ�*/
    if (VOS_NULL_PTR == pstImsSdu->pstSdu->pNext)
    {
        pstImsPkt = pstImsSdu->pstSdu;
    }
    else
    {
        pstImsPkt = CDS_TtfMemCopyAlloc(pstImsSdu->pstSdu,pstImsSdu->ulSduLen);
        TTF_MemFree(UEPS_PID_CDS,pstImsSdu->pstSdu);
    }

    if (VOS_NULL_PTR == pstImsPkt)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_DlProcImsData : Copy Alloc Ttf Mem Fail.Len=",pstImsSdu->ulSduLen);
        CDS_PRINT_ERROR1(CDS_DlProcImsData_ENUM,LL2_PTR_NULL,pstImsSdu->ulSduLen);
        CDS_DBG_IMS_DL_ALLOC_MEM_FAIL_NUM(1);
        return ;
    }

    /*�����Ҫ��Ϣ*/
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstImsPkt,
                                         pstImsPkt->usUsed,
                                         pstCdsEntity->usModemId,
                                         pstImsSdu->ucRabId);

    /*Added by l00304941 for LTE PDU Report,2015-03-13*/
    CDS_DBG_IMS_DL_IP_PKT_HOOK(pstImsPkt);
    CDS_DBG_DL_REC_IP_PKT_INFO(pstImsPkt);

    /*NDCLIENT���ݰ������͵�NDCLIENT*/
    if ((PS_TRUE == CDS_IsImsDefBearer(pstImsSdu->ucRabId,pstCdsEntity))
         && (PS_TRUE == CDS_IsNdClientPkt(pstImsPkt)))
    {
        CDS_SendNdDataIndMsg(pstImsPkt,pstImsSdu->ucRabId,pstCdsEntity);
        TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
        CDS_DBG_IMS_DL_RX_ND_PKT_NUM(1);
        return;
    }
    else if (PS_TRUE == CDS_IsImsUtPkt(pstImsPkt, pstCdsEntity))
    {
        /*�����ڴ�ָ��*/
        pstImsSdu->pstSdu = pstImsPkt;
        CDS_DlProcImsUtPkt(pstImsSdu,pstCdsEntity);
        return;
    }

    /*���͵�IMS NIC*/
    if (PS_SUCC != IMS_NIC_DlDataRcv(pstImsPkt->pData,
                                     pstImsPkt->usUsed,
                                     pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
        CDS_DBG_IMS_DL_SEND_TO_NIC_FAIL_NUM(1);
        return;
    }

    /*�ͷ��ڴ�*/
    TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
    CDS_DBG_IMS_DL_SEND_TO_NIC_SUCC_NUM(1);
    return;
}
VOS_VOID CDS_SendImsaSetImsBearerCnfMsg(VOS_UINT32 ulResult)
{
    IMSA_CDS_SET_IMS_BEARER_CNF_STRU   *pstCnfMsg;
    VOS_UINT32                          ulMsgLen;

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_SendImsaSetImsBearerCnfMsg. ulResult=",ulResult);
    CDS_PRINT_INFO1(CDS_SendImsaSetImsBearerCnfMsg_ENUM, CDS_PRINT_CNF_RESULT, ulResult);

    ulMsgLen = sizeof(IMSA_CDS_SET_IMS_BEARER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SendImsaSetImsBearerCnfMsg : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_SendImsaSetImsBearerCnfMsg_ENUM,CDS_PRINT_ALLOC_MEM_FAIL_HDRLEN,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstCnfMsg,PS_PID_IMSA);
    pstCnfMsg->ulMsgId  = ID_IMSA_CDS_SET_IMS_BEARER_CNF;
    pstCnfMsg->ulResult = ulResult;

    /*������Ϣ*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_SendImsaSetImsBearerCnfMsg Succ.");
    CDS_PRINT_INFO(CDS_SendImsaSetImsBearerCnfMsg_ENUM, LL2_FUNCTION_EXIT);

    return;
}

VOS_VOID CDS_ImsaSetImsBearerReqMsgProc(MsgBlock *pstMsg)
{
    IMSA_CDS_SET_IMS_BEARER_REQ_STRU   *pstReqMsg;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    VOS_UINT32                         ulLoop = 0;
    VOS_UINT8                          ucEpsbId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ImsaSetImsBearerReqMsgProc.");
    CDS_PRINT_INFO(CDS_ImsaSetImsBearerReqMsgProc_ENUM, LL2_FUNCTION_ENTER);

    pstReqMsg = (IMSA_CDS_SET_IMS_BEARER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->ulImsBearerNum > IMSA_CDS_MAX_IMS_BEARER_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : IMS Bearer Number Error.",pstReqMsg->ulImsBearerNum);
        CDS_PRINT_ERROR1(CDS_ImsaSetImsBearerReqMsgProc_ENUM,CDS_PRINT_IMS_BEARER_NUM_ERR,pstReqMsg->ulImsBearerNum);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*Ĭ�ϰ�MODEM_0����*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ImsaSetImsBearerReqMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*ע��IMS NIC�ص�����*/
    if (PS_SUCC != IMS_NIC_RegUlDataSendCb((IMS_NIC_SEND_UL_DATA_FUNC)CDS_RxDataFromImsNIC,
                                            pstCdsEntity->usModemId))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : IMS_NIC_RegUlDataSendCb Fail.");
        CDS_PRINT_ERROR(CDS_ImsaSetImsBearerReqMsgProc_ENUM,LL2_FUNCTION_RETURN_ERROR);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*����CDSʵ����Ϣ*/
    pstCdsEntity->ulImsBearerNum = pstReqMsg->ulImsBearerNum;
    PS_MEM_CPY(pstCdsEntity->astImsBearerInfo,
               pstReqMsg->astImsBearerArray,
               pstReqMsg->ulImsBearerNum * sizeof(IMSA_CDS_IMS_BEARER_STRU));
    for(ulLoop = 0; ulLoop < pstCdsEntity->ulImsBearerNum; ulLoop ++)
    {
        ucEpsbId = pstCdsEntity->astImsBearerInfo[ulLoop].ucEpsbId;
        CDS_LPDCP_SetImsBearer(ucEpsbId);
    }

    pstCdsEntity->stImsPortInfo.usMinImsPort = pstReqMsg->stImsPortInfo.usMinImsPort;
    pstCdsEntity->stImsPortInfo.usMaxImsPort = pstReqMsg->stImsPortInfo.usMaxImsPort;

    /*���ͳɹ���Ϣ*/
    CDS_SendImsaSetImsBearerCnfMsg(PS_SUCC);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ImsaSetImsBearerReqMsgProc Succ.");
    CDS_PRINT_INFO(CDS_ImsaSetImsBearerReqMsgProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}


VOS_VOID CDS_IMSA_MsgProc(MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_IMSA_MsgProc : Input NULL PTR.");
        CDS_PRINT_INFO(CDS_IMSA_MsgProc_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_IMSA_CDS_SET_IMS_BEARER_REQ:
        CDS_ImsaSetImsBearerReqMsgProc(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_IMSA_MsgProc: Msg Id Error.MsgID=",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_IMSA_MsgProc_ENUM, CDS_PRINT_MSG_ID_ERROR, TTF_GET_MSG_NAME(pstMsg));
        break;

    }

    return;

}

VOS_UINT8 CDS_JudgIpPktType(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt)
{
    VOS_UINT32      ulCnt;

    /*����*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if((ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId)
                    &&(IMSA_CDS_IMS_BEARER_TYPE_MEDIA == pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType))
        {
            if (pstIpPkt->usUsed > CDS_IMS_MIN_SPEECH_FRM)
            {
                return IP_PKT_TYPE_IMS_SPEECH;
            }
            else
            {
                return IP_PKT_TYPE_IMS_SILENCE;
            }
        }
    }
    return IP_PKT_TYPE_NORMAL;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

