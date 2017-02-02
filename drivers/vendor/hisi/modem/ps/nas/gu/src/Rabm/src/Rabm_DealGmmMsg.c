

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"
#include "NasRabmMsgProc.h"
#include "NasRabmFastdorm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALGMMMSG_C
/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
extern VOS_VOID Tc_TaskInit(VOS_VOID);


VOS_VOID  NAS_RabmGmmRoutingAreaUpdateIndMsg( VOS_VOID *pMsg )
{
    GMMRABM_ROUTING_AREA_UPDATE_IND_MSG     *pstRAMsg;
    VOS_UINT8                                ucLoop;
    VOS_UINT8                                ucPdpActFlag = 0;

    pstRAMsg = ( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG * )pMsg;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
    {
        if ( GMM_RABM_RAU_UNDER_HANDOVER == pstRAMsg->ucGmmRauCause )
        {
            /*��ӡ������Ϣ---�յ�2G��3G�л��е�·����������Ϣ:*/
            RABM_LOG_NORMAL( "NAS_RabmGmmRoutingAreaUpdateIndMsg:NORMAL:RECEIVE RA Update Msg while 2G changes to 3G" );

            if ( GMM_RABM_RAU_SUCCESS == pstRAMsg->ucResult )
            {
                /*Ѱ���Ƿ��м����PDP:*/
                for ( ucLoop = 0; ucLoop < RABM_3G_PS_MAX_ENT_NUM ; ucLoop++ )
                {
                    if( RABM_NSAPI_ACTIVE_NO_RAB == g_aRabmPsEnt[ucLoop].ucState )
                    {
                        ucPdpActFlag = 1;
                        break;
                    }
                }

                if ( 1 == ucPdpActFlag )
                {
                    gRabm2GTo3GDataResume = VOS_TRUE;
                }
            }
            else
            {
                 /*��ӡ������Ϣ---�յ�2G��3G�л������·��������ʧ����Ϣ:*/
                 RABM_LOG_NORMAL( "NAS_RabmGmmRoutingAreaUpdateIndMsg:NORMAL:RECEIVE RA Update Msg(2G->3G),but RAU Fail!" );
                 NAS_Rabm2GTo3GRAUFail();
            }
        }
        else
        {
            /*��ӡ������Ϣ---�յ�3G�µ�NORMAL RAU��Ϣ:*/
            RABM_LOG_NORMAL( "NAS_RabmGmmRoutingAreaUpdateIndMsg:NORMAL:RECEIVE RA Update Msg(GMM_RABM_RAU_UNDER_NORMAL) in 3G mode!" );
            return;
        }
    }
    else     /*����ǰ����ģʽΪ2G*/
    {
        /*������·��������:*/
        if ( GMM_RABM_RAU_UNDER_NORMAL == pstRAMsg->ucGmmRauCause )
        {
            /*��ӡ������Ϣ---�յ�2G�е�·����������Ϣ:*/
            RABM_LOG_NORMAL( "NAS_RabmGmmRoutingAreaUpdateIndMsg:NORMAL:RECEIVE RA Update Msg(in 2G Mode)" );

            if ( GMM_RABM_RAU_SUCCESS == pstRAMsg->ucResult )
            {
                NAS_Rabm2GRoutingAreaUpdate( pstRAMsg );
            }
            else
            {
                /*��ӡ������Ϣ---�յ�2G�е�·��������ʧ����Ϣ:*/
                RABM_LOG_WARNING( "NAS_RabmGmmRoutingAreaUpdateIndMsg:WARNING:RECEIVE RA Update Msg(in 2G Mode),but RAU Fail!" );
            }
        }
        else  /*�л��е�·��������*/
        {
            if ( GMM_RABM_RAU_SUCCESS == pstRAMsg->ucResult )
            {
                /*��ӡ������Ϣ---�յ�3G��2G�л��е�·����������Ϣ:*/
                RABM_LOG_NORMAL( "NAS_RabmGmmRoutingAreaUpdateIndMsg:NORMAL:RECEIVE RA Update Msg(3G->2G)" );

                /*����3G��2G�е�·������������:*/
                NAS_Rabm3GTo2GRoutingAreaUpdate( pstRAMsg );
            }
            else
            {
                 /*��ӡ������Ϣ---�յ�3G��2G�л��е�·��������ʧ����Ϣ:*/
                 RABM_LOG_WARNING( "NAS_RabmGmmRoutingAreaUpdateIndMsg:WARNING:RECEIVE RA Update Msg(3G->2G),but RAU Fail!" );
                 NAS_Rabm3GTo2GRAUFail();
            }
        }
    }
}



VOS_VOID  NAS_Rabm2GTo3GRAUFail( VOS_VOID )
{
    /*�ͷ���2G��3G�л���ʼʱSNDCP���������:*/
    SN_RabmClear2G3Share();

    return;
}
VOS_VOID  NAS_Rabm3GTo2GRAUFail( VOS_VOID )
{
    VOS_UINT32                              ulLength;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG    *pstRAUpdateRsp;

    /*����GMMRABM_ROUT_AREA_UPDATE_RSP��Ϣ:*/
    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pstRAUpdateRsp )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_Rabm3GTo2GRAUFail:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );

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
    PS_NAS_MEM_SET( pstRAUpdateRsp->aucRecvNPDUNumListIE, 0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN );
    /*��N-PDU��ʶΪ��Ч:*/
    pstRAUpdateRsp->ucNpduValidFlg            = GMM_RABM_NPDU_INVALID;
    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_Rabm3GTo2GRAUFail:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_Rabm3GTo2GRAUFail:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP Msg" );
    }

    /*�ͷ���3G��2G�л���ʼʱPDCP���������:*/
    SN_RabmClear3G2Share();

    return;
}
VOS_VOID  NAS_Rabm2GRoutingAreaUpdate( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG   *pMsg )
{
    VOS_UINT8                               ucLoop;
    VOS_UINT8                               ucFlag = VOS_FALSE;
    VOS_UINT32                              ulLength;
    RABM_SN_SEQUENCE_IND_MSG                *pstSnSequenceInd;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pstRAUpdateRsp;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*����2G������NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_2G_NULL:
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_ROUT_AREA_UPDATE:             /*������״̬�Ĵ���ʽһ��*/
                break;
            case RABM_DATA_TRANS_STOP:
            case RABM_DATA_TRANS_READY:
                if ( VOS_FALSE == ucFlag )
                {
                    /*����:*/
                    ucFlag = VOS_TRUE;

                    /*��ȡ�µ�TLLIֵ:*/
                    gulRabmTLLI = pMsg->ulTLLI;

                    /*����Rabm.routing.area.update.T1��ʱ��:*/
                    NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );

                    /*��ӡ������Ϣ---������Rabm.routing.area.update.T1��ʱ��:*/
                    RABM_LOG_NORMAL( "NAS_Rabm2GRoutingAreaUpdate:NORMAL:Start Rabm.routing.area.update.T1 Timer SUCCESS" );

                    /*����SNRABM_SEQUENCE_IND��Ϣ:*/
                    ulLength         = sizeof( RABM_SN_SEQUENCE_IND_MSG ) - VOS_MSG_HEAD_LENGTH;
                    pstSnSequenceInd = ( RABM_SN_SEQUENCE_IND_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
                    if ( VOS_NULL_PTR == pstSnSequenceInd )
                    {
                        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
                        RABM_LOG_ERROR( "NAS_Rabm2GRoutingAreaUpdate:ERROR:Allocates a message packet for SNRABM_SEQUENCE_IND msg FAIL!" );

                        /*�ر�Rabm.routing.area.update.T1��ʱ��:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );
                        return;
                    }
                    /*��д��Ϣͷ:*/
                    pstSnSequenceInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
                    pstSnSequenceInd->ulSenderPid     = WUEPS_PID_RABM;
                    pstSnSequenceInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
                    pstSnSequenceInd->ulReceiverPid   = UEPS_PID_SN;
                    pstSnSequenceInd->ulLength        = ulLength;
                    /*��д��Ϣ��:*/
                    pstSnSequenceInd->usMsgType                = ID_SN_RABM_SEQUENCE_IND;
                    pstSnSequenceInd->usPId                    = 5;
                    pstSnSequenceInd->RabmSnSequenceInd.ulTLLI = pMsg->ulTLLI;
                    /*����N-PDU����:*/
                    NAS_RabmDecodeNPdu( pMsg, &pstSnSequenceInd->RabmSnSequenceInd.RecvNPduNumList );
                    /*���͸���Ϣ:*/
                    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstSnSequenceInd ) )
                    {
                        /*��ӡ������Ϣ---������Ϣʧ��:*/
                        RABM_LOG_WARNING( "NAS_Rabm2GRoutingAreaUpdate:WARNING:SEND SNRABM_SEQUENCE_IND msg FAIL!" );
                    }
                    else
                    {
                        /*��ӡ������Ϣ---��������Ϣ:*/
                        RABM_LOG_NORMAL( "NAS_Rabm2GRoutingAreaUpdate:NORMAL:SEND SNRABM_SEQUENCE_IND Msg" );
                    }
                }

                /*��ӡ������Ϣ---״̬�л�:*/
                if ( RABM_DATA_TRANS_STOP == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state CHANGE TO RABM_ROUT_AREA_UPDATE state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state CHANGE TO RABM_ROUT_AREA_UPDATE state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }

                /*����NSAPI��״̬��ΪRABM_ROUT_AREA_UPDATE״̬:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_ROUT_AREA_UPDATE);

                /*����·����������ԭ��ֵ:*/
                gastRabm2GEntity[ucLoop].RAUpdateCause = RABM_RA_UPDATE_CAUSE_NORMAL;
                break;
            default:
                /*��ӡ������Ϣ---��NSAPI����״̬���ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_Rabm2GRoutingAreaUpdate:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }

    if ( VOS_FALSE == ucFlag )
    {
        /*��ȡ�µ�TLLIֵ:*/
        gulRabmTLLI = pMsg->ulTLLI;

        /*���ͽ�Rx N-PDU numbers��Ϊ0��GMMRABM_ROUTING_AREA_UPDATE_RSP��Ϣ:*/
        ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
        pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
        if ( VOS_NULL_PTR == pstRAUpdateRsp )
        {
            /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
            RABM_LOG_ERROR( "NAS_Rabm2GRoutingAreaUpdate:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
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
        PS_NAS_MEM_SET( pstRAUpdateRsp->aucRecvNPDUNumListIE, 0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN );
        /*��дN-PDU��Ч��־Ϊ��Ч:*/
        pstRAUpdateRsp->ucNpduValidFlg = GMM_RABM_NPDU_INVALID;
        /*���͸���Ϣ:*/
        if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
        {
            /*��ӡ������Ϣ---������Ϣʧ��:*/
            RABM_LOG_WARNING( "NAS_Rabm2GRoutingAreaUpdate:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is Invalid) msg FAIL!" );
        }
        else
        {
            /*��ӡ������Ϣ---��������Ϣ:*/
            RABM_LOG_NORMAL( "NAS_Rabm2GRoutingAreaUpdate:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is Invalid) Msg" );
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_RABM_GetLPdcpNpduNumList(
    RABM_PDCP_GET_N_PDU_NUM_LIST_ST    *pstPdcpNpduNumList
)
{
    VOS_UINT8                           ucEntId;
    VOS_UINT8                           ucState;

    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        ucState = NAS_RABM_GetGPsEntState(ucEntId);
        if (RABM_2G_NULL != ucState)
        {
            pstPdcpNpduNumList->aucNPDUNumList[ucEntId + RABM_2G_NSAPI_OFFSET][0] = 1;
            pstPdcpNpduNumList->aucNPDUNumList[ucEntId + RABM_2G_NSAPI_OFFSET][1] = 0;
        }
    }
}
#endif


VOS_VOID  NAS_Rabm3GTo2GRoutingAreaUpdate( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG   *pMsg )
{
    VOS_UINT8                               ucLoop;
    VOS_UINT8                               ucFlag = VOS_FALSE;
    VOS_UINT32                              ulLength;
    RABM_PDCP_GET_N_PDU_NUM_LIST_ST         stPdcpNpduNumList;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG    *pstRAUpdateRsp;
    RABM_SN_SEQUENCE_IND_MSG               *pstSnSequenceInd;

    /* ��ʼ��N-PDU Number List */
    PS_MEM_SET(&stPdcpNpduNumList, 0x00, sizeof(RABM_PDCP_GET_N_PDU_NUM_LIST_ST));

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*��������NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )     /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_2G_NULL :
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO :
            case RABM_ROUT_AREA_UPDATE :
            case RABM_DATA_TRANS_STOP :                     /*������״̬�Ĵ���ʽһ��*/
                /*��ӡ������Ϣ---��NSAPI������״̬�����߼�:*/
                if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:This NSAPI's state RABM_NSAPI_OK_TRANSMODE_NO is Abnormal!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else if ( RABM_ROUT_AREA_UPDATE == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:This NSAPI's state RABM_ROUT_AREA_UPDATE is Abnormal!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:This NSAPI's state RABM_DATA_TRANS_STOP is Abnormal!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                break;
            case RABM_DATA_TRANS_READY :
                if ( VOS_FALSE == ucFlag )
                {
                    /*����:*/
                    ucFlag = VOS_TRUE;

                    /*��ȡ�µ�TLLIֵ:*/
                    gulRabmTLLI = pMsg->ulTLLI;

                    /*����Rabm.Sys.3To2.T3��ʱ��:*/
                    NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );

                    /*��ӡ������Ϣ---������Rabm.Sys.3To2.T3��ʱ��:*/
                    RABM_LOG_NORMAL( "NAS_Rabm3GTo2GRoutingAreaUpdate:NORMAL:Start Rabm.Sys.3To2.T3 Timer SUCCESS" );

                    /*����SNRABM_SEQUENCE_IND��Ϣ:*/
                    ulLength         = sizeof( RABM_SN_SEQUENCE_IND_MSG ) - VOS_MSG_HEAD_LENGTH;
                    pstSnSequenceInd = ( RABM_SN_SEQUENCE_IND_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
                    if ( VOS_NULL_PTR == pstSnSequenceInd )
                    {
                        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
                        RABM_LOG_ERROR( "NAS_Rabm3GTo2GRoutingAreaUpdate:ERROR:Allocates a message packet for SNRABM_SEQUENCE_IND msg FAIL!" );

                        /*�ر�Rabm.Sys.3To2.T3��ʱ��:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
                        return;
                    }
                    /*��д��Ϣͷ:*/
                    pstSnSequenceInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
                    pstSnSequenceInd->ulSenderPid     = WUEPS_PID_RABM;
                    pstSnSequenceInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
                    pstSnSequenceInd->ulReceiverPid   = UEPS_PID_SN;
                    pstSnSequenceInd->ulLength        = ulLength;
                    /*��д��Ϣ��:*/
                    pstSnSequenceInd->usMsgType                = ID_SN_RABM_SEQUENCE_IND;
                    pstSnSequenceInd->usPId                    = 5;
                    pstSnSequenceInd->RabmSnSequenceInd.ulTLLI = pMsg->ulTLLI;
                    /*����N-PDU����:*/
                    NAS_RabmDecodeNPdu( pMsg, &pstSnSequenceInd->RabmSnSequenceInd.RecvNPduNumList );
                    /*���͸���Ϣ:*/
                    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstSnSequenceInd ) )
                    {
                        /*��ӡ������Ϣ---������Ϣʧ��:*/
                        RABM_LOG_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:SEND SNRABM_SEQUENCE_IND msg FAIL!" );
                    }
                    else
                    {
                        /*��ӡ������Ϣ---��������Ϣ:*/
                        RABM_LOG_NORMAL( "NAS_Rabm3GTo2GRoutingAreaUpdate:NORMAL:SEND SNRABM_SEQUENCE_IND Msg" );
                    }

                    /*����GMMRABM_ROUT_AREA_UPDATE_RSP��Ϣ:*/
                    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
                    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
                    if ( VOS_NULL_PTR == pstRAUpdateRsp )
                    {
                        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
                        RABM_LOG_ERROR( "NAS_Rabm3GTo2GRoutingAreaUpdate:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );

                        /*�ر�Rabm.Sys.3To2.T3��ʱ��:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
                        return;
                    }
                    /*��д��Ϣͷ:*/
                    pstRAUpdateRsp->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
                    pstRAUpdateRsp->MsgHeader.ulSenderPid     = WUEPS_PID_RABM;
                    pstRAUpdateRsp->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
                    pstRAUpdateRsp->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
                    pstRAUpdateRsp->MsgHeader.ulLength        = ulLength;

                    pstRAUpdateRsp->MsgHeader.ulMsgName       = ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP;
                    /*��N-PDUΪ��Ч:*/
                    pstRAUpdateRsp->ucNpduValidFlg            = GMM_RABM_NPDU_VALID;

                    /* ��ȡN-PDU Number List */
#if (FEATURE_ON == FEATURE_LTE)
                    if (VOS_TRUE == NAS_RABM_GetL2GFlg())
                    {
                        NAS_RABM_GetLPdcpNpduNumList(&stPdcpNpduNumList);
                        NAS_RABM_ClearL2GFlg();
                    }
                    else
                    {
                        stPdcpNpduNumList = gPdcpRcvNpduNum;
                    }
#else
                    stPdcpNpduNumList = gPdcpRcvNpduNum;
#endif
                    /*����N-PDU����:*/
                    NAS_RabmEncodeNPdu(pstRAUpdateRsp, (RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST*)&stPdcpNpduNumList);

                    /*���͸���Ϣ:*/
                    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
                    {
                        /*��ӡ������Ϣ---������Ϣʧ��:*/
                        RABM_LOG_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
                    }
                    else
                    {
                        /*��ӡ������Ϣ---��������Ϣ:*/
                        RABM_LOG_NORMAL( "NAS_Rabm3GTo2GRoutingAreaUpdate:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP Msg" );
                    }
                }

                /*����NSAPI��״̬��ΪRABM_ROUT_AREA_UPDATE״̬:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_ROUT_AREA_UPDATE);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state CHANGE TO RABM_ROUT_AREA_UPDATE state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                /*����·����������ԭ��ֵ:*/
                gastRabm2GEntity[ucLoop].RAUpdateCause = RABM_RA_UPDATE_CAUSE_3G_TO_2G;
                break;
            default:
                /*��ӡ������Ϣ---��NSAPI����״̬���ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_Rabm3GTo2GRoutingAreaUpdate:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }

    if ( VOS_FALSE == ucFlag )
    {
        /*��ȡ�µ�TLLIֵ:*/
        gulRabmTLLI = pMsg->ulTLLI;

        /*���ͽ�Rx N-PDU numbers��Ϊ0��GMMRABM_ROUTING_AREA_UPDATE_RSP��Ϣ:*/
        ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
        pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
        if ( VOS_NULL_PTR == pstRAUpdateRsp )
        {
            /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
            RABM_LOG_ERROR( "NAS_Rabm3GTo2GRoutingAreaUpdate:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
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
        PS_NAS_MEM_SET( pstRAUpdateRsp->aucRecvNPDUNumListIE, 0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN );
        /*��дN-PDU��Ч��־Ϊ��Ч:*/
        pstRAUpdateRsp->ucNpduValidFlg = GMM_RABM_NPDU_INVALID;
        /*���͸���Ϣ:*/
        if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
        {
            /*��ӡ������Ϣ---������Ϣʧ��:*/
            RABM_LOG_WARNING( "NAS_Rabm3GTo2GRoutingAreaUpdate:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is Invalid) msg FAIL!" );
        }
        else
        {
            /*��ӡ������Ϣ---��������Ϣ:*/
            RABM_LOG_NORMAL( "NAS_Rabm3GTo2GRoutingAreaUpdate:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is Invalid) Msg" );
        }
    }
}
VOS_VOID  NAS_RabmDeal2GTo3GSuspendIndMsg( VOS_VOID )
{
    VOS_UINT8               ucLoop;
    VOS_UINT8               ucFlag1 = VOS_FALSE;
    ST_APP_RABM_STATUS      stReportStatus;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*����2G��ÿ��NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_2G_NULL:
                /*��ӡ������Ϣ---״̬����:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state keep the same: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
                if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[ucLoop] )   /*������Rabm.act.req.T1��ʱ��*/
                {
                    /*�ر�Rabm.act.req.T1��ʱ��:*/
                    NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )ucLoop, RABM_TIMER_PARA_ACT_REQ_T1 );
                }

                /*��APP�ϱ�TAFRABM_STARTSTOP_IND(STOP)��Ϣ:*/
                stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
                stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
                Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPPֹͣ���ݴ���*/

                /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state report TAFRABM_STARTSTOP_IND(STOP) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                /*��״̬����ΪRABM_DATA_TRANS_STOP״̬:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_STOP);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_STOP state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_DATA_TRANS_READY:
                /*��APP�ϱ�TAFRABM_STARTSTOP_IND(STOP)��Ϣ:*/
                stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
                stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
                Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPPֹͣ���ݴ���*/

                /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state report TAFRABM_STARTSTOP_IND(STOP) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                /*��״̬����ΪRABM_DATA_TRANS_STOP״̬:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_STOP);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state CHANGE TO RABM_DATA_TRANS_STOP state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_ROUT_AREA_UPDATE:
                if ( VOS_FALSE == ucFlag1 )
                {
                    /*���־:*/
                    ucFlag1 = VOS_TRUE;

                    if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )   /*������rout.area.update.T1��ʱ��*/
                    {
                        /*�ر�rout.area.update.T1��ʱ��:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );
                    }
                    else
                    {
                        if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )    /*������Rabm.sys.3To2.T3��ʱ��*/
                        {
                            /*�ر�Rabm.sys.3To2.T3��ʱ��:*/
                            NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
                        }
                    }
                }

                if ( RABM_RA_UPDATE_CAUSE_NORMAL == gastRabm2GEntity[ucLoop].RAUpdateCause )
                {
                    /*��APP�ϱ�TAFRABM_STARTSTOP_IND(STOP)��Ϣ:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
                    Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPPֹͣ���ݴ���*/

                    /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state report TAFRABM_STARTSTOP_IND(STOP) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }

                /*��״̬����ΪRABM_DATA_TRANS_STOP״̬:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_STOP);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_STOP state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_DATA_TRANS_STOP:
                /*��ӡ������Ϣ---״̬����:*/
                RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state keep the same: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            default:
                /*��ӡ������Ϣ--- ��NSAPI����Ӧ��״̬����:*/
                RABM_LOG1_ERROR( "NAS_RabmDeal2GTo3GSuspendIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
        }
    }

}
VOS_VOID  NAS_RabmDeal3GTo2GSuspendIndMsg( VOS_VOID )
{
    VOS_UINT8               ucLoop;
    ST_APP_RABM_STATUS      stReportStatus;

    /* ֹͣRAB�ؽ�������ʱ�� */
    if ( RABM_TRUE == g_ucReestTimerFlg )
    {
        RABM_TimerStop(0);
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
        g_ucReestTimerFlg = RABM_FALSE;
    }

    for ( ucLoop = 0; ucLoop < RABM_3G_PS_MAX_ENT_NUM; ucLoop++ )   /*����3G��ÿ��NSAPI*/
    {
        /*������Rabm.ReestTimer,��ر���������λ�˶�ʱ����־:*/
        if ( RABM_TRUE == g_aRabmPsEnt[ucLoop].ucReEstFlg )
        {
            NAS_RABM_StopReestRabPendingTmr(ucLoop + RABM_NSAPI_OFFSET);
            g_aRabmPsEnt[ucLoop].ucReEstFlg = RABM_FALSE;
        }

        switch ( g_aRabmPsEnt[ucLoop].ucState )    /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_NULL:
                break;

            case RABM_NSAPI_ACTIVE_PENDING:
            case RABM_ACT_PENDING_WITH_RAB:             /*������״̬�Ĵ���ʽһ��*/
                /*��ӡ������Ϣ---״̬�л�:*/
                if ( RABM_NSAPI_ACTIVE_PENDING == g_aRabmPsEnt[ucLoop].ucState )
                {
                    RABM_LOG1_NORMAL( "STATE RABM_NSAPI_ACTIVE_PENDING state CHANGE TO RABM_NULL state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    RABM_LOG1_NORMAL( "STATE RABM_ACT_PENDING_WITH_RAB state CHANGE TO RABM_NULL state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                RABM_SetWState(ucLoop, RABM_NULL);                      /*״̬��� */

                RABM_RelSaveData(&g_aRabmPsEnt[ucLoop].DlDataSave, RABM_DOWNLINK);       /*�ͷŴ洢����������*/
                RABM_RelSaveData(&g_aRabmPsEnt[ucLoop].UlDataSave, RABM_UPLINK);         /*�ͷŴ洢����������*/
                break;

            case RABM_NSAPI_ACTIVE_WITH_RAB:
                /*��APP�ϱ�TAFRABM_STARTSTOP_IND(STOP)��Ϣ:*/
                stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
                stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
                Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPPֹͣ���ݴ���*/
                /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_ACTIVE_WITH_RAB state report TAFRABM_STARTSTOP_IND(STOP) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                /*��λ�Ƿ�֪ͨTAFֹͣ���ݴ���ı�־λ:*/
                g_aRabmPsEnt[ucLoop].ucStpFlg = RABM_TRUE;

                /*��״̬����ΪRABM_DATA_TRANSFER_STOP:*/
                RABM_SetWState(ucLoop, RABM_DATA_TRANSFER_STOP);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_ACTIVE_WITH_RAB state CHANGE TO RABM_DATA_TRANSFER_STOP state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;

            case RABM_DATA_TRANSFER_STOP:
                /*��ӡ������Ϣ---״̬����:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_ACTIVE_NO_RAB state keep the same: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;

            case RABM_NSAPI_ACTIVE_NO_RAB:
                /*��״̬����ΪRABM_DATA_TRANSFER_STOP:*/
                RABM_SetWState(ucLoop, RABM_DATA_TRANSFER_STOP);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_ACTIVE_NO_RAB state CHANGE TO RABM_DATA_TRANSFER_STOP state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;

            case RABM_TC_STATE_NULL:
                Tc_TaskInit();

                /*��״̬����ΪRABM_NULL:*/
                RABM_SetWState(ucLoop, RABM_NULL);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_TC_STATE_NULL state CHANGE TO RABM_NULL state: NSAPI:", ucLoop+ RABM_NSAPI_OFFSET );
                break;

            case RABM_TC_STATE_WITH_RAB:
                Tc_TaskInit();
                /*��״̬����ΪRABM_NULL:*/
                RABM_SetWState(ucLoop, RABM_NULL);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_TC_STATE_WITH_RAB state CHANGE TO RABM_NULL state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;

            default:
                /*��ӡ������Ϣ--- ��NSAPI����Ӧ��״̬����:*/
                RABM_LOG1_ERROR( "NAS_RabmDeal3GTo2GSuspendIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
        }
    }

}


VOS_VOID  NAS_RabmSndSnSaveDataInd(VOS_VOID)
{
    VOS_UINT32                      ulLength;
    RABM_SNDCP_SAVE_DATA_IND_MSG    *pSaveDataInd;

    ulLength     = sizeof( RABM_SNDCP_SAVE_DATA_IND_MSG ) - VOS_MSG_HEAD_LENGTH;
    pSaveDataInd = ( RABM_SNDCP_SAVE_DATA_IND_MSG *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );

    if ( VOS_NULL_PTR == pSaveDataInd )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmSndSnSaveDataInd:ERROR:Allocates a message packet for RABM_SNDCP_SAVE_DATA_IND_MSG FAIL!" );

        return;
    }

    /*��д��Ϣͷ:*/
    pSaveDataInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSaveDataInd->ulSenderPid     = WUEPS_PID_RABM;
    pSaveDataInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSaveDataInd->ulReceiverPid   = UEPS_PID_SN;
    pSaveDataInd->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pSaveDataInd->usMsgType       = ID_RABM_SNDCP_SAVE_DATA_IND;
    pSaveDataInd->usPId           = 5;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pSaveDataInd ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmSndSnSaveDataInd:WARNING:SEND RABM_SNDCP_SAVE_DATA_IND_MSG msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmSndSnSaveDataInd:NORMAL:SEND RABM_SNDCP_SAVE_DATA_IND_MSG Msg" );
    }

    return;
}




VOS_VOID  NAS_RabmSndSnDataResumeInd(VOS_VOID)
{
    VOS_UINT32                      ulLength;
    RABM_SNDCP_RESUME_DATA_IND_MSG  *pResumeDataInd;

    ulLength       = sizeof( RABM_SNDCP_RESUME_DATA_IND_MSG ) - VOS_MSG_HEAD_LENGTH;
    pResumeDataInd = ( RABM_SNDCP_RESUME_DATA_IND_MSG *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );

    if ( VOS_NULL_PTR == pResumeDataInd )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmSndSnDataResumeInd:ERROR:Allocates a message packet for RABM_SNDCP_RESUME_DATA_IND_MSG FAIL!" );

        return;
    }

    /*��д��Ϣͷ:*/
    pResumeDataInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pResumeDataInd->ulSenderPid     = WUEPS_PID_RABM;
    pResumeDataInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pResumeDataInd->ulReceiverPid   = UEPS_PID_SN;
    pResumeDataInd->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pResumeDataInd->usMsgType       = ID_RABM_SNDCP_RESUME_DATA_IND;
    pResumeDataInd->usPId           = 5;
    /*��дNSAPI��RB��ӳ���ϵ:*/
    PS_MEM_CPY( (VOS_VOID *)pResumeDataInd->astNsapiMapRb, (VOS_VOID *)gastNsapiMapRb, sizeof(SNDCP_NSAPI_MAP_RB_INFO) * SNDCP_RABM_MAX_NSAPI_NUM );

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pResumeDataInd ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmSndSnDataResumeInd:WARNING:SEND RABM_SNDCP_RESUME_DATA_IND_MSG msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmSndSnDataResumeInd:NORMAL:SEND RABM_SNDCP_RESUME_DATA_IND_MSG Msg" );
    }

    return;
}
VOS_VOID  NAS_RabmSndPdcpDataResumeInd(RRRABM_RAB_IND_STRU  *pMsg)
{
    VOS_UINT8                       ucLoop;
    VOS_UINT32                      ulLoop;
    VOS_UINT8                       ucEntId;
    VOS_UINT8                       ucRabId;
    VOS_UINT32                      ulLength;
    RABM_PDCP_DATA_RESUME_IND_STRU  *pDataResumeInd;

    ulLength       = sizeof( RABM_PDCP_DATA_RESUME_IND_STRU ) - VOS_MSG_HEAD_LENGTH;
    pDataResumeInd = (RABM_PDCP_DATA_RESUME_IND_STRU *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );

    if ( VOS_NULL_PTR == pDataResumeInd )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmSndPdcpDataResumeInd:ERROR:Allocates a message packet for RABM_PDCP_DATA_RESUME_IND_STRU FAIL!" );

        return;
    }

    /*��д��Ϣͷ:*/
    pDataResumeInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pDataResumeInd->ulSenderPid     = WUEPS_PID_RABM;
    pDataResumeInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDataResumeInd->ulReceiverPid   = WUEPS_PID_PDCP;
    pDataResumeInd->ulLength        = ulLength;
    pDataResumeInd->enMsgName       = ID_RABM_PDCP_DATA_RESUME_IND;

    /*��ʼ��FLAG:*/
    for ( ucLoop = 0; ucLoop < PS_NSAPI_NUM; ucLoop++ )
    {
        /*��ʼ��FLAG:*/
        pDataResumeInd->astNsapiMapRb[ucLoop].enValidInd = PS_FALSE;
    }

    /*��дRB��Ϣ*/
    for(ulLoop = 0; ulLoop < pMsg->ulRabCnt; ulLoop++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[ulLoop].ulCnDomainId)
        {
            ucEntId = (VOS_UINT8)((pMsg->aRabInfo[ulLoop].ulRabId & 0x0f) - RABM_NSAPI_OFFSET);
            ucRabId = (VOS_UINT8)(pMsg->aRabInfo[ulLoop].ulRabId);
            if( RABM_NSAPI_ACTIVE_NO_RAB == g_aRabmPsEnt[ucEntId].ucState )
            {
                pDataResumeInd->astNsapiMapRb[ucRabId].enValidInd = PS_TRUE;
                pDataResumeInd->astNsapiMapRb[ucRabId].ucRbId = (VOS_UINT8)(pMsg->aRabInfo[ulLoop].aulRbId[0]);
            }
        }
    }


    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pDataResumeInd ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmSndPdcpDataResumeInd:WARNING:SEND RABM_PDCP_DATA_RESUME_IND msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmSndPdcpDataResumeInd:NORMAL:SEND RABM_PDCP_DATA_RESUME_IND Msg" );
    }

    return;
}





VOS_VOID  NAS_RabmRcvPdcpDataResumeRsp(VOS_VOID *pMsg)
{
    /*��ӡ������Ϣ--�յ�PDCP_RABM_DATA_RESUME_RSP_STRU��Ϣ:*/
    RABM_LOG_NORMAL("NAS_RabmRcvPdcpDataResumeRsp:NORMAL:Recv PDCP_RABM_DATA_RESUME_RSP_STRU msg");

    return;
}
VOS_UINT32  NAS_RabmSndPdcpSaveDataInd(VOS_VOID)
{
    VOS_UINT32                      ulLength;
    VOS_UINT32                      ulResult;
    RABM_PDCP_SAVE_DATA_IND_STRU    *pSaveDataInd;

    ulLength     = sizeof( RABM_PDCP_SAVE_DATA_IND_STRU ) - VOS_MSG_HEAD_LENGTH;
    pSaveDataInd = (RABM_PDCP_SAVE_DATA_IND_STRU *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pSaveDataInd )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmSndPdcpSaveDataInd:ERROR:Allocates a message packet for RABM_PDCP_SAVE_DATA_IND_STRU msg FAIL!" );

        return RABM_FAILURE;
    }

    /*��д��Ϣͷ:*/
    pSaveDataInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSaveDataInd->ulSenderPid     = WUEPS_PID_RABM;
    pSaveDataInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSaveDataInd->ulReceiverPid   = WUEPS_PID_PDCP;
    pSaveDataInd->ulLength        = ulLength;
    pSaveDataInd->enMsgName       = ID_RABM_PDCP_SAVE_DATA_IND;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pSaveDataInd ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmSndPdcpSaveDataInd:WARNING:SEND RABM_PDCP_SAVE_DATA_IND_STRU msg FAIL!" );

        ulResult = RABM_SUCCESS;
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmSndPdcpSaveDataInd:NORMAL:SEND RABM_PDCP_SAVE_DATA_IND_STRU Msg" );

        ulResult = RABM_FAILURE;
    }

    return ulResult;
}
VOS_VOID  NAS_RabmRcvPdcpSaveDataRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                       ucLoop,i,ucFlag;
    PDCP_RABM_SAVE_DATA_RSP_STRU    *pSaveDataRsp;

    pSaveDataRsp = (PDCP_RABM_SAVE_DATA_RSP_STRU *)pMsg;

    if ( pSaveDataRsp->ucRbCnt > PS_WUE_MAX_PS_RB_NUM )
    {
        /*��ӡ������Ϣ---��Ϣ��ָʾ��RB��������PDCP_RABM_MAX_ENT_NUM:*/
        RABM_LOG_WARNING( "NAS_RabmRcvPdcpSaveDataRsp:WARNING:RB count in the msg is beyond PDCP_RABM_MAX_ENT_NUM!" );
        return;
    }

    /*��ʼ��gPdcpRcvNpduNumȫ�ֱ���:*/
    PS_MEM_SET( (VOS_VOID *)(&gPdcpRcvNpduNum), 0, sizeof(RABM_PDCP_GET_N_PDU_NUM_LIST_ST) );

    for ( ucLoop = 0; ucLoop < pSaveDataRsp->ucRbCnt; ucLoop++ )
    {
        ucFlag = VOS_FALSE;

        for ( i = 0; i < RABM_3G_PS_MAX_ENT_NUM; i++ )
        {
            if ( g_aRabmPsEnt[i].RabInfo.ucRbNum != 0 )
            {
                if ( g_aRabmPsEnt[i].RabInfo.aucRbId[0]
                     == pSaveDataRsp->astPdcpNumInfo[ucLoop].ucRbId )
                {
                    gPdcpRcvNpduNum.aucNPDUNumList[i + RABM_2G_NSAPI_OFFSET][0] = 1;
                    gPdcpRcvNpduNum.aucNPDUNumList[i + RABM_2G_NSAPI_OFFSET][1] = pSaveDataRsp->astPdcpNumInfo[ucLoop].ucRcvNPduNum;

                    ucFlag = VOS_TRUE;
                    break;
                }
            }
        }

        if ( VOS_TRUE != ucFlag )
        {
            /*��ӡ������Ϣ---��Ϣ��ָʾ��RBδ�ҵ���Ӧ��NSAPI:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvPdcpSaveDataRsp:WARNING:Can't find NSAPI match to RbId in the msg ! RbId = ",
                               pSaveDataRsp->astPdcpNumInfo[ucLoop].ucRbId );
        }
    }

    return;
}
VOS_VOID  NAS_RabmSaveNsapiMapRbInfo(VOS_VOID)
{
    VOS_UINT8       ucLoop;

    for  ( ucLoop = 0; ucLoop < SNDCP_RABM_MAX_NSAPI_NUM; ucLoop++ )
    {
        if ( ucLoop < RABM_MIN_NSAPI_NUMBER )
        {
            gastNsapiMapRb[ucLoop].ucFlag = PS_FALSE;
            continue;
        }


        if ( RABM_NSAPI_ACTIVE_WITH_RAB == g_aRabmPsEnt[ucLoop - RABM_2G_NSAPI_OFFSET].ucState )
        {
            gastNsapiMapRb[ucLoop].ucFlag = PS_TRUE;
            gastNsapiMapRb[ucLoop].ucRbId = g_aRabmPsEnt[ucLoop - RABM_2G_NSAPI_OFFSET].RabInfo.aucRbId[0];
        }
        else
        {
            gastNsapiMapRb[ucLoop].ucFlag = PS_FALSE;
        }

    }

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
