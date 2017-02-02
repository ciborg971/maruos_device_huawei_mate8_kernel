


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CdsDebug.h"
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsIpFragmentProc.h"

#define CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD   (5000000)
#define CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD   (500000)

CDS_STATS_INFO_STRU    g_stCdsStats = {0};

VOS_UINT32   g_ulCdsOmSwitch = 0;

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


VOS_VOID CDS_SetDbgRptBearerId(VOS_UINT8  ucEpsbId)
{
    /*LTEĬ�Ϸ���Modem0*/
    g_astCdsEntity[MODEM_ID_0].ucDbgBearerId = ucEpsbId;
    return;
}
VOS_VOID CDS_SetMbmsBearerId(VOS_UINT8  ucEpsbId)
{
    /*LTEĬ�Ϸ���Modem0*/
    g_astCdsEntity[MODEM_ID_0].ucMbmsBearerId = ucEpsbId;
    return;
}
VOS_VOID CDS_SetPktDiscardFlg(MODEM_ID_ENUM_UINT16 enModemId,VOS_UINT32  ulDir, VOS_UINT32 ulFlg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    if (0 == ulDir)
    {
        pstCdsEntity->ulULPktDiscardFlg = ulFlg;
    }
    else
    {
        pstCdsEntity->ulDLPktDiscardFlg = ulFlg;
    }

    return ;
}


VOS_VOID CDS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag)
{
    switch (ulFlowDebugFlag)
    {
        case CDS_FLOW_DEBUG_DL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulDLFlowRptThreshold   = CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            break;

        case CDS_FLOW_DEBUG_UL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowRptThreshold   = CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        case CDS_FLOW_DEBUG_ALL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulDLFlowRptThreshold   = CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            g_stCdsStats.ulULFlowRptThreshold   = CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        default:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_FALSE;
            break;
    }

    return;
}


VOS_VOID CDS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold)
{
    g_stCdsStats.ulDLFlowRptThreshold   = ulFlowDLRptThreshold;
    return;
}


VOS_VOID CDS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold)
{
    g_stCdsStats.ulULFlowRptThreshold   = ulFlowULRptThreshold;
    return;
}


VOS_VOID CDS_DLFlowAdd(VOS_UINT32  ulSduLen)
{
    if (PS_TRUE == g_stCdsStats.ulDLFlowDebugFlag)
    {
        /* ����ͳ�� */
        g_stCdsStats.ulDLFlowInfo += ulSduLen;

        /* ����ͳ���ϱ� */
        if (g_stCdsStats.ulDLFlowInfo >= g_stCdsStats.ulDLFlowRptThreshold)
        {
            g_stCdsStats.ulDLEndSlice   = VOS_GetSlice();

            PS_PRINTF("CDS DL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stCdsStats.ulDLFlowInfo, g_stCdsStats.ulDLEnSduQueSucc, g_stCdsStats.ulDLEndSlice,
                (g_stCdsStats.ulDLEndSlice - g_stCdsStats.ulDLStartSlice));

            g_stCdsStats.ulDLStartSlice = g_stCdsStats.ulDLEndSlice;
            g_stCdsStats.ulDLFlowInfo   = 0;
        }
    }

    return;
}


VOS_VOID CDS_ULFlowAdd(VOS_UINT32  ulSduLen)
{
    if (PS_TRUE == g_stCdsStats.ulULFlowDebugFlag)
    {
        /* ����ͳ�� */
        g_stCdsStats.ulULFlowInfo += ulSduLen;

        /* ����ͳ���ϱ� */
        if (g_stCdsStats.ulULFlowInfo >= g_stCdsStats.ulULFlowRptThreshold)
        {
            g_stCdsStats.ulULEndSlice   = VOS_GetSlice();

            PS_PRINTF("CDS UL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stCdsStats.ulULFlowInfo, g_stCdsStats.ulULASRxIpPktNum, g_stCdsStats.ulULEndSlice,
                (g_stCdsStats.ulULEndSlice - g_stCdsStats.ulULStartSlice));

            g_stCdsStats.ulULStartSlice = g_stCdsStats.ulULEndSlice;
            g_stCdsStats.ulULFlowInfo   = 0;
        }
    }

    return;
}


VOS_VOID CDS_ShowEventStats(VOS_VOID)
{

    PS_PRINTF("�����յ�IPF�жϴ���                          %d\n",g_stCdsStats.ulIpfULIntNum);
    PS_PRINTF("���д���IPF�жϴ���                          %d\n",g_stCdsStats.ulULProcIpfIntNum);
    PS_PRINTF("�����յ�ADQ���жϴ���                        %d\n",g_stCdsStats.ulUlAdqEmtypIntNum);
    PS_PRINTF("���д���ADQ���жϴ���                        %d\n",g_stCdsStats.ulUlProcAdqEmptyIntNum);
    PS_PRINTF("����IPF�����ڴ��ͷź����ص�����              %d\n",g_stCdsStats.ulIpfDlCallMemFreeNum);
    PS_PRINTF("����IPF�����ڴ溯���ͷ��ڴ����              %d\n",g_stCdsStats.ulIpfDlFreeMemNum);
    PS_PRINTF("����10ms�����Զ�ʱ���������д����¼�����     %d\n",g_stCdsStats.ulDL10msTmrTrigEvent);
    PS_PRINTF("����1ms��֡�жϴ������д����¼�����          %d\n",g_stCdsStats.ulDL1msIntTrigEvent);
    PS_PRINTF("����UMTS DSP�жϴ������д����¼�����         %d\n",g_stCdsStats.ulDLUmtsIntTrigEvent);
    PS_PRINTF("���д������д����¼�����                     %d\n",g_stCdsStats.ulDLProcEventNum);
    PS_PRINTF("\r\n");

    return;
}


VOS_VOID CDS_ShowUlRdProcStats(VOS_VOID)
{
    PS_PRINTF("����IPF�յ�RD����                            %d\n",g_stCdsStats.ulULIpfRxRDNum);
    PS_PRINTF("����RD�ڴ�ת��ʧ�ܸ���                       %d\n",g_stCdsStats.ulULIpfTransMemFailNum);
    PS_PRINTF("����IPF RD ModemID�������                   %d\n",g_stCdsStats.ulULIpfModemIdErrNum);
    PS_PRINTF("���л���ģʽ�ͷ�RD����                       %d\n",g_stCdsStats.ulULIpfFreePktInLB);
    PS_PRINTF("�����յ�IP������                             %d\n",g_stCdsStats.ulULIpfRxIpPktNum);
    PS_PRINTF("�����յ�IP��Ƭ������                         %d\n",g_stCdsStats.ulULIpfRxIpSegNum);
    PS_PRINTF("�����յ�NDIS������                           %d\n",g_stCdsStats.ulULIpfRxNdisPktNum);
    PS_PRINTF("����IPF���˴������                          %d\n",g_stCdsStats.ulULIpfFilterErrNum);

    PS_PRINTF("\r\n");
    return;
}


VOS_VOID CDS_ShowUlAdqProcStats(VOS_VOID)
{

    PS_PRINTF("����ADQ�����ڴ����                          %d\n",g_stCdsStats.ulULADQAllocMemNum);
    PS_PRINTF("����ADQ����ʧ���ͷ��ڴ����                  %d\n",g_stCdsStats.ulULADQFreeMemNum);
    PS_PRINTF("��������AD 0�ڴ����                         %d\n",g_stCdsStats.ulULADQCfgAd0Num);
    PS_PRINTF("��������AD 1�ڴ����                         %d\n",g_stCdsStats.ulULADQCfgAd1Num);
    PS_PRINTF("��������AD�ڴ�����(AD0+AD1)                  %d\n",g_stCdsStats.ulULADQCfgAdNum);
    PS_PRINTF("��������ADQ�ɹ�����                          %d\n",g_stCdsStats.ulULADQCfgAdSucc);
    PS_PRINTF("��������ADQʧ�ܴ���                          %d\n",g_stCdsStats.ulULADQCfgAdFail);
    PS_PRINTF("��������ADQ�ձ�����ʱ������                  %d\n",g_stCdsStats.ulULADQStartEmptyTmrNum);
    PS_PRINTF("����ֹͣADQ�ձ�����ʱ������                  %d\n",g_stCdsStats.ulULADQStopEmptyTmrNum);
    PS_PRINTF("����ADQ�ձ�����ʱ����ʱ����                  %d\n",g_stCdsStats.ulULADQEmptyTmrTimeoutNum);
    PS_PRINTF("����IPF ADQ���жϸ���                        %d\n",g_stCdsStats.ulUlAdqEmtypIntNum);
    PS_PRINTF("����IPF AD 0������жϸ���                   %d\n",g_stCdsStats.ulULADQAd0EmptyIntNum);
    PS_PRINTF("����IPF AD 1������жϸ���                   %d\n",g_stCdsStats.ulULADQAd1EmptyIntNum);

    PS_PRINTF("\r\n");
    return;
}



VOS_VOID CDS_ShowUlIpPktProcStats(VOS_VOID)
{

    PS_PRINTF("���н�����յ���IP���ܺ�                     %d\n",g_stCdsStats.ulULASRxIpPktNum);
    PS_PRINTF("���д�׮�ͷŵ�IP������                       %d\n",g_stCdsStats.ulULDirectFreePktNum);
    PS_PRINTF("����LTEģ���յ�IP������                      %d\n",g_stCdsStats.ulULLTERxPktNum);
    PS_PRINTF("����GUģ���յ�IP������                       %d\n",g_stCdsStats.ulULGURxPktNum);
    PS_PRINTF("����NULLģ����IP������                       %d\n",g_stCdsStats.ulULNULLRxPktNum);
    PS_PRINTF("���н���ģʽ�����ͷŵ�IP������               %d\n",g_stCdsStats.ulULRanModeErrFreeNum);
    PS_PRINTF("\r\n");

    PS_PRINTF("LTE���������ͷŵ�IP������                    %d\n",g_stCdsStats.ulULLTEFcFreePktNum);
    PS_PRINTF("LTE���д���IP��Ƭʧ��IP������                %d\n",g_stCdsStats.ulULLTEProcIpSegFail);
    PS_PRINTF("LTE���з��͵�LPDCP��IP������                 %d\n",g_stCdsStats.ulULLTESendToLPdcpNum);
    PS_PRINTF("LTE���л���IP������                          %d\n",g_stCdsStats.ulULLTESavePktNum);
    PS_PRINTF("LTE����ERABM״̬�����ͷŵ�IP������           %d\n",g_stCdsStats.ulULLTEERabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("GU���������ͷŵ�IP������                     %d\n",g_stCdsStats.ulULGUFcFreePktNum);
    PS_PRINTF("GU���з��͵�RABM��IP������                   %d\n",g_stCdsStats.ulULGUSendToRabmNum);
    PS_PRINTF("GU���л���IP������                           %d\n",g_stCdsStats.ulULGUSavePktNum);
    PS_PRINTF("GU����RABM״̬�����ͷŵ�IP������             %d\n",g_stCdsStats.ulULGURabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("1x���з��͵�RLP��IP������                    %d\n",g_stCdsStats.ulUL1xSendToRlpNum);
    PS_PRINTF("1x���з��͵�PPP��IP������                    %d\n",g_stCdsStats.ulUL1xSendToPppNum);
    PS_PRINTF("1x���л���IP������                           %d\n",g_stCdsStats.ulUL1xSavePktNum);
    PS_PRINTF("1x����RAB״̬INACTIVEʱ�ͷŵ�IP������        %d\n",g_stCdsStats.ulUL1xRabStateIna);
    PS_PRINTF("1x����RAB״̬�����ͷŵ�IP������              %d\n",g_stCdsStats.ulUL1xRabStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("HRPD���з��͵�PPP��IP������                  %d\n",g_stCdsStats.ulULHRPDSendToPppNum);
    PS_PRINTF("HRPD���л���IP������                         %d\n",g_stCdsStats.ulULHRPDSavePktNum);
    PS_PRINTF("HRPD����RAB״̬INACTIVEʱ�ͷŵ�IP������      %d\n",g_stCdsStats.ulULHRPDRabStateIna);
    PS_PRINTF("HRPD����RAB״̬�����ͷŵ�IP������            %d\n",g_stCdsStats.ulULHRPDRabStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("���л�����ӳɹ�����                         %d\n",g_stCdsStats.ulULBuffEnQueSucc);
    PS_PRINTF("���л������ʧ�ܸ���                         %d\n",g_stCdsStats.ulULBuffEnQueFail);
    PS_PRINTF("���л��������ʧ�ܸ���                       %d\n",g_stCdsStats.ulULBuffSoftFilterFail);
    PS_PRINTF("���л��淢��IP���ɹ�����                     %d\n",g_stCdsStats.ulULBuffSendPktSuccNum);
    PS_PRINTF("���л����ͷ�IP������                         %d\n",g_stCdsStats.ulULBuffFreePktNum);
    PS_PRINTF("\r\n");

    PS_PRINTF("����IP������ͳ���ܺ�\n");
    PS_PRINTF("�����յ�NDCLIENT������                       %d\n",g_stCdsStats.ulULRecvNdPktNum);
    PS_PRINTF("�����յ�DHCP������                           %d\n",g_stCdsStats.ulULRecvDhcpPktNum);
    PS_PRINTF("�����յ��������ݰ�����                       %d\n",g_stCdsStats.ulLBUlSendPktNum);
    PS_PRINTF("�����յ�RD���ݰ�����                         %d\n",g_stCdsStats.ulULIpfRxIpPktNum + g_stCdsStats.ulULIpfRxIpSegNum);
    PS_PRINTF("���л����������·��͸���                     %d\n",g_stCdsStats.ulULBuffSendPktSuccNum);
    PS_PRINTF("���а�ģʽ�ַ������ݰ��ܺ�(ND+DHCP+LB+IP+BUFF)    %d\n",g_stCdsStats.ulULASRxIpPktNum);

    return;
}


VOS_VOID CDS_ShowDlSduProcStats(VOS_VOID)
{

    PS_PRINTF("����SDU����ͳ��\n\n");

    PS_PRINTF("����GSMģ����SDU����                         %d\n",g_stCdsStats.ulDLGSMRxSduNum);
    PS_PRINTF("����GSMģ����IMS���ݰ�����                   %d\n",g_stCdsStats.ulDLGSMRxImsNum);
    PS_PRINTF("����GSMģ���ض���SDU����                     %d\n",g_stCdsStats.ulDLGSMFcFreeSduNum);
    PS_PRINTF("����GSMģ����ģʽ�½���SDU����               %d\n",g_stCdsStats.ulLBDLRxSduInGSM);
    PS_PRINTF("����GSM��ȡȱʡRABIDʧ�ܸ���                 %d\n",g_stCdsStats.ulDLGSMGetDeftRabIdFail);
    PS_PRINTF("����GSMģ��ӳɹ�����                        %d\n",g_stCdsStats.ulDLGSMEnQueSucc);
    PS_PRINTF("����GSMģ���ʧ�ܸ���                        %d\n",g_stCdsStats.ulDLGSMEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("����UMTSģ����SDU����                        %d\n",g_stCdsStats.ulDLUMTSRxSduNum);
    PS_PRINTF("����UMTSģ����IMS���ݰ�����                  %d\n",g_stCdsStats.ulDLUMTSRxImsNum);
    PS_PRINTF("����UMTSģ���ض���SDU����                    %d\n",g_stCdsStats.ulDLUMTSFcFreeSduNum);
    PS_PRINTF("����UMTSģ����ģʽ�½���SDU����              %d\n",g_stCdsStats.ulLBDLRxSduInUMTS);
    PS_PRINTF("����UMTSģ��׮ֱ���ͷ�SDU����                %d\n",g_stCdsStats.ulDLUMTSDirectFreeSduNum);
    PS_PRINTF("����UMTS��ȡȱʡRABIDʧ�ܸ���                %d\n",g_stCdsStats.ulDLUMTSGetDeftRabIdFail);
    PS_PRINTF("����UMTSģ��ӳɹ�����                       %d\n",g_stCdsStats.ulDLUMTSEnQueSucc);
    PS_PRINTF("����UMTSģ���ʧ�ܸ���                       %d\n",g_stCdsStats.ulDLUMTSEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("����1xģ����SDU����                          %d\n",g_stCdsStats.ulDL1xRxSduNum);
    PS_PRINTF("����1xģ��׮ֱ���ͷ�SDU����                  %d\n",g_stCdsStats.ulDL1xDirectFreeSduNum);
    PS_PRINTF("����1x��ȡDRB��Ӧ��RABIDʧ�ܸ���             %d\n",g_stCdsStats.ulDL1xGetRabIDFail);
    PS_PRINTF("����1x��ȡDRB��Ӧ��Ĭ��RABIDʧ�ܸ���         %d\n",g_stCdsStats.ulDL1xGetDeftRabIDFail);
    PS_PRINTF("����1xģ��ӳɹ�����                         %d\n",g_stCdsStats.ulDL1xEnQueSucc);
    PS_PRINTF("����1xģ���ʧ�ܸ���                         %d\n",g_stCdsStats.ulDL1xEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("����HRPDģ����SDU����                        %d\n",g_stCdsStats.ulDLHRPDRxSduNum);
    PS_PRINTF("����HRPDģ��׮ֱ���ͷ�SDU����                %d\n",g_stCdsStats.ulDLHRPDDirectFreeSduNum);
    PS_PRINTF("����HRPD��ȡDRB��Ӧ��RABIDʧ�ܸ���           %d\n",g_stCdsStats.ulDLHRPDGetRabIDFail);
    PS_PRINTF("����HRPD��ȡDRB��Ӧ��Ĭ��RABIDʧ�ܸ���       %d\n",g_stCdsStats.ulDLHRPDGetDeftRabIDFail);
    PS_PRINTF("����HRPDģ��ӳɹ�����                       %d\n",g_stCdsStats.ulDLHRPDEnQueSucc);
    PS_PRINTF("����HRPDģ���ʧ�ܸ���                       %d\n",g_stCdsStats.ulDLHRPDEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("����LTEģ����SDU����                         %d\n",g_stCdsStats.ulDLLteRxSduNum);
    PS_PRINTF("����LTEģ����IMS���ݰ�����                   %d\n",g_stCdsStats.ulDLLteRxImsNum);
    PS_PRINTF("����LTEģ���ض���SDU����                     %d\n",g_stCdsStats.ulDLLteFcFreeSduNum);
    PS_PRINTF("����LTEģ��׮ֱ���ͷ�SDU����                 %d\n",g_stCdsStats.ulDLLteDirectFreeSduNum);
    PS_PRINTF("����LTEģ����ģʽ�½���SDU����               %d\n",g_stCdsStats.ulLBDLRxSduInLte);
    PS_PRINTF("����LTE��ȡ��ӦEPSBIDʧ�ܸ���                %d\n",g_stCdsStats.ulDLLteGetEpsbIDFail);
    PS_PRINTF("����LTE��ȡȱʡEPSBIDʧ�ܸ���                %d\n",g_stCdsStats.ulDLLteGetDeftEpsbIDFail);
    PS_PRINTF("����LTE����L2 Debug���ݰ�����                %d\n",g_stCdsStats.ulDLLteRxDbgPkt);
    PS_PRINTF("����LTE����MBMS���ݰ�����                    %d\n",g_stCdsStats.ulDLLteRxMbmsSdu);
    PS_PRINTF("����LTEģ��ӳɹ�����                        %d\n",g_stCdsStats.ulDLLteEnQueSucc);
    PS_PRINTF("����LTEģ���ʧ�ܸ���                        %d\n",g_stCdsStats.ulDLLteEnQueFail);


    PS_PRINTF("\r\n");

    PS_PRINTF("����SDU���е�ǰ�������ݰ�����               %d\n",LUP_QueCnt(CDS_GET_IPF_DL_SDU_QUE()));
    PS_PRINTF("����SDU��ӳɹ�����                          %d\n",g_stCdsStats.ulDLEnSduQueSucc);
    PS_PRINTF("����SDU���ʧ������                          %d\n",g_stCdsStats.ulDLEnSduQueFail);
    PS_PRINTF("\r\n");

    return;
}


VOS_VOID CDS_ShowDlIpfProcStats(VOS_VOID)
{
    PS_PRINTF("����IPF����ͳ��\n\n");

    PS_PRINTF("��������IPFû��BD����                       %d\n",g_stCdsStats.ulDLIpfCfgHaveNoBD);
    PS_PRINTF("��������IPFû��CD����                       %d\n",g_stCdsStats.ulDLIpfCfgHaveNoCD);
    PS_PRINTF("��������IPF CD��������                      %d\n",g_stCdsStats.ulDLIpfCfgCDNotEnough);
    PS_PRINTF("��������BD�ɹ�����                          %d\n",g_stCdsStats.ulDLIpfCfgBDSucc);
    PS_PRINTF("��������BDʧ�ܸ���                          %d\n",g_stCdsStats.ulDLIpfCfgBDFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("�����Ž�ģʽ����Դ�ڴ�ɹ�����              %d\n",g_stCdsStats.ulDLIpfSaveSrcMemSucc);
    PS_PRINTF("�����Ž�ģʽ����Դ�ڴ�ʧ�ܸ���              %d\n",g_stCdsStats.ulDLIpfSaveSrcMemFail);
    PS_PRINTF("�����Ž�ģʽԴ�ڴ��ͷŶ��е�ǰ����          %d\n",LUP_QueCnt(CDS_IPF_DL_SRCMEM_FREE_QUE()));
    PS_PRINTF("�����Ž�ģʽ�ͷ�Դ�ڴ�ɹ�����              %d\n",g_stCdsStats.ulDLIpfFreeSrcMemNum);
    PS_PRINTF("�����Ž�ģʽ�ͷ�Դ�ڴ�ʧ�ܸ���              %d\n",g_stCdsStats.ulDLIpfFreeSrcMemErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("���з��Ž�ģʽIPF�����ڴ�ʧ�ܴ���           %d\n",g_stCdsStats.ulDLIpfCfgBDAllocMemFail);
    PS_PRINTF("���з��Ž�ģʽSDU���ȴ������               %d\n",g_stCdsStats.ulDLIpfCfgBDSduLenErr);
    PS_PRINTF("���з��Ž�ģʽIPF�����ڴ��ͷź����ص�����   %d\n",g_stCdsStats.ulIpfDlCallMemFreeNum);
    PS_PRINTF("���з��Ž�ģʽ�ͷ��ڴ����                  %d\n",g_stCdsStats.ulIpfDlFreeMemNum);

    PS_PRINTF("\r\n");

    return;
}



VOS_VOID CDS_ShowLBProcStats(VOS_VOID)
{
    PS_PRINTF("����ģʽ����ͳ��\n\n");
    PS_PRINTF("�������д�GSM���յ�SDU����                  %d\n",g_stCdsStats.ulLBDLRxSduInGSM);
    PS_PRINTF("�������д�UMTS���յ�SDU����                 %d\n",g_stCdsStats.ulLBDLRxSduInUMTS);
    PS_PRINTF("�������д�LTE���յ�SDU����                  %d\n",g_stCdsStats.ulLBDLRxSduInLte);
    PS_PRINTF("�������д�CDMA���յ�SDU����                 %d\n",g_stCdsStats.ulLBDLRxSduInCDMA);
    PS_PRINTF("�������������ڴ�ʧ�ܵĸ���                  %d\n",g_stCdsStats.ulLBDLAllocMemFail);
    PS_PRINTF("����������ӳɹ�����                        %d\n",g_stCdsStats.ulLBDDLEnQueSucc);
    PS_PRINTF("�����������ʧ�ܸ���                        %d\n",g_stCdsStats.ulLBDLEnQueFail);
    PS_PRINTF("�������������ʧ�ܸ���                      %d\n",g_stCdsStats.ulLBULSoftFilterFail);
    PS_PRINTF("�������з��͵����ݰ�����                    %d\n",g_stCdsStats.ulLBUlSendPktNum);
    PS_PRINTF("����������ն����ͷ����ݰ�����              %d\n",g_stCdsStats.ulLBUlClearPktNum);

    PS_PRINTF("\r\n");

    return;
}



VOS_VOID CDS_ShowModemGUProcStats(VOS_UINT16 usModemId)
{

    if (usModemId >= MODEM_ID_BUTT)
    {
        PS_PRINTF("ModemId�Ƿ�������ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("Modem %d�ϵ�GU����ͳ����Ϣ\n",usModemId);
    PS_PRINTF("����GUģ���յ�IP������                       %d\n",g_stCdsStats.astModemStats[usModemId].ulULGURxPktNum);
    PS_PRINTF("����GU�����ͷŵ�IP������                     %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUFcFreePktNum);
    PS_PRINTF("����GU���͵�RABM��IP������                   %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUSendToRabmNum);
    PS_PRINTF("����GU����IP������                           %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUSavePktNum);
    PS_PRINTF("����GU RABM״̬�����ͷŵ�IP������            %d\n",g_stCdsStats.astModemStats[usModemId].ulULGURabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("����GSMģ����SDU����                         %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMRxSduNum);
    PS_PRINTF("����GSMģ����IMS���ݰ�����                   %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMRxImsNum);
    PS_PRINTF("����GSMģ���ض���SDU����                     %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMFcFreeSduNum);
    PS_PRINTF("����GSMģ����ģʽ�½���SDU����               %d\n",g_stCdsStats.astModemStats[usModemId].ulLBDLRxSduInGSM);
    PS_PRINTF("����GSMģ��ӳɹ�����                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMEnQueSucc);
    PS_PRINTF("����GSMģ���ʧ�ܸ���                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("����UMTSģ����SDU����                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSRxSduNum);
    PS_PRINTF("����UMTSģ����IMS���ݰ�����                  %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSRxImsNum);
    PS_PRINTF("����UMTSģ���ض���SDU����                    %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSFcFreeSduNum);
    PS_PRINTF("����UMTSģ����ģʽ�½���SDU����              %d\n",g_stCdsStats.astModemStats[usModemId].ulLBDLRxSduInUMTS);
    PS_PRINTF("����UMTSģ��׮ֱ���ͷ�SDU����                %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSDirectFreeSduNum);
    PS_PRINTF("����UMTSģ��ӳɹ�����                       %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSEnQueSucc);
    PS_PRINTF("����UMTSģ���ʧ�ܸ���                       %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("\r\n");

    return;
}



VOS_VOID CDS_ShowCdsEntityInfo(VOS_UINT16 usModemId)
{
    char    strRanMode[][20]  = {"NULL","LTE","GU","��Ч����ģʽ"};
    char    strLBState[][20]  = {"����ģʽ","����ģʽ"};


    CDS_ENTITY_STRU         *pstCdsEntity;
    VOS_UINT32               ulCnt;

    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        PS_PRINTF("ModemId�Ƿ�������ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("��ʾModem%d��CDSʵ��״̬  \r\n",usModemId);
    PS_PRINTF("��ǰ����ģʽ              : %s\r\n",strRanMode[pstCdsEntity->enRanMode]);
    PS_PRINTF("����SR������־            : %d\r\n",pstCdsEntity->ulServiceReqFlg);
    PS_PRINTF("���л�����л������      : %d\r\n",LUP_QueCnt(pstCdsEntity->pstUlDataQue));
    PS_PRINTF("���л������ݱ�����ʱ��    : 0x%x\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_UL_DATA_PROCTECT].pstTmrHdr);
    PS_PRINTF("����10ms�����Զ�ʱ��      : 0x%x\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_DL_10MS_PERIODIC_TMR].pstTmrHdr);
    PS_PRINTF("����ģʽ״̬              : %s\r\n",strLBState[pstCdsEntity->ulTestModeFlg]);
    PS_PRINTF("����ģʽ����              : %d\r\n",pstCdsEntity->ulLoopBackMode);
    PS_PRINTF("����ģʽB��ʱ��ʱ��       : %d\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_LB_MODE_B_TMR].ulTmrLen);
    PS_PRINTF("���ض��е�ǰ����SDU       : %d\r\n",LUP_QueCnt(pstCdsEntity->pstLBModeBQue));

    PS_PRINTF("�������ݰ�ֱ�Ӷ�������    : %d\r\n",pstCdsEntity->ulULPktDiscardFlg);
    PS_PRINTF("�������ݰ�ֱ�Ӷ�������    : %d\r\n",pstCdsEntity->ulDLPktDiscardFlg);

    PS_PRINTF("\r\n");

    PS_PRINTF("��ʾModem%d��IMS������Ϣ  \r\n",usModemId);

    PS_PRINTF("IMS�˿ںŷ�Χ             :%d - %d\r\n",pstCdsEntity->stImsPortInfo.usMinImsPort,
                                                pstCdsEntity->stImsPortInfo.usMaxImsPort);

    PS_PRINTF("IMS��������               : %d\r\n",pstCdsEntity->ulImsBearerNum);
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        PS_PRINTF("IMS����ID                 : %d\r\n",pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId);
        PS_PRINTF("IMS��������               : %d\r\n",pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType);
    }

    PS_PRINTF("\r\n");
    return;
}


VOS_VOID CDS_PrintIpv4Addr(const IPV4_ADDR_UN  *pstIpv4Addr)
{
    CDS_ASSERT(VOS_NULL_PTR != pstIpv4Addr);

    PS_PRINTF("%d.%d.%d.%d\r\n", pstIpv4Addr->aucIPAddr[0],
                           pstIpv4Addr->aucIPAddr[1],
                           pstIpv4Addr->aucIPAddr[2],
                           pstIpv4Addr->aucIPAddr[3]);
    return;
}


VOS_VOID CDS_PrintIpv6Addr(const IPV6_ADDR_UN  *pstIpv6Addr)
{

    VOS_UINT32       ulCnt;

    CDS_ASSERT(VOS_NULL_PTR != pstIpv6Addr);

    for (ulCnt = 0; ulCnt < IPV6_ADDR_LEN - 1; ulCnt ++)
    {
        PS_PRINTF("%.2x:",pstIpv6Addr->aucIPAddr[ulCnt]);
    }

    PS_PRINTF("%.2x\r\n",pstIpv6Addr->aucIPAddr[ulCnt]);

    return;
}

VOS_VOID CDS_ShowSoftFilterIPv4Info(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*Service Type*/
    if (PS_TRUE == pstSoftFilter->bitOpTypeOfService)
    {
        PS_PRINTF("TFT Service Type          : %d\r\n",pstSoftFilter->ucTypeOfService);
        PS_PRINTF("TFT Service Type Mask     : %d\r\n",pstSoftFilter->ucTypeOfServiceMask);
    }

    /*Э��ID*/
    if (PS_TRUE == pstSoftFilter->bitOpProtocolId)
    {
        PS_PRINTF("TFT Protocol ID           : %d\r\n",pstSoftFilter->ucTypeOfService);
    }

    /*ԴIP��ַ��Ϣ*/
    if (PS_TRUE == pstSoftFilter->bitOpLcIpv4AddrAndMask)
    {
        PS_PRINTF("TFT IPv4 Src Address      : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unLocalIpv4Addr));
        PS_PRINTF("TFT IPv4 Src Address Mask : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unLocalIpv4Mask));
    }

    /*Ŀ��IP��ַ��Ϣ*/
    if (PS_TRUE == pstSoftFilter->bitOpRmtIpv4AddrAndMask)
    {
        PS_PRINTF("TFT IPv4 Dest Address     : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unRmtIpv4Addr));
        PS_PRINTF("TFT IPv4 Dest Address Mask: ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unRmtIpv4Mask));
    }

    return;
}



VOS_VOID CDS_ShowSoftFilterIPv6Info(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*Service Type*/
    if (PS_TRUE == pstSoftFilter->bitOpTypeOfService)
    {
        PS_PRINTF("TFT Service Type          : %d\r\n",pstSoftFilter->ucTypeOfService);
        PS_PRINTF("TFT Service Type Mask     : %d\r\n",pstSoftFilter->ucTypeOfServiceMask);
    }

    /*Э��ID*/
    if (PS_TRUE == pstSoftFilter->bitOpProtocolId)
    {
        PS_PRINTF("TFT Protocol ID           : %d\r\n",pstSoftFilter->ucTypeOfService);
    }

    /*FlowLable*/
    if (PS_TRUE == pstSoftFilter->bitOpFlowLabelType)
    {
        PS_PRINTF("TFT FlowLable Type        : 0x%.8x\r\n",pstSoftFilter->ulFlowLabelType);
    }

    /*ԴIPv6��ַ*/
    if (PS_TRUE == pstSoftFilter->bitOpLcIpv6AddrAndMask)
    {
        PS_PRINTF("TFT IPv6 Source Address    \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unLocalIpv6Addr));
        PS_PRINTF("TFT IPv6 Source Address Mask \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unLocalIpv6Mask));
    }

    /*Ŀ��IPv6��ַ*/
    if (PS_TRUE == pstSoftFilter->bitOpRmtIpv6AddrAndMask)
    {
        PS_PRINTF("TFT IPv6 Dest Address    \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unRmtIpv6Addr));
        PS_PRINTF("TFT IPv6 Dest Address Mask \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unRmtIpv6Mask));
    }

    return;
}
VOS_VOID CDS_ShowSoftFilterTransportLayerInfo(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*SPI*/
    if (PS_TRUE == pstSoftFilter->bitOpSecuParaIndex)
    {
        PS_PRINTF("TFT IPSec SPI             : 0x%.8x\r\n",pstSoftFilter->ulSecuParaIndex);
    }

    /*Դ�˿���Ϣ*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleLocalPort)
    {
        PS_PRINTF("TFT Source Port           : %d\r\n",pstSoftFilter->usSingleLcPort);
    }

    if (PS_TRUE == pstSoftFilter->bitOpLocalPortRange)
    {
        PS_PRINTF("TFT Source Port Range     : [%d,%d]\r\n",pstSoftFilter->usLcPortLowLimit,pstSoftFilter->usLcPortHighLimit);
    }

    /*Ŀ�Ķ˿���Ϣ*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleRemotePort)
    {
        PS_PRINTF("TFT Dest Port             : %d\r\n",pstSoftFilter->usSingleRmtPort);
    }

    if (PS_TRUE == pstSoftFilter->bitOpRemotePortRange)
    {
        PS_PRINTF("TFT Dest Port Range       : [%d,%d]\r\n",pstSoftFilter->usRmtPortLowLimit,pstSoftFilter->usRmtPortHighLimit);
    }

    return;
}
VOS_VOID CDS_ShowUlSoftFilter(VOS_UINT16 usModemId)
{

    CDS_ENTITY_STRU             *pstCdsEntity;
    CDS_SOFTFILTER_INFO_STRU    *pstSoftFilter;
    VOS_UINT32                   ulCnt;

    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        PS_PRINTF("ModemId�Ƿ�������ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("��ʾModem%d�������������������Ϊ%d  \r\n",usModemId,pstCdsEntity->ulUlSoftFilterNum);

    for (ulCnt = 0; ulCnt < pstCdsEntity->ulUlSoftFilterNum; ulCnt ++)
    {
        pstSoftFilter = &(pstCdsEntity->astUlSoftFilter[ulCnt]);
        PS_PRINTF("�����������%d��ϸ��Ϣ\r\n",ulCnt);
        PS_PRINTF("�����������ID            : %d\r\n",pstSoftFilter->ulPacketFilterId);
        PS_PRINTF("���������������          : %d\r\n",pstSoftFilter->enDirection);
        PS_PRINTF("���������������          : %d\r\n",pstSoftFilter->enFilterType);
        PS_PRINTF("��������������ȼ�        : %d\r\n",pstSoftFilter->usPrecedence);
        PS_PRINTF("�������������Ӧ�ĳ���ID  : %d\r\n",pstSoftFilter->ucRabId);

        if (CDS_SOFTFILTER_TYPE_IPV4 == pstSoftFilter->enFilterType)
        {
            CDS_ShowSoftFilterIPv4Info(pstSoftFilter);
        }
        else
        {
            CDS_ShowSoftFilterIPv6Info(pstSoftFilter);
        }

        CDS_ShowSoftFilterTransportLayerInfo(pstSoftFilter);

        PS_PRINTF("\r\n");

    }


    PS_PRINTF("\r\n");
    return;
}



VOS_VOID CDS_ShowUlSoftFilterStats(VOS_VOID)
{

    PS_PRINTF("������������ݰ�����                         %d\n",g_stCdsStats.ulULSoftFilterPktNum);
    PS_PRINTF("���������IPV4���ݰ�����                     %d\n",g_stCdsStats.ulULSoftFilterIPv4Num);
    PS_PRINTF("���������IPV6���ݰ�����                     %d\n",g_stCdsStats.ulULSoftFilterIPv6Num);
    PS_PRINTF("���������ʧ�ܸ���                           %d\n",g_stCdsStats.ulULSoftFilterFailNum);
    PS_PRINTF("���������IP��Ƭ����                         %d\n",g_stCdsStats.ulULSoftFilterIPSegNum);
    PS_PRINTF("���������IP��Ƭ����ɹ�����                 %d\n",g_stCdsStats.ulULSoftFilterIPSegSucc);
    PS_PRINTF("���������IP��Ƭ����ʧ�ܸ���                 %d\n",g_stCdsStats.ulULSoftFilterIPSegFail);

    PS_PRINTF("\r\n");
    return;
}



VOS_VOID CDS_ShowIMSStats(VOS_VOID)
{
    PS_PRINTF("IMS�����հ��������ô���                      %d\n",g_stCdsStats.ulImsULRxFunCallNum);
    PS_PRINTF("IMS�����հ�������ηǷ�����                  %d\n",g_stCdsStats.ulImsULRxFunParaErr);

    PS_PRINTF("IMS���н���IMS NIC���ݰ�����                 %d\n",g_stCdsStats.ulImsULRxNicPktNum);
    PS_PRINTF("IMS���������ڴ�ʧ�ܸ���                      %d\n",g_stCdsStats.ulImsULAllocMemFail);
    PS_PRINTF("IMS�������ʧ�ܸ���                          %d\n",g_stCdsStats.ulImsULEnQueFail);
    PS_PRINTF("IMS������ӳɹ�����                          %d\n",g_stCdsStats.ulImsULEnQueSucc);
    PS_PRINTF("IMS���д���IMS_PROC�¼�����                  %d\n",g_stCdsStats.ulImsULTrigImsEvent);
    PS_PRINTF("IMS���д���IMS_PROC�¼�����                  %d\n",g_stCdsStats.ulImsULProcImsEvent);
    PS_PRINTF("IMS���������ʧ�ܴ���                        %d\n",g_stCdsStats.ulImsULSoftFilterFail);
    PS_PRINTF("IMS�������ݰ����͵��տڸ���                  %d\n",g_stCdsStats.ulImsULSendToRan);

    PS_PRINTF("IMS���н���IMS���ݰ�����                     %d\n",g_stCdsStats.ulImsDLRxImsPkt);
    PS_PRINTF("IMS���н��յ�NDCLIENT���ݰ�����              %d\n",g_stCdsStats.ulImsDLNdPktNum);
    PS_PRINTF("IMS���������ڴ�ʧ�ܸ���                      %d\n",g_stCdsStats.ulImsDLAllocMemFail);
    PS_PRINTF("IMS���л�ȡĿ�Ķ˿ں�ʧ�ܸ���                %d\n",g_stCdsStats.ulImsDLGetDestPortFail);
    PS_PRINTF("IMS���з��͵�IMS NIC���ݰ�ʧ�ܸ���           %d\n",g_stCdsStats.ulImsDLSendToNicFail);
    PS_PRINTF("IMS���з��͵�IMS NIC���ݰ��ɹ�����           %d\n",g_stCdsStats.ulImsDLSendToNicSucc);

    PS_PRINTF("IMS���н���Ut���ݰ�����                     %d\n",g_stCdsStats.ulImsDLRxUtPkt);
    PS_PRINTF("IMS����Ut���ݰ�����ɹ�����                 %d\n",g_stCdsStats.ulImsDLUtPktProcSuccNum);
    PS_PRINTF("IMS����Ut���ݰ�����ʧ�ܸ���                 %d\n",g_stCdsStats.ulImsDLUtPktProcErrNum);

    PS_PRINTF("\r\n");
    return;
}


VOS_VOID CDS_ShowIpV4FragmentBuffInfo(VOS_VOID)
{

    VOS_UINT32                         ulCnt;
    CDS_IPV4_FRAGMENT_BUFF_STRU       *pstIpv4FragBuff;
    CDS_IPV4_FRAGMENT_INFO_STRU       *pstIpv4FragInfo;

    pstIpv4FragBuff = CDS_GET_IPV4_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV4_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstIpv4FragInfo = &(pstIpv4FragBuff->astSegBuff[ulCnt]);
        PS_PRINTF("\n IPV4 Fragment Buffer Index : %d\n",ulCnt);
        PS_PRINTF("EPS Bearer  ID:                 %d\n", pstIpv4FragInfo->ucEpsbID);
        PS_PRINTF("Source IP Addr:                 ");
        CDS_PrintIpv4Addr(&(pstIpv4FragInfo->unSrcAddr));
        PS_PRINTF("Dest   IP Addr:                 ");
        CDS_PrintIpv4Addr(&(pstIpv4FragInfo->unDstAddr));
        PS_PRINTF("IP Fragment ID:                 %d\n", pstIpv4FragInfo->usIpIdentity);
    }

    return;
}


VOS_VOID CDS_ShowIpV6FragmentBuffInfo(VOS_VOID)
{

    VOS_UINT32                         ulCnt;
    CDS_IPV6_FRAGMENT_BUFF_STRU       *pstIpv6FragBuff;
    CDS_IPV6_FRAGMENT_INFO_STRU       *pstIpv6FragInfo;

    pstIpv6FragBuff = CDS_GET_IPV6_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV6_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstIpv6FragInfo = &(pstIpv6FragBuff->astSegBuff[ulCnt]);
        PS_PRINTF("\n IPV6 Fragment Buffer Index : %d\n",ulCnt);
        PS_PRINTF("EPS Bearer  ID:    %d\n", pstIpv6FragInfo->ucEpsbID);
        PS_PRINTF("IP Fragment ID:    %d\n", pstIpv6FragInfo->ulIdentity);
        PS_PRINTF("Src IPV6 Addr :    ");
        CDS_PrintIpv6Addr(&(pstIpv6FragInfo->unSrcAddr));
        PS_PRINTF("Dst IPV6 Addr :    ");
        CDS_PrintIpv6Addr(&(pstIpv6FragInfo->unDstAddr));
    }

    return;
}



VOS_VOID CDS_ShowIpFragStats(VOS_VOID)
{

    PS_PRINTF("����IPV4 ��Ƭ�ĸ���               %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4Frag);
    PS_PRINTF("����IPV4 IPF���˳ɹ��ĸ���        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4IpfSucc);
    PS_PRINTF("����IPV4 IPF����ʧ�ܵĸ���        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4IpfFail);
    PS_PRINTF("����IPV6 ��Ƭ�ĸ���               %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6Frag);
    PS_PRINTF("����IPV6 IPF���˳ɹ��ĸ���        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6IpfSucc);
    PS_PRINTF("����IPV6 IPF����ʧ�ܵĸ���        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6IpfFail);
    PS_PRINTF("���ձ��ش���ɹ��ĸ���            %d\n",g_stCdsIpFragBuff.stStats.ulLocalProcSucc);
    PS_PRINTF("���ձ��ش���ʧ�ܵĸ���            %d\n",g_stCdsIpFragBuff.stStats.ulLocalProcFail);

    return;
}


VOS_VOID CDS_IpFrag_Help(VOS_VOID)
{
    PS_PRINTF("CDS_ShowIpV4FragmentBuffInfo             ��ʾIPV4��Ƭ������Ϣ\n");
    PS_PRINTF("CDS_ShowIpV6FragmentBuffInfo             ��ʾIPV6��Ƭ������Ϣ\n");
    PS_PRINTF("CDS_ShowIpFragStats                      ��ʾIP��Ƭͳ����Ϣ\n");
    PS_PRINTF("CDS_ClearIpFragBuff                      ���IP��Ƭ����");

    return;
}


VOS_VOID CDS_Help(VOS_VOID)
{

    PS_PRINTF("********************CDS�����Ϣ************************\n");
    PS_PRINTF("CDS_ShowCdsEntityInfo(ModemId)          ��ʾ��ӦModem��CDSʵ��״̬\n");
    PS_PRINTF("CDS_ShowEventStats                      ��ʾCDS�¼�����ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowUlRdProcStats                   ��ʾCDS����RD����ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowUlAdqProcStats                  ��ʾCDS����ADQͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowUlIpPktProcStats                ��ʾCDS����IP������ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowDlSduProcStats                  ��ʾCDS����SDU����ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowDlIpfProcStats                  ��ʾCDS����IPF����ͳ����Ϣ\n");

    PS_PRINTF("CDS_ShowModemGUProcStats(ModemId)       ��ʾGU��������ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowLBProcStats                     ��ʾ����ģʽ����ͳ����Ϣ\n");
    PS_PRINTF("CDS_IpFrag_Help                         ��ʾIP��Ƭ�����Ϣ\n");
    PS_PRINTF("QosFc_ShowStats                         ��ʾ������������ͳ����Ϣ\n");

    PS_PRINTF("CDS_ShowUlSoftFilter(ModemId)           ��ʾ���й���������Ϣ\n");
    PS_PRINTF("CDS_ShowUlSoftFilterStats               ��ʾ��������˴���ͳ����Ϣ\n");
    PS_PRINTF("CDS_ShowIMSStats                        ��ʾIMS����ͳ����Ϣ\n");

    return;
}
/*****************************************************************************
 �� �� ��  : LUP_CdsLomTraceRcvUlData
 ��������  : �û���ʱ��Trace�����ڼ�¼CDS������������ʱ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��23��
    ��    ��   : hujianbo 42180
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Cds_LomTraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulCdsOmSwitch)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "User plane latency trace: CDS rcv ul data\n");
        CDS_PRINT_ERROR(Cds_LomTraceRcvUlData_ENUM, LL2_CDS_RECV_UL_DATA);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Cds_LomTraceSendDlData
 ��������  : �û���ʱ��Trace�����ڼ�¼CDS������������ʱ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��23��
    ��    ��   : hujianbo 42180
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Cds_LomTraceSendDlData(VOS_VOID)
{
    if (1 == g_ulCdsOmSwitch)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "User plane latency trace: CDS send dl data\n");
        CDS_PRINT_ERROR(Cds_LomTraceSendDlData_ENUM, LL2_CDS_SEND_DL_DATA);
    }

    return;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



