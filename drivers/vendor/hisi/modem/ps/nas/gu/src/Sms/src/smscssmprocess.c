
#include "smsinclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SMS_CSSMPROCESS_C


extern VOS_UINT8  Smt_StartMemNotification( VOS_VOID );
extern VOS_VOID SMC_ReportM2NOtaMsg(NAS_MSG_STRU *pMsg);

/*lint -save -e958 */

VOS_UINT32 NAS_SMS_ResendCsRpData(VOS_UINT8 ucRetransFlg)
{
    VOS_UINT8                           ucRdPos;
    VOS_UINT8                           ucTpType;

    if ((VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg)
     || (0 == g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

    /* SUBMIT ������Ҫ���޸�TP-RD�����޸�TP-RD���� */
    if (SMS_TRUE != g_SmrEnt.SmrMo.ucMemAvailFlg)
    {
        ucRdPos  = (VOS_UINT8)(SMS_TPDU_MTI_CS + *((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + SMS_TPDU_SCLEN_CS));
        ucTpType = (*((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos)) & NAS_SMS_TP_MTI_MASK;

        if ((NAS_SMS_TP_MTI_SUBMIT == ucTpType)
         && (VOS_TRUE == ucRetransFlg))
        {
            *((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos) |= SMT_TP_RD_RETRANS;
        }
    }

    SMC_SndMmMsg(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg,
                 MMSMS_DATA_REQ,
                 (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen);

    return VOS_TRUE;
}
VOS_UINT32 NAS_SMS_ResendCsRpReport(VOS_VOID)
{

    if ((VOS_NULL_PTR == g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg)
     || (0 == g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

    SMC_SndMmMsg(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg,
                 MMSMS_DATA_REQ,
                 (VOS_UINT16)g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen);

    return VOS_TRUE;
}



VOS_VOID NAS_SMS_RcvNackMsg(MMSMS_NACK_DATA_IND_STRU *pstNackMsg)
{
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucTiValue;
    VOS_UINT8                           ucTiFlag;
    VOS_UINT8                           ucCpType;
    VOS_UINT8                           ucRpType;
    VOS_UINT32                          ulRet;

    ucPos = 0;

    /* ��ȡTI��TI-flag����Ϣ���ͣ�*/
    ucTiFlag  = (VOS_UINT8)((pstNackMsg->stNackMsg.aucNasMsg[ucPos] & NAS_SMS_TI_FLAG_MASK) >> NAS_SMS_TI_FLAG_OFFSET);
    ucTiValue = (VOS_UINT8)((pstNackMsg->stNackMsg.aucNasMsg[ucPos] & NAS_SMS_TI_VALUE_MASK) >> NAS_SMS_TI_VALUE_OFFSET);

    ucPos++;

    /*
    δ������Ϣ�ش�����:
    CP-ACK��Ϣ���ش���
    SUBMIT��COMMAND��Ϣ���ж�MO ENTITY��TIһ�£�TI-FLAG��ȷ��
    DELIVER-REPORT��Ϣ���ж�MT ENTITY��TIһ�£�TI-FLAG��ȷ��
    ���������������
    */
    ucCpType = pstNackMsg->stNackMsg.aucNasMsg[ucPos];
    if (SMC_DATA_TYPE_CP_DATA != ucCpType)
    {
        return;
    }
    ucPos++;

    /* RPDU length */
    ucPos++;

    /* RPDU tag */
    ucRpType = pstNackMsg->stNackMsg.aucNasMsg[ucPos];

    /* SMMA SUBMIT��COMMAND��Ϣ���ж�MO ENTITY��TIһ�£�TI-FLAG��ȷ�� */
    /* RP-ACK��Ϣ���ж�MO ENTITY��TIһ�£�TI-FLAG��ȷ�� */
    /* SUBMIT ������Ҫ�޸�TP-RD���� */
    /* ����������COMMAND��RP-ACK��Ϣֱ�ӷ��ͼ��� */
    if ((SMR_MTN_DATA_TYPE_RP_ACK == ucRpType)
     || (SMR_MTN_DATA_TYPE_RP_ERR == ucRpType))
    {
        if (((g_SmcCsEnt.SmcMt.ucTi & NAS_SMS_LOCAL_TI_VALUE_MASK) != ucTiValue)
         || (NAS_SMS_TI_FLAG_MSG_SEND_TO_ORIG != ucTiFlag))
        {
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: g_SmcCsEnt.SmcMt.ucTi ", g_SmcCsEnt.SmcMt.ucTi);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiValue ", ucTiValue);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiFlag ", ucTiFlag);
            return;
        }

        ulRet = NAS_SMS_ResendCsRpReport();
        if (VOS_TRUE != ulRet)
        {
            return;
        }

        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "SMS:NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "SMS:NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        return;
    }
    else
    {
        if (((g_SmcCsEnt.SmcMo.ucTi  & NAS_SMS_LOCAL_TI_VALUE_MASK) != ucTiValue)
         || (NAS_SMS_TI_FLAG_MSG_SEND_FROM_ORIG != ucTiFlag))
        {
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: g_SmcCsEnt.SmcMt.ucTi ", g_SmcCsEnt.SmcMt.ucTi);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiValue ", ucTiValue);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiFlag ", ucTiFlag);
            return;
        }

        ulRet = NAS_SMS_ResendCsRpData(VOS_TRUE);
        if (VOS_TRUE != ulRet)
        {
            return;
        }

        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }
    }

    return;
}



VOS_VOID SMC_RcvNwCsMtData(
                       VOS_UINT8*   pucCpdu,
                       VOS_UINT32    ulCpduLen
                      )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet;
    SMC_ENTITY_STRU     g_OrgSmcEnt;
    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* ��Ϣ���                                 */
    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* �������                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR, ucResult,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvNwCsMtData:WARNING:SMC_MSG_VALID != ucResult ");
        return;
    }

    switch(pucCpdu[1])
    {                                                                           /* ��Ϣ����                                 */
    case SMC_DATA_TYPE_CP_DATA:
        SMS_Memcpy(&g_OrgSmcEnt, &g_SmcCsEnt, sizeof(SMC_ENTITY_STRU));
        if(g_SmcCsEnt.SmcMt.ucTi != (pucCpdu[0] >> 4))
        {
            if(SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
            {
                /* It should be copied that receive the CP ACK at SMC_MT_WAIT_FOR_CP_ACK state */
                /* ֹͣtimer TC1M */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
                {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M failed" );
                }

                g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* ���timer��ʱ����                        */

                NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

                if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
                {
                    SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* �ͷŻ������Ϣ                           */
                    g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* ��ʼ����Ϣ����                           */
                }
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_INVALID_TI,
                                  pucCpdu[0] >> 4 );                                /* ������ָʾ����                           */

                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: Invalid Ti,ignore MSG" );
                return ;
            }
        }

        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* ʵ��״̬�ǿ��л��ڵȴ�����ȷ��           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMtData:NORMAL:SMS state = SMC_MT_WAIT_FOR_RP_ACK");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_RP_ACK);

            g_SmcCsEnt.SmcMt.ucTi = pucCpdu[0] >> 4;                            /* �洢ti                                   */

            g_SmcCsEnt.SmcMt.ucMr = pucCpdu[SMC_MSG_HDR_LEN + 2];               /* �洢mr                                   */

            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ACK,
                              0XFF,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* �������ȷ��                             */

            ulRet = SMR_SmcApiEstInd( &(pucCpdu[3]),
                                      (ulCpduLen - SMC_MSG_HDR_LEN) - 1,
                                      SMS_CN_CS );                /* ��߲��ύ����                           */
            if(VOS_OK == ulRet)
            {
                if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
                {
                    SMC_ComCsWaitAckSta(SMS_TRUE);                                  /* ���ù�������                             */
                }
            }
            else
            {
                SMS_Memcpy(&g_SmcCsEnt,&g_OrgSmcEnt, sizeof(SMC_ENTITY_STRU));
            }
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              pucCpdu[0] >> 4 );                                /* ������ָʾ����                           */
        }
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if(SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* ��ʵ���״̬����                         */
            /* ֹͣtimer TC1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M failed" );
            }

            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* ���timer��ʱ����                        */

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

            if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
            {
                SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* �ͷŻ������Ϣ                           */
                g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* ��ʼ����Ϣ����                           */
            }

            SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* �ͷ�mm����                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMtData:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ָʾ����                           */
        }
        break;
    case SMC_DATA_TYPE_CP_ERR:
        if( SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState )
        {                                                                       /* ��ʵ���״̬����                         */
            SMC_ComCsInitEnt(SMS_TRUE);                                         /* ��ʼ��CS���ʵ��                         */
        }
        break;
    default:
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                          (pucCpdu[0] & 0xf0) >> 4 );                           /* �����౨�� δʶ�����Ϣ����              */
        break;
    }
    return;
}
VOS_VOID SMC_RcvMmEstInd(
                     VOS_UINT8*   pucCpdu,
                     VOS_UINT32    ulCpduLen
                     )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet ;

    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* ��Ϣ���                                 */

    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* �������                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              ucResult,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */

        }

        SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                                /* �ͷ�mm����                               */

        return;
    }

    if (SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
    {                                                                       /* ��ʵ���״̬����                         */
        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstInd: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstInd: TimerStop: TC1M failed" );
        }

        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* ���timer��ʱ����                        */

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

        if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
        {
            SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* �ͷŻ������Ϣ                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* ��ʼ����Ϣ����                           */
        }

        SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* �ͷ�mm����                               */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstInd:NORMAL:SMS state = SMC_MT_IDLE");

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

    }

    if(SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
    {                                                                           /* ʵ���ǿ���״̬                           */
        if(SMC_DATA_TYPE_CP_DATA == pucCpdu[1])
        {                                                                       /* ����������CP-DATA                        */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstInd:NORMAL:SMS state = SMC_MT_WAIT_FOR_RP_ACK");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_RP_ACK);

            g_SmcCsEnt.SmcMt.ucTi    = pucCpdu[0] >> 4;                         /* �洢ti                                   */
            g_SmcCsEnt.SmcMt.ucMr    = pucCpdu[SMC_MSG_HDR_LEN + 2];            /* �洢mr                                   */

            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ACK,
                              0xff,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* �������ȷ��                             */

            ulRet = SMR_SmcApiEstInd( &(pucCpdu[3]),
                                       (ulCpduLen - SMC_MSG_HDR_LEN) - 1,
                                       SMS_CN_CS );                /* ��߲��ϱ�����                           */
            if (VOS_OK != ulRet)
            {
                if (SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR == ulRet)
                {
                    SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* �ͷ�mm����                               */

                    NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
                }
                else
                {
                    NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);
                }
            }
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */
            SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                            /* �ͷ�mm����                               */
        }
    }
    else
    {
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                          (pucCpdu[0] & 0xf0) >> 4 );                           /* ������ش���ָʾ                         */
        SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                                /* �ͷ�mm����                               */
    }
    return;
}

VOS_VOID SMC_RcvNwCsMoData(
                       VOS_UINT8* pucCpdu,
                       VOS_UINT32  ulCpduLen
                      )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet;

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* ��Ϣ���                                 */
    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* �������                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              ucResult,
                              (pucCpdu[0] & 0xf0)>>4);                          /* ������ش���ָʾ                         */
        }
        return;
    }

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: event ", pucCpdu[1] );
    switch( pucCpdu[1] )
    {                                                                           /* ��Ϣ����                                 */
    case SMC_DATA_TYPE_CP_DATA:
        if((SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState)||
           (SMC_MO_MM_CONN_EST == g_SmcCsEnt.SmcMo.ucState))
        {                                                                       /* ״̬��ȷ                                 */
            if (ulCpduLen > (SMC_MSG_HDR_LEN + 1))
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_TRUE;                             /* ������Ҫ����CP-ACK��־                   */
                ulRet = SMR_SmcApiDataInd(&(pucCpdu[3]),
                                          (ulCpduLen - SMC_MSG_HDR_LEN) -1);                 /* ��߲��ύ����                           */
                if(VOS_OK == ulRet )
                {
                    /*MO����SMC_MO_WAIT_FOR_CP_ACK״̬˵��û�н��յ�CP-ACKֱ�ӽ���RP-ACK/ERR*/
                    if (SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
                    {
                        /* ֹͣtimer TC1M */
                        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMoData: TimerStop: TC1M" );
                        if (SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
                        {
                            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_RcvNwCsMoData: fail to Stop TC1M" );
                        }

                        if (0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                        {                                                                   /* �д洢�ķ�����Ϣ                         */
                            SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);                     /* �ͷŴ洢����Ϣ                           */
                            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                       /* �����Ϣ����                             */
                        }

                        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                        /* ���timer��ʱ����                        */
                    }

                    NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_TO_SND_CP_ACK);
                }
                else
                {
                    if (SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR != ulRet)
                    {
                        NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);

                    }
                    else
                    {
                        NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_DATA);
                    }
                    g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;                             /* ������Ҫ����CP-ACK��־                   */
                }
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MANDA_INFO_ELEM_ERR,
                                  (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */
            }
        }
        else
        {
            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                SMC_MoBufferCpAckSend();
                SMS_SendMnMoLinkCloseInd();
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                                  (pucCpdu[0] & 0xf0) >> 4);                        /* ������ش���ָʾ                         */
            }
        }
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if( SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* ״̬��ȷ                                 */
            SMC_ComCsWaitAckSta( SMS_FALSE );                                   /* ���ù�������                             */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData:NORMAL:SMS state = SMC_MO_MM_CONN_EST");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_MM_CONN_EST);
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */
        }

        break;
    case SMC_DATA_TYPE_CP_ERR:
        if ( SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* ״̬��ȷ                                 */
            SMC_ComCsInitEnt(SMS_FALSE);                                        /* ��ʼ��CS���ʵ��                         */

            SMR_SmcApiErrorInd((SMR_SMT_ERROR_CP_ERROR_BEGIN | pucCpdu[2]) , SMS_FALSE);                        /* ���ϲ㱨��                               */
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* ������ش���ָʾ                         */
        }

        break;
    default:
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                          (pucCpdu[0] & 0xf0) >> 4);                        /* ������ش���ָʾ                         */
        break;
    }
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
    return;
}

VOS_VOID SMC_RcvMmEstCnf(
                        MMSMS_EST_CNF_STRU * pRcvMsg                            /* �յ�����Ϣ�׵�ַ                         */
                    )
{
    VOS_UINT16 usMsgLen;                                                            /* ������Ϣ����                             */
    VOS_UINT8 *pucData   = SMS_POINTER_NULL;                                        /* ����洢��Ϣ�����׵�ַ��ָ��             */
    VOS_UINT8  aucSnd[255];


    if(g_SmcCsEnt.SmcMo.ucTi != (VOS_UINT8)(pRcvMsg->ulTi))
    {                                                                           /* TI���� ������Ϣ ����                     */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:g_SmcCsEnt.SmcMo.ucTi != (VOS_UINT8)(pRcvMsg->ulTi) ");
        return;
    }

    if(pRcvMsg->ulTi < 8)
    {                                                                           /* ���TIС��8                              */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:pRcvMsg->ulTi < 8");
        return;
    }

    if(g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen == 0)
    {                                                                           /* �л������Ϣ                             */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:none message to send.");
        return;
    }

    /* ǰһMO��TI�򻺴�CP-ACK��û���ͷ�, �˴���Ҫ��ɢ�����CP-ACK���ͷ�TI */
    if(SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
    {
        /*����ǰһTI ��CP-ACK*/
        SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucPreTi);
        /*�ͷ�ǰһTI*/
        SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);

        /* �����Ҫ����CP-ACK��־��֪ͨ T ��CP-ACK�ѷ��� */
        g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        SMS_SendMnMoLinkCloseInd();

    }

    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMC_RcvMmEstCnf: SMC_TIMER_ID_TR1M Timer stop fails" );
    }

    if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf: TimerStart: TR1M Failed" );
    }

    g_SmcCsEnt.SmcMo.ucMr =
                 ((VOS_UINT8 *)(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg))[2];          /* ��¼RP-MR                                   */
    g_SmrEnt.SmrMo.ucMr =
                 ((VOS_UINT8 *)(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg))[2];          /* ��¼RP-MR                                   */

    /*����g_SmcCsEnt.SmcMo.HoldRcvMsg������ϢCP-DATA(RP-DATA)��MM*/
    usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU) - 4) +
               (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen) +
               SMC_MSG_HDR_LEN;                                                 /* �����Ϣ�ĳ���                           */
                                                                                /*ע��: (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen) + SMC_MSG_HDR_LENΪL3��Ϣ��aucSmsMsg����*/
    if( g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen < SMC_SND_MSG_MIN_LEN )
    {                                                                           /* ��Ϣ�ĳ��Ƚ�С                           */
        usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);                                 /* ������Ϣ�ĳ���                           */
    }

    SMS_Memset( aucSnd,0,usMsgLen );

    pucData = ((MMSMS_DATA_REQ_STRU *)aucSnd)->SmsMsg.aucNasMsg;

    ((MMSMS_DATA_REQ_STRU *)aucSnd)->ulTi = pRcvMsg->ulTi;
    pucData[0] = (VOS_UINT8 )((pRcvMsg->ulTi & 0x07) << 4);                     /* ��дTI                                   */
    pucData[0] |= NAS_PD_SMS;                                                   /* ��дPD                                   */
    pucData[1] = SMC_DATA_TYPE_CP_DATA;                                         /* ��д��Ϣ����                             */

    SMS_Memcpy( ( pucData + 2 ),
                g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg,
                g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen );

    ((MMSMS_DATA_REQ_STRU *)aucSnd)->SmsMsg.ulNasMsgSize =
                  g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen + SMC_MSG_HDR_LEN;

    SMS_Free( g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg );
    g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;

    /* ������ش���Ϣ��C��Ļ���HoldSndMsg�� */
    g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc( usMsgLen );  /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_RcvMmEstCnf: Memory allocation fails" );
        return;
    }
    SMS_Memcpy( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg,
                aucSnd,
                usMsgLen );                                                     /* ������Ϣ                                 */
    g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = usMsgLen;                        /* ������Ϣ����                             */

    /* ������ʱ��TC1M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstCnf: TimerStart: TC1M" );
    if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MO ) )
    {
        SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);
        g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                               /* �����Ϣ����                             */
        return;
    }

    g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

    SMC_SndMmMsg( aucSnd, MMSMS_DATA_REQ, usMsgLen );                       /* ������Ϣ                                 */

    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstCnf:NORMAL:SMS state = SMC_MO_WAIT_FOR_CP_ACK");

    NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);

    return;
}
VOS_VOID SMC_ComCsMtErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
)
{
    /* TI���                                   */
    if(g_SmcCsEnt.SmcMt.ucTi == ucTi)
    {
        /* ���Ž���ʵ���ڿ���̬������ */
        if (SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
        {
            return;
        }

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComCsMtErr:NORMAL:SMS state = SMC_MT_IDLE");

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

        SMC_ComCsInitEnt(SMS_TRUE);                                             /* ��ʼ��CS���ʵ��                         */
        SMR_SmcApiErrorInd(enErrorCode, SMS_TRUE);                              /* �ϱ�����                                 */
    }
    return;
}

VOS_VOID SMC_ComCsMoErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
)
{
    if( g_SmcCsEnt.SmcMo.ucTi == ucTi )
    {                                                                           /* TI���                                   */
        PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SMC_ComCsMoErr: g_SmcCsEnt.SmcMo.ucState is ",
                g_SmcCsEnt.SmcMo.ucState);
        switch(g_SmcCsEnt.SmcMo.ucState)
        {                                                                       /* MO��ʵ���״̬                           */
        case SMC_MO_WAIT_FOR_CP_ACK:
        case SMC_MO_WAIT_TO_SND_CP_ACK:
        case SMC_MO_MM_CONN_PENDING:
        case SMC_MO_MM_CONN_EST:
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComCsMoErr:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            SMC_ComCsInitEnt(SMS_FALSE);                                        /* ��ʼ��CS���ʵ��                         */
            SMR_SmcApiErrorInd(enErrorCode, SMS_FALSE);                             /* �ϱ�����                                 */
            break;
        default:
            break;
        }
    }
    return;
}
/*******************************************************************************
  Module:   SMC_ComCsWaitAckSta
  Function: ��ʼ����Ӧ����Դ
  Input:    VOS_UINT8   ucMtFlg   MO,MT���̵ı�ʶ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
      2.
*******************************************************************************/
VOS_VOID SMC_ComCsWaitAckSta(
                         VOS_UINT8   ucMtFlg                                        /* ��mt���� �ж�MO,MT���̵ı�ʶ             */
                         )
{
    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* ����mt����   ��MO����                    */
        if (0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg );                           /* �ͷŻ������Ϣ                           */
            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen        = 0;                        /* ��ʼ����Ϣ����                           */
        }

        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes    = 0;                        /* ���timer��ʱ����                        */

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            return;
        }
    }
    else
    {
        if (0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg );                           /* �ͷŻ������Ϣ                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen        = 0;                        /* ��ʼ����Ϣ����                           */
        }

        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes    = 0;                        /* ���timer��ʱ����                        */

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            return;
        }
    }
    return;
}

VOS_VOID SMC_RcvMmRelInd(
                     MMSMS_REL_IND_STRU  *pRcvMsg                               /* �յ�����Ϣ                               */
                     )
{
    if( pRcvMsg->ulTi < 7 )
    {                                                                           /* SMC MTʵ��                               */
        if( SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState )
        {                                                                       /* SMC MTʵ��״̬Ϊ�ǿ�                     */
            if( g_SmcCsEnt.SmcMt.ucTi == pRcvMsg->ulTi )
            {                                                                   /* TI���                                   */
                SMC_ComCsMtErr( (SMR_SMT_ERROR_CS_ERROR_BEGIN | pRcvMsg->ulRelCause),
                                (VOS_UINT8)pRcvMsg->ulTi);                         /* ����CS��MTʵ��Ĵ���                     */
            }
        }
    }
    else
    {
        if( SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* SMC MOʵ��״̬Ϊ�ǿ�                     */
            if( g_SmcCsEnt.SmcMo.ucTi == pRcvMsg->ulTi )
            {                                                                   /* TI���                                   */
                SMC_ComCsMoErr( (SMR_SMT_ERROR_CS_ERROR_BEGIN | pRcvMsg->ulRelCause),
                                (VOS_UINT8)pRcvMsg->ulTi);                         /* ����CS��MOʵ��Ĵ���                     */
            }
            else if ((SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
                  && (g_SmcCsEnt.SmcMo.ucPreTi == pRcvMsg->ulTi))
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
            else
            {
            }
        }
    }
    return;
}

/*******************************************************************************
  Module:   SMC_SndMmDataReq
  Function: ��MM����MMSMS_DATA_REQ
  Input:    VOS_UINT8     ucType   ��������
            VOS_UINT8     ucCause  ����ԭ��
            VOS_UINT8     ucTi     transaction id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��      2004.03.11   �¹�����
      2.
*******************************************************************************/
VOS_VOID SMC_SndMmDataReq(
                      VOS_UINT8     ucType,                                         /* ��������                                 */
                      VOS_UINT8     ucCause,                                        /* ����ԭ��                                 */
                      VOS_UINT8     ucTi                                            /* transaction id                           */
                     )
{
    VOS_UINT8               aucTempMsg[255];
    /* MMSMS_DATA_REQ_STRU  *pSndMsg = */
    /* (MMSMS_DATA_REQ_STRU *)Sms_AllocMsg( sizeof(MMSMS_DATA_REQ_STRU) );      ����ռ�                                 */
    SMS_Memset( aucTempMsg,0,sizeof(MMSMS_DATA_REQ_STRU) );                        /* ��ʼ������                               */

    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->ulTi                = ucTi;                                        /* ��дPD                                   */
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[0] = (VOS_UINT8)((ucTi ^ 0x08) << 4);                 /* ��дTI                                   */
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[0] |= NAS_PD_SMS;
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[1] = ucType;                                      /* ��д��Ϣ����                             */

    if(SMC_DATA_TYPE_CP_ERR == ucType)
    {                                                                           /* ����������cp-error                       */
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ERR_LEN;                          /* ��ֵ��Ϣ����                             */
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[2] = ucCause;                                 /* ��д����ԭ��                             */
    }
    else
    {
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ACK_LEN;                          /* ��ֵ��Ϣ����                             */
    }
    SMC_SndMmMsg(aucTempMsg,MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU));  /* ����mm��Ϣ                               */


    return;
}
/*******************************************************************************
  Module:   SMC_SndRelReq
  Function: ��MM����MMSMS_REL_REQ
  Input:    VOS_UINT8     ucTi     transaction id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��      2004.03.11   �¹�����
      2.
*******************************************************************************/
VOS_VOID SMC_SndRelReq(
                   VOS_UINT8    ucTi                                                /* transaction id                           */
                  )
{
    /* MMSMS_REL_REQ_STRU  *pSndMsg = */
    /* (MMSMS_REL_REQ_STRU *)Sms_AllocMsg( sizeof(MMSMS_REL_REQ_STRU) );   �����ڴ�ռ�                             */
    VOS_UINT8     aucTempMsg[255];

    SMS_Memset( aucTempMsg,0,sizeof(MMSMS_REL_REQ_STRU) );                         /* ��ʼ������                               */

    ((MMSMS_REL_REQ_STRU* )aucTempMsg)->ulTi = ucTi;                                                       /* ��ֵti                                   */

    SMC_SndMmMsg(aucTempMsg, MMSMS_REL_REQ, sizeof(MMSMS_REL_REQ_STRU));  /* ����GMM��Ϣ                              */


    return;
}

VOS_VOID SMC_SndMmMsg(
                  VOS_UINT8     *pucSnd,                                            /* ������Ϣ���׵�ַ                         */
                  VOS_UINT8     ucType,                                             /* ��Ϣ����                                 */
                  VOS_UINT16    usLen                                               /* ��Ϣ����                                 */
                  )
{
    VOS_UINT32  ulRet;
    VOS_UINT8   *pucMsg;

    pucMsg = (VOS_UINT8* )PS_ALLOC_MSG( WUEPS_PID_SMS,
                            usLen - VOS_MSG_HEAD_LENGTH );
    if ( VOS_NULL_PTR == pucMsg )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_SndMmMsg: Message allocation fails" );
        return;
    }

    PS_MEM_CPY(pucMsg, pucSnd, usLen);

    ((MSG_HEADER_STRU * )pucMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulSenderPid     = WUEPS_PID_SMS;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverPid   = WUEPS_PID_MM;
    ((MSG_HEADER_STRU * )pucMsg)->ulLength        = usLen - VOS_MSG_HEAD_LENGTH;
    ((MSG_HEADER_STRU * )pucMsg)->ulMsgName     = ucType;                       /* ��д��Ϣ����                             */

    /*Report event begin*/
    if( MMSMS_DATA_REQ == ucType )
    {
        SMC_ReportM2NOtaMsg(&(((MMSMS_DATA_REQ_STRU *)pucSnd)->SmsMsg));

    }
    /*Report event end*/

    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pucMsg );
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        SMS_LOG( PS_LOG_LEVEL_ERROR, "SMS:SMC_SndMmMsg:Error: Send msg fails" );
    }
}
VOS_VOID SMC_SndMmCpAckMsg(
                      VOS_UINT8     ucTi)
{
    VOS_UINT8                           aucTempMsg[255];
    VOS_UINT32                          ulMsgLen;
    MMSMS_DATA_REQ_STRU                 *pstCpAck;

    ulMsgLen = sizeof(MMSMS_DATA_REQ_STRU);

    SMS_Memset( aucTempMsg, 0, ulMsgLen);
    pstCpAck = (MMSMS_DATA_REQ_STRU *)aucTempMsg;

    pstCpAck->ulTi = ucTi;

    pstCpAck->SmsMsg.aucNasMsg[0] = (ucTi & 0x07) << 4;

    pstCpAck->SmsMsg.ulNasMsgSize = SMC_MSG_HDR_LEN;                                              /* ��ֵ��Ϣ����                             */
    pstCpAck->SmsMsg.aucNasMsg[0] |= NAS_PD_SMS;                                                  /* ��дpd                                   */
    pstCpAck->SmsMsg.aucNasMsg[1]  = SMC_DATA_TYPE_CP_ACK;                                         /* ��д��Ϣ����                             */

    SMC_SndMmMsg(aucTempMsg, MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU));         /* ������Ϣ                                 */

    return;
}


VOS_VOID SMC_ComCsInitEnt(
                         VOS_UINT8   ucMtFlg                                        /* �ж�MO,MT���̵ı�ʶ                      */
                     )
{
    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* ��MO����                                 */
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndRelReq( g_SmcCsEnt.SmcMo.ucTi );                             /* ָʾMM�ͷ�MM����                         */
        }
        if( 0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen )
        {                                                                       /* �д洢�Ľ�����Ϣ                         */
            SMS_Free( g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg );                       /* �ͷŴ洢����Ϣ                           */
            g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                           /* �����Ϣ����                             */
        }
        else if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {                                                                       /* �д洢�ķ�����Ϣ                         */
            SMS_Free( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg );                       /* �ͷŴ洢����Ϣ                           */
            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                           /* �����Ϣ����                             */
        }
        else
        {

        }

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
        }

        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;
        if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {
            g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;                             /* ������Ҫ����CP-ACK��־                   */
            SMS_SendMnMoLinkCloseInd();
        }

        NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
    }
    else
    {
        if( SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState )
        {
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* �ͷ�mm����                               */
        }
        if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
        {
            SMS_Free( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg );                       /* �ͷŻ������Ϣ                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* ��ʼ����Ϣ����                           */
        }

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: fail to stop SMC_TIMER_ID_CS_TC1M_MT." );
        }

        /* g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                           /* ���timer��ʱ����                        */

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

    }
    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_SMS_SndMmBeginSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSMS_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstBeginSessionNotify = (MMSMS_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmBeginSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstBeginSessionNotify->stMsgHeader.ulLength         = sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName        = MMSMS_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstBeginSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmBeginSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


VOS_VOID NAS_SMS_SndMmEndSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSMS_END_SESSION_NOTIFY_STRU      *pstEndSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstEndSessionNotify = (MMSMS_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmEndSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstEndSessionNotify->stMsgHeader.ulLength         = sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName        = MMSMS_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstEndSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmEndSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


#endif


VOS_VOID SMC_RcvMmRegStaInd(
                       MMSMS_REG_STATE_IND_STRU  *pRcvMsg                       /* �յ�����Ϣ�׵�ַ                         */
                       )
{
    if( (MM_SMS_REG_ATTACHED == pRcvMsg->ulRegSts )
     || (MM_SMS_REG_ATTACH_ATTEMPT_TO_UPDATE == pRcvMsg->ulRegSts )
        )
    {                                                                           /* ״̬ΪATTACH                             */
        g_ucCsRegFlg = SMS_TRUE;                                                  /* ��¼��״̬                               */
        g_ucCurSendDomain = SMS_SEND_DOMAIN_CS;
    }
    else
    {
        g_ucCsRegFlg = SMS_FALSE;                                                 /* ��¼��״̬                               */

        SMC_ComCsMtErr( SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMt.ucTi);         /* ����CS��MTʵ��Ĵ���                     */
        SMC_ComCsMoErr( SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMo.ucTi);         /* ����CS��MOʵ��Ĵ���                     */
    }
    SMS_AttachFlag(SMS_SEND_DOMAIN_CS,g_ucCsRegFlg);

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

