


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"
#include "CdsMsgProc.h"
#include "CdsUlProc.h"
#include "CdsSoftFilter.h"
#include "CdsImsProc.h"
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#include "CdsBastetProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_ENTITY_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/
extern VOS_VOID Fc_LteInit(VOS_VOID);
extern VOS_VOID QosFc_Init(VOS_VOID);
extern VOS_VOID CDS_ClearIpFragBuff(VOS_VOID);

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
VOS_UINT32                         g_ulCdsTaskId         = 0;   /*CDS����ID*/
VOS_UINT32                         g_ulCdsTaskReadyFlag  = 0;   /*CDS��������״̬*/
CDS_ENTITY_STRU                    g_astCdsEntity[CDS_MAX_MODEM_NUM]; /*CDS����ʵ��*/

#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32  g_ulCdsStFlg = PS_FALSE;

    /*PC STʹ��,g_ulCdsStFlg��ST�����д�*/
    #define  CDS_ST_TMR_START(pHTIMER)      \
             if (PS_TRUE == g_ulCdsStFlg)   \
             {                              \
                (pHTIMER) = (HTIMER)0xffff; \
                return PS_SUCC;             \
             }
    #define  CDS_ST_TMR_STOP(pHTIMER)       \
             if (PS_TRUE == g_ulCdsStFlg)   \
             {                              \
                (pHTIMER) = 0;              \
                return;                     \
             }
#else
    #define  CDS_ST_TMR_START(pHTIMER)
    #define  CDS_ST_TMR_STOP(pHTIMER)
#endif

/******************************************************************************
   5 ����ʵ��
******************************************************************************/


CDS_ENTITY_STRU* CDS_GetCdsEntity(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= CDS_MAX_MODEM_NUM)
    {
        return VOS_NULL_PTR;
    }

    return &(g_astCdsEntity[enModemId]);
}



VOS_VOID CDS_TimerInit (CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_TIMER_STRU          *pstTmr;

    /*NULLģʽ��10�����Զ�ʱ��*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_DL_10MS_PERIODIC_TMR]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_DL_10MS_PERIODIC_TMR;
    pstTmr->ulTmrLen  = CDS_TMR_LEN;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    /*����ģʽB��ʱ��*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_LB_MODE_B_TMR]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_LB_MODE_B_TMR;
    pstTmr->ulTmrLen  = 0;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    /*�������ݱ�����ʱ��*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_UL_DATA_PROCTECT]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_UL_DATA_PROCTECT;
    pstTmr->ulTmrLen  = CDS_UL_DATA_PROTECT_TMR_LEN;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    return;
}
VOS_UINT32 CDS_StartTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId)
{
    CDS_TIMER_STRU          *pstTmr;
    VOS_INT32                lLock;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*����ж�*/
    if (ulTmrId >= CDS_TMR_ID_MODEM_BUTT)
    {
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_StartTimer : Input ulTmrId Error.",ulTmrId);
        CDS_PRINT_INFO1(CDS_StartTimer_ENUM, CDS_PRINT_TIMER_ID_ERROR, ulTmrId);
        return PS_FAIL;
    }

    /*��ö�ʱ���ṹ��ָ��*/
    pstTmr = &(pstCdsEntity->astTimer[ulTmrId]);

    /*������*/
    if (VOS_NULL_PTR != pstTmr->pstTmrHdr)
    {
        return PS_SUCC;
    }

    /*������ʱ��*/
    lLock = VOS_SplIMP();
    if (VOS_OK != PS_START_REL_TIMER(&(pstTmr->pstTmrHdr),
                                    UEPS_PID_CDS,
                                    pstTmr->ulTmrLen,
                                    ulTmrId,
                                    pstTmr->ulPara,
                                    VOS_RELTIMER_NOLOOP))
    {
        VOS_Splx(lLock);
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StartTimer : Start Tmr Fail.",pstCdsEntity->usModemId,ulTmrId);
        CDS_PRINT_ERROR2(CDS_StartTimer_ENUM,CDS_PRINT_START_TIMER_FAIL,pstCdsEntity->usModemId,ulTmrId);
        return PS_FAIL;
    }
    VOS_Splx(lLock);

    /*CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StartTimer : Start Timer Succ.",pstCdsEntity->usModemId,ulTmrId);*/
    return PS_SUCC;
}
VOS_VOID CDS_StopTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId)
{
    CDS_TIMER_STRU          *pstTmr;
    VOS_INT32                lLock;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*����ж�*/
    if (ulTmrId >= CDS_TMR_ID_MODEM_BUTT)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StopTimer : Timer ID Error.",ulTmrId);
        CDS_PRINT_ERROR1(CDS_StopTimer_ENUM,CDS_PRINT_TIMER_ID_ERROR,ulTmrId);
        return;
    }

    /*��ö�ʱ���ṹ��ָ��*/
    pstTmr = &(pstCdsEntity->astTimer[ulTmrId]);

    /*��ֹͣ*/
    if (VOS_NULL_PTR == pstTmr->pstTmrHdr)
    {
        return ;
    }

    /*ֹͣ��ʱ��*/
    lLock = VOS_SplIMP();
    if (VOS_OK != PS_STOP_REL_TIMER(&(pstTmr->pstTmrHdr)))
    {
        VOS_Splx(lLock);
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StopTimer : Stop Tmr Fail.",pstCdsEntity->usModemId,ulTmrId);
        CDS_PRINT_ERROR2(CDS_StartTimer_ENUM,CDS_PRINT_STOP_TIMER_FAIL,pstCdsEntity->usModemId,ulTmrId);
        return;
    }
    VOS_Splx(lLock);

    /*CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StopTimer : Stop Tmr Succ.",pstCdsEntity->usModemId,ulTmrId);*/
    return ;
}
VOS_VOID CDS_ProcLoopBackQue(CDS_ENTITY_STRU  *pstCdsEntity)
{
    VOS_UINT32          ulCnt;
    TTF_MEM_ST         *pstIpPkt;
    VOS_UINT16          usResult;

    /*�������ض���*/
    for (ulCnt = 0; ulCnt < CDS_LB_QUE_SIZE; ulCnt ++)
    {
        /*����*/
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstLBModeBQue,(VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        /*��������˽ӿ�*/
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_LB_UL_SOFT_FILTER_FAIL_NUM(1);
            continue;
        }

        /*�����˽���浽TTF��*/
        CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usResult);

        /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt);

        /*��ģʽ�ַ�*/
        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);

        /*���Ӽ���*/
        CDS_DBG_LB_UL_SEND_PKT_NUM(1);
    }

    return;
}
VOS_VOID CDS_ClearLoopBackQue(const CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST      *pstIpPkt;
    VOS_UINT32       ulCnt;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    for (ulCnt = 0; ulCnt < CDS_LB_QUE_SIZE; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstLBModeBQue,(VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
        CDS_DBG_LB_UL_CLEAR_PKT_NUM(1);
    }

    return;
}


VOS_VOID CDS_RxLoopBackPkt(CDS_LB_DL_SDU_STRU *pstDlData, CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST            *pstDstTtf;
    VOS_INT32              lLock;

    /*�ǻ���ģʽBֱ���ͷ�*/
    if (CDS_LB_MODE_B != pstCdsEntity->ulLoopBackMode)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_DBG_LB_DL_RX_SDU_IN_NO_MODE_B(1);
        return;
    }

    /*����Ŀ���ڴ�*/
    pstDstTtf = CDS_AllocTtfMem(pstDlData->ulSduLen);
    if (VOS_NULL_PTR == pstDstTtf)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_DBG_LB_DL_ALLOC_MEM_FAIL(1);
        return;
    }

    /*�����ڴ濽��*/
    if (PS_SUCC != TTF_MemGetHeadData(  UEPS_PID_CDS,
                                        pstDlData->pstSdu,
                                        pstDstTtf->pData,
                                        (VOS_UINT16)(pstDlData->ulSduLen)))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        TTF_MemFree(UEPS_PID_CDS,pstDstTtf);
        return;
    }

    /*�ͷ�Դ�ڴ�*/
    TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);

    /*���ֱ�Ҫ��Ϣ����׮����:ModemId=0,RabId=5*/
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstDstTtf,
                                             pstCdsEntity->ucLBDefBearerId,
                                             MODEM_ID_0,
                                             pstCdsEntity->ucLBDefBearerId);

    /*���*/
    lLock = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstLBModeBQue,pstDstTtf))
    {
        VOS_Splx(lLock);
        TTF_MemFree(UEPS_PID_CDS,pstDstTtf);
        CDS_DBG_LB_DL_ENQUE_FAIL_NUM(1);
        return;
    }
    VOS_Splx(lLock);

    /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
    CDS_DBG_DL_REC_IP_PKT_INFO(pstDstTtf);
    CDS_DBG_DL_LTE_IP_PKT_HOOK(pstDstTtf);

    CDS_DBG_LB_DL_ENQUE_SUCC_NUM(1);

    /*�������ض�ʱ��*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity, CDS_TMR_ID_LB_MODE_B_TMR))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RxLoopBackPkt : Start LB Mode B Timer Fail.");
        CDS_PRINT_ERROR(CDS_RxLoopBackPkt_ENUM,CDS_PRINT_START_TIMER_FAIL);
        return;
    }

    return;
}


VOS_VOID CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{
    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_LoopBackModeBTimeoutProc");
    CDS_PRINT_INFO(CDS_LoopBackModeBTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*����ж�*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*���ݲ�����ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*ֹͣ��ʱ��*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR);

    /*û�д��ڻ���״̬��ֱ�ӷ���*/
    if (PS_TRUE != pstCdsEntity->ulTestModeFlg)
    {
        CDS_ClearLoopBackQue(pstCdsEntity);
        return;
    }

    /*��ģʽB����ֱ�ӷ��أ�GU����ģʽ4ӳ�䵽CDS_LB_MODE_B*/
    if (CDS_LB_MODE_B != pstCdsEntity->ulLoopBackMode)
    {
        CDS_ClearLoopBackQue(pstCdsEntity);
        return;
    }

    /*������������*/
    CDS_ProcLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_LoopBackModeBTimeoutProc");
    CDS_PRINT_INFO(CDS_LoopBackModeBTimeoutProc_ENUM, LL2_FUNCTION_EXIT);
    return;
}


VOS_VOID CDS_Dl10msPeridicTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{
    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_Dl10msPeridicTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*����ж�*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*���ݲ�����ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*����SDU���п�*/
    if (PS_TRUE == LUP_IsQueEmpty(CDS_GET_IPF_DL_SDU_QUE()))
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_Dl10msPeridicTmrTimeoutProc : DL Sdu Empty Stop Timer.");
        CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, CDS_PRINT_DL_SDU_QUE_EMPTY);
        return;
    }

    if (PS_SUCC != CDS_StartTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR))
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_Dl10msPeridicTmrTimeoutProc : ReStart Timer Fail.");
        CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, CDS_PRINT_RESTART_TIMER_FAIL);
        return;
    }

    /*�����������ݻ������д����¼�*/
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_10MS_TMR_TRIG_EVENT(1);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_Dl10msPeridicTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}


VOS_VOID CDS_UlDataProtectTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{

    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_UlDataProtectTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_UlDataProtectTmrTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*����ж�*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*���ݲ�����ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_UlDataProtectTmrTimeoutProc : Get CDS Entity Fail.",pstTmrMsg->ulPara);
        CDS_PRINT_INFO1(CDS_UlDataProtectTmrTimeoutProc_ENUM, CDS_PRINT_GET_ENTITY_FAIL_MODEM_ID, pstTmrMsg->ulPara);
        return;
    }

    /*ֹͣ��ʱ��*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_UL_DATA_PROCTECT);

    /*���Service Request��־λ*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*�������л�������*/
    CDS_ClearUlBuffData(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_UlDataProtectTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_UlDataProtectTmrTimeoutProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}
CDS_BEARER_DATA_FLOW_STRU* CDS_GetBearerDataFlowPtr(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{

    /*����ж�*/
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstCdsEntity,VOS_NULL_PTR);

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Input RabId Fail.RabID=",ucRabId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowPtr_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return VOS_NULL_PTR;
    }

    return (CDS_BEARER_DATA_FLOW_STRU *)&(pstCdsEntity->stFlowStats.astBearerDS[ucRabId - CDS_NAS_MIN_BEARER_ID]);
}
VOS_VOID CDS_GetBearerDataFlowInfo(VOS_UINT8 ucRabId,CDS_BEARER_DATA_FLOW_STRU *pstDataFlowInfo, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_BEARER_DATA_FLOW_STRU    *pstLocalValue;
    CDS_ENTITY_STRU              *pstCdsEntity;

    if (VOS_NULL_PTR == pstDataFlowInfo)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Get CDS Entity Error. ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        PS_MEM_SET(pstDataFlowInfo,0,sizeof(CDS_BEARER_DATA_FLOW_STRU));
        return;
    }

    pstLocalValue = CDS_GetBearerDataFlowPtr(ucRabId,pstCdsEntity);
    if (VOS_NULL_PTR == pstLocalValue)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucRabId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        PS_MEM_SET(pstDataFlowInfo,0,sizeof(CDS_BEARER_DATA_FLOW_STRU));
        return;
    }

    pstDataFlowInfo->ulTotalReceiveFluxHigh = pstLocalValue->ulTotalReceiveFluxHigh;
    pstDataFlowInfo->ulTotalReceiveFluxLow  = pstLocalValue->ulTotalReceiveFluxLow;
    pstDataFlowInfo->ulTotalSendFluxHigh    = pstLocalValue->ulTotalSendFluxHigh;
    pstDataFlowInfo->ulTotalSendFluxLow     = pstLocalValue->ulTotalSendFluxLow;

    return;
}


VOS_VOID CDS_ClearBearerDataFlowInfo(VOS_UINT8 ucBearerId, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_BEARER_DATA_FLOW_STRU    *pstLocalValue;
    int                           intLockLevel;
    CDS_ENTITY_STRU              *pstCdsEntity;

    /*���CDSʵ��ָ��*/
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : Get CDS Entity Error. ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_ClearBearerDataFlowInfo_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        return;
    }

    /*��ó�������ͳ��ָ��*/
    pstLocalValue = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstLocalValue)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
        CDS_PRINT_ERROR1(CDS_ClearBearerDataFlowInfo_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    intLockLevel = VOS_SplIMP();
    pstLocalValue->ulTotalReceiveFluxHigh = 0;
    pstLocalValue->ulTotalReceiveFluxLow  = 0;
    pstLocalValue->ulTotalSendFluxHigh    = 0;
    pstLocalValue->ulTotalSendFluxLow     = 0;
    VOS_Splx(intLockLevel);

    return;
}


VOS_VOID CDS_DLDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_BEARER_DATA_FLOW_STRU   *pstBearerDFInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*��ó�������ͳ��ָ��*/
    pstBearerDFInfo = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstBearerDFInfo)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
        CDS_PRINT_ERROR1(CDS_DLDataFlowStats_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    /*������������ͳ��*/
    pstBearerDFInfo->ulTotalReceiveFluxLow += ulPktLen;

    /*��32bit��ת*/
    if (pstBearerDFInfo->ulTotalReceiveFluxLow < ulPktLen)
    {
        pstBearerDFInfo->ulTotalReceiveFluxHigh ++;
    }

    return;
}
VOS_VOID CDS_ULDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_BEARER_DATA_FLOW_STRU   *pstBearerDFInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*��ó�������ͳ��ָ��*/
    pstBearerDFInfo = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstBearerDFInfo)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
         CDS_PRINT_ERROR1(CDS_ULDataFlowStats_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    /*������������ͳ��*/
    pstBearerDFInfo->ulTotalSendFluxLow += ulPktLen;

    /*��32bit��ת*/
    if (pstBearerDFInfo->ulTotalSendFluxLow < ulPktLen)
    {
        pstBearerDFInfo->ulTotalSendFluxHigh ++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_DLThrDataFlowStats
 ��������  : CDS����ͳ��ֱͨͨ������,��LPDCP����
 �������  : VOS_UINT32 ulPktLen
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2015��09��15��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_LPDCP_DLThrDataFlowStats(VOS_UINT8 ucEpsbID,VOS_UINT32 ulPktLen)
{
    CDS_ENTITY_STRU       *pstCdsEntity;

    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    CDS_DLDataFlowStats(ucEpsbID, ulPktLen, pstCdsEntity);

    return;
}



VOS_VOID CDS_SendEventToCds(VOS_UINT32 ulEvent)
{
    if (1 == g_ulCdsTaskReadyFlag)
    {
        (VOS_VOID)VOS_EventWrite(g_ulCdsTaskId, ulEvent);
    }

    return;
}


VOS_VOID CDS_LPdcpWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_SDU_TRIGGER_EVENT_NUM(1);
    return;
}



VOS_VOID CDS_LSubFrmIntWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_LTE_1MS_INT_TRIG_EVENT(1);
    return;
}


VOS_VOID CDS_UmtsIntWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_UMTS_INT_TRIG_EVENT(1);
    return;
}

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 �� �� ��  : CDS_CDMA_WakeupCds
 ��������  : CDMA�����жϴ����¼�������CDS������������
 �������  :��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_CDMA_WakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_CDMA_INT_TRIG_EVENT(1);
    return;
}
#endif


VOS_VOID CDS_EventProc(VOS_UINT32 ulEvent)
{
    /*��������IPF����*/
    if (ulEvent & CDS_EVENT_UL_IPF_INT)
    {
        CDS_UlProcIpfResult();
        CDS_DBG_UL_PROC_IPF_INT_NUM(1);
    }
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    /*����BASTET����������IP��*/
    if (ulEvent & CDS_EVENT_UL_BASTET_PROC)
    {
        if(PS_TRUE == CDS_GetBastetSupportFlag())
        {
            CDS_UlProcBastetData();
            CDS_DBG_BST_UL_PROC_BST_EVENT_NUM(1);
        }
    }

#endif
    /*�������л���*/
    if (ulEvent & CDS_EVENT_DL_DATA_PROC)
    {
        CDS_ConfigDlIPF();
        CDS_DBG_DL_PROC_EVENT_NUM(1);
    }

    /*IMS Proc*/
    if (ulEvent & CDS_EVENT_UL_IMS_PROC)
    {
        CDS_UlProcImsData(MODEM_ID_0);
        CDS_DBG_IMS_UL_PROC_IMS_EVENT_NUM(1);
    }

    /*ADQ��*/
    if (ulEvent & CDS_EVENT_UL_ADQ_EMPTY)
    {
        CDS_AllocMemForAdq();
        CDS_DBG_UL_PROC_ADQ_EMPTY_INT_NUM(1);
    }

    return;
}
VOS_VOID CDS_EntityInit (VOS_VOID)
{
    VOS_UINT32               ulCnt;
    CDS_ENTITY_STRU         *pstCdsEntity;

    for (ulCnt = 0; ulCnt < CDS_MAX_MODEM_NUM; ulCnt ++)
    {
        pstCdsEntity = &(g_astCdsEntity[ulCnt]);
        /*����ModemId*/
        pstCdsEntity->usModemId = (VOS_UINT16)ulCnt;

        /*���û��ر�־λPS_FALSE,״̬ΪDeactive̬*/
        pstCdsEntity->ulTestModeFlg     = PS_FALSE;
        pstCdsEntity->ulLoopBackMode    = CDS_LB_MODE_BUTT;
        pstCdsEntity->ulLoopBackState   = CDS_LB_STATE_DEACTIVE;

        /*����Service Request״̬*/
        pstCdsEntity->ulServiceReqFlg   = PS_FALSE;

        /*����GU SR��־*/
        CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

        /*����ģʽ����ΪNULL*/
        pstCdsEntity->enRanMode = MMC_CDS_MODE_NULL;

        /*�������л������*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstUlDataQue),CDS_UL_IDLE_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create UL Idle Que Fail.\n");
            return;
        }

        /*�������ػ������*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstLBModeBQue),CDS_LB_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create Loop Back Que Fail.\n");
            return;
        }

        /*����IMS����*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstIMSDataQue),CDS_IMS_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create UL Idle Que Fail.\n");
            return;
        }

#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
        /*����BASTET����*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstBastetUlQue),CDS_BASTET_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create Bastet Que Fail.\n");
            return;
        }
#endif
        /*��ʱ����ʼ��*/
        CDS_TimerInit(pstCdsEntity);
        /*����IMS����������Ϣ�������������*/
        pstCdsEntity->ulImsBearerNum = 0;
        PS_MEM_SET(pstCdsEntity->astImsBearerInfo,0,sizeof(IMSA_CDS_IMS_BEARER_STRU) * IMSA_CDS_MAX_IMS_BEARER_NUM);
        pstCdsEntity->stImsPortInfo.usMaxImsPort = 0;
        pstCdsEntity->stImsPortInfo.usMinImsPort = 0;

        pstCdsEntity->ulUlSoftFilterNum = 0;
        PS_MEM_SET(pstCdsEntity->astUlSoftFilter,0, sizeof(CDS_SOFTFILTER_INFO_STRU) * CDS_MAX_SOFT_FILTER_NUM);

        /*������غų�ʼ����ȫ����ʼ��Ϊ5*/
        pstCdsEntity->ucMbmsBearerId        = CDS_NAS_MIN_BEARER_ID;
        pstCdsEntity->ucDbgBearerId         = CDS_NAS_MIN_BEARER_ID;
        pstCdsEntity->ucLBDefBearerId       = CDS_NAS_MIN_BEARER_ID;

        /*�������������ж�������*/
        pstCdsEntity->ulULPktDiscardFlg = PS_FALSE;
        pstCdsEntity->ulDLPktDiscardFlg = PS_FALSE;

        CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    }

    return ;
}
STATIC VOS_UINT32 CDS_PidInit (enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
        /* 1. ��ȫ�ֱ���ʹ�õ�ȫ���ڴ����봦�� */
            CDS_ClearIpFragBuff();

        /* 2. ȫ�ֱ�����ʼ ���ڳ�ʼ���漰��TCM�������Ƶ�HpaMsgProc.c��DSP��ʼ������ڵ��øú���*/
            CDS_EntityInit();

            if (PS_SUCC != CDS_IpfInit())
            {
                PS_PRINTF("CDS_PidInit : Init IPF Fail\r\n");
                return PS_FAIL;
            }

            /* ���س�ʼ�� */
            Fc_LteInit();
            QosFc_Init();

        /* 3. ��ʱ����ʼ������ */

        /* 4. ��ʱ���Ǽ� */

        /* 5. ״̬���Ǽ�, */

        /* 6. ȫ�ֿ��ر�����ʼ������ */

        /* 7. ����ģ���ʼ���������� */

        /* 8. OTHERS��ʼ������ִ�� */
        #if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
            CDS_BstInit();
        #endif
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return PS_SUCC;
}


/*lint -e715*/
#if (VOS_OS_VER == VOS_WIN32)


VOS_VOID CDS_FidTask(VOS_UINT32 ulQueueID, VOS_UINT32 FID_value,
                                     VOS_UINT32 Para1, VOS_UINT32 Para2)
{
    MsgBlock       *pMsg              = VOS_NULL_PTR;
    VOS_UINT32      ulEvent           = 0;
    VOS_UINT32      ulTaskID          = 0;
    VOS_UINT32      ulEventMask       = 0;
    VOS_UINT32      ulExpectEvent     = 0;

    ulTaskID = VOS_GetCurrentTaskID();

    if (PS_NULL_UINT32 == ulTaskID)
    {
        PS_PRINTF("CDS ERROR, reg Msg Func \r\n");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        PS_PRINTF("CDS ERROR, Create Event Fail \r\n");
        return;
    }

    g_ulCdsTaskId           = ulTaskID;
    g_ulCdsTaskReadyFlag    = 1;

    ulExpectEvent           = CDS_EVENT_UL_IPF_INT | CDS_EVENT_DL_DATA_PROC | CDS_EVENT_UL_ADQ_EMPTY
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
                              | CDS_EVENT_UL_IMS_PROC | CDS_EVENT_UL_BASTET_PROC | VOS_MSG_SYNC_EVENT;
#else
                              | CDS_EVENT_UL_IMS_PROC | VOS_MSG_SYNC_EVENT;
#endif
    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while(1)
    /*lint +e716*/
    {
        if (VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent))
        {
            PS_PRINTF("CDS Read Event Error .\r\n");
            continue;
        }

        /*�¼�����*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            CDS_EventProc(ulEvent);
            continue;
        }

        /*��Ϣ����*/
        pMsg = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            switch(TTF_GET_MSG_RECV_PID(pMsg))
            {
            case UEPS_PID_CDS:
                CDS_RecvMsgProc(pMsg);
                break;
            default:
                PS_PRINTF("CDS Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg));
                break;
            }

            VOS_SysFreeMsg(pMsg);
        }
    }

}


#else

VOS_VOID CDS_FidTask(VOS_UINT32 ulQueueID, VOS_UINT32 FID_value,
                                     VOS_UINT32 Para1, VOS_UINT32 Para2)
{
    MsgBlock       *pMsg              = VOS_NULL_PTR;
    VOS_UINT32      ulEvent           = 0;
    VOS_UINT32      ulTaskID          = 0;
    VOS_UINT32      ulEventMask       = 0;
    VOS_UINT32      ulExpectEvent     = 0;

    ulTaskID = VOS_GetCurrentTaskID();

    if (PS_NULL_UINT32 == ulTaskID)
    {
        PS_PRINTF("CDS ERROR, reg Msg Func \r\n");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        PS_PRINTF("CDS ERROR, Create Event Fail \r\n");
        return;
    }

    g_ulCdsTaskId           = ulTaskID;
    g_ulCdsTaskReadyFlag    = 1;

    ulExpectEvent           = CDS_EVENT_UL_IPF_INT | CDS_EVENT_DL_DATA_PROC | CDS_EVENT_UL_ADQ_EMPTY
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
                              | CDS_EVENT_UL_BASTET_PROC
#endif
                              | CDS_EVENT_UL_IMS_PROC |VOS_MSG_SYNC_EVENT;

    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    for(;;)
    /*lint +e716*/
    {
        if (VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent))
        {
            PS_PRINTF("CDS Read Event Error .\r\n");
            continue;
        }

        /*�¼�����*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            CDS_EventProc(ulEvent);
            continue;
        }

        /*��Ϣ����*/
        pMsg = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            switch(TTF_GET_MSG_RECV_PID(pMsg))
            {
            case UEPS_PID_CDS:
                CDS_RecvMsgProc(pMsg);
                break;
            default:
                PS_PRINTF("CDS Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg));
                break;
            }

            PS_FREE_MSG(UEPS_PID_CDS,pMsg);
        }
    }

}

#endif
/*lint +e715*/

VOS_UINT32 CDS_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32   ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            /* MAC UL PID��ʼ��*/
            ulResult = VOS_RegisterPIDInfo(UEPS_PID_CDS,
                                CDS_PidInit,
                                CDS_RecvMsgProc);
            if (PS_SUCC != ulResult)
            {
                return (VOS_UINT32)PS_FAIL;
            }

            ulResult = VOS_RegisterMsgTaskEntry(UEPS_FID_CDS, (VOS_VOIDFUNCPTR)CDS_FidTask);

            if (PS_SUCC != ulResult)
            {
                PS_PRINTF("LUEPS_FID_CDS Reg msg routine FAIL!,ulRslt\n", ulResult);
                return (VOS_UINT32)PS_FAIL;
            }

            /*ͬLRLCMAC_DL�������ȼ���ͬ*/
            ulResult = VOS_RegisterMsgTaskPrio(UEPS_FID_CDS, VOS_PRIORITY_P3);

            if( PS_SUCC != ulResult )
            {
                PS_PRINTF("Error: UEPS_FID_CDS VOS_RegisterMsgTaskPrio failed!");
                return (VOS_UINT32)PS_FAIL;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

