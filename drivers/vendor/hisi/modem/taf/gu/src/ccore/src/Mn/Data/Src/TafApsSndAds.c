


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDADS_C

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsSndAds.h"

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/



ADS_QCI_TYPE_ENUM_UINT8 TAF_APS_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                   *pQos
)
{
    ADS_QCI_TYPE_ENUM_UINT8             enQci;

    /* ת������μ�: 23.401
       Annex E (normative):
        Mapping between EPS and Release 99 QoS parameters
        QCI    Traffic_Class  Traffic_Handling_Priority Signalling_Indication  Src_Stats_Descriptor
         1     Conversational          NA                       NA                  SPEECH
         2     Conversational          NA                       NA                    NA
         3     Conversational          NA                       NA                   Unknown
         4     Streaming               NA                       NA                   Unknown
         5     Interactive              1                       YES                  Unknown
         6     Interactive              1                       NO                    NA
         7     Interactive              2                       NO                    NA
         8     Interactive              3                       NO                    NA
         9     Background              NA                       NA                    NA

      NOTE��1: When QCI 2 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 150 ms. When Release 99 QoS parameter values are mapped to a QCI,
               QCI 2 is used for conversational/unknown if the Transfer Delay parameter is greater
               or equal to 150 ms.
      NOTE��2: When QCI 3 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 80 ms as the lowest possible value, according to TS 23.107 [59]. When Release
               99 QoS parameter values are mapped to a QCI, QCI 3 is used for conversational/unknown if
               the Transfer Delay parameter is lower than 150 ms.
      NOTE  3: When QCI 4 is mapped to Release 99 QoS parameter values, it is mapped to Streaming/Unknown.
               When Release 99 QoS parameter values are mapped to a QCI, Streaming/Unknown and Streaming/Speech
               are both mapped to QCI 4.
    */
    /* ����QOS trafficClass������ȡQCI */
    if (TAF_APS_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL == pQos->ucTrafficClass)
    {
        if (TAF_APS_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH == pQos->ucSrcStatisticsDescriptor)
        {
            enQci       = ADS_QCI_TYPE_QCI1_GBR;
        }
        else if (pQos->usTransDelay >= TAF_APS_APP_QOS_TRANSFER_DELAY_150MS)
        {
            enQci       = ADS_QCI_TYPE_QCI2_GBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI3_GBR;
        }
    }
    else if (TAF_APS_APP_QOS_TRAFFIC_CLASS_STREAMING == pQos->ucTrafficClass)
    {
        enQci       = ADS_QCI_TYPE_QCI4_GBR;
    }
    else if (TAF_APS_APP_QOS_TRAFFIC_CLASS_INTERACTIVE == pQos->ucTrafficClass)
    {
        if (TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1 == pQos->ucTraffHandlePrior)
        {
            if (TAF_APS_APP_QOS_SIGNAL_IND_OPTIMISE == pQos->ucSignallingIndication)
            {
                enQci       = ADS_QCI_TYPE_QCI5_NONGBR;
            }
            else
            {
                enQci       = ADS_QCI_TYPE_QCI6_NONGBR;
            }
        }
        else if (TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2 == pQos->ucTraffHandlePrior)
        {
            enQci       = ADS_QCI_TYPE_QCI7_NONGBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI8_NONGBR;
        }
    }
    else
    {
        enQci       = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    return enQci;
}
VOS_VOID TAF_APS_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
)
{
    ADS_PDP_STATUS_IND_STRU            *pstMsg;

    /* ����ADS_PDP_STATUS_IND_STRU��Ϣ */
    pstMsg = (ADS_PDP_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(ADS_PDP_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        APS_WARN_LOG("Taf_APS_SendAdsPdpStatusInd: alloc msg fail!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_PDP_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->enMsgId         = ID_APS_ADS_PDP_STATUS_IND;

    /* ��д��Ϣ�� */
    pstMsg->enModemId       = pstAdsInd->enModemId;
    pstMsg->ucRabId         = pstAdsInd->ucRabId;
    pstMsg->enPdpStatus     = pstAdsInd->enPdpStatus;
    pstMsg->enPdpType       = pstAdsInd->enPdpType;
    pstMsg->enQciType       = pstAdsInd->enQciType;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))
    {
        APS_WARN_LOG("TAF_APS_SendAdsPdpStatusInd: Send msg fail!");
        return;
    }

    return;
}


VOS_VOID TAF_APS_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    stAdsInd.enModemId = MODEM_ID_0;

#if 0
#if (FEATURE_ON == FEATURE_IMS)
    /* ��module idΪIMSA������ר�г���ʱ������ADS����PDP״̬�ı�֪ͨ��Ϣ */
    if (PS_PID_IMSA == pstEvent->stCtrl.ulModuleId)
    {
        APS_WARN_LOG("TAF_APS_NotifyAdsWhenPdpModify:module id is imsa");
        return;
    }
#endif
#endif

    stAdsInd.enModemId = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == stAdsInd.enModemId)
    {
        APS_ERR_LOG("TAF_APS_NotifyAdsWhenPdpModify:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_MODIFY;
    stAdsInd.enPdpType      = TAF_PDP_TYPE_BUTT;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = TAF_APS_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* ��ADS_DL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}


VOS_VOID TAF_APS_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstEvent
)
{
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    stAdsInd.enModemId = MODEM_ID_0;

#if 0
#if (FEATURE_ON == FEATURE_IMS)
    /* ��module idΪIMSA������ר�г���ʱ������ADS����PDP״̬�ı�֪ͨ��Ϣ */
    if (PS_PID_IMSA == pstEvent->stCtrl.ulModuleId)
    {
        APS_WARN_LOG("TAF_APS_NotifyAdsWhenPdpDeactivated:module id is imsa");
        return;
    }
#endif
#endif

    stAdsInd.enModemId = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == stAdsInd.enModemId)
    {
        APS_ERR_LOG("TAF_APS_NotifyAdsWhenPdpDeactivated:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_DEACT;
    stAdsInd.enPdpType      = pstEvent->enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = ADS_QCI_TYPE_BUTT;

    /* ��ADS_DL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}


VOS_VOID TAF_APS_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    stAdsInd.enModemId = MODEM_ID_0;

#if 0
#if (FEATURE_ON == FEATURE_IMS)
    /* ��module idΪIMSA������ר�г���ʱ������ADS����PDP״̬�ı�֪ͨ��Ϣ */
    if (PS_PID_IMSA == pstEvent->stCtrl.ulModuleId)
    {
        APS_WARN_LOG("TAF_APS_NotifyAdsWhenPdpAvtivated:module id is imsa");
        return;
    }
#endif
#endif

    stAdsInd.enModemId = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == stAdsInd.enModemId)
    {
        APS_ERR_LOG("TAF_APS_NotifyAdsWhenPdpAvtivated:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_ACT;
    stAdsInd.enPdpType      = pstEvent->stPdpAddr.enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = TAF_APS_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* ��ADS_DL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_NotifyAdsWhenCdataSoInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucRabId
)
{
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    stAdsInd.enModemId = MODEM_ID_0;

    stAdsInd.enModemId = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == stAdsInd.enModemId)
    {
        APS_ERR_LOG("TAF_APS_NotifyAdsWhenCdataSoInd:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_ACT;
    stAdsInd.enPdpType      = enPdpType;
    stAdsInd.ucRabId        = ucRabId;

    /* TODO:���� */
    stAdsInd.enQciType      = ADS_QCI_TYPE_BUTT;

    /* ��ADS_DL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                                &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                                &stAdsInd);

    return;
}


VOS_VOID TAF_APS_NotifyAdsWhenCdataEstFail(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucRabId
)
{
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == stAdsInd.enModemId)
    {
        APS_ERR_LOG("TAF_APS_NotifyAdsWhenCdataEstFail:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_DEACT;
    stAdsInd.enPdpType      = enPdpType;
    stAdsInd.ucRabId        = ucRabId;
    stAdsInd.enQciType      = ADS_QCI_TYPE_BUTT;

    /* ��ADS_DL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    TAF_APS_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


