

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALSNMSG_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


VOS_VOID  NAS_RabmSnSequenceRspMsg( VOS_VOID *pMsg )
{
    VOS_UINT8                                ucLoop;
    VOS_UINT8                                ucFlag = VOS_FALSE;
    ST_APP_RABM_STATUS                       stReportStatus;

    if ( ( RABM_ROUTING_AREA_UPDATE_T1_ON != gRabmRAT1Switch )
         && ( RABM_3G_TO_2G_T3_ON != gRabm3GTo2GT3Switch ) )   /*������ʱ����û��*/
    {
        /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
        RABM_LOG_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RECEIVE an ILLOGICAL SnSequenceRsp Msg because rout.area.update.T1 and Rabm.sys.3To2.T3 Timer are OFF!" );
        return;
    }

    if ( ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )
         && ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch ) )   /*������ʱ��������*/
    {
        /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
        RABM_LOG_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RECEIVE an ILLOGICAL SnSequenceRsp Msg because rout.area.update.T1 and Rabm.sys.3To2.T3 Timer are ON!" );
        return;
    }

    /*��ӡ������Ϣ---�յ���Ϣ:*/
    RABM_LOG_NORMAL( "NAS_RabmSnSequenceRspMsg:NORMAL:RECEIVE RABM_SN_SEQUENCE_RSP_MSG Msg From UEPS_PID_SN" );

    if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )
    {
        ucFlag = VOS_TRUE;
    }

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*����2G�е�ÿ��NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )   /*��NSAPI��״̬*/
        {
            case RABM_2G_NULL:
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                      /*������״̬�Ĵ���ʽһ��*/
                if ( VOS_TRUE == ucFlag )
                {
                    if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                    else if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[ucLoop].State )
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_DATA_TRANS_READY state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                    else
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_DATA_TRANS_STOP state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                }
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*����NSAPI��״̬��ΪRABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )   /*������rout.area.update.T1��ʱ��*/
                {
                    /*����2G�еĴ���:*/
                    NAS_RabmDeal2GSnSequence(pMsg);

                    /*��APP�ϱ�TAFRABM_STARTSTOP_IND(START)��Ϣ:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPP��ʼ���ݴ���*/
                    /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                }
                else if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )           /*������Rabm.sys.3To2.T3��ʱ��*/
                {
                    /*�����л��еĴ���*/
                    NAS_RabmDealChangeSnSequence();

                    /*��APP�ϱ�TAFRABM_STARTSTOP_IND(START)��Ϣ:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPP��ʼ���ݴ���*/
                    /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    /*��APP�ϱ�TAFRABM_STARTSTOP_IND(START)��Ϣ:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPP��ʼ���ݴ���*/
                    /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                break;
            default:
                /*��ӡ������Ϣ---��NSAPI��״̬�ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_RabmSnSequenceRspMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }

}



VOS_VOID  NAS_RabmDeal2GSnSequence( VOS_VOID * pMsg )
{
    VOS_UINT32                               ulLength;
    RABM_SN_SEQUENCE_RSP_MSG                *pstSequenceRsp;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pstRAUpdateRsp;

    pstSequenceRsp = ( RABM_SN_SEQUENCE_RSP_MSG * )pMsg;

    /*�ر�rout.area.update.T1��ʱ��:*/
    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );

    /*����GMMRABM_ROUTING_AREA_UPDATE_RSP��Ϣ:*/
    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pstRAUpdateRsp )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmDeal2GSnSequence:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
        return;
    }
    /*��д��Ϣͷ:*/
    pstRAUpdateRsp->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstRAUpdateRsp->MsgHeader.ulSenderPid     = WUEPS_PID_RABM;
    pstRAUpdateRsp->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRAUpdateRsp->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstRAUpdateRsp->MsgHeader.ulLength        = ulLength;

    pstRAUpdateRsp->MsgHeader.ulMsgName       = ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP;
    /*��д��Ϣ��:*/
    /*��N-PDUΪ��Ч:*/
    pstRAUpdateRsp->ucNpduValidFlg            = GMM_RABM_NPDU_VALID;
    /*����N-PDU����:*/
    NAS_RabmEncodeNPdu( pstRAUpdateRsp , &pstSequenceRsp->RabmSnSequenceRsp.RecvNPduNumList );
    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmDeal2GSnSequence:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmDeal2GSnSequence:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP Msg" );
    }

}




VOS_VOID  NAS_RabmDealChangeSnSequence( VOS_VOID )
{
    /*�ر�Rabm.sys.3To2.T3��ʱ��:*/
    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );

    /*��SNDCP����RABM_SNDCP_RESUME_DATA_IND��Ϣ:*/
    NAS_RabmSndSnDataResumeInd();
}



VOS_VOID  NAS_RabmSnSaveDataRspMsg(VOS_VOID)
{
    /*��ӡ������Ϣ--�յ�RABM_SNDCP_SAVE_DATA_RSP��Ϣ:*/
    RABM_LOG_NORMAL("NAS_RabmSnSaveDataRspMsg:NORMAL:Recv RABM_SNDCP_SAVE_DATA_RSP msg");

    return;
}
VOS_VOID  NAS_RabmSnResumeDataRspMsg(VOS_VOID)
{
    /*��ӡ������Ϣ--�յ�RABM_SNDCP_RESUME_DATA_RSP��Ϣ:*/
    RABM_LOG_NORMAL("NAS_RabmSnSaveDataRspMsg:NORMAL:Recv RABM_SNDCP_RESUME_DATA_RSP msg");

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
