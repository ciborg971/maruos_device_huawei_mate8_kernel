

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"
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

#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALTIMEOUTMSG_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


VOS_VOID  NAS_RabmTimerExpiredMsgDispatch( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    switch ( pTimerExpiredMsg->ulPara )           /*��ʱ��Ϣ�ַ�*/
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
            /*��ӡ������Ϣ---�յ���ʱ��Ϣ:*/
            RABM_LOG_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.rout.area.update.T1 Timer Expired Msg" );

            NAS_RabmRoutingAreaUpdateT1Expired( pTimerExpiredMsg );
            break;

        case RABM_TIMER_PARA_3_TO_2_T3:
            /*��ӡ������Ϣ---�յ���ʱ��Ϣ:*/
            RABM_LOG_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg" );

            NAS_Rabm3GTo2GT3Expired( pTimerExpiredMsg );
            break;
        case RABM_TIMER_PARA_ACT_REQ_T1:
            /*��ӡ������Ϣ---�յ���ʱ��Ϣ:*/
            RABM_LOG1_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.act.req.T1 Timer Expired Msg!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );

            NAS_RabmActReqT1Expired( pTimerExpiredMsg );
            break;
        case RABM_TIMER_PARA_REESTRAB_TIMER:
            /*��ӡ������Ϣ--- �յ������߼�����Ϣ:*/
            RABM_LOG_WARNING( "NAS_RabmTimerExpiredMsgDispatch:WARNING:RECEIVE Rabm.ReestRab Expired Msg is ILLOGICAL in 2G mode!" );
            break;
        default:
            /*��ӡ������Ϣ--- ��ʱ��Ϣ��ulPara�ֶγ���:*/
            RABM_LOG_WARNING( "NAS_RabmTimerExpiredMsgDispatch:WARNING:RECEIVE an ERROR Expired Msg(The PARA item of the msg is WRONG)!" );
            break;
    }
}




VOS_VOID  NAS_RabmRoutingAreaUpdateT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    VOS_UINT8                               ucLoop;
    VOS_UINT32                              ulLength;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG    *pstRAUpdateRsp;

    /*�ж���ڲ����Ƿ�Ϸ�:*/
    if ( RABM_TIMER_NAME_COMMON != pTimerExpiredMsg->ulName )
    {
        /*��ӡ������Ϣ---��ʱ��Ϣ���ֳ���:*/
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:The Name of the Rabm.rout.area.update.T1 Expired Msg is WRONG!" );
        return;
    }

    if ( RABM_ROUTING_AREA_UPDATE_T1_ON != gRabmRAT1Switch )    /*��δ��Rabm.rout.area.update.T1��ʱ��*/

    {
        /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:RECEIVE Rabm.rout.area.update.T1 Timer Expired Msg is ILLOGICAL because Rabm.rout.area.update.T1 Timer hasn't started!" );
        return;
    }

    /*���ͽ�Rx N-PDU numbers��Ϊ0��GMMRABM_ROUTING_AREA_UPDATE_RSP��Ϣ:*/
    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pstRAUpdateRsp )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmRoutingAreaUpdateT1Expired:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
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
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is 0) msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmRoutingAreaUpdateT1Expired:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is 0) Msg" );
    }

    /*��λRabm.rout.area.update.T1��ʱ����־:*/
    gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_OFF;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*����2G�е�ÿ��NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*��NSAPI��״̬*/
        {
            case RABM_2G_NULL:
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                  /*������״̬�Ĵ���ʽһ��*/
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*����NSAPI��״̬��ΪRABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            default:
                /*��ӡ������Ϣ---��NSAPI��״̬�ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_RabmRoutingAreaUpdateT1Expired:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }
}
VOS_VOID  NAS_RabmActReqT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    /*�ж���ڲ����Ƿ�Ϸ�:*/
    if ( pTimerExpiredMsg->ulName > RABM_TIMER_NAME_NSAPI_15 )
    {
        /*��ӡ������Ϣ---NSAPI������Χ:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:The NSAPI item of the Msg is BEYOND Range!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
        return;
    }

    /*��δ��Rabm.act.req.T1��ʱ��:*/
    if ( RABM_ACT_REQ_T1_ON != gaRabmActReqT1Switch[pTimerExpiredMsg->ulName] )     /*��δ�򿪸�NSAPI��Rabm.act.req.T1��ʱ��*/
    {
        /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:RECEIVE Rabm.act.req.T1 Timer Expired Msg is ILLOGICAL because Rabm.act.req.T1 Timer hasn't started!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
        return;
    }

    /*��λ��NSAPI��Rabm.act.req.T1��ʱ����־:*/
    gaRabmActReqT1Switch[pTimerExpiredMsg->ulName] = RABM_ACT_REQ_T1_OFF;

    if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[pTimerExpiredMsg->ulName].State )  /*����NSAPI����RABM_NSAPI_OK_TRANSMODE_NO״̬*/
    {
        /*����NSAPI����Ϊ��ȷ��ģʽ:*/
        gastRabm2GEntity[pTimerExpiredMsg->ulName].TransMode = RABM_ADM_ENUM;
        /*��ӡ������Ϣ---����ģʽ��Ϊ��ȷ��ģʽ:*/
        RABM_LOG1_NORMAL( "NAS_RabmActReqT1Expired:Transmode set to ADM mode: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );

        /*����NSAPI��״̬��ΪRABM_DATA_TRANS_READY:*/
        RABM_SetGState((RABM_NSAPI_ENUM)(pTimerExpiredMsg->ulName), RABM_DATA_TRANS_READY);

        /*��ӡ������Ϣ---״̬�л�:*/
        RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
    }
    else
    {
        /*��ӡ������Ϣ---��NSAPI������״̬�����߼�:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:The NSAPI's state is ILLOGICAL when RECEIVE Rabm.act.req.T1 Timer Expired Msg!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
    }
}


VOS_VOID  NAS_Rabm3GTo2GT3Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    VOS_UINT8               ucLoop;
    ST_APP_RABM_STATUS      stReportStatus;

    /*�ж���ڲ����Ƿ�Ϸ�:*/
    if ( RABM_TIMER_NAME_COMMON != pTimerExpiredMsg->ulName )
    {
        /*��ӡ������Ϣ---��ʱ��Ϣ���ֳ���:*/
        RABM_LOG_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:The Name of the Rabm.Sys.3To2.T3 Timer Expired Msg is WRONG!" );
        return;
    }

    if ( RABM_3G_TO_2G_T3_ON != gRabm3GTo2GT3Switch )         /*��δ��Rabm.Sys.3To2.T3��ʱ��*/
    {
        /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
        RABM_LOG_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL because Rabm.Sys.3To2.T3 Timer hasn't started!" );
        return;
    }

    /*��λRabm.3To2.T3��ʱ����־:*/
    gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_OFF;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )    /*����2G��ÿ��NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_2G_NULL:
                /*��ӡ������Ϣ---״̬����:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state keep the same: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                  /*������״̬�Ĵ���ʽһ��*/
                /*��ӡ������Ϣ---��NSAPI����Ӧ��״̬�����߼�:*/
                if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_DATA_TRANS_READY state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_DATA_TRANS_STOP state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*��APP�ϱ�TAFRABM_STARTSTOP_IND(START)��Ϣ:*/
                stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPP��ʼ���ݴ���*/
                /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                /*��״̬��ΪRABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            default:
                /*��ӡ������Ϣ---NSAPI��Ӧ��״̬�ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_Rabm3GTo2GT3Expired:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
        }
    }

    /*�ͷ���3G��2G�л���ʼʱPDCP���������:*/
    SN_RabmClear3G2Share();
}
VOS_VOID NAS_RABM_ProcTiRabReestRequestExpired(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_ProcTiRabReestRequestExpired: RABM_TIMER_PARA_REESTRAB_TIMER");

    /* ���RAB�ؽ���ʱ��������ʶ */
    NAS_RABM_ClearRabRsestTimerFlg();

    /* ����RABMʵ��, ֪ͨCDSģ���ͷŴ���ҵ���ؽ��Ļ��� */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
        {
            NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);
            NAS_RABM_SndCdsFreeBuffDataInd(ucEntId + RABM_NSAPI_OFFSET);
        }
    }

    return;
}


VOS_VOID NAS_RABM_ProcTiRabReestPendingExpired(VOS_UINT8 ucRabId)
{
    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_ProcTiRabReestPendingExpired: RABM_TIMER_RAB_REESTABLISH_PENDING");

    /* ���ʵ���ؽ���ʶ */
    NAS_RABM_ClearWPsEntRabReestFlg(ucRabId - RABM_NSAPI_OFFSET);

    /* ֪ͨCDS�����ؽ�ʧ�� */
    NAS_RABM_SndCdsFreeBuffDataInd(ucRabId);

    return;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
