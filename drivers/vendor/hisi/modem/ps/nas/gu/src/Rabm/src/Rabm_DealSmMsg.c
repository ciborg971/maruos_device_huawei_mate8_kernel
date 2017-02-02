

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALSMMSG_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*��ʶ�����ϱ���ʱ���Ƿ�����*/
extern RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM_U32  g_stRabmWriteFluxToNvTimerSwitch;



/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


VOS_VOID  NAS_RabmSmPdpActivateIndMsg( VOS_VOID *pMsg )
{
    RABMSM_ACTIVATE_IND_STRU           *pstPdpActivateIndMsg;
    RABM_NSAPI_ENUM                     NsapiIndex;
    QCI_TYPE_ENUM_UINT8                 enQci;

    pstPdpActivateIndMsg = ( RABMSM_ACTIVATE_IND_STRU * )pMsg;

    if ( ( pstPdpActivateIndMsg->ulNsapi < RABM_MIN_NSAPI_NUMBER )
        || ( pstPdpActivateIndMsg->ulNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*��ӡ������Ϣ---�����Ϣ�Ƿ�:*/
        RABM_LOG_WARNING( "NAS_RabmSmPdpActivateIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!" );

        return;
    }

    if ( ( RABMSM_ACT_MSG_1 != pstPdpActivateIndMsg->ulActMsgType )
         && ( RABMSM_ACT_MSG_2 != pstPdpActivateIndMsg->ulActMsgType ) )
    {
        /*��ӡ������Ϣ---�����Ϣ����Ϣ�ı�ʶ�Ƿ�:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpActivateIndMsg:WARNING:The MsgType item of the Entry Parameter is ERROR!: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpActivateIndMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )    /*��NSAPI����Ӧ��״̬*/
    {
        case RABM_2G_NULL:
            if ( RABMSM_ACT_MSG_1 == pstPdpActivateIndMsg->ulActMsgType )
            {
                /*��ӡ������Ϣ---�յ���һ��PDP������Ϣ:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:RECEIVE The FIRST PdpActivateInd Msg: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*��ȡucPppFlg:*/
                if( RABM_SM_PPP_PROT == pstPdpActivateIndMsg->ulPppFlag )
                {
                    gastRabm2GEntity[NsapiIndex].ucPppFlg = RABM_SM_PPP_PROT;
                }
                else
                {
                    gastRabm2GEntity[NsapiIndex].ucPppFlg = RABM_SM_IP_PROT;
                }

                return;
            }

            if ((RABMSM_ACT_MSG_2 == pstPdpActivateIndMsg->ulActMsgType)
             && (VOS_TRUE == NAS_RABM_GetDataSuspendFlg()))
            {
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state CHANGE TO RABM_DATA_TRANS_STOP state: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*����NSAPI��״̬��ΪRABM_DATA_TRANS_STOP:*/
                RABM_SetGState(NsapiIndex, RABM_DATA_TRANS_STOP);
            }
            else
            {
                /*����Rabm.act.req.T1��ʱ��:*/
                NAS_RabmStartTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );

                /*��ӡ������Ϣ---������Rabm.act.req.T1��ʱ��:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:Start Rabm.act.req.T1 Timer SUCCESS: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*����NSAPI��״̬��ΪRABM_NSAPI_OK_TRANSMODE_NO:*/
                RABM_SetGState(NsapiIndex, RABM_NSAPI_OK_TRANSMODE_NO);

                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state CHANGE TO RABM_NSAPI_OK_TRANSMODE_NO state: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );
            }

            gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpActivateIndMsg->Qos.ulLength;
            PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                       pstPdpActivateIndMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);

            /*����RAB_MAPӳ��ʵ��*/
            NAS_RABM_CreateRabMapEntity((VOS_UINT8)(pstPdpActivateIndMsg->ulNsapi),
                                        (VOS_UINT8)(pstPdpActivateIndMsg->ulLinkdNsapi),
                                        (VOS_UINT8)(pstPdpActivateIndMsg->ulNsapi));

            /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
            enQci = NAS_RABM_GetQciFromQos(gastRabm2GEntity[NsapiIndex].stQos.ulQosLength,
                                           gastRabm2GEntity[NsapiIndex].stQos.aucQosValue);

            NAS_RABM_SndCdsQosFcRabCreateInd(NsapiIndex + RABM_NSAPI_OFFSET, enQci);
            break;
        case RABM_NSAPI_OK_TRANSMODE_NO:
        case RABM_DATA_TRANS_READY:
        case RABM_ROUT_AREA_UPDATE:
        case RABM_DATA_TRANS_STOP:                     /*��������ַǿ�״̬�µ�NSAPI����ֻ����QoS�ĸ��£��ʴ���ʽһ��*/
            if ( RABMSM_ACT_MSG_1 == pstPdpActivateIndMsg->ulActMsgType )
            {
                /*��ӡ������Ϣ---�յ���һ��PDP������Ϣ:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:RECEIVE The FIRST PdpActivateInd Msg: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                return;
            }

            /*��ӡ������Ϣ---��ʱ��NSAPI�Ѽ���ʸ���Qos:*/
            RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:This NSAPI has been Activated,so UPDATE the QoS: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

            gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpActivateIndMsg->Qos.ulLength;
            PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                       pstPdpActivateIndMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);

            break;
        default:
            /*��ӡ������Ϣ---��NSAPI��״̬�ֶγ���:*/
            RABM_LOG1_ERROR( "NAS_RabmSmPdpActivateIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );
            break;
    }

    return;
}
VOS_VOID  NAS_RabmSmPdpDeactivateIndMsg( VOS_VOID *pMsg )
{
    VOS_UINT8                            ucLoop;
    RABM_NSAPI_ENUM                      NsapiIndex;
    RABMSM_DEACTIVATE_IND_STRU          *pstPdpDeactiveIndMsg;

    pstPdpDeactiveIndMsg = ( RABMSM_DEACTIVATE_IND_STRU * )pMsg;

    if ( pstPdpDeactiveIndMsg->ulDeactiveNum > RABM_2G_MAX_ENT_NUM )
    {
        RABM_LOG_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:The DeactiveNum item of the Entry Parameter is BEYOND range!" );
        return;
    }

    for ( ucLoop = 0; ucLoop < pstPdpDeactiveIndMsg->ulDeactiveNum; ucLoop++ )/*������Ϣ��ָʾ����ȥ�����NSAPI�ĸ���*/
    {
        if ( ( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] < RABM_MIN_NSAPI_NUMBER )
             || ( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] > RABM_MAX_NSAPI_NUMBER ) )
        {
            /*��ӡ������Ϣ---��Ϣ�е�NSAPI���ڷ�Χ֮��:*/
            RABM_LOG1_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
            continue;
        }

        NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] - RABM_2G_NSAPI_OFFSET );

        switch ( gastRabm2GEntity[NsapiIndex].State )   /*��NSAPI����Ӧ��״̬*/
        {
            case RABM_2G_NULL:
                /*��ӡ������Ϣ---״̬����:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state keep the same: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
                if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[NsapiIndex] )   /*������Rabm.act.req.T1��ʱ��*/
                {
                    /*�ر�Rabm.act.req.T1��ʱ��:*/
                    NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );
                }

                /*����NSAPI��״̬��ΪRABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );

                /*���QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            case RABM_ROUT_AREA_UPDATE:
                if ( RABM_NO == NAS_RabmQueryRAUState( NsapiIndex ) )
                {
                    if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )    /*������rout.area.update.T1��ʱ��*/
                    {
                        /*�ر�rout.area.update.T1��ʱ��:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );
                    }
                    else
                    {
                        if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )         /*������Rabm.sys.3To2.T3��ʱ��*/
                        {
                            /*�ر�Rabm.sys.3To2.T3��ʱ��:*/
                            NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
                        }
                    }
                }

                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                /*����NSAPI��״̬��ΪRABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*���QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            case RABM_DATA_TRANS_READY:
                /*no break here*/
            case RABM_DATA_TRANS_STOP:
                /*��ӡ������Ϣ---״̬�л�:*/
                if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[NsapiIndex].State )
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                }
                else
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                }
                /*����NSAPI��״̬��ΪRABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*���QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            default:
                /*��ӡ������Ϣ---��NSAPI����Ӧ��״̬�ֶγ���:*/
                RABM_LOG1_ERROR( "NAS_RabmSmPdpDeactivateIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                /*����NSAPI��״̬��ΪRABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*��ӡ������Ϣ---����״̬�����NSAPI��״̬��ΪRABM_2G_NULL:*/
                RABM_LOG1_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:Set this NSAPI's state to RABM_2G_NULL!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );

                /*���QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
        }

        /*ɾ��RAB_MAPʵ��*/
        RABM_DelRabMap((VOS_UINT8)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]));
    }

    return;
}




VOS_VOID  NAS_RabmSmPdpModifyIndMsg( VOS_VOID *pMsg )
{
    RABMSM_MODIFY_IND_STRU             *pstPdpModifyIndMsg;
    RABM_NSAPI_ENUM                     NsapiIndex;
    QCI_TYPE_ENUM_UINT8                 enQci;

    pstPdpModifyIndMsg = ( RABMSM_MODIFY_IND_STRU * )pMsg;

    /*��ӡ������Ϣ---�յ���Ϣ:*/
    RABM_LOG1_NORMAL( "NAS_RabmSmPdpModifyIndMsg:NORMAL:RECEIVE RABMSM_MODIFY_IND Msg: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );

    if ( ( pstPdpModifyIndMsg->ulNsapi < RABM_MIN_NSAPI_NUMBER )
         || ( pstPdpModifyIndMsg->ulNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*��ӡ������Ϣ---��Ϣ�е�NSAPI���ڷ�Χ֮��:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpModifyIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );

        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpModifyIndMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    if ( ( gastRabm2GEntity[NsapiIndex].State >= RABM_NSAPI_OK_TRANSMODE_NO )
         && ( gastRabm2GEntity[NsapiIndex].State <= RABM_DATA_TRANS_STOP ) )
    {
        /*���¸�NSAPI�е�QoS����:*/
        gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpModifyIndMsg->Qos.ulLength;
        PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                   pstPdpModifyIndMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);

        /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
        enQci = NAS_RABM_GetQciFromQos(gastRabm2GEntity[NsapiIndex].stQos.ulQosLength,
                                       gastRabm2GEntity[NsapiIndex].stQos.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(NsapiIndex + RABM_NSAPI_OFFSET, enQci);

    }
    else if ( RABM_2G_NULL == gastRabm2GEntity[NsapiIndex].State )
    {
        /*��ӡ������Ϣ---��NSAPIδ����:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpModifyIndMsg:WARNING:This NSAPI hasn't been activated!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );
    }
    else
    {
        /*��ӡ������Ϣ---��NSAPI��״̬����:*/
        RABM_LOG1_ERROR( "NAS_RabmSmPdpModifyIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );
    }

    return;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
