
#include "smsinclude.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasGmmInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SMC_COM_C


/*lint -save -e958 */

VOS_VOID SMC_TimerTc1mExp(
                      VOS_UINT8       ucTimerId                                     /* TIMER ID                                 */
                      )
{
    VOS_BOOL                            bRetryFlag;
    VOS_UINT32                          ulRet;


    /* ֹͣ��ǰ�Ķ�ʱ�� */
    if ( SMS_FALSE == SMS_TimerStop( ucTimerId ) )
    {
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: SMS_TimerStop fail." );;
    }

    switch(ucTimerId)
    {
    case SMC_TIMER_ID_PS_TC1M_MT:
        if (SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: PS MT state is idle." );
            return;
        }

        if (0 == g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendPsRpReport();
            if (VOS_TRUE == ulRet)
            {


                /* �澯�������Ӷ�������ʱ������ֵ���ж� */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_PS_TC1M_MT) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: TR1M Failed" );
                }


                return;
            }
        }

        if(SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState)
        {

            /* ������ѭ����ʱ��,��ʱ���ѱ�ֹͣ */

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                   /* �����ʱ����                             */

            if(0 != g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen)
            {                                                               /* �д洢����Ϣ                             */
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            }

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_TimerTc1mExp:NORMAL:SMS state = SMC_MT_IDLE");

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_TRUE);                                 /* �ϱ�����                                 */
        }

        break;
    case SMC_TIMER_ID_PS_TC1M_MO:
        if (SMC_MO_IDLE == g_SmcPsEnt.SmcMo.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: PS MO state is idle." );
            return;
        }

        if (0 == g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendPsRpData(VOS_TRUE);
            if (VOS_TRUE == ulRet)
            {


                /* �澯�������Ӷ�������ʱ������ֵ���ж� */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_PS_TC1M_MO) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_PS_TC1M_MO Failed" );
                }


                return;
            }
        }

        if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
        {

            /* ������ѭ����ʱ��,��ʱ���ѱ�ֹͣ */

            g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                   /* �����ʱ����                             */

            if(0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
            {                                                               /* �д洢����Ϣ                             */
                SMS_Free( g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg );
                g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMo.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
            }

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL:SMS state = SMC_MO_IDLE");

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_FALSE);                                 /* �ϱ�����                                 */
        }

        break;
    case SMC_TIMER_ID_CS_TC1M_MT:
        if (SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: CS MT state is idle." );
            return;
        }

        if (0 == g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendCsRpReport();
            if (VOS_TRUE == ulRet)
            {


                /* �澯�������Ӷ�������ʱ������ֵ���ж� */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_CS_TC1M_MT) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_CS_TC1M_MT Failed" );
                }


                return;
            }

        }

        if(SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState)
        {
            SMC_ComCsInitEnt( SMS_TRUE );                                   /* ��ʼ��CS���ʵ��                         */

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_TRUE);                                 /* �ϱ�����                                 */
        }

        break;
    case SMC_TIMER_ID_CS_TC1M_MO:
        if (SMC_MO_IDLE == g_SmcCsEnt.SmcMo.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: CS MO state is idle." );
            return;
        }

        if (0 == g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendCsRpData(VOS_TRUE);
            if (VOS_TRUE == ulRet)
            {


                /* �澯�������Ӷ�������ʱ������ֵ���ж� */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_CS_TC1M_MO) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_CS_TC1M_MO Failed" );
                }


                return;
            }
        }

        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_ComCsInitEnt( SMS_FALSE );                                  /* ��ʼ��CS���ʵ��                         */

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_FALSE);                                 /* �ϱ�����                                 */
        }

        break;
    default:
        break;
    }
}
VOS_VOID  SMC_GetCpDataTiValidFlag(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            *pbValidFlag
)
{
    VOS_UINT8                           ucCmpTi;

    /* ��ʾ���յĸ���Ϣ����MO������ */
    if ((ucTi & 0x80) != 0x80)
    {
        *pbValidFlag = VOS_TRUE;
        return;
    }

    ucCmpTi = ucTi >> 4;

    /* PS���MOʵ��״̬��Ϊ��                   */
    if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
    {
        /* TI���                                   */
        if(ucCmpTi == g_SmcPsEnt.SmcMo.ucTi)
        {
            *pbValidFlag = VOS_TRUE;
            return;
        }
    }

    /* CS���MOʵ��״̬��Ϊ��                   */
    if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
    {
        /* TI���                                   */
        if (ucCmpTi == g_SmcCsEnt.SmcMo.ucTi)
        {
            *pbValidFlag = VOS_TRUE;
            return;
        }

        if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {
            /* TI���: MO�����У������ط�RP-ACKʱ���ߵ�������*/
            if (ucCmpTi == g_SmcCsEnt.SmcMo.ucPreTi)
            {
                *pbValidFlag = VOS_TRUE;
                return;
            }
        }
    }

    *pbValidFlag = VOS_FALSE;
    return;
}


VOS_UINT8 SMC_ComNwMsgChk(
                     VOS_UINT8* pucCpdu,
                     VOS_UINT32  ulCpduLen
                     )
{
    VOS_BOOL                            bTiValidFlag;

    /*24011 9.2.1 Message too short , ������Ϣ*/
    if(ulCpduLen < 2)
    {                                                                           /* ��Ϣ̫��                                 */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Message too short!");
        return SMC_CP_ERR_MSG_INVALID;
    }

    /*24011 9.2.2  TI valueΪ0x111, ������Ϣ*/
    if (((pucCpdu[0] >> 4) & 0x07) == 0x07)
    {                                                                           /* TI����                                   */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS TI ERROR!");
        return SMC_CP_ERR_MSG_INVALID;
    }

    if(SMC_DATA_TYPE_CP_DATA == pucCpdu[1])
    {
        /*UE�յ����Խ���ʵ���CP-DATA��Ϣ����TI��һ��������Ϣ*/
        SMC_GetCpDataTiValidFlag(pucCpdu[0], &bTiValidFlag);
        if(VOS_TRUE != bTiValidFlag)
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MSG INVALID!");
            return SMC_CP_ERR_MSG_INVALID;
        }
        /* ������ǿ��IE                             */
        if(ulCpduLen <= 2)
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MANDATORY INFO ERROR!");
            return SMS_CP_ERR_MANDA_INFO_ELEM_ERR;
        }
    }
    else if (SMC_DATA_TYPE_CP_ERR == pucCpdu[1])
    {
        if(ulCpduLen < 3)
        {                                                                       /* ������ǿ��IE                             */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MSG INVALID!");
            return SMC_CP_ERR_MSG_INVALID;                                      /* ���ش���ԭ��                             */
        }
        /*TIֵ����ʱ,ignore����Ϣ*/
        if((((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMt.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMt.ucTi)
            )
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Cp-err,invalid Ti!");
            return SMC_CP_ERR_MSG_INVALID;                                      /* ���ش���ԭ��                             */
        }
    }
    else if (SMC_DATA_TYPE_CP_ACK == pucCpdu[1])
    {                                                                           /* ��Ϣ������CP-ACK                       */
        if((((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMt.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMt.ucTi))
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Cp-ACK,invalid Ti!");
            return SMS_CP_ERR_INVALID_TI;                                      /* ���ش���ԭ��                             */
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Sms-msg-type error!");
        return SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT;                                      /* ���ش���ԭ��                             */
    }

    return SMC_MSG_VALID;
}
VOS_VOID SMC_MoBufferCpAckSend(VOS_VOID)
{
    if ((SMS_TRUE != g_SmcCsEnt.SmcMo.ucCpAckFlg)
     && (SMS_TRUE != g_SmcPsEnt.SmcMo.ucCpAckFlg))
    {
        PS_NAS_LOG(WUEPS_PID_SMS,
               VOS_NULL,
               PS_LOG_LEVEL_NORMAL,
               "SMC_MoBufferCpAckSend:INFO: no CP-ACK need to send.");
        return;
    }

    if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
    {
        g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                                /* ָʾMM�ͷ�MM����                         */

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_NORMAL,
                   "SMC_MoBufferCpAckSend: SMS state = SMC_MO_IDLE");
        }
        else if (SMC_MO_MM_CONN_PENDING == g_SmcCsEnt.SmcMo.ucState)
        {
            if (g_SmcCsEnt.SmcMo.ucPreTi == g_SmcCsEnt.SmcMo.ucTi)
            {
                PS_NAS_LOG(WUEPS_PID_SMS,
                       VOS_NULL,
                       PS_LOG_LEVEL_WARNING,
                       "SMC_MoBufferCpAckSend: "
                       "Current TI and previous TI is indentical.");
                return;
            }
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucPreTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);                                /* ָʾMM�ͷ�MM����                         */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "SMC_MoBufferCpAckSend:WARNING: CP-ACK indication and C layer"
                   "state not indentical.");
        }
    }
    else
    {
        g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ACK, 0XFF, g_SmcPsEnt.SmcMo.ucTi );
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                                   0XFF,
                                   g_SmcPsEnt.SmcMo.ucTi );                         /* �������ȷ��                             */
            }
            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_NORMAL,
                   "SMC_MoBufferCpAckSend: SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_WARNING,
                   "SMC_MoBufferCpAckSend: CP-ACK indication and C layer"
                   "state not indentical.");
        }
    }

    return;
}
/*lint -restore */

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_SMS_NotifySessionAccordingCsMoEntityStateChg(VOS_UINT8  ucState)
{
    /* cs����ʵ��״̬��idle����idle��������Դ */
    if ((SMC_MO_IDLE == g_SmcCsEnt.SmcMo.ucState)
     && (SMC_MO_IDLE != ucState))
    {
        NAS_SMS_SndMmBeginSessionNotify(MMSMS_SESSION_TYPE_MO_SMS);
    }

    /* cs����ʵ��ӷ�idle��idle���ͷ���Դ */
    if ((SMC_MO_IDLE == ucState)
     && (SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState))
    {
        NAS_SMS_SndMmEndSessionNotify(MMSMS_SESSION_TYPE_MO_SMS);
    }

    return;
}
#endif


VOS_VOID NAS_SMS_ChangeCsMoEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMo.ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SMS_NotifySessionAccordingCsMoEntityStateChg(ucState);
#endif

    g_SmcCsEnt.SmcMo.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMo.ucState);

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_SMS_NotifySessionAccordingCsMtEntityStateChg(VOS_UINT8  ucState)
{
    /* cs mtʵ��״̬��idle����idle,���뱻����Դ */
    if ((SMC_MT_IDLE ==g_SmcCsEnt.SmcMt.ucState)
     && (SMC_MT_IDLE != ucState))
    {
        NAS_SMS_SndMmBeginSessionNotify(MMSMS_SESSION_TYPE_MT_SMS);
    }

    /* cs mtʵ��ӷ�idle��idle���ͷű�����Դ */
    if ((SMC_MT_IDLE == ucState)
     && (SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState))
    {
        NAS_SMS_SndMmEndSessionNotify(MMSMS_SESSION_TYPE_MT_SMS);
    }

    return;
}
#endif


VOS_VOID NAS_SMS_ChangeCsMtEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMt.ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SMS_NotifySessionAccordingCsMtEntityStateChg(ucState);
#endif

    g_SmcCsEnt.SmcMt.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMt.ucState);

    return;
}


VOS_VOID NAS_SMS_NotifySessionAccordingPsMoEntityStateChg(VOS_UINT8  ucState)
{
    /* ps�����ж���ʵ��״̬��idle����idle��������Դ */
    if ((SMC_MO_IDLE == g_SmcPsEnt.SmcMo.ucState)
     && (SMC_MO_IDLE != ucState))
    {
        NAS_SMS_SndGmmBeginSessionNotify(GMMSMS_SESSION_TYPE_MO_SMS);
    }

    /* ps�����ж���ʵ��״̬�ӷ�idle��idle���ͷ���Դ */
    if ((SMC_MO_IDLE == ucState)
     && (SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState))
    {
        NAS_SMS_SndGmmEndSessionNotify(GMMSMS_SESSION_TYPE_MO_SMS);
    }

    return;
}


VOS_VOID NAS_SMS_ChangePsMoEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMo.ucState);

    NAS_SMS_NotifySessionAccordingPsMoEntityStateChg(ucState);

    g_SmcPsEnt.SmcMo.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMo.ucState);

    return;
}


VOS_VOID NAS_SMS_NotifySessionAccordingPsMtEntityStateChg(VOS_UINT8  ucState)
{
    /* ps�򱻽ж���ʵ��״̬��idle����idle��������Դ */
    if ((SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState)
     && (SMC_MT_IDLE != ucState))
    {
        NAS_SMS_SndGmmBeginSessionNotify(GMMSMS_SESSION_TYPE_MT_SMS);
    }

    /* ps�򱻽ж���ʵ��״̬�ӷ�idle��idle���ͷ���Դ */
    if ((SMC_MT_IDLE == ucState)
     && (SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState))
    {
        NAS_SMS_SndGmmEndSessionNotify(GMMSMS_SESSION_TYPE_MT_SMS);
    }

    return;
}


VOS_VOID NAS_SMS_ChangePsMtEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMt.ucState);

    NAS_SMS_NotifySessionAccordingPsMtEntityStateChg(ucState);

    g_SmcPsEnt.SmcMt.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMt.ucState);

    return;
}



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

