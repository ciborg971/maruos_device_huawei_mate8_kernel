
#include "SmInclude.h"
#include "NasSmComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVTAF_C


VOS_VOID NAS_SM_ProcTafPdpActiveReq(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* ΪMS���������(Crӳ���NSAPI��Ч)        */
        if ( SM_RETURN_OK == SM_PdpAddrApnComp(pstMsg) )
        {                                                                       /* PDP context����,����PDP address��APN��ͬ */
            SM_SndTafSmPdpActivateRej(ucCr, SM_TAF_CAUSE_SM_DUPLICATE, VOS_NULL_PTR);
        }
        else
        {
            NAS_SM_ProcTafPdpCnxtActReq_S00(pstMsg);
        }
    }
    else
    {                                                                           /* network���������,״̬Ϊ�ǿյĴ���       */
        switch(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
        case SM_PDP_INACTIVE:
            NAS_SM_ProcTafPdpCnxtActReq_S05(pstMsg);

            break;
        case SM_PDP_ACTIVE_PENDING:
        case SM_PDP_ACTIVE:
        case SM_PDP_MODIFY_PENDING:
        case SM_PDP_INACTIVE_PENDING:
        case SM_PDP_NW_MODIFY:
            SM_SndTafSmPdpActivateRej(ucCr,
                                      SM_TAF_CAUSE_SM_INVALID_NSAPI,
                                      VOS_NULL_PTR);

            break;
        default:
            break;
        }
    }

    return;
}

/*******************************************************************************
  Module:   SM_ProcTafPdpActiveRej
  Function: TAFSM_PDP_ACTIVATE_REJ_RSP����Ϣ�ַ�
  Input:    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID NAS_SM_ProcTafPdpActiveRej(
    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvNwReqPdpCnxtActMsg_S02:WARNING:0xff == ucCntxtIndex ");
        return;
    }

    if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬ΪSM_PDP_NW_ACTIVE                   */
        SM_TimerStop(ucCntxtIndex);                                         /* ֹͣTimer                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;   /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActRejRsp:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_INACTIVE");

        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActRejRsp:NORMAL: Destroy SM entity(index):", ucCntxtIndex);
        SM_SndReqPdpActRejMsg(pstMsg, g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi);  /* ����REJECT��Ϣ                           */
        SM_ComDelNsapiFromAddr(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex,
            ucCntxtIndex);                                                  /* ά��ADDR��APNʵ��                        */
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff; /* ��ʼ��Ti�б�                             */
        g_CrMapToNsapi[ucCr] = 0xff;                                        /* ��ʼ��Cr�б�                             */
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCnxtActRejRsp:WARNING:APP->SM: Message type not compatible with the state  !");
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpDeActiveReq(
    SMREG_PDP_DEACTIVATE_REQ_STRU      *pstMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucLinkNsapi;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
        SM_SndTafSmPdpDeActInd (
            ucCr,
            SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
            SM_FALSE);                                                          /* ����TAFSM_PDP_DEACTIVATE_IND             */
        return;
    }
    ucAddrIndex  = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if ( SM_PDP_INACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE_PENDING            */
        ;
    }
    else
    {
        if((SM_TRUE == pstMsg->bitOpTearDownInd) && (SM_TRUE == pstMsg->ucTearDownInd))
        {                                                                       /* ����Tear down indicator IE���� requested */
            SM_SndRabmSmDeactivateInd(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);             /* ֪ͨRABMȥ����Nsapi�б�:                 */
            for (i=0;i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
            {                                                                   /* Nsapi�б�                                */
                ucLinkNsapi
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];
                SM_ComClearPdpCntxt(ucLinkNsapi);                               /* �ͷ�ʵ��                                 */
                g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucState=SM_PDP_INACTIVE;  /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtDeActReq:NORMAL: SM state = SM_PDP_INACTIVE");
                if ( ucLinkNsapi != ucCntxtIndex )
                {
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucTi]
                        = 0xFF;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucCr]
                        = 0xFF;
                }
            }
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* ���Addr Apnʵ��                         */
        }
        else
        {                                                                       /* ������Tear down  ����not requested       */
            SM_ComClearPdpCntxt(ucCntxtIndex);                                  /* ���ʵ��                                 */
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);                   /* ά��Addr��Apnʵ��                        */
            SM_SndRabmSmDeactivateInd(1,&ucCntxtIndex);                         /* ֪ͨRABMȥ����Nsapi                      */
        }

        if ((SM_TRUE == pstMsg->bitOpPcpTaCause) && (SM_TRUE == pstMsg->enPcpTaCause))
        {
            NAS_SM_BeginSession();

            SM_SndPdpDeActReqMsg(pstMsg, ucCntxtIndex);                             /* ����DEACTIVATE PDP CONTEXT REQUEST       */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* Timr ��ʱ������0                         */
            SM_TimerStart(ucCntxtIndex,SM_T3390_LENGTH,SM_TIMER_TYPE_T3390);        /* ����T3390                                */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState=SM_PDP_INACTIVE_PENDING; /* ״̬�л���SM_PDP_INACTIVE_PENDING        */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SM_RcvTafPdpCnxtDeActReq: SM state = SM_PDP_INACTIVE_PENDING");
        }
        else
        {   /*�����ͷ���Դ*/
            /*ֹͣTimer;�ͷ������APN�ڴ�;ȥ����RABM;�ͷ�Qos�ڴ�;�ͷŻ�����ط���Ϣ */

            SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);

            SM_ComClearPdpCntxt(ucCntxtIndex);

            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;

            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]=0xff;
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi]=0xff;

            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                    "SM Local Release :  ==> SM_PDP_INACTIVE");

        }
    }
    return;
}
VOS_VOID NAS_SM_ProcTafPdpModifyRsp(
    SMREG_PDP_MODIFY_RSP_STRU          *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    if ( 0xff != ucCntxtIndex )
    {                                                                           /* ״̬��ΪSM_PDP_INACTIVE                  */
        if ( SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* ��ǰ��״̬ΪSM_PDP_NW_MODIFY             */
            SM_TimerStop(ucCntxtIndex);                                         /* ֹͣTimer                                */
            SM_SndPdpModAccMsg(pstMsg, ucCntxtIndex);                           /* ��network����MODIFY PDP CONTEXT ACCEP    */
            SM_SndRabmSmModifyInd(ucCntxtIndex);                                /* ֪ͨRABM�޸ĳɹ�                         */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;     /* ״̬�л���SM_PDP_ACTIVE                  */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpModifyRsp:NORMAL:SM state: SM_PDP_NW_MODIFY ==> SM_PDP_ACTIVE");

            NAS_SM_SndGmmPdpModifyInd(ucCntxtIndex + SM_NSAPI_OFFSET);

            NAS_SM_EndSession();
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpModifyRsp:WARNING:APP->SM: Message type not compatible with the state  !");
        }
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpModifyRejRsp(
    SMREG_PDP_MODIFY_REJ_RSP_STRU       *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    /* ����Cr��ȡucCntxtIndex */
    ucCr         = pstMsg->ucConnectId;
    ucCntxtIndex = g_CrMapToNsapi[ucCr];

    if (0xFF != ucCntxtIndex)
    {
        if (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            SM_TimerStop(ucCntxtIndex);

            /* ����MODIFY_PDP_CONTEXT_REJECT��Ϣ������ */
            NAS_SM_SndPdpModRejMsg(pstMsg, ucCntxtIndex);

            /* ״̬�л���SM_PDP_ACTIVE */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;

            NAS_NORMAL_LOG(WUEPS_PID_SM,
                "NAS_SM_ProcTafPdpModifyRejRsp:NORMAL:SM state: SM_PDP_NW_MODIFY ==> SM_PDP_ACTIVE");

            NAS_SM_EndSession();
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_SM,
                "NAS_SM_ProcTafPdpModifyRejRsp:WARNING:APP->SM: Message type not compatible with the state  !");
        }
    }

    return;
}
VOS_VOID NAS_SM_ProcTafPdpModifyReq(
    SMREG_PDP_MODIFY_REQ_STRU          *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_INT8                            ue_revision;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    /* �ն˿���������:�����ǰ�汾ΪPS_PTL_VER_PRE_R99���յ��ϲ��û�������PDP MODIFY����
                       ֱ�ӻظ��ܾ���Cause: TAF_SM_REJ_CAUSE_INSUFF_RESOURCE */
    ue_revision = NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS);
    if (PS_PTL_VER_PRE_R99 == ue_revision)
    {
        SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES, ucCr);
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCntxtModifyReq:WARNING:ue_revision is PS_PTL_VER_PRE_R99,modify PDP req is rejected!");
        return;
    }

    if ( 0xff != ucCntxtIndex )
    {                                                                           /* ״̬��ΪSM_PDP_INACTIVE                  */
        if ( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* ��ǰ��״̬ΪSM_PDP_ACTIVE                */
            NAS_SM_BeginSession();


            SM_SndPdpModReqMsg(pstMsg, ucCntxtIndex);                           /* ��network���� REQUEST                    */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0; /* Timr ��ʱ������0                         */
            SM_TimerStart(ucCntxtIndex,SM_T3381_LENGTH,SM_TIMER_TYPE_T3381);    /* ����T3381                                */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                = SM_PDP_MODIFY_PENDING;                                        /* ״̬�л���SM_PDP_MODIFY_PENDING          */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCntxtModifyReq:NORMAL:SM state: SM_PDP_ACTIVE ==> SM_PDP_MODIFY_PENDING");
        }
        else if (SM_PDP_MODIFY_PENDING
                 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCntxtModifyReq:WARNING:APP->SM: Message type not compatible with the state  !");
        }
        else if (SM_PDP_NW_MODIFY
                 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_MODIFY_COLLISION,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        }
        else
        {
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        }
    }
    else
    {
        SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE, ucCr);                                                     /* �ؾܾ���Ϣ                               */
    }

    return;
}
VOS_VOID NAS_SM_ProcTafPdpActiveSecReq(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucLinkCntxtIndex;
    VOS_INT8                            ue_revision;

    ucCr         = pstMsg->ucConnectId;                                         /* ȡCR��ʵ��ֵ                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* ����Cr��ȡucCntxtIndex                   */

    /* �ն˿���������:�����ǰ�汾ΪPS_PTL_VER_PRE_R99���յ��ϲ��û�������PDP���μ�������,
                       ֱ�ӻظ��ܾ���Cause: TAF_SM_REJ_CAUSE_INSUFF_RESOURCE */
    ue_revision = NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS);
    if (PS_PTL_VER_PRE_R99 == ue_revision)
    {
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCnxtActSecReq:WARNING:ue_revision is PS_PTL_VER_PRE_R99,active secondary PDP req is rejected!");
        return;
    }

    ucLinkCntxtIndex = (pstMsg->ucPrimNsapi - SM_NSAPI_OFFSET);                 /* ���ucLinkCntxtIndex                     */
    if ( 0xff != ucCntxtIndex )
    {                                                                           /* ״̬��ΪSM_PDP_INACTIVE                  */
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_INVALID_NSAPI);
    }
    else
    {
        switch ( g_SmEntity.aPdpCntxtList[ucLinkCntxtIndex].ucState )
        {                                                                       /* ucLinkCntxtIndex״̬Ϊ�Ѿ�����           */
            case SM_PDP_ACTIVE:
            case SM_PDP_MODIFY_PENDING:
            case SM_PDP_NW_MODIFY:
            case SM_PDP_ACTIVE_PENDING:
                NAS_SM_ProcTafPdpActiveSecReq_S00(pstMsg);
                break;
            default:
                SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT);
                break;
        }
    }
    return;
}
VOS_VOID NAS_SM_ProcTafPdpActiveSecReq_S00(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pstMsg
)
{
    VOS_UINT16                          i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucNsapiCnt;
    VOS_UINT8                           ucCr;

    ucTi = 0;
    ucCr = pstMsg->ucConnectId;                                                 /* ȡCR��ʵ��ֵ                             */
    ucTiFlg = SM_FALSE;
    ucCntxtIndex = SM_MAX_NSAPI_NUM;
    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
        {
            ucCntxtIndex = (VOS_UINT8)i;                                        /* ��ȡʵ�������                           */
            break;
        }
    }

    for ( i = 0x80; i <= (SM_MAX_TI_NUM - 1); i++ )
    {
        if ( 0xff == g_TiMapToNsapi[i] )
        {                                                                       /* ����û��ʹ�õ�TI                         */
            ucTi = (VOS_UINT8)i;                                                  /* ��ȡTI                                   */
            ucTiFlg = SM_TRUE;
            break;
        }
    }

    if ( (SM_MAX_NSAPI_NUM != ucCntxtIndex)&&(SM_FALSE != ucTiFlg) )
    {                                                                           /* ���� ʵ��,PDP Addr,Ti�ɹ�                */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActSecReq_S00:NORMAL: Create SM entity(index):", ucCntxtIndex);

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_MS_ORG;          /* �趨ʵ��ķ����־ MS����                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* �洢CR                                   */
        g_CrMapToNsapi[ucCr] = ucCntxtIndex;                                    /* ά��Cr��NSAPI��ӳ��                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* �洢TI                                   */
        g_TiMapToNsapi[ucTi] = ucCntxtIndex;                                    /* ά��Ti��NSAPI��ӳ��                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stRequestedQos.ulQosLen;                                  /* �趨Qos�����ݳ���                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stRequestedQos.aucQos,
                   pstMsg->stRequestedQos.ulQosLen);                            /* �洢Qos����                              */
        ucAddrIndex = g_SmEntity.aPdpCntxtList
            [pstMsg->ucPrimNsapi - SM_NSAPI_OFFSET].ucAddrIndex;                /* ���ucAddrIndex                          */
        ucNsapiCnt = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[ucNsapiCnt]
            = ucCntxtIndex;                                                     /* �洢Nsapi                                */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt++;                  /* ά��Nsapi                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;
        NAS_SM_BeginSession();
        SM_SndPdpActSecReqMsg(pstMsg, ucCntxtIndex);                            /* ��network����SECONDARY ACTIVE REQUEST    */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* Timr ��ʱ������0                         */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* ����T3381                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
            = SM_PDP_ACTIVE_PENDING;                                            /* ״̬�л���SM_PDP_ACTIVE_PENDING          */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActSecReq_S00:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_ACTIVE_PENDING");
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* ֪ͨRABM�Ѿ�����Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);  /* �ؾܾ���Ϣ                               */
    }

    return;
}
VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S00(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT16                          i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucCr;

    ucTi = 0;
    ucCr = pstMsg->ucConnectId;
    ucTiFlg = SM_FALSE;
    ucCntxtIndex = SM_MAX_NSAPI_NUM;

    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
        {
            ucCntxtIndex = (VOS_UINT8)i;                                        /* ��ȡʵ�������                           */
            break;
        }
    }

    for ( i = 0x80; i <= (SM_MAX_TI_NUM - 1); i++ )
    {
        if ( 0xff == g_TiMapToNsapi[i] )
        {                                                                       /* ����û��ʹ�õ�TI                         */
            ucTi = (VOS_UINT8)i;                                                /* ��ȡTI                                   */
            ucTiFlg = SM_TRUE;
            break;
        }
    }

    ucAddrIndex = SM_ComFindNullAddrApn();                                      /* ����δʹ�õ�Addr                         */
    if (( SM_MAX_NSAPI_NUM != ucCntxtIndex )
      &&( SM_FALSE != ucTiFlg )
      &&( SM_MAX_NSAPI_NUM!= ucAddrIndex))
    {                                                                           /* ���� ʵ��,PDP Addr,Ti�ɹ�                */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActReq_S00:NORMAL:Create SM entity(index):", ucCntxtIndex);

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_MS_ORG;          /* �趨ʵ��ķ����־ MS����                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* �洢CR                                   */
        g_CrMapToNsapi[ucCr]= ucCntxtIndex;                                     /* ά��Cr��NSAPI��ӳ��                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* �洢TI                                   */
        g_TiMapToNsapi[ucTi]= ucCntxtIndex;                                     /* ά��Ti��NSAPI��ӳ��                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;       /* �趨ucAddrIndex                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stReqQos.ulQosLen;                                        /* �趨Qos�����ݳ���                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stReqQos.aucQos,
                   pstMsg->stReqQos.ulQosLen);                                  /* �洢Qos����                              */
        g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
        SM_MemCpy(
              g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
              pstMsg->stReqPdpAddr.aucPdpAddr,
              pstMsg->stReqPdpAddr.ulPdpAddrLen);                               /* �洢PDP Addr����                         */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
            = pstMsg->stReqPdpAddr.ulPdpAddrLen;                                /* �趨PDP Addr ����                        */
        if ( SM_TRUE == pstMsg->bitOpAcsPointName )
        {                                                                       /* APN����                                  */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength
                = pstMsg->stAcsPointName.ulApnLen;                              /* �趨AcsPointName���ݳ���                 */
            PS_MEM_CPY(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                       pstMsg->stAcsPointName.aucApnAddr,
                       pstMsg->stAcsPointName.ulApnLen);                        /* �洢AcsPointName����                     */
        }
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 1;                /* �趨Nsapi����                            */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] = ucCntxtIndex;    /* �洢NSAPI                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE_PENDING; /* ״̬�л���SM_PDP_ACTIVE_PENDING          */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActReq_S00:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_ACTIVE_PENDING ");

        NAS_SM_BeginSession();
        SM_SndPdpActReqMsg(pstMsg, ucCntxtIndex);                               /* ������ϢREQUEST                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* ��ʱ������0                              */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* ����T3380                                */
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* ֪ͨRABM�Ѿ�����Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActivateRej(ucCr,
                                  SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,
                                  VOS_NULL_PTR);                                /* �ؾܾ���Ϣ                               */
    }

    return;
}


VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S05(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucCr;

    ucCr = pstMsg->ucConnectId;
    ucCntxtIndex = g_CrMapToNsapi[ucCr];

    SM_TimerStop(ucCntxtIndex);                                                 /* ֹͣNetwork����PDP Active����Timer       */

    ucAddrIndex = SM_ComFindNullAddrApn();                                      /* ����δʹ�õ�Addr                         */
    if ( SM_MAX_NSAPI_NUM != ucAddrIndex )
    {                                                                           /* ���� PDP Addr�ɹ�                        */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;       /* �趨ucAddrIndex                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stReqQos.ulQosLen;                                        /* �趨Qos�����ݳ���                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stReqQos.aucQos,
                   pstMsg->stReqQos.ulQosLen);                                  /* �洢Qos����                              */
        g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 1;                /* �趨Nsapi����                            */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] = ucCntxtIndex;    /* �洢NSAPI                                */
        SM_MemCpy(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                pstMsg->stReqPdpAddr.aucPdpAddr,
                pstMsg->stReqPdpAddr.ulPdpAddrLen);                             /* �洢PDP Addr����                         */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
            = pstMsg->stReqPdpAddr.ulPdpAddrLen;                                /* �趨PDP Addr ����                        */
        if ( SM_TRUE == pstMsg->bitOpAcsPointName )
        {                                                                       /* APN����                                  */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength
                = pstMsg->stAcsPointName.ulApnLen;                              /* �趨AcsPointName���ݳ���                 */
            PS_MEM_CPY(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                       pstMsg->stAcsPointName.aucApnAddr,
                       pstMsg->stAcsPointName.ulApnLen);                        /* �洢AcsPointName����                     */
        }

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE_PENDING; /* ״̬�л���SM_PDP_ACTIVE_PENDING          */

        NAS_SM_BeginSession();

        SM_SndPdpActReqMsg(pstMsg, ucCntxtIndex);                               /* ������ϢREQUEST                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* ��ʱ������0                              */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* ����T3380                                */
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* ֪ͨRABM�Ѿ�����Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActivateRej(
            ucCr,
            SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,
            VOS_NULL_PTR);
    }

    return;
}


VOS_VOID NAS_SM_RcvTafPdpCnxtActReq(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT32                          ulIndex;
    VOS_VOID                           *pHoldMsg;

    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        /* ���ý���D_PMC_SMREG_PDP_ACT_REQ�Ĵ��� */
        NAS_SM_ProcTafPdpActiveReq(pstMsg);
    }
    else
    {
        for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
        {
            if (VOS_NULL_PTR == g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg)
            {
                /* ���뻺����Ϣ */
                pHoldMsg = SM_Malloc(sizeof(SMREG_PDP_ACTIVATE_REQ_STRU));
                if (VOS_NULL_PTR == pHoldMsg)
                {
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_RcvTafPdpCnxtActReq: ERROR: ALLOC MSG FAIL");
                    return;
                }

                /* ����������Ϣ */
                PS_MEM_CPY(pHoldMsg, (VOS_VOID *)pstMsg, sizeof(SMREG_PDP_ACTIVATE_REQ_STRU));

                g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg = pHoldMsg;
                break;
            }
        }

        if (SM_PS_NOTREGISTER == g_SmEntity.ucRegisterFlg)
        {
            /* ��GMM����ע������ */
            NAS_SM_SndGmmEstablishReq();

            /* ������ʱ�� 80s */
            SM_TimerStart(SM_REGISTER_TIMER_ID, SM_T0001_LENGTH, SM_TIMER_TYPE_T0001);

            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERING;
        }
    }
}
VOS_VOID NAS_SM_RcvTafPdpCnxtActRejRsp(
    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpActiveRej(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpCnxtActRejRsp:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpCntxtModifyReq(
    SMREG_PDP_MODIFY_REQ_STRU          *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyReq(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpCntxtModifyReq:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpCnxtDeActReq(
    SMREG_PDP_DEACTIVATE_REQ_STRU       *pstMsg
)
{
    VOS_UINT32                          ulIndex;
    VOS_VOID                           *pHoldMsg;

    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpDeActiveReq(pstMsg);
    }
    else if (SM_PS_REGISTERING == g_SmEntity.ucRegisterFlg)
    {
        for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
        {
            if (VOS_NULL_PTR == g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg)
            {
                /* ���뻺����Ϣ */
                pHoldMsg = SM_Malloc(sizeof(SMREG_PDP_DEACTIVATE_REQ_STRU));
                if (VOS_NULL_PTR == pHoldMsg)
                {
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_RcvTafPdpCnxtDeActReq: ERROR: ALLOC MSG FAIL");
                    return;
                }

                /* ����������Ϣ */
                PS_MEM_CPY(pHoldMsg, (VOS_VOID *)pstMsg, sizeof(SMREG_PDP_DEACTIVATE_REQ_STRU));

                g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg = pHoldMsg;
                break;
            }
        }
    }
    else
    {
    }
}


VOS_VOID NAS_SM_RcvTafPdpCnxtActSecReq(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpActiveSecReq(pstMsg);
    }
    else
    {
        /* GMMδע�ᣬ�ؾܾ���Ϣ */
        SM_SndTafSmPdpActSecRej(pstMsg->ucConnectId, SM_TAF_CAUSE_SM_UNKNOWN);
    }
}
VOS_VOID NAS_SM_RcvTafPdpModifyRsp(
    SMREG_PDP_MODIFY_RSP_STRU           *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyRsp(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpModifyRsp:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpModifyRejRsp(
    SMREG_PDP_MODIFY_REJ_RSP_STRU       *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyRejRsp(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafPdpModifyRejRsp:WARNING: PS not Registered !");
    }
}


VOS_UINT8 SM_PdpAddrApnComp(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucResult1;
    VOS_UINT8                           ucResult2;

    ucRet     = SM_RETURN_NG;
    ucResult1 = 0xFF;
    ucResult2 = 0xFF;
    if(( SM_FALSE == pstMsg->bitOpAcsPointName )
        ||( pstMsg->stReqPdpAddr.ulPdpAddrLen <= 2 ))
    {                                                                           /* �����ԱȽ�                               */
    }
    else
    {
        for(i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            if(0 != (g_SmPdpAddrApn.usPdpAddrFlg & (VOS_UINT16)((VOS_UINT32)0x01 << i)))
            {                                                                   /* AddrApn����                              */
                if(( g_SmPdpAddrApn.aPdpAddrlist[i].PdpApn.ulApnLength
                    == pstMsg->stAcsPointName.ulApnLen )
                    &&(g_SmPdpAddrApn.aPdpAddrlist[i].PdpAddrInfo.ulAddrLength
                    == pstMsg->stReqPdpAddr.ulPdpAddrLen ))
                {                                                               /* ���ݵĳ�����ͬ                           */
                    ucResult1 = SM_MemCmp(
                        g_SmPdpAddrApn.aPdpAddrlist[i].PdpApn.aucApnValue,
                        pstMsg->stAcsPointName.aucApnAddr,
                        pstMsg->stAcsPointName.ulApnLen);                       /* �����ڴ�ȽϺ���                         */
                    ucResult2 = SM_MemCmp(
                        g_SmPdpAddrApn.aPdpAddrlist[i].PdpAddrInfo.aucAddrValue,
                        pstMsg->stReqPdpAddr.aucPdpAddr,
                        pstMsg->stReqPdpAddr.ulPdpAddrLen);                     /* �����ڴ�ȽϺ���                         */
                    if(( 0 == ucResult1 )
                        &&( 0 == ucResult2 ))
                    {                                                           /* APN��Addr��ͬ                            */
                        ucRet = SM_RETURN_OK;                                   /* �趨����ֵOK                             */
                        break;
                    }
                }
            }
        }
    }
    return ucRet;
}
VOS_VOID NAS_SM_StopRegisterProcedure(VOS_VOID)
{
    VOS_UINT8                           i;

    /* ��鵱ǰ�Ƿ���ڻ������Ϣ */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
        {
            return;
        }
    }

    /* ��鵱ǰ�Ƿ���ڼ�������е�PDP */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {
            return;
        }
    }

    /* ����SMע��״̬��ֹͣע�ᶨʱ�� */
    if (SM_PS_REGISTERING == NAS_SM_GET_REGISTER_FLG())
    {
        NAS_SM_SET_REGISTER_FLG(SM_PS_NOTREGISTER);
        SM_TimerStop(SM_REGISTER_TIMER_ID);
    }

    return;
}
VOS_VOID NAS_SM_ClearHoldMsgByConnectId(VOS_UINT8 ucConnectId)
{
    MSG_HEADER_STRU                    *pstHoldMsg;
    VOS_UINT8                           i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
        {
            pstHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;

            if ( (ID_SMREG_PDP_ACTIVATE_REQ == pstHoldMsg->ulMsgName)
              && (ucConnectId == ((SMREG_PDP_ACTIVATE_REQ_STRU *)pstHoldMsg)->ucConnectId) )
            {
                break;
            }

            if ( (ID_SMREG_PDP_DEACTIVATE_REQ == pstHoldMsg->ulMsgName)
              && (ucConnectId == ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pstHoldMsg)->ucConnectId) )
            {
                break;
            }
        }
    }

    if (i < SM_MAX_NSAPI_NUM)
    {
        SM_ComClearPdpCntxt(i);
        SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);
        g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;
    }

    return;
}


VOS_VOID NAS_SM_RcvTafPdpAbortReq(
    SMREG_PDP_ABORT_REQ_STRU           *pstPdpAbortReq
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucAddrIndex;
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;

    /* ����ConnectId��ȡCR(PDPID) */
    ucCr            = pstPdpAbortReq->ucConnectId;

    /* ��ȡTI��Ӧ��PDP CONTEXT���� */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromCrMap(ucCr);

    /* ���PDP CONTEXT������Ч�� */
    if (0xFF == ucPdpCtxIndex)
    {
        /* ����������Ϣ */
        NAS_SM_ClearHoldMsgByConnectId(pstPdpAbortReq->ucConnectId);

        /* ˢ��SMע��״̬��ֹͣ��ʱ�� */
        NAS_SM_StopRegisterProcedure();

        NAS_SM_EndSession();

        return;
    }

    /* ��ȡ��ǰPDP CONTEXT���ݵ�ַ */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* ��ȡPDP ADDRESS���� */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    switch (pstPdpCtxInfo->ucState)
    {
        case SM_PDP_ACTIVE_PENDING:
        case SM_PDP_INACTIVE_PENDING:

            /* ��SMʵ��״̬��ΪINACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

            /* ���TI��PDP INDEX��ӳ���ϵ */
            NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

            /* ���CR��PDP INDEX��ӳ���ϵ */
            NAS_SM_ClearNsapiToCrMap(ucCr);

            /* �����Ӧ��PDPʵ����Ϣ */
            SM_ComClearPdpCntxt(ucPdpCtxIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

            /* ֪ͨGMM����PDP CONTEXT״̬ */
            NAS_SM_SndGmmPdpStatusInd();

            /* ֪ͨRABM����״̬ */
            SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

            /* ֪ͨGMM���SM���� */
            NAS_SM_SndGmmAbortReq();

            NAS_SM_SndGmmPdpDeactivatedInd();

            break;

        case SM_PDP_MODIFY_PENDING:

            /* ��SMʵ��״̬��ΪACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_ACTIVE;

            SM_TimerStop(ucPdpCtxIndex);

            break;

        case SM_PDP_ACTIVE:

             /* ��SMʵ��״̬��ΪINACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

            /* ���TI��PDP INDEX��ӳ���ϵ */
            NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

            /* ���CR��PDP INDEX��ӳ���ϵ */
            NAS_SM_ClearNsapiToCrMap(ucCr);

            /* �����Ӧ��PDPʵ����Ϣ */
            SM_ComClearPdpCntxt(ucPdpCtxIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

            /* ֪ͨGMM����PDP CONTEXT״̬ */
            NAS_SM_SndGmmPdpStatusInd();
            NAS_SM_SndGmmPdpDeactivatedInd();

            /* ֪ͨRABM����״̬ */
            SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM,
                "NAS_SM_RcvTafPdpAbortReq: Wrong state!");
            break;
    }

    NAS_SM_EndSession();

    return;
}
VOS_VOID NAS_SM_RcvTafPdpLocalDeactivateReq(
    SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU    *pstPdpLocalDeactivateReq
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucAddrIndex;

    /* ����ConnectId��ȡCR(PDPID) */
    ucCr            = pstPdpLocalDeactivateReq->ucConnectId;

    /* ��ȡTI��Ӧ��PDP CONTEXT���� */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromCrMap(ucCr);

    /* ���PDP CONTEXT������Ч�� */
    if (0xFF == ucPdpCtxIndex)
    {
        return;
    }

    /* ��ȡ��ǰPDP CONTEXT���ݵ�ַ */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* ��SMʵ��״̬��ΪINACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

    /* ��ȡPDP ADDRESS���� */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    /* ���TI��PDP INDEX��ӳ���ϵ */
    NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

    /* ���CR��PDP INDEX��ӳ���ϵ */
    NAS_SM_ClearNsapiToCrMap(ucCr);

    /* �����Ӧ��PDPʵ����Ϣ */
    SM_ComClearPdpCntxt(ucPdpCtxIndex);
    SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

    /* ֪ͨGMM����PDP CONTEXT״̬ */
    NAS_SM_SndGmmPdpStatusInd();

    /* ֪ͨRABM����״̬ */
    SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

    /* ֪ͨGMM���SM���� */
    NAS_SM_SndGmmAbortReq();

    NAS_SM_SndGmmPdpDeactivatedInd();

    NAS_SM_EndSession();
    return;
}


VOS_VOID NAS_SM_BeginSession(VOS_VOID)
{
    SM_ENTITY_STRU                     *pstSmEntity = VOS_NULL_PTR;

    pstSmEntity = NAS_SM_GetSmEntity();

    pstSmEntity->ulSessionBeginFlg = PS_TRUE;
    NAS_SM_SndGmmBeginSessionNotify(GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL);

    return;
}


VOS_VOID NAS_SM_EndSession(VOS_VOID)
{
    SM_ENTITY_STRU                     *pstSmEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSmEntity = NAS_SM_GetSmEntity();

    /* ��鵱ǰ�Ƿ����������̴��� */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if ( (VOS_NULL_PTR != pstSmEntity->aHoldMsg[i].pHoldRcvMsg)
          || (SM_PDP_ACTIVE_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_INACTIVE_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_MODIFY_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_NW_MODIFY == pstSmEntity->aPdpCntxtList[i].ucState) )
        {
            return;
        }
    }

    /* �ͷ���Դ */
    if (PS_TRUE == pstSmEntity->ulSessionBeginFlg)
    {
        pstSmEntity->ulSessionBeginFlg = PS_FALSE;
        NAS_SM_SndGmmEndSessionNotify(GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL);
    }

    return;
}




/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

