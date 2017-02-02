
#include "smsinclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SMR_COM_C



VOS_VOID SMR_MemNotifyRetrans(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulSendLen
)
{
    if ( SMR_RETRANS_PERMIT != g_SmrEnt.SmrMo.ucRetransFlg )
    {                                                                           /* RETRANS FLAG ��λ                        */
        SMS_SendMnReportReq(enErrorCode, pucData, ulSendLen);
        g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;                      /* ��RETRANS FLAG��0���                    */
        g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                               /* �����־λ                               */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
        g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
    }
    else
    {
        SMC_SmrApiRelReq((VOS_UINT8)enErrorCode, SMS_FALSE );                                   /* ����MNSMS_REL_REQ,�ͷ�mm����             */
        /*���ǰ�����Ϣ*/
        g_SmrEnt.SmrMo.ucRetransFlg = SMR_RETRANS_NO_PERMIT;                    /* ��RETRANS FLAG��0���                    */

        /* ������ʱ��TRAM */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_MemNotifyRetrans: TimerStart: TRAM" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TRAM ) )
        {
            return;
        }

        g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RETRANS_TIMER;   /* ״̬Ǩ��                                 */

    }
}
VOS_VOID SMR_TimerTr1mExpire()
{
    /* ֹͣtimer TR1M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTr1mExpire: TimerStop: TR1M" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
    {
        return;
    }

    if ( SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState )
    {
        if ( SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg )
        {                                                                       /*���ڴ�֪ͨ����                            */
            SMR_MemNotifyRetrans(SMR_SMT_ERROR_TR1M_TIMEOUT, VOS_NULL_PTR, 0);         /* �����ط����̵Ĵ���                       */

            if (SMR_IDLE == g_SmrEnt.SmrMo.ucState)
            {
                SMC_SmrApiRelReq(SMR_SMC_REL_CAUSE_NORMAL, SMS_FALSE );             /* �ͷŵ�ǰ���ڽ�������Ϣ����Դ */
            }

        }
        else
        {
            SMC_SmrApiAbortReq(SMR_SMC_ABORT_CAUSE_TR1M_EXP);                   /* �����౨��                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_TimerTr1mExpire:NORMAL:SMS state = SMR_IDLE");
            g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                  /* �������                                 */

            SMS_SendMnReportReq(SMR_SMT_ERROR_TR1M_TIMEOUT, VOS_NULL_PTR, 0);

        }
    }
}

VOS_VOID SMR_TimerTr2mExpire()
{
    /* ֹͣtimer TR2M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTr2mExpire: TimerStop: TR2M" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
    {
        return;
    }

    /* g_SmrEnt.SmrMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
    if (SMR_WAIT_TO_SND_RP_ACK == g_SmrEnt.SmrMt.ucState)
    {
        SMC_SmrApiAbortReq( SMR_SMC_ABORT_CAUSE_TR2M_EXP );                     /* ����MNSMS_ABORT_REQ                      */
        /* SMR_MkSndReportError( g_SmrEnt.SmrMt.ucMr,SMR_ERR_CAUSE_TEMP_FAILURE );  ����SMRL_REPORT_IND                      */
        /*��ʱ����ʱ�󣬻�û����Ӧ��֪ͨAT�޸�+CNMI�������<mt>��<ds>��Ϊ0*/
        SMS_SendMnMtErrInd(SMR_SMT_ERROR_TR2M_TIMEOUT);
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_TimerTr2mExpire:NORMAL:SMS state = SMR_IDLE");
        g_SmrEnt.SmrMt.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
    }
}
/*******************************************************************************
Module:   SMR_TimerTramExpire
Function: TRAM��ʱ���������
Input:
Output:
NOTE:
Return:   VOS_VOID
History:
1.   ��־��   2004.03.10   �¹�����
2.
*******************************************************************************/
VOS_VOID SMR_TimerTramExpire()
{
    VOS_UINT8     ErrData[3];    /*A32D00461,zzy,pclint*/                                                    /* ������ʱָ��RP_SMMA��ָ��                */

    /* ֹͣtimer TRAM */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTramExpire: TimerStop: TRAM" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
    {
        return;
    }

    /* g_SmrEnt.SmrMo.aTimerInfo[1].ucTimerSta = SMS_TIMER_STATUS_STOP; */

    if ( SMR_WAIT_FOR_RETRANS_TIMER == g_SmrEnt.SmrMo.ucState )
    {
        g_SmrEnt.SmrMo.ucRetransFlg = SMR_RETRANS_PROCESS;                      /* ��ʵ���ڵ�RetransFlg��ΪSMR_RETRANS_PROC
                                                                                 * ESS                                      */
        ErrData[0] = 2;                                                    /* ��дRP_SMMA����Ϣ����                    */
        ErrData[1] = SMR_MTN_DATA_TYPE_RP_SMMA;                            /* ��дRP_SMMA����Ϣ����                    */
        /*lint -e961*/
        g_SmrEnt.SmrMo.ucMr = ++g_ucSmsMR;
        /*lint +e961*/
        ErrData[2] = g_SmrEnt.SmrMo.ucMr;                              /* ��дRP_SMMA��MR                          */

        SMC_SmrApiEstReq(g_ucCurSendDomain,ErrData,3);                                           /* ����MNSMS_EST_REQ                        */

        /* ������ʱ��TR1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTramExpire: TimerStart: TR1M" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
        {
            return;
        }

        /* g_SmrEnt.SmrMo.aTimerInfo[0].ucTimerSta = SMS_TIMER_STATUS_RUN; */

        g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RP_ACK;          /* ״̬Ǩ�Ƶ�SMR_WAIT_FOR_RP_ACK״̬        */
    }
}
VOS_UINT8 SMR_SmcChk(
                 VOS_UINT8     *pucData,                                            /* �����׵�ַ                               */
                 VOS_UINT32     ulLen                                                /* ���ݳ���                                 */
                 )
{
    VOS_UINT16 usSmsMsgLength;                                                      /* ����洢��Ϣ�ĳ��ȵı���                 */
    if (ulLen < 2)
    {                                                                           /* �����Ϣ����                             */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_MSG_TOO_SHORT_ERROR ");
        return SMR_MSG_TOO_SHORT_ERROR;
    }
    switch(pucData[0])
    {
    case SMR_NTM_DATA_TYPE_RP_DATA:
        /*Ӧ������RP-Data����С����*/
        if (ulLen < SMR_MIN_RP_DATA_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP DATA ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        if ((*(pucData+2) < 2)||(*(pucData+2) > 11))
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        usSmsMsgLength = 2+ *(pucData+2)+1;                                     /* ����RP_Originator Address��ĳ���        */
        if (usSmsMsgLength >= ulLen)
        {                                                                       /* ��Ϣ�ĳ��ȴ���                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        usSmsMsgLength += 1;                                                    /* ����RP_Destination Address��ĳ���       */
        usSmsMsgLength += (pucData[usSmsMsgLength]+1);                          /* ����RP_User Data��ĳ���                 */
        if (usSmsMsgLength > ulLen)
        {                                                                       /* ��Ϣ�ĳ��ȴ���                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        break;
    case SMR_NTM_DATA_TYPE_RP_ACK:
        if (ulLen < SMR_MIN_RP_ACK_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP ACK ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        usSmsMsgLength = 2;                                                     /* ������Ϣ�ĳ���                           */
        if ( 41 == *(pucData+2))
        {                                                                       /* �����Ϣ�а���USER DATA                  */
            usSmsMsgLength = usSmsMsgLength + 2 + *(pucData+3);
        }
        if (usSmsMsgLength > ulLen)
        {                                                                       /* ��Ϣ�ĳ��ȴ���                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        break;
    case SMR_NTM_DATA_TYPE_RP_ERR:
        if (ulLen < SMR_MIN_RP_ERROR_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP ERROR ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        usSmsMsgLength =  2 + *(pucData+2)+1;                                   /* ������Ϣ�ĳ���                           */
        if (usSmsMsgLength > ulLen)
        {                                                                       /* ��Ϣ�ĳ��ȴ���                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR ");
            return  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
        }
        else if(usSmsMsgLength < ulLen)
        {
            if ( 41 == *(pucData+ usSmsMsgLength))
            {                                                                   /* �����Ϣ�а���USER DATA                  */
                usSmsMsgLength = usSmsMsgLength +
                                  *(pucData + usSmsMsgLength+1)+2;
            }
            if (usSmsMsgLength > ulLen)
            {                                                                   /* ��Ϣ�ĳ��ȴ���                           */
                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR ");
                return  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
            }
        }
        else
        {

        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST ");
        return SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
    }
    return SMR_MSG_CHK_SUCCESS;
}
/*******************************************************************************
Module:   SMR_SndRpErrorReq
Function: ���ɲ����²㷢��RP_ERROR����MNSMS_DATA_REQ
Input:    VOS_UINT8     ucMr     Message Reference
          VOS_UINT8     ucCause  RP_Cause��ԭ��ֵ
          VOS_UINT8     ucMtFlg  mt��־
Output:
NOTE:
Return:   VOS_UINT8
History:
1.   ��־��   2004.03.10   �¹�����
2.
*******************************************************************************/
VOS_VOID SMR_SndRpErrorReq(
                       VOS_UINT8     ucMr,                                          /* Message Reference                        */
                       VOS_UINT8     ucCause,                                       /* RP_Cause��ԭ��ֵ                         */
                       VOS_UINT8     ucMtFlg                                        /* mt��־                                   */
                       )
{
    VOS_UINT8   ErrData[5];   /*A32D00461,zzy,pclint*/                                                          /* ������ʱָ�������Ϣ��ָ��               */

    if(SMS_FALSE == ucMtFlg)
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SndRpErrorReq:WARNING:ucMtFlg = SMS_FALSE");
        return;
    }

    ErrData[0]       = 4;                                                        /* ��дRP_ERROR����ϢRPDU�ĳ���             */
    ErrData[1] = SMR_ERR_CAUSE_MTI_MO_RP_ERROR;                            /* ��дRP_ERROR����Ϣ���� MS->N ֵΪ4       */
    ErrData[2] = ucMr;                                                     /* ��дRP_ERROR��MR                         */
    ErrData[3] = 1;                                                        /* ��дRP_Cause�ĳ���                       */
    ErrData[4] = ucCause;                                                  /* ��дRP_Cause��ԭ��ֵ                     */
    SMC_SmrApiDataReq(ErrData,5);                                              /* ���÷���API                              */
}

/* Delete SMR_MkSndReportError */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

