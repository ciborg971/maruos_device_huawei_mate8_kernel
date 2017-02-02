

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"
#include "NasRabmMsgProc.h"
#include "NVIM_Interface.h"
#include "NasUtranCtrlInterface.h"
#include "WasNvInterface.h"
#include "NasRabmFastdorm.h"

#if(FEATURE_ON == FEATURE_BASTET)
#include "BastetRabmInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_ASSISTANT_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/*2G��RABMʵ��Ľṹ������*/
RABM_2G_ENTITY_ST                                           gastRabm2GEntity[RABM_2G_MAX_ENT_NUM];

/*���Լ�¼3G�з���3G��2G�л�ʱ���ڷ����л�ǰ������״̬*/
VOS_UCHAR                                                   gaucRabm3GPreState[RABM_3G_PS_MAX_ENT_NUM];

/*��ʶ��ǰ�Ƿ����ڽ���2G��3G���л�*/
RABM_2G_TO_3G_SWITCH_ENUM                                   gRabm2GTo3GSwitch;

/*��ʶ��ǰ�Ƿ����ڽ���3G��2G���л�*/
RABM_3G_TO_2G_SWITCH_ENUM                                   gRabm3GTo2GSwitch;

/*��ʶ2G��·�������¶�ʱ���Ƿ�����*/
RABM_RA_T1_SWITCH_ENUM_UINT8                                gRabmRAT1Switch;

/*��ʶRabm.Act.Req.T1��ʱ���Ƿ�����*/
RABM_ACT_REQ_T1_SWITCH_ENUM_UINT8                           gaRabmActReqT1Switch[RABM_2G_MAX_ENT_NUM];

/*��ʶRabm.2To3.T1��ʱ���Ƿ�����*/
RABM_2G_TO_3G_T1_SWITCH_ENUM                                gRabm2GTo3GT1Switch;

/*��ʶRabm.3To2.T1��ʱ���Ƿ�����*/
RABM_3G_TO_2G_T1_SWITCH_ENUM                                gRabm3GTo2GT1Switch;

/*��ʶRabm.3To2.T3��ʱ���Ƿ�����*/
RABM_3G_TO_2G_T3_SWITCH_ENUM_UINT8                          gRabm3GTo2GT3Switch;

/*��ʶRabm.3To2.RA.Update��ʱ���Ƿ�����*/
RABM_3G_TO_2G_RA_UPDATE_SWITCH_ENUM                         gRabm3GTo2GRAUpdateSwitch;

/*TLLI��ȫ�ֱ���*/
VOS_UINT32                                                  gulRabmTLLI;

/*��ʱ��ʱ������(�Զ�ʱ����PARAö����Ϊ����)*/
VOS_UINT32                                                  gaulRabmTimerLength[RABM_TIMER_PARA_BUTT];

/*ʵ�嶨ʱ��(�Զ�ʱ����NAMEö����Ϊ����)*/
HTIMER                                                      gastRabmEntityTimer[RABM_MAX_ENT_NUM];

/*���ö�ʱ��(�Զ�ʱ����PARAö����Ϊ����)*/
HTIMER                                                      gastRabmCommonTimer[RABM_COMMON_TIMER_NUMBER];

/*��ʶ��һ�λ�ȡ�����Ƿ����*/
RABM_GET_CUR_NET_FIRSTTIME_ENUM                             gRabmGetCurNetFirsttime;

/*��ʶ��ǰ����������ģʽ*/
RABM_CUR_NET_ENUM                                           gRabmCurNet;

/*2G��3G�л��������ָ��ı�־*/
VOS_UINT32                                                  gRabm2GTo3GDataResume;

/*3G��2G�л�ʱ��RABM����NSAPI��RB��ӳ���ϵ*/
SNDCP_NSAPI_MAP_RB_INFO                                     gastNsapiMapRb[SNDCP_RABM_MAX_NSAPI_NUM];

NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmFDFluxDetectTimer;
NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmFDRetryTimer;
NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmFDWaitGmmQryRsltTimer;
NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmResendEstTimer;

NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmVPDelayTimer;
NAS_RABM_TIMER_STATUS_ENUM_UINT8                           g_ulNasRabmVPReQryGmmDelayTimer;

/*RABM��PDCP����֪��RCV NPDU NUM ��Ϣ*/
RABM_PDCP_GET_N_PDU_NUM_LIST_ST                             gPdcpRcvNpduNum;

#if (FEATURE_ON == FEATURE_LTE)
/* L->G���, ���ڱ��L->G������ */
VOS_UINT32                              g_ulNasRabmL2GFlg = VOS_FALSE;
#endif

RAB_AS_UL_DATA_CALLBACK_STRU g_astRabAsUlDataCallBack[] =
{
  /*====ucMode===,  =========ucState=========,  usRsv   =====pAsUlDataCallBack=====*/

    {RABM_3G_ENUM,  RABM_NULL,                  0,      VOS_NULL_PTR                    },
    {RABM_3G_ENUM,  RABM_NSAPI_ACTIVE_PENDING,  0,      RABM_SndRABMUlDataCallBack},
    {RABM_3G_ENUM,  RABM_NSAPI_ACTIVE_NO_RAB,   0,      RABM_SndRABMUlDataCallBack},
    {RABM_3G_ENUM,  RABM_NSAPI_ACTIVE_WITH_RAB, 0,      RABM_SndPdcpUlDataCallBack     },
    {RABM_3G_ENUM,  RABM_DATA_TRANSFER_STOP,    0,      RABM_SndRABMUlDataCallBack},
    {RABM_3G_ENUM,  RABM_ACT_PENDING_WITH_RAB,  0,      RABM_SndRABMUlDataCallBack},
    {RABM_3G_ENUM,  RABM_TC_STATE_NULL,         0,      VOS_NULL_PTR                    },
    {RABM_3G_ENUM,  RABM_TC_STATE_WITH_RAB,     0,      VOS_NULL_PTR                    },
    {RABM_2G_ENUM,  RABM_2G_NULL,               0,      VOS_NULL_PTR                    },
    {RABM_2G_ENUM,  RABM_NSAPI_OK_TRANSMODE_NO, 0,      RABM_SndRABMUlDataCallBack },
    {RABM_2G_ENUM,  RABM_DATA_TRANS_READY,      0,      RABM_SndSndcpUlDataCallBack    },
    {RABM_2G_ENUM,  RABM_ROUT_AREA_UPDATE,      0,      RABM_SndRABMUlDataCallBack },
    {RABM_2G_ENUM,  RABM_DATA_TRANS_STOP,       0,      RABM_SndRABMUlDataCallBack }
};

/* ======================== */    /* RABӳ��ʵ�壬��RAB IDΪ�����±꣬��Ч����[5,15] */
RAB_MAP_STRU    g_astRabMap[PS_WUE_MAX_RB_ID + 1];


/* ======================== */    /* RB ID��RAB ID�Ŀ���������,���Ч�ʣ���Ч��Χ[5,32] */
VOS_UINT8       g_aucRb2Rab[PS_WUE_MAX_RB_ID + 1];


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
extern VOS_VOID  R_ITF_SetFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);


VOS_VOID  NAS_Rabm2GInit( VOS_VOID )
{
    VOS_UINT8                   ucLoop;
    NVIM_FASTDORM_PARA_STRU     stFastDormPara;
    VOS_UINT32                  ulRslt;


    PS_MEM_SET(&stFastDormPara, 0x00, sizeof(stFastDormPara));


    /*��ӡ������Ϣ---2G��RABMģ��ĳ�ʼ��:*/
    RABM_LOG_NORMAL( "NAS_Rabm2GInit:NORMAL:Start to Initial RABM module in 2G mode" );

    /*��ʼ����ʱ��ʱ������(��ʱ����)*/
    gaulRabmTimerLength[RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1] = 30000;

    gaulRabmTimerLength[RABM_TIMER_PARA_3_TO_2_T3]           = 30000;
    gaulRabmTimerLength[RABM_TIMER_PARA_ACT_REQ_T1]          = 30000;

    gaulRabmTimerLength[RABM_TIMER_FASTDORM_FLUX_DETECT]            = 1000;
    gaulRabmTimerLength[RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT]    = 2000;

    gaulRabmTimerLength[RABM_TIMER_FASTDORM_RETRY]                  = 2000;

    gaulRabmTimerLength[RABM_TIMER_RESEND_EST_REQ]                  = 500;

    gaulRabmTimerLength[RABM_TIMER_VOICEPREFER_DELAY] = 4000;
    gaulRabmTimerLength[RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY] = 4000;

    /* ��NVIM�ж�ȡW��FASTDORM������ز��� */
    ulRslt = NV_Read(en_NV_Item_Fastdorm_Para,
                     &stFastDormPara,
                     sizeof(NVIM_FASTDORM_PARA_STRU));
    /* �����ȡʧ�ܣ������ø��ֲ���ΪĬ��ֵ������ʧ�� */
    if (NV_OK != ulRslt)
    {
        RABM_LOG1_WARNING( "NAS_Rabm2GInit:Read NVIM Failed,ulRslt:", (VOS_INT32)ulRslt);
    }
    else
    {
        gaulRabmTimerLength[RABM_TIMER_FASTDORM_RETRY] = stFastDormPara.ucNasRetryInterval * 1000;
    }

    for ( ucLoop = 0; ucLoop < RABM_MAX_ENT_NUM; ucLoop++ )
    {
        gastRabmEntityTimer[ucLoop] = VOS_NULL_PTR;
    }
    for ( ucLoop = 0; ucLoop < RABM_COMMON_TIMER_NUMBER; ucLoop++ )
    {
        gastRabmCommonTimer[ucLoop] = VOS_NULL_PTR;
    }

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )
    {
        /*��ʼ��RABM״̬��:*/
        RABM_SetGState((RABM_NSAPI_ENUM)ucLoop,RABM_2G_NULL);
        gastRabm2GEntity[ucLoop].ucNsapi           = ( VOS_UINT8 )( ucLoop + RABM_2G_NSAPI_OFFSET );
        gastRabm2GEntity[ucLoop].TransMode         = RABM_ADM_ENUM;
        gastRabm2GEntity[ucLoop].stQos.ulQosLength = 0;
        gastRabm2GEntity[ucLoop].RAUpdateCause     = RABM_RA_UPDATE_CAUSE_BUTT;

        /*��ʼ��Rabm.Act.Req.T1��ʱ����־:*/
        gaRabmActReqT1Switch[ucLoop] = RABM_ACT_REQ_T1_OFF;

        PS_MEM_SET(gastRabm2GEntity[ucLoop].stQos.aucQosValue,
                   0x00,
                   sizeof(gastRabm2GEntity[ucLoop].stQos.aucQosValue));

    }

    /*��ʼ��2G����ʹ�õ�������ʱ����־:*/
    gRabmRAT1Switch           = RABM_ROUTING_AREA_UPDATE_T1_OFF;
    gRabm2GTo3GT1Switch       = RABM_2G_TO_3G_T1_OFF;
    gRabm3GTo2GT3Switch       = RABM_3G_TO_2G_T3_OFF;
    gRabm3GTo2GRAUpdateSwitch = RABM_3G_TO_2G_RA_UPDATE_OFF;

    /*��ʼ��2G��3G���л���ʶ:*/
    gRabm2GTo3GSwitch          = RABM_2G_TO_3G_SWITCH_OFF;

    /*��ʼ����һ�λ�ȡ�����Ƿ���ɵı�ʶ:*/
    gRabmGetCurNetFirsttime = RABM_GET_CUR_NET_FIRSTTIME_OFF;

    /*��ʼ��NSAPI��RB��ӳ���ϵ:*/
    PS_MEM_SET( (VOS_VOID *)gastNsapiMapRb, 0, sizeof(SNDCP_NSAPI_MAP_RB_INFO) * SNDCP_RABM_MAX_NSAPI_NUM );

    /*��ʼ��RCV NPDU NUM ��Ϣ:*/
    PS_MEM_SET( (VOS_VOID *)(&gPdcpRcvNpduNum), 0, sizeof(RABM_PDCP_GET_N_PDU_NUM_LIST_ST) );

    /*��ӡ������Ϣ---2G��RABMģ��ĳ�ʼ���ɹ�:*/
    RABM_LOG_NORMAL( "NAS_Rabm2GInit:NORMAL:Initial RABM module in 2G mode SUCCESS" );

    /*��ʼ��RAB_MAP��ʹ�õ������Ϣ:*/
    RABM_RabMapInit();

    return;
}
VOS_VOID NAS_RabmStartTimer( RABM_TIMER_NAME_ENUM Name, RABM_TIMER_PARA_ENUM Para )
{
    RABM_START_TIMER_ST                 *pstRabmStartTimer;
    RABM_START_TIMER_ST                  stRabmStartTimer;
    RABM_TIMER_NAME_ENUM                 EntityTimerName = ( RABM_TIMER_NAME_ENUM )0;

    pstRabmStartTimer = &stRabmStartTimer;

    if ((RABM_TIMER_NAME_COMMON == Name)
     || (RABM_TIMER_NAME_FD_RETRY == Name)
     || (RABM_TIMER_NAME_FD_FLUX_DETECT == Name))
    {
        pstRabmStartTimer->pstHTimer  = &gastRabmCommonTimer[Para];
        if ( RABM_TIMER_FASTDORM_FLUX_DETECT == Para )
        {
            pstRabmStartTimer->ucMode = VOS_RELTIMER_LOOP;
        }
        else
        {
            pstRabmStartTimer->ucMode = VOS_RELTIMER_NOLOOP;
        }
    }
    else
    {
        EntityTimerName               = Name;
        pstRabmStartTimer->pstHTimer  = &gastRabmEntityTimer[Name];
        pstRabmStartTimer->ucMode     = VOS_RELTIMER_NOLOOP;
    }

    /*���ö�ʱ������:*/
    pstRabmStartTimer->ulPid     = WUEPS_PID_RABM;
    pstRabmStartTimer->Name      = Name;
    pstRabmStartTimer->Param     = Para;
    pstRabmStartTimer->ulLength  = gaulRabmTimerLength[Para];

    /*����ָ����ʱ��:*/
    if ( VOS_OK != NAS_StartRelTimer( pstRabmStartTimer->pstHTimer,
                                      pstRabmStartTimer->ulPid,
                                      pstRabmStartTimer->ulLength,
                                      pstRabmStartTimer->Name,
                                      pstRabmStartTimer->Param,
                                      pstRabmStartTimer->ucMode ) )
    {
        RABM_LOG1_ERROR( "NAS_RabmStartTimer: Start Timer FAIL! Para:", Para);
    }

    /*��λ��ʱ��������־:*/
    switch ( Para )
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
            gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_ON;
            break;

        case RABM_TIMER_PARA_3_TO_2_T3:
            gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_ON;
            break;

        case RABM_TIMER_PARA_ACT_REQ_T1:
            gaRabmActReqT1Switch[EntityTimerName] = RABM_ACT_REQ_T1_ON;
            break;

        case RABM_TIMER_FASTDORM_FLUX_DETECT:                                            /* ������������ⶨʱ������ʱ�����Ƿ��������仯 */
            g_ulNasRabmFDFluxDetectTimer = NAS_RABM_TIMER_STATUS_RUNING;
            break;

        case RABM_TIMER_FASTDORM_RETRY:                                                  /* RETRY��ʱ������ʱ�����³���FD */
            g_ulNasRabmFDRetryTimer = NAS_RABM_TIMER_STATUS_RUNING;
            break;

        case RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT:
            g_ulNasRabmFDWaitGmmQryRsltTimer = NAS_RABM_TIMER_STATUS_RUNING;
            break;

        case RABM_TIMER_RESEND_EST_REQ:
            g_ulNasRabmResendEstTimer = NAS_RABM_TIMER_STATUS_RUNING;

        case RABM_TIMER_VOICEPREFER_DELAY:
            g_ulNasRabmVPDelayTimer = NAS_RABM_TIMER_STATUS_RUNING;
            break;

        case RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY:
            g_ulNasRabmVPReQryGmmDelayTimer = NAS_RABM_TIMER_STATUS_RUNING;
            break;

        default:
            break;
    }
    return;
}


NAS_RABM_TIMER_STATUS_ENUM_UINT8  NAS_RABM_CheckTimerStatus(
    RABM_TIMER_NAME_ENUM                enEntityTimerName,
    RABM_TIMER_PARA_ENUM                enTimerPara
)
{
    switch ( enTimerPara )
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
            return gRabmRAT1Switch;

        case RABM_TIMER_PARA_3_TO_2_T3:
            return gRabm3GTo2GT3Switch;

        case RABM_TIMER_PARA_ACT_REQ_T1:
            return gaRabmActReqT1Switch[enEntityTimerName];

        case RABM_TIMER_FASTDORM_FLUX_DETECT:                                            /* ������������ⶨʱ������ʱ�����Ƿ��������仯 */
            return g_ulNasRabmFDFluxDetectTimer;

        case RABM_TIMER_FASTDORM_RETRY:                                                  /* RETRY��ʱ������ʱ�����³���FD */
            return g_ulNasRabmFDRetryTimer;

        case RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT:
            return g_ulNasRabmFDWaitGmmQryRsltTimer;

        case RABM_TIMER_RESEND_EST_REQ:
            return g_ulNasRabmResendEstTimer;

        case RABM_TIMER_VOICEPREFER_DELAY:
            return g_ulNasRabmVPDelayTimer;

        case RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY:
            return g_ulNasRabmVPReQryGmmDelayTimer;

        default:
            return NAS_RABM_TIMER_STATUS_STOP;
    }
}


VOS_VOID NAS_RabmStopTimer( RABM_TIMER_NAME_ENUM Name, RABM_TIMER_PARA_ENUM Para )
{
    RABM_TIMER_NAME_ENUM                 EntityTimerName   = ( RABM_TIMER_NAME_ENUM )0;
    RABM_TIMER_PARA_ENUM                 CommonTimerPara   = ( RABM_TIMER_PARA_ENUM )0;
    HTIMER                              *pstHTimer;


    if ((RABM_TIMER_NAME_COMMON == Name)
     || (RABM_TIMER_NAME_FD_RETRY == Name)
     || (RABM_TIMER_NAME_FD_FLUX_DETECT == Name))
    {
        CommonTimerPara = Para;
    }
    else
    {
        EntityTimerName = Name;
    }

    if (NAS_RABM_TIMER_STATUS_STOP == NAS_RABM_CheckTimerStatus(EntityTimerName,Para))
    {
        return;
    }

    /*��ȡ��Ҫ�رյĶ�ʱ����HTIMERָ��:*/

    if ((RABM_TIMER_NAME_COMMON == Name)
     || (RABM_TIMER_NAME_FD_RETRY == Name)
     || (RABM_TIMER_NAME_FD_FLUX_DETECT == Name))
    {
        pstHTimer  = &gastRabmCommonTimer[CommonTimerPara];
    }
    else
    {
        pstHTimer  = &gastRabmEntityTimer[EntityTimerName];
    }

    /*�ر�ָ����ʱ��:*/
    if ( VOS_OK != NAS_StopRelTimer(WUEPS_PID_RABM, Para, pstHTimer ) )
    {
        NAS_WARNING_LOG1(WUEPS_PID_RABM, "NAS_RabmStopTimer: Stop timer failed. Para:", Para) ;
    }

    /*��λ��ʱ��������־:*/
    switch ( Para )
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
            gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_OFF;
            break;
        case RABM_TIMER_PARA_3_TO_2_T3:
            gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_OFF;
            break;
        case RABM_TIMER_PARA_ACT_REQ_T1:
            gaRabmActReqT1Switch[EntityTimerName] = RABM_ACT_REQ_T1_OFF;
            break;

        case RABM_TIMER_FASTDORM_FLUX_DETECT:                                            /* ������������ⶨʱ������ʱ�����Ƿ��������仯 */
            g_ulNasRabmFDFluxDetectTimer = NAS_RABM_TIMER_STATUS_STOP;
            break;

        case RABM_TIMER_FASTDORM_RETRY:                                                  /* RETRY��ʱ������ʱ�����³���FD */
            g_ulNasRabmFDRetryTimer = NAS_RABM_TIMER_STATUS_STOP;
            break;

        case RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT:
            g_ulNasRabmFDWaitGmmQryRsltTimer = NAS_RABM_TIMER_STATUS_STOP;
            break;

        case RABM_TIMER_RESEND_EST_REQ:
            g_ulNasRabmResendEstTimer = NAS_RABM_TIMER_STATUS_STOP;

        case RABM_TIMER_VOICEPREFER_DELAY:
            g_ulNasRabmVPDelayTimer = NAS_RABM_TIMER_STATUS_STOP;
            break;

        case RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY:
            g_ulNasRabmVPReQryGmmDelayTimer = NAS_RABM_TIMER_STATUS_STOP;
            break;

        default:
            break;
    }
    return;
}
VOS_UINT32  NAS_RabmQueryTransmodeNoState( VOS_VOID )
{
    VOS_UINT8       ucLoop;

    /*��������NSAPI:*/
    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )
    {
        if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )   /*����RABM_NSAPI_OK_TRANSMODE_NO״̬*/
        {
            return RABM_YES;
        }
    }
    return RABM_NO;
}


VOS_VOID  NAS_RabmDecodeNPdu( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG *pRAUpdateIndMsg,
                                          RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   *pstNPdu )
{
    VOS_UINT8       ucLoop,ucLeft,ucRight,ucNumber,ucNsapi,ucNpduNum;

    /*��ʼ��pstNPduָ��Ľṹ��:*/
    for ( ucLoop = 0; ucLoop <= RABM_MAX_NSAPI_NUMBER; ucLoop++ )
    {
        pstNPdu->aucNPDUNumList[ucLoop][0] = 0;
    }

    /*���N-PDU�ĸ���:*/
    ucNumber = ( VOS_UINT8 )( ( ( VOS_UINT16 )pRAUpdateIndMsg->aucRecvNPDUNumListIE[1] * ( VOS_UINT16 )8 ) / ( VOS_UINT16 )12 );

    /*����N-PDU:*/
    for ( ucLoop = 1; ucLoop <= ucNumber; ucLoop++ )
    {
        if ( 1 == (ucLoop % 2) )
        {
            /*�õ�N-PDU value�������е�����(���Ϊ����):*/
            ucLeft  = ( VOS_UINT8 )( (( ( ucLoop - 1 ) * 12 ) / 8) + RABM_N_PDU_OFFSET );
            ucRight = ucLeft + 1;
            if (ucRight >= RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN)
            {
                continue;
            }

            /*��ȡNSAPI��:*/
            ucNsapi = ( pRAUpdateIndMsg->aucRecvNPDUNumListIE[ucLeft] >> 4 ) & 0x0f;

            /*��ȡNPDU Number:*/
            ucNpduNum =( ( pRAUpdateIndMsg->aucRecvNPDUNumListIE[ucLeft]  << 4 ) & 0xf0 )
                        | ( ( pRAUpdateIndMsg->aucRecvNPDUNumListIE[ucRight] >> 4 ) & 0x0f );

            if ( RABM_2G_NULL == gastRabm2GEntity[ucNsapi - RABM_2G_NSAPI_OFFSET].State )
            {
                /*��ӡ������Ϣ---��NSAPIδ����:*/
                RABM_LOG1_WARNING( "NAS_RabmDecodeNPdu:WARNING:This NSAPI hasn't been activated but also receive a N-PDU number!: NSAPI:", ucNsapi );
            }

            /*��дpstNPdu��ָ��Ľṹ��:*/
            pstNPdu->aucNPDUNumList[ucNsapi][0] = 1;
            pstNPdu->aucNPDUNumList[ucNsapi][1] = ucNpduNum;
        }
        else
        {
            /*�õ�N-PDU value�������е�����(���Ϊż��):*/
            ucLeft  = ( VOS_UINT8 )( ((( ucLoop * 12 ) / 8) - 2) + RABM_N_PDU_OFFSET );
            ucRight = ucLeft + 1;
            if (ucRight >= RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN)
            {
                continue;
            }

            /*��ȡNSAPI��:*/
            ucNsapi = pRAUpdateIndMsg->aucRecvNPDUNumListIE[ucLeft] & 0x0f;

            /*��ȡNPDU Number:*/
            ucNpduNum = pRAUpdateIndMsg->aucRecvNPDUNumListIE[ucRight];

            if ( RABM_2G_NULL == gastRabm2GEntity[ucNsapi - RABM_2G_NSAPI_OFFSET].State )
            {
                /*��ӡ������Ϣ---��NSAPIδ����:*/
                RABM_LOG1_WARNING( "NAS_RabmDecodeNPdu:WARNING:This NSAPI hasn't been activated but also receive a N-PDU number!: NSAPI:", ucNsapi );
            }

            /*��дpstNPdu��ָ��Ľṹ��:*/
            pstNPdu->aucNPDUNumList[ucNsapi][0] = 1;
            pstNPdu->aucNPDUNumList[ucNsapi][1] = ucNpduNum;
        }
    }
}
VOS_VOID    NAS_RabmEncodeNPdu( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG *PRAUpdateRspMsg,
                                            RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   *pstNPdu )
{
    VOS_UINT8       ucLoop,ucNumber,ucLeft,ucRight;

    /*��дN-PDU������IEI:*/
    PRAUpdateRspMsg->aucRecvNPDUNumListIE[0] = 0x26;

    /*������NSAPI��Ӧ��N-PDU number:*/
    for ( ucNumber = 0, (ucLoop = 5); ucLoop <= RABM_MAX_NSAPI_NUMBER; ucLoop++ )
    {
        if( 1 == pstNPdu->aucNPDUNumList[ucLoop][0] )
        {
            ucNumber++;

            if ( 1 == (ucNumber % 2) )      /*��������N-PDU Number*/
            {
                /*�õ�N-PDU value�������е�����(���Ϊ����):*/
                ucLeft  = ( VOS_UINT8 )( (( ( ucNumber - 1 ) * 12 ) / 8) + RABM_N_PDU_OFFSET );
                ucRight = ucLeft + 1;

                /*����NSAPI:*/
                PRAUpdateRspMsg->aucRecvNPDUNumListIE[ucLeft]  = ( ucLoop << 4 ) &0xf0;

                /*����N-PDU�Ÿ�4λ:*/
                PRAUpdateRspMsg->aucRecvNPDUNumListIE[ucLeft] |= ( pstNPdu->aucNPDUNumList[ucLoop][1] >> 4 ) & 0x0f;
                /*����N-PDU�ŵ�4λ:*/
                PRAUpdateRspMsg->aucRecvNPDUNumListIE[ucRight] = ( pstNPdu->aucNPDUNumList[ucLoop][1] << 4 ) & 0xf0;
            }
            else                          /*��ż����N-PDU Number*/
            {
                /*�õ�N-PDU value�������е�����(���Ϊż��):*/
                ucLeft  = ( VOS_UINT8 )( ((( ucNumber * 12 ) / 8) - 2) + RABM_N_PDU_OFFSET );
                ucRight = ucLeft + 1;

                /*����NSAPI:*/
                PRAUpdateRspMsg->aucRecvNPDUNumListIE[ucLeft] |= ucLoop;

                /*����N-PDU��:*/
                PRAUpdateRspMsg->aucRecvNPDUNumListIE[ucRight] = pstNPdu->aucNPDUNumList[ucLoop][1];
            }
        }
        else
        {
            if ( 0 != pstNPdu->aucNPDUNumList[ucLoop][0] )
            {
                /*��ӡ������Ϣ---NSAPI�Ƿ񼤻�ı�־λ����:*/
                RABM_LOG1_WARNING( "NAS_RabmEncodeNPdu:WARNING:This NSAPI's flag(indicate the NSAPI has received N-PDU Number or not)is ERROR!: NSAPI:", ucLoop );
            }
        }
    }

    /*��дN-PDU������Length�ֶ�:*/
    PRAUpdateRspMsg->aucRecvNPDUNumListIE[1] =( VOS_UINT8 )( ( (ucNumber * 12) + 4 ) / 8 );

}
VOS_UINT32    NAS_RabmQueryRAUState( VOS_UINT8 ucNsapiIndex )
{
    VOS_UINT8 ucLoop;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )
    {
        if ( ucLoop == ucNsapiIndex )
        {
            continue;
        }

        if ( RABM_ROUT_AREA_UPDATE == gastRabm2GEntity[ucLoop].State )
        {
            return RABM_YES;
        }
    }

    return RABM_NO;
}



VOS_UINT32    NAS_RabmQueryNoOrReadyState( VOS_UINT8 ucNsapiIndex )
{
    VOS_UINT8 ucLoop;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )
    {
        if ( ucLoop == ucNsapiIndex )
        {
            continue;
        }

        if ( ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
             || ( RABM_DATA_TRANS_READY == gastRabm2GEntity[ucLoop].State ) )
        {
            return RABM_YES;
        }
    }

    return RABM_NO;
}


VOS_VOID    NAS_RabmDeactive3GPdp(VOS_UINT8 ucNsapiIndex)
{
    RABM_APS_LOCAL_PDP_DEACT_REQ    *pMsg;
    VOS_UINT32                       ulLength;

    if ( ucNsapiIndex >= RABM_MAX_ENT_NUM )
    {
        /*��ӡ������Ϣ---��NSAPIδ����:*/
        RABM_LOG_WARNING( "NAS_RabmDeactive3GPdp:WARNING:This NSAPI is beyond range!" );
        return;
    }

    /*���QoS:*/
    g_aRabmPsEnt[ucNsapiIndex].QoS.ulQosLength = 0;
    PS_MEM_SET(g_aRabmPsEnt[ucNsapiIndex].QoS.aucQosValue,
               0x00,
               sizeof(g_aRabmPsEnt[ucNsapiIndex].QoS.aucQosValue));

    g_aRabmPsEnt[ucNsapiIndex].RabInfo.ucRbNum = 0;                /*��ʼ��RB�ĸ���Ϊ0*/
    g_aRabmPsEnt[ucNsapiIndex].ucPppFlg        = RABM_SM_IP_PROT;  /*�ϲ�Э�����ͳ�ʼ��ΪIP*/

    RABM_RelSaveData(&g_aRabmPsEnt[ucNsapiIndex].DlDataSave, RABM_DOWNLINK);       /*�ͷŴ洢����������*/
    RABM_RelSaveData(&g_aRabmPsEnt[ucNsapiIndex].UlDataSave, RABM_UPLINK);         /*�ͷŴ洢����������*/


    /*����RABM_APS_LOCAL_PDP_DEACT_REQ��Ϣ:*/
    ulLength = sizeof( RABM_APS_LOCAL_PDP_DEACT_REQ ) - VOS_MSG_HEAD_LENGTH;
    pMsg     = ( RABM_APS_LOCAL_PDP_DEACT_REQ * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmDeactive3GPdp:ERROR:Allocates a message packet for RABM_APS_LOCAL_PDP_DEACT_REQ msg FAIL!" );
        return;
    }
    /*��д��Ϣͷ:*/
    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_RABM;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pMsg->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pMsg->ulMsgType       = RABM_APS_LOCAL_PDP_DEACT_REQ_MSG;
    pMsg->ucNsapi         = ucNsapiIndex + RABM_NSAPI_OFFSET;
    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pMsg ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmDeactive3GPdp:WARNING:SEND RABM_APS_LOCAL_PDP_DEACT_REQ msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmDeactive3GPdp:NORMAL:SEND RABM_APS_LOCAL_PDP_DEACT_REQ Msg" );
    }

    return;
}
VOS_VOID  NAS_RabmSndHandoverRabRsp(VOS_UINT8  ucRabNum, RRRABM_HANDOVER_RAB_IND_STRU *pMsg)
{
    RRRABM_HANDOVER_RAB_RSP_STRU   *pSndMsg;
    VOS_UINT32                      ulLength;
    VOS_UINT8                       i;

    ulLength = sizeof(RRRABM_HANDOVER_RAB_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pSndMsg  = (RRRABM_HANDOVER_RAB_RSP_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM, ulLength);
    if ( VOS_NULL_PTR == pSndMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "NAS_RabmSndHandoverRabRsp:ERROR:Allocates a message packet for RRRABM_HANDOVER_RAB_IND_STRU msg FAIL!" );
        return;
    }

    RABM_Memset((VOS_VOID *)pSndMsg,0,sizeof(RRRABM_HANDOVER_RAB_RSP_STRU));

    /*��д��Ϣͷ:*/
    pSndMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid     = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pSndMsg->MsgHeader.ulLength        = ulLength;
    pSndMsg->MsgHeader.ulMsgName       = RRRABM_HANDOVER_RAB_RSP;

    /*��д��Ϣ��:*/
    pSndMsg->ulOpId     = pMsg->ulOpId;
    pSndMsg->ulRabCnt   = (VOS_UINT32)ucRabNum;

    for ( i = 0; i <pSndMsg->ulRabCnt; i++ )
    {
        pSndMsg->aRabInfo[i].enCnDomainId     = pMsg->aRabInfo[i].ulCnDomainId;
        pSndMsg->aRabInfo[i].ulRabId          = pMsg->aRabInfo[i].ulRabId;
        pSndMsg->aRabInfo[i].ulPppValid       = WUEPS_TRUE;
        pSndMsg->aRabInfo[i].ulDeliveryErrSdu = RABM_ERROR_SDU_DELIVERY_NO_DET;
    }

    /*������Ϣ:*/
    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pSndMsg) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        RABM_LOG_WARNING( "NAS_RabmSndHandoverRabRsp:WARNING:SEND RRRABM_HANDOVER_RAB_RSP msg FAIL!" );
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        RABM_LOG_NORMAL( "NAS_RabmSndHandoverRabRsp:NORMAL:SEND RRRABM_HANDOVER_RAB_RSP Msg" );
    }
}





VOS_VOID  NAS_RabmDealHandoverRabInd(RRRABM_HANDOVER_RAB_IND_STRU *pMsg)
{
    VOS_UINT8  ucRabNum = 0;
    VOS_UINT8  i;

    switch ( pMsg->ulRabChangeType )
    {
        case NAS_RRC_RAB_SETUP_REQUEST:
            for( i = 0; i < pMsg->ulRabCnt; i++ )
            {
                if( RABM_CN_CS == pMsg->aRabInfo[i].ulCnDomainId )
                {
                    if( ucRabNum >= RABM_CS_MAX_ENT_NUM )
                    {
                        ucRabNum = 0;
                        /*��ӡ������Ϣ---:ucRabNum����14��*/
                        RABM_LOG_WARNING( "NAS_RabmDealHandoverRabInd:WARNING: ucRabNum is bigger than 14!" );
                        break;
                    }
                    else
                    {
                        ucRabNum++;
                    }
                }
                else if ( RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId )
                {
                    if (ucRabNum >= RABM_PS_MAX_ENT_NUM)
                    {
                        /* RabNum����11�� */
                        ucRabNum = 0;

                        NAS_WARNING_LOG(WUEPS_PID_RABM,
                            "NAS_RabmDealHandoverRabInd: RabNum is bigger than 11.");
                        break;
                    }
                    else
                    {
                        ucRabNum++;
                    }
                }
                else
                {
                    /*��ӡ������Ϣ---CN��ֵ����:*/
                    RABM_LOG_WARNING( "NAS_RabmDealHandoverRabInd:WARNING:Domain is Error!" );
                    ucRabNum = 0;
                    break;
                }
            }
            /*��RR����RSP��Ϣ*/
            NAS_RabmSndHandoverRabRsp( ucRabNum, pMsg );
            break;
        case NAS_RRC_RAB_SETUP_SUCCESS:
        case NAS_RRC_RAB_SETUP_FAILURE:
        case NAS_RRC_RAB_RECONFIG:
        case NAS_RRC_RAB_RELEASE:
            /*��ӡ������Ϣ---�յ������߼���Ϣ:*/
            RABM_LOG_WARNING( "NAS_RabmDealHandoverRabInd:WARNING:Receive Illegal Msg!" );
            break;
        default:
            /*��ӡ������Ϣ---�յ�����Ϣ���ֳ���:*/
            RABM_LOG_WARNING( "NAS_RabmDealHandoverRabInd:WARNING:The name of receive Msg is Error!" );
            break;
    }

}





VOS_VOID  NAS_RabmPowerOff(VOS_VOID)
{
    VOS_UINT8                           ucLoop;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_RABM_GetCurrentSysMode())
    {
        /*2G ����Դ����:*/
        /*������ʱ���Ĺر�:*/
        if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )   /*��������rout.area.update.T1��ʱ��*/
        {
            /*�ر�rout.area.update.T1��ʱ��:*/
            NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );
        }

        if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )    /*������Rabm.sys.3To2.T3��ʱ��*/
        {
            /*�ر�Rabm.sys.3To2.T3��ʱ��:*/
            NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
        }

        /*�ر�ʵ�嶨ʱ�������ն�̬������ڴ�:*/
        for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )
        {
            /*���ն�̬�ڴ�:*/
            switch ( gastRabm2GEntity[ucLoop].State )    /*��NSAPI����Ӧ��״̬*/
            {
                case RABM_2G_NULL:
                    break;
                case RABM_NSAPI_OK_TRANSMODE_NO:
                    if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[ucLoop] )   /*������Rabm.act.req.T1��ʱ��*/
                    {
                        /*�ر�Rabm.act.req.T1��ʱ��:*/
                        NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )ucLoop, RABM_TIMER_PARA_ACT_REQ_T1 );
                    }

                    /*��״̬����ΪRABM_2G_NULL״̬:*/
                    RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_2G_NULL);

                    /*���QoS:*/
                    gastRabm2GEntity[ucLoop].stQos.ulQosLength = 0;
                    PS_MEM_SET(gastRabm2GEntity[ucLoop].stQos.aucQosValue,
                               0x00,
                               sizeof(gastRabm2GEntity[ucLoop].stQos.aucQosValue));

                    break;
                case RABM_DATA_TRANS_READY:
                case RABM_ROUT_AREA_UPDATE:
                case RABM_DATA_TRANS_STOP:
                    /*��״̬����ΪRABM_2G_NULL״̬:*/
                    RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_2G_NULL);

                    /*���QoS:*/
                    gastRabm2GEntity[ucLoop].stQos.ulQosLength = 0;
                    PS_MEM_SET(gastRabm2GEntity[ucLoop].stQos.aucQosValue,
                               0x00,
                               sizeof(gastRabm2GEntity[ucLoop].stQos.aucQosValue));

                    break;
                default:
                    /*��ӡ������Ϣ--- ��NSAPI����Ӧ��״̬����:*/
                    RABM_LOG1_ERROR( "NAS_RabmPowerOff:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    break;
            }
        }
    }
    else
    {
        /*3G ����Դ����:*/
        /*������Rabm.ReestTimer,��ر���������λ�˶�ʱ����־:*/
        if ( RABM_TRUE == g_ucReestTimerFlg )
        {
            RABM_TimerStop(0);
            NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
            g_ucReestTimerFlg = RABM_FALSE;
        }

        /*���ն�̬�ڴ�:*/
        for ( ucLoop = 0; ucLoop < RABM_3G_PS_MAX_ENT_NUM; ucLoop++ )   /*����3G��ÿ��NSAPI*/
        {
            switch ( g_aRabmPsEnt[ucLoop].ucState )    /*��NSAPI����Ӧ��״̬*/
            {
                case RABM_NULL:
                    break;
                case RABM_NSAPI_ACTIVE_PENDING:
                case RABM_ACT_PENDING_WITH_RAB:             /*������״̬�Ĵ���ʽһ��*/
                case RABM_NSAPI_ACTIVE_WITH_RAB:
                case RABM_DATA_TRANSFER_STOP:
                case RABM_NSAPI_ACTIVE_NO_RAB:
                    RABM_SetWState(ucLoop, RABM_NULL);    /*״̬��� */

                    g_aRabmPsEnt[ucLoop].RabInfo.ucRbNum = 0;                /*��ʼ��RB�ĸ���Ϊ0*/
                    g_aRabmPsEnt[ucLoop].ucPppFlg        = RABM_SM_IP_PROT;  /*�ϲ�Э�����ͳ�ʼ��ΪIP*/
                    g_aRabmPsEnt[ucLoop].QoS.ulQosLength = 0;                /*���QoS*/
                    PS_MEM_SET(g_aRabmPsEnt[ucLoop].QoS.aucQosValue,
                               0x00,
                               sizeof(g_aRabmPsEnt[ucLoop].QoS.aucQosValue));

                    RABM_RelSaveData(&g_aRabmPsEnt[ucLoop].DlDataSave, RABM_DOWNLINK);       /*�ͷŴ洢����������*/
                    RABM_RelSaveData(&g_aRabmPsEnt[ucLoop].UlDataSave, RABM_UPLINK);         /*�ͷŴ洢����������*/

                    /* ֹͣRB����������ʱ�� */
                    if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucLoop))
                    {
                        NAS_RABM_StopReestRabPendingTmr(ucLoop);
                        NAS_RABM_ClearWPsEntRabReestFlg(ucLoop);
                    }

                    break;
                default:
                    /*��ӡ������Ϣ--- ��NSAPI����Ӧ��״̬����:*/
                    RABM_LOG1_ERROR( "NAS_RabmPowerOff:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    break;
            }
        }
    }

    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmFDFluxDetectTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    }

    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmFDRetryTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY);
    }

    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmFDWaitGmmQryRsltTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON,RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);
    }

    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmResendEstTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON,RABM_TIMER_RESEND_EST_REQ);
    }

    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmVPDelayTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_DELAY);
    }
    if (NAS_RABM_TIMER_STATUS_RUNING == g_ulNasRabmVPReQryGmmDelayTimer)
    {
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY);
    }

    /*���ó�ʼ������:*/
    Rabm_Init();
    NAS_Rabm2GInit();

#if (FEATURE_ON == FEATURE_LTE)
    NAS_RABM_SetSysMode(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    return;
}
VOS_UINT8  NAS_GetRbTxMode(VOS_UINT32 ulDomain, VOS_INT8    cRbId)
{
    VOS_UINT8    ucEntId,ucLoop;

    if ( RRC_NAS_PS_DOMAIN == ulDomain )
    {
        for(ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++)
        {
            if((RABM_NULL != g_aRabmPsEnt[ucEntId].ucState)
                &&(RABM_NSAPI_ACTIVE_PENDING != g_aRabmPsEnt[ucEntId].ucState)
                &&(RABM_NSAPI_ACTIVE_NO_RAB != g_aRabmPsEnt[ucEntId].ucState))
            {
                if(cRbId == g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0])
                {
                    break;
                }
            }
        }

        if ( RABM_PS_MAX_ENT_NUM == ucEntId )
        {
            return WUE_RLC_MODE_BUTT;
        }
        else
        {
            return g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[0];
        }
    }
    else
    {
        for(ucEntId = 0; ucEntId < RABM_CS_MAX_ENT_NUM; ucEntId++)
        {
            for(ucLoop = 0; ucLoop < g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum; ucLoop++)
            {
                if(g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[ucLoop] == (VOS_UINT8)cRbId)
                {
                    return g_aRabmCsEnt[ucEntId].RabInfo.aucRbTxMode[ucLoop];
                }
            }
        }

        return WUE_RLC_MODE_BUTT;
    }

}


VOS_VOID NAS_RABM_MNTN_TracePktLostEvt(
    NAS_RABM_PKT_FLOW_DIR_ENUM_UINT8    enPtkFlowDir,
    VOS_UINT8                           ucPoint
)
{
    NAS_RABM_MNTN_PKT_LOST_STRU        *pstPktLostEvt = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPktLostEvt = (NAS_RABM_MNTN_PKT_LOST_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_RABM,
                        sizeof(NAS_RABM_MNTN_PKT_LOST_STRU));
    if (VOS_NULL_PTR == pstPktLostEvt)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_MNTN_TracePktLostEvt: Memory alloc failed.");
        return;
    }

    /* ��д��Ϣ */
    pstPktLostEvt->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPktLostEvt->ulReceiverPid   = WUEPS_PID_RABM;
    pstPktLostEvt->enMsgId         = (NAS_RABM_PKT_FLOW_DIR_UPLINK == enPtkFlowDir) ?
                                     ID_NAS_RABM_MNTN_EVT_UL_PKT_LOST : ID_NAS_RABM_MNTN_EVT_DL_PKT_LOST;
    pstPktLostEvt->ucPoint         = ucPoint;

    DIAG_TraceReport(pstPktLostEvt);

    PS_FREE_MSG(WUEPS_PID_RABM, pstPktLostEvt);

    return;
}


VOS_VOID RABM_UpdateCallBack(VOS_UINT8 ucEntId)
{
    VOS_UINT8                           ucState;
    VOS_UINT8                           ucChgMask;
    VOS_UINT32                          ulLoop;
    RABM_CUR_NET_ENUM                   enRabmCurrNet;

    /*���g_astRabMap��ʵ���Ƿ��Ѵ���*/
    if (PS_TRUE !=  g_astRabMap[ucEntId + RABM_NSAPI_OFFSET].enucExistInd )
    {
        RABM_LOG1_WARNING( "RABM, RABM_UpdateCallBack, WARNING, RAB MAP Not Exist, RabId <1>", ucEntId + RABM_NSAPI_OFFSET);
        return;
    }

    switch (NAS_RABM_GetCurrentSysMode())
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            enRabmCurrNet = RABM_2G_ENUM;
            ucState = NAS_RABM_GetGPsEntState(ucEntId);
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_LTE:
            enRabmCurrNet = RABM_3G_ENUM;
            ucState = NAS_RABM_GetWPsEntState(ucEntId);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "RABM_UpdateCallBack: Invalid system mode." );
            return;
    }

    /*������Ӧ���лص�*/
    for (ulLoop = 0; ulLoop < (sizeof(g_astRabAsUlDataCallBack)/sizeof(RAB_AS_UL_DATA_CALLBACK_STRU)); ulLoop++)
    {
        if ( (g_astRabAsUlDataCallBack[ulLoop].ucMode == enRabmCurrNet)
            && (g_astRabAsUlDataCallBack[ulLoop].ucState == ucState) )
        {
            /* ������ӦRAB_MAPʵ������лص� */
            ucChgMask = 0;
            ucChgMask |= RAB_MAP_CHG_MASK_UL_CALLBACK;
            RABM_ChgRabMap( ucEntId + RABM_NSAPI_OFFSET,
                            ucChgMask,
                            0,
                            g_astRabAsUlDataCallBack[ulLoop].pAsUlDataCallBack,
                            VOS_NULL_PTR );
            break;
        }
    }

    /*������Ӧ���лص�(���лص���������״̬��ת�ƣ�����״̬Ǩ��IDLE̬�����轫���лص�ָ����Ϊ��ָ��)*/
    if (RABM_2G_ENUM == enRabmCurrNet)
    {
        if ( RABM_2G_NULL == gastRabm2GEntity[ucEntId].State )
        {
            /*����Ӧʵ������лص��ÿ�*/
            ucChgMask = 0;
            ucChgMask |= RAB_MAP_CHG_MASK_DL_CALLBACK;
            RABM_ChgRabMap( ucEntId + RABM_2G_NSAPI_OFFSET,
                            ucChgMask,
                            0,
                            VOS_NULL_PTR,
                            VOS_NULL_PTR );
        }
    }
    else
    {
        if ( RABM_NULL == g_aRabmPsEnt[ucEntId].ucState )
        {
            /*����Ӧʵ������лص��ÿ�*/
            ucChgMask = 0;
            ucChgMask |= RAB_MAP_CHG_MASK_DL_CALLBACK;
            RABM_ChgRabMap( ucEntId + RABM_NSAPI_OFFSET,
                            ucChgMask,
                            0,
                            VOS_NULL_PTR,
                            VOS_NULL_PTR );
        }
    }

    RABM_LOG1_NORMAL( "RABM, RABM_UpdateCallBack, NORMAL, Update RabId <1> CallBack", ucEntId + RABM_NSAPI_OFFSET );

    return;
}



VOS_VOID RABM_SetGState(RABM_NSAPI_ENUM  EntId, RABM_2G_STATE_ENUM  DestState)
{
    VOS_UINT8   ucChgMask;

    /*���EntId�ĺϷ���*/
    if (RABM_NSAPI_BUTT <= EntId)
    {
        RABM_LOG1_WARNING( "RABM_SetGState:WARNING:EntId is beyond range!",
                           (VOS_INT32)EntId );
        return;
    }

    /*���DestState�ĺϷ���*/
    if (RABM_STATE_BUTT <= DestState )
    {
        RABM_LOG2_WARNING( "RABM_SetGState:WARNING:DestState is beyond range!",
                           (VOS_INT32)EntId,
                           (VOS_INT32)DestState );
        return;
    }

    /*ִ��״̬Ǩ�Ʋ���*/
    gastRabm2GEntity[EntId].State = DestState;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_RABM_GetCurrentSysMode())
    {
        if (RABM_2G_NULL != DestState)
        {
            /*����RAB_MAP���е�ucAsId*/
            ucChgMask = 0;
            ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
            RABM_ChgRabMap(EntId + RABM_NSAPI_OFFSET,
                           ucChgMask,
                           EntId + RABM_NSAPI_OFFSET,
                           VOS_NULL_PTR,
                           VOS_NULL_PTR);
        }

        /*����RAB_MAP���е������лص�����*/
        RABM_UpdateCallBack(EntId);
    }

    return;
}
VOS_VOID RABM_SetWState(VOS_UINT8    ucEntId, VOS_UINT8   ucDestState)
{
    /*���EntId�ĺϷ���*/
    if (RABM_PS_MAX_ENT_NUM <= ucEntId)
    {
        RABM_LOG1_WARNING( "RABM_SetWState:WARNING:ucEntId is beyond range!",
                           (VOS_INT32)ucEntId );
        return;
    }

    /*���DestState�ĺϷ���*/
    if (RABM_TC_STATE_WITH_RAB < ucDestState)
    {
        RABM_LOG2_WARNING( "RABM_SetWState:WARNING:ucDestState is beyond range!",
                           (VOS_INT32)ucEntId,
                           (VOS_INT32)ucDestState );
        return;
    }

    /*ִ��״̬Ǩ�Ʋ���*/
    g_aRabmPsEnt[ucEntId].ucState = ucDestState;

    if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
      || (NAS_MML_NET_RAT_TYPE_LTE == NAS_RABM_GetCurrentSysMode()) )
    {
        RABM_UpdateCallBack(ucEntId);
    }

    return;
}
VOS_VOID RABM_TraceRabMapInfo(VOS_UINT8 ucRabId)
{
    RABM_TRACE_RAB_MAP_INFO_STRU    stTraceRabMapInfoMsg;


    /*====================*/    /* ������� */
    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG1(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_TraceRabMapInfo, WARNING, Invalid RabId, RabId <1>",
            ucRabId);
        return;
    }

    PS_MEM_SET(&stTraceRabMapInfoMsg, 0, sizeof(RABM_TRACE_RAB_MAP_INFO_STRU));

    stTraceRabMapInfoMsg.ulSenderCpuId      = VOS_LOCAL_CPUID;
    stTraceRabMapInfoMsg.ulSenderPid        = WUEPS_PID_RABM;
    stTraceRabMapInfoMsg.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    stTraceRabMapInfoMsg.ulReceiverPid      = WUEPS_PID_RABM;
    stTraceRabMapInfoMsg.ulLength           = sizeof(RABM_TRACE_RAB_MAP_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    stTraceRabMapInfoMsg.ulMsgName          = RABM_TRACE_RAB_MAP_INFO_MSG;
    stTraceRabMapInfoMsg.enucExistInd       = g_astRabMap[ucRabId].enucExistInd;
    stTraceRabMapInfoMsg.ucRabId            = g_astRabMap[ucRabId].ucRabId;
    stTraceRabMapInfoMsg.ucAsId             = g_astRabMap[ucRabId].ucAsId;

    if (VOS_NULL_PTR == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        stTraceRabMapInfoMsg.enUlCbName = RAB_UL_CB_NAME_NULL;
    }
    else if (RABM_SndRABMUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        stTraceRabMapInfoMsg.enUlCbName = RAB_UL_CB_NAME_SND_RABM;
    }
    else if (RABM_SndPdcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        stTraceRabMapInfoMsg.enUlCbName = RAB_UL_CB_NAME_SND_PDCP;
    }
    else if (RABM_SndSndcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        stTraceRabMapInfoMsg.enUlCbName = RAB_UL_CB_NAME_SND_SNDCP;
    }
    else
    {
        stTraceRabMapInfoMsg.enUlCbName = RAB_UL_CB_NAME_BUTT;
    }

    if (VOS_NULL_PTR == g_astRabMap[ucRabId].pDlDataCallBack)
    {
        stTraceRabMapInfoMsg.enDlCbName = RAB_DL_CB_NAME_NULL;
    }
    else if (RABM_SndAppDlDataCallBack == g_astRabMap[ucRabId].pDlDataCallBack)
    {
        stTraceRabMapInfoMsg.enDlCbName = RAB_DL_CB_NAME_DEFAULT;
    }
    else
    {
        stTraceRabMapInfoMsg.enDlCbName = RAB_DL_CB_NAME_APP_REG;
    }

    DIAG_TraceReport(&stTraceRabMapInfoMsg);
} /* RABM_TraceRabMapInfo */



VOS_VOID RABM_CreateRabMap(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucLinkdRabId,
    VOS_UINT8                           ucAsId,
    RAB_UL_DATA_CALLBACK                pRabUlDataCallBack,
    RAB_DL_DATA_CALLBACK                pRabDlDataCallBack
)
{
    /*====================*/    /* ������� */
    /* RabIdֵ����ΧΪ:[5,15] */
    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG4(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_CreateRabMap, WARNING, Invalid RabId, RabId <1>, AsId <2>, UlCallBack <3 >, DLCallBack <4>",
            ucRabId, ucAsId, (VOS_INT32)pRabUlDataCallBack, (VOS_INT32)pRabDlDataCallBack);
        return;
    }

    if ( !RAB_MAP_ASID_IS_VALID(ucAsId) )
    {
        PS_NAS_LOG4(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_CreateRabMap, WARNING, Invalid ucAsId, RabId <1>, AsId <2>, UlCallBack <3 >, DLCallBack <4>",
            ucRabId, ucAsId, (VOS_INT32)pRabUlDataCallBack, (VOS_INT32)pRabDlDataCallBack);
        return;
    }

    /* �ص�����֧��ע��պ���������� */


    /* ���ӳ��ʵ���Ѿ����ڣ������ */
    if (PS_TRUE == g_astRabMap[ucRabId].enucExistInd)
    {
        PS_NAS_LOG4(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_CreateRabMap, WARNING, This RAB MAP Is Already Exist, RabId <1>, AsId <2>, UlCallBack <3 >, DLCallBack <4>",
            ucRabId, ucAsId, (VOS_INT32)pRabUlDataCallBack, (VOS_INT32)pRabDlDataCallBack);
        return;
    }


    /*====================*/    /* ����RABӳ��ʵ�� */
    g_astRabMap[ucRabId].enucExistInd       = PS_TRUE;
    g_astRabMap[ucRabId].ucRabId            = ucRabId;
    g_astRabMap[ucRabId].ucLinkdRabId       = ucLinkdRabId;
    g_astRabMap[ucRabId].ucAsId             = ucAsId;
    g_astRabMap[ucRabId].pUlDataCallBack    = pRabUlDataCallBack;

    /*PDP����ɹ�ʱ�������ڿ���������״̬�������R�ӿ���������*/
    if(RABM_SndPdcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
    {

        R_ITF_SetFlowLev(VOS_RATMODE_WCDMA);

    }
    else if(RABM_SndSndcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        R_ITF_SetFlowLev(VOS_RATMODE_GSM);
    }
    else
    {
        ;
    }

    g_astRabMap[ucRabId].pDlDataCallBack    = pRabDlDataCallBack;

    /* ����RB��ӳ��ʵ��Ŀ������� */
    g_aucRb2Rab[ucAsId]                     = ucRabId;

    PS_NAS_LOG4(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_NORMAL,
        "RABM, RABM_CreateRabMap, NORMAL, CreatRabMap Success, RabId <1>, AsId <2>, UlCallBack <3 >, DLCallBack <4>",
        ucRabId, ucAsId, (VOS_INT32)pRabUlDataCallBack, (VOS_INT32)pRabDlDataCallBack);

    RABM_TraceRabMapInfo(ucRabId);

    return;

} /* RABM_CreateRabMap */



VOS_VOID RABM_DelRabMap(VOS_UINT8 ucRabId)
{
    VOS_UINT8   ucAsId;

    /*====================*/    /* ������� */
    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG1(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_DelRabMap, WARNING, Invalid RabId, RabId <1>",
            ucRabId);
        return;
    }

    /* ���ӳ��ʵ���Ѿ������ڣ������ */
    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        PS_NAS_LOG1(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_DelRabMap, WARNING, This RAB MAP Is Not Exist, RabId <1>",
            ucRabId);
        return;
    }


    /*====================*/    /*  ɾ����RABӳ��ʵ�� */
    ucAsId  = g_astRabMap[ucRabId].ucAsId;  /* ��ȡAS_ID */

    g_astRabMap[ucRabId].enucExistInd       = PS_FALSE;
    g_astRabMap[ucRabId].ucRabId            = RAB_MAP_INVALID_RAB_ID;
    g_astRabMap[ucRabId].ucLinkdRabId       = RAB_MAP_INVALID_RAB_ID;
    g_astRabMap[ucRabId].ucAsId             = RAB_MAP_INVALID_AS_ID;
    g_astRabMap[ucRabId].pUlDataCallBack    = VOS_NULL_PTR;
    g_astRabMap[ucRabId].pDlDataCallBack    = VOS_NULL_PTR;

    if ( RAB_MAP_ASID_IS_VALID(ucAsId) )
    {
        /* ���RB��ӳ��ʵ��Ŀ������� */
        g_aucRb2Rab[ucAsId]                 = RAB_MAP_INVALID_RAB_ID;
    }
    else
    {
        PS_NAS_LOG2(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_DelRabMap, WARNING, Invalid RbId, RabId <1>, AsId <2>",
            ucRabId, ucAsId);
    }

    PS_NAS_LOG2(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_NORMAL,
        "RABM, RABM_DelRabMap, NORMAL, DelRabMap Success, RabId <1>, AsId <2>",
        ucRabId, ucAsId);

    RABM_TraceRabMapInfo(ucRabId);

    return;

} /* RABM_DelRabMap */



VOS_VOID RABM_ChgRabMap
(
    VOS_UINT8       ucRabId,
    VOS_UINT8       ucChgMask,
    VOS_UINT8       ucAsId,
    RAB_UL_DATA_CALLBACK pRabUlDataCallBack,
    RAB_DL_DATA_CALLBACK pRabDlDataCallBack
)
{
    VOS_UINT8   ucOldAsId;

    /*====================*/    /* ������� */
    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_ChgRabMap, WARNING, Invalid RabId, RabId <1>, ucChgMask <2> AsId <3>",
            ucRabId, ucChgMask, ucAsId);
        return;
    }

    /* RABӳ��ʵ����������ڣ��쳣 */
    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_ChgRabMap, WARNING, RAB MAP Not Exist, RabId <1>, ucChgMask <2> AsId <3>",
            ucRabId, ucChgMask, ucAsId);
        return;
    }

    /*====================*/    /* ���������޸�RABӳ��ʵ���Ԫ�� */
    if ( 0 != (RAB_MAP_CHG_MASK_AS_ID & ucChgMask) )
    {
        /* ���ԭ��RB��ӳ��ʵ��Ŀ������� */
        ucOldAsId   = g_astRabMap[ucRabId].ucAsId;

        if ( !RAB_MAP_ASID_IS_VALID(ucAsId) )
        {
            PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "RABM, RABM_ChgRabMap, WARNING, Invalid RbId, RabId <1>, ucChgMask <2> AsId <3>",
                ucRabId, ucChgMask, ucAsId);
            return;
        }

        g_astRabMap[ucRabId].ucAsId     = ucAsId;

        /* ����RB��ӳ��ʵ��Ŀ������� */
        g_aucRb2Rab[ucAsId] = ucRabId;

        /*���ucOldAsId�ĺϷ���(֮���Բ���RAB_MAP_ASID_IS_VALID���жϣ�����Ϊ��W/G��ϵͳ������,Wģʽ�µ�ucOldAsId���ܴ���
           G�µ�[5,15]�ĺϷ���Χ)����ֻ�ж�ucOldAsId��W��Gģʽ�µ�����Ϸ���ȡֵ��Χ[5,32]*/
        if ( (PS_WUE_MIN_T_RB_ID <= ucOldAsId) && (PS_WUE_MAX_RB_ID >= ucOldAsId) )
        {
            if ( (ucOldAsId != ucAsId) && (g_aucRb2Rab[ucOldAsId] == g_aucRb2Rab[ucAsId]) )
            {
                g_aucRb2Rab[ucOldAsId] = RAB_MAP_INVALID_RAB_ID;
            }
        }
    }

    if ( 0 != (RAB_MAP_CHG_MASK_UL_CALLBACK & ucChgMask) )
    {
        g_astRabMap[ucRabId].pUlDataCallBack    = pRabUlDataCallBack;

        /*˫ģ�л�ʱ������R�ӿ���������*/
        if(RABM_SndPdcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
        {

            R_ITF_SetFlowLev(VOS_RATMODE_WCDMA);

        }
        else if(RABM_SndSndcpUlDataCallBack == g_astRabMap[ucRabId].pUlDataCallBack)
        {
           R_ITF_SetFlowLev(VOS_RATMODE_GSM);

        }
        else
        {
            ;
        }
    }

    if ( 0 != (RAB_MAP_CHG_MASK_DL_CALLBACK & ucChgMask) )
    {
        g_astRabMap[ucRabId].pDlDataCallBack    = pRabDlDataCallBack;
    }

    PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_NORMAL,
        "RABM, RABM_ChgRabMap, NORMAL, Change RabMap Success, RabId <1>, ucChgMask <2> AsId <3>",
        ucRabId, ucChgMask, ucAsId);

    RABM_TraceRabMapInfo(ucRabId);

    return;

} /* RABM_ChgRabMap */



VOS_VOID RABM_SendUlData(VOS_UINT8 ucRabId, TTF_MEM_ST *pstData)
{
    VOS_UINT8   ucAsId;
    VOS_UINT32  ulRtn;

    /*====================*/    /* ������� */
    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG2(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendUlData, WARNING, Invalid RabId, RabId <1>, pData <2>",
            ucRabId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_UPLINK, 1);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return;
    }

    /* RABӳ��ʵ����������ڣ��쳣 */
    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        PS_NAS_LOG2(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendUlData, WARNING, RAB MAP Not Exist, RabId <1>, pData <2>",
            ucRabId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_UPLINK, 2);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return;
    }

    /* ��ȡRB_ID */
    ucAsId  = g_astRabMap[ucRabId].ucAsId;

    if ( !RAB_MAP_ASID_IS_VALID(ucAsId) )
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendUlData, WARNING, Invalid RbId, RabId <1>, AsId <2>, pData <3>",
            ucRabId, ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_UPLINK, 3);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return;
    }

    /*====================*/    /* ����RAB_IDѰ��RAB_MAP����������Ӧ�Ļص� */
    if (VOS_NULL_PTR == g_astRabMap[ucRabId].pUlDataCallBack)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendUlData, WARNING, UlCallBack Is NULL, RabId <1>, ucAsId <2>, pData <3>",
            ucRabId, ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_UPLINK, 4);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return;
    }

    /* ������ַ� */
    ulRtn = g_astRabMap[ucRabId].pUlDataCallBack(ucRabId, ucAsId, pstData);
    if (PS_SUCC != ulRtn)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendUlData, WARNING, Call UlCallBack Fail, RabId <1>, ucAsId <2>, pData <3>",
            ucRabId, ucAsId, (VOS_INT32)pstData);
    }

    return;

} /* RABM_SendUlData */


VOS_UINT32 RABM_SendDlData(VOS_UINT8 ucAsId, TTF_MEM_ST *pstData)
{
    VOS_UINT8   ucRabId;
    VOS_UINT32  ulRtn;

    /*====================*/    /* ������� */
    if ( !RAB_MAP_ASID_IS_VALID(ucAsId) )
    {
        PS_NAS_LOG2(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendDlData, WARNING, Invalid RbId, AsId <1>, pData",
            ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_DOWNLINK, 1);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return PS_FAIL;
    }

    /* ���ݿ����������ȡRAB_ID��ӳ��ʵ�� */
    ucRabId = g_aucRb2Rab[ucAsId];

    if ( !RAB_MAP_RAB_IS_VALID(ucRabId) )
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendDlData, WARNING, Invalid RabId, RabId <1>, AsId <2>, pData",
            ucRabId, ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_DOWNLINK, 2);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return PS_FAIL;
    }

    /* RABӳ��ʵ����������ڣ��쳣 */
    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendDlData, WARNING, RAB MAP Is Free, RabId <1>, AsId <2>, pData",
            ucRabId, ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_DOWNLINK, 3);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return PS_FAIL;
    }


    /*====================*/    /* ����RAB_IDѰ��RAB_MAP����������Ӧ�����лص� */
    if (VOS_NULL_PTR == g_astRabMap[ucRabId].pDlDataCallBack)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendDlData, WARNING, DlCallBack Is NULL, RabId <1>, AsId <2>, pData",
            ucRabId, ucAsId, (VOS_INT32)pstData);

        NAS_RABM_MNTN_TracePktLostEvt(NAS_RABM_PKT_FLOW_DIR_DOWNLINK, 4);
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return PS_FAIL;
    }

    /* ��Ӧ�÷ַ� */
    ulRtn = g_astRabMap[ucRabId].pDlDataCallBack(ucRabId, pstData);
    if (PS_SUCC != ulRtn)
    {
        PS_NAS_LOG3(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
            "RABM, RABM_SendDlData, WARNING, Call DlCallBack Fail, RabId <1>, AsId <2>, pData",
            ucRabId, ucAsId, (VOS_INT32)pstData);
        return PS_FAIL;
    }

    /* W�¶�FD�������ݼ����������ۼ� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
    {
        NAS_RABM_INC_FD_DLDATA_CNT();

        NAS_RABM_ProcFastDormStatusInTransfer();

        NAS_RABM_AbortRelRrcProcedure();
    }

    return PS_SUCC;
} /* RABM_SendDlData */

VOS_UINT32 RABM_SndPdcpUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData)
{
    VOS_UINT16                          usDataLen;

    usDataLen       = TTF_MemGetLen(WUEPS_PID_RABM, pstData);

    NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(ucRbId, pstData, usDataLen * 8);

    NAS_RABM_INC_FD_ULDATA_CNT();

    NAS_RABM_ProcFastDormStatusInTransfer();

    NAS_RABM_AbortRelRrcProcedure();

    return PS_SUCC;
}
VOS_UINT32 RABM_SndSndcpUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucNsapi, TTF_MEM_ST *pstData)
{
    RABM_NSAPI_ENUM         NsapiIndex;
    SN_UNITDATA_REQ_MSG    *pUnitDataReqMsg;
    SN_DATA_REQ_MSG        *pDataReqMsg;
    VOS_UINT16              usLen;

    NsapiIndex  = ( RABM_NSAPI_ENUM )( ucRabId - RABM_2G_NSAPI_OFFSET );
    usLen       = TTF_MemGetLen(WUEPS_PID_RABM, pstData);

    if ( RABM_ABM_ENUM == gastRabm2GEntity[NsapiIndex].TransMode )
    {
        /* �����ȷ��ģʽ */
        pDataReqMsg = (SN_DATA_REQ_MSG *)
            PS_ALLOC_MSG( WUEPS_PID_RABM, sizeof(SN_DATA_REQ_MSG) - VOS_MSG_HEAD_LENGTH);
        if ( VOS_NULL_PTR == pDataReqMsg )
        {
            PS_NAS_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "RABM, RABM_SndSndcpUlDataCallBack, WARNING, Alloc msg fail!");
            TTF_MemFree(WUEPS_PID_RABM, pstData);
            return PS_FAIL;
        }

        pDataReqMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
        pDataReqMsg->ulSenderPid        = WUEPS_PID_RABM;
        pDataReqMsg->ulReceiverPid      = UEPS_PID_SN;
        pDataReqMsg->usMsgType          = ID_SN_DATA_REQ;
        pDataReqMsg->usPId              = ucNsapi;
        pDataReqMsg->ucMask             = 0;
        pDataReqMsg->usPduNum           = 0;
        pDataReqMsg->usPduLen           = usLen;
        pDataReqMsg->pMemPt             = pstData;

        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pDataReqMsg))
        {
            PS_NAS_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "RABM, RABM_SndSndcpUlDataCallBack, WARNING, Send msg fail!");
            TTF_MemFree(WUEPS_PID_RABM, pstData);
            return PS_FAIL;
        }
    }
    else    /* ����Ƿ�ȷ��ģʽ */
    {
        pUnitDataReqMsg = (SN_UNITDATA_REQ_MSG *)PS_ALLOC_MSG
            (WUEPS_PID_RABM, sizeof(SN_UNITDATA_REQ_MSG) - VOS_MSG_HEAD_LENGTH);
        if ( VOS_NULL_PTR == pUnitDataReqMsg )
        {
            PS_NAS_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "RABM, RABM_SndSndcpUlDataCallBack, WARNING, Alloc msg fail!");
            TTF_MemFree(WUEPS_PID_RABM, pstData);
            return PS_FAIL;
        }

        pUnitDataReqMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
        pUnitDataReqMsg->ulSenderPid        = WUEPS_PID_RABM;
        pUnitDataReqMsg->ulReceiverPid      = UEPS_PID_SN;
        pUnitDataReqMsg->usMsgType          = ID_SN_UNITDATA_REQ;
        pUnitDataReqMsg->usPId              = ucNsapi;
        pUnitDataReqMsg->usPduLen           = usLen;
        pUnitDataReqMsg->pMemPt             = pstData;


        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pUnitDataReqMsg))
        {
            PS_NAS_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "RABM, RABM_SndSndcpUlDataCallBack, WARNING, Send msg fail!");
            TTF_MemFree(WUEPS_PID_RABM, pstData);
            return PS_FAIL;
        }
    }

    return PS_SUCC;

}





VOS_UINT32 RABM_SndRABMUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData)
{
    /*�ͷ��㿽�����ݿ�*/
    TTF_MemFree(WUEPS_PID_RABM, pstData);

    return PS_SUCC;
}
VOS_UINT32 RABM_SndAppDlDataCallBack(VOS_UINT8 ucRabId, TTF_MEM_ST *pstData)
{
    VOS_UINT32                  ulDataLen;
    ST_APP_RABM_DATA            AppRabmData;

    ulDataLen = TTF_MemGetLen(WUEPS_PID_RABM, pstData);

    AppRabmData.pucData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_RABM, ulDataLen);
    if (VOS_NULL_PTR == AppRabmData.pucData)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        RABM_LOG_ERROR( "RABM_SndAppDlDataCallBack:ERROR:Allocates a dynamic mem fail!" );

        /*�ͷ��㿽�����ݿ�*/
        TTF_MemFree(WUEPS_PID_RABM, pstData);
        return PS_FAIL;
    }

    /*��TTF MEM�㿽���ṹ�п��������������ڴ�����*/
    (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM, pstData, 0, AppRabmData.pucData, (VOS_UINT16)ulDataLen);

    /*�ͷ��㿽�����ݿ�*/
    TTF_MemFree(WUEPS_PID_RABM, pstData);

    /*����APPע��Ļص�����*/
    AppRabmData.ucDomain  = TAF_DATA_PS_DOMAIN;
    AppRabmData.ucRabId   = ucRabId;
    AppRabmData.ulDataLen = ulDataLen;
    Api_AppRabmDataInd(&AppRabmData);

    /*�ͷ������ڴ��*/
    PS_MEM_FREE(WUEPS_PID_RABM, AppRabmData.pucData);
    return PS_SUCC;
}




VOS_VOID    RABM_RabMapInit(VOS_VOID)
{
    VOS_UINT8   ucLoop;

    for (ucLoop = 0; ucLoop <= PS_WUE_MAX_RB_ID; ucLoop++)
    {
        g_astRabMap[ucLoop].enucExistInd    = PS_FALSE;
        g_astRabMap[ucLoop].ucRabId         = RAB_MAP_INVALID_RAB_ID;
        g_astRabMap[ucLoop].ucLinkdRabId    = RAB_MAP_INVALID_RAB_ID;
        g_astRabMap[ucLoop].ucAsId          = RAB_MAP_INVALID_AS_ID;
        g_astRabMap[ucLoop].pUlDataCallBack = VOS_NULL_PTR;
        g_astRabMap[ucLoop].pDlDataCallBack = VOS_NULL_PTR;
    }

    for (ucLoop = 0; ucLoop <= PS_WUE_MAX_RB_ID; ucLoop++)
    {
        g_aucRb2Rab[ucLoop] = RAB_MAP_INVALID_RAB_ID;
    }

    return;
}




VOS_UINT32  RABM_IsExistBufferUplinkData(VOS_VOID)
{
    VOS_UINT8   ucEntId;

    for(ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++)
    {
        if((RABM_NULL != g_aRabmPsEnt[ucEntId].ucState) && (0 != g_aRabmPsEnt[ucEntId].UlDataSave.ucNum))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32  RABM_ResumeFirstActIndStatus(RABM_CUR_NET_ENUM enCurNetType, VOS_UINT8 ucEntId)
{
    RABMSM_ACTIVATE_IND_STRU    ActivateInd;
    RABMSM_ACTIVATE_IND_STRU    *pActivateInd;

    if ( (RABM_3G_ENUM != enCurNetType) && (RABM_2G_ENUM != enCurNetType) )
    {
        RABM_LOG_WARNING( "RABM_ResumeFirstActIndStatus:WARNING:enCurNetType is Error" );
        return VOS_ERR;
    }

    if ( ucEntId >= RABM_2G_MAX_ENT_NUM )
    {
        RABM_LOG_WARNING( "RABM_ResumeFirstActIndStatus:WARNING:ucEntId is Abnormal" );
        return VOS_ERR;
    }

    pActivateInd = &ActivateInd;
    if (VOS_OK != SM_RabmGetFirstActIndMsgInfo( (VOS_UINT8)(ucEntId + RABM_2G_NSAPI_OFFSET), pActivateInd) )
    {
        RABM_LOG_WARNING( "RABM_ResumeFirstActIndStatus:WARNING:SM_RabmGetFirstActIndMsgInfo invoke Error" );
        return VOS_ERR;
    }

    if (RABM_3G_ENUM == enCurNetType)
    {
        g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pActivateInd->Qos.ulLength;

        PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                   pActivateInd->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);


        if(RABM_SM_PPP_PROT == pActivateInd->ulPppFlag)
        {
            g_aRabmPsEnt[ucEntId].ucPppFlg = RABM_SM_PPP_PROT;
        }
        else
        {
            g_aRabmPsEnt[ucEntId].ucPppFlg = RABM_SM_IP_PROT;
        }
    }
    else
    {
        /*��ȡucPppFlg:*/
        if( RABM_SM_PPP_PROT == pActivateInd->ulPppFlag )
        {
            gastRabm2GEntity[ucEntId].ucPppFlg = RABM_SM_PPP_PROT;
        }
        else
        {
            gastRabm2GEntity[ucEntId].ucPppFlg = RABM_SM_IP_PROT;
        }
    }

    return VOS_OK;
}
VOS_UINT32 NAS_RABM_IsPsRbExist(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < RABM_PS_MAX_ENT_NUM; i++)
    {
        if (0 != g_aRabmPsEnt[i].RabInfo.ucRbNum)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_RABM_CreateRabMapEntity(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucLinkdRabId,
    VOS_UINT8                           ucAsId
)
{
    RAB_UL_DATA_CALLBACK                pRabUlDataCallBack;
    RAB_DL_DATA_CALLBACK                pRabDlDataCallBack;
    VOS_UINT8                           ucState;
    VOS_UINT32                          ulLoop;
    RABM_CUR_NET_ENUM                   enRabmCurrNet;

    pRabUlDataCallBack = VOS_NULL_PTR;

    switch (NAS_RABM_GetCurrentSysMode())
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            enRabmCurrNet = RABM_2G_ENUM;
            ucState = NAS_RABM_GetGPsEntState(ucRabId - RABM_2G_NSAPI_OFFSET);
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_LTE:
            enRabmCurrNet = RABM_3G_ENUM;
            ucState = NAS_RABM_GetWPsEntState(ucRabId - RABM_NSAPI_OFFSET);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_CreateRabMapEntity: Invalid system mode." );
            return;
    }

    /* ������Ӧ���лص� */
    for (ulLoop = 0; ulLoop < (sizeof(g_astRabAsUlDataCallBack)/sizeof(RAB_AS_UL_DATA_CALLBACK_STRU)); ulLoop++)
    {
        if ( (g_astRabAsUlDataCallBack[ulLoop].ucMode == enRabmCurrNet)
          && (g_astRabAsUlDataCallBack[ulLoop].ucState == ucState) )
        {
            /* �ҵ���ӦRAB_MAPʵ������лص� */
            pRabUlDataCallBack = g_astRabAsUlDataCallBack[ulLoop].pAsUlDataCallBack;
            break;
        }
    }

    /* δ�ҵ�ƥ������лص� */
    if (ulLoop == (sizeof(g_astRabAsUlDataCallBack)/sizeof(RAB_AS_UL_DATA_CALLBACK_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM,
            "NAS_RABM_CreateRabMapEntity: Can't find match pAsUlDataCallBack." );
        pRabUlDataCallBack = VOS_NULL_PTR;
    }

    /* ������Ӧ���лص���ͳһʹ��CDS�ṩ�����лص� */
    pRabDlDataCallBack = NAS_RABM_DL_DataInd;

    RABM_CreateRabMap(ucRabId, ucLinkdRabId, ucAsId, pRabUlDataCallBack, pRabDlDataCallBack);

}


#if ( FEATURE_ON == FEATURE_BASTET )

VOS_UINT8 RABM_GetRbId(VOS_UINT8 ucRabId)
{
    if ( ucRabId > PS_WUE_MAX_RB_ID )
    {
        return RAB_MAP_INVALID_AS_ID;
    }

    return g_astRabMap[ucRabId].ucAsId;
}
#endif
/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
