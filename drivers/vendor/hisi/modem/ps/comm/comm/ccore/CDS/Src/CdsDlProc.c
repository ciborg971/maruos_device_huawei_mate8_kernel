


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CDS.h"
#include "CdsDlProc.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"
#include "QosFcOm.h"
#include "CdsImsProc.h"
#include "CdsBastetProc.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_DL_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/
extern VOS_BOOL Fc_CdsDlPktDiscard(VOS_UINT8 ucRabId);

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

#if (CDS_FEATURE_OFF == CDS_FEATURE_MULTI_MODEM)

VOS_UINT32 I1_NAS_RABM_GetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId)
{
    if (VOS_NULL_PTR == pucDeftRabId)
    {
        return PS_FAIL;
    }

    *pucDeftRabId = ucRabId;
    return PS_SUCC;
}

#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_MODEM_2)

VOS_UINT32 I2_NAS_RABM_GetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId)
{
    if (VOS_NULL_PTR == pucDeftRabId)
    {
        return PS_FAIL;
    }

    *pucDeftRabId = ucRabId;
    return PS_SUCC;
}

#endif


VOS_UINT32 CDS_GUGetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    if (MODEM_ID_0 == enModemId)
    {
        return NAS_RABM_GetDefaultRabId(ucRabId, pucDeftRabId);
    }
    else if (MODEM_ID_1 == enModemId)
    {
        return I1_NAS_RABM_GetDefaultRabId(ucRabId, pucDeftRabId);
    }
    else if (MODEM_ID_2 == enModemId)
    {
        return I2_NAS_RABM_GetDefaultRabId(ucRabId, pucDeftRabId);
    }
    else
    {
        return PS_FAIL;
    }
}


VOS_UINT32 CDS_RxDlSdu(TTF_MEM_ST *pstIpPkt)
{
    VOS_INT32      lLock;

    lLock = VOS_SplIMP();

    if (PS_SUCC != LUP_EnQue(CDS_GET_IPF_DL_SDU_QUE(),pstIpPkt))
    {
        VOS_Splx(lLock);
        TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
        CDS_DBG_DL_EN_SDU_QUEUE_FAIL_NUM(1);
        return PS_FAIL;
    }

    CDS_DBG_DL_EN_SDU_QUEUE_SUCC_NUM(1);

    VOS_Splx(lLock);

    return PS_SUCC;
}



VOS_UINT32 CDS_GUDlSduParaCheck(CDS_RABM_TRANS_DATA_STRU *pstDlData)
{
    if (VOS_NULL_PTR == pstDlData)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GUDlSduParaCheck : Input Null Para.");
        CDS_PRINT_ERROR(CDS_GUDlSduParaCheck_ENUM, LL2_PARA_CHECK_FAIL);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == pstDlData->pstSdu)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GUDlSduParaCheck : Sdu Ptr Is NULL.");
        CDS_PRINT_ERROR(CDS_GUDlSduParaCheck_ENUM, CDS_PRINT_SDU_PTR_NULL);
        return PS_FAIL;
    }

    if ((0 == pstDlData->ulSduLen) || (CDS_DL_SDU_MAX_LEN < pstDlData->ulSduLen))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GUDlSduParaCheck : SDU Too Big.",pstDlData->ulSduLen);
        CDS_PRINT_ERROR1(CDS_GUDlSduParaCheck_ENUM, CDS_PRINT_SDU_LEN_ERROR, pstDlData->ulSduLen);
        return PS_FAIL;
    }

    if ((CDS_NAS_MIN_BEARER_ID > pstDlData->ucRabId) || (CDS_NAS_MAX_BEARER_ID < pstDlData->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GUDlSduParaCheck : Input RabId Fail.RabID=",pstDlData->ucRabId);
        CDS_PRINT_ERROR1(CDS_GUDlSduParaCheck_ENUM, CDS_PRINT_RAB_ID_ERR, pstDlData->ucRabId);
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        return PS_FAIL;
    }

    return PS_SUCC;
}


VOS_VOID CDS_UMTS_DL_DataInd(CDS_RABM_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    TTF_MEM_ST            *pstIpPkt;
    CDS_ENTITY_STRU       *pstCdsEntity;
    CDS_LB_DL_SDU_STRU     stLbSdu;
    VOS_UINT8              ucDeftRabId;
    CDS_IMS_SDU_STRU       stImsSdu;

    /*����ж�*/
    if (PS_SUCC != CDS_GUDlSduParaCheck(pstDlData))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_UMTS_DL_DataInd : Sdu Para Error.");
        CDS_PRINT_ERROR(CDS_UMTS_DL_DataInd_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UMTS_DL_DataInd : Input ModemId Fail.RabID=",enModemId);
        CDS_PRINT_ERROR1(CDS_UMTS_DL_DataInd_ENUM, CDS_PRINT_MODEM_ID_ERR, enModemId);
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        return;
    }

    CDS_DBG_DL_UMTS_RX_SDU_NUM(1);
    CDS_DBG_MODEM_DL_UMTS_RX_SDU_NUM(enModemId,1);

    /* ����ͳ�� */
    CDS_DLFlowAdd(pstDlData->ulSduLen);

    /*IMS*/
    if (PS_TRUE == CDS_IsImsBearer(pstDlData->ucRabId, pstCdsEntity))
    {
        stImsSdu.ucRabId  = pstDlData->ucRabId;
        stImsSdu.ucDrbId  = 0;
        stImsSdu.ulSduLen = pstDlData->ulSduLen;
        stImsSdu.pstSdu   = pstDlData->pstSdu;
        CDS_DlProcImsData(&stImsSdu, pstCdsEntity);
        CDS_DBG_DL_UMTS_RX_IMS_PKT_NUM(1);
        CDS_DBG_MODEM_DL_UMTS_RX_IMS_PKT_NUM(enModemId,1);
        /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
        CDS_BstSendRxInd();
        return;
    }
    /*BASTET*/
    if(PS_TRUE == CDS_GU_BstProcDlData(pstDlData, enModemId))
    {
        return;
    }
    /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
    CDS_BstSendRxInd();

    /*����ģʽ*/
    if ((PS_TRUE == pstCdsEntity->ulTestModeFlg) && (CDS_LB_STATE_START == pstCdsEntity->ulLoopBackState))
    {
        stLbSdu.ulSduLen = pstDlData->ulSduLen;
        stLbSdu.pstSdu   = pstDlData->pstSdu;
        CDS_RxLoopBackPkt(&stLbSdu,pstCdsEntity);

        CDS_DBG_LB_DL_RX_SDU_FROM_UMTS(1);
        CDS_DBG_MODEM_ID_LB_DL_RX_SDU_FROM_UMTS(enModemId,1);
        return;
    }

    /*���ܲ��ԣ��ڴ�ֱ���ͷ�*/
    if (PS_TRUE == pstCdsEntity->ulDLPktDiscardFlg)
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        CDS_DBG_DL_UMTS_DIRECT_FREE_SDU_NUM(1);
        CDS_DBG_MODEM_DL_UMTS_DIRECT_FREE_SDU_NUM(enModemId,1);
        return;
    }

    /* ���ض��� */
    if(Fc_CdsDlPktDiscard(pstDlData->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        FC_DBG_DLGU_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_DL_UMTS_FC_FREE_SDU_NUM(1);
        CDS_DBG_MODEM_DL_UMTS_FC_FREE_SDU_NUM(enModemId,1);
        /*CDS_UP_EVENT_RPT(CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD);*/
        return;
    }

    /*��������ͳ��*/
    CDS_DLDataFlowStats(pstDlData->ucRabId,pstDlData->ulSduLen,pstCdsEntity);

    /*���ȱʡPDP����ID*/
    if (PS_SUCC != CDS_GUGetDefaultRabId(pstDlData->ucRabId,&ucDeftRabId,enModemId))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        CDS_DBG_DL_UMTS_GET_DEFT_RABID_FAIL(1);
        return;
    }

    /*���浱ǰ��Ϣ*/
    pstIpPkt = pstDlData->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstDlData->ulSduLen,
                                         enModemId,
                                         ucDeftRabId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_UMTS_ENQUE_FAIL_NUM(1);
        CDS_DBG_MODEM_DL_UMTS_ENQUE_FAIL_NUM(enModemId,1);
        return;
    }

    CDS_DBG_DL_UMTS_ENQUE_SUCC_NUM(1);
    CDS_DBG_MODEM_DL_UMTS_ENQUE_SUCC_NUM(enModemId,1);
    return;
}


VOS_VOID CDS_GSM_RxSdu(CDS_RABM_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    TTF_MEM_ST            *pstIpPkt;
    CDS_ENTITY_STRU       *pstCdsEntity;
    CDS_LB_DL_SDU_STRU     stLbSdu;
    VOS_UINT8              ucDeftRabId;
    CDS_IMS_SDU_STRU       stImsSdu;

    /*����ж�*/
    if (PS_SUCC != CDS_GUDlSduParaCheck(pstDlData))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GSM_DL_DataInd : Sdu Para Error.");
        CDS_PRINT_ERROR(CDS_GSM_RxSdu_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GSM_DL_DataInd : Input ModemId Error.ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_GSM_RxSdu_ENUM, CDS_PRINT_MODEM_ID_ERR, enModemId);
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        return;
    }

    CDS_DBG_DL_GSM_RX_SDU_NUM(1);
    CDS_DBG_MODEM_DL_GSM_RX_SDU_NUM(enModemId,1);

    /* ����ͳ�� */
    CDS_DLFlowAdd(pstDlData->ulSduLen);

    /*IMS*/
    if (PS_TRUE == CDS_IsImsBearer(pstDlData->ucRabId, pstCdsEntity))
    {
        stImsSdu.ucRabId  = pstDlData->ucRabId;
        stImsSdu.ucDrbId  = 0;
        stImsSdu.ulSduLen = pstDlData->ulSduLen;
        stImsSdu.pstSdu   = pstDlData->pstSdu;
        CDS_DlProcImsData(&stImsSdu, pstCdsEntity);
        CDS_DBG_DL_GSM_RX_IMS_PKT_NUM(1);
        CDS_DBG_MODEM_DL_GSM_RX_IMS_PKT_NUM(enModemId,1);
        /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
        CDS_BstSendRxInd();
        return;
    }
    /*BASTET*/
    if(PS_TRUE == CDS_GU_BstProcDlData(pstDlData, enModemId))
    {
        return;
    }
    /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
    CDS_BstSendRxInd();
    /*����ģʽ*/
    if ((PS_TRUE == pstCdsEntity->ulTestModeFlg) && (CDS_LB_STATE_START == pstCdsEntity->ulLoopBackState))
    {
        stLbSdu.ulSduLen = pstDlData->ulSduLen;
        stLbSdu.pstSdu   = pstDlData->pstSdu;
        CDS_RxLoopBackPkt(&stLbSdu,pstCdsEntity);

        CDS_DBG_LB_DL_RX_SDU_FROM_GSM(1);
        CDS_DBG_MODEM_ID_LB_DL_RX_SDU_FROM_GSM(enModemId,1);
        return;
    }

    /* ���ض��� */
    if(Fc_CdsDlPktDiscard(pstDlData->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        FC_DBG_DLGU_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_DL_GSM_FC_FREE_SDU_NUM(1);
        CDS_DBG_MODEM_DL_GSM_FC_FREE_SDU_NUM(enModemId,1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD);
        return;
    }

    /*��������ͳ��*/
    CDS_DLDataFlowStats(pstDlData->ucRabId,pstDlData->ulSduLen,pstCdsEntity);

    /*���ȱʡPDP����ID*/
    if (PS_SUCC != CDS_GUGetDefaultRabId(pstDlData->ucRabId,&ucDeftRabId,enModemId))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        CDS_DBG_DL_GSM_GET_DEFT_RABID_FAIL(1);
        return;
    }

    /*���浱ǰ��Ϣ*/
    pstIpPkt = pstDlData->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstDlData->ulSduLen,
                                         enModemId,
                                         ucDeftRabId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_GSM_ENQUE_FAIL_NUM(1);
        CDS_DBG_MODEM_DL_GSM_ENQUE_FAIL_NUM(enModemId,1);
        return;
    }

    CDS_DBG_DL_GSM_ENQUE_SUCC_NUM(1);
    CDS_DBG_MODEM_DL_GSM_ENQUE_SUCC_NUM(enModemId,1);

    return;
}


VOS_VOID CDS_GSM_DL_DataInd(CDS_RABM_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_GSM_RxSdu(pstDlData, enModemId);

    if (0 != LUP_QueCnt(CDS_GET_IPF_DL_SDU_QUE()))
    {
        CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
        CDS_DBG_DL_SDU_TRIGGER_EVENT_NUM(1);
    }

    return;
}


VOS_VOID CDS_LTE_RecvDbgData(TTF_MEM_ST *pstIpPkt)
{
    CDS_ENTITY_STRU       *pstCdsEntity;

    if (VOS_NULL_PTR == pstIpPkt)
    {
        return;
    }

    CDS_DBG_DL_LTE_DBG_PKT_HOOK(pstIpPkt);

    /*LTEĬ�Ϸ���Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
        return;
    }

    CDS_DBG_DL_LTE_RX_DBG_PKT_NUM(1);

    /*�����Ҫ��Ϣ*/
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstIpPkt->usUsed,
                                         MODEM_ID_0,
                                         pstCdsEntity->ucDbgBearerId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(1);
        return;
    }

    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_SDU_TRIGGER_EVENT_NUM(1);
    CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(1);
    return;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
extern VOS_VOID L2_DlAppThrStatProc(VOS_UINT32 ulLength);
VOS_VOID CDS_LTE_DL_DataInd(CDS_LPDCP_DATA_STRU *pstDsLpdcpData)
{
    TTF_MEM_ST            *pstIpPkt;
    VOS_UINT8              ucDeftEpsbID;
    VOS_UINT8              ucEpsbID;
    CDS_ENTITY_STRU       *pstCdsEntity;
    CDS_LB_DL_SDU_STRU     stLbSdu;
    CDS_IMS_SDU_STRU       stImsSdu;

    CDS_ASSERT(VOS_NULL_PTR != pstDsLpdcpData);

    /*LTEĬ�Ϸ���Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS, pstDsLpdcpData->pstSdu);
        return;
    }

    CDS_DBG_DL_LTE_RX_SDU_NUM(1);

    /* ����ͳ�� */
    CDS_DLFlowAdd(pstDsLpdcpData->ulSduLen);

    /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
    CDS_DBG_DL_REC_IP_PKT_INFO(pstDsLpdcpData->pstSdu);
    CDS_DBG_DL_LTE_IP_PKT_HOOK(pstDsLpdcpData->pstSdu);

    /*���ܲ��ԣ��ڴ�ֱ���ͷ�*/
    if (PS_TRUE == pstCdsEntity->ulDLPktDiscardFlg)
    {
        TTF_MemFree(UEPS_PID_CDS, pstDsLpdcpData->pstSdu);
        CDS_DBG_DL_LTE_DIRECT_FREE_SDU_NUM(1);
        return;
    }

    /*����ģʽ*/
    if ((PS_TRUE == pstCdsEntity->ulTestModeFlg) && (CDS_LB_STATE_START == pstCdsEntity->ulLoopBackState))
    {
        stLbSdu.ulSduLen = pstDsLpdcpData->ulSduLen;
        stLbSdu.pstSdu   = pstDsLpdcpData->pstSdu;
        CDS_RxLoopBackPkt(&stLbSdu,pstCdsEntity);
        CDS_DBG_LB_DL_RX_SDU_FROM_LTE(1);
        CDS_BstSendRxInd();
        return;
    }

    /*���DRB��Ӧ��EpsbIDʧ��.��������ͳ��*/
    if (PS_SUCC != CDS_ERABM_GetEpsbId(pstDsLpdcpData->ucRbId,&ucEpsbID))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDsLpdcpData->pstSdu);
        CDS_DBG_DL_LTE_GET_EPSBID_FAIL(1);
        return;
    }

    /*IMS*/
    if (PS_TRUE == CDS_IsImsBearer(ucEpsbID, pstCdsEntity))
    {
        stImsSdu.ucRabId  = ucEpsbID;
        stImsSdu.ucDrbId  = pstDsLpdcpData->ucRbId;
        stImsSdu.ulSduLen = pstDsLpdcpData->ulSduLen;
        stImsSdu.pstSdu   = pstDsLpdcpData->pstSdu;
        CDS_DlProcImsData(&stImsSdu, pstCdsEntity);
        CDS_DBG_DL_LTE_RX_IMS_PKT_NUM(1);
        /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
        CDS_BstSendRxInd();
        return;
    }

    /*BASTET*/
    if(PS_TRUE == CDS_LTE_BstProcDlData(pstDsLpdcpData,ucEpsbID))
    {
        return;
    }
    /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
    CDS_BstSendRxInd();

    /* ���ض��� */
    if(Fc_CdsDlPktDiscard(ucEpsbID))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDsLpdcpData->pstSdu);
        FC_DBG_DLLTE_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_DL_LTE_FC_FREE_SDU_NUM(1);
        /*CDS_UP_EVENT_RPT(CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD);*/
        return;
    }

    /*��������ͳ��*/
    CDS_DLDataFlowStats(ucEpsbID,pstDsLpdcpData->ulSduLen,pstCdsEntity);

    L2_DlAppThrStatProc(pstDsLpdcpData->ulSduLen);

    /*���ȱʡEPS����ID*/
    if (PS_SUCC != CDS_ERABM_GetDefaultEpsbId(pstDsLpdcpData->ucRbId,&ucDeftEpsbID))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDsLpdcpData->pstSdu);
        CDS_DBG_DL_LTE_GET_DEFT_EPSBID_FAIL(1);
        return;
    }

    /*�����Ҫ��Ϣ*/
    pstIpPkt = pstDsLpdcpData->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstDsLpdcpData->ulSduLen,
                                         MODEM_ID_0,
                                         ucDeftEpsbID);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(1);
        return;
    }

    CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(1);
    return;
}


VOS_VOID CDS_MBMS_DL_DataInd(TTF_MEM_ST *pstSdu)
{
    CDS_ENTITY_STRU       *pstCdsEntity;

    if (VOS_NULL_PTR == pstSdu)
    {
        return;
    }

    /*LTEĬ�Ϸ���Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS, pstSdu);
        return;
    }

    CDS_DBG_DL_LTE_RX_MBMS_SDU_NUM(1);

    /*�����Ҫ��Ϣ*/
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstSdu,
                                         pstSdu->usUsed,
                                         MODEM_ID_0,
                                         pstCdsEntity->ucMbmsBearerId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstSdu))
    {
        CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(1);
        return;
    }

    CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(1);

    /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
    CDS_DBG_DL_REC_IP_PKT_INFO(pstSdu);
    CDS_DBG_DL_LTE_IP_PKT_HOOK(pstSdu);

    return;
}


#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 �� �� ��  : CDS_CDMADlSduParaCheck
 ��������  : CDMA����SDU�������

 �������  : CDS_CDMA_TRANS_DATA_STRU *pstDlData
 �������  : ��
 �� �� ֵ  : PS_SUCC : ������Ч
             PS_FAIL : ������Ч
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��31��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CDS_CDMADlSduParaCheck(CDS_CDMA_TRANS_DATA_STRU *pstDlData)
{

    if (VOS_NULL_PTR == pstDlData)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_CDMADlSduParaCheck : Input Null Para.");
        CDS_PRINT_ERROR(CDS_CDMADlSduParaCheck_ENUM, LL2_PARA_CHECK_FAIL);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == pstDlData->pstSdu)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_CDMADlSduParaCheck : Sdu Ptr Is NULL.");
        CDS_PRINT_ERROR(CDS_CDMADlSduParaCheck_ENUM, CDS_PRINT_SDU_PTR_NULL);
        return PS_FAIL;
    }

    if ((0 == pstDlData->ulSduLen) || (CDS_DL_SDU_MAX_LEN < pstDlData->ulSduLen))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_CDMADlSduParaCheck : SDU Too Big.",pstDlData->ulSduLen);
        CDS_PRINT_ERROR1(CDS_CDMADlSduParaCheck_ENUM, CDS_PRINT_SDU_TOO_BIG,pstDlData->ulSduLen);
        return PS_FAIL;
    }

    if ((CDS_MIN_PDN_ID > pstDlData->ucPdnId) || (CDS_MAX_PDN_ID < pstDlData->ucPdnId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_CDMADlSduParaCheck : Input RabId Fail.RabID=",pstDlData->ucPdnId);
        CDS_PRINT_ERROR1(CDS_CDMADlSduParaCheck_ENUM, CDS_PRINT_RAB_ID_ERR,pstDlData->ucPdnId);
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : CDS_CDMA_DL_DataInd
 ��������  : ����CDMA�������ݰ�.�ɵ����߱�֤��κϷ���
 �������  : CDS_CDMA_TRANS_DATA_STRU *pstDlData
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_CDMA_DL_DataInd(CDS_CDMA_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_ENTITY_STRU                               *pstCdsEntity;
    TTF_MEM_ST                                    *pstIpPkt;
    VOS_UINT8                                      ucRabId;

    /*����ж�*/
    if (PS_SUCC != CDS_CDMADlSduParaCheck(pstDlData))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_CDMA_DL_DataInd : Sdu Para Error.");
        CDS_PRINT_ERROR(CDS_CDMA_DL_DataInd_ENUM, CDS_PRINT_SDU_PTR_NULL);
        return;
    }

    ucRabId = TAF_APS_MapPdnIdToRabId(pstDlData->ucPdnId);
    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_PRINT_ERROR1(CDS_CDMA_DL_DataInd_ENUM, CDS_PRINT_RAB_ID_ERR, ucRabId);
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        return;
    }

    /*����ModemId��ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_CDMA_DL_DataInd : Input ModemId Error.ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_CDMA_DL_DataInd_ENUM, CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        return;
    }

    CDS_DBG_DL_CDMA_RX_SDU_NUM(pstCdsEntity->enRanMode,1);
    CDS_DBG_MODEM_DL_CDMA_RX_SDU_NUM(enModemId,pstCdsEntity->enRanMode,1);

    /* ����ͳ�� */
    CDS_DLFlowAdd(pstDlData->ulSduLen);

    /*���ܲ��ԣ��ڴ�ֱ���ͷ�*/
    if (PS_TRUE == pstCdsEntity->ulDLPktDiscardFlg)
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        CDS_DBG_DL_CDMA_DIRECT_FREE_SDU_NUM(pstCdsEntity->enRanMode,1);
        CDS_DBG_MODEM_DL_CDMA_DIRECT_FREE_SDU_NUM(enModemId,pstCdsEntity->enRanMode,1);
        return;
    }

    /* ���ض��� */
    if(Fc_CdsDlPktDiscard(ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS, pstDlData->pstSdu);
        FC_DBG_DLCDMA_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_DL_CDMA_FC_FREE_SDU_NUM(pstCdsEntity->enRanMode,1);
        CDS_DBG_MODEM_DL_CDMA_FC_FREE_SDU_NUM(enModemId,pstCdsEntity->enRanMode,1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD);
        return;
    }

    /*��������ͳ��*/
    CDS_DLDataFlowStats(ucRabId,pstDlData->ulSduLen,pstCdsEntity);

    /*�����Ҫ��Ϣ*/
    pstIpPkt = pstDlData->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstDlData->ulSduLen,
                                         enModemId,
                                         ucRabId);

    /*���*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_CDMA_ENQUE_FAIL_NUM(pstCdsEntity->enRanMode,1);
        CDS_DBG_MODEM_DL_CDMA_ENQUE_FAIL_NUM(enModemId,pstCdsEntity->enRanMode,1);
        return;
    }

    CDS_DBG_DL_CDMA_ENQUE_SUCC_NUM(pstCdsEntity->enRanMode,1);
    CDS_DBG_MODEM_DL_CDMA_ENQUE_SUCC_NUM(enModemId,pstCdsEntity->enRanMode,1);
    return;

}

/*****************************************************************************
 �� �� ��  : CDS_CDMA_DL_DataInd
��������  : ����CDMA 1X�������ݰ�.�ɵ����߱�֤��κϷ���
 �������  : CDS_CDMA_TRANS_DATA_STRU *pstDlData
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_CDMA_1X_DL_DataInd(const CDS_CDMA_1X_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_CDMA_TRANS_DATA_STRU                  stCdmaDlData = {0};

    if (VOS_NULL_PTR == pstDlData)
    {
        return;
    }

    stCdmaDlData.ucPdnId  = pstDlData->ucPdnId;
    stCdmaDlData.ulSduLen = pstDlData->ulSduLen;
    stCdmaDlData.pstSdu   = pstDlData->pstSdu;

    CDS_CDMA_DL_DataInd(&stCdmaDlData, enModemId);

    return;

}

/*****************************************************************************
 �� �� ��  : CDS_CDMA_DL_DataInd
 ��������  : ����CDMA HRPD�������ݰ�.�ɵ����߱�֤��κϷ���
 �������  : CDS_CDMA_TRANS_DATA_STRU *pstDlData
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_CDMA_HRPD_DL_DataInd(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_CDMA_TRANS_DATA_STRU                  stCdmaDlData = {0};

    if (VOS_NULL_PTR == pstDlData)
    {
        return;
    }

    stCdmaDlData.ucPdnId  = pstDlData->ucPdnId;
    stCdmaDlData.ulSduLen = pstDlData->ulSduLen;
    stCdmaDlData.pstSdu   = pstDlData->pstSdu;

    CDS_CDMA_DL_DataInd(&stCdmaDlData, enModemId);

    return;

}

#endif


VOS_VOID CDS_SetDfsMax(VOS_VOID)
{
    TAF_APS_SetDfsMax();
    return;
}


VOS_UINT32 CDS_GetDlSduQueCnt(VOS_VOID)
{
    return LUP_QueCnt(CDS_GET_IPF_DL_SDU_QUE());
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

