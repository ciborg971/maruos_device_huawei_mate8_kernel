


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
#include "CdsUlProc.h"
#include "CdsDebug.h"
#include "CdsMsgProc.h"
#include "CdsInterface.h"
#include "QosFcOm.h"
#include "CdsSoftFilter.h"
#include "CdsBastetProc.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_UL_PROC_C
/*lint +e767*/

extern VOS_UINT32 CDS_IpFragmentProc( VOS_UINT8       *pucEpsbID,
                                          TTF_MEM_ST      *pstIpPkt,
                                          const IPF_RESULT_STRU *pstIpfRslt,
                                          const CDS_ENTITY_STRU  *pstCdsEntity);

extern VOS_VOID CDS_LPDCP_TriggerUlDataProc(VOS_VOID);

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


/*lint -e960*/

VOS_VOID CDS_ULStorePkt(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    /*IP���������л������*/
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue, pstIpPkt))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_BUFF_EN_QUE_FAIL_NUM(1);
        return;
    }

    CDS_DBG_UL_BUFF_EN_QUE_SUCC_NUM(1);

    /*����������ʱ��*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_ULStorePkt : Start UL DATA PROCTECT timer Fail.Modem Id",pstCdsEntity->usModemId);
        CDS_PRINT_ERROR1(CDS_ULStorePkt_ENUM,CDS_PRINT_START_TIMER_FAIL,pstCdsEntity->usModemId);
        return;
    }

    return;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)

extern VOS_VOID L2_UlAppThrStatProc(VOS_UINT32 ulLength);
VOS_VOID CDS_UlLteDispatchData(VOS_UINT8 ucEpsbID,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT8                                 ucDrbId;
    CDS_ERABM_TRANSFER_RESULT_ENUM_UINT32     enERabmStatus;
    CDS_LPDCP_DATA_STRU                       stLPdcpData;

    CDS_ASSERT((ucEpsbID >= CDS_NAS_MIN_BEARER_ID)&&(ucEpsbID <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    L2_UlAppThrStatProc(pstIpPkt->usUsed);

    /*DRB ״̬*/
    enERabmStatus = CDS_ERABM_GetDrbId(ucEpsbID,&ucDrbId);
    switch(enERabmStatus)
    {
    case CDS_ERABM_TRANSFER_RESULT_SUCC:

        /*��������ͳ��-���GU MMC���⣬ֻͳ��ACTIVE״̬��������*/
        CDS_ULDataFlowStats(ucEpsbID, pstIpPkt->usUsed,pstCdsEntity);

        stLPdcpData.ucRbId   = ucDrbId;
        stLPdcpData.ulSduLen = pstIpPkt->usUsed;
        stLPdcpData.pstSdu   = pstIpPkt;
        CDS_LPDCP_DataReq(&stLPdcpData);
        CDS_DBG_UL_LTE_SEND_TO_LPDCP_NUM(1);
        break;

    case CDS_ERABM_TRANSFER_RESULT_IDLE:
        if (PS_FALSE == pstCdsEntity->ulServiceReqFlg)
        {
            CDS_ERabmSerivceRequestNotify(ucEpsbID);
            pstCdsEntity->ulServiceReqFlg = PS_TRUE;
        }

        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_LTE_SAVE_PKT_NUM(1);
        break;

    case CDS_ERABM_TRANSFER_RESULT_DRB_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_LTE_SAVE_PKT_NUM(1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_LTE_ERABM_STATE_ERROR(1);
        break;

    }

    return;
}
VOS_VOID CDS_LTEPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                                 ucEpsbId;
    IPF_RESULT_STRU                          *pstIpfRlst;
    VOS_UINT16                                usFilterResult;

    /*��õ�EPSBID*/
    usFilterResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)&(usFilterResult);
    ucEpsbId = (VOS_UINT8)(pstIpfRlst->usBearedId);
    /*lint -e960*/
    if ((CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRlst->usIpSegInfo)
         &&(PS_SUCC != CDS_IpFragmentProc(&ucEpsbId, pstIpPkt,pstIpfRlst,pstCdsEntity)))
    {
        /*IP��Ƭ��*/
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_LTE_PROC_IPSEG_FAIL_NUM(1);
        return;
    }
    /*lint +e960*/

    /* ���ض��� */
    if(QosFc_IsDiscard(ucEpsbId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULLTE_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_LTE_FC_FREE_PKT_NUM(1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlLteDispatchData(ucEpsbId,pstIpPkt,pstCdsEntity);

    return;
}

#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 �� �� ��  : CDS_UlCDMADataReq
 ��������  : CDMA ��ucRabId�ַ�����,���û���֤����Ϸ�
 �������  : VOS_UINT8 ucRabId,
             TTF_MEM_ST *pstIpPkt,

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��12��30��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���
    2.��    ��   : 2015��06��12��
      ��    ��   : l00304941
      �޸�����   : ����HRPD�ӿ�

*****************************************************************************/
VOS_VOID CDS_UlCDMADataReq(VOS_UINT8 ucRabId,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_CDMA_1X_TRANS_DATA_STRU          st1xUlData;
    CDS_CDMA_HRPD_TRANS_DATA_STRU        stHrpdUlData;
    VOS_UINT8                            ucPdnId = TAF_APS_MapRabIdToPdnId(ucRabId);

    if ((CDS_MIN_PDN_ID > ucPdnId) || (CDS_MAX_PDN_ID < ucPdnId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    if (APS_CDS_MODE_1X == pstCdsEntity->enRanMode)
    {
        st1xUlData.ucPdnId   = ucPdnId;
        st1xUlData.ulSduLen  = pstIpPkt->usUsed;
        st1xUlData.pstSdu    = pstIpPkt;
        PPPC_1X_PullPacketEvent(&st1xUlData);
    }
    else
    {
        stHrpdUlData.ucPdnId   = ucPdnId;
        stHrpdUlData.ulSduLen  = pstIpPkt->usUsed;
        stHrpdUlData.pstSdu    = pstIpPkt;
        PPPC_HRPD_PullPacketEvent(&stHrpdUlData);
    }

    CDS_DBG_UL_CDMA_SEND_TO_PPP_NUM(pstCdsEntity->enRanMode, 1);

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_UlCDMARlpDispatchData
 ��������  : CDMA ��ucRabId�ַ�����,���û���֤����Ϸ�
 �������  : VOS_UINT8 ucRabId,
             TTF_MEM_ST *pstIpPkt,
             CDS_ENTITY_STRU *pstCdsEntity

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��12��30��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_UlCDMADispatchData(VOS_UINT8 ucRabId,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8             enCDMABearStatus;
    VOS_UINT32                                       ulRanMode;

    CDS_ASSERT((ucRabId >= CDS_NAS_MIN_BEARER_ID)&&(ucRabId <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    L2_UlAppThrStatProc(pstIpPkt->usUsed);
    ulRanMode = pstCdsEntity->enRanMode;

    /*��ȡRAB ״̬*/
    enCDMABearStatus = TAF_APS_GetCdataBearStatus(ucRabId);

    switch (enCDMABearStatus)
    {
    case APS_CDS_CDATA_BEAR_STATUS_ACTIVE:

        /*��������ͳ��*/
        CDS_ULDataFlowStats(ucRabId, pstIpPkt->usUsed, pstCdsEntity);

        CDS_UlCDMADataReq(ucRabId, pstIpPkt, pstCdsEntity);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_IDLE:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);

        /*֪ͨAPS����*/
        CDS_APSServiceRequestNotify(pstCdsEntity, ucRabId);

        CDS_DBG_UL_CDMA_SAVE_PKT_NUM(ulRanMode, 1);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);

        CDS_DBG_UL_CDMA_SAVE_PKT_NUM(ulRanMode, 1);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_INACTIVE:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

        CDS_DBG_UL_CDMA_RAB_STATE_INACTIVE(ulRanMode, 1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

        CDS_DBG_UL_CDMA_RAB_STATE_ERROR(ulRanMode, 1);
        break;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_CDMAPktProc
 ��������  : CDMA����PPP֡
 �������  : pstCdsEntity: CDS����ʵ��
             pstIpPkt :    ����PPP֡

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_CDMAPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                                     ucRabId;

    /*RABID:��ǰֱ��ʹ���û����е�RABID*/
    ucRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /* ���ض��� */
    if(QosFc_IsDiscard(ucRabId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULCDMA_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_CDMA_FC_FREE_PKT_NUM(pstCdsEntity->enRanMode, 1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlCDMADispatchData(ucRabId,pstIpPkt,pstCdsEntity);

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_CheckUlBuffDataToSend
 ��������  : ���CDSʵ�����л���������Ƿ��ж�ӦRab������
 �������  :

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��11��15��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CDS_CheckUlBuffDataToSend(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId)
{
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulQueCnt;
    VOS_UINT32                          ucDataExist = PS_FALSE;
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT8                           ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    /*��������*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);

    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*���ָ������*/
        if (ucPktRabId == ucRabId)
        {
            ucDataExist = PS_TRUE;
        }

        /*�������*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    return ucDataExist;
}

/*****************************************************************************
 �� �� ��  : CDS_CheckUlDataToSend
 ��������  : CDS����Ƿ����������ݴ�����
 �������  :

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��11��15��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CDS_CheckUlDataToSend(MODEM_ID_ENUM_UINT16 enModemId,VOS_UINT8 ucRabId)
{
    CDS_ENTITY_STRU                               *pstCdsEntity;

    /* ����ModemId ���CDSʵ��ָ��*/
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_CheckUlDataToSend : Get CDS Entity Fail.ModemId",
                       enModemId);
        CDS_PRINT_ERROR1(CDS_CheckUlDataToSend_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        return PS_FALSE;
    }

    /*���л��治Ϊ��*/
    return CDS_CheckUlBuffDataToSend(pstCdsEntity,ucRabId);

}
#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_MULTI_MODEM)

RABM_RAB_STATUS_ENUM_UINT32 I1_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return RABM_RAB_STATUS_BUTT;
}



VOS_VOID I1_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData)
{
    if (VOS_NULL_PTR == pstUlData)
    {
        return;
    }

    TTF_MemFree(UEPS_PID_CDS,pstUlData->pstSdu);
    return;
}

#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_MODEM_2)


RABM_RAB_STATUS_ENUM_UINT32 I2_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return RABM_RAB_STATUS_BUTT;
}



VOS_VOID I2_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData)
{
    if (VOS_NULL_PTR == pstUlData)
    {
        return;
    }

    TTF_MemFree(UEPS_PID_CDS,pstUlData->pstSdu);
    return;
}

#endif


RABM_RAB_STATUS_ENUM_UINT32 CDS_GUGetRabIdStatus(VOS_UINT8  ucRabId, VOS_UINT16 usModemId)
{
    if (MODEM_ID_0 == usModemId)
    {
        return NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else if (MODEM_ID_1 == usModemId)
    {
        return I1_NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else if (MODEM_ID_2 == usModemId)
    {
        return I2_NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else
    {
        return RABM_RAB_STATUS_BUTT;
    }
}


VOS_VOID CDS_GUUlDataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData, VOS_UINT16 usModemId)
{
    CDS_ASSERT(VOS_NULL_PTR != pstUlData);

    if (MODEM_ID_0 == usModemId)
    {
        NAS_RABM_UL_DataReq(pstUlData);
    }
    else if (MODEM_ID_1 == usModemId)
    {
        I1_NAS_RABM_UL_DataReq(pstUlData);
    }
    else if (MODEM_ID_2 == usModemId)
    {
        I2_NAS_RABM_UL_DataReq(pstUlData);
    }
    else
    {
        /*�쳣���ͷ��ڴ�*/
        TTF_MemFree(UEPS_PID_CDS, pstUlData->pstSdu);
    }

    return;
}
VOS_VOID CDS_UlGUDispatchData(VOS_UINT8 ucRabId, TTF_MEM_ST *pstIpPkt, CDS_ENTITY_STRU *pstCdsEntity)
{
    RABM_RAB_STATUS_ENUM_UINT32      enRabStatus;
    CDS_RABM_TRANS_DATA_STRU         stRabmData;
    VOS_UINT16                       usModemId;

    CDS_ASSERT((ucRabId >= CDS_NAS_MIN_BEARER_ID)&&(ucRabId <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    /*RAB ״̬*/
    usModemId = pstCdsEntity->usModemId;
    enRabStatus = CDS_GUGetRabIdStatus(ucRabId, usModemId);
    switch(enRabStatus)
    {
    case RABM_RAB_STATUS_ACTIVE:

        /*��������ͳ��*/
        CDS_ULDataFlowStats(ucRabId, pstIpPkt->usUsed,pstCdsEntity);

        stRabmData.ucRabId  = ucRabId;
        stRabmData.ulSduLen = pstIpPkt->usUsed;
        stRabmData.pstSdu   = pstIpPkt;
        CDS_GUUlDataReq(&stRabmData,usModemId);
        CDS_DBG_UL_GU_SEND_TO_RABM_NUM(1);
        CDS_DBG_MODEM_UL_GU_SEND_TO_RABM_NUM(usModemId,1);
        break;

    case RABM_RAB_STATUS_IDLE:
        CDS_RabmSerivceRequestNotify(ucRabId,pstCdsEntity);
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_GU_SAVE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_SAVE_PKT_NUM(usModemId,1);
        break;

    case RABM_RAB_STATUS_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_GU_SAVE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_SAVE_PKT_NUM(usModemId,1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_GU_RABM_STATE_ERROR(1);
        CDS_DBG_MODEM_UL_GU_RABM_STATE_ERROR(usModemId,1);
        break;

    }

    return;
}




VOS_VOID CDS_GUPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                        ucRabId;
    VOS_UINT16                       usFilterResult;
    IPF_RESULT_STRU                 *pstIpfRlst;


    /* ����������Ч�����������ݰ� */
    if (PS_TRUE == CDS_GET_VOICEPREFER_ACT_FLAG(pstCdsEntity))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    usFilterResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)&(usFilterResult);
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRlst->usIpSegInfo)
    {
        (VOS_VOID)CDS_IpFragmentProc(&ucRabId, pstIpPkt,pstIpfRlst,pstCdsEntity);
    }

    /*RABID:��ǰGUδʵ�ֶ���أ�ҲΪ��IP��Ƭ������ǰֱ��ʹ���û����е�RABID*/
    ucRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /* ���ض��� */
    if(QosFc_IsDiscard(ucRabId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULGU_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_GU_FC_FREE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_FC_FREE_PKT_NUM(pstCdsEntity->usModemId,1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlGUDispatchData(ucRabId,pstIpPkt,pstCdsEntity);
    return;
}
VOS_VOID CDS_UlDispatchDataByRanMode(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt)
{

    CDS_DBG_UL_AS_RX_IP_PKT_NUM(1);

    /* ����ͳ�� */
    CDS_ULFlowAdd(pstIpPkt->usUsed);

    /*���������ڴ�ֱ���ͷ�*/
    if (PS_TRUE == pstCdsEntity->ulULPktDiscardFlg)
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_DIRECT_FREE_PKT_NUM(1);
        return;
    }

    /*������ģʽ�ַ�*/
    switch(pstCdsEntity->enRanMode)
    {
    case MMC_CDS_MODE_NULL:
        CDS_ULStorePkt(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_NULL_RX_PKT_NUM(1);
        break;

    case MMC_CDS_MODE_GU:
        CDS_GUPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_GU_RX_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_FC_FREE_PKT_NUM(pstCdsEntity->usModemId,1);
        break;

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    case MMC_CDS_MODE_LTE:
        CDS_LTEPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_LTE_RX_PKT_NUM(1);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
    case APS_CDS_MODE_1X:
    case APS_CDS_MODE_EVDO:
        CDS_CDMAPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_CDMA_RX_PKT_NUM(pstCdsEntity->enRanMode, 1);
        break;
#endif
    default :
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_RAN_MODE_ERROR_FREE_NUM(1);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UlDispatchDataByRanMode : Current Ran Mode Error.Ran Mode :",pstCdsEntity->enRanMode);
        CDS_PRINT_ERROR1(CDS_UlDispatchDataByRanMode_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL,pstCdsEntity->enRanMode);
        break;
    }

    return;
}
CDS_UL_IP_PKT_TYPE_ENUM_UINT32 CDS_PreProcUlRD(TTF_MEM_ST *pstIpPkt)
{
    IPF_RESULT_STRU       *pstIpfRslt;
    VOS_UINT16             usIpfResult;

    usIpfResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRslt  = (IPF_RESULT_STRU *)&usIpfResult;

    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRslt->usIpSegInfo)
    {
        /*IP��Ƭ����,��IP��Ƭ���ߵ�ȱʡ����*/
        CDS_DBG_UL_IPF_RX_IP_SEG_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NORMAL;
    }

    /*����BID���з���*/
    if ((pstIpfRslt->usBearedId >= CDS_UL_IPF_BEARER_ID_EPSBID5)
        && (pstIpfRslt->usBearedId <= CDS_UL_IPF_BEARER_ID_EPSBID15))
    {
        /*[5,15]������IP��*/
        CDS_DBG_UL_IPF_RX_IP_PKT_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NORMAL;
    }
    else if ( (CDS_UL_IPF_BEARER_ID_DHCPV4 <= pstIpfRslt->usBearedId)
            &&(CDS_UL_IPF_BEARER_ID_LL_FF >= pstIpfRslt->usBearedId))
    {
        /*[16,21],NDIS*/
        CDS_DBG_UL_IPF_RX_NDIS_PKT_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NDIS;
    }
    else
    {
        if (usIpfResult & CDS_UL_IPF_RESULT_PKT_ERROR_MASK)
        {
            /*����IPFָʾIP�����ڴ���ģ����䷢�͵���Ӧ��ȱʡ�����ϣ�Ϊ�˹��NAT KEEP-ALIVE����*/
            CDS_DBG_UL_IPF_FILTER_ERROR_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_IPF_ERR);
            usIpfResult = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);
            CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt, usIpfResult);
            return CDS_UL_IP_PKT_TYPE_NORMAL;
        }
        else
        {
            /*����IPFָʾIP��ȷ��û��ƥ�䵽��ȷ�����ϵģ�ֱ�Ӷ���������˹׼������*/
            CDS_DBG_UL_IPF_FILTER_ERROR_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_IPF_ERR);
            return CDS_UL_IP_PKT_TYPE_ERROR;
        }
    }
}


VOS_VOID CDS_UlProcIpfResult(VOS_VOID)
{
    VOS_UINT32                            ulRdNum = IPF_ULRD_DESC_SIZE;
    VOS_UINT32                         ulCnt;
    IPF_RD_DESC_S                     *pstRD;
    CDS_UL_IP_PKT_TYPE_ENUM_UINT32     enIpType;
    IPF_RD_DESC_S                     *pstUlRdBuff;
    CDS_ENTITY_STRU                   *pstCdsEntity;
    VOS_UINT16                         usModemId;
    TTF_MEM_ST                        *pstIpPkt;
    VOS_UINT8                          ucPktType;

    /*����IPF RD���*/
    pstUlRdBuff = CDS_GET_UL_RD_BUFF();
    CDS_ASSERT(VOS_NULL_PTR != pstUlRdBuff);

    LDRV_IPF_GET_ULRD(&ulRdNum,pstUlRdBuff);
    if (0 == ulRdNum)
    {
        /*NO RD*/
        return;
    }

    /*����ͳ�Ƽ���*/
    CDS_DBG_UL_IPF_RX_RD_NUM(ulRdNum);
    Cds_LomTraceRcvUlData();

    /*����RD*/
    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt ++)
    {
        pstRD = &(pstUlRdBuff[ulCnt]);

        /*ת��ΪTTF�ڴ�*/
        pstIpPkt = CDS_RdTransferTtfMem(pstRD);
        if (VOS_NULL_PTR == pstIpPkt)
        {
            CDS_DBG_UL_IPF_TRANS_MEM_FAIL_NUM(1);
            continue;
        }

        /*��ö�ӦModemʵ��ָ��*/
        usModemId = CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt);

        ucPktType = CDS_UL_GET_PKT_TYPE_FROM_TTF(pstIpPkt);

        /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt);

        pstCdsEntity = CDS_GetCdsEntity(usModemId);
        if (VOS_NULL_PTR == pstCdsEntity)
        {
            TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
            CDS_DBG_UL_IPF_MODEMID_ERROR_NUM(1);
            continue;
        }

        /*����ģʽ��ֱ�Ӷ���*/
        if (PS_TRUE == pstCdsEntity->ulTestModeFlg)
        {
            TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
            CDS_DBG_UL_IPF_FREE_PKT_IN_LB(1);
            continue;
        }

        /*��RD���з��ദ��*/
        enIpType = CDS_PreProcUlRD(pstIpPkt);
        if (CDS_UL_IP_PKT_TYPE_NORMAL == enIpType)
        {
            /*��ģʽ�ַ�*/
            /*��������bastetģ����������ݷ��ͣ���Ҫ֪ͨbastetģ��*/
            CDS_BstSendTxInd();
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
        }
        else if (CDS_UL_IP_PKT_TYPE_NDIS == enIpType)
        {
            /*�����ݷ��͵�ADS*/
            CDS_UlDataIndToAds(pstIpPkt);
        }
        else
        {
            if (ADS_CDS_IPF_PKT_TYPE_PPP == ucPktType)
            {
                CDS_UlDispatchDataByRanMode(pstCdsEntity, pstIpPkt);
            }
            else
            {
                /* �ͷ��ڴ� */
                TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            }
        }
    }

    /*ΪADQ�����ڴ棬��ֹδִ���걻����*/
    CDS_AllocMemForAdq();

    /*����RD������֮��ͨ�������¼�������������������������*/
    CDS_TriggerUlProcOnFinalRD();

    return;
}
VOS_VOID CDS_TriggerUlProcOnFinalRD(VOS_VOID)
{
    CDS_ENTITY_STRU *pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);

    if(VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_TriggerUlProcOnFinalRD : CDS_GetCdsEntity return NULL");
        CDS_PRINT_ERROR(CDS_TriggerUlProcOnFinalRD_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    if(MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        CDS_LPDCP_TriggerUlDataProc();
    }
#endif

    if(MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        NAS_RABM_SetFinIpInRdFlag(PS_TRUE);
    }

    return;
}



VOS_VOID CDS_ClearUlBuffData(CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32           ulCnt;
    TTF_MEM_ST          *pstTtfMem;

    /*ֹͣ������ʱ��*/
    CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);

    /*���Service Request��־λ*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*����GU SR��־*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*��������*/
    for(ulCnt = 0; ulCnt < CDS_UL_IDLE_QUE_SIZE; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
        CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
    }

    return;
}


VOS_VOID CDS_SendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstIpPkt;
    VOS_UINT16                  usResult;

    /*ֹͣ������ʱ��*/
    CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);

    /*���Service Request��־λ*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*����GU SR��־*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*��������*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        /*��������˽ӿ�*/
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_UL_BUFF_SOFT_FILTER_FAIL_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_SOFT_IPF_ERR);
            continue;
        }

        /*�����˽���浽TTF��*/
        CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usResult);

        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);

        CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
    }

    return;
}


VOS_VOID CDS_SendUlBuffDataToRabm(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucSendRabId)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstTtfMem;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*��������*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*ȫ�����ͻ���ָ������*/
        if ((ucPktRabId == ucSendRabId) || (CDS_NAS_ALL_BEARER_ID == ucSendRabId))
        {
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstTtfMem);
            CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
            continue;
        }

        /*�����ͣ����������*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*����Ϊ�գ�ֹͣ������ʱ��*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;
}


VOS_VOID CDS_CDMASendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucSendRabId)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstIpPkt;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*���Service Request��־λ*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*��������*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

        /*ȫ�����ͻ���ָ������*/
        if ((ucPktRabId == ucSendRabId) || (CDS_NAS_ALL_BEARER_ID == ucSendRabId))
        {
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
            CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
            continue;
        }

        /*�����ͣ����������*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstIpPkt))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*����Ϊ�գ�ֹͣ������ʱ��*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;
}
VOS_VOID CDS_UlGUClearBuffData(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId)
{

    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstTtfMem;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*��������*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*ȫ�����ͻ���ָ������*/
        if ((ucPktRabId == ucRabId) || (CDS_NAS_ALL_BEARER_ID == ucRabId))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
            continue;
        }

        /*�����ͣ����������*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*����Ϊ�գ�ֹͣ������ʱ��*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;

}


VOS_UINT32 CDS_IsPsDataAvail(VOS_VOID)
{

    CDS_ENTITY_STRU    *pstCdsEntity;

    /*Ĭ��MODEM_0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    /*���л��治Ϊ��*/
    if (PS_FALSE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



